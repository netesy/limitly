#include "../type_checker.hh"
#include "../module_manager.hh"

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

TypePtr TypeChecker::check_contract_statement(std::shared_ptr<LM::Frontend::AST::ContractStatement> contract_stmt) {
    if (!contract_stmt) return nullptr;
    
    if (!contract_stmt->condition) {
        add_error("contract statement missing condition", contract_stmt->line, 0, 
                get_code_context(contract_stmt->line), "contract", "contract(condition, message)");
        return type_system.NIL_TYPE;
    }
    
    if (!contract_stmt->message) {
        add_error("contract statement missing message", contract_stmt->line, 0, 
                get_code_context(contract_stmt->line), "contract", "contract(condition, message)");
        return type_system.NIL_TYPE;
    }
    
    // Check condition is boolean
    TypePtr conditionType = check_expression(contract_stmt->condition);
    if (!is_boolean_type(conditionType) && conditionType->tag != TypeTag::Any) {
        add_error("contract condition must be boolean, got " + conditionType->toString(), 
                contract_stmt->line, 0, get_code_context(contract_stmt->line), "condition", "boolean expression");
    }
    
    // Check message is string
    TypePtr messageType = check_expression(contract_stmt->message);
    if (!is_string_type(messageType) && messageType->tag != TypeTag::Any) {
        add_error("contract message must be string, got " + messageType->toString(), 
                contract_stmt->line, 0, get_code_context(contract_stmt->line), "message", "string literal or expression");
    }
    
    contract_stmt->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_match_statement(std::shared_ptr<LM::Frontend::AST::MatchStatement> match_stmt) {
    if (!match_stmt) return nullptr;
    
    // Check the matched expression
    TypePtr matchType = check_expression(match_stmt->value);
    TypePtr unified_branch_type = nullptr;

    // Check each case
    for (auto& matchCase : match_stmt->cases) {
        enter_scope();

        // Validate pattern compatibility and register bindings
        matchCase.pattern->inferred_type = matchType;
        validate_pattern_compatibility(matchCase.pattern, matchType, match_stmt->line);

        // Check guard if present
        if (matchCase.guard) {
            TypePtr guardType = check_expression(matchCase.guard);
            if (!is_boolean_type(guardType) && guardType->tag != TypeTag::Any) {
                add_error("Match guard must be a boolean expression", match_stmt->line);
            }
        }
        
        // Check case body
        TypePtr branch_type = check_statement(matchCase.body);
        
        // Mandate 2: All branches must resolve to a single unified type
        if (!unified_branch_type) {
            unified_branch_type = branch_type;
        } else if (branch_type) {
            try {
                unified_branch_type = type_system.getCommonType(unified_branch_type, branch_type);
            } catch (const std::exception& e) {
                add_error("Match branch type mismatch: " + std::string(e.what()), match_stmt->line);
            }
        }
        
        exit_scope();
    }

    TypePtr result_type = unified_branch_type ? unified_branch_type : type_system.NIL_TYPE;
    match_stmt->inferred_type = result_type;
    
    // Convert cases to shared_ptr vector for function calls
    std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>> case_ptrs;
    case_ptrs.reserve(match_stmt->cases.size());
    for (const auto& case_item : match_stmt->cases) {
        case_ptrs.push_back(std::make_shared<LM::Frontend::AST::MatchCase>(case_item));
    }
    
    // Enhanced exhaustiveness checking for different type categories
    if (is_error_union_type(matchType)) {
        if (!is_exhaustive_error_match(case_ptrs, matchType)) {
            auto* errorUnionPtr = std::get_if<ErrorUnionType>(&matchType->extra);
            if (!errorUnionPtr) {
                throw std::runtime_error("Missing ErrorUnionType data in ErrorUnion type");
            }
            auto& errorUnion = *errorUnionPtr;
            
            if (errorUnion.isGenericError) {
                add_error("Match statement is not exhaustive for error union type. Must handle both success case (val pattern) and error case (err pattern)", 
                        match_stmt->line);
            } else {
                std::string missingPatterns = "Must handle success case (val pattern) and all error types: [" + 
                                            join_error_types(errorUnion.errorTypes) + "]";
                add_error("Match statement is not exhaustive for error union type. " + missingPatterns, 
                        match_stmt->line);
            }
        }
    } else if (is_union_type(matchType)) {
        // Union type exhaustiveness checking
        if (!is_exhaustive_union_match(matchType, case_ptrs)) {
            std::string missingVariants = get_missing_union_variants(matchType, case_ptrs);
            add_error("Match statement is not exhaustive for union type " + matchType->toString() + 
                    ". Missing patterns for: " + missingVariants, match_stmt->line);
        }
    } else if (type_system.isOptionType(matchType)) {
        // Option type exhaustiveness checking
        if (!is_exhaustive_option_match(case_ptrs)) {
            add_error("Match statement is not exhaustive for Option type. Must handle both Some and None cases", 
                        match_stmt->line);
        }
    }
    
    return result_type;
}

void TypeChecker::register_builtin_function(const std::string& name, 
                                            const std::vector<TypePtr>& param_types,
                                            TypePtr return_type) {
    FunctionSignature sig;
    sig.name = name;
    sig.param_types = param_types;
    sig.return_type = return_type;
    sig.declaration = nullptr; // Builtin functions have no declaration
    
    function_signatures[name] = sig;
    TypePtr func_type = type_system.createFunctionType(sig.param_types, sig.return_type);
    declare_variable(name, func_type);
}

// =============================================================================
// FRAME DECLARATION AND INSTANTIATION TYPE CHECKING
// =============================================================================

TypePtr TypeChecker::check_trait_declaration(std::shared_ptr<LM::Frontend::AST::TraitDeclaration> trait) {
    if (!trait) return nullptr;

    TraitInfo trait_info;
    trait_info.name = trait->name;
    trait_info.extends = trait->extends;
    trait_info.declaration = trait;

    // Resolve parent traits
    for (const auto& parent_name : trait->extends) {
        if (trait_declarations.find(parent_name) == trait_declarations.end()) {
            add_error("Unknown parent trait: " + parent_name, trait->line);
        }
    }

    // Register methods
    for (const auto& method : trait->methods) {
        std::string method_name = trait->name + "." + method->name;
        FunctionSignature signature;
        signature.name = method_name;
        signature.return_type = method->returnType ? resolve_type_annotation(method->returnType.value()) : type_system.NIL_TYPE;
        
        // Traits are like frames in that they have a 'this' pointer for their methods
        // but it's a polymorphic 'this' (the frame that implements the trait)
        signature.param_types.push_back(type_system.ANY_TYPE); // 'this'
        
        for (const auto& param : method->params) {
            signature.param_types.push_back(resolve_type_annotation(param.second));
        }
        function_signatures[method_name] = signature;
    }

    trait_declarations[trait->name] = trait_info;
    
        TypePtr trait_type = std::make_shared<::Type>(TypeTag::Trait);
    TraitType trait_extra;
    trait_extra.name = trait->name;
    trait_extra.extends = trait->extends;
    for (const auto& method : trait->methods) {
        TypePtr ret_type = method->returnType ? resolve_type_annotation(method->returnType.value()) : type_system.NIL_TYPE;
        trait_extra.methodSignatures.push_back({method->name, ret_type});
    }
    trait_type->extra = trait_extra;
    type_system.addUserDefinedType(trait->name, trait_type);
    trait->inferred_type = trait_type;
    
    return trait_type;
}

TypePtr TypeChecker::check_frame_declaration(std::shared_ptr<LM::Frontend::AST::FrameDeclaration> frame) {
    return check_frame_declaration_with_name(frame->name, frame);
}

TypePtr TypeChecker::check_frame_declaration_with_name(const std::string& name, std::shared_ptr<LM::Frontend::AST::FrameDeclaration> frame) {
    if (!frame) return nullptr;
    
    // Set current frame context
    auto prev_frame = current_frame;
    current_frame = frame;
    
    // Create frame info for tracking
    FrameInfo frame_info;
    frame_info.name = name;
    frame_info.declaration = frame;
    
    // Verify trait implementations recursively
    std::vector<std::string> trait_worklist = frame->implements;
    std::unordered_set<std::string> visited_traits;

    while (!trait_worklist.empty()) {
        std::string trait_name = trait_worklist.back();
        trait_worklist.pop_back();

        if (visited_traits.count(trait_name)) continue;
        visited_traits.insert(trait_name);

        auto it = trait_declarations.find(trait_name);
        if (it == trait_declarations.end()) {
            add_error("Frame '" + frame->name + "' implements unknown trait: " + trait_name, frame->line);
            continue;
        }

        const auto& trait_info = it->second;
        for (const auto& trait_method : trait_info.declaration->methods) {
            // Check if frame implements this method
            bool implemented = false;
            for (const auto& frame_method : frame->methods) {
                if (frame_method->name == trait_method->name) {
                    implemented = true;
                    break;
                }
            }
            
            if (!implemented) {
                // Check if trait has default implementation
                if (trait_method->body && !trait_method->body->statements.empty()) {
                    // It has a default implementation, we're good
                } else {
                    add_error("Frame '" + frame->name + "' does not implement required trait method: " + trait_method->name, frame->line);
                }
            }
        }

        // Add parent traits to verify them too
        for (const auto& parent : trait_info.extends) {
            trait_worklist.push_back(parent);
        }
    }

    // Check all fields
    for (const auto& field : frame->fields) {
        if (!field) continue;
        
        // Resolve field type
        TypePtr field_type = nullptr;
        if (field->type) {
            field_type = resolve_type_annotation(field->type);
        } else {
            add_error("Frame field '" + field->name + "' must have a type annotation", frame->line);
            field_type = type_system.ANY_TYPE;
        }
        
        // Check if field has a default value
        bool has_default = (field->defaultValue != nullptr);
        
        // If field has default value, check its type
        if (has_default) {
            TypePtr default_type = check_expression(field->defaultValue);
            if (!is_type_compatible(field_type, default_type)) {
                add_type_error(field_type->toString(), default_type->toString(), frame->line);
            }
        }
        
        // Store field info
        frame_info.fields.push_back({field->name, field_type});
        frame_info.field_has_default.push_back({field->name, has_default});
    }
    
    // Store frame info BEFORE checking methods so they can reference the frame
    frame_declarations[name] = frame_info;
    
    // Create a frame type
    TypePtr frame_type = type_system.createFrameType(name);
    frame->inferred_type = frame_type;
    
    // Declare the frame name as a type in the current scope
    declare_variable(name, frame_type);
    
    // Check init() method if present
    if (frame->init) {
        // Type check init method
        // Init methods are like regular methods but called during instantiation
        enter_scope();
        
        // Declare parameters
        for (const auto& param : frame->init->parameters) {
            TypePtr param_type = resolve_type_annotation(param.second);
            declare_variable(param.first, param_type);
        }
        
        // Check optional parameters
        for (const auto& opt_param : frame->init->optionalParams) {
            TypePtr param_type = resolve_type_annotation(opt_param.second.first);
            declare_variable(opt_param.first, param_type);
            
            // Check default value if present
            if (opt_param.second.second) {
                TypePtr default_type = check_expression(opt_param.second.second);
                if (!is_type_compatible(param_type, default_type)) {
                    add_type_error(param_type->toString(), default_type->toString(), frame->line);
                }
            }
        }
        
        // Check init body
        if (frame->init->body) {
            check_statement(frame->init->body);
        }
        
        exit_scope();
    }
    
    // Check deinit() method if present
    if (frame->deinit) {
        // Type check deinit method
        // Deinit methods should have no parameters
        if (!frame->deinit->parameters.empty() || !frame->deinit->optionalParams.empty()) {
            add_error("deinit() method cannot have parameters", frame->line);
        }
        
        // Check deinit body
        if (frame->deinit->body) {
            enter_scope();
            check_statement(frame->deinit->body);
            exit_scope();
        }
    }
    
    // Check other methods
    for (const auto& method : frame->methods) {
        if (!method) continue;
        
        enter_scope();
        
        // Declare parameters
        for (const auto& param : method->parameters) {
            TypePtr param_type = resolve_type_annotation(param.second);
            declare_variable(param.first, param_type);
        }
        
        // Check optional parameters
        for (const auto& opt_param : method->optionalParams) {
            TypePtr param_type = resolve_type_annotation(opt_param.second.first);
            declare_variable(opt_param.first, param_type);
            
            // Check default value if present
            if (opt_param.second.second) {
                TypePtr default_type = check_expression(opt_param.second.second);
                if (!is_type_compatible(param_type, default_type)) {
                    add_type_error(param_type->toString(), default_type->toString(), frame->line);
                }
            }
        }
        
        // Check method body
        if (method->body) {
            check_statement(method->body);
        }
        
        exit_scope();
    }
    
    // Restore previous frame context
    current_frame = prev_frame;
    
    return frame_type;
}

TypePtr TypeChecker::check_frame_instantiation_expr(std::shared_ptr<LM::Frontend::AST::FrameInstantiationExpr> expr) {
    if (!expr) return nullptr;
    
    // Look up the frame declaration
    auto frame_it = frame_declarations.find(expr->frameName);
    if (frame_it == frame_declarations.end()) {
        add_error("Unknown frame type: " + expr->frameName, expr->line);
        return type_system.ANY_TYPE;
    }
    
    const FrameInfo& frame_info = frame_it->second;
    
    // Check that all required fields are provided
    std::set<std::string> provided_fields;
    
    // Check positional arguments (if any)
    if (!expr->positionalArgs.empty()) {
        add_error("Frame instantiation does not support positional arguments. Use named arguments: " + 
                 expr->frameName + "(field1=value1, field2=value2)", expr->line);
    }
    
    // Check named arguments
    for (const auto& [field_name, field_value] : expr->namedArgs) {
        // Check if field exists in frame
        bool field_found = false;
        TypePtr expected_type = nullptr;
        
        for (size_t i = 0; i < frame_info.fields.size(); ++i) {
            if (frame_info.fields[i].first == field_name) {
                field_found = true;
                expected_type = frame_info.fields[i].second;
                break;
            }
        }
        
        if (!field_found) {
            add_error("Frame '" + expr->frameName + "' has no field named '" + field_name + "'", expr->line);
            continue;
        }
        
        // Check field value type
        TypePtr actual_type = check_expression(field_value);
        if (!is_type_compatible(expected_type, actual_type)) {
            add_type_error(expected_type->toString(), actual_type->toString(), expr->line);
        }
        
        provided_fields.insert(field_name);
    }
    
    // Check that all required fields (those without defaults) are provided
    for (size_t i = 0; i < frame_info.fields.size(); ++i) {
        const std::string& field_name = frame_info.fields[i].first;
        bool has_default = frame_info.field_has_default[i].second;
        
        if (!has_default && provided_fields.find(field_name) == provided_fields.end()) {
            add_error("Frame instantiation missing required field: '" + field_name + "'", expr->line);
        }
    }
    
    // Return the frame type
    TypePtr frame_type = type_system.createFrameType(expr->frameName);
    expr->inferred_type = frame_type;
    
    return frame_type;
}

// Helper: Collect all function dependencies (functions called by a function)
static std::set<std::string> collect_function_dependencies(
    const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& func,
    const std::unordered_map<std::string, std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>>& all_functions) {
    
    std::set<std::string> dependencies;
    if (!func || !func->body) return dependencies;
    
    // Walk the AST and find all function calls
    std::function<void(const std::shared_ptr<LM::Frontend::AST::Statement>&)> visit_stmt = 
        [&](const std::shared_ptr<LM::Frontend::AST::Statement>& stmt) {
            if (!stmt) return;
            
            // Check if it's an expression statement
            if (auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt)) {
                // Visit the expression
                std::function<void(const std::shared_ptr<LM::Frontend::AST::Expression>&)> visit_expr = 
                    [&](const std::shared_ptr<LM::Frontend::AST::Expression>& expr) {
                        if (!expr) return;
                        
                        // Check for function calls
                        if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
                            if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(call->callee)) {
                                if (all_functions.find(var->name) != all_functions.end()) {
                                    dependencies.insert(var->name);
                                }
                            }
                            // Visit arguments
                            for (const auto& arg : call->arguments) {
                                visit_expr(arg);
                            }
                        }
                        // Recursively visit sub-expressions
                        else if (auto binary = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
                            visit_expr(binary->left);
                            visit_expr(binary->right);
                        }
                        else if (auto unary = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
                            visit_expr(unary->right);
                        }
                    };
                visit_expr(expr_stmt->expression);
            }
            // Recursively visit block statements
            else if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
                for (const auto& s : block->statements) {
                    visit_stmt(s);
                }
            }
            else if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
                visit_stmt(if_stmt->thenBranch);
                if (if_stmt->elseBranch) {
                    visit_stmt(if_stmt->elseBranch);
                }
            }
            else if (auto while_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WhileStatement>(stmt)) {
                visit_stmt(while_stmt->body);
            }
            else if (auto for_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ForStatement>(stmt)) {
                visit_stmt(for_stmt->body);
            }
        };
    
    // Visit all statements in the function body
    for (const auto& stmt : func->body->statements) {
        visit_stmt(stmt);
    }
    
    return dependencies;
}

