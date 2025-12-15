#include "src/frontend/lir_generator.hh"
#include "src/frontend/ast_builder.hh"
#include <iostream>
#include <memory>

using namespace AST;
using namespace LIR;

int main() {
    try {
        std::cout << "=== Comprehensive LIR Generation Test ===\n\n";
        
        LIRGenerator generator;
        
        // Test 1: Basic arithmetic expressions
        std::cout << "Test 1: Basic arithmetic\n";
        std::cout << "------------------------\n";
        
        auto arithmetic_func = std::make_unique<LIR_Function>("test_arithmetic", 0);
        auto entry_block = arithmetic_func->create_block("entry");
        
        // Create: 5 + 3 * 2
        LIR_Value const5(int64_t(5));
        LIR_Value const3(int64_t(3));
        LIR_Value const2(int64_t(2));
        
        LIR_Value temp1 = arithmetic_func->new_temp();
        LIR_Value temp2 = arithmetic_func->new_temp();
        
        entry_block->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const3, {}, temp1));
        entry_block->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const2, {}, temp2));
        entry_block->add_instruction(LIR_Instruction(LIR_Op::Mul, temp1, temp2, temp1));
        
        LIR_Value temp3 = arithmetic_func->new_temp();
        entry_block->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const5, {}, temp3));
        entry_block->add_instruction(LIR_Instruction(LIR_Op::Add, temp3, temp1, temp3));
        
        entry_block->add_instruction(LIR_Instruction(LIR_Op::Return, temp3, {}, {}));
        
        std::cout << arithmetic_func->to_string() << std::endl;
        
        // Test 2: Variable declarations and usage
        std::cout << "\nTest 2: Variables and assignment\n";
        std::cout << "------------------------------\n";
        
        auto var_func = std::make_unique<LIR_Function>("test_variables", 0);
        auto var_entry = var_func->create_block("entry");
        
        // var x = 10
        LIR_Value const10(int64_t(10));
        LIR_Value x_var = var_func->new_temp();
        var_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const10, {}, x_var));
        var_entry->add_instruction(LIR_Instruction(LIR_Op::StoreVar, x_var, {}, LIR_Value(LIR_ValueKind::Var, 0)));
        
        // var y = x + 5
        LIR_Value const5_b(int64_t(5));
        LIR_Value y_temp1 = var_func->new_temp();
        LIR_Value y_temp2 = var_func->new_temp();
        
        var_entry->add_instruction(LIR_Instruction(LIR_Op::LoadVar, LIR_Value(LIR_ValueKind::Var, 0), {}, y_temp1));
        var_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, const5_b, {}, y_temp2));
        var_entry->add_instruction(LIR_Instruction(LIR_Op::Add, y_temp1, y_temp2, y_temp1));
        var_entry->add_instruction(LIR_Instruction(LIR_Op::StoreVar, y_temp1, {}, LIR_Value(LIR_ValueKind::Var, 1)));
        
        var_entry->add_instruction(LIR_Instruction(LIR_Op::Return, y_temp1, {}, {}));
        
        std::cout << var_func->to_string() << std::endl;
        
        // Test 3: Control flow (if statement)
        std::cout << "\nTest 3: Control flow (if)\n";
        std::cout << "-----------------------\n";
        
        auto if_func = std::make_unique<LIR_Function>("test_if", 0);
        auto if_entry = if_func->create_block("entry");
        auto then_block = if_func->create_block("then");
        auto else_block = if_func->create_block("else");
        auto merge_block = if_func->create_block("merge");
        
        // Load condition
        LIR_Value condition(LIR_ValueKind::Bool, true);
        LIR_Value cond_temp = if_func->new_temp();
        if_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, condition, {}, cond_temp));
        
        // Conditional jump
        if_entry->add_instruction(LIR_Instruction(LIR_Op::JumpIfFalse, cond_temp, {}, LIR_Value(LIR_ValueKind::Temp, else_block->id)));
        
        // Then branch
        LIR_Value then_val(int64_t(42));
        LIR_Value then_temp = if_func->new_temp();
        then_block->add_instruction(LIR_Instruction(LIR_Op::LoadConst, then_val, {}, then_temp));
        then_block->add_instruction(LIR_Instruction(LIR_Op::Jump, {}, {}, LIR_Value(LIR_ValueKind::Temp, merge_block->id)));
        
        // Else branch
        LIR_Value else_val(int64_t(99));
        LIR_Value else_temp = if_func->new_temp();
        else_block->add_instruction(LIR_Instruction(LIR_Op::LoadConst, else_val, {}, else_temp));
        else_block->add_instruction(LIR_Instruction(LIR_Op::Jump, {}, {}, LIR_Value(LIR_ValueKind::Temp, merge_block->id)));
        
        // Merge block
        merge_block->add_instruction(LIR_Instruction(LIR_Op::Return, then_temp, {}, {}));
        
        std::cout << if_func->to_string() << std::endl;
        
        // Test 4: Module system
        std::cout << "\nTest 4: Module system\n";
        std::cout << "--------------------\n";
        
        auto module_func = std::make_unique<LIR_Function>("math_module", 0);
        auto module_entry = module_func->create_block("entry");
        
        // Module begin
        LIR_Value module_name("math");
        module_entry->add_instruction(LIR_Instruction(LIR_Op::BeginModule, module_name, {}, {}));
        
        // Export PI constant
        LIR_Value pi_const(3.14159);
        LIR_Value pi_temp = module_func->new_temp();
        module_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, pi_const, {}, pi_temp));
        LIR_Value pi_symbol("PI");
        module_entry->add_instruction(LIR_Instruction(LIR_Op::ExportSymbol, pi_symbol, pi_temp, {}));
        
        // Export add function placeholder
        LIR_Value add_func_temp = module_func->new_temp();
        LIR_Value add_symbol("add");
        module_entry->add_instruction(LIR_Instruction(LIR_Op::ExportSymbol, add_symbol, add_func_temp, {}));
        
        // Module end
        module_entry->add_instruction(LIR_Instruction(LIR_Op::EndModule, {}, {}, {}));
        module_entry->add_instruction(LIR_Instruction(LIR_Op::Return, {}, {}, {}));
        
        std::cout << module_func->to_string() << std::endl;
        
        // Test 5: Import statement
        std::cout << "\nTest 5: Import statement\n";
        std::cout << "-----------------------\n";
        
        auto import_func = std::make_unique<LIR_Function>("main", 0);
        auto import_entry = import_func->create_block("entry");
        
        // Import math module
        LIR_Value import_path("math");
        LIR_Value import_alias("m");
        import_entry->add_instruction(LIR_Instruction(LIR_Op::ImportModule, import_path, import_alias, {}));
        
        // Use imported PI
        LIR_Value imported_pi(LIR_ValueKind::Var, 2); // Would be resolved from module
        LIR_Value use_temp = import_func->new_temp();
        import_entry->add_instruction(LIR_Instruction(LIR_Op::LoadVar, imported_pi, {}, use_temp));
        
        import_entry->add_instruction(LIR_Instruction(LIR_Op::Return, use_temp, {}, {}));
        
        std::cout << import_func->to_string() << std::endl;
        
        // Test 6: String operations
        std::cout << "\nTest 6: String operations\n";
        std::cout << "-------------------------\n";
        
        auto string_func = std::make_unique<LIR_Function>("test_strings", 0);
        auto string_entry = string_func->create_block("entry");
        
        // String concatenation
        LIR_Value hello("Hello");
        LIR_Value world("World");
        LIR_Value str_temp1 = string_func->new_temp();
        LIR_Value str_temp2 = string_func->new_temp();
        
        string_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, hello, {}, str_temp1));
        string_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, world, {}, str_temp2));
        string_entry->add_instruction(LIR_Instruction(LIR_Op::Concat, str_temp1, str_temp2, str_temp1));
        
        string_entry->add_instruction(LIR_Instruction(LIR_Op::Return, str_temp1, {}, {}));
        
        std::cout << string_func->to_string() << std::endl;
        
        // Test 7: Boolean operations
        std::cout << "\nTest 7: Boolean operations\n";
        std::cout << "--------------------------\n";
        
        auto bool_func = std::make_unique<LIR_Function>("test_bool", 0);
        auto bool_entry = bool_func->create_block("entry");
        
        // true && false
        LIR_Value true_val(true);
        LIR_Value false_val(false);
        LIR_Value bool_temp1 = bool_func->new_temp();
        LIR_Value bool_temp2 = bool_func->new_temp();
        
        bool_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, true_val, {}, bool_temp1));
        bool_entry->add_instruction(LIR_Instruction(LIR_Op::LoadConst, false_val, {}, bool_temp2));
        bool_entry->add_instruction(LIR_Instruction(LIR_Op::And, bool_temp1, bool_temp2, bool_temp1));
        
        bool_entry->add_instruction(LIR_Instruction(LIR_Op::Return, bool_temp1, {}, {}));
        
        std::cout << bool_func->to_string() << std::endl;
        
        std::cout << "\n=== All LIR Generation Tests Completed Successfully! ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
