# LIR Redesign - Implementation Plan

## Executive Summary

**Goal**: Collapse 58+ type-specific FFI opcodes into 15-20 generic operations with metadata-based type dispatch.

**Benefit**: Cleaner IR, easier to maintain, faster to extend, better aligned with compiler design principles.

**Effort**: ~3-4 days for complete implementation and testing.

**Risk**: Medium (touches core IR but well-isolated changes).

---

## Phase 1: Enum Redesign (1 day)

### 1.1 Update LIR_Op Enum

**File**: `src/lir/lir.hh`

**Changes**:
```cpp
enum class LIR_Op : uint8_t {
    // ... existing opcodes unchanged ...
    
    // REMOVE: All 58 type-specific FFI opcodes
    // - FFILoadInt8/16/32/64, FFILoadUInt8/16/32/64, FFILoadFloat, FFILoadDouble, FFILoadPtr
    // - FFIStoreInt8/16/32/64, FFIStoreUInt8/16/32/64, FFIStoreFloat, FFIStoreDouble, FFIStorePtr
    // - FFIAlloc, FFIFree, FFIRealloc, FFIMemcpy, FFIMemset, FFIMemcmp
    // - FFIAddPtr, FFISubPtr, FFIPtrDiff, FFIAlignPtr, FFIIsAligned
    // - FFIToCString, FFIFromCString, FFIFreeCString
    // - FFICStringPtr, FFICStringFromPtr
    // - FFIBufferAlloc, FFIBufferFromPtr, FFIBufferFree, FFIBufferResize, FFIBufferRead, FFIBufferWrite
    // - FFIBufferSize, FFIBufferCapacity, FFIBufferAsPtr
    // - FFICallPtr, FFICallPtr0-5, FFICCallFrame*, FFIVMSave/Restore, FFICCallExecute
    
    // ADD: Generic Memory Operations
    MemoryLoad,         // Load value from memory (type from result_type)
    MemoryStore,        // Store value to memory (type from type_a)
    MemoryCopy,         // memcpy(dst, src, size)
    MemoryFill,         // memset(dst, value, size)
    MemoryCompare,      // int = memcmp(lhs, rhs, size)
    MemoryAlloc,        // ptr = malloc(size)
    MemoryFree,         // free(ptr)
    MemoryResize,       // ptr = realloc(ptr, size)
    
    // ADD: Generic Pointer Operations (rename from FFI*)
    PtrAdd,             // ptr + offset
    PtrSub,             // ptr - offset
    PtrDiff,            // ptr1 - ptr2
    PtrAlign,           // align_to(ptr, alignment)
    PtrIsAligned,       // (ptr % alignment == 0) ? true : false
    
    // ADD: Marshaling Operations (replace FFICString*, FFIBuffer*)
    Marshal,            // Convert value (from_type, to_type in imm)
    Unmarshal,          // Reverse convert (from_type, to_type in imm)
    BufferView,         // Create buffer view of memory
    BufferCreate,       // Create new buffer
    BufferResize,       // Resize buffer
    
    // KEEP: Dynamic Linking (already clean)
    LibraryLoad,        // dlopen(path)
    LibraryUnload,      // dlclose(handle)
    LibrarySymbol,      // dlsym(handle, symbol)
    
    // ADD: Generic Foreign Calls (replace FFICall*)
    ForeignCall,        // Call function at runtime
    ForeignCallDirect,  // Call known function
    
    // ADD: Callback Support (replace FFICallback*)
    CallbackCreate,     // Create callback wrapper
    CallbackDestroy,    // Destroy callback wrapper
    
    // REMOVE: Frame/VM management (implementation detail)
    // - FFICCallFrameCreate, FFICCallFrameDestroy, FFICCallFrameSetReg, FFICCallFrameGetReg
    // - FFICCallFrameSetStackArg, FFICCallFrameGetStackArg
    // - FFIVMSave, FFIVMRestore, FFICCallExecute
    // - FFICalcStructLayout, FFIGetABIInfo
};
```

**Verification**:
- [ ] Count opcodes: should be ~95 (was 150+)
- [ ] No duplicates
- [ ] All memory ops grouped
- [ ] All linking ops grouped
- [ ] All call ops grouped

