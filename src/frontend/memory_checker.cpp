#include "memory_checker.hh"
#include "../error/debugger.hh"
#include <sstream>
#include <algorithm>

namespace LM {
namespace Frontend {
using namespace LM::Error;

// =============================================================================
// MAIN MEMORY CHECKING ENTRY POINT
// =============================================================================

MemoryCheckResult MemoryChecker::check_program(std::shared_ptr<LM::Frontend::AST::Program> program, 
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
    variable_generation_info.clear();
    reference_chain.clear();
    generation_history.clear();
    current_region_id = 0;
    current_generation = 0;
    current_scope_depth = 0;
    region_stack.clear();
    generation_stack_history.clear();
    
    // Don't reset Debugger error state to avoid clearing type checker errors
    
    // Enter initial memory region
    enter_memory_region();
    
    // Mark imported symbols and function declarations as initialized
    for (const auto& [name, stmt] : program->imported_symbols) { 
        initialized_variables.insert(name); 
    }
    for (auto& stmt : program->statements) {
        if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) { 
            initialized_variables.insert(func->name); 
        }
    }
    
    // Check all statements for memory safety
    for (auto& stmt : program->statements) {
        check_statement(stmt);
        // Only attach memory_info to statements that represent actual region boundaries
        // Block statements, function declarations, etc.
        if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
            insert_memory_operations(stmt);
        } else if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
            insert_memory_operations(stmt);
        }
        // TODO: Add other statement types that represent region boundaries
    }
    
    // Exit initial region
    exit_memory_region();
    
    // Create result
    MemoryCheckResult result;
    result.success = !Debugger::hasError();
    result.program = program;
    result.errors = errors;
    result.warnings = warnings;
    
    return result;
}

// =============================================================================
// STATEMENT CHECKING
// =============================================================================

void MemoryChecker::check_statement(std::shared_ptr<LM::Frontend::AST::Statement> stmt) {
    if (!stmt) return;
    
    if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
        check_var_declaration(var_decl);
    } else if (auto assignment = std::dynamic_pointer_cast<LM::Frontend::AST::AssignExpr>(stmt)) {
        check_assignment(assignment);
    } else if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
        check_block_statement(block);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt)) {
        check_expression(expr_stmt->expression);
    } else if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
        check_expression(if_stmt->condition);
        check_statement(if_stmt->thenBranch);
        if (if_stmt->elseBranch) {
            check_statement(if_stmt->elseBranch);
        }
    } else if (auto while_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WhileStatement>(stmt)) {
        check_expression(while_stmt->condition);
        check_statement(while_stmt->body);
    } else if (auto for_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ForStatement>(stmt)) {
        if (for_stmt->initializer) check_statement(for_stmt->initializer);
        if (for_stmt->condition) check_expression(for_stmt->condition);
        if (for_stmt->increment) check_expression(for_stmt->increment);
        check_statement(for_stmt->body);
        
        // For loop variables are handled in the initializer statement
        // which should be a variable declaration that check_statement will process
    } else if (auto return_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
        // Handle return statement - ownership transfer from callee to caller
        if (return_stmt->value) {
            check_expression(return_stmt->value);
            
            // If returning a variable, mark it as escaped
            // The ownership transfers to the caller, so the callee's region cannot reclaim it
            if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(return_stmt->value)) {
                mark_variable_escaped(var_expr->name);
            }
        }
    } else if (auto iter_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IterStatement>(stmt)) {
        // Handle iter statement - check the iterable and body
        check_expression(iter_stmt->iterable);
        
        // Mark loop variables as initialized (they are implicitly initialized by the loop)
        for (const auto& loop_var : iter_stmt->loopVars) {
            mark_variable_initialized(loop_var);
            
            // Create generation info for loop variable if it doesn't exist
            if (variable_generation_info.find(loop_var) == variable_generation_info.end()) {
                GenerationInfo gen_info;
                gen_info.region_id = current_region_id;
                gen_info.generation = current_generation;
                gen_info.is_linear = false;  // Loop variables are typically not linear
                gen_info.ownership_state = OwnershipState::Valid;
                gen_info.scope_depth = current_scope_depth;
                variable_generation_info[loop_var] = gen_info;
                variable_regions[loop_var] = current_region_id;
                variable_generations[loop_var] = current_generation;
            } else {
                variable_generation_info[loop_var].ownership_state = OwnershipState::Valid;
            }
        }
        
        check_statement(iter_stmt->body);
    }
}

