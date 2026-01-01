#include "type_checker.hh"
#include "../common/debugger.hh"
#include "../memory/model.hh"
#include <sstream>
#include <stdexcept>

// =============================================================================
// TYPE CHECKER IMPLEMENTATION
// =============================================================================

bool TypeChecker::check_program(std::shared_ptr<AST::Program> program) {
    if (!program) {
        add_error("Null program provided");
        return false;
    }
    
    // Reset error state before checking
    Debugger::resetError();
    errors.clear();
    current_scope = std::make_unique<Scope>();
    
    // First pass: collect function declarations
    for (const auto& stmt : program->statements) {
        if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            check_function_declaration(func_decl);
        }
    }
    
    // Second pass: check all statements
    for (const auto& stmt : program->statements) {
        check_statement(stmt);
    }
    
    // Set the inferred type on the program node
    // For a program, we could use void type or the type of the last statement
    program->inferred_type = type_system.NIL_TYPE; // Programs don't return values
    
    return !Debugger::hasError();
}

void TypeChecker::add_error(const std::string& message, int line) {
    // Use same error system as parser - use the 7-parameter signature to avoid ambiguity
    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, 0, InterpretationStage::SEMANTIC, current_source, current_file_path, "", "");
    } else {
        Debugger::error(message, line, 0, InterpretationStage::SEMANTIC, "repl", "repl", "", "");
    }
}

void TypeChecker::add_type_error(const std::string& expected, const std::string& found, int line) {
    add_error("Type mismatch: expected " + expected + ", found " + found, line);
}

// =============================================================================
// LINEAR TYPE REFERENCE SYSTEM
// =============================================================================

void TypeChecker::check_linear_type_access(const std::string& var_name, int line) {
    // Check if this is a linear type
    if (linear_types.find(var_name) != linear_types.end()) {
        auto& linear_info = linear_types[var_name];
        
        if (linear_info.is_moved) {
            add_error("Use of moved linear type '" + var_name + "' [Mitigation: Linear types can only be used once]", line);
            return;
        }
        
        // Linear type is valid for access
        linear_info.access_count++;
    }
}

void TypeChecker::create_reference(const std::string& linear_var, const std::string& ref_var, int line, bool is_mutable) {
    if (linear_types.find(linear_var) != linear_types.end()) {
        auto& linear_info = linear_types[linear_var];
        
        if (linear_info.is_moved) {
            add_error("Cannot create reference to moved linear type '" + linear_var + "' [Mitigation: Create reference before move]", line);
            return;
        }
        
        // Check mutable aliasing rules
        check_mutable_aliasing(linear_var, ref_var, is_mutable, line);
        
        // Create reference with current generation and scope
        ReferenceInfo ref_info;
        ref_info.target_linear_var = linear_var;
        ref_info.creation_line = line;
        ref_info.is_valid = true;
        ref_info.created_generation = linear_info.current_generation;
        ref_info.is_mutable = is_mutable;
        ref_info.creation_scope = current_scope_level;
        
        references[ref_var] = ref_info;
        linear_info.references.insert(ref_var);
        
        if (is_mutable) {
            linear_info.mutable_references.insert(ref_var);
        }
        
        // Mark reference as accessing linear type
        linear_info.access_count++;
    }
}

void TypeChecker::move_linear_type(const std::string& var_name, int line) {
    if (linear_types.find(var_name) != linear_types.end()) {
        auto& linear_info = linear_types[var_name];
        
        if (linear_info.is_moved) {
            add_error("Double move of linear type '" + var_name + "' [Mitigation: Linear types can only be moved once]", line);
            return;
        }
        
        // Mark linear type as moved and increment generation
        linear_info.is_moved = true;
        linear_info.move_line = line;
        linear_info.current_generation++;  // Move to next generation
        
        // Invalidate all references - their generations no longer match
        for (const auto& ref_name : linear_info.references) {
            if (references.find(ref_name) != references.end()) {
                auto& ref_info = references[ref_name];
                
                // Check if reference generation matches current generation
                if (ref_info.created_generation != linear_info.current_generation) {
                    ref_info.is_valid = false;
                    add_error("Reference '" + ref_name + "' invalidated by generation change of '" + var_name + "' [Mitigation: References are generation-scoped]", ref_info.creation_line);
                }
            }
        }
        
        linear_info.references.clear();
    }
}

void TypeChecker::check_reference_validity(const std::string& ref_name, int line) {
    if (references.find(ref_name) != references.end()) {
        const auto& ref_info = references[ref_name];
        
        if (!ref_info.is_valid) {
            add_error("Use of invalid reference '" + ref_name + "' [Mitigation: Reference invalidated by linear type generation change]", line);
            return;
        }
        
        // Check if target linear type still exists
        if (linear_types.find(ref_info.target_linear_var) != linear_types.end()) {
            const auto& linear_info = linear_types[ref_info.target_linear_var];
            
            // Check if reference generation matches linear type current generation
            if (ref_info.created_generation != linear_info.current_generation) {
                add_error("Use of stale reference '" + ref_name + "' - generation mismatch [Mitigation: References are generation-scoped]", line);
                return;
            }
            
            if (linear_info.is_moved) {
                add_error("Use of reference '" + ref_name + "' to moved linear type [Mitigation: References die when linear type moves]", line);
            }
        }
    }
}

void TypeChecker::enter_scope() {
    current_scope_level++;
    current_scope = std::make_unique<Scope>(std::move(current_scope));
}

void TypeChecker::exit_scope() {
    current_scope_level--;
    if (current_scope && current_scope->parent) {
        current_scope = std::move(current_scope->parent);
    }
}

