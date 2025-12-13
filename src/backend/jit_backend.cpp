#include "jit_backend.hh"
#include <iostream>

JitBackend::JitBackend() {
    m_context = gcc_jit_context_acquire();
    if (!m_context) {
        throw std::runtime_error("Failed to acquire JIT context");
    }

    // Get types
    m_int_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_INT);
    m_const_char_ptr_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_CONST_CHAR_PTR);

    // Get printf
    m_printf_func = gcc_jit_context_get_builtin_function(m_context, "printf");
}

JitBackend::~JitBackend() {
    if (m_context) {
        gcc_jit_context_release(m_context);
    }
}

void JitBackend::process(const std::shared_ptr<AST::Program>& program) {
    // Create the main function
    gcc_jit_type* int_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_INT);
    m_main_func = gcc_jit_context_new_function(m_context, NULL, GCC_JIT_FUNCTION_EXPORTED, int_type, "main", 0, NULL, 0);
    m_current_block = gcc_jit_function_new_block(m_main_func, "entry");
    m_scopes.emplace_back();

    for (const auto& stmt : program->statements) {
        visit(stmt);
    }

    gcc_jit_block_end_with_return(m_current_block, NULL, gcc_jit_context_new_rvalue_from_int(m_context, int_type, 0));
}

void JitBackend::compile(const char* output_filename) {
    gcc_jit_context_compile_to_file(m_context, GCC_JIT_OUTPUT_KIND_EXECUTABLE, output_filename);
}

void JitBackend::visit(const std::shared_ptr<AST::Statement>& stmt) {
    if (auto s = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ForStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::BreakStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ContinueStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::IterStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::MatchStatement>(stmt)) return visit(s);
    throw std::runtime_error("Unsupported statement type for JIT");
}

void JitBackend::visit(const std::shared_ptr<AST::VarDeclaration>& stmt) {
    // For now, assume all variables are integers
    gcc_jit_type* type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_LONG_LONG);
    gcc_jit_lvalue* lvalue = gcc_jit_function_new_local(m_main_func, NULL, type, stmt->name.c_str());
    m_scopes.back()[stmt->name] = lvalue;
    if (stmt->initializer) {
        gcc_jit_rvalue* rvalue = visit_expr(stmt->initializer);
        gcc_jit_block_add_assignment(m_current_block, NULL, lvalue, rvalue);
    }
}

void JitBackend::visit(const std::shared_ptr<AST::ExprStatement>& stmt) {
    visit_expr(stmt->expression);
}

void JitBackend::visit(const std::shared_ptr<AST::ForStatement>& stmt) {
    if (stmt->isIterableLoop) {
        throw std::runtime_error("Iterable for loops are not yet supported by JIT");
    }

    m_scopes.emplace_back();

    if (stmt->initializer) {
        visit(stmt->initializer);
    }

    gcc_jit_block* cond_block = gcc_jit_function_new_block(m_main_func, "for_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(m_main_func, "for_body");
    gcc_jit_block* increment_block = gcc_jit_function_new_block(m_main_func, "for_increment");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_main_func, "after_for");

    m_loop_blocks.push_back({increment_block, after_block});

    gcc_jit_block_end_with_jump(m_current_block, NULL, cond_block);

    m_current_block = cond_block;
    if (stmt->condition) {
        gcc_jit_rvalue* condition = visit_expr(stmt->condition);
        gcc_jit_block_end_with_conditional(m_current_block, NULL, condition, body_block, after_block);
    } else {
        gcc_jit_block_end_with_jump(m_current_block, NULL, body_block);
    }

    m_current_block = body_block;
    visit(stmt->body);
    gcc_jit_block_end_with_jump(m_current_block, NULL, increment_block);

    m_current_block = increment_block;
    if (stmt->increment) {
        visit_expr(stmt->increment);
    }
    gcc_jit_block_end_with_jump(m_current_block, NULL, cond_block);

    m_current_block = after_block;
    m_scopes.pop_back();
    m_loop_blocks.pop_back();
}

void JitBackend::visit(const std::shared_ptr<AST::MatchStatement>& stmt) {
    gcc_jit_rvalue* value = visit_expr(stmt->value);
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_main_func, "after_match");
    std::vector<gcc_jit_block*> case_blocks;
    std::vector<gcc_jit_case*> cases;

    for (size_t i = 0; i < stmt->cases.size(); ++i) {
        case_blocks.push_back(gcc_jit_function_new_block(m_main_func, ("case_" + std::to_string(i)).c_str()));
    }

    for (size_t i = 0; i < stmt->cases.size(); ++i) {
        auto literal_expr = std::dynamic_pointer_cast<AST::LiteralExpr>(stmt->cases[i].pattern);
        if (!literal_expr) {
            throw std::runtime_error("JIT only supports literal patterns in match statements");
        }
        gcc_jit_rvalue* case_value = visit_expr(literal_expr);
        cases.push_back(gcc_jit_context_new_case(m_context, case_value, case_value, case_blocks[i]));
    }

    gcc_jit_block_end_with_switch(m_current_block, NULL, value, after_block, cases.size(), cases.data());

    for (size_t i = 0; i < stmt->cases.size(); ++i) {
        m_current_block = case_blocks[i];
        visit(stmt->cases[i].body);
        gcc_jit_block_end_with_jump(m_current_block, NULL, after_block);
    }

    m_current_block = after_block;
}

