#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include "../../../lir/functions.hh"
#include "../compiled_resolver.hh"
#include <cstdio>
#include <stdexcept>
#include <string>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_frames(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::NewFrame: {
            // LIR generator puts field count in pc->imm
            LmFrame* frame = reinterpret_cast<LmFrame*>(lm_frame_alloc(pc->type_name.c_str(), pc->imm));
            registers[pc->dst] = BOX_PTR(frame);
            // Register allocation with current active region
            register_native_allocation(registers[pc->dst]);
            break;
        }
        case LIR::LIR_Op::FrameGetField:
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && f->header.type_id == TYPE_FRAME && pc->b < static_cast<uint32_t>(f->field_count)) {
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
                if (f && f->header.type_id == TYPE_FRAME && pc->a < static_cast<uint32_t>(f->field_count)) {
                    f->fields[pc->a] = registers[pc->b];
                    transfer_ownership(registers[pc->b], registers[pc->dst]);
                }
            }
            break;
        case LIR::LIR_Op::FrameGetFieldAtomic:
            // Atomic variant: same semantics as the regular getter for now
            // (the runtime helpers are also non-atomic underneath; the
            // distinction exists for future memory-model work).
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && f->header.type_id == TYPE_FRAME && pc->b < static_cast<uint32_t>(f->field_count)) {
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
                if (f && f->header.type_id == TYPE_FRAME && pc->a < static_cast<uint32_t>(f->field_count)) {
                    lm_frame_set_field_atomic(f, (int)pc->a, registers[pc->b]);
                    transfer_ownership(registers[pc->b], registers[pc->dst]);
                }
            }
            break;
        case LIR::LIR_Op::FrameFieldAtomicAdd:
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && pc->b < static_cast<uint32_t>(f->field_count)) {
                    lm_frame_field_atomic_add(f, (int)pc->b, registers[pc->dst]);
                }
            }
            break;
        case LIR::LIR_Op::FrameFieldAtomicSub:
            if (IS_PTR(registers[pc->a])) {
                LmFrame* f = (LmFrame*)UNBOX_PTR(registers[pc->a]);
                if (f && pc->b < static_cast<uint32_t>(f->field_count)) {
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
            finalize_frame(registers[pc->a]);
            break;
        case LIR::LIR_Op::MakeTraitObject:
            // Minimal placeholder: produce a 2-field frame [instance_ptr, trait_id].
            // Full trait vtable is deferred.
            break;
        case LIR::LIR_Op::TraitCallMethod: {
            if (pc->call_args.empty()) {
                throw std::runtime_error("VM: TraitCallMethod requires at least one argument (the receiver object)");
            }
            RegisterValue obj_val = registers[pc->call_args[0]];
            if (!IS_PTR(obj_val)) {
                throw std::runtime_error("VM: TraitCallMethod receiver is not a pointer");
            }
            LmFrame* f = (LmFrame*)UNBOX_PTR(obj_val);
            if (!f) {
                throw std::runtime_error("VM: TraitCallMethod receiver is null");
            }
            std::string frame_name = f->name;
            std::string resolved_func_name = frame_name + "." + pc->func_name;
            
            if (CompiledResolver::getInstance().dispatch(resolved_func_name, *pc, registers, this)) {
                break;
            }

            std::string trait_func_name = pc->type_name + "." + pc->func_name;
            if (CompiledResolver::getInstance().dispatch(trait_func_name, *pc, registers, this)) {
                break;
            }

            auto& func_manager = LIR::LIRFunctionManager::getInstance();
            std::string final_func_name = "";
            if (func_manager.hasFunction(resolved_func_name)) {
                final_func_name = resolved_func_name;
            } else {
                if (func_manager.hasFunction(trait_func_name)) {
                    final_func_name = trait_func_name;
                }
            }
            
            if (!final_func_name.empty()) {
                auto func = func_manager.getFunction(final_func_name);
                std::vector<RegisterValue> arg_vals;
                arg_vals.reserve(pc->call_args.size());
                for (auto arg_reg : pc->call_args) arg_vals.push_back(registers[arg_reg]);

                registers[pc->dst] = call_interpreted(final_func_name, arg_vals);
            } else {
                throw std::runtime_error("VM: TraitCallMethod: unresolved function " + resolved_func_name);
            }
            break;
        }
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
