#include "lymar.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/type_checker.hh"
#include "frontend/module_manager.hh"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <optional>
#include <sstream>
#include <cctype>
#include <cstdint>
#include <utility>
#include <regex>
#include <functional>
#include <filesystem>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

namespace LM {
namespace {

namespace Json {

enum class Type { Null, Bool, Number, String, Array, Object };

struct Value {
    Type type = Type::Null;
    bool bool_val = false;
    double num_val = 0.0;
    int64_t int_val = 0;
    bool is_int = false;
    std::string str_val;
    std::vector<Value> arr_val;
    std::vector<std::pair<std::string, Value>> obj_val;

    Value() : type(Type::Null) {}
    Value(std::nullptr_t) : type(Type::Null) {}
    Value(bool b) : type(Type::Bool), bool_val(b) {}
    Value(int n) : type(Type::Number), num_val(n), int_val(n), is_int(true) {}
    Value(int64_t n) : type(Type::Number), num_val(static_cast<double>(n)), int_val(n), is_int(true) {}
    Value(size_t n) : type(Type::Number), num_val(static_cast<double>(n)), int_val(static_cast<int64_t>(n)), is_int(true) {}
    Value(double n) : type(Type::Number), num_val(n), int_val(static_cast<int64_t>(n)), is_int(false) {}
    Value(const char* s) : type(Type::String), str_val(s ? s : "") {}
    Value(const std::string& s) : type(Type::String), str_val(s) {}
    Value(std::string&& s) : type(Type::String), str_val(std::move(s)) {}

    static Value object() {
        Value v;
        v.type = Type::Object;
        return v;
    }

    static Value array() {
        Value v;
        v.type = Type::Array;
        return v;
    }

    bool is_null() const { return type == Type::Null; }
    bool is_bool() const { return type == Type::Bool; }
    bool is_number() const { return type == Type::Number; }
    bool is_string() const { return type == Type::String; }
    bool is_array() const { return type == Type::Array; }
    bool is_object() const { return type == Type::Object; }
    bool empty() const {
        return (type == Type::Null) ||
               (is_object() && obj_val.empty()) ||
               (is_array() && arr_val.empty()) ||
               (is_string() && str_val.empty());
    }

    bool as_bool(bool def = false) const { return is_bool() ? bool_val : def; }
    int64_t as_int(int64_t def = 0) const { return is_number() ? int_val : def; }
    double as_double(double def = 0.0) const { return is_number() ? num_val : def; }
    const std::string& as_string() const {
        static const std::string empty;
        return is_string() ? str_val : empty;
    }

    bool has(const std::string& key) const {
        if (!is_object()) return false;
        for (const auto& kv : obj_val) {
            if (kv.first == key) return true;
        }
        return false;
    }

    const Value& operator[](const std::string& key) const {
        static const Value null_val;
        if (!is_object()) return null_val;
        for (const auto& kv : obj_val) {
            if (kv.first == key) return kv.second;
        }
        return null_val;
    }

    Value& operator[](const std::string& key) {
        if (!is_object()) {
            type = Type::Object;
            obj_val.clear();
        }
        for (auto& kv : obj_val) {
            if (kv.first == key) return kv.second;
        }
        obj_val.push_back({key, Value()});
        return obj_val.back().second;
    }

    size_t size() const {
        if (is_array()) return arr_val.size();
        if (is_object()) return obj_val.size();
        return 0;
    }

    const Value& operator[](size_t idx) const {
        static const Value null_val;
        if (is_array() && idx < arr_val.size()) return arr_val[idx];
        return null_val;
    }

    Value& operator[](size_t idx) {
        static Value null_val;
        if (is_array() && idx < arr_val.size()) return arr_val[idx];
        return null_val;
    }

    void push_back(const Value& v) {
        if (!is_array()) {
            type = Type::Array;
            arr_val.clear();
        }
        arr_val.push_back(v);
    }

    void push_back(Value&& v) {
        if (!is_array()) {
            type = Type::Array;
            arr_val.clear();
        }
        arr_val.push_back(std::move(v));
    }

    std::string serialize() const {
        std::string out;
        serialize_into(out);
        return out;
    }

    void serialize_into(std::string& out) const {
        switch (type) {
            case Type::Null: out += "null"; break;
            case Type::Bool: out += bool_val ? "true" : "false"; break;
            case Type::Number:
                if (is_int) {
                    out += std::to_string(int_val);
                } else {
                    char buf[64];
                    snprintf(buf, sizeof(buf), "%g", num_val);
                    out += buf;
                }
                break;
            case Type::String:
                escape_string(str_val, out);
                break;
            case Type::Array:
                out += '[';
                for (size_t i = 0; i < arr_val.size(); ++i) {
                    if (i > 0) out += ',';
                    arr_val[i].serialize_into(out);
                }
                out += ']';
                break;
            case Type::Object:
                out += '{';
                for (size_t i = 0; i < obj_val.size(); ++i) {
                    if (i > 0) out += ',';
                    escape_string(obj_val[i].first, out);
                    out += ':';
                    obj_val[i].second.serialize_into(out);
                }
                out += '}';
                break;
        }
    }

private:
    static void escape_string(const std::string& s, std::string& out) {
        out += '\"';
        for (char c : s) {
            switch (c) {
                case '\"': out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\b': out += "\\b"; break;
                case '\f': out += "\\f"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default:
                    if (static_cast<unsigned char>(c) < 0x20) {
                        char buf[8];
                        snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned char>(c));
                        out += buf;
                    } else {
                        out += c;
                    }
                    break;
            }
        }
        out += '\"';
    }
};

class Parser {
    const std::string& s;
    size_t idx = 0;

    void skip_ws() {
        while (idx < s.size() && (s[idx] == ' ' || s[idx] == '\t' || s[idx] == '\r' || s[idx] == '\n')) {
            idx++;
        }
    }

    char peek() {
        skip_ws();
        return (idx < s.size()) ? s[idx] : '\0';
    }

    char get() {
        skip_ws();
        return (idx < s.size()) ? s[idx++] : '\0';
    }

    bool match(char expected) {
        skip_ws();
        if (idx < s.size() && s[idx] == expected) {
            idx++;
            return true;
        }
        return false;
    }

public:
    explicit Parser(const std::string& str) : s(str) {}

    Value parse() {
        skip_ws();
        return parse_value();
    }

private:
    Value parse_value() {
        char c = peek();
        if (c == '\0') return Value();
        if (c == '{') return parse_object();
        if (c == '[') return parse_array();
        if (c == '"') return parse_string();
        if (c == 't' || c == 'f') return parse_bool();
        if (c == 'n') return parse_null();
        if (c == '-' || (c >= '0' && c <= '9')) return parse_number();
        return Value();
    }

    Value parse_object() {
        Value obj = Value::object();
        get();
        skip_ws();
        if (peek() == '}') {
            get();
            return obj;
        }
        while (idx < s.size()) {
            skip_ws();
            if (peek() != '"') break;
            Value key = parse_string();
            if (!match(':')) break;
            Value val = parse_value();
            obj[key.as_string()] = std::move(val);
            skip_ws();
            if (match(',')) {
                continue;
            }
            if (match('}')) {
                break;
            }
            break;
        }
        return obj;
    }

    Value parse_array() {
        Value arr = Value::array();
        get();
        skip_ws();
        if (peek() == ']') {
            get();
            return arr;
        }
        while (idx < s.size()) {
            Value val = parse_value();
            arr.push_back(std::move(val));
            skip_ws();
            if (match(',')) {
                continue;
            }
            if (match(']')) {
                break;
            }
            break;
        }
        return arr;
    }

    Value parse_string() {
        get();
        std::string res;
        while (idx < s.size()) {
            char c = s[idx++];
            if (c == '"') {
                return Value(res);
            }
            if (c == '\\' && idx < s.size()) {
                char esc = s[idx++];
                switch (esc) {
                    case '"': res += '"'; break;
                    case '\\': res += '\\'; break;
                    case '/': res += '/'; break;
                    case 'b': res += '\b'; break;
                    case 'f': res += '\f'; break;
                    case 'n': res += '\n'; break;
                    case 'r': res += '\r'; break;
                    case 't': res += '\t'; break;
                    case 'u': {
                        if (idx + 4 <= s.size()) {
                            std::string hex = s.substr(idx, 4);
                            idx += 4;
                            uint32_t cp = std::strtoul(hex.c_str(), nullptr, 16);
                            if (cp < 0x80) {
                                res += static_cast<char>(cp);
                            } else if (cp < 0x800) {
                                res += static_cast<char>(0xC0 | (cp >> 6));
                                res += static_cast<char>(0x80 | (cp & 0x3F));
                            } else {
                                res += static_cast<char>(0xE0 | (cp >> 12));
                                res += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                                res += static_cast<char>(0x80 | (cp & 0x3F));
                            }
                        }
                        break;
                    }
                    default: res += esc; break;
                }
            } else {
                res += c;
            }
        }
        return Value(res);
    }

    Value parse_bool() {
        if (s.compare(idx, 4, "true") == 0) {
            idx += 4;
            return Value(true);
        }
        if (s.compare(idx, 5, "false") == 0) {
            idx += 5;
            return Value(false);
        }
        return Value();
    }

    Value parse_null() {
        if (s.compare(idx, 4, "null") == 0) {
            idx += 4;
        }
        return Value();
    }

    Value parse_number() {
        size_t start = idx;
        bool is_fp = false;
        if (s[idx] == '-') idx++;
        while (idx < s.size() && s[idx] >= '0' && s[idx] <= '9') idx++;
        if (idx < s.size() && s[idx] == '.') {
            is_fp = true;
            idx++;
            while (idx < s.size() && s[idx] >= '0' && s[idx] <= '9') idx++;
        }
        if (idx < s.size() && (s[idx] == 'e' || s[idx] == 'E')) {
            is_fp = true;
            idx++;
            if (idx < s.size() && (s[idx] == '+' || s[idx] == '-')) idx++;
            while (idx < s.size() && s[idx] >= '0' && s[idx] <= '9') idx++;
        }
        std::string sub = s.substr(start, idx - start);
        if (is_fp) {
            return Value(std::strtod(sub.c_str(), nullptr));
        } else {
            return Value(static_cast<int64_t>(std::strtoll(sub.c_str(), nullptr, 10)));
        }
    }
};

} // namespace Json

struct LSPDiagnostic {
    int line = 0;
    int character = 0;
    int end_line = 0;
    int end_character = 1;
    int severity = 1;
    std::string message;
    std::string source = "lymar";
};

struct DocumentSnapshot {
    std::string uri;
    int version = 0;
    std::string content;
    std::vector<Frontend::Token> tokens;
    std::shared_ptr<Frontend::AST::Program> ast;
    std::shared_ptr<Frontend::AST::Program> last_valid_ast;
    bool is_valid = false;
    bool type_check_valid = false;
    std::optional<Frontend::TypeCheckResult> last_check_result;
    std::vector<LSPDiagnostic> diagnostics;

    std::shared_ptr<Frontend::AST::Program> get_ast() const {
        return ast ? ast : last_valid_ast;
    }

    void update_full(const std::string& new_text, int new_version = -1) {
        content = new_text;
        if (new_version >= 0) version = new_version;
        else version++;
        type_check_valid = false;
        recheck();
    }

    void recheck() {
        diagnostics.clear();
        Frontend::Scanner scanner(content);
        tokens = scanner.scanTokens();
        try {
            Frontend::Parser parser(scanner, false);
            ast = parser.parse();
            is_valid = (ast != nullptr);
            if (ast) {
                last_valid_ast = ast;
            }

            for (const auto& parse_err : parser.getErrors()) {
                LSPDiagnostic diag;
                diag.line = parse_err.line > 0 ? parse_err.line - 1 : 0;
                diag.character = parse_err.column > 0 ? parse_err.column - 1 : 0;
                diag.end_line = diag.line;
                diag.end_character = diag.character + 1;
                diag.severity = 1;
                diag.message = parse_err.message;
                diagnostics.push_back(diag);
            }
        } catch (const std::exception& e) {
            is_valid = false;
            LSPDiagnostic diag;
            diag.line = 0;
            diag.character = 0;
            diag.end_line = 0;
            diag.end_character = 1;
            diag.severity = 1;
            diag.message = e.what();
            diagnostics.push_back(diag);
        } catch (...) {
            is_valid = false;
        }

        if (ast) {
            try {
                Frontend::ModuleManager::getInstance().resolve_all(ast, "lsp");
                last_check_result = Frontend::TypeCheckerFactory::check_program(
                    ast, content, uri.empty() ? "lsp-input" : uri);
                type_check_valid = true;

                if (last_check_result.has_value()) {
                    for (const auto& err_str : last_check_result->errors) {
                        LSPDiagnostic diag;
                        diag.line = 0;
                        diag.character = 0;
                        diag.end_line = 0;
                        diag.end_character = 1;
                        diag.severity = 1;
                        diag.message = err_str;

                        size_t q1 = err_str.find('`');
                        size_t q2 = (q1 != std::string::npos) ? err_str.find('`', q1 + 1) : std::string::npos;
                        if (q1 == std::string::npos) {
                            q1 = err_str.find('\'');
                            q2 = (q1 != std::string::npos) ? err_str.find('\'', q1 + 1) : std::string::npos;
                        }
                        if (q1 != std::string::npos && q2 != std::string::npos) {
                            std::string target = err_str.substr(q1 + 1, q2 - q1 - 1);
                            size_t found_pos = content.find(target);
                            if (found_pos != std::string::npos) {
                                int cur_line = 0;
                                int cur_col = 0;
                                for (size_t i = 0; i < found_pos; ++i) {
                                    if (content[i] == '\n') {
                                        cur_line++;
                                        cur_col = 0;
                                    } else {
                                        cur_col++;
                                    }
                                }
                                diag.line = cur_line;
                                diag.character = cur_col;
                                diag.end_line = cur_line;
                                diag.end_character = cur_col + static_cast<int>(target.size());
                            }
                        }
                        diagnostics.push_back(diag);
                    }
                }
            } catch (const std::exception& e) {
                LSPDiagnostic diag;
                diag.line = 0;
                diag.character = 0;
                diag.end_line = 0;
                diag.end_character = 1;
                diag.severity = 1;
                diag.message = e.what();
                diagnostics.push_back(diag);
            }
        }
    }
};

class LSPDependencyGraph {
public:
    std::unordered_map<std::string, std::vector<std::string>> file_dependencies;

    void record_import(const std::string& file_uri, const std::string& imported_path) {
        file_dependencies[imported_path].push_back(file_uri);
    }

