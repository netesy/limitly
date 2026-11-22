// header_parser.cpp - C declaration-subset parser for roadmap 2b binding generation.
// Uses a simple tokenizer followed by recursive-descent parsing of function
// declarations. Preprocessor lines, comments, struct/union/enum definitions,
// and inline function bodies are recognized and skipped.

#include "header_parser.hh"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace LM::Backend::Native {
namespace {

// ─── Tokenizer ────────────────────────────────────────────────────────────────
enum TokKind { IDENT, KEYWORD, PUNCT, NUMBER, EOF_TOK };
struct Token {
    TokKind kind;
    std::string text;
};

static const std::unordered_set<std::string> kKeywords = {
    "void","_Bool","char","short","int","long","float","double",
    "signed","unsigned","const","volatile","restrict","static",
    "extern","inline","struct","union","enum","typedef","sizeof",
};

bool is_ident_char(char c) { return std::isalnum(c) || c == '_'; }

// Heuristic for calling-convention / attribute macros (VKAPI_CALL, APIENTRY,
// WINAPI, ...): all-caps identifier-like tokens. Only skipped when followed
// by another identifier, so genuine ALL_CAPS function names still parse.
bool is_macro_ident(const std::string& s) {
    if (s.size() < 2) return false;
    bool has_alpha = false;
    for (char c : s) {
        if (c >= 'a' && c <= 'z') return false;
        if (std::isalpha(static_cast<unsigned char>(c))) has_alpha = true;
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') return false;
    }
    return has_alpha;
}

std::vector<Token> tokenize(const std::string& src) {
    std::vector<Token> toks;
    size_t i = 0;
    while (i < src.size()) {
        // Skip line comments
        if (i + 1 < src.size() && src[i] == '/' && src[i+1] == '/') {
            while (i < src.size() && src[i] != '\n') ++i;
            continue;
        }
        // Skip block comments
        if (i + 1 < src.size() && src[i] == '/' && src[i+1] == '*') {
            i += 2;
            while (i + 1 < src.size() && !(src[i] == '*' && src[i+1] == '/')) ++i;
            if (i + 1 < src.size()) i += 2;
            continue;
        }
        // Skip preprocessor lines
        if (src[i] == '#') {
            while (i < src.size() && src[i] != '\n') {
                // Handle line continuation
                if (src[i] == '\\' && i + 1 < src.size() && src[i+1] == '\n') i += 2;
                else ++i;
            }
            continue;
        }
        // Whitespace
        if (std::isspace(static_cast<unsigned char>(src[i]))) { ++i; continue; }
        // Identifiers / keywords
        if (std::isalpha(static_cast<unsigned char>(src[i])) || src[i] == '_') {
            size_t start = i;
            while (i < src.size() && is_ident_char(src[i])) ++i;
            std::string word = src.substr(start, i - start);
            toks.push_back({kKeywords.count(word) ? KEYWORD : IDENT, word});
            continue;
        }
        // String literals
        if (src[i] == '"' || src[i] == '\'') {
            char q = src[i];
            size_t start = i;
            ++i;
            while (i < src.size() && src[i] != q) {
                if (src[i] == '\\') ++i;
                ++i;
            }
            if (i < src.size()) ++i; // closing quote
            toks.push_back({IDENT, src.substr(start, i - start)});
            continue;
        }
        // Numbers (kept for enum constant evaluation; suffix letters included)
        if (std::isdigit(static_cast<unsigned char>(src[i])) ||
            (src[i] == '.' && i + 1 < src.size() && std::isdigit(static_cast<unsigned char>(src[i+1])))) {
            size_t start = i;
            while (i < src.size() && (std::isalnum(static_cast<unsigned char>(src[i])) || src[i] == '.')) ++i;
            toks.push_back({NUMBER, src.substr(start, i - start)});
            continue;
        }
        // Punctuation
        toks.push_back({PUNCT, std::string(1, src[i])});
        ++i;
    }
    toks.push_back({EOF_TOK, ""});
    return toks;
}

// ─── Parser State ─────────────────────────────────────────────────────────────
struct Parser {
    const std::vector<Token>& toks;
    size_t pos = 0;
    std::unordered_map<std::string, CType> typedefs;
    // Struct/union tag name -> definition (populated as bodies are parsed).
    std::unordered_map<std::string, std::shared_ptr<CStructDef>> struct_defs;
    std::vector<std::string>& warnings;
    std::string filename;
    std::vector<CConstantDecl>* constants = nullptr;
    // Values collected so far (enum enumerators + earlier constants), used to
    // evaluate constant expressions that reference prior names.
    std::unordered_map<std::string, int64_t> const_values;
    bool const_expr_failed = false;

