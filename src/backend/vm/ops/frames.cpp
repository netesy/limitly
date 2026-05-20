#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_frames(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::NewFrame:
            registers[pc->dst] = BOX_PTR(lm_frame_alloc(pc->type_name.c_str(), pc->a));
            break;
        case LIR::LIR_Op::FrameGetField:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = lm_frame_get_field(UNBOX_PTR(registers[pc->a]), pc->b);
            }
            break;
        case LIR::LIR_Op::FrameSetField:
            if (IS_PTR(registers[pc->dst])) {
                lm_frame_set_field(UNBOX_PTR(registers[pc->dst]), pc->a, registers[pc->b]);
            }
            break;
        case LIR::LIR_Op::FrameGetFieldAtomic:
            if (IS_PTR(registers[pc->a])) {
                registers[pc->dst] = lm_frame_get_field_atomic(UNBOX_PTR(registers[pc->a]), pc->b);
            }
            break;
        case LIR::LIR_Op::FrameSetFieldAtomic:
            if (IS_PTR(registers[pc->dst])) {
                lm_frame_set_field_atomic(UNBOX_PTR(registers[pc->dst]), pc->a, registers[pc->b]);
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
