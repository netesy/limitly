#include "type_checker.hh"
#include "module_manager.hh"
#include "../error/debugger.hh"
#include "../memory/model.hh"
#include "parser.hh"
#include "scanner.hh"
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <sstream>

namespace LM {
namespace Frontend {
using namespace LM::Error;

bool TypeChecker::check_program(std::shared_ptr<LM::Frontend::AST::Program> program) {
    if (!program) {
        add_error("Null program provided");
        return false;
    }
    
    current_program_ = program;  // Store for import handling
    
    Debugger::resetError();
    errors.clear();
    current_scope = std::make_unique<Scope>();

    // PASS 0: Module Resolution and Type Checking
    auto& manager = ModuleManager::getInstance();
    // manager.clear(); // Removed to prevent infinite recursion
    // manager.resolve_all(program, "root"); // Handled by factory or initial call
    if (manager.has_circular_dependencies()) {
        add_error("Circular dependency detected in modules");
    }

    // Type check all loaded modules recursively
    auto all_modules = manager.get_all_modules();
    for (const auto& [path, module] : all_modules) {
        if (module && !module->is_checked) {
            module->is_checked = true; // Mark before to prevent recursion
            TypeSystem ts;
            TypeChecker checker(ts);
            checker.set_source_context(module->source, module->path);
            if (!checker.check_program(module->ast)) {
                add_error("Failed to type check module: " + path);
            }
        }
    }

    for (const auto& stmt : program->statements) {
        if (auto mod_decl = std::dynamic_pointer_cast<LM::Frontend::AST::ModuleDeclaration>(stmt)) {
            check_module_declaration(mod_decl);
        } else if (auto import_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ImportStatement>(stmt)) {
            check_import_statement(import_stmt);
        }
    }


    // Register built-in functions in the global scope
    for (const auto& pair : function_signatures) {
        declare_variable(pair.first, type_system.FUNCTION_TYPE);
    }
    
    // PASS 1: Name Registration (including inlined symbols)
    auto register_name = [&](const std::string& name, const std::shared_ptr<LM::Frontend::AST::Statement>& stmt) {
        if (auto frame_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
            type_system.addUserDefinedType(name, type_system.createFrameType(name));
        } else if (auto trait_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) {
            TypePtr trait_type = std::make_shared<::Type>(TypeTag::Trait);
            type_system.addUserDefinedType(name, trait_type);
        }
    };

    for (const auto& stmt : program->statements) {
        std::string name;
        if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) name = frame->name;
        else if (auto trait = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) name = trait->name;
        if (!name.empty()) register_name(name, stmt);
    }
    for (const auto& [name, stmt] : program->imported_symbols) {
        register_name(name, stmt);
    }

    // PASS 2: Signature Resolution (including inlined symbols)
    auto resolve_sig = [&](const std::string& name, const std::shared_ptr<LM::Frontend::AST::Statement>& stmt) {
        if (auto frame_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
            TypeSystem::FrameInfo info;
            info.name = name;
            info.declaration = frame_decl;
            info.implements = frame_decl->implements;
            info.hasInit = (frame_decl->init != nullptr);
            info.hasDeinit = (frame_decl->deinit != nullptr);

            size_t offset = 0;
            for (const auto& field : frame_decl->fields) {
                TypePtr field_type = field->type ? resolve_type_annotation(field->type) : type_system.ANY_TYPE;
                info.fields.push_back({field->name, field_type});
                info.fieldVisibilities[field->name] = field->visibility;
                info.fieldOffsets[field->name] = offset++;
            }
            info.totalFieldSize = offset;

            if (frame_decl->init) {
                std::string init_name = name + ".init";
                FunctionSignature sig;
                sig.name = init_name;
                sig.return_type = type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(name));
                for (const auto& p : frame_decl->init->parameters) sig.param_types.push_back(resolve_type_annotation(p.second));
                function_signatures[init_name] = sig;
            }
            for (const auto& m : frame_decl->methods) {
                std::string m_name = name + "." + m->name;
                FunctionSignature sig;
                sig.name = m_name;
                sig.return_type = m->returnType ? resolve_type_annotation(m->returnType) : type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(name));
                for (const auto& p : m->parameters) sig.param_types.push_back(resolve_type_annotation(p.second));
                function_signatures[m_name] = sig;
                info.methodSignatures[m->name] = sig.return_type;
            }
            if (frame_decl->deinit) {
                std::string deinit_name = name + ".deinit";
                FunctionSignature sig;
                sig.name = deinit_name;
                sig.return_type = type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(name));
                function_signatures[deinit_name] = sig;
            }

            type_system.registerFrame(name, info);
            frame_declarations[name].name = info.name;
            frame_declarations[name].declaration = frame_decl;
            frame_declarations[name].fields = info.fields;

        } else if (auto trait_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) {
            TypeSystem::TraitInfo info;
            info.name = name;
            info.declaration = trait_decl;
            info.extends = trait_decl->extends;
            for (const auto& m : trait_decl->methods) {
                std::string m_name = name + "." + m->name;
                FunctionSignature sig;
                sig.name = m_name;
                sig.return_type = m->returnType ? resolve_type_annotation(m->returnType.value()) : type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.ANY_TYPE);
                for (const auto& p : m->params) sig.param_types.push_back(resolve_type_annotation(p.second));
                function_signatures[m_name] = sig;
                info.methodSignatures[m->name] = sig.return_type;
            }
            type_system.registerTrait(name, info);
        } else if (auto func_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
            FunctionSignature sig;
            sig.name = name;
            if (func_decl->name == "main") {
                 sig.return_type = type_system.INT64_TYPE;
            } else {
                 sig.return_type = func_decl->returnType ? resolve_type_annotation(func_decl->returnType.value()) : type_system.STRING_TYPE;
            }
            sig.declaration = func_decl;
            sig.can_fail = func_decl->canFail || func_decl->throws;
            sig.error_types = func_decl->declaredErrorTypes;
            for (const auto& p : func_decl->params) {
                sig.param_types.push_back(resolve_type_annotation(p.second));
                sig.optional_params.push_back(false);
            }
            for (const auto& op : func_decl->optionalParams) {
                sig.param_types.push_back(resolve_type_annotation(op.second.first));
                sig.optional_params.push_back(true);
            }
            function_signatures[name] = sig;
            declare_variable(name, type_system.FUNCTION_TYPE);
        } else if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
            TypePtr var_type = (var_decl->type && var_decl->type.value()) ? resolve_type_annotation(var_decl->type.value()) : type_system.ANY_TYPE;
            declare_variable(name, var_type);
        }
    };

    for (const auto& stmt : program->statements) {
        std::string name;
        if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) name = frame->name;
        else if (auto trait = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) name = trait->name;
        else if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) name = func->name;
        if (!name.empty()) resolve_sig(name, stmt);
    }
    for (const auto& [name, stmt] : program->imported_symbols) {
        resolve_sig(name, stmt);
    }

    // PASS 3: Body Verification (local and inlined symbols)
    for (const auto& stmt : program->statements) {
        if (auto func_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
            if (func_decl->name == "main") {
                // Ensure main's signature uses String for params if needed by the language
                // but let's just make it return int
            }
        }
        check_statement(stmt);
    }
    for (const auto& [name, stmt] : program->imported_symbols) {
        // Skip frames in PASS 3 as their methods are checked when frame is checked
        if (auto frame_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
            // Check frame declaration using qualified name
            check_frame_declaration_with_name(name, frame_decl);
            continue;
        } else if (auto func_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
            // Save original name, set to qualified name for checking, then restore
            std::string original_name = func_decl->name;
            func_decl->name = name;
            check_function_declaration(func_decl);
            func_decl->name = original_name;
            continue;
        }
        check_statement(stmt);
    }
    

    program->inferred_type = type_system.NIL_TYPE;
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

void TypeChecker::add_error(const std::string& message, int line, int column, const std::string& context, 
                         const std::string& lexeme, const std::string& expected_value) {
    // Enhanced error with lexeme and expected value information
    std::string enhancedMessage = message;
    if (!lexeme.empty()) {
        enhancedMessage += " (at '" + lexeme + "')";
    }
    if (!expected_value.empty()) {
        enhancedMessage += " - expected: " + expected_value;
    }
    
    if (line > 0 && !current_source.empty()) {
        Debugger::error(enhancedMessage, line, column, InterpretationStage::SEMANTIC, current_source, current_file_path, context, "");
    } else {
        Debugger::error(enhancedMessage, line, column, InterpretationStage::SEMANTIC, "repl", "repl", context, "");
    }
}

void TypeChecker::add_type_error(const std::string& expected, const std::string& found, int line) {
    add_error("Type mismatch: expected " + expected + ", found " + found, line);
}

std::string TypeChecker::get_code_context(int line) {
    if (current_source.empty() || line <= 0) {
        return "";
    }
    
    std::istringstream stream(current_source);
    std::string currentLine;
    int currentLineNumber = 1;
    
    // Find the target line
    while (std::getline(stream, currentLine) && currentLineNumber < line) {
        currentLineNumber++;
    }
    
    if (currentLineNumber == line) {
        return currentLine;
    }
    
    return "";
}

void TypeChecker::check_assert_call(const std::shared_ptr<LM::Frontend::AST::CallExpr>& expr) {
    if (expr->arguments.size() != 2) {
        add_error("assert() expects exactly 2 arguments: condition (bool) and message (string), got " + 
                std::to_string(expr->arguments.size()), expr->line, 0, 
                get_code_context(expr->line), "assert(...)", "assert(condition, message)");
        return;
    }
    
    // Check first argument (condition) is boolean
    TypePtr conditionType = check_expression(expr->arguments[0]);
    if (!is_boolean_type(conditionType) && conditionType->tag != TypeTag::Any) {
        add_error("assert() first argument must be boolean, got " + conditionType->toString(), 
                expr->line, 0, get_code_context(expr->line), "condition", "boolean expression");
    }
    
    // Check second argument (message) is string
    TypePtr messageType = check_expression(expr->arguments[1]);
    if (!is_string_type(messageType) && messageType->tag != TypeTag::Any) {
        add_error("assert() second argument must be string, got " + messageType->toString(), 
                expr->line, 0, get_code_context(expr->line), "message", "string literal or expression");
    }
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
    type_system.pushScope();
}

