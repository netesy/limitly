#ifndef LIR_H
#define LIR_H

#include <vector>
#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include "../backend/value.hh"

namespace LIR {

// Register and Immediate types
using Reg = uint32_t;
using Imm = uint32_t;

// LIR Operations (following the register-based design)
enum class LIR_Op : uint8_t {
    // Move and constants
    Mov,        // Move (reg = reg)
    LoadConst,  // Load constant into register (reg = ValuePtr)
    
    // Arithmetic operations
    Add,        // Add (reg = reg1 + reg2)
    Sub,        // Subtract (reg = reg1 - reg2)
    Mul,        // Multiply (reg = reg1 * reg2)
    Div,        // Divide (reg = reg1 / reg2)
    Mod,        // Modulo (reg = reg1 % reg2)
    Neg,        // Negate (reg = -reg1)
    
    // Bitwise operations
    And,        // Bitwise AND (reg = reg1 & reg2)
    Or,         // Bitwise OR (reg = reg1 | reg2)
    Xor,        // Bitwise XOR (reg = reg1 ^ reg2)
    
    // Comparison operations
    CmpEQ,      // Compare Equal (reg = reg1 == reg2)
    CmpNEQ,     // Compare Not Equal (reg = reg1 != reg2)
    CmpLT,      // Compare Less Than (reg = reg1 < reg2)
    CmpLE,      // Compare Less Than or Equal (reg = reg1 <= reg2)
    CmpGT,      // Compare Greater Than (reg = reg1 > reg2)
    CmpGE,      // Compare Greater Than or Equal (reg = reg1 >= reg2)
    
    // Control flow
    Jump,       // Unconditional jump (jump to label)
    JumpIfFalse,// Jump if condition is false
    Call,       // Function call (reg = call(func_id, params...))
    Return,     // Return (return from function)
    
    // Typed print operations
    PrintInt,   // Print integer (print_int(reg))
    PrintFloat, // Print float (print_float(reg))
    PrintBool,  // Print boolean (print_bool(reg))
    PrintString,// Print string (print_string(reg))
    
    Nop,        // No operation (debugging)
    
    // Memory operations
    Load,       // Load from memory
    Store,      // Store to memory
    
    // Type operations
    Cast,       // Type casting
    ToString,   // Convert value to string representation
    
    // String operations
    Concat,     // String concatenation
    
    // String builder operations
    SBCreate,   // Create string builder
    SBAppend,   // Append string/value to builder
    SBFinish,   // Finish building string
    
    // Error handling
    ConstructError,
    ConstructOk,
    
    // Atomic operations
    AtomicLoad,
    AtomicStore,
    AtomicFetchAdd,
    
    // Concurrency
    Await,
    AsyncCall,
    
    // List/Collection operations
    ListCreate,
    ListAppend,
    ListIndex,
    
    // Class operations
    NewObject,
    GetField,
    SetField,
    
    // Module operations
    ImportModule,
    ExportSymbol,
    BeginModule,
    EndModule
};

// Source location information
struct LIR_SourceLoc {
    std::string filename;
    uint32_t line;
    uint32_t column;
    
    LIR_SourceLoc() : line(0), column(0) {}
    LIR_SourceLoc(const std::string& file, uint32_t ln, uint32_t col = 0)
        : filename(file), line(ln), column(col) {}
    
    std::string to_string() const {
        std::stringstream ss;
        ss << filename << ":" << line;
        if (column > 0) ss << ":" << column;
        return ss.str();
    }
};

// Debug information for a function
struct LIR_DebugInfo {
    std::string function_name;
    LIR_SourceLoc loc;
    std::unordered_map<uint32_t, std::string> var_names; // reg -> name
    std::unordered_map<uint32_t, LIR_SourceLoc> reg_defs; // reg -> definition location
};

// LIR Instruction Structure (register-based)
struct LIR_Inst {
    LIR_Op op;     // Operation
    Reg dst;       // Destination register
    Reg a;         // Operand 1 (source register)
    Reg b;         // Operand 2 (source register, optional)
    Imm imm;       // Immediate value (optional, for constants or jump targets)
    ValuePtr const_val; // Constant value (for LoadConst operations)
    
    // Debug information
    std::string comment;
    LIR_SourceLoc loc;
    
    LIR_Inst(LIR_Op op, Reg dst = 0, Reg a = 0, Reg b = 0, Imm imm = 0)
        : op(op), dst(dst), a(a), b(b), imm(imm) {}
    
    LIR_Inst(LIR_Op op, Reg dst, ValuePtr constant)
        : op(op), dst(dst), a(0), b(0), imm(0), const_val(constant) {}
    
