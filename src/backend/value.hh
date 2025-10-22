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

struct Type;
using TypePtr = std::shared_ptr<Type>;

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
    ClosureValue() : startAddress(0), endAddress(0) {}
    
    ClosureValue(const std::string& funcName, size_t start, size_t end,
                 std::shared_ptr<::Environment> capturedEnv,
                 const std::vector<std::string>& capturedVars)
        : functionName(funcName), startAddress(start), endAddress(end),
          capturedEnvironment(capturedEnv), capturedVariables(capturedVars) {}
    
    // Copy constructor
    ClosureValue(const ClosureValue& other)
        : functionName(other.functionName), startAddress(other.startAddress), endAddress(other.endAddress),
          capturedEnvironment(other.capturedEnvironment), capturedVariables(other.capturedVariables) {}
    
    // Move constructor
    ClosureValue(ClosureValue&& other) noexcept
        : functionName(std::move(other.functionName)), startAddress(other.startAddress), endAddress(other.endAddress),
          capturedEnvironment(std::move(other.capturedEnvironment)),
          capturedVariables(std::move(other.capturedVariables)) {}
    
    // Assignment operators
    ClosureValue& operator=(const ClosureValue& other) {
        if (this != &other) {
            functionName = other.functionName;
            startAddress = other.startAddress;
            endAddress = other.endAddress;
            capturedEnvironment = other.capturedEnvironment;
            capturedVariables = other.capturedVariables;
        }
        return *this;
    }
    
    ClosureValue& operator=(ClosureValue&& other) noexcept {
        if (this != &other) {
            functionName = std::move(other.functionName);
            startAddress = other.startAddress;
            endAddress = other.endAddress;
            capturedEnvironment = std::move(other.capturedEnvironment);
            capturedVariables = std::move(other.capturedVariables);
        }
        return *this;
    }
    
    // Utility methods
    bool isValid() const {
        return !functionName.empty() && startAddress < endAddress;
    }
    
    // Execute the closure with given arguments
    ValuePtr execute(const std::vector<ValuePtr>& args) {
        // This will be implemented by the VM when executing closures
        // For now, return nullptr as a placeholder
        if (functionName.empty()) {
            throw std::runtime_error("Cannot execute closure: function name is empty");
        }
        
        // The actual execution will be handled by the VM's closure execution mechanism
        // This is just a placeholder that will be called by the VM
        return nullptr;
    }
    
    // Get captured variable count
    size_t getCapturedVariableCount() const {
        return capturedVariables.size();
    }
    
    // Check if variable is captured
    bool isVariableCaptured(const std::string& varName) const {
        return std::find(capturedVariables.begin(), capturedVariables.end(), varName) 
               != capturedVariables.end();
    }
    
    // Get function name
    std::string getFunctionName() const {
        return functionName;
    }
    
    // Memory management methods
    std::string getClosureId() const {
        return functionName + "_" + std::to_string(reinterpret_cast<uintptr_t>(this));
    }
    
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
                 const std::vector<bool>& defaults = {})
        : paramTypes(params), returnType(ret), paramNames(names), hasDefaultValues(defaults) {
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
        case TypeTag::Function:
            return "Function";
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
        // Validate variant name
        const auto* enumTypeDetails = std::get_if<EnumType>(&enumType->extra);
        if (!enumTypeDetails) {
            throw std::runtime_error("Invalid enum type");
        }

        auto it = std::find(enumTypeDetails->values.begin(), enumTypeDetails->values.end(), name);
        if (it == enumTypeDetails->values.end()) {
            throw std::runtime_error("Unknown enum variant: " + name);
        }
    }

    static ValuePtr create(const std::string& variantName, const TypePtr& enumType, ValuePtr associatedValue = nullptr);

    std::string toString() const {
        // if (associatedValue) {
        //     return "Enum(" + variantName + ", " + associatedValue->toString() + ")";
        // }
        // return "Enum(" + variantName + ")";

        if (associatedValue) {
            // Use a generic representation if toString() is not available
            return "Enum(" + variantName + ", <associated value>)";
        }
        return "Enum(" + variantName + ")";
    }
};

struct ErrorValue {
    std::string errorType;
    std::string message;
    std::vector<ValuePtr> arguments;
    size_t sourceLocation = 0;      // For stack traces

    ErrorValue() = default;

    ErrorValue(const std::string& type, const std::string& msg = "", 
               const std::vector<ValuePtr>& args = {}, size_t location = 0)
        : errorType(type), message(msg), arguments(args), sourceLocation(location) {}

    std::string toString() const;  // Declaration only, definition after Value struct
};

