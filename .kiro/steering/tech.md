# Technology Stack

## Core Technologies
- **Language**: C++17
- **Build System**: Make (primary), CMake (alternative)
- **Architecture**: Compiler frontend + LIR + Register-based VM backend
- **Memory Model**: RAII with smart pointers, region-based allocation

## Build System Usage

### Primary Build Method
**Use `make` for all builds** (works on Windows with MSYS2/MinGW64)
```bash
make
```

### Build Outputs
- `bin/limitly.exe` - Main language interpreter
- `bin/test_parser.exe` - Parser testing utility

### Alternative: CMake
```bash
mkdir build && cd build
cmake ..
make
```

### Build Flags
```bash
make clean          # Clean build artifacts
make rebuild        # Clean and rebuild
make run_limitly    # Build and run interpreter
make run_test_parser # Build and run parser tests
```

## Common Commands

### Running the Language
```bash
# Execute source file (default: register VM)
./bin/limitly.exe sample.lm

# Execute with register VM (explicit)
./bin/limitly.exe --vm sample.lm

# Compile with JIT (compile hot paths at runtime)
./bin/limitly.exe --jit sample.lm

# Compile with AOT (compile entire program before execution)
./bin/limitly.exe --aot sample.lm

# Compile to native executable (AOT)
./bin/limitly.exe --aot -o sample.exe sample.lm

# Print AST
./bin/limitly.exe -ast sample.lm

# Print tokens
./bin/limitly.exe -tokens sample.lm

# Print LIR (Low-level Intermediate Representation)
./bin/limitly.exe -bytecode sample.lm

# Start REPL
./bin/limitly.exe -repl
```

### Development Commands
```bash
# Test parser
./bin/test_parser.exe sample.lm

# Run test suite
./tests/run_tests.bat              # Silent mode
./tests/run_tests_verbose.bat      # Verbose mode

# Run specific test category
./bin/limitly.exe tests/loops/for_loops.lm
```

## Compilation Pipeline

### Frontend
1. **Scanner** (`src/frontend/scanner.cpp`)
   - Tokenizes source code
   - Handles keywords, identifiers, literals, operators
   - Produces token stream

2. **Parser** (`src/frontend/parser.cpp`)
   - Builds Abstract Syntax Tree (AST) from tokens
   - Implements recursive descent parsing
   - Handles operator precedence and associativity

3. **Type Checker** (`src/frontend/type_checker.cpp`)
   - Type inference and checking
   - Validates type compatibility
   - Produces typed AST

### Backend - Multiple Execution Modes

#### Mode 1: Register VM (Interpretation)
- **Component**: `src/backend/register.cpp`
- **Purpose**: Direct interpretation of LIR
- **Use Case**: Development, debugging, quick execution
- **Performance**: Moderate (no compilation overhead)
- **Startup**: Fast (immediate execution)

#### Mode 2: JIT Compilation (Just-In-Time)
- **Component**: `src/backend/jit.cpp`
- **Purpose**: Compile hot code paths to native code at runtime
- **Use Case**: Long-running applications, performance-critical code
- **Performance**: High (after warmup)
- **Startup**: Slower (compilation during execution)

#### Mode 3: AOT Compilation (Ahead-Of-Time)
- **Component**: `src/backend/jit.cpp`
- **Purpose**: Compile entire program to native code before execution
- **Use Case**: Production deployments, performance-critical applications
- **Performance**: High (no runtime compilation)
- **Startup**: Slower (pre-compilation required)

### LIR Generation
1. **LIR Generator** (`src/lir/generator.cpp`)
   - Converts typed AST to Low-level Intermediate Representation
   - Performs register allocation
   - Generates LIR instructions
   - Produces intermediate code for both VM and JIT

### Execution Flow
```
Source Code
    ↓
Scanner → Tokens
    ↓
Parser → AST
    ↓
Type Checker → Typed AST
    ↓
LIR Generator → LIR Instructions
    ↓
    ├─→ Register VM (interpret)
    ├─→ JIT Compiler (compile hot paths)
    └─→ AOT Compiler (compile all code)
    ↓
Execution
```

## Code Standards

### C++ Standards
- C++17 standard compliance
- Use modern C++ features (smart pointers, auto, range-based for)
- Avoid C-style casts, use C++ casts

### Code Style
- Header guards for all `.hh` files
- Namespace organization (`AST::`, `frontend::`, `backend::`, `LIR::`)
- RAII for resource management
- Smart pointers (`std::shared_ptr`, `std::unique_ptr`)
- STL containers and algorithms

### Naming Conventions
- Classes: PascalCase (`Scanner`, `Parser`, `VM`)
- Functions: camelCase (`scanTokens`, `parseExpression`)
- Constants: UPPER_SNAKE_CASE (`TOKEN_EOF`, `MAX_STACK_SIZE`)
- Member variables: snake_case with trailing underscore (`member_var_`)
- Enums: PascalCase for enum class, UPPER_SNAKE_CASE for values

### Documentation
- Document public APIs with comments
- Use consistent indentation (4 spaces)
- Include examples in complex function documentation
- Update steering docs when changing architecture

## Compiler Flags

### Optimization
- `-O3` for release builds (default)
- `-O0` for debug builds (use `-g` flag)

### Warnings
- `-Wall -Wextra` for comprehensive warnings
- `-Wno-unused-parameter` to suppress unused parameter warnings
- `-Wno-unused-variable` to suppress unused variable warnings

### Linking
- `-static-libgcc -static-libstdc++` for static linking
- `-lws2_32` for Windows socket support
- `-lgccjit` for JIT compilation support (future)

## Development Workflow

### Making Changes
1. Edit source files in `src/`
2. Run `make` to build
3. Test with `./bin/limitly.exe test_file.lm`
4. Run test suite: `./tests/run_tests.bat`
5. Update documentation if needed

### Adding New Features
1. Update scanner/parser if syntax changes
2. Update AST definitions in `src/common/ast.hh`
3. Update type checker if type rules change
4. Update LIR generator for code generation
5. Update VM if new operations needed
6. Add tests in `tests/` directory
7. Update steering docs

### Debugging
- Use `-ast` flag to inspect AST
- Use `-bytecode` flag to inspect LIR
- Add debug prints in VM execution
- Use debugger with breakpoints (gdb/lldb)

## Performance Considerations

### Register Allocation
- Efficient register allocation in LIR generator
- Minimize register spills
- Track register types for optimization

### Memory Management
- Region-based allocation for objects
- Smart pointers to prevent memory leaks
- Garbage collection for circular references

### Optimization Opportunities
- Constant folding in LIR generation
- Dead code elimination
- Instruction combining
- Inline caching for method dispatch

## Known Issues and Workarounds

### Nested While Loops
- **Issue**: Infinite loop with nested while loops
- **Workaround**: Use sequential loops or refactor into functions
- **Status**: VM bug in jump instruction handling

### Nested List Iteration
- **Issue**: Cannot iterate over lists of lists
- **Workaround**: Use direct indexing instead
- **Status**: Type system limitation

### String Keys in Nested Dicts
- **Issue**: Nested dictionary access with string keys needs type tracking
- **Workaround**: Use numeric keys or direct indexing
- **Status**: Type inference limitation

## Future Improvements

### Short Term
- Fix nested while loop bug
- Implement nested list iteration
- Improve type tracking for nested collections
- Add more optimization passes

### Medium Term
- JIT compilation support
- Better error messages with suggestions
- Performance profiling tools
- Memory usage analysis

### Long Term
- Language server protocol (LSP) support
- IDE integration
- Package manager
- Standard library expansion
