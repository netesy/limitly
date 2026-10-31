#include "../type_checker.hh"
#include "../parser.hh"

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
    } else if (auto mixin_decl = std::dynamic_pointer_cast<LM::Frontend::AST::MixinDeclaration>(stmt)) {
        return check_mixin_declaration(mixin_decl);
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
    } else if (auto iter_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IterStatement>(stmt)) {
        return check_iter_statement(iter_stmt);
    } else if (auto parallel_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ParallelStatement>(stmt)) {
        return check_parallel_statement(parallel_stmt);
    } else if (auto concurrent_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ConcurrentStatement>(stmt)) {
        return check_concurrent_statement(concurrent_stmt);
    } else if (auto task_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::TaskStatement>(stmt)) {
        return check_task_statement(task_stmt);
    } else if (auto worker_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WorkerStatement>(stmt)) {
        return check_worker_statement(worker_stmt);
    } else if (auto break_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::BreakStatement>(stmt)) {
        return type_system.NIL_TYPE;
    } else if (auto continue_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ContinueStatement>(stmt)) {
        return type_system.NIL_TYPE;
    } else if (auto return_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
        return check_return_statement(return_stmt);
    } else if (auto match_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::MatchStatement>(stmt)) {
        return check_match_statement(match_stmt);
    } else if (auto contract_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ContractStatement>(stmt)) {
        return check_contract_statement(contract_stmt);
    } else if (auto staged_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::StagedStatement>(stmt)) {
        return check_staged_statement(staged_stmt);
    } else if (auto staged_block = std::dynamic_pointer_cast<LM::Frontend::AST::StagedBlockStatement>(stmt)) {
        return check_staged_block_statement(staged_block);
    } else if (auto unsafe_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::UnsafeStatement>(stmt)) {
        bool prev = in_unsafe_block;
        in_unsafe_block = true;
        TypePtr body_res = check_statement(unsafe_stmt->body);
        in_unsafe_block = prev;
        unsafe_stmt->inferred_type = type_system.NIL_TYPE;
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

    if (func->isStaged) {
        // Value-returning staged functions are evaluated at compile time; their calls
        // fold to constants (see try_fold_staged_call). Register for call folding. A
        // staged fn is compile-time only and is skipped during runtime code generation.
        staged_functions_[func->name] = func;
        if (func->returnType && *func->returnType && (*func->returnType)->typeName == "type") {
            // Type constructor (`staged fn ...(x: type): type`). It is callable only from
            // type positions (resolve_staged_call_annotation); skip the value-callable
            // registration entirely so it cannot appear as a runtime function.
            return nullptr;
        }
    }
    for (bool is_staged : func->stagedParams) {
        if (is_staged) {
            add_error("staged parameters ('staged param') are not supported yet", func->line);
            break;
        }
    }
    
    
    // Resolve return type
    TypePtr return_type = type_system.ANY_TYPE; // Default for unannotated functions
    if (func->name == "main") {
        return_type = type_system.INT64_TYPE;
    } else if (func->returnType) {
        // A staged type constructor returned early above, so a meta name here is a misuse:
        // `type`/`enum`/`frame` only describe stage-0 parameters, never a runtime result.
        const auto& rt = func->returnType.value();
        if (rt && is_stage0_meta_name(rt->typeName)) {
            add_error("stage-0 meta type '" + rt->typeName + "' is only valid as a parameter of a staged fn returning type", func->line);
            return_type = type_system.ANY_TYPE;
        } else {
            return_type = resolve_type_annotation(rt);
        }
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
            if (is_stage0_meta_name(param.second->typeName)) {
                // See the return-type guard above: stage-0 parameter bindings belong to a
                // staged type constructor, which never reaches this loop.
                add_error("stage-0 meta type '" + param.second->typeName + "' is only valid as a parameter of a staged fn returning type", func->line);
            } else {
                param_type = resolve_type_annotation(param.second);
            }
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
    
    // Staged functions are evaluated at compile time by the fold executor or, for bodies
    // outside the foldable subset, by the stage-0 VM; their bodies are not runtime
    // type-checked here (parameters are not constants during normal checking, which would
    // mis-flag inner staged calls). The stage-0 VM type-checks the body itself before
    // lowering it (check_staged_body_for_vm).
    if (func->isStaged) {
        func->inferred_type = return_type;
        return return_type;
    }

    // Check function body
    current_function = func;
    current_return_type = return_type;
    enter_scope();
    
    // Declare parameters with memory tracking
    for (size_t i = 0; i < func->params.size(); ++i) {
        declare_variable(func->params[i].first, signature.param_types[i]);
        // Function parameters are initialized when the function is called
    }
    
    // Declare optional parameters with memory tracking
    for (size_t i = 0; i < func->optionalParams.size(); ++i) {
        size_t param_index = func->params.size() + i;
        declare_variable(func->optionalParams[i].first, signature.param_types[param_index]);
        // Function parameters are initialized when the function is called
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
            }
        }
    } else if (init_type->tag == TypeTag::List) {
        auto* list_type = std::get_if<ListType>(&init_type->extra);
        if (list_type) {
            for (const auto& name : dest_decl->names) {
                declare_variable(name, list_type->elementType);
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
        if (is_stage0_meta_name(var_decl->type.value()->typeName)) {
            // Runtime bindings cannot be annotated with a stage-0 meta name; staged bodies are
            // folded by exec_staged_stmt, which never reaches here.
            add_error("stage-0 meta type '" + var_decl->type.value()->typeName + "' is only valid as a parameter of a staged fn returning type", var_decl->line);
        } else {
            declared_type = resolve_type_annotation(var_decl->type.value());
        }
    }
    
    TypePtr init_type = nullptr;
    if (var_decl->initializer) {
        // Pass the declared type as expected type for better type inference
        init_type = check_expression_with_expected_type(var_decl->initializer, declared_type);
        
        long long val_int = 0;
        double val_double = 0.0;
        bool is_int = false;
        if (var_decl->isConst && evaluate_const_expr(var_decl->initializer, val_int, val_double, is_int, this)) {
            if (is_int) {
                constant_ints[var_decl->name] = val_int;
            } else {
                constant_doubles[var_decl->name] = val_double;
            }
        }

        // Record an enum-valued binding so stage 0 can fold equality on it. Immutable bindings
        // only: a `var` may be reassigned later and this environment is not watched for stores.
        long long enum_tag = 0;
        std::string enum_name;
        if (var_decl->isConst && try_stage0_enum_value(var_decl->initializer, enum_tag, enum_name)) {
            constant_enums_[var_decl->name] = {enum_name, enum_tag};
        }

        // Check if initializing from another variable (potential move or module alias)
        if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(var_decl->initializer)) {
            if (import_aliases.count(var_expr->name)) {
                std::string target_mod = import_aliases[var_expr->name];
                import_aliases[var_decl->name] = target_mod;
                FrameInfo alias_info;
                alias_info.name = var_decl->name;
                frame_declarations[var_decl->name] = alias_info;
                TypePtr mod_frame = type_system.createFrameType(var_decl->name);
                declare_variable(var_decl->name, mod_frame);
                variable_types[var_decl->name] = mod_frame;
                var_decl->inferred_type = mod_frame;
                return mod_frame;
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

        // Refinements are semantic types, not just aliases over their base type.
        // Discharge the assignment obligation immediately when the native SMT
        // fragment can decide it.  Unknown/unsupported expressions remain
        // eligible for the existing runtime path, but definite violations are
        // rejected at compile time.
        if (declared_type->tag == TypeTag::Refined && var_decl->initializer) {
            if (const auto* refined = std::get_if<RefinedType>(&declared_type->extra)) {
                SMTProofResult proof = SMTVerifier::verify_refinement(
                    refined->condition, var_decl->initializer);
                if (proof.status == SMTProofStatus::Counterexample) {
                    add_error("type mismatch: refinement type violation for variable '" + var_decl->name +
                              "': initializer does not satisfy " + declared_type->toString(),
                              var_decl->line);
                } else if (verification_policy_ == VerificationPolicy::Strict &&
                           proof.status != SMTProofStatus::Proven) {
                    add_error("strict verification could not prove refinement for variable '" +
                              var_decl->name + "': " + proof.message, var_decl->line);
                }
            }
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
    
    declare_variable(var_decl->name, final_type, var_decl->isConst);

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
    type_system.addUserDefinedType(type_decl->name, underlying_type);
    if (!current_module_name.empty()) {
        type_system.registerTypeAlias(current_module_name + "." + type_decl->name, underlying_type);
        type_system.addUserDefinedType(current_module_name + "." + type_decl->name, underlying_type);
    }
    
    // If the underlying type is a Frame, propagate FrameInfo to frame_declarations
    if (underlying_type->tag == TypeTag::Frame) {
        if (auto* fd = std::get_if<FrameType>(&underlying_type->extra)) {
            auto it = frame_declarations.find(fd->name);
            if (it != frame_declarations.end()) {
                frame_declarations[type_decl->name] = it->second;
                if (!current_module_name.empty()) {
                    frame_declarations[current_module_name + "." + type_decl->name] = it->second;
                }
            }
        }
    }
    
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

    if (enum_decl->hasExplicitVisibility) {
        add_error("`enum` declarations cannot have a visibility modifier (`enum` is already public by default)", enum_decl->line);
    }

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
    } else {
        // Replace existing enum type with complete one (from Pass -1)
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
    
    TypePtr last_type = nullptr;
    for (const auto& stmt : block->statements) {
        last_type = check_statement(stmt);
    }
    
    exit_scope();
    
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
    
    check_statement(if_stmt->thenBranch);
    if (if_stmt->elseBranch) check_statement(if_stmt->elseBranch);

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
    
    // NEW: Phase 2 - Control flow safety
    // Validate scope cleanup on loop entry
    
    check_statement(while_stmt->body);
    
    // NEW: Phase 2 - Control flow safety
    // Validate cleanup on loop exit
    
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
    
    // NEW: Phase 2 - Control flow safety
    // Validate scope cleanup on loop entry
    
    check_statement(for_stmt->body);
    
    // NEW: Phase 2 - Control flow safety
    // Validate cleanup on loop exit
    
    in_loop = was_in_loop;
    
    exit_scope();
    
    // Set the inferred type on the for statement
    TypePtr result_type = type_system.NIL_TYPE;
    for_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_iter_statement(std::shared_ptr<LM::Frontend::AST::IterStatement> iter_stmt) {
    if (!iter_stmt) return nullptr;

    // Type-check the iterable expression
    TypePtr iterable_type = check_expression(iter_stmt->iterable);

    // Infer element type(s) from the iterable's inferred type.
    // For lists/ranges/channels there is a single element type; for dicts we
    // can produce a (key, value) pair when two loop variables are bound.
    TypePtr key_type = type_system.ANY_TYPE;
    TypePtr value_type = type_system.ANY_TYPE;
    TypePtr element_type = type_system.ANY_TYPE;
    bool recognized = false;

    if (iterable_type) {
        switch (iterable_type->tag) {
            case TypeTag::List:
                element_type = type_system.getContainerElementType(iterable_type);
                key_type = element_type;
                recognized = true;
                break;
            case TypeTag::String:
                element_type = type_system.INT64_TYPE;
                key_type = element_type;
                recognized = true;
                break;
            case TypeTag::Dict: {
                auto kv = type_system.getDictTypes(iterable_type);
                key_type = kv.first;
                value_type = kv.second;
                element_type = key_type;
                recognized = true;
                break;
            }
            case TypeTag::Range:
                element_type = type_system.INT64_TYPE;
                key_type = element_type;
                recognized = true;
                break;
            case TypeTag::Tuple: {
                // Heterogeneous tuples iterate as any; homogeneous tuples bind
                // to the shared element type.
                auto* tt = std::get_if<TupleType>(&iterable_type->extra);
                if (tt && !tt->elementTypes.empty()) {
                    bool homogeneous = true;
                    for (size_t i = 1; i < tt->elementTypes.size(); ++i) {
                        if (!tt->elementTypes[i] ||
                            tt->elementTypes[i]->toString() != tt->elementTypes[0]->toString()) {
                            homogeneous = false;
                            break;
                        }
                    }
                    if (homogeneous) element_type = tt->elementTypes[0];
                }
                key_type = element_type;
                recognized = true;
                break;
            }
            case TypeTag::Channel:
                // Channels currently carry no typed element info; default to any.
                element_type = type_system.ANY_TYPE;
                key_type = element_type;
                recognized = true;
                break;
            case TypeTag::Any:
                // Untyped iterable; bind loop vars to any without erroring.
                recognized = true;
                break;
            default:
                recognized = false;
                break;
        }
    }

    if (!recognized) {
        std::string type_name = iterable_type ? iterable_type->toString() : std::string("unknown");
        add_error("Cannot iterate over type " + type_name, iter_stmt->line);
    }

    // Push a scope and bind the loop variable(s).
    enter_scope();

    if (iter_stmt->loopVars.size() == 1) {
        // For a single loop var: lists/ranges/channels bind to the element type;
        // dicts bind to the key type per task spec.
        declare_variable(iter_stmt->loopVars[0], element_type);
    } else if (iter_stmt->loopVars.size() == 2) {
        // Two loop vars: (key, value). For non-dict iterables the second var
        // gets any type as a fallback.
        declare_variable(iter_stmt->loopVars[0], key_type);
        declare_variable(iter_stmt->loopVars[1], value_type);
    } else if (!iter_stmt->loopVars.empty()) {
        // Defensive: bind all loop vars to any.
        for (const auto& var_name : iter_stmt->loopVars) {
            declare_variable(var_name, type_system.ANY_TYPE);
        }
    }

    // Type-check the body in the loop scope.
    bool was_in_loop = in_loop;
    in_loop = true;
    
    // NEW: Phase 2 - Control flow safety
    if (iter_stmt->loopVars.size() > 0) {
    }
    
    // Validate scope cleanup on loop entry
    
    check_statement(iter_stmt->body);
    
    // Validate cleanup on loop exit
    
    in_loop = was_in_loop;

    exit_scope();

    // iter statements do not produce a value.
    TypePtr result_type = type_system.NIL_TYPE;
    iter_stmt->inferred_type = result_type;

    return result_type;
}

TypePtr TypeChecker::check_parallel_statement(std::shared_ptr<LM::Frontend::AST::ParallelStatement> parallel_stmt) {
    if (!parallel_stmt) return nullptr;
    
    enter_scope();
    // Parallel blocks have direct access to outer values subject to the
    // capability analysis performed by the memory checker.
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
    TypePtr element_type = type_system.ANY_TYPE;
    if (task_stmt->iterable) {
        TypePtr iterable_type = check_expression(task_stmt->iterable);
        if (iterable_type && iterable_type->tag == TypeTag::List)
            element_type = type_system.getContainerElementType(iterable_type);
        else if (iterable_type && iterable_type->tag == TypeTag::Range)
            element_type = type_system.INT64_TYPE;
    }
    
    // Bind loop variable
    if (!task_stmt->loopVar.empty()) {
        declare_variable(task_stmt->loopVar, element_type);
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
    TypePtr element_type = type_system.ANY_TYPE;
    if (worker_stmt->iterable) {
        TypePtr iterable_type = check_expression(worker_stmt->iterable);
        if (iterable_type && iterable_type->tag == TypeTag::List)
            element_type = type_system.getContainerElementType(iterable_type);
        else if (iterable_type && iterable_type->tag == TypeTag::Range)
            element_type = type_system.INT64_TYPE;
    }
    
    // Bind parameter
    if (!worker_stmt->paramName.empty()) {
        declare_variable(worker_stmt->paramName, element_type);
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
    
    if (!current_return_type) {
        add_error("return statement not allowed at global scope", return_stmt->line);
        return type_system.NIL_TYPE;
    }

    TypePtr return_type = nullptr;
    if (return_stmt->value) {
        return_type = check_expression(return_stmt->value);
        if (!return_type) return nullptr;
        
        // Auto-wrap in ok() if function returns error union type and value is not already wrapped
        if (current_return_type && type_system.isFallibleType(current_return_type)) {
            // Check if the return value is already an error construct or ok construct
            bool is_already_wrapped = false;
            if (auto error_construct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(return_stmt->value)) {
                is_already_wrapped = true;
            } else if (auto ok_construct = std::dynamic_pointer_cast<LM::Frontend::AST::OkConstructExpr>(return_stmt->value)) {
                is_already_wrapped = true;
            } else if (type_system.isFallibleType(return_type)) {
                is_already_wrapped = true;
            } else if (return_type->tag == TypeTag::Nil) {
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
    
    // Closure captures are fully supported when returning lambdas.

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

TypePtr TypeChecker::check_staged_statement(std::shared_ptr<LM::Frontend::AST::StagedStatement> staged_stmt) {
    if (!staged_stmt) return type_system.NIL_TYPE;

    if (staged_stmt->declaration) {
        return check_statement(staged_stmt->declaration);
    } else if (staged_stmt->block) {
        auto eval_block = evaluate_staged_statement_node(staged_stmt->block, 0);
        return check_statement(eval_block);
    } else if (staged_stmt->expression) {
        auto eval_expr = evaluate_staged_expression(staged_stmt->expression, 0);
        return check_expression(eval_expr);
    }
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_staged_block_statement(std::shared_ptr<LM::Frontend::AST::StagedBlockStatement> staged_block) {
    if (!staged_block || !staged_block->body) return type_system.NIL_TYPE;

    auto eval_node = evaluate_staged_statement_node(staged_block->body, 0);
    return check_statement(eval_node);
}

// Stage-0 sandbox accounting (docs/staged.md section 4). Steps bound the work the type checker
// may spend folding; bytes bound what the folded program retains. Both draw on one
// compilation-wide budget, and the first exhaustion reports and latches, so the recursion that
// unwinds afterwards stays silent instead of repeating the error per frame.
bool TypeChecker::stage0_charge(long line, size_t steps, size_t bytes) {
    if (staged_budget_exhausted_) return false;
    staged_steps_ += steps;
    staged_bytes_ += bytes;
    const bool over_steps = staged_steps_ > STAGE0_MAX_STEPS;
    const bool over_bytes = staged_bytes_ > STAGE0_MAX_BYTES;
    if (!over_steps && !over_bytes) return true;
    staged_budget_exhausted_ = true;
    if (over_steps) {
        add_error("staged evaluation error: instruction limit exceeded (1000000 stage-0 steps)", line);
    } else {
        add_error("staged evaluation error: allocation limit exceeded (64 MB of compile-time output)", line);
    }
    return false;
}

std::shared_ptr<LM::Frontend::AST::Statement> TypeChecker::evaluate_staged_statement_node(std::shared_ptr<LM::Frontend::AST::Statement> stmt, size_t depth) {
    if (!stmt) return nullptr;
    if (!stage0_charge(stmt->line)) return stmt;
    if (depth >= STAGE0_MAX_DEPTH) {
        add_error("staged evaluation error: maximum recursion depth exceeded (1000 nested nodes)", stmt->line);
        staged_budget_exhausted_ = true;
        return stmt;
    }

    if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
        std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> new_stmts;
        for (auto& s : block->statements) {
            auto eval_s = evaluate_staged_statement_node(s, depth + 1);
            if (eval_s) new_stmts.push_back(eval_s);
        }
        block->statements = new_stmts;
        return block;
    }

    if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
        auto eval_cond = evaluate_staged_expression(if_stmt->condition, depth + 1);
        long long val_int = 0;
        double val_double = 0.0;
        bool is_int = false;
        if (evaluate_const_expr(eval_cond, val_int, val_double, is_int, this)) {
            bool cond_true = is_int ? (val_int != 0) : (val_double != 0.0);
            if (cond_true) {
                return evaluate_staged_statement_node(if_stmt->thenBranch, depth + 1);
            } else {
                if (if_stmt->elseBranch) {
                    return evaluate_staged_statement_node(if_stmt->elseBranch, depth + 1);
                } else {
                    auto empty = std::make_shared<LM::Frontend::AST::ExprStatement>();
                    empty->line = if_stmt->line;
                    return empty;
                }
            }
        }
        if_stmt->condition = eval_cond;
        if_stmt->thenBranch = evaluate_staged_statement_node(if_stmt->thenBranch, depth + 1);
        if (if_stmt->elseBranch) {
            if_stmt->elseBranch = evaluate_staged_statement_node(if_stmt->elseBranch, depth + 1);
        }
        return if_stmt;
    }

    if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
        if (var_decl->initializer) {
            var_decl->initializer = evaluate_staged_expression(var_decl->initializer, depth + 1);
        }
        return var_decl;
    }

    if (auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt)) {
        if (expr_stmt->expression) {
            expr_stmt->expression = evaluate_staged_expression(expr_stmt->expression, depth + 1);
        }
        return expr_stmt;
    }

    return stmt;
}

// =============================================================================
// staged fn compile-time evaluation (value-returning subset)
// =============================================================================
namespace {
std::shared_ptr<LM::Frontend::AST::LiteralExpr> make_const_literal(long long vi, double vd,
                                                                   bool is_int, int line,
                                                                   TypeChecker& tc) {
    auto lit = std::make_shared<LM::Frontend::AST::LiteralExpr>();
    lit->line = line;
    if (is_int) {
        lit->value = std::to_string(vi);
        lit->literalType = LM::Frontend::TokenType::INT_LITERAL;
    } else {
        lit->value = std::to_string(vd);
        lit->literalType = LM::Frontend::TokenType::FLOAT_LITERAL;
    }
    // The literal survives into the program, so it is stage-0 heap: charge the budget for it.
    tc.stage0_charge(line, 0, sizeof(LM::Frontend::AST::LiteralExpr));
    return lit;
}
} // namespace

std::shared_ptr<LM::Frontend::AST::Expression> TypeChecker::fold_stage0_expr(
        std::shared_ptr<LM::Frontend::AST::Expression> e, int depth) {
    if (!e) return e;
    if (!stage0_charge(e->line)) return e;
    if (static_cast<size_t>(depth) >= STAGE0_MAX_DEPTH) {
        add_error("staged evaluation error: maximum recursion depth exceeded (1000 nested nodes)", e->line);
        staged_budget_exhausted_ = true;
        return e;
    }
    // Fast path: the expression is already constant-evaluable (variables resolve through
    // the constant environment, no node mutation).
    long long vi = 0; double vd = 0.0; bool is_int = false;
    if (evaluate_const_expr(e, vi, vd, is_int, this))
        return make_const_literal(vi, vd, is_int, e->line, *this);

    // Binary / unary: rebuild a *fresh* node with folded children so nested staged-fn
    // calls collapse into literals. The original body nodes are never mutated, so a
    // staged fn folded once does not leak literals into its shared AST for later calls.
    if (auto bin = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(e)) {
        auto nb = std::make_shared<LM::Frontend::AST::BinaryExpr>();
        nb->line = bin->line;
        nb->op = bin->op;
        nb->left = fold_stage0_expr(bin->left, depth + 1);
        nb->right = fold_stage0_expr(bin->right, depth + 1);
        if (evaluate_const_expr(nb, vi, vd, is_int, this))
            return make_const_literal(vi, vd, is_int, bin->line, *this);
        return nb;
    }
    if (auto un = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(e)) {
        auto nu = std::make_shared<LM::Frontend::AST::UnaryExpr>();
        nu->line = un->line;
        nu->op = un->op;
        nu->right = fold_stage0_expr(un->right, depth + 1);
        if (evaluate_const_expr(nu, vi, vd, is_int, this))
            return make_const_literal(vi, vd, is_int, un->line, *this);
        return nu;
    }
    if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(e)) {
        auto callee = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(call->callee);
        if (callee) {
            auto it = staged_functions_.find(callee->name);
            if (it != staged_functions_.end()) {
                auto fn = it->second;
                if (is_staged_type_fn(fn)) {
                    // A type constructor invoked from a value expression: no value exists
                    // to fold. resolve_staged_type_expr handles the type-position path.
                    add_error("staged fn '" + callee->name + "' returns type and can only be used in a type position", call->line);
                    return call;
                }
                if (call->arguments.size() != fn->params.size()) {
                    add_error("staged fn '" + callee->name + "' expects " + std::to_string(fn->params.size()) + " argument(s)", call->line);
                    return call;
                }
                bool bind_ok = true;
                // Snapshot BEFORE binding: fold_staged_body's own snapshot is taken after
                // these params land in the maps, so without this restore the callee's
                // parameters leak and clobber the caller's same-named bindings (silent
                // mis-folds on shadowing). Mirrors the save/restore in check_call_expr.
                auto saved_ints = constant_ints;
                auto saved_doubles = constant_doubles;
                auto saved_types = constant_types_;
                auto saved_enums = constant_enums_;
                for (size_t i = 0; i < fn->params.size(); ++i) {
                    auto fa = fold_stage0_expr(call->arguments[i], depth + 1);
                    const std::string& pn = fn->params[i].first;
                    long long avi = 0; double avd = 0.0; bool aint = false;
                    // An enum argument binds in the enum environment: a variant is not a number,
                    // and storing its tag in constant_ints would let `p == 0` fold to true.
                    long long etag = 0; std::string ename;
                    if (try_stage0_enum_value(fa, etag, ename)) {
                        constant_ints.erase(pn);
                        constant_doubles.erase(pn);
                        constant_enums_[pn] = {ename, etag};
                        continue;
                    }
                    if (!evaluate_const_expr(fa, avi, avd, aint, this)) {
                        add_error("staged fn '" + callee->name + "' argument " + std::to_string(i + 1) + " must be a compile-time constant", call->line);
                        bind_ok = false;
                        break;
                    }
                    constant_ints.erase(pn);
                    constant_doubles.erase(pn);
                    constant_enums_.erase(pn);
                    if (aint) constant_ints[pn] = avi; else constant_doubles[pn] = avd;
                }
                long long oi = 0; double od = 0.0; bool oisint = false;
                TypePtr dummy;
                bool folded = bind_ok && fold_staged_body(fn, oi, od, oisint, dummy, false);
                constant_ints = saved_ints;
                constant_doubles = saved_doubles;
                constant_types_ = saved_types;
                constant_enums_ = saved_enums;
                if (folded)
                    return make_const_literal(oi, od, oisint, call->line, *this);
                return call;
            }
        }
        // Anything else is a host call. Stage 0 runs inside the type checker, which has no
        // system access, so there is nothing to execute here (docs/staged.md section 4,
        // Isolation Boundary). Report it rather than leaving a call the folder cannot reduce.
        const std::string callee_name = callee ? callee->name : "<expression>";
        add_error("staged evaluation error: cannot call '" + callee_name + "' at compile time -- stage 0 executes staged fns only and has no host access", call->line);
        return call;
    }
    return e;
}

// `an enum` / `a frame` — article for the kind-bound diagnostics.
static const char* kind_article(const std::string& kind) {
    return (kind == "enum") ? "an" : "a";
}

bool TypeChecker::exec_staged_stmt(std::shared_ptr<LM::Frontend::AST::Statement> stmt,
                                   long long& out_int, double& out_double, bool& out_is_int,
                                   TypePtr& out_type, bool want_type,
                                   bool& returned, bool& failed) {
    if (!stmt) { failed = true; return false; }
    if (returned) return true; // already produced a value; ignore trailing statements

    if (auto ret = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
        if (want_type) {
            // Type mode: resolve the expression directly in the type domain. It must NOT
            // go through fold_stage0_expr first: that path value-evaluates `T | nil`
            // (bitwise-OR on names) and rejects type-constructor calls.
            TypePtr t = resolve_staged_type_expr(ret->value, 0);
            if (!t) {
                if (!failed) // resolve may already have reported
                    add_error("staged fn 'return' must evaluate to a compile-time type", ret->line);
                failed = true; return false;
            }
            out_type = t; returned = true;
            return true;
        }
        auto folded = fold_stage0_expr(ret->value, 0);
        long long vi = 0; double vd = 0.0; bool is_int = false;
        if (!evaluate_const_expr(folded, vi, vd, is_int, this)) {
            add_error("staged fn 'return' value must be a compile-time constant", ret->line);
            failed = true; return false;
        }
        out_int = vi; out_double = vd; out_is_int = is_int; returned = true;
        return true;
    }

    if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
        for (auto& s : block->statements) {
            if (!exec_staged_stmt(s, out_int, out_double, out_is_int, out_type, want_type, returned, failed)) return false;
            if (returned) return true;
        }
        return true;
    }

    if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
        auto cond = fold_stage0_expr(if_stmt->condition, 0);
        long long vi = 0; double vd = 0.0; bool is_int = false;
        if (!evaluate_const_expr(cond, vi, vd, is_int, this)) {
            add_error("staged fn 'if' condition must be a compile-time constant", if_stmt->line);
            failed = true; return false;
        }
        bool cond_true = is_int ? (vi != 0) : (vd != 0.0);
        if (cond_true) return exec_staged_stmt(if_stmt->thenBranch, out_int, out_double, out_is_int, out_type, want_type, returned, failed);
        if (if_stmt->elseBranch) return exec_staged_stmt(if_stmt->elseBranch, out_int, out_double, out_is_int, out_type, want_type, returned, failed);
        return true;
    }

    if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
        bool decl_is_type = var_decl->type && *var_decl->type && is_stage0_meta_name((*var_decl->type)->typeName);
        if (want_type && decl_is_type) {
            // `var T: type = ...` binds a type value in the fold environment.
            TypePtr t = resolve_staged_type_expr(var_decl->initializer, 0);
            if (!t) {
                add_error("staged fn local '" + var_decl->name + "' must evaluate to a compile-time type", var_decl->line);
                failed = true; return false;
            }
            bool kb = false;
            auto required = staged_kind_bound(*var_decl->type, kb);
            if (required && t->tag != *required) {
                const std::string kind = (*var_decl->type)->typeName;
                add_error("staged fn local '" + var_decl->name + "' requires " + std::string(kind_article(kind)) + " " + kind + " type, found `" + t->toString() + "`", var_decl->line);
                failed = true; return false;
            }
            constant_types_.erase(var_decl->name);
            constant_types_[var_decl->name] = t;
            return true;
        }
        if (!want_type && decl_is_type) {
            add_error("staged fn local '" + var_decl->name + "' of type 'type' is only supported in a staged fn returning type", var_decl->line);
            failed = true; return false;
        }
        auto init = fold_stage0_expr(var_decl->initializer, 0);
        long long local_enum_tag = 0;
        std::string local_enum_name;
        if (try_stage0_enum_value(init, local_enum_tag, local_enum_name)) {
            constant_ints.erase(var_decl->name);
            constant_doubles.erase(var_decl->name);
            constant_enums_[var_decl->name] = {local_enum_name, local_enum_tag};
            return true;
        }
        long long vi = 0; double vd = 0.0; bool is_int = false;
        if (!evaluate_const_expr(init, vi, vd, is_int, this)) {
            add_error("staged fn local '" + var_decl->name + "' must be a compile-time constant", var_decl->line);
            failed = true; return false;
        }
        constant_ints.erase(var_decl->name);
        constant_doubles.erase(var_decl->name);
        constant_enums_.erase(var_decl->name);
        if (is_int) constant_ints[var_decl->name] = vi; else constant_doubles[var_decl->name] = vd;
        return true;
    }

    // Loops, expression statements and any other construct: not permitted in v1.
    add_error("unsupported construct in staged fn (only val/var constants, if/elif/else and return are supported)", stmt->line);
    failed = true;
    return false;
}

bool TypeChecker::fold_staged_body(std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> fn,
                                   long long& out_int, double& out_double, bool& out_is_int,
                                   TypePtr& out_type, bool want_type) {
    if (static_cast<size_t>(staged_fold_depth_) >= STAGE0_MAX_DEPTH) {
        add_error("staged evaluation error: maximum recursion depth exceeded (1000 nested staged fn calls)", fn ? fn->line : 0);
        staged_budget_exhausted_ = true;
        return false;
    }
    // A body the folder does not implement -- loops, local mutation -- runs on the stage-0 VM
    // instead. The choice is made from the syntax alone, before anything is folded, so a body
    // is never reported twice (once as "unsupported" and once by the other executor).
    if (!want_type && fn && staged_body_needs_vm(fn->body)) {
        const size_t errors_before = errors.size();
        if (run_staged_fn_on_vm(fn, out_int, out_double, out_is_int)) return true;
        if (errors.size() == errors_before) {
            add_error("staged fn '" + fn->name + "' could not be evaluated at compile time", fn->line);
        }
        return false;
    }
    ++staged_fold_depth_;
    // No internal environment snapshot: every call site snapshots BEFORE binding
    // parameters and restores after the fold, so callee bindings can never leak.

    long long vi = 0; double vd = 0.0; bool is_int = false;
    TypePtr vt = nullptr;
    bool returned = false; bool failed = false;
    if (fn && fn->body) {
        for (auto& s : fn->body->statements) {
            if (!exec_staged_stmt(s, vi, vd, is_int, vt, want_type, returned, failed)) { failed = true; break; }
            if (returned) break;
        }
    } else {
        failed = true;
    }

    --staged_fold_depth_;

    if (failed) return false;
    if (!returned) {
        add_error("staged fn '" + (fn ? fn->name : std::string()) + "' did not return a compile-time value", fn ? fn->line : 0);
        return false;
    }
    if (want_type) {
        if (!vt) return false;
        out_type = vt;
        return true;
    }
    out_int = vi; out_double = vd; out_is_int = is_int;
    return true;
}

bool TypeChecker::is_staged_type_fn(std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> fn) {
    if (!fn || !fn->isStaged || !fn->returnType || !*fn->returnType) return false;
    return (*fn->returnType)->typeName == "type";
}

TypePtr TypeChecker::resolve_staged_type_expr(std::shared_ptr<LM::Frontend::AST::Expression> e, int depth) {
    if (!e) return nullptr;
    if (!stage0_charge(e->line)) return nullptr;
    if (static_cast<size_t>(depth) >= STAGE0_MAX_DEPTH) {
        add_error("staged evaluation error: maximum recursion depth exceeded (1000 nested nodes)", e->line);
        staged_budget_exhausted_ = true;
        return nullptr;
    }
    // `type { ... }` literal: resolve the annotation against the current environment.
    // Never cache the result on the node: body nodes are shared across fold
    // invocations, and a cached type from one call would leak into the next.
    if (auto tle = std::dynamic_pointer_cast<LM::Frontend::AST::TypeLiteralExpr>(e)) {
        // The synthesized structural type is retained by the program, so it is charged to the
        // stage-0 heap bound: the Type header plus one entry per field.
        stage0_charge(e->line, 0, sizeof(::Type) + 64 * tle->annotation->structuralFields.size());
        return resolve_type_annotation(tle->annotation);
    }
    // Identifier referencing a bound type value (parameter, local, or nested result).
    if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(e)) {
        auto it = constant_types_.find(var->name);
        if (it != constant_types_.end()) return it->second;
        // Bare type names in expression position, e.g. `return T | nil;` -- `nil` and
        // primitives are ordinary identifiers here, so recognize them explicitly.
        if (var->name == "nil") return type_system.NIL_TYPE;
        if (TypePtr t = type_system.getType(var->name)) {
            if (t->tag != ::TypeTag::Nil) return t;
        }
        try {
            if (TypePtr ta = type_system.getTypeAlias(var->name)) {
                if (ta->tag != ::TypeTag::Nil) return ta;
            }
        } catch (...) {}
        if (const FrameInfo* fi = lookup_frame_info(var->name)) {
            return type_system.createFrameType(fi->name);
        }
        add_error("staged type expression references unknown type value '" + var->name + "'", e->line);
        return nullptr;
    }
    // `A | B` builds a union type when both sides are type values.
    if (auto bin = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(e)) {
        if (bin->op == LM::Frontend::TokenType::PIPE) {
            TypePtr a = resolve_staged_type_expr(bin->left, depth + 1);
            TypePtr b = resolve_staged_type_expr(bin->right, depth + 1);
            if (a && b) {
                stage0_charge(e->line, 0, sizeof(::Type) + 64 * 2);
                return type_system.createUnionType({a, b});
            }
            return nullptr;
        }
        return nullptr;
    }
    // Parenthesised type expression, e.g. `return (nullable(int)) | nil;`.
    if (auto grp = std::dynamic_pointer_cast<LM::Frontend::AST::GroupingExpr>(e)) {
        return resolve_staged_type_expr(grp->expression, depth + 1);
    }
    // Nested type constructor call, e.g. `nullable(either(int, str))`.
    if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(e)) {
        auto callee = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(call->callee);
        if (!callee) return nullptr;
        auto it = staged_functions_.find(callee->name);
        if (it == staged_functions_.end() || !is_staged_type_fn(it->second)) {
            add_error("staged fn '" + callee->name + "' does not return a type", e->line);
            return nullptr;
        }
        auto fn = it->second;
        if (call->arguments.size() != fn->params.size()) {
            add_error("staged fn '" + callee->name + "' expects " + std::to_string(fn->params.size()) + " type argument(s)", e->line);
            return nullptr;
        }
        // Snapshot before binding; a type fn may bind int or enum params too, so every
        // constant map is saved and restored around the fold.
        auto saved_types = constant_types_;
        auto saved_ints = constant_ints;
        auto saved_doubles = constant_doubles;
        auto saved_enums = constant_enums_;
        TypePtr result = nullptr;
        bool bind_ok = true;
        for (size_t i = 0; i < fn->params.size() && bind_ok; ++i) {
            const auto& pann = fn->params[i].second;
            const std::string& pn = fn->params[i].first;
            bool is_type_param = false;
            (void)staged_kind_bound(pann, is_type_param);
            if (is_type_param) {
                TypePtr at = resolve_staged_type_expr(call->arguments[i], depth + 1);
                if (!at) { bind_ok = false; break; }
                bind_ok = bind_staged_type_arg(callee->name, pn, pann, at, e->line);
            } else {
                auto fa = fold_stage0_expr(call->arguments[i], depth + 1);
                long long etag = 0; std::string ename;
                if (try_stage0_enum_value(fa, etag, ename)) {
                    constant_ints.erase(pn);
                    constant_doubles.erase(pn);
                    constant_enums_[pn] = {ename, etag};
                    continue;
                }
                long long avi = 0; double avd = 0.0; bool aint = false;
                if (!evaluate_const_expr(fa, avi, avd, aint, this)) {
                    add_error("staged fn '" + callee->name + "' argument " + std::to_string(i + 1) + " must be a compile-time constant", e->line);
                    bind_ok = false; break;
                }
                constant_types_.erase(pn);
                constant_ints.erase(pn);
                constant_doubles.erase(pn);
                constant_enums_.erase(pn);
                if (aint) constant_ints[pn] = avi; else constant_doubles[pn] = avd;
            }
        }
        if (bind_ok) {
            long long oi = 0; double od = 0.0; bool oisint = false;
            if (fold_staged_body(fn, oi, od, oisint, result, true)) { /* ok */ }
            else result = nullptr;
        }
        constant_types_ = saved_types;
        constant_ints = saved_ints;
        constant_doubles = saved_doubles;
        constant_enums_ = saved_enums;
        return result;
    }
    // `nil` parses to a null literal, so `return T | nil;` arrives here as a literal.
    if (auto lit = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(e)) {
        if (std::holds_alternative<std::nullptr_t>(lit->value)) return type_system.NIL_TYPE;
        return nullptr;  // a folded number/string used as a type: not a type value
    }
    add_error("expression inside staged fn must be a type value", e->line);
    return nullptr;
}

std::optional<TypeTag> TypeChecker::staged_kind_bound(const std::shared_ptr<LM::Frontend::AST::TypeAnnotation>& pann,
                                                      bool& is_kind_bound) {
    is_kind_bound = false;
    if (!pann) return std::nullopt;
    // `type`/`enum`/`frame` reach the checker as plain annotation names: none of them is a
    // known primitive type name, so the parser treats them as user-defined and we decide here.
    if (pann->typeName == "type") { is_kind_bound = true; return std::nullopt; }  // any type
    if (pann->typeName == "enum") { is_kind_bound = true; return TypeTag::Enum; }
    if (pann->typeName == "frame") { is_kind_bound = true; return TypeTag::Frame; }
    return std::nullopt;
}

bool TypeChecker::bind_staged_type_arg(const std::string& ctor_name, const std::string& pn,
                                       const std::shared_ptr<LM::Frontend::AST::TypeAnnotation>& pann,
                                       TypePtr arg, int line) {
    bool is_kind_bound = false;
    auto required = staged_kind_bound(pann, is_kind_bound);
    if (!is_kind_bound) {
        // A type argument bound to a value parameter: the value type is carried as an
        // int tag only if the body never reads it, so reject it explicitly.
        add_error("staged type constructor '" + ctor_name + "' parameter '" + pn + "' must be annotated 'type' (or a kind bound such as 'enum'/'frame') to receive a type argument", line);
        return false;
    }
    if (required && arg && arg->tag != *required) {
        std::string kind = pann->typeName;
        add_error("staged type constructor '" + ctor_name + "' parameter '" + pn + "' requires " + std::string(kind_article(kind)) + " " + kind + " type, found `" + arg->toString() + "`", line);
        return false;
    }
    // A parameter is bound in exactly one domain: clear any same-named value binding first.
    constant_types_.erase(pn);
    constant_ints.erase(pn);
    constant_doubles.erase(pn);
    constant_enums_.erase(pn);
    constant_types_[pn] = arg;
    return true;
}

TypePtr TypeChecker::resolve_staged_call_annotation(std::shared_ptr<LM::Frontend::AST::TypeAnnotation> annotation) {
    if (!stage0_charge(0)) return type_system.NIL_TYPE;
    // Staged frame templates (roadmaps.md item 1b) claim the request first: `Name(args)` on a
    // registered `staged frame` synthesizes a frame instead of folding to an existing type.
    {
        auto tf = staged_frame_templates_.find(annotation->stagedCallName);
        if (tf != staged_frame_templates_.end()) {
            return instantiate_staged_frame(annotation, annotation->stagedCallName, annotation->line);
        }
    }
    auto it = staged_functions_.find(annotation->stagedCallName);
    if (it == staged_functions_.end() || !is_staged_type_fn(it->second)) {
        add_error("cannot find staged type constructor '" + annotation->stagedCallName + "'");
        return type_system.NIL_TYPE;
    }
    auto fn = it->second;
    if (annotation->stagedCallArgs.size() != fn->params.size()) {
        add_error("staged type constructor '" + annotation->stagedCallName + "' expects " + std::to_string(fn->params.size()) + " argument(s)");
        return type_system.NIL_TYPE;
    }
    // Resolve each argument: type arguments become TypePtrs, literal arguments stay as
    // expressions to be folded into the value environment (nested staged calls resolve
    // recursively through resolve_type_annotation).
    std::vector<TypePtr> arg_types;
    for (const auto& arg : annotation->stagedCallArgs) {
        if (arg->stagedCallValueArg) {
            arg_types.push_back(nullptr);  // value argument: bound below
            continue;
        }
        TypePtr t = resolve_type_annotation(arg);
        if (!t) return type_system.NIL_TYPE;
        arg_types.push_back(t);
    }
    auto saved_types = constant_types_;
    auto saved_ints = constant_ints;
    auto saved_doubles = constant_doubles;
    auto saved_enums = constant_enums_;
    TypePtr result = nullptr;
    bool bind_ok = true;
    for (size_t i = 0; i < fn->params.size(); ++i) {
        const std::string& pn = fn->params[i].first;
        const auto& pann = fn->params[i].second;
        const bool is_value_arg = (bool)annotation->stagedCallArgs[i]->stagedCallValueArg;
        constant_types_.erase(pn);
        constant_ints.erase(pn);
        constant_doubles.erase(pn);
        constant_enums_.erase(pn);
        if (is_value_arg) {
            // Constant value parameter, e.g. `vector(8, int)` driving a comptime `if`.
            bool is_type_param = false;
            (void)staged_kind_bound(pann, is_type_param);
            if (is_type_param) {
                add_error("staged type constructor '" + annotation->stagedCallName + "' parameter '" + pn + "' expects a type, got a value");
                bind_ok = false;
                break;
            }
            auto fa = fold_stage0_expr(annotation->stagedCallArgs[i]->stagedCallValueArg, 0);
            long long etag = 0; std::string ename;
            if (try_stage0_enum_value(fa, etag, ename)) {
                constant_enums_[pn] = {ename, etag};
                continue;
            }
            long long avi = 0; double avd = 0.0; bool aint = false;
            if (!evaluate_const_expr(fa, avi, avd, aint, this)) {
                add_error("staged type constructor '" + annotation->stagedCallName + "' value argument '" + pn + "' must be a compile-time constant");
                bind_ok = false;
                break;
            }
            constant_types_.erase(pn);
            if (aint) constant_ints[pn] = avi; else constant_doubles[pn] = avd;
        } else {
            if (!bind_staged_type_arg(annotation->stagedCallName, pn, pann, arg_types[i], 0)) {
                bind_ok = false;
                break;
            }
        }
    }
    if (bind_ok) {
        long long oi = 0; double od = 0.0; bool oisint = false;
        if (!fold_staged_body(fn, oi, od, oisint, result, true)) result = nullptr;
    }
    constant_types_ = saved_types;
    constant_ints = saved_ints;
    constant_doubles = saved_doubles;
    constant_enums_ = saved_enums;
    if (!result) {
        add_error("staged type constructor '" + annotation->stagedCallName + "' failed to fold to a compile-time type");
        return type_system.NIL_TYPE;
    }
    return result;
}

// =============================================================================
// Staged frame templates -- roadmaps.md item 1b, the generics replacement for
// data shapes. A `staged frame Name(T: type)` declaration contributes no frame
// of its own: a type-position request `Name(args)` substitutes concrete type
// tokens for the meta-parameters, re-parses the substituted token stream into
// a plain FrameDeclaration, and adopts it (name registration, signature
// resolution, body check) into the current program before codegen runs. The
// instances are ordinary nominal frames, so every backend conforms by
// construction -- exactly the contract item 1 set for staged fns.
// =============================================================================
namespace {

// Identifier-safe spelling of a name: module dots and other punctuation fold to '_'.
std::string sf_sanitize(const std::string& in) {
    std::string out;
    out.reserve(in.size());
    for (char c : in) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') out.push_back(c);
        else out.push_back('_');
    }
    return out;
}

// Primitive type -> single annotation token. Round-trips through parseBasicType.
bool sf_primitive_token(const TypePtr& t, Token& out_tok) {
    struct Row { TypeTag tag; TokenType tt; const char* lx; };
    static const Row rows[] = {
        {TypeTag::Nil, TokenType::NIL_TYPE, "nil"},
        {TypeTag::Bool, TokenType::BOOL_TYPE, "bool"},
        {TypeTag::Int, TokenType::INT_TYPE, "int"},
        {TypeTag::Int8, TokenType::INT8_TYPE, "i8"},
        {TypeTag::Int16, TokenType::INT16_TYPE, "i16"},
        {TypeTag::Int32, TokenType::INT32_TYPE, "i32"},
        {TypeTag::Int64, TokenType::INT64_TYPE, "i64"},
        {TypeTag::Int128, TokenType::INT128_TYPE, "i128"},
        {TypeTag::UInt, TokenType::UINT_TYPE, "uint"},
        {TypeTag::UInt8, TokenType::UINT8_TYPE, "u8"},
        {TypeTag::UInt16, TokenType::UINT16_TYPE, "u16"},
        {TypeTag::UInt32, TokenType::UINT32_TYPE, "u32"},
        {TypeTag::UInt64, TokenType::UINT64_TYPE, "u64"},
        {TypeTag::UInt128, TokenType::UINT128_TYPE, "u128"},
        {TypeTag::Float32, TokenType::FLOAT32_TYPE, "f32"},
        {TypeTag::Float64, TokenType::FLOAT_TYPE, "float"},
        {TypeTag::Decimal2, TokenType::D2_TYPE, "d2"},
        {TypeTag::Decimal4, TokenType::D4_TYPE, "d4"},
        {TypeTag::Decimal6, TokenType::D6_TYPE, "d6"},
        {TypeTag::String, TokenType::STR_TYPE, "str"},
        {TypeTag::Any, TokenType::ANY_TYPE, "any"},
        {TypeTag::Channel, TokenType::CHANNEL_TYPE, "channel"},
    };
    for (const auto& r : rows) {
        if (t->tag == r.tag) { out_tok = Token(r.tt, r.lx, 0); return true; }
    }
    return false;
}

// Named (nominal) types carry their identity as one identifier token; a module-
// qualified lexeme ("core.Point") is a single token that parseBasicType accepts
// and the checker resolves through import_aliases exactly like a hand-written
// annotation would.
bool sf_named_token(const TypePtr& t, Token& out_tok) {
    if (t->tag == TypeTag::Frame) {
        if (const auto* f = std::get_if<FrameType>(&t->extra); f && !f->name.empty()) {
            out_tok = Token(TokenType::IDENTIFIER, f->name, 0); return true;
        }
    } else if (t->tag == TypeTag::Enum) {
        if (const auto* e = std::get_if<EnumType>(&t->extra); e && !e->name.empty()) {
            out_tok = Token(TokenType::IDENTIFIER, e->name, 0); return true;
        }
    } else if (t->tag == TypeTag::Trait) {
        if (const auto* tr = std::get_if<TraitType>(&t->extra); tr && !tr->name.empty()) {
            out_tok = Token(TokenType::IDENTIFIER, tr->name, 0); return true;
        }
    }
    return false;
}

// Re-parseable token spelling of a resolved type (substitution payload).
bool sf_type_tokens_rec(const TypePtr& t, std::vector<Token>& out) {
    if (!t) return false;
    Token single;
    if (sf_primitive_token(t, single) || sf_named_token(t, single)) { out.push_back(single); return true; }
    switch (t->tag) {
        case TypeTag::List: {
            const auto* lt = std::get_if<ListType>(&t->extra);
            if (!lt || !lt->elementType) return false;
            out.push_back(Token(TokenType::LEFT_BRACKET, "[", 0));
            if (!sf_type_tokens_rec(lt->elementType, out)) return false;
            out.push_back(Token(TokenType::RIGHT_BRACKET, "]", 0));
            return true;
        }
        case TypeTag::Dict: {
            const auto* dt = std::get_if<DictType>(&t->extra);
            if (!dt || !dt->keyType || !dt->valueType) return false;
            out.push_back(Token(TokenType::LEFT_BRACE, "{", 0));
            if (!sf_type_tokens_rec(dt->keyType, out)) return false;
            out.push_back(Token(TokenType::COLON, ":", 0));
            if (!sf_type_tokens_rec(dt->valueType, out)) return false;
            out.push_back(Token(TokenType::RIGHT_BRACE, "}", 0));
            return true;
        }
        case TypeTag::Tuple: {
            const auto* tt = std::get_if<TupleType>(&t->extra);
            if (!tt || tt->elementTypes.empty()) return false;
            out.push_back(Token(TokenType::LEFT_PAREN, "(", 0));
            bool first = true;
            for (const auto& e : tt->elementTypes) {
                if (!first) out.push_back(Token(TokenType::COMMA, ",", 0));
                first = false;
                if (!sf_type_tokens_rec(e, out)) return false;
            }
            out.push_back(Token(TokenType::RIGHT_PAREN, ")", 0));
            return true;
        }
        case TypeTag::Union: {
            // `A | B` is parseable wherever an annotation is; no parentheses (the grammar
            // reserves '(' for tuples and function types in annotation position).
            const auto* ut = std::get_if<UnionType>(&t->extra);
            if (!ut || ut->types.empty()) return false;
            bool first = true;
            for (const auto& m : ut->types) {
                if (!first) out.push_back(Token(TokenType::PIPE, "|", 0));
                first = false;
                if (!sf_type_tokens_rec(m, out)) return false;
            }
            return true;
        }
        default:
            return false;
    }
}

// Stable identifier fragment for cache/mangle keys (distinct per type spelling).
bool sf_type_mangle_rec(const TypePtr& t, std::string& out) {
    if (!t) return false;
    switch (t->tag) {
        case TypeTag::Frame:
        case TypeTag::Enum:
        case TypeTag::Trait: {
            Token tok;
            if (!sf_named_token(t, tok)) return false;
            out += sf_sanitize(tok.lexeme);
            return true;
        }
        case TypeTag::List: {
            const auto* lt = std::get_if<ListType>(&t->extra);
            if (!lt || !lt->elementType) return false;
            out += "List_of_";
            return sf_type_mangle_rec(lt->elementType, out);
        }
        case TypeTag::Dict: {
            const auto* dt = std::get_if<DictType>(&t->extra);
            if (!dt || !dt->keyType || !dt->valueType) return false;
            out += "Dict_of_";
            if (!sf_type_mangle_rec(dt->keyType, out)) return false;
            out += "_to_";
            return sf_type_mangle_rec(dt->valueType, out);
        }
        case TypeTag::Tuple: {
            const auto* tt = std::get_if<TupleType>(&t->extra);
            if (!tt || tt->elementTypes.empty()) return false;
            out += "Tuple_of_";
            for (size_t i = 0; i < tt->elementTypes.size(); ++i) {
                if (i) out += "_";
                if (!sf_type_mangle_rec(tt->elementTypes[i], out)) return false;
            }
            return true;
        }
        case TypeTag::Union: {
            const auto* ut = std::get_if<UnionType>(&t->extra);
            if (!ut || ut->types.empty()) return false;
            out += "Union_of_";
            for (size_t i = 0; i < ut->types.size(); ++i) {
                if (i) out += "_";
                if (!sf_type_mangle_rec(ut->types[i], out)) return false;
            }
            return true;
        }
        default:
            break;
    }
    Token prim;
    if (sf_primitive_token(t, prim)) { out += prim.lexeme; return true; }
    return false;
}   // namespace-open helpers end

} // namespace

void TypeChecker::register_staged_frame_template(const std::string& name,
                                                 const std::shared_ptr<LM::Frontend::AST::FrameDeclaration>& decl) {
    if (!decl) return;
    auto prev = staged_frame_templates_.find(name);
    if (prev != staged_frame_templates_.end()) {
        if (prev->second.get() != decl.get())
            add_error("duplicate staged frame template '" + name + "'", decl->line);
        return;
    }
    // Validate the meta-parameters now, not per request: a template can never be
    // instantiated if a bound is missing (a bad declaration is one precise error).
    for (const auto& p : decl->templateParams) {
        bool is_bound = false;
        staged_kind_bound(p.bound, is_bound);
        if (!is_bound) {
            add_error("staged frame '" + name + "' parameter '" + p.name +
                      "' must be bound to a stage-0 kind (`type`, `enum`, or `frame`)", decl->line);
        }
    }
    staged_frame_templates_[name] = decl;
}

std::vector<LM::Frontend::Token> TypeChecker::staged_frame_type_tokens(const TypePtr& t) {
    std::vector<Token> out;
    if (!sf_type_tokens_rec(t, out)) return {};
    return out;
}

std::string TypeChecker::staged_frame_mangle(const TypePtr& t) {
    std::string out;
    if (!sf_type_mangle_rec(t, out)) return "";
    return out;
}

TypePtr TypeChecker::instantiate_staged_frame(const std::shared_ptr<LM::Frontend::AST::TypeAnnotation>& annotation,
                                              const std::string& template_key, int line) {
    auto tmpl_it = staged_frame_templates_.find(template_key);
    if (tmpl_it == staged_frame_templates_.end()) {
        add_error("cannot find staged frame template '" + template_key + "'", line);
        return type_system.NIL_TYPE;
    }
    auto tmpl = tmpl_it->second;
    if (!stage0_charge(line, 1, sizeof(LM::Frontend::AST::FrameDeclaration))) return type_system.NIL_TYPE;
    if (tmpl->templateBodyTokens.empty()) {
        add_error("staged frame '" + template_key + "' has no body to instantiate", tmpl->line);
        return type_system.NIL_TYPE;
    }
    if (annotation->stagedCallArgs.size() != tmpl->templateParams.size()) {
        add_error("staged frame '" + template_key + "' expects " + std::to_string(tmpl->templateParams.size()) +
                  " type argument(s), got " + std::to_string(annotation->stagedCallArgs.size()), line);
        return type_system.NIL_TYPE;
    }
    if (++staged_frame_depth_ > STAGED_FRAME_MAX_DEPTH) {
        --staged_frame_depth_;
        add_error("staged frame instantiation error: maximum nesting depth exceeded (" +
                  std::to_string(STAGED_FRAME_MAX_DEPTH) + " nested instantiations)", line);
        return type_system.NIL_TYPE;
    }
    struct Restore { std::unordered_map<std::string, TypePtr>* d; ~Restore() { (void)d; } };
    // Resolve and kind-check every argument (nested requests recurse here).
    std::vector<TypePtr> args;
    args.reserve(annotation->stagedCallArgs.size());
    for (size_t i = 0; i < annotation->stagedCallArgs.size(); ++i) {
        const auto& argann = annotation->stagedCallArgs[i];
        const std::string& pn = tmpl->templateParams[i].name;
        if (!argann || argann->stagedCallValueArg) {
            add_error("staged frame '" + template_key + "' parameter '" + pn + "' takes a type argument, not a value", line);
            --staged_frame_depth_;
            return type_system.NIL_TYPE;
        }
        TypePtr t = resolve_type_annotation(argann);
        if (!t) {
            --staged_frame_depth_;
            return type_system.NIL_TYPE;
        }
        bool is_bound = false;
        auto required = staged_kind_bound(tmpl->templateParams[i].bound, is_bound);
        if (required && t->tag != *required) {
            add_error("staged frame '" + template_key + "' parameter '" + pn + "' requires " +
                      std::string(kind_article(tmpl->templateParams[i].bound->typeName)) + " " +
                      tmpl->templateParams[i].bound->typeName + " type, found `" + t->toString() + "`", line);
            --staged_frame_depth_;
            return type_system.NIL_TYPE;
        }
        args.push_back(t);
    }

    // Mangle: the template's request spelling plus one fragment per argument. Nominal
    // identity falls out of the cache key -- Option(int) is always Option_int.
    std::string base = sf_sanitize(template_key);
    std::string mangled = base;
    for (const auto& a : args) {
        std::string m = staged_frame_mangle(a);
        if (m.empty()) {
            add_error("staged frame '" + template_key + "': type argument `" + a->toString() +
                      "` is not a supported instantiation argument", line);
            --staged_frame_depth_;
            return type_system.NIL_TYPE;
        }
        mangled += "_" + m;
    }
    if (auto hit = generated_staged_frames_.find(mangled); hit != generated_staged_frames_.end()) {
        --staged_frame_depth_;
        return hit->second;   // cached (possibly still under construction -- a self-reference
                              // through another template resolves exactly like a frame field
                              // referring to its own frame)
    }
    if (generated_staged_frames_.size() >= STAGED_FRAME_MAX_GENERATED) {
        --staged_frame_depth_;
        add_error("staged frame instantiation error: frame limit exceeded (" +
                  std::to_string(STAGED_FRAME_MAX_GENERATED) + " synthesized frames)", line);
        return type_system.NIL_TYPE;
    }

    // Substitute meta-parameters at the token level: an identifier equal to a parameter
    // name is replaced by the argument's annotation tokens, everything else is copied.
    std::vector<Token> toks;
    toks.reserve(tmpl->templateBodyTokens.size() + 4 + args.size());
    toks.push_back(Token(TokenType::FRAME, "frame", tmpl->line));
    toks.push_back(Token(TokenType::IDENTIFIER, mangled, tmpl->line));
    toks.push_back(Token(TokenType::LEFT_BRACE, "{", tmpl->line));
    bool subst_ok = true;
    for (const auto& bt : tmpl->templateBodyTokens) {
        int slot = -1;
        if (bt.type == TokenType::IDENTIFIER) {
            for (size_t i = 0; i < tmpl->templateParams.size(); ++i) {
                if (tmpl->templateParams[i].name == bt.lexeme) { slot = (int)i; break; }
            }
        }
        if (slot < 0) { toks.push_back(bt); continue; }
        auto repl = staged_frame_type_tokens(args[(size_t)slot]);
        if (repl.empty()) { subst_ok = false; break; }
        for (auto& rt : repl) { rt.line = bt.line; }
        toks.insert(toks.end(), repl.begin(), repl.end());
    }
    if (!subst_ok) {
        add_error("staged frame '" + template_key + "': type argument `" + args[0]->toString() +
                  "` is not a supported instantiation argument", line);
        --staged_frame_depth_;
        return type_system.NIL_TYPE;
    }
    toks.push_back(Token(TokenType::RIGHT_BRACE, "}", tmpl->line));
    toks.push_back(Token(TokenType::EOF_TOKEN, "", tmpl->line));

    // Re-parse the substituted stream. Trivia-free by construction, so the frame body
    // grammar needs the semicolons it always had -- this is the same token stream a
    // hand-written frame produces.
    std::shared_ptr<LM::Frontend::AST::FrameDeclaration> gen;
    try {
        Scanner synth_scanner(toks);
        Parser synth_parser(synth_scanner, false);
        auto synth_program = synth_parser.parse();
        if (!synth_parser.hadError() && synth_program && synth_program->statements.size() == 1) {
            gen = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(synth_program->statements[0]);
        }
    } catch (const std::runtime_error&) {
        gen = nullptr;
    }
    if (!gen) {
        add_error("failed to synthesize staged frame '" + mangled + "' from template '" + template_key + "'", line);
        --staged_frame_depth_;
        return type_system.NIL_TYPE;
    }
    gen->isGenerated = true;

    // Adopt: exactly the registration a hand-written frame receives in passes 1-3, in the
    // order the checker performs them, then into the program AST for codegen.
    type_system.addUserDefinedType(mangled, type_system.createFrameType(mangled));
    TypePtr frame_type = type_system.getUserDefinedType(mangled);
    if (!frame_type) frame_type = type_system.createFrameType(mangled);
    generated_staged_frames_[mangled] = frame_type;   // before body check: requests raised
                                                      // inside re-enter on this same frame
    register_frame_signature(mangled, gen);
    check_frame_declaration_with_name(mangled, gen);
    if (current_program_) current_program_->statements.push_back(gen);
    stage0_charge(line, 0, toks.size() * sizeof(Token));
    --staged_frame_depth_;
    return frame_type;
}

} // namespace Frontend
} // namespace LM
