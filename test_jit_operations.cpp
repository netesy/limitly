#include "src/backend/jit/jit.hh"
#include "src/lir/lir.hh"
#include <iostream>
#include <vector>

int main() {
    using namespace LIR;
    using namespace JIT;
    
    // Create a simple test function: add two numbers
    LIR_Function test_func("test_add", 2);
    
    // r2 = r0 + r1
    LIR_Inst add_inst(LIR_Op::Add, 2, 0, 1);
    add_inst.comment = "Add two parameters";
    test_func.add_instruction(add_inst);
    
    // return r2
    LIR_Inst ret_inst(LIR_Op::Return, 0, 2);
    test_func.add_instruction(ret_inst);
    
    // Create JIT backend
    JITBackend jit;
    jit.set_debug_mode(true);
    
    // Process the function
    std::cout << "Processing function..." << std::endl;
    jit.process_function(test_func);
    
    // Compile to memory
    std::cout << "Compiling to memory..." << std::endl;
    auto result = jit.compile(JIT::CompileMode::ToMemory);
    
    if (result.success) {
        std::cout << "Compilation successful!" << std::endl;
        
        // Execute the compiled function
        std::vector<int> args = {10, 20};
        int result_val = jit.execute_compiled_function(args);
        std::cout << "Result: " << result_val << " (expected: 30)" << std::endl;
        
        // Show stats
        auto stats = jit.get_stats();
        std::cout << "Functions compiled: " << stats.functions_compiled << std::endl;
        std::cout << "Instructions compiled: " << stats.instructions_compiled << std::endl;
        std::cout << "Compilation time: " << stats.compilation_time_ms << "ms" << std::endl;
    } else {
        std::cerr << "Compilation failed: " << result.error_message << std::endl;
        return 1;
    }
    
    // Test other operations
    std::cout << "\nTesting other operations..." << std::endl;
    
    // Test arithmetic operations
    LIR_Function arithmetic_test("test_arithmetic", 2);
    
    // r2 = r0 * r1
    arithmetic_test.add_instruction(LIR_Inst(LIR_Op::Mul, 2, 0, 1));
    // r3 = r2 / r1
    arithmetic_test.add_instruction(LIR_Inst(LIR_Op::Div, 3, 2, 1));
    // r4 = r2 % r1
    arithmetic_test.add_instruction(LIR_Inst(LIR_Op::Mod, 4, 2, 1));
    // return r3
    arithmetic_test.add_instruction(LIR_Inst(LIR_Op::Return, 0, 3));
    
    JITBackend jit_arith;
    jit_arith.process_function(arithmetic_test);
    auto arith_result = jit_arith.compile(JIT::CompileMode::ToMemory);
    
    if (arith_result.success) {
        std::vector<int> args = {15, 3};
        int arith_val = jit_arith.execute_compiled_function(args);
        std::cout << "Arithmetic result: " << arith_val << " (expected: 5)" << std::endl;
    }
    
    // Test comparison operations
    std::cout << "\nTesting comparison operations..." << std::endl;
    
    LIR_Function comparison_test("test_comparison", 2);
    
    // r2 = r0 == r1
    comparison_test.add_instruction(LIR_Inst(LIR_Op::CmpEQ, 2, 0, 1));
    // return r2
    comparison_test.add_instruction(LIR_Inst(LIR_Op::Return, 0, 2));
    
    JITBackend jit_cmp;
    jit_cmp.process_function(comparison_test);
    auto cmp_result = jit_cmp.compile(JIT::CompileMode::ToMemory);
    
    if (cmp_result.success) {
        std::vector<int> args = {10, 10};
        int cmp_val = jit_cmp.execute_compiled_function(args);
        std::cout << "Comparison result: " << cmp_val << " (expected: 1 for true)" << std::endl;
    }
    
    std::cout << "\nAll tests completed!" << std::endl;
    return 0;
}
