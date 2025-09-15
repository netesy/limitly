#pragma once

#include "memory_analyzer.hh"
#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifdef _MSC_VER
#include <intrin.h>
#endif


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define TRACE_INFO() (std::string(__FUNCTION__) + " at line " + TOSTRING(__LINE__))

constexpr size_t MIN_ALLOC_SIZE = 8;
constexpr size_t MAX_ALLOC_SIZE = 256;
constexpr size_t POOL_CHUNK_SIZE = 1024;

class MemoryPool {
private:
    std::vector<void*> freeBlocks;
    std::vector<void*> allocatedBlocks;
    std::mutex poolMutex;
    size_t blockSize;
    size_t poolSize;

public:
    MemoryPool(size_t blockSize, size_t poolSize)
        : blockSize(blockSize), poolSize(poolSize) {
        allocatedBlocks.reserve(poolSize);
        for (size_t i = 0; i < poolSize; ++i) {
            void* block = std::malloc(blockSize);
            freeBlocks.push_back(block);
            allocatedBlocks.push_back(block);
        }
    }

    ~MemoryPool() {
        for (void* block : allocatedBlocks) {
            std::free(block);
        }
    }

    void* allocate() {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (freeBlocks.empty()) {
            return std::malloc(blockSize);
        }
        void* block = freeBlocks.back();
        freeBlocks.pop_back();
        return block;
    }

    void deallocate(void* ptr) {
        std::lock_guard<std::mutex> lock(poolMutex);
        freeBlocks.push_back(ptr);
    }
};

class ObjectPool {
private:
    std::stack<void*> pool;
    std::mutex poolMutex;
    size_t objectSize;

public:
    ObjectPool(size_t objectSize, size_t initialSize) : objectSize(objectSize) {
        for (size_t i = 0; i < initialSize; ++i) {
            pool.push(std::malloc(objectSize));
        }
    }

    ~ObjectPool() {
        while (!pool.empty()) {
            std::free(pool.top());
            pool.pop();
        }
    }

    void* allocate() {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (pool.empty()) {
            return std::malloc(objectSize);
        }
        void* obj = pool.top();
        pool.pop();
        return obj;
    }

    void deallocate(void* obj) {
        std::lock_guard<std::mutex> lock(poolMutex);
        pool.push(obj);
    }
};

class DefaultAllocator {
private:
    std::unordered_map<size_t, MemoryPool*> memoryPools;
    ObjectPool objectPool;

public:
    DefaultAllocator()
        : objectPool(256, POOL_CHUNK_SIZE) {
        for (size_t size = MIN_ALLOC_SIZE; size <= MAX_ALLOC_SIZE; size *= 2) {
            memoryPools[size] = new MemoryPool(size, POOL_CHUNK_SIZE);
        }
    }

    ~DefaultAllocator() {
        for (auto& pair : memoryPools) {
            delete pair.second;
        }
    }

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
        // Calculate the actual size needed to satisfy alignment
        // // size_t actualSize = size + (alignment - 1) + sizeof(void*);
        
        if (size <= MAX_ALLOC_SIZE) {
            // Find the next power of two that can hold the requested size
            size_t poolSize = 1;
            while (poolSize < size) {
                poolSize <<= 1;
            }
            
            void* mem = memoryPools[poolSize]->allocate();
            if (!mem) {
                std::cerr << "[ERROR] Failed to allocate " << size 
                          << " bytes from pool of size " << poolSize << std::endl;
                return nullptr;
            }
            
            // Align the memory
            void* alignedPtr = reinterpret_cast<void*>(
                (reinterpret_cast<size_t>(mem) + sizeof(void*) + alignment - 1) & ~(alignment - 1)
            );
            
            // Store the original pointer right before the aligned memory
            *(reinterpret_cast<void**>(alignedPtr) - 1) = mem;
            return alignedPtr;
        }
        
        // For large allocations, use the object pool
        void* mem = objectPool.allocate();
        if (!mem) {
            std::cerr << "[ERROR] Failed to allocate " << size 
                      << " bytes from object pool" << std::endl;
            return nullptr;
        }
        
