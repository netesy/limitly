#include "../generator.hh"
#include "../functions.hh"
#include "../../frontend/module_manager.hh"
#include "../function_registry.hh"
#include "../builtin_functions.hh"
#include "../../frontend/ast.hh"
#include "../../frontend/scanner.hh"
#include <algorithm>
#include <functional>
#include <map>
#include <limits>

using namespace LM::LIR;

namespace LM {
namespace LIR {

namespace {
bool resolve_match_variant_info(TypeSystem* type_system,
                                TypePtr match_type,
                                const std::string& pattern_type_name,
                                int64_t& out_tag,
                                size_t& out_arity) {
    TypePtr enum_type = match_type;
    std::string variant_name = pattern_type_name;

    auto dot_pos = pattern_type_name.find('.');
    if (dot_pos != std::string::npos) {
        std::string enum_name = pattern_type_name.substr(0, dot_pos);
        variant_name = pattern_type_name.substr(dot_pos + 1);
        if (type_system) {
            enum_type = type_system->getType(enum_name);
        }
    }

    if (!enum_type || enum_type->tag != TypeTag::Enum) return false;
    auto* enum_info = std::get_if<EnumType>(&enum_type->extra);
    if (!enum_info) return false;

    auto it = std::find(enum_info->values.begin(), enum_info->values.end(), variant_name);
    if (it == enum_info->values.end()) return false;

    out_tag = static_cast<int64_t>(std::distance(enum_info->values.begin(), it));
    auto arity_it = enum_info->variantTypes.find(variant_name);
    out_arity = (arity_it != enum_info->variantTypes.end()) ? arity_it->second.size() : 0;
    return true;
}
}

void Generator::emit_stmt(LM::Frontend::AST::Statement& stmt) {
   // std::cout << "[DEBUG] emit_stmt called with type: " << typeid(stmt).name() << std::endl;
    
    if (auto expr_stmt = dynamic_cast<LM::Frontend::AST::ExprStatement*>(&stmt)) {
       // std::cout << "[DEBUG] Emitting ExprStatement" << std::endl;
        emit_expr_stmt(*expr_stmt);
    } else if (auto print_stmt = dynamic_cast<LM::Frontend::AST::PrintStatement*>(&stmt)) {
       // std::cout << "[DEBUG] Emitting PrintStatement" << std::endl;
        emit_print_stmt(*print_stmt);
    } else if (auto var_stmt = dynamic_cast<LM::Frontend::AST::VarDeclaration*>(&stmt)) {
        emit_var_stmt(*var_stmt);
    } else if (auto block_stmt = dynamic_cast<LM::Frontend::AST::BlockStatement*>(&stmt)) {
        emit_block_stmt(*block_stmt);
    } else if (auto if_stmt = dynamic_cast<LM::Frontend::AST::IfStatement*>(&stmt)) {
        emit_if_stmt(*if_stmt);
    } else if (auto while_stmt = dynamic_cast<LM::Frontend::AST::WhileStatement*>(&stmt)) {
        emit_while_stmt(*while_stmt);
    } else if (auto for_stmt = dynamic_cast<LM::Frontend::AST::ForStatement*>(&stmt)) {
        emit_for_stmt(*for_stmt);
    } else if (auto iter_stmt = dynamic_cast<LM::Frontend::AST::IterStatement*>(&stmt)) {
        emit_iter_stmt(*iter_stmt);
    } else if (auto break_stmt = dynamic_cast<LM::Frontend::AST::BreakStatement*>(&stmt)) {
        emit_break_stmt(*break_stmt);
    } else if (auto continue_stmt = dynamic_cast<LM::Frontend::AST::ContinueStatement*>(&stmt)) {
        emit_continue_stmt(*continue_stmt);
    } else if (auto return_stmt = dynamic_cast<LM::Frontend::AST::ReturnStatement*>(&stmt)) {
        emit_return_stmt(*return_stmt);
    } else if (auto func_stmt = dynamic_cast<LM::Frontend::AST::FunctionDeclaration*>(&stmt)) {
        emit_func_stmt(*func_stmt);
    } else if (auto import_stmt = dynamic_cast<LM::Frontend::AST::ImportStatement*>(&stmt)) {
        emit_import_stmt(*import_stmt);
    } else if (auto match_stmt = dynamic_cast<LM::Frontend::AST::MatchStatement*>(&stmt)) {
        emit_match_stmt(*match_stmt);
    } else if (auto contract_stmt = dynamic_cast<LM::Frontend::AST::ContractStatement*>(&stmt)) {
        emit_contract_stmt(*contract_stmt);
    } else if (auto comptime_stmt = dynamic_cast<LM::Frontend::AST::ComptimeStatement*>(&stmt)) {
        emit_comptime_stmt(*comptime_stmt);
    } else if (auto parallel_stmt = dynamic_cast<LM::Frontend::AST::ParallelStatement*>(&stmt)) {
        emit_parallel_stmt(*parallel_stmt);
    } else if (auto concurrent_stmt = dynamic_cast<LM::Frontend::AST::ConcurrentStatement*>(&stmt)) {
       // std::cout << "[DEBUG] Emitting ConcurrentStatement" << std::endl;
        emit_concurrent_stmt(*concurrent_stmt);
    } else if (auto task_stmt = dynamic_cast<LM::Frontend::AST::TaskStatement*>(&stmt)) {
        emit_task_stmt(*task_stmt);
    } else if (auto worker_stmt = dynamic_cast<LM::Frontend::AST::WorkerStatement*>(&stmt)) {
        emit_worker_stmt(*worker_stmt);
    } else if (auto unsafe_stmt = dynamic_cast<LM::Frontend::AST::UnsafeStatement*>(&stmt)) {
        emit_unsafe_stmt(*unsafe_stmt);
    } else if (auto trait_stmt = dynamic_cast<LM::Frontend::AST::TraitDeclaration*>(&stmt)) {
        emit_trait_stmt(*trait_stmt);
    } else if (auto frame_stmt = dynamic_cast<LM::Frontend::AST::FrameDeclaration*>(&stmt)) {
        emit_frame_stmt(*frame_stmt);
    } else if (auto module_stmt = dynamic_cast<LM::Frontend::AST::ModuleDeclaration*>(&stmt)) {
        emit_module_stmt(*module_stmt);
    } else if (auto type_decl = dynamic_cast<LM::Frontend::AST::TypeDeclaration*>(&stmt)) {
        // Type aliases don't generate code
    } else if (auto enum_decl = dynamic_cast<LM::Frontend::AST::EnumDeclaration*>(&stmt)) {
        // Enums don't generate code yet
    } else {
        report_error("Unsupported statement type in LIR generator");
    }
}


void Generator::emit_expr_stmt(LM::Frontend::AST::ExprStatement& stmt) {
    emit_expr(*stmt.expression);
}


void Generator::emit_print_stmt(LM::Frontend::AST::PrintStatement& stmt) {
    if (stmt.arguments.empty()) {
        // Empty print statement - just print a newline
        Reg newline_reg = allocate_register();
        auto string_type = std::make_shared<::Type>(::TypeTag::String);
        ValuePtr newline_val = std::make_shared<Value>(string_type, std::string("\n"));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, newline_reg, newline_val));
        emit_instruction(LIR_Inst(LIR_Op::PrintString, Type::Void, 0, newline_reg, 0));
        return;
    }
    
