# LIR Redesign - Collapse Type-Specific Opcodes into Groups

## Problem Analysis

**Current LIR has 58 memory/FFI opcodes**:
- `FFILoadInt8`, `FFILoadInt16`, `FFILoadInt32`, `FFILoadInt64`
- `FFILoadUInt8`, `FFILoadUInt16`, `FFILoadUInt32`, `FFILoadUInt64`
- `FFILoadFloat`, `FFILoadDouble`, `FFILoadPtr`
- `FFIStoreInt8`, `FFIStoreInt16`, `FFIStoreInt32`, `FFIStoreInt64`
- `FFIStoreUInt8`, `FFIStoreUInt16`, `FFIStoreUInt32`, `FFIStoreUInt64`
- `FFIStoreFloat`, `FFIStoreDouble`, `FFIStorePtr`
- `FFIAlloc`, `FFIFree`, `FFIRealloc`
- `FFIMemcpy`, `FFIMemset`, `FFIMemcmp`
- `FFIAddPtr`, `FFISubPtr`, `FFIPtrDiff`, `FFIAlignPtr`, `FFIIsAligned`
- `FFILibraryLoad`, `FFILibraryUnload`, `FFILibraryGetSymbol`
- `ForeignCall`, `FFICallPtr0-5`
- `FFICCallFrame*`, `FFIVMSave/Restore`, etc.

**Root Cause**: Type information encoded in opcode name instead of in type metadata.

**Solution**: Use `result_type`, `type_a`, `type_b`, `imm` fields that already exist.

---

## Proposed Redesign

### Group 1: Memory Operations (8 opcodes)

Replace 22 type-specific opcodes with 4 generic ones:

```cpp
enum class LIR_Op : uint8_t {
    // Memory Operations (generic, type comes from result_type/type_a)
    MemoryLoad,         // dst = *(ptr<type_a>)
    MemoryStore,        // *(ptr<result_type>) = value
    MemoryCopy,         // memcpy(dst, src, size)
    MemoryFill,         // memset(dst, value, size)
    MemoryCompare,      // result = memcmp(lhs, rhs, size)
    MemoryAlloc,        // dst = malloc(size)
    MemoryFree,         // free(ptr)
    MemoryResize,       // dst = realloc(ptr, size)
};
```

**Usage Examples**:
```cpp
// Old: FFILoadInt32 r0, r1
// New: MemoryLoad r0, r1, result_type=I64

// Old: FFIStoreInt32 r0, r1
// New: MemoryStore r0, r1, result_type=I32

// Old: FFIMemcpy r0, r1, r2
// New: MemoryCopy r0, r1, r2

// Type dispatch in VM:
if (result_type == Type::I32) { /* i32 */ }
else if (result_type == Type::F64) { /* f64 */ }
```

**Implementation**:
```cpp
// In register.cpp:
void RegisterVM::execute_memory_load(const LIR::LIR_Inst* pc) {
    // Type dispatch using pc->result_type
    switch (pc->result_type) {
        case Type::I32:
            registers[pc->dst] = BOX_INT(*(int32_t*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::I64:
            registers[pc->dst] = BOX_INT(*(int64_t*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::F64:
            registers[pc->dst] = make_float(*(double*)UNBOX_PTR(registers[pc->a]));
            break;
        // ... etc
    }
}
```

### Group 2: Pointer Operations (5 opcodes)

Replace 5 opcodes (no change needed - already clean):

```cpp
enum class LIR_Op : uint8_t {
    // Pointer Operations
    PtrAdd,             // dst = ptr + offset
    PtrSub,             // dst = ptr - offset
    PtrDiff,            // dst = ptr1 - ptr2
    PtrAlign,           // dst = align_to(ptr, alignment)
    PtrIsAligned,       // dst = (ptr % alignment == 0) ? true : false
};
```

**No change needed** - these are already clean opcodes, just rename `FFI*` to `Ptr*`.

### Group 3: Marshaling Operations (5 opcodes)

Replace string/buffer/wrapper operations:

```cpp
enum class LIR_Op : uint8_t {
    // Marshaling - data conversions and views
    Marshal,            // dst = convert(src, from_type, to_type)
    Unmarshal,          // dst = convert(src, from_type, to_type)
    BufferView,         // dst = buffer_view(ptr, size)
    BufferCreate,       // dst = malloc(size) as buffer
    BufferResize,       // dst = realloc(buf, new_size)
};
```

**Usage Examples**:
```cpp
// Old: FFIFromCString r0, r1
// New: Marshal r0, r1, from_type=CString, to_type=String

// Old: FFIToCString r0, r1
// New: Unmarshal r0, r1, from_type=String, to_type=CString

// Type info in:
// - imm field: encoding of (from_type << 8 | to_type)
// - result_type: output type
// - type_a: input type
```

**Metadata Encoding**:
```cpp
// In imm field:
#define MAKE_MARSHAL_TYPE(from, to) ((from << 8) | to)

// Predefined conversions:
enum MarshalType : uint32_t {
    StringToCString = MAKE_MARSHAL_TYPE(String, CString),
    CStringToString = MAKE_MARSHAL_TYPE(CString, String),
    PtrToBuffer = MAKE_MARSHAL_TYPE(Ptr, Buffer),
    BufferToPtr = MAKE_MARSHAL_TYPE(Buffer, Ptr),
};
```

### Group 4: Dynamic Linking (3 opcodes)

These are legitimately distinct:

```cpp
enum class LIR_Op : uint8_t {
    // Dynamic Linking
    LibraryLoad,        // dst = dlopen(path)
    LibraryUnload,      // dlclose(handle)
    LibrarySymbol,      // dst = dlsym(handle, symbol)
};
```

**No changes** - these are clean and distinct operations at the C boundary.

### Group 5: Foreign Calls (2 opcodes)

Replace 15+ opcodes with 2 generic ones:

```cpp
enum class LIR_Op : uint8_t {
    // Foreign Function Calls
    ForeignCall,        // dst = func(args...) where func is in register
    ForeignCallDirect,  // dst = func(args...) where func is known at compile time
};
```

**Usage**:
```cpp
// Old: FFICallPtr5 r0, r1, r2, r3, r4, r5
// New: ForeignCall r0, [r1, r2, r3, r4, r5], calling_convention=SystemV_x64

// Metadata:
// - call_args: vector of argument registers
// - call_arg_types: vector of argument types
// - result_type: return type
// - imm: calling convention (platform-specific)

// No "FFICCallFrame*" opcodes - VM handles frame setup internally
// No "FFIVMSave/Restore" - VM manages state
// No "FFICCallExecute" - just ForeignCall with args
```

**Callback Support**:
```cpp
// Add only:
CallbackCreate,     // id = create_callback(func_ptr)
CallbackDestroy,    // destroy_callback(id)

// Not:
FFIRegisterCallback, FFIUnregisterCallback, FFIGetCallbackPtr
// These become implementation details
```

---

## Revised Complete LIR_Op Enum

