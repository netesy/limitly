#include <cerrno>
#include <cwchar>
#include <iterator>

#include "os_info.hh"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#if defined(_WIN32)
    #include <winsock2.h>
    #include <windows.h>
    #include <process.h>
    #else
    #include <unistd.h>
    #if defined(__APPLE__)
        #include <sys/resource.h>
        #include <crt_externs.h>
        #include <mach-o/dyld.h>
    #elif defined(__linux__) || defined(__FreeBSD__)
        #include <sys/resource.h>
    #endif
    #include <sys/types.h>
    #include <sys/wait.h>
#endif

// POSIX exposes the environment block as `environ`; Darwin only reliably
// exposes the accessor, and WASI has no process environment at all.
#if !defined(_WIN32) && !defined(__wasi__)
#if defined(__APPLE__)
    #define LYMAR_ENVIRON (*_NSGetEnviron())
#else
extern char** environ;
    #define LYMAR_ENVIRON environ
#endif
#endif

namespace LM {
namespace Runtime {
namespace OS {

namespace {

#if defined(_WIN32)
// The Win32 wide APIs are used throughout so that paths and variable values
// containing non-ASCII characters survive; Lymar strings are UTF-8.
std::string wide_to_utf8(const wchar_t* text, int length) {
    if (!text || length <= 0) return {};
    int size = WideCharToMultiByte(CP_UTF8, 0, text, length, nullptr, 0, nullptr, nullptr);
    if (size <= 0) return {};
    std::string out(static_cast<size_t>(size), '\0');
    WideCharToMultiByte(CP_UTF8, 0, text, length, out.data(), size, nullptr, nullptr);
    // WideCharToMultiByte reports the trailing NUL for length == -1 inputs.
    if (!out.empty() && out.back() == '\0') out.pop_back();
    return out;
}

std::wstring utf8_to_wide(const std::string& text) {
    if (text.empty()) return {};
    int size = MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), nullptr, 0);
    if (size <= 0) return {};
    std::wstring out(static_cast<size_t>(size), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), out.data(), size);
    return out;
}

std::string win_env(const wchar_t* key) {
    wchar_t buffer[4096];
    DWORD n = GetEnvironmentVariableW(key, buffer, static_cast<DWORD>(std::size(buffer)));
    if (n == 0 || n >= std::size(buffer)) return {};
    return wide_to_utf8(buffer, static_cast<int>(n));
}
#endif

// Native command line of this process. Only used when nothing set the program
// arguments explicitly, i.e. inside a standalone AOT executable whose entry
// point receives no argv.
std::vector<std::string> native_argv() {
    std::vector<std::string> out;
#if defined(_WIN32)
    // CommandLineToArgvW lives in shell32, which is not linked by every AOT
    // toolchain, so the same MSVC CRT splitting rules are applied here:
    // 2n backslashes before a quote yield n backslashes and toggle quoting,
    // 2n+1 yield n backslashes plus a literal quote, whitespace separates
    // arguments unless it is quoted.
    const wchar_t* line = GetCommandLineW();
    if (!line) return out;
    const size_t count = std::wcslen(line);
    size_t index = 0;
    while (index < count) {
        while (index < count && (line[index] == L' ' || line[index] == L'\t')) ++index;
        if (index >= count) break;
        std::wstring current;
        bool quoting = false;
        while (index < count) {
            size_t backs = 0;
            while (index < count && line[index] == L'\\') { ++backs; ++index; }
            if (index < count && line[index] == L'"') {
                // An even run of backslashes makes the quote a quoting
                // character; an odd run escapes one literal quote instead, and
                // that escaped quote never changes the quoting state.
                current.append(backs / 2, L'\\');
                if (backs % 2 == 0) quoting = !quoting;
                else current.push_back(L'"');
                ++index;
                continue;
            }
            current.append(backs, L'\\');
            if (index >= count) break;
            if (!quoting && (line[index] == L' ' || line[index] == L'\t')) break;
            current.push_back(line[index]);
            ++index;
        }
        out.push_back(wide_to_utf8(current.c_str(), static_cast<int>(current.size())));
    }
#elif defined(__linux__)
    std::FILE* f = std::fopen("/proc/self/cmdline", "rb");
    if (!f) return out;
    std::string blob;
    char chunk[4096];
    size_t read = 0;
    while ((read = std::fread(chunk, 1, sizeof(chunk), f)) > 0) blob.append(chunk, read);
    std::fclose(f);
    size_t start = 0;
    while (start < blob.size()) {
        size_t end = blob.find('\0', start);
        if (end == std::string::npos) end = blob.size();
        if (end > start) out.push_back(blob.substr(start, end - start));
        start = end + 1;
    }
#endif
    return out;
}

std::string native_executable_path() {
#if defined(_WIN32)
    wchar_t buffer[4096];
    DWORD n = GetModuleFileNameW(nullptr, buffer, static_cast<DWORD>(std::size(buffer)));
    if (n == 0 || n >= std::size(buffer)) return {};
    return wide_to_utf8(buffer, static_cast<int>(n));
#elif defined(__linux__)
    char buffer[4096];
    ssize_t n = ::readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (n <= 0) return {};
    buffer[n] = '\0';
    return std::string(buffer);
#elif defined(__APPLE__)
    char buffer[4096];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) != 0) return {};
    return std::string(buffer);
