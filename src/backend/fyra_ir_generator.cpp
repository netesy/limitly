#include "fyra_ir_generator.hh"
#include "ir/Constant.h"
#include "ir/Type.h"
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace LM::Backend::Fyra {

FyraIRGenerator::FyraIRGenerator() {
    context_ = std::make_shared<ir::IRContext>();
    current_module_ = context_->createModule("limit_module");
    builder_ = std::make_unique<ir::IRBuilder>(context_);
    builder_->setModule(current_module_.get());
}

std::string FyraIRGenerator::generate_label() {
    return "L" + std::to_string(label_counter_++);
}

std::shared_ptr<ir::Module> FyraIRGenerator::generate_from_ast(
    const std::shared_ptr<Frontend::AST::Program>& program) {
    
    if (!program) {
        errors_.push_back("Program is null");
        return nullptr;
    }

    for (const auto& stmt : program->statements) {
        if (auto class_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            std::vector<ir::Type*> fields;
            int offset = 0;
            int index = 0;
            for (const auto& field : class_decl->fields) {
                ir::Type* field_ty = ast_type_to_fyra_type(field->type ? field->type->typeName : "int");
                fields.push_back(field_ty);
                struct_field_indices_[class_decl->name][field->name] = index++;
                struct_field_offsets_[class_decl->name][field->name] = offset;
                offset += 8;
            }
            ir::StructType* struct_ty = context_->createStructType(class_decl->name);
            struct_ty->setBody(fields);
            current_module_->addType(class_decl->name, struct_ty);
        }
    }

    for (const auto& stmt : program->statements) {
        if (auto func_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            ir::Type* ret_type = ast_type_to_fyra_type(func_decl->returnType.has_value() ? func_decl->returnType.value()->typeName : "void");
            std::vector<ir::Type*> param_types;
            for (const auto& param : func_decl->params) {
                param_types.push_back(ast_type_to_fyra_type(param.second ? param.second->typeName : "int"));
            }
            builder_->createFunction(func_decl->name, ret_type, param_types);
        } else if (auto class_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            for (const auto& method : class_decl->methods) {
                std::string full_name = class_decl->name + "." + method->name;
                ir::Type* ret_type = ast_type_to_fyra_type(method->returnType ? method->returnType->typeName : "void");
                std::vector<ir::Type*> param_types;
                param_types.push_back(context_->getPointerType(current_module_->getType(class_decl->name)));
                for (const auto& param : method->parameters) {
                    param_types.push_back(ast_type_to_fyra_type(param.second ? param.second->typeName : "int"));
                }
                builder_->createFunction(full_name, ret_type, param_types);
            }
        }
    }

    ir::Function* top_level_func = builder_->createFunction("__limit_main__", context_->getIntegerType(64));
    top_level_func->setExported(true);
    ir::BasicBlock* entry = builder_->createBasicBlock("entry", top_level_func);
    builder_->setInsertPoint(entry);
    
    current_locals_.clear();
    
    for (const auto& stmt : program->statements) {
        if (std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) continue;
        if (std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) continue;
        emit_statement(stmt);
    }
    
    if (builder_->getInsertPoint() && (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret)) {
        builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
    }
    

    for (const auto& stmt : program->statements) {
        if (auto func_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            generate_function(func_decl);
        } else if (auto class_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            emit_class_declaration(class_decl);
        }
    }

    FyraBuiltinFunctions::emit_used_builtins(current_module_.get(), builder_.get(), used_builtins_);

    return current_module_;
}

std::shared_ptr<ir::Module> FyraIRGenerator::generate_from_lir(
    const LIR::LIR_Function& lir_func) {
    current_module_ = context_->createModule("limit_lir_module");
    builder_ = std::make_unique<ir::IRBuilder>(context_);
    builder_->setModule(current_module_.get());
    errors_.clear();

    ir::Function* main_fn = builder_->createFunction(lir_func.name.empty() ? "__limit_main__" : lir_func.name, context_->getIntegerType(64));
    main_fn->setExported(true);

    // Pre-create blocks for label-based control flow.
    std::unordered_map<uint32_t, ir::BasicBlock*> label_blocks;
    for (const auto& inst : lir_func.instructions) {
        if (inst.op == LIR::LIR_Op::Label) {
            label_blocks[inst.imm] = builder_->createBasicBlock("L" + std::to_string(inst.imm), main_fn);
        }
    }

    ir::BasicBlock* entry = builder_->createBasicBlock("entry", main_fn);
    builder_->setInsertPoint(entry);

    std::unordered_map<LIR::Reg, ir::Value*> register_slots;
    auto ensure_slot = [&](LIR::Reg reg, LIR::Type type) -> ir::Value* {
        auto it = register_slots.find(reg);
        if (it != register_slots.end()) return it->second;
        ir::Type* slot_type = lir_type_to_fyra_type(type);
        if (slot_type->isVoidTy()) slot_type = context_->getIntegerType(64);
        ir::Instruction* slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), slot_type);
        slot->setName("r" + std::to_string(reg));
        register_slots[reg] = slot;
        return slot;
    };
    auto load_reg = [&](LIR::Reg reg, LIR::Type type) -> ir::Value* {
        return builder_->createLoad(ensure_slot(reg, type));
    };
    auto store_reg = [&](LIR::Reg reg, ir::Value* value, LIR::Type type) {
        builder_->createStore(value, ensure_slot(reg, type));
    };

    bool terminated = false;
    for (const auto& inst : lir_func.instructions) {
        if (terminated) break;
        switch (inst.op) {
            case LIR::LIR_Op::Label: {
                auto label_it = label_blocks.find(inst.imm);
                if (label_it != label_blocks.end()) {
                    if (!builder_->getInsertPoint()->getInstructions().empty()) {
                        auto opcode = builder_->getInsertPoint()->getInstructions().back()->getOpcode();
                        if (opcode != ir::Instruction::Jmp && opcode != ir::Instruction::Jnz && opcode != ir::Instruction::Ret) {
                            builder_->createJmp(label_it->second);
                        }
                    } else {
                        builder_->createJmp(label_it->second);
                    }
                    builder_->setInsertPoint(label_it->second);
                }
                break;
            }
            case LIR::LIR_Op::LoadConst: {
                if (!inst.const_val) break;
                ir::Value* c = nullptr;
                if (inst.const_val->type) {
                    switch (inst.const_val->type->tag) {
                        case TypeTag::Bool:
                            c = context_->getConstantInt(context_->getIntegerType(64), inst.const_val->data == "true" ? 1 : 0);
                            break;
                        case TypeTag::Float32:
                        case TypeTag::Float64:
                            c = context_->getConstantFP(context_->getDoubleType(), std::stod(inst.const_val->data));
                            break;
                        default:
                            c = context_->getConstantInt(context_->getIntegerType(64), std::stoll(inst.const_val->data));
                            break;
                    }
                } else {
                    c = context_->getConstantInt(context_->getIntegerType(64), std::stoll(inst.const_val->data));
                }
                store_reg(inst.dst, c, inst.result_type);
                break;
            }
            case LIR::LIR_Op::Mov:
            case LIR::LIR_Op::Copy:
                store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type);
                break;
            case LIR::LIR_Op::Add:
                store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::Sub:
                store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::Mul:
                store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::Div:
                store_reg(inst.dst, builder_->createDiv(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::Mod:
                store_reg(inst.dst, builder_->createRem(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::Neg:
                store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type);
                break;
            case LIR::LIR_Op::CmpEQ:
                store_reg(inst.dst, builder_->createCeq(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::CmpNEQ:
                store_reg(inst.dst, builder_->createCne(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::CmpLT:
                store_reg(inst.dst, builder_->createCslt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::CmpLE:
                store_reg(inst.dst, builder_->createCsle(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::CmpGT:
                store_reg(inst.dst, builder_->createCsgt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::CmpGE:
                store_reg(inst.dst, builder_->createCsge(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::Jump: {
                auto target_it = label_blocks.find(inst.imm);
                if (target_it == label_blocks.end()) {
                    errors_.push_back("Unknown jump label: " + std::to_string(inst.imm));
                    break;
                }
                builder_->createJmp(target_it->second);
                break;
            }
            case LIR::LIR_Op::JumpIf:
            case LIR::LIR_Op::JumpIfFalse: {
                auto target_it = label_blocks.find(inst.imm);
                if (target_it == label_blocks.end()) {
                    errors_.push_back("Unknown conditional jump label: " + std::to_string(inst.imm));
                    break;
                }
                ir::BasicBlock* fallthrough = builder_->createBasicBlock(generate_label() + "_cont", main_fn);
                ir::Value* cond = load_reg(inst.a, inst.type_a);
                if (inst.op == LIR::LIR_Op::JumpIfFalse) {
                    builder_->createBr(cond, fallthrough, target_it->second);
                } else {
                    builder_->createBr(cond, target_it->second, fallthrough);
                }
                builder_->setInsertPoint(fallthrough);
                break;
            }
            case LIR::LIR_Op::PrintInt:
            case LIR::LIR_Op::PrintUint:
            case LIR::LIR_Op::PrintFloat:
            case LIR::LIR_Op::PrintBool:
            case LIR::LIR_Op::PrintString: {
                std::string builtin = "lm_print_int";
                ir::Type* arg_ty = context_->getIntegerType(64);
                if (inst.op == LIR::LIR_Op::PrintFloat) {
                    builtin = "lm_print_float";
                    arg_ty = context_->getDoubleType();
                } else if (inst.op == LIR::LIR_Op::PrintBool) {
                    builtin = "lm_print_bool";
                } else if (inst.op == LIR::LIR_Op::PrintString) {
                    builtin = "lm_print_str";
                    arg_ty = context_->getPointerType(context_->getIntegerType(8));
                } else if (inst.op == LIR::LIR_Op::PrintUint) {
                    builtin = "lm_print_uint";
                }
                used_builtins_.insert(builtin);
                ir::Function* fn = current_module_->getFunction(builtin);
                if (!fn) fn = builder_->createFunction(builtin, context_->getVoidType(), {arg_ty});
                builder_->createCall(fn, {load_reg(inst.a, inst.type_a)});
                break;
            }
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
                if (inst.a != 0 || inst.type_a != LIR::Type::Void) builder_->createRet(load_reg(inst.a, inst.type_a));
                else builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
                terminated = true;
                break;
            default:
                errors_.push_back("Unsupported LIR op in Fyra lowering: " + std::to_string(static_cast<int>(inst.op)));
                break;
        }
    }

    if (!terminated && builder_->getInsertPoint()) {
        builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
    }

    FyraBuiltinFunctions::emit_used_builtins(current_module_.get(), builder_.get(), used_builtins_);
    return current_module_;
}

void FyraIRGenerator::emit_builtins() {}

ir::Function* FyraIRGenerator::generate_function(
    const std::shared_ptr<Frontend::AST::FunctionDeclaration>& func_decl) {
    
    if (!func_decl) return nullptr;

    ir::Function* func = current_module_->getFunction(func_decl->name);
    if (!func) {
        ir::Type* ret_type = ast_type_to_fyra_type(func_decl->returnType.has_value() ? func_decl->returnType.value()->typeName : "void");
        std::vector<ir::Type*> param_types;
        for (const auto& param : func_decl->params) {
            param_types.push_back(ast_type_to_fyra_type(param.second ? param.second->typeName : "int"));
        }
        func = builder_->createFunction(func_decl->name, ret_type, param_types);
    }
    
    if (!func->getBasicBlocks().empty()) return func;
    
    ir::BasicBlock* entry = builder_->createBasicBlock(func_decl->name + "_entry", func);
    builder_->setInsertPoint(entry);
    
    current_locals_.clear();
    auto& params = func->getParameters();
    auto it = params.begin();
    for (size_t i = 0; i < func_decl->params.size() && it != params.end(); ++i, ++it) {
        std::string param_name = func_decl->params[i].first;
        ir::Type* p_type = it->get()->getType();
        ir::Instruction* slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), p_type);
        slot->setName("slot_" + param_name);
        builder_->createStore(it->get(), slot);
        current_locals_[param_name] = slot;
    }
    
    if (func_decl->body) {
        emit_block_statement(func_decl->body);
    }
    
    if (func->getType()->isVoidTy() && (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret)) {
        builder_->createRet(nullptr);
    }
    
    return func;
}

ir::Value* FyraIRGenerator::emit_expression(
    const std::shared_ptr<Frontend::AST::Expression>& expr) {
    
    if (!expr) return nullptr;
    
    ir::Value* result = nullptr;
    if (auto binary = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
        result = emit_binary_expr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<Frontend::AST::UnaryExpr>(expr)) {
        result = emit_unary_expr(unary);
    } else if (auto literal = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(expr)) {
        result = emit_literal_expr(literal);
    } else if (auto variable = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr)) {
        result = emit_variable_expr(variable);
    } else if (auto this_expr = std::dynamic_pointer_cast<Frontend::AST::ThisExpr>(expr)) {
        auto var = std::make_shared<Frontend::AST::VariableExpr>();
        var->name = "self";
        result = emit_variable_expr(var);
    } else if (auto call = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(expr)) {
        result = emit_call_expr(call);
    } else if (auto assign = std::dynamic_pointer_cast<Frontend::AST::AssignExpr>(expr)) {
        result = emit_assign_expr(assign);
    } else if (auto index = std::dynamic_pointer_cast<Frontend::AST::IndexExpr>(expr)) {
        result = emit_index_expr(index);
    } else if (auto member = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(expr)) {
        result = emit_member_expr(member);
    } else if (auto list = std::dynamic_pointer_cast<Frontend::AST::ListExpr>(expr)) {
        result = emit_list_expr(list);
    } else if (auto tuple = std::dynamic_pointer_cast<Frontend::AST::TupleExpr>(expr)) {
        used_builtins_.insert("lm_tuple_new");
        used_builtins_.insert("lm_tuple_set");
        ir::Function* tuple_new = current_module_->getFunction("lm_tuple_new");
        if (!tuple_new) {
            tuple_new = builder_->createFunction("lm_tuple_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
        }
        ir::Value* tuple_val = builder_->createCall(tuple_new, {context_->getConstantInt(context_->getIntegerType(64), (long long)tuple->elements.size())});
        ir::Function* tuple_set = current_module_->getFunction("lm_tuple_set");
        if (!tuple_set) {
            tuple_set = builder_->createFunction("lm_tuple_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
        }
        for (size_t i = 0; i < tuple->elements.size(); ++i) {
            ir::Value* elem = emit_expression(tuple->elements[i]);
            builder_->createCall(tuple_set, {tuple_val, context_->getConstantInt(context_->getIntegerType(64), (long long)i), elem});
        }
        result = tuple_val;
    } else if (auto dict = std::dynamic_pointer_cast<Frontend::AST::DictExpr>(expr)) {
        result = emit_dict_expr(dict);
    } else if (auto range = std::dynamic_pointer_cast<Frontend::AST::RangeExpr>(expr)) {
        result = emit_range_expr(range);
    } else if (auto frame_init = std::dynamic_pointer_cast<Frontend::AST::FrameInstantiationExpr>(expr)) {
        ir::Type* type = current_module_->getType(frame_init->frameName);
        if (!type) {
            std::vector<ir::Type*> fields = {context_->getIntegerType(64), context_->getIntegerType(64)};
            ir::StructType* struct_ty = context_->createStructType(frame_init->frameName);
            struct_ty->setBody(fields);
            current_module_->addType(frame_init->frameName, struct_ty);
            type = struct_ty;
        }
        size_t type_size = type->getSize();
        if (type_size == 0) type_size = 16;
        ir::Value* size = context_->getConstantInt(context_->getIntegerType(64), (long long)type_size);
        ir::Value* alloc = builder_->createAlloc(size, type);
        std::string init_name = frame_init->frameName + ".init";
        ir::Function* init_func = current_module_->getFunction(init_name);
        if (init_func) {
            std::vector<ir::Value*> args_v = {alloc};
            for (const auto& arg : frame_init->positionalArgs) {
                args_v.push_back(emit_expression(arg));
            }
            builder_->createCall(init_func, args_v);
        }
        result = alloc;
    }
    return result;
}

void FyraIRGenerator::emit_statement(
    const std::shared_ptr<Frontend::AST::Statement>& stmt) {
    if (!stmt) return;
    if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
        emit_var_declaration(var_decl);
    } else if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
        emit_block_statement(block);
    } else if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
        emit_if_statement(if_stmt);
    } else if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
        emit_while_statement(while_stmt);
    } else if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
        emit_for_statement(for_stmt);
    } else if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
        emit_iter_statement(iter_stmt);
    } else if (auto parallel_stmt = std::dynamic_pointer_cast<Frontend::AST::ParallelStatement>(stmt)) {
        emit_parallel_statement(parallel_stmt);
    } else if (auto concurrent_stmt = std::dynamic_pointer_cast<Frontend::AST::ConcurrentStatement>(stmt)) {
        emit_concurrent_statement(concurrent_stmt);
    } else if (auto ret_stmt = std::dynamic_pointer_cast<Frontend::AST::ReturnStatement>(stmt)) {
        emit_return_statement(ret_stmt);
    } else if (auto print_stmt = std::dynamic_pointer_cast<Frontend::AST::PrintStatement>(stmt)) {
        emit_print_statement(print_stmt);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<Frontend::AST::ExprStatement>(stmt)) {
        emit_expression(expr_stmt->expression);
    }
}

ir::Value* FyraIRGenerator::emit_binary_expr(
    const std::shared_ptr<Frontend::AST::BinaryExpr>& expr) {
    ir::Value* lhs = emit_expression(expr->left);
    ir::Value* rhs = emit_expression(expr->right);
    switch (expr->op) {
        case Frontend::TokenType::PLUS: return builder_->createAdd(lhs, rhs);
        case Frontend::TokenType::MINUS: return builder_->createSub(lhs, rhs);
        case Frontend::TokenType::STAR: return builder_->createMul(lhs, rhs);
        case Frontend::TokenType::SLASH: return builder_->createDiv(lhs, rhs);
        case Frontend::TokenType::MODULUS: return builder_->createRem(lhs, rhs);
        case Frontend::TokenType::EQUAL_EQUAL: return builder_->createCeq(lhs, rhs);
        case Frontend::TokenType::BANG_EQUAL: return builder_->createCne(lhs, rhs);
        case Frontend::TokenType::LESS: return builder_->createCslt(lhs, rhs);
        case Frontend::TokenType::LESS_EQUAL: return builder_->createCsle(lhs, rhs);
        case Frontend::TokenType::GREATER: return builder_->createCsgt(lhs, rhs);
        case Frontend::TokenType::GREATER_EQUAL: return builder_->createCsge(lhs, rhs);
        default: return nullptr;
    }
}

ir::Value* FyraIRGenerator::emit_unary_expr(
    const std::shared_ptr<Frontend::AST::UnaryExpr>& expr) {
    ir::Value* operand = emit_expression(expr->right);
    if (expr->op == Frontend::TokenType::MINUS) {
        return builder_->createNeg(operand);
    }
    return nullptr;
}

ir::Value* FyraIRGenerator::emit_literal_expr(
    const std::shared_ptr<Frontend::AST::LiteralExpr>& expr) {
    if (std::holds_alternative<std::string>(expr->value)) {
        std::string s = std::get<std::string>(expr->value);
        if (expr->literalType == Frontend::TokenType::INT_LITERAL) {
             long long val = std::stoll(s);
             return context_->getConstantInt(context_->getIntegerType(64), val);
        } else {
             used_builtins_.insert("lm_box_string");
             ir::Function* box_string = current_module_->getFunction("lm_box_string");
             if (!box_string) {
                 box_string = builder_->createFunction("lm_box_string", context_->getPointerType(context_->getIntegerType(8)), {context_->getPointerType(context_->getIntegerType(8))});
             }
             ir::Value* str_const = context_->getConstantString(s);
             std::string name = "$str" + std::to_string(label_counter_++);
             auto gv = std::make_unique<ir::GlobalVariable>(context_->getPointerType(context_->getIntegerType(8)), name, static_cast<ir::Constant*>(str_const), false, ".data");
             ir::GlobalVariable* gv_ptr = gv.get();
             current_module_->addGlobalVariable(std::move(gv));
             std::vector<ir::Value*> args = {gv_ptr};
             return builder_->createCall(box_string, args);
        }
    } else if (std::holds_alternative<bool>(expr->value)) {
        return context_->getConstantInt(context_->getIntegerType(64), std::get<bool>(expr->value) ? 1 : 0);
    }
    return nullptr;
}

ir::Value* FyraIRGenerator::emit_variable_expr(
    const std::shared_ptr<Frontend::AST::VariableExpr>& expr) {
    std::string name = expr->name;
    if (name == "this") name = "self";
    if (current_locals_.count(name)) {
        return builder_->createLoad(current_locals_[name]);
    }
    return nullptr;
}

ir::Value* FyraIRGenerator::emit_call_expr(
    const std::shared_ptr<Frontend::AST::CallExpr>& expr) {
    std::string func_name;
    std::vector<ir::Value*> args;
    if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr->callee)) {
        func_name = var->name;
        if (auto struct_ty = current_module_->getType(func_name)) {
            ir::Value* size = context_->getConstantInt(context_->getIntegerType(64), struct_ty->getSize() > 0 ? (long long)struct_ty->getSize() : 16);
            ir::Instruction* alloc = builder_->createAlloc(size, struct_ty);
            std::string vname = "alloc_" + func_name;
            alloc->setName(vname);
            std::string init_name = func_name + ".init";
            ir::Function* init_func = current_module_->getFunction(init_name);
            if (init_func) {
                std::vector<ir::Value*> init_args = {alloc};
                for (const auto& arg : expr->arguments) init_args.push_back(emit_expression(arg));
                builder_->createCall(init_func, init_args);
            }
            return alloc;
        }
    } else if (auto member = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(expr->callee)) {
        ir::Value* obj = emit_expression(member->object);
        ir::Type* obj_ty = obj->getType();
        if (auto ptr_ty = dynamic_cast<ir::PointerType*>(obj_ty)) {
            obj_ty = ptr_ty->getElementType();
        }
        if (auto struct_ty = dynamic_cast<ir::StructType*>(obj_ty)) {
            func_name = struct_ty->getName() + "." + member->name;
            args.push_back(obj);
        } else {
             func_name = member->name;
             args.push_back(obj);
        }
    }

    if (FyraBuiltinFunctions::is_builtin(func_name)) {
        if (func_name == "print") {
            ir::Value* arg = emit_expression(expr->arguments[0]);
            if (arg->getType()->isPointerTy()) {
                 func_name = "lm_print_str";
            } else {
                 func_name = "lm_print_int";
            }
        } else {
            func_name = FyraBuiltinFunctions::get_internal_name(func_name);
        }
        used_builtins_.insert(func_name);
    }

    ir::Function* callee = current_module_->getFunction(func_name);
    if (!callee) {
        std::vector<ir::Type*> params;
        if (!args.empty()) params.push_back(args[0]->getType());
        for (const auto& arg : expr->arguments) {
             params.push_back(context_->getIntegerType(64));
        }
        callee = builder_->createFunction(func_name, context_->getVoidType(), params);
    }
    for (const auto& arg : expr->arguments) {
        args.push_back(emit_expression(arg));
    }
    return builder_->createCall(callee, args);
}

ir::Value* FyraIRGenerator::emit_assign_expr(
    const std::shared_ptr<Frontend::AST::AssignExpr>& expr) {
    ir::Value* val = emit_expression(expr->value);
    if (!val) return nullptr;
    if (expr->object) {
        ir::Value* obj = nullptr;
        if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr->object)) {
            std::string name = var->name;
            if (name == "this") name = "self";
            if (current_locals_.count(name)) obj = builder_->createLoad(current_locals_[name]);
        }
        if (!obj) obj = emit_expression(expr->object);
        if (expr->member.has_value()) {
            ir::Type* obj_ty = obj->getType();
            if (auto ptr_ty = dynamic_cast<ir::PointerType*>(obj_ty)) obj_ty = ptr_ty->getElementType();
            if (auto struct_ty = dynamic_cast<ir::StructType*>(obj_ty)) {
                std::string struct_name = struct_ty->getName();
                if (struct_field_offsets_.count(struct_name) && struct_field_offsets_[struct_name].count(expr->member.value())) {
                    int offset = struct_field_offsets_[struct_name][expr->member.value()];
                    ir::Value* field_ptr = builder_->createAdd(obj, context_->getConstantInt(context_->getIntegerType(64), (long long)offset));
                    builder_->createStore(val, field_ptr);
                    return val;
                }
            }
        } else if (expr->index) {
            used_builtins_.insert("lm_list_set");
            ir::Function* list_set = current_module_->getFunction("lm_list_set");
            if (!list_set) list_set = builder_->createFunction("lm_list_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
            ir::Value* idx = emit_expression(expr->index);
            builder_->createCall(list_set, {obj, idx, val});
            return val;
        }
    } else {
        std::string name = expr->name;
        if (name == "this") name = "self";
        if (current_locals_.count(name)) {
            builder_->createStore(val, current_locals_[name]);
            return val;
        }
    }
    return nullptr;
}

ir::Value* FyraIRGenerator::emit_index_expr(
    const std::shared_ptr<Frontend::AST::IndexExpr>& expr) {
    used_builtins_.insert("lm_list_get");
    ir::Value* obj = emit_expression(expr->object);
    ir::Value* idx = emit_expression(expr->index);
    ir::Function* list_get = current_module_->getFunction("lm_list_get");
    if (!list_get) list_get = builder_->createFunction("lm_list_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
    return builder_->createCall(list_get, {obj, idx});
}

ir::Value* FyraIRGenerator::emit_member_expr(
    const std::shared_ptr<Frontend::AST::MemberExpr>& expr) {
    ir::Value* obj = nullptr;
    if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr->object)) {
        std::string name = var->name;
        if (name == "this") name = "self";
        if (current_locals_.count(name)) obj = builder_->createLoad(current_locals_[name]);
    }
    if (!obj) obj = emit_expression(expr->object);
    if (!obj) return nullptr;
    ir::Type* obj_ty = obj->getType();
    if (auto ptr_ty = dynamic_cast<ir::PointerType*>(obj_ty)) obj_ty = ptr_ty->getElementType();
    if (auto struct_ty = dynamic_cast<ir::StructType*>(obj_ty)) {
        std::string struct_name = struct_ty->getName();
        if (struct_field_offsets_.count(struct_name) && struct_field_offsets_[struct_name].count(expr->name)) {
            int offset = struct_field_offsets_[struct_name][expr->name];
            ir::Value* field_ptr = builder_->createAdd(obj, context_->getConstantInt(context_->getIntegerType(64), (long long)offset));
            return builder_->createLoad(field_ptr);
        }
    }
    return obj;
}