        // For object pool allocations, we don't need to handle alignment specially
        // since they're already aligned to the object size
        return mem;
    }

    void deallocate(void* ptr, size_t size) {
        if (!ptr) return;
        
        if (size <= MAX_ALLOC_SIZE) {
            // For aligned allocations, we need to get the original pointer
            // which is stored right before the aligned memory
            void* originalPtr = *(reinterpret_cast<void**>(ptr) - 1);
            
            // Find the pool size (next power of two >= size)
            size_t poolSize = 1;
            while (poolSize < size) {
                poolSize <<= 1;
            }
            
            memoryPools[poolSize]->deallocate(originalPtr);
        } else {
            objectPool.deallocate(ptr);
        }
    }

    void deallocate(void* ptr) {
        objectPool.deallocate(ptr);
    }
};

struct AllocationInfo
{
    size_t size;
    std::chrono::steady_clock::time_point timestamp;
    std::string stackTrace;
    size_t generation;
};

class AllocationTracker
{
    std::map<size_t, std::vector<void *>> sizeTree;
    std::unordered_map<void *, std::unique_ptr<AllocationInfo>> skiplist;
    std::mutex mutex;

public:
    void add(void *ptr, size_t size, const std::string &stackTrace, size_t generation)
    {
        std::lock_guard lock(mutex);
        auto info = std::make_unique<AllocationInfo>(
            AllocationInfo{size, std::chrono::steady_clock::now(), stackTrace, generation});
        sizeTree[size].push_back(ptr);
        skiplist[ptr] = std::move(info);
    }

    void remove(void *ptr)
    {
        std::lock_guard lock(mutex);
        if (auto it = skiplist.find(ptr); it != skiplist.end()) {
            sizeTree[it->second->size].erase(std::remove(sizeTree[it->second->size].begin(),
                                                         sizeTree[it->second->size].end(),
                                                         ptr),
                                             sizeTree[it->second->size].end());
            if (sizeTree[it->second->size].empty())
                sizeTree.erase(it->second->size);
            skiplist.erase(it);
        }
    }

    AllocationInfo *get(void *ptr)
    {
        std::lock_guard lock(mutex);
        auto it = skiplist.find(ptr);
        return it != skiplist.end() ? it->second.get() : nullptr;
    }

    // Add these methods to make AllocationTracker iterable
    auto begin() const { return skiplist.begin(); }
    auto end() const { return skiplist.end(); }
    auto begin() { return skiplist.begin(); }
    auto end() { return skiplist.end(); }
};

template<typename Allocator = DefaultAllocator>
class MemoryManager
{
private:
    mutable std::ofstream logFile;
    mutable std::mutex logMutex;
    bool auditMode;
    Allocator allocator;
    AllocationTracker tracker;
    MemoryAnalyzer analyzer;

public:
    MemoryManager(bool enableAudit = false)
        : auditMode(enableAudit)
    {
    }

    ~MemoryManager()
    {
        //analyzeMemoryUsage();
    }

