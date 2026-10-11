// Private standalone-AOT ownership helpers. No public object/header fields.
#include "memory.hh"
#include "region_instances.hh"
#include "reference_flags.hh"
#include "aot_value_kind.hh"
#include "numeric_conversion.hh"
#include "numeric_semantics.hh"
#include "atomic_field.hh"
#include <optional>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <map>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>

namespace {
using Word = uint64_t;
constexpr Word object_kind = static_cast<Word>(LM::Memory::AOTValueKind::Object);
constexpr Word boolean_kind = static_cast<Word>(LM::Memory::AOTValueKind::Boolean);
struct Allocation {
    size_t size;
    Word owner;
    std::unordered_map<size_t, Word> edges;
    void (*finalizer)(Word) = nullptr;
    bool finalized = false;
    bool float_box = false;
    bool raw_memory = false;
};
struct Region {
    Word parent;
    Word lexical;
    size_t depth;
    std::unordered_set<Word> members;
};
struct Files {
    uint64_t next = 2;
    std::unordered_map<uint64_t, FILE*> handles;
    ~Files() { for (auto [id, file] : handles) if (file) std::fclose(file); }
};
// Shared metadata is synchronized; invocation state and the active region are
// thread-local. Region identities remain unique across recursive workers.
struct ConcurrentRegions : LM::Memory::RegionInstances<Region> {
    ConcurrentRegions() : RegionInstances(Region{0,0,0,{}}) {}
    void erase(Word id) {
        auto position = std::lower_bound(entries.begin(), entries.end(), id,
            [](const auto& entry, Word value) { return entry.first < value; });
        if (position == entries.end() || position->first != id) throw std::runtime_error("Inactive region retirement");
        entries.erase(position);
    }
};
struct ReferenceOwner { std::thread::id thread; Word region; };
struct SchedulerConfiguration { Word cores, timeout, config; };
struct SharedHeap {
    std::recursive_mutex mutex;
    std::thread::id owner = std::this_thread::get_id();
    LM::Memory::DefaultAllocator allocator;
    LM::Memory::LifetimeRegistry lifetimes;
    Word next = 1;
    std::map<Word, Allocation> allocations;
    ConcurrentRegions regions;
    std::map<Word,Word> shadow;
    std::map<Word,ReferenceOwner> reference_owners;
    Files files;
    std::map<Word,SchedulerConfiguration> schedulers;
    std::unordered_set<Word> closed_channels;
    std::condition_variable_any work_available;
};
SharedHeap& shared_heap() { static SharedHeap state; return state; }
thread_local unsigned runtime_lock_depth = 0;
struct RuntimeGuard {
    RuntimeGuard() { shared_heap().mutex.lock(); ++runtime_lock_depth; }
    ~RuntimeGuard() { --runtime_lock_depth; shared_heap().mutex.unlock(); }
};
struct RuntimeSuspend {
    unsigned depth = runtime_lock_depth;
    RuntimeSuspend() { while(runtime_lock_depth) { --runtime_lock_depth; shared_heap().mutex.unlock(); } }
    ~RuntimeSuspend() { while(runtime_lock_depth < depth) {shared_heap().mutex.lock(); ++runtime_lock_depth;} }
};
struct Heap {
    LM::Memory::DefaultAllocator& allocator = shared_heap().allocator;
    LM::Memory::LifetimeRegistry& lifetimes = shared_heap().lifetimes;
    struct Invocation {
        Word region = 0;
        std::vector<Word> args;
        std::unordered_set<Word> slots;
        std::vector<std::pair<Word, Word>> staged_params;
    };
    Word active = 0, base = 0;
    Word& next = shared_heap().next;
    bool worker = false;
    char worker_error[1024] = {};
    std::atomic<bool>* cancellation = nullptr;
    std::chrono::steady_clock::time_point deadline;
    bool timed = false, timed_out = false;
    std::map<Word, Allocation>& allocations = shared_heap().allocations;
    ConcurrentRegions& regions = shared_heap().regions;
    std::map<Word, Word>& shadow = shared_heap().shadow;
    std::vector<Invocation> invocations;
    std::vector<Word> pending_args;
    Word return_pointer = 0;
    Files& files = shared_heap().files;

    void forget_kinds(Word address, Word size, bool overlapping = false) {
        if (!size) return;
        auto first = shadow.lower_bound(overlapping && address >= sizeof(Word) - 1 ? address - (sizeof(Word) - 1) : address);
        while (first != shadow.end() && (first->first < address || first->first - address < size))
            first = shadow.erase(first);
    }
    auto containing(Word address) {
        auto found = allocations.upper_bound(address);
        if (found == allocations.begin()) return allocations.end();
        --found;
        return address - found->first < found->second.size ? found : allocations.end();
    }
    void promote(Word value, Word target) {
        std::vector<Word> pending{value};
        std::unordered_set<Word> seen;
        while (!pending.empty()) {
            auto found = containing(pending.back());
            pending.pop_back();
            if (found == allocations.end() || !seen.insert(found->first).second) continue;
            auto& allocation = found->second;
            if (regions.at(allocation.owner).depth <= regions.at(target).depth) continue;
            regions.at(allocation.owner).members.erase(found->first);
            regions.at(target).members.insert(found->first);
            allocation.owner = target;
            for (auto [offset, child] : allocation.edges) pending.push_back(child);
        }
    }
    void finalize(Word pointer) {
        auto found = allocations.find(pointer);
        if (found == allocations.end() || found->second.finalized) return;
        found->second.finalized = true;
        auto callback = found->second.finalizer;
        if (callback) {
            struct RestoreWorkerState {
                Heap& heap; char error[1024]; std::atomic<bool>* cancellation; bool timed;
                explicit RestoreWorkerState(Heap& value):heap(value),cancellation(value.cancellation),timed(value.timed) {
                    std::memcpy(error,heap.worker_error,sizeof(error));heap.worker_error[0]=0;heap.cancellation=nullptr;heap.timed=false;
                }
                ~RestoreWorkerState() {
                    heap.cancellation=cancellation;heap.timed=timed;
                    if(error[0]) std::memcpy(heap.worker_error,error,sizeof(error));
                }
            } restore(*this);
            RuntimeSuspend suspend;callback(pointer);
        }
    }
    void release(Word pointer) {
        auto found = allocations.find(pointer);
        if (found == allocations.end()) throw std::runtime_error("AOT free of unowned allocation");
        regions.at(found->second.owner).members.erase(pointer);
        forget_kinds(pointer, found->second.size);
        lifetimes.revoke(pointer);
        shared_heap().schedulers.erase(pointer);
        shared_heap().closed_channels.erase(pointer);
        allocations.erase(found);
        allocator.deallocate(reinterpret_cast<void*>(pointer));
    }
    void cleanup(Word region) {
        // Fields and children remain alive throughout destructor execution.
        for (;;) {
            std::vector<Word> objects;
            for (auto object : regions.at(region).members)
                if (!allocations.at(object).finalized) objects.push_back(object);
            if (objects.empty()) break;
            for (auto object : objects) finalize(object);
        }
        for (auto position=shared_heap().reference_owners.begin(); position!=shared_heap().reference_owners.end();)
            if(position->second.region==region) position=shared_heap().reference_owners.erase(position); else ++position;
        lifetimes.end_region(region);
        while (!regions.at(region).members.empty()) release(*regions.at(region).members.begin());
    }
    ~Heap() {
        RuntimeGuard lock;
        try {
            while (active != base) {
                auto parent = regions.at(active).parent;
                cleanup(active);
                regions.erase(active);
                active = parent;
            }
            if (std::this_thread::get_id() == shared_heap().owner) cleanup(0);
        } catch (...) { std::terminate(); }
    }
};
Heap& heap() { static thread_local Heap value; return value; }
Files& files() { return heap().files; }
Word read_word(Word address, size_t offset = 0) {
    Word value;
    std::memcpy(&value, reinterpret_cast<void*>(address + offset), sizeof(value));
    return value;
}
const char* string_data(Word value) {
    if (value <= 4096 || (read_word(value) & 0xffffffff) != 11) return nullptr;
    return reinterpret_cast<const char*>(value + 24);
}
std::optional<__int128> integer_number(Word value, Word kind) {
    if (!kind) return static_cast<int64_t>(value);
    if (kind != object_kind || value <= 4096) return {};
    auto type = read_word(value) & 0xffffffff;
    if (type == 5) return static_cast<int64_t>(read_word(value, 8));
    if (type == 6) return read_word(value, 8);
    if (type == 7 || type == 8) {
        __int128 number; std::memcpy(&number, reinterpret_cast<void*>(value + 16), sizeof(number)); return number;
    }
    return {};
}
std::string integer_text(__int128 number) {
    bool negative = number < 0;
    auto magnitude = negative ? 0 - static_cast<unsigned __int128>(number) : static_cast<unsigned __int128>(number);
    std::string text;
    do { text.push_back('0' + magnitude % 10); magnitude /= 10; } while (magnitude);
    if (negative) text.push_back('-');
    std::reverse(text.begin(), text.end()); return text;
}
}

