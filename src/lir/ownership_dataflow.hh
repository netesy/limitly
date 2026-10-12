#pragma once

#include "../memory/ownership.hh"
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace LM::LIR::Detail {

struct OwnershipBinding {
    unsigned availability = 1; // Uninitialized / live / consumed path bits.
    bool stale = false;
    std::set<Memory::Identity> aliases;
    bool operator==(const OwnershipBinding&) const = default;
};

using OwnershipState = std::map<Memory::Identity, OwnershipBinding>;

// Join another reachable predecessor into an existing reachable input. An
// absent binding is uninitialized, not unreachable: both one-sided cases must
// retain that path bit. The first predecessor is copied by the worklist caller.
inline bool join_ownership_state(OwnershipState& input, const OwnershipState& incoming) {
    bool changed = false;
    auto left = input.begin();
    auto right = incoming.begin();
    while (left != input.end() || right != incoming.end()) {
        if (right == incoming.end() ||
            (left != input.end() && left->first < right->first)) {
            const auto availability = left->second.availability | 1u;
            changed |= availability != left->second.availability;
            left->second.availability = availability;
            ++left;
        } else if (left == input.end() || right->first < left->first) {
            auto binding = right->second;
            binding.availability |= 1u;
            input.emplace_hint(left, right->first, std::move(binding));
            changed = true;
            ++right;
        } else {
            auto& binding = left->second;
            const auto& other = right->second;
            const auto availability = binding.availability | other.availability;
            const bool stale = binding.stale || other.stale;
            changed |= availability != binding.availability || stale != binding.stale;
            binding.availability = availability;
            binding.stale = stale;
            const auto aliases = binding.aliases.size();
            binding.aliases.insert(other.aliases.begin(), other.aliases.end());
            changed |= aliases != binding.aliases.size();
            ++left;
            ++right;
        }
    }
    return changed;
}

// Presence is independent of availability: a newly encountered uninitialized
// binding still changes the solver lattice. Alias sets are sorted local indices.
class IndexedOwnershipState {
    std::vector<uint8_t> availability, stale, present;
    std::vector<std::vector<size_t>> aliases;
    void touch(size_t id) { present[id] = 1; }
    void invalidate(size_t id) {
        for (size_t i = 0; i < aliases.size(); ++i)
            if (std::binary_search(aliases[i].begin(), aliases[i].end(), id)) stale[i] = 1;
    }
    static void insert(std::vector<size_t>& set, size_t id) {
        auto at = std::lower_bound(set.begin(), set.end(), id);
        if (at == set.end() || *at != id) set.insert(at, id);
    }
public:
    explicit IndexedOwnershipState(size_t count)
        : availability(count, 1), stale(count), present(count), aliases(count) {}
    bool valid(size_t id) { touch(id); return availability[id] == 2 && !stale[id]; }
    void live(size_t id) { touch(id); availability[id] = 2; }
    void consume(size_t id) { touch(id); availability[id] = 4; invalidate(id); }
    void initialize(size_t id) { touch(id); if (availability[id] == 1) availability[id] = 2; }
    void define(size_t id) { touch(id); invalidate(id); availability[id] = 2; stale[id] = 0; aliases[id].clear(); }
    void alias(size_t id, size_t origin) {
        touch(id); touch(origin);
        insert(aliases[id], origin);
        // Self aliases are legal; insertion above cannot invalidate this traversal.
        if (id != origin) for (auto source : aliases[origin]) insert(aliases[id], source);
        stale[id] |= availability[origin] != 2 || stale[origin];
    }
    bool join(const IndexedOwnershipState& other) {
        bool changed = false;
        for (size_t id = 0; id < present.size(); ++id) {
            if (!present[id] && !other.present[id]) continue;
            const auto bits = availability[id] | other.availability[id];
            changed |= !present[id] || bits != availability[id] || (other.stale[id] && !stale[id]);
            present[id] = 1; availability[id] = bits; stale[id] |= other.stale[id];
            const auto size = aliases[id].size();
            if (this != &other) for (auto source : other.aliases[id]) insert(aliases[id], source);
            changed |= size != aliases[id].size();
        }
        return changed;
    }
    void set_binding(size_t id, const OwnershipBinding& value) {
        touch(id); availability[id] = value.availability; stale[id] = value.stale;
        aliases[id].assign(value.aliases.begin(), value.aliases.end());
    }
    OwnershipBinding binding(size_t id) const {
        return {availability[id], bool(stale[id]), {aliases[id].begin(), aliases[id].end()}};
    }
    bool contains(size_t id) const { return present[id]; }
};

} // namespace LM::LIR::Detail
