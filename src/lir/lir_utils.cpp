#include "lir.hh"
#include <iomanip>
#include <sstream>

namespace LIR {

std::string LIR_Disassembler::disassemble() const {
    std::stringstream ss;
    
    // Function header
    ss << "function " << func.name << "(";
    for (uint32_t i = 0; i < func.param_count; ++i) {
        if (i > 0) ss << ", ";
        ss << "r" << i;
    }
    ss << ") {\n";
    
    // Instructions
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        
        // Add label if this is a jump target
        for (size_t j = 0; j < func.instructions.size(); ++j) {
            const auto& other = func.instructions[j];
            if ((other.op == LIR_Op::Jump || other.op == LIR_Op::JumpIfFalse) && 
                static_cast<size_t>(other.imm) == i) {
                ss << "L" << i << ":\n";
                break;
            }
        }
        
        // Add instruction
        ss << "  " << i << ": " << disassemble_instruction(inst) << "\n";
    }
    
    ss << "}";
    return ss.str();
}

std::string LIR_Disassembler::disassemble_instruction(const LIR_Inst& inst) const {
    std::string result = inst.to_string();
    
    // Add debug info if enabled
    if (show_debug_info) {
        auto it = func.debug_info.var_names.find(inst.dst);
        if (it != func.debug_info.var_names.end()) {
            result += " ; " + it->second;
        }
    }
    
    return result;
}

bool LIR_Optimizer::optimize() {
    bool changed = false;
    
    if (func.optimizations.enable_peephole) {
        changed |= peephole_optimize();
    }
    
    if (func.optimizations.enable_const_fold) {
        changed |= constant_folding();
    }
    
    if (func.optimizations.enable_dead_code_elim) {
        changed |= dead_code_elimination();
    }
    
    return changed;
}

bool LIR_Optimizer::peephole_optimize() {
    // Simple peephole optimizations
    bool changed = false;
    
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        auto& inst = func.instructions[i];
        
        // Remove redundant moves: mov r1, r0 -> (use r0 directly)
        if (inst.op == LIR_Op::Mov && inst.dst == inst.a) {
            func.instructions.erase(func.instructions.begin() + i);
            --i;
            changed = true;
            continue;
        }
        
        // TODO: Add more peephole patterns
    }
    
    return changed;
}

bool LIR_Optimizer::constant_folding() {
    bool changed = false;
    
    for (auto& inst : func.instructions) {
        // Skip if not a binary operation with constant operands
        if (inst.a >= func.register_count || inst.b >= func.register_count) {
            continue;
        }
        
        // TODO: Implement constant folding for binary operations
        // This would involve tracking constant values and folding them
    }
    
    return changed;
}

bool LIR_Optimizer::dead_code_elimination() {
    // Simple dead code elimination
    std::vector<bool> used(func.register_count, false);
    
    // Mark all used registers
    for (const auto& inst : func.instructions) {
        // Mark source operands as used
        if (inst.a < func.register_count) used[inst.a] = true;
        if (inst.b < func.register_count) used[inst.b] = true;
    }
    
    // Remove instructions that write to unused registers
    bool changed = false;
    for (auto it = func.instructions.begin(); it != func.instructions.end(); ) {
        if (it->dst < func.register_count && !used[it->dst] &&
            it->op != LIR_Op::Store && it->op != LIR_Op::Return) {
            it = func.instructions.erase(it);
            changed = true;
        } else {
            ++it;
        }
    }
    
    return changed;
}

} // namespace LIR
