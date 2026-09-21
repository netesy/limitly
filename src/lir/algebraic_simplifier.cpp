#include "algebraic_simplifier.hh"
#include <algorithm>

namespace LM {
namespace LIR {

bool AlgebraicSimplifier::is_pure_instruction(const LIR_Inst& inst) {
    switch (inst.op) {
        case LIR_Op::Add: case LIR_Op::Sub: case LIR_Op::Mul:
        case LIR_Op::And: case LIR_Op::Or: case LIR_Op::Xor: case LIR_Op::Shl: case LIR_Op::Shr:
        case LIR_Op::CmpEQ: case LIR_Op::CmpNEQ: case LIR_Op::CmpLT: case LIR_Op::CmpLE:
        case LIR_Op::CmpGT: case LIR_Op::CmpGE: case LIR_Op::Mov: case LIR_Op::LoadConst:
            return true;
        default:
            return false; // Div, Store, Load, Call, atomic, and concurrency ops are barriers
    }
}

bool AlgebraicSimplifier::optimize_function(LIR_Function& func) {
    bool changed = false;

    // Identify pure basic block sequences bounded by side-effect barriers
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        auto& inst = func.instructions[i];

        if (!is_pure_instruction(inst)) continue;

        // Algebraic simplification 1: Add reg, 0 -> Mov reg
        if (inst.op == LIR_Op::Add && inst.a != UINT32_MAX && inst.b == UINT32_MAX && inst.imm == 0) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
        }

        // Algebraic simplification 2: Mul reg, 1 -> Mov reg
        if (inst.op == LIR_Op::Mul && inst.a != UINT32_MAX && inst.b == UINT32_MAX && inst.imm == 1) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
        }

        // Algebraic simplification 3: Sub reg, 0 -> Mov reg
        if (inst.op == LIR_Op::Sub && inst.a != UINT32_MAX && inst.b == UINT32_MAX && inst.imm == 0) {
            inst.op = LIR_Op::Mov;
            inst.b = UINT32_MAX;
            changed = true;
        }
    }

    return changed;
}

} // namespace LIR
} // namespace LM
