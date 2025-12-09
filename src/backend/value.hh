//value.hh
#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "../common/opcodes.hh"
#include "concurrency/channel.hh"
#include <atomic>

// Forward declarations for AST types
namespace AST {
class FunctionDeclaration;
}

// Forward declarations
struct Value;
using ValuePtr = std::shared_ptr<Value>;

struct NewType;
using TypePtr = std::shared_ptr<NewType>;

// Forward declare ListValue and DictValue
struct ListValue;
struct DictValue;

// Forward declare IteratorValue
struct IteratorValue;
using IteratorValuePtr = std::shared_ptr<IteratorValue>;

// Forward declare ObjectInstance from classes
namespace backend {
class ObjectInstance;
class ClassDefinition;
class UserDefinedFunction;

// Function definition for user-defined functions
struct Function {
    std::string name;
    std::shared_ptr<AST::FunctionDeclaration> declaration;
    std::vector<std::pair<std::string, TypePtr>> parameters;  // name and type
    std::vector<std::pair<std::string, TypePtr>> optionalParameters;
    std::map<std::string, std::pair<ValuePtr, TypePtr>> defaultValues;
    size_t startAddress;
    size_t endAddress;
    TypePtr returnType;
    bool isLambda = false;  // Flag to indicate if this is a lambda function

    Function() : startAddress(0), endAddress(0), returnType(nullptr), isLambda(false) {}

    Function(const std::string& n, size_t start)
        : name(n), startAddress(start), endAddress(0), returnType(nullptr), isLambda(false) {}
};
}
using ObjectInstancePtr = std::shared_ptr<backend::ObjectInstance>;

// Forward declare Environment
class Environment;

struct ModuleValue {
    std::shared_ptr<Environment> env;
    std::vector<Instruction> bytecode;
};

// Closure value for capturing variables from enclosing scope
struct ClosureValue {
    std::string functionName;                                // Name of the lambda function
    size_t startAddress;                                     // Bytecode start address
    size_t endAddress;                                       // Bytecode end address
    std::shared_ptr<::Environment> capturedEnvironment;        // Environment with captured variables
    std::vector<std::string> capturedVariables;             // Names of captured variables
    
    // Constructor
    ClosureValue();
    
    ClosureValue(const std::string& funcName, size_t start, size_t end,
                 std::shared_ptr<::Environment> capturedEnv,
                 const std::vector<std::string>& capturedVars);
    
    // Copy constructor
    ClosureValue(const ClosureValue& other);
    
    // Move constructor
    ClosureValue(ClosureValue&& other) noexcept;
    
    // Assignment operators
    ClosureValue& operator=(const ClosureValue& other);
    
    ClosureValue& operator=(ClosureValue&& other) noexcept;
    
    // Utility methods
    bool isValid() const;
    
    // Execute the closure with given arguments
    ValuePtr execute(const std::vector<ValuePtr>& args);
    
    // Get captured variable count
    size_t getCapturedVariableCount() const;
    
    // Check if variable is captured
    bool isVariableCaptured(const std::string& varName) const;
    
    // Get function name
    std::string getFunctionName() const;
    
    // Memory management methods
    std::string getClosureId() const;
    
    void cleanup();
    
    // Check for potential memory leaks
    bool hasMemoryLeaks() const;
    
    // Get memory usage estimate
    size_t getMemoryUsage() const;
    
    // String representation
    std::string toString() const;
    
    // Static factory method for creating closures (defined later after factory namespace)
    static ValuePtr create(std::shared_ptr<backend::UserDefinedFunction> func,
                           std::shared_ptr<::Environment> capturedEnv,
                           const std::vector<std::string>& capturedVars);
};

enum class TypeTag {
    Nil,
    Bool,
    Int,
    Int8,
    Int16,
    Int32,
    Int64,
    UInt,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
    Float32,
    Float64,
    String,
    List,
    Dict,
    Tuple,
    Enum,
    Function,
    Closure,
    Any,
    Sum,
    Union,
    ErrorUnion,
    Range,
    UserDefined,
    Class,
    Channel,
    Object,
    Module
};

// Forward declaration for ClosureValue factory method with proper TypePtr
namespace ClosureValueFactory {
ValuePtr createClosure(std::shared_ptr<backend::UserDefinedFunction> func,
                       std::shared_ptr<::Environment> capturedEnv,
                       const std::vector<std::string>& capturedVars,
                       TypePtr closureType = nullptr);
}

struct ListType
{
    TypePtr elementType;
};

struct DictType
{
    TypePtr keyType;
    TypePtr valueType;
};

struct TupleType
{
    std::vector<TypePtr> elementTypes;
    
    TupleType() = default;
    TupleType(const std::vector<TypePtr>& types) : elementTypes(types) {}
    
    size_t size() const { return elementTypes.size(); }
    
    std::string toString() const; // Implementation moved to avoid forward declaration issues
};

struct EnumType
{
    std::vector<std::string> values;