    void setAuditMode(bool enable)
    {
        auditMode = enable;
    }

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t))
    {
        if (size == 0) {
            throw std::invalid_argument("Attempt to allocate zero bytes");
        }

        void *ptr = allocator.allocate(size, alignment);

        if (!ptr) {
            std::cerr << "[ERROR] MemoryManager::allocate failed to allocate "
                        << size << " bytes" << std::endl;
            throw std::bad_alloc();
        }

        // Zero-initialize the memory
        std::memset(ptr, 0, size);

        analyzer.recordAllocation(ptr, size, auditMode ? TRACE_INFO() : "");
        return ptr;
    }

    void deallocate(void *ptr)
    {
        // Get the size from the allocation tracker
        MemoryAnalyzer::AllocationInfo* info = analyzer.getAllocationInfo(ptr);
        size_t size = info ? info->size : 0;

        // Record deallocation
        analyzer.recordDeallocation(ptr);

        // Deallocate with the size parameter
        allocator.deallocate(ptr, size);
    }

    void analyzeMemoryUsage() const {
        auto reports = analyzer.getMemoryUsage();
        analyzer.printMemoryUsageReport(reports);
    }   

    class Region
    {
    private:
        MemoryManager &manager;
        std::unordered_map<void *, size_t> objectGenerations;
        size_t currentGeneration;

    public:
        explicit Region(MemoryManager &mgr)
            : manager(mgr)
            , currentGeneration(0)
        {
        }

        ~Region()
        {
            for (const auto &[ptr, gen] : objectGenerations) {
                manager.deallocate(ptr);
            }
        }

        template <typename T, typename... Args>
        T *create(Args &&...args)
        {
            void *memory = manager.allocate(sizeof(T), alignof(T));
            if (!memory) {
                return nullptr;
            }
            try {
                T *obj = new (memory) T(std::forward<Args>(args)...);
                objectGenerations[memory] = ++currentGeneration;
                return obj;
            } catch (...) {
                manager.deallocate(memory);
                throw;
            }
        }

        template<typename T>
        void deallocate(void *ptr, size_t size, size_t alignment)
        {
            if (!ptr) {
                return;
            }

            try {
                // Call destructor if it's a non-trivial type
                if constexpr (!std::is_trivially_destructible_v<T>) {
                    static_cast<T*>(ptr)->~T();
                }

                // Deallocate the memory
                manager.deallocate(ptr);

                // Remove from generations map
                auto it = objectGenerations.find(ptr);
                if (it != objectGenerations.end()) {
                    objectGenerations.erase(it);
                }
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Exception in Region::deallocate: " << e.what() << std::endl;
                // Still try to deallocate the memory even if destructor fails
                manager.deallocate(ptr);
                objectGenerations.erase(ptr);
                throw;
            } catch (...) {
                std::cerr << "[ERROR] Unknown exception in Region::deallocate" << std::endl;
                manager.deallocate(ptr);
                objectGenerations.erase(ptr);
                throw;
            }
        }

        // Add convenience overload for deallocate
        template<typename T>
        void deallocate(void* ptr)
        {
            deallocate<T>(ptr, sizeof(T), alignof(T));
        }

        size_t getGeneration(void *ptr) const
        {
            auto it = objectGenerations.find(ptr);
            return (it != objectGenerations.end()) ? it->second : 0;
        }
    };

    template<typename T>
    class Linear
    {
    private:
        T *ptr;
        Region *region;
        bool ownsResource;
        MemoryManager &manager;

    public:
        explicit Linear(Region &r, T *p, MemoryManager &mgr)
            : ptr(p)
            , region(&r)
            , ownsResource(true)
            , manager(mgr)
        {
        }

        Linear(const Linear &) = delete;
        Linear &operator=(const Linear &) = delete;

        Linear(Linear &&other) noexcept
            : ptr(other.ptr)
            , region(other.region)
            , ownsResource(other.ownsResource)
            , manager(other.manager)
        {
            other.ptr = nullptr;
            other.region = nullptr;
            other.ownsResource = false;
        }

        Linear &operator=(Linear &&other) noexcept
        {
            if (this != &other) {
                release();
                ptr = other.ptr;
                region = other.region;
                ownsResource = other.ownsResource;
                other.ptr = nullptr;
                other.region = nullptr;
                other.ownsResource = false;
            }
            return *this;
        }

        ~Linear() { release(); }

        T *operator->() const { return ptr; }
        T &operator*() const { return *ptr; }
        T *get() const { return ptr; }

        T *borrow() const
        {
            return ptr;
        }

        Region &getRegion() const { return *region; }

        void release()
        {
            if (ptr && ownsResource) {
                ptr->~T();
                region->template deallocate<T>(ptr);  // Use convenience overload
                ptr = nullptr;
                ownsResource = false;
            }
        }
    };

    template<typename T>
    class Ref
    {
    private:
        T *ptr;
        Region *region;
        size_t expectedGeneration;
        std::atomic<int> *refCount;
        MemoryManager &manager;

        void incrementRefCount()
        {
            if (refCount) {
                refCount->fetch_add(1, std::memory_order_relaxed);
            }
        }

        void decrementRefCount()
        {
            if (refCount && refCount->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete refCount;
                if (ptr && isValid()) {
                    ptr->~T();
                    region->template deallocate<T>(ptr);  // Use convenience overload
                }
                ptr = nullptr;
                region = nullptr;
                refCount = nullptr;
            }
        }

    public:
        Ref()
            : ptr(nullptr)
            , region(nullptr)
            , expectedGeneration(0)
            , refCount(nullptr)
            , manager(MemoryManager::getInstance())
        {}

        Ref(Region &r, T *p)
            : ptr(p)
            , region(&r)
            , expectedGeneration(r.getGeneration(p))
            , refCount(new std::atomic<int>(1))
            , manager(MemoryManager::getInstance())
        {
        }

        Ref(const Ref &other)
            : ptr(other.ptr)
            , region(other.region)
            , expectedGeneration(other.expectedGeneration)
            , refCount(other.refCount)
            , manager(other.manager)
        {
            incrementRefCount();
        }

        Ref &operator=(const Ref &other)
        {
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

        Ref(Ref &&other) noexcept
            : ptr(other.ptr)
            , region(other.region)
            , expectedGeneration(other.expectedGeneration)
            , refCount(other.refCount)
            , manager(other.manager)
        {
            other.ptr = nullptr;
            other.region = nullptr;
            other.refCount = nullptr;
        }

        Ref &operator=(Ref &&other) noexcept
        {
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

        T *operator->() const
        {
            if (!isValid()) {
                throw std::runtime_error("Accessing invalid generational reference");
            }
            return ptr;
        }

        T &operator*() const
        {
            if (!isValid()) {
                throw std::runtime_error("Accessing invalid generational reference");
            }
            return *ptr;
        }

        T *get() const { return ptr; }
        bool isValid() const
        {
            return ptr != nullptr && region->getGeneration(ptr) == expectedGeneration;
        }
        Region &getRegion() const { return *region; }
    };

    template<typename T, typename... Args>
    Linear<T> makeLinear(Region &region, Args &&...args)
    {
        static_assert(std::is_nothrow_destructible<T>::value,
                      "Type must be nothrow destructible for safe cleanup");

        T *obj = region.template create<T>(std::forward<Args>(args)...);

        if (!obj) {
            throw std::bad_alloc();
        }

        return Linear<T>(region, obj, *this);
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> makeRef(Region &region, Args &&...args)
    {
        static_assert(std::is_nothrow_destructible<T>::value,
                      "Type must be nothrow destructible for safe cleanup");

        try {
            T *obj = region.template create<T>(std::forward<Args>(args)...);

            if (!obj) {
                std::cerr << "[ERROR] makeRef: Failed to create object - returned nullptr" << std::endl;
                throw std::bad_alloc();
            }

            size_t generation = region.getGeneration(obj);

            auto deleter = [&region](T* ptr) {
                region.template deallocate<T>(ptr);
            };

            return std::shared_ptr<T>(obj, deleter);

        } catch (const std::exception& e) {
            std::cerr << "[EXCEPTION] makeRef: " << e.what() << std::endl;
            throw;
        } catch (...) {
            std::cerr << "[EXCEPTION] makeRef: Unknown exception" << std::endl;
            throw;
        }
    }

    class Unsafe
    {
    public:
        static void *allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t))
        {
            return DefaultAllocator().allocate(size, alignment);
        }

        static void deallocate(void *ptr) noexcept
        {
            DefaultAllocator().deallocate(ptr);
        }

        static void *resize(void *ptr,
                            std::size_t new_size,
                            std::size_t alignment = alignof(std::max_align_t))
        {
            void *new_ptr = DefaultAllocator().allocate(new_size, alignment);
            if (ptr) {
                std::memcpy(new_ptr, ptr, new_size);
                DefaultAllocator().deallocate(ptr);
            }
            return new_ptr;
        }

        static void *allocateZeroed(std::size_t num, std::size_t size)
        {
            std::size_t total = num * size;
            void *ptr = allocate(total);
            if (ptr) {
                std::memset(ptr, 0, total);
            }
            return ptr;
        }

        static void copy(void *dest, const void *src, std::size_t num)
        {
            std::memcpy(dest, src, num);
        }

        static void set(void *ptr, int value, std::size_t num) { std::memset(ptr, value, num); }

        static int compare(const void *ptr1, const void *ptr2, std::size_t num)
        {
            return std::memcmp(ptr1, ptr2, num);
        }

        static void move(void *dest, const void *src, std::size_t num)
        {
            std::memmove(dest, src, num);
        }
    };

    // Singleton instance
    static MemoryManager &getInstance()
    {
        static MemoryManager instance;
        return instance;
    }
};