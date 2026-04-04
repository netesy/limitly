#include "../generator.hh"
#include "../functions.hh"
#include "../../frontend/module_manager.hh"
#include "../function_registry.hh"
#include "../builtin_functions.hh"
#include "../../frontend/ast.hh"
#include "../../frontend/scanner.hh"
#include <algorithm>
#include <map>
#include <limits>

using namespace LM::LIR;

namespace LM {
namespace LIR {

void Generator::lower_trait_declaration(LM::Frontend::AST::TraitDeclaration& trait_decl) {
    for (const auto& method : trait_decl.methods) {
        lower_trait_method(trait_decl.name, *method);
    }
}


void Generator::lower_trait_method(const std::string& trait_name, LM::Frontend::AST::FunctionDeclaration& method) {
    std::string full_method_name = trait_name + "." + method.name;
    
    // If method has no body, it's abstract, nothing to lower
    if (!method.body || method.body->statements.empty()) {
        return;
    }

    auto& func_manager = LIRFunctionManager::getInstance();
    
    // Create function with parameters (including 'this' as first parameter)
    size_t total_params = method.params.size() + 1; // +1 for 'this'
    current_function_ = std::make_unique<LIR_Function>(full_method_name, total_params);
    next_register_ = total_params;
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    enter_scope();
    
    cfg_context_.building_cfg = false;
    cfg_context_.current_block = nullptr;
    
    // Register 'this' parameter as first parameter (register 0)
    this_register_ = 0;
    bind_variable("this", 0);
    auto any_type = std::make_shared<::Type>(::TypeTag::Any);
    set_register_language_type(0, any_type);
    set_register_abi_type(0, Type::Ptr);
    
    // Register method parameters
    for (size_t i = 0; i < method.params.size(); ++i) {
        size_t reg_index = i + 1; // +1 for 'this'
        bind_variable(method.params[i].first, static_cast<Reg>(reg_index));
        set_register_type(static_cast<Reg>(reg_index), nullptr);
    }
    
    // Emit method body
    if (method.body) {
        emit_stmt(*method.body);
    }
    
    // Add implicit return
    if (!current_function_->instructions.empty() && !current_function_->instructions.back().isReturn()) {
        emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, 0, 0, 0));
    } else if (current_function_->instructions.empty()) {
        emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, 0, 0, 0));
    }

    exit_scope();
    this_register_ = UINT32_MAX;
    
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    
    std::vector<LIRParameter> params;
    LIRParameter this_param;
    this_param.name = "this";
    this_param.type = Type::Ptr;
    params.push_back(this_param);
    
    for (const auto& param : method.params) {
        LIRParameter lir_param;
        lir_param.name = param.first;
        lir_param.type = Type::I64;
        params.push_back(lir_param);
    }
    
    auto lir_func = func_manager.createFunction(full_method_name, params, Type::I64, nullptr);
    lir_func->setInstructions(result->instructions);
}


void Generator::lower_frame_methods(LM::Frontend::AST::FrameDeclaration& frame_decl) {
    // Lower all frame methods into separate LIR functions
    
    // Lower regular methods
    for (const auto& method : frame_decl.methods) {
        lower_frame_method(frame_decl.name, *method);
    }
    
    // Lower init method if present
    if (frame_decl.init) {
        lower_frame_init_method(frame_decl.name, *frame_decl.init);
    }
    
    // Lower deinit method if present
    if (frame_decl.deinit) {
        lower_frame_deinit_method(frame_decl.name, *frame_decl.deinit);
    }
}


