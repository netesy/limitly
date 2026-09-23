#include "limitly.hh"
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
    std::string source = "limitly";
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

    // 4. Check AST variables
    if (current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                if (var_decl->name == receiver) {
                    if (var_decl->type.has_value() && var_decl->type.value()) {
                        std::string tname = var_decl->type.value()->typeName;
                        res.category = SymbolTypeCategory::Frame;
                        res.name = tname;
                        return res;
                    }
                    if (var_decl->initializer) {
                        if (auto fi = std::dynamic_pointer_cast<Frontend::AST::FrameInstantiationExpr>(var_decl->initializer)) {
                            res.category = SymbolTypeCategory::Frame;
                            res.name = fi->frameName;
                            return res;
                        }
                    }
                    if (var_decl->inferred_type && var_decl->inferred_type->tag == TypeTag::Frame) {
                        if (const auto* ft = std::get_if<FrameType>(&var_decl->inferred_type->extra)) {
                            res.category = SymbolTypeCategory::Frame;
                            res.name = ft->name;
                            return res;
                        }
                    }
                }
            }
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
    ReceiverContext rctx = extract_receiver_context(content, cursor_idx);

    if (rctx.is_member_access) {
        // Dot access / member completion
        ResolvedReceiver rec = resolve_receiver(rctx.receiver, line, snap);
        std::unordered_set<std::string> seen;

        if (rec.category == SymbolTypeCategory::Frame) {
            // Find frame in AST
            if (current_ast) {
                for (const auto& stmt : current_ast->statements) {
                    if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                        if (f->name == rec.name) {
                            // Fields
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
                            // Init method
                            if (f->init && seen.insert("init").second) {
                                Json::Value item = Json::Value::object();
                                item["label"] = "init";
                                item["kind"] = 2; // Method
                                item["detail"] = format_method_signature(f->init, f->name);
                                item["insertText"] = "init()";
                                item["sortText"] = "010_init";
                                item["insertTextFormat"] = 1;
                                items.push_back(item);
                            }
                            // Methods
                            for (const auto& m : f->methods) {
                                if (seen.insert(m->name).second) {
                                    Json::Value item = Json::Value::object();
                                    item["label"] = m->name;
                                    item["kind"] = 2; // Method
                                    item["detail"] = format_method_signature(m, f->name);
                                    item["insertText"] = m->name + "()";
                                    item["sortText"] = "010_" + m->name;
                                    items.push_back(item);
                                }
                            }
                            // Implemented traits
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
                                                    item["insertText"] = m->name + "()";
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
            // Check frame declarations from type checker result
            if (snap.last_check_result.has_value()) {
                auto fit = snap.last_check_result->frame_declarations.find(rec.name);
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
                }
            }
        } else if (rec.category == SymbolTypeCategory::Module) {
            // Module symbols
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
        } else if (rec.category == SymbolTypeCategory::Trait) {
            if (current_ast) {
                for (const auto& stmt : current_ast->statements) {
                    if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                        if (t->name == rec.name) {
                            for (const auto& m : t->methods) {
                                if (seen.insert(m->name).second) {
                                    Json::Value item = Json::Value::object();
                                    item["label"] = m->name;
                                    item["kind"] = 2; // Method
                                    item["detail"] = format_func_signature(m);
                                    item["insertText"] = m->name + "()";
                                    item["sortText"] = "010_" + m->name;
                                    items.push_back(item);
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
        }

        res["items"] = items;
        return res;
    }

    // Proof-aware completion if typed hole exists in AST
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
        }
    }

    // Local and top-level declarations
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
                    item["sortText"] = "100_" + var_decl->name;
                    items.push_back(item);
                }
            } else if (auto fn_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
                if (seen.insert(fn_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = fn_decl->name;
                    item["kind"] = 3; // Function
                    item["detail"] = format_func_signature(fn_decl);
                    item["insertText"] = fn_decl->name + "()";
                    item["sortText"] = "100_" + fn_decl->name;
                    items.push_back(item);
                }
            } else if (auto frame_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (seen.insert(frame_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = frame_decl->name;
                    item["kind"] = 7; // Class
                    item["detail"] = "frame " + frame_decl->name;
                    item["insertText"] = frame_decl->name;
                    item["sortText"] = "100_" + frame_decl->name;
                    items.push_back(item);
                }
            } else if (auto trait_decl = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                if (seen.insert(trait_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = trait_decl->name;
                    item["kind"] = 8; // Interface
                    item["detail"] = "trait " + trait_decl->name;
                    item["insertText"] = trait_decl->name;
                    item["sortText"] = "100_" + trait_decl->name;
                    items.push_back(item);
                }
            } else if (auto enum_decl = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                if (seen.insert(enum_decl->name).second) {
                    Json::Value item = Json::Value::object();
                    item["label"] = enum_decl->name;
                    item["kind"] = 13; // Enum
                    item["detail"] = "enum " + enum_decl->name;
                    item["insertText"] = enum_decl->name;
                    item["sortText"] = "100_" + enum_decl->name;
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
                    item["sortText"] = "100_" + imp_name;
                    items.push_back(item);
                }
            }
        }
    }

    // Built-in keywords
    static const std::vector<std::string> keywords = {
        "var", "val", "const", "fn", "frame", "trait", "if", "elif", "else",
        "while", "for", "iter", "in", "match", "return", "import", "as",
        "pub", "prot", "ok", "err", "true", "false", "nil", "break", "continue"
    };
    for (const auto& kw : keywords) {
        Json::Value item = Json::Value::object();
        item["label"] = kw;
        item["kind"] = 14;
        item["detail"] = "keyword";
        item["insertText"] = kw;
        item["sortText"] = "200_" + kw;
        items.push_back(item);
    }

    res["items"] = items;
    return res;
}

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

    // Check if word is part of receiver.word
    ReceiverContext rctx = extract_receiver_context(content, word_end);
    if (rctx.is_member_access && !rctx.receiver.empty()) {
        ResolvedReceiver rec = resolve_receiver(rctx.receiver, line, snap);
        if (rec.category == SymbolTypeCategory::Frame && current_ast) {
            for (const auto& stmt : current_ast->statements) {
                if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    if (f->name == rec.name) {
                        for (const auto& field : f->fields) {
                            if (field->name == word) {
                                hover_info = "```limitly\n(field) " + f->name + "." + field->name;
                                if (field->type) hover_info += ": " + field->type->typeName;
                                hover_info += "\n```";
                                break;
                            }
                        }
                        if (hover_info.empty()) {
                            if (word == "init" && f->init) {
                                hover_info = "```limitly\n" + format_method_signature(f->init, f->name) + "\n```";
                            } else {
                                for (const auto& m : f->methods) {
                                    if (m->name == word) {
                                        hover_info = "```limitly\n(method) " + format_method_signature(m, f->name) + "\n```";
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
                                                    hover_info = "```limitly\n(trait method) " + format_func_signature(m) + "\n```";
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
        } else if (rec.category == SymbolTypeCategory::Module) {
            if (snap.last_check_result.has_value()) {
                auto mit = snap.last_check_result->registered_modules.find(rec.name);
                if (mit != snap.last_check_result->registered_modules.end()) {
                    auto sit = mit->second.symbols.find(word);
                    if (sit != mit->second.symbols.end()) {
                        hover_info = "```limitly\n(module member) " + rec.name + "." + word;
                        if (sit->second) hover_info += ": " + sit->second->toString();
                        hover_info += "\n```";
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
                    hover_info = "```limitly\nvar " + var_decl->name;
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
                    hover_info = "```limitly\n" + format_func_signature(fn_decl) + "\n```";
                    break;
                }
            } else if (auto frame_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (frame_decl->name == word) {
                    hover_info = "```limitly\nframe " + frame_decl->name;
                    if (!frame_decl->implements.empty()) {
                        hover_info += ": ";
                        for (size_t i = 0; i < frame_decl->implements.size(); ++i) {
                            if (i > 0) hover_info += ", ";
                            hover_info += frame_decl->implements[i];
                        }
                    }
                    hover_info += "\n```";
                    break;
                }
            } else if (auto trait_decl = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                if (trait_decl->name == word) {
                    hover_info = "```limitly\ntrait " + trait_decl->name + "\n```";
                    break;
                }
            } else if (auto enum_decl = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                if (enum_decl->name == word) {
                    hover_info = "```limitly\nenum " + enum_decl->name + "\n```";
                    break;
                }
            }
        }
    }

    // Built-in function lookup
    if (hover_info.empty() && snap.last_check_result.has_value()) {
        auto it_sig = snap.last_check_result->function_signatures.find(word);
        if (it_sig != snap.last_check_result->function_signatures.end()) {
            hover_info = "```limitly\n(builtin) fn " + word + "(";
            for (size_t pi = 0; pi < it_sig->second.param_types.size(); ++pi) {
                if (pi > 0) hover_info += ", ";
                hover_info += it_sig->second.param_types[pi] ? it_sig->second.param_types[pi]->toString() : "any";
            }
            hover_info += "): " + (it_sig->second.return_type ? it_sig->second.return_type->toString() : "void");
            hover_info += "\n```";
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
        } else if (rec.category == SymbolTypeCategory::Module && snap.last_check_result.has_value()) {
            std::string qname = rec.name + "." + method_name;
            auto sig_it = snap.last_check_result->function_signatures.find(qname);
            if (sig_it != snap.last_check_result->function_signatures.end()) {
                Json::Value sig_info = Json::Value::object();
                std::string label = "fn " + qname + "(";
                Json::Value params_arr = Json::Value::array();
                for (size_t pi = 0; pi < sig_it->second.param_types.size(); ++pi) {
                    if (pi > 0) label += ", ";
                    std::string plabel = "arg" + std::to_string(pi) + ": " + (sig_it->second.param_types[pi] ? sig_it->second.param_types[pi]->toString() : "any");
                    label += plabel;
                    Json::Value p_info = Json::Value::object();
                    p_info["label"] = plabel;
                    params_arr.push_back(p_info);
                }
                label += "): " + (sig_it->second.return_type ? sig_it->second.return_type->toString() : "void");
                sig_info["label"] = label;
                sig_info["parameters"] = params_arr;
                sigs.push_back(sig_info);
                res["signatures"] = sigs;
                return res;
            }
        }
    } else {
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

        if (snap.last_check_result.has_value()) {
            auto it_sig = snap.last_check_result->function_signatures.find(callee);
            if (it_sig != snap.last_check_result->function_signatures.end()) {
                Json::Value sig_info = Json::Value::object();
                std::string label = "fn " + callee + "(";
                Json::Value params_arr = Json::Value::array();
                for (size_t pi = 0; pi < it_sig->second.param_types.size(); ++pi) {
                    if (pi > 0) label += ", ";
                    std::string plabel = "arg" + std::to_string(pi) + ": " + (it_sig->second.param_types[pi] ? it_sig->second.param_types[pi]->toString() : "any");
                    label += plabel;
                    Json::Value p_info = Json::Value::object();
                    p_info["label"] = plabel;
                    params_arr.push_back(p_info);
                }
                label += "): " + (it_sig->second.return_type ? it_sig->second.return_type->toString() : "void");
                sig_info["label"] = label;
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
    if (rctx.is_member_access && !rctx.receiver.empty()) {
        ResolvedReceiver rec = resolve_receiver(rctx.receiver, line, snap);
        if (rec.category == SymbolTypeCategory::Frame && current_ast) {
            for (const auto& stmt : current_ast->statements) {
                if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                    if (f->name == rec.name) {
                        for (const auto& field : f->fields) {
                            if (field->name == word) {
                                Json::Value loc = Json::Value::object();
                                loc["uri"] = uri;
                                Json::Value range = Json::Value::object();
                                Json::Value start = Json::Value::object();
                                int def_line = field->line > 0 ? field->line - 1 : (f->line > 0 ? f->line - 1 : 0);
                                if (field->line == 0) {
                                    // Scan content for field declaration
                                    std::istringstream iss(content);
                                    std::string sline;
                                    int cline = 0;
                                    while (std::getline(iss, sline)) {
                                        if (sline.find(word) != std::string::npos && (sline.find(':') != std::string::npos || sline.find("var") != std::string::npos || sline.find("pub") != std::string::npos)) {
                                            def_line = cline;
                                            break;
                                        }
                                        cline++;
                                    }
                                }
                                start["line"] = def_line;
                                start["character"] = 0;
                                Json::Value end = Json::Value::object();
                                end["line"] = start["line"];
                                end["character"] = static_cast<int>(word.size());
                                range["start"] = start;
                                range["end"] = end;
                                loc["range"] = range;
                                return loc;
                            }
                        }
                        if (word == "init" && f->init) {
                            Json::Value loc = Json::Value::object();
                            loc["uri"] = uri;
                            Json::Value range = Json::Value::object();
                            Json::Value start = Json::Value::object();
                            int def_line = f->init->line > 0 ? f->init->line - 1 : (f->line > 0 ? f->line - 1 : 0);
                            start["line"] = def_line;
                            start["character"] = 0;
                            Json::Value end = Json::Value::object();
                            end["line"] = start["line"];
                            end["character"] = 4;
                            range["start"] = start;
                            range["end"] = end;
                            loc["range"] = range;
                            return loc;
                        }
                        for (const auto& m : f->methods) {
                            if (m->name == word) {
                                Json::Value loc = Json::Value::object();
                                loc["uri"] = uri;
                                Json::Value range = Json::Value::object();
                                Json::Value start = Json::Value::object();
                                int def_line = m->line > 0 ? m->line - 1 : (f->line > 0 ? f->line - 1 : 0);
                                if (m->line == 0) {
                                    // Scan content for method declaration
                                    std::istringstream iss(content);
                                    std::string sline;
                                    int cline = 0;
                                    while (std::getline(iss, sline)) {
                                        if (sline.find(word) != std::string::npos && sline.find("fn ") != std::string::npos) {
                                            def_line = cline;
                                            break;
                                        }
                                        cline++;
                                    }
                                }
                                start["line"] = def_line;
                                start["character"] = 0;
                                Json::Value end = Json::Value::object();
                                end["line"] = start["line"];
                                end["character"] = static_cast<int>(word.size());
                                range["start"] = start;
                                range["end"] = end;
                                loc["range"] = range;
                                return loc;
                            }
                        }
                    }
                }
            }
        }
    }

    if (current_ast) {
        for (const auto& stmt : current_ast->statements) {
            if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                if (var_decl->name == word) {
                    Json::Value loc = Json::Value::object();
                    loc["uri"] = uri;
                    Json::Value range = Json::Value::object();
                    Json::Value start = Json::Value::object();
                    start["line"] = var_decl->line > 0 ? var_decl->line - 1 : 0;
                    start["character"] = 0;
                    Json::Value end = Json::Value::object();
                    end["line"] = start["line"];
                    end["character"] = static_cast<int>(word.size());
                    range["start"] = start;
                    range["end"] = end;
                    loc["range"] = range;
                    return loc;
                }
            } else if (auto fn_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
                if (fn_decl->name == word) {
                    Json::Value loc = Json::Value::object();
                    loc["uri"] = uri;
                    Json::Value range = Json::Value::object();
                    Json::Value start = Json::Value::object();
                    start["line"] = fn_decl->line > 0 ? fn_decl->line - 1 : 0;
                    start["character"] = 0;
                    Json::Value end = Json::Value::object();
                    end["line"] = start["line"];
                    end["character"] = static_cast<int>(word.size());
                    range["start"] = start;
                    range["end"] = end;
                    loc["range"] = range;
                    return loc;
                }
            } else if (auto frame_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (frame_decl->name == word) {
                    Json::Value loc = Json::Value::object();
                    loc["uri"] = uri;
                    Json::Value range = Json::Value::object();
                    Json::Value start = Json::Value::object();
                    start["line"] = frame_decl->line > 0 ? frame_decl->line - 1 : 0;
                    start["character"] = 0;
                    Json::Value end = Json::Value::object();
                    end["line"] = start["line"];
                    end["character"] = static_cast<int>(word.size());
                    range["start"] = start;
                    range["end"] = end;
                    loc["range"] = range;
                    return loc;
                }
            } else if (auto trait_decl = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
                if (trait_decl->name == word) {
                    Json::Value loc = Json::Value::object();
                    loc["uri"] = uri;
                    Json::Value range = Json::Value::object();
                    Json::Value start = Json::Value::object();
                    start["line"] = trait_decl->line > 0 ? trait_decl->line - 1 : 0;
                    start["character"] = 0;
                    Json::Value end = Json::Value::object();
                    end["line"] = start["line"];
                    end["character"] = static_cast<int>(word.size());
                    range["start"] = start;
                    range["end"] = end;
                    loc["range"] = range;
                    return loc;
                }
            } else if (auto enum_decl = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
                if (enum_decl->name == word) {
                    Json::Value loc = Json::Value::object();
                    loc["uri"] = uri;
                    Json::Value range = Json::Value::object();
                    Json::Value start = Json::Value::object();
                    start["line"] = enum_decl->line > 0 ? enum_decl->line - 1 : 0;
                    start["character"] = 0;
                    Json::Value end = Json::Value::object();
                    end["line"] = start["line"];
                    end["character"] = static_cast<int>(word.size());
                    range["start"] = start;
                    range["end"] = end;
                    loc["range"] = range;
                    return loc;
                }
            }
        }
    }

    return Json::Value();
}

static Json::Value handle_document_symbol(const Json::Value& params) {
    std::string uri = params["textDocument"]["uri"].as_string();
    Json::Value symbols = Json::Value::array();

    auto it = g_document_snapshots.find(uri);
    if (it == g_document_snapshots.end()) return symbols;
    auto current_ast = it->second.get_ast();
    if (!current_ast) return symbols;

    for (const auto& stmt : current_ast->statements) {
        if (auto f = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = f->name;
            sym["kind"] = 5; // Class
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            int s_line = f->line > 0 ? f->line - 1 : 0;
            start["line"] = s_line;
            start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = s_line + 5;
            end["character"] = 0;
            range["start"] = start;
            range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;

            Json::Value children = Json::Value::array();
            for (const auto& field : f->fields) {
                Json::Value child = Json::Value::object();
                child["name"] = field->name;
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
                child["kind"] = 6; // Method
                int il = f->init->line > 0 ? f->init->line - 1 : s_line;
                Json::Value crange = Json::Value::object();
                Json::Value cstart = Json::Value::object();
                cstart["line"] = il; cstart["character"] = 0;
                Json::Value cend = Json::Value::object();
                cend["line"] = il; cend["character"] = 4;
                crange["start"] = cstart; crange["end"] = cend;
                child["range"] = crange;
                child["selectionRange"] = crange;
                children.push_back(child);
            }
            for (const auto& m : f->methods) {
                Json::Value child = Json::Value::object();
                child["name"] = m->name;
                child["kind"] = 6; // Method
                int ml = m->line > 0 ? m->line - 1 : s_line;
                Json::Value crange = Json::Value::object();
                Json::Value cstart = Json::Value::object();
                cstart["line"] = ml; cstart["character"] = 0;
                Json::Value cend = Json::Value::object();
                cend["line"] = ml; cend["character"] = static_cast<int>(m->name.size());
                crange["start"] = cstart; crange["end"] = cend;
                child["range"] = crange;
                child["selectionRange"] = crange;
                children.push_back(child);
            }
            sym["children"] = children;
            symbols.push_back(sym);
        } else if (auto t = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = t->name;
            sym["kind"] = 11; // Interface
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            int s_line = t->line > 0 ? t->line - 1 : 0;
            start["line"] = s_line;
            start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = s_line + 3;
            end["character"] = 0;
            range["start"] = start;
            range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;

            Json::Value children = Json::Value::array();
            for (const auto& m : t->methods) {
                Json::Value child = Json::Value::object();
                child["name"] = m->name;
                child["kind"] = 6; // Method
                child["range"] = range;
                child["selectionRange"] = range;
                children.push_back(child);
            }
            sym["children"] = children;
            symbols.push_back(sym);
        } else if (auto fn = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = fn->name;
            sym["kind"] = 12; // Function
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            int s_line = fn->line > 0 ? fn->line - 1 : 0;
            start["line"] = s_line;
            start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = s_line + 2;
            end["character"] = 0;
            range["start"] = start;
            range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;
            symbols.push_back(sym);
        } else if (auto v = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = v->name;
            sym["kind"] = 13; // Variable
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            start["line"] = v->line > 0 ? v->line - 1 : 0;
            start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = start["line"];
            end["character"] = static_cast<int>(v->name.size());
            range["start"] = start;
            range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;
            symbols.push_back(sym);
        } else if (auto e = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(stmt)) {
            Json::Value sym = Json::Value::object();
            sym["name"] = e->name;
            sym["kind"] = 10; // Enum
            Json::Value range = Json::Value::object();
            Json::Value start = Json::Value::object();
            int s_line = e->line > 0 ? e->line - 1 : 0;
            start["line"] = s_line;
            start["character"] = 0;
            Json::Value end = Json::Value::object();
            end["line"] = s_line + 3;
            end["character"] = 0;
            range["start"] = start;
            range["end"] = end;
            sym["range"] = range;
            sym["selectionRange"] = range;

            Json::Value children = Json::Value::array();
            for (const auto& var : e->variants) {
                Json::Value child = Json::Value::object();
                child["name"] = var.first;
                child["kind"] = 22; // EnumMember
                child["range"] = range;
                child["selectionRange"] = range;
                children.push_back(child);
            }
            sym["children"] = children;
            symbols.push_back(sym);
        }
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

    std::cerr << "Limitly LSP server started (LSP v3.17 / JSON-RPC 2.0)..." << std::endl;

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
                caps["documentSymbolProvider"] = true;
                caps["documentFormattingProvider"] = true;

                Json::Value server_info = Json::Value::object();
                server_info["name"] = "limitly-lsp";
                server_info["version"] = "1.0.0";

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
            } else if (method == "textDocument/documentSymbol") {
                Json::Value res = Json::Value::object();
                res["jsonrpc"] = "2.0";
                res["id"] = id;
                res["result"] = handle_document_symbol(msg["params"]);
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