    if (stmt.arguments.size() == 1) {
        // Single argument - print it directly
        Reg value = emit_expr(*stmt.arguments[0]);
        emit_print_value(value);
        return;
    }
    
    // Multiple arguments - concatenate them into a single string
    Reg result_reg = emit_expr(*stmt.arguments[0]);
    
    // Convert first argument to string if it's not already
    TypePtr first_type = get_register_language_type(result_reg);
    if (!first_type || first_type->tag != ::TypeTag::String) {
        Reg str_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::ToString, Type::Ptr, str_reg, result_reg, 0));
        auto string_type = std::make_shared<::Type>(::TypeTag::String);
        set_register_language_type(str_reg, string_type);
        result_reg = str_reg;
    }
    
    // Concatenate remaining arguments
    for (size_t i = 1; i < stmt.arguments.size(); ++i) {
        Reg arg_reg = emit_expr(*stmt.arguments[i]);
        
        // Convert argument to string if it's not already
        TypePtr arg_type = get_register_language_type(arg_reg);
        if (!arg_type || arg_type->tag != ::TypeTag::String) {
            Reg str_arg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ToString, Type::Ptr, str_arg, arg_reg, 0));
            auto string_type = std::make_shared<::Type>(::TypeTag::String);
            set_register_language_type(str_arg, string_type);
            arg_reg = str_arg;
        }
        
        // Add a space between arguments
        if (i > 1 || (first_type && first_type->tag == ::TypeTag::String)) {
            Reg space_reg = allocate_register();
            auto string_type = std::make_shared<::Type>(::TypeTag::String);
            ValuePtr space_val = std::make_shared<Value>(string_type, std::string(" "));
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, space_reg, space_val));
            set_register_language_type(space_reg, string_type);
            
            Reg temp_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::STR_CONCAT, Type::Ptr, temp_reg, result_reg, space_reg));
            set_register_language_type(temp_reg, string_type);
            result_reg = temp_reg;
        }
        
        // Concatenate the argument
        Reg concat_reg = allocate_register();
        auto string_type = std::make_shared<::Type>(::TypeTag::String);
        emit_instruction(LIR_Inst(LIR_Op::STR_CONCAT, Type::Ptr, concat_reg, result_reg, arg_reg));
        set_register_language_type(concat_reg, string_type);
        result_reg = concat_reg;
    }
    
    // Print the final concatenated string
    emit_instruction(LIR_Inst(LIR_Op::PrintString, Type::Void, 0, result_reg, 0));
}


void Generator::emit_print_value(Reg value) {
    // Helper function to print a single value based on its type
    TypePtr reg_type = get_register_language_type(value);
    if (reg_type) {
        switch (reg_type->tag) {
            case ::TypeTag::Int:
            case ::TypeTag::Int8:
            case ::TypeTag::Int16:
            case ::TypeTag::Int32:
            case ::TypeTag::Int64:
                emit_instruction(LIR_Inst(LIR_Op::PrintInt, Type::Void, 0, value, 0));
                break;
            case ::TypeTag::UInt:
            case ::TypeTag::UInt8:
            case ::TypeTag::UInt16:
            case ::TypeTag::UInt32:
            case ::TypeTag::UInt64:
                emit_instruction(LIR_Inst(LIR_Op::PrintUint, Type::Void, 0, value, 0));
                break;
            case ::TypeTag::Float32:
            case ::TypeTag::Float64:
                emit_instruction(LIR_Inst(LIR_Op::PrintFloat, Type::Void, 0, value, 0));
                break;
            case ::TypeTag::Bool:
                emit_instruction(LIR_Inst(LIR_Op::PrintBool, Type::Void, 0, value, 0));
                break;
            case ::TypeTag::String:
                emit_instruction(LIR_Inst(LIR_Op::PrintString, Type::Void, 0, value, 0));
                break;
            default:
                // Convert to string and print
                Reg str_reg = allocate_register();
                // Get the type of the value being converted
                TypePtr val_type = get_register_language_type(value);
                LIR::Type lir_type = language_type_to_abi_type(val_type);
                emit_instruction(LIR_Inst(LIR_Op::ToString, Type::Ptr, str_reg, value, 0, 0, lir_type));
                auto string_type = std::make_shared<::Type>(::TypeTag::String);
                set_register_language_type(str_reg, string_type);
                emit_instruction(LIR_Inst(LIR_Op::PrintString, Type::Void, 0, str_reg, 0));
                break;
        }
    } else {
        // Fallback: Type is unknown (likely Any or unset)
        // Always convert to string first, then print
        // This handles tuples, lists, dicts, and other complex types
        Reg str_reg = allocate_register();
        // Assume unknown types are pointers to collections
        emit_instruction(LIR_Inst(LIR_Op::ToString, Type::Ptr, str_reg, value, 0, 0, LIR::Type::Ptr));
        auto string_type = std::make_shared<::Type>(::TypeTag::String);
        set_register_language_type(str_reg, string_type);
        emit_instruction(LIR_Inst(LIR_Op::PrintString, Type::Void, 0, str_reg, 0));
}
}



