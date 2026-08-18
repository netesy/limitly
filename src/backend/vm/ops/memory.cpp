#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <mutex>
#include <iostream>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

namespace {
    std::mutex g_memory_mutex;
    std::unordered_map<uintptr_t, size_t> g_memory_allocations;

    void* value_to_ptr(RegisterValue val) {
        if (IS_PTR(val)) {
            auto* header = static_cast<ObjHeader*>(UNBOX_PTR(val));
            if (header->type_id == TYPE_FOREIGN_PTR) return ((ObjForeignPtr*)header)->ptr;
            return UNBOX_PTR(val);
        }
        if (is_integer(val)) return (void*)(uintptr_t)as_i64(val);
        return nullptr;
    }
}

void RegisterVM::execute_memory_load(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_NIL; return; }
    
    LIR::Type target_type = pc->result_type;
    if (pc->op == LIR::LIR_Op::MemoryLoad) {
        switch (pc->imm) {
            case 0: target_type = LIR::Type::I8; break;
            case 1: target_type = LIR::Type::U8; break;
            case 2: target_type = LIR::Type::I16; break;
            case 3: target_type = LIR::Type::U16; break;
            case 4: target_type = LIR::Type::I32; break;
            case 5: target_type = LIR::Type::U32; break;
            case 6: target_type = LIR::Type::I64; break;
            case 7: target_type = LIR::Type::U64; break;
            case 8: target_type = LIR::Type::F32; break;
            case 9: target_type = LIR::Type::F64; break;
            case 10: target_type = LIR::Type::Ptr; break;
        }
    }

    switch (target_type) {
        case LIR::Type::I8: registers[pc->dst] = BOX_INT(static_cast<int64_t>(*(int8_t*)ptr)); break;
        case LIR::Type::U8: registers[pc->dst] = BOX_INT(static_cast<int64_t>(*(uint8_t*)ptr)); break;
        case LIR::Type::I16: registers[pc->dst] = BOX_INT(static_cast<int64_t>(*(int16_t*)ptr)); break;
        case LIR::Type::U16: registers[pc->dst] = BOX_INT(static_cast<int64_t>(*(uint16_t*)ptr)); break;
        case LIR::Type::I32: registers[pc->dst] = BOX_INT(static_cast<int64_t>(*(int32_t*)ptr)); break;
        case LIR::Type::U32: registers[pc->dst] = BOX_INT(static_cast<int64_t>(*(uint32_t*)ptr)); break;
        case LIR::Type::I64: registers[pc->dst] = BOX_INT(*(int64_t*)ptr); break;
        case LIR::Type::U64: registers[pc->dst] = BOX_INT(static_cast<int64_t>(*(uint64_t*)ptr)); break;
        case LIR::Type::F32: registers[pc->dst] = make_float(static_cast<double>(*(float*)ptr)); break;
        case LIR::Type::F64: registers[pc->dst] = make_float(*(double*)ptr); break;
        case LIR::Type::Bool: registers[pc->dst] = *(bool*)ptr ? VAL_TRUE : VAL_FALSE; break;
        case LIR::Type::Ptr: registers[pc->dst] = lm_alloc_foreign_ptr(*(void**)ptr); break;
        default: registers[pc->dst] = VAL_NIL; break;
    }
}

void RegisterVM::execute_memory_store(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) return;
    LIR::Type value_type = pc->type_b;
    if (pc->op == LIR::LIR_Op::MemoryStore) {
        switch (pc->imm) {
            case 0: value_type = LIR::Type::I8; break;
            case 1: value_type = LIR::Type::U8; break;
            case 2: value_type = LIR::Type::I16; break;
            case 3: value_type = LIR::Type::U16; break;
            case 4: value_type = LIR::Type::I32; break;
            case 5: value_type = LIR::Type::U32; break;
            case 6: value_type = LIR::Type::I64; break;
            case 7: value_type = LIR::Type::U64; break;
            case 8: value_type = LIR::Type::F32; break;
            case 9: value_type = LIR::Type::F64; break;
            case 10: value_type = LIR::Type::Ptr; break;
        }
    }
    switch (value_type) {
        case LIR::Type::I8: *(int8_t*)ptr = static_cast<int8_t>(to_int(registers[pc->b])); break;
        case LIR::Type::U8: *(uint8_t*)ptr = static_cast<uint8_t>(to_int(registers[pc->b])); break;
        case LIR::Type::I16: *(int16_t*)ptr = static_cast<int16_t>(to_int(registers[pc->b])); break;
        case LIR::Type::U16: *(uint16_t*)ptr = static_cast<uint16_t>(to_int(registers[pc->b])); break;
        case LIR::Type::I32: *(int32_t*)ptr = static_cast<int32_t>(to_int(registers[pc->b])); break;
        case LIR::Type::U32: *(uint32_t*)ptr = static_cast<uint32_t>(to_int(registers[pc->b])); break;
        case LIR::Type::I64: *(int64_t*)ptr = to_int(registers[pc->b]); break;
        case LIR::Type::U64: *(uint64_t*)ptr = static_cast<uint64_t>(to_int(registers[pc->b])); break;
        case LIR::Type::F32: *(float*)ptr = static_cast<float>(to_float(registers[pc->b])); break;
        case LIR::Type::F64: *(double*)ptr = to_float(registers[pc->b]); break;
        case LIR::Type::Bool: *(bool*)ptr = IS_BOOL(registers[pc->b]) ? UNBOX_BOOL(registers[pc->b]) : (to_int(registers[pc->b]) != 0); break;
        case LIR::Type::Ptr: *(void**)ptr = value_to_ptr(registers[pc->b]); break;
        default: break;
    }
}

