// Private standalone-AOT ownership helpers. No public object/header fields.
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
struct Allocation {
    size_t size;
    Word owner;
    std::unordered_map<size_t, Word> edges;
    void (*finalizer)(Word) = nullptr;
    bool finalized = false;
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
    struct Invocation {
        std::vector<Word> args;
        std::unordered_set<Word> slots;
        std::vector<std::pair<Word, Word>> staged_params;
    };
    Word active = 0, next = 1;
    std::map<Word, Allocation> allocations;
    std::unordered_map<Word, Region> regions{{0, {0, 0, 0, {}}}};
    std::unordered_map<Word, bool> shadow;
    std::vector<Invocation> invocations;
    std::vector<Word> pending_args;
    Word return_pointer = 0;
    Files files;

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
        for (auto [offset, child] : found->second.edges) shadow.erase(pointer + offset);
        allocations.erase(found);
        std::free(reinterpret_cast<void*>(pointer));
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
    return found != flags.end() && found->second;
}
uint64_t lymar_aot_region_current() { return heap().active; }
void lymar_aot_region_enter(uint64_t lexical) {
    auto& h = heap();
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
    if (is_pointer) h.promote(value, target);
}
uint64_t lymar_aot_alloc(uint64_t size) {
    if (size > SIZE_MAX) throw std::bad_alloc();
    auto pointer = reinterpret_cast<Word>(std::calloc(1, std::max(size, Word(1))));
    if (!pointer) throw std::bad_alloc();
    auto& h = heap();
    h.allocations.emplace(pointer, Allocation{static_cast<size_t>(std::max(size, Word(1))), h.active, {}});
    h.regions.at(h.active).members.insert(pointer);
    return pointer;
}
void lymar_aot_free(uint64_t pointer) { if (pointer) heap().release(pointer); }
void lymar_aot_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
    auto& h = heap();
    if (!is_pointer && !h.shadow.erase(address)) return;
    auto container = h.containing(address);
    if (is_pointer) h.shadow[address] = true;
    else h.shadow.erase(address);
    if (container == h.allocations.end()) {
        if (!h.invocations.empty()) h.invocations.back().slots.insert(address);
        return;
    }
    auto offset = address - container->first;
    container->second.edges.erase(offset);
    if (is_pointer && h.containing(child) != h.allocations.end()) {
        container->second.edges[offset] = child;
        h.promote(child, container->second.owner);
    }
}
void lymar_aot_global_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
    auto& h = heap();
    if (is_pointer) { h.shadow[address] = true; h.promote(child, 0); }
    else h.shadow.erase(address);
}
void lymar_aot_copy(uint64_t destination, uint64_t source, uint64_t size) {
    auto& h = heap();
    std::vector<std::pair<Word, Word>> edges;
    auto src = h.containing(source);
    if (src != h.allocations.end()) {
        auto start = source - src->first;
        for (auto [offset, child] : src->second.edges)
            if (offset >= start && offset - start < size) edges.emplace_back(destination + offset - start, child);
    }
    std::memmove(reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), size);
    auto dst = h.containing(destination);
    if (dst != h.allocations.end()) {
        auto start = destination - dst->first;
        std::erase_if(dst->second.edges, [&](auto edge) {
            if (edge.first >= start && edge.first - start < size) {
                h.shadow.erase(dst->first + edge.first);
                return true;
            }
            return false;
        });
    }
    for (auto [address, child] : edges) lymar_aot_edge(address, child, 1);
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
    lymar_aot_copy(replacement, pointer, std::min(size, Word(original.size)));
    lymar_aot_free(pointer);
    return replacement;
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
    h.return_pointer = 0;
    std::vector<Word> args;
    std::vector<bool> pointers;
    for (Word n = 0; n < count; ++n) {
        auto value = read_word(arguments, n * 8);
        bool pointer = h.shadow.count(arguments + n * 8);
        if (pointer && value > 4096 && (read_word(value) & 0xffffffff) == 1) {
            auto data = read_word(value, 8), size = read_word(value, 16);
            for (Word i = 0; i < size; ++i) {
                args.push_back(read_word(data, i * 8));
                pointers.push_back(h.shadow.count(data + i * 8));
            }
        } else if (value != nil) { args.push_back(value); pointers.push_back(pointer); }
    }
    auto arg_string = [&](size_t n) { return n < args.size() && pointers[n] ? string_data(args[n]) : nullptr; };
    auto& f = files();
    auto found = f.handles.find(id);
    if (id > 1 && found == f.handles.end()) return nil;
    FILE* stream = id == 0 ? stdout : id == 1 ? stderr : found->second;
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
    while (!h.files.handles.empty()) lymar_aot_resource_destroy(h.files.handles.begin()->first);
    h.pending_args.clear();
    h.return_pointer = 0;
}
}
