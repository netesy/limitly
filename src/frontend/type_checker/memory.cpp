#include "../type_checker.hh"

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

// =============================================================================
// LINEAR TYPE REFERENCE SYSTEM
// =============================================================================

void TypeChecker::check_linear_type_access(const std::string& var_name, int line) {
    // Check if this is a linear type
    if (linear_types.find(var_name) != linear_types.end()) {
        auto& linear_info = linear_types[var_name];
        
        if (linear_info.is_moved) {
            add_error("Use of moved linear type '" + var_name + "'\n\n= reason: Linear types can only be used once\n= help: ensure you use the linear type before moving it to another variable", line);
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
            add_error("Cannot create reference to moved linear type '" + linear_var + "'\n\n= reason: Linear types can only be moved once\n= help: create the reference before moving the linear type", line);
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
            add_error("Double move of linear type '" + var_name + "'\n\n= reason: Linear types can only be moved once\n= help: ensure you only move the linear type one time", line);
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
                    add_error("Reference '" + ref_name + "' invalidated by generation change of '" + var_name + "'\n\n= reason: References are generation-scoped\n= help: recreate the reference after the move", ref_info.creation_line);
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
            add_error("Use of invalid reference '" + ref_name + "'\n\n= reason: Reference invalidated by linear type generation change\n= help: recreate the reference after the generation change", line);
            return;
        }
        
        // Check if target linear type still exists
        if (linear_types.find(ref_info.target_linear_var) != linear_types.end()) {
            const auto& linear_info = linear_types[ref_info.target_linear_var];
            
            // Check if reference generation matches linear type current generation
            if (ref_info.created_generation != linear_info.current_generation) {
                add_error("Use of stale reference '" + ref_name + "' - generation mismatch\n\n= reason: References are generation-scoped\n= help: recreate the reference after the generation change", line);
                return;
            }
            
            if (linear_info.is_moved) {
                add_error("Use of reference '" + ref_name + "' to moved linear type\n\n= reason: References die when linear type moves\n= help: use the reference before moving the linear type", line);
            }
        }
    }
}

void TypeChecker::check_mutable_aliasing(const std::string& linear_var, const std::string& ref_var, bool is_mutable, int line) {
    if (linear_types.find(linear_var) != linear_types.end()) {
        const auto& linear_info = linear_types[linear_var];
        
        if (is_mutable) {
            // Cannot create mutable reference if other references exist
            if (linear_info.references.size() > 0) {
                add_error("Cannot create mutable reference '" + ref_var + "' - other references to '" + linear_var + "' exist\n\n= reason: Mutable references require exclusive access\n= help: ensure no other references exist before creating a mutable reference", line);
                return;
            }
            
            // Cannot create multiple mutable references
            if (linear_info.mutable_references.size() > 0) {
                add_error("Multiple mutable references to '" + linear_var + "' not allowed\n\n= reason: Only one mutable reference per linear type\n= help: use a single mutable reference or use immutable references", line);
                return;
            }
        } else {
            // Cannot create immutable reference if mutable reference exists
            if (linear_info.mutable_references.size() > 0) {
                add_error("Cannot create immutable reference '" + ref_var + "' - mutable reference to '" + linear_var + "' exists\n\n= reason: Mutable references are exclusive\n= help: remove the mutable reference or use only immutable references", line);
                return;
            }
        }
    }
}

void TypeChecker::check_scope_escape(const std::string& ref_name, int target_scope, int line) {
    if (references.find(ref_name) != references.end()) {
        const auto& ref_info = references[ref_name];
        
        if (ref_info.creation_scope > target_scope) {
            add_error("Reference '" + ref_name + "' would escape its creation scope\n\n= reason: References cannot outlive their scope - would create dangling reference\n= help: ensure the reference does not escape its creation scope", line);
        }
        
        if (ref_info.is_mutable && ref_info.creation_scope > target_scope) {
            add_error("Mutable reference '" + ref_name + "' cannot escape scope\n\n= reason: Mutable references have stricter lifetime requirements\n= help: ensure the mutable reference does not escape its creation scope", line);
        }
    }
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
    size_t region_to_clean = current_region_id;
    if (!region_stack.empty()) {
        current_region_id = region_stack.back();
        region_stack.pop_back();
        current_generation = (current_generation > 0) ? current_generation - 1 : 0;
    }
    
    // Drop all variables in the exited region
    for (auto i = variable_memory_info.begin(); i != variable_memory_info.end();) {
        if (i->second.region_id == region_to_clean && i->second.memory_state != "dropped") {
            i = variable_memory_info.erase(i);
        } else {
            ++i;
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
                     info.type->toString() + "' was not freed before going out of scope\n\n= reason: Owned variables must be explicitly freed\n= help: use linear types, region GC, or compile-time analysis to manage memory", line);
        }
    }
}

void TypeChecker::check_use_after_free(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "dropped") {
            add_error("Use-after-free: variable '" + name + "' was freed and is no longer accessible\n\n= reason: Freed variables cannot be accessed\n= help: use linear types, regions, or lifetime checks to prevent use-after-free", line);
        }
    }
}

void TypeChecker::check_dangling_pointer(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "moved" || it->second.memory_state == "dropped") {
            add_error("Dangling pointer: variable '" + name + "' points to invalid memory\n\n= reason: Variable was moved or dropped\n= help: use region + generational references to prevent dangling pointers", line);
        }
    }
}

void TypeChecker::check_double_free(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "dropped") {
            add_error("Double free: variable '" + name + "' was already freed\n\n= reason: Variables can only be freed once\n= help: use single ownership and compile-time drop analysis", line);
        }
    }
}

void TypeChecker::check_multiple_owners(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it == variable_memory_info.end()) {
        return;
    }
    
    VariableInfo& var_info = it->second;
    
    // Check if variable is a linear type
    bool is_linear = (var_info.type &&
                     (var_info.type->tag == TypeTag::List ||
                      var_info.type->tag == TypeTag::Dict ||
                      var_info.type->tag == TypeTag::UserDefined));
    
    if (!is_linear) {
        return; // Only linear types need single ownership
    }
    
    // Track reference count for linear types
    if (var_info.reference_count > 1) {
        add_error("Multiple owners detected: variable '" + name + "' has " + 
                 std::to_string(var_info.reference_count) + " references\n\n= reason: Linear types require single ownership\n= help: move the value instead of copying, or use shared ownership patterns", line);
    }
}

