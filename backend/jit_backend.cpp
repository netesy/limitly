#include "jit_backend.hh"
#include <iostream>

JitBackend::JitBackend() {
    ctxt = gcc_jit_context_acquire();
    if (!ctxt) {
        // Handle error
        std::cerr << "Failed to acquire JIT context" << std::endl;
        return;
    }
    // Set up options if needed

    // Import printf for use in print statements
    gcc_jit_type* int_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT);
    gcc_jit_type* const_char_ptr_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_CONST_CHAR_PTR);
    gcc_jit_param* param_format = gcc_jit_context_new_param(ctxt, nullptr, const_char_ptr_type, "format");
    printf_func = gcc_jit_context_new_function(
        ctxt, nullptr,
        GCC_JIT_FUNCTION_IMPORTED,
        int_type,
        "printf",
        1, &param_format, 1); // is_variadic = true

    // Import strcmp for string comparisons
    gcc_jit_param* p1 = gcc_jit_context_new_param(ctxt, nullptr, const_char_ptr_type, "s1");
    gcc_jit_param* p2 = gcc_jit_context_new_param(ctxt, nullptr, const_char_ptr_type, "s2");
    gcc_jit_param* strcmp_params[] = {p1, p2};
    strcmp_func = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                              int_type, "strcmp", 2, strcmp_params, 0);

    // Import asprintf for string interpolation assignments
    gcc_jit_type* char_ptr_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_CHAR_PTR);
    gcc_jit_type* char_ptr_ptr_type = gcc_jit_type_get_pointer(char_ptr_type);
    gcc_jit_param* asprintf_p1 = gcc_jit_context_new_param(ctxt, nullptr, char_ptr_ptr_type, "strp");
    gcc_jit_param* asprintf_p2 = gcc_jit_context_new_param(ctxt, nullptr, const_char_ptr_type, "fmt");
    gcc_jit_param* asprintf_params[] = {asprintf_p1, asprintf_p2};
    asprintf_func = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                int_type, "asprintf", 2, asprintf_params, 1); // variadic

    // Import malloc for object instantiation
    gcc_jit_type* size_t_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_SIZE_T);
    gcc_jit_param* malloc_param = gcc_jit_context_new_param(ctxt, nullptr, size_t_type, "size");
    malloc_func = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                              gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID_PTR),
                                              "malloc", 1, &malloc_param, 0);

    // --- Import Concurrency C-API ---
    gcc_jit_type* void_ptr_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID_PTR);
    gcc_jit_type* size_t_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_SIZE_T);

    // scheduler_create() -> Scheduler*
    scheduler_create_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                       void_ptr_type, "scheduler_create", 0, nullptr, 0);

    // scheduler_destroy(Scheduler*)
    gcc_jit_param* p_sched_destroy = gcc_jit_context_new_param(ctxt, nullptr, void_ptr_type, "scheduler");
    scheduler_destroy_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                        gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID),
                                                        "scheduler_destroy", 1, &p_sched_destroy, 0);

    // scheduler_submit(Scheduler*, task_func_t)
    gcc_jit_type* task_func_type = gcc_jit_context_new_function_ptr_type(ctxt, nullptr, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID), 0, nullptr, 0);
    gcc_jit_param* p_sched_submit_1 = gcc_jit_context_new_param(ctxt, nullptr, void_ptr_type, "scheduler");
    gcc_jit_param* p_sched_submit_2 = gcc_jit_context_new_param(ctxt, nullptr, task_func_type, "task");
    gcc_jit_param* submit_params[] = {p_sched_submit_1, p_sched_submit_2};
    scheduler_submit_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                       gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID),
                                                       "scheduler_submit", 2, submit_params, 0);

    // scheduler_shutdown(Scheduler*)
    gcc_jit_param* p_sched_shutdown = gcc_jit_context_new_param(ctxt, nullptr, void_ptr_type, "scheduler");
    scheduler_shutdown_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                         gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID),
                                                         "scheduler_shutdown", 1, &p_sched_shutdown, 0);

    // thread_pool_create(size_t, Scheduler*) -> ThreadPool*
    gcc_jit_param* p_tp_create_1 = gcc_jit_context_new_param(ctxt, nullptr, size_t_type, "num_threads");
    gcc_jit_param* p_tp_create_2 = gcc_jit_context_new_param(ctxt, nullptr, void_ptr_type, "scheduler");
    gcc_jit_param* tp_create_params[] = {p_tp_create_1, p_tp_create_2};
    thread_pool_create_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                         void_ptr_type, "thread_pool_create", 2, tp_create_params, 0);

    // thread_pool_destroy(ThreadPool*)
    gcc_jit_param* p_tp_destroy = gcc_jit_context_new_param(ctxt, nullptr, void_ptr_type, "pool");
    thread_pool_destroy_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                          gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID),
                                                          "thread_pool_destroy", 1, &p_tp_destroy, 0);

    // thread_pool_start(ThreadPool*)
    gcc_jit_param* p_tp_start = gcc_jit_context_new_param(ctxt, nullptr, void_ptr_type, "pool");
    thread_pool_start_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                        gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID),
                                                        "thread_pool_start", 1, &p_tp_start, 0);

    // thread_pool_stop(ThreadPool*)
    gcc_jit_param* p_tp_stop = gcc_jit_context_new_param(ctxt, nullptr, void_ptr_type, "pool");
    thread_pool_stop_func_ = gcc_jit_context_new_function(ctxt, nullptr, GCC_JIT_FUNCTION_IMPORTED,
                                                       gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID),
                                                       "thread_pool_stop", 1, &p_tp_stop, 0);
}

JitBackend::~JitBackend() {
    if (ctxt) {
        gcc_jit_context_release(ctxt);
    }
}

