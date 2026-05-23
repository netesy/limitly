#include "optimizer.hh"
#include "runtime/runtime_value.h"
#include <unordered_set>
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
        bool dce = dead_code_elimination();

        pass_changed |= ur;
        pass_changed |= cf;
        pass_changed |= po;
        pass_changed |= dce;

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
                if (inst.imm >= 0) {
                    push_if_valid(static_cast<size_t>(inst.imm));
                }
                break;
            }
            case LIR_Op::JumpIf:
            case LIR_Op::JumpIfFalse: {
                if (inst.imm >= 0) {
                    push_if_valid(static_cast<size_t>(inst.imm));
                }
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
            if ((inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) &&
                inst.imm >= 0) {
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

bool Optimizer::has_instruction_side_effects(const LIR_Inst& inst) const {
    return (
        inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid ||
        inst.op == LIR_Op::CallIndirect || inst.op == LIR_Op::CallBuiltin ||
        inst.op == LIR_Op::CallVariadic ||
        inst.op == LIR_Op::PrintInt || inst.op == LIR_Op::PrintUint ||
        inst.op == LIR_Op::PrintFloat || inst.op == LIR_Op::PrintBool ||
        inst.op == LIR_Op::PrintString ||
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
            // Check if b is a constant 0
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

        // 5. Strength reduction: mul rX, rY, 1 -> mov rX, rY
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

        // 6. Strength reduction: mul rX, rY, 2 -> add rX, rY, rY
        if (inst.op == LIR_Op::Mul && inst.b != UINT32_MAX) {
            if (i > 0) {
                auto& prev = func_.instructions[i - 1];
                if (prev.op == LIR_Op::LoadConst && prev.dst == inst.b &&
                    IS_INT(prev.const_val) && UNBOX_INT(prev.const_val) == 2) {
                    inst.op = LIR_Op::Add;
                    inst.b = inst.a;
                    changed = true;
                    continue;
                }
            }
        }

        // 7. Eliminate redundant comparisons: cmpeq rX, rY, rY -> load_const rX, true
        if ((inst.op == LIR_Op::CmpEQ || inst.op == LIR_Op::CmpLE || inst.op == LIR_Op::CmpGE) && 
            inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            // Create a true constant
            inst.const_val = VAL_TRUE;
            changed = true;
            continue;
        }

        // 8. Eliminate redundant comparisons: cmpne rX, rY, rY -> load_const rX, false
        if ((inst.op == LIR_Op::CmpNEQ || inst.op == LIR_Op::CmpLT || inst.op == LIR_Op::CmpGT) && 
            inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            // Create a false constant
            inst.const_val = VAL_FALSE;
            changed = true;
            continue;
        }

        // 9. Eliminate redundant boolean operations: and rX, rY, rY -> mov rX, rY
        if (inst.op == LIR_Op::And && inst.a == inst.b) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
            continue;
        }

        // 10. Eliminate redundant boolean operations: or rX, rY, rY -> mov rX, rY
        if (inst.op == LIR_Op::Or && inst.a == inst.b) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
            continue;
        }

        // 11. Eliminate redundant boolean operations: xor rX, rY, rY -> load_const rX, false
        if (inst.op == LIR_Op::Xor && inst.a != UINT32_MAX && inst.a == inst.b) {
            inst.op = LIR_Op::LoadConst;
            inst.a = UINT32_MAX;
            inst.b = UINT32_MAX;
            inst.const_val = VAL_FALSE;
            changed = true;
            continue;
        }

        // 12. Eliminate redundant negation: neg rX, rY; neg rZ, rX -> mov rZ, rY
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

        // 13. Eliminate unused jumps: jump L; L: -> remove jump
        if (inst.op == LIR_Op::Jump && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Label && next.imm == inst.imm) {
                func_.instructions.erase(func_.instructions.begin() + i);
                --i;
                changed = true;
                continue;
            }
        }

        // 14. Combine consecutive loads into single load
        if (inst.op == LIR_Op::LoadConst && i + 1 < func_.instructions.size()) {
            auto& next = func_.instructions[i + 1];
            if (next.op == LIR_Op::Mov && next.a == inst.dst) {
                // Replace next mov with direct load to its destination
                inst.dst = next.dst;
                func_.instructions.erase(func_.instructions.begin() + i + 1);
                changed = true;
                continue;
            }
        }

        // 15. Eliminate mov before return: mov rX, rY; return rX -> return rY
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

        // 16. Eliminate sub rX, rY, 0 -> mov rX, rY
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

        // 17. Eliminate div rX, rY, 1 -> mov rX, rY
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

        // 18. Eliminate mod rX, rY, 1 -> load_const rX, 0
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

                // Only fold integers for now
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

} // namespace LIR
} // namespace LM
