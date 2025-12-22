#include "jit.hh"
#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../memory.hh"
#include "../register/register.hh"
#include <libgccjit++.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "../value.hh"

// C wrapper functions for JIT string building
extern "C" {
    // Memory manager wrapper functions
    void* jit_mem_allocate_permanent(size_t size);
    void limitly_mem_deallocate(void* ptr);
}

namespace JIT {

JITBackend::JITBackend() 
    : m_context(gccjit::context::acquire()), 
      m_optimizations_enabled(false),
      m_debug_mode(false),
      m_compiled_function(nullptr),
      m_jit_result(nullptr),
      current_memory_region_(nullptr) {
    
#if defined(_WIN32) || defined(__CYGWIN__)
    // Export all symbols so JITed code can see runtime functions
    // Windows-specific options to export all symbols and disable static linking for JIT
    m_context.add_driver_option("-Wl,--export-all-symbols");
    m_context.add_driver_option("-Wl,--dynamicbase");
#endif
    
    // Initialize memory manager with audit mode disabled for performance
    memory_manager_.setAuditMode(false);
    
    // Initialize basic types
    m_void_type = m_context.get_type(GCC_JIT_TYPE_VOID);
    m_int_type = m_context.get_type(GCC_JIT_TYPE_LONG_LONG);
    m_uint_type = m_context.get_type(GCC_JIT_TYPE_UINT64_T);
    m_double_type = m_context.get_type(GCC_JIT_TYPE_DOUBLE);
    m_bool_type = m_context.get_type(GCC_JIT_TYPE_BOOL);
    m_const_char_ptr_type = m_context.get_type(GCC_JIT_TYPE_CONST_CHAR_PTR);
    m_void_ptr_type = m_context.get_type(GCC_JIT_TYPE_VOID_PTR);
    m_c_int_type = m_context.get_type(GCC_JIT_TYPE_INT);
    
    // Allow unreachable blocks to handle break/continue control flow
    m_context.set_bool_allow_unreachable_blocks(1);
    
    // Create string builder type
    std::vector<gccjit::field> sb_fields;
    sb_fields.push_back(m_context.new_field(m_const_char_ptr_type, "buffer"));
    sb_fields.push_back(m_context.new_field(m_context.get_type(GCC_JIT_TYPE_SIZE_T), "capacity"));
    sb_fields.push_back(m_context.new_field(m_context.get_type(GCC_JIT_TYPE_SIZE_T), "length"));
    sb_fields.push_back(m_context.new_field(m_void_ptr_type, "region"));
    m_string_builder_type = m_context.new_struct_type("limitly_string_builder", sb_fields);
    
    // Get standard library functions
    std::vector<gccjit::param> printf_params;
    printf_params.push_back(m_context.new_param(m_const_char_ptr_type, "format"));
    m_printf_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "printf", printf_params, 1);
    
    std::vector<gccjit::param> malloc_params;
    malloc_params.push_back(m_context.new_param(m_context.get_type(GCC_JIT_TYPE_SIZE_T), "size"));
    m_malloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "malloc", malloc_params, 0);
    
    std::vector<gccjit::param> free_params;
    free_params.push_back(m_context.new_param(m_void_ptr_type, "ptr"));
    m_free_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "free", free_params, 0);
    
    std::vector<gccjit::param> memset_params;
    memset_params.push_back(m_context.new_param(m_void_ptr_type, "ptr"));
    memset_params.push_back(m_context.new_param(m_int_type, "value"));
    memset_params.push_back(m_context.new_param(m_context.get_type(GCC_JIT_TYPE_SIZE_T), "size"));
    m_memset_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "memset", memset_params, 0);
    
    std::vector<gccjit::param> memcpy_params;
    memcpy_params.push_back(m_context.new_param(m_void_ptr_type, "dest"));
    memcpy_params.push_back(m_context.new_param(m_void_ptr_type, "src"));
    memcpy_params.push_back(m_context.new_param(m_context.get_type(GCC_JIT_TYPE_SIZE_T), "n"));
    m_memcpy_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "memcpy", memcpy_params, 0);
    
    std::vector<gccjit::param> puts_params;
    puts_params.push_back(m_context.new_param(m_const_char_ptr_type, "str"));
    m_puts_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "puts", puts_params, 0);
    
    // Set up strlen function
    std::vector<gccjit::param> strlen_params;
    strlen_params.push_back(m_context.new_param(m_const_char_ptr_type, "str"));
    m_size_t_type = m_context.get_type(GCC_JIT_TYPE_SIZE_T);
    m_strlen_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_size_t_type, "strlen", strlen_params, 0);
    
    // Set up sprintf function
    std::vector<gccjit::param> sprintf_params;
    sprintf_params.push_back(m_context.new_param(m_void_ptr_type, "buffer"));
    sprintf_params.push_back(m_context.new_param(m_const_char_ptr_type, "format"));
    m_sprintf_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "sprintf", sprintf_params, 1);
    
    // Set up snprintf function
    std::vector<gccjit::param> snprintf_params;
    snprintf_params.push_back(m_context.new_param(m_void_ptr_type, "buffer"));
    snprintf_params.push_back(m_context.new_param(m_size_t_type, "size"));
    snprintf_params.push_back(m_context.new_param(m_const_char_ptr_type, "format"));
    m_snprintf_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "snprintf", snprintf_params, 1);
    
    // Set up platform time function (header-only, no runtime.c needed)
    std::vector<gccjit::param> get_ticks_params;
    m_get_ticks_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_uint_type, "get_ticks", get_ticks_params, 0);

    // Register runtime utility functions
    std::vector<gccjit::param> concat_params;
    concat_params.push_back(m_context.new_param(m_const_char_ptr_type, "a"));
    concat_params.push_back(m_context.new_param(m_const_char_ptr_type, "b"));
    m_runtime_concat_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_const_char_ptr_type, "limitly_runtime_concat", concat_params, 0);
    
    std::vector<gccjit::param> format_params;
    format_params.push_back(m_context.new_param(m_const_char_ptr_type, "format"));
    format_params.push_back(m_context.new_param(m_const_char_ptr_type, "arg"));
    m_runtime_format_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_const_char_ptr_type, "limitly_runtime_format", format_params, 0);

    // Initialize stats
    m_stats = {0, 0, 0.0};

    // Set up strcpy function
    std::vector<gccjit::param> strcpy_params;
    strcpy_params.push_back(m_context.new_param(m_void_ptr_type, "dest"));
    strcpy_params.push_back(m_context.new_param(m_const_char_ptr_type, "src"));
    m_strcpy_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "strcpy", strcpy_params, 0);
    
    // Set up strcat function
    std::vector<gccjit::param> strcat_params;
    strcat_params.push_back(m_context.new_param(m_void_ptr_type, "dest"));
    strcat_params.push_back(m_context.new_param(m_const_char_ptr_type, "src"));
    m_strcat_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "strcat", strcat_params, 0);
}

JITBackend::~JITBackend() {
    // Cleanup memory regions
    cleanup_memory();
    
    // Clean up JIT result if it exists
    if (m_jit_result) {
        gcc_jit_result_release(m_jit_result);
        m_jit_result = nullptr;
    }
    // Context will be automatically cleaned up by libgccjit++
}

// C wrapper implementations
static MemoryManager<> g_jit_memory_manager;

#if defined(_WIN32) || defined(__CYGWIN__)
    #define JIT_EXPORT __declspec(dllexport)
#else
    #define JIT_EXPORT __attribute__((visibility("default")))
#endif

