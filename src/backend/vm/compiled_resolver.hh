#pragma once

#include "vm_value.hh"
#include "frontend/module_manager.hh"
#include <string>
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <algorithm>
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
        bool exported = false;
        for (const auto& [name, variants] : Frontend::ModuleManager::getInstance().get_compiled_modules()) {
            for (const auto& meta : variants) {
                if (meta.artifact_kind == "shared" &&
                    std::find(meta.exports.begin(), meta.exports.end(), symbol) != meta.exports.end()) exported = true;
            }
        }
        if (!exported) return false;
        void* native_symbol = getSymbol(symbol);
        if (native_symbol && symbol_abi_[symbol] == Backend::Native::ABI_VERSION) {
            std::vector<LmValue> args;
            args.reserve(call.call_args.size() + closure_args.size());
            for (auto r : call.call_args) args.push_back(registers.at(r));
            args.insert(args.end(), closure_args.begin(), closure_args.end());
            auto entry = reinterpret_cast<Backend::Native::Entry>(native_symbol);
            auto value = entry(&Backend::Native::host_api(), vm_context, args.data(), args.size());
            if (call.dst != UINT32_MAX) registers.at(call.dst) = value;
            if (std::getenv("LYMAR_TRACE_PRECOMPILED")) std::cerr << "PRECOMPILED_CALL: " << symbol << "\n";
            return true;
        }
        if (native_symbol) {
            throw std::runtime_error("Unsupported precompiled module ABI for '" + symbol + "'; rebuild the module");
        }
        if (std::getenv("LYMAR_DISABLE_INTERPRETER_FALLBACK")) {
            throw std::runtime_error("Precompiled dispatch unavailable for '" + symbol + "': native symbol unavailable");
        }
        return false;
    }

private:
    CompiledResolver() = default;

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
