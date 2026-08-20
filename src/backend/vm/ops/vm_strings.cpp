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
                if (h && h->type_id == TYPE_STRING) {
                    LmStringHeader* str = (LmStringHeader*)h;
                    int64_t index = as_i64(registers[pc->b]);
                    if (index >= 0 && (uint64_t)index < str->len) {
                        registers[pc->dst] = make_i64((uint8_t)str->data[index]);
                    }
                } else if (h && h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                    const char* text = static_cast<const char*>(((LmBox*)h)->value.as_ptr);
                    int64_t index = as_i64(registers[pc->b]);
                    if (text && index >= 0) {
                        size_t len = std::strlen(text);
                        if (static_cast<size_t>(index) < len) {
                            registers[pc->dst] = make_i64(static_cast<uint8_t>(text[index]));
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
                LmStringHeader* s = lm_value_to_string(registers[pc->a]);
                str_val = s ? std::string(s->data, s->len) : "";
                lm_str_free(s);
            }
            LmStringHeader* res = lm_str_from_bytes(str_val.data(), str_val.length());
            registers[pc->dst] = BOX_PTR(res);
            if (res && !vm_region_stack.empty()) {
                uintptr_t ptr = reinterpret_cast<uintptr_t>(res);
                vm_allocation_regions[ptr] = active_region_id;
                vm_allocation_types[ptr] = TYPE_STRING;
            }
            break;
        }
        case LIR::LIR_Op::STR_CONCAT: {
            LmStringHeader* str_a = nullptr;
            LmStringHeader* str_b = nullptr;
            bool free_a = false, free_b = false;

            if (IS_PTR(registers[pc->a])) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(registers[pc->a]);
                if (h && h->type_id == TYPE_STRING) {
                    str_a = (LmStringHeader*)h;
                }
            }
            if (IS_PTR(registers[pc->b])) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(registers[pc->b]);
                if (h && h->type_id == TYPE_STRING) {
                    str_b = (LmStringHeader*)h;
                }
            }

            if (!str_a) {
                if (is_integer(registers[pc->a]) && str_b != nullptr) {
                    int64_t byte_val = as_i64(registers[pc->a]);
                    if (byte_val >= 0 && byte_val <= 255) {
                        char byte_char[2] = { (char)byte_val, '\0' };
                        str_a = lm_str_from_bytes(byte_char, 1);
                    } else {
                        str_a = lm_value_to_string(registers[pc->a]);
                    }
                } else {
                    str_a = lm_value_to_string(registers[pc->a]);
                }
                free_a = true;
            }
            if (!str_b) {
                if (is_integer(registers[pc->b]) && str_a != nullptr) {
                    int64_t byte_val = as_i64(registers[pc->b]);
                    if (byte_val >= 0 && byte_val <= 255) {
                        char byte_char[2] = { (char)byte_val, '\0' };
                        str_b = lm_str_from_bytes(byte_char, 1);
                    } else {
                        str_b = lm_value_to_string(registers[pc->b]);
                    }
                } else {
                    str_b = lm_value_to_string(registers[pc->b]);
                }
                free_b = true;
            }

            LmStringHeader* res = lm_str_concat(str_a, str_b);
            if (free_a) lm_str_free(str_a);
            if (free_b) lm_str_free(str_b);

            registers[pc->dst] = BOX_PTR(res);
            if (res && !vm_region_stack.empty()) {
                uintptr_t ptr = reinterpret_cast<uintptr_t>(res);
                vm_allocation_regions[ptr] = active_region_id;
                vm_allocation_types[ptr] = TYPE_STRING;
            }
            break;
        }
        case LIR::LIR_Op::STR_FORMAT: {
            LmStringHeader* fmt_hdr = nullptr;
            LmStringHeader* arg_hdr = nullptr;
            bool free_fmt = false, free_arg = false;

            if (IS_PTR(registers[pc->a])) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(registers[pc->a]);
                if (h && h->type_id == TYPE_STRING) fmt_hdr = (LmStringHeader*)h;
            }
            if (IS_PTR(registers[pc->b])) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(registers[pc->b]);
                if (h && h->type_id == TYPE_STRING) arg_hdr = (LmStringHeader*)h;
            }

            if (!fmt_hdr) {
                fmt_hdr = lm_value_to_string(registers[pc->a]);
                free_fmt = true;
            }
            if (!arg_hdr) {
                arg_hdr = lm_value_to_string(registers[pc->b]);
                free_arg = true;
            }

            LmStringHeader* res = lm_str_format(fmt_hdr, arg_hdr);
            if (free_fmt) lm_str_free(fmt_hdr);
            if (free_arg) lm_str_free(arg_hdr);

            registers[pc->dst] = BOX_PTR(res);
            if (res && !vm_region_stack.empty()) {
                uintptr_t ptr = reinterpret_cast<uintptr_t>(res);
                vm_allocation_regions[ptr] = active_region_id;
                vm_allocation_types[ptr] = TYPE_STRING;
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
