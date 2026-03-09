//types.hh
#pragma once

#include "../memory/memory.hh"
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
#include <iomanip>
#include <functional>

// Forward declarations for AST types
namespace LM {
namespace Frontend {
namespace AST {
    struct TypeAnnotation;
    struct FunctionTypeAnnotation;
    struct LambdaExpr;
    struct FrameDeclaration;
    struct TraitDeclaration;
    enum class VisibilityLevel;
}
}
}

using AST_TypeAnnotation = LM::Frontend::AST::TypeAnnotation;
using AST_FunctionTypeAnnotation = LM::Frontend::AST::FunctionTypeAnnotation;
using AST_LambdaExpr = LM::Frontend::AST::LambdaExpr;
using AST_FrameDeclaration = LM::Frontend::AST::FrameDeclaration;
using AST_TraitDeclaration = LM::Frontend::AST::TraitDeclaration;
using VisibilityLevel = LM::Frontend::AST::VisibilityLevel;

class TypeSystem
{
public:
    struct FrameInfo {
        std::string name;
        std::vector<std::pair<std::string, TypePtr>> fields;
        std::map<std::string, VisibilityLevel> fieldVisibilities;
        std::map<std::string, size_t> fieldOffsets;
        std::map<std::string, TypePtr> methodSignatures;
        std::map<std::string, size_t> methodIndices;
        std::vector<std::string> implements;
        bool hasInit = false;
        bool hasDeinit = false;
        size_t totalFieldSize = 0;
        std::shared_ptr<AST_FrameDeclaration> declaration;
    };

    struct TraitInfo {
        std::string name;
        std::vector<std::string> extends;
        std::map<std::string, TypePtr> methodSignatures;
        std::shared_ptr<AST_TraitDeclaration> declaration;
    };

private:
    std::map<std::string, TypePtr> userDefinedTypes;
    std::map<std::string, TypePtr> typeAliases;
    std::map<std::string, TypePtr> errorTypes;

    // Canonicalization cache for structural types
    std::map<std::string, TypePtr> typeCache;

    // Contextual scoping (stack of maps)
    std::vector<std::map<std::string, TypePtr>> scopeStack;
    
    // Persistent registries for cross-pass identity
    std::map<std::string, FrameInfo> frameRegistry;
    std::map<std::string, TraitInfo> traitRegistry;