// Atomic wrapper for integer primitives
struct AtomicValue {
    std::shared_ptr<std::atomic<int64_t>> inner;
    AtomicValue() : inner(std::make_shared<std::atomic<int64_t>>(0)) {}
    AtomicValue(int64_t v) : inner(std::make_shared<std::atomic<int64_t>>(v)) {}
};

// ErrorUnion helper class for efficient tagged union operations - optimized for cache efficiency
class ErrorUnion {
public:
    enum class Tag : uint8_t { SUCCESS, ERROR };

private:
    // Optimize memory layout for cache efficiency
    alignas(8) Tag tag_;  // Align to 8 bytes for better cache performance
    
    // Use a more cache-friendly layout
    union alignas(8) {
        ValuePtr successValue_;
        ErrorValue errorValue_;
    };

public:
    // Constructors - optimized for common cases
    ErrorUnion(ValuePtr success) noexcept : tag_(Tag::SUCCESS), successValue_(success) {}
    
    ErrorUnion(const ErrorValue& error) : tag_(Tag::ERROR) {
        new (&errorValue_) ErrorValue(error);
    }
    
    ErrorUnion(const std::string& errorType, const std::string& message = "", 
               const std::vector<ValuePtr>& args = {}, size_t location = 0) 
        : tag_(Tag::ERROR) {
        new (&errorValue_) ErrorValue(errorType, message, args, location);
    }

    // Copy constructor - optimized for success path
    ErrorUnion(const ErrorUnion& other) : tag_(other.tag_) {
        if (tag_ == Tag::SUCCESS) [[likely]] {
            successValue_ = other.successValue_;
        } else {
            new (&errorValue_) ErrorValue(other.errorValue_);
        }
    }

    // Move constructor - optimized for success path
    ErrorUnion(ErrorUnion&& other) noexcept : tag_(other.tag_) {
        if (tag_ == Tag::SUCCESS) [[likely]] {
            successValue_ = std::move(other.successValue_);
        } else {
            new (&errorValue_) ErrorValue(std::move(other.errorValue_));
        }
    }

    // Assignment operators - optimized with likely/unlikely hints
    ErrorUnion& operator=(const ErrorUnion& other) {
        if (this != &other) [[likely]] {
            // Destroy current content
            if (tag_ == Tag::ERROR) [[unlikely]] {
                errorValue_.~ErrorValue();
            }
            
            // Copy new content
            tag_ = other.tag_;
            if (tag_ == Tag::SUCCESS) [[likely]] {
                successValue_ = other.successValue_;
            } else {
                new (&errorValue_) ErrorValue(other.errorValue_);
            }
        }
        return *this;
    }

    ErrorUnion& operator=(ErrorUnion&& other) noexcept {
        if (this != &other) [[likely]] {
            // Destroy current content
            if (tag_ == Tag::ERROR) [[unlikely]] {
                errorValue_.~ErrorValue();
            }
            
            // Move new content
            tag_ = other.tag_;
            if (tag_ == Tag::SUCCESS) [[likely]] {
                successValue_ = std::move(other.successValue_);
            } else {
                new (&errorValue_) ErrorValue(std::move(other.errorValue_));
            }
        }
        return *this;
    }

    // Destructor - optimized for success path
    ~ErrorUnion() {
        if (tag_ == Tag::ERROR) [[unlikely]] {
            errorValue_.~ErrorValue();
        }
    }

    // Inspection methods - inlined for performance
    [[nodiscard]] inline bool isSuccess() const noexcept { return tag_ == Tag::SUCCESS; }
    [[nodiscard]] inline bool isError() const noexcept { return tag_ == Tag::ERROR; }
    [[nodiscard]] inline Tag getTag() const noexcept { return tag_; }

    // Value access methods - optimized with likely/unlikely hints
    [[nodiscard]] ValuePtr getSuccessValue() const {
        if (tag_ != Tag::SUCCESS) [[unlikely]] {
            throw std::runtime_error("Attempted to get success value from error union");
        }
        return successValue_;
    }

    [[nodiscard]] const ErrorValue& getErrorValue() const {
        if (tag_ != Tag::ERROR) [[unlikely]] {
            throw std::runtime_error("Attempted to get error value from success union");
        }
        return errorValue_;
    }

    // Safe access methods - optimized for success path
    [[nodiscard]] ValuePtr getSuccessValueOr(ValuePtr defaultValue) const noexcept {
        return isSuccess() ? successValue_ : defaultValue;
    }

    [[nodiscard]] std::string getErrorType() const {
        return isError() ? errorValue_.errorType : "";
    }

    [[nodiscard]] std::string getErrorMessage() const {
        return isError() ? errorValue_.message : "";
    }

    // Conversion to Value
    ValuePtr toValue(TypePtr errorUnionType) const;  // Declaration, definition after Value struct

    // Static factory methods - optimized for common patterns
    [[nodiscard]] static ErrorUnion success(ValuePtr value) noexcept {
        return ErrorUnion(value);
    }

