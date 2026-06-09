#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Data construction layer - operations for creating/viewing data structures
// This layer includes: strings, buffers, wrappers, and other constructed types

// String conversion - construct Limitly string from C pointer
void RegisterVM::execute_construct_string_from_cstr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    const char* cstr = static_cast<const char*>(UNBOX_PTR(registers[pc->a]));
    if (!cstr) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Convert C string to Limitly string using runtime support
    // TODO: Call runtime function when available
    // LmString lm_str = lm_string_from_cstr(cstr);
    // registers[pc->dst] = lm_str.value;
    
    // Placeholder until runtime support integrated
    registers[pc->dst] = VAL_NIL;
}

// String conversion - construct C pointer view from Limitly string
void RegisterVM::execute_construct_cstr_from_string(const LIR::LIR_Inst* pc) {
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
    // TODO: Call runtime function when available
    // LmString lm_str = {.value = str_val};
    // const char* cstr = lm_string_data(lm_str);
    // registers[pc->dst] = BOX_PTR((void*)cstr);
    
    // Placeholder until runtime support integrated
    registers[pc->dst] = VAL_NIL;
}

// Free C string - helper for freeing allocated strings
void RegisterVM::execute_construct_free_cstr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[pc->a]);
    if (ptr) {
        std::free(ptr);
    }
}

// Buffer construction - allocate buffer of given size
void RegisterVM::execute_construct_buffer_alloc(const LIR::LIR_Inst* pc) {
    int64_t size = to_int(registers[pc->a]);
    if (size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = std::malloc(size);
    if (!ptr) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // TODO: Wrap in Buffer frame structure when available
    // For now, just return raw pointer
    registers[pc->dst] = BOX_PTR(ptr);
}

// Buffer construction - create buffer from existing pointer
void RegisterVM::execute_construct_buffer_from_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[pc->a]);
    int64_t size = to_int(registers[pc->b]);
    
    if (size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // TODO: Create buffer object wrapping this pointer
    // For now, just return raw pointer
    registers[pc->dst] = BOX_PTR(ptr);
}

// Buffer operations - get capacity of buffer
void RegisterVM::execute_construct_buffer_capacity(const LIR::LIR_Inst* pc) {
    RegisterValue buf = registers[pc->a];
    
    // TODO: Extract capacity from buffer frame
    // For now, return 0
    registers[pc->dst] = BOX_INT(0);
}

// Buffer operations - get size of buffer
void RegisterVM::execute_construct_buffer_size(const LIR::LIR_Inst* pc) {
    RegisterValue buf = registers[pc->a];
    
    // TODO: Extract size from buffer frame
    // For now, return 0
    registers[pc->dst] = BOX_INT(0);
}

// Buffer operations - get pointer from buffer
void RegisterVM::execute_construct_buffer_as_ptr(const LIR::LIR_Inst* pc) {
    RegisterValue buf = registers[pc->a];
    
    if (!IS_PTR(buf)) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // TODO: Extract pointer from buffer frame
    // For now, just pass through
    registers[pc->dst] = buf;
}

// CString wrapper - create wrapper from pointer
void RegisterVM::execute_construct_cstring_from_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[pc->a]);
    
    // TODO: Create CString frame wrapping this pointer
    // For now, just return the pointer
    registers[pc->dst] = BOX_PTR(ptr);
}

// CString wrapper - extract pointer from wrapper
void RegisterVM::execute_construct_cstring_ptr(const LIR::LIR_Inst* pc) {
    RegisterValue cstr_obj = registers[pc->a];
    
    if (!IS_PTR(cstr_obj)) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // TODO: Extract ptr field from CString frame
    // For now, just pass through
    registers[pc->dst] = cstr_obj;
}

// Main construction dispatcher
// This handles all data construction operations (strings, buffers, wrappers, etc.)
void RegisterVM::execute_construction(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // String construction
        case LIR::LIR_Op::FFIFromCString:
            execute_construct_string_from_cstr(pc);
            break;
        case LIR::LIR_Op::FFIToCString:
            execute_construct_cstr_from_string(pc);
            break;
        case LIR::LIR_Op::FFIFreeCString:
            execute_construct_free_cstr(pc);
            break;
        
        // Buffer construction
        case LIR::LIR_Op::FFIBufferAlloc:
            execute_construct_buffer_alloc(pc);
            break;
        case LIR::LIR_Op::FFIBufferFromPtr:
            execute_construct_buffer_from_ptr(pc);
            break;
        case LIR::LIR_Op::FFIBufferCapacity:
            execute_construct_buffer_capacity(pc);
            break;
        case LIR::LIR_Op::FFIBufferSize:
            execute_construct_buffer_size(pc);
            break;
        case LIR::LIR_Op::FFIBufferAsPtr:
            execute_construct_buffer_as_ptr(pc);
            break;
        case LIR::LIR_Op::FFIBufferFree:
            // Free buffer memory
            registers[pc->dst] = registers[pc->a]; // Pass through for now
            break;
        
        // CString wrapper construction
        case LIR::LIR_Op::FFICStringFromPtr:
            execute_construct_cstring_from_ptr(pc);
            break;
        case LIR::LIR_Op::FFICStringPtr:
            execute_construct_cstring_ptr(pc);
            break;
        
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