### 1.2 Add Metadata Encoding

**File**: `src/lir/lir.hh`

**Add**:
```cpp
namespace LIR {
    // Marshal type encoding (16 bits each)
    enum class MarshalType : uint16_t {
        StringToCString  = 0,
        CStringToString  = 1,
        PtrToBuffer      = 2,
        BufferToPtr      = 3,
        // ... expand as needed
    };
    
    inline uint32_t make_marshal_imm(MarshalType type) {
        return static_cast<uint32_t>(type);
    }
    
    // Calling convention encoding (8 bits)
    enum class CallingConvention : uint8_t {
        SystemV_x64      = 0,    // System V AMD64 ABI
        Windows_x64      = 1,    // Windows x64 calling convention
        ARM64_EABI       = 2,    // ARM64 EABI
        Default          = SystemV_x64,
    };
}
```

**Usage**:
```cpp
// When generating MemoryLoad:
inst.op = LIR::LIR_Op::MemoryLoad;
inst.result_type = Type::I32;  // Type dispatch in VM
inst.dst = dst_reg;
inst.a = src_reg;

// When generating ForeignCall:
inst.op = LIR::LIR_Op::ForeignCall;
inst.imm = static_cast<uint32_t>(LIR::CallingConvention::SystemV_x64);
inst.call_args = {r1, r2, r3};
inst.call_arg_types = {Type::I64, Type::I64, Type::Ptr};
```

---

## Phase 2: VM Dispatcher Updates (1.5 days)

### 2.1 Update execute_memory()

**File**: `src/backend/vm/ops/memory.cpp`

**Changes**:

**Before** (current structure with 22 separate functions):
```cpp
case LIR::LIR_Op::FFILoadInt8:
    execute_memory_load_int8(pc);
    break;
case LIR::LIR_Op::FFILoadInt16:
    execute_memory_load_int16(pc);
    break;
// ... 20 more cases
```

**After** (single generic operation):
```cpp
case LIR::LIR_Op::MemoryLoad: {
    switch (pc->result_type) {
        case Type::I8:
            registers[pc->dst] = BOX_INT(*(int8_t*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::I16:
            registers[pc->dst] = BOX_INT(*(int16_t*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::I32:
            registers[pc->dst] = BOX_INT(*(int32_t*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::I64:
            registers[pc->dst] = BOX_INT(*(int64_t*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::F64:
            registers[pc->dst] = make_float(*(double*)UNBOX_PTR(registers[pc->a]));
            break;
        case Type::Ptr:
            registers[pc->dst] = BOX_PTR(*(void**)UNBOX_PTR(registers[pc->a]));
            break;
        default:
            registers[pc->dst] = VAL_NIL;
    }
    break;
}
```

**Remove**: All 44 old helper functions (execute_memory_load_*, execute_memory_store_*)

**Benefits**:
- Single case handles all 22 load types
- Type dispatch centralized
- Easier to add new types
- Better cache locality

### 2.2 Update execute_construction()

**File**: `src/backend/vm/ops/construction.cpp`

**Changes**:
```cpp
case LIR::LIR_Op::Marshal: {
    MarshalType marshal_type = static_cast<MarshalType>(pc->imm);
    switch (marshal_type) {
        case MarshalType::StringToCString:
            registers[pc->dst] = marshal_string_to_cstr(registers[pc->a]);
            break;
        case MarshalType::CStringToString:
            registers[pc->dst] = marshal_cstr_to_string(registers[pc->a]);
            break;
        // ... other conversions
    }
    break;
}

case LIR::LIR_Op::BufferView:
    registers[pc->dst] = create_buffer_view(
        UNBOX_PTR(registers[pc->a]),
        to_int(registers[pc->b])
    );
    break;

case LIR::LIR_Op::BufferCreate:
    registers[pc->dst] = create_buffer(to_int(registers[pc->a]));
    break;
```

**Remove**: All old FFIBuffer* and FFICString* cases

### 2.3 Update execute_ffi()

**File**: `src/backend/vm/ops/ffi.cpp`

