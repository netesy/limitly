#pragma once

#include "memory_analyzer.hh"
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

constexpr size_t MIN_ALLOC_SIZE = 4;
constexpr size_t MAX_ALLOC_SIZE = 256;
constexpr size_t POOL_CHUNK_SIZE = 128;  // Reduced from 256
constexpr size_t LARGE_ALLOC_THRESHOLD = 512;  // New threshold for large allocations

// Lightweight allocation header (only 16 bytes)
struct AllocationHeader {
    uint32_t size;           // 4 bytes
    uint16_t poolIndex;      // 2 bytes (which pool this came from)
    uint16_t flags;          // 2 bytes (alignment, etc.)
    uint64_t padding;        // 8 bytes (for alignment)
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
            spinUnlock();
            // Expand pool by 50% when exhausted
            size_t expandSize = std::max(size_t(32), allocatedChunks.size() * POOL_CHUNK_SIZE / 2);
            expandPool(expandSize);
            spinLock();
            
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
        freeBlocks.push_back(ptr);
        freeCount++;
        spinUnlock();
    }
    
    size_t getFreeCount() const { return freeCount; }
    size_t getBlockSize() const { return blockSize; }
};

class DefaultAllocator {
private:
    static constexpr size_t NUM_POOLS = 6;  // 4, 8, 16, 32, 64, 128, 256 bytes
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
        size_t totalSize = size + sizeof(AllocationHeader);
        
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
        header->size = static_cast<uint32_t>(size);
        header->poolIndex = poolIdx;
        header->flags = 0;
        
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
            std::free(mem);
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

        // Add these methods to make AllocationTracker iterable
    auto begin() const { return allocationMap.begin(); }
    auto end() const { return allocationMap.end(); }
    auto begin() { return allocationMap.begin(); }
    auto end() { return allocationMap.end(); }
};

template<typename Allocator = DefaultAllocator>
class MemoryManager {
private:
    Allocator allocator;
    AllocationTracker tracker;
    MemoryAnalyzer analyzer;
    bool auditMode;

public:
    MemoryManager(bool enableAudit = false)
        : auditMode(enableAudit) {}

    void setAuditMode(bool enable) {
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
            analyzer.recordAllocation(ptr, size, TRACE_INFO());
        }
        
