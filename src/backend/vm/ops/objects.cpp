#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_objects(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::MakeEnum: {
            // In the unified model, Enum can be a specialized LmFrame or its own type.
            // For now, let's use a Frame with 2 fields: [tag, payload]
            void* enum_obj = lm_frame_alloc("__lir_internal_enum__", 2);
            lm_frame_set_field(enum_obj, 0, make_i64(static_cast<int64_t>(pc->imm)));
            lm_frame_set_field(enum_obj, 1, pc->a == UINT32_MAX ? VAL_NIL : registers[pc->a]);
            registers[pc->dst] = BOX_PTR(enum_obj);
            break;
        }
        case LIR::LIR_Op::ConstructError: {
            // Error union with [is_error=1, payload]
            void* err_obj = lm_frame_alloc("__lir_internal_error__", 2);
            lm_frame_set_field(err_obj, 0, make_i64(1));
            lm_frame_set_field(err_obj, 1, registers[pc->a]);
            registers[pc->dst] = BOX_PTR(err_obj);
            break;
        }
        case LIR::LIR_Op::ConstructOk: {
            // Error union with [is_error=0, payload]
            void* ok_obj = lm_frame_alloc("__lir_internal_ok__", 2);
            lm_frame_set_field(ok_obj, 0, make_i64(0));
            lm_frame_set_field(ok_obj, 1, registers[pc->a]);
            registers[pc->dst] = BOX_PTR(ok_obj);
            break;
        }
        case LIR::LIR_Op::IsError: {
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                LmValue is_err = lm_frame_get_field(obj, 0);
                registers[pc->dst] = (as_i64(is_err) != 0) ? VAL_TRUE : VAL_FALSE;
            } else {
                registers[pc->dst] = VAL_FALSE;
            }
            break;
        }
        case LIR::LIR_Op::Unwrap: {
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = lm_frame_get_field(obj, 1);
            } else {
                registers[pc->dst] = registers[pc->a];
            }
            break;
        }
        case LIR::LIR_Op::GetTag: {
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = lm_frame_get_field(obj, 0);
            }
            break;
        }
        case LIR::LIR_Op::GetPayload: {
            if (IS_PTR(registers[pc->a])) {
                void* obj = UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = lm_frame_get_field(obj, 1);
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
