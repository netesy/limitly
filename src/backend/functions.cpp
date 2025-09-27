#include "functions.hh"
#include "types.hh"
#include "../common/debugger.hh"

namespace backend {

// UserDefinedFunction implementation
UserDefinedFunction::UserDefinedFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl) 
    : signature(FunctionUtils::createSignature(decl)), body(decl->body) {
}

UserDefinedFunction::UserDefinedFunction(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl) 
    : signature(FunctionUtils::createSignature(decl)), body(decl->body) {
    signature.isAsync = true;
}

ValuePtr UserDefinedFunction::execute(const std::vector<ValuePtr>& args) {
    // This will be implemented by the specific backend (VM, C codegen, etc.)
    // The VM will override this to execute the function body
    // C codegen will generate C code for this function
    return nullptr;
}

// NativeFunction implementation
NativeFunction::NativeFunction(const std::string& name,
                              const std::vector<Parameter>& params,
                              std::optional<std::shared_ptr<AST::TypeAnnotation>> returnType,
                              NativeFunctionPtr func)
    : function(func) {
    signature.name = name;
    signature.parameters = params;
    signature.returnType = returnType;
}

ValuePtr NativeFunction::execute(const std::vector<ValuePtr>& args) {
    if (!FunctionUtils::validateArguments(signature, args)) {
        return nullptr; // Error handling will be done by the backend
    }
    
    auto adjustedArgs = FunctionUtils::applyDefaults(signature, args);
    return function(adjustedArgs);
}

// CallFrame implementation
void CallFrame::bindParameters(const std::vector<ValuePtr>& args) {
    const auto& sig = function->getSignature();
    
    // Bind required parameters
    for (size_t i = 0; i < sig.parameters.size() && i < args.size(); ++i) {
        localVariables[sig.parameters[i].name] = args[i];
    }
    
    // Bind optional parameters
    size_t optionalStart = sig.parameters.size();
    for (size_t i = 0; i < sig.optionalParameters.size(); ++i) {
        size_t argIndex = optionalStart + i;
        if (argIndex < args.size()) {
            localVariables[sig.optionalParameters[i].name] = args[argIndex];
        }
        // Default values will be applied by FunctionUtils::applyDefaults
    }
}

ValuePtr CallFrame::getVariable(const std::string& name) const {
    auto it = localVariables.find(name);
    return (it != localVariables.end()) ? it->second : nullptr;
}

void CallFrame::setVariable(const std::string& name, ValuePtr value) {
    localVariables[name] = value;
}

// FunctionRegistry implementation
void FunctionRegistry::registerFunction(const std::shared_ptr<AST::FunctionDeclaration>& decl) {
    auto func = std::make_shared<UserDefinedFunction>(decl);
    functions[decl->name] = func;
}

void FunctionRegistry::registerFunction(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl) {
    auto func = std::make_shared<UserDefinedFunction>(decl);
    functions[decl->name] = func;
}

void FunctionRegistry::registerNativeFunction(const std::string& name,
                                             const std::vector<Parameter>& params,
                                             std::optional<std::shared_ptr<AST::TypeAnnotation>> returnType,
                                             NativeFunction::NativeFunctionPtr func) {
    auto nativeFunc = std::make_shared<NativeFunction>(name, params, returnType, func);
    functions[name] = nativeFunc;
}

std::shared_ptr<FunctionImplementation> FunctionRegistry::getFunction(const std::string& name) const {
    auto it = functions.find(name);
    return (it != functions.end()) ? it->second : nullptr;
}

bool FunctionRegistry::hasFunction(const std::string& name) const {
    return functions.find(name) != functions.end();
}

std::vector<std::string> FunctionRegistry::getFunctionNames() const {
    std::vector<std::string> names;
    names.reserve(functions.size());
    for (const auto& pair : functions) {
        names.push_back(pair.first);
    }
    return names;
}

void FunctionRegistry::clear() {
    functions.clear();
}

// FunctionUtils implementation
namespace FunctionUtils {

bool validateArguments(const FunctionSignature& signature, const std::vector<ValuePtr>& args) {
    return signature.isValidParamCount(args.size());
}

std::vector<ValuePtr> applyDefaults(const FunctionSignature& signature,
                                   const std::vector<ValuePtr>& args) {
    std::vector<ValuePtr> result = args;
    
    // If we have fewer arguments than total parameters, apply defaults
    size_t totalParams = signature.getTotalParamCount();
    if (args.size() < totalParams) {
        result.reserve(totalParams);
        
        // Add default values for missing optional parameters
        size_t optionalStart = signature.parameters.size();
        for (size_t i = args.size(); i < totalParams; ++i) {
            size_t optionalIndex = i - optionalStart;
            if (optionalIndex < signature.optionalParameters.size()) {
                const auto& optParam = signature.optionalParameters[optionalIndex];
                if (optParam.defaultValue) {
                    // Default value evaluation would be handled by the backend
                    // For now, we'll add a placeholder
                    result.push_back(nullptr); // Backend will evaluate default
                }
            }
        }
    }
    
    return result;
}

FunctionSignature createSignature(const std::shared_ptr<AST::FunctionDeclaration>& decl) {
    FunctionSignature sig;
    sig.name = decl->name;
    sig.parameters = convertParameters(decl->params);
    sig.optionalParameters = convertOptionalParameters(decl->optionalParams);
    sig.returnType = decl->returnType;
    sig.genericParams = decl->genericParams;
    sig.throws = decl->throws;
    sig.isAsync = false;
    return sig;
}

FunctionSignature createSignature(const std::shared_ptr<AST::AsyncFunctionDeclaration>& decl) {
    FunctionSignature sig;
    sig.name = decl->name;
    sig.parameters = convertParameters(decl->params);
    sig.optionalParameters = convertOptionalParameters(decl->optionalParams);
    sig.returnType = decl->returnType;
    sig.genericParams = decl->genericParams;
    sig.throws = decl->throws;
    sig.isAsync = true;
    return sig;
}

std::vector<Parameter> convertParameters(
    const std::vector<std::pair<std::string, std::shared_ptr<AST::TypeAnnotation>>>& params) {
    std::vector<Parameter> result;
    result.reserve(params.size());
    
    for (const auto& param : params) {
        result.emplace_back(param.first, param.second, false, nullptr);
    }
    
    return result;
}

std::vector<Parameter> convertOptionalParameters(
    const std::vector<std::pair<std::string, std::pair<std::shared_ptr<AST::TypeAnnotation>, 
                                                      std::shared_ptr<AST::Expression>>>>& params) {
    std::vector<Parameter> result;
    result.reserve(params.size());
    
    for (const auto& param : params) {
        result.emplace_back(param.first, param.second.first, true, param.second.second);
    }
    
    return result;
}

} // namespace FunctionUtils

} // namespace backend