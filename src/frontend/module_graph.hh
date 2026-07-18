// ModuleGraph header - constructs and validates module dependency graph
#ifndef MODULE_GRAPH_H
#define MODULE_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "module_manager.hh"

namespace LM {
namespace Frontend {

class ModuleGraph {
public:
    // Build graph from existing modules map
    explicit ModuleGraph(const std::unordered_map<std::string, std::shared_ptr<Module>>& modules);

    // Detect cycles in the dependency graph
    bool has_cycle() const;

    // Return a topological order of module names (empty if cycle exists)
    std::vector<std::string> topological_order() const;

private:
    // adjacency list: module -> list of dependent modules
    std::unordered_map<std::string, std::vector<std::string>> adj_;
    // helper for DFS cycle detection
    bool dfs(const std::string& node,
             std::unordered_map<std::string, int>& state) const;
};

} // namespace Frontend
} // namespace LM

#endif // MODULE_GRAPH_H
