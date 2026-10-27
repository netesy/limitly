#include "../register.hh"
#include "../vm_value.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_bitwise(const LIR::LIR_Inst* pc) {
    // The unchecked opcodes resolve to the same implementation as the checked ones.
    // "Unchecked" means the trap checks were proven unnecessary, never that the
    // operand is guaranteed to fit a 61-bit SMI immediate, so results go through
    // make_i64() and heap-promote when they no longer fit. Shifts use an unsigned
    // left operand to stay defined behaviour, and a shift count outside [0,64) yields
    // zero, matching the immediate fast path in register.cpp.
    switch (pc->op) {
        case LIR::LIR_Op::And:
        case LIR::LIR_Op::IAnd_Unchecked:
            registers[pc->dst] = make_i64(to_int(registers[pc->a]) & to_int(registers[pc->b]));
            break;
        case LIR::LIR_Op::Or:
        case LIR::LIR_Op::IOr_Unchecked:
            registers[pc->dst] = make_i64(to_int(registers[pc->a]) | to_int(registers[pc->b]));
            break;
        case LIR::LIR_Op::Xor:
        case LIR::LIR_Op::IXor_Unchecked:
            registers[pc->dst] = make_i64(to_int(registers[pc->a]) ^ to_int(registers[pc->b]));
            break;
        case LIR::LIR_Op::Shl:
        case LIR::LIR_Op::Shr: {
            int64_t value = to_int(registers[pc->a]);
            int64_t amount = to_int(registers[pc->b]);
            if (amount < 0 || amount >= 64) {
                registers[pc->dst] = make_i64(0);
            } else if (pc->op == LIR::LIR_Op::Shl) {
                registers[pc->dst] = make_i64(static_cast<int64_t>(
                    static_cast<uint64_t>(value) << amount));
            } else {
                registers[pc->dst] = make_i64(value >> amount);
            }
            break;
        }
        case LIR::LIR_Op::IAdd_Unchecked:
            // Addition belongs to the arithmetic dispatcher; route it there instead of
            // leaving the destination register holding a stale value.
            execute_arithmetic(pc);
            break;
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