    void invalidate(const std::string& changed_uri, std::unordered_map<std::string, DocumentSnapshot>& snapshots) {
        auto it = snapshots.find(changed_uri);
        if (it != snapshots.end()) {
            it->second.type_check_valid = false;
        }
        auto dep_it = file_dependencies.find(changed_uri);
        if (dep_it != file_dependencies.end()) {
            for (const auto& dependent : dep_it->second) {
                if (snapshots.count(dependent)) {
                    snapshots[dependent].type_check_valid = false;
                }
            }
        }
    }
};

struct CompletionCandidate {
    std::string label;
    std::string detail;
    int score = 0;
    bool proven = false;
};

class ProofAwareCompletionEngine {
public:
    static std::vector<CompletionCandidate> complete_hole(
        const Frontend::AST::TypedHoleExpr& hole,
        const std::shared_ptr<TypeSystem>& ts) {

        std::vector<CompletionCandidate> results;
        if (!ts) return results;

        for (const auto& [name, type] : hole.lexical_bindings) {
            if (!type) continue;
            CompletionCandidate cand;
            cand.label = name;
            cand.detail = type->toString();

            if (hole.expected_type) {
                if (type->toString() == hole.expected_type->toString()) {
                    cand.score = 100;
                    cand.proven = true;
                } else if (ts->isCompatible(hole.expected_type, type)) {
                    cand.score = 80;
                    cand.proven = true;
                } else {
                    cand.score = 10;
                    cand.proven = false;
                }

                if (hole.expected_type->tag == ::TypeTag::Refined) {
                    if (const auto* refined = std::get_if<RefinedType>(&hole.expected_type->extra)) {
                        auto var_expr = std::make_shared<Frontend::AST::VariableExpr>();
                        var_expr->name = name;
                        Frontend::SMTProofResult proof = Frontend::SMTVerifier::verify_refinement(refined->condition, var_expr);
                        if (proof.status == Frontend::SMTProofStatus::Proven) {
                            cand.score += 20;
                            cand.proven = true;
                        } else if (proof.status == Frontend::SMTProofStatus::Counterexample) {
                            cand.score = 0;
                            cand.proven = false;
                        }
                    }
                }
            } else {
                cand.score = 50;
            }
            results.push_back(cand);
        }

        std::sort(results.begin(), results.end(), [](const CompletionCandidate& a, const CompletionCandidate& b) {
            return a.score > b.score;
        });

        return results;
    }
};

static std::unordered_map<std::string, DocumentSnapshot> g_document_snapshots;
static LSPDependencyGraph g_dependency_graph;

static void send_json_rpc(const Json::Value& val) {
    std::string payload = val.serialize();
    std::cout << "Content-Length: " << payload.size() << "\r\n\r\n" << payload;
    std::cout.flush();
}

static void send_publish_diagnostics(const std::string& uri, int version, const std::vector<LSPDiagnostic>& diags) {
    Json::Value notif = Json::Value::object();
    notif["jsonrpc"] = "2.0";
    notif["method"] = "textDocument/publishDiagnostics";

    Json::Value params = Json::Value::object();
    params["uri"] = uri;
    if (version >= 0) {
        params["version"] = version;
    }

    Json::Value diag_arr = Json::Value::array();
    for (const auto& d : diags) {
        Json::Value item = Json::Value::object();
        Json::Value range = Json::Value::object();
        Json::Value start = Json::Value::object();
        start["line"] = d.line;
        start["character"] = d.character;
        Json::Value end = Json::Value::object();
        end["line"] = d.end_line;
        end["character"] = d.end_character;
        range["start"] = start;
        range["end"] = end;

        item["range"] = range;
        item["severity"] = d.severity;
        item["message"] = d.message;
        item["source"] = d.source;
        diag_arr.push_back(item);
    }
    params["diagnostics"] = diag_arr;
    notif["params"] = params;

    send_json_rpc(notif);
}

static size_t get_cursor_offset(const std::string& content, int line, int character) {
    int cur_line = 0;
    int cur_col = 0;
    for (size_t i = 0; i < content.size(); ++i) {
        if (cur_line == line && cur_col == character) {
            return i;
        }
        if (content[i] == '\n') {
            cur_line++;
            cur_col = 0;
        } else {
            cur_col++;
        }
    }
    return content.size();
}

static void get_word_at_offset(const std::string& content, size_t cursor_idx,
                               size_t& word_start, size_t& word_end) {
    word_start = cursor_idx;
    word_end = cursor_idx;
    if (content.empty()) return;
    if (cursor_idx > content.size()) cursor_idx = content.size();

    size_t s = cursor_idx;
    if (s > 0 && !std::isalnum(content[s]) && content[s] != '_' &&
        (std::isalnum(content[s - 1]) || content[s - 1] == '_')) {
        s--;
    }
    while (s > 0 && (std::isalnum(content[s - 1]) || content[s - 1] == '_')) {
        s--;
    }
    size_t e = s;
    while (e < content.size() && (std::isalnum(content[e]) || content[e] == '_')) {
        e++;
    }
    word_start = s;
    word_end = e;
}

struct ReceiverContext {
    bool is_member_access = false;
    std::string receiver;
    std::string member_prefix;
};

static ReceiverContext extract_receiver_context(const std::string& content, size_t cursor_idx) {
    ReceiverContext ctx;
    if (content.empty() || cursor_idx > content.size()) return ctx;

    size_t p = cursor_idx;
    while (p > 0 && (std::isalnum(content[p - 1]) || content[p - 1] == '_')) {
        p--;
    }
    ctx.member_prefix = content.substr(p, cursor_idx - p);

    size_t dot_p = p;
    while (dot_p > 0 && (content[dot_p - 1] == ' ' || content[dot_p - 1] == '\t')) {
        dot_p--;
    }

    if (dot_p > 0 && content[dot_p - 1] == '.') {
        ctx.is_member_access = true;
        size_t r_end = dot_p - 1;
        while (r_end > 0 && (content[r_end - 1] == ' ' || content[r_end - 1] == '\t')) {
            r_end--;
        }
        size_t r_start = r_end;
        while (r_start > 0 && (std::isalnum(content[r_start - 1]) || content[r_start - 1] == '_' || content[r_start - 1] == '.')) {
            r_start--;
        }
        ctx.receiver = content.substr(r_start, r_end - r_start);
    }

    return ctx;
}

enum class SymbolTypeCategory {
    Unknown,
    Frame,
    Trait,
    Module,
    Enum
};

struct ResolvedReceiver {
    SymbolTypeCategory category = SymbolTypeCategory::Unknown;
    std::string name;
};

static ResolvedReceiver resolve_receiver(const std::string& receiver,
                                         int line,
                                         const DocumentSnapshot& snap) {
    ResolvedReceiver res;
    if (receiver.empty()) return res;

    auto current_ast = snap.get_ast();

    // 1. self keyword
    if (receiver == "self") {
        if (current_ast) {
            for (const auto& stmt : current_ast->statements) {
                if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    for (const auto& m : f->methods) {
                        if (m->line <= line + 1) {
                            res.category = SymbolTypeCategory::Frame;
                            res.name = f->name;
                        }
                    }
                    if (f->init && f->init->line <= line + 1) {
                        res.category = SymbolTypeCategory::Frame;
                        res.name = f->name;
                    }
                    if (res.category == SymbolTypeCategory::Frame) return res;
                }
            }
            for (const auto& stmt : current_ast->statements) {
                if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    res.category = SymbolTypeCategory::Frame;
                    res.name = f->name;
                    return res;
                }
            }
        }
    }

    // 2. Module via import aliases or registered modules
    if (snap.last_check_result.has_value()) {
        const auto& aliases = snap.last_check_result->import_aliases;
        std::string mod_target = receiver;
        auto alias_it = aliases.find(receiver);
        if (alias_it != aliases.end()) {
            mod_target = alias_it->second;
        }
        if (snap.last_check_result->registered_modules.count(mod_target) ||
            snap.last_check_result->registered_modules.count(receiver)) {
            res.category = SymbolTypeCategory::Module;
            res.name = snap.last_check_result->registered_modules.count(mod_target) ? mod_target : receiver;
            return res;
        }
    }
    auto mod_ptr = Frontend::ModuleManager::getInstance().get_module(receiver);
    if (mod_ptr) {
        res.category = SymbolTypeCategory::Module;
        res.name = receiver;
        return res;
    }

    // 3. Variable types from type checker
    if (snap.last_check_result.has_value()) {
        auto var_it = snap.last_check_result->variable_types.find(receiver);
        if (var_it != snap.last_check_result->variable_types.end() && var_it->second) {
            auto type = var_it->second;
            if (type->tag == TypeTag::Frame) {
                if (const auto* ft = std::get_if<FrameType>(&type->extra)) {
                    res.category = SymbolTypeCategory::Frame;
                    res.name = ft->name;
                    return res;
                }
            }
        }
    }

    // 4. Check AST variables (including local variables in functions, methods, blocks)
    auto inspect_var = [&](const std::shared_ptr<Frontend::AST::VarDeclaration>& var_decl) -> bool {
        if (!var_decl || var_decl->name != receiver) return false;
        if (line > 0 && var_decl->line > line + 1) return false;

        if (var_decl->inferred_type && var_decl->inferred_type->tag == TypeTag::Frame) {
            if (const auto* ft = std::get_if<FrameType>(&var_decl->inferred_type->extra)) {
                res.category = SymbolTypeCategory::Frame;
                res.name = ft->name;
                return true;
            }
        }
        if (var_decl->type.has_value() && var_decl->type.value()) {
            std::string tname = var_decl->type.value()->typeName;
            res.category = SymbolTypeCategory::Frame;
            res.name = tname;
            return true;
        }
        if (var_decl->initializer) {
            if (auto fi = std::dynamic_pointer_cast<Frontend::AST::FrameInstantiationExpr>(var_decl->initializer)) {
                res.category = SymbolTypeCategory::Frame;
                res.name = fi->frameName;
                return true;
            }
            if (auto call = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(var_decl->initializer)) {
                if (call->inferred_type && call->inferred_type->tag == TypeTag::Frame) {
                    if (const auto* ft = std::get_if<FrameType>(&call->inferred_type->extra)) {
                        res.category = SymbolTypeCategory::Frame;
                        res.name = ft->name;
                        return true;
                    }
                }
                if (auto mem = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(call->callee)) {
                    res.category = SymbolTypeCategory::Frame;
                    res.name = mem->name;
                    return true;
                }
                if (auto var_c = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(call->callee)) {
                    res.category = SymbolTypeCategory::Frame;
                    res.name = var_c->name;
                    return true;
                }
            }
        }
        return false;
    };

    std::function<bool(const std::shared_ptr<Frontend::AST::Statement>&)> walk_stmt;
    walk_stmt = [&](const std::shared_ptr<Frontend::AST::Statement>& stmt) -> bool {
        if (!stmt) return false;
        if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
            if (inspect_var(var_decl)) return true;
        } else if (auto fn_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            for (const auto& p : fn_decl->params) {
                if (p.first == receiver && p.second) {
                    res.category = SymbolTypeCategory::Frame;
                    res.name = p.second->typeName;
                    return true;
                }
            }
            if (fn_decl->body && walk_stmt(fn_decl->body)) return true;
        } else if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
            for (const auto& s : block->statements) {
                if (walk_stmt(s)) return true;
            }
        } else if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
            if (if_stmt->thenBranch && walk_stmt(if_stmt->thenBranch)) return true;
            if (if_stmt->elseBranch && walk_stmt(if_stmt->elseBranch)) return true;
        } else if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
            if (while_stmt->body && walk_stmt(while_stmt->body)) return true;
        } else if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
            if (for_stmt->initializer && walk_stmt(for_stmt->initializer)) return true;
            if (for_stmt->body && walk_stmt(for_stmt->body)) return true;
        } else if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
            if (iter_stmt->body && walk_stmt(iter_stmt->body)) return true;
        } else if (auto frame_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            if (frame_decl->init && frame_decl->init->body && walk_stmt(frame_decl->init->body)) return true;
            if (frame_decl->deinit && frame_decl->deinit->body && walk_stmt(frame_decl->deinit->body)) return true;
            for (const auto& m : frame_decl->methods) {
                if (m && m->body && walk_stmt(m->body)) return true;
            }
        }
        return false;
    };

    if (current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (walk_stmt(stmt)) return res;
        }
    }
    if (snap.last_check_result.has_value() && snap.last_check_result->program) {
        for (const auto& stmt : snap.last_check_result->program->statements) {
            if (walk_stmt(stmt)) return res;
        }
    }

    // 5. Frame name directly
    if (snap.last_check_result.has_value() && snap.last_check_result->frame_declarations.count(receiver)) {
        res.category = SymbolTypeCategory::Frame;
        res.name = receiver;
        return res;
    }
    if (current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (f->name == receiver) {
                    res.category = SymbolTypeCategory::Frame;
                    res.name = receiver;
                    return res;
                }
            }
        }
    }

    // 6. Trait name
    if (snap.last_check_result.has_value() && snap.last_check_result->trait_declarations.count(receiver)) {
        res.category = SymbolTypeCategory::Trait;
        res.name = receiver;
        return res;
    }
    if (current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                if (t->name == receiver) {
                    res.category = SymbolTypeCategory::Trait;
                    res.name = receiver;
                    return res;
                }
            }
        }
    }

    // 7. Enum name
    if (current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                if (e->name == receiver) {
                    res.category = SymbolTypeCategory::Enum;
                    res.name = receiver;
                    return res;
                }
            }
        }
    }

    // 8. Text heuristic fallback for live-typing: search for "var/val/const <receiver> : <Type>" or "= <Type> {"
    try {
        std::regex rx_decl("(?:var|val|const)\\s+" + receiver + "\\s*:\\s*([A-Za-z_][A-Za-z0-9_]*)");
        std::smatch match;
        if (std::regex_search(snap.content, match, rx_decl)) {
            res.category = SymbolTypeCategory::Frame;
            res.name = match[1].str();
            return res;
        }
        std::regex rx_init("(?:var|val|const)\\s+" + receiver + "\\s*=\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*[\\{\\(]");
        if (std::regex_search(snap.content, match, rx_init)) {
            res.category = SymbolTypeCategory::Frame;
            res.name = match[1].str();
            return res;
        }
    } catch (...) {}

    return res;
}

static std::string format_method_signature(const std::shared_ptr<Frontend::AST::FrameMethod>& m, const std::string& frame_name = "") {
    std::string sig = "pub fn ";
    if (!frame_name.empty()) sig += frame_name + ".";
    sig += m->name + "(";
    bool first = true;
    for (const auto& p : m->parameters) {
        if (!first) sig += ", ";
        sig += p.first;
        if (p.second) sig += ": " + p.second->typeName + (p.second->isOptional ? "?" : "");
        first = false;
    }
    for (const auto& op : m->optionalParams) {
        if (!first) sig += ", ";
        sig += op.first + "?";
        if (op.second.first) sig += ": " + op.second.first->typeName;
        first = false;
    }
    sig += ")";
    if (m->returnType) {
        sig += ": " + m->returnType->typeName + (m->returnType->isOptional ? "?" : "");
    }
    return sig;
}

static std::string format_func_signature(const std::shared_ptr<Frontend::AST::FunctionDeclaration>& fn) {
    std::string sig = "fn " + fn->name + "(";
    bool first = true;
    for (const auto& p : fn->params) {
        if (!first) sig += ", ";
        sig += p.first;
        if (p.second) sig += ": " + p.second->typeName + (p.second->isOptional ? "?" : "");
        first = false;
    }
    for (const auto& op : fn->optionalParams) {
        if (!first) sig += ", ";
        sig += op.first + "?";
        if (op.second.first) sig += ": " + op.second.first->typeName;
        first = false;
    }
    sig += ")";
    if (fn->returnType.has_value() && fn->returnType.value()) {
        sig += ": " + fn->returnType.value()->typeName + (fn->returnType.value()->isOptional ? "?" : "");
    } else if (fn->inferred_type) {
        sig += ": " + fn->inferred_type->toString();
    }
    return sig;
}

static int find_block_end(const std::string& content, int start_line) {
    std::istringstream iss(content);
    std::string sline;
    int cur_line = 0;
    int brace_count = 0;
    bool found_open_brace = false;

    while (std::getline(iss, sline)) {
        if (cur_line >= start_line) {
            for (char ch : sline) {
                if (ch == '{') {
                    brace_count++;
                    found_open_brace = true;
                } else if (ch == '}') {
                    brace_count--;
                    if (found_open_brace && brace_count == 0) {
                        return cur_line;
                    }
                }
            }
        }
        cur_line++;
    }
    return start_line + 2;
}

// -----------------------------------------------------------------------------
// Language Documentation & Metadata Tables
// -----------------------------------------------------------------------------

struct KeywordDoc {
    const char* keyword;
    const char* summary;
    const char* syntax;
    const char* description;
};

