#include "../register.hh"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_arithmetic(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::Add:
            registers[pc->dst] = lm_add(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Sub:
            registers[pc->dst] = lm_sub(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Mul:
            registers[pc->dst] = lm_mul(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Div:
            registers[pc->dst] = lm_div(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::Neg:
            registers[pc->dst] = lm_sub(make_i64(0), registers[pc->a]);
            break;
        case LIR::LIR_Op::DecAdd:
            registers[pc->dst] = lm_add(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecSub:
            registers[pc->dst] = lm_sub(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecMul:
            // Simplified: decimal multiply needs rescaling, but let's use runtime
            registers[pc->dst] = lm_mul(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecDiv:
            registers[pc->dst] = lm_div(registers[pc->a], registers[pc->b]);
            break;
        case LIR::LIR_Op::DecMod:
            // Placeholder
            registers[pc->dst] = VAL_NIL;
            break;
        case LIR::LIR_Op::DecNeg:
            registers[pc->dst] = lm_sub(make_i64(0), registers[pc->a]);
            break;
        case LIR::LIR_Op::DecRescale:
            // Simplified rescale
            registers[pc->dst] = registers[pc->a];
            break;
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
