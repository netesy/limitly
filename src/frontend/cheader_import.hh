// cheader_import.hh - Resolves `import "c:<header>" [from "<lib>"] ...` by
// running the existing header parser + binding generator pipeline at compile
// time and returning the path to the generated .lm module (roadmap item 2c).

#pragma once
#include <string>
#include <vector>
#include <optional>

namespace LM::Frontend {

// Minimal filter descriptor (avoids pulling full ast.hh into this TU).
struct CHeaderFilter {
    std::vector<std::string> identifiers; // if non-empty, only these are kept
};

// Resolve a c: scheme import:
//   1. Locate the header via include_dirs + system paths.
//   2. Parse function declarations using the existing 2b pipeline.
//   3. Optionally filter by symbol names.
//   4. Generate the binding .lm module.
//   5. Write to .cache/bindings/<ns>.lm (cached: skip if fresh).
//   6. Return the path to the written file, or "" on failure (error populated).
std::string resolve_c_header_import(
    const std::string& header_path,              // "c:" stripped
    const std::optional<std::string>& from_lib,  // "libmath_ops" or nullopt
    const std::vector<std::string>& include_dirs,
    const CHeaderFilter& filter,                 // empty identifiers = all
    const std::string& namespace_alias,
    std::string& error);

// Collect include directories from environment, manifest, and system paths.
std::vector<std::string> collect_c_include_dirs();

// Register additional include dirs (from CLI/manifest) for header resolution.
void set_c_header_extra_include_dirs(const std::vector<std::string>& dirs);

} // namespace LM::Frontend
