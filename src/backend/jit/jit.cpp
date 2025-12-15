#include "jit.hh"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <cstdio>

namespace JIT {

JITBackend::JITBackend() 
    : m_context(gccjit::context::acquire()), 
      m_optimizations_enabled(false),
      m_debug_mode(false),
      m_compiled_function(nullptr) {
    
    // Initialize basic types
    m_void_type = m_context.get_type(GCC_JIT_TYPE_VOID);
    m_int_type = m_context.get_type(GCC_JIT_TYPE_LONG_LONG);
    m_double_type = m_context.get_type(GCC_JIT_TYPE_DOUBLE);
    m_bool_type = m_context.get_type(GCC_JIT_TYPE_BOOL);
    m_const_char_ptr_type = m_context.get_type(GCC_JIT_TYPE_CONST_CHAR_PTR);
    m_void_ptr_type = m_context.get_type(GCC_JIT_TYPE_VOID_PTR);
    
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
    
    std::vector<gccjit::param> puts_params;
    puts_params.push_back(m_context.new_param(m_const_char_ptr_type, "str"));
    m_puts_func = m_context.new_function(GCC_JIT_FUNCTION_IMPORTED, m_int_type, "puts", puts_params, 0);
    
    // Initialize stats
    m_stats = {0, 0, 0.0};
}

JITBackend::~JITBackend() {
    // Context will be automatically cleaned up by libgccjit++
}

void JITBackend::process_function(const LIR::LIR_Function& function) {
    processed_functions.push_back(function);
    compile_function(function);
}

void JITBackend::compile_function(const LIR::LIR_Function& function) {
    Timer timer;
    
    // Clear previous state
    jit_registers.clear();
    
    // Create function type and function
    std::vector<gccjit::param> param_types;
    for (uint32_t i = 0; i < function.param_count; ++i) {
        param_types.push_back(m_context.new_param(m_int_type, ("param" + std::to_string(i)).c_str()));
    }
    
    m_current_func = m_context.new_function(GCC_JIT_FUNCTION_EXPORTED, m_int_type, function.name.c_str(), param_types, 0);
    
    // Create entry block
    m_current_block = m_current_func.new_block("entry");
    
    // Allocate registers for parameters
    for (uint32_t i = 0; i < function.param_count; ++i) {
        gccjit::lvalue param = m_current_func.get_param(i);
        set_jit_register(i, param);
    }
    
    // Compile instructions
    for (const auto& inst : function.instructions) {
        compile_instruction(inst);
        m_stats.instructions_compiled++;
    }
    
    // Add implicit return if none exists
    if (function.instructions.empty() || 
        function.instructions.back().op != LIR::LIR_Op::Return) {
        m_current_block.add_eval(m_context.new_rvalue(m_int_type, 0));
        m_current_block.end_with_return(m_context.new_rvalue(m_int_type, 0));
    }
    
    // Update stats
    m_stats.functions_compiled++;
    m_stats.compilation_time_ms += timer.elapsed_ms();
}

gccjit::rvalue JITBackend::compile_instruction(const LIR::LIR_Inst& inst) {
    switch (inst.op) {
        // Data Movement
        case LIR::LIR_Op::Mov: {
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue src = get_jit_register(inst.a);
            m_current_block.add_assignment(dst, src);
            return src;
        }
        
        case LIR::LIR_Op::LoadConst: {
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue value;
            
            if (inst.const_val) {
                // Handle different value types based on the Value's type
                if (inst.const_val->type) {
                    switch (inst.const_val->type->tag) {
                        case TypeTag::Int:
                        case TypeTag::Int8:
                        case TypeTag::Int16:
                        case TypeTag::Int32:
                        case TypeTag::Int64:
                            value = m_context.new_rvalue(m_int_type, std::stoi(inst.const_val->data));
                            break;
                        case TypeTag::Float32:
                        case TypeTag::Float64:
                            value = m_context.new_rvalue(m_double_type, std::stod(inst.const_val->data));
                            break;
                        case TypeTag::Bool:
                            value = m_context.new_rvalue(m_bool_type, inst.const_val->data == "true" ? 1 : 0);
                            break;
                        case TypeTag::String:
                            // For string constants, create a global string
                            value = m_context.new_rvalue(m_const_char_ptr_type, 0);
                            break;
                        case TypeTag::Nil:
                        default:
                            value = m_context.new_rvalue(m_int_type, 0);
                            break;
                    }
                } else {
                    // Default to nil/int zero
                    value = m_context.new_rvalue(m_int_type, 0);
                }
            } else {
                // No constant value, default to zero
                value = m_context.new_rvalue(m_int_type, 0);
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
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_arithmetic_op(inst.op, a, b);
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        // Bitwise Operations
        case LIR::LIR_Op::And:
        case LIR::LIR_Op::Or:
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
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_comparison_op(inst.op, a, b);
            m_current_block.add_assignment(dst, result);
            return result;
        }
        
        // Control Flow
        case LIR::LIR_Op::Jump:
            compile_jump(inst);
            break;
            
        case LIR::LIR_Op::JumpIfFalse:
            compile_conditional_jump(inst);
            break;
            
        case LIR::LIR_Op::Call:
            compile_call(inst);
            break;
            
        case LIR::LIR_Op::Print:
            compile_print(inst);
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
            gccjit::lvalue dst = get_jit_register(inst.dst);
            gccjit::rvalue a = get_jit_register(inst.a);
            gccjit::rvalue b = get_jit_register(inst.b);
            gccjit::rvalue result = compile_string_concat(a, b);
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
    switch (op) {
        case LIR::LIR_Op::Add:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_PLUS, m_int_type, a, b);
        case LIR::LIR_Op::Sub:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MINUS, m_int_type, a, b);
        case LIR::LIR_Op::Mul:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MULT, m_int_type, a, b);
        case LIR::LIR_Op::Div:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_DIVIDE, m_int_type, a, b);
        case LIR::LIR_Op::Mod:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_MODULO, m_int_type, a, b);
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
    
    gccjit::rvalue bool_result = m_context.new_comparison(comparison, a, b);
    // Cast boolean to int (0 or 1) for storage in integer register
    return m_context.new_cast(bool_result, m_int_type);
}

