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

#include <mutex>

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

        // Prefer statically linked artifacts (already inside this process, no
        // runtime loading), then fall back to shared libraries.
        auto& mm = LM::Frontend::ModuleManager::getInstance();
        for (int pass = 0; pass < 2; ++pass) {
            // "vmstatic" artifacts are statically linked VM-dispatch objects;
            // they are deliberately distinct from "static" AOT artifacts so
            // the AOT linker never picks up the tagged-ABI wrappers.
            const bool want_static = pass == 0;
            for (const auto& [mod_name, vec] : mm.get_compiled_modules()) {
                for (const auto& meta : vec) {
                    const bool kind_match = want_static
                        ? (meta.artifact_kind == "static" || meta.artifact_kind == "vmstatic")
                        : meta.artifact_kind == "shared";
                    if (kind_match && !meta.artifact_path.empty() &&
                        std::find(meta.exports.begin(), meta.exports.end(), symbol) != meta.exports.end()) {
                        void* sym = nullptr;
                        if (want_static) {
                            ensure_static_init();
                            sym = findProcessSymbol(symbol);
                            symbol_abi_[symbol] = Backend::Native::ABI_VERSION;
                        } else {
                            void* handle = getLibraryHandle(meta.artifact_path);
                            if (handle) {
                                sym = findSymbolInHandle(handle, symbol);
                                if (sym) {
                                    auto version = reinterpret_cast<uint32_t (*)()>(findSymbolInHandle(handle, "lymar_module_abi_version"));
                                    symbol_abi_[symbol] = version ? version() : 0;
                                }
                            }
                        }
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

    // Resolve a precompiled shared-module export to an ABI-validated entry
    // point, or nullptr when no compatible export exists. Result is cached
    // per symbol and invalidated on module-metadata revision changes.
    Backend::Native::Entry resolve_entry(const std::string& symbol) {
        if (symbol.empty()) return nullptr;
        refresh_metadata();
        if (Frontend::ModuleManager::getInstance().get_compiled_modules().empty()) return nullptr;
        auto [position, inserted] = dispatch_targets_.try_emplace(symbol);
        auto& target = position->second;
        if (inserted) {
            for (const auto& [name, variants] : Frontend::ModuleManager::getInstance().get_compiled_modules()) {
                for (const auto& meta : variants) {
                    if (((meta.artifact_kind == "shared" || meta.artifact_kind == "static" || meta.artifact_kind == "vmstatic")) &&
                        std::find(meta.exports.begin(), meta.exports.end(), symbol) != meta.exports.end()) {
                        target.exported = true;
                        break;
                    }
                }
                if (target.exported) break;
            }
        }
        if (!target.exported) return nullptr;
        if (!target.entry) {
            target.entry = reinterpret_cast<Backend::Native::Entry>(getSymbol(symbol));
            if (target.entry) target.abi = symbol_abi_.at(symbol);
        }
        return (target.entry && target.abi == Backend::Native::ABI_VERSION) ? target.entry : nullptr;
    }

    // Invoke a precompiled shared-module export directly with tagged VM
    // values, bypassing the register-file plumbing used by dispatch(). Used by
    // gpu_dispatch to run `gpu task` bodies natively when the task lives in a
    // compiled module. Returns false when no ABI-compatible export exists.
    bool dispatch_values(const std::string& symbol, const LmValue* args, size_t count,
                         void* vm_context, LmValue* out = nullptr) {
        auto entry = resolve_entry(symbol);
        if (!entry) return false;
        auto value = entry(&Backend::Native::host_api(), vm_context, args, count);
        if (out) *out = value;
        if (std::getenv("LYMAR_TRACE_PRECOMPILED")) std::cerr << "PRECOMPILED_CALL: " << symbol << "\n";
        return true;
    }

    template <typename RegContainer>
    bool dispatch(const std::string& symbol, const LIR::LIR_Inst& call,
                  RegContainer& registers, void* vm_context,
                  const std::vector<LmValue>& closure_args = {}) {
        // Baseline ABI 1 shares canonical VM values; legacy scalar artifacts must rebuild.
        auto* function = LIR::FunctionRegistry::getInstance().getFunction(symbol);
        if (!function) {
            if (std::getenv("LYMAR_TRACE_PRECOMPILED") && symbol.find("sdf_atlas") != std::string::npos)
                std::cerr << "DISPATCH_FAIL_NO_LIR: " << symbol << "\n";
            return false;
        }
        refresh_metadata();
        // Pure VM execution needs no target cache when no native artifacts exist.
        if (Frontend::ModuleManager::getInstance().get_compiled_modules().empty()) {
            if (std::getenv("LYMAR_TRACE_PRECOMPILED") && symbol.find("sdf_atlas") != std::string::npos)
                std::cerr << "DISPATCH_FAIL_NO_MODULES: " << symbol << "\n";
            return false;
        }
        auto [position, inserted] = dispatch_targets_.try_emplace(symbol);
        auto& target = position->second;
        if (inserted) {
            for (const auto& [name, variants] : Frontend::ModuleManager::getInstance().get_compiled_modules()) {
                for (const auto& meta : variants) {
                    if (((meta.artifact_kind == "shared" || meta.artifact_kind == "static" || meta.artifact_kind == "vmstatic")) &&
                        std::find(meta.exports.begin(), meta.exports.end(), symbol) != meta.exports.end()) {
                        target.exported = true;
                        break;
                    }
                }
                if (target.exported) break;
            }
        }
        if (!target.exported) {
            if (std::getenv("LYMAR_TRACE_PRECOMPILED") && symbol.find("sdf_atlas") != std::string::npos)
                std::cerr << "DISPATCH_FAIL_NOT_EXPORTED: " << symbol << "\n";
            return false;
        }
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
            if (std::getenv("LYMAR_TRACE_PRECOMPILED")) std::cerr << "DISPATCH_ENTER: " << symbol << "\n";
            auto value = entry(&Backend::Native::host_api(), vm_context, args, count);
            if (std::getenv("LYMAR_TRACE_PRECOMPILED")) std::cerr << "DISPATCH_LEAVE: " << symbol << "\n";
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

    // Symbols from statically linked AOT archives live in this executable's
    // own symbol table; look them up with the default process handle.
    void* findProcessSymbol(const std::string& symbol) {
#if defined(_WIN32)
        return reinterpret_cast<void*>(GetProcAddress(GetModuleHandleA(nullptr), symbol.c_str()));
#else
        return dlsym(RTLD_DEFAULT, symbol.c_str());
#endif
    }

    // Statically linked module objects carry a `main` init runner renamed to
    // `lymar_module_init` at build time; invoke it once so module globals and
    // `__init` bodies run before the first dispatched call.
    void ensure_static_init() {
        static std::once_flag flag;
        std::call_once(flag, [this] {
            if (std::getenv("LYMAR_TRACE_PRECOMPILED")) std::cerr << "STATIC_INIT: calling lymar_module_init\n";
            auto init = reinterpret_cast<void (*)()>(findProcessSymbol("lymar_module_init"));
            if (init) init();
            if (std::getenv("LYMAR_TRACE_PRECOMPILED")) std::cerr << "STATIC_INIT: done\n";
        });
    }
};

} // namespace LM