void MemoryChecker::check_var_declaration(std::shared_ptr<LM::Frontend::AST::VarDeclaration> var_decl) {
    if (!var_decl) return;
    
    // Check if variable has a type (should be set by type checker)
    if (!var_decl->inferred_type) {
        add_error("Variable '" + var_decl->name + "' has no inferred type - type checker must run first", 
                 var_decl->line);
        return;
    }
    
    // Check if it's a linear type
    bool is_linear = (var_decl->inferred_type->tag == TypeTag::List ||
                      var_decl->inferred_type->tag == TypeTag::Dict ||
                      var_decl->inferred_type->tag == TypeTag::Frame);
    
    // Create generation info for this variable
    GenerationInfo gen_info;
    gen_info.region_id = current_region_id;
    gen_info.generation = current_generation;
    gen_info.is_linear = is_linear;
    gen_info.ownership_state = OwnershipState::Uninitialized;
    gen_info.scope_depth = current_scope_depth;
    
    variable_generation_info[var_decl->name] = gen_info;
    variable_regions[var_decl->name] = current_region_id;
    variable_generations[var_decl->name] = current_generation;
    
    // Track generation history
    if (generation_history.find(var_decl->name) == generation_history.end()) {
        generation_history[var_decl->name] = {};
    }
    generation_history[var_decl->name].push_back(current_generation);
    
    // Check initializer
    if (var_decl->initializer) {
        check_expression(var_decl->initializer);
        mark_variable_initialized(var_decl->name);
        variable_generation_info[var_decl->name].ownership_state = OwnershipState::Valid;
        
        // Check if initializing from another variable
        // For Limit, we use COPY semantics by default, not MOVE semantics
        // The source variable remains valid unless this is an explicit move operation
        if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(var_decl->initializer)) {
            if (is_variable_moved(var_expr->name)) {
                add_memory_error("Use-after-move", var_expr->name,
                               "Variable '" + var_expr->name + "' used after being moved",
                               var_expr->line);
            }
            // NOTE: We do NOT mark source as moved here
            // In Limit, assignment is COPY by default, not MOVE
            // Only explicit move operations should transfer ownership
        }
    } else {
        // Variable declared without initializer remains uninitialized
        variable_generation_info[var_decl->name].ownership_state = OwnershipState::Uninitialized;
    }
}

void MemoryChecker::check_assignment(std::shared_ptr<LM::Frontend::AST::AssignExpr> assignment) {
    if (!assignment) return;
    
    // Check the value being assigned
    check_expression(assignment->value);
    
    // Check if assigning from a moved variable
    if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(assignment->value)) {
        if (is_variable_moved(var_expr->name)) {
            add_memory_error("Use-after-move", var_expr->name,
                           "Variable '" + var_expr->name + "' used after being moved",
                           var_expr->line);
        }
        // NOTE: We do NOT mark source as moved here
        // In Limit, assignment is COPY by default for primitive types
        // For linear types, we need explicit move semantics
        // This is a mutation/rebinding operation, not ownership transfer
    }
    
    // Mark target variable as initialized and update its state
    mark_variable_initialized(assignment->name);
    if (variable_generation_info.find(assignment->name) != variable_generation_info.end()) {
        variable_generation_info[assignment->name].ownership_state = OwnershipState::Valid;
    }
}