void Generator::emit_var_stmt(LM::Frontend::AST::VarDeclaration& stmt) {
   // std::cout << "[DEBUG] emit_var_stmt called for variable: " << stmt.name << std::endl;

    // Check if this is a module-level variable (global)
    if (!current_module_.empty() && current_module_ != "root") {
        std::string qualified_name = current_module_ + "." + stmt.name;
        Reg val_reg = 0;
        if (stmt.initializer) {
            val_reg = emit_expr(*stmt.initializer);
        } else {
            val_reg = allocate_register();
            ValuePtr nil_val = std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Nil), "");
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Void, val_reg, nil_val));
        }
        LIR_Inst store_inst(LIR_Op::StoreGlobal, Type::Void, 0, val_reg, 0);
        store_inst.func_name = qualified_name;
        emit_instruction(store_inst);
        return;
    }

    Reg value_reg;
    
    // Determine the declared type first, before processing the initializer
    TypePtr declared_type = nullptr;
    if (stmt.type.has_value()) {
       // std::cout << "[DEBUG] Variable has explicit type" << std::endl;
        // Convert TypeAnnotation to Type - handle all basic types including 128-bit
        auto type_annotation = *stmt.type.value();
        if (type_annotation.typeName == "u32") {
            declared_type = std::make_shared<::Type>(::TypeTag::UInt32);
        } else if (type_annotation.typeName == "u16") {
            declared_type = std::make_shared<::Type>(::TypeTag::UInt16);
        } else if (type_annotation.typeName == "u8") {
            declared_type = std::make_shared<::Type>(::TypeTag::UInt8);
        } else if (type_annotation.typeName == "u64") {
            declared_type = std::make_shared<::Type>(::TypeTag::UInt64);
        } else if (type_annotation.typeName == "u128") {
            declared_type = std::make_shared<::Type>(::TypeTag::UInt128);
        } else if (type_annotation.typeName == "int") {
            declared_type = std::make_shared<::Type>(::TypeTag::Int64);
        } else if (type_annotation.typeName == "i64") {
            declared_type = std::make_shared<::Type>(::TypeTag::Int64);
        } else if (type_annotation.typeName == "i32") {
            declared_type = std::make_shared<::Type>(::TypeTag::Int32);
        } else if (type_annotation.typeName == "i16") {
            declared_type = std::make_shared<::Type>(::TypeTag::Int16);
        } else if (type_annotation.typeName == "i8") {
            declared_type = std::make_shared<::Type>(::TypeTag::Int8);
        } else if (type_annotation.typeName == "i128") {
            declared_type = std::make_shared<::Type>(::TypeTag::Int128);
        } else if (type_annotation.typeName == "f64") {
            declared_type = std::make_shared<::Type>(::TypeTag::Float64);
        } else if (type_annotation.typeName == "f32") {
            declared_type = std::make_shared<::Type>(::TypeTag::Float32);
        } else if (type_annotation.typeName == "bool") {
            declared_type = std::make_shared<::Type>(::TypeTag::Bool);
        } else if (type_annotation.typeName == "string") {
            declared_type = std::make_shared<::Type>(::TypeTag::String);
        } else if (type_annotation.typeName == "any") {
            declared_type = std::make_shared<::Type>(::TypeTag::Any);
        }
    }
    
   // std::cout << "[DEBUG] Checking if variable has initializer" << std::endl;
    if (stmt.initializer) {
       // std::cout << "[DEBUG] Variable has initializer, processing..." << std::endl;
        // Check if the initializer is a literal - if so, optimize by directly using it
        if (auto literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(stmt.initializer.get())) {
            // For literal initializers, emit the literal with the expected type
            value_reg = emit_literal_expr(*literal, declared_type);
        } else {
            // For non-literal initializers, evaluate and move
           // std::cout << "[DEBUG] Processing non-literal initializer" << std::endl;
            Reg value = emit_expr(*stmt.initializer);
           // std::cout << "[DEBUG] emit_expr completed, value=" << value << std::endl;
            value_reg = allocate_register();
            Type abi_type = language_type_to_abi_type(stmt.inferred_type);
            emit_instruction(LIR_Inst(LIR_Op::Mov, abi_type, value_reg, value, 0));
        }
        
        if (declared_type) {
            set_register_type(value_reg, declared_type);
        } else {
            set_register_type(value_reg, stmt.initializer->inferred_type);
        }
    } else {
        // Initialize with nil
        value_reg = allocate_register();
        auto nil_type = std::make_shared<::Type>(::TypeTag::Nil);
        ValuePtr nil_val = std::make_shared<Value>(nil_type, "");
        Type abi_type = language_type_to_abi_type(stmt.inferred_type);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, abi_type, value_reg, nil_val));
        set_register_type(value_reg, nil_type);
    }
   // std::cout << "[DEBUG] Binding variable: " << stmt.name << " to register " << value_reg << std::endl;
    bind_variable(stmt.name, value_reg);
   // std::cout << "[DEBUG] emit_var_stmt completed for: " << stmt.name << std::endl;
}


void Generator::emit_block_stmt(LM::Frontend::AST::BlockStatement& stmt) {
    enter_scope();
    for (const auto& block_stmt : stmt.statements) {
        emit_stmt(*block_stmt);
    }
    exit_scope();
}


void Generator::emit_if_stmt(LM::Frontend::AST::IfStatement& stmt) {
    if (cfg_context_.building_cfg) {
        // CFG mode: create basic blocks
        emit_if_stmt_cfg(stmt);
    } else {
        // Linear mode: use conditional jumps
        emit_if_stmt_linear(stmt);
    }
}


void Generator::emit_if_stmt_cfg(LM::Frontend::AST::IfStatement& stmt) {
    // CFG mode: create basic blocks
    LIR_BasicBlock* then_block = create_basic_block("if_then");
    LIR_BasicBlock* else_block = stmt.elseBranch ? create_basic_block("if_else") : nullptr;
    LIR_BasicBlock* end_block = create_basic_block("if_end");
    
    // Emit condition check in current block
    Reg condition = emit_expr(*stmt.condition);
    Reg condition_bool = allocate_register();
    
    // For boolean conditions, use them directly
    TypePtr condition_type = get_register_type(condition);
    if (condition_type && condition_type->tag == ::TypeTag::Bool) {
        condition_bool = condition;
    } else {
        // Convert non-boolean condition to boolean
        Reg zero_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int);
        ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, zero_reg, zero_val));
        set_register_type(zero_reg, int_type);
        emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition_bool, condition, zero_reg));
        set_register_type(condition_bool, std::make_shared<::Type>(::TypeTag::Bool));
    }
    
    // Conditional jump: if false, go to else (or end if no else)
    uint32_t false_target = else_block ? else_block->id : end_block->id;
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0, false_target));
    
    // Set up edges from current block
    add_block_edge(get_current_block(), then_block);
    if (else_block) {
        add_block_edge(get_current_block(), else_block);
    } else {
        add_block_edge(get_current_block(), end_block);
    }
    
    // === Then Block ===
    set_current_block(then_block);
    
    // Emit then branch
    if (stmt.thenBranch) {
        emit_stmt(*stmt.thenBranch);
    }
    
    // Jump to end after then branch (only if no terminator already exists)
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, end_block->id));
        add_block_edge(then_block, end_block);  // Add CFG edge
    }
    
    // === Else Block (if present) ===
    if (else_block) {
        set_current_block(else_block);
        
        // Emit else branch
        if (stmt.elseBranch) {
            emit_stmt(*stmt.elseBranch);
        }
        
        // Jump to end after else branch (only if no terminator already exists)
        // This is important: we only jump if the current block doesn't already have a terminator
        // (like a return statement from a nested if)
        LIR_BasicBlock* current = get_current_block();
        if (current && !current->has_terminator()) {
            emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, end_block->id));
            add_block_edge(current, end_block);  // Add CFG edge
        }
    }
    
    // === End Block: continuation ===
    set_current_block(end_block);
    
    // Don't mark end_block as terminated - it's a continuation point for subsequent statements
    // Only mark as terminated if it has explicit terminator instructions
    if (end_block && end_block->has_terminator()) {
        end_block->terminated = true;
    }
}



void Generator::emit_if_stmt_linear(LM::Frontend::AST::IfStatement& stmt) {
    // Emit condition
    Reg condition = emit_expr(*stmt.condition);
    Reg condition_bool = allocate_register();
    
    // Convert condition to boolean if needed
    TypePtr condition_type = get_register_type(condition);
    if (condition_type && condition_type->tag == ::TypeTag::Bool) {
        condition_bool = condition;
    } else {
        // Convert non-boolean condition to boolean
        Reg zero_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int);
        ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, zero_reg, zero_val));
        set_register_type(zero_reg, int_type);
        emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition_bool, condition, zero_reg));
        set_register_type(condition_bool, std::make_shared<::Type>(::TypeTag::Bool));
    }
    
    // Reserve space for jump instructions
    size_t false_jump_pc = current_function_->instructions.size();
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0)); // Placeholder target
    
    // Emit then branch
    emit_stmt(*stmt.thenBranch);
    
    if (stmt.elseBranch) {
        // Reserve space for jump to end
        size_t end_jump_pc = current_function_->instructions.size();
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0)); // Placeholder target
        
        // Update false jump to point to else branch
        size_t else_start_pc = current_function_->instructions.size();
        current_function_->instructions[false_jump_pc].imm = else_start_pc;
        
        // Emit else branch
        emit_stmt(*stmt.elseBranch);
        
        // Update end jump to point after else branch
        size_t end_pc = current_function_->instructions.size();
        current_function_->instructions[end_jump_pc].imm = end_pc;
    } else {
        // No else branch - the false jump should skip the then branch
        // The target should be the next instruction after the then branch
        size_t end_pc = current_function_->instructions.size();
        current_function_->instructions[false_jump_pc].imm = end_pc;
    }
}


