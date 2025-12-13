#include "jit_backend.hh"
#include <functional>
#include <iostream>
#include "value.hh"

JitBackend::JitBackend() : m_region(m_mem_manager), m_context(gccjit::context::acquire()) {
    // Get types
    m_void_type = m_context.get_type(GCC_JIT_TYPE_VOID);
    m_int_type = m_context.get_type(GCC_JIT_TYPE_INT);
    m_double_type = m_context.get_type(GCC_JIT_TYPE_DOUBLE);
    m_bool_type = m_context.get_type(GCC_JIT_TYPE_BOOL);
    m_const_char_ptr_type = m_context.get_type(GCC_JIT_TYPE_CONST_CHAR_PTR);

    m_int8_type = m_context.get_type(GCC_JIT_TYPE_INT8_T);
    m_int16_type = m_context.get_type(GCC_JIT_TYPE_INT16_T);
    m_int32_type = m_context.get_type(GCC_JIT_TYPE_INT32_T);
    m_int64_type = m_context.get_type(GCC_JIT_TYPE_INT64_T);
    m_uint8_type = m_context.get_type(GCC_JIT_TYPE_UINT8_T);
    m_uint16_type = m_context.get_type(GCC_JIT_TYPE_UINT16_T);
    m_uint32_type = m_context.get_type(GCC_JIT_TYPE_UINT32_T);
    m_uint64_type = m_context.get_type(GCC_JIT_TYPE_UINT64_T);
    m_float_type = m_context.get_type(GCC_JIT_TYPE_FLOAT);
    m_long_double_type = m_context.get_type(GCC_JIT_TYPE_LONG_DOUBLE);

    // Get printf
    m_printf_func = m_context.get_builtin_function("printf");

    // Get strcmp
    std::vector<gccjit::param> strcmp_params;
    strcmp_params.push_back(m_context.new_param(m_const_char_ptr_type, "s1"));
    strcmp_params.push_back(m_context.new_param(m_const_char_ptr_type, "s2"));
    m_strcmp_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "strcmp", strcmp_params, 0);

    // Get malloc
    std::vector<gccjit::param> malloc_params;
    malloc_params.push_back(m_context.new_param(m_context.get_type(GCC_JIT_TYPE_SIZE_T), "size"));
    m_malloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type.get_pointer(), "malloc", malloc_params, 0);
}