void MemoryChecker::check_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (!expr) return;
    
    if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
        check_variable_access(var_expr);
    } else if (auto call_expr = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        check_function_call(call_expr);
    } else if (auto binary_expr = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        check_expression(binary_expr->left);
        check_expression(binary_expr->right);
    } else if (auto unary_expr = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
        check_expression(unary_expr->right);
    } else if (auto group_expr = std::dynamic_pointer_cast<LM::Frontend::AST::GroupingExpr>(expr)) {
        check_expression(group_expr->expression);
    }
}

void MemoryChecker::check_variable_access(std::shared_ptr<LM::Frontend::AST::VariableExpr> var_expr) {
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
    
    // Check ownership state
    auto gen_iter = variable_generation_info.find(name);
    if (gen_iter != variable_generation_info.end()) {
        const GenerationInfo& gen_info = gen_iter->second;
        
        // Only check generation lifetime for references or escaped values
        // Ordinary variable reads should NOT advance generation or cause generation mismatches
        if (gen_info.ownership_state == OwnershipState::Escaped) {
            check_reference_lifetime(name, gen_info.generation, current_generation);
        }
        
        // Prevent access to invalid states
        if (gen_info.ownership_state == OwnershipState::Invalid ||
            gen_info.ownership_state == OwnershipState::Consumed) {
            add_memory_error("Invalid access", name,
                            "Variable '" + name + "' is in invalid state",
                            var_expr->line);
        }
    }
    
    // NOTE: We do NOT advance generation on ordinary reads
    // Generation transition only occurs on actual ownership changes (move, escape, etc.)
}

void MemoryChecker::check_function_call(std::shared_ptr<LM::Frontend::AST::CallExpr> call) {
    if (!call) return;
    
    // Check all arguments
    for (auto& arg : call->arguments) {
        check_expression(arg);
        
        // If argument is a variable, check for moved state
        // But do NOT automatically mark as moved - this depends on function semantics
        if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(arg)) {
            if (is_variable_moved(var_expr->name)) {
                add_memory_error("Use-after-move", var_expr->name,
                               "Variable '" + var_expr->name + "' used after being moved",
                               var_expr->line);
            }
            // NOTE: We do NOT mark the variable as moved here
            // Function calls may borrow, copy, or consume based on signature
            // This requires analysis of function parameter ownership semantics
            // For now, we conservatively assume parameters are borrowed (not moved)
            // unless the function is explicitly marked as consuming/linear
        }
    }
}

void MemoryChecker::check_block_statement(std::shared_ptr<LM::Frontend::AST::BlockStatement> block) {
    if (!block) return;
    
    // Enter new scope
    enter_scope();
    
    // Save current variable state to track which variables are newly created
    auto saved_moved = moved_variables;
    auto saved_initialized = initialized_variables;
    auto saved_gen_info = variable_generation_info;
    
    // Track which variables are newly created in this scope
    std::unordered_set<std::string> new_variables;
    
    // Check all statements in block
    for (auto& stmt : block->statements) {
        check_statement(stmt);
        
        // Track variable declarations in this scope
        if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
            new_variables.insert(var_decl->name);
        }
    }
    
    // Invalidate scope references
    invalidate_scope_references();
    
    // Exit scope
    exit_scope();
    
    // Restore outer scope state for existing variables, but keep new variables removed
    moved_variables = saved_moved;
    initialized_variables = saved_initialized;
    
    // Only restore generation info for variables that existed before this scope
    for (const auto& [name, info] : saved_gen_info) {
        if (new_variables.find(name) == new_variables.end()) {
            variable_generation_info[name] = info;
        } else {
            // Remove generation info for variables that were created in this scope
            variable_generation_info.erase(name);
        }
    }
}

// =============================================================================
// MEMORY OPERATIONS
// =============================================================================

// The memory checker attaches memory_info to AST nodes for the LIR generator to use
// This provides a unified region management system instead of independent systems