void JitBackend::visit(const std::shared_ptr<AST::WhileStatement>& stmt) {
    gcc_jit_block* cond_block = gcc_jit_function_new_block(m_main_func, "while_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(m_main_func, "while_body");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_main_func, "after_while");

    m_loop_blocks.push_back({cond_block, after_block});

    gcc_jit_block_end_with_jump(m_current_block, NULL, cond_block);

    m_current_block = cond_block;
    gcc_jit_rvalue* condition = visit_expr(stmt->condition);
    gcc_jit_block_end_with_conditional(m_current_block, NULL, condition, body_block, after_block);

    m_current_block = body_block;
    visit(stmt->body);
    gcc_jit_block_end_with_jump(m_current_block, NULL, cond_block);

    m_current_block = after_block;
    m_loop_blocks.pop_back();
}

void JitBackend::visit(const std::shared_ptr<AST::BlockStatement>& stmt) {
    m_scopes.emplace_back();
    for (const auto& s : stmt->statements) {
        visit(s);
    }
    m_scopes.pop_back();
}

void JitBackend::visit(const std::shared_ptr<AST::PrintStatement>& stmt) {
    for (const auto& arg : stmt->arguments) {
        gcc_jit_rvalue* rvalue = visit_expr(arg);
        gcc_jit_type* type = gcc_jit_rvalue_get_type(rvalue);
        const char* format_str;
        if (type == m_int_type) {
            format_str = "%d\n";
        } else if (type == m_const_char_ptr_type) {
            format_str = "%s\n";
        } else {
            throw std::runtime_error("Unsupported type for print");
        }
        gcc_jit_rvalue* format = gcc_jit_context_new_string_literal(m_context, format_str);
        gcc_jit_rvalue* args[] = {format, rvalue};
        gcc_jit_block_add_eval(m_current_block, NULL, gcc_jit_context_new_call(m_context, NULL, m_printf_func, 2, args));
    }
}

void JitBackend::visit(const std::shared_ptr<AST::IfStatement>& stmt) {
    gcc_jit_rvalue* condition = visit_expr(stmt->condition);
    gcc_jit_block* then_block = gcc_jit_function_new_block(m_main_func, "then");
    gcc_jit_block* else_block = gcc_jit_function_new_block(m_main_func, "else");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_main_func, "after");

    gcc_jit_block_end_with_conditional(m_current_block, NULL, condition, then_block, else_block);

    m_current_block = then_block;
    visit(stmt->thenBranch);
    gcc_jit_block_end_with_jump(m_current_block, NULL, after_block);

    m_current_block = else_block;
    if (stmt->elseBranch) {
        visit(stmt->elseBranch);
    }
    gcc_jit_block_end_with_jump(m_current_block, NULL, after_block);

    m_current_block = after_block;
}

void JitBackend::visit(const std::shared_ptr<AST::BreakStatement>& stmt) {
    if (m_loop_blocks.empty()) {
        throw std::runtime_error("Break statement outside of loop");
    }
    gcc_jit_block_end_with_jump(m_current_block, NULL, m_loop_blocks.back().second);
}

void JitBackend::visit(const std::shared_ptr<AST::ContinueStatement>& stmt) {
    if (m_loop_blocks.empty()) {
        throw std::runtime_error("Continue statement outside of loop");
    }
    gcc_jit_block_end_with_jump(m_current_block, NULL, m_loop_blocks.back().first);
}

