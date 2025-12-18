#include "function_registry.hh"
#include "generator.hh"
#include "../backend/vm/vm.hh"
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
    std::cout << "[DEBUG] LIR Registry: Registered LIR function '" << name << "'" << std::endl;
}

void FunctionRegistry::registerBuiltinFunction(const std::string& name, std::function<ValuePtr(const std::vector<ValuePtr>&)> impl) {
    if (!impl) {
        throw std::runtime_error("Cannot register null builtin implementation: " + name);
    }
    
    builtin_functions_[name] = impl;
    std::cout << "[DEBUG] LIR Registry: Registered builtin function '" << name << "'" << std::endl;
}

// Function lookup
bool FunctionRegistry::hasFunction(const std::string& name) const {
    return lir_functions_.find(name) != lir_functions_.end() ||
           builtin_functions_.find(name) != builtin_functions_.end() ||
           user_functions_.find(name) != user_functions_.end() ||
           native_functions_.find(name) != native_functions_.end();
}

LIR_Function* FunctionRegistry::getFunction(const std::string& name) const {
    auto it = lir_functions_.find(name);
    return (it != lir_functions_.end()) ? it->second.get() : nullptr;
}

std::function<ValuePtr(const std::vector<ValuePtr>&)> FunctionRegistry::getBuiltinImplementation(const std::string& name) const {
    auto it = builtin_functions_.find(name);
    return (it != builtin_functions_.end()) ? it->second : nullptr;
}

// Function calling
ValuePtr FunctionRegistry::callFunction(const std::string& name, const std::vector<ValuePtr>& args) {
    // First check for LIR functions
    if (auto lir_func = getFunction(name)) {
        std::cout << "[DEBUG] LIR Registry: Calling LIR function '" << name << "'" << std::endl;
        
        // For LIR functions, we need to execute them through the JIT
        // Check if we have a user-defined function with AST
        auto user_it = user_functions_.find(name);
        if (user_it != user_functions_.end()) {
            std::cout << "[DEBUG] LIR Registry: Executing user-defined function '" << name << "'" << std::endl;
            return user_it->second->execute(args);
        }
        
        // Fallback: return 0
        auto int_type = std::make_shared<Type>(TypeTag::Int);
        return std::make_shared<Value>(int_type, static_cast<int64_t>(0));
    }
    
    // Check for builtin functions
    if (auto builtin_impl = getBuiltinImplementation(name)) {
        std::cout << "[DEBUG] LIR Registry: Calling builtin function '" << name << "'" << std::endl;
        return builtin_impl(args);
    }
    
    // Check for user-defined functions
    auto user_it = user_functions_.find(name);
    if (user_it != user_functions_.end()) {
        std::cout << "[DEBUG] LIR Registry: Calling user-defined function '" << name << "'" << std::endl;
        return user_it->second->execute(args);
    }
    
    // Check for native functions
    auto native_it = native_functions_.find(name);
    if (native_it != native_functions_.end()) {
        std::cout << "[DEBUG] LIR Registry: Calling native function '" << name << "'" << std::endl;
        return native_it->second->execute(args);
    }
    
    throw std::runtime_error("Function not found: " + name);
}

// Integration with existing function system
void FunctionRegistry::registerUserDefinedFunction(const std::shared_ptr<backend::UserDefinedFunction>& userFunc) {
    if (!userFunc) {
        throw std::runtime_error("Cannot register null user-defined function");
    }
    
    user_functions_[userFunc->getSignature().name] = userFunc;
    std::cout << "[DEBUG] LIR Registry: Registered user-defined function '" << userFunc->getSignature().name << "'" << std::endl;
}

void FunctionRegistry::registerNativeFunction(const std::shared_ptr<backend::NativeFunction>& nativeFunc) {
    if (!nativeFunc) {
        throw std::runtime_error("Cannot register null native function");
    }
    
    native_functions_[nativeFunc->getSignature().name] = nativeFunc;
    std::cout << "[DEBUG] LIR Registry: Registered native function '" << nativeFunc->getSignature().name << "'" << std::endl;
}

// Get all registered function names
std::vector<std::string> FunctionRegistry::getFunctionNames() const {
    std::vector<std::string> names;
    
    for (const auto& pair : lir_functions_) {
        names.push_back(pair.first);
    }
    for (const auto& pair : builtin_functions_) {
        names.push_back(pair.first);
    }
    for (const auto& pair : user_functions_) {
        names.push_back(pair.first);
    }
    for (const auto& pair : native_functions_) {
        names.push_back(pair.first);
    }
    
    return names;
}

// Clear all functions
void FunctionRegistry::clear() {
    lir_functions_.clear();
    builtin_functions_.clear();
    user_functions_.clear();
    native_functions_.clear();
}

// FunctionManager implementation
void FunctionManager::registerLIRFunction(const std::string& name, std::unique_ptr<LIR_Function> function) {
    FunctionRegistry::getInstance().registerFunction(name, std::move(function));
}

ValuePtr FunctionManager::generateFunctionCall(const std::string& name, const std::vector<ValuePtr>& args) {
    return FunctionRegistry::getInstance().callFunction(name, args);
}

bool FunctionManager::isFunctionRegistered(const std::string& name) {
    return FunctionRegistry::getInstance().hasFunction(name);
}

} // namespace LIR
