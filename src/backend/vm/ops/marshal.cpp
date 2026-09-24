// Marshal and Unmarshal implementations
// These are generic data conversion operations

#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Generic Marshal operation - type conversion based on imm field
void RegisterVM::execute_marshal(const LIR::LIR_Inst* pc) {
    using MT = LIR::Metadata::MarshalType;
    MT marshal_type = LIR::Metadata::extract_marshal_type(pc->imm);
    
    switch (marshal_type) {
        case MT::StringToCString:
            execute_construct_cstr_from_string(pc);
            break;
        case MT::CStringToString:
            execute_construct_string_from_cstr(pc);
            break;
        case MT::PtrToBuffer:
            execute_construct_buffer_from_ptr(pc);
            break;
        case MT::BufferToPtr:
            execute_construct_buffer_as_ptr(pc);
            break;
        case MT::IntToFloat:
            registers[pc->dst] = make_float(static_cast<double>(to_int(registers[pc->a])));
            break;
        case MT::FloatToInt:
            registers[pc->dst] = BOX_INT(static_cast<int64_t>(to_float(registers[pc->a])));
            break;
        default:
            registers[pc->dst] = VAL_NIL;
    }
}

// Generic Unmarshal operation - reverse conversion
void RegisterVM::execute_unmarshal(const LIR::LIR_Inst* pc) {
    using MT = LIR::Metadata::MarshalType;
    MT marshal_type = LIR::Metadata::extract_marshal_type(pc->imm);
    
    switch (marshal_type) {
        case MT::StringToCString:
            // Reverse: CString to String
            execute_construct_string_from_cstr(pc);
            break;
        case MT::CStringToString:
            // Reverse: String to CString
            execute_construct_cstr_from_string(pc);
            break;
        case MT::PtrToBuffer:
            // Reverse: Buffer to Ptr
            execute_construct_buffer_as_ptr(pc);
            break;
        case MT::BufferToPtr:
            // Reverse: Ptr to Buffer
            execute_construct_buffer_from_ptr(pc);
            break;
        case MT::IntToFloat:
            // Reverse: Float to Int
            registers[pc->dst] = BOX_INT(static_cast<int64_t>(to_float(registers[pc->a])));
            break;
        case MT::FloatToInt:
            // Reverse: Int to Float
            registers[pc->dst] = make_float(static_cast<double>(to_int(registers[pc->a])));
            break;
        default:
            registers[pc->dst] = VAL_NIL;
    }
}

// Buffer view - create a view into memory range
void RegisterVM::execute_buffer_view(const LIR::LIR_Inst* pc) {
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
    
    // For now, just return pointer
    registers[pc->dst] = BOX_PTR(ptr);
}

// Buffer create - allocate new buffer
void RegisterVM::execute_buffer_create(const LIR::LIR_Inst* pc) {
    execute_construct_buffer_alloc(pc);
}

// Buffer resize - resize existing buffer
void RegisterVM::execute_buffer_resize(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[pc->a]);
    int64_t new_size = to_int(registers[pc->b]);
    
    if (new_size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* new_ptr = std::realloc(ptr, new_size);
    if (new_ptr) {
        registers[pc->dst] = BOX_PTR(new_ptr);
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

// Library, Foreign Call, and Callback operations are handled in ffi.cpp

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
