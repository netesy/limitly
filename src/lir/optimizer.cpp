#include "optimizer.hh"
#include "functions.hh"
#include "backend/vm/vm_value.hh"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

namespace LM {
namespace LIR {

// ============================================================================
// Liveness Analysis for Dead Code Elimination
// ============================================================================

class LivenessAnalyzer {
public:
    explicit LivenessAnalyzer(const std::vector<LIR_Inst>& instructions)
        : instructions_(instructions) {}

    // Compute which registers are live at each instruction
    std::vector<std::unordered_set<Reg>> analyze() {
        std::vector<std::unordered_set<Reg>> live_at(instructions_.size());
        
        if (instructions_.empty()) return live_at;

        // Build a map of labels to instruction indices
        std::unordered_map<uint32_t, size_t> label_to_idx;
        for (size_t i = 0; i < instructions_.size(); ++i) {
            if (instructions_[i].op == LIR_Op::Label) {
                label_to_idx[instructions_[i].imm] = i;
            }
        }

        // Backward pass: compute liveness from end to start
        std::unordered_set<Reg> live_regs;
        
        for (int i = static_cast<int>(instructions_.size()) - 1; i >= 0; --i) {
            const auto& inst = instructions_[i];
            
            // Add uses to live set (before this instruction)
            if (inst.a != UINT32_MAX) live_regs.insert(inst.a);
            if (inst.b != UINT32_MAX) live_regs.insert(inst.b);
            for (Reg arg : inst.call_args) {
                if (arg != UINT32_MAX) live_regs.insert(arg);
            }
            
            // For return statements, the destination register is also live
            if ((inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret) && inst.dst != UINT32_MAX) {
                live_regs.insert(inst.dst);
            }
            
            // For conditional jumps, we need to consider both paths
            if (inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
                // The condition register is used
                if (inst.dst != UINT32_MAX) live_regs.insert(inst.dst);
            }
            
            // Store live set at this point
            live_at[i] = live_regs;
            
            // Remove destination from live set (it's being defined here)
            // EXCEPT for return statements where dst is the return value
            // EXCEPT for jumps where dst is the condition
            if (inst.dst != UINT32_MAX && 
                inst.op != LIR_Op::Return && inst.op != LIR_Op::Ret &&
                inst.op != LIR_Op::Jump && inst.op != LIR_Op::JumpIf && inst.op != LIR_Op::JumpIfFalse) {
                live_regs.erase(inst.dst);
            }
        }
        
        return live_at;
    }

private:
    const std::vector<LIR_Inst>& instructions_;
};

bool Optimizer::optimize() {
    bool changed = false;
    bool pass_changed;
    int pass_count = 0;
    do {
        pass_changed = false;
        bool ur = remove_unreachable_code();
        bool cf = constant_folding();
        bool po = peephole_optimize();
        bool rm = redundant_memory_elimination();
        bool dce = dead_code_elimination();
        bool rc = remove_redundant_entry_calls();

        bool fi = function_inlining();
        bool gvn = global_value_numbering();
        bool gch = generational_check_hoisting();
        bool pol = prune_orphaned_labels();
        bool tco = tail_call_optimization();
        bool licm = loop_invariant_code_motion();

        pass_changed |= ur;
        pass_changed |= cf;
        pass_changed |= po;
        pass_changed |= rm;
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
    return changed;
}

bool Optimizer::dead_code_elimination() {
    if (func_.instructions.empty()) return false;

    bool changed = false;
    
    // Perform liveness analysis
    LivenessAnalyzer analyzer(func_.instructions);
    auto live_at = analyzer.analyze();

    // Mark instructions to remove (backward pass)
    std::vector<bool> to_remove(func_.instructions.size(), false);
    
    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        const auto& inst = func_.instructions[i];
        
        // Check if instruction has side effects
        bool has_side_effects = has_instruction_side_effects(inst);
        
        // Check if destination is live after this instruction
        bool dst_is_live = false;
        if (inst.dst != UINT32_MAX && i + 1 < live_at.size()) {
            dst_is_live = live_at[i + 1].count(inst.dst) > 0;
        }
        
        // Keep instruction if it has side effects or destination is live
        if (!has_side_effects && !dst_is_live && inst.dst != UINT32_MAX) {
            // Dead instruction - mark for removal
            to_remove[i] = true;
            changed = true;
        }
    }

    // Remove marked instructions in reverse order
    for (int i = static_cast<int>(func_.instructions.size()) - 1; i >= 0; --i) {
        if (to_remove[i]) {
            func_.instructions.erase(func_.instructions.begin() + i);
        }
    }

    return changed;
}

bool Optimizer::remove_unreachable_code() {
    if (func_.instructions.empty()) return false;

    const size_t n = func_.instructions.size();
    std::vector<bool> reachable(n, false);
    std::queue<size_t> worklist;

    auto push_if_valid = [&](size_t idx) {
        if (idx < n && !reachable[idx]) {
            reachable[idx] = true;
            worklist.push(idx);
        }
    };

    // Entry point
    push_if_valid(0);

    // Graph traversal over instruction indices (CFG-aware over jump targets,
    // with linear fallthrough when control continues).
    while (!worklist.empty()) {
        size_t i = worklist.front();
        worklist.pop();
        const auto& inst = func_.instructions[i];

        switch (inst.op) {
            case LIR_Op::Jump: {
                push_if_valid(static_cast<size_t>(inst.imm));
                break;
            }
            case LIR_Op::JumpIf:
            case LIR_Op::JumpIfFalse: {
                push_if_valid(static_cast<size_t>(inst.imm));
                if (i + 1 < n) push_if_valid(i + 1);  // fallthrough
                break;
            }
            case LIR_Op::Return:
            case LIR_Op::Ret: {
                // terminal
                break;
            }
            default: {
                if (i + 1 < n) push_if_valid(i + 1);  // linear reachability
                break;
            }
        }
    }

    bool changed = false;
    std::vector<LIR_Inst> compacted;
    compacted.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        if (reachable[i]) {
            compacted.push_back(func_.instructions[i]);
        } else {
            changed = true;
        }
    }

