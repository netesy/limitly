# Fyra Backend Integration Guide

## Overview

Fyra has been integrated as a subproject in `src/backend/fyra/` to provide advanced AOT (Ahead-of-Time) and WebAssembly compilation capabilities for the Limit language.

## Architecture

### Backend Structure

```
src/backend/
├── fyra/                    # Fyra subproject (git submodule)
│   ├── src/                 # Fyra source code
│   ├── include/             # Fyra headers
│   └── CMakeLists.txt       # Fyra build configuration
├── fyra.hh                  # Fyra integration header
├── fyra.cpp                 # Fyra integration implementation
├── jit/                     # JIT compilation backend
├── vm/                      # Register-based VM
└── ...                      # Other backend components
```

### Compilation Pipeline

```
Source Code (.lm)
    ↓
Scanner → Tokens
    ↓
Parser → AST
    ↓
Type Checker → Typed AST
    ↓
Memory Checker → Verified AST
    ↓
    ├─→ LIR Generator → LIR Instructions
    │   ├─→ Register VM (interpret)
    │   └─→ JIT Compiler (compile hot paths)
    │
    └─→ Fyra IR Generator → Fyra IR (direct from AST)
        ├─→ Fyra AOT (compile to native)
        ├─→ Fyra WASM (compile to WebAssembly)
        └─→ Fyra WASI (compile to WASI)
    ↓
Execution / Output
```

**Key Difference**: Fyra targets (AOT, WASM, WASI) now bypass LIR entirely and generate Fyra IR directly from the verified AST, similar to how LLVM works as an intermediate representation layer.

## Usage

### Command-Line Interface

```bash
# Print Fyra IR (for debugging)
./bin/limitly.exe -fyra-ir program.lm

# AOT compilation with Fyra (native executable)
./bin/limitly.exe -aot program.lm

# WebAssembly compilation
./bin/limitly.exe -wasm program.lm

# WASI compilation (WebAssembly System Interface)
./bin/limitly.exe -wasi program.lm

# JIT compilation (uses LIR)
./bin/limitly.exe -jit program.lm

# Register VM interpretation (uses LIR, default)
./bin/limitly.exe program.lm
```

### Output Files

- **AOT**: `program.exe` (Windows) or `program` (Linux)
- **WASM**: `program.wasm`
- **WASI**: `program.wasi`

## Implementation Details

### Fyra IR Generator

Located in `src/backend/fyra_ir_generator.hh` and `src/backend/fyra_ir_generator.cpp`:

The `FyraIRGenerator` class converts verified AST directly to Fyra IR, bypassing LIR:

```cpp
class FyraIRGenerator {
public:
    // Generate Fyra IR from verified AST
    std::shared_ptr<FyraIRFunction> generate_from_ast(
        const std::shared_ptr<Frontend::AST::Program>& program);
    
    // Generate Fyra IR from a single function
    std::shared_ptr<FyraIRFunction> generate_function(
        const std::shared_ptr<Frontend::AST::FunctionDeclaration>& func_decl);
    
    // Get generated IR as string
    std::string get_ir_string() const;
};
```

### Fyra Compiler Class

Located in `src/backend/fyra.hh` and `src/backend/fyra.cpp`:

```cpp
class FyraCompiler {
public:
    // Compile with options
    CompileResult compile(const LIR::LIRFunction& lir_func,
                         const FyraCompileOptions& options);
    
    // Convenience methods
    CompileResult compile_aot(const LIR::LIRFunction& lir_func,
                             const std::string& output_file,
                             OptimizationLevel opt_level = OptimizationLevel::O2);
    
    CompileResult compile_wasm(const LIR::LIRFunction& lir_func,
                              const std::string& output_file,
                              OptimizationLevel opt_level = OptimizationLevel::O2);
    
    CompileResult compile_wasi(const LIR::LIRFunction& lir_func,
                              const std::string& output_file,
                              OptimizationLevel opt_level = OptimizationLevel::O2);
};
```

### LIR to Fyra IR Conversion

The `convert_lir_to_fyra_ir()` method translates LIR instructions to Fyra's intermediate representation. This is the key integration point where:

1. LIR instructions are analyzed
2. Fyra IR code is generated
3. Optimization opportunities are identified

### Compilation Options

```cpp
struct FyraCompileOptions {
    CompileTarget target;           // AOT, WASM, or WASI
    OptimizationLevel opt_level;    // O0, O1, O2, O3
    std::string output_file;        // Output filename
    bool debug_info;                // Include debug symbols
    bool verbose;                   // Verbose output
    std::string triple;             // Target triple
};
```

## Integration Points

### 1. Main Entry Point (`src/main.cpp`)

