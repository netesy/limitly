// SymbolDatabase for Limitly compiler
#ifndef SYMBOL_DATABASE_H
#define SYMBOL_DATABASE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

namespace LM {
namespace Frontend {

enum class SymbolKind {
    Frame,
    Trait,
    Function,
    Alias
};

struct Symbol {
    std::string name;                     // Simple name
    std::string fully_qualified_name;    // e.g., std.collections.Vector
    SymbolKind kind;
    std::string module;                  // Module where defined
    // Additional metadata can be added as needed
};

class SymbolDatabase {
public:
    // Register a new symbol; returns false if already exists
    bool register_symbol(const Symbol& sym) {
        const auto& key = sym.fully_qualified_name;
        auto [it, inserted] = symbols_.emplace(key, sym);
        return inserted;
    }

    // Lookup by fully qualified name
    std::optional<Symbol> lookup(const std::string& fq_name) const {
        auto it = symbols_.find(fq_name);
        if (it != symbols_.end()) return it->second;
        return std::nullopt;
    }

    // Retrieve all symbols (useful for debugging)
    const std::unordered_map<std::string, Symbol>& all_symbols() const { return symbols_; }

private:
    std::unordered_map<std::string, Symbol> symbols_; // key: fully qualified name
};

} // namespace Frontend
} // namespace LM

#endif // SYMBOL_DATABASE_H
