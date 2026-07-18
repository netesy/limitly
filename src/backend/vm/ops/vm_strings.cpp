#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_string.h"
#include "../../../runtime/runtime_value.h"
#include <cstring>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_strings(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::StringIndex: {
            registers[pc->dst] = VAL_NIL;
            if (IS_PTR(registers[pc->a])) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(registers[pc->a]);
                if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                    const char* text = static_cast<const char*>(((LmBox*)h)->value.as_ptr);
                    int64_t index = as_i64(registers[pc->b]);
                    size_t len = std::strlen(text);
                    if (index >= 0 && static_cast<size_t>(index) < len) {
                        char out[2] = { text[index], '\0' };
                        registers[pc->dst] = BOX_PTR(lm_box_string(out));
                    }
                }
            }
            break;
        }
        case LIR::LIR_Op::ToString: {
            LmString s = lm_value_to_string(registers[pc->a]);
            registers[pc->dst] = BOX_PTR(lm_box_string(s.data));
            lm_string_free(s);
            break;
        }
        case LIR::LIR_Op::STR_CONCAT: {
            LmString s1 = lm_value_to_string(registers[pc->a]);
            LmString s2 = lm_value_to_string(registers[pc->b]);
            LmString res = lm_string_concat(s1, s2);
            registers[pc->dst] = BOX_PTR(lm_box_string(res.data));
            lm_string_free(s1);
            lm_string_free(s2);
            lm_string_free(res);
            break;
        }
        case LIR::LIR_Op::STR_FORMAT: {
            LmString fmt = lm_value_to_string(registers[pc->a]);
            LmString arg = lm_value_to_string(registers[pc->b]);
            LmString res = lm_string_format(fmt, arg);
            registers[pc->dst] = BOX_PTR(lm_box_string(res.data));
            lm_string_free(fmt);
            lm_string_free(arg);
            lm_string_free(res);
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
