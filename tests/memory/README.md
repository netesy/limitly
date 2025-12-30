# Memory Safety Tests

This directory contains comprehensive tests for memory safety checking in the Limit programming language.

## Test Files

### `memory_safety_tests.lm`
Tests valid memory operations that should pass memory safety checks:
- Variable initialization and use
- Move semantics and ownership transfer
- Linear type tracking
- Reference creation and validation
- Memory regions and scoping
- Function parameter ownership
- Borrowing semantics
- Complex ownership patterns

### `memory_error_tests.lm`
Tests invalid memory operations that should trigger memory safety errors:
- Use after move
- Use before initialization
- Double move
- Use after scope ends
- Invalid references after move
- Memory leaks
- Dangling pointers
- Generation mismatches
- Buffer overflows
- Uninitialized variable usage

## Memory Safety Features Tested

1. **Linear Types**: Variables can only be used once after being moved
2. **Ownership Transfer**: Values are moved between variables, invalidating the source
3. **Reference Tracking**: References are tracked and validated for lifetime
4. **Generation System**: References are tied to specific generations of linear types
5. **Scope Analysis**: Variables are tracked within their lexical scopes
6. **Initialization Checking**: Variables must be initialized before use
7. **Move Semantics**: Explicit tracking of when values are moved
8. **Memory Regions**: Hierarchical memory management with region-based allocation

## Running the Tests

```bash
# Run memory safety tests (should pass)
./bin/limitly.exe tests/memory/memory_safety_tests.lm

# Run memory error tests (should detect errors)
./bin/limitly.exe tests/memory/memory_error_tests.lm
```

## Expected Behavior

- **memory_safety_tests.lm**: Should compile and run successfully with no memory safety errors
- **memory_error_tests.lm**: Should detect multiple memory safety violations and report them with helpful error messages

## Memory Model

The memory checker implements a compile-time memory safety model based on:

1. **Linear Types**: Each value has a single owner at any time
2. **Regions**: Memory is organized into hierarchical regions
3. **Generations**: References are tied to specific generations of their targets
4. **Borrowing**: Temporary access without ownership transfer
5. **Move Semantics**: Explicit ownership transfer between variables
6. **Lifetime Analysis**: Compile-time tracking of variable lifetimes
7. **Escape Analysis**: Prevention of references outliving their targets

This model prevents common memory safety issues like:
- Use-after-free
- Double-free
- Memory leaks
- Dangling pointers
- Buffer overflows
- Uninitialized memory access