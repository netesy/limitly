#include "jit_backend.hh"
#include <functional>
#include <iostream>
#include "value.hh"

JitBackend::JitBackend() : m_context(gccjit::context::acquire()), m_mem_manager() {
    // Check if context is valid
    if (!m_context.get_inner_context()) {
        throw std::runtime_error("Failed to acquire JIT context");
    }
    
    // Initialize memory region
    m_region = std::make_unique<MemoryManager<>::Region>(m_mem_manager);
    
    // Initialize basic types
    m_void_type = m_context.get_type(GCC_JIT_TYPE_VOID);
    if (!m_void_type.get_inner_type()) {
        throw std::runtime_error("Failed to get void type");
    }
    
    m_int_type = m_context.get_type(GCC_JIT_TYPE_INT);
    if (!m_int_type.get_inner_type()) {
        throw std::runtime_error("Failed to get int type");
    }
    m_double_type = m_context.get_type(GCC_JIT_TYPE_DOUBLE);
    m_bool_type = m_context.get_type(GCC_JIT_TYPE_BOOL);
    m_int8_type = m_context.get_type(GCC_JIT_TYPE_INT8_T);
    m_int16_type = m_context.get_type(GCC_JIT_TYPE_INT16_T);
    m_int32_type = m_context.get_type(GCC_JIT_TYPE_INT32_T);
    m_int64_type = m_context.get_type(GCC_JIT_TYPE_INT64_T);
    m_uint8_type = m_context.get_type(GCC_JIT_TYPE_UINT8_T);
    m_uint16_type = m_context.get_type(GCC_JIT_TYPE_UINT16_T);
    m_uint32_type = m_context.get_type(GCC_JIT_TYPE_UINT32_T);
    m_uint64_type = m_context.get_type(GCC_JIT_TYPE_UINT64_T);
    m_float_type = m_context.get_type(GCC_JIT_TYPE_FLOAT);
    m_const_char_ptr_type = m_context.get_type(GCC_JIT_TYPE_CONST_CHAR_PTR);
    m_void_ptr_type = m_context.get_type(GCC_JIT_TYPE_VOID_PTR);
    
    // Validate critical types
    if (!m_const_char_ptr_type.get_inner_type()) {
        throw std::runtime_error("Failed to get const char ptr type");
    }
    if (!m_void_ptr_type.get_inner_type()) {
        throw std::runtime_error("Failed to get void ptr type");
    }
    
    // Set up printf function
    std::vector<gccjit::param> printf_params;
    printf_params.push_back(m_context.new_param(m_const_char_ptr_type, "format"));
    m_printf_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "printf", printf_params, 1);
    
    // Set up strcmp function
    std::vector<gccjit::param> strcmp_params;
    strcmp_params.push_back(m_context.new_param(m_const_char_ptr_type, "s1"));
    strcmp_params.push_back(m_context.new_param(m_const_char_ptr_type, "s2"));
    m_strcmp_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "strcmp", strcmp_params, 0);
    
    // Set up malloc function
    std::vector<gccjit::param> malloc_params;
    malloc_params.push_back(m_context.new_param(m_context.get_type(GCC_JIT_TYPE_SIZE_T), "size"));
    m_malloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type.get_pointer(), "malloc", malloc_params, 0);
    
    // Set up strlen function
    std::vector<gccjit::param> strlen_params;
    strlen_params.push_back(m_context.new_param(m_const_char_ptr_type, "str"));
    m_strlen_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_context.get_type(GCC_JIT_TYPE_SIZE_T), "strlen", strlen_params, 0);
    
    // Set up strcpy function
    std::vector<gccjit::param> strcpy_params;
    strcpy_params.push_back(m_context.new_param(m_const_char_ptr_type, "dest"));
    strcpy_params.push_back(m_context.new_param(m_const_char_ptr_type, "src"));
    m_strcpy_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_const_char_ptr_type, "strcpy", strcpy_params, 0);
    
    // Set up strcat function
    std::vector<gccjit::param> strcat_params;
    strcat_params.push_back(m_context.new_param(m_const_char_ptr_type, "dest"));
    strcat_params.push_back(m_context.new_param(m_const_char_ptr_type, "src"));
    m_strcat_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_const_char_ptr_type, "strcat", strcat_params, 0);
    
    // Register builtin functions
    register_builtin_functions();
}

JitBackend::~JitBackend() = default;

void JitBackend::process(const std::vector<std::shared_ptr<AST::Program>>& programs) {
    // First pass: Create forward declarations for all functions and add to symbol table
    for (const auto& program : programs) {
        for (const auto& stmt : program->statements) {
            if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
                std::cout << "DEBUG: Processing function: " << func_decl->name << std::endl;
                std::vector<gccjit::param> params;
                std::vector<TypePtr> param_types;
                for (const auto& p : func_decl->params) {
                    std::cout << "DEBUG: Processing param: " << p.first << std::endl;
                    auto jit_type = get_jit_type(p.second);
                    if (!jit_type.get_inner_type()) {
                        throw std::runtime_error("Failed to get JIT type for param: " + p.first);
                    }
                    params.push_back(m_context.new_param(jit_type, p.first.c_str()));
                    param_types.push_back(convert_ast_type(p.second));
                }
                std::cout << "DEBUG: Getting return type" << std::endl;
                gccjit::type return_type = get_jit_type(func_decl->returnType.value_or(nullptr));
                if (!return_type.get_inner_type()) {
                    throw std::runtime_error("Failed to get JIT return type for function: " + func_decl->name);
                }
                TypePtr return_type_ptr = convert_ast_type(func_decl->returnType.value_or(nullptr));
                
                enum gcc_jit_function_kind kind = func_decl->visibility == AST::VisibilityLevel::Public ? GCC_JIT_FUNCTION_EXPORTED : GCC_JIT_FUNCTION_INTERNAL;
                std::string mangled_name = mangle(func_decl->name);
                std::cout << "DEBUG: Creating function: " << mangled_name << std::endl;
                gccjit::function func = m_context.new_function(kind, return_type, mangled_name.c_str(), params, 0);
                if (!func.get_inner_function()) {
                    throw std::runtime_error("Failed to create function: " + mangled_name);
                }
                m_functions[mangled_name] = func;
                
                // Add to symbol table
                FunctionSignature signature(func_decl->name, param_types, return_type_ptr);
                m_symbol_table.addFunction(func_decl->name, signature);
            }
        }
    }

    // Create the main function
    std::vector<gccjit::param> main_params;
    
    // Debug: Check if m_int_type is valid
    if (!m_int_type.get_inner_type()) {
        throw std::runtime_error("m_int_type is NULL before creating main function");
    }
    
    try {
        m_main_func = m_context.new_function(GCC_JIT_FUNCTION_EXPORTED, m_int_type, "main", main_params, 0);
        if (!m_main_func.get_inner_function()) {
            throw std::runtime_error("Failed to create main function - NULL function returned");
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to create main function: " + std::string(e.what()));
    }
    m_current_func = m_main_func;
    m_current_block = m_current_func.new_block("entry");
    
    // Global scope is already created in symbol table constructor

    // Second pass: Generate code for all statements
    for (const auto& program : programs) {
        for (const auto& stmt : program->statements) {
            visit(stmt);
        }
    }

    m_current_block.end_with_return(m_context.new_rvalue(m_int_type, 0));
}

void JitBackend::compile(const char* output_filename) {
    m_context.compile_to_file(GCC_JIT_OUTPUT_KIND_EXECUTABLE, output_filename);
}

