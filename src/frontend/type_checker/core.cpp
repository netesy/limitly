#include "../type_checker.hh"
#include "../module_manager.hh"
#include "../../error/debugger.hh"
#include "../../memory/model.hh"
#include "../parser.hh"
#include "../scanner.hh"
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

    // PASS -1: Basic Type Discovery (Pre-registration)
    auto register_custom_type = [&](const std::string& name, const std::shared_ptr<LM::Frontend::AST::Statement>& stmt) {
        if (auto enum_decl = std::dynamic_pointer_cast<LM::Frontend::AST::EnumDeclaration>(stmt)) {
            EnumType enumTypeInfo;
            enumTypeInfo.name = name;
            for (const auto& variant : enum_decl->variants) enumTypeInfo.addVariant(variant.first);
            TypePtr enumType = std::make_shared<::Type>(TypeTag::Enum, enumTypeInfo);
            type_system.addUserDefinedType(name, enumType);

            // Register variants in global scope (qualified only) and track ownership
            for (const auto& variant : enum_decl->variants) {
                std::string qualified = name + "." + variant.first;
                variant_owners[variant.first].push_back(enumType);
                
                if (variant.second.empty()) {
                    variable_types[qualified] = enumType;
                    FunctionSignature sig;
                    sig.name = variant.first;
                    sig.return_type = enumType;
                    function_signatures[qualified] = sig;
                } else {
                    std::vector<TypePtr> paramTypes;
                    for (const auto& t : variant.second) paramTypes.push_back(type_system.ANY_TYPE);
                    TypePtr constructorType = type_system.createFunctionType(paramTypes, enumType);
                    variable_types[qualified] = constructorType;
                    FunctionSignature sig;
                    sig.name = variant.first;
                    sig.param_types = paramTypes;
                    sig.return_type = enumType;
                    function_signatures[qualified] = sig;
                }
            }
        } else if (auto type_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TypeDeclaration>(stmt)) {
            type_system.addUserDefinedType(name, type_system.ANY_TYPE);
        } else if (auto frame_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
            type_system.addUserDefinedType(name, type_system.createFrameType(name));
        }
    };

    for (const auto& stmt : program->statements) {
        std::string name;
        if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) name = frame->name;
        else if (auto trait = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) name = trait->name;
        else if (auto enm = std::dynamic_pointer_cast<LM::Frontend::AST::EnumDeclaration>(stmt)) name = enm->name;
        else if (auto type_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TypeDeclaration>(stmt)) name = type_decl->name;
        if (!name.empty()) register_custom_type(name, stmt);
    }
    for (const auto& [name, stmt] : program->imported_symbols) {
        register_custom_type(name, stmt);
    }

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
        else if (auto enm = std::dynamic_pointer_cast<LM::Frontend::AST::EnumDeclaration>(stmt)) name = enm->name;
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
                 sig.return_type = func_decl->returnType ? resolve_type_annotation(func_decl->returnType.value()) : type_system.NIL_TYPE;
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
            
            std::vector<std::string> param_names;
            std::vector<bool> has_defaults;
            for (const auto& p : func_decl->params) {
                param_names.push_back(p.first);
                has_defaults.push_back(false);
            }
            for (const auto& op : func_decl->optionalParams) {
                param_names.push_back(op.first);
                has_defaults.push_back(op.second.second != nullptr);
            }
            TypePtr func_type = type_system.createFunctionType(param_names, sig.param_types, sig.return_type, has_defaults);
            variable_types[name] = func_type;
            declare_variable(name, func_type);
        } else if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
            TypePtr var_type = (var_decl->type && var_decl->type.value()) ? resolve_type_annotation(var_decl->type.value()) : type_system.ANY_TYPE;
            declare_variable(name, var_type);
        } else if (auto enum_decl = std::dynamic_pointer_cast<LM::Frontend::AST::EnumDeclaration>(stmt)) {
            check_enum_declaration(enum_decl);
        } else if (auto type_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TypeDeclaration>(stmt)) {
            check_type_declaration(type_decl);
        }
    };

    for (const auto& stmt : program->statements) {
        std::string name;
        if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) name = frame->name;
        else if (auto trait = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) name = trait->name;
        else if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) name = func->name;
        else if (auto enm = std::dynamic_pointer_cast<LM::Frontend::AST::EnumDeclaration>(stmt)) name = enm->name;
        if (!name.empty()) resolve_sig(name, stmt);
    }
    for (const auto& [name, stmt] : program->imported_symbols) {
        resolve_sig(name, stmt);
    }

    // PASS 2.5: Global Scope Population
    // Register built-in and already-discovered symbols in the global scope
    for (const auto& pair : function_signatures) {
        TypePtr type = nullptr;
        auto vt_it = variable_types.find(pair.first);
        if (vt_it != variable_types.end()) {
            type = vt_it->second;
        } else {
            type = type_system.createFunctionType(pair.second.param_types, pair.second.return_type);
        }
        declare_variable(pair.first, type);
    }

    // PASS 3: Body Verification (local and inlined symbols)
    for (const auto& stmt : program->statements) {
        if (auto enum_decl = std::dynamic_pointer_cast<LM::Frontend::AST::EnumDeclaration>(stmt)) {
            // Already handled in PASS 2/3 but let's be explicit
        } else if (auto type_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TypeDeclaration>(stmt)) {
            // Already handled
        }
    }
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
    errors.push_back(message);
    // Type checker errors default to column 1 since we don't have precise token positions
    int column = 1;
    
    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, column, InterpretationStage::SEMANTIC, current_source, current_file_path, "", "");
    } else {
        Debugger::error(message, line, column, InterpretationStage::SEMANTIC, "(in REPL)", "(in REPL)", "", "");
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
    
    errors.push_back(enhancedMessage);
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
    if (type && type->tag == TypeTag::Function) {
        declare_variable_memory(name, type);
        mark_variable_initialized(name);
    }
    if (current_scope) {
        current_scope->declare(name, type);
    }
}

TypePtr TypeChecker::lookup_variable(const std::string& name) {
    TypePtr res = current_scope ? current_scope->lookup(name) : nullptr;
    if (!res) {
        auto it = variable_types.find(name);
        if (it != variable_types.end()) res = it->second;
    }
    return res;
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
    TypePtr type = lookup_variable(name);
    if (type && (type->tag == TypeTag::Function || type->tag == TypeTag::Int || type->tag == TypeTag::Int64 || type->tag == TypeTag::String || type->tag == TypeTag::Bool)) return;
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

    // Protected allows access from related frames (those sharing traits)
    if (visibility == LM::Frontend::AST::VisibilityLevel::Protected) {
        auto target_info = type_system.getFrameInfo(frame_name);
        auto current_info = type_system.getFrameInfo(current_frame->name);

        if (target_info && current_info) {
            // Check if current frame inherits from target frame
            if (target_info->name == current_info->name) return true;
            for (const auto& trait_a : target_info->implements) {
                for (const auto& trait_b : current_info->implements) {
                    if (trait_a == trait_b) return true;
                }
            }
        }
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

} // namespace Frontend
} // namespace LM
