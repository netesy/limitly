# Fyra IR Architecture - Direct AST to IR Compilation

## Overview

The Limit language now uses **Fyra IR as a primary intermediate representation** for AOT and WebAssembly compilation, similar to how LLVM serves as an IR layer in other compilers. This architecture bypasses LIR entirely for Fyra targets, providing a cleaner separation of concerns.

## Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                     Source Code (.lm)                           │
└────────────────────────────┬────────────────────────────────────┘
                             │
                    ┌────────▼────────┐
                    │  Scanner/Parser │
                    └────────┬────────┘
                             │
                    ┌────────▼────────┐
                    │      AST        │
                    └────────┬────────┘
                             │
                    ┌────────▼────────┐
                    │  Type Checker   │
                    └────────┬────────┘
                             │
                    ┌────────▼────────┐
                    │ Memory Checker  │
                    └────────┬────────┘
                             │
                    ┌────────▼────────────────────────────┐
                    │    Verified AST (Canonical IR)      │
                    └────────┬──────────────┬──────────────┘
                             │              │
              ┌──────────────┘              └──────────────┐
              │                                            │
    ┌─────────▼──────────┐                    ┌───────────▼────────┐
    │  LIR Generator     │                    │ Fyra IR Generator  │
    │  (for VM/JIT)      │                    │ (for AOT/WASM)     │
    └─────────┬──────────┘                    └───────────┬────────┘
              │                                            │
    ┌─────────▼──────────┐                    ┌───────────▼────────┐
    │  LIR Instructions  │                    │   Fyra IR Code     │
    └─────────┬──────────┘                    └───────────┬────────┘
              │                                            │
    ┌─────────┴──────────┐                    ┌───────────┴────────┐
    │                    │                    │                    │
┌───▼──┐  ┌──────┐   ┌───▼──┐            ┌───▼──┐  ┌──────┐  ┌───▼──┐
│ Reg  │  │ JIT  │   │ Opt  │            │ AOT  │  │ WASM │  │ WASI │
│ VM   │  │ Comp │   │ Pass │            │ Comp │  │ Comp │  │ Comp │
└──────┘  └──────┘   └──────┘            └──────┘  └──────┘  └──────┘
```

## Key Components

### 1. Fyra IR Generator (`src/backend/fyra_ir_generator.hh/cpp`)

Converts verified AST directly to Fyra IR without intermediate LIR step.

**Key Classes**:
- `FyraIRGenerator` - Main generator class
- `FyraIRFunction` - Represents a function in Fyra IR
- `FyraInstruction` - Individual IR instruction

**Key Methods**:
```cpp
// Generate from entire program
std::shared_ptr<FyraIRFunction> generate_from_ast(
    const std::shared_ptr<Frontend::AST::Program>& program);

// Generate from single function
std::shared_ptr<FyraIRFunction> generate_function(
    const std::shared_ptr<Frontend::AST::FunctionDeclaration>& func_decl);
```

### 2. Fyra Compiler (`src/backend/fyra.hh/cpp`)

Wraps Fyra compiler invocation and handles compilation to different targets.

**Supported Targets**:
- **AOT**: Native executable compilation
- **WASM**: WebAssembly module
- **WASI**: WebAssembly System Interface

### 3. Compilation Pipeline

**For Fyra Targets** (AOT, WASM, WASI):
```
AST → Type Check → Memory Check → Fyra IR Gen → Fyra Compiler → Output
```

**For VM/JIT Targets**:
```
AST → Type Check → Memory Check → LIR Gen → VM/JIT Backend → Output
```

## Fyra IR Format

Fyra IR is a low-level intermediate representation with the following characteristics:

### Type System
```cpp
enum class FyraType {
    I32,        // 32-bit integer
    I64,        // 64-bit integer
    F64,        // 64-bit float
    Bool,       // Boolean
    Ptr,        // Pointer
    Void,       // Void type
    Struct,     // Struct type
    Array,      // Array type
    Function    // Function type
};
```

### Instruction Format
```
%result = operation %operand1, %operand2 : ResultType
```

Example:
```
%t0 = const 42 : i64
%t1 = add %t0, %t0 : i64
call print %t1 : void
ret %t1 : i64
```

## Expression Code Generation

### Binary Operations
```cpp
// Input: a + b
// Output:
%t0 = load_var a : i64
%t1 = load_var b : i64
%t2 = add %t0, %t1 : i64
```

### Function Calls
```cpp
// Input: foo(x, y)
// Output:
%t0 = load_var x : i64
%t1 = load_var y : i64
%t2 = call foo %t0, %t1 : i64
```

### Control Flow
```cpp
// Input: if (cond) { ... } else { ... }
// Output:
%t0 = load_var cond : bool
jmpif %t0, L_else : void
; then branch
jmp L_end : void
L_else:
; else branch
L_end:
```

## Integration with Main Pipeline

### Command-Line Usage

```bash
# Print Fyra IR for debugging
./bin/limitly.exe -fyra-ir program.lm