void RegisterVM::execute_memory_copy(const LIR::LIR_Inst* pc) {
    // Arg layout (set by the LIR generator for 3-arg intrinsics):
    //   pc->a            = destination pointer
    //   pc->b            = source pointer
    //   pc->call_args[0] = byte count
    // The previous implementation read dest from pc->dst (the result
    // register), which silently turned every copy into a no-op when dst
    // was unused. Read dest from pc->a instead.
    void* dest = value_to_ptr(registers[pc->a]);
    void* src = (pc->b != UINT32_MAX) ? value_to_ptr(registers[pc->b]) : nullptr;
    size_t n = (!pc->call_args.empty() && pc->call_args[0] != UINT32_MAX)
                   ? static_cast<size_t>(to_int(registers[pc->call_args[0]]))
                   : 0;
    if (dest && src && n > 0) std::memcpy(dest, src, n);
}

void RegisterVM::execute_memory_fill(const LIR::LIR_Inst* pc) {
    // Arg layout:
    //   pc->a            = destination pointer
    //   pc->b            = fill byte (int)
    //   pc->call_args[0] = byte count
    void* dest = value_to_ptr(registers[pc->a]);
    int value = (pc->b != UINT32_MAX) ? static_cast<int>(to_int(registers[pc->b])) : 0;
    size_t n = (!pc->call_args.empty() && pc->call_args[0] != UINT32_MAX)
                   ? static_cast<size_t>(to_int(registers[pc->call_args[0]]))
                   : 0;
    if (dest && n > 0) std::memset(dest, value, n);
}

void RegisterVM::execute_memory_compare(const LIR::LIR_Inst* pc) {
    // Arg layout:
    //   pc->a            = lhs pointer
    //   pc->b            = rhs pointer
    //   pc->call_args[0] = byte count
    //   pc->dst          = result register
    // The previous implementation read size from pc->imm (always a tiny
    // constant); read from the third argument register instead.
    void* s1 = value_to_ptr(registers[pc->a]);
    void* s2 = (pc->b != UINT32_MAX) ? value_to_ptr(registers[pc->b]) : nullptr;
    size_t n = (!pc->call_args.empty() && pc->call_args[0] != UINT32_MAX)
                   ? static_cast<size_t>(to_int(registers[pc->call_args[0]]))
                   : 0;
    if (s1 && s2 && n > 0) {
        int result = std::memcmp(s1, s2, n);
        registers[pc->dst] = BOX_INT(static_cast<int64_t>(result));
    } else registers[pc->dst] = BOX_INT(0);
}

