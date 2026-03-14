// fyra_ir_generator.cpp - Direct AST to Fyra IR Code Generation

#include "fyra_ir_generator.hh"
#include "ir/Constant.h"
#include "ir/Type.h"
#include <iostream>
#include <sstream>

namespace LM::Backend::Fyra {

FyraIRGenerator::FyraIRGenerator() {
    current_module_ = std::make_shared<ir::Module>("limit_module");
    builder_ = std::make_unique<ir::IRBuilder>();
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

    emit_builtins();
    
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
            ir::StructType* struct_ty = ir::StructType::create(class_decl->name);
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
                param_types.push_back(ir::PointerType::get(current_module_->getType(class_decl->name)));
                for (const auto& param : method->parameters) {
                    param_types.push_back(ast_type_to_fyra_type(param.second ? param.second->typeName : "int"));
                }
                builder_->createFunction(full_name, ret_type, param_types);
            }
        }
    }

    ir::Function* top_level_func = builder_->createFunction("main", ir::IntegerType::get(64));
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
        builder_->createRet(ir::ConstantInt::get(ir::IntegerType::get(64), 0));
    }
    

    for (const auto& stmt : program->statements) {
        if (auto func_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            generate_function(func_decl);
        } else if (auto class_decl = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            emit_class_declaration(class_decl);
        }
    }

    return current_module_;
}

