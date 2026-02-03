# Bug Fix: Void Type Casting Error

## Issue
When compiling JIT code with tuple iteration, the compiler threw an error:
```
libgccjit.so: error: gcc_jit_context_new_cast: cannot cast r12 from type: void * to type: void
```

## Root Cause
In the `compile_call` function, when assigning the result of a function call to a register, the code was using `m_int_type` as the destination register type regardless of the actual function return type. When a function returned `void`, this caused the code to try to create a local variable of type `void`, which is invalid in C.

## Solution
Changed the destination register type from hardcoded `m_int_type` to the actual `return_type` determined from the function's instructions:

### Before
```cpp
gccjit::lvalue dst = get_jit_register(inst.dst, m_int_type);
m_current_block.add_assignment(dst, call_result);
```

### After
```cpp
gccjit::lvalue dst = get_jit_register(inst.dst, return_type);
m_current_block.add_assignment(dst, call_result);
```

## Changes Made
- Modified `compile_call` function in `src/backend/jit/jit.cpp`
- Updated all 5 branches (0-4 args and 5+ args) to use `return_type` instead of `m_int_type`
- Ensured void functions don't try to assign results to registers

## Testing
The fix should resolve the casting error when:
- Iterating over tuples
- Calling functions that return void
- Calling functions with various return types

## Files Modified
- `src/backend/jit/jit.cpp` - Fixed compile_call function (lines ~1219-1283)