    [[nodiscard]] static ErrorUnion error(const std::string& errorType, const std::string& message = "", 
                           const std::vector<ValuePtr>& args = {}, size_t location = 0) {
        return ErrorUnion(errorType, message, args, location);
    }

    [[nodiscard]] static ErrorUnion error(const ErrorValue& errorValue) {
        return ErrorUnion(errorValue);
    }

    // String representation
    std::string toString() const;  // Declaration only, definition after Value struct
};

struct ListValue {
    std::vector<ValuePtr> elements;

    void append(ValuePtr value) { elements.push_back(value); }
    void extend(const ListValue& other) {
        elements.insert(elements.end(), other.elements.begin(), other.elements.end());
    }
    ValuePtr pop(int index = -1) {
        if (elements.empty()) throw std::runtime_error("pop from empty list");
        if (index < 0) index = elements.size() + index;
        if (index < 0 || static_cast<size_t>(index) >= elements.size())
            throw std::runtime_error("pop index out of range");
        ValuePtr value = elements[index];
        elements.erase(elements.begin() + index);
        return value;
    }
    void insert(int index, ValuePtr value) {
        if (index < 0) index = elements.size() + index;
        if (index < 0 || static_cast<size_t>(index) > elements.size())
            throw std::runtime_error("insert index out of range");
        elements.insert(elements.begin() + index, value);
    }
    void clear() { elements.clear(); }

    size_t len() const { return elements.size(); }

    ValuePtr at(int index) const {
        if (index < 0) index = elements.size() + index;
        if (index < 0 || static_cast<size_t>(index) >= elements.size())
            throw std::runtime_error("index out of range");
        return elements[index];
    }
};

// Add these method declarations to DictValue struct
struct TupleValue {
    std::vector<ValuePtr> elements;
    
    TupleValue() = default;
    TupleValue(const std::vector<ValuePtr>& elems) : elements(elems) {}
    
    size_t size() const { return elements.size(); }
    
    ValuePtr get(size_t index) const {
        if (index >= elements.size()) {
            throw std::runtime_error("Tuple index out of bounds: " + std::to_string(index));
        }
        return elements[index];
    }
    
    void set(size_t index, ValuePtr value) {
        if (index >= elements.size()) {
            throw std::runtime_error("Tuple index out of bounds: " + std::to_string(index));
        }
        elements[index] = value;
    }
    
    std::string toString() const; // Implementation moved to avoid forward declaration issues
};

struct DictValue {
    std::map<ValuePtr, ValuePtr> elements;

    ValuePtr get(const ValuePtr& key, const ValuePtr& defaultValue = nullptr) const {
        auto it = elements.find(key);
        return it != elements.end() ? it->second : defaultValue;
    }
    void setdefault(const ValuePtr& key, const ValuePtr& defaultValue) {
        if (elements.find(key) == elements.end()) {
            elements[key] = defaultValue;
        }
    }
    ValuePtr pop(const ValuePtr& key, const ValuePtr& defaultValue = nullptr) {
        auto it = elements.find(key);
        if (it == elements.end()) {
            if (defaultValue == nullptr) throw std::runtime_error("key not found");
            return defaultValue;
        }
        ValuePtr value = it->second;
        elements.erase(it);
        return value;
    }
    void update(const DictValue& other) {
        for (const auto& [key, value] : other.elements) {
            elements[key] = value;
        }
    }
    void clear() { elements.clear(); }

    size_t len() const { return elements.size(); }

    std::vector<ValuePtr> keys() const {
        std::vector<ValuePtr> result;
        for (const auto& [key, _] : elements) {
            result.push_back(key);
        }
        return result;
    }
    std::vector<ValuePtr> values() const {
        std::vector<ValuePtr> result;
        for (const auto& [_, value] : elements) {
            result.push_back(value);
        }
        return result;
    }
};

// Add toString method to Value struct
struct Value {
    TypePtr type;
                 std::variant<std::monostate,
                 bool,
                 int8_t,
                 int16_t,
                 int32_t,
                 int64_t,
                 uint8_t,
                 uint16_t,
                 uint32_t,
                 uint64_t,
                 double,
                 float,
                 std::string,
                 ListValue,
                 DictValue,
                 TupleValue,
                 SumValue,
                 EnumValue,
                 ErrorValue,
                 UserDefinedValue,
                 IteratorValuePtr,
                 ObjectInstancePtr,
                 std::shared_ptr<backend::ClassDefinition>
    , std::shared_ptr<Channel<ValuePtr>>
    , AtomicValue
    , ModuleValue
    , std::shared_ptr<backend::UserDefinedFunction>
    , backend::Function
    , ClosureValue
                >
        data;