#else
    return {};
#endif
}

} // namespace

// ===================== Environment =====================

bool env_lookup(const std::string& key, std::string& out) {
    if (key.empty()) return false;
#if defined(_WIN32)
    auto wide_key = utf8_to_wide(key);
    if (wide_key.empty()) return false;
    std::vector<wchar_t> buffer(512);
    for (int attempt = 0; attempt < 8; ++attempt) {
        DWORD n = GetEnvironmentVariableW(wide_key.c_str(), buffer.data(), static_cast<DWORD>(buffer.size()));
        if (n == 0) return false;  // unset, or empty value with a zero-length result
        if (n < buffer.size()) {
            // GetEnvironmentVariableW reports the required length excluding the
            // NUL, so an empty request means the variable exists but holds "".
            out = wide_to_utf8(buffer.data(), static_cast<int>(n));
            return true;
        }
        buffer.assign(static_cast<size_t>(n) + 1, L'\0');
    }
    return false;
#else
    const char* value = std::getenv(key.c_str());
    if (!value) return false;
    out = value;
    return true;
#endif
}

std::string env_get(const std::string& key) {
    std::string value;
    return env_lookup(key, value) ? value : std::string();
}

bool env_set(const std::string& key, const std::string& value) {
    if (key.empty() || key.find('=') != std::string::npos) return false;
#if defined(_WIN32)
    // Win32 has no representation for a variable that exists but holds "":
    // SetEnvironmentVariableW removes the variable when the value is empty. So
    // on Windows "set to empty" means "unset", unlike POSIX setenv(key, "", 1).
    return SetEnvironmentVariableW(utf8_to_wide(key).c_str(), utf8_to_wide(value).c_str()) != 0;
#elif defined(__wasi__)
    (void)value; return false;
#else
    return ::setenv(key.c_str(), value.c_str(), 1) == 0;
#endif
}

bool env_unset(const std::string& key) {
    if (key.empty()) return false;
#if defined(_WIN32)
    return SetEnvironmentVariableW(utf8_to_wide(key).c_str(), nullptr) != 0;
#elif defined(__wasi__)
    (void)key; return false;
#else
    return ::unsetenv(key.c_str()) == 0;
#endif
}

std::vector<std::string> env_list() {
    std::vector<std::string> out;
#if defined(_WIN32)
    wchar_t* block = GetEnvironmentStringsW();
    if (!block) return out;
    for (const wchar_t* entry = block; *entry;) {
        std::wstring text(entry);
        // Entries such as "=C::C:\Windows" are drive-current-directory
        // bookkeeping kept by the CRT; they are not real variables.
        if (!text.empty() && text.front() != L'=') {
            auto utf8 = wide_to_utf8(text.c_str(), static_cast<int>(text.size()));
            if (!utf8.empty()) out.push_back(utf8);
        }
        entry += text.size() + 1;
    }
    FreeEnvironmentStringsW(block);
#else
    for (char** it = LYMAR_ENVIRON; it && *it; ++it) {
        std::string entry(*it);
        // A zero-length name is not a usable variable.
        if (!entry.empty() && entry.front() != '=') out.push_back(entry);
    }
#endif
    return out;
}

// ===================== Working directory =====================

std::string cwd() {
#if defined(_WIN32)
    wchar_t buffer[4096];
    DWORD n = GetCurrentDirectoryW(static_cast<DWORD>(std::size(buffer)), buffer);
    if (n == 0 || n >= std::size(buffer)) return {};
    return wide_to_utf8(buffer, static_cast<int>(n));
#elif defined(__wasi__)
    return {};
#else
    char buffer[4096];
    if (!::getcwd(buffer, sizeof(buffer))) return {};
    return std::string(buffer);
#endif
}

bool chdir_to(const std::string& path) {
    if (path.empty()) return false;
#if defined(_WIN32)
    return SetCurrentDirectoryW(utf8_to_wide(path).c_str()) != 0;
#elif defined(__wasi__)
    (void)path; return false;
#else
    return ::chdir(path.c_str()) == 0;
#endif
}

// ===================== Well-known directories =====================