    if (changed) {
        // Build old->new index map so jump targets remain valid after compaction.
        std::vector<size_t> remap(n, static_cast<size_t>(-1));
        size_t next = 0;
        for (size_t i = 0; i < n; ++i) {
            if (reachable[i]) remap[i] = next++;
        }

        for (auto& inst : compacted) {
            if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
                size_t old_target = static_cast<size_t>(inst.imm);
                if (old_target < n && remap[old_target] != static_cast<size_t>(-1)) {
                    inst.imm = static_cast<int64_t>(remap[old_target]);
                }
            }
        }

        func_.instructions = std::move(compacted);
    }

    return changed;
}

bool Optimizer::dead_code_elimination_simple() {
    if (func_.instructions.empty()) return false;

    bool changed = false;
    bool pass_changed = true;
    int iterations = 0;
    
    // Iteratively remove dead code until no more changes
    while (pass_changed && iterations < 10) {
        iterations++;
        pass_changed = false;
        
        // Backward pass: compute which registers are live at each point
        std::unordered_set<Reg> live_regs;
        
        // Start from the end and work backwards
        for (int i = static_cast<int>(func_.instructions.size()) - 1; i >= 0; --i) {
            const auto& inst = func_.instructions[i];
            
            // Check if this instruction has side effects
            bool has_side_effects = has_instruction_side_effects(inst);
            
            // If destination is live or has side effects, keep it
            if (has_side_effects || (inst.dst != UINT32_MAX && live_regs.count(inst.dst))) {
                // Add operands to live set
                if (inst.a != UINT32_MAX) live_regs.insert(inst.a);
                if (inst.b != UINT32_MAX) live_regs.insert(inst.b);
                
                // Add call arguments
                for (Reg arg : inst.call_args) {
                    if (arg != UINT32_MAX) live_regs.insert(arg);
                }
            } else if (inst.dst != UINT32_MAX) {
                // This instruction is dead - remove it
                func_.instructions.erase(func_.instructions.begin() + i);
                pass_changed = true;
                changed = true;
                continue;
            }
            
            // Remove destination from live set (it's being defined here)
            if (inst.dst != UINT32_MAX) {
                live_regs.erase(inst.dst);
            }
        }
    }
    
    return changed;
}

