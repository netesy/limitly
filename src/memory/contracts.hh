#pragma once
#include "model.hh"
#include <cstdint>
#include <atomic>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace LM::Memory {
// Capability tokens are never pointer values. A new capability has a globally
// unique identity across runtime registries, including after reset/address reuse.
// Registries are confined to an owning VM/thread; sharing requires its lock.
class LifetimeRegistry {
    struct Allocation { uint64_t generation; uint64_t readers = 0; bool writer = false; };
    struct Reference {
        uintptr_t address;
        uint64_t generation, region, previous = 0, next = 0;
        bool writable;
    };
    std::unordered_map<uintptr_t, Allocation> allocations_;
    std::unordered_map<uint64_t, Reference> references_;
    std::unordered_map<uint64_t, uint64_t> region_heads_;
    static uint64_t fresh() {
        // Shared identities also reject tokens supplied to another VM/thread.
        // Saturating CAS refuses exhaustion without ever wrapping the counter.
        static std::atomic<uint64_t> sequence{1};
        auto candidate = sequence.load(std::memory_order_relaxed);
        for (;;) {
            if (candidate == std::numeric_limits<uint64_t>::max())
                throw std::overflow_error("Memory capability identity exhausted");
            if (sequence.compare_exchange_weak(candidate, candidate + 1,
                    std::memory_order_relaxed, std::memory_order_relaxed)) return candidate;
        }
    }

public:
    void adopt(uintptr_t address) {
        if (!address || allocations_.count(address)) return;
        allocations_.emplace(address, Allocation{fresh()});
    }
    void revoke(uintptr_t address) { allocations_.erase(address); }
    void reset() { allocations_.clear(); references_.clear(); region_heads_.clear(); } // capability identities never reset
    uint64_t borrow(uintptr_t address, bool writable, uint64_t region = 0) {
        auto found = allocations_.find(address);
        if (found == allocations_.end()) throw std::runtime_error("Borrow of unowned allocation");
        auto& allocation = found->second;
        if (allocation.writer || (writable && allocation.readers))
            throw std::runtime_error("Conflicting memory borrow");
        auto token = fresh();
        auto [head, inserted] = region_heads_.try_emplace(region, 0);
        try { references_.emplace(token, Reference{address, allocation.generation, region, 0, head->second, writable}); }
        catch (...) { if (inserted) region_heads_.erase(head); throw; }
        if (head->second) references_.at(head->second).previous = token;
        head->second = token;
        if (writable) allocation.writer = true; else ++allocation.readers;
        return token;
    }
    uintptr_t resolve(uint64_t token, bool write = false) const {
        auto ref = references_.find(token);
        if (ref == references_.end()) throw std::runtime_error("Invalid memory reference");
        auto allocation = allocations_.find(ref->second.address);
        if (allocation == allocations_.end() || !same_generation(ref->second.generation, allocation->second.generation))
            throw std::runtime_error("Expired memory reference");
        if (write && !ref->second.writable) throw std::runtime_error("Write through immutable borrow");
        return ref->second.address;
    }
    void end_borrow(uint64_t token) {
        auto ref = references_.find(token);
        if (ref == references_.end()) throw std::runtime_error("Invalid memory reference release");
        auto allocation = allocations_.find(ref->second.address);
        if (allocation != allocations_.end() && same_generation(ref->second.generation, allocation->second.generation)) {
            if (ref->second.writable) allocation->second.writer = false;
            else --allocation->second.readers;
        }
        auto scope = ref->second.region;
        auto previous = ref->second.previous, next = ref->second.next;
        if (previous) references_.at(previous).next = next;
        else if (next) region_heads_.at(scope) = next;
        else region_heads_.erase(scope);
        if (next) references_.at(next).previous = previous;
        references_.erase(ref);
    }
    void end_region(uint64_t region) {
        for (;;) {
            auto head = region_heads_.find(region);
            if (head == region_heads_.end()) return;
            end_borrow(head->second);
        }
    }
    uint64_t reference_region(uint64_t token) const {
        (void)resolve(token);
        return references_.at(token).region;
    }
    uint64_t move_reference(uint64_t token, uint64_t region) {
        auto address = resolve(token);
        auto writable = references_.at(token).writable;
        end_borrow(token);
        return borrow(address, writable, region);
    }
    void consume(uintptr_t address) {
        auto found = allocations_.find(address);
        if (found == allocations_.end()) throw std::runtime_error("Consume of unowned allocation");
        if (found->second.writer || found->second.readers)
            throw std::runtime_error("Consume while borrowed");
        found->second.generation = fresh();
    }
};
} // namespace LM::Memory
