# Phase 3: LIR Generation Updates - Implementation Plan

## Executive Summary

**Goal**: Update LIR generation to use new generic memory operations with type dispatch instead of type-specific opcodes.

**Status**: Ready to implement

**Files to Update**:
1. `src/lir/generator/core.cpp` - Foreign call generation
2. `src/lir/generator/expressions.cpp` - Expression generation, memory operations
3. `src/lir/generator/statements.cpp` - Statement generation
4. Build system: Makefile

**Effort**: ~2-3 hours

---

## Phase 3A: Memory Load/Store Generation

### Current Implementation Pattern

The current LIR generator has patterns like:

```cpp
// src/lir/generator/expressions.cpp (hypothetical)
if (element_type == Type::I32) {
    LIR::LIR_Inst load(LIR::LIR_Op::FFILoadInt32, dst_reg, src_reg);
    function.add_instruction(load);
} else if (element_type == Type::I64) {
    LIR::LIR_Inst load(LIR::LIR_Op::FFILoadInt64, dst_reg, src_reg);
    function.add_instruction(load);
} else if (element_type == Type::F64) {
    LIR::LIR_Inst load(LIR::LIR_Op::FFILoadDouble, dst_reg, src_reg);
    function.add_instruction(load);
}
// ... 8+ more type cases
```

### New Implementation Pattern

Replace all that boilerplate with:

```cpp
// Simple: one instruction, type in metadata
LIR::LIR_Inst load;
load.op = LIR::LIR_Op::MemoryLoad;
load.result_type = element_type;  // Type dispatch happens in VM
load.dst = dst_reg;
load.a = src_reg;
function.add_instruction(load);
```

### Search Pattern to Find All Occurrences

Search for these patterns in LIR generator files:

```
FFILoadInt8|FFILoadInt16|FFILoadInt32|FFILoadInt64|FFILoadUInt8|
FFILoadUInt16|FFILoadUInt32|FFILoadUInt64|FFILoadFloat|FFILoadDouble|FFILoadPtr|
FFIStoreInt8|FFIStoreInt16|FFIStoreInt32|FFIStoreInt64|FFIStoreUInt8|
FFIStoreUInt16|FFIStoreUInt32|FFIStoreUInt64|FFIStoreFloat|FFIStoreDouble|FFIStorePtr
```

---

## Phase 3B: Pointer Operation Generation

### Current Pattern

```cpp
LIR::LIR_Inst add_ptr(LIR::LIR_Op::FFIAddPtr, dst_reg, src_reg, offset_reg);
LIR::LIR_Inst sub_ptr(LIR::LIR_Op::FFISubPtr, dst_reg, src_reg, offset_reg);
LIR::LIR_Inst ptr_diff(LIR::LIR_Op::FFIPtrDiff, dst_reg, ptr1_reg, ptr2_reg);
```

### New Pattern

```cpp
LIR::LIR_Inst add_ptr;
add_ptr.op = LIR::LIR_Op::PtrAdd;  // Renamed from FFIAddPtr
add_ptr.dst = dst_reg;
add_ptr.a = src_reg;
add_ptr.b = offset_reg;
function.add_instruction(add_ptr);
```

### Changes
- Rename `FFIAddPtr` → `PtrAdd`
- Rename `FFISubPtr` → `PtrSub`
- Rename `FFIPtrDiff` → `PtrDiff`
- Rename `FFIAlignPtr` → `PtrAlign`
- Rename `FFIIsAligned` → `PtrIsAligned`

These are pure renames with no logic change.

---

## Phase 3C: String/Buffer/Marshaling Generation

### Current Pattern (FFI Operations)

```cpp
// String to CString
LIR::LIR_Inst to_cstr(LIR::LIR_Op::FFIToCString, dst_reg, str_reg);
function.add_instruction(to_cstr);

// Buffer allocation
LIR::LIR_Inst buf_alloc(LIR::LIR_Op::FFIBufferAlloc, dst_reg, size_reg);
function.add_instruction(buf_alloc);
```

### New Pattern (Marshal Operations)

```cpp
// String to CString
LIR::LIR_Inst marshal;
marshal.op = LIR::LIR_Op::Marshal;
marshal.result_type = Type::Ptr;  // Result is a pointer
marshal.type_a = Type::String;    // Input is a string
marshal.dst = dst_reg;
marshal.a = str_reg;
marshal.imm = static_cast<uint32_t>(LIR::Metadata::MarshalType::StringToCString);
function.add_instruction(marshal);

// Buffer allocation
LIR::LIR_Inst buf_create;
buf_create.op = LIR::LIR_Op::BufferCreate;
buf_create.dst = dst_reg;
buf_create.a = size_reg;
function.add_instruction(buf_create);
```

