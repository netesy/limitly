#pragma once

#include "analyzer.hh"
#include "contracts.hh"
#include <array>
#include <limits>
#include <functional>
#include <algorithm>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <new>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define TRACE_INFO() (std::string(__FUNCTION__) + " at line " + TOSTRING(__LINE__))

namespace LM {
namespace Memory {

constexpr size_t MIN_ALLOC_SIZE = 4;
constexpr size_t MAX_ALLOC_SIZE = 256;
constexpr size_t POOL_CHUNK_SIZE = 128;  // Reduced from 256
constexpr size_t LARGE_ALLOC_THRESHOLD = 512;  // New threshold for large allocations

// Private allocator prefix; canonical language object headers remain unchanged.
struct alignas(std::max_align_t) AllocationHeader {
    size_t size;
    uint16_t poolIndex;      // 2 bytes (which pool this came from)
    uint16_t flags;          // 2 bytes (alignment, etc.)
    void* base;
};

class MemoryPool {
private:
    std::vector<void*> freeBlocks;
    std::vector<void*> allocatedChunks;  // Track chunks for cleanup
    size_t blockSize;
    size_t freeCount;

    // Use a simple spinlock for better performance
    std::atomic_flag lock = ATOMIC_FLAG_INIT;

    void spinLock() {
        while (lock.test_and_set(std::memory_order_acquire)) {
            // Spin
        }
    }

    void spinUnlock() {
        lock.clear(std::memory_order_release);
    }

public:
    MemoryPool(size_t blockSize, size_t initialSize)
        : blockSize(blockSize), freeCount(0) {
        freeBlocks.reserve(initialSize);
        expandPool(initialSize);
    }

    ~MemoryPool() {
        for (void* chunk : allocatedChunks) {
            std::free(chunk);
        }
    }

    void expandPool(size_t count) {
        // Allocate one large chunk and subdivide it
        size_t chunkSize = blockSize * count;
        void* chunk = std::malloc(chunkSize);
        if (!chunk) return;

        allocatedChunks.push_back(chunk);

        // Subdivide the chunk into blocks
        char* ptr = static_cast<char*>(chunk);
        for (size_t i = 0; i < count; ++i) {
            freeBlocks.push_back(ptr);
            ptr += blockSize;
        }
        freeCount += count;
    }

    void* allocate() {
        spinLock();

        if (freeBlocks.empty()) {

            // Expand pool by 50% when exhausted
            size_t expandSize = std::max(size_t(32), allocatedChunks.size() * POOL_CHUNK_SIZE / 2);
            try { expandPool(expandSize); }
            catch (...) { spinUnlock(); throw; }

            if (freeBlocks.empty()) {
                spinUnlock();
                return nullptr;
            }
        }

        void* block = freeBlocks.back();
        freeBlocks.pop_back();
        freeCount--;

        spinUnlock();
        return block;
    }

    void deallocate(void* ptr) {
        if (!ptr) return;

        spinLock();
        try { freeBlocks.push_back(ptr); }
        catch (...) { spinUnlock(); throw; }
        freeCount++;
        spinUnlock();
    }

    size_t getFreeCount() const { return freeCount; }
    size_t getBlockSize() const { return blockSize; }
};

class DefaultAllocator {
private:
    static constexpr size_t NUM_POOLS = 7;  // 4, 8, 16, 32, 64, 128, 256 bytes
    std::array<std::unique_ptr<MemoryPool>, NUM_POOLS> memoryPools;