gccjit::rvalue JITBackend::compile_bitwise_op(LIR::LIR_Op op, gccjit::rvalue a, gccjit::rvalue b) {
    switch (op) {
        case LIR::LIR_Op::And:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_LOGICAL_AND, m_int_type, a, b);
        case LIR::LIR_Op::Or:
            return m_context.new_binary_op(GCC_JIT_BINARY_OP_LOGICAL_OR, m_int_type, a, b);
        case LIR::LIR_Op::Xor:
            // XOR is not directly available, implement as (a & ~b) | (~a & b)
            return a; // Simplified for now
        default:
            return a;
    }
}

void JITBackend::compile_jump(const LIR::LIR_Inst& inst) {
    // For now, just end the block (simplified)
    m_current_block.end_with_jump(m_current_block);
}

void JITBackend::compile_conditional_jump(const LIR::LIR_Inst& inst) {
    gccjit::rvalue condition = get_jit_register(inst.a);
    
    // Create true and false blocks
    gccjit::block true_block = m_current_func.new_block("true");
    gccjit::block false_block = m_current_func.new_block("false");
    
    // Conditional jump
    m_current_block.end_with_conditional(condition, true_block, false_block);
    
    // Set current block to false block for now (simplified)
    m_current_block = false_block;
}

void JITBackend::compile_call(const LIR::LIR_Inst& inst) {
    // Simplified call implementation
    gccjit::rvalue result = m_context.new_rvalue(m_int_type, 0);
    gccjit::lvalue dst = get_jit_register(inst.dst);
    m_current_block.add_assignment(dst, result);
}