void FyraIRGenerator::emit_builtins() {
    // lm_print_int(int)
    ir::Function* print_int = builder_->createFunction("lm_print_int", ir::VoidType::get(), {ir::IntegerType::get(64)});
    ir::BasicBlock* b_entry = builder_->createBasicBlock("entry", print_int);
    ir::BasicBlock* b_neg = builder_->createBasicBlock("neg", print_int);
    ir::BasicBlock* b_abs = builder_->createBasicBlock("abs", print_int);
    ir::BasicBlock* b_loop = builder_->createBasicBlock("loop", print_int);
    ir::BasicBlock* b_done = builder_->createBasicBlock("done", print_int);

    builder_->setInsertPoint(b_entry);
    ir::Value* val = print_int->getParameters().front().get();
    ir::Value* buf = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 32), ir::IntegerType::get(64));
    ir::Value* ptr = builder_->createAdd(buf, ir::ConstantInt::get(ir::IntegerType::get(64), 31));
    builder_->createStoreb(ir::ConstantInt::get(ir::IntegerType::get(8), 10), ptr);

    ir::Instruction* val_slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), ir::IntegerType::get(64));
    ir::Instruction* ptr_slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), ir::IntegerType::get(64));
    builder_->createStore(ptr, ptr_slot);

    ir::Value* is_neg = builder_->createCslt(val, ir::ConstantInt::get(ir::IntegerType::get(64), 0));
    builder_->createBr(is_neg, b_neg, b_abs);

    builder_->setInsertPoint(b_neg);
    std::string minus_name = "$str_minus";
    auto gv_minus = new ir::GlobalVariable(ir::PointerType::get(ir::IntegerType::get(8)), minus_name, ir::ConstantString::get("-"), false, "");
    current_module_->addGlobalVariable(gv_minus);

    std::vector<ir::Value*> neg_sys_args = {
        ir::ConstantInt::get(ir::IntegerType::get(64), 1), // stdout
        gv_minus,
        ir::ConstantInt::get(ir::IntegerType::get(64), 1)
    };
    builder_->createSyscall(ir::SyscallId::Write, neg_sys_args);
    ir::Value* abs_v = builder_->createNeg(val);
    builder_->createStore(abs_v, val_slot);
    builder_->createJmp(b_loop);

    builder_->setInsertPoint(b_abs);
    builder_->createStore(val, val_slot);
    builder_->createJmp(b_loop);

    builder_->setInsertPoint(b_loop);
    ir::Value* curr_val = builder_->createLoad(val_slot);
    ir::Value* next_val = builder_->createDiv(curr_val, ir::ConstantInt::get(ir::IntegerType::get(64), 10));
    ir::Value* rem = builder_->createRem(curr_val, ir::ConstantInt::get(ir::IntegerType::get(64), 10));
    ir::Value* ascii = builder_->createAdd(rem, ir::ConstantInt::get(ir::IntegerType::get(64), 48));

    ir::Value* curr_ptr = builder_->createLoad(ptr_slot);
    ir::Value* next_ptr = builder_->createSub(curr_ptr, ir::ConstantInt::get(ir::IntegerType::get(64), 1));
    builder_->createStoreb(builder_->createCast(ascii, ir::IntegerType::get(8)), next_ptr);

    builder_->createStore(next_val, val_slot);
    builder_->createStore(next_ptr, ptr_slot);

    ir::Value* cond = builder_->createCuge(next_val, ir::ConstantInt::get(ir::IntegerType::get(64), 1));
    builder_->createBr(cond, b_loop, b_done);

    builder_->setInsertPoint(b_done);
    ir::Value* final_ptr = builder_->createLoad(ptr_slot);
    ir::Value* end_ptr = builder_->createAdd(buf, ir::ConstantInt::get(ir::IntegerType::get(64), 32));
    ir::Value* len = builder_->createSub(end_ptr, final_ptr);

    std::vector<ir::Value*> done_sys_args = {
        ir::ConstantInt::get(ir::IntegerType::get(64), 1), // stdout
        final_ptr,
        len
    };
    builder_->createSyscall(ir::SyscallId::Write, done_sys_args);
    builder_->createRet(nullptr);

    // lm_assert(bool, string)
    ir::Function* lm_assert = builder_->createFunction("lm_assert", ir::VoidType::get(), {ir::IntegerType::get(64), ir::IntegerType::get(64)});
    ir::BasicBlock* a_entry = builder_->createBasicBlock("entry", lm_assert);
    ir::BasicBlock* a_fail = builder_->createBasicBlock("fail", lm_assert);
    ir::BasicBlock* a_pass = builder_->createBasicBlock("pass", lm_assert);

    builder_->setInsertPoint(a_entry);
    ir::Value* a_cond = lm_assert->getParameters().front().get();
    builder_->createBr(a_cond, a_pass, a_fail);

    builder_->setInsertPoint(a_fail);
    std::vector<ir::Value*> fail_sys_args = {
        ir::ConstantInt::get(ir::IntegerType::get(64), 1) // exit status
    };
    builder_->createSyscall(ir::SyscallId::Exit, fail_sys_args);
    builder_->createRet(nullptr);

    builder_->setInsertPoint(a_pass);
    builder_->createRet(nullptr);

    ir::Function* box_string = builder_->createFunction("lm_box_string", ir::IntegerType::get(64), {ir::IntegerType::get(64)});
    ir::BasicBlock* s_entry = builder_->createBasicBlock("entry", box_string);
    builder_->setInsertPoint(s_entry);
    builder_->createRet(box_string->getParameters().front().get());

    // lm_print_str(str)
    ir::Function* print_str = builder_->createFunction("lm_print_str", ir::VoidType::get(), {ir::PointerType::get(ir::IntegerType::get(8))});
    ir::BasicBlock* ps_entry = builder_->createBasicBlock("entry", print_str);
    ir::BasicBlock* ps_loop = builder_->createBasicBlock("loop", print_str);
    ir::BasicBlock* ps_done = builder_->createBasicBlock("done", print_str);

    builder_->setInsertPoint(ps_entry);
    ir::Value* s_val = print_str->getParameters().front().get();
    ir::Instruction* len_slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), ir::IntegerType::get(64));
    builder_->createStore(ir::ConstantInt::get(ir::IntegerType::get(64), 0), len_slot);
    builder_->createJmp(ps_loop);

    builder_->setInsertPoint(ps_loop);
    ir::Value* curr_len = builder_->createLoad(len_slot);
    ir::Value* ps_curr_ptr = builder_->createAdd(s_val, curr_len);
    ir::Value* curr_char = builder_->createLoadub(ps_curr_ptr);
    ir::Value* is_null = builder_->createCeq(curr_char, ir::ConstantInt::get(ir::IntegerType::get(8), 0));
    ir::Value* next_len = builder_->createAdd(curr_len, ir::ConstantInt::get(ir::IntegerType::get(64), 1));
    builder_->createStore(next_len, len_slot);
    builder_->createBr(is_null, ps_done, ps_loop);

    builder_->setInsertPoint(ps_done);
    ir::Value* final_len = builder_->createLoad(len_slot);
    ir::Value* actual_len = builder_->createSub(final_len, ir::ConstantInt::get(ir::IntegerType::get(64), 1));

    // Syscall write args: fd, buf, count
    std::vector<ir::Value*> ps_sys_args = {
        ir::ConstantInt::get(ir::IntegerType::get(64), 1), // stdout
        s_val,
        actual_len
    };
    builder_->createSyscall(ir::SyscallId::Write, ps_sys_args);

    // Print newline
    auto gv_nl = new ir::GlobalVariable(ir::PointerType::get(ir::IntegerType::get(8)), "$nl", ir::ConstantString::get("\n"), false, "");
    current_module_->addGlobalVariable(gv_nl);
    std::vector<ir::Value*> nl_sys_args = {
        ir::ConstantInt::get(ir::IntegerType::get(64), 1), // stdout
        gv_nl,
        ir::ConstantInt::get(ir::IntegerType::get(64), 1)
    };
    builder_->createSyscall(ir::SyscallId::Write, nl_sys_args);

    builder_->createRet(nullptr);
}

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
        ir::Instruction* slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), p_type);
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
        ir::Function* tuple_new = current_module_->getFunction("lm_tuple_new");
        if (!tuple_new) {
            tuple_new = builder_->createFunction("lm_tuple_new", ir::IntegerType::get(64), {ir::IntegerType::get(64)});
        }
        ir::Value* tuple_val = builder_->createCall(tuple_new, {ir::ConstantInt::get(ir::IntegerType::get(64), (long long)tuple->elements.size())});
        ir::Function* tuple_set = current_module_->getFunction("lm_tuple_set");
        if (!tuple_set) {
            tuple_set = builder_->createFunction("lm_tuple_set", ir::VoidType::get(), {ir::IntegerType::get(64), ir::IntegerType::get(64), ir::IntegerType::get(64)});
        }
        for (size_t i = 0; i < tuple->elements.size(); ++i) {
            ir::Value* elem = emit_expression(tuple->elements[i]);
            builder_->createCall(tuple_set, {tuple_val, ir::ConstantInt::get(ir::IntegerType::get(64), (long long)i), elem});
        }
        result = tuple_val;
    } else if (auto dict = std::dynamic_pointer_cast<Frontend::AST::DictExpr>(expr)) {
        result = emit_dict_expr(dict);
    } else if (auto range = std::dynamic_pointer_cast<Frontend::AST::RangeExpr>(expr)) {
        result = emit_range_expr(range);
    } else if (auto frame_init = std::dynamic_pointer_cast<Frontend::AST::FrameInstantiationExpr>(expr)) {
        ir::Type* type = current_module_->getType(frame_init->frameName);
        if (!type) {
            std::vector<ir::Type*> fields = {ir::IntegerType::get(64), ir::IntegerType::get(64)};
            ir::StructType* struct_ty = ir::StructType::create(frame_init->frameName);
            struct_ty->setBody(fields);
            current_module_->addType(frame_init->frameName, struct_ty);
            type = struct_ty;
        }
        size_t type_size = type->getSize();
        if (type_size == 0) type_size = 16;
        ir::Value* size = ir::ConstantInt::get(ir::IntegerType::get(64), (long long)type_size);
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
             return ir::ConstantInt::get(ir::IntegerType::get(64), val);
        } else {
             ir::Function* box_string = current_module_->getFunction("lm_box_string");
             if (!box_string) {
                 box_string = builder_->createFunction("lm_box_string", ir::IntegerType::get(64), {ir::IntegerType::get(64)});
             }
             ir::Value* str_const = ir::ConstantString::get(s);
             std::string name = "$str" + std::to_string(label_counter_++);
             auto gv = new ir::GlobalVariable(ir::PointerType::get(ir::IntegerType::get(8)), name, static_cast<ir::Constant*>(str_const), false, "");
             current_module_->addGlobalVariable(gv);
             std::vector<ir::Value*> args = {gv};
             return builder_->createCall(box_string, args);
        }
    } else if (std::holds_alternative<bool>(expr->value)) {
        return ir::ConstantInt::get(ir::IntegerType::get(64), std::get<bool>(expr->value) ? 1 : 0);
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
            ir::Value* size = ir::ConstantInt::get(ir::IntegerType::get(64), struct_ty->getSize() > 0 ? (long long)struct_ty->getSize() : 16);
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

    if (func_name == "print") {
        ir::Value* arg = emit_expression(expr->arguments[0]);
        if (arg->getType()->isPointerTy()) {
             func_name = "lm_print_str";
        } else {
             func_name = "lm_print_int";
        }
    }
    if (func_name == "assert") func_name = "lm_assert";

    ir::Function* callee = current_module_->getFunction(func_name);
    if (!callee) {
        std::vector<ir::Type*> params;
        if (!args.empty()) params.push_back(args[0]->getType());
        for (const auto& arg : expr->arguments) {
             params.push_back(ir::IntegerType::get(64));
        }
        callee = builder_->createFunction(func_name, ir::VoidType::get(), params);
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
                    ir::Value* field_ptr = builder_->createAdd(obj, ir::ConstantInt::get(ir::IntegerType::get(64), (long long)offset));
                    builder_->createStore(val, field_ptr);
                    return val;
                }
            }
        } else if (expr->index) {
            ir::Function* list_set = current_module_->getFunction("lm_list_set");
            if (!list_set) list_set = builder_->createFunction("lm_list_set", ir::VoidType::get(), {ir::IntegerType::get(64), ir::IntegerType::get(64), ir::IntegerType::get(64)});
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
    ir::Value* obj = emit_expression(expr->object);
    ir::Value* idx = emit_expression(expr->index);
    ir::Function* list_get = current_module_->getFunction("lm_list_get");
    if (!list_get) list_get = builder_->createFunction("lm_list_get", ir::IntegerType::get(64), {ir::IntegerType::get(64), ir::IntegerType::get(64)});
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
            ir::Value* field_ptr = builder_->createAdd(obj, ir::ConstantInt::get(ir::IntegerType::get(64), (long long)offset));
            return builder_->createLoad(field_ptr);
        }
    }
    return obj;
}