int JitBackend::compile_and_run() {
    // Debug mode: compile in memory and run directly
    gcc_jit_result* result = m_context.compile();
    if (!result) {
        throw std::runtime_error("JIT compilation failed in debug mode");
    }
    
    // Get the main function pointer
    typedef int (*main_func_t)();
    main_func_t main_func = (main_func_t)gcc_jit_result_get_code(result, "main");
    if (!main_func) {
        gcc_jit_result_release(result);
        throw std::runtime_error("Failed to get main function from JIT result");
    }
    
    // Run the function and capture return value
    int exit_code = main_func();
    
    // Clean up
    gcc_jit_result_release(result);
    
    return exit_code;
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
    // Determine the type of the variable
    gccjit::type type;
    TypePtr symbol_type;
    
    if (stmt->type) {
        type = get_jit_type(stmt->type.value_or(nullptr));
        symbol_type = convert_ast_type(stmt->type.value());
    } else if (stmt->initializer) {
        // Infer type from initializer
        gccjit::rvalue init_val = visit_expr(stmt->initializer);
        type = init_val.get_type();
        symbol_type = convert_jit_type(type);
    } else {
        // Default to int type if no type and no initializer
        type = m_int_type;
        symbol_type = std::make_shared<Type>(TypeTag::Int);
    }
    
    // Create variable
    gccjit::lvalue lvalue;
    if (m_symbol_table.isInGlobalScope()) { // Global variable
        enum gcc_jit_global_kind kind = stmt->visibility == AST::VisibilityLevel::Public ? GCC_JIT_GLOBAL_EXPORTED : GCC_JIT_GLOBAL_INTERNAL;
        std::string mangled_name = mangle(stmt->name);
        lvalue = m_context.new_global(kind, type, mangled_name.c_str());
    } else { // Local variable
        lvalue = m_current_func.new_local(type, stmt->name.c_str());
    }
    
    // Store in both symbol table and JIT mapping
    m_symbol_table.addVariable(stmt->name, symbol_type, stmt->line);
    m_variable_lvalues[stmt->name] = lvalue;
    
    // Initialize if needed
    if (stmt->initializer) {
        gccjit::rvalue rvalue = visit_expr(stmt->initializer);
        // Cast to the correct type if needed
        if (rvalue.get_type().get_inner_type() != type.get_inner_type()) {
            rvalue = m_context.new_cast(rvalue, type);
        }
        m_current_block.add_assignment(lvalue, rvalue);
    }
}

void JitBackend::visit(const std::shared_ptr<AST::ExprStatement>& stmt) {
    visit_expr(stmt->expression);
}

