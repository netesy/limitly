#ifndef DECLARATION_RESOLVER_H
#define DECLARATION_RESOLVER_H

#include "symbol_database.hh"
#include "module_manager.hh"
#include "ast.hh"

namespace LM {
namespace Frontend {

// Walks the AST of each loaded module and registers global symbols (frames, traits, functions)
class DeclarationResolver {
public:
    explicit DeclarationResolver(SymbolDatabase& db) : symbol_db_(db) {}

    // Resolve declarations for all modules managed by ModuleManager
    void resolve_all(ModuleManager& manager);

private:
    SymbolDatabase& symbol_db_;

    void process_module(const std::string& module_name, const std::shared_ptr<AST::Program>& program);
    void process_statement(const std::string& module_name, const std::shared_ptr<AST::Statement>& stmt);
};

} // namespace Frontend
} // namespace LM

#endif // DECLARATION_RESOLVER_H
