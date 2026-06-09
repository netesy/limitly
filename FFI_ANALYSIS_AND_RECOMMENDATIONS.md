# FFI Implementation Analysis - Seamless C Interop

## Executive Summary

The current FFI implementation in `src/backend/vm/ops/ffi.cpp` provides comprehensive C interop capabilities but has **critical gaps** preventing seamless bidirectional interop. The architecture is sound, using the existing LIR infrastructure correctly, but needs targeted improvements.

**Key Finding**: The FFI layer has **placeholder implementations** for string conversion and actual C function calls that must be completed for true interop.

---

## Current State Analysis

### ✅ What We Have (Fully Implemented)

#### 1. Memory Management (8 functions)
- `execute_ffi_alloc()` - malloc wrapper with tracking
- `execute_ffi_free()` - free with validation
- `execute_ffi_realloc()` - realloc with tracking
- **Quality**: Excellent. Tracks allocations, prevents double-free, thread-safe

#### 2. Memory Operations (3 functions)
- `execute_ffi_memcpy()` - memory copying
- `execute_ffi_memset()` - memory initialization
- `execute_ffi_memcmp()` - memory comparison
- **Quality**: Complete and correct

#### 3. Pointer Arithmetic (5 functions)
- `execute_ffi_add_ptr()` - pointer + offset
- `execute_ffi_sub_ptr()` - pointer - offset
- `execute_ffi_ptr_diff()` - pointer difference
- `execute_ffi_align_ptr()` - alignment calculation
- `execute_ffi_is_aligned()` - alignment checking
- **Quality**: Correct, all edge cases handled

#### 4. Load Operations (11 functions)
- All primitive types: i8, u8, i16, u16, i32, u32, i64, u64, float, double, ptr
- Format: `execute_ffi_load_[type]()`
- **Quality**: Complete and correct boxing/unboxing

#### 5. Store Operations (11 functions)
- Mirror of load operations for writing
- Format: `execute_ffi_store_[type]()`
- **Quality**: Complete and correct

#### 6. Library Loading (3 functions)
- `execute_ffi_library_load()` - dlopen/LoadLibraryA
- `execute_ffi_library_unload()` - dlclose/FreeLibrary
- `execute_ffi_library_get_symbol()` - dlsym/GetProcAddress
- **Quality**: Cross-platform (Windows/Unix), correct

#### 7. Callback Infrastructure (3 functions)
- `execute_ffi_register_callback()` - register a callback ID
- `execute_ffi_unregister_callback()` - unregister callback
- `execute_ffi_get_callback_ptr()` - retrieve callback pointer
- **Quality**: Skeleton present but trampoline creation is NOT implemented

#### 8. Call Frame Management (6 functions)
- `execute_ffi_ccall_frame_create()` - allocate call frame
- `execute_ffi_ccall_frame_destroy()` - deallocate call frame
- `execute_ffi_ccall_frame_set_reg()` - set register argument
- `execute_ffi_ccall_frame_get_reg()` - get register argument
- `execute_ffi_ccall_frame_set_stack_arg()` - set stack argument
- `execute_ffi_ccall_frame_get_stack_arg()` - get stack argument
- **Quality**: Good but unused - no actual calling mechanism

---

### ❌ What's Missing or Broken

#### 1. **String Conversion (2 functions) - CRITICAL**
```cpp
void RegisterVM::execute_ffi_to_cstring(const LIR::LIR_Inst* pc) {
    // PLACEHOLDER: Returns VAL_NIL
    registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_ffi_from_cstring(const LIR::LIR_Inst* pc) {
    // PLACEHOLDER: Returns VAL_NIL
    registers[pc->dst] = VAL_NIL;
}
```

**Impact**: Cannot pass strings to/from C functions. This blocks most practical C interop.

**Why it's broken**: Requires runtime support to:
- Extract string data from Limitly string object (boxed heap value)
- Create Limitly string from C string pointer

**Needed**:
- Runtime function to get C string pointer from Limitly `LmString`
- Runtime function to create Limitly string from C pointer
- These should already exist in `src/runtime/runtime_string.h`