### Search Patterns

Find and replace:
- `FFIToCString` → Use `Marshal` with `MarshalType::StringToCString`
- `FFIFromCString` → Use `Marshal` with `MarshalType::CStringToString`
- `FFIBufferAlloc` → Use `BufferCreate`
- `FFIBufferFromPtr` → Use `BufferView`

---

## Phase 3D: Foreign Call Generation

### Current Pattern

```cpp
// Build frame
LIR::LIR_Inst frame_create(LIR::LIR_Op::FFICCallFrameCreate, frame_id, arg_count, stack_size);
function.add_instruction(frame_create);

// Set frame registers for each argument
for (size_t i = 0; i < args.size(); i++) {
    LIR::LIR_Inst set_reg(LIR::LIR_Op::FFICCallFrameSetReg, frame_id, i_reg, arg_regs[i]);
    function.add_instruction(set_reg);
}

// Execute call
LIR::LIR_Inst exec(LIR::LIR_Op::FFICCallExecute, dst_reg, func_ptr_reg);
function.add_instruction(exec);
```

### New Pattern

```cpp
// Direct call
LIR::LIR_Inst call;
call.op = LIR::LIR_Op::ForeignCall;
call.result_type = return_type;
call.dst = dst_reg;
call.call_args = {func_ptr_reg, arg1_reg, arg2_reg, ...};
call.call_arg_types = {Type::Ptr, Type::I64, Type::I64, ...};
call.imm = static_cast<uint32_t>(LIR::CallingConvention::SystemV_x64);
function.add_instruction(call);
```

### Impact
- **Before**: 3 + N instructions (frame create, N register sets, execute)
- **After**: 1 instruction
- **Reduction**: ~80% fewer instructions

### Search Pattern
- `FFICCallFrameCreate`, `FFICCallFrameSetReg`, `FFICCallExecute` → Replace with single `ForeignCall`

---

## Implementation Steps

### Step 1: Search and Document

Create a complete list of all locations where old opcodes are used:

```bash
grep -r "FFILoadInt\|FFILoadUInt\|FFILoadFloat\|FFILoadDouble\|FFILoadPtr" src/lir/generator/ | wc -l
grep -r "FFIStoreInt\|FFIStoreUInt\|FFIStoreFloat\|FFIStoreDouble\|FFIStorePtr" src/lir/generator/ | wc -l
grep -r "FFIAddPtr\|FFISubPtr\|FFIPtrDiff\|FFIAlignPtr\|FFIIsAligned" src/lir/generator/ | wc -l
grep -r "FFIToCString\|FFIFromCString\|FFIBufferAlloc" src/lir/generator/ | wc -l
grep -r "FFICCallFrame\|FFICCallExecute" src/lir/generator/ | wc -l
```

### Step 2: Update Memory Operations

In `src/lir/generator/expressions.cpp`:

1. Find all memory load generation code
2. Replace with generic `MemoryLoad` using `result_type`
3. Find all memory store generation code
4. Replace with generic `MemoryStore` using `type_a`

**Before**: 22 different opcodes
**After**: 2 opcodes with type dispatch

### Step 3: Update Pointer Operations

In `src/lir/generator/*.cpp`:

1. Find all pointer operation generation code
2. Rename opcodes (pure renames):
   - `FFIAddPtr` → `PtrAdd`
   - `FFISubPtr` → `PtrSub`
   - `FFIPtrDiff` → `PtrDiff`
   - `FFIAlignPtr` → `PtrAlign`
   - `FFIIsAligned` → `PtrIsAligned`

**Impact**: No logic changes, just opcode names

### Step 4: Update String/Buffer Generation

In `src/lir/generator/core.cpp` and `src/lir/generator/expressions.cpp`:

1. Find string conversion generation (FFIToCString, FFIFromCString)
2. Replace with `Marshal`/`Unmarshal` using metadata
3. Find buffer operations (FFIBufferAlloc, FFIBufferFromPtr)
4. Replace with `BufferCreate`, `BufferView`

**Pattern**: Replace opcode, add `imm` field with marshal type

### Step 5: Update Foreign Call Generation

In `src/lir/generator/core.cpp`:

1. Find FFICCallFrame creation code
2. Replace entire sequence with single `ForeignCall`
3. Set `call_args`, `call_arg_types`, `imm` fields
4. Remove frame management code

**Reduction**: 80% fewer instructions

### Step 6: Update Type Metadata