    // Size to pool index lookup
    uint8_t sizeToPoolIndex(size_t size) const {
        if (size <= 4) return 0;
        if (size <= 8) return 1;
        if (size <= 16) return 2;
        if (size <= 32) return 3;
        if (size <= 64) return 4;
        if (size <= 128) return 5;
        if (size <= 256) return 6;
        return 255;  // Not in pool
    }

public:
    DefaultAllocator() {
        size_t poolSize = MIN_ALLOC_SIZE;
        for (size_t i = 0; i < NUM_POOLS; ++i) {
            memoryPools[i] = std::make_unique<MemoryPool>(poolSize, POOL_CHUNK_SIZE);
            poolSize *= 2;
        }
    }

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
        // Add header size
        if (!alignment || (alignment & (alignment - 1))) throw std::invalid_argument("Invalid allocation alignment");
        alignment = std::max(alignment, alignof(std::max_align_t));
        if (size > SIZE_MAX - sizeof(AllocationHeader) - alignment) throw std::bad_alloc();
        size_t totalSize = size + sizeof(AllocationHeader);
        if (alignment > alignof(std::max_align_t)) {
            auto base = std::malloc(totalSize + alignment);
            if (!base) return nullptr;
            auto address = (reinterpret_cast<uintptr_t>(base) + sizeof(AllocationHeader) + alignment - 1) & ~(alignment - 1);
            auto* header = reinterpret_cast<AllocationHeader*>(address) - 1;
            header->size = size; header->poolIndex = 255; header->flags = 0; header->base = base;
            return reinterpret_cast<void*>(address);
        }

        uint8_t poolIdx = sizeToPoolIndex(totalSize);

        void* mem = nullptr;
        if (poolIdx < NUM_POOLS) {
            mem = memoryPools[poolIdx]->allocate();
        }

        if (!mem) {
            // Fallback to system allocator for large allocations
            mem = std::malloc(totalSize);
            if (!mem) return nullptr;
            poolIdx = 255;  // Mark as system allocated
        }

        // Setup header
        AllocationHeader* header = static_cast<AllocationHeader*>(mem);
        header->size = size;
        header->poolIndex = poolIdx;
        header->flags = 0;
        header->base = mem;

        // Return pointer after header
        return static_cast<char*>(mem) + sizeof(AllocationHeader);
    }

    void deallocate(void* ptr, size_t size) {
        if (!ptr) return;

        // Get header
        void* mem = static_cast<char*>(ptr) - sizeof(AllocationHeader);
        AllocationHeader* header = static_cast<AllocationHeader*>(mem);

        uint8_t poolIdx = header->poolIndex;

        if (poolIdx < NUM_POOLS) {
            memoryPools[poolIdx]->deallocate(mem);
        } else {
            std::free(header->base);
        }
    }

    void deallocate(void* ptr) {
        if (!ptr) return;

        void* mem = static_cast<char*>(ptr) - sizeof(AllocationHeader);
        AllocationHeader* header = static_cast<AllocationHeader*>(mem);
        deallocate(ptr, header->size);
    }
};

struct AllocationInfo {
    size_t size;
    size_t generation;
    // Removed: timestamp and stackTrace to save memory
};

class AllocationTracker {
    std::unordered_map<void*, std::unique_ptr<AllocationInfo>> allocationMap;
    std::mutex mutex;

public:
    void add(void* ptr, size_t size, size_t generation) {
        std::lock_guard lock(mutex);
        allocationMap[ptr] = std::make_unique<AllocationInfo>(
            AllocationInfo{size, generation});
    }

    void remove(void* ptr) {
        std::lock_guard lock(mutex);
        allocationMap.erase(ptr);
    }

    AllocationInfo* get(void* ptr) {
        std::lock_guard lock(mutex);
        auto it = allocationMap.find(ptr);
        return it != allocationMap.end() ? it->second.get() : nullptr;
    }
};

template<typename Allocator = DefaultAllocator>
class MemoryManager {
private:
    Allocator allocator;
    std::unique_ptr<MemoryAnalyzer> analyzer;
    bool auditMode;

public:
    MemoryManager(bool enableAudit = false)
        : auditMode(enableAudit) { if (auditMode) analyzer = std::make_unique<MemoryAnalyzer>(); }

    void setAuditMode(bool enable) {
        if (enable && !analyzer) analyzer = std::make_unique<MemoryAnalyzer>();
        auditMode = enable;
    }

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
        if (size == 0) {
            throw std::invalid_argument("Attempt to allocate zero bytes");
        }