    Parser(const std::vector<Token>& t, std::vector<std::string>& w, const std::string& f,
           std::vector<CConstantDecl>* c = nullptr)
        : toks(t), warnings(w), filename(f), constants(c) {}

    const Token& cur() const { return toks[std::min(pos, toks.size()-1)]; }
    const Token& peek(size_t n = 1) const { return toks[std::min(pos+n, toks.size()-1)]; }
    void advance() { if (pos < toks.size()-1) ++pos; }
    bool match(const std::string& text) { if (cur().text == text) { advance(); return true; } return false; }
    bool expect(const std::string& text) { if (cur().text == text) { advance(); return true; } return false; }

    // ─── Type Parsing ─────────────────────────────────────────────────────────
    CType parse_base_type() {
        // Check typedef first
        if (cur().kind == IDENT) {
            auto it = typedefs.find(cur().text);
            if (it != typedefs.end()) { CType t = it->second; advance(); return t; }
        }

        bool is_unsigned = false;
        bool is_signed = false;
        // Qualifiers to skip
        while (cur().text == "const" || cur().text == "volatile" || cur().text == "restrict" ||
               cur().text == "static" || cur().text == "extern" || cur().text == "inline" ||
               (cur().kind == IDENT && is_macro_ident(cur().text) && peek().kind == IDENT)) {
            advance();
        }
        if (cur().text == "unsigned") { is_unsigned = true; advance(); }
        else if (cur().text == "signed") { is_signed = true; advance(); }

        CType result;
        result.kind = CType::Int; // default after unsigned/signed with no base
        result.is_unsigned = is_unsigned;

        if (cur().text == "void") { result = {CType::Void, false, 0, ""}; advance(); }
        else if (cur().text == "_Bool") { result = {CType::Bool, false, 0, ""}; advance(); }
        else if (cur().text == "char") { result = {CType::Char, is_unsigned, 8, ""}; advance(); }
        else if (cur().text == "short") { result = {CType::Short, is_unsigned, 16, ""}; advance(); }
        else if (cur().text == "int") { result = {CType::Int, is_unsigned, 32, ""}; advance(); }
        else if (cur().text == "long") {
            advance();
            if (cur().text == "long") { advance(); result = {CType::LongLong, is_unsigned, 64, ""}; }
            else result = {CType::Long, is_unsigned, 64, ""};
        }
        else if (cur().text == "float") { result = {CType::Float, false, 32, ""}; advance(); }
        else if (cur().text == "double") { result = {CType::Double, false, 64, ""}; advance(); }
        else if (cur().text == "struct" || cur().text == "union" || cur().text == "enum") {
            std::string tag = cur().text;
            advance();
            std::string name;
            if (cur().kind == IDENT) { name = cur().text; advance(); }
            if (tag == "enum") {
                // enum used as a type: body (if any) handled by callers;
                // enums marshal as i32.
                result = {CType::Custom, false, 0, "enum " + name};
            } else if (cur().text == "{") {
                // Inline body: `struct S { ... }` or `typedef struct { ... } T;`
                auto def = parse_struct_body(tag == "union", name);
                if (def && def->supported) {
                    result.kind = CType::Struct;
                    result.def = def;
                    result.base_name = name;
                    if (!name.empty()) struct_defs[name] = def;
                } else {
                    result = {CType::Custom, false, 0, tag + " " + name};
                    if (def) {
                        // Keep the definition for diagnostics/future use but
                        // mark the type unmarshalable.
                        if (!name.empty()) struct_defs[name] = def;
                    }
                }
            } else {
                // Tag reference without body: resolve previously parsed def.
                auto it = struct_defs.find(name);
                if (it != struct_defs.end() && it->second->supported) {
                    result.kind = CType::Struct;
                    result.def = it->second;
                    result.base_name = name;
                } else {
                    result = {CType::Custom, false, 0, tag + " " + name};
                }
            }
        }
        else if (cur().kind == IDENT) {
            // Unknown identifier type - check if stdint fixed-width
            std::string name = cur().text;
            result = map_fixed_width(name);
            if (result.kind == CType::Custom) {
                // Check typedefs again (might have been defined as something else)
                auto it = typedefs.find(name);
                if (it != typedefs.end()) result = it->second;
            }
            advance();
        }
        else {
            result = {CType::Custom, false, 0, cur().text};
            advance();
        }

        // Apply unsigned if we consumed it but base didn't set it
        if (is_unsigned && result.kind != CType::Void && result.kind != CType::Float &&
            result.kind != CType::Double && result.kind != CType::Bool) {
            result.is_unsigned = true;
        }
        // If we had unsigned/signed but no type keyword followed (e.g. `unsigned x`), default to int
        if ((is_unsigned || is_signed) && result.kind == CType::Custom && result.base_name.empty()) {
            result = {CType::Int, is_unsigned, 32, ""};
        }
        return result;
    }