    void addVariant(const std::string& name) {
        if (std::find(values.begin(), values.end(), name) != values.end()) {
            throw std::runtime_error("Enum variant already exists: " + name);
        }
        values.push_back(name);
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "Enum(";
        for (auto it = values.begin(); it != values.end(); ++it) {
            if (it != values.begin()) oss << ", ";
            oss << *it;
        }
        oss << ")";
        return oss.str();
    }
};

struct FunctionType
{
    std::vector<TypePtr> paramTypes;                         // Parameter types (legacy)
    TypePtr returnType;                                      // Return type
    
    // Enhanced function signature support
    std::vector<std::string> paramNames;                     // Parameter names (optional)
    std::vector<bool> hasDefaultValues;                      // Which parameters have defaults
    bool isVariadic = false;                                 // Whether function accepts variable arguments
    
    // Generic function type support
    std::vector<std::string> typeParameters;                 // Generic type parameter names (e.g., T, U)
    bool isGeneric = false;                                  // Whether this is a generic function
    
    // Constructors
    FunctionType() = default;
    
    FunctionType(const std::vector<TypePtr>& params, TypePtr ret)
        : paramTypes(params), returnType(ret) {
        // Initialize default values tracking
        hasDefaultValues.resize(params.size(), false);
    }
    
    FunctionType(const std::vector<std::string>& names, 
                 const std::vector<TypePtr>& params, 
                 TypePtr ret,
                 const std::vector<bool>& defaults = {},
                 const std::vector<std::string>& typeParams = {})
        : paramTypes(params), returnType(ret), paramNames(names), hasDefaultValues(defaults), 
        typeParameters(typeParams), isGeneric(!typeParams.empty()) {
        // Ensure consistent sizes
        if (hasDefaultValues.empty()) {
            hasDefaultValues.resize(params.size(), false);
        }
    }
    
    // Helper methods
    size_t getParameterCount() const { return paramTypes.size(); }
    
    bool hasNamedParameters() const { 
        return !paramNames.empty() && 
               std::any_of(paramNames.begin(), paramNames.end(), 
                           [](const std::string& name) { return !name.empty(); });
    }
    
    std::string getParameterName(size_t index) const {
        return (index < paramNames.size()) ? paramNames[index] : "";
    }
    
    TypePtr getParameterType(size_t index) const {
        return (index < paramTypes.size()) ? paramTypes[index] : nullptr;
    }
    
    bool parameterHasDefault(size_t index) const {
        return (index < hasDefaultValues.size()) ? hasDefaultValues[index] : false;
    }
    
    // Type compatibility checking (contravariance for parameters, covariance for return)
    bool isCompatibleWith(const FunctionType& other) const;
    
    // String representation
    std::string toString() const;
};

struct UserDefinedType
{
    std::string name;
    std::vector<std::pair<std::string, std::map<std::string, TypePtr>>> fields;
};

struct SumType
{
    std::vector<TypePtr> variants;
};

struct UnionType
{
    std::vector<TypePtr> types;
};

struct ErrorUnionType
{
    TypePtr successType;                     // The success value type
    std::vector<std::string> errorTypes;     // Allowed error type names
    bool isGenericError = false;             // True for Type?, false for Type?Error1, Error2
};

struct Type
{
    TypeTag tag;
    bool isList = false;
    bool isDict = false;
    std::variant<std::monostate, ListType, DictType, TupleType, EnumType, FunctionType, SumType, UnionType, ErrorUnionType, UserDefinedType>
        extra;

    Type(TypeTag t)
        : tag(t)
    {}
    Type(TypeTag t,
         const std::variant<std::monostate,
                            ListType,
                            DictType,
                            TupleType,
                            EnumType,
                            FunctionType,
                            SumType,
                            UnionType,
                            ErrorUnionType,
                            UserDefinedType> &ex)
        : tag(t)
        , extra(ex)
    {}

    // In value.hh, add this inside the Type struct
    Type(const Type& other)
        : tag(other.tag), extra(other.extra) {
    }