void Generator::emit_while_stmt(LM::Frontend::AST::WhileStatement& stmt) {
    if (cfg_context_.building_cfg) {
        // CFG mode: create basic blocks
        emit_while_stmt_cfg(stmt);
    } else {
        // Linear mode: use loop instructions
        emit_while_stmt_linear(stmt);
    }
}


void Generator::emit_while_stmt_cfg(LM::Frontend::AST::WhileStatement& stmt) {
    // CFG mode: create basic blocks for while loop
    enter_scope();
    enter_loop();
    
    LIR_BasicBlock* header_block = create_basic_block("while_header");
    LIR_BasicBlock* body_block = create_basic_block("while_body");
    LIR_BasicBlock* end_block = create_basic_block("while_end");
    
    // Set loop labels for break/continue
    set_loop_labels(header_block->id, end_block->id, header_block->id);
    
    // Connect current block to header block
    add_block_edge(get_current_block(), header_block);
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    
    // Emit condition check in header block
    set_current_block(header_block);
    
    // Emit loop condition
    Reg condition = emit_expr(*stmt.condition);
    Reg condition_bool = allocate_register();
    
    // For boolean conditions, use them directly
    TypePtr condition_type = get_register_type(condition);
    if (condition_type && condition_type->tag == ::TypeTag::Bool) {
        condition_bool = condition;
    } else {
        // Convert non-boolean condition to boolean
        Reg zero_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int);
        ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, zero_reg, zero_val));
        set_register_type(zero_reg, int_type);
        emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition_bool, condition, zero_reg));
        set_register_type(condition_bool, std::make_shared<::Type>(::TypeTag::Bool));
    }
    
    // Conditional jump: if false, exit loop
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0, end_block->id));
    
    // Set up edges from header block
    add_block_edge(header_block, body_block);  // Continue if true
    add_block_edge(header_block, end_block);   // Exit if false
    
    // === Body Block ===
    set_current_block(body_block);
    
    // Emit loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Jump back to header to continue loop
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
        add_block_edge(body_block, header_block);
    }
    
    // === End Block: continuation ===
    set_current_block(end_block);
    
    exit_loop();
    exit_scope();
    
    // Don't mark end_block as terminated - it's a continuation point for subsequent statements
    // Only mark as terminated if it has explicit terminator instructions
    if (end_block && end_block->has_terminator()) {
        end_block->terminated = true;
    }
}


void Generator::emit_while_stmt_linear(LM::Frontend::AST::WhileStatement& stmt) {
    Imm cond_label = (Imm)current_function_->instructions.size();
    Reg cond_reg = emit_expr(*stmt.condition);
    
    size_t jump_to_patch = current_function_->instructions.size();
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, Type::Void, 0, cond_reg, 0, 0));

    if (stmt.body) emit_stmt(*stmt.body);

    emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, cond_label));

    Imm end_label = (Imm)current_function_->instructions.size();
    current_function_->instructions[jump_to_patch].imm = end_label;
}


void Generator::emit_for_stmt(LM::Frontend::AST::ForStatement& stmt) {
    if (cfg_context_.building_cfg) {
        // CFG mode: create basic blocks
        emit_for_stmt_cfg(stmt);
    } else {
        // Linear mode: use loop instructions
        emit_for_stmt_linear(stmt);
    }
}


void Generator::emit_for_stmt_cfg(LM::Frontend::AST::ForStatement& stmt) {
    // CFG mode: create basic blocks for for loop
    enter_scope();
    enter_loop();
    
    LIR_BasicBlock* init_block = create_basic_block("for_init");
    LIR_BasicBlock* header_block = create_basic_block("for_header");
    LIR_BasicBlock* body_block = create_basic_block("for_body");
    LIR_BasicBlock* increment_block = create_basic_block("for_increment");
    LIR_BasicBlock* end_block = create_basic_block("for_end");
    
    // Set loop labels for break/continue
    set_loop_labels(header_block->id, end_block->id, increment_block->id);
    
    // Connect current block to init block
    add_block_edge(get_current_block(), init_block);
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, init_block->id));
    
    // === Init Block (executed only once) ===
    set_current_block(init_block);
    
    if (stmt.initializer) {
        emit_stmt(*stmt.initializer);
    }
    
    // Jump to header after initialization
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(init_block, header_block);
    
    // === Header Block (executed each iteration) ===
    set_current_block(header_block);
    
    // Emit condition check
    Reg condition = allocate_register();
    if (stmt.condition) {
        Reg condition_expr = emit_expr(*stmt.condition);
        
        // For boolean conditions, use them directly
        TypePtr condition_type = get_register_type(condition_expr);
        if (condition_type && condition_type->tag == ::TypeTag::Bool) {
            condition = condition_expr;
        } else {
            // Convert non-boolean condition to boolean
            Reg zero_reg = allocate_register();
            auto int_type = std::make_shared<::Type>(::TypeTag::Int);
            ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, zero_reg, zero_val));
            set_register_type(zero_reg, int_type);
            emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition, condition_expr, zero_reg));
            set_register_type(condition, std::make_shared<::Type>(::TypeTag::Bool));
        }
    } else {
        // No condition - always true
        auto bool_type = std::make_shared<::Type>(::TypeTag::Bool);
        ValuePtr true_val = std::make_shared<Value>(bool_type, true);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Bool, condition, true_val));
        set_register_type(condition, bool_type);
    }
    
    // Conditional jump: if false, exit loop
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition, 0, end_block->id));
    
    // Set up edges from header block
    add_block_edge(header_block, body_block);  // Continue if true
    add_block_edge(header_block, end_block);   // Exit if false
    
    // === Body Block ===
    set_current_block(body_block);
    
    // Emit loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Jump to increment block
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, increment_block->id));
        add_block_edge(body_block, increment_block);
    }
    
    // === Increment Block ===
    set_current_block(increment_block);
    
    // Emit increment - for loop increment is typically an assignment expression
    if (stmt.increment) {
        // Create an expression statement from increment expression
        LM::Frontend::AST::ExprStatement expr_stmt;
        expr_stmt.expression = stmt.increment;
        emit_stmt(expr_stmt);
    }
    
    // Jump back to header to continue loop
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
        add_block_edge(increment_block, header_block);
    }
    
    // === End Block: continuation ===
    set_current_block(end_block);
    
    exit_loop();
    exit_scope();
    
    // Don't mark end_block as terminated - it's a continuation point for subsequent statements
    // Only mark as terminated if it has explicit terminator instructions
    if (end_block && end_block->has_terminator()) {
        end_block->terminated = true;
    }
}


