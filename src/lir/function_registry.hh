#ifndef FUNCTION_REGISTRY_H
#define FUNCTION_REGISTRY_H

#include "lir.hh"
#include "../backend/functions.hh"
#include "../backend/value.hh"
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
    void registerBuiltinFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> impl);
    
    // Function lookup
    bool hasFunction(const std::string& name) const;
    LIR_Function* getFunction(const std::string& name) const;
    std::function<ValuePtr(const std::vector<ValuePtr>&)> getBuiltinImplementation(const std::string& name) const;
    
    // Function calling
    ValuePtr callFunction(const std::string& name, const std::vector<ValuePtr>& args);
    
    // Integration with existing function system
    void registerUserDefinedFunction(const std::shared_ptr<backend::UserDefinedFunction>& userFunc);
    void registerNativeFunction(const std::shared_ptr<backend::NativeFunction>& nativeFunc);
    
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
    
    // Storage for builtin function implementations
    std::unordered_map<std::string, std::function<ValuePtr(const std::vector<ValuePtr>&)>> builtin_functions_;
    
    // References to existing function system
    std::unordered_map<std::string, std::shared_ptr<backend::UserDefinedFunction>> user_functions_;
    std::unordered_map<std::string, std::shared_ptr<backend::NativeFunction>> native_functions_;
};

// Helper class for integrating function registry with LIR generator
class FunctionManager {
public:
    // Register a function from LIR generator
    static void registerLIRFunction(const std::string& name, std::unique_ptr<LIR_Function> function);
    
    // Generate LIR for a function call
    static ValuePtr generateFunctionCall(const std::string& name, const std::vector<ValuePtr>& args);
    
    // Check if a function is registered
    static bool isFunctionRegistered(const std::string& name);
};

} // namespace LIR

#endif // FUNCTION_REGISTRY_H
