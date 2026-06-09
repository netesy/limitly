# FFI as Intrinsics Layer - Architectural Redesign

## Current Problem

**Current State**: FFI is a separate layer bolted onto the VM
- `execute_ffi()` is a dedicated dispatcher with 50+ functions
- Separate concerns: arithmetic, memory, pointers all have their own handlers
- Memory operations like `load`, `store`, `memcpy` live in FFI but are really intrinsics
- No clear distinction between "Limitly operations" and "C interop"

**The Issue**: This creates a false boundary. Memory loads/stores are **fundamental operations**, not "FFI-specific". String creation is **data construction**, not "C conversion".

---

## The Insight

Looking at `execute_arithmetic()`:
```cpp
case LIR::LIR_Op::Add:
    registers[pc->dst] = lm_add(registers[pc->a], registers[pc->b]);
    break;
```

This is the **intrinsic pattern**:
1. LIR opcode maps to dispatcher case
2. Dispatcher calls runtime intrinsic function
3. Runtime function handles type dispatch and logic

**FFI should follow this same pattern**, not be separate from it.

---

## Proposed Architecture

### Tier 1: Fundamental Intrinsics (Already Correct)

These belong in `execute_arithmetic()` family:
```cpp
// Memory operations are intrinsics, not FFI-specific
case LIR::LIR_Op::MemoryLoad:
case LIR::LIR_Op::MemoryStore:
case LIR::LIR_Op::MemoryAlloc:
case LIR::LIR_Op::MemoryFree:

// Pointer arithmetic is intrinsic
case LIR::LIR_Op::FFIAddPtr:
case LIR::LIR_Op::FFISubPtr:
```

**Why**: These are not "C-specific". They're fundamental operations:
- Memory allocation is how we allocate anything (strings, buffers, objects)
- Pointer arithmetic is a basic data operation
- Loading/storing is core to object layout

### Tier 2: Data Construction (Move Out of FFI)

These are data construction, belong in own dispatcher:
```cpp
void RegisterVM::execute_construction(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // String operations
        case LIR::LIR_Op::FFIToCString:
            registers[pc->dst] = intrinsic_string_to_cptr(registers[pc->a]);
            break;
        case LIR::LIR_Op::FFIFromCString:
            registers[pc->dst] = intrinsic_cptr_to_string(registers[pc->a]);
            break;
        
        // Buffer operations
        case LIR::LIR_Op::FFIBufferAlloc:
            registers[pc->dst] = intrinsic_buffer_alloc(as_i64(registers[pc->a]));
            break;
        case LIR::LIR_Op::FFIBufferFromPtr:
            registers[pc->dst] = intrinsic_buffer_from_ptr(
                UNBOX_PTR(registers[pc->a]),
                as_i64(registers[pc->b])
            );
            break;
        
        // CString wrapper
        case LIR::LIR_Op::FFICStringPtr:
            registers[pc->dst] = intrinsic_cstring_ptr(registers[pc->a]);
            break;
        case LIR::LIR_Op::FFICStringFromPtr:
            registers[pc->dst] = intrinsic_cstring_from_ptr(
                UNBOX_PTR(registers[pc->a])
            );
            break;
    }
}
```

**Why**: These are **data construction/view operations**:
- Creating a string from bytes is like `ListCreate`
- Creating a buffer view is like `DictCreate`
- Creating a wrapper is like `FrameInstantiate`

### Tier 3: Interop Operations (Move to External Module)

These truly are C interop and stay somewhat separate:
```cpp
void RegisterVM::execute_extern(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // Library loading
        case LIR::LIR_Op::FFILibraryLoad:
            registers[pc->dst] = extern_library_load(
                intrinsic_string_to_cptr(registers[pc->a])
            );
            break;
        case LIR::LIR_Op::FFILibraryUnload:
            extern_library_unload(UNBOX_PTR(registers[pc->a]));
            break;
        case LIR::LIR_Op::FFILibraryGetSymbol:
            registers[pc->dst] = extern_library_get_symbol(
                UNBOX_PTR(registers[pc->a]),
                intrinsic_string_to_cptr(registers[pc->b])
            );
            break;
        
        // Foreign calls
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::FFICallPtr:
        case LIR::LIR_Op::FFICallPtr0:
            registers[pc->dst] = extern_call_function(pc);
            break;
        
        // Callbacks
        case LIR::LIR_Op::FFIRegisterCallback:
            registers[pc->dst] = extern_register_callback(registers[pc->a]);
            break;
    }
}
```