void Generator::emit_for_stmt_linear(LM::Frontend::AST::ForStatement& stmt) {
    enter_scope();
    if (stmt.initializer) emit_stmt(*stmt.initializer);
    
    Imm cond_label = (Imm)current_function_->instructions.size();
    Reg cond_reg = 0;
    size_t jump_to_patch = 0;
    bool has_cond = false;
    
    if (stmt.condition) {
        cond_reg = emit_expr(*stmt.condition);
        jump_to_patch = current_function_->instructions.size();
        emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, Type::Void, 0, cond_reg, 0, 0));
        has_cond = true;
    }
    
    if (stmt.body) emit_stmt(*stmt.body);
    if (stmt.increment) emit_expr(*stmt.increment);

    emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, cond_label));

    if (has_cond) {
        Imm end_label = (Imm)current_function_->instructions.size();
        current_function_->instructions[jump_to_patch].imm = end_label;
    }
    exit_scope();
}


void Generator::emit_return_stmt(LM::Frontend::AST::ReturnStatement& stmt) {
    if (else_context_.in_else_block) {
        // Inside an else block - store the value in the result register instead of returning
        if (stmt.value) {
            Reg value = emit_expr(*stmt.value);
            // Move the value to the result register
            emit_instruction(LIR_Inst(LIR_Op::Mov, Type::I64, else_context_.result_register, value, 0));
        } else {
            // No value - store a default value (0)
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, else_context_.result_register, 0, 0));
        }
        // Don't emit a return instruction - let the else block continue
    } else {
        // Normal return statement
        if (stmt.value) {
            Reg value = emit_expr(*stmt.value);
            emit_instruction(LIR_Inst(LIR_Op::Return, value));
        } else {
            emit_instruction(LIR_Inst(LIR_Op::Return));
        }
    }
}


void Generator::emit_func_stmt(LM::Frontend::AST::FunctionDeclaration& stmt) {
   // std::cout << "[DEBUG] LIR Generator: Processing function declaration '" << stmt.name << "'" << std::endl;
    
    // Collect parameter registers
    std::vector<Reg> param_regs;
    for (size_t i = 0; i < stmt.params.size(); ++i) {
        param_regs.push_back(static_cast<Reg>(i));
    }
    
    // Determine return register (if function has return type)
    Reg return_reg = 0;
    if (stmt.returnType.has_value()) {
        return_reg = static_cast<Reg>(stmt.params.size()); // Return register comes after parameters
    }
    
    // Emit function definition using new format: fn r2, add(r0, r1) {
    emit_instruction(LIR_Inst(LIR_Op::FuncDef, stmt.name, param_regs, return_reg));
    
    // Generate function body (this will be handled by the separate function generation pass)
}


void Generator::emit_import_stmt(LM::Frontend::AST::ImportStatement& stmt) {
    // Smart import resolution - just update alias map, no LIR emission
    std::string alias = stmt.alias.value_or(stmt.modulePath);
    import_aliases_[alias] = stmt.modulePath;
    
   // std::cout << "[DEBUG] Import registered: " << alias << " -> " << stmt.modulePath << std::endl;
}


void Generator::emit_contract_stmt(LM::Frontend::AST::ContractStatement& stmt) {
    report_error("Contract statements not yet implemented");
}


void Generator::emit_comptime_stmt(LM::Frontend::AST::ComptimeStatement& stmt) {
    report_error("Comptime statements not yet implemented");
}


void Generator::emit_iter_stmt(LM::Frontend::AST::IterStatement& stmt) {
    auto range_expr = dynamic_cast<LM::Frontend::AST::RangeExpr*>(stmt.iterable.get());
    auto var_expr = dynamic_cast<LM::Frontend::AST::VariableExpr*>(stmt.iterable.get());
    auto list_expr = dynamic_cast<LM::Frontend::AST::ListExpr*>(stmt.iterable.get());
    auto dict_expr = dynamic_cast<LM::Frontend::AST::DictExpr*>(stmt.iterable.get());
    auto tuple_expr = dynamic_cast<LM::Frontend::AST::TupleExpr*>(stmt.iterable.get());
    
    if (range_expr) {
        // Handle range iteration (existing logic)
        if (stmt.loopVars.size() != 1) {
            report_error("iter statement currently supports only one loop variable");
            return;
        }
        const std::string& loop_var_name = stmt.loopVars[0];

        LIR_BasicBlock* header_block = create_basic_block("iter_header");
        LIR_BasicBlock* body_block = create_basic_block("iter_body");
        LIR_BasicBlock* increment_block = create_basic_block("iter_increment");
        LIR_BasicBlock* exit_block = create_basic_block("iter_exit");

        enter_scope();
        enter_loop();
        set_loop_labels(header_block->id, exit_block->id, increment_block->id);

        Reg loop_var_reg = allocate_register();
        bind_variable(loop_var_name, loop_var_reg);

        Reg start_reg = emit_expr(*range_expr->start);
        emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, start_reg, 0));
        set_register_type(loop_var_reg, get_register_type(start_reg));

        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
        add_block_edge(get_current_block(), header_block);

        set_current_block(header_block);
        Reg end_reg = emit_expr(*range_expr->end);
        Reg cmp_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, loop_var_reg, end_reg));
        set_register_type(cmp_reg, std::make_shared<::Type>(::TypeTag::Bool));
        emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, exit_block->id));
        add_block_edge(header_block, body_block);
        add_block_edge(header_block, exit_block);

        set_current_block(body_block);
        if (stmt.body) {
            emit_stmt(*stmt.body);
        }
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, increment_block->id));
        add_block_edge(body_block, increment_block);

        set_current_block(increment_block);
        Reg step_reg;
        if (range_expr->step) {
            step_reg = emit_expr(*range_expr->step);
        } else {
            step_reg = allocate_register();
            auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
            ValuePtr one_val = std::make_shared<Value>(int_type, (int64_t)1);
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, step_reg, one_val));
            set_register_type(step_reg, int_type);
        }
        Reg new_val_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::Add, new_val_reg, loop_var_reg, step_reg));
        emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, new_val_reg, 0));
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
        add_block_edge(increment_block, header_block);

        set_current_block(exit_block);
        exit_loop();
        exit_scope();
        
    } else if (list_expr) {
        emit_list_iter_stmt(stmt, *list_expr);
        
    } else if (dict_expr) {
        emit_dict_iter_stmt(stmt, *dict_expr);
        
    } else if (tuple_expr) {
        emit_tuple_iter_stmt(stmt, *tuple_expr);
        
    } else if (var_expr) {
        // Handle variable-based iteration (could be list, dict, tuple, or channel)
        // Note: We allow multiple loop variables for dictionary iteration

        // Get the variable and check its type
        Reg iterable_reg = resolve_variable(var_expr->name);
        if (iterable_reg == UINT32_MAX) {
            report_error("Undefined variable: " + var_expr->name);
            return;
        }

        // Get the type of the iterable variable
        TypePtr iterable_type = get_register_type(iterable_reg);
        if (!iterable_type) {
            report_error("Cannot determine type of variable: " + var_expr->name);
            return;
        }

        // Check if it's a list, dict, tuple, or channel
        if (iterable_type->tag == TypeTag::List) {
            emit_list_var_iter_stmt(stmt, iterable_reg);
            
        } else if (iterable_type->tag == TypeTag::Dict) {
            emit_dict_var_iter_stmt(stmt, iterable_reg);
            
        } else if (iterable_type->tag == TypeTag::Tuple) {
            // Get tuple size from type system
            auto* tuple_type_ptr = std::get_if<TupleType>(&iterable_type->extra);
            if (tuple_type_ptr) {
                int64_t tuple_len = static_cast<int64_t>(tuple_type_ptr->elementTypes.size());
                emit_tuple_var_iter_stmt(stmt, iterable_reg, tuple_len);
            } else {
                emit_tuple_var_iter_stmt(stmt, iterable_reg, 0);
            }
            
        } else {
            // Handle channel iteration - requires exactly one loop variable
            if (stmt.loopVars.size() != 1) {
                report_error("channel iteration requires exactly one loop variable");
                return;
            }
            const std::string& loop_var_name = stmt.loopVars[0];
            
            // Handle channel iteration (existing logic)
            LIR_BasicBlock* header_block = create_basic_block("channel_iter_header");
            LIR_BasicBlock* body_block = create_basic_block("channel_iter_body");
            LIR_BasicBlock* exit_block = create_basic_block("channel_iter_exit");

            enter_scope();
            enter_loop();
            set_loop_labels(header_block->id, exit_block->id, 0);

            // Bind loop variable
            Reg loop_var_reg = allocate_register();
            bind_variable(loop_var_name, loop_var_reg);

            // Jump to header
            emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
            add_block_edge(get_current_block(), header_block);

            set_current_block(header_block);
            // Non-blocking channel poll
            Reg poll_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ChannelPoll, poll_reg, iterable_reg, 0));
            set_register_type(poll_reg, std::make_shared<::Type>(::TypeTag::Any));
            
            // Create nil constant for comparison
            Reg nil_reg = allocate_register();
            auto nil_type = std::make_shared<::Type>(::TypeTag::Nil);
            ValuePtr nil_val = std::make_shared<Value>(nil_type, std::string("nil"));
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Void, nil_reg, nil_val));
            set_register_type(nil_reg, nil_type);
            
            // Compare poll result with nil
            Reg is_nil_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::CmpEQ, is_nil_reg, poll_reg, nil_reg));
            set_register_type(is_nil_reg, std::make_shared<::Type>(::TypeTag::Bool));
            
            // Jump to exit if poll result is nil (channel empty/closed)
            emit_instruction(LIR_Inst(LIR_Op::JumpIf, 0, is_nil_reg, 0, exit_block->id));
            add_block_edge(header_block, body_block);
            add_block_edge(header_block, exit_block);

            set_current_block(body_block);
            // Use the polled value
            emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, poll_reg, 0));
            set_register_type(loop_var_reg, std::make_shared<::Type>(::TypeTag::Any));
            
            // Execute loop body
            if (stmt.body) {
                emit_stmt(*stmt.body);
            }
            
            // Jump back to header
            emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
            add_block_edge(body_block, header_block);

            set_current_block(exit_block);
            exit_loop();
            exit_scope();
        }
        
    } else {
        report_error("iter statement supports range expressions, lists, dicts, tuples, and channel variables");
    }
}


