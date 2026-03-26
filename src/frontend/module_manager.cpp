#include "module_manager.hh"
#include "scanner.hh"
#include "parser.hh"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <functional>
#include <future>

namespace LM {
namespace Frontend {

std::string ModuleManager::find_module_file(const std::string& module_path) {
    std::string filePath = module_path;
    std::replace(filePath.begin(), filePath.end(), '.', '/');
    filePath += ".lm";
    return filePath;
}

std::shared_ptr<Module> ModuleManager::get_module(const std::string& name) {
    std::lock_guard<std::mutex> lock(modules_mutex_);
    return get_module_unlocked(name);
}

std::shared_ptr<Module> ModuleManager::get_module_unlocked(const std::string& name) const {
    auto it = modules_.find(name);
    return (it != modules_.end()) ? it->second : nullptr;
}

std::unordered_map<std::string, std::shared_ptr<Module>> ModuleManager::get_all_modules() {
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
            if (var->visibility == AST::VisibilityLevel::Public) {
                module->public_symbols.insert(var->name);
            }
        } else if (auto frame = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
            module->public_symbols.insert(frame->name);
        } else if (auto import_stmt = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) {
            module->dependencies.push_back(import_stmt->modulePath);
        }
    }
}

void ModuleManager::resolve_all(std::shared_ptr<AST::Program> root_program, const std::string& root_path) {
    if (!root_program) return;

    std::vector<std::string> worklist;
    for (const auto& stmt : root_program->statements) {
        if (auto imp = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) {
            worklist.push_back(imp->modulePath);
        }
    }

    std::set<std::string> processing;
    while (!worklist.empty()) {
        std::vector<std::future<std::shared_ptr<Module>>> futures;
        std::vector<std::string> next_worklist;

        for (const auto& path : worklist) {
            {
                std::lock_guard<std::mutex> lock(modules_mutex_);
                if (modules_.count(path) || processing.count(path)) continue;
            }
            processing.insert(path);
            futures.push_back(std::async(std::launch::async, &ModuleManager::load_module, this, path));
        }

        for (auto& f : futures) {
            auto mod = f.get();
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