```cpp
enum class LIR_Op : uint8_t {
    // === Core Operations (existing) ===
    Mov, LoadConst, Add, Sub, Mul, Div, Mod, Neg, And, Or, Xor,
    CmpEQ, CmpNEQ, CmpLT, CmpLE, CmpGT, CmpGE, StringIndex,
    Jump, JumpIfFalse, JumpIf, Label,
    Call, CallVoid, CallIndirect, CallBuiltin, CallVariadic,
    Return, FuncDef, Param, Ret, VaStart, VaArg, VaEnd, Copy,
    PrintInt, PrintUint, PrintFloat, PrintBool, PrintString,
    Nop, Cast, ToString, STR_CONCAT, STR_FORMAT,
    
    // === Decimal Operations (existing) ===
    DecAdd, DecSub, DecMul, DecDiv, DecMod, DecNeg, DecRescale,
    
    // === Error Handling (existing) ===
    ConstructError, ConstructOk, IsError, Unwrap, UnwrapOr,
    
    // === Type Operations (existing) ===
    MakeEnum, GetTag, GetPayload,
    
    // === Atomic Operations (existing) ===
    AtomicLoad, AtomicStore, AtomicFetchAdd,
    
    // === Async Operations (existing) ===
    Await, AsyncCall,
    
    // === Concurrency (existing) ===
    TaskContextAlloc, TaskContextInit, TaskGetState, TaskSetState, TaskSetField, TaskGetField,
    ChannelAlloc, ChannelPush, ChannelPop, ChannelHasData,
    ChannelSend, ChannelOffer, ChannelRecv, ChannelPoll, ChannelClose,
    SchedulerInit, SchedulerRun, SchedulerTick, SchedulerAddTask,
    GetTickCount, DelayUntil, ParallelInit, ParallelSync,
    
    // === Collections (existing) ===
    ListCreate, ListAppend, ListIndex, ListLen,
    DictCreate, DictSet, DictGet, DictHas, DictLen, DictItems,
    TupleCreate, TupleGet, TupleSet, TupleLen,
    
    // === Object-Oriented (existing) ===
    NewFrame, FrameGetField, FrameSetField, FrameGetFieldAtomic, FrameSetFieldAtomic,
    FrameFieldAtomicAdd, FrameFieldAtomicSub, FrameCallMethod, FrameCallInit, FrameCallDeinit,
    TraitCallMethod, MakeTraitObject,
    
    // === Module System (existing) ===
    ImportModule, ExportSymbol, BeginModule, EndModule, LoadGlobal, StoreGlobal,
    
    // === Shared Memory (existing) ===
    SharedCellAlloc, SharedCellLoad, SharedCellStore, SharedCellAdd, SharedCellSub,
    
    // === REDESIGNED: Memory Operations ===
    MemoryLoad,         // Type dispatch via result_type
    MemoryStore,        // Type dispatch via type_a
    MemoryCopy,         // memcpy(dst, src, size)
    MemoryFill,         // memset(dst, value, size)
    MemoryCompare,      // memcmp(lhs, rhs, size)
    MemoryAlloc,        // malloc(size)
    MemoryFree,         // free(ptr)
    MemoryResize,       // realloc(ptr, size)
    
    // === REDESIGNED: Pointer Operations ===
    PtrAdd,             // ptr + offset
    PtrSub,             // ptr - offset
    PtrDiff,            // ptr1 - ptr2
    PtrAlign,           // align_to(ptr, align)
    PtrIsAligned,       // (ptr % align == 0)
    
    // === REDESIGNED: Marshaling Operations ===
    Marshal,            // Type conversion (from_type, to_type in imm)
    Unmarshal,          // Reverse conversion
    BufferView,         // View pointer as buffer
    BufferCreate,       // Create buffer
    BufferResize,       // Resize buffer
    
    // === REDESIGNED: Dynamic Linking ===
    LibraryLoad,        // dlopen(path)
    LibraryUnload,      // dlclose(handle)
    LibrarySymbol,      // dlsym(handle, symbol)
    
    // === REDESIGNED: Foreign Calls ===
    ForeignCall,        // Indirect function call
    ForeignCallDirect,  // Direct function call (function_name in func_name field)
    
    // === REDESIGNED: Callbacks ===
    CallbackCreate,     // Create callback ID
    CallbackDestroy,    // Destroy callback
};
```

**Total: ~95 opcodes** (was ~150+ with all type-specific variants)
- **Removed**: 58+ type-specific `FFI*` opcodes
- **Added**: 4 generic memory ops, 5 generic marshaling ops, 2 generic call ops
- **Renamed**: `FFI*` → `Ptr*` / `Memory*`

---

## Implementation Changes Required

### 1. Update LIR_Inst to Support Type Dispatch

```cpp
struct LIR_Inst {
    LIR_Op op;
    Type result_type;      // Type for output
    Type type_a;           // Type for operand a
    Type type_b;           // Type for operand b
    Reg dst;
    Reg a;
    Reg b;
    Imm imm;               // Used for metadata (marshal types, etc)
    
    // Add these for better documentation:
    enum Metadata : uint32_t {
        MARSHAL_TYPE_BITS = 16,
        CALLING_CONVENTION_BITS = 8,
    };
};
```

### 2. Update VM Dispatchers

**Before**:
```cpp
case LIR::LIR_Op::FFILoadInt8:
    execute_ffi_load_int8(pc);
    break;
case LIR::LIR_Op::FFILoadInt16:
    execute_ffi_load_int16(pc);
    break;
// ... 10 more cases
```

