#include "memory_checker.hh"
#include "../common/debugger.hh"
#include <sstream>

// =============================================================================
// MEMORY CHECKER IMPLEMENTATION
// =============================================================================

MemoryCheckResult MemoryChecker::check_program(std::shared_ptr<AST::Program> program, 
                                               const std::string& source, 
                                               const std::string& filename) {
    if (!program) {
        MemoryCheckResult result;
        result.success = false;
        result.program = nullptr;
        result.errors.push_back("Null program provided to memory checker");
        return result;
    }
    
    // Initialize state
    current_source = source;
    current_file_path = filename;
    errors.clear();
    warnings.clear();
    variable_regions.clear();
    moved_variables.clear();
    initialized_variables.clear();
    variable_generations.clear();
    current_region_id = 0;
    current_generation = 0;
    
    // Don't reset Debugger error state to avoid clearing type checker errors
    
    // Enter initial memory region
    enter_memory_region();
    
    // Check all statements for memory safety
    for (auto& stmt : program->statements) {
        check_statement(stmt);
        insert_memory_operations(stmt);
    }
    
    // Check for memory leaks at program end
    // (Disabled for now - only complex types would need explicit cleanup)
    // for (const auto& [var_name, region_id] : variable_regions) {
    //     if (!is_variable_moved(var_name)) {
    //         add_warning("Variable '" + var_name + "' goes out of scope without explicit cleanup", 0);
    //     }
    // }
    
    // Create result
    MemoryCheckResult result;
    result.success = !Debugger::hasError(); // Check global error state like type checker
    result.program = program;
    result.errors = errors; // Keep local errors for compatibility
    result.warnings = warnings;
    
    return result;
}

void MemoryChecker::check_statement(std::shared_ptr<AST::Statement> stmt) {
    if (!stmt) return;
    
    if (auto var_decl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        check_var_declaration(var_decl);
    } else if (auto assignment = std::dynamic_pointer_cast<AST::AssignExpr>(stmt)) {
        check_assignment(assignment);
    } else if (auto block = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        check_block_statement(block);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        check_expression(expr_stmt->expression);
    } else if (auto if_stmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        check_expression(if_stmt->condition);
        check_statement(if_stmt->thenBranch);
        if (if_stmt->elseBranch) {
            check_statement(if_stmt->elseBranch);
        }
    } else if (auto while_stmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        check_expression(while_stmt->condition);
        check_statement(while_stmt->body);
    } else if (auto for_stmt = std::dynamic_pointer_cast<AST::ForStatement>(stmt)) {
        if (for_stmt->initializer) check_statement(for_stmt->initializer);
        if (for_stmt->condition) check_expression(for_stmt->condition);
        if (for_stmt->increment) check_expression(for_stmt->increment);
        check_statement(for_stmt->body);
    }
}

void MemoryChecker::check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl) {
    if (!var_decl) return;
    
    // Check if variable has a type (should be set by type checker)
    if (!var_decl->inferred_type) {
        add_error("Variable '" + var_decl->name + "' has no inferred type - type checker must run first", 
                 var_decl->line);
        return;
    }
    
    // Create memory tracking for the variable
    variable_regions[var_decl->name] = current_region_id;
    variable_generations[var_decl->name] = current_generation;
    
    // Check initializer
    if (var_decl->initializer) {
        check_expression(var_decl->initializer);
        mark_variable_initialized(var_decl->name);
        
        // Check if initializing from another variable (potential move)
        if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(var_decl->initializer)) {
            if (is_variable_moved(var_expr->name)) {
                add_memory_error("Use-after-move", var_expr->name,
                               "Variable '" + var_expr->name + "' used after being moved",
                               var_expr->line);
            } else {
                // Mark source variable as moved (for linear types)
                mark_variable_moved(var_expr->name);
            }
        }
    }
}

void MemoryChecker::check_assignment(std::shared_ptr<AST::AssignExpr> assignment) {
    if (!assignment) return;
    
    // Check the value being assigned
    check_expression(assignment->value);
    
    // Check if assigning from a moved variable
    if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(assignment->value)) {
        if (is_variable_moved(var_expr->name)) {
            add_memory_error("Use-after-move", var_expr->name,
                           "Variable '" + var_expr->name + "' used after being moved",
                           var_expr->line);
        } else {
            // Mark source variable as moved (for linear types)
            mark_variable_moved(var_expr->name);
        }
    }
    
    // Mark target variable as initialized
    mark_variable_initialized(assignment->name);
}

void MemoryChecker::check_expression(std::shared_ptr<AST::Expression> expr) {
    if (!expr) return;
    
    if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        check_variable_access(var_expr);
    } else if (auto call_expr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        check_function_call(call_expr);
    } else if (auto binary_expr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        check_expression(binary_expr->left);
        check_expression(binary_expr->right);
    } else if (auto unary_expr = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        check_expression(unary_expr->right);
    } else if (auto group_expr = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        check_expression(group_expr->expression);
    }
}

void MemoryChecker::check_variable_access(std::shared_ptr<AST::VariableExpr> var_expr) {
    if (!var_expr) return;
    
    const std::string& name = var_expr->name;
    
    // Check if variable was moved
    if (is_variable_moved(name)) {
        add_memory_error("Use-after-move", name,
                        "Variable '" + name + "' used after being moved",
                        var_expr->line);
        return;
    }
    
    // Check if variable is initialized
    if (!is_variable_initialized(name)) {
        add_memory_error("Use-before-init", name,
                        "Variable '" + name + "' used before initialization",
                        var_expr->line);
        return;
    }
}