void JitBackend::process(const std::shared_ptr<AST::Program>& program) {
    // Create a main function for the top-level code
    gcc_jit_function* main_func = gcc_jit_context_new_function(
        ctxt,
        nullptr,
        GCC_JIT_FUNCTION_EXPORTED,
        gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT),
        "main",
        0,
        nullptr,
        0
    );

    gcc_jit_block* block = gcc_jit_function_new_block(main_func, "initial");

    for (const auto& stmt : program->statements) {
        if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            visitFunctionDeclaration(funcDecl);
        } else {
            block = visitStatement(stmt, main_func, block);
        }
    }

    gcc_jit_rvalue* zero = gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT), 0);
    gcc_jit_block_end_with_return(block, nullptr, zero);
}

void JitBackend::compile(const char* output_filename) {
    if (!ctxt) return;
    gcc_jit_context_compile_to_file(ctxt, GCC_JIT_OUTPUT_KIND_EXECUTABLE, output_filename);
}

#include <type_traits>

gcc_jit_type* JitBackend::to_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type) {
    if (!type) {
        return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID);
    }
    if (type->typeName == "int") {
        return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT);
    } else if (type->typeName == "float") {
        return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_DOUBLE);
    } else if (type->typeName == "bool") {
        return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_BOOL);
    } else if (type->typeName == "str") {
        return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_CONST_CHAR_PTR);
    }

    // Check for user-defined class types
    auto it = class_structs.find(type->typeName);
    if (it != class_structs.end()) {
        return gcc_jit_type_get_pointer(it->second);
    }

    // Add other type conversions here
    return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID_PTR);
}

void JitBackend::visitFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    std::cout << "Visiting function: " << stmt->name << std::endl;
    std::vector<gcc_jit_param*> params;
    for (const auto& p : stmt->params) {
        params.push_back(gcc_jit_context_new_param(ctxt, nullptr, to_jit_type(p.second), p.first.c_str()));
    }

    gcc_jit_function* func = gcc_jit_context_new_function(
        ctxt,
        nullptr,
        GCC_JIT_FUNCTION_EXPORTED,
        to_jit_type(stmt->returnType.value_or(nullptr)),
        stmt->name.c_str(),
        params.size(),
        params.data(),
        0
    );

    // Store the function so it can be called (needed for recursion)
    functions[stmt->name] = func;

    // --- Create a new scope for the function ---
    auto variables_backup = variables;
    variables.clear();

    // Add parameters to the new scope
    for (size_t i = 0; i < stmt->params.size(); ++i) {
        const auto& param_decl = stmt->params[i];
        const std::string& param_name = param_decl.first;
        gcc_jit_param* jit_param = gcc_jit_function_get_param(func, i);
        variables[param_name] = gcc_jit_param_as_lvalue(jit_param);
    }

    gcc_jit_block* block = gcc_jit_function_new_block(func, "initial");

    for (const auto& s : stmt->body->statements) {
        block = visitStatement(s, func, block);
        if (!block) break; // Stop if a return statement was encountered
    }

    // Add an implicit void return if the function doesn't end with one
    if (block) {
         gcc_jit_block_end_with_void_return(block, nullptr);
    }

    // --- Restore the previous scope ---
    variables = variables_backup;
}

// Other visitor implementations will go here

gcc_jit_rvalue* JitBackend::visitExpression(const std::shared_ptr<AST::Expression>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        return visitBinaryExpr(binaryExpr, func, block);
    } else if (auto unaryExpr = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        return visitUnaryExpr(unaryExpr, func, block);
    } else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        return visitLiteralExpr(literalExpr, func, block);
    } else if (auto variableExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        return visitVariableExpr(variableExpr, func, block);
    } else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        return visitCallExpr(callExpr, func, block);
    } else if (auto assignExpr = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
        return visitAssignExpr(assignExpr, func, block);
    } else if (auto groupingExpr = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        return visitGroupingExpr(groupingExpr, func, block);
    } else if (auto rangeExpr = std::dynamic_pointer_cast<AST::RangeExpr>(expr)) {
        return visitRangeExpr(rangeExpr, func, block);
    } else if (auto interpStrExpr = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(expr)) {
        return visitInterpolatedStringExpr(interpStrExpr, func, block);
    } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        return visitMemberExpr(memberExpr, func, block);
    } else if (auto thisExpr = std::dynamic_pointer_cast<AST::ThisExpr>(expr)) {
        return visitThisExpr(thisExpr, func, block);
    }
    std::cerr << "Unsupported expression type" << std::endl;
    return nullptr;
}

gcc_jit_block* JitBackend::visitStatement(const std::shared_ptr<AST::Statement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    std::cout << "Visiting statement, line: " << stmt->line << std::endl;
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        return visitVarDeclaration(varDecl, func, block);
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        return visitExprStatement(exprStmt, func, block);
    } else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        return visitPrintStatement(printStmt, func, block);
    } else if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        return visitBlockStatement(blockStmt, func, block);
    } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        return visitIfStatement(ifStmt, func, block);
    } else if (auto iterStmt = std::dynamic_pointer_cast<AST::IterStatement>(stmt)) {
        return visitIterStatement(iterStmt, func, block);
    } else if (auto whileStmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        return visitWhileStatement(whileStmt, func, block);
    }
    // Add other statement visitors here
    if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) {
        return visitClassDeclaration(classDecl, func, block);
    }
    if (auto parallelStmt = std::dynamic_pointer_cast<AST::ParallelStatement>(stmt)) {
        return visitParallelStatement(parallelStmt, func, block);
    }
    if (auto concurrentStmt = std::dynamic_pointer_cast<AST::ConcurrentStatement>(stmt)) {
        return visitConcurrentStatement(concurrentStmt, func, block);
    }
    return block;
}

