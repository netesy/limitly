#include "limitly.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/type_checker.hh"
#include "frontend/module_manager.hh"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <functional>
#include <limits>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace LM {
namespace {

struct Json {
    using Object = std::map<std::string, Json>;
    using Array = std::vector<Json>;
    std::variant<std::nullptr_t, bool, double, std::string, Object, Array> value = nullptr;
    const Json* get(const std::string& key) const {
        auto object = std::get_if<Object>(&value);
        if (!object) return nullptr;
        auto it = object->find(key);
        return it == object->end() ? nullptr : &it->second;
    }
    std::string string_or(std::string fallback = {}) const {
        if (auto string = std::get_if<std::string>(&value)) return *string;
        return fallback;
    }
    int int_or(int fallback = 0) const {
        if (auto number = std::get_if<double>(&value)) return static_cast<int>(*number);
        return fallback;
    }
};

class JsonParser {
    const std::string& input;
    size_t cursor = 0;
    void whitespace() { while (cursor < input.size() && std::isspace(static_cast<unsigned char>(input[cursor]))) ++cursor; }
    std::string parse_string() {
        std::string result;
        ++cursor;
        while (cursor < input.size() && input[cursor] != '"') {
            char c = input[cursor++];
            if (c == '\\' && cursor < input.size()) {
                char escaped = input[cursor++];
                if (escaped == 'n') result += '\n';
                else if (escaped == 'r') result += '\r';
                else if (escaped == 't') result += '\t';
                else result += escaped;
            } else result += c;
        }
        if (cursor < input.size()) ++cursor;
        return result;
    }
    Json parse_value() {
        whitespace();
        if (cursor >= input.size()) return {};
        if (input[cursor] == '"') return Json{parse_string()};
        if (input[cursor] == '{') {
            Json::Object object; ++cursor; whitespace();
            while (cursor < input.size() && input[cursor] != '}') {
                std::string key = parse_string(); whitespace();
                if (cursor < input.size() && input[cursor] == ':') ++cursor;
                object.emplace(std::move(key), parse_value()); whitespace();
                if (cursor < input.size() && input[cursor] == ',') { ++cursor; whitespace(); } else break;
            }
            if (cursor < input.size()) ++cursor;
            return Json{std::move(object)};
        }
        if (input[cursor] == '[') {
            Json::Array array; ++cursor; whitespace();
            while (cursor < input.size() && input[cursor] != ']') {
                array.push_back(parse_value()); whitespace();
                if (cursor < input.size() && input[cursor] == ',') { ++cursor; whitespace(); } else break;
            }
            if (cursor < input.size()) ++cursor;
            return Json{std::move(array)};
        }
        if (input.compare(cursor, 4, "true") == 0) { cursor += 4; return Json{true}; }
        if (input.compare(cursor, 5, "false") == 0) { cursor += 5; return Json{false}; }
        if (input.compare(cursor, 4, "null") == 0) { cursor += 4; return {}; }
        size_t start = cursor;
        while (cursor < input.size() && (std::isdigit(static_cast<unsigned char>(input[cursor])) || input[cursor] == '-' || input[cursor] == '.')) ++cursor;
        return Json{std::stod(input.substr(start, cursor - start))};
    }
public:
    explicit JsonParser(const std::string& source) : input(source) {}
    Json parse() { return parse_value(); }
};

std::string escape_json(const std::string& value) {
    std::string result;
    for (char c : value) {
        if (c == '"' || c == '\\') { result += '\\'; result += c; }
        else if (c == '\n') result += "\\n";
        else if (c == '\r') result += "\\r";
        else if (c == '\t') result += "\\t";
        else result += c;
    }
    return result;
}

void send_message(const std::string& payload) {
    std::cout << "Content-Length: " << payload.size() << "\r\n\r\n" << payload;
    std::cout.flush();
}

size_t offset_at(const std::string& text, int line, int character) {
    size_t offset = 0;
    for (int current = 0; current < line && offset < text.size(); ++current) {
        size_t newline = text.find('\n', offset);
        offset = newline == std::string::npos ? text.size() : newline + 1;
    }
    return std::min(text.size(), offset + static_cast<size_t>(std::max(0, character)));
}

struct Document { std::string text; int version = 0; };

std::vector<std::string> diagnostics_for(const std::string& uri, const Document& document) {
    std::vector<std::string> errors;
    try {
        Frontend::Scanner scanner(document.text);
        scanner.scanTokens();
        Frontend::Parser parser(scanner, false);
        auto ast = parser.parse();
        Frontend::ModuleManager::getInstance().resolve_all(ast, uri);
        auto result = Frontend::TypeCheckerFactory::check_program(ast, document.text, uri);
        errors = std::move(result.errors);
    } catch (const std::exception& error) { errors.push_back(error.what()); }
    return errors;
}

std::vector<Frontend::TypedHoleInfo> typed_holes_for(
    const std::string& uri, const Document& document) {
    try {
        Frontend::Scanner scanner(document.text);
        scanner.scanTokens();
        Frontend::Parser parser(scanner, false);
        auto ast = parser.parse();
        Frontend::ModuleManager::getInstance().resolve_all(ast, uri);
        return Frontend::TypeCheckerFactory::check_program(
            ast, document.text, uri).typed_holes;
    } catch (...) {
        return {};
    }
}

void publish_diagnostics(const std::string& uri, const Document& document) {
    auto errors = diagnostics_for(uri, document);
    std::ostringstream out;
    out << "{\"jsonrpc\":\"2.0\",\"method\":\"textDocument/publishDiagnostics\",\"params\":{\"uri\":\""
        << escape_json(uri) << "\",\"version\":" << document.version << ",\"diagnostics\":[";
    for (size_t i = 0; i < errors.size(); ++i) {
        if (i) out << ',';
        out << "{\"range\":{\"start\":{\"line\":0,\"character\":0},\"end\":{\"line\":0,\"character\":1}},"
               "\"severity\":1,\"source\":\"limitly\",\"message\":\"" << escape_json(errors[i]) << "\"}";
    }
    out << "]}}";
    send_message(out.str());
}

std::string completion_items(const Document& document, int line) {
    auto holes = typed_holes_for("lsp-completion", document);
    const Frontend::TypedHoleInfo* hole = nullptr;
    for (const auto& candidate : holes) {
        if (candidate.line == line + 1) { hole = &candidate; break; }
    }
    TypePtr expected_type = hole ? hole->expected_type : nullptr;
    std::string expected = expected_type ? expected_type->toString() : "any";

    struct Item { std::string label, detail; };
    std::vector<Item> items;
    auto add = [&](std::string label, std::string detail) {
        if (std::none_of(items.begin(), items.end(), [&](const Item& item) { return item.label == label; }))
            items.push_back({std::move(label), std::move(detail)});
    };
    TypePtr base = expected_type;
    const RefinedType* refined = nullptr;
    if (expected_type && expected_type->tag == TypeTag::Refined) {
        refined = std::get_if<RefinedType>(&expected_type->extra);
        if (refined) base = refined->baseType;
    }
    if (base && base->tag == TypeTag::Bool) { add("true", "bool inhabitant"); add("false", "bool inhabitant"); }
    else if (base && base->tag == TypeTag::String) add("\"\"", "str inhabitant");
    else if (base && (base->tag == TypeTag::Int || base->tag == TypeTag::Int64 ||
                      base->tag == TypeTag::Int32 || base->tag == TypeTag::UInt)) {
        bool found = false;
        std::vector<int64_t> candidates = {0, 1, -1};
        std::function<void(const std::shared_ptr<Frontend::AST::Expression>&)> collect_bounds;
        collect_bounds = [&](const auto& expression) {
            if (auto literal = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(expression)) {
                if (std::holds_alternative<std::string>(literal->value)) {
                    try {
                        int64_t value = std::stoll(std::get<std::string>(literal->value));
                        candidates.push_back(value);
                        if (value < std::numeric_limits<int64_t>::max()) candidates.push_back(value + 1);
                        if (value > std::numeric_limits<int64_t>::min()) candidates.push_back(value - 1);
                    } catch (...) {}
                }
            } else if (auto binary = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expression)) {
                collect_bounds(binary->left);
                collect_bounds(binary->right);
            } else if (auto unary = std::dynamic_pointer_cast<Frontend::AST::UnaryExpr>(expression)) {
                collect_bounds(unary->right);
            }
        };
        if (refined) collect_bounds(refined->condition);
        std::sort(candidates.begin(), candidates.end());
        candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
        for (int64_t witness : candidates) {
            auto literal = std::make_shared<Frontend::AST::LiteralExpr>();
            literal->literalType = Frontend::TokenType::INT_LITERAL;
            literal->value = std::to_string(witness);
            if (!refined || Frontend::SMTVerifier::verify_refinement(
                    refined->condition, literal).status == Frontend::SMTProofStatus::Proven) {
                add(std::to_string(witness), refined
                    ? "statically proves " + expected : "integer inhabitant");
                found = true;
                break;
            }
        }
        if (!found) add("0", "candidate; no bounded witness was proven");
    } else add("nil", "fallback inhabitant");
    if (hole) for (const auto& binding : hole->compatible_bindings)
        add(binding, "compiler-checked binding for " + expected);
    std::ostringstream out; out << '[';
    for (size_t i = 0; i < items.size(); ++i) {
        if (i) out << ',';
        out << "{\"label\":\"" << escape_json(items[i].label) << "\",\"kind\":12,\"detail\":\""
            << escape_json(items[i].detail) << "\",\"sortText\":\"" << i << "\"}";
    }
    out << ']'; return out.str();
}

