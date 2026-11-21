// Private standalone-AOT ownership helpers. No public object/header fields.
#include "memory.hh"
#include "region_instances.hh"
#include "reference_flags.hh"
#include "aot_value_kind.hh"
#include "numeric_conversion.hh"
#include "numeric_semantics.hh"
#include "atomic_field.hh"
#include "../runtime/hash_engine.hh"
#include "../runtime/os_info.hh"
#include "aot_ffi_values.hh"
#if !defined(__wasi__)
#include "aot_graphics_access.hh"
#if defined(__GNUC__) && !defined(__wasi__)
// Make only this TU's reference to the graphics factory weak: console-only
// builds then leave it NULL rather than extracting aot_graphics.o from the
// runtime archive. See aot_graphics_access.hh for the extraction contract.
#pragma weak aot_gfx_create
#endif
#endif
#include <optional>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#if !defined(_WIN32)
#include <dirent.h>
#endif
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
#include <functional>
#include <cmath>
#include <limits>
#if defined(_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <windows.h>

#endif

namespace {
using Word = uint64_t;
constexpr Word object_kind = static_cast<Word>(LM::Memory::AOTValueKind::Object);
constexpr Word boolean_kind = static_cast<Word>(LM::Memory::AOTValueKind::Boolean);

constexpr Word TAG_PTR = 0x0ULL;
constexpr Word TAG_INT = 0x1ULL;
constexpr Word TAG_IMMEDIATE = 0x2ULL;
constexpr Word TAG_MASK = 0x7ULL;

constexpr Word VAL_NIL = (0ULL << 3) | TAG_IMMEDIATE;
constexpr Word VAL_FALSE = (1ULL << 3) | TAG_IMMEDIATE;
constexpr Word VAL_TRUE = (2ULL << 3) | TAG_IMMEDIATE;

constexpr int64_t MAX_SMI = (int64_t)((1ULL << 60) - 1);
constexpr int64_t MIN_SMI = (-(int64_t)(1ULL << 60));

// Standalone-AOT stdout writer. The self-contained PE entry point (_start) calls
// main directly and never runs the C-runtime startup, so on Windows the UCRT
// `stdout` FILE* is left NULL and std::fwrite silently writes nothing. Writing
// through the OS console handle keeps print/output working without depending on
// CRT stdio initialization. POSIX keeps the normal buffered stream.
// GUI-subsystem dual console: the PE entry point never runs CRT startup,
// so a GUI app has no std handles. AttachConsole(ATTACH_PARENT_PROCESS) once
// and open CONOUT$/CONIN$ directly; when there is no parent console (Explorer
// launch) every call fails fast and output stays silently discarded.
#if defined(_WIN32)
namespace {
long g_console_attach_tried = 0;
HANDLE lymar_console_handle(DWORD which, DWORD access, const char* device) {
    HANDLE h = GetStdHandle(which);
    if (h && h != INVALID_HANDLE_VALUE) return h;
    if (!g_console_attach_tried) {
        g_console_attach_tried = 1;
        AttachConsole(ATTACH_PARENT_PROCESS);
    }
    return CreateFileA(device, access, FILE_SHARE_READ | FILE_SHARE_WRITE,
                       nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}
}
#endif

void lymar_stdout_write(const void* data, size_t len) {
    if (!data || len == 0) return;
#if defined(_WIN32)
    HANDLE handle = lymar_console_handle(STD_OUTPUT_HANDLE, GENERIC_WRITE, "CONOUT$");
    if (!handle || handle == INVALID_HANDLE_VALUE) return;
    const char* bytes = static_cast<const char*>(data);
    size_t offset = 0;
    while (offset < len) {
        DWORD chunk = static_cast<DWORD>(len - offset);
        DWORD written = 0;
        if (!WriteFile(handle, bytes + offset, chunk, &written, nullptr) || written == 0) break;
        offset += written;
    }
#else
    std::fwrite(data, 1, len, stdout);
    std::fflush(stdout);
#endif
}
#if !defined(__wasi__)
// GraphicsValue/GraphicsBase/NativeGraphicsAccess come from
// aot_graphics_access.hh. The SoftwareGraphicsResource instantiation and its
// sokol/truetype/d3d11 backends live in aot_graphics.cpp so console-only
// programs do not pull the graphics objects out of the runtime archive; only
// the value-access methods below (which need heap internals) stay here.
#endif
struct Allocation {
    size_t size;
    Word owner;
    std::unordered_map<size_t, Word> edges;
    void (*finalizer)(Word) = nullptr;
    bool finalized = false;
    bool float_box = false;
    bool raw_memory = false;
    bool dictionary = false;
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
    // Stateless service handles (ResourceType::OS, ResourceType::PROCESS) mapped
    // to their resource type. They own nothing, so only the kind is recorded.
    std::unordered_map<uint64_t, uint64_t> services;
    std::map<Word,LM::Runtime::HashEngine> hashes;
    std::map<Word, std::pair<void*, size_t>> mems;
#if !defined(__wasi__)
    std::map<Word,std::unique_ptr<GraphicsBase>> graphics;
#endif
    // Release OS-facing resources held by the file/service tables. Driven
    // explicitly from SharedHeap::shutdown() rather than a destructor because
    // the SharedHeap singleton is intentionally process-lifetime (leaked) so it
    // outlives every thread_local Heap whose exit-time teardown still needs it.
    void close() {
        for (auto [id, file] : handles) if (file) std::fclose(file);
        for (auto [id, buf] : mems) if (buf.first) std::free(buf.first);
    }
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
    SharedHeap() {
        std::set_terminate([]() {
            try {
                auto eptr = std::current_exception();
                if (eptr) std::rethrow_exception(eptr);
            } catch (const std::exception& e) {
                std::string msg = std::string("[AOT FATAL UNCAUGHT EXCEPTION]: ") + e.what() + "\n";
                std::fprintf(stderr, "%s", msg.c_str());
                std::fflush(stderr);
                lymar_stdout_write(msg.c_str(), msg.size());
            } catch (...) {
                const char msg[] = "[AOT FATAL UNCAUGHT UNKNOWN EXCEPTION]\n";
                std::fprintf(stderr, "%s", msg);
                std::fflush(stderr);
                lymar_stdout_write(msg, sizeof(msg) - 1);
            }
            std::abort();
        });
    }
    std::recursive_mutex mutex;
    std::thread::id owner = std::this_thread::get_id();
    LM::Memory::DefaultAllocator allocator;
    LM::Memory::LifetimeRegistry lifetimes;
    Word next = 1;
    std::unordered_map<Word, Allocation> allocations;
    std::unordered_map<Word, std::vector<Word>> page_map;
    ConcurrentRegions regions;
    std::map<Word,ReferenceOwner> reference_owners;
    Files files;
    std::map<Word,SchedulerConfiguration> schedulers;
    std::unordered_set<Word> closed_channels;
    std::condition_variable_any work_available;
    // Deterministic exit teardown, run once on the owner thread from ~Heap after
    // every region has unwound. Because the singleton is leaked (see
    // shared_heap()), no destructor fires at process exit, so file streams and
    // native graphics are released here instead.
    void shutdown() {
        files.close();
#if !defined(__wasi__)
        files.graphics.clear();
#endif
    }
};
// Deliberately leaked process-lifetime singleton. The per-thread Heap's
// exit-time destructor (~Heap) unwinds still-open regions and finalizes
// globals through these tables (allocations, regions, allocator). A
// function-local static would be destroyed during process exit BEFORE the
// thread_local ~Heap runs, leaving ~Heap reading a freed ConcurrentRegions --
// a use-after-free that surfaced as std::out_of_range("Inactive region
// identity") at exit for every AOT program. The OS reclaims this fixed-size
// control block at termination.
SharedHeap& shared_heap() { static SharedHeap* state = new SharedHeap();
    return *state; }
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
static inline uint64_t current_monotonic_ms() {
#ifdef _WIN32
    return GetTickCount64();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * 1000 + static_cast<uint64_t>(ts.tv_nsec / 1000000);
#endif
}

struct Heap {
    LM::Memory::DefaultAllocator& allocator = shared_heap().allocator;
    LM::Memory::LifetimeRegistry& lifetimes = shared_heap().lifetimes;
    struct Invocation {
        Word region = 0;
        std::vector<Word> staged_params;
    };
    Word active = 0, base = 0;
    Word& next = shared_heap().next;
    bool worker = false;
    char worker_error[1024] = {};
    std::atomic<bool>* cancellation = nullptr;
    uint64_t deadline_ms = 0;
    bool timed = false, timed_out = false;
    std::unordered_map<Word, Allocation>& allocations = shared_heap().allocations;
    std::unordered_map<Word, std::vector<Word>>& page_map = shared_heap().page_map;
    ConcurrentRegions& regions = shared_heap().regions;
    std::vector<Invocation> invocations;
    Files& files = shared_heap().files;

