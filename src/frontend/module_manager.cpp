#include "module_manager.hh"
#include "scanner.hh"
#include "parser.hh"
#include "type_checker.hh"
#include "../error/debugger.hh"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <functional>
#include <future>
#include <iomanip>

#include <filesystem>

namespace LM {
namespace Frontend {

namespace fs = std::filesystem;

std::string CompiledModuleMeta::serialize() const {
    std::stringstream ss;
    ss << "module_name=" << module_name << "\n";
    ss << "abi_version=" << abi_version << "\n";
    ss << "target_triple=" << target_triple << "\n";
    ss << "architecture=" << architecture << "\n";
    ss << "os=" << os << "\n";
    ss << "artifact_kind=" << artifact_kind << "\n";
    ss << "artifact_path=" << artifact_path << "\n";
    ss << "source_hash=" << source_hash << "\n";

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
        else if (key == "target_triple") out_meta.target_triple = val;
        else if (key == "architecture") out_meta.architecture = val;
        else if (key == "os") out_meta.os = val;
        else if (key == "artifact_kind") out_meta.artifact_kind = val;
        else if (key == "artifact_path") out_meta.artifact_path = val;
        else if (key == "source_hash") out_meta.source_hash = val;
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
    compiled_modules_[meta.module_name].push_back(meta);
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

bool ModuleManager::is_artifact_valid(const CompiledModuleMeta& meta, const std::string& current_source_path) const {
    if (!fs::exists(meta.artifact_path)) return false;
    if (current_source_path.empty() || !fs::exists(current_source_path)) return true;

    // Source modification time vs artifact modification time
    auto src_time = fs::last_write_time(current_source_path);
    auto art_time = fs::last_write_time(meta.artifact_path);
    if (src_time > art_time) return false;

    return true;
}

void ModuleManager::set_include_dirs(const std::vector<std::string>& dirs) {
    std::lock_guard<std::mutex> lock(modules_mutex_);
    include_dirs_ = dirs;
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
    Parser parser(scanner);
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