const Json* path(const Json& root, std::initializer_list<const char*> keys) {
    const Json* value = &root;
    for (auto key : keys) { value = value->get(key); if (!value) return nullptr; }
    return value;
}

} // namespace

void LSP::run() {
    std::unordered_map<std::string, Document> documents;
    std::string header;
    while (std::getline(std::cin, header)) {
        if (header == "exit") break;
        if (!header.starts_with("Content-Length:")) {
            // Preserve the original one-line diagnostic protocol for scripts.
            Document document{header, 0};
            auto errors = diagnostics_for("lsp-input", document);
            std::cout << "{\n  \"success\": " << (errors.empty() ? "true" : "false") << ",\n  \"errors\": [";
            for (size_t i = 0; i < errors.size(); ++i) std::cout << (i ? "," : "") << "{\"message\":\"" << escape_json(errors[i]) << "\"}";
            std::cout << "]\n}\n\n";
            continue;
        }
        size_t length = std::stoul(header.substr(header.find(':') + 1));
        while (std::getline(std::cin, header) && header != "\r" && !header.empty()) {}
        std::string payload(length, '\0'); std::cin.read(payload.data(), static_cast<std::streamsize>(length));
        Json request;
        try { request = JsonParser(payload).parse(); } catch (...) { continue; }
        std::string method = request.get("method") ? request.get("method")->string_or() : "";
        const Json* id = request.get("id");
        auto id_text = [&]() {
            if (!id) return std::string("null");
            if (auto text = std::get_if<std::string>(&id->value)) return std::string("\"") + escape_json(*text) + "\"";
            return std::to_string(id->int_or());
        };
        if (method == "initialize") {
            send_message("{\"jsonrpc\":\"2.0\",\"id\":" + id_text() + ",\"result\":{\"capabilities\":{\"textDocumentSync\":2,\"completionProvider\":{\"triggerCharacters\":[\"?\"]}}}}");
        } else if (method == "shutdown") {
            send_message("{\"jsonrpc\":\"2.0\",\"id\":" + id_text() + ",\"result\":null}");
        } else if (method == "exit") break;
        else if (method == "textDocument/didOpen") {
            auto uri = path(request, {"params", "textDocument", "uri"});
            auto text = path(request, {"params", "textDocument", "text"});
            auto version = path(request, {"params", "textDocument", "version"});
            if (uri && text) { auto& doc = documents[uri->string_or()]; doc = {text->string_or(), version ? version->int_or() : 0}; publish_diagnostics(uri->string_or(), doc); }
        } else if (method == "textDocument/didChange") {
            auto uri = path(request, {"params", "textDocument", "uri"});
            auto version = path(request, {"params", "textDocument", "version"});
            auto changes = path(request, {"params", "contentChanges"});
            if (!uri || !changes) continue;
            auto found = documents.find(uri->string_or()); if (found == documents.end()) continue;
            if (version && version->int_or() <= found->second.version) continue;
            if (auto array = std::get_if<Json::Array>(&changes->value)) for (const auto& change : *array) {
                auto text = change.get("text"); if (!text) continue;
                auto range = change.get("range");
                if (!range) found->second.text = text->string_or();
                else {
                    auto sl = path(*range, {"start", "line"}); auto sc = path(*range, {"start", "character"});
                    auto el = path(*range, {"end", "line"}); auto ec = path(*range, {"end", "character"});
                    size_t begin = offset_at(found->second.text, sl ? sl->int_or() : 0, sc ? sc->int_or() : 0);
                    size_t end = offset_at(found->second.text, el ? el->int_or() : 0, ec ? ec->int_or() : 0);
                    found->second.text.replace(begin, end - begin, text->string_or());
                }
            }
            found->second.version = version ? version->int_or(found->second.version + 1) : found->second.version + 1;
            publish_diagnostics(uri->string_or(), found->second);
        } else if (method == "textDocument/didClose") {
            auto uri = path(request, {"params", "textDocument", "uri"});
            if (uri) { documents.erase(uri->string_or()); send_message("{\"jsonrpc\":\"2.0\",\"method\":\"textDocument/publishDiagnostics\",\"params\":{\"uri\":\"" + escape_json(uri->string_or()) + "\",\"diagnostics\":[]}}"); }
        } else if (method == "textDocument/completion") {
            auto uri = path(request, {"params", "textDocument", "uri"});
            auto line = path(request, {"params", "position", "line"});
            auto found = uri ? documents.find(uri->string_or()) : documents.end();
            std::string items = found == documents.end() ? "[]" : completion_items(found->second, line ? line->int_or() : 0);
            send_message("{\"jsonrpc\":\"2.0\",\"id\":" + id_text() + ",\"result\":{\"isIncomplete\":false,\"items\":" + items + "}}");
        }
    }
}
} // namespace LM
