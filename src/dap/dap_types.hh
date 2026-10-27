#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <algorithm>

namespace LM {
namespace DAP {

namespace DapJson {

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
        static const std::string empty_str;
        return is_string() ? str_val : empty_str;
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
            if (match(',')) continue;
            if (match('}')) break;
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
            if (match(',')) continue;
            if (match(']')) break;
            break;
        }
        return arr;
    }

    Value parse_string() {
        get();
        std::string res;
        while (idx < s.size()) {
            char c = s[idx++];
            if (c == '"') return Value(res);
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
        if (s.compare(idx, 4, "null") == 0) idx += 4;
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
        if (is_fp) return Value(std::strtod(sub.c_str(), nullptr));
        return Value(static_cast<int64_t>(std::strtoll(sub.c_str(), nullptr, 10)));
    }
};

} // namespace DapJson

// DAP protocol entities
struct DapSource {
    std::string name;
    std::string path;

    DapJson::Value to_json() const {
        DapJson::Value val = DapJson::Value::object();
        val["name"] = name;
        val["path"] = path;
        return val;
    }

    static DapSource from_json(const DapJson::Value& val) {
        DapSource src;
        if (val.has("name")) src.name = val["name"].as_string();
        if (val.has("path")) src.path = val["path"].as_string();
        return src;
    }
};

struct DapSourceBreakpoint {
    int line = 0;
    std::string condition;

    static DapSourceBreakpoint from_json(const DapJson::Value& val) {
        DapSourceBreakpoint sbp;
        if (val.has("line")) sbp.line = static_cast<int>(val["line"].as_int());
        if (val.has("condition")) sbp.condition = val["condition"].as_string();
        return sbp;
    }
};

struct DapBreakpoint {
    int id = 0;
    bool verified = true;
    std::string message;
    DapSource source;
    int line = 0;

    DapJson::Value to_json() const {
        DapJson::Value val = DapJson::Value::object();
        val["id"] = id;
        val["verified"] = verified;
        if (!message.empty()) val["message"] = message;
        val["source"] = source.to_json();
        val["line"] = line;
        return val;
    }
};

struct DapThread {
    int id = 1;
    std::string name = "Main Thread";

    DapJson::Value to_json() const {
        DapJson::Value val = DapJson::Value::object();
        val["id"] = id;
        val["name"] = name;
        return val;
    }
};

struct DapStackFrame {
    int id = 0;
    std::string name;
    DapSource source;
    int line = 0;
    int column = 1;

    DapJson::Value to_json() const {
        DapJson::Value val = DapJson::Value::object();
        val["id"] = id;
        val["name"] = name;
        val["source"] = source.to_json();
        val["line"] = line;
        val["column"] = column;
        return val;
    }
};

struct DapScope {
    std::string name;
    int variablesReference = 0;
    bool expensive = false;

    DapJson::Value to_json() const {
        DapJson::Value val = DapJson::Value::object();
        val["name"] = name;
        val["variablesReference"] = variablesReference;
        val["expensive"] = expensive;
        return val;
    }
};

struct DapVariable {
    std::string name;
    std::string value;
    std::string type;
    int variablesReference = 0;

    DapJson::Value to_json() const {
        DapJson::Value val = DapJson::Value::object();
        val["name"] = name;
        val["value"] = value;
        if (!type.empty()) val["type"] = type;
        val["variablesReference"] = variablesReference;
        return val;
    }
};

struct StoppedEventParams {
    std::string reason; // "breakpoint", "step", "pause", "exception", "entry"
    int threadId = 1;
    std::string description;
    std::string text;
    bool allThreadsStopped = true;
};

} // namespace DAP
} // namespace LM