#### 2. **Actual C Function Calling (1 function) - CRITICAL**
```cpp
void RegisterVM::execute_ffi_ccall_execute(const LIR::LIR_Inst* pc) {
    // PLACEHOLDER: Returns 0
    registers[pc->dst] = BOX_INT(0);
}
```

**Impact**: Cannot call C functions at all. The infrastructure is ready but not connected.

**Why it's broken**: Requires actual calling mechanism that:
- Uses call frame setup to marshall arguments
- Calls the function pointer
- Marshalls return value back

**Needed**:
- Platform-specific calling convention support (x86-64, ARM64)
- Thunk generation for calling conventions
- Currently missing entirely

#### 3. **Callback Trampolines (1 function) - CRITICAL**
```cpp
void RegisterVM::execute_ffi_register_callback(const LIR::LIR_Inst* pc) {
    // INCOMPLETE: Allocates ID but doesn't create trampoline
    int64_t callback_id = g_next_callback_id++;
    registers[pc->dst] = BOX_INT(callback_id);
}
```

**Impact**: Cannot pass Limitly functions to C code.

**Why it's broken**: Trampoline generation requires:
- Allocating executable memory
- Writing machine code to call back into Limitly
- Platform-specific assembly

**Needed**:
- Executable memory allocator (Windows VirtualAlloc, Unix mprotect)
- Minimal machine code generation for thunks
- Alternative: Use libffi for this

#### 4. **VM State Save/Restore (2 functions) - INCOMPLETE**
```cpp
void RegisterVM::execute_ffi_vm_save(const LIR::LIR_Inst* pc) {
    registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_ffi_vm_restore(const LIR::LIR_Inst* pc) {
    // do nothing
}
```

**Impact**: Cannot save/restore VM state around C calls.

**Why it's needed**: C functions might longjmp or otherwise disrupt VM state.

#### 5. **Struct Layout Calculation (1 function) - INCOMPLETE**
```cpp
void RegisterVM::execute_ffi_calc_struct_layout(const LIR::LIR_Inst* pc) {
    registers[pc->dst] = VAL_NIL;
}
```

**Impact**: Cannot calculate proper struct offsets for C struct access.

#### 6. **ABI Info Query (1 function) - INCOMPLETE**
```cpp
void RegisterVM::execute_ffi_get_abi_info(const LIR::LIR_Inst* pc) {
    registers[pc->dst] = VAL_NIL;
}
```

**Impact**: Cannot query platform calling conventions.

---

## LIR Architecture Analysis

### ✅ LIR Instruction Coverage

The LIR opcodes are well-designed for FFI. We have:

**Memory Operations**:
- `FFIAlloc`, `FFIFree`, `FFIRealloc` - memory management
- `FFIMemcpy`, `FFIMemset`, `FFIMemcmp` - bulk operations
- `MemoryLoad`, `MemoryStore` - generic load/store with type dispatch

**Pointer Operations**:
- `FFIAddPtr`, `FFISubPtr`, `FFIPtrDiff`, `FFIAlignPtr`, `FFIIsAligned`

**Type-Specific Load/Store** (22 opcodes):
- Individual opcodes for each primitive: `FFILoadInt8`, `FFILoadUInt8`, etc.
- Or can use generic `MemoryLoad`/`MemoryStore` with `imm` field as type index

**Library Loading**:
- `FFILibraryLoad`, `FFILibraryUnload`, `FFILibraryGetSymbol`

**Foreign Calls**:
- `ForeignCall` - generic C function calls (NOT IMPLEMENTED)
- `FFICallPtr0-5` - convenience wrappers with fixed arg counts (NOT IMPLEMENTED)

**Call Frames**:
- `FFICCallFrameCreate`, `FFICCallFrameDestroy`
- `FFICCallFrameSetReg`, `FFICCallFrameGetReg`
- `FFICCallFrameSetStackArg`, `FFICCallFrameGetStackArg`

**Supporting**:
- `FFIRegisterCallback`, `FFIUnregisterCallback`, `FFIGetCallbackPtr`
- `FFIVMSave`, `FFIVMRestore`, `FFICCallExecute`
- `FFICalcStructLayout`, `FFIGetABIInfo`