void JitBackend::print_rvalue(gcc_jit_rvalue* rval, gcc_jit_block* block, bool with_newline) {
    gcc_jit_type* rval_type = gcc_jit_rvalue_get_type(rval);
    gcc_jit_type* int_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT);
    gcc_jit_type* double_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_DOUBLE);
    gcc_jit_type* bool_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_BOOL);
    gcc_jit_type* string_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_CONST_CHAR_PTR);

    const char* format_str_cstr;
    int num_args = 2;

    if (rval_type == int_type || rval_type == bool_type) {
        format_str_cstr = with_newline ? "%d\n" : "%d";
    } else if (rval_type == double_type) {
        format_str_cstr = with_newline ? "%f\n" : "%f";
    } else if (rval_type == string_type) {
        format_str_cstr = with_newline ? "%s\n" : "%s";
    } else {
        format_str_cstr = with_newline ? "nil\n" : "nil";
        num_args = 1;
    }

    gcc_jit_rvalue* format_rval = gcc_jit_context_new_string_literal(ctxt, format_str_cstr);

    if (num_args == 1) {
        gcc_jit_rvalue* call_args[] = { format_rval };
        gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, printf_func, 1, call_args));
    } else {
        gcc_jit_rvalue* r_val_promoted = gcc_jit_context_new_cast(ctxt, nullptr, rval, double_type);
        gcc_jit_rvalue* call_args[] = { format_rval, (rval_type == double_type) ? r_val_promoted : rval };
        gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, printf_func, 2, call_args));
    }
}

gcc_jit_block* JitBackend::visitPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    for (const auto& arg : stmt->arguments) {
        if (auto interpolated = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(arg)) {
            // Handle interpolated string by printing each part
            for (const auto& part : interpolated->parts) {
                std::visit(
                    [&](auto&& p) {
                        using T = std::decay_t<decltype(p)>;
                        if constexpr (std::is_same_v<T, std::string>) {
                            // It's a literal string part
                            gcc_jit_rvalue* format = gcc_jit_context_new_string_literal(ctxt, "%s");
                            gcc_jit_rvalue* str_val = gcc_jit_context_new_string_literal(ctxt, p.c_str());
                            gcc_jit_rvalue* args[] = { format, str_val };
                            gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, printf_func, 2, args));
                        } else {
                            // It's an expression part
                            gcc_jit_rvalue* rval = visitExpression(p, func, block);
                            print_rvalue(rval, block, false); // false = no newline
                        }
                    },
                    part);
            }
            // Print the final newline for the whole statement
            gcc_jit_rvalue* nl_format = gcc_jit_context_new_string_literal(ctxt, "\n");
            gcc_jit_rvalue* nl_args[] = { nl_format };
            gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, printf_func, 1, nl_args));
        } else {
            // It's a simple print(expression)
            gcc_jit_rvalue* rval = visitExpression(arg, func, block);
            print_rvalue(rval, block, true); // true = with newline
        }
    }
    return block;
}

// Expression visitors
gcc_jit_rvalue* JitBackend::visitBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    gcc_jit_rvalue* lhs = visitExpression(expr->left, func, block);
    gcc_jit_rvalue* rhs = visitExpression(expr->right, func, block);

    // TODO: Handle type promotion (e.g., int + float)
    gcc_jit_type* result_type = gcc_jit_rvalue_get_type(lhs);

    switch (expr->op) {
        // Arithmetic
        case TokenType::PLUS:
            return gcc_jit_context_new_binary_op(ctxt, nullptr, GCC_JIT_BINARY_OP_PLUS, result_type, lhs, rhs);
        case TokenType::MINUS:
            return gcc_jit_context_new_binary_op(ctxt, nullptr, GCC_JIT_BINARY_OP_MINUS, result_type, lhs, rhs);
        case TokenType::STAR:
            return gcc_jit_context_new_binary_op(ctxt, nullptr, GCC_JIT_BINARY_OP_MULT, result_type, lhs, rhs);
        case TokenType::SLASH:
            return gcc_jit_context_new_binary_op(ctxt, nullptr, GCC_JIT_BINARY_OP_DIVIDE, result_type, lhs, rhs);
        case TokenType::MODULUS:
            if (gcc_jit_type_get_kind(result_type) == GCC_JIT_TYPE_KIND_INT) {
                return gcc_jit_context_new_binary_op(ctxt, nullptr, GCC_JIT_BINARY_OP_MODULO, result_type, lhs, rhs);
            } else {
                std::cerr << "Unsupported operand types for % (modulo)" << std::endl;
                return nullptr;
            }

        // Comparisons
        case TokenType::GREATER:
            return gcc_jit_context_new_comparison(ctxt, nullptr, GCC_JIT_COMPARISON_GT, lhs, rhs);
        case TokenType::GREATER_EQUAL:
            return gcc_jit_context_new_comparison(ctxt, nullptr, GCC_JIT_COMPARISON_GE, lhs, rhs);
        case TokenType::LESS:
            return gcc_jit_context_new_comparison(ctxt, nullptr, GCC_JIT_COMPARISON_LT, lhs, rhs);
        case TokenType::LESS_EQUAL:
            return gcc_jit_context_new_comparison(ctxt, nullptr, GCC_JIT_COMPARISON_LE, lhs, rhs);
        case TokenType::EQUAL_EQUAL:
        case TokenType::BANG_EQUAL: {
            gcc_jit_type* lhs_type = gcc_jit_rvalue_get_type(lhs);
            if (lhs_type == gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_CONST_CHAR_PTR)) {
                // String comparison using strcmp
                gcc_jit_rvalue* call_args[] = {lhs, rhs};
                gcc_jit_rvalue* strcmp_result = gcc_jit_context_new_call(ctxt, nullptr, strcmp_func, 2, call_args);
                gcc_jit_rvalue* zero = gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_rvalue_get_type(strcmp_result), 0);
                gcc_jit_comparison op = (expr->op == TokenType::EQUAL_EQUAL) ? GCC_JIT_COMPARISON_EQ : GCC_JIT_COMPARISON_NE;
                return gcc_jit_context_new_comparison(ctxt, nullptr, op, strcmp_result, zero);
            } else {
                // Numeric/pointer comparison
                gcc_jit_comparison op = (expr->op == TokenType::EQUAL_EQUAL) ? GCC_JIT_COMPARISON_EQ : GCC_JIT_COMPARISON_NE;
                return gcc_jit_context_new_comparison(ctxt, nullptr, op, lhs, rhs);
            }
        }

        // Logical (with short-circuiting)
        case TokenType::AND:
             return gcc_jit_context_new_logical_op(ctxt, nullptr, GCC_JIT_LOGICAL_OP_AND, lhs, rhs);
        case TokenType::OR:
             return gcc_jit_context_new_logical_op(ctxt, nullptr, GCC_JIT_LOGICAL_OP_OR, lhs, rhs);

        default:
            std::cerr << "Unsupported binary operator" << std::endl;
            return nullptr;
    }
}