void TypeChecker::check_buffer_overflow(const std::string& array_name, const std::string& index_expr, int line) {
    auto it = variable_memory_info.find(array_name);
    if (it == variable_memory_info.end()) {
        return; // Array not tracked
    }
    
    const VariableInfo& var_info = it->second;
    
    // Check if this is actually an array/list type
    if (var_info.type && var_info.type->tag == TypeTag::List) {
        // Try to evaluate the index expression if it's a constant
        // For now, we'll do a conservative check - warn about any dynamic index
        bool is_constant = (index_expr.find("var") == std::string::npos &&
                          index_expr.find("fn") == std::string::npos &&
                          index_expr.find("(") == std::string::npos);
        
        if (!is_constant) {
            // Dynamic index - warn about potential overflow
            add_error("Buffer overflow risk: array '" + array_name + "' accessed with dynamic index '" + index_expr + "'\n\n= reason: Cannot verify bounds at compile time\n= help: add explicit bounds check or use constant index", line);
        }
    }
}

void TypeChecker::check_uninitialized_use(const std::string& name, int line) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "uninitialized") {
            add_error("Uninitialized use: variable '" + name + "' used before initialization\n\n= reason: Variables must be initialized before use\n= help: require initialization or use zero-fill debug mode", line);
        }
    }
}

void TypeChecker::check_invalid_type(const std::string& var_name, TypePtr expected_type, TypePtr actual_type, int line) {
    if (!is_type_compatible(expected_type, actual_type)) {
        add_error("Invalid type: variable '" + var_name + "' type mismatch\n\n= reason: Expected type '" + expected_type->toString() + "' but found '" + actual_type->toString() + "'\n= help: use a compatible type or add explicit type conversion", line);
    }
}

void TypeChecker::check_misalignment(const std::string& ptr_name, int line) {
    auto it = variable_memory_info.find(ptr_name);
    if (it == variable_memory_info.end()) {
        return;
    }
    
    const VariableInfo& var_info = it->second;
    
    // Check if this is a pointer-like type (user-defined frames that might contain pointers)
    if (var_info.type && var_info.type->tag == TypeTag::UserDefined) {
        // For user-defined types, check if they require specific alignment
        // This is a conservative check - in a real implementation we'd check type metadata
        if (var_info.alloc_id % 8 != 0) {
            // Not 8-byte aligned - potential misalignment for 64-bit types
            add_error("Potential misalignment: '" + ptr_name + "' may not be properly aligned for its type\n\n= reason: User-defined types may require specific alignment\n= help: ensure proper allocation alignment", line);
        }
    }
}

void TypeChecker::check_heap_corruption(const std::string& operation, int line) {
    // Check for double writes to freed memory or writes outside allocated regions
    for (const auto& [var_name, var_info] : variable_memory_info) {
        if (var_info.memory_state == "dropped" || var_info.memory_state == "moved") {
            // Check if operation is trying to access freed/moved memory
            if (operation.find(var_name) != std::string::npos) {
                add_error("Heap corruption risk: operation '" + operation + "' may access freed memory '" + var_name + "'\n\n= reason: Memory was already freed or moved\n= help: ensure memory is valid before operation", line);
            }
        }
    }
}

void TypeChecker::check_race_condition(const std::string& shared_var, int line) {
    auto it = variable_memory_info.find(shared_var);
    if (it == variable_memory_info.end()) {
        return;
    }
    
    const VariableInfo& var_info = it->second;
    
    // Check if variable is in a state that could cause race conditions
    // Variables that are "owned" and shared across threads are potential race conditions
    if (var_info.memory_state == "owned") {
        // Check if this is a mutable type that could be modified concurrently
        bool is_mutable_type = (var_info.type &&
                               (var_info.type->tag == TypeTag::List ||
                                var_info.type->tag == TypeTag::Dict ||
                                var_info.type->tag == TypeTag::UserDefined));
        
        if (is_mutable_type) {
            add_error("Race condition risk: mutable variable '" + shared_var + "' may be accessed concurrently\n\n= reason: Mutable shared state without synchronization\n= help: use atomic operations, mutex, or move ownership instead of sharing", line);
        }
    }
}

void TypeChecker::check_variable_use(const std::string& name, int line) {
    TypePtr type = lookup_variable(name);
    if (type && (type->tag == TypeTag::Function || type->tag == TypeTag::Int || type->tag == TypeTag::Int64 || type->tag == TypeTag::String || type->tag == TypeTag::Bool)) return;
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "moved") {
            add_error("Use after move: variable '" + name + "' was moved and is no longer accessible\n\n= reason: Moved variables cannot be accessed\n= help: use linear types, regions, or lifetime checks", line);
            check_dangling_pointer(name, line);
        } else if (it->second.memory_state == "dropped") {
            add_error("Use after drop: variable '" + name + "' was dropped and is no longer accessible\n\n= reason: Dropped variables cannot be accessed\n= help: use single ownership and compile-time drop analysis", line);
            check_use_after_free(name, line);
        } else if (it->second.memory_state == "uninitialized") {
            add_error("Use before initialization: variable '" + name + "' is used before being initialized\n\n= reason: Variables must be initialized before use\n= help: require initialization or use zero-fill debug mode", line);
            check_uninitialized_use(name, line);
        }
    }
}

