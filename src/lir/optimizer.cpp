#include "optimizer.hh"
#include "functions.hh"
#include "analysis.hh"
#include "backend/vm/vm_value.hh"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

namespace LM {
namespace LIR {

bool Optimizer::optimize() {
    bool changed = false;
    bool pass_changed;
    int pass_count = 0;

    report_ = OptimizationReport{};
    report_.function_name = func_.name;
    report_.initial_instructions = func_.instructions.size();
    report_.memory_ops_before = MetricsCollector::count_memory_ops(func_);

    AnalysisManager am(func_);

    auto run_pass = [&](const std::string& name, auto pass_fn) -> bool {
        size_t before = func_.instructions.size();
        bool res = pass_fn();
        size_t after = func_.instructions.size();
        int delta = static_cast<int>(after) - static_cast<int>(before);
        if (delta != 0) {
            report_.pass_deltas[name] += delta;
        }
        return res;
    };

    do {
        pass_changed = false;

        bool ur = run_pass("Unreachable code elimination", [&]() { return remove_unreachable_code(); });
        if (ur) am.invalidate_all();

        bool cf = run_pass("Constant folding", [&]() { return constant_folding(); });
        if (cf) am.invalidate_all();

        bool po = run_pass("Peephole / Strength reduction", [&]() { return peephole_optimize(); });
        if (po) am.invalidate_all();

        bool rm = run_pass("Redundant memory elimination", [&]() { return redundant_memory_elimination(); });
        if (rm) am.invalidate_def_use();

        bool cp = run_pass("Copy propagation", [&]() { return copy_propagation(); });
        if (cp) am.invalidate_all();

        bool dce = run_pass("DCE", [&]() { return dead_code_elimination(); });
        if (dce) am.invalidate_all();

        bool rc = run_pass("Redundant entry calls", [&]() { return remove_redundant_entry_calls(); });
        if (rc) am.invalidate_all();

        bool fi = run_pass("Inlining", [&]() { return function_inlining(); });
        if (fi) am.invalidate_all();

        bool gvn = run_pass("GVN", [&]() { return global_value_numbering(); });
        if (gvn) am.invalidate_all();

        bool gch = run_pass("Generational check hoisting", [&]() { return generational_check_hoisting(); });
        if (gch) am.invalidate_all();

        bool pol = run_pass("Prune orphaned labels", [&]() { return prune_orphaned_labels(); });
        if (pol) am.invalidate_cfg();

        bool tco = run_pass("TCO", [&]() { return tail_call_optimization(); });
        if (tco) am.invalidate_all();

        bool licm = run_pass("LICM", [&]() { return loop_invariant_code_motion(); });
        if (licm) am.invalidate_all();

        pass_changed |= ur;
        pass_changed |= cf;
        pass_changed |= po;
        pass_changed |= rm;
        pass_changed |= cp;
        pass_changed |= dce;
        pass_changed |= rc;
        pass_changed |= fi;
        pass_changed |= gvn;
        pass_changed |= gch;
        pass_changed |= pol;
        pass_changed |= tco;
        pass_changed |= licm;

        changed |= pass_changed;
        pass_count++;
    } while (pass_changed && pass_count < 10);

    report_.final_instructions = func_.instructions.size();
    report_.memory_ops_after = MetricsCollector::count_memory_ops(func_);

    if (std::getenv("LIMITLY_PRINT_OPT_REPORT")) {
        report_.print();
    }

    return changed;
}

bool Optimizer::dead_code_elimination() {
    if (func_.instructions.empty()) return false;

    bool changed = false;
    AnalysisManager am(func_);
    const auto& def_use = am.get_def_use();

    // Mark instructions to remove
    std::vector<bool> to_remove(func_.instructions.size(), false);

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        const auto& inst = func_.instructions[i];

        if (DefUseAnalysis::has_side_effects(inst)) continue;

        if (inst.dst != UINT32_MAX) {
            size_t use_count = def_use.get_use_count(inst.dst);
            if (use_count == 0) {
                to_remove[i] = true;
                changed = true;
            }
        }
    }