gcc_jit_rvalue* JitBackend::visitUnaryExpr(const std::shared_ptr<AST::UnaryExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    gcc_jit_rvalue* rhs = visitExpression(expr->right, func, block);
    gcc_jit_type* rhs_type = gcc_jit_rvalue_get_type(rhs);

    switch (expr->op) {
        case TokenType::MINUS:
            return gcc_jit_context_new_unary_op(ctxt, nullptr, GCC_JIT_UNARY_OP_MINUS, rhs_type, rhs);
        case TokenType::BANG:
            return gcc_jit_context_new_unary_op(ctxt, nullptr, GCC_JIT_UNARY_OP_LOGICAL_NEGATE, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_BOOL), rhs);
        default:
            std::cerr << "Unsupported unary operator" << std::endl;
            return nullptr;
    }
}

gcc_jit_rvalue* JitBackend::visitLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    return std::visit([this](auto&& arg) -> gcc_jit_rvalue* {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            return gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT), arg);
        } else if constexpr (std::is_same_v<T, double>) {
            return gcc_jit_context_new_rvalue_from_double(ctxt, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_DOUBLE), arg);
        } else if constexpr (std::is_same_v<T, bool>) {
            return gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_BOOL), arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return gcc_jit_context_new_string_literal(ctxt, arg.c_str());
        } else if constexpr (std::is_same_v<T, std::nullptr_t>) {
            gcc_jit_type* void_ptr_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID_PTR);
            return gcc_jit_context_null(ctxt, void_ptr_type);
        }
        return nullptr;
    }, expr->value);
}

gcc_jit_rvalue* JitBackend::visitVariableExpr(const std::shared_ptr<AST::VariableExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    auto it = variables.find(expr->name);
    if (it == variables.end()) {
        std::cerr << "Unknown variable referenced: " << expr->name << std::endl;
        return nullptr;
    }
    return gcc_jit_lvalue_as_rvalue(it->second);
}

gcc_jit_rvalue* JitBackend::visitCallExpr(const std::shared_ptr<AST::CallExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    // Case 1: Method call, e.g., obj.method()
    if (auto member_expr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->callee)) {
        gcc_jit_rvalue* obj_ptr = visitExpression(member_expr->object, func, block);
        gcc_jit_type* struct_ptr_type = gcc_jit_rvalue_get_type(obj_ptr);
        gcc_jit_type* struct_type = gcc_jit_type_get_pointed_to(struct_ptr_type);
        std::string class_name = gcc_jit_type_get_name(struct_type);
        std::string method_name = member_expr->name;
        std::string mangled_name = class_name + "_" + method_name;

        auto it = functions.find(mangled_name);
        if (it == functions.end()) {
            std::cerr << "JIT Error: Call to unknown method " << method_name << " for class " << class_name << std::endl;
            return nullptr;
        }
        gcc_jit_function* target_func = it->second;

        std::vector<gcc_jit_rvalue*> args;
        args.push_back(obj_ptr); // Add 'self' as the first argument
        for (const auto& arg_expr : expr->arguments) {
            args.push_back(visitExpression(arg_expr, func, block));
        }

        return gcc_jit_context_new_call(ctxt, nullptr, target_func, args.size(), args.data());
    }

    // Case 2: Regular function call or constructor call
    if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        const std::string& name = var_expr->name;

        // Is it a constructor call?
        if (class_structs.count(name)) {
            std::string constructor_name = name + "_constructor";
            auto it = functions.find(constructor_name);
            if (it == functions.end()) {
                std::cerr << "JIT Error: Could not find constructor for class " << name << std::endl;
                return nullptr;
            }
            gcc_jit_function* constructor_func = it->second;
            std::vector<gcc_jit_rvalue*> args;
            for (const auto& arg_expr : expr->arguments) {
                args.push_back(visitExpression(arg_expr, func, block));
            }
            return gcc_jit_context_new_call(ctxt, nullptr, constructor_func, args.size(), args.data());
        }

        // Is it a regular function call?
        auto it = functions.find(name);
        if (it != functions.end()) {
            gcc_jit_function* target_func = it->second;
            std::vector<gcc_jit_rvalue*> args;
            for (const auto& arg_expr : expr->arguments) {
                args.push_back(visitExpression(arg_expr, func, block));
            }
            return gcc_jit_context_new_call(ctxt, nullptr, target_func, args.size(), args.data());
        }

        std::cerr << "JIT Error: Call to unknown function or class " << name << std::endl;
        return nullptr;
    }

    std::cerr << "JIT Error: Complex callees not yet supported." << std::endl;
    return nullptr;
}

