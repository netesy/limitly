#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../../lir/function_registry.hh"
#include "../../lir/builtin_functions.hh"
#include "register.hh"
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_list.h"
#include "../../runtime/runtime_dict.h"
#include "../../runtime/runtime_tuple.h"
#include "../../runtime/runtime_value.h"
#include <iostream>
#include <memory>
#include <cstring>
#include <cstdint>
#include <string>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {
static __int128 parse_i128(const std::string& s) {
    __int128 result = 0;
    bool neg = false;
    size_t i = 0;
    if (s.empty()) return 0;
    if (s[0] == '-') { neg = true; i = 1; }
    for (; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
            result = result * 10 + (s[i] - '0');
    }
    return neg ? -result : result;
}

static unsigned __int128 parse_u128(const std::string& s) {
    unsigned __int128 result = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
            result = result * 10 + (s[i] - '0');
    }
    return result;
}


void RegisterVM::execute_instructions(const LIR::LIR_Function& function, size_t start_pc, size_t end_pc) {
    const LIR::LIR_Inst* pc = function.instructions.data() + start_pc;
    const LIR::LIR_Inst* end = function.instructions.data() + end_pc;

    while (pc < end) {
        instruction_count++;
        if (instruction_count > MAX_INSTRUCTIONS) {
            std::cerr << "Error: Instruction limit exceeded" << std::endl;
            return;
        }

        switch (pc->op) {
            case LIR::LIR_Op::LoadConst: {
                ValuePtr cv = pc->const_val;
                if (!cv) {
                    registers[pc->dst] = VAL_NIL;
                } else {
                    switch (cv->type->tag) {
                        case TypeTag::Int:
                        case TypeTag::Int64:
                            registers[pc->dst] = make_i64(std::stoll(cv->data));
                            break;
                        case TypeTag::UInt:
                        case TypeTag::UInt64:
                            registers[pc->dst] = make_u64(std::stoull(cv->data));
                            break;
                        case TypeTag::Int128:
                            registers[pc->dst] = make_i128(parse_i128(cv->data));
                            break;
                        case TypeTag::UInt128:
                            registers[pc->dst] = make_u128(parse_u128(cv->data));
                            break;
                        case TypeTag::Float64:
                            registers[pc->dst] = make_float(std::stod(cv->data));
                            break;
                        case TypeTag::Bool:
                            registers[pc->dst] = (cv->data == "true") ? VAL_TRUE : VAL_FALSE;
                            break;
                        case TypeTag::String:
                            registers[pc->dst] = BOX_PTR(lm_box_string(cv->data.c_str()));
                            break;
                        default:
                            registers[pc->dst] = VAL_NIL;
                    }
                }
                break;
            }
            case LIR::LIR_Op::Add: {
                registers[pc->dst] = lm_add(registers[pc->a], registers[pc->b]);
                break;
            }
            case LIR::LIR_Op::Sub: {
                registers[pc->dst] = lm_sub(registers[pc->a], registers[pc->b]);
                break;
            }
            case LIR::LIR_Op::Mul: {
                registers[pc->dst] = lm_mul(registers[pc->a], registers[pc->b]);
                break;
            }
            case LIR::LIR_Op::Div: {
                registers[pc->dst] = lm_div(registers[pc->a], registers[pc->b]);
                break;
            }
            case LIR::LIR_Op::Mov: {
                registers[pc->dst] = registers[pc->a];
                break;
            }
            case LIR::LIR_Op::CmpEQ: {
                registers[pc->dst] = (lm_value_eq(registers[pc->a], registers[pc->b])) ? VAL_TRUE : VAL_FALSE;
                break;
            }
            case LIR::LIR_Op::CmpGT: {
                registers[pc->dst] = (numeric_compare(registers[pc->a], registers[pc->b]) > 0) ? VAL_TRUE : VAL_FALSE;
                break;
            }
            case LIR::LIR_Op::PrintInt:
            case LIR::LIR_Op::PrintUint: {
                std::cout << as_i64(registers[pc->a]) << std::endl;
                break;
            }
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret: {
                if (pc->op == LIR::LIR_Op::Ret) registers[0] = registers[pc->a];
                return;
            }
            // ... Many more opcodes need to be migrated ...
            default:
                // For now, let's just break to avoid crashing
                break;
        }
        pc++;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
