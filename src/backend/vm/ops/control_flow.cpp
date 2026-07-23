#include "../register.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_control_flow(const LIR::LIR_Inst*& pc, const LIR::LIR_Function& function) {
    switch (pc->op) {
        case LIR::LIR_Op::Jump: {
            uint64_t target = pc->imm;
            auto it = current_label_map_.find(static_cast<uint32_t>(pc->imm));
            if (it != current_label_map_.end()) {
                target = it->second;
            }
            pc = function.instructions.data() + target - 1; // -1 because loop increments pc
            break;
        }
        case LIR::LIR_Op::JumpIf: {
            if (to_bool(registers[pc->a])) {
                uint64_t target = pc->imm;
                auto it = current_label_map_.find(static_cast<uint32_t>(pc->imm));
                if (it != current_label_map_.end()) {
                    target = it->second;
                }
                pc = function.instructions.data() + target - 1;
            }
            break;
        }
        case LIR::LIR_Op::JumpIfFalse: {
            if (!to_bool(registers[pc->a])) {
                uint64_t target = pc->imm;
                auto it = current_label_map_.find(static_cast<uint32_t>(pc->imm));
                if (it != current_label_map_.end()) {
                    target = it->second;
                }
                pc = function.instructions.data() + target - 1;
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
