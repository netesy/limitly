#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include <cstdio>
#include <stdexcept>
#include <string>

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
            // pc->dst holds the frame pointer (container), pc->b holds the value.
            if (IS_PTR(registers[pc->dst])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->dst]);
                if (f && pc->a >= 0 && pc->a < f->field_count) {
                    f->fields[pc->a] = registers[pc->b];
                }
            }
            break;
        case LIR::LIR_Op::FrameGetFieldAtomic:
            // Atomic variant: same semantics as the regular getter for now
            // (the runtime helpers are also non-atomic underneath; the
            // distinction exists for future memory-model work).
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && pc->b >= 0 && pc->b < f->field_count) {
                    registers[pc->dst] = lm_frame_get_field_atomic(f, (int)pc->b);
                } else {
                    registers[pc->dst] = VAL_NIL;
                }
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::FrameSetFieldAtomic:
            if (IS_PTR(registers[pc->dst])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->dst]);
                if (f && pc->a >= 0 && pc->a < f->field_count) {
                    lm_frame_set_field_atomic(f, (int)pc->a, registers[pc->b]);
                }
            }
            break;
        case LIR::LIR_Op::FrameFieldAtomicAdd:
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && pc->b >= 0 && pc->b < f->field_count) {
                    lm_frame_field_atomic_add(f, (int)pc->b, registers[pc->dst]);
                }
            }
            break;
        case LIR::LIR_Op::FrameFieldAtomicSub:
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && pc->b >= 0 && pc->b < f->field_count) {
                    lm_frame_field_atomic_sub(f, (int)pc->b, registers[pc->dst]);
                }
            }
            break;
        case LIR::LIR_Op::FrameCallMethod:
            // Method dispatch on frames is performed through the regular
            // function call machinery (FrameType.method) at LIR-generation
            // time; this opcode should not normally be emitted. Log and continue
            // rather than throwing — throwing breaks any program that exercises
            // a frame method through this path.
            break;
        case LIR::LIR_Op::FrameCallInit:
            // Init dispatch is handled at LIR-generation time; no-op here.
            break;
        case LIR::LIR_Op::FrameCallDeinit:
            // Deinit dispatch: no-op for now (full implementation would call
            // the frame's deinit() method). Silently continuing is safer than
            // throwing, which breaks programs that define deinit().
            break;
        case LIR::LIR_Op::MakeTraitObject:
            // Minimal placeholder: produce a 2-field frame [instance_ptr, trait_id].
            // Full trait vtable is deferred.
            break;
        case LIR::LIR_Op::TraitCallMethod:
            // No-op for now; full trait method dispatch is deferred.
            break;
        // The following cases are routed here by the main dispatcher for
        // historical reasons; the implementations live in execute_objects.
        // We fall through to the default-throw so any future re-routing
        // mismatch becomes loud rather than silent.
        default:
            throw std::runtime_error(
                "VM: execute_frames: unsupported opcode " +
                std::to_string(static_cast<int>(pc->op)));
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
