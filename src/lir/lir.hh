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
#include "../backend/types.hh"

namespace LIR {

// Register and Immediate types
using Reg = uint32_t;
using Imm = uint32_t;

// Single type system for both LIR and JIT (ABI-level types)
enum class Type : uint8_t {
    // Primitive types
    I32,
    I64, 
    F64,
    Bool,
    
    // Pointer types
    Ptr,
    
    // Special types
    Void
};

// Convert Type to string
std::string type_to_string(Type type);

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
    JumpIf,     // Jump if condition is true
    Label,      // Label definition for jump targets
    Call,       // Function call (reg = call(func_id, params...))
    Return,     // Return (return from function)
    
    // Function definition operations
    FuncDef,    // Function definition (fn name, return_reg)
    Param,      // Parameter definition (param reg)
    Ret,        // Function return with register (ret reg)
    
    // Typed print operations
    PrintInt,   // Print integer (print_int(reg))
    PrintUint,   // Print unsigned integer (print_uint(reg))
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
    Concat,     // String concatenation (legacy)
    STR_CONCAT, // Explicit string concatenation (+)
    STR_FORMAT, // String formatting (interpolation)
    
    // Error handling
    ConstructError,
    ConstructOk,
    IsError,     // Check if Result contains an error
    Unwrap,      // Unwrap Result value (panic if error)
    UnwrapOr,    // Unwrap with default value
    
    // Atomic operations
    AtomicLoad,
    AtomicStore,
    AtomicFetchAdd,
    
    // Concurrency
    Await,
    AsyncCall,
    
    // === THREADLESS CONCURRENCY ===
    
    // Task management (pure data structures)
    TaskContextAlloc,    // Allocate task context array
    TaskContextInit,     // Initialize a task context
    TaskGetState,        // Get current state from context
    TaskSetState,        // Set new state in context
    TaskSetField,        // Set arbitrary field in context (sleep_until, counter, etc.)
    TaskGetField,        // Get arbitrary field from context
    
    // Simple channel (no locks, single-threaded)
    ChannelAlloc,        // Allocate channel buffer
    ChannelPush,         // Push value (no blocking)
    ChannelPop,          // Pop value (no blocking)
    ChannelHasData,      // Check if channel has data
    
    // Scheduler control
    SchedulerInit,       // Initialize scheduler
    SchedulerRun,        // Run scheduler loop (returns when all done)
    SchedulerTick,       // Single scheduler tick
    
    // Time (bare metal compatible)
    GetTickCount,        // Get monotonic tick counter
    DelayUntil,          // Check if delay expired (non-blocking)
    
    // === LOCK-FREE PARALLEL OPERATIONS ===
    WorkQueueAlloc,      // Allocate lock-free work queue
    WorkQueuePush,       // Push task to queue (atomic)
    WorkQueuePop,        // Pop task from queue (atomic)
    ParallelWaitComplete,// Wait for all workers to complete
    WorkerSignal,        // Signal workers to start
    WorkerJoin,          // Wait for workers to finish
    
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

// Source location for debugging
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

// LIR Instruction structure (typed)
struct LIR_Inst {
    LIR_Op op;             // Operation
    Type result_type;      // Type of the result register (ABI-level)
    Reg dst;               // Destination register
    Reg a;                 // Operand 1 (source register)
    Reg b;                 // Operand 2 (source register, optional)
    Imm imm;               // Immediate value (optional, for constants or jump targets)
    ValuePtr const_val;    // Constant value (for LoadConst operations)
    
    // Debug information
    std::string comment;
    LIR_SourceLoc loc;
    
    LIR_Inst(LIR_Op op, Type result_type, Reg dst = 0, Reg a = 0, Reg b = 0, Imm imm = 0)
        : op(op), result_type(result_type), dst(dst), a(a), b(b), imm(imm) {}
    
    LIR_Inst(LIR_Op op, Type result_type, Reg dst, ValuePtr constant)
        : op(op), result_type(result_type), dst(dst), a(0), b(0), imm(0), const_val(constant) {}
    
    // Legacy constructors for backward compatibility
    LIR_Inst(LIR_Op op, Reg dst = 0, Reg a = 0, Reg b = 0, Imm imm = 0)
        : op(op), result_type(Type::Void), dst(dst), a(a), b(b), imm(imm) {}
    
    LIR_Inst(LIR_Op op, Reg dst, ValuePtr constant)
        : op(op), result_type(Type::Void), dst(dst), a(0), b(0), imm(0), const_val(constant) {}
    
    // Check if this instruction is a return instruction
    bool isReturn() const {
        return op == LIR_Op::Return || op == LIR_Op::Ret;
    }
    
