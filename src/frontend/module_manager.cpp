#include "module_manager.hh"
#include "scanner.hh"
#include "parser.hh"
#include "type_checker.hh"
#include "../error/debugger.hh"
#include "../lir/function_registry.hh"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <functional>
#include <future>
#include <iomanip>
#include <cstdlib>

#include <filesystem>

namespace LM {
namespace Frontend {

namespace fs = std::filesystem;

namespace {
class SHA256Helper {
public:
    SHA256Helper() { reset(); }

    void reset() {
        state_[0] = 0x6a09e667; state_[1] = 0xbb67ae85;
        state_[2] = 0x3c6ef372; state_[3] = 0xa54ff53a;
        state_[4] = 0x510e527f; state_[5] = 0x9b05688c;
        state_[6] = 0x1f83d9ab; state_[7] = 0x5be0cd19;
        buflen_ = 0; totlen_ = 0;
    }

    void update(const uint8_t* data, size_t len) {
        totlen_ += len;
        size_t i = 0;
        while (i < len) {
            size_t space = 64 - buflen_;
            size_t chunk = (len - i < space) ? (len - i) : space;
            std::memcpy(buf_ + buflen_, data + i, chunk);
            buflen_ += chunk;
            i += chunk;
            if (buflen_ == 64) {
                transform(buf_);
                buflen_ = 0;
            }
        }
    }

    std::string digest() {
        uint64_t total_bits = totlen_ * 8;
        uint8_t pad = 0x80;
        update(&pad, 1);
        pad = 0;
        while (buflen_ != 56) update(&pad, 1);
        uint8_t len_be[8];
        for (int i = 7; i >= 0; i--) {
            len_be[i] = (uint8_t)(total_bits & 0xFF);
            total_bits >>= 8;
        }
        update(len_be, 8);

        char hex[65];
        std::snprintf(hex, sizeof(hex),
            "%08x%08x%08x%08x%08x%08x%08x%08x",
            state_[0], state_[1], state_[2], state_[3],
            state_[4], state_[5], state_[6], state_[7]);
        return std::string(hex);
    }

private:
    static uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
    static uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
    static uint32_t maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
    static uint32_t ep0(uint32_t x) { return rotr(x,2) ^ rotr(x,13) ^ rotr(x,22); }
    static uint32_t ep1(uint32_t x) { return rotr(x,6) ^ rotr(x,11) ^ rotr(x,25); }
    static uint32_t sig0(uint32_t x) { return rotr(x,7) ^ rotr(x,18) ^ (x >> 3); }
    static uint32_t sig1(uint32_t x) { return rotr(x,17) ^ rotr(x,19) ^ (x >> 10); }