**Why**: These truly depend on C runtime and platform specifics:
- Loading external libraries
- Calling external functions
- Creating callbacks
- These are legitimately "extern"

---

## New Dispatcher Structure

### Before (Current)
```
Main VM loop
├── arithmetic (10 ops)
├── comparison (6 ops)
├── strings (8 ops)
├── collections (12 ops)
├── io (3 ops)
├── ffi (50+ ops)  ← BLOATED
├── calls (5 ops)
├── concurrency (15 ops)
└── ...
```

### After (Proposed)
```
Main VM loop
├── arithmetic (10 ops)
├── comparison (6 ops)
├── strings (8 ops)
├── collections (12 ops)
├── io (3 ops)
├── memory (8 ops)
│   └── Move from FFI: alloc, free, realloc, load, store, memcpy, memset, memcmp
├── construction (12 ops)
│   └── Move from FFI: string conversion, buffer ops, CString wrapper
├── extern (15 ops)
│   └── Keep in FFI: library loading, foreign calls, callbacks
├── calls (5 ops)
├── concurrency (15 ops)
└── ...
```

---

## Detailed Proposal

### 1. Create `execute_memory()` Dispatcher

**File**: Rename part of `src/backend/vm/ops/ffi.cpp` to `src/backend/vm/ops/memory.cpp`

**Why**: Memory operations are fundamentals, not FFI-specific

```cpp
// src/backend/vm/ops/memory.cpp
#include "../register.hh"
#include "../../../runtime/runtime.h"

namespace LM { namespace Backend { namespace VM { namespace Register {

void RegisterVM::execute_memory(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // Memory allocation
        case LIR::LIR_Op::MemoryAlloc:
            registers[pc->dst] = intrinsic_alloc(as_i64(registers[pc->a]));
            break;
        case LIR::LIR_Op::MemoryFree:
            intrinsic_free(UNBOX_PTR(registers[pc->a]));
            break;
        case LIR::LIR_Op::MemoryResize:
            registers[pc->dst] = intrinsic_realloc(
                UNBOX_PTR(registers[pc->a]),
                as_i64(registers[pc->b])
            );
            break;
        
        // Load/store dispatch
        case LIR::LIR_Op::MemoryLoad: {
            int type_id = pc->imm & 0xF;
            registers[pc->dst] = intrinsic_load(
                UNBOX_PTR(registers[pc->a]),
                (PrimitiveType)type_id
            );
            break;
        }
        case LIR::LIR_Op::MemoryStore: {
            int type_id = pc->imm & 0xF;
            intrinsic_store(
                UNBOX_PTR(registers[pc->dst]),
                registers[pc->a],
                (PrimitiveType)type_id
            );
            break;
        }
        
        // Bulk operations
        case LIR::LIR_Op::FFIMemcpy:
            intrinsic_memcpy(
                UNBOX_PTR(registers[pc->dst]),
                UNBOX_PTR(registers[pc->a]),
                as_i64(registers[pc->b])
            );
            break;
        case LIR::LIR_Op::FFIMemset:
            intrinsic_memset(
                UNBOX_PTR(registers[pc->dst]),
                as_i64(registers[pc->a]),
                as_i64(registers[pc->b])
            );
            break;
        case LIR::LIR_Op::FFIMemcmp:
            registers[pc->dst] = make_i64(intrinsic_memcmp(
                UNBOX_PTR(registers[pc->a]),
                UNBOX_PTR(registers[pc->b]),
                as_i64(registers[pc->imm])
            ));
            break;
        
        // Pointer arithmetic
        case LIR::LIR_Op::FFIAddPtr:
            registers[pc->dst] = intrinsic_add_ptr(
                UNBOX_PTR(registers[pc->a]),
                as_i64(registers[pc->b])
            );
            break;
        case LIR::LIR_Op::FFISubPtr:
            registers[pc->dst] = intrinsic_sub_ptr(
                UNBOX_PTR(registers[pc->a]),
                as_i64(registers[pc->b])
            );
            break;
        case LIR::LIR_Op::FFIPtrDiff:
            registers[pc->dst] = make_i64(intrinsic_ptr_diff(
                UNBOX_PTR(registers[pc->a]),
                UNBOX_PTR(registers[pc->b])
            ));
            break;
        case LIR::LIR_Op::FFIAlignPtr:
            registers[pc->dst] = intrinsic_align_ptr(
                UNBOX_PTR(registers[pc->a]),
                as_i64(registers[pc->b])
            );
            break;
        case LIR::LIR_Op::FFIIsAligned:
            registers[pc->dst] = intrinsic_is_aligned(
                UNBOX_PTR(registers[pc->a]),
                as_i64(registers[pc->b])
                ? VAL_TRUE : VAL_FALSE;
            break;
        
        default:
            break;
    }
}

}}}} // namespaces
```

