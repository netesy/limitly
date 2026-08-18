#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_string.hh"
#include "../vm_value.hh"
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
                        LmBox* box = lm_box_string(out);
                        registers[pc->dst] = BOX_PTR(box);
                        // Register allocation with current active region
                        if (box && !vm_region_stack.empty()) {
                            uintptr_t ptr = reinterpret_cast<uintptr_t>(box);
                            vm_allocation_regions[ptr] = active_region_id;
                        }
                    }
                }
            }
            break;
        }
        case LIR::LIR_Op::ToString: {
            TypePtr lang_type = get_register_language_type(pc->a);
            std::string str_val;
            if (lang_type && is_decimal_type(lang_type)) {
                ValuePtr v = register_to_value_ptr(registers[pc->a], lang_type);
                str_val = v->toString();
            } else {
                LmString s = lm_value_to_string(registers[pc->a]);
                str_val = s.data ? s.data : "";
                lm_string_free(s);
            }
            LmBox* box = lm_box_string(str_val.c_str());
            registers[pc->dst] = BOX_PTR(box);
            if (box && !vm_region_stack.empty()) {
                uintptr_t ptr = reinterpret_cast<uintptr_t>(box);
                vm_allocation_regions[ptr] = active_region_id;
            }
            break;
        }
        case LIR::LIR_Op::STR_CONCAT: {
            LmString s1 = lm_value_to_string(registers[pc->a]);
            LmString s2 = lm_value_to_string(registers[pc->b]);
            LmString res = lm_string_concat(s1, s2);
            LmBox* box = lm_box_string(res.data);
            registers[pc->dst] = BOX_PTR(box);
            if (box && !vm_region_stack.empty()) {
                uintptr_t ptr = reinterpret_cast<uintptr_t>(box);
                vm_allocation_regions[ptr] = active_region_id;
            }
            lm_string_free(s1);
            lm_string_free(s2);
            lm_string_free(res);
            break;
        }
        case LIR::LIR_Op::STR_FORMAT: {
            TypePtr fmt_lang_type = get_register_language_type(pc->a);
            TypePtr arg_lang_type = get_register_language_type(pc->b);
            
            std::string fmt_str;
            if (fmt_lang_type && is_decimal_type(fmt_lang_type)) {
                fmt_str = register_to_value_ptr(registers[pc->a], fmt_lang_type)->toString();
            } else {
                LmString s = lm_value_to_string(registers[pc->a]);
                fmt_str = s.data ? s.data : "";
                lm_string_free(s);
            }
            
            std::string arg_str;
            if (arg_lang_type && is_decimal_type(arg_lang_type)) {
                arg_str = register_to_value_ptr(registers[pc->b], arg_lang_type)->toString();
            } else {
                LmString s = lm_value_to_string(registers[pc->b]);
                arg_str = s.data ? s.data : "";
                lm_string_free(s);
            }

            LmString fmt = lm_string_from_cstr(fmt_str.c_str());
            LmString arg = lm_string_from_cstr(arg_str.c_str());
            LmString res = lm_string_format(fmt, arg);
            LmBox* box = lm_box_string(res.data);
            registers[pc->dst] = BOX_PTR(box);
            if (box && !vm_region_stack.empty()) {
                uintptr_t ptr = reinterpret_cast<uintptr_t>(box);
                vm_allocation_regions[ptr] = active_region_id;
            }
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
