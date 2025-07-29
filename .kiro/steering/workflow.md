# Development Workflow

## Development Phases

### Current Focus
The project is currently in Phase 2 (Backend Development) with recent major achievements:
- ✅ **Fixed critical control flow issues**: All jump offset calculations corrected
- ✅ **Complete control flow support**: if/else, while, for, nested structures working
- ✅ **Fixed iterator stack management**: Clean execution without spurious output
- ✅ **Comprehensive test suite**: 20+ test files with automated runners

**Current priorities**:
- Completing VM implementation for complex operations
- Implementing function calls and returns in the VM
- Implementing object-oriented features in the VM
- Adding break/continue statements for loops
- Implementing exception handling (try/catch blocks)

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
- **8 test categories**: basic, expressions, strings, loops, functions, classes, concurrency, integration
- **20+ test files**: Covering all implemented language features
- **Automated test runners**: Both silent and verbose modes available

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