// Runtime utility functions for JIT
extern "C" {
    JIT_EXPORT const char* limitly_runtime_concat(const char* a, const char* b) {
        // Use a thread_local static string for thread safety
        thread_local static std::string result;
        result = std::string(a) + std::string(b);
        return result.c_str();
    }
    
    JIT_EXPORT const char* limitly_runtime_format(const char* format, const char* arg) {
        // Use a thread_local static string for thread safety
        thread_local static std::string result;
        result = std::string(format);
        
        // Simple %s replacement
        size_t pos = result.find("%s");
        if (pos != std::string::npos) {
            result.replace(pos, 2, arg);
        } else {
            result += arg; // Fallback: append
        }
        return result.c_str();
    }
    
    void* jit_mem_allocate_permanent(size_t size) {
        return g_jit_memory_manager.allocate(size);
    }
    
    void limitly_mem_deallocate(void* ptr) {
        g_jit_memory_manager.deallocate(ptr);
    }
}

void JITBackend::process_function(const LIR::LIR_Function& function) {
    processed_functions.push_back(function);
    compile_function(function);
}

void JITBackend::compile_function(const LIR::LIR_Function& function) {
    Timer timer;
    
    // Clean up any previous result
    if (m_jit_result) {
        gcc_jit_result_release(m_jit_result);
        m_jit_result = nullptr;
    }
    
    // Clear previous state
    jit_registers.clear();
    register_types.clear();
    label_blocks.clear();
    pending_jumps.clear();
    block_name_map.clear();
    
    // Enter memory region for this compilation
    enter_memory_region();

    // Populate register_types from function's register_types mapping
    for (const auto& entry : function.register_types) {
        register_types[entry.first] = to_jit_type(entry.second);
    }
    
    // Create function type and function
    std::vector<gccjit::param> param_types;
    for (uint32_t i = 0; i < function.param_count; ++i) {
        gccjit::type param_type = register_types[i];
        if (!param_type.get_inner_type()) {
            param_type = m_int_type; // Default to int if no type specified
        }
        param_types.push_back(m_context.new_param(param_type, ("param" + std::to_string(i)).c_str()));
        param_types.push_back(m_context.new_param(m_int_type, ("param" + std::to_string(i)).c_str()));
    }
    
    m_current_func = m_context.new_function(GCC_JIT_FUNCTION_EXPORTED, m_int_type, function.name.c_str(), param_types, 0);
    
    // === SINGLE PASS: Process instructions and create blocks on the fly ===
    compile_function_single_pass(function);
    
    // Compile the context using proper gcc_jit flow
    if (m_debug_mode) {
        std::cout << "Compiling JIT context..." << std::endl;
    }
    
    gcc_jit_result* jit_result = m_context.compile();
    if (!jit_result) {
        std::string error_msg = "JIT compilation failed";
        // Try to get more detailed error information
        if (m_debug_mode) {
            std::cerr << "JIT compilation failed - this might be due to unreachable blocks in LIR" << std::endl;
        }
        report_error(error_msg);
        m_current_func = nullptr;
        return;
    }
    
    // Check if there were any warnings or errors during compilation
    if (m_debug_mode) {
        std::cout << "JIT compilation completed" << std::endl;
    }
    
    // Get the compiled function code
    m_compiled_function = gcc_jit_result_get_code(jit_result, function.name.c_str());
    if (!m_compiled_function) {
        // Try to get more detailed error information
        if (m_debug_mode) {
            std::cerr << "Failed to get compiled function: " << function.name << std::endl;
            std::cerr << "This might indicate the function was not properly compiled or has an invalid signature" << std::endl;
        }
        report_error("Failed to get compiled function: " + function.name);
        m_current_func = nullptr;
      // ADD THIS:
      m_jit_result = jit_result; // Hand over ownership to the class member
        return;
    }
    
    if (m_debug_mode) {
        std::cout << "JIT compilation successful, function at: " << m_compiled_function << std::endl;
    }
    
    // Keep the result alive - don't release it yet
    m_jit_result = jit_result;
    
    // Don't explicitly set to nullptr - let it go out of scope naturally to avoid cleanup issues
    // m_current_func = nullptr;
    
    m_stats.compilation_time_ms = timer.elapsed_ms();
    exit_memory_region();
    
    // Update stats
    m_stats.functions_compiled++;
    m_stats.compilation_time_ms += timer.elapsed_ms();
}

void JITBackend::compile_function_single_pass(const LIR::LIR_Function& function) {
    // Create entry block
    m_current_block = m_current_func.new_block("entry");
    label_blocks[UINT32_MAX] = m_current_block; // Use special value for entry block
    
    // Allocate registers for parameters
    for (uint32_t i = 0; i < function.param_count; ++i) {
        gccjit::lvalue param = m_current_func.get_param(i);
        set_jit_register(i, param);
    }
    
    // Track whether current block is terminated
    bool current_block_terminated = false;
    
    // Process all instructions in a single pass
    for (size_t i = 0; i < function.instructions.size(); ++i) {
        const auto& inst = function.instructions[i];
        
        // Check if this instruction position is a jump target
        auto it = label_blocks.find(i);
        if (it != label_blocks.end() && i != UINT32_MAX) {
            m_current_block = it->second;
            current_block_terminated = false;
        } else if (current_block_terminated) {
            // Previous instruction terminated the block, create a new one for this instruction
            std::string new_block_name = "inst_" + std::to_string(i);
            m_current_block = m_current_func.new_block(new_block_name);
            label_blocks[i] = m_current_block;
            current_block_terminated = false;
        }
        
        // Pre-create jump target blocks
        if (inst.op == LIR::LIR_Op::Jump || inst.op == LIR::LIR_Op::JumpIfFalse) {
            uint32_t target_label = inst.imm;
            if (label_blocks.find(target_label) == label_blocks.end()) {
                std::string block_name = "label_" + std::to_string(target_label);
                gccjit::block target_block = m_current_func.new_block(block_name);
                label_blocks[target_label] = target_block;
            }
        }
        
        // Emit the instruction
        if (inst.op == LIR::LIR_Op::Jump) {
            compile_jump(inst);
            current_block_terminated = true;
            m_stats.instructions_compiled++;
        } else if (inst.op == LIR::LIR_Op::JumpIfFalse) {
            compile_conditional_jump(inst, i);
            current_block_terminated = true;
            m_stats.instructions_compiled++;
        } else if (inst.op == LIR::LIR_Op::Return) {
            compile_instruction(inst);
            current_block_terminated = true;
            m_stats.instructions_compiled++;
        } else {
            compile_instruction(inst);
            m_stats.instructions_compiled++;
        }
    }
}