ir::Value* FyraIRGenerator::emit_list_expr(
    const std::shared_ptr<Frontend::AST::ListExpr>& expr) {
    used_builtins_.insert("lm_list_new");
    used_builtins_.insert("lm_list_append");
    ir::Function* list_new = current_module_->getFunction("lm_list_new");
    if (!list_new) list_new = builder_->createFunction("lm_list_new", context_->getIntegerType(64), {});
    ir::Value* list = builder_->createCall(list_new, {});
    ir::Function* list_append = current_module_->getFunction("lm_list_append");
    if (!list_append) list_append = builder_->createFunction("lm_list_append", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64)});
    for (const auto& elem_expr : expr->elements) {
        ir::Value* elem = emit_expression(elem_expr);
        builder_->createCall(list_append, {list, elem});
    }
    return list;
}

ir::Value* FyraIRGenerator::emit_dict_expr(
    const std::shared_ptr<Frontend::AST::DictExpr>& expr) {
    used_builtins_.insert("jit_dict_new");
    used_builtins_.insert("lm_dict_set");
    ir::Function* dict_new = current_module_->getFunction("jit_dict_new");
    if (!dict_new) dict_new = builder_->createFunction("jit_dict_new", context_->getIntegerType(64), {});
    ir::Value* dict = builder_->createCall(dict_new, {});
    ir::Function* dict_set = current_module_->getFunction("lm_dict_set");
    if (!dict_set) dict_set = builder_->createFunction("lm_dict_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
    for (const auto& entry : expr->entries) {
        ir::Value* key = emit_expression(entry.first);
        ir::Value* val = emit_expression(entry.second);
        builder_->createCall(dict_set, {dict, key, val});
    }
    return dict;
}

ir::Value* FyraIRGenerator::emit_range_expr(
    const std::shared_ptr<Frontend::AST::RangeExpr>& expr) {
    return emit_expression(expr->start);
}

void FyraIRGenerator::emit_var_declaration(
    const std::shared_ptr<Frontend::AST::VarDeclaration>& decl) {
    ir::Type* type = ast_type_to_fyra_type(decl->type.has_value() ? decl->type.value()->typeName : "int");
    ir::Instruction* slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), type);
    slot->setName("var_" + decl->name);
    current_locals_[decl->name] = slot;
    if (decl->initializer) {
        ir::Value* init = emit_expression(decl->initializer);
        builder_->createStore(init, slot);
    }
}

