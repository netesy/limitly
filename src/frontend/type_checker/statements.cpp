#include "../type_checker.hh"

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

TypePtr TypeChecker::check_statement(std::shared_ptr<LM::Frontend::AST::Statement> stmt) {
    if (!stmt) return nullptr;
    
    if (auto import_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ImportStatement>(stmt)) {
        return check_import_statement(import_stmt);
    } else if (auto func_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
        return check_function_declaration(func_decl);
    } else if (auto frame_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
        return check_frame_declaration(frame_decl);
    } else if (auto trait_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) {
        return check_trait_declaration(trait_decl);
    } else if (auto dest_decl = std::dynamic_pointer_cast<LM::Frontend::AST::DestructuringDeclaration>(stmt)) {
        return check_destructuring_declaration(dest_decl);
    } else if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
        return check_var_declaration(var_decl);
    } else if (auto type_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TypeDeclaration>(stmt)) {
        return check_type_declaration(type_decl);
    } else if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
        return check_block_statement(block);
    } else if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
        return check_if_statement(if_stmt);
    } else if (auto while_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WhileStatement>(stmt)) {
        return check_while_statement(while_stmt);
    } else if (auto for_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ForStatement>(stmt)) {
        return check_for_statement(for_stmt);
    } else if (auto parallel_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ParallelStatement>(stmt)) {
        return check_parallel_statement(parallel_stmt);
    } else if (auto concurrent_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ConcurrentStatement>(stmt)) {
        return check_concurrent_statement(concurrent_stmt);
    } else if (auto task_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::TaskStatement>(stmt)) {
        return check_task_statement(task_stmt);
    } else if (auto worker_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WorkerStatement>(stmt)) {
        return check_worker_statement(worker_stmt);
    } else if (auto return_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
        return check_return_statement(return_stmt);
    } else if (auto print_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::PrintStatement>(stmt)) {
        return check_print_statement(print_stmt);
    } else if (auto match_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::MatchStatement>(stmt)) {
        return check_match_statement(match_stmt);
    } else if (auto contract_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ContractStatement>(stmt)) {
        return check_contract_statement(contract_stmt);
    } else if (auto comptime_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ComptimeStatement>(stmt)) {
        // Strict phase separation: comptime evaluation is not allowed to consume runtime state
        // until a dedicated deterministic comptime evaluator is implemented.
        add_error("comptime statements are currently disabled: compile-time execution cannot depend on runtime values", comptime_stmt->line);
        return type_system.NIL_TYPE;
    } else if (auto unsafe_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::UnsafeStatement>(stmt)) {
        // Unsafe operations must always be explicitly scoped and validated; reject until
        // full unsafe memory-model checks are implemented in frontend + lowering + runtime.
        add_error("unsafe statements are currently disabled: explicit unsafe boundaries require full memory-model validation", unsafe_stmt->line);
        return type_system.NIL_TYPE;
    } else if (auto import_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ImportStatement>(stmt)) {
        return check_import_statement(import_stmt);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt)) {
        return check_expression(expr_stmt->expression);
    }
    
    return nullptr;
}

