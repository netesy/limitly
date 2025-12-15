#include "src/frontend/lir_generator.hh"
#include "src/frontend/ast_builder.hh"
#include <iostream>
#include <memory>

using namespace AST;
using namespace LIR;

int main() {
    try {
        // Create a simple AST for testing
        // This would normally be built by the parser, but we'll create it manually
        LIRGenerator generator;
        
        // Test basic expression generation
        std::cout << "Testing LIR generation...\n";
        
        // Create a simple program AST (this is just a placeholder - you'd need actual AST nodes)
        // For now, let's just test the LIR structures
        
        // Create a simple LIR function manually to test the structures
        auto func = std::make_unique<LIR_Function>("test_function", 2);
        
        // Create some blocks
        auto entry = func->create_block("entry");
        auto body = func->create_block("body");
        auto exit = func->create_block("exit");
        
        // Add some instructions
        LIR_Value const1(42);
        LIR_Value const2(24);
        LIR_Value temp1 = func->new_temp();
        LIR_Value temp2 = func->new_temp();
        
        entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const1, {}, temp1));
        entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const2, {}, temp2));
        entry->add_instruction(LIR_Instruction(LIR_Op::Add, temp1, temp2, temp1));
        entry->add_instruction(LIR_Instruction(LIR_Op::Jump, {}, {}, LIR_Value(LIR_ValueKind::Temp, body->id)));
        
        body->add_instruction(LIR_Instruction(LIR_Op::Return, temp1, {}, {}));
        
        // Print the generated LIR
        std::cout << func->to_string() << std::endl;
        
        std::cout << "LIR generation test completed successfully!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