void FyraIRGenerator::emit_function_declaration(
    const std::shared_ptr<Frontend::AST::FunctionDeclaration>& decl) {
    generate_function(decl);
}

void FyraIRGenerator::emit_class_declaration(
    const std::shared_ptr<Frontend::AST::FrameDeclaration>& decl) {
    for (const auto& method : decl->methods) {
        std::string full_name = decl->name + "." + method->name;
        ir::Function* func = current_module_->getFunction(full_name);
        if (!func || !func->getBasicBlocks().empty()) continue;
        ir::BasicBlock* entry = builder_->createBasicBlock(full_name + "_entry", func);
        builder_->setInsertPoint(entry);
        current_locals_.clear();
        auto& params = func->getParameters();
        auto it = params.begin();
        if (it != params.end()) {
            ir::Type* self_type = it->get()->getType();
            ir::Instruction* self_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), self_type);
            self_slot->setName("slot_self");
            builder_->createStore(it->get(), self_slot);
            current_locals_["self"] = self_slot;
            ++it;
        }
        for (size_t i = 0; i < method->parameters.size() && it != params.end(); ++i, ++it) {
            std::string param_name = method->parameters[i].first;
            ir::Type* p_type = it->get()->getType();
            ir::Instruction* p_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), p_type);
            p_slot->setName("slot_" + param_name);
            builder_->createStore(it->get(), p_slot);
            current_locals_[param_name] = p_slot;
        }
        if (method->body) emit_block_statement(method->body);
        if (func->getType()->isVoidTy() && (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret)) {
            builder_->createRet(nullptr);
        }
    }
}

