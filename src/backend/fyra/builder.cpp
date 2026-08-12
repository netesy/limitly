// builder.cpp - LIR to Fyra IR Conversion Implementation
#include "builder.hh"
#include "../../lir/lir.hh"
#include "capability_mapper.hh"
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
#include "../../lir/function_registry.hh"
#include "../../lir/builtin_functions.hh"

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
    LIR::LIRBuiltinFunctions::getInstance().initialize();
    current_module_ = std::make_shared<ir::Module>(lir_func.name, context_);
    builder_->setModule(current_module_.get());
    used_builtins_.clear();

    // 1. Declare all functions upfront to support forward references and correct recursion
    ir::Function* main_fn = builder_->createFunction(lir_func.name, context_->getIntegerType(64));

    auto& registry = LIR::FunctionRegistry::getInstance();
    for (const auto& func_name : registry.getFunctionNames()) {
        if (func_name == lir_func.name) continue;
        if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) continue;
        auto* f = registry.getFunction(func_name);
        if (!f) continue;

        std::vector<ir::Type*> param_types;
        for (size_t i = 0; i < f->param_count; ++i) {
            param_types.push_back(context_->getIntegerType(64));
        }

        ir::Type* ret_type = context_->getIntegerType(64);
        builder_->createFunction(func_name, ret_type, param_types);
    }

    // 2. Build the top-level main function body
    build_function_body(main_fn, lir_func);

    // 3. Build the bodies of all other registered functions
    for (const auto& func_name : registry.getFunctionNames()) {
        if (func_name == lir_func.name) continue;
        if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) continue;
        auto* f = registry.getFunction(func_name);
        if (!f) continue;

        ir::Function* fn = current_module_->getFunction(func_name);
        if (fn) {
            build_function_body(fn, *f);
        }
    }

    FyraBuiltinFunctions::emit_used_builtins(current_module_.get(), builder_.get(), used_builtins_);
    return current_module_;
}