void JitBackend::visit(const std::shared_ptr<AST::ForStatement>& stmt) {
    // Enter new scope for for loop
    m_symbol_table.enterScope();
    
    // Handle initializer (it's a Statement, not Expression)
    if (stmt->initializer) {
        visit(stmt->initializer);
    }
    
    gccjit::rvalue end_val = visit_expr(stmt->condition);
    gccjit::rvalue step_val = visit_expr(stmt->increment);
    
    gccjit::lvalue loop_var = m_current_func.new_local(m_int_type, stmt->loopVars[0].c_str());
    
    // Add loop variable to symbol table and JIT mapping
    TypePtr int_type = std::make_shared<Type>(TypeTag::Int32);
    m_symbol_table.addVariable(stmt->loopVars[0], int_type, stmt->line);
    m_variable_lvalues[stmt->loopVars[0]] = loop_var;
    
    gccjit::block cond_block = m_current_func.new_block("for_cond");
    gccjit::block body_block = m_current_func.new_block("for_body");
    gccjit::block after_block = m_current_func.new_block("for_after");
    
    m_current_block.end_with_jump(cond_block);
    
    m_current_block = cond_block;
    gccjit::rvalue condition = m_context.new_comparison(GCC_JIT_COMPARISON_LE, loop_var, end_val);
    m_current_block.end_with_conditional(condition, body_block, after_block);
    
    m_current_block = body_block;
    m_loop_blocks.push_back({cond_block, after_block});
    visit(stmt->body);
    m_loop_blocks.pop_back();
    
    // Increment loop variable
    gccjit::rvalue loop_var_rvalue = loop_var.dereference();
    gccjit::rvalue new_val = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, loop_var_rvalue.get_type(), loop_var_rvalue, step_val);
    m_current_block.add_assignment(loop_var, new_val);
    
    m_current_block.end_with_jump(cond_block);
    
    m_current_block = after_block;
    
    // Exit scope
    m_symbol_table.exitScope();
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::LambdaExpr>& expr) {
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
                Symbol* symbol = m_symbol_table.findVariable(var_expr->name);
                if (symbol) {
                    is_local = true;
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
    std::vector<gccjit::field> env_fields;
    for (const auto& var_name : captured_vars) {
        auto it = m_variable_lvalues.find(var_name);
        if (it != m_variable_lvalues.end()) {
            env_fields.push_back(m_context.new_field(it->second.get_type(), var_name.c_str()));
        }
    }
    gccjit::struct_ env_struct = m_context.new_struct_type("env", env_fields);
    gccjit::type env_type = env_struct;

    gccjit::type func_ptr_type = m_void_type.get_pointer();
    std::vector<gccjit::field> fields;
    fields.push_back(m_context.new_field(func_ptr_type, "func_ptr"));
    fields.push_back(m_context.new_field(env_type.get_pointer(), "env"));
    gccjit::struct_ closure_struct = m_context.new_struct_type("closure", fields);
    gccjit::type closure_type = closure_struct;

    // Create the JIT function for the lambda
    std::vector<gccjit::param> params;
    params.push_back(m_context.new_param(m_void_type.get_pointer(), "env"));
    for (const auto& p : expr->params) {
        params.push_back(m_context.new_param(get_jit_type(p.second), p.first.c_str()));
    }
    gccjit::type return_type = get_jit_type(expr->returnType.value_or(nullptr));
    gccjit::function func = m_context.new_function(GCC_JIT_FUNCTION_INTERNAL, return_type, "lambda", params, 0);

    // Code generation for the lambda body
    auto prev_func = m_current_func;
    auto prev_block = m_current_block;
    m_current_func = func;
    m_current_block = func.new_block("entry");

    // Enter new scope for lambda
    m_symbol_table.enterScope();
    
    // Add parameters to symbol table and JIT mapping
    for (size_t i = 1; i < params.size(); ++i) {
        const auto& param_name = expr->params[i - 1].first;
        TypePtr param_type = convert_ast_type(expr->params[i - 1].second);
        m_symbol_table.addVariable(param_name, param_type, 0);
        m_variable_lvalues[param_name] = func.get_param(i);
    }

    visit(expr->body);

    // Exit scope
    m_symbol_table.exitScope();
    m_current_block = prev_block;

    // Allocate and populate the closure struct
    gccjit::lvalue closure_lvalue = m_current_func.new_local(closure_type, "closure");
    
    // Get size using C API
    gcc_jit_type* c_env_type = env_type.get_inner_type();
    size_t env_size = gcc_jit_type_get_size(c_env_type);
    gccjit::rvalue size = m_context.new_rvalue(
        m_context.get_type(GCC_JIT_TYPE_SIZE_T), 
        static_cast<int>(env_size)
    );
    std::vector<gccjit::rvalue> args;
    args.push_back(size);
    gccjit::rvalue env_ptr = m_context.new_call(m_malloc_func, args);
    gccjit::lvalue env_lvalue = m_context.new_cast(env_ptr, env_type.get_pointer()).dereference();

    for (size_t i = 0; i < captured_vars.size(); ++i) {
        auto it = m_variable_lvalues.find(captured_vars[i]);
        if (it != m_variable_lvalues.end()) {
            m_current_block.add_assignment(env_lvalue.access_field(env_fields[i]), it->second);
        }
    }
    
    // Allocate closure in the region
    m_current_block.add_assignment(closure_lvalue.access_field(fields[0]), func.get_address());
    m_current_block.add_assignment(closure_lvalue.access_field(fields[1]), env_ptr);

    return closure_lvalue;
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::CallExpr>& expr) {
    auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee);
    auto member_expr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->callee);
    
    if (member_expr) {
        // Handle method calls
        gccjit::rvalue object = visit_expr(member_expr->object);
        gccjit::lvalue object_lvalue = object.dereference();
        gccjit::type struct_type = object_lvalue.get_type();
        
        // Find the mangled name by searching m_class_types
        std::string mangled_name;
        for (const auto& [name, type] : m_class_types) {
            // Get the underlying C objects
            gcc_jit_type* c_type = type;
            gcc_jit_type* c_struct_type = struct_type.get_inner_type();
            if (c_type == c_struct_type) {
                mangled_name = name;
                break;
            }
        }
        
        if (mangled_name.empty()) {
            throw std::runtime_error("Unknown struct type");
        }
        
        std::string class_name = m_type_names[mangled_name];
        std::string method_name = class_name + "_" + member_expr->name;
        std::string mangled_method_name = mangle(method_name);

        if (m_functions.count(mangled_method_name)) {
            gccjit::function func = m_functions[mangled_method_name];
            std::vector<gccjit::rvalue> args;
            args.push_back(object);
            for (const auto& arg : expr->arguments) {
                args.push_back(visit_expr(arg));
            }
            return m_context.new_call(func, args);
        }
    } else if (var_expr) {
        // Handle direct function calls
        std::string mangled_name = mangle(var_expr->name);
        
        // Check user-defined functions in m_functions (JIT compilation context)
        if (m_functions.count(mangled_name)) {
            gccjit::function func = m_functions[mangled_name];
            std::vector<gccjit::rvalue> args;
            for (const auto& arg : expr->arguments) {
                args.push_back(visit_expr(arg));
            }
            return m_context.new_call(func, args);
        }
        
        // Check if it's a builtin function that wasn't registered yet
        auto& builtins = builtin::BuiltinFunctions::getInstance();
        if (builtins.isBuiltinFunction(var_expr->name)) {
            // Register it on-demand
            const auto* def = builtins.getBuiltinDefinition(var_expr->name);
            if (def) {
                // Convert parameter types
                std::vector<gccjit::param> params;
                for (const auto& paramType : def->parameterTypes) {
                    gccjit::type jit_type = convert_builtin_type(paramType);
                    // Skip void parameter types - they're not valid in function parameters
                    if (jit_type.get_inner_type() != m_void_type.get_inner_type()) {
                        params.push_back(m_context.new_param(jit_type, ("param_" + std::to_string(params.size())).c_str()));
                    }
                }
                
                // Convert return type
                gccjit::type return_type = convert_builtin_type(def->returnType);
                
                // Create the function
                auto func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, return_type, mangled_name.c_str(), params, 0);
                m_functions[mangled_name] = func;
                
                std::vector<gccjit::rvalue> args;
                for (const auto& arg : expr->arguments) {
                    args.push_back(visit_expr(arg));
                }
                return m_context.new_call(func, args);
            }
        }

        if (m_class_types.count(mangled_name)) {
            gccjit::type class_type = m_class_types[mangled_name];
            // libgccjit cannot query type size directly, use hardcoded approach
            // For now, assume 64 bytes per class (this should be tracked properly)
            gccjit::rvalue size = m_context.new_rvalue(m_context.get_type(GCC_JIT_TYPE_SIZE_T), 64);
            std::vector<gccjit::rvalue> args;
            args.push_back(size);
            gccjit::rvalue instance = m_context.new_call(m_malloc_func, args);
            return m_context.new_cast(instance, class_type.get_pointer());
        }

        throw std::runtime_error("Unknown function or class: " + var_expr->name);
    } else {
        // Handle closure calls (function as first-class values)
        gccjit::rvalue callee = visit_expr(expr->callee);
        gccjit::type callee_type = callee.get_type();
        gcc_jit_type* c_callee_type = callee_type.get_inner_type();

        if (gcc_jit_type_is_struct(c_callee_type)) {
            // Assume it's a closure
            gccjit::lvalue closure_lvalue = callee.dereference();
            gccjit::rvalue func_ptr = closure_lvalue.access_field(m_context.new_field(m_void_type.get_pointer(), "func_ptr"));
            gccjit::rvalue env = closure_lvalue.access_field(m_context.new_field(m_void_type.get_pointer(), "env"));

            // Use C API for call through pointer
            std::vector<gcc_jit_rvalue*> c_args;
            gcc_jit_rvalue* c_env = env.get_inner_rvalue();
            c_args.push_back(c_env);
            for (const auto& arg : expr->arguments) {
                gccjit::rvalue arg_rvalue = visit_expr(arg);
                c_args.push_back(arg_rvalue.get_inner_rvalue());
            }
            
            gcc_jit_context* c_ctx = m_context.get_inner_context();
            gcc_jit_rvalue* c_func_ptr = func_ptr.get_inner_rvalue();
            gcc_jit_rvalue* result = gcc_jit_context_new_call_through_ptr(
                c_ctx,
                nullptr,
                c_func_ptr,
                c_args.size(),
                c_args.data()
            );
            return gccjit::rvalue(result);
        }
        
        throw std::runtime_error("JIT only supports direct function calls and closure calls");
    }
}

