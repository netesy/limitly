# Project Structure

## Directory Organization

```
├── frontend/           # Language frontend (lexer/parser)
│   ├── scanner.hh/cpp  # Tokenization
│   └── parser.hh/cpp   # AST generation
├── backend/            # Language backend (codegen/VM)
│   ├── backend.cpp     # Bytecode generation
│   ├── vm.hh/cpp       # Virtual machine
│   ├── memory.hh       # Memory management
│   ├── types.hh        # Type system
│   └── value.hh        # Runtime values
├── build/              # Build artifacts (generated)
├── bin/                # Compiled executables (generated)
└── zig-cache/          # Zig build cache (generated)
```

## Core Files

### Language Definition
- `ast.hh` - Abstract Syntax Tree definitions
- `opcodes.hh` - Bytecode instruction set
- `types.hh` - Type system definitions
- `value.hh` - Runtime value representations
- `memory.hh` - Memory management utilities

### Executables
- `main.cpp` - Main interpreter entry point
- `test_parser.cpp` - Parser testing utility
- `debugger.hh/cpp` - Error reporting and debugging

### Build Configuration
- `CMakeLists.txt` - CMake build configuration
- `build.zig` - Zig build configuration
- `build*.bat` - Windows batch build scripts

### Documentation
- `README.md` - Project overview and usage
- `activities.md` - Development roadmap and status
- `sample.lm` - Example Limit language code

## Naming Conventions

### Files
- Headers: `.hh` extension
- Implementation: `.cpp` extension
- Language files: `.lm` extension

### Code Organization
- Namespaces: `AST::`, `frontend::`, `backend::`
- Classes: PascalCase (`Scanner`, `Parser`, `VM`)
- Functions: camelCase (`scanTokens`, `parseExpression`)
- Constants: UPPER_SNAKE_CASE (`TOKEN_EOF`, `MAX_STACK_SIZE`)

## Architecture Patterns

### Frontend Pipeline
1. **Scanner** → Tokens
2. **Parser** → AST
3. **Backend** → Bytecode
4. **VM** → Execution

### Memory Management
- RAII principles throughout
- Smart pointers for AST nodes
- Custom memory managers for VM
- Stack-based execution model