gccjit::rvalue JITBackend::compile_instruction(const LIR::LIR_Inst& inst) {
    switch (inst.op) {
        // Data Movement
        case LIR::LIR_Op::Mov: {
            gccjit::rvalue src = get_jit_register(inst.a);
            // Get or create destination register with the same type as source
            gccjit::lvalue dst = get_jit_register(inst.dst, src.get_type());
            m_current_block.add_assignment(dst, src);
            return src;
        }
        
        case LIR::LIR_Op::LoadConst: {
            gccjit::lvalue dst;
            gccjit::rvalue value;
            
            if (inst.const_val) {
                // Handle different value types based on the Value's type
                if (inst.const_val->type) {
                    switch (inst.const_val->type->tag) {
                        case TypeTag::Int:
                            dst = get_jit_register(inst.dst, m_int_type);
                            // Use int to resolve ambiguity
                            {
                                long long val = std::stoll(inst.const_val->data);
                                value = m_context.new_rvalue(m_int_type, static_cast<int>(val));
                            }
                            break;      
                        case TypeTag::UInt8:
                        case TypeTag::UInt16:
                        case TypeTag::UInt32:
                            dst = get_jit_register(inst.dst, m_uint_type);
                            // Use int to resolve ambiguity
                            {
                                unsigned long long val = std::stoull(inst.const_val->data);
                                value = m_context.new_rvalue(m_uint_type, static_cast<int>(val));
                            }
                            break;
                        case TypeTag::UInt64:
                            dst = get_jit_register(inst.dst, m_uint_type);
                            // Handle large unsigned values that don't fit in signed int
                            try {
                                unsigned long long val = std::stoull(inst.const_val->data);
                                value = m_context.new_rvalue(m_uint_type, static_cast<int>(val));
                            } catch (const std::out_of_range&) {
                                // If value is too large, use 0 as fallback
                                value = m_context.new_rvalue(m_uint_type, 0);
                            } catch (const std::invalid_argument&) {
                                // If parsing fails, use 0 as fallback  
                                value = m_context.new_rvalue(m_uint_type, 0);
                            }
                            break;
                            
                        case TypeTag::Int32: 
                            dst = get_jit_register(inst.dst, m_uint_type);
                            value = m_context.new_rvalue(m_uint_type, static_cast<int>(std::stoll(inst.const_val->data)));
                            break;
                        case TypeTag::Int64:
                            dst = get_jit_register(inst.dst, m_uint_type);
                            {
                                long long val = std::stoll(inst.const_val->data);
                                value = m_context.new_rvalue(m_uint_type, static_cast<long>(val));
                            }
                            break;
                        case TypeTag::Float32:
                        case TypeTag::Float64:
                            dst = get_jit_register(inst.dst, m_double_type);
                            value = m_context.new_rvalue(m_double_type, static_cast<double>(std::stold(inst.const_val->data)));
                            break;
                        case TypeTag::Bool:
                            dst = get_jit_register(inst.dst, m_bool_type);
                            value = m_context.new_rvalue(m_bool_type, inst.const_val->data == "true" ? 1 : 0);
                            break;
                        case TypeTag::String:
                            dst = get_jit_register(inst.dst, m_const_char_ptr_type);
                            // Create string literal using C API
                            {
                                gcc_jit_rvalue* c_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), inst.const_val->data.c_str());
                                value = gccjit::rvalue(c_str);
                            }
                            break;
                        case TypeTag::Nil:
                                                dst = get_jit_register(inst.dst, m_int_type);
                            value = m_context.new_rvalue(m_int_type, 0);
                            break;
                        default:
                            dst = get_jit_register(inst.dst, m_int_type);
                            value = m_context.new_rvalue(m_int_type, 0);
                            break;
                    }
                } else {
                    // Default to string type
                    gcc_jit_rvalue* c_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), inst.const_val->data.c_str());
                    value = gccjit::rvalue(c_str);
                }
            } else {
                // // Default to int type
                // dst = get_jit_register(inst.dst, m_int_type);
                // value = m_context.new_rvalue(m_int_type, 0);

                                    // Default to string type
                    gcc_jit_rvalue* c_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), inst.const_val->data.c_str());
                    value = gccjit::rvalue(c_str);
            }
            
            m_current_block.add_assignment(dst, value);
            return value;
        }
        
        // Arithmetic Operations
        case LIR::LIR_Op::Add:
        case LIR::LIR_Op::Sub:
        case LIR::LIR_Op::Mul:
        case LIR::LIR_Op::Div:
        case LIR::LIR_Op::Mod: {
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_arithmetic_op(inst.op, a, b);
            
            // Get or create destination register with the correct type
            gccjit::lvalue dst = get_jit_register(inst.dst, result.get_type());
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        // Bitwise/Logical Operations
        case LIR::LIR_Op::And:
        case LIR::LIR_Op::Or: {
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_bitwise_op(inst.op, a, b);
            // Get or create destination register with bool type for logical operations
            gccjit::lvalue dst = get_jit_register(inst.dst, m_bool_type);
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        case LIR::LIR_Op::Xor: {
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_bitwise_op(inst.op, a, b);
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        // Comparison Operations
        case LIR::LIR_Op::CmpEQ:
        case LIR::LIR_Op::CmpNEQ:
        case LIR::LIR_Op::CmpLT:
        case LIR::LIR_Op::CmpLE:
        case LIR::LIR_Op::CmpGT:
        case LIR::LIR_Op::CmpGE: {
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_comparison_op(inst.op, a, b);
            // Get or create destination register with bool type
            gccjit::lvalue dst = get_jit_register(inst.dst, m_bool_type);
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        // Control Flow
        case LIR::LIR_Op::Jump:
            compile_jump(inst);
            break;
            
        case LIR::LIR_Op::JumpIfFalse:
            // This should not be called anymore - handled in single pass
            report_error("JumpIfFalse should be handled in single pass, not compile_instruction");
            break;
            
        case LIR::LIR_Op::Call:
            compile_call(inst);
            break;
            
        case LIR::LIR_Op::PrintInt:
            compile_print_int(inst);
            break;
            
        case LIR::LIR_Op::PrintUint:
            compile_print_uint(inst);
            break;
                    
        case LIR::LIR_Op::PrintFloat:
            compile_print_float(inst);
            break;
            
        case LIR::LIR_Op::PrintBool:
            compile_print_bool(inst);
            break;
            
        case LIR::LIR_Op::PrintString:
            compile_print_string(inst);
            break;
            
        case LIR::LIR_Op::Return:
            compile_return(inst);
            break;
            
        // Function definition operations
        case LIR::LIR_Op::FuncDef:
            // Function definition - no JIT action needed for now
            // This is metadata for the function structure
            break;
            
        case LIR::LIR_Op::Param:
            // Parameter definition - no JIT action needed for now
            // This is metadata for parameter registers
            break;
            
        case LIR::LIR_Op::Ret:
            compile_return(inst);
            break;
            
        // Memory Operations
        case LIR::LIR_Op::Load:
        case LIR::LIR_Op::Store:
            compile_memory_op(inst);
            break;
            
        // String Operations
        case LIR::LIR_Op::Concat: {
            gccjit::lvalue dst = get_jit_register(inst.dst, m_const_char_ptr_type);
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_string_concat(a, b);
            // Cast void* to const char* for assignment
            gccjit::rvalue cast_result = m_context.new_cast(result, m_const_char_ptr_type);
            m_current_block.add_assignment(dst, cast_result);
            return cast_result;
        }
        
        case LIR::LIR_Op::STR_CONCAT: {
            gccjit::lvalue dst = get_jit_register(inst.dst, m_const_char_ptr_type);
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_string_concat(a, b);
            // Cast void* to const char* for assignment
            gccjit::rvalue cast_result = m_context.new_cast(result, m_const_char_ptr_type);
            m_current_block.add_assignment(dst, cast_result);
            return cast_result;
        }
        
        case LIR::LIR_Op::STR_FORMAT: {
            gccjit::lvalue dst = get_jit_register(inst.dst, m_const_char_ptr_type);
            gccjit::rvalue format = get_jit_register(inst.a);
            gccjit::rvalue arg = get_jit_register(inst.b);
            gccjit::rvalue result = compile_string_format(format, arg);
            // Cast void* to const char* for assignment
            gccjit::rvalue cast_result = m_context.new_cast(result, m_const_char_ptr_type);
            m_current_block.add_assignment(dst, cast_result);
            return cast_result;
        }
        
        // Type Operations
        case LIR::LIR_Op::Cast: {
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue src = get_jit_register(inst.a);
            // For now, just assign (type casting would need more info)
            m_current_block.add_assignment(dst, src);
            return src;
        }
        
        case LIR::LIR_Op::ToString: {
            gccjit::lvalue dst = get_jit_register(inst.dst, m_const_char_ptr_type);
            gccjit::rvalue src = get_jit_register(inst.a);
            gccjit::rvalue result = compile_to_string(src);
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        case LIR::LIR_Op::Nop:
            // No operation
            break;
            
        // === THREADLESS CONCURRENCY OPERATIONS ===
        // All generated inline - no external runtime functions needed!
        
        case LIR::LIR_Op::ChannelAlloc: {
            // Generate: void* ch = malloc(sizeof(Channel) + capacity * sizeof(int));
            // Initialize inline using raw memory operations
            
            gccjit::lvalue dst = get_jit_register(inst.dst, m_void_ptr_type);
            gccjit::rvalue capacity = get_jit_register(inst.a);
            
            // Calculate total size: sizeof(Channel) approx + buffer size
            gccjit::rvalue size_of_int = m_context.new_rvalue(m_size_t_type, static_cast<long>(sizeof(int)));
            gccjit::rvalue capacity_as_uintptr = m_context.new_cast(capacity, m_uint_type); // Use uint as intermediate
            gccjit::rvalue capacity_as_size = m_context.new_cast(capacity_as_uintptr, m_size_t_type);
            gccjit::rvalue buffer_size = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, capacity_as_size, size_of_int);
            gccjit::rvalue header_size = m_context.new_rvalue(m_size_t_type, static_cast<long>(32)); // Approx header size
            gccjit::rvalue total_size = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_size_t_type, buffer_size, header_size);
            
            // Allocate memory
            std::vector<gccjit::rvalue> malloc_args = {total_size};
            gccjit::rvalue channel_ptr = m_context.new_call(m_malloc_func, malloc_args);
            
            // Initialize using memset (zero everything)
            std::vector<gccjit::rvalue> memset_args = {channel_ptr, m_context.new_rvalue(m_int_type, 0), total_size};
            m_context.new_call(m_memset_func, memset_args);
            
            // Store capacity at offset 0 (approximate struct layout)
            gccjit::lvalue capacity_ptr = m_context.new_cast(channel_ptr, m_int_type.get_pointer()).dereference();
            m_current_block.add_assignment(capacity_ptr, capacity);
            
            m_current_block.add_assignment(dst, channel_ptr);
            return channel_ptr;
        }
        
        case LIR::LIR_Op::ChannelPush: {
            // Generate simplified inline channel push using raw memory
            
            gccjit::rvalue channel_ptr = get_jit_register(inst.a);
            gccjit::rvalue value = get_jit_register(inst.b);
            gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
            
            // Simplified: assume always succeeds for now
            // In real implementation, would track write_pos/read_pos
            
            // For now, just return success (1)
            m_current_block.add_assignment(dst, m_context.new_rvalue(m_int_type, 1));
            return dst;
        }
        
        case LIR::LIR_Op::ChannelPop: {
            // Generate simplified inline channel pop using raw memory
            
            gccjit::rvalue channel_ptr = get_jit_register(inst.a);
            gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
            
            // Simplified: return 0 for now (no data)
            // In real implementation, would track write_pos/read_pos
            
            m_current_block.add_assignment(dst, m_context.new_rvalue(m_int_type, 0));
            return dst;
        }
        
        case LIR::LIR_Op::ChannelHasData: {
            // Generate simplified inline channel check
            
            gccjit::rvalue channel_ptr = get_jit_register(inst.a);
            gccjit::lvalue dst = get_jit_register(inst.dst, m_bool_type);
            
            // Simplified: return false for now
            m_current_block.add_assignment(dst, m_context.new_rvalue(m_bool_type, 0));
            return dst;
        }
        
        case LIR::LIR_Op::TaskContextAlloc: {
            // Generate: TaskContext* tasks = malloc(count * sizeof(TaskContext));
            
            gccjit::lvalue dst = get_jit_register(inst.dst, m_void_ptr_type);
            
            // Get count - create a new temp register to avoid type conflicts
            gccjit::rvalue count_src_raw = get_jit_register(inst.a);
            gccjit::rvalue count_src = count_src_raw;
            
            // Cast count to int if needed
            if (count_src.get_type().get_inner_type() != m_int_type.get_inner_type()) {
                count_src = m_context.new_cast(count_src, m_int_type);
            }
            
            // Approximate TaskContext size
            gccjit::rvalue task_size = m_context.new_rvalue(m_size_t_type, static_cast<long>(128)); // Approx size
            gccjit::rvalue count_as_uintptr = m_context.new_cast(count_src, m_uint_type); // Use uint as intermediate
            gccjit::rvalue count_as_size = m_context.new_cast(count_as_uintptr, m_size_t_type);
            gccjit::rvalue total_size = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, count_as_size, task_size);
            
            // Allocate array
            std::vector<gccjit::rvalue> malloc_args = {total_size};
            gccjit::rvalue tasks_ptr = m_context.new_call(m_malloc_func, malloc_args);
            
            // Initialize to zero
            std::vector<gccjit::rvalue> memset_args = {tasks_ptr, m_context.new_rvalue(m_int_type, 0), total_size};
            m_context.new_call(m_memset_func, memset_args);
            
            m_current_block.add_assignment(dst, tasks_ptr);
            return tasks_ptr;
        }
        
        case LIR::LIR_Op::TaskContextInit: {
            // Generate: tasks[task_id].state = TASK_STATE_INIT;
            // Generate: tasks[task_id].task_id = task_id;
            
            gccjit::rvalue tasks_ptr = get_jit_register(inst.dst);
            gccjit::rvalue task_id = get_jit_register(inst.a);
            
            // Calculate task offset: task_id * task_size
            gccjit::rvalue task_size = m_context.new_rvalue(m_size_t_type, static_cast<long>(128));
            gccjit::rvalue task_id_as_uintptr = m_context.new_cast(task_id, m_uint_type); // Use uint as intermediate
            gccjit::rvalue task_id_as_size = m_context.new_cast(task_id_as_uintptr, m_size_t_type);
            gccjit::rvalue task_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, task_id_as_size, task_size);
            
            // Get task pointer: tasks_ptr + task_offset
            gccjit::rvalue task_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, tasks_ptr, task_offset);
            
            // Set state at offset 0
            gccjit::lvalue state_ptr = m_context.new_cast(task_ptr, m_int_type.get_pointer()).dereference();
            m_current_block.add_assignment(state_ptr, m_context.new_rvalue(m_int_type, 0)); // TASK_STATE_INIT
            
            // Set task_id at offset 4 (approximate)
            gccjit::rvalue offset_4 = m_context.new_rvalue(m_size_t_type, static_cast<long>(4));
            gccjit::rvalue task_id_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, 
                task_ptr, offset_4);
            gccjit::lvalue task_id_field = m_context.new_cast(task_id_ptr, m_int_type.get_pointer()).dereference();
            m_current_block.add_assignment(task_id_field, task_id);
            
            return task_id;
        }
        
        case LIR::LIR_Op::TaskSetField: {
            // Generate: tasks[task_index].fields[field_index] = value;
            
            gccjit::rvalue tasks_ptr = get_jit_register(inst.dst);
            gccjit::rvalue task_index = get_jit_register(inst.a);
            gccjit::rvalue field_index = get_jit_register(inst.b);
            gccjit::rvalue value = get_jit_register(inst.imm);
            
            // Calculate task offset
            gccjit::rvalue task_size = m_context.new_rvalue(m_size_t_type, static_cast<long>(128));
            gccjit::rvalue task_index_as_uintptr = m_context.new_cast(task_index, m_uint_type); // Use uint as intermediate
            gccjit::rvalue task_index_as_size = m_context.new_cast(task_index_as_uintptr, m_size_t_type);
            gccjit::rvalue task_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, task_index_as_size, task_size);
            
            // Get task pointer
            gccjit::rvalue task_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, tasks_ptr, task_offset);
            
            // Calculate field offset (approximate: base_offset + field_index * 4)
            gccjit::rvalue base_field_offset = m_context.new_rvalue(m_size_t_type, static_cast<long>(16)); // Start after basic fields
            gccjit::rvalue field_index_as_uintptr = m_context.new_cast(field_index, m_uint_type); // Use uint as intermediate
            gccjit::rvalue field_index_as_size = m_context.new_cast(field_index_as_uintptr, m_size_t_type);
            gccjit::rvalue field_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, 
                field_index_as_size, m_context.new_rvalue(m_size_t_type, static_cast<long>(4)));
            gccjit::rvalue total_field_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_size_t_type, base_field_offset, field_offset);
            
            // Get field pointer
            gccjit::rvalue field_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, task_ptr, total_field_offset);
            gccjit::lvalue field = m_context.new_cast(field_ptr, m_int_type.get_pointer()).dereference();
            
            m_current_block.add_assignment(field, value);
            return value;
        }
        
        case LIR::LIR_Op::SchedulerRun: {
            // Generate simplified scheduler loop
            
            gccjit::rvalue tasks_ptr = get_jit_register(inst.dst);
            gccjit::rvalue task_count = get_jit_register(inst.a);
            
            // For now, just return 0 (simplified)
            // Real implementation would generate the full scheduler loop
            gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
            m_current_block.add_assignment(dst, m_context.new_rvalue(m_int_type, 0));
            return dst;
        }
        
        case LIR::LIR_Op::GetTickCount: {
            // Generate: return get_ticks(); (imported from platform header)
            
            gccjit::lvalue dst = get_jit_register(inst.dst, m_uint_type);
            std::vector<gccjit::rvalue> get_ticks_args = {}; // No arguments
            gccjit::rvalue ticks = m_context.new_call(m_get_ticks_func, get_ticks_args);
            m_current_block.add_assignment(dst, ticks);
            return ticks;
        }
        
        case LIR::LIR_Op::DelayUntil: {
            // Generate: return (current_ticks >= target_ticks);
            
            gccjit::rvalue target_ticks = get_jit_register(inst.a);
            gccjit::lvalue dst = get_jit_register(inst.dst, m_bool_type);
            
            // Get current ticks
            std::vector<gccjit::rvalue> get_ticks_args = {};
            gccjit::rvalue current_ticks = m_context.new_call(m_get_ticks_func, get_ticks_args);
            
            // Compare
            gccjit::rvalue expired = m_context.new_comparison(GCC_JIT_COMPARISON_GE, current_ticks, target_ticks);
            m_current_block.add_assignment(dst, expired);
            return expired;
        }
        
        case LIR::LIR_Op::TaskGetState: {
            // Generate: return tasks[task_id].state;
            
            gccjit::rvalue tasks_ptr = get_jit_register(inst.a);
            gccjit::rvalue task_id = get_jit_register(inst.b);
            gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
            
            // Calculate task offset
            gccjit::rvalue task_size = m_context.new_rvalue(m_size_t_type, static_cast<long>(128));
            gccjit::rvalue task_id_as_uintptr = m_context.new_cast(task_id, m_uint_type);
            gccjit::rvalue task_id_as_size = m_context.new_cast(task_id_as_uintptr, m_size_t_type);
            gccjit::rvalue task_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, task_id_as_size, task_size);
            
            // Get task pointer
            gccjit::rvalue task_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, tasks_ptr, task_offset);
            
            // Get state at offset 0
            gccjit::lvalue state_ptr = m_context.new_cast(task_ptr, m_int_type.get_pointer()).dereference();
            gccjit::rvalue state = state_ptr;
            m_current_block.add_assignment(dst, state);
            return state;
        }
        
        case LIR::LIR_Op::TaskSetState: {
            // Generate: tasks[task_id].state = new_state;
            
            gccjit::rvalue tasks_ptr = get_jit_register(inst.dst);
            gccjit::rvalue task_id = get_jit_register(inst.a);
            gccjit::rvalue new_state = get_jit_register(inst.b);
            
            // Calculate task offset
            gccjit::rvalue task_size = m_context.new_rvalue(m_size_t_type, static_cast<long>(128));
            gccjit::rvalue task_id_as_uintptr = m_context.new_cast(task_id, m_uint_type);
            gccjit::rvalue task_id_as_size = m_context.new_cast(task_id_as_uintptr, m_size_t_type);
            gccjit::rvalue task_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, task_id_as_size, task_size);
            
            // Get task pointer
            gccjit::rvalue task_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, tasks_ptr, task_offset);
            
            // Set state at offset 0
            gccjit::lvalue state_ptr = m_context.new_cast(task_ptr, m_int_type.get_pointer()).dereference();
            m_current_block.add_assignment(state_ptr, new_state);
            return new_state;
        }
        
        case LIR::LIR_Op::TaskGetField: {
            // Generate: return tasks[task_index].fields[field_index];
            
            gccjit::rvalue tasks_ptr = get_jit_register(inst.a);
            gccjit::rvalue task_index = get_jit_register(inst.b);
            gccjit::rvalue field_index = get_jit_register(inst.imm);
            gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
            
            // Calculate task offset
            gccjit::rvalue task_size = m_context.new_rvalue(m_size_t_type, static_cast<long>(128));
            gccjit::rvalue task_index_as_uintptr = m_context.new_cast(task_index, m_uint_type);
            gccjit::rvalue task_index_as_size = m_context.new_cast(task_index_as_uintptr, m_size_t_type);
            gccjit::rvalue task_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, task_index_as_size, task_size);
            
            // Get task pointer
            gccjit::rvalue task_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, tasks_ptr, task_offset);
            
            // Calculate field offset (approximate: base_offset + field_index * 4)
            gccjit::rvalue base_field_offset = m_context.new_rvalue(m_size_t_type, static_cast<long>(16));
            gccjit::rvalue field_index_as_uintptr = m_context.new_cast(field_index, m_uint_type);
            gccjit::rvalue field_index_as_size = m_context.new_cast(field_index_as_uintptr, m_size_t_type);
            gccjit::rvalue field_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_size_t_type, 
                field_index_as_size, m_context.new_rvalue(m_size_t_type, static_cast<long>(4)));
            gccjit::rvalue total_field_offset = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_size_t_type, base_field_offset, field_offset);
            
            // Get field pointer
            gccjit::rvalue field_ptr = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_void_ptr_type, task_ptr, total_field_offset);
            gccjit::lvalue field = m_context.new_cast(field_ptr, m_int_type.get_pointer()).dereference();
            gccjit::rvalue value = field;
            m_current_block.add_assignment(dst, value);
            return value;
        }
        
        case LIR::LIR_Op::SchedulerInit: {
            // Generate: return 0; (simplified - no initialization needed)
            
            gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
            m_current_block.add_assignment(dst, m_context.new_rvalue(m_int_type, 0));
            return dst;
        }
        
        case LIR::LIR_Op::SchedulerTick: {
            // Generate: return 0; (simplified - single tick)
            
            gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
            m_current_block.add_assignment(dst, m_context.new_rvalue(m_int_type, 0));
            return dst;
        }
            
        default:
            report_error("Unsupported instruction: " + std::to_string(static_cast<int>(inst.op)));
            break;
    }
    
    return m_context.new_rvalue(m_int_type, 0);
}