    // Default constructor
    Value() : type(nullptr) {}

    // Constructor with type only
    explicit Value(TypePtr t) : type(std::move(t)) {}

    // String constructors
    Value(TypePtr t, const std::string& str) : type(std::move(t)), data(str) {}

    // String literal constructor
    Value(TypePtr t, const char* str) : type(std::move(t)), data(std::string(str)) {}

    // Boolean constructor
    Value(TypePtr t, bool val) : type(std::move(t)), data(val) {}

    // Floating point constructors
    Value(TypePtr t, float val) : type(std::move(t)), data(val) {
    }

    Value(TypePtr t, double val) : type(std::move(t)), data(val) {
    }

    // Template constructor for integer types - eliminates ambiguity
    template<typename T>
    Value(TypePtr t, T val,
          typename std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>>* = nullptr)
        : type(std::move(t)) {
        

        // Store based on the TypeTag, not the input type
        if (!type) {
            data = static_cast<int32_t>(val);
            return;
        }

        switch (type->tag) {
            case TypeTag::Int8:
                data = safe_cast<int8_t>(val);
                break;
            case TypeTag::Int16:
                data = safe_cast<int16_t>(val);
                break;
            case TypeTag::Int:
            case TypeTag::Int32:
                data = safe_cast<int32_t>(val);
                break;
            case TypeTag::Int64:
                data = safe_cast<int64_t>(val);
                break;
            case TypeTag::UInt8:
                data = safe_cast<uint8_t>(val);
                break;
            case TypeTag::UInt16:
                data = safe_cast<uint16_t>(val);
                break;
            case TypeTag::UInt:
            case TypeTag::UInt32:
                data = safe_cast<uint32_t>(val);
                break;
            case TypeTag::UInt64:
                data = safe_cast<uint64_t>(val);
                break;
            default:
                // Default to int32_t for unspecified integer types
                data = static_cast<int32_t>(val);
        }
    }

    // Move constructor
    Value(Value&& other) noexcept
        : type(std::move(other.type)),
          data(std::move(other.data)) {
        
    }

    // Copy constructor
    Value(const Value& other)
    : type(other.type ? std::make_shared<Type>(*other.type) : nullptr),
      data(other.data) {
   
}

// Update the destructor:
~Value() {
   
}
        // Constructor for ListValue
        Value(TypePtr t, const ListValue& lv) : type(std::move(t)), data(lv) {
           
        }

        // Constructor for TupleValue
        Value(TypePtr t, const TupleValue& tv) : type(std::move(t)), data(tv) {
           
        }

        // Constructor for DictValue
        Value(TypePtr t, const DictValue& dv) : type(std::move(t)), data(dv) {
           
;
        }

        // Constructor for EnumValue
        Value(TypePtr t, const EnumValue& ev) : type(std::move(t)), data(ev) {
           
        }

        // Constructor for ErrorValue
        Value(TypePtr t, const ErrorValue& erv) : type(std::move(t)), data(erv) {
           
        }

        // Constructor for SumValue
        Value(TypePtr t, const SumValue& sv) : type(std::move(t)), data(sv) {
           
;
        }

        // Constructor for UserDefinedValue
        Value(TypePtr t, const UserDefinedValue& udv) : type(std::move(t)), data(udv) {
           
        }

        // Constructor for IteratorValuePtr
        Value(TypePtr t, const IteratorValuePtr& iter) : type(std::move(t)), data(iter) {
        }

    // Constructor for Channel pointer
    Value(TypePtr t, const std::shared_ptr<Channel<ValuePtr>>& ch) : type(std::move(t)), data(ch) {
    }

    // Constructor for AtomicValue
    Value(TypePtr t, const AtomicValue& av) : type(std::move(t)), data(av) {}

        // Constructor for ObjectInstancePtr
        Value(TypePtr t, const ObjectInstancePtr& obj) : type(std::move(t)), data(obj) {
        }

        // Constructor for UserDefinedFunction
        Value(TypePtr t, const std::shared_ptr<backend::UserDefinedFunction>& func) : type(std::move(t)), data(func) {}

        // Constructor for backend::Function
        Value(TypePtr t, const backend::Function& func) : type(std::move(t)), data(func) {}

        // Constructor for ClosureValue
        Value(TypePtr t, const ClosureValue& closure) : type(std::move(t)), data(closure) {}

    bool isError() const {
        // An error can be a direct ErrorValue or an ErrorUnion holding an ErrorValue.
        if (type && type->tag == TypeTag::ErrorUnion) {
            return std::holds_alternative<ErrorValue>(data);
        }
        return std::holds_alternative<ErrorValue>(data);
    }

    const ErrorValue* getErrorValue() const {
        if (isError()) {
            return std::get_if<ErrorValue>(&data);
        }
        return nullptr;
    }