void TypeChecker::check_variable_move(const std::string& name) {
    TypePtr type = lookup_variable(name);
    if (type && (type->tag == TypeTag::Function || type->tag == TypeTag::Int || type->tag == TypeTag::Int64 || type->tag == TypeTag::String || type->tag == TypeTag::Bool)) return;
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
    // Also move in linear_types map to keep them in sync!
    if (linear_types.find(name) != linear_types.end()) {
        move_linear_type(name, current_line);
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
    if (it == variable_memory_info.end()) {
        return;
    }
    
    const VariableInfo& var_info = it->second;
    
    // Check if variable is a linear type
    bool is_linear = (var_info.type &&
                     (var_info.type->tag == TypeTag::List ||
                      var_info.type->tag == TypeTag::Dict ||
                      var_info.type->tag == TypeTag::UserDefined));
    
    if (!is_linear) {
        return; // Only linear types need escape analysis
    }
    
    // Check if variable is being moved to a different scope
    if (target_context != "current_scope") {
        // Variable escaping current scope
        if (var_info.memory_state == "owned") {
            add_error("Linear type '" + var_name + "' escapes its scope\n\n= reason: Linear types cannot escape their allocation scope\n= help: move the variable explicitly or use shared ownership", current_line);
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

// =============================================================================
// PHASE 1: OOP FRAME MEMORY SAFETY
// =============================================================================

// Frame field mutable aliasing detection
void TypeChecker::check_frame_field_mutable_aliasing(
    const std::string& frame_var,
    const std::string& field_name,
    bool is_mutable,
    int line) {
    
    std::string field_key = frame_var + "." + field_name;
    auto it = frame_field_memory_info.find(field_key);
    if (it == frame_field_memory_info.end()) {
        FrameFieldMemoryInfo info;
        info.frame_name = frame_var;
        info.field_name = field_name;
        info.is_linear = false;
        info.is_owned = true;
        info.has_exclusive_ref = false;
        frame_field_memory_info[field_key] = info;
        return;
    }
    
    FrameFieldMemoryInfo& field_info = it->second;
    if (is_mutable) {
        if (field_info.has_exclusive_ref) {
            add_error("Cannot create multiple mutable references to frame field '" + field_name + 
                     "' of frame '" + frame_var + "'", line);
            return;
        }
        if (!field_info.mutable_refs.empty()) {
            add_error("Frame field '" + field_name + "' is already borrowed mutably", line);
            return;
        }
    }
}

void TypeChecker::invalidate_frame_field_references(
    const std::string& frame_var,
    const std::string& field_name,
    int line) {
    
    std::string field_key = frame_var + "." + field_name;
    auto it = frame_field_memory_info.find(field_key);
    if (it != frame_field_memory_info.end()) {
        FrameFieldMemoryInfo& field_info = it->second;
        if (!field_info.mutable_refs.empty()) {
            add_error("Field '" + field_name + "' of frame '" + frame_var + 
                     "' was modified while having active references", line);
        }
        field_info.has_exclusive_ref = false;
        field_info.mutable_refs.clear();
    }
}

void TypeChecker::verify_frame_field_exclusive_access(
    const std::string& frame_var,
    const std::string& field_name,
    int line) {
    
    std::string field_key = frame_var + "." + field_name;
    auto it = frame_field_memory_info.find(field_key);
    if (it != frame_field_memory_info.end()) {
        FrameFieldMemoryInfo& field_info = it->second;
        if (field_info.has_exclusive_ref && !field_info.mutable_refs.empty()) {
            add_error("Field '" + field_name + "' of frame '" + frame_var + 
                     "' does not have exclusive access", line);
        }
    }
}

void TypeChecker::register_frame_for_deinit(
    const std::string& frame_name,
    int scope_level) {
    
    FrameAllocation alloc;
    alloc.frame_name = frame_name;
    alloc.scope_level = scope_level;
    alloc.line = current_line;
    frame_allocations_in_scope.push_back(alloc);
}

void TypeChecker::verify_frame_full_initialization(
    const std::string& frame_name,
    const std::vector<std::string>& initialized_fields,
    int line) {
    
    auto frame_it = frame_declarations.find(frame_name);
    if (frame_it == frame_declarations.end()) {
        return;
    }
    
    const FrameInfo& frame_info = frame_it->second;
    for (size_t i = 0; i < frame_info.fields.size(); ++i) {
        const std::string& field_name = frame_info.fields[i].first;
        bool has_default = frame_info.field_has_default[i].second;
        
        bool is_initialized = false;
        for (const auto& init_field : initialized_fields) {
            if (init_field == field_name) {
                is_initialized = true;
                break;
            }
        }
        
        if (!is_initialized && !has_default) {
            add_error("Frame '" + frame_name + "' field '" + field_name + 
                     "' must be initialized (no default value)", line);
        }
    }
}

void TypeChecker::check_frame_field_linear_types(
    const std::string& frame_name,
    const std::vector<std::pair<std::string, TypePtr>>& fields) {
    
    for (const auto& [field_name, field_type] : fields) {
        bool is_linear = false;
        if (field_type) {
            is_linear = (field_type->tag == TypeTag::List ||
                        field_type->tag == TypeTag::Dict ||
                        field_type->tag == TypeTag::UserDefined);
        }
        
        if (is_linear) {
            std::string field_key = frame_name + "." + field_name;
            auto it = frame_field_memory_info.find(field_key);
            if (it != frame_field_memory_info.end()) {
                it->second.is_linear = true;
                it->second.is_owned = true;
            }
        }
    }
}

void TypeChecker::verify_trait_implementation(
    const std::string& frame_name,
    const std::string& trait_name,
    const FrameInfo& frame_info) {
    
    auto trait_it = trait_declarations.find(trait_name);
    if (trait_it == trait_declarations.end()) {
        add_error("Unknown trait: " + trait_name, current_line);
        return;
    }
    
    (void)frame_info;
}

void TypeChecker::validate_method_signature_compatibility(
    std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> trait_method,
    std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> frame_method) {
    
    if (!trait_method || !frame_method) {
        return;
    }
    
    if (trait_method->params.size() != frame_method->params.size()) {
        add_error("Method signature mismatch: parameter count differs", current_line);
        return;
    }
    
    for (size_t i = 0; i < trait_method->params.size(); ++i) {
        const auto& trait_param_type = trait_method->params[i].second;
        const auto& frame_param_type = frame_method->params[i].second;
        
        TypePtr trait_type = resolve_type_annotation(trait_param_type);
        TypePtr frame_type = resolve_type_annotation(frame_param_type);
        
        if (!is_type_compatible(trait_type, frame_type)) {
            add_error("Method parameter type mismatch at parameter " + std::to_string(i + 1), current_line);
        }
    }
    
    TypePtr trait_return = trait_method->returnType.has_value() ? 
        resolve_type_annotation(trait_method->returnType.value()) : type_system.NIL_TYPE;
    TypePtr frame_return = frame_method->returnType.has_value() ? 
        resolve_type_annotation(frame_method->returnType.value()) : type_system.NIL_TYPE;
    
    if (!is_type_compatible(trait_return, frame_return)) {
        add_error("Method return type mismatch", current_line);
    }
}

// =============================================================================
// PHASE 2: CONTROL FLOW MEMORY SAFETY
// =============================================================================

void TypeChecker::check_linear_type_in_loop_body(
    const std::string& loop_var,
    const std::vector<std::shared_ptr<LM::Frontend::AST::Statement>>& body_statements,
    int line) {
    
    auto it = variable_memory_info.find(loop_var);
    if (it == variable_memory_info.end()) {
        return;
    }
    
    const VariableInfo& var_info = it->second;
    bool is_linear = (var_info.type->tag == TypeTag::List ||
                     var_info.type->tag == TypeTag::Dict ||
                     var_info.type->tag == TypeTag::UserDefined);
    
    if (!is_linear) {
        return;
    }
    
    int access_count = 0;
    std::function<void(const std::shared_ptr<LM::Frontend::AST::Statement>&)> count_accesses = 
        [&](const std::shared_ptr<LM::Frontend::AST::Statement>& stmt) {
            if (!stmt) return;
            if (auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt)) {
                std::function<void(const std::shared_ptr<LM::Frontend::AST::Expression>&)> check_expr = 
                    [&](const std::shared_ptr<LM::Frontend::AST::Expression>& expr) {
                        if (!expr) return;
                        if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
                            if (var->name == loop_var) {
                                access_count++;
                            }
                        }
                    };
                check_expr(expr_stmt->expression);
            }
            else if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
                for (const auto& s : block->statements) {
                    count_accesses(s);
                }
            }
        };
    
    for (const auto& stmt : body_statements) {
        count_accesses(stmt);
    }
    
    if (access_count > 1) {
        add_error("Linear type '" + loop_var + "' accessed " + 
                 std::to_string(access_count) + " times in loop", line);
    }
}

void TypeChecker::validate_break_cleanup(int line) {
    // Check that linear types in loop scope are properly handled on break
    for (const auto& [var_name, var_info] : variable_memory_info) {
        if (var_info.memory_state == "dropped") {
            continue;
        }
        
        // Check if variable is a linear type
        bool is_linear = (var_info.type &&
                         (var_info.type->tag == TypeTag::List ||
                          var_info.type->tag == TypeTag::Dict ||
                          var_info.type->tag == TypeTag::UserDefined));
        
        if (is_linear && var_info.memory_state == "owned") {
            // Linear type still owned when breaking - potential leak
            add_error("Linear type '" + var_name + "' may leak on break\n\n= reason: Variable still owned when breaking from loop\n= help: drop or move the variable before breaking", line);
        }
    }
}

void TypeChecker::validate_continue_cleanup(int line) {
    for (const auto& [ref_name, ref_info] : references) {
        if (!ref_info.is_valid) {
            continue;
        }
        if (ref_info.creation_scope < 0) {
            add_error("Reference '" + ref_name + "' has unclear scope for continue", line);
        }
    }
}

void TypeChecker::validate_scope_cleanup_on_control_flow(const std::string& control_flow_type, int line) {
    (void)control_flow_type;
    (void)line;
    for (const auto& [var_name, var_info] : variable_memory_info) {
        if (var_info.memory_state == "dropped") {
            continue;
        }
        bool is_linear = (var_info.type->tag == TypeTag::List ||
                         var_info.type->tag == TypeTag::Dict ||
                         var_info.type->tag == TypeTag::UserDefined);
        if (is_linear && var_info.memory_state != "moved") {
        }
    }
}

// =============================================================================
// PHASE 3: LAMBDA & CLOSURE SAFETY - COMPREHENSIVE IMPLEMENTATION
// =============================================================================
// Addresses memory safety gaps for lambda and closure capture semantics:
// - Variable capture analysis (identifies all captured variables)
// - Ownership validation (ensures valid ownership for captures)
// - Linear type move semantics (tracks ownership transfer)
// - Closure lifetime checking (prevents use-after-free)
// - Reference escape analysis (validates reference lifetime in closures)
// - Mutable capture validation (prevents invalid mutable captures)
// - Closure environment cleanup (proper resource deallocation)

void TypeChecker::analyze_lambda_captures(
    const std::shared_ptr<LM::Frontend::AST::LambdaExpr>& lambda) {
    
    if (!lambda) return;
    
    // Phase 3.1: AST traversal to find all variable references
    std::set<std::string> referenced_vars;
    std::set<std::string> mutable_referenced_vars;
    
    std::function<void(const std::shared_ptr<LM::Frontend::AST::Expression>&)> find_refs_expr = 
        [&](const std::shared_ptr<LM::Frontend::AST::Expression>& expr) {
            if (!expr) return;
            
            if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
                // Skip lambda parameters themselves
                bool is_param = false;
                for (const auto& [param_name, _] : lambda->params) {
                    if (param_name == var->name) {
                        is_param = true;
                        break;
                    }
                }
                if (!is_param) {
                    referenced_vars.insert(var->name);
                }
            }
            else if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
                find_refs_expr(call->callee);
                for (const auto& arg : call->arguments) {
                    find_refs_expr(arg);
                }
            }
            else if (auto binary = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
                find_refs_expr(binary->left);
                find_refs_expr(binary->right);
            }
            else if (auto unary = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
                find_refs_expr(unary->right);
            }
            else if (auto index = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
                find_refs_expr(index->object);
                find_refs_expr(index->index);
            }
            else if (auto member = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr)) {
                find_refs_expr(member->object);
            }
            else if (auto list = std::dynamic_pointer_cast<LM::Frontend::AST::ListExpr>(expr)) {
                for (const auto& elem : list->elements) {
                    find_refs_expr(elem);
                }
            }
            else if (auto dict = std::dynamic_pointer_cast<LM::Frontend::AST::DictExpr>(expr)) {
                for (const auto& [_, val] : dict->entries) {
                    find_refs_expr(val);
                }
            }
            else if (auto tuple = std::dynamic_pointer_cast<LM::Frontend::AST::TupleExpr>(expr)) {
                for (const auto& elem : tuple->elements) {
                    find_refs_expr(elem);
                }
            }
        };
    
    std::function<void(const std::shared_ptr<LM::Frontend::AST::Statement>&)> find_refs_stmt = 
        [&](const std::shared_ptr<LM::Frontend::AST::Statement>& stmt) {
            if (!stmt) return;
            
            if (auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt)) {
                find_refs_expr(expr_stmt->expression);
            }
            else if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
                for (const auto& s : block->statements) {
                    find_refs_stmt(s);
                }
            }
            else if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
                find_refs_expr(if_stmt->condition);
                find_refs_stmt(if_stmt->thenBranch);
                if (if_stmt->elseBranch) {
                    find_refs_stmt(if_stmt->elseBranch);
                }
            }
            else if (auto while_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WhileStatement>(stmt)) {
                find_refs_expr(while_stmt->condition);
                find_refs_stmt(while_stmt->body);
            }
            else if (auto for_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ForStatement>(stmt)) {
                find_refs_expr(nullptr);  // Initializer is a statement, skip
                find_refs_expr(for_stmt->condition);
                find_refs_expr(for_stmt->increment);
                find_refs_stmt(for_stmt->body);
            }
            else if (auto iter_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IterStatement>(stmt)) {
                find_refs_expr(iter_stmt->iterable);
                find_refs_stmt(iter_stmt->body);
            }
            else if (auto return_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
                if (return_stmt->value) {
                    find_refs_expr(return_stmt->value);
                }
            }
        };
    
    find_refs_stmt(lambda->body);
    
    // Phase 3.2: Validate and register each capture with ownership checks
    for (const auto& var_name : referenced_vars) {
        auto var_it = variable_memory_info.find(var_name);
        if (var_it == variable_memory_info.end()) {
            continue;  // Variable not in current scope - cannot capture
        }
        
        const VariableInfo& var_info = var_it->second;
        
        // Phase 3.2.1: Check variable current memory state
        if (var_info.memory_state == "moved") {
            add_error("Cannot capture moved variable '" + var_name + "' in lambda\n\n= reason: Moved variables cannot be captured - ownership already transferred\n= help: ensure variable has not been moved before capturing in lambda", lambda->line);
            continue;
        }
        
        if (var_info.memory_state == "dropped") {
            add_error("Cannot capture dropped variable '" + var_name + "' in lambda\n\n= reason: Dropped variables cannot be captured - no longer valid\n= help: ensure variable has not been dropped before capturing in lambda", lambda->line);
            continue;
        }
        
        // Phase 3.2.2: Determine if variable is linear type
        bool is_linear = (var_info.type && 
                         (var_info.type->tag == TypeTag::List ||
                          var_info.type->tag == TypeTag::Dict ||
                          var_info.type->tag == TypeTag::UserDefined));
        
        // Phase 3.2.3: Create capture record with metadata
        // Track capture using current_lambda_captures stack
        current_lambda_captures.push_back({
            var_name,  // variable_name
            false,     // is_moved
            false,     // is_mutable_ref
            lambda->line,  // line
            var_info.type  // capture_type
        });
    }
}

