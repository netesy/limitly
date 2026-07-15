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
            if (IS_PTR(registers[pc->dst])) {
                lm_list_append((LmList*)UNBOX_PTR(registers[pc->dst]), registers[pc->a]);
            }
            break;
        case LIR::LIR_Op::ListIndex:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = lm_list_get((LmList*)UNBOX_PTR(registers[pc->a]), to_int(registers[pc->b]));
            }
            break;
        case LIR::LIR_Op::ListLen:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = make_i64(lm_list_len((LmList*)UNBOX_PTR(registers[pc->a])));
            }
            break;
        case LIR::LIR_Op::TupleCreate: {
            int64_t size = pc->imm;
            registers[pc->dst] = BOX_PTR(lm_tuple_new(size));
            break;
        }
        case LIR::LIR_Op::TupleSet: {
            if (IS_PTR(registers[pc->dst])) {
                int64_t idx = to_int(registers[pc->a]);
                lm_tuple_set((LmTuple*)UNBOX_PTR(registers[pc->dst]), idx, registers[pc->b]);
            }
            break;
        }
        case LIR::LIR_Op::TupleGet: {
            if (IS_PTR(registers[pc->a])) {
                int64_t idx = to_int(registers[pc->b]);
                registers[pc->dst] = lm_tuple_get((LmTuple*)UNBOX_PTR(registers[pc->a]), idx);
            }
            break;
        }
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