void Generator::emit_dict_iter_stmt(LM::Frontend::AST::IterStatement& stmt, LM::Frontend::AST::DictExpr& dict_expr) {
    // Handle dict iteration (simplified - iterate over keys)
    if (stmt.loopVars.size() != 1) {
        report_error("dict iteration currently supports only one loop variable");
        return;
    }
    const std::string& loop_var_name = stmt.loopVars[0];

    LIR_BasicBlock* header_block = create_basic_block("dict_iter_header");
    LIR_BasicBlock* body_block = create_basic_block("dict_iter_body");
    LIR_BasicBlock* exit_block = create_basic_block("dict_iter_exit");

    enter_scope();
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, 0);

    // Create the dict
    Reg dict_reg = emit_dict_expr(dict_expr);
    
    // Bind loop variable
    Reg loop_var_reg = allocate_register();
    bind_variable(loop_var_name, loop_var_reg);

    // Initialize index to 0
    Reg index_reg = allocate_register();
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, zero_val));
    set_register_type(index_reg, int_type);

    // Jump to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);

    set_current_block(header_block);
    
    // Get dict size using entry count from AST
    Reg size_reg = allocate_register();
    auto size_type = std::make_shared<::Type>(::TypeTag::Int64);
    ValuePtr size_val = std::make_shared<Value>(size_type, int64_t(dict_expr.entries.size()));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, size_reg, size_val));
    set_register_type(size_reg, size_type);
    
    // Compare index with size
    Reg cmp_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, index_reg, size_reg));
    set_register_type(cmp_reg, std::make_shared<::Type>(::TypeTag::Bool));
    
    // Jump to exit if index >= size
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, exit_block->id));
    add_block_edge(header_block, body_block);
    add_block_edge(header_block, exit_block);

    set_current_block(body_block);
    
    // For a more realistic implementation, we need to extract keys from the dict at runtime
    // For now, we'll use a simplified approach that creates keys based on the index
    // In a full implementation, this would involve proper dict key extraction methods
    
    // Extract key from dict at current index
    Reg key_reg = allocate_register();
    auto key_type = std::make_shared<::Type>(::TypeTag::String);
    LIR_Inst call_inst(LIR_Op::DictItems, Type::Ptr, key_reg, 0);
    call_inst.call_args = {dict_reg, index_reg};
    emit_instruction(call_inst);
    set_register_type(key_reg, key_type);
    
    // Move key to loop variable
    emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, key_reg, 0));
    set_register_type(loop_var_reg, key_type);
    
    // Execute loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Increment index
    Reg one_reg = allocate_register();
    ValuePtr one_val = std::make_shared<Value>(int_type, int64_t(1));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, one_reg, one_val));
    set_register_type(one_reg, int_type);
    
    Reg new_index_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::Add, new_index_reg, index_reg, one_reg));
    emit_instruction(LIR_Inst(LIR_Op::Mov, index_reg, new_index_reg, 0));
    
    // Jump back to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(body_block, header_block);

    set_current_block(exit_block);
    exit_loop();
    exit_scope();
}


void Generator::emit_list_iter_stmt(LM::Frontend::AST::IterStatement& stmt, LM::Frontend::AST::ListExpr& list_expr) {
    // Handle list iteration
    if (stmt.loopVars.size() != 1) {
        report_error("list iteration currently supports only one loop variable");
        return;
    }
    const std::string& loop_var_name = stmt.loopVars[0];

    LIR_BasicBlock* header_block = create_basic_block("list_iter_header");
    LIR_BasicBlock* body_block = create_basic_block("list_iter_body");
    LIR_BasicBlock* exit_block = create_basic_block("list_iter_exit");

    enter_scope();
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, 0);

    // Create the list
    Reg list_reg = emit_list_expr(list_expr);
    
    // Bind loop variable
    Reg loop_var_reg = allocate_register();
    bind_variable(loop_var_name, loop_var_reg);

    // Initialize index to 0
    Reg index_reg = allocate_register();
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, zero_val));
    set_register_type(index_reg, int_type);

    // Jump to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);

    set_current_block(header_block);
    
    // Get list length using element count from AST
    Reg len_reg = allocate_register();
    auto len_type = std::make_shared<::Type>(::TypeTag::Int64);
    ValuePtr len_val = std::make_shared<Value>(len_type, int64_t(list_expr.elements.size()));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, len_reg, len_val));
    set_register_type(len_reg, len_type);
    
    // Compare index with length
    Reg cmp_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, index_reg, len_reg));
    set_register_type(cmp_reg, std::make_shared<::Type>(::TypeTag::Bool));
    
    // Jump to exit if index >= length
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, exit_block->id));
    add_block_edge(header_block, body_block);
    add_block_edge(header_block, exit_block);

    set_current_block(body_block);
    
    // Get element at current index
    Reg elem_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::ListIndex, Type::Ptr, elem_reg, list_reg, index_reg));
    set_register_type(elem_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Move element to loop variable
    emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, elem_reg, 0));
    set_register_type(loop_var_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Execute loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Increment index
    Reg one_reg = allocate_register();
    ValuePtr one_val = std::make_shared<Value>(int_type, int64_t(1));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, one_reg, one_val));
    set_register_type(one_reg, int_type);
    
    Reg new_index_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::Add, new_index_reg, index_reg, one_reg));
    emit_instruction(LIR_Inst(LIR_Op::Mov, index_reg, new_index_reg, 0));
    
    // Jump back to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(body_block, header_block);

    set_current_block(exit_block);
    exit_loop();
    exit_scope();
}


