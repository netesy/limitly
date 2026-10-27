#include "optimizer.hh"
#include "verifier.hh"
#include <stdexcept>
#include "../memory/lir_analysis.hh"
#include "../memory/region_analysis.hh"
#include "algebraic_simplifier.hh"
#include "functions.hh"
#include "analysis.hh"
#include "backend/vm/vm_value.hh"
#include "backend/vm/vm_string.hh"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

namespace LM {
namespace LIR {

bool Optimizer::optimize() {
    auto reindex_labels = [](LIR_Function& func) {
        std::unordered_map<Imm, Imm> label_remap;
        for (size_t i = 0; i < func.instructions.size(); ++i) {
            auto& inst = func.instructions[i];
            if (inst.op == LIR_Op::Label) {
                label_remap[inst.imm] = static_cast<Imm>(i);
                inst.imm = static_cast<Imm>(i);
            }
        }
        for (auto& inst : func.instructions) {
            if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
                auto it = label_remap.find(inst.imm);
                if (it != label_remap.end()) {
                    inst.imm = it->second;
                }
            }
        }
    };

    auto verify_memory_contract = [&]() {
        reindex_labels(func_);
        std::vector<std::string> errors;
        if (!Verifier::verify_memory_regions(func_, errors) || !Verifier::verify_ownership(func_, errors)) {
            std::string diagnostic = "Invalid canonical memory contract during optimization of " + func_.name;
            for (const auto& error : errors) diagnostic += "\n" + error;
            throw std::runtime_error(diagnostic);
        }
    };
    verify_memory_contract();
    bool changed = false;
    bool pass_changed;
    int pass_count = 0;

    report_ = OptimizationReport{};
    report_.function_name = func_.name;
    report_.initial_instructions = func_.instructions.size();
    report_.initial_blocks = MetricsCollector::count_blocks(func_);
    report_.initial_memory_ops = MetricsCollector::count_memory_ops(func_);
    report_.initial_loads = MetricsCollector::count_loads(func_);
    report_.initial_stores = MetricsCollector::count_stores(func_);

    AnalysisManager am(func_);

    auto run_pass = [&](const std::string& name, auto pass_fn) -> bool {
        PassRecord rec;
        rec.pass_name = name;
        rec.instructions_before = func_.instructions.size();
        rec.memory_ops_before = MetricsCollector::count_memory_ops(func_);
        rec.loads_before = MetricsCollector::count_loads(func_);
        rec.stores_before = MetricsCollector::count_stores(func_);
        rec.blocks_before = MetricsCollector::count_blocks(func_);

        bool res = pass_fn();
        if (res) verify_memory_contract();

        rec.instructions_after = func_.instructions.size();
        rec.memory_ops_after = MetricsCollector::count_memory_ops(func_);
        rec.loads_after = MetricsCollector::count_loads(func_);
        rec.stores_after = MetricsCollector::count_stores(func_);
        rec.blocks_after = MetricsCollector::count_blocks(func_);

        rec.instruction_delta = static_cast<int>(rec.instructions_after) - static_cast<int>(rec.instructions_before);
        rec.memory_delta = static_cast<int>(rec.memory_ops_after) - static_cast<int>(rec.memory_ops_before);
        rec.loads_delta = static_cast<int>(rec.loads_after) - static_cast<int>(rec.loads_before);
        rec.stores_delta = static_cast<int>(rec.stores_after) - static_cast<int>(rec.stores_before);
        rec.blocks_delta = static_cast<int>(rec.blocks_after) - static_cast<int>(rec.blocks_before);

        if (res || rec.instruction_delta != 0 || rec.memory_delta != 0 || rec.blocks_delta != 0) {
            report_.passes.push_back(rec);
        }
        return res;
    };