        void* ptr = allocator.allocate(size, alignment);
        if (!ptr) {
            throw std::bad_alloc();
        }

        // Only zero-initialize for small allocations in debug mode
        #ifdef DEBUG
        if (size <= 256) {
            std::memset(ptr, 0, size);
        }
        #endif

        if (auditMode) {
            analyzer->recordAllocation(ptr, size, TRACE_INFO());
        }

        return ptr;
    }

    void deallocate(void* ptr) {
        if (!ptr) return;

        if (auditMode) {
            analyzer->recordDeallocation(ptr);
        }

        allocator.deallocate(ptr);
    }

    void analyzeMemoryUsage() const {
        if (!analyzer) return;
        auto reports = analyzer->getMemoryUsage();
        analyzer->printMemoryUsageReport(reports);
    }

    class Region {
    private:
        MemoryManager& manager;
        std::unordered_map<void*, size_t> objectGenerations;
        std::unordered_map<size_t, std::vector<void*>> generationObjects;
        size_t currentGeneration;
        size_t nextObjectGeneration = 1;
        std::unordered_map<void*, std::function<void(void*)>> destructors;
        std::shared_ptr<bool> alive = std::make_shared<bool>(true);
        void destroy(void* pointer) {
            auto it = destructors.find(pointer);
            if (it != destructors.end()) {
                auto drop = std::move(it->second); destructors.erase(it);
                drop(pointer);
            }
        }

        // Object reuse pools by size
        std::unordered_map<size_t, std::vector<void*>> reusePool;
        static constexpr size_t MAX_REUSE_POOL_SIZE = 1000;

    public:
        explicit Region(MemoryManager& mgr)
            : manager(mgr), currentGeneration(0) {
            generationObjects[0] = {};
        }

        std::weak_ptr<bool> lifetime() const { return alive; }
        ~Region() {
            *alive = false;
            while (!generationObjects.empty()) clearScope(generationObjects.begin()->first);
            for (auto& [size, pool] : reusePool)
                for (void* ptr : pool) manager.deallocate(ptr);
        }
        void clearScope(size_t scope) {
            for (;;) {
                auto found = generationObjects.find(scope);
                if (found == generationObjects.end()) return;
                auto objects = std::move(found->second);
                generationObjects.erase(found);
                for (auto ptr : objects) {
                    // A preceding destructor may already have dropped a sibling.
                    if (!objectGenerations.erase(ptr)) continue;
                    destroy(ptr);
                    manager.deallocate(ptr);
                }
            }
        }

        template<typename T, typename... Args>
        T* create(Args&&... args) {
            size_t objSize = sizeof(T);
            void* memory = nullptr;

            // Try to reuse an object from the pool
            auto& pool = reusePool[objSize];
            if (!pool.empty() && alignof(T) <= alignof(std::max_align_t)) {
                memory = pool.back();
                pool.pop_back();
            } else {
                memory = manager.allocate(sizeof(T), alignof(T));
            }

            if (!memory) return nullptr;

            try {
                T* obj = new (memory) T(std::forward<Args>(args)...);
                if (nextObjectGeneration == SIZE_MAX) throw std::overflow_error("Object generation exhausted");
                objectGenerations[memory] = nextObjectGeneration++;
                destructors[memory] = [](void* p) { static_cast<T*>(p)->~T(); };
                generationObjects[currentGeneration].push_back(memory);
                return obj;
            } catch (...) {
                // Return to pool instead of deallocating
                if (pool.size() < MAX_REUSE_POOL_SIZE && alignof(T) <= alignof(std::max_align_t)) {
                    pool.push_back(memory);
                } else {
                    manager.deallocate(memory);
                }
                throw;
            }
        }

