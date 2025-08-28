# Limit Language Test Suite

This directory contains comprehensive tests for the Limit programming language implementation.

## Test Structure

```
tests/
├── basic/              # Basic language features
│   ├── variables.lm    # Variable declarations and assignments
│   ├── literals.lm     # Literal values (int, float, string, bool, null)
│   ├── control_flow.lm # If statements and conditional logic
│   └── print_statements.lm # Print statement functionality
├── expressions/        # Expression evaluation
│   ├── arithmetic.lm   # Arithmetic operations (+, -, *, /, %, unary)
│   ├── comparison.lm   # Comparison operations (==, !=, <, >, <=, >=)
│   ├── logical.lm      # Logical operations (&&, ||, !)
│   └── ranges.lm       # Range expressions (1..5)
├── strings/           # String operations
│   ├── interpolation.lm # String interpolation with {variable}
│   └── operations.lm   # String operations and comparisons
├── loops/             # Loop constructs
│   ├── for_loops.lm    # For loop functionality
│   ├── iter_loops.lm   # Iterator loops with ranges
│   └── while_loops.lm  # While loops (if implemented)
├── functions/         # Function features
│   ├── basic_functions.lm    # Function declarations and calls
│   └── advanced_functions.lm # Optional parameters, closures
├── classes/           # Object-oriented features
│   ├── basic_classes.lm # Class definitions and methods
│   └── inheritance.lm  # Class inheritance and polymorphism
├── concurrency/       # Concurrent programming
│   ├── parallel_blocks.lm   # Parallel execution blocks
│   └── concurrent_blocks.lm # Concurrent execution and async/await
└── integration/       # Integration tests
    ├── comprehensive.lm # Multi-feature integration test
    └── error_handling.lm # Error handling and exceptions
```

## Running Tests

### Quick Test Run
```bash
cd tests
run_tests.bat
```

### Verbose Test Run (with output)
```bash
cd tests
run_tests_verbose.bat
```

### Individual Test
```bash
cd tests
..\bin\limitly.exe basic\variables.lm
```

## Test Categories

### ✅ Currently Implemented Features
- **Variables**: Declaration, assignment, scoping
- **Literals**: Integers, floats, strings, booleans, null
- **Arithmetic**: +, -, *, /, %, unary operators
- **Comparison**: ==, !=, <, >, <=, >=
- **Logical**: and, or, !
- **Control Flow**: if/else statements
- **Loops**: for loops, iter loops with ranges, while loop, match
- **Patterns**: Pattern matching and destructuring
- **String Interpolation**: {variable} syntax
- **Print Statements**: Output functionality
- **Ranges**: 1..5 syntax for iteration
- **Concurrency**: Parallel/concurrent blocks
- **Functions**: Function

### 🚧 Partially Implemented Features
- **Classes**: Framework exists, needs implementation
- **Error Handling**: Basic error reporting

### ❌ Not Yet Implemented Features
- **Arrays/Lists**: Collection types
- **Advanced Functions**: Closures, higher-order functions
- **Exception Handling**: try/catch/finally blocks
- **Inheritance**: Class inheritance and polymorphism
- **Modules**: Import/export statements
- **Generics**: Generic types and type constraints

- **Async/Await**: Async/await syntax and implementation
- **Generators**: Yield statements and generators
- **Reflection**: Runtime type introspection
- **Traits**: Trait implementation and composition
- **Macros**: Macro system and implementation
- **Meta Programming**: Runtime code generation and reflection
- **Reflection**: Runtime type introspection
- **Traits**: Trait implementation and composition
- **Macros**: Macro system and implementation
- **Meta Programming**: Runtime code generation and reflection

## Test Results Interpretation

- **PASS**: Test executed without errors
- **FAIL**: Test encountered syntax errors or runtime errors
- **SKIP**: Test contains unimplemented features (commented out)

## Adding New Tests

1. Create a new `.lm` file in the appropriate category directory
2. Add comprehensive test cases for the feature
3. Update this README with the new test
4. Add the test to the appropriate test runner script

## Test Guidelines

- Each test file should be self-contained
- Use descriptive print statements to show test progress
- Test both positive and negative cases
- Include edge cases and boundary conditions
- Comment out tests for unimplemented features with TODO notes