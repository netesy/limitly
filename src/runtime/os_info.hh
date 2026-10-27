#ifndef LYMAR_RUNTIME_OS_INFO_H
#define LYMAR_RUNTIME_OS_INFO_H

// Platform/environment services shared by every backend.
//
// The RegisterVM and the standalone AOT runtime both expose these facts through
// the OS (ResourceType::OS) and PROCESS (ResourceType::PROCESS) resources. They
// call into this single implementation so the two backends cannot drift apart:
// an operation that reports a different value per backend would break the
// backend-conformance rule in AGENTS.md.

#include <cstdint>
#include <string>
#include <vector>

namespace LM {
namespace Runtime {
namespace OS {

// Ambient machine and environment facts (ResourceType::OS).
// Distinguishes "set but empty" from "unset", which env_get cannot.
bool env_lookup(const std::string& key, std::string& out);
std::string env_get(const std::string& key);
bool env_set(const std::string& key, const std::string& value);
bool env_unset(const std::string& key);
// Each entry is "KEY=VALUE".
std::vector<std::string> env_list();
std::string cwd();
bool chdir_to(const std::string& path);
std::string home_dir();
std::string temp_dir();
std::string exe_path();
// "windows" | "linux" | "darwin" | "freebsd" | "wasi" | "unknown"
std::string os_name();
// "x86_64" | "aarch64" | "riscv64" | "i686" | "wasm32" | "unknown"
std::string arch();
std::string hostname();
int64_t num_cpu();

// Process identity and lifecycle (ResourceType::PROCESS).
int64_t pid();
// Current resident set size in kilobytes, or -1 when the platform cannot report it.
int64_t rss_kb();
// Peak resident set size in kilobytes, or -1 when unavailable.
int64_t peak_rss_kb();
// Run `argv` directly (no shell) and wait; returns the child exit code, or -1
// when the child could not be started.
int spawn_wait(const std::vector<std::string>& argv);
// Terminate this process with `code`. Flushes stdio but deliberately skips
// static destructors and frame deinitializers, mirroring Go's os.Exit.
void terminate(int code);

// Program arguments. The interpreter reports the arguments the CLI handed to
// the script (see Compiler::executeFile); a standalone AOT executable falls
// back to its own native argv because nothing sets these.
void set_program_arguments(const std::string& command, const std::vector<std::string>& args);
std::string command_name();
std::vector<std::string> program_arguments();

} // namespace OS
} // namespace Runtime
} // namespace LM

#endif // LYMAR_RUNTIME_OS_INFO_H
