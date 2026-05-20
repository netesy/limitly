#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_list.h"
#include "../../../runtime/runtime_dict.h"
#include "../../../runtime/runtime_tuple.h"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_collections(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::ListCreate:
            registers[pc->dst] = BOX_PTR(lm_list_new());
            break;
        case LIR::LIR_Op::ListAppend:
            if (IS_PTR(registers[pc->a])) {
                lm_list_append((LmList*)UNBOX_PTR(registers[pc->a]), registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::ListLen:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = make_i64(lm_list_len((LmList*)UNBOX_PTR(registers[pc->a])));
            }
            break;
        case LIR::LIR_Op::TupleCreate:
            registers[pc->dst] = BOX_PTR(lm_tuple_new(pc->a));
            break;
        case LIR::LIR_Op::TupleSet:
            if (IS_PTR(registers[pc->dst])) {
                lm_tuple_set((LmTuple*)UNBOX_PTR(registers[pc->dst]), pc->a, registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::TupleGet:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = lm_tuple_get((LmTuple*)UNBOX_PTR(registers[pc->a]), pc->b);
            }
            break;
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