void FyraIRGenerator::emit_block_statement(
    const std::shared_ptr<Frontend::AST::BlockStatement>& stmt) {
    for (const auto& s : stmt->statements) emit_statement(s);
}

void FyraIRGenerator::emit_if_statement(
    const std::shared_ptr<Frontend::AST::IfStatement>& stmt) {
    ir::Value* cond = emit_expression(stmt->condition);
    ir::Function* func = builder_->getInsertPoint()->getParent();
    ir::BasicBlock* then_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* else_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* merge_bb = builder_->createBasicBlock(generate_label(), func);
    builder_->createBr(cond, then_bb, else_bb);
    builder_->setInsertPoint(then_bb);
    emit_statement(stmt->thenBranch);
    if (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret) builder_->createJmp(merge_bb);
    builder_->setInsertPoint(else_bb);
    if (stmt->elseBranch) emit_statement(stmt->elseBranch);
    if (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret) builder_->createJmp(merge_bb);
    builder_->setInsertPoint(merge_bb);
}

void FyraIRGenerator::emit_while_statement(
    const std::shared_ptr<Frontend::AST::WhileStatement>& stmt) {
    ir::Function* func = builder_->getInsertPoint()->getParent();
    ir::BasicBlock* cond_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* body_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* end_bb = builder_->createBasicBlock(generate_label(), func);
    builder_->createJmp(cond_bb);
    builder_->setInsertPoint(cond_bb);
    ir::Value* cond = emit_expression(stmt->condition);
    builder_->createBr(cond, body_bb, end_bb);
    builder_->setInsertPoint(body_bb);
    emit_statement(stmt->body);
    if (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret) builder_->createJmp(cond_bb);
    builder_->setInsertPoint(end_bb);
}

