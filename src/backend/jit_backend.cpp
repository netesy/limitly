#include "jit_backend.hh"
#include <functional>
#include <iostream>

JitBackend::JitBackend() : m_region(m_mem_manager) {
    m_context = gcc_jit_context_acquire();
    if (!m_context) {
        throw std::runtime_error("Failed to acquire JIT context");
    }

    // Get types
    m_void_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_VOID);
    m_int_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_INT);
    m_double_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_DOUBLE);
    m_bool_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_BOOL);
    m_const_char_ptr_type = gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_CONST_CHAR_PTR);

    // Get printf
    m_printf_func = gcc_jit_context_get_builtin_function(m_context, "printf");

    // Get strcmp
    std::vector<gcc_jit_param*> strcmp_params;
    strcmp_params.push_back(gcc_jit_context_new_param(m_context, NULL, m_const_char_ptr_type, "s1"));
    strcmp_params.push_back(gcc_jit_context_new_param(m_context, NULL, m_const_char_ptr_type, "s2"));
    m_strcmp_func = gcc_jit_context_new_function(m_context, NULL, GCC_JIT_FUNCTION_IMPORTED, m_int_type, "strcmp", strcmp_params.size(), strcmp_params.data(), 0);

    // Get malloc
    std::vector<gcc_jit_param*> malloc_params;
    malloc_params.push_back(gcc_jit_context_new_param(m_context, NULL, gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_SIZE_T), "size"));
    m_malloc_func = gcc_jit_context_new_function(m_context, NULL, GCC_JIT_FUNCTION_IMPORTED, gcc_jit_type_get_pointer(m_void_type), "malloc", malloc_params.size(), malloc_params.data(), 0);
}

JitBackend::~JitBackend() {
    if (m_context) {
        gcc_jit_context_release(m_context);
    }
}

void JitBackend::process(const std::vector<std::shared_ptr<AST::Program>>& programs) {
    // First pass: Create forward declarations for all functions
    for (const auto& program : programs) {
        for (const auto& stmt : program->statements) {
            if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
                std::vector<gcc_jit_param*> params;
                for (const auto& p : func_decl->params) {
                    params.push_back(gcc_jit_context_new_param(m_context, NULL, get_jit_type(p.second), p.first.c_str()));
                }
                gcc_jit_type* return_type = get_jit_type(func_decl->returnType.value_or(nullptr));
                enum gcc_jit_function_kind kind = func_decl->visibility == AST::VisibilityLevel::Public ? GCC_JIT_FUNCTION_EXPORTED : GCC_JIT_FUNCTION_INTERNAL;
                std::string mangled_name = mangle(func_decl->name);
                gcc_jit_function* func = gcc_jit_context_new_function(m_context, NULL, kind, return_type, mangled_name.c_str(), params.size(), params.data(), 0);
                m_functions[mangled_name] = func;
            }
        }
    }

    // Create the main function
    m_main_func = gcc_jit_context_new_function(m_context, NULL, GCC_JIT_FUNCTION_EXPORTED, m_int_type, "main", 0, NULL, 0);
    m_current_func = m_main_func;
    m_current_block = gcc_jit_function_new_block(m_current_func, "entry");
    m_scopes.emplace_back();

    // Second pass: Generate code for all statements
    for (const auto& program : programs) {
        for (const auto& stmt : program->statements) {
            visit(stmt);
        }
    }

    gcc_jit_block_end_with_return(m_current_block, NULL, gcc_jit_context_new_rvalue_from_int(m_context, m_int_type, 0));
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
    if (auto s = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ParallelStatement>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ModuleDeclaration>(stmt)) return visit(s);
    if (auto s = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) return visit(s);
    throw std::runtime_error("Unsupported statement type for JIT");
}