    bool canConvert(TypePtr from, TypePtr to)
    {
        if (!from || !to) return false;
        if (from == to || to->tag == TypeTag::Any)
            return true;

        // Handle boolean type conversions
        if (from->tag == TypeTag::Bool && to->tag == TypeTag::Bool) {
            return true;
        }
        
        // Handle frame type conversions
        if (from->tag == TypeTag::Frame && to->tag == TypeTag::Frame) {
            auto fromFrameType = std::get_if<FrameType>(&from->extra);
            auto toFrameType = std::get_if<FrameType>(&to->extra);
            if (fromFrameType && toFrameType) {
                return fromFrameType->name == toFrameType->name;
            }
            return false;
        }

        // Numeric type conversions
        bool fromIsInt = (from->tag >= TypeTag::Int && from->tag <= TypeTag::UInt128);
        bool toIsInt = (to->tag >= TypeTag::Int && to->tag <= TypeTag::UInt128);
        if (fromIsInt && toIsInt) return true;
        
        bool fromIsFloat = (from->tag == TypeTag::Float32 || from->tag == TypeTag::Float64);
        bool toIsFloat = (to->tag == TypeTag::Float32 || to->tag == TypeTag::Float64);
        if (fromIsFloat && toIsFloat) return true;
        if (fromIsInt && toIsFloat) return true;

        // Error union type compatibility
        if (from->tag == TypeTag::ErrorUnion && to->tag == TypeTag::ErrorUnion) {
            auto fromErrorUnion = std::get<ErrorUnionType>(from->extra);
            auto toErrorUnion = std::get<ErrorUnionType>(to->extra);
            if (!canConvert(fromErrorUnion.successType, toErrorUnion.successType)) return false;
            if (toErrorUnion.isGenericError) return true;
            if (fromErrorUnion.isGenericError) return toErrorUnion.isGenericError;
            return true;
        }
        
        if (to->tag == TypeTag::ErrorUnion) {
            auto toErrorUnion = std::get<ErrorUnionType>(to->extra);
            return canConvert(from, toErrorUnion.successType);
        }

        // Union type compatibility
        if (to->tag == TypeTag::Union) {
            auto unionTypes = std::get<UnionType>(to->extra).types;
            return std::any_of(unionTypes.begin(), unionTypes.end(),
                               [&](TypePtr type) { return canConvert(from, type); });
        }

        return false;
    }

public:
    // --- Type Constants ---
    const TypePtr NIL_TYPE = std::make_shared<Type>(TypeTag::Nil);
    const TypePtr BOOL_TYPE = std::make_shared<Type>(TypeTag::Bool);
    const TypePtr INT64_TYPE = std::make_shared<Type>(TypeTag::Int64);
    const TypePtr INT_TYPE = INT64_TYPE;
    const TypePtr INT8_TYPE = std::make_shared<Type>(TypeTag::Int8);
    const TypePtr INT16_TYPE = std::make_shared<Type>(TypeTag::Int16);
    const TypePtr INT32_TYPE = std::make_shared<Type>(TypeTag::Int32);
    const TypePtr INT128_TYPE = std::make_shared<Type>(TypeTag::Int128);
    const TypePtr UINT64_TYPE = std::make_shared<Type>(TypeTag::UInt64);
    const TypePtr UINT_TYPE = UINT64_TYPE;
    const TypePtr UINT8_TYPE = std::make_shared<Type>(TypeTag::UInt8);
    const TypePtr UINT16_TYPE = std::make_shared<Type>(TypeTag::UInt16);
    const TypePtr UINT32_TYPE = std::make_shared<Type>(TypeTag::UInt32);
    const TypePtr UINT128_TYPE = std::make_shared<Type>(TypeTag::UInt128);
    const TypePtr FLOAT64_TYPE = std::make_shared<Type>(TypeTag::Float64);
    const TypePtr FLOAT32_TYPE = std::make_shared<Type>(TypeTag::Float32);
    const TypePtr STRING_TYPE = std::make_shared<Type>(TypeTag::String);
    const TypePtr ANY_TYPE = std::make_shared<Type>(TypeTag::Any);
    const TypePtr LIST_TYPE = std::make_shared<Type>(TypeTag::List);
    const TypePtr DICT_TYPE = std::make_shared<Type>(TypeTag::Dict);
    const TypePtr TUPLE_TYPE = std::make_shared<Type>(TypeTag::Tuple);
    const TypePtr ENUM_TYPE = std::make_shared<Type>(TypeTag::Enum);
    const TypePtr SUM_TYPE = std::make_shared<Type>(TypeTag::Sum);
    const TypePtr FUNCTION_TYPE = std::make_shared<Type>(TypeTag::Function);
    const TypePtr CLOSURE_TYPE = std::make_shared<Type>(TypeTag::Closure);
    const TypePtr OBJECT_TYPE = std::make_shared<Type>(TypeTag::Object);
    const TypePtr MODULE_TYPE = std::make_shared<Type>(TypeTag::Module);
    const TypePtr CHANNEL_TYPE = std::make_shared<Type>(TypeTag::Channel);
    const TypePtr ERROR_UNION_TYPE = std::make_shared<Type>(TypeTag::ErrorUnion);

    TypeSystem() {
        // Initialize with global scope
        scopeStack.push_back({});
        registerBuiltinErrors();
    }

    // --- Scoping Methods ---
    void pushScope() { scopeStack.push_back({}); }
    void popScope() { if (scopeStack.size() > 1) scopeStack.pop_back(); }

    void registerType(const std::string& name, TypePtr type) {
        scopeStack.back()[name] = type;
    }