void FyraIRGenerator::emit_for_statement(
    const std::shared_ptr<Frontend::AST::ForStatement>& stmt) {
    ir::Function* func = builder_->getInsertPoint()->getParent();
    if (stmt->initializer) emit_statement(stmt->initializer);
    ir::BasicBlock* cond_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* body_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* inc_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* end_bb = builder_->createBasicBlock(generate_label(), func);
    builder_->createJmp(cond_bb);
    builder_->setInsertPoint(cond_bb);
    if (stmt->condition) {
        ir::Value* cond = emit_expression(stmt->condition);
        builder_->createBr(cond, body_bb, end_bb);
    } else builder_->createJmp(body_bb);
    builder_->setInsertPoint(body_bb);
    emit_statement(stmt->body);
    if (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret) builder_->createJmp(inc_bb);
    builder_->setInsertPoint(inc_bb);
    if (stmt->increment) emit_expression(stmt->increment);
    builder_->createJmp(cond_bb);
    builder_->setInsertPoint(end_bb);
}

void FyraIRGenerator::emit_iter_statement(
    const std::shared_ptr<Frontend::AST::IterStatement>& stmt) {
    used_builtins_.insert("lm_list_len");
    used_builtins_.insert("lm_list_get");
    ir::Value* iterable = emit_expression(stmt->iterable);
    ir::Function* func = builder_->getInsertPoint()->getParent();
    ir::Function* list_len = current_module_->getFunction("lm_list_len");
    if (!list_len) list_len = builder_->createFunction("lm_list_len", context_->getIntegerType(64), {context_->getIntegerType(64)});
    ir::Value* len = builder_->createCall(list_len, {iterable});
    ir::Instruction* counter_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
    builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), counter_slot);
    ir::BasicBlock* cond_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* body_bb = builder_->createBasicBlock(generate_label(), func);
    ir::BasicBlock* end_bb = builder_->createBasicBlock(generate_label(), func);
    builder_->createJmp(cond_bb);
    builder_->setInsertPoint(cond_bb);
    ir::Value* counter = builder_->createLoad(counter_slot);
    ir::Value* cond = builder_->createCslt(counter, len);
    builder_->createBr(cond, body_bb, end_bb);
    builder_->setInsertPoint(body_bb);
    ir::Function* list_get = current_module_->getFunction("lm_list_get");
    if (!list_get) list_get = builder_->createFunction("lm_list_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
    ir::Value* element = builder_->createCall(list_get, {iterable, counter});
    if (!stmt->loopVars.empty()) {
        ir::Instruction* var_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
        builder_->createStore(element, var_slot);
        current_locals_[stmt->loopVars[0]] = var_slot;
    }
    emit_statement(stmt->body);
    ir::Value* next_counter = builder_->createAdd(counter, context_->getConstantInt(context_->getIntegerType(64), 1));
    builder_->createStore(next_counter, counter_slot);
    if (builder_->getInsertPoint()->getInstructions().empty() || builder_->getInsertPoint()->getInstructions().back()->getOpcode() != ir::Instruction::Ret) builder_->createJmp(cond_bb);
    builder_->setInsertPoint(end_bb);
}