TypePtr TypeChecker::check_function_declaration(std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> func) {
    if (!func) return nullptr;
    
    // Enter new memory region for this function
    enter_memory_region();
    
    // Resolve return type
    TypePtr return_type = type_system.ANY_TYPE; // Default for unannotated functions
    if (func->name == "main") {
        return_type = type_system.INT64_TYPE;
    } else if (func->returnType) {
        return_type = resolve_type_annotation(func->returnType.value());
    }
    
    // Create function signature with enhanced features
    FunctionSignature signature;
    signature.name = func->name;
    signature.return_type = return_type;
    signature.declaration = func;
    signature.can_fail = func->canFail || func->throws;
    signature.error_types = func->declaredErrorTypes;
    
    // Check parameters
    for (const auto& param : func->params) {
        TypePtr param_type = type_system.ANY_TYPE; // Default for untyped parameters
        if (param.second) {
            param_type = resolve_type_annotation(param.second);
        }
        signature.param_types.push_back(param_type);
        signature.optional_params.push_back(false); // Required parameters are not optional
        signature.has_default_values.push_back(false); // Required parameters don't have defaults
    }
    
    // Check optional parameters
    for (const auto& optional_param : func->optionalParams) {
        TypePtr param_type = type_system.ANY_TYPE; // Default for untyped parameters
        if (optional_param.second.first) {
            param_type = resolve_type_annotation(optional_param.second.first);
        }
        signature.param_types.push_back(param_type);
        signature.optional_params.push_back(true); // These are optional parameters
        signature.has_default_values.push_back(optional_param.second.second != nullptr); // Has default if expression exists
    }
    
    function_signatures[func->name] = signature;
    
    // Validate error type annotations
    validate_function_error_types(func);
    
    // Declare the function name as a variable in the current scope
    // This allows the function to be called by name
    std::vector<std::string> param_names;
    for (const auto& p : func->params) param_names.push_back(p.first);
    for (const auto& op : func->optionalParams) param_names.push_back(op.first);
    
    TypePtr function_type = type_system.createFunctionType(param_names, signature.param_types, return_type, signature.has_default_values);
    declare_variable(func->name, function_type);
    mark_variable_initialized(func->name);
    
    // Check function body
    current_function = func;
    current_return_type = return_type;
    enter_scope();
    
    // Declare parameters with memory tracking
    for (size_t i = 0; i < func->params.size(); ++i) {
        declare_variable(func->params[i].first, signature.param_types[i]);
        declare_variable_memory(func->params[i].first, signature.param_types[i]);
        // Function parameters are initialized when the function is called
        mark_variable_initialized(func->params[i].first);
    }
    
    // Declare optional parameters with memory tracking
    for (size_t i = 0; i < func->optionalParams.size(); ++i) {
        size_t param_index = func->params.size() + i;
        declare_variable(func->optionalParams[i].first, signature.param_types[param_index]);
        declare_variable_memory(func->optionalParams[i].first, signature.param_types[param_index]);
        // Function parameters are initialized when the function is called
        mark_variable_initialized(func->optionalParams[i].first);
    }
    
    // Check body
    TypePtr body_type = check_statement(func->body);

    // Infer return type for unannotated non-main functions from body.
    if (func->name != "main" && !func->returnType.has_value() && body_type) {
        return_type = body_type;
        signature.return_type = return_type;
        function_signatures[func->name] = signature;
    }
    
    // Validate function body error types
    validate_function_body_error_types(func);
    
    // Exit scope and memory region
    exit_scope();
    exit_memory_region();
    
    current_function = nullptr;
    current_return_type = nullptr;
    
    func->inferred_type = return_type;
    return return_type;
}


