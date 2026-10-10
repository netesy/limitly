#include "../register.hh"
#include "../../../memory/memory.hh"
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

    size_t checked_size(int64_t size) {
        return size > 0 ? static_cast<size_t>(size) : 0;
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
    void* dest = value_to_ptr(registers[pc->a]);
    void* src = (pc->b != UINT32_MAX) ? value_to_ptr(registers[pc->b]) : nullptr;
    size_t n = 0;
    if (pc->call_args.size() >= 3) {
        n = checked_size(to_int(registers[pc->call_args[2]]));
    } else if (!pc->call_args.empty() && pc->call_args[0] != UINT32_MAX) {
        n = checked_size(to_int(registers[pc->call_args[0]]));
    }
    if (dest && src && n > 0) std::memcpy(dest, src, n);
}

void RegisterVM::execute_memory_fill(const LIR::LIR_Inst* pc) {
    void* dest = value_to_ptr(registers[pc->a]);
    int value = (pc->b != UINT32_MAX) ? static_cast<int>(to_int(registers[pc->b])) : 0;
    size_t n = 0;
    if (pc->call_args.size() >= 3) {
        n = checked_size(to_int(registers[pc->call_args[2]]));
    } else if (!pc->call_args.empty() && pc->call_args[0] != UINT32_MAX) {
        n = checked_size(to_int(registers[pc->call_args[0]]));
    }
    if (dest && n > 0) std::memset(dest, value, n);
}

void RegisterVM::execute_memory_compare(const LIR::LIR_Inst* pc) {
    void* s1 = value_to_ptr(registers[pc->a]);
    void* s2 = (pc->b != UINT32_MAX) ? value_to_ptr(registers[pc->b]) : nullptr;
    size_t n = 0;
    if (pc->call_args.size() >= 3) {
        n = checked_size(to_int(registers[pc->call_args[2]]));
    } else if (!pc->call_args.empty() && pc->call_args[0] != UINT32_MAX) {
        n = checked_size(to_int(registers[pc->call_args[0]]));
    }
    if (s1 && s2 && n > 0) {
        int result = std::memcmp(s1, s2, n);
        registers[pc->dst] = BOX_INT(static_cast<int64_t>(result));
    } else registers[pc->dst] = BOX_INT(0);
}

void RegisterVM::index_raw_alias(uintptr_t pointer) {
    auto* wrapper = reinterpret_cast<ObjForeignPtr*>(pointer);
    if (wrapper->ptr) raw_aliases.emplace(reinterpret_cast<uintptr_t>(wrapper->ptr), pointer);
}
void RegisterVM::unindex_raw_alias(uintptr_t pointer) {
    auto* wrapper = reinterpret_cast<ObjForeignPtr*>(pointer);
    if (!wrapper->ptr) return; // Invalidated aliases were already removed.
    auto [begin, end] = raw_aliases.equal_range(reinterpret_cast<uintptr_t>(wrapper->ptr));
    for (auto it = begin; it != end; ++it) {
        if (it->second == pointer) { raw_aliases.erase(it); return; }
    }
}
void RegisterVM::invalidate_raw_aliases(uintptr_t address, size_t size) {
    auto it = raw_aliases.lower_bound(address);
    while (it != raw_aliases.end() && it->first - address <= size) {
        reinterpret_cast<ObjForeignPtr*>(it->second)->ptr = nullptr;
        it = raw_aliases.erase(it);
    }
}

// Links live in the existing ownership records; region heads need no allocation.
uintptr_t& RegisterVM::raw_head(uint64_t region) {
    return region ? region_instances.at(region).raw_head : root_raw_head;
}
void RegisterVM::attach_raw_memory(uintptr_t address, uint64_t region) {
    auto& head = raw_head(region);
    auto& record = owned_raw_memory.at(address);
    record = {region, 0, head};
    if (head) owned_raw_memory.at(head).previous = address;
    head = address;
}
void RegisterVM::detach_raw_memory(uintptr_t address) {
    const auto record = owned_raw_memory.at(address);
    if (record.previous) owned_raw_memory.at(record.previous).next = record.next;
    else raw_head(record.region) = record.next;
    if (record.next) owned_raw_memory.at(record.next).previous = record.previous;
}