void FyraIRGenerator::emit_parallel_statement(
    const std::shared_ptr<Frontend::AST::ParallelStatement>& stmt) {
    emit_statement(stmt->body);
}

void FyraIRGenerator::emit_concurrent_statement(
    const std::shared_ptr<Frontend::AST::ConcurrentStatement>& stmt) {
    emit_statement(stmt->body);
}

void FyraIRGenerator::emit_print_statement(
    const std::shared_ptr<Frontend::AST::PrintStatement>& stmt) {
    for (const auto& arg_expr : stmt->arguments) {
        ir::Value* val = emit_expression(arg_expr);
        if (!val) continue;

        std::string func_name;
        if (val->getType()->isPointerTy()) {
            func_name = "lm_print_str";
        } else {
            func_name = "lm_print_int";
        }

        used_builtins_.insert(func_name);
        ir::Function* print_func = current_module_->getFunction(func_name);
        if (!print_func) {
            ir::Type* arg_type = (func_name == "lm_print_str") ? 
                                 (ir::Type*)context_->getPointerType(context_->getIntegerType(8)) : 
                                 (ir::Type*)context_->getIntegerType(64);
            print_func = builder_->createFunction(func_name, context_->getVoidType(), {arg_type});
        }
        builder_->createCall(print_func, {val});
    }
}