        return ptr;
    }

    void deallocate(void* ptr) {
        if (!ptr) return;
        
        if (auditMode) {
            analyzer.recordDeallocation(ptr);
        }
        
        allocator.deallocate(ptr);
    }

    void analyzeMemoryUsage() const {
        auto reports = analyzer.getMemoryUsage();
        analyzer.printMemoryUsageReport(reports);
    }

    class Region {
    private:
        MemoryManager& manager;
        std::unordered_map<void*, size_t> objectGenerations;
        std::unordered_map<size_t, std::vector<void*>> generationObjects;
        size_t currentGeneration;

    public:
        explicit Region(MemoryManager& mgr)
            : manager(mgr), currentGeneration(0) {
            generationObjects[0] = {};
        }

        ~Region() {
            for (auto const& [gen, ptrs] : generationObjects) {
                for (void* ptr : ptrs) {
                    manager.deallocate(ptr);
                }
            }
        }

        template<typename T, typename... Args>
        T* create(Args&&... args) {
            void* memory = manager.allocate(sizeof(T), alignof(T));
            if (!memory) return nullptr;
            
            try {
                T* obj = new (memory) T(std::forward<Args>(args)...);
                objectGenerations[memory] = currentGeneration;
                generationObjects[currentGeneration].push_back(memory);
                return obj;
            } catch (...) {
                manager.deallocate(memory);
                throw;
            }
        }

        template<typename T>
        void deallocate(void* ptr) {
            if (!ptr) return;

            try {
                if constexpr (!std::is_trivially_destructible_v<T>) {
                    static_cast<T*>(ptr)->~T();
                }

                manager.deallocate(ptr);

                auto gen_it = objectGenerations.find(ptr);
                if (gen_it != objectGenerations.end()) {
                    size_t gen = gen_it->second;
                    objectGenerations.erase(gen_it);

                    auto& ptr_list = generationObjects[gen];
                    ptr_list.erase(std::remove(ptr_list.begin(), ptr_list.end(), ptr), ptr_list.end());
                }
            } catch (...) {
                manager.deallocate(ptr);
                objectGenerations.erase(ptr);
                throw;
            }
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
            if (currentGeneration == 0) return;

            size_t removable = currentGeneration;
            auto it = generationObjects.find(removable);
            
            if (it != generationObjects.end()) {
                for (void* ptr : it->second) {
                    manager.deallocate(ptr);
                    objectGenerations.erase(ptr);
                }
                generationObjects.erase(it);
            }
            
            --currentGeneration;
        }
    };

    template<typename T>
    class Linear {
    private:
        T* ptr;
        Region* region;
        bool ownsResource;
        MemoryManager& manager;

    public:
        explicit Linear(Region& r, T* p, MemoryManager& mgr)
            : ptr(p), region(&r), ownsResource(true), manager(mgr) {}

        Linear(const Linear&) = delete;
        Linear& operator=(const Linear&) = delete;

        Linear(Linear&& other) noexcept
            : ptr(other.ptr), region(other.region), 
              ownsResource(other.ownsResource), manager(other.manager) {
            other.ptr = nullptr;
            other.ownsResource = false;
        }

        Linear& operator=(Linear&& other) noexcept {
            if (this != &other) {
                release();
                ptr = other.ptr;
                region = other.region;
                ownsResource = other.ownsResource;
                other.ptr = nullptr;
                other.ownsResource = false;
            }
            return *this;
        }

        ~Linear() { release(); }

        T* operator->() const { return ptr; }
        T& operator*() const { return *ptr; }
        T* get() const { return ptr; }
        T* borrow() const { return ptr; }
        Region& getRegion() const { return *region; }

        void release() {
            if (ptr && ownsResource) {
                region->template deallocate<T>(ptr);
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
                if (ptr && isValid()) {
                    region->template deallocate<T>(ptr);
                }
                ptr = nullptr;
                region = nullptr;
                refCount = nullptr;
            }
        }

    public:
        Ref() : ptr(nullptr), region(nullptr), 
                expectedGeneration(0), refCount(nullptr) {}

        Ref(Region& r, T* p)
            : ptr(p), region(&r), expectedGeneration(r.getGeneration(p)),
              refCount(new std::atomic<int>(1)) {}

        Ref(const Ref& other)
            : ptr(other.ptr), region(other.region),
              expectedGeneration(other.expectedGeneration),
              refCount(other.refCount) {
            incrementRefCount();
        }

        Ref& operator=(const Ref& other) {
            if (this != &other) {
                decrementRefCount();
                ptr = other.ptr;
                region = other.region;
                expectedGeneration = other.expectedGeneration;
                refCount = other.refCount;
                incrementRefCount();
            }
            return *this;
        }

        Ref(Ref&& other) noexcept
            : ptr(other.ptr), region(other.region),
              expectedGeneration(other.expectedGeneration),
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

        T* get() const { return ptr; }
        bool isValid() const {
            return ptr != nullptr && region->getGeneration(ptr) == expectedGeneration;
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
    public:
        static void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) {
            return DefaultAllocator().allocate(size, alignment);
        }

        static void deallocate(void* ptr) noexcept {
            DefaultAllocator().deallocate(ptr);
        }

        static void* resize(void* ptr, std::size_t new_size, 
                           std::size_t alignment = alignof(std::max_align_t)) {
            void* new_ptr = DefaultAllocator().allocate(new_size, alignment);
            if (ptr) {
                std::memcpy(new_ptr, ptr, new_size);
                DefaultAllocator().deallocate(ptr);
            }
            return new_ptr;
        }

        static void* allocateZeroed(std::size_t num, std::size_t size) {
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