TypePtr TypeChecker::check_destructuring_declaration(std::shared_ptr<LM::Frontend::AST::DestructuringDeclaration> dest_decl) {
    if (!dest_decl) return nullptr;
    
    TypePtr init_type = check_expression(dest_decl->initializer);
    if (!init_type) {
        add_error("Failed to determine type of initializer in destructuring declaration", dest_decl->line);
        return nullptr;
    }
    
    if (init_type->tag == TypeTag::Tuple) {
        auto* tuple_type = std::get_if<TupleType>(&init_type->extra);
        if (tuple_type) {
            if (dest_decl->names.size() != tuple_type->elementTypes.size()) {
                add_error("Tuple size mismatch in destructuring: expected " + 
                         std::to_string(tuple_type->elementTypes.size()) + " variables, got " + 
                         std::to_string(dest_decl->names.size()), dest_decl->line);
            }
            
            for (size_t i = 0; i < std::min(dest_decl->names.size(), tuple_type->elementTypes.size()); ++i) {
                declare_variable(dest_decl->names[i], tuple_type->elementTypes[i]);
                declare_variable_memory(dest_decl->names[i], tuple_type->elementTypes[i]);
                mark_variable_initialized(dest_decl->names[i]);
            }
        }
    } else if (init_type->tag == TypeTag::List) {
        auto* list_type = std::get_if<ListType>(&init_type->extra);
        if (list_type) {
            for (const auto& name : dest_decl->names) {
                declare_variable(name, list_type->elementType);
                declare_variable_memory(name, list_type->elementType);
                mark_variable_initialized(name);
            }
        }
    } else {
        add_error("Cannot destructure non-tuple/list type: " + init_type->toString(), dest_decl->line);
    }
    
    dest_decl->inferred_type = init_type;
    return init_type;
}
TypePtr TypeChecker::check_var_declaration(std::shared_ptr<LM::Frontend::AST::VarDeclaration> var_decl) {
    if (!var_decl) return nullptr;
    
    TypePtr declared_type = nullptr;
    if (var_decl->type) {
        declared_type = resolve_type_annotation(var_decl->type.value());
    }
    
    TypePtr init_type = nullptr;
    if (var_decl->initializer) {
        // Pass the declared type as expected type for better type inference
        init_type = check_expression_with_expected_type(var_decl->initializer, declared_type);
        
        // Check if initializing from another variable (potential move)
        if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(var_decl->initializer)) {
            TypePtr rhs_type = lookup_variable(var_expr->name);
            bool is_copyable = (rhs_type &&
                (rhs_type->tag == TypeTag::Function ||
                 rhs_type->tag == TypeTag::Int || rhs_type->tag == TypeTag::Int64 ||
                 rhs_type->tag == TypeTag::Float32 || rhs_type->tag == TypeTag::Float64 ||
                 rhs_type->tag == TypeTag::Bool || rhs_type->tag == TypeTag::String ||
                 rhs_type->tag == TypeTag::Nil || rhs_type->tag == TypeTag::Any));
            
            if (!is_copyable) {
                // For complex types, this would be a move
                // For now, we'll implement basic move semantics for all types
                check_variable_move(var_expr->name);
            }
        }
    }
    
    TypePtr final_type = nullptr;
    
    if (declared_type && init_type) {
        // Both declared and initialized - check compatibility
        if (is_type_compatible(declared_type, init_type)) {
            final_type = declared_type;
        } else if (is_string_type(declared_type) && is_string_type(init_type)) {
            // String type identity fix
            final_type = declared_type;
        } else {
            add_type_error(declared_type->toString(), init_type->toString(), var_decl->line);
            final_type = declared_type; // Use declared type anyway
        }
    } else if (declared_type) {
        // Only declared
        final_type = declared_type;
    } else if (init_type) {
        // Only initialized - infer type
        final_type = init_type;
    } else {
        // Neither - error
        add_error("Variable declaration without type or initializer", var_decl->line);
        final_type = type_system.STRING_TYPE; // Default
    }
    
    declare_variable(var_decl->name, final_type);
    declare_variable_memory(var_decl->name, final_type);  // Track memory safety
    
    // Mark as initialized if there's an initializer
    if (var_decl->initializer) {
        mark_variable_initialized(var_decl->name);
    }
    
    // Set the inferred type on the variable declaration statement
    var_decl->inferred_type = final_type;
    
    return final_type;
}

TypePtr TypeChecker::check_type_declaration(std::shared_ptr<LM::Frontend::AST::TypeDeclaration> type_decl) {
    if (!type_decl) return nullptr;
    
    // Resolve the underlying type
    TypePtr underlying_type = resolve_type_annotation(type_decl->type);
    if (!underlying_type) {
        add_error("Failed to resolve type for alias: " + type_decl->name, type_decl->line);
        return nullptr;
    }
    
    // Register the type alias in the type system
    type_system.registerTypeAlias(type_decl->name, underlying_type);
    
    // Set the inferred type on the type declaration statement
    type_decl->inferred_type = underlying_type;
    
    return underlying_type;
}

