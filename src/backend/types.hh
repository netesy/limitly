// src/backend/types.hh
#pragma once

#include "value.hh"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>

namespace LM {

// Forward declarations for AST types
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

namespace Backend {

// Use aliases for AST types
using AST_TypeAnnotation = LM::Frontend::AST::TypeAnnotation;
using AST_FunctionTypeAnnotation = LM::Frontend::AST::FunctionTypeAnnotation;
using AST_LambdaExpr = LM::Frontend::AST::LambdaExpr;
using AST_FrameDeclaration = LM::Frontend::AST::FrameDeclaration;
using AST_TraitDeclaration = LM::Frontend::AST::TraitDeclaration;
using VisibilityLevel = LM::Frontend::AST::VisibilityLevel;

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

class TypeSystem {
private:
    std::map<std::string, TypePtr> userDefinedTypes;
    std::map<std::string, TypePtr> typeAliases;
    std::map<std::string, TypePtr> errorTypes;

    // Canonicalization cache for structural types
    std::map<std::string, TypePtr> typeCache;

    // Contextual scoping (stack of maps)
    std::vector<std::map<std::string, TypePtr>> scopeStack;
    
public:
    // Persistent registries for cross-pass identity
    std::map<std::string, FrameInfo> frameRegistry;
    std::map<std::string, TraitInfo> traitRegistry;

    TypeSystem() {
        // Initialize with global scope
        scopeStack.push_back({});
        registerBuiltinErrors();
    }

    // Basic Types
    const TypePtr NIL_TYPE = std::make_shared<Type>(TypeTag::Nil);
    const TypePtr BOOL_TYPE = std::make_shared<Type>(TypeTag::Bool);
    const TypePtr INT_TYPE = std::make_shared<Type>(TypeTag::Int);
    const TypePtr INT8_TYPE = std::make_shared<Type>(TypeTag::Int8);
    const TypePtr INT16_TYPE = std::make_shared<Type>(TypeTag::Int16);
    const TypePtr INT32_TYPE = std::make_shared<Type>(TypeTag::Int32);
    const TypePtr INT64_TYPE = std::make_shared<Type>(TypeTag::Int64);
    const TypePtr INT128_TYPE = std::make_shared<Type>(TypeTag::Int128);
    const TypePtr UINT_TYPE = std::make_shared<Type>(TypeTag::UInt);
    const TypePtr UINT8_TYPE = std::make_shared<Type>(TypeTag::UInt8);
    const TypePtr UINT16_TYPE = std::make_shared<Type>(TypeTag::UInt16);
    const TypePtr UINT32_TYPE = std::make_shared<Type>(TypeTag::UInt32);
    const TypePtr UINT64_TYPE = std::make_shared<Type>(TypeTag::UInt64);
    const TypePtr UINT128_TYPE = std::make_shared<Type>(TypeTag::UInt128);
    const TypePtr FLOAT32_TYPE = std::make_shared<Type>(TypeTag::Float32);
    const TypePtr FLOAT64_TYPE = std::make_shared<Type>(TypeTag::Float64);
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

    // Built-in Error Constants
    const std::string DIVISION_BY_ZERO_ERROR_STR = "DivisionByZeroError";
    const std::string INDEX_OUT_OF_BOUNDS_ERROR_STR = "IndexOutOfBoundsError";
    const std::string KEY_NOT_FOUND_ERROR_STR = "KeyNotFoundError";
    const std::string TYPE_MISMATCH_ERROR_STR = "TypeMismatchError";
    const std::string NULL_POINTER_ERROR_STR = "NullPointerError";

    // --- Scoping Methods ---
    void pushScope() { scopeStack.push_back({}); }
    void popScope() { if (scopeStack.size() > 1) scopeStack.pop_back(); }
    void enterScope() { pushScope(); }
    void exitScope() { popScope(); }

    void registerType(const std::string& name, TypePtr type) {
        scopeStack.back()[name] = type;
    }

    bool declare(const std::string& name, TypePtr type) {
        if (scopeStack.back().count(name)) return false;
        scopeStack.back()[name] = type;
        return true;
    }

    TypePtr lookup(const std::string& name) {
        for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) return found->second;
        }
        return nullptr;
    }

    // --- Persistence Methods ---
    void registerFrame(const std::string& name, const FrameInfo& info) {
        frameRegistry[name] = info;
    }

    FrameInfo* getFrameInfo(const std::string& name) {
        auto it = frameRegistry.find(name);
        if (it != frameRegistry.end()) return &it->second;
        return nullptr;
    }

    void registerTrait(const std::string& name, const TraitInfo& info) {
        traitRegistry[name] = info;
    }

    TraitInfo* getTraitInfo(const std::string& name) {
        auto it = traitRegistry.find(name);
        if (it != traitRegistry.end()) return &it->second;
        return nullptr;
    }

    // --- Canonicalization ---
    TypePtr getCanonicalType(const std::string& key, std::function<TypePtr()> creator) {
        if (typeCache.count(key)) return typeCache[key];
        TypePtr newType = creator();
        typeCache[key] = newType;
        return newType;
    }