void JitBackend::visit(const std::shared_ptr<AST::MatchStatement>& stmt) {
    gccjit::rvalue value = visit_expr(stmt->value);
    gccjit::block after_block = m_current_func.new_block("after_match");
    std::vector<gccjit::block> case_blocks;
    std::vector<gccjit::case_> cases;

    for (size_t i = 0; i < stmt->cases.size(); ++i) {
        case_blocks.push_back(m_current_func.new_block(("case_" + std::to_string(i)).c_str()));
    }

    for (size_t i = 0; i < stmt->cases.size(); ++i) {
        auto literal_expr = std::dynamic_pointer_cast<AST::LiteralExpr>(stmt->cases[i].pattern);
        if (!literal_expr) {
            throw std::runtime_error("JIT only supports literal patterns in match statements");
        }
        gccjit::rvalue case_value = visit_expr(literal_expr);
        cases.push_back(m_context.new_case(case_value, case_value, case_blocks[i]));
    }

    m_current_block.end_with_switch(value, after_block, cases);

    for (size_t i = 0; i < stmt->cases.size(); ++i) {
        m_current_block = case_blocks[i];
        visit(stmt->cases[i].body);
        m_current_block.end_with_jump(after_block);
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
    // Create a new struct type for the class
    std::vector<gccjit::field> fields;

    if (!stmt->superClassName.empty()) {
        std::string mangled_super_name = mangle(stmt->superClassName);
        if (m_class_types.count(mangled_super_name)) {
            fields.push_back(m_context.new_field(m_class_types[mangled_super_name], "super"));
        } else {
            throw std::runtime_error("Unknown superclass: " + stmt->superClassName);
        }
    }
    

    for (const auto& field : stmt->fields) {
        gccjit::type field_type = get_jit_type(field->type.value_or(nullptr));
        fields.push_back(m_context.new_field(field_type, field->name.c_str()));
    }

    std::string mangled_name = mangle(stmt->name);
    gccjit::struct_ class_struct = m_context.new_struct_type(mangled_name.c_str(), fields);
    gccjit::type class_type = class_struct;

    m_class_types[mangled_name] = class_type.get_inner_type();
    m_type_names[mangled_name] = stmt->name;
    
    // Store the fields for later access
    m_class_fields[mangled_name] = fields;

    // Store field names for later lookup
    std::vector<std::string> field_names;
    for (const auto& field : stmt->fields) {
        field_names.push_back(field->name);
    }
    m_struct_field_names[mangled_name] = field_names;

    for (const auto& method : stmt->methods) {
        std::vector<gccjit::param> params;
        params.push_back(m_context.new_param(class_type.get_pointer(), "this"));
        for (const auto& p : method->params) {
            params.push_back(m_context.new_param(get_jit_type(p.second), p.first.c_str()));
        }
        gccjit::type return_type = get_jit_type(method->returnType.value_or(nullptr));
        enum gcc_jit_function_kind kind = method->visibility == AST::VisibilityLevel::Public ? GCC_JIT_FUNCTION_EXPORTED : GCC_JIT_FUNCTION_INTERNAL;
        std::string method_name = stmt->name + "_" + method->name;
        std::string mangled_method_name = mangle(method_name);
        gccjit::function func = m_context.new_function(kind, return_type, mangled_method_name.c_str(), params, 0);
        m_functions[mangled_method_name] = func;
    }
}

void JitBackend::visit(const std::shared_ptr<AST::ParallelStatement>& stmt) {
    throw std::runtime_error("Parallel statements are not yet supported by JIT");
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::GroupingExpr>& expr) {
    return visit_expr(expr->expression);
}

void JitBackend::visit(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    std::string mangled_name = mangle(stmt->name);
    gccjit::function func = m_functions[mangled_name];
    gccjit::function prev_func = m_current_func;
    m_current_func = func;
    gccjit::block prev_block = m_current_block;
    m_current_block = m_current_func.new_block("entry");

    // Enter new scope for function
    m_symbol_table.enterScope();
    
    // Add parameters to symbol table and JIT mapping
    for (size_t i = 0; i < stmt->params.size(); ++i) {
        const auto& [param_name, param_type] = stmt->params[i];
        TypePtr symbol_type = convert_ast_type(param_type);
        m_symbol_table.addVariable(param_name, symbol_type, stmt->line);
        m_variable_lvalues[param_name] = func.get_param(i);
    }

    visit(stmt->body);

    // If function doesn't end with a return statement, add one
    if (!stmt->body->statements.empty()) {
        auto last_stmt = stmt->body->statements.back();
        if (!std::dynamic_pointer_cast<AST::ReturnStatement>(last_stmt)) {
            // Add implicit return for void functions
            m_current_block.end_with_return();
        }
    } else {
        // Empty function body, add implicit return
        m_current_block.end_with_return();
    }

    // Exit function scope
    m_symbol_table.exitScope();
    m_current_block = prev_block;
    m_current_func = prev_func;
}

void JitBackend::visit(const std::shared_ptr<AST::ReturnStatement>& stmt) {
    if (stmt->value) {
        gccjit::rvalue rvalue = visit_expr(stmt->value);
        m_current_block.end_with_return(rvalue);
    } else {
        m_current_block.end_with_return();
    }
}

gccjit::type JitBackend::get_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type) {
    if (!type) {
        return m_void_type;
    }

    // Create a Type object from the annotation
    Type t(TypeTag::Nil); // Default to Nil
    if (type->isList) {
        t.isList = true;
    }
    if(type->isDict){
        t.isDict = true;
    }

    // Mapping from string to TypeTag
    static const std::map<std::string, TypeTag> typeMap = {
        {"int", TypeTag::Int},
        {"float", TypeTag::Float64},
        {"bool", TypeTag::Bool},
        {"str", TypeTag::String},
        {"i8", TypeTag::Int8},
        {"i16", TypeTag::Int16},
        {"i32", TypeTag::Int32},
        {"i64", TypeTag::Int64},
        {"u8", TypeTag::UInt8},
        {"u16", TypeTag::UInt16},
        {"u32", TypeTag::UInt32},
        {"u64", TypeTag::UInt64},
        {"f32", TypeTag::Float32},
        {"f64", TypeTag::Float64}
    };

    auto it = typeMap.find(type->typeName);
    if (it != typeMap.end()) {
        t.tag = it->second;
    } else if (m_class_types.count(type->typeName)) {
        gcc_jit_type* c_class_type = m_class_types.at(type->typeName);
        // Wrap the C type back into C++ type
        return gccjit::type(c_class_type).get_pointer();
    } else {
        throw std::runtime_error("Unsupported type for JIT: " + type->typeName);
    }
    
    switch (t.tag) {
        case TypeTag::Int: return m_int_type;
        case TypeTag::Float64: return m_double_type;
        case TypeTag::Bool: return m_bool_type;
        case TypeTag::String: return m_const_char_ptr_type;
        case TypeTag::Int8: return m_int8_type;
        case TypeTag::Int16: return m_int16_type;
        case TypeTag::Int32: return m_int32_type;
        case TypeTag::Int64: return m_int64_type;
        case TypeTag::UInt8: return m_uint8_type;
        case TypeTag::UInt16: return m_uint16_type;
        case TypeTag::UInt32: return m_uint32_type;
        case TypeTag::UInt64: return m_uint64_type;
        case TypeTag::Float32: return m_float_type;
        default: throw std::runtime_error("Unsupported type for JIT: " + type->typeName);
    }
}

void JitBackend::visit(const std::shared_ptr<AST::WhileStatement>& stmt) {
    gccjit::block cond_block = m_current_func.new_block("while_cond");
    gccjit::block body_block = m_current_func.new_block("while_body");
    gccjit::block after_block = m_current_func.new_block("after_while");

    m_loop_blocks.push_back({cond_block, after_block});

    m_current_block.end_with_jump(cond_block);
    
    m_current_block = cond_block;
    gccjit::rvalue condition = visit_expr(stmt->condition);
    m_current_block.end_with_conditional(condition, body_block, after_block);

    m_current_block = body_block;
    visit(stmt->body);
    m_current_block.end_with_jump(cond_block);

    m_current_block = after_block;
    m_loop_blocks.pop_back();
}

void JitBackend::visit(const std::shared_ptr<AST::BlockStatement>& stmt) {
    m_symbol_table.enterScope();
    for (const auto& block_stmt : stmt->statements) {
        visit(block_stmt);
    }
    m_symbol_table.exitScope();
}