        template<typename T>
        void deallocate(void* ptr) {
            if (!ptr) return;
            if (!objectGenerations.erase(ptr)) throw std::runtime_error("Drop of non-live object");
            for (auto& [scope, pointers] : generationObjects)
                pointers.erase(std::remove(pointers.begin(), pointers.end(), ptr), pointers.end());
            destroy(ptr);
            auto& pool = reusePool[sizeof(T)];
            if (pool.size() < MAX_REUSE_POOL_SIZE && alignof(T) <= alignof(std::max_align_t)) {
                try { pool.push_back(ptr); }
                catch (...) { manager.deallocate(ptr); throw; }
            } else manager.deallocate(ptr);
        }

        size_t getGeneration(void* ptr) const {
            auto it = objectGenerations.find(ptr);
            return (it != objectGenerations.end()) ? it->second : 0;
        }

        void enterScope() {
            ++currentGeneration;
            generationObjects[currentGeneration] = {};
        }

        void exitScope() {
            if (!currentGeneration) return;
            clearScope(currentGeneration);
            --currentGeneration;
        }
        void collectGarbage() {
            if (currentGeneration) clearScope(currentGeneration);
        }

        // Get current allocation count for this scope
        size_t getScopeAllocationCount() const {
            auto it = generationObjects.find(currentGeneration);
            return (it != generationObjects.end()) ? it->second.size() : 0;
        }
    };

    template<typename T>
    class Linear {
    private:
        T* ptr;
        Region* region;
        std::weak_ptr<bool> regionAlive;
        size_t expectedGeneration;
        bool ownsResource;
        MemoryManager& manager;

    public:
        explicit Linear(Region& r, T* p, MemoryManager& mgr)
            : ptr(p), region(&r), regionAlive(r.lifetime()), expectedGeneration(r.getGeneration(p)), ownsResource(true), manager(mgr) {}

        Linear(const Linear&) = delete;
        Linear& operator=(const Linear&) = delete;

        Linear(Linear&& other) noexcept
            : ptr(other.ptr), region(other.region), regionAlive(other.regionAlive), expectedGeneration(other.expectedGeneration),
              ownsResource(other.ownsResource), manager(other.manager) {
            other.ptr = nullptr;
            other.ownsResource = false;
        }

        Linear& operator=(Linear&& other) noexcept {
            if (this != &other) {
                release();
                ptr = other.ptr;
                region = other.region;
                regionAlive = other.regionAlive;
                expectedGeneration = other.expectedGeneration;
                ownsResource = other.ownsResource;
                other.ptr = nullptr;
                other.ownsResource = false;
            }
            return *this;
        }

        ~Linear() { release(); }

        bool isValid() const {
            auto live = regionAlive.lock();
            return ptr && ownsResource && live && *live && region->getGeneration(ptr) == expectedGeneration;
        }
        T* get() const {
            if (!isValid()) throw std::runtime_error("Access to expired linear allocation");
            return ptr;
        }
        T* operator->() const { return get(); }
        T& operator*() const { return *get(); }
        T* borrow() const { return get(); }
        Region& getRegion() const { return *region; }

        void release() {
            if (ptr && ownsResource) {
                if (isValid()) region->template deallocate<T>(ptr);
                ptr = nullptr;
                ownsResource = false;
            }
        }
    };

    template<typename T>
    class Ref {
    private:
        T* ptr;
        Region* region;
        std::weak_ptr<bool> regionAlive;
        size_t expectedGeneration;
        std::atomic<int>* refCount;

        void incrementRefCount() {
            if (refCount) {
                refCount->fetch_add(1, std::memory_order_relaxed);
            }
        }

        void decrementRefCount() {
            if (refCount && refCount->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete refCount;

                ptr = nullptr;
                region = nullptr;
                refCount = nullptr;
            }
        }

    public:
        Ref() : ptr(nullptr), region(nullptr),
                expectedGeneration(0), refCount(nullptr) {}

        Ref(Region& r, T* p)
            : ptr(p), region(&r), regionAlive(r.lifetime()), expectedGeneration(r.getGeneration(p)),
              refCount(new std::atomic<int>(1)) {}

        Ref(const Ref& other)
            : ptr(other.ptr), region(other.region),
              regionAlive(other.regionAlive), expectedGeneration(other.expectedGeneration),
              refCount(other.refCount) {
            incrementRefCount();
        }