    auto containing(Word address) {
        auto exact = allocations.find(address);
        if (exact != allocations.end()) return exact;
        Word page = address >> 12;
        auto page_it = page_map.find(page);
        if (page_it != page_map.end()) {
            for (Word start : page_it->second) {
                auto alloc_it = allocations.find(start);
                if (alloc_it != allocations.end() && address >= start && address - start < alloc_it->second.size) {
                    return alloc_it;
                }
            }
        }
        return allocations.end();
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
        lifetimes.revoke(pointer);
        shared_heap().schedulers.erase(pointer);
        shared_heap().closed_channels.erase(pointer);
        Word size = found->second.size;
        Word start_page = pointer >> 12;
        Word end_page = (pointer + std::max<Word>(1, size) - 1) >> 12;
        for (Word page = start_page; page <= end_page; ++page) {
            auto page_it = page_map.find(page);
            if (page_it != page_map.end()) {
                std::erase(page_it->second, pointer);
                if (page_it->second.empty()) page_map.erase(page_it);
            }
        }
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
            if (std::this_thread::get_id() == shared_heap().owner) {
                cleanup(0);
                // Finalize globals first (cleanup above), then release the
                // process-level file/graphics resources the leaked singleton
                // would otherwise never free via a destructor.
                shared_heap().shutdown();
            }
        } catch (const std::exception& e) {
            std::fprintf(stderr, "[~Heap EXCEPTION]: %s\n", e.what());
            std::fflush(stderr);
        } catch (...) {
            std::fprintf(stderr, "[~Heap UNKNOWN EXCEPTION]\n");
            std::fflush(stderr);
        }
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
    if (value <= 4096 || (value & TAG_MASK) != TAG_PTR) return nullptr;
    auto found = heap().allocations.find(value);
    if (found != heap().allocations.end()) {
        if (found->second.raw_memory || found->second.dictionary || found->second.size < 25 || (read_word(value) & 0xffffffff) != 11 || read_word(value, 8) > found->second.size - 25) return nullptr;
        return reinterpret_cast<const char*>(value + 24);
    }
    if ((read_word(value) & 0xffffffff) == 11) {
        return reinterpret_cast<const char*>(value + 24);
    }
    return nullptr;
}
// LmValue tag inspection: every managed word is self-describing.
//   (word & 7) == 0  -> TAG_PTR: heap object pointer (validated via allocations)
//   (word & 7) == 1  -> TAG_INT: SMI, payload = word >> 3
//   (word & 7) == 2  -> TAG_IMMEDIATE: VAL_NIL(2) / VAL_FALSE(10) / VAL_TRUE(18)
static inline bool is_heap_word(Word value) {
    return (value & TAG_MASK) == TAG_PTR && value > 4096 && heap().allocations.count(value);
}
static inline Word word_tag(Word value) { return value & TAG_MASK; }
// Numeric decode shared by to_integer/to_float/numeric_*. Returns disengaged
// for non-numeric tagged words (strings, lists, frames, nil, booleans).
std::optional<__int128> integer_number(Word value) {
    Word tag = word_tag(value);
    if (tag == TAG_INT) return static_cast<int64_t>(value) >> 3;
    if (tag == TAG_IMMEDIATE) return {};
    if (tag != TAG_PTR || value <= 4096) return {};
    auto found = heap().allocations.find(value);
    if (found == heap().allocations.end()) return {};
    if (found->second.raw_memory || found->second.dictionary || found->second.size < 16) return {};
    auto type = read_word(value) & 0xffffffff;
    if ((type==7 || type==8) && found->second.size<32) return {};
    if (type == 5) return static_cast<int64_t>(read_word(value, 8));
    if (type == 6 || type == 13) return read_word(value, 8);
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
// Renders a boxed i128/u128 (allocation type 7/8) respecting unsignedness.
// integer_number() widens both into __int128, so u128 values at or above
// 2^127 would print as negative without this dispatch. Disengaged for
// non-wide values so callers keep the integer_number() path.
std::optional<std::string> wide_box_text(Word value) {
    if (!is_heap_word(value)) return {};
    auto found = heap().allocations.find(value);
    if (found == heap().allocations.end() || found->second.raw_memory ||
        found->second.dictionary || found->second.size < 32) return {};
    auto type = read_word(value) & 0xffffffff;
    if (type != 7 && type != 8) return {};
    unsigned __int128 u;
    std::memcpy(&u, reinterpret_cast<void*>(value + 16), sizeof(u));
    if (type == 8) {
        if (u == 0) return std::string("0");
        std::string text;
        do { text.push_back('0' + u % 10); u /= 10; } while (u);
        std::reverse(text.begin(), text.end());
        return text;
    }
    __int128 s;
    std::memcpy(&s, &u, sizeof(s));
    return integer_text(s);
}
}

extern "C" {
uint64_t lymar_aot_alloc(uint64_t size);
uint64_t lymar_aot_box_float(double number);
uint64_t lymar_aot_box_i64(int64_t v);
uint64_t lymar_aot_tag_int(int64_t v);
int64_t lymar_aot_untag_int(uint64_t word);
uint64_t lymar_aot_tag_bool(uint64_t val);
uint64_t lymar_aot_untag_bool(uint64_t word);
uint64_t lymar_aot_tag_pointer(uint64_t ptr);
uint64_t lymar_aot_untag_ptr(uint64_t word);
uint64_t lymar_aot_untag_at(uint64_t word);
void lymar_aot_edge(uint64_t address, uint64_t child);
double lymar_aot_to_float(uint64_t value);

// Frame operations require a live, correctly shaped receiver before addressing
// its fields. This is backend-private layout validation, not frontend inference.
uint64_t lymar_aot_frame_field_address(uint64_t pointer, uint64_t index) {
    if (pointer <= 4096) return 0;
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    auto frame = h.allocations.find(pointer);
    bool in_alloc = (frame != h.allocations.end());
    size_t alloc_sz = in_alloc ? frame->second.size : 0;
    uint64_t w0 = read_word(pointer);
    auto nm_ptr = (w0 == 15) ? read_word(pointer, 8) : 0;
    std::string nm = (nm_ptr > 4096 && (read_word(nm_ptr) & 0xffffffff) == 11) ? std::string((const char*)(nm_ptr + 24), read_word(nm_ptr, 8)) : "<none>";
    if (!in_alloc || alloc_sz < 40 || (w0 & 0xffffffff) != 15) {
        if ((w0 & 0xffffffff) == 15) {
            h.allocations[pointer] = Allocation{40, h.active, {}};
            h.regions.at(h.active).members.insert(pointer);
        } else {
            char msg[256];
            snprintf(msg, sizeof(msg), "Invalid or expired frame receiver (frame=%s in_alloc=%d sz=%llu w0=%llx)", nm.c_str(), in_alloc, (unsigned long long)alloc_sz, (unsigned long long)w0);
            throw std::runtime_error(msg);
        }
    }
    auto count = read_word(pointer, 24);
    if (index >= count) throw std::runtime_error("Invalid frame field index");
    auto fields = read_word(pointer, 16);
    auto array = h.allocations.find(fields);
    if (array == h.allocations.end()) {
        size_t fbytes = (count > 0 ? count : 2) * sizeof(Word);
        h.allocations[fields] = Allocation{fbytes, h.active, {}};
        h.regions.at(h.active).members.insert(fields);
    }
    return fields + index * sizeof(Word);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_frame_get_field(uint64_t pointer, uint64_t index) {
    if (pointer <= 4096) return 2; // VAL_NIL
    auto addr = lymar_aot_frame_field_address(pointer, index);
    if (!addr) return 2;
    // Slot holds a tagged LmValue; builder-side untag_word decodes it and
    // erased consumers read the self-describing word directly.
    return *reinterpret_cast<const Word*>(addr);
}
void lymar_aot_frame_set_field(uint64_t pointer, uint64_t index, uint64_t value) {
    if (pointer <= 4096) return;
    auto addr = lymar_aot_frame_field_address(pointer, index);
    if (!addr) return;
    *reinterpret_cast<Word*>(addr) = value;
    lymar_aot_edge(addr, value);
}
uint64_t lymar_aot_frame_matches(uint64_t pointer, uint64_t expected, uint64_t length) {
    if (pointer <= 4096) return 0;
    try {
        RuntimeGuard guard;
        if ((read_word(pointer) & 0xffffffff) != 15) return 0;

        auto name = read_word(pointer, 8);
        if (name <= 4096 || (read_word(name) & 0xffffffff) != 11) return 0;
        if (!expected || expected <= 4096) return 0;

        size_t n_len = read_word(name, 8);
        std::string n_str((const char*)(name + 24), n_len);
        std::string e_str((const char*)(expected + 24), length);

        if (n_str == e_str) return 1;
        if (n_str.size() > e_str.size() && n_str.ends_with("." + e_str)) return 1;
        if (e_str.size() > n_str.size() && e_str.ends_with("." + n_str)) return 1;
        return 0;
    } catch (...) {
        return 0;
    }
}
// Indirect-call dispatch compares a runtime function-name receiver (a heap
// Lymar string) against a compile-time candidate-name blob that
// get_or_create_global_str emits into .data. lymar_aot_value_equal cannot see
// the .data operand because its object classifier requires a heap allocation,
// so it silently rejected every candidate and every indirect call through an
// fn-typed value returned nil. Both sides share the LmStringHeader layout
// (type_id@0, len@8, data@24), so compare by shape and bytes without demanding
// the candidate global be heap-tracked.
uint64_t lymar_aot_string_name_eq(uint64_t string_ptr, uint64_t name_global, uint64_t length) {
    try {
    RuntimeGuard runtime_guard;

    if (string_ptr <= 4096) return 0;
    if ((read_word(string_ptr) & 0xffffffff) != 11) return 0;   // receiver must be a string
    if (read_word(string_ptr, 8) != length) return 0;           // byte length must match the candidate
    return std::memcmp(reinterpret_cast<const void*>(string_ptr + 24),
                       reinterpret_cast<const void*>(name_global + 24), length) == 0 ? 1 : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_atomic_load(uint64_t pointer, uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    // Return the tagged slot word; the consumer's untag_word decodes it.
    return LM::Memory::atomic_field_load(reinterpret_cast<Word*>(address));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_atomic_store(uint64_t pointer, uint64_t index, uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    // Publish ownership before publishing the field value. The slot
    // receives the tagged LmValue word so readers see a self-describing value.
    std::lock_guard lock(LM::Memory::atomic_field_mutex(reinterpret_cast<void*>(address)));
    lymar_aot_edge(address, value);
    std::atomic_ref<Word>(*reinterpret_cast<Word*>(address)).store(value, std::memory_order_seq_cst);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_atomic_update(uint64_t pointer, uint64_t index, uint64_t value, uint64_t subtract) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    LM::Memory::atomic_field_update(reinterpret_cast<Word*>(address), [&](Word old) {
        // Both operands are tagged LmValue words; results are re-tagged below.
        auto is_float_box = [](Word word) {
            return is_heap_word(word) && (read_word(word) & 0xffffffff) == 9;
        };
        auto left = integer_number(old), right = integer_number(value);
        Word result = VAL_NIL;
        if (left && right) {
            __int128 number;
            if (LM::Memory::add_integer(*left, *right, number, subtract != 0)) {
                if (number >= MIN_SMI && number <= MAX_SMI)
                    result = (static_cast<Word>(number) << 3) | TAG_INT;
                else {
                    result = lymar_aot_alloc(32); *reinterpret_cast<Word*>(result) = 7;
                    std::memcpy(reinterpret_cast<void*>(result + 16), &number, sizeof(number));
                }
            }
        } else if ((left || is_float_box(old)) && (right || is_float_box(value))) {
            auto a = lymar_aot_to_float(old), b = lymar_aot_to_float(value);
            result = lymar_aot_box_float(subtract ? a - b : a + b);
        } else if (!subtract && is_heap_word(old) && is_heap_word(value) &&
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
        lymar_aot_edge(address, result);
        return result;
    });

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_builtin_arity_error() {
    try {
    RuntimeGuard runtime_guard;
 throw std::runtime_error("Builtin argument count mismatch");
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_ref_create(uint64_t pointer, uint64_t writable) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    if ((pointer == 0 || pointer == VAL_NIL) && (writable & LM::Memory::ReferenceNullable)) return 0;
    if (!h.allocations.count(pointer)) throw std::runtime_error("AOT borrow of unowned object");
    h.lifetimes.adopt(pointer);
    auto token = h.lifetimes.borrow(pointer, (writable & LM::Memory::ReferenceWritable) != 0, h.active);
    shared_heap().reference_owners[token] = {std::this_thread::get_id(),h.active};
    return token;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_nil(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    // Managed words are tagged LmValues: VAL_NIL (and the 0 sentinel produced
    // by failed slot lookups) are the only nil representations.
    return value == VAL_NIL || value == 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_object(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    return is_heap_word(value) ? 1 : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Ok/err union boxes are raw 24-byte allocations tagged with a magic word so
// Unwrap/IsError can distinguish them from the raw scalars and frames that
// optional (T?) and plain unions also carry. Layout: [magic][is_error][payload].
constexpr Word union_box_magic = 0x4C594D41524F4B21ULL; // "LYMAROK!"

static bool is_union_box(Word value) {
    if (!is_heap_word(value)) return false;
    auto found = heap().containing(value);
    if (found == heap().allocations.end() || found->first != value || found->second.size < 24) return false;
    return read_word(value) == union_box_magic;
}
uint64_t lymar_aot_union_is_error(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    return is_union_box(value) && read_word(value, 8) != 0 ? 1 : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_union_unwrap(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    if (is_union_box(value)) return read_word(value, 16);
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return value;
    }
}
uint64_t lymar_aot_string_receiver(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    return is_heap_word(value) && (read_word(value) & 0xffffffff) == 11 ? value : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_callable_receiver(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    if (!is_heap_word(value)) return 0;
    auto type = read_word(value) & 0xffffffff;
    if (type == 11) return value; // canonical function-name string
    auto& h = heap();
    auto tuple = h.allocations.find(value);
    if (type != 3 || tuple == h.allocations.end() || tuple->second.size < 32 || !read_word(value,16)) return 0;
    auto elements = read_word(value,8);
    auto array = h.allocations.find(elements);
    if (array == h.allocations.end() || array->second.size < 8) return 0;
    auto name = read_word(elements);
    if (!is_heap_word(name) || (read_word(name) & 0xffffffff) != 11) return 0;
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_string_index(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    if ((value & TAG_MASK) == TAG_INT) return static_cast<uint64_t>(static_cast<int64_t>(value) >> 3);
    if (value == VAL_FALSE || value == VAL_NIL || value == 0) return 0;
    if (value == VAL_TRUE) return 1;
    if (!is_heap_word(value)) return 0;
    auto type = read_word(value) & 0xffffffff;
    if (type >= 5 && type <= 8) return read_word(value + 8);
    if (type == 9) {
        double number;
        std::memcpy(&number, reinterpret_cast<void*>(value + 8), sizeof(number));
        return static_cast<uint64_t>(LM::Memory::truncate_i64(number));
    }
    return 0; // as_i64 does not parse strings or convert booleans.

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_print_object(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    return is_heap_word(value) && (read_word(value) & 0xffffffff) != 9 ? 1 : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
double lymar_aot_to_float(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    Word tag = word_tag(value);
    if (tag == TAG_IMMEDIATE) return value == VAL_TRUE ? 1.0 : 0.0;
    if (tag == TAG_INT) return static_cast<double>(static_cast<int64_t>(value) >> 3);
    if (tag != TAG_PTR || value <= 4096) return static_cast<double>(static_cast<int64_t>(value));
    auto found = heap().allocations.find(value);
    if (found != heap().allocations.end() && !found->second.raw_memory && !found->second.dictionary && found->second.size >= 16) {
        if ((read_word(value) & 0xffffffff) == 9) {
            double number;
            std::memcpy(&number, reinterpret_cast<void*>(value + 8), sizeof(number));
            return number;
        }
        if (auto* text = string_data(value)) { try { return std::stod(text); } catch (...) {} }
    }
    if (auto integer = integer_number(value)) return static_cast<double>(*integer);
    return static_cast<double>(static_cast<int64_t>(value));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0.0;
    }
}
uint64_t lymar_aot_to_integer(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    Word tag = word_tag(value);
    if (tag == TAG_INT) return static_cast<uint64_t>(static_cast<int64_t>(value) >> 3);
    if (value == VAL_FALSE || value == VAL_NIL || value == 0) return 0;
    if (value == VAL_TRUE) return 1;
    if (tag == TAG_IMMEDIATE) return 0;
    if (tag != TAG_PTR || value <= 4096) return value;
    if (auto integer = integer_number(value)) return static_cast<Word>(*integer);
    auto found = heap().allocations.find(value);
    if (found != heap().allocations.end() && !found->second.raw_memory) {
        if (auto* text = string_data(value)) {
            try { return static_cast<uint64_t>(std::stoll(text)); }
            catch (...) { return static_cast<unsigned char>(text[0]); }
        }
        if (found->second.size >= 16 && (read_word(value) & 0xffffffff) == 9) {
            return static_cast<uint64_t>(LM::Memory::truncate_i64(lymar_aot_to_float(value)));
        }
        if (found->second.size >= 16 && (read_word(value) & 0xffffffff) == 5) {
            return read_word(value, 8);
        }
    }
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_float_to_integer(double number) {
    try {
    RuntimeGuard runtime_guard;

    return static_cast<uint64_t>(LM::Memory::truncate_i64(number));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_to_boolean(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    if (value == VAL_FALSE || value == VAL_NIL || value == 0) return 0;
    if (value == VAL_TRUE) return 1;
    if ((value & TAG_MASK) == TAG_INT) return (static_cast<int64_t>(value) >> 3) != 0;
    if ((value & TAG_MASK) == TAG_IMMEDIATE) return value != VAL_FALSE && value != VAL_NIL && value != 0;
    if (value <= 4096) return value != 0;
    if (!is_heap_word(value)) return value != 0;
    if ((read_word(value) & 0xffffffff) == 9) return lymar_aot_to_float(value) != 0.0;
    return 1;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
int64_t lymar_aot_numeric_compare(uint64_t left, uint64_t right) {
    RuntimeGuard guard;
    auto classify = [&](Word value) -> Word {
        if (!is_heap_word(value)) return 0;
        auto found = heap().containing(value);
        if (found == heap().allocations.end())
            throw std::runtime_error("Invalid or expired comparison operand");
        if (found->first != value || found->second.raw_memory || found->second.dictionary) return 0;
        if (found->second.size < 8) throw std::runtime_error("Invalid comparison allocation");
        auto type = read_word(value) & 0xffffffff;
        if (type >= 5 && type <= 9 && found->second.size < (type == 7 || type == 8 ? 32 : 16))
            throw std::runtime_error("Invalid numeric allocation");
        return type;
    };
    auto ltype = classify(left), rtype = classify(right);
    // Numeric operands: SMI/immediate-decoded integers and heap number boxes.
    bool lnumeric = integer_number(left).has_value() || (ltype >= 5 && ltype <= 9);
    bool rnumeric = integer_number(right).has_value() || (rtype >= 5 && rtype <= 9);
    if (lnumeric && rnumeric) {
        if (ltype == 9 || rtype == 9) {
            auto a = lymar_aot_to_float(left), b = lymar_aot_to_float(right);
            return a < b ? -1 : a > b ? 1 : 0;
        }
        auto a = *integer_number(left), b = *integer_number(right);
        return a < b ? -1 : a > b ? 1 : 0;
    }
    // Lexicographic string ordering (type-id 11): length at +8, bytes at +24.
    // Mirrors numeric_compare in the VM so relational operators on str are
    // equivalent across the VM, native, AOT and Fyra backends.
    if (ltype == 11 && rtype == 11) {
        auto la = read_word(left, 8), lb = read_word(right, 8);
        auto n = la < lb ? la : lb;
        int c = n ? std::memcmp(reinterpret_cast<void*>(left + 24),
                                reinterpret_cast<void*>(right + 24), n) : 0;
        if (c < 0) return -1;
        if (c > 0) return 1;
        if (la < lb) return -1;
        if (la > lb) return 1;
        return 0;
    }
    // Tagged words already carry the VM ordering encoding: SMI (v<<3)|1,
    // immediates 2/10/18, heap pointers by address.
    return left < right ? -1 : left > right ? 1 : 0;
}
static uint64_t format_argument(uint64_t value, bool printable);
void lymar_aot_dbg_lidx(uint64_t list_val, uint64_t idx_val) {
    uint64_t lp = list_val & ~7ULL;
    uint64_t hdr = 0, size = 0, data = 0;
    bool tracked = false;
    try {
        RuntimeGuard g;
        auto f = heap().allocations.find(lp);
        if (f != heap().allocations.end() && f->second.size >= 32) {
            tracked = true;
            auto* w = reinterpret_cast<uint64_t*>(lp);
            hdr = w[0]; size = w[2]; data = w[1];
        }
    } catch (...) {}
    std::fprintf(stderr, "[lidx] list=%llx idx=%lld tracked=%d hdr=%llx size=%lld data=%llx\n",
        (unsigned long long)list_val, (long long)idx_val, (int)tracked,
        (unsigned long long)hdr, (long long)size, (unsigned long long)data);
    std::fflush(stderr);
}
void lymar_aot_print_integer(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    // Raw scalar-domain printer: callers only route unboxed i64 words here.
    // Tagged LmValue words go through lymar_aot_print_value instead.
    char text[64];
    const auto length = std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value));
    lymar_stdout_write(text, static_cast<size_t>(length));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_print_float(double value) {
    try {
    RuntimeGuard runtime_guard;

    char text[64];
    const auto length = std::snprintf(text, sizeof(text), "%.6g", value);
    lymar_stdout_write(text, static_cast<size_t>(length));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_value_equal(uint64_t left, uint64_t right) {
    try {
    RuntimeGuard runtime_guard;

    // Both operands are tagged LmValue words; nil-ness is word identity.
    const bool left_nil = left == VAL_NIL || left == 0;
    const bool right_nil = right == VAL_NIL || right == 0;
    if (left_nil || right_nil) return left_nil && right_nil;
    auto is_bool_word = [](uint64_t v) {
        return v == VAL_TRUE || v == VAL_FALSE ||
               ((v & TAG_MASK) == TAG_IMMEDIATE && v != VAL_NIL) ||
               (v <= 1 && (v & TAG_MASK) != TAG_PTR);
    };
    if (left == VAL_TRUE || left == VAL_FALSE || right == VAL_TRUE || right == VAL_FALSE) {
        auto to_b = [](uint64_t v) -> int {
            if (v == VAL_TRUE || v == 1 || v == VAL_TRUE) return 1;
            if (v == VAL_FALSE || v == 0) return 0;
            if ((v & TAG_MASK) == TAG_IMMEDIATE) return v == VAL_TRUE ? 1 : 0;
            if ((v & TAG_MASK) == TAG_INT) return (static_cast<int64_t>(v) >> 3) != 0;
            return v != 0 ? 1 : 0;
        };
        if (is_bool_word(left) && is_bool_word(right)) return to_b(left) == to_b(right);
        return left == right;
    }
    if (left == right) return 1;
    auto get_object_type = [&](Word value) -> Word {
        if (!is_heap_word(value)) return UINT64_MAX;
        auto found = heap().allocations.find(value);
        if (found == heap().allocations.end() || found->second.raw_memory || found->second.size < 8) return UINT64_MAX;
        return read_word(value) & 0xffffffff;
    };
    const Word left_type = get_object_type(left);
    const Word right_type = get_object_type(right);
    if (auto left_integer = integer_number(left))
        if (auto right_integer = integer_number(right)) return *left_integer == *right_integer;
    if ((integer_number(left) || left_type == 9) && (integer_number(right) || right_type == 9))
        return left_type == 9 || right_type == 9
            ? lymar_aot_to_float(left) == lymar_aot_to_float(right) : left == right;
    if (left_type == 11 && right_type == 11) {
        auto size = read_word(left, 8);
        return size == read_word(right, 8) && std::memcmp(reinterpret_cast<void*>(left + 24), reinterpret_cast<void*>(right + 24), size) == 0;
    }
    // Char-vs-string: a SMI operand compares against a one-character string.
    if ((left & TAG_MASK) == TAG_INT && right_type == 11)
        return read_word(right, 8) == 1 && static_cast<uint8_t>(static_cast<int64_t>(left) >> 3) == *reinterpret_cast<uint8_t*>(right + 24);
    if ((right & TAG_MASK) == TAG_INT && left_type == 11)
        return read_word(left, 8) == 1 && static_cast<uint8_t>(static_cast<int64_t>(right) >> 3) == *reinterpret_cast<uint8_t*>(left + 24);
    // Preserve the existing native enum representation and payload equality.
    if (left_type == 0x454e554d && right_type == 0x454e554d)
        return read_word(left, 8) == read_word(right, 8) && read_word(left, 16) == read_word(right, 16);
    return 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_create_checked(uint64_t pointer, uint64_t mode) {
    try {
    RuntimeGuard runtime_guard;

    if (!is_heap_word(pointer)) throw std::runtime_error("Borrow requires a managed object");
    return lymar_aot_ref_create(pointer, mode);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_resolve(uint64_t token, uint64_t writable) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    if (!token && (writable & LM::Memory::ReferenceNullable)) return 2;
    if ((writable & LM::Memory::ReferenceWritable) && h.worker && shared_heap().reference_owners.at(token).thread != std::this_thread::get_id())
        throw std::runtime_error("Worker cannot write through a captured reference");
    return h.lifetimes.resolve(token, (writable & LM::Memory::ReferenceWritable) != 0);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_move(uint64_t token, uint64_t lexical, uint64_t caller) {
    try {
    RuntimeGuard runtime_guard;

    if (lexical & ~LM::Memory::ReferenceMoveMask) throw std::runtime_error("Invalid AOT reference move mode");
    auto& h = heap();
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
    auto owner = shared_heap().reference_owners.at(token).thread;
    auto moved = h.lifetimes.move_reference(token, target);
    shared_heap().reference_owners.erase(token);
    shared_heap().reference_owners[moved] = {owner,target};
    return moved;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_ref_release_nullable(uint64_t token) {
    try {
    RuntimeGuard runtime_guard;

    if (token) lymar_aot_ref_release(token);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}

uint64_t lymar_aot_call_enter() {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    h.invocations.push_back({h.active, {}});
    return h.active;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_call_leave() {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT invocation stack underflow");
    h.invocations.pop_back();

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_param_push(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT Param outside invocation");

    h.invocations.back().staged_params.push_back(value);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_param_pop(uint64_t fallback) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT ConstructError outside invocation");
    auto& params = h.invocations.back().staged_params;
    if (params.empty()) return fallback;
    auto value = params.back();
    params.pop_back();
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_region_current() {
    try {
    RuntimeGuard runtime_guard;
 return heap().active;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_region_move(uint64_t value, uint64_t lexical, uint64_t caller) {
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
    if (is_heap_word(value)) h.promote(value, target);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        Word alloc_size = std::max(size, Word(1));
        h.allocations.emplace(pointer, Allocation{static_cast<size_t>(alloc_size), h.active, {}});
        Word start_page = pointer >> 12;
        Word end_page = (pointer + alloc_size - 1) >> 12;
        for (Word page = start_page; page <= end_page; ++page) {
            h.page_map[page].push_back(pointer);
        }
        h.regions.at(h.active).members.insert(pointer);
    } catch (...) {
        h.allocations.erase(pointer);
        h.allocator.deallocate(reinterpret_cast<void*>(pointer));
        throw;
    }
    return pointer;

    } catch (const std::exception& failure) {
        std::fprintf(stderr, "[lymar_aot_alloc FAILED]: size=%llu active=%llu error=%s\n",
            (unsigned long long)size, (unsigned long long)heap().active, failure.what());
        std::fflush(stderr);
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_box_i64(int64_t v) {
    try {
        RuntimeGuard runtime_guard;
        auto pointer = lymar_aot_alloc(32);
        Word* words = reinterpret_cast<Word*>(pointer);
        words[0] = 5; // TYPE_I64
        words[1] = static_cast<Word>(v);
        words[2] = 0;
        words[3] = static_cast<Word>(v);
        return pointer;
    } catch (...) {
        return 0;
    }
}
uint64_t lymar_aot_tag_int(int64_t v) {
    if (v >= MIN_SMI && v <= MAX_SMI) {
        return (static_cast<uint64_t>(v) << 3) | TAG_INT;
    }
    return lymar_aot_box_i64(v);
}
int64_t lymar_aot_untag_int(uint64_t word) {
    if (word == VAL_NIL) return VAL_NIL;
    if ((word & TAG_MASK) == TAG_INT) {
        return static_cast<int64_t>(word) >> 3;
    }
    if ((word & TAG_MASK) == TAG_PTR && word > 4096) {
        try {
            RuntimeGuard runtime_guard;
            auto found = heap().allocations.find(word);
            if (found != heap().allocations.end() && !found->second.raw_memory && found->second.size >= 16) {
                uint64_t type = *reinterpret_cast<const Word*>(word) & 0xffffffff;
                if (type == 5 || type == 6 || type == 13) {
                    return static_cast<int64_t>(*reinterpret_cast<const Word*>(word + 8));
                }
            }
        } catch (...) {}
    }
    return static_cast<int64_t>(word);
}
uint64_t lymar_aot_tag_bool(uint64_t val) {
    return (val == 1 || val == VAL_TRUE) ? VAL_TRUE : VAL_FALSE;
}
uint64_t lymar_aot_untag_bool(uint64_t word) {
    if (word == VAL_TRUE) return 1;
    if (word == VAL_FALSE) return 0;
    if ((word & TAG_MASK) == TAG_IMMEDIATE) {
        return (word >> 3) ? 1 : 0;
    }
    return word ? 1 : 0;
}
uint64_t lymar_aot_tag_pointer(uint64_t ptr) {
    if (!ptr) return 0;
    if (ptr == VAL_NIL) return VAL_NIL;
    try {
        RuntimeGuard runtime_guard;
        if ((ptr & TAG_MASK) == 0 && ptr > 4096) {
            auto& h = heap();
            if (h.allocations.find(ptr) != h.allocations.end()) {
                return ptr; // Safe Lymar heap pointer
            }
        }
        // Foreign or unaligned pointer: wrap in TYPE_FOREIGN_PTR (13)
        if (std::getenv("LYMAR_TRACE_TAGPTR")) std::fprintf(stderr, "[tagptr-wrap] ptr=%llx\n", (unsigned long long)ptr);
        auto box = lymar_aot_alloc(32);
        Word* words = reinterpret_cast<Word*>(box);
        words[0] = 13;
        words[1] = ptr;
        words[2] = 0;
        words[3] = ptr;
        heap().promote(box, 0); // Pin wrapper in permanent region
        return box;
    } catch (...) {
        return ptr;
    }
}
uint64_t lymar_aot_untag_ptr(uint64_t word) {
    if (!word) return 0;
    if (word == VAL_NIL) return 0;
    if ((word & TAG_MASK) == TAG_PTR && word > 4096) {
        try {
            RuntimeGuard runtime_guard;
            auto found = heap().allocations.find(word);
            if (found != heap().allocations.end() && !found->second.raw_memory && found->second.size >= 16) {
                uint64_t type = *reinterpret_cast<const Word*>(word) & 0xffffffff;
                if (type == 13) {
                    return *reinterpret_cast<const Word*>(word + 8);
                }
            }
        } catch (...) {}
        return word;
    }
    return word & ~TAG_MASK;
}
uint64_t lymar_aot_scalar_to_string(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    if (is_heap_word(value) && (read_word(value) & 0xffffffff) == 11)
        return value;
    std::string wide_text;
    char text[64];
    const char* output = text;
    size_t length;
    if (value == VAL_NIL || value == 0) { output = "nil"; length = 3; }
    else if (value == VAL_TRUE) { output = "true"; length = 4; }
    else if (value == VAL_FALSE) { output = "false"; length = 5; }
    else if (is_heap_word(value) && (read_word(value) & 0xffffffff) == 9)
        length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", lymar_aot_to_float(value)));
    else if (auto wide = wide_box_text(value)) { wide_text = *wide; output = wide_text.c_str(); length = wide_text.size(); }
    else if (auto integer = integer_number(value)) { wide_text = integer_text(*integer); output = wide_text.c_str(); length = wide_text.size(); }
    else if ((value & TAG_MASK) == TAG_INT) { wide_text = integer_text(static_cast<int64_t>(value) >> 3); output = wide_text.c_str(); length = wide_text.size(); }
    else length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value)));
    auto pointer = lymar_aot_alloc(24 + length + 1);
    Word header[] = {11, length, length};
    std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 24), output, length);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Statically-known booleans cannot ride the dynamic kind sidecar (integer
// slots record kind 0), so `bool as str` needs a dedicated entry point.
uint64_t lymar_aot_bool_to_string(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    // Tagged bool words are VAL_TRUE(18)/VAL_FALSE(10) — both nonzero, so a
    // raw `value ?` test prints "true" for false. Decode via to_boolean.
    const bool truth = lymar_aot_to_boolean(value) != 0;
    const char* output = truth ? "true" : "false";
    size_t length = truth ? 4 : 5;
    auto pointer = lymar_aot_alloc(24 + length + 1);
    Word header[] = {11, length, length};
    std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 24), output, length);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Erased scalar arguments must become strings before the generated formatter
// inspects object layouts. A float box is not a list, and a Boolean is not an
// integer. Compound objects retain their existing formatting path. Every word
// is a self-describing LmValue: `word & 7` selects the decode.
static uint64_t format_argument(uint64_t value, bool printable) {
    try {
        RuntimeGuard guard;
        auto& h = heap();
        std::unordered_set<Word> visiting;
        auto require = [&](Word pointer, Word bytes) {
            auto allocation = h.allocations.find(pointer);
            if (allocation == h.allocations.end() || bytes > allocation->second.size)
                throw std::runtime_error("Invalid or expired formatting receiver");
        };
        std::function<std::string(Word)> format = [&](Word word) -> std::string {
            if (word == VAL_FALSE) return "false";
            if (word == VAL_TRUE) return "true";
            if (word == VAL_NIL || word == 0) return "nil";
            if ((word & TAG_MASK) == TAG_INT) return integer_text(static_cast<int64_t>(word) >> 3);
            if ((word & TAG_MASK) == TAG_IMMEDIATE) return integer_text(static_cast<int64_t>(word));
            if (word <= 4096) return integer_text(static_cast<int64_t>(word));
            auto alloc_it = h.allocations.find(word);
            if (alloc_it == h.allocations.end()) {
                // Foreign/untracked pointer word: render the address.
                return integer_text(static_cast<int64_t>(word));
            }
            require(word, 8);
            auto& allocation = alloc_it->second;
            // ffi.alloc/raw buffers are address scalars (pubptr = int), not
            // formattable objects — render the address like the VM does.
            if (allocation.raw_memory) return integer_text(static_cast<int64_t>(word));
            auto type = read_word(word) & 0xffffffff;
            if (!allocation.dictionary && type == 11) {
                require(word, 24);
                auto length = read_word(word, 8);
                if (length > allocation.size - 24) throw std::runtime_error("Invalid string length");
                return std::string(reinterpret_cast<const char*>(word + 24), length);
            }
            if (!allocation.dictionary && type >= 5 && type <= 8) {
                require(word, type <= 6 ? 16 : 32);
                if (auto wide = wide_box_text(word)) return *wide;
                return integer_text(*integer_number(word));
            }
            if (!allocation.dictionary && type == 13) {
                require(word, 16);
                return integer_text(static_cast<int64_t>(read_word(word, 8)));
            }
            if (!allocation.dictionary && type == 9) {
                require(word, 16);
                char buffer[64];
                std::snprintf(buffer, sizeof(buffer), "%.6g", lymar_aot_to_float(word));
                return buffer;
            }
            if (!allocation.dictionary && read_word(word) == union_box_magic) {
                require(word, 32);
                auto flag = read_word(word, 8);
                auto payload = read_word(word, 16);
                auto inner = format(payload);
                return flag ? "err(" + inner + ")" : "ok(" + inner + ")";
            }
            if (!visiting.insert(word).second) throw std::runtime_error("Cyclic value formatting");
            struct Visit { std::unordered_set<Word>& set; Word word; ~Visit() { set.erase(word); } } visit{visiting, word};
            require(word, 32);
            if (!allocation.dictionary && type == 0x454e554d) {
                auto name = format(read_word(word, 24));
                auto payload = read_word(word, 16);
                if (lymar_aot_is_nil(payload)) return name;
                return name + "(" + format(payload) + ")";
            }
            auto nested = [&](Word child) {
                auto rendered = format(child);
                auto found = h.allocations.find(child);
                if (printable && is_heap_word(child) && found != h.allocations.end() &&
                    !found->second.raw_memory && !found->second.dictionary &&
                    found->second.size >= 24 && (read_word(child) & 0xffffffff) == 11)
                    return std::string("\"") + rendered + "\"";
                return rendered;
            };
            Word elements, count;
            uint64_t element_kind = 0;
            std::string text;
            if (allocation.dictionary) {
                count = read_word(word); auto capacity = read_word(word, 8);
                elements = read_word(word, 16); auto values = read_word(word, 24);
                if (count > capacity || capacity > UINT64_MAX / sizeof(Word)) throw std::runtime_error("Invalid dictionary length");
                require(elements, capacity * sizeof(Word)); require(values, capacity * sizeof(Word));
                std::vector<std::pair<std::string, std::string>> entries;
                for (Word index = 0; index < count; ++index) {
                    auto key = elements + index * sizeof(Word), value = values + index * sizeof(Word);
                    entries.emplace_back(nested(read_word(key)), nested(read_word(value)));
                }
                if (printable) std::sort(entries.begin(), entries.end());
                text = "{";
                for (size_t index = 0; index < entries.size(); ++index) {
                    if (index) text += ", ";
                    text += entries[index].first + ": " + entries[index].second;
                }
                return text + "}";
            }
            if (type == 1 || type == 3) {
                elements = read_word(word, 8); count = read_word(word, 16);
                text = type == 1 ? "[" : "(";
                if (type == 1) element_kind = read_word(word) >> 32;
            } else if (type == 15) {
                require(word, 40); elements = read_word(word, 16); count = read_word(word, 24);
                text = format(read_word(word, 8)) + "{";
            } else throw std::runtime_error("Unsupported object formatting kind");
            if (count > UINT64_MAX / sizeof(Word)) throw std::runtime_error("Invalid aggregate length");
            require(elements, count * sizeof(Word));
            for (Word index = 0; index < count; ++index) {
                if (index) text += ", ";
                auto address = elements + index * sizeof(Word);
                auto element = read_word(address);
                if (element_kind == 1) {
                    text += integer_text(static_cast<int64_t>(element));
                } else if (element_kind == 2) {
                    text += element ? "true" : "false";
                } else {
                    text += nested(element);
                }
            }
            return text + (type == 1 ? "]" : type == 3 ? ")" : "}");
        };
        auto text = format(value);
        auto pointer = lymar_aot_alloc(24 + text.size() + 1);
        Word header[] = {11, text.size(), text.size()};
        std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
        std::memcpy(reinterpret_cast<void*>(pointer + 24), text.c_str(), text.size() + 1);
        return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_format_argument(uint64_t value) {
    return format_argument(value, false);
}
uint64_t lymar_aot_mark_dictionary(uint64_t pointer) {
    RuntimeGuard guard;
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || found->second.size != 32)
        throw std::runtime_error("Invalid dictionary allocation");
    found->second.dictionary = true;
    return pointer;
}
void lymar_aot_print_value(uint64_t value) {
    RuntimeGuard guard;
    auto string = format_argument(value, true);
    if (!string) return;
    lymar_stdout_write(reinterpret_cast<const void*>(string + 24), read_word(string, 8));
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_float_bits_to_string(uint64_t bits) {
    double number;
    std::memcpy(&number, &bits, sizeof(number));
    return lymar_aot_float_to_string(number);
}
uint64_t lymar_aot_length(uint64_t pointer_raw) {
    // Standalone-AOT machine code carries no C++ unwind metadata, so a throw
    // here would crash the process before any catch could run. Report failures
    // directly: workers record worker_error for the scheduler; the main thread
    // prints the VM-style error and exits nonzero (lymar_aot_assert pattern).
    auto fail=[&](const char* message)->uint64_t {
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", message);
        if (!heap().worker) {
            std::string text=std::string("Error: ")+message+"\n";
            lymar_stdout_write(text.data(),text.size());
            std::exit(1);
        }
        return 0;
    };
    try {
    RuntimeGuard guard;
    if(lymar_aot_is_nil(pointer_raw) || pointer_raw <= 4096 || (pointer_raw & TAG_MASK) != TAG_PTR) return 0;
    uint64_t pointer = pointer_raw;
    auto found=heap().allocations.find(pointer);
    if(found==heap().allocations.end() || found->second.raw_memory || found->second.size<8) {
        if (pointer > 4096) {
            auto type = read_word(pointer) & 0xffffffff;
            if (type == 11) return read_word(pointer, 8);
            if (type == 1) return read_word(pointer, 16);
        }
        return fail("Invalid or expired length receiver");
    }
    auto& record=found->second;
    if(record.dictionary) {
        if(record.size<32) return fail("Invalid dictionary header");
        auto count=read_word(pointer),capacity=read_word(pointer,8);
        for(Word offset:{Word(16),Word(24)}) {
            auto data=heap().allocations.find(read_word(pointer,offset));
            if(count>capacity || data==heap().allocations.end() || capacity>data->second.size/8)
                return fail("Invalid dictionary storage");
        }
        return count;
    }
    auto type=read_word(pointer)&0xffffffff;
    if(type==11) {
        if(!string_data(pointer)) return fail("Invalid string header");
        return read_word(pointer,8);
    }
    if(type==1) return lymar_aot_ffi_list_size(pointer);
    if(type==15) {
        if(record.size<40) return fail("Invalid frame header");
        auto* name=string_data(read_word(pointer,8));
        // Preserve the VM's existing frame-length interpretation.
        if(name && std::strcmp(name,"LinkedList")==0 && read_word(pointer,24)>2) {
            auto address=lymar_aot_frame_field_address(pointer,2);
            return lymar_aot_to_integer(read_word(address));
        }
        return 0;
    }
    char msg[512];
    uint64_t w0 = read_word(pointer);
    uint64_t w8 = read_word(pointer, 8);
    uint64_t w16 = read_word(pointer, 16);
    uint64_t w24 = read_word(pointer, 24);
    HMODULE hMod = GetModuleHandleA(NULL);
    void* retAddr = __builtin_return_address(0);
    uint64_t rva = (uint64_t)retAddr - (uint64_t)hMod;
    snprintf(msg, sizeof(msg), "len: unsupported object type (type=%llu ptr=%llx sz=%llu w0=%llx w8=%llx w16=%llx w24=%llx RVA=+0x%llx caller=%p)",
             (unsigned long long)type, (unsigned long long)pointer, (unsigned long long)record.size,
             (unsigned long long)w0, (unsigned long long)w8, (unsigned long long)w16, (unsigned long long)w24,
             (unsigned long long)rva, retAddr);
    return fail(msg);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        if (!heap().worker) {
            std::string message = std::string("Error: ") + failure.what() + "\n";
            lymar_stdout_write(message.data(), message.size());
            std::exit(1);
        }
        return 0;
    }
}
uint64_t lymar_aot_tuple_length(uint64_t pointer) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_is_object(pointer)) return 0;
        auto record = heap().allocations.find(pointer);
        // TupleLen is only emitted as a match-arm probe: non-tuple receivers
        // must yield 0 (arm fails) rather than throw and poison worker_error.
        if (record == heap().allocations.end() || record->second.size < 32)
            return 0;
        return !record->second.dictionary && (read_word(pointer) & 0xffffffff) == 3 ? read_word(pointer, 16) : 0;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Match-arm type guard: reports the structural kind of an erased word so
// list/tuple/dict patterns can fail cleanly instead of probing foreign layouts.
// Returns 1=list, 2=dict, 3=tuple, 0=anything else (scalars, strings, frames).
uint64_t lymar_aot_word_kind(uint64_t word) {
    try {
        RuntimeGuard guard;
        Word t = word & TAG_MASK;
        if (t == TAG_PTR && word > 4096 && heap().allocations.count(word)) return object_kind;
        if (t == TAG_INT) return object_kind;
        if (word == VAL_TRUE || word == VAL_FALSE) return boolean_kind;
        return 0;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_probe_kind(uint64_t value) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_is_object(value)) return 0;
        auto record = heap().allocations.find(value);
        if (record == heap().allocations.end() || record->second.size < 8) return 0;
        if (record->second.dictionary) return 2;
        Word tag = read_word(value) & 0xffffffff;
        if (tag == 1) return 1;
        if (tag == 3) return 3;
        return 0;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_string_hash(uint64_t value) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_string_receiver(value))
            throw std::runtime_error("_builtin_string_hash_bytes expects str");
        Word hash = 5381, length = read_word(value, 8);
        auto* bytes = reinterpret_cast<const unsigned char*>(value + 24);
        for (Word index = 0; index < length; ++index) hash = (hash * 33 + bytes[index]) % 2147483647;
        return hash;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_list_slice(uint64_t value, uint64_t start, uint64_t end) {
    try {
        RuntimeGuard guard;
        auto& h = heap();
        Word source = 0, count = 0;
        if (!lymar_aot_is_nil(value)) {
            auto record = h.allocations.find(value);
            if (!is_heap_word(value) || record == h.allocations.end() ||
                record->second.size < 32 || (read_word(value) & 0xffffffff) != 1)
                throw std::runtime_error("_builtin_list_slice expects list");
            source = read_word(value, 8); count = read_word(value, 16);
            auto data = h.allocations.find(source);
            if (data == h.allocations.end() || count > data->second.size / sizeof(Word))
                throw std::runtime_error("Invalid list elements allocation");
        }
        auto first = static_cast<int64_t>(lymar_aot_string_index(start));
        auto last = static_cast<int64_t>(lymar_aot_string_index(end));
        Word begin = std::min(count, static_cast<Word>(std::max<int64_t>(0, first)));
        Word limit = std::min(count, static_cast<Word>(std::max<int64_t>(0, last)));
        Word length = limit > begin ? limit - begin : 0;
        auto pointer = lymar_aot_alloc(32);
        auto elements = lymar_aot_alloc(std::max<Word>(1, length) * sizeof(Word));
        // Preserve the source header word so the element-storage kind (high
        // 32 bits: 0=tagged, 1=raw int, 2=raw bool) survives the slice.
        Word header_word = source ? read_word(value) : 1;
        uint64_t slice_kind = header_word >> 32;
        Word header[] = {header_word, elements, length, std::max<Word>(1, length)};
        std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
        lymar_aot_edge(pointer + 8, elements);
        for (Word index = 0; index < length; ++index) {
            auto address = source + (begin + index) * sizeof(Word);
            auto copied = read_word(address);
            std::memcpy(reinterpret_cast<void*>(elements + index * sizeof(Word)), &copied, sizeof(copied));
            // Only tagged-word (kind 0) elements can be object references;
            // raw int/bool elements are scalars and take no ownership edge.
            if (slice_kind == 0) lymar_aot_edge(elements + index * sizeof(Word), copied);
        }
        return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// String-slice/case/trim builtins. The IR-emitted versions (emit_*_ir in
// fyra_builtin_functions.cpp) rely on alloc-slot + loop shapes the Fyra
// backend miscompiles — substring returns "" and to_lower faults — so these
// names lower to runtime calls instead (see lower_runtime_builtin). Args
// arrive as erased words; string-ness is proven by the heap tag, not the
// lossy kind sidecar, and integer args accept boxed payloads.
static Word aot_str_arg_int(Word value) {
    if ((value & TAG_MASK) == TAG_PTR && value > 4096) {
        auto found = heap().allocations.find(value);
        if (found != heap().allocations.end() && (read_word(value) & 0xffffffff) == 5) {
            return read_word(value, 8);
        }
    }
    return value;
}
static Word aot_string_view(Word value, Word& length) {
    length = 0;
    if (value <= 4096) return 0;
    auto& h = heap();
    auto found = h.allocations.find(value);
    if (found != h.allocations.end()) {
        if (found->second.raw_memory || found->second.dictionary ||
            found->second.size < 25 || (read_word(value) & 0xffffffff) != 11) return 0;
        length = read_word(value, 8);
        if (length > found->second.size - 25) return 0;
        return value;
    }
    if ((read_word(value) & 0xffffffff) == 11) {
        length = read_word(value, 8);
        return value;
    }
    return 0;
}
static Word aot_string_make(const char* data, Word length) {
    auto pointer = lymar_aot_alloc(24 + length + 1);
    Word header[] = {11, length, length};
    std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
    if (length) std::memcpy(reinterpret_cast<void*>(pointer + 24), data, length);
    *reinterpret_cast<char*>(pointer + 24 + length) = 0;
    return pointer;
}
extern "C" uint64_t lymar_aot_substring(uint64_t value, uint64_t start, uint64_t end) {
    try {
    RuntimeGuard runtime_guard;
    Word length = 0;
    Word str = aot_string_view(value, length);
    if (!str) return aot_string_make("", 0);
    int64_t s = static_cast<int64_t>(aot_str_arg_int(start));
    int64_t e = static_cast<int64_t>(aot_str_arg_int(end));
    if (s < 0 || e > static_cast<int64_t>(length)) { if (e > static_cast<int64_t>(length)) e = static_cast<int64_t>(length); }
    if (s < 0 || s >= e) return aot_string_make("", 0);
    return aot_string_make(reinterpret_cast<const char*>(str + 24) + s, static_cast<Word>(e - s));
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
extern "C" uint64_t lymar_aot_string_case(uint64_t value, uint64_t upper) {
    try {
    RuntimeGuard runtime_guard;
    Word length = 0;
    Word str = aot_string_view(value, length);
    if (!str) return aot_string_make("", 0);
    auto pointer = lymar_aot_alloc(24 + length + 1);
    Word header[] = {11, length, length};
    std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
    const char* src = reinterpret_cast<const char*>(str + 24);
    char* dst = reinterpret_cast<char*>(pointer + 24);
    for (Word i = 0; i < length; ++i) {
        char c = src[i];
        if (upper) { if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A'); }
        else       { if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a'); }
        dst[i] = c;
    }
    dst[length] = 0;
    return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
extern "C" uint64_t lymar_aot_string_trim(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;
    Word length = 0;
    Word str = aot_string_view(value, length);
    if (!str) return aot_string_make("", 0);
    const char* data = reinterpret_cast<const char*>(str + 24);
    auto is_ws = [](char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'; };
    Word begin = 0, end = length;
    while (begin < end && is_ws(data[begin])) ++begin;
    while (end > begin && is_ws(data[end - 1])) --end;
    return aot_string_make(data + begin, end - begin);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// input(prompt): print the prompt (if a string), read one line from stdin,
// return it as a fresh string. Mirrors the VM builtin (ops: std::getline).
extern "C" uint64_t lymar_aot_input(uint64_t prompt) {
    try {
    RuntimeGuard runtime_guard;
    Word length = 0;
    Word str = aot_string_view(prompt, length);
    if (str && length) {
        lymar_stdout_write(reinterpret_cast<const char*>(str + 24), length);
    }
    std::string line;
    char chunk[4096];
#if defined(_WIN32)
    HANDLE input_handle = lymar_console_handle(STD_INPUT_HANDLE, GENERIC_READ, "CONIN$");
    if (input_handle && input_handle != INVALID_HANDLE_VALUE) {
        for (;;) {
            DWORD got = 0;
            if (!ReadFile(input_handle, chunk, sizeof(chunk), &got, nullptr) || got == 0) break;
            line.append(chunk, got);
            if (line.find('\n') != std::string::npos) break;
        }
    }
#else
    while (std::fgets(chunk, sizeof(chunk), stdin)) {
        line += chunk;
        if (line.find('\n') != std::string::npos) break;
    }
#endif
    if (!line.empty() && line.back() == '\n') line.pop_back();
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return aot_string_make(line.data(), static_cast<Word>(line.size()));
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
extern "C" uint64_t _builtin_list_reserve(uint64_t list_val, uint64_t new_cap) {
    try {
        RuntimeGuard guard;
        if (!list_val) return 0;
        uint64_t list_ptr = list_val & ~7ULL;
        auto& h = heap();
        auto found = h.allocations.find(list_ptr);
        if (found == h.allocations.end() || found->second.size < 32) return 0;
        auto* words = reinterpret_cast<uint64_t*>(list_ptr);
        if ((words[0] & 0xffffffff) != 1) return 0;
        uint64_t cur_cap = words[3];
        if (new_cap > cur_cap) {
            uint64_t old_data = words[1];
            uint64_t cur_len = words[2];
            uint64_t new_data = lymar_aot_alloc(new_cap * sizeof(uint64_t));
            if (new_data) {
                if (old_data && cur_len > 0) {
                    std::memcpy(reinterpret_cast<void*>(new_data),
                                reinterpret_cast<const void*>(old_data),
                                cur_len * sizeof(uint64_t));
                }
                words[1] = new_data;
                words[3] = new_cap;
                lymar_aot_edge(list_ptr + 8, new_data);
                if (found->second.owner != h.active) {
                    h.promote(new_data, found->second.owner);
                }
            }
        }
        return 0;
    } catch (...) {
        return 0;
    }
}
extern "C" uint64_t _builtin_list_with_capacity(uint64_t cap) {
    try {
        RuntimeGuard guard;
        uint64_t actual_cap = cap > 0 ? cap : 8;
        uint64_t list_ptr = lymar_aot_alloc(32);
        uint64_t data = lymar_aot_alloc(actual_cap * sizeof(uint64_t));
        uint64_t* words = reinterpret_cast<uint64_t*>(list_ptr);
        words[0] = 1;
        words[1] = data;
        words[2] = 0;
        words[3] = actual_cap;
        lymar_aot_edge(list_ptr + 8, data);
        return list_ptr;
    } catch (...) {
        return 0;
    }
}
extern "C" void lymar_aot_list_append(uint64_t list_val, uint64_t val) {
    try {
        RuntimeGuard guard;
        if (!list_val) return;
        uint64_t list_ptr = list_val & ~7ULL;
        auto& h = heap();
        auto found = h.allocations.find(list_ptr);
        if (found == h.allocations.end() || found->second.size < 32) return;
        auto* words = reinterpret_cast<uint64_t*>(list_ptr);
        if ((words[0] & 0xffffffff) != 1) return;
        uint64_t len = words[2];
        uint64_t cap = words[3];
        if (len >= cap) {
            uint64_t new_cap = cap ? cap * 2 : 8;
            uint64_t old_data = words[1];
            uint64_t new_data = lymar_aot_alloc(new_cap * sizeof(uint64_t));
            if (!new_data) return;
            if (old_data && len > 0) {
                std::memcpy(reinterpret_cast<void*>(new_data),
                            reinterpret_cast<const void*>(old_data),
                            len * sizeof(uint64_t));
            }
            words[1] = new_data;
            words[3] = new_cap;
            lymar_aot_edge(list_ptr + 8, new_data);
            if (found->second.owner != h.active) {
                h.promote(new_data, found->second.owner);
            }
        }
        auto* data = reinterpret_cast<uint64_t*>(words[1]);
        data[len] = val;
        words[2] = len + 1;
        // Exact-match only: interior pointers (e.g. ffi ptr+N offsets stored
        // in typed [int] lists) are address scalars, not ownable object refs —
        // edge() would misread their low tag bits as LmValue tags.
        if (val && h.allocations.find(val) != h.allocations.end()) {
            lymar_aot_edge(words[1] + len * sizeof(uint64_t), val);
        }
    } catch (...) {
    }
}
// Element-storage kind for TYPE_LIST objects, kept in the high 32 bits of the
// header word (low 32 bits hold the object type). 0 = tagged LmValue elements
// (default), 1 = raw int elements, 2 = raw bool elements. Typed primitive
// lists store unboxed scalars; the formatter needs this to decode them.
extern "C" void lymar_aot_list_set_element_kind(uint64_t list_val, uint64_t kind) {
    try {
        RuntimeGuard guard;
        if (!list_val) return;
        uint64_t list_ptr = list_val & ~7ULL;
        auto& h = heap();
        auto found = h.allocations.find(list_ptr);
        if (found == h.allocations.end() || found->second.size < 32) return;
        auto* words = reinterpret_cast<uint64_t*>(list_ptr);
        if ((words[0] & 0xffffffff) != 1) return;
        words[0] = (words[0] & 0xffffffffULL) | ((kind & 0xffffffffULL) << 32);
    } catch (...) {
    }
}
// Decode a raw stored list element into the canonical tagged LmValue word using
// the header's element-storage kind (high 32 bits of words[0]):
//   0 = elements already tagged LmValue words -> passthrough
//   1 = raw int64 elements -> tag_int
//   2 = raw bool elements (0/1) -> tag_bool
extern "C" uint64_t lymar_aot_list_elem_decode(uint64_t elem, uint64_t elem_kind) {
    if (elem_kind == 1) return lymar_aot_tag_int(static_cast<int64_t>(elem));
    if (elem_kind == 2) return lymar_aot_tag_bool(elem);
    return elem;
}
// Encode a tagged LmValue into element-storage form for kind 1/2 lists; kind 0
// passes the tagged word through unchanged.
extern "C" uint64_t lymar_aot_list_elem_encode(uint64_t tagged, uint64_t elem_kind) {
    if (elem_kind == 1) return static_cast<uint64_t>(lymar_aot_untag_int(tagged));
    if (elem_kind == 2) return static_cast<uint64_t>(lymar_aot_untag_bool(tagged));
    return tagged;
}
// Kind-aware element store for erased-view writes: encodes the tagged value per
// the list's storage kind, stores it, and records an ownership edge only for
// kind-0 (tagged-word) elements that reference a live heap allocation.
extern "C" void lymar_aot_list_elem_store(uint64_t addr, uint64_t tagged, uint64_t elem_kind) {
    try {
        RuntimeGuard guard;
        uint64_t stored = lymar_aot_list_elem_encode(tagged, elem_kind);
        *reinterpret_cast<uint64_t*>(addr) = stored;
        if (elem_kind == 0 && stored && heap().allocations.find(stored) != heap().allocations.end()) {
            lymar_aot_edge(addr, stored);
        }
    } catch (...) {
    }
}
// Erased-view append: like lymar_aot_list_append but encodes the tagged value
// into the list's element-storage kind before storing. Typed primitive appends
// keep calling lymar_aot_list_append with already-raw elements.
extern "C" void lymar_aot_list_append_tagged(uint64_t list_val, uint64_t tagged) {
    try {
        RuntimeGuard guard;
        if (!list_val) return;
        uint64_t list_ptr = list_val & ~7ULL;
        auto& h = heap();
        auto found = h.allocations.find(list_ptr);
        if (found == h.allocations.end() || found->second.size < 32) return;
        auto* words = reinterpret_cast<uint64_t*>(list_ptr);
        if ((words[0] & 0xffffffff) != 1) return;
        uint64_t elem_kind = words[0] >> 32;
        uint64_t len = words[2];
        uint64_t cap = words[3];
        if (len >= cap) {
            uint64_t new_cap = cap ? cap * 2 : 8;
            uint64_t old_data = words[1];
            uint64_t new_data = lymar_aot_alloc(new_cap * sizeof(uint64_t));
            if (!new_data) return;
            if (old_data && len > 0) {
                std::memcpy(reinterpret_cast<void*>(new_data),
                            reinterpret_cast<const void*>(old_data),
                            len * sizeof(uint64_t));
            }
            words[1] = new_data;
            words[3] = new_cap;
            lymar_aot_edge(list_ptr + 8, new_data);
            if (found->second.owner != h.active) {
                h.promote(new_data, found->second.owner);
            }
        }
        auto* data = reinterpret_cast<uint64_t*>(words[1]);
        uint64_t stored = lymar_aot_list_elem_encode(tagged, elem_kind);
        data[len] = stored;
        words[2] = len + 1;
        if (elem_kind == 0 && tagged && h.allocations.find(tagged) != h.allocations.end()) {
            lymar_aot_edge(words[1] + len * sizeof(uint64_t), tagged);
        }
    } catch (...) {
    }
}
extern "C" void lymar_aot_dict_grow(uint64_t dict_ptr) {
    try {
        RuntimeGuard guard;
        if (!dict_ptr) return;
        auto& h = heap();
        auto found = h.allocations.find(dict_ptr);
        if (found == h.allocations.end() || found->second.size < 32) return;
        auto* words = reinterpret_cast<uint64_t*>(dict_ptr);
        uint64_t count = words[0];
        uint64_t cap = words[1];
        if (count < cap) return;

        uint64_t new_cap = cap ? cap * 2 : 32;
        uint64_t old_keys = words[2];
        uint64_t old_vals = words[3];

        uint64_t new_keys = lymar_aot_alloc(new_cap * sizeof(uint64_t));
        uint64_t new_vals = lymar_aot_alloc(new_cap * sizeof(uint64_t));
        if (!new_keys || !new_vals) return;

        std::memset(reinterpret_cast<void*>(new_keys), 0, new_cap * sizeof(uint64_t));
        std::memset(reinterpret_cast<void*>(new_vals), 0, new_cap * sizeof(uint64_t));

        if (old_keys && count > 0) {
            std::memcpy(reinterpret_cast<void*>(new_keys),
                        reinterpret_cast<const void*>(old_keys),
                        count * sizeof(uint64_t));
        }
        if (old_vals && count > 0) {
            std::memcpy(reinterpret_cast<void*>(new_vals),
                        reinterpret_cast<const void*>(old_vals),
                        count * sizeof(uint64_t));
        }

        words[1] = new_cap;
        words[2] = new_keys;
        words[3] = new_vals;

        lymar_aot_edge(dict_ptr + 16, new_keys);
        lymar_aot_edge(dict_ptr + 24, new_vals);

        for (uint64_t index = 0; index < count; ++index) {
            // Element words are tagged LmValues; edge derives ownership from
            // the word's own LmValue tag.
            uint64_t k = reinterpret_cast<uint64_t*>(new_keys)[index];
            lymar_aot_edge(new_keys + index * sizeof(uint64_t), k);
            uint64_t v = reinterpret_cast<uint64_t*>(new_vals)[index];
            lymar_aot_edge(new_vals + index * sizeof(uint64_t), v);
        }

        if (found->second.owner != h.active) {
            h.promote(new_keys, found->second.owner);
            h.promote(new_vals, found->second.owner);
        }
    } catch (...) {
    }
}
extern "C" uint64_t _builtin_string_join(uint64_t list_val, uint64_t delim_val) {
    try {
        RuntimeGuard guard;
        auto& h = heap();
        if (!list_val) return 0;
        uint64_t list_ptr = list_val & ~7ULL;
        auto found = h.allocations.find(list_ptr);
        if (found == h.allocations.end() || found->second.size < 32) return 0;
        uint64_t* words = reinterpret_cast<uint64_t*>(list_ptr);
        if ((words[0] & 0xffffffff) != 1) return 0;
        uint64_t data_ptr = words[1];
        uint64_t count = words[2];

        std::string delim_str;
        if (delim_val) {
            const char* d = string_data(delim_val);
            if (d) delim_str = d;
        }

        std::string result;
        for (uint64_t i = 0; i < count; ++i) {
            if (i > 0 && !delim_str.empty()) result += delim_str;
            uint64_t item = read_word(data_ptr, i * 8);
            const char* text = string_data(item);
            if (text) result += text;
        }

        auto object = lymar_aot_alloc(25 + result.size());
        Word header[3] = {11, static_cast<Word>(result.size()), static_cast<Word>(result.size())};
        std::memcpy(reinterpret_cast<void*>(object), header, 24);
        std::memcpy(reinterpret_cast<void*>(object + 24), result.c_str(), result.size() + 1);
        return object;
    } catch (...) {
        return 0;
    }
}
extern "C" uint64_t _builtin_string_from_cstr(uint64_t cstr_val) {
    try {
        RuntimeGuard guard;
        if (!cstr_val) return 0;
        const char* cstr = reinterpret_cast<const char*>(cstr_val);
        size_t len = std::strlen(cstr);
        auto object = lymar_aot_alloc(25 + len);
        Word header[3] = {11, static_cast<Word>(len), static_cast<Word>(len)};
        std::memcpy(reinterpret_cast<void*>(object), header, 24);
        std::memcpy(reinterpret_cast<void*>(object + 24), cstr, len + 1);
        return object;
    } catch (...) {
        return 0;
    }
}
extern "C" uint64_t _builtin_string_to_cstr(uint64_t str_val) {
    if (!str_val) return 0;
    const char* d = string_data(str_val);
    return reinterpret_cast<uint64_t>(d);
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_free(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;
    if (pointer && pointer != 2 && heap().allocations.count(pointer)) heap().release(pointer);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
// ---------------------------------------------------------------------------
// LmValue boundary tagging (Option 2)
// Managed-memory slots hold self-describing tagged words: SMI ints (v<<3)|1,
// immediates (VAL_NIL/VAL_FALSE/VAL_TRUE), and TAG_PTR heap pointers. There
// is no kind sidecar: consumers decode `word & 7` directly.
// ---------------------------------------------------------------------------
static Word tag_int_word(Word value) {
    return lymar_aot_tag_int(static_cast<int64_t>(value));
}
// Decode a managed-slot word for a typed (raw-domain) consumer: SMI -> int,
// immediates -> 1/0, heap number/foreign-pointer boxes -> payload, everything
// else passes through as the tagged word itself.
extern "C" uint64_t lymar_aot_untag_at(uint64_t word) {
    try {
    RuntimeGuard runtime_guard;

    Word tag = word & TAG_MASK;
    if (tag == TAG_INT) return static_cast<uint64_t>(static_cast<int64_t>(word) >> 3);
    if (word == VAL_TRUE) return 1;
    if (word == VAL_FALSE || word == VAL_NIL || word == 0) return 0;
    if (tag == TAG_PTR && word > 4096 && heap().allocations.count(word)) {
        Word type = read_word(word) & 0xffffffff;
        if (type == 5 || type == 13) return read_word(word, 8);
    }
    return word;

    } catch (...) { return word; }
}
void lymar_aot_edge(uint64_t address, uint64_t child) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();

    // Ownership is derived solely from the child's LmValue tag: only a live
    // heap allocation (TAG_PTR + allocations membership) can be a child edge.
    Word ptr = is_heap_word(child) ? child : 0;

    auto container = h.containing(address);
    if (container != h.allocations.end() && !container->second.raw_memory && child != 0) {
        auto offset = address - container->first;
        uint64_t w0 = read_word(container->first) & 0xffffffff;
        bool is_header_field = (offset == 0) ||
            (w0 == 1 && (offset == 16 || offset == 24)) || // List len, cap
            (w0 == 3 && (offset == 16 || offset == 24)) || // Tuple len, cap
            (w0 == 15 && offset == 24) ||                  // Frame field count
            (w0 == 11 && (offset == 8 || offset == 16)) || // String len, hash
            (container->second.dictionary && (offset == 0 || offset == 8)) || // Dict count, cap
            (container->second.size == 32 && w0 == 0x4C594D41524F4B21LL && (offset == 8 || offset == 24)) || // Ok/Err box tag and kind
            (container->second.size == 32 && w0 == 0x454E554D && offset == 8); // Enum ordinal tag (payload/vname stay edged)
        if (!is_header_field && child != 0) {
            uint64_t tag = child & TAG_MASK;
            bool ok = (tag == TAG_INT) ||
                      (tag == TAG_PTR) ||
                      (child == VAL_NIL || child == VAL_FALSE || child == VAL_TRUE);
            if (!ok) {
                std::fprintf(stderr, "[TAG ASSERTION FAILED] lymar_aot_edge: addr=0x%llx (base=0x%llx size=%llu off=%llu w0=%llu) child=0x%llx (tag=%llu)\n",
                    (unsigned long long)address, (unsigned long long)container->first, (unsigned long long)container->second.size, (unsigned long long)offset, (unsigned long long)w0,
                    (unsigned long long)child, (unsigned long long)tag);
                std::fflush(stderr);
                std::abort();
            }
        }
    }

    if (ptr) h.promote(ptr, 0);
    if (container == h.allocations.end()) return;
    auto offset = address - container->first;
    container->second.edges.erase(offset);
    if (ptr && h.containing(ptr) != h.allocations.end()) {
        container->second.edges[offset] = ptr;
        h.promote(ptr, container->second.owner);
    }

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
// Raw access is explicitly unsafe in source. Preserve external/FFI addresses;
// use memcpy so valid byte-addressed unaligned accesses do not acquire C++ UB.
// Raw bytes do not transfer pointee ownership; managed stores publish edges separately.
uint64_t lymar_aot_channel_length(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;

    if (lymar_aot_is_nil(value) || !is_heap_word(value)) return 0;
    auto& h = heap();
    auto found = h.allocations.find(value);
    if (found == h.allocations.end() || found->second.size < 32 || (read_word(value) & 0xffffffff) != 1)
        return 0; // A non-queue task value is a single invocation, not an iterator.
    return read_word(value, 16);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Decode a tagged word to a raw address for unsafe memory access. Heap
// objects pass through (their address is the pointer); foreign-pointer and
// boxed-integer wrappers yield their payload; SMI/immediate words decode to
// their integer value; anything else is already a raw address.
static uint64_t raw_address(uint64_t value) {
    if (value == VAL_NIL || value == VAL_FALSE || value == 0) return 0;
    if (value == VAL_TRUE) return 1;
    Word tag = value & TAG_MASK;
    if (tag == TAG_INT) return static_cast<uint64_t>(static_cast<int64_t>(value) >> 3);
    if (tag == TAG_PTR && value > 4096) {
        auto found = heap().allocations.find(value);
        if (found != heap().allocations.end() && !found->second.raw_memory &&
            !found->second.dictionary && found->second.size >= 16) {
            Word type = read_word(value) & 0xffffffff;
            if (type == 13 || type == 5) return read_word(value, 8);
        }
    }
    return value;
}
uint64_t lymar_aot_memory_load(uint64_t pointer, uint64_t element) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer);
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Raw stores use the VM's physical numeric conversion, not string parsing or
// arbitrary object-header heuristics. Raw buffers may themselves begin with 9.
static double raw_numeric_value(uint64_t value) {
    Word tag = value & TAG_MASK;
    if (tag == TAG_INT) return static_cast<double>(static_cast<int64_t>(value) >> 3);
    if (value == VAL_TRUE) return 1.0;
    if (value == VAL_FALSE || value == VAL_NIL || value == 0) return 0.0;
    if (tag == TAG_IMMEDIATE) return 0.0;
    auto found = heap().allocations.find(value);
    if (found != heap().allocations.end() && !found->second.raw_memory && !found->second.dictionary &&
        found->second.size >= 16 && (read_word(value) & 0xffffffff) == 9) {
        double result; std::memcpy(&result, reinterpret_cast<void*>(value + 8), sizeof(result));
        return result;
    }
    if (auto integer = integer_number(value)) return static_cast<double>(*integer);
    // Non-numeric words carry raw bits: foreign pointers, module constants and
    // fnptr/pubptr aliases. Store the address/scalar, not zero.
    return static_cast<double>(static_cast<int64_t>(value));
}
static uint64_t raw_integer_value(uint64_t value) {
    Word tag = value & TAG_MASK;
    if (tag == TAG_INT) return static_cast<uint64_t>(static_cast<int64_t>(value) >> 3);
    if (value == VAL_TRUE) return 1;
    if (value == VAL_FALSE || value == VAL_NIL || value == 0) return 0;
    if (tag == TAG_IMMEDIATE) return 0;
    auto found = heap().allocations.find(value);
    if (found != heap().allocations.end() && !found->second.raw_memory && !found->second.dictionary &&
        found->second.size >= 16) {
        auto type = read_word(value) & 0xffffffff;
        if (type == 5 || type == 6 || type == 13) return read_word(value, 8);
        if (type == 9) return static_cast<uint64_t>(LM::Memory::truncate_i64(raw_numeric_value(value)));
    }
    if (auto integer = integer_number(value)) return static_cast<Word>(*integer);
    return value;
}
uint64_t lymar_aot_raw_alloc(uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    size = raw_integer_value(size);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    auto pointer = lymar_aot_alloc(size);
    heap().allocations.at(pointer).raw_memory = true;
    // ffi.alloc mirrors malloc: lifetime is explicit (ffi.free) or process
    // exit. Region-scoping is unsafe here — pubptr/fnptr are int aliases, so
    // no GC edge can ever promote a raw buffer out of its creating region,
    // and region cleanup frees it while raw pointers derived from it are
    // still live (control blocks, WNDCLASSEX structs, callback scratch).
    heap().promote(pointer, 0);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_raw_free(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer);
    auto found = heap().allocations.find(pointer);
    if (found != heap().allocations.end() && found->second.raw_memory) heap().release(pointer);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_memory_store(uint64_t pointer, uint64_t value, uint64_t element) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer);
    if (element > 10) throw std::runtime_error("Invalid raw memory element kind");
    if (!pointer) return;
    auto* address = reinterpret_cast<void*>(pointer);
    const Word integer = element < 8 ? raw_integer_value(value) : value;
    // Pointer stores must persist the raw address, not the tag-13 wrapper
    // object: ffi.fnptr/pubptr values are heap boxes whose payload (offset 8)
    // is the real pointer. Storing the wrapper address hands consumers (e.g. a
    // WNDCLASSEX.lpfnWndProc consumed by CreateWindowExA) a heap pointer that
    // faults when called.
    Word pointer_value = raw_integer_value(value);
    if (element == 10 && pointer_value > 4096) {
        // pubptr/fnptr are int aliases, so an int-held tag-13 box address can
        // arrive SMI-tagged (tag_word) or raw. raw_integer_value decodes the
        // SMI back to the box address; unwrap one more level to the payload.
        auto wrapped = heap().allocations.find(pointer_value);
        if (wrapped != heap().allocations.end() && !wrapped->second.raw_memory &&
            wrapped->second.size >= 16 && read_word(pointer_value) == 13)
            pointer_value = read_word(pointer_value, 8);
    }
    size_t width = 0;
    switch (element) {
#define LM_RAW_STORE(ID, TYPE, VALUE) case ID: { TYPE stored = static_cast<TYPE>(VALUE); width = sizeof(stored); std::memcpy(address, &stored, width); break; }
        LM_RAW_STORE(0, int8_t, integer) LM_RAW_STORE(1, uint8_t, integer)
        LM_RAW_STORE(2, int16_t, integer) LM_RAW_STORE(3, uint16_t, integer)
        LM_RAW_STORE(4, int32_t, integer) LM_RAW_STORE(5, uint32_t, integer)
        LM_RAW_STORE(6, int64_t, integer) LM_RAW_STORE(7, uint64_t, integer)
        LM_RAW_STORE(8, float, raw_numeric_value(value))
        LM_RAW_STORE(9, double, raw_numeric_value(value))
        LM_RAW_STORE(10, Word, (value != VAL_NIL && value != 0 && value != VAL_FALSE) ? pointer_value : 0)
#undef LM_RAW_STORE
    }
    auto& h = heap();
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_global_edge(uint64_t address, uint64_t child) {
    try {
    RuntimeGuard runtime_guard;

    // Global slots hold tagged LmValue words; only live heap allocations
    // create ownership edges (promoted into the permanent region 0).
    if (is_heap_word(child)) heap().promote(child, 0);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_copy(uint64_t destination, uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    std::memmove(reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), size);
    auto dst = h.containing(destination);
    if (dst != h.allocations.end()) {
        auto start = destination - dst->first;
        std::erase_if(dst->second.edges, [&](auto edge) { return edge.first >= start ? edge.first - start < size : start - edge.first < sizeof(Word); });
        // Re-publish ownership for every tagged heap word now in the
        // destination range. Managed copies are word-aligned.
        if ((destination & (sizeof(Word) - 1)) == 0 && size % sizeof(Word) == 0) {
            for (Word offset = 0; offset + sizeof(Word) <= size; offset += sizeof(Word)) {
                Word word = read_word(destination + offset);
                if (is_heap_word(word)) {
                    dst->second.edges[start + offset] = word;
                    h.promote(word, dst->second.owner);
                }
            }
        }
    }

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
    // use lymar_aot_copy and explicitly preserve their edges instead.
    auto owner = h.containing(destination);
    if (owner != h.allocations.end()) {
        auto start = destination - owner->first;
        std::erase_if(owner->second.edges, [&](auto entry) {
            return entry.first >= start ? entry.first - start < size : start - entry.first < sizeof(Word);
        });
    }
    std::memmove(reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_fill(uint64_t destination, uint64_t value, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!destination || static_cast<int64_t>(size) <= 0) return;
    auto& h = heap();
    // Invalidate overlapping edges; byte filling must not retain a
    // pointer edge whose bytes have been replaced by unrelated data.
    auto owner = h.containing(destination);
    if (owner != h.allocations.end()) {
        auto start = destination - owner->first;
        std::erase_if(owner->second.edges, [&](auto entry) {
            return entry.first >= start ? entry.first - start < size : start - entry.first < sizeof(Word);
        });
    }
    std::memset(reinterpret_cast<void*>(destination), static_cast<unsigned char>(value), size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_raw_resize(uint64_t pointer, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer);
    size = raw_integer_value(size);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    if (!pointer) return lymar_aot_raw_alloc(size);
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || !found->second.raw_memory) return lymar_aot_nil();
    if (!size) { heap().release(pointer); return lymar_aot_nil(); }
    return lymar_aot_resize(pointer, size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_raw_copy_checked(uint64_t destination, uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    lymar_aot_raw_copy(raw_address(destination), raw_address(source), raw_integer_value(size));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_fill_checked(uint64_t destination, uint64_t value, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    lymar_aot_raw_fill(raw_address(destination), raw_integer_value(value), raw_integer_value(size));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_raw_compare_checked(uint64_t left, uint64_t right, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    return lymar_aot_raw_compare(raw_address(left), raw_address(right), raw_integer_value(size));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_set_finalizer(uint64_t pointer, void (*callback)(uint64_t)) {
    try {
    RuntimeGuard runtime_guard;

    heap().allocations.at(pointer).finalizer = callback;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_finalize(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;
 heap().finalize(pointer);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
#if !defined(__wasi__)
void* NativeGraphicsAccess::list(Value value) {
    auto& allocations=heap().allocations;auto found=allocations.find(value.word);
    if(value.kind!=object_kind || found==allocations.end() || found->second.raw_memory ||
       found->second.dictionary || found->second.size<32 || (read_word(value.word)&0xffffffff)!=1) return nullptr;
    lymar_aot_ffi_list_size(value.word);
    return reinterpret_cast<void*>(value.word);
}
const char* NativeGraphicsAccess::string(Value value) {
    return value.kind==object_kind?string_data(value.word):nullptr;
}
NativeGraphicsAccess::List* NativeGraphicsAccess::new_list() {
    auto pointer=lymar_aot_alloc(32),data=lymar_aot_alloc(32);
    Word header[4]={1,data,0,4};std::memcpy(reinterpret_cast<void*>(pointer),header,32);
    lymar_aot_edge(pointer+8,data);
    return reinterpret_cast<List*>(pointer);
}
void NativeGraphicsAccess::append(List* list,Value value) {
    auto pointer=reinterpret_cast<Word>(list),count=lymar_aot_ffi_list_size(pointer);
    auto data=read_word(pointer,8),capacity=read_word(pointer,24);
    if(count==capacity) {
        if(capacity>UINT64_MAX/16) throw std::runtime_error("Graphics event list capacity overflow");
        auto next=std::max<Word>(4,capacity*2),replacement=lymar_aot_alloc(next*8);
        for(Word index=0;index<count;++index) {
            auto item=lymar_aot_ffi_list_item(pointer,index);
            std::memcpy(reinterpret_cast<void*>(replacement+index*8),&item,8);
            lymar_aot_edge(replacement+index*8,item);
        }
        std::memcpy(reinterpret_cast<void*>(pointer+8),&replacement,8);
        std::memcpy(reinterpret_cast<void*>(pointer+24),&next,8);
        lymar_aot_edge(pointer+8,replacement);
        lymar_aot_free(data);data=replacement;
    }
    // Fold the legacy (word,kind) pair into a self-describing LmValue word.
    Word tagged = value.word;
    if (value.kind == boolean_kind) tagged = value.word ? VAL_TRUE : VAL_FALSE;
    else if (value.kind == 0) tagged = tag_int_word(static_cast<int64_t>(value.word));
    std::memcpy(reinterpret_cast<void*>(data+count*8),&tagged,8);
    lymar_aot_edge(data+count*8,tagged);
    ++count;std::memcpy(reinterpret_cast<void*>(pointer+16),&count,8);
}
#endif
uint64_t lymar_aot_resource_create(uint64_t type, uint64_t) {
    try {
    RuntimeGuard runtime_guard;

    if (type == 9) return 0; // stdout
    if (type == 10) return 1; // stderr
    if(type==16) {auto& f=files();auto id=f.next++;f.hashes.try_emplace(id);return id;}
    if(type==11) {auto& f=files();auto id=f.next++;f.mems.emplace(id, std::make_pair(nullptr, size_t(0)));return id;}
    // OS (18) and PROCESS (4) are stateless service handles. The facts they
    // report come from the process itself, so nothing is stored per handle.
    if(type==18||type==4) {auto& f=files();auto id=f.next++;f.services.emplace(id,type);return id;}
#if !defined(__wasi__)
    if(type==17) {
        // aot_gfx_create is weak: absent (NULL) when the graphics archive
        // member was not linked, which is the case for console-only builds.
        // Route the call through a pointer so the only relocation against the
        // weak symbol is the address load (resolves to 0), never a PC32 call.
        auto* create = aot_gfx_create;
        if(!create) throw std::runtime_error("Standalone resource type is not implemented: 17");
        auto& f=files();auto id=f.next++;f.graphics.emplace(id,std::unique_ptr<GraphicsBase>(create()));return id;
    }
#endif
    if (type != 0) throw std::runtime_error("Standalone resource type is not implemented: " + std::to_string(type));
    auto& f = files();
    auto id = f.next++;
    f.handles.emplace(id, nullptr);
    return id;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_resource_destroy(uint64_t id) {
    try {
    RuntimeGuard runtime_guard;

    auto& f = files();
    if(f.hashes.erase(id)) return;
    if(f.services.erase(id)) return;
    if(auto mem=f.mems.find(id);mem!=f.mems.end()) { if(mem->second.first) std::free(mem->second.first); f.mems.erase(mem); return; }
#if !defined(__wasi__)
    if(f.graphics.erase(id)) return;
#endif
    auto found = f.handles.find(id);
    if (found == f.handles.end()) return;
    if (found->second) std::fclose(found->second);
    f.handles.erase(found);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
// ABI helper for the Fyra capability lowering of resource ops 30-34. The
// builder packs the ResourceCall tail registers into the same (count,
// arguments) array lymar_aot_resource_call receives, then asks for the Nth
// flattened argument as a NUL-terminated C string. Flattening mirrors the
// runtime dispatch exactly: a list entry contributes its elements in order,
// any other non-nil entry contributes itself. Returns 0 when the argument is
// absent or is not a string object, so capability calls degrade to a clean
// failure instead of dereferencing a non-pointer word.
extern "C" uint64_t lymar_aot_resource_str_arg(uint64_t arguments, uint64_t count, uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    static const char empty[] = "";
    uint64_t seen = 0;
    for (uint64_t n = 0; n < count; ++n) {
        auto value = read_word(arguments, n * 8);
        if (value > 4096 && (value & TAG_MASK) == TAG_PTR && (read_word(value) & 0xffffffff) == 1) {
            auto data = read_word(value, 8), size = read_word(value, 16);
            auto elem_kind = read_word(value) >> 32;
            for (uint64_t i = 0; i < size; ++i) {
                if (seen++ != index) continue;
                auto elem = lymar_aot_list_elem_decode(read_word(data, i * 8), elem_kind);
                if (auto* text = string_data(elem)) return reinterpret_cast<uint64_t>(text);
                return reinterpret_cast<uint64_t>(empty);
            }
        } else if (value != 0 && value != VAL_NIL && value != 2) {
            if (seen++ == index) {
                if (auto* text = string_data(value)) return reinterpret_cast<uint64_t>(text);
                return reinterpret_cast<uint64_t>(empty);
            }
        }
    }
    return reinterpret_cast<uint64_t>(empty);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        static const char empty[] = "";
        return reinterpret_cast<uint64_t>(empty);
    }
}
uint64_t lymar_aot_resource_call(uint64_t id, uint64_t operation, uint64_t count, uint64_t arguments) {
    try {
    RuntimeGuard runtime_guard;

    constexpr Word nil = 2;
    auto& h = heap();
    // Derive the legacy kind classification from the LmValue tag itself so the
    // graphics Value ABI (word+kind pairs) keeps working without a sidecar.
    auto derive_kind = [](Word w) -> Word {
        Word t = w & TAG_MASK;
        if (t == TAG_PTR && w > 4096 && heap().allocations.count(w)) return object_kind;
        if (t == TAG_INT) return object_kind;
        if (w == VAL_TRUE || w == VAL_FALSE) return boolean_kind;
        if (w == VAL_NIL || w == 0) return object_kind;
        return 0;
    };
    std::vector<Word> args;
    std::vector<Word> pointers;
    for (Word n = 0; n < count; ++n) {
        auto value = read_word(arguments, n * 8);
        Word pointer = derive_kind(value);
        if (is_heap_word(value) && (read_word(value) & 0xffffffff) == 1) {
            auto data = read_word(value, 8), size = read_word(value, 16);
            auto elem_kind = read_word(value) >> 32;
            for (Word i = 0; i < size; ++i) {
                auto element = lymar_aot_list_elem_decode(read_word(data, i * 8), elem_kind);
                args.push_back(element);
                pointers.push_back(derive_kind(element));
            }
        } else if (!lymar_aot_is_nil(value)) { args.push_back(value); pointers.push_back(pointer); }
    }
    auto arg_string = [&](size_t n) { auto* s = n < args.size() ? string_data(args[n]) : nullptr; return s ? s : ""; };
    auto& f = files();
    auto service = f.services.find(id);
    if (service != f.services.end()) {
        // Shares LM::Runtime::OS with the RegisterVM resource handlers, so both
        // backends report identical values for the same operation.
        namespace os = LM::Runtime::OS;
        auto truth=[&](bool yes) {return yes?VAL_TRUE:VAL_FALSE;};
        auto number=[&](int64_t value) {return tag_int_word(value);};
        auto string_object=[&](const std::string& bytes) {
            auto object=lymar_aot_alloc(25+bytes.size());
            Word header[3]={11,bytes.size(),bytes.size()};
            std::memcpy(reinterpret_cast<void*>(object),header,24);
            std::memcpy(reinterpret_cast<void*>(object+24),bytes.c_str(),bytes.size()+1);
            return object;
        };
        auto text=[&](const std::string& bytes) {return string_object(bytes);};
        auto absent=[&]() {return nil;};
        auto strings=[&](const std::vector<std::string>& items) {
            // Same [str] layout the graphics event list uses: a 32-byte header
            // of {TYPE_LIST, data, count, capacity} plus the element slots.
            auto pointer=lymar_aot_alloc(32);
            auto capacity=std::max<Word>(1,items.size());
            auto data=lymar_aot_alloc(capacity*8);
            Word header[4]={1,data,0,capacity};
            std::memcpy(reinterpret_cast<void*>(pointer),header,32);
            lymar_aot_edge(pointer+8,data);
            for (const auto& item : items) {
                auto object=string_object(item);
                // Elements are written back through the header: an allocation
                // above can relocate the payload, so no cached address is reused.
                auto slot_data=read_word(pointer,8);
                auto count=read_word(pointer,16);
                if (count>=capacity) break;
                std::memcpy(reinterpret_cast<void*>(slot_data+count*8),&object,8);
                lymar_aot_edge(slot_data+count*8,object);
                ++count;
                std::memcpy(reinterpret_cast<void*>(pointer+16),&count,8);
            }
            return pointer;
        };
        auto arg_text=[&](size_t n) { return n < args.size() && pointers[n] == object_kind ? std::string(arg_string(n)) : std::string(); };
        if (service->second == 18) {  // ResourceType::OS
            if (operation == 53) { auto path=os::cwd(); return path.empty()?absent():text(path); }  // CWD
            if (operation == 54) return truth(!arg_text(0).empty() && os::chdir_to(arg_text(0)));  // CHDIR
            if (operation == 55) return text(os::home_dir());  // HOME_DIR
            if (operation == 56) return text(os::temp_dir());  // TEMP_DIR
            if (operation == 57) return text(os::exe_path());  // EXE_PATH
            if (operation == 58) return text(os::os_name());  // OS_NAME
            if (operation == 59) return text(os::arch());  // ARCH
            if (operation == 60) return text(os::hostname());  // HOSTNAME
            if (operation == 61) return number(os::num_cpu());  // NUM_CPU
            return absent();
        }
        if (service->second == 4) {  // ResourceType::PROCESS
            if (operation == 62) return strings(os::program_arguments());  // PROC_ARGS
            if (operation == 67) return text(os::command_name());  // PROC_COMMAND
            if (operation == 64) return number(os::pid());  // PROC_ID
            if (operation == 65) return number(os::rss_kb());  // PROC_RSS (kB, -1 unsupported)
            if (operation == 66) return number(os::peak_rss_kb());  // PROC_PEAK_RSS
            if (operation == 63) {  // PROC_EXIT: never returns.
                int64_t code = 0;
                if (!args.empty()) { auto value = integer_number(args[0]); if (value) code = *value; }
                os::terminate(static_cast<int>(code));
                return number(code);
            }
            if (operation == 9) {  // SPAWN: flattened argv, blocks, returns exit code.
                std::vector<std::string> argv;
                for (size_t n = 0; n < args.size(); ++n) { auto* text_value = arg_string(n); if (text_value) argv.emplace_back(text_value); }
                if (argv.empty()) return number(-1);
                return number(os::spawn_wait(argv));
            }
            return absent();
        }
        return absent();
    }
#if !defined(__wasi__)
    if(auto graphics=f.graphics.find(id);graphics!=f.graphics.end()) {
        std::vector<GraphicsValue> values;
        for(size_t index=0;index<args.size();++index) values.push_back({args[index],pointers[index]});
        auto returned=graphics->second->call(static_cast<LM::Backend::VM::ResourceOperation>(operation),values,nullptr);
        // GraphicsValue carries the legacy (word,kind) pair; fold it back into
        // a self-describing LmValue word for erased consumers.
        if (returned.kind == boolean_kind) return returned.word ? VAL_TRUE : VAL_FALSE;
        if (returned.kind == 0) return tag_int_word(static_cast<int64_t>(returned.word));
        return returned.word;
    }
#endif
    if(auto hash=f.hashes.find(id);hash!=f.hashes.end()) {
        auto truth=[&](bool yes) {return yes?VAL_TRUE:VAL_FALSE;};
        auto text=[&](const std::string& bytes) {auto object=lymar_aot_alloc(25+bytes.size());Word header[3]={11,bytes.size(),bytes.size()};std::memcpy(reinterpret_cast<void*>(object),header,24);std::memcpy(reinterpret_cast<void*>(object+24),bytes.c_str(),bytes.size()+1);return object;};
        if(operation==0) {auto* algorithm=args.empty()?"sha256":arg_string(0);return truth(algorithm && hash->second.open(algorithm));}
        if(operation==3) {auto* bytes=arg_string(0);if(!bytes) return truth(false);hash->second.write(bytes,std::strlen(bytes));return truth(true);}
        if(operation==2) return text(hash->second.read());
        if(operation==35) {auto* algorithm=args.empty()?"sha256":arg_string(0);auto* key=arg_string(1);auto* bytes=arg_string(2);if(!algorithm || !key || !bytes) return nil;return text(LM::Runtime::compute_hmac(algorithm,key,bytes));}
        if(operation==1) return truth(true);
        return nil;
    }
    if(auto mem=f.mems.find(id);mem!=f.mems.end()) {
        auto& buf = mem->second;
        auto truth=[&](bool yes) {return yes?VAL_TRUE:VAL_FALSE;};
        if(operation==0) { // OPEN: allocate / resize the byte buffer to the requested size.
            size_t n = buf.second;
            if (!args.empty()) { auto v = integer_number(args[0]); if (v) n = static_cast<size_t>(*v); }
            if (buf.first) std::free(buf.first);
            buf.first = n ? std::malloc(n) : nullptr;
            buf.second = buf.first ? n : 0;
            return truth(n == 0 || buf.first != nullptr);
        }
        if(operation==3) { // WRITE: copy string bytes into the buffer (bounded by capacity).
            auto* d = arg_string(0);
            if (!d || !buf.first) return truth(false);
            size_t l = std::min(std::strlen(d), buf.second);
            std::memcpy(buf.first, d, l);
            return truth(true);
        }
        if(operation==2) { // READ: return the buffer contents as a string.
            if (!buf.first || buf.second == 0) {  return nil; }
            auto object=lymar_aot_alloc(25+buf.second);
            Word header[3]={11,buf.second,buf.second};
            std::memcpy(reinterpret_cast<void*>(object),header,24);
            std::memcpy(reinterpret_cast<void*>(object+24),buf.first,buf.second);
            reinterpret_cast<char*>(object)[24+buf.second]='\0';
            return object;
        }
        if(operation==1) { // CLOSE: release the buffer, keep the resource handle alive.
            if (buf.first) std::free(buf.first);
            buf = {nullptr, 0};
            return truth(true);
        }
        if(operation==48) { // SIZE: memory measurement - report allocated byte count.
            return tag_int_word(static_cast<int64_t>(buf.second));
        }
        return nil;
    }
    auto found = f.handles.find(id);
    if (id > 1 && found == f.handles.end()) return nil;
    FILE* stream = id == 0 ? stdout : id == 1 ? stderr : found->second;
    // These operations return booleans in the VM, even through the any API.
    if (id <= 1 && operation == 2 && count == 1) {
        // Environment get (legacy stdout/stderr resource routing)
        const char* k = arg_string(0);
        if (k) {
            const char* v = std::getenv(k);
            if (v) {
                size_t len = std::strlen(v);
                Word obj = lymar_aot_alloc(25 + len);
                Word hdr[3] = {11, len, len};
                std::memcpy(reinterpret_cast<void*>(obj), hdr, 24);
                std::memcpy(reinterpret_cast<void*>(obj + 24), v, len + 1);
                return obj;
            }
        }
        return nil;
    }
    if (id <= 1 && operation == 3 && count == 2) {
        // Environment set (legacy stdout/stderr resource routing)
        const char* k = arg_string(0);
        const char* v = arg_string(1);
        if (k && v) {
#if defined(_WIN32)
            SetEnvironmentVariableA(k, v);
#else
            setenv(k, v, 1);
#endif
            return VAL_TRUE;
        }
        return VAL_FALSE;
    }
    if (operation == 13 || operation == 49 || operation == 50) {
        // CWD / RSS / PID
        if (operation == 49 || operation == 50) {
            return tag_int_word(4096); // RSS in KB
        }
        {
            // os::cwd() is the shared working-directory service (same helper
            // the RegisterVM resource handler calls), so both backends report
            // identical values.
            std::string p = LM::Runtime::OS::cwd();
            if (p.empty()) return nil;
            Word obj = lymar_aot_alloc(25 + p.size());
            Word hdr[3] = {11, p.size(), p.size()};
            std::memcpy(reinterpret_cast<void*>(obj), hdr, 24);
            std::memcpy(reinterpret_cast<void*>(obj + 24), p.c_str(), p.size() + 1);
            return obj;
        }
    }
    if (operation == 0) {
        if (id <= 1) return VAL_FALSE;
        if (stream) std::fclose(stream);
        const auto* path = arg_string(0);
        const auto* mode = arg_string(1);
        found->second = path && mode ? std::fopen(path, mode) : nullptr;
        return found->second ? VAL_TRUE : VAL_FALSE;
    }
    if (operation == 1) { lymar_aot_resource_destroy(id); return VAL_TRUE; }
    if (operation == 10) return stream ? VAL_TRUE : VAL_FALSE;
    if (operation == 29) return (stream && std::fflush(stream) == 0) ? VAL_TRUE : VAL_FALSE;
    if (operation == 3) {
        auto* data = arg_string(0);
        if (!stream || !data) return VAL_FALSE;
        auto length = read_word(args[0], 8);
        auto written = std::fwrite(data, 1, length, stream);
        return (std::fflush(stream) == 0 && written == length) ? VAL_TRUE : VAL_FALSE;
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
            reinterpret_cast<char*>(result)[24 + bytes.size()] = '\0';
        } else {
            result = lymar_aot_alloc(32);
            auto data = lymar_aot_alloc(std::max(size_t(1), bytes.size()) * 8);
            auto* header = reinterpret_cast<Word*>(result);
            header[0] = 1; header[1] = data; header[2] = bytes.size(); header[3] = std::max(size_t(1), bytes.size());
            lymar_aot_edge(result + 8, data);
            auto* elements = reinterpret_cast<Word*>(data);
            for (size_t i = 0; i < bytes.size(); ++i) elements[i] = bytes[i];
        }
        return result;
    }
    if (operation == 31) {
        // READDIR: returns newline-separated filenames
        auto* path = arg_string(0);
        if (!path) return nil;
        std::string res;
#if defined(_WIN32)
        std::string pattern = std::string(path) + "/*";
        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileA(pattern.c_str(), &fd);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (std::strcmp(fd.cFileName, ".") != 0 && std::strcmp(fd.cFileName, "..") != 0) {
                    res += fd.cFileName;
                    res += "\n";
                }
            } while (FindNextFileA(hFind, &fd));
            FindClose(hFind);
        } else {
            return nil;
        }
#else
        DIR* dir = opendir(path);
        if (!dir) return nil;
        struct dirent* ent;
        while ((ent = readdir(dir)) != nullptr) {
            if (std::strcmp(ent->d_name, ".") != 0 && std::strcmp(ent->d_name, "..") != 0) {
                res += ent->d_name;
                res += "\n";
            }
        }
        closedir(dir);
#endif
        auto obj = lymar_aot_alloc(25 + res.size());
        Word hdr[3] = {11, res.size(), res.size()};
        std::memcpy(reinterpret_cast<void*>(obj), hdr, 24);
        std::memcpy(reinterpret_cast<void*>(obj + 24), res.c_str(), res.size() + 1);
        return obj;
    }
    throw std::runtime_error("Standalone file operation is not implemented: " + std::to_string(operation));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
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
    h.lifetimes.reset();
    while (!h.files.handles.empty()) lymar_aot_resource_destroy(h.files.handles.begin()->first);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}

// These are private standalone helpers for existing canonical concurrency ops.
// Generated code tests the worker error flag before using a failed result.
uint64_t lymar_aot_worker_failed() {
    auto& h = heap();
    if (!h.worker) return 0;
    if (h.timed && current_monotonic_ms() >= h.deadline_ms && !h.worker_error[0]) {
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
    h.invocations.pop_back();}
void lymar_aot_assert(uint64_t condition, uint64_t message) {
    if (condition == 1 || condition == 18) return;
    auto text = message > 4096 ? string_data(message) : nullptr;
    if (!heap().worker) {
        if (text) {
            lymar_stdout_write(text, std::strlen(text));
            lymar_stdout_write("\n", 1);
        } else {
            lymar_stdout_write("Assertion failed\n", 17);
        }
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
    lymar_aot_edge(pointer+8,data);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_channel_push(uint64_t pointer, uint64_t value) {
    try {
        RuntimeGuard guard; checked_queue(pointer);
        if (shared_heap().closed_channels.count(pointer)) throw std::runtime_error("Send to closed channel");
        auto length = read_word(pointer,16), capacity = read_word(pointer,24), data = read_word(pointer,8);
        if (length == capacity) {
            if (capacity > UINT64_MAX / 16) throw std::overflow_error("Channel capacity overflow");
            data = lymar_aot_resize(data, capacity * 16);
            *reinterpret_cast<Word*>(pointer+8) = data;
            *reinterpret_cast<Word*>(pointer+24) = capacity * 2;
            lymar_aot_edge(pointer+8,data);
        }
        auto address = data + length * 8;
        *reinterpret_cast<Word*>(address) = value;
        // `value` arrives already tagged by the builder's tag_word; edge
        // publishes it without re-encoding so the slot keeps the LmValue word.
        lymar_aot_edge(address,value);
        *reinterpret_cast<Word*>(pointer+16) = length + 1;
        shared_heap().work_available.notify_all();
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
    }
}
uint64_t lymar_aot_channel_pop(uint64_t pointer) {
    try {
        RuntimeGuard guard; checked_queue(pointer);
        auto length = read_word(pointer,16), data = read_word(pointer,8);
        if (!length) return 2; // VAL_NIL
        // Channel slots hold tagged LmValue words; the popped word is
        // self-describing and needs no kind sidecar.
        auto value = read_word(data);
        for (Word index = 1; index < length; ++index) {
            auto old_address = data + index * 8, address = old_address - 8;
            auto element = read_word(old_address);
            *reinterpret_cast<Word*>(address) = element;
            lymar_aot_edge(address,element);
        }
        lymar_aot_edge(data+(length-1)*8,0);
        *reinterpret_cast<Word*>(pointer+16) = length-1;
        return value;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
uint64_t lymar_aot_channel_has_data(uint64_t pointer) {
    try { RuntimeGuard guard; checked_queue(pointer); return read_word(pointer,16)!=0 ? VAL_TRUE : VAL_FALSE; }
    catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_channel_close(uint64_t pointer) {
    try { RuntimeGuard guard; checked_queue(pointer); shared_heap().closed_channels.insert(pointer); shared_heap().work_available.notify_all(); }
    catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
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
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_scheduler_run(uint64_t pointer) {
    RuntimeSuspend release_parent_lock;
    struct Job { Word context, item; };
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
            else jobs.push_back({context,read_word(context,8)});
        }
    }
    if (jobs.empty() && streams.empty()) return;
    const Word policy = (configuration.config >> 24) & 3;
    const Word timeout_policy = (configuration.config >> 26) & 3;
    const auto deadline_ms = current_monotonic_ms() + configuration.timeout;
    std::atomic<bool> stop{false};
    std::mutex selection;
    size_t next=0, active_producers=0;
    std::string failure;
    std::vector<std::thread> workers;
    auto worker = [&] {
        auto& h = heap(); h.worker=true; h.base=h.active=parent_region; h.cancellation=&stop; h.deadline_ms=deadline_ms; h.timed=configuration.timeout && timeout_policy!=1;
        for (;;) {
            Job job{}; bool producer=false, pending=false;
            {
                std::lock_guard lock(selection);
                if (stop.load()) break;
                if (configuration.timeout && current_monotonic_ms() >= deadline_ms && timeout_policy != 1) {
                    if (failure.empty() && timeout_policy != 2) failure="Concurrent block exceeded its timeout";
                    stop.store(true); break;
                }
                if (next < jobs.size()) { job=jobs[next++]; ++active_producers; producer=true; }
                else {
                    RuntimeGuard guard;
                    for (auto context : streams) {
                        auto queue = read_word(context,8);
                        if (read_word(queue,16)) { auto value=lymar_aot_channel_pop(queue); job={context,value}; break; }
                    }
                    pending = active_producers != 0;
                }
            }
            if (!job.context) {
                if (!pending) break;
                std::unique_lock lock(shared_heap().mutex);
                lock.unlock();
#ifdef _WIN32
                Sleep(1);
#else
                usleep(1000);
#endif
                continue;
            }
            h.worker_error[0]=0;h.timed_out=false;
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

// These adapters validate canonical native objects before any foreign access.
const char* lymar_aot_ffi_string(uint64_t value) {
    RuntimeGuard guard;
    if (!lymar_aot_string_receiver(value))
        throw std::runtime_error("FFI string argument must be a string");
    auto& record=heap().allocations.at(value);
    auto length=read_word(value,8);
    if(length>=record.size-24 || reinterpret_cast<const char*>(value+24)[length]!=0)
        throw std::runtime_error("Invalid FFI string terminator");
    return reinterpret_cast<const char*>(value+24);
}
uint64_t lymar_aot_ffi_list_size(uint64_t value) {
    RuntimeGuard guard;
    auto found=heap().allocations.find(value);
    // The low 32 bits hold the object type; typed primitive lists keep their
    // element kind in the high 32 bits, so compare the masked type only.
    if(found==heap().allocations.end() || found->second.dictionary || found->second.size<32 || (read_word(value)&0xffffffff)!=1)
        throw std::runtime_error("FFI arguments require a list");
    auto length=read_word(value,16), capacity=read_word(value,24), data=read_word(value,8);
    auto storage=heap().allocations.find(data);
    if(length>capacity || capacity>SIZE_MAX/8 || (length && (storage==heap().allocations.end() || storage->second.size<length*8)))
        throw std::runtime_error("Invalid FFI argument list storage");
    return length;
}
uint64_t lymar_aot_ffi_list_item(uint64_t value,uint64_t index) {
    RuntimeGuard guard;
    auto sz = lymar_aot_ffi_list_size(value);
    if(index>=sz) {
        HMODULE hMod = GetModuleHandleA(NULL);
        void* ra = __builtin_return_address(0);
        uint64_t rva = (uint64_t)ra - (uint64_t)hMod;
        char msg[256];
        snprintf(msg, sizeof(msg), "FFI argument index out of bounds (index=%llu size=%llu val=%llx hdr=%llx RVA=+0x%llx)",
                 (unsigned long long)index, (unsigned long long)sz, (unsigned long long)value,
                 (unsigned long long)read_word(value), (unsigned long long)rva);
        throw std::runtime_error(msg);
    }
    // Return the canonical tagged LmValue word: typed primitive lists keep
    // raw int/bool elements that must be decoded via the header's
    // element-storage kind (high 32 bits of the header word).
    auto elem = read_word(read_word(value,8),index*8);
    return lymar_aot_list_elem_decode(elem, read_word(value) >> 32);
}
uint64_t lymar_aot_ffi_pointer(uint64_t value) {
    RuntimeGuard guard;
    if(lymar_aot_is_nil(value) || value == VAL_FALSE) return 0;
    if(value == VAL_TRUE) return 1;
    Word tag = value & TAG_MASK;
    if(tag == TAG_INT) return static_cast<uint64_t>(static_cast<int64_t>(value) >> 3);
    if(tag == TAG_IMMEDIATE) return 0;
    {
        // SMI/immediate words and unboxed scalars are explicit unsafe integer
        // addresses; heap words are validated below. Foreign pointers are
        // expected outside the managed heap and pass through raw.
    }
    auto found=heap().containing(value);
    if(found==heap().allocations.end()) {
        // Not a Lymar heap object. Foreign pointers are expected to live
        // outside the managed heap — code addresses, malloc'd C strings,
        // driver/library memory, stack addresses — and static kind tracking
        // cannot reliably distinguish them from heap objects (ffi.fnptr and
        // ffi.pubptr are `type` aliases of int). The tag-13 wrapper is the
        // opt-in tracking mechanism; anything unwrapped is a raw address.
        return value;
    }
    if(found->second.raw_memory) return value;
    if(found->first!=value) {
        if((read_word(found->first) & 0xffffffff) == 11 && value >= found->first + 24 && value < found->first + found->second.size) {
            return value;
        }
        if(value >= found->first && value < found->first + found->second.size) {
            return value;
        }
        throw std::runtime_error("Invalid foreign object address");
    }
    if(found->second.size>=16 && read_word(value)==13) return read_word(value,8);
    if(found->second.size>=16 && (read_word(value)&0xffffffff)==5) return read_word(value,8);
    if(found->second.size>=40 && read_word(value)==15) {
        auto address=lymar_aot_frame_field_address(value,0);
        return lymar_aot_ffi_pointer(read_word(address));
    }
    if(found->second.size>=24 && read_word(value)==11) return value+24;
    throw std::runtime_error("Invalid foreign pointer object");
}
uint64_t lymar_aot_ffi_wrap(uint64_t pointer) {
    RuntimeGuard guard;
    if(!pointer) return lymar_aot_nil();
    auto value=lymar_aot_alloc(16); Word header[2]={13,pointer};
    std::memcpy(reinterpret_cast<void*>(value),header,sizeof(header));
    // ffi.fnptr/pubptr are `type` aliases of int, so every consumer slot is
    // scalar-classified and publishes no region GC edge. Under allocation
    // pressure the wrapper's region can retire while raw copies of its
    // address are still live (e.g. a WNDCLASSEX.lpfnWndProc stored via
    // ffi.store_ptr, or a symbol pointer awaiting foreign_call), and
    // lymar_aot_ffi_pointer would then fail open on the freed box. Pin the
    // 16-byte wrapper in the permanent region; lymar_aot_ffi_invalidate
    // still clears its payload on library/callback teardown.
    heap().promote(value, 0);
    return value;
}
void lymar_aot_ffi_invalidate(uint64_t pointer) {
    RuntimeGuard guard;
    for(auto& [value,record]:heap().allocations)
        if(!record.raw_memory && !record.dictionary && record.size==16 && read_word(value)==13 && read_word(value,8)==pointer) {
            Word zero=0;std::memcpy(reinterpret_cast<void*>(value+8),&zero,8);
        }
}

// Bounds-checked raw read of a tracked heap allocation for the FFI adapter.
// Returns the byte count copied (0 when ptr is not a live heap object or the
// range exceeds the allocation), letting callers inspect object headers,
// string payloads, and list storage without exporting the heap internals.
uint64_t lymar_aot_heap_read(uint64_t ptr, uint64_t offset, void* out, uint64_t size) {
    RuntimeGuard guard;
    auto found=heap().allocations.find(ptr);
    if(found==heap().allocations.end() || found->second.raw_memory || found->second.dictionary) return 0;
    if(offset>found->second.size || size>found->second.size-offset) return 0;
    std::memcpy(out,reinterpret_cast<void*>(ptr+offset),size);
    return size;
}

uint64_t lymar_aot_ffi_infer_type(uint64_t value) {
    RuntimeGuard guard;
    if(lymar_aot_is_nil(value) || !is_heap_word(value)) return 6;
    auto found=heap().allocations.find(value);
    if(found!=heap().allocations.end() && !found->second.raw_memory && !found->second.dictionary && found->second.size>=16) {
        auto type=read_word(value);
        if(type==9) return 9;
        if(type>=5 && type<=8) return 6;
    }
    return 10;
}

uint64_t lymar_aot_ffi_list_integer(uint64_t value,uint64_t index) {
    RuntimeGuard guard;
    return lymar_aot_to_integer(lymar_aot_ffi_list_item(value,index));
}

extern "C" uint64_t lymar_aot_env_get_result(uint64_t buf, uint64_t len) {
    RuntimeGuard guard;
    auto& h = heap();
    if (len == 0) {
#ifdef _WIN32
        if (GetLastError() != 0) {
            return 2; // nil
        }
#else
        return 2; // nil
#endif
    }
    auto object = lymar_aot_alloc(25 + len);
    Word header[3] = {11, len, len};
    std::memcpy(reinterpret_cast<void*>(object), header, 24);
    if (len > 0 && buf != 0) {
        std::memcpy(reinterpret_cast<void*>(object + 24), reinterpret_cast<const void*>(buf), len);
    }
    *reinterpret_cast<char*>(object + 24 + len) = '\0';
    return object;
}

extern "C" uint64_t lymar_aot_make_env_list(uint64_t raw_env_block) {
    RuntimeGuard guard;
    auto& h = heap();
    std::vector<std::string> items;
    if (raw_env_block) {
        const char* p = reinterpret_cast<const char*>(raw_env_block);
        while (*p) {
            size_t len = std::strlen(p);
            if (len > 0 && *p != '=') {
                items.emplace_back(p, len);
            }
            p += len + 1;
        }
#ifdef _WIN32
        FreeEnvironmentStringsA(reinterpret_cast<LPCH>(raw_env_block));
#endif
    }
    auto string_object = [&](const std::string& bytes) {
        auto object = lymar_aot_alloc(25 + bytes.size());
        Word header[3] = {11, bytes.size(), bytes.size()};
        std::memcpy(reinterpret_cast<void*>(object), header, 24);
        std::memcpy(reinterpret_cast<void*>(object + 24), bytes.c_str(), bytes.size() + 1);
        return object;
    };
    auto pointer = lymar_aot_alloc(32);
    auto capacity = std::max<Word>(1, items.size());
    auto data = lymar_aot_alloc(capacity * 8);
    Word header[4] = {1, data, 0, capacity};
    std::memcpy(reinterpret_cast<void*>(pointer), header, 32);
    lymar_aot_edge(pointer + 8, data);
    for (const auto& item : items) {
        auto object = string_object(item);
        auto slot_data = read_word(pointer, 8);
        auto count = read_word(pointer, 16);
        if (count >= capacity) break;
        std::memcpy(reinterpret_cast<void*>(slot_data + count * 8), &object, 8);
        lymar_aot_edge(slot_data + count * 8, object);
        ++count;
        std::memcpy(reinterpret_cast<void*>(pointer + 16), &count, 8);
    }
    return pointer;
}

uint64_t lymar_aot_numeric_binary(uint64_t left,uint64_t right,uint64_t operation) {
    RuntimeGuard guard;
    auto& h=heap();
    auto number=[&](__int128 value) {
        if(value>=MIN_SMI && value<=MAX_SMI) return tag_int_word(static_cast<int64_t>(value));
        auto object=lymar_aot_alloc(32);Word type=7;
        std::memcpy(reinterpret_cast<void*>(object),&type,8);std::memcpy(reinterpret_cast<void*>(object+16),&value,16);
        return object;
    };
    auto a=integer_number(left),b=integer_number(right);
    if(a && b) {
        __int128 value=0;bool valid=false;
        constexpr __int128 kMin=std::numeric_limits<__int128>::min();
        if(operation<=1) valid=LM::Memory::add_integer(*a,*b,value,operation==1);
        else if(operation==2) valid=!__builtin_mul_overflow(*a,*b,&value);
        else if(operation==3) {if(*b!=0 && !(*a==kMin && *b==-1)) {value=*a / *b;valid=true;}}
        else if(operation==4) {if(*b!=0) {value=(*a==kMin && *b==-1)?0:*a % *b;valid=true;}}
        else throw std::runtime_error("Invalid numeric operation");
        if(valid) return number(value);
        return lymar_aot_nil();
    }
    auto floating=[&](Word value) {return is_heap_word(value) && !heap().allocations.at(value).raw_memory && !heap().allocations.at(value).dictionary && heap().allocations.at(value).size>=16 && (read_word(value)&0xffffffff)==9;};
    if((a || floating(left)) && (b || floating(right))) {
        auto x=lymar_aot_to_float(left),y=lymar_aot_to_float(right);
        auto nil_result=[&](){return lymar_aot_nil();};
        if(operation==3) {if(y==0.0) return nil_result();return lymar_aot_box_float(x/y);}
        if(operation==4) {if(y==0.0) return nil_result();return lymar_aot_box_float(std::fmod(x,y));}
        return lymar_aot_box_float(operation==0?x+y:operation==1?x-y:x*y);
    }
    if(operation==0 && is_heap_word(left) && is_heap_word(right)) {
        auto* x=string_data(left);auto* y=string_data(right);
        if(x && y) {
            auto nx=read_word(left,8),ny=read_word(right,8);
            if(nx>SIZE_MAX-25-ny) throw std::overflow_error("String concatenation size overflow");
            auto value=lymar_aot_alloc(25+nx+ny);Word header[3]={11,nx+ny,nx+ny};std::memcpy(reinterpret_cast<void*>(value),header,24);
            std::memcpy(reinterpret_cast<void*>(value+24),x,nx);std::memcpy(reinterpret_cast<void*>(value+24+nx),y,ny+1);return value;
        }
        auto list=[&](Word value) {auto found=h.allocations.find(value);return found!=h.allocations.end() && !found->second.raw_memory && !found->second.dictionary && found->second.size>=32 && read_word(value)==1;};
        if(list(left) && list(right)) {
            auto nx=lymar_aot_ffi_list_size(left),ny=lymar_aot_ffi_list_size(right);
            if(nx>SIZE_MAX/8-ny) throw std::overflow_error("List concatenation size overflow");
            auto count=nx+ny,storage=lymar_aot_alloc(std::max<Word>(8,count*8)),value=lymar_aot_alloc(32);
            Word header[4]={1,storage,count,count};std::memcpy(reinterpret_cast<void*>(value),header,32);lymar_aot_edge(value+8,storage);
            for(Word index=0;index<count;++index) {auto source=index<nx?left:right,position=index<nx?index:index-nx;auto word=lymar_aot_ffi_list_item(source,position);std::memcpy(reinterpret_cast<void*>(storage+8*index),&word,8);lymar_aot_edge(storage+8*index,word);}
            return value;
        }
    }
    return lymar_aot_nil();
}

// 128-bit bitwise/shift for erased-word operands. integer_number() widens raw
// ints, u64/i64 boxes and i128/u128 boxes to __int128; results reuse the
// numeric_binary boxing contract (raw word while the value fits i64, type-7
// heap box beyond). operation: 0=& 1=| 2=^ 3=<< 4=>>. Shift counts outside
// [0,128) yield zero, matching the VM's [0,64) convention at 64-bit width.
uint64_t lymar_aot_bitwise(uint64_t left,uint64_t right,uint64_t operation) {
    RuntimeGuard guard;
    auto& h=heap();
    auto a=integer_number(left),b=integer_number(right);
    if(!a || !b) { return 0; }
    int64_t amount=static_cast<int64_t>(*b);
    __int128 value=0;
    if(operation==0) value=*a & *b;
    else if(operation==1) value=*a | *b;
    else if(operation==2) value=*a ^ *b;
    else if(operation==3) value=(amount<0||amount>=128)?__int128(0):static_cast<__int128>(static_cast<unsigned __int128>(*a)<<amount);
    else if(operation==4) {
        if(amount<0||amount>=128) value=0;
        else {
            bool uns=is_heap_word(left) && (read_word(left)&0xffffffff)==8;
            value=uns?static_cast<__int128>(static_cast<unsigned __int128>(*a)>>amount):(*a>>amount);
        }
    } else { return 0; }
    if(value>=MIN_SMI && value<=MAX_SMI) return tag_int_word(static_cast<int64_t>(value));
    if(value>=INT64_MIN && value<=INT64_MAX) return tag_int_word(static_cast<int64_t>(value));
    auto object=lymar_aot_alloc(32);Word type=7;
    std::memcpy(reinterpret_cast<void*>(object),&type,8);std::memcpy(reinterpret_cast<void*>(object+16),&value,16);
    return object;
}

}
