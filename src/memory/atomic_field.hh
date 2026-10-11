#pragma once
#include <atomic>
#include <cstdint>
#include <mutex>

namespace LM::Memory {
// No frame-layout or per-object allocation changes. Every atomic writer uses
// the same stripe so a allocating numeric RMW cannot lose a concurrent store.
inline std::mutex& atomic_field_mutex(const void* address) {
    static std::mutex stripes[64];
    return stripes[(reinterpret_cast<uintptr_t>(address) >> 3) % 64];
}
inline uint64_t atomic_field_load(uint64_t* address) {
    return std::atomic_ref<uint64_t>(*address).load(std::memory_order_seq_cst);
}
inline void atomic_field_store(uint64_t* address, uint64_t value) {
    std::lock_guard lock(atomic_field_mutex(address));
    std::atomic_ref<uint64_t>(*address).store(value, std::memory_order_seq_cst);
}
template<class Update> uint64_t atomic_field_update(uint64_t* address, Update update) {
    std::lock_guard lock(atomic_field_mutex(address));
    auto value = update(atomic_field_load(address));
    std::atomic_ref<uint64_t>(*address).store(value, std::memory_order_seq_cst);
    return value;
}
}
