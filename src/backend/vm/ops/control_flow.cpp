#include "../register.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_control_flow(const LIR::LIR_Inst*& pc, const LIR::LIR_Function& function) {
    switch (pc->op) {
        case LIR::LIR_Op::Jump:
            pc = function.instructions.data() + pc->imm - 1; // -1 because loop increments pc
            break;
        case LIR::LIR_Op::JumpIf:
            if (to_bool(registers[pc->a])) {
                pc = function.instructions.data() + pc->imm - 1;
            }
            break;
        case LIR::LIR_Op::JumpIfFalse:
            if (!to_bool(registers[pc->a])) {
                pc = function.instructions.data() + pc->imm - 1;
            }
            break;
        case LIR::LIR_Op::EffectHandle: {
            uint64_t tag = pc->a != UINT32_MAX ? as_u64(registers[pc->a]) : pc->imm;
            uint64_t handler_pc = pc->b;
            uint64_t return_pc = pc->imm;
            auto* fiber = get_current_fiber();
            if (fiber) {
                fiber->push_effect_handler(tag, handler_pc, return_pc);
            }
            break;
        }
        case LIR::LIR_Op::EffectPerform: {
            uint64_t tag = pc->a != UINT32_MAX ? as_u64(registers[pc->a]) : pc->imm;
            auto* fiber = get_current_fiber();
            if (fiber) {
                const auto* frame = fiber->find_effect_handler(tag);
                if (frame) {
                    pc = function.instructions.data() + frame->handler_pc - 1;
                }
            }
            break;
        }
        case LIR::LIR_Op::EffectResume: {
            auto* fiber = get_current_fiber();
            if (fiber) {
                fiber->pop_effect_handler();
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
