// Private standalone-AOT ownership helpers. No public object/header fields.
#include "memory.hh"
#include "region_instances.hh"
#include "reference_flags.hh"
#include "aot_value_kind.hh"
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
struct Heap {
    LM::Memory::DefaultAllocator allocator;
    LM::Memory::LifetimeRegistry lifetimes;
    struct Invocation {
        std::vector<Word> args;
        std::unordered_set<Word> slots;
        std::vector<std::pair<Word, Word>> staged_params;
    };
    Word active = 0, next = 1;
    std::map<Word, Allocation> allocations;
    LM::Memory::RegionInstances<Region> regions{Region{0, 0, 0, {}}};
    std::map<Word, Word> shadow;
    std::vector<Invocation> invocations;
    std::vector<Word> pending_args;
    Word return_pointer = 0;
    Files files;

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
        if (callback) callback(pointer);
    }
    void release(Word pointer) {
        auto found = allocations.find(pointer);
        if (found == allocations.end()) throw std::runtime_error("AOT free of unowned allocation");
        regions.at(found->second.owner).members.erase(pointer);
        forget_kinds(pointer, found->second.size);
        lifetimes.revoke(pointer);
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
        lifetimes.end_region(region);
        while (!regions.at(region).members.empty()) release(*regions.at(region).members.begin());
    }
    ~Heap() {
        try {
            while (active) {
                auto parent = regions.at(active).parent;
                cleanup(active);
                regions.erase(active);
                active = parent;
            }
            cleanup(0);
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
}

extern "C" {
// Frame operations require a live, correctly shaped receiver before addressing
// its fields. This is backend-private layout validation, not frontend inference.
uint64_t lymar_aot_frame_field_address(uint64_t pointer, uint64_t index) {
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
}
uint64_t lymar_aot_ref_create(uint64_t pointer, uint64_t writable) {
    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    h.return_pointer = 0;
    if ((pointer == 0 || pointer == 2) && (writable & LM::Memory::ReferenceNullable)) return 0;
    if (!h.allocations.count(pointer)) throw std::runtime_error("AOT borrow of unowned object");
    h.lifetimes.adopt(pointer);
    h.return_pointer = 0;
    return h.lifetimes.borrow(pointer, (writable & LM::Memory::ReferenceWritable) != 0, h.active);
}
// Provenance distinguishes actual nil/pointers from raw scalar words that
// happen to equal the nil representation (notably integers zero and two).
uint64_t lymar_aot_nil() { return 2; }
uint64_t lymar_aot_is_nil(uint64_t value, uint64_t is_pointer) {
    return is_pointer == object_kind && (value == 0 || value == 2);
}
uint64_t lymar_aot_is_object(uint64_t value, uint64_t is_pointer) {
    return is_pointer == object_kind && value != 0 && value != 2;
}
uint64_t lymar_aot_boolean(uint64_t value) { return value; }
uint64_t lymar_aot_is_print_object(uint64_t value, uint64_t kind) {
    return lymar_aot_is_object(value, kind) && (read_word(value) & 0xffffffff) != 9;
}
double lymar_aot_to_float(uint64_t value, uint64_t kind) {
    if (!kind) return static_cast<double>(static_cast<int64_t>(value));
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0.0;
    if ((read_word(value) & 0xffffffff) == 9) {
        double number;
        std::memcpy(&number, reinterpret_cast<void*>(value + 8), sizeof(number));
        return number;
    }
    if (auto* text = string_data(value)) { try { return std::stod(text); } catch (...) {} }
    return 0.0;
}
uint64_t lymar_aot_to_integer(uint64_t value, uint64_t kind) {
    if (!kind) return value;
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0;
    if (auto* text = string_data(value)) {
        try { return static_cast<uint64_t>(std::stoll(text)); }
        catch (...) { return static_cast<unsigned char>(text[0]); }
    }
    return static_cast<uint64_t>(static_cast<int64_t>(lymar_aot_to_float(value, kind)));
}
uint64_t lymar_aot_to_boolean(uint64_t value, uint64_t kind) {
    if (lymar_aot_is_nil(value, kind)) return 0;
    if (kind != object_kind) return value != 0;
    if ((read_word(value) & 0xffffffff) == 9) return lymar_aot_to_float(value, kind) != 0.0;
    return 1;
}
void lymar_aot_print_integer(uint64_t value, uint64_t kind) {
    char text[64];
    const char* output = text;
    size_t length;
    if (lymar_aot_is_nil(value, kind)) { output = "nil"; length = 3; }
    else if (kind == boolean_kind) { output = value ? "true" : "false"; length = value ? 4 : 5; }
    else if (kind == object_kind && (read_word(value) & 0xffffffff) == 9)
        length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", lymar_aot_to_float(value, kind)));
    else length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value)));
    std::fwrite(output, 1, length, stdout);
    std::fflush(stdout);
}
void lymar_aot_print_float(double value) {
    char text[64];
    const auto length = std::snprintf(text, sizeof(text), "%.6g", value);
    std::fwrite(text, 1, static_cast<size_t>(length), stdout);
    std::fflush(stdout);
}
uint64_t lymar_aot_value_equal(uint64_t left, uint64_t right, uint64_t left_kind, uint64_t right_kind) {
    const bool left_nil = lymar_aot_is_nil(left, left_kind), right_nil = lymar_aot_is_nil(right, right_kind);
    if (left_nil || right_nil) return left_nil && right_nil;
    if (left_kind == boolean_kind || right_kind == boolean_kind)
        return left_kind == right_kind && left == right;
    if (left == right && left_kind == right_kind) return 1;
    const Word left_type = left_kind == object_kind ? read_word(left) & 0xffffffff : UINT64_MAX;
    const Word right_type = right_kind == object_kind ? read_word(right) & 0xffffffff : UINT64_MAX;
    if ((!left_kind || left_type == 9) && (!right_kind || right_type == 9))
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
}
uint64_t lymar_aot_ref_create_checked(uint64_t pointer, uint64_t mode, uint64_t is_pointer) {
    if (is_pointer != object_kind) throw std::runtime_error("Borrow requires a managed object");
    return lymar_aot_ref_create(pointer, mode);
}
uint64_t lymar_aot_ref_resolve(uint64_t token, uint64_t writable) {
    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    h.return_pointer = 1;
    if (!token && (writable & LM::Memory::ReferenceNullable)) return 2;
    return h.lifetimes.resolve(token, (writable & LM::Memory::ReferenceWritable) != 0);
}
uint64_t lymar_aot_ref_move(uint64_t token, uint64_t lexical, uint64_t caller) {
    if (lexical & ~LM::Memory::ReferenceMoveMask) throw std::runtime_error("Invalid AOT reference move mode");
    auto& h = heap();
    h.return_pointer = 0;
    if (!token && (lexical & LM::Memory::ReferenceMoveNullable)) return 0;
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
    return h.lifetimes.move_reference(token, target);
}
void lymar_aot_ref_release(uint64_t token) { heap().lifetimes.end_borrow(token); }
void lymar_aot_ref_release_nullable(uint64_t token) {
    if (token) lymar_aot_ref_release(token);
}
void lymar_aot_consume(uint64_t pointer) {
    auto& h = heap();
    if (!h.allocations.count(pointer)) throw std::runtime_error("AOT consume of unowned object");
    h.lifetimes.adopt(pointer);
    h.lifetimes.consume(pointer);
}

