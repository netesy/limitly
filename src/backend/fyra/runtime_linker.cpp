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
    // The system DLL import libraries mirror the -l flags the target driver
    // path passes (sokol window/GDI, winsock, D3D11/DXGI shader compiler) so
    // the self-contained image resolves the same symbols without a driver.
    const std::vector<std::string> wanted{"libstdc++.a", "libstdc++fs.a", "libwinpthread.a",
        "libmingwex.a", "libmsvcrt.a", "libmingw32.a",
        "libws2_32.a", "libgdi32.a", "libuser32.a", "libshell32.a", "libkernel32.a", "libopengl32.a",
        "libd3d11.a", "libdxgi.a", "libd3dcompiler.a"};
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
// Locate a static libffi archive for the target. The standalone runtime's FFI
// call path (lymarrt_ffi_call*/lymar_aot_foreign_call) is implemented on top of
// libffi, so the self-contained link needs the archive the same way the target
// driver path adds -lffi. Returns an empty path when no archive can be found;
// the internal link then fails with the unresolved ffi_* symbol and the caller
// falls back to the driver exactly as before.
std::filesystem::path libffi_archive(const target::TargetDescriptor& t) {
    namespace fs = std::filesystem;
    std::vector<fs::path> roots;
    if (const char* env = std::getenv("LYMAR_AOT_WINLIB"); env && *env) roots.emplace_back(env);
    if (t.os == target::OS::Windows) {
        const auto compiler = compiler_directory();
        roots.push_back(compiler);
        if (compiler.has_parent_path()) roots.push_back(compiler.parent_path());
        roots.emplace_back("C:/msys64/mingw64/lib");
        for (const auto& root : roots) {
            std::error_code ec;
            const auto candidate = root / "libffi.a";
            if (fs::exists(candidate, ec)) return candidate;
        }
    } else if (t.os == target::OS::Linux || t.os == target::OS::FreeBSD || t.os == target::OS::Android) {
        roots = {"/usr/lib/x86_64-linux-gnu", "/usr/lib64", "/usr/lib", "/usr/local/lib"};
        for (const auto& root : roots) {
            std::error_code ec;
            const auto candidate = root / "libffi.a";
            if (fs::exists(candidate, ec)) return candidate;
        }
    }
    return {};
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
    // "auto" (and "fyra") always try the internal linker first — including
    // Windows GUI builds, which now link correctly. On failure the code below
    // falls back to the target C++ driver, so this can only regress to the
    // previous behavior, never below it.
    if (linker != "driver") {
        // GUI-subsystem executables (std.gg/ui/game/d3/... in the module
        // graph) get PE subsystem 2 instead of the default console one.
        // LYMAR_CONSOLE=1 forces the console subsystem for debugging: stderr
        // stays visible while all other GUI linking behavior is unchanged.
        const bool console_override = [] {
            const char* v = std::getenv("LYMAR_CONSOLE");
            return v && *v && v[0] != '0';
        }();
        if (options.gui_app && !console_override) {
            backend.peSubsystem(2);
            // aot_runtime.o references aot_gfx_create weakly so console builds
            // skip aot_graphics.o (sokol/truetype/d3d11). GUI builds seed the
            // symbol as a strong undefined reference so archive extraction
            // pulls the graphics member and its backend objects.
            backend.addUndefinedSymbol("aot_gfx_create");
        }
        backend.addStaticLibrary(runtime.string());
        // Contribute the target C/C++ runtime archives so the self-contained
        // Fyra image links without an external driver on Windows.
        if (target.os == target::OS::Windows)
            for (const auto& syslib : windows_runtime_libraries()) backend.addStaticLibrary(syslib);
        // Stale runtime archives built before libffi absorption still resolve
        // ffi_* through a located static libffi archive; new archives already
        // satisfy those symbols internally so this contributes nothing.
        if (const auto ffi = libffi_archive(target); !ffi.empty())
            backend.addStaticLibrary(ffi.string());
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
        // Static libstdc++/libgcc members carry DWARF that the PE linker
        // cannot map into sections: ~1.8MB lands as a headerless overlay plus
        // ~0.3MB of named .debug_* sections. Lymar codegen emits no debug info
        // of its own, so the only debug data in the image is this unusable
        // archive baggage — strip it unconditionally. --strip-debug alone is
        // NOT enough: it removes the named sections but leaves the overlay.
        if (!std::getenv("LYMAR_KEEP_SYMBOLS")) command.push_back("-Wl,--strip-all");
        const bool console_override = [] {
            const char* v = std::getenv("LYMAR_CONSOLE");
            return v && *v && v[0] != '0';
        }();
        if (options.gui_app) {
            // aot_runtime.o references aot_gfx_create weakly so console builds
            // skip aot_graphics.o (sokol/truetype/d3d11). GUI builds seed the
            // symbol here to force the archive member — and its backend
            // objects — to be extracted. This must stay unconditional for GUI
            // programs: LYMAR_CONSOLE only swaps the PE subsystem below, it
            // must not drop graphics extraction or resource type 17 fails.
            command.push_back("-Wl,-u,aot_gfx_create");
            if (!console_override) command.push_back("-mwindows");
        }
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
        command.insert(command.end(), {"-lws2_32", "-lgdi32", "-luser32", "-lshell32", "-lopengl32",
                                       "-ld3d11", "-ldxgi", "-ld3dcompiler"});
    command.insert(command.end(), {"-o", options.output_file});
    if (std::getenv("LYMAR_DEBUG_LINK")) {
        std::string cmdline;
        for (const auto& c : command) { cmdline += c; cmdline += ' '; }
        std::cerr << "[link-cmd] " << cmdline << "\n";
    }
    auto status = run_driver(command);
    result.success = status == 0;
    if (!result.success) result.errors.push_back("Target driver failed (status " + std::to_string(status) +
        ") for " + target_key(target) + ": " + command[0] + "; runtime " + runtime.string());
    return result;
}
}
