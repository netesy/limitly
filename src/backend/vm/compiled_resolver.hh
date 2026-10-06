#pragma once

#include "vm_value.hh"
#include "frontend/module_manager.hh"
#include <string>
#include <unordered_map>
#include <iostream>
#include <cstdlib>

#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace LM {

class CompiledResolver {
public:
    static CompiledResolver& getInstance() {
        static CompiledResolver instance;
        return instance;
    }

    void* getSymbol(const std::string& symbol) {
        if (symbol.empty()) return nullptr;
        auto it = resolved_symbols_.find(symbol);
        if (it != resolved_symbols_.end()) {
            return it->second;
        }

        // Try searching in all loaded precompiled modules
        auto& mm = LM::Frontend::ModuleManager::getInstance();
        for (const auto& [mod_name, vec] : mm.get_compiled_modules()) {
            for (const auto& meta : vec) {
                if (meta.artifact_kind == "shared" && !meta.artifact_path.empty()) {
                    void* handle = getLibraryHandle(meta.artifact_path);
                    if (handle) {
                        void* sym = findSymbolInHandle(handle, symbol);
                        if (sym) {
                            resolved_symbols_[symbol] = sym;
                            return sym;
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    bool dispatch(const std::string& symbol, uint64_t reg_base, void* vm_instance) {
        void* sym = getSymbol(symbol);
        if (sym) {
            using CompiledFn = LmValue(*)(uint64_t, void*);
            CompiledFn fn = reinterpret_cast<CompiledFn>(sym);
            fn(reg_base, vm_instance);
            return true;
        }

        if (std::getenv("LYMAR_DISABLE_INTERPRETER_FALLBACK")) {
            std::cerr << "FATAL: Precompiled native callable dispatch failed for symbol '"
                      << symbol << "' and LYMAR_DISABLE_INTERPRETER_FALLBACK is set!\n";
            std::exit(1);
        }
        return false;
    }

private:
    CompiledResolver() = default;

    std::unordered_map<std::string, void*> resolved_symbols_;
    std::unordered_map<std::string, void*> loaded_handles_;

    void* getLibraryHandle(const std::string& path) {
        auto it = loaded_handles_.find(path);
        if (it != loaded_handles_.end()) return it->second;

#if defined(_WIN32)
        HMODULE handle = LoadLibraryA(path.c_str());
#else
        void* handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
#endif
        if (handle) {
            loaded_handles_[path] = reinterpret_cast<void*>(handle);
        }
        return reinterpret_cast<void*>(handle);
    }

    void* findSymbolInHandle(void* handle, const std::string& symbol) {
        if (!handle) return nullptr;
#if defined(_WIN32)
        return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(handle), symbol.c_str()));
#else
        return dlsym(handle, symbol.c_str());
#endif
    }
};

} // namespace LM
