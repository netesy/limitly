#include "linter.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/ast.hh"
#include "frontend/type_checker.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

namespace LM {

namespace {

void enable_ansi_colors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

std::string format_type(const std::shared_ptr<Frontend::AST::TypeAnnotation>& type) {
    if (!type) return "";
    if (!type->typeName.empty()) {
        std::string res = type->typeName;
        if (type->isOptional) res += "?";
        return res;
    }
    if (type->isList && type->elementType) {
        return "[" + format_type(type->elementType) + "]";
    }
    if (type->isDict && type->keyType && type->valueType) {
        return "{" + format_type(type->keyType) + ": " + format_type(type->valueType) + "}";
    }
    if (type->isTuple) {
        std::string s = "(";
        for (size_t i = 0; i < type->tupleTypes.size(); ++i) {
            s += format_type(type->tupleTypes[i]);
            if (i + 1 < type->tupleTypes.size()) s += ", ";
        }
        return s + ")";
    }
    if (type->isUnion) {
        std::string s;
        for (size_t i = 0; i < type->unionTypes.size(); ++i) {
            s += format_type(type->unionTypes[i]);
            if (i + 1 < type->unionTypes.size()) s += " | ";
        }
        return s;
    }
    return "";
}

bool is_reserved_keyword(const std::string& s) {
    static const std::unordered_set<std::string> keywords = {
        "iter", "any", "fn", "if", "while", "for", "return", "var", "val", "const",
        "frame", "trait", "import", "match", "in", "type", "enum", "err", "ok",
        "and", "or", "not", "as", "where", "self", "super", "true", "false",
        "nil", "break", "continue", "parallel", "concurrent", "task", "worker",
        "contract", "staged", "unsafe", "module", "mixin", "show", "hide", "from",
        "elif", "else", "static", "pub", "prot", "this"
    };
    return keywords.find(s) != keywords.end();
}

std::string to_pascal_case(const std::string& s) {
    std::string res;
    bool cap = true;
    for (char c : s) {
        if (c == '_') {
            cap = true;
        } else if (cap) {
            res += static_cast<char>(std::toupper(c));
            cap = false;
        } else {
            res += c;
        }
    }
    return res;
}

std::string to_snake_case(const std::string& s) {
    std::string res;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (std::isupper(static_cast<unsigned char>(c))) {
            if (i > 0 && s[i - 1] != '_') {
                bool prev_lower = std::islower(static_cast<unsigned char>(s[i - 1])) || std::isdigit(static_cast<unsigned char>(s[i - 1]));
                bool next_lower = (i + 1 < s.size() && std::islower(static_cast<unsigned char>(s[i + 1])));
                if (prev_lower || next_lower) {
                    res += '_';
                }
            }
            res += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        } else {
            res += c;
        }
    }
    return res;
}

bool is_all_caps(const std::string& s) {
    bool has_alpha = false;
    for (char c : s) {
        if (std::isalpha(c)) {
            has_alpha = true;
            if (!std::isupper(c)) return false;
        }
    }
    return has_alpha;
}

bool is_pascal_case(const std::string& s) {
    if (s.empty() || !std::isupper(s[0])) return false;
    if (s.find('_') != std::string::npos) return false;
    return true;
}

bool is_snake_case(const std::string& s) {
    for (char c : s) {
        if (std::isupper(c)) return false;
    }
    return true;
}

void collect_referenced_type(const std::shared_ptr<Frontend::AST::TypeAnnotation>& type, std::unordered_set<std::string>& used) {
    if (!type) return;
    if (!type->typeName.empty()) {
        auto dot = type->typeName.find('.');
        if (dot != std::string::npos) {
            used.insert(type->typeName.substr(0, dot));
            used.insert(type->typeName.substr(dot + 1));
        } else {
            used.insert(type->typeName);
        }
    }
    if (type->elementType) collect_referenced_type(type->elementType, used);
    if (type->keyType) collect_referenced_type(type->keyType, used);
    if (type->valueType) collect_referenced_type(type->valueType, used);
    if (type->returnType) collect_referenced_type(type->returnType, used);
    for (const auto& t : type->unionTypes) collect_referenced_type(t, used);
    for (const auto& t : type->tupleTypes) collect_referenced_type(t, used);
    for (const auto& t : type->functionParams) collect_referenced_type(t, used);
    for (const auto& p : type->functionParameters) collect_referenced_type(p.type, used);
    for (const auto& f : type->structuralFields) collect_referenced_type(f.type, used);
    for (const auto& a : type->associatedTypes) collect_referenced_type(a, used);
    for (const auto& a : type->stagedCallArgs) collect_referenced_type(a, used);
    for (const auto& err : type->errorTypes) {
        auto dot = err.find('.');
        if (dot != std::string::npos) {
            used.insert(err.substr(0, dot));
            used.insert(err.substr(dot + 1));
        } else {
            used.insert(err);
        }
    }
}

void collect_referenced_vars(const std::shared_ptr<Frontend::AST::Node>& node, std::unordered_set<std::string>& used);

void collect_referenced_vars(const std::shared_ptr<Frontend::AST::Node>& node, std::unordered_set<std::string>& used) {
    if (!node) return;

    if (auto var_expr = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(node)) {
        used.insert(var_expr->name);
        return;
    }

    if (auto bin_expr = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(node)) {
        collect_referenced_vars(bin_expr->left, used);
        collect_referenced_vars(bin_expr->right, used);
        return;
    }

    if (auto un_expr = std::dynamic_pointer_cast<Frontend::AST::UnaryExpr>(node)) {
        collect_referenced_vars(un_expr->right, used);
        return;
    }

    if (auto call_expr = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(node)) {
        collect_referenced_vars(call_expr->callee, used);
        for (const auto& arg : call_expr->arguments) collect_referenced_vars(arg, used);
        for (const auto& [k, v] : call_expr->namedArgs) collect_referenced_vars(v, used);
        return;
    }

    if (auto member_expr = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(node)) {
        collect_referenced_vars(member_expr->object, used);
        used.insert(member_expr->name);
        return;
    }

    if (auto index_expr = std::dynamic_pointer_cast<Frontend::AST::IndexExpr>(node)) {
        collect_referenced_vars(index_expr->object, used);
        collect_referenced_vars(index_expr->index, used);
        return;
    }

    if (auto assign_expr = std::dynamic_pointer_cast<Frontend::AST::AssignExpr>(node)) {
        collect_referenced_vars(assign_expr->object, used);
        collect_referenced_vars(assign_expr->index, used);
        collect_referenced_vars(assign_expr->value, used);
        return;
    }

    if (auto list_expr = std::dynamic_pointer_cast<Frontend::AST::ListExpr>(node)) {
        for (const auto& el : list_expr->elements) collect_referenced_vars(el, used);
        return;
    }

    if (auto tuple_expr = std::dynamic_pointer_cast<Frontend::AST::TupleExpr>(node)) {
        for (const auto& el : tuple_expr->elements) collect_referenced_vars(el, used);
        return;
    }

    if (auto dict_expr = std::dynamic_pointer_cast<Frontend::AST::DictExpr>(node)) {
        for (const auto& el : dict_expr->entries) {
            collect_referenced_vars(el.first, used);
            collect_referenced_vars(el.second, used);
        }
        return;
    }

    if (auto interp = std::dynamic_pointer_cast<Frontend::AST::InterpolatedStringExpr>(node)) {
        for (const auto& part : interp->parts) {
            if (std::holds_alternative<std::shared_ptr<Frontend::AST::Expression>>(part)) {
                collect_referenced_vars(std::get<std::shared_ptr<Frontend::AST::Expression>>(part), used);
            }
        }
        return;
    }

    if (auto cast_expr = std::dynamic_pointer_cast<Frontend::AST::CastExpr>(node)) {
        collect_referenced_vars(cast_expr->expression, used);
        collect_referenced_type(cast_expr->targetType, used);
        return;
    }

    if (auto grouping = std::dynamic_pointer_cast<Frontend::AST::GroupingExpr>(node)) {
        collect_referenced_vars(grouping->expression, used);
        return;
    }

    if (auto range = std::dynamic_pointer_cast<Frontend::AST::RangeExpr>(node)) {
        collect_referenced_vars(range->start, used);
        collect_referenced_vars(range->end, used);
        collect_referenced_vars(range->step, used);
        return;
    }

    if (auto lambda = std::dynamic_pointer_cast<Frontend::AST::LambdaExpr>(node)) {
        for (const auto& p : lambda->params) collect_referenced_type(p.second, used);
        if (lambda->returnType.has_value() && lambda->returnType.value()) {
            collect_referenced_type(lambda->returnType.value(), used);
        }
        collect_referenced_vars(lambda->body, used);
        return;
    }

    if (auto obj_lit = std::dynamic_pointer_cast<Frontend::AST::ObjectLiteralExpr>(node)) {
        auto dot = obj_lit->constructorName.find('.');
        if (dot != std::string::npos) {
            used.insert(obj_lit->constructorName.substr(0, dot));
            used.insert(obj_lit->constructorName.substr(dot + 1));
        } else if (!obj_lit->constructorName.empty()) {
            used.insert(obj_lit->constructorName);
        }
        for (const auto& [k, v] : obj_lit->properties) {
            collect_referenced_vars(v, used);
        }
        return;
    }

    if (auto fi = std::dynamic_pointer_cast<Frontend::AST::FrameInstantiationExpr>(node)) {
        auto dot = fi->frameName.find('.');
        if (dot != std::string::npos) {
            used.insert(fi->frameName.substr(0, dot));
            used.insert(fi->frameName.substr(dot + 1));
        } else if (!fi->frameName.empty()) {
            used.insert(fi->frameName);
        }
        for (const auto& a : fi->positionalArgs) collect_referenced_vars(a, used);
        for (const auto& [k, v] : fi->namedArgs) collect_referenced_vars(v, used);
        return;
    }

    if (auto tp = std::dynamic_pointer_cast<Frontend::AST::TypePatternExpr>(node)) {
        collect_referenced_type(tp->type, used);
        return;
    }

    if (auto bp = std::dynamic_pointer_cast<Frontend::AST::BindingPatternExpr>(node)) {
        auto dot = bp->typeName.find('.');
        if (dot != std::string::npos) {
            used.insert(bp->typeName.substr(0, dot));
            used.insert(bp->typeName.substr(dot + 1));
        } else if (!bp->typeName.empty()) {
            used.insert(bp->typeName);
        }
        for (const auto& p : bp->patterns) collect_referenced_vars(p, used);
        return;
    }

    if (auto op = std::dynamic_pointer_cast<Frontend::AST::OrPatternExpr>(node)) {
        for (const auto& p : op->patterns) collect_referenced_vars(p, used);
        return;
    }

    if (auto fallible = std::dynamic_pointer_cast<Frontend::AST::FallibleExpr>(node)) {
        collect_referenced_vars(fallible->expression, used);
        collect_referenced_vars(fallible->elseHandler, used);
        return;
    }

    if (auto ok_expr = std::dynamic_pointer_cast<Frontend::AST::OkConstructExpr>(node)) {
        collect_referenced_vars(ok_expr->value, used);
        return;
    }

    if (auto err_expr = std::dynamic_pointer_cast<Frontend::AST::ErrorConstructExpr>(node)) {
        if (!err_expr->errorType.empty()) {
            auto dot = err_expr->errorType.find('.');
            if (dot != std::string::npos) {
                used.insert(err_expr->errorType.substr(0, dot));
                used.insert(err_expr->errorType.substr(dot + 1));
            } else {
                used.insert(err_expr->errorType);
            }
        }
        for (const auto& arg : err_expr->arguments) collect_referenced_vars(arg, used);
        return;
    }

    if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(node)) {
        for (const auto& s : block->statements) collect_referenced_vars(s, used);
        return;
    }