void MemoryChecker::insert_memory_operations(std::shared_ptr<LM::Frontend::AST::Statement> stmt) {
    if (stmt) {
        stmt->memory_info = LM::Frontend::AST::MemoryInfo(current_region_id, current_generation);
    }
}

void MemoryChecker::insert_make_linear(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (expr) {
        expr->memory_info = LM::Frontend::AST::MemoryInfo(current_region_id, current_generation, true);
    }
}

void MemoryChecker::insert_make_ref(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (expr) {
        auto info = LM::Frontend::AST::MemoryInfo(current_region_id, current_generation);
        info.is_reference = true;
        expr->memory_info = info;
    }
}

void MemoryChecker::insert_move(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (expr) {
        auto info = LM::Frontend::AST::MemoryInfo(current_region_id, current_generation);
        info.is_moved = true;
        expr->memory_info = info;
    }
}

void MemoryChecker::insert_drop(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (expr) {
        auto info = LM::Frontend::AST::MemoryInfo(current_region_id, current_generation);
        info.needs_drop = true;
        expr->memory_info = info;
    }
}

// =============================================================================
// VARIABLE TRACKING
// =============================================================================

void MemoryChecker::mark_variable_initialized(const std::string& name) {
    initialized_variables.insert(name);
}

void MemoryChecker::mark_variable_moved(const std::string& name) {
    moved_variables.insert(name);
    if (variable_generation_info.find(name) != variable_generation_info.end()) {
        variable_generation_info[name].ownership_state = OwnershipState::Moved;
        // Only advance generation on actual move
        track_generation_transition(name, current_generation, current_generation + 1);
        current_generation++;
    }
}

void MemoryChecker::mark_variable_copied(const std::string& name) {
    // Copy does not change ownership state
    // Source remains valid
    // No generation transition
}

void MemoryChecker::mark_variable_borrowed(const std::string& name, bool is_mutable) {
    if (variable_generation_info.find(name) != variable_generation_info.end()) {
        variable_generation_info[name].ownership_state = is_mutable ? 
            OwnershipState::MutablyBorrowed : OwnershipState::Borrowed;
    }
}

void MemoryChecker::mark_variable_escaped(const std::string& name) {
    if (variable_generation_info.find(name) != variable_generation_info.end()) {
        variable_generation_info[name].ownership_state = OwnershipState::Escaped;
        // Generation transition on escape
        track_generation_transition(name, current_generation, current_generation + 1);
        current_generation++;
    }
}

void MemoryChecker::mark_variable_consumed(const std::string& name) {
    moved_variables.insert(name);
    if (variable_generation_info.find(name) != variable_generation_info.end()) {
        variable_generation_info[name].ownership_state = OwnershipState::Consumed;
        track_generation_transition(name, current_generation, current_generation + 1);
        current_generation++;
    }
}

bool MemoryChecker::is_variable_initialized(const std::string& name) const {
    return initialized_variables.find(name) != initialized_variables.end();
}

bool MemoryChecker::is_variable_moved(const std::string& name) const {
    return moved_variables.find(name) != moved_variables.end();
}

OwnershipState MemoryChecker::get_ownership_state(const std::string& name) const {
    auto iter = variable_generation_info.find(name);
    if (iter != variable_generation_info.end()) {
        return iter->second.ownership_state;
    }
    return OwnershipState::Uninitialized;
}

// =============================================================================
// GENERATIONAL REFERENCE TRACKING
// =============================================================================

std::shared_ptr<GenerationalRef> MemoryChecker::create_reference(const std::string& var_name, bool is_mutable) {
    auto ref = std::make_shared<GenerationalRef>(
        var_name + "_ref_" + std::to_string(current_generation),
        current_generation,
        current_region_id,
        current_scope_depth,
        is_mutable
    );
    
    // Track reference in generation stack
    if (generation_stack.empty()) {
        generation_stack.push_back({});
    }
    generation_stack.back().push_back(ref);
    
    // Track reference chain
    reference_chain[var_name].push_back(ref);
    
    return ref;
}