void RegisterVM::export_raw_memory(RegisterVM& parent) {
    // Parent graph publication holds its heap lock. Raw ownership mutations
    // share the allocation-registry lock with alloc/free/resize/promotion.
    std::lock_guard<std::mutex> lock(g_memory_mutex);
    while (root_raw_head) {
        auto address = root_raw_head;
        detach_raw_memory(address);
        auto node = owned_raw_memory.extract(address);
        parent.owned_raw_memory.insert(std::move(node));
        parent.attach_raw_memory(address, 0);
    }
}

void RegisterVM::promote_raw_memory(void* address, uint64_t target) {
    if (!address) return;
    std::lock_guard<std::mutex> lock(g_memory_mutex);
    auto value = reinterpret_cast<uintptr_t>(address);
    size_t target_depth = target ? region_instances.at(target).depth : 0;
    // Ordered base addresses locate an interior pointer without a heap scan.
    // Preserve the existing one-past alias contract (offset == size).
    auto found = owned_raw_memory.upper_bound(value);
    if (found == owned_raw_memory.begin()) return;
    --found;
    auto base = found->first;
    auto region = found->second.region;
    auto size = g_memory_allocations.find(base);
    if (size == g_memory_allocations.end() || value - base > size->second) return;
    size_t source_depth = region ? region_instances.at(region).depth : 0;
    if (source_depth > target_depth) {
        detach_raw_memory(base);
        attach_raw_memory(base, target);
    }
}

void RegisterVM::release_region_raw_memory(uint64_t region) {
    auto& head = raw_head(region);
    if (!head) return;
    std::lock_guard<std::mutex> lock(g_memory_mutex);
    while (head) {
        auto address = head;
        head = owned_raw_memory.at(address).next;
        auto allocation = g_memory_allocations.find(address);
        if (allocation != g_memory_allocations.end()) {
            invalidate_raw_aliases(address, allocation->second);
            Memory::MemoryManager<>::Unsafe::deallocate(reinterpret_cast<void*>(address));
            g_memory_allocations.erase(allocation);
        }
        // The entire list is retiring; no surviving links need repair.
        owned_raw_memory.erase(address);
    }
}

void RegisterVM::release_raw_memory() {
    if (owned_raw_memory.empty()) return;
    std::lock_guard<std::mutex> lock(g_memory_mutex);
    for (auto [ptr, region] : owned_raw_memory) {
        auto allocation = g_memory_allocations.find(ptr);
        if (allocation != g_memory_allocations.end()) {
            invalidate_raw_aliases(ptr, allocation->second);
            Memory::MemoryManager<>::Unsafe::deallocate(reinterpret_cast<void*>(ptr));
            g_memory_allocations.erase(allocation);
        }
    }
    owned_raw_memory.clear();
    root_raw_head = 0;
    for (auto& entry : region_instances.entries) entry.second.raw_head = 0;
}

RegisterValue RegisterVM::allocate_raw_memory(size_t size) {
    void* ptr = Memory::MemoryManager<>::Unsafe::allocate(size);
    if (!ptr) return VAL_NIL;
    auto value = lm_alloc_foreign_ptr(ptr);
    if (!IS_PTR(value)) { Memory::MemoryManager<>::Unsafe::deallocate(ptr); return VAL_NIL; }
    {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        auto address = reinterpret_cast<uintptr_t>(ptr);
        g_memory_allocations[address] = size;
        owned_raw_memory.emplace(address, RawOwnership{active_region_id});
        attach_raw_memory(address, active_region_id);
    }
    register_native_allocation(value);
    return value;
}

size_t RegisterVM::raw_memory_size(RegisterValue value) {
    auto address = reinterpret_cast<uintptr_t>(value_to_ptr(value));
    std::lock_guard<std::mutex> lock(g_memory_mutex);
    auto found = g_memory_allocations.find(address);
    return found == g_memory_allocations.end() ? 0 : found->second;
}

