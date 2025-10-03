# Implementation Plan

- [x] 1. Extend Value system with closure support ⚠️ PARTIAL
  - ✅ Add ClosureValue struct to value.hh with function reference and captured environment
  - ✅ Update Value variant to include ClosureValue type
  - ✅ Implement ClosureValue constructor and execution methods
  - ✅ Create a proper function Object in functions.cpp that we can use in the backend.cpp and vm.cpp   
  - ✅ Add TypeTag::Closure to type system
  - ❌ Lambda function registration timing issues prevent proper closure creation
  - _Requirements: 1.1, 1.2, 1.3_

- [x] 2. Add closure opcodes to VM instruction set






  - Add suport for lambda, closure and higher order functions to the parser using our syntax : for types not ->
  - Add CREATE_CLOSURE, CAPTURE_VAR, PUSH_LAMBDA, CALL_CLOSURE opcodes to opcodes.hh
  - Add PUSH_FUNCTION_REF and CALL_HIGHER_ORDER opcodes for higher-order functions
  - Update Instruction struct to handle closure-specific data
  - _Requirements: 1.1, 2.1, 3.1_

- [x] 3. Implement lambda expression AST support ✅ WORKING
  - ✅ Add LambdaExpr struct to ast.hh with parameters, body, and captured variables
  - ✅ Update Expression variant to include LambdaExpr
  - ✅ Add lambda parsing support to parser for syntax like `fn(x, y) {x + y}`
  - ✅ Implement lambda tokenization in scanner for lambda operators
  - ✅ Lambda expressions parse correctly and generate bytecode
  - _Requirements: 6.1, 6.2, 6.4_

- [x] 4. Enhance Environment class for closure variable capture






  - Add capturedVariables set and closureParent pointer to Environment class
  - Implement createClosureEnvironment method for creating closure scopes
  - Add captureVariable and isVariableCaptured methods
  - Update variable lookup to check captured variables first
  - _Requirements: 1.1, 1.2, 6.5_

- [x] 5. Implement closure creation in bytecode generator ⚠️ PARTIAL
  - ✅ Add visitLambdaExpr method to BytecodeGenerator
  - ✅ Implement variable capture analysis during lambda compilation
  - ✅ Generate CREATE_CLOSURE and CAPTURE_VAR instructions
  - ❌ Bytecode generation order issues prevent proper lambda function registration
  - ❌ PUSH_LAMBDA executes before lambda function is registered in VM
  - ❌ Handle nested lambda expressions with proper scope analysis
  - _Requirements: 1.1, 1.2, 6.2_

- [x] 6. Implement closure execution in VM ⚠️ PARTIAL
  - ✅ Add handleCreateClosure method to VM for CREATE_CLOSURE opcode
  - ✅ Implement handleCaptureVar for CAPTURE_VAR opcode
  - ✅ Add handleCallClosure for CALL_CLOSURE opcode with environment restoration
  - ✅ Update function call mechanism to handle both regular functions and closures
  - ❌ Lambda function lookup fails because functions not registered at execution time
  - ❌ Variable capture fails due to execution order issues
  - _Requirements: 1.1, 1.3, 2.1, 3.1_

- [x] 7. Implement higher-order function support in VM ✅ WORKING
  - ✅ Update handleCall method to accept function values as parameters
  - ✅ Add support for functions as parameters and return values
  - ✅ Function assignment to variables works correctly
  - ✅ Function composition works correctly
  - ❌ Lambda expressions not working (PUSH_LAMBDA fails to find lambda functions)
  - ❌ Closures with variable capture not working (bytecode generation issues)
  - _Requirements: 2.1, 2.2, 2.3, 3.1, 3.2, 3.3_

- [ ] 8. Fix lambda function registration timing for closure support

















  - Implement bytecode pre-processing phase to register all lambda functions before execution
  - Add VM::preProcessBytecode method to scan for BEGIN_FUNCTION/END_FUNCTION pairs
  - Register lambda functions (__lambda_*) in userDefinedFunctions during pre-processing
  - Modify VM::run to call preProcessBytecode before main execution loop
  - Update lambda bytecode generation to ensure proper function registration order
  - Add debug logging for lambda function registration and lookup
  - Create test cases to verify lambda expressions work: `fn(x: int): int { return x * 2; }`
  - Create test cases to verify closures with variable capture work
  - _Requirements: 1.1, 1.2, 1.3, 6.1, 6.2, 6.5_

- [ ] 9. Create builtin functions module structure
  - Create src/common/builtin_functions.cpp file for builtin function implementations
  - Add BuiltinFunctions class with static registration method
  - Implement registerAll method to register builtins with VM at startup
  - Add builtin function type definitions and signatures
  - _Requirements: 5.1, 5.2, 5.4_

- [ ] 10. Implement core collection builtin functions
  - Implement map function that applies transformation to each collection element
  - Implement filter function that returns elements satisfying predicate
  - Implement reduce function that accumulates values using reducer function
  - Implement forEach function that executes function for each element
  - _Requirements: 4.1, 4.2, 4.3, 4.4_

