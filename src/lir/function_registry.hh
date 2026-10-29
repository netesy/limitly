#ifndef FUNCTION_REGISTRY_H
#define FUNCTION_REGISTRY_H

#include "lir.hh"
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

namespace LM {
namespace LIR {


// LIR Function Registry - manages LIR functions for JIT compilation
class FunctionRegistry {
public:
    // Singleton pattern
    static FunctionRegistry& getInstance();
    
    // Register LIR functions
    void registerFunction(const std::string& name, std::unique_ptr<LIR_Function> function);
    void registerVerifiedFunction(const std::string& name, std::unique_ptr<LIR_Function> function) {
        if (function) lir_functions_[name] = std::move(function);
    }
    
    // Function lookup
    bool hasFunction(const std::string& name) const;
    LIR_Function* getFunction(const std::string& name) const;
    
    // Get all registered function names
    std::vector<std::string> getFunctionNames() const;
    
    // Clear all functions (for testing)
    void clear();

    // Drops a single function. Compile-time (stage-0) evaluation registers the staged fn it
    // is about to run and removes it again, so a compile-time-only function never becomes
    // part of the program that is generated, cached, or exported afterwards.
    void erase(const std::string& name);
    
private:
    FunctionRegistry() = default;
    ~FunctionRegistry() = default;
    FunctionRegistry(const FunctionRegistry&) = delete;
    FunctionRegistry& operator=(const FunctionRegistry&) = delete;
    
    // Storage for LIR functions
    std::unordered_map<std::string, std::unique_ptr<LIR_Function>> lir_functions_;
};

} // namespace LIR
} // namespace LM

#endif // FUNCTION_REGISTRY_H
