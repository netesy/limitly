#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_list.h"
#include "../../../runtime/runtime_dict.h"
#include "../../../runtime/runtime_tuple.h"
#include "../../../runtime/runtime_value.h"
#include <cstdlib>

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
            } else {
                registers[pc->dst] = make_i64(0);
            }
            break;
        case LIR::LIR_Op::ListIndex:
            if (IS_PTR(registers[pc->a])) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(registers[pc->a]);
                uint64_t index = static_cast<uint64_t>(as_i64(registers[pc->b]));
                if (h->type_id == TYPE_LIST) {
                    registers[pc->dst] = lm_list_get((LmList*)h, index);
                } else if (h->type_id == TYPE_TUPLE) {
                    registers[pc->dst] = lm_tuple_get((LmTuple*)h, index);
                } else {
                    registers[pc->dst] = VAL_NIL;
                }
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::DictCreate:
            registers[pc->dst] = BOX_PTR(lm_dict_new(hash_boxed_value, cmp_boxed_value));
            break;
        case LIR::LIR_Op::DictSet:
            if (IS_PTR(registers[pc->dst])) {
                lm_dict_set((LmDict*)UNBOX_PTR(registers[pc->dst]), registers[pc->a], registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::DictGet:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = lm_dict_get((LmDict*)UNBOX_PTR(registers[pc->a]), registers[pc->b]);
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::DictHas:
            registers[pc->dst] = (IS_PTR(registers[pc->a]) && lm_dict_contains((LmDict*)UNBOX_PTR(registers[pc->a]), registers[pc->b])) ? VAL_TRUE : VAL_FALSE;
            break;
        case LIR::LIR_Op::DictLen:
            if (IS_PTR(registers[pc->a])) {
                LmDict* dict = (LmDict*)UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = make_i64(static_cast<int64_t>(dict->size));
            } else {
                registers[pc->dst] = make_i64(0);
            }
            break;
        case LIR::LIR_Op::DictItems:
            if (pc->call_args.size() >= 2 && IS_PTR(registers[pc->call_args[0]])) {
                uint64_t count = 0;
                LmValue* items = lm_dict_items((LmDict*)UNBOX_PTR(registers[pc->call_args[0]]), &count);
                int64_t wanted = as_i64(registers[pc->call_args[1]]);
                if (items && wanted >= 0 && static_cast<uint64_t>(wanted) < count) {
                    registers[pc->dst] = items[static_cast<uint64_t>(wanted) * 2];
                } else {
                    registers[pc->dst] = VAL_NIL;
                }
                if (items) free(items);
            } else if (IS_PTR(registers[pc->a])) {
                uint64_t count = 0;
                LmValue* items = lm_dict_items((LmDict*)UNBOX_PTR(registers[pc->a]), &count);
                LmList* list = lm_list_new();
                for (uint64_t i = 0; items && i < count; ++i) {
                    LmTuple* entry = lm_tuple_new(2);
                    lm_tuple_set(entry, 0, items[i * 2]);
                    lm_tuple_set(entry, 1, items[i * 2 + 1]);
                    lm_list_append(list, BOX_PTR(entry));
                }
                if (items) free(items);
                registers[pc->dst] = BOX_PTR(list);
            } else {
                registers[pc->dst] = BOX_PTR(lm_list_new());
            }
            break;
        case LIR::LIR_Op::TupleCreate:
            registers[pc->dst] = BOX_PTR(lm_tuple_new(pc->imm));
            break;
        case LIR::LIR_Op::TupleSet:
            if (IS_PTR(registers[pc->dst])) {
                lm_tuple_set((LmTuple*)UNBOX_PTR(registers[pc->dst]), static_cast<uint64_t>(as_i64(registers[pc->a])), registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::TupleGet:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = lm_tuple_get((LmTuple*)UNBOX_PTR(registers[pc->a]), static_cast<uint64_t>(as_i64(registers[pc->b])));
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::TupleLen:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = make_i64(static_cast<int64_t>(lm_tuple_size((LmTuple*)UNBOX_PTR(registers[pc->a]))));
            } else {
                registers[pc->dst] = make_i64(0);
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