gccjit::rvalue JITBackend::compile_arithmetic_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b) {
    // Determine the result type based on operand types
    gccjit::type result_type = a.get_type();
    
    // If either operand is double, use double
    if (a.get_type().get_inner_type() == m_double_type.get_inner_type() ||
        b.get_type().get_inner_type() == m_double_type.get_inner_type()) {
        result_type = m_double_type;
        // Cast both operands to double if needed
        if (a.get_type().get_inner_type() != m_double_type.get_inner_type()) {
            a = m_context.new_cast(a, m_double_type);
        }
        if (b.get_type().get_inner_type() != m_double_type.get_inner_type()) {
            b = m_context.new_cast(b, m_double_type);
        }
    }
    
    switch (op) {
        case LIR::LIR_Op::Add:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, result_type, a, b);
        case LIR::LIR_Op::Sub:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MINUS, result_type, a, b);
        case LIR::LIR_Op::Mul:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, result_type, a, b);
        case LIR::LIR_Op::Div:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_DIVIDE, result_type, a, b);
        case LIR::LIR_Op::Mod:
            // Modulo only works on integers
            if (result_type.get_inner_type() == m_double_type.get_inner_type()) {
                return a; // Can't do modulo on floats
            }
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MODULO, result_type, a, b);
        default:
            return a;
    }
}