void JitBackend::visit(const std::shared_ptr<AST::VarDeclaration>& stmt) {
    gcc_jit_type* type = get_jit_type(stmt->type.value_or(nullptr));
    if (m_scopes.size() == 1) { // Global variable
        enum gcc_jit_global_kind kind = stmt->visibility == AST::VisibilityLevel::Public ? GCC_JIT_GLOBAL_EXPORTED : GCC_JIT_GLOBAL_INTERNAL;
        std::string mangled_name = mangle(stmt->name);
        gcc_jit_lvalue* lvalue = gcc_jit_context_new_global(m_context, NULL, kind, type, mangled_name.c_str());
        m_scopes.back()[mangled_name] = lvalue;
        if (stmt->initializer) {
            gcc_jit_rvalue* rvalue = visit_expr(stmt->initializer);
            gcc_jit_global_set_initializer_rvalue(lvalue, rvalue);
        }
    } else { // Local variable
        gcc_jit_lvalue* lvalue = gcc_jit_function_new_local(m_current_func, NULL, type, stmt->name.c_str());
        m_scopes.back()[stmt->name] = lvalue;
        if (stmt->initializer) {
            gcc_jit_rvalue* rvalue = visit_expr(stmt->initializer);
            gcc_jit_block_add_assignment(m_current_block, NULL, lvalue, rvalue);
        }
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

    gcc_jit_block* cond_block = gcc_jit_function_new_block(m_current_func, "for_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(m_current_func, "for_body");
    gcc_jit_block* increment_block = gcc_jit_function_new_block(m_current_func, "for_increment");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_current_func, "after_for");

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

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::LambdaExpr>& expr) {
    // Analyze captured variables
    std::vector<std::string> captured_vars;
    std::function<void(const std::shared_ptr<AST::Node>&)> find_captures = 
        [&](const std::shared_ptr<AST::Node>& node) {
        if (!node) return;
        if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(node)) {
            bool is_param = false;
            for (const auto& p : expr->params) {
                if (p.first == var_expr->name) {
                    is_param = true;
                    break;
                }
            }
            if (!is_param) {
                bool is_local = false;
                for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
                    if (it->count(var_expr->name)) {
                        is_local = true;
                        break;
                    }
                }
                if (is_local) {
                    captured_vars.push_back(var_expr->name);
                }
            }
        }
        // Recurse
        if (auto block = std::dynamic_pointer_cast<AST::BlockStatement>(node)) {
            for (const auto& s : block->statements) find_captures(s);
        } else if (auto if_stmt = std::dynamic_pointer_cast<AST::IfStatement>(node)) {
            find_captures(if_stmt->condition);
            find_captures(if_stmt->thenBranch);
            find_captures(if_stmt->elseBranch);
        } else if (auto for_stmt = std::dynamic_pointer_cast<AST::ForStatement>(node)) {
            find_captures(for_stmt->initializer);
            find_captures(for_stmt->condition);
            find_captures(for_stmt->increment);
            find_captures(for_stmt->body);
        } else if (auto while_stmt = std::dynamic_pointer_cast<AST::WhileStatement>(node)) {
            find_captures(while_stmt->condition);
            find_captures(while_stmt->body);
        } else if (auto iter_stmt = std::dynamic_pointer_cast<AST::IterStatement>(node)) {
            find_captures(iter_stmt->iterable);
            find_captures(iter_stmt->body);
        } else if (auto match_stmt = std::dynamic_pointer_cast<AST::MatchStatement>(node)) {
            find_captures(match_stmt->value);
            for (const auto& c : match_stmt->cases) {
                find_captures(c.pattern);
                find_captures(c.body);
            }
        } else if (auto expr_stmt = std::dynamic_pointer_cast<AST::ExprStatement>(node)) {
            find_captures(expr_stmt->expression);
        } else if (auto binary_expr = std::dynamic_pointer_cast<AST::BinaryExpr>(node)) {
            find_captures(binary_expr->left);
            find_captures(binary_expr->right);
        }
    };
    find_captures(expr->body);

    // Define closure and environment structures
    std::vector<gcc_jit_field*> env_fields;
    for (const auto& var_name : captured_vars) {
        for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
            if (it->count(var_name)) {
                env_fields.push_back(gcc_jit_context_new_field(m_context, NULL, gcc_jit_rvalue_get_type(gcc_jit_lvalue_as_rvalue(it->at(var_name))), var_name.c_str()));
                break;
            }
        }
    }
    gcc_jit_struct* env_struct = gcc_jit_context_new_struct_type(m_context, NULL, "env", env_fields.size(), env_fields.data());
    gcc_jit_type* env_type = gcc_jit_struct_as_type(env_struct);

    gcc_jit_type* func_ptr_type = gcc_jit_type_get_pointer(m_void_type);
    gcc_jit_field* fields[] = {
        gcc_jit_context_new_field(m_context, NULL, func_ptr_type, "func_ptr"),
        gcc_jit_context_new_field(m_context, NULL, gcc_jit_type_get_pointer(env_type), "env")
    };
    gcc_jit_struct* closure_struct = gcc_jit_context_new_struct_type(m_context, NULL, "closure", 2, fields);
    gcc_jit_type* closure_type = gcc_jit_struct_as_type(closure_struct);

    // Create the JIT function for the lambda
    std::vector<gcc_jit_param*> params;
    params.push_back(gcc_jit_context_new_param(m_context, NULL, gcc_jit_type_get_pointer(m_void_type), "env"));
    for (const auto& p : expr->params) {
        params.push_back(gcc_jit_context_new_param(m_context, NULL, get_jit_type(p.second), p.first.c_str()));
    }
    gcc_jit_type* return_type = get_jit_type(expr->returnType.value_or(nullptr));
    gcc_jit_function* func = gcc_jit_context_new_function(m_context, NULL, GCC_JIT_FUNCTION_INTERNAL, return_type, "lambda", params.size(), params.data(), 0);

    // Code generation for the lambda body
    gcc_jit_block* prev_block = m_current_block;
    m_current_block = gcc_jit_function_new_block(func, "entry");

    m_scopes.emplace_back();
    for (size_t i = 1; i < params.size(); ++i) {
        m_scopes.back()[expr->params[i - 1].first] = gcc_jit_param_as_lvalue(params[i]);
    }

    visit(expr->body);

    m_scopes.pop_back();
    m_current_block = prev_block;

    // Allocate and populate the closure struct
    gcc_jit_lvalue* closure_lvalue = gcc_jit_function_new_local(m_current_func, NULL, closure_type, "closure");
    
    // Allocate environment on the heap
    gcc_jit_rvalue* size = gcc_jit_context_new_rvalue_from_int(m_context, gcc_jit_context_get_type(m_context, GCC_JIT_TYPE_SIZE_T), gcc_jit_type_get_size(env_type));
    gcc_jit_rvalue* args[] = {size};
    gcc_jit_rvalue* env_ptr = gcc_jit_context_new_call(m_context, NULL, m_malloc_func, 1, args);
    gcc_jit_lvalue* env_lvalue = gcc_jit_rvalue_dereference(gcc_jit_context_new_cast(m_context, NULL, env_ptr, gcc_jit_type_get_pointer(env_type)), NULL);

    for (size_t i = 0; i < captured_vars.size(); ++i) {
        for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
            if (it->count(captured_vars[i])) {
                gcc_jit_block_add_assignment(m_current_block, NULL, gcc_jit_lvalue_access_field(env_lvalue, NULL, env_fields[i]), gcc_jit_lvalue_as_rvalue(it->at(captured_vars[i])));
                break;
            }
        }
    }
    
    // Allocate closure in the region
    gcc_jit_block_add_assignment(m_current_block, NULL, gcc_jit_lvalue_access_field(closure_lvalue, NULL, fields[0]), gcc_jit_function_get_address(func, NULL));
    gcc_jit_block_add_assignment(m_current_block, NULL, gcc_jit_lvalue_access_field(closure_lvalue, NULL, fields[1]), env_ptr);

    return gcc_jit_lvalue_as_rvalue(closure_lvalue);
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::CallExpr>& expr) {
    gcc_jit_rvalue* callee = visit_expr(expr->callee);
    gcc_jit_type* callee_type = gcc_jit_rvalue_get_type(callee);

    if (gcc_jit_type_is_struct(callee_type)) {
        // Assume it's a closure
        gcc_jit_lvalue* closure_lvalue = gcc_jit_rvalue_dereference(callee, NULL);
        gcc_jit_rvalue* func_ptr = gcc_jit_rvalue_access_field(gcc_jit_lvalue_as_rvalue(closure_lvalue), NULL, gcc_jit_struct_get_field(gcc_jit_type_is_struct(callee_type), 0));
        gcc_jit_rvalue* env = gcc_jit_rvalue_access_field(gcc_jit_lvalue_as_rvalue(closure_lvalue), NULL, gcc_jit_struct_get_field(gcc_jit_type_is_struct(callee_type), 1));

        std::vector<gcc_jit_rvalue*> args;
        args.push_back(env);
        for (const auto& arg : expr->arguments) {
            args.push_back(visit_expr(arg));
        }
        return gcc_jit_context_new_call_through_ptr(m_context, NULL, func_ptr, args.size(), args.data());
    } else {
        auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee);
        if (!var_expr) {
            throw std::runtime_error("JIT only supports direct function calls");
        }

        if (m_functions.count(var_expr->name)) {
            gcc_jit_function* func = m_functions[var_expr->name];
            std::vector<gcc_jit_rvalue*> args;
            for (const auto& arg : expr->arguments) {
                args.push_back(visit_expr(arg));
            }
            return gcc_jit_context_new_call(m_context, NULL, func, args.size(), args.data());
        }

        throw std::runtime_error("Unknown function: " + var_expr->name);
    }
}

