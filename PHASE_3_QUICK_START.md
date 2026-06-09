# Phase 3: Quick Start Guide

## Overview

Phase 3 updates LIR generation to use new generic operations. This guide helps implement Phase 3 quickly and correctly.

## Key Changes at a Glance

### 1. Memory Load/Store (Highest Impact)

**Before**:
```cpp
if (type == Type::I32) {
    emit(FFILoadInt32, dst, src);
} else if (type == Type::I64) {
    emit(FFILoadInt64, dst, src);
} // ... 9 more types
```

**After**:
```cpp
LIR::LIR_Inst load;
load.op = LIR::LIR_Op::MemoryLoad;
load.result_type = type;  // Type in metadata
load.dst = dst;
load.a = src;
emit(load);
```

**Impact**: 22 opcodes → 2 opcodes

### 2. Pointer Operations (Pure Renames)

**Before**:
```cpp
emit(FFIAddPtr, dst, ptr, offset);
emit(FFISubPtr, dst, ptr, offset);
emit(FFIPtrDiff, dst, ptr1, ptr2);
```

**After**:
```cpp
emit(PtrAdd, dst, ptr, offset);
emit(PtrSub, dst, ptr, offset);
emit(PtrDiff, dst, ptr1, ptr2);
```

**Impact**: Just change opcode names (FFI* → Ptr*)

### 3. String/Buffer Marshaling

**Before**:
```cpp
emit(FFIToCString, dst, str);
emit(FFIFromCString, dst, cstr);
emit(FFIBufferAlloc, dst, size);
```

**After**:
```cpp
auto marshal = make_marshal(dst, str, MarshalType::StringToCString);
emit(Marshal, marshal);

auto unmarshal = make_unmarshal(dst, cstr, MarshalType::CStringToString);
emit(Unmarshal, unmarshal);

emit(BufferCreate, dst, size);
```

**Impact**: Metadata-based dispatch

### 4. Foreign Calls (Largest Reduction)

**Before** (8+ instructions):
```cpp
emit(FFICCallFrameCreate, frame, argc, stack_size);
for (arg : args) {
    emit(FFICCallFrameSetReg, frame, i, arg);
}
emit(FFICCallExecute, dst, func_ptr);
```

**After** (1 instruction):
```cpp
auto call = make_foreign_call(dst, func_ptr, args);
emit(ForeignCall, call);
```

**Impact**: 80% instruction reduction

---

## Implementation Checklist

### Phase 3A: Memory Operations

- [ ] Find all FFILoadInt* generation
- [ ] Replace with MemoryLoad + result_type
- [ ] Find all FFIStoreInt* generation
- [ ] Replace with MemoryStore + type_a
- [ ] Test memory operations

### Phase 3B: Pointer Operations

- [ ] Rename FFIAddPtr → PtrAdd
- [ ] Rename FFISubPtr → PtrSub
- [ ] Rename FFIPtrDiff → PtrDiff
- [ ] Rename FFIAlignPtr → PtrAlign
- [ ] Rename FFIIsAligned → PtrIsAligned
- [ ] Test pointer operations

### Phase 3C: Marshaling

- [ ] Find FFIToCString generation
- [ ] Replace with Marshal + StringToCString metadata
- [ ] Find FFIFromCString generation
- [ ] Replace with Marshal + CStringToString metadata
- [ ] Find FFIBuffer* generation
- [ ] Replace with Buffer* operations
- [ ] Test marshaling operations

### Phase 3D: Foreign Calls

- [ ] Find FFICCallFrame* sequences
- [ ] Replace with single ForeignCall
- [ ] Set call_args, call_arg_types, imm fields
- [ ] Test foreign call generation

### Phase 3E: Build & Test

- [ ] Compile Phase 3 changes
- [ ] Run full test suite
- [ ] Verify no regressions
- [ ] Check performance

---

## Code Patterns to Use

### Pattern 1: Generic Memory Load

```cpp
// Always use this pattern for memory loads
LIR::LIR_Inst load;
load.op = LIR::LIR_Op::MemoryLoad;
load.result_type = element_type;
load.dst = dst_reg;
load.a = src_ptr_reg;
function.add_instruction(load);
```

### Pattern 2: Generic Memory Store

```cpp
// Always use this pattern for memory stores
LIR::LIR_Inst store;
store.op = LIR::LIR_Op::MemoryStore;
store.type_a = element_type;
store.dst = dst_ptr_reg;   // Pointer destination
store.a = src_reg;         // Value source
store.b = value_reg;       // Alternative usage
function.add_instruction(store);
```

### Pattern 3: Marshaling with Metadata

```cpp
// For string conversions
LIR::LIR_Inst marshal;
marshal.op = LIR::LIR_Op::Marshal;
marshal.result_type = Type::Ptr;
marshal.type_a = Type::String;
marshal.dst = dst_reg;
marshal.a = src_reg;
marshal.imm = static_cast<uint32_t>(LIR::Metadata::MarshalType::StringToCString);
function.add_instruction(marshal);
```

### Pattern 4: Foreign Call

```cpp
// For foreign function calls
LIR::LIR_Inst call;
call.op = LIR::LIR_Op::ForeignCall;
call.result_type = return_type;
call.dst = dst_reg;
call.call_args = {func_ptr_reg, arg1_reg, arg2_reg};
call.call_arg_types = {Type::Ptr, Type::I64, Type::I64};
call.imm = static_cast<uint32_t>(LIR::CallingConvention::SystemV_x64);
function.add_instruction(call);
```