    static CType map_fixed_width(const std::string& name) {
        // stdint.h types
        if (name == "int8_t") return {CType::FixedWidth, false, 8, name};
        if (name == "uint8_t") return {CType::FixedWidth, true, 8, name};
        if (name == "int16_t") return {CType::FixedWidth, false, 16, name};
        if (name == "uint16_t") return {CType::FixedWidth, true, 16, name};
        if (name == "int32_t") return {CType::FixedWidth, false, 32, name};
        if (name == "uint32_t") return {CType::FixedWidth, true, 32, name};
        if (name == "int64_t") return {CType::FixedWidth, false, 64, name};
        if (name == "uint64_t") return {CType::FixedWidth, true, 64, name};
        if (name == "size_t" || name == "uintptr_t" || name == "intptr_t")
            return {CType::FixedWidth, name == "uintptr_t", 64, name};
        if (name == "ssize_t") return {CType::FixedWidth, false, 64, name};
        if (name == "bool") return {CType::Bool, false, 0, name};
        return {CType::Custom, false, 0, name};
    }

    CType parse_type() {
        CType base = parse_base_type();
        // Pointer(s)
        while (cur().text == "*") {
            advance();
            // skip const/volatile after *
            while (cur().text == "const" || cur().text == "volatile" || cur().text == "restrict")
                advance();
            base = {CType::Ptr, false, 0, ""};
        }
        return base;
    }

    // ─── Constant-expression evaluation (enum initializers) ──────────────────
    // Restricted C constant-expression subset: integer literals, prior
    // constant names, char literals, unary + - ~, and the binary operators
    // | ^ & << >> + - * / %. Comparison/logical/ternary are rejected.

    static bool is_punct2(const Token& a, const Token& b, const char* op) {
        return a.kind == PUNCT && b.kind == PUNCT && a.text + b.text == op;
    }

    int64_t eval_primary() {
        const Token& t = cur();
        if (t.kind == NUMBER) {
            advance();
            std::string s = t.text;
            // Strip integer suffixes (u/l combinations, case-insensitive)
            while (!s.empty() && (s.back() == 'u' || s.back() == 'U' ||
                                  s.back() == 'l' || s.back() == 'L')) s.pop_back();
            if (s.rfind("0x", 0) == 0 || s.rfind("0X", 0) == 0) {
                return static_cast<int64_t>(std::strtoull(s.c_str(), nullptr, 16));
            }
            if (s.size() > 2 && s[0] == '0' && s[1] == 'b') {
                return static_cast<int64_t>(std::strtoull(s.c_str() + 2, nullptr, 2));
            }
            if (s.size() > 1 && s[0] == '0') {
                return static_cast<int64_t>(std::strtoull(s.c_str(), nullptr, 8));
            }
            return static_cast<int64_t>(std::strtoll(s.c_str(), nullptr, 10));
        }
        if (t.kind == IDENT) {
            // Char literal: token text includes the quotes, e.g. 'a' or '\n'
            if (t.text.size() >= 3 && t.text.front() == '\'') {
                advance();
                std::string body = t.text.substr(1, t.text.size() - 2);
                if (body.empty()) { const_expr_failed = true; return 0; }
                if (body[0] == '\\' && body.size() >= 2) {
                    char c = body[1];
                    switch (c) {
                        case 'n': return '\n'; case 't': return '\t'; case 'r': return '\r';
                        case '0': return '\0'; case '\\': return '\\'; case '\'': return '\'';
                        case '"': return '"'; case 'a': return '\a'; case 'b': return '\b';
                        case 'f': return '\f'; case 'v': return '\v';
                        default: return static_cast<unsigned char>(c);
                    }
                }
                return static_cast<unsigned char>(body[0]);
            }
            auto it = const_values.find(t.text);
            if (it != const_values.end()) { advance(); return it->second; }
            const_expr_failed = true;
            advance();
            return 0;
        }
        if (t.text == "(") {
            advance();
            int64_t v = eval_bitor();
            if (cur().text == ")") advance();
            else const_expr_failed = true;
            return v;
        }
        const_expr_failed = true;
        advance();
        return 0;
    }