    std::string to_string() const;
};


// Register allocation context
class LIR_FunctionContext {
public:
    std::unordered_map<std::string, Reg> variable_to_reg;
    std::unordered_map<Reg, TypePtr> register_types;
    std::vector<LIR_Inst> instructions;
    uint32_t next_reg = 0;
    
    // Register allocation
    Reg allocate_register() {
        return next_reg++;
    }
    
    // Variable mapping
    Reg get_variable_register(const std::string& name) {
        auto it = variable_to_reg.find(name);
        return (it != variable_to_reg.end()) ? it->second : UINT32_MAX;
    }
    
    void set_variable_register(const std::string& name, Reg reg) {
        variable_to_reg[name] = reg;
    }

    void set_register_type(Reg reg, TypePtr type) {
        register_types[reg] = type;
    }

    TypePtr get_register_type(Reg reg) const {
        auto it = register_types.find(reg);
        return (it != register_types.end()) ? it->second : nullptr;
    }

    // Instruction emission
    void add_instruction(const LIR_Inst& inst) {
        instructions.push_back(inst);
    }
    
    // Utility methods
    Reg new_temp() {
        return allocate_register();
    }
};

// Optimization flags
struct LIR_OptimizationFlags {
    bool enable_peephole : 1;
    bool enable_const_fold : 1;
    bool enable_dead_code_elim : 1;
    
    LIR_OptimizationFlags() : 
        enable_peephole(false), 
        enable_const_fold(false), 
        enable_dead_code_elim(false) {}
};

// LIR Function with register allocation and debug info
class LIR_Function {
public:
    std::string name;
    std::vector<LIR_Inst> instructions;
    uint32_t param_count;
    uint32_t register_count;
    LIR_DebugInfo debug_info;
    LIR_OptimizationFlags optimizations;
    
    // Variable to register mapping
    std::unordered_map<std::string, Reg> variable_to_reg;
    std::unordered_map<Reg, TypePtr> register_types;

    LIR_Function(const std::string& name, uint32_t param_count = 0)
        : name(name), param_count(param_count), register_count(0) {
        // Ensure the name is properly initialized
        this->name = name;
    }
    
    // Add copy constructor and assignment operator to prevent shallow copies
    LIR_Function(const LIR_Function& other) 
        : name(other.name),
          instructions(other.instructions),
          param_count(other.param_count),
          register_count(other.register_count),
          debug_info(other.debug_info),
          optimizations(other.optimizations),
          variable_to_reg(other.variable_to_reg),
          register_types(other.register_types) {}
          
    LIR_Function& operator=(const LIR_Function& other) {
        if (this != &other) {
            name = other.name;
            instructions = other.instructions;
            param_count = other.param_count;
            register_count = other.register_count;
            debug_info = other.debug_info;
            optimizations = other.optimizations;
            variable_to_reg = other.variable_to_reg;
            register_types = other.register_types;
        }
        return *this;
    }
    
    // Register allocation
    Reg allocate_register() {
        return register_count++;
    }
    
    // Variable mapping
    Reg get_variable_register(const std::string& name) const {
        auto it = variable_to_reg.find(name);
        return (it != variable_to_reg.end()) ? it->second : UINT32_MAX;
    }
    
    void set_variable_register(const std::string& name, Reg reg) {
        variable_to_reg[name] = reg;
    }

    void set_register_type(Reg reg, TypePtr type) {
        register_types[reg] = type;
    }

    TypePtr get_register_type(Reg reg) const {
        auto it = register_types.find(reg);
        return (it != register_types.end()) ? it->second : nullptr;
    }

    // Instruction emission
    void add_instruction(const LIR_Inst& inst) {
        instructions.push_back(inst);
    }
    
    std::string to_string() const;
};

// Disassembler
class LIR_Disassembler {
    const LIR_Function& func;
    bool show_debug_info;
    
public:
    LIR_Disassembler(const LIR_Function& f, bool debug = false) 
        : func(f), show_debug_info(debug) {}
        
    std::string disassemble() const;
    std::string disassemble_instruction(const LIR_Inst& inst) const;
};

// Optimizer
class LIR_Optimizer {
    LIR_Function& func;
    
    bool peephole_optimize();
    bool constant_folding();
    bool dead_code_elimination();
    
public:
    LIR_Optimizer(LIR_Function& f) : func(f) {}
    
    // Run all enabled optimizations
    bool optimize();
    
    // Enable/disable specific optimizations
    void set_optimization_flags(const LIR_OptimizationFlags& flags) {
        func.optimizations = flags;
    }
};

// Utility functions
std::string lir_op_to_string(LIR_Op op);

} // namespace LIR

#endif // LIR_H
