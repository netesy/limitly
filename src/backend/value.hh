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

// Forward declarations
struct Value;
using ValuePtr = std::shared_ptr<Value>;

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
}
using ObjectInstancePtr = std::shared_ptr<backend::ObjectInstance>;

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
    Enum,
    Function,
    Any,
    Sum,
    Union,
    ErrorUnion,
    Range,
    UserDefined,
    Class,
    Object
};

struct Type;
using TypePtr = std::shared_ptr<Type>;

struct ListType
{
    TypePtr elementType;
};

struct DictType
{
    TypePtr keyType;
    TypePtr valueType;
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
    std::vector<TypePtr> paramTypes;
    TypePtr returnType;
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
    std::variant<std::monostate, ListType, DictType, EnumType, FunctionType, SumType, UnionType, ErrorUnionType, UserDefinedType>
        extra;

    Type(TypeTag t)
        : tag(t)
    {}
    Type(TypeTag t,
         const std::variant<std::monostate,
                            ListType,
                            DictType,
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
        case TypeTag::Enum:
            return "Enum";
        case TypeTag::Function:
            return "Function";
        case TypeTag::Any:
            return "Any";
        case TypeTag::Sum:
            return "Sum";
        case TypeTag::Union:
            return "Union";
        case TypeTag::ErrorUnion:
            return "ErrorUnion";
        case TypeTag::UserDefined:
            return "UserDefined";
        case TypeTag::Object:
            return "Object";
        case TypeTag::Class:
            return "Class";
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

// ErrorUnion helper class for efficient tagged union operations
class ErrorUnion {
public:
    enum class Tag : uint8_t { SUCCESS, ERROR };

private:
    Tag tag_;
    union {
        ValuePtr successValue_;
        ErrorValue errorValue_;
    };

public:
    // Constructors
    ErrorUnion(ValuePtr success) : tag_(Tag::SUCCESS), successValue_(success) {}
    
    ErrorUnion(const ErrorValue& error) : tag_(Tag::ERROR) {
        new (&errorValue_) ErrorValue(error);
    }
    
    ErrorUnion(const std::string& errorType, const std::string& message = "", 
               const std::vector<ValuePtr>& args = {}, size_t location = 0) 
        : tag_(Tag::ERROR) {
        new (&errorValue_) ErrorValue(errorType, message, args, location);
    }

    // Copy constructor
    ErrorUnion(const ErrorUnion& other) : tag_(other.tag_) {
        if (tag_ == Tag::SUCCESS) {
            successValue_ = other.successValue_;
        } else {
            new (&errorValue_) ErrorValue(other.errorValue_);
        }
    }

    // Move constructor
    ErrorUnion(ErrorUnion&& other) noexcept : tag_(other.tag_) {
        if (tag_ == Tag::SUCCESS) {
            successValue_ = std::move(other.successValue_);
        } else {
            new (&errorValue_) ErrorValue(std::move(other.errorValue_));
        }
    }

    // Assignment operators - use copy-and-swap idiom
    ErrorUnion& operator=(const ErrorUnion& other) {
        if (this != &other) {
            // Destroy current content
            if (tag_ == Tag::ERROR) {
                errorValue_.~ErrorValue();
            }
            
            // Copy new content
            tag_ = other.tag_;
            if (tag_ == Tag::SUCCESS) {
                successValue_ = other.successValue_;
            } else {
                new (&errorValue_) ErrorValue(other.errorValue_);
            }
        }
        return *this;
    }

    ErrorUnion& operator=(ErrorUnion&& other) noexcept {
        if (this != &other) {
            // Destroy current content
            if (tag_ == Tag::ERROR) {
                errorValue_.~ErrorValue();
            }
            
            // Move new content
            tag_ = other.tag_;
            if (tag_ == Tag::SUCCESS) {
                successValue_ = std::move(other.successValue_);
            } else {
                new (&errorValue_) ErrorValue(std::move(other.errorValue_));
            }
        }
        return *this;
    }

    // Destructor
    ~ErrorUnion() {
        if (tag_ == Tag::ERROR) {
            errorValue_.~ErrorValue();
        }
    }

    // Inspection methods
    bool isSuccess() const { return tag_ == Tag::SUCCESS; }
    bool isError() const { return tag_ == Tag::ERROR; }
    Tag getTag() const { return tag_; }

    // Value access methods
    ValuePtr getSuccessValue() const {
        if (tag_ != Tag::SUCCESS) {
            throw std::runtime_error("Attempted to get success value from error union");
        }
        return successValue_;
    }

    const ErrorValue& getErrorValue() const {
        if (tag_ != Tag::ERROR) {
            throw std::runtime_error("Attempted to get error value from success union");
        }
        return errorValue_;
    }

    // Safe access methods
    ValuePtr getSuccessValueOr(ValuePtr defaultValue) const {
        return isSuccess() ? successValue_ : defaultValue;
    }

    std::string getErrorType() const {
        return isError() ? errorValue_.errorType : "";
    }

    std::string getErrorMessage() const {
        return isError() ? errorValue_.message : "";
    }

    // Conversion to Value
    ValuePtr toValue(TypePtr errorUnionType) const;  // Declaration, definition after Value struct

    // Static factory methods
    static ErrorUnion success(ValuePtr value) {
        return ErrorUnion(value);
    }

    static ErrorUnion error(const std::string& errorType, const std::string& message = "", 
                           const std::vector<ValuePtr>& args = {}, size_t location = 0) {
        return ErrorUnion(errorType, message, args, location);
    }

    static ErrorUnion error(const ErrorValue& errorValue) {
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
                 SumValue,
                 EnumValue,
                 ErrorValue,
                 UserDefinedValue,
                 IteratorValuePtr,
                 ObjectInstancePtr,
                 std::shared_ptr<backend::ClassDefinition>
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

        // Constructor for ObjectInstancePtr
        Value(TypePtr t, const ObjectInstancePtr& obj) : type(std::move(t)), data(obj) {
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
            [&](const ObjectInstancePtr& obj) {
                oss << "<object>";
            },
            [&](const std::shared_ptr<backend::ClassDefinition>&) {
                oss << "<class>";
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
            [&](const ObjectInstancePtr& obj) {
                oss << "<object>";
            },
            [&](const std::shared_ptr<backend::ClassDefinition>&) {
                oss << "<class>";
            }
        }, data);
        return oss.str();
    }
};

inline ValuePtr EnumValue::create(const std::string& variantName, const TypePtr& enumType, ValuePtr associatedValue) {
    auto value = std::make_shared<Value>(enumType);
    value->data = EnumValue(variantName, enumType, associatedValue);
    return value;
}

// ErrorValue toString implementation (defined after Value struct)
inline std::string ErrorValue::toString() const {
    std::ostringstream oss;
    oss << "Error(" << errorType;
    if (!message.empty()) {
        oss << ", \"" << message << "\"";
    }
    if (!arguments.empty()) {
        oss << ", [";
        for (size_t i = 0; i < arguments.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << arguments[i]->toString();
        }
        oss << "]";
    }
    oss << ")";
    return oss.str();
}

// ErrorUnion toValue implementation (defined after Value struct)
inline ValuePtr ErrorUnion::toValue(TypePtr errorUnionType) const {
    auto value = std::make_shared<Value>(errorUnionType);
    
    if (isSuccess()) {
        // For success values, store the actual success data
        value->data = successValue_->data;
    } else {
        // For error values, store the ErrorValue
        value->data = errorValue_;
    }
    
    return value;
}

// ErrorUnion toString implementation (defined after Value struct)
inline std::string ErrorUnion::toString() const {
    if (isSuccess()) {
        return "Success(" + (successValue_ ? successValue_->toString() : "null") + ")";
    } else {
        return "Error(" + errorValue_.toString() + ")";
    }
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
        RANGE
    };

    IteratorType type;
    size_t index;
    ValuePtr container;
    
    IteratorValue(IteratorType t, ValuePtr c) 
        : type(t), index(0), container(std::move(c)) {}
    
    bool hasNext() {
        if (!container) return false;
        
        if (type == IteratorType::LIST) {
            // For LIST type, the data should be a ListValue
            if (auto list = std::get_if<ListValue>(&container->data)) {
                return index < list->elements.size();
            }
        } else { // RANGE
            // For RANGE, we need to get the range bounds from the container
            // First, check if the container has a ListValue (materialized range)
            if (auto list = std::get_if<ListValue>(&container->data)) {
                return index < list->elements.size();
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
        } else { // RANGE
            // Handle both materialized (ListValue) and unmaterialized ranges
            if (auto list = std::get_if<ListValue>(&container->data)) {
                // If this is a materialized range (list of values)
                if (index < list->elements.size()) {
                    return list->elements[index++];
                }
            }
            
            throw std::runtime_error("Invalid range iterator state");
        }
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