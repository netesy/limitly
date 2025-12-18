#include "jit.hh"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "../value.hh"

// C wrapper functions for JIT string building
extern "C" {
    typedef struct {
        char* buffer;
        size_t capacity;
        size_t length;
        void* region;
    } jit_string_builder;
    
    // Memory manager wrapper functions
    void* limitly_mem_allocate(size_t size);
    void limitly_mem_deallocate(void* ptr);
    
    jit_string_builder* jit_sb_create();
    void jit_sb_destroy(jit_string_builder* sb);
    char* jit_sb_finish(jit_string_builder* sb);
    void jit_sb_append_cstr(jit_string_builder* sb, const char* s);
    void jit_sb_append_int(jit_string_builder* sb, long long v);
    void jit_sb_append_float(jit_string_builder* sb, double v);
    void jit_sb_append_bool(jit_string_builder* sb, int v);
}

// C wrapper implementations
void* limitly_mem_allocate(size_t size) {
    return MemoryManager<>::Unsafe::allocate(size);
}

void limitly_mem_deallocate(void* ptr) {
    MemoryManager<>::Unsafe::deallocate(ptr);
}

// C function implementations
jit_string_builder* jit_sb_create() {
    // Use memory manager for allocation
    jit_string_builder* sb = (jit_string_builder*)MemoryManager<>::Unsafe::allocate(sizeof(jit_string_builder));
    if (!sb) return NULL;
    
    sb->capacity = 128;
    sb->length = 0;
    sb->buffer = (char*)MemoryManager<>::Unsafe::allocate(sb->capacity);
    sb->region = NULL;
    
    if (!sb->buffer) {
        MemoryManager<>::Unsafe::deallocate(sb);
        return NULL;
    }
    
    sb->buffer[0] = '\0';
    return sb;
}

void jit_sb_destroy(jit_string_builder* sb) {
    if (sb) {
        if (sb->buffer) MemoryManager<>::Unsafe::deallocate(sb->buffer);
        MemoryManager<>::Unsafe::deallocate(sb);
    }
}

char* jit_sb_finish(jit_string_builder* sb) {
    if (!sb) return NULL;
    char* result = sb->buffer;
    sb->buffer = NULL;
    sb->length = 0;
    sb->capacity = 0;
    MemoryManager<>::Unsafe::deallocate(sb);
    return result;
}

void jit_sb_append_cstr(jit_string_builder* sb, const char* s) {
    if (!sb || !s) return;
    
    size_t len = strlen(s);
    if (sb->length + len + 1 > sb->capacity) {
        size_t new_cap = sb->capacity * 2;
        while (sb->length + len + 1 > new_cap) new_cap *= 2;
        
        char* new_buf = (char*)MemoryManager<>::Unsafe::resize(sb->buffer, new_cap);
        if (!new_buf) return;
        
        sb->buffer = new_buf;
        sb->capacity = new_cap;
    }
    
    memcpy(sb->buffer + sb->length, s, len);
    sb->length += len;
    sb->buffer[sb->length] = '\0';
}

void jit_sb_append_int(jit_string_builder* sb, long long v) {
    if (!sb) return;
    char temp[32];
    int n = snprintf(temp, sizeof(temp), "%lld", v);
    if (n > 0) jit_sb_append_cstr(sb, temp);
}

void jit_sb_append_float(jit_string_builder* sb, double v) {
    if (!sb) return;
    char temp[64];
    int n = snprintf(temp, sizeof(temp), "%g", v);
    if (n > 0) jit_sb_append_cstr(sb, temp);
}

void jit_sb_append_bool(jit_string_builder* sb, int v) {
    if (!sb) return;
    jit_sb_append_cstr(sb, v ? "true" : "false");
}

namespace JIT {

JITBackend::JITBackend() 
    : m_context(gccjit::context::acquire()), 
      m_optimizations_enabled(false),
      m_debug_mode(false),
      m_compiled_function(nullptr),
      m_jit_result(nullptr),
      current_memory_region_(nullptr) {
    
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

    // String builder helpers (imported from runtime)
    std::vector<gccjit::param> sb_create_params;
    m_jit_sb_create_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "jit_sb_create", sb_create_params, 0);
    