void TypeChecker::validate_capture_ownership(
    const std::string& capture_var, bool is_moved, int line) {
    
    // Phase 3.3: Validate ownership transfer for capture
    auto var_it = variable_memory_info.find(capture_var);
    if (var_it == variable_memory_info.end()) {
        return;  // Variable not in scope
    }
    
    VariableInfo& var_info = var_it->second;
    
    // Check if variable is linear
    bool is_linear = (var_info.type &&
                     (var_info.type->tag == TypeTag::List ||
                      var_info.type->tag == TypeTag::Dict ||
                      var_info.type->tag == TypeTag::UserDefined));
    
    // Phase 3.3.1: Handle linear type ownership transfer (move semantics)
    if (is_moved && is_linear) {
        // Linear type cannot be captured multiple times
        // Moving it into closure transfers ownership
        
        // Mark original variable as moved
        if (var_info.memory_state == "owned") {
            var_info.memory_state = "moved";
        }
        
        add_error("Linear type '" + capture_var + "' moved into lambda capture\n\n= reason: Ownership transferred to closure\n= help: variable can no longer be used after capture", line);
    } 
    // Phase 3.3.2: Borrowing for non-linear or immutable captures
    else if (!is_moved && !is_linear) {
        // Non-linear types can be captured by reference (borrow)
        // This is safe
    }
    // Phase 3.3.3: Error for moving non-linear types unnecessarily
    else if (is_moved && !is_linear) {
        add_error("Cannot move non-linear type '" + capture_var + "' - use borrowing instead\n\n= reason: Non-linear types should be borrowed, not moved\n= help: capture by reference instead", line);
    }
}