void JitBackend::visit(const std::shared_ptr<AST::PrintStatement>& stmt) {
    for (const auto& arg : stmt->arguments) {
        gccjit::rvalue rvalue = visit_expr(arg);
        gccjit::type type = rvalue.get_type();
        // Get the underlying C objects for type comparison
        gcc_jit_context* c_ctx = m_context.get_inner_context();
        gcc_jit_type* c_type = type.get_inner_type();
        gcc_jit_type* c_int_type = m_int_type.get_inner_type();
        gcc_jit_type* c_int8_type = m_int8_type.get_inner_type();
        gcc_jit_type* c_int16_type = m_int16_type.get_inner_type();
        gcc_jit_type* c_int32_type = m_int32_type.get_inner_type();
        gcc_jit_type* c_int64_type = m_int64_type.get_inner_type();
        gcc_jit_type* c_uint8_type = m_uint8_type.get_inner_type();
        gcc_jit_type* c_uint16_type = m_uint16_type.get_inner_type();
        gcc_jit_type* c_uint32_type = m_uint32_type.get_inner_type();
        gcc_jit_type* c_uint64_type = m_uint64_type.get_inner_type();
        gcc_jit_type* c_double_type = m_double_type.get_inner_type();
        gcc_jit_type* c_long_double_type = m_long_double_type.get_inner_type();
        gcc_jit_type* c_float_type = m_float_type.get_inner_type();
        gcc_jit_type* c_bool_type = m_bool_type.get_inner_type();
        gcc_jit_type* c_const_char_ptr_type = m_const_char_ptr_type.get_inner_type();
        gcc_jit_type* c_void_type = m_void_type.get_inner_type();
        
        // Special handling for booleans
        if (c_type == c_bool_type) {
            // Create blocks for conditional boolean printing
            gccjit::block true_block = m_current_func.new_block("bool_true");
            gccjit::block false_block = m_current_func.new_block("bool_false");
            gccjit::block after_block = m_current_func.new_block("after_bool");
            
            // Create string literals for "true" and "false"
            gcc_jit_rvalue* c_true_str = gcc_jit_context_new_string_literal(c_ctx, "true\n");
            gcc_jit_rvalue* c_false_str = gcc_jit_context_new_string_literal(c_ctx, "false\n");
            gccjit::rvalue true_str = gccjit::rvalue(c_true_str);
            gccjit::rvalue false_str = gccjit::rvalue(c_false_str);
            
            // Conditional jump based on boolean value
            m_current_block.end_with_conditional(rvalue, true_block, false_block);
            
            // True block
            m_current_block = true_block;
            std::vector<gccjit::rvalue> true_args;
            true_args.push_back(true_str);
            m_current_block.add_eval(m_context.new_call(m_printf_func, true_args));
            m_current_block.end_with_jump(after_block);
            
            // False block
            m_current_block = false_block;
            std::vector<gccjit::rvalue> false_args;
            false_args.push_back(false_str);
            m_current_block.add_eval(m_context.new_call(m_printf_func, false_args));
            m_current_block.end_with_jump(after_block);
            
            // Continue with after block
            m_current_block = after_block;
        } else {
            const char* format_str;
            if (c_type == c_int_type || c_type == c_int8_type || c_type == c_int16_type || c_type == c_int32_type || c_type == c_int64_type) {
                format_str = "%ld\n";
            } else if (c_type == c_uint8_type || c_type == c_uint16_type || c_type == c_uint32_type) {
                format_str = "%u\n";
            } else if (c_type == c_uint64_type) {
                // Use proper format for uint64_t on different platforms
                #ifdef _WIN32
                    format_str = "%llu\n";  // Windows uses %llu for uint64_t
                #else
                    format_str = "%lu\n";   // Unix uses %lu for uint64_t
                #endif
            } else if (c_type == c_double_type || c_type == c_long_double_type) {
                format_str = "%Lf\n";
            } else if (c_type == c_float_type) {
                format_str = "%f\n";
            } else if (c_type == c_const_char_ptr_type) {
                format_str = "%s\n";
            } else if (c_type == c_void_type) {
                format_str = "(nil)\n";
            } else {
                format_str = "%p\n";
            }
            // Use C API to create string literal
            gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(c_ctx, format_str);
            gccjit::rvalue format = gccjit::rvalue(c_format);
            std::vector<gccjit::rvalue> args;
            args.push_back(format);
            args.push_back(rvalue);
            m_current_block.add_eval(m_context.new_call(m_printf_func, args));
        }
    }
}

void JitBackend::visit(const std::shared_ptr<AST::IfStatement>& stmt) {
    gccjit::rvalue condition = visit_expr(stmt->condition);
    gccjit::block then_block = m_current_func.new_block("then");
    gccjit::block else_block = m_current_func.new_block("else");
    gccjit::block after_block = m_current_func.new_block("after");
    
    m_current_block.end_with_conditional(condition, then_block, else_block);

    m_current_block = then_block;
    visit(stmt->thenBranch);
    m_current_block.end_with_jump(after_block);

    m_current_block = else_block;
    if (stmt->elseBranch) {
        visit(stmt->elseBranch);
    }
    m_current_block.end_with_jump(after_block);

    m_current_block = after_block;
}

void JitBackend::visit(const std::shared_ptr<AST::BreakStatement>& stmt) {
    if (m_loop_blocks.empty()) {
        throw std::runtime_error("Break statement outside of loop");
    }
    m_current_block.end_with_jump(m_loop_blocks.back().second);
}

void JitBackend::visit(const std::shared_ptr<AST::ContinueStatement>& stmt) {
    if (m_loop_blocks.empty()) {
        throw std::runtime_error("Continue statement outside of loop");
    }
    m_current_block.end_with_jump(m_loop_blocks.back().first);
}

