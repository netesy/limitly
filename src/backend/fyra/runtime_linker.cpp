#include "runtime_linker.hh"
#include <chrono>
#include <cerrno>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <unistd.h>
#include <sys/wait.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

namespace LM::Backend::Fyra {
namespace {
std::filesystem::path compiler_directory() {
#ifdef _WIN32
    std::vector<wchar_t> path(32768);
    auto length = GetModuleFileNameW(nullptr, path.data(), path.size());
    if (length && length < path.size()) return std::filesystem::path(std::wstring(path.data(), length)).parent_path();
#elif defined(__APPLE__)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::vector<char> path(size);
    if (_NSGetExecutablePath(path.data(), &size) == 0) return std::filesystem::weakly_canonical(path.data()).parent_path();
#elif defined(__linux__)
    return std::filesystem::read_symlink("/proc/self/exe").parent_path();
#endif
    if (const char* home = std::getenv("LYMAR_HOME")) return std::filesystem::path(home) / "bin";
    throw std::runtime_error("Cannot locate compiler runtime directory; set LYMAR_AOT_RUNTIME");
}
bool native_target(const target::TargetDescriptor& t) {
#if defined(_WIN32)
    if (t.os != target::OS::Windows) return false;
#elif defined(__APPLE__)
    if (t.os != target::OS::MacOS) return false;
#elif defined(__linux__)
    if (t.os != target::OS::Linux) return false;
#else
    return false;
#endif
#if defined(__x86_64__) || defined(_M_X64)
    return t.arch == target::Arch::X64;
#elif defined(__aarch64__) || defined(_M_ARM64)
    return t.arch == target::Arch::AArch64;
#elif defined(__riscv) && __riscv_xlen == 64
    return t.arch == target::Arch::RISCV64;
#else
    return false;
#endif
}
std::string target_key(target::TargetDescriptor t) {
    t.artifact.reset();
    return t.toString();
}
std::string default_driver(const target::TargetDescriptor& t) {
    if (native_target(t)) return "g++";
    const std::string arch = t.arch == target::Arch::X64 ? "x86_64" :
        t.arch == target::Arch::AArch64 ? "aarch64" : t.arch == target::Arch::RISCV64 ? "riscv64" : "";
    if (!arch.empty() && t.os == target::OS::Linux) return arch + "-linux-gnu-g++";
    if (t.arch == target::Arch::X64 && t.os == target::OS::Windows) return "x86_64-w64-mingw32-g++";
    throw std::runtime_error("Set LYMAR_AOT_CXX to a target C++ driver/wrapper for " + target_key(t));
}
int run_driver(const std::vector<std::string>& arguments) {
    std::vector<const char*> argv;
    for (const auto& arg : arguments) argv.push_back(arg.c_str());
    argv.push_back(nullptr);
#ifdef _WIN32
    return static_cast<int>(_spawnvp(_P_WAIT, argv[0], argv.data()));
#else
    auto pid = fork();
    if (pid < 0) return -1;
    if (!pid) {
        execvp(argv[0], const_cast<char* const*>(argv.data()));
        _exit(127);
    }
    int status;
    while (waitpid(pid, &status, 0) < 0) { if (errno != EINTR) return -1; }
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
#endif
}
}

::fyra::BuildResult link_standalone_runtime(::fyra::BackendBuilder& backend,
    const FyraCompileOptions& options, const target::TargetDescriptor& target,
    const std::vector<std::string>& libraries) {
    ::fyra::BuildResult result;
    result.outputPath = options.output_file;
    result.kind = ::fyra::OutputKind::Executable;
    const char* override = std::getenv("LYMAR_AOT_RUNTIME");
    std::filesystem::path runtime;
    if (override && *override) runtime = override;
    else {
        const auto directory = compiler_directory();
        runtime = directory / "runtimes" / target_key(target) / "liblymar_aot.a";
        if (!std::filesystem::exists(runtime) && native_target(target)) runtime = directory / "liblymar_aot.a";
    }
    if (!std::filesystem::exists(runtime)) {
        result.errors.push_back("Missing standalone runtime for " + target_key(target) + ": " + runtime.string() +
            "; build it with scripts/build_aot_runtime.py using a target toolchain or set LYMAR_AOT_RUNTIME");
        return result;
    }
    const char* selection = std::getenv("LYMAR_AOT_LINKER");
    const std::string linker = selection && *selection ? selection : "auto";
    if (linker != "auto" && linker != "fyra" && linker != "driver") {
        result.errors.push_back("LYMAR_AOT_LINKER must be auto, fyra, or driver");
        return result;
    }
    if (linker != "driver") {
        backend.addStaticLibrary(runtime.string());
        auto internal = backend.emitExecutable(options.output_file);
        if (internal.success || linker == "fyra") return internal;
        std::string reason;
        for (const auto& error : internal.errors) reason += (reason.empty() ? "" : "; ") + error;
        result.warnings.push_back("Fyra internal linker cannot link this runtime: " + reason + "; using the target C++ driver");
    }
    const auto temporary = options.output_file + ".lymar-" +
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".o";
    struct RemoveTemporary {
        std::filesystem::path path;
        ~RemoveTemporary() { std::error_code error; std::filesystem::remove(path, error); }
    } remove_temporary{temporary};
    auto object = backend.emitObject(temporary);
    if (!object.success) return object;
    const char* driver = std::getenv("LYMAR_AOT_CXX");
    std::vector<std::string> command{driver && *driver ? driver : default_driver(target)};
    if (target.os == target::OS::Linux || target.os == target::OS::FreeBSD || target.os == target::OS::Android) {
        command.push_back("-no-pie");
        command.push_back("-Wl,-z,noexecstack");
    } else if (target.os == target::OS::MacOS) command.push_back("-Wl,-no_pie");
    command.push_back(temporary);
    command.insert(command.end(), libraries.begin(), libraries.end());
    command.insert(command.end(), {runtime.string(), "-o", options.output_file});
    auto status = run_driver(command);
    result.success = status == 0;
    if (!result.success) result.errors.push_back("Target driver failed (status " + std::to_string(status) +
        ") for " + target_key(target) + ": " + command[0] + "; runtime " + runtime.string());
    return result;
}
}
