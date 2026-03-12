// src/lm/backend/value.hh
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
#include <iomanip>
#include <optional>
#include <charconv>
#include <atomic>

namespace LM {
namespace Backend {

// Forward declarations
struct Value;
using ValuePtr = std::shared_ptr<Value>;

struct Type;
using TypePtr = std::shared_ptr<Type>;

struct ListValue;
struct DictValue;
struct TupleValue;
struct SumValue;
struct EnumValue;
struct ErrorValue;
struct UserDefinedValue;
struct IteratorValue;
using IteratorValuePtr = std::shared_ptr<IteratorValue>;

class Environment;

namespace backend {
    class ObjectInstance;
    class ClassDefinition;
    class UserDefinedFunction;
    struct Function {
        std::string name;
        size_t startAddress = 0;
        size_t endAddress = 0;
        TypePtr returnType = nullptr;
    };
}
using ObjectInstancePtr = std::shared_ptr<backend::ObjectInstance>;

namespace Register {
    struct Channel;
}

// Type Tags
enum class TypeTag {
    Nil, Bool, Int, Int8, Int16, Int32, Int64, Int128,
    UInt, UInt8, UInt16, UInt32, UInt64, UInt128,
    Float32, Float64, String, List, Dict, Tuple, Enum,
    Function, Closure, Any, Sum, Union, ErrorUnion, Range,
    UserDefined, Channel, Object, Module, Frame, Trait, TraitObject
};

// Structural Types
struct ListType { TypePtr elementType; };
struct DictType { TypePtr keyType; TypePtr valueType; };

struct TupleType {
    std::vector<TypePtr> elementTypes;
    TupleType() = default;
    TupleType(const std::vector<TypePtr>& types) : elementTypes(types) {}
    size_t size() const { return elementTypes.size(); }
    std::string toString() const;
};

struct EnumType {
    std::vector<std::string> values;
    void addVariant(const std::string& name) { values.push_back(name); }
    std::string toString() const;
};

struct FunctionType {
    std::vector<TypePtr> paramTypes;
    TypePtr returnType;
    std::vector<std::string> paramNames;
    std::vector<bool> hasDefaultValues;
    bool isVariadic = false;
    
    FunctionType() = default;
    FunctionType(const std::vector<TypePtr>& params, TypePtr ret)
        : paramTypes(params), returnType(ret) {
        hasDefaultValues.resize(params.size(), false);
    }
    std::string toString() const;
};

struct UserDefinedType { std::string name; };
struct SumType { std::vector<TypePtr> variants; };
struct UnionType { std::vector<TypePtr> types; };
struct ErrorUnionType {
    TypePtr successType;
    std::vector<std::string> errorTypes;
    bool isGenericError = false;
};
struct FrameType { std::string name; };
struct TraitType { std::string name; };
struct TraitObjectType { std::string traitName; TypePtr underlyingType; };

// Type Definition
struct Type {
    TypeTag tag;
    std::variant<std::monostate, ListType, DictType, TupleType, EnumType, FunctionType, SumType, UnionType, ErrorUnionType, UserDefinedType, FrameType, TraitType, TraitObjectType> extra;

    Type(TypeTag t) : tag(t) {}
    Type(TypeTag t, const decltype(extra)& ex) : tag(t), extra(ex) {}

