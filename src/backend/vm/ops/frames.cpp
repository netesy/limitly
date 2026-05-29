#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include <cstdio>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_frames(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::NewFrame:
            // LIR generator puts field count in pc->imm
            registers[pc->dst] = BOX_PTR(lm_frame_alloc(pc->type_name.c_str(), pc->imm));
            break;
        case LIR::LIR_Op::FrameGetField:
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && pc->b >= 0 && pc->b < f->field_count) {
                    registers[pc->dst] = f->fields[pc->b];
                } else {
                    registers[pc->dst] = 0;
                }
            }
            break;
        case LIR::LIR_Op::FrameSetField:
            if (IS_PTR(registers[pc->dst])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->dst]);
                if (f && pc->a >= 0 && pc->a < f->field_count) {
                    f->fields[pc->a] = registers[pc->b];
                }
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
