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
    Range,
    UserDefined
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

struct Type
{
    TypeTag tag;
    std::variant<std::monostate, ListType, DictType, EnumType, FunctionType, SumType, UnionType, UserDefinedType>
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
        case TypeTag::UserDefined:
            return "UserDefined";
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
                 UserDefinedValue,
                 IteratorValuePtr>
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

    friend std::ostream &operator<<(std::ostream &os, const Value &value);

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