void TypeChecker::exit_scope() {
    current_scope_level--;
    if (current_scope && current_scope->parent) {
        current_scope = std::move(current_scope->parent);
    }
    type_system.popScope();
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
    // Escape analysis logic - to be updated for frames
}

bool TypeChecker::is_variable_alive(const std::string& name) {
    auto it = variable_memory_info.find(name);
    return (it != variable_memory_info.end() && 
            (it->second.memory_state == "owned" || it->second.memory_state == "borrowed"));
}

bool TypeChecker::is_visible(const std::string& frame_name, LM::Frontend::AST::VisibilityLevel visibility, int line) {
    // Public and Const are always visible
    if (visibility == LM::Frontend::AST::VisibilityLevel::Public ||
        visibility == LM::Frontend::AST::VisibilityLevel::Const) {
        return true;
    }

    // Private and Protected require being inside the frame or a subtype
    if (!current_frame) {
        return false;
    }

    // Check if we are inside the same frame
    if (current_frame->name == frame_name) {
        return true;
    }

    // Protected allows access from sub-frames (traits in this system)
    if (visibility == LM::Frontend::AST::VisibilityLevel::Protected) {
        // Find if current frame implements any trait that corresponds to the target frame
        // In this system, traits don't have fields, so protected fields are only between frames.
        // Since there's no frame inheritance yet, protected is same as private for now.
        // TODO: Implement trait-based protected access if needed
        return false;
    }

    return false;
}

void TypeChecker::mark_variable_moved(const std::string& name) {
    check_variable_move(name);
}

void TypeChecker::mark_variable_dropped(const std::string& name) {
    check_variable_drop(name);
}

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
    TypePtr return_type = type_system.STRING_TYPE; // Default
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
        TypePtr param_type = type_system.STRING_TYPE; // Default
        if (param.second) {
            param_type = resolve_type_annotation(param.second);
        }
        signature.param_types.push_back(param_type);
        signature.optional_params.push_back(false); // Required parameters are not optional
        signature.has_default_values.push_back(false); // Required parameters don't have defaults
    }
    
    // Check optional parameters
    for (const auto& optional_param : func->optionalParams) {
        TypePtr param_type = type_system.STRING_TYPE; // Default
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
    TypePtr result_type = type_system.STRING_TYPE; // if statements don't produce a value
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
    TypePtr result_type = type_system.STRING_TYPE;
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
    TypePtr result_type = type_system.STRING_TYPE;
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

TypePtr TypeChecker::check_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (!expr) return nullptr;
    
    TypePtr type = nullptr;
    
    if (auto literal = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr)) {
        type = check_literal_expr(literal);
    } else if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        type = check_call_expr(call);
    } else if (auto variable = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
        type = check_variable_expr(variable);
    } else if (auto this_expr = std::dynamic_pointer_cast<LM::Frontend::AST::ThisExpr>(expr)) {
        // Handle 'this' reference in frame methods
        if (current_frame) {
            type = type_system.createFrameType(current_frame->name);
        } else {
            add_error("'this' can only be used inside frame methods", expr->line);
            type = type_system.ANY_TYPE;
        }
    } else if (auto binary = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        type = check_binary_expr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
        type = check_unary_expr(unary);
    } else if (auto assign = std::dynamic_pointer_cast<LM::Frontend::AST::AssignExpr>(expr)) {
        type = check_assign_expr(assign);
    } else if (auto grouping = std::dynamic_pointer_cast<LM::Frontend::AST::GroupingExpr>(expr)) {
        type = check_grouping_expr(grouping);
    } else if (auto member = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr)) {
        type = check_member_expr(member);
    } else if (auto index = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
        type = check_index_expr(index);
    } else if (auto list = std::dynamic_pointer_cast<LM::Frontend::AST::ListExpr>(expr)) {
        type = check_list_expr(list);
    } else if (auto tuple = std::dynamic_pointer_cast<LM::Frontend::AST::TupleExpr>(expr)) {
        type = check_tuple_expr(tuple);
    } else if (auto dict = std::dynamic_pointer_cast<LM::Frontend::AST::DictExpr>(expr)) {
        type = check_dict_expr(dict);
    } else if (auto interpolated = std::dynamic_pointer_cast<LM::Frontend::AST::InterpolatedStringExpr>(expr)) {
        type = check_interpolated_string_expr(interpolated);
    } else if (auto lambda = std::dynamic_pointer_cast<LM::Frontend::AST::LambdaExpr>(expr)) {
        type = check_lambda_expr(lambda);
    } else if (auto error_construct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(expr)) {
        type = check_error_construct_expr(error_construct);
    } else if (auto ok_construct = std::dynamic_pointer_cast<LM::Frontend::AST::OkConstructExpr>(expr)) {
        type = check_ok_construct_expr(ok_construct);
    } else if (auto fallible = std::dynamic_pointer_cast<LM::Frontend::AST::FallibleExpr>(expr)) {
        type = check_fallible_expr(fallible);
    } else if (auto frame_inst = std::dynamic_pointer_cast<LM::Frontend::AST::FrameInstantiationExpr>(expr)) {
        type = check_frame_instantiation_expr(frame_inst);
    } else {
        add_error("Unknown expression type", expr->line);
        type = type_system.STRING_TYPE; // Default fallback
    }
    
    // Set the inferred type on the expression node
    expr->inferred_type = type;
    
    return type;
}

TypePtr TypeChecker::check_expression_with_expected_type(std::shared_ptr<LM::Frontend::AST::Expression> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    TypePtr type = nullptr;
    
    if (auto literal = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr)) {
        type = check_literal_expr_with_expected_type(literal, expected_type);
    } else if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        type = check_call_expr(call);
    } else if (auto variable = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
        type = check_variable_expr(variable);
    } else if (auto binary = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        type = check_binary_expr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
        type = check_unary_expr(unary);
    } else if (auto assign = std::dynamic_pointer_cast<LM::Frontend::AST::AssignExpr>(expr)) {
        type = check_assign_expr(assign);
    } else if (auto grouping = std::dynamic_pointer_cast<LM::Frontend::AST::GroupingExpr>(expr)) {
        type = check_grouping_expr(grouping);
    } else if (auto member = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr)) {
        type = check_member_expr(member);
    } else if (auto index = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
        type = check_index_expr(index);
    } else if (auto list = std::dynamic_pointer_cast<LM::Frontend::AST::ListExpr>(expr)) {
        type = check_list_expr(list);
    } else if (auto tuple = std::dynamic_pointer_cast<LM::Frontend::AST::TupleExpr>(expr)) {
        type = check_tuple_expr(tuple);
    } else if (auto dict = std::dynamic_pointer_cast<LM::Frontend::AST::DictExpr>(expr)) {
        type = check_dict_expr(dict);
    } else if (auto interpolated = std::dynamic_pointer_cast<LM::Frontend::AST::InterpolatedStringExpr>(expr)) {
        type = check_interpolated_string_expr(interpolated);
    } else if (auto lambda = std::dynamic_pointer_cast<LM::Frontend::AST::LambdaExpr>(expr)) {
        type = check_lambda_expr(lambda);
    } else if (auto error_construct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(expr)) {
        type = check_error_construct_expr(error_construct);
    } else if (auto ok_construct = std::dynamic_pointer_cast<LM::Frontend::AST::OkConstructExpr>(expr)) {
        type = check_ok_construct_expr(ok_construct);
    } else if (auto fallible = std::dynamic_pointer_cast<LM::Frontend::AST::FallibleExpr>(expr)) {
        type = check_fallible_expr(fallible);
    } else if (auto frame_inst = std::dynamic_pointer_cast<LM::Frontend::AST::FrameInstantiationExpr>(expr)) {
        type = check_frame_instantiation_expr(frame_inst);
    } else {
        add_error("Unknown expression type", expr->line);
        type = type_system.STRING_TYPE; // Default fallback
    }
    
    // Set the inferred type on the expression node
    expr->inferred_type = type;
    
    return type;
}