void JitBackend::visit(const std::shared_ptr<AST::IterStatement>& stmt) {
    if (stmt->loopVars.size() != 1) {
        throw std::runtime_error("JIT only supports single variable iter loops");
    }

    auto range_expr = std::dynamic_pointer_cast<AST::RangeExpr>(stmt->iterable);
    if (!range_expr) {
        throw std::runtime_error("JIT only supports range-based iter loops");
    }

    // Enter new scope for iter loop
    m_symbol_table.enterScope();

    // Initializer
    gccjit::lvalue i = m_current_func.new_local(m_int_type, stmt->loopVars[0].c_str());
    TypePtr int_type = std::make_shared<Type>(TypeTag::Int32);
    m_symbol_table.addVariable(stmt->loopVars[0], int_type, stmt->line);
    m_variable_lvalues[stmt->loopVars[0]] = i;
    gccjit::rvalue start = visit_expr(range_expr->start);
    m_current_block.add_assignment(i, start);

    gccjit::block cond_block = m_current_func.new_block("iter_cond");
    gccjit::block body_block = m_current_func.new_block("iter_body");
    gccjit::block increment_block = m_current_func.new_block("iter_increment");
    gccjit::block after_block = m_current_func.new_block("after_iter");

    m_loop_blocks.push_back({increment_block, after_block});

    m_current_block.end_with_jump(cond_block);

    // Condition
    m_current_block = cond_block;
    gccjit::rvalue end = visit_expr(range_expr->end);
    enum gcc_jit_comparison op = range_expr->inclusive ? GCC_JIT_COMPARISON_LE : GCC_JIT_COMPARISON_LT;
    gccjit::rvalue condition = m_context.new_comparison(op, i, end);
    m_current_block.end_with_conditional(condition, body_block, after_block);

    // Body
    m_current_block = body_block;
    visit(stmt->body);
    m_current_block.end_with_jump(increment_block);

    // Increment
    m_current_block = increment_block;
    gccjit::rvalue step = range_expr->step ? visit_expr(range_expr->step) : m_context.new_rvalue(m_int_type, 1);
    m_current_block.add_assignment_op(i, GCC_JIT_BINARY_OP_PLUS, step);
    m_current_block.end_with_jump(cond_block);

    m_current_block = after_block;
    
    // Exit scope
    m_symbol_table.exitScope();
    m_loop_blocks.pop_back();
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::Expression>& expr) {
    if (auto e = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::CallExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) return visit_expr(e);
    if (auto e = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) return visit_expr(e);
    throw std::runtime_error("Unsupported expression type for JIT");
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    gccjit::rvalue left = visit_expr(expr->left);
    gccjit::rvalue right = visit_expr(expr->right);

    gccjit::type left_type = left.get_type();
    gccjit::type right_type = right.get_type();

    // Get the underlying C objects for type comparison
    gcc_jit_type* c_left_type = left_type.get_inner_type();
    gcc_jit_type* c_right_type = right_type.get_inner_type();
    gcc_jit_type* c_const_char_ptr_type = m_const_char_ptr_type.get_inner_type();
    
    if (c_left_type == c_const_char_ptr_type && c_right_type == c_const_char_ptr_type) {
        if (expr->op == TokenType::EQUAL_EQUAL || expr->op == TokenType::BANG_EQUAL) {
            std::vector<gccjit::rvalue> args;
            args.push_back(left);
            args.push_back(right);
            gccjit::rvalue result = m_context.new_call(m_strcmp_func, args);
            gccjit::rvalue zero = m_context.new_rvalue(m_int_type, 0);
            if (expr->op == TokenType::EQUAL_EQUAL) {
                return m_context.new_comparison(GCC_JIT_COMPARISON_EQ, result, zero);
            } else {
                return m_context.new_comparison(GCC_JIT_COMPARISON_NE, result, zero);
            }
        } else if (expr->op == TokenType::PLUS) {
            // String concatenation using strcat
            // First, calculate total length needed
            std::vector<gccjit::rvalue> strlen_args;
            strlen_args.push_back(left);
            gccjit::rvalue left_len = m_context.new_call(m_strlen_func, strlen_args);
            
            strlen_args.clear();
            strlen_args.push_back(right);
            gccjit::rvalue right_len = m_context.new_call(m_strlen_func, strlen_args);
            
            gccjit::rvalue total_len = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_context.get_type(GCC_JIT_TYPE_SIZE_T), left_len, right_len);
            gccjit::rvalue total_len_plus_one = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_context.get_type(GCC_JIT_TYPE_SIZE_T), total_len, m_context.new_rvalue(m_context.get_type(GCC_JIT_TYPE_SIZE_T), 1));
            
            // Allocate memory for concatenated string
            gccjit::rvalue result_ptr = m_context.new_call(m_malloc_func, {total_len_plus_one});
            gccjit::rvalue result_ptr_cast = m_context.new_cast(result_ptr, m_const_char_ptr_type);
            
            // Copy left string
            std::vector<gccjit::rvalue> strcpy_args;
            strcpy_args.push_back(result_ptr_cast);
            strcpy_args.push_back(left);
            m_context.new_call(m_strcpy_func, strcpy_args);
            
            // Concatenate right string
            std::vector<gccjit::rvalue> strcat_args;
            strcat_args.push_back(result_ptr_cast);
            strcat_args.push_back(right);
            m_context.new_call(m_strcat_func, strcat_args);
            
            return result_ptr_cast;
        }
    }

    // Cast to common type if needed
    if (c_left_type != c_right_type) {
        // Prefer the larger type for arithmetic operations
        if (is_arithmetic_op(expr->op)) {
            gccjit::type common_type = get_common_type(left_type, right_type);
            if (c_left_type != common_type.get_inner_type()) {
                left = m_context.new_cast(left, common_type);
            }
            if (c_right_type != common_type.get_inner_type()) {
                right = m_context.new_cast(right, common_type);
            }
        }
    }

    switch (expr->op) {
        case TokenType::PLUS:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, left.get_type(), left, right);
        case TokenType::MINUS:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MINUS, left.get_type(), left, right);
        case TokenType::STAR:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, left.get_type(), left, right);
        case TokenType::SLASH:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_DIVIDE, left.get_type(), left, right);
        case TokenType::MODULUS:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MODULO, left.get_type(), left, right);
        case TokenType::EQUAL_EQUAL:
            return m_context.new_comparison(GCC_JIT_COMPARISON_EQ, left, right);
        case TokenType::BANG_EQUAL:
            return m_context.new_comparison(GCC_JIT_COMPARISON_NE, left, right);
        case TokenType::LESS:
            return m_context.new_comparison(GCC_JIT_COMPARISON_LT, left, right);
        case TokenType::LESS_EQUAL:
            return m_context.new_comparison(GCC_JIT_COMPARISON_LE, left, right);
        case TokenType::GREATER:
            return m_context.new_comparison(GCC_JIT_COMPARISON_GT, left, right);
        case TokenType::GREATER_EQUAL:
            return m_context.new_comparison(GCC_JIT_COMPARISON_GE, left, right);
        case TokenType::AND:
        {
            gccjit::block on_true = m_current_func.new_block("on_true");
            gccjit::block on_false = m_current_func.new_block("on_false");
            gccjit::block after = m_current_func.new_block("after");
            gccjit::lvalue result = m_current_func.new_local(m_bool_type, "and_result");

            m_current_block.end_with_conditional(left, on_true, on_false);

            m_current_block = on_true;
            m_current_block.add_assignment(result, right);
            m_current_block.end_with_jump(after);

            m_current_block = on_false;
            m_current_block.add_assignment(result, m_context.new_rvalue(m_bool_type, 0));
            m_current_block.end_with_jump(after);

            m_current_block = after;
            return result;
        }
        case TokenType::OR:
        {
            gccjit::block on_true = m_current_func.new_block("on_true");
            gccjit::block on_false = m_current_func.new_block("on_false");
            gccjit::block after = m_current_func.new_block("after");
            gccjit::lvalue result = m_current_func.new_local(m_bool_type, "or_result");

            m_current_block.end_with_conditional(left, on_true, on_false);

            m_current_block = on_true;
            m_current_block.add_assignment(result, m_context.new_rvalue(m_bool_type, 1));
            m_current_block.end_with_jump(after);

            m_current_block = on_false;
            m_current_block.add_assignment(result, right);
            m_current_block.end_with_jump(after);

            m_current_block = after;
            return result;
        }
        default:
            throw std::runtime_error("Unsupported binary operator for JIT");
    }
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::UnaryExpr>& expr) {
    gccjit::rvalue right = visit_expr(expr->right);
    enum gcc_jit_unary_op op;
    switch (expr->op) {
        case TokenType::MINUS: op = GCC_JIT_UNARY_OP_MINUS; break;
        case TokenType::PLUS: return right; // Unary plus does nothing
        case TokenType::BANG: op = GCC_JIT_UNARY_OP_LOGICAL_NEGATE; break;
        default: throw std::runtime_error("Unsupported unary operator for JIT");
    }
    return m_context.new_unary_op(op, right.get_type(), right);
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::LiteralExpr>& expr) {
    if (std::holds_alternative<std::string>(expr->value)) {
        std::string value = std::get<std::string>(expr->value);
        
        // Determine if this is a numeric or string literal
        // Numeric literals start with digit, +, or -, and may contain decimal point or scientific notation
        // String literals can contain any characters but don't start like numbers
        bool isNumeric = false;
        if (!value.empty()) {
            char first = value[0];
            if (std::isdigit(first) || first == '+' || first == '-') {
                isNumeric = true;
            }
        }
        
        if (isNumeric) {
            // Try to parse as number
            try {
                bool hasDecimal = value.find('.') != std::string::npos;
                bool hasScientific = value.find('e') != std::string::npos || value.find('E') != std::string::npos;
                
                if (hasDecimal || hasScientific) {
                    // Floating point literal
                    return m_context.new_rvalue(m_double_type, std::stod(value));
                } else {
                    // Integer literal - try unsigned first for large values
                    try {
                        unsigned long long uint_val = std::stoull(value);
                        
                        // Use appropriate integer type based on value size
                        if (uint_val > 0xFFFFFFFF) {
                            // For uint64 values, handle large values using bitwise operations
                            gcc_jit_context* c_ctx = m_context.get_inner_context();
                            gcc_jit_type* c_uint64_type = m_uint64_type.get_inner_type();
                            
                            if (uint_val <= INT_MAX) {
                                // Values that fit in signed int - safe to use int function
                                gcc_jit_rvalue* c_val = gcc_jit_context_new_rvalue_from_int(c_ctx, c_uint64_type, static_cast<int>(uint_val));
                                return gccjit::rvalue(c_val);
                            } else {
                                // For very large unsigned values, construct using bitwise operations
                                // Split into high and low 32-bit parts
                                uint32_t high = static_cast<uint32_t>(uint_val >> 32);
                                uint32_t low = static_cast<uint32_t>(uint_val & 0xFFFFFFFF);
                                
                                // Create low part
                                gcc_jit_rvalue* c_low = gcc_jit_context_new_rvalue_from_int(c_ctx, c_uint64_type, low);
                                gccjit::rvalue low_val = gccjit::rvalue(c_low);
                                
                                // Create high part and shift left
                                gcc_jit_rvalue* c_high = gcc_jit_context_new_rvalue_from_int(c_ctx, c_uint64_type, high);
                                gccjit::rvalue high_val = gccjit::rvalue(c_high);
                                gccjit::rvalue shift_val = m_context.new_rvalue(m_uint64_type, 32);
                                gccjit::rvalue shifted_high = m_context.new_binary_op(GCC_JIT_BINARY_OP_LSHIFT, m_uint64_type, high_val, shift_val);
                                
                                // Combine with bitwise OR
                                gccjit::rvalue result = m_context.new_binary_op(GCC_JIT_BINARY_OP_BITWISE_OR, m_uint64_type, low_val, shifted_high);
                                return result;
                            }
                        } else {
                            // For values that fit in int range, use int type
                            if (uint_val <= INT_MAX) {
                                gcc_jit_context* c_ctx = m_context.get_inner_context();
                                gcc_jit_type* c_int_type = m_int_type.get_inner_type();
                                gcc_jit_rvalue* c_val = gcc_jit_context_new_rvalue_from_int(c_ctx, c_int_type, static_cast<int>(uint_val));
                                return gccjit::rvalue(c_val);
                            } else if (uint_val > 0xFFFF) {
                                // Use C API for uint32 values  
                                gcc_jit_context* c_ctx = m_context.get_inner_context();
                                gcc_jit_type* c_uint32_type = m_uint32_type.get_inner_type();
                                gcc_jit_rvalue* c_val = gcc_jit_context_new_rvalue_from_int(c_ctx, c_uint32_type, static_cast<int>(uint_val));
                                return gccjit::rvalue(c_val);
                            } else if (uint_val > 0xFF) {
                                // Use C API for uint16 values
                                gcc_jit_context* c_ctx = m_context.get_inner_context();
                                gcc_jit_type* c_uint16_type = m_uint16_type.get_inner_type();
                                gcc_jit_rvalue* c_val = gcc_jit_context_new_rvalue_from_int(c_ctx, c_uint16_type, static_cast<int>(uint_val));
                                return gccjit::rvalue(c_val);
                            } else {
                                // Use C API for uint8 values
                                gcc_jit_context* c_ctx = m_context.get_inner_context();
                                gcc_jit_type* c_uint8_type = m_uint8_type.get_inner_type();
                                gcc_jit_rvalue* c_val = gcc_jit_context_new_rvalue_from_int(c_ctx, c_uint8_type, static_cast<int>(uint_val));
                                return gccjit::rvalue(c_val);
                            }
                        }
                    } catch (const std::out_of_range&) {
                        // If too large for unsigned, try signed (for negative numbers)
                        long long int_val = std::stoll(value);
                        // Use C API for int64 values
                        gcc_jit_context* c_ctx = m_context.get_inner_context();
                        gcc_jit_type* c_int64_type = m_int64_type.get_inner_type();
                        gcc_jit_rvalue* c_val = gcc_jit_context_new_rvalue_from_long(c_ctx, c_int64_type, int_val);
                        return gccjit::rvalue(c_val);
                    }
                }
            } catch (const std::exception&) {
                // If parsing fails, fall through to treat as string
            }
        }
        
        // Treat as string literal
        gcc_jit_context* c_ctx = m_context.get_inner_context();
        gcc_jit_rvalue* c_str = gcc_jit_context_new_string_literal(c_ctx, value.c_str());
        return gccjit::rvalue(c_str);
    }
    if (std::holds_alternative<bool>(expr->value)) {
        return m_context.new_rvalue(m_bool_type, std::get<bool>(expr->value));
    }
    if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        // Create a null pointer value - use C API
        gcc_jit_context* c_ctx = m_context.get_inner_context();
        gcc_jit_type* c_void_ptr_type = m_void_type.get_pointer().get_inner_type();
        gcc_jit_rvalue* c_null = gcc_jit_context_null(c_ctx, c_void_ptr_type);
        return gccjit::rvalue(c_null);
    }
    // Add other literal types here
    return gccjit::rvalue();
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::VariableExpr>& expr) {
    // Look up variable in symbol table
    Symbol* symbol = m_symbol_table.findVariable(expr->name);
    if (!symbol) {
        throw std::runtime_error("Unknown variable: " + expr->name);
    }
    
    // Get the JIT lvalue from our mapping
    auto it = m_variable_lvalues.find(expr->name);
    if (it == m_variable_lvalues.end()) {
        throw std::runtime_error("Variable not found in JIT mapping: " + expr->name);
    }
    
    return it->second;
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::MemberExpr>& expr) {
    gccjit::rvalue object = visit_expr(expr->object);
    gccjit::lvalue object_lvalue = object.dereference();
    gccjit::type struct_type = object_lvalue.get_type();
    
    // Check if this is a struct type using C API
    gcc_jit_type* c_struct_type = struct_type.get_inner_type();
    gcc_jit_struct* class_struct_ptr = gcc_jit_type_is_struct(c_struct_type);
    if (!class_struct_ptr) {
        throw std::runtime_error("Not a struct type");
    }

    // Find the mangled name by searching m_class_types
    std::string mangled_name;
    for (const auto& [name, type] : m_class_types) {
        // Get the underlying C objects
        gcc_jit_type* c_type = type;
        gcc_jit_type* c_struct_type = struct_type.get_inner_type();
        if (c_type == c_struct_type) {
            mangled_name = name;
            break;
        }
    }
    
    if (mangled_name.empty()) {
        throw std::runtime_error("Unknown struct type");
    }
    
    const auto& field_names = m_struct_field_names[mangled_name];
    const auto& fields = m_class_fields[mangled_name];
    
    for (size_t i = 0; i < field_names.size(); ++i) {
        if (field_names[i] == expr->name) {
            gccjit::field field = fields[i];
            return object_lvalue.access_field(field);
        }
    }

    throw std::runtime_error("Unknown member: " + expr->name);
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::AssignExpr>& expr) {
    gccjit::rvalue rvalue = visit_expr(expr->value);
    
    // Look up variable in symbol table
    Symbol* symbol = m_symbol_table.findVariable(expr->name);
    if (!symbol) {
        throw std::runtime_error("Unknown variable: " + expr->name);
    }
    
    // Get the JIT lvalue from our mapping
    auto it = m_variable_lvalues.find(expr->name);
    if (it == m_variable_lvalues.end()) {
        throw std::runtime_error("Variable not found in JIT mapping: " + expr->name);
    }
    
    gccjit::lvalue lvalue = it->second;
    
    // Cast to the correct type if needed
    if (rvalue.get_type().get_inner_type() != lvalue.get_type().get_inner_type()) {
        rvalue = m_context.new_cast(rvalue, lvalue.get_type());
    }
    
    m_current_block.add_assignment(lvalue, rvalue);
    return rvalue;
}