    friend std::ostream &operator<<(std::ostream &os, const Value &value);

    // Get raw string representation for interpolation/concatenation (no quotes)
    std::string getRawString() const {
        std::ostringstream oss;
        std::visit(overloaded{
            [&](const std::monostate&) { oss << "nil"; },
            [&](bool b) { oss << (b ? "true" : "false"); },
            [&](int8_t i) { oss << static_cast<int>(i); },
            [&](int16_t i) { oss << i; },
            [&](int32_t i) { oss << i; },
            [&](int64_t i) { oss << i; },
            [&](uint8_t u) { oss << static_cast<unsigned>(u); },
            [&](uint16_t u) { oss << u; },
            [&](uint32_t u) { oss << u; },
            [&](uint64_t u) { oss << u; },
            [&](float f) { oss << f; },
            [&](double d) { oss << d; },
            [&](const std::string& s) { oss << s; }, // No quotes for raw string
            [&](const ListValue& lv) {
                oss << "[";
                for (size_t i = 0; i < lv.elements.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << lv.elements[i]->getRawString();
                }
                oss << "]";
            },
            [&](const DictValue& dv) {
                oss << "{";
                bool first = true;
                for (const auto& [key, value] : dv.elements) {
                    if (!first) oss << ", ";
                    first = false;
                    oss << key->getRawString() << ": " << value->getRawString();
                }
                oss << "}";
            },
            [&](const TupleValue& tv) {
                oss << "(";
                for (size_t i = 0; i < tv.elements.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << tv.elements[i]->getRawString();
                }
                oss << ")";
            },
            [&](const SumValue& sv) {
                oss << "Sum(" << sv.activeVariant << ", " << sv.value->getRawString() << ")";
            },
            [&](const EnumValue& ev) {
                oss << ev.toString(); // Use existing enum toString
            },
            [&](const ErrorValue& erv) {
                oss << erv.toString();
            },
            [&](const UserDefinedValue& udv) {
                oss << udv.variantName << "{";
                bool first = true;
                for (const auto& [field, value] : udv.fields) {
                    if (!first) oss << ", ";
                    first = false;
                    oss << field << ": " << value->getRawString();
                }
                oss << "}";
            },
            [&](const IteratorValuePtr&) {
                oss << "<iterator>";
            },
            [&](const std::shared_ptr<Channel<ValuePtr>>&){
                oss << "<channel>";
            },
            [&](const AtomicValue& av) {
                // Print the current atomic integer value
                if (av.inner) {
                    oss << av.inner->load();
                } else {
                    oss << "<atomic(nil)>";
                }
            },
            [&](const ObjectInstancePtr& obj) {
                oss << "<object>";
            },
            [&](const std::shared_ptr<backend::ClassDefinition>&) {
                oss << "<class>";
            },
            [&](const ModuleValue&) {
                oss << "<module>";
            },
            [&](const std::shared_ptr<backend::UserDefinedFunction>&) {
                oss << "<function>";
            },
            [&](const backend::Function& func) {
                oss << "<function:" << func.name << ">";
            },
            [&](const ClosureValue& closure) {
                oss << closure.toString();
            }
        }, data);
        return oss.str();
    }

    std::string toString() const {
        std::ostringstream oss;
        std::visit(overloaded{
            [&](const std::monostate&) { oss << "nil"; },
            [&](bool b) { oss << (b ? "true" : "false"); },
            [&](int8_t i) { oss << static_cast<int>(i); },
            [&](int16_t i) { oss << i; },
            [&](int32_t i) { oss << i; },
            [&](int64_t i) { oss << i; },
            [&](uint8_t u) { oss << static_cast<unsigned>(u); },
            [&](uint16_t u) { oss << u; },
            [&](uint32_t u) { oss << u; },
            [&](uint64_t u) { oss << u; },
            [&](float f) { oss << f; },
            [&](double d) { oss << d; },
            [&](const std::string& s) { oss << '"' << s << '"'; },
            [&](const ListValue& lv) {
                oss << "[";
                for (size_t i = 0; i < lv.elements.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << lv.elements[i]->toString();
                }
                oss << "]";
            },
            [&](const DictValue& dv) {
                oss << "{";
                bool first = true;
                for (const auto& [key, value] : dv.elements) {
                    if (!first) oss << ", ";
                    first = false;
                    oss << key->toString() << ": " << value->toString();
                }
                oss << "}";
            },
            [&](const TupleValue& tv) {
                oss << tv.toString();
            },
            [&](const SumValue& sv) {
                oss << "Sum(" << sv.activeVariant << ", " << sv.value->toString() << ")";
            },
            [&](const EnumValue& ev) { oss << ev.toString(); },
            [&](const ErrorValue& erv) { oss << erv.toString(); },
            [&](const UserDefinedValue& udv) {
                oss << udv.variantName << "{";
                bool first = true;
                for (const auto& [field, value] : udv.fields) {
                    if (!first) oss << ", ";
                    first = false;
                    oss << field << ": " << value->toString();
                }
                oss << "}";
            },
            [&](const IteratorValuePtr&) {
                oss << "<iterator>";
            },
            [&](const std::shared_ptr<Channel<ValuePtr>>&){
                oss << "<channel>";
            },
            [&](const AtomicValue& av) {
                if (av.inner) {
                    oss << av.inner->load();
                } else {
                    oss << "<atomic(nil)>";
                }
            },
            [&](const ObjectInstancePtr& obj) {
                oss << "<object>";
            },
            [&](const std::shared_ptr<backend::ClassDefinition>&) {
                oss << "<class>";
            },
            [&](const ModuleValue&) {
                oss << "<module>";
            },
            [&](const std::shared_ptr<backend::UserDefinedFunction>&) {
                oss << "<function>";
            },
            [&](const backend::Function& func) {
                oss << "<function:" << func.name << ">";
            },
            [&](const ClosureValue& closure) {
                oss << closure.toString();
            }
        }, data);
        return oss.str();
    }
};