void JITBackend::compile_print(const LIR::LIR_Inst& inst) {
    // Print the value in register a
    gccjit::rvalue value = get_jit_register(inst.a);
    
    // Get the C type for comparison
    gcc_jit_type* c_type = value.get_type().get_inner_type();
    gcc_jit_type* c_int_type = m_int_type.get_inner_type();
    gcc_jit_type* c_double_type = m_double_type.get_inner_type();
    gcc_jit_type* c_bool_type = m_bool_type.get_inner_type();
    gcc_jit_type* c_const_char_ptr_type = m_const_char_ptr_type.get_inner_type();
    
    // Handle different types for printing
    if (c_type == c_int_type) {
        // Print integer using printf
        const char* format_str = "%d\n";
        gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), format_str);
        gccjit::rvalue format = gccjit::rvalue(c_format);
        std::vector<gccjit::rvalue> args = {format, value};
        gccjit::rvalue printf_call = m_context.new_call(m_printf_func, args);
        m_current_block.add_eval(printf_call);
    } else if (c_type == c_double_type) {
        // Print double using printf
        const char* format_str = "%f\n";
        gcc_jit_rvalue* c_format = gcc_jit_context_new_string_literal(m_context.get_inner_context(), format_str);
        gccjit::rvalue format = gccjit::rvalue(c_format);
        std::vector<gccjit::rvalue> args = {format, value};
        gccjit::rvalue printf_call = m_context.new_call(m_printf_func, args);
        m_current_block.add_eval(printf_call);
    } else if (c_type == c_bool_type) {
        // Print boolean using printf with conditional
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
    } else {
        // Default: print as string using puts
        std::vector<gccjit::rvalue> args = {value};
        gccjit::rvalue puts_call = m_context.new_call(m_puts_func, args);
        m_current_block.add_eval(puts_call);
    }
}

void JITBackend::compile_return(const LIR::LIR_Inst& inst) {
    if (inst.a != 0) {
        gccjit::rvalue value = get_jit_register(inst.a);
        m_current_block.end_with_return(value);
    } else {
        m_current_block.end_with_return(m_context.new_rvalue(m_int_type, 0));
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
    // Simplified string concatenation - for now just return first string
    // Real implementation would need proper string handling
    return a;
}

gccjit::lvalue JITBackend::get_jit_register(LIR::Reg reg) {
    auto it = jit_registers.find(reg);
    if (it == jit_registers.end()) {
        // Create new register variable
        std::string name = "r" + std::to_string(reg);
        gccjit::lvalue jit_reg = m_current_func.new_local(m_int_type, name.c_str());
        jit_registers[reg] = jit_reg;
        return jit_reg;
    }
    return it->second;
}

void JITBackend::set_jit_register(LIR::Reg reg, gccjit::lvalue value) {
    jit_registers[reg] = value;
}

CompileResult JITBackend::compile(CompileMode mode, const std::string& output_path) {
    CompileResult result;
    
    try {
        if (mode == CompileMode::ToMemory) {
            // Compile to memory
            gcc_jit_result* jit_result = m_context.compile();
            if (jit_result) {
                m_compiled_function = gcc_jit_result_get_code(jit_result, processed_functions[0].name.c_str());
                result.success = true;
                result.compiled_function = m_compiled_function;
            } else {
                result.success = false;
                result.error_message = "JIT compilation failed";
            }
        } else if (mode == CompileMode::ToFile || mode == CompileMode::ToExecutable) {
            // Compile to file
            std::string filename = output_path.empty() ? "output.o" : output_path;
            
            if (mode == CompileMode::ToExecutable) {
                // Compile directly to executable using libgccjit
                m_context.compile_to_file(GCC_JIT_OUTPUT_KIND_EXECUTABLE, filename.c_str());
                result.success = true;
                result.output_file = filename;
            } else {
                // Compile to object file
                m_context.compile_to_file(GCC_JIT_OUTPUT_KIND_OBJECT_FILE, filename.c_str());
                result.success = true;
                result.output_file = filename;
            }
        }
    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = e.what();
    }
    
    return result;
}

int JITBackend::execute_compiled_function(const std::vector<int>& args) {
    if (!m_compiled_function) {
        report_error("No compiled function available");
        return -1;
    }
    
    // Cast to function pointer and call
    typedef int (*func_type)(int, int, int, int);
    func_type func = reinterpret_cast<func_type>(m_compiled_function);
    
    // Call with arguments (simplified - max 4 args)
    int a0 = args.size() > 0 ? args[0] : 0;
    int a1 = args.size() > 1 ? args[1] : 0;
    int a2 = args.size() > 2 ? args[2] : 0;
    int a3 = args.size() > 3 ? args[3] : 0;
    
    return func(a0, a1, a2, a3);
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
        m_context.set_bool_option(GCC_JIT_BOOL_OPTION_DEBUGINFO, true);
        m_context.set_bool_option(GCC_JIT_BOOL_OPTION_DUMP_INITIAL_TREE, true);
        m_context.set_bool_option(GCC_JIT_BOOL_OPTION_DUMP_GENERATED_CODE, true);
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

} // namespace JIT