gccjit::rvalue JITBackend::compile_comparison_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b) {
    enum gcc_jit_comparison comparison;
    
    switch (op) {
        case LIR::LIR_Op::CmpEQ: comparison = GCC_JIT_COMPARISON_EQ; break;
        case LIR::LIR_Op::CmpNEQ: comparison = GCC_JIT_COMPARISON_NE; break;
        case LIR::LIR_Op::CmpLT: comparison = GCC_JIT_COMPARISON_LT; break;
        case LIR::LIR_Op::CmpLE: comparison = GCC_JIT_COMPARISON_LE; break;
        case LIR::LIR_Op::CmpGT: comparison = GCC_JIT_COMPARISON_GT; break;
        case LIR::LIR_Op::CmpGE: comparison = GCC_JIT_COMPARISON_GE; break;
        default: comparison = GCC_JIT_COMPARISON_EQ; break;
    }
    
    // Return bool result directly - don't cast to int
    return m_context.new_comparison(comparison, a, b);
}

gccjit::rvalue JITBackend::compile_bitwise_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b) {
    switch (op) {
        case LIR::LIR_Op::And:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_LOGICAL_AND, m_bool_type, a, b);
        case LIR::LIR_Op::Or:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_LOGICAL_OR, m_bool_type, a, b);
        case LIR::LIR_Op::Xor:
            // XOR is not directly available, implement as (a & ~b) | (~a & b)
            return a; // Simplified for now
        default:
            return a;
    }
}

