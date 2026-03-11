#include "lir.hh"
#include "function_registry.hh"
#include "functions.hh"
#include <iomanip>
#include <sstream>
#include <set>
#include <unordered_set>

namespace LM {
namespace LIR {


std::string Disassembler::disassemble() const {
    std::stringstream ss;
    
    // Main function header
    ss << "fn " << func.name << "(";
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
    
    // Show user-defined functions that are actually called AND task functions
    auto& function_registry = FunctionRegistry::getInstance();
    
    // Get all registered function names
    auto all_function_names = function_registry.getFunctionNames();
    bool has_user_functions = false;
    
    // First show called functions (original behavior)
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
                    has_user_functions = true;
                    // Create a temporary disassembler for this function
                    Disassembler func_disassemble(*lir_func, show_debug_info);
                    
                    // Get the disassembly but remove recursive call to avoid infinite loop
                    ss << "\nfn " << lir_func->name << "(";
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
    
    // Also show task functions (even if not called directly)
    if (!all_function_names.empty()) {
        bool has_task_functions = false;
        bool has_worker_functions = false;
        for (const auto& func_name : all_function_names) {
            // Check if this is a task function (starts with "task_")
            if (func_name.find("task_") == 0) {
                auto lir_func = function_registry.getFunction(func_name);
                if (lir_func && !lir_func->instructions.empty()) {
                    if (!has_task_functions) {
                        ss << "\n=== Task Functions ===\n";
                        has_task_functions = true;
                    }
                    
                    // Create a temporary disassembler for this task function
                    Disassembler func_disassemble(*lir_func, show_debug_info);
                    
                    // Task function header
                    ss << "\nfn " << lir_func->name << "() {\n";
                    
                    // Task function instructions
                    for (size_t i = 0; i < lir_func->instructions.size(); ++i) {
                        const auto& inst = lir_func->instructions[i];
                        ss << "  " << i << ": " << func_disassemble.disassemble_instruction(inst) << "\n";
                    }
                    
                    ss << "}\n";
                }
            }
            // Check if this is a worker function (starts with "worker_")
            else if (func_name.find("worker_") == 0) {
                auto lir_func = function_registry.getFunction(func_name);
                if (lir_func && !lir_func->instructions.empty()) {
                    if (!has_worker_functions) {
                        ss << "\n=== Worker Functions ===\n";
                        has_worker_functions = true;
                    }
                    
                    // Create a temporary disassembler for this worker function
                    Disassembler func_disassemble(*lir_func, show_debug_info);
                    
                    // Worker function header
                    ss << "\nfn " << lir_func->name << "() {\n";
                    
                    // Worker function instructions
                    for (size_t i = 0; i < lir_func->instructions.size(); ++i) {
                        const auto& inst = lir_func->instructions[i];
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
                    ss << "\nfn " << func_name << "(";
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

    Verifier verifier(func);
    if (!verifier.verify()) {
        return false;
    }
    
    if (func.optimizations.enable_peephole) {
        changed |= peephole_optimize();
    }
    
    if (func.optimizations.enable_const_fold) {
        changed |= constant_folding();
    }

    if (func.optimizations.enable_peephole) {
        changed |= copy_propagation();
    }

    if (func.optimizations.enable_dead_code_elim) {
        changed |= dead_store_elimination();
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

bool Optimizer::copy_propagation() {
    bool changed = false;
    std::unordered_map<Reg, Reg> aliases;

    for (auto& inst : func.instructions) {
        auto resolve_alias = [&aliases](Reg reg) {
            auto it = aliases.find(reg);
            while (it != aliases.end() && it->second != reg) {
                reg = it->second;
                it = aliases.find(reg);
            }
            return reg;
        };

        Reg resolved_a = resolve_alias(inst.a);
        if (resolved_a != inst.a) {
            inst.a = resolved_a;
            changed = true;
        }

        Reg resolved_b = resolve_alias(inst.b);
        if (resolved_b != inst.b) {
            inst.b = resolved_b;
            changed = true;
        }

        if (inst.op == LIR_Op::Mov || inst.op == LIR_Op::Copy) {
            aliases[inst.dst] = resolve_alias(inst.a);
        } else if (inst.dst != 0) {
            aliases.erase(inst.dst);
        }
    }

    return changed;
}

bool Optimizer::dead_store_elimination() {
    bool changed = false;
    std::unordered_set<Reg> live;

    auto has_side_effect = [](LIR_Op op) {
        return op == LIR_Op::Store || op == LIR_Op::CallVoid || op == LIR_Op::CallBuiltin ||
               op == LIR_Op::CallVariadic || op == LIR_Op::Return || op == LIR_Op::Ret ||
               op == LIR_Op::Jump || op == LIR_Op::JumpIf || op == LIR_Op::JumpIfFalse;
    };

    for (auto it = func.instructions.rbegin(); it != func.instructions.rend();) {
        const bool writes_reg = (it->dst != 0);
        const bool needed_write = !writes_reg || live.find(it->dst) != live.end();

        if (!needed_write && !has_side_effect(it->op)) {
            it = std::reverse_iterator(func.instructions.erase(std::next(it).base()));
            changed = true;
            continue;
        }

        if (writes_reg) {
            live.erase(it->dst);
        }

        if (it->a != 0) live.insert(it->a);
        if (it->b != 0) live.insert(it->b);
        ++it;
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

bool Verifier::check_register_in_range(Reg reg) const {
    return reg == 0 || reg < func.register_count;
}

bool Verifier::check_uses_and_defs() {
    std::vector<bool> defined(func.register_count, false);
    for (uint32_t i = 0; i < func.param_count && i < func.register_count; ++i) {
        defined[i] = true;
    }

    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];

        if (!check_register_in_range(inst.dst) || !check_register_in_range(inst.a) || !check_register_in_range(inst.b)) {
            error_ = "register out of range at instruction " + std::to_string(i);
            return false;
        }

        if (inst.a != 0 && !defined[inst.a]) {
            error_ = "use before def (a) at instruction " + std::to_string(i);
            return false;
        }
        if (inst.b != 0 && !defined[inst.b]) {
            error_ = "use before def (b) at instruction " + std::to_string(i);
            return false;
        }

        if (inst.dst != 0 && inst.op != LIR_Op::Store && inst.op != LIR_Op::Jump &&
            inst.op != LIR_Op::JumpIf && inst.op != LIR_Op::JumpIfFalse && inst.op != LIR_Op::CallVoid) {
            defined[inst.dst] = true;
        }
    }

    return true;
}

bool Verifier::check_jump_targets() const {
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
            if (inst.imm >= func.instructions.size()) {
                return false;
            }
        }
    }
    return true;
}

bool Verifier::check_return_shape() const {
    if (func.instructions.empty()) {
        return true;
    }
    for (const auto& inst : func.instructions) {
        if ((inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret) && inst.b != 0) {
            return false;
        }
    }
    return true;
}

bool Verifier::check_type_consistency() const {
    for (size_t i = 0; i < func.instructions.size(); ++i) {
        const auto& inst = func.instructions[i];
        if (inst.dst == 0 || inst.result_type == Type::Void) {
            continue;
        }

        Type known = func.get_register_abi_type(inst.dst);
        if (known != Type::Void && known != inst.result_type) {
            return false;
        }
    }
    return true;
}

bool Verifier::verify() {
    error_.clear();
    if (!check_uses_and_defs()) {
        return false;
    }
    if (!check_jump_targets()) {
        error_ = "invalid jump target";
        return false;
    }
    if (!check_return_shape()) {
        error_ = "invalid return instruction shape";
        return false;
    }
    if (!check_type_consistency()) {
        error_ = "register ABI type mismatch";
        return false;
    }
    return true;
}

} // namespace LIR
} // namespace LM
