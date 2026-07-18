#include "../register.hh"
#include <iostream>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_io(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