    void transform(const uint8_t block[64]) {
        static const uint32_t K[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };
        uint32_t W[64];
        for (int i = 0; i < 16; i++) {
            W[i] = ((uint32_t)block[i*4] << 24) | ((uint32_t)block[i*4+1] << 16) |
                   ((uint32_t)block[i*4+2] << 8) | (uint32_t)block[i*4+3];
        }
        for (int i = 16; i < 64; i++) {
            W[i] = sig1(W[i-2]) + W[i-7] + sig0(W[i-15]) + W[i-16];
        }
        uint32_t a = state_[0], b = state_[1], c = state_[2], d = state_[3];
        uint32_t e = state_[4], f = state_[5], g = state_[6], h = state_[7];
        for (int i = 0; i < 64; i++) {
            uint32_t t1 = h + ep1(e) + ch(e,f,g) + K[i] + W[i];
            uint32_t t2 = ep0(a) + maj(a,b,c);
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        state_[0] += a; state_[1] += b; state_[2] += c; state_[3] += d;
        state_[4] += e; state_[5] += f; state_[6] += g; state_[7] += h;
    }

    uint32_t state_[8];
    uint8_t buf_[64];
    size_t buflen_;
    uint64_t totlen_;
};

static std::string format_type_annotation(const std::shared_ptr<AST::TypeAnnotation>& type_ann) {
    if (!type_ann) return "any";
    std::string res;
    if (type_ann->isList) {
        res = "[" + format_type_annotation(type_ann->elementType) + "]";
    } else if (type_ann->isDict) {
        res = "{" + format_type_annotation(type_ann->keyType) + ": " + format_type_annotation(type_ann->valueType) + "}";
    } else if (type_ann->isTuple) {
        res = "(";
        for (size_t i = 0; i < type_ann->tupleTypes.size(); ++i) {
            if (i > 0) res += ", ";
            res += format_type_annotation(type_ann->tupleTypes[i]);
        }
        res += ")";
    } else {
        res = type_ann->typeName.empty() ? "any" : type_ann->typeName;
    }
    if (type_ann->isOptional) {
        res += "?";
    }
    return res;
}
} // anonymous namespace

std::string CompiledModuleMeta::compute_sha256(const std::string& input) {
    SHA256Helper h;
    h.update(reinterpret_cast<const uint8_t*>(input.data()), input.size());
    return h.digest();
}

std::string CompiledModuleMeta::serialize() const {
    std::stringstream ss;
    ss << "module_name=" << module_name << "\n";
    ss << "abi_version=" << abi_version << "\n";
    ss << "runtime_semantics=" << runtime_semantics << "\n";
    ss << "target_triple=" << target_triple << "\n";
    ss << "architecture=" << architecture << "\n";
    ss << "os=" << os << "\n";
    ss << "artifact_kind=" << artifact_kind << "\n";
    ss << "artifact_path=" << artifact_path << "\n";
    ss << "source_hash=" << source_hash << "\n";
    for (const auto& [name, hash] : dependency_hashes) ss << "dependency_hash." << name << "=" << hash << "\n";

    ss << "exports=";
    for (size_t i = 0; i < exports.size(); ++i) {
        if (i > 0) ss << ",";
        ss << exports[i];
    }
    ss << "\n";

    ss << "dependencies=";
    for (size_t i = 0; i < dependencies.size(); ++i) {
        if (i > 0) ss << ",";
        ss << dependencies[i];
    }
    ss << "\n";

    ss << "signatures=";
    size_t sig_idx = 0;
    for (const auto& [name, sig] : export_signatures) {
        if (sig_idx > 0) ss << ";";
        ss << name << ":" << sig;
        sig_idx++;
    }
    ss << "\n";

    return ss.str();
}

bool CompiledModuleMeta::deserialize(const std::string& input, CompiledModuleMeta& out_meta) {
    std::stringstream ss(input);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);