void JITBackend::compile_jump(const LIR::LIR_Inst& inst) {
    // Simple direct jump - target block should already exist from pass 1
    uint32_t target_label = inst.imm;
    
    auto it = label_blocks.find(target_label);
    if (it != label_blocks.end()) {
        gccjit::block target_block = it->second;
        try {
            m_current_block.end_with_jump(target_block);
        } catch (const std::exception& e) {
            // Block might already be terminated - this can happen in complex control flow
            // For now, just report and continue
            report_error("Jump block already terminated: " + std::string(e.what()));
        }
    }
}

void JITBackend::compile_conditional_jump(const LIR::LIR_Inst& inst, size_t current_instruction_pos) {
    gccjit::rvalue condition = get_jit_register(inst.a);
    uint32_t target_label = inst.imm;
    
    // Get or create target block (false branch)
    gccjit::block target_block;
    auto it = label_blocks.find(target_label);
    if (it != label_blocks.end()) {
        target_block = it->second;
    } else {
        std::string block_name = "label_" + std::to_string(target_label);
        target_block = m_current_func.new_block(block_name);
        label_blocks[target_label] = target_block;
    }
    
    // Create continuation block (true branch - next instruction)
    size_t continuation_pos = current_instruction_pos + 1;
    gccjit::block continuation_block;
    
    // Check if continuation block already exists
    auto cont_it = label_blocks.find(continuation_pos);
    if (cont_it != label_blocks.end()) {
        continuation_block = cont_it->second;
    } else {
        std::string cont_name = "cont_" + std::to_string(continuation_pos);
        continuation_block = m_current_func.new_block(cont_name);
        label_blocks[continuation_pos] = continuation_block;
    }
    
    // Conditional jump: if false, go to target; if true, continue
    m_current_block.end_with_conditional(condition, continuation_block, target_block);
    
    // DON'T switch to continuation block here - let the main loop handle it
    // The block is terminated, so we can't add more instructions to it
}

void JITBackend::compile_call(const LIR::LIR_Inst& inst) {
    // Get function ID from inst.b (function ID is stored in operand b)
    int32_t function_id = static_cast<int32_t>(inst.b);
    
    // Get number of arguments from inst.a
    int32_t arg_count = static_cast<int32_t>(inst.a);
    
    // Access LIR function manager to get function
    auto& func_manager = LIR::LIRFunctionManager::getInstance();
    auto function_names = func_manager.getFunctionNames();
    
    // Find function by ID/index
    std::string func_name;
    if (function_id >= 0 && function_id < static_cast<int32_t>(function_names.size())) {
        func_name = function_names[function_id];
    } else {
        // Invalid function ID, return 0
        gccjit::rvalue result = m_context.new_rvalue(m_int_type, 0);
        gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
        m_current_block.add_assignment(dst, result);
        return;
    }
    
    // Get the actual LIR function with its instructions
    auto lir_func = func_manager.getFunction(func_name);
    if (!lir_func) {
        // Function not found, return 0
        gccjit::rvalue result = m_context.new_rvalue(m_int_type, 0);
        gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
        m_current_block.add_assignment(dst, result);
        return;
    }
    
    // Use the Register VM to execute the function's LIR instructions directly
    // This is the "Compile function's LIR instructions to JIT blocks" approach
    // but instead we use the direct threaded interpreter which is simpler and more reliable
    
    // Create a Register VM instance for this function call
    // static Register::RegisterVM vm;
    
    // // Execute the function using the Register VM
    // vm.execute_lir_instructions_direct(lir_func->getInstructions());
    
    // Get the return value from the Register VM
    // auto result_value = vm.get_register(0); // Assume return value is in r0
    Register::RegisterValue result_value = 0; // Default return value
    
    // Convert Register VM result to JIT value
    gccjit::rvalue result;
    if (std::holds_alternative<int64_t>(result_value)) {
        int64_t val = std::get<int64_t>(result_value);
        result = m_context.new_rvalue(m_int_type, static_cast<int>(val));
    } else if (std::holds_alternative<double>(result_value)) {
        result = m_context.new_rvalue(m_double_type, std::get<double>(result_value));
    } else if (std::holds_alternative<bool>(result_value)) {
        result = m_context.new_rvalue(m_bool_type, std::get<bool>(result_value));
    } else {
        // Default to 0 for unsupported types
        result = m_context.new_rvalue(m_int_type, 0);
    }
    
    // Set the result register
    gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
    m_current_block.add_assignment(dst, result);
}

void JITBackend::compile_print_int(const LIR::LIR_Inst& inst) {
    // Print integer using printf
    gccjit::rvalue value = get_jit_register(inst.a);
    const char* format_str = "%lld\n";
    gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), format_str);
    gccjit::rvalue format = gccjit::rvalue(c_format);
    std::vector<gccjit::rvalue> args = {format, value};
    gccjit::rvalue printf_call = m_context.new_call(m_printf_func, args);
    m_current_block.add_eval(printf_call);
}

void JITBackend::compile_print_uint(const LIR::LIR_Inst& inst) {
    // Print integer using printf
    gccjit::rvalue value = get_jit_register(inst.a);
    const char* format_str = "%llu\n";
    gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), format_str);
    gccjit::rvalue format = gccjit::rvalue(c_format);
    std::vector<gccjit::rvalue> args = {format, value};
    gccjit::rvalue printf_call = m_context.new_call(m_printf_func, args);
    m_current_block.add_eval(printf_call);
}

void JITBackend::compile_print_float(const LIR::LIR_Inst& inst) {
    // Print float using printf
    gccjit::rvalue value = get_jit_register(inst.a);
    
    // Ensure value is a double
    if (value.get_type().get_inner_type() != m_double_type.get_inner_type()) {
        value = m_context.new_cast(value, m_double_type);
    }
    
    const char* format_str = "%g\n";
    gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), format_str);
    gccjit::rvalue format = gccjit::rvalue(c_format);
    std::vector<gccjit::rvalue> args = {format, value};
    gccjit::rvalue printf_call = m_context.new_call(m_printf_func, args);
    m_current_block.add_eval(printf_call);
}