    do {
        bool promotions = run_pass("Proven scalar promotions", [&]() {
            std::vector<std::string> errors;
            if (!Verifier::verify(func_, errors)) return false;
            return Memory::eliminate_proven_scalar_promotions(func_);
        });
        if (promotions) am.invalidate_all();
        bool regions = run_pass("Proven scalar leaf regions", [&]() {
            std::vector<std::string> errors;
            if (!Verifier::verify(func_, errors)) return false;
            return Memory::eliminate_scalar_leaf_regions(func_);
        });
        if (regions) am.invalidate_all();
        pass_changed = Memory::eliminate_proven_local_borrows(func_);
        pass_changed |= regions || promotions;
        if (pass_changed) am.invalidate_all();

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

        bool alg_simp = run_pass("Algebraic simplification", [&]() { return algebraic_simplification(); });
        if (alg_simp) am.invalidate_all();

        bool rlr = run_pass("Remove loop region ops", [&]() { return remove_loop_region_ops(); });
        if (rlr) am.invalidate_all();

        bool lu = run_pass("Loop unrolling", [&]() { return loop_unroll(); });
        if (lu) am.invalidate_all();

        pass_changed |= ur;
        pass_changed |= rlr;
        pass_changed |= lu;
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
        pass_changed |= alg_simp;
        pass_changed |= rlr;

        changed |= pass_changed;
        pass_count++;
    } while (pass_changed && pass_count < 10);

    report_.final_instructions = func_.instructions.size();
    report_.final_blocks = MetricsCollector::count_blocks(func_);
    report_.final_memory_ops = MetricsCollector::count_memory_ops(func_);
    report_.final_loads = MetricsCollector::count_loads(func_);
    report_.final_stores = MetricsCollector::count_stores(func_);