void JitBackend::process(const std::vector<std::shared_ptr<AST::Program>>& programs) {
    // First pass: Create forward declarations for all functions
    for (const auto& program : programs) {
        for (const auto& stmt : program->statements) {
            if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
                std::vector<gccjit::param> params;
                for (const auto& p : func_decl->params) {
                    params.push_back(m_context.new_param(get_jit_type(p.second), p.first.c_str()));
                }
                gccjit::type return_type = get_jit_type(func_decl->returnType.value_or(nullptr));
                enum gcc_jit_function_kind kind = func_decl->visibility == AST::VisibilityLevel::Public ? GCC_JIT_FUNCTION_EXPORTED : GCC_JIT_FUNCTION_INTERNAL;
                std::string mangled_name = mangle(func_decl->name);
                gccjit::function func = m_context.new_function(kind, return_type, mangled_name.c_str(), params, 0);
                m_functions[mangled_name] = func;
            }
        }
    }

    // Create the main function
    m_main_func = m_context.new_function(GCC_JIT_FUNCTION_EXPORTED, m_int_type, "main", std::vector<gccjit::param>(), 0);
    m_current_func = m_main_func;
    m_current_block = m_current_func.new_block("entry");
    m_scopes.emplace_back();

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
    // Determine the type of the variable.
    // This will now correctly handle TypeTag enums.
    gccjit::type type = get_jit_type(stmt->type.value_or(nullptr));
    if (m_scopes.size() == 1) { // Global variable
        enum gcc_jit_global_kind kind = stmt->visibility == AST::VisibilityLevel::Public ? GCC_JIT_GLOBAL_EXPORTED : GCC_JIT_GLOBAL_INTERNAL;
        std::string mangled_name = mangle(stmt->name);
        gccjit::lvalue lvalue = m_context.new_global(kind, type, mangled_name.c_str());
        m_scopes.back()[mangled_name] = lvalue;
        if (stmt->initializer) {
            gccjit::rvalue rvalue = visit_expr(stmt->initializer);
            // TODO: Set initializer for global
        }
    } else { // Local variable
        gccjit::lvalue lvalue = m_current_func.new_local(type, stmt->name.c_str());
        m_scopes.back()[stmt->name] = lvalue;
        if (stmt->initializer) {
            gccjit::rvalue rvalue = visit_expr(stmt->initializer);
            m_current_block.add_assignment(lvalue, rvalue);
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

    gccjit::block cond_block = m_current_func.new_block("for_cond");
    gccjit::block body_block = m_current_func.new_block("for_body");
    gccjit::block increment_block = m_current_func.new_block("for_increment");
    gccjit::block after_block = m_current_func.new_block("after_for");

    m_loop_blocks.push_back({increment_block, after_block});

    m_current_block.end_with_jump(cond_block);

    m_current_block = cond_block;
    if (stmt->condition) {
        gccjit::rvalue condition = visit_expr(stmt->condition);
        m_current_block.end_with_conditional(condition, body_block, after_block);
    } else {
        m_current_block.end_with_jump(body_block);
    }

    m_current_block = body_block;
    visit(stmt->body);
    m_current_block.end_with_jump(increment_block);

    m_current_block = increment_block;
    if (stmt->increment) {
        visit_expr(stmt->increment);
    }
    m_current_block.end_with_jump(cond_block);

    m_current_block = after_block;
    m_scopes.pop_back();
    m_loop_blocks.pop_back();
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
    std::vector<gccjit::field> env_fields;
    for (const auto& var_name : captured_vars) {
        for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
            if (it->count(var_name)) {
                env_fields.push_back(m_context.new_field(it->at(var_name).get_type(), var_name.c_str()));
                break;
            }
        }
    }
    gccjit::struct_ env_struct = m_context.new_struct_type("env", env_fields);
    gccjit::type env_type = env_struct.as_type();

    gccjit::type func_ptr_type = m_void_type.get_pointer();
    std::vector<gccjit::field> fields;
    fields.push_back(m_context.new_field(func_ptr_type, "func_ptr"));
    fields.push_back(m_context.new_field(env_type.get_pointer(), "env"));
    gccjit::struct_ closure_struct = m_context.new_struct_type("closure", fields);
    gccjit::type closure_type = closure_struct.as_type();

    // Create the JIT function for the lambda
    std::vector<gccjit::param> params;
    params.push_back(m_context.new_param(m_void_type.get_pointer(), "env"));
    for (const auto& p : expr->params) {
        params.push_back(m_context.new_param(get_jit_type(p.second), p.first.c_str()));
    }
    gccjit::type return_type = get_jit_type(expr->returnType.value_or(nullptr));
    gccjit::function func = m_context.new_function(GCC_JIT_FUNCTION_INTERNAL, return_type, "lambda", params, 0);

    // Code generation for the lambda body
    gccjit::block prev_block = m_current_block;
    m_current_block = func.new_block("entry");

    m_scopes.emplace_back();
    for (size_t i = 1; i < params.size(); ++i) {
        m_scopes.back()[expr->params[i - 1].first] = func.get_param(i);
    }

    visit(expr->body);

    m_scopes.pop_back();
    m_current_block = prev_block;

    // Allocate and populate the closure struct
    gccjit::lvalue closure_lvalue = m_current_func.new_local(closure_type, "closure");
    
    // Allocate environment on the heap
    gccjit::rvalue size = m_context.new_rvalue(m_context.get_type(GCC_JIT_TYPE_SIZE_T), env_type.get_size());
    std::vector<gccjit::rvalue> args;
    args.push_back(size);
    gccjit::rvalue env_ptr = m_context.new_call(m_malloc_func, args);
    gccjit::lvalue env_lvalue = m_context.new_cast(env_ptr, env_type.get_pointer()).dereference();

    for (size_t i = 0; i < captured_vars.size(); ++i) {
        for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
            if (it->count(captured_vars[i])) {
                m_current_block.add_assignment(env_lvalue.access_field(env_fields[i]), it->at(captured_vars[i]));
                break;
            }
        }
    }
    
    // Allocate closure in the region
    m_current_block.add_assignment(closure_lvalue.access_field(fields[0]), func.get_address());
    m_current_block.add_assignment(closure_lvalue.access_field(fields[1]), env_ptr);

    return closure_lvalue;
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::CallExpr>& expr) {
    gccjit::rvalue callee = visit_expr(expr->callee);
    gccjit::type callee_type = callee.get_type();

    if (callee_type.is_struct()) {
        // Assume it's a closure
        gccjit::lvalue closure_lvalue = callee.dereference();
        gccjit::rvalue func_ptr = closure_lvalue.access_field(m_context.new_field(m_void_type.get_pointer(), "func_ptr"));
        gccjit::rvalue env = closure_lvalue.access_field(m_context.new_field(m_void_type.get_pointer(), "env"));

        std::vector<gccjit::rvalue> args;
        args.push_back(env);
        for (const auto& arg : expr->arguments) {
            args.push_back(visit_expr(arg));
        }
        return m_context.new_call_through_ptr(func_ptr, args);
    } else {
        auto member_expr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->callee);
        if (member_expr) {
            gccjit::rvalue object = visit_expr(member_expr->object);
            gccjit::lvalue object_lvalue = object.dereference();
            gccjit::type struct_type = object_lvalue.get_type();
            std::string class_name = m_type_names[struct_type];
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
        }

        auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee);
        if (!var_expr) {
            throw std::runtime_error("JIT only supports direct function calls");
        }

        std::string mangled_name = mangle(var_expr->name);
        if (m_functions.count(mangled_name)) {
            gccjit::function func = m_functions[mangled_name];
            std::vector<gccjit::rvalue> args;
            for (const auto& arg : expr->arguments) {
                args.push_back(visit_expr(arg));
            }
            return m_context.new_call(func, args);
        }

        if (m_class_types.count(mangled_name)) {
            gccjit::type class_type = m_class_types[mangled_name];
            gccjit::rvalue size = m_context.new_rvalue(m_context.get_type(GCC_JIT_TYPE_SIZE_T), class_type.get_size());
            std::vector<gccjit::rvalue> args;
            args.push_back(size);
            gccjit::rvalue instance = m_context.new_call(m_malloc_func, args);
            return m_context.new_cast(instance, class_type.get_pointer());
        }

        throw std::runtime_error("Unknown function or class: " + var_expr->name);
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
    gccjit::type class_type = class_struct.as_type();

    m_class_types[mangled_name] = class_type;
    m_type_names[class_type] = stmt->name;

    // Store field names for later lookup
    std::vector<std::string> field_names;
    for (const auto& field : stmt->fields) {
        field_names.push_back(field->name);
    }
    m_struct_field_names[class_struct] = field_names;

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
    gccjit::function func = m_functions[stmt->name];
    gccjit::function prev_func = m_current_func;
    m_current_func = func;
    gccjit::block prev_block = m_current_block;
    m_current_block = m_current_func.new_block("entry");

    m_scopes.emplace_back();
    for (size_t i = 0; i < stmt->params.size(); ++i) {
        m_scopes.back()[stmt->params[i].first] = func.get_param(i);
    }

    visit(stmt->body);

    m_scopes.pop_back();
    m_current_block = prev_block;
    m_current_func = prev_func;
}