**Changes**:
```cpp
case LIR::LIR_Op::ForeignCall: {
    void* func_ptr = UNBOX_PTR(registers[arg_reg(pc, 0, pc->a)]);
    if (!func_ptr) {
        registers[pc->dst] = VAL_NIL;
        break;
    }
    
    CallingConvention cc = static_cast<CallingConvention>(pc->imm);
    registers[pc->dst] = call_external_function(
        func_ptr,
        pc->call_args,
        pc->call_arg_types,
        registers,
        cc  // Platform-specific calling convention
    );
    break;
}

case LIR::LIR_Op::ForeignCallDirect: {
    // pc->func_name contains the function name
    // Look up or call directly
    registers[pc->dst] = call_external_function_direct(
        pc->func_name,
        pc->call_args,
        pc->call_arg_types,
        registers
    );
    break;
}

case LIR::LIR_Op::CallbackCreate:
    registers[pc->dst] = create_callback_wrapper(registers[pc->a]);
    break;

case LIR::LIR_Op::CallbackDestroy:
    destroy_callback_wrapper(to_int(registers[pc->a]));
    break;
```

**Remove**: All old FFICall*, FFICCallFrame*, FFIVMSave/Restore cases

---

## Phase 3: LIR Generation Updates (1 day)

### 3.1 Update Memory Load Generation

**File**: `src/lir/generator/expressions.cpp`

**Before**:
```cpp
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
```

**After**:
```cpp
LIR::LIR_Inst load;
load.op = LIR::LIR_Op::MemoryLoad;
load.result_type = element_type;  // Type in metadata
load.dst = dst_reg;
load.a = src_reg;
function.add_instruction(load);
```

**Changes**:
- Remove all type-specific load/store generation
- Use single `MemoryLoad`/`MemoryStore` with `result_type`
- Remove `type_a`/`type_b` checking loops
- Simplify to 5 lines per operation

### 3.2 Update Call Generation

**File**: `src/lir/generator/core.cpp`

**Before**:
```cpp
// Build FFICCallFrame
LIR::LIR_Inst frame_create(LIR::LIR_Op::FFICCallFrameCreate, frame_id_reg, arg_count_reg, stack_size_reg);
function.add_instruction(frame_create);

// Set frame registers
for (size_t i = 0; i < args.size(); i++) {
    LIR::LIR_Inst set_reg(LIR::LIR_Op::FFICCallFrameSetReg, frame_id_reg, i_reg, arg_regs[i]);
    function.add_instruction(set_reg);
}

// Execute call
LIR::LIR_Inst exec(LIR::LIR_Op::FFICCallExecute, dst_reg, func_ptr_reg);
function.add_instruction(exec);
```

**After**:
```cpp
// Direct ForeignCall
LIR::LIR_Inst call;
call.op = LIR::LIR_Op::ForeignCall;
call.result_type = return_type;
call.dst = dst_reg;
call.call_args = {func_ptr_reg, arg_reg_1, arg_reg_2, ...};
call.call_arg_types = {Type::Ptr, Type::I64, Type::I64, ...};
call.imm = static_cast<uint32_t>(LIR::CallingConvention::SystemV_x64);
function.add_instruction(call);
```

**Impact**:
- ~80% fewer LIR instructions for foreign calls
- Direct representation of intent
- VM handles frame setup internally

### 3.3 Update String/Buffer Generation

**File**: `src/lir/generator/expressions.cpp`

**Before**:
```cpp
// String to C string
LIR::LIR_Inst to_cstr(LIR::LIR_Op::FFIToCString, dst_reg, str_reg);
function.add_instruction(to_cstr);

// C string to string
LIR::LIR_Inst from_cstr(LIR::LIR_Op::FFIFromCString, dst_reg, cstr_reg);
function.add_instruction(from_cstr);
```

**After**:
```cpp
// String to C string
LIR::LIR_Inst marshal;
marshal.op = LIR::LIR_Op::Marshal;
marshal.result_type = Type::Ptr;
marshal.type_a = Type::String;
marshal.dst = dst_reg;
marshal.a = str_reg;
marshal.imm = static_cast<uint32_t>(LIR::MarshalType::StringToCString);
function.add_instruction(marshal);
```

---

## Phase 4: Testing & Validation (1 day)

### 4.1 Unit Tests

Create test file: `tests/lir/opcode_redesign.lm`