    int64_t eval_unary() {
        if (cur().text == "-") { advance(); return -eval_unary(); }
        if (cur().text == "~") { advance(); return ~eval_unary(); }
        if (cur().text == "+") { advance(); return eval_unary(); }
        return eval_primary();
    }

    int64_t eval_mul() {
        int64_t v = eval_unary();
        while (!const_expr_failed) {
            if (cur().text == "*") { advance(); v *= eval_unary(); }
            else if (cur().text == "/") { advance(); int64_t r = eval_unary(); v = r ? v / r : 0; }
            else if (cur().text == "%") { advance(); int64_t r = eval_unary(); v = r ? v % r : 0; }
            else break;
        }
        return v;
    }
    int64_t eval_add() {
        int64_t v = eval_mul();
        while (!const_expr_failed) {
            if (cur().text == "+") { advance(); v += eval_mul(); }
            else if (cur().text == "-") { advance(); v -= eval_mul(); }
            else break;
        }
        return v;
    }
    int64_t eval_shift() {
        int64_t v = eval_add();
        while (!const_expr_failed) {
            if (is_punct2(cur(), peek(), "<<")) { advance(); advance(); v <<= eval_add(); }
            else if (is_punct2(cur(), peek(), ">>")) { advance(); advance(); v >>= eval_add(); }
            else break;
        }
        return v;
    }
    int64_t eval_bitand() {
        int64_t v = eval_shift();
        while (!const_expr_failed && cur().text == "&") { advance(); v &= eval_shift(); }
        return v;
    }
    int64_t eval_bitxor() {
        int64_t v = eval_bitand();
        while (!const_expr_failed && cur().text == "^") { advance(); v ^= eval_bitand(); }
        return v;
    }
    int64_t eval_bitor() {
        int64_t v = eval_bitxor();
        while (!const_expr_failed && cur().text == "|") { advance(); v |= eval_bitxor(); }
        return v;
    }

    // Parses `{ IDENT (= expr)? (, ...)* }` starting at the '{' token.
    // Appends each enumerator to `constants` (when set) and const_values.
    // Returns the number of enumerators consumed.
    size_t parse_enum_body() {
        size_t count = 0;
        if (!expect("{")) return 0;
        int64_t next_value = 0;
        bool first = true;
        while (cur().kind != EOF_TOK && cur().text != "}") {
            if (!first) {
                if (!expect(",")) break;
                // Trailing comma before }
                if (cur().text == "}") break;
            }
            first = false;
            if (cur().kind != IDENT) { advance(); continue; }
            std::string name = cur().text;
            advance();
            if (cur().text == "=") {
                advance();
                const_expr_failed = false;
                size_t save = pos;
                next_value = eval_bitor();
                if (const_expr_failed) {
                    warnings.push_back(filename + ": could not evaluate enum value for '" + name + "'");
                    // Recover: skip to , or }
                    while (cur().kind != EOF_TOK && cur().text != "," && cur().text != "}") advance();
                    continue;
                }
                (void)save;
            }
            const_values[name] = next_value;
            if (constants) constants->push_back({name, next_value});
            ++count;
            ++next_value;
        }
        expect("}");
        return count;
    }

    // ─── Skip balanced braces ─────────────────────────────────────────────────
    void skip_braces() {
        int depth = 0;
        while (cur().kind != EOF_TOK) {
            if (cur().text == "{") ++depth;
            else if (cur().text == "}") { --depth; if (depth == 0) { advance(); return; } }
            advance();
        }
    }

