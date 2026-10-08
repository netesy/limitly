// Private standalone-AOT ownership helpers. No public object/header fields.
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
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
struct Heap {
    struct Invocation { std::vector<Word> args; std::unordered_set<Word> slots; };
    Word active = 0, next = 1;
    std::map<Word, Allocation> allocations;
    std::unordered_map<Word, Region> regions{{0, {0, 0, 0, {}}}};
    std::unordered_map<Word, bool> shadow;
    std::vector<Invocation> invocations;
    std::vector<Word> pending_args;
    Word return_pointer = 0;

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
}

extern "C" {
uint64_t lymar_aot_call_enter() {
    auto& h = heap();
    h.invocations.push_back({std::move(h.pending_args), {}});
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
[[noreturn]] void lymar_aot_exit(uint64_t status) { std::exit(static_cast<int>(status)); }
uint64_t lymar_aot_live_allocations() { return heap().allocations.size(); }
void lymar_aot_reset() {
    auto& h = heap();
    if (h.active || !h.invocations.empty()) throw std::runtime_error("AOT reset with active invocation");
    h.cleanup(0);
    h.shadow.clear();
}
}