# Compile to native executable
./bin/limitly.exe -aot program.lm

# Compile to WebAssembly
./bin/limitly.exe -wasm program.lm

# Compile to WASI
./bin/limitly.exe -wasi program.lm
```

### Main Entry Point Flow

```cpp
// 1. Parse and type check
auto ast = parser.parse();
auto typed_ast = type_checker.check(ast);
auto verified_ast = memory_checker.check(typed_ast);

// 2. For Fyra targets, generate Fyra IR directly
if (useAot || useWasm || useWasi) {
    FyraIRGenerator gen;
    auto fyra_ir = gen.generate_from_ast(verified_ast);
    
    FyraCompiler compiler;
    auto result = compiler.compile_aot(fyra_ir, output_file);
}

// 3. For other targets, use LIR
else {
    LIRGenerator gen;
    auto lir = gen.generate_program(verified_ast);
    
    RegisterVM vm;
    vm.execute(lir);
}
```

## Advantages of This Architecture

### 1. **Separation of Concerns**
- LIR remains focused on VM/JIT execution
- Fyra IR handles compilation to native/WASM
- Each IR optimized for its use case

### 2. **Direct AST to IR**
- Fewer transformation steps
- Easier to maintain type information
- Better error messages with source mapping

### 3. **Scalability**
- Easy to add new backends (e.g., LLVM, Cranelift)
- Each backend gets its own IR generator
- No need to modify existing backends

### 4. **Performance**
- Fyra IR can be optimized independently
- No overhead from LIR conversion
- Direct compilation to target format

## Future Enhancements

### Short Term
1. Implement full expression support in Fyra IR generator
2. Add optimization passes for Fyra IR
3. Implement type mapping for complex types
4. Add support for closures and higher-order functions

### Medium Term
1. Integrate Fyra's optimization pipeline
2. Add cross-compilation support
3. Implement incremental compilation
4. Add profiling and performance analysis

### Long Term
1. Support for additional backends (LLVM, Cranelift)
2. Distributed compilation
3. Custom optimization passes
4. Advanced code generation strategies

## Debugging

### Print Fyra IR
```bash
./bin/limitly.exe -fyra-ir program.lm
```

### Enable Debug Mode
In `src/main.cpp`, set:
```cpp
fyra.set_debug_mode(true);
```

This will output:
- Generated Fyra IR code
- Compilation commands
- Detailed error messages

### Common Issues

**Issue**: Fyra IR generation fails
- Check AST is valid: `./bin/limitly.exe -ast program.lm`
- Check type checking passes: Look for type errors
- Enable debug mode for detailed output

**Issue**: Compilation fails
- Verify Fyra is installed: `fyra --version`
- Check Fyra IR output: `./bin/limitly.exe -fyra-ir program.lm`
- Review Fyra documentation for IR format requirements

## References

- Fyra Repository: https://github.com/netesy/fyra
- Fyra IR Documentation: See Fyra project docs
- Limit Language Guide: See `docs/guide.md`
- LIR Documentation: See `src/lir/lir.hh`