void JitBackend::visit(const std::shared_ptr<AST::MatchStatement>& stmt) {
    gcc_jit_rvalue* value = visit_expr(stmt->value);
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_current_func, "after_match");
    std::vector<gcc_jit_block*> case_blocks;
    std::vector<gcc_jit_case*> cases;

    for (size_t i = 0; i < stmt->cases.size(); ++i) {
        case_blocks.push_back(gcc_jit_function_new_block(m_current_func, ("case_" + std::to_string(i)).c_str()));
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

void JitBackend::visit(const std::shared_ptr<AST::ImportStatement>& stmt) {
    // Will be implemented in a later step
}

std::string JitBackend::mangle(const std::string& name) {
    return "_Z" + std::to_string(m_current_module_name.length()) + m_current_module_name + std::to_string(name.length()) + name;
}

void JitBackend::visit(const std::shared_ptr<AST::ModuleDeclaration>& stmt) {
    m_current_module_name = stmt->name;
    for (const auto& s : stmt->publicMembers) {
        visit(s);
    }
    for (const auto& s : stmt->protectedMembers) {
        visit(s);
    }
    for (const auto& s : stmt->privateMembers) {
        visit(s);
    }
}

void JitBackend::visit(const std::shared_ptr<AST::ClassDeclaration>& stmt) {
    throw std::runtime_error("Class declarations are not yet supported by JIT");
}

void JitBackend::visit(const std::shared_ptr<AST::ParallelStatement>& stmt) {
    throw std::runtime_error("Parallel statements are not yet supported by JIT");
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::GroupingExpr>& expr) {
    return visit_expr(expr->expression);
}

void JitBackend::visit(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    gcc_jit_function* func = m_functions[stmt->name];
    gcc_jit_function* prev_func = m_current_func;
    m_current_func = func;
    gcc_jit_block* prev_block = m_current_block;
    m_current_block = gcc_jit_function_new_block(m_current_func, "entry");

    m_scopes.emplace_back();
    for (int i = 0; i < stmt->params.size(); ++i) {
        m_scopes.back()[stmt->params[i].first] = gcc_jit_param_as_lvalue(gcc_jit_function_get_param(func, i));
    }

    visit(stmt->body);

    m_scopes.pop_back();
    m_current_block = prev_block;
    m_current_func = prev_func;
}

void JitBackend::visit(const std::shared_ptr<AST::ReturnStatement>& stmt) {
    if (stmt->value) {
        gcc_jit_rvalue* rvalue = visit_expr(stmt->value);
        gcc_jit_block_end_with_return(m_current_block, NULL, rvalue);
    } else {
        gcc_jit_block_end_with_void_return(m_current_block, NULL);
    }
}

gcc_jit_type* JitBackend::get_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type) {
    if (!type) {
        return m_void_type;
    }
    if (type->typeName == "int") {
        return m_int_type;
    }
    if (type->typeName == "double") {
        return m_double_type;
    }
    if (type->typeName == "bool") {
        return m_bool_type;
    }
    if (type->typeName == "string") {
        return m_const_char_ptr_type;
    }
    throw std::runtime_error("Unsupported type for JIT: " + type->typeName);
}