    std::vector<gccjit::param> sb_destroy_params;
    sb_destroy_params.push_back(m_context.new_param(m_void_ptr_type, "sb"));
    m_jit_sb_destroy_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "jit_sb_destroy", sb_destroy_params, 0);
    
    std::vector<gccjit::param> sb_finish_params;
    sb_finish_params.push_back(m_context.new_param(m_void_ptr_type, "sb"));
    m_jit_sb_finish_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_const_char_ptr_type, "jit_sb_finish", sb_finish_params, 0);
    
    std::vector<gccjit::param> sb_append_cstr_params;
    sb_append_cstr_params.push_back(m_context.new_param(m_void_ptr_type, "sb"));
    sb_append_cstr_params.push_back(m_context.new_param(m_const_char_ptr_type, "str"));
    m_jit_sb_append_cstr_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "jit_sb_append_cstr", sb_append_cstr_params, 0);
    
    std::vector<gccjit::param> sb_append_int_params;
    sb_append_int_params.push_back(m_context.new_param(m_void_ptr_type, "sb"));
    sb_append_int_params.push_back(m_context.new_param(m_int_type, "value"));
    m_jit_sb_append_int_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "jit_sb_append_int", sb_append_int_params, 0);
    
    std::vector<gccjit::param> sb_append_float_params;
    sb_append_float_params.push_back(m_context.new_param(m_void_ptr_type, "sb"));
    sb_append_float_params.push_back(m_context.new_param(m_double_type, "value"));
    m_jit_sb_append_float_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "jit_sb_append_float", sb_append_float_params, 0);
    
    std::vector<gccjit::param> sb_append_bool_params;
    sb_append_bool_params.push_back(m_context.new_param(m_void_ptr_type, "sb"));
    sb_append_bool_params.push_back(m_context.new_param(m_c_int_type, "value"));
    m_jit_sb_append_bool_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_type, "jit_sb_append_bool", sb_append_bool_params, 0);
    
    // Initialize stats
    m_stats = {0, 0, 0.0};
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

    for (const auto& entry : function.register_types) {
        register_types[entry.first] = to_jit_type(entry.second);
    }
    
    // Create function type and function
    std::vector<gccjit::param> param_types;
    for (uint32_t i = 0; i < function.param_count; ++i) {
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
                            dst = get_jit_register(inst.dst, m_uint_type);
                            // Explicitly cast to long to resolve ambiguity
                            {
                                long long val = std::stoll(inst.const_val->data);
                                value = m_context.new_rvalue(m_uint_type, static_cast<long>(val));
                            }
                            break;      
                        case TypeTag::UInt8:
                        case TypeTag::UInt16:
                        case TypeTag::UInt32:
                            dst = get_jit_register(inst.dst, m_uint_type);
                            // Explicitly cast to long to resolve the ambiguity
                            {

                                long long val = std::stoll(inst.const_val->data);
                                value = m_context.new_rvalue(m_uint_type, static_cast<long>(val));
                            }
                            break;
                        case TypeTag::UInt64:
                            dst = get_jit_register(inst.dst, m_uint_type);
                            // Handle large unsigned values that don't fit in signed int
                            try {
                                value = m_context.new_rvalue(m_uint_type, static_cast<long>(std::stoull(inst.const_val->data)));
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
        
        // String Builder Operations
        case LIR::LIR_Op::SBCreate: {
            gccjit::lvalue dst = get_jit_register(inst.dst, m_void_ptr_type);
            gccjit::rvalue result = compile_sb_create();
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        case LIR::LIR_Op::SBAppend: {
            gccjit::rvalue sb = get_jit_register(inst.dst);
            gccjit::rvalue value = get_jit_register(inst.a);
            compile_sb_append(inst.dst, inst.a, sb, value);
            return m_context.new_rvalue(m_int_type, 0);
        }
        
        case LIR::LIR_Op::SBFinish: {
            gccjit::lvalue dst = get_jit_register(inst.dst, m_const_char_ptr_type);
            gccjit::rvalue sb = get_jit_register(inst.a);
            gccjit::rvalue result = compile_sb_finish(sb);
            m_current_block.add_assignment(dst, result);
            return result;
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
    // Simplified call implementation
    gccjit::rvalue result = m_context.new_rvalue(m_int_type, 0);
    gccjit::lvalue dst = get_jit_register(inst.dst);
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
    // For proper string concatenation, we need to:
    // 1. Allocate memory for the result string
    // 2. Copy both strings into the result
    // 3. Return the result
    
    // For now, implement a simple version using sprintf
    // Get lengths of both strings (simplified)
    std::vector<gccjit::rvalue> strlen_args_a = {a};
    gccjit::rvalue len_a = m_context.new_call(m_strlen_func, strlen_args_a);
    
    std::vector<gccjit::rvalue> strlen_args_b = {b};
    gccjit::rvalue len_b = m_context.new_call(m_strlen_func, strlen_args_b);
    
    gccjit::rvalue total_len = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_size_t_type, len_a, len_b);
    total_len = m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_size_t_type, total_len, 
                                       m_context.new_rvalue(m_size_t_type, 1)); // +1 for null terminator
    
    // Use memory manager allocation instead of malloc
    // Create a custom allocation function that uses our memory manager
    std::vector<gccjit::param> mem_alloc_params;
    mem_alloc_params.push_back(m_context.new_param(m_size_t_type, "size"));
    gccjit::function mem_alloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "limitly_mem_allocate", mem_alloc_params, 0);
    
    // Allocate memory for result using our memory manager
    std::vector<gccjit::rvalue> alloc_args = {total_len};
    gccjit::rvalue result_ptr = m_context.new_call(mem_alloc_func, alloc_args);
    
    // Use sprintf to concatenate
    gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "%s%s");
    gccjit::rvalue format_str = gccjit::rvalue(c_format);
    std::vector<gccjit::rvalue> sprintf_args = {result_ptr, format_str, a, b};
    m_context.new_call(m_sprintf_func, sprintf_args);
    
    return result_ptr;
}

