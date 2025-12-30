#include "function_registry.hh"
#include <stdexcept>
#include <iostream>

namespace LIR {

// Singleton implementation
FunctionRegistry& FunctionRegistry::getInstance() {
    static FunctionRegistry instance;
    return instance;
}

// Register LIR functions
void FunctionRegistry::registerFunction(const std::string& name, std::unique_ptr<LIR_Function> function) {
    if (!function) {
        throw std::runtime_error("Cannot register null function: " + name);
    }
    
    lir_functions_[name] = std::move(function);
    // Debug output removed for cleaner execution
}

// Function lookup
bool FunctionRegistry::hasFunction(const std::string& name) const {
    return lir_functions_.find(name) != lir_functions_.end();
}

LIR_Function* FunctionRegistry::getFunction(const std::string& name) const {
    auto it = lir_functions_.find(name);
    if (it != lir_functions_.end()) {
        return it->second.get();
    }
    return nullptr;
}

// Get all registered function names
std::vector<std::string> FunctionRegistry::getFunctionNames() const {
    std::vector<std::string> names;
    names.reserve(lir_functions_.size());
    for (const auto& pair : lir_functions_) {
        names.push_back(pair.first);
    }
    return names;
}

// Clear all functions (for testing)
void FunctionRegistry::clear() {
    lir_functions_.clear();
}

} // namespace LIR