gcc_jit_rvalue* JitBackend::visitAssignExpr(const std::shared_ptr<AST::AssignExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    // Handle member assignment: obj.field = value
    if (expr->object) {
        auto member_expr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->object);
        if (!member_expr) {
            std::cerr << "JIT Error: Invalid target for assignment." << std::endl;
            return nullptr;
        }

        gcc_jit_rvalue* obj_ptr = visitExpression(member_expr->object, func, block);
        gcc_jit_type* struct_ptr_type = gcc_jit_rvalue_get_type(obj_ptr);
        gcc_jit_type* struct_type = gcc_jit_type_get_pointed_to(struct_ptr_type);
        const char* type_name = gcc_jit_type_get_name(struct_type);

        auto it = class_fields.find(type_name);
        if (it == class_fields.end()) {
             std::cerr << "JIT Error: Not a class type or class has no fields: " << type_name << std::endl;
             return nullptr;
        }

        gcc_jit_field* field = nullptr;
        for (auto f : it->second) {
            if (gcc_jit_field_get_name(f) == member_expr->name) {
                field = f;
                break;
            }
        }

        if (!field) {
            std::cerr << "JIT Error: No such field '" << member_expr->name << "' in class " << type_name << std::endl;
            return nullptr;
        }

        gcc_jit_lvalue* field_lval = gcc_jit_rvalue_access_field(obj_ptr, nullptr, field);
        gcc_jit_rvalue* rhs_val = visitExpression(expr->value, func, block);
        gcc_jit_block_add_assignment(block, nullptr, field_lval, rhs_val);
        return rhs_val;

    } else { // Handle simple variable assignment: var = value
        auto it = variables.find(expr->name);
        if (it == variables.end()) {
            std::cerr << "Attempted to assign to unknown variable: " << expr->name << std::endl;
            return nullptr;
        }
        gcc_jit_lvalue* lval = it->second;
        gcc_jit_rvalue* rval = visitExpression(expr->value, func, block);

        // TODO: Check for type compatibility before assignment
        gcc_jit_block_add_assignment(block, nullptr, lval, rval);
        return rval; // Assignment expression evaluates to the assigned value
    }
}

// Statement visitors (stubs for now)
gcc_jit_block* JitBackend::visitVarDeclaration(const std::shared_ptr<AST::VarDeclaration>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    // TODO: Check for redeclaration in the same scope
    gcc_jit_rvalue* init_val = visitExpression(stmt->initializer, func, block);
    if (!init_val) {
        std::cerr << "Invalid initializer for variable " << stmt->name << std::endl;
        return block;
    }

    gcc_jit_type* var_type;
    if (stmt->type.has_value()) {
        var_type = to_jit_type(stmt->type.value());
    } else {
        var_type = gcc_jit_rvalue_get_type(init_val);
    }

    gcc_jit_lvalue* local_var = gcc_jit_function_new_local(func, nullptr, var_type, stmt->name.c_str());
    variables[stmt->name] = local_var;
    gcc_jit_block_add_assignment(block, nullptr, local_var, init_val);
    return block;
}

gcc_jit_block* JitBackend::visitBlockStatement(const std::shared_ptr<AST::BlockStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    auto variables_backup = variables;
    for (const auto& s : stmt->statements) {
        block = visitStatement(s, func, block);
    }
    variables = variables_backup;
    return block;
}

gcc_jit_block* JitBackend::visitIfStatement(const std::shared_ptr<AST::IfStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    gcc_jit_rvalue* cond_val = visitExpression(stmt->condition, func, block);

    gcc_jit_block* then_block = gcc_jit_function_new_block(func, "then_branch");
    gcc_jit_block* after_block = gcc_jit_function_new_block(func, "after_if");
    gcc_jit_block* else_block = stmt->elseBranch ? gcc_jit_function_new_block(func, "else_branch") : after_block;

    gcc_jit_block_end_with_conditional(block, nullptr, cond_val, then_block, else_block);

    // Then branch
    gcc_jit_block* then_block_after = visitStatement(stmt->thenBranch, func, then_block);
    if (then_block_after) { // The block might be terminated by a return
        gcc_jit_block_end_with_jump(then_block_after, nullptr, after_block);
    }

    // Else branch
    if (stmt->elseBranch) {
        gcc_jit_block* else_block_after = visitStatement(stmt->elseBranch, func, else_block);
        if (else_block_after) {
            gcc_jit_block_end_with_jump(else_block_after, nullptr, after_block);
        }
    }

    return after_block;
}