    if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(node)) {
        collect_referenced_vars(if_stmt->condition, used);
        collect_referenced_vars(if_stmt->thenBranch, used);
        collect_referenced_vars(if_stmt->elseBranch, used);
        return;
    }

    if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(node)) {
        collect_referenced_vars(while_stmt->condition, used);
        collect_referenced_vars(while_stmt->body, used);
        return;
    }

    if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(node)) {
        collect_referenced_vars(for_stmt->initializer, used);
        collect_referenced_vars(for_stmt->condition, used);
        collect_referenced_vars(for_stmt->increment, used);
        collect_referenced_vars(for_stmt->body, used);
        return;
    }

    if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(node)) {
        collect_referenced_vars(iter_stmt->iterable, used);
        collect_referenced_vars(iter_stmt->body, used);
        return;
    }

    if (auto ret_stmt = std::dynamic_pointer_cast<Frontend::AST::ReturnStatement>(node)) {
        collect_referenced_vars(ret_stmt->value, used);
        return;
    }

    if (auto expr_stmt = std::dynamic_pointer_cast<Frontend::AST::ExprStatement>(node)) {
        collect_referenced_vars(expr_stmt->expression, used);
        return;
    }

    if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(node)) {
        if (var_decl->type.has_value() && var_decl->type.value()) {
            collect_referenced_type(var_decl->type.value(), used);
        }
        collect_referenced_vars(var_decl->initializer, used);
        return;
    }

    if (auto destr = std::dynamic_pointer_cast<Frontend::AST::DestructuringDeclaration>(node)) {
        collect_referenced_vars(destr->initializer, used);
        return;
    }

    if (auto func_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(node)) {
        if (func_decl->returnType.has_value() && func_decl->returnType.value()) {
            collect_referenced_type(func_decl->returnType.value(), used);
        }
        for (const auto& p : func_decl->params) {
            collect_referenced_type(p.second, used);
        }
        for (const auto& p : func_decl->optionalParams) {
            collect_referenced_type(p.second.first, used);
            collect_referenced_vars(p.second.second, used);
        }
        collect_referenced_vars(func_decl->body, used);
        return;
    }

    if (auto frame_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(node)) {
        for (const auto& impl : frame_decl->implements) {
            auto dot = impl.find('.');
            if (dot != std::string::npos) {
                used.insert(impl.substr(0, dot));
                used.insert(impl.substr(dot + 1));
            } else {
                used.insert(impl);
            }
        }
        for (const auto& field : frame_decl->fields) {
            if (field) {
                collect_referenced_type(field->type, used);
                collect_referenced_vars(field->defaultValue, used);
            }
        }
        for (const auto& method : frame_decl->methods) {
            if (method) {
                collect_referenced_type(method->returnType, used);
                for (const auto& p : method->parameters) collect_referenced_type(p.second, used);
                for (const auto& p : method->optionalParams) {
                    collect_referenced_type(p.second.first, used);
                    collect_referenced_vars(p.second.second, used);
                }
                collect_referenced_vars(method->body, used);
            }
        }
        if (frame_decl->init) {
            for (const auto& p : frame_decl->init->parameters) collect_referenced_type(p.second, used);
            for (const auto& p : frame_decl->init->optionalParams) {
                collect_referenced_type(p.second.first, used);
                collect_referenced_vars(p.second.second, used);
            }
            collect_referenced_vars(frame_decl->init->body, used);
        }
        if (frame_decl->deinit) {
            collect_referenced_vars(frame_decl->deinit->body, used);
        }
        for (const auto& emb : frame_decl->embeds) {
            if (emb) {
                auto dot = emb->typeName.find('.');
                if (dot != std::string::npos) {
                    used.insert(emb->typeName.substr(0, dot));
                    used.insert(emb->typeName.substr(dot + 1));
                } else {
                    used.insert(emb->typeName);
                }
            }
        }
        return;
    }

    if (auto trait_decl = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(node)) {
        for (const auto& ext : trait_decl->extends) {
            auto dot = ext.find('.');
            if (dot != std::string::npos) {
                used.insert(ext.substr(0, dot));
                used.insert(ext.substr(dot + 1));
            } else {
                used.insert(ext);
            }
        }
        for (const auto& m : trait_decl->methods) {
            collect_referenced_vars(m, used);
        }
        return;
    }

    if (auto mixin_decl = std::dynamic_pointer_cast<Frontend::AST::MixinDeclaration>(node)) {
        for (const auto& f : mixin_decl->fields) {
            if (f) {
                collect_referenced_type(f->type, used);
                collect_referenced_vars(f->defaultValue, used);
            }
        }
        for (const auto& m : mixin_decl->methods) {
            if (m) {
                collect_referenced_type(m->returnType, used);
                for (const auto& p : m->parameters) collect_referenced_type(p.second, used);
                for (const auto& p : m->optionalParams) {
                    collect_referenced_type(p.second.first, used);
                    collect_referenced_vars(p.second.second, used);
                }
                collect_referenced_vars(m->body, used);
            }
        }
        return;
    }

    if (auto type_decl = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(node)) {
        collect_referenced_type(type_decl->type, used);
        return;
    }

    if (auto enum_decl = std::dynamic_pointer_cast<Frontend::AST::EnumDeclaration>(node)) {
        for (const auto& v : enum_decl->variants) {
            for (const auto& t : v.second) collect_referenced_type(t, used);
        }
        return;
    }

    if (auto mod_decl = std::dynamic_pointer_cast<Frontend::AST::ModuleDeclaration>(node)) {
        for (const auto& s : mod_decl->publicMembers) collect_referenced_vars(s, used);
        for (const auto& s : mod_decl->protectedMembers) collect_referenced_vars(s, used);
        for (const auto& s : mod_decl->privateMembers) collect_referenced_vars(s, used);
        return;
    }

    if (auto par = std::dynamic_pointer_cast<Frontend::AST::ParallelStatement>(node)) {
        collect_referenced_vars(par->body, used);
        return;
    }

    if (auto conc = std::dynamic_pointer_cast<Frontend::AST::ConcurrentStatement>(node)) {
        collect_referenced_vars(conc->body, used);
        return;
    }

    if (auto task = std::dynamic_pointer_cast<Frontend::AST::TaskStatement>(node)) {
        collect_referenced_vars(task->iterable, used);
        collect_referenced_vars(task->body, used);
        return;
    }

    if (auto worker = std::dynamic_pointer_cast<Frontend::AST::WorkerStatement>(node)) {
        collect_referenced_vars(worker->iterable, used);
        collect_referenced_vars(worker->body, used);
        return;
    }

    if (auto unsafe = std::dynamic_pointer_cast<Frontend::AST::UnsafeStatement>(node)) {
        collect_referenced_vars(unsafe->body, used);
        return;
    }

    if (auto staged = std::dynamic_pointer_cast<Frontend::AST::StagedBlockStatement>(node)) {
        collect_referenced_vars(staged->body, used);
        return;
    }

    if (auto staged_expr = std::dynamic_pointer_cast<Frontend::AST::StagedExpr>(node)) {
        collect_referenced_vars(staged_expr->expression, used);
        collect_referenced_vars(staged_expr->block, used);
        return;
    }

    if (auto contract_stmt = std::dynamic_pointer_cast<Frontend::AST::ContractStatement>(node)) {
        collect_referenced_vars(contract_stmt->condition, used);
        collect_referenced_vars(contract_stmt->message, used);
        return;
    }

    if (auto match_stmt = std::dynamic_pointer_cast<Frontend::AST::MatchStatement>(node)) {
        collect_referenced_vars(match_stmt->value, used);
        for (const auto& c : match_stmt->cases) {
            collect_referenced_vars(c.pattern, used);
            collect_referenced_vars(c.guard, used);
            collect_referenced_vars(c.body, used);
        }
        return;
    }
}

void collect_return_statements(const std::shared_ptr<Frontend::AST::Statement>& stmt,
                               std::vector<std::shared_ptr<Frontend::AST::ReturnStatement>>& returns) {
    if (!stmt) return;
    if (auto ret = std::dynamic_pointer_cast<Frontend::AST::ReturnStatement>(stmt)) {
        returns.push_back(ret);
        return;
    }
    if (std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
        return;
    }
    if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
        for (const auto& s : block->statements) {
            collect_return_statements(s, returns);
        }
        return;
    }
    if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
        collect_return_statements(if_stmt->thenBranch, returns);
        collect_return_statements(if_stmt->elseBranch, returns);
        return;
    }
    if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
        collect_return_statements(while_stmt->body, returns);
        return;
    }
    if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
        collect_return_statements(for_stmt->body, returns);
        return;
    }
    if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
        collect_return_statements(iter_stmt->body, returns);
        return;
    }
    if (auto unsafe_stmt = std::dynamic_pointer_cast<Frontend::AST::UnsafeStatement>(stmt)) {
        collect_return_statements(unsafe_stmt->body, returns);
        return;
    }
}

std::string infer_expression_type(const std::shared_ptr<Frontend::AST::Expression>& expr,
                                  const std::unordered_map<std::string, std::string>& var_types) {
    if (!expr) return "";

    if (auto lit = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(expr)) {
        if (std::holds_alternative<bool>(lit->value)) return "bool";
        if (std::holds_alternative<std::nullptr_t>(lit->value)) return "nil";
        if (lit->literalType == Frontend::TokenType::INT_LITERAL || lit->literalType == Frontend::TokenType::HEX_LITERAL) return "int";
        if (lit->literalType == Frontend::TokenType::FLOAT_LITERAL || lit->literalType == Frontend::TokenType::SCIENTIFIC_LITERAL) return "float";
        if (lit->literalType == Frontend::TokenType::STRING) return "str";
        if (lit->literalType == Frontend::TokenType::NIL) return "nil";
        if (std::holds_alternative<std::string>(lit->value)) return "str";
    }

    if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr)) {
        auto it = var_types.find(var->name);
        if (it != var_types.end()) return it->second;
    }

    if (auto interp = std::dynamic_pointer_cast<Frontend::AST::InterpolatedStringExpr>(expr)) {
        return "str";
    }

    if (auto cast_expr = std::dynamic_pointer_cast<Frontend::AST::CastExpr>(expr)) {
        if (cast_expr->targetType) {
            return format_type(cast_expr->targetType);
        }
    }

    if (auto list_expr = std::dynamic_pointer_cast<Frontend::AST::ListExpr>(expr)) {
        if (!list_expr->elements.empty()) {
            std::string elem_type = infer_expression_type(list_expr->elements[0], var_types);
            if (!elem_type.empty()) {
                return "[" + elem_type + "]";
            }
        }
        return "[any]";
    }

    if (auto dict_expr = std::dynamic_pointer_cast<Frontend::AST::DictExpr>(expr)) {
        if (!dict_expr->entries.empty()) {
            std::string k_type = infer_expression_type(dict_expr->entries[0].first, var_types);
            std::string v_type = infer_expression_type(dict_expr->entries[0].second, var_types);
            if (!k_type.empty() && !v_type.empty()) {
                return "{" + k_type + ": " + v_type + "}";
            }
        }
    }

    if (auto idx = std::dynamic_pointer_cast<Frontend::AST::IndexExpr>(expr)) {
        std::string coll = infer_expression_type(idx->object, var_types);
        if (coll.size() > 2 && coll.front() == '[' && coll.back() == ']') {
            return coll.substr(1, coll.size() - 2);
        }
    }

    if (auto bin = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
        switch (bin->op) {
            case Frontend::TokenType::EQUAL_EQUAL:
            case Frontend::TokenType::BANG_EQUAL:
            case Frontend::TokenType::LESS:
            case Frontend::TokenType::GREATER:
            case Frontend::TokenType::LESS_EQUAL:
            case Frontend::TokenType::GREATER_EQUAL:
            case Frontend::TokenType::AND:
            case Frontend::TokenType::OR:
                return "bool";
            case Frontend::TokenType::MODULUS:
            case Frontend::TokenType::AMPERSAND:
            case Frontend::TokenType::PIPE:
            case Frontend::TokenType::CARET:
            case Frontend::TokenType::LESS_LESS:
            case Frontend::TokenType::GREATER_GREATER:
                return "int";
            case Frontend::TokenType::PLUS: {
                std::string l = infer_expression_type(bin->left, var_types);
                std::string r = infer_expression_type(bin->right, var_types);
                if (l == "str" || r == "str") return "str";
                if (l == "float" || r == "float") return "float";
                if (l == "int" && r == "int") return "int";
                return l.empty() ? r : l;
            }
            case Frontend::TokenType::MINUS:
            case Frontend::TokenType::STAR:
            case Frontend::TokenType::SLASH:
            case Frontend::TokenType::POWER: {
                std::string l = infer_expression_type(bin->left, var_types);
                std::string r = infer_expression_type(bin->right, var_types);
                if (l == "float" || r == "float") return "float";
                if (l == "int" && r == "int") return "int";
                return l.empty() ? r : l;
            }
            default:
                break;
        }
    }

    if (auto un = std::dynamic_pointer_cast<Frontend::AST::UnaryExpr>(expr)) {
        if (un->op == Frontend::TokenType::BANG || un->op == Frontend::TokenType::NOT) return "bool";
        if (un->op == Frontend::TokenType::MINUS || un->op == Frontend::TokenType::TILDE) {
            return infer_expression_type(un->right, var_types);
        }
    }

    if (auto call = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(expr)) {
        if (auto callee_var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(call->callee)) {
            if (callee_var->name == "len" || callee_var->name == "str_len") return "int";
            if (callee_var->name == "parse_int" || callee_var->name == "to_int") return "int";
            if (callee_var->name == "to_string" || callee_var->name == "to_str") return "str";
            if (callee_var->name == "parse_bool") return "bool";
            if (callee_var->name == "parse_float") return "float";
        }
        if (auto member = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(call->callee)) {
            if (member->name == "length" || member->name == "len" || member->name == "count") return "int";
            if (member->name == "to_string") return "str";
            if (member->name == "is_valid" || member->name == "is_empty" ||
                member->name == "starts_with" || member->name == "ends_with" ||
                member->name == "contains" || member->name == "equals") return "bool";
        }
    }

    return "";
}

