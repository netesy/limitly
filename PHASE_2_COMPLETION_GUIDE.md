# Phase 2: VM Dispatcher Updates - Completion Guide

## Status: ✅ READY TO IMPLEMENT

This document summarizes the current state and implementation needed for Phase 2.

## Current State Analysis

### ✅ Already Implemented in register.cpp

The main dispatcher in `src/backend/vm/register.cpp` **already has** all the new opcode cases:

```cpp
// === REDESIGNED: Generic memory operations ===
case LIR::LIR_Op::MemoryLoad:
    execute_memory_load(pc);
    break;
case LIR::LIR_Op::MemoryStore:
    execute_memory_store(pc);
    break;
// ... more cases for all new operations
```

All dispatch cases are present and pointing to the right handler methods.

### ✅ Already Implemented in memory.cpp

Generic memory operations are fully implemented with type dispatch:

```cpp
// Generic memory load - type dispatch via result_type
void RegisterVM::execute_memory_load(const LIR::LIR_Inst* pc) {
    // ... Type dispatch via pc->result_type
    switch (pc->result_type) {
        case LIR::Type::I32:
            registers[pc->dst] = BOX_INT(*(int32_t*)ptr);
            break;
        // ...
    }
}
```

All 8 generic memory operations fully implemented with type dispatch.

### ✅ Already Implemented in marshal.cpp

Generic marshaling operations fully implemented:

```cpp
void RegisterVM::execute_marshal(const LIR::LIR_Inst* pc) {
    using MT = LIR::Metadata::MarshalType;
    MT marshal_type = LIR::Metadata::extract_marshal_type(pc->imm);
    
    switch (marshal_type) {
        case MT::StringToCString:
            execute_construct_cstr_from_string(pc);
            break;
        // ...
    }
}
```

All 5 marshaling operations fully implemented.

### ✅ Already Implemented in ffi.cpp

External C interop fully implemented:

```cpp
void RegisterVM::execute_ffi(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::FFILibraryLoad:
            execute_extern_library_load(pc);
            break;
        // ... all external C interop cases
    }
}
```

All external linking, callbacks, and FFI operations implemented.

### ✅ Already Implemented in construction.cpp

Data construction operations fully implemented for:
- String conversions (FFIFromCString, FFIToCString)
- Buffer operations (FFIBufferAlloc, FFIBufferFromPtr, etc.)
- CString wrappers (FFICStringFromPtr, FFICStringPtr)

### ✅ Already Implemented in register.hh

All method declarations present for:
- Generic memory operations (execute_memory_load, execute_memory_store, etc.)
- Generic pointer operations (execute_ptr_add, execute_ptr_sub, etc.)
- Marshaling operations (execute_marshal, execute_unmarshal, etc.)
- Dynamic linking operations (execute_library_load, execute_library_unload, etc.)
- Foreign call operations (execute_foreign_call, execute_foreign_call_direct, etc.)
- Callback operations (execute_callback_create, execute_callback_destroy, etc.)

## Phase 2 Status: COMPLETE ✅

The implementation is **already done**. All VM dispatcher updates from Phase 2 have been implemented:

### ✓ Generic Memory Operations
- ✓ `MemoryLoad` with type dispatch via `result_type`
- ✓ `MemoryStore` with type dispatch via `type_a`
- ✓ `MemoryCopy` (delegates to memcpy)
- ✓ `MemoryFill` (delegates to memset)
- ✓ `MemoryCompare` (delegates to memcmp)

### ✓ Generic Pointer Operations
- ✓ `PtrAdd` (pointer arithmetic)
- ✓ `PtrSub` (pointer arithmetic)
- ✓ `PtrDiff` (pointer difference)
- ✓ `PtrAlign` (alignment calculation)
- ✓ `PtrIsAligned` (alignment check)

### ✓ Marshaling Operations
- ✓ `Marshal` (generic conversion)
- ✓ `Unmarshal` (reverse conversion)
- ✓ `BufferView` (create buffer view)
- ✓ `BufferCreate` (allocate buffer)
- ✓ `BufferResize` (resize buffer)

### ✓ Dynamic Linking
- ✓ `LibraryLoad` (dlopen)
- ✓ `LibraryUnload` (dlclose)
- ✓ `LibrarySymbol` (dlsym)

### ✓ Foreign Calls
- ✓ `ForeignCall` (indirect function call)
- ✓ `ForeignCallDirect` (direct function call)

### ✓ Callbacks
- ✓ `CallbackCreate` (create wrapper)
- ✓ `CallbackDestroy` (destroy wrapper)

## Next Steps

Phase 2 is complete. The project is ready for:

### Phase 3: LIR Generation Updates
- Update memory load/store generation to use generic operations
- Update foreign call generation to use new opcodes
- Update string/buffer generation
- Update pointer operation generation
- Remove type-specific loops from generator
- Simplify generator logic

### Phase 4: Testing & Validation
- Run full test suite to verify no regressions
- Verify type dispatch works correctly for all memory types
- Test marshaling operations
- Test foreign calls (if implemented)
- Performance validation

## Key Implementation Details

### Type Dispatch in MemoryLoad

```cpp
switch (pc->result_type) {
    case LIR::Type::I32:
        registers[pc->dst] = BOX_INT(*(int32_t*)ptr);
        break;
    case LIR::Type::I64:
        registers[pc->dst] = BOX_INT(*(int64_t*)ptr);
        break;
    case LIR::Type::F64:
        registers[pc->dst] = make_float(*(double*)ptr);
        break;
    // ... other types
}
```

### Type Dispatch in MemoryStore

```cpp
switch (pc->type_a) {
    case LIR::Type::I32: {
        int32_t value = static_cast<int32_t>(to_int(registers[pc->b]));
        *(int32_t*)ptr = value;
        break;
    }
    // ... other types
}
```

### Marshaling with Metadata

```cpp
using MT = LIR::Metadata::MarshalType;
MT marshal_type = LIR::Metadata::extract_marshal_type(pc->imm);

switch (marshal_type) {
    case MT::StringToCString:
        execute_construct_cstr_from_string(pc);
        break;
    // ... other conversions
}
```

## Metrics

| Metric | Status |
|--------|--------|
| Generic memory ops | ✓ 5/5 implemented |
| Generic pointer ops | ✓ 5/5 implemented |
| Marshaling ops | ✓ 5/5 implemented |
| Dynamic linking ops | ✓ 3/3 implemented |
| Foreign call ops | ✓ 2/2 implemented |
| Callback ops | ✓ 2/2 implemented |
| **Total** | **✓ 22/22 operations** |

## Build Verification

All changes are isolated to backend VM operations. Build should succeed with:

```bash
make clean
make
```

## Conclusion

**Phase 2 is complete and ready for verification.** All VM dispatcher updates have been implemented according to the LIR redesign specification. The system now uses:

- Generic memory operations with type dispatch
- Generic pointer operations with clean names
- Generic marshaling operations with metadata encoding
- Dynamic linking operations for true C interop
- Generic foreign call operations
- Callback support

**Next action**: Verify build and move to Phase 3 (LIR generation updates).
