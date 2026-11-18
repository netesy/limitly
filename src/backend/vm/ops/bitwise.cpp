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
    //
    // i128/u128 operands carry boxed 128-bit values; the 64-bit path below would
    // silently truncate them. Detect them through the register language types and
    // run the operation at 128-bit width instead.
    auto wide_kind = [&](LIR::Reg r) -> int {
        TypePtr t = get_register_language_type(r);
        if (!t) return 0;
        if (t->tag == TypeTag::Int128) return 1;
        if (t->tag == TypeTag::UInt128) return 2;
        return 0;
    };
    int wide_a = wide_kind(pc->a), wide_b = wide_kind(pc->b);
    if (wide_a || wide_b || wide_kind(pc->dst)) {
        bool uns = (wide_a == 2 || wide_b == 2 || wide_kind(pc->dst) == 2);
        switch (pc->op) {
            case LIR::LIR_Op::And:
            case LIR::LIR_Op::IAnd_Unchecked:
                registers[pc->dst] = make_i128(as_i128(registers[pc->a]) & as_i128(registers[pc->b]));
                break;
            case LIR::LIR_Op::Or:
            case LIR::LIR_Op::IOr_Unchecked:
                registers[pc->dst] = make_i128(as_i128(registers[pc->a]) | as_i128(registers[pc->b]));
                break;
            case LIR::LIR_Op::Xor:
            case LIR::LIR_Op::IXor_Unchecked:
                registers[pc->dst] = make_i128(as_i128(registers[pc->a]) ^ as_i128(registers[pc->b]));
                break;
            case LIR::LIR_Op::Shl:
            case LIR::LIR_Op::Shr: {
                __int128 value = as_i128(registers[pc->a]);
                int64_t amount = as_i64(registers[pc->b]);
                if (amount < 0 || amount >= 128) {
                    registers[pc->dst] = make_i128(0);
                } else if (pc->op == LIR::LIR_Op::Shl) {
                    registers[pc->dst] = make_i128(value << amount);
                } else if (uns) {
                    registers[pc->dst] = make_i128(static_cast<__int128>(
                        static_cast<unsigned __int128>(value) >> amount));
                } else {
                    registers[pc->dst] = make_i128(value >> amount);
                }
                break;
            }
            default:
                break;
        }
        return;
    }
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
