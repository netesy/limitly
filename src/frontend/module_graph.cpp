#include "module_graph.hh"

namespace LM {
namespace Frontend {

ModuleGraph::ModuleGraph(const std::unordered_map<std::string, std::shared_ptr<Module>>& modules) {
    // Build adjacency list: each module points to its dependencies
    for (const auto& [name, mod] : modules) {
        if (!mod) continue;
        adj_[name] = mod->dependencies;
    }
}

bool ModuleGraph::dfs(const std::string& node, std::unordered_map<std::string, int>& state) const {
    // 0 = unvisited, 1 = visiting, 2 = visited
    if (state[node] == 1) return true;   // cycle detected
    if (state[node] == 2) return false;  // already processed
    state[node] = 1;
    auto it = adj_.find(node);
    if (it != adj_.end()) {
        for (const auto& dep : it->second) {
            if (dfs(dep, state)) return true;
        }
    }
    state[node] = 2;
    return false;
}

bool ModuleGraph::has_cycle() const {
    std::unordered_map<std::string, int> state; // default 0
    for (const auto& kv : adj_) {
        if (state[kv.first] == 0) {
            if (dfs(kv.first, state)) return true;
        }
    }
    return false;
}

std::vector<std::string> ModuleGraph::topological_order() const {
    // Kahn's algorithm (based on indegree)
    std::unordered_map<std::string, int> indegree;
    for (const auto& kv : adj_) {
        indegree[kv.first]; // ensure entry
    }
    for (const auto& kv : adj_) {
        for (const auto& dep : kv.second) {
            indegree[dep]++;
        }
    }
    std::vector<std::string> order;
    std::vector<std::string> zero;
    for (const auto& kv : indegree) {
        if (kv.second == 0) zero.push_back(kv.first);
    }
    while (!zero.empty()) {
        std::string n = zero.back();
        zero.pop_back();
        order.push_back(n);
        auto it = adj_.find(n);
        if (it != adj_.end()) {
            for (const auto& dep : it->second) {
                if (--indegree[dep] == 0) {
                    zero.push_back(dep);
                }
            }
        }
    }
    // If order size != number of nodes, a cycle exists; return empty vector
    if (order.size() != adj_.size()) {
        return {};
    }
    return order;
}

} // namespace Frontend
} // namespace LM
