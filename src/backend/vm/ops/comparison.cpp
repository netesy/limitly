#include "../register.hh"
#include "../vm_value.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

#include <iostream>
void RegisterVM::execute_comparison(const LIR::LIR_Inst* pc) {
    RegisterValue va = registers[pc->a];
    RegisterValue vb = registers[pc->b];
    if (IS_INT(va) && IS_INT(vb)) {
        int64_t ia = UNBOX_INT(va);
        int64_t ib = UNBOX_INT(vb);
        bool res = false;
        switch (pc->op) {
            case LIR::LIR_Op::CmpEQ:  res = (ia == ib); break;
            case LIR::LIR_Op::CmpNEQ: res = (ia != ib); break;
            case LIR::LIR_Op::CmpLT:  res = (ia < ib);  break;
            case LIR::LIR_Op::CmpLE:  res = (ia <= ib); break;
            case LIR::LIR_Op::CmpGT:  res = (ia > ib);  break;
            case LIR::LIR_Op::CmpGE:  res = (ia >= ib); break;
            default: break;
        }
        registers[pc->dst] = res ? VAL_TRUE : VAL_FALSE;
        return;
    }

    bool result = false;
    if (pc->op == LIR::LIR_Op::CmpEQ) {
        result = lm_value_eq(va, vb);
    } else if (pc->op == LIR::LIR_Op::CmpNEQ) {
        result = !lm_value_eq(va, vb);
    } else {
        int cmp = numeric_compare(va, vb);
        switch (pc->op) {
            case LIR::LIR_Op::CmpLT:  result = (cmp < 0);  break;
            case LIR::LIR_Op::CmpLE:  result = (cmp <= 0); break;
            case LIR::LIR_Op::CmpGT:  result = (cmp > 0);  break;
            case LIR::LIR_Op::CmpGE:  result = (cmp >= 0); break;
            default: break;
        }
    }
    registers[pc->dst] = result ? VAL_TRUE : VAL_FALSE;
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