gccjit::rvalue JITBackend::compile_to_string(gccjit::rvalue value) {
    // Convert value to string representation
    // Get the C type for comparison
    gcc_jit_type* c_type = value.get_type().get_inner_type();
    gcc_jit_type* c_int_type = m_int_type.get_inner_type();
    gcc_jit_type* c_double_type = m_double_type.get_inner_type();
    gcc_jit_type* c_bool_type = m_bool_type.get_inner_type();
    gcc_jit_type* c_const_char_ptr_type = m_const_char_ptr_type.get_inner_type();

    if (c_type == c_int_type) {
        // Convert int to string using snprintf
        // Allocate buffer for int string (max 12 digits + sign + null)
        gccjit::rvalue buffer_size = m_context.new_rvalue(m_size_t_type, 13);

        // Use memory manager allocation function
        std::vector<gccjit::param> mem_alloc_params;
        mem_alloc_params.push_back(m_context.new_param(m_size_t_type, "size"));
        gccjit::function mem_alloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "limitly_mem_allocate", mem_alloc_params, 0);

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

        // Use memory manager allocation function
        std::vector<gccjit::param> mem_alloc_params;
        mem_alloc_params.push_back(m_context.new_param(m_size_t_type, "size"));
        gccjit::function mem_alloc_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "limitly_mem_allocate", mem_alloc_params, 0);

        gccjit::rvalue buffer = m_context.new_call(mem_alloc_func, {buffer_size});

        gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "%f");
        gccjit::rvalue format_str = gccjit::rvalue(c_format);
        std::vector<gccjit::rvalue> snprintf_args = {buffer, buffer_size, format_str, value};
        m_context.new_call(m_snprintf_func, snprintf_args);

        // Cast to const char* before returning
        return m_context.new_cast(buffer, m_const_char_ptr_type);
    } else if (c_type == c_bool_type) {
        // Convert bool to string using conditional
        gccjit::block true_block = m_current_func.new_block("to_string_true");
        gccjit::block false_block = m_current_func.new_block("to_string_false");
        gccjit::block after_block = m_current_func.new_block("to_string_after");

        // Create conditional jump
        m_current_block.end_with_conditional(value, true_block, false_block);

        // True block: return "true"
        m_current_block = true_block;
        {
            gcc_jit_rvalue* c_true_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "true");
            gccjit::rvalue true_str = gccjit::rvalue(c_true_str);
            m_current_block.end_with_return(true_str);
        }

        // False block: return "false"
        m_current_block = false_block;
        {
            gcc_jit_rvalue* c_false_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "false");
            gccjit::rvalue false_str = gccjit::rvalue(c_false_str);
            m_current_block.end_with_return(false_str);
        }
        
        // Set current block to after block for subsequent code
        m_current_block = after_block;
        
        // Return a default value (this won't be reached due to the returns above)
        gcc_jit_rvalue* c_default_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "");
        return gccjit::rvalue(c_default_str);
    } else {
        // Default case: return empty string
        gcc_jit_rvalue* c_empty_str = gcc_jit_context_new_string_literal(m_context.get_inner_context(), "");
        return gccjit::rvalue(c_empty_str);
    }
}

