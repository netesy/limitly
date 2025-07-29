# Testing and Debugging Guide

## Comprehensive Test Suite ✅

### Test Organization
The project now has a comprehensive test suite organized in `tests/` directory:

```
tests/
├── basic/              # Variables, literals, control flow, print statements
├── expressions/        # Arithmetic, comparison, logical, ranges  
├── strings/           # Interpolation and string operations
├── loops/             # For loops, iter loops, while loops
├── functions/         # Basic and advanced function features
├── classes/           # OOP features and inheritance
├── concurrency/       # Parallel and concurrent blocks
└── integration/       # Comprehensive and error handling tests
```

### Test Infrastructure
- **20+ test files**: Comprehensive coverage of all implemented features
- **Automated test runners**: 
  - `tests/run_tests.bat` - Silent mode with pass/fail reporting
  - `tests/run_tests_verbose.bat` - Verbose mode with full output
- **Test documentation**: Complete README with guidelines for adding tests

### Testing Approach

#### Unit Testing
- Test individual components in isolation
- Focus on edge cases and error conditions
- Use test fixtures for common setup

#### Integration Testing
- Test interaction between components
- Verify correct data flow through the system
- Test end-to-end functionality

#### Feature Testing
- Systematic testing of all language features
- Regression testing for fixed issues
- Performance testing for critical operations

### Recent Test Achievements ✅
- ✅ **All control flow tests pass**: if/else, while, for loops, nested structures
- ✅ **All iterator tests pass**: Simple and nested iterations work correctly
- ✅ **String interpolation tests pass**: All interpolation patterns supported
- ✅ **Expression tests pass**: Arithmetic, comparison, logical operations
- ✅ **Clean test execution**: No spurious output or stack pollution

## Testing Tools

### Parser Testing
- `test_parser` executable for testing the parser
- Verify AST structure matches expected output
- Test error handling and recovery

### VM Testing
- Test bytecode generation and execution
- Verify correct execution of language features
- Test memory management and garbage collection

### Performance Testing
- Benchmark critical operations
- Compare against baseline implementations
- Identify bottlenecks and optimization opportunities

## Debugging Techniques

### AST Visualization
- Print AST structure for debugging
- Verify correct parsing of language constructs
- Identify issues in the parser

### Bytecode Disassembly
- Print bytecode instructions for debugging
- Verify correct code generation
- Identify issues in the backend

### VM Tracing
- Step-by-step execution of bytecode
- Inspect stack and environment state
- Track memory allocations and deallocations

## Error Handling

### Compile-Time Errors
- Syntax errors from the parser
- Type errors from the type checker
- Semantic errors from the analyzer

### Runtime Errors
- Division by zero
- Null reference
- Out of bounds access
- Stack overflow
- Memory allocation failure

### Error Reporting
- Clear error messages with context
- Line and column information
- Suggestions for fixing errors

## Debugging Tools

### Memory Analyzer
- Track memory allocations and deallocations
- Detect memory leaks
- Verify correct garbage collection

### Profiler
- Identify performance bottlenecks
- Measure execution time of operations
- Optimize critical paths

### Debugger Integration
- Set breakpoints in source code
- Inspect variables and stack frames
- Step through execution

## Test Cases

### Currently Tested Features ✅
- ✅ **Variable declarations and assignments**: All types and scoping
- ✅ **Control flow statements**: if/else, while, for loops, nested structures
- ✅ **Expressions and operators**: Arithmetic, comparison, logical, ranges
- ✅ **String operations**: Interpolation, concatenation, all patterns
- ✅ **Iterator loops**: Range-based iteration, nested iterations
- ✅ **Print statements**: Clean output without side effects
- ✅ **Basic literals**: Numbers, strings, booleans

### Planned Test Coverage
- [ ] Function declarations and calls
- [ ] Classes and objects
- [ ] Error handling (try/catch)
- [ ] Concurrency primitives
- [ ] Advanced type features

### Edge Cases Tested
- ✅ **Nested control structures**: Multiple levels of nesting
- ✅ **Complex expressions**: Mixed arithmetic and logical operations
- ✅ **String interpolation edge cases**: Expressions at string start
- ✅ **Iterator nesting**: Multiple levels of nested iterations
- [ ] Empty programs
- [ ] Very large programs
- [ ] Deeply nested expressions
- [ ] Recursive functions
- [ ] Complex type hierarchies
- [ ] Resource-intensive operations

### Test Quality Metrics
- **Test Coverage**: 20+ test files covering all implemented features
- **Pass Rate**: 100% for all implemented features
- **Regression Testing**: All previously fixed issues remain resolved
- **Clean Execution**: No memory leaks or spurious output