#ifndef JIT_H
#define JIT_H

#include "../../lir/lir.hh"
#include <libgccjit++.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <chrono>  

namespace JIT {

// Compilation modes
enum class CompileMode {
    ToMemory,    // Keep in memory for immediate execution
    ToFile,      // Compile to object file
    ToExecutable // Compile to executable
};

// Compilation result
struct CompileResult {
    bool success;
    std::string error_message;
    
    // For memory compilation
    void* compiled_function;
    
    // For file compilation
    std::string output_file;
    
    CompileResult() : success(false), compiled_function(nullptr) {}
};

class JITBackend {
public:
    JITBackend();
    ~JITBackend();

    // Main compilation methods
    void process_function(const LIR::LIR_Function& function);
    CompileResult compile(CompileMode mode = CompileMode::ToMemory, 
                         const std::string& output_path = "");
    
    // Execute compiled function (memory mode only)
    int execute_compiled_function(const std::vector<int>& args = {});
    
    // Debug and optimization
    void enable_optimizations(bool enable = true);
    void set_debug_mode(bool debug = true);
    
    // Get compilation statistics
    struct Stats {
        size_t functions_compiled;
        size_t instructions_compiled;
        double compilation_time_ms;
    };
    Stats get_stats() const;

private:
    // JIT compilation methods
    void compile_function(const LIR::LIR_Function& function);
    gccjit::rvalue compile_instruction(const LIR::LIR_Inst& inst);
    
    // Register management for JIT
    std::unordered_map<LIR::Reg, gccjit::lvalue> jit_registers;
    gccjit::lvalue get_jit_register(LIR::Reg reg);
    void set_jit_register(LIR::Reg reg, gccjit::lvalue value);
    
    // libgccjit context
    gccjit::context m_context;
    gccjit::function m_current_func;
    gccjit::block m_current_block;
    
    // Types
    gccjit::type m_void_type;
    gccjit::type m_int_type;
    gccjit::type m_double_type;
    gccjit::type m_bool_type;
    gccjit::type m_const_char_ptr_type;
    gccjit::type m_void_ptr_type;
    
    // Standard library functions
    gccjit::function m_printf_func;
    gccjit::function m_malloc_func;
    gccjit::function m_free_func;
    gccjit::function m_puts_func;
    
    // Helper methods
    gccjit::rvalue convert_to_jit_type(gccjit::rvalue value, gccjit::type target_type);
    
    // Basic operations implementation
    gccjit::rvalue compile_arithmetic_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b);
    gccjit::rvalue compile_comparison_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b);
    gccjit::rvalue compile_bitwise_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b);
    
    // Control flow
    void compile_jump(const LIR::LIR_Inst& inst);
    void compile_conditional_jump(const LIR::LIR_Inst& inst);
    void compile_call(const LIR::LIR_Inst& inst);
    void compile_print(const LIR::LIR_Inst& inst);
    void compile_return(const LIR::LIR_Inst& inst);
    
    // Memory operations
    void compile_memory_op(const LIR::LIR_Inst& inst);
    
    // String operations
    gccjit::rvalue compile_string_concat(gccjit::rvalue a, gccjit::rvalue b);
    
    // Error handling
    void report_error(const std::string& message);
    bool has_errors() const;
    std::vector<std::string> get_errors() const;
    
    // Configuration
    bool m_optimizations_enabled;
    bool m_debug_mode;
    
    // State
    std::vector<std::string> errors;
    std::vector<LIR::LIR_Function> processed_functions;
    void* m_compiled_function;
    
    // Statistics
    Stats m_stats;
    
    // Helper for timing
    class Timer {
        std::chrono::high_resolution_clock::time_point start;
    public:
        Timer() : start(std::chrono::high_resolution_clock::now()) {}
        double elapsed_ms() const {
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double, std::milli>(end - start).count();
        }
    };
};

} // namespace JIT

#endif // JIT_H
