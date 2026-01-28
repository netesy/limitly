# Project Structure

## Directory Organization

```
├── src/
│   ├── frontend/           # Language frontend (lexer/parser)
│   │   ├── scanner.hh/cpp  # Tokenization
│   │   ├── parser.hh/cpp   # AST generation
│   │   └── type_checker.hh/cpp # Type checking and inference
│   ├── backend/            # Language backend (codegen/VM/JIT)
│   │   ├── backend.cpp     # Backend utilities
│   │   ├── register.hh/cpp # Register-based virtual machine
│   │   ├── jit.hh/cpp      # JIT and AOT compilation
│   │   ├── memory.hh       # Memory management
│   │   ├── types.hh        # Type system definitions
│   │   ├── value.hh        # Runtime value representations
│   │   ├── fiber.hh        # Fiber/task management
│   │   └── jit/            # JIT compilation internals
│   ├── lir/                # Low-level intermediate representation
│   │   ├── lir.hh          # LIR instruction definitions
│   │   └── generator.cpp   # LIR code generation
│   ├── common/             # Shared utilities
│   │   ├── ast.hh          # Abstract Syntax Tree definitions
│   │   ├── opcodes.hh      # Bytecode operation codes (legacy)
│   │   └── debugger.hh/cpp # Error reporting and debugging
│   ├── main.cpp            # Main interpreter entry point
│   └── test_parser.cpp     # Parser testing utility
├── tests/                  # Comprehensive test suite
│   ├── basic/              # Basic language features
│   ├── expressions/        # Expression evaluation
│   ├── strings/            # String operations
│   ├── loops/              # Loop constructs
│   ├── functions/          # Function features
│   ├── classes/            # OOP features
│   ├── concurrency/        # Parallel/concurrent blocks
│   ├── types/              # Type system
│   ├── modules/            # Module system
│   ├── error_handling/     # Error handling
│   └── integration/        # Integration tests
├── docs/                   # Documentation
│   ├── guide.md            # Language guide
│   ├── zen.md              # Language philosophy
│   └── limit_vs_python.md  # Language comparison
├── .kiro/steering/         # Kiro IDE steering documents
│   ├── product.md          # Product status and features
│   ├── workflow.md         # Development workflow
│   ├── vm_implementation.md # VM implementation guide
│   ├── testing.md          # Testing strategy
│   ├── tech.md             # Technology stack
│   ├── structure.md        # Project structure (this file)
│   └── language_design.md  # Language design principles
├── build/                  # Build artifacts (generated)
├── bin/                    # Compiled executables (generated)
├── Makefile                # Build configuration
└── CMakeLists.txt          # CMake configuration
```

## Core Files

### Language Definition
- `src/common/ast.hh` - Abstract Syntax Tree definitions
- `src/lir/lir.hh` - LIR instruction definitions (current)
- `src/backend/types.hh` - Type system definitions
- `src/backend/value.hh` - Runtime value representations
- `src/backend/memory.hh` - Memory management utilities

### Frontend Components
- `src/frontend/scanner.hh/cpp` - Lexical analysis
- `src/frontend/parser.hh/cpp` - Syntax analysis and AST generation
- `src/frontend/type_checker.hh/cpp` - Type checking and inference

### Backend Components
- `src/lir/generator.cpp` - LIR code generation from AST
- `src/backend/backend.cpp` - Backend utilities
- `src/backend/register.hh/cpp` - Register-based virtual machine
- `src/backend/jit.hh/cpp` - JIT and AOT compilation
- `src/backend/fiber.hh` - Fiber/task management for concurrency

### Executables
- `src/main.cpp` - Main interpreter entry point
- `src/test_parser.cpp` - Parser testing utility

### Build Configuration
- `Makefile` - Primary build system (use `make`)
- `CMakeLists.txt` - CMake configuration (alternative)

### Documentation
- `README.md` - Project overview and usage
- `activities.md` - Development roadmap and status
- `docs/guide.md` - Comprehensive language guide
- `docs/zen.md` - Language philosophy and design
- `docs/limit_vs_python.md` - Language comparison

## Naming Conventions

### Files
- Headers: `.hh` extension
- Implementation: `.cpp` extension
- Language files: `.lm` extension
- Test files: `test_*.lm` or in `tests/` directory

### Code Organization
- Namespaces: `AST::`, `frontend::`, `backend::`, `LIR::`
- Classes: PascalCase (`Scanner`, `Parser`, `VM`, `Generator`)
- Functions: camelCase (`scanTokens`, `parseExpression`, `emit_expr`)
- Constants: UPPER_SNAKE_CASE (`TOKEN_EOF`, `MAX_STACK_SIZE`)
- Enums: PascalCase for enum class names, UPPER_SNAKE_CASE for values

## Architecture Patterns

### Compilation Pipeline
1. **Scanner** (src/frontend/scanner.cpp) → Tokens
2. **Parser** (src/frontend/parser.cpp) → AST
3. **Type Checker** (src/frontend/type_checker.cpp) → Typed AST
4. **LIR Generator** (src/lir/generator.cpp) → LIR Instructions
5. **Register VM** (src/backend/register.cpp) → Interpretation
6. **JIT/AOT Compiler** (src/backend/jit.cpp) → Native Code (optional)

### Memory Management
- RAII principles throughout
- Smart pointers for AST nodes (`std::shared_ptr`, `std::unique_ptr`)
- Register-based VM with stack frames
- Region-based memory allocation for objects

### Type System
- Static typing with type inference
- Type aliases, union types, Option types
- Compile-time type checking
- Runtime type information for dispatch

### Concurrency Model
- Fiber-based task management
- Channel-based communication
- Parallel blocks with `iter` statements
- Concurrent blocks with `task` statements
