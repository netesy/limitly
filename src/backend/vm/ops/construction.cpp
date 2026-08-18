#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"

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
    LmBox* box = lm_box_string(cstr);
    registers[pc->dst] = BOX_PTR(box);
    
    if (box && !vm_region_stack.empty()) {
        uintptr_t ptr = reinterpret_cast<uintptr_t>(box);
        vm_allocation_regions[ptr] = active_region_id;
    }
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
    if (header->type_id != TYPE_BOX || reinterpret_cast<LmBox*>(header)->type != LM_BOX_STRING) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Get the string data pointer
    LmBox* box = reinterpret_cast<LmBox*>(header);
    const char* cstr = (const char*)box->value.as_ptr;
    registers[pc->dst] = BOX_PTR((void*)cstr);
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
        // String construction - using Marshal operations
        case LIR::LIR_Op::Marshal:
            // Dispatch based on marshal type in imm field
            switch (pc->imm) {
                case static_cast<uint32_t>(LIR::Metadata::MarshalType::CStringToString):
                    execute_construct_string_from_cstr(pc);
                    break;
                case static_cast<uint32_t>(LIR::Metadata::MarshalType::StringToCString):
                    execute_construct_cstr_from_string(pc);
                    break;
                default:
                    break;
            }
            break;
        
        // Buffer construction
        case LIR::LIR_Op::BufferCreate:
            execute_construct_buffer_alloc(pc);
            break;
        case LIR::LIR_Op::BufferView:
            execute_construct_buffer_from_ptr(pc);
            break;
        case LIR::LIR_Op::MemoryFree:
            // Free buffer memory
            if (IS_PTR(registers[pc->a])) {
                void* ptr = UNBOX_PTR(registers[pc->a]);
                if (ptr) {
                    std::free(ptr);
                }
            }
            registers[pc->dst] = registers[pc->a];
            break;
        
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
