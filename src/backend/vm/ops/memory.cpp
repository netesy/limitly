#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <mutex>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Memory allocation tracking - intrinsic layer
namespace {
    std::mutex g_memory_mutex;
    std::unordered_map<uintptr_t, size_t> g_memory_allocations;

    LIR::Reg arg_reg(const LIR::LIR_Inst* pc, size_t index, LIR::Reg fallback) {
        return index < pc->call_args.size() ? pc->call_args[index] : fallback;
    }
}

// ============================================================================
// PHASE 2: Generic Memory Operations with Type Dispatch
// ============================================================================

// Generic memory load - type dispatch via result_type
void RegisterVM::execute_memory_load(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[pc->a]);
    if (!ptr) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Type dispatch: interpret pointer based on result_type
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
        case LIR::Type::Bool:
            registers[pc->dst] = *(bool*)ptr ? VAL_TRUE : VAL_FALSE;
            break;
        case LIR::Type::Ptr:
            registers[pc->dst] = BOX_PTR(*(void**)ptr);
            break;
        default:
            registers[pc->dst] = VAL_NIL;
    }
}

// Generic memory store - type dispatch via type_a
void RegisterVM::execute_memory_store(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[pc->a]);
    if (!ptr) {
        return;
    }
    
    // Type dispatch: store value at pointer based on type_a
    switch (pc->type_a) {
        case LIR::Type::I32: {
            int32_t value = static_cast<int32_t>(to_int(registers[pc->b]));
            *(int32_t*)ptr = value;
            break;
        }
        case LIR::Type::I64: {
            int64_t value = to_int(registers[pc->b]);
            *(int64_t*)ptr = value;
            break;
        }
        case LIR::Type::F64: {
            double value = to_float(registers[pc->b]);
            *(double*)ptr = value;
            break;
        }
        case LIR::Type::Bool: {
            // Extract boolean from value - use inline conversion
            bool value = IS_BOOL(registers[pc->b]) ? UNBOX_BOOL(registers[pc->b]) : (to_int(registers[pc->b]) != 0);
            *(bool*)ptr = value;
            break;
        }
        case LIR::Type::Ptr: {
            void* value = IS_PTR(registers[pc->b]) ? UNBOX_PTR(registers[pc->b]) : nullptr;
            *(void**)ptr = value;
            break;
        }
        default:
            break;
    }
}

// Bulk memory operations
void RegisterVM::execute_memory_copy(const LIR::LIR_Inst* pc) {
    execute_memory_memcpy(pc);  // Delegate to existing impl
}

void RegisterVM::execute_memory_fill(const LIR::LIR_Inst* pc) {
    execute_memory_memset(pc);  // Delegate to existing impl
}

void RegisterVM::execute_memory_compare(const LIR::LIR_Inst* pc) {
    execute_memory_memcmp(pc);  // Delegate to existing impl
}

// Pointer operations with generic names
void RegisterVM::execute_ptr_add(const LIR::LIR_Inst* pc) {
    execute_memory_add_ptr(pc);  // Delegate to existing impl
}

void RegisterVM::execute_ptr_sub(const LIR::LIR_Inst* pc) {
    execute_memory_sub_ptr(pc);  // Delegate to existing impl
}

void RegisterVM::execute_ptr_diff(const LIR::LIR_Inst* pc) {
    execute_memory_ptr_diff(pc);  // Delegate to existing impl
}

void RegisterVM::execute_ptr_align(const LIR::LIR_Inst* pc) {
    execute_memory_align_ptr(pc);  // Delegate to existing impl
}

void RegisterVM::execute_ptr_is_aligned(const LIR::LIR_Inst* pc) {
    execute_memory_is_aligned(pc);  // Delegate to existing impl
}

// Memory deallocation - intrinsic
void RegisterVM::execute_memory_free(const LIR::LIR_Inst* pc) {
    LIR::Reg ptr_reg = arg_reg(pc, 0, pc->a);
    if (!IS_PTR(registers[ptr_reg])) {
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[ptr_reg]);
    if (ptr) {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        auto it = g_memory_allocations.find(reinterpret_cast<uintptr_t>(ptr));
        if (it != g_memory_allocations.end()) {
            g_memory_allocations.erase(it);
            std::free(ptr);
        }
    }
}