void TypeChecker::check_mutable_aliasing(const std::string& linear_var, const std::string& ref_var, bool is_mutable, int line) {
    if (linear_types.find(linear_var) != linear_types.end()) {
        const auto& linear_info = linear_types[linear_var];
        
        if (is_mutable) {
            // Cannot create mutable reference if other references exist
            if (linear_info.references.size() > 0) {
                add_error("Cannot create mutable reference '" + ref_var + "' - other references to '" + linear_var + "' exist [Mitigation: Mutable references require exclusive access]", line);
                return;
            }
            
            // Cannot create multiple mutable references
            if (linear_info.mutable_references.size() > 0) {
                add_error("Multiple mutable references to '" + linear_var + "' not allowed [Mitigation: Only one mutable reference per linear type]", line);
                return;
            }
        } else {
            // Cannot create immutable reference if mutable reference exists
            if (linear_info.mutable_references.size() > 0) {
                add_error("Cannot create immutable reference '" + ref_var + "' - mutable reference to '" + linear_var + "' exists [Mitigation: Mutable references are exclusive]", line);
                return;
            }
        }
    }
}

void TypeChecker::check_scope_escape(const std::string& ref_name, int target_scope, int line) {
    if (references.find(ref_name) != references.end()) {
        const auto& ref_info = references[ref_name];
        
        if (ref_info.creation_scope > target_scope) {
            add_error("Reference '" + ref_name + "' would escape its creation scope [Mitigation: References cannot outlive their scope - would create dangling reference]", line);
        }
        
        if (ref_info.is_mutable && ref_info.creation_scope > target_scope) {
            add_error("Mutable reference '" + ref_name + "' cannot escape scope [Mitigation: Mutable references have stricter lifetime requirements]", line);
        }
    }
}

void TypeChecker::declare_variable(const std::string& name, TypePtr type) {
    if (current_scope) {
        current_scope->declare(name, type);
    }
}

TypePtr TypeChecker::lookup_variable(const std::string& name) {
    return current_scope ? current_scope->lookup(name) : nullptr;
}

// =============================================================================
// MEMORY SAFETY IMPLEMENTATION
// =============================================================================

void TypeChecker::enter_memory_region() {
    region_stack.push_back(current_region_id);
    current_generation++;
    current_region_id++;
}

void TypeChecker::exit_memory_region() {
    if (!region_stack.empty()) {
        current_region_id = region_stack.back();
        region_stack.pop_back();
        current_generation = (current_generation > 0) ? current_generation - 1 : 0;
    }
    
    // Drop all variables in this region that haven't been dropped
    for (auto it = variable_memory_info.begin(); it != variable_memory_info.end();) {
        if (it->second.region_id == current_region_id && it->second.memory_state != "dropped") {
            // Check if this is a class/struct type that needs explicit drop
            if (it->second.type && it->second.type->tag == TypeTag::Class) {
                add_error("Variable '" + it->first + "' of type '" + 
                         it->second.type->toString() + "' was not dropped before going out of scope");
            }
            it = variable_memory_info.erase(it);
        } else {
            ++it;
        }
    }
}

void TypeChecker::declare_variable_memory(const std::string& name, TypePtr type) {
    VariableInfo info;
    info.type = type;
    info.memory_state = "uninitialized";
    info.region_id = current_region_id;
    info.alloc_id = next_alloc_id++;
    variable_memory_info[name] = info;
}

void TypeChecker::mark_variable_initialized(const std::string& name) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "uninitialized") {
            it->second.memory_state = "owned";
        }
    }
}

void TypeChecker::check_memory_leaks(int line) {
    for (const auto& [name, info] : variable_memory_info) {
        if (info.memory_state == "owned" && info.region_id == current_region_id) {
            // Variable is still owned in current region - potential leak
            add_error("Memory leak: variable '" + name + "' of type '" + 
                     info.type->toString() + "' was not freed before going out of scope [Mitigation: Use linear types, region GC, compile-time analysis]", line);
        }
    }
}

void TypeChecker::check_use_after_free(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "dropped") {
            add_error("Use-after-free: variable '" + name + "' was freed and is no longer accessible [Mitigation: Linear types, regions, lifetime checks]", line);
        }
    }
}

void TypeChecker::check_dangling_pointer(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "moved" || it->second.memory_state == "dropped") {
            add_error("Dangling pointer: variable '" + name + "' points to invalid memory [Mitigation: Region + generational references]", line);
        }
    }
}

void TypeChecker::check_double_free(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "dropped") {
            add_error("Double free: variable '" + name + "' was already freed [Mitigation: Single ownership, compile-time drop]", line);
        }
    }
}

void TypeChecker::check_multiple_owners(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        // Check if variable is being shared/copied when it should be unique
        if (it->second.memory_state == "owned") {
            // In a real implementation, we'd track reference counts
            add_error("Multiple owners detected: variable '" + name + "' should have single ownership [Mitigation: Single ownership, compile-time drop]", line);
        }
    }
}

void TypeChecker::check_buffer_overflow(const std::string& array_name, const std::string& index_expr, int line) {
    // Simplified check - in real implementation we'd track array bounds
    add_error("Buffer overflow: array '" + array_name + "' access with index '" + index_expr + "' may exceed bounds [Mitigation: Bounds checks, typed arrays]", line);
}

void TypeChecker::check_uninitialized_use(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "uninitialized") {
            add_error("Uninitialized use: variable '" + name + "' used before initialization [Mitigation: Require initialization, zero-fill debug]", line);
        }
    }
}

void TypeChecker::check_invalid_type(const std::string& var_name, TypePtr expected_type, TypePtr actual_type, int line) {
    if (!is_type_compatible(expected_type, actual_type)) {
        add_error("Invalid type: variable '" + var_name + "' type mismatch [Mitigation: Strong type system, no implicit punning]", line);
    }
}

void TypeChecker::check_misalignment(const std::string& ptr_name, int line) {
    add_error("Misalignment: pointer '" + ptr_name + "' may not be properly aligned [Mitigation: Enforce alignment in allocator]", line);
}