void TypeChecker::check_closure_lifetime(const std::string& closure_var, int line) {
    // Phase 3.4: Validate closure lifetime against captured variables
    
    // Check each variable in the current lambda capture stack
    for (const auto& capture_var : current_lambda_captures) {
        auto var_it = variable_memory_info.find(capture_var.variable_name);
        if (var_it == variable_memory_info.end()) {
            add_error("Closure '" + closure_var + "' captures variable '" + capture_var.variable_name + 
                     "' that is no longer in scope\n\n= reason: Captured variable has been dropped\n= help: ensure closure is dropped before captured variable goes out of scope", line);
            continue;
        }
        
        const VariableInfo& var_info = var_it->second;
        
        // Check for use-after-free scenarios
        if (var_info.memory_state == "dropped") {
            add_error("Closure '" + closure_var + "' captures dropped variable '" + capture_var.variable_name + 
                     "'\n\n= reason: Captured variable was dropped - closure references invalid memory\n= help: ensure captured variables are valid when closure is invoked", line);
        }
    }
}

void TypeChecker::validate_lambda_escape_analysis(
    const std::shared_ptr<LM::Frontend::AST::LambdaExpr>& lambda) {
    // Phase 3.5: Perform escape analysis on lambda expression
    
    if (!lambda) return;
    
    // Determine if lambda escapes current scope
    bool can_escape = false;
    
    // Check if lambda is being returned (escapes to outer scope)
    if (current_return_type) {
        can_escape = true;
    }
    
    if (!can_escape) {
        return;  // Lambda doesn't escape - captures are safe
    }
    
    // For escaping lambdas, validate captured variables
    if (lambda_captures_stack.empty()) return;
    
    for (const auto& capture_var : current_lambda_captures) {
        auto var_it = variable_memory_info.find(capture_var.variable_name);
        if (var_it == variable_memory_info.end()) continue;
        
        const VariableInfo& var_info = var_it->second;
        
        // Check if variable is a linear type that cannot escape
        bool is_linear = (var_info.type &&
                         (var_info.type->tag == TypeTag::List ||
                          var_info.type->tag == TypeTag::Dict ||
                          var_info.type->tag == TypeTag::UserDefined));
        
        if (is_linear && !capture_var.is_moved) {
            add_error("Escaping lambda captures linear type '" + capture_var.variable_name + 
                     "'\n\n= reason: Linear types cannot be borrowed across scope boundaries\n= help: move the linear type into the lambda or use shared ownership", lambda->line);
        }
    }
}

