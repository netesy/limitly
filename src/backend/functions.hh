#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>
#include <functional>
#include "../frontend/ast.hh"
#include "value.hh"

namespace backend {

// Forward declarations
class FunctionRegistry;
class CallFrame;
class Environment;


// Function definition for user-defined functions
struct Function {
    std::string name;
    std::shared_ptr<AST::FunctionDeclaration> declaration;
    // std::vector<std::string> parameters;
    // std::vector<std::string> optionalParameters;
    // std::map<std::string, ValuePtr> defaultValues;
    std::vector<std::pair<std::string, TypePtr>> parameters;  // name and type
    std::vector<std::pair<std::string, TypePtr>> optionalParameters;
    std::map<std::string, std::pair<ValuePtr, TypePtr>> defaultValues;
    size_t startAddress;
    size_t endAddress;
    TypePtr returnType;
    
    Function() : startAddress(0), endAddress(0), returnType(nullptr) {}
    
    Function(const std::string& n, size_t start) 
        : name(n), startAddress(start), endAddress(0), returnType(nullptr) {}
};

// Function parameter information
struct Parameter {
    std::string name;
    std::shared_ptr<AST::TypeAnnotation> type;
    bool isOptional = false;
    std::shared_ptr<AST::Expression> defaultValue = nullptr;
    
    Parameter(const std::string& n, std::shared_ptr<AST::TypeAnnotation> t, 
              bool optional = false, std::shared_ptr<AST::Expression> def = nullptr)
        : name(n), type(t), isOptional(optional), defaultValue(def) {}
};

// Function signature information
struct FunctionSignature {
    std::string name;
    std::vector<Parameter> parameters;
    std::vector<Parameter> optionalParameters;
    std::optional<std::shared_ptr<AST::TypeAnnotation>> returnType;
    std::vector<std::string> genericParams;
    bool throws = false;
    bool isAsync = false;
    
    // Get total parameter count (required + optional)
    size_t getTotalParamCount() const {
        return parameters.size() + optionalParameters.size();
    }
    
    // Get minimum parameter count (only required)
    size_t getMinParamCount() const {
        return parameters.size();
    }
    
    // Check if parameter count is valid for this function
    bool isValidParamCount(size_t count) const {
        return count >= getMinParamCount() && count <= getTotalParamCount();
    }
};

// Abstract base class for function implementations
class FunctionImplementation {
public:
    virtual ~FunctionImplementation() = default;
    
    // Get the function signature
    virtual const FunctionSignature& getSignature() const = 0;
    
    // Execute the function (backend-specific)
    virtual ValuePtr execute(const std::vector<ValuePtr>& args) = 0;
    
    // Check if this is a native function
    virtual bool isNative() const = 0;
    
    // Get the function body (for user-defined functions)
    virtual std::shared_ptr<AST::BlockStatement> getBody() const { return nullptr; }
};

// User-defined function implementation
class UserDefinedFunction : public FunctionImplementation {
private:
    FunctionSignature signature;
    std::shared_ptr<AST::BlockStatement> body;
    
public:
    UserDefinedFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl);
    UserDefinedFunction(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl);
    
    const FunctionSignature& getSignature() const override { return signature; }
    ValuePtr execute(const std::vector<ValuePtr>& args) override;
    bool isNative() const override { return false; }
    std::shared_ptr<AST::BlockStatement> getBody() const override { return body; }
};

// Native function implementation (C++ functions)
class NativeFunction : public FunctionImplementation {
public:
    using NativeFunctionPtr = std::function<ValuePtr(const std::vector<ValuePtr>&)>;
    
private:
    FunctionSignature signature;
    NativeFunctionPtr function;
    
public:
    NativeFunction(const std::string& name, 
                   const std::vector<Parameter>& params,
                   std::optional<std::shared_ptr<AST::TypeAnnotation>> returnType,
                   NativeFunctionPtr func);
    
    const FunctionSignature& getSignature() const override { return signature; }
    ValuePtr execute(const std::vector<ValuePtr>& args) override;
    bool isNative() const override { return true; }
};

// Forward declaration for Environment
class Environment;

// Call frame for function execution
class CallFrame {
public:
    std::string functionName;
    std::unordered_map<std::string, ValuePtr> localVariables;
    size_t returnAddress;
    std::shared_ptr<FunctionImplementation> function;
    std::shared_ptr<void> previousEnvironment; // Generic pointer to previous environment
    
    CallFrame(const std::string& name, size_t retAddr, 
              std::shared_ptr<FunctionImplementation> func)
        : functionName(name), returnAddress(retAddr), function(func), previousEnvironment(nullptr) {}
    
    // Bind parameters to arguments
    void bindParameters(const std::vector<ValuePtr>& args);
    
    // Get local variable
    ValuePtr getVariable(const std::string& name) const;
    
    // Set local variable
    void setVariable(const std::string& name, ValuePtr value);
    
    // Set previous environment (VM-specific)
    template<typename EnvType>
    void setPreviousEnvironment(std::shared_ptr<EnvType> env) {
        previousEnvironment = std::static_pointer_cast<void>(env);
    }
    
    // Get previous environment (VM-specific)
    template<typename EnvType>
    std::shared_ptr<EnvType> getPreviousEnvironment() const {
        return std::static_pointer_cast<EnvType>(previousEnvironment);
    }
};

// Function registry for managing all functions
class FunctionRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<FunctionImplementation>> functions;
    
public:
    // Register a user-defined function
    void registerFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl);
    void registerFunction(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl);
    
    // Register a native function
    void registerNativeFunction(const std::string& name,
                               const std::vector<Parameter>& params,
                               std::optional<std::shared_ptr<AST::TypeAnnotation>> returnType,
                               NativeFunction::NativeFunctionPtr func);
    
    // Get function by name
    std::shared_ptr<FunctionImplementation> getFunction(const std::string& name) const;
    
    // Check if function exists
    bool hasFunction(const std::string& name) const;
    
    // Get all function names
    std::vector<std::string> getFunctionNames() const;
    
    // Clear all functions
    void clear();
};

// Function call utilities
namespace FunctionUtils {
    // Validate function call arguments
    bool validateArguments(const FunctionSignature& signature, 
                          const std::vector<ValuePtr>& args);
    
    // Apply default values to missing optional parameters
    std::vector<ValuePtr> applyDefaults(const FunctionSignature& signature,
                                       const std::vector<ValuePtr>& args);
    
    // Create function signature from AST declaration
    FunctionSignature createSignature(const std::shared_ptr<AST::FunctionDeclaration>& decl);
    FunctionSignature createSignature(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl);
    
    // Convert AST parameters to Parameter objects
    std::vector<Parameter> convertParameters(
        const std::vector<std::pair<std::string, std::shared_ptr<AST::TypeAnnotation>>>& params);
    
    std::vector<Parameter> convertOptionalParameters(
        const std::vector<std::pair<std::string, std::pair<std::shared_ptr<AST::TypeAnnotation>, 
                                                          std::shared_ptr<AST::Expression>>>>& params);
}

} // namespace backend

#endif // FUNCTIONS_HH