void TypeChecker::check_heap_corruption(const std::string& operation, int line) {
    add_error("Heap corruption detected during: " + operation + " [Mitigation: Linear types, bounds checks]", line);
}

void TypeChecker::check_race_condition(const std::string& shared_var, int line) {
    add_error("Race condition: concurrent access to variable '" + shared_var + "' [Mitigation: Ownership, borrow rules, thread-local memory]", line);
}

void TypeChecker::check_variable_use(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "moved") {
            add_error("Use after move: variable '" + name + "' was moved and is no longer accessible [Mitigation: Linear types, regions, lifetime checks]", line);
            check_dangling_pointer(name, line);
        } else if (it->second.memory_state == "dropped") {
            add_error("Use after drop: variable '" + name + "' was dropped and is no longer accessible [Mitigation: Single ownership, compile-time drop]", line);
            check_use_after_free(name, line);
        } else if (it->second.memory_state == "uninitialized") {
            add_error("Use before initialization: variable '" + name + "' is used before being initialized [Mitigation: Require initialization, zero-fill debug]", line);
            check_uninitialized_use(name, line);
        }
    }
}

void TypeChecker::check_variable_move(const std::string& name) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "moved") {
            add_error("Double move: variable '" + name + "' was already moved");
        } else if (it->second.memory_state == "dropped") {
            add_error("Move after drop: variable '" + name + "' was already dropped");
        } else {
            it->second.memory_state = "moved";
        }
    }
}

void TypeChecker::check_variable_drop(const std::string& name) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "dropped") {
            add_error("Double drop: variable '" + name + "' was already dropped");
        } else if (it->second.memory_state == "moved") {
            add_error("Drop after move: cannot drop moved variable '" + name + "'");
        } else {
            it->second.memory_state = "dropped";
        }
    }
}

void TypeChecker::check_borrow_safety(const std::string& var_name) {
    auto it = variable_memory_info.find(var_name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state != "owned") {
            add_error("Cannot borrow variable '" + var_name + "' in state '" + 
                     it->second.memory_state + "'; only owned values can be borrowed");
        }
    }
}

void TypeChecker::check_escape_analysis(const std::string& var_name, const std::string& target_context) {
    auto it = variable_memory_info.find(var_name);
    if (it != variable_memory_info.end()) {
        // Simple escape analysis: if target_context is different from current region
        // and the variable is a class/struct, it might escape
        if (it->second.type && it->second.type->tag == TypeTag::Class) {
            if (target_context != "current_function") {
                add_error("Variable '" + var_name + "' of type '" + 
                         it->second.type->toString() + "' cannot escape current scope");
            }
        }
    }
}

bool TypeChecker::is_variable_alive(const std::string& name) {
    auto it = variable_memory_info.find(name);
    return (it != variable_memory_info.end() && 
            (it->second.memory_state == "owned" || it->second.memory_state == "borrowed"));
}

void TypeChecker::mark_variable_moved(const std::string& name) {
    check_variable_move(name);
}

void TypeChecker::mark_variable_dropped(const std::string& name) {
    check_variable_drop(name);
}

TypePtr TypeChecker::check_statement(std::shared_ptr<AST::Statement> stmt) {
    if (!stmt) return nullptr;
    
    if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        return check_function_declaration(func_decl);
    } else if (auto var_decl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        return check_var_declaration(var_decl);
    } else if (auto type_decl = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) {
        return check_type_declaration(type_decl);
    } else if (auto block = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        return check_block_statement(block);
    } else if (auto if_stmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        return check_if_statement(if_stmt);
    } else if (auto while_stmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        return check_while_statement(while_stmt);
    } else if (auto for_stmt = std::dynamic_pointer_cast<AST::ForStatement>(stmt)) {
        return check_for_statement(for_stmt);
    } else if (auto return_stmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        return check_return_statement(return_stmt);
    } else if (auto print_stmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        return check_print_statement(print_stmt);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        return check_expression(expr_stmt->expression);
    }
    
    return nullptr;
}

TypePtr TypeChecker::check_function_declaration(std::shared_ptr<AST::FunctionDeclaration> func) {
    if (!func) return nullptr;
    
    // Enter new memory region for this function
    enter_memory_region();
    
    // Resolve return type
    TypePtr return_type = type_system.STRING_TYPE; // Default
    if (func->returnType) {
        return_type = resolve_type_annotation(func->returnType.value());
    }
    
    // Create function signature
    FunctionSignature signature;
    signature.name = func->name;
    signature.return_type = return_type;
    signature.declaration = func;
    
    // Check parameters
    for (const auto& param : func->params) {
        TypePtr param_type = type_system.STRING_TYPE; // Default
        if (param.second) {
            param_type = resolve_type_annotation(param.second);
        }
        signature.param_types.push_back(param_type);
    }
    
    // Check optional parameters
    for (const auto& optional_param : func->optionalParams) {
        TypePtr param_type = type_system.STRING_TYPE; // Default
        if (optional_param.second.first) {
            param_type = resolve_type_annotation(optional_param.second.first);
        }
        signature.param_types.push_back(param_type);
    }
    
    function_signatures[func->name] = signature;
    
    // Declare the function name as a variable in the current scope
    // This allows the function to be called by name
    TypePtr function_type = type_system.FUNCTION_TYPE;
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
    
    // Exit scope and memory region
    exit_scope();
    exit_memory_region();
    
    current_function = nullptr;
    current_return_type = nullptr;
    
    func->inferred_type = return_type;
    return return_type;
}