gcc_jit_block* JitBackend::visitWhileStatement(const std::shared_ptr<AST::WhileStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    gcc_jit_block* cond_block = gcc_jit_function_new_block(func, "while_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(func, "while_body");
    gcc_jit_block* after_block = gcc_jit_function_new_block(func, "after_while");

    loop_contexts.push_back({cond_block, after_block});

    gcc_jit_block_end_with_jump(block, nullptr, cond_block);

    // Condition block
    gcc_jit_rvalue* cond_val = visitExpression(stmt->condition, func, cond_block);
    gcc_jit_block_end_with_conditional(cond_block, nullptr, cond_val, body_block, after_block);

    // Body block
    gcc_jit_block* body_after_block = visitStatement(stmt->body, func, body_block);
    if (body_after_block) {
        gcc_jit_block_end_with_jump(body_after_block, nullptr, cond_block);
    }

    loop_contexts.pop_back();
    return after_block;
}

gcc_jit_block* JitBackend::visitForStatement(const std::shared_ptr<AST::ForStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    // For now, only handling C-style loops, not iterables.
    if (stmt->isIterableLoop) {
        std::cerr << "JIT Error: Iterable for loops not yet supported." << std::endl;
        return block;
    }

    // New scope for the loop variable
    auto variables_backup = variables;

    // Initializer
    if (stmt->initializer) {
        block = visitStatement(stmt->initializer, func, block);
    }

    gcc_jit_block* cond_block = gcc_jit_function_new_block(func, "for_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(func, "for_body");
    gcc_jit_block* increment_block = gcc_jit_function_new_block(func, "for_increment");
    gcc_jit_block* after_block = gcc_jit_function_new_block(func, "after_for");

    loop_contexts.push_back({increment_block, after_block});

    gcc_jit_block_end_with_jump(block, nullptr, cond_block);

    // Condition block
    if (stmt->condition) {
        gcc_jit_rvalue* cond_val = visitExpression(stmt->condition, func, cond_block);
        gcc_jit_block_end_with_conditional(cond_block, nullptr, cond_val, body_block, after_block);
    } else {
        // No condition means an infinite loop
        gcc_jit_block_end_with_jump(cond_block, nullptr, body_block);
    }

    // Body block
    gcc_jit_block* body_after_block = visitStatement(stmt->body, func, body_block);
    if (body_after_block) {
        gcc_jit_block_end_with_jump(body_after_block, nullptr, increment_block);
    }

    // Increment block
    if (stmt->increment) {
        visitExpression(stmt->increment, func, increment_block);
    }
    gcc_jit_block_end_with_jump(increment_block, nullptr, cond_block);

    loop_contexts.pop_back();
    variables = variables_backup;
    return after_block;
}
gcc_jit_block* JitBackend::visitReturnStatement(const std::shared_ptr<AST::ReturnStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    if (stmt->value) {
        gcc_jit_rvalue* rval = visitExpression(stmt->value, func, block);
        gcc_jit_block_end_with_return(block, nullptr, rval);
    } else {
        gcc_jit_block_end_with_void_return(block, nullptr);
    }
    return nullptr; // This block is terminated.
}
gcc_jit_block* JitBackend::visitExprStatement(const std::shared_ptr<AST::ExprStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    visitExpression(stmt->expression, func, block);
    return block;
}
gcc_jit_block* JitBackend::visitBreakStatement(const std::shared_ptr<AST::BreakStatement>& stmt, gcc_jit_block* block) {
    if (loop_contexts.empty()) {
        std::cerr << "JIT Error: 'break' statement outside of a loop." << std::endl;
        return block; // Or handle as a compile-time error
    }
    gcc_jit_block* break_target = loop_contexts.back().second;
    gcc_jit_block_end_with_jump(block, nullptr, break_target);
    return nullptr; // This block is terminated
}

gcc_jit_block* JitBackend::visitIterStatement(const std::shared_ptr<AST::IterStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    auto range_expr = std::dynamic_pointer_cast<AST::RangeExpr>(stmt->iterable);
    if (!range_expr) {
        std::cerr << "JIT Error: iter loops currently only support range expressions." << std::endl;
        return block;
    }

    auto variables_backup = variables;

    // Evaluate range limits
    gcc_jit_rvalue* start_val = visitExpression(range_expr->start, func, block);
    gcc_jit_rvalue* end_val = visitExpression(range_expr->end, func, block);
    gcc_jit_rvalue* step_val;
    if (range_expr->step) {
        step_val = visitExpression(range_expr->step, func, block);
    } else {
        step_val = gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_rvalue_get_type(start_val), 1);
    }

    // Create loop variable
    const std::string& var_name = stmt->loopVars[0];
    gcc_jit_type* var_type = gcc_jit_rvalue_get_type(start_val);
    gcc_jit_lvalue* loop_var = gcc_jit_function_new_local(func, nullptr, var_type, var_name.c_str());
    variables[var_name] = loop_var;
    gcc_jit_block_add_assignment(block, nullptr, loop_var, start_val);

    // Create blocks
    gcc_jit_block* cond_block = gcc_jit_function_new_block(func, "iter_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(func, "iter_body");
    gcc_jit_block* increment_block = gcc_jit_function_new_block(func, "iter_increment");
    gcc_jit_block* after_block = gcc_jit_function_new_block(func, "after_iter");

    loop_contexts.push_back({increment_block, after_block});
    gcc_jit_block_end_with_jump(block, nullptr, cond_block);

    // Condition
    gcc_jit_rvalue* current_val = gcc_jit_lvalue_as_rvalue(loop_var);
    gcc_jit_comparison op = range_expr->inclusive ? GCC_JIT_COMPARISON_LE : GCC_JIT_COMPARISON_LT;
    gcc_jit_rvalue* cond_val = gcc_jit_context_new_comparison(ctxt, nullptr, op, current_val, end_val);
    gcc_jit_block_end_with_conditional(cond_block, nullptr, cond_val, body_block, after_block);

    // Body
    gcc_jit_block* body_after = visitStatement(stmt->body, func, body_block);
    if (body_after) {
        gcc_jit_block_end_with_jump(body_after, nullptr, increment_block);
    }

    // Increment
    current_val = gcc_jit_lvalue_as_rvalue(loop_var);
    gcc_jit_rvalue* next_val = gcc_jit_context_new_binary_op(ctxt, nullptr, GCC_JIT_BINARY_OP_PLUS, var_type, current_val, step_val);
    gcc_jit_block_add_assignment(increment_block, nullptr, loop_var, next_val);
    gcc_jit_block_end_with_jump(increment_block, nullptr, cond_block);

    loop_contexts.pop_back();
    variables = variables_backup;
    return after_block;
}

gcc_jit_block* JitBackend::visitContinueStatement(const std::shared_ptr<AST::ContinueStatement>& stmt, gcc_jit_block* block) {
    if (loop_contexts.empty()) {
        std::cerr << "JIT Error: 'continue' statement outside of a loop." << std::endl;
        return block; // Or handle as a compile-time error
    }
    gcc_jit_block* continue_target = loop_contexts.back().first;
    gcc_jit_block_end_with_jump(block, nullptr, continue_target);
    return nullptr; // This block is terminated
}

gcc_jit_rvalue* JitBackend::visitGroupingExpr(const std::shared_ptr<AST::GroupingExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    return visitExpression(expr->expression, func, block);
}

gcc_jit_rvalue* JitBackend::visitInterpolatedStringExpr(const std::shared_ptr<AST::InterpolatedStringExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    std::string format_str;
    std::vector<gcc_jit_rvalue*> args;

    // Build the format string and the argument list
    for (const auto& part : expr->parts) {
        std::visit(
            [&](auto&& p) {
                using T = std::decay_t<decltype(p)>;
                if constexpr (std::is_same_v<T, std::string>) {
                    format_str += p;
                } else {
                    gcc_jit_rvalue* rval = visitExpression(p, func, block);
                    gcc_jit_type* rval_type = gcc_jit_rvalue_get_type(rval);
                    if (gcc_jit_type_get_kind(rval_type) == GCC_JIT_TYPE_KIND_INT || gcc_jit_type_get_kind(rval_type) == GCC_JIT_TYPE_KIND_BOOL) {
                        format_str += "%d";
                    } else if (gcc_jit_type_get_kind(rval_type) == GCC_JIT_TYPE_KIND_DOUBLE) {
                        format_str += "%f";
                    } else { // const char* and other pointers
                        format_str += "%s";
                    }
                    args.push_back(rval);
                }
            },
            part);
    }

    // Create a local variable to hold the result of asprintf
    gcc_jit_type* char_ptr_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_CHAR_PTR);
    gcc_jit_lvalue* result_str_lval = gcc_jit_function_new_local(func, nullptr, char_ptr_type, "interpolated_str");

    // Prepare arguments for asprintf
    std::vector<gcc_jit_rvalue*> asprintf_args;
    asprintf_args.push_back(gcc_jit_lvalue_get_address(result_str_lval, nullptr));
    asprintf_args.push_back(gcc_jit_context_new_string_literal(ctxt, format_str.c_str()));
    asprintf_args.insert(asprintf_args.end(), args.begin(), args.end());

    // Call asprintf
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, asprintf_func, asprintf_args.size(), asprintf_args.data()));

    // Return the dynamically allocated string
    // NOTE: This memory is leaked! A proper implementation would need to track and free it.
    return gcc_jit_lvalue_as_rvalue(result_str_lval);
}