// Helper: Recursively collect all dependencies (transitive closure)
static std::set<std::string> collect_all_dependencies(
    const std::string& symbol_name,
    const std::unordered_map<std::string, std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>>& all_functions,
    std::set<std::string>& visited) {
    
    std::set<std::string> all_deps;
    if (visited.find(symbol_name) != visited.end()) {
        return all_deps;  // Already processed
    }
    visited.insert(symbol_name);
    
    auto it = all_functions.find(symbol_name);
    if (it == all_functions.end()) {
        return all_deps;  // Not a function
    }
    
    // Get direct dependencies
    auto direct_deps = collect_function_dependencies(it->second, all_functions);
    all_deps.insert(direct_deps.begin(), direct_deps.end());
    
    // Recursively get dependencies of dependencies
    for (const auto& dep : direct_deps) {
        auto transitive = collect_all_dependencies(dep, all_functions, visited);
        all_deps.insert(transitive.begin(), transitive.end());
    }
    
    return all_deps;
}

TypePtr TypeChecker::check_import_statement(std::shared_ptr<LM::Frontend::AST::ImportStatement> import_stmt) {
    if (!import_stmt) return nullptr;
    auto& manager = ModuleManager::getInstance();
    auto module = manager.load_module(import_stmt->modulePath);
    if (!module) {
        add_error("Failed to load module: " + import_stmt->modulePath, import_stmt->line);
        return nullptr;
    }

  if (import_stmt->filter && import_stmt->filter->type == LM::Frontend::AST::ImportFilterType::Show) {
        for (const auto& identifier : import_stmt->filter->identifiers) {
            if (!module->public_symbols.count(identifier)) {
                add_error(
                    "Import filter references unknown symbol '" + identifier +
                    "' in module '" + import_stmt->modulePath + "'",
                    import_stmt->line
                );
            }
        }
    }

    auto symbols_to_import = manager.filter_symbols(module, import_stmt->filter);
    std::string alias = import_stmt->alias ? import_stmt->alias.value() : "";
    if (alias.empty()) {
        size_t last_dot = import_stmt->modulePath.find_last_of('.');
        alias = (last_dot != std::string::npos) ? import_stmt->modulePath.substr(last_dot + 1) : import_stmt->modulePath;
    }
    import_aliases[alias] = import_stmt->modulePath;
    FrameInfo alias_info; alias_info.name = alias;
    frame_declarations[alias] = alias_info;
    declare_variable(alias, type_system.createFrameType(alias));
    
    // Register all symbols from the module
    for (const auto& stmt : module->ast->statements) {
        std::string name;
        if (auto f = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) name = f->name;
        else if (auto fr = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) name = fr->name;
        else if (auto v = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) name = v->name;
        else if (auto t = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) name = t->name;
        if (!name.empty() && symbols_to_import.count(name)) {
            std::vector<std::pair<std::string, bool>> target_names;
            target_names.push_back({alias + "." + name, true});
            // Always register unqualified names for type-checking imported module internals.
            // Only expose them to the program symbol table when no filter is present.
            target_names.push_back({name, !import_stmt->filter.has_value()});

            for (const auto& target : target_names) {
                const std::string& qname = target.first;
                const bool expose_to_program = target.second;
                if (expose_to_program) {
                    current_program_->imported_symbols[qname] = stmt;
                }
                if (auto f = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
                    FunctionSignature sig; sig.name = qname; sig.declaration = f;
                    // Don't resolve types here - just use ANY_TYPE to avoid type-checking in module context
                    sig.return_type = f->returnType.has_value()
                        ? resolve_type_annotation(f->returnType.value())
                        : type_system.ANY_TYPE;
                    for (const auto& p : f->params) {
                        if (p.second) {
                            sig.param_types.push_back(resolve_type_annotation(p.second));
                        } else {
                            sig.param_types.push_back(type_system.ANY_TYPE);
                        }
                    }
                    function_signatures[qname] = sig;
                    declare_variable(qname, type_system.createFunctionType({}, sig.param_types, sig.return_type));
                } else if (auto v = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
                    // For variables, just use ANY_TYPE to avoid type-checking initialization expressions
                    declare_variable(qname, type_system.ANY_TYPE);
                } else if (auto fr = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
                    FrameInfo fi; fi.name = qname; fi.declaration = fr;
                    frame_declarations[qname] = fi;
                    declare_variable(qname, type_system.createFrameType(qname));
                } else if (auto tr = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) {
                    TraitInfo ti; ti.name = qname; ti.declaration = tr; ti.extends = tr->extends;
                    trait_declarations[qname] = ti;
                    TraitType tt; tt.name = qname;
                    type_system.addUserDefinedType(qname, std::make_shared<::Type>(TypeTag::Trait, tt));
                }
            }
        }
    }
    
    return type_system.NIL_TYPE;
}

} // namespace Frontend
} // namespace LM
