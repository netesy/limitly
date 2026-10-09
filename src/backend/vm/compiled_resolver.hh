#pragma once

#include "vm_value.hh"
#include "frontend/module_manager.hh"
#include <string>
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <array>
#include "lir/function_registry.hh"
#include "runtime/lymarrt/lymarrt.h"
#include "backend/native/abi.hh"

#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace LM {

class CompiledResolver {
public:
    static CompiledResolver& getInstance() {
        // Execution threads must not mutate one another's dispatch caches.
        // Module registration epochs invalidate each thread's facts on next use.
        static thread_local CompiledResolver instance;
        return instance;
    }

    void* getSymbol(const std::string& symbol) {
        refresh_metadata();
        if (symbol.empty()) return nullptr;
        auto it = resolved_symbols_.find(symbol);
        if (it != resolved_symbols_.end()) {
            return it->second;
        }

        // Try searching in all loaded precompiled modules
        auto& mm = LM::Frontend::ModuleManager::getInstance();
        for (const auto& [mod_name, vec] : mm.get_compiled_modules()) {
            for (const auto& meta : vec) {
                if (meta.artifact_kind == "shared" && !meta.artifact_path.empty() &&
                    std::find(meta.exports.begin(), meta.exports.end(), symbol) != meta.exports.end()) {
                    void* handle = getLibraryHandle(meta.artifact_path);
                    if (handle) {
                        void* sym = findSymbolInHandle(handle, symbol);
                        if (sym) {
                            auto version = reinterpret_cast<uint32_t (*)()>(findSymbolInHandle(handle, "lymar_module_abi_version"));
                            symbol_abi_[symbol] = version ? version() : 0;
                            resolved_symbols_[symbol] = sym;
                            return sym;
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    bool dispatch(const std::string& symbol, const LIR::LIR_Inst& call,
                  std::vector<LmValue>& registers, void* vm_context,
                  const std::vector<LmValue>& closure_args = {}) {
        // Baseline ABI 1 shares canonical VM values; legacy scalar artifacts must rebuild.
        auto* function = LIR::FunctionRegistry::getInstance().getFunction(symbol);
        if (!function) return false;
        refresh_metadata();
        // Pure VM execution needs no target cache when no native artifacts exist.
        if (Frontend::ModuleManager::getInstance().get_compiled_modules().empty()) return false;
        auto [position, inserted] = dispatch_targets_.try_emplace(symbol);
        auto& target = position->second;
        if (inserted) {
            for (const auto& [name, variants] : Frontend::ModuleManager::getInstance().get_compiled_modules()) {
                for (const auto& meta : variants) {
                    if (meta.artifact_kind == "shared" &&
                        std::find(meta.exports.begin(), meta.exports.end(), symbol) != meta.exports.end()) {
                        target.exported = true;
                        break;
                    }
                }
                if (target.exported) break;
            }
        }
        if (!target.exported) return false;
        // Retry unresolved symbols; a temporarily missing library is not a
        // permanently negative cache entry. Successful targets retain ABI validation.
        if (!target.entry) {
            target.entry = reinterpret_cast<Backend::Native::Entry>(getSymbol(symbol));
            if (target.entry) target.abi = symbol_abi_.at(symbol);
        }
        if (target.entry && target.abi == Backend::Native::ABI_VERSION) {
            const size_t count = call.call_args.size() + closure_args.size();
            // Per-invocation storage is reentrant, including callbacks into this VM.
            // Bound stack usage while preserving arbitrary callable arity.
            std::array<LmValue, 64> local_args;
            std::vector<LmValue> overflow_args;
            LmValue* args = local_args.data();
            if (count > local_args.size()) {
                overflow_args.resize(count);
                args = overflow_args.data();
            }
            size_t index = 0;
            for (auto r : call.call_args) args[index++] = registers.at(r);
            for (auto value : closure_args) args[index++] = value;
            auto entry = target.entry;
            auto value = entry(&Backend::Native::host_api(), vm_context, args, count);
            if (call.dst != UINT32_MAX) registers.at(call.dst) = value;
            if (std::getenv("LYMAR_TRACE_PRECOMPILED")) std::cerr << "PRECOMPILED_CALL: " << symbol << "\n";
            return true;
        }
        if (target.entry) {
            throw std::runtime_error("Unsupported precompiled module ABI for '" + symbol + "'; rebuild the module");
        }
        if (std::getenv("LYMAR_DISABLE_INTERPRETER_FALLBACK")) {
            throw std::runtime_error("Precompiled dispatch unavailable for '" + symbol + "': native symbol unavailable");
        }
        return false;
    }

private:
    CompiledResolver() = default;

    struct DispatchTarget {
        Backend::Native::Entry entry = nullptr;
        uint32_t abi = 0;
        bool exported = false;
    };
    uint64_t metadata_revision_ = UINT64_MAX;
    std::unordered_map<std::string, DispatchTarget> dispatch_targets_;
    void refresh_metadata() {
        const auto revision = Frontend::ModuleManager::getInstance().compiled_modules_revision();
        if (revision == metadata_revision_) return;
        dispatch_targets_.clear();
        resolved_symbols_.clear();
        symbol_abi_.clear();
        metadata_revision_ = revision;
    }

    std::unordered_map<std::string, void*> resolved_symbols_;
    std::unordered_map<std::string, uint32_t> symbol_abi_;
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