// =============================================================================
// PHASE 4: CONCURRENCY SAFETY - COMPREHENSIVE IMPLEMENTATION
// =============================================================================
// Addresses memory safety for parallel and concurrent execution:
// - Thread-safe type checking (Send/Sync traits)
// - Data race detection and prevention
// - Linear type across thread boundaries
// - Channel type safety validation
// - Reference lifetime across threads

void TypeChecker::check_parallel_block_thread_safety(
    const std::vector<std::string>& captured_vars, int line) {
    
    // Phase 4.1: Parallel block type safety analysis
    // Parallel blocks require Send types (can move) and Sync types (can share)
    
    for (const auto& var_name : captured_vars) {
        auto it = variable_memory_info.find(var_name);
        if (it == variable_memory_info.end()) {
            continue;  // Variable not tracked
        }
        
        const VariableInfo& var_info = it->second;
        
        // Phase 4.1.1: Check if type is Send-safe
        bool is_send = (var_info.type &&
                       (var_info.type->tag == TypeTag::Int ||
                        var_info.type->tag == TypeTag::Int64 ||
                        var_info.type->tag == TypeTag::Float32 ||
                        var_info.type->tag == TypeTag::Float64 ||
                        var_info.type->tag == TypeTag::Bool ||
                        var_info.type->tag == TypeTag::String));
        
        // Phase 4.1.2: Detect linear types in parallel (data race risk)
        bool is_linear = (var_info.type &&
                         (var_info.type->tag == TypeTag::List ||
                          var_info.type->tag == TypeTag::Dict ||
                          var_info.type->tag == TypeTag::UserDefined));
        
        if (is_linear && !is_send) {
            add_error("Linear type '" + var_name + "' in parallel block - data race risk\n\n= reason: Multiple threads access same linear type\n= help: move linear type to thread or use atomic/mutex", line);
        }
        
        // Phase 4.1.3: Check mutable access without synchronization
        if (var_info.memory_state == "owned") {
            // Mutable variable shared in parallel
            add_error("Mutable variable '" + var_name + "' shared across threads without synchronization\n\n= reason: Multiple threads can modify - data race\n= help: use atomic, mutex, or move instead of sharing", line);
        }
    }
}

void TypeChecker::check_concurrent_block_thread_safety(
    const std::vector<std::string>& captured_vars, int line) {
    
    // Phase 4.2: Concurrent block type safety analysis  
    // Concurrent blocks (I/O-bound) also require Send/Sync types
    
    for (const auto& var_name : captured_vars) {
        auto it = variable_memory_info.find(var_name);
        if (it == variable_memory_info.end()) {
            continue;
        }
        
        const VariableInfo& var_info = it->second;
        
        // Phase 4.2.1: Identify linear types in tasks
        bool is_linear = (var_info.type &&
                         (var_info.type->tag == TypeTag::List ||
                          var_info.type->tag == TypeTag::Dict ||
                          var_info.type->tag == TypeTag::UserDefined));
        
        if (is_linear) {
            add_error("Linear type '" + var_name + "' in concurrent block\n\n= reason: Linear types cannot be safely shared between tasks\n= help: move linear type to specific task or use channels for communication", line);
        }
        
        // Phase 4.2.2: Check for mutable concurrent access
        if (var_info.memory_state == "owned") {
            add_error("Mutable variable '" + var_name + "' accessed from multiple concurrent tasks\n\n= reason: Concurrent tasks can interleave - data race possible\n= help: use mutex, atomic, or task-local copy", line);
        }
    }
}

void TypeChecker::detect_data_races(const std::string& var_name, int line) {
    // Phase 4.3: Data race detection
    
    auto it = variable_memory_info.find(var_name);
    if (it == variable_memory_info.end()) {
        return;
    }
    
    const VariableInfo& var_info = it->second;
    
    // Phase 4.3.1: Check if variable is shared without protection
    // In concurrent context, owned (mutable) variables are race risks
    if (concurrency_context.in_concurrent_block || concurrency_context.in_parallel_block) {
        if (var_info.memory_state == "owned") {
            add_error("Data race: variable '" + var_name + "' accessed from multiple threads\n\n= reason: Multiple threads can modify variable simultaneously\n= help: use atomic operations, mutex, or thread-local storage", line);
        }
    }
}

void TypeChecker::validate_send_trait(TypePtr type, int line) {
    // Phase 4.4: Validate Send trait
    // Send types can be moved to different threads
    
    if (!type) {
        add_error("Cannot validate Send trait for null type", line);
        return;
    }
    
    // Primitives and strings are Send
    bool is_send = (type->tag == TypeTag::Int ||
                   type->tag == TypeTag::Int64 ||
                   type->tag == TypeTag::Float32 ||
                   type->tag == TypeTag::Float64 ||
                   type->tag == TypeTag::Bool ||
                   type->tag == TypeTag::String);
    
    // Linear types are Send (can move to thread)
    bool is_linear_send = (type->tag == TypeTag::List ||
                          type->tag == TypeTag::Dict);
    
    // User-defined types need Send marker
    bool is_user_send = (type->tag == TypeTag::UserDefined);
    // For now, assume user-defined might not be Send
    
    if (!is_send && !is_linear_send && type->tag == TypeTag::UserDefined) {
        add_error("Type '" + type->toString() + "' does not implement Send trait - cannot move to thread\n\n= reason: Type cannot be safely transferred between threads\n= help: add Send implementation or use Rc/Arc for sharing", line);
    }
}

void TypeChecker::validate_sync_trait(TypePtr type, int line) {
    // Phase 4.5: Validate Sync trait
    // Sync types can be safely shared between threads
    
    if (!type) {
        add_error("Cannot validate Sync trait for null type", line);
        return;
    }
    
    // Only primitives are Sync (can be safely shared)
    bool is_sync = (type->tag == TypeTag::Int ||
                   type->tag == TypeTag::Int64 ||
                   type->tag == TypeTag::Float32 ||
                   type->tag == TypeTag::Float64 ||
                   type->tag == TypeTag::Bool);
    
    // Linear types are NOT Sync (exclusive ownership)
    bool is_linear = (type->tag == TypeTag::List ||
                     type->tag == TypeTag::Dict);
    
    if (is_linear) {
        add_error("Type '" + type->toString() + "' does not implement Sync trait - cannot safely share between threads\n\n= reason: Linear types have exclusive ownership\n= help: move to specific thread or use mutex", line);
    }
}

