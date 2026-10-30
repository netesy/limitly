#include "runtime_linker.hh"
#include <algorithm>
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
// Locate the target C/C++ runtime archives that a self-contained Windows image
// needs. The Fyra internal linker never calls an external driver, but the Lymar
// runtime archive is compiled against the standard C++ library and the MinGW C
// runtime, so those archives must be contributed to the link for the produced
// image to resolve without falling back to a host toolchain. The search root is
// configurable through LYMAR_AOT_WINLIB so a cross sysroot can be supplied.
std::vector<std::string> windows_runtime_libraries() {
    namespace fs = std::filesystem;
    std::vector<fs::path> roots;
    if (const char* env = std::getenv("LYMAR_AOT_WINLIB"); env && *env) roots.emplace_back(env);
    const auto compiler = compiler_directory();
    roots.push_back(compiler);
    if (compiler.has_parent_path()) roots.push_back(compiler.parent_path());
    roots.emplace_back("C:/msys64/mingw64/lib");
    // Keep the archive order stable and independent of the caller environment.
    const std::vector<std::string> wanted{"libstdc++.a", "libstdc++fs.a", "libwinpthread.a",
        "libmingwex.a", "libmsvcrt.a", "libmingw32.a"};
    std::vector<std::string> found;
    std::vector<std::string> seen;
    auto consider = [&](const fs::path& candidate) {
        std::error_code check;
        if (!fs::exists(candidate, check)) return;
        const std::string absolute = fs::weakly_canonical(candidate, check).string();
        if (std::find(seen.begin(), seen.end(), absolute) == seen.end()) {
            seen.push_back(absolute);
            found.push_back(absolute);
        }
    };
    for (const auto& root : roots) {
        std::error_code ec;
        if (!fs::is_directory(root, ec)) continue;
        for (const auto& name : wanted) consider(root / name);
    }
    // The static GCC runtime (unwinder, __emutls, __floattidf, ___chkstk_ms) is
    // not in the top-level lib directory; it lives under lib/gcc/<triple>/<ver>/.
    // A self-contained link needs these static members because there is no
    // external driver to add them implicitly the way the compiler driver would.
    const std::vector<std::string> gccStatics{"libgcc.a", "libgcc_eh.a"};
    for (const auto& libRoot : {compiler.parent_path() / "lib", fs::path("C:/msys64/mingw64/lib")}) {
        std::error_code ec;
        if (!fs::is_directory(libRoot, ec)) continue;
        const auto gccDir = libRoot / "gcc";
        if (!fs::is_directory(gccDir, ec)) continue;
        std::error_code itec;
        for (auto rit = fs::recursive_directory_iterator(gccDir, fs::directory_options::skip_permission_denied, itec);
             !itec && rit != fs::recursive_directory_iterator(); rit.increment(itec)) {
            std::error_code isf;
            if (!rit->is_regular_file(isf) || isf) continue;
            const std::string fname = rit->path().filename().string();
            if (std::find(gccStatics.begin(), gccStatics.end(), fname) != gccStatics.end())
                consider(rit->path());
        }
    }
    return found;
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
        // Contribute the target C/C++ runtime archives so the self-contained
        // Fyra image links without an external driver on Windows.
        if (target.os == target::OS::Windows)
            for (const auto& syslib : windows_runtime_libraries()) backend.addStaticLibrary(syslib);
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
    if (target.os == target::OS::Linux || target.os == target::OS::FreeBSD || target.os == target::OS::Android || target.os == target::OS::MacOS)
        command.push_back("-pthread");
    if (target.os == target::OS::Windows) {
        command.push_back("-static-libgcc");
        command.push_back("-static-libstdc++");
    }
    command.push_back(temporary);
    // Foreign toolchain objects (roadmap item 2a) sit next to the program
    // object so the driver resolves program references against them, and
    // any extra libraries they need follow after the archive ordering.
    command.insert(command.end(), options.native_objects.begin(), options.native_objects.end());
    command.insert(command.end(), libraries.begin(), libraries.end());
    command.push_back(runtime.string());
    command.insert(command.end(), options.native_link_libs.begin(), options.native_link_libs.end());
    if(target.os!=target::OS::WASI) {
        command.push_back("-lffi");
        if(target.os!=target::OS::Windows && target.os!=target::OS::MacOS) command.push_back("-ldl");
    }
    // The standalone runtime archive bundles the sokol application member on
    // demand; when a program reaches it, the Windows system libraries that
    // supply its GDI/user-interface symbols must be linked explicitly. The
    // interpreter build obtains these through the host link, but the
    // target-driver path only receives program and runtime archives.
    if (target.os == target::OS::Windows)
        command.insert(command.end(), {"-lws2_32", "-lgdi32", "-luser32", "-lshell32", "-lopengl32"});
    command.insert(command.end(), {"-o", options.output_file});
    auto status = run_driver(command);
    result.success = status == 0;
    if (!result.success) result.errors.push_back("Target driver failed (status " + std::to_string(status) +
        ") for " + target_key(target) + ": " + command[0] + "; runtime " + runtime.string());
    return result;
}
}