### ✅ Existing Infrastructure We Can Use

1. **Tagged Value System**
   - All values in registers are `RegisterValue` (uint64_t with 3-bit tag)
   - Boxing/unboxing already correct in FFI code
   - Supports: INT (61-bit), PTR (raw pointer), IMMEDIATE (nil, true, false)

2. **Heap Objects**
   - `ObjHeader` + type_id system for complex types
   - `LmString` already defined in runtime

3. **Function Calling**
   - Call frame already has `call_args` vector of registers
   - Call frame has `call_arg_types` for type information

4. **Thread Safety**
   - Using std::mutex for all global state (allocations, libraries, callbacks)
   - This is correct and sufficient

### 🔴 Missing: Actual Function Calling Convention

**Problem**: No code to actually invoke C functions with proper calling conventions.

**Current State**: 
- Call frames set up arguments
- But `execute_ffi_ccall_execute()` just returns 0
- Never actually calls the function

**What's Needed** (use existing LIR, no new instructions):

Use the `ForeignCall` LIR_Op which already exists:
```cpp
void RegisterVM::execute_ffi_ccall_execute(const LIR::LIR_Inst* pc) {
    // Get function pointer
    RegisterValue func_ptr_val = registers[pc->a];
    if (!IS_PTR(func_ptr_val)) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* func_ptr = UNBOX_PTR(func_ptr_val);
    
    // Get call frame or arguments
    // On x86-64 System V ABI:
    // - RDI, RSI, RDX, RCX, R8, R9 for integer/pointer args
    // - XMM0-7 for float args
    // - RAX for return
    
    // For now: Simple case with fixed arg count from pc->imm
    int arg_count = pc->imm & 0xF;
    
    // Call with appropriate convention
    // This requires platform-specific assembly
}
```

---

## Recommendations for Seamless Interop

### Priority 1: Critical Path (Do First)

#### 1.1 Implement String Conversion (2-3 hours)

**File**: `src/backend/vm/ops/ffi.cpp`

Replace placeholders:

```cpp
void RegisterVM::execute_ffi_to_cstring(const LIR::LIR_Inst* pc) {
    RegisterValue str_val = registers[pc->a];
    
    // Check if it's a Limitly string (heap-allocated)
    if (!IS_PTR(str_val)) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    auto* header = static_cast<ObjHeader*>(UNBOX_PTR(str_val));
    if (header->type_id != TYPE_STRING) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Get the string data pointer
    // Requires runtime function: const char* lm_string_data(LmString str)
    // From runtime/runtime_string.h
    LmString lm_str = {.value = str_val};
    const char* cstr = lm_string_data(lm_str);
    
    if (!cstr) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    registers[pc->dst] = BOX_PTR((void*)cstr);
}

void RegisterVM::execute_ffi_from_cstring(const LIR::LIR_Inst* pc) {
    RegisterValue cstr_val = registers[pc->a];
    
    if (!IS_PTR(cstr_val)) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    const char* cstr = static_cast<const char*>(UNBOX_PTR(cstr_val));
    if (!cstr) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Convert C string to Limitly string
    // Requires runtime function: LmString lm_string_from_cstr(const char* cstr)
    // From runtime/runtime_string.h
    LmString lm_str = lm_string_from_cstr(cstr);
    
    registers[pc->dst] = lm_str.value;
}
```

**Runtime Support Needed** (check/add to `src/runtime/runtime_string.h`):
```c
const char* lm_string_data(LmString str);
LmString lm_string_from_cstr(const char* cstr);
```

#### 1.2 Implement Basic C Function Calling (4-6 hours)

**File**: `src/backend/vm/ops/ffi.cpp` + new `src/backend/vm/calling_convention.hh`

Start with x86-64 System V ABI (used on Linux/macOS) and Windows x64:

```cpp
// New file: src/backend/vm/calling_convention.hh
#pragma once

#include "../lir/lir.hh"
#include <cstdint>
#include <vector>

namespace LM {
namespace Backend {
namespace VM {

// Simple calling convention support
class CallConvention {
public:
    // Call function with arguments from registers, return in registers[dst]
    static void call_extern_func(
        void* func_ptr,
        const std::vector<RegisterValue>& args,
        const std::vector<LIR::Type>& arg_types,
        RegisterValue& result,
        LIR::Type result_type
    );
    
    // Get platform calling convention info
    static const char* get_calling_convention();
    static int get_max_register_args();
};

}}}
```

**Implementation** (`src/backend/vm/calling_convention.cpp`):
- For x86-64: Use inline assembly or LLVM's calling convention
- For ARM64: Similar approach
- Use platform detection macros

**Connect to FFI execution**:
```cpp
void RegisterVM::execute_ffi_ccall_execute(const LIR::LIR_Inst* pc) {
    RegisterValue func_ptr_val = registers[arg_reg(pc, 0, pc->a)];
    if (!IS_PTR(func_ptr_val)) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* func_ptr = UNBOX_PTR(func_ptr_val);
    
    // Get call frame if provided
    int arg_count = pc->call_args.size();
    std::vector<RegisterValue> args;
    std::vector<LIR::Type> arg_types;
    
    for (size_t i = 0; i < arg_count; i++) {
        args.push_back(registers[pc->call_args[i]]);
        arg_types.push_back(pc->call_arg_types.size() > i ? 
                           pc->call_arg_types[i] : LIR::Type::I64);
    }
    
    RegisterValue result = VAL_NIL;
    CallConvention::call_extern_func(
        func_ptr, args, arg_types, result, pc->result_type
    );
    
    registers[pc->dst] = result;
}
```

### Priority 2: Important (Do Second)

#### 2.1 Implement VM State Save/Restore (1-2 hours)

```cpp
void RegisterVM::execute_ffi_vm_save(const LIR::LIR_Inst* pc) {
    // Create a list containing all register values
    // Return pointer to saved state
    // For now, we can store in global map
    
    static uint64_t vm_save_id = 0;
    uint64_t id = vm_save_id++;
    
    // Store register state
    std::vector<RegisterValue> saved_regs = registers;
    g_vm_saved_states[id] = saved_regs;
    
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(id));
}

void RegisterVM::execute_ffi_vm_restore(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]);
    auto it = g_vm_saved_states.find(static_cast<uint64_t>(id));
    if (it != g_vm_saved_states.end()) {
        registers = it->second;
        g_vm_saved_states.erase(it);
    }
}
```

#### 2.2 Implement Callback Trampolines (3-4 hours)

This is complex. Start simple:

```cpp
// For x86-64, we need a small trampoline that calls back into Limitly
// Simple approach: use thunk pool

struct CallbackThunk {
    uint64_t callback_id;
    void* limitly_callback_func;
    // Machine code for the trampoline
};

void RegisterVM::execute_ffi_register_callback(const LIR::LIR_Inst* pc) {
    // Get the Limitly function pointer
    RegisterValue func_val = registers[arg_reg(pc, 0, pc->a)];
    
    if (!IS_PTR(func_val)) {
        registers[pc->dst] = BOX_INT(-1);
        return;
    }
    
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    int64_t callback_id = g_next_callback_id++;
    
    // TODO: Allocate and generate thunk
    // For now, store the callback function address
    g_callbacks[callback_id] = UNBOX_PTR(func_val);
    
    registers[pc->dst] = BOX_INT(callback_id);
}
```

**Alternative**: Use `libffi` library for closure support:
- Add `#include <ffi.h>`
- Use `ffi_closure_alloc()` to create executable space
- Use `ffi_prep_closure()` to set up callback
- Much simpler and portable

### Priority 3: Nice-to-Have (Do Later)

#### 3.1 Struct Layout Calculation

```cpp
void RegisterVM::execute_ffi_calc_struct_layout(const LIR::LIR_Inst* pc) {
    // For now, store field info and return a layout descriptor
    // This requires parsing field types and calculating offsets
    // with proper ABI padding
    
    // Simple case: no padding (will break on some architectures)
    registers[pc->dst] = VAL_NIL;  // Return nil for now
}
```

#### 3.2 ABI Info Query

