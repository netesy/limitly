#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include <cstring>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Data construction layer - operations for creating/viewing data structures
// This layer includes: strings, buffers, wrappers, and other constructed types

// String conversion - construct Lymar string from C pointer
void RegisterVM::execute_construct_string_from_cstr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    auto* input = static_cast<ObjHeader*>(UNBOX_PTR(registers[pc->a]));
    const char* cstr = input->type_id == TYPE_FOREIGN_PTR ? static_cast<const char*>(reinterpret_cast<ObjForeignPtr*>(input)->ptr) : nullptr;
    if (!cstr) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Convert C string to Lymar string using runtime support
    LmBox* box = lm_box_string(cstr);
    registers[pc->dst] = BOX_PTR(box);
    
    register_native_allocation(registers[pc->dst]);
}

// String conversion - construct C pointer view from Lymar string
void RegisterVM::execute_construct_cstr_from_string(const LIR::LIR_Inst* pc) {
    auto value = registers[pc->a];
    if (!IS_PTR(value)) { registers[pc->dst] = VAL_NIL; return; }
    auto* header = static_cast<ObjHeader*>(UNBOX_PTR(value));
    const char* data = nullptr;
    size_t size = 0;
    if (header->type_id == TYPE_STRING) {
        auto* str = reinterpret_cast<LmStringHeader*>(header); data = str->data; size = str->len;
    } else if (header->type_id == TYPE_BOX && reinterpret_cast<LmBox*>(header)->type == LM_BOX_STRING) {
        data = static_cast<const char*>(reinterpret_cast<LmBox*>(header)->value.as_ptr);
        size = data ? std::strlen(data) : 0;
    } else { registers[pc->dst] = VAL_NIL; return; }
    auto result = allocate_raw_memory(size + 1);
    if (IS_PTR(result)) {
        auto* raw = static_cast<ObjForeignPtr*>(UNBOX_PTR(result));
        if (size) std::memcpy(raw->ptr, data, size);
        static_cast<char*>(raw->ptr)[size] = '\0';
    }
    registers[pc->dst] = result;
}

void RegisterVM::execute_construct_free_cstr(const LIR::LIR_Inst* pc) { execute_memory_free(pc); }

void RegisterVM::execute_construct_buffer_alloc(const LIR::LIR_Inst* pc) { execute_memory_alloc(pc); }

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
    registers[pc->dst] = make_i64(raw_memory_size(buf));
}

// Buffer operations - get size of buffer
void RegisterVM::execute_construct_buffer_size(const LIR::LIR_Inst* pc) {
    RegisterValue buf = registers[pc->a];
    
    // TODO: Extract size from buffer frame
    // For now, return 0
    registers[pc->dst] = make_i64(raw_memory_size(buf));
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