### 2. Create `execute_construction()` Dispatcher

**File**: New `src/backend/vm/ops/construction.cpp`

**Why**: These are data construction operations, like `ListCreate`, `DictCreate`

```cpp
// src/backend/vm/ops/construction.cpp
#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_string.h"

namespace LM { namespace Backend { namespace VM { namespace Register {

void RegisterVM::execute_construction(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // String construction from C pointer
        case LIR::LIR_Op::FFIFromCString: {
            const char* cstr = static_cast<const char*>(UNBOX_PTR(registers[pc->a]));
            registers[pc->dst] = cstr ? lm_string_from_cstr(cstr).value : VAL_NIL;
            break;
        }
        
        // String conversion to C pointer
        case LIR::LIR_Op::FFIToCString: {
            RegisterValue str_val = registers[pc->a];
            if (IS_PTR(str_val)) {
                auto* header = static_cast<ObjHeader*>(UNBOX_PTR(str_val));
                if (header->type_id == TYPE_STRING) {
                    LmString lm_str = {.value = str_val};
                    registers[pc->dst] = BOX_PTR((void*)lm_string_data(lm_str));
                    break;
                }
            }
            registers[pc->dst] = VAL_NIL;
            break;
        }
        
        // Buffer construction
        case LIR::LIR_Op::FFIBufferAlloc: {
            int64_t size = as_i64(registers[pc->a]);
            void* ptr = malloc(size);
            registers[pc->dst] = ptr ? BOX_PTR(ptr) : VAL_NIL;
            break;
        }
        
        case LIR::LIR_Op::FFIBufferFromPtr: {
            void* ptr = UNBOX_PTR(registers[pc->a]);
            int64_t size = as_i64(registers[pc->b]);
            // Create buffer object wrapping this pointer
            registers[pc->dst] = create_buffer(ptr, size);
            break;
        }
        
        case LIR::LIR_Op::FFIBufferFree: {
            RegisterValue buf = registers[pc->a];
            if (IS_PTR(buf)) {
                auto* header = static_cast<ObjHeader*>(UNBOX_PTR(buf));
                if (header->type_id == TYPE_BUFFER) {
                    // Extract and free
                    free_buffer(buf);
                }
            }
            break;
        }
        
        // CString wrapper creation
        case LIR::LIR_Op::FFICStringFromPtr: {
            void* ptr = UNBOX_PTR(registers[pc->a]);
            registers[pc->dst] = create_cstring_wrapper(ptr);
            break;
        }
        
        case LIR::LIR_Op::FFICStringPtr: {
            RegisterValue cstr_obj = registers[pc->a];
            registers[pc->dst] = extract_ptr_from_cstring_wrapper(cstr_obj);
            break;
        }
        
        default:
            break;
    }
}

}}}} // namespaces
```