    TypePtr getType(const std::string& name) {
        TypePtr t = lookup(name);
        if (t) return t;

        // Built-ins
        if (name == "bigint" || name == "int" || name == "i64" || name == "u64" || 
            name == "i32" || name == "u32" || name == "i16" || name == "u16" ||
            name == "i8" || name == "u8" || name == "i128" || name == "u128" ||
            name == "uint" || name == "f32" || name == "f64" || name == "float") {
            if (name == "i8") return INT8_TYPE;
            if (name == "u8") return UINT8_TYPE;
            if (name == "i16") return INT16_TYPE;
            if (name == "u16") return UINT16_TYPE;
            if (name == "i32") return INT32_TYPE;
            if (name == "u32") return UINT32_TYPE;
            if (name == "i64" || name == "int") return INT64_TYPE;
            if (name == "u64" || name == "uint") return UINT64_TYPE;
            if (name == "i128" || name == "bigint") return INT128_TYPE;
            if (name == "u128") return UINT128_TYPE;
            if (name == "f32" || name == "float") return FLOAT32_TYPE;
            if (name == "f64") return FLOAT64_TYPE;
            return INT64_TYPE;
        }
        if (name == "string") return STRING_TYPE;
        if (name == "str") return STRING_TYPE;
        if (name == "bool") return BOOL_TYPE;
        if (name == "list") return LIST_TYPE;
        if (name == "dict") return DICT_TYPE;
        if (name == "tuple") return TUPLE_TYPE;
        if (name == "enum") return ENUM_TYPE;
        if (name == "sum") return SUM_TYPE;
        if (name == "closure") return CLOSURE_TYPE;
        if (name == "function") return FUNCTION_TYPE;
        if (name == "object") return OBJECT_TYPE;
        if (name == "module") return MODULE_TYPE;
        if (name == "nil" || name == "void") return NIL_TYPE;
        
        // Frames/Traits from registries
        if (frameRegistry.count(name)) return createFrameType(name);
        if (traitRegistry.count(name)) return createTraitType(name);

        // Check type aliases
        TypePtr aliasType = resolveTypeAlias(name);
        if (aliasType) return aliasType;
        
        return nullptr;
    }

    // Compatibility
    bool isCompatible(TypePtr source, TypePtr target) {
        if (!source || !target) return false;
        if (source == target || target->tag == TypeTag::Any) return true;

        if (source->tag == target->tag) {
            switch (source->tag) {
                case TypeTag::Nil:
                case TypeTag::Bool:
                case TypeTag::Int:
                case TypeTag::Int8:
                case TypeTag::Int16:
                case TypeTag::Int32:
                case TypeTag::Int64:
                case TypeTag::Int128:
                case TypeTag::UInt:
                case TypeTag::UInt8:
                case TypeTag::UInt16:
                case TypeTag::UInt32:
                case TypeTag::UInt64:
                case TypeTag::UInt128:
                case TypeTag::Float32:
                case TypeTag::Float64:
                case TypeTag::String:
                case TypeTag::Channel:
                case TypeTag::Function:
                    return true;
                default: break;
            }
        }

        // Basic numeric promotion
        bool sourceIsInt = (source->tag >= TypeTag::Int && source->tag <= TypeTag::UInt128);
        bool targetIsInt = (target->tag >= TypeTag::Int && target->tag <= TypeTag::UInt128);
        if (sourceIsInt && targetIsInt) return true;

        bool targetIsFloat = (target->tag == TypeTag::Float32 || target->tag == TypeTag::Float64);
        if (sourceIsInt && targetIsFloat) return true;

        // Fallible type compatibility
        if (source->tag == TypeTag::ErrorUnion && target->tag == TypeTag::ErrorUnion) {
            auto sEut = std::get_if<ErrorUnionType>(&source->extra);
            auto tEut = std::get_if<ErrorUnionType>(&target->extra);
            if (sEut && tEut) {
                if (!isCompatible(sEut->successType, tEut->successType)) return false;
                if (tEut->isGenericError) return true;
                for (const auto& err : sEut->errorTypes) {
                    if (std::find(tEut->errorTypes.begin(), tEut->errorTypes.end(), err) == tEut->errorTypes.end()) return false;
                }
                return true;
            }
        }

        // Frame compatibility
        if (source->tag == TypeTag::Frame && target->tag == TypeTag::Frame) {
            auto sft = std::get_if<FrameType>(&source->extra);
            auto tft = std::get_if<FrameType>(&target->extra);
            if (sft && tft) return sft->name == tft->name;
        }

        return false;
    }

    TypePtr getCommonType(TypePtr a, TypePtr b) {
        if (!a || !b) return nullptr;
        if (isCompatible(a, b)) return b;
        if (isCompatible(b, a)) return a;
        return ANY_TYPE;
    }

    // Type Factories
    TypePtr createListType(TypePtr elementType) {
        return std::make_shared<Type>(TypeTag::List, ListType{elementType});
    }

    TypePtr createDictType(TypePtr keyType, TypePtr valueType) {
        return std::make_shared<Type>(TypeTag::Dict, DictType{keyType, valueType});
    }

