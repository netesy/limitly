# Type-Aware ToString Implementation

## Current Status
We have successfully added explicit type information to LIR instructions:
- `result_type`: Type of the result register
- `type_a`: Type of operand a
- `type_b`: Type of operand b
- `call_arg_types`: Types of function call arguments

## Problem
The `ToString` operation needs to convert values to strings, but currently:
1. Register VM relies on pointer range detection (unreliable on 64-bit systems)
2. JIT compiler doesn't have type information at runtime

## Solution
Use the explicit type information from LIR instructions to guide the conversion:

### For Register VM
When executing `ToString r8, r7 [types: r8:ptr, r7:ptr]`:
1. Check `type_a` (r7's type) - it's `Ptr`
2. Since it's a pointer, call `lm_value_to_string()` which handles collection detection
3. Store the result in r8

### For JIT Compiler
When compiling `ToString r8, r7 [types: r8:ptr, r7:ptr]`:
1. Check `type_a` (r7's type) - it's `Ptr`
2. Generate code to call `lm_value_to_string()` with the pointer value
3. Extract the string data pointer from the returned LmString

## Implementation Steps

### Step 1: Update Register VM ToString Handler
- Read `inst.type_a` to determine the operand type
- If `type_a == Type::Ptr`, call `lm_value_to_string()`
- Otherwise, use type-specific conversion

### Step 2: Update JIT ToString Handler
- Read `inst.type_a` to determine the operand type
- If `type_a == Type::Ptr`, generate call to `lm_value_to_string()`
- Extract string data pointer from LmString result

### Step 3: Propagate Type Information
- Ensure LIR generator sets `type_a` and `type_b` for all instructions
- Verify type information flows through the compilation pipeline

## Benefits
1. **Correctness**: No more unreliable pointer range detection
2. **Clarity**: Type information is explicit in the LIR
3. **Maintainability**: Easy to understand what types are being operated on
4. **Performance**: Can optimize based on known types