extern "C" {
uint64_t lymar_aot_alloc(uint64_t size);
uint64_t lymar_aot_box_float(double number);
void lymar_aot_edge(uint64_t address, uint64_t child, uint64_t kind);
double lymar_aot_to_float(uint64_t value, uint64_t kind);
// Frame operations require a live, correctly shaped receiver before addressing
// its fields. This is backend-private layout validation, not frontend inference.
uint64_t lymar_aot_frame_field_address(uint64_t pointer, uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    auto frame = h.allocations.find(pointer);
    if (frame == h.allocations.end() || frame->second.size < 40 || (read_word(pointer) & 0xffffffff) != 15)
        throw std::runtime_error("Invalid or expired frame receiver");
    auto count = read_word(pointer, 24);
    if (index >= count) throw std::runtime_error("Invalid frame field index");
    auto fields = read_word(pointer, 16);
    auto array = h.allocations.find(fields);
    if (array == h.allocations.end() || count > array->second.size / sizeof(Word))
        throw std::runtime_error("Invalid frame fields allocation");
    h.return_pointer = 1;
    return fields + index * sizeof(Word);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_atomic_load(uint64_t pointer, uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    auto result = LM::Memory::atomic_field_load(reinterpret_cast<Word*>(address));
    auto found = heap().shadow.find(address);
    heap().return_pointer = found == heap().shadow.end() ? 0 : found->second;
    return result;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_atomic_store(uint64_t pointer, uint64_t index, uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    // Publish ownership/kind before publishing the field value.
    std::lock_guard lock(LM::Memory::atomic_field_mutex(reinterpret_cast<void*>(address)));
    lymar_aot_edge(address, value, kind);
    std::atomic_ref<Word>(*reinterpret_cast<Word*>(address)).store(value, std::memory_order_seq_cst);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_atomic_update(uint64_t pointer, uint64_t index, uint64_t value, uint64_t kind, uint64_t subtract) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    LM::Memory::atomic_field_update(reinterpret_cast<Word*>(address), [&](Word old) {
        auto found = heap().shadow.find(address);
        Word old_kind = found == heap().shadow.end() ? 0 : found->second;
        Word result = 2, result_kind = object_kind;
        auto left = integer_number(old, old_kind), right = integer_number(value, kind);
        if (left && right) {
            __int128 number;
            if (LM::Memory::add_integer(*left, *right, number, subtract != 0)) {
                if (number >= INT64_MIN && number <= INT64_MAX) { result = static_cast<Word>(number); result_kind = 0; }
                else { result = lymar_aot_alloc(32); *reinterpret_cast<Word*>(result) = 7;
                    std::memcpy(reinterpret_cast<void*>(result + 16), &number, sizeof(number)); }
            }
        } else {
            auto is_float = [](Word word, Word mode) { return mode == object_kind && word > 4096 && (read_word(word) & 0xffffffff) == 9; };
            if ((left || is_float(old, old_kind)) && (right || is_float(value, kind))) {
                auto a = lymar_aot_to_float(old, old_kind), b = lymar_aot_to_float(value, kind);
                result = lymar_aot_box_float(subtract ? a - b : a + b);
            } else if (!subtract && old_kind == object_kind && kind == object_kind && old > 4096 && value > 4096 &&
                       (read_word(old) & 0xffffffff) == 11 && (read_word(value) & 0xffffffff) == 11) {
                auto a = read_word(old, 8), b = read_word(value, 8);
                if (b > UINT64_MAX - 25 || a > UINT64_MAX - b - 25) throw std::overflow_error("Atomic string length overflow");
                result = lymar_aot_alloc(25 + a + b);
                *reinterpret_cast<Word*>(result) = 11; *reinterpret_cast<Word*>(result + 8) = a + b;
                *reinterpret_cast<Word*>(result + 16) = a + b;
                std::memcpy(reinterpret_cast<void*>(result + 24), reinterpret_cast<void*>(old + 24), a);
                std::memcpy(reinterpret_cast<void*>(result + 24 + a), reinterpret_cast<void*>(value + 24), b);
                *reinterpret_cast<char*>(result + 24 + a + b) = 0;
            }
        }
        lymar_aot_edge(address, result, result_kind);
        return result;
    });

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_builtin_arity_error() {
    try {
    RuntimeGuard runtime_guard;
 throw std::runtime_error("Builtin argument count mismatch");
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_ref_create(uint64_t pointer, uint64_t writable) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    h.return_pointer = 0;
    if ((pointer == 0 || pointer == 2) && (writable & LM::Memory::ReferenceNullable)) return 0;
    if (!h.allocations.count(pointer)) throw std::runtime_error("AOT borrow of unowned object");
    h.lifetimes.adopt(pointer);
    h.return_pointer = 0;
    auto token = h.lifetimes.borrow(pointer, (writable & LM::Memory::ReferenceWritable) != 0, h.active);
    shared_heap().reference_owners[token] = {std::this_thread::get_id(),h.active};
    return token;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Provenance distinguishes actual nil/pointers from raw scalar words that
// happen to equal the nil representation (notably integers zero and two).
uint64_t lymar_aot_nil() {
    try {
    RuntimeGuard runtime_guard;
 return 2;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_nil(uint64_t value, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    return is_pointer == object_kind && (value == 0 || value == 2);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_object(uint64_t value, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    return is_pointer == object_kind && value != 0 && value != 2;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Erased native integers are untagged, so pointer shape cannot validate a
// string receiver. The existing kind sidecar is authoritative at this boundary.
uint64_t lymar_aot_string_receiver(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (!lymar_aot_is_object(value, kind)) return 0;
    return (read_word(value) & 0xffffffff) == 11 ? value : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_callable_receiver(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (!lymar_aot_is_object(value, kind)) return 0;
    auto type = read_word(value) & 0xffffffff;
    if (type == 11) return value; // canonical function-name string
    auto& h = heap();
    auto tuple = h.allocations.find(value);
    if (type != 3 || tuple == h.allocations.end() || tuple->second.size < 32 || !read_word(value,16)) return 0;
    auto elements = read_word(value,8);
    auto array = h.allocations.find(elements);
    if (array == h.allocations.end() || array->second.size < 8) return 0;
    auto origin = h.shadow.find(elements);
    auto name = read_word(elements);
    if (origin == h.shadow.end() || !lymar_aot_is_object(name,origin->second) ||
        (read_word(name) & 0xffffffff) != 11) return 0;
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_string_index(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (kind == 0) return value;
    if (!lymar_aot_is_object(value, kind)) return 0;
    auto type = read_word(value) & 0xffffffff;
    if (type >= 5 && type <= 8) return read_word(value + 8);
    if (type == 9) {
        double number;
        std::memcpy(&number, reinterpret_cast<void*>(value + 8), sizeof(number));
        return static_cast<uint64_t>(LM::Memory::truncate_i64(number));
    }
    return 0; // as_i64 does not parse strings or convert booleans.

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_boolean(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;
 return value;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_print_object(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    return lymar_aot_is_object(value, kind) && (read_word(value) & 0xffffffff) != 9;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
double lymar_aot_to_float(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (auto integer = integer_number(value, kind)) return static_cast<double>(*integer);
    if (!kind) return static_cast<double>(static_cast<int64_t>(value));
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0.0;
    if ((read_word(value) & 0xffffffff) == 9) {
        double number;
        std::memcpy(&number, reinterpret_cast<void*>(value + 8), sizeof(number));
        return number;
    }
    if (auto* text = string_data(value)) { try { return std::stod(text); } catch (...) {} }
    return 0.0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0.0;
    }
}
uint64_t lymar_aot_to_integer(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (auto integer = integer_number(value, kind)) return static_cast<Word>(*integer);
    if (!kind) return value;
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0;
    if (auto* text = string_data(value)) {
        try { return static_cast<uint64_t>(std::stoll(text)); }
        catch (...) { return static_cast<unsigned char>(text[0]); }
    }
    return static_cast<uint64_t>(LM::Memory::truncate_i64(lymar_aot_to_float(value, kind)));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_float_to_integer(double number) {
    try {
    RuntimeGuard runtime_guard;

    return static_cast<uint64_t>(LM::Memory::truncate_i64(number));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_to_boolean(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (lymar_aot_is_nil(value, kind)) return 0;
    if (kind != object_kind) return value != 0;
    if ((read_word(value) & 0xffffffff) == 9) return lymar_aot_to_float(value, kind) != 0.0;
    return 1;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_print_integer(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    char text[64];
    const char* output = text;
    size_t length;
    if (lymar_aot_is_nil(value, kind)) { output = "nil"; length = 3; }
    else if (kind == boolean_kind) { output = value ? "true" : "false"; length = value ? 4 : 5; }
    else if (auto integer = integer_number(value, kind)) {
        auto number = integer_text(*integer); std::fwrite(number.data(), 1, number.size(), stdout); std::fflush(stdout); return;
    }
    else if (kind == object_kind && (read_word(value) & 0xffffffff) == 9)
        length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", lymar_aot_to_float(value, kind)));
    else length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value)));
    std::fwrite(output, 1, length, stdout);
    std::fflush(stdout);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_print_float(double value) {
    try {
    RuntimeGuard runtime_guard;

    char text[64];
    const auto length = std::snprintf(text, sizeof(text), "%.6g", value);
    std::fwrite(text, 1, static_cast<size_t>(length), stdout);
    std::fflush(stdout);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_value_equal(uint64_t left, uint64_t right, uint64_t left_kind, uint64_t right_kind) {
    try {
    RuntimeGuard runtime_guard;

    const bool left_nil = lymar_aot_is_nil(left, left_kind), right_nil = lymar_aot_is_nil(right, right_kind);
    if (left_nil || right_nil) return left_nil && right_nil;
    if (left_kind == boolean_kind || right_kind == boolean_kind)
        return left_kind == right_kind && left == right;
    if (left == right && left_kind == right_kind) return 1;
    const Word left_type = left_kind == object_kind ? read_word(left) & 0xffffffff : UINT64_MAX;
    const Word right_type = right_kind == object_kind ? read_word(right) & 0xffffffff : UINT64_MAX;
    if (auto left_integer = integer_number(left, left_kind))
        if (auto right_integer = integer_number(right, right_kind)) return *left_integer == *right_integer;
    if ((integer_number(left, left_kind) || left_type == 9) && (integer_number(right, right_kind) || right_type == 9))
        return left_type == 9 || right_type == 9
            ? lymar_aot_to_float(left, left_kind) == lymar_aot_to_float(right, right_kind) : left == right;
    if (left_type == 11 && right_type == 11) {
        auto size = read_word(left, 8);
        return size == read_word(right, 8) && std::memcmp(reinterpret_cast<void*>(left + 24), reinterpret_cast<void*>(right + 24), size) == 0;
    }
    if (!left_kind && right_type == 11)
        return read_word(right, 8) == 1 && static_cast<uint8_t>(left) == *reinterpret_cast<uint8_t*>(right + 24);
    if (!right_kind && left_type == 11)
        return read_word(left, 8) == 1 && static_cast<uint8_t>(right) == *reinterpret_cast<uint8_t*>(left + 24);
    // Preserve the existing native enum representation and payload equality.
    if (left_type == 0x454e554d && right_type == 0x454e554d)
        return read_word(left, 8) == read_word(right, 8) && read_word(left, 16) == read_word(right, 16);
    return 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_create_checked(uint64_t pointer, uint64_t mode, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    if (is_pointer != object_kind) throw std::runtime_error("Borrow requires a managed object");
    return lymar_aot_ref_create(pointer, mode);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_resolve(uint64_t token, uint64_t writable) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    h.return_pointer = 1;
    if (!token && (writable & LM::Memory::ReferenceNullable)) return 2;
    if ((writable & LM::Memory::ReferenceWritable) && h.worker && shared_heap().reference_owners.at(token).thread != std::this_thread::get_id())
        throw std::runtime_error("Worker cannot write through a captured reference");
    return h.lifetimes.resolve(token, (writable & LM::Memory::ReferenceWritable) != 0);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_move(uint64_t token, uint64_t lexical, uint64_t caller) {
    try {
    RuntimeGuard runtime_guard;

    if (lexical & ~LM::Memory::ReferenceMoveMask) throw std::runtime_error("Invalid AOT reference move mode");
    auto& h = heap();
    h.return_pointer = 0;
    if (!token && (lexical & LM::Memory::ReferenceMoveNullable)) return 0;
    if (h.worker && shared_heap().reference_owners.at(token).thread != std::this_thread::get_id())
        throw std::runtime_error("Worker cannot move a captured reference");
    lexical = static_cast<uint32_t>(lexical & LM::Memory::ReferenceRegionMask);
    auto pointer = h.lifetimes.resolve(token);
    auto target = caller;
    if (lexical) {
        target = h.active;
        while (target && h.regions.at(target).lexical != lexical) target = h.regions.at(target).parent;
        if (!target) throw std::runtime_error("AOT reference move target is not active");
    }
    if (h.regions.at(h.allocations.at(pointer).owner).depth > h.regions.at(target).depth)
        throw std::runtime_error("AOT reference promotion requires owner promotion");
    auto origin = h.lifetimes.reference_region(token);
    if (h.regions.at(origin).depth < h.regions.at(target).depth) target = origin;
    h.return_pointer = 0;
    auto owner = shared_heap().reference_owners.at(token).thread;
    auto moved = h.lifetimes.move_reference(token, target);
    shared_heap().reference_owners.erase(token);
    shared_heap().reference_owners[moved] = {owner,target};
    return moved;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_ref_release(uint64_t token) {
    try {
    RuntimeGuard runtime_guard;
 if (heap().worker && shared_heap().reference_owners.at(token).thread != std::this_thread::get_id())
     throw std::runtime_error("Worker cannot release a captured reference");
 heap().lifetimes.end_borrow(token); shared_heap().reference_owners.erase(token);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_ref_release_nullable(uint64_t token) {
    try {
    RuntimeGuard runtime_guard;

    if (token) lymar_aot_ref_release(token);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_consume(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (!h.allocations.count(pointer)) throw std::runtime_error("AOT consume of unowned object");
    h.lifetimes.adopt(pointer);
    h.lifetimes.consume(pointer);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}

uint64_t lymar_aot_call_enter() {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    h.invocations.push_back({h.active, std::move(h.pending_args), {}, {}});
    h.pending_args.clear();
    return h.active;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_arg_set(uint64_t index, uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& args = heap().pending_args;
    if (args.size() <= index) args.resize(index + 1);
    args[index] = pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_arg_kind(uint64_t index, uint64_t fallback) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    return h.invocations.empty() || index >= h.invocations.back().args.size() ? fallback : h.invocations.back().args[index];

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_arg_get(uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    return h.invocations.empty() || index >= h.invocations.back().args.size() ? 0 : h.invocations.back().args[index];

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_call_leave(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT invocation stack underflow");
    for (auto slot : h.invocations.back().slots) h.shadow.erase(slot);
    h.invocations.pop_back();
    h.return_pointer = pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_return_pointer() {
    try {
    RuntimeGuard runtime_guard;
 return heap().return_pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_param_push(uint64_t value, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT Param outside invocation");
    h.invocations.back().staged_params.emplace_back(value, is_pointer);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_param_pop(uint64_t fallback, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT ConstructError outside invocation");
    auto& params = h.invocations.back().staged_params;
    h.return_pointer = is_pointer;
    if (params.empty()) return fallback;
    auto [value, pointer] = params.back();
    params.pop_back();
    h.return_pointer = pointer;
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_slot_pointer(uint64_t address) {
    try {
    RuntimeGuard runtime_guard;

    auto& flags = heap().shadow;
    auto found = flags.find(address);
    return found != flags.end() ? found->second : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_region_current() {
    try {
    RuntimeGuard runtime_guard;
 return heap().active;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_region_enter(uint64_t lexical) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.next == UINT64_MAX) throw std::overflow_error("AOT region identity exhausted");
    auto id = h.next++;
    h.regions.emplace(id, Region{h.active, lexical, h.regions.at(h.active).depth + 1, {}});
    h.active = id;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_region_exit(uint64_t lexical) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (!h.active || h.regions.at(h.active).lexical != lexical)
        throw std::runtime_error("AOT RegionExit mismatch");
    auto id = h.active;
    auto parent = h.regions.at(id).parent;
    h.cleanup(id);
    h.active = parent;
    h.regions.erase(id);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_region_move(uint64_t value, uint64_t lexical, uint64_t caller, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    auto target = caller;
    if (lexical) {
        target = h.active;
        while (target && h.regions.at(target).lexical != lexical) target = h.regions.at(target).parent;
        if (!target) throw std::runtime_error("AOT RegionMove target is not active");
    }
    // Validate the target even for an immediate value.
    h.regions.at(target);
    if (is_pointer == object_kind) h.promote(value, target);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_alloc(uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (size > SIZE_MAX) throw std::bad_alloc();
    auto pointer = reinterpret_cast<Word>(heap().allocator.allocate(std::max(size, Word(1))));
    if (!pointer) throw std::bad_alloc();
    std::memset(reinterpret_cast<void*>(pointer), 0, std::max(size, Word(1)));
    auto& h = heap();
    try {
        h.allocations.emplace(pointer, Allocation{static_cast<size_t>(std::max(size, Word(1))), h.active, {}});
        h.regions.at(h.active).members.insert(pointer);
    } catch (...) {
        h.allocations.erase(pointer);
        h.allocator.deallocate(reinterpret_cast<void*>(pointer));
        throw;
    }
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_box_float(double number) {
    try {
    RuntimeGuard runtime_guard;

    auto pointer = lymar_aot_alloc(16);
    heap().allocations.at(pointer).float_box = true;
    const Word header = 9; // Existing TYPE_FLOAT header and payload offsets.
    std::memcpy(reinterpret_cast<void*>(pointer), &header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 8), &number, sizeof(number));
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_scalar_to_string(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (kind == object_kind && !lymar_aot_is_nil(value, kind) && (read_word(value) & 0xffffffff) == 11)
        return value;
    std::string wide_text;
    char text[64];
    const char* output = text;
    size_t length;
    if (lymar_aot_is_nil(value, kind)) { output = "nil"; length = 3; }
    else if (kind == boolean_kind) { output = value ? "true" : "false"; length = value ? 4 : 5; }
    else if (kind == object_kind && (read_word(value) & 0xffffffff) == 9)
        length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", lymar_aot_to_float(value, kind)));
    else if (auto integer = integer_number(value, kind)) { wide_text = integer_text(*integer); output = wide_text.c_str(); length = wide_text.size(); }
    else length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value)));
    auto pointer = lymar_aot_alloc(24 + length + 1);
    Word header[] = {11, length, length};
    std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 24), output, length);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Erased scalar arguments must become strings before the generated formatter
// inspects object layouts. A float box is not a list, and a Boolean is not an
// integer. Compound objects retain their existing formatting path.
uint64_t lymar_aot_format_argument(uint64_t value, uint64_t kind) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_is_object(value, kind) || lymar_aot_is_nil(value, kind))
            return lymar_aot_scalar_to_string(value, kind);
        auto type = read_word(value) & 0xffffffff;
        if ((type >= 5 && type <= 9) || integer_number(value, kind))
            return lymar_aot_scalar_to_string(value, kind);
        return value;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_float_to_string(double value) {
    try {
        RuntimeGuard guard;
        char text[64];
        auto length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", value));
        auto pointer = lymar_aot_alloc(24 + length + 1);
        Word header[] = {11, length, length};
        std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
        std::memcpy(reinterpret_cast<void*>(pointer + 24), text, length + 1);
        return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_float_bits_to_string(uint64_t bits) {
    double number;
    std::memcpy(&number, &bits, sizeof(number));
    return lymar_aot_float_to_string(number);
}
uint64_t lymar_aot_tuple_length(uint64_t pointer, uint64_t kind) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_is_object(pointer, kind)) return 0;
        auto record = heap().allocations.find(pointer);
        if (record == heap().allocations.end() || record->second.size < 32)
            throw std::runtime_error("Invalid or expired tuple receiver");
        return (read_word(pointer) & 0xffffffff) == 3 ? read_word(pointer, 16) : 0;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_string_hash(uint64_t value, uint64_t kind) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_string_receiver(value, kind))
            throw std::runtime_error("_builtin_string_hash_bytes expects str");
        Word hash = 5381, length = read_word(value, 8);
        auto* bytes = reinterpret_cast<const unsigned char*>(value + 24);
        for (Word index = 0; index < length; ++index) hash = (hash * 33 + bytes[index]) % 2147483647;
        return hash;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_list_slice(uint64_t value, uint64_t start, uint64_t end,
                              uint64_t kind, uint64_t start_kind, uint64_t end_kind) {
    try {
        RuntimeGuard guard;
        auto& h = heap();
        Word source = 0, count = 0;
        if (!lymar_aot_is_nil(value, kind)) {
            auto record = h.allocations.find(value);
            if (kind != object_kind || record == h.allocations.end() ||
                record->second.size < 32 || (read_word(value) & 0xffffffff) != 1)
                throw std::runtime_error("_builtin_list_slice expects list");
            source = read_word(value, 8); count = read_word(value, 16);
            auto data = h.allocations.find(source);
            if (data == h.allocations.end() || count > data->second.size / sizeof(Word))
                throw std::runtime_error("Invalid list elements allocation");
        }
        auto first = static_cast<int64_t>(lymar_aot_string_index(start, start_kind));
        auto last = static_cast<int64_t>(lymar_aot_string_index(end, end_kind));
        Word begin = std::min(count, static_cast<Word>(std::max<int64_t>(0, first)));
        Word limit = std::min(count, static_cast<Word>(std::max<int64_t>(0, last)));
        Word length = limit > begin ? limit - begin : 0;
        auto pointer = lymar_aot_alloc(32);
        auto elements = lymar_aot_alloc(std::max<Word>(1, length) * sizeof(Word));
        Word header[] = {1, elements, length, std::max<Word>(1, length)};
        std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
        lymar_aot_edge(pointer + 8, elements, object_kind);
        for (Word index = 0; index < length; ++index) {
            auto address = source + (begin + index) * sizeof(Word);
            auto copied = read_word(address);
            auto found = h.shadow.find(address);
            Word mode = found == h.shadow.end() ? 0 : found->second;
            std::memcpy(reinterpret_cast<void*>(elements + index * sizeof(Word)), &copied, sizeof(copied));
            lymar_aot_edge(elements + index * sizeof(Word), copied, mode);
        }
        h.return_pointer = object_kind;
        return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// LoadConst strings are copied into the current region, just as the VM copies
// managed constants into its tracked heap. Static linker storage is never freed.
uint64_t lymar_aot_copy_constant(uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    auto pointer = lymar_aot_alloc(size);
    std::memcpy(reinterpret_cast<void*>(pointer), reinterpret_cast<const void*>(source), size);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_free(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;
 if (pointer) heap().release(pointer);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (!is_pointer && !h.shadow.erase(address)) return;
    auto container = h.containing(address);
    if (is_pointer) h.shadow[address] = is_pointer;
    else h.shadow.erase(address);
    if (container == h.allocations.end()) {
        if (!h.invocations.empty()) h.invocations.back().slots.insert(address);
        return;
    }
    auto offset = address - container->first;
    container->second.edges.erase(offset);
    if (is_pointer == object_kind && h.containing(child) != h.allocations.end()) {
        container->second.edges[offset] = child;
        h.promote(child, container->second.owner);
    }

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
// Raw access is explicitly unsafe in source. Preserve external/FFI addresses;
// use memcpy so valid byte-addressed unaligned accesses do not acquire C++ UB.
// Raw bytes do not transfer pointee ownership; managed stores publish edges separately.
uint64_t lymar_aot_channel_length(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (kind != object_kind || lymar_aot_is_nil(value, kind)) return 0;
    auto& h = heap();
    auto found = h.allocations.find(value);
    if (found == h.allocations.end() || found->second.size < 32 || (read_word(value) & 0xffffffff) != 1)
        return 0; // A non-queue task value is a single invocation, not an iterator.
    return read_word(value, 16);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
static uint64_t raw_address(uint64_t value, uint64_t kind) {
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0;
    if (kind != 0 && kind != object_kind) throw std::runtime_error("Invalid raw pointer kind");
    return value;
}
uint64_t lymar_aot_memory_load_kind(uint64_t pointer, uint64_t element, uint64_t pointer_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    if (!pointer || element >= 8) return object_kind;
    return 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_memory_load(uint64_t pointer, uint64_t element, uint64_t pointer_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    if (element > 10) throw std::runtime_error("Invalid raw memory element kind");
    if (!pointer) return lymar_aot_nil();
    const auto* address = reinterpret_cast<const void*>(pointer);
    switch (element) {
#define LM_RAW_LOAD(ID, TYPE) case ID: { TYPE value; std::memcpy(&value, address, sizeof(value)); return static_cast<Word>(value); }
        LM_RAW_LOAD(0, int8_t) LM_RAW_LOAD(1, uint8_t)
        LM_RAW_LOAD(2, int16_t) LM_RAW_LOAD(3, uint16_t)
        LM_RAW_LOAD(4, int32_t) LM_RAW_LOAD(5, uint32_t)
        LM_RAW_LOAD(6, int64_t) LM_RAW_LOAD(7, uint64_t)
#undef LM_RAW_LOAD
        case 8: { float value; std::memcpy(&value, address, sizeof(value)); return lymar_aot_box_float(value); }
        case 9: { double value; std::memcpy(&value, address, sizeof(value)); return lymar_aot_box_float(value); }
        case 10: { Word value; std::memcpy(&value, address, sizeof(value)); return value; }
    }
    throw std::runtime_error("Invalid raw memory element kind");

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Raw stores use the VM's physical numeric conversion, not string parsing or
// arbitrary object-header heuristics. Raw buffers may themselves begin with 9.
static double raw_numeric_value(uint64_t value, uint64_t kind) {
    if (kind == 0) return static_cast<double>(static_cast<int64_t>(value));
    if (kind != object_kind) return 0.0;
    auto found = heap().allocations.find(value);
    if (found == heap().allocations.end() || !found->second.float_box || found->second.size < 16 ||
        (read_word(value) & 0xffffffff) != 9) return 0.0;
    double result; std::memcpy(&result, reinterpret_cast<void*>(value + 8), sizeof(result));
    return result;
}
static uint64_t raw_integer_value(uint64_t value, uint64_t kind) {
    return kind == 0 ? value : static_cast<Word>(static_cast<int64_t>(raw_numeric_value(value, kind)));
}
uint64_t lymar_aot_raw_alloc(uint64_t size, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    size = raw_integer_value(size, kind);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    auto pointer = lymar_aot_alloc(size);
    heap().allocations.at(pointer).raw_memory = true;
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_raw_free(uint64_t pointer, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, kind);
    auto found = heap().allocations.find(pointer);
    if (found != heap().allocations.end() && found->second.raw_memory) heap().release(pointer);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_memory_store(uint64_t pointer, uint64_t value, uint64_t element, uint64_t kind, uint64_t pointer_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    if (element > 10) throw std::runtime_error("Invalid raw memory element kind");
    if (!pointer) return;
    auto* address = reinterpret_cast<void*>(pointer);
    const Word integer = element < 8 ? raw_integer_value(value, kind) : value;
    size_t width = 0;
    switch (element) {
#define LM_RAW_STORE(ID, TYPE, VALUE) case ID: { TYPE stored = static_cast<TYPE>(VALUE); width = sizeof(stored); std::memcpy(address, &stored, width); break; }
        LM_RAW_STORE(0, int8_t, integer) LM_RAW_STORE(1, uint8_t, integer)
        LM_RAW_STORE(2, int16_t, integer) LM_RAW_STORE(3, uint16_t, integer)
        LM_RAW_STORE(4, int32_t, integer) LM_RAW_STORE(5, uint32_t, integer)
        LM_RAW_STORE(6, int64_t, integer) LM_RAW_STORE(7, uint64_t, integer)
        LM_RAW_STORE(8, float, raw_numeric_value(value, kind))
        LM_RAW_STORE(9, double, raw_numeric_value(value, kind))
        LM_RAW_STORE(10, Word, (kind == 0 || (kind == object_kind && !lymar_aot_is_nil(value, kind))) ? value : 0)
#undef LM_RAW_STORE
    }
    auto& h = heap();
    // At most fifteen byte-addressed word slots overlap an eight-byte write;
    // do not scan unrelated stack/object kind metadata on every raw store.
    h.forget_kinds(pointer, width, true);
    auto owner = h.containing(pointer);
    if (owner != h.allocations.end()) {
        auto start = pointer - owner->first;
        for (size_t offset = start >= sizeof(Word) - 1 ? start - (sizeof(Word) - 1) : 0;
             offset <= start || offset - start < width; ++offset) {
            owner->second.edges.erase(offset);
            if (offset == SIZE_MAX) break;
        }
    }
    // Physical raw-pointer bytes do not acquire ownership. The VM does not
    // promote pointees on MemoryStore; canonical managed stores publish edges
    // separately through lymar_aot_edge. Preserve destructor scope/order.

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_global_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (is_pointer) { h.shadow[address] = is_pointer; if (is_pointer == object_kind) h.promote(child, 0); }
    else h.shadow.erase(address);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_copy(uint64_t destination, uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    // Snapshot every value kind before memmove, including overlapping ranges.
    std::vector<std::pair<Word, Word>> kinds;
    for (auto entry = h.shadow.lower_bound(source); entry != h.shadow.end() && entry->first - source < size; ++entry)
        if (size - (entry->first - source) >= sizeof(Word))
            kinds.emplace_back(destination + entry->first - source, entry->second);
    std::memmove(reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), size);
    h.forget_kinds(destination, size, true);
    auto dst = h.containing(destination);
    if (dst != h.allocations.end()) {
        auto start = destination - dst->first;
        std::erase_if(dst->second.edges, [&](auto edge) { return edge.first >= start ? edge.first - start < size : start - edge.first < sizeof(Word); });
    }
    for (auto [address, kind] : kinds) lymar_aot_edge(address, read_word(address), kind);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_copy(uint64_t destination, uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!destination || !source || static_cast<int64_t>(size) <= 0) return;
    auto& h = heap();
    // Raw byte copies carry no ownership contract. Managed aggregate copies
    // use lymar_aot_copy and explicitly preserve their edges/kinds instead.
    h.forget_kinds(destination, size, true);
    auto owner = h.containing(destination);
    if (owner != h.allocations.end()) {
        auto start = destination - owner->first;
        std::erase_if(owner->second.edges, [&](auto entry) {
            return entry.first >= start ? entry.first - start < size : start - entry.first < sizeof(Word);
        });
    }
    std::memmove(reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_fill(uint64_t destination, uint64_t value, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!destination || static_cast<int64_t>(size) <= 0) return;
    auto& h = heap();
    // Invalidate overlapping kinds/edges; byte filling must not retain a
    // pointer edge whose bytes have been replaced by unrelated data.
    h.forget_kinds(destination, size, true);
    auto owner = h.containing(destination);
    if (owner != h.allocations.end()) {
        auto start = destination - owner->first;
        std::erase_if(owner->second.edges, [&](auto entry) {
            return entry.first >= start ? entry.first - start < size : start - entry.first < sizeof(Word);
        });
    }
    std::memset(reinterpret_cast<void*>(destination), static_cast<unsigned char>(value), size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_raw_compare(uint64_t left, uint64_t right, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!left || !right || static_cast<int64_t>(size) <= 0) return 0;
    return static_cast<int64_t>(std::memcmp(reinterpret_cast<void*>(left), reinterpret_cast<void*>(right), size));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_resize(uint64_t pointer, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!pointer) return lymar_aot_alloc(size);
    if (!size) { lymar_aot_free(pointer); return 0; }
    auto& h = heap();
    auto original = h.allocations.at(pointer);
    auto replacement = lymar_aot_alloc(size);
    auto& allocation = h.allocations.at(replacement);
    h.regions.at(allocation.owner).members.erase(replacement);
    allocation.owner = original.owner;
    h.regions.at(allocation.owner).members.insert(replacement);
    allocation.finalizer = original.finalizer;
    allocation.float_box = original.float_box;
    allocation.raw_memory = original.raw_memory;
    lymar_aot_copy(replacement, pointer, std::min(size, Word(original.size)));
    lymar_aot_free(pointer);
    return replacement;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_raw_resize(uint64_t pointer, uint64_t size, uint64_t pointer_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    size = raw_integer_value(size, size_kind);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    if (!pointer) return lymar_aot_raw_alloc(size, 0);
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || !found->second.raw_memory) return lymar_aot_nil();
    if (!size) { heap().release(pointer); return lymar_aot_nil(); }
    return lymar_aot_resize(pointer, size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_raw_copy_checked(uint64_t destination, uint64_t source, uint64_t size,
                               uint64_t destination_kind, uint64_t source_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    lymar_aot_raw_copy(raw_address(destination, destination_kind), raw_address(source, source_kind), raw_integer_value(size, size_kind));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_fill_checked(uint64_t destination, uint64_t value, uint64_t size,
                               uint64_t destination_kind, uint64_t value_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    lymar_aot_raw_fill(raw_address(destination, destination_kind), raw_integer_value(value, value_kind), raw_integer_value(size, size_kind));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_raw_compare_checked(uint64_t left, uint64_t right, uint64_t size,
                                     uint64_t left_kind, uint64_t right_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    return lymar_aot_raw_compare(raw_address(left, left_kind), raw_address(right, right_kind), raw_integer_value(size, size_kind));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_set_finalizer(uint64_t pointer, void (*callback)(uint64_t)) {
    try {
    RuntimeGuard runtime_guard;

    heap().allocations.at(pointer).finalizer = callback;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_finalize(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;
 heap().finalize(pointer);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_resource_create(uint64_t type, uint64_t) {
    try {
    RuntimeGuard runtime_guard;

    if (type == 9) return 0; // stdout
    if (type == 10) return 1; // stderr
    if (type != 0) throw std::runtime_error("Standalone resource type is not implemented: " + std::to_string(type));
    auto& f = files();
    auto id = f.next++;
    f.handles.emplace(id, nullptr);
    return id;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_resource_destroy(uint64_t id) {
    try {
    RuntimeGuard runtime_guard;

    auto& f = files();
    auto found = f.handles.find(id);
    if (found == f.handles.end()) return;
    if (found->second) std::fclose(found->second);
    f.handles.erase(found);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_resource_call(uint64_t id, uint64_t operation, uint64_t count, uint64_t arguments) {
    try {
    RuntimeGuard runtime_guard;

    constexpr Word nil = 2;
    auto& h = heap();
    h.return_pointer = object_kind; // Default failure is nil.
    std::vector<Word> args;
    std::vector<Word> pointers;
    for (Word n = 0; n < count; ++n) {
        auto value = read_word(arguments, n * 8);
        Word pointer = lymar_aot_slot_pointer(arguments + n * 8);
        if (pointer == object_kind && value > 4096 && (read_word(value) & 0xffffffff) == 1) {
            auto data = read_word(value, 8), size = read_word(value, 16);
            for (Word i = 0; i < size; ++i) {
                args.push_back(read_word(data, i * 8));
                pointers.push_back(lymar_aot_slot_pointer(data + i * 8));
            }
        } else if (!lymar_aot_is_nil(value, pointer)) { args.push_back(value); pointers.push_back(pointer); }
    }
    auto arg_string = [&](size_t n) { return n < args.size() && pointers[n] == object_kind ? string_data(args[n]) : nullptr; };
    auto& f = files();
    auto found = f.handles.find(id);
    if (id > 1 && found == f.handles.end()) return nil;
    FILE* stream = id == 0 ? stdout : id == 1 ? stderr : found->second;
    // These operations return booleans in the VM, even through the any API.
    h.return_pointer = (operation == 2 || operation == 47) ? object_kind : boolean_kind;
    if (operation == 0) {
        if (id <= 1) return 0;
        if (stream) std::fclose(stream);
        const auto* path = arg_string(0);
        const auto* mode = arg_string(1);
        found->second = path && mode ? std::fopen(path, mode) : nullptr;
        return found->second != nullptr;
    }
    if (operation == 1) { lymar_aot_resource_destroy(id); return 1; }
    if (operation == 10) return stream != nullptr;
    if (operation == 29) return stream && std::fflush(stream) == 0;
    if (operation == 3) {
        auto* data = arg_string(0);
        if (!stream || !data) return 0;
        auto length = read_word(args[0], 8);
        auto written = std::fwrite(data, 1, length, stream);
        return std::fflush(stream) == 0 && written == length;
    }
    if (operation == 2 || operation == 47) {
        if (!stream) return nil;
        std::vector<unsigned char> bytes;
        unsigned char buffer[4096];
        size_t length;
        while ((length = std::fread(buffer, 1, sizeof(buffer), stream)))
            bytes.insert(bytes.end(), buffer, buffer + length);
        if (std::ferror(stream)) return nil;
        Word result;
        if (operation == 2) {
            result = lymar_aot_alloc(24 + bytes.size() + 1);
            auto* header = reinterpret_cast<Word*>(result);
            header[0] = 11; header[1] = header[2] = bytes.size();
            if (!bytes.empty()) std::memcpy(reinterpret_cast<void*>(result + 24), bytes.data(), bytes.size());
        } else {
            result = lymar_aot_alloc(32);
            auto data = lymar_aot_alloc(std::max(size_t(1), bytes.size()) * 8);
            auto* header = reinterpret_cast<Word*>(result);
            header[0] = 1; header[1] = data; header[2] = bytes.size(); header[3] = std::max(size_t(1), bytes.size());
            lymar_aot_edge(result + 8, data, 1);
            auto* elements = reinterpret_cast<Word*>(data);
            for (size_t i = 0; i < bytes.size(); ++i) elements[i] = bytes[i];
        }
        h.return_pointer = 1;
        return result;
    }
    if (operation == 30 || operation == 32 || operation == 33 || operation == 34) {
        auto* path = arg_string(0);
        if (!path) return 0;
        std::error_code error;
        if (operation == 30) return std::filesystem::create_directories(path, error);
        if (operation == 33) return std::filesystem::exists(path, error);
        if (operation == 34) return std::filesystem::remove(path, error);
        auto* destination = arg_string(1);
        if (!destination) return 0;
        std::filesystem::rename(path, destination, error);
        return !error;
    }
    throw std::runtime_error("Standalone file operation is not implemented: " + std::to_string(operation));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
[[noreturn]] void lymar_aot_exit(uint64_t status) { std::exit(static_cast<int>(status)); }
uint64_t lymar_aot_live_allocations() {
    try {
    RuntimeGuard runtime_guard;
 return heap().allocations.size();
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_reset() {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.active || !h.invocations.empty()) throw std::runtime_error("AOT reset with active invocation");
    h.cleanup(0);
    h.shadow.clear();
    h.lifetimes.reset();
    while (!h.files.handles.empty()) lymar_aot_resource_destroy(h.files.handles.begin()->first);
    h.pending_args.clear();
    h.return_pointer = 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}

// These are private standalone helpers for existing canonical concurrency ops.
// Generated code tests the worker error flag before using a failed result.
uint64_t lymar_aot_worker_failed() {
    auto& h = heap();
    if (!h.worker) return 0;
    if (h.timed && std::chrono::steady_clock::now() >= h.deadline && !h.worker_error[0]) {
        h.timed_out=true;
        std::snprintf(h.worker_error,sizeof(h.worker_error),"Concurrent block exceeded its timeout");
        if(h.cancellation) h.cancellation->store(true);
    }
    if (h.cancellation && h.cancellation->load(std::memory_order_acquire) && !h.worker_error[0])
        std::snprintf(h.worker_error, sizeof(h.worker_error), "Worker cancelled");
    return h.worker_error[0] != 0;
}
void lymar_aot_call_abort() {
    RuntimeGuard guard;
    auto& h = heap();
    if (h.invocations.empty()) return;
    const auto region = h.invocations.back().region;
    while (h.active != region) {
        auto current = h.active, parent = h.regions.at(current).parent;
        h.cleanup(current); h.regions.erase(current); h.active = parent;
    }
    for (auto slot : h.invocations.back().slots) h.shadow.erase(slot);
    h.invocations.pop_back(); h.pending_args.clear(); h.return_pointer = 0;
}
void lymar_aot_assert(uint64_t condition, uint64_t message) {
    if (condition == 1 || condition == 18) return;
    auto text = message > 4096 ? string_data(message) : nullptr;
    if (!heap().worker) {
        if(text) std::printf("%s\n",text); else std::printf("Assertion failed\n");
        std::fflush(stdout);
        std::exit(1);
    }
    if (!heap().worker_error[0])
        std::snprintf(heap().worker_error, sizeof(heap().worker_error), "Assertion failed: %s", text ? text : "assertion");
}

static void checked_queue(Word pointer) {
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || found->second.size < 32 || (read_word(pointer) & 0xffffffff) != 1)
        throw std::runtime_error("Invalid or expired channel");
    auto size = read_word(pointer,16), capacity = read_word(pointer,24), data = read_word(pointer,8);
    auto buffer = heap().allocations.find(data);
    if (size > capacity || buffer == heap().allocations.end() || capacity > buffer->second.size / 8)
        throw std::runtime_error("Invalid channel storage");
}
uint64_t lymar_aot_channel_new() {
    try {
    RuntimeGuard guard;
    auto pointer = lymar_aot_alloc(32), data = lymar_aot_alloc(128);
    *reinterpret_cast<Word*>(pointer) = 1;
    *reinterpret_cast<Word*>(pointer+8) = data;
    *reinterpret_cast<Word*>(pointer+24) = 16;
    lymar_aot_edge(pointer+8,data,object_kind);
    heap().return_pointer = object_kind;
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_channel_push(uint64_t pointer, uint64_t value, uint64_t kind) {
    try {
        RuntimeGuard guard; checked_queue(pointer);
        if (shared_heap().closed_channels.count(pointer)) throw std::runtime_error("Send to closed channel");
        auto length = read_word(pointer,16), capacity = read_word(pointer,24), data = read_word(pointer,8);
        if (length == capacity) {
            if (capacity > UINT64_MAX / 16) throw std::overflow_error("Channel capacity overflow");
            data = lymar_aot_resize(data, capacity * 16);
            *reinterpret_cast<Word*>(pointer+8) = data;
            *reinterpret_cast<Word*>(pointer+24) = capacity * 2;
            lymar_aot_edge(pointer+8,data,object_kind);
        }
        auto address = data + length * 8;
        lymar_aot_edge(address,value,kind);
        *reinterpret_cast<Word*>(address) = value;
        *reinterpret_cast<Word*>(pointer+16) = length + 1;
        shared_heap().work_available.notify_all();
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
    }
}
uint64_t lymar_aot_channel_pop(uint64_t pointer) {
    try {
        RuntimeGuard guard; checked_queue(pointer);
        auto length = read_word(pointer,16), data = read_word(pointer,8);
        if (!length) { heap().return_pointer = object_kind; return 2; }
        auto value = read_word(data), kind = heap().shadow.count(data) ? heap().shadow.at(data) : 0;
        for (Word index = 1; index < length; ++index) {
            auto old_address = data + index * 8, address = old_address - 8;
            auto element = read_word(old_address);
            auto mode = heap().shadow.count(old_address) ? heap().shadow.at(old_address) : 0;
            *reinterpret_cast<Word*>(address) = element;
            lymar_aot_edge(address,element,mode);
        }
        lymar_aot_edge(data+(length-1)*8,0,0);
        *reinterpret_cast<Word*>(pointer+16) = length-1;
        heap().return_pointer = kind;
        return value;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
uint64_t lymar_aot_channel_has_data(uint64_t pointer) {
    try { RuntimeGuard guard; checked_queue(pointer); heap().return_pointer=0; return read_word(pointer,16)!=0; }
    catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_channel_close(uint64_t pointer) {
    try { RuntimeGuard guard; checked_queue(pointer); shared_heap().closed_channels.insert(pointer); shared_heap().work_available.notify_all(); }
    catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
    }
}
uint64_t lymar_aot_scheduler_new(uint64_t cores, uint64_t timeout, uint64_t config) {
    try {
    RuntimeGuard guard;
    auto pointer = lymar_aot_channel_new();
    shared_heap().schedulers[pointer] = {std::max(Word(1),cores),timeout,config};
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth || !heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_scheduler_run(uint64_t pointer) {
    RuntimeSuspend release_parent_lock;
    struct Job { Word context, item, kind; };
    std::vector<Job> jobs;
    std::vector<Word> streams;
    Word parent_region;
    SchedulerConfiguration configuration;
    {
        RuntimeGuard guard; checked_queue(pointer);
        configuration = shared_heap().schedulers.at(pointer); parent_region = heap().active;
        auto length = read_word(pointer,16), data = read_word(pointer,8);
        for (Word index=0; index<length; ++index) {
            auto context = read_word(data,index*8);
            auto found = heap().allocations.find(context);
            if (found == heap().allocations.end() || found->second.size < 64 || !read_word(context,32))
                throw std::runtime_error("Invalid native task context");
            if (read_word(context,24)==1) { checked_queue(read_word(context,8)); streams.push_back(context); }
            else jobs.push_back({context,read_word(context,8),heap().shadow.count(context+8)?heap().shadow.at(context+8):0});
        }
    }
    if (jobs.empty() && streams.empty()) return;
    const Word policy = (configuration.config >> 24) & 3;
    const Word timeout_policy = (configuration.config >> 26) & 3;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(configuration.timeout);
    std::atomic<bool> stop{false};
    std::mutex selection;
    size_t next=0, active_producers=0;
    std::string failure;
    std::vector<std::thread> workers;
    auto worker = [&] {
        auto& h = heap(); h.worker=true; h.base=h.active=parent_region; h.cancellation=&stop; h.deadline=deadline; h.timed=configuration.timeout && timeout_policy!=1;
        for (;;) {
            Job job{}; bool producer=false, pending=false;
            {
                std::lock_guard lock(selection);
                if (stop.load()) break;
                if (configuration.timeout && std::chrono::steady_clock::now() >= deadline && timeout_policy != 1) {
                    if (failure.empty() && timeout_policy != 2) failure="Concurrent block exceeded its timeout";
                    stop.store(true); break;
                }
                if (next < jobs.size()) { job=jobs[next++]; ++active_producers; producer=true; }
                else {
                    RuntimeGuard guard;
                    for (auto context : streams) {
                        auto queue = read_word(context,8);
                        if (read_word(queue,16)) { auto value=lymar_aot_channel_pop(queue); job={context,value,h.return_pointer}; break; }
                    }
                    pending = active_producers != 0;
                }
            }
            if (!job.context) {
                if (!pending) break;
                std::unique_lock lock(shared_heap().mutex);
                shared_heap().work_available.wait_for(lock,std::chrono::milliseconds(1));
                continue;
            }
            h.worker_error[0]=0;h.timed_out=false;
            h.pending_args={object_kind,job.kind,0};
            auto callback = reinterpret_cast<Word(*)(Word,Word)>(read_word(job.context,32));
            callback(job.context,job.item);
            const bool failed = h.worker_error[0]!=0;
            {
                RuntimeGuard guard;
                while (!h.invocations.empty()) lymar_aot_call_abort();
                while (h.active != parent_region) {
                    auto current=h.active, parent=h.regions.at(current).parent;
                    h.cleanup(current);h.regions.erase(current);h.active=parent;
                }
            }
            {
                std::lock_guard lock(selection);
                if (producer) --active_producers;
                if (failed && std::strcmp(h.worker_error,"Worker cancelled")!=0) {
                    if (h.timed_out) {
                        if (timeout_policy != 2 && failure.empty()) failure=h.worker_error;
                        stop.store(true);
                    } else {
                        if (policy != 2 && failure.empty()) failure=h.worker_error;
                        if (policy != 1) stop.store(true);
                    }
                }
                shared_heap().work_available.notify_all();
            }
        }
        h.cancellation=nullptr;
    };
    // Join every started worker even if thread creation fails. No detached work
    // may outlive captured regions, borrowed references or the scheduler.
    try {
        const auto count=std::min<Word>(configuration.cores,std::max(size_t(1),jobs.size()+streams.size()));
        for (Word index=0; index<count; ++index) workers.emplace_back(worker);
    } catch (...) {
        stop.store(true); for(auto& thread:workers) thread.join(); throw;
    }
    for(auto& thread:workers) thread.join();
    if (!failure.empty()) {
        if (heap().worker) {
            if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.c_str());
        } else { std::fprintf(stderr,"%s\n",failure.c_str()); std::exit(1); }
    }
}

}
