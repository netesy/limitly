#include "../register.hh"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_bitwise(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::And:
            registers[pc->dst] = make_i64(to_int(registers[pc->a]) & to_int(registers[pc->b]));
            break;
        case LIR::LIR_Op::Or:
            registers[pc->dst] = make_i64(to_int(registers[pc->a]) | to_int(registers[pc->b]));
            break;
        case LIR::LIR_Op::Xor:
            registers[pc->dst] = make_i64(to_int(registers[pc->a]) ^ to_int(registers[pc->b]));
            break;
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
