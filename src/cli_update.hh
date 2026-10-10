#pragma once
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cerrno>
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#include "backend/native/process_arguments.hh"
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

inline int update_lymar(int argc, char** argv) {
    namespace fs = std::filesystem;
    std::vector<fs::path> homes;
    if (const char* home = std::getenv("LYMAR_HOME")) homes.emplace_back(home);
    fs::path executable = fs::absolute(argv[0]);
#ifdef _WIN32
    char buffer[32768];
    DWORD length = GetModuleFileNameA(nullptr, buffer, sizeof(buffer));
    if (length && length < sizeof(buffer)) executable = std::string(buffer, length);
#elif defined(__linux__)
    std::error_code ec;
    auto actual = fs::read_symlink("/proc/self/exe", ec);
    if (!ec) executable = actual;
#else
    if (!fs::exists(executable)) {
        if (const char* path = std::getenv("PATH")) {
            std::string paths(path); size_t start = 0;
            while (start <= paths.size()) {
                auto end = paths.find(':', start);
                auto candidate = fs::path(paths.substr(start, end - start)) / argv[0];
                if (fs::exists(candidate)) { executable = fs::absolute(candidate); break; }
                if (end == std::string::npos) break;
                start = end + 1;
            }
        }
    }
#endif
    homes.push_back(executable.parent_path().parent_path());
    fs::path script;
    for (const auto& home : homes)
        if (fs::is_regular_file(home / "scripts/update.py")) { script = home / "scripts/update.py"; break; }
    if (script.empty()) {
        std::cerr << "Updater missing: install a complete Lymar distribution including scripts/update.py\n";
        return 1;
    }
#ifdef _WIN32
    std::string python = "python";
#else
    std::string python = "python3";
#endif
    std::vector<std::string> arguments{python, script.string(), "--current-home", script.parent_path().parent_path().string()};
    for (int i = 2; i < argc; ++i) arguments.emplace_back(argv[i]);
#ifdef _WIN32
    for (auto& argument : arguments) argument = LM::Backend::Native::quote_windows_argument(argument);
#endif
    std::vector<char*> pointers;
    for (auto& argument : arguments) pointers.push_back(argument.data());
    pointers.push_back(nullptr);
#ifdef _WIN32
    auto status = _spawnvp(_P_WAIT, python.c_str(), pointers.data());
    if (status < 0) std::cerr << "lymar up requires Python 3 on PATH\n";
    return status < 0 ? 1 : static_cast<int>(status);
#else
    auto pid = fork();
    if (pid == 0) { execvp(python.c_str(), pointers.data()); std::cerr << "lymar up requires Python 3 on PATH\n"; _exit(127); }
    if (pid < 0) return 1;
    int status;
    while (waitpid(pid, &status, 0) < 0) if (errno != EINTR) return 1;
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
#endif
}
