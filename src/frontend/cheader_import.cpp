// cheader_import.cpp - Implementation of the C header import resolution pipeline.
// Reuses the existing 2b header_parser + binding_generator to produce importable
// .lm modules from `import "c:<header>" [from "<lib>"] ...` statements.

#include "cheader_import.hh"
#include "../backend/native/header_parser.hh"
#include "../backend/native/binding_generator.hh"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>

namespace fs = std::filesystem;

namespace LM::Frontend {
namespace {

// Extra include dirs set by the CLI/driver before compilation begins.
// Stored here so the type checker can pass manifest paths without threading
// them through every call site.
static std::vector<std::string> g_extra_include_dirs;

// Detect system C include directories by probing well-known paths.
std::vector<std::string> detect_system_include_dirs() {
    std::vector<std::string> dirs;
#ifdef _WIN32
    // MinGW-w64 (msys64)
    const char* mingw_env = std::getenv("MINGW_INCLUDE_DIR");
    if (mingw_env) dirs.push_back(mingw_env);
    dirs.push_back("C:/msys64/mingw64/include");
    dirs.push_back("C:/msys64/mingw64/x86_64-w64-mingw32/include");
    // Detect from gcc if available
    {
        FILE* pipe = popen("gcc -E -Wp,-v -x c - -o NUL < NUL 2>&1", "r");
        if (pipe) {
            char buf[512];
            bool in_search = false;
            while (fgets(buf, sizeof(buf), pipe)) {
                std::string line(buf);
                if (line.find("#include <...> search") != std::string::npos) {
                    in_search = true; continue;
                }
                if (in_search) {
                    if (line.find("End of search") != std::string::npos) break;
                    // Trim whitespace
                    size_t start = line.find_first_not_of(" \t");
                    size_t end = line.find_last_not_of(" \t\r\n");
                    if (start != std::string::npos && end != std::string::npos)
                        dirs.push_back(line.substr(start, end - start + 1));
                }
            }
            pclose(pipe);
        }
    }
#else
    dirs.push_back("/usr/local/include");
    dirs.push_back("/usr/include");
    // Detect from gcc
    {
        FILE* pipe = popen("gcc -E -Wp,-v -x c - -o /dev/null < /dev/null 2>&1", "r");
        if (pipe) {
            char buf[512];
            bool in_search = false;
            while (fgets(buf, sizeof(buf), pipe)) {
                std::string line(buf);
                if (line.find("#include <...> search") != std::string::npos) {
                    in_search = true; continue;
                }
                if (in_search) {
                    if (line.find("End of search") != std::string::npos) break;
                    size_t start = line.find_first_not_of(" \t");
                    size_t end = line.find_last_not_of(" \t\r\n");
                    if (start != std::string::npos && end != std::string::npos)
                        dirs.push_back(line.substr(start, end - start + 1));
                }
            }
            pclose(pipe);
        }
    }
#endif
    // LYMAR_HOME/include
    if (const char* home = std::getenv("LYMAR_HOME")) {
        dirs.push_back(std::string(home) + "/include");
    }
    return dirs;
}

// Find the header file by searching through include dirs.
std::string locate_header(const std::string& header_path,
                          const std::vector<std::string>& include_dirs) {
    // Direct path (relative to cwd or absolute)
    if (fs::exists(header_path)) return fs::absolute(header_path).string();

    // Search include directories
    for (const auto& dir : include_dirs) {
        fs::path candidate = fs::path(dir) / header_path;
        if (fs::exists(candidate)) return candidate.string();
    }
    return "";
}

} // anonymous namespace

std::vector<std::string> collect_c_include_dirs() {
    auto dirs = detect_system_include_dirs();
    // Append any extra dirs set by the CLI driver
    dirs.insert(dirs.end(), g_extra_include_dirs.begin(), g_extra_include_dirs.end());
    return dirs;
}

// Called by the driver (main.cpp/lymar.cpp) to register manifest/CLI include dirs.
void set_c_header_extra_include_dirs(const std::vector<std::string>& dirs) {
    g_extra_include_dirs = dirs;
}

std::string resolve_c_header_import(
    const std::string& header_path,
    const std::optional<std::string>& from_lib,
    const std::vector<std::string>& include_dirs,
    const CHeaderFilter& filter,
    const std::string& namespace_alias,
    std::string& error) {

    // 1. Locate the header
    std::string resolved = locate_header(header_path, include_dirs);
    if (resolved.empty()) {
        error = "cannot find C header '" + header_path + "' in include paths";
        return "";
    }

    // 2. Check cache: if the binding .lm exists and is newer than the header, reuse it
    fs::path bind_dir = ".cache/bindings";
    fs::path out_path = bind_dir / (namespace_alias + ".lm");
    std::error_code ec;
    fs::create_directories(bind_dir, ec);

    if (fs::exists(out_path, ec)) {
        auto hdr_time = fs::last_write_time(resolved, ec);
        auto bind_time = fs::last_write_time(out_path, ec);
        if (!ec && bind_time >= hdr_time && filter.identifiers.empty()) {
            // Cached and header hasn't changed: reuse (skip cache when filtered)
            return out_path.string();
        }
    }

    // 3. Read the header source
    std::ifstream hdr_file(resolved);
    if (!hdr_file.is_open()) {
        error = "cannot read C header '" + resolved + "'";
        return "";
    }
    std::stringstream ss;
    ss << hdr_file.rdbuf();
    std::string source = ss.str();
    hdr_file.close();

    // 4. Parse function declarations
    std::vector<std::string> warnings;
    auto decls = Backend::Native::parse_header(source, resolved, warnings);

    // 5. Filter by symbol names if requested
    if (!filter.identifiers.empty()) {
        std::vector<Backend::Native::CFunctionDecl> filtered;
        for (const auto& d : decls) {
            if (std::find(filter.identifiers.begin(), filter.identifiers.end(), d.name)
                != filter.identifiers.end()) {
                filtered.push_back(d);
            }
        }
        decls = std::move(filtered);
    }

    if (decls.empty()) {
        error = "no function declarations found in '" + header_path + "'"
                + (filter.identifiers.empty() ? "" : " (after symbol filter)");
        return "";
    }

    // 6. Determine library path: from clause or empty string (system)
    std::string lib_path = from_lib.value_or("");

    // 7. Generate bindings
    std::string gen_source = Backend::Native::generate_bindings(decls, namespace_alias, lib_path);

    // 8. Write to cache
    std::ofstream ofs(out_path);
    if (!ofs.is_open()) {
        error = "cannot write binding module to '" + out_path.string() + "'";
        return "";
    }
    ofs << gen_source;
    ofs.close();

    return out_path.string();
}

} // namespace LM::Frontend
