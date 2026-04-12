// builder.cpp - LIR to Fyra IR Conversion Builder implementation
#include "builder.hh"
#include "fyra_builtin_functions.hh"
#include "ir/PhiNode.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

namespace LM::Backend::Fyra {

LIRToFyraIRBuilder::LIRToFyraIRBuilder(std::shared_ptr<ir::IRContext> context)
    : context_(context) {}

std::string LIRToFyraIRBuilder::generate_label() {
    return "L" + std::to_string(label_counter_++);
}

ir::Type* LIRToFyraIRBuilder::lir_type_to_fyra_type(LIR::Type lir_type) {
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

std::shared_ptr<ir::Module> LIRToFyraIRBuilder::build(const LIR::LIR_Function& lir_func) {
    current_module_ = context_->createModule("limit_lir_module");
    builder_ = std::make_unique<ir::IRBuilder>(context_);
    builder_->setModule(current_module_.get());
    errors_.clear();
    used_builtins_.clear();

    ir::Function* main_fn = builder_->createFunction(lir_func.name.empty() ? "main" : lir_func.name, context_->getIntegerType(64));
    main_fn->setExported(true);

    // 1. Identify all jump targets
    std::set<uint32_t> jump_targets;
    for (const auto& inst : lir_func.instructions) {
        if (inst.op == LIR::LIR_Op::Jump || inst.op == LIR::LIR_Op::JumpIf || inst.op == LIR::LIR_Op::JumpIfFalse) {
            jump_targets.insert(inst.imm);
        }
    }

    // 2. Pre-create basic blocks for targets
    std::unordered_map<uint32_t, ir::BasicBlock*> block_map;
    for (uint32_t target_idx : jump_targets) {
        block_map[target_idx] = builder_->createBasicBlock("L" + std::to_string(target_idx), main_fn);
    }

    ir::BasicBlock* entry = builder_->createBasicBlock("entry", main_fn);
    builder_->setInsertPoint(entry);

    std::unordered_map<LIR::Reg, ir::Instruction*> register_slots;
    auto ensure_slot = [&](LIR::Reg reg, LIR::Type type) -> ir::Instruction* {
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
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        if (terminated) break;
        const auto& inst = lir_func.instructions[i];

        if (block_map.count((uint32_t)i)) {
            ir::BasicBlock* next_bb = block_map[(uint32_t)i];
            if (!builder_->getInsertPoint()->getInstructions().empty()) {
                auto last_opcode = builder_->getInsertPoint()->getInstructions().back()->getOpcode();
                if (last_opcode != ir::Instruction::Jmp && last_opcode != ir::Instruction::Br && last_opcode != ir::Instruction::Ret) {
                     builder_->createJmp(next_bb);
                }
            } else {
                 builder_->createJmp(next_bb);
            }
            builder_->setInsertPoint(next_bb);
        }

        switch (inst.op) {
            case LIR::LIR_Op::Label: break;
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
                            try { c = context_->getConstantFP(context_->getDoubleType(), std::stod(inst.const_val->data)); }
                            catch (...) { c = context_->getConstantFP(context_->getDoubleType(), 0.0); errors_.push_back("Failed to parse float: " + inst.const_val->data); }
                            break;
                        case TypeTag::String: {
                            used_builtins_.insert("lm_box_string");
                            ir::Function* box_string = current_module_->getFunction("lm_box_string");
                            if (!box_string) box_string = builder_->createFunction("lm_box_string", context_->getPointerType(context_->getIntegerType(8)), {context_->getPointerType(context_->getIntegerType(8))});
                            ir::Value* str_const = context_->getConstantString(inst.const_val->data);
                            std::string name = "$str_" + std::to_string(label_counter_++);
                            auto gv = std::make_unique<ir::GlobalVariable>(context_->getPointerType(context_->getIntegerType(8)), name, static_cast<ir::Constant*>(str_const), false, ".data");
                            ir::GlobalVariable* gv_ptr = gv.get();
                            current_module_->addGlobalVariable(std::move(gv));
                            c = builder_->createCall(box_string, {gv_ptr});
                            break;
                        }
                        default:
                            if (inst.const_val->data == "nil") c = context_->getConstantInt(context_->getIntegerType(64), 0);
                            else {
                                try { c = context_->getConstantInt(context_->getIntegerType(64), std::stoll(inst.const_val->data)); }
                                catch (...) { c = context_->getConstantInt(context_->getIntegerType(64), 0); errors_.push_back("Failed to parse int: " + inst.const_val->data); }
                            }
                            break;
                    }
                } else {
                    if (inst.const_val->data == "nil") c = context_->getConstantInt(context_->getIntegerType(64), 0);
                    else {
                        try { c = context_->getConstantInt(context_->getIntegerType(64), std::stoll(inst.const_val->data)); }
                        catch (...) { c = context_->getConstantInt(context_->getIntegerType(64), 0); errors_.push_back("Failed to parse untyped: " + inst.const_val->data); }
                    }
                }
                store_reg(inst.dst, c, inst.result_type);
                break;
            }
            case LIR::LIR_Op::Mov:
            case LIR::LIR_Op::Copy:
                store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type);
                break;
            case LIR::LIR_Op::Add: store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Sub: store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Mul: store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Div: store_reg(inst.dst, builder_->createDiv(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Mod: store_reg(inst.dst, builder_->createRem(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Neg: store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type); break;
            case LIR::LIR_Op::And: store_reg(inst.dst, builder_->createAnd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Or: store_reg(inst.dst, builder_->createOr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Xor: store_reg(inst.dst, builder_->createXor(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpEQ: store_reg(inst.dst, builder_->createCeq(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpNEQ: store_reg(inst.dst, builder_->createCne(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpLT: store_reg(inst.dst, builder_->createCslt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpLE: store_reg(inst.dst, builder_->createCsle(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpGT: store_reg(inst.dst, builder_->createCsgt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpGE: store_reg(inst.dst, builder_->createCsge(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Jump: {
                if (block_map.count(inst.imm)) builder_->createJmp(block_map[inst.imm]);
                else errors_.push_back("Jump to unknown index: " + std::to_string(inst.imm));
                break;
            }
            case LIR::LIR_Op::JumpIf:
            case LIR::LIR_Op::JumpIfFalse: {
                if (block_map.count(inst.imm)) {
                    ir::BasicBlock* fallthrough = builder_->createBasicBlock(generate_label() + "_cont", main_fn);
                    ir::Value* cond = load_reg(inst.a, inst.type_a);
                    if (inst.op == LIR::LIR_Op::JumpIfFalse) builder_->createBr(cond, fallthrough, block_map[inst.imm]);
                    else builder_->createBr(cond, block_map[inst.imm], fallthrough);
                    builder_->setInsertPoint(fallthrough);
                } else errors_.push_back("Cond jump to unknown index: " + std::to_string(inst.imm));
                break;
            }
            case LIR::LIR_Op::Call:
            case LIR::LIR_Op::CallVoid: {
                std::string name = inst.func_name; if (name.empty() && inst.const_val) name = inst.const_val->data;
                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < inst.call_args.size(); ++k) pts.push_back(context_->getIntegerType(64));
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                ir::Value* res = builder_->createCall(func, args);
                if (inst.op == LIR::LIR_Op::Call) store_reg(inst.dst, res, inst.result_type);
                break;
            }
            case LIR::LIR_Op::CallBuiltin: {
                std::string name = inst.func_name; if (name.empty() && inst.const_val) name = inst.const_val->data;
                used_builtins_.insert(name);
                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < inst.call_args.size(); ++k) pts.push_back(context_->getIntegerType(64));
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                store_reg(inst.dst, builder_->createCall(func, args), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Load: store_reg(inst.dst, builder_->createLoad(load_reg(inst.a, inst.type_a)), inst.result_type); break;
            case LIR::LIR_Op::Store: builder_->createStore(load_reg(inst.b, inst.type_b), load_reg(inst.a, inst.type_a)); break;
            case LIR::LIR_Op::Cast: store_reg(inst.dst, builder_->createCast(load_reg(inst.a, inst.type_a), lir_type_to_fyra_type(inst.result_type)), inst.result_type); break;
            case LIR::LIR_Op::ToString: {
                used_builtins_.insert("lm_to_string");
                ir::Function* fn = current_module_->getFunction("lm_to_string");
                if (!fn) fn = builder_->createFunction("lm_to_string", context_->getPointerType(context_->getIntegerType(8)), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::STR_CONCAT: {
                used_builtins_.insert("lm_str_concat");
                ir::Function* fn = current_module_->getFunction("lm_str_concat");
                if (!fn) fn = builder_->createFunction("lm_str_concat", context_->getPointerType(context_->getIntegerType(8)), {context_->getPointerType(context_->getIntegerType(8)), context_->getPointerType(context_->getIntegerType(8))});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ConstructError: {
                used_builtins_.insert("lm_error_new");
                ir::Function* fn = current_module_->getFunction("lm_error_new");
                if (!fn) fn = builder_->createFunction("lm_error_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ConstructOk: store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type); break;
            case LIR::LIR_Op::IsError: {
                ir::Value* val = load_reg(inst.a, inst.type_a);
                ir::Value* thr = context_->getConstantInt(context_->getIntegerType(64), 0x7FFFFFFFFFFFFFFF);
                store_reg(inst.dst, builder_->createCsgt(val, thr), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Unwrap: store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type); break;
            case LIR::LIR_Op::ListCreate: {
                used_builtins_.insert("lm_list_new");
                ir::Function* fn = current_module_->getFunction("lm_list_new");
                if (!fn) fn = builder_->createFunction("lm_list_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ListAppend: {
                used_builtins_.insert("lm_list_append");
                ir::Function* fn = current_module_->getFunction("lm_list_append");
                if (!fn) fn = builder_->createFunction("lm_list_append", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64)});
                builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)});
                break;
            }
            case LIR::LIR_Op::ListIndex: {
                used_builtins_.insert("lm_list_get");
                ir::Function* fn = current_module_->getFunction("lm_list_get");
                if (!fn) fn = builder_->createFunction("lm_list_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ListLen: {
                used_builtins_.insert("lm_list_len");
                ir::Function* fn = current_module_->getFunction("lm_list_len");
                if (!fn) fn = builder_->createFunction("lm_list_len", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::NewFrame: {
                std::string name = inst.func_name; if (name.empty()) name = "Frame";
                ir::Type* type = current_module_->getType(name);
                if (!type) { ir::StructType* st = context_->createStructType(name); st->setBody({context_->getIntegerType(64), context_->getIntegerType(64)}); current_module_->addType(name, st); type = st; }
                store_reg(inst.dst, builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 16), type), inst.result_type);
                break;
            }
            case LIR::LIR_Op::FrameGetField: {
                ir::Value* addr = builder_->createAdd(load_reg(inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm * 8));
                store_reg(inst.dst, builder_->createLoad(addr), inst.result_type);
                break;
            }
            case LIR::LIR_Op::FrameSetField: {
                ir::Value* addr = builder_->createAdd(load_reg(inst.dst, inst.result_type), context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm * 8));
                builder_->createStore(load_reg(inst.a, inst.type_a), addr);
                break;
            }
            case LIR::LIR_Op::PrintInt:
            case LIR::LIR_Op::PrintUint:
            case LIR::LIR_Op::PrintFloat:
            case LIR::LIR_Op::PrintBool:
            case LIR::LIR_Op::PrintString: {
                std::string b = "lm_print_int"; ir::Type* at = context_->getIntegerType(64);
                if (inst.op == LIR::LIR_Op::PrintFloat) { b = "lm_print_float"; at = context_->getDoubleType(); }
                else if (inst.op == LIR::LIR_Op::PrintBool) b = "lm_print_bool";
                else if (inst.op == LIR::LIR_Op::PrintString) { b = "lm_print_str"; at = context_->getPointerType(context_->getIntegerType(8)); }
                else if (inst.op == LIR::LIR_Op::PrintUint) b = "lm_print_uint";
                used_builtins_.insert(b);
                ir::Function* fn = current_module_->getFunction(b);
                if (!fn) fn = builder_->createFunction(b, context_->getVoidType(), {at});
                builder_->createCall(fn, {load_reg(inst.a, inst.type_a)});
                break;
            }
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
                if (inst.a != 0 || inst.type_a != LIR::Type::Void) builder_->createRet(load_reg(inst.a, inst.type_a));
                else builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
                terminated = true;
                break;
            case LIR::LIR_Op::Nop: break;
            default:
                if (inst.dst != 0) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                break;
        }
    }
    if (!terminated && builder_->getInsertPoint()) builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
    FyraBuiltinFunctions::emit_used_builtins(current_module_.get(), builder_.get(), used_builtins_);
    return current_module_;
}

} // namespace LM::Backend::Fyra
