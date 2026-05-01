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
        if (it->second.memory_state == "owned") {
            // In a real implementation, we'd track ownership transfers
            // For now, this is a placeholder
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
            add_error("Use of uninitialized variable '" + name + "' [Mitigation: Require initialization before use]", line);
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
    TypePtr type = lookup_variable(name);
    if (type && (type->tag == TypeTag::Function || type->tag == TypeTag::Int || type->tag == TypeTag::Int64 || type->tag == TypeTag::String || type->tag == TypeTag::Bool)) return;
    
    // Check if variable is in memory info
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "dropped") {
            check_use_after_free(name, line);
        } else if (it->second.memory_state == "uninitialized") {
            check_uninitialized_use(name, line);
        }
    }
}

void TypeChecker::check_variable_move(const std::string& name) {
    TypePtr type = lookup_variable(name);
    if (type && (type->tag == TypeTag::Function || type->tag == TypeTag::Int || type->tag == TypeTag::Int64 || type->tag == TypeTag::String || type->tag == TypeTag::Bool)) return;
    
    // Mark variable as moved
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        it->second.memory_state = "moved";
    }
}

void TypeChecker::check_variable_drop(const std::string& name) {
    auto it = variable_memory_info.find(name);
    if (it != variable_memory_info.end()) {
        if (it->second.memory_state == "dropped") {
            check_double_free(name, 0);
        } else {
            it->second.memory_state = "dropped";
        }
    }
}

void TypeChecker::check_borrow_safety(const std::string& var_name) {
    auto it = variable_memory_info.find(var_name);
    if (it != variable_memory_info.end()) {
        // Check if variable can be borrowed
        if (it->second.memory_state == "dropped" || it->second.memory_state == "moved") {
            add_error("Cannot borrow variable '" + var_name + "' - it has been moved or dropped", 0);
        }
    }
}

void TypeChecker::check_escape_analysis(const std::string& var_name, const std::string& target_context) {
    // Escape analysis logic - to be updated for frames
}

bool TypeChecker::is_variable_alive(const std::string& name) {
    auto it = variable_memory_info.find(name);
    return (it != variable_memory_info.end() && 
            it->second.memory_state != "dropped" && 
            it->second.memory_state != "moved");
}

void TypeChecker::mark_variable_moved(const std::string& name) {
    check_variable_move(name);
}

void TypeChecker::mark_variable_dropped(const std::string& name) {
    check_variable_drop(name);
}

} // namespace Frontend
} // namespace LM
