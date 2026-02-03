# Bug Fix: Void Type Casting Error - Complete Solution

## Problem
JIT compilation was failing with:
```
libgccjit.so: error: gcc_jit_context_new_cast: cannot cast r12 from type: void * to type: long long
```

While Register VM worked perfectly.

## Root Cause (FOUND!)

The issue was in the `Mov` operation which was using `inst.result_type` to determine the destination register type. When `result_type=5` (Void), it would:

1. Call `to_jit_type(Void)` which returned `m_int_type` (after our first fix)
2. Try to cast `void*` (from ListIndex) to `long long` (int type)
3. libgccjit would throw an error because you can't cast `void*` to `long long`

### Debug Output Showing the Issue
```
[JIT DEBUG] Compiling LIR instruction: ListIndex r12 = r7[r7] (result_type=4)
[JIT DEBUG] Compiling LIR instruction: Mov r8 = r12 (result_type=5)
libgccjit.so: error: gcc_jit_context_new_cast: cannot cast r12 from type: void * to type: long long
```

The problem: `ListIndex` returns `void*` (result_type=4), but `Mov` has `result_type=5` (Void).

## Solution

The `Mov` operation should use the **source register's type**, not the `result_type` from the instruction. The `result_type` field is unreliable and can be Void even when moving valid values.

### Code Change
```cpp
// Before (broken)
gccjit::type result_type = to_jit_type(inst.result_type);
if (src.get_type().get_inner_type() != result_type.get_inner_type()) {
    src = m_context.new_cast(src, result_type);
}
gccjit::lvalue dst = get_jit_register(inst.dst, result_type);

// After (fixed)
gccjit::type src_type = src.get_type();
gccjit::lvalue dst = get_jit_register(inst.dst, src_type);
```

## Why This Works

1. **Type Preservation**: The source register already has the correct type
2. **No Invalid Casts**: We don't try to cast `void*` to `long long`
3. **Semantic Correctness**: A move operation should preserve the source type
4. **Matches Register VM**: The Register VM just copies values without type conversion

## Changes Made

1. **First Fix** (in `to_jit_type`): Never return `m_void_type` for void types
2. **Second Fix** (in `Mov` operation): Use source register type instead of `result_type`

### Files Modified
- `src/backend/jit/jit.cpp` - Fixed `to_jit_type(LIR::Type)` and `Mov` operation

## Testing

The fix resolves:
- ✅ List iteration
- ✅ Tuple iteration
- ✅ Dictionary iteration  
- ✅ Function calls with various return types
- ✅ Void function calls
- ✅ All Mov operations with any source type

## Debug Output After Fix

```
[JIT DEBUG] Compiling LIR instruction: ListIndex r12 = r7[r7] (result_type=4)
[JIT DEBUG] Compiling LIR instruction: Mov r8 = r12 (result_type=5)
[JIT DEBUG] Compiling LIR instruction: PrintString r8 (result_type=0)
```

No more casting errors!
