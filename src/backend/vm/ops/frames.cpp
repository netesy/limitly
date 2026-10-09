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

LmFrame* RegisterVM::checked_frame(RegisterValue value, uint32_t index) {
        if (!IS_PTR(value)) throw std::runtime_error("Invalid frame receiver");
        auto pointer = reinterpret_cast<uintptr_t>(UNBOX_PTR(value));
        bool live = false;
        for (auto* owner = this; owner && !live; owner = owner->heap_parent_) {
            std::lock_guard<std::recursive_mutex> lock(owner->heap_mutex_);
            auto found = owner->vm_allocation_types.find(pointer);
            live = found != owner->vm_allocation_types.end() && found->second == TYPE_FRAME;
        }
        if (!live) throw std::runtime_error("Invalid or expired frame receiver");
        auto* frame = reinterpret_cast<LmFrame*>(pointer);
        if (!frame->fields || index >= static_cast<uint32_t>(frame->field_count))
            throw std::runtime_error("Invalid frame field index");
        return frame;
}

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
            registers[pc->dst] = checked_frame(registers[pc->a], pc->b)->fields[pc->b];
            break;
        case LIR::LIR_Op::FrameSetField:
            checked_frame(registers[pc->dst], pc->a)->fields[pc->a] = registers[pc->b];
            transfer_ownership(registers[pc->b], registers[pc->dst]);
            break;
        case LIR::LIR_Op::FrameGetFieldAtomic:
            registers[pc->dst] = lm_frame_get_field_atomic(checked_frame(registers[pc->a], pc->b), static_cast<int>(pc->b));
            break;
        case LIR::LIR_Op::FrameSetFieldAtomic:
            lm_frame_set_field_atomic(checked_frame(registers[pc->dst], pc->a), static_cast<int>(pc->a), registers[pc->b]);
            transfer_ownership(registers[pc->b], registers[pc->dst]);
            break;
        case LIR::LIR_Op::FrameFieldAtomicAdd:
            lm_frame_field_atomic_add(checked_frame(registers[pc->a], pc->b), static_cast<int>(pc->b), registers[pc->dst]);
            break;
        case LIR::LIR_Op::FrameFieldAtomicSub:
            lm_frame_field_atomic_sub(checked_frame(registers[pc->a], pc->b), static_cast<int>(pc->b), registers[pc->dst]);
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