In `src/lir/lir.hh`, ensure metadata encoding is defined:

```cpp
namespace LIR {
    namespace Metadata {
        enum class MarshalType : uint16_t {
            StringToCString  = 0,
            CStringToString  = 1,
            // ...
        };
        
        inline MarshalType extract_marshal_type(uint32_t imm) {
            return static_cast<MarshalType>(imm & 0xFFFF);
        }
    }
}
```

### Step 7: Verify Build

```bash
make clean
make
```

### Step 8: Run Tests

```bash
./tests/run_tests.bat
```

---

## Files to Modify

### Primary Changes

| File | Changes | Lines |
|------|---------|-------|
| `src/lir/generator/core.cpp` | Foreign call generation | ~50-100 |
| `src/lir/generator/expressions.cpp` | Memory ops, string ops | ~100-150 |
| `src/lir/generator/statements.cpp` | Minor cleanup | ~10-20 |
| `src/lir/lir.hh` | Metadata encoding (if needed) | ~10-20 |

### Secondary Changes

| File | Changes | Impact |
|------|---------|--------|
| `Makefile` | No changes needed | - |
| VM operations | No changes (Phase 2 done) | - |
| Type checker | No changes | - |
| Parser | No changes | - |

---

## Backward Compatibility

All changes are internal to the LIR generator:
- No language syntax changes
- No type system changes
- No VM operation changes (Phase 2 already updated)
- No public API changes

Old FFI opcodes can still be supported in the VM for backward compatibility during transition.

---

## Testing Strategy

### Unit Tests

No new tests needed - existing tests should pass:
- All language features remain the same
- Only IR representation changes internally
- Type system unchanged

### Regression Tests

Run full test suite to ensure no regressions:

```bash
./tests/run_tests.bat              # Silent mode
./tests/run_tests_verbose.bat      # Verbose mode
```

### Performance Tests

Verify IR generation performance:
- Should be slightly faster (fewer type checks)
- Should produce smaller LIR (fewer instructions)
- No runtime performance change

### Verification Checklist

- [ ] All memory load/store operations generate `MemoryLoad`/`MemoryStore`
- [ ] All pointer operations renamed consistently
- [ ] All string/buffer operations use `Marshal`
- [ ] All foreign calls use single `ForeignCall` operation
- [ ] Build completes without errors
- [ ] All tests pass
- [ ] No performance regression
- [ ] LIR size reduced

---

## Success Criteria

✓ All FFI opcodes removed from LIR generation
✓ All memory operations use type dispatch
✓ All pointer operations renamed
✓ All marshaling operations use metadata
✓ All foreign calls use single opcode
✓ 50%+ reduction in FFI opcode generation
✓ Build succeeds
✓ All tests pass
✓ No breaking changes to language

---

## Risk Assessment

### Low Risk ✅
- Changes isolated to LIR generator
- No language changes
- VM already updated
- Backward compatible during transition

### Mitigations
- Run full test suite after changes
- Keep git tags before/after Phase 3
- Easy to revert individual generator changes

---

## Timeline

| Step | Duration | Checkpoint |
|------|----------|------------|
| 1. Search & Document | 30 min | List all locations |
| 2. Memory Ops | 45 min | 22 → 2 opcodes |
| 3. Pointer Ops | 15 min | Rename only |
| 4. String/Buffer | 30 min | Use Marshal |
| 5. Foreign Calls | 45 min | 80% reduction |
| 6. Metadata | 15 min | Type encoding |
| 7. Build & Test | 30 min | Verify all pass |
| **Total** | **3.25 hours** | |

---

## Implementation Order

1. **Memory Operations** (highest impact)
2. **Pointer Operations** (simple renames)
3. **Foreign Calls** (largest reduction)
4. **String/Buffer Operations** (depends on Marshal implementation)
5. **Metadata** (supporting infrastructure)
6. **Build & Verification**

---

## Notes

- Memory operations have highest impact (22 opcodes → 2)
- Pointer operations are pure renames
- Foreign calls have highest reduction (80%)
- All changes are additive - no removing existing functionality
- VM already handles new operations (Phase 2 complete)

---

## Next Phase

After Phase 3 completion:
- **Phase 4**: Testing & Validation
  - Run full test suite
  - Performance validation
  - Documentation updates
  - Complete LIR redesign implementation

---

## Conclusion

Phase 3 is well-defined and ready for implementation. The focus is on updating LIR generation to use new generic operations with type dispatch, reducing FFI opcodes by 50%+.

**Success metrics**: All tests pass, cleaner LIR generation, no performance regression.
