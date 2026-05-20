#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_string.h"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_strings(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::ToString: {
            LmString s = lm_value_to_string(registers[pc->a]);
            registers[pc->dst] = BOX_PTR(lm_box_string(s.data));
            lm_string_free(s);
            break;
        }
        case LIR::LIR_Op::STR_CONCAT: {
            std::string s1 = to_string(registers[pc->a]);
            std::string s2 = to_string(registers[pc->b]);
            registers[pc->dst] = BOX_PTR(lm_box_string((s1 + s2).c_str()));
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