uint64_t lymar_aot_call_enter() {
    auto& h = heap();
    h.invocations.push_back({std::move(h.pending_args), {}, {}});
    h.pending_args.clear();
    return h.active;
}
void lymar_aot_arg_set(uint64_t index, uint64_t pointer) {
    auto& args = heap().pending_args;
    if (args.size() <= index) args.resize(index + 1);
    args[index] = pointer;
}
uint64_t lymar_aot_arg_kind(uint64_t index, uint64_t fallback) {
    auto& h = heap();
    return h.invocations.empty() || index >= h.invocations.back().args.size() ? fallback : h.invocations.back().args[index];
}
uint64_t lymar_aot_arg_get(uint64_t index) {
    auto& h = heap();
    return h.invocations.empty() || index >= h.invocations.back().args.size() ? 0 : h.invocations.back().args[index];
}
void lymar_aot_call_leave(uint64_t pointer) {
    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT invocation stack underflow");
    for (auto slot : h.invocations.back().slots) h.shadow.erase(slot);
    h.invocations.pop_back();
    h.return_pointer = pointer;
}
uint64_t lymar_aot_return_pointer() { return heap().return_pointer; }
void lymar_aot_param_push(uint64_t value, uint64_t is_pointer) {
    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT Param outside invocation");
    h.invocations.back().staged_params.emplace_back(value, is_pointer);
}
uint64_t lymar_aot_param_pop(uint64_t fallback, uint64_t is_pointer) {
    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT ConstructError outside invocation");
    auto& params = h.invocations.back().staged_params;
    h.return_pointer = is_pointer;
    if (params.empty()) return fallback;
    auto [value, pointer] = params.back();
    params.pop_back();
    h.return_pointer = pointer;
    return value;
}
uint64_t lymar_aot_slot_pointer(uint64_t address) {
    auto& flags = heap().shadow;
    auto found = flags.find(address);
    return found != flags.end() ? found->second : 0;
}
uint64_t lymar_aot_region_current() { return heap().active; }
void lymar_aot_region_enter(uint64_t lexical) {
    auto& h = heap();
    if (h.next == UINT64_MAX) throw std::overflow_error("AOT region identity exhausted");
    auto id = h.next++;
    h.regions.emplace(id, Region{h.active, lexical, h.regions.at(h.active).depth + 1, {}});
    h.active = id;
}
void lymar_aot_region_exit(uint64_t lexical) {
    auto& h = heap();
    if (!h.active || h.regions.at(h.active).lexical != lexical)
        throw std::runtime_error("AOT RegionExit mismatch");
    auto id = h.active;
    auto parent = h.regions.at(id).parent;
    h.cleanup(id);
    h.active = parent;
    h.regions.erase(id);
}
void lymar_aot_region_move(uint64_t value, uint64_t lexical, uint64_t caller, uint64_t is_pointer) {
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
}
uint64_t lymar_aot_alloc(uint64_t size) {
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
}
uint64_t lymar_aot_box_float(double number) {
    auto pointer = lymar_aot_alloc(16);
    heap().allocations.at(pointer).float_box = true;
    const Word header = 9; // Existing TYPE_FLOAT header and payload offsets.
    std::memcpy(reinterpret_cast<void*>(pointer), &header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 8), &number, sizeof(number));
    return pointer;
}
uint64_t lymar_aot_scalar_to_string(uint64_t value, uint64_t kind) {
    char text[64];
    const char* output = text;
    size_t length;
    if (lymar_aot_is_nil(value, kind)) { output = "nil"; length = 3; }
    else if (kind == boolean_kind) { output = value ? "true" : "false"; length = value ? 4 : 5; }
    else if (kind == object_kind && (read_word(value) & 0xffffffff) == 9)
        length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", lymar_aot_to_float(value, kind)));
    else length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value)));
    auto pointer = lymar_aot_alloc(24 + length + 1);
    Word header[] = {11, length, length};
    std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 24), output, length);
    return pointer;
}
// LoadConst strings are copied into the current region, just as the VM copies
// managed constants into its tracked heap. Static linker storage is never freed.
uint64_t lymar_aot_copy_constant(uint64_t source, uint64_t size) {
    auto pointer = lymar_aot_alloc(size);
    std::memcpy(reinterpret_cast<void*>(pointer), reinterpret_cast<const void*>(source), size);
    return pointer;
}
void lymar_aot_free(uint64_t pointer) { if (pointer) heap().release(pointer); }
void lymar_aot_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
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
}
// Raw access is explicitly unsafe in source. Preserve external/FFI addresses;
// use memcpy so valid byte-addressed unaligned accesses do not acquire C++ UB.
// Raw bytes do not transfer pointee ownership; managed stores publish edges separately.
uint64_t lymar_aot_channel_length(uint64_t value, uint64_t kind) {
    if (kind != object_kind || lymar_aot_is_nil(value, kind)) return 0;
    auto& h = heap();
    auto found = h.allocations.find(value);
    if (found == h.allocations.end() || found->second.size < 32 || (read_word(value) & 0xffffffff) != 1)
        return 0; // A non-queue task value is a single invocation, not an iterator.
    return read_word(value, 16);
}
static uint64_t raw_address(uint64_t value, uint64_t kind) {
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0;
    if (kind != 0 && kind != object_kind) throw std::runtime_error("Invalid raw pointer kind");
    return value;
}
uint64_t lymar_aot_memory_load_kind(uint64_t pointer, uint64_t element, uint64_t pointer_kind) {
    pointer = raw_address(pointer, pointer_kind);
    if (!pointer || element >= 8) return object_kind;
    return 0;
}
uint64_t lymar_aot_memory_load(uint64_t pointer, uint64_t element, uint64_t pointer_kind) {
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
    size = raw_integer_value(size, kind);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    auto pointer = lymar_aot_alloc(size);
    heap().allocations.at(pointer).raw_memory = true;
    return pointer;
}
void lymar_aot_raw_free(uint64_t pointer, uint64_t kind) {
    pointer = raw_address(pointer, kind);
    auto found = heap().allocations.find(pointer);
    if (found != heap().allocations.end() && found->second.raw_memory) heap().release(pointer);
}
void lymar_aot_memory_store(uint64_t pointer, uint64_t value, uint64_t element, uint64_t kind, uint64_t pointer_kind) {
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
}
void lymar_aot_global_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
    auto& h = heap();
    if (is_pointer) { h.shadow[address] = is_pointer; if (is_pointer == object_kind) h.promote(child, 0); }
    else h.shadow.erase(address);
}
void lymar_aot_copy(uint64_t destination, uint64_t source, uint64_t size) {
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
}
void lymar_aot_raw_copy(uint64_t destination, uint64_t source, uint64_t size) {
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
}
void lymar_aot_raw_fill(uint64_t destination, uint64_t value, uint64_t size) {
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
}
uint64_t lymar_aot_raw_compare(uint64_t left, uint64_t right, uint64_t size) {
    if (!left || !right || static_cast<int64_t>(size) <= 0) return 0;
    return static_cast<int64_t>(std::memcmp(reinterpret_cast<void*>(left), reinterpret_cast<void*>(right), size));
}
uint64_t lymar_aot_resize(uint64_t pointer, uint64_t size) {
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
}
uint64_t lymar_aot_raw_resize(uint64_t pointer, uint64_t size, uint64_t pointer_kind, uint64_t size_kind) {
    pointer = raw_address(pointer, pointer_kind);
    size = raw_integer_value(size, size_kind);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    if (!pointer) return lymar_aot_raw_alloc(size, 0);
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || !found->second.raw_memory) return lymar_aot_nil();
    if (!size) { heap().release(pointer); return lymar_aot_nil(); }
    return lymar_aot_resize(pointer, size);
}
void lymar_aot_raw_copy_checked(uint64_t destination, uint64_t source, uint64_t size,
                               uint64_t destination_kind, uint64_t source_kind, uint64_t size_kind) {
    lymar_aot_raw_copy(raw_address(destination, destination_kind), raw_address(source, source_kind), raw_integer_value(size, size_kind));
}
void lymar_aot_raw_fill_checked(uint64_t destination, uint64_t value, uint64_t size,
                               uint64_t destination_kind, uint64_t value_kind, uint64_t size_kind) {
    lymar_aot_raw_fill(raw_address(destination, destination_kind), raw_integer_value(value, value_kind), raw_integer_value(size, size_kind));
}
uint64_t lymar_aot_raw_compare_checked(uint64_t left, uint64_t right, uint64_t size,
                                     uint64_t left_kind, uint64_t right_kind, uint64_t size_kind) {
    return lymar_aot_raw_compare(raw_address(left, left_kind), raw_address(right, right_kind), raw_integer_value(size, size_kind));
}
void lymar_aot_set_finalizer(uint64_t pointer, void (*callback)(uint64_t)) {
    heap().allocations.at(pointer).finalizer = callback;
}
void lymar_aot_finalize(uint64_t pointer) { heap().finalize(pointer); }
uint64_t lymar_aot_resource_create(uint64_t type, uint64_t) {
    if (type == 9) return 0; // stdout
    if (type == 10) return 1; // stderr
    if (type != 0) throw std::runtime_error("Standalone resource type is not implemented: " + std::to_string(type));
    auto& f = files();
    auto id = f.next++;
    f.handles.emplace(id, nullptr);
    return id;
}
void lymar_aot_resource_destroy(uint64_t id) {
    auto& f = files();
    auto found = f.handles.find(id);
    if (found == f.handles.end()) return;
    if (found->second) std::fclose(found->second);
    f.handles.erase(found);
}
uint64_t lymar_aot_resource_call(uint64_t id, uint64_t operation, uint64_t count, uint64_t arguments) {
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
}
[[noreturn]] void lymar_aot_exit(uint64_t status) { std::exit(static_cast<int>(status)); }
uint64_t lymar_aot_live_allocations() { return heap().allocations.size(); }
void lymar_aot_reset() {
    auto& h = heap();
    if (h.active || !h.invocations.empty()) throw std::runtime_error("AOT reset with active invocation");
    h.cleanup(0);
    h.shadow.clear();
    h.lifetimes.reset();
    while (!h.files.handles.empty()) lymar_aot_resource_destroy(h.files.handles.begin()->first);
    h.pending_args.clear();
    h.return_pointer = 0;
}
}