void FyraIRGenerator::emit_return_statement(
    const std::shared_ptr<Frontend::AST::ReturnStatement>& stmt) {
    if (stmt->value) builder_->createRet(emit_expression(stmt->value));
    else builder_->createRet(nullptr);
}

ir::Type* FyraIRGenerator::ast_type_to_fyra_type(const std::string& ast_type) {
    if (ast_type == "int" || ast_type == "i64") return context_->getIntegerType(64);
    if (ast_type == "i32") return context_->getIntegerType(32);
    if (ast_type == "i8" || ast_type == "u8") return context_->getIntegerType(8);
    if (ast_type == "float" || ast_type == "f64") return context_->getDoubleType();
    if (ast_type == "bool") return context_->getIntegerType(64);
    if (ast_type == "void") return context_->getVoidType();
    ir::Type* ty = current_module_->getType(ast_type);
    if (ty) return context_->getPointerType(ty);
    return context_->getIntegerType(64);
}

ir::Type* FyraIRGenerator::lir_type_to_fyra_type(LIR::Type lir_type) {
    switch (lir_type) {
        case LIR::Type::I32: return context_->getIntegerType(32);
        case LIR::Type::I64: return context_->getIntegerType(64);
        case LIR::Type::F64: return context_->getDoubleType();
        case LIR::Type::Bool: return context_->getIntegerType(64);
        case LIR::Type::Ptr: return context_->getPointerType(context_->getIntegerType(8));
        case LIR::Type::Void: return context_->getVoidType();
        default: return context_->getIntegerType(64);
    }
}

} // namespace LM::Backend::Fyra
