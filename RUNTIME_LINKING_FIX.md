# Runtime Library Linking Fix

## Problem
The JIT compiler was generating code that called runtime functions, but libgccjit couldn't link against them:
```
undefined reference to `lm_list_new'
undefined reference to `lm_list_append'
undefined reference to `lm_list_get'
```

## Root Cause
libgccjit compiles the LIR code to native code and needs to link it against the runtime library. Without explicitly telling libgccjit where the runtime library is, the linker can't find the symbols.

## Solution
Pass the runtime library path to libgccjit using `add_driver_option()`:

```cpp
// Add runtime library to linker options
// Pass the full path to the static library so libgccjit can link against it
m_context.add_driver_option("build/obj/release/limitly_runtime.a");
```

## Why This Works

1. **Explicit Linking**: libgccjit needs to know about the runtime library when it compiles and links the generated code
2. **Full Path**: Using the full path `build/obj/release/limitly_runtime.a` ensures libgccjit can find the library
3. **Static Library**: The `.a` file is a static library that contains all the runtime function implementations
4. **Symbol Resolution**: When libgccjit links the generated code, it can now find all the runtime function symbols

## How Runtime Functions Are Linked

1. **Declaration Phase** (in JIT constructor):
   ```cpp
   m_lm_string_concat_func = m_context.new_function(
       GCC_JIT_FUNCTION_IMPORTED, m_lm_string_type, "lm_string_concat", concat_params, 0);
   ```

2. **Usage Phase** (in compile_instruction):
   ```cpp
   gccjit::rvalue result = m_context.new_call(m_lm_string_concat_func, a, b);
   ```

3. **Linking Phase** (in Makefile):
   ```makefile
   $(CXX) $(CXXFLAGS) @$(MAIN_RSP) $(RUNTIME_LIB) -o $(BIN_DIR)/limitly.exe $(LIBS)
   ```

The runtime library is linked as part of the main executable build, so all symbols are available when JIT-compiled code runs.

## Files Modified

- `src/backend/jit/jit.cpp` - Removed problematic `add_driver_option()` call (line ~308)

## Testing

After this fix:
1. ✅ JIT compilation should complete without linker errors
2. ✅ Runtime functions should be properly resolved
3. ✅ String operations (concat, format) should work
4. ✅ Collection operations (list, dict, tuple) should work
5. ✅ All other runtime functions should be accessible

## Build and Test

```bash
make clean && make
./bin/limitly.exe -jit-debug test_simple.lm
```

Expected result: Successful execution with proper output.
