#include "verifier.hh"
#include <iostream>
#include <algorithm>
#include <unordered_map>

namespace LM {
namespace LIR {

bool Verifier::verify(const LIR_Function& func, std::vector<std::string>& errors) {
    bool success = true;
    
    for (const auto& inst : func.instructions) {
        if (!verify_instruction(inst, func, errors)) {
            success = false;
        }
    }
    
    if (!verify_control_flow(func, errors)) {
        success = false;
    }
    
    if (!detect_infinite_loops(func, errors)) {
        success = false;
    }
    
    return success;
}

bool Verifier::verify_instruction(const LIR_Inst& inst, const LIR_Function& func, std::vector<std::string>& errors) {
    if (inst.dst != UINT32_MAX && inst.dst >= func.register_count) {
        errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid destination register " + std::to_string(inst.dst));
        return false;
    }
    
    if (inst.a != UINT32_MAX && inst.a >= func.register_count) {
        errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid a register " + std::to_string(inst.a));
        return false;
    }
    
    if (inst.b != UINT32_MAX && inst.b >= func.register_count) {
        errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid b register " + std::to_string(inst.b));
        return false;
    }
    
    for (Reg arg : inst.call_args) {
        if (arg >= func.register_count) {
            errors.push_back("Instruction " + lir_op_to_string(inst.op) + " uses invalid argument register " + std::to_string(arg));
            return false;
        }
    }
    
    return true;
}

bool Verifier::verify_control_flow(const LIR_Function& func, std::vector<std::string>& errors) {
    std::unordered_set<uint32_t> labels;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Label) {
            labels.insert(inst.imm);
        }
    }
    
    bool success = true;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
            if (labels.find(inst.imm) == labels.end()) {
                errors.push_back("Function " + func.name + " has jump to undefined label " + std::to_string(inst.imm));
                success = false;
            }
        }
    }
    
    return success;
}

bool Verifier::detect_infinite_loops(const LIR_Function& func, std::vector<std::string>& errors) {
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::Jump) {
            uint32_t target_label = inst.imm;
            if (i > 0 && func.instructions[i-1].op == LIR_Op::Label && func.instructions[i-1].imm == target_label) {
                errors.push_back("Infinite loop detected in function " + func.name + ": self-jump at instruction " + std::to_string(i));
                return false;
            }
        }
    }
    
    return true;
}

} // namespace LIR
} // namespace LM
