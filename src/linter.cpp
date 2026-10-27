#include "linter.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/ast.hh"
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
        if (std::isupper(c)) {
            if (i > 0 && s[i - 1] != '_') res += '_';
            res += static_cast<char>(std::tolower(c));
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
        collect_referenced_vars(var_decl->initializer, used);
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

        push_scope();

        // 1. First pass: record imports and declarations
        struct ImportInfo {
            std::string symbol_name;
            int line = 0;
        };
        std::vector<ImportInfo> imports;

        for (const auto& stmt : program->statements) {
            if (auto imp = std::dynamic_pointer_cast<Frontend::AST::ImportStatement>(stmt)) {
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
        for (const auto& stmt : program->statements) {
            collect_referenced_vars(stmt, all_referenced);
        }

        for (const auto& imp : imports) {
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

            if (!is_snake_case(func->name) && func->name != "init" && func->name != "deinit") {
                add_diag(func->line, 1, "naming-convention",
                         "Function '" + func->name + "' should be snake_case (e.g. '" + to_snake_case(func->name) + "')",
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
                if (type && format_type(type) == "any") {
                    add_diag(func->line, 1, "any-overuse",
                             "Parameter '" + param + "' uses dynamic 'any' type",
                             "prefer a concrete type (e.g. 'int', 'str') or trait contract to enable static safety");
                }
                VarMeta meta;
                meta.line = func->line;
                meta.is_list = (type && type->isList);
                scope_stack.back()[param] = meta;
            }

            if (func->returnType.has_value() && func->returnType.value() && format_type(func->returnType.value()) == "any") {
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

            for (const auto& m : trait->methods) {
                visit_statement(m);
            }
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

            if (var_decl->type.has_value() && var_decl->type.value() && format_type(var_decl->type.value()) == "any") {
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
    Frontend::Scanner scanner(source, filename);
    scanner.scanTokens();
    Frontend::Parser parser(scanner);
    auto program = parser.parse();

    LintVisitor visitor;
    visitor.filename = filename;
    visitor.visit_program(program);
    return visitor.diagnostics;
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
        if (arg == "--deny-warnings" || arg == "-Werror") {
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
        if (fs::exists("src")) opts.target_paths.push_back("src");
        if (fs::exists("tests")) opts.target_paths.push_back("tests");
    }

    std::vector<std::string> files_to_lint;
    for (const auto& path_str : opts.target_paths) {
        if (fs::is_regular_file(path_str)) {
            files_to_lint.push_back(path_str);
        } else if (fs::is_directory(path_str)) {
            for (const auto& entry : fs::recursive_directory_iterator(path_str)) {
                if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                    files_to_lint.push_back(entry.path().generic_string());
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

} // namespace LM