### 3. Reduce FFI to Just External Interop

**File**: Keep `src/backend/vm/ops/ffi.cpp` but only for true C interop

```cpp
// src/backend/vm/ops/ffi.cpp (simplified)
#include "../register.hh"
#include "../../../runtime/runtime.h"
#include <dlfcn.h>

namespace LM { namespace Backend { namespace VM { namespace Register {

void RegisterVM::execute_ffi(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // Library loading - true external C interop
        case LIR::LIR_Op::FFILibraryLoad: {
            RegisterValue path_val = registers[pc->a];
            const char* path = get_cstring_from_value(path_val);
            if (!path) {
                registers[pc->dst] = VAL_NIL;
                break;
            }
            
            #ifdef _WIN32
            void* handle = LoadLibraryA(path);
            #else
            void* handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
            #endif
            
            registers[pc->dst] = handle ? BOX_PTR(handle) : VAL_NIL;
            break;
        }
        
        case LIR::LIR_Op::FFILibraryUnload: {
            void* handle = UNBOX_PTR(registers[pc->a]);
            if (handle) {
                #ifdef _WIN32
                FreeLibrary(static_cast<HMODULE>(handle));
                #else
                dlclose(handle);
                #endif
            }
            break;
        }
        
        case LIR::LIR_Op::FFILibraryGetSymbol: {
            void* handle = UNBOX_PTR(registers[pc->a]);
            RegisterValue sym_val = registers[pc->b];
            const char* symbol = get_cstring_from_value(sym_val);
            
            if (!handle || !symbol) {
                registers[pc->dst] = VAL_NIL;
                break;
            }
            
            #ifdef _WIN32
            void* ptr = (void*)GetProcAddress(static_cast<HMODULE>(handle), symbol);
            #else
            void* ptr = dlsym(handle, symbol);
            #endif
            
            registers[pc->dst] = ptr ? BOX_PTR(ptr) : VAL_NIL;
            break;
        }
        
        // Foreign function calls
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::FFICallPtr: {
            void* func = UNBOX_PTR(registers[pc->a]);
            if (!func) {
                registers[pc->dst] = VAL_NIL;
                break;
            }
            
            // Call with proper calling convention
            registers[pc->dst] = call_external_function(
                func,
                pc->call_args,
                registers,
                pc->result_type
            );
            break;
        }
        
        // Callbacks
        case LIR::LIR_Op::FFIRegisterCallback: {
            RegisterValue callback = registers[pc->a];
            int64_t callback_id = register_limitly_callback(callback);
            registers[pc->dst] = make_i64(callback_id);
            break;
        }
        
        case LIR::LIR_Op::FFIUnregisterCallback: {
            int64_t callback_id = as_i64(registers[pc->a]);
            unregister_limitly_callback(callback_id);
            break;
        }
        
        case LIR::LIR_Op::FFIGetCallbackPtr: {
            int64_t callback_id = as_i64(registers[pc->a]);
            void* ptr = get_callback_trampoline_ptr(callback_id);
            registers[pc->dst] = ptr ? BOX_PTR(ptr) : VAL_NIL;
            break;
        }
        
        default:
            break;
    }
}

}}}} // namespaces
```

### 4. Update Main Dispatcher

