#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <set>
#include <mutex>
#include "ast.hh"

namespace LM {
namespace Frontend {

struct Module {
    std::string name;
    std::string path;
    std::string source;
    std::shared_ptr<AST::Program> ast;
    std::vector<std::string> dependencies;
    std::set<std::string> public_symbols;
    std::set<std::string> used_symbols;
    bool is_checked = false;
    bool is_initialized = false;
};

class ModuleManager {
public:
    static ModuleManager& getInstance() {
        static ModuleManager instance;
        return instance;
    }

    // Load a module and its dependencies recursively
    std::shared_ptr<Module> load_module(const std::string& module_path);

    // Resolve all imports for a given root program
    void resolve_all(std::shared_ptr<AST::Program> root_program, const std::string& root_path);

    std::shared_ptr<Module> get_module(const std::string& name);

    // Returns a copy of the modules map for thread-safe iteration
    std::unordered_map<std::string, std::shared_ptr<Module>> get_all_modules();

    // Helper to filter symbols based on show/hide
    std::set<std::string> filter_symbols(std::shared_ptr<Module> module, const std::optional<AST::ImportFilter>& filter);

    // Get modules in topological order for initialization
    std::vector<std::string> get_topological_order();
    bool has_circular_dependencies();

    void clear() {
        std::lock_guard<std::mutex> lock(modules_mutex_);
        modules_.clear();
    }

private:
    ModuleManager() = default;

    std::unordered_map<std::string, std::shared_ptr<Module>> modules_;
    mutable std::mutex modules_mutex_;

    std::shared_ptr<Module> get_module_unlocked(const std::string& name) const;
    std::string find_module_file(const std::string& module_path);
    void extract_metadata(std::shared_ptr<Module> module);
};

} // namespace Frontend
} // namespace LM

#endif // MODULE_MANAGER_H
