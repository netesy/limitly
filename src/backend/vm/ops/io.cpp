#include "../register.hh"
#include <iostream>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_io(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::PrintInt:
        case LIR::LIR_Op::PrintUint:
            std::cout << to_int(registers[pc->a]) << std::endl;
            break;
        case LIR::LIR_Op::PrintFloat:
            std::cout << to_float(registers[pc->a]) << std::endl;
            break;
        case LIR::LIR_Op::PrintBool:
            std::cout << (to_bool(registers[pc->a]) ? "true" : "false") << std::endl;
            break;
        case LIR::LIR_Op::PrintString:
            std::cout << to_string(registers[pc->a]) << std::endl;
            break;
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