TypePtr TypeChecker::check_literal_expr(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr) {
    if (!expr) return nullptr;
    
    // Set type based on the literal value and token type
    if (std::holds_alternative<std::string>(expr->value)) {
        const std::string& str = std::get<std::string>(expr->value);
        
        // Use the token type to determine the correct type
        switch (expr->literalType) {
            case TokenType::INT_LITERAL:
                expr->inferred_type = type_system.INT64_TYPE;
                return type_system.INT64_TYPE;
                
            case TokenType::FLOAT_LITERAL:
            case TokenType::SCIENTIFIC_LITERAL:
                expr->inferred_type = type_system.FLOAT64_TYPE;
                return type_system.FLOAT64_TYPE;
                
            default:
                // Non-numeric string literal
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

TypePtr TypeChecker::check_literal_expr_with_expected_type(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    // Set type based on the literal value and token type, considering expected type
    if (std::holds_alternative<std::string>(expr->value)) {
        const std::string& str = std::get<std::string>(expr->value);
        
        // Use the token type to determine the correct type
        switch (expr->literalType) {
            case TokenType::INT_LITERAL: {
                // If we have an expected type and it's an integer type, use it
                if (expected_type && is_integer_type(expected_type)) {
                    expr->inferred_type = expected_type;
                    return expected_type;
                }
                // Otherwise, default to INT64_TYPE
                expr->inferred_type = type_system.INT64_TYPE;
                return type_system.INT64_TYPE;
            }
                
            case TokenType::FLOAT_LITERAL:
            case TokenType::SCIENTIFIC_LITERAL: {
                // If we have an expected type and it's a float type, use it
                if (expected_type && is_float_type(expected_type)) {
                    expr->inferred_type = expected_type;
                    return expected_type;
                }
                // Otherwise, default to FLOAT64_TYPE
                expr->inferred_type = type_system.FLOAT64_TYPE;
                return type_system.FLOAT64_TYPE;
            }
                
            default:
                // Non-numeric string literal
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

TypePtr TypeChecker::check_variable_expr(std::shared_ptr<LM::Frontend::AST::VariableExpr> expr) {
    if (!expr) return nullptr;

    // Check for module alias access (e.g., math in math.add)
    if (import_aliases.count(expr->name)) {
        TypePtr type = type_system.createFrameType(expr->name);
        expr->inferred_type = type;
        return type;
    }

    // Check if it's an imported frame or function name (without prefix)
    auto it = current_program_->imported_symbols.find(expr->name);
    if (it != current_program_->imported_symbols.end()) {
        if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(it->second)) {
            TypePtr type = type_system.createFrameType(expr->name);
            expr->inferred_type = type;
            return type;
        }
    }
    
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

TypePtr TypeChecker::check_binary_expr(std::shared_ptr<LM::Frontend::AST::BinaryExpr> expr) {
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

TypePtr TypeChecker::check_unary_expr(std::shared_ptr<LM::Frontend::AST::UnaryExpr> expr) {
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
            // Numeric negation/affirmation
            if (!is_numeric_type(right_type)) {
                add_type_error("numeric", right_type->toString(), expr->line);
            }
            
            // Special case: Handle large integers that were parsed as float due to overflow
            // but should be integers when negated (e.g., -9223372036854775808 = INT64_MIN)
            if (expr->op == TokenType::MINUS && right_type->tag == TypeTag::Float64) {
                if (auto literal = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr->right)) {
                    if (std::holds_alternative<std::string>(literal->value)) {
                        const std::string& str = std::get<std::string>(literal->value);
                        
                        // Only apply this fix to pure integers (no decimal point or scientific notation)
                        bool hasDecimal = str.find('.') != std::string::npos;
                        bool hasScientific = str.find('e') != std::string::npos || str.find('E') != std::string::npos;
                        
                        if (!hasDecimal && !hasScientific) {
                            // Try to parse as unsigned long long to check the range
                            try {
                                unsigned long long value = std::stoull(str);
                                
                                // Check if this value, when negated, fits in int64 range
                                // INT64_MAX = 9223372036854775807
                                // INT64_MIN = -9223372036854775808 (which is INT64_MAX + 1)
                                const unsigned long long INT64_MAX_PLUS_1 = 9223372036854775808ULL;
                                
                                if (value <= INT64_MAX_PLUS_1) {
                                    // This negative value fits in int64
                                    // Update both the type and mark this as an integer literal
                                    literal->inferred_type = type_system.INT64_TYPE;
                                    expr->inferred_type = type_system.INT64_TYPE;
                                    
                                    // Also update the literal's value to ensure it's treated as integer
                                    // Store the negative value as a string to preserve the integer nature
                                    literal->value = "-" + str;
                                    
                                    return type_system.INT64_TYPE;
                                }
                                
                                // Check if it fits in int128 range (for very large numbers)
                                // For now, we'll be conservative and only handle int64 range
                                // Future: could extend to int128 if needed
                                
                            } catch (const std::exception&) {
                                // If parsing fails, keep as float
                            }
                        }
                    }
                }
            }
            expr->inferred_type = right_type;
            return right_type;
            
        default:
            add_error("Unsupported unary operator", expr->line);
            return right_type;
    }
}

TypePtr TypeChecker::check_call_expr(std::shared_ptr<LM::Frontend::AST::CallExpr> expr) {
    if (!expr) return nullptr;
    
    // Check positional arguments first
    std::vector<TypePtr> arg_types;
    for (const auto& arg : expr->arguments) {
        arg_types.push_back(check_expression(arg));
    }
    
    // Check if callee is a variable (could be function or frame name)
    if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->callee)) {
        // Check if it's a frame instantiation
        auto frame_it = frame_declarations.find(var_expr->name);
        if (frame_it == frame_declarations.end()) {
            // Try lookup in imported symbols
            auto it = current_program_->imported_symbols.find(var_expr->name);
            if (it != current_program_->imported_symbols.end()) {
                 if (std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(it->second)) {
                     frame_it = frame_declarations.find(var_expr->name);
                 }
            }
        }

        if (frame_it != frame_declarations.end()) {
            const FrameInfo& frame_info = frame_it->second;
            std::string init_name = var_expr->name + ".init";
            auto sig_it = function_signatures.find(init_name);

            // Validate named arguments against both init parameters AND fields
            for (const auto& [arg_name, value] : expr->namedArgs) {
                bool matched = false;
                TypePtr target_type = nullptr;

                // 1. Check init parameters
                if (frame_info.declaration && frame_info.declaration->init) {
                    const auto& init = frame_info.declaration->init;
                    for (const auto& p : init->parameters) {
                        if (p.first == arg_name) { target_type = resolve_type_annotation(p.second); matched = true; break; }
                    }
                    if (!matched) {
                        for (const auto& op : init->optionalParams) {
                            if (op.first == arg_name) { target_type = resolve_type_annotation(op.second.first); matched = true; break; }
                        }
                    }
                }

                // 2. Check fields if not matched in init
                if (!matched) {
                    for (const auto& field : frame_info.fields) {
                        if (field.first == arg_name) { target_type = field.second; matched = true; break; }
                    }
                }

                if (matched) {
                    TypePtr val_type = check_expression(value);
                    if (!is_type_compatible(target_type, val_type)) add_type_error(target_type->toString(), val_type->toString(), expr->line);
                } else {
                    add_error("Frame '" + var_expr->name + "' has no field or init parameter named '" + arg_name + "'", expr->line);
                }
            }

            // Validate positional arguments (passing to init)
            if (!expr->arguments.empty() || sig_it != function_signatures.end()) {
                if (sig_it == function_signatures.end()) {
                    if (!expr->arguments.empty()) add_error("Frame '" + var_expr->name + "' has no init() method to accept positional arguments", expr->line);
                } else {
                    std::vector<TypePtr> expected_params = sig_it->second.param_types;
                    if (!expected_params.empty()) expected_params.erase(expected_params.begin()); // skip 'this'

                    // Count how many required parameters are satisfied by named arguments
                    size_t satisfied_by_named = 0;
                    size_t required_count = 0;
                    if (frame_info.declaration && frame_info.declaration->init) {
                        const auto& init = frame_info.declaration->init;
                        required_count = init->parameters.size();
                        for (size_t i = 0; i < required_count; ++i) {
                            if (expr->namedArgs.count(init->parameters[i].first)) satisfied_by_named++;
                        }
                    } else {
                        required_count = expected_params.size(); // Fallback
                    }

                    if (expr->arguments.size() + satisfied_by_named < required_count) {
                         // Only error if we actually HAVE positional arguments,
                         // otherwise let's assume it's direct field initialization if it matches.
                         if (!expr->arguments.empty()) {
                             add_error("Frame '" + var_expr->name + "' init method requires " + std::to_string(required_count) + " arguments, but only " +
                                      std::to_string(expr->arguments.size() + satisfied_by_named) + " were provided", expr->line);
                         }
                    }
                }
            }

            TypePtr frame_type = type_system.createFrameType(var_expr->name);
            expr->inferred_type = frame_type;
            return frame_type;
        }

        // Check if it's a function call
        TypePtr result_type = nullptr;
        if (check_function_call(var_expr->name, arg_types, result_type)) {
            expr->inferred_type = result_type;
            return result_type;
        }
    }
    
    // Check if callee is a member expression (method call or module function call)
    if (auto member_expr = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr->callee)) {
        // Check if this is a module member access (e.g., math.add)
        if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(member_expr->object)) {
            std::string qualified_name = var_expr->name + "." + member_expr->name;

            // 1. Check if it's a frame instantiation (e.g., oop.Person())
            auto frame_it = frame_declarations.find(qualified_name);
            if (frame_it != frame_declarations.end()) {
                const FrameInfo& frame_info = frame_it->second;
                std::string init_name = qualified_name + ".init";
                auto sig_it = function_signatures.find(init_name);

                // Validate named arguments against both init parameters AND fields
                for (const auto& [arg_name, value] : expr->namedArgs) {
                    bool matched = false;
                    TypePtr target_type = nullptr;

                    if (frame_info.declaration && frame_info.declaration->init) {
                        const auto& init = frame_info.declaration->init;
                        for (const auto& p : init->parameters) {
                            if (p.first == arg_name) { target_type = resolve_type_annotation(p.second); matched = true; break; }
                        }
                        if (!matched) {
                            for (const auto& op : init->optionalParams) {
                                if (op.first == arg_name) { target_type = resolve_type_annotation(op.second.first); matched = true; break; }
                            }
                        }
                    }

                    if (!matched) {
                        for (const auto& field : frame_info.fields) {
                            if (field.first == arg_name) { target_type = field.second; matched = true; break; }
                        }
                    }

                    if (matched) {
                        TypePtr val_type = check_expression(value);
                        if (!is_type_compatible(target_type, val_type)) add_type_error(target_type->toString(), val_type->toString(), expr->line);
                    } else {
                        add_error("Frame '" + qualified_name + "' has no field or init parameter named '" + arg_name + "'", expr->line);
                    }
                }

                // Validate positional arguments (passing to init)
                if (!expr->arguments.empty() || sig_it != function_signatures.end()) {
                    if (sig_it == function_signatures.end()) {
                        if (!expr->arguments.empty()) add_error("Frame '" + qualified_name + "' has no init() method to accept positional arguments", expr->line);
                    } else {
                        std::vector<TypePtr> expected_params = sig_it->second.param_types;
                        if (!expected_params.empty()) expected_params.erase(expected_params.begin()); // skip 'this'

                        size_t satisfied_by_named = 0;
                        size_t required_count = 0;
                        if (frame_info.declaration && frame_info.declaration->init) {
                            const auto& init = frame_info.declaration->init;
                            required_count = init->parameters.size();
                            for (size_t i = 0; i < required_count; ++i) {
                                if (expr->namedArgs.count(init->parameters[i].first)) satisfied_by_named++;
                            }
                        } else {
                            required_count = expected_params.size();
                        }

                        if (expr->arguments.size() + satisfied_by_named < required_count) {
                             if (!expr->arguments.empty()) {
                                 add_error("Frame '" + qualified_name + "' init method requires " + std::to_string(required_count) + " arguments, but only " +
                                          std::to_string(expr->arguments.size() + satisfied_by_named) + " were provided", expr->line);
                             }
                        }
                    }
                }
                TypePtr frame_type = type_system.createFrameType(qualified_name);
                expr->inferred_type = frame_type;
                return frame_type;
            }

            // 2. Check if it's a module function
            auto sig_it = function_signatures.find(qualified_name);
            if (sig_it == function_signatures.end()) {
                // Try dotted name without :: if LIR generator use .
                sig_it = function_signatures.find(var_expr->name + "." + member_expr->name);
            }
            if (sig_it != function_signatures.end()) {
                validate_argument_types(sig_it->second.param_types, arg_types, qualified_name);
                expr->inferred_type = sig_it->second.return_type;
                return sig_it->second.return_type;
            }

            // 3. Fallback for module alias
            auto alias_it = import_aliases.find(var_expr->name);
            if (alias_it != import_aliases.end()) {
                std::string full_name = alias_it->second + "." + member_expr->name;
                auto sig_it2 = function_signatures.find(full_name);
                if (sig_it2 != function_signatures.end()) {
                    validate_argument_types(sig_it2->second.param_types, arg_types, full_name);
                    expr->inferred_type = sig_it2->second.return_type;
                    return sig_it2->second.return_type;
                }
                add_error("Module '" + alias_it->second + "' has no member '" + member_expr->name + "'", expr->line);
                return type_system.ANY_TYPE;
            }
        }
        
        // Get the object type
        TypePtr object_type = check_expression(member_expr->object);
        
        // Handle frame method calls
        if (object_type && object_type->tag == TypeTag::Frame) {
            // Get the frame name from the FrameType
            auto frameTypeData = std::get_if<FrameType>(&object_type->extra);
            if (!frameTypeData) {
                add_error("Invalid frame type", expr->line);
                return type_system.ANY_TYPE;
            }
            
            std::string frame_name = frameTypeData->name;
            std::string method_name = member_expr->name;
            
            // Look up the frame declaration
            auto frame_it = frame_declarations.find(frame_name);
            if (frame_it == frame_declarations.end()) {
                add_error("Unknown frame type: " + frame_name, expr->line);
                return type_system.ANY_TYPE;
            }
            
            const FrameInfo& frame_info = frame_it->second;
            
            // Find the method in the frame
            std::shared_ptr<LM::Frontend::AST::FrameMethod> method = nullptr;
            for (const auto& m : frame_info.declaration->methods) {
                if (m->name == method_name) {
                    method = m;
                    break;
                }
            }
            
            // Check init and deinit methods
            if (!method && method_name == "init") {
                method = frame_info.declaration->init;
            }
            if (!method && method_name == "deinit") {
                method = frame_info.declaration->deinit;
            }
            
            if (!method) {
                // Not found in frame, check implemented traits recursively
                std::vector<std::string> trait_worklist = frame_info.declaration->implements;
                std::unordered_set<std::string> visited_traits;

                while (!trait_worklist.empty()) {
                    std::string current_trait = trait_worklist.back();
                    trait_worklist.pop_back();

                    if (visited_traits.count(current_trait)) continue;
                    visited_traits.insert(current_trait);

                    auto trait_it = trait_declarations.find(current_trait);
                    if (trait_it != trait_declarations.end()) {
                        for (const auto& tm : trait_it->second.declaration->methods) {
                            if (tm->name == method_name) {
                                // Found in trait hierarchy (static dispatch)
                                TypePtr trait_return_type = tm->returnType ? resolve_type_annotation(tm->returnType.value()) : type_system.NIL_TYPE;
                                expr->inferred_type = trait_return_type;
                                return trait_return_type;
                            }
                        }
                        // Add parent traits to worklist
                        for (const auto& parent : trait_it->second.extends) {
                            trait_worklist.push_back(parent);
                        }
                    }
                }

                add_error("Frame '" + frame_name + "' has no method '" + method_name + "'", expr->line);
                return type_system.ANY_TYPE;
            }
            
            // Check visibility
            if (!is_visible(frame_name, method->visibility, expr->line)) {
                add_error("Cannot access " + LM::Frontend::AST::visibilityToString(method->visibility) +
                         " method '" + method_name + "' of frame '" + frame_name + "'", expr->line);
            }
            
            // Check parameter count and types
            size_t required_params = method->parameters.size();
            size_t optional_params = method->optionalParams.size();
            size_t total_params = required_params + optional_params;
            size_t provided_args = arg_types.size();
            
            if (provided_args < required_params) {
                add_error("Method '" + method_name + "' requires " + std::to_string(required_params) + 
                         " arguments, but " + std::to_string(provided_args) + " were provided", expr->line);
            } else if (provided_args > total_params) {
                add_error("Method '" + method_name + "' accepts at most " + std::to_string(total_params) + 
                         " arguments, but " + std::to_string(provided_args) + " were provided", expr->line);
            }
            
            // Check parameter types
            for (size_t i = 0; i < std::min(provided_args, total_params); ++i) {
                TypePtr expected_type = nullptr;
                if (i < required_params) {
                    expected_type = resolve_type_annotation(method->parameters[i].second);
                } else {
                    expected_type = resolve_type_annotation(method->optionalParams[i - required_params].second.first);
                }
                
                if (!is_type_compatible(expected_type, arg_types[i])) {
                    add_type_error(expected_type->toString(), arg_types[i]->toString(), expr->line);
                }
            }
            
            // Return the method's return type
            if (method->returnType) {
                TypePtr return_type = resolve_type_annotation(method->returnType);
                expr->inferred_type = return_type;
                return return_type;
            } else {
                expr->inferred_type = type_system.NIL_TYPE;
                return type_system.NIL_TYPE;
            }
        }
        
        // For other types, just check the member expression
        TypePtr result_type = check_expression(expr->callee);
        if (result_type) {
            expr->inferred_type = result_type;
            return result_type;
        }
    }
    
    // If not a known function, check the callee as an expression
    TypePtr callee_type = check_expression(expr->callee);
    
    add_error("Cannot call non-function value", expr->line);
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_assign_expr(std::shared_ptr<LM::Frontend::AST::AssignExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr value_type = check_expression(expr->value);
    
    // Handle member assignment (e.g., obj.field = value)
    if (expr->object && expr->member) {
        TypePtr object_type = check_expression(expr->object);
        
        // Handle frame field assignment
        if (object_type && object_type->tag == TypeTag::Frame) {
            // Get the frame name from the FrameType
            auto frameTypeData = std::get_if<FrameType>(&object_type->extra);
            if (!frameTypeData) {
                add_error("Invalid frame type", expr->line);
                return value_type;
            }
            
            std::string frame_name = frameTypeData->name;
            std::string field_name = *expr->member;
            
            // Look up the frame declaration
            auto frame_it = frame_declarations.find(frame_name);
            if (frame_it == frame_declarations.end()) {
                add_error("Unknown frame type: " + frame_name, expr->line);
                return value_type;
            }
            
            const FrameInfo& frame_info = frame_it->second;
            
            // Find the field
            TypePtr field_type = nullptr;
            for (const auto& [fname, ftype] : frame_info.fields) {
                if (fname == field_name) {
                    field_type = ftype;
                    break;
                }
            }
            
            if (!field_type) {
                add_error("Frame '" + frame_name + "' has no field '" + field_name + "'", expr->line);
                return value_type;
            }
            
            // Check visibility
            // TODO: Implement proper visibility checking based on context
            
            // Check type compatibility
            if (!is_type_compatible(field_type, value_type)) {
                add_type_error(field_type->toString(), value_type->toString(), expr->line);
            }
            
            return value_type;
        }
        
        // For other types, just return the value type
        return value_type;
    }
    
    // Handle index assignment (e.g., arr[0] = value)
    if (expr->object && expr->index) {
        // Just check the object and index expressions
        check_expression(expr->object);
        check_expression(expr->index);
        return value_type;
    }
    
    // For simple variable assignment
    if (!expr->object && !expr->member && !expr->index) {
        TypePtr var_type = lookup_variable(expr->name);
        if (var_type) {
            if (!is_type_compatible(var_type, value_type) && 
                !(is_string_type(var_type) && is_string_type(value_type))) {
                add_type_error(var_type->toString(), value_type->toString(), expr->line);
            }
            
            // Check if we're assigning from another variable (create reference or move)
            if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->value)) {
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

TypePtr TypeChecker::check_grouping_expr(std::shared_ptr<LM::Frontend::AST::GroupingExpr> expr) {
    if (!expr) return nullptr;
    return check_expression(expr->expression);
}

TypePtr TypeChecker::check_member_expr(std::shared_ptr<LM::Frontend::AST::MemberExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr object_type = check_expression(expr->object);
    
    // Handle channel method access
    if (object_type && object_type->tag == TypeTag::Channel) {
        std::string method_name = expr->name;
        
        // Return appropriate types for channel methods
        if (method_name == "offer") {
            return type_system.BOOL_TYPE; // offer() returns bool
        } else if (method_name == "poll") {
            return type_system.ANY_TYPE; // poll() returns Option<T> (represented as any for now)
        } else if (method_name == "send") {
            return type_system.NIL_TYPE; // send() returns nil
        } else if (method_name == "recv") {
            return type_system.ANY_TYPE; // recv() returns T
        } else if (method_name == "close") {
            return type_system.NIL_TYPE; // close() returns nil
        } else {
            add_error("Unknown channel method: " + method_name, expr->line);
            return type_system.ANY_TYPE;
        }
    }
    
    // Handle frame member access
    if (object_type && object_type->tag == TypeTag::Frame) {
        // Get the frame name from the FrameType
        auto frameTypeData = std::get_if<FrameType>(&object_type->extra);
        if (!frameTypeData) {
            add_error("Invalid frame type", expr->line);
            return type_system.ANY_TYPE;
        }
        
        std::string frame_name = frameTypeData->name;
        std::string member_name = expr->name;
        
        // Look up the frame declaration
        auto frame_it = frame_declarations.find(frame_name);
        if (frame_it == frame_declarations.end()) {
            add_error("Unknown frame type: " + frame_name, expr->line);
            return type_system.ANY_TYPE;
        }
        
        const FrameInfo& frame_info = frame_it->second;
        
        // Check if this is a module alias access
        if (import_aliases.count(frame_name)) {
            std::string qualified_name = frame_name + "." + member_name;
            TypePtr member_type = lookup_variable(qualified_name);
            if (member_type && member_type->tag != TypeTag::Nil) {
                expr->inferred_type = member_type;
                return member_type;
            }
            // Check for functions
            if (function_signatures.count(qualified_name)) {
                expr->inferred_type = type_system.FUNCTION_TYPE;
                return type_system.FUNCTION_TYPE;
            }
        }

        if (!frame_info.declaration) {
            // If it's a module alias, we shouldn't fail if we just haven't found the member yet
            // but we should have found it if it exists.
            if (import_aliases.count(frame_name)) {
                add_error("Module '" + frame_name + "' has no member '" + member_name + "'", expr->line);
            } else {
                add_error("Invalid frame declaration for " + frame_name, expr->line);
            }
            return type_system.ANY_TYPE;
        }

        // Check if member is a field
        for (const auto& [field_name, field_type] : frame_info.fields) {
            if (field_name == member_name) {
                // Check visibility
                // Find the field in the frame declaration to get visibility
                for (const auto& field : frame_info.declaration->fields) {
                    if (field->name == member_name) {
                        if (!is_visible(frame_name, field->visibility, expr->line)) {
                            add_error("Cannot access " + LM::Frontend::AST::visibilityToString(field->visibility) +
                                     " field '" + member_name + "' of frame '" + frame_name + "'", expr->line);
                        }
                        expr->inferred_type = field_type;
                        return field_type;
                    }
                }
            }
        }
        
        // Check if member is a method
        for (const auto& method : frame_info.declaration->methods) {
            if (method->name == member_name) {
                // Check visibility
                if (!is_visible(frame_name, method->visibility, expr->line)) {
                    add_error("Cannot access " + LM::Frontend::AST::visibilityToString(method->visibility) +
                             " method '" + member_name + "' of frame '" + frame_name + "'", expr->line);
                }
                
                // Return the method's return type
                if (method->returnType) {
                    TypePtr return_type = resolve_type_annotation(method->returnType);
                    expr->inferred_type = return_type;
                    return return_type;
                } else {
                    // Method has no explicit return type, assume nil
                    expr->inferred_type = type_system.NIL_TYPE;
                    return type_system.NIL_TYPE;
                }
            }
        }
        
        // Check init and deinit methods
        if (member_name == "init" && frame_info.declaration->init) {
            if (frame_info.declaration->init->returnType) {
                TypePtr return_type = resolve_type_annotation(frame_info.declaration->init->returnType);
                expr->inferred_type = return_type;
                return return_type;
            } else {
                expr->inferred_type = type_system.NIL_TYPE;
                return type_system.NIL_TYPE;
            }
        }
        
        if (member_name == "deinit" && frame_info.declaration->deinit) {
            expr->inferred_type = type_system.NIL_TYPE;
            return type_system.NIL_TYPE;
        }
        
        // Member not found
        add_error("Frame '" + frame_name + "' has no member '" + member_name + "'", expr->line);
        return type_system.ANY_TYPE;
    }
    
    // For now, assume all other member access returns string
    // TODO: Implement proper class/struct type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_index_expr(std::shared_ptr<LM::Frontend::AST::IndexExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr object_type = check_expression(expr->object);
    TypePtr index_type = check_expression(expr->index);
    
    // For now, assume all indexing returns string
    // TODO: Implement proper collection type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_list_expr(std::shared_ptr<LM::Frontend::AST::ListExpr> expr) {
    if (!expr) return nullptr;
    
    if (expr->elements.empty()) {
        // Empty list - return generic list type
        return type_system.createTypedListType(type_system.ANY_TYPE);
    }
    
    // Check all elements and infer common element type
    std::vector<TypePtr> elementTypes;
    for (const auto& elem : expr->elements) {
        TypePtr elemType = check_expression(elem);
        elementTypes.push_back(elemType);
    }
    
    // Find common type for all elements
    TypePtr commonElementType = elementTypes[0];
    for (size_t i = 1; i < elementTypes.size(); ++i) {
        try {
            commonElementType = get_common_type(commonElementType, elementTypes[i]);
        } catch (const std::exception& e) {
            add_error("Inconsistent element types in list literal: cannot mix " + 
                    commonElementType->toString() + " and " + elementTypes[i]->toString() + 
                    ": " + e.what(), expr->line);
            return type_system.createTypedListType(type_system.ANY_TYPE);
        }
    }
    
    TypePtr listType = type_system.createTypedListType(commonElementType);
    expr->inferred_type = listType;
    return listType;
}

TypePtr TypeChecker::check_tuple_expr(std::shared_ptr<LM::Frontend::AST::TupleExpr> expr) {
    if (!expr) return nullptr;
    
    // Check all elements and collect their types
    std::vector<TypePtr> elementTypes;
    for (const auto& elem : expr->elements) {
        TypePtr elemType = check_expression(elem);
        elementTypes.push_back(elemType);
    }
    
    // Create tuple type with the element types
    TypePtr tupleType = type_system.createTupleType(elementTypes);
    expr->inferred_type = tupleType;
    return tupleType;
}

TypePtr TypeChecker::check_dict_expr(std::shared_ptr<LM::Frontend::AST::DictExpr> expr) {
    if (!expr) return nullptr;
    
    if (expr->entries.empty()) {
        // Empty dictionary - return generic dict type
        return type_system.createTypedDictType(type_system.STRING_TYPE, type_system.ANY_TYPE);
    }
    
    // Check all entries and infer common key and value types
    std::vector<TypePtr> keyTypes;
    std::vector<TypePtr> valueTypes;
    
    for (const auto& [keyExpr, valueExpr] : expr->entries) {
        TypePtr keyType = check_expression(keyExpr);
        TypePtr valueType = check_expression(valueExpr);
        keyTypes.push_back(keyType);
        valueTypes.push_back(valueType);
    }
    
    // Find common types for keys and values
    TypePtr commonKeyType = keyTypes[0];
    TypePtr commonValueType = valueTypes[0];
    
    for (size_t i = 1; i < keyTypes.size(); ++i) {
        try {
            commonKeyType = get_common_type(commonKeyType, keyTypes[i]);
        } catch (const std::exception& e) {
            add_error("Inconsistent key types in dictionary literal: cannot mix " + 
                    commonKeyType->toString() + " and " + keyTypes[i]->toString() + 
                    ": " + e.what(), expr->line);
            return type_system.createTypedDictType(type_system.STRING_TYPE, type_system.ANY_TYPE);
        }
    }
    
    for (size_t i = 1; i < valueTypes.size(); ++i) {
        try {
            commonValueType = get_common_type(commonValueType, valueTypes[i]);
        } catch (const std::exception& e) {
            add_error("Inconsistent value types in dictionary literal: cannot mix " + 
                    commonValueType->toString() + " and " + valueTypes[i]->toString() + 
                    ": " + e.what(), expr->line);
            return type_system.createTypedDictType(commonKeyType, type_system.ANY_TYPE);
        }
    }
    
    TypePtr dictType = type_system.createTypedDictType(commonKeyType, commonValueType);
    expr->inferred_type = dictType;
    return dictType;
}

TypePtr TypeChecker::check_interpolated_string_expr(std::shared_ptr<LM::Frontend::AST::InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& part : expr->parts) {
        if (std::holds_alternative<std::shared_ptr<LM::Frontend::AST::Expression>>(part)) {
            check_expression(std::get<std::shared_ptr<LM::Frontend::AST::Expression>>(part));
        }
    }
    
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_lambda_expr(std::shared_ptr<LM::Frontend::AST::LambdaExpr> expr) {
    if (!expr) return nullptr;
    
    // Create new scope for lambda parameters
    enter_scope();
    
    // Process parameters and add them to scope
    std::vector<TypePtr> paramTypes;
    for (const auto& param : expr->params) {
        TypePtr paramType = type_system.ANY_TYPE;
        if (param.second) {
            paramType = resolve_type_annotation(param.second);
        }
        paramTypes.push_back(paramType);
        declare_variable(param.first, paramType);
    }
    
    // Determine return type
    TypePtr returnType = type_system.ANY_TYPE;
    if (expr->returnType.has_value()) {
        returnType = resolve_type_annotation(expr->returnType.value());
    } else {
        // Enhanced return type inference from lambda body
        returnType = infer_lambda_return_type(expr->body);
    }
    
    // Set up function context for lambda
    auto prevFunction = current_function;
    auto prevReturnType = current_return_type;
    
    // Create a temporary function signature for the lambda
    FunctionSignature lambdaSignature;
    lambdaSignature.name = "<lambda>";
    lambdaSignature.param_types = paramTypes;
    lambdaSignature.return_type = returnType;
    lambdaSignature.can_fail = false;
    lambdaSignature.error_types = {};
    
    current_function = nullptr; // Lambdas don't have function declarations
    current_return_type = returnType;
    
    // Check lambda body
    TypePtr bodyType = check_statement(expr->body);
    
    // Restore previous context
    current_function = prevFunction;
    current_return_type = prevReturnType;
    
    exit_scope(); // Exit lambda scope
    
    // Create and return function type
    TypePtr functionType = type_system.createFunctionType(paramTypes, returnType);
    expr->inferred_type = functionType;
    return functionType;
}

TypePtr TypeChecker::check_error_construct_expr(std::shared_ptr<LM::Frontend::AST::ErrorConstructExpr> expr) {
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

TypePtr TypeChecker::check_ok_construct_expr(std::shared_ptr<LM::Frontend::AST::OkConstructExpr> expr) {
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

TypePtr TypeChecker::check_fallible_expr(std::shared_ptr<LM::Frontend::AST::FallibleExpr> expr) {
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

TypePtr TypeChecker::resolve_type_annotation(std::shared_ptr<LM::Frontend::AST::TypeAnnotation> annotation) {
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
    
    // Check if getType returned NIL_TYPE (which means type not found)
    if (base_type && base_type->tag == TypeTag::Nil) {
        // Type not found, try type alias
        base_type = type_system.getTypeAlias(annotation->typeName);
    }
    
    if (!base_type || base_type->tag == TypeTag::Nil) {
        // Handle special cases that might not be in the type system yet
        if (annotation->typeName == "atomic") {
            // atomic is an alias for i64
            base_type = type_system.INT64_TYPE;
        } else if (annotation->typeName == "channel") {
            // channel type is represented as any (channel handle)
            base_type = type_system.ANY_TYPE;
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
    
    // Handle refinement types (e.g., int where value > 0)
    if (annotation->isRefined && annotation->refinementCondition) {
        // Create new scope to avoid polluting outer scope with 'value'
        enter_scope();
        // Bind 'value' to the base type for condition checking
        declare_variable("value", base_type);

        // Check the refinement condition
        TypePtr conditionType = check_expression(annotation->refinementCondition);
        if (!is_boolean_type(conditionType)) {
            add_error("Refinement condition must be boolean, got " + conditionType->toString(), annotation->refinementCondition->line);
        }

        exit_scope();

        RefinedType refined;
        refined.baseType = base_type;
        refined.condition = annotation->refinementCondition;
        base_type = std::make_shared<::Type>(TypeTag::Refined, refined);
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
    if (!expected || !actual) return false;

    // Handle refinement types
    if (expected->tag == TypeTag::Refined) {
        if (const auto* refined = std::get_if<RefinedType>(&expected->extra)) {
            // A refined type is compatible if the base types are compatible
            // In a full implementation, we'd also need to check the condition.
            return is_type_compatible(refined->baseType, actual);
        }
    }

    if (actual->tag == TypeTag::Refined) {
        if (const auto* refined = std::get_if<RefinedType>(&actual->extra)) {
            return is_type_compatible(expected, refined->baseType);
        }
    }

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
    // Get function signature to check optional parameters
    auto func_it = function_signatures.find(func_name);
    if (func_it == function_signatures.end()) {
        return false;
    }
    
    const FunctionSignature& sig = func_it->second;
    auto func_decl = sig.declaration;
    
    if (!func_decl) {
        // Fallback to strict checking if we don't have declaration
        if (expected.size() != actual.size()) {
            add_error("Function " + func_name + " expects " + 
                     std::to_string(expected.size()) + " arguments, got " + 
                     std::to_string(actual.size()));
            return false;
        }
    } else {
        // Check argument count considering optional parameters
        size_t min_args = 0; // Count required parameters
        size_t max_args = expected.size(); // All parameters
        
        // Count required vs optional parameters
        for (size_t i = 0; i < sig.optional_params.size() && i < expected.size(); ++i) {
            if (!sig.optional_params[i]) {
                min_args++; // This is a required parameter
            }
        }
        
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

bool TypeChecker::is_integer_type(TypePtr type) {
    return type && (type->tag == TypeTag::Int || type->tag == TypeTag::Int8 || 
                   type->tag == TypeTag::Int16 || type->tag == TypeTag::Int32 || 
                   type->tag == TypeTag::Int64 || type->tag == TypeTag::Int128 ||
                   type->tag == TypeTag::UInt || type->tag == TypeTag::UInt8 || 
                   type->tag == TypeTag::UInt16 || type->tag == TypeTag::UInt32 || 
                   type->tag == TypeTag::UInt64 || type->tag == TypeTag::UInt128);
}

bool TypeChecker::is_float_type(TypePtr type) {
    return type && (type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64);
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

bool TypeChecker::is_optional_type(TypePtr type) {
    if (!type || type->tag != TypeTag::ErrorUnion) {
        return false;
    }
    
    // Both optional types (str?) and fallible types (int?DivisionByZero) 
    // should be allowed in if conditions for null/error checking
    auto* errorUnionPtr = std::get_if<ErrorUnionType>(&type->extra);
    if (!errorUnionPtr) {
        throw std::runtime_error("Missing ErrorUnionType data in ErrorUnion type");
    }
    auto& errorUnion = *errorUnionPtr;
    
    // Optional types: empty error types and marked as generic (str?)
    bool isOptional = errorUnion.errorTypes.empty() && errorUnion.isGenericError;
    
    // Fallible types: have specific error types (int?DivisionByZero)
    bool isFallible = !errorUnion.errorTypes.empty();
    
    return isOptional || isFallible;
}

bool TypeChecker::is_error_union_type(TypePtr type) {
    return type && type->tag == TypeTag::ErrorUnion;
}

bool TypeChecker::is_union_type(TypePtr type) {
    return type && type->tag == TypeTag::Union;
}

bool TypeChecker::requires_error_handling(TypePtr type) {
    return is_error_union_type(type);
}

TypePtr TypeChecker::promote_numeric_types(TypePtr left, TypePtr right) {
    return get_common_type(left, right);
}

// =============================================================================
// ADVANCED ERROR HANDLING METHODS
// =============================================================================

void TypeChecker::validate_function_error_types(const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& stmt) {
    // Validate consistency between return type and declared error types
    if (stmt->returnType && *stmt->returnType) {
        auto returnType = resolve_type_annotation(*stmt->returnType);
        
        if (is_error_union_type(returnType)) {
            auto* errorUnionPtr = std::get_if<ErrorUnionType>(&returnType->extra);
            if (!errorUnionPtr) {
                throw std::runtime_error("Missing ErrorUnionType data in ErrorUnion type");
            }
            auto& errorUnion = *errorUnionPtr;
            
            // If function declares specific error types, they should match return type
            if (stmt->canFail && !stmt->declaredErrorTypes.empty()) {
                // Check that declared error types match return type error types
                if (!errorUnion.isGenericError) {
                    for (const auto& declaredError : stmt->declaredErrorTypes) {
                        if (std::find(errorUnion.errorTypes.begin(), errorUnion.errorTypes.end(), declaredError) == errorUnion.errorTypes.end()) {
                            add_error("Function '" + stmt->name + "' declares error type '" + declaredError + 
                                    "' but return type does not include this error type", stmt->line);
                        }
                    }
                    
                    for (const auto& returnError : errorUnion.errorTypes) {
                        if (std::find(stmt->declaredErrorTypes.begin(), stmt->declaredErrorTypes.end(), returnError) == stmt->declaredErrorTypes.end()) {
                            add_error("Function '" + stmt->name + "' return type includes error type '" + returnError + 
                                    "' but it is not declared in function signature", stmt->line);
                        }
                    }
                }
            }
        } else if (stmt->canFail) {
            // Function declares it can fail but return type is not an error union
            add_error("Function '" + stmt->name + "' declares 'throws' but return type is not an error union type", stmt->line);
        }
    } else if (stmt->canFail) {
        // Function declares it can fail but has no return type annotation
        add_error("Function '" + stmt->name + "' declares 'throws' but has no return type annotation. " +
                "Use 'Type?' for generic errors or 'Type?ErrorType1,ErrorType2' for specific error types", stmt->line);
    }
}

void TypeChecker::validate_function_body_error_types(const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& stmt) {
    if (!stmt->canFail) {
        return; // No error type validation needed for non-fallible functions
    }
    
    // Infer error types that function body can actually produce
    std::vector<std::string> inferredErrorTypes = infer_function_error_types(stmt->body);
    
    // If function declares specific error types, validate they can be produced
    if (!stmt->declaredErrorTypes.empty()) {
        for (const auto& declaredError : stmt->declaredErrorTypes) {
            if (!can_function_produce_error_type(stmt->body, declaredError)) {
                add_error("Function '" + stmt->name + "' declares error type '" + declaredError + 
                        "' but function body cannot produce this error type", stmt->line);
            }
        }
        
        // Check for undeclared error types that body might produce
        for (const auto& inferredError : inferredErrorTypes) {
            if (std::find(stmt->declaredErrorTypes.begin(), stmt->declaredErrorTypes.end(), inferredError) == stmt->declaredErrorTypes.end()) {
                add_error("Function '" + stmt->name + "' body can produce error type '" + inferredError + 
                        "' but it is not declared in function signature", stmt->line);
            }
        }
    }
}

std::vector<std::string> TypeChecker::infer_function_error_types(const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    std::vector<std::string> errorTypes;
    
    if (auto blockStmt = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        for (const auto& stmt : blockStmt->statements) {
            auto stmtErrors = infer_function_error_types(stmt);
            errorTypes.insert(errorTypes.end(), stmtErrors.begin(), stmtErrors.end());
        }
    } else if (auto returnStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(body)) {
        if (returnStmt->value) {
            auto returnErrors = infer_expression_error_types(returnStmt->value);
            errorTypes.insert(errorTypes.end(), returnErrors.begin(), returnErrors.end());
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(body)) {
        auto thenErrors = infer_function_error_types(ifStmt->thenBranch);
        errorTypes.insert(errorTypes.end(), thenErrors.begin(), thenErrors.end());
        
        if (ifStmt->elseBranch) {
            auto elseErrors = infer_function_error_types(ifStmt->elseBranch);
            errorTypes.insert(errorTypes.end(), elseErrors.begin(), elseErrors.end());
        }
    } else if (auto exprStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(body)) {
        // Check for fallible expressions that might propagate errors
        auto exprErrors = infer_expression_error_types(exprStmt->expression);
        errorTypes.insert(errorTypes.end(), exprErrors.begin(), exprErrors.end());
    }
    
    // Remove duplicates
    std::sort(errorTypes.begin(), errorTypes.end());
    errorTypes.erase(std::unique(errorTypes.begin(), errorTypes.end()), errorTypes.end());
    
    return errorTypes;
}

std::vector<std::string> TypeChecker::infer_expression_error_types(const std::shared_ptr<LM::Frontend::AST::Expression>& expr) {
    std::vector<std::string> errorTypes;
    
    if (auto errorConstruct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(expr)) {
        // Direct error construction
        errorTypes.push_back(errorConstruct->errorType);
        
    } else if (auto fallibleExpr = std::dynamic_pointer_cast<LM::Frontend::AST::FallibleExpr>(expr)) {
        // Fallible expression with ? operator - propagates errors from inner expression
        auto innerErrors = infer_expression_error_types(fallibleExpr->expression);
        errorTypes.insert(errorTypes.end(), innerErrors.begin(), innerErrors.end());
        
    } else if (auto callExpr = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        // Function call - check if called function can produce errors
        if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(callExpr->callee)) {
            auto it = function_signatures.find(varExpr->name);
            if (it != function_signatures.end() && it->second.can_fail) {
                errorTypes.insert(errorTypes.end(), it->second.error_types.begin(), it->second.error_types.end());
            }
        }
        
    } else if (auto binaryExpr = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        // Binary expressions might produce built-in errors (e.g., division by zero)
        if (binaryExpr->op == TokenType::SLASH) {
            errorTypes.push_back("DivisionByZero");
        }
        
        // Also check operands for error propagation
        auto leftErrors = infer_expression_error_types(binaryExpr->left);
        auto rightErrors = infer_expression_error_types(binaryExpr->right);
        errorTypes.insert(errorTypes.end(), leftErrors.begin(), leftErrors.end());
        errorTypes.insert(errorTypes.end(), rightErrors.begin(), rightErrors.end());
        
    } else if (auto indexExpr = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
        // Array/dict indexing can produce IndexOutOfBounds errors
        errorTypes.push_back("IndexOutOfBounds");
        
        // Also check object and index expressions
        auto objectErrors = infer_expression_error_types(indexExpr->object);
        auto indexErrors = infer_expression_error_types(indexExpr->index);
        errorTypes.insert(errorTypes.end(), objectErrors.begin(), objectErrors.end());
        errorTypes.insert(errorTypes.end(), indexErrors.begin(), indexErrors.end());
    }
    
    // Remove duplicates
    std::sort(errorTypes.begin(), errorTypes.end());
    errorTypes.erase(std::unique(errorTypes.begin(), errorTypes.end()), errorTypes.end());
    
    return errorTypes;
}

bool TypeChecker::can_function_produce_error_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body, 
                                             const std::string& errorType) {
    // Check if function body can produce specified error type
    
    if (auto blockStmt = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        for (const auto& stmt : blockStmt->statements) {
            if (can_function_produce_error_type(stmt, errorType)) {
                return true;
            }
        }
    } else if (auto returnStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(body)) {
        if (returnStmt->value) {
            // Check if return expression can produce error type
            auto returnErrors = infer_expression_error_types(returnStmt->value);
            return std::find(returnErrors.begin(), returnErrors.end(), errorType) != returnErrors.end();
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(body)) {
        return can_function_produce_error_type(ifStmt->thenBranch, errorType) ||
               (ifStmt->elseBranch && can_function_produce_error_type(ifStmt->elseBranch, errorType));
    } else if (auto exprStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(body)) {
        // Check for fallible expressions that might propagate errors
        auto exprErrors = infer_expression_error_types(exprStmt->expression);
        return std::find(exprErrors.begin(), exprErrors.end(), errorType) != exprErrors.end();
    }
    
    return false;
}

bool TypeChecker::can_propagate_error(const std::vector<std::string>& source_errors, 
                                  const std::vector<std::string>& target_errors) {
    // If target allows generic errors, any source is compatible
    if (target_errors.empty()) {
        return true;
    }
    
    // Check that all source errors are in target errors
    for (const auto& sourceError : source_errors) {
        bool found = std::find(target_errors.begin(), target_errors.end(), sourceError) != target_errors.end();
        if (!found) {
            return false;
        }
    }
    
    return true;
}

bool TypeChecker::is_error_union_compatible(TypePtr from, TypePtr to) {
    if (!is_error_union_type(from) || !is_error_union_type(to)) {
        return false;
    }
    
    auto* fromErrorUnionPtr = std::get_if<ErrorUnionType>(&from->extra);
    auto* toErrorUnionPtr = std::get_if<ErrorUnionType>(&to->extra);
    if (!fromErrorUnionPtr || !toErrorUnionPtr) {
        return false;
    }
    auto& fromErrorUnion = *fromErrorUnionPtr;
    auto& toErrorUnion = *toErrorUnionPtr;
    
    // Success types must be compatible
    if (!is_type_compatible(fromErrorUnion.successType, toErrorUnion.successType)) {
        return false;
    }
    
    // Check error type compatibility
    return can_propagate_error(fromErrorUnion.errorTypes, toErrorUnion.errorTypes);
}

std::string TypeChecker::join_error_types(const std::vector<std::string>& errorTypes) {
    if (errorTypes.empty()) {
        return "any error";
    }
    
    std::string result;
    for (size_t i = 0; i < errorTypes.size(); ++i) {
        if (i > 0) result += ", ";
        result += errorTypes[i];
    }
    return result;
}

// =============================================================================
// PATTERN MATCHING METHODS
// =============================================================================

bool TypeChecker::is_exhaustive_error_match(const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases, TypePtr type) {
    if (!is_error_union_type(type)) {
        return true; // Non-error types don't need exhaustive error matching
    }
    
    auto* errorUnionPtr = std::get_if<ErrorUnionType>(&type->extra);
    if (!errorUnionPtr) {
        return false;
    }
    auto& errorUnion = *errorUnionPtr;
    
    bool hasSuccessCase = false;
    bool hasGenericErrorCase = false;
    std::unordered_set<std::string> coveredErrors;
    
    for (const auto& matchCase : cases) {
        // Enhanced pattern analysis for error matching
        if (auto valPattern = std::dynamic_pointer_cast<LM::Frontend::AST::ValPatternExpr>(matchCase->pattern)) {
            hasSuccessCase = true;
        } else if (auto errPattern = std::dynamic_pointer_cast<LM::Frontend::AST::ErrPatternExpr>(matchCase->pattern)) {
            if (errPattern->errorType.has_value()) {
                // Specific error type in err pattern
                coveredErrors.insert(errPattern->errorType.value());
            } else {
                // Generic error pattern
                hasGenericErrorCase = true;
            }
        } else if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            if (bindingPattern->typeName == "val") {
                hasSuccessCase = true;
            } else if (bindingPattern->typeName == "err") {
                hasGenericErrorCase = true;
            } else {
                // Specific error type pattern
                coveredErrors.insert(bindingPattern->typeName);
            }
        } else {
            // Wildcard or other patterns - assume they cover everything
            hasSuccessCase = true;
            hasGenericErrorCase = true;
        }
    }
    
    // For generic error unions, we need at least success and error cases
    if (errorUnion.isGenericError) {
        return hasSuccessCase && hasGenericErrorCase;
    }
    
    // For specific error unions, all error types must be covered plus success case
    bool allErrorsCovered = hasGenericErrorCase || 
                           (coveredErrors.size() >= errorUnion.errorTypes.size() &&
                            std::all_of(errorUnion.errorTypes.begin(), errorUnion.errorTypes.end(),
                                       [&coveredErrors](const std::string& errorType) {
                                           return coveredErrors.find(errorType) != coveredErrors.end();
                                       }));
    
    return hasSuccessCase && allErrorsCovered;
}

bool TypeChecker::is_exhaustive_union_match(TypePtr union_type, const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases) {
    if (!is_union_type(union_type)) {
        return true; // Non-union types don't need union exhaustiveness checking
    }
    
    const auto* unionTypeInfo = std::get_if<UnionType>(&union_type->extra);
    if (!unionTypeInfo) {
        return true;
    }
    
    std::set<std::string> coveredVariantNames;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            coveredVariantNames.insert(bindingPattern->typeName);
        } else if (auto literalExpr = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(matchCase->pattern)) {
            if (std::holds_alternative<std::string>(literalExpr->value)) {
                coveredVariantNames.insert(std::get<std::string>(literalExpr->value));
            } else if (std::holds_alternative<std::nullptr_t>(literalExpr->value)) {
                hasWildcard = true;
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_") {
                hasWildcard = true;
            } else {
                coveredVariantNames.insert(varExpr->name);
            }
        }
    }
    
    if (hasWildcard) return true;
    
    // Check if all variant names are covered
    for (const auto& name : unionTypeInfo->variantNames) {
        if (coveredVariantNames.find(name) == coveredVariantNames.end()) {
            return false;
        }
    }
    
    return true;
}

bool TypeChecker::is_exhaustive_option_match(const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases) {
    bool hasSomeCase = false;
    bool hasNoneCase = false;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            if (bindingPattern->typeName == "Some" || bindingPattern->typeName == "some") {
                hasSomeCase = true;
            } else if (bindingPattern->typeName == "None" || bindingPattern->typeName == "none") {
                hasNoneCase = true;
            } else if (bindingPattern->typeName == "_" || bindingPattern->typeName == "any") {
                hasWildcard = true;
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_" || varExpr->name == "any") {
                hasWildcard = true;
            }
        }
    }
    
    // If we have a wildcard, it's exhaustive
    if (hasWildcard) {
        return true;
    }
    
    // Otherwise, need both Some and None cases
    return hasSomeCase && hasNoneCase;
}

std::string TypeChecker::get_missing_union_variants(TypePtr union_type, const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases) {
    if (!is_union_type(union_type)) {
        return "";
    }
    
    const auto* unionTypeInfo = std::get_if<UnionType>(&union_type->extra);
    if (!unionTypeInfo) {
        return "";
    }
    
    std::set<std::string> coveredVariantNames;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            coveredVariantNames.insert(bindingPattern->typeName);
        } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_") {
                hasWildcard = true;
            } else {
                coveredVariantNames.insert(varExpr->name);
            }
        }
    }
    
    if (hasWildcard) return "";
    
    std::vector<std::string> missing;
    for (const auto& name : unionTypeInfo->variantNames) {
        if (coveredVariantNames.find(name) == coveredVariantNames.end()) {
            missing.push_back(name);
        }
    }
    
    if (missing.empty()) return "";
    
    std::string result = "Missing patterns for: ";
    for (size_t i = 0; i < missing.size(); ++i) {
        if (i > 0) result += ", ";
        result += missing[i];
    }
    return result;
}

void TypeChecker::validate_pattern_compatibility(std::shared_ptr<LM::Frontend::AST::Expression> pattern_node, TypePtr match_type, int line) {
    // Basic pattern compatibility validation
    if (!pattern_node || !match_type) {
        return;
    }
    
    if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(pattern_node)) {
        // Check if binding pattern is compatible with match type
        if (bindingPattern->typeName == "val") {
            // val pattern expects success type
            if (is_error_union_type(match_type)) {
                auto* errorUnionPtr = std::get_if<ErrorUnionType>(&match_type->extra);
                if (errorUnionPtr) {
                    auto& errorUnion = *errorUnionPtr;
                    // val pattern should match the success type
                    // This is a simplified check - in practice, we'd need more sophisticated matching
                }
            } else {
                add_error("val pattern can only be used with error union types", line);
            }
        } else if (bindingPattern->typeName == "err") {
            // err pattern expects error type
            if (!is_error_union_type(match_type)) {
                add_error("err pattern can only be used with error union types", line);
            }
        }
    } else if (auto typePattern = std::dynamic_pointer_cast<LM::Frontend::AST::TypePatternExpr>(pattern_node)) {
        // Type pattern - check compatibility
        if (typePattern->type) {
            TypePtr patternType = resolve_type_annotation(typePattern->type);
            if (!is_type_compatible(patternType, match_type)) {
                add_error("Type pattern type " + patternType->toString() + " does not match match type " + match_type->toString(), line);
            }
        }
    } else if (auto literalPattern = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(pattern_node)) {
        // Literal pattern - check compatibility
        TypePtr literalType = check_literal_expr(literalPattern);
        if (!is_type_compatible(literalType, match_type)) {
            add_error("Literal pattern type " + literalType->toString() + " does not match match type " + match_type->toString(), line);
        }
    }
    // Add more pattern type checks as needed
}

// =============================================================================
// ENHANCED TYPE INFERENCE METHODS
// =============================================================================

TypePtr TypeChecker::infer_lambda_return_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    // Try to infer return type from lambda body
    if (!body) {
        return type_system.NIL_TYPE;
    }
    
    // If body is a block statement, look for return statements
    if (auto blockStmt = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        std::vector<TypePtr> returnTypes;
        
        for (const auto& stmt : blockStmt->statements) {
            if (auto returnStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
                if (returnStmt->value) {
                    TypePtr returnType = check_expression(returnStmt->value);
                    returnTypes.push_back(returnType);
                } else {
                    returnTypes.push_back(type_system.NIL_TYPE);
                }
            }
        }
        
        // If we found return statements, try to find common type
        if (!returnTypes.empty()) {
            TypePtr commonType = returnTypes[0];
            for (size_t i = 1; i < returnTypes.size(); ++i) {
                try {
                    commonType = get_common_type(commonType, returnTypes[i]);
                } catch (const std::exception&) {
                    // If types are incompatible, fall back to ANY_TYPE
                    return type_system.ANY_TYPE;
                }
            }
            return commonType;
        }
        
        // No explicit return statements found, assume NIL return
        return type_system.NIL_TYPE;
    }
    
    // If body is an expression statement, infer from expression
    if (auto exprStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(body)) {
        return check_expression(exprStmt->expression);
    }
    
    // For other statement types, assume NIL return
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::infer_literal_type(const std::shared_ptr<LM::Frontend::AST::LiteralExpr>& expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    // Handle string-based literal values with enhanced type inference
    if (std::holds_alternative<std::string>(expr->value)) {
        std::string stringValue = std::get<std::string>(expr->value);
        
        // Try to determine if this string represents a number
        bool isNumeric = false;
        bool isFloat = false;
        
        if (!stringValue.empty()) {
            char first = stringValue[0];
            if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                isNumeric = true;
                // Check if it's a float
                if (stringValue.find('.') != std::string::npos || 
                    stringValue.find('e') != std::string::npos || 
                    stringValue.find('E') != std::string::npos) {
                    isFloat = true;
                }
            }
        }
        
        // If we have an expected type context and it's compatible, use it
        if (expected_type && (
            expected_type->tag == TypeTag::Int || expected_type->tag == TypeTag::Int8 ||
            expected_type->tag == TypeTag::Int16 || expected_type->tag == TypeTag::Int32 ||
            expected_type->tag == TypeTag::Int64 || expected_type->tag == TypeTag::Int128 ||
            expected_type->tag == TypeTag::UInt || expected_type->tag == TypeTag::UInt8 ||
            expected_type->tag == TypeTag::UInt16 || expected_type->tag == TypeTag::UInt32 ||
            expected_type->tag == TypeTag::UInt64 || expected_type->tag == TypeTag::UInt128 ||
            expected_type->tag == TypeTag::Float32 || expected_type->tag == TypeTag::Float64)) {
            return expected_type;
        }
        
        if (isNumeric) {
            if (isFloat) {
                // Float values - determine appropriate float type
                try {
                    double floatVal = std::stod(stringValue);
                    if (std::abs(floatVal) <= std::numeric_limits<float>::max()) {
                        float floatVal32 = static_cast<float>(floatVal);
                        if (static_cast<double>(floatVal32) == floatVal) {
                            return type_system.FLOAT32_TYPE;
                        }
                    }
                    return type_system.FLOAT64_TYPE;
                } catch (const std::exception&) {
                    // If parsing fails, treat as string
                    return type_system.STRING_TYPE;
                }
            } else {
                // Integer values - determine appropriate integer type
                try {
                    // Try to fit into the smallest appropriate integer type
                    int64_t intVal = std::stoll(stringValue);
                    
                    if (intVal >= std::numeric_limits<int8_t>::min() && intVal <= std::numeric_limits<int8_t>::max()) {
                        return type_system.INT8_TYPE;
                    } else if (intVal >= std::numeric_limits<int16_t>::min() && intVal <= std::numeric_limits<int16_t>::max()) {
                        return type_system.INT16_TYPE;
                    } else if (intVal >= std::numeric_limits<int32_t>::min() && intVal <= std::numeric_limits<int32_t>::max()) {
                        return type_system.INT32_TYPE;
                    } else {
                        return type_system.INT64_TYPE;
                    }
                } catch (const std::exception&) {
                    // If too large for int64, use Int128
                    return type_system.INT128_TYPE;
                }
            }
        } else {
            // String literal
            return type_system.STRING_TYPE;
        }
    } else if (std::holds_alternative<bool>(expr->value)) {
        return type_system.BOOL_TYPE;
    } else if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        return type_system.NIL_TYPE;
    }
    
    return type_system.STRING_TYPE; // Default fallback
}

// =============================================================================
// CONTRACT STATEMENT CHECKING
// =============================================================================

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
    
    // Check each case
    for (const auto& matchCase : match_stmt->cases) {
        // Check guard if present
        if (matchCase.guard) {
            TypePtr guardType = check_expression(matchCase.guard);
            if (!is_boolean_type(guardType) && guardType->tag != TypeTag::Any) {
                add_error("Match guard must be a boolean expression", match_stmt->line);
            }
        }
        
        // Check case body
        check_statement(matchCase.body);
        
        // Validate pattern compatibility with matched type
        validate_pattern_compatibility(matchCase.pattern, matchType, match_stmt->line);
    }
    
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
    
    match_stmt->inferred_type = matchType;
    return matchType;
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

TypeCheckResult check_program(std::shared_ptr<LM::Frontend::AST::Program> program, const std::string& source, const std::string& file_path) {
    // Resolve all modules once at the beginning
    auto& manager = ModuleManager::getInstance();
    manager.clear();
    manager.resolve_all(program, "root");

    // Create type system
    auto type_system = std::make_shared<TypeSystem>();
    auto checker = create(*type_system);
    
    // Set source context for error reporting
    checker->set_source_context(source, file_path);
    
    bool success = checker->check_program(program);
    TypeCheckResult result(program, type_system, success, checker->get_errors());
    result.import_aliases = checker->get_import_aliases();  // Copy import aliases from checker
    result.registered_modules = checker->get_registered_modules();  // Copy registered modules from checker
    
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
    checker.register_builtin_function("print", {ts.ANY_TYPE}, ts.NIL_TYPE);
    
    // Math constants (as functions)
    checker.register_builtin_function("pi", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("e", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("ln2", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("ln10", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("sqrt2", {}, ts.FLOAT64_TYPE);
    
    // Collection functions (enhanced)
    auto function_type = ts.createFunctionType({}, ts.ANY_TYPE); // Simple function type
    checker.register_builtin_function("map", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.createTypedListType(ts.ANY_TYPE));
    checker.register_builtin_function("filter", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.createTypedListType(ts.ANY_TYPE));
    checker.register_builtin_function("reduce", {function_type, ts.createTypedListType(ts.ANY_TYPE), ts.ANY_TYPE}, ts.ANY_TYPE);
    checker.register_builtin_function("forEach", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.NIL_TYPE);
    checker.register_builtin_function("find", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.ANY_TYPE);
    checker.register_builtin_function("some", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.BOOL_TYPE);
    checker.register_builtin_function("every", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.BOOL_TYPE);
    
    // Function composition
    checker.register_builtin_function("compose", {function_type, function_type}, function_type);
    checker.register_builtin_function("curry", {function_type}, function_type);
    checker.register_builtin_function("partial", {function_type, ts.ANY_TYPE}, function_type);
    
    // Channel function
    checker.register_builtin_function("channel", {}, ts.CHANNEL_TYPE);
    
    // Additional utility functions from backend
    checker.register_builtin_function("typeOf", {ts.ANY_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("debug", {ts.ANY_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("input", {ts.STRING_TYPE}, ts.STRING_TYPE);
}

} // namespace TypeCheckerFactory

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
    type_system.addUserDefinedType(trait->name, trait_type);
    // TODO: add TraitType extra info
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

    auto symbols_to_import = manager.filter_symbols(module, import_stmt->filter);
    
    // Alias management
    std::string alias = import_stmt->alias ? import_stmt->alias.value() : "";
    if (alias.empty()) {
        // If no alias, use the last part of the module path
        size_t last_dot = import_stmt->modulePath.find_last_of('.');
        if (last_dot != std::string::npos) {
            alias = import_stmt->modulePath.substr(last_dot + 1);
        } else {
            alias = import_stmt->modulePath;
        }
    }
    import_aliases[alias] = import_stmt->modulePath;

    // Register the alias as a "variable" that points to a dummy frame
    // This allows the TypeChecker to resolve 'math' in 'math.add'
    TypeSystem::FrameInfo dummy_info;
    dummy_info.name = alias;
    type_system.registerFrame(alias, dummy_info);
    declare_variable(alias, type_system.createFrameType(alias));

    // Also add to frame_declarations so check_member_expr doesn't complain
    FrameInfo info;
    info.name = alias;
    frame_declarations[alias] = info;
    
    // Inline symbols into the current program's imported_symbols map
    for (const auto& stmt : module->ast->statements) {
        std::string name;
        if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) name = func->name;
        else if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) name = frame->name;
        else if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) name = var->name;

        if (!name.empty() && symbols_to_import.count(name)) {
            std::string qualified_name = alias + "." + name;
            current_program_->imported_symbols[qualified_name] = stmt;
            // Also allow direct name if it doesn't conflict?
            // For now, only qualified names via alias are supported.
        }
    }
    
    return type_system.NIL_TYPE;
}

} // namespace Frontend
} // namespace LM