void RegisterVM::execute_memory_alloc(const LIR::LIR_Inst* pc) {
    int64_t size = to_int(registers[pc->a]);
    registers[pc->dst] = size < 0 ? VAL_NIL : allocate_raw_memory(static_cast<size_t>(size));
}

void RegisterVM::execute_memory_free(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (ptr) {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        auto it = g_memory_allocations.find(reinterpret_cast<uintptr_t>(ptr));
        if (it == g_memory_allocations.end() || !owned_raw_memory.count(reinterpret_cast<uintptr_t>(ptr))) return;
        invalidate_raw_aliases(reinterpret_cast<uintptr_t>(ptr), it->second);
        g_memory_allocations.erase(it);
        auto address = reinterpret_cast<uintptr_t>(ptr);
        detach_raw_memory(address);
        owned_raw_memory.erase(address);
        Memory::MemoryManager<>::Unsafe::deallocate(ptr);
    }
}

void RegisterVM::execute_memory_realloc(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    int64_t size = to_int(registers[pc->b]);
    if (size < 0) { registers[pc->dst] = VAL_NIL; return; }
    if (!ptr) { registers[pc->dst] = allocate_raw_memory(static_cast<size_t>(size)); return; }
    const uintptr_t old_address = reinterpret_cast<uintptr_t>(ptr);
    if (size == 0) { execute_memory_free(pc); registers[pc->dst] = VAL_NIL; return; }
    uint64_t original_region;
    {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        auto it = g_memory_allocations.find(old_address);
        if (it == g_memory_allocations.end() || !owned_raw_memory.count(old_address)) {
            registers[pc->dst] = VAL_NIL;
            return;
        }
        original_region = owned_raw_memory.at(old_address).region;
    }
    void* new_ptr = Memory::MemoryManager<>::Unsafe::resize(ptr, size);
    if (new_ptr) {
        {
        std::lock_guard<std::mutex> lock(g_memory_mutex);
        invalidate_raw_aliases(old_address, g_memory_allocations.at(old_address));
        g_memory_allocations.erase(old_address);
        detach_raw_memory(old_address);
        // Reuse the existing map node even when realloc changes the address.
        auto node = owned_raw_memory.extract(old_address);
        node.key() = reinterpret_cast<uintptr_t>(new_ptr);
        owned_raw_memory.insert(std::move(node));
        attach_raw_memory(reinterpret_cast<uintptr_t>(new_ptr), original_region);
        g_memory_allocations[reinterpret_cast<uintptr_t>(new_ptr)] = size;
        }
        // Never acquire a parent heap lock while holding the raw registry lock.
        RegisterValue val = lm_alloc_foreign_ptr(new_ptr);
        registers[pc->dst] = val;
        // Register allocation with current active region
        register_native_allocation(registers[pc->dst]);
    } else registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_ptr_add(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_NIL; return; }
    uint8_t* p = static_cast<uint8_t*>(ptr);
    int64_t offset = to_int(registers[pc->b]);
    RegisterValue val = lm_alloc_foreign_ptr(p + offset);
    registers[pc->dst] = val;
    register_native_allocation(val);
}

void RegisterVM::execute_ptr_sub(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_NIL; return; }
    uint8_t* p = static_cast<uint8_t*>(ptr);
    int64_t offset = to_int(registers[pc->b]);
    RegisterValue val = lm_alloc_foreign_ptr(p - offset);
    registers[pc->dst] = val;
    register_native_allocation(val);
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
    if (alignment <= 0 || (alignment & (alignment - 1)) != 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    uintptr_t aligned = (addr + (alignment - 1)) & ~(alignment - 1);
    RegisterValue val = lm_alloc_foreign_ptr(reinterpret_cast<void*>(aligned));
    registers[pc->dst] = val;
    register_native_allocation(val);
}

void RegisterVM::execute_ptr_is_aligned(const LIR::LIR_Inst* pc) {
    void* ptr = value_to_ptr(registers[pc->a]);
    if (!ptr) { registers[pc->dst] = VAL_FALSE; return; }
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    int64_t alignment = to_int(registers[pc->b]);
    if (alignment <= 0 || (alignment & (alignment - 1)) != 0) {
        registers[pc->dst] = VAL_FALSE;
        return;
    }
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