std::string home_dir() {
#if defined(_WIN32)
    auto profile = win_env(L"USERPROFILE");
    if (!profile.empty()) return profile;
    auto drive = win_env(L"HOMEDRIVE"), leaf = win_env(L"HOMEPATH");
    if (!drive.empty() && !leaf.empty()) return drive + leaf;
    return {};
#else
    auto home = env_get("HOME");
    return home;
#endif
}

std::string temp_dir() {
#if defined(_WIN32)
    auto temp = win_env(L"TEMP");
    if (!temp.empty()) return temp;
    temp = win_env(L"TMP");
    if (!temp.empty()) return temp;
    wchar_t buffer[4096];
    DWORD n = GetTempPathW(static_cast<DWORD>(std::size(buffer)), buffer);
    if (n == 0 || n >= std::size(buffer)) return {};
    return wide_to_utf8(buffer, static_cast<int>(n));
#else
    auto temp = env_get("TMPDIR");
    return !temp.empty() ? temp : std::string("/tmp");
#endif
}

std::string exe_path() { return native_executable_path(); }

// ===================== Machine identity =====================

std::string os_name() {
#if defined(_WIN32)
    return "windows";
#elif defined(__APPLE__)
    return "darwin";
#elif defined(__ANDROID__)
    return "android";
#elif defined(__linux__)
    return "linux";
#elif defined(__FreeBSD__)
    return "freebsd";
#elif defined(__wasi__)
    return "wasi";
#else
    return "unknown";
#endif
}

std::string arch() {
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(__i386__) || defined(_M_IX86)
    return "i686";
#elif defined(__aarch64__) || defined(_M_ARM64)
    return "aarch64";
#elif defined(__arm__) || defined(_M_ARM)
    return "arm";
#elif defined(__riscv) && __riscv_xlen == 64
    return "riscv64";
#elif defined(__wasm64__)
    return "wasm64";
#elif defined(__wasm32__) || defined(__wasi__)
    return "wasm32";
#else
    return "unknown";
#endif
}

std::string hostname() {
#if defined(_WIN32)
    wchar_t buffer[256];
    DWORD n = static_cast<DWORD>(std::size(buffer));
    if (!GetComputerNameW(buffer, &n) || n == 0) return {};
    return wide_to_utf8(buffer, static_cast<int>(n));
#elif defined(__wasi__)
    return {};
#else
    char buffer[256];
    if (::gethostname(buffer, sizeof(buffer) - 1) != 0) return {};
    buffer[sizeof(buffer) - 1] = '\0';
    return std::string(buffer);
#endif
}

int64_t num_cpu() {
#if defined(_WIN32)
    SYSTEM_INFO info{};
    GetSystemInfo(&info);
    return static_cast<int64_t>(info.dwNumberOfProcessors);
#elif defined(__wasi__)
    return 1;
#else
    long n = ::sysconf(_SC_NPROCESSORS_ONLN);
    return n > 0 ? static_cast<int64_t>(n) : 1;
#endif
}

// ===================== Process =====================

int64_t pid() {
#if defined(_WIN32)
    return static_cast<int64_t>(GetCurrentProcessId());
#elif defined(__wasi__)
    return 0;
#else
    return static_cast<int64_t>(::getpid());
#endif
}

namespace {
#if defined(_WIN32)
// PROCESS_MEMORY_COUNTERS: a DWORD size followed by eight SIZE_T counters.
// K32GetProcessMemoryInfo is exported by kernel32 on Vista and later, so it is
// resolved dynamically to avoid a psapi link dependency in every toolchain.
struct WinProcessMemoryCounters {
    DWORD cb;
    size_t working_set;
    size_t peak_working_set;
    size_t quota_peak_paged_pool;
    size_t quota_paged_pool;
    size_t quota_peak_non_paged_pool;
    size_t quota_non_paged_pool;
    size_t pagefile_usage;
    size_t peak_pagefile_usage;
};

int64_t windows_working_set_kb(bool peak) {
    using MemoryInfoFn = BOOL(WINAPI*)(HANDLE, void*, DWORD);
    static MemoryInfoFn query = []() -> MemoryInfoFn {
        HMODULE module = GetModuleHandleA("kernel32.dll");
        if (!module) module = LoadLibraryA("kernel32.dll");
        if (!module) return nullptr;
        return reinterpret_cast<MemoryInfoFn>(GetProcAddress(module, "K32GetProcessMemoryInfo"));
    }();
    if (!query) return -1;
    WinProcessMemoryCounters counters{};
    counters.cb = sizeof(counters);
    if (!query(GetCurrentProcess(), &counters, sizeof(counters))) return -1;
    size_t bytes = peak ? counters.peak_working_set : counters.working_set;
    return static_cast<int64_t>(bytes / 1024);
}
#endif
} // namespace