static const std::vector<KeywordDoc> kKeywords = {
    // Control flow
    { "if", "Conditional branch", "if (condition) { ... }", "Executes the following block if the condition evaluates to true." },
    { "else", "Alternative conditional branch", "if (x) { ... } else { ... }", "Executes when the preceding if/elif condition is false." },
    { "elif", "Else-if conditional branch", "if (x) { ... } elif (y) { ... }", "Tests a secondary condition when preceding if/elif conditions evaluate to false." },
    { "for", "C-style iteration loop", "for (var i = 0; i < n; i += 1) { ... }", "Iterates with an initializer, loop condition, and increment expression." },
    { "iter", "Collection and range iterator loop", "iter (item in collection) { ... }", "Iterates over elements in lists, maps, streams, or integer ranges (e.g. `1..10`)." },
    { "while", "Condition-controlled loop", "while (condition) { ... }", "Executes the block repeatedly while the condition remains true." },
    { "match", "Pattern matching expression", "match (val) { pattern => { ... } }", "Matches a value against structured patterns including variants, val/err fallibles, and ranges." },
    { "break", "Loop termination statement", "break;", "Terminates the innermost executing loop immediately." },
    { "continue", "Next loop iteration statement", "continue;", "Skips the rest of the current iteration and begins the next loop cycle." },
    { "return", "Function return statement", "return value;", "Exits the current function, optionally returning a value." },

    // Concurrency & Tasks
    { "task", "Parallel task spawning", "task(i in 1..10) { ... }", "Spawns concurrent asynchronous units of execution across available threads." },
    { "worker", "Concurrent stream processing worker", "worker(data in stream) { ... }", "Processes incoming stream or channel data concurrently." },
    { "async", "Asynchronous function modifier", "async fn fetch(): str { ... }", "Declares an asynchronous function returning a future." },
    { "await", "Asynchronous value resolution", "var res = await async_task();", "Suspends execution until the awaited asynchronous future completes." },
    { "unsafe", "Unsafe execution block", "unsafe { ... }", "Allows low-level operations, unchecked pointers, and foreign memory interaction." },
    { "staged", "Staged compile-time block", "staged { ... }", "Executes code during compilation for metaprogramming and code generation." },
    { "defer", "Deferred cleanup statement", "defer { cleanup(); }", "Guarantees execution of the enclosed block upon exiting the current function scope." },
    { "parallel", "Data-parallel execution block", "parallel(cores=4) { ... }", "Distributes execution of operations across multiple CPU cores." },
    { "concurrent", "Channel-based concurrent block", "concurrent(cores=2) { ... }", "Executes concurrent channel-communicating tasks with cooperative scheduling." },

    // Declarations & OOP
    { "fn", "Function declaration", "fn name(param: Type): ReturnType { ... }", "Defines a named function with typed parameters and return value." },
    { "type", "Type alias or definition", "type UserId = int;", "Defines a type alias, union type, intersection type, or refined type constraint." },
    { "frame", "Class-like OOP frame declaration", "frame Name { pub field: int; pub init(...) { ... } }", "Lymar's canonical object-oriented structure supporting public/protected fields, methods, constructors, and trait conformance." },
    { "class", "Class declaration (OOP frame alias)", "class Name { ... }", "Class-like structure declaration, interoperable with frame semantics." },
    { "trait", "Interface contract declaration", "trait Shape { fn area(): int; }", "Defines an abstract interface of method requirements that frames can implement." },
    { "interface", "Interface definition", "interface Printable { fn to_str(): str; }", "Defines a contract of methods implemented by types." },
    { "mixin", "Reusable method mixin", "mixin Loggable { ... }", "Declares a reusable set of methods composable into frames." },
    { "implements", "Trait or interface conformance", "frame Square: Shape { ... }", "Specifies the traits implemented by a frame." },
    { "impl", "Trait implementation block", "impl Trait for Frame { ... }", "Implements methods of a trait for a given frame or type." },
    { "enum", "Enumeration declaration", "enum Color { Red, Green, Blue }", "Defines a type with a fixed set of named variants, optionally holding associated values." },
    { "module", "Module declaration", "module Math { ... }", "Defines a modular namespace encapsulating types, functions, and constants." },
    { "import", "Module import declaration", "import std.collections show List;", "Imports a module or specific symbols into the current compilation scope." },
    { "from", "Module import source clause", "from std.math import sqrt;", "Specifies the module source path for an import statement." },
    { "export", "Module symbol export", "export fn calculate(): int { ... }", "Exposes a symbol for use outside the defining module." },
    { "var", "Mutable variable declaration", "var x: int = 42;", "Declares a mutable variable that can be reassigned." },
    { "val", "Immutable local binding", "val y = 100;", "Binds an immutable local variable that cannot be reassigned." },
    { "const", "Constant declaration", "const PI = 3.14159;", "Defines an immutable compile-time constant." },
    { "mut", "Mutability modifier", "mut var ref;", "Explicitly designates a reference or binding as mutable." },
    { "atomic", "Atomic thread-safe primitive", "var counter: atomic = 0;", "Declares a thread-safe primitive updated with atomic operations." },

    // Modifiers & Visibility
    { "pub", "Public visibility modifier", "pub fn process(): void { ... }", "Makes a field, method, or symbol accessible outside its containing frame or module." },
    { "prot", "Protected visibility modifier", "prot field: int;", "Makes a field or method accessible only within its frame and inheriting frames." },
    { "static", "Static member modifier", "static fn create(): Frame { ... }", "Associates a method or field with the frame type rather than instances." },
    { "abstract", "Abstract method or frame modifier", "abstract fn render(): void;", "Declares a method requirement without an implementation body." },
    { "final", "Final modifier", "final fn compute(): int { ... }", "Prevents a frame from being inherited or a method from being overridden." },
    { "show", "Selective import filter", "import std.collections show Iterator;", "Whitelists specific symbols to import from a module." },
    { "hide", "Hiding import filter", "import std.io hide raw_read;", "Blacklists specific symbols from being imported from a module." },

    // Lifecycle
    { "init", "Frame constructor lifecycle method", "pub init(w: int, h: int) { self.w = w; }", "Special lifecycle method invoked during instance construction." },
    { "deinit", "Frame destructor lifecycle method", "pub deinit() { cleanup(); }", "Special lifecycle method invoked when an instance is destroyed." },

    // Operators & Predicates
    { "and", "Logical AND operator", "if (a and b) { ... }", "Boolean conjunction operator, short-circuiting on false." },
    { "or", "Logical OR operator", "if (a or b) { ... }", "Boolean disjunction operator, short-circuiting on true." },
    { "not", "Logical NOT operator", "if (not flag) { ... }", "Boolean negation operator keyword." },
    { "in", "Iteration and membership operator", "iter (x in list)", "Used in iterator loops and membership verification tests." },
    { "as", "Explicit type cast operator", "val f = x as float;", "Performs explicit static type conversion between compatible types." },
    { "is", "Type checking operator", "if (val is int) { ... }", "Tests whether a value matches a specific runtime or compile-time type." },
    { "where", "Refined type constraint clause", "type Positive = int where value > 0;", "Attaches an SMT-verifiable predicate constraint to a base type." },

    // Error Handling
    { "ok", "Fallible success constructor", "return ok(result);", "Constructs a success value for a fallible function return (`T?`)." },
    { "err", "Fallible error constructor", "return err(DivisionByZero);", "Constructs an error value for a fallible function return (`T?Error`)." },

    // Special
    { "self", "Current instance reference", "self.width = w;", "Canonical self-reference inside frame methods (`this` is unsupported)." },
    { "super", "Parent frame reference", "super.init();", "Refers to the parent frame's members or constructor." },
    { "contract", "Runtime contract assertion", "contract(x > 0, \"Must be positive\");", "Enforces a contract condition verified at runtime or statically proven." },
    { "true", "Boolean true literal", "var flag = true;", "Boolean literal representing truth." },
    { "false", "Boolean false literal", "var flag = false;", "Boolean literal representing falsehood." },
    { "nil", "Null / absence literal", "var opt: str? = nil;", "Represents the absence of a value for optional and reference types." }
};

struct BuiltinTypeDoc {
    const char* name;
    const char* summary;
    const char* details;
};

static const std::vector<BuiltinTypeDoc> kBuiltinTypes = {
    // Integers
    { "int", "Signed integer (native platform / 64-bit)", "Standard signed integer type with platform-native bit-width (64-bit on 64-bit systems)." },
    { "uint", "Unsigned integer (native platform / 64-bit)", "Standard unsigned integer type for non-negative values." },
    { "i8", "8-bit signed integer", "Signed 8-bit integer with range from -128 to 127." },
    { "i16", "16-bit signed integer", "Signed 16-bit integer with range from -32,768 to 32,767." },
    { "i32", "32-bit signed integer", "Signed 32-bit integer with range from -2,147,483,648 to 2,147,483,647." },
    { "i64", "64-bit signed integer", "Signed 64-bit integer with range from -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807." },
    { "i128", "128-bit signed integer", "Signed 128-bit wide integer for high-precision arithmetic." },
    { "u8", "8-bit unsigned integer / byte", "Unsigned 8-bit integer with range from 0 to 255." },
    { "u16", "16-bit unsigned integer", "Unsigned 16-bit integer with range from 0 to 65,535." },
    { "u32", "32-bit unsigned integer", "Unsigned 32-bit integer with range from 0 to 4,294,967,295." },
    { "u64", "64-bit unsigned integer", "Unsigned 64-bit integer with range from 0 to 18,446,744,073,709,551,615." },
    { "u128", "128-bit unsigned integer", "Unsigned 128-bit wide integer for high-precision arithmetic." },

    // Floats & Decimals
    { "float", "Double-precision floating point (64-bit IEEE 754)", "Standard IEEE 754 double-precision floating-point type." },
    { "f32", "Single-precision float (32-bit IEEE 754)", "IEEE 754 32-bit single-precision floating-point number." },
    { "f64", "Double-precision float (64-bit IEEE 754)", "IEEE 754 64-bit double-precision floating-point number." },
    { "d2", "Fixed decimal with 2 decimal digits", "Exact fixed-point decimal type with 2 fractional digits, ideal for currency." },
    { "d4", "Fixed decimal with 4 decimal digits", "Exact fixed-point decimal type with 4 fractional digits." },
    { "d6", "Fixed decimal with 6 decimal digits", "Exact fixed-point decimal type with 6 fractional digits." },
    { "decimal", "Fixed-precision decimal", "High-precision exact fixed-point decimal type preventing floating-point rounding errors." },

    // Primitives & System
    { "bool", "Boolean type (`true` or `false`)", "Logical boolean value." },
    { "str", "UTF-8 string type", "Immutable UTF-8 encoded string sequence with string interpolation support (`{var}`)." },
    { "any", "Dynamic escape-hatch type", "Represents an unconstrained dynamic value, checked at runtime." },
    { "nil", "Null / None type", "Represents absence of value. Used in optional union types (`Type?` = `Type | nil`)." },
    { "channel", "Concurrency communication channel", "Thread-safe FIFO message channel for concurrent task communication." },
    { "atomic", "Atomic thread-safe primitive", "Thread-safe atomic integer or reference with lock-free atomic hardware guarantees." },

    // Collections & Compounds
    { "list", "Homogeneous list collection: `[T]`", "Dynamic ordered collection of elements of uniform type." },
    { "dict", "Key-value dictionary collection: `{K: V}`", "Hash map mapping key types to value types." },
    { "tuple", "Heterogeneous tuple: `(T1, T2)`", "Fixed-size product type holding multiple heterogeneous values accessed via dot indexing (e.g. `t.0`)." },
    { "Option", "Optional wrapper type", "Represents a value that may be present (`Some`) or absent (`nil`)." },
    { "Result", "Fallible result type", "Represents either a success value (`ok`) or an error (`err`)." },
    { "Error", "Base error type", "Base error structure used with fallible functions and the `?` propagator." }
};

struct BuiltinFuncDoc {
    const char* name;
    const char* signature;
    const char* snippet;
    const char* summary;
    std::vector<std::pair<std::string, std::string>> params;
    const char* return_type;
};

static const std::vector<BuiltinFuncDoc> kBuiltinFunctions = {
    { "print", "fn print(...values: any): void", "print(${1:value})", "Prints values to standard output without trailing newline.", {{"...values: any", "Values to print"}}, "void" },
    { "println", "fn println(...values: any): void", "println(${1:value})", "Prints values followed by a newline to standard output.", {{"...values: any", "Values to print"}}, "void" },
    { "len", "fn len(collection: any): int", "len(${1:collection})", "Returns the number of elements in a list, string, dictionary, or tuple.", {{"collection: any", "Target collection or string"}}, "int" },
    { "append", "fn append(list: [any], item: any): void", "append(${1:list}, ${2:item})", "Appends a single item or all elements from another list to the target list.", {{"list: [any]", "Target list"}, {"item: any", "Item or list to append"}}, "void" },
    { "pop", "fn pop(list: [any]): any", "pop(${1:list})", "Removes and returns the last element from a list.", {{"list: [any]", "Target list"}}, "any" },
    { "insert", "fn insert(list: [any], index: int, item: any): void", "insert(${1:list}, ${2:index}, ${3:item})", "Inserts an element into a list at the specified zero-based index.", {{"list: [any]", "Target list"}, {"index: int", "Zero-based index"}, {"item: any", "Item to insert"}}, "void" },
    { "remove", "fn remove(list: [any], index: int): any", "remove(${1:list}, ${2:index})", "Removes and returns the element at the specified index in a list.", {{"list: [any]", "Target list"}, {"index: int", "Zero-based index"}}, "any" },
    { "keys", "fn keys(dict: {any: any}): [any]", "keys(${1:dict})", "Returns a list containing all keys from a dictionary.", {{"dict: {any: any}", "Target dictionary"}}, "[any]" },
    { "values", "fn values(dict: {any: any}): [any]", "values(${1:dict})", "Returns a list containing all values from a dictionary.", {{"dict: {any: any}", "Target dictionary"}}, "[any]" },
    { "has", "fn has(dict: {any: any}, key: any): bool", "has(${1:dict}, ${2:key})", "Checks if a dictionary contains the specified key.", {{"dict: {any: any}", "Target dictionary"}, {"key: any", "Key to look up"}}, "bool" },
    { "get", "fn get(dict: {any: any}, key: any, default_value: any): any", "get(${1:dict}, ${2:key}, ${3:default_value})", "Returns the value for a key in a dictionary, or the default value if absent.", {{"dict: {any: any}", "Target dictionary"}, {"key: any", "Key to look up"}, {"default_value: any", "Fallback default"}}, "any" },
    { "set", "fn set(dict: {any: any}, key: any, value: any): void", "set(${1:dict}, ${2:key}, ${3:value})", "Associates a key with a value in a dictionary.", {{"dict: {any: any}", "Target dictionary"}, {"key: any", "Key to set"}, {"value: any", "Value to assign"}}, "void" },
    { "str", "fn str(value: any): str", "str(${1:value})", "Converts a value to its string representation.", {{"value: any", "Value to convert"}}, "str" },
    { "int", "fn int(value: any): int", "int(${1:value})", "Converts a numeric value or string to an integer.", {{"value: any", "Value to convert"}}, "int" },
    { "float", "fn float(value: any): float", "float(${1:value})", "Converts a numeric value or string to a float.", {{"value: any", "Value to convert"}}, "float" },
    { "bool", "fn bool(value: any): bool", "bool(${1:value})", "Converts a value to a boolean.", {{"value: any", "Value to convert"}}, "bool" },
    { "type_of", "fn type_of(value: any): str", "type_of(${1:value})", "Returns the runtime type name of a value as a string.", {{"value: any", "Value to inspect"}}, "str" },
    { "assert", "fn assert(condition: bool, message: str): void", "assert(${1:condition}, \"${2:assertion failed}\")", "Asserts that condition is true; halts with an error message otherwise.", {{"condition: bool", "Condition to verify"}, {"message: str", "Failure message"}}, "void" },
    { "panic", "fn panic(message: str): void", "panic(\"${1:fatal error}\")", "Terminates execution immediately with an unrecoverable error message.", {{"message: str", "Panic error message"}}, "void" },
    { "range", "fn range(start: int, end: int, step: int = 1): [int]", "range(${1:start}, ${2:end}, ${3:1})", "Generates an integer sequence from start up to end.", {{"start: int", "Start value"}, {"end: int", "End boundary"}, {"step: int", "Step increment (default 1)"}}, "[int]" },
    { "abs", "fn abs(n: float): float", "abs(${1:n})", "Returns the absolute value of a numeric value.", {{"n: float", "Numeric input"}}, "float" },
    { "min", "fn min(a: any, b: any): any", "min(${1:a}, ${2:b})", "Returns the smaller of two comparable values.", {{"a: any", "First value"}, {"b: any", "Second value"}}, "any" },
    { "max", "fn max(a: any, b: any): any", "max(${1:a}, ${2:b})", "Returns the larger of two comparable values.", {{"a: any", "First value"}, {"b: any", "Second value"}}, "any" },
    { "sleep", "fn sleep(ms: int): void", "sleep(${1:ms})", "Suspends the current execution thread for milliseconds.", {{"ms: int", "Milliseconds to pause"}}, "void" },
    { "exit", "fn exit(code: int): void", "exit(${1:0})", "Terminates the host process with the specified exit code.", {{"code: int", "Exit status code"}}, "void" },
    { "clock", "fn clock(): float", "clock()", "Returns current monotonic high-resolution clock time in seconds.", {}, "float" },
    { "join", "fn join(list: [str], separator: str): str", "join(${1:list}, ${2:\", \"})", "Joins a list of strings into a single string with a delimiter.", {{"list: [str]", "Strings to concatenate"}, {"separator: str", "Delimiter string"}}, "str" },
    { "split", "fn split(str: str, separator: str): [str]", "split(${1:str}, ${2:\",\"})", "Splits a string by a delimiter into a list of strings.", {{"str: str", "Source string"}, {"separator: str", "Delimiter string"}}, "[str]" },
    { "replace", "fn replace(str: str, old: str, new_val: str): str", "replace(${1:str}, ${2:old}, ${3:new})", "Replaces occurrences of a substring with a replacement string.", {{"str: str", "Source string"}, {"old: str", "Substring to find"}, {"new_val: str", "Replacement"}}, "str" },
    { "trim", "fn trim(str: str): str", "trim(${1:str})", "Removes leading and trailing whitespace from a string.", {{"str: str", "Source string"}}, "str" },
    { "matches", "fn matches(value: str, pattern: str): bool", "matches(${1:value}, ${2:pattern})", "Tests whether a string matches a regular expression pattern.", {{"value: str", "Input string"}, {"pattern: str", "Regex pattern"}}, "bool" },
    { "open", "fn open(filename: str, mode: str): any", "open(${1:filename}, ${2:\"r\"})", "Opens a file resource in read ('r'), write ('w'), or append ('a') mode.", {{"filename: str", "File path"}, {"mode: str", "Mode string"}}, "any" },
    { "map", "fn map(items: [any], fn: (any) -> any): [any]", "map(${1:items}, ${2:fn})", "Transforms each item in a collection using a mapping function.", {{"items: [any]", "Input collection"}, {"fn: (any) -> any", "Transformation lambda"}}, "[any]" },
    { "filter", "fn filter(items: [any], predicate: (any) -> bool): [any]", "filter(${1:items}, ${2:predicate})", "Filters a collection using a predicate function.", {{"items: [any]", "Input collection"}, {"predicate: (any) -> bool", "Filter predicate"}}, "[any]" },
    { "reduce", "fn reduce(items: [any], fn: (any, any) -> any, init: any): any", "reduce(${1:items}, ${2:fn}, ${3:init})", "Reduces a collection to a single value using an accumulator.", {{"items: [any]", "Input collection"}, {"fn: (any, any) -> any", "Accumulator lambda"}, {"init: any", "Initial seed value"}}, "any" },
    { "contract", "fn contract(condition: bool, message: str): void", "contract(${1:condition}, \"${2:contract failed}\")", "Enforces a contract invariant at runtime or statically verifies it.", {{"condition: bool", "Contract invariant condition"}, {"message: str", "Error message"}}, "void" },
    { "ok", "fn ok(value: any): any?", "ok(${1:value})", "Constructs a fallible success value.", {{"value: any", "Success payload"}}, "any?" },
    { "err", "fn err(error: any): any?", "err(${1:Error})", "Constructs a fallible error value.", {{"error: any", "Error type or object"}}, "any?" },
    { "is_error", "fn is_error(value: any): bool", "is_error(${1:value})", "Returns true if a fallible value contains an error.", {{"value: any", "Fallible value"}}, "bool" },
    { "is_success", "fn is_success(value: any): bool", "is_success(${1:value})", "Returns true if a fallible value contains a success result.", {{"value: any", "Fallible value"}}, "bool" }
};

