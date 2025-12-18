#ifndef LIR_FUNCTIONS_HH
#define LIR_FUNCTIONS_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <optional>
#include "../backend/value.hh"
#include "../backend/types.hh"

namespace LIR {

// LIR-specific parameter and signature types (independent from backend)
struct LIRParameter {
    std::string name;
    std::shared_ptr<Type> type;
};

struct LIRFunctionSignature {
    std::string name;
    std::vector<LIRParameter> parameters;
    std::optional<std::shared_ptr<Type>> returnType;
    bool isAsync = false;
};

// Forward declarations
class LIRFunction;
class LIRFunctionManager;

// Type alias for LIR function body implementations
// These are specifically designed for LIR register-based operations
using LIRFunctionBody = std::function<ValuePtr(const std::vector<ValuePtr>&)>;

// LIR-specific function class
// Optimized for register-based LIR operations and JIT compilation
class LIRFunction {
private:
    std::string name_;
    std::vector<LIRParameter> parameters_;
    std::optional<std::shared_ptr<Type>> returnType_;
    LIRFunctionBody body_;
    LIRFunctionSignature signature_;
    
    // Store the LIR instructions for this function
    std::vector<LIR::LIR_Inst> instructions_;

public:
    LIRFunction(const std::string& name, 
                const std::vector<LIRParameter>& params,
                std::optional<std::shared_ptr<Type>> returnType,
                LIRFunctionBody body);
    
    // Function interface
    ValuePtr execute(const std::vector<ValuePtr>& args);
    bool isNative() const;
    const LIRFunctionSignature& getSignature() const;
    
    // LIR-specific accessors
    const std::string& getName() const { return name_; }
    const std::vector<LIRParameter>& getParameters() const { return parameters_; }
    const std::optional<std::shared_ptr<Type>>& getReturnType() const { return returnType_; }
    bool hasBody() const { return static_cast<bool>(body_); }
    
    // LIR instruction access
    const std::vector<LIR::LIR_Inst>& getInstructions() const { return instructions_; }
    void setInstructions(const std::vector<LIR::LIR_Inst>& instructions) { instructions_ = instructions; }
};

// Manager for LIR-specific functions
// Completely separate from the backend bytecode system
class LIRFunctionManager {
private:
    static LIRFunctionManager* instance;
    std::unordered_map<std::string, std::shared_ptr<LIRFunction>> functions_;
    bool initialized_ = false;

public:
    static LIRFunctionManager& getInstance();
    
    // Initialization
    void initialize();
    
    // Function registration
    void registerFunction(std::shared_ptr<LIRFunction> function);
    
    // Function lookup
    std::shared_ptr<LIRFunction> getFunction(const std::string& name);
    bool hasFunction(const std::string& name) const;
    size_t getFunctionIndex(const std::string& name) const;
    
    // Function creation helpers
    std::shared_ptr<LIRFunction> createFunction(
        const std::string& name,
        const std::vector<LIRParameter>& params,
        std::optional<std::shared_ptr<Type>> returnType,
        LIRFunctionBody body);
    
    std::shared_ptr<LIRFunction> createArithmeticFunction(
        const std::string& name,
        const std::vector<TypeTag>& paramTypes,
        TypeTag returnType,
        std::function<ValuePtr(const std::vector<ValuePtr>&)> impl);
    
    // Utility methods
    std::vector<std::string> getFunctionNames() const;
};

// BuiltinUtils namespace for accessing builtin LIR functions
namespace BuiltinUtils {
    void initializeBuiltins();
    bool isBuiltinFunction(const std::string& name);
    ValuePtr callBuiltinFunction(const std::string& name, const std::vector<ValuePtr>& args);
    std::vector<std::string> getBuiltinFunctionNames();
}

// Utility functions for LIR function integration
namespace FunctionUtils {

// Call any LIR function (builtin or user-defined) by name
ValuePtr callFunction(const std::string& name, const std::vector<ValuePtr>& args);

// Check if a function exists (builtin or user-defined)
bool isFunction(const std::string& name);

// Initialize LIR function system
void initializeFunctions();

// Get all available function names (builtin + user-defined)
std::vector<std::string> getAllFunctionNames();

// Helper functions for creating common operation functions
std::shared_ptr<LIRFunction> createBinaryOpFunction(
    const std::string& name,
    TypeTag paramType,
    TypeTag returnType,
    std::function<ValuePtr(ValuePtr, ValuePtr)> operation);

std::shared_ptr<LIRFunction> createUnaryOpFunction(
    const std::string& name,
    TypeTag paramType,
    TypeTag returnType,
    std::function<ValuePtr(ValuePtr)> operation);

} // namespace LIRFunctionUtils

} // namespace LIR

#endif // LIR_FUNCTIONS_HH