    // ─── Declaration Handling ─────────────────────────────────────────────────
    void handle_typedef() {
        // typedef <type> <name>;  or  typedef <type> (*name)(...);
        // or typedef enum { ... } Name;  (enum constants are collected)
        advance(); // 'typedef'
        CType base = parse_type();
        bool was_enum = base.base_name.rfind("enum", 0) == 0;
        if (cur().text == "{") {
            if (was_enum) parse_enum_body();
            else skip_braces();
        }
        if (cur().kind == IDENT) {
            std::string name = cur().text;
            advance();
            // C enums are int-sized; register the typedef as i32 so enum-typed
            // parameters/returns marshal with the correct width.
            typedefs[name] = was_enum ? CType{CType::Int, false, 32, ""} : base;
        }
        // Skip to semicolon
        while (cur().kind != EOF_TOK && cur().text != ";" && cur().text != "{") advance();
        if (cur().text == "{") { skip_braces(); }
        expect(";");
    }

    // Scalar size/alignment in bytes for layout purposes. Returns false for
    // types that cannot appear as a flat struct field (nested aggregates,
    // void, unknown/custom).
    static bool scalar_layout(const CType& t, uint32_t& size, uint32_t& align) {
        switch (t.kind) {
            case CType::Bool:
            case CType::Char:   size = 1; align = 1; return true;
            case CType::Short:  size = 2; align = 2; return true;
            case CType::Int:
            case CType::Float:  size = 4; align = 4; return true;
            case CType::Long:
            case CType::LongLong:
            case CType::Double:
            case CType::Ptr:    size = 8; align = 8; return true;
            case CType::FixedWidth: {
                if (t.width <= 0 || t.width > 64) return false;
                size = static_cast<uint32_t>((t.width + 7) / 8);
                align = size < 8 ? size : 8;
                return true;
            }
            default: return false;
        }
    }

    static uint32_t align_up(uint32_t v, uint32_t a) {
        return a == 0 ? v : ((v + a - 1) / a) * a;
    }

    // Parses `{ field-decl; ... }` starting at '{'. Each field declaration is
    // `<type> <declarator> (, <declarator>)* ;`. Arrays, bitfields, nested
    // aggregates, and unions mark the definition unsupported but are still
    // consumed so parsing stays in sync.
    std::shared_ptr<CStructDef> parse_struct_body(bool is_union, const std::string& name) {
        auto def = std::make_shared<CStructDef>();
        def->name = name;
        def->is_union = is_union;
        if (!expect("{")) return def;
        while (cur().kind != EOF_TOK && cur().text != "}") {
            if (cur().text == ";") { advance(); continue; }
            CType field_type = parse_type();
            // Declarator list for this field type
            bool first = true;
            while (cur().kind != EOF_TOK && cur().text != ";" && cur().text != "}") {
                if (!first) {
                    if (!expect(",")) break;
                }
                first = false;
                // Skip pointer stars (already folded into field_type by
                // parse_type for the first declarator only; extra stars here
                // are rare — treat as unsupported).
                while (cur().text == "*") { advance(); }
                if (cur().text == "(") {
                    // Function-pointer or parenthesized declarator: unsupported
                    int depth = 0;
                    while (cur().kind != EOF_TOK) {
                        if (cur().text == "(") ++depth;
                        else if (cur().text == ")") { --depth; if (depth == 0) { advance(); break; } }
                        advance();
                    }
                    def->supported = false;
                    continue;
                }
                if (cur().kind != IDENT) { advance(); continue; }
                std::string fname = cur().text;
                advance();
                bool bad = false;
                // Array suffix -> unsupported
                while (cur().text == "[") {
                    bad = true;
                    advance();
                    while (cur().kind != EOF_TOK && cur().text != "]") advance();
                    expect("]");
                }
                // Bitfield `: N` -> unsupported
                if (cur().text == ":") {
                    bad = true;
                    advance();
                    while (cur().kind != EOF_TOK && cur().text != "," && cur().text != ";" && cur().text != "}") advance();
                }
                CStructField f;
                f.name = fname;
                f.type = field_type;
                if (bad || is_union || field_type.kind == CType::Struct ||
                    field_type.kind == CType::Void || field_type.kind == CType::Custom) {
                    def->supported = false;
                }
                def->fields.push_back(f);
            }
            expect(";");
        }
        expect("}");
        if (is_union || !def->supported || def->fields.empty() || def->fields.size() > 16) {
            def->supported = false;
        }
        if (def->supported) {
            // Compute native layout (LP64/Win64 agree for these scalar types:
            // align = min(size, 8), tail padding to struct alignment).
            uint32_t offset = 0;
            uint32_t max_align = 1;
            for (auto& f : def->fields) {
                uint32_t fsz = 0, fal = 1;
                if (!scalar_layout(f.type, fsz, fal)) { def->supported = false; break; }
                offset = align_up(offset, fal);
                f.offset = offset;
                offset += fsz;
                if (fal > max_align) max_align = fal;
            }
            if (def->supported) {
                def->align = max_align;
                def->size = align_up(offset, max_align);
            }
        }
        return def;
    }

