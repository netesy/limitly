#include "declaration_resolver.hh"

namespace LM {
namespace Frontend {

void DeclarationResolver::resolve_all(ModuleManager& manager) {
    // Iterate over all loaded modules and process each AST program
    for (const auto& [module_name, module_ptr] : manager.get_all_modules()) {
        if (!module_ptr || !module_ptr->ast) continue;
        process_module(module_name, module_ptr->ast);
    }
}

void DeclarationResolver::process_module(const std::string& module_name, const std::shared_ptr<AST::Program>& program) {
    // Iterate top-level statements in the program
    for (const auto& stmt : program->statements) {
        process_statement(module_name, stmt);
    }
}

void DeclarationResolver::process_statement(const std::string& module_name, const std::shared_ptr<AST::Statement>& stmt) {
    // Handle only declarations we care about: frames, traits, functions, type aliases
    // The AST node types are assumed to be identifiable via dynamic_cast or type enum.
    // For simplicity, we use a type tag (stmt->node_type) – adapt as needed.
    // This stub demonstrates registration; actual compiler may need more detailed handling.
    if (!stmt) return;

    // Updated handling using dynamic_cast to identify statement types
    if (auto fd = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
        Symbol sym;
        sym.name = fd->name;
        sym.fully_qualified_name = module_name + "." + fd->name;
        sym.kind = SymbolKind::Frame;
        sym.module = module_name;
        symbol_db_.register_symbol(sym);
    } else if (auto td = std::dynamic_pointer_cast<AST::TraitDeclaration>(stmt)) {
        Symbol sym;
        sym.name = td->name;
        sym.fully_qualified_name = module_name + "." + td->name;
        sym.kind = SymbolKind::Trait;
        sym.module = module_name;
        symbol_db_.register_symbol(sym);
    } else if (auto fd = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        Symbol sym;
        sym.name = fd->name;
        sym.fully_qualified_name = module_name + "." + fd->name;
        sym.kind = SymbolKind::Function;
        sym.module = module_name;
        symbol_db_.register_symbol(sym);
    } else if (auto ad = std::dynamic_pointer_cast<AST::AliasDeclaration>(stmt)) {
        Symbol sym;
        sym.name = ad->name;
        sym.fully_qualified_name = module_name + "." + ad->name;
        sym.kind = SymbolKind::Alias;
        sym.module = module_name;
        symbol_db_.register_symbol(sym);
    } else {
        // Other statements are ignored for global symbol collection.
    }
}

} // namespace Frontend
} // namespace LM
