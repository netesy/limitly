// SymbolDatabase implementation for Limitly compiler
#include "symbol_database.hh"

namespace LM {
namespace Frontend {

// Default constructor
SymbolDatabase::SymbolDatabase() = default;

// Register a new symbol; returns false if already exists
bool SymbolDatabase::register_symbol(const Symbol &sym) {
    const auto &key = sym.fully_qualified_name;
    auto [it, inserted] = symbols_.emplace(key, sym);
    return inserted;
}

// Lookup a symbol by fully qualified name
std::optional<Symbol> SymbolDatabase::lookup(const std::string &fq_name) const {
    auto it = symbols_.find(fq_name);
    if (it != symbols_.end()) {
        return it->second;
    }
    return std::nullopt;
}

// Return all stored symbols (read‑only reference)
const std::unordered_map<std::string, Symbol> &SymbolDatabase::all_symbols() const {
    return symbols_;
}

} // namespace Frontend
} // namespace LM