Added command-line flags:
- `-fyra-ir <file>` - Print Fyra IR (for debugging)
- `-aot <file>` - AOT compilation (uses Fyra IR)
- `-wasm <file>` - WebAssembly compilation (uses Fyra IR)
- `-wasi <file>` - WASI compilation (uses Fyra IR)

### 2. Build System (`Makefile`)

Added source files:
- `src/backend/fyra.cpp` - Fyra compiler wrapper
- `src/backend/fyra_ir_generator.cpp` - Direct AST to Fyra IR conversion

### 3. Compilation Pipeline

**For Fyra targets (AOT, WASM, WASI)**:
```
Verified AST → Fyra IR Generator → Fyra IR → Fyra Compiler → Output
```

**For other targets (Register VM, JIT)**:
```
Verified AST → LIR Generator → LIR → Backend → Output
```

## Development Workflow

### Making Changes to Fyra

Since Fyra is a git submodule, you can make changes directly:

```bash
# Navigate to Fyra subproject
cd src/backend/fyra

# Make changes and commit
git add .
git commit -m "Your changes"
git push

# Return to main project
cd ../../../

# Update submodule reference
git add src/backend/fyra
git commit -m "Update Fyra submodule"
```

### Updating Fyra

```bash
# Update to latest Fyra version
git submodule update --remote src/backend/fyra

# Or manually
cd src/backend/fyra
git pull origin main
cd ../../../
git add src/backend/fyra
git commit -m "Update Fyra to latest"
```

## Optimization Levels

### O0 (No Optimization)
- Fastest compilation
- Largest output
- Best for debugging

### O1 (Basic Optimization)
- Moderate compilation time
- Moderate output size
- Good for development

### O2 (Standard Optimization) - Default
- Reasonable compilation time
- Good output size
- Good performance

### O3 (Aggressive Optimization)
- Longest compilation time
- Smallest output
- Best runtime performance

## Error Handling

Fyra compilation errors are caught and reported:

```cpp
CompileResult result = fyra.compile_aot(lir_func, "output.exe");
if (!result.success) {
    std::cerr << "Compilation failed: " << result.error_message << "\n";
    for (const auto& warning : result.warnings) {
        std::cerr << "Warning: " << warning << "\n";
    }
}
```

## Future Enhancements

### Short Term
1. Implement full LIR to Fyra IR conversion
2. Add support for all LIR instruction types
3. Implement type mapping between LIR and Fyra
4. Add optimization passes

### Medium Term
1. Integrate Fyra's optimization pipeline
2. Add profiling and performance analysis
3. Implement cross-compilation support
4. Add incremental compilation

### Long Term
1. Fyra as default backend for production builds
2. Distributed compilation support
3. Custom optimization passes
4. Advanced code generation strategies

## Testing

### Test Fyra IR Generation

```bash
# Create a test program
echo 'print(42);' > test.lm

# Print Fyra IR
./bin/limitly.exe -fyra-ir test.lm

# Test AOT compilation
./bin/limitly.exe -aot test.lm
./test.exe

# Test WASM compilation
./bin/limitly.exe -wasm test.lm

# Test WASI compilation
./bin/limitly.exe -wasi test.lm
```

### Debugging Fyra IR Issues

Enable debug mode in main.cpp:

```cpp
fyra.set_debug_mode(true);
```

This will print:
- Generated Fyra IR
- Compilation commands
- Detailed error messages

## Performance Considerations

### AOT Compilation
- **Startup**: Slower (pre-compilation required)
- **Runtime**: Fastest (native code)
- **Use Case**: Production deployments, performance-critical code

### WASM Compilation
- **Startup**: Moderate (JIT in browser)
- **Runtime**: Good (optimized by browser)
- **Use Case**: Web deployment, cross-platform

### WASI Compilation
- **Startup**: Moderate (JIT in runtime)
- **Runtime**: Good (system interface)
- **Use Case**: Serverless, edge computing

## Troubleshooting

### Fyra Not Found

If you get "Fyra compiler not found" error:

1. Ensure Fyra is installed and in PATH
2. Check Fyra installation: `fyra --version`
3. Update Fyra: `git submodule update --remote`

### Compilation Failures

1. Check LIR generation: `./bin/limitly.exe -lir program.lm`
2. Enable debug mode for detailed output
3. Check Fyra documentation for IR format requirements

### Performance Issues

1. Try different optimization levels
2. Profile with `-O0` for debugging
3. Use `-O3` for production builds
4. Check for unnecessary allocations in LIR

## References

- Fyra Repository: https://github.com/netesy/fyra
- LIR Documentation: See `src/lir/lir.hh`
- Limit Language Guide: See `docs/guide.md`