struct DecoratorDoc {
    const char* label;
    const char* summary;
    const char* details;
};

static const std::vector<DecoratorDoc> kDecorators = {
    { "@public", "Marks a member as publicly accessible.", "Exposes the annotated member outside the declaring frame or file." },
    { "@private", "Marks a member as private to the current file.", "Restricts member access exclusively to the current declaration scope." },
    { "@protected", "Marks a member as protected.", "Restricts member access to the declaring frame and subframes." },
    { "@test", "Marks a function as a unit test.", "Registers the annotated function with the Lymar test framework." },
    { "@inline", "Requests compiler function inlining.", "Suggests to the optimizer that calls to this function should be inlined." },
    { "@pure", "Declares a function free of observable side effects.", "Informs the compiler that this function depends only on arguments with no mutations." },
    { "@tailrec", "Verifies and optimizes tail call recursion.", "Directs the compiler to guarantee constant-stack tail-call optimization." },
    { "@deprecated", "Marks a declaration as deprecated.", "Emits a compile-time warning whenever this symbol is used." },
    { "@entry", "Marks a function as an application entry point.", "Defines the executable main entry point for the compiled binary." },
    { "@benchmark", "Marks a function for performance benchmarking.", "Executes the function inside the compiler's benchmarking profiler." },
    { "@export", "Exports a symbol for dynamic linkage or FFI.", "Exports symbol symbol names into the binary export table for external linkers." }
};

struct SnippetDoc {
    const char* label;
    const char* insert_text;
    const char* documentation;
};

static const std::vector<SnippetDoc> kSnippets = {
    { "fn", "fn ${1:name}(${2:param}: ${3:Type}): ${4:ReturnType} {\n\t$0\n}", "Function definition with typed parameters and return type" },
    { "fn (simple)", "fn ${1:name}() {\n\t$0\n}", "Simple function without parameters" },
    { "fn (error handling)", "fn ${1:name}(${2:param}: ${3:Type}): ${4:ReturnType}?${5:ErrorType} {\n\t$0\n}", "Function with fallible error return type" },
    { "frame", "frame ${1:Name} {\n\tpub ${2:field}: ${3:int};\n\n\tpub init(${4:params}) {\n\t\t$0\n\t}\n}", "Frame declaration (canonical Lymar OOP structure)" },
    { "class", "class ${1:Name} {\n\tfn init(${2:params}) {\n\t\t$0\n\t}\n}", "Class definition with constructor" },
    { "trait", "trait ${1:Name} {\n\tfn ${2:method}(${3:params}): ${4:ReturnType};\n}", "Trait (interface) definition" },
    { "enum", "enum ${1:Name} {\n\t${2:Variant1},\n\t${3:Variant2}\n}", "Enum declaration with variants" },
    { "type", "type ${1:Name} = ${2:Type};", "Type alias declaration" },
    { "type (refined)", "type ${1:Name} = ${2:Type} where ${3:condition};", "Refined type with verifiable predicate constraint" },
    { "for", "for (var ${1:i} = 0; ${1:i} < ${2:n}; ${1:i} += 1) {\n\t$0\n}", "C-style for loop" },
    { "iter", "iter (${1:item} in ${2:collection}) {\n\t$0\n}", "Iterator loop over collection or stream" },
    { "iter (range)", "iter (${1:i} in ${2:start}..${3:end}) {\n\t$0\n}", "Range-based iterator loop (inclusive)" },
    { "while", "while (${1:condition}) {\n\t$0\n}", "Condition-controlled while loop" },
    { "if", "if (${1:condition}) {\n\t$0\n}", "Conditional branch" },
    { "if-else", "if (${1:condition}) {\n\t${2}\n} else {\n\t$0\n}", "If-else conditional statement" },
    { "match", "match (${1:value}) {\n\tval ${2:success} => { $3 },\n\terr ${4:error} => { $0 }\n}", "Pattern matching expression for fallible types" },
    { "? else", "${1:expression}? else {\n\t$0\n}", "Inline fallible error handler with fallback block" },
    { "contract", "contract(${1:condition}, \"${2:error message}\");", "Runtime contract assertion" },
    { "task", "task(${1:i} in ${2:1..10}) {\n\t$0\n}", "Parallel task spawn block" },
    { "worker", "worker(${1:data} in ${2:stream}) {\n\t$0\n}", "Concurrent worker stream processor" },
    { "parallel", "parallel(cores=${1:2}) {\n\t$0\n}", "Multi-core parallel execution block" },
    { "concurrent", "concurrent(cores=${1:2}) {\n\t$0\n}", "Channel-based concurrent block" }
};

// -----------------------------------------------------------------------------
// Completion Handler
// -----------------------------------------------------------------------------

