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

    // Trait conformance registry: canonical trait name -> set of canonical
    // frame names that were verified to implement it (including via parent
    // traits). Recorded by the type checker where alias resolution has
    // already succeeded; consumed by backend reachability/dispatch so trait
    // calls only keep real implementors instead of every same-named method.
    void record_trait_implementor(const std::string& trait_name, const std::string& frame_name) {
        trait_implementors_[trait_name].insert(frame_name);
    }
    const std::map<std::string, std::set<std::string>>& trait_implementors() const {
        return trait_implementors_;
    }

    // Frame-method registry: LIR function names (module.Frame.method) that
    // are frame methods, recorded during LIR lowering. Backend trait
    // dispatch uses it to exclude module-level functions that merely share
    // a method's name. Empty on LIR-cache hits (lowering is skipped), in
    // which case consumers must fall back to unfiltered matching.
    void record_frame_method(const std::string& function_name) {
        frame_method_names_.insert(function_name);
    }
    const std::set<std::string>& frame_method_names() const { return frame_method_names_; }

    // Compile-time target OS specialization. The driver sets this once per
    // compilation (host OS for `run`, -target for `build`); load_module then
    // rewrites the std.os.identity TARGET_OS const initializer so platform
    // dispatch folds at compile time and dead branches produce no code.
    // Codes: 0=unknown 1=windows 2=linux 3=macos 4=android 5=freebsd 6=wasi
    static void set_target_os(int code) { target_os_code_ = code; }
    static int target_os() { return target_os_code_; }

    // Compile-time graphics-backend preference for std.gg, sourced from the
    // LYMAR_GG_BACKEND environment variable at compile time. Codes:
    // 0=auto (runtime dispatch, both backends linked), 1=native, 2=sokol.
    // load_module rewrites the std.os.identity GG_BACKEND const initializer so
    // std.gg's backend dispatch folds and the unused backend is tree-shaken.
    static void set_gg_backend(int code) { gg_backend_code_ = code; }
    static int gg_backend() { return gg_backend_code_; }

    // Set search directories for module imports
    void set_include_dirs(const std::vector<std::string>& dirs);
    // Add a single search directory (used by c: scheme binding generation)
    void add_include_path(const std::string& dir);

    // Cross-module compile-time constants. Each module is type-checked by its
    // own TypeChecker instance, so const tables do not cross module boundaries
    // on their own; check_program records them here keyed by module path so
    // `alias.CONST` expressions in other modules can fold at compile time.
    void record_module_constants(const std::string& module_path,
                                 const std::unordered_map<std::string, long long>& ints,
                                 const std::unordered_map<std::string, double>& doubles) {
        module_int_consts_[module_path] = ints;
        module_double_consts_[module_path] = doubles;
    }
    const std::unordered_map<std::string, long long>* module_int_constants(const std::string& module_path) const {
        auto it = module_int_consts_.find(module_path);
        return it == module_int_consts_.end() ? nullptr : &it->second;
    }
    const std::unordered_map<std::string, double>* module_double_constants(const std::string& module_path) const {
        auto it = module_double_consts_.find(module_path);
        return it == module_double_consts_.end() ? nullptr : &it->second;
    }

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
        file_cache_.clear();
        // Conformance facts are re-recorded by each type-check pass; keeping
        // stale entries would only over-approximate dispatch candidates.
        trait_implementors_.clear();
        frame_method_names_.clear();
        module_int_consts_.clear();
        module_double_consts_.clear();
        compiled_modules_revision_counter().fetch_add(1, std::memory_order_release);
        // Type checking reloads modules after resolution; keep the configured
        // search paths so -I and installed LYMAR_HOME modules remain available.
    }

private:
    ModuleManager() = default;

    std::unordered_map<std::string, std::shared_ptr<Module>> modules_;
    std::vector<std::string> include_dirs_;
    std::unordered_map<std::string, std::string> file_cache_;
    std::unordered_map<std::string, std::vector<CompiledModuleMeta>> compiled_modules_;
    std::map<std::string, std::set<std::string>> trait_implementors_;
    std::set<std::string> frame_method_names_;
    // Defaults to the host OS so tools that never call set_target_os (LSP,
    // DAP, linter) still get correct specialization; lymar.cpp overrides with
    // options.target for cross-compilation.
    static inline int target_os_code_ =
#ifdef _WIN32
        1;
#elif defined(__APPLE__)
        3;
#elif defined(__ANDROID__)
        4;
#elif defined(__FreeBSD__)
        5;
#elif defined(__wasi__) || defined(__wasm__)
        6;
#elif defined(__linux__)
        2;
#else
        0;
#endif
    // Defaults to AUTO so tools that never call set_gg_backend keep runtime
    // backend dispatch; lymar.cpp sets this from LYMAR_GG_BACKEND.
    static inline int gg_backend_code_ = 0;
    static std::atomic<uint64_t>& compiled_modules_revision_counter() {
        static std::atomic<uint64_t> revision{0};
        return revision;
    }
    std::map<std::string, std::unordered_map<std::string, long long>> module_int_consts_;
    std::map<std::string, std::unordered_map<std::string, double>> module_double_consts_;
    mutable std::mutex modules_mutex_;

    std::shared_ptr<Module> get_module_unlocked(const std::string& name) const;
    std::string find_module_file(const std::string& module_path);
    void extract_metadata(std::shared_ptr<Module> module);
    void expand_reexports(std::shared_ptr<Module> module);
};

} // namespace Frontend
} // namespace LM

#endif // MODULE_MANAGER_H
