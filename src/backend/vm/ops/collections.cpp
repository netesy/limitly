#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_list.h"
#include "../../../runtime/runtime_dict.h"
#include "../../../runtime/runtime_tuple.h"
#include "../../../runtime/runtime_value.h"
#include <cstdlib>

namespace {

ObjHeader* header_if_type(LmValue value, uint32_t type_id) {
    if (!IS_PTR(value)) return nullptr;
    auto* header = static_cast<ObjHeader*>(UNBOX_PTR(value));
    return header && header->type_id == type_id ? header : nullptr;
}

} // namespace

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
            if (auto* list = reinterpret_cast<LmList*>(header_if_type(registers[pc->a], TYPE_LIST))) {
                lm_list_append(list, registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::ListLen:
            if (auto* list = reinterpret_cast<LmList*>(header_if_type(registers[pc->a], TYPE_LIST))) {
                registers[pc->dst] = make_i64(lm_list_len(list));
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
            if (auto* dict = reinterpret_cast<LmDict*>(header_if_type(registers[pc->dst], TYPE_DICT))) {
                lm_dict_set(dict, registers[pc->a], registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::DictGet:
            if (auto* dict = reinterpret_cast<LmDict*>(header_if_type(registers[pc->a], TYPE_DICT))) {
                registers[pc->dst] = lm_dict_get(dict, registers[pc->b]);
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::DictHas:
            if (auto* dict = reinterpret_cast<LmDict*>(header_if_type(registers[pc->a], TYPE_DICT))) {
                registers[pc->dst] = lm_dict_contains(dict, registers[pc->b]) ? VAL_TRUE : VAL_FALSE;
            } else {
                registers[pc->dst] = VAL_FALSE;
            }
            break;
        case LIR::LIR_Op::DictLen:
            if (auto* dict = reinterpret_cast<LmDict*>(header_if_type(registers[pc->a], TYPE_DICT))) {
                registers[pc->dst] = make_i64(static_cast<int64_t>(dict->size));
            } else {
                registers[pc->dst] = make_i64(0);
            }
            break;
        case LIR::LIR_Op::DictItems:
            if (pc->call_args.size() >= 2 && header_if_type(registers[pc->call_args[0]], TYPE_DICT)) {
                uint64_t count = 0;
                LmValue* items = lm_dict_items(reinterpret_cast<LmDict*>(header_if_type(registers[pc->call_args[0]], TYPE_DICT)), &count);
                int64_t wanted = as_i64(registers[pc->call_args[1]]);
                if (items && wanted >= 0 && static_cast<uint64_t>(wanted) < count) {
                    registers[pc->dst] = items[static_cast<uint64_t>(wanted) * 2];
                } else {
                    registers[pc->dst] = VAL_NIL;
                }
                if (items) free(items);
            } else if (auto* dict = reinterpret_cast<LmDict*>(header_if_type(registers[pc->a], TYPE_DICT))) {
                uint64_t count = 0;
                LmValue* items = lm_dict_items(dict, &count);
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
            if (auto* tuple = reinterpret_cast<LmTuple*>(header_if_type(registers[pc->dst], TYPE_TUPLE))) {
                lm_tuple_set(tuple, static_cast<uint64_t>(as_i64(registers[pc->a])), registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::TupleGet:
            if (auto* tuple = reinterpret_cast<LmTuple*>(header_if_type(registers[pc->a], TYPE_TUPLE))) {
                registers[pc->dst] = lm_tuple_get(tuple, static_cast<uint64_t>(as_i64(registers[pc->b])));
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::TupleLen:
            if (auto* tuple = reinterpret_cast<LmTuple*>(header_if_type(registers[pc->a], TYPE_TUPLE))) {
                registers[pc->dst] = make_i64(static_cast<int64_t>(lm_tuple_size(tuple)));
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