**File**: `src/backend/vm/vm.cpp` (or wherever main execute loop is)

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
        
        // Memory operations (intrinsic layer)
        case LIR::LIR_Op::MemoryAlloc:
        case LIR::LIR_Op::MemoryFree:
        case LIR::LIR_Op::MemoryLoad:
        case LIR::LIR_Op::MemoryStore:
        case LIR::LIR_Op::FFIAddPtr:
        case LIR::LIR_Op::FFIMemcpy:
            execute_memory(pc);
            break;
        
        // Data construction (intrinsic layer)
        case LIR::LIR_Op::FFIToCString:
        case LIR::LIR_Op::FFIFromCString:
        case LIR::LIR_Op::FFIBufferAlloc:
        case LIR::LIR_Op::FFICStringFromPtr:
            execute_construction(pc);
            break;
        
        // External interop
        case LIR::LIR_Op::FFILibraryLoad:
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::FFIRegisterCallback:
            execute_ffi(pc);
            break;
        
        // ... other operations
    }
}
```

---

## Benefits of This Architecture

### 1. **Correct Abstraction Levels**
- **Tier 1 (Intrinsics)**: Memory, arithmetic, pointers - fundamental operations
- **Tier 2 (Construction)**: Data structure creation - part of value system
- **Tier 3 (Extern)**: C library calls - truly external

### 2. **Easier to Understand and Maintain**
- FFI becomes just "external C interop" (5-10 operations)
- Not conflating "accessing memory" with "calling C functions"
- Each dispatcher has single responsibility

### 3. **Better Code Organization**
- Memory ops grouped with other memory concepts
- String operations in construction layer (like ListCreate)
- Only pure C interop in FFI module

### 4. **Clearer Semantics**
- `MemoryLoad/Store` are now clearly intrinsics (not FFI-specific)
- `StringFromCString` is data construction (not C-specific interop)
- `LibraryLoad` is clearly external interop

### 5. **Future-Proof**
- Easy to add new intrinsics (just add case to `execute_memory`)
- Easy to add new data types (add to `execute_construction`)
- C interop stays confined to `execute_ffi`

---

## Migration Path

### Step 1: Create New Dispatchers
- [ ] Create `src/backend/vm/ops/memory.cpp`
- [ ] Create `src/backend/vm/ops/construction.cpp`
- [ ] Add method declarations to `register.hh`

### Step 2: Move FFI Code
- [ ] Move memory operations to `memory.cpp`
- [ ] Move string/buffer operations to `construction.cpp`
- [ ] Keep only external interop in `ffi.cpp`

### Step 3: Update Main Dispatcher
- [ ] Add cases to main execute loop
- [ ] Update switch statement in main VM

### Step 4: Update Header
- [ ] Add new methods to `register.hh`
- [ ] Remove old FFI method declarations

### Step 5: Test & Verify
- [ ] Run full test suite
- [ ] Check no functionality lost
- [ ] Verify same behavior

---

## Example: How This Improves Code

### Before (Everything in FFI)
```cpp
// src/backend/vm/ops/ffi.cpp - 50+ functions
void execute_ffi_alloc() { ... }
void execute_ffi_load_int64() { ... }
void execute_ffi_from_cstring() { ... }
void execute_ffi_library_load() { ... }
void execute_ffi_call_ptr() { ... }
// All mixed together, hard to navigate
```

### After (Clear Layers)
```cpp
// src/backend/vm/ops/memory.cpp - Pure memory operations
void execute_memory(const LIR::LIR_Inst* pc) {
    case MemoryAlloc: ... // Intrinsic
    case MemoryLoad: ... // Intrinsic
    case FFIAddPtr: ... // Intrinsic
}

// src/backend/vm/ops/construction.cpp - Data construction
void execute_construction(const LIR::LIR_Inst* pc) {
    case FFIFromCString: ... // Data construction
    case FFIBufferAlloc: ... // Data construction
}

// src/backend/vm/ops/ffi.cpp - External C interop only
void execute_ffi(const LIR::LIR_Inst* pc) {
    case FFILibraryLoad: ... // True interop
    case ForeignCall: ... // True interop
    case FFIRegisterCallback: ... // True interop
}
```

---

## Conclusion

The key insight is:

> **FFI is not a layer. It's the boundary between Limitly and external code. Inside that boundary, memory operations are intrinsics, data construction is part of the value system, and only genuine C interop belongs in the FFI module.**

This redesign:
- ✅ Doesn't add new LIR instructions
- ✅ Uses existing LIR opcodes more semantically correct
- ✅ Improves code organization and maintainability
- ✅ Makes the architecture clearer and more extensible
- ✅ Separates concerns properly
- ✅ Makes it easier to test and debug