    if (changed) {
        for (int i = static_cast<int>(func_.instructions.size()) - 1; i >= 0; --i) {
            if (to_remove[i]) {
                func_.instructions.erase(func_.instructions.begin() + i);
            }
        }
    }

    return changed;
}

bool Optimizer::remove_unreachable_code() {
    if (func_.instructions.empty()) return false;

    bool changed = false;
    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        const auto& inst = func_.instructions[i];

        if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret) {
            size_t j = i + 1;
            while (j < func_.instructions.size() && func_.instructions[j].op != LIR_Op::Label) {
                func_.instructions.erase(func_.instructions.begin() + j);
                changed = true;
            }
        }
    }

    return changed;
}

bool Optimizer::dead_code_elimination_simple() {
    return dead_code_elimination();
}

bool Optimizer::redundant_memory_elimination() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    std::unordered_map<Reg, Reg> active_memory_stores;

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        auto& inst = func_.instructions[i];

        if (inst.op == LIR_Op::Label || inst.op == LIR_Op::Jump ||
            inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse ||
            inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid ||
            inst.op == LIR_Op::CallIndirect || inst.op == LIR_Op::CallBuiltin) {
            active_memory_stores.clear();
            continue;
        }

        if (inst.op == LIR_Op::MemoryStore || inst.op == LIR_Op::Store) {
            Reg ptr_reg = inst.a;
            Reg val_reg = inst.b;
            auto it = active_memory_stores.find(ptr_reg);
            if (it != active_memory_stores.end() && it->second == val_reg) {
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            } else {
                active_memory_stores[ptr_reg] = val_reg;
            }
        }

        if (inst.op == LIR_Op::MemoryLoad || inst.op == LIR_Op::Load) {
            Reg ptr_reg = inst.a;
            auto it = active_memory_stores.find(ptr_reg);
            if (it != active_memory_stores.end()) {
                Reg stored_val = it->second;
                inst.op = LIR_Op::Mov;
                inst.a = stored_val;
                inst.b = UINT32_MAX;
                changed = true;
                if (inst.dst != UINT32_MAX) {
                    for (auto store_it = active_memory_stores.begin(); store_it != active_memory_stores.end(); ) {
                        if (store_it->first == inst.dst || store_it->second == inst.dst) {
                            store_it = active_memory_stores.erase(store_it);
                        } else {
                            ++store_it;
                        }
                    }
                }
                continue;
            }
        }

        if (inst.dst != UINT32_MAX) {
            for (auto store_it = active_memory_stores.begin(); store_it != active_memory_stores.end(); ) {
                if (store_it->first == inst.dst || store_it->second == inst.dst) {
                    store_it = active_memory_stores.erase(store_it);
                } else {
                    ++store_it;
                }
            }
        }
    }

    return changed;
}

bool Optimizer::has_instruction_side_effects(const LIR_Inst& inst) const {
    return DefUseAnalysis::has_side_effects(inst);
}