void MemoryChecker::invalidate_generation(int generation) {
    // Invalidate all references from this generation
    for (auto& [var_name, refs] : reference_chain) {
        for (auto& ref : refs) {
            if (ref->created_generation == generation) {
                ref->is_valid = false;
            }
        }
    }
}

void MemoryChecker::invalidate_references_at_scope(int scope_depth) {
    // Invalidate all references created at or within this scope
    for (auto& [var_name, refs] : reference_chain) {
        for (auto& ref : refs) {
            if (ref->created_scope >= scope_depth) {
                ref->is_valid = false;
            }
        }
    }
}

bool MemoryChecker::is_reference_valid(const std::shared_ptr<GenerationalRef>& ref) const {
    if (!ref) return false;
    return ref->is_valid && ref->created_generation == current_generation;
}

void MemoryChecker::check_reference_lifetime(const std::string& var_name, int ref_generation, int current_gen) {
    // Only flag stale references if there was an actual ownership transition
    // Generation mismatch alone is not an error - it must correspond to a move/escape
    auto gen_iter = variable_generation_info.find(var_name);
    if (gen_iter != variable_generation_info.end()) {
        const GenerationInfo& gen_info = gen_iter->second;
        // Only report error if the variable's ownership state actually changed
        if (ref_generation < current_gen && 
            (gen_info.ownership_state == OwnershipState::Moved ||
             gen_info.ownership_state == OwnershipState::Escaped ||
             gen_info.ownership_state == OwnershipState::Consumed)) {
            add_error("Reference to variable '" + var_name + "' is stale (generation mismatch)", 0);
        }
    }
}

void MemoryChecker::check_mutable_aliasing(const std::string& var_name, bool is_mutable) {
    if (!is_mutable) return;
    
    auto iter = reference_chain.find(var_name);
    if (iter != reference_chain.end()) {
        int mutable_count = 0;
        for (const auto& ref : iter->second) {
            if (ref->is_mutable && ref->is_valid) {
                mutable_count++;
            }
        }
        
        if (mutable_count > 1) {
            add_error("Multiple mutable references to '" + var_name + "' violate aliasing rules", 0);
        }
    }
}

void MemoryChecker::track_generation_transition(const std::string& var_name, int old_gen, int new_gen) {
    invalidate_generation(old_gen);
    
    if (generation_history.find(var_name) == generation_history.end()) {
        generation_history[var_name] = {};
    }
    generation_history[var_name].push_back(new_gen);
}

// =============================================================================
// SCOPE MANAGEMENT
// =============================================================================

void MemoryChecker::enter_scope() {
    current_scope_depth++;
    enter_memory_region();
    generation_stack.push_back({});
}

void MemoryChecker::exit_scope() {
    invalidate_scope_references();
    exit_memory_region();
    
    if (!generation_stack.empty()) {
        generation_stack.pop_back();
    }
    
    current_scope_depth--;
}

void MemoryChecker::invalidate_scope_references() {
    invalidate_references_at_scope(current_scope_depth);
}

// =============================================================================
// MEMORY REGION MANAGEMENT
// =============================================================================

void MemoryChecker::enter_memory_region() {
    region_stack.push_back(current_region_id);
    generation_stack_history.push_back(current_generation);
    current_region_id++;
    current_generation++;
}

void MemoryChecker::exit_memory_region() {
    if (!region_stack.empty()) {
        region_stack.pop_back();
    }
    if (!generation_stack_history.empty()) {
        generation_stack_history.pop_back();
    }
}

// =============================================================================
// ERROR REPORTING
// =============================================================================

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
    
    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, current_source, current_file_path, hint, "");
    } else {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, "", "", hint, "");
    }
}