void find_param_uses(const std::string& param,
                     const std::shared_ptr<Frontend::AST::Expression>& expr,
                     std::string& inferred) {
    if (!expr || !inferred.empty()) return;

    if (auto cast_expr = std::dynamic_pointer_cast<Frontend::AST::CastExpr>(expr)) {
        if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(cast_expr->expression)) {
            if (var->name == param && cast_expr->targetType) {
                inferred = format_type(cast_expr->targetType);
                return;
            }
        }
    }

    if (auto bin = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
        if (bin->op == Frontend::TokenType::MODULUS ||
            bin->op == Frontend::TokenType::AMPERSAND ||
            bin->op == Frontend::TokenType::PIPE ||
            bin->op == Frontend::TokenType::CARET ||
            bin->op == Frontend::TokenType::LESS_LESS ||
            bin->op == Frontend::TokenType::GREATER_GREATER) {
            if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->left)) {
                if (var->name == param) { inferred = "int"; return; }
            }
            if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->right)) {
                if (var->name == param) { inferred = "int"; return; }
            }
        }
        if (bin->op == Frontend::TokenType::STAR || bin->op == Frontend::TokenType::SLASH ||
            bin->op == Frontend::TokenType::MINUS) {
            auto is_int_lit = [](const std::shared_ptr<Frontend::AST::Expression>& e) {
                if (auto lit = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(e)) {
                    return lit->literalType == Frontend::TokenType::INT_LITERAL || lit->literalType == Frontend::TokenType::HEX_LITERAL;
                }
                return false;
            };
            if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->left)) {
                if (var->name == param && is_int_lit(bin->right)) { inferred = "int"; return; }
            }
            if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->right)) {
                if (var->name == param && is_int_lit(bin->left)) { inferred = "int"; return; }
            }
        }
        find_param_uses(param, bin->left, inferred);
        find_param_uses(param, bin->right, inferred);
        return;
    }

    if (auto call = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(expr)) {
        find_param_uses(param, call->callee, inferred);
        for (const auto& arg : call->arguments) {
            find_param_uses(param, arg, inferred);
        }
        return;
    }

    if (auto un = std::dynamic_pointer_cast<Frontend::AST::UnaryExpr>(expr)) {
        if (un->op == Frontend::TokenType::TILDE) {
            if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(un->right)) {
                if (var->name == param) { inferred = "int"; return; }
            }
        }
        find_param_uses(param, un->right, inferred);
        return;
    }

    if (auto member = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(expr)) {
        if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(member->object)) {
            if (var->name == param) {
                if (member->name == "length" || member->name == "starts_with" ||
                    member->name == "ends_with" || member->name == "contains") {
                    inferred = "str";
                    return;
                }
            }
        }
        find_param_uses(param, member->object, inferred);
        return;
    }
}

void find_param_uses_in_stmt(const std::string& param,
                             const std::shared_ptr<Frontend::AST::Statement>& stmt,
                             std::string& inferred) {
    if (!stmt || !inferred.empty()) return;
    if (auto expr_stmt = std::dynamic_pointer_cast<Frontend::AST::ExprStatement>(stmt)) {
        find_param_uses(param, expr_stmt->expression, inferred);
        return;
    }
    if (auto ret_stmt = std::dynamic_pointer_cast<Frontend::AST::ReturnStatement>(stmt)) {
        find_param_uses(param, ret_stmt->value, inferred);
        return;
    }
    if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
        find_param_uses(param, var_decl->initializer, inferred);
        return;
    }
    if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
        for (const auto& s : block->statements) {
            find_param_uses_in_stmt(param, s, inferred);
            if (!inferred.empty()) return;
        }
        return;
    }
    if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
        find_param_uses(param, if_stmt->condition, inferred);
        find_param_uses_in_stmt(param, if_stmt->thenBranch, inferred);
        find_param_uses_in_stmt(param, if_stmt->elseBranch, inferred);
        return;
    }
    if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
        find_param_uses(param, while_stmt->condition, inferred);
        find_param_uses_in_stmt(param, while_stmt->body, inferred);
        return;
    }
    if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
        find_param_uses_in_stmt(param, for_stmt->initializer, inferred);
        find_param_uses(param, for_stmt->condition, inferred);
        find_param_uses(param, for_stmt->increment, inferred);
        find_param_uses_in_stmt(param, for_stmt->body, inferred);
        return;
    }
    if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
        find_param_uses(param, iter_stmt->iterable, inferred);
        find_param_uses_in_stmt(param, iter_stmt->body, inferred);
        return;
    }
    if (auto unsafe_stmt = std::dynamic_pointer_cast<Frontend::AST::UnsafeStatement>(stmt)) {
        find_param_uses_in_stmt(param, unsafe_stmt->body, inferred);
        return;
    }
}

struct AstDeclarations {
    std::unordered_map<int, std::vector<std::shared_ptr<Frontend::AST::VarDeclaration>>> vars_by_line;
    std::unordered_map<int, std::vector<std::shared_ptr<Frontend::AST::FunctionDeclaration>>> funcs_by_line;
    std::unordered_map<int, std::vector<std::shared_ptr<Frontend::AST::FrameMethod>>> methods_by_line;
};

void collect_declarations(const std::shared_ptr<Frontend::AST::Statement>& stmt, AstDeclarations& decls) {
    if (!stmt) return;
    if (auto vd = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
        decls.vars_by_line[vd->line].push_back(vd);
        return;
    }
    if (auto fd = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
        decls.funcs_by_line[fd->line].push_back(fd);
        if (fd->body) {
            for (const auto& s : fd->body->statements) {
                collect_declarations(s, decls);
            }
        }
        return;
    }
    if (auto frame = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
        if (frame->init) {
            decls.methods_by_line[frame->init->line].push_back(frame->init);
            if (frame->init->body) {
                for (const auto& s : frame->init->body->statements) {
                    collect_declarations(s, decls);
                }
            }
        }
        if (frame->deinit) {
            decls.methods_by_line[frame->deinit->line].push_back(frame->deinit);
            if (frame->deinit->body) {
                for (const auto& s : frame->deinit->body->statements) {
                    collect_declarations(s, decls);
                }
            }
        }
        for (const auto& m : frame->methods) {
            if (m) {
                decls.methods_by_line[m->line].push_back(m);
                if (m->body) {
                    for (const auto& s : m->body->statements) {
                        collect_declarations(s, decls);
                    }
                }
            }
        }
        return;
    }
    if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
        for (const auto& s : block->statements) {
            collect_declarations(s, decls);
        }
        return;
    }
    if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
        collect_declarations(if_stmt->thenBranch, decls);
        collect_declarations(if_stmt->elseBranch, decls);
        return;
    }
    if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
        collect_declarations(while_stmt->body, decls);
        return;
    }
    if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
        collect_declarations(for_stmt->initializer, decls);
        collect_declarations(for_stmt->body, decls);
        return;
    }
    if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
        collect_declarations(iter_stmt->body, decls);
        return;
    }
    if (auto unsafe_stmt = std::dynamic_pointer_cast<Frontend::AST::UnsafeStatement>(stmt)) {
        collect_declarations(unsafe_stmt->body, decls);
        return;
    }
}

bool replace_var_annotation(std::string& line, const std::string& var_name, const std::string& old_type, const std::string& new_type) {
    bool in_str = false;
    char quote = 0;
    int interp_depth = 0;
    size_t i = 0;
    while (i < line.length()) {
        if (in_str) {
            if (line[i] == '\\' && i + 1 < line.length()) { i += 2; continue; }
            if (line[i] == quote && interp_depth == 0) { in_str = false; i++; continue; }
            if (line[i] == '{') { interp_depth++; i++; continue; }
            if (line[i] == '}' && interp_depth > 0) { interp_depth--; i++; continue; }
            i++;
            continue;
        } else {
            if (line[i] == '"' || line[i] == '\'') { in_str = true; quote = line[i]; interp_depth = 0; i++; continue; }
            if (line[i] == '/' && i + 1 < line.length() && line[i + 1] == '/') break;
        }

        if (line.compare(i, var_name.length(), var_name) == 0) {
            bool left_boundary = (i == 0 || (!isalnum(static_cast<unsigned char>(line[i - 1])) && line[i - 1] != '_'));
            bool right_boundary = (i + var_name.length() >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + var_name.length()])) && line[i + var_name.length()] != '_'));
            if (left_boundary && right_boundary) {
                size_t p = i + var_name.length();
                while (p < line.length() && (line[p] == ' ' || line[p] == '\t')) p++;
                if (p < line.length() && line[p] == ':') {
                    p++;
                    while (p < line.length() && (line[p] == ' ' || line[p] == '\t')) p++;
                    if (p < line.length() && line.compare(p, old_type.length(), old_type) == 0) {
                        bool r_bound = (p + old_type.length() >= line.length() || (!isalnum(static_cast<unsigned char>(line[p + old_type.length()])) && line[p + old_type.length()] != '_'));
                        if (r_bound) {
                            line.replace(p, old_type.length(), new_type);
                            return true;
                        }
                    }
                }
            }
        }
        i++;
    }
    return false;
}