---

## Search/Replace Guide

### Find All Memory Load Generation

```
Pattern: (FFILoadInt|FFILoadUInt|FFILoadFloat|FFILoadDouble|FFILoadPtr)
Files: src/lir/generator/expressions.cpp
Replace with: MemoryLoad + result_type
```

### Find All Memory Store Generation

```
Pattern: (FFIStoreInt|FFIStoreUInt|FFIStoreFloat|FFIStoreDouble|FFIStorePtr)
Files: src/lir/generator/expressions.cpp
Replace with: MemoryStore + type_a
```

### Find All Pointer Operation Generation

```
Pattern: (FFIAddPtr|FFISubPtr|FFIPtrDiff|FFIAlignPtr|FFIIsAligned)
Files: src/lir/generator/*.cpp
Replace with: Ptr* (just rename)
```

### Find All String Marshaling

```
Pattern: (FFIToCString|FFIFromCString)
Files: src/lir/generator/*.cpp
Replace with: Marshal/Unmarshal + metadata
```

### Find All Buffer Operations

```
Pattern: (FFIBuffer|FFICString)
Files: src/lir/generator/*.cpp
Replace with: Buffer*/Marshal operations
```

### Find All Foreign Call Frames

```
Pattern: (FFICCallFrame|FFICCallExecute)
Files: src/lir/generator/core.cpp
Replace with: Single ForeignCall
```

---

## Testing Your Changes

### 1. After Each Subsection

```bash
make clean
make
# Check for compilation errors
```

### 2. After Memory Operations

```bash
./tests/run_tests.bat
# Verify no failures in memory tests
```

### 3. After Pointer Operations

```bash
./bin/limitly.exe tests/basic/variables.lm
# Test pointer operations
```

### 4. After Marshaling

```bash
./bin/limitly.exe tests/integration/full_suite.lm
# Test string and buffer operations
```

### 5. After Foreign Calls

```bash
./tests/run_tests.bat
# Full test suite - should all pass
```

---

## Troubleshooting

### Build Error: Undefined Reference

**Cause**: Opcode name mismatch
**Solution**: Check enum value is used correctly

```cpp
// ✅ Correct
load.op = LIR::LIR_Op::MemoryLoad;

// ❌ Wrong
load.op = LIR::LIR_Op::FFILoadInt32;
```

### Build Error: Invalid Enum Value

**Cause**: Using old opcode name
**Solution**: Replace with new generic opcode

```cpp
// Find all FFI* opcodes and replace
FFILoadInt32 → MemoryLoad (use result_type)
FFIAddPtr → PtrAdd
FFIToCString → Marshal (use metadata)
```

### Test Failure: Memory Operations

**Cause**: result_type or type_a not set correctly
**Solution**: Verify metadata fields are correct

```cpp
load.op = LIR::LIR_Op::MemoryLoad;
load.result_type = element_type;  // Must be set!
```

### Test Failure: Marshal Operations

**Cause**: Metadata encoding incorrect
**Solution**: Use correct metadata type

```cpp
marshal.imm = static_cast<uint32_t>(LIR::Metadata::MarshalType::StringToCString);
```

---

## Performance Optimization Tips

### 1. Reduce Type Dispatch Cases

```cpp
// Only include types actually used
switch (pc->result_type) {
    case Type::I32:
    case Type::I64:
    case Type::F64:
    case Type::Ptr:
        // Common types handled
        break;
}
```

### 2. Batch Similar Operations

```cpp
// Group memory operations together for cache locality
emit(MemoryLoad, ...);
emit(MemoryLoad, ...);
emit(MemoryLoad, ...);
```

### 3. Minimize Metadata Overhead

```cpp
// Reuse metadata encoding for similar types
marshal.imm = base_type | variant;
```

---

## Documentation Checklist

- [ ] Document new opcode usage
- [ ] Add examples for each pattern
- [ ] Update LIR generation guide
- [ ] Document metadata encoding
- [ ] Add troubleshooting guide

---

## Common Patterns Quick Reference

| Operation | Old Pattern | New Pattern | Metadata |
|-----------|------------|-------------|----------|
| Load | FFILoadInt32 | MemoryLoad | result_type |
| Store | FFIStoreInt32 | MemoryStore | type_a |
| Add Ptr | FFIAddPtr | PtrAdd | - |
| String→C | FFIToCString | Marshal | StringToCString |
| C→String | FFIFromCString | Unmarshal | CStringToString |
| Call Func | FFICCallFrame* | ForeignCall | CallingConvention |

---

## Success Indicators

- ✅ Memory load/store generation uses MemoryLoad/MemoryStore
- ✅ Pointer operations use Ptr* naming
- ✅ Marshaling uses Marshal/Unmarshal with metadata
- ✅ Foreign calls use single ForeignCall instruction
- ✅ All tests pass
- ✅ No compilation errors
- ✅ Smaller LIR code (fewer instructions)
- ✅ Build time similar or faster

---

## Next Steps After Phase 3

1. Run Phase 4 testing
2. Verify no performance regression
3. Document changes
4. Complete LIR redesign

---

*Quick start guide for Phase 3 implementation. Use in conjunction with PHASE_3_IMPLEMENTATION_PLAN.md for detailed guidance.*