gcc_jit_block* JitBackend::visitClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    const std::string& class_name = stmt->name;

    // Create an opaque struct first to handle potential recursive references.
    gcc_jit_struct* class_struct = gcc_jit_context_new_opaque_struct(ctxt, nullptr, class_name.c_str());
    class_structs[class_name] = class_struct;

    std::vector<gcc_jit_field*> fields;
    for (const auto& field_decl : stmt->fields) {
        gcc_jit_type* field_type = to_jit_type(field_decl->type.value_or(nullptr));
        gcc_jit_field* field = gcc_jit_context_new_field(ctxt, nullptr, field_type, field_decl->name.c_str());
        fields.push_back(field);
    }

    // TODO: Handle inline constructor params as fields

    gcc_jit_struct_set_fields(class_struct, nullptr, fields.size(), fields.data());
    class_fields[class_name] = fields;

    // Visit methods
    for (const auto& method_decl : stmt->methods) {
        // Mangle name
        std::string mangled_name = class_name + "_" + method_decl->name;

        // Create a new function declaration with 'self' as the first param
        auto new_method_decl = std::make_shared<AST::FunctionDeclaration>(*method_decl);
        new_method_decl->name = mangled_name;

        auto self_type_annot = std::make_shared<AST::TypeAnnotation>();
        self_type_annot->typeName = class_name;
        self_type_annot->isUserDefined = true;

        new_method_decl->params.insert(new_method_decl->params.begin(), {"self", self_type_annot});

        visitFunctionDeclaration(new_method_decl);
    }

    // --- Create constructor ---
    std::string constructor_name = class_name + "_constructor";
    std::shared_ptr<AST::FunctionDeclaration> init_method = nullptr;
    for (const auto& method : stmt->methods) {
        if (method->name == "init") {
            init_method = method;
            break;
        }
    }

    std::vector<gcc_jit_param*> constructor_params;
    if (init_method) {
        for (const auto& p : init_method->params) {
            constructor_params.push_back(gcc_jit_context_new_param(ctxt, nullptr, to_jit_type(p.second), p.first.c_str()));
        }
    }

    gcc_jit_function* constructor = gcc_jit_context_new_function(
        ctxt, nullptr, GCC_JIT_FUNCTION_EXPORTED,
        gcc_jit_type_get_pointer(class_struct),
        constructor_name.c_str(), constructor_params.size(), constructor_params.data(), 0);
    functions[constructor_name] = constructor;

    gcc_jit_block* constructor_block = gcc_jit_function_new_block(constructor, "entry");

    // Malloc the object
    gcc_jit_rvalue* struct_size = gcc_jit_context_get_size_of(ctxt, class_struct);
    gcc_jit_rvalue* obj_ptr_void = gcc_jit_context_new_call(ctxt, nullptr, malloc_func, 1, &struct_size);
    gcc_jit_rvalue* obj_ptr = gcc_jit_context_new_cast(ctxt, nullptr, obj_ptr_void, gcc_jit_type_get_pointer(class_struct));

    // Call the init method
    if (init_method) {
        std::string init_mangled_name = class_name + "_init";
        auto it = functions.find(init_mangled_name);
        if (it != functions.end()) {
            gcc_jit_function* init_func = it->second;
            std::vector<gcc_jit_rvalue*> init_args;
            init_args.push_back(obj_ptr); // self
            for (size_t i = 0; i < constructor_params.size(); ++i) {
                init_args.push_back(gcc_jit_param_as_rvalue(gcc_jit_function_get_param(constructor, i)));
            }
            gcc_jit_block_add_eval(constructor_block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, init_func, init_args.size(), init_args.data()));
        }
    }

    gcc_jit_block_end_with_return(constructor_block, nullptr, obj_ptr);


    return block;
}