bool replace_return_type_annotation(std::string& line, const std::string& func_name, const std::string& old_type, const std::string& new_type) {
    bool in_str = false;
    char quote = 0;
    int interp_depth = 0;
    size_t i = 0;
    while (i < line.length()) {
        if (in_str) {
            if (line[i] == '\\' && i + 1 < line.length()) { i += 2; continue; }
            if (line[i] == quote && interp_depth == 0) { in_str = false; i++; continue; }
            if (line[i] == '{') { interp_depth++; i++; continue; }
            if (line[i] == '}' && interp_depth > 0) { interp_depth--; i++; continue; }
            i++;
            continue;
        } else {
            if (line[i] == '"' || line[i] == '\'') { in_str = true; quote = line[i]; interp_depth = 0; i++; continue; }
            if (line[i] == '/' && i + 1 < line.length() && line[i + 1] == '/') break;
        }

        if (line.compare(i, func_name.length(), func_name) == 0) {
            bool left_boundary = (i == 0 || (!isalnum(static_cast<unsigned char>(line[i - 1])) && line[i - 1] != '_'));
            bool right_boundary = (i + func_name.length() >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + func_name.length()])) && line[i + func_name.length()] != '_'));
            if (left_boundary && right_boundary) {
                size_t p = line.find('(', i + func_name.length());
                if (p != std::string::npos) {
                    int depth = 0;
                    size_t close_paren = std::string::npos;
                    for (size_t k = p; k < line.length(); ++k) {
                        if (line[k] == '(') depth++;
                        else if (line[k] == ')') {
                            depth--;
                            if (depth == 0) { close_paren = k; break; }
                        }
                    }
                    if (close_paren != std::string::npos) {
                        size_t colon = close_paren + 1;
                        while (colon < line.length() && (line[colon] == ' ' || line[colon] == '\t')) colon++;
                        if (colon < line.length() && line[colon] == ':') {
                            size_t t_pos = colon + 1;
                            while (t_pos < line.length() && (line[t_pos] == ' ' || line[t_pos] == '\t')) t_pos++;
                            if (t_pos < line.length() && line.compare(t_pos, old_type.length(), old_type) == 0) {
                                bool r_bound = (t_pos + old_type.length() >= line.length() || (!isalnum(static_cast<unsigned char>(line[t_pos + old_type.length()])) && line[t_pos + old_type.length()] != '_'));
                                if (r_bound) {
                                    line.replace(t_pos, old_type.length(), new_type);
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        i++;
    }
    return false;
}

bool insert_return_type_annotation(std::string& line, const std::string& func_name, const std::string& new_type) {
    bool in_str = false;
    char quote = 0;
    int interp_depth = 0;
    size_t i = 0;
    while (i < line.length()) {
        if (in_str) {
            if (line[i] == '\\' && i + 1 < line.length()) { i += 2; continue; }
            if (line[i] == quote && interp_depth == 0) { in_str = false; i++; continue; }
            if (line[i] == '{') { interp_depth++; i++; continue; }
            if (line[i] == '}' && interp_depth > 0) { interp_depth--; i++; continue; }
            i++;
            continue;
        } else {
            if (line[i] == '"' || line[i] == '\'') { in_str = true; quote = line[i]; interp_depth = 0; i++; continue; }
            if (line[i] == '/' && i + 1 < line.length() && line[i + 1] == '/') break;
        }

        if (line.compare(i, func_name.length(), func_name) == 0) {
            bool left_boundary = (i == 0 || (!isalnum(static_cast<unsigned char>(line[i - 1])) && line[i - 1] != '_'));
            bool right_boundary = (i + func_name.length() >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + func_name.length()])) && line[i + func_name.length()] != '_'));
            if (left_boundary && right_boundary) {
                size_t p = line.find('(', i + func_name.length());
                if (p != std::string::npos) {
                    int depth = 0;
                    size_t close_paren = std::string::npos;
                    for (size_t k = p; k < line.length(); ++k) {
                        if (line[k] == '(') depth++;
                        else if (line[k] == ')') {
                            depth--;
                            if (depth == 0) { close_paren = k; break; }
                        }
                    }
                    if (close_paren != std::string::npos) {
                        size_t after_paren = close_paren + 1;
                        while (after_paren < line.length() && (line[after_paren] == ' ' || line[after_paren] == '\t')) after_paren++;
                        if (after_paren < line.length() && line[after_paren] != ':') {
                            line.insert(close_paren + 1, ": " + new_type);
                            return true;
                        }
                    }
                }
            }
        }
        i++;
    }
    return false;
}

struct VarMeta {
    int line = 0;
    bool is_list = false;
    bool is_fallible = false;
};

class LintVisitor {
public:
    std::string filename;
    std::vector<LintDiagnostic> diagnostics;

    // Scope stack for variables and shadowing detection
    std::vector<std::unordered_map<std::string, VarMeta>> scope_stack;

    // Known fallible functions
    std::unordered_set<std::string> fallible_functions;

    bool in_trait = false;
    bool is_runtime_bridge = false;

    void push_scope() {
        scope_stack.emplace_back();
    }

    void pop_scope() {
        if (!scope_stack.empty()) {
            scope_stack.pop_back();
        }
    }

    int find_in_outer_scopes(const std::string& name) const {
        if (scope_stack.size() <= 1) return 0;
        for (int i = static_cast<int>(scope_stack.size()) - 2; i >= 0; --i) {
            auto it = scope_stack[i].find(name);
            if (it != scope_stack[i].end()) {
                return it->second.line;
            }
        }
        return 0;
    }

    bool is_known_list_var(const std::string& name) const {
        for (int i = static_cast<int>(scope_stack.size()) - 1; i >= 0; --i) {
            auto it = scope_stack[i].find(name);
            if (it != scope_stack[i].end()) {
                return it->second.is_list;
            }
        }
        return false;
    }

    void add_diag(int line, int col, const std::string& rule, const std::string& message, const std::string& help = "", const std::string& severity = "warning") {
        diagnostics.push_back({filename, line, col, severity, rule, message, help});
    }

    void visit_program(const std::shared_ptr<Frontend::AST::Program>& program) {
        if (!program) return;

        is_runtime_bridge = (filename.find("internal") != std::string::npos ||
                             filename.find("resource") != std::string::npos ||
                             filename.find("gg") != std::string::npos);

        push_scope();

        // 1. First pass: record imports and declarations
        struct ImportInfo {
            std::string symbol_name;
            int line = 0;
        };
        std::vector<ImportInfo> imports;

        for (const auto& stmt : program->statements) {
            if (auto imp = std::dynamic_pointer_cast<Frontend::AST::ImportStatement>(stmt)) {
                if (imp->visibility == Frontend::AST::VisibilityLevel::Public) {
                    continue; // Re-exported symbols via pub import are exported for consumers
                }
                if (imp->alias.has_value() && !imp->alias.value().empty()) {
                    imports.push_back({imp->alias.value(), imp->line});
                } else if (imp->filter.has_value() && !imp->filter.value().identifiers.empty()) {
                    for (const auto& id : imp->filter.value().identifiers) {
                        imports.push_back({id, imp->line});
                    }
                } else {
                    std::string mod = imp->modulePath;
                    size_t dot = mod.rfind('.');
                    std::string sym = (dot != std::string::npos) ? mod.substr(dot + 1) : mod;
                    imports.push_back({sym, imp->line});
                }
            } else if (auto func = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
                if (func->canFail) {
                    fallible_functions.insert(func->name);
                }
            } else if (auto frame = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                for (const auto& m : frame->methods) {
                    if (m && m->returnType && m->returnType->isFallible) {
                        fallible_functions.insert(frame->name + "." + m->name);
                        fallible_functions.insert(m->name);
                    }
                }
            }
        }

        // Collect all referenced symbols across whole program for unused-import check
        std::unordered_set<std::string> all_referenced;
        bool has_frame_embeds = false;
        for (const auto& stmt : program->statements) {
            collect_referenced_vars(stmt, all_referenced);
            if (auto frame = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
                if (!frame->embeds.empty()) {
                    has_frame_embeds = true;
                }
            }
        }

        for (const auto& imp : imports) {
            if (has_frame_embeds && (imp.symbol_name == "math" || imp.symbol_name == "color" || imp.symbol_name == "transform")) {
                continue; // Promoted methods from embedded frames (e.g. Vec2, Rect, Node) require modules in enclosing scope
            }
            if (all_referenced.find(imp.symbol_name) == all_referenced.end()) {
                add_diag(imp.line, 1, "unused-import",
                         "Imported module/symbol '" + imp.symbol_name + "' is never referenced",
                         "remove this unused import to keep the namespace clean and improve build times");
            }
        }

        // 2. Second pass: visit all statements with full checking
        for (const auto& stmt : program->statements) {
            visit_statement(stmt);
        }

        pop_scope();
    }

    void visit_block(const std::shared_ptr<Frontend::AST::BlockStatement>& block) {
        if (!block) return;

        push_scope();

        bool terminated = false;
        int term_line = 0;

        for (size_t i = 0; i < block->statements.size(); ++i) {
            const auto& stmt = block->statements[i];
            if (terminated) {
                add_diag(stmt->line, 1, "dead-code",
                         "Unreachable code detected after statement on line " + std::to_string(term_line),
                         "this statement will never execute; remove it or adjust control flow logic");
                break;
            }

            visit_statement(stmt);

            if (std::dynamic_pointer_cast<Frontend::AST::ReturnStatement>(stmt) ||
                std::dynamic_pointer_cast<Frontend::AST::BreakStatement>(stmt) ||
                std::dynamic_pointer_cast<Frontend::AST::ContinueStatement>(stmt)) {
                terminated = true;
                term_line = stmt->line;
            }
        }

        pop_scope();
    }

