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

namespace LIR {

// Forward declarations
class LIRBuiltinFunction;
class LIRBuiltinFunctions;

// Type alias for LIR builtin function implementations
// These are specifically designed for LIR register-based operations
using LIRBuiltinImpl = std::function<ValuePtr(const std::vector<ValuePtr>&)>;

// LIR-specific builtin function class
// Optimized for register-based LIR operations and JIT compilation
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
    
    // Function interface
    ValuePtr execute(const std::vector<ValuePtr>& args);
    bool isNative() const;
    const LIRFunctionSignature& getSignature() const;
    
    // LIR-specific accessors
    const std::string& getName() const { return name_; }
    const std::vector<TypeTag>& getParameterTypes() const { return paramTypes_; }
    TypeTag getReturnType() const { return returnType_; }
};

// Manager for LIR-specific builtin functions
// Completely separate from the backend bytecode system
class LIRBuiltinFunctions {
private:
    static LIRBuiltinFunctions* instance;
    std::unordered_map<std::string, std::shared_ptr<LIRBuiltinFunction>> builtinFunctions_;
    bool initialized_ = false;

public:
    static LIRBuiltinFunctions& getInstance();
    
    // Initialization
    void initialize();
    
    // Function registration
    void registerFunction(std::shared_ptr<LIRBuiltinFunction> function);
    
    // Function lookup
    std::shared_ptr<LIRBuiltinFunction> getFunction(const std::string& name);
    bool hasFunction(const std::string& name) const;
    
    // Utility methods
    std::vector<std::string> getFunctionNames() const;

private:
    // Registration categories
    void registerStringFunctions();
    void registerIOFunctions();
    void registerMathFunctions();
    void registerUtilityFunctions();
    void registerCollectionFunctions();
    void registerSearchFunctions();
    void registerCompositionFunctions();
    
    // Helper methods
    std::shared_ptr<LIRBuiltinFunction> createArithmeticFunction(
        const std::string& name,
        const std::vector<TypeTag>& paramTypes,
        TypeTag returnType,
        std::function<ValuePtr(const std::vector<ValuePtr>&)> impl);
};

// Utility functions for LIR builtin function integration
namespace BuiltinUtils {

// Initialize LIR builtin function system
void initializeBuiltins();

// Get all available builtin function names
std::vector<std::string> getBuiltinFunctionNames();

// Check if a builtin function exists
bool isBuiltinFunction(const std::string& name);

// Call a builtin function by name
ValuePtr callBuiltinFunction(const std::string& name, const std::vector<ValuePtr>& args);

} // namespace BuiltinUtils

} // namespace LIR

#endif // LIR_BUILTIN_FUNCTIONS_HH