gcc_jit_rvalue* JitBackend::visitMemberExpr(const std::shared_ptr<AST::MemberExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    // For this step, we only handle field access. Method calls are handled by CallExpr.
    gcc_jit_rvalue* obj_ptr = visitExpression(expr->object, func, block);
    gcc_jit_type* struct_ptr_type = gcc_jit_rvalue_get_type(obj_ptr);
    gcc_jit_type* struct_type = gcc_jit_type_get_pointed_to(struct_ptr_type);
    const char* type_name = gcc_jit_type_get_name(struct_type);

    auto it = class_fields.find(type_name);
    if (it == class_fields.end()) {
         std::cerr << "JIT Error: Not a class type or class has no fields: " << type_name << std::endl;
         return nullptr;
    }

    gcc_jit_field* field = nullptr;
    for (auto f : it->second) {
        if (gcc_jit_field_get_name(f) == expr->name) {
            field = f;
            break;
        }
    }

    if (!field) {
        // This might be a method, which is fine. Return null and let CallExpr handle it.
        // A better approach would be to return a special value indicating a method.
        return nullptr;
    }

    return gcc_jit_rvalue_from_lvalue(gcc_jit_rvalue_access_field(obj_ptr, nullptr, field));
}

gcc_jit_rvalue* JitBackend::visitThisExpr(const std::shared_ptr<AST::ThisExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    // 'self' is an implicit parameter in methods. We'll look it up by name.
    auto it = variables.find("self");
    if (it == variables.end()) {
        std::cerr << "JIT Error: 'self' used outside of a method." << std::endl;
        return nullptr;
    }
    return gcc_jit_lvalue_as_rvalue(it->second);
}

gcc_jit_block* JitBackend::visitParallelStatement(const std::shared_ptr<AST::ParallelStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    std::cout << "JIT: Visiting ParallelStatement" << std::endl;

    // 1. Create the scheduler and thread pool
    gcc_jit_rvalue* scheduler = gcc_jit_context_new_call(ctxt, nullptr, scheduler_create_func_, 0, nullptr);

    // For now, hardcode the number of threads. In a real implementation, this would come from stmt->cores.
    gcc_jit_rvalue* num_threads = gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_SIZE_T), 4);
    gcc_jit_rvalue* tp_create_args[] = {num_threads, scheduler};
    gcc_jit_rvalue* pool = gcc_jit_context_new_call(ctxt, nullptr, thread_pool_create_func_, 2, tp_create_args);

    // 2. Start the pool
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, thread_pool_start_func_, 1, &pool));

    // 3. TODO: This is the hard part - generate and submit tasks.
    // For now, we visit the body, but this is incorrect as the body contains
    // special 'task' constructs that need to be compiled into separate functions.
    // This requires a much more complex visitor logic.
    block = visitStatement(stmt->body, func, block);


    // 4. Stop and destroy the runtime
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, thread_pool_stop_func_, 1, &pool));
    // In a real implementation with RAII, these destroy calls might not be necessary
    // if the C++ destructors handle cleanup. But the C-API exposes them, so we call them.
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, thread_pool_destroy_func_, 1, &pool));
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, scheduler_destroy_func_, 1, &scheduler));

    return block;
}

gcc_jit_block* JitBackend::visitConcurrentStatement(const std::shared_ptr<AST::ConcurrentStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    std::cout << "JIT: Visiting ConcurrentStatement (behaving like Parallel)" << std::endl;

    // TODO: This is a stub implementation. A real implementation would use the EventLoop
    // for I/O-bound tasks instead of just a general-purpose thread pool.
    // For now, it behaves identically to a 'parallel' block.

    // 1. Create the scheduler and thread pool
    gcc_jit_rvalue* scheduler = gcc_jit_context_new_call(ctxt, nullptr, scheduler_create_func_, 0, nullptr);

    // For now, hardcode the number of threads.
    gcc_jit_rvalue* num_threads = gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_SIZE_T), 4);
    gcc_jit_rvalue* tp_create_args[] = {num_threads, scheduler};
    gcc_jit_rvalue* pool = gcc_jit_context_new_call(ctxt, nullptr, thread_pool_create_func_, 2, tp_create_args);

    // 2. Start the pool
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, thread_pool_start_func_, 1, &pool));

    // 3. TODO: Generate and submit tasks
    block = visitStatement(stmt->body, func, block);

    // 4. Stop and destroy the runtime
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, thread_pool_stop_func_, 1, &pool));
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, thread_pool_destroy_func_, 1, &pool));
    gcc_jit_block_add_eval(block, nullptr, gcc_jit_context_new_call(ctxt, nullptr, scheduler_destroy_func_, 1, &scheduler));

    return block;
}

gcc_jit_rvalue* JitBackend::visitRangeExpr(const std::shared_ptr<AST::RangeExpr>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    std::cerr << "JIT Warning: Range expression used outside of an iter-loop. This has no effect." << std::endl;
    return nullptr;
}
