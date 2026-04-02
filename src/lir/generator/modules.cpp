#include "../generator.hh"
#include "../functions.hh"
#include "../../frontend/module_manager.hh"
#include "../function_registry.hh"
#include "../builtin_functions.hh"
#include "../../frontend/ast.hh"
#include "../../frontend/scanner.hh"
#include <algorithm>
#include <map>
#include <limits>

using namespace LM::LIR;

namespace LM {
namespace LIR {

void Generator::collect_module_signatures(LM::Frontend::AST::Program& program) {
    auto& manager = LM::Frontend::ModuleManager::getInstance();
    for (const auto& [path, module] : manager.get_all_modules()) {
        if (path == "root") continue;

        std::string init_func_name = path + ".__init__";
        FunctionInfo init_info;
        init_info.name = init_func_name;
        init_info.param_count = 0;
        init_info.visibility = LM::Frontend::AST::VisibilityLevel::Public;
        function_table_[init_func_name] = std::move(init_info);
    }
}


void Generator::register_module_symbol(const std::string& module_name, const std::string& symbol_name, 
                                       LM::Frontend::AST::VisibilityLevel visibility, bool is_function, size_t param_count) {
    ModuleSymbolInfo symbol_info;
    symbol_info.qualified_name = module_name + "::" + symbol_name;
    symbol_info.module_name = module_name;
    symbol_info.symbol_name = symbol_name;
    symbol_info.visibility = visibility;
    symbol_info.is_function = is_function;
    symbol_info.is_variable = !is_function;
    symbol_info.param_count = param_count;
    
    module_symbol_table_[symbol_info.qualified_name] = symbol_info;
}


Generator::ModuleSymbolInfo* Generator::resolve_module_symbol(const std::string& qualified_name) {
    auto it = module_symbol_table_.find(qualified_name);
    if (it != module_symbol_table_.end()) {
        return &it->second;
    }
    return nullptr;
}


bool Generator::can_access_module_symbol(const ModuleSymbolInfo& symbol, const std::string& from_module) {
    // Public symbols are always accessible
    if (symbol.visibility == LM::Frontend::AST::VisibilityLevel::Public) {
        return true;
    }
    
    // Protected and private symbols are only accessible from the same module
    return from_module == symbol.module_name;
}


void Generator::emit_module_stmt(LM::Frontend::AST::ModuleDeclaration& stmt) {
    // Module declarations are handled in Pass 0 (signature collection)
    // This function is called during Pass 2 but doesn't emit LIR
    // since modules are handled through the symbol resolution system
}

// Variable capture analysis for concurrent statements

} // namespace LIR
} // namespace LM