void JitBackend::visit(const std::shared_ptr<AST::IterStatement>& stmt) {
    if (stmt->loopVars.size() != 1) {
        throw std::runtime_error("JIT only supports single variable iter loops");
    }

    auto range_expr = std::dynamic_pointer_cast<AST::RangeExpr>(stmt->iterable);
    if (!range_expr) {
        throw std::runtime_error("JIT only supports range-based iter loops");
    }

    m_scopes.emplace_back();

    // Initializer
    gcc_jit_lvalue* i = gcc_jit_function_new_local(m_main_func, NULL, m_int_type, stmt->loopVars[0].c_str());
    m_scopes.back()[stmt->loopVars[0]] = i;
    gcc_jit_rvalue* start = visit_expr(range_expr->start);
    gcc_jit_block_add_assignment(m_current_block, NULL, i, start);

    gcc_jit_block* cond_block = gcc_jit_function_new_block(m_main_func, "iter_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(m_main_func, "iter_body");
    gcc_jit_block* increment_block = gcc_jit_function_new_block(m_main_func, "iter_increment");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_main_func, "after_iter");

    m_loop_blocks.push_back({increment_block, after_block});

    gcc_jit_block_end_with_jump(m_current_block, NULL, cond_block);

    // Condition
    m_current_block = cond_block;
    gcc_jit_rvalue* end = visit_expr(range_expr->end);
    gcc_jit_rvalue* condition = gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_LT, gcc_jit_lvalue_as_rvalue(i), end);
    gcc_jit_block_end_with_conditional(m_current_block, NULL, condition, body_block, after_block);

    // Body
    m_current_block = body_block;
    visit(stmt->body);
    gcc_jit_block_end_with_jump(m_current_block, NULL, increment_block);

    // Increment
    m_current_block = increment_block;
    gcc_jit_rvalue* one = gcc_jit_context_new_rvalue_from_int(m_context, m_int_type, 1);
    gcc_jit_block_add_assignment_op(m_current_block, NULL, i, GCC_JIT_BINARY_OP_PLUS, one);
    gcc_jit_block_end_with_jump(m_current_block, NULL, cond_block);

    m_current_block = after_block;
    m_scopes.pop_back();
    m_loop_blocks.pop_back();
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::Expression>& expr) {
    if (auto e = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) return visit_expr(e);
    throw std::runtime_error("Unsupported expression type for JIT");
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    gcc_jit_rvalue* left = visit_expr(expr->left);
    gcc_jit_rvalue* right = visit_expr(expr->right);
    switch (expr->op) {
        case TokenType::PLUS:
            return gcc_jit_context_new_binary_op(m_context, NULL, GCC_JIT_BINARY_OP_PLUS, gcc_jit_rvalue_get_type(left), left, right);
        case TokenType::MINUS:
            return gcc_jit_context_new_binary_op(m_context, NULL, GCC_JIT_BINARY_OP_MINUS, gcc_jit_rvalue_get_type(left), left, right);
        case TokenType::STAR:
            return gcc_jit_context_new_binary_op(m_context, NULL, GCC_JIT_BINARY_OP_MULT, gcc_jit_rvalue_get_type(left), left, right);
        case TokenType::SLASH:
            return gcc_jit_context_new_binary_op(m_context, NULL, GCC_JIT_BINARY_OP_DIVIDE, gcc_jit_rvalue_get_type(left), left, right);
        case TokenType::EQUAL_EQUAL:
            return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_EQ, left, right);
        case TokenType::BANG_EQUAL:
            return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_NE, left, right);
        case TokenType::LESS:
            return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_LT, left, right);
        case TokenType::LESS_EQUAL:
            return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_LE, left, right);
        case TokenType::GREATER:
            return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_GT, left, right);
        case TokenType::GREATER_EQUAL:
            return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_GE, left, right);
        default:
            throw std::runtime_error("Unsupported binary operator for JIT");
    }
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::UnaryExpr>& expr) {
    gcc_jit_rvalue* right = visit_expr(expr->right);
    enum gcc_jit_unary_op op;
    switch (expr->op) {
        case TokenType::MINUS: op = GCC_JIT_UNARY_OP_MINUS; break;
        case TokenType::BANG: op = GCC_JIT_UNARY_OP_LOGICAL_NEGATE; break;
        default: throw std::runtime_error("Unsupported unary operator for JIT");
    }
    return gcc_jit_context_new_unary_op(m_context, NULL, op, gcc_jit_rvalue_get_type(right), right);
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::LiteralExpr>& expr) {
    if (std::holds_alternative<long long>(expr->value)) {
        gcc_jit_type* type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_LONG_LONG);
        return gcc_jit_context_new_rvalue_from_long(m_context, type, std::get<long long>(expr->value));
    }
    if (std::holds_alternative<bool>(expr->value)) {
        gcc_jit_type* type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_BOOL);
        return gcc_jit_context_new_rvalue_from_int(m_context, type, std::get<bool>(expr->value));
    }
    if (std::holds_alternative<std::string>(expr->value)) {
        return gcc_jit_context_new_string_literal(m_context, std::get<std::string>(expr->value).c_str());
    }
    // Add other literal types here
    return nullptr;
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::VariableExpr>& expr) {
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
        auto& scope = *it;
        if (scope.count(expr->name)) {
            return gcc_jit_lvalue_as_rvalue(scope[expr->name]);
        }
    }
    throw std::runtime_error("Unknown variable: " + expr->name);
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::AssignExpr>& expr) {
    gcc_jit_rvalue* rvalue = visit_expr(expr->value);
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
        auto& scope = *it;
        if (scope.count(expr->name)) {
            gcc_jit_block_add_assignment(m_current_block, NULL, scope[expr->name], rvalue);
            return rvalue;
        }
    }
    throw std::runtime_error("Unknown variable: " + expr->name);
}