    TypePtr createTupleType(const std::vector<TypePtr>& elementTypes) {
        return std::make_shared<Type>(TypeTag::Tuple, TupleType{elementTypes});
    }

    TypePtr createFunctionType(const std::vector<TypePtr>& params, TypePtr ret) {
        return std::make_shared<Type>(TypeTag::Function, FunctionType{params, ret});
    }

    TypePtr createFrameType(const std::string& name) {
        return std::make_shared<Type>(TypeTag::Frame, FrameType{name});
    }

    TypePtr createTraitType(const std::string& name) {
        return std::make_shared<Type>(TypeTag::Trait, TraitType{name});
    }

    TypePtr createErrorUnionType(TypePtr success, const std::vector<std::string>& errors, bool isGeneric = true) {
        ErrorUnionType eut;
        eut.successType = success;
        eut.errorTypes = errors;
        eut.isGenericError = isGeneric;
        return std::make_shared<Type>(TypeTag::ErrorUnion, eut);
    }

    TypePtr createFallibleType(TypePtr successType) {
        return createErrorUnionType(successType, {}, true);
    }

    TypePtr createOptionType(TypePtr valueType) {
        if (!valueType) valueType = ANY_TYPE;
        return createUnionType({valueType, NIL_TYPE});
    }

    TypePtr createUnionType(const std::vector<TypePtr>& types) {
        if (types.empty()) return NIL_TYPE;
        if (types.size() == 1) return types[0];
        return std::make_shared<Type>(TypeTag::Union, UnionType{types});
    }

    // Value Creation
    ValuePtr createValue(TypePtr type) {
        ValuePtr value = std::make_shared<Value>();
        value->type = type;
        switch (type->tag) {
            case TypeTag::Nil: value->data = ""; break;
            case TypeTag::Bool: value->data = "false"; break;
            case TypeTag::Int:
            case TypeTag::Int64: value->data = "0"; break;
            case TypeTag::Float64: value->data = "0.0"; break;
            case TypeTag::String: value->data = ""; break;
            case TypeTag::List: value->complexData = ListValue{}; break;
            case TypeTag::Dict: value->complexData = DictValue{}; break;
            case TypeTag::Tuple: {
                if (auto* tt = std::get_if<TupleType>(&type->extra)) {
                    TupleValue tv;
                    for (const auto& et : tt->elementTypes) tv.elements.push_back(createValue(et));
                    value->complexData = tv;
                }
                break;
            }
            default: break;
        }
        return value;
    }

    // Type Aliases
    void registerTypeAlias(const std::string& alias, TypePtr type) {
        typeAliases[alias] = type;
    }

    TypePtr resolveTypeAlias(const std::string& alias) {
        auto it = typeAliases.find(alias);
        if (it != typeAliases.end()) return it->second;
        return nullptr;
    }

    TypePtr getTypeAlias(const std::string& alias) {
        return resolveTypeAlias(alias);
    }

    void addUserDefinedType(const std::string& name, TypePtr type) {
        userDefinedTypes[name] = type;
    }

    // Fallible/Option Helpers
    bool isFallibleType(TypePtr type) {
        return type && type->tag == TypeTag::ErrorUnion;
    }

    TypePtr getFallibleSuccessType(TypePtr fallibleType) {
        if (!isFallibleType(fallibleType)) return nullptr;
        auto eut = std::get_if<ErrorUnionType>(&fallibleType->extra);
        return eut ? eut->successType : nullptr;
    }

    bool isOptionType(TypePtr type) {
        if (!type || type->tag != TypeTag::Union) return false;
        auto ut = std::get_if<UnionType>(&type->extra);
        if (!ut || ut->types.size() != 2) return false;
        bool hasNil = false;
        for (const auto& t : ut->types) if (t->tag == TypeTag::Nil) hasNil = true;
        return hasNil;
    }

    TypePtr getOptionValueType(TypePtr optionType) {
        if (!isOptionType(optionType)) return nullptr;
        auto ut = std::get_if<UnionType>(&optionType->extra);
        for (const auto& t : ut->types) if (t->tag != TypeTag::Nil) return t;
        return nullptr;
    }

    // Compatibility Helpers
    TypePtr createTypedListType(TypePtr elem) { return createListType(elem); }
    TypePtr createTypedDictType(TypePtr key, TypePtr val) { return createDictType(key, val); }

    void registerBuiltinErrors() {
        registerType(DIVISION_BY_ZERO_ERROR_STR, std::make_shared<Type>(TypeTag::ErrorUnion));
        registerType(INDEX_OUT_OF_BOUNDS_ERROR_STR, std::make_shared<Type>(TypeTag::ErrorUnion));
    }

private:
    // Circular dependency detection for type aliases
    bool hasCircularDependency(const std::string& aliasName, TypePtr type,
                              std::set<std::string> visited = {}) {
        if (visited.find(aliasName) != visited.end()) return true;
        visited.insert(aliasName);
        return false; // Simplified
    }

    bool canConvert(TypePtr from, TypePtr to) { return isCompatible(from, to); }
};

} // namespace Backend
} // namespace LM
