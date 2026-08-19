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
#include "backend/vm/vm_value_base.hh"
#include "backend/vm/vm_runtime.hh"
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
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

    std::string main_name = lir_func.name;
    if (main_name == "__top_level_wrapper__") main_name = "main";
    ir::Function* main_fn = builder_->createFunction(main_name, context_->getIntegerType(64));

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
    std::unordered_map<uint32_t, LIR::Type> reg_types;
    std::unordered_map<uint32_t, int> reg_decimal_scales;
    std::unordered_map<uint32_t, int64_t> reg_int_values;
    std::unordered_map<uint32_t, double> reg_float_values;
    std::unordered_map<uint32_t, std::string> reg_string_literals;

    auto decimal_scale_for_reg = [&](uint32_t r) -> int {
        if (reg_decimal_scales.count(r)) return reg_decimal_scales[r];
        auto it = lir_func.register_language_types.find(r);
        if (it != lir_func.register_language_types.end() && it->second) {
            int scale = it->second->getDecimalScale();
            if (scale > 0) return scale;
        }
        return -1;
    };

    auto decimal_scale_for_inst = [&](const LIR::LIR_Inst& dec_inst) -> int {
        int dst_scale = decimal_scale_for_reg(dec_inst.dst);
        if (dst_scale > 0) return dst_scale;
        int a_scale = decimal_scale_for_reg(dec_inst.a);
        int b_scale = decimal_scale_for_reg(dec_inst.b);
        if (a_scale > 0 && b_scale > 0) return std::max(a_scale, b_scale);
        if (a_scale > 0) return a_scale;
        if (b_scale > 0) return b_scale;
        return 4;
    };

    auto pow10_i64 = [](int n) -> int64_t {
        int64_t value = 1;
        for (int i = 0; i < n; ++i) value *= 10;
        return value;
    };

    auto format_float_literal = [](double value) -> std::string {
        std::ostringstream oss;
        oss << std::setprecision(6) << std::defaultfloat << value;
        return oss.str();
    };

    size_t max_reg = lir_func.register_count;
    for (const auto& inst : lir_func.instructions) {
        if (inst.dst != UINT32_MAX) max_reg = std::max(max_reg, (size_t)inst.dst);
        if (inst.a != UINT32_MAX) max_reg = std::max(max_reg, (size_t)inst.a);
        if (inst.b != UINT32_MAX) max_reg = std::max(max_reg, (size_t)inst.b);
        for (auto arg : inst.call_args) max_reg = std::max(max_reg, (size_t)arg);
    }
    std::unordered_map<uint32_t, ir::Instruction*> reg_slots;
    for (size_t r = 0; r <= max_reg + 10; ++r) {
        reg_slots[r] = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
        builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), reg_slots[r]);
    }

    // Initialize registers from function parameters
    size_t param_idx = 0;
    for (const auto& param : main_fn->getParameters()) {
        builder_->createStore(param.get(), reg_slots[param_idx]);
        regs[param_idx] = param.get();
        param_idx++;
    }

    if (block_map.count(0)) {
        builder_->createJmp(block_map[0]);
    }

    auto load_reg = [&](uint32_t r, LIR::Type t) -> ir::Value* {
        if (reg_slots.count(r)) {
            return builder_->createLoad(reg_slots[r]);
        }
        if (regs.count(r)) return regs[r];
        ir::Type* fty = lir_type_to_fyra_type(t);
        if (t == LIR::Type::F64 || t == LIR::Type::F32) {
            return context_->getConstantFP(context_->getDoubleType(), 0.0);
        }
        if (fty->isIntegerTy()) {
            return context_->getConstantInt(static_cast<ir::IntegerType*>(fty), 0);
        }
        return context_->getConstantInt(context_->getIntegerType(64), 0);
    };

    auto store_reg = [&](uint32_t r, ir::Value* v, LIR::Type t) {
        if (v) {
            if (v->getName().empty() && !dynamic_cast<ir::Constant*>(v)) {
                v->setName("r" + std::to_string(r));
            }
            if (reg_slots.count(r)) {
                builder_->createStore(v, reg_slots[r]);
            }
        }
        regs[r] = v;
        reg_types[r] = t;
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
                if (reg_decimal_scales.count(inst.a)) reg_decimal_scales[inst.dst] = reg_decimal_scales[inst.a];
                if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = reg_int_values[inst.a];
                if (reg_float_values.count(inst.a)) reg_float_values[inst.dst] = reg_float_values[inst.a];
                if (reg_string_literals.count(inst.a)) reg_string_literals[inst.dst] = reg_string_literals[inst.a];
                if (reg_types.count(inst.a)) reg_types[inst.dst] = reg_types[inst.a];
                store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type);
                break;
            case LIR::LIR_Op::LoadConst: {
                if (inst.type_name == "d2" || inst.type_name == "decimal") reg_decimal_scales[inst.dst] = 2;
                else if (inst.type_name == "d4") reg_decimal_scales[inst.dst] = 4;
                else if (inst.type_name == "d6") reg_decimal_scales[inst.dst] = 6;

                LmValue val = inst.const_val;
                if (IS_NIL(val) || val == 0) {
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                    reg_types[inst.dst] = LIR::Type::Ptr;
                    store_reg(inst.dst, c, LIR::Type::Ptr);
                } else if (IS_INT(val) && (((val >> 3) << 3) | TAG_INT) == val) {
                    int64_t actual_val = UNBOX_INT(val);
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                    reg_int_values[inst.dst] = actual_val;
                    store_reg(inst.dst, c, inst.result_type);
                } else if (IS_BOOL(val)) {
                    uint64_t actual_val = UNBOX_BOOL(val) ? 1 : 0;
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                    store_reg(inst.dst, c, LIR::Type::Bool);
                } else if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h->type_id == TYPE_BOX) {
                        LmBox* box = (LmBox*)h;
                        if (box->type == LM_BOX_STRING) {
                            const char* s = (char*)box->value.as_ptr;
                            reg_string_literals[inst.dst] = s;
                            ir::Value* str_const = context_->getConstantString(s);
                            std::string name = "str_const_" + std::to_string(label_counter_++);
                            auto gv = std::make_unique<ir::GlobalVariable>(
                                context_->getPointerType(context_->getIntegerType(8)),
                                name, static_cast<ir::Constant*>(str_const), false, ".data"
                            );
                            ir::Value* raw_str_ptr = gv.get();
                            current_module_->addGlobalVariable(std::move(gv));
                            
                            // Just store the raw string pointer - NO BOXING for AOT!
                            store_reg(inst.dst, raw_str_ptr, LIR::Type::Ptr);
                        } else if (box->type == LM_BOX_INT) {
                            uint64_t actual_val = (inst.result_type == LIR::Type::I64) ? box->value.as_int : BOX_INT(box->value.as_int);
                            if (inst.result_type == LIR::Type::I64) reg_int_values[inst.dst] = box->value.as_int;
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                            store_reg(inst.dst, c, inst.result_type);
                        } else if (box->type == LM_BOX_FLOAT) {
                            double fval = box->value.as_float;
                            ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                            reg_types[inst.dst] = LIR::Type::F64;
                            reg_float_values[inst.dst] = fval;
                            store_reg(inst.dst, c, LIR::Type::F64);
                        } else if (box->type == LM_BOX_BOOL) {
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), box->value.as_bool ? 1 : 0);
                            store_reg(inst.dst, c, LIR::Type::Bool);
                        } else {
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                            store_reg(inst.dst, c, inst.result_type);
                        }
                    } else if (h->type_id == TYPE_FLOAT) {
                        double fval = ((ObjFloat*)h)->value;
                        ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                        reg_types[inst.dst] = LIR::Type::F64;
                        reg_float_values[inst.dst] = fval;
                        store_reg(inst.dst, c, LIR::Type::F64);
                    } else {
                        ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                        store_reg(inst.dst, c, inst.result_type);
                    }
                } else {
                    if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) {
                        reg_types[inst.dst] = inst.result_type;
                    }
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), val);
                    store_reg(inst.dst, c, inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::StoreGlobal: {
                std::string gname = inst.func_name.empty() ? ("global_" + std::to_string(inst.dst)) : inst.func_name;
                for (char& c : gname) { if (c == '.') c = '_'; }
                ir::GlobalVariable* gv = nullptr;
                for (const auto& item : current_module_->getGlobalVariables()) {
                    if (item->getName() == gname) { gv = item.get(); break; }
                }
                if (!gv) {
                    auto new_gv = std::make_unique<ir::GlobalVariable>(
                        context_->getIntegerType(64),
                        gname,
                        context_->getConstantInt(context_->getIntegerType(64), 0),
                        false,
                        ".data"
                    );
                    gv = new_gv.get();
                    current_module_->addGlobalVariable(std::move(new_gv));
                }
                builder_->createStore(load_reg(inst.a, inst.type_a), gv);
                if (reg_decimal_scales.count(inst.a)) {
                    global_decimal_scales_[gname] = reg_decimal_scales[inst.a];
                }
                break;
            }
            case LIR::LIR_Op::LoadGlobal: {
                std::string gname = inst.func_name.empty() ? ("global_" + std::to_string(inst.a)) : inst.func_name;
                for (char& c : gname) { if (c == '.') c = '_'; }
                ir::GlobalVariable* gv = nullptr;
                for (const auto& item : current_module_->getGlobalVariables()) {
                    if (item->getName() == gname) { gv = item.get(); break; }
                }
                if (!gv) {
                    auto new_gv = std::make_unique<ir::GlobalVariable>(
                        context_->getIntegerType(64),
                        gname,
                        context_->getConstantInt(context_->getIntegerType(64), 0),
                        false,
                        ".data"
                    );
                    gv = new_gv.get();
                    current_module_->addGlobalVariable(std::move(new_gv));
                }
                ir::Value* loaded = builder_->createLoad(gv);
                store_reg(inst.dst, loaded, inst.result_type);
                if (global_decimal_scales_.count(gname)) {
                    reg_decimal_scales[inst.dst] = global_decimal_scales_[gname];
                }
                break;
            }
            case LIR::LIR_Op::Add: store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Sub: store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Mul: store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Div: store_reg(inst.dst, builder_->createDiv(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Mod: store_reg(inst.dst, builder_->createRem(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Neg:
                if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = -reg_int_values[inst.a];
                if (reg_float_values.count(inst.a)) reg_float_values[inst.dst] = -reg_float_values[inst.a];
                store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type);
                break;
            case LIR::LIR_Op::DecAdd:
                reg_decimal_scales[inst.dst] = decimal_scale_for_inst(inst);
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b)) reg_int_values[inst.dst] = reg_int_values[inst.a] + reg_int_values[inst.b];
                store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::DecSub:
                reg_decimal_scales[inst.dst] = decimal_scale_for_inst(inst);
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b)) reg_int_values[inst.dst] = reg_int_values[inst.a] - reg_int_values[inst.b];
                store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::DecMul: {
                int scale = decimal_scale_for_inst(inst);
                reg_decimal_scales[inst.dst] = scale;
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b)) reg_int_values[inst.dst] = (reg_int_values[inst.a] * reg_int_values[inst.b]) / pow10_i64(scale);
                ir::Value* product = builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                store_reg(inst.dst, builder_->createDiv(product, context_->getConstantInt(context_->getIntegerType(64), pow10_i64(scale))), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DecDiv: {
                int scale = decimal_scale_for_inst(inst);
                reg_decimal_scales[inst.dst] = scale;
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b) && reg_int_values[inst.b] != 0) reg_int_values[inst.dst] = (reg_int_values[inst.a] * pow10_i64(scale)) / reg_int_values[inst.b];
                ir::Value* numerator = builder_->createMul(load_reg(inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), pow10_i64(scale)));
                store_reg(inst.dst, builder_->createDiv(numerator, load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DecMod:
                reg_decimal_scales[inst.dst] = decimal_scale_for_inst(inst);
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b) && reg_int_values[inst.b] != 0) reg_int_values[inst.dst] = reg_int_values[inst.a] % reg_int_values[inst.b];
                store_reg(inst.dst, builder_->createRem(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::DecNeg:
                if (reg_decimal_scales.count(inst.a)) reg_decimal_scales[inst.dst] = reg_decimal_scales[inst.a];
                if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = -reg_int_values[inst.a];
                store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type);
                break;
            case LIR::LIR_Op::Shl: store_reg(inst.dst, builder_->createShl(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Shr: store_reg(inst.dst, builder_->createShr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::And: store_reg(inst.dst, builder_->createAnd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Or:  store_reg(inst.dst, builder_->createOr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::Xor: store_reg(inst.dst, builder_->createXor(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type); break;
            case LIR::LIR_Op::CmpEQ: {
                bool is_ptr = (inst.type_a == LIR::Type::Ptr || inst.type_b == LIR::Type::Ptr ||
                               (reg_types.count(inst.a) && reg_types[inst.a] == LIR::Type::Ptr) ||
                               (reg_types.count(inst.b) && reg_types[inst.b] == LIR::Type::Ptr));
                if (is_ptr) {
                    used_builtins_.insert("lm_key_eq");
                    ir::Function* fn = current_module_->getFunction("lm_key_eq");
                    if (!fn) fn = builder_->createFunction("lm_key_eq", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                    store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}), inst.result_type);
                } else {
                    store_reg(inst.dst, builder_->createCeq(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::CmpNEQ: {
                bool is_ptr = (inst.type_a == LIR::Type::Ptr || inst.type_b == LIR::Type::Ptr ||
                               (reg_types.count(inst.a) && reg_types[inst.a] == LIR::Type::Ptr) ||
                               (reg_types.count(inst.b) && reg_types[inst.b] == LIR::Type::Ptr));
                if (is_ptr) {
                    used_builtins_.insert("lm_key_eq");
                    ir::Function* fn = current_module_->getFunction("lm_key_eq");
                    if (!fn) fn = builder_->createFunction("lm_key_eq", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                    ir::Value* eq_res = builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)});
                    store_reg(inst.dst, builder_->createCeq(eq_res, context_->getConstantInt(context_->getIntegerType(64), 0)), inst.result_type);
                } else {
                    store_reg(inst.dst, builder_->createCne(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            }
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
                    terminated = true;
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
                    for (size_t ai = 0; ai < args.size(); ++ai) {
                        if (ai > 0) {
                            ir::GlobalVariable* gv_sp = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "str_space", " ");
                            builder_->createExternCall("io.write", {
                                context_->getConstantInt(context_->getIntegerType(64), 1),
                                gv_sp,
                                context_->getConstantInt(context_->getIntegerType(64), 1)
                            }, context_->getIntegerType(64));
                        }
                        LIR::Type arg_type = (ai < inst.call_arg_types.size()) ? inst.call_arg_types[ai] : LIR::Type::I64;
                        if (ai < inst.call_args.size() && reg_types.count(inst.call_args[ai])) {
                            LIR::Type reg_t = reg_types[inst.call_args[ai]];
                            if (reg_t == LIR::Type::Bool || reg_t == LIR::Type::Ptr || reg_t == LIR::Type::F64 || reg_t == LIR::Type::F32) {
                                arg_type = reg_t;
                            }
                        }
                        if (arg_type == LIR::Type::Ptr) {
                            std::string prid = std::to_string(ai) + "_" + std::to_string(rand() % 10000);
                            ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                            ir::BasicBlock* b_pr_nil = builder_->createBasicBlock("pr_nil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_nonnil = builder_->createBasicBlock("pr_nonnil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_str = builder_->createBasicBlock("pr_str_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_int = builder_->createBasicBlock("pr_int_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_next = builder_->createBasicBlock("pr_next_" + prid, cur_fn);

                            ir::Value* is_nil = builder_->createCeq(args[ai], context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                            builder_->createBr(is_nil, b_pr_nil, b_pr_nonnil);

                            builder_->setInsertPoint(b_pr_nil);
                            FyraBuiltinFunctions::emit_print_nil_inline(current_module_.get(), builder_.get());
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_nonnil);
                            ir::Value* is_str_ptr = builder_->createCuge(args[ai], context_->getConstantInt(context_->getIntegerType(64), 65536));
                            builder_->createBr(is_str_ptr, b_pr_str, b_pr_int);

                            builder_->setInsertPoint(b_pr_str);
                            FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), args[ai]);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_int);
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_next);
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            uint32_t arg_reg = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                            if (reg_float_values.count(arg_reg)) {
                                std::string fname = "float_const_" + std::to_string(label_counter_++);
                                ir::GlobalVariable* gv_float = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), fname, format_float_literal(reg_float_values[arg_reg]));
                                FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), gv_float);
                            } else {
                                FyraBuiltinFunctions::emit_print_float_inline(current_module_.get(), builder_.get(), args[ai]);
                            }
                        } else if (ai < inst.call_args.size() && reg_decimal_scales.count(inst.call_args[ai]) && reg_decimal_scales[inst.call_args[ai]] > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], reg_decimal_scales[inst.call_args[ai]]);
                        } else {
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                        }
                    }
                    ir::GlobalVariable* gv_nl = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "nl", "\n");
                    builder_->createExternCall("io.write", {
                        context_->getConstantInt(context_->getIntegerType(64), 1),
                        gv_nl,
                        context_->getConstantInt(context_->getIntegerType(64), 1)
                    }, context_->getIntegerType(64));

                    if (inst.op == LIR::LIR_Op::Call) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                } else if (name == "sleep" || name == "time.sleep" || name == "sleep_ms" || name == "time_sleep") {
                    ir::Value* res = builder_->createExternCall("process.sleep", args, lir_type_to_fyra_type(inst.result_type));
                    if (inst.op == LIR::LIR_Op::Call && inst.dst != 0) store_reg(inst.dst, res, inst.result_type);
                    break;
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
                    for (size_t ai = 0; ai < args.size(); ++ai) {
                        if (ai > 0) {
                            ir::GlobalVariable* gv_sp = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "str_space", " ");
                            builder_->createExternCall("io.write", {
                                context_->getConstantInt(context_->getIntegerType(64), 1),
                                gv_sp,
                                context_->getConstantInt(context_->getIntegerType(64), 1)
                            }, context_->getIntegerType(64));
                        }
                        LIR::Type arg_type = (ai < inst.call_arg_types.size()) ? inst.call_arg_types[ai] : LIR::Type::I64;
                        if (ai < inst.call_args.size() && reg_types.count(inst.call_args[ai])) {
                            LIR::Type reg_t = reg_types[inst.call_args[ai]];
                            if (reg_t == LIR::Type::Bool || reg_t == LIR::Type::Ptr || reg_t == LIR::Type::F64 || reg_t == LIR::Type::F32) {
                                arg_type = reg_t;
                            }
                        }
                        if (arg_type == LIR::Type::Ptr) {
                            std::string prid = std::to_string(ai) + "_" + std::to_string(rand() % 10000);
                            ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                            ir::BasicBlock* b_pr_nil = builder_->createBasicBlock("pr_nil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_nonnil = builder_->createBasicBlock("pr_nonnil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_str = builder_->createBasicBlock("pr_str_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_int = builder_->createBasicBlock("pr_int_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_next = builder_->createBasicBlock("pr_next_" + prid, cur_fn);

                            ir::Value* is_nil = builder_->createCeq(args[ai], context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                            builder_->createBr(is_nil, b_pr_nil, b_pr_nonnil);

                            builder_->setInsertPoint(b_pr_nil);
                            FyraBuiltinFunctions::emit_print_nil_inline(current_module_.get(), builder_.get());
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_nonnil);
                            ir::Value* is_str_ptr = builder_->createCuge(args[ai], context_->getConstantInt(context_->getIntegerType(64), 65536));
                            builder_->createBr(is_str_ptr, b_pr_str, b_pr_int);

                            builder_->setInsertPoint(b_pr_str);
                            FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), args[ai]);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_int);
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_next);
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            uint32_t arg_reg = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                            if (reg_float_values.count(arg_reg)) {
                                std::string fname = "float_const_" + std::to_string(label_counter_++);
                                ir::GlobalVariable* gv_float = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), fname, format_float_literal(reg_float_values[arg_reg]));
                                FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), gv_float);
                            } else {
                                FyraBuiltinFunctions::emit_print_float_inline(current_module_.get(), builder_.get(), args[ai]);
                            }
                        } else if (ai < inst.call_args.size() && reg_decimal_scales.count(inst.call_args[ai]) && reg_decimal_scales[inst.call_args[ai]] > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], reg_decimal_scales[inst.call_args[ai]]);
                        } else {
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                        }
                    }
                    ir::GlobalVariable* gv_nl = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "nl", "\n");
                    builder_->createExternCall("io.write", {
                        context_->getConstantInt(context_->getIntegerType(64), 1),
                        gv_nl,
                        context_->getConstantInt(context_->getIntegerType(64), 1)
                    }, context_->getIntegerType(64));

                    if (inst.dst != UINT32_MAX) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                } else if (name == "assert" && !args.empty()) {
                    std::string aid = std::to_string(label_counter_++);
                    ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                    ir::BasicBlock* b_pass = builder_->createBasicBlock("assert_pass_" + aid, cur_fn);
                    ir::BasicBlock* b_fail = builder_->createBasicBlock("assert_fail_" + aid, cur_fn);

                    builder_->createBr(args[0], b_pass, b_fail);

                    builder_->setInsertPoint(b_fail);
                    if (args.size() > 1) {
                        FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), args[1]);
                    } else {
                        ir::GlobalVariable* gv_fail = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "assert_msg", "Assertion failed\n");
                        builder_->createExternCall("io.write", {
                            context_->getConstantInt(context_->getIntegerType(64), 1),
                            gv_fail,
                            context_->getConstantInt(context_->getIntegerType(64), 17)
                        }, context_->getIntegerType(64));
                    }
                    builder_->createExternCall("process.exit", {
                        context_->getConstantInt(context_->getIntegerType(64), 1)
                    }, context_->getIntegerType(64));
                    builder_->createJmp(b_pass);

                    builder_->setInsertPoint(b_pass);
                    if (inst.dst != UINT32_MAX) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
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
                store_reg(inst.dst, builder_->createCast(load_reg(inst.a, inst.type_a), lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            case LIR::LIR_Op::DecRescale: {
                int src_scale = decimal_scale_for_reg(inst.a);
                int dst_scale = decimal_scale_for_reg(inst.dst);
                if (dst_scale > 0 && src_scale < 0) src_scale = (dst_scale == 6) ? 4 : 2;
                if (src_scale > 0 && dst_scale < 0) dst_scale = (src_scale == 2) ? 4 : 6;

                ir::Value* value = load_reg(inst.a, inst.type_a);
                if (src_scale > 0 && dst_scale > 0 && src_scale != dst_scale) {
                    int delta = dst_scale - src_scale;
                    int64_t factor = pow10_i64(std::abs(delta));
                    if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = (delta > 0) ? (reg_int_values[inst.a] * factor) : (reg_int_values[inst.a] / factor);
                    if (delta > 0) value = builder_->createMul(value, context_->getConstantInt(context_->getIntegerType(64), factor));
                    else value = builder_->createDiv(value, context_->getConstantInt(context_->getIntegerType(64), factor));
                }
                if (src_scale == dst_scale && reg_int_values.count(inst.a)) reg_int_values[inst.dst] = reg_int_values[inst.a];
                if (dst_scale > 0) reg_decimal_scales[inst.dst] = dst_scale;
                store_reg(inst.dst, value, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ToString: {
                used_builtins_.insert("lm_to_string");
                ir::Function* fn = current_module_->getFunction("lm_to_string");
                if (!fn) fn = builder_->createFunction("lm_to_string", context_->getPointerType(context_->getIntegerType(8)), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::STR_CONCAT: {
                FyraBuiltinFunctions::emit_str_concat_ir(current_module_.get(), builder_.get());
                ir::Function* fn = current_module_->getFunction("lm_str_concat");
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::STR_FORMAT: {
                used_builtins_.insert("lm_rt_str_format");
                ir::Function* fn = current_module_->getFunction("lm_rt_str_format");
                if (!fn) fn = builder_->createFunction("lm_rt_str_format", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* fmt_arg = load_reg(inst.a, inst.type_a);
                ir::Value* value_arg = load_reg(inst.b, inst.type_b);
                std::string formatted_value;
                bool has_formatted_value = false;
                if (reg_decimal_scales.count(inst.b) && reg_decimal_scales[inst.b] > 0 && reg_int_values.count(inst.b)) {
                    int scale = reg_decimal_scales[inst.b];
                    int64_t raw = reg_int_values[inst.b];
                    bool neg = raw < 0;
                    if (neg) raw = -raw;
                    int64_t divisor = pow10_i64(scale);
                    std::ostringstream oss;
                    if (neg) oss << '-';
                    oss << (raw / divisor) << '.' << std::setw(scale) << std::setfill('0') << (raw % divisor);
                    formatted_value = oss.str();
                    has_formatted_value = true;
                } else if (reg_float_values.count(inst.b)) {
                    formatted_value = format_float_literal(reg_float_values[inst.b]);
                    has_formatted_value = true;
                }
                if (has_formatted_value) {
                    std::string fmt = reg_string_literals.count(inst.a) ? reg_string_literals[inst.a] : "%s";
                    size_t pos = fmt.find("%s");
                    if (pos != std::string::npos) fmt.replace(pos, 2, formatted_value);
                    std::string fname = "str_format_const_" + std::to_string(label_counter_++);
                    ir::GlobalVariable* gv_formatted = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), fname, fmt);
                    store_reg(inst.dst, gv_formatted, LIR::Type::Ptr);
                } else {
                    if (reg_decimal_scales.count(inst.b) && reg_decimal_scales[inst.b] > 0) {
                        value_arg = FyraBuiltinFunctions::emit_decimal_to_str_inline(current_module_.get(), builder_.get(), value_arg, reg_decimal_scales[inst.b]);
                    }
                    store_reg(inst.dst, builder_->createCall(fn, {fmt_arg, value_arg}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                }
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
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleCreate: {
                used_builtins_.insert("lm_tuple_new");
                ir::Function* fn = current_module_->getFunction("lm_tuple_new");
                if (!fn) fn = builder_->createFunction("lm_tuple_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleSet: {
                used_builtins_.insert("lm_tuple_set");
                ir::Function* fn = current_module_->getFunction("lm_tuple_set");
                if (!fn) fn = builder_->createFunction("lm_tuple_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                builder_->createCall(fn, {load_reg(inst.dst, inst.result_type), load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)});
                break;
            }
            case LIR::LIR_Op::TupleGet: {
                used_builtins_.insert("lm_tuple_get");
                ir::Function* fn = current_module_->getFunction("lm_tuple_get");
                if (!fn) fn = builder_->createFunction("lm_tuple_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleLen: {
                // tuple length is stored at offset 0
                ir::Value* len = builder_->createLoad(load_reg(inst.a, inst.type_a));
                store_reg(inst.dst, len, inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictCreate: {
                used_builtins_.insert("lm_dict_new");
                ir::Function* fn = current_module_->getFunction("lm_dict_new");
                if (!fn) fn = builder_->createFunction("lm_dict_new", context_->getIntegerType(64), {});
                store_reg(inst.dst, builder_->createCall(fn, {}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictSet: {
                used_builtins_.insert("lm_dict_set");
                ir::Function* fn = current_module_->getFunction("lm_dict_set");
                if (!fn) fn = builder_->createFunction("lm_dict_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                builder_->createCall(fn, {load_reg(inst.dst, inst.result_type), load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)});
                break;
            }
            case LIR::LIR_Op::DictGet: {
                used_builtins_.insert("lm_dict_get");
                ir::Function* fn = current_module_->getFunction("lm_dict_get");
                if (!fn) fn = builder_->createFunction("lm_dict_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictLen: {
                ir::Value* count = builder_->createLoad(load_reg(inst.a, inst.type_a));
                store_reg(inst.dst, count, inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictHas: {
                used_builtins_.insert("lm_dict_has");
                ir::Function* fn = current_module_->getFunction("lm_dict_has");
                if (!fn) fn = builder_->createFunction("lm_dict_has", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictItems: {
                used_builtins_.insert("lm_dict_items");
                uint32_t dict_reg = (inst.a != UINT32_MAX && inst.a != 0) ? inst.a : (!inst.call_args.empty() ? inst.call_args[0] : UINT32_MAX);
                ir::Function* fn = current_module_->getFunction("lm_dict_items");
                if (!fn) fn = builder_->createFunction("lm_dict_items", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(dict_reg, LIR::Type::Ptr)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::NewFrame: {
                std::string name = inst.func_name; if (name.empty()) name = "Frame";
                uint32_t fields = static_cast<uint32_t>(inst.imm);
                uint32_t bytes = (fields > 0 ? fields : 2) * 8;
                ir::Type* type = current_module_->getType(name);
                if (!type) { ir::StructType* st = context_->createStructType(name); st->setBody({context_->getIntegerType(64), context_->getIntegerType(64)}); current_module_->addType(name, st); type = st; }
                store_reg(inst.dst, builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), bytes), type), inst.result_type);
                break;
            }
            case LIR::LIR_Op::FrameGetField:
            case LIR::LIR_Op::FrameGetFieldAtomic: {
                uint32_t field_idx = (inst.b != UINT32_MAX) ? inst.b : static_cast<uint32_t>(inst.imm);
                ir::Value* addr = builder_->createAdd(load_reg(inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                store_reg(inst.dst, builder_->createLoad(addr), inst.result_type);
                break;
            }
            case LIR::LIR_Op::FrameSetField:
            case LIR::LIR_Op::FrameSetFieldAtomic: {
                uint32_t field_idx = inst.a;
                ir::Value* val = load_reg(inst.b, inst.type_b);
                ir::Value* addr = builder_->createAdd(load_reg(inst.dst, inst.result_type), context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                builder_->createStore(val, addr);
                break;
            }
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
                if (inst.type_a != LIR::Type::Void) {
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