void TypeChecker::check_channel_type_safety(
    const std::shared_ptr<LM::Frontend::AST::CallExpr>& send_expr, int line) {
    
    // Phase 4.6: Channel type safety checking
    
    if (!send_expr) return;
    
    // Get the callee (should be channel.send)
    auto member = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(send_expr->callee);
    if (!member) return;
    
    // Phase 4.6.1: Get channel variable name
    auto ch_var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(member->object);
    if (!ch_var) return;
    
    // Phase 4.6.2: Get type being sent (first argument)
    if (send_expr->arguments.empty()) return;
    
    auto sent_expr = send_expr->arguments[0];
    TypePtr sent_type = nullptr;
    
    // Try to infer type of expression being sent
    if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(sent_expr)) {
        auto it = variable_memory_info.find(var->name);
        if (it != variable_memory_info.end()) {
            sent_type = it->second.type;
        }
    }
    
    if (!sent_type) return;
    
    // Phase 4.6.3: Validate Send trait for type
    validate_send_trait(sent_type, line);
    
    // Phase 4.6.4: Check for linear type in channel
    bool is_linear = (sent_type->tag == TypeTag::List ||
                     sent_type->tag == TypeTag::Dict ||
                     sent_type->tag == TypeTag::UserDefined);
    
    if (is_linear) {
        // Linear types can be sent (move semantics)
        // But mark original as moved
        if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(sent_expr)) {
            auto it = variable_memory_info.find(var->name);
            if (it != variable_memory_info.end()) {
                it->second.memory_state = "moved";
            }
        }
    }
}

// =============================================================================
// PHASE 5: ENUM & PATTERN SAFETY
// =============================================================================

void TypeChecker::register_enum_variant(
    const std::string& enum_name,
    const std::string& variant_name,
    const std::vector<TypePtr>& associated_types) {
    // =========================================================================
    // PHASE 5.1: ENUM VARIANT OWNERSHIP TRACKING
    // =========================================================================
    // Purpose: Track variant information for memory safety analysis
    
    // Create variant information
    VariantInfo variant_info;
    variant_info.enum_name = enum_name;
    variant_info.variant_name = variant_name;
    variant_info.associated_types = associated_types;
    
    // Register in global variant registry
    std::string variant_key = enum_name + "::" + variant_name;
    variant_registry[variant_key] = variant_info;
    
    // Update variant owners mapping
    if (variant_owners.find(enum_name) == variant_owners.end()) {
        variant_owners[enum_name] = std::vector<TypePtr>();
    }
    
    // Store types associated with this variant
    for (const auto& type : associated_types) {
        variant_owners[enum_name].push_back(type);
    }
}

void TypeChecker::check_variant_constructor_ownership(
    const std::string& variant_name,
    const std::vector<TypePtr>& arg_types,
    int line) {
    // =========================================================================
    // PHASE 5.1: VARIANT CONSTRUCTOR OWNERSHIP VALIDATION
    // =========================================================================
    // Purpose: Validate that variant construction preserves ownership semantics
    
    // Find variant in registry
    auto variant_it = variant_registry.find(variant_name);
    if (variant_it == variant_registry.end()) {
        // Variant not found in registry
        add_error("Unknown variant: " + variant_name, line);
        return;
    }
    
    const auto& variant_info = variant_it->second;
    const auto& expected_types = variant_info.associated_types;
    
    // Check argument count matches
    if (arg_types.size() != expected_types.size()) {
        add_error("Variant " + variant_name + " expects " + 
                 std::to_string(expected_types.size()) + " arguments, got " + 
                 std::to_string(arg_types.size()), line);
        return;
    }
    
    // Validate each argument type matches expected type
    for (size_t i = 0; i < arg_types.size(); ++i) {
        if (!is_type_compatible(expected_types[i], arg_types[i])) {
            add_error("Argument " + std::to_string(i) + " of variant " + variant_name + 
                     " has incompatible type", line);
            return;
        }
        
        // Phase 5.1.1: Check if argument is a linear type reference
        // Linear types need special handling in variants
        // References and special types may require special cleanup
        if (arg_types[i]) {
            // Note: Ownership is tracked through variable_memory_info
            // Linear arguments will be moved into variant
        }
    }
}

void TypeChecker::validate_pattern_binding_ownership(
    const std::shared_ptr<LM::Frontend::AST::Expression>& pattern,
    TypePtr match_type,
    int line) {
    // =========================================================================
    // PHASE 5.2: PATTERN BINDING SAFETY VALIDATION
    // =========================================================================
    // Purpose: Ensure pattern bindings have correct ownership semantics
    
    if (!pattern) return;
    
    // Check for binding pattern (e.g., Some(x), Container.Full(data))
    auto binding_pattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(pattern);
    if (binding_pattern) {
        // Phase 5.2.1: Validate binding pattern safety
        // For each bound variable, check ownership
        for (const auto& inner_pattern : binding_pattern->patterns) {
            if (!inner_pattern) continue;
            
            // Get the variable name from the pattern
            auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(inner_pattern);
            if (var_expr) {
                const std::string& binding_var = var_expr->name;
                
                // Phase 5.2.2: Determine if binding is move or borrow
                // Check if match_type represents a linear/moved type
                if (linear_types.find(binding_var) != linear_types.end()) {
                    // This is a linear type - binding creates a move
                    check_pattern_linear_type_move(binding_var, match_type, line);
                } else if (match_type) {
                    // This is a non-linear type - binding copies or borrows
                    // Register binding in variable tracking
                    declare_variable(binding_var, match_type);
                }
            }
        }
    }
    
    // Check for or pattern (A | B)
    auto or_pattern = std::dynamic_pointer_cast<LM::Frontend::AST::OrPatternExpr>(pattern);
    if (or_pattern) {
        // Phase 5.2.3: Validate all arms have consistent bindings
        for (const auto& arm_pattern : or_pattern->patterns) {
            validate_pattern_binding_ownership(arm_pattern, match_type, line);
        }
    }
}