// FunctionType method implementations
inline bool FunctionType::isCompatibleWith(const FunctionType& other) const {
    // Check parameter count
    if (paramTypes.size() != other.paramTypes.size()) {
        return false;
    }
    
    // Check parameter types (contravariant - parameters can be more general in target)
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        // For function parameters, the target type should accept what the source provides
        // This means other.paramTypes[i] should be assignable from paramTypes[i]
        if (!paramTypes[i] || !other.paramTypes[i]) {
            return false;
        }
        // Note: This would need access to TypeSystem for proper compatibility checking
        // For now, we'll do a simple type tag comparison
        if (paramTypes[i]->tag != other.paramTypes[i]->tag) {
            return false;
        }
    }
    
    // Check return type (covariant - return type can be more specific in source)
    if (returnType && other.returnType) {
        if (returnType->tag != other.returnType->tag) {
            return false;
        }
    } else if (returnType != other.returnType) {
        return false; // One has return type, other doesn't
    }
    
    return true;
}

inline std::string FunctionType::toString() const {
    std::ostringstream oss;
    oss << "fn(";
    
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        if (i > 0) oss << ", ";
        
        // Add parameter name if available
        if (i < paramNames.size() && !paramNames[i].empty()) {
            oss << paramNames[i] << ": ";
        }
        
        // Add parameter type
        if (paramTypes[i]) {
            oss << paramTypes[i]->toString();
        } else {
            oss << "unknown";
        }
        
        // Add default indicator if applicable
        if (i < hasDefaultValues.size() && hasDefaultValues[i]) {
            oss << "?";
        }
    }
    
    if (isVariadic) {
        if (!paramTypes.empty()) oss << ", ";
        oss << "...";
    }
    
    oss << ")";
    
    // Add return type
    if (returnType) {
        oss << ": " << returnType->toString();
    }
    
    return oss.str();
}

// Error value construction and inspection utility functions
namespace ErrorUtils {
    // Create an error value
    inline ValuePtr createError(const std::string& errorType, const std::string& message = "", 
                               const std::vector<ValuePtr>& args = {}, size_t location = 0) {
        auto errorValue = std::make_shared<Value>();
        errorValue->type = std::make_shared<Type>(TypeTag::UserDefined); // Error types are user-defined
        errorValue->data = ErrorValue(errorType, message, args, location);
        return errorValue;
    }

    // Create a success value wrapped in an error union
    inline ValuePtr createSuccess(ValuePtr successValue, TypePtr errorUnionType) {
        auto value = std::make_shared<Value>(errorUnionType);
        value->data = successValue->data;
        return value;
    }

    // Create an error union value from ErrorUnion helper
    inline ValuePtr createErrorUnionValue(const ErrorUnion& errorUnion, TypePtr errorUnionType) {
        return errorUnion.toValue(errorUnionType);
    }

    // Check if a value is an error
    inline bool isError(const ValuePtr& value) {
        return std::holds_alternative<ErrorValue>(value->data);
    }

    // Check if a value is a success value (not an error)
    inline bool isSuccess(const ValuePtr& value) {
        return !isError(value);
    }

    // Extract error value from a Value (throws if not an error)
    inline const ErrorValue& getError(const ValuePtr& value) {
        if (auto errorValue = std::get_if<ErrorValue>(&value->data)) {
            return *errorValue;
        }
        throw std::runtime_error("Value is not an error");
    }

    // Extract error value safely (returns nullptr if not an error)
    inline const ErrorValue* getErrorSafe(const ValuePtr& value) {
        return std::get_if<ErrorValue>(&value->data);
    }

