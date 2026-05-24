// builder.cpp - LIR to Fyra IR Conversion Implementation
#include "builder.hh"
#include "../../lir/lir.hh"
#include "ir/Module.h"
#include "ir/Function.h"
#include "ir/IRBuilder.h"
#include "ir/IRContext.h"
#include "ir/Type.h"
#include "ir/Value.h"
#include "ir/Constant.h"
#include "fyra_builtin_functions.hh"
#include "../../runtime/runtime_value_base.h"
#include "../../runtime/runtime.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace LM::Backend::Fyra {

LIRToFyraIRBuilder::LIRToFyraIRBuilder(std::shared_ptr<ir::IRContext> context)
    : context_(context), builder_(std::make_unique<ir::IRBuilder>(context)) {
}

ir::Type* LIRToFyraIRBuilder::lir_type_to_fyra_type(LIR::Type lir_type) {
    switch (lir_type) {
        case LIR::Type::Void: return context_->getVoidType();
        case LIR::Type::I64:
        case LIR::Type::Bool: return context_->getIntegerType(64);
        case LIR::Type::F64: return context_->getDoubleType();
        case LIR::Type::Ptr: return context_->getPointerType(context_->getIntegerType(8));
        default: return context_->getIntegerType(64);
    }
}

std::string LIRToFyraIRBuilder::generate_label() {
    return "label_" + std::to_string(label_counter_++);
}

std::shared_ptr<ir::Module> LIRToFyraIRBuilder::build(const LIR::LIR_Function& lir_func) {
    current_module_ = std::make_shared<ir::Module>(lir_func.name, context_);
    builder_->setModule(current_module_.get());
    used_builtins_.clear();

    ir::Function* main_fn = builder_->createFunction(lir_func.name, context_->getIntegerType(64));
    ir::BasicBlock* entry_bb = builder_->createBasicBlock("entry", main_fn);
    builder_->setInsertPoint(entry_bb);

    std::unordered_map<uint32_t, ir::BasicBlock*> block_map;
    if (lir_func.cfg && !lir_func.cfg->blocks.empty()) {
        for (const auto& block : lir_func.cfg->blocks) {
            block_map[block->id] = builder_->createBasicBlock(block->label.empty() ? "block_" + std::to_string(block->id) : block->label, main_fn);
        }
    } else {
        for (const auto& inst : lir_func.instructions) {
            if (inst.op == LIR::LIR_Op::Label) {
                block_map[inst.imm] = builder_->createBasicBlock("label_" + std::to_string(inst.imm), main_fn);
            }
        }
    }

    std::unordered_map<uint32_t, ir::Value*> regs;
    auto load_reg = [&](uint32_t r, LIR::Type t) -> ir::Value* {
        if (regs.count(r)) return regs[r];
        ir::Type* fty = lir_type_to_fyra_type(t);
        if (fty->isIntegerTy()) {
            return context_->getConstantInt(static_cast<ir::IntegerType*>(fty), 0);
        }
        return context_->getConstantInt(context_->getIntegerType(64), 0);
    };
    auto store_reg = [&](uint32_t r, ir::Value* v, LIR::Type t) {
        regs[r] = v;
    };

    bool terminated = false;
    for (const auto& inst : lir_func.instructions) {
        if (inst.op == LIR::LIR_Op::Label) {
            if (!terminated && builder_->getInsertPoint()) builder_->createJmp(block_map[inst.imm]);
            builder_->setInsertPoint(block_map[inst.imm]);
            terminated = false;
            continue;
        }

        if (terminated) continue;

        switch (inst.op) {
            case LIR::LIR_Op::Mov:
                store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type);
                break;
            case LIR::LIR_Op::LoadConst: {
                ir::Value* c = nullptr;
                LmValue val = inst.const_val;
                if (IS_INT(val)) c = context_->getConstantInt(context_->getIntegerType(64), UNBOX_INT(val));
                else if (IS_PTR(val)) c = context_->getConstantInt(context_->getIntegerType(64), (uintptr_t)UNBOX_PTR(val));
                else c = context_->getConstantInt(context_->getIntegerType(64), val);
                store_reg(inst.dst, c, inst.result_type);
                break;
            }
            case LIR::LIR_Op::Add: store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Sub: store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Mul: store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Div: store_reg(inst.dst, builder_->createDiv(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::And: store_reg(inst.dst, builder_->createAnd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Or:  store_reg(inst.dst, builder_->createOr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Xor: store_reg(inst.dst, builder_->createXor(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpEQ: store_reg(inst.dst, builder_->createCeq(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpNEQ: store_reg(inst.dst, builder_->createCne(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpLT: store_reg(inst.dst, builder_->createCslt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpLE: store_reg(inst.dst, builder_->createCsle(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpGT: store_reg(inst.dst, builder_->createCsgt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpGE: store_reg(inst.dst, builder_->createCsge(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Jump: {
                if (block_map.count(inst.imm)) {
                    builder_->createJmp(block_map[inst.imm]);
                    terminated = true;
                } else errors_.push_back("Jump to unknown label ID: " + std::to_string(inst.imm));
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
                } else errors_.push_back("Cond jump to unknown label ID: " + std::to_string(inst.imm));
                break;
            }
            case LIR::LIR_Op::Call:
            case LIR::LIR_Op::CallVoid: {
                std::string name = inst.func_name; 
                if (name.empty() && inst.const_val) {
                    if (IS_PTR(inst.const_val)) {
                        ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                        if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                            name = (char*)((LmBox*)h)->value.as_ptr;
                        }
                    }
                }
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
            case LIR::LIR_Op::CallIndirect: {
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                ir::Value* callee = load_reg(inst.a, inst.type_a);
                ir::Value* res = builder_->createCall(callee, args, lir_type_to_fyra_type(inst.result_type));
                if (inst.dst != 0) store_reg(inst.dst, res, inst.result_type);
                break;
            }
            case LIR::LIR_Op::CallBuiltin: {
                std::string name = inst.func_name; 
                if (name.empty() && inst.const_val) {
                    if (IS_PTR(inst.const_val)) {
                        ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                        if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                            name = (char*)((LmBox*)h)->value.as_ptr;
                        }
                    }
                }
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
            case LIR::LIR_Op::Cast:
            case LIR::LIR_Op::DecRescale:
                store_reg(inst.dst, builder_->createCast(load_reg(inst.a, inst.type_a), lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
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
