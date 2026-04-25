#ifndef LIR_BUILTIN_FUNCTIONS_HH
#define LIR_BUILTIN_FUNCTIONS_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../backend/value.hh"
#include "../backend/types.hh"
#include "functions.hh"

namespace LM {
namespace LIR {

// Forward declarations
class LIRBuiltinFunction;
class LIRBuiltinFunctions;

// Type alias for LIR builtin function implementations
using LIRBuiltinImpl = std::function<ValuePtr(const std::vector<ValuePtr>&)>;

// LIR-specific builtin function class
class LIRBuiltinFunction {
private:
    std::string name_;
    std::vector<TypeTag> paramTypes_;
    TypeTag returnType_;
    LIRBuiltinImpl implementation_;
    LIRFunctionSignature signature_;

public:
    LIRBuiltinFunction(const std::string& name, 
                       const std::vector<TypeTag>& paramTypes,
                       TypeTag returnType,
                       LIRBuiltinImpl impl);
    
    ValuePtr execute(const std::vector<ValuePtr>& args);
    bool isNative() const;
    const LIRFunctionSignature& getSignature() const;
    
    const std::string& getName() const { return name_; }
    const std::vector<TypeTag>& getParameterTypes() const { return paramTypes_; }
    TypeTag getReturnType() const { return returnType_; }
};

// Manager for LIR-specific builtin functions (VM Intrinsics)
class LIRBuiltinFunctions {
private:
    static LIRBuiltinFunctions* instance;
    std::unordered_map<std::string, std::shared_ptr<LIRBuiltinFunction>> builtinFunctions_;
    bool initialized_ = false;

public:
    static LIRBuiltinFunctions& getInstance();
    
    void initialize();
    void registerFunction(std::shared_ptr<LIRBuiltinFunction> function);
    
    std::shared_ptr<LIRBuiltinFunction> getFunction(const std::string& name);
    bool hasFunction(const std::string& name) const;
    
    std::vector<std::string> getFunctionNames() const;

private:
    // Only VM Intrinsics are built-in
    void registerIOFunctions();      // print, input
    void registerUtilityFunctions(); // typeof, clock, sleep, time, assert
};

namespace BuiltinUtils {
    void initializeBuiltins();
    std::vector<std::string> getBuiltinFunctionNames();
    bool isBuiltinFunction(const std::string& name);
    ValuePtr callBuiltinFunction(const std::string& name, const std::vector<ValuePtr>& args);
} // namespace BuiltinUtils

} // namespace LIR
} // namespace LM
#endif // LIR_BUILTIN_FUNCTIONS_HH