bool Optimizer::peephole_optimize() {
    bool changed = false;

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        auto& inst = func_.instructions[i];

        if (inst.op == LIR_Op::Mov && inst.dst == inst.a) {
            func_.instructions.erase(func_.instructions.begin() + i);
            --i;
            changed = true;
            continue;
        }

        if (inst.op == LIR_Op::Mov && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Mov && next.a == inst.dst) {
                next.a = inst.a;
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            }
        }

        if (inst.op == LIR_Op::LoadConst && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::LoadConst && next.dst == inst.dst &&
                next.const_val == inst.const_val) {
                func_.instructions.erase(func_.instructions.begin() + i + 1);
                changed = true;
                continue;
            }
        }

        if (inst.op == LIR_Op::Add && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 0) {
                    inst.op = LIR_Op::Mov;
                    inst.b = UINT32_MAX;
                    changed = true;
                    continue;
                }
            }
        }

        if (inst.op == LIR_Op::Mul && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 0) {
                    inst.op = LIR_Op::LoadConst;
                    inst.a = UINT32_MAX;
                    inst.b = UINT32_MAX;
                    inst.const_val = make_i64(0);
                    changed = true;
                    continue;
                }
            }
        }

        if (inst.op == LIR_Op::Mul && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 1) {
                    inst.op = LIR_Op::Mov;
                    inst.b = UINT32_MAX;
                    changed = true;
                    continue;
                }
            }
        }

        if (inst.op == LIR_Op::Mul && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val)) {
                    int64_t val = UNBOX_INT(prev.const_val);
                    if (val == 2) {
                        inst.op = LIR_Op::Add;
                        inst.b = inst.a;
                        changed = true;
                        continue;
                    } else if (val > 2 && (val & (val - 1)) == 0) {
                        int shift = 0;
                        while (val > 1) { val >>= 1; shift++; }
                        prev.const_val = make_i64(shift);
                        inst.op = LIR_Op::Shl;
                        changed = true;
                        continue;
                    }
                }
            }
        }

        if ((inst.op == LIR_Op::CmpEQ || inst.op == LIR_Op::CmpLE || inst.op == LIR_Op::CmpGE) &&
            inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            inst.const_val = VAL_TRUE;
            changed = true;
            continue;
        }

        if ((inst.op == LIR_Op::CmpNEQ || inst.op == LIR_Op::CmpLT || inst.op == LIR_Op::CmpGT) &&
            inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            inst.const_val = VAL_FALSE;
            changed = true;
            continue;
        }

        if (inst.op == LIR_Op::And && inst.a == inst.b) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
            continue;
        }

        if (inst.op == LIR_Op::Or && inst.a == inst.b) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
            continue;
        }

        if (inst.op == LIR_Op::Xor && inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            inst.const_val = VAL_FALSE;
            changed = true;
            continue;
        }

        if (inst.op == LIR_Op::Neg && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Neg && next.a == inst.dst) {
                next.op = LIR_Op::Mov;
                next.a = inst.a;
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            }
        }

        if (inst.op == LIR_Op::Jump && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Label && next.imm == inst.imm) {
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            }
        }

        if (inst.op == LIR_Op::LoadConst && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Mov && next.a == inst.dst) {
                inst.dst = next.dst;
                func_.instructions.erase(func_.instructions.begin() + i + 1);
                changed = true;
                continue;
            }
        }

        if (inst.op == LIR_Op::Mov && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if ((next.op == LIR_Op::Return || next.op == LIR_Op::Ret) && next.dst == inst.dst) {
                next.dst = inst.a;
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            }
        }

        if (inst.op == LIR_Op::Sub && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 0) {
                    inst.op = LIR_Op::Mov;
                    inst.b = UINT32_MAX;
                    changed = true;
                    continue;
                }
            }
        }

        if (inst.op == LIR_Op::Div && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 1) {
                    inst.op = LIR_Op::Mov;
                    inst.b = UINT32_MAX;
                    changed = true;
                    continue;
                }
            }
        }

        if (inst.op == LIR_Op::Mod && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 1) {
                    inst.op = LIR_Op::LoadConst;
                    inst.a = UINT32_MAX;
                    inst.b = UINT32_MAX;
                    inst.const_val = make_i64(0);
                    changed = true;
                    continue;
                }
            }
        }
    }

    return changed;
}

