#include "functions.hh"
#include "function_registry.hh"
#include "lir.hh"
#include "../backend/types.hh"
#include <iostream>

namespace LIR {

// Helper function to convert TypeTag to LIR::Type
Type typeTagToLIRType(TypeTag tag) {
    switch (tag) {
        case TypeTag::Int:
        case TypeTag::Int32:
            return Type::I32;
        case TypeTag::Int64:
            return Type::I64;
        case TypeTag::Float64:
            return Type::F64;
        case TypeTag::Bool:
            return Type::Bool;
        case TypeTag::Nil:
            return Type::Void;
        default:
            return Type::I32; // Default to I32 for unknown types
    }
}

// LIRFunction implementation
LIRFunction::LIRFunction(const std::string& name, 
                       const std::vector<LIRParameter>& params,
                       std::optional<Type> returnType,
                       LIRFunctionBody body)
    : name_(name), parameters_(params), returnType_(returnType), body_(body) {
    
    // Create LIR-specific signature
    signature_.name = name_;
    signature_.parameters = params;
    signature_.returnType = returnType;
    signature_.isAsync = false;
}

ValuePtr LIRFunction::execute(const std::vector<ValuePtr>& args) {
    if (!body_) {
        throw std::runtime_error("No implementation for LIR function: " + name_);
    }
    
    // Validate argument count
    if (args.size() != parameters_.size()) {
        throw std::runtime_error("Argument count mismatch for LIR function: " + name_ + 
                              " (expected " + std::to_string(parameters_.size()) + 
                              ", got " + std::to_string(args.size()) + ")");
    }
    
    // Execute the function body
    return body_(args);
}

bool LIRFunction::isNative() const {
    return false;  // LIR functions are not native C++ functions
}

const LIRFunctionSignature& LIRFunction::getSignature() const {
    return signature_;
}

// LIRFunctionManager implementation
LIRFunctionManager& LIRFunctionManager::getInstance() {
    static LIRFunctionManager instance;
    return instance;
}

void LIRFunctionManager::initialize() {
    if (initialized_) {
        return;
    }
    
    // Initialize builtins first
    BuiltinUtils::initializeBuiltins();
    
    // Register builtin functions with the function registry for JIT compilation
    auto& registry = FunctionRegistry::getInstance();
    auto builtin_names = BuiltinUtils::getBuiltinFunctionNames();
    
    for (const auto& name : builtin_names) {
        // Create a simple LIR function wrapper for builtins
        auto lir_func = std::make_unique<LIR_Function>("builtin_" + name, 0);
        lir_func->name = name;
        lir_func->param_count = 0; // Will be determined at call time
        
        // Add a simple call instruction to the builtin
        LIR_Inst call_inst(LIR_Op::Call, 0, 0, 0, 0);
        call_inst.dst = 0; // Return value in register 0
        call_inst.a = 0;   // Function index (will be resolved)
        call_inst.b = 0;   // Argument count (will be resolved)
        lir_func->instructions.push_back(call_inst);
        
        // Add return instruction
        LIR_Inst ret_inst(LIR_Op::Return, 0, 0, 0, 0);
        ret_inst.a = 0; // Return register 0
        lir_func->instructions.push_back(ret_inst);
        
        registry.registerFunction(name, std::move(lir_func));
    }
    
    initialized_ = true;
}

void LIRFunctionManager::registerFunction(std::shared_ptr<LIRFunction> function) {
    if (!function) {
        throw std::runtime_error("Cannot register null LIR function");
    }
    
    std::string name = function->getName();
    functions_[name] = function;
    
    // Also register with the LIR function registry for JIT compilation
    auto& registry = FunctionRegistry::getInstance();
    
    // Convert LIRFunction to LIR_Function for registry
    auto lir_func = std::make_unique<LIR_Function>(name, function->getParameters().size());
    lir_func->name = name;
    lir_func->param_count = function->getParameters().size();
    
    // Set up register types for parameters
    for (size_t i = 0; i < function->getParameters().size(); ++i) {
        lir_func->register_types[i] = function->getParameters()[i].type;
    }
    
    // Set return type if available
    if (function->getReturnType()) {
        lir_func->register_types[0] = *function->getReturnType(); // Return value in register 0
    }
    
    // Copy instructions if available
    lir_func->instructions = function->getInstructions();
    
    registry.registerFunction(name, std::move(lir_func));
}

std::shared_ptr<LIRFunction> LIRFunctionManager::getFunction(const std::string& name) {
    auto it = functions_.find(name);
    return (it != functions_.end()) ? it->second : nullptr;
}

bool LIRFunctionManager::hasFunction(const std::string& name) const {
    return functions_.find(name) != functions_.end();
}

std::vector<std::string> LIRFunctionManager::getFunctionNames() const {
    std::vector<std::string> names;
    for (const auto& [name, function] : functions_) {
        names.push_back(name);
    }
    return names;
}

size_t LIRFunctionManager::getFunctionIndex(const std::string& name) const {
    auto it = functions_.find(name);
    if (it == functions_.end()) {
        return SIZE_MAX; // Not found
    }
    
    // Calculate index by iterating through the map
    size_t index = 0;
    for (const auto& [func_name, function] : functions_) {
        if (func_name == name) {
            return index;
        }
        index++;
    }
    
    return SIZE_MAX; // Should not reach here
}

std::shared_ptr<LIRFunction> LIRFunctionManager::createFunction(
    const std::string& name,
    const std::vector<LIRParameter>& params,
    std::optional<Type> returnType,
    LIRFunctionBody body) {
    
    auto function = std::make_shared<LIRFunction>(name, params, returnType, body);
    registerFunction(function);
    return function;
}

std::shared_ptr<LIRFunction> LIRFunctionManager::createArithmeticFunction(
    const std::string& name,
    const std::vector<TypeTag>& paramTypes,
    TypeTag returnType,
    std::function<ValuePtr(const std::vector<ValuePtr>&)> impl) {
    
    std::vector<LIRParameter> params;
    for (size_t i = 0; i < paramTypes.size(); i++) {
        LIRParameter param;
        param.name = "arg" + std::to_string(i);
        param.type = typeTagToLIRType(paramTypes[i]);
        params.push_back(param);
    }
    
    auto return_type = typeTagToLIRType(returnType);
    auto body = [impl](const std::vector<ValuePtr>& args) -> ValuePtr {
        return impl(args);
    };
    
    return createFunction(name, params, return_type, body);
}

// FunctionUtils implementation
namespace FunctionUtils {
    
void initializeFunctions() {
    LIRFunctionManager::getInstance().initialize();
}

bool isFunction(const std::string& name) {
    return BuiltinUtils::isBuiltinFunction(name) || 
           LIRFunctionManager::getInstance().hasFunction(name);
}

ValuePtr callFunction(const std::string& name, const std::vector<ValuePtr>& args) {
    // First try builtin functions
    if (BuiltinUtils::isBuiltinFunction(name)) {
        return BuiltinUtils::callBuiltinFunction(name, args);
    }
    
    // Then try user-defined functions
    auto func = LIRFunctionManager::getInstance().getFunction(name);
    if (func) {
        return func->execute(args);
    }
    
    throw std::runtime_error("LIR function not found: " + name);
}

std::vector<std::string> getAllFunctionNames() {
    std::vector<std::string> names;
    
    // Add builtin function names
    auto builtin_names = BuiltinUtils::getBuiltinFunctionNames();
    names.insert(names.end(), builtin_names.begin(), builtin_names.end());
    
    // Add user-defined function names
    auto user_names = LIRFunctionManager::getInstance().getFunctionNames();
    names.insert(names.end(), user_names.begin(), user_names.end());
    
    return names;
}

} // namespace FunctionUtils

// Helper to create simple arithmetic functions
std::shared_ptr<LIRFunction> createBinaryOpFunction(
    const std::string& name,
    TypeTag paramType,
    TypeTag returnType,
    std::function<ValuePtr(ValuePtr, ValuePtr)> operation) {
    
    return LIRFunctionManager::getInstance().createArithmeticFunction(
        name,
        std::vector<TypeTag>{paramType, paramType},
        returnType,
        [operation](const std::vector<ValuePtr>& args) -> ValuePtr {
            return operation(args[0], args[1]);
        }
    );
}

std::shared_ptr<LIRFunction> createUnaryOpFunction(
    const std::string& name,
    TypeTag paramType,
    TypeTag returnType,
    std::function<ValuePtr(ValuePtr)> operation) {
    
    return LIRFunctionManager::getInstance().createArithmeticFunction(
        name,
        std::vector<TypeTag>{paramType},
        returnType,
        [operation](const std::vector<ValuePtr>& args) -> ValuePtr {
            return operation(args[0]);
        }
    );
}

} // namespace LIR
