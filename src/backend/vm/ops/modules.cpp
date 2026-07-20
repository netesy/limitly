#include "../register.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_modules(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::LoadGlobal: {
            auto it = globals_.find(pc->func_name);
            if (it != globals_.end()) {
                registers[pc->dst] = it->second;
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        }
        case LIR::LIR_Op::StoreGlobal:
            globals_[pc->func_name] = registers[pc->a];
            break;
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
