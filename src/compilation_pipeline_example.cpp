// =============================================================================
// SIMPLIFIED COMPILATION PIPELINE: AST -> LIR -> JIT
// =============================================================================
// This demonstrates the simplified three-layer approach where:
// 1. AST carries inferred types (LanguageType*)
// 2. LIR uses ABI-level types directly (Type enum)
// 3. JIT consumes the same ABI types from LIR

#include "frontend/ast.hh"
#include "frontend/type_checker.hh"
#include "lir/generator.hh"

namespace CompilationPipeline {

// Simplified compilation pipeline
struct SimplePipeline {
    TypeSystem type_system;
    
    bool compile_program(std::shared_ptr<AST::Program> program) {
        // Initialize type system
        type_system.initialize_builtin_types();
        
        // Step 1: Type checking (AST -> AST with inferred types)
        auto type_check_result = TypeCheckerFactory::check_program(program);
        if (!type_check_result.success) {
            return false;
        }
        
        // Step 2: LIR generation (AST with types -> LIR with ABI types)
        LIR::Generator generator;
        auto lir_function = generator.generate_program(type_check_result);
        if (!lir_function) {
            return false;
        }
        
        // Step 3: JIT compilation (LIR with ABI types -> Machine code)
        // JIT can directly use the ABI types from LIR - no conversion needed!
        bool jit_success = compile_to_machine_code(*lir_function);
        
        return jit_success;
    }
    
private:
    bool compile_to_machine_code(const LIR::LIR_Function& lir_function) {
        // JIT compilation - directly uses ABI types from LIR
        for (const auto& inst : lir_function.instructions) {
            // Each instruction already has the correct ABI type in inst.result_type
            // No type conversion needed - JIT can generate machine code directly!
            
            switch (inst.result_type) {
                case LIR::Type::I32:
                    // Generate 32-bit integer machine code
                    break;
                case LIR::Type::I64:
                    // Generate 64-bit integer machine code
                    break;
                case LIR::Type::F64:
                    // Generate floating point machine code
                    break;
                case LIR::Type::Ptr:
                    // Generate pointer machine code
                    break;
                case LIR::Type::Bool:
                    // Generate boolean machine code
                    break;
                case LIR::Type::Void:
                    // No result type
                    break;
            }
        }
        return true;
    }
};

} // namespace CompilationPipeline

/*
## BENEFITS OF SIMPLIFIED APPROACH:

1. **Faster**: No type conversion overhead between LIR and JIT
2. **Simpler**: Single type system for both LIR and JIT
3. **Cleaner**: Less code, easier to understand and maintain
4. **Direct**: AST -> LIR -> JIT with minimal abstraction layers

## TYPE FLOW:
- AST expressions carry `LanguageType* inferred_type`
- Type checker sets `expr->inferred_type` 
- LIR generator converts `LanguageType*` -> `Type` (ABI level)
- JIT uses `Type` directly from LIR instructions

## EXAMPLE:
```cpp
// AST: 5 + 3.14
// Type checker: expr->inferred_type = type_system.get_float_type()
// LIR: Add(Type::F64, dst, reg_int, reg_float)  // ABI type directly
// JIT: Generate floating point add instruction
```

This is much cleaner than the original three-layer type system!
*/