void JITBackend::compile_print_bool(const LIR::LIR_Inst& inst) {
    // Print boolean using printf with conditional blocks
    gccjit::rvalue value = get_jit_register(inst.a);
    gccjit::block true_block = m_current_func.new_block("print_true");
    gccjit::block false_block = m_current_func.new_block("print_false");
    gccjit::block after_block = m_current_func.new_block("print_after");
    
    // Create conditional jump
    m_current_block.end_with_conditional(value, true_block, false_block);
    
    // True block: print "true"
    m_current_block = true_block;
    {
        const char* true_format = "true\n";
        gcc_jit_rvalue* c_true_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), true_format);
        gccjit::rvalue true_format_rval = gccjit::rvalue(c_true_format);
        std::vector<gccjit::rvalue> true_args = {true_format_rval};
        m_current_block.add_eval(m_context.new_call(m_printf_func, true_args));
        m_current_block.end_with_jump(after_block);
    }
    
    // False block: print "false"
    m_current_block = false_block;
    {
        const char* false_format = "false\n";
        gcc_jit_rvalue* c_false_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), false_format);
        gccjit::rvalue false_format_rval = gccjit::rvalue(c_false_format);
        std::vector<gccjit::rvalue> false_args = {false_format_rval};
        m_current_block.add_eval(m_context.new_call(m_printf_func, false_args));
        m_current_block.end_with_jump(after_block);
    }
    
    // Continue with after block
    m_current_block = after_block;
}

void JITBackend::compile_print_string(const LIR::LIR_Inst& inst) {
    // Print string using puts
    gccjit::rvalue value = get_jit_register(inst.a);
    std::vector<gccjit::rvalue> args = {value};
    gccjit::rvalue puts_call = m_context.new_call(m_puts_func, args);
    m_current_block.add_eval(puts_call);
}

void JITBackend::compile_return(const LIR::LIR_Inst& inst) {
    if (inst.a != 0) {
        gccjit::rvalue value = get_jit_register(inst.a);
        m_current_block.end_with_return(value);
    } else {
        // Return zero for void/nil returns
        gccjit::rvalue zero = m_context.new_rvalue(m_int_type, 0);
        m_current_block.end_with_return(zero);
    }
}

void JITBackend::compile_memory_op(const LIR::LIR_Inst& inst) {
    // Simplified memory operations
    switch (inst.op) {
        case LIR::LIR_Op::Load: {
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue ptr = get_jit_register(inst.a);
            gccjit::lvalue mem_access = m_context.new_cast(ptr, m_int_type.get_pointer()).dereference();
            gccjit::rvalue value = mem_access;
            m_current_block.add_assignment(dst, value);
            break;
        }
        case LIR::LIR_Op::Store: {
            gccjit::rvalue ptr = get_jit_register(inst.a);
            gccjit::rvalue value = get_jit_register(inst.b);
            gccjit::lvalue mem_access = m_context.new_cast(ptr, m_int_type.get_pointer()).dereference();
            m_current_block.add_assignment(mem_access, value);
            // Simplified - actual store would need more complex handling
            break;
        }
        default:
            break;
    }
}

gccjit::rvalue JITBackend::compile_string_concat(gccjit::rvalue a, gccjit::rvalue b) {
    // Ensure both operands are converted to C strings
    gccjit::rvalue a_str = compile_to_cstring(a);
    gccjit::rvalue b_str = compile_to_cstring(b);
    
    // Call the runtime concatenation function
    std::vector<gccjit::rvalue> args = {a_str, b_str};
    return m_context.new_call(m_runtime_concat_func, args);
}


gccjit::rvalue JITBackend::compile_string_format(gccjit::rvalue format, gccjit::rvalue arg) {
    // Ensure both operands are converted to C strings
    gccjit::rvalue format_str = compile_to_cstring(format);
    gccjit::rvalue arg_str = compile_to_cstring(arg);
    
    // Call the runtime formatting function
    std::vector<gccjit::rvalue> args = {format_str, arg_str};
    return m_context.new_call(m_runtime_format_func, args);
}


gccjit::rvalue JITBackend::compile_to_string(gccjit::rvalue value) {
    // Get the C type for comparison
    gcc_jit_type* c_type = value.get_type().get_inner_type();
    gcc_jit_type* c_int_type = m_int_type.get_inner_type();
    gcc_jit_type* c_double_type = m_double_type.get_inner_type();
    gcc_jit_type* c_bool_type = m_bool_type.get_inner_type();
    gcc_jit_type* c_const_char_ptr_type = m_const_char_ptr_type.get_inner_type();

    // If already a string, return as-is
    if (c_type == c_const_char_ptr_type) {
        return value;
    } else if (c_type == c_int_type) {
        // Convert int to string using snprintf
        // Allocate buffer for int string (max 12 digits + sign + null)
        gccjit::rvalue buffer_size = m_context.new_rvalue(m_size_t_type, 13);

        // Use permanent memory manager allocation
        std::vector<gccjit::param> mem_alloc_params;
        mem_alloc_params.push_back(m_context.new_param(m_size_t_type, "size"));
        gccjit::function mem_alloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "jit_mem_allocate_permanent", mem_alloc_params, 0);

        gccjit::rvalue buffer = m_context.new_call(mem_alloc_func, {buffer_size});

        gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "%d");
        gccjit::rvalue format_str = gccjit::rvalue(c_format);
        std::vector<gccjit::rvalue> snprintf_args = {buffer, buffer_size, format_str, value};
        m_context.new_call(m_snprintf_func, snprintf_args);

        // Cast to const char* before returning
        return m_context.new_cast(buffer, m_const_char_ptr_type);
    } else if (c_type == c_double_type) {
        // Convert double to string using snprintf
        // Allocate buffer for double string (max 32 characters)
        gccjit::rvalue buffer_size = m_context.new_rvalue(m_size_t_type, 33);

        // Use permanent memory manager allocation
        std::vector<gccjit::param> mem_alloc_params;
        mem_alloc_params.push_back(m_context.new_param(m_size_t_type, "size"));
        gccjit::function mem_alloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "jit_mem_allocate_permanent", mem_alloc_params, 0);

        gccjit::rvalue buffer = m_context.new_call(mem_alloc_func, {buffer_size});

        gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "%f");
        gccjit::rvalue format_str = gccjit::rvalue(c_format);
        std::vector<gccjit::rvalue> snprintf_args = {buffer, buffer_size, format_str, value};
        m_context.new_call(m_snprintf_func, snprintf_args);

        // Cast to const char* before returning
        return m_context.new_cast(buffer, m_const_char_ptr_type);
    } else if (c_type == c_bool_type) {
        // Convert bool to string using a local variable and conditional assignment
        // Create a local variable to hold the result
        gccjit::lvalue result_var = m_current_func.new_local(m_const_char_ptr_type, "bool_str_result");
        
        // Create blocks for the conditional
        gccjit::block true_block = m_current_func.new_block("bool_to_str_true");
        gccjit::block false_block = m_current_func.new_block("bool_to_str_false");
        gccjit::block merge_block = m_current_func.new_block("bool_to_str_merge");
        
        // Branch based on the boolean value
        m_current_block.end_with_conditional(value, true_block, false_block);
        
        // True block: assign "true"
        gcc_jit_rvalue* c_true_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "true");
        gccjit::rvalue true_str = gccjit::rvalue(c_true_str);
        true_block.add_assignment(result_var, true_str);
        true_block.end_with_jump(merge_block);
        
        // False block: assign "false"
        gcc_jit_rvalue* c_false_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "false");
        gccjit::rvalue false_str = gccjit::rvalue(c_false_str);
        false_block.add_assignment(result_var, false_str);
        false_block.end_with_jump(merge_block);
        
        // Continue in merge block
        m_current_block = merge_block;
        
        // Return the result variable as rvalue
        return result_var;
    } 
    else {
        // Default case: return empty string
        gcc_jit_rvalue* c_empty_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "");
        return gccjit::rvalue(c_empty_str);
    }
}