        Ref& operator=(const Ref& other) {
            if (this != &other) {
                decrementRefCount();
                ptr = other.ptr;
                region = other.region;
                regionAlive = other.regionAlive;
                expectedGeneration = other.expectedGeneration;
                refCount = other.refCount;
                incrementRefCount();
            }
            return *this;
        }

        Ref(Ref&& other) noexcept
            : ptr(other.ptr), region(other.region),
              regionAlive(other.regionAlive), expectedGeneration(other.expectedGeneration),
              refCount(other.refCount) {
            other.ptr = nullptr;
            other.region = nullptr;
            other.refCount = nullptr;
        }

        Ref& operator=(Ref&& other) noexcept {
            if (this != &other) {
                decrementRefCount();
                ptr = other.ptr;
                region = other.region;
                regionAlive = other.regionAlive;
                expectedGeneration = other.expectedGeneration;
                refCount = other.refCount;
                other.ptr = nullptr;
                other.region = nullptr;
                other.refCount = nullptr;
            }
            return *this;
        }

        ~Ref() { decrementRefCount(); }

        T* operator->() const {
            if (!isValid()) {
                throw std::runtime_error("Accessing invalid generational reference");
            }
            return ptr;
        }

        T& operator*() const {
            if (!isValid()) {
                throw std::runtime_error("Accessing invalid generational reference");
            }
            return *ptr;
        }

        T* get() const { return operator->(); }
        bool isValid() const {
            auto live = regionAlive.lock();
            return ptr && live && *live && region->getGeneration(ptr) == expectedGeneration;
        }
        Region& getRegion() const { return *region; }
    };

    template<typename T, typename... Args>
    Linear<T> makeLinear(Region& region, Args&&... args) {
        T* obj = region.template create<T>(std::forward<Args>(args)...);
        if (!obj) throw std::bad_alloc();
        return Linear<T>(region, obj, *this);
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> makeRef(Region& region, Args&&... args) {
        T* obj = region.template create<T>(std::forward<Args>(args)...);
        if (!obj) throw std::bad_alloc();

        auto deleter = [&region](T* ptr) {
            region.template deallocate<T>(ptr);
        };

        return std::shared_ptr<T>(obj, deleter);
    }

    class Unsafe {
        static DefaultAllocator& allocator() { static DefaultAllocator value; return value; }
    public:
        static void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) {
            return allocator().allocate(size, alignment);
        }

        static void deallocate(void* ptr) noexcept {
            allocator().deallocate(ptr);
        }

        static void* resize(void* ptr, std::size_t new_size,
                           std::size_t alignment = alignof(std::max_align_t)) {
            void* new_ptr = allocator().allocate(new_size, alignment);
            if (ptr) {
                auto* header = reinterpret_cast<AllocationHeader*>(ptr) - 1;
                if (!new_ptr) throw std::bad_alloc();
                std::memcpy(new_ptr, ptr, std::min(new_size, header->size));
                allocator().deallocate(ptr);
            }
            return new_ptr;
        }

        static void* allocateZeroed(std::size_t num, std::size_t size) {
            if (size && num > SIZE_MAX / size) throw std::bad_alloc();
            std::size_t total = num * size;
            void* ptr = allocate(total);
            if (ptr) std::memset(ptr, 0, total);
            return ptr;
        }

        static void copy(void* dest, const void* src, std::size_t num) {
            std::memcpy(dest, src, num);
        }

        static void set(void* ptr, int value, std::size_t num) {
            std::memset(ptr, value, num);
        }

        static int compare(const void* ptr1, const void* ptr2, std::size_t num) {
            return std::memcmp(ptr1, ptr2, num);
        }

        static void move(void* dest, const void* src, std::size_t num) {
            std::memmove(dest, src, num);
        }
    };

    static MemoryManager& getInstance() {
        static MemoryManager instance;
        return instance;
    }
};

} // namespace LM
} // namespace Memory
