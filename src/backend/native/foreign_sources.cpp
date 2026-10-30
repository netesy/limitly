// foreign_sources.cpp - Native toolchain compilation of foreign .c/.cpp
// sources (roadmap item 2a). Mirrors the toolchain usage in
// scripts/build_aot_runtime.py: the driver compiles each source to a
// position-independent object file, and the artifact link paths contribute
// those objects. Argument vectors are passed directly to the driver so no
// shell quoting layer is involved on Windows.

#include "foreign_sources.hh"
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
#endif

namespace LM::Backend::Native {
namespace {
std::string host_os() {
#if defined(_WIN32)
    return "windows";
#elif defined(__APPLE__)
    return "macos";
#else
    return "linux";
#endif
}
std::string host_arch() {
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(__aarch64__) || defined(_M_ARM64)
    return "aarch64";
#elif defined(__riscv) && __riscv_xlen == 64
    return "riscv64";
#else
    return "unknown";
#endif
}
// Same cross-prefix table the AOT runtime link stage uses, so a project
// compiled for a foreign target pulls a matching toolchain instead of the
// host compiler. The plain host names work on every supported native build.
std::string prefixed_driver(const std::string& base, const std::string& target,
                            const std::string& arch) {
    if (target == host_os() && arch == host_arch()) return base;
    if (arch != "x86_64" && arch != "aarch64" && arch != "riscv64") return base;
    const std::string arch_prefix = arch == "x86_64" ? "x86_64" : arch;
    if (target == "linux") return arch_prefix + "-linux-gnu-" + base;
    if (target == "windows") return arch_prefix + "-w64-mingw32-" + base;
    return base;
}
std::string select_driver(const char* env, const std::string& base,
                          const std::string& target, const std::string& arch) {
    if (const char* override_ = std::getenv(env); override_ && *override_) return override_;
    return prefixed_driver(base, target, arch);
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
} // namespace

std::vector<std::string> compile_foreign_sources(const std::vector<std::string>& sources,
                                                 const std::vector<std::string>& include_dirs,
                                                 const std::vector<std::string>& extra_cflags,
                                                 const std::string& output,
                                                 const std::string& target,
                                                 const std::string& arch) {
    std::vector<std::string> objects;
    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    // Objects live next to the artifact so the link stage and the driver see
    // the same filesystem the output is written to.
    std::filesystem::path directory = std::filesystem::path(output).parent_path();
    if (directory.empty()) directory = ".";
    size_t index = 0;
    for (const auto& source : sources) {
        std::error_code exists;
        if (!std::filesystem::exists(source, exists) || exists)
            throw std::runtime_error("Foreign native source does not exist: " + source);
        const bool is_c = std::filesystem::path(source).extension() == ".c";
        const std::string driver = is_c ? select_driver("LYMAR_AOT_CC", "gcc", target, arch)
                                        : select_driver("LYMAR_AOT_CXX", "g++", target, arch);
        std::vector<std::string> command{driver, "-O2", "-fPIC", "-c"};
        if (is_c) command.push_back("-std=c11");
        for (const auto& dir : include_dirs) command.push_back("-I" + dir);
        for (const auto& flag : extra_cflags) command.push_back(flag);
        command.push_back(source);
        const auto object = directory / (std::filesystem::path(output).stem().string() +
            ".lymar-native-" + std::to_string(stamp) + "-" + std::to_string(index++) + ".o");
        command.push_back("-o");
        command.push_back(object.string());
        const auto status = run_driver(command);
        if (status != 0) {
            std::error_code cleanup;
            std::filesystem::remove(object, cleanup);
            throw std::runtime_error("Native toolchain failed (status " + std::to_string(status) +
                ") compiling " + source + " with " + driver);
        }
        objects.push_back(object.string());
    }
    return objects;
}

void cleanup_foreign_objects(const std::vector<std::string>& objects) {
    for (const auto& object : objects) {
        std::error_code error;
        std::filesystem::remove(object, error);
    }
}

} // namespace LM::Backend::Native