void JitBackend::visit(const std::shared_ptr<AST::ReturnStatement>& stmt) {
    if (stmt->value) {
        gccjit::rvalue rvalue = visit_expr(stmt->value);
        m_current_block.end_with_return(rvalue);
    } else {
        m_current_block.end_with_void_return();
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
        return m_class_types.at(type->typeName).get_pointer();
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
    m_scopes.emplace_back();
    for (const auto& s : stmt->statements) {
        visit(s);
    }
    m_scopes.pop_back();
}

void JitBackend::visit(const std::shared_ptr<AST::PrintStatement>& stmt) {
    for (const auto& arg : stmt->arguments) {
        gccjit::rvalue rvalue = visit_expr(arg);
        gccjit::type type = rvalue.get_type();
        const char* format_str;
        if (type == m_int_type || type == m_int8_type || type == m_int16_type || type == m_int32_type || type == m_int64_type) {
            format_str = "%ld\n";
        } else if (type == m_uint8_type || type == m_uint16_type || type == m_uint32_type || type == m_uint64_type) {
            format_str = "%lu\n";
        } else if (type == m_double_type || type == m_long_double_type) {
            format_str = "%Lf\n";
        } else if (type == m_float_type) {
            format_str = "%f\n";
        } else if (type == m_bool_type) {
            format_str = "%s\n";
            // rvalue = m_context.new_conditional(rvalue, m_context.new_string_literal("true"), m_context.new_string_literal("false"));
        } else if (type == m_const_char_ptr_type) {
            format_str = "%s\n";
        } else if (type == m_void_type) {
            format_str = "nil\n";
            rvalue = m_context.new_string_literal("nil");
        } else {
            throw std::runtime_error("Unsupported type for print");
        }
        gccjit::rvalue format = m_context.new_string_literal(format_str);
        std::vector<gccjit::rvalue> args;
        args.push_back(format);
        args.push_back(rvalue);
        m_current_block.add_eval(m_context.new_call(m_printf_func, args));
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

    m_scopes.emplace_back();

    // Initializer
    gccjit::lvalue i = m_current_func.new_local(m_int_type, stmt->loopVars[0].c_str());
    m_scopes.back()[stmt->loopVars[0]] = i;
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
    m_scopes.pop_back();
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

    if (left_type == m_const_char_ptr_type && right_type == m_const_char_ptr_type) {
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
        case TokenType::BANG: op = GCC_JIT_UNARY_OP_LOGICAL_NEGATE; break;
        default: throw std::runtime_error("Unsupported unary operator for JIT");
    }
    return m_context.new_unary_op(op, right.get_type(), right);
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::LiteralExpr>& expr) {
    if (std::holds_alternative<BigInt>(expr->value)) {
        return m_context.new_rvalue(m_int_type, std::stoll(std::get<BigInt>(expr->value).to_string()));
    }
    if (std::holds_alternative<bool>(expr->value)) {
        return m_context.new_rvalue(m_bool_type, std::get<bool>(expr->value));
    }
    if (std::holds_alternative<std::string>(expr->value)) {
        return m_context.new_string_literal(std::get<std::string>(expr->value).c_str());
    }
    if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        return m_context.null(m_void_type);
    }
    // Add other literal types here
    return gccjit::rvalue();
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::VariableExpr>& expr) {
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
        auto& scope = *it;
        if (scope.count(expr->name)) {
            return scope[expr->name];
        }
    }
    throw std::runtime_error("Unknown variable: " + expr->name);
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::MemberExpr>& expr) {
    gccjit::rvalue object = visit_expr(expr->object);
    gccjit::lvalue object_lvalue = object.dereference();
    gccjit::type struct_type = object_lvalue.get_type();
    gccjit::struct_ class_struct = struct_type.is_struct();

    const auto& field_names = m_struct_field_names[class_struct];
    for (size_t i = 0; i < field_names.size(); ++i) {
        if (field_names[i] == expr->name) {
            gccjit::field field = class_struct.get_field(i);
            return object_lvalue.access_field(field);
        }
    }

    throw std::runtime_error("Unknown member: " + expr->name);
}

gccjit::rvalue JitBackend::visit_expr(const std::shared_ptr<AST::AssignExpr>& expr) {
    gccjit::rvalue rvalue = visit_expr(expr->value);
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
        auto& scope = *it;
        if (scope.count(expr->name)) {
            m_current_block.add_assignment(scope[expr->name], rvalue);
            return rvalue;
        }
    }
    throw std::runtime_error("Unknown variable: " + expr->name);
}
