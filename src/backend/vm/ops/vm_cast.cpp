#include "../register.hh"
#include "../vm_value.hh"
#include "../vm_string.hh"
#include <string>
#include <cstdlib>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_cast(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::Cast: {
            LmValue val = registers[pc->a];
            if (pc->result_type == LIR::Type::I64) {
                if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h) {
                        const char* str = nullptr;
                        if (h->type_id == TYPE_STRING) {
                            str = ((LmStringHeader*)h)->data;
                        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                            str = (const char*)((LmBox*)h)->value.as_ptr;
                        }
                        if (str) {
                            try {
                                registers[pc->dst] = make_i64(std::stoll(str));
                                break;
                            } catch (...) {}
                        }
                    }
                }
                registers[pc->dst] = make_i64(as_i64(val));
            } else if (pc->result_type == LIR::Type::F64) {
                if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h) {
                        const char* str = nullptr;
                        if (h->type_id == TYPE_STRING) {
                            str = ((LmStringHeader*)h)->data;
                        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                            str = (const char*)((LmBox*)h)->value.as_ptr;
                        }
                        if (str) {
                            try {
                                registers[pc->dst] = make_float(std::stod(str));
                                break;
                            } catch (...) {}
                        }
                    }
                }
                registers[pc->dst] = make_float(as_float(val));
            } else if (pc->result_type == LIR::Type::Bool) {
                registers[pc->dst] = to_bool(val) ? VAL_TRUE : VAL_FALSE;
            } else {
                registers[pc->dst] = val;
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
