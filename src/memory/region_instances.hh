#pragma once
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace LM::Memory {
// Storage is reused by depth; externally visible identities are never reused.
// Region contents remain backend-specific and retirement stays stack ordered.
template<class Region> struct RegionInstances {
    std::vector<std::pair<uint64_t, Region>> entries;
    RegionInstances() = default;
    explicit RegionInstances(Region root) { entries.emplace_back(0, std::move(root)); }
    void clear() { entries.clear(); }
    void emplace(uint64_t id, Region region) {
        if (!entries.empty() && id <= entries.back().first)
            throw std::runtime_error("Non-monotonic region identity");
        entries.emplace_back(id, std::move(region));
    }
    const Region& at(uint64_t id) const {
        // Entry/exit and current-region allocation normally access the top.
        // Older active ancestors still require an identity lookup.
        if (!entries.empty() && entries.back().first == id) return entries.back().second;
        auto found = std::lower_bound(entries.begin(), entries.end(), id,
            [](const auto& entry, uint64_t key) { return entry.first < key; });
        if (found == entries.end() || found->first != id)
            throw std::out_of_range("Inactive region identity");
        return found->second;
    }
    Region& at(uint64_t id) {
        return const_cast<Region&>(static_cast<const RegionInstances&>(*this).at(id));
    }
    void erase(uint64_t id) {
        if (entries.empty() || entries.back().first != id)
            throw std::runtime_error("Non-stack region retirement");
        entries.pop_back();
    }
};
}