ir::Value* FyraIRGenerator::emit_list_expr(
    const std::shared_ptr<Frontend::AST::ListExpr>& expr) {
    ir::Function* list_new = current_module_->getFunction("lm_list_new");
    if (!list_new) list_new = builder_->createFunction("lm_list_new", ir::IntegerType::get(64), {});
    ir::Value* list = builder_->createCall(list_new, {});
    ir::Function* list_append = current_module_->getFunction("lm_list_append");
    if (!list_append) list_append = builder_->createFunction("lm_list_append", ir::VoidType::get(), {ir::IntegerType::get(64), ir::IntegerType::get(64)});
    for (const auto& elem_expr : expr->elements) {
        ir::Value* elem = emit_expression(elem_expr);
        builder_->createCall(list_append, {list, elem});
    }
    return list;
}

ir::Value* FyraIRGenerator::emit_dict_expr(
    const std::shared_ptr<Frontend::AST::DictExpr>& expr) {
    ir::Function* dict_new = current_module_->getFunction("jit_dict_new");
    if (!dict_new) dict_new = builder_->createFunction("jit_dict_new", ir::IntegerType::get(64), {});
    ir::Value* dict = builder_->createCall(dict_new, {});
    ir::Function* dict_set = current_module_->getFunction("lm_dict_set");
    if (!dict_set) dict_set = builder_->createFunction("lm_dict_set", ir::VoidType::get(), {ir::IntegerType::get(64), ir::IntegerType::get(64), ir::IntegerType::get(64)});
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
    ir::Instruction* slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), type);
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
            ir::Instruction* self_slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), self_type);
            self_slot->setName("slot_self");
            builder_->createStore(it->get(), self_slot);
            current_locals_["self"] = self_slot;
            ++it;
        }
        for (size_t i = 0; i < method->parameters.size() && it != params.end(); ++i, ++it) {
            std::string param_name = method->parameters[i].first;
            ir::Type* p_type = it->get()->getType();
            ir::Instruction* p_slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), p_type);
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
    ir::Value* iterable = emit_expression(stmt->iterable);
    ir::Function* func = builder_->getInsertPoint()->getParent();
    ir::Function* list_len = current_module_->getFunction("lm_list_len");
    if (!list_len) list_len = builder_->createFunction("lm_list_len", ir::IntegerType::get(64), {ir::IntegerType::get(64)});
    ir::Value* len = builder_->createCall(list_len, {iterable});
    ir::Instruction* counter_slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), ir::IntegerType::get(64));
    builder_->createStore(ir::ConstantInt::get(ir::IntegerType::get(64), 0), counter_slot);
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
    if (!list_get) list_get = builder_->createFunction("lm_list_get", ir::IntegerType::get(64), {ir::IntegerType::get(64), ir::IntegerType::get(64)});
    ir::Value* element = builder_->createCall(list_get, {iterable, counter});
    if (!stmt->loopVars.empty()) {
        ir::Instruction* var_slot = builder_->createAlloc(ir::ConstantInt::get(ir::IntegerType::get(64), 8), ir::IntegerType::get(64));
        builder_->createStore(element, var_slot);
        current_locals_[stmt->loopVars[0]] = var_slot;
    }
    emit_statement(stmt->body);
    ir::Value* next_counter = builder_->createAdd(counter, ir::ConstantInt::get(ir::IntegerType::get(64), 1));
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
    ir::Function* print_int = current_module_->getFunction("lm_print_int");
    if (!print_int) print_int = builder_->createFunction("lm_print_int", ir::VoidType::get(), {ir::IntegerType::get(64)});
    for (const auto& arg : stmt->arguments) {
        ir::Value* val = emit_expression(arg);
        if (val) builder_->createCall(print_int, {val});
    }
}

void FyraIRGenerator::emit_return_statement(
    const std::shared_ptr<Frontend::AST::ReturnStatement>& stmt) {
    if (stmt->value) builder_->createRet(emit_expression(stmt->value));
    else builder_->createRet(nullptr);
}

ir::Type* FyraIRGenerator::ast_type_to_fyra_type(const std::string& ast_type) {
    if (ast_type == "int" || ast_type == "i64") return ir::IntegerType::get(64);
    if (ast_type == "i32") return ir::IntegerType::get(32);
    if (ast_type == "i8" || ast_type == "u8") return ir::IntegerType::get(8);
    if (ast_type == "float" || ast_type == "f64") return ir::DoubleType::get();
    if (ast_type == "bool") return ir::IntegerType::get(64);
    if (ast_type == "void") return ir::VoidType::get();
    ir::Type* ty = current_module_->getType(ast_type);
    if (ty) return ir::PointerType::get(ty);
    return ir::IntegerType::get(64);
}

} // namespace LM::Backend::Fyra
