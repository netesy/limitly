#ifndef BUILTIN_FUNCTIONS_HH
#define BUILTIN_FUNCTIONS_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../backend/value.hh"

// Forward declarations
struct Value;
class VM;
using ValuePtr = std::shared_ptr<Value>;

namespace builtin {

// Type alias for builtin function implementations
using BuiltinFunctionImpl = std::function<ValuePtr(const std::vector<ValuePtr>&)>;

// Note: VM-aware builtin function implementations will be added when full closure support is implemented

// Forward declarations
struct Value;

// Structure to define a builtin function
struct BuiltinFunctionDefinition {
    std::string name;
    std::vector<TypeTag> parameterTypes;
    TypeTag returnType;
    std::string description;
    BuiltinFunctionImpl implementation;
    
    // Constructor
    BuiltinFunctionDefinition() = default;
    
    BuiltinFunctionDefinition(const std::string& n, 
                             const std::vector<TypeTag>& params,
                             TypeTag ret,
                             const std::string& desc,
                             BuiltinFunctionImpl impl)
        : name(n), parameterTypes(params), returnType(ret), description(desc), implementation(impl) {}
};

// Main builtin functions class
class BuiltinFunctions {
private:
    static BuiltinFunctions* instance;
    std::unordered_map<std::string, BuiltinFunctionDefinition> builtinDefinitions;
    
    // Private constructor for singleton pattern
    BuiltinFunctions();
    
    // Initialize all builtin function definitions
    void initializeBuiltinDefinitions();
    
    // Register a single builtin function
    void registerBuiltinFunction(const std::string& name, const BuiltinFunctionDefinition& definition);
    
public:
    // Singleton access
    static BuiltinFunctions& getInstance();
    
    // Register all builtin functions with the VM
    static void registerAll(::VM* vm);
    
    // Alternative registration method that returns function definitions
    static std::unordered_map<std::string, BuiltinFunctionImpl> getAllBuiltinImplementations();
    
    // Query methods
    bool isBuiltinFunction(const std::string& name) const;
    const BuiltinFunctionDefinition* getBuiltinDefinition(const std::string& name) const;
    std::vector<std::string> getBuiltinFunctionNames() const;
    
    // Core collection operations
    static ValuePtr map(const std::vector<ValuePtr>& args);
    static ValuePtr filter(const std::vector<ValuePtr>& args);
    static ValuePtr reduce(const std::vector<ValuePtr>& args);
    static ValuePtr forEach(const std::vector<ValuePtr>& args);
    
    // Search operations
    static ValuePtr find(const std::vector<ValuePtr>& args);
    static ValuePtr some(const std::vector<ValuePtr>& args);
    static ValuePtr every(const std::vector<ValuePtr>& args);
    
    // Note: VM-aware search operations will be added when full closure support is implemented
    
    // Utility operations
    static ValuePtr compose(const std::vector<ValuePtr>& args);
    static ValuePtr curry(const std::vector<ValuePtr>& args);
    static ValuePtr partial(const std::vector<ValuePtr>& args);
    
    // Note: VM-aware utility operations will be added when full closure support is implemented
    
    // Core utility functions
    static ValuePtr clock(const std::vector<ValuePtr>& args);
    static ValuePtr sleep(const std::vector<ValuePtr>& args);
    static ValuePtr len(const std::vector<ValuePtr>& args);
    static ValuePtr time(const std::vector<ValuePtr>& args);
    static ValuePtr date(const std::vector<ValuePtr>& args);
    static ValuePtr now(const std::vector<ValuePtr>& args);
    static ValuePtr assertCondition(const std::vector<ValuePtr>& args);
    static ValuePtr input(const std::vector<ValuePtr>& args);
    static ValuePtr round(const std::vector<ValuePtr>& args);
    static ValuePtr debug(const std::vector<ValuePtr>& args);
    static ValuePtr typeOf(const std::vector<ValuePtr>& args);
};

// Utility functions for builtin function implementation

// Validate function arguments against expected types
void validateArguments(const std::string& functionName, const std::vector<ValuePtr>& args, 
                      const std::vector<TypeTag>& expectedTypes);

// Convert TypeTag to string for error messages
std::string typeTagToString(TypeTag tag);

// Check if a value is callable (function or closure)
bool isCallable(const ValuePtr& value);

// Call a function value with arguments (helper for builtin implementations)
ValuePtr callFunction(const ValuePtr& function, const std::vector<ValuePtr>& args);

// Note: VM-aware function calling will be added when full closure support is implemented

} // namespace builtin

#endif // BUILTIN_FUNCTIONS_HH