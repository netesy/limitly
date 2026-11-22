// cheader_import.cpp - Implementation of the C header import resolution pipeline.
// Reuses the existing 2b header_parser + binding_generator to produce importable
// .lm modules from `import "c:<header>" [from "<lib>"] ...` statements.

#include "cheader_import.hh"
#include "../backend/native/header_parser.hh"
#include "../backend/native/binding_generator.hh"

#include <algorithm>
#include <cstdint>
#include <cstdio>
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
static std::vector<std::string> g_c_import_link_libs;

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

void register_c_import_link_lib(const std::string& lib_path) {
    if (std::find(g_c_import_link_libs.begin(), g_c_import_link_libs.end(), lib_path)
        == g_c_import_link_libs.end()) {
        g_c_import_link_libs.push_back(lib_path);
    }
}

const std::vector<std::string>& c_import_link_libs() {
    return g_c_import_link_libs;
}

std::string resolve_c_header_import(
    const std::string& header_path,
    const std::optional<std::string>& from_lib,
    const std::vector<std::string>& include_dirs,
    const CHeaderFilter& filter,
    const std::string& namespace_alias,
    std::string& error) {

    // Register the link library up front: cached binding reuse returns before
    // generation, but AOT still needs the lib on the link line.
    if (from_lib.has_value() && !from_lib->empty()) {
        register_c_import_link_lib(*from_lib);
    }

    // 1. Locate the header
    std::string resolved = locate_header(header_path, include_dirs);
    if (resolved.empty()) {
        error = "cannot find C header '" + header_path + "' in include paths";
        return "";
    }

    // 2. Read and parse the header. This runs even on binding-cache hits:
    // the direct-call signature registry must be populated on every resolve
    // so AOT call sites can bypass generated wrappers.
    std::ifstream hdr_file(resolved);
    if (!hdr_file.is_open()) {
        error = "cannot read C header '" + resolved + "'";
        return "";
    }
    std::stringstream ss;
    ss << hdr_file.rdbuf();
    std::string source = ss.str();
    hdr_file.close();

    // 3. Parse function declarations and enum constants
    std::vector<std::string> warnings;
    std::vector<Backend::Native::CConstantDecl> constants;
    auto decls = Backend::Native::parse_header(source, resolved, warnings, &constants);

    // 4. Filter by symbol names if requested
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

    // Publish direct-call signatures for AOT wrapper bypass (cache hits too).
    Backend::Native::register_c_direct_signatures(namespace_alias, decls);

    // 5. Check cache: if the binding .lm exists, is newer than the header, and
    // was generated from THIS header, reuse it. The alias-only filename means
    // two different headers imported `as vk` would otherwise share stale
    // bindings, so the source path is stamped into the file and verified.
    fs::path bind_dir = ".cache/bindings";
    fs::path out_path = bind_dir / (namespace_alias + ".lm");
    std::error_code ec;
    fs::create_directories(bind_dir, ec);

    if (fs::exists(out_path, ec)) {
        auto hdr_time = fs::last_write_time(resolved, ec);
        auto bind_time = fs::last_write_time(out_path, ec);
        bool source_matches = false;
        {
            std::ifstream chk(out_path);
            std::string first;
            std::getline(chk, first);
            source_matches = first == "// c-import-source: " + resolved;
        }
        if (!ec && bind_time >= hdr_time && source_matches && filter.identifiers.empty()) {
            // Cached and header hasn't changed: reuse (skip cache when filtered)
            return out_path.string();
        }
    }

    // 7. Generate bindings (also re-registers direct signatures)
    std::string lib_path = from_lib.value_or("");
    std::string gen_source = Backend::Native::generate_bindings(decls, constants, namespace_alias, lib_path);
    gen_source = "// c-import-source: " + resolved + "\n" + gen_source;

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
