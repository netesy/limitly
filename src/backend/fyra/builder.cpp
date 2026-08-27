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
#include "backend/vm/vm_value.hh"
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
        case LIR::Type::Void: return context_->getIntegerType(64);
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

    auto& registry = LIR::FunctionRegistry::getInstance();

    // Perform reachability analysis starting from the entry function
    std::unordered_set<std::string> reachable_funcs;
    std::vector<std::string> worklist;

    reachable_funcs.insert(lir_func.name);
    worklist.push_back(lir_func.name);

    if (lir_func.name == "__top_level_wrapper__" && registry.getFunction("main")) {
        reachable_funcs.insert("main");
        worklist.push_back("main");
    }

    auto inspect_instructions = [&](const LIR::LIR_Function& f) {
        for (const auto& inst : f.instructions) {
            std::string callee = inst.func_name;
            if (callee.empty() && inst.const_val && IS_PTR(inst.const_val)) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                if (h->type_id == TYPE_STRING) callee = ((LmStringHeader*)h)->data;
            }
            if (!callee.empty() && registry.getFunction(callee)) {
                if (reachable_funcs.find(callee) == reachable_funcs.end()) {
                    reachable_funcs.insert(callee);
                    worklist.push_back(callee);
                }
            }
        }
    };

    size_t work_idx = 0;
    while (work_idx < worklist.size()) {
        std::string fname = worklist[work_idx++];
        if (fname == lir_func.name) {
            inspect_instructions(lir_func);
        } else {
            auto* f = registry.getFunction(fname);
            if (f) inspect_instructions(*f);
        }
    }

    std::string main_name = lir_func.name;
    if (main_name == "__top_level_wrapper__") main_name = "main";
    ir::Function* main_fn = builder_->createFunction(main_name, context_->getIntegerType(64));

    // 1. Declare only reachable registered functions
    for (const auto& func_name : registry.getFunctionNames()) {
        if (func_name == lir_func.name) continue;
        if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) continue;
        if (reachable_funcs.find(func_name) == reachable_funcs.end()) continue;
        auto* f = registry.getFunction(func_name);
        if (!f) continue;

        std::string ir_name = func_name;
        if (func_name == "main" && lir_func.name == "__top_level_wrapper__") {
            ir_name = "__user_main";
        }

        std::vector<ir::Type*> param_types;
        for (size_t i = 0; i < f->param_count; ++i) {
            param_types.push_back(context_->getIntegerType(64));
        }

        ir::Type* ret_type = context_->getIntegerType(64);
        builder_->createFunction(ir_name, ret_type, param_types);
    }

    // 2. Build the bodies of reachable registered functions
    for (const auto& func_name : registry.getFunctionNames()) {
        if (func_name == lir_func.name) continue;
        if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) continue;
        if (reachable_funcs.find(func_name) == reachable_funcs.end() && !func_name.ends_with(".__init__")) continue;
        auto* f = registry.getFunction(func_name);
        if (!f) continue;

        std::string ir_name = func_name;
        if (func_name == "main" && lir_func.name == "__top_level_wrapper__") {
            ir_name = "__user_main";
        }

        ir::Function* fn = current_module_->getFunction(ir_name);
        if (fn) {
            build_function_body(fn, *f);
        }
    }

    // 3. Build the top-level main function body
    build_function_body(main_fn, lir_func);

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


    auto is_float_op = [&](const LIR::LIR_Inst& inst) -> bool {
        auto is_dec = [&](uint32_t r) {
            return r != UINT32_MAX && reg_decimal_scales.count(r) && reg_decimal_scales[r] > 0;
        };
        if (is_dec(inst.a) || is_dec(inst.b) || is_dec(inst.dst)) return false;

        if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) return true;
        if (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32) return true;
        if (inst.type_b == LIR::Type::F64 || inst.type_b == LIR::Type::F32) return true;
        if (inst.a != UINT32_MAX && reg_types.count(inst.a) && (reg_types[inst.a] == LIR::Type::F64 || reg_types[inst.a] == LIR::Type::F32)) return true;
        if (inst.b != UINT32_MAX && reg_types.count(inst.b) && (reg_types[inst.b] == LIR::Type::F64 || reg_types[inst.b] == LIR::Type::F32)) return true;

        auto is_reg_float = [&](uint32_t r) {
            if (r == UINT32_MAX) return false;
            auto it = lir_func.register_language_types.find(r);
            if (it != lir_func.register_language_types.end() && it->second) {
                return it->second->tag == ::TypeTag::Float64 || it->second->tag == ::TypeTag::Float32;
            }
            auto it2 = lir_func.register_types.find(r);
            if (it2 != lir_func.register_types.end()) {
                return it2->second == LIR::Type::F64 || it2->second == LIR::Type::F32;
            }
            return false;
        };

        if (is_reg_float(inst.a) || is_reg_float(inst.b) || is_reg_float(inst.dst)) return true;
        return false;
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
        auto it = lir_func.register_types.find(param_idx);
        if (it != lir_func.register_types.end()) {
            reg_types[param_idx] = it->second;
        }
        param_idx++;
    }

    if (main_fn->getName() == "main") {
        auto& registry = LIR::FunctionRegistry::getInstance();
        for (const auto& func_name : registry.getFunctionNames()) {
            if (func_name.ends_with(".__init__")) {
                ir::Function* init_fn = current_module_->getFunction(func_name);
                if (!init_fn) {
                    init_fn = builder_->createFunction(func_name, context_->getVoidType(), {});
                }
                builder_->createCall(init_fn, {});
            }
        }
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

    auto load_float_reg = [&](uint32_t r, LIR::Type t) -> ir::Value* {
        ir::Value* v = load_reg(r, t);
        LIR::Type actual_t = (reg_types.count(r) ? reg_types[r] : t);
        if (actual_t == LIR::Type::I64 || actual_t == LIR::Type::Bool) {
            return builder_->createSltof(v, context_->getDoubleType());
        }
        return v;
    };

    auto store_float_reg = [&](uint32_t r, ir::Value* fval) {
        store_reg(r, fval, LIR::Type::F64);
    };

    bool terminated = false;
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        const auto& inst = lir_func.instructions[i];

        if (block_map.count(i)) {
            if (!terminated && builder_->getInsertPoint() && i > 0 && builder_->getInsertPoint() != block_map[i]) {
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
                else if (inst.type_a != LIR::Type::Void) reg_types[inst.dst] = inst.type_a;
                store_reg(inst.dst, load_reg(inst.a, inst.type_a), (reg_types.count(inst.dst) ? reg_types[inst.dst] : inst.result_type));
                break;
            case LIR::LIR_Op::LoadConst: {
                if (inst.type_name == "d2" || inst.type_name == "decimal") reg_decimal_scales[inst.dst] = 2;
                else if (inst.type_name == "d4") reg_decimal_scales[inst.dst] = 4;
                else if (inst.type_name == "d6") reg_decimal_scales[inst.dst] = 6;

                LmValue val = inst.const_val;
                bool is_float_const = (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32 || is_float_op(inst));
                if (!is_float_const && IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h && h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_FLOAT) {
                        is_float_const = true;
                    }
                }
                if (is_float_const) {
                    double fval = 0.0;
                    if (IS_PTR(val)) {
                        fval = as_float(val);
                    } else {
                        memcpy(&fval, &val, sizeof(double));
                    }
                    ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                    reg_types[inst.dst] = LIR::Type::F64;
                    reg_float_values[inst.dst] = fval;
                    store_reg(inst.dst, c, LIR::Type::F64);
                } else if (IS_NIL(val) || val == 0) {
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                    reg_types[inst.dst] = LIR::Type::Ptr;
                    store_reg(inst.dst, c, LIR::Type::Ptr);
                } else if (IS_INT(val) && (((val >> 3) << 3) | TAG_INT) == val) {
                    int64_t actual_val = UNBOX_INT(val);
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                    reg_int_values[inst.dst] = actual_val;
                    reg_types[inst.dst] = LIR::Type::I64;
                    store_reg(inst.dst, c, LIR::Type::I64);
                } else if (IS_BOOL(val)) {
                    uint64_t actual_val = UNBOX_BOOL(val) ? 1 : 0;
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                    store_reg(inst.dst, c, LIR::Type::Bool);
                } else if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h->type_id == TYPE_STRING) {
                        const char* s = ((LmStringHeader*)h)->data;
                        uint64_t s_len = ((LmStringHeader*)h)->len;
                        reg_string_literals[inst.dst] = s;
                        reg_types[inst.dst] = LIR::Type::Ptr;

                        auto i8_ty  = context_->getIntegerType(8);

                        std::vector<ir::Constant*> elems;
                        auto add_u32 = [&](uint32_t val) {
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)(val & 0xFF)));
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> 8) & 0xFF)));
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> 16) & 0xFF)));
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> 24) & 0xFF)));
                        };
                        auto add_u64 = [&](uint64_t val) {
                            for (int b = 0; b < 8; ++b) {
                                elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> (b * 8)) & 0xFF)));
                            }
                        };

                        add_u32(11); // TYPE_STRING
                        add_u32(0);  // metadata
                        add_u64(s_len);
                        add_u64(s_len);

                        for (size_t i = 0; i <= s_len; ++i) {
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)s[i]));
                        }

                        auto arr_ty = context_->getArrayType(i8_ty, elems.size());
                        ir::Value* arr_const = context_->getConstantArray(arr_ty, elems);
                        std::string name = "str_hdr_" + std::to_string(label_counter_++);
                        auto gv = std::make_unique<ir::GlobalVariable>(
                            context_->getPointerType(i8_ty),
                            name, static_cast<ir::Constant*>(arr_const), false, ".data"
                        );
                        ir::Value* raw_str_ptr = gv.get();
                        current_module_->addGlobalVariable(std::move(gv));
                        store_reg(inst.dst, raw_str_ptr, LIR::Type::Ptr);
                    } else if (h->type_id == TYPE_BOX) {
                        LmBox* box = (LmBox*)h;
                        if (box->type == LM_BOX_STRING) {
                            const char* s = (char*)box->value.as_ptr;
                            uint64_t s_len = strlen(s);
                            reg_string_literals[inst.dst] = s;
                            reg_types[inst.dst] = LIR::Type::Ptr;

                            std::string gv_name = "str_data_" + std::to_string(label_counter_++);
                            ir::GlobalVariable* gv_bytes = FyraBuiltinFunctions::get_or_create_global_str(
                                current_module_.get(), builder_.get(), gv_name, s
                            );
                            store_reg(inst.dst, gv_bytes, LIR::Type::Ptr);
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
                        double fval;
                        memcpy(&fval, &val, sizeof(double));
                        ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                        reg_types[inst.dst] = inst.result_type;
                        reg_float_values[inst.dst] = fval;
                        store_reg(inst.dst, c, inst.result_type);
                    } else {
                        ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), val);
                        store_reg(inst.dst, c, inst.result_type);
                    }
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
                    ir::GlobalVariable* raw_gv = new_gv.get();
                    current_module_->addGlobalVariable(std::move(new_gv));
                    gv = raw_gv;
                }
                builder_->createStore(load_reg(inst.a, inst.type_a), gv);
                if (reg_decimal_scales.count(inst.a)) {
                    global_decimal_scales_[gname] = reg_decimal_scales[inst.a];
                }
                if (reg_types.count(inst.a)) {
                    global_types_[gname] = reg_types[inst.a];
                } else if (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32) {
                    global_types_[gname] = inst.type_a;
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
                    ir::GlobalVariable* raw_gv = new_gv.get();
                    current_module_->addGlobalVariable(std::move(new_gv));
                    gv = raw_gv;
                }
                ir::Value* loaded = builder_->createLoad(gv);
                LIR::Type loaded_type = inst.result_type;
                if (global_types_.count(gname)) {
                    loaded_type = global_types_[gname];
                }
                store_reg(inst.dst, loaded, loaded_type);
                if (global_decimal_scales_.count(gname)) {
                    reg_decimal_scales[inst.dst] = global_decimal_scales_[gname];
                }
                break;
            }
            case LIR::LIR_Op::Add:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFAdd(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else {
                    store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Sub:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFSub(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else {
                    store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Mul:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFMul(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else {
                    store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Div:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFDiv(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else {
                    ir::Value* num = load_reg(inst.a, inst.type_a);
                    ir::Value* den = load_reg(inst.b, inst.type_b);
                    ir::Value* is_zero = builder_->createCeq(den, context_->getConstantInt(context_->getIntegerType(64), 0));

                    std::string div_id = std::to_string(label_counter_++);
                    ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                    ir::BasicBlock* b_safe = builder_->createBasicBlock("div_safe_" + div_id, cur_fn);
                    ir::BasicBlock* b_zero = builder_->createBasicBlock("div_zero_" + div_id, cur_fn);
                    ir::BasicBlock* b_done = builder_->createBasicBlock("div_done_" + div_id, cur_fn);
                    ir::Instruction* res_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));

                    builder_->createBr(is_zero, b_zero, b_safe);

                    builder_->setInsertPoint(b_zero);
                    builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), res_slot);
                    builder_->createJmp(b_done);

                    builder_->setInsertPoint(b_safe);
                    builder_->createStore(builder_->createDiv(num, den), res_slot);
                    builder_->createJmp(b_done);

                    builder_->setInsertPoint(b_done);
                    store_reg(inst.dst, builder_->createLoad(res_slot), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Mod: {
                ir::Value* num = load_reg(inst.a, inst.type_a);
                ir::Value* den = load_reg(inst.b, inst.type_b);
                ir::Value* is_zero = builder_->createCeq(den, context_->getConstantInt(context_->getIntegerType(64), 0));

                std::string mod_id = std::to_string(label_counter_++);
                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                ir::BasicBlock* b_safe = builder_->createBasicBlock("mod_safe_" + mod_id, cur_fn);
                ir::BasicBlock* b_zero = builder_->createBasicBlock("mod_zero_" + mod_id, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("mod_done_" + mod_id, cur_fn);
                ir::Instruction* res_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));

                builder_->createBr(is_zero, b_zero, b_safe);

                builder_->setInsertPoint(b_zero);
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_safe);
                builder_->createStore(builder_->createRem(num, den), res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                store_reg(inst.dst, builder_->createLoad(res_slot), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Neg:
                if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = -reg_int_values[inst.a];
                if (reg_float_values.count(inst.a)) reg_float_values[inst.dst] = -reg_float_values[inst.a];
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFSub(context_->getConstantFP(context_->getDoubleType(), 0.0), load_float_reg(inst.a, inst.type_a)));
                } else {
                    store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type);
                }
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
                reg_types[inst.dst] = LIR::Type::Bool;
                bool is_ptr = (inst.type_a == LIR::Type::Ptr || inst.type_b == LIR::Type::Ptr ||
                               (reg_types.count(inst.a) && reg_types[inst.a] == LIR::Type::Ptr) ||
                               (reg_types.count(inst.b) && reg_types[inst.b] == LIR::Type::Ptr) ||
                               reg_string_literals.count(inst.a) || reg_string_literals.count(inst.b));
                if (is_ptr) {
                    used_builtins_.insert("lm_key_eq");
                    ir::Function* fn = current_module_->getFunction("lm_key_eq");
                    if (!fn) fn = builder_->createFunction("lm_key_eq", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                    store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}), LIR::Type::Bool);
                } else if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCeqf(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    ir::Value* c = builder_->createCeq(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                }
                break;
            }
            case LIR::LIR_Op::CmpNEQ: {
                reg_types[inst.dst] = LIR::Type::Bool;
                bool is_ptr = (inst.type_a == LIR::Type::Ptr || inst.type_b == LIR::Type::Ptr ||
                               (reg_types.count(inst.a) && reg_types[inst.a] == LIR::Type::Ptr) ||
                               (reg_types.count(inst.b) && reg_types[inst.b] == LIR::Type::Ptr) ||
                               reg_string_literals.count(inst.a) || reg_string_literals.count(inst.b));
                if (is_ptr) {
                    used_builtins_.insert("lm_key_eq");
                    ir::Function* fn = current_module_->getFunction("lm_key_eq");
                    if (!fn) fn = builder_->createFunction("lm_key_eq", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                    ir::Value* eq_res = builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)});
                    store_reg(inst.dst, builder_->createCeq(eq_res, context_->getConstantInt(context_->getIntegerType(64), 0)), LIR::Type::Bool);
                } else if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCnef(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    ir::Value* c = builder_->createCne(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                }
                break;
            }
            case LIR::LIR_Op::CmpLT:
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createClt(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    ir::Value* c = builder_->createCslt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                }
                break;
            case LIR::LIR_Op::CmpLE:
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCle(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    ir::Value* c = builder_->createCsle(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                }
                break;
            case LIR::LIR_Op::CmpGT:
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCgt(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    ir::Value* c = builder_->createCsgt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                }
                break;
            case LIR::LIR_Op::CmpGE:
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCge(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    ir::Value* c = builder_->createCsge(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                }
                break;
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
                    terminated = false;
                } else errors_.push_back("Cond jump to unknown target: " + std::to_string(inst.imm));
                break;
            }
            case LIR::LIR_Op::Call:
            case LIR::LIR_Op::CallVoid: {
                std::string name = inst.func_name; 
                if (name.empty() && inst.const_val) {
                    if (IS_PTR(inst.const_val)) {
                        ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                        if (h->type_id == TYPE_STRING) {
                            name = ((LmStringHeader*)h)->data;
                        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
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
                                builder_->createAdd(gv_sp, context_->getConstantInt(context_->getIntegerType(64), 24)),
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
                        if (ai < inst.call_args.size() && reg_string_literals.count(inst.call_args[ai])) {
                            arg_type = LIR::Type::Ptr;
                        }
                        if (ai < inst.call_args.size() && reg_int_values.count(inst.call_args[ai])) {
                            arg_type = LIR::Type::I64;
                        }
                        if (arg_type == LIR::Type::I64 && (inst.call_arg_types.size() > ai && inst.call_arg_types[ai] == LIR::Type::Bool)) {
                            arg_type = LIR::Type::Bool;
                        }
                        std::string prid = std::to_string(ai) + "_" + std::to_string(label_counter_++);
                        ir::Function* cur_fn = builder_->getInsertPoint()->getParent();

                        uint32_t arg_r = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                        bool is_known_i64 = (arg_r != UINT32_MAX && (reg_int_values.count(arg_r) || (reg_types.count(arg_r) && reg_types[arg_r] == LIR::Type::I64)));

                        if (arg_type == LIR::Type::I64 || is_known_i64) {
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::Ptr) {
                            ir::BasicBlock* b_pr_ptr = builder_->createBasicBlock("pr_ptr_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_int = builder_->createBasicBlock("pr_int_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_nil = builder_->createBasicBlock("pr_nil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_obj = builder_->createBasicBlock("pr_obj_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_next = builder_->createBasicBlock("pr_next_" + prid, cur_fn);

                            ir::Value* arg_val = args[ai];
                            ir::Value* is_ge_ptr = builder_->createCuge(arg_val, context_->getConstantInt(context_->getIntegerType(64), 65536));
                            ir::Value* high_bits = builder_->createShr(arg_val, context_->getConstantInt(context_->getIntegerType(64), 48));
                            ir::Value* high_zero = builder_->createCeq(high_bits, context_->getConstantInt(context_->getIntegerType(64), 0));
                            ir::Value* is_valid_ptr = builder_->createAnd(is_ge_ptr, high_zero);

                            builder_->createBr(is_valid_ptr, b_pr_ptr, b_pr_int);

                            // Branch: scalar int
                            builder_->setInsertPoint(b_pr_int);
                            ir::BasicBlock* b_pr_int_nil = builder_->createBasicBlock("pr_int_nil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_int_real = builder_->createBasicBlock("pr_int_real_" + prid, cur_fn);
                            ir::Value* is_vnil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                            ir::Value* is_znil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                            ir::Value* is_nil_scalar = builder_->createOr(is_vnil, is_znil);

                            builder_->createBr(is_nil_scalar, b_pr_int_nil, b_pr_int_real);

                            builder_->setInsertPoint(b_pr_int_nil);
                            FyraBuiltinFunctions::emit_print_nil_inline(current_module_.get(), builder_.get());
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_int_real);
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), arg_val);
                            builder_->createJmp(b_pr_next);

                            // Branch: pointer candidate
                            builder_->setInsertPoint(b_pr_ptr);
                            ir::Value* is_zero_nil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                            ir::Value* is_val_nil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                            ir::Value* is_nil = builder_->createOr(is_zero_nil, is_val_nil);
                            builder_->createBr(is_nil, b_pr_nil, b_pr_obj);

                            builder_->setInsertPoint(b_pr_nil);
                            FyraBuiltinFunctions::emit_print_nil_inline(current_module_.get(), builder_.get());
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_obj);
                            ir::Value* magic = builder_->createLoad(arg_val);
                            ir::Value* type_id = builder_->createAnd(magic, context_->getConstantInt(context_->getIntegerType(64), 0xFFFFFFFF));

                            ir::BasicBlock* b_pr_str = builder_->createBasicBlock("pr_str_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_enum = builder_->createBasicBlock("pr_enum_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_list = builder_->createBasicBlock("pr_list_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_non_str = builder_->createBasicBlock("pr_nonstr_" + prid, cur_fn);

                            ir::Value* is_str = builder_->createCeq(type_id, context_->getConstantInt(context_->getIntegerType(64), 11));
                            builder_->createBr(is_str, b_pr_str, b_pr_non_str);

                            builder_->setInsertPoint(b_pr_str);
                            FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), arg_val);
                            builder_->createJmp(b_pr_next);

                            ir::BasicBlock* b_pr_dict = builder_->createBasicBlock("pr_dict_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_fallback = builder_->createBasicBlock("pr_fb_" + prid, cur_fn);

                            builder_->setInsertPoint(b_pr_non_str);
                            ir::Value* is_enum = builder_->createCeq(magic, context_->getConstantInt(context_->getIntegerType(64), 0x454E554D));
                            builder_->createBr(is_enum, b_pr_enum, b_pr_list);

                            builder_->setInsertPoint(b_pr_enum);
                            ir::Function* fn_enum_str = current_module_->getFunction("lm_enum_to_str");
                            if (fn_enum_str) {
                                ir::Value* enum_s = builder_->createCall(fn_enum_str, {arg_val});
                                FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), enum_s);
                            } else {
                                FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), arg_val);
                            }
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_list);
                            ir::Value* is_list = builder_->createCeq(type_id, context_->getConstantInt(context_->getIntegerType(64), 12));
                            builder_->createBr(is_list, b_pr_dict, b_pr_fallback);

                            builder_->setInsertPoint(b_pr_dict);
                            ir::Function* fn_list_str = current_module_->getFunction("lm_list_to_str");
                            if (fn_list_str) {
                                ir::Value* list_s = builder_->createCall(fn_list_str, {arg_val});
                                FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), list_s);
                            } else {
                                FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), arg_val);
                            }
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_fallback);
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), arg_val);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_next);
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            FyraBuiltinFunctions::emit_print_float_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (ai < inst.call_args.size() && reg_decimal_scales.count(inst.call_args[ai]) && reg_decimal_scales[inst.call_args[ai]] > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], reg_decimal_scales[inst.call_args[ai]]);
                        } else {
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                        }
                    }
                    ir::GlobalVariable* gv_nl = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "nl", "\n");
                    builder_->createExternCall("io.write", {
                        context_->getConstantInt(context_->getIntegerType(64), 1),
                        builder_->createAdd(gv_nl, context_->getConstantInt(context_->getIntegerType(64), 24)),
                        context_->getConstantInt(context_->getIntegerType(64), 1)
                    }, context_->getIntegerType(64));

                    if (inst.op == LIR::LIR_Op::Call) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                } else if (name == "sleep" || name == "time.sleep" || name == "sleep_ms" || name == "time_sleep") {
                    ir::Value* res = builder_->createExternCall("process.sleep", args, lir_type_to_fyra_type(inst.result_type));
                    if (inst.op == LIR::LIR_Op::Call && inst.dst != UINT32_MAX) store_reg(inst.dst, res, inst.result_type);
                    break;
                } else if (FyraBuiltinFunctions::is_builtin(name)) {
                    name = FyraBuiltinFunctions::get_internal_name(name);
                } else if (name == "main" && lir_func.name == "__top_level_wrapper__" && LIR::FunctionRegistry::getInstance().hasFunction("main")) {
                    name = "__user_main";
                }

                used_builtins_.insert(name);

                if (name.empty()) name = "dummy_fn";
                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < args.size(); ++k) pts.push_back(args[k]->getType());
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
                ir::Value* res = func ? static_cast<ir::Value*>(builder_->createCall(func, args)) : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0));
                if (inst.op == LIR::LIR_Op::Call) {
                    reg_types[inst.dst] = inst.result_type;
                    store_reg(inst.dst, res, inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::CallIndirect: {
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                ir::Value* callee = load_reg(inst.a, inst.type_a);

                std::string cid = std::to_string(label_counter_++);
                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                ir::BasicBlock* b_dispatch = builder_->createBasicBlock("ind_disp_" + cid, cur_fn);
                ir::BasicBlock* b_raw_call = builder_->createBasicBlock("ind_raw_" + cid, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("ind_done_" + cid, cur_fn);

                ir::Instruction* res_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), res_slot);

                ir::Value* is_ge_ptr = builder_->createCuge(callee, context_->getConstantInt(context_->getIntegerType(64), 65536));
                ir::Value* high_bits = builder_->createShr(callee, context_->getConstantInt(context_->getIntegerType(64), 48));
                ir::Value* high_zero = builder_->createCeq(high_bits, context_->getConstantInt(context_->getIntegerType(64), 0));
                ir::Value* is_valid_ptr = builder_->createAnd(is_ge_ptr, high_zero);

                builder_->createBr(is_valid_ptr, b_dispatch, b_raw_call);

                builder_->setInsertPoint(b_dispatch);
                ir::Value* magic = builder_->createLoad(callee);
                ir::Value* type_id = builder_->createAnd(magic, context_->getConstantInt(context_->getIntegerType(64), 0xFFFFFFFF));
                ir::Value* is_str = builder_->createCeq(type_id, context_->getConstantInt(context_->getIntegerType(64), 11));

                ir::BasicBlock* b_str_dispatch = builder_->createBasicBlock("ind_str_" + cid, cur_fn);
                ir::BasicBlock* b_closure_dispatch = builder_->createBasicBlock("ind_cls_" + cid, cur_fn);
                builder_->createBr(is_str, b_str_dispatch, b_closure_dispatch);

                // Closure Tuple Dispatch: callee is a tuple ptr (element 0 = fn name or string, extra elements = captures)
                builder_->setInsertPoint(b_closure_dispatch);
                used_builtins_.insert("lm_tuple_get");
                ir::Function* fn_tget = current_module_->getFunction("lm_tuple_get");
                if (!fn_tget) fn_tget = builder_->createFunction("lm_tuple_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* fn_obj = builder_->createCall(fn_tget, {callee, context_->getConstantInt(context_->getIntegerType(64), 0)});

                std::vector<ir::Value*> closure_args;
                closure_args.push_back(callee); // pass closure tuple as extra param
                for (auto& a : args) closure_args.push_back(a);

                used_builtins_.insert("lm_key_eq");
                ir::Function* fn_eq = current_module_->getFunction("lm_key_eq");
                if (!fn_eq) fn_eq = builder_->createFunction("lm_key_eq", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});

                std::vector<ir::Function*> cand_funcs;
                for (const auto& f : current_module_->getFunctions()) {
                    if (f->getName() != "main" && !f->getName().starts_with("lm_") && !f->getName().starts_with("_builtin_")) {
                        cand_funcs.push_back(f.get());
                    }
                }

                ir::BasicBlock* cur_cls_chk = b_closure_dispatch;
                for (size_t fi = 0; fi < cand_funcs.size(); ++fi) {
                    ir::Function* target_f = cand_funcs[fi];
                    std::string f_name = target_f->getName();

                    builder_->setInsertPoint(cur_cls_chk);
                    ir::GlobalVariable* gv_fname = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "cls_str_" + f_name + "_" + cid, f_name);
                    ir::Value* eq_res = builder_->createCall(fn_eq, {fn_obj, gv_fname});
                    ir::Value* is_match = builder_->createCne(eq_res, context_->getConstantInt(context_->getIntegerType(64), 0));

                    size_t dot_p = f_name.rfind('.');
                    if (dot_p != std::string::npos) {
                        std::string unq_name = f_name.substr(dot_p + 1);
                        ir::GlobalVariable* gv_unq = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "cls_unq_" + unq_name + "_" + cid + "_" + std::to_string(fi), unq_name);
                        ir::Value* unq_eq = builder_->createCall(fn_eq, {fn_obj, gv_unq});
                        ir::Value* unq_match = builder_->createCne(unq_eq, context_->getConstantInt(context_->getIntegerType(64), 0));
                        is_match = builder_->createOr(is_match, unq_match);
                    }

                    ir::BasicBlock* b_match = builder_->createBasicBlock("cls_m_" + std::to_string(fi) + "_" + cid, cur_fn);
                    ir::BasicBlock* b_next_check = builder_->createBasicBlock("cls_next_" + std::to_string(fi) + "_" + cid, cur_fn);

                    builder_->createBr(is_match, b_match, b_next_check);

                    builder_->setInsertPoint(b_match);
                    std::vector<ir::Value*> call_args_matching;
                    size_t target_param_cnt = target_f->getParameters().size();
                    if (target_param_cnt == args.size() + 1) {
                        for (size_t k = 0; k < args.size(); ++k) call_args_matching.push_back(args[k]);
                        call_args_matching.push_back(callee);
                    } else if (target_param_cnt == args.size()) {
                        for (size_t k = 0; k < args.size(); ++k) call_args_matching.push_back(args[k]);
                    } else {
                        for (size_t k = 0; k < target_param_cnt; ++k) {
                            if (k < args.size()) call_args_matching.push_back(args[k]);
                            else if (k == args.size()) call_args_matching.push_back(callee);
                            else call_args_matching.push_back(context_->getConstantInt(context_->getIntegerType(64), 0));
                        }
                    }
                    ir::Value* call_res = builder_->createCall(target_f, call_args_matching);
                    builder_->createStore(call_res, res_slot);
                    builder_->createJmp(b_done);

                    cur_cls_chk = b_next_check;
                }

                builder_->setInsertPoint(cur_cls_chk);
                builder_->createJmp(b_raw_call);

                // String Name Direct Dispatch
                builder_->setInsertPoint(b_str_dispatch);
                ir::BasicBlock* cur_check_bb = b_str_dispatch;
                for (size_t fi = 0; fi < cand_funcs.size(); ++fi) {
                    ir::Function* target_f = cand_funcs[fi];
                    std::string f_name = target_f->getName();

                    builder_->setInsertPoint(cur_check_bb);
                    ir::GlobalVariable* gv_fname = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "fn_str_" + f_name + "_" + cid, f_name);
                    ir::Value* eq_res = builder_->createCall(fn_eq, {callee, gv_fname});
                    ir::Value* is_match = builder_->createCne(eq_res, context_->getConstantInt(context_->getIntegerType(64), 0));

                    size_t dot_p = f_name.rfind('.');
                    if (dot_p != std::string::npos) {
                        std::string unq_name = f_name.substr(dot_p + 1);
                        ir::GlobalVariable* gv_unq = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "fn_unq_" + unq_name + "_" + cid + "_" + std::to_string(fi), unq_name);
                        ir::Value* unq_eq = builder_->createCall(fn_eq, {callee, gv_unq});
                        ir::Value* unq_match = builder_->createCne(unq_eq, context_->getConstantInt(context_->getIntegerType(64), 0));
                        is_match = builder_->createOr(is_match, unq_match);
                    }

                    ir::BasicBlock* b_match = builder_->createBasicBlock("ind_m_" + std::to_string(fi) + "_" + cid, cur_fn);
                    ir::BasicBlock* b_next_check = builder_->createBasicBlock("ind_next_" + std::to_string(fi) + "_" + cid, cur_fn);

                    builder_->createBr(is_match, b_match, b_next_check);

                    builder_->setInsertPoint(b_match);
                    std::vector<ir::Value*> call_args_matching;
                    for (size_t k = 0; k < target_f->getParameters().size(); ++k) {
                        if (k < args.size()) call_args_matching.push_back(args[k]);
                        else call_args_matching.push_back(context_->getConstantInt(context_->getIntegerType(64), 0));
                    }
                    ir::Value* call_res = builder_->createCall(target_f, call_args_matching);
                    builder_->createStore(call_res, res_slot);
                    builder_->createJmp(b_done);

                    cur_check_bb = b_next_check;
                }

                builder_->setInsertPoint(cur_check_bb);
                builder_->createJmp(b_raw_call);

                builder_->setInsertPoint(b_raw_call);
                ir::Value* raw_res = builder_->createCall(callee, args, lir_type_to_fyra_type(inst.result_type));
                builder_->createStore(raw_res, res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                ir::Value* final_res = builder_->createLoad(res_slot);
                if (inst.dst != UINT32_MAX) {
                    reg_types[inst.dst] = inst.result_type;
                    store_reg(inst.dst, final_res, inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::CallBuiltin: {
                std::string name = inst.func_name; 
                if (name.empty() && inst.const_val) {
                    if (IS_PTR(inst.const_val)) {
                        ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                        if (h->type_id == TYPE_STRING) {
                            name = ((LmStringHeader*)h)->data;
                        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
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
                                builder_->createAdd(gv_sp, context_->getConstantInt(context_->getIntegerType(64), 24)),
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
                        if (ai < inst.call_args.size() && reg_string_literals.count(inst.call_args[ai])) {
                            arg_type = LIR::Type::Ptr;
                        }
                        if (ai < inst.call_args.size() && (reg_int_values.count(inst.call_args[ai]) || (inst.call_arg_types.size() > ai && inst.call_arg_types[ai] == LIR::Type::I64 && !reg_types.count(inst.call_args[ai])))) {
                            arg_type = LIR::Type::I64;
                        }
                        if (arg_type == LIR::Type::I64 && (inst.call_arg_types.size() > ai && inst.call_arg_types[ai] == LIR::Type::Bool)) {
                            arg_type = LIR::Type::Bool;
                        }
                        std::string prid = std::to_string(ai) + "_" + std::to_string(label_counter_++);
                        ir::Function* cur_fn = builder_->getInsertPoint()->getParent();

                        uint32_t arg_r = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                        bool is_known_i64 = (arg_r != UINT32_MAX && (reg_int_values.count(arg_r) || (reg_types.count(arg_r) && reg_types[arg_r] == LIR::Type::I64)));

                        if (arg_type == LIR::Type::I64 || is_known_i64) {
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::Ptr) {
                            ir::BasicBlock* b_pr_ptr = builder_->createBasicBlock("pr_ptr_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_int = builder_->createBasicBlock("pr_int_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_nil = builder_->createBasicBlock("pr_nil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_obj = builder_->createBasicBlock("pr_obj_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_next = builder_->createBasicBlock("pr_next_" + prid, cur_fn);

                            ir::Value* arg_val = args[ai];
                            ir::Value* is_ge_ptr = builder_->createCuge(arg_val, context_->getConstantInt(context_->getIntegerType(64), 65536));
                            ir::Value* high_bits = builder_->createShr(arg_val, context_->getConstantInt(context_->getIntegerType(64), 48));
                            ir::Value* high_zero = builder_->createCeq(high_bits, context_->getConstantInt(context_->getIntegerType(64), 0));
                            ir::Value* is_valid_ptr = builder_->createAnd(is_ge_ptr, high_zero);

                            builder_->createBr(is_valid_ptr, b_pr_ptr, b_pr_int);

                            // Branch: scalar int
                            builder_->setInsertPoint(b_pr_int);
                            ir::BasicBlock* b_pr_int_nil = builder_->createBasicBlock("pr_int_nil_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_int_real = builder_->createBasicBlock("pr_int_real_" + prid, cur_fn);
                            ir::Value* is_vnil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                            ir::Value* is_znil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                            ir::Value* is_nil_scalar = builder_->createOr(is_vnil, is_znil);

                            builder_->createBr(is_nil_scalar, b_pr_int_nil, b_pr_int_real);

                            builder_->setInsertPoint(b_pr_int_nil);
                            FyraBuiltinFunctions::emit_print_nil_inline(current_module_.get(), builder_.get());
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_int_real);
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), arg_val);
                            builder_->createJmp(b_pr_next);

                            // Branch: pointer candidate
                            builder_->setInsertPoint(b_pr_ptr);
                            ir::Value* is_zero_nil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                            ir::Value* is_val_nil = builder_->createCeq(arg_val, context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                            ir::Value* is_nil = builder_->createOr(is_zero_nil, is_val_nil);
                            builder_->createBr(is_nil, b_pr_nil, b_pr_obj);

                            builder_->setInsertPoint(b_pr_nil);
                            FyraBuiltinFunctions::emit_print_nil_inline(current_module_.get(), builder_.get());
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_obj);
                            ir::Value* magic = builder_->createLoad(arg_val);
                            ir::Value* type_id = builder_->createAnd(magic, context_->getConstantInt(context_->getIntegerType(64), 0xFFFFFFFF));

                            ir::BasicBlock* b_pr_str = builder_->createBasicBlock("pr_str_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_enum = builder_->createBasicBlock("pr_enum_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_list = builder_->createBasicBlock("pr_list_" + prid, cur_fn);
                            ir::BasicBlock* b_pr_non_str = builder_->createBasicBlock("pr_nonstr_" + prid, cur_fn);

                            ir::Value* is_str = builder_->createCeq(type_id, context_->getConstantInt(context_->getIntegerType(64), 11));
                            builder_->createBr(is_str, b_pr_str, b_pr_non_str);

                            builder_->setInsertPoint(b_pr_str);
                            FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), arg_val);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_non_str);
                            ir::Value* is_enum = builder_->createCeq(magic, context_->getConstantInt(context_->getIntegerType(64), 0x454E554D));
                            builder_->createBr(is_enum, b_pr_enum, b_pr_list);

                            builder_->setInsertPoint(b_pr_enum);
                            used_builtins_.insert("lm_enum_to_str");
                            ir::Function* fn_enum_str = current_module_->getFunction("lm_enum_to_str");
                            if (!fn_enum_str) fn_enum_str = builder_->createFunction("lm_enum_to_str", context_->getIntegerType(64), {context_->getIntegerType(64)});
                            ir::Value* enum_s = builder_->createCall(fn_enum_str, {arg_val});
                            FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), enum_s);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_list);
                            used_builtins_.insert("lm_list_to_str");
                            ir::Function* fn_list_str = current_module_->getFunction("lm_list_to_str");
                            if (!fn_list_str) fn_list_str = builder_->createFunction("lm_list_to_str", context_->getIntegerType(64), {context_->getIntegerType(64)});
                            ir::Value* list_s = builder_->createCall(fn_list_str, {arg_val});
                            FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), list_s);
                            builder_->createJmp(b_pr_next);

                            builder_->setInsertPoint(b_pr_next);
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            FyraBuiltinFunctions::emit_print_float_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (ai < inst.call_args.size() && reg_decimal_scales.count(inst.call_args[ai]) && reg_decimal_scales[inst.call_args[ai]] > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], reg_decimal_scales[inst.call_args[ai]]);
                        } else {
                            FyraBuiltinFunctions::emit_print_int_inline(current_module_.get(), builder_.get(), args[ai]);
                        }
                    }
                    ir::GlobalVariable* gv_nl = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "nl", "\n");
                    builder_->createExternCall("io.write", {
                        context_->getConstantInt(context_->getIntegerType(64), 1),
                        builder_->createAdd(gv_nl, context_->getConstantInt(context_->getIntegerType(64), 24)),
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
                        ir::Value* msg_ptr = args[1];
                        ir::Value* is_valid_msg = builder_->createCuge(msg_ptr, context_->getConstantInt(context_->getIntegerType(64), 65536));
                        ir::BasicBlock* b_msg_v = builder_->createBasicBlock("assert_msg_v_" + aid, cur_fn);
                        ir::BasicBlock* b_msg_d = builder_->createBasicBlock("assert_msg_d_" + aid, cur_fn);
                        builder_->createBr(is_valid_msg, b_msg_v, b_msg_d);

                        builder_->setInsertPoint(b_msg_v);
                        FyraBuiltinFunctions::emit_print_str_inline(current_module_.get(), builder_.get(), msg_ptr);
                        ir::GlobalVariable* gv_nl = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "nl", "\n");
                        builder_->createExternCall("io.write", {
                            context_->getConstantInt(context_->getIntegerType(64), 1),
                            builder_->createAdd(gv_nl, context_->getConstantInt(context_->getIntegerType(64), 24)),
                            context_->getConstantInt(context_->getIntegerType(64), 1)
                        }, context_->getIntegerType(64));
                        builder_->createExternCall("process.exit", {
                            context_->getConstantInt(context_->getIntegerType(64), 1)
                        }, context_->getIntegerType(64));

                        builder_->setInsertPoint(b_msg_d);
                        ir::GlobalVariable* gv_fail = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "assert_msg", "Assertion failed\n");
                        builder_->createExternCall("io.write", {
                            context_->getConstantInt(context_->getIntegerType(64), 1),
                            builder_->createAdd(gv_fail, context_->getConstantInt(context_->getIntegerType(64), 24)),
                            context_->getConstantInt(context_->getIntegerType(64), 17)
                        }, context_->getIntegerType(64));
                    } else {
                        ir::GlobalVariable* gv_fail = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "assert_msg", "Assertion failed\n");
                        builder_->createExternCall("io.write", {
                            context_->getConstantInt(context_->getIntegerType(64), 1),
                            builder_->createAdd(gv_fail, context_->getConstantInt(context_->getIntegerType(64), 24)),
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
                } else if (name == "main" && lir_func.name == "__top_level_wrapper__" && LIR::FunctionRegistry::getInstance().hasFunction("main")) {
                    name = "__user_main";
                }

                used_builtins_.insert(name);

                if (name.empty()) name = "dummy_fn";
                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < args.size(); ++k) pts.push_back(args[k]->getType());
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
                if (func) store_reg(inst.dst, builder_->createCall(func, args), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Load: store_reg(inst.dst, builder_->createLoad(load_reg(inst.a, inst.type_a)), inst.result_type); break;
            case LIR::LIR_Op::Store: builder_->createStore(load_reg(inst.b, inst.type_b), load_reg(inst.a, inst.type_a)); break;
            case LIR::LIR_Op::Cast: {
                if (inst.result_type != LIR::Type::Ptr && (inst.type_a == LIR::Type::Ptr || (reg_types.count(inst.a) && reg_types[inst.a] == LIR::Type::Ptr))) {
                    ir::Value* str_val = load_reg(inst.a, LIR::Type::Ptr);
                    ir::Value* int_val = FyraBuiltinFunctions::emit_str_to_int_inline(current_module_.get(), builder_.get(), str_val);
                    store_reg(inst.dst, int_val, inst.result_type);
                } else {
                    store_reg(inst.dst, builder_->createCast(load_reg(inst.a, inst.type_a), lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                }
                break;
            }
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
                if (!fn) fn = builder_->createFunction("lm_to_string", context_->getIntegerType(64), {context_->getIntegerType(64)});
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
                if (inst.type_b == LIR::Type::Bool || (reg_types.count(inst.b) && reg_types[inst.b] == LIR::Type::Bool)) {
                    value_arg = FyraBuiltinFunctions::emit_bool_to_str_inline(current_module_.get(), builder_.get(), value_arg);
                } else if (reg_decimal_scales.count(inst.b) && reg_decimal_scales[inst.b] > 0) {
                    value_arg = FyraBuiltinFunctions::emit_decimal_to_str_inline(current_module_.get(), builder_.get(), value_arg, reg_decimal_scales[inst.b]);
                } else if (inst.type_b == LIR::Type::F64 || inst.type_b == LIR::Type::F32 || (reg_types.count(inst.b) && (reg_types[inst.b] == LIR::Type::F64 || reg_types[inst.b] == LIR::Type::F32))) {
                    value_arg = FyraBuiltinFunctions::emit_float_to_str_inline(current_module_.get(), builder_.get(), value_arg);
                } else if (inst.type_b != LIR::Type::Ptr && (!reg_types.count(inst.b) || reg_types[inst.b] != LIR::Type::Ptr)) {
                    used_builtins_.insert("lm_to_string");
                    ir::Function* fn_to_str = current_module_->getFunction("lm_to_string");
                    if (!fn_to_str) fn_to_str = builder_->createFunction("lm_to_string", context_->getPointerType(context_->getIntegerType(8)), {context_->getIntegerType(64)});
                    value_arg = builder_->createCall(fn_to_str, {value_arg});
                }
                LIR::Type res_t = (inst.result_type != LIR::Type::Void) ? inst.result_type : LIR::Type::Ptr;
                store_reg(inst.dst, builder_->createCall(fn, {fmt_arg, value_arg}, lir_type_to_fyra_type(res_t)), res_t);
                break;
            }
            case LIR::LIR_Op::ConstructError: {
                ir::Value* payload = (inst.a != UINT32_MAX) ? load_reg(inst.a, inst.type_a) : context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                ir::Value* err_box = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 16)}, context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 1), err_box);
                ir::Value* payload_addr = builder_->createAdd(err_box, context_->getConstantInt(context_->getIntegerType(64), 8));
                builder_->createStore(payload, payload_addr);
                store_reg(inst.dst, err_box, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ConstructOk: {
                ir::Value* payload = load_reg(inst.a, inst.type_a);
                ir::Value* ok_box = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 16)}, context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), ok_box);
                ir::Value* payload_addr = builder_->createAdd(ok_box, context_->getConstantInt(context_->getIntegerType(64), 8));
                builder_->createStore(payload, payload_addr);
                store_reg(inst.dst, ok_box, inst.result_type);
                break;
            }
            case LIR::LIR_Op::IsError: {
                ir::Value* container = load_reg(inst.a, LIR::Type::Ptr);
                ir::Value* is_err_flag = builder_->createLoad(container);
                ir::Value* is_err_bool = builder_->createCne(is_err_flag, context_->getConstantInt(context_->getIntegerType(64), 0));
                store_reg(inst.dst, builder_->createCast(is_err_bool, context_->getIntegerType(64)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Unwrap: {
                ir::Value* container = load_reg(inst.a, LIR::Type::Ptr);
                ir::Value* payload_addr = builder_->createAdd(container, context_->getConstantInt(context_->getIntegerType(64), 8));
                ir::Value* payload = builder_->createLoad(payload_addr);
                store_reg(inst.dst, payload, inst.result_type);
                break;
            }
            case LIR::LIR_Op::UnwrapOr: {
                ir::Value* container = load_reg(inst.a, LIR::Type::Ptr);
                ir::Value* is_err_flag = builder_->createLoad(container);
                ir::Value* is_err = builder_->createCne(is_err_flag, context_->getConstantInt(context_->getIntegerType(64), 0));
                
                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                std::string uoid = std::to_string(label_counter_++);
                ir::BasicBlock* b_err = builder_->createBasicBlock("uor_err_" + uoid, cur_fn);
                ir::BasicBlock* b_ok  = builder_->createBasicBlock("uor_ok_" + uoid, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("uor_done_" + uoid, cur_fn);

                ir::Instruction* res_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
                builder_->createBr(is_err, b_err, b_ok);

                builder_->setInsertPoint(b_err);
                ir::Value* fallback = (inst.b != UINT32_MAX) ? load_reg(inst.b, inst.type_b) : context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                builder_->createStore(fallback, res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_ok);
                ir::Value* payload_addr = builder_->createAdd(container, context_->getConstantInt(context_->getIntegerType(64), 8));
                ir::Value* payload = builder_->createLoad(payload_addr);
                builder_->createStore(payload, res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                store_reg(inst.dst, builder_->createLoad(res_slot), inst.result_type);
                break;
            }
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
            case LIR::LIR_Op::ListSet: {
                used_builtins_.insert("lm_list_set");
                ir::Function* fn = current_module_->getFunction("lm_list_set");
                if (!fn) fn = builder_->createFunction("lm_list_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                builder_->createCall(fn, {load_reg(inst.dst, inst.result_type), load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)});
                break;
            }
            case LIR::LIR_Op::StringIndex: {
                used_builtins_.insert("_builtin_string_byte_at");
                ir::Function* fn = current_module_->getFunction("_builtin_string_byte_at");
                if (!fn) fn = builder_->createFunction("_builtin_string_byte_at", context_->getIntegerType(64), {context_->getPointerType(context_->getIntegerType(8)), context_->getIntegerType(64)});
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
            case LIR::LIR_Op::MakeEnum: {
                used_builtins_.insert("lm_enum_new");
                ir::Function* fn = current_module_->getFunction("lm_enum_new");
                if (!fn) fn = builder_->createFunction("lm_enum_new", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* tag_val = context_->getConstantInt(context_->getIntegerType(64), static_cast<long long>(inst.imm));
                ir::Value* payload_val = (inst.a != UINT32_MAX) ? load_reg(inst.a, inst.type_a) : context_->getConstantInt(context_->getIntegerType(64), 0);
                if (inst.a != UINT32_MAX && (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32)) {
                    payload_val = builder_->createCast(payload_val, context_->getIntegerType(64));
                }
                ir::GlobalVariable* vname_gv = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "vname_" + inst.func_name, inst.func_name);
                store_reg(inst.dst, builder_->createCall(fn, {tag_val, payload_val, vname_gv}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::GetTag: {
                used_builtins_.insert("lm_enum_tag");
                ir::Function* fn = current_module_->getFunction("lm_enum_tag");
                if (!fn) fn = builder_->createFunction("lm_enum_tag", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::GetPayload: {
                used_builtins_.insert("lm_enum_payload");
                ir::Function* fn = current_module_->getFunction("lm_enum_payload");
                if (!fn) fn = builder_->createFunction("lm_enum_payload", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::NewFrame: {
                std::string name = inst.func_name; if (name.empty()) name = "Frame";
                uint32_t fields = static_cast<uint32_t>(inst.imm);
                uint32_t bytes = (fields > 0 ? fields : 2) * 8;
                ir::Type* type = current_module_->getType(name);
                if (!type) { ir::StructType* st = context_->createStructType(name); st->setBody({context_->getIntegerType(64), context_->getIntegerType(64)}); current_module_->addType(name, st); type = st; }
                ir::Value* frame_ptr = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), bytes)}, lir_type_to_fyra_type(inst.result_type));
                // Zero out allocated frame memory
                for (uint32_t f_idx = 0; f_idx < (fields > 0 ? fields : 2); ++f_idx) {
                    ir::Value* addr = builder_->createAdd(frame_ptr, context_->getConstantInt(context_->getIntegerType(64), f_idx * 8));
                    builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), addr);
                }
                store_reg(inst.dst, frame_ptr, inst.result_type);
                break;
            }
            case LIR::LIR_Op::FrameGetField:
            case LIR::LIR_Op::FrameGetFieldAtomic: {
                uint32_t field_idx = (inst.b != UINT32_MAX) ? inst.b : static_cast<uint32_t>(inst.imm);
                ir::Value* frame_ptr = load_reg(inst.a, LIR::Type::Ptr);
                ir::Value* addr = builder_->createAdd(frame_ptr, context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                store_reg(inst.dst, builder_->createLoad(addr), inst.result_type);
                break;
            }
            case LIR::LIR_Op::FrameSetField:
            case LIR::LIR_Op::FrameSetFieldAtomic: {
                // In LIR_Inst for FrameSetField:
                // dst = frame_ptr (object_reg), a = field_idx (offset), b = value_reg
                ir::Value* frame_ptr = load_reg(inst.dst, LIR::Type::Ptr);
                ir::Value* val = load_reg(inst.b, inst.type_b);
                uint32_t field_idx = inst.a;
                ir::Value* addr = builder_->createAdd(frame_ptr, context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                builder_->createStore(val, addr);
                break;
            }
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
                if (main_fn->getName() == "main") {
                    builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
                } else if (inst.a != UINT32_MAX) {
                    ir::Value* ret_val = load_reg(inst.a, inst.type_a);
                    builder_->createRet(ret_val);
                } else {
                    builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
                }
                terminated = true;
                break;
            case LIR::LIR_Op::Nop: break;
            // Shared Memory & Concurrency Operations
            case LIR::LIR_Op::SharedCellAlloc: {
                ir::Value* cell_ptr = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 8)}, lir_type_to_fyra_type(inst.result_type));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), cell_ptr);
                store_reg(inst.dst, cell_ptr, inst.result_type);
                break;
            }
            case LIR::LIR_Op::SharedCellStore: {
                ir::Value* cell_ptr = load_reg((inst.a != UINT32_MAX && inst.a != 0) ? inst.a : inst.dst, LIR::Type::Ptr);
                ir::Value* val = load_reg(inst.b, inst.type_b);
                builder_->createStore(val, cell_ptr);
                break;
            }
            case LIR::LIR_Op::SharedCellLoad: {
                ir::Value* cell_ptr = load_reg(inst.a, LIR::Type::Ptr);
                store_reg(inst.dst, builder_->createLoad(cell_ptr), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TaskContextAlloc: {
                ir::Value* ctx_ptr = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 64)}, lir_type_to_fyra_type(inst.result_type));
                for (uint32_t f_idx = 0; f_idx < 8; ++f_idx) {
                    ir::Value* addr = builder_->createAdd(ctx_ptr, context_->getConstantInt(context_->getIntegerType(64), f_idx * 8));
                    builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), addr);
                }
                store_reg(inst.dst, ctx_ptr, inst.result_type);
                break;
            }
            case LIR::LIR_Op::TaskContextInit: {
                if (inst.dst != UINT32_MAX) store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TaskSetField: {
                uint32_t ctx_reg = (inst.b != UINT32_MAX && inst.b != 0) ? inst.b : inst.a;
                uint32_t val_reg = (inst.a != UINT32_MAX && inst.a != ctx_reg) ? inst.a : (inst.dst != UINT32_MAX && inst.dst != ctx_reg ? inst.dst : inst.b);
                ir::Value* ctx_ptr = load_reg(ctx_reg, LIR::Type::Ptr);
                ir::Value* val = load_reg(val_reg, LIR::Type::I64);
                uint32_t field_idx = inst.imm;
                ir::Value* addr = builder_->createAdd(ctx_ptr, context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                builder_->createStore(val, addr);
                break;
            }
            case LIR::LIR_Op::TaskGetField: {
                ir::Value* ctx_ptr = load_reg(inst.a, LIR::Type::Ptr);
                uint32_t field_idx = inst.imm;
                ir::Value* addr = builder_->createAdd(ctx_ptr, context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                store_reg(inst.dst, builder_->createLoad(addr), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ParallelInit:
            case LIR::LIR_Op::SchedulerInit: {
                used_builtins_.insert("lm_list_new");
                ir::Function* fn = current_module_->getFunction("lm_list_new");
                if (!fn) fn = builder_->createFunction("lm_list_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), 16)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::SchedulerAddTask: {
                used_builtins_.insert("lm_list_append");
                ir::Function* fn = current_module_->getFunction("lm_list_append");
                if (!fn) fn = builder_->createFunction("lm_list_append", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                uint32_t s_reg = (inst.dst != UINT32_MAX && inst.dst != 0) ? inst.dst : inst.a;
                uint32_t t_reg = (inst.a != UINT32_MAX && inst.a != s_reg) ? inst.a : inst.b;
                ir::Value* sched_ptr = load_reg(s_reg, LIR::Type::Ptr);
                ir::Value* task_ptr = load_reg(t_reg, LIR::Type::Ptr);
                if (fn) builder_->createCall(fn, {sched_ptr, task_ptr}, context_->getIntegerType(64));
                break;
            }
            case LIR::LIR_Op::SchedulerRun: {
                used_builtins_.insert("lm_list_len");
                used_builtins_.insert("lm_list_get");
                used_builtins_.insert("lm_channel_pop");
                ir::Function* fn_len = current_module_->getFunction("lm_list_len");
                if (!fn_len) fn_len = builder_->createFunction("lm_list_len", context_->getIntegerType(64), {context_->getIntegerType(64)});
                ir::Function* fn_get = current_module_->getFunction("lm_list_get");
                if (!fn_get) fn_get = builder_->createFunction("lm_list_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Function* fn_pop = current_module_->getFunction("lm_channel_pop");
                if (!fn_pop) fn_pop = builder_->createFunction("lm_channel_pop", context_->getIntegerType(64), {context_->getIntegerType(64)});

                uint32_t s_reg = (inst.a != UINT32_MAX && inst.a != 0) ? inst.a : inst.dst;
                ir::Value* sched_ptr = load_reg(s_reg, LIR::Type::Ptr);
                ir::Value* count = builder_->createCall(fn_len, {sched_ptr}, context_->getIntegerType(64));

                std::string sid = std::to_string(label_counter_++);
                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                ir::BasicBlock* b_loop = builder_->createBasicBlock("sc_loop_" + sid, cur_fn);
                ir::BasicBlock* b_body = builder_->createBasicBlock("sc_body_" + sid, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("sc_done_" + sid, cur_fn);

                ir::Instruction* i_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), i_slot);
                builder_->createJmp(b_loop);

                builder_->setInsertPoint(b_loop);
                ir::Value* i_val = builder_->createLoad(i_slot);
                ir::Value* cond = builder_->createCslt(i_val, count);
                builder_->createBr(cond, b_body, b_done);

                builder_->setInsertPoint(b_body);
                ir::Value* task_ctx = builder_->createCall(fn_get, {sched_ptr, i_val}, context_->getIntegerType(64));

                ir::Value* f0 = builder_->createLoad(builder_->createAdd(task_ctx, context_->getConstantInt(context_->getIntegerType(64), 0)));
                ir::Value* f1_raw = builder_->createLoad(builder_->createAdd(task_ctx, context_->getConstantInt(context_->getIntegerType(64), 8)));
                ir::Value* f2 = builder_->createLoad(builder_->createAdd(task_ctx, context_->getConstantInt(context_->getIntegerType(64), 16)));
                ir::Value* f3 = builder_->createLoad(builder_->createAdd(task_ctx, context_->getConstantInt(context_->getIntegerType(64), 24)));
                ir::Value* fn_name_ptr = builder_->createLoad(builder_->createAdd(task_ctx, context_->getConstantInt(context_->getIntegerType(64), 32)));

                ir::Value* f1_len = builder_->createCall(fn_len, {f1_raw}, context_->getIntegerType(64));
                ir::Value* is_chan_iter = builder_->createCsgt(f1_len, context_->getConstantInt(context_->getIntegerType(64), 0));

                ir::BasicBlock* b_w_loop = builder_->createBasicBlock("sc_w_loop_" + sid, cur_fn);
                ir::BasicBlock* b_w_body = builder_->createBasicBlock("sc_w_body_" + sid, cur_fn);
                ir::BasicBlock* b_single = builder_->createBasicBlock("sc_single_" + sid, cur_fn);
                ir::BasicBlock* b_next_task = builder_->createBasicBlock("sc_next_t_" + sid, cur_fn);

                builder_->createBr(is_chan_iter, b_w_loop, b_single);

                auto emit_dispatch = [&](ir::Value* arg_f1) {
                    ir::Value* old0 = builder_->createLoad(reg_slots[0]);
                    ir::Value* old1 = builder_->createLoad(reg_slots[1]);
                    ir::Value* old2 = builder_->createLoad(reg_slots[2]);
                    ir::Value* old3 = builder_->createLoad(reg_slots[3]);

                    builder_->createStore(f0, reg_slots[0]);
                    builder_->createStore(arg_f1, reg_slots[1]);
                    builder_->createStore(f2, reg_slots[2]);
                    builder_->createStore(f3, reg_slots[3]);
                    store_reg(max_reg + 1, fn_name_ptr, LIR::Type::Ptr);

                    std::string cid = std::to_string(label_counter_++);
                    ir::BasicBlock* b_dispatch = builder_->createBasicBlock("sched_disp_" + cid, cur_fn);
                    ir::BasicBlock* b_raw_call = builder_->createBasicBlock("sched_raw_" + cid, cur_fn);
                    ir::BasicBlock* b_done_call = builder_->createBasicBlock("sched_done_" + cid, cur_fn);

                    ir::Value* is_ge_ptr = builder_->createCuge(fn_name_ptr, context_->getConstantInt(context_->getIntegerType(64), 65536));
                    ir::Value* high_bits = builder_->createShr(fn_name_ptr, context_->getConstantInt(context_->getIntegerType(64), 48));
                    ir::Value* high_zero = builder_->createCeq(high_bits, context_->getConstantInt(context_->getIntegerType(64), 0));
                    ir::Value* is_valid_ptr = builder_->createAnd(is_ge_ptr, high_zero);

                    builder_->createBr(is_valid_ptr, b_dispatch, b_raw_call);

                    builder_->setInsertPoint(b_dispatch);
                    used_builtins_.insert("lm_key_eq");
                    ir::Function* fn_eq = current_module_->getFunction("lm_key_eq");
                    if (!fn_eq) fn_eq = builder_->createFunction("lm_key_eq", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});

                    std::vector<ir::Function*> cand_funcs;
                    for (const auto& f : current_module_->getFunctions()) {
                        if (f->getName() != "main" && !f->getName().starts_with("lm_") && !f->getName().starts_with("_builtin_")) {
                            cand_funcs.push_back(f.get());
                        }
                    }

                    ir::BasicBlock* cur_check_bb = b_dispatch;
                    for (size_t fi = 0; fi < cand_funcs.size(); ++fi) {
                        ir::Function* target_f = cand_funcs[fi];
                        std::string f_name = target_f->getName();

                        builder_->setInsertPoint(cur_check_bb);
                        ir::GlobalVariable* gv_fname = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "fn_s_str_" + f_name + "_" + cid, f_name);
                        ir::Value* eq_res = fn_eq ? static_cast<ir::Value*>(builder_->createCall(fn_eq, {fn_name_ptr, gv_fname}, context_->getIntegerType(64))) : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0));
                        ir::Value* is_match = builder_->createCne(eq_res, context_->getConstantInt(context_->getIntegerType(64), 0));

                        size_t dot_p = f_name.rfind('.');
                        if (dot_p != std::string::npos) {
                            std::string unq_name = f_name.substr(dot_p + 1);
                            ir::GlobalVariable* gv_unq = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "fn_s_unq_" + unq_name + "_" + cid + "_" + std::to_string(fi), unq_name);
                            ir::Value* unq_eq = fn_eq ? static_cast<ir::Value*>(builder_->createCall(fn_eq, {fn_name_ptr, gv_unq}, context_->getIntegerType(64))) : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0));
                            ir::Value* unq_match = builder_->createCne(unq_eq, context_->getConstantInt(context_->getIntegerType(64), 0));
                            is_match = builder_->createOr(is_match, unq_match);
                        }

                        ir::BasicBlock* b_match = builder_->createBasicBlock("sched_m_" + std::to_string(fi) + "_" + cid, cur_fn);
                        ir::BasicBlock* b_next_check = builder_->createBasicBlock("sched_next_chk_" + std::to_string(fi) + "_" + cid, cur_fn);

                        builder_->createBr(is_match, b_match, b_next_check);

                        builder_->setInsertPoint(b_match);
                        std::vector<ir::Value*> call_args_matching = {f0, arg_f1, f2, f3};
                        while (call_args_matching.size() < target_f->getParameters().size()) {
                            call_args_matching.push_back(context_->getConstantInt(context_->getIntegerType(64), 0));
                        }
                        if (target_f) builder_->createCall(target_f, call_args_matching, context_->getIntegerType(64));
                        builder_->createJmp(b_done_call);

                        cur_check_bb = b_next_check;
                    }

                    builder_->setInsertPoint(cur_check_bb);
                    builder_->createJmp(b_raw_call);

                    builder_->setInsertPoint(b_raw_call);
                    builder_->createJmp(b_done_call);

                    builder_->setInsertPoint(b_done_call);
                    builder_->createStore(old0, reg_slots[0]);
                    builder_->createStore(old1, reg_slots[1]);
                    builder_->createStore(old2, reg_slots[2]);
                    builder_->createStore(old3, reg_slots[3]);
                };

                // Stream worker loop branch
                builder_->setInsertPoint(b_w_loop);
                ir::Value* rem_cnt = builder_->createCall(fn_len, {f1_raw}, context_->getIntegerType(64));
                ir::Value* has_rem = builder_->createCsgt(rem_cnt, context_->getConstantInt(context_->getIntegerType(64), 0));
                builder_->createBr(has_rem, b_w_body, b_next_task);

                builder_->setInsertPoint(b_w_body);
                ir::Value* popped_item = builder_->createCall(fn_pop, {f1_raw}, context_->getIntegerType(64));
                emit_dispatch(popped_item);
                builder_->createJmp(b_w_loop);

                // Single task execution branch
                builder_->setInsertPoint(b_single);
                emit_dispatch(f1_raw);
                builder_->createJmp(b_next_task);

                builder_->setInsertPoint(b_next_task);
                ir::Value* next_i_val = builder_->createAdd(i_val, context_->getConstantInt(context_->getIntegerType(64), 1));
                builder_->createStore(next_i_val, i_slot);
                builder_->createJmp(b_loop);

                builder_->setInsertPoint(b_done);
                break;
            }
            case LIR::LIR_Op::ParallelSync: break;
            case LIR::LIR_Op::ResourceCreate: {
                if (inst.imm == (uint32_t)LIR::ResourceType::CHANNEL || inst.imm == (uint32_t)LIR::ResourceType::MEMORY) {
                    used_builtins_.insert("lm_list_new");
                    ir::Function* fn = current_module_->getFunction("lm_list_new");
                    if (!fn) fn = builder_->createFunction("lm_list_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                    store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), 16)}, context_->getIntegerType(64)), inst.result_type);
                } else {
                    store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::ChannelAlloc: {
                used_builtins_.insert("lm_list_new");
                ir::Function* fn = current_module_->getFunction("lm_list_new");
                if (!fn) fn = builder_->createFunction("lm_list_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), 16)}, context_->getIntegerType(64)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ChannelSend:
            case LIR::LIR_Op::ChannelOffer:
            case LIR::LIR_Op::ChannelPush: {
                used_builtins_.insert("lm_list_append");
                ir::Function* fn = current_module_->getFunction("lm_list_append");
                if (!fn) fn = builder_->createFunction("lm_list_append", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* ch_ptr = (inst.a != UINT32_MAX && inst.a != 0) ? load_reg(inst.a, LIR::Type::Ptr) : load_reg(inst.dst, LIR::Type::Ptr);
                ir::Value* val = (inst.b != UINT32_MAX) ? load_reg(inst.b, LIR::Type::I64) : load_reg(inst.a, LIR::Type::I64);
                if (fn) builder_->createCall(fn, {ch_ptr, val}, context_->getIntegerType(64));
                if (inst.dst != UINT32_MAX && inst.dst != inst.a) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 1), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ChannelRecv:
            case LIR::LIR_Op::ChannelPop:
            case LIR::LIR_Op::ChannelPoll: {
                used_builtins_.insert("lm_channel_pop");
                used_builtins_.insert("lm_list_new");
                ir::Function* fn = current_module_->getFunction("lm_channel_pop");
                ir::Value* ch_ptr = (inst.a != UINT32_MAX && inst.a != 0) ? load_reg(inst.a, LIR::Type::Ptr) : load_reg(inst.dst, LIR::Type::Ptr);
                if (fn) store_reg(inst.dst, builder_->createCall(fn, {ch_ptr}, context_->getIntegerType(64)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ChannelHasData: {
                used_builtins_.insert("lm_list_len");
                ir::Function* fn = current_module_->getFunction("lm_list_len");
                if (!fn) fn = builder_->createFunction("lm_list_len", context_->getIntegerType(64), {context_->getIntegerType(64)});
                ir::Value* ch_ptr = (inst.a != UINT32_MAX && inst.a != 0) ? load_reg(inst.a, LIR::Type::Ptr) : load_reg(inst.dst, LIR::Type::Ptr);
                ir::Value* count = fn ? static_cast<ir::Value*>(builder_->createCall(fn, {ch_ptr}, context_->getIntegerType(64))) : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0));
                store_reg(inst.dst, builder_->createCsgt(count, context_->getConstantInt(context_->getIntegerType(64), 0)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ChannelClose: break;
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
                if (inst.dst != UINT32_MAX) store_reg(inst.dst, res, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ForeignCallDirect: {
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                ir::Value* res = builder_->createExternCall(inst.func_name, args, lir_type_to_fyra_type(inst.result_type));
                if (inst.dst != UINT32_MAX) store_reg(inst.dst, res, inst.result_type);
                break;
            }
            default:
                if (inst.dst != UINT32_MAX) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                break;
        }
    }
    if (!terminated && builder_->getInsertPoint()) builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
}

} // namespace LM::Backend::Fyra