// Memory resizing - intrinsic
void RegisterVM::execute_memory_realloc(const LIR::LIR_Inst* pc) {
    LIR::Reg ptr_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg size_reg = arg_reg(pc, 1, pc->b);
    if (!IS_PTR(registers[ptr_reg])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[ptr_reg]);
    int64_t new_size = to_int(registers[size_reg]);
    
    if (new_size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* new_ptr = std::realloc(ptr, new_size);
    if (new_ptr) {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        g_memory_allocations.erase(reinterpret_cast<uintptr_t>(ptr));
        g_memory_allocations[reinterpret_cast<uintptr_t>(new_ptr)] = new_size;
        registers[pc->dst] = BOX_PTR(new_ptr);
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

// Bulk memory copy - intrinsic
void RegisterVM::execute_memory_memcpy(const LIR::LIR_Inst* pc) {
    LIR::Reg dest_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg src_reg = arg_reg(pc, 1, pc->b);
    LIR::Reg size_reg = arg_reg(pc, 2, pc->dst);
    if (!IS_PTR(registers[dest_reg]) || !IS_PTR(registers[src_reg])) {
        return;
    }
    
    void* dest = UNBOX_PTR(registers[dest_reg]);
    void* src = UNBOX_PTR(registers[src_reg]);
    int64_t size = to_int(registers[size_reg]);
    
    if (dest && src && size > 0) {
        std::memcpy(dest, src, size);
    }
}

// Bulk memory fill - intrinsic
void RegisterVM::execute_memory_memset(const LIR::LIR_Inst* pc) {
    LIR::Reg ptr_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg value_reg = arg_reg(pc, 1, pc->b);
    LIR::Reg size_reg = arg_reg(pc, 2, pc->dst);
    if (!IS_PTR(registers[ptr_reg])) {
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[ptr_reg]);
    int64_t value = to_int(registers[value_reg]);
    int64_t size = to_int(registers[size_reg]);
    
    if (ptr && size > 0) {
        std::memset(ptr, static_cast<int>(value), size);
    }
}

// Bulk memory comparison - intrinsic
void RegisterVM::execute_memory_memcmp(const LIR::LIR_Inst* pc) {
    LIR::Reg lhs_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg rhs_reg = arg_reg(pc, 1, pc->b);
    LIR::Reg size_reg = arg_reg(pc, 2, pc->imm);
    if (!IS_PTR(registers[lhs_reg]) || !IS_PTR(registers[rhs_reg])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    void* ptr1 = UNBOX_PTR(registers[lhs_reg]);
    void* ptr2 = UNBOX_PTR(registers[rhs_reg]);
    int64_t size = to_int(registers[size_reg]);
    
    if (ptr1 && ptr2 && size > 0) {
        int result = std::memcmp(ptr1, ptr2, size);
        registers[pc->dst] = BOX_INT(result);
    } else {
        registers[pc->dst] = BOX_INT(0);
    }
}

// Pointer arithmetic - intrinsic
void RegisterVM::execute_memory_add_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t offset = to_int(registers[pc->b]);
    uintptr_t result = ptr + static_cast<uintptr_t>(offset);
    registers[pc->dst] = BOX_PTR(reinterpret_cast<void*>(result));
}

// Pointer subtraction - intrinsic
void RegisterVM::execute_memory_sub_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t offset = to_int(registers[pc->b]);
    uintptr_t result = ptr - static_cast<uintptr_t>(offset);
    registers[pc->dst] = BOX_PTR(reinterpret_cast<void*>(result));
}

// Pointer difference - intrinsic
void RegisterVM::execute_memory_ptr_diff(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a]) || !IS_PTR(registers[pc->b])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    uintptr_t ptr1 = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    uintptr_t ptr2 = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->b]));
    int64_t diff = static_cast<int64_t>(ptr1 - ptr2);
    registers[pc->dst] = BOX_INT(diff);
}

