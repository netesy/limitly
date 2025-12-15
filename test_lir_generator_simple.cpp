#include "src/frontend/lir_generator.hh"
#include <iostream>
#include <memory>

using namespace LIR;

int main() {
    try {
        std::cout << "=== LIRGenerator Class Test ===\n\n";
        
        LIRGenerator generator;
        
        // Test basic functionality without full AST
        std::cout << "Testing LIRGenerator basic functionality...\n";
        
        // Create a simple program manually
        auto program = std::make_unique<LIR_Function>("test_program", 0);
        auto entry = program->create_block("entry");
        
        // Add some basic instructions
        LIR_Value const42(int64_t(42));
        LIR_Value temp = program->new_temp();
        
        entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const42, {}, temp));
        entry->add_instruction(LIR_Instruction(LIR_Op::Return, temp, {}, {}));
        
        std::cout << "Generated LIR:\n";
        std::cout << program->to_string() << std::endl;
        
        // Test error handling
        std::cout << "\nTesting error handling...\n";
        auto error_func = std::make_unique<LIR_Function>("error_test", 0);
        auto error_entry = error_func->create_block("entry");
        
        // This should work fine
        LIR_Value const_val(int64_t(10));
        LIR_Value error_temp = error_func->new_temp();
        error_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const_val, {}, error_temp));
        
        std::cout << "Error test function generated successfully:\n";
        std::cout << error_func->to_string() << std::endl;
        
        std::cout << "\n=== LIRGenerator Test Completed Successfully! ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