void Generator::emit_tuple_iter_stmt(LM::Frontend::AST::IterStatement& stmt, LM::Frontend::AST::TupleExpr& tuple_expr) {
    // Handle tuple iteration (similar to list)
    if (stmt.loopVars.size() != 1) {
        report_error("tuple iteration currently supports only one loop variable");
        return;
    }
    const std::string& loop_var_name = stmt.loopVars[0];

    LIR_BasicBlock* header_block = create_basic_block("tuple_iter_header");
    LIR_BasicBlock* body_block = create_basic_block("tuple_iter_body");
    LIR_BasicBlock* exit_block = create_basic_block("tuple_iter_exit");

    enter_scope();
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, 0);

    // Create the tuple
    Reg tuple_reg = emit_tuple_expr(tuple_expr);
    
    // Bind loop variable
    Reg loop_var_reg = allocate_register();
    bind_variable(loop_var_name, loop_var_reg);

    // Initialize index to 0
    Reg index_reg = allocate_register();
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, zero_val));
    set_register_type(index_reg, int_type);

    // Jump to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);

    set_current_block(header_block);
    
    // Get tuple size from type system instead of parameter
    Reg len_reg = allocate_register();
    auto len_type = std::make_shared<::Type>(::TypeTag::Int64);
    
    // Extract tuple size from register type
    int64_t tuple_len = tuple_expr.elements.size(); // Default fallback
    
    ValuePtr len_val = std::make_shared<Value>(len_type, tuple_len);
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, len_reg, len_val));
    set_register_type(len_reg, len_type);
    
    // Compare index with length
    Reg cmp_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, index_reg, len_reg));
    set_register_type(cmp_reg, std::make_shared<::Type>(::TypeTag::Bool));
    
    // Jump to exit if index >= length
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, exit_block->id));
    add_block_edge(header_block, body_block);
    add_block_edge(header_block, exit_block);

    set_current_block(body_block);
    
    // Get element at current index (tuples use list_index internally)
    Reg elem_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::TupleGet, Type::Ptr, elem_reg, tuple_reg, index_reg));
    set_register_type(elem_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Move element to loop variable
    emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, elem_reg, 0));
    set_register_type(loop_var_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Execute loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Increment index
    Reg one_reg = allocate_register();
    ValuePtr one_val = std::make_shared<Value>(int_type, int64_t(1));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, one_reg, one_val));
    set_register_type(one_reg, int_type);
    
    Reg new_index_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::Add, new_index_reg, index_reg, one_reg));
    emit_instruction(LIR_Inst(LIR_Op::Mov, index_reg, new_index_reg, 0));
    
    // Jump back to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(body_block, header_block);

    set_current_block(exit_block);
    exit_loop();
    exit_scope();
}


void Generator::emit_dict_var_iter_stmt(LM::Frontend::AST::IterStatement& stmt, Reg dict_reg) {
    // Convert dict to list of tuples using DictItems operation
    // The runtime does the heavy lifting (walking the hash table)
    LIR::Reg items_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::DictItems, Type::Ptr, items_reg, dict_reg));
    
    // Iterate the list normally using existing list iteration
    emit_list_var_iter_stmt(stmt, items_reg);
}


void Generator::emit_list_var_iter_stmt(LM::Frontend::AST::IterStatement& stmt, Reg list_reg) {
    // Handle list iteration for variables
    if (stmt.loopVars.size() != 1) {
        report_error("list iteration currently supports only one loop variable");
        return;
    }
    const std::string& loop_var_name = stmt.loopVars[0];

    // Check if this is actually a tuple
    TypePtr iterable_type = get_register_type(list_reg);
    bool is_tuple = iterable_type && iterable_type->tag == TypeTag::Tuple;

    LIR_BasicBlock* header_block = create_basic_block("list_var_iter_header");
    LIR_BasicBlock* body_block = create_basic_block("list_var_iter_body");
    LIR_BasicBlock* exit_block = create_basic_block("list_var_iter_exit");

    enter_scope();
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, 0);

    // Bind loop variable
    Reg loop_var_reg = allocate_register();
    bind_variable(loop_var_name, loop_var_reg);

    // Initialize index to 0
    Reg index_reg = allocate_register();
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, zero_val));
    set_register_type(index_reg, int_type);

    // Jump to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);

    set_current_block(header_block);
    
    // Get the actual list length using ListLen operation
    Reg len_reg = allocate_register();
    auto len_type = std::make_shared<::Type>(::TypeTag::Int64);
    emit_instruction(LIR_Inst(LIR_Op::ListLen, Type::I64, len_reg, list_reg));
    set_register_type(len_reg, len_type);
    
    // Compare index with length
    Reg cmp_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, index_reg, len_reg));
    set_register_type(cmp_reg, std::make_shared<::Type>(::TypeTag::Bool));
    
    // Jump to exit if index >= length
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, exit_block->id));
    add_block_edge(header_block, body_block);
    add_block_edge(header_block, exit_block);

    set_current_block(body_block);
    
    // Get element at current index
    Reg elem_reg = allocate_register();
    if (is_tuple) {
        emit_instruction(LIR_Inst(LIR_Op::TupleGet, Type::Ptr, elem_reg, list_reg, index_reg));
    } else {
        emit_instruction(LIR_Inst(LIR_Op::ListIndex, Type::Ptr, elem_reg, list_reg, index_reg));
    }
    set_register_type(elem_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Move element to loop variable
    emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, elem_reg, 0));
    set_register_type(loop_var_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Execute loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Increment index
    Reg one_reg = allocate_register();
    ValuePtr one_val = std::make_shared<Value>(int_type, int64_t(1));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, one_reg, one_val));
    set_register_type(one_reg, int_type);
    
    Reg new_index_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::Add, new_index_reg, index_reg, one_reg));
    emit_instruction(LIR_Inst(LIR_Op::Mov, index_reg, new_index_reg, 0));
    
    // Jump back to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(body_block, header_block);

    set_current_block(exit_block);
    exit_loop();
    exit_scope();
}