    void visit_statement(const std::shared_ptr<Frontend::AST::Statement>& stmt) {
        if (!stmt) return;

        if (auto func = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            if (is_reserved_keyword(func->name)) {
                add_diag(func->line, 1, "reserved-identifier",
                         "'" + func->name + "' is a reserved language keyword and cannot be used as a function name",
                         "choose an alternative function name that does not conflict with language keywords (AGENTS.md)");
            }

            if (!is_snake_case(func->name) && !is_pascal_case(func->name) && func->name != "init" && func->name != "deinit") {
                add_diag(func->line, 1, "naming-convention",
                         "Function '" + func->name + "' should be snake_case or PascalCase (e.g. '" + to_snake_case(func->name) + "')",
                         "rename function to follow standard Lymar naming conventions");
            }

            push_scope();

            for (const auto& [param, type] : func->params) {
                if (is_reserved_keyword(param)) {
                    add_diag(func->line, 1, "reserved-identifier",
                             "Parameter '" + param + "' is a reserved language keyword",
                             "rename parameter to avoid shadowing language keyword (AGENTS.md)");
                }
                if (!param.empty() && param[0] != '_' && !is_snake_case(param)) {
                    add_diag(func->line, 1, "naming-convention",
                             "Parameter '" + param + "' should be snake_case",
                             "rename parameter to follow snake_case (e.g. '" + to_snake_case(param) + "')");
                }
                if (!in_trait && !is_runtime_bridge && type && format_type(type) == "any") {
                    add_diag(func->line, 1, "any-overuse",
                             "Parameter '" + param + "' uses dynamic 'any' type",
                             "prefer a concrete type (e.g. 'int', 'str') or trait contract to enable static safety");
                }
                VarMeta meta;
                meta.line = func->line;
                meta.is_list = (type && type->isList);
                scope_stack.back()[param] = meta;
            }

            if (!in_trait && !is_runtime_bridge && func->returnType.has_value() && func->returnType.value() && format_type(func->returnType.value()) == "any") {
                add_diag(func->line, 1, "any-overuse",
                         "Function '" + func->name + "' has return type 'any'",
                         "prefer concrete return type or trait for static verification");
            }

            if (func->body) {
                std::unordered_set<std::string> used_names;
                collect_referenced_vars(func->body, used_names);

                for (const auto& s : func->body->statements) {
                    if (auto vd = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(s)) {
                        if (!vd->name.empty() && vd->name[0] != '_' && used_names.find(vd->name) == used_names.end()) {
                            add_diag(vd->line, 1, "unused-var",
                                     "Variable '" + vd->name + "' is declared but never read",
                                     "if this variable is intentionally unused, prefix its name with '_' (e.g. '_" + vd->name + "')");
                        }
                    }
                }
            }

            visit_block(func->body);
            pop_scope();
            return;
        }

        if (auto frame = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            if (is_reserved_keyword(frame->name)) {
                add_diag(frame->line, 1, "reserved-identifier",
                         "'" + frame->name + "' is a reserved language keyword and cannot be used as a frame name",
                         "rename frame to an identifier that does not conflict with reserved keywords");
            }

            if (!is_pascal_case(frame->name)) {
                add_diag(frame->line, 1, "naming-convention",
                         "Frame '" + frame->name + "' should be PascalCase (e.g. '" + to_pascal_case(frame->name) + "')",
                         "rename frame to follow PascalCase convention");
            }

            for (const auto& field : frame->fields) {
                if (field && !field->name.empty()) {
                    if (is_reserved_keyword(field->name)) {
                        add_diag(field->line, 1, "reserved-identifier",
                                 "Frame field '" + field->name + "' is a reserved keyword",
                                 "rename field to avoid reserved keyword collision (AGENTS.md)");
                    }
                    if (!is_snake_case(field->name) && !is_all_caps(field->name)) {
                        add_diag(field->line, 1, "naming-convention",
                                 "Frame field '" + field->name + "' should be snake_case",
                                 "rename field to follow snake_case convention");
                    }
                }
            }

            if (frame->init) visit_method(frame->init);
            if (frame->deinit) visit_method(frame->deinit);
            for (const auto& m : frame->methods) visit_method(m);
            return;
        }

        if (auto trait = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
            if (is_reserved_keyword(trait->name)) {
                add_diag(trait->line, 1, "reserved-identifier",
                         "'" + trait->name + "' is a reserved keyword and cannot be used as a trait name",
                         "rename trait to avoid keyword collision");
            }

            if (!is_pascal_case(trait->name)) {
                add_diag(trait->line, 1, "naming-convention",
                         "Trait '" + trait->name + "' should be PascalCase (e.g. '" + to_pascal_case(trait->name) + "')",
                         "rename trait to follow PascalCase convention");
            }

            bool prev_in_trait = in_trait;
            in_trait = true;
            for (const auto& m : trait->methods) {
                visit_statement(m);
            }
            in_trait = prev_in_trait;
            return;
        }

        if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
            if (is_reserved_keyword(var_decl->name)) {
                add_diag(var_decl->line, 1, "reserved-identifier",
                         "Variable '" + var_decl->name + "' is a reserved language keyword",
                         "rename variable to avoid keyword collision (AGENTS.md)");
            }

            if (var_decl->name == "this") {
                add_diag(var_decl->line, 1, "this-forbidden",
                         "Use of 'this' is forbidden in Lymar",
                         "in Lymar, 'self' is the canonical instance reference; replace 'this' with 'self' (AGENTS.md)");
            }

            if (!var_decl->name.empty() && !is_snake_case(var_decl->name) && !is_all_caps(var_decl->name)) {
                add_diag(var_decl->line, 1, "naming-convention",
                         "Variable '" + var_decl->name + "' should be snake_case",
                         "rename variable to follow snake_case convention");
            }

            int outer_line = find_in_outer_scopes(var_decl->name);
            if (outer_line > 0) {
                add_diag(var_decl->line, 1, "variable-shadowing",
                         "Variable '" + var_decl->name + "' shadows variable declared on line " + std::to_string(outer_line),
                         "consider renaming the inner variable to avoid unintended shadowing and confusion");
            }

            if (!is_runtime_bridge && var_decl->type.has_value() && var_decl->type.value() && format_type(var_decl->type.value()) == "any") {
                add_diag(var_decl->line, 1, "any-overuse",
                         "Explicit 'any' dynamic type annotation on variable '" + var_decl->name + "'",
                         "prefer concrete type or trait contract to enable compiler optimizations and checks");
            }

            VarMeta meta;
            meta.line = var_decl->line;
            meta.is_list = (var_decl->type.has_value() && var_decl->type.value() && var_decl->type.value()->isList);
            if (std::dynamic_pointer_cast<Frontend::AST::ListExpr>(var_decl->initializer)) {
                meta.is_list = true;
            }

            if (!scope_stack.empty()) {
                scope_stack.back()[var_decl->name] = meta;
            }

            visit_expression(var_decl->initializer);
            return;
        }

        if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
            if (auto lit = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(if_stmt->condition)) {
                if (std::holds_alternative<bool>(lit->value)) {
                    bool val = std::get<bool>(lit->value);
                    add_diag(if_stmt->line, 1, "constant-condition",
                             std::string("Condition is always ") + (val ? "true" : "false") + "; branch outcome is fixed at compile time",
                             val ? "if-condition is redundant; remove check or simplify" : "if-branch is dead code; remove it");
                }
            }

            visit_expression(if_stmt->condition);

            if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(if_stmt->thenBranch)) {
                if (block->statements.empty()) {
                    add_diag(if_stmt->line, 1, "empty-block",
                             "Empty 'if' branch contains no statements",
                             "remove the empty branch or add implementation logic");
                }
            }
            visit_statement(if_stmt->thenBranch);
            visit_statement(if_stmt->elseBranch);
            return;
        }

        if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
            if (auto lit = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(while_stmt->condition)) {
                if (std::holds_alternative<bool>(lit->value)) {
                    bool val = std::get<bool>(lit->value);
                    if (!val) {
                        add_diag(while_stmt->line, 1, "constant-condition",
                                 "'while (false)' loop body will never execute",
                                 "remove loop or adjust condition");
                    }
                }
            }

            visit_expression(while_stmt->condition);
            if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(while_stmt->body)) {
                if (block->statements.empty()) {
                    add_diag(while_stmt->line, 1, "empty-block",
                             "Empty 'while' loop body",
                             "remove loop or add implementation body");
                }
            }
            visit_statement(while_stmt->body);
            return;
        }

        if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
            push_scope();
            visit_statement(for_stmt->initializer);
            visit_expression(for_stmt->condition);
            visit_expression(for_stmt->increment);
            if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(for_stmt->body)) {
                if (block->statements.empty()) {
                    add_diag(for_stmt->line, 1, "empty-block",
                             "Empty 'for' loop body",
                             "remove loop or add loop body statements");
                }
            }
            visit_statement(for_stmt->body);
            pop_scope();
            return;
        }

        if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
            push_scope();
            for (const auto& v : iter_stmt->loopVars) {
                if (is_reserved_keyword(v)) {
                    add_diag(iter_stmt->line, 1, "reserved-identifier",
                             "Loop variable '" + v + "' is a reserved language keyword",
                             "rename loop variable to avoid keyword collision (AGENTS.md)");
                }
                int outer_line = find_in_outer_scopes(v);
                if (outer_line > 0) {
                    add_diag(iter_stmt->line, 1, "variable-shadowing",
                             "Iteration variable '" + v + "' shadows variable declared on line " + std::to_string(outer_line),
                             "rename iteration variable to avoid shadowing");
                }
                VarMeta meta;
                meta.line = iter_stmt->line;
                scope_stack.back()[v] = meta;
            }

            visit_expression(iter_stmt->iterable);
            if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(iter_stmt->body)) {
                if (block->statements.empty()) {
                    add_diag(iter_stmt->line, 1, "empty-block",
                             "Empty 'iter' loop body",
                             "remove loop or add loop body statements");
                }
            }
            visit_statement(iter_stmt->body);
            pop_scope();
            return;
        }

        if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
            visit_block(block);
            return;
        }

        if (auto ret = std::dynamic_pointer_cast<Frontend::AST::ReturnStatement>(stmt)) {
            visit_expression(ret->value);
            return;
        }

        if (auto expr_stmt = std::dynamic_pointer_cast<Frontend::AST::ExprStatement>(stmt)) {
            if (auto call = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(expr_stmt->expression)) {
                if (auto var_callee = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(call->callee)) {
                    if (fallible_functions.find(var_callee->name) != fallible_functions.end()) {
                        add_diag(expr_stmt->line, 1, "unhandled-fallible",
                                 "Fallible call to '" + var_callee->name + "' result is discarded without handling",
                                 "handle the fallible result using '?' to propagate or '? else { ... }' for fallback");
                    }
                }
            }
            visit_expression(expr_stmt->expression);
            return;
        }
    }

    void visit_method(const std::shared_ptr<Frontend::AST::FrameMethod>& m) {
        if (!m) return;
        if (is_reserved_keyword(m->name)) {
            add_diag(m->line, 1, "reserved-identifier",
                     "Method name '" + m->name + "' is a reserved language keyword",
                     "rename method to an identifier that does not conflict with keywords");
        }
        if (!is_snake_case(m->name) && m->name != "init" && m->name != "deinit") {
            add_diag(m->line, 1, "naming-convention",
                     "Method '" + m->name + "' should be snake_case (e.g. '" + to_snake_case(m->name) + "')",
                     "rename method to follow snake_case convention");
        }
        push_scope();
        for (const auto& [param, type] : m->parameters) {
            if (is_reserved_keyword(param)) {
                add_diag(m->line, 1, "reserved-identifier",
                         "Parameter '" + param + "' is a reserved keyword",
                         "rename parameter to avoid keyword collision (AGENTS.md)");
            }
            VarMeta meta;
            meta.line = m->line;
            meta.is_list = (type && type->isList);
            scope_stack.back()[param] = meta;
        }
        visit_block(m->body);
        pop_scope();
    }

    void visit_expression(const std::shared_ptr<Frontend::AST::Expression>& expr) {
        if (!expr) return;

        if (auto var_expr = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr)) {
            if (var_expr->name == "this") {
                add_diag(var_expr->line, 1, "this-forbidden",
                         "Use of 'this' is forbidden in Lymar",
                         "in Lymar, 'self' is the canonical instance reference; replace 'this' with 'self' (AGENTS.md)");
            }
            return;
        }

        if (auto bin = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
            // Self-comparison check (e.g., x == x, y != y)
            if (bin->op == Frontend::TokenType::EQUAL_EQUAL || bin->op == Frontend::TokenType::BANG_EQUAL ||
                bin->op == Frontend::TokenType::LESS || bin->op == Frontend::TokenType::GREATER ||
                bin->op == Frontend::TokenType::LESS_EQUAL || bin->op == Frontend::TokenType::GREATER_EQUAL) {
                auto l = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->left);
                auto r = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->right);
                if (l && r && !l->name.empty() && l->name == r->name) {
                    add_diag(bin->line, 1, "self-comparison",
                             "Self-comparison detected: '" + l->name + "' compared to itself",
                             "comparing a variable to itself always evaluates to a constant; remove or fix comparison operand");
                }
            }

            // Redundant boolean comparison check (e.g., x == true)
            if (bin->op == Frontend::TokenType::EQUAL_EQUAL || bin->op == Frontend::TokenType::BANG_EQUAL) {
                auto check_bool = [&](const std::shared_ptr<Frontend::AST::Expression>& e) -> bool {
                    if (auto lit = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(e)) {
                        return std::holds_alternative<bool>(lit->value);
                    }
                    return false;
                };

                if (check_bool(bin->left) || check_bool(bin->right)) {
                    add_diag(bin->line, 1, "redundant-bool",
                             "Redundant comparison with boolean literal",
                             "simplify expression by using the condition directly (e.g. 'if (cond)' instead of 'if (cond == true)')");
                }
            }

            // List concatenation via '+' check (unsupported per AGENTS.md)
            if (bin->op == Frontend::TokenType::PLUS) {
                bool is_left_list = std::dynamic_pointer_cast<Frontend::AST::ListExpr>(bin->left) != nullptr;
                bool is_right_list = std::dynamic_pointer_cast<Frontend::AST::ListExpr>(bin->right) != nullptr;

                if (!is_left_list) {
                    if (auto lv = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->left)) {
                        is_left_list = is_known_list_var(lv->name);
                    }
                }
                if (!is_right_list) {
                    if (auto rv = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(bin->right)) {
                        is_right_list = is_known_list_var(rv->name);
                    }
                }

                if (is_left_list || is_right_list) {
                    add_diag(bin->line, 1, "list-concat",
                             "List concatenation with '+' is unsupported in Lymar",
                             "in Lymar, '+' is not supported for lists; use 'append(list, item)' or 'append(list, other_list)' instead (AGENTS.md)");
                }
            }

            visit_expression(bin->left);
            visit_expression(bin->right);
            return;
        }

        if (auto un = std::dynamic_pointer_cast<Frontend::AST::UnaryExpr>(expr)) {
            visit_expression(un->right);
            return;
        }

        if (auto call = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(expr)) {
            visit_expression(call->callee);
            for (const auto& a : call->arguments) visit_expression(a);
            for (const auto& [k, v] : call->namedArgs) visit_expression(v);
            return;
        }

        if (auto assign = std::dynamic_pointer_cast<Frontend::AST::AssignExpr>(expr)) {
            visit_expression(assign->object);
            visit_expression(assign->index);
            visit_expression(assign->value);
            return;
        }

        if (auto member = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(expr)) {
            visit_expression(member->object);
            return;
        }

        if (auto idx = std::dynamic_pointer_cast<Frontend::AST::IndexExpr>(expr)) {
            visit_expression(idx->object);
            visit_expression(idx->index);
            return;
        }

        if (auto fallible = std::dynamic_pointer_cast<Frontend::AST::FallibleExpr>(expr)) {
            visit_expression(fallible->expression);
            visit_statement(fallible->elseHandler);
            return;
        }

        if (auto list_expr = std::dynamic_pointer_cast<Frontend::AST::ListExpr>(expr)) {
            for (const auto& el : list_expr->elements) visit_expression(el);
            return;
        }

        if (auto tuple_expr = std::dynamic_pointer_cast<Frontend::AST::TupleExpr>(expr)) {
            for (const auto& el : tuple_expr->elements) visit_expression(el);
            return;
        }

        if (auto dict_expr = std::dynamic_pointer_cast<Frontend::AST::DictExpr>(expr)) {
            for (const auto& el : dict_expr->entries) {
                visit_expression(el.first);
                visit_expression(el.second);
            }
            return;
        }

        if (auto cast_expr = std::dynamic_pointer_cast<Frontend::AST::CastExpr>(expr)) {
            visit_expression(cast_expr->expression);
            return;
        }
    }
};

