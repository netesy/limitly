# Compilation Architecture Update

## Overview
The Limit language has been upgraded from a single VM-based execution model to a multi-mode compilation architecture supporting:
1. **Register VM** - Direct interpretation (development/debugging)
2. **JIT Compilation** - Runtime compilation of hot paths (performance)
3. **AOT Compilation** - Ahead-of-time compilation to native code (production)

## Architecture Changes

### Previous Architecture
```
Source Code
    ↓
Scanner → Parser → Type Checker → LIR Generator
    ↓
VM (vm.cpp) - Single execution mode
    ↓
Execution
```

### New Architecture
```
Source Code
    ↓
Scanner → Parser → Type Checker → LIR Generator
    ↓
    ├─→ Register VM (register.cpp) - Interpretation
    ├─→ JIT Compiler (jit.cpp) - Runtime compilation
    └─→ AOT Compiler (jit.cpp) - Pre-compilation
    ↓
Execution
```

## File Changes

### Removed
- `src/backend/vm.hh` - Old VM header
- `src/backend/vm.cpp` - Old VM implementation

### Added
- `src/backend/register.hh` - Register VM header
- `src/backend/register.cpp` - Register VM implementation
- `src/backend/jit.hh` - JIT/AOT compiler header
- `src/backend/jit.cpp` - JIT/AOT compiler implementation

## Execution Modes

### Mode 1: Register VM (Default)
**Command**: `./bin/limitly.exe sample.lm` or `./bin/limitly.exe --vm sample.lm`

**Characteristics**:
- Direct interpretation of LIR instructions
- No compilation overhead
- Immediate execution
- Moderate performance
- Best for: Development, debugging, quick scripts

**Performance Profile**:
- Startup: Fast (< 100ms)
- Execution: Moderate (10-100x slower than native)
- Memory: Low (only LIR in memory)

### Mode 2: JIT Compilation
**Command**: `./bin/limitly.exe --jit sample.lm`

**Characteristics**:
- Monitors code execution
- Identifies hot paths (frequently executed code)
- Compiles hot paths to native code at runtime
- Gradually improves performance
- Best for: Long-running applications, performance-critical code

**Performance Profile**:
- Startup: Moderate (compilation during execution)
- Execution: High (near-native after warmup)
- Memory: Moderate (LIR + compiled code)
- Warmup: 1-10 seconds typical

**How It Works**:
1. Start with Register VM interpretation
2. Monitor execution frequency of code blocks
3. When threshold is reached, compile to native code
4. Replace interpreted code with native version
5. Continue execution with compiled code

### Mode 3: AOT Compilation
**Command**: `./bin/limitly.exe --aot sample.lm` or `./bin/limitly.exe --aot -o sample.exe sample.lm`

**Characteristics**:
- Compiles entire program before execution
- Produces standalone executable
- No runtime compilation
- Best for: Production deployments, performance-critical applications

**Performance Profile**:
- Startup: Slower (pre-compilation required)
- Execution: High (native code)
- Memory: Moderate (compiled code only)
- Compilation: 1-30 seconds typical

**How It Works**:
1. Parse and type-check entire program
2. Generate LIR for all code
3. Compile all LIR to native code
4. Link and generate executable
5. Execute native code directly

## Command Line Interface

### Execution Mode Selection
```bash
# Register VM (default)
./bin/limitly.exe sample.lm
./bin/limitly.exe --vm sample.lm

# JIT Compilation
./bin/limitly.exe --jit sample.lm

# AOT Compilation
./bin/limitly.exe --aot sample.lm
```

### Output Options
```bash
# Compile to executable (AOT only)
./bin/limitly.exe --aot -o output.exe sample.lm

# Compile to object file (AOT only)
./bin/limitly.exe --aot -c output.o sample.lm

# Compile to assembly (AOT only)
./bin/limitly.exe --aot -S output.s sample.lm
```

### Debugging Options
```bash
# Print AST
./bin/limitly.exe -ast sample.lm

# Print tokens
./bin/limitly.exe -tokens sample.lm

# Print LIR
./bin/limitly.exe -bytecode sample.lm

# Print generated native code (JIT/AOT)
./bin/limitly.exe --jit -asm sample.lm
```

## Implementation Details

### Register VM (register.cpp)
- Interprets LIR instructions directly
- Maintains execution stack and registers
- Handles function calls and returns
- Manages memory and garbage collection
- Supports all language features

### JIT Compiler (jit.cpp)
- Monitors code execution frequency
- Identifies hot paths using profiling
- Converts LIR to native code
- Performs optimization passes
- Handles code patching and replacement

### AOT Compiler (jit.cpp)
- Compiles entire program upfront
- Performs global optimizations
- Generates standalone executable
- Handles linking and relocation
- Produces optimized native code

## Performance Characteristics

### Startup Time
```
Register VM:  < 100ms
JIT:          100ms - 1s (initial interpretation)
AOT:          1s - 30s (compilation phase)
```

### Execution Speed (relative to native C++)
```
Register VM:  10-100x slower
JIT:          1-5x slower (after warmup)
AOT:          1-2x slower (with optimizations)
```

### Memory Usage
```
Register VM:  Low (LIR only)
JIT:          Moderate (LIR + compiled code)
AOT:          Moderate (compiled code only)
```

## Use Case Recommendations

### Use Register VM When:
- Developing and debugging code
- Running quick scripts
- Startup time is critical
- Memory is limited
- Code is not performance-critical

### Use JIT When:
- Running long-lived applications
- Performance matters but startup time is acceptable
- Code has hot paths that benefit from compilation
- Want automatic optimization

### Use AOT When:
- Deploying to production
- Performance is critical
- Want predictable performance
- Distributing standalone executables
- Compilation time is acceptable

## Migration Guide

### For Developers
1. Continue using Register VM for development (default)
2. Use `--jit` flag for performance testing
3. Use `--aot` flag for production builds

### For Users
1. Run scripts with default Register VM
2. For performance-critical code, use `--jit` or `--aot`
3. For production, use AOT-compiled executables

## Future Enhancements

### Short Term
- Optimize JIT compilation speed
- Improve hot path detection
- Add profiling information

### Medium Term
- Implement tiered compilation (multiple optimization levels)
- Add inline caching for method dispatch
- Implement escape analysis for optimization

### Long Term
- LLVM backend for better code generation
- Vectorization support
- SIMD optimizations
- Parallel compilation

## Backward Compatibility

All existing Limit programs continue to work without modification:
- Default behavior uses Register VM (same as before)
- Existing scripts run unchanged
- No syntax changes required
- Optional compilation modes for performance

## Testing

### Test Coverage
- Register VM: All existing tests pass
- JIT: Correctness tests (same as Register VM)
- AOT: Correctness tests (same as Register VM)

### Performance Benchmarks
- Fibonacci sequence
- Matrix multiplication
- String processing
- Concurrent tasks
- Memory allocation

## Conclusion

The new multi-mode compilation architecture provides flexibility for different use cases:
- **Register VM** for development and quick execution
- **JIT** for performance-critical long-running applications
- **AOT** for production deployments and standalone executables

This architecture maintains backward compatibility while enabling significant performance improvements for users who need them.
