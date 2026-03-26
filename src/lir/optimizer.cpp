#include "optimizer.hh"
#include <unordered_set>
#include <algorithm>

namespace LM {
namespace LIR {

bool Optimizer::optimize() {
    bool changed = false;
    bool pass_changed;
    int pass_count = 0;
    do {
        pass_changed = false;
        bool cf = constant_folding();
        bool po = peephole_optimize();
        bool dce = dead_code_elimination();

        pass_changed |= cf;
        pass_changed |= po;
        pass_changed |= dce;

        if (pass_changed) {
        }
        changed |= pass_changed;
        pass_count++;
    } while (pass_changed && pass_count < 10);
    return changed;
}

bool Optimizer::dead_code_elimination() {
    if (func_.instructions.empty()) return false;

    std::unordered_set<Reg> used_regs;

    // Mark registers used in instructions
    for (const auto& inst : func_.instructions) {
        // Registers used as operands
        if (inst.op != LIR_Op::LoadConst && inst.op != LIR_Op::Label) {
            used_regs.insert(inst.a);
            if (inst.op != LIR_Op::Neg && inst.op != LIR_Op::Jump && inst.op != LIR_Op::Label) {
                used_regs.insert(inst.b);
            }
        }

        // Registers used in calls
        for (Reg arg : inst.call_args) {
            used_regs.insert(arg);
        }
    }

    size_t initial_size = func_.instructions.size();
    auto it = std::remove_if(func_.instructions.begin(), func_.instructions.end(), [&](const LIR_Inst& inst) {
        // Don't remove instructions with side effects
        if (inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid ||
            inst.op == LIR_Op::PrintInt || inst.op == LIR_Op::PrintString ||
            inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret ||
            inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse ||
            inst.op == LIR_Op::Label || inst.op == LIR_Op::Store ||
            inst.op == LIR_Op::FrameSetField || inst.op == LIR_Op::FrameCallInit ||
            inst.op == LIR_Op::FrameCallDeinit || inst.op == LIR_Op::FrameCallMethod) {
            return false;
        }

        // Remove if destination register is not used
        if (inst.dst != UINT32_MAX && used_regs.find(inst.dst) == used_regs.end()) {
            return true;
        }

        return false;
    });

    if (it != func_.instructions.end()) {
        func_.instructions.erase(it, func_.instructions.end());
        return true;
    }

    return false;
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

        // 2. Strength reduction: add rX, rY, 0 -> mov rX, rY
        // (Assuming 0 is an immediate or constant register)
    }
    return changed;
}

bool Optimizer::constant_folding() {
    if (func_.instructions.empty()) return false;

    bool changed = false;
    std::unordered_map<Reg, ValuePtr> const_regs;

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
                ValuePtr va = const_regs[inst.a];
                ValuePtr vb = const_regs[inst.b];

                // Only fold integers for now
                if (va && vb && va->type && vb->type &&
                    (va->type->tag == TypeTag::Int || va->type->tag == TypeTag::Int64) &&
                    (vb->type->tag == TypeTag::Int || vb->type->tag == TypeTag::Int64)) {
                    try {
                        int64_t a = std::stoll(va->data);
                        int64_t b = std::stoll(vb->data);
                        int64_t res = 0;

                        if (inst.op == LIR_Op::Add) res = a + b;
                        else if (inst.op == LIR_Op::Sub) res = a - b;
                        else if (inst.op == LIR_Op::Mul) res = a * b;
                        else if (inst.op == LIR_Op::Div && b != 0) res = a / b;
                        else continue;

                        ValuePtr res_val = std::make_shared<Value>(va->type, res);
                        inst.op = LIR_Op::LoadConst;
                        inst.const_val = res_val;
                        const_regs[inst.dst] = res_val;
                        changed = true;
                    } catch (...) {}
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