static Json::Value handle_completion(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    int line = static_cast<int>(params["position"]["line"].as_int());
    int character = static_cast<int>(params["position"]["character"].as_int());

    Json::Value res = Json::Value::object();
    res["isIncomplete"] = false;
    Json::Value items = Json::Value::array();

    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) {
        res["items"] = items;
        return res;
    }

    const auto& snap = it->second;
    const auto& content = snap.content;
    auto current_ast = snap.get_ast();
    size_t cursor_idx = get_cursor_offset(content, line, character);

    // Extract line prefix up to cursor
    std::string before_cursor;
    size_t line_start = 0;
    int cur_l = 0;
    for (size_t i = 0; i < content.size(); ++i) {
        if (cur_l == line) {
            line_start = i;
            break;
        }
        if (content[i] == '\n') cur_l++;
    }
    if (cursor_idx >= line_start) {
        before_cursor = content.substr(line_start, cursor_idx - line_start);
    }

    // 1. Member access completion (dot access: receiver.member)
    ReceiverContext rctx = extract_receiver_context(content, cursor_idx);
    if (rctx.is_member_access) {
        ResolvedReceiver rec = resolve_receiver(rctx.receiver, line, snap);
        std::unordered_set<std::string> seen;

        if (rec.category == SymbolTypeCategory::Frame) {
            if (current_ast) {
                for (const auto& stmt : current_ast->statements) {
                    if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                        if (f->name == rec.name) {
                            for (const auto& field : f->fields) {
                                if (seen.insert(field->name).second) {
                                    Json::Value item = Json::Value::object();
                                    item["label"] = field->name;
                                    item["kind"] = 5; // Field
                                    item["detail"] = (field->type ? field->type->typeName : "field");
                                    item["insertText"] = field->name;
                                    item["sortText"] = "020_" + field->name;
                                    items.push_back(item);
                                }
                            }
                            if (f->init && seen.insert("init").second) {
                                Json::Value item = Json::Value::object();
                                item["label"] = "init";
                                item["kind"] = 9; // Constructor
                                item["detail"] = format_method_signature(f->init, f->name);
                                item["insertText"] = "init(${1})";
                                item["insertTextFormat"] = 2;
                                item["sortText"] = "010_init";
                                items.push_back(item);
                            }
                            if (f->deinit && seen.insert("deinit").second) {
                                Json::Value item = Json::Value::object();
                                item["label"] = "deinit";
                                item["kind"] = 2; // Method
                                item["detail"] = "pub deinit()";
                                item["insertText"] = "deinit()";
                                item["sortText"] = "010_deinit";
                                items.push_back(item);
                            }
                            for (const auto& m : f->methods) {
                                if (seen.insert(m->name).second) {
                                    Json::Value item = Json::Value::object();
                                    item["label"] = m->name;
                                    item["kind"] = 2; // Method
                                    item["detail"] = format_method_signature(m, f->name);
                                    item["insertText"] = m->parameters.empty() && m->optionalParams.empty() ? m->name + "()" : m->name + "(${1})";
                                    item["insertTextFormat"] = 2;
                                    item["sortText"] = "010_" + m->name;
                                    items.push_back(item);
                                }
                            }
                            for (const auto& trait_name : f->implements) {
                                for (const auto& tstmt : current_ast->statements) {
                                    if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(tstmt)) {
                                        if (t->name == trait_name) {
                                            for (const auto& m : t->methods) {
                                                if (seen.insert(m->name).second) {
                                                    Json::Value item = Json::Value::object();
                                                    item["label"] = m->name;
                                                    item["kind"] = 2; // Method
                                                    item["detail"] = format_func_signature(m);
                                                    item["insertText"] = m->params.empty() && m->optionalParams.empty() ? m->name + "()" : m->name + "(${1})";
                                                    item["insertTextFormat"] = 2;
                                                    item["sortText"] = "015_" + m->name;
                                                    items.push_back(item);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (snap.last_check_result.has_value()) {
                auto fit = snap.last_check_result->frame_declarations.find(rec.name);
                if (fit == snap.last_check_result->frame_declarations.end()) {
                    for (auto it = snap.last_check_result->frame_declarations.begin(); it != snap.last_check_result->frame_declarations.end(); ++it) {
                        if (it->first == rec.name || it->first.ends_with("." + rec.name)) {
                            fit = it;
                            break;
                        }
                    }
                }
                if (fit != snap.last_check_result->frame_declarations.end()) {
                    for (const auto& fld : fit->second.fields) {
                        if (seen.insert(fld.first).second) {
                            Json::Value item = Json::Value::object();
                            item["label"] = fld.first;
                            item["kind"] = 5; // Field
                            item["detail"] = fld.second ? fld.second->toString() : "field";
                            item["insertText"] = fld.first;
                            item["sortText"] = "020_" + fld.first;
                            items.push_back(item);
                        }
                    }
                    if (fit->second.declaration) {
                        const auto& f = fit->second.declaration;
                        if (f->init && seen.insert("init").second) {
                            Json::Value item = Json::Value::object();
                            item["label"] = "init";
                            item["kind"] = 9; // Constructor
                            item["detail"] = format_method_signature(f->init, f->name);
                            item["insertText"] = "init(${1})";
                            item["insertTextFormat"] = 2;
                            item["sortText"] = "010_init";
                            items.push_back(item);
                        }
                        if (f->deinit && seen.insert("deinit").second) {
                            Json::Value item = Json::Value::object();
                            item["label"] = "deinit";
                            item["kind"] = 2; // Method
                            item["detail"] = "pub deinit()";
                            item["insertText"] = "deinit()";
                            item["sortText"] = "010_deinit";
                            items.push_back(item);
                        }
                        for (const auto& m : f->methods) {
                            if (seen.insert(m->name).second) {
                                Json::Value item = Json::Value::object();
                                item["label"] = m->name;
                                item["kind"] = 2; // Method
                                item["detail"] = format_method_signature(m, f->name);
                                item["insertText"] = m->parameters.empty() && m->optionalParams.empty() ? m->name + "()" : m->name + "(${1})";
                                item["insertTextFormat"] = 2;
                                item["sortText"] = "010_" + m->name;
                                items.push_back(item);
                            }
                        }
                        for (const auto& trait_name : f->implements) {
                            auto tit = snap.last_check_result->trait_declarations.find(trait_name);
                            if (tit != snap.last_check_result->trait_declarations.end() && tit->second.declaration) {
                                for (const auto& m : tit->second.declaration->methods) {
                                    if (seen.insert(m->name).second) {
                                        Json::Value item = Json::Value::object();
                                        item["label"] = m->name;
                                        item["kind"] = 2; // Method
                                        item["detail"] = format_func_signature(m);
                                        item["insertText"] = m->params.empty() && m->optionalParams.empty() ? m->name + "()" : m->name + "(${1})";
                                        item["insertTextFormat"] = 2;
                                        item["sortText"] = "015_" + m->name;
                                        items.push_back(item);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (rec.category == SymbolTypeCategory::Enum) {
            if (current_ast) {
                for (const auto& stmt : current_ast->statements) {
                    if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                        if (e->name == rec.name) {
                            for (const auto& var : e->variants) {
                                if (seen.insert(var.first).second) {
                                    Json::Value item = Json::Value::object();
                                    item["label"] = var.first;
                                    item["kind"] = 20; // EnumMember
                                    item["detail"] = e->name + "." + var.first;
                                    item["insertText"] = var.first;
                                    item["sortText"] = "010_" + var.first;
                                    items.push_back(item);
                                }
                            }
                        }
                    }
                }
            }
        } else if (rec.category == SymbolTypeCategory::Module) {
            if (snap.last_check_result.has_value()) {
                auto mit = snap.last_check_result->registered_modules.find(rec.name);
                if (mit != snap.last_check_result->registered_modules.end()) {
                    for (const auto& [sname, stype] : mit->second.symbols) {
                        if (seen.insert(sname).second) {
                            Json::Value item = Json::Value::object();
                            item["label"] = sname;
                            if (stype && stype->tag == TypeTag::Function) {
                                item["kind"] = 2; // Method
                                item["detail"] = stype->toString();
                                item["insertText"] = sname + "()";
                            } else if (stype && stype->tag == TypeTag::Frame) {
                                item["kind"] = 7; // Class
                                item["detail"] = "frame " + sname;
                                item["insertText"] = sname;
                            } else {
                                item["kind"] = 6; // Variable
                                item["detail"] = stype ? stype->toString() : "Variable";
                                item["insertText"] = sname;
                            }
                            item["sortText"] = "050_" + sname;
                            items.push_back(item);
                        }
                    }
                }
            }
            auto mod_ptr = Frontend::ModuleManager::getInstance().get_module(rec.name);
            if (mod_ptr) {
                for (const auto& sym : mod_ptr->public_symbols) {
                    if (seen.insert(sym).second) {
                        Json::Value item = Json::Value::object();
                        item["label"] = sym;
                        item["kind"] = 6;
                        item["detail"] = "module symbol";
                        item["insertText"] = sym;
                        item["sortText"] = "050_" + sym;
                        items.push_back(item);
                    }
                }
            }
        }

        res["items"] = items;
        return res;
    }

    // 2. Decorator completion: typing `@...`
    size_t at_pos = before_cursor.rfind('@');
    if (at_pos != std::string::npos) {
        bool only_ident = true;
        for (size_t p = at_pos + 1; p < before_cursor.size(); ++p) {
            if (!std::isalnum(before_cursor[p]) && before_cursor[p] != '_') {
                only_ident = false;
                break;
            }
        }
        if (only_ident) {
            for (const auto& dec : kDecorators) {
                Json::Value item = Json::Value::object();
                item["label"] = dec.label;
                item["kind"] = 14; // Keyword
                item["detail"] = "Decorator";
                item["documentation"] = dec.summary;
                item["insertText"] = dec.label;
                item["sortText"] = "010_" + std::string(dec.label);
                items.push_back(item);
            }
            res["items"] = items;
            return res;
        }
    }

    // 3. Proof-aware completion if typed hole exists in AST
    if (current_ast && snap.last_check_result.has_value()) {
        struct HoleVisitor {
            const Frontend::AST::TypedHoleExpr* hole = nullptr;
            void visit(const std::shared_ptr<Frontend::AST::Statement>& stmt) {
                if (!stmt) return;
                if (auto expr_stmt = std::dynamic_pointer_cast<Frontend::AST::ExprStatement>(stmt)) {
                    visit_expr(expr_stmt->expression);
                } else if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
                    for (const auto& s : block->statements) visit(s);
                } else if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                    if (var_decl->initializer) visit_expr(var_decl->initializer);
                }
            }
            void visit_expr(const std::shared_ptr<Frontend::AST::Expression>& expr) {
                if (!expr) return;
                if (auto h = std::dynamic_pointer_cast<Frontend::AST::TypedHoleExpr>(expr)) {
                    hole = h.get();
                } else if (auto bin = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
                    visit_expr(bin->left);
                    visit_expr(bin->right);
                } else if (auto assign = std::dynamic_pointer_cast<Frontend::AST::AssignExpr>(expr)) {
                    visit_expr(assign->value);
                }
            }
        } visitor;

        for (const auto& stmt : current_ast->statements) {
            visitor.visit(stmt);
        }

        if (visitor.hole) {
            auto candidates = ProofAwareCompletionEngine::complete_hole(*visitor.hole, snap.last_check_result->type_system);
            for (size_t i = 0; i < candidates.size(); ++i) {
                Json::Value item = Json::Value::object();
                item["label"] = candidates[i].label;
                item["kind"] = 6;
                item["detail"] = candidates[i].detail + (candidates[i].proven ? " (proven)" : "");
                item["insertText"] = candidates[i].label;
                char sort_buf[32];
                snprintf(sort_buf, sizeof(sort_buf), "%05d_%s", static_cast<int>(99999 - candidates[i].score), candidates[i].label.c_str());
                item["sortText"] = std::string(sort_buf);
                items.push_back(item);
            }
            if (!candidates.empty()) {
                res["items"] = items;
                return res;
            }
        }
    }

    // 4. Context-aware type suggestions
    bool is_after_colon = false;
    bool is_after_type_eq = false;
    bool is_in_error_type = false;
    bool is_after_as = false;
    try {
        is_after_colon = std::regex_search(before_cursor, std::regex(":\\s*$"));
        is_after_type_eq = std::regex_search(before_cursor, std::regex("(?:type\\s+[A-Za-z0-9_]*\\s*=\\s*|type\\s*=\\s*)$"));
        is_in_error_type = std::regex_search(before_cursor, std::regex("[A-Za-z0-9_]+\\s*\\?\\s*[A-Za-z0-9_]*$")) && !std::regex_search(before_cursor, std::regex("=\\s*\\?$"));
        is_after_as = std::regex_search(before_cursor, std::regex("(?:\\bas|as)\\s+$"));
    } catch (...) {}

    if (is_after_colon || is_after_type_eq || is_in_error_type || is_after_as) {
        // High-priority type suggestions
        for (const auto& bt : kBuiltinTypes) {
            Json::Value item = Json::Value::object();
            item["label"] = bt.name;
            item["kind"] = 25; // TypeParameter
            item["detail"] = bt.summary;
            item["documentation"] = bt.details;
            item["insertText"] = bt.name;
            item["sortText"] = "010_" + std::string(bt.name);
            items.push_back(item);
        }

        // Add user-defined types (frames, traits, enums, type aliases)
        if (current_ast) {
            std::unordered_set<std::string> seen_types;
            for (const auto& stmt : current_ast->statements) {
                if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    if (seen_types.insert(f->name).second) {
                        Json::Value item = Json::Value::object();
                        item["label"] = f->name;
                        item["kind"] = 7; // Class
                        item["detail"] = "frame " + f->name;
                        item["insertText"] = f->name;
                        item["sortText"] = "020_" + f->name;
                        items.push_back(item);
                    }
                } else if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                    if (seen_types.insert(t->name).second) {
                        Json::Value item = Json::Value::object();
                        item["label"] = t->name;
                        item["kind"] = 8; // Interface
                        item["detail"] = "trait " + t->name;
                        item["insertText"] = t->name;
                        item["sortText"] = "020_" + t->name;
                        items.push_back(item);
                    }
                } else if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                    if (seen_types.insert(e->name).second) {
                        Json::Value item = Json::Value::object();
                        item["label"] = e->name;
                        item["kind"] = 13; // Enum
                        item["detail"] = "enum " + e->name;
                        item["insertText"] = e->name;
                        item["sortText"] = "020_" + e->name;
                        items.push_back(item);
                    }
                } else if (auto td = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(stmt)) {
                    if (seen_types.insert(td->name).second) {
                        Json::Value item = Json::Value::object();
                        item["label"] = td->name;
                        item["kind"] = 25; // TypeParameter
                        item["detail"] = "type " + td->name;
                        item["insertText"] = td->name;
                        item["sortText"] = "020_" + td->name;
                        items.push_back(item);
                    }
                }
            }
        }

        res["items"] = items;
        return res;
    }

    // 5. Code Snippets (high priority for developers)
    for (const auto& snip : kSnippets) {
        Json::Value item = Json::Value::object();
        item["label"] = snip.label;
        item["kind"] = 15; // Snippet
        item["insertText"] = snip.insert_text;
        item["insertTextFormat"] = 2; // Snippet
        item["detail"] = "Snippet: " + std::string(snip.label);
        item["documentation"] = snip.documentation;
        item["sortText"] = "030_" + std::string(snip.label);
        items.push_back(item);
    }

    // 6. Built-in Functions (20+ functions with parameter snippets)
    for (const auto& fn : kBuiltinFunctions) {
        Json::Value item = Json::Value::object();
        item["label"] = fn.name;
        item["kind"] = 3; // Function
        item["detail"] = fn.signature;
        item["documentation"] = fn.summary;
        item["insertText"] = fn.snippet;
        item["insertTextFormat"] = 2; // Snippet
        item["sortText"] = "040_" + std::string(fn.name);
        items.push_back(item);
    }

    // 7. Local and top-level user declarations
    if (current_ast) {
        std::unordered_set<std::string> seen;
        for (const auto& stmt : current_ast->statements) {
            if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                if (seen.insert(var_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = var_decl->name;
                    item["kind"] = 6; // Variable
                    std::string detail = "Variable";
                    if (var_decl->inferred_type) detail += ": " + var_decl->inferred_type->toString();
                    else if (var_decl->type.has_value() && var_decl->type.value()) detail += ": " + var_decl->type.value()->typeName;
                    item["detail"] = detail;
                    item["insertText"] = var_decl->name;
                    item["sortText"] = "050_" + var_decl->name;
                    items.push_back(item);
                }
            } else if (auto fn_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
                if (seen.insert(fn_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = fn_decl->name;
                    item["kind"] = 3; // Function
                    item["detail"] = format_func_signature(fn_decl);
                    item["insertText"] = fn_decl->params.empty() && fn_decl->optionalParams.empty() ? fn_decl->name + "()" : fn_decl->name + "(${1})";
                    item["insertTextFormat"] = 2;
                    item["sortText"] = "050_" + fn_decl->name;
                    items.push_back(item);
                }
            } else if (auto frame_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (seen.insert(frame_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = frame_decl->name;
                    item["kind"] = 7; // Class
                    item["detail"] = "frame " + frame_decl->name;
                    item["insertText"] = frame_decl->name;
                    item["sortText"] = "050_" + frame_decl->name;
                    items.push_back(item);
                }
            } else if (auto trait_decl = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                if (seen.insert(trait_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = trait_decl->name;
                    item["kind"] = 8; // Interface
                    item["detail"] = "trait " + trait_decl->name;
                    item["insertText"] = trait_decl->name;
                    item["sortText"] = "050_" + trait_decl->name;
                    items.push_back(item);
                }
            } else if (auto enum_decl = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                if (seen.insert(enum_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = enum_decl->name;
                    item["kind"] = 13; // Enum
                    item["detail"] = "enum " + enum_decl->name;
                    item["insertText"] = enum_decl->name;
                    item["sortText"] = "050_" + enum_decl->name;
                    items.push_back(item);
                }
            } else if (auto td = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(stmt)) {
                if (seen.insert(td->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = td->name;
                    item["kind"] = 25; // TypeParameter
                    item["detail"] = "type " + td->name;
                    item["insertText"] = td->name;
                    item["sortText"] = "050_" + td->name;
                    items.push_back(item);
                }
            } else if (auto imp_stmt = std::dynamic_pointer_cast<Frontend::AST::ImportStatement>(stmt)) {
                std::string imp_name = (imp_stmt->alias.has_value() && !imp_stmt->alias.value().empty()) ? imp_stmt->alias.value() : imp_stmt->modulePath;
                if (seen.insert(imp_name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = imp_name;
                    item["kind"] = 9; // Module
                    item["detail"] = "import " + imp_stmt->modulePath;
                    item["insertText"] = imp_name;
                    item["sortText"] = "050_" + imp_name;
                    items.push_back(item);
                }
            }
        }
    }

    // 8. Built-in Types
    for (const auto& bt : kBuiltinTypes) {
        Json::Value item = Json::Value::object();
        item["label"] = bt.name;
        item["kind"] = 25; // TypeParameter
        item["detail"] = bt.summary;
        item["documentation"] = bt.details;
        item["insertText"] = bt.name;
        item["sortText"] = "060_" + std::string(bt.name);
        items.push_back(item);
    }

    // 9. Built-in Keywords
    for (const auto& kw : kKeywords) {
        Json::Value item = Json::Value::object();
        item["label"] = kw.keyword;
        item["kind"] = 14; // Keyword
        item["detail"] = kw.summary;
        item["documentation"] = std::string(kw.description) + "\n\nSyntax: `" + kw.syntax + "`";
        item["insertText"] = kw.keyword;
        item["sortText"] = "070_" + std::string(kw.keyword);
        items.push_back(item);
    }

    // 10. Decorators
    for (const auto& dec : kDecorators) {
        Json::Value item = Json::Value::object();
        item["label"] = dec.label;
        item["kind"] = 14; // Keyword
        item["detail"] = dec.summary;
        item["documentation"] = dec.details;
        item["insertText"] = dec.label;
        item["sortText"] = "080_" + std::string(dec.label);
        items.push_back(item);
    }

    res["items"] = items;
    return res;
}

// -----------------------------------------------------------------------------
// Hover Handler
// -----------------------------------------------------------------------------

static Json::Value handle_hover(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    int line = static_cast<int>(params["position"]["line"].as_int());
    int character = static_cast<int>(params["position"]["character"].as_int());

    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) {
        return Json::Value();
    }

    const auto& content = it->second.content;
    size_t cursor_idx = get_cursor_offset(content, line, character);
    size_t word_start = 0, word_end = 0;
    get_word_at_offset(content, cursor_idx, word_start, word_end);

    if (word_start == word_end) return Json::Value();
    std::string word = content.substr(word_start, word_end - word_start);

    std::string hover_info;
    const auto& snap = it->second;
    auto current_ast = snap.get_ast();

    // Check if word is preceded by '@' (decorator hover)
    if (word_start > 0 && content[word_start - 1] == '@') {
        std::string dec_name = "@" + word;
        for (const auto& dec : kDecorators) {
            if (dec_name == dec.label) {
                hover_info = "**Decorator:** `" + dec_name + "`\n\n" + dec.summary + "\n\n" + dec.details;
                break;
            }
        }
    }

    // Check if word is part of receiver.word
    if (hover_info.empty()) {
        ReceiverContext rctx = extract_receiver_context(content, word_end);
        if (rctx.is_member_access && !rctx.receiver.empty()) {
            ResolvedReceiver rec = resolve_receiver(rctx.receiver, line, snap);
            if (rec.category == SymbolTypeCategory::Frame && current_ast) {
                for (const auto& stmt : current_ast->statements) {
                    if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                        if (f->name == rec.name) {
                            for (const auto& field : f->fields) {
                                if (field->name == word) {
                                    hover_info = "```lymar\n(field) " + f->name + "." + field->name;
                                    if (field->type) hover_info += ": " + field->type->typeName;
                                    hover_info += "\n```";
                                    break;
                                }
                            }
                            if (hover_info.empty()) {
                                if (word == "init" && f->init) {
                                    hover_info = "```lymar\n" + format_method_signature(f->init, f->name) + "\n```";
                                } else if (word == "deinit" && f->deinit) {
                                    hover_info = "```lymar\npub fn " + f->name + ".deinit(): void\n```";
                                } else {
                                    for (const auto& m : f->methods) {
                                        if (m->name == word) {
                                            hover_info = "```lymar\n(method) " + format_method_signature(m, f->name) + "\n```";
                                            break;
                                        }
                                    }
                                }
                            }
                            if (hover_info.empty()) {
                                for (const auto& trait_name : f->implements) {
                                    for (const auto& tstmt : current_ast->statements) {
                                        if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(tstmt)) {
                                            if (t->name == trait_name) {
                                                for (const auto& m : t->methods) {
                                                    if (m->name == word) {
                                                        hover_info = "```lymar\n(trait method) " + format_func_signature(m) + "\n```";
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (!hover_info.empty()) break;
                                }
                            }
                        }
                    }
                }
            } else if (rec.category == SymbolTypeCategory::Enum && current_ast) {
                for (const auto& stmt : current_ast->statements) {
                    if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                        if (e->name == rec.name) {
                            for (const auto& var : e->variants) {
                                if (var.first == word) {
                                    hover_info = "```lymar\n(enum variant) " + e->name + "." + var.first + "\n```";
                                    break;
                                }
                            }
                        }
                    }
                }
            } else if (rec.category == SymbolTypeCategory::Module) {
                if (snap.last_check_result.has_value()) {
                    auto mit = snap.last_check_result->registered_modules.find(rec.name);
                    if (mit != snap.last_check_result->registered_modules.end()) {
                        auto sit = mit->second.symbols.find(word);
                        if (sit != mit->second.symbols.end()) {
                            hover_info = "```lymar\n(module member) " + rec.name + "." + word;
                            if (sit->second) hover_info += ": " + sit->second->toString();
                            hover_info += "\n```";
                        }
                    }
                }
            }
        }
    }

    // Direct symbol lookup in AST
    if (hover_info.empty() && current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                if (var_decl->name == word) {
                    hover_info = "```lymar\nvar " + var_decl->name;
                    if (var_decl->inferred_type) {
                        hover_info += ": " + var_decl->inferred_type->toString();
                    } else if (var_decl->type.has_value() && var_decl->type.value()) {
                        hover_info += ": " + var_decl->type.value()->typeName;
                    }
                    hover_info += "\n```";
                    break;
                }
            } else if (auto fn_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
                if (fn_decl->name == word) {
                    hover_info = "```lymar\n" + format_func_signature(fn_decl) + "\n```";
                    break;
                }
            } else if (auto frame_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (frame_decl->name == word) {
                    hover_info = "```lymar\nframe " + frame_decl->name;
                    if (!frame_decl->implements.empty()) {
                        hover_info += ": ";
                        for (size_t i = 0; i < frame_decl->implements.size(); ++i) {
                            if (i > 0) hover_info += ", ";
                            hover_info += frame_decl->implements[i];
                        }
                    }
                    hover_info += " {\n";
                    for (const auto& fld : frame_decl->fields) {
                        hover_info += "    pub " + fld->name + ": " + (fld->type ? fld->type->typeName : "any") + ";\n";
                    }
                    for (const auto& m : frame_decl->methods) {
                        hover_info += "    pub fn " + m->name + "(...);\n";
                    }
                    hover_info += "}\n```";
                    break;
                }
            } else if (auto trait_decl = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                if (trait_decl->name == word) {
                    hover_info = "```lymar\ntrait " + trait_decl->name + " {\n";
                    for (const auto& m : trait_decl->methods) {
                        hover_info += "    fn " + m->name + "(...);\n";
                    }
                    hover_info += "}\n```";
                    break;
                }
            } else if (auto enum_decl = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                if (enum_decl->name == word) {
                    hover_info = "```lymar\nenum " + enum_decl->name + " {\n";
                    for (const auto& v : enum_decl->variants) {
                        hover_info += "    " + v.first + ",\n";
                    }
                    hover_info += "}\n```";
                    break;
                }
            } else if (auto td = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(stmt)) {
                if (td->name == word) {
                    hover_info = "```lymar\ntype " + td->name + "\n```";
                    break;
                }
            }
        }
    }

    // Built-in function documentation
    if (hover_info.empty()) {
        for (const auto& fn : kBuiltinFunctions) {
            if (word == fn.name) {
                hover_info = "**Built-in Function:** `" + std::string(fn.name) + "`\n\n```lymar\n" +
                             fn.signature + "\n```\n\n" + fn.summary;
                if (!fn.params.empty()) {
                    hover_info += "\n\n**Parameters:**\n";
                    for (const auto& p : fn.params) {
                        hover_info += "- `" + p.first + "`: " + p.second + "\n";
                    }
                }
                break;
            }
        }
    }

    // Built-in type documentation
    if (hover_info.empty()) {
        for (const auto& bt : kBuiltinTypes) {
            if (word == bt.name) {
                hover_info = "**Type:** `" + std::string(bt.name) + "`\n\n" +
                             bt.summary + "\n\n" + bt.details;
                break;
            }
        }
    }

    // Keyword documentation
    if (hover_info.empty()) {
        for (const auto& kw : kKeywords) {
            if (word == kw.keyword) {
                hover_info = "**Keyword:** `" + std::string(kw.keyword) + "`\n\n" +
                             kw.summary + "\n\n```lymar\n" +
                             kw.syntax + "\n```\n\n" + kw.description;
                break;
            }
        }
    }

    if (hover_info.empty()) {
        return Json::Value();
    }

    Json::Value res = Json::Value::object();
    Json::Value contents = Json::Value::object();
    contents["kind"] = "markdown";
    contents["value"] = hover_info;
    res["contents"] = contents;
    return res;
}

// -----------------------------------------------------------------------------
// Signature Help Handler
// -----------------------------------------------------------------------------

static Json::Value handle_signature_help(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    int line = static_cast<int>(params["position"]["line"].as_int());
    int character = static_cast<int>(params["position"]["character"].as_int());

    Json::Value res = Json::Value::object();
    Json::Value sigs = Json::Value::array();
    res["signatures"] = sigs;
    res["activeSignature"] = 0;
    res["activeParameter"] = 0;

    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) return res;
    const auto& snap = it->second;
    const auto& content = snap.content;

    size_t cursor_idx = get_cursor_offset(content, line, character);
    if (cursor_idx > content.size()) cursor_idx = content.size();

    int paren_depth = 0;
    int comma_count = 0;
    size_t open_paren_idx = std::string::npos;
    bool in_str = false;

    for (size_t i = cursor_idx; i > 0; --i) {
        char ch = content[i - 1];
        if (ch == '\"') in_str = !in_str;
        if (in_str) continue;

        if (ch == ')') {
            paren_depth++;
        } else if (ch == '(') {
            if (paren_depth > 0) {
                paren_depth--;
            } else {
                open_paren_idx = i - 1;
                break;
            }
        } else if (ch == ',' && paren_depth == 0) {
            comma_count++;
        }
    }

    if (open_paren_idx == std::string::npos) {
        return res;
    }

    res["activeParameter"] = comma_count;

    size_t end_callee = open_paren_idx;
    while (end_callee > 0 && (content[end_callee - 1] == ' ' || content[end_callee - 1] == '\t')) {
        end_callee--;
    }
    size_t start_callee = end_callee;
    while (start_callee > 0 && (std::isalnum(content[start_callee - 1]) || content[start_callee - 1] == '_' || content[start_callee - 1] == '.')) {
        start_callee--;
    }

    if (start_callee == end_callee) return res;
    std::string callee = content.substr(start_callee, end_callee - start_callee);

    size_t dot_pos = callee.rfind('.');
    auto current_ast = snap.get_ast();
    if (dot_pos != std::string::npos) {
        std::string receiver = callee.substr(0, dot_pos);
        std::string method_name = callee.substr(dot_pos + 1);

        ResolvedReceiver rec = resolve_receiver(receiver, line, snap);
        if (rec.category == SymbolTypeCategory::Frame && current_ast) {
            for (const auto& stmt : current_ast->statements) {
                if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    if (f->name == rec.name) {
                        std::shared_ptr<Frontend::AST::FrameMethod> target_m = nullptr;
                        if (method_name == "init" && f->init) {
                            target_m = f->init;
                        } else if (method_name == "deinit" && f->deinit) {
                            target_m = f->deinit;
                        } else {
                            for (const auto& m : f->methods) {
                                if (m->name == method_name) {
                                    target_m = m;
                                    break;
                                }
                            }
                        }

                        if (target_m) {
                            Json::Value sig_info = Json::Value::object();
                            sig_info["label"] = format_method_signature(target_m, f->name);
                            Json::Value params_arr = Json::Value::array();
                            for (const auto& p : target_m->parameters) {
                                Json::Value p_info = Json::Value::object();
                                p_info["label"] = p.first + (p.second ? ": " + p.second->typeName : "");
                                params_arr.push_back(p_info);
                            }
                            for (const auto& op : target_m->optionalParams) {
                                Json::Value p_info = Json::Value::object();
                                p_info["label"] = op.first + "?" + (op.second.first ? ": " + op.second.first->typeName : "");
                                params_arr.push_back(p_info);
                            }
                            sig_info["parameters"] = params_arr;
                            sigs.push_back(sig_info);
                            res["signatures"] = sigs;
                            return res;
                        }
                    }
                }
            }
        }
    } else {
        // Simple identifier callee
        if (current_ast) {
            for (const auto& stmt : current_ast->statements) {
                if (auto fn = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
                    if (fn->name == callee) {
                        Json::Value sig_info = Json::Value::object();
                        sig_info["label"] = format_func_signature(fn);
                        Json::Value params_arr = Json::Value::array();
                        for (const auto& p : fn->params) {
                            Json::Value p_info = Json::Value::object();
                            p_info["label"] = p.first + (p.second ? ": " + p.second->typeName : "");
                            params_arr.push_back(p_info);
                        }
                        for (const auto& op : fn->optionalParams) {
                            Json::Value p_info = Json::Value::object();
                            p_info["label"] = op.first + "?" + (op.second.first ? ": " + op.second.first->typeName : "");
                            params_arr.push_back(p_info);
                        }
                        sig_info["parameters"] = params_arr;
                        sigs.push_back(sig_info);
                        res["signatures"] = sigs;
                        return res;
                    }
                } else if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    if (f->name == callee) {
                        Json::Value sig_info = Json::Value::object();
                        if (f->init) {
                            sig_info["label"] = format_method_signature(f->init, f->name);
                            Json::Value params_arr = Json::Value::array();
                            for (const auto& p : f->init->parameters) {
                                Json::Value p_info = Json::Value::object();
                                p_info["label"] = p.first + (p.second ? ": " + p.second->typeName : "");
                                params_arr.push_back(p_info);
                            }
                            for (const auto& op : f->init->optionalParams) {
                                Json::Value p_info = Json::Value::object();
                                p_info["label"] = op.first + "?" + (op.second.first ? ": " + op.second.first->typeName : "");
                                params_arr.push_back(p_info);
                            }
                            sig_info["parameters"] = params_arr;
                        } else {
                            sig_info["label"] = f->name + "()";
                            sig_info["parameters"] = Json::Value::array();
                        }
                        sigs.push_back(sig_info);
                        res["signatures"] = sigs;
                        return res;
                    }
                }
            }
        }

        // Built-in function signature help (20+ functions supported)
        for (const auto& fn : kBuiltinFunctions) {
            if (callee == fn.name) {
                Json::Value sig_info = Json::Value::object();
                sig_info["label"] = fn.signature;
                sig_info["documentation"] = fn.summary;
                Json::Value params_arr = Json::Value::array();
                for (const auto& p : fn.params) {
                    Json::Value p_info = Json::Value::object();
                    p_info["label"] = p.first;
                    p_info["documentation"] = p.second;
                    params_arr.push_back(p_info);
                }
                sig_info["parameters"] = params_arr;
                sigs.push_back(sig_info);
                res["signatures"] = sigs;
                return res;
            }
        }
    }

    res["signatures"] = sigs;
    return res;
}

// -----------------------------------------------------------------------------
// Definition Handler (Go to Definition & Peek Definition)
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Definition & Reference Helpers
// -----------------------------------------------------------------------------

static std::string file_path_to_uri(const std::string& raw_path) {
    if (raw_path.empty()) return "";
    if (raw_path.rfind("file://", 0) == 0) return raw_path;
    try {
        std::error_code ec;
        std::filesystem::path p = std::filesystem::absolute(raw_path, ec);
        std::string s = p.generic_string();
        if (!s.empty() && s[0] != '/') {
            return "file:///" + s;
        }
        return "file://" + s;
    } catch (...) {
        std::string s = raw_path;
        for (char& c : s) if (c == '\\') c = '/';
        if (!s.empty() && s[0] != '/') {
            return "file:///" + s;
        }
        return "file://" + s;
    }
}

static Json::Value make_location(const std::string& target_uri, int line, int char_start, int char_end) {
    Json::Value loc = Json::Value::object();
    loc["uri"] = target_uri;
    Json::Value range = Json::Value::object();
    Json::Value start = Json::Value::object();
    start["line"] = line >= 0 ? line : 0;
    start["character"] = char_start >= 0 ? char_start : 0;
    Json::Value end = Json::Value::object();
    end["line"] = line >= 0 ? line : 0;
    end["character"] = char_end >= char_start ? char_end : char_start;
    range["start"] = start;
    range["end"] = end;
    loc["range"] = range;
    return loc;
}

static std::pair<int, int> find_symbol_in_source(const std::string& source,
                                                 const std::string& sym,
                                                 int hint_line_0 = -1,
                                                 const std::string& prefix_pattern = "") {
    if (source.empty() || sym.empty()) return {hint_line_0 >= 0 ? hint_line_0 : 0, 0};

    if (hint_line_0 >= 0) {
        std::istringstream iss_hint(source);
        std::string sline;
        int l = 0;
        while (std::getline(iss_hint, sline)) {
            if (l == hint_line_0) {
                size_t pos = sline.find(sym);
                if (pos != std::string::npos) {
                    return {hint_line_0, static_cast<int>(pos)};
                }
                break;
            }
            l++;
        }
    }

    std::regex rx;
    bool use_rx = false;
    if (!prefix_pattern.empty()) {
        try {
            rx = std::regex(prefix_pattern + "\\s+" + sym + "\\b");
            use_rx = true;
        } catch (...) {}
    }

    std::istringstream iss(source);
    std::string sline;
    int cur_line = 0;
    int fallback_line = -1, fallback_char = 0;

    while (std::getline(iss, sline)) {
        if (use_rx) {
            std::smatch m;
            if (std::regex_search(sline, m, rx)) {
                size_t p = sline.find(sym, m.position());
                if (p != std::string::npos) {
                    return {cur_line, static_cast<int>(p)};
                }
            }
        }
        size_t p = sline.find(sym);
        if (p != std::string::npos) {
            bool valid_start = (p == 0 || (!std::isalnum(sline[p - 1]) && sline[p - 1] != '_'));
            bool valid_end = (p + sym.size() >= sline.size() || (!std::isalnum(sline[p + sym.size()]) && sline[p + sym.size()] != '_'));
            if (valid_start && valid_end && fallback_line == -1) {
                fallback_line = cur_line;
                fallback_char = static_cast<int>(p);
            }
        }
        cur_line++;
    }

    if (fallback_line != -1) {
        return {fallback_line, fallback_char};
    }
    return {hint_line_0 >= 0 ? hint_line_0 : 0, 0};
}

static std::shared_ptr<Frontend::Module> find_module_by_name(const std::string& name) {
    if (name.empty()) return nullptr;
    auto& mm = Frontend::ModuleManager::getInstance();
    auto m = mm.get_module(name);
    if (m) return m;

    auto all = mm.get_all_modules();
    for (const auto& [mname, mod] : all) {
        if (!mod) continue;
        if (mname == name || mod->name == name) return mod;
        if (mname.size() > name.size() && mname.substr(mname.size() - name.size()) == name &&
            (mname[mname.size() - name.size() - 1] == '.' || mname[mname.size() - name.size() - 1] == '/')) {
            return mod;
        }
    }
    return nullptr;
}

static Json::Value find_symbol_in_module(const std::shared_ptr<Frontend::Module>& mod,
                                         const std::string& symbol_name,
                                         const std::string& member_name = "") {
    if (!mod) return Json::Value();
    std::string mod_uri = file_path_to_uri(mod->path);

    if (!member_name.empty()) {
        if (mod->ast) {
            for (const auto& stmt : mod->ast->statements) {
                if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    if (f->name == symbol_name) {
                        for (const auto& field : f->fields) {
                            if (field->name == member_name) {
                                auto [line, ch] = find_symbol_in_source(mod->source, member_name,
                                    field->line > 0 ? field->line - 1 : -1, "(?:pub\\s+|prot\\s+)?var");
                                return make_location(mod_uri, line, ch, ch + member_name.size());
                            }
                        }
                        if (member_name == "init" && f->init) {
                            auto [line, ch] = find_symbol_in_source(mod->source, "init",
                                f->init->line > 0 ? f->init->line - 1 : -1, "(?:pub\\s+|prot\\s+)?");
                            return make_location(mod_uri, line, ch, ch + 4);
                        }
                        if (member_name == "deinit" && f->deinit) {
                            auto [line, ch] = find_symbol_in_source(mod->source, "deinit",
                                f->deinit->line > 0 ? f->deinit->line - 1 : -1, "(?:pub\\s+|prot\\s+)?");
                            return make_location(mod_uri, line, ch, ch + 6);
                        }
                        for (const auto& m : f->methods) {
                            if (m->name == member_name) {
                                auto [line, ch] = find_symbol_in_source(mod->source, member_name,
                                    m->line > 0 ? m->line - 1 : -1, "(?:pub\\s+|prot\\s+)?fn");
                                return make_location(mod_uri, line, ch, ch + member_name.size());
                            }
                        }
                    }
                }
            }
        }
        return Json::Value();
    }

    if (mod->ast) {
        for (const auto& stmt : mod->ast->statements) {
            if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (f->name == symbol_name) {
                    auto [line, ch] = find_symbol_in_source(mod->source, symbol_name,
                        f->line > 0 ? f->line - 1 : -1, "frame");
                    return make_location(mod_uri, line, ch, ch + symbol_name.size());
                }
            } else if (auto fn = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
                if (fn->name == symbol_name) {
                    auto [line, ch] = find_symbol_in_source(mod->source, symbol_name,
                        fn->line > 0 ? fn->line - 1 : -1, "(?:pub\\s+|prot\\s+)?fn");
                    return make_location(mod_uri, line, ch, ch + symbol_name.size());
                }
            } else if (auto v = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                if (v->name == symbol_name) {
                    auto [line, ch] = find_symbol_in_source(mod->source, symbol_name,
                        v->line > 0 ? v->line - 1 : -1, "(?:pub\\s+|prot\\s+)?(?:var|val|const)");
                    return make_location(mod_uri, line, ch, ch + symbol_name.size());
                }
            } else if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                if (t->name == symbol_name) {
                    auto [line, ch] = find_symbol_in_source(mod->source, symbol_name,
                        t->line > 0 ? t->line - 1 : -1, "trait");
                    return make_location(mod_uri, line, ch, ch + symbol_name.size());
                }
            } else if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                if (e->name == symbol_name) {
                    auto [line, ch] = find_symbol_in_source(mod->source, symbol_name,
                        e->line > 0 ? e->line - 1 : -1, "enum");
                    return make_location(mod_uri, line, ch, ch + symbol_name.size());
                }
            } else if (auto td = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(stmt)) {
                if (td->name == symbol_name) {
                    auto [line, ch] = find_symbol_in_source(mod->source, symbol_name,
                        td->line > 0 ? td->line - 1 : -1, "type");
                    return make_location(mod_uri, line, ch, ch + symbol_name.size());
                }
            }
        }
    }

    try {
        std::regex rx("\\b(?:frame|fn|var|val|const|trait|enum|type)\\s+" + symbol_name + "\\b");
        std::smatch m;
        if (std::regex_search(mod->source, m, rx)) {
            auto [line, ch] = find_symbol_in_source(mod->source, symbol_name, -1);
            return make_location(mod_uri, line, ch, ch + symbol_name.size());
        }
    } catch (...) {}

    return Json::Value();
}

static Json::Value find_symbol_in_local_ast(const std::shared_ptr<Frontend::AST::Program>& ast,
                                            const std::string& content,
                                            const std::string& uri,
                                            const std::string& word,
                                            int cursor_line) {
    if (!ast) return Json::Value();

    Json::Value best_match;
    int best_line = -1;

    auto consider_match = [&](int decl_line, const std::string& sym_name, const std::string& prefix_pattern = "") {
        int l = decl_line > 0 ? decl_line - 1 : 0;
        if (cursor_line >= 0 && l > cursor_line) return;
        if (l >= best_line) {
            best_line = l;
            auto [line, ch] = find_symbol_in_source(content, sym_name, l, prefix_pattern);
            best_match = make_location(uri, line, ch, ch + sym_name.size());
        }
    };

    std::function<void(const std::shared_ptr<Frontend::AST::Statement>&)> walk_stmt;
    walk_stmt = [&](const std::shared_ptr<Frontend::AST::Statement>& stmt) {
        if (!stmt) return;

        if (auto v = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
            if (v->name == word) {
                consider_match(v->line, word, "(?:var|val|const)");
            }
        } else if (auto fn = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            if (fn->name == word) {
                consider_match(fn->line, word, "(?:pub\\s+|prot\\s+)?fn");
            }
            for (const auto& p : fn->params) {
                if (p.first == word) {
                    consider_match(fn->line, word);
                }
            }
            if (fn->body) walk_stmt(fn->body);
        } else if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            if (f->name == word) {
                consider_match(f->line, word, "frame");
            }
            for (const auto& field : f->fields) {
                if (field->name == word) {
                    consider_match(field->line, word, "(?:pub\\s+|prot\\s+)?var");
                }
            }
            if (f->init) {
                for (const auto& p : f->init->parameters) {
                    if (p.first == word) consider_match(f->init->line, word);
                }
                if (f->init->body) walk_stmt(f->init->body);
            }
            if (f->deinit && f->deinit->body) {
                walk_stmt(f->deinit->body);
            }
            for (const auto& m : f->methods) {
                if (m->name == word) {
                    consider_match(m->line, word, "(?:pub\\s+|prot\\s+)?fn");
                }
                for (const auto& p : m->parameters) {
                    if (p.first == word) consider_match(m->line, word);
                }
                if (m->body) walk_stmt(m->body);
            }
        } else if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
            if (t->name == word) {
                consider_match(t->line, word, "trait");
            }
        } else if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
            if (e->name == word) {
                consider_match(e->line, word, "enum");
            }
            for (const auto& var : e->variants) {
                if (var.first == word) {
                    consider_match(e->line, word);
                }
            }
        } else if (auto td = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(stmt)) {
            if (td->name == word) {
                consider_match(td->line, word, "type");
            }
        } else if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
            for (const auto& s : block->statements) {
                walk_stmt(s);
            }
        } else if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
            if (if_stmt->thenBranch) walk_stmt(if_stmt->thenBranch);
            if (if_stmt->elseBranch) walk_stmt(if_stmt->elseBranch);
        } else if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
            if (while_stmt->body) walk_stmt(while_stmt->body);
        } else if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
            if (for_stmt->initializer) walk_stmt(for_stmt->initializer);
            if (for_stmt->body) walk_stmt(for_stmt->body);
        } else if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
            for (const auto& lv : iter_stmt->loopVars) {
                if (lv == word) {
                    consider_match(iter_stmt->line, word, "iter\\s*\\(");
                }
            }
            if (iter_stmt->body) walk_stmt(iter_stmt->body);
        }
    };

    for (const auto& stmt : ast->statements) {
        walk_stmt(stmt);
    }

    return best_match;
}