bool JitBackend::is_arithmetic_op(TokenType op) {
    return op == TokenType::PLUS || op == TokenType::MINUS || 
           op == TokenType::STAR || op == TokenType::SLASH;
}

gccjit::type JitBackend::get_common_type(gccjit::type type1, gccjit::type type2) {
    // Simple type promotion rules
    // If types are the same, return that type
    if (type1.get_inner_type() == type2.get_inner_type()) {
        return type1;
    }
    
    // Prefer double over float
    if (type1.get_inner_type() == m_double_type.get_inner_type() || 
        type2.get_inner_type() == m_double_type.get_inner_type()) {
        return m_double_type;
    }
    
    // If one is float and the other is integer, prefer float
    if (type1.get_inner_type() == m_float_type.get_inner_type() || 
        type2.get_inner_type() == m_float_type.get_inner_type()) {
        return m_float_type;
    }
    
    // Prefer larger integer types
    if (type1.get_inner_type() == m_int64_type.get_inner_type() || 
        type2.get_inner_type() == m_int64_type.get_inner_type()) {
        return m_int64_type;
    }
    
    if (type1.get_inner_type() == m_int32_type.get_inner_type() || 
        type2.get_inner_type() == m_int32_type.get_inner_type()) {
        return m_int32_type;
    }
    
    if (type1.get_inner_type() == m_int16_type.get_inner_type() || 
        type2.get_inner_type() == m_int16_type.get_inner_type()) {
        return m_int16_type;
    }
    
    // Default to int
    return m_int_type;
}

