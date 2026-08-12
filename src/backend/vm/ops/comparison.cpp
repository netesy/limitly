#include "../register.hh"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

#include <iostream>
void RegisterVM::execute_comparison(const LIR::LIR_Inst* pc) {
    bool result = false;
    if (pc->op == LIR::LIR_Op::CmpEQ) {
        result = lm_value_eq(registers[pc->a], registers[pc->b]);
    } else if (pc->op == LIR::LIR_Op::CmpNEQ) {
        result = !lm_value_eq(registers[pc->a], registers[pc->b]);
    } else {
        int cmp = numeric_compare(registers[pc->a], registers[pc->b]);
        switch (pc->op) {
            case LIR::LIR_Op::CmpLT:  result = (cmp < 0);  break;
            case LIR::LIR_Op::CmpLE:  result = (cmp <= 0); break;
            case LIR::LIR_Op::CmpGT:  result = (cmp > 0);  break;
            case LIR::LIR_Op::CmpGE:  result = (cmp >= 0); break;
            default: break;
        }
        // Let's add a debug print for string comparisons!
        if (IS_PTR(registers[pc->a]) && IS_PTR(registers[pc->b])) {
            ObjHeader* h1 = (ObjHeader*)UNBOX_PTR(registers[pc->a]);
            ObjHeader* h2 = (ObjHeader*)UNBOX_PTR(registers[pc->b]);
            if (h1->type_id == TYPE_BOX && h2->type_id == TYPE_BOX) {
                LmBox* b1 = (LmBox*)h1;
                LmBox* b2 = (LmBox*)h2;
                if (b1->type == LM_BOX_STRING && b2->type == LM_BOX_STRING) {
                }
            }
        }
    }
    registers[pc->dst] = result ? VAL_TRUE : VAL_FALSE;
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
