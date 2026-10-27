#pragma once

#include "lir.hh"
#include <memory>
#include <string>
#include <vector>

namespace LM {
namespace LIR {

class CacheManager {
public:
    static bool is_cache_enabled();
    static void set_cache_enabled(bool enabled);

    // Clears the on-disk cache directory
    static void clear_cache();

    // Returns the cache directory path (default ".cache/lymar")
    static std::string get_cache_directory();

    // Try loading a cached program (all module functions + top-level wrapper).
    // Returns nullptr on cache miss or dependency invalidation.
    static std::unique_ptr<LIR_Function> try_load_program_cache(
        const std::string& entry_file,
        bool verbose = false
    );

    // Save a program and its loaded dependencies to the cache.
    static bool save_program_cache(
        const std::string& entry_file,
        const LIR_Function& top_level_func,
        bool verbose = false
    );

private:
    static std::string compute_cache_path(const std::string& entry_file);
    static bool enabled_;
};

} // namespace LIR
} // namespace LM
