#include "../register.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_modules(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::LoadGlobal:
            registers[pc->dst] = globals_[pc->func_name];
            break;
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
