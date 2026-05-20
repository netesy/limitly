#include "../register.hh"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_comparison(const LIR::LIR_Inst* pc) {
    int cmp = numeric_compare(registers[pc->a], registers[pc->b]);
    bool result = false;
    switch (pc->op) {
        case LIR::LIR_Op::CmpEQ:  result = (cmp == 0); break;
        case LIR::LIR_Op::CmpNEQ: result = (cmp != 0); break;
        case LIR::LIR_Op::CmpLT:  result = (cmp < 0);  break;
        case LIR::LIR_Op::CmpLE:  result = (cmp <= 0); break;
        case LIR::LIR_Op::CmpGT:  result = (cmp > 0);  break;
        case LIR::LIR_Op::CmpGE:  result = (cmp >= 0); break;
        default: break;
    }
    registers[pc->dst] = result ? VAL_TRUE : VAL_FALSE;
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
