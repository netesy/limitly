//types.hh
#pragma once

#include "memory.hh"
#include "value.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include <cmath>

// Forward declarations for AST types
namespace AST {
    struct TypeAnnotation;
    struct FunctionTypeAnnotation;
    struct LambdaExpr;
}

// Pre-declare Type for mutual recursion with type structures
struct NewType;
using TypePtr = std::shared_ptr<NewType>;

// New Harmonized Type Structures
struct PrimitiveType { std::string name; };
struct ListType { TypePtr elementType; };
struct DictType { TypePtr keyType; TypePtr valueType; };
struct TupleType { std::vector<TypePtr> elementTypes; };
struct FunctionType {
    std::vector<TypePtr> paramTypes;
    TypePtr returnType;
    std::vector<std::string> paramNames;
};
struct UnionType { std::vector<TypePtr> types; };
struct ErrorUnionType {
    TypePtr successType;
    std::vector<std::string> errorTypes;
    bool isGenericError;
};
struct UserDefinedType { std::string name; };
struct ModuleType { std::string name; };
struct AnyType {};
struct NilType {};

struct NewType {
    using TypeVariant = std::variant<
        PrimitiveType, ListType, DictType, TupleType, FunctionType,
        UnionType, ErrorUnionType, UserDefinedType, ModuleType, AnyType, NilType
    >;
    TypeVariant data;
    NewType(TypeVariant data) : data(std::move(data)) {}

    std::string toString() const {
        return std::visit([](const auto& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, PrimitiveType>) return arg.name;
            if constexpr (std::is_same_v<T, ListType>) return "[" + arg.elementType->toString() + "]";
            if constexpr (std::is_same_v<T, DictType>) return "{" + arg.keyType->toString() + ": " + arg.valueType->toString() + "}";
            // ... other types ...
            return "unknown";
        }, data);
    }
};

// Existing TypeTag enum - kept for backward compatibility
enum class TypeTag {
    Nil, Bool, Int, Int8, Int16, Int32, Int64, UInt, UInt8, UInt16, UInt32, UInt64,
    Float32, Float64, String, List, Dict, Enum, Function, Any, Sum, Union,
    UserDefined, Tuple, Range, Class, Object, Module, ErrorUnion, Channel, Closure
};

// Existing Type struct - kept for backward compatibility
struct Type {
    TypeTag tag;
    std::variant<std::monostate, ListType, DictType, TupleType, FunctionType, UnionType, ErrorUnionType, UserDefinedType> extra;
    size_t activeUnionVariant = 0;

    Type(TypeTag t) : tag(t) {}
    Type(TypeTag t, auto e) : tag(t), extra(e) {}

    std::string toString() const {
        // ... implementation ...
        return "old_type";
    }
};


class TypeSystem
{
private:
    std::map<std::string, TypePtr> userDefinedTypes;
    std::map<std::string, TypePtr> typeAliases;
    std::map<std::string, TypePtr> errorTypes;
    MemoryManager<> &memoryManager;
    MemoryManager<>::Region &region;

    bool hasCircularDependency(const std::string& aliasName, TypePtr type, 
                              std::set<std::string> visited = {});
    
    bool checkTypeForCircularReferences(TypePtr type, std::set<std::string>& visited);

    bool canConvert(TypePtr from, TypePtr to);
    TypePtr getWiderType(TypePtr a, TypePtr b);

public:
    bool isNumericType(TypeTag tag);

private:
    bool isListType(TypePtr type) const;
    bool isDictType(TypePtr type) const;
    bool isSafeNumericConversion(TypeTag from, TypeTag to);
    ValuePtr stringToNumber(const std::string &str, TypePtr targetType);
    ValuePtr numberToString(const ValuePtr &value);

public:
    TypeSystem(MemoryManager<> &memManager, MemoryManager<>::Region &reg);

    const TypePtr NIL_TYPE = std::make_shared<NewType>(NilType{});
    const TypePtr BOOL_TYPE = std::make_shared<NewType>(PrimitiveType{"bool"});
    const TypePtr INT_TYPE = std::make_shared<NewType>(PrimitiveType{"int"});
    const TypePtr INT64_TYPE = std::make_shared<NewType>(PrimitiveType{"int64"});
    const TypePtr UINT64_TYPE = std::make_shared<NewType>(PrimitiveType{"uint64"});
    const TypePtr FLOAT64_TYPE = std::make_shared<NewType>(PrimitiveType{"float64"});
    const TypePtr STRING_TYPE = std::make_shared<NewType>(PrimitiveType{"string"});
    const TypePtr ANY_TYPE = std::make_shared<NewType>(AnyType{});
    // ... other new types ...

    TypePtr getType(const std::string& name);

    ValuePtr createValue(TypePtr type);

    bool isCompatible(TypePtr source, TypePtr target);

    TypePtr getCommonType(TypePtr a, TypePtr b);

    void addUserDefinedType(const std::string &name, TypePtr type);
    TypePtr getUserDefinedType(const std::string &name);
    void registerTypeAlias(const std::string &alias, TypePtr type);
    TypePtr resolveTypeAlias(const std::string &alias);

    // ... other methods ...
};