bool Optimizer::constant_folding() {
    if (func_.instructions.empty()) return false;

    bool changed = false;
    AnalysisManager am(func_);
    const auto& cfg = am.get_cfg();

    for (const auto& block : cfg.get_blocks()) {
        if (!block.reachable) continue;

        std::unordered_map<Reg, Backend::Value> block_consts;

        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            auto& inst = func_.instructions[i];

            if (inst.op == LIR_Op::LoadConst) {
                block_consts[inst.dst] = inst.const_val;
                continue;
            }

            if (inst.op == LIR_Op::Mov) {
                if (block_consts.count(inst.a)) {
                    block_consts[inst.dst] = block_consts[inst.a];
                } else {
                    block_consts.erase(inst.dst);
                }
                continue;
            }

            if (inst.op == LIR_Op::Add || inst.op == LIR_Op::Sub ||
                inst.op == LIR_Op::Mul || inst.op == LIR_Op::Div || inst.op == LIR_Op::Mod) {
                if (block_consts.count(inst.a) && block_consts.count(inst.b)) {
                    Backend::Value va = block_consts[inst.a];
                    Backend::Value vb = block_consts[inst.b];

                    if (IS_INT(va) && IS_INT(vb)) {
                        int64_t a = UNBOX_INT(va);
                        int64_t b = UNBOX_INT(vb);
                        int64_t res = 0;
                        bool valid = true;

                        if (inst.op == LIR_Op::Add) res = a + b;
                        else if (inst.op == LIR_Op::Sub) res = a - b;
                        else if (inst.op == LIR_Op::Mul) res = a * b;
                        else if (inst.op == LIR_Op::Div) {
                            if (b == 0) valid = false;
                            else res = a / b;
                        } else if (inst.op == LIR_Op::Mod) {
                            if (b == 0) valid = false;
                            else res = a % b;
                        }

                        if (valid) {
                            Backend::Value res_val = make_i64(res);
                            inst.op = LIR_Op::LoadConst;
                            inst.a = UINT32_MAX;
                            inst.b = UINT32_MAX;
                            inst.const_val = res_val;
                            block_consts[inst.dst] = res_val;
                            changed = true;
                        }
                    }
                } else {
                    if (inst.dst != UINT32_MAX) block_consts.erase(inst.dst);
                }
            } else if (inst.dst != UINT32_MAX) {
                block_consts.erase(inst.dst);
            }
        }
    }

    return changed;
}

bool Optimizer::function_inlining() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    auto& func_mgr = LIRFunctionManager::getInstance();

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        auto& inst = func_.instructions[i];

        if ((inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid) &&
            !inst.func_name.empty() && inst.func_name != func_.name &&
            func_mgr.hasFunction(inst.func_name)) {

            auto target_func = func_mgr.getFunction(inst.func_name);
            if (!target_func) continue;

            const auto& target_insts = target_func->getInstructions();
            if (target_insts.empty() || target_insts.size() > 12) continue;

            bool is_leaf = true;
            for (const auto& ti : target_insts) {
                if (ti.op == LIR_Op::Call || ti.op == LIR_Op::CallVoid ||
                    ti.op == LIR_Op::CallIndirect || ti.op == LIR_Op::CallBuiltin ||
                    ti.op == LIR_Op::Jump || ti.op == LIR_Op::JumpIf || ti.op == LIR_Op::JumpIfFalse) {
                    is_leaf = false;
                    break;
                }
            }
            if (!is_leaf) continue;

            size_t num_params = inst.call_args.size();
            size_t max_target_reg = num_params + 16;
            for (const auto& ti : target_insts) {
                if (ti.dst != UINT32_MAX && ti.dst > max_target_reg) max_target_reg = ti.dst;
                if (ti.a != UINT32_MAX && ti.a > max_target_reg) max_target_reg = ti.a;
                if (ti.b != UINT32_MAX && ti.b > max_target_reg) max_target_reg = ti.b;
            }

            Reg base_reg = func_.allocate_register();
            for (size_t r = 1; r <= max_target_reg; ++r) {
                func_.allocate_register();
            }

            std::vector<LIR_Inst> inlined_insts;

            for (size_t param_idx = 0; param_idx < inst.call_args.size(); ++param_idx) {
                Reg param_reg = static_cast<Reg>(param_idx) + base_reg;
                Reg arg_reg = inst.call_args[param_idx];
                inlined_insts.push_back(LIR_Inst(LIR_Op::Mov, Type::I64, param_reg, arg_reg, 0));
            }

            for (const auto& ti : target_insts) {
                if (ti.op == LIR_Op::Return || ti.op == LIR_Op::Ret) {
                    if (inst.dst != UINT32_MAX && ti.dst != UINT32_MAX) {
                        Reg ret_val = ti.dst + base_reg;
                        inlined_insts.push_back(LIR_Inst(LIR_Op::Mov, Type::I64, inst.dst, ret_val, 0));
                    }
                } else {
                    LIR_Inst mapped = ti;
                    if (mapped.dst != UINT32_MAX) mapped.dst += base_reg;
                    if (mapped.a != UINT32_MAX) mapped.a += base_reg;
                    if (mapped.b != UINT32_MAX) mapped.b += base_reg;
                    inlined_insts.push_back(mapped);
                }
            }

            func_.instructions.erase(func_.instructions.begin() + i);
            func_.instructions.insert(func_.instructions.begin() + i, inlined_insts.begin(), inlined_insts.end());
            changed = true;
            break;
        }
    }

    return changed;
}