    std::string to_string() const;
};

// Forward declaration
struct LIR_Inst;

// Basic Block for CFG
struct LIR_BasicBlock {
    uint32_t id;                     // Unique block identifier
    std::string label;               // Optional label for debugging
    std::vector<LIR_Inst> instructions; // Instructions in this block
    std::vector<uint32_t> successors; // Successor block IDs
    std::vector<uint32_t> predecessors; // Predecessor block IDs
    bool is_entry;                   // Is this the entry block?
    bool is_exit;                    // Is this the exit block?
    bool terminated;                 // Explicitly marked as terminated
    
    LIR_BasicBlock(uint32_t id, const std::string& label = "") 
        : id(id), label(label), is_entry(false), is_exit(false), terminated(false) {}
    
    // Add instruction to block
    void add_instruction(const LIR_Inst& inst) {
        instructions.push_back(inst);
    }
    
    // Add successor edge
    void add_successor(uint32_t block_id) {
        successors.push_back(block_id);
    }
    
    // Add predecessor edge
    void add_predecessor(uint32_t block_id) {
        predecessors.push_back(block_id);
    }
    
    // Check if block has terminator (last instruction is control flow)
    bool has_terminator() const {
        if (terminated) return true;
        if (instructions.empty()) return false;
        const auto& last = instructions.back();
        return last.op == LIR_Op::Jump || 
               last.op == LIR_Op::JumpIfFalse || 
               last.op == LIR_Op::Return;
    }
};

// Control Flow Graph
class LIR_CFG {
public:
    std::vector<std::unique_ptr<LIR_BasicBlock>> blocks;
    uint32_t entry_block_id;
    uint32_t exit_block_id;
    uint32_t next_block_id;
    
    LIR_CFG() : entry_block_id(0), exit_block_id(UINT32_MAX), next_block_id(0) {}
    
    // Create new basic block
    LIR_BasicBlock* create_block(const std::string& label = "") {
        auto block = std::make_unique<LIR_BasicBlock>(next_block_id++, label);
        LIR_BasicBlock* block_ptr = block.get();
        blocks.push_back(std::move(block));
        return block_ptr;
    }
    
    // Get block by ID
    LIR_BasicBlock* get_block(uint32_t id) {
        if (id < blocks.size()) {
            return blocks[id].get();
        }
        return nullptr;
    }
    
    // Add edge between blocks
    void add_edge(uint32_t from_id, uint32_t to_id) {
        LIR_BasicBlock* from = get_block(from_id);
        LIR_BasicBlock* to = get_block(to_id);
        if (from && to) {
            from->add_successor(to_id);
            to->add_predecessor(from_id);
        }
    }
    
    // Validate CFG structure
    bool validate() const;
    void dump_dot() const; // For debugging
};

// Source location information
// Debug information for a function
struct LIR_DebugInfo {
    std::string function_name;
    LIR_SourceLoc loc;
    std::unordered_map<uint32_t, std::string> var_names; // reg -> name
    std::unordered_map<uint32_t, LIR_SourceLoc> reg_defs; // reg -> definition location
};

// LIR Instruction Structure (register-based)
// Register allocation context
class LIR_FunctionContext {
public:
    std::unordered_map<std::string, Reg> variable_to_reg;
    std::unordered_map<Reg, Type> register_types;  // ABI-level types for registers
    std::unordered_map<Reg, TypePtr> register_language_types; // Language types for reference
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

    void set_register_type(Reg reg, Type abi_type) {
        register_types[reg] = abi_type;
    }

    void set_register_language_type(Reg reg, TypePtr lang_type) {
        register_language_types[reg] = lang_type;
    }

    Type get_register_type(Reg reg) const {
        auto it = register_types.find(reg);
        return (it != register_types.end()) ? it->second : Type::Void;
    }

    TypePtr get_register_language_type(Reg reg) const {
        auto it = register_language_types.find(reg);
        return (it != register_language_types.end()) ? it->second : nullptr;
    }

    // Legacy method for backward compatibility
    void set_register_type_legacy(Reg reg, TypePtr type) {
        // Convert legacy TypePtr to Type if needed
        register_types[reg] = Type::I64; // Default
    }