void JitBackend::visit(const std::shared_ptr<AST::WhileStatement>& stmt) {
    gcc_jit_block* cond_block = gcc_jit_function_new_block(m_current_func, "while_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(m_current_func, "while_body");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_current_func, "after_while");

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
        } else if (type == m_double_type) {
            format_str = "%f\n";
        } else if (type == m_bool_type) {
            format_str = "%s\n";
           // rvalue = gcc_jit_context_new_conditional(m_context, NULL, rvalue, gcc_jit_context_new_string_literal(m_context, "true"), gcc_jit_context_new_string_literal(m_context, "false"));
        } else if (type == m_const_char_ptr_type) {
            format_str = "%s\n";
        } else if (type == m_void_type) {
            format_str = "nil\n";
            rvalue = gcc_jit_context_new_string_literal(m_context, "nil");
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
    gcc_jit_block* then_block = gcc_jit_function_new_block(m_current_func, "then");
    gcc_jit_block* else_block = gcc_jit_function_new_block(m_current_func, "else");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_current_func, "after");
    
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
    gcc_jit_lvalue* i = gcc_jit_function_new_local(m_current_func, NULL, m_int_type, stmt->loopVars[0].c_str());
    m_scopes.back()[stmt->loopVars[0]] = i;
    gcc_jit_rvalue* start = visit_expr(range_expr->start);
    gcc_jit_block_add_assignment(m_current_block, NULL, i, start);

    gcc_jit_block* cond_block = gcc_jit_function_new_block(m_current_func, "iter_cond");
    gcc_jit_block* body_block = gcc_jit_function_new_block(m_current_func, "iter_body");
    gcc_jit_block* increment_block = gcc_jit_function_new_block(m_current_func, "iter_increment");
    gcc_jit_block* after_block = gcc_jit_function_new_block(m_current_func, "after_iter");

    m_loop_blocks.push_back({increment_block, after_block});

    gcc_jit_block_end_with_jump(m_current_block, NULL, cond_block);

    // Condition
    m_current_block = cond_block;
    gcc_jit_rvalue* end = visit_expr(range_expr->end);
    enum gcc_jit_comparison op = range_expr->inclusive ? GCC_JIT_COMPARISON_LE : GCC_JIT_COMPARISON_LT;
    gcc_jit_rvalue* condition = gcc_jit_context_new_comparison(m_context, NULL, op, gcc_jit_lvalue_as_rvalue(i), end);
    gcc_jit_block_end_with_conditional(m_current_block, NULL, condition, body_block, after_block);

    // Body
    m_current_block = body_block;
    visit(stmt->body);
    gcc_jit_block_end_with_jump(m_current_block, NULL, increment_block);

    // Increment
    m_current_block = increment_block;
    gcc_jit_rvalue* step = range_expr->step ? visit_expr(range_expr->step) : gcc_jit_context_new_rvalue_from_int(m_context, m_int_type, 1);
    gcc_jit_block_add_assignment_op(m_current_block, NULL, i, GCC_JIT_BINARY_OP_PLUS, step);
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
    if (auto e = std::dynamic_pointer_cast<AST::CallExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) return visit_expr(e);
    throw std::runtime_error("Unsupported expression type for JIT");
}

