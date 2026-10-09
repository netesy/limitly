#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <set>
#include <map>
#include <mutex>
#include <atomic>
#include "ast.hh"

namespace LM {
namespace Frontend {

struct CompiledModuleMeta {
    std::string module_name;
    std::string abi_version = "0.0.1"; // Lymar/lymarrt ABI version
    std::string runtime_semantics; // Artifact freshness, independent of the object ABI.
    std::string target_triple; // e.g. x86_64-linux-gnu
    std::string architecture; // e.g. x86_64
    std::string os; // e.g. linux
    std::string artifact_kind; // "shared" or "static"
    std::string artifact_path; // path to .so or .a file
    std::vector<std::string> exports;
    std::map<std::string, std::string> export_signatures;
    std::vector<std::string> dependencies;
    std::string source_hash; // Content SHA256 hash for stale detection
    std::map<std::string, std::string> dependency_hashes;

    std::string serialize() const;
    static bool deserialize(const std::string& input, CompiledModuleMeta& out_meta);
    static std::string compute_sha256(const std::string& input);
};

struct Module {
    std::string name;
    std::string path;
    std::string source;
    std::shared_ptr<AST::Program> ast;
    std::vector<std::string> dependencies;
    std::set<std::string> public_symbols;
    std::vector<std::shared_ptr<AST::Statement>> reexports;
    // Re-exported symbol name -> path of the module that actually defines it.
    std::map<std::string, std::string> reexport_sources;
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
    // Maps `<module>.<name>` to the defining module's `<module>.<name>` when <name> is
    // a `pub import ... show` re-export; otherwise returns the input unchanged.
    std::string canonical_symbol(const std::string& qualified_name);

    // Returns a copy of the modules map for thread-safe iteration
    std::unordered_map<std::string, std::shared_ptr<Module>> get_all_modules() const;

    // Helper to filter symbols based on show/hide
    std::set<std::string> filter_symbols(std::shared_ptr<Module> module, const std::optional<AST::ImportFilter>& filter);

    // Get modules in topological order for initialization
    std::vector<std::string> get_topological_order();
    bool has_circular_dependencies();

    // Set search directories for module imports
    void set_include_dirs(const std::vector<std::string>& dirs);

    // Precompiled module discovery and registration
    const std::unordered_map<std::string, std::vector<CompiledModuleMeta>>& get_compiled_modules() const {
        return compiled_modules_;
    }
    // Dispatch facts are valid only for this metadata registration epoch.
    uint64_t compiled_modules_revision() const { return compiled_modules_revision_counter().load(std::memory_order_acquire); }
    bool register_compiled_module(const CompiledModuleMeta& meta);
    bool find_compiled_module(const std::string& module_name, const std::string& target_triple, const std::string& required_kind, CompiledModuleMeta& out_meta);
    bool is_artifact_valid(const CompiledModuleMeta& meta, const std::string& current_source_path);
    CompiledModuleMeta generate_metadata(
        std::shared_ptr<Module> module,
        const std::string& target,
        const std::string& arch,
        const std::string& artifact_kind,
        const std::string& artifact_path
    );

    void clear() {
        std::lock_guard<std::mutex> lock(modules_mutex_);
        modules_.clear();
        compiled_modules_.clear();
        compiled_modules_revision_counter().fetch_add(1, std::memory_order_release);
        // Type checking reloads modules after resolution; keep the configured
        // search paths so -I and installed LYMAR_HOME modules remain available.
    }

private:
    ModuleManager() = default;

    std::unordered_map<std::string, std::shared_ptr<Module>> modules_;
    std::vector<std::string> include_dirs_;
    std::unordered_map<std::string, std::vector<CompiledModuleMeta>> compiled_modules_;
    static std::atomic<uint64_t>& compiled_modules_revision_counter() {
        static std::atomic<uint64_t> revision{0};
        return revision;
    }
    mutable std::mutex modules_mutex_;

    std::shared_ptr<Module> get_module_unlocked(const std::string& name) const;
    std::string find_module_file(const std::string& module_path);
    void extract_metadata(std::shared_ptr<Module> module);
    void expand_reexports(std::shared_ptr<Module> module);
};

} // namespace Frontend
} // namespace LM

#endif // MODULE_MANAGER_H