gccjit::rvalue JITBackend::compile_sb_create() {
    std::vector<gccjit::rvalue> args;
    return m_context.new_call(m_jit_sb_create_func, args);
}

void JITBackend::compile_sb_append(LIR::Reg sb_reg, LIR::Reg value_reg, gccjit::rvalue sb, gccjit::rvalue value) {
    auto it = register_types.find(value_reg);
    gccjit::type value_type = (it != register_types.end()) ? it->second : value.get_type();
    auto inner = value_type.get_inner_type();
    if (inner == m_const_char_ptr_type.get_inner_type()) {
        compile_sb_append_string(sb, value);
    } else if (inner == m_int_type.get_inner_type()) {
        compile_sb_append_int(sb, value);
    } else if (inner == m_double_type.get_inner_type()) {
        compile_sb_append_double(sb, value);
    } else if (inner == m_bool_type.get_inner_type()) {
        compile_sb_append_bool(sb, value);
    } else {
        gccjit::rvalue str_val = compile_to_string(value);
        compile_sb_append_string(sb, str_val);
    }
}

void JITBackend::compile_sb_append_string(gccjit::rvalue sb, gccjit::rvalue str) {
    std::vector<gccjit::rvalue> args = {sb, str};
    gccjit::rvalue call = m_context.new_call(m_jit_sb_append_cstr_func, args);
    m_current_block.add_eval(call);
}

void JITBackend::compile_sb_append_int(gccjit::rvalue sb, gccjit::rvalue value) {
    if (value.get_type().get_inner_type() != m_int_type.get_inner_type()) {
        value = m_context.new_cast(value, m_int_type);
    }
    std::vector<gccjit::rvalue> args = {sb, value};
    gccjit::rvalue call = m_context.new_call(m_jit_sb_append_int_func, args);
    m_current_block.add_eval(call);
}

void JITBackend::compile_sb_append_double(gccjit::rvalue sb, gccjit::rvalue value) {
    if (value.get_type().get_inner_type() != m_double_type.get_inner_type()) {
        value = m_context.new_cast(value, m_double_type);
    }
    std::vector<gccjit::rvalue> args = {sb, value};
    gccjit::rvalue call = m_context.new_call(m_jit_sb_append_float_func, args);
    m_current_block.add_eval(call);
}

void JITBackend::compile_sb_append_bool(gccjit::rvalue sb, gccjit::rvalue value) {
    if (value.get_type().get_inner_type() != m_c_int_type.get_inner_type()) {
        value = m_context.new_cast(value, m_c_int_type);
    }
    std::vector<gccjit::rvalue> args = {sb, value};
    gccjit::rvalue call = m_context.new_call(m_jit_sb_append_bool_func, args);
    m_current_block.add_eval(call);
}

gccjit::rvalue JITBackend::compile_sb_finish(gccjit::rvalue sb) {
    std::vector<gccjit::rvalue> args = {sb};
    return m_context.new_call(m_jit_sb_finish_func, args);
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
        case TypeTag::UInt:
        case TypeTag::UInt8:
        case TypeTag::UInt16:
        case TypeTag::UInt32:
        case TypeTag::UInt64:
        case TypeTag::UInt128:
            return m_int_type;
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
        // Create new register variable with specified type
        std::string name = "r" + std::to_string(reg);
        gccjit::lvalue jit_reg = m_current_func.new_local(type, name.c_str());
        jit_registers[reg] = jit_reg;
        register_types[reg] = type;
        return jit_reg;
    }
    return it->second;
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