    std::string toString() const
    {
        switch (tag) {
        case TypeTag::Nil:
            return "Nil";
        case TypeTag::Bool:
            return "Bool";
        case TypeTag::Int:
            return "Int";
        case TypeTag::Int8:
            return "Int8";
        case TypeTag::Int16:
            return "Int16";
        case TypeTag::Int32:
            return "Int32";
        case TypeTag::Int64:
            return "Int64";
        case TypeTag::UInt:
            return "UInt";
        case TypeTag::UInt8:
            return "UInt8";
        case TypeTag::UInt16:
            return "UInt16";
        case TypeTag::UInt32:
            return "UInt32";
        case TypeTag::UInt64:
            return "UInt64";
        case TypeTag::Float32:
            return "Float32";
        case TypeTag::Float64:
            return "Float64";
        case TypeTag::String:
            return "String";
        case TypeTag::List:
            return "List";
        case TypeTag::Dict:
            return "Dict";
        case TypeTag::Tuple: {
            if (const auto* tupleType = std::get_if<TupleType>(&extra)) {
                return tupleType->toString();
            }
            return "Tuple";
        }
        case TypeTag::Enum:
            return "Enum";
        case TypeTag::Function: {
            if (const auto* funcType = std::get_if<FunctionType>(&extra)) {
                return funcType->toString();
            }
            return "Function";  // Generic function type
        }
        case TypeTag::Closure:
            return "Closure";
        case TypeTag::Any:
            return "Any";
        case TypeTag::Sum:
            return "Sum";
        case TypeTag::Union:
            return "Union";
        case TypeTag::ErrorUnion: {
            if (const auto* errorUnion = std::get_if<ErrorUnionType>(&extra)) {
                std::string result = errorUnion->successType->toString() + "?";
                if (!errorUnion->isGenericError && !errorUnion->errorTypes.empty()) {
                    result += "{";
                    for (size_t i = 0; i < errorUnion->errorTypes.size(); ++i) {
                        if (i > 0) result += ", ";
                        result += errorUnion->errorTypes[i];
                    }
                    result += "}";
                }
                return result;
            }
            return "ErrorUnion";
        }
        case TypeTag::UserDefined:
            return "UserDefined";
        case TypeTag::Object:
            return "Object";
        case TypeTag::Class:
            return "Class";
        case TypeTag::Module:
            return "Module";
        default:
            return "Unknown";
        }
    }

    bool operator==(const Type &other) const { return tag == other.tag; }
    bool operator!=(const Type &other) const { return !(*this == other); }
};

constexpr int getSizeInBits(TypeTag tag)
{
    switch (tag) {
    case TypeTag::Int8:
    case TypeTag::UInt8:
        return 8;
    case TypeTag::Int16:
    case TypeTag::UInt16:
        return 16;
    case TypeTag::Int:
    case TypeTag::UInt:
    case TypeTag::Int32:
    case TypeTag::UInt32:
    case TypeTag::Float32:
        return 32;
    case TypeTag::Int64:
    case TypeTag::UInt64:
    case TypeTag::Float64:
        return 64;
    default:
        return 0;
    }
}

class OverflowException : public std::runtime_error
{
public:
    OverflowException(const std::string &msg)
        : std::runtime_error(msg)
    {}
};

template<typename To, typename From>
To safe_cast(From value)
{
    To result = static_cast<To>(value);
    if (static_cast<From>(result) != value || (value > 0 && result < 0)
        || (value < 0 && result > 0)) {
        throw OverflowException("Overflow detected in integer conversion");
    }
    return result;
}

template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct Value;
using ValuePtr = std::shared_ptr<Value>;

struct UserDefinedValue
{
    std::string variantName;
    std::map<std::string, ValuePtr> fields;
};

struct SumValue
{
    size_t activeVariant;
    ValuePtr value;
};

struct EnumValue {
    std::string variantName;
    ValuePtr associatedValue;

    EnumValue() = default;

    EnumValue(const std::string& name, const TypePtr& enumType, ValuePtr value = nullptr)
        : variantName(name), associatedValue(value) {
    }

    static ValuePtr create(const std::string& variantName, const TypePtr& enumType, ValuePtr associatedValue = nullptr);

    std::string toString() const {
        if (associatedValue) {
            return "Enum(" + variantName + ", <associated value>)";
        }
        return "Enum(" + variantName + ")";
    }
};

struct ErrorValue {
    std::string errorType;
    std::string message;
    std::vector<ValuePtr> arguments;
    size_t sourceLocation = 0;

    ErrorValue() = default;

    ErrorValue(const std::string& type, const std::string& msg = "", 
               const std::vector<ValuePtr>& args = {}, size_t location = 0)
        : errorType(type), message(msg), arguments(args), sourceLocation(location) {}

    std::string toString() const;
};

struct AtomicValue {
    std::shared_ptr<std::atomic<int64_t>> inner;
    AtomicValue() : inner(std::make_shared<std::atomic<int64_t>>(0)) {}
    AtomicValue(int64_t v) : inner(std::make_shared<std::atomic<int64_t>>(v)) {}
};

struct ListValue {
    std::vector<ValuePtr> elements;

    void append(ValuePtr value) { elements.push_back(value); }
};

struct TupleValue {
    std::vector<ValuePtr> elements;
};

struct DictValue {
    std::map<ValuePtr, ValuePtr> elements;
};

struct Value {
    TypePtr type;
    std::variant<std::monostate,
                 bool,
                 long long,
                 unsigned long long,
                 double,
                 std::string,
                 ListValue,
                 DictValue,
                 TupleValue,
                 ErrorValue
                 >
        data;
    Value() : type(nullptr) {}
    explicit Value(TypePtr t) : type(std::move(t)) {}
    Value(TypePtr t, auto v) : type(std::move(t)), data(v) {}

    std::string getRawString() const;
    std::string toString() const;
};