        if (key == "module_name") out_meta.module_name = val;
        else if (key == "abi_version") out_meta.abi_version = val;
        else if (key == "runtime_semantics") out_meta.runtime_semantics = val;
        else if (key == "target_triple") out_meta.target_triple = val;
        else if (key == "architecture") out_meta.architecture = val;
        else if (key == "os") out_meta.os = val;
        else if (key == "artifact_kind") out_meta.artifact_kind = val;
        else if (key == "artifact_path") out_meta.artifact_path = val;
        else if (key == "source_hash") out_meta.source_hash = val;
        else if (key.starts_with("dependency_hash.")) out_meta.dependency_hashes[key.substr(16)] = val;
        else if (key == "exports") {
            out_meta.exports.clear();
            std::stringstream list_ss(val);
            std::string item;
            while (std::getline(list_ss, item, ',')) {
                if (!item.empty()) out_meta.exports.push_back(item);
            }
        } else if (key == "dependencies") {
            out_meta.dependencies.clear();
            std::stringstream list_ss(val);
            std::string item;
            while (std::getline(list_ss, item, ',')) {
                if (!item.empty()) out_meta.dependencies.push_back(item);
            }
        } else if (key == "signatures") {
            out_meta.export_signatures.clear();
            std::stringstream sigs_ss(val);
            std::string pair;
            while (std::getline(sigs_ss, pair, ';')) {
                size_t colon = pair.find(':');
                if (colon != std::string::npos) {
                    out_meta.export_signatures[pair.substr(0, colon)] = pair.substr(colon + 1);
                }
            }
        }
    }
    return !out_meta.module_name.empty() && !out_meta.artifact_kind.empty();
}

bool ModuleManager::register_compiled_module(const CompiledModuleMeta& meta) {
    std::lock_guard<std::mutex> lock(modules_mutex_);
    auto& variants = compiled_modules_[meta.module_name];
    for (const auto& existing : variants) if (existing.artifact_path == meta.artifact_path) return true;
    variants.push_back(meta);
    return true;
}

bool ModuleManager::find_compiled_module(const std::string& module_name, const std::string& target_triple, const std::string& required_kind, CompiledModuleMeta& out_meta) {
    std::lock_guard<std::mutex> lock(modules_mutex_);
    auto it = compiled_modules_.find(module_name);
    if (it == compiled_modules_.end()) return false;

    for (const auto& meta : it->second) {
        if ((target_triple.empty() || meta.target_triple == target_triple) &&
            (required_kind.empty() || meta.artifact_kind == required_kind)) {
            out_meta = meta;
            return true;
        }
    }
    return false;
}

bool ModuleManager::is_artifact_valid(const CompiledModuleMeta& meta, const std::string& current_source_path) {
    if (!fs::exists(meta.artifact_path)) return false;
    if (meta.abi_version != "1.0.0" || meta.runtime_semantics != "regions-v2") return false;
    for (const auto& [name, hash] : meta.dependency_hashes) {
        std::ifstream dependency(find_module_file(name));
        if (!dependency) return false;
        std::stringstream contents;
        contents << dependency.rdbuf();
        if (CompiledModuleMeta::compute_sha256(contents.str()) != hash) return false;
    }
    if (current_source_path.empty() || !fs::exists(current_source_path)) return true;

    // Source modification time vs artifact modification time
    auto src_time = fs::last_write_time(current_source_path);
    auto art_time = fs::last_write_time(meta.artifact_path);
    if (src_time > art_time) return false;

    // Check content hash if current source exists
    std::ifstream src_file(current_source_path);
    if (src_file.is_open()) {
        std::stringstream ss;
        ss << src_file.rdbuf();
        std::string current_hash = CompiledModuleMeta::compute_sha256(ss.str());
        if (!meta.source_hash.empty() && meta.source_hash != "00000000" && meta.source_hash != current_hash) {
            return false;
        }
    }

    return true;
}

CompiledModuleMeta ModuleManager::generate_metadata(
    std::shared_ptr<Module> module,
    const std::string& target,
    const std::string& arch,
    const std::string& artifact_kind,
    const std::string& artifact_path)
{
    CompiledModuleMeta meta;
    if (!module) return meta;

    meta.module_name = module->name;
    if (meta.module_name.length() > 6 && meta.module_name.substr(meta.module_name.length() - 6) == ".index") {
        meta.module_name = meta.module_name.substr(0, meta.module_name.length() - 6);
    }
    meta.abi_version = "1.0.0";
    meta.runtime_semantics = "regions-v2";
    meta.target_triple = arch + "-" + target;
    meta.architecture = arch;
    meta.os = target;
    meta.artifact_kind = artifact_kind;
    meta.artifact_path = artifact_path;
    meta.source_hash = CompiledModuleMeta::compute_sha256(module->source);
    for (const auto& [name, dependency] : get_all_modules()) {
        if (!dependency->path.empty() && name != module->name) {
            meta.dependency_hashes[name] = CompiledModuleMeta::compute_sha256(dependency->source);
        }
    }

    // Dependencies
    for (const auto& dep : module->dependencies) {
        if (std::find(meta.dependencies.begin(), meta.dependencies.end(), dep) == meta.dependencies.end()) {
            meta.dependencies.push_back(dep);
        }
    }

    // Exports and signatures
    std::string mod_prefix = meta.module_name;
    if (module->ast) {
        for (const auto& stmt : module->ast->statements) {
            if (auto func = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
                if (func->visibility == AST::VisibilityLevel::Public) {
                    std::string sym_name = mod_prefix + "." + func->name;
                    meta.exports.push_back(sym_name);
                    
                    std::stringstream sig_ss;
                    sig_ss << "fn(";
                    for (size_t i = 0; i < func->params.size(); ++i) {
                        if (i > 0) sig_ss << ", ";
                        sig_ss << func->params[i].first << ": " << format_type_annotation(func->params[i].second);
                    }
                    sig_ss << "): " << (func->returnType.has_value() ? format_type_annotation(func->returnType.value()) : "nil");
                    meta.export_signatures[sym_name] = sig_ss.str();
                }
            } else if (auto frame = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
                std::string frame_sym = mod_prefix + "." + frame->name;
                meta.exports.push_back(frame_sym);
                meta.export_signatures[frame_sym] = "frame";
                if (frame->init) {
                    meta.exports.push_back(frame_sym + ".init");
                    meta.export_signatures[frame_sym + ".init"] = "constructor";
                }

                for (const auto& method : frame->methods) {
                    if (method->visibility == AST::VisibilityLevel::Public) {
                        std::string method_sym = frame_sym + "." + method->name;
                        meta.exports.push_back(method_sym);

                        std::stringstream sig_ss;
                        sig_ss << "fn(";
                        for (size_t i = 0; i < method->parameters.size(); ++i) {
                            if (i > 0) sig_ss << ", ";
                            sig_ss << method->parameters[i].first << ": " << format_type_annotation(method->parameters[i].second);
                        }
                        sig_ss << "): " << (method->returnType ? format_type_annotation(method->returnType) : "nil");
                        meta.export_signatures[method_sym] = sig_ss.str();
                    }
                }
            } else if (auto var = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
                if (var->visibility == AST::VisibilityLevel::Public || var->isConst) {
                    std::string var_sym = mod_prefix + "." + var->name;
                    meta.exports.push_back(var_sym);
                    meta.export_signatures[var_sym] = var->type.has_value() ? format_type_annotation(var->type.value()) : "any";
                }
            }
        }
    }

    // Returned closures need native dispatch metadata as well as an exported entry.
    for (const auto& name : LIR::FunctionRegistry::getInstance().getFunctionNames()) {
        if (name.starts_with(mod_prefix + ".") && name.find(".__lambda_") != std::string::npos) {
            meta.exports.push_back(name);
            meta.export_signatures[name] = "closure";
        }
    }

    // A facade such as std.collections re-exports implementations from child
    // modules. Their canonical symbols must be discoverable in the library's
    // metadata, just as they are in its native export table.
    for (const auto& [name, child] : get_all_modules()) {
        std::string canonical = name;
        if (canonical.ends_with(".index")) canonical.resize(canonical.size() - 6);
        if (!canonical.starts_with(mod_prefix + ".")) continue;
        auto child_meta = generate_metadata(child, target, arch, artifact_kind, artifact_path);
        for (const auto& symbol : child_meta.exports) {
            if (std::find(meta.exports.begin(), meta.exports.end(), symbol) == meta.exports.end()) {
                meta.exports.push_back(symbol);
                meta.export_signatures[symbol] = child_meta.export_signatures[symbol];
            }
        }
    }
    return meta;
}

void ModuleManager::set_include_dirs(const std::vector<std::string>& dirs) {
    std::lock_guard<std::mutex> lock(modules_mutex_);
    include_dirs_ = dirs;
    if (const char* home = std::getenv("LYMAR_HOME")) include_dirs_.push_back(home);
}

std::string ModuleManager::find_module_file(const std::string& module_path) {
    std::string relPath = module_path;
    std::replace(relPath.begin(), relPath.end(), '.', '/');

    auto check_path = [](const std::string& base) -> std::string {
        if (fs::exists(base + ".lm")) {
            return base + ".lm";
        }
        if (fs::exists(base) && fs::is_directory(base) && fs::exists(base + "/index.lm")) {
            return base + "/index.lm";
        }
        return "";
    };

    // Check directly relative to current directory
    std::string found = check_path(relPath);
    if (!found.empty()) {
        return found;
    }

    // Check configured include directories
    std::vector<std::string> dirs;
    {
        std::lock_guard<std::mutex> lock(modules_mutex_);
        dirs = include_dirs_;
    }
    for (const auto& dir : dirs) {
        std::string candidate = (fs::path(dir) / relPath).string();
        found = check_path(candidate);
        if (!found.empty()) {
            return found;
        }
    }

    return relPath + ".lm";
}

std::shared_ptr<Module> ModuleManager::get_module(const std::string& name) {
    std::lock_guard<std::mutex> lock(modules_mutex_);
    return get_module_unlocked(name);
}

std::string ModuleManager::canonical_symbol(const std::string& qualified_name) {
    size_t dot = qualified_name.rfind('.');
    if (dot == std::string::npos) return qualified_name;
    auto mod = get_module(qualified_name.substr(0, dot));
    if (!mod) return qualified_name;
    auto it = mod->reexport_sources.find(qualified_name.substr(dot + 1));
    if (it == mod->reexport_sources.end()) return qualified_name;
    return it->second + "." + it->first;
}

std::shared_ptr<Module> ModuleManager::get_module_unlocked(const std::string& name) const {
    auto it = modules_.find(name);
    return (it != modules_.end()) ? it->second : nullptr;
}

std::unordered_map<std::string, std::shared_ptr<Module>> ModuleManager::get_all_modules() const {
    std::lock_guard<std::mutex> lock(modules_mutex_);
    return modules_;
}

std::shared_ptr<Module> ModuleManager::load_module(const std::string& module_path) {
    {
        std::lock_guard<std::mutex> lock(modules_mutex_);
        if (modules_.count(module_path)) {
            return modules_[module_path];
        }
    }

    std::string filePath = find_module_file(module_path);
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return nullptr;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    file.close();

    Scanner scanner(source, filePath);
    scanner.scanTokens();
    // Imported modules need semantic ASTs; their concrete syntax trees are never displayed.
    Parser parser(scanner, false);
    auto ast = parser.parse();

    if (!ast || LM::Error::Debugger::hasError()) {
        TypeChecker::failed_modules.insert(module_path);
        size_t last_dot = module_path.find_last_of('.');
        if (last_dot != std::string::npos) {
            TypeChecker::failed_modules.insert(module_path.substr(0, last_dot));
        }
    }

    if (!ast) return nullptr;

    auto module = std::make_shared<Module>();
    module->name = module_path;
    module->path = filePath;
    module->source = source;
    module->ast = ast;

    extract_metadata(module);
    {
        std::lock_guard<std::mutex> lock(modules_mutex_);
        modules_[module_path] = module;
    }
    expand_reexports(module);

    // Discover precompiled module artifacts (.meta files) for module_path
    std::string mod_leaf = module_path;
    if (mod_leaf.ends_with(".index")) mod_leaf.resize(mod_leaf.size() - 6);
    size_t dot_pos = mod_leaf.rfind('.');
    if (dot_pos != std::string::npos) mod_leaf = mod_leaf.substr(dot_pos + 1);

    std::vector<std::string> candidate_paths = {
        "bin/lib" + mod_leaf + ".so",
        "bin/" + mod_leaf + ".so",
        "bin/lib" + mod_leaf + ".a",
        "bin/" + mod_leaf + ".a",
        filePath + ".so",
        filePath + ".a",
        (fs::path(filePath).parent_path() / ("lib" + mod_leaf + ".so")).string(),
        (fs::path(filePath).parent_path() / (mod_leaf + ".so")).string(),
        (fs::path(filePath).parent_path() / ("lib" + mod_leaf + ".a")).string(),
        (fs::path(filePath).parent_path() / (mod_leaf + ".a")).string()
    };

    // Discover the native artifact extensions on each supported host.
    const auto linux_candidates = candidate_paths;
    for (const auto& path : linux_candidates) {
        fs::path candidate(path);
        for (const char* extension : {".dll", ".dylib", ".lib"}) {
            candidate.replace_extension(extension);
            candidate_paths.push_back(candidate.string());
        }
    }
    for (const auto& dir : include_dirs_) {
        for (const char* extension : {".so", ".dll", ".dylib", ".a", ".lib"}) {
            candidate_paths.push_back((fs::path(dir) / "bin" / ("lib" + mod_leaf + extension)).string());
        }
    }

    // Umbrella libraries can also serve imports of a child module directly.
    std::string parent = module_path;
    while (parent.find_last_of('.') != std::string::npos) {
        parent.resize(parent.find_last_of('.'));
        const auto leaf = parent.substr(parent.find_last_of('.') == std::string::npos ? 0 : parent.find_last_of('.') + 1);
        for (const char* extension : {".so", ".dll", ".dylib", ".a", ".lib"}) {
            candidate_paths.push_back((fs::path("bin") / ("lib" + leaf + extension)).string());
            for (const auto& dir : include_dirs_) candidate_paths.push_back((fs::path(dir) / "bin" / ("lib" + leaf + extension)).string());
        }
    }

    for (const auto& cp : candidate_paths) {
        std::string meta_p = cp + ".meta";
        if (fs::exists(meta_p) && fs::exists(cp)) {
            std::ifstream mf(meta_p);
            if (mf.is_open()) {
                std::stringstream mbuf;
                mbuf << mf.rdbuf();
                CompiledModuleMeta meta;
                if (CompiledModuleMeta::deserialize(mbuf.str(), meta)) {
                    // A sidecar describes the binary beside it. Bind to that
                    // candidate so moving an installation cannot retain a path
                    // to the original build machine or checkout.
                    meta.artifact_path = fs::absolute(cp).string();
                    std::string canonical = module_path;
                    if (canonical.ends_with(".index")) canonical.resize(canonical.size() - 6);
                    if ((canonical == meta.module_name || canonical.starts_with(meta.module_name + ".")) &&
                        is_artifact_valid(meta, find_module_file(meta.module_name))) {
                        register_compiled_module(meta);
                    }
                }
            }
        }
    }

    return module;
}

void ModuleManager::extract_metadata(std::shared_ptr<Module> module) {
    if (!module || !module->ast) return;

    for (const auto& stmt : module->ast->statements) {
        if (auto func = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            if (func->visibility == AST::VisibilityLevel::Public) {
                module->public_symbols.insert(func->name);
            }
        } else if (auto var = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
            // Const declarations are always public module-level symbols
            if (var->visibility == AST::VisibilityLevel::Public || var->isConst) {
                module->public_symbols.insert(var->name);
            }
        } else if (auto frame = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
            // Mandate: Frames are always public module-level symbols.
            module->public_symbols.insert(frame->name);
        } else if (auto trait = std::dynamic_pointer_cast<AST::TraitDeclaration>(stmt)) {
            // Mandate: Traits are always public module-level symbols.
            module->public_symbols.insert(trait->name);
        } else if (auto enum_decl = std::dynamic_pointer_cast<AST::EnumDeclaration>(stmt)) {
            // Mandate: Enums are always public module-level symbols.
            module->public_symbols.insert(enum_decl->name);
        } else if (auto type_decl = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) {
            // Type aliases are always public module-level symbols
            module->public_symbols.insert(type_decl->name);
        } else if (auto import_stmt = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) {
            module->dependencies.push_back(import_stmt->modulePath);
        }
    }
}

void ModuleManager::expand_reexports(std::shared_ptr<Module> module) {
    if (!module || !module->ast) return;

    // Guards against `pub import` cycles (A re-exports B which re-exports A).
    static thread_local std::set<std::string> expanding;
    if (!expanding.insert(module->name).second) return;

    auto declared_name = [](const std::shared_ptr<AST::Statement>& stmt) -> std::string {
        if (auto f = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) return f->name;
        if (auto v = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) return v->name;
        if (auto fr = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) return fr->name;
        if (auto t = std::dynamic_pointer_cast<AST::TraitDeclaration>(stmt)) return t->name;
        if (auto e = std::dynamic_pointer_cast<AST::EnumDeclaration>(stmt)) return e->name;
        if (auto td = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) return td->name;
        return "";
    };

    for (const auto& stmt : module->ast->statements) {
        auto imp = std::dynamic_pointer_cast<AST::ImportStatement>(stmt);
        if (!imp || imp->visibility != AST::VisibilityLevel::Public) continue;
        // Re-exports must name their symbols explicitly (`show A, B`); there is no
        // wildcard re-export, so a module cannot widen its API by accident.
        if (!imp->filter || imp->filter->type != AST::ImportFilterType::Show) continue;

        auto source = load_module(imp->modulePath);
        if (!source || !source->ast) continue;

        for (const auto& id : imp->filter->identifiers) {
            // Only symbols the source module itself exposes can be re-exported, and a
            // local declaration always wins over a re-export of the same name.
            if (!source->public_symbols.count(id)) continue;
            if (module->public_symbols.count(id)) continue;

            std::shared_ptr<AST::Statement> found;
            for (const auto& s : source->ast->statements) {
                if (declared_name(s) == id) { found = s; break; }
            }
            if (!found) {
                for (const auto& s : source->reexports) {
                    if (declared_name(s) == id) { found = s; break; }
                }
            }
            if (!found) continue;
            module->reexports.push_back(found);
            auto chained = source->reexport_sources.find(id);
            module->reexport_sources[id] = (chained != source->reexport_sources.end()) ? chained->second : imp->modulePath;
            module->public_symbols.insert(id);
        }
    }

    expanding.erase(module->name);
}

void ModuleManager::resolve_all(std::shared_ptr<AST::Program> root_program, const std::string& root_path) {
    if (!root_program) return;

    // Register root program as a module
    auto root_module = std::make_shared<Module>();
    root_module->name = root_path;
    root_module->ast = root_program;
    extract_metadata(root_module);
    {
        std::lock_guard<std::mutex> lock(modules_mutex_);
        modules_[root_path] = root_module;
    }

    std::vector<std::string> worklist;
    for (const auto& stmt : root_program->statements) {
        if (auto imp = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) {
            worklist.push_back(imp->modulePath);
        }
    }

    std::set<std::string> visited;
    while (!worklist.empty()) {
        std::vector<std::string> next_worklist;

        for (const auto& path : worklist) {
            if (!visited.insert(path).second) continue;

            std::shared_ptr<Module> mod = nullptr;
            {
                std::lock_guard<std::mutex> lock(modules_mutex_);
                auto it = modules_.find(path);
                if (it != modules_.end()) mod = it->second;
            }

            if (!mod) {
                mod = load_module(path);
            }

            if (mod) {
                for (const auto& dep : mod->dependencies) {
                    next_worklist.push_back(dep);
                }
            }
        }

        worklist = std::move(next_worklist);
    }
}

std::set<std::string> ModuleManager::filter_symbols(std::shared_ptr<Module> module, const std::optional<AST::ImportFilter>& filter) {
    if (!module) return {};
    if (!filter) return module->public_symbols;

    std::set<std::string> result;
    if (filter->type == AST::ImportFilterType::Show) {
        for (const auto& id : filter->identifiers) {
            if (module->public_symbols.count(id)) result.insert(id);
        }
    } else { // Hide
        result = module->public_symbols;
        for (const auto& id : filter->identifiers) result.erase(id);
    }
    return result;
}

std::vector<std::string> ModuleManager::get_topological_order() {
    std::vector<std::string> order;
    std::unordered_map<std::string, int> state;

    std::function<bool(const std::string&)> visit = [&](const std::string& name) {
        if (state[name] == 1) return false;
        if (state[name] == 2) return true;
        state[name] = 1;
        auto mod = get_module_unlocked(name);
        if (mod) {
            for (const auto& dep : mod->dependencies) {
                if (!visit(dep)) return false;
            }
        }
        state[name] = 2;
        order.push_back(name);
        return true;
    };

    std::lock_guard<std::mutex> lock(modules_mutex_);
    for (auto const& [name, mod] : modules_) {
        if (state[name] == 0) visit(name);
    }
    return order;
}

bool ModuleManager::has_circular_dependencies() {
    std::unordered_map<std::string, int> state;
    std::function<bool(const std::string&)> check = [&](const std::string& name) {
        if (state[name] == 1) return true;
        if (state[name] == 2) return false;
        state[name] = 1;
        auto mod = get_module_unlocked(name);
        if (mod) {
            for (const auto& dep : mod->dependencies) {
                if (check(dep)) return true;
            }
        }
        state[name] = 2;
        return false;
    };

    std::lock_guard<std::mutex> lock(modules_mutex_);
    for (auto const& [name, mod] : modules_) {
        if (state[name] == 0 && check(name)) return true;
    }
    return false;
}

} // namespace Frontend
} // namespace LM