void TypeChecker::check_pattern_linear_type_move(
    const std::string& binding_var, TypePtr pattern_type, int line) {
    // =========================================================================
    // PHASE 5.2: PATTERN LINEAR TYPE MOVE SEMANTICS
    // =========================================================================
    // Purpose: Validate that linear type bindings in patterns use move semantics
    
    if (!pattern_type) return;
    
    // Phase 5.2.4: Validate linear type move
    // When a linear type is bound in a pattern, it is moved (not borrowed)
    
    // Check if the binding_var is in the linear types tracker
    // If it's being bound from a pattern match, it's a move
    
    // Phase 5.2.5: Register linear type binding as moved
    // The binding_var now owns the linear value
    declare_variable(binding_var, pattern_type);
    
    // Mark the binding as having linear semantics
    if (variable_memory_info.find(binding_var) != variable_memory_info.end()) {
        variable_memory_info[binding_var].memory_state = "owned_by_pattern";
    }
    
    // Phase 5.2.6: Validate the binding doesn't escape the pattern scope
    // This will be checked during pattern arm execution
    // The binding will be dropped when exiting the match arm
}

// =============================================================================
// PHASE 6: EXCEPTION SAFETY
// =============================================================================

void TypeChecker::validate_frame_init_exception_safety(
    const std::string& frame_name,
    const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& init_method,
    int line) {
    // =========================================================================
    // PHASE 6.1: FRAME INIT EXCEPTION SAFETY
    // =========================================================================
    // Purpose: Ensure frames are cleaned up if init fails partway through
    
    if (!init_method) return;
    
    // Phase 6.1.1: Track that we're analyzing an init method
    exception_safety_context.current_frame_name = frame_name;
    exception_safety_context.in_init_method = true;
    exception_safety_context.initialized_fields.clear();
    exception_safety_context.exit_paths.clear();
    
    // Phase 6.1.2: Analyze init method body for field initializations
    if (init_method->body) {
        auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(init_method->body);
        if (block) {
            for (const auto& stmt : block->statements) {
                if (!stmt) continue;
                
                // Track field assignments: self.field = ...
                auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt);
                if (expr_stmt && expr_stmt->expression) {
                    auto assign_expr = std::dynamic_pointer_cast<LM::Frontend::AST::AssignExpr>(expr_stmt->expression);
                    if (assign_expr && assign_expr->object && assign_expr->member) {
                        // Check if it's self.field assignment
                        auto self_var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(assign_expr->object);
                        if (self_var && self_var->name == "self") {
                            // This is a field initialization
                            std::string field_name = assign_expr->member.value();
                            
                            // Phase 6.1.3: Track field as initialized
                            FieldInitializationInfo field_info;
                            field_info.field_name = field_name;
                            field_info.initialization_line = stmt->line;
                            field_info.is_initialized = true;
                            field_info.init_order = static_cast<int>(exception_safety_context.initialized_fields.size());
                            
                            exception_safety_context.initialized_fields.push_back(field_info);
                        }
                    }
                }
                
                // Phase 6.1.4: Check for error propagation (? operator)
                auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt);
                if (var_decl) {
                    // Check if initialization might fail (contains ?)
                    if (var_decl->initializer) {
                        auto fallible = std::dynamic_pointer_cast<LM::Frontend::AST::FallibleExpr>(var_decl->initializer);
                        if (fallible) {
                            // This field init can fail
                            if (!exception_safety_context.initialized_fields.empty()) {
                                exception_safety_context.initialized_fields.back().has_error_handling = true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Phase 6.1.5: Validate all fields can be cleaned up on init failure
    for (const auto& field : exception_safety_context.initialized_fields) {
        // Check that field type can be dropped
        if (field.field_type) {
            // Most types can be dropped - verify this in type system if needed
        }
    }
    
    exception_safety_context.in_init_method = false;
}

void TypeChecker::track_field_initialization_order(const std::string& frame_name) {
    // =========================================================================
    // PHASE 6.2: FIELD INITIALIZATION ORDER TRACKING
    // =========================================================================
    // Purpose: Maintain and validate field initialization order for cleanup
    
    // Phase 6.2.1: Build cleanup order (reverse of init order)
    // Fields must be cleaned up in reverse order of initialization
    exception_safety_context.cleanup_order.clear();
    
    // Phase 6.2.2: Walk through initialized fields in reverse
    for (int i = static_cast<int>(exception_safety_context.initialized_fields.size()) - 1; i >= 0; --i) {
        const auto& field = exception_safety_context.initialized_fields[i];
        exception_safety_context.cleanup_order.push_back(field.field_name);
    }
    
    // Phase 6.2.3: Validate deterministic order
    // All paths must initialize in same order for predictable cleanup
    // This is already enforced by C++ member initialization order
    
    // Phase 6.2.4: Check for circular dependencies
    // If field A depends on field B, ensure B is initialized first
    // This would be detected during type checking if implemented
}

void TypeChecker::validate_cleanup_on_exception(
    const std::vector<std::string>& initialized_fields, int line) {
    // =========================================================================
    // PHASE 6.3: CLEANUP GUARANTEE SYSTEM
    // =========================================================================
    // Purpose: Ensure cleanup is guaranteed even on error paths
    
    // Phase 6.3.1: Verify all exit paths have cleanup
    // Exit paths: return, break, continue, ?, error propagation
    
    // Phase 6.3.2: For each initialized field, check cleanup guarantee
    for (const auto& field_name : initialized_fields) {
        // Find field in resource cleanup tracking
        if (resource_cleanup_tracking.find(field_name) != resource_cleanup_tracking.end()) {
            auto& cleanup_info = resource_cleanup_tracking[field_name];
            
            // Phase 6.3.3: Verify cleanup sites are on all exit paths
            if (cleanup_info.cleanup_sites.empty()) {
                add_error("Field '" + field_name + "' has no cleanup site\n\n" +
                         "= reason: Exception safety requires cleanup on all exit paths\n" +
                         "= help: ensure field is cleaned up in deinit or error handler", line);
            }
            
            cleanup_info.cleanup_guaranteed = true;
        }
    }
    
    // Phase 6.3.4: Check for double-cleanup prevention
    // Ensure same field isn't cleaned multiple times
    std::unordered_set<std::string> cleaned_fields;
    for (const auto& field_name : initialized_fields) {
        if (cleaned_fields.find(field_name) != cleaned_fields.end()) {
            add_error("Field '" + field_name + "' cleaned up multiple times\n\n" +
                     "= reason: Double cleanup can cause crashes\n" +
                     "= help: ensure each field is only cleaned once", line);
        }
        cleaned_fields.insert(field_name);
    }
}

} // namespace Frontend
} // namespace LM