bool Optimizer::copy_propagation() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    AnalysisManager am(func_);
    const auto& cfg = am.get_cfg();

    for (const auto& block : cfg.get_blocks()) {
        if (!block.reachable) continue;

        std::unordered_map<Reg, Reg> copy_map;

        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            auto& inst = func_.instructions[i];

            // Substitute operands if copy exists
            if (inst.a != UINT32_MAX && copy_map.count(inst.a)) {
                inst.a = copy_map[inst.a];
                changed = true;
            }
            if (inst.b != UINT32_MAX && copy_map.count(inst.b)) {
                inst.b = copy_map[inst.b];
                changed = true;
            }
            for (size_t arg_idx = 0; arg_idx < inst.call_args.size(); ++arg_idx) {
                if (inst.call_args[arg_idx] != UINT32_MAX && copy_map.count(inst.call_args[arg_idx])) {
                    inst.call_args[arg_idx] = copy_map[inst.call_args[arg_idx]];
                    changed = true;
                }
            }

            // Invalidate copies if destination or source is overwritten
            if (inst.dst != UINT32_MAX) {
                copy_map.erase(inst.dst);
                for (auto it = copy_map.begin(); it != copy_map.end(); ) {
                    if (it->second == inst.dst) {
                        it = copy_map.erase(it);
                    } else {
                        ++it;
                    }
                }
            }

            // Track new Mov copy
            if (inst.op == LIR_Op::Mov && inst.dst != UINT32_MAX && inst.a != UINT32_MAX && inst.dst != inst.a) {
                copy_map[inst.dst] = inst.a;
            }
        }
    }

    return changed;
}