// Pointer alignment calculation - intrinsic
void RegisterVM::execute_memory_align_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t alignment = to_int(registers[pc->b]);
    
    if (alignment <= 0 || (alignment & (alignment - 1)) != 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t aligned = (ptr + alignment - 1) & ~(alignment - 1);
    registers[pc->dst] = BOX_PTR(reinterpret_cast<void*>(aligned));
}

// Pointer alignment check - intrinsic
void RegisterVM::execute_memory_is_aligned(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_FALSE;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t alignment = to_int(registers[pc->b]);
    
    if (alignment <= 0) {
        registers[pc->dst] = VAL_FALSE;
        return;
    }
    
    bool aligned = (ptr % static_cast<uintptr_t>(alignment)) == 0;
    registers[pc->dst] = aligned ? VAL_TRUE : VAL_FALSE;
}

// Type-specific load operations - intrinsic
void RegisterVM::execute_memory_load_int8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    int8_t* ptr = static_cast<int8_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_memory_load_uint8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    uint8_t* ptr = static_cast<uint8_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_memory_load_int16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    int16_t* ptr = static_cast<int16_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_memory_load_uint16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    uint16_t* ptr = static_cast<uint16_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_memory_load_int32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    int32_t* ptr = static_cast<int32_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_memory_load_uint32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    uint32_t* ptr = static_cast<uint32_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_memory_load_int64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    int64_t* ptr = static_cast<int64_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(*ptr);
}

void RegisterVM::execute_memory_load_uint64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    uint64_t* ptr = static_cast<uint64_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_memory_load_float(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = make_float(0.0);
        return;
    }
    float* ptr = static_cast<float*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = make_float(static_cast<double>(*ptr));
}

void RegisterVM::execute_memory_load_double(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = make_float(0.0);
        return;
    }
    double* ptr = static_cast<double*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = make_float(*ptr);
}

void RegisterVM::execute_memory_load_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    void** ptr = static_cast<void**>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_PTR(*ptr);
}

// Type-specific store operations - intrinsic
void RegisterVM::execute_memory_store_int8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    int8_t* ptr = static_cast<int8_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<int8_t>(to_int(registers[pc->a]));
}

void RegisterVM::execute_memory_store_uint8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    uint8_t* ptr = static_cast<uint8_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<uint8_t>(to_int(registers[pc->a]));
}

void RegisterVM::execute_memory_store_int16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    int16_t* ptr = static_cast<int16_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<int16_t>(to_int(registers[pc->a]));
}

void RegisterVM::execute_memory_store_uint16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    uint16_t* ptr = static_cast<uint16_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<uint16_t>(to_int(registers[pc->a]));
}

void RegisterVM::execute_memory_store_int32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    int32_t* ptr = static_cast<int32_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<int32_t>(to_int(registers[pc->a]));
}

void RegisterVM::execute_memory_store_uint32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    uint32_t* ptr = static_cast<uint32_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<uint32_t>(to_int(registers[pc->a]));
}

void RegisterVM::execute_memory_store_int64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    int64_t* ptr = static_cast<int64_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = to_int(registers[pc->a]);
}

void RegisterVM::execute_memory_store_uint64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    uint64_t* ptr = static_cast<uint64_t*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<uint64_t>(to_int(registers[pc->a]));
}

void RegisterVM::execute_memory_store_float(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    float* ptr = static_cast<float*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = static_cast<float>(to_float(registers[pc->a]));
}

void RegisterVM::execute_memory_store_double(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    double* ptr = static_cast<double*>(UNBOX_PTR(registers[pc->dst]));
    *ptr = to_float(registers[pc->a]);
}

void RegisterVM::execute_memory_store_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) return;
    void** ptr = static_cast<void**>(UNBOX_PTR(registers[pc->dst]));
    *ptr = IS_PTR(registers[pc->a]) ? UNBOX_PTR(registers[pc->a]) : nullptr;
}

// Backward compatibility stubs - delegate to existing alloc/free/realloc implementations

