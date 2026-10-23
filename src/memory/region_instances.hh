#pragma once
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace LM::Memory {
// Storage is reused by depth; externally visible identities are never reused.
// Region contents remain backend-specific and retirement stays stack ordered.
template<class Region> struct RegionInstances {
    std::vector<std::pair<uint64_t, Region>> entries;

    RegionInstances() = default;
    explicit RegionInstances(Region root) {
        entries.emplace_back(0, std::move(root));
    }
    void clear() {
        entries.clear();
        last_id = UINT64_MAX;
        last_index = 0;
    }
    void emplace(uint64_t id, Region region) {
        if (!entries.empty() && id <= entries.back().first)
            throw std::runtime_error("Non-monotonic region identity");
        entries.emplace_back(id, std::move(region));
        last_id = UINT64_MAX;
        last_index = 0;
    }
    mutable uint64_t last_id = UINT64_MAX;
    mutable size_t last_index = 0;

    const Region& at(uint64_t id) const {
        if (last_id == id && last_index < entries.size() && entries[last_index].first == id) {
            return entries[last_index].second;
        }
        if (!entries.empty() && entries.back().first == id) {
            last_id = id;
            last_index = entries.size() - 1;
            return entries.back().second;
        }
        if (entries.size() <= 16) {
            for (size_t i = entries.size(); i > 0; --i) {
                size_t idx = i - 1;
                if (entries[idx].first == id) {
                    last_id = id;
                    last_index = idx;
                    return entries[idx].second;
                }
            }
        } else {
            auto found = std::lower_bound(entries.begin(), entries.end(), id,
                [](const auto& entry, uint64_t key) { return entry.first < key; });
            if (found != entries.end() && found->first == id) {
                size_t idx = std::distance(entries.begin(), found);
                last_id = id;
                last_index = idx;
                return found->second;
            }
        }
        throw std::out_of_range("Inactive region identity");
    }
    Region& at(uint64_t id) {
        return const_cast<Region&>(static_cast<const RegionInstances&>(*this).at(id));
    }
    void erase(uint64_t id) {
        if (entries.empty() || entries.back().first != id)
            throw std::runtime_error("Non-stack region retirement");
        if (last_id == id) {
            last_id = UINT64_MAX;
            last_index = 0;
        }
        entries.pop_back();
    }
};
}
