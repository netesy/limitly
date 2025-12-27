#ifndef FUNCTION_REGISTRY_H
#define FUNCTION_REGISTRY_H

#include "lir.hh"
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

namespace LIR {

// LIR Function Registry - manages LIR functions for JIT compilation
class FunctionRegistry {
public:
    // Singleton pattern
    static FunctionRegistry& getInstance();
    
    // Register LIR functions
    void registerFunction(const std::string& name, std::unique_ptr<LIR_Function> function);
    
    // Function lookup
    bool hasFunction(const std::string& name) const;
    LIR_Function* getFunction(const std::string& name) const;
    
    // Get all registered function names
    std::vector<std::string> getFunctionNames() const;
    
    // Clear all functions (for testing)
    void clear();
    
private:
    FunctionRegistry() = default;
    ~FunctionRegistry() = default;
    FunctionRegistry(const FunctionRegistry&) = delete;
    FunctionRegistry& operator=(const FunctionRegistry&) = delete;
    
    // Storage for LIR functions
    std::unordered_map<std::string, std::unique_ptr<LIR_Function>> lir_functions_;
};

} // namespace LIR

#endif // FUNCTION_REGISTRY_H