    TypePtr get_register_type_legacy(Reg reg) const {
        // Return nullptr since we're moving away from TypePtr
        return nullptr;
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
struct OptimizationFlags {
    bool enable_peephole : 1;
    bool enable_const_fold : 1;
    bool enable_dead_code_elim : 1;
    
    OptimizationFlags() : 
        enable_peephole(false), 
        enable_const_fold(false), 
        enable_dead_code_elim(false) {}
};

// LIR Function with register allocation, debug info, and CFG
class LIR_Function {
public:
    std::string name;
    std::vector<LIR_Inst> instructions; // Keep for backward compatibility
    std::unique_ptr<LIR_CFG> cfg;       // New CFG structure
    uint32_t param_count;
    uint32_t register_count;
    LIR_DebugInfo debug_info;
    OptimizationFlags optimizations;
    
    // Variable to register mapping
    std::unordered_map<std::string, Reg> variable_to_reg;
    std::unordered_map<Reg, Type> register_types;    // ABI-level types for registers
    std::unordered_map<Reg, TypePtr> register_language_types; // Language types for reference

    LIR_Function(const std::string& name, uint32_t param_count = 0)
        : name(name), param_count(param_count), register_count(0), cfg(std::make_unique<LIR_CFG>()) {
        // Ensure the name is properly initialized
        this->name = name;
    }
    
    // Add copy constructor and assignment operator to prevent shallow copies
    LIR_Function(const LIR_Function& other) 
        : name(other.name),
          instructions(other.instructions),
          cfg(other.cfg ? std::make_unique<LIR_CFG>() : nullptr),
          param_count(other.param_count),
          register_count(other.register_count),
          debug_info(other.debug_info),
          optimizations(other.optimizations),
          variable_to_reg(other.variable_to_reg),
          register_types(other.register_types),
          register_language_types(other.register_language_types) {
        // Manually copy CFG blocks if needed
        if (other.cfg && cfg) {
            // Copy basic CFG structure but recreate blocks
            cfg->entry_block_id = other.cfg->entry_block_id;
            cfg->exit_block_id = other.cfg->exit_block_id;
            cfg->next_block_id = other.cfg->next_block_id;
            // Note: We don't copy the blocks themselves since they contain unique_ptr
        }
    }
          
    LIR_Function& operator=(const LIR_Function& other) {
        if (this != &other) {
            name = other.name;
            instructions = other.instructions;
            cfg = other.cfg ? std::make_unique<LIR_CFG>() : nullptr;
            param_count = other.param_count;
            register_count = other.register_count;
            debug_info = other.debug_info;
            optimizations = other.optimizations;
            variable_to_reg = other.variable_to_reg;
            register_types = other.register_types;
            register_language_types = other.register_language_types;
            
            // Manually copy CFG structure if needed
            if (other.cfg && cfg) {
                cfg->entry_block_id = other.cfg->entry_block_id;
                cfg->exit_block_id = other.cfg->exit_block_id;
                cfg->next_block_id = other.cfg->next_block_id;
                // Note: We don't copy the blocks themselves since they contain unique_ptr
            }
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
        // Legacy method - convert to ABI type
        register_types[reg] = Type::I64;
    }

    TypePtr get_register_type(Reg reg) const {
        // Legacy method - return nullptr since we're moving away from TypePtr
        return nullptr;
    }

    // New simplified methods
    void set_register_abi_type(Reg reg, Type abi_type) {
        register_types[reg] = abi_type;
    }

    void set_register_language_type(Reg reg, TypePtr lang_type) {
        register_language_types[reg] = lang_type;
    }

    Type get_register_abi_type(Reg reg) const {
        auto it = register_types.find(reg);
        return (it != register_types.end()) ? it->second : Type::Void;
    }

    TypePtr get_register_language_type(Reg reg) const {
        auto it = register_language_types.find(reg);
        return (it != register_language_types.end()) ? it->second : nullptr;
    }

    // Instruction emission
    void add_instruction(const LIR_Inst& inst) {
        instructions.push_back(inst);
    }
    
    std::string to_string() const;
};

// Disassembler
class Disassembler {
    const LIR_Function& func;
    bool show_debug_info;
    
public:
    Disassembler(const LIR_Function& f, bool debug = false) 
        : func(f), show_debug_info(debug) {}
        
    std::string disassemble() const;
    std::string disassemble_instruction(const LIR_Inst& inst) const;
};

// Optimizer
class Optimizer {
    LIR_Function& func;
    
    bool peephole_optimize();
    bool constant_folding();
    bool dead_code_elimination();
    
public:
    Optimizer(LIR_Function& f) : func(f) {}
    
    // Run all enabled optimizations
    bool optimize();
    
    // Enable/disable specific optimizations
    void set_optimization_flags(const OptimizationFlags& flags) {
        func.optimizations = flags;
    }
};

// Utility functions
std::string lir_op_to_string(LIR_Op op);
std::string type_to_string(Type type);

// Type conversion utilities (simplified)
Type language_type_to_abi_type(TypePtr lang_type);

} // namespace LIR

#endif // LIR_H
