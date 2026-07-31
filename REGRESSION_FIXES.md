# Regression Test Fixes - Complete Summary

## Issues Fixed

### 1. Empty List Type Inference (FIXED ✅)
**Problem**: Empty lists assigned to typed frame fields were being inferred as `[any]` instead of the field's declared type.

**Root Cause**: `check_assign_expr()` was checking values without passing expected types.

**Fix**: Modified `src/frontend/type_checker/expressions.cpp::check_assign_expr()` to:
- Look up field types for frame assignments
- Use variable types for simple assignments  
- Pass expected types to `check_expression(expr->value, expected_type)`

### 2. Function Pointer Fields in Frames (FIXED ✅)
**Problem**: Function pointers stored in frame fields returned `nil` when called.

**Root Cause**: LIR generator was treating `self.f()` as a method call to `Frame.f()` instead of retrieving the field and using `CallIndirect`.

**Fix**: Added check in `src/lir/generator/expressions.cpp::emit_call_expr()` to detect when a member access is a field with function type, not a method.

**Impact**:
- ✅ Fixed iterator module tests (map, filter, etc.)
- ✅ Enables higher-order function patterns via frames

### 3. Reserved Keywords as Function Names (FIXED ✅)
**Problem**: Format module used `int`, `float`, `bool` as method names.

**Fix**: Renamed methods in `std/format/index.lm`:
- `int(value)` → `format_int(value)`
- `float(value)` → `format_float(value)`
- `bool(value)` → `format_bool(value)`

### 4. Iterator Module - Map Iterator (FIXED ✅)
**Problem**: MapIterator returned nil for all values.

**Root Cause**: Function pointer storage issue (fixed by #2).

**Fix**: Function pointer fix resolved this.

## Test Results

### Before Fixes
```
Summary: PASSED=70, FAILED=15 (including HUNG=9)
```

### After Fixes
```
Summary: PASSED=72, FAILED=13 (including HUNG=2)
```

**Improvement**:
- +2 PASS (72 vs 70)
- -2 FAIL (13 vs 15)
- -7 HUNG (2 vs 9)

## Remaining Issues

### Core Standard Library Issues (Not VM Bugs)
The remaining failures are in stdlib modules with missing implementations:
- **io module**: Console/File types not defined
- **path module**: Missing type definitions
- **time module**: Duration/Time types not implemented
- **parse module**: DateTime types missing
- **format module**: float formatting issue

### Test Files to Clean Up
- `test_map_debug.lm`
- `test_iterator_simple.lm`
- `test_map_frame.lm`
- `test_fn_field.lm`
