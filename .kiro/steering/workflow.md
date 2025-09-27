# Development Workflow

## Development Phases

### Current Focus
The project is currently in Phase 2 (Backend Development) with major achievements:
- ✅ **Complete control flow support**: if/else, while, for, nested structures working
- ✅ **Basic function calls**: Function declarations, calls, returns, and recursion working
- ✅ **Optional/default parameters**: Functions with optional and default parameters implemented
- ✅ **Comprehensive test suite**: 25+ test files across 8 categories with automated runners
- ✅ **Advanced type system**: Type aliases, union types, Option types implemented
- ✅ **Error handling framework**: Compile-time error checking with ? operator syntax
- ✅ **Module system**: Basic import/export with aliasing and filtering

**Current priorities**:
- Completing object-oriented features (classes, inheritance, method dispatch)
- Implementing closures and higher-order functions
- Completing error handling VM implementation (?else{}, error propagation)
- Implementing concurrency primitives (parallel/concurrent blocks)
- Adding advanced type features (generics, structural types)

### Next Steps
- Complete Phase 2 (Backend Development)
- Begin Phase 3 (Language Features) - generics, modules, standard library
- Start work on Phase 4 (Tooling and Documentation) - IDE integration, debugger

## Feature Implementation Process

1. **Design**
   - Define language feature syntax
   - Update AST structure if needed
   - Define bytecode operations

2. **Frontend Implementation**
   - Add token types to scanner
   - Add parsing rules to parser
   - Create AST nodes

3. **Backend Implementation**
   - Add bytecode generation for new AST nodes
   - Implement VM operations for new bytecode
   - Add runtime support in VM

4. **Testing**
   - Create test cases in sample.lm
   - Verify AST generation
   - Verify bytecode generation
   - Test execution in VM

5. **Documentation**
   - Update README.md with new features
   - Document language syntax and semantics
   - Add examples to sample.lm

## Testing Strategy

### Comprehensive Test Suite
The project now has a comprehensive test suite organized in `tests/` directory:
- **10 test categories**: basic, expressions, strings, loops, functions, classes, concurrency, modules, types, error_handling, integration
- **25+ test files**: Covering all implemented and partially implemented language features
- **Automated test runners**: Both silent and verbose modes available
- **Specialized test runners**: Module error tests, common error validation tests

### Test Execution
```bash
# Run all tests (silent mode)
./tests/run_tests.bat

# Run all tests (verbose mode)  
./tests/run_tests_verbose.bat

# Run specific test category
./bin/limitly.exe tests/loops/for_loops.lm
```

### Parser Testing
Use `test_parser` to verify AST generation:
```bash
./test_parser sample.lm
```

### Bytecode Testing
Use `-bytecode` flag to verify bytecode generation:
```bash
./limitly -bytecode sample.lm
```

### VM Testing
Execute sample programs and verify output:
```bash
./limitly sample.lm
```

### Recent Test Improvements
- ✅ All control flow tests pass (if/else, while, for loops)
- ✅ All iterator tests pass (including nested iterations)
- ✅ String interpolation tests pass (all patterns)
- ✅ Expression and arithmetic tests pass
- ✅ Function tests pass (basic calls, recursion, optional/default parameters)
- ✅ Type system tests pass (type aliases, union types, Option types)
- ✅ Module system tests pass (import/export, aliasing, filtering)
- ✅ Error handling syntax tests pass (compile-time validation)
- ✅ Clean program termination without spurious output

## Contribution Guidelines

### Code Style
- Follow C++17 best practices
- Use smart pointers for memory management
- Document public APIs with comments
- Use consistent indentation (4 spaces)

### Pull Request Process
1. Create feature branch
2. Implement changes
3. Add tests
4. Update documentation
5. Submit PR with description of changes

### Commit Message Format
```
[component]: Brief description

Detailed description of changes and rationale.
```

Example:
```
[vm]: Implement function calls

- Add CALL and RETURN opcodes
- Implement call frame management
- Add support for function arguments
```