```limit
// Test MemoryLoad with different types
var ptr = ffi_alloc(100);
ffi_store_int32(ptr, 42);
var val: int = ffi_load_int32(ptr);
assert(val == 42);

// Test MemoryStore
ffi_store_int64(ptr, 1000000);
var val64: int = ffi_load_int64(ptr);
assert(val64 == 1000000);

// Test marshaling
var str = "Hello";
var cstr = ffi_to_cstring(str);
var str_back = ffi_from_cstring(cstr);
assert(str == str_back);

// Test pointer arithmetic
var ptr2 = ffi_add_ptr(ptr, 8);
assert(ffi_ptr_diff(ptr2, ptr) == 8);
```

### 4.2 Regression Tests

Run existing test suite:
```bash
./tests/run_tests.bat
```

Expected: All tests pass without modification (opcodes internal to IR)

### 4.3 Integration Tests

Verify:
- [ ] Memory operations work correctly
- [ ] Pointer arithmetic works
- [ ] String marshaling works
- [ ] Foreign calls work (if implemented)
- [ ] Callbacks work (if implemented)

### 4.4 Performance Validation

Measure:
- [ ] No performance regression in memory operations
- [ ] Type dispatch overhead acceptable
- [ ] Generated LIR is simpler/smaller

---

## Implementation Checklist

### Phase 1: Enum Design
- [ ] Remove 58 type-specific opcodes
- [ ] Add 8 generic memory opcodes
- [ ] Add 5 pointer opcodes
- [ ] Add 5 marshaling opcodes
- [ ] Add 3 linking opcodes
- [ ] Add 2 call opcodes
- [ ] Add 2 callback opcodes
- [ ] Update opcode count documentation
- [ ] Verify no duplicates

### Phase 2: VM Dispatchers
- [ ] Update `execute_memory()` for MemoryLoad/MemoryStore
- [ ] Replace 44 type-specific helper functions with type dispatch
- [ ] Update `execute_construction()` for Marshal/Unmarshal
- [ ] Update `execute_ffi()` for ForeignCall/Callback*
- [ ] Remove frame management code (now internal)
- [ ] Remove VM state management code (now internal)
- [ ] Test each operation type

### Phase 3: LIR Generation
- [ ] Update memory load/store generation
- [ ] Update foreign call generation
- [ ] Update string/buffer generation
- [ ] Update pointer operation generation
- [ ] Remove type-specific loops
- [ ] Simplify generator logic

### Phase 4: Testing
- [ ] Run full test suite
- [ ] Verify no regressions
- [ ] Performance validation
- [ ] Update documentation

---

## Benefits Summary

| Metric | Before | After | Change |
|--------|--------|-------|--------|
| Total opcodes | 150+ | ~95 | -37% |
| FFI opcodes | 58 | 15-20 | -73% |
| Type-specific load | 11 | 1 | -91% |
| Type-specific store | 11 | 1 | -91% |
| Helper functions | 44 | 1 | -98% |
| Naming clarity | FFILoadInt32 | MemoryLoad | ✅ |
| Code maintainability | Low | High | ✅ |
| Easy to extend | Hard | Easy | ✅ |

---

## Risk Assessment

### Low Risk ✅
- IR changes are internal to backend
- No changes to language syntax
- No changes to existing functionality
- Well-scoped changes

### Mitigations
- Comprehensive test suite catches regressions
- Phase-by-phase implementation allows testing after each phase
- Type dispatch is already proven pattern in VM

### Rollback Plan
- Git tag before starting: `lir-redesign-start`
- Easy to revert if issues arise
- Changes are isolated to backend/lir

---

## Timeline

| Phase | Duration | Start | End |
|-------|----------|-------|-----|
| Enum Design | 4 hours | Day 1 | Day 1 |
| VM Dispatchers | 12 hours | Day 1 | Day 2 |
| LIR Generation | 8 hours | Day 2 | Day 3 |
| Testing | 8 hours | Day 3 | Day 4 |
| **Total** | **32 hours** | | **4 days** |

---

## Success Criteria

- [ ] All tests pass without modification
- [ ] No performance regression
- [ ] Opcode count reduced by >50%
- [ ] VM dispatcher simpler and more maintainable
- [ ] LIR generation cleaner
- [ ] Documentation updated
- [ ] Code reviewed and approved

