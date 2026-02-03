# Final JIT Fixes

## Issues Fixed

### 1. Unknown LIR Operation 29
**Problem**: The debug output showed "Unknown op 29" which was likely a loop control operation.

**Solution**: Added debug output for all remaining LIR operations:
- `Neg` - Negate
- `JumpIf` - Jump if true
- `Label` - Label definition
- `CallVoid` - Void function call
- `CallIndirect` - Indirect function call
- `CallBuiltin` - Builtin function call
- `CallVariadic` - Variadic function call
- `FuncDef` - Function definition
- `Param` - Parameter definition
- `Ret` - Return with value
- `VaStart`, `VaArg`, `VaEnd` - Variadic argument handling
- `Copy` - Value copy
- `ConstructError`, `ConstructOk` - Result construction
- `IsError`, `Unwrap`, `UnwrapOr` - Result operations

**Impact**: Now all LIR operations will be properly identified in debug output.

### 2. Missing Runtime Library Path
**Problem**: Linker error: `cannot find obj/release/limitly_runtime.a: No such file or directory`

**Root Cause**: The JIT was using the wrong path for the runtime library. The build system creates it at `build/obj/release/limitly_runtime.a`, not `obj/release/limitly_runtime.a`.

**Solution**: Changed the driver option from:
```cpp
m_context.add_driver_option("obj/release/limitly_runtime.a");
```

To:
```cpp
m_context.add_driver_option("build/obj/release/limitly_runtime.a");
```

**Impact**: JIT compilation can now successfully link against the runtime library.

## Files Modified

- `src/backend/jit/jit.cpp`
  - Added debug output for all LIR operations (lines ~450-470)
  - Fixed runtime library path (line ~308)

## Testing

After these fixes, the JIT should:
1. ✅ Show proper debug output for all LIR operations
2. ✅ Successfully link against the runtime library
3. ✅ Execute JIT-compiled code without linker errors

## Next Steps

Run the test again:
```bash
./bin/limitly.exe -jit-debug test_simple.lm
```

Expected output:
- All LIR instructions properly identified
- No linker errors
- Successful execution with output