gccjit::rvalue JITBackend::compile_to_cstring(gccjit::rvalue value) {
    // If already a string pointer, just return it
    gcc_jit_type* c_type = value.get_type().get_inner_type();
    gcc_jit_type* c_const_char_ptr = m_const_char_ptr_type.get_inner_type();
    
    if (c_type == c_const_char_ptr) {
        return value;
    }
    
    // Otherwise convert to string
    return compile_to_string(value);
}


gccjit::type JITBackend::to_jit_type(LIR::Type type) {
    switch (type) {
        case LIR::Type::I32:
            return m_int_type;
        case LIR::Type::I64:
            return m_int_type;
        case LIR::Type::F64:
            return m_double_type;
        case LIR::Type::Bool:
            return m_bool_type;
        case LIR::Type::Ptr:
            return m_void_ptr_type;
        case LIR::Type::Void:
            return m_void_type;
        default:
            return m_int_type;
    }
}

gccjit::type JITBackend::to_jit_type(TypePtr type) {
    if (!type) {
        return m_int_type;
    }

    switch (type->tag) {
        case TypeTag::Bool:
            return m_bool_type;
        case TypeTag::Int:
        case TypeTag::Int8:
        case TypeTag::Int16:
        case TypeTag::Int32:
        case TypeTag::Int64:
        case TypeTag::Int128:
            return m_int_type;
        case TypeTag::UInt:
        case TypeTag::UInt8:
        case TypeTag::UInt16:
        case TypeTag::UInt32:
        case TypeTag::UInt64:
        case TypeTag::UInt128:
            return m_uint_type;
        case TypeTag::Float32:
        case TypeTag::Float64:
            return m_double_type;
        case TypeTag::String:
            return m_const_char_ptr_type;
        default:
            return m_void_ptr_type;
    }
}

gccjit::lvalue JITBackend::get_jit_register(LIR::Reg reg) {
    auto it = jit_registers.find(reg);
    if (it == jit_registers.end()) {
        // Create new register variable using tracked type (default to int)
        gccjit::type reg_type = m_int_type;
        auto type_it = register_types.find(reg);
        if (type_it != register_types.end()) {
            reg_type = type_it->second;
        }
        std::string name = "r" + std::to_string(reg);
        gccjit::lvalue jit_reg = m_current_func.new_local(reg_type, name.c_str());
        jit_registers[reg] = jit_reg;
        return jit_reg;
    }
    return it->second;
}

gccjit::lvalue JITBackend::get_jit_register(LIR::Reg reg, gccjit::type type) {
    auto it = jit_registers.find(reg);
    if (it == jit_registers.end()) {
        // Create new register variable
        std::string name = "r" + std::to_string(reg);
        gccjit::lvalue jit_reg = m_current_func.new_local(type, name.c_str());
        jit_registers[reg] = jit_reg;
        return jit_reg;
    }
    return it->second;
}

gccjit::lvalue JITBackend::get_jit_register_temp(gccjit::type type) {
    static int temp_counter = 0;
    std::string name = "temp" + std::to_string(temp_counter++);
    return m_current_func.new_local(type, name.c_str());
}

void JITBackend::set_jit_register(LIR::Reg reg, gccjit::lvalue value) {
    register_types[reg] = value.get_type();
    jit_registers[reg] = value;
}

CompileResult JITBackend::compile(CompileMode mode, const std::string& output_path) {
    CompileResult result;
    
    try {
        // First, check if we have a function to process
        if (processed_functions.empty()) {
            result.success = false;
            result.error_message = "No function to compile";
            return result;
        }
        
        // Process the first (and typically only) function
        const auto& function = processed_functions[0];
        
        // === SINGLE PASS: Process instructions and create blocks on the fly ===
        compile_function_single_pass(function);
        
        // Compile the context using proper gcc_jit flow
        if (m_debug_mode) {
            std::cout << "Compiling JIT context..." << std::endl;
        }
        
        gcc_jit_result* jit_result = m_context.compile();
        if (!jit_result) {
            result.success = false;
            result.error_message = "JIT compilation failed";
            return result;
        }
        
        // Get the compiled function code
        m_compiled_function = gcc_jit_result_get_code(jit_result, function.name.c_str());
        if (!m_compiled_function) {
            result.success = false;
            result.error_message = "Failed to get compiled function: " + function.name;
            return result;
        }
        
        if (m_debug_mode) {
            std::cout << "JIT compilation successful, function at: " << m_compiled_function << std::endl;
        }
        
        // Clean up the result (we don't need it anymore)
        gcc_jit_result_release(jit_result);
        
        // Set up the result based on compilation mode
        if (mode == CompileMode::ToMemory) {
            result.success = true;
            result.compiled_function = m_compiled_function;
        } else if (mode == CompileMode::ToFile || mode == CompileMode::ToExecutable) {
            // Compile to file
            std::string filename = output_path.empty() ? "output.o" : output_path;
            
            if (mode == CompileMode::ToExecutable) {
                m_context.compile_to_file(GCC_JIT_OUTPUT_KIND_EXECUTABLE, filename.c_str());
            } else {
                m_context.compile_to_file(GCC_JIT_OUTPUT_KIND_OBJECT_FILE, filename.c_str());
            }
            
            result.success = true;
            result.output_file = filename;
        }
        
    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = std::string("JIT compilation error: ") + e.what();
    }
    
    return result;
}

int JITBackend::execute_compiled_function(const std::vector<int>& args) {
    if (!m_compiled_function) {
        report_error("No compiled function available");
        return -1;
    }
    
    // Cast to function pointer with no parameters since our generated functions take no args
    typedef int (*func_type)();
    func_type func = reinterpret_cast<func_type>(m_compiled_function);
    
    // Call the function (no parameters needed for our test functions)
    return func();
}


void JITBackend::enable_optimizations(bool enable) {
    m_optimizations_enabled = enable;
    if (enable) {
        m_context.set_int_option(GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL, 2);
    } else {
        m_context.set_int_option(GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL, 0);
    }
}

void JITBackend::set_debug_mode(bool debug) {
    m_debug_mode = debug;
    if (debug) {
        // Don't set libgccjit debug to avoid overwhelming output
        // m_context.set_bool_option(GCC_JIT_BOOL_OPTION_DEBUGINFO, true);
        // m_context.set_bool_option(GCC_JIT_BOOL_OPTION_DUMP_INITIAL_GIMPLE, true);
        // m_context.set_bool_option(GCC_JIT_BOOL_OPTION_DUMP_GENERATED_CODE, true);
        m_context.set_int_option(GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL, 0);
    }
}

JITBackend::Stats JITBackend::get_stats() const {
    return m_stats;
}

void JITBackend::report_error(const std::string& message) {
    errors.push_back(message);
    if (m_debug_mode) {
        std::cerr << "JIT Error: " << message << std::endl;
    }
}

bool JITBackend::has_errors() const {
    return !errors.empty();
}

std::vector<std::string> JITBackend::get_errors() const {
    return errors;
}

// Memory management methods
void JITBackend::enter_memory_region() {
    if (!current_memory_region_) {
        current_memory_region_ = new MemoryManager<>::Region(memory_manager_);
    }
}

void JITBackend::exit_memory_region() {
    if (current_memory_region_) {
        delete current_memory_region_;
        current_memory_region_ = nullptr;
    }
}

void* JITBackend::allocate_in_region(size_t size, size_t alignment) {
    if (!current_memory_region_) {
        enter_memory_region();
    }
    return memory_manager_.allocate(size, alignment);
}

template<typename T, typename... Args>
T* JITBackend::create_object(Args&&... args) {
    if (!current_memory_region_) {
        enter_memory_region();
    }
    return current_memory_region_->create<T>(std::forward<Args>(args)...);
}

void JITBackend::cleanup_memory() {
    exit_memory_region();
   // memory_manager_.analyzeMemoryUsage();
}

} // namespace JIT
