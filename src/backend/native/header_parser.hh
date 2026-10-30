// header_parser.hh - Minimal C header declaration parser for binding generation
// (roadmap item 2b). Extracts function declarations from .h/.hpp files so the
// binding_generator can emit a Lymar namespace with typed FFI wrappers.

#pragma once
#include <string>
#include <vector>

namespace LM::Backend::Native {

struct CType {
    enum Kind { Void, Bool, Char, Short, Int, Long, LongLong,
                Float, Double, Ptr, FixedWidth, Custom };
    Kind kind;
    bool is_unsigned = false;
    int width = 0;           // for FixedWidth: 8/16/32/64
    std::string base_name;   // for Custom/typedef resolution
};

struct CParam {
    CType type;
    std::string name;        // optional
};

struct CFunctionDecl {
    std::string name;
    CType return_type;
    std::vector<CParam> params;
    bool is_variadic = false;
};

// Parse a C header source string and extract function declarations.
// The filename is used for diagnostic warnings. Returns the list of
// extracted function declarations; warnings accumulate skipped constructs.
std::vector<CFunctionDecl> parse_header(const std::string& source,
                                        const std::string& filename,
                                        std::vector<std::string>& warnings);

// Derive a Lymar module/namespace name from the header filename.
// "path/to/mylib.h" → "mylib"
std::string derive_namespace(const std::string& header_path);

} // namespace LM::Backend::Native