bool Optimizer::global_value_numbering() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    AnalysisManager am(func_);
    const auto& dom = am.get_dom();
    const auto& cfg = am.get_cfg();

    struct ExprKey {
        LIR_Op op;
        Reg a;
        Reg b;
        bool operator==(const ExprKey& o) const { return op == o.op && a == o.a && b == o.b; }
    };

    struct ExprKeyHash {
        size_t operator()(const ExprKey& k) const {
            return (static_cast<size_t>(k.op) << 16) ^ (k.a << 8) ^ k.b;
        }
    };

    struct AvailableExpr {
        Reg dst_reg;
        uint32_t block_id;
    };

    std::unordered_map<ExprKey, AvailableExpr, ExprKeyHash> avail_table;

    for (const auto& block : cfg.get_blocks()) {
        if (!block.reachable) continue;

        for (size_t i = block.start_inst_idx; i < block.end_inst_idx; ++i) {
            auto& inst = func_.instructions[i];

            if (DefUseAnalysis::has_side_effects(inst) || inst.op == LIR_Op::Load || inst.op == LIR_Op::MemoryLoad) {
                if (inst.dst != UINT32_MAX) {
                    Reg r = inst.dst;
                    for (auto it = avail_table.begin(); it != avail_table.end(); ) {
                        if (it->first.a == r || it->first.b == r || it->second.dst_reg == r) {
                            it = avail_table.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
                continue;
            }

            if (inst.op == LIR_Op::Add || inst.op == LIR_Op::Sub || inst.op == LIR_Op::Mul ||
                inst.op == LIR_Op::Div || inst.op == LIR_Op::And || inst.op == LIR_Op::Or ||
                inst.op == LIR_Op::Xor || inst.op == LIR_Op::Shl || inst.op == LIR_Op::Shr ||
                inst.op == LIR_Op::CmpEQ || inst.op == LIR_Op::CmpNEQ || inst.op == LIR_Op::CmpLT ||
                inst.op == LIR_Op::CmpLE || inst.op == LIR_Op::CmpGT || inst.op == LIR_Op::CmpGE) {

                ExprKey key{inst.op, inst.a, inst.b};
                auto it = avail_table.find(key);
                if (it != avail_table.end()) {
                    if (dom.dominates(it->second.block_id, block.id)) {
                        Reg existing_dst = it->second.dst_reg;
                        inst.op = LIR_Op::Mov;
                        inst.a = existing_dst;
                        inst.b = UINT32_MAX;
                        changed = true;
                        continue;
                    }
                }

                if (inst.dst != UINT32_MAX) {
                    Reg r = inst.dst;
                    for (auto it_a = avail_table.begin(); it_a != avail_table.end(); ) {
                        if (it_a->first.a == r || it_a->first.b == r || it_a->second.dst_reg == r) {
                            it_a = avail_table.erase(it_a);
                        } else {
                            ++it_a;
                        }
                    }
                }

                if (inst.dst != UINT32_MAX && inst.dst != inst.a && inst.dst != inst.b) {
                    avail_table[key] = AvailableExpr{inst.dst, block.id};
                }
            } else if (inst.dst != UINT32_MAX) {
                Reg r = inst.dst;
                for (auto it = avail_table.begin(); it != avail_table.end(); ) {
                    if (it->first.a == r || it->first.b == r || it->second.dst_reg == r) {
                        it = avail_table.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }
    }

    return changed;
}

bool Optimizer::generational_check_hoisting() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    for (size_t i = 0; i + 1 < func_.instructions.size(); ) {
        auto& first = func_.instructions[i];
        auto& second = func_.instructions[i + 1];

        if (first.op == LIR_Op::RegionEnter && second.op == LIR_Op::RegionExit &&
            first.imm == second.imm) {
            func_.instructions.erase(func_.instructions.begin() + i, func_.instructions.begin() + i + 2);
            changed = true;
            if (i > 0) --i;
        } else {
            ++i;
        }
    }

    return changed;
}

bool Optimizer::prune_orphaned_labels() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    std::unordered_set<uint32_t> targeted_labels;
    for (const auto& inst : func_.instructions) {
        if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
            targeted_labels.insert(static_cast<uint32_t>(inst.imm));
        }
    }

    uint32_t first_label = UINT32_MAX;
    for (const auto& inst : func_.instructions) {
        if (inst.op == LIR_Op::Label) {
            first_label = static_cast<uint32_t>(inst.imm);
            break;
        }
    }

    for (size_t i = 0; i < func_.instructions.size(); ) {
        const auto& inst = func_.instructions[i];
        if (inst.op == LIR_Op::Label && inst.imm != first_label &&
            targeted_labels.find(inst.imm) == targeted_labels.end()) {
            func_.instructions.erase(func_.instructions.begin() + i);
            changed = true;
        } else {
            ++i;
        }
    }

    return changed;
}

bool Optimizer::tail_call_optimization() {
    if (func_.instructions.empty() || func_.name.empty()) return false;
    bool changed = false;

    uint32_t entry_label = UINT32_MAX;
    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        if (func_.instructions[i].op == LIR_Op::Label) {
            entry_label = static_cast<uint32_t>(func_.instructions[i].imm);
            break;
        }
    }

    if (entry_label == UINT32_MAX) return false;

    for (size_t i = 0; i + 1 < func_.instructions.size(); ++i) {
        auto& call_inst = func_.instructions[i];
        const auto& next_inst = func_.instructions[i + 1];

        if ((call_inst.op == LIR_Op::Call || call_inst.op == LIR_Op::CallVoid) &&
            call_inst.func_name == func_.name &&
            (next_inst.op == LIR_Op::Return || next_inst.op == LIR_Op::Ret)) {

            std::vector<LIR_Inst> replacement;
            size_t num_args = call_inst.call_args.size();
            std::vector<Reg> temps(num_args);

            for (size_t arg_idx = 0; arg_idx < num_args; ++arg_idx) {
                temps[arg_idx] = func_.allocate_register();
                replacement.push_back(LIR_Inst(LIR_Op::Mov, Type::I64, temps[arg_idx], call_inst.call_args[arg_idx], 0));
            }
            for (size_t arg_idx = 0; arg_idx < num_args; ++arg_idx) {
                Reg param_reg = static_cast<Reg>(arg_idx);
                replacement.push_back(LIR_Inst(LIR_Op::Mov, Type::I64, param_reg, temps[arg_idx], 0));
            }

            replacement.push_back(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, entry_label));

            func_.instructions.erase(func_.instructions.begin() + i);
            func_.instructions.insert(func_.instructions.begin() + i, replacement.begin(), replacement.end());
            changed = true;
            break;
        }
    }

    return changed;
}