void Generator::lower_frame_method(const std::string& frame_name, LM::Frontend::AST::FrameMethod& method) {
    // Create a function with the frame method name (frame_name.method_name)
    std::string full_method_name = frame_name + "." + method.name;
    
    auto& func_manager = LIRFunctionManager::getInstance();
    
    // Register function signature early for recursive calls
    if (!func_manager.hasFunction(full_method_name)) {
        std::vector<LIRParameter> empty_params;
        auto func = func_manager.createFunction(full_method_name, empty_params, Type::I64, nullptr);
    }
    
    // Create function with parameters (including 'this' as first parameter)
    size_t total_params = method.parameters.size() + 1; // +1 for 'this'
    current_function_ = std::make_unique<LIR_Function>(full_method_name, total_params);
    next_register_ = total_params;
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    enter_scope();
    
    // Use CFG mode for proper JIT compatibility (disabled for now)
    cfg_context_.building_cfg = false;  // DISABLED: CFG linearization has bugs with elif
    cfg_context_.current_block = nullptr;
    
    // Register 'this' parameter as first parameter (register 0)
    this_register_ = 0;  // Set this_register_ for 'this' context
    bind_variable("this", 0);
    auto frame_type = std::make_shared<::Type>(::TypeTag::Frame);
    FrameType ft;
    ft.name = frame_name;
    frame_type->extra = ft;
    set_register_language_type(0, frame_type);
    set_register_abi_type(0, Type::Ptr);
    
    // Register method parameters
    for (size_t i = 0; i < method.parameters.size(); ++i) {
        size_t reg_index = i + 1; // +1 for 'this'
        bind_variable(method.parameters[i].first, static_cast<Reg>(reg_index));
        set_register_type(static_cast<Reg>(reg_index), nullptr);
    }
    
    // Emit method body
    if (method.body) {
        emit_stmt(*method.body);
    }
    
    // Add implicit return if none exists
    if (!cfg_context_.building_cfg) {
        // Linear mode - add implicit return if function doesn't end with return
        if (current_function_->instructions.empty() || 
            !current_function_->instructions.back().isReturn()) {
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, 0, 0, 0));
        }
    }
    
    // Finish CFG building (only if CFG was used)
    if (cfg_context_.building_cfg) {
        if (!validate_cfg()) {
            report_error("CFG validation failed for frame method: " + full_method_name);
        }
        finish_cfg_build();
    }

    exit_scope();
    this_register_ = UINT32_MAX;  // Clear this_register_
    
    // Convert LIR_Function to LIRFunction and update the registration
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    
    // Create proper LIRFunction from our LIR_Function
    std::vector<LIRParameter> params;
    
    // Add 'this' parameter
    LIRParameter this_param;
    this_param.name = "this";
    this_param.type = Type::Ptr;
    params.push_back(this_param);
    
    // Add method parameters
    for (const auto& param : method.parameters) {
        LIRParameter lir_param;
        lir_param.name = param.first;
        // Convert type - for now use I64 as default
        lir_param.type = Type::I64;
        params.push_back(lir_param);
    }
    
    // Create function with I64 return type for now
    auto lir_func = func_manager.createFunction(full_method_name, params, Type::I64, nullptr);
    
    // Copy the instructions from our LIR_Function
    lir_func->setInstructions(result->instructions);

    // Update function table
    auto& func_info = function_table_[full_method_name];
    func_info.lir_function = nullptr; // Not needed since FunctionRegistry manages it
}


void Generator::lower_frame_init_method(const std::string& frame_name, LM::Frontend::AST::FrameMethod& init_method) {
    // Create a function with the frame init method name (frame_name.init)
    std::string full_method_name = frame_name + ".init";
    
    auto& func_manager = LIRFunctionManager::getInstance();
    
    // Register function signature early for recursive calls
    if (!func_manager.hasFunction(full_method_name)) {
        std::vector<LIRParameter> empty_params;
        auto func = func_manager.createFunction(full_method_name, empty_params, Type::I64, nullptr);
    }
    
    // Create function with parameters (including 'this' as first parameter)
    size_t total_params = init_method.parameters.size() + 1; // +1 for 'this'
    current_function_ = std::make_unique<LIR_Function>(full_method_name, total_params);
    next_register_ = total_params;
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    enter_scope();
    
    // Use CFG mode for proper JIT compatibility (disabled for now)
    cfg_context_.building_cfg = false;  // DISABLED: CFG linearization has bugs with elif
    cfg_context_.current_block = nullptr;
    
    // Register 'this' parameter as first parameter (register 0)
    this_register_ = 0;  // Set this_register_ for 'this' context
    bind_variable("this", 0);
    auto frame_type = std::make_shared<::Type>(::TypeTag::Frame);
    FrameType ft;
    ft.name = frame_name;
    frame_type->extra = ft;
    set_register_language_type(0, frame_type);
    set_register_abi_type(0, Type::Ptr);
    
    // Register init parameters
    for (size_t i = 0; i < init_method.parameters.size(); ++i) {
        size_t reg_index = i + 1; // +1 for 'this'
        bind_variable(init_method.parameters[i].first, static_cast<Reg>(reg_index));
        set_register_type(static_cast<Reg>(reg_index), nullptr);
    }
    
    // Emit init method body
    if (init_method.body) {
        emit_stmt(*init_method.body);
    }
    
    // Add implicit return if none exists
    if (!cfg_context_.building_cfg) {
        // Linear mode - add implicit return if function doesn't end with return
        if (current_function_->instructions.empty() || 
            !current_function_->instructions.back().isReturn()) {
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, 0, 0, 0));
        }
    }
    
    // Finish CFG building (only if CFG was used)
    if (cfg_context_.building_cfg) {
        if (!validate_cfg()) {
            report_error("CFG validation failed for frame init method: " + full_method_name);
        }
        finish_cfg_build();
    }

    exit_scope();
    this_register_ = UINT32_MAX;  // Clear this_register_
    
    // Convert LIR_Function to LIRFunction and update the registration
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    
    // Create proper LIRFunction from our LIR_Function
    std::vector<LIRParameter> params;
    
    // Add 'this' parameter
    LIRParameter this_param;
    this_param.name = "this";
    this_param.type = Type::Ptr;
    params.push_back(this_param);
    
    // Add init parameters
    for (const auto& param : init_method.parameters) {
        LIRParameter lir_param;
        lir_param.name = param.first;
        // Convert type - for now use I64 as default
        lir_param.type = Type::I64;
        params.push_back(lir_param);
    }
    
    // Create function with I64 return type for now
    auto lir_func = func_manager.createFunction(full_method_name, params, Type::I64, nullptr);
    
    // Copy the instructions from our LIR_Function
    lir_func->setInstructions(result->instructions);

    // Update function table
    auto& func_info = function_table_[full_method_name];
    func_info.lir_function = nullptr; // Not needed since FunctionRegistry manages it
}


