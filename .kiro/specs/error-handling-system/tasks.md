# Implementation Plan

- [x] 1. Extend AST with error handling nodes








  - Add FallibleExpr, ErrorConstructExpr, and OkConstructExpr to frontend/ast.hh
  - Extend TypeAnnotation struct to support error type annotations (isFallible, errorTypes fields)
  - Create unit tests for new AST node construction and validation
  - _Requirements: 1.1, 1.2, 2.1, 2.2_

- [x] 2. Add error union types to type system







  - Extend backend/types.hh with ErrorUnionType struct and integration into Type::extra variant
  - Add error type constants and registry to TypeSystem class
  - Implement error union type compatibility checking in canConvert method
  - Write unit tests for error union type creation and compatibility
  - _Requirements: 1.1, 1.3, 5.2, 5.4_

- [x] 3. Extend scanner and parser for error syntax





  - Add QUESTION token type to frontend/scanner.hh for ? operator
  - Add ERR and OK keywords to scanner for error/success construction
  - Extend parser to handle Type?ErrorList syntax in function return types
  - Parse fallible expressions with ? operator and optional else handlers
  - Parse err() and ok() constructor expressions
  - _Requirements: 1.2, 1.3, 2.1, 2.2, 3.1_

- [ ] 4. Implement error value representation in VM
  - Add ErrorValue struct to backend/value.hh with error type, message, and arguments
  - Extend Value variant to include ErrorValue and error union representations
  - Add ErrorUnion helper class for efficient tagged union operations
  - Create error value construction and inspection methods
  - Write unit tests for error value creation and manipulation
  - _Requirements: 2.1, 2.2, 7.1, 7.2_

- [ ] 5. Add error handling bytecode operations
  - Extend opcodes.hh with CHECK_ERROR, PROPAGATE_ERROR, CONSTRUCT_ERROR, CONSTRUCT_OK opcodes
  - Add IS_ERROR, IS_SUCCESS, UNWRAP_VALUE opcodes for error union operations
  - Implement bytecode generation for fallible expressions in backend/backend.cpp
  - Generate bytecode for error construction (err/ok) expressions
  - _Requirements: 3.1, 3.2, 7.5_

- [ ] 6. Implement VM error handling runtime
  - Add error propagation logic to backend/vm.cpp for new error opcodes
  - Implement stack-based error frame management for efficient propagation
  - Add error checking and unwrapping operations in VM execution loop
  - Create error construction and success value wrapping operations
  - Write integration tests for VM error handling execution
  - _Requirements: 3.1, 3.2, 3.4, 7.1, 7.2_

- [ ] 7. Add compile-time error type checking
  - Extend type checker to validate error union compatibility in function calls
  - Implement unhandled fallible expression detection (require ? or match)
  - Add error type propagation validation in function signatures
  - Generate compile-time errors for incompatible error types
  - Write tests for compile-time error detection and validation
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_

- [ ] 8. Implement built-in error types
  - Add standard error types (DivisionByZero, IndexOutOfBounds, etc.) to type system
  - Modify arithmetic operations to return error unions for division by zero
  - Update array/dict indexing to return error unions for bounds violations
  - Add error handling to type conversion operations
  - Create comprehensive tests for built-in error scenarios
  - _Requirements: 6.1, 6.2, 6.3, 6.4, 6.5_

- [ ] 9. Extend pattern matching for error handling
  - Add val/err pattern support to existing match statement parsing
  - Extend MatchCase AST nodes to handle error pattern matching
  - Generate bytecode for error pattern matching in match expressions
  - Implement VM support for error pattern matching execution
  - Add exhaustive matching validation for error union types
  - Write tests for comprehensive error pattern matching scenarios
  - _Requirements: 4.1, 4.2, 4.3, 4.4, 4.5_

- [ ] 10. Add function signature error type validation
  - Extend FunctionDeclaration AST to include error type annotations
  - Validate that function bodies can produce declared error types
  - Check error type compatibility between caller and callee functions
  - Implement error type inference for functions using ? operator
  - Create tests for function signature error type validation
  - _Requirements: 1.4, 5.1, 5.2, 5.3_

- [ ] 11. Implement error propagation optimization
  - Add zero-cost success path optimization in VM execution
  - Implement efficient error frame stack management
  - Add error value pooling to reduce memory allocations
  - Optimize error union type layout for cache efficiency
  - Write performance tests to validate zero-cost abstractions
  - _Requirements: 7.1, 7.2, 7.3, 7.4, 7.5_

- [ ] 12. Create comprehensive error handling test suite
  - Write end-to-end tests for complete error propagation flows
  - Test nested error propagation through multiple function calls
  - Create tests for error handling with existing language features (loops, classes)
  - Add performance benchmarks comparing error vs success path execution
  - Test error handling integration with concurrency features
  - _Requirements: All requirements - comprehensive validation_