```cpp
void RegisterVM::execute_ffi_get_abi_info(const LIR::LIR_Inst* pc) {
    // Return platform-specific ABI information
    // Pointer size, alignment requirements, etc.
    
    struct ABIInfo {
        uint32_t pointer_size;   // 8 on 64-bit
        uint32_t alignment;      // 8 on 64-bit
        uint32_t calling_convention;  // SYSV_ABI, WINDOWS_x64, etc.
    };
    
    // Store in a static and return pointer
    registers[pc->dst] = VAL_NIL;  // Return nil for now
}
```

---

## Implementation Checklist

### Phase 1: Enable Basic Interop (Required)
- [ ] Implement `execute_ffi_to_cstring()` - uses existing LIR
- [ ] Implement `execute_ffi_from_cstring()` - uses existing LIR
- [ ] Add runtime string conversion functions to runtime_string.h
- [ ] Implement `execute_ffi_ccall_execute()` - uses existing LIR
- [ ] Create calling_convention.hh with platform support

### Phase 2: Complete Infrastructure (Important)
- [ ] Implement `execute_ffi_vm_save()` - uses existing LIR
- [ ] Implement `execute_ffi_vm_restore()` - uses existing LIR
- [ ] Implement callback trampolines (or integrate libffi)
- [ ] Add `execute_ffi_register_callback()` - uses existing LIR

### Phase 3: Polish (Nice-to-Have)
- [ ] Implement `execute_ffi_calc_struct_layout()` - new data structures
- [ ] Implement `execute_ffi_get_abi_info()` - uses existing LIR
- [ ] Add error handling and validation

---

## Key Architectural Decisions

### 1. Don't Add New LIR Instructions
✅ **DECISION**: Use existing LIR opcodes
- `ForeignCall` already exists for calling C functions
- `FFICallPtr0-5` can be convenience wrappers
- `MemoryLoad`/`MemoryStore` with `imm` field handle type dispatch
- Call frames already support argument marshalling

### 2. Keep String Conversion Simple
✅ **DECISION**: Direct pointer exchange
- Don't copy strings when passing to C
- Return pointer to C string data
- Use existing boxed string layout

### 3. Leverage Existing Value System
✅ **DECISION**: Use RegisterValue (uint64_t with 3-bit tag)
- All pointers are already boxed correctly
- Integer boxing matches C int64_t
- Float boxing works for doubles

### 4. Platform-Specific Calling Conventions
✅ **DECISION**: Encapsulate in CallConvention class
- Single `#ifdef` for platform selection
- x86-64 System V ABI (Linux/macOS)
- x86-64 Windows ABI
- ARM64 (when needed)

---

## Testing Strategy

Create test file: `tests/ffi/basic_c_interop.lm`

```limit
// Load C standard library
var libc = ffi_library_load("libc.so.6");  // or msvcrt.dll on Windows

// Test 1: String conversion
var limitly_str = "Hello from Limitly!";
var c_ptr = ffi_to_cstring(limitly_str);
var back = ffi_from_cstring(c_ptr);
print("String roundtrip: {back}");

// Test 2: Memory operations
var ptr = ffi_alloc(100);
ffi_store_int64(ptr, 42);
var val = ffi_load_int64(ptr);
print("Memory value: {val}");
ffi_free(ptr);

// Test 3: Library loading
var puts_func = ffi_library_get_symbol(libc, "puts");
if (puts_func != nil) {
    print("Found puts function!");
}
ffi_library_unload(libc);
```

---

## Conclusion

The FFI implementation has an **excellent foundation** with comprehensive LIR support and correct low-level operations. However, it needs **three critical implementations** for seamless interop:

1. **String conversion** (2-3 hours) - Use existing LIR and runtime
2. **C function calling** (4-6 hours) - Use existing LIR, add calling convention
3. **Callback trampolines** (3-4 hours) - Use existing LIR, integrate libffi

These are **achievable without adding new LIR instructions** by leveraging:
- Existing `ForeignCall` and `FFICallPtr*` opcodes
- Existing call frame infrastructure
- Existing boxing/unboxing system
- Platform detection already in place

**Total estimated effort**: 10-15 hours for Phase 1 & 2 to enable full bidirectional C interop.