    // Get error type from a value (empty string if not an error)
    inline std::string getErrorType(const ValuePtr& value) {
        if (auto errorValue = std::get_if<ErrorValue>(&value->data)) {
            return errorValue->errorType;
        }
        return "";
    }

    // Get error message from a value (empty string if not an error)
    inline std::string getErrorMessage(const ValuePtr& value) {
        if (auto errorValue = std::get_if<ErrorValue>(&value->data)) {
            return errorValue->message;
        }
        return "";
    }

    // Get error arguments from a value (empty vector if not an error)
    inline std::vector<ValuePtr> getErrorArguments(const ValuePtr& value) {
        if (auto errorValue = std::get_if<ErrorValue>(&value->data)) {
            return errorValue->arguments;
        }
        return {};
    }

    // Get error source location from a value (0 if not an error)
    inline size_t getErrorLocation(const ValuePtr& value) {
        if (auto errorValue = std::get_if<ErrorValue>(&value->data)) {
            return errorValue->sourceLocation;
        }
        return 0;
    }

    // Wrap a success value in an error union type
    inline ValuePtr wrapAsSuccess(ValuePtr successValue, TypePtr errorUnionType) {
        auto value = std::make_shared<Value>(errorUnionType);
        value->data = successValue->data;
        return value;
    }

    // Wrap an error value in an error union type
    inline ValuePtr wrapAsError(const ErrorValue& errorValue, TypePtr errorUnionType) {
        auto value = std::make_shared<Value>(errorUnionType);
        value->data = errorValue;
        return value;
    }

    // Create an error union value from ErrorUnion helper
    inline ValuePtr createErrorUnion(const ErrorUnion& errorUnion, TypePtr errorUnionType) {
        return errorUnion.toValue(errorUnionType);
    }

    // Unwrap success value (throws if error)
    inline ValuePtr unwrapSuccess(const ValuePtr& value) {
        if (isError(value)) {
            throw std::runtime_error("Attempted to unwrap error as success");
        }
        return value;
    }

    // Unwrap success value safely (returns nullptr if error)
    inline ValuePtr unwrapSuccessSafe(const ValuePtr& value) {
        return isError(value) ? nullptr : value;
    }

    // Built-in error creation functions
    inline ValuePtr createDivisionByZeroError(const std::string& message = "Division by zero") {
        return createError("DivisionByZero", message);
    }

    inline ValuePtr createIndexOutOfBoundsError(const std::string& message = "Index out of bounds") {
        return createError("IndexOutOfBounds", message);
    }

    inline ValuePtr createNullReferenceError(const std::string& message = "Null reference access") {
        return createError("NullReference", message);
    }

    inline ValuePtr createTypeConversionError(const std::string& message = "Type conversion failed") {
        return createError("TypeConversion", message);
    }

    inline ValuePtr createIOError(const std::string& message = "I/O operation failed") {
        return createError("IOError", message);
    }

    // Error type compatibility checking
    inline bool areErrorTypesCompatible(const std::string& errorType1, const std::string& errorType2) {
        return errorType1 == errorType2;
    }
}

// Iterator for list and range values
struct IteratorValue {
    enum class IteratorType {
        LIST,
        RANGE,
        CHANNEL
    };

    IteratorType type;
    size_t index;
    ValuePtr container;
    // For channel iterators: a buffered value received by hasNext()
    bool hasBuffered = false;
    ValuePtr bufferedValue;
    
    IteratorValue(IteratorType t, ValuePtr c) 
        : type(t), index(0), container(std::move(c)) {}
    
    bool hasNext() {
        if (!container) return false;
        
        if (type == IteratorType::LIST) {
            // For LIST type, the data should be a ListValue
            if (auto list = std::get_if<ListValue>(&container->data)) {
                return index < list->elements.size();
            }
        } else if (type == IteratorType::RANGE) { // RANGE
            // For RANGE, we need to get the range bounds from the container
            // First, check if the container has a ListValue (materialized range)
            if (auto list = std::get_if<ListValue>(&container->data)) {
                return index < list->elements.size();
            }
        } else if (type == IteratorType::CHANNEL) {
            // If we already buffered a value, we have next
            if (hasBuffered) return true;

            // Attempt to receive from the channel (this will block until value or closed)
            try {
                if (auto chPtr = std::get_if<std::shared_ptr<Channel<ValuePtr>>>(&container->data)) {
                    ValuePtr v;
                    bool ok = (*chPtr)->receive(v);
                    if (ok) {
                        bufferedValue = v;
                        hasBuffered = true;
                        return true;
                    }
                    return false; // channel closed and no value
                }
            } catch (...) {
                return false;
            }
        }
        return false;
    }
    