void MemoryChecker::add_error(const std::string& message, int line) {
    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, current_source, current_file_path, "", "");
    } else {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, "", "", "", "");
    }
}

void MemoryChecker::add_warning(const std::string& message, int line) {
    std::ostringstream oss;
    oss << "Warning: " << message;
    if (line > 0) {
        oss << " (line " << line << ")";
    }
    warnings.push_back(oss.str());
}

// =============================================================================
// DIAGNOSTIC METHODS
// =============================================================================

std::string MemoryChecker::get_generation_info(const std::string& var_name) const {
    std::ostringstream oss;
    
    auto iter = variable_generation_info.find(var_name);
    if (iter != variable_generation_info.end()) {
        const GenerationInfo& info = iter->second;
        oss << "Variable: " << var_name << "\n";
        oss << "  Region: " << info.region_id << "\n";
        oss << "  Generation: " << info.generation << "\n";
        oss << "  Is Linear: " << (info.is_linear ? "yes" : "no") << "\n";
        oss << "  Ownership State: ";
        switch (info.ownership_state) {
            case OwnershipState::Uninitialized: oss << "Uninitialized"; break;
            case OwnershipState::Valid: oss << "Valid"; break;
            case OwnershipState::Moved: oss << "Moved"; break;
            case OwnershipState::Borrowed: oss << "Borrowed"; break;
            case OwnershipState::MutablyBorrowed: oss << "MutablyBorrowed"; break;
            case OwnershipState::Escaped: oss << "Escaped"; break;
            case OwnershipState::Consumed: oss << "Consumed"; break;
            case OwnershipState::Invalid: oss << "Invalid"; break;
        }
        oss << "\n";
        oss << "  Scope Depth: " << info.scope_depth << "\n";
        
        auto hist_iter = generation_history.find(var_name);
        if (hist_iter != generation_history.end()) {
            oss << "  Generation History: ";
            for (int gen : hist_iter->second) {
                oss << gen << " ";
            }
            oss << "\n";
        }
    }
    
    return oss.str();
}

std::string MemoryChecker::get_reference_info(const std::string& var_name) const {
    std::ostringstream oss;
    
    auto iter = reference_chain.find(var_name);
    if (iter != reference_chain.end()) {
        oss << "References to '" << var_name << "':\n";
        for (const auto& ref : iter->second) {
            oss << "  Ref ID: " << ref->ref_id << "\n";
            oss << "    Created Generation: " << ref->created_generation << "\n";
            oss << "    Created Region: " << ref->created_region << "\n";
            oss << "    Created Scope: " << ref->created_scope << "\n";
            oss << "    Is Mutable: " << (ref->is_mutable ? "yes" : "no") << "\n";
            oss << "    Is Valid: " << (ref->is_valid ? "yes" : "no") << "\n";
        }
    }
    
    return oss.str();
}

void MemoryChecker::dump_memory_state() const {
    std::cout << "=== MEMORY CHECKER STATE ===\n";
    std::cout << "Current Region ID: " << current_region_id << "\n";
    std::cout << "Current Generation: " << current_generation << "\n";
    std::cout << "Current Scope Depth: " << current_scope_depth << "\n";
    std::cout << "\nVariable Generation Info:\n";
    for (const auto& [name, info] : variable_generation_info) {
        std::cout << get_generation_info(name);
    }
    std::cout << "\nReference Chains:\n";
    for (const auto& [name, refs] : reference_chain) {
        std::cout << get_reference_info(name);
    }
}

// =============================================================================
// FACTORY IMPLEMENTATION
// =============================================================================

MemoryCheckResult MemoryCheckerFactory::check_program(std::shared_ptr<LM::Frontend::AST::Program> program, 
                                                      const std::string& source, 
                                                      const std::string& filename) {
    MemoryChecker checker;
    return checker.check_program(program, source, filename);
}

} // namespace Frontend
} // namespace LM