void Generator::lower_frame_deinit_method(const std::string& frame_name, LM::Frontend::AST::FrameMethod& deinit_method) {
    // Create a function with the frame deinit method name (frame_name.deinit)
    std::string full_method_name = frame_name + ".deinit";
    
    auto& func_manager = LIRFunctionManager::getInstance();
    
    // Register function signature early for recursive calls
    if (!func_manager.hasFunction(full_method_name)) {
        std::vector<LIRParameter> empty_params;
        auto func = func_manager.createFunction(full_method_name, empty_params, Type::I64, nullptr);
    }
    
    // Create function with only 'this' parameter (deinit takes no other parameters)
    size_t total_params = 1; // Only 'this'
    current_function_ = std::make_unique<LIR_Function>(full_method_name, total_params);
    next_register_ = total_params;
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    enter_scope();
    
    // Use CFG mode for proper JIT compatibility (disabled for now)
    cfg_context_.building_cfg = false;  // DISABLED: CFG linearization has bugs with elif
    cfg_context_.current_block = nullptr;
    
    // Register 'this' parameter as first parameter (register 0)
    this_register_ = 0;  // Set this_register_ for 'this' context
    bind_variable("this", 0);
    auto frame_type = std::make_shared<::Type>(::TypeTag::Frame);
    FrameType ft;
    ft.name = frame_name;
    frame_type->extra = ft;
    set_register_language_type(0, frame_type);
    set_register_abi_type(0, Type::Ptr);
    
    // 1. Recursive cleanup: Call deinit on all frame-typed fields
    auto frame_it = frame_table_.find(frame_name);
    if (frame_it != frame_table_.end()) {
        for (size_t i = 0; i < frame_it->second.fields.size(); ++i) {
            if (frame_it->second.fields[i].second->tag == TypeTag::Frame) {
                Reg field_reg = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::FrameGetField, Type::Ptr, field_reg, 0, static_cast<uint32_t>(i)));
                emit_instruction(LIR_Inst(LIR_Op::FrameCallDeinit, Type::Void, field_reg, 0, 0));
            }
        }
    }

    // Emit deinit method body
    if (deinit_method.body) {
        emit_stmt(*deinit_method.body);
    }
    
    // Add implicit return if none exists
    if (!cfg_context_.building_cfg) {
        // Linear mode - add implicit return if function doesn't end with return
        if (current_function_->instructions.empty() || 
            !current_function_->instructions.back().isReturn()) {
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, 0, 0, 0));
        }
    }
    
    // Finish CFG building (only if CFG was used)
    if (cfg_context_.building_cfg) {
        if (!validate_cfg()) {
            report_error("CFG validation failed for frame deinit method: " + full_method_name);
        }
        finish_cfg_build();
    }

    exit_scope();
    this_register_ = UINT32_MAX;  // Clear this_register_
    
    // Convert LIR_Function to LIRFunction and update the registration
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    
    // Create proper LIRFunction from our LIR_Function
    std::vector<LIRParameter> params;
    
    // Add 'this' parameter
    LIRParameter this_param;
    this_param.name = "this";
    this_param.type = Type::Ptr;
    params.push_back(this_param);
    
    // Create function with I64 return type for now
    auto lir_func = func_manager.createFunction(full_method_name, params, Type::I64, nullptr);
    
    // Copy the instructions from our LIR_Function
    lir_func->setInstructions(result->instructions);

    // Update function table
    auto& func_info = function_table_[full_method_name];
    func_info.lir_function = nullptr; // Not needed since FunctionRegistry manages it
}


void Generator::emit_trait_stmt(LM::Frontend::AST::TraitDeclaration& stmt) {
    // Trait declarations are handled in Pass 0 and Pass 1
}


void Generator::emit_frame_stmt(LM::Frontend::AST::FrameDeclaration& stmt) {
    // Frame declarations are handled in Pass 0 (signature collection)
    // This function is called during Pass 2 but doesn't need to emit anything
    // since the frame layout and methods are already registered
}


} // namespace LIR
} // namespace LM
