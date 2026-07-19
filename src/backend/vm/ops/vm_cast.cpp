#include "../register.hh"
#include "../../../runtime/runtime_value.h"
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
                    if (h->type_id == TYPE_BOX) {
                        LmBox* box = (LmBox*)h;
                        if (box->type == LM_BOX_STRING) {
                            const char* str = (const char*)box->value.as_ptr;
                            if (str) {
                                try {
                                    registers[pc->dst] = make_i64(std::stoll(str));
                                    break;
                                } catch (...) {}
                            }
                        }
                    }
                }
                registers[pc->dst] = make_i64(as_i64(val));
            } else if (pc->result_type == LIR::Type::F64) {
                if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h->type_id == TYPE_BOX) {
                        LmBox* box = (LmBox*)h;
                        if (box->type == LM_BOX_STRING) {
                            const char* str = (const char*)box->value.as_ptr;
                            if (str) {
                                try {
                                    registers[pc->dst] = make_float(std::stod(str));
                                    break;
                                } catch (...) {}
                            }
                        }
                    }
                }
                registers[pc->dst] = make_float(as_float(val));
            } else if (pc->result_type == LIR::Type::Bool) {
                registers[pc->dst] = to_bool(val) ? VAL_TRUE : VAL_FALSE;
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