void LIRToFyraIRBuilder::build_function_body(ir::Function* main_fn, const LIR::LIR_Function& lir_func) {
    ir::BasicBlock* entry_bb = builder_->createBasicBlock("entry", main_fn);
    builder_->setInsertPoint(entry_bb);

    std::unordered_map<uint32_t, size_t> label_to_index;
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        if (lir_func.instructions[i].op == LIR::LIR_Op::Label) {
            label_to_index[lir_func.instructions[i].imm] = i;
        }
    }

    std::unordered_set<size_t> leaders;
    leaders.insert(0);
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        const auto& inst = lir_func.instructions[i];
        if (inst.op == LIR::LIR_Op::Jump || inst.op == LIR::LIR_Op::JumpIf || inst.op == LIR::LIR_Op::JumpIfFalse) {
            if (label_to_index.count(inst.imm)) {
                leaders.insert(label_to_index[inst.imm]);
            } else if (inst.imm < lir_func.instructions.size()) {
                leaders.insert(inst.imm);
            }
            if (i + 1 < lir_func.instructions.size()) {
                leaders.insert(i + 1);
            }
        } else if (inst.op == LIR::LIR_Op::Label) {
            leaders.insert(i);
            if (i + 1 < lir_func.instructions.size()) {
                leaders.insert(i + 1);
            }
        }
    }

    std::unordered_map<size_t, ir::BasicBlock*> block_map;
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        if (leaders.count(i)) {
            std::string block_name = "block_" + std::to_string(i);
            block_map[i] = builder_->createBasicBlock(block_name, main_fn);
        }
    }

    auto get_target_block = [&](uint32_t target_imm, size_t current_inst_index) -> ir::BasicBlock* {
        if (label_to_index.count(target_imm)) {
            size_t target_idx = label_to_index[target_imm];
            if (block_map.count(target_idx)) {
                return block_map[target_idx];
            }
        } else if (block_map.count(target_imm)) {
            return block_map[target_imm];
        }
        return nullptr;
    };

    std::unordered_map<uint32_t, ir::Value*> regs;

    // Initialize registers from function parameters
    size_t param_idx = 0;
    for (const auto& param : main_fn->getParameters()) {
        regs[param_idx] = param.get();
        param_idx++;
    }

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
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        const auto& inst = lir_func.instructions[i];

        if (block_map.count(i)) {
            if (!terminated && builder_->getInsertPoint() && i > 0) {
                builder_->createJmp(block_map[i]);
            }
            builder_->setInsertPoint(block_map[i]);
            terminated = false;
        }

        if (inst.op == LIR::LIR_Op::Label) {
            continue;
        }

        if (terminated) continue;

        switch (inst.op) {
            case LIR::LIR_Op::Mov:
                store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type);
                break;
            case LIR::LIR_Op::LoadConst: {
                LmValue val = inst.const_val;
                if (IS_INT(val)) {
                    // Load tagged SMI directly
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), val);
                    store_reg(inst.dst, c, inst.result_type);
                } else if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h->type_id == TYPE_BOX) {
                        LmBox* box = (LmBox*)h;
                        if (box->type == LM_BOX_STRING) {
                            const char* s = (char*)box->value.as_ptr;
                            ir::Value* str_const = context_->getConstantString(s);
                            std::string name = "str_const_" + std::to_string(label_counter_++);
                            auto gv = std::make_unique<ir::GlobalVariable>(
                                context_->getPointerType(context_->getIntegerType(8)),
                                name, static_cast<ir::Constant*>(str_const), false, ".data"
                            );
                            ir::Value* raw_str_ptr = gv.get();
                            current_module_->addGlobalVariable(std::move(gv));

                            // Box the string at runtime
                            used_builtins_.insert("lm_box_string");
                            ir::Function* box_fn = current_module_->getFunction("lm_box_string");
                            if (!box_fn) {
                                box_fn = builder_->createFunction("lm_box_string", context_->getIntegerType(64), {context_->getPointerType(context_->getIntegerType(8))});
                            }
                            ir::Value* boxed_str = builder_->createCall(box_fn, {raw_str_ptr}, context_->getIntegerType(64));
                            store_reg(inst.dst, boxed_str, inst.result_type);
                        } else if (box->type == LM_BOX_INT) {
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), BOX_INT(box->value.as_int));
                            store_reg(inst.dst, c, inst.result_type);
                        } else if (box->type == LM_BOX_FLOAT) {
                            double fval = box->value.as_float;
                            union {
                                double d;
                                uint64_t u;
                            } cast_val;
                            cast_val.d = fval;

                            // Box the float at runtime from bits to prevent XMM mismatches
                            used_builtins_.insert("lm_box_float_from_bits");
                            ir::Function* box_fn = current_module_->getFunction("lm_box_float_from_bits");
                            if (!box_fn) {
                                box_fn = builder_->createFunction("lm_box_float_from_bits", context_->getIntegerType(64), {context_->getIntegerType(64)});
                            }
                            ir::Value* bit_val = context_->getConstantInt(context_->getIntegerType(64), cast_val.u);
                            ir::Value* boxed_flt = builder_->createCall(box_fn, {bit_val}, context_->getIntegerType(64));
                            store_reg(inst.dst, boxed_flt, inst.result_type);
                        } else if (box->type == LM_BOX_BOOL) {
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), box->value.as_bool ? VAL_TRUE : VAL_FALSE);
                            store_reg(inst.dst, c, inst.result_type);
                        } else {
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                            store_reg(inst.dst, c, inst.result_type);
                        }
                    } else {
                        ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                        store_reg(inst.dst, c, inst.result_type);
                    }
                } else {
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), val);
                    store_reg(inst.dst, c, inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::Add: store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Sub: store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Mul: store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Div: store_reg(inst.dst, builder_->createDiv(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Mod: store_reg(inst.dst, builder_->createRem(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Neg: store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type); break;
            case LIR::LIR_Op::Shl: store_reg(inst.dst, builder_->createShl(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Shr: store_reg(inst.dst, builder_->createShr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
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
                ir::BasicBlock* target = get_target_block(inst.imm, i);
                if (target) {
                    builder_->createJmp(target);
                    terminated = true;
                } else errors_.push_back("Jump to unknown target: " + std::to_string(inst.imm));
                break;
            }
            case LIR::LIR_Op::JumpIf:
            case LIR::LIR_Op::JumpIfFalse: {
                ir::BasicBlock* target = get_target_block(inst.imm, i);
                if (target) {
                    ir::BasicBlock* fallthrough = block_map[i + 1];
                    ir::Value* cond = load_reg(inst.a, inst.type_a);
                    if (inst.op == LIR::LIR_Op::JumpIfFalse) builder_->createBr(cond, fallthrough, target);
                    else builder_->createBr(cond, target, fallthrough);
                    builder_->setInsertPoint(fallthrough);
                } else errors_.push_back("Cond jump to unknown target: " + std::to_string(inst.imm));
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
                if (name.empty()) {
                    if (LIR::BuiltinUtils::isBuiltinFunction(lir_func.name)) {
                        name = lir_func.name;
                    }
                }

                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));

                if (name == "print" && !args.empty()) {
                    if (args[0]->getType()->isPointerTy()) {
                        name = "lm_print_str";
                    } else {
                        name = "lm_print_int";
                    }
                } else if (FyraBuiltinFunctions::is_builtin(name)) {
                    name = FyraBuiltinFunctions::get_internal_name(name);
                }

                used_builtins_.insert(name);

                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < args.size(); ++k) pts.push_back(args[k]->getType());
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
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
                if (name.empty()) {
                    if (LIR::BuiltinUtils::isBuiltinFunction(lir_func.name)) {
                        name = lir_func.name;
                    }
                }

                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));

                if (name == "print" && !args.empty()) {
                    if (args[0]->getType()->isPointerTy()) {
                        name = "lm_print_str";
                    } else {
                        name = "lm_print_int";
                    }
                } else if (FyraBuiltinFunctions::is_builtin(name)) {
                    name = FyraBuiltinFunctions::get_internal_name(name);
                }

                used_builtins_.insert(name);

                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < args.size(); ++k) pts.push_back(args[k]->getType());
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
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
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::STR_CONCAT: {
                used_builtins_.insert("lm_str_concat");
                ir::Function* fn = current_module_->getFunction("lm_str_concat");
                if (!fn) fn = builder_->createFunction("lm_str_concat", context_->getPointerType(context_->getIntegerType(8)), {context_->getPointerType(context_->getIntegerType(8)), context_->getPointerType(context_->getIntegerType(8))});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::STR_FORMAT: {
                used_builtins_.insert("lm_rt_str_format");
                ir::Function* fn = current_module_->getFunction("lm_rt_str_format");
                if (!fn) fn = builder_->createFunction("lm_rt_str_format", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ConstructError: {
                used_builtins_.insert("lm_error_new");
                ir::Function* fn = current_module_->getFunction("lm_error_new");
                if (!fn) fn = builder_->createFunction("lm_error_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
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
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
                if (inst.a != 0 || inst.type_a != LIR::Type::Void) {
                    ir::Value* ret_val = load_reg(inst.a, inst.type_a);
                    builder_->createRet(ret_val);
                } else {
                    builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
                }
                terminated = true;
                break;
            case LIR::LIR_Op::Nop: break;
            // Memory Operations
            case LIR::LIR_Op::MemoryAlloc: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::MemoryAlloc);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a)};
                    ir::Value* res = builder_->createExternCall(cap->name, args, lir_type_to_fyra_type(inst.result_type));
                    store_reg(inst.dst, res, inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::MemoryFree: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::MemoryFree);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a)};
                    builder_->createExternCall(cap->name, args, nullptr);
                }
                break;
            }
            case LIR::LIR_Op::MemoryResize: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::MemoryResize);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)};
                    ir::Value* res = builder_->createExternCall(cap->name, args, lir_type_to_fyra_type(inst.result_type));
                    store_reg(inst.dst, res, inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::MemoryCopy: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::MemoryCopy);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b), context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)};
                    builder_->createExternCall(cap->name, args, nullptr);
                }
                break;
            }
            case LIR::LIR_Op::MemoryFill: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::MemoryFill);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b), context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)};
                    builder_->createExternCall(cap->name, args, nullptr);
                }
                break;
            }
            case LIR::LIR_Op::MemoryCompare: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::MemoryCompare);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b), context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)};
                    ir::Value* res = builder_->createExternCall(cap->name, args, lir_type_to_fyra_type(inst.result_type));
                    store_reg(inst.dst, res, inst.result_type);
                }
                break;
            }
            // Pointer Operations - use Fyra IR arithmetic directly
            case LIR::LIR_Op::PtrAdd:
                store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::PtrSub:
                store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::PtrDiff:
                store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::PtrAlign: {
                // Alignment: (ptr + (alignment - 1)) & ~(alignment - 1)
                ir::Value* align_minus_one = builder_->createSub(load_reg(inst.b, inst.type_b), context_->getConstantInt(context_->getIntegerType(64), 1));
                ir::Value* aligned = builder_->createAdd(load_reg(inst.a, inst.type_a), align_minus_one);
                ir::Value* mask = builder_->createXor(align_minus_one, context_->getConstantInt(context_->getIntegerType(64), -1));
                store_reg(inst.dst, builder_->createAnd(aligned, mask), inst.result_type);
                break;
            }
            case LIR::LIR_Op::PtrIsAligned: {
                // Check if (ptr & (alignment - 1)) == 0
                ir::Value* align_minus_one = builder_->createSub(load_reg(inst.b, inst.type_b), context_->getConstantInt(context_->getIntegerType(64), 1));
                ir::Value* masked = builder_->createAnd(load_reg(inst.a, inst.type_a), align_minus_one);
                store_reg(inst.dst, builder_->createCeq(masked, context_->getConstantInt(context_->getIntegerType(64), 0)), inst.result_type);
                break;
            }
            // Dynamic Linking Operations
            case LIR::LIR_Op::LibraryLoad: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::LibraryLoad);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a)};
                    ir::Value* res = builder_->createExternCall(cap->name, args, lir_type_to_fyra_type(inst.result_type));
                    store_reg(inst.dst, res, inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::LibraryUnload: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::LibraryUnload);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a)};
                    builder_->createExternCall(cap->name, args, nullptr);
                }
                break;
            }
            case LIR::LIR_Op::LibrarySymbol: {
                auto cap = CapabilityMapper::map(LIR::LIR_Op::LibrarySymbol);
                if (cap) {
                    std::vector<ir::Value*> args = {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)};
                    ir::Value* res = builder_->createExternCall(cap->name, args, lir_type_to_fyra_type(inst.result_type));
                    store_reg(inst.dst, res, inst.result_type);
                }
                break;
            }
            // Foreign Call Operations
            case LIR::LIR_Op::ForeignCall: {
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                ir::Value* callee = load_reg(inst.a, inst.type_a);
                ir::Value* res = builder_->createCall(callee, args, lir_type_to_fyra_type(inst.result_type));
                if (inst.dst != 0) store_reg(inst.dst, res, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ForeignCallDirect: {
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                ir::Value* res = builder_->createExternCall(inst.func_name, args, lir_type_to_fyra_type(inst.result_type));
                if (inst.dst != 0) store_reg(inst.dst, res, inst.result_type);
                break;
            }
            default:
                if (inst.dst != 0) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                break;
        }
    }
    if (!terminated && builder_->getInsertPoint()) builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
}

} // namespace LM::Backend::Fyra