TypePtr TypeChecker::check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl) {
    if (!var_decl) return nullptr;
    
    TypePtr declared_type = nullptr;
    if (var_decl->type) {
        declared_type = resolve_type_annotation(var_decl->type.value());
    }
    
    TypePtr init_type = nullptr;
    if (var_decl->initializer) {
        init_type = check_expression(var_decl->initializer);
        
        // Check if initializing from another variable (potential move)
        if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(var_decl->initializer)) {
            // For complex types, this would be a move
            // For now, we'll implement basic move semantics for all types
            check_variable_move(var_expr->name);
        }
    }
    
    TypePtr final_type = nullptr;
    
    if (declared_type && init_type) {
        // Both declared and initialized - check compatibility
        if (is_type_compatible(declared_type, init_type)) {
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

TypePtr TypeChecker::check_type_declaration(std::shared_ptr<AST::TypeDeclaration> type_decl) {
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

TypePtr TypeChecker::check_block_statement(std::shared_ptr<AST::BlockStatement> block) {
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

TypePtr TypeChecker::check_if_statement(std::shared_ptr<AST::IfStatement> if_stmt) {
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
    TypePtr result_type = type_system.STRING_TYPE; // if statements don't produce a value
    if_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_while_statement(std::shared_ptr<AST::WhileStatement> while_stmt) {
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
    TypePtr result_type = type_system.STRING_TYPE;
    while_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_for_statement(std::shared_ptr<AST::ForStatement> for_stmt) {
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
    TypePtr result_type = type_system.STRING_TYPE;
    for_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_return_statement(std::shared_ptr<AST::ReturnStatement> return_stmt) {
    if (!return_stmt) return nullptr;
    
    TypePtr return_type = nullptr;
    if (return_stmt->value) {
        return_type = check_expression(return_stmt->value);
        
        // Auto-wrap in ok() if function returns error union type and value is not already wrapped
        if (current_return_type && type_system.isFallibleType(current_return_type)) {
            // Check if the return value is already an error construct or ok construct
            bool is_already_wrapped = false;
            if (auto error_construct = std::dynamic_pointer_cast<AST::ErrorConstructExpr>(return_stmt->value)) {
                is_already_wrapped = true;
            } else if (auto ok_construct = std::dynamic_pointer_cast<AST::OkConstructExpr>(return_stmt->value)) {
                is_already_wrapped = true;
            }
            
            if (!is_already_wrapped) {
                // Get the expected success type from the function's return type
                TypePtr expected_success_type = type_system.getFallibleSuccessType(current_return_type);
                
                if (expected_success_type && is_type_compatible(expected_success_type, return_type)) {
                    // Automatically wrap the return value in ok()
                    auto ok_construct = std::make_shared<AST::OkConstructExpr>();
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

TypePtr TypeChecker::check_print_statement(std::shared_ptr<AST::PrintStatement> print_stmt) {
    if (!print_stmt) return nullptr;
    
    for (const auto& arg : print_stmt->arguments) {
        check_expression(arg);
    }
    
    // Set the inferred type on the print statement
    TypePtr result_type = type_system.STRING_TYPE;
    print_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_expression(std::shared_ptr<AST::Expression> expr) {
    if (!expr) return nullptr;
    
    TypePtr type = nullptr;
    
    if (auto literal = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        type = check_literal_expr(literal);
    } else if (auto call = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        type = check_call_expr(call);
    } else if (auto variable = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        type = check_variable_expr(variable);
    } else if (auto binary = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        type = check_binary_expr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        type = check_unary_expr(unary);
    } else if (auto assign = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
        type = check_assign_expr(assign);
    } else if (auto grouping = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        type = check_grouping_expr(grouping);
    } else if (auto member = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        type = check_member_expr(member);
    } else if (auto index = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
        type = check_index_expr(index);
    } else if (auto list = std::dynamic_pointer_cast<AST::ListExpr>(expr)) {
        type = check_list_expr(list);
    } else if (auto tuple = std::dynamic_pointer_cast<AST::TupleExpr>(expr)) {
        type = check_tuple_expr(tuple);
    } else if (auto dict = std::dynamic_pointer_cast<AST::DictExpr>(expr)) {
        type = check_dict_expr(dict);
    } else if (auto interpolated = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(expr)) {
        type = check_interpolated_string_expr(interpolated);
    } else if (auto lambda = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) {
        type = check_lambda_expr(lambda);
    } else if (auto error_construct = std::dynamic_pointer_cast<AST::ErrorConstructExpr>(expr)) {
        type = check_error_construct_expr(error_construct);
    } else if (auto ok_construct = std::dynamic_pointer_cast<AST::OkConstructExpr>(expr)) {
        type = check_ok_construct_expr(ok_construct);
    } else if (auto fallible = std::dynamic_pointer_cast<AST::FallibleExpr>(expr)) {
        type = check_fallible_expr(fallible);
    } else {
        add_error("Unknown expression type", expr->line);
        type = type_system.STRING_TYPE; // Default fallback
    }
    
    // Set the inferred type on the expression node
    expr->inferred_type = type;
    
    return type;
}

TypePtr TypeChecker::check_literal_expr(std::shared_ptr<AST::LiteralExpr> expr) {
    if (!expr) return nullptr;
    
    // Set type based on the literal value
    if (std::holds_alternative<std::string>(expr->value)) {
        // Check if it's a numeric string
        const std::string& str = std::get<std::string>(expr->value);
        bool is_numeric = !str.empty() && (str[0] == '-' || str[0] == '+' || 
                          (str[0] >= '0' && str[0] <= '9'));
        for (size_t i = 1; i < str.size() && is_numeric; i++) {
            if (str[i] != '.' && !(str[i] >= '0' && str[i] <= '9')) {
                is_numeric = false;
            }
        }
        
        if (is_numeric) {
            // Check if it contains a decimal point to determine if it's a float
            bool is_float = false;
            for (size_t i = 0; i < str.size(); i++) {
                if (str[i] == '.') {
                    is_float = true;
                    break;
                }
            }
            
            if (is_float) {
                expr->inferred_type = type_system.FLOAT64_TYPE;
                return type_system.FLOAT64_TYPE;
            } else {
                expr->inferred_type = type_system.INT64_TYPE;
                return type_system.INT64_TYPE;
            }
        } else {
            expr->inferred_type = type_system.STRING_TYPE;
            return type_system.STRING_TYPE;
        }
    } else if (std::holds_alternative<bool>(expr->value)) {
        expr->inferred_type = type_system.BOOL_TYPE;
        return type_system.BOOL_TYPE;
    } else if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        expr->inferred_type = type_system.NIL_TYPE;
        return type_system.NIL_TYPE;
    }
    
    expr->inferred_type = type_system.STRING_TYPE;
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_variable_expr(std::shared_ptr<AST::VariableExpr> expr) {
    if (!expr) return nullptr;
    
    // Check if this is a reference
    if (references.find(expr->name) != references.end()) {
        check_reference_validity(expr->name, expr->line);
        
        // Get the type from the target linear type
        const auto& ref_info = references[expr->name];
        TypePtr target_type = lookup_variable(ref_info.target_linear_var);
        if (target_type) {
            expr->inferred_type = target_type;
            return target_type;
        }
    }
    
    // Check linear type access
    check_linear_type_access(expr->name, expr->line);
    
    TypePtr type = lookup_variable(expr->name);
    if (!type) {
        add_error("Undefined variable: " + expr->name + " [Mitigation: Declare variable before use]", expr->line);
        return nullptr;
    }
    
    // Check memory safety before using the variable
    check_variable_use(expr->name, expr->line);
    
    expr->inferred_type = type;
    return type;
}

TypePtr TypeChecker::check_binary_expr(std::shared_ptr<AST::BinaryExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr left_type = check_expression(expr->left);
    TypePtr right_type = check_expression(expr->right);
    
    switch (expr->op) {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::STAR:
        case TokenType::SLASH:
            // Arithmetic operations
            if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
                return promote_numeric_types(left_type, right_type);
            } else if (expr->op == TokenType::PLUS && 
                      (is_string_type(left_type) || is_string_type(right_type))) {
                return type_system.STRING_TYPE;
            }
            add_error("Invalid operand types for arithmetic operation", expr->line);
            return type_system.INT_TYPE;
            
        case TokenType::EQUAL_EQUAL:
        case TokenType::BANG_EQUAL:
        case TokenType::LESS:
        case TokenType::LESS_EQUAL:
        case TokenType::GREATER:
        case TokenType::GREATER_EQUAL:
            // Comparison operations
            return type_system.BOOL_TYPE;
            
        case TokenType::AND:
        case TokenType::OR:
            // Logical operations
            if (is_boolean_type(left_type) && is_boolean_type(right_type)) {
                return type_system.BOOL_TYPE;
            }
            add_error("Logical operations require boolean operands", expr->line);
            return type_system.BOOL_TYPE;
            
        case TokenType::MODULUS:
        case TokenType::POWER:
            if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
                return promote_numeric_types(left_type, right_type);
            }
            add_error("Invalid operand types for arithmetic operation", expr->line);
            return type_system.INT_TYPE;
        default:
            add_error("Unsupported binary operator", expr->line);
            return type_system.STRING_TYPE;
    }
}

TypePtr TypeChecker::check_unary_expr(std::shared_ptr<AST::UnaryExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr right_type = check_expression(expr->right);
    
    switch (expr->op) {
        case TokenType::BANG:
            // Logical NOT
            if (!is_boolean_type(right_type)) {
                add_type_error("bool", right_type->toString(), expr->line);
            }
            return type_system.BOOL_TYPE;
            
        case TokenType::MINUS:
        case TokenType::PLUS:
            // Numeric negation
            if (!is_numeric_type(right_type)) {
                add_type_error("numeric", right_type->toString(), expr->line);
            }
            return right_type;
            
        default:
            add_error("Unsupported unary operator", expr->line);
            return right_type;
    }
}

TypePtr TypeChecker::check_call_expr(std::shared_ptr<AST::CallExpr> expr) {
    if (!expr) return nullptr;
    
    // Check arguments first
    std::vector<TypePtr> arg_types;
    for (const auto& arg : expr->arguments) {
        arg_types.push_back(check_expression(arg));
    }
    
    // Check if callee is a function (before checking the callee as an expression)
    if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        TypePtr result_type = nullptr;
        if (check_function_call(var_expr->name, arg_types, result_type)) {
            expr->inferred_type = result_type;
            return result_type;
        }
    }
    
    // If not a known function, check the callee as an expression
    TypePtr callee_type = check_expression(expr->callee);
    
    add_error("Cannot call non-function value", expr->line);
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_assign_expr(std::shared_ptr<AST::AssignExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr value_type = check_expression(expr->value);
    
    // For simple variable assignment
    if (!expr->object && !expr->member && !expr->index) {
        TypePtr var_type = lookup_variable(expr->name);
        if (var_type) {
            if (!is_type_compatible(var_type, value_type)) {
                add_type_error(var_type->toString(), value_type->toString(), expr->line);
            }
            
            // Check if we're assigning from another variable (create reference or move)
            if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->value)) {
                if (linear_types.find(var_expr->name) != linear_types.end()) {
                    // This is a linear type - move it and increment generation
                    move_linear_type(var_expr->name, var_expr->line);
                    
                    // The target becomes the new owner with updated generation
                    LinearTypeInfo new_linear_info;
                    new_linear_info.is_moved = false;
                    new_linear_info.access_count = 1;
                    new_linear_info.current_generation = linear_types[var_expr->name].current_generation;
                    linear_types[expr->name] = new_linear_info;
                } else {
                    // Regular variable - create reference
                    create_reference(var_expr->name, expr->name, expr->line);
                }
            }
        } else {
            // Implicit variable declaration
            declare_variable(expr->name, value_type);
            declare_variable_memory(expr->name, value_type);  // Track memory for new variable
            
            // New variables are linear types by default
            LinearTypeInfo linear_info;
            linear_info.is_moved = false;
            linear_info.access_count = 0;
            linear_types[expr->name] = linear_info;
        }
    }
    
    return value_type;
}

TypePtr TypeChecker::check_grouping_expr(std::shared_ptr<AST::GroupingExpr> expr) {
    if (!expr) return nullptr;
    return check_expression(expr->expression);
}

TypePtr TypeChecker::check_member_expr(std::shared_ptr<AST::MemberExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr object_type = check_expression(expr->object);
    
    // For now, assume all member access returns string
    // TODO: Implement proper class/struct type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_index_expr(std::shared_ptr<AST::IndexExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr object_type = check_expression(expr->object);
    TypePtr index_type = check_expression(expr->index);
    
    // For now, assume all indexing returns string
    // TODO: Implement proper collection type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_list_expr(std::shared_ptr<AST::ListExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr element_type = nullptr;
    for (const auto& elem : expr->elements) {
        TypePtr elem_type = check_expression(elem);
        if (element_type) {
            element_type = get_common_type(element_type, elem_type);
        } else {
            element_type = elem_type;
        }
    }
    
    // Create list type
    // TODO: Implement proper list type creation
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_tuple_expr(std::shared_ptr<AST::TupleExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& elem : expr->elements) {
        check_expression(elem);
    }
    
    // TODO: Implement proper tuple type creation
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_dict_expr(std::shared_ptr<AST::DictExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& [key, value] : expr->entries) {
        check_expression(key);
        check_expression(value);
    }
    
    // TODO: Implement proper dict type creation
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_interpolated_string_expr(std::shared_ptr<AST::InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& part : expr->parts) {
        if (std::holds_alternative<std::shared_ptr<AST::Expression>>(part)) {
            check_expression(std::get<std::shared_ptr<AST::Expression>>(part));
        }
    }
    
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_lambda_expr(std::shared_ptr<AST::LambdaExpr> expr) {
    if (!expr) return nullptr;
    
    // TODO: Implement proper lambda type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_error_construct_expr(std::shared_ptr<AST::ErrorConstructExpr> expr) {
    if (!expr) return nullptr;
    
    // For err() constructs, we need to infer the Type? from the function's return type context
    // If we're in a function that returns Type?, then err() should return that same Type?
    
    TypePtr error_union_type = nullptr;
    
    if (current_return_type && current_return_type->tag == TypeTag::ErrorUnion) {
        // We're in a function that returns a fallible type, use that type
        error_union_type = current_return_type;
    } else if (current_return_type && type_system.isFallibleType(current_return_type)) {
        // We're in a function that returns a fallible type, use that type
        error_union_type = current_return_type;
    } else {
        // Fallback: create a generic error union type
        // This should ideally be inferred from context in a full implementation
        error_union_type = type_system.createFallibleType(type_system.STRING_TYPE);
    }
    
    expr->inferred_type = error_union_type;
    return error_union_type;
}

TypePtr TypeChecker::check_ok_construct_expr(std::shared_ptr<AST::OkConstructExpr> expr) {
    if (!expr) return nullptr;
    
    // Check the value expression first
    TypePtr value_type = check_expression(expr->value);
    if (!value_type) {
        add_error("Failed to determine type of ok() value", expr->line);
        return nullptr;
    }
    
    // Create a fallible type (Type?) with the value type as the success type
    // If we're in a function context, try to match the return type
    TypePtr ok_type = nullptr;
    
    if (current_return_type && current_return_type->tag == TypeTag::ErrorUnion) {
        // We're in a function that returns a fallible type
        // Check if the value type is compatible with the expected success type
        TypePtr expected_success_type = type_system.getFallibleSuccessType(current_return_type);
        if (expected_success_type && is_type_compatible(expected_success_type, value_type)) {
            ok_type = current_return_type;
        } else {
            add_error("ok() value type doesn't match function return type", expr->line);
            ok_type = type_system.createFallibleType(value_type);
        }
    } else {
        // Create a new fallible type with the value type
        ok_type = type_system.createFallibleType(value_type);
    }
    
    expr->inferred_type = ok_type;
    return ok_type;
}

TypePtr TypeChecker::check_fallible_expr(std::shared_ptr<AST::FallibleExpr> expr) {
    if (!expr) return nullptr;
    
    // Check the expression that might be fallible
    TypePtr expr_type = check_expression(expr->expression);
    if (!expr_type) {
        add_error("Failed to determine type of fallible expression", expr->line);
        return nullptr;
    }
    
    // The expression should be a fallible type (Type?)
    if (!type_system.isFallibleType(expr_type)) {
        add_error("? operator can only be used on fallible types (Type?)", expr->line);
        return nullptr;
    }
    
    // The ? operator unwraps the fallible type, returning the success type
    TypePtr success_type = type_system.getFallibleSuccessType(expr_type);
    if (!success_type) {
        add_error("Failed to extract success type from fallible type", expr->line);
        return type_system.STRING_TYPE;
    }
    
    expr->inferred_type = success_type;
    return success_type;
}

TypePtr TypeChecker::resolve_type_annotation(std::shared_ptr<AST::TypeAnnotation> annotation) {
    if (!annotation) return nullptr;
    
    // Handle structural types (basic support - just return a placeholder for now)
    if (annotation->isStructural && !annotation->structuralFields.empty()) {
        // For now, structural types are not fully implemented in the type system
        // We'll return a placeholder type to indicate the parsing worked
        add_error("Structural types are parsed but not yet fully implemented in the type system");
        return type_system.STRING_TYPE; // Placeholder
    }
    
    // Handle union types
    if (annotation->isUnion && !annotation->unionTypes.empty()) {
        std::vector<TypePtr> union_member_types;
        
        // Resolve each type in the union
        for (const auto& union_member : annotation->unionTypes) {
            TypePtr member_type = resolve_type_annotation(union_member);
            if (member_type) {
                union_member_types.push_back(member_type);
            }
        }
        
        if (!union_member_types.empty()) {
            // Create a union type using the type system
            return type_system.createUnionType(union_member_types);
        }
    }
    
    // First try to get the base type from the type system (handles built-in types and aliases)
    TypePtr base_type = type_system.getType(annotation->typeName);
    if (!base_type) {
        // Check if it's a registered type alias
        base_type = type_system.getTypeAlias(annotation->typeName);
    }
    
    if (!base_type) {
        // Handle special cases that might not be in the type system yet
        if (annotation->typeName == "atomic") {
            // atomic is an alias for i64
            base_type = type_system.INT64_TYPE;
        } else if (annotation->typeName == "channel") {
            // channel type is represented as i64 (channel handle)
            base_type = type_system.INT64_TYPE;
        } else if (annotation->typeName == "nil") {
            base_type = type_system.NIL_TYPE;
        } else {
            // If it's not a built-in type, it might be a user-defined type alias
            // For now, we'll return STRING_TYPE as fallback, but this should be improved
            // to properly handle type aliases and union types
            add_error("Unknown type: " + annotation->typeName);
            return type_system.STRING_TYPE;
        }
    }
    
    // Handle optional types (e.g., str?, int?) - unified Type? system
    if (annotation->isOptional) {
        // Create a fallible type (Type?) using the unified error system
        // Type? is syntactic sugar for Result<Type, DefaultError>
        return type_system.createFallibleType(base_type);
    }
    
    return base_type;
}

bool TypeChecker::is_type_compatible(TypePtr expected, TypePtr actual) {
    return type_system.isCompatible(actual, expected);
}

TypePtr TypeChecker::get_common_type(TypePtr left, TypePtr right) {
    return type_system.getCommonType(left, right);
}

bool TypeChecker::can_implicitly_convert(TypePtr from, TypePtr to) {
    // Simple conversion check - can be expanded later
    if (!from || !to) return false;
    if (from == to) return true;
    if (to->tag == TypeTag::Any) return true;
    
    // Numeric conversions
    bool from_is_numeric = (from->tag == TypeTag::Int || from->tag == TypeTag::Int8 || 
                           from->tag == TypeTag::Int16 || from->tag == TypeTag::Int32 || 
                           from->tag == TypeTag::Int64 || from->tag == TypeTag::Int128 ||
                           from->tag == TypeTag::UInt || from->tag == TypeTag::UInt8 || 
                           from->tag == TypeTag::UInt16 || from->tag == TypeTag::UInt32 || 
                           from->tag == TypeTag::UInt64 || from->tag == TypeTag::UInt128 ||
                           from->tag == TypeTag::Float32 || from->tag == TypeTag::Float64);
    
    bool to_is_numeric = (to->tag == TypeTag::Int || to->tag == TypeTag::Int8 || 
                         to->tag == TypeTag::Int16 || to->tag == TypeTag::Int32 || 
                         to->tag == TypeTag::Int64 || to->tag == TypeTag::Int128 ||
                         to->tag == TypeTag::UInt || to->tag == TypeTag::UInt8 || 
                         to->tag == TypeTag::UInt16 || to->tag == TypeTag::UInt32 || 
                         to->tag == TypeTag::UInt64 || to->tag == TypeTag::UInt128 ||
                         to->tag == TypeTag::Float32 || to->tag == TypeTag::Float64);
    
    return from_is_numeric && to_is_numeric;
}

bool TypeChecker::check_function_call(const std::string& func_name, 
                                     const std::vector<TypePtr>& arg_types,
                                     TypePtr& result_type) {
    auto it = function_signatures.find(func_name);
    if (it == function_signatures.end()) {
        add_error("Undefined function: " + func_name);
        return false;
    }
    
    const FunctionSignature& sig = it->second;
    
    if (!validate_argument_types(sig.param_types, arg_types, func_name)) {
        return false;
    }
    
    result_type = sig.return_type;
    return true;
}

bool TypeChecker::validate_argument_types(const std::vector<TypePtr>& expected,
                                         const std::vector<TypePtr>& actual,
                                         const std::string& func_name) {
    // For now, we need to get the function declaration to check optional parameters
    auto func_it = function_signatures.find(func_name);
    if (func_it == function_signatures.end()) {
        return false;
    }
    
    const FunctionSignature& sig = func_it->second;
    auto func_decl = sig.declaration;
    
    if (!func_decl) {
        // Fallback to strict checking if we don't have the declaration
        if (expected.size() != actual.size()) {
            add_error("Function " + func_name + " expects " + 
                     std::to_string(expected.size()) + " arguments, got " + 
                     std::to_string(actual.size()));
            return false;
        }
    } else {
        // Check argument count considering optional parameters
        size_t min_args = func_decl->params.size(); // Required parameters
        size_t max_args = func_decl->params.size() + func_decl->optionalParams.size(); // All parameters
        
        if (actual.size() < min_args || actual.size() > max_args) {
            if (min_args == max_args) {
                add_error("Function " + func_name + " expects " + 
                         std::to_string(min_args) + " arguments, got " + 
                         std::to_string(actual.size()));
            } else {
                add_error("Function " + func_name + " expects " + 
                         std::to_string(min_args) + "-" + std::to_string(max_args) + 
                         " arguments, got " + std::to_string(actual.size()));
            }
            return false;
        }
    }
    
    // Check type compatibility for provided arguments
    for (size_t i = 0; i < actual.size() && i < expected.size(); ++i) {
        if (!is_type_compatible(expected[i], actual[i])) {
            add_error("Argument " + std::to_string(i + 1) + " of function " + 
                     func_name + " expects " + expected[i]->toString() +
                     ", got " + actual[i]->toString());
            return false;
        }
    }
    
    return true;
}

bool TypeChecker::is_numeric_type(TypePtr type) {
    return type && (type->tag == TypeTag::Int || type->tag == TypeTag::Int8 || 
                   type->tag == TypeTag::Int16 || type->tag == TypeTag::Int32 || 
                   type->tag == TypeTag::Int64 || type->tag == TypeTag::Int128 ||
                   type->tag == TypeTag::UInt || type->tag == TypeTag::UInt8 || 
                   type->tag == TypeTag::UInt16 || type->tag == TypeTag::UInt32 || 
                   type->tag == TypeTag::UInt64 || type->tag == TypeTag::UInt128 ||
                   type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64);
}

bool TypeChecker::is_boolean_type(TypePtr type) {
    if (!type) return false;
    
    // Direct boolean type
    if (type->tag == TypeTag::Bool) {
        return true;
    }
    
    // Union types (including optional types) can be used in boolean contexts
    if (type->tag == TypeTag::Union) {
        return true; // Optional types like str? can be used in if conditions
    }
    
    // ErrorUnion types (fallible types like str?) can be used in boolean contexts
    if (type->tag == TypeTag::ErrorUnion) {
        return true; // Fallible types like str? can be used in if conditions
    }
    
    return false;
}

bool TypeChecker::is_string_type(TypePtr type) {
    return type && type->tag == TypeTag::String;
}

TypePtr TypeChecker::promote_numeric_types(TypePtr left, TypePtr right) {
    return get_common_type(left, right);
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
}

// =============================================================================
// TYPE CHECKER FACTORY IMPLEMENTATION
// =============================================================================

namespace TypeCheckerFactory {

TypeCheckResult check_program(std::shared_ptr<AST::Program> program, const std::string& source, const std::string& file_path) {
    // Create memory manager and region for type system
    static MemoryManager<> memoryManager;
    static MemoryManager<>::Region memoryRegion(memoryManager);
    static TypeSystem type_system(memoryManager, memoryRegion);
    auto checker = create(type_system);
    
    // Set source context for error reporting
    checker->set_source_context(source, file_path);
    
    TypeCheckResult result(program, type_system, checker->check_program(program), checker->get_errors());
    
    return result;
}

std::unique_ptr<TypeChecker> create(TypeSystem& type_system) {
    auto checker = std::make_unique<TypeChecker>(type_system);
    
    // Register builtin functions
    register_builtin_functions(*checker);
    
    return checker;
}

void register_builtin_functions(TypeChecker& checker) {
    auto& ts = checker.get_type_system();
    
    // Math functions
    checker.register_builtin_function("abs", {ts.INT_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("fabs", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("sqrt", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("cbrt", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("pow", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("exp", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("exp2", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("log", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("log10", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("log2", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // Trigonometric functions
    checker.register_builtin_function("sin", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("cos", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("tan", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("asin", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("acos", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("atan", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("atan2", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // Hyperbolic functions
    checker.register_builtin_function("sinh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("cosh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("tanh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("asinh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("acosh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("atanh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // Rounding functions
    checker.register_builtin_function("ceil", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("floor", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("trunc", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("round", {ts.FLOAT64_TYPE, ts.INT_TYPE}, ts.FLOAT64_TYPE);
    
    // Other math functions
    checker.register_builtin_function("fmod", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("remainder", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("fmax", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("fmin", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("fdim", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("hypot", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // String functions
    checker.register_builtin_function("concat", {ts.STRING_TYPE, ts.STRING_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("length", {ts.STRING_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("substring", {ts.STRING_TYPE, ts.INT_TYPE, ts.INT_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("str_format", {ts.STRING_TYPE, ts.ANY_TYPE}, ts.STRING_TYPE);
    
    // Utility functions
    checker.register_builtin_function("typeof", {ts.ANY_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("clock", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("sleep", {ts.FLOAT64_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("len", {ts.ANY_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("time", {}, ts.INT64_TYPE);
    checker.register_builtin_function("date", {}, ts.STRING_TYPE);
    checker.register_builtin_function("now", {}, ts.STRING_TYPE);
    checker.register_builtin_function("assert", {ts.BOOL_TYPE, ts.STRING_TYPE}, ts.NIL_TYPE);
    
    // Math constants (as functions)
    checker.register_builtin_function("pi", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("e", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("ln2", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("ln10", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("sqrt2", {}, ts.FLOAT64_TYPE);
    
    // Collection functions (simplified for now)
    auto function_type = ts.createFunctionType({}, ts.ANY_TYPE); // Simple function type
    checker.register_builtin_function("map", {function_type, ts.LIST_TYPE}, ts.LIST_TYPE);
    checker.register_builtin_function("filter", {function_type, ts.LIST_TYPE}, ts.LIST_TYPE);
    checker.register_builtin_function("reduce", {function_type, ts.LIST_TYPE, ts.ANY_TYPE}, ts.ANY_TYPE);
    checker.register_builtin_function("forEach", {function_type, ts.LIST_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("find", {function_type, ts.LIST_TYPE}, ts.ANY_TYPE);
    checker.register_builtin_function("some", {function_type, ts.LIST_TYPE}, ts.BOOL_TYPE);
    checker.register_builtin_function("every", {function_type, ts.LIST_TYPE}, ts.BOOL_TYPE);
    
    // Function composition
    checker.register_builtin_function("compose", {function_type, function_type}, function_type);
    checker.register_builtin_function("curry", {function_type}, function_type);
    checker.register_builtin_function("partial", {function_type, ts.ANY_TYPE}, function_type);
    
    // Channel function
    checker.register_builtin_function("channel", {}, ts.INT_TYPE);
}

} // namespace TypeCheckerFactory