void RegisterVM::execute_memory_alloc(const LIR::LIR_Inst* pc) {
    int64_t size = to_int(registers[pc->a]);
    if (size < 0) { registers[pc->dst] = VAL_NIL; return; }
    void* ptr = std::malloc(size);
    if (ptr) {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        g_memory_allocations[reinterpret_cast<uintptr_t>(ptr)] = size;
        RegisterValue val = lm_alloc_foreign_ptr(ptr);
        registers[pc->dst] = val;
        // Register allocation with current active region
        if (IS_PTR(val) && !vm_region_stack.empty()) {
            uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
            vm_allocation_regions[ptr_val] = active_region_id;
        }
    } else registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_memory_free(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (ptr) {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        g_memory_allocations.erase(reinterpret_cast<uintptr_t>(ptr));
        std::free(ptr);
    }
}

void RegisterVM::execute_memory_realloc(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { execute_memory_alloc(pc); return; }
    int64_t size = to_int(registers[pc->b]);
    if (size < 0) { registers[pc->dst] = VAL_NIL; return; }
    void* new_ptr = std::realloc(ptr, size);
    if (new_ptr) {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        g_memory_allocations.erase(reinterpret_cast<uintptr_t>(ptr));
        g_memory_allocations[reinterpret_cast<uintptr_t>(new_ptr)] = size;
        RegisterValue val = lm_alloc_foreign_ptr(new_ptr);
        registers[pc->dst] = val;
        // Register allocation with current active region
        if (IS_PTR(val) && !vm_region_stack.empty()) {
            uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
            vm_allocation_regions[ptr_val] = active_region_id;
        }
    } else registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_ptr_add(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_NIL; return; }
    uint8_t* p = static_cast<uint8_t*>(ptr);
    int64_t offset = to_int(registers[pc->b]);
    RegisterValue val = lm_alloc_foreign_ptr(p + offset);
    registers[pc->dst] = val;
    // Register allocation with current active region
    if (IS_PTR(val) && !vm_region_stack.empty()) {
        uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
        vm_allocation_regions[ptr_val] = active_region_id;
    }
}

void RegisterVM::execute_ptr_sub(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_NIL; return; }
    uint8_t* p = static_cast<uint8_t*>(ptr);
    int64_t offset = to_int(registers[pc->b]);
    RegisterValue val = lm_alloc_foreign_ptr(p - offset);
    registers[pc->dst] = val;
    // Register allocation with current active region
    if (IS_PTR(val) && !vm_region_stack.empty()) {
        uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
        vm_allocation_regions[ptr_val] = active_region_id;
    }
}

void RegisterVM::execute_ptr_diff(const LIR::LIR_Inst* pc) {
    void* p1 = value_to_ptr(registers[pc->a]);
    void* p2 = value_to_ptr(registers[pc->b]);
    if (!p1 || !p2) { registers[pc->dst] = BOX_INT(0); return; }
    registers[pc->dst] = BOX_INT(static_cast<int64_t>((uint8_t*)p1 - (uint8_t*)p2));
}

void RegisterVM::execute_ptr_align(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_NIL; return; }
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    int64_t alignment = to_int(registers[pc->b]);
    if (alignment <= 0) { registers[pc->dst] = registers[pc->a]; return; }
    uintptr_t aligned = (addr + (alignment - 1)) & ~(alignment - 1);
    RegisterValue val = lm_alloc_foreign_ptr(reinterpret_cast<void*>(aligned));
    registers[pc->dst] = val;
    // Register allocation with current active region
    if (IS_PTR(val) && !vm_region_stack.empty()) {
        uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
        vm_allocation_regions[ptr_val] = active_region_id;
    }
}

void RegisterVM::execute_ptr_is_aligned(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_FALSE; return; }
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    int64_t alignment = to_int(registers[pc->b]);
    if (alignment <= 0) { registers[pc->dst] = VAL_FALSE; return; }
    bool aligned = (addr % static_cast<uintptr_t>(alignment)) == 0;
    registers[pc->dst] = aligned ? VAL_TRUE : VAL_FALSE;
}

void RegisterVM::execute_memory(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::MemoryLoad: execute_memory_load(pc); break;
        case LIR::LIR_Op::MemoryStore: execute_memory_store(pc); break;
        case LIR::LIR_Op::MemoryCopy: execute_memory_copy(pc); break;
        case LIR::LIR_Op::MemoryFill: execute_memory_fill(pc); break;
        case LIR::LIR_Op::MemoryCompare: execute_memory_compare(pc); break;
        case LIR::LIR_Op::MemoryAlloc: execute_memory_alloc(pc); break;
        case LIR::LIR_Op::MemoryFree: execute_memory_free(pc); break;
        case LIR::LIR_Op::MemoryResize: execute_memory_realloc(pc); break;
        case LIR::LIR_Op::PtrAdd: execute_ptr_add(pc); break;
        case LIR::LIR_Op::PtrSub: execute_ptr_sub(pc); break;
        case LIR::LIR_Op::PtrDiff: execute_ptr_diff(pc); break;
        case LIR::LIR_Op::PtrAlign: execute_ptr_align(pc); break;
        case LIR::LIR_Op::PtrIsAligned: execute_ptr_is_aligned(pc); break;
        default: break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