    bool handle_struct_union_enum() {
        std::string kw = cur().text; // struct/union/enum
        advance();
        // Skip optional tag
        std::string tag_name;
        if (cur().kind == IDENT) { tag_name = cur().text; advance(); }
        // If { follows, parse enum bodies for constants; parse struct/union
        // bodies into definitions.
        if (cur().text == "{") {
            if (kw == "enum") {
                parse_enum_body();
            } else {
                auto def = parse_struct_body(kw == "union", tag_name);
                if (!tag_name.empty()) struct_defs[tag_name] = def;
            }
        }
        // After body, there might be variable declarations or typedef names
        // Just skip to ;
        while (cur().kind != EOF_TOK && cur().text != ";" && cur().text != "}") advance();
        expect(";");
        return true; // consumed, not a function
    }

    std::optional<CFunctionDecl> try_parse_function() {
        size_t save = pos;
        CType ret = parse_type();

        // Must be followed by an identifier (function name), possibly with
        // calling-convention/attribute macro qualifiers in between
        // (e.g. `VkResult VKAPI_CALL vkCreateInstance(`).
        while (cur().kind == IDENT && is_macro_ident(cur().text) && peek().kind == IDENT)
            advance();
        if (cur().kind != IDENT) { pos = save; return std::nullopt; }
        std::string name = cur().text;
        advance();

        // Must be followed by (
        if (cur().text != "(") { pos = save; return std::nullopt; }
        advance();

        CFunctionDecl decl;
        decl.name = name;
        decl.return_type = ret;

        // Parse parameters
        bool first = true;
        while (cur().kind != EOF_TOK && cur().text != ")") {
            if (first) first = false;
            else if (!expect(",")) { advance(); continue; }

            if (cur().text == "...") { decl.is_variadic = true; advance(); break; }
            if (cur().text == "void" && peek().text == ")") { advance(); break; }

            // Skip function-pointer params: detect `(*name>` pattern
            if (cur().text == "(" && peek().text == "*") {
                // Skip balanced parens for the function pointer
                int depth = 0;
                while (cur().kind != EOF_TOK) {
                    if (cur().text == "(") ++depth;
                    else if (cur().text == ")") { --depth; if (depth == 0) { advance(); break; } }
                    advance();
                }
                // Skip to comma or closing paren
                while (cur().kind != EOF_TOK && cur().text != "," && cur().text != ")") advance();
                warnings.push_back(filename + ": skipped function-pointer parameter in '" + name + "'");
                continue;
            }

            CParam param;
            param.type = parse_type();
            if (cur().kind == IDENT) { param.name = cur().text; advance(); }
            // Skip array brackets
            while (cur().text == "[") { advance(); while (cur().kind != EOF_TOK && cur().text != "]") advance(); expect("]"); }
            decl.params.push_back(param);
        }
        expect(")");

        // Function declaration ends with ; or has a body { ... }
        if (cur().text == ";") {
            advance();
            return decl;
        }
        if (cur().text == "{") {
            // inline function body - skip it
            skip_braces();
            return decl;
        }
        // const/override/throw qualifiers (C++)
        while (cur().kind != EOF_TOK && cur().text != ";" && cur().text != "{") advance();
        if (cur().text == ";") { advance(); return decl; }
        if (cur().text == "{") { skip_braces(); return decl; }

        pos = save;
        return std::nullopt;
    }