// -----------------------------------------------------------------------------
// Definition Handler (Go to Definition & Peek Definition)
// -----------------------------------------------------------------------------

static Json::Value handle_definition(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    int line = static_cast<int>(params["position"]["line"].as_int());
    int character = static_cast<int>(params["position"]["character"].as_int());

    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) return Json::Value();
    const auto& snap = it->second;
    const auto& content = snap.content;

    size_t cursor_idx = get_cursor_offset(content, line, character);
    size_t word_start = 0, word_end = 0;
    get_word_at_offset(content, cursor_idx, word_start, word_end);
    if (word_start == word_end) return Json::Value();
    std::string word = content.substr(word_start, word_end - word_start);

    auto current_ast = snap.get_ast();
    ReceiverContext rctx = extract_receiver_context(content, word_end);

    // 1. Member access: receiver.word
    if (rctx.is_member_access && !rctx.receiver.empty()) {
        ResolvedReceiver rec = resolve_receiver(rctx.receiver, line, snap);

        // 1a. Receiver resolved as Frame
        if (rec.category == SymbolTypeCategory::Frame) {
            if (current_ast) {
                for (const auto& stmt : current_ast->statements) {
                    if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                        if (f->name == rec.name) {
                            for (const auto& field : f->fields) {
                                if (field->name == word) {
                                    auto [dline, dch] = find_symbol_in_source(content, word, field->line > 0 ? field->line - 1 : -1, "(?:pub\\s+|prot\\s+)?var");
                                    return make_location(uri, dline, dch, dch + word.size());
                                }
                            }
                            if (word == "init" && f->init) {
                                auto [dline, dch] = find_symbol_in_source(content, "init", f->init->line > 0 ? f->init->line - 1 : -1);
                                return make_location(uri, dline, dch, dch + 4);
                            }
                            if (word == "deinit" && f->deinit) {
                                auto [dline, dch] = find_symbol_in_source(content, "deinit", f->deinit->line > 0 ? f->deinit->line - 1 : -1);
                                return make_location(uri, dline, dch, dch + 6);
                            }
                            for (const auto& m : f->methods) {
                                if (m->name == word) {
                                    auto [dline, dch] = find_symbol_in_source(content, word, m->line > 0 ? m->line - 1 : -1, "(?:pub\\s+|prot\\s+)?fn");
                                    return make_location(uri, dline, dch, dch + word.size());
                                }
                            }
                        }
                    }
                }
            }

            auto all_mods = Frontend::ModuleManager::getInstance().get_all_modules();
            for (const auto& [mname, mod] : all_mods) {
                Json::Value loc = find_symbol_in_module(mod, rec.name, word);
                if (loc.is_object() && loc.has("uri")) return loc;
            }
        }

        // 1b. Receiver resolved as Module (e.g. linked_list.LinkedList)
        if (rec.category == SymbolTypeCategory::Module) {
            auto mod = find_module_by_name(rec.name);
            if (mod) {
                Json::Value loc = find_symbol_in_module(mod, word);
                if (loc.is_object() && loc.has("uri")) return loc;
            }
            auto all_mods = Frontend::ModuleManager::getInstance().get_all_modules();
            for (const auto& [mname, mod_cand] : all_mods) {
                Json::Value loc = find_symbol_in_module(mod_cand, word);
                if (loc.is_object() && loc.has("uri")) return loc;
            }
        }

        // 1c. Receiver might be an Enum (e.g. Color.Red)
        if (current_ast) {
            for (const auto& stmt : current_ast->statements) {
                if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                    if (e->name == rctx.receiver) {
                        for (const auto& var : e->variants) {
                            if (var.first == word) {
                                auto [dline, dch] = find_symbol_in_source(content, word, e->line > 0 ? e->line - 1 : -1);
                                return make_location(uri, dline, dch, dch + word.size());
                            }
                        }
                    }
                }
            }
        }
        auto all_mods = Frontend::ModuleManager::getInstance().get_all_modules();
        for (const auto& [mname, mod] : all_mods) {
            if (!mod || !mod->ast) continue;
            for (const auto& stmt : mod->ast->statements) {
                if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                    if (e->name == rctx.receiver) {
                        for (const auto& var : e->variants) {
                            if (var.first == word) {
                                auto [dline, dch] = find_symbol_in_source(mod->source, word, e->line > 0 ? e->line - 1 : -1);
                                return make_location(file_path_to_uri(mod->path), dline, dch, dch + word.size());
                            }
                        }
                    }
                }
            }
        }
    }

    // 2. Non-member: check import statements first (import ... as alias)
    if (current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (auto imp = std::dynamic_pointer_cast<Frontend::AST::ImportStatement>(stmt)) {
                if ((imp->alias.has_value() && imp->alias.value() == word) || imp->modulePath == word ||
                    (imp->modulePath.size() > word.size() && imp->modulePath.substr(imp->modulePath.size() - word.size()) == word)) {
                    auto mod = find_module_by_name(imp->modulePath);
                    if (mod && !mod->path.empty()) {
                        return make_location(file_path_to_uri(mod->path), 0, 0, 0);
                    }
                }
                if (imp->filter.has_value()) {
                    for (const auto& id : imp->filter->identifiers) {
                        if (id == word) {
                            auto mod = find_module_by_name(imp->modulePath);
                            if (mod) {
                                Json::Value loc = find_symbol_in_module(mod, word);
                                if (loc.is_object() && loc.has("uri")) return loc;
                            }
                        }
                    }
                }
            }
        }
    }

    // 3. Search local AST (local variables, function params, functions, frames, enums, etc.)
    Json::Value local_loc = find_symbol_in_local_ast(current_ast, content, uri, word, line);
    if (local_loc.is_object() && local_loc.has("uri")) {
        return local_loc;
    }

    // 4. Search imported modules for top-level symbols (functions, frames, traits, enums, types)
    auto all_mods = Frontend::ModuleManager::getInstance().get_all_modules();
    for (const auto& [mname, mod] : all_mods) {
        Json::Value loc = find_symbol_in_module(mod, word);
        if (loc.is_object() && loc.has("uri")) return loc;
    }

    // 5. Text search fallback for declaration patterns in current file
    try {
        std::regex rx_decl("\\b(?:fn|class|frame|trait|enum|type|var|val|const)\\s+" + word + "\\b");
        std::istringstream iss(content);
        std::string sline;
        int cline = 0;
        while (std::getline(iss, sline)) {
            std::smatch m;
            if (std::regex_search(sline, m, rx_decl)) {
                size_t p = sline.find(word, m.position());
                return make_location(uri, cline, static_cast<int>(p), static_cast<int>(p + word.size()));
            }
            cline++;
        }
    } catch (...) {}

    return Json::Value();
}