void Generator::emit_tuple_var_iter_stmt(LM::Frontend::AST::IterStatement& stmt, Reg tuple_reg, int64_t tuple_len) {
    // Handle tuple iteration for variables (similar to list)
    if (stmt.loopVars.size() != 1) {
        report_error("tuple iteration currently supports only one loop variable");
        return;
    }
    const std::string& loop_var_name = stmt.loopVars[0];

    LIR_BasicBlock* header_block = create_basic_block("tuple_var_iter_header");
    LIR_BasicBlock* body_block = create_basic_block("tuple_var_iter_body");
    LIR_BasicBlock* exit_block = create_basic_block("tuple_var_iter_exit");

    enter_scope();
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, 0);

    // Bind loop variable
    Reg loop_var_reg = allocate_register();
    bind_variable(loop_var_name, loop_var_reg);

    // Initialize index to 0
    Reg index_reg = allocate_register();
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, zero_val));
    set_register_type(index_reg, int_type);

    // Jump to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);

    set_current_block(header_block);
    
    Reg len_reg = allocate_register();
    auto len_type = std::make_shared<::Type>(::TypeTag::Int64);
    if (tuple_len > 0) {
        ValuePtr len_val = std::make_shared<Value>(len_type, tuple_len);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, len_reg, len_val));
    } else {
        // If tuple_len is 0, we can use TupleLen op if available, or assume it is known at runtime
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, len_reg, std::make_shared<Value>(len_type, int64_t(0))));
    }
    set_register_type(len_reg, len_type);
    
    // Compare index with length
    Reg cmp_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, index_reg, len_reg));
    set_register_type(cmp_reg, std::make_shared<::Type>(::TypeTag::Bool));
    
    // Jump to exit if index >= length
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, exit_block->id));
    add_block_edge(header_block, body_block);
    add_block_edge(header_block, exit_block);

    set_current_block(body_block);
    
    // Get element at current index (tuples use list_index internally)
    Reg elem_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::TupleGet, Type::Ptr, elem_reg, tuple_reg, index_reg));
    set_register_type(elem_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Move element to loop variable
    emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, elem_reg, 0));
    set_register_type(loop_var_reg, std::make_shared<::Type>(::TypeTag::Any));
    
    // Execute loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Increment index
    Reg one_reg = allocate_register();
    ValuePtr one_val = std::make_shared<Value>(int_type, int64_t(1));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, one_reg, one_val));
    set_register_type(one_reg, int_type);
    
    Reg new_index_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::Add, new_index_reg, index_reg, one_reg));
    emit_instruction(LIR_Inst(LIR_Op::Mov, index_reg, new_index_reg, 0));
    
    // Jump back to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(body_block, header_block);

    set_current_block(exit_block);
    exit_loop();
    exit_scope();
}


void Generator::emit_break_stmt(LM::Frontend::AST::BreakStatement& stmt) {
    uint32_t break_label = get_break_label();
    if (break_label != 0) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, break_label));
        // Add edge to break target block
        LIR_BasicBlock* break_target = current_function_->cfg->get_block(break_label);
        if (break_target) {
            add_block_edge(get_current_block(), break_target);
        }
        // Mark current block as terminated to prevent further instruction generation
        if (get_current_block()) {
            get_current_block()->terminated = true;
        }
    }
}


void Generator::emit_continue_stmt(LM::Frontend::AST::ContinueStatement& stmt) {
    uint32_t continue_label = get_continue_label();
    if (continue_label != 0) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, continue_label));
        // Add edge to continue target block
        LIR_BasicBlock* continue_target = current_function_->cfg->get_block(continue_label);
        if (continue_target) {
            add_block_edge(get_current_block(), continue_target);
        }
        // Mark current block as terminated to prevent further instruction generation
        if (get_current_block()) {
            get_current_block()->terminated = true;
        }
    }
}


void Generator::emit_unsafe_stmt(LM::Frontend::AST::UnsafeStatement& stmt) {
    report_error("Unsafe statements not yet implemented");
}



void Generator::emit_match_stmt(LM::Frontend::AST::MatchStatement& stmt) {
    if (!stmt.value) return;
    Reg value_reg = emit_expr(*stmt.value);
    std::vector<size_t> end_jumps;

    auto i64_type = std::make_shared<::Type>(::TypeTag::Int64);

    for (size_t i = 0; i < stmt.cases.size(); ++i) {
        const auto& match_case = stmt.cases[i];
        enter_scope();
        std::vector<size_t> fail_jumps;

        // Pattern Check
        if (auto literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(match_case.pattern.get())) {
            if (!std::holds_alternative<std::nullptr_t>(literal->value)) {
                Reg literal_reg = emit_expr(*literal);
                Reg cmp = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::CmpEQ, cmp, value_reg, literal_reg));
                fail_jumps.push_back(current_function_->instructions.size());
                emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp, 0));
            }
        } else if (auto var_expr = dynamic_cast<LM::Frontend::AST::VariableExpr*>(match_case.pattern.get())) {
            if (var_expr->name != "_") {
                bind_variable(var_expr->name, value_reg);
            }
        } else if (auto binding = dynamic_cast<LM::Frontend::AST::BindingPatternExpr*>(match_case.pattern.get())) {
            int64_t tag = 0; size_t arity = 0;
            TypePtr m_type = stmt.value->inferred_type;
            if (m_type && resolve_match_variant_info(type_system_.get(), m_type, binding->typeName, tag, arity)) {
                Reg tag_reg = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::GetTag, Type::I64, tag_reg, value_reg));
                Reg expected = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, expected, std::make_shared<Value>(i64_type, tag)));
                Reg cmp = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::CmpEQ, cmp, tag_reg, expected));
                fail_jumps.push_back(current_function_->instructions.size());
                emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp, 0));

                if (!binding->variableNames.empty()) {
                    Reg payload = allocate_register();
                    emit_instruction(LIR_Inst(LIR_Op::GetPayload, Type::Ptr, payload, value_reg));
                    if (binding->variableNames.size() == 1) {
                        if (binding->variableNames[0] != "_") bind_variable(binding->variableNames[0], payload);
                    } else {
                        for (size_t v_idx = 0; v_idx < binding->variableNames.size(); ++v_idx) {
                            Reg idx_reg = allocate_register();
                            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, idx_reg, std::make_shared<Value>(i64_type, static_cast<int64_t>(v_idx))));
                            Reg elem = allocate_register();
                            emit_instruction(LIR_Inst(LIR_Op::TupleGet, Type::Ptr, elem, payload, idx_reg));
                            if (binding->variableNames[v_idx] != "_") bind_variable(binding->variableNames[v_idx], elem);
                        }
                    }
                }
            } else {
                fail_jumps.push_back(current_function_->instructions.size());
                emit_instruction(LIR_Inst(LIR_Op::Jump, 0));
            }
        }

        // Guard Check
        if (match_case.guard) {
            Reg guard_reg = emit_expr(*match_case.guard);
            fail_jumps.push_back(current_function_->instructions.size());
            emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, guard_reg, 0));
        }

        // Body
        if (match_case.body) {
            emit_stmt(*match_case.body);
        }

        // Jump to end of match after successful execution
        end_jumps.push_back(current_function_->instructions.size());
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0));

        // Patch failure jumps to next case start
        size_t next_case_pc = current_function_->instructions.size();
        for (size_t f_pc : fail_jumps) {
            current_function_->instructions[f_pc].imm = next_case_pc;
        }
        exit_scope();
    }

    // Final Patch: All successful ends jump to after the match
    size_t match_end_pc = current_function_->instructions.size();
    for (size_t e_pc : end_jumps) {
        current_function_->instructions[e_pc].imm = match_end_pc;
    }
}


} // namespace LIR
} // namespace LM
