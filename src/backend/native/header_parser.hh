// header_parser.hh - Minimal C header declaration parser for binding generation
// (roadmap item 2b). Extracts function declarations from .h/.hpp files so the
// binding_generator can emit a Lymar namespace with typed FFI wrappers.

#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace LM::Backend::Native {

struct CStructDef;

struct CType {
    enum Kind { Void, Bool, Char, Short, Int, Long, LongLong,
                Float, Double, Ptr, FixedWidth, Custom, Struct };
    Kind kind;
    bool is_unsigned = false;
    int width = 0;           // for FixedWidth: 8/16/32/64
    std::string base_name;   // for Custom/typedef resolution
    // For Kind::Struct: the parsed definition (fields, size, alignment).
    // Null for forward-declared or unsupported structs.
    std::shared_ptr<CStructDef> def;
};

// A parsed C struct definition: flat scalar fields with native-layout
// offsets. `supported` is false when the body contains constructs the
// binding layer cannot marshal (nested aggregates, arrays, bitfields,
// unions, oversized field counts).
struct CStructField {
    std::string name;
    CType type;
    uint32_t offset = 0;
};

struct CStructDef {
    std::string name;                 // tag name or typedef alias (may be "")
    bool is_union = false;
    bool supported = true;
    std::vector<CStructField> fields;
    uint32_t size = 0;                // sizeof including tail padding
    uint32_t align = 1;               // struct alignment
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

// A named integer constant extracted from an enum body (or #define with an
// integer literal value). `value` is the evaluated 64-bit result.
struct CConstantDecl {
    std::string name;
    int64_t value = 0;
};

// Parse a C header source string and extract function declarations.
// The filename is used for diagnostic warnings. Returns the list of
// extracted function declarations; warnings accumulate skipped constructs.
// When `constants` is non-null, enum enumerators are appended to it.
std::vector<CFunctionDecl> parse_header(const std::string& source,
                                        const std::string& filename,
                                        std::vector<std::string>& warnings,
                                        std::vector<CConstantDecl>* constants = nullptr);

// Derive a Lymar module/namespace name from the header filename.
// "path/to/mylib.h" → "mylib"
std::string derive_namespace(const std::string& header_path);

} // namespace LM::Backend::Native