void MemoryChecker::check_function_call(std::shared_ptr<AST::CallExpr> call) {
    if (!call) return;
    
    // Check all arguments
    for (auto& arg : call->arguments) {
        check_expression(arg);
        
        // If argument is a variable, it might be moved into the function
        if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(arg)) {
            if (is_variable_moved(var_expr->name)) {
                add_memory_error("Use-after-move", var_expr->name,
                               "Variable '" + var_expr->name + "' used after being moved",
                               var_expr->line);
            }
            // For now, don't automatically move function arguments
            // This would require function signature analysis
        }
    }
}

void MemoryChecker::check_block_statement(std::shared_ptr<AST::BlockStatement> block) {
    if (!block) return;
    
    // Enter new memory region for block
    enter_memory_region();
    
    // Save current variable state
    auto saved_moved = moved_variables;
    auto saved_initialized = initialized_variables;
    
    // Check all statements in block
    for (auto& stmt : block->statements) {
        check_statement(stmt);
    }
    
    // Restore variable state (variables declared in block go out of scope)
    moved_variables = saved_moved;
    initialized_variables = saved_initialized;
    
    // Exit memory region
    exit_memory_region();
}

void MemoryChecker::insert_memory_operations(std::shared_ptr<AST::Statement> stmt) {
    // This would insert memory operation nodes into the AST
    // For now, we just set memory info on the statement
    if (stmt) {
        stmt->memory_info = AST::MemoryInfo(current_region_id, current_generation);
    }
}

void MemoryChecker::insert_make_linear(std::shared_ptr<AST::Expression> expr) {
    // Insert MakeLinearExpr node - for now just set memory info
    if (expr) {
        expr->memory_info = AST::MemoryInfo(current_region_id, current_generation);
    }
}

void MemoryChecker::insert_make_ref(std::shared_ptr<AST::Expression> expr) {
    // Insert MakeRefExpr node - for now just set memory info
    if (expr) {
        expr->memory_info = AST::MemoryInfo(current_region_id, current_generation);
    }
}

void MemoryChecker::insert_move(std::shared_ptr<AST::Expression> expr) {
    // Insert MoveExpr node - for now just set memory info
    if (expr) {
        expr->memory_info = AST::MemoryInfo(current_region_id, current_generation);
    }
}

void MemoryChecker::insert_drop(std::shared_ptr<AST::Expression> expr) {
    // Insert DropExpr node - for now just set memory info
    if (expr) {
        expr->memory_info = AST::MemoryInfo(current_region_id, current_generation);
    }
}

void MemoryChecker::mark_variable_initialized(const std::string& name) {
    initialized_variables.insert(name);
}

void MemoryChecker::mark_variable_moved(const std::string& name) {
    moved_variables.insert(name);
}

bool MemoryChecker::is_variable_initialized(const std::string& name) const {
    return initialized_variables.find(name) != initialized_variables.end();
}

bool MemoryChecker::is_variable_moved(const std::string& name) const {
    return moved_variables.find(name) != moved_variables.end();
}

void MemoryChecker::enter_memory_region() {
    current_region_id++;
    current_generation++;
}

void MemoryChecker::exit_memory_region() {
    // Clean up variables from this region
    // For now, just increment generation
    current_generation++;
}

void MemoryChecker::add_memory_error(const std::string& error_type, const std::string& variable_name, 
                                    const std::string& description, int line) {
    std::string message = error_type + ": " + description;
    std::string hint;
    
    if (error_type == "Use-after-move") {
        hint = "Memory Model: Linear types can only be used once. After a move, the original variable becomes invalid. "
               "Type Checking: Use references (&var) for borrowing instead of moving, or clone the value if copying is needed.";
    } else if (error_type == "Use-after-free") {
        hint = "Memory Model: Accessing freed memory is undefined behavior. "
               "Type Checking: Linear types and region-based allocation prevent use-after-free at compile-time.";
    } else if (error_type == "Use-before-init") {
        hint = "Memory Model: Variables must be initialized before use. "
               "Type Checking: The compiler tracks initialization state to prevent undefined behavior.";
    } else if (error_type == "Double move") {
        hint = "Memory Model: Linear types have single ownership - they can only be moved once. "
               "Type Checking: The compiler tracks ownership to prevent double moves.";
    } else if (error_type == "Memory leak") {
        hint = "Memory Model: All allocated memory must be freed before going out of scope. "
               "Type Checking: Use linear types with automatic cleanup or explicit drop operations.";
    } else {
        hint = "Memory Model: Use linear types and region-based allocation for memory safety. "
               "Type Checking: Compile-time analysis prevents memory safety violations.";
    }
    
    // Use the same error reporting system as type checker but with MEMORY stage
    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, current_source, current_file_path, hint, "");
    } else {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, "", "", hint, "");
    }
}

void MemoryChecker::add_error(const std::string& message, int line) {
    // Use same error system as type checker but with MEMORY stage
    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, current_source, current_file_path, "", "");
    } else {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, "", "", "", "");
    }
}

void MemoryChecker::add_warning(const std::string& message, int line) {
    // For warnings, we can use a different approach or just add to warnings list
    std::ostringstream oss;
    oss << "Warning: " << message;
    if (line > 0) {
        oss << " (line " << line << ")";
    }
    warnings.push_back(oss.str());
}

// =============================================================================
// FACTORY IMPLEMENTATION
// =============================================================================

MemoryCheckResult MemoryCheckerFactory::check_program(std::shared_ptr<AST::Program> program, 
                                                      const std::string& source, 
                                                      const std::string& filename) {
    MemoryChecker checker;
    return checker.check_program(program, source, filename);
}