// -----------------------------------------------------------------------------
// References Handler (Find All References)
// -----------------------------------------------------------------------------

static Json::Value handle_references(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    int line = static_cast<int>(params["position"]["line"].as_int());
    int character = static_cast<int>(params["position"]["character"].as_int());
    bool include_decl = true;
    if (params.has("context") && params["context"].has("includeDeclaration")) {
        include_decl = params["context"]["includeDeclaration"].as_bool(true);
    }

    Json::Value results = Json::Value::array();
    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) return results;
    const auto& content = it->second.content;

    size_t cursor_idx = get_cursor_offset(content, line, character);
    size_t word_start = 0, word_end = 0;
    get_word_at_offset(content, cursor_idx, word_start, word_end);
    if (word_start == word_end) return results;
    std::string word = content.substr(word_start, word_end - word_start);

    // Identify definition location
    std::string decl_uri = "";
    int decl_line = -1;
    Json::Value def_loc = handle_definition(params);
    if (def_loc.is_object() && def_loc.has("uri") && def_loc.has("range") && def_loc["range"].has("start")) {
        decl_uri = def_loc["uri"].as_string();
        decl_line = static_cast<int>(def_loc["range"]["start"]["line"].as_int(-1));
    }

    // Gather all files to scan: open snapshots + loaded modules
    std::unordered_map<std::string, std::string> files_to_scan;
    for (const auto& [doc_uri, doc_snap] : g_document_snapshots) {
        files_to_scan[doc_uri] = doc_snap.content;
    }
    auto all_mods = Frontend::ModuleManager::getInstance().get_all_modules();
    for (const auto& [mname, mod] : all_mods) {
        if (!mod || mod->source.empty() || mod->path.empty()) continue;
        std::string mod_uri = file_path_to_uri(mod->path);
        if (files_to_scan.find(mod_uri) == files_to_scan.end()) {
            files_to_scan[mod_uri] = mod->source;
        }
    }

    auto same_uri = [](const std::string& a, const std::string& b) -> bool {
        if (a == b) return true;
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(a[i])) != std::tolower(static_cast<unsigned char>(b[i]))) {
                return false;
            }
        }
        return true;
    };

    // Scan documents for usages
    for (const auto& [doc_uri, doc_content] : files_to_scan) {
        std::istringstream iss(doc_content);
        std::string sline;
        int cur_line = 0;

        while (std::getline(iss, sline)) {
            size_t pos = 0;
            while ((pos = sline.find(word, pos)) != std::string::npos) {
                bool valid_start = (pos == 0) || (!std::isalnum(sline[pos - 1]) && sline[pos - 1] != '_');
                size_t after = pos + word.size();
                bool valid_end = (after >= sline.size()) || (!std::isalnum(sline[after]) && sline[after] != '_');

                if (valid_start && valid_end) {
                    bool is_decl = (!decl_uri.empty() && same_uri(doc_uri, decl_uri) && cur_line == decl_line);
                    std::string before_word = sline.substr(0, pos);
                    try {
                        if (std::regex_search(before_word, std::regex("(?:fn|frame|class|trait|enum|type|var|val|const|pub|prot)\\s+$"))) {
                            is_decl = true;
                        }
                    } catch (...) {}

                    if (include_decl || !is_decl) {
                        results.push_back(make_location(doc_uri, cur_line, static_cast<int>(pos), static_cast<int>(pos + word.size())));
                    }
                }
                pos += word.size();
            }
            cur_line++;
        }
    }

    return results;
}


// -----------------------------------------------------------------------------
// Document Symbol Handler (Outline View / Symbol Search)
// -----------------------------------------------------------------------------