bool Optimizer::loop_invariant_code_motion() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    AnalysisManager am(func_);
    const auto& loops = am.get_loops().get_loops();
    const auto& cfg = am.get_cfg();

    for (const auto& loop : loops) {
        std::unordered_map<Reg, size_t> loop_reg_defs;
        for (uint32_t block_id : loop.body_blocks) {
            const auto* block = cfg.get_block(block_id);
            if (!block) continue;
            for (size_t k = block->start_inst_idx; k < block->end_inst_idx; ++k) {
                if (func_.instructions[k].dst != UINT32_MAX) {
                    loop_reg_defs[func_.instructions[k].dst]++;
                }
            }
        }

        const auto* header_block = cfg.get_block(loop.header_id);
        if (!header_block) continue;

        for (uint32_t block_id : loop.body_blocks) {
            const auto* block = cfg.get_block(block_id);
            if (!block) continue;

            for (size_t k = block->start_inst_idx; k < block->end_inst_idx; ++k) {
                const auto& cand = func_.instructions[k];
                if (DefUseAnalysis::has_side_effects(cand) || cand.dst == UINT32_MAX) continue;

                bool a_invariant = (cand.a == UINT32_MAX || loop_reg_defs.count(cand.a) == 0);
                bool b_invariant = (cand.b == UINT32_MAX || loop_reg_defs.count(cand.b) == 0);
                bool dst_single_def = (loop_reg_defs[cand.dst] == 1);

                if (a_invariant && b_invariant && dst_single_def) {
                    LIR_Inst hoisted = cand;
                    func_.instructions.erase(func_.instructions.begin() + k);

                    size_t insert_pos = header_block->start_inst_idx;
                    if (insert_pos < func_.instructions.size() &&
                        func_.instructions[insert_pos].op == LIR_Op::Label) {
                        insert_pos++;
                    }
                    func_.instructions.insert(func_.instructions.begin() + insert_pos, hoisted);
                    changed = true;
                    break;
                }
            }
            if (changed) break;
        }
        if (changed) break;
    }

    return changed;
}

bool Optimizer::remove_redundant_entry_calls() {
    if (func_.instructions.empty()) return false;

    if (func_.name != "__top_level_wrapper__") return false;

    bool changed = false;

    for (size_t i = 0; i + 1 < func_.instructions.size(); ++i) {
        const auto& first = func_.instructions[i];
        const auto& second = func_.instructions[i + 1];

        if ((first.op == LIR_Op::Call || first.op == LIR_Op::CallVoid) &&
            (second.op == LIR_Op::Call || second.op == LIR_Op::CallVoid)) {

            if (first.func_name == second.func_name && !first.func_name.empty()) {
                func_.instructions.erase(func_.instructions.begin() + i + 1);
                changed = true;
                --i;
            }
        }
    }

    return changed;
}

} // namespace LIR
} // namespace LM