**After**:
```cpp
case LIR::LIR_Op::MemoryLoad: {
    switch (pc->result_type) {
        case Type::I8:
            registers[pc->dst] = BOX_INT(*(int8_t*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::I16:
            registers[pc->dst] = BOX_INT(*(int16_t*)UNBOX_PTR(registers[pc->a]));
            break;
        // ... etc
    }
    break;
}
```

### 3. LIR Generation Changes

**Before**:
```cpp
if (element_type == Type::I32) {
    emit(LIR::LIR_Op::FFILoadInt32, dst_reg, src_reg);
} else if (element_type == Type::I64) {
    emit(LIR::LIR_Op::FFILoadInt64, dst_reg, src_reg);
} else if (element_type == Type::F64) {
    emit(LIR::LIR_Op::FFILoadDouble, dst_reg, src_reg);
}
```

**After**:
```cpp
LIR::LIR_Inst load;
load.op = LIR::LIR_Op::MemoryLoad;
load.result_type = element_type;  // Encodes the type
load.dst = dst_reg;
load.a = src_reg;
emit(load);
```

---

## Benefits of This Redesign

### 1. **Opcode Reduction** ✅
- 58 FFI opcodes → 15-20 operations
- Type information in metadata, not opcode names
- Cleaner enum, easier to maintain

### 2. **Better Naming** ✅
- `MemoryLoad` instead of `FFILoadInt32`, `FFILoadInt64`, etc.
- `PtrAdd` instead of `FFIAddPtr`
- `LibraryLoad` (actual boundary crossing)
- `ForeignCall` (actual boundary crossing)
- Clear separation: Memory operations vs. C boundary operations

### 3. **Easier to Extend** ✅
- Add new types? Just use different `result_type` value
- Add new calling conventions? Use different `imm` field
- Add new marshal types? Update encoding in `imm`
- No new opcodes needed

### 4. **More Idiomatic IR** ✅
- Matches how mature IRs work (LLVM, Cranelift)
- Type metadata separate from operation
- Generic operations with type dispatch
- Clean boundary between Limitly and C

### 5. **Better for Optimization** ✅
- Type dispatch in one place → easier to optimize
- Metadata-based operations → better for passes
- Cleaner structure for analysis

### 6. **Simpler Frontend** ✅
- LIR generator has fewer cases to handle
- Less boilerplate in type-specific dispatch

---

## Migration Path

### Phase 1: Update Enum
1. Replace all `FFI*` opcodes with `Memory*` and `Ptr*`
2. Add `Marshal`, `Unmarshal`, `BufferView`, `BufferCreate`, `BufferResize`
3. Add `ForeignCall`, `ForeignCallDirect`
4. Add `CallbackCreate`, `CallbackDestroy`
5. Remove frame/VM-state opcodes (implementation detail)

### Phase 2: Update VM Dispatchers
1. Consolidate 22 load opcodes into `MemoryLoad` with type dispatch
2. Consolidate 22 store opcodes into `MemoryStore` with type dispatch
3. Update `execute_memory()` to handle type dispatch
4. Update `execute_construction()` for marshaling
5. Simplify `execute_ffi()` to only true boundary crossing

### Phase 3: Update LIR Generation
1. Use `result_type` field instead of type-specific opcodes
2. Use `imm` field for metadata (marshal types, calling conventions)
3. Remove boilerplate type checking in generator

### Phase 4: Testing
1. Verify all existing tests still pass
2. Check that type dispatch works correctly
3. Validate marshaling operations
4. Test foreign calls with different conventions

---

## Summary

**Current LIR**: 150+ opcodes, many type-specific, `FFI` prefix confusing
**Proposed LIR**: ~95 opcodes, generic operations, metadata-based types

**Key Changes**:
1. `MemoryLoad`/`MemoryStore` replace 22 type-specific opcodes
2. `PtrAdd`/`PtrSub` rename (no logic change)
3. `Marshal`/`Unmarshal` for data conversions
4. `ForeignCall` (2 opcodes) instead of 15+ call-related opcodes
5. Remove frame management opcodes (implementation detail)
6. Remove VM state management opcodes (implementation detail)

**Result**: Cleaner IR that better represents intent, easier to optimize, more maintainable, more extensible.

