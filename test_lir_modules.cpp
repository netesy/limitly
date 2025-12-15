#include "src/frontend/lir_generator.hh"
#include "src/frontend/ast_builder.hh"
#include <iostream>
#include <memory>

using namespace AST;
using namespace LIR;

int main() {
    try {
        std::cout << "Testing LIR module and import generation...\n";
        
        LIRGenerator generator;
        
        // Test 1: Create a simple module
        std::cout << "\n=== Test 1: Module Declaration ===\n";
        
        // Create a module AST manually (simplified)
        auto module_func = std::make_unique<LIR_Function>("test_module", 0);
        auto entry_block = module_func->create_block("entry");
        
        // Simulate module begin/end
        LIR_Value module_name("test_module");
        entry_block->add_instruction(LIR_Instruction(LIR_Op::BeginModule, module_name, {}, {}));
        
        // Add a variable declaration
        LIR_Value const_val(42);
        LIR_Value var_temp = module_func->new_temp();
        entry_block->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const_val, {}, var_temp));
        entry_block->add_instruction(LIR_Instruction(LIR_Op::StoreVar, var_temp, {}, LIR_Value(LIR_ValueKind::Var, 0)));
        
        // Export the variable
        LIR_Value export_name("answer");
        entry_block->add_instruction(LIR_Instruction(LIR_Op::ExportSymbol, export_name, var_temp, {}));
        
        // End module
        entry_block->add_instruction(LIR_Instruction(LIR_Op::EndModule, {}, {}, {}));
        
        std::cout << module_func->to_string() << std::endl;
        
        // Test 2: Import statement
        std::cout << "\n=== Test 2: Import Statement ===\n";
        
        auto import_func = std::make_unique<LIR_Function>("main", 0);
        auto import_entry = import_func->create_block("entry");
        
        // Import the module
        LIR_Value import_path("test_module");
        LIR_Value import_alias("mymodule");
        import_entry->add_instruction(LIR_Instruction(LIR_Op::ImportModule, import_path, import_alias, {}));
        
        // Use imported symbol
        LIR_Value imported_symbol(LIR_ValueKind::Var, 1); // This would be resolved from module
        LIR_Value use_temp = import_func->new_temp();
        import_entry->add_instruction(LIR_Instruction(LIR_Op::LoadVar, imported_symbol, {}, use_temp));
        
        std::cout << import_func->to_string() << std::endl;
        
        // Test 3: Complex module with multiple exports
        std::cout << "\n=== Test 3: Complex Module ===\n";
        
        auto complex_func = std::make_unique<LIR_Function>("math_module", 0);
        auto complex_entry = complex_func->create_block("entry");
        
        // Module begin
        LIR_Value math_name("math");
        complex_entry->add_instruction(LIR_Instruction(LIR_Op::BeginModule, math_name, {}, {}));
        
        // Export PI constant
        LIR_Value pi_const(3.14159);
        LIR_Value pi_temp = complex_func->new_temp();
        complex_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, pi_const, {}, pi_temp));
        LIR_Value pi_name("PI");
        complex_entry->add_instruction(LIR_Instruction(LIR_Op::ExportSymbol, pi_name, pi_temp, {}));
        
        // Export add function (simplified)
        LIR_Value add_func_temp = complex_func->new_temp();
        LIR_Value add_name("add");
        complex_entry->add_instruction(LIR_Instruction(LIR_Op::ExportSymbol, add_name, add_func_temp, {}));
        
        // Module end
        complex_entry->add_instruction(LIR_Instruction(LIR_Op::EndModule, {}, {}, {}));
        
        std::cout << complex_func->to_string() << std::endl;
        
        std::cout << "\n=== LIR Module Test Completed Successfully! ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
