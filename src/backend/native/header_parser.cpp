// header_parser.cpp - C declaration-subset parser for roadmap 2b binding generation.
// Uses a simple tokenizer followed by recursive-descent parsing of function
// declarations. Preprocessor lines, comments, struct/union/enum definitions,
// and inline function bodies are recognized and skipped.

#include "header_parser.hh"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace LM::Backend::Native {
namespace {

// ─── Tokenizer ────────────────────────────────────────────────────────────────
enum TokKind { IDENT, KEYWORD, PUNCT, EOF_TOK };
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
        // Numbers (skip)
        if (std::isdigit(static_cast<unsigned char>(src[i]))) {
            while (i < src.size() && (std::isalnum(static_cast<unsigned char>(src[i])) || src[i] == '.')) ++i;
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
    std::vector<std::string>& warnings;
    std::string filename;

    Parser(const std::vector<Token>& t, std::vector<std::string>& w, const std::string& f)
        : toks(t), warnings(w), filename(f) {}

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
               cur().text == "static" || cur().text == "extern" || cur().text == "inline") {
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
            // Skip the tag and return as Custom/Ptr
            std::string tag = cur().text;
            advance();
            std::string name = cur().text;
            if (cur().kind == IDENT) advance();
            result = {CType::Custom, false, 0, tag + " " + name};
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
        advance(); // 'typedef'
        CType base = parse_type();
        if (cur().kind == IDENT) {
            std::string name = cur().text;
            advance();
            typedefs[name] = base;
        }
        // Skip to semicolon
        while (cur().kind != EOF_TOK && cur().text != ";" && cur().text != "{") advance();
        if (cur().text == "{") { skip_braces(); }
        expect(";");
    }

    bool handle_struct_union_enum() {
        std::string kw = cur().text; // struct/union/enum
        advance();
        // Skip optional tag
        if (cur().kind == IDENT) advance();
        // If { follows, skip the body
        if (cur().text == "{") { skip_braces(); }
        // After struct body, there might be variable declarations or typedef names
        // Just skip to ;
        while (cur().kind != EOF_TOK && cur().text != ";" && cur().text != "}") advance();
        expect(";");
        return true; // consumed, not a function
    }

    std::optional<CFunctionDecl> try_parse_function() {
        size_t save = pos;
        CType ret = parse_type();

        // Must be followed by an identifier (function name)
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
                                        std::vector<std::string>& warnings) {
    auto tokens = tokenize(source);
    std::vector<CFunctionDecl> functions;
    Parser parser(tokens, warnings, filename);

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
