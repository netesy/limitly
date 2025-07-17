# Development Workflow

## Development Phases

### Current Focus
The project is currently in Phase 2 (Backend Development) with focus on:
- Completing VM implementation for complex operations
- Implementing function calls and returns in the VM
- Implementing object-oriented features in the VM
- Implementing concurrency primitives in the VM

### Next Steps
- Complete Phase 2 (Backend Development)
- Begin Phase 3 (Language Features)
- Start work on Phase 4 (Tooling and Documentation)

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