bool Optimizer::redundant_memory_elimination() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    // Track memory state for pointers: address_reg -> stored_value_reg / loaded_dest_reg
    // Invalidated on labels, calls, stores to unknown memory, etc.
    std::unordered_map<Reg, Reg> active_memory_stores;

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        auto& inst = func_.instructions[i];

        // Invalidate on control flow or calls
        if (inst.op == LIR_Op::Label || inst.op == LIR_Op::Jump ||
            inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse ||
            inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid ||
            inst.op == LIR_Op::CallIndirect || inst.op == LIR_Op::CallBuiltin) {
            active_memory_stores.clear();
            continue;
        }

        // Redundant Store: Store ptr, val; Store ptr, val -> remove second store
        if (inst.op == LIR_Op::MemoryStore || inst.op == LIR_Op::Store) {
            Reg ptr_reg = inst.a;
            Reg val_reg = inst.b;
            auto it = active_memory_stores.find(ptr_reg);
            if (it != active_memory_stores.end() && it->second == val_reg) {
                // Redundant store of same value to same address
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            } else {
                active_memory_stores[ptr_reg] = val_reg;
            }
        }

        // Redundant Load: Store ptr, val; Load dst, ptr -> Mov dst, val
        if (inst.op == LIR_Op::MemoryLoad || inst.op == LIR_Op::Load) {
            Reg ptr_reg = inst.a;
            auto it = active_memory_stores.find(ptr_reg);
            if (it != active_memory_stores.end()) {
                Reg stored_val = it->second;
                inst.op = LIR_Op::Mov;
                inst.a = stored_val;
                inst.b = UINT32_MAX;
                changed = true;
                // Invalidate if destination register is modified by this load
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

        // Invalidate any active store mappings if dst is overwritten
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
    return (
        inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid ||
        inst.op == LIR_Op::CallIndirect || inst.op == LIR_Op::CallBuiltin ||
        inst.op == LIR_Op::CallVariadic ||
        inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret ||
        inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || 
        inst.op == LIR_Op::JumpIfFalse ||
        inst.op == LIR_Op::Label || inst.op == LIR_Op::Store ||
        inst.op == LIR_Op::ChannelSend || inst.op == LIR_Op::ChannelRecv ||
        inst.op == LIR_Op::ChannelClose || inst.op == LIR_Op::Await ||
        inst.op == LIR_Op::AsyncCall
    );
}

bool Optimizer::peephole_optimize() {
    bool changed = false;
    
    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        auto& inst = func_.instructions[i];

        // 1. Remove redundant moves: mov rX, rX
        if (inst.op == LIR_Op::Mov && inst.dst == inst.a) {
            func_.instructions.erase(func_.instructions.begin() + i);
            --i;
            changed = true;
            continue;
        }

        // 2. Eliminate double moves: mov rX, rY; mov rZ, rX -> mov rZ, rY
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

        // 3. Eliminate redundant loads: load_const rX, C; load_const rX, C -> load_const rX, C
        if (inst.op == LIR_Op::LoadConst && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::LoadConst && next.dst == inst.dst && 
                next.const_val == inst.const_val) {
                func_.instructions.erase(func_.instructions.begin() + i + 1);
                changed = true;
                continue;
            }
        }

        // 4. Strength reduction: add rX, rY, 0 -> mov rX, rY
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

        // 5. Strength reduction: mul rX, rY, 0 -> load_const rX, 0
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

        // 6. Strength reduction: mul rX, rY, 1 -> mov rX, rY
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

        // 7. Strength reduction: mul rX, rY, 2^n -> shl rX, rY, n
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
                        // Power of two > 2: rewrite mul rX, rY, 2^n -> shl rX, rY, n
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

        // 8. Eliminate redundant comparisons: cmpeq rX, rY, rY -> load_const rX, true
        if ((inst.op == LIR_Op::CmpEQ || inst.op == LIR_Op::CmpLE || inst.op == LIR_Op::CmpGE) && 
            inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            inst.const_val = VAL_TRUE;
            changed = true;
            continue;
        }

        // 9. Eliminate redundant comparisons: cmpne rX, rY, rY -> load_const rX, false
        if ((inst.op == LIR_Op::CmpNEQ || inst.op == LIR_Op::CmpLT || inst.op == LIR_Op::CmpGT) && 
            inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            inst.const_val = VAL_FALSE;
            changed = true;
            continue;
        }

        // 10. Eliminate redundant boolean operations: and rX, rY, rY -> mov rX, rY
        if (inst.op == LIR_Op::And && inst.a == inst.b) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
            continue;
        }

        // 11. Eliminate redundant boolean operations: or rX, rY, rY -> mov rX, rY
        if (inst.op == LIR_Op::Or && inst.a == inst.b) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
            continue;
        }

        // 12. Eliminate redundant boolean operations: xor rX, rY, rY -> load_const rX, false
        if (inst.op == LIR_Op::Xor && inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            inst.const_val = VAL_FALSE;
            changed = true;
            continue;
        }

        // 13. Eliminate redundant negation: neg rX, rY; neg rZ, rX -> mov rZ, rY
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

        // 14. Eliminate unused jumps: jump L; L: -> remove jump
        if (inst.op == LIR_Op::Jump && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Label && next.imm == inst.imm) {
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            }
        }

        // 15. Combine consecutive loads into single load
        if (inst.op == LIR_Op::LoadConst && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Mov && next.a == inst.dst) {
                inst.dst = next.dst;
                func_.instructions.erase(func_.instructions.begin() + i + 1);
                changed = true;
                continue;
            }
        }

        // 16. Eliminate mov before return: mov rX, rY; return rX -> return rY
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

        // 17. Eliminate sub rX, rY, 0 -> mov rX, rY
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

        // 18. Eliminate div rX, rY, 1 -> mov rX, rY
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

        // 19. Eliminate mod rX, rY, 1 -> load_const rX, 0
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
    std::unordered_map<Reg, Backend::Value> const_regs;

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        auto& inst = func_.instructions[i];

        if (inst.op == LIR_Op::LoadConst) {
            const_regs[inst.dst] = inst.const_val;
            continue;
        }

        if (inst.op == LIR_Op::Mov) {
            if (const_regs.count(inst.a)) {
                const_regs[inst.dst] = const_regs[inst.a];
            } else {
                const_regs.erase(inst.dst);
            }
            continue;
        }

        // Arithmetic folding
        if (inst.op == LIR_Op::Add || inst.op == LIR_Op::Sub || inst.op == LIR_Op::Mul || inst.op == LIR_Op::Div) {
            if (const_regs.count(inst.a) && const_regs.count(inst.b)) {
                Backend::Value va = const_regs[inst.a];
                Backend::Value vb = const_regs[inst.b];

                if (IS_INT(va) && IS_INT(vb)) {
                    int64_t a = UNBOX_INT(va);
                    int64_t b = UNBOX_INT(vb);
                    int64_t res = 0;

                    if (inst.op == LIR_Op::Add) res = a + b;
                    else if (inst.op == LIR_Op::Sub) res = a - b;
                    else if (inst.op == LIR_Op::Mul) res = a * b;
                    else if (inst.op == LIR_Op::Div && b != 0) res = a / b;
                    else continue;

                    Backend::Value res_val = make_i64(res);
                    inst.op = LIR_Op::LoadConst;
                    inst.const_val = res_val;
                    const_regs[inst.dst] = res_val;
                    changed = true;
                }
            } else {
                if (inst.dst != UINT32_MAX) const_regs.erase(inst.dst);
            }
        } else if (inst.dst != UINT32_MAX) {
            const_regs.erase(inst.dst);
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
            // Candidate check: small leaf function (under 12 instructions, no internal calls/jumps)
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

            // Reserve registers in caller function for inlined frame
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

            // Map parameters
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

            // Replace call instruction with inlined instructions
            func_.instructions.erase(func_.instructions.begin() + i);
            func_.instructions.insert(func_.instructions.begin() + i, inlined_insts.begin(), inlined_insts.end());
            changed = true;
            break;
        }
    }

    return changed;
}

bool Optimizer::global_value_numbering() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

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

    std::unordered_map<ExprKey, Reg, ExprKeyHash> value_table;

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        auto& inst = func_.instructions[i];

        // Invalidate table on labels and calls/jumps (basic block boundary)
        if (inst.op == LIR_Op::Label || inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid ||
            inst.op == LIR_Op::CallIndirect || inst.op == LIR_Op::CallBuiltin ||
            inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
            value_table.clear();
            continue;
        }

        // Invalidate any table entries where an operand or dst register is overwritten
        auto invalidate_reg = [&](Reg r) {
            if (r == UINT32_MAX) return;
            for (auto it = value_table.begin(); it != value_table.end(); ) {
                if (it->first.a == r || it->first.b == r || it->second == r) {
                    it = value_table.erase(it);
                } else {
                    ++it;
                }
            }
        };

        // If this instruction modifies inst.dst or operands, invalidate past table entries using them
        if (inst.dst != UINT32_MAX) {
            invalidate_reg(inst.dst);
        }

        // Pure side-effect-free arithmetic/bitwise/comparison instructions
        if (inst.op == LIR_Op::Add || inst.op == LIR_Op::Sub || inst.op == LIR_Op::Mul ||
            inst.op == LIR_Op::Div || inst.op == LIR_Op::And || inst.op == LIR_Op::Or ||
            inst.op == LIR_Op::Xor || inst.op == LIR_Op::Shl || inst.op == LIR_Op::Shr ||
            inst.op == LIR_Op::CmpEQ || inst.op == LIR_Op::CmpNEQ || inst.op == LIR_Op::CmpLT ||
            inst.op == LIR_Op::CmpLE || inst.op == LIR_Op::CmpGT || inst.op == LIR_Op::CmpGE) {

            ExprKey key{inst.op, inst.a, inst.b};
            auto it = value_table.find(key);
            if (it != value_table.end()) {
                // Duplicate expression found! Replace instruction with Mov from existing result
                Reg existing_dst = it->second;
                inst.op = LIR_Op::Mov;
                inst.a = existing_dst;
                inst.b = UINT32_MAX;
                changed = true;
            } else if (inst.dst != UINT32_MAX && inst.dst != inst.a && inst.dst != inst.b) {
                value_table[key] = inst.dst;
            }
        }
    }

    return changed;
}

bool Optimizer::generational_check_hoisting() {
    if (func_.instructions.empty()) return false;
    bool changed = false;

    // Eliminate consecutive matching RegionEnter / RegionExit instruction pairs with no intervening side effects
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

    // Preserve the first label if it serves as the function entry label
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

    // Entry label is the first label defined in the function
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

            // Convert tail call into parameter moves via temporary registers to avoid clobbering
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

    std::unordered_map<uint32_t, size_t> label_pos;
    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        if (func_.instructions[i].op == LIR_Op::Label) {
            label_pos[static_cast<uint32_t>(func_.instructions[i].imm)] = i;
        }
    }

    for (size_t i = 0; i < func_.instructions.size(); ++i) {
        const auto& inst = func_.instructions[i];
        if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
            uint32_t target_label = static_cast<uint32_t>(inst.imm);
            auto it = label_pos.find(target_label);
            if (it != label_pos.end() && it->second < i) {
                size_t header_idx = it->second;
                size_t backedge_idx = i;

                // Track definitions count for registers modified within loop
                std::unordered_map<Reg, size_t> loop_reg_defs;
                for (size_t k = header_idx; k <= backedge_idx; ++k) {
                    if (func_.instructions[k].dst != UINT32_MAX) {
                        loop_reg_defs[func_.instructions[k].dst]++;
                    }
                }

                for (size_t k = header_idx + 1; k < backedge_idx; ++k) {
                    const auto& cand = func_.instructions[k];
                    if (has_instruction_side_effects(cand) || cand.dst == UINT32_MAX) continue;

                    bool a_invariant = (cand.a == UINT32_MAX || loop_reg_defs.count(cand.a) == 0);
                    bool b_invariant = (cand.b == UINT32_MAX || loop_reg_defs.count(cand.b) == 0);
                    bool dst_single_def = (loop_reg_defs[cand.dst] == 1);

                    if (a_invariant && b_invariant && dst_single_def) {
                        LIR_Inst hoisted = cand;
                        func_.instructions.erase(func_.instructions.begin() + k);
                        func_.instructions.insert(func_.instructions.begin() + header_idx, hoisted);
                        changed = true;
                        break;
                    }
                }
                if (changed) break;
            }
        }
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