void print_friendly_diagnostic(const LintDiagnostic& d, const std::vector<std::string>& file_lines, bool use_color) {
    std::string reset = use_color ? "\033[0m" : "";
    std::string bold = use_color ? "\033[1m" : "";
    std::string red = use_color ? "\033[1;31m" : "";
    std::string yellow = use_color ? "\033[1;33m" : "";
    std::string cyan = use_color ? "\033[1;36m" : "";
    std::string green = use_color ? "\033[1;32m" : "";
    std::string line_blue = use_color ? "\033[34m" : "";

    std::string sev_color = (d.severity == "error") ? red : yellow;

    std::cout << sev_color << d.severity << "[" << d.rule << "]" << reset
              << bold << ": " << d.message << reset << "\n";

    std::cout << cyan << "  --> " << reset << d.file << ":" << d.line << ":" << d.column << "\n";

    if (d.line > 0 && d.line <= static_cast<int>(file_lines.size())) {
        std::string line_str = std::to_string(d.line);
        std::string pad(line_str.size(), ' ');

        std::cout << line_blue << "   " << pad << "|\n" << reset;

        std::string code = file_lines[d.line - 1];
        while (!code.empty() && (code.back() == '\r' || code.back() == '\n')) {
            code.pop_back();
        }

        std::cout << line_blue << " " << line_str << " | " << reset << code << "\n";

        std::cout << line_blue << "   " << pad << "| " << reset << sev_color;
        int indent = 0;
        while (indent < static_cast<int>(code.size()) && (code[indent] == ' ' || code[indent] == '\t')) {
            indent++;
        }
        for (int i = 0; i < indent; ++i) std::cout << ' ';
        int caret_len = std::max(1, static_cast<int>(code.size()) - indent);
        for (int i = 0; i < caret_len; ++i) std::cout << '^';
        std::cout << reset << "\n";
    }

    if (!d.help.empty()) {
        std::string line_str = (d.line > 0) ? std::to_string(d.line) : "";
        std::string pad(line_str.size(), ' ');
        std::cout << green << "   " << pad << "= help: " << reset << d.help << "\n";
    }

    std::cout << "\n";
}

} // namespace

std::vector<LintDiagnostic> Linter::lintSource(const std::string& filename, const std::string& source, const Options& opts) {
    (void)opts;
    try {
        Frontend::Scanner scanner(source, filename);
        scanner.scanTokens();
        Frontend::Parser parser(scanner);
        auto program = parser.parse();
        if (!program) return {};

        LintVisitor visitor;
        visitor.filename = filename;
        visitor.visit_program(program);
        return visitor.diagnostics;
    } catch (const std::exception& e) {
        if (filename.find("/errors/") != std::string::npos || filename.find("\\errors\\") != std::string::npos) {
            return {};
        }
        return {{filename, 1, 1, "error", "syntax-error", e.what(), "fix syntax errors before linting"}};
    }
}

std::vector<LintDiagnostic> Linter::lintFile(const std::string& filepath, const Options& opts) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return {{filepath, 0, 0, "error", "io", "Could not open file for linting", "ensure the file exists and is readable"}};
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return lintSource(filepath, buffer.str(), opts);
}

int Linter::run(int argc, char** argv) {
    enable_ansi_colors();

    Options opts;
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--fix") {
            return runFix(argc, argv);
        } else if (arg == "--deny-warnings" || arg == "-Werror") {
            opts.deny_warnings = true;
        } else if (arg == "--json") {
            opts.json_output = true;
        } else if (arg == "--no-color") {
            opts.no_color = true;
        } else if (arg == "-v" || arg == "--verbose") {
            opts.verbose = true;
        } else if (arg[0] != '-') {
            opts.target_paths.push_back(arg);
        }
    }

    if (opts.target_paths.empty()) {
        if (fs::exists("std")) opts.target_paths.push_back("std");
        if (fs::exists("tests")) opts.target_paths.push_back("tests");
    }

    std::vector<std::string> files_to_lint;
    for (const auto& path_str : opts.target_paths) {
        if (fs::is_regular_file(path_str)) {
            files_to_lint.push_back(path_str);
        } else if (fs::is_directory(path_str)) {
            for (const auto& entry : fs::recursive_directory_iterator(path_str)) {
                if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                    std::string gen_path = entry.path().generic_string();
                    if (gen_path.find("tests/errors/") != std::string::npos || gen_path.find("tests/negative/") != std::string::npos) continue;
                    files_to_lint.push_back(gen_path);
                }
            }
        }
    }

    std::sort(files_to_lint.begin(), files_to_lint.end());

    size_t warning_count = 0;
    size_t error_count = 0;

    for (const auto& file : files_to_lint) {
        std::ifstream f(file);
        std::vector<std::string> lines;
        std::string l;
        while (std::getline(f, l)) {
            lines.push_back(l);
        }

        auto diags = lintFile(file, opts);
        for (const auto& d : diags) {
            if (d.severity == "error") error_count++;
            else warning_count++;

            if (opts.json_output) {
                std::cout << "{\"file\":\"" << d.file << "\",\"line\":" << d.line
                          << ",\"column\":" << d.column
                          << ",\"rule\":\"" << d.rule << "\",\"severity\":\"" << d.severity
                          << "\",\"message\":\"" << d.message << "\",\"help\":\"" << d.help << "\"}\n";
            } else {
                print_friendly_diagnostic(d, lines, !opts.no_color);
            }
        }
    }

    if (!opts.json_output) {
        std::string bold = !opts.no_color ? "\033[1m" : "";
        std::string green = !opts.no_color ? "\033[1;32m" : "";
        std::string yellow = !opts.no_color ? "\033[1;33m" : "";
        std::string red = !opts.no_color ? "\033[1;31m" : "";
        std::string reset = !opts.no_color ? "\033[0m" : "";

        if (error_count == 0 && warning_count == 0) {
            std::cout << green << "✨ All checks passed! No lint issues found across "
                      << files_to_lint.size() << " files." << reset << "\n";
        } else {
            std::cout << (error_count > 0 ? red : yellow) << bold
                      << (error_count > 0 ? "✖ " : "⚠ ")
                      << "Linter finished: " << warning_count << " warning" << (warning_count == 1 ? "" : "s")
                      << ", " << error_count << " error" << (error_count == 1 ? "" : "s")
                      << " across " << files_to_lint.size() << " file" << (files_to_lint.size() == 1 ? "" : "s")
                      << "." << reset << "\n";
            if (warning_count > 0 && !opts.deny_warnings) {
                std::cout << "  (tip: run with " << bold << "--deny-warnings" << reset << " or " << bold << "-Werror" << reset << " to treat warnings as build-breaking errors)\n";
            }
        }
    }

    if (error_count > 0 || (opts.deny_warnings && warning_count > 0)) {
        return 1;
    }
    return 0;
}

