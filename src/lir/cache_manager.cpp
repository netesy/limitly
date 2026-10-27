#include "cache_manager.hh"
#include "serializer.hh"
#include "function_registry.hh"
#include "functions.hh"
#include "builtin_functions.hh"
#include "../frontend/module_manager.hh"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>
#include <cstring>

namespace fs = std::filesystem;

namespace LM {
namespace LIR {

bool CacheManager::enabled_ = true;

bool CacheManager::is_cache_enabled() {
    if (std::getenv("LYMAR_DISABLE_CACHE") || std::getenv("LYMAR_NO_CACHE")) {
        return false;
    }
    return enabled_;
}

void CacheManager::set_cache_enabled(bool enabled) {
    enabled_ = enabled;
}

std::string CacheManager::get_cache_directory() {
    const char* env_dir = std::getenv("LYMAR_CACHE_DIR");
    if (env_dir && *env_dir) {
        return std::string(env_dir);
    }
    return ".cache/lymar";
}

void CacheManager::clear_cache() {
    std::error_code ec;
    fs::remove_all(get_cache_directory(), ec);
}

std::string CacheManager::compute_cache_path(const std::string& entry_file) {
    std::string norm = entry_file;
    for (char& c : norm) {
        if (c == '\\') c = '/';
    }
    std::string sanitized = norm;
    for (char& c : sanitized) {
        if (c == '/' || c == ':' || c == '.' || c == ' ') {
            c = '_';
        }
    }
    // Add 64-bit hash suffix to prevent any collision
    size_t h = std::hash<std::string>{}(norm);
    char hex[24];
    snprintf(hex, sizeof(hex), "_%016llx", static_cast<unsigned long long>(h));
    return get_cache_directory() + "/programs/" + sanitized + hex + ".lircache";
}

namespace {

struct CacheWriter {
    std::vector<uint8_t> buf;
    void u8(uint8_t v) { buf.push_back(v); }
    void u32(uint32_t v) {
        buf.insert(buf.end(), reinterpret_cast<uint8_t*>(&v), reinterpret_cast<uint8_t*>(&v) + 4);
    }
    void u64(uint64_t v) {
        buf.insert(buf.end(), reinterpret_cast<uint8_t*>(&v), reinterpret_cast<uint8_t*>(&v) + 8);
    }
    void i64(int64_t v) {
        buf.insert(buf.end(), reinterpret_cast<uint8_t*>(&v), reinterpret_cast<uint8_t*>(&v) + 8);
    }
    void bytes(const void* p, size_t n) {
        const auto* b = reinterpret_cast<const uint8_t*>(p);
        buf.insert(buf.end(), b, b + n);
    }
    void str(const std::string& s) {
        u32(static_cast<uint32_t>(s.size()));
        bytes(s.data(), s.size());
    }
};

struct CacheReader {
    const std::vector<uint8_t>& buf;
    size_t pos = 0;
    explicit CacheReader(const std::vector<uint8_t>& b) : buf(b) {}
    void need(size_t n) const {
        if (pos + n > buf.size()) throw std::runtime_error("Unexpected end of cache buffer");
    }
    uint8_t u8() { need(1); return buf[pos++]; }
    uint32_t u32() {
        need(4);
        uint32_t v;
        std::memcpy(&v, buf.data() + pos, 4);
        pos += 4;
        return v;
    }
    uint64_t u64() {
        need(8);
        uint64_t v;
        std::memcpy(&v, buf.data() + pos, 8);
        pos += 8;
        return v;
    }
    int64_t i64() {
        need(8);
        int64_t v;
        std::memcpy(&v, buf.data() + pos, 8);
        pos += 8;
        return v;
    }
    std::string str() {
        uint32_t len = u32();
        need(len);
        std::string s(reinterpret_cast<const char*>(buf.data() + pos), len);
        pos += len;
        return s;
    }
    std::vector<uint8_t> blob() {
        uint32_t len = u32();
        need(len);
        std::vector<uint8_t> out(buf.begin() + pos, buf.begin() + pos + len);
        pos += len;
        return out;
    }
};

} // namespace

bool CacheManager::save_program_cache(
    const std::string& entry_file,
    const LIR_Function& top_level_func,
    bool verbose
) {
    if (!is_cache_enabled()) return false;

    try {
        std::string cache_path = compute_cache_path(entry_file);
        fs::path parent_dir = fs::path(cache_path).parent_path();
        std::error_code ec;
        fs::create_directories(parent_dir, ec);
        if (ec) return false;

        std::unordered_set<std::string> seen_paths;
        std::vector<std::string> dep_paths;

        auto add_dep = [&](const std::string& p) {
            if (p.empty()) return;
            std::error_code ec2;
            if (fs::exists(p, ec2) && fs::is_regular_file(p, ec2)) {
                std::string norm = fs::path(p).lexically_normal().generic_string();
                if (seen_paths.insert(norm).second) {
                    dep_paths.push_back(p);
                }
            }
        };

        add_dep(entry_file);
        auto all_modules = LM::Frontend::ModuleManager::getInstance().get_all_modules();
        for (const auto& [mod_name, mod] : all_modules) {
            if (mod && !mod->path.empty()) {
                add_dep(mod->path);
            }
        }

        CacheWriter w;
        w.bytes("LMC1", 4);
        w.u8(1); // cache format version
        w.u8(1); // ABI version

        // Dependencies
        w.u32(static_cast<uint32_t>(dep_paths.size()));
        for (const auto& path : dep_paths) {
            std::error_code ec2;
            auto ftime = fs::last_write_time(path, ec2);
            int64_t nanos = ec2 ? 0 : std::chrono::duration_cast<std::chrono::nanoseconds>(ftime.time_since_epoch()).count();
            uint64_t size = ec2 ? 0 : fs::file_size(path, ec2);
            w.str(path);
            w.i64(nanos);
            w.u64(size);
        }

        // Functions (skip builtins)
        auto& registry = FunctionRegistry::getInstance();
        auto all_func_names = registry.getFunctionNames();
        std::vector<std::string> func_names;
        for (const auto& name : all_func_names) {
            if (BuiltinUtils::isBuiltinFunction(name)) continue;
            func_names.push_back(name);
        }

        w.u32(static_cast<uint32_t>(func_names.size()));
        for (const auto& name : func_names) {
            auto* func = registry.getFunction(name);
            if (!func) {
                w.str(name);
                w.u32(0);
                continue;
            }
            auto f_bytes = Serializer::serialize(*func);
            w.str(name);
            w.u32(static_cast<uint32_t>(f_bytes.size()));
            w.bytes(f_bytes.data(), f_bytes.size());
        }

        // Top-level wrapper function
        auto top_bytes = Serializer::serialize(top_level_func);
        w.u32(static_cast<uint32_t>(top_bytes.size()));
        w.bytes(top_bytes.data(), top_bytes.size());

        // Write to tmp then atomic rename
        std::string tmp_path = cache_path + ".tmp";
        std::ofstream out(tmp_path, std::ios::binary);
        if (!out.is_open()) return false;
        out.write(reinterpret_cast<const char*>(w.buf.data()), w.buf.size());
        out.close();

        fs::rename(tmp_path, cache_path, ec);
        if (ec) {
            fs::remove(tmp_path, ec);
            return false;
        }

        if (verbose || std::getenv("LYMAR_TRACE_CACHE")) {
            std::cerr << "[CACHE_SAVE] " << entry_file << " -> " << cache_path
                      << " (" << dep_paths.size() << " deps, " << func_names.size() << " funcs, "
                      << w.buf.size() / 1024 << " KB)\n";
        }
        return true;
    } catch (const std::exception& e) {
        if (verbose || std::getenv("LYMAR_TRACE_CACHE")) {
            std::cerr << "[CACHE_SAVE_ERROR] " << e.what() << "\n";
        }
        return false;
    }
}

std::unique_ptr<LIR_Function> CacheManager::try_load_program_cache(
    const std::string& entry_file,
    bool verbose
) {
    if (!is_cache_enabled()) return nullptr;

    try {
        std::string cache_path = compute_cache_path(entry_file);
        std::error_code ec;
        if (!fs::exists(cache_path, ec)) return nullptr;

        std::ifstream in(cache_path, std::ios::binary | std::ios::ate);
        if (!in.is_open()) return nullptr;
        std::streamsize file_size = in.tellg();
        if (file_size < 10) return nullptr;
        in.seekg(0, std::ios::beg);

        std::vector<uint8_t> buffer(file_size);
        if (!in.read(reinterpret_cast<char*>(buffer.data()), file_size)) return nullptr;
        in.close();

        CacheReader r(buffer);
        char magic[4];
        r.need(4);
        std::memcpy(magic, buffer.data() + r.pos, 4);
        r.pos += 4;
        if (std::memcmp(magic, "LMC1", 4) != 0) return nullptr;

        uint8_t version = r.u8();
        uint8_t abi_version = r.u8();
        if (version != 1 || abi_version != 1) return nullptr;

        // Validate dependencies
        uint32_t dep_count = r.u32();
        for (uint32_t i = 0; i < dep_count; ++i) {
            std::string path = r.str();
            int64_t stored_nanos = r.i64();
            uint64_t stored_size = r.u64();

            if (!fs::exists(path, ec) || !fs::is_regular_file(path, ec)) {
                if (verbose || std::getenv("LYMAR_TRACE_CACHE")) {
                    std::cerr << "[CACHE_MISS] Dependency missing: " << path << "\n";
                }
                return nullptr;
            }
            auto current_time = fs::last_write_time(path, ec);
            if (ec) return nullptr;
            int64_t current_nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time.time_since_epoch()).count();
            if (current_nanos != stored_nanos) {
                if (verbose || std::getenv("LYMAR_TRACE_CACHE")) {
                    std::cerr << "[CACHE_MISS] Dependency modified (time): " << path << "\n";
                }
                return nullptr;
            }
            auto current_size = fs::file_size(path, ec);
            if (ec || current_size != stored_size) {
                if (verbose || std::getenv("LYMAR_TRACE_CACHE")) {
                    std::cerr << "[CACHE_MISS] Dependency modified (size): " << path << "\n";
                }
                return nullptr;
            }
        }

        // Cache Hit!
        if (verbose || std::getenv("LYMAR_TRACE_CACHE")) {
            std::cerr << "[CACHE_HIT] Loading " << entry_file << " from " << cache_path << "\n";
        }

        auto& registry = FunctionRegistry::getInstance();
        auto& func_manager = LIRFunctionManager::getInstance();
        registry.clear();
        func_manager.clear();

        // Register standard runtime builtins into FunctionRegistry
        BuiltinUtils::initializeBuiltins();
        for (const auto& name : BuiltinUtils::getBuiltinFunctionNames()) {
            auto lir_func = std::make_unique<LIR_Function>("builtin_" + name, 0);
            lir_func->name = name;
            lir_func->param_count = 0;
            LIR_Inst call_inst(LIR_Op::Call, 0, 0, 0, 0);
            call_inst.dst = 0;
            call_inst.a = 0;
            call_inst.b = 0;
            lir_func->instructions.push_back(call_inst);
            LIR_Inst ret_inst(LIR_Op::Return, 0, 0, 0, 0);
            ret_inst.a = 0;
            lir_func->instructions.push_back(ret_inst);
            registry.registerVerifiedFunction(name, std::move(lir_func));
        }

        uint32_t func_count = r.u32();
        for (uint32_t i = 0; i < func_count; ++i) {
            std::string name = r.str();
            auto f_bytes = r.blob();
            if (f_bytes.empty()) continue;
            if (BuiltinUtils::isBuiltinFunction(name)) continue;

            LIR_Function func = Serializer::deserialize(f_bytes);

            // Populate LIRFunctionManager
            std::vector<LIRParameter> params;
            for (size_t p = 0; p < func.param_count; ++p) {
                LIRParameter param;
                param.name = "arg" + std::to_string(p);
                auto it = func.register_types.find(static_cast<Reg>(p));
                param.type = (it != func.register_types.end()) ? it->second : Type::I64;
                params.push_back(param);
            }
            auto lir_f = std::make_shared<LIRFunction>(name, params, Type::I64, nullptr);
            lir_f->memory_effects_ = func.memory_effects;
            lir_f->inferred_effects_ = func.inferred_effects;
            lir_f->ownership_parameters_ = func.ownership_parameters;
            lir_f->ownership_captures_ = func.ownership_captures;
            lir_f->ownership_provenance_ = func.ownership_provenance;
            lir_f->register_count_ = func.register_count;
            lir_f->setRegisterLanguageTypes(func.register_language_types);
            lir_f->setRegisterTypes(func.register_types);
            lir_f->setInstructions(func.instructions);
            func_manager.registerCachedFunction(name, lir_f);

            // Populate FunctionRegistry directly without re-running heavy verification
            registry.registerVerifiedFunction(name, std::make_unique<LIR_Function>(std::move(func)));
        }

        // Read top-level wrapper
        auto top_bytes = r.blob();
        if (top_bytes.empty()) return nullptr;
        LIR_Function top_level = Serializer::deserialize(top_bytes);
        return std::make_unique<LIR_Function>(std::move(top_level));
    } catch (const std::exception& e) {
        if (verbose || std::getenv("LYMAR_TRACE_CACHE")) {
            std::cerr << "[CACHE_LOAD_ERROR] " << e.what() << "\n";
        }
        return nullptr;
    }
}

} // namespace LIR
} // namespace LM