static Json::Value handle_document_symbol(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    Json::Value symbols = Json::Value::array();

    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) return symbols;
    const auto& content = it->second.content;
    auto current_ast = it->second.get_ast();
    if (!current_ast) return symbols;

    for (const auto& stmt : current_ast->statements) {
        if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = f->name;
            sym["detail"] = "frame";
            sym["kind"] = 5; // Class
            int s_line = f->line > 0 ? f->line - 1 : 0;
            int e_line = find_block_end(content, s_line);

            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            start["line"] = s_line;
            start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = e_line;
            end["character"] = 1;
            range["start"] = start;
            range["end"] = end;
            sym["range"] = range;

            Json::Value sel_range = Json::Value::object();
            Json::Value sel_start = Json::Value::object();
            sel_start["line"] = s_line;
            sel_start["character"] = 0;
            Json::Value sel_end = Json::Value::object();
            sel_end["line"] = s_line;
            sel_end["character"] = static_cast<int>(f->name.size());
            sel_range["start"] = sel_start;
            sel_range["end"] = sel_end;
            sym["selectionRange"] = sel_range;

            Json::Value children = Json::Value::array();
            for (const auto& field : f->fields) {
                Json::Value child = Json::Value::object();
                child["name"] = field->name;
                child["detail"] = field->type ? field->type->typeName : "field";
                child["kind"] = 8; // Field
                int fl = field->line > 0 ? field->line - 1 : s_line;
                Json::Value crange = Json::Value::object();
                Json::Value cstart = Json::Value::object();
                cstart["line"] = fl; cstart["character"] = 0;
                Json::Value cend = Json::Value::object();
                cend["line"] = fl; cend["character"] = static_cast<int>(field->name.size());
                crange["start"] = cstart; crange["end"] = cend;
                child["range"] = crange;
                child["selectionRange"] = crange;
                children.push_back(child);
            }
            if (f->init) {
                Json::Value child = Json::Value::object();
                child["name"] = "init";
                child["detail"] = format_method_signature(f->init, f->name);
                child["kind"] = 9; // Constructor
                int il = f->init->line > 0 ? f->init->line - 1 : s_line;
                int i_end = find_block_end(content, il);
                Json::Value crange = Json::Value::object();
                Json::Value cstart = Json::Value::object();
                cstart["line"] = il; cstart["character"] = 0;
                Json::Value cend = Json::Value::object();
                cend["line"] = i_end; cend["character"] = 1;
                crange["start"] = cstart; crange["end"] = cend;
                child["range"] = crange;
                Json::Value csel = Json::Value::object();
                Json::Value csel_start = Json::Value::object();
                csel_start["line"] = il; csel_start["character"] = 0;
                Json::Value csel_end = Json::Value::object();
                csel_end["line"] = il; csel_end["character"] = 4;
                csel["start"] = csel_start; csel["end"] = csel_end;
                child["selectionRange"] = csel;
                children.push_back(child);
            }
            if (f->deinit) {
                Json::Value child = Json::Value::object();
                child["name"] = "deinit";
                child["detail"] = "pub deinit()";
                child["kind"] = 6; // Method
                int dl = f->deinit->line > 0 ? f->deinit->line - 1 : s_line;
                int d_end = find_block_end(content, dl);
                Json::Value crange = Json::Value::object();
                Json::Value cstart = Json::Value::object();
                cstart["line"] = dl; cstart["character"] = 0;
                Json::Value cend = Json::Value::object();
                cend["line"] = d_end; cend["character"] = 1;
                crange["start"] = cstart; crange["end"] = cend;
                child["range"] = crange;
                Json::Value csel = Json::Value::object();
                Json::Value csel_start = Json::Value::object();
                csel_start["line"] = dl; csel_start["character"] = 0;
                Json::Value csel_end = Json::Value::object();
                csel_end["line"] = dl; csel_end["character"] = 6;
                csel["start"] = csel_start; csel["end"] = csel_end;
                child["selectionRange"] = csel;
                children.push_back(child);
            }
            for (const auto& m : f->methods) {
                Json::Value child = Json::Value::object();
                child["name"] = m->name;
                child["detail"] = format_method_signature(m, f->name);
                child["kind"] = 6; // Method
                int ml = m->line > 0 ? m->line - 1 : s_line;
                int m_end = find_block_end(content, ml);
                Json::Value crange = Json::Value::object();
                Json::Value cstart = Json::Value::object();
                cstart["line"] = ml; cstart["character"] = 0;
                Json::Value cend = Json::Value::object();
                cend["line"] = m_end; cend["character"] = 1;
                crange["start"] = cstart; crange["end"] = cend;
                child["range"] = crange;
                Json::Value csel = Json::Value::object();
                Json::Value csel_start = Json::Value::object();
                csel_start["line"] = ml; csel_start["character"] = 0;
                Json::Value csel_end = Json::Value::object();
                csel_end["line"] = ml; csel_end["character"] = static_cast<int>(m->name.size());
                csel["start"] = csel_start; csel["end"] = csel_end;
                child["selectionRange"] = csel;
                children.push_back(child);
            }
            sym["children"] = children;
            symbols.push_back(sym);
        } else if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = t->name;
            sym["detail"] = "trait";
            sym["kind"] = 11; // Interface
            int s_line = t->line > 0 ? t->line - 1 : 0;
            int e_line = find_block_end(content, s_line);
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            start["line"] = s_line; start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = e_line; end["character"] = 1;
            range["start"] = start; range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;

            Json::Value children = Json::Value::array();
            for (const auto& m : t->methods) {
                Json::Value child = Json::Value::object();
                child["name"] = m->name;
                child["detail"] = format_func_signature(m);
                child["kind"] = 6; // Method
                int ml = m->line > 0 ? m->line - 1 : s_line;
                Json::Value mrange = Json::Value::object();
                Json::Value mstart = Json::Value::object();
                mstart["line"] = ml; mstart["character"] = 0;
                Json::Value mend = Json::Value::object();
                mend["line"] = ml; mend["character"] = static_cast<int>(m->name.size());
                mrange["start"] = mstart; mrange["end"] = mend;
                child["range"] = mrange;
                child["selectionRange"] = mrange;
                children.push_back(child);
            }
            sym["children"] = children;
            symbols.push_back(sym);
        } else if (auto fn = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = fn->name;
            sym["detail"] = format_func_signature(fn);
            sym["kind"] = 12; // Function
            int s_line = fn->line > 0 ? fn->line - 1 : 0;
            int e_line = find_block_end(content, s_line);
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            start["line"] = s_line; start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = e_line; end["character"] = 1;
            range["start"] = start; range["end"] = end;
            sym["range"] = range;

            Json::Value sel = Json::Value::object();
            Json::Value sel_start = Json::Value::object();
            sel_start["line"] = s_line; sel_start["character"] = 0;
            Json::Value sel_end = Json::Value::object();
            sel_end["line"] = s_line; sel_end["character"] = static_cast<int>(fn->name.size());
            sel["start"] = sel_start; sel["end"] = sel_end;
            sym["selectionRange"] = sel;
            symbols.push_back(sym);
        } else if (auto v = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = v->name;
            sym["detail"] = (v->type.has_value() && v->type.value()) ? v->type.value()->typeName : "variable";
            sym["kind"] = 13; // Variable
            int s_line = v->line > 0 ? v->line - 1 : 0;
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            start["line"] = s_line; start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = s_line; end["character"] = static_cast<int>(v->name.size());
            range["start"] = start; range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;
            symbols.push_back(sym);
        } else if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = e->name;
            sym["detail"] = "enum";
            sym["kind"] = 10; // Enum
            int s_line = e->line > 0 ? e->line - 1 : 0;
            int e_line = find_block_end(content, s_line);
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            start["line"] = s_line; start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = e_line; end["character"] = 1;
            range["start"] = start; range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;

            Json::Value children = Json::Value::array();
            for (const auto& var : e->variants) {
                Json::Value child = Json::Value::object();
                child["name"] = var.first;
                child["detail"] = e->name + "." + var.first;
                child["kind"] = 22; // EnumMember
                child["range"] = range;
                child["selectionRange"] = range;
                children.push_back(child);
            }
            sym["children"] = children;
            symbols.push_back(sym);
        } else if (auto td = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = td->name;
            sym["detail"] = "type";
            sym["kind"] = 26; // TypeParameter
            int s_line = td->line > 0 ? td->line - 1 : 0;
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            start["line"] = s_line; start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = s_line; end["character"] = static_cast<int>(td->name.size());
            range["start"] = start; range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;
            symbols.push_back(sym);
        }
    }

    return symbols;
}

// -----------------------------------------------------------------------------
// Workspace Symbol Handler (Ctrl+T Search Across Files)
// -----------------------------------------------------------------------------

static Json::Value handle_workspace_symbol(const Json::Value& params) {
    std::string query = params.has("query") ? params["query"].as_string() : "";
    std::string lower_query = query;
    for (char& c : lower_query) c = std::tolower(c);

    Json::Value symbols = Json::Value::array();

    for (const auto& [uri, snap] : g_document_snapshots) {
        Json::Value doc_params = Json::Value::object();
        Json::Value textDoc = Json::Value::object();
        textDoc["uri"] = uri;
        doc_params["textDocument"] = textDoc;
        Json::Value doc_syms = handle_document_symbol(doc_params);

        std::function<void(const Json::Value&, const std::string&)> collect = [&](const Json::Value& sym_list, const std::string& container) {
            if (!sym_list.is_array()) return;
            for (const auto& s : sym_list.arr_val) {
                std::string sname = s["name"].as_string();
                std::string lower_sname = sname;
                for (char& c : lower_sname) c = std::tolower(c);

                if (query.empty() || lower_sname.find(lower_query) != std::string::npos) {
                    Json::Value ws_sym = Json::Value::object();
                    ws_sym["name"] = sname;
                    ws_sym["kind"] = s["kind"];
                    Json::Value loc = Json::Value::object();
                    loc["uri"] = uri;
                    loc["range"] = s["range"];
                    ws_sym["location"] = loc;
                    if (!container.empty()) ws_sym["containerName"] = container;
                    symbols.push_back(ws_sym);
                }

                if (s.has("children")) {
                    collect(s["children"], sname);
                }
            }
        };

        collect(doc_syms, "");
    }

    return symbols;
}


static Json::Value handle_formatting(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    Json::Value edits = Json::Value::array();

    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) return edits;
    const auto& content = it->second.content;

    std::string formatted = LM::Formatter::format(content);

    int line_count = 0;
    int last_line_len = 0;
    for (char ch : content) {
        if (ch == '\n') {
            line_count++;
            last_line_len = 0;
        } else {
            last_line_len++;
        }
    }

    Json::Value edit = Json::Value::object();
    Json::Value range = Json::Value::object();
    Json::Value start = Json::Value::object();
    start["line"] = 0;
    start["character"] = 0;
    Json::Value end = Json::Value::object();
    end["line"] = line_count + 1;
    end["character"] = last_line_len;
    range["start"] = start;
    range["end"] = end;

    edit["range"] = range;
    edit["newText"] = formatted;
    edits.push_back(edit);
    return edits;
}

} // anonymous namespace

void LSP::run() {
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    std::cerr << "Lymar LSP server started (LSP v3.17 / JSON-RPC 2.0)..." << std::endl;

    while (std::cin) {
        std::string line;
        char c = 0;
        while (std::cin.get(c)) {
            if (c == '\r') {
                if (std::cin.peek() == '\n') std::cin.get(c);
                break;
            }
            if (c == '\n') break;
            line += c;
        }

        if (std::cin.eof() && line.empty()) break;
        if (line.empty()) continue;

        std::string lower_line = line;
        for (char& ch : lower_line) ch = std::tolower(ch);

        if (lower_line.rfind("content-length:", 0) == 0) {
            size_t colon_pos = line.find(':');
            int content_length = std::stoi(line.substr(colon_pos + 1));

            // Consume remaining headers until empty line
            while (std::cin.get(c)) {
                if (c == '\r') {
                    if (std::cin.peek() == '\n') std::cin.get(c);
                    break;
                }
                if (c == '\n') break;
                std::string extra_hdr;
                extra_hdr += c;
                while (std::cin.get(c)) {
                    if (c == '\r') {
                        if (std::cin.peek() == '\n') std::cin.get(c);
                        break;
                    }
                    if (c == '\n') break;
                    extra_hdr += c;
                }
                if (extra_hdr.empty()) break;
            }

            std::string payload(content_length, '\0');
            std::cin.read(&payload[0], content_length);

            Json::Parser parser(payload);
            Json::Value msg = parser.parse();
            if (!msg.is_object()) continue;

            std::string method = msg["method"].as_string();
            bool has_id = msg.has("id");
            Json::Value id = msg["id"];

            if (method == "initialize") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;

                Json::Value result = Json::Value::object();
                Json::Value caps = Json::Value::object();
                caps["textDocumentSync"] = 1;

                Json::Value comp = Json::Value::object();
                comp["resolveProvider"] = false;
                Json::Value triggers = Json::Value::array();
                triggers.push_back(".");
                triggers.push_back(":");
                triggers.push_back("?");
                triggers.push_back("(");
                triggers.push_back(",");
                triggers.push_back("\"");
                triggers.push_back("@");
                comp["triggerCharacters"] = triggers;
                caps["completionProvider"] = comp;
                caps["hoverProvider"] = true;

                Json::Value sig_help = Json::Value::object();
                Json::Value sig_triggers = Json::Value::array();
                sig_triggers.push_back("(");
                sig_triggers.push_back(",");
                sig_help["triggerCharacters"] = sig_triggers;
                caps["signatureHelpProvider"] = sig_help;

                caps["definitionProvider"] = true;
                caps["referencesProvider"] = true;
                caps["referenceProvider"] = true;
                caps["documentSymbolProvider"] = true;
                caps["workspaceSymbolProvider"] = true;
                caps["documentFormattingProvider"] = true;

                Json::Value server_info = Json::Value::object();
                server_info["name"] = "lymar-lsp";
                server_info["version"] = "0.0.1";

                result["capabilities"] = caps;
                result["serverInfo"] = server_info;
                res["result"] = result;
                send_json_rpc(res);
            } else if (method == "initialized") {
                // Initialized notification
            } else if (method == "shutdown") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = Json::Value();
                send_json_rpc(res);
            } else if (method == "exit") {
                break;
            } else if (method == "textDocument/didOpen") {
                const auto& doc = msg["params"]["textDocument"];
                std::string uri = doc["uri"].as_string();
                int version = static_cast<int>(doc["version"].as_int());
                std::string text = doc["text"].as_string();

                auto& snap = g_document_snapshots[uri];
                snap.uri = uri;
                snap.update_full(text, version);
                g_dependency_graph.invalidate(uri, g_document_snapshots);
                send_publish_diagnostics(uri, version, snap.diagnostics);
            } else if (method == "textDocument/didChange") {
                const auto& doc = msg["params"]["textDocument"];
                std::string uri = doc["uri"].as_string();
                int version = static_cast<int>(doc["version"].as_int());
                const auto& changes = msg["params"]["contentChanges"];

                if (changes.is_array() && changes.size() > 0) {
                    std::string new_text = changes[changes.size() - 1]["text"].as_string();
                    auto& snap = g_document_snapshots[uri];
                    snap.uri = uri;
                    snap.update_full(new_text, version);
                    g_dependency_graph.invalidate(uri, g_document_snapshots);
                    send_publish_diagnostics(uri, version, snap.diagnostics);
                }
            } else if (method == "textDocument/didClose") {
                std::string uri = msg["params"]["textDocument"]["uri"].as_string();
                send_publish_diagnostics(uri, -1, {});
            } else if (method == "textDocument/completion") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_completion(msg["params"]);
                send_json_rpc(res);
            } else if (method == "textDocument/hover") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_hover(msg["params"]);
                send_json_rpc(res);
            } else if (method == "textDocument/signatureHelp") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_signature_help(msg["params"]);
                send_json_rpc(res);
            } else if (method == "textDocument/definition") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_definition(msg["params"]);
                send_json_rpc(res);
            } else if (method == "textDocument/references") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_references(msg["params"]);
                send_json_rpc(res);
            } else if (method == "textDocument/documentSymbol") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_document_symbol(msg["params"]);
                send_json_rpc(res);
            } else if (method == "workspace/symbol") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_workspace_symbol(msg["params"]);
                send_json_rpc(res);
            } else if (method == "textDocument/formatting") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_formatting(msg["params"]);
                send_json_rpc(res);
            } else {
                if (has_id) {
                    Json::Value res = Json::Value::object();
                    res["jsonrpc"] = "2.0";
                    res["id"] = id;
                    Json::Value err = Json::Value::object();
                    err["code"] = -32601;
                    err["message"] = "Method not found: " + method;
                    res["error"] = err;
                    send_json_rpc(res);
                }
            }
        } else {
            // Legacy / CLI line-by-line fallback mode
            if (line == "exit") break;
            std::string active_uri = "file://active.lm";
            try {
                auto& snapshot = g_document_snapshots[active_uri];
                snapshot.uri = active_uri;
                snapshot.update_full(line);
                g_dependency_graph.invalidate(active_uri, g_document_snapshots);

                auto res = snapshot.last_check_result.value_or(Frontend::TypeCheckResult{nullptr, nullptr, false, {}});

                std::cout << "{\n";
                std::cout << "  \"success\": " << (res.success ? "true" : "false") << ",\n";
                std::cout << "  \"version\": " << snapshot.version << ",\n";
                std::cout << "  \"errors\": [\n";
                for (size_t i = 0; i < res.errors.size(); ++i) {
                    std::string err = res.errors[i];
                    size_t pos = 0;
                    while ((pos = err.find('\"', pos)) != std::string::npos) {
                        err.replace(pos, 1, "\\\"");
                        pos += 2;
                    }
                    std::cout << "    { \"message\": \"" << err << "\" }" << (i + 1 < res.errors.size() ? "," : "") << "\n";
                }
                std::cout << "  ]";

                if (snapshot.ast) {
                    struct HoleVisitor {
                        const Frontend::AST::TypedHoleExpr* hole = nullptr;
                        void visit(const std::shared_ptr<Frontend::AST::Statement>& stmt) {
                            if (!stmt) return;
                            if (auto expr_stmt = std::dynamic_pointer_cast<Frontend::AST::ExprStatement>(stmt)) {
                                visit_expr(expr_stmt->expression);
                            } else if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
                                for (const auto& s : block->statements) visit(s);
                            } else if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                                if (var_decl->initializer) visit_expr(var_decl->initializer);
                            }
                        }
                        void visit_expr(const std::shared_ptr<Frontend::AST::Expression>& expr) {
                            if (!expr) return;
                            if (auto h = std::dynamic_pointer_cast<Frontend::AST::TypedHoleExpr>(expr)) {
                                hole = h.get();
                            } else if (auto bin = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
                                visit_expr(bin->left);
                                visit_expr(bin->right);
                            } else if (auto assign = std::dynamic_pointer_cast<Frontend::AST::AssignExpr>(expr)) {
                                visit_expr(assign->value);
                            }
                        }
                    } visitor;

                    for (const auto& stmt : snapshot.ast->statements) {
                        visitor.visit(stmt);
                    }

                    if (visitor.hole) {
                        auto candidates = ProofAwareCompletionEngine::complete_hole(*visitor.hole, res.type_system);
                        std::cout << ",\n  \"completions\": [\n";
                        for (size_t i = 0; i < candidates.size(); ++i) {
                            std::cout << "    { \"label\": \"" << candidates[i].label
                                      << "\", \"detail\": \"" << candidates[i].detail
                                      << "\", \"score\": " << candidates[i].score
                                      << ", \"proven\": " << (candidates[i].proven ? "true" : "false")
                                      << " }" << (i + 1 < candidates.size() ? "," : "") << "\n";
                        }
                        std::cout << "  ]";
                    }
                }
                std::cout << "\n}\n" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "{ \"success\": false, \"errors\": [{ \"message\": \"" << e.what() << "\" }] }\n" << std::endl;
            }
        }
    }
}

} // namespace LM