    void parse_translation_unit(std::vector<CFunctionDecl>& out) {
        while (cur().kind != EOF_TOK) {
            if (cur().text == "typedef") { handle_typedef(); continue; }
            if (cur().text == "struct" || cur().text == "union" || cur().text == "enum") {
                // Could be a definition or a forward decl followed by something else
                size_t save = pos;
                handle_struct_union_enum();
                continue;
            }
            if (cur().text == "extern" && peek().text == "\"C\"") {
                advance(); advance(); // extern "C"
                if (cur().text == "{") advance(); // open brace
                continue;
            }
            if (cur().text == "asm" || cur().text == "__attribute__") {
                if (cur().text == "__attribute__") {
                    advance();
                    if (cur().text == "(") {
                        int depth = 0;
                        while (cur().kind != EOF_TOK) {
                            if (cur().text == "(") ++depth;
                            else if (cur().text == ")") { --depth; if (depth == 0) { advance(); break; } }
                            advance();
                        }
                    }
                    continue;
                }
                advance();
                while (cur().kind != EOF_TOK && cur().text != ";") advance();
                expect(";");
                continue;
            }
            // Try function declaration
            auto fn = try_parse_function();
            if (fn) { out.push_back(*fn); continue; }

            // Function-like macro invocation without a trailing semicolon
            // (e.g. `VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImageView)`).
            // Skip the balanced argument list so recovery doesn't run away
            // and swallow the next declaration.
            if (cur().kind == IDENT && peek().text == "(") {
                advance(); advance(); // IDENT (
                int depth = 1;
                while (cur().kind != EOF_TOK && depth > 0) {
                    if (cur().text == "(") ++depth;
                    else if (cur().text == ")") --depth;
                    advance();
                }
                if (cur().text == ";") advance();
                continue;
            }

            // Variable declaration or something else - skip to ;
            while (cur().kind != EOF_TOK && cur().text != ";" && cur().text != "{") advance();
            if (cur().text == "{") skip_braces();
            expect(";");
        }
    }
};

} // anonymous namespace

// ─── Public API ────────────────────────────────────────────────────────────────

std::vector<CFunctionDecl> parse_header(const std::string& source,
                                        const std::string& filename,
                                        std::vector<std::string>& warnings,
                                        std::vector<CConstantDecl>* constants) {
    auto tokens = tokenize(source);
    std::vector<CFunctionDecl> functions;
    Parser parser(tokens, warnings, filename, constants);

    // Pre-load common typedefs
    parser.typedefs["size_t"] = {CType::FixedWidth, true, 64, "size_t"};
    parser.typedefs["ssize_t"] = {CType::FixedWidth, false, 64, "ssize_t"};
    parser.typedefs["intptr_t"] = {CType::FixedWidth, false, 64, "intptr_t"};
    parser.typedefs["uintptr_t"] = {CType::FixedWidth, true, 64, "uintptr_t"};
    parser.typedefs["ptrdiff_t"] = {CType::FixedWidth, false, 64, "ptrdiff_t"};
    parser.typedefs["int8_t"] = {CType::FixedWidth, false, 8, "int8_t"};
    parser.typedefs["uint8_t"] = {CType::FixedWidth, true, 8, "uint8_t"};
    parser.typedefs["int16_t"] = {CType::FixedWidth, false, 16, "int16_t"};
    parser.typedefs["uint16_t"] = {CType::FixedWidth, true, 16, "uint16_t"};
    parser.typedefs["int32_t"] = {CType::FixedWidth, false, 32, "int32_t"};
    parser.typedefs["uint32_t"] = {CType::FixedWidth, true, 32, "uint32_t"};
    parser.typedefs["int64_t"] = {CType::FixedWidth, false, 64, "int64_t"};
    parser.typedefs["uint64_t"] = {CType::FixedWidth, true, 64, "uint64_t"};
    parser.typedefs["bool"] = {CType::Bool, false, 0, "bool"};
    parser.typedefs["wchar_t"] = {CType::Int, false, 32, "wchar_t"};

    parser.parse_translation_unit(functions);
    return functions;
}

std::string derive_namespace(const std::string& header_path) {
    std::filesystem::path p(header_path);
    std::string stem = p.stem().string();
    // Sanitize: replace non-identifier chars with underscore
    for (auto& c : stem) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_')
            c = '_';
    }
    // Avoid leading digits
    if (!stem.empty() && std::isdigit(static_cast<unsigned char>(stem[0])))
        stem = "_" + stem;
    return stem;
}

} // namespace LM::Backend::Native