gcc_jit_rvalue* JitBackend::visit_expr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    gcc_jit_rvalue* left = visit_expr(expr->left);
    gcc_jit_rvalue* right = visit_expr(expr->right);

    gcc_jit_type* left_type = gcc_jit_rvalue_get_type(left);
    gcc_jit_type* right_type = gcc_jit_rvalue_get_type(right);

    if (left_type == m_const_char_ptr_type && right_type == m_const_char_ptr_type) {
        if (expr->op == TokenType::EQUAL_EQUAL || expr->op == TokenType::BANG_EQUAL) {
            gcc_jit_rvalue* args[] = {left, right};
            gcc_jit_rvalue* result = gcc_jit_context_new_call(m_context, NULL, m_strcmp_func, 2, args);
            gcc_jit_rvalue* zero = gcc_jit_context_new_rvalue_from_int(m_context, m_int_type, 0);
            if (expr->op == TokenType::EQUAL_EQUAL) {
                return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_EQ, result, zero);
            } else {
                return gcc_jit_context_new_comparison(m_context, NULL, GCC_JIT_COMPARISON_NE, result, zero);
            }
        }
    }

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
        case TokenType::AND:
        {
            gcc_jit_block* on_true = gcc_jit_function_new_block(m_current_func, "on_true");
            gcc_jit_block* on_false = gcc_jit_function_new_block(m_current_func, "on_false");
            gcc_jit_block* after = gcc_jit_function_new_block(m_current_func, "after");
            gcc_jit_lvalue* result = gcc_jit_function_new_local(m_current_func, NULL, m_bool_type, "and_result");

            gcc_jit_block_end_with_conditional(m_current_block, NULL, left, on_true, on_false);

            m_current_block = on_true;
            gcc_jit_block_add_assignment(m_current_block, NULL, result, right);
            gcc_jit_block_end_with_jump(m_current_block, NULL, after);

            m_current_block = on_false;
            gcc_jit_block_add_assignment(m_current_block, NULL, result, gcc_jit_context_new_rvalue_from_int(m_context, m_bool_type, 0));
            gcc_jit_block_end_with_jump(m_current_block, NULL, after);

            m_current_block = after;
            return gcc_jit_lvalue_as_rvalue(result);
        }
        case TokenType::OR:
        {
            gcc_jit_block* on_true = gcc_jit_function_new_block(m_current_func, "on_true");
            gcc_jit_block* on_false = gcc_jit_function_new_block(m_current_func, "on_false");
            gcc_jit_block* after = gcc_jit_function_new_block(m_current_func, "after");
            gcc_jit_lvalue* result = gcc_jit_function_new_local(m_current_func, NULL, m_bool_type, "or_result");

            gcc_jit_block_end_with_conditional(m_current_block, NULL, left, on_true, on_false);

            m_current_block = on_true;
            gcc_jit_block_add_assignment(m_current_block, NULL, result, gcc_jit_context_new_rvalue_from_int(m_context, m_bool_type, 1));
            gcc_jit_block_end_with_jump(m_current_block, NULL, after);

            m_current_block = on_false;
            gcc_jit_block_add_assignment(m_current_block, NULL, result, right);
            gcc_jit_block_end_with_jump(m_current_block, NULL, after);

            m_current_block = after;
            return gcc_jit_lvalue_as_rvalue(result);
        }
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
        return gcc_jit_context_new_rvalue_from_long(m_context, m_int_type, std::get<long long>(expr->value));
    }
    if (std::holds_alternative<long double>(expr->value)) {
        return gcc_jit_context_new_rvalue_from_double(m_context, m_double_type, std::get<long double>(expr->value));
    }
    if (std::holds_alternative<bool>(expr->value)) {
        return gcc_jit_context_new_rvalue_from_int(m_context, m_bool_type, std::get<bool>(expr->value));
    }
    if (std::holds_alternative<std::string>(expr->value)) {
        return gcc_jit_context_new_string_literal(m_context, std::get<std::string>(expr->value).c_str());
    }
    if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        return gcc_jit_context_null(m_context, m_void_type);
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
