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
            lm_frame_set_field(enum_obj, 0, make_i64(pc->a));
            lm_frame_set_field(enum_obj, 1, registers[pc->b]);
            registers[pc->dst] = BOX_PTR(enum_obj);
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
