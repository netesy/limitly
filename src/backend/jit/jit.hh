#ifndef JIT_H
#define JIT_H

#include "../../lir/lir.hh"
#include "../memory.hh"
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
    CompileResult compile(CompileMode mode = CompileMode::ToMemory, const std::string& output_path = "");
    
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
    void compile_function_single_pass(const LIR::LIR_Function& function);
    gccjit::rvalue compile_instruction(const LIR::LIR_Inst& inst);
    
    // Register management for JIT
    std::unordered_map<LIR::Reg, gccjit::lvalue> jit_registers;
    std::unordered_map<LIR::Reg, gccjit::type> register_types;
    gccjit::lvalue get_jit_register(LIR::Reg reg);
    gccjit::lvalue get_jit_register(LIR::Reg reg, gccjit::type type);
    gccjit::lvalue get_jit_register_temp(gccjit::type type);
    void set_jit_register(LIR::Reg reg, gccjit::lvalue value);
    
    // libgccjit context
    gccjit::context m_context;
    gccjit::function m_current_func;
    gccjit::block m_current_block;
    
    // Types
    gccjit::type m_void_type;
    gccjit::type m_int_type;
    gccjit::type m_uint_type;
    gccjit::type m_double_type;
    gccjit::type m_bool_type;
    gccjit::type m_const_char_ptr_type;
    gccjit::type m_void_ptr_type;
    gccjit::type m_string_builder_type;
    gccjit::type m_c_int_type;
    gccjit::type m_size_t_type;
    gccjit::type m_lm_string_type;
    
    // Standard library functions
    gccjit::function m_printf_func;
    gccjit::function m_malloc_func;
    gccjit::function m_free_func;
    gccjit::function m_puts_func;
    gccjit::function m_strlen_func;
    gccjit::function m_sprintf_func;
    gccjit::function m_snprintf_func;
    gccjit::function m_memset_func;
    gccjit::function m_memcpy_func;
    gccjit::function m_strcat_func;
    gccjit::function m_strcpy_func;
    
    // Runtime utility functions
    gccjit::function m_runtime_concat_func;
    gccjit::function m_runtime_format_func;
    gccjit::function m_get_ticks_func;
    gccjit::function m_jit_mem_allocate_func;
    gccjit::function m_loop_check_func;
    
    // Runtime string functions
    gccjit::function m_lm_string_concat_func;
    gccjit::function m_lm_int_to_string_func;
    gccjit::function m_lm_double_to_string_func;
    gccjit::function m_lm_bool_to_string_func;
    gccjit::function m_lm_string_free_func;
    gccjit::function m_lm_string_from_cstr_func;
    
    // Helper methods
    gccjit::rvalue convert_to_jit_type(gccjit::rvalue value, gccjit::type target_type);
    gccjit::type to_jit_type(TypePtr type);
    gccjit::type to_jit_type(LIR::Type type);
    
    // Basic operations implementation
    gccjit::rvalue compile_arithmetic_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b);
    gccjit::rvalue compile_comparison_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b);
    gccjit::rvalue compile_bitwise_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b);
    
    // String operations
    gccjit::rvalue compile_string_concat(gccjit::rvalue a, gccjit::rvalue b);
    gccjit::rvalue compile_string_format(gccjit::rvalue format, gccjit::rvalue arg);
    gccjit::rvalue compile_to_string(gccjit::rvalue value);
    gccjit::rvalue compile_to_cstring(gccjit::rvalue value);
    gccjit::rvalue convert_to_lm_string(gccjit::rvalue value);
    
    // Control flow
    void compile_jump(const LIR::LIR_Inst& inst);
    void compile_conditional_jump(const LIR::LIR_Inst& inst, size_t current_instruction_pos);
    void compile_call(const LIR::LIR_Inst& inst);
    void compile_print_int(const LIR::LIR_Inst& inst);
    void compile_print_uint(const LIR::LIR_Inst& inst);    
    void compile_print_float(const LIR::LIR_Inst& inst);
    void compile_print_bool(const LIR::LIR_Inst& inst);
    void compile_print_string(const LIR::LIR_Inst& inst);
    void compile_return(const LIR::LIR_Inst& inst);
    
    // Memory operations
    void compile_memory_op(const LIR::LIR_Inst& inst);
    
    // Memory management methods
    void enter_memory_region();
    void exit_memory_region();
    void* allocate_in_region(size_t size, size_t alignment = alignof(std::max_align_t));
    template<typename T, typename... Args>
    T* create_object(Args&&... args);
    void cleanup_memory();
    
    // Error handling
    void report_error(const std::string& message);
    bool has_errors() const;
    std::vector<std::string> get_errors() const;
    
    // Configuration
    bool m_optimizations_enabled;
    bool m_debug_mode;
    
    // Memory management
    MemoryManager<> memory_manager_;
    MemoryManager<>::Region* current_memory_region_ = nullptr;
    
    // State
    std::vector<std::string> errors;
    std::vector<LIR::LIR_Function> processed_functions;
    void* m_compiled_function;
    gcc_jit_result* m_jit_result; // Keep the result alive
    
    // Label to block mapping for jump resolution
    std::unordered_map<uint32_t, gccjit::block> label_blocks;
    
    // Pending jumps that need forward resolution
    struct PendingJump {
        std::string source_block_name;
        uint32_t target_label;
        std::string continuation_name;
    };
    std::vector<PendingJump> pending_jumps;
    
    // Map block names to actual blocks for resolution
    std::unordered_map<std::string, gccjit::block> block_name_map;
    
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