    if (std::getenv("LYMAR_PRINT_OPT_REPORT")) {
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
    // Quarantined: pointer-register equality does not establish non-aliasing.
    // Keep the implementation below for the subsequent optimization gate.
    return false;
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

        // Chained string concatenation peephole optimization:
        // STR_CONCAT dst, a, b where a is an empty string
        if (inst.op == LIR_Op::STR_CONCAT && inst.a != UINT32_MAX && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.a && IS_PTR(prev.const_val) && UNBOX_PTR(prev.const_val)) {
                    auto* lm_str = reinterpret_cast<LmStringHeader*>(UNBOX_PTR(prev.const_val));
                    if (lm_str && lm_str->len == 0) {
                        inst.op = LIR_Op::Mov;
                        inst.a = inst.b;
                        inst.b = UINT32_MAX;
                        changed = true;
                        continue;
                    }
                }
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

bool Optimizer::loop_unroll() {
    // Simple loop unrolling for tight integer loops (4x unroll)
    // Detect pattern: LoadConst(counter), CmpLT(counter, limit), JumpIfFalse, body, Add(counter, 1), Jump(header)
    bool changed = false;

    for (size_t i = 0; i < func_.instructions.size(); ) {
        // Look for loop header: comparison with constant limit
        if (i + 3 >= func_.instructions.size()) {
            i++;
            continue;
        }

        auto& cmp_inst = func_.instructions[i];
        if (cmp_inst.op != LIR_Op::CmpLT) {
            i++;
            continue;
        }

        auto& jf_inst = func_.instructions[i + 1];
        if (jf_inst.op != LIR_Op::JumpIfFalse) {
            i++;
            continue;
        }

        // Find the loop body and increment
        size_t body_start = i + 2;
        size_t increment_pos = UINT32_MAX;
        size_t jump_back_pos = UINT32_MAX;
        bool has_region_ops = false;

        // Scan forward to find increment and jump back
        for (size_t j = body_start; j < func_.instructions.size(); j++) {
            // Check for region operations (prevent unrolling if present)
            if (func_.instructions[j].op == LIR_Op::RegionEnter ||
                func_.instructions[j].op == LIR_Op::RegionExit ||
                func_.instructions[j].op == LIR_Op::RegionMove) {
                has_region_ops = true;
            }
            if (func_.instructions[j].op == LIR_Op::Add &&
                func_.instructions[j].a == cmp_inst.a &&
                func_.instructions[j].b != UINT32_MAX) {
                // Check if adding 1
                auto& prev = func_.instructions[j - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == func_.instructions[j].b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 1) {
                    increment_pos = j;
                }
            }
            if (func_.instructions[j].op == LIR_Op::Jump &&
                func_.instructions[j].imm == static_cast<Imm>(i)) {
                jump_back_pos = j;
                break;
            }
        }

        if (increment_pos == UINT32_MAX || jump_back_pos == UINT32_MAX) {
            i++;
            continue;
        }

        // Skip unrolling if loop has region operations (complex ownership semantics)
        if (has_region_ops) {
            i = jump_back_pos + 1;
            continue;
        }

        // Check if loop body is small enough to unroll (max 10 instructions for tight loops)
        size_t body_size = increment_pos - body_start;
        if (body_size > 10 || body_size < 2) {
            i = jump_back_pos + 1;
            continue;
        }

        // Unroll 4x: duplicate body 4 times and adjust increment
        // Extract body instructions
        std::vector<LIR_Inst> body_body;
        for (size_t j = body_start; j < increment_pos; j++) {
            body_body.push_back(func_.instructions[j]);
        }

        // Create new instructions: duplicate body 4 times
        std::vector<LIR_Inst> new_instructions;
        
        // Add 4 copies of the body
        for (int unroll = 0; unroll < 4; unroll++) {
            for (const auto& inst : body_body) {
                new_instructions.push_back(inst);
            }
        }

        // Replace increment: change +1 to +4
        auto& increment_inst = func_.instructions[increment_pos];
        auto& const_inst = func_.instructions[increment_pos - 1];
        const_inst.const_val = make_i64(4);

        // Replace old body with unrolled version
        func_.instructions.erase(func_.instructions.begin() + body_start, 
                                    func_.instructions.begin() + increment_pos);
        func_.instructions.insert(func_.instructions.begin() + body_start, 
                                 new_instructions.begin(), new_instructions.end());

        // Reindex labels
        std::unordered_map<Imm, Imm> label_remap;
        for (size_t j = 0; j < func_.instructions.size(); ++j) {
            auto& inst = func_.instructions[j];
            if (inst.op == LIR_Op::Label) {
                label_remap[inst.imm] = static_cast<Imm>(j);
                inst.imm = static_cast<Imm>(j);
            }
        }
        for (auto& inst : func_.instructions) {
            if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
                auto it = label_remap.find(inst.imm);
                if (it != label_remap.end()) {
                    inst.imm = it->second;
                }
            }
        }

        changed = true;
        i = increment_pos + 1;
    }

    return changed;
}

bool Optimizer::remove_loop_region_ops() {
    // Remove unnecessary region operations from tight scalar loops
    // A loop is "scalar" if it only uses local registers and no pointers/objects
    bool changed = false;

    // Always remove Nop instructions with ownership comments - they're metadata
    for (size_t i = 0; i < func_.instructions.size(); ) {
        if (func_.instructions[i].op == LIR_Op::Nop) {
            func_.instructions.erase(func_.instructions.begin() + i);
            changed = true;
        } else {
            i++;
        }
    }

    for (size_t i = 0; i < func_.instructions.size(); ) {
        // Find RegionEnter
        if (func_.instructions[i].op != LIR_Op::RegionEnter) {
            i++;
            continue;
        }

        size_t region_start = i;
        size_t region_end = UINT32_MAX;
        uint32_t region_id = func_.instructions[i].imm;

        // Find matching RegionExit
        for (size_t j = i + 1; j < func_.instructions.size(); j++) {
            if (func_.instructions[j].op == LIR_Op::RegionExit && func_.instructions[j].imm == region_id) {
                region_end = j;
                break;
            }
        }

        if (region_end == UINT32_MAX) {
            i++;
            continue;
        }

        // Check if region contains only scalar operations (no memory ops, no calls, no pointer ops)
        bool has_non_scalar = false;
        for (size_t j = region_start + 1; j < region_end; j++) {
            auto& inst = func_.instructions[j];
            if (inst.op == LIR_Op::RegionEnter || inst.op == LIR_Op::RegionExit ||
                inst.op == LIR_Op::RegionMove) {
                continue; // Nested regions
            }
            // Check for non-scalar operations
            if (inst.op == LIR_Op::Call || inst.op == LIR_Op::CallIndirect ||
                inst.op == LIR_Op::MemoryLoad || inst.op == LIR_Op::MemoryStore ||
                inst.op == LIR_Op::MemoryAlloc || inst.op == LIR_Op::MemoryFree ||
                inst.op == LIR_Op::ListCreate || inst.op == LIR_Op::ListIndex ||
                inst.op == LIR_Op::ListSet || inst.op == LIR_Op::ListAppend ||
                inst.op == LIR_Op::DictCreate || inst.op == LIR_Op::DictGet ||
                inst.op == LIR_Op::DictSet || inst.op == LIR_Op::STR_CONCAT ||
                inst.op == LIR_Op::STR_FORMAT || inst.op == LIR_Op::StringIndex) {
                has_non_scalar = true;
                break;
            }
        }

        if (has_non_scalar) {
            i = region_end + 1;
            continue;
        }

        // Remove scalar region operations (RegionEnter, RegionExit, RegionMove, Nop ownership)
        size_t j = region_start;
        while (j <= region_end && j < func_.instructions.size()) {
            auto& inst = func_.instructions[j];
            if (inst.op == LIR_Op::RegionEnter || inst.op == LIR_Op::RegionExit ||
                inst.op == LIR_Op::RegionMove || inst.op == LIR_Op::Nop) {
                func_.instructions.erase(func_.instructions.begin() + j);
                changed = true;
                // Don't increment j, we're removing
            } else {
                j++;
            }
        }

        i = j;
    }

    return changed;
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

        // Convert unchecked ops back to regular ops if types aren't provably int
        // This is a safety fallback - unchecked ops should only be used when we're certain
        if (inst.op == LIR_Op::IAdd_Unchecked || inst.op == LIR_Op::IXor_Unchecked ||
            inst.op == LIR_Op::IAnd_Unchecked || inst.op == LIR_Op::IOr_Unchecked) {
            // For now, keep them as-is since the generator only emits them for provable ints
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

                        if (inst.op == LIR_Op::Add) valid = !__builtin_add_overflow(a, b, &res);
                        else if (inst.op == LIR_Op::Sub) valid = !__builtin_sub_overflow(a, b, &res);
                        else if (inst.op == LIR_Op::Mul) valid = !__builtin_mul_overflow(a, b, &res);
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
    // Quarantined: invariant addresses do not imply invariant memory contents.
    return false;
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

bool Optimizer::algebraic_simplification() {
    if (func_.instructions.empty()) return false;
    AlgebraicSimplifier simplifier;
    return simplifier.optimize_function(func_);
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

            // Only module initialization is idempotent. Repeated ordinary calls
            // (including print and side-effecting functions) must both execute.
            if (first.func_name == second.func_name && first.func_name.ends_with(".__init__")) {
                const size_t removed = i + 1;
                func_.instructions.erase(func_.instructions.begin() + i + 1);
                // Linearized branches contain instruction indices, not labels.
                for (auto& instruction : func_.instructions) {
                    if ((instruction.op == LIR_Op::Jump || instruction.op == LIR_Op::JumpIf ||
                         instruction.op == LIR_Op::JumpIfFalse || instruction.op == LIR_Op::Label) && instruction.imm > removed) {
                        --instruction.imm;
                    }
                }
                changed = true;
                --i;
            }
        }
    }

    return changed;
}

} // namespace LIR
} // namespace LM