- [ ] 11. Implement search and utility builtin functions
  - Implement find function that returns first element matching predicate
  - Implement some function that returns true if any element satisfies predicate
  - Implement every function that returns true if all elements satisfy predicate
  - Add compose, curry, and partial functions for function composition
  - _Requirements: 4.5, 4.6, 4.7_

- [ ] 12. Integrate builtin functions with VM startup
  - Update VM constructor to call BuiltinFunctions::registerAll
  - Ensure builtin functions are available in global environment
  - Add builtin function performance optimization for native VM operations
  - Implement error handling integration with language error system
  - _Requirements: 5.2, 5.3, 5.5_

- [ ] 13. Implement closure memory management
  - Add closure variable lifetime tracking in memory manager
  - Implement proper cleanup when closures are garbage collected
  - Handle circular reference detection for closures
  - Optimize memory usage for captured variables to avoid duplication
  - _Requirements: 7.1, 7.2, 7.3, 7.4, 7.5_

- [ ] 14. Create comprehensive closure test suite
  - Write tests for basic closure creation and variable capture
  - Test nested closures with multiple capture levels
  - Create tests for closure modification of captured variables
  - Test closure memory cleanup and garbage collection
  - _Requirements: 1.1, 1.2, 1.3, 1.4, 1.5_

- [ ] 15. Create higher-order function test suite
  - Write tests for functions accepting function parameters
  - Test functions returning other functions (function factories)
  - Create tests for function composition and currying
  - Test complex higher-order function scenarios with multiple levels
  - _Requirements: 2.1, 2.2, 2.3, 2.4, 3.1, 3.2, 3.3_

- [ ] 16. Create builtin functions test suite
  - Write comprehensive tests for each builtin function (map, filter, reduce, etc.)
  - Test builtin functions with various collection types and edge cases
  - Create performance tests for builtin function efficiency
  - Test error handling for invalid inputs to builtin functions
  - _Requirements: 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 5.5_

- [ ] 17. Create lambda expression test suite
  - Write tests for lambda syntax parsing and execution
  - Test lambda variable capture with different scope scenarios
  - Create tests for lambda type inference and explicit typing
  - Test lambda expressions as arguments to higher-order functions
  - _Requirements: 6.1, 6.2, 6.3, 6.4, 6.5_

- [ ] 18. Integration testing and optimization
  - Create complex integration tests combining closures, higher-order functions, and builtins
  - Implement performance optimizations based on test results
  - Add comprehensive error handling tests for all closure-related features
  - Verify memory management works correctly under stress testing
  - _Requirements: 7.1, 7.2, 7.3, 7.4, 7.5_
## Current
 Implementation Status

### ✅ WORKING: Higher-Order Functions
- Function parameters: `fn apply(f: function(int): int, x: int): int`
- Function assignment: `var my_func = some_function;`
- Function composition: Functions can call other functions passed as parameters
- Function return values: Functions can return other functions (regular function names)

### ❌ NOT WORKING: Lambda Expressions and Closures
- Lambda expressions: `fn(x: int): int { return x * 2; }` fail with "lambda function not found"
- Closures with variable capture: Lambdas that reference outer scope variables fail
- Nested function definitions: `fn outer() { fn inner() { ... } }` not supported

### Root Cause Analysis
The main issue is with the **bytecode execution order**:

1. **Lambda Registration Timing**: Lambda functions are defined with `BEGIN_FUNCTION`/`END_FUNCTION` opcodes that execute during the parent function's execution, but `PUSH_LAMBDA` tries to find the lambda before it's registered.

2. **Variable Capture Timing**: `CAPTURE_VAR` tries to capture variables during lambda creation, but the lambda's environment context is not properly established.

3. **Bytecode Generation Order**: The current order generates:
   ```
   BEGIN_FUNCTION __lambda_0
   ... lambda body ...
   END_FUNCTION
   PUSH_LAMBDA __lambda_0  // ❌ Fails here - lambda not found
   CAPTURE_VAR x
   CREATE_CLOSURE
   ```

### Recommended Fix
The lambda functions need to be registered during the initial bytecode processing phase, not during execution. This requires either:

1. **Pre-processing approach**: Scan bytecode for all `BEGIN_FUNCTION`/`END_FUNCTION` pairs and register them before execution starts
2. **Deferred execution approach**: Change lambda bytecode generation to defer lambda body generation until after the parent function is processed
3. **Immediate registration approach**: Modify `BEGIN_FUNCTION` handler to immediately register lambda functions even when encountered during execution

### Test Results
```bash
# ✅ Working
./bin/limitly.exe test_simple_higher_order.lm
./bin/limitly.exe test_higher_order_functions.lm

# ❌ Not working  
./bin/limitly.exe test_lambda_closure.lm
./bin/limitly.exe test_simple_lambda.lm
```