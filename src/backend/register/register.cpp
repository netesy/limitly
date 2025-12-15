#include "register.hh"
#include <iostream>
#include <stdexcept>

namespace Register {

RegisterVM::RegisterVM() : ip(0) {
    // Initialize registers with nil values
    registers.resize(1024, nullptr);
}

void RegisterVM::execute_function(const LIR::LIR_Function& function) {
    reset();
    
    // Execute instructions sequentially
    while (ip < function.instructions.size()) {
        const LIR_Inst& inst = function.instructions[ip];
        
        // Handle jumps by modifying ip
        if (inst.op == LIR_Op::Jump) {
            ip = inst.imm;
            continue;
        } else if (inst.op == LIR_Op::JumpIfFalse) {
            bool condition = to_bool(get_register(inst.a));
            if (!condition) {
                ip = inst.imm;
            } else {
                ip++;
            }
            continue;
        } else if (inst.op == LIR_Op::Return) {
            break;
        }
        
        execute_instruction(inst);
        ip++;
    }
}

Register::RegisterValue RegisterVM::execute_instruction(const LIR::LIR_Inst& inst) {
    switch (inst.op) {
        case LIR_Op::Mov:
            set_register(inst.dst, get_register(inst.a));
            break;
            
        case LIR_Op::LoadConst:
            if (inst.const_val.kind == LIR_ValueKind::Int) {
                set_register(inst.dst, inst.const_val.i);
            } else if (inst.const_val.kind == LIR_ValueKind::Float) {
                set_register(inst.dst, inst.const_val.f);
            } else if (inst.const_val.kind == LIR_ValueKind::Bool) {
                set_register(inst.dst, inst.const_val.b);
            } else if (inst.const_val.kind == LIR_ValueKind::String) {
                set_register(inst.dst, std::string(inst.const_val.s));
            } else if (inst.const_val.kind == LIR_ValueKind::Nil) {
                set_register(inst.dst, nullptr);
            }
            break;
            
        case LIR_Op::Add:
        case LIR_Op::Sub:
        case LIR_Op::Mul:
        case LIR_Op::Div:
        case LIR_Op::Mod:
        case LIR_Op::And:
        case LIR_Op::Or:
        case LIR_Op::Xor:
            set_register(inst.dst, perform_binary_op(inst.op, get_register(inst.a), get_register(inst.b)));
            break;
            
        case LIR_Op::CmpEQ:
        case LIR_Op::CmpNEQ:
        case LIR_Op::CmpLT:
        case LIR_Op::CmpLE:
        case LIR_Op::CmpGT:
        case LIR_Op::CmpGE: {
            bool result = perform_comparison(inst.op, get_register(inst.a), get_register(inst.b));
            set_register(inst.dst, result);
            break;
        }
        
        case LIR_Op::Call:
            // Simplified call handling
            std::cout << "Call to function in register r" << inst.a << std::endl;
            set_register(inst.dst, nullptr);
            break;
            
        case LIR_Op::Load:
        case LIR_Op::Store:
            // Placeholder for memory operations
            break;
            
        case LIR_Op::Cast:
            // Type casting (placeholder)
            set_register(inst.dst, get_register(inst.a));
            break;
            
        case LIR_Op::Concat: {
            std::string a_str = to_string(get_register(inst.a));
            std::string b_str = to_string(get_register(inst.b));
            set_register(inst.dst, a_str + b_str);
            break;
        }
        
        case LIR_Op::Nop:
            // No operation
            break;
            
        default:
            std::cerr << "Unsupported LIR operation: " << static_cast<int>(inst.op) << std::endl;
            break;
    }
    
    return get_register(inst.dst);
}

const Register::RegisterValue& RegisterVM::get_register(LIR::Reg reg) const {
    if (reg >= registers.size()) {
        static RegisterValue nil_value = nullptr;
        return nil_value;
    }
    return registers[reg];
}

void RegisterVM::set_register(LIR::Reg reg, const RegisterValue& value) {
    if (reg >= registers.size()) {
        registers.resize(reg + 1, nullptr);
    }
    registers[reg] = value;
}

void RegisterVM::reset() {
    std::fill(registers.begin(), registers.end(), nullptr);
    ip = 0;
}

std::string RegisterVM::register_value_to_string(const RegisterValue& value) const {
    if (std::holds_alternative<int64_t>(value)) {
        return std::to_string(std::get<int64_t>(value));
    } else if (std::holds_alternative<double>(value)) {
        return std::to_string(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    } else if (std::holds_alternative<std::string>(value)) {
        return "\"" + std::get<std::string>(value) + "\"";
    } else if (std::holds_alternative<std::nullptr_t>(value)) {
        return "nil";
    }
    return "unknown";
}

Register::RegisterValue RegisterVM::perform_binary_op(LIR::LIR_Op op, const RegisterValue& a, const RegisterValue& b) {
    if (is_numeric(a) && is_numeric(b)) {
        double a_val = to_float(a);
        double b_val = to_float(b);
        
        switch (op) {
            case LIR_Op::Add: return a_val + b_val;
            case LIR_Op::Sub: return a_val - b_val;
            case LIR_Op::Mul: return a_val * b_val;
            case LIR_Op::Div: return b_val != 0 ? a_val / b_val : 0.0;
            case LIR_Op::Mod: {
                int64_t a_int = to_int(a);
                int64_t b_int = to_int(b);
                return b_int != 0 ? a_int % b_int : 0;
            }
            case LIR_Op::And: return to_int(a) & to_int(b);
            case LIR_Op::Or: return to_int(a) | to_int(b);
            case LIR_Op::Xor: return to_int(a) ^ to_int(b);
            default: break;
        }
    } else if (op == LIR_Op::And || op == LIR_Op::Or) {
        // Logical operations
        bool a_bool = to_bool(a);
        bool b_bool = to_bool(b);
        return (op == LIR_Op::And) ? a_bool && b_bool : a_bool || b_bool;
    }
    
    return nullptr;
}

Register::RegisterValue RegisterVM::perform_unary_op(LIR::LIR_Op op, const RegisterValue& a) {
    if (op == LIR_Op::Sub && is_numeric(a)) {
        return -to_float(a);
    }
    // Add other unary operations as needed
    return a;
}

bool RegisterVM::perform_comparison(LIR::LIR_Op op, const RegisterValue& a, const RegisterValue& b) {
    if (is_numeric(a) && is_numeric(b)) {
        double a_val = to_float(a);
        double b_val = to_float(b);
        
        switch (op) {
            case LIR_Op::CmpEQ: return a_val == b_val;
            case LIR_Op::CmpNEQ: return a_val != b_val;
            case LIR_Op::CmpLT: return a_val < b_val;
            case LIR_Op::CmpLE: return a_val <= b_val;
            case LIR_Op::CmpGT: return a_val > b_val;
            case LIR_Op::CmpGE: return a_val >= b_val;
            default: return false;
        }
    } else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b)) {
        const std::string& a_str = std::get<std::string>(a);
        const std::string& b_str = std::get<std::string>(b);
        
        switch (op) {
            case LIR_Op::CmpEQ: return a_str == b_str;
            case LIR_Op::CmpNEQ: return a_str != b_str;
            case LIR_Op::CmpLT: return a_str < b_str;
            case LIR_Op::CmpLE: return a_str <= b_str;
            case LIR_Op::CmpGT: return a_str > b_str;
            case LIR_Op::CmpGE: return a_str >= b_str;
            default: return false;
        }
    }
    
    return false;
}

bool RegisterVM::is_numeric(const RegisterValue& value) const {
    return std::holds_alternative<int64_t>(value) || std::holds_alternative<double>(value);
}

int64_t RegisterVM::to_int(const RegisterValue& value) const {
    if (std::holds_alternative<int64_t>(value)) {
        return std::get<int64_t>(value);
    } else if (std::holds_alternative<double>(value)) {
        return static_cast<int64_t>(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1 : 0;
    }
    return 0;
}

double RegisterVM::to_float(const RegisterValue& value) const {
    if (std::holds_alternative<double>(value)) {
        return std::get<double>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        return static_cast<double>(std::get<int64_t>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1.0 : 0.0;
    }
    return 0.0;
}

bool RegisterVM::to_bool(const RegisterValue& value) const {
    if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        return std::get<int64_t>(value) != 0;
    } else if (std::holds_alternative<double>(value)) {
        return std::get<double>(value) != 0.0;
    } else if (std::holds_alternative<std::string>(value)) {
        return !std::get<std::string>(value).empty();
    }
    return false;
}

std::string RegisterVM::to_string(const RegisterValue& value) const {
    return register_value_to_string(value);
}

} // namespace Register