    ValuePtr next() {
        if (!hasNext()) {
            throw std::runtime_error("No more elements in iterator");
        }
        
        if (type == IteratorType::LIST) {
            if (auto list = std::get_if<ListValue>(&container->data)) {
                if (index < list->elements.size()) {
                    return list->elements[index++];
                }
            }
            throw std::runtime_error("Invalid list iterator state");
        } else if (type == IteratorType::RANGE) { // RANGE
            // Handle both materialized (ListValue) and unmaterialized ranges
            if (auto list = std::get_if<ListValue>(&container->data)) {
                // If this is a materialized range (list of values)
                if (index < list->elements.size()) {
                    return list->elements[index++];
                }
            }
            
            throw std::runtime_error("Invalid range iterator state");
        } else if (type == IteratorType::CHANNEL) {
            if (hasBuffered) {
                auto res = bufferedValue;
                bufferedValue = nullptr;
                hasBuffered = false;
                return res;
            }
            // As a fallback, try to receive directly
            if (auto chPtr = std::get_if<std::shared_ptr<Channel<ValuePtr>>>(&container->data)) {
                ValuePtr v;
                bool ok = (*chPtr)->receive(v);
                if (ok) return v;
                throw std::runtime_error("No more elements in iterator");
            }
            throw std::runtime_error("Invalid channel iterator state");
        }
        throw std::runtime_error("Invalid iterator type");
    }
    
};



// Implementation of operator<< for Value
inline std::ostream &operator<<(std::ostream &os, const Value &value) {
    os << value.toString();
    return os;
}

// Forward declare the rest of the Value class to fix circular dependency

// Define the operator<< for ListValue
inline std::ostream &operator<<(std::ostream &os, const ListValue &lv)
{
    os << "[";
    for (size_t i = 0; i < lv.elements.size(); ++i) {
        if (i > 0)
            os << ", ";
        os << lv.elements[i];
    }
    os << "]";
    return os;
}

// Define the operator<< for DictValue
inline std::ostream &operator<<(std::ostream &os, const DictValue &dv)
{
    os << "{";
    bool first = true;
    for (const auto &[key, value] : dv.elements) {
        if (!first)
            os << ", ";
        first = false;
        os << key << ": " << value;
    }
    os << "}";
    return os;
}

// Define the operator<< for UserDefinedValue
inline std::ostream &operator<<(std::ostream &os, const UserDefinedValue &udv)
{
    os << udv.variantName << "{";
    bool first = true;
    for (const auto &[field, value] : udv.fields) {
        if (!first)
            os << ", ";
        first = false;
        os << field << ": " << value;
    }
    os << "}";
    return os;
}

// Define the operator<< for SumValue
inline std::ostream &operator<<(std::ostream &os, const SumValue &udv)
{
    os << "Variant" << udv.activeVariant << "(";
    os << *udv.value;
    os << ")";
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const std::monostate &)
{
    return os << "Nil";
}

// Update the operator<< for EnumValue
inline std::ostream &operator<<(std::ostream &os, const EnumValue &ev) {
    os << ev.toString();
    return os;
}

// Define the operator<< for ErrorValue
inline std::ostream &operator<<(std::ostream &os, const ErrorValue &erv) {
    os << erv.toString();
    return os;
}
// Define the operator<< for ValuePtr
inline std::ostream &operator<<(std::ostream &os, const ValuePtr &valuePtr)
{
    if (valuePtr) {
        os << *valuePtr;
    } else {
        os << "nullptr";
    }
    return os;
}
// ClosureValue factory method implementation
namespace ClosureValueFactory {
    inline ValuePtr createClosure(std::shared_ptr<backend::UserDefinedFunction> func,
                                 std::shared_ptr<::Environment> capturedEnv,
                                 const std::vector<std::string>& capturedVars,
                                 TypePtr closureType) {
        if (!func) {
            throw std::runtime_error("Cannot create closure: function is null");
        }
        
        // Create closure type if not provided
        if (!closureType) {
            closureType = std::make_shared<Type>(TypeTag::Closure);
        }
        
        // Create the closure value - for now use placeholder values since this factory
        // is used for backward compatibility. The VM will create closures directly.
        ClosureValue closure("closure", 0, 0, capturedEnv, capturedVars);
        
        // Return as ValuePtr
        return std::make_shared<Value>(closureType, closure);
    }
}



// ClosureValue::create implementation
inline ValuePtr ClosureValue::create(std::shared_ptr<backend::UserDefinedFunction> func,
                                    std::shared_ptr<Environment> capturedEnv,
                                    const std::vector<std::string>& capturedVars) {
    TypePtr closureType = std::make_shared<Type>(TypeTag::Closure);
    return ClosureValueFactory::createClosure(func, capturedEnv, capturedVars, closureType);
}