int Linter::runFix(int argc, char** argv) {
    enable_ansi_colors();

    FixOptions opts;
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--dry-run") {
            opts.dry_run = true;
        } else if (arg == "-v" || arg == "--verbose") {
            opts.verbose = true;
        } else if (arg == "--no-color") {
            opts.no_color = true;
        } else if (arg == "--fix") {
            // ignore if passed to fix command
        } else if (arg[0] != '-') {
            opts.target_paths.push_back(arg);
        }
    }

    if (opts.target_paths.empty()) {
        if (fs::exists("std")) opts.target_paths.push_back("std");
        if (fs::exists("tests")) opts.target_paths.push_back("tests");
        if (fs::exists("src")) opts.target_paths.push_back("src");
    }

    std::vector<std::string> files_to_fix;
    for (const auto& path_str : opts.target_paths) {
        if (fs::is_regular_file(path_str)) {
            files_to_fix.push_back(path_str);
        } else if (fs::is_directory(path_str)) {
            for (const auto& entry : fs::recursive_directory_iterator(path_str)) {
                if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                    std::string gen_path = entry.path().generic_string();
                    if (gen_path.find("tests/errors/") != std::string::npos || gen_path.find("tests/negative/") != std::string::npos) continue;
                    files_to_fix.push_back(gen_path);
                }
            }
        }
    }

    std::sort(files_to_fix.begin(), files_to_fix.end());

    std::string bold = !opts.no_color ? "\033[1m" : "";
    std::string green = !opts.no_color ? "\033[1;32m" : "";
    std::string yellow = !opts.no_color ? "\033[1;33m" : "";
    std::string cyan = !opts.no_color ? "\033[1;36m" : "";
    std::string reset = !opts.no_color ? "\033[0m" : "";

    size_t total_fixes = 0;
    size_t files_modified = 0;

    auto rename_identifiers_in_line = [&](std::string& line, const std::string& sym, const std::string& target) -> bool {
        bool line_modified = false;
        bool in_str = false;
        char quote = 0;
        int interp_depth = 0;

        size_t i = 0;
        while (i < line.length()) {
            if (in_str) {
                if (line[i] == '\\' && i + 1 < line.length()) {
                    i += 2;
                    continue;
                }
                if (line[i] == quote && interp_depth == 0) {
                    in_str = false;
                    i++;
                    continue;
                }
                if (line[i] == '{') {
                    interp_depth++;
                    i++;
                    continue;
                }
                if (line[i] == '}' && interp_depth > 0) {
                    interp_depth--;
                    i++;
                    continue;
                }
                if (interp_depth == 0) {
                    i++;
                    continue;
                }
            } else {
                if (line[i] == '"' || line[i] == '\'') {
                    in_str = true;
                    quote = line[i];
                    interp_depth = 0;
                    i++;
                    continue;
                }
                if (line[i] == '/' && i + 1 < line.length() && line[i + 1] == '/') {
                    break;
                }
            }

            if (line.compare(i, sym.length(), sym) == 0) {
                bool left_boundary = (i == 0 || (!isalnum(static_cast<unsigned char>(line[i - 1])) && line[i - 1] != '_'));
                bool right_boundary = (i + sym.length() >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + sym.length()])) && line[i + sym.length()] != '_'));
                if (left_boundary && right_boundary) {
                    line.replace(i, sym.length(), target);
                    i += target.length();
                    line_modified = true;
                    continue;
                }
            }
            i++;
        }
        return line_modified;
    };

    Options lint_opts;
    for (const auto& file : files_to_fix) {
        std::ifstream in(file);
        if (!in.is_open()) continue;
        std::vector<std::string> lines;
        std::string l;
        while (std::getline(in, l)) {
            lines.push_back(l);
        }
        in.close();

        auto diags = lintFile(file, lint_opts);
        if (diags.empty()) continue;

        // Sort diagnostics descending by line number so edits do not disrupt earlier lines
        std::sort(diags.begin(), diags.end(), [](const LintDiagnostic& a, const LintDiagnostic& b) {
            return a.line > b.line;
        });

        AstDeclarations decls;
        std::string initial_content;
        for (const auto& line_str : lines) {
            initial_content += line_str + "\n";
        }
        try {
            Frontend::Scanner scanner(initial_content, file);
            scanner.scanTokens();
            Frontend::Parser parser(scanner);
            auto file_ast = parser.parse();
            if (file_ast) {
                for (const auto& s : file_ast->statements) {
                    collect_declarations(s, decls);
                }
            }
        } catch (...) {}

        auto verify_program_clean = [&](const std::vector<std::string>& test_lines) -> bool {
            std::string test_source;
            for (const auto& tl : test_lines) {
                if (tl == "__LYMAR_REMOVED_LINE__") continue;
                test_source += tl + "\n";
            }
            try {
                // Silence stderr/stdout during speculative verification check
                std::stringstream sink;
                auto* old_cerr = std::cerr.rdbuf(sink.rdbuf());
                auto* old_cout = std::cout.rdbuf(sink.rdbuf());

                Frontend::Scanner scanner(test_source, file);
                scanner.scanTokens();
                Frontend::Parser parser(scanner);
                auto prog = parser.parse();
                bool clean = false;
                if (prog) {
                    auto result = Frontend::TypeCheckerFactory::check_program(prog, test_source, file);
                    clean = result.success;
                }

                std::cerr.rdbuf(old_cerr);
                std::cout.rdbuf(old_cout);
                return clean;
            } catch (...) {
                return false;
            }
        };

        int file_fixes = 0;
        std::unordered_set<int> fixed_redundant_bool_lines;
        std::unordered_set<std::string> fixed_naming_symbols;
        for (const auto& d : diags) {
            if (d.line <= 0 || static_cast<size_t>(d.line) > lines.size()) continue;
            std::string& line = lines[d.line - 1];

            if (d.rule == "unused-import") {
                std::string sym;
                auto q1 = d.message.find('\'');
                if (q1 != std::string::npos) {
                    auto q2 = d.message.find('\'', q1 + 1);
                    if (q2 != std::string::npos) {
                        sym = d.message.substr(q1 + 1, q2 - q1 - 1);
                    }
                }

                bool fixed = false;
                if (!sym.empty()) {
                    auto show_pos = line.find("show");
                    if (show_pos != std::string::npos) {
                        auto sym_pos = line.find(sym, show_pos);
                        if (sym_pos != std::string::npos) {
                            size_t comma_before = line.rfind(',', sym_pos);
                            if (comma_before != std::string::npos && comma_before >= show_pos) {
                                line.erase(comma_before, (sym_pos + sym.length()) - comma_before);
                                fixed = true;
                            } else {
                                size_t comma_after = line.find(',', sym_pos + sym.length());
                                if (comma_after != std::string::npos) {
                                    size_t next_char = line.find_first_not_of(" \t", comma_after + 1);
                                    if (next_char != std::string::npos) {
                                        line.erase(sym_pos, next_char - sym_pos);
                                    } else {
                                        line.erase(sym_pos, (comma_after + 1) - sym_pos);
                                    }
                                    fixed = true;
                                } else {
                                    line = "__LYMAR_REMOVED_LINE__";
                                    fixed = true;
                                }
                            }
                        }
                    } else {
                        line = "__LYMAR_REMOVED_LINE__";
                        fixed = true;
                    }
                } else {
                    line = "__LYMAR_REMOVED_LINE__";
                    fixed = true;
                }

                if (fixed) {
                    file_fixes++;
                    if (opts.verbose) {
                        std::cout << cyan << "  [fix] " << reset << file << ":" << d.line << ": removed unused import '" << sym << "'\n";
                    }
                }
            } else if (d.rule == "redundant-bool") {
                if (fixed_redundant_bool_lines.count(d.line)) continue;
                fixed_redundant_bool_lines.insert(d.line);

                enum class BoolFixKind { Remove, Negate };
                struct BoolMatch {
                    size_t op_pos;
                    size_t op_len;
                    BoolFixKind kind;
                };

                std::vector<BoolMatch> matches;
                bool in_str = false;
                char quote_char = 0;
                for (size_t i = 0; i < line.length(); ++i) {
                    if (in_str) {
                        if (line[i] == '\\' && i + 1 < line.length()) {
                            i++;
                        } else if (line[i] == quote_char) {
                            in_str = false;
                        }
                    } else {
                        if (line[i] == '"' || line[i] == '\'') {
                            in_str = true;
                            quote_char = line[i];
                        } else if (line[i] == '/' && i + 1 < line.length() && line[i + 1] == '/') {
                            break;
                        } else {
                            if (line.compare(i, 8, "== false") == 0) {
                                if (i + 8 >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + 8])) && line[i + 8] != '_')) {
                                    matches.push_back({i, 8, BoolFixKind::Negate});
                                    i += 7;
                                    continue;
                                }
                            } else if (line.compare(i, 7, "!= true") == 0) {
                                if (i + 7 >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + 7])) && line[i + 7] != '_')) {
                                    matches.push_back({i, 7, BoolFixKind::Negate});
                                    i += 6;
                                    continue;
                                }
                            } else if (line.compare(i, 7, "== true") == 0) {
                                if (i + 7 >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + 7])) && line[i + 7] != '_')) {
                                    matches.push_back({i, 7, BoolFixKind::Remove});
                                    i += 6;
                                    continue;
                                }
                            } else if (line.compare(i, 8, "!= false") == 0) {
                                if (i + 8 >= line.length() || (!isalnum(static_cast<unsigned char>(line[i + 8])) && line[i + 8] != '_')) {
                                    matches.push_back({i, 8, BoolFixKind::Remove});
                                    i += 7;
                                    continue;
                                }
                            }
                        }
                    }
                }

                // Sort descending by position so rightmost replacements don't invalidate leftmost offsets
                std::sort(matches.begin(), matches.end(), [](const BoolMatch& a, const BoolMatch& b) {
                    return a.op_pos > b.op_pos;
                });

                bool fixed = false;
                for (const auto& m : matches) {
                    size_t op_pos = m.op_pos;
                    size_t op_len = m.op_len;
                    size_t left_end = op_pos;
                    while (left_end > 0 && (line[left_end - 1] == ' ' || line[left_end - 1] == '\t')) {
                        left_end--;
                    }
                    if (left_end == 0) continue;

                    if (m.kind == BoolFixKind::Remove) {
                        line.erase(left_end, (op_pos + op_len) - left_end);
                        fixed = true;
                    } else if (m.kind == BoolFixKind::Negate) {
                        size_t p = left_end;
                        if (line[p - 1] == ')') {
                            int depth = 0;
                            size_t cur = p - 1;
                            bool found = false;
                            while (true) {
                                if (line[cur] == ')') depth++;
                                else if (line[cur] == '(') {
                                    depth--;
                                    if (depth == 0) {
                                        p = cur;
                                        found = true;
                                        break;
                                    }
                                }
                                if (cur == 0) break;
                                cur--;
                            }
                            if (!found) continue;

                            // Trace backwards over any chained calls, indexing, or member accesses
                            while (p > 0) {
                                if (line[p - 1] == ']') {
                                    int bdepth = 0;
                                    size_t bcur = p - 1;
                                    bool bfound = false;
                                    while (true) {
                                        if (line[bcur] == ']') bdepth++;
                                        else if (line[bcur] == '[') {
                                            bdepth--;
                                            if (bdepth == 0) {
                                                p = bcur;
                                                bfound = true;
                                                break;
                                            }
                                        }
                                        if (bcur == 0) break;
                                        bcur--;
                                    }
                                    if (!bfound) break;
                                } else if (line[p - 1] == ')') {
                                    int cdepth = 0;
                                    size_t ccur = p - 1;
                                    bool cfound = false;
                                    while (true) {
                                        if (line[ccur] == ')') cdepth++;
                                        else if (line[ccur] == '(') {
                                            cdepth--;
                                            if (cdepth == 0) {
                                                p = ccur;
                                                cfound = true;
                                                break;
                                            }
                                        }
                                        if (ccur == 0) break;
                                        ccur--;
                                    }
                                    if (!cfound) break;
                                } else if (isalnum(static_cast<unsigned char>(line[p - 1])) || line[p - 1] == '_' || line[p - 1] == '.') {
                                    p--;
                                } else {
                                    break;
                                }
                            }
                        } else if (line[p - 1] == ']') {
                            int bdepth = 0;
                            size_t bcur = p - 1;
                            bool bfound = false;
                            while (true) {
                                if (line[bcur] == ']') bdepth++;
                                else if (line[bcur] == '[') {
                                    bdepth--;
                                    if (bdepth == 0) {
                                        p = bcur;
                                        bfound = true;
                                        break;
                                    }
                                }
                                if (bcur == 0) break;
                                bcur--;
                            }
                            if (bfound) {
                                while (p > 0 && (isalnum(static_cast<unsigned char>(line[p - 1])) || line[p - 1] == '_' || line[p - 1] == '.')) {
                                    p--;
                                }
                            }
                        } else {
                            while (p > 0 && (isalnum(static_cast<unsigned char>(line[p - 1])) || line[p - 1] == '_' || line[p - 1] == '.')) {
                                p--;
                            }
                        }

                        if (p < left_end) {
                            line.erase(left_end, (op_pos + op_len) - left_end);
                            if (p >= 4 && line.substr(p - 4, 4) == "not ") {
                                line.erase(p - 4, 4);
                            } else if (p >= 1 && line[p - 1] == '!') {
                                line.erase(p - 1, 1);
                            } else {
                                line.insert(p, "not ");
                            }
                            fixed = true;
                        }
                    }
                }

                if (fixed) {
                    file_fixes++;
                    if (opts.verbose) {
                        std::cout << cyan << "  [fix] " << reset << file << ":" << d.line << ": simplified redundant boolean comparison\n";
                    }
                }
            } else if (d.rule == "this-forbidden") {
                bool fixed = false;
                size_t pos = 0;
                while ((pos = line.find("this.", pos)) != std::string::npos) {
                    line.replace(pos, 5, "self.");
                    pos += 5;
                    fixed = true;
                }
                pos = 0;
                while ((pos = line.find("this", pos)) != std::string::npos) {
                    bool left_boundary = (pos == 0 || (!isalnum(line[pos - 1]) && line[pos - 1] != '_'));
                    bool right_boundary = (pos + 4 >= line.length() || (!isalnum(line[pos + 4]) && line[pos + 4] != '_'));
                    if (left_boundary && right_boundary) {
                        line.replace(pos, 4, "self");
                        pos += 4;
                        fixed = true;
                    } else {
                        pos += 4;
                    }
                }
                if (fixed) {
                    file_fixes++;
                    if (opts.verbose) {
                        std::cout << cyan << "  [fix] " << reset << file << ":" << d.line << ": replaced forbidden 'this' with 'self'\n";
                    }
                }
            } else if (d.rule == "unused-var") {
                std::string var_name;
                auto q1 = d.message.find('\'');
                if (q1 != std::string::npos) {
                    auto q2 = d.message.find('\'', q1 + 1);
                    if (q2 != std::string::npos) {
                        var_name = d.message.substr(q1 + 1, q2 - q1 - 1);
                    }
                }
                if (!var_name.empty()) {
                    bool fixed = false;
                    std::string target_var = "var " + var_name;
                    auto pos = line.find(target_var);
                    if (pos != std::string::npos) {
                        line.replace(pos, target_var.length(), "var _" + var_name);
                        fixed = true;
                    } else {
                        std::string target_val = "val " + var_name;
                        pos = line.find(target_val);
                        if (pos != std::string::npos) {
                            line.replace(pos, target_val.length(), "val _" + var_name);
                            fixed = true;
                        }
                    }
                    if (fixed) {
                        file_fixes++;
                        if (opts.verbose) {
                            std::cout << cyan << "  [fix] " << reset << file << ":" << d.line << ": prefixed unused variable '" << var_name << "' with '_'\n";
                        }
                    }
                }
            } else if (d.rule == "naming-convention") {
                std::string sym;
                auto q1 = d.message.find('\'');
                if (q1 != std::string::npos) {
                    auto q2 = d.message.find('\'', q1 + 1);
                    if (q2 != std::string::npos) {
                        sym = d.message.substr(q1 + 1, q2 - q1 - 1);
                    }
                }
                if (!sym.empty() && fixed_naming_symbols.find(sym) == fixed_naming_symbols.end()) {
                    fixed_naming_symbols.insert(sym);

                    std::string target;
                    if (d.message.find("Frame '") != std::string::npos || d.message.find("Trait '") != std::string::npos) {
                        target = to_pascal_case(sym);
                    } else {
                        target = to_snake_case(sym);
                    }

                    if (!target.empty() && target != sym) {
                        bool any_renamed = false;
                        for (auto& file_line : lines) {
                            if (rename_identifiers_in_line(file_line, sym, target)) {
                                any_renamed = true;
                            }
                        }
                        if (any_renamed) {
                            file_fixes++;
                            if (opts.verbose) {
                                std::cout << cyan << "  [fix] " << reset << file << ":" << d.line << ": renamed '" << sym << "' to '" << target << "'\n";
                            }
                        }
                    }
                }
            } else if (d.rule == "any-overuse") {
                std::string orig_line = line;
                bool fix_attempted = false;
                std::string fix_desc = "";

                if (d.message.find("Explicit 'any' dynamic type annotation on variable '") != std::string::npos) {
                    std::string var_name;
                    auto var_pos = d.message.find("variable '");
                    if (var_pos != std::string::npos) {
                        auto q1 = var_pos + 10;
                        auto q2 = d.message.find('\'', q1);
                        if (q2 != std::string::npos) var_name = d.message.substr(q1, q2 - q1);
                    }
                    if (!var_name.empty() && decls.vars_by_line.count(d.line)) {
                        for (const auto& vd : decls.vars_by_line[d.line]) {
                            if (vd->name == var_name && vd->initializer) {
                                std::unordered_map<std::string, std::string> vtypes;
                                std::string inferred = infer_expression_type(vd->initializer, vtypes);
                                if (!inferred.empty() && inferred != "any") {
                                    if (replace_var_annotation(line, var_name, "any", inferred)) {
                                        fix_attempted = true;
                                        fix_desc = "inferred variable '" + var_name + "' type as '" + inferred + "'";
                                        break;
                                    }
                                }
                            }
                        }
                    }
                } else if (d.message.find("has return type 'any'") != std::string::npos) {
                    std::string func_name;
                    auto q1 = d.message.find('\'');
                    if (q1 != std::string::npos) {
                        auto q2 = d.message.find('\'', q1 + 1);
                        if (q2 != std::string::npos) func_name = d.message.substr(q1 + 1, q2 - q1 - 1);
                    }
                    if (!func_name.empty()) {
                        std::shared_ptr<Frontend::AST::Statement> body = nullptr;
                        std::unordered_map<std::string, std::string> local_vars;
                        if (decls.funcs_by_line.count(d.line)) {
                            for (const auto& fd : decls.funcs_by_line[d.line]) {
                                if (fd->name == func_name) {
                                    body = fd->body;
                                    for (const auto& [pname, ptype] : fd->params) {
                                        if (ptype && format_type(ptype) != "any") local_vars[pname] = format_type(ptype);
                                        else {
                                            std::string p_inf;
                                            find_param_uses_in_stmt(pname, fd->body, p_inf);
                                            if (!p_inf.empty()) local_vars[pname] = p_inf;
                                        }
                                    }
                                    if (fd->body) {
                                        for (const auto& s : fd->body->statements) {
                                            if (auto vd = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(s)) {
                                                if (vd->initializer) {
                                                    std::string t = infer_expression_type(vd->initializer, local_vars);
                                                    if (!t.empty()) local_vars[vd->name] = t;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        if (body) {
                            std::vector<std::shared_ptr<Frontend::AST::ReturnStatement>> returns;
                            collect_return_statements(body, returns);
                            std::string inferred;
                            if (returns.empty()) {
                                inferred = "nil";
                            } else {
                                bool all_same = true;
                                for (const auto& ret : returns) {
                                    std::string t = infer_expression_type(ret->value, local_vars);
                                    if (t.empty()) { all_same = false; break; }
                                    if (inferred.empty()) inferred = t;
                                    else if (inferred != t) { all_same = false; break; }
                                }
                                if (!all_same) inferred = "";
                            }
                            if (!inferred.empty() && inferred != "any") {
                                if (replace_return_type_annotation(line, func_name, "any", inferred)) {
                                    fix_attempted = true;
                                    fix_desc = "inferred function '" + func_name + "' return type as '" + inferred + "'";
                                }
                            }
                        }
                    }
                } else if (d.message.find("uses dynamic 'any' type") != std::string::npos) {
                    std::string param_name;
                    auto q1 = d.message.find('\'');
                    if (q1 != std::string::npos) {
                        auto q2 = d.message.find('\'', q1 + 1);
                        if (q2 != std::string::npos) param_name = d.message.substr(q1 + 1, q2 - q1 - 1);
                    }
                    if (!param_name.empty()) {
                        std::shared_ptr<Frontend::AST::Statement> body = nullptr;
                        if (decls.funcs_by_line.count(d.line)) {
                            for (const auto& fd : decls.funcs_by_line[d.line]) {
                                for (const auto& [pname, ptype] : fd->params) {
                                    if (pname == param_name) {
                                        body = fd->body;
                                        break;
                                    }
                                }
                                if (body) break;
                            }
                        }
                        if (body) {
                            std::string inferred;
                            find_param_uses_in_stmt(param_name, body, inferred);
                            if (!inferred.empty() && inferred != "any") {
                                if (replace_var_annotation(line, param_name, "any", inferred)) {
                                    fix_attempted = true;
                                    fix_desc = "inferred parameter '" + param_name + "' type as '" + inferred + "'";
                                }
                            }
                        }
                    }
                }

                if (fix_attempted) {
                    if (verify_program_clean(lines)) {
                        file_fixes++;
                        if (opts.verbose) {
                            std::cout << cyan << "  [fix] " << reset << file << ":" << d.line << ": " << fix_desc << "\n";
                        }
                    } else {
                        line = orig_line;
                    }
                }
            } else if (d.rule == "missing-return-type") {
                std::string orig_line = line;
                bool fix_attempted = false;
                std::string fix_desc = "";
                std::string func_name;
                auto q1 = d.message.find('\'');
                if (q1 != std::string::npos) {
                    auto q2 = d.message.find('\'', q1 + 1);
                    if (q2 != std::string::npos) func_name = d.message.substr(q1 + 1, q2 - q1 - 1);
                }
                if (!func_name.empty() && decls.funcs_by_line.count(d.line)) {
                    for (const auto& fd : decls.funcs_by_line[d.line]) {
                        if (fd->name == func_name && fd->body) {
                            std::unordered_map<std::string, std::string> local_vars;
                            for (const auto& [pname, ptype] : fd->params) {
                                if (ptype) local_vars[pname] = format_type(ptype);
                            }
                            std::vector<std::shared_ptr<Frontend::AST::ReturnStatement>> returns;
                            collect_return_statements(fd->body, returns);
                            std::string inferred;
                            if (returns.empty()) {
                                inferred = "nil";
                            } else {
                                bool all_same = true;
                                for (const auto& ret : returns) {
                                    std::string t = infer_expression_type(ret->value, local_vars);
                                    if (t.empty()) { all_same = false; break; }
                                    if (inferred.empty()) inferred = t;
                                    else if (inferred != t) { all_same = false; break; }
                                }
                                if (!all_same) inferred = "";
                            }
                            if (!inferred.empty() && inferred != "any") {
                                if (insert_return_type_annotation(line, func_name, inferred)) {
                                    fix_attempted = true;
                                    fix_desc = "added inferred return type ':" + inferred + "' to function '" + func_name + "'";
                                }
                            }
                            break;
                        }
                    }
                }
                if (fix_attempted) {
                    if (verify_program_clean(lines)) {
                        file_fixes++;
                        if (opts.verbose) {
                            std::cout << cyan << "  [fix] " << reset << file << ":" << d.line << ": " << fix_desc << "\n";
                        }
                    } else {
                        line = orig_line;
                    }
                }
            }
        }

        if (file_fixes > 0) {
            total_fixes += file_fixes;
            files_modified++;

            std::string new_content;
            for (const auto& line_str : lines) {
                if (line_str == "__LYMAR_REMOVED_LINE__") continue;
                new_content += line_str + "\n";
            }

            if (!opts.dry_run) {
                std::ofstream out(file);
                if (out.is_open()) {
                    out << new_content;
                }
                std::cout << green << "Fixed " << file_fixes << " issue" << (file_fixes == 1 ? "" : "s")
                          << " in " << file << reset << "\n";
            } else {
                std::cout << yellow << "[dry-run] Would fix " << file_fixes << " issue" << (file_fixes == 1 ? "" : "s")
                          << " in " << file << reset << "\n";
            }
        }
    }

    if (total_fixes == 0) {
        std::cout << green << "✨ No fixable lint issues found." << reset << "\n";
    } else {
        std::cout << (opts.dry_run ? yellow : green) << bold
                  << (opts.dry_run ? "ℹ " : "✨ ")
                  << (opts.dry_run ? "Would fix " : "Fixed ") << total_fixes << " issue" << (total_fixes == 1 ? "" : "s")
                  << " across " << files_modified << " file" << (files_modified == 1 ? "" : "s")
                  << (opts.dry_run ? ". Run 'lymar fix' to apply." : ".") << reset << "\n";
    }

    return 0;
}

} // namespace LM
