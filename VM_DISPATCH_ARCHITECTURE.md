# VM Dispatch Architecture - Quick Reference

## Three-Tier Execution Model

### Tier 1: Intrinsics (Fundamental Operations)
**Dispatcher**: `execute_memory()` in `src/backend/vm/ops/memory.cpp`

Operations that every runtime needs:
- Memory allocation/deallocation
- Memory operations (copy, fill, compare)
- Pointer arithmetic
- Type-specific load/store

**LIR Opcodes Handled**:
- `MemoryAlloc`, `MemoryFree`, `MemoryResize`
- `MemoryLoad`, `MemoryStore`
- `FFIMemcpy`, `FFIMemset`, `FFIMemcmp`
- `FFIAddPtr`, `FFISubPtr`, `FFIPtrDiff`, `FFIAlignPtr`, `FFIIsAligned`
- `FFILoadInt8/16/32/64`, `FFILoadUInt8/16/32/64`, `FFILoadFloat`, `FFILoadDouble`, `FFILoadPtr`
- `FFIStoreInt8/16/32/64`, `FFIStoreUInt8/16/32/64`, `FFIStoreFloat`, `FFIStoreDouble`, `FFIStorePtr`

**Function Pattern**: `execute_memory_*(const LIR::LIR_Inst* pc)`

---

### Tier 2: Construction (Data Structure Creation)
**Dispatcher**: `execute_construction()` in `src/backend/vm/ops/construction.cpp`

Operations for creating/viewing data structures:
- String conversions
- Buffer operations
- Type wrappers

**LIR Opcodes Handled**:
- `FFIFromCString`, `FFIToCString`, `FFIFreeCString`
- `FFIBufferAlloc`, `FFIBufferFromPtr`, `FFIBufferFree`, `FFIBufferResize`, `FFIBufferRead`, `FFIBufferWrite`
- `FFIBufferSize`, `FFIBufferCapacity`, `FFIBufferAsPtr`
- `FFICStringFromPtr`, `FFICStringPtr`

**Function Pattern**: `execute_construct_*(const LIR::LIR_Inst* pc)`

---

### Tier 3: External C Interop (Boundary Layer)
**Dispatcher**: `execute_ffi()` in `src/backend/vm/ops/ffi.cpp`

Operations for calling external C code:
- Library loading/unloading
- Symbol resolution
- Function calling
- Callback management

**LIR Opcodes Handled**:
- `FFILibraryLoad`, `FFILibraryUnload`, `FFILibraryGetSymbol`
- `ForeignCall`, `FFICallPtr`, `FFICallPtr0-5`
- `FFIRegisterCallback`, `FFIUnregisterCallback`, `FFIGetCallbackPtr`
- `FFICCallFrameCreate/Destroy/SetReg/GetReg/SetStackArg/GetStackArg`
- `FFIVMSave`, `FFIVMRestore`, `FFICCallExecute`
- `FFICalcStructLayout`, `FFIGetABIInfo`

**Function Pattern**: `execute_extern_*(const LIR::LIR_Inst* pc)`

---

## Integration Point

### Where to Add Dispatch Routing

Update the main instruction dispatcher (likely in `src/backend/vm/register.cpp`):

```cpp
void RegisterVM::execute_instruction(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // Core operations
        case LIR::LIR_Op::Add:
        case LIR::LIR_Op::Sub:
        case LIR::LIR_Op::Mul:
            execute_arithmetic(pc);
            break;
        
        case LIR::LIR_Op::CmpEQ:
        case LIR::LIR_Op::CmpLT:
            execute_comparison(pc);
            break;
        
        // **NEW**: Intrinsics tier
        case LIR::LIR_Op::MemoryAlloc:
        case LIR::LIR_Op::MemoryFree:
        case LIR::LIR_Op::MemoryLoad:
        case LIR::LIR_Op::MemoryStore:
        case LIR::LIR_Op::FFIAddPtr:
        case LIR::LIR_Op::FFIMemcpy:
        case LIR::LIR_Op::FFILoadInt8:
        case LIR::LIR_Op::FFIStoreInt8:
            execute_memory(pc);
            break;
        
        // **NEW**: Construction tier
        case LIR::LIR_Op::FFIToCString:
        case LIR::LIR_Op::FFIFromCString:
        case LIR::LIR_Op::FFIBufferAlloc:
        case LIR::LIR_Op::FFICStringFromPtr:
            execute_construction(pc);
            break;
        
        // **UPDATED**: FFI tier (now only true interop)
        case LIR::LIR_Op::FFILibraryLoad:
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::FFIRegisterCallback:
            execute_ffi(pc);
            break;
        
        // Existing operations
        case LIR::LIR_Op::ListCreate:
            execute_collections(pc);
            break;
        
        // ... etc
    }
}
```

---

## File Organization

```
src/backend/vm/ops/
├── arithmetic.cpp          (existing)
├── comparison.cpp          (existing)
├── collections.cpp         (existing)
├── frames.cpp              (existing)
├── control_flow.cpp        (existing)
├── io.cpp                  (existing)
├── bitwise.cpp             (existing)
├── concurrency.cpp         (existing)
├── modules.cpp             (existing)
├── objects.cpp             (existing)
├── vm_strings.cpp          (existing)
├── vm_calls.cpp            (existing)
├── vm_cast.cpp             (existing)
├── memory.cpp              (NEW - intrinsics)
├── construction.cpp        (NEW - data construction)
└── ffi.cpp                 (REFACTORED - true interop only)
```

---

## Migration Guide

### For Adding New Memory Operations
1. Add LIR opcode to `src/lir/lir.hh` if needed
2. Implement in `src/backend/vm/ops/memory.cpp`
3. Add case to `execute_memory()` dispatcher
4. Declare in `register.hh` (private helper method)

### For Adding New Data Constructions
1. Add LIR opcode to `src/lir/lir.hh` if needed
2. Implement in `src/backend/vm/ops/construction.cpp`
3. Add case to `execute_construction()` dispatcher
4. Declare in `register.hh` (private helper method)

### For Adding New External Interop
1. Add LIR opcode to `src/lir/lir.hh` if needed
2. Implement in `src/backend/vm/ops/ffi.cpp`
3. Add case to `execute_ffi()` dispatcher
4. Declare in `register.hh` (private helper method)

---

## Operation Counts

| Layer | Dispatcher | Operations | File Size |
|-------|-----------|-----------|-----------|
| Intrinsics | `execute_memory()` | 33 | 450 lines |
| Construction | `execute_construction()` | 10 | 200 lines |
| Extern | `execute_ffi()` | 15 | 250 lines |
| **Total** | **3 dispatchers** | **58** | **~900 lines** |

---

## Design Principles

1. **Single Responsibility**: Each dispatcher handles one layer
2. **Clear Boundaries**: Three tiers clearly separated
3. **Intrinsics First**: Fundamental operations in intrinsics layer
4. **Data Construction**: Value system operations in construction layer
5. **External Only**: True C interop in FFI layer

---

## Testing Strategy

### Intrinsics Tier
- Test memory allocation/deallocation
- Test pointer arithmetic
- Test load/store for all types
- Test bulk operations (memcpy, memset, memcmp)

### Construction Tier
- Test string conversions
- Test buffer creation
- Test wrapper operations

### Extern Tier
- Test library loading
- Test symbol resolution
- Test callback registration
- Test function calling

---

## Notes

- All three dispatchers use same pattern: dispatcher delegates to specific functions
- No new LIR instructions added - reuses existing opcodes
- Backward compatible - all operations still work
- Clear naming: `execute_memory_*`, `execute_construct_*`, `execute_extern_*`