int64_t rss_kb() {
#if defined(_WIN32)
    return windows_working_set_kb(false);
#elif defined(__linux__)
    // statm field 2 is the resident page count.
    std::FILE* f = std::fopen("/proc/self/statm", "rb");
    if (!f) return -1;
    long total = 0, resident = 0;
    int scanned = std::fscanf(f, "%ld %ld", &total, &resident);
    std::fclose(f);
    if (scanned != 2 || resident <= 0) return -1;
    long page = ::sysconf(_SC_PAGESIZE);
    if (page <= 0) page = 4096;
    return static_cast<int64_t>(resident * page / 1024);
#elif defined(__APPLE__) || defined(__FreeBSD__)
    // No portable per-process current-RSS call without Mach APIs; max RSS is
    // the closest value getrusage exposes and peak_rss_kb() reports it too.
    struct ::rusage usage{};
    if (::getrusage(RUSAGE_SELF, &usage) != 0) return -1;
#if defined(__APPLE__)
    return static_cast<int64_t>(usage.ru_maxrss / 1024);  // bytes on Darwin
#else
    return static_cast<int64_t>(usage.ru_maxrss);          // kilobytes on FreeBSD
#endif
#else
    return -1;
#endif
}

int64_t peak_rss_kb() {
#if defined(_WIN32)
    return windows_working_set_kb(true);
#elif defined(__linux__)
    std::FILE* f = std::fopen("/proc/self/status", "rb");
    if (!f) return -1;
    char line[256];
    int64_t peak = -1;
    while (std::fgets(line, sizeof(line), f)) {
        // VmHWM is the high-water mark already expressed in kB.
        if (std::strncmp(line, "VmHWM:", 6) == 0) {
            peak = std::atoll(line + 6);
            break;
        }
    }
    std::fclose(f);
    return peak;
#elif defined(__APPLE__) || defined(__FreeBSD__)
    struct ::rusage usage{};
    if (::getrusage(RUSAGE_SELF, &usage) != 0) return -1;
#if defined(__APPLE__)
    return static_cast<int64_t>(usage.ru_maxrss / 1024);
#else
    return static_cast<int64_t>(usage.ru_maxrss);
#endif
#else
    return -1;
#endif
}

int spawn_wait(const std::vector<std::string>& argv) {
    if (argv.empty()) return -1;
#if defined(_WIN32)
    std::vector<const char*> pointers;
    pointers.reserve(argv.size() + 1);
    for (const auto& argument : argv) pointers.push_back(argument.c_str());
    pointers.push_back(nullptr);
    int status = _spawnvp(_P_WAIT, pointers[0], const_cast<char* const*>(pointers.data()));
    return status;
#elif defined(__wasi__)
    return -1;
#else
    // Mirrors the fork/exec/waitpid idiom already used by the AOT driver
    // launcher, so behaviour matches across the compiler's own subprocess use.
    ::pid_t child = ::fork();
    if (child < 0) return -1;
    if (child == 0) {
        std::vector<char*> arguments;
        arguments.reserve(argv.size() + 1);
        for (const auto& argument : argv) arguments.push_back(const_cast<char*>(argument.c_str()));
        arguments.push_back(nullptr);
        ::execvp(arguments[0], arguments.data());
        ::_exit(127);
    }
    int status = 0;
    while (::waitpid(child, &status, 0) < 0) {
        if (errno != EINTR) return -1;
    }
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) return 128 + WTERMSIG(status);
    return -1;
#endif
}

void terminate(int code) {
    // Flush buffered output first: _Exit bypasses atexit handlers and static
    // destructors, which also avoids re-entering the ResourceManager mutex that
    // is still held by the resource call performing the exit.
    std::fflush(nullptr);
    // POSIX can only report eight bits to a parent, so the mask is applied on
    // every platform to keep the observable code identical.
    std::_Exit(static_cast<int>(static_cast<unsigned>(code) & 0xffu));
}

// ===================== Program arguments =====================

namespace {
struct ProgramArguments {
    bool explicit_cli = false;
    std::string command;
    std::vector<std::string> arguments;
};

ProgramArguments& program_state() {
    static ProgramArguments state;
    return state;
}
} // namespace

void set_program_arguments(const std::string& command, const std::vector<std::string>& args) {
    auto& state = program_state();
    state.explicit_cli = true;
    state.command = command;
    state.arguments = args;
}

std::string command_name() {
    auto& state = program_state();
    if (state.explicit_cli) return state.command;
    auto native = native_argv();
    return native.empty() ? std::string() : native.front();
}

std::vector<std::string> program_arguments() {
    auto& state = program_state();
    if (state.explicit_cli) return state.arguments;
    auto native = native_argv();
    // argv[0] is the program itself, which is command_name(), not an argument.
    if (native.empty()) return {};
    return std::vector<std::string>(native.begin() + 1, native.end());
}

} // namespace OS
} // namespace Runtime
} // namespace LM