    std::string toString() const {
        switch (tag) {
            case TypeTag::Nil: return "Nil";
            case TypeTag::Bool: return "Bool";
            case TypeTag::Int: return "Int";
            case TypeTag::Int64: return "Int64";
            case TypeTag::Float64: return "Float64";
            case TypeTag::String: return "String";
            case TypeTag::Any: return "Any";
            case TypeTag::Frame: {
                if (const auto* ft = std::get_if<FrameType>(&extra)) return "Frame<" + ft->name + ">";
                return "Frame";
            }
            case TypeTag::Trait: {
                if (const auto* tt = std::get_if<TraitType>(&extra)) return "Trait<" + tt->name + ">";
                return "Trait";
            }
            case TypeTag::ErrorUnion: return "ErrorUnion";
            case TypeTag::List: return "List";
            case TypeTag::Tuple: {
                if (const auto* tt = std::get_if<TupleType>(&extra)) return tt->toString();
                return "Tuple";
            }
            case TypeTag::Function: return "Function";
            default: return "Type";
        }
    }
};

// Converters
namespace ValueConverters {
    inline std::optional<int64_t> toInt64(const std::string& str) {
        int64_t result = 0;
        if (str.empty()) return std::nullopt;
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
        return (ec == std::errc()) ? std::make_optional(result) : std::nullopt;
    }
    inline std::optional<double> toDouble(const std::string& str) {
        try { return std::stod(str); } catch (...) { return std::nullopt; }
    }
    inline bool toBool(const std::string& str) {
        return !str.empty() && str != "0" && str != "false";
    }
    template<typename T>
    inline T safeConvert(const std::string& str, T defaultValue = T{}) {
        if constexpr (std::is_same_v<T, int64_t>) { if (auto val = toInt64(str)) return *val; }
        else if constexpr (std::is_same_v<T, double>) { if (auto val = toDouble(str)) return *val; }
        else if constexpr (std::is_same_v<T, bool>) { return toBool(str); }
        return defaultValue;
    }
}

// Complex Value Structures
struct ListValue { std::vector<ValuePtr> elements; };
struct DictValue { std::map<ValuePtr, ValuePtr> elements; };
struct TupleValue {
    std::vector<ValuePtr> elements;
    std::string toString() const;
};
struct SumValue { size_t activeVariant; ValuePtr value; };
struct EnumValue {
    std::string variantName;
    ValuePtr associatedValue;
    std::string toString() const { return "Enum(" + variantName + ")"; }
};
struct ErrorValue {
    std::string errorType;
    std::string message;
    std::vector<ValuePtr> arguments;
    ErrorValue() = default;
    ErrorValue(const std::string& t, const std::string& m = "") : errorType(t), message(m) {}
    std::string toString() const { return errorType + ": " + message; }
};
struct UserDefinedValue { std::string variantName; std::map<std::string, ValuePtr> fields; };

struct AtomicValue {
    std::shared_ptr<std::atomic<int64_t>> inner;
    AtomicValue() : inner(std::make_shared<std::atomic<int64_t>>(0)) {}
    AtomicValue(int64_t v) : inner(std::make_shared<std::atomic<int64_t>>(v)) {}
};

struct ClosureValue {
    std::string functionName;
    size_t startAddress;
    size_t endAddress;
    std::shared_ptr<Environment> capturedEnvironment;
    std::vector<std::string> capturedVariables;
    std::string toString() const { return "Closure(" + functionName + ")"; }
};

struct Value {
    TypePtr type;
    std::string data;
    size_t activeUnionVariant = 0;
    std::variant<std::monostate, ListValue, DictValue, TupleValue, SumValue, EnumValue, ErrorValue, UserDefinedValue, IteratorValuePtr, ObjectInstancePtr, std::shared_ptr<backend::ClassDefinition>, std::shared_ptr<Register::Channel>, AtomicValue, std::shared_ptr<Environment>, std::shared_ptr<backend::UserDefinedFunction>, backend::Function, ClosureValue> complexData;

    Value() : type(nullptr), data("") {}
    explicit Value(TypePtr t) : type(t), data("") {}
    Value(TypePtr t, const std::string& str) : type(t), data(str) {}
    Value(TypePtr t, int64_t val) : type(t), data(std::to_string(val)) {}
    Value(TypePtr t, double val) : type(t), data(std::to_string(val)) {}
    Value(TypePtr t, bool val) : type(t), data(val ? "true" : "false") {}

    template<typename T>
    T as() const {
        if constexpr (std::is_same_v<T, int64_t>) return ValueConverters::safeConvert<int64_t>(data);
        if constexpr (std::is_same_v<T, double>) return ValueConverters::safeConvert<double>(data);
        if constexpr (std::is_same_v<T, bool>) return ValueConverters::toBool(data);
        if constexpr (std::is_same_v<T, std::string>) return data;
        throw std::runtime_error("Unsupported as<T>");
    }

    std::string toString() const {
        if (type && type->tag == TypeTag::String) return data;
        if (!data.empty()) return data;
        return "<complex>";
    }
};

struct IteratorValue {
    virtual bool hasNext() const = 0;
    virtual ValuePtr next() = 0;
    virtual ~IteratorValue() = default;
};

// ErrorUnion helper class
class ErrorUnion {
public:
    enum class Tag : uint8_t { SUCCESS, ERROR };
private:
    Tag tag_;
    ValuePtr successValue_;
    ErrorValue errorValue_;
public:
    ErrorUnion(ValuePtr success) : tag_(Tag::SUCCESS), successValue_(success) {}
    ErrorUnion(const ErrorValue& error) : tag_(Tag::ERROR), errorValue_(error) {}
    bool isSuccess() const { return tag_ == Tag::SUCCESS; }
    bool isError() const { return tag_ == Tag::ERROR; }
    ValuePtr getSuccessValue() const { return successValue_; }
    const ErrorValue& getErrorValue() const { return errorValue_; }
};

// Implementation of toString for structural types
inline std::string TupleType::toString() const {
    std::string res = "(";
    for (size_t i = 0; i < elementTypes.size(); ++i) {
        if (i > 0) res += ", ";
        if (elementTypes[i]) res += elementTypes[i]->toString();
        else res += "null";
    }
    return res + ")";
}

inline std::string FunctionType::toString() const {
    std::string res = "fn(";
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        if (i > 0) res += ", ";
        if (paramTypes[i]) res += paramTypes[i]->toString();
    }
    res += ")";
    if (returnType) res += ": " + returnType->toString();
    return res;
}

inline std::string TupleValue::toString() const {
    std::string res = "(";
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) res += ", ";
        if (elements[i]) res += elements[i]->toString();
        else res += "nil";
    }
    return res + ")";
}

} // namespace Backend
} // namespace LM
