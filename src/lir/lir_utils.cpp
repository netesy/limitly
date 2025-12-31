#include "lir.hh"
#include "function_registry.hh"
#include "functions.hh"
#include <iomanip>
#include <sstream>
#include <set>

namespace LIR {

std::string Disassembler::disassemble() const {
    std::stringstream ss;
    
    // Main function header
    ss << "function " << func.name << "(";
    for (uint32_t i = 0; i < func.param_count; ++i) {
        if (i > 0) ss << ", ";
        ss << "r" << i;
    }
    ss << ") {\n";
    
    // Collect function names that are actually called in the main function
    std::set<std::string> called_functions;
    for (const auto& inst : func.instructions) {
        if (inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid) {
            if (!inst.func_name.empty()) {
                called_functions.insert(inst.func_name);
            }
        }
    }
    
    // Main function instructions
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
    
    ss << "}\n";
    
    // Only show user-defined functions that are actually called
    auto& function_registry = FunctionRegistry::getInstance();
    
    if (!called_functions.empty()) {
        ss << "\n=== User-Defined Functions ===\n";
        for (const auto& func_name : called_functions) {
            auto lir_func = function_registry.getFunction(func_name);
            if (lir_func && !lir_func->instructions.empty()) {
                // Only show functions that have actual instructions (not just builtin stubs)
                bool has_real_instructions = false;
                for (const auto& inst : lir_func->instructions) {
                    // Builtin functions typically have just a call and return instruction
                    if (inst.op != LIR_Op::Call && inst.op != LIR_Op::Return) {
                        has_real_instructions = true;
                        break;
                    }
                }
                
                // Show functions that either have real instructions or more than just call+return
                if (has_real_instructions || lir_func->instructions.size() > 2) {
                    // Create a temporary disassembler for this function
                    Disassembler func_disassemble(*lir_func, show_debug_info);
                    
                    // Get the disassembly but remove the recursive call to avoid infinite loop
                    ss << "\nfunction " << lir_func->name << "(";
                    for (uint32_t i = 0; i < lir_func->param_count; ++i) {
                        if (i > 0) ss << ", ";
                        ss << "r" << i;
                    }
                    ss << ") {\n";
                    
                    // Function instructions
                    for (size_t i = 0; i < lir_func->instructions.size(); ++i) {
                        const auto& inst = lir_func->instructions[i];
                        
                        // Add label if this is a jump target
                        for (size_t j = 0; j < lir_func->instructions.size(); ++j) {
                            const auto& other = lir_func->instructions[j];
                            if ((other.op == LIR_Op::Jump || other.op == LIR_Op::JumpIfFalse) && 
                                static_cast<size_t>(other.imm) == i) {
                                ss << "L" << i << ":\n";
                                break;
                            }
                        }
                        
                        // Add instruction
                        ss << "  " << i << ": " << func_disassemble.disassemble_instruction(inst) << "\n";
                    }
                    
                    ss << "}\n";
                }
            }
        }
    }
    
    // Add the actual function implementations from LIRFunctionManager (like in main.cpp)
    auto& lir_func_manager = LIRFunctionManager::getInstance();
    auto function_names = lir_func_manager.getFunctionNames();
    
    if (!function_names.empty()) {
        ss << "\n=== Function LIR Instructions ===\n";
        for (const auto& func_name : function_names) {
            auto lir_func = lir_func_manager.getFunction(func_name);
            if (lir_func) {
                const auto& instructions = lir_func->getInstructions();
                if (!instructions.empty()) {
                    // Function header in proper disassembly style
                    ss << "\nfunction " << func_name << "(";
                    for (size_t p = 0; p < lir_func->getParameters().size(); ++p) {
                        if (p > 0) ss << ", ";
                        ss << "r" << p;
                    }
                    ss << ") {\n";
                    
                    // Function instructions with proper formatting
                    for (size_t i = 0; i < instructions.size(); ++i) {
                        const auto& inst = instructions[i];
                        
                        // Add label if this is a jump target
                        for (size_t j = 0; j < instructions.size(); ++j) {
                            const auto& other = instructions[j];
                            if ((other.op == LIR_Op::Jump || other.op == LIR_Op::JumpIfFalse) && 
                                static_cast<size_t>(other.imm) == i) {
                                ss << "L" << i << ":\n";
                                break;
                            }
                        }
                        
                        // Add instruction with proper indentation and formatting
                        ss << "  " << i << ": " << inst.to_string();
                        
                        // Add debug info if enabled (similar to main function)
                        if (show_debug_info) {
                            // Note: LIRFunction doesn't have debug_info like LIR_Function,
                            // so we'll just add basic type information if available
                            ss << " ; user function";
                        }
                        
                        ss << "\n";
                    }
                    
                    ss << "}\n";
                }
            }
        }
    }
    
    return ss.str();
}

std::string Disassembler::disassemble_instruction(const LIR_Inst& inst) const {
    std::string result = inst.to_string();
    
    // Add debug info if enabled
    if (show_debug_info) {
        auto it = func.debug_info.var_names.find(inst.dst);
        if (it != func.debug_info.var_names.end()) {
            result += " ; " + it->second;
        }
        
        // Add register type information
        std::vector<std::pair<Reg, std::string>> reg_types;
        
        // Get type for destination register
        if (inst.dst != 0) {
            LIR::Type dst_type = func.get_register_abi_type(inst.dst);
            if (dst_type != LIR::Type::Void) {
                reg_types.push_back({inst.dst, type_to_string(dst_type)});
            }
        }
        
        // Get types for source registers
        if (inst.a != 0) {
            LIR::Type a_type = func.get_register_abi_type(inst.a);
            if (a_type != LIR::Type::Void) {
                reg_types.push_back({inst.a, type_to_string(a_type)});
            }
        }
        
        if (inst.b != 0) {
            LIR::Type b_type = func.get_register_abi_type(inst.b);
            if (b_type != LIR::Type::Void) {
                reg_types.push_back({inst.b, type_to_string(b_type)});
            }
        }
        
        // Add type information to output
        if (!reg_types.empty()) {
            result += " [types: ";
            for (size_t i = 0; i < reg_types.size(); ++i) {
                if (i > 0) result += ", ";
                result += "r" + std::to_string(reg_types[i].first) + ":" + reg_types[i].second;
            }
            result += "]";
        }
    }
    
    return result;
}

bool Optimizer::optimize() {
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

bool Optimizer::peephole_optimize() {
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

bool Optimizer::constant_folding() {
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

bool Optimizer::dead_code_elimination() {
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