void RegisterVM::execute_memory_alloc(const LIR::LIR_Inst* pc) {
    // Allocate memory and track it
    int64_t size = to_int(registers[pc->a]);
    if (size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = std::malloc(size);
    if (ptr) {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        g_memory_allocations[reinterpret_cast<uintptr_t>(ptr)] = size;
        registers[pc->dst] = BOX_PTR(ptr);
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

// Main memory intrinsics dispatcher
void RegisterVM::execute_memory(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // === NEW: Generic memory operations with type dispatch ===
        case LIR::LIR_Op::MemoryLoad:
            execute_memory_load(pc);
            break;
        case LIR::LIR_Op::MemoryStore:
            execute_memory_store(pc);
            break;
        case LIR::LIR_Op::MemoryCopy:
        case LIR::LIR_Op::FFIMemcpy:
            execute_memory_memcpy(pc);
            break;
        case LIR::LIR_Op::MemoryFill:
        case LIR::LIR_Op::FFIMemset:
            execute_memory_memset(pc);
            break;
        case LIR::LIR_Op::MemoryCompare:
        case LIR::LIR_Op::FFIMemcmp:
            execute_memory_memcmp(pc);
            break;
        case LIR::LIR_Op::MemoryAlloc:
        case LIR::LIR_Op::FFIAlloc:
            execute_memory_alloc(pc);
            break;
        case LIR::LIR_Op::MemoryFree:
        case LIR::LIR_Op::FFIFree:
            execute_memory_free(pc);
            break;
        case LIR::LIR_Op::MemoryResize:
        case LIR::LIR_Op::FFIRealloc:
            execute_memory_realloc(pc);
            break;
        
        // === NEW: Generic pointer operations ===
        case LIR::LIR_Op::PtrAdd:
        case LIR::LIR_Op::FFIAddPtr:
            execute_memory_add_ptr(pc);
            break;
        case LIR::LIR_Op::PtrSub:
        case LIR::LIR_Op::FFISubPtr:
            execute_memory_sub_ptr(pc);
            break;
        case LIR::LIR_Op::PtrDiff:
        case LIR::LIR_Op::FFIPtrDiff:
            execute_memory_ptr_diff(pc);
            break;
        case LIR::LIR_Op::PtrAlign:
        case LIR::LIR_Op::FFIAlignPtr:
            execute_memory_align_ptr(pc);
            break;
        case LIR::LIR_Op::PtrIsAligned:
        case LIR::LIR_Op::FFIIsAligned:
            execute_memory_is_aligned(pc);
            break;
        
        // Load/Store operations now use generic type dispatch
        case LIR::LIR_Op::FFILoadInt8:
        case LIR::LIR_Op::FFILoadUInt8:
        case LIR::LIR_Op::FFILoadInt16:
        case LIR::LIR_Op::FFILoadUInt16:
        case LIR::LIR_Op::FFILoadInt32:
        case LIR::LIR_Op::FFILoadUInt32:
        case LIR::LIR_Op::FFILoadInt64:
        case LIR::LIR_Op::FFILoadUInt64:
        case LIR::LIR_Op::FFILoadFloat:
        case LIR::LIR_Op::FFILoadDouble:
        case LIR::LIR_Op::FFILoadPtr:
            execute_memory_load(pc);
            break;
        
        case LIR::LIR_Op::FFIStoreInt8:
        case LIR::LIR_Op::FFIStoreUInt8:
        case LIR::LIR_Op::FFIStoreInt16:
        case LIR::LIR_Op::FFIStoreUInt16:
        case LIR::LIR_Op::FFIStoreInt32:
        case LIR::LIR_Op::FFIStoreUInt32:
        case LIR::LIR_Op::FFIStoreInt64:
        case LIR::LIR_Op::FFIStoreUInt64:
        case LIR::LIR_Op::FFIStoreFloat:
        case LIR::LIR_Op::FFIStoreDouble:
        case LIR::LIR_Op::FFIStorePtr:
            execute_memory_store(pc);
            break;
        
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