TypePtr TypeChecker::check_module_declaration(std::shared_ptr<LM::Frontend::AST::ModuleDeclaration> module_decl) {
    if (!module_decl) return nullptr;

    // Set current module name
    std::string prev_module = current_module_name;
    current_module_name = module_decl->name;


    // Inline members into the program's imported_symbols map
    for (const auto& member : module_decl->publicMembers) {
        std::string name;
        if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(member)) name = func->name;
        else if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(member)) name = frame->name;
        else if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(member)) name = var->name;

        if (!name.empty()) {
            std::string qualified_name = module_decl->name + "." + name;
            current_program_->imported_symbols[qualified_name] = member;
            // Also inline with original name to allow direct access if not aliased?
            // The main.cpp resolveImports doesn't support aliasing yet, so it just prepends modDecl
            current_program_->imported_symbols[name] = member;
        }
    }

    current_module_name = prev_module;

    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_enum_declaration(std::shared_ptr<LM::Frontend::AST::EnumDeclaration> enum_decl) {
    if (!enum_decl) return nullptr;

    // Create or get the base enum type
    TypePtr enumType = type_system.getType(enum_decl->name);
    if (!enumType || enumType->tag == TypeTag::Nil) {
        EnumType enumTypeInfo;
        enumTypeInfo.name = enum_decl->name;
        for (const auto& variant : enum_decl->variants) {
            std::vector<TypePtr> associated;
            for (const auto& t : variant.second) associated.push_back(resolve_type_annotation(t));
            enumTypeInfo.addVariant(variant.first, associated);
        }
        enumType = std::make_shared<::Type>(TypeTag::Enum, enumTypeInfo);
        type_system.addUserDefinedType(enum_decl->name, enumType);
    }

    // Register variants (qualified only) in global maps
    for (const auto& variant : enum_decl->variants) {
        const std::string& variantName = variant.first;
        const auto& associatedTypes = variant.second;
        std::string qualified = enum_decl->name + "." + variantName;

        if (associatedTypes.empty()) {
            // Unit variant
            variable_types[qualified] = enumType;
            variable_types[variantName] = enumType; // Also register unqualified

            FunctionSignature sig;
            sig.name = variantName;
            sig.return_type = enumType;
            function_signatures[qualified] = sig;
        } else {
            // Variant with associated values - functions as a constructor
            std::vector<TypePtr> paramTypes;
            for (const auto& astType : associatedTypes) {
                paramTypes.push_back(resolve_type_annotation(astType));
            }

            TypePtr constructorType = type_system.createFunctionType(paramTypes, enumType);
            variable_types[qualified] = constructorType;
            variable_types[variantName] = constructorType; // Also register unqualified

            FunctionSignature sig;
            sig.name = variantName;
            sig.param_types = paramTypes;
            sig.return_type = enumType;
            function_signatures[qualified] = sig;

            // Also register as a type if it's a single associated type (for sum-type like behavior)
            if (paramTypes.size() == 1) {
                type_system.registerType(variantName, constructorType);
            }
        }
    }

    enum_decl->inferred_type = enumType;
    return enumType;
}

TypePtr TypeChecker::check_block_statement(std::shared_ptr<LM::Frontend::AST::BlockStatement> block) {
    if (!block) return nullptr;
    
    enter_scope();
    enter_memory_region();  // New memory region for block
    
    TypePtr last_type = nullptr;
    for (const auto& stmt : block->statements) {
        last_type = check_statement(stmt);
    }
    
    exit_scope();
    exit_memory_region();  // Clean up memory region
    
    // Set the inferred type on the block statement
    block->inferred_type = last_type;
    
    return last_type;
}