gccjit::type JitBackend::convert_builtin_type(TypeTag tag) {
    switch (tag) {
        case TypeTag::Nil: return m_void_type;
        case TypeTag::Bool: return m_bool_type;
        case TypeTag::Int: 
        case TypeTag::Int32: return m_int32_type;
        case TypeTag::Int8: return m_int8_type;
        case TypeTag::Int16: return m_int16_type;
        case TypeTag::Int64: return m_int64_type;
        case TypeTag::Int128: return m_int64_type; // Use int64 for int128 for now
        case TypeTag::UInt:
        case TypeTag::UInt32: return m_uint32_type;
        case TypeTag::UInt8: return m_uint8_type;
        case TypeTag::UInt16: return m_uint16_type;
        case TypeTag::UInt64: return m_uint64_type;
        case TypeTag::UInt128: return m_uint64_type; // Use uint64 for uint128 for now
        case TypeTag::Float32: return m_float_type;
        case TypeTag::Float64: return m_double_type;
        case TypeTag::String: return m_const_char_ptr_type;
        case TypeTag::List: return m_void_ptr_type; // Use void* for List type
        case TypeTag::Function: return m_void_ptr_type; // Use void* for Function type
        case TypeTag::Any: return m_void_ptr_type; // Use void* for Any type
        default: return m_void_type; // Default to void for unsupported types
    }
}

void JitBackend::register_builtin_functions() {
    auto& builtins = builtin::BuiltinFunctions::getInstance();
    auto implementations = builtins.getAllBuiltinImplementations();
    
    for (const auto& [name, impl] : implementations) {
        const auto* def = builtins.getBuiltinDefinition(name);
        if (!def) continue;
        
        // Convert parameter types
        std::vector<gccjit::param> params;
        std::vector<TypePtr> param_types;
        for (const auto& paramType : def->parameterTypes) {
            gccjit::type jit_type = convert_builtin_type(paramType);
            if (!jit_type.get_inner_type()) {
                throw std::runtime_error("Failed to convert builtin param type for: " + name);
            }
            // Skip void parameter types - they're not valid in function parameters
            if (jit_type.get_inner_type() != m_void_type.get_inner_type()) {
                params.push_back(m_context.new_param(jit_type, ("param_" + std::to_string(params.size())).c_str()));
                param_types.push_back(convert_jit_type(jit_type));
            }
        }
        
        // Convert return type
        gccjit::type return_type = convert_builtin_type(def->returnType);
        if (!return_type.get_inner_type()) {
            throw std::runtime_error("Failed to convert builtin return type for: " + name);
        }
        TypePtr return_type_ptr = convert_jit_type(return_type);
        
        // Create function
        std::string mangled_name = mangle(name);
        auto func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, return_type, mangled_name.c_str(), params, 0);
        m_functions[mangled_name] = func;
        
        // Add to symbol table
        FunctionSignature signature(name, param_types, return_type_ptr);
        m_symbol_table.addFunction(name, signature);
    }
}

TypePtr JitBackend::convert_ast_type(const std::shared_ptr<AST::TypeAnnotation>& ast_type) {
    if (!ast_type) return std::make_shared<Type>(TypeTag::Any);
    
    // Use the typeName field from TypeAnnotation
    const std::string& type_name = ast_type->typeName;
    
    if (type_name == "void") return std::make_shared<Type>(TypeTag::Nil);
    if (type_name == "bool") return std::make_shared<Type>(TypeTag::Bool);
    if (type_name == "int" || type_name == "i32") return std::make_shared<Type>(TypeTag::Int32);
    if (type_name == "i8") return std::make_shared<Type>(TypeTag::Int8);
    if (type_name == "i16") return std::make_shared<Type>(TypeTag::Int16);
    if (type_name == "i64") return std::make_shared<Type>(TypeTag::Int64);
    if (type_name == "u8") return std::make_shared<Type>(TypeTag::UInt8);
    if (type_name == "u16") return std::make_shared<Type>(TypeTag::UInt16);
    if (type_name == "u32") return std::make_shared<Type>(TypeTag::UInt32);
    if (type_name == "u64") return std::make_shared<Type>(TypeTag::UInt64);
    if (type_name == "f32") return std::make_shared<Type>(TypeTag::Float32);
    if (type_name == "f64") return std::make_shared<Type>(TypeTag::Float64);
    if (type_name == "str") return std::make_shared<Type>(TypeTag::String);
    
    return std::make_shared<Type>(TypeTag::Any);
}

TypePtr JitBackend::convert_jit_type(gccjit::type jit_type) {
    auto inner = jit_type.get_inner_type();
    if (inner == m_void_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Nil);
    if (inner == m_bool_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Bool);
    if (inner == m_int_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Int32);
    if (inner == m_int8_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Int8);
    if (inner == m_int16_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Int16);
    if (inner == m_int64_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Int64);
    if (inner == m_uint8_type.get_inner_type()) return std::make_shared<Type>(TypeTag::UInt8);
    if (inner == m_uint16_type.get_inner_type()) return std::make_shared<Type>(TypeTag::UInt16);
    if (inner == m_uint32_type.get_inner_type()) return std::make_shared<Type>(TypeTag::UInt32);
    if (inner == m_uint64_type.get_inner_type()) return std::make_shared<Type>(TypeTag::UInt64);
    if (inner == m_float_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Float32);
    if (inner == m_double_type.get_inner_type()) return std::make_shared<Type>(TypeTag::Float64);
    if (inner == m_const_char_ptr_type.get_inner_type()) return std::make_shared<Type>(TypeTag::String);
    
    return std::make_shared<Type>(TypeTag::Any);
}
