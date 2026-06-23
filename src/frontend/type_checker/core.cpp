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
            TypeChecker checker(this->type_system);
            checker.set_source_context(module->source, module->path);
            if (!checker.check_program(module->ast)) {
                add_error("Failed to type check module: " + path);
            }

            // Merge metadata back into current checker
            for (const auto& [name, info] : checker.frame_declarations) {
                this->frame_declarations[name] = info;
            }
            for (const auto& [name, info] : checker.trait_declarations) {
                this->trait_declarations[name] = info;
            }
            for (const auto& [name, sig] : checker.function_signatures) {
                this->function_signatures[name] = sig;
            }
            for (const auto& [name, type] : checker.variable_types) {
                this->variable_types[name] = type;
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

            auto& fd = frame_declarations[name];
            fd.name = name;
            fd.declaration = frame_decl;
            fd.fields = info.fields;
            fd.field_has_default.clear();
            for (const auto& field : frame_decl->fields) {
                fd.field_has_default.push_back({field->name, field->defaultValue != nullptr});
            }

            if (frame_decl->init) {
                std::string init_name = name + ".init";
                FunctionSignature sig;
                sig.name = init_name;
                sig.return_type = type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(name));
                for (const auto& p : frame_decl->init->parameters) sig.param_types.push_back(resolve_type_annotation(p.second));
                for (const auto& op : frame_decl->init->optionalParams) sig.param_types.push_back(resolve_type_annotation(op.second.first));
                function_signatures[init_name] = sig;
            }
            for (const auto& m : frame_decl->methods) {
                std::string m_name = name + "." + m->name;
                FunctionSignature sig;
                sig.name = m_name;
                sig.return_type = m->returnType ? resolve_type_annotation(m->returnType) : type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(name));
                for (const auto& p : m->parameters) sig.param_types.push_back(resolve_type_annotation(p.second));
                for (const auto& op : m->optionalParams) sig.param_types.push_back(resolve_type_annotation(op.second.first));
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

// =============================================================================
// SCOPE MANAGEMENT (declare_variable/lookup_variable/enter_scope/exit_scope)
// Memory-safety helpers, get_code_context, check_assert_call, is_visible and
// related utilities live in their canonical TUs (memory.cpp / utils.cpp).
// =============================================================================

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

} // namespace Frontend
} // namespace LM