TypePtr TypeChecker::check_if_statement(std::shared_ptr<LM::Frontend::AST::IfStatement> if_stmt) {
    if (!if_stmt) return nullptr;
    
    // Check condition
    TypePtr condition_type = check_expression(if_stmt->condition);
    if (!is_boolean_type(condition_type)) {
        add_type_error("bool", condition_type->toString(), if_stmt->condition->line);
    }
    
    // Check then branch
    check_statement(if_stmt->thenBranch);
    
    // Check else branch if present
    if (if_stmt->elseBranch) {
        check_statement(if_stmt->elseBranch);
    }
    
    // Set the inferred type on the if statement
    TypePtr result_type = type_system.NIL_TYPE; // if statements don't produce a value
    if_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_while_statement(std::shared_ptr<LM::Frontend::AST::WhileStatement> while_stmt) {
    if (!while_stmt) return nullptr;
    
    // Check condition
    TypePtr condition_type = check_expression(while_stmt->condition);
    if (!is_boolean_type(condition_type)) {
        add_type_error("bool", condition_type->toString(), while_stmt->condition->line);
    }
    
    // Check body
    bool was_in_loop = in_loop;
    in_loop = true;
    check_statement(while_stmt->body);
    in_loop = was_in_loop;
    
    // Set the inferred type on the while statement
    TypePtr result_type = type_system.NIL_TYPE;
    while_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_for_statement(std::shared_ptr<LM::Frontend::AST::ForStatement> for_stmt) {
    if (!for_stmt) return nullptr;
    
    enter_scope();
    
    // Check initializer
    if (for_stmt->initializer) {
        check_statement(for_stmt->initializer);
    }
    
    // Check condition
    if (for_stmt->condition) {
        TypePtr condition_type = check_expression(for_stmt->condition);
        if (!is_boolean_type(condition_type)) {
            add_type_error("bool", condition_type->toString(), for_stmt->condition->line);
        }
    }
    
    // Check increment
    if (for_stmt->increment) {
        check_expression(for_stmt->increment);
    }
    
    // Check body
    bool was_in_loop = in_loop;
    in_loop = true;
    check_statement(for_stmt->body);
    in_loop = was_in_loop;
    
    exit_scope();
    
    // Set the inferred type on the for statement
    TypePtr result_type = type_system.NIL_TYPE;
    for_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_parallel_statement(std::shared_ptr<LM::Frontend::AST::ParallelStatement> parallel_stmt) {
    if (!parallel_stmt) return nullptr;
    
    enter_scope();
    // Parallel blocks have direct access to outer scope variables, but with SharedCell semantics
    // For type checking, we check the body normally
    if (parallel_stmt->body) {
        check_statement(parallel_stmt->body);
    }
    exit_scope();
    
    parallel_stmt->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_concurrent_statement(std::shared_ptr<LM::Frontend::AST::ConcurrentStatement> concurrent_stmt) {
    if (!concurrent_stmt) return nullptr;
    
    enter_scope();
    
    // Declare channel if present
    if (!concurrent_stmt->channel.empty()) {
        declare_variable(concurrent_stmt->channel, type_system.CHANNEL_TYPE);
    }
    
    // Check body
    if (concurrent_stmt->body) {
        check_statement(concurrent_stmt->body);
    }
    
    exit_scope();
    
    concurrent_stmt->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_task_statement(std::shared_ptr<LM::Frontend::AST::TaskStatement> task_stmt) {
    if (!task_stmt) return nullptr;
    
    enter_scope();
    
    // Check iterable
    if (task_stmt->iterable) {
        TypePtr iterable_type = check_expression(task_stmt->iterable);
        // For now, allow any iterable, but could be restricted to ranges/collections
    }
    
    // Bind loop variable
    if (!task_stmt->loopVar.empty()) {
        declare_variable(task_stmt->loopVar, type_system.INT64_TYPE);
    }
    
    // Check body
    if (task_stmt->body) {
        check_statement(task_stmt->body);
    }
    
    exit_scope();
    
    task_stmt->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_worker_statement(std::shared_ptr<LM::Frontend::AST::WorkerStatement> worker_stmt) {
    if (!worker_stmt) return nullptr;
    
    enter_scope();
    
    // Check iterable
    if (worker_stmt->iterable) {
        TypePtr iterable_type = check_expression(worker_stmt->iterable);
    }
    
    // Bind parameter
    if (!worker_stmt->paramName.empty()) {
        declare_variable(worker_stmt->paramName, type_system.ANY_TYPE);
    }
    
    // Check body
    if (worker_stmt->body) {
        check_statement(worker_stmt->body);
    }
    
    exit_scope();
    
    worker_stmt->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_return_statement(std::shared_ptr<LM::Frontend::AST::ReturnStatement> return_stmt) {
    if (!return_stmt) return nullptr;
    
    TypePtr return_type = nullptr;
    if (return_stmt->value) {
        return_type = check_expression(return_stmt->value);
        
        // Auto-wrap in ok() if function returns error union type and value is not already wrapped
        if (current_return_type && type_system.isFallibleType(current_return_type)) {
            // Check if the return value is already an error construct or ok construct
            bool is_already_wrapped = false;
            if (auto error_construct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(return_stmt->value)) {
                is_already_wrapped = true;
            } else if (auto ok_construct = std::dynamic_pointer_cast<LM::Frontend::AST::OkConstructExpr>(return_stmt->value)) {
                is_already_wrapped = true;
            }
            
            if (!is_already_wrapped) {
                // Get the expected success type from the function's return type
                TypePtr expected_success_type = type_system.getFallibleSuccessType(current_return_type);
                
                if (expected_success_type && is_type_compatible(expected_success_type, return_type)) {
                    // Automatically wrap the return value in ok()
                    auto ok_construct = std::make_shared<LM::Frontend::AST::OkConstructExpr>();
                    ok_construct->value = return_stmt->value;
                    ok_construct->line = return_stmt->line;
                    ok_construct->inferred_type = current_return_type;
                    
                    // Replace the return statement's value with the ok construct
                    return_stmt->value = ok_construct;
                    return_type = current_return_type;
                } else {
                    add_type_error(expected_success_type ? expected_success_type->toString() : "unknown", 
                                 return_type->toString(), return_stmt->line);
                }
            }
        }
    } else {
        return_type = type_system.NIL_TYPE;
    }
    
    // Check if return type matches function return type
    if (current_return_type && !is_type_compatible(current_return_type, return_type)) {
        add_type_error(current_return_type->toString(), return_type->toString(), return_stmt->line);
    }
    
    // Set the inferred type on the return statement
    return_stmt->inferred_type = return_type;
    
    return return_type;
}

TypePtr TypeChecker::check_range_expr(std::shared_ptr<LM::Frontend::AST::RangeExpr> expr) {
    if (!expr) return nullptr;
    TypePtr startType = check_expression(expr->start);
    TypePtr endType = check_expression(expr->end);
    if (!is_numeric_type(startType)) add_type_error("numeric", startType->toString(), expr->line);
    if (!is_numeric_type(endType)) add_type_error("numeric", endType->toString(), expr->line);
    if (expr->step) {
        TypePtr stepType = check_expression(expr->step);
        if (!is_numeric_type(stepType)) add_type_error("numeric", stepType->toString(), expr->line);
    }
    TypePtr rangeType = std::make_shared<::Type>(TypeTag::Range);
    expr->inferred_type = rangeType;
    return rangeType;
}

TypePtr TypeChecker::check_print_statement(std::shared_ptr<LM::Frontend::AST::PrintStatement> print_stmt) {
    if (!print_stmt) return nullptr;
    
    for (const auto& arg : print_stmt->arguments) {
        check_expression(arg);
    }
    
    // Set the inferred type on the print statement
    TypePtr result_type = type_system.STRING_TYPE;
    print_stmt->inferred_type = result_type;
    
    return result_type;
}

} // namespace Frontend
} // namespace LM