    TypePtr getType(const std::string& name) {
        // 1. Check contextual scopes (inner to outer)
        for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) return found->second;
        }

        // 2. Check built-in types
        if (name == "int" || name == "i64") return INT64_TYPE;
        if (name == "uint" || name == "u64") return UINT64_TYPE;
        if (name == "i8") return INT8_TYPE;
        if (name == "u8") return UINT8_TYPE;
        if (name == "i16") return INT16_TYPE;
        if (name == "u16") return UINT16_TYPE;
        if (name == "i32") return INT32_TYPE;
        if (name == "u32") return UINT32_TYPE;
        if (name == "i128") return INT128_TYPE;
        if (name == "u128") return UINT128_TYPE;
        if (name == "float" || name == "f64") return FLOAT64_TYPE;
        if (name == "f32") return FLOAT32_TYPE;
        if (name == "bool") return BOOL_TYPE;
        if (name == "string" || name == "str") return STRING_TYPE;
        if (name == "any") return ANY_TYPE;
        if (name == "void" || name == "nil") return NIL_TYPE;
        if (name == "channel") return CHANNEL_TYPE;
        if (name == "list") return LIST_TYPE;
        if (name == "dict") return DICT_TYPE;
        if (name == "tuple") return TUPLE_TYPE;
        if (name == "enum") return ENUM_TYPE;
        if (name == "sum") return SUM_TYPE;
        if (name == "closure") return CLOSURE_TYPE;
        if (name == "function") return FUNCTION_TYPE;
        if (name == "object") return OBJECT_TYPE;
        if (name == "module") return MODULE_TYPE;

        // 3. Check persistent registries
        if (frameRegistry.count(name)) return createFrameType(name);
        if (traitRegistry.count(name)) {
            return getCanonicalType("trait:" + name, [&]() {
                return std::make_shared<Type>(TypeTag::Trait);
            });
        }

        // 4. Check type aliases
        if (typeAliases.count(name)) return typeAliases[name];

        // 5. Check user defined types
        if (userDefinedTypes.count(name)) return userDefinedTypes[name];

        return nullptr;
    }

    void addUserDefinedType(const std::string& name, TypePtr type) {
        userDefinedTypes[name] = type;
    }

    void registerTypeAlias(const std::string& name, TypePtr type) {
        typeAliases[name] = type;
    }

    TypePtr getTypeAlias(const std::string& name) {
        if (typeAliases.count(name)) return typeAliases[name];
        return nullptr;
    }

    // --- Persistence Methods ---
    void registerFrame(const std::string& name, const FrameInfo& info) {
        frameRegistry[name] = info;
    }

    FrameInfo* getFrameInfo(const std::string& name) {
        if (frameRegistry.count(name)) return &frameRegistry[name];
        return nullptr;
    }

    void registerTrait(const std::string& name, const TraitInfo& info) {
        traitRegistry[name] = info;
    }

    TraitInfo* getTraitInfo(const std::string& name) {
        if (traitRegistry.count(name)) return &traitRegistry[name];
        return nullptr;
    }

    // --- Canonicalization ---
    TypePtr getCanonicalType(const std::string& key, std::function<TypePtr()> creator) {
        if (typeCache.count(key)) return typeCache[key];
        TypePtr newType = creator();
        typeCache[key] = newType;
        return newType;
    }

    // --- Type Creators ---
    TypePtr createFrameType(const std::string& name) {
        return getCanonicalType("frame:" + name, [&]() {
            FrameType ft; ft.name = name;
            return std::make_shared<Type>(TypeTag::Frame, ft);
        });
    }

    TypePtr createFallibleType(TypePtr successType) {
        if (!successType) return nullptr;
        return getCanonicalType("fallible:" + successType->toString(), [&]() {
            ErrorUnionType eut; eut.successType = successType; eut.isGenericError = true;
            return std::make_shared<Type>(TypeTag::ErrorUnion, eut);
        });
    }

    bool isFallibleType(TypePtr type) {
        return type && type->tag == TypeTag::ErrorUnion;
    }

    TypePtr getFallibleSuccessType(TypePtr fallibleType) {
        if (!isFallibleType(fallibleType)) return nullptr;
        const auto* eut = std::get_if<ErrorUnionType>(&fallibleType->extra);
        return eut ? eut->successType : nullptr;
    }

    TypePtr createTypedListType(TypePtr elementType) {
        return getCanonicalType("list:" + (elementType ? elementType->toString() : "any"), [&]() {
            ListType lt; lt.elementType = elementType ? elementType : ANY_TYPE;
            return std::make_shared<Type>(TypeTag::List, lt);
        });
    }

    TypePtr createTypedDictType(TypePtr keyType, TypePtr valueType) {
        return getCanonicalType("dict:" + (keyType ? keyType->toString() : "any") + ":" + (valueType ? valueType->toString() : "any"), [&]() {
            DictType dt; dt.keyType = keyType ? keyType : ANY_TYPE; dt.valueType = valueType ? valueType : ANY_TYPE;
            return std::make_shared<Type>(TypeTag::Dict, dt);
        });
    }

    TypePtr createFunctionType(const std::vector<TypePtr>& paramTypes, TypePtr returnType) {
        std::string key = "func:";
        for (const auto& t : paramTypes) key += (t ? t->toString() : "any") + ",";
        key += "->" + (returnType ? returnType->toString() : "void");
        return getCanonicalType(key, [&]() {
            FunctionType ft; ft.paramTypes = paramTypes; ft.returnType = returnType ? returnType : NIL_TYPE;
            return std::make_shared<Type>(TypeTag::Function, ft);
        });
    }

    TypePtr createTupleType(const std::vector<TypePtr>& elementTypes) {
        std::string key = "tuple:";
        for (const auto& t : elementTypes) key += (t ? t->toString() : "any") + ",";
        return getCanonicalType(key, [&]() {
            TupleType tt; tt.elementTypes = elementTypes;
            return std::make_shared<Type>(TypeTag::Tuple, tt);
        });
    }

    bool isOptionType(TypePtr type) {
        if (!type || type->tag != TypeTag::Union) return false;
        const auto* ut = std::get_if<UnionType>(&type->extra);
        if (!ut || ut->types.size() != 2) return false;
        bool hasNil = false, hasNonNil = false;
        for (const auto& t : ut->types) {
            if (t->tag == TypeTag::Nil) hasNil = true; else hasNonNil = true;
        }
        return hasNil && hasNonNil;
    }

    TypePtr getCommonType(TypePtr a, TypePtr b) {
        if (!a || !b) return nullptr;
        if (a->tag == TypeTag::Any) return b;
        if (b->tag == TypeTag::Any) return a;
        if (a->tag == TypeTag::Nil) return b;
        if (b->tag == TypeTag::Nil) return a;
        if (canConvert(a, b)) return b;
        if (canConvert(b, a)) return a;
        return ANY_TYPE;
    }

    // --- Error Handling ---
    void registerBuiltinErrors() {
        errorTypes["DefaultError"] = std::make_shared<Type>(TypeTag::UserDefined);
    }

    ValuePtr createValue(TypePtr type) {
        ValuePtr val = std::make_shared<Value>();
        val->type = type;
        if (type->tag == TypeTag::Bool) val->data = "false";
        else if (type->tag >= TypeTag::Int && type->tag <= TypeTag::Float64) val->data = "0";
        else val->data = "";
        return val;
    }

    bool isCompatible(TypePtr src, TypePtr dst) { return canConvert(src, dst); }

    TypePtr createUnionType(const std::vector<TypePtr>& types) {
        std::string key = "union:";
        for (const auto& t : types) key += (t ? t->toString() : "any") + "|";
        return getCanonicalType(key, [&]() {
            UnionType ut; ut.types = types;
            return std::make_shared<Type>(TypeTag::Union, ut);
        });
    }
};
