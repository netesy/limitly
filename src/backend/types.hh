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

// Forward declarations for AST types
namespace AST {
    struct TypeAnnotation;
    struct FunctionTypeAnnotation;
    struct LambdaExpr;
}

class TypeSystem
{
private:
    std::map<std::string, TypePtr> userDefinedTypes;
    std::map<std::string, TypePtr> typeAliases;
    std::map<std::string, TypePtr> errorTypes;
    MemoryManager<> &memoryManager;
    MemoryManager<>::Region &region;

    // Circular dependency detection for type aliases
    bool hasCircularDependency(const std::string& aliasName, TypePtr type, 
                              std::set<std::string> visited = {}) {
        // If we've already visited this alias, we have a cycle
        if (visited.find(aliasName) != visited.end()) {
            return true;
        }
        
        // Add current alias to visited set
        visited.insert(aliasName);
        
        // Check if the type references any type aliases that could create cycles
        return checkTypeForCircularReferences(type, visited);
    }
    
    bool checkTypeForCircularReferences(TypePtr type, std::set<std::string>& visited) {
        if (!type) return false;
        
        // For now, we'll implement basic checking for direct type alias references
        // This can be extended later for more complex type structures
        
        // Check if this type is a user-defined type that might be an alias
        // For the current implementation, we'll focus on preventing direct circular references
        // More sophisticated checking can be added when we implement complex type structures
        
        return false; // No circular dependency detected for basic types
    }

    bool canConvert(TypePtr from, TypePtr to)
    {
        if (from == to || to->tag == TypeTag::Any)
            return true;

    // Handle boolean type conversions
    if (from->tag == TypeTag::Bool && to->tag == TypeTag::Bool) {
        return true;
    }   

        // Numeric type conversions with range checks
        if (isNumericType(from->tag) && isNumericType(to->tag)) {
            // Check if conversion is safe (no overflow/precision loss)
            return isSafeNumericConversion(from->tag, to->tag);
        }

        // Handle list and dict type compatibility
        if (from->tag == TypeTag::List && to->tag == TypeTag::List) {
            auto fromListType = std::get<ListType>(from->extra);
            auto toListType = std::get<ListType>(to->extra);
            return canConvert(fromListType.elementType, toListType.elementType);
        }

        if (from->tag == TypeTag::Dict && to->tag == TypeTag::Dict) {
            auto fromDictType = std::get<DictType>(from->extra);
            auto toDictType = std::get<DictType>(to->extra);
            return canConvert(fromDictType.keyType, toDictType.keyType) &&
                   canConvert(fromDictType.valueType, toDictType.valueType);
        }

        // Handle tuple type compatibility
        if (from->tag == TypeTag::Tuple && to->tag == TypeTag::Tuple) {
            auto fromTupleType = std::get<TupleType>(from->extra);
            auto toTupleType = std::get<TupleType>(to->extra);
            
            // Tuples must have same number of elements
            if (fromTupleType.elementTypes.size() != toTupleType.elementTypes.size()) {
                return false;
            }
            
            // All corresponding element types must be compatible
            for (size_t i = 0; i < fromTupleType.elementTypes.size(); ++i) {
                if (!canConvert(fromTupleType.elementTypes[i], toTupleType.elementTypes[i])) {
                    return false;
                }
            }
            return true;
        }

        // Union and sum type compatibility
        if (from->tag == TypeTag::Union) {
            auto unionTypes = std::get<UnionType>(from->extra).types;
            return std::any_of(unionTypes.begin(), unionTypes.end(),
                               [&](TypePtr type) { return canConvert(type, to); });
        }

        // Error union type compatibility
        if (from->tag == TypeTag::ErrorUnion && to->tag == TypeTag::ErrorUnion) {
            auto fromErrorUnion = std::get<ErrorUnionType>(from->extra);
            auto toErrorUnion = std::get<ErrorUnionType>(to->extra);
            
            // Success types must be compatible
            if (!canConvert(fromErrorUnion.successType, toErrorUnion.successType)) {
                return false;
            }
            
            // If target is generic error (Type?), any error union is compatible
            if (toErrorUnion.isGenericError) {
                return true;
            }
            
            // If source is generic error, it's only compatible with generic target
            if (fromErrorUnion.isGenericError) {
                return toErrorUnion.isGenericError;
            }
            
            // Check that all source error types are in target error types
            for (const auto& sourceError : fromErrorUnion.errorTypes) {
                bool found = std::find(toErrorUnion.errorTypes.begin(), 
                                     toErrorUnion.errorTypes.end(), 
                                     sourceError) != toErrorUnion.errorTypes.end();
                if (!found) {
                    return false;
                }
            }
            
            return true;
        }
        
        // Success type can be converted to error union if success types are compatible
        if (to->tag == TypeTag::ErrorUnion) {
            auto toErrorUnion = std::get<ErrorUnionType>(to->extra);
            return canConvert(from, toErrorUnion.successType);
        }

        // Function type compatibility
        if (from->tag == TypeTag::Function && to->tag == TypeTag::Function) {
            auto fromFuncType = std::get<FunctionType>(from->extra);
            auto toFuncType = std::get<FunctionType>(to->extra);
            
            // Check parameter count
            if (fromFuncType.paramTypes.size() != toFuncType.paramTypes.size()) {
                return false;
            }
            
            // Check parameter types (contravariant)
            for (size_t i = 0; i < fromFuncType.paramTypes.size(); ++i) {
                if (!canConvert(toFuncType.paramTypes[i], fromFuncType.paramTypes[i])) {
                    return false;
                }
            }
            
            // Check return type (covariant)
            return canConvert(fromFuncType.returnType, toFuncType.returnType);
        }

        return false;
    }
    TypePtr getWiderType(TypePtr a, TypePtr b) {
        // Define type hierarchy (from narrowest to widest)
        static const std::unordered_map<TypeTag, int> typeRanks = {
            {TypeTag::Int8, 0},    {TypeTag::UInt8, 1},
            {TypeTag::Int16, 2},   {TypeTag::UInt16, 3},
            {TypeTag::Int32, 4},   {TypeTag::UInt32, 5},
            {TypeTag::Int64, 6},   {TypeTag::UInt64, 7},
            {TypeTag::Float32, 8}, {TypeTag::Float64, 9}
        };

        auto itA = typeRanks.find(a->tag);
        auto itB = typeRanks.find(b->tag);

        if (itA == typeRanks.end() || itB == typeRanks.end()) {
            throw std::runtime_error("Invalid numeric type in type promotion");
        }

        return (itA->second >= itB->second) ? a : b;
    }
public:
    bool isNumericType(TypeTag tag) {
        return tag == TypeTag::Int8 || tag == TypeTag::Int16 || tag == TypeTag::Int32 ||
        tag == TypeTag::Int64 || tag == TypeTag::UInt8 || tag == TypeTag::UInt16 ||
        tag == TypeTag::UInt32 || tag == TypeTag::UInt64 || tag == TypeTag::Float32 ||
        tag == TypeTag::Float64;
    }

private:
    bool isListType(TypePtr type) const { return type->tag == TypeTag::List; }
    bool isDictType(TypePtr type) const { return type->tag == TypeTag::Dict; }
    bool isSafeNumericConversion(TypeTag from, TypeTag to) {
        // Conversion matrix to determine safe numeric conversions
        switch (from) {
        case TypeTag::Int8:
            return to == TypeTag::Int8 ||
                   to == TypeTag::Int16 ||
                   to == TypeTag::Int ||
                   to == TypeTag::Int32 ||
                   to == TypeTag::Int64 ||
                   to == TypeTag::Float32 ||
                   to == TypeTag::Float64;

        case TypeTag::Int16:
            return to == TypeTag::Int16 ||
                   to == TypeTag::Int ||
                   to == TypeTag::Int32 ||
                   to == TypeTag::Int64 ||
                   to == TypeTag::Float32 ||
                   to == TypeTag::Float64;

        case TypeTag::Int32:
            return to == TypeTag::Int32 ||
            to == TypeTag::Int ||
                   to == TypeTag::Int64 ||
                   to == TypeTag::Float32 ||
                   to == TypeTag::Float64;

        case TypeTag::Int64:
            return to == TypeTag::Int64 ||
                   to == TypeTag::Float64;

        case TypeTag::UInt8:
            return to == TypeTag::UInt8 ||
                   to == TypeTag::UInt16 ||
                   to == TypeTag::UInt ||
                   to == TypeTag::UInt32 ||
                   to == TypeTag::UInt64 ||
                   to == TypeTag::Int16 ||
                   to == TypeTag::Int ||
                   to == TypeTag::Int32 ||
                   to == TypeTag::Int64 ||
                   to == TypeTag::Float32 ||
                   to == TypeTag::Float64;

        case TypeTag::UInt16:
            return to == TypeTag::UInt16 ||
                   to == TypeTag::UInt ||
                   to == TypeTag::UInt32 ||
                   to == TypeTag::UInt64 ||
                   to == TypeTag::Int32 ||
                   to == TypeTag::Int64 ||
                   to == TypeTag::Float32 ||
                   to == TypeTag::Float64;

        case TypeTag::UInt32:
            return to == TypeTag::UInt32 ||
                   to == TypeTag::UInt ||
                   to == TypeTag::UInt64 ||
                   to == TypeTag::Int64 ||
                   to == TypeTag::Float64;

        case TypeTag::UInt64:
            return to == TypeTag::UInt64 ||
                   to == TypeTag::Float64;

        case TypeTag::Float32:
            return to == TypeTag::Float32 ||
                   to == TypeTag::Float64;

        case TypeTag::Float64:
            return to == TypeTag::Float64;

        default:
            return false;
        }
    }
    ValuePtr stringToNumber(const std::string &str, TypePtr targetType)
    {
        ValuePtr result = memoryManager.makeRef<Value>(region);
        result->type = targetType;

        try {
            if (targetType->tag == TypeTag::Int) {
                result->data = std::stoll(str);
            } else if (targetType->tag == TypeTag::Float32) {
                result->data = std::stof(str);
            } else if (targetType->tag == TypeTag::Float64) {
                result->data = std::stod(str);
            }
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to convert string to number: " + std::string(e.what()));
        }

        return result;
    }
    ValuePtr numberToString(const ValuePtr &value)
    {
        ValuePtr result = memoryManager.makeRef<Value>(region);
        result->type = STRING_TYPE;

        std::visit(overloaded{[&](int64_t v) { result->data = std::to_string(v); },
                              [&](double v) { result->data = std::to_string(v); },
                              [&](auto) {
                                  throw std::runtime_error("Unexpected type in numberToString");
                              }},
                   value->data);

        return result;
    }

public:
    TypeSystem(MemoryManager<> &memManager, MemoryManager<>::Region &reg)
        : memoryManager(memManager), region(reg) {
        registerBuiltinErrors();
    }

    const TypePtr NIL_TYPE = std::make_shared<Type>(TypeTag::Nil);
    const TypePtr BOOL_TYPE = std::make_shared<Type>(TypeTag::Bool);
    const TypePtr INT_TYPE = std::make_shared<Type>(TypeTag::Int);
    const TypePtr INT8_TYPE = std::make_shared<Type>(TypeTag::Int8);
    const TypePtr INT16_TYPE = std::make_shared<Type>(TypeTag::Int16);
    const TypePtr INT32_TYPE = std::make_shared<Type>(TypeTag::Int32);
    const TypePtr INT64_TYPE = std::make_shared<Type>(TypeTag::Int64);
    const TypePtr UINT_TYPE = std::make_shared<Type>(TypeTag::UInt);
    const TypePtr UINT8_TYPE = std::make_shared<Type>(TypeTag::UInt8);
    const TypePtr UINT16_TYPE = std::make_shared<Type>(TypeTag::UInt16);
    const TypePtr UINT32_TYPE = std::make_shared<Type>(TypeTag::UInt32);
    const TypePtr UINT64_TYPE = std::make_shared<Type>(TypeTag::UInt64);
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
    const TypePtr ERROR_UNION_TYPE = std::make_shared<Type>(TypeTag::ErrorUnion);

    // Built-in error types
    const TypePtr DIVISION_BY_ZERO_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr INDEX_OUT_OF_BOUNDS_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr NULL_REFERENCE_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr TYPE_CONVERSION_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr IO_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr PARSE_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr NETWORK_ERROR = std::make_shared<Type>(TypeTag::UserDefined);

    TypePtr getType(const std::string& name) {
        // First check built-in types
        if (name == "int") return INT_TYPE;
        if (name == "i64") return INT64_TYPE;
        if (name == "u64") return UINT64_TYPE;
        if (name == "f64") return FLOAT64_TYPE;
        if (name == "float") return FLOAT64_TYPE;
        if (name == "string") return STRING_TYPE;
        if (name == "str") return STRING_TYPE;
        if (name == "bool") return BOOL_TYPE;
        if (name == "list") return LIST_TYPE;
        if (name == "dict") return DICT_TYPE;
        if (name == "tuple") return TUPLE_TYPE;
        if (name == "object") return OBJECT_TYPE;
        if (name == "module") return MODULE_TYPE;
        
        // Check type aliases
        TypePtr aliasType = resolveTypeAlias(name);
        if (aliasType) {
            return aliasType;
        }
        
        // Check user-defined types
        auto it = userDefinedTypes.find(name);
        if (it != userDefinedTypes.end()) {
            return it->second;
        }
        
        return NIL_TYPE;
    }

    ValuePtr createValue(TypePtr type)
    {
        ValuePtr value = memoryManager.makeRef<Value>(region);
        value->type = type;

        switch (type->tag) {
        case TypeTag::Nil:
            value->data = std::monostate{};
            break;
        case TypeTag::Bool:
            value->data = false;
            break;
        case TypeTag::Int64:
            value->data = int64_t(0);
            break;
        case TypeTag::Int8:
            value->data = int8_t(0);
            break;
        case TypeTag::Int16:
            value->data = int16_t(0);
            break;
        case TypeTag::Int:
        case TypeTag::Int32:
            value->data = int32_t(0);
            break;
        case TypeTag::UInt64:
            value->data = uint64_t(0);
            break;
        case TypeTag::UInt8:
            value->data = uint8_t(0);
            break;
        case TypeTag::UInt16:
            value->data = uint16_t(0);
            break;
        case TypeTag::UInt:
        case TypeTag::UInt32:
            value->data = uint32_t(0);
            break;
        case TypeTag::Float32:
            value->data = float(0.0);
            break;
        case TypeTag::Float64:
            value->data = double(0.0);
            break;
        case TypeTag::String:
            value->data = std::string("");
            break;
        case TypeTag::List:
            value->data = ListValue{};
            break;
        case TypeTag::Dict:
            value->data = DictValue{};
            break;
        case TypeTag::Tuple:
            // For tuple types, create tuple with default values for each element
            if (const auto *tupleType = std::get_if<TupleType>(&type->extra)) {
                TupleValue tupleValue;
                for (const auto& elementType : tupleType->elementTypes) {
                    tupleValue.elements.push_back(createValue(elementType));
                }
                value->data = tupleValue;
            } else {
                // Empty tuple
                value->data = TupleValue{};
            }
            break;
        case TypeTag::Enum:
            // For enums, we'll set it to the first value in the enum
            if (const auto *enumType = std::get_if<EnumType>(&type->extra)) {
                if (!enumType->values.empty()) {
                    value->data = enumType->values[0];
                } else {
                    value->data = std::string(""); // Empty enum, use empty string as default
                }
            } else {
                throw std::runtime_error("Invalid enum type");
            }
            break;
        case TypeTag::Sum:
            // For sum types, we'll set it to the first variant with a default value
            if (const auto *sumType = std::get_if<SumType>(&type->extra)) {
                if (!sumType->variants.empty()) {
                    value->data = SumValue{0, createValue(sumType->variants[0])};
                } else {
                    throw std::runtime_error("Empty sum type");
                }
            } else {
                throw std::runtime_error("Invalid sum type");
            }
            break;

        case TypeTag::Union:
            // For union types, we'll set it to the first type with a default value
            if (const auto *unionType = std::get_if<UnionType>(&type->extra)) {
                if (!unionType->types.empty()) {
                    value->data = createValue(unionType->types[0])->data;
                } else {
                    throw std::runtime_error("Empty union type");
                }
            } else {
                throw std::runtime_error("Invalid union type");
            }
            break;
        case TypeTag::ErrorUnion:
            // For error union types, create a success value by default
            if (const auto *errorUnionType = std::get_if<ErrorUnionType>(&type->extra)) {
                value->data = createValue(errorUnionType->successType)->data;
            } else {
                throw std::runtime_error("Invalid error union type");
            }
            break;
        case TypeTag::UserDefined:
            value->data = UserDefinedValue{};
            break;
        case TypeTag::Function:
            // Functions are typically not instantiated as values
            throw std::runtime_error("Cannot create a value for Function type");
        case TypeTag::Closure:
            // Closures are typically not instantiated as default values
            throw std::runtime_error("Cannot create a default value for Closure type");
        case TypeTag::Any:
            // For Any type, we'll use std::monostate as a placeholder
            value->data = std::monostate{};
            break;
        default:
            throw std::runtime_error("Unsupported type tag: "
                                     + std::to_string(static_cast<int>(type->tag)));
        }

        return value;
    }

    bool isCompatible(TypePtr source, TypePtr target) { return canConvert(source, target); }

    TypePtr getCommonType(TypePtr a, TypePtr b)
    {   if(!a || !b)
            return nullptr;
    // Handle Any type
    if (a->tag == TypeTag::Any) return b;
    if (b->tag == TypeTag::Any) return a;

    // Handle Nil type
    if (a->tag == TypeTag::Nil) return b;
    if (b->tag == TypeTag::Nil) return a;

    // Handle Bool type
    if (a->tag == TypeTag::Bool && b->tag == TypeTag::Bool) {
        return a;
    }

    // If types are the same, return either
    if (a->tag == b->tag) {
        return a;
    }

    // Handle numeric type promotions
    if (isNumericType(a->tag) && isNumericType(b->tag)) {
        return getWiderType(a, b);
    }

    // Handle other type conversions
    if (canConvert(a, b)) return b;
    if (canConvert(b, a)) return a;
    throw std::runtime_error("Incompatible types: " + a->toString() + " and " + b->toString());
    }

    void addUserDefinedType(const std::string &name, TypePtr type)
    {
        userDefinedTypes[name] = type;
    }

    TypePtr getUserDefinedType(const std::string &name)
    {
        if (userDefinedTypes.find(name) != userDefinedTypes.end()) {
            return userDefinedTypes[name];
        }
        throw std::runtime_error("User-defined type not found: " + name);
    }

    // Enhanced type alias methods for advanced type system
    void registerTypeAlias(const std::string &alias, TypePtr type) {
        // Check for circular dependencies before registering
        if (hasCircularDependency(alias, type)) {
            throw std::runtime_error("Circular dependency detected in type alias: " + alias);
        }
        typeAliases[alias] = type;
    }

    TypePtr resolveTypeAlias(const std::string &alias) {
        auto it = typeAliases.find(alias);
        if (it != typeAliases.end()) {
            return it->second;
        }
        return nullptr; // Return nullptr if not found, let caller handle
    }

    // Legacy methods for backward compatibility
    void addTypeAlias(const std::string &alias, TypePtr type) { 
        registerTypeAlias(alias, type);
    }

    TypePtr getTypeAlias(const std::string &alias)
    {
        TypePtr resolved = resolveTypeAlias(alias);
        if (resolved) {
            return resolved;
        }
        throw std::runtime_error("Type alias not found: " + alias);
    }

    // Error type registry methods
    void registerBuiltinErrors() {
        errorTypes["DivisionByZero"] = DIVISION_BY_ZERO_ERROR;
        errorTypes["IndexOutOfBounds"] = INDEX_OUT_OF_BOUNDS_ERROR;
        errorTypes["NullReference"] = NULL_REFERENCE_ERROR;
        errorTypes["TypeConversion"] = TYPE_CONVERSION_ERROR;
        errorTypes["IOError"] = IO_ERROR;
        errorTypes["ParseError"] = PARSE_ERROR;
        errorTypes["NetworkError"] = NETWORK_ERROR;
    }

    void registerUserError(const std::string& name, TypePtr type) {
        errorTypes[name] = type;
    }

    TypePtr getErrorType(const std::string& name) {
        auto it = errorTypes.find(name);
        if (it != errorTypes.end()) {
            return it->second;
        }
        throw std::runtime_error("Error type not found: " + name);
    }

    bool isErrorType(const std::string& name) {
        return errorTypes.find(name) != errorTypes.end();
    }

    // Create error union type
    TypePtr createErrorUnionType(TypePtr successType, const std::vector<std::string>& errorTypeNames = {}, bool isGeneric = false) {
        ErrorUnionType errorUnion;
        errorUnion.successType = successType;
        errorUnion.errorTypes = errorTypeNames;
        errorUnion.isGenericError = isGeneric;
        
        return std::make_shared<Type>(TypeTag::ErrorUnion, errorUnion);
    }

    // Create function type (legacy)
    TypePtr createFunctionType(const std::vector<TypePtr>& paramTypes, TypePtr returnType) {
        FunctionType functionType(paramTypes, returnType);
        return std::make_shared<Type>(TypeTag::Function, functionType);
    }
    
    // Create function type with named parameters
    TypePtr createFunctionType(const std::vector<std::string>& paramNames,
                              const std::vector<TypePtr>& paramTypes, 
                              TypePtr returnType,
                              const std::vector<bool>& hasDefaults = {}) {
        FunctionType functionType(paramNames, paramTypes, returnType, hasDefaults);
        return std::make_shared<Type>(TypeTag::Function, functionType);
    }
    
    // Create tuple type
    TypePtr createTupleType(const std::vector<TypePtr>& elementTypes) {
        TupleType tupleType(elementTypes);
        return std::make_shared<Type>(TypeTag::Tuple, tupleType);
    }
    
    // Create function type from AST function type annotation (implemented below)
    TypePtr createFunctionTypeFromAST(const AST::FunctionTypeAnnotation& funcTypeAnnotation);
    
    // Function type inference for lambda expressions (implemented below)
    TypePtr inferFunctionType(const AST::LambdaExpr& lambda);
    
    // Function type compatibility checking
    bool areFunctionTypesCompatible(TypePtr fromFunc, TypePtr toFunc) {
        if (!fromFunc || !toFunc || 
            fromFunc->tag != TypeTag::Function || 
            toFunc->tag != TypeTag::Function) {
            return false;
        }
        
        auto fromFuncType = std::get<FunctionType>(fromFunc->extra);
        auto toFuncType = std::get<FunctionType>(toFunc->extra);
        
        return fromFuncType.isCompatibleWith(toFuncType);
    }
    
    // Function overloading support
    bool canOverloadFunction(const std::string& functionName,
                           const std::vector<TypePtr>& newParamTypes,
                           const std::vector<TypePtr>& existingParamTypes) {
        // Check if parameter lists are different enough to allow overloading
        if (newParamTypes.size() != existingParamTypes.size()) {
            return true; // Different arity allows overloading
        }
        
        // Check if any parameter types are different
        for (size_t i = 0; i < newParamTypes.size(); ++i) {
            if (!newParamTypes[i] || !existingParamTypes[i]) {
                continue;
            }
            
            if (newParamTypes[i]->tag != existingParamTypes[i]->tag) {
                return true; // Different parameter types allow overloading
            }
        }
        
        return false; // Same signature, no overloading allowed
    }
    


    TypePtr inferType(const ValuePtr &value) { return value->type; }

    bool checkType(const ValuePtr &value, const TypePtr &expectedType)
    {
        if (value->type->tag != expectedType->tag) {
            return false;
        }

        switch (expectedType->tag) {
        case TypeTag::Int:
        case TypeTag::Int8:
        case TypeTag::Int16:
        case TypeTag::Int32:
        case TypeTag::Int64:
        case TypeTag::UInt:
        case TypeTag::UInt8:
        case TypeTag::UInt16:
        case TypeTag::UInt32:
        case TypeTag::UInt64:
        case TypeTag::Float32:
        case TypeTag::Float64:
        case TypeTag::Bool:
        case TypeTag::String:
        case TypeTag::Nil:
            return true; // Simple types match by tag alone

        case TypeTag::List: {
            const auto &listType = std::get<ListType>(expectedType->extra);
            if (const auto *listValue = std::get_if<ListValue>(&value->data)) {
                for (const auto &element : listValue->elements) {
                    if (!checkType(element, listType.elementType)) {
                        return false;
                    }
                }
                return true;
            }
            break;
        }

        case TypeTag::Dict: {
            const auto &dictType = std::get<DictType>(expectedType->extra);
            if (const auto *dictValue = std::get_if<DictValue>(&value->data)) {
                for (const auto &[key, val] : dictValue->elements) {
                    if (!checkType(key, dictType.keyType) || !checkType(val, dictType.valueType)) {
                        return false;
                    }
                }
                return true;
            }
            break;
        }

        case TypeTag::Tuple: {
            const auto &tupleType = std::get<TupleType>(expectedType->extra);
            if (const auto *tupleValue = std::get_if<TupleValue>(&value->data)) {
                // Check that tuple has correct number of elements
                if (tupleValue->elements.size() != tupleType.elementTypes.size()) {
                    return false;
                }
                
                // Check each element type
                for (size_t i = 0; i < tupleValue->elements.size(); ++i) {
                    if (!checkType(tupleValue->elements[i], tupleType.elementTypes[i])) {
                        return false;
                    }
                }
                return true;
            }
            break;
        }

        case TypeTag::Sum: {
            const auto &sumType = std::get<SumType>(expectedType->extra);
            if (const auto *sumValue = std::get_if<SumValue>(&value->data)) {
                if (sumValue->activeVariant >= sumType.variants.size()) {
                    return false;
                }
                const auto &variantType = sumType.variants[sumValue->activeVariant];
                return checkType(sumValue->value, variantType);
            }
            break;
        }

       case TypeTag::Enum: {
            if (const auto *enumType = std::get_if<EnumType>(&expectedType->extra)) {
                if (!enumType->values.empty()) {
                    value->data = EnumValue(enumType->values[0], expectedType);
                } else {
                    value->data = std::string(""); // Empty enum, use empty string as default
                }
            } else {
                throw std::runtime_error("Invalid enum type");
            }
            break;
        }

        case TypeTag::Function:
            // Function type checking might involve checking the signature
            // This is a placeholder and might need more complex logic
            return true;

        case TypeTag::Closure:
            // Closure type checking - for now, just check if it's a closure
            return std::holds_alternative<ClosureValue>(value->data);

        case TypeTag::Any:
            // Any type always matches
            return true;

        case TypeTag::Channel:
            // Channel types match by tag alone for now
            return true;

        case TypeTag::Union:
        case TypeTag::ErrorUnion:
        case TypeTag::Range:
        case TypeTag::UserDefined:
        case TypeTag::Class:
        case TypeTag::Object:
        case TypeTag::Module:
            // TODO: implement checks for these
            return false;

        //default:
        //    throw std::runtime_error("Unsupported type tag: "
        //                             + std::to_string(static_cast<int>(expectedType->tag)));
        }

        // Handle Union type separately, as it can match multiple types
        if (expectedType->tag == TypeTag::Union) {
            const auto &unionType = std::get<UnionType>(expectedType->extra);
            for (const auto &type : unionType.types) {
                if (checkType(value, type)) {
                    return true;
                }
            }
            return false;
        }

        // Handle ErrorUnion type separately
        if (expectedType->tag == TypeTag::ErrorUnion) {
            const auto &errorUnionType = std::get<ErrorUnionType>(expectedType->extra);
            
            // Check if value is an error
            if (const auto *errorValue = std::get_if<ErrorValue>(&value->data)) {
                // If it's a generic error union, any error is valid
                if (errorUnionType.isGenericError) {
                    return true;
                }
                // Check if the error type is in the allowed list
                return std::find(errorUnionType.errorTypes.begin(), 
                               errorUnionType.errorTypes.end(), 
                               errorValue->errorType) != errorUnionType.errorTypes.end();
            }
            
            // Check if value matches the success type
            return checkType(value, errorUnionType.successType);
        }

        return false; // Fallback for non-matching types
    }

    ValuePtr convert(const ValuePtr &value, TypePtr targetType)
    {
        if (!isCompatible(value->type, targetType)) {
            throw std::runtime_error("Incompatible types: " + value->type->toString() + " and "
                                     + targetType->toString());
        }

        ValuePtr result = std::make_shared<Value>();
        result->type = targetType;

        std::visit(
            overloaded{[&](int64_t v) {
                           switch (targetType->tag) {
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = v;
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from int64_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](int32_t v) {
                           switch (targetType->tag) {
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = v;
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from int32_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](int16_t v) {
                           switch (targetType->tag) {
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = v;
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from int16_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](int8_t v) {
                           switch (targetType->tag) {
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = v;
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from int8_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](uint64_t v) {
                           switch (targetType->tag) {
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = v;
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from uint64_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](uint32_t v) {
                           switch (targetType->tag) {
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = v;
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from uint32_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](uint16_t v) {
                           switch (targetType->tag) {
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = v;
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from uint16_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](uint8_t v) {
                           switch (targetType->tag) {
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = v;
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from uint8_t to "
                                                        + targetType->toString());
                           }
                       },
                       [&](double v) {
                           switch (targetType->tag) {
                           case TypeTag::Float64:
                               result->data = v;
                               break;
                           case TypeTag::Float32:
                               result->data = safe_cast<float>(v);
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               // For large literals, use range checking instead of safe_cast
                               if (v >= static_cast<double>(std::numeric_limits<int64_t>::min()) && 
                                   v <= static_cast<double>(std::numeric_limits<int64_t>::max())) {
                                   result->data = static_cast<int64_t>(v);
                               } else {
                                   throw std::runtime_error("Value out of range for int64_t: " + std::to_string(v));
                               }
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               // For large literals that were converted to double, use direct cast
                               // This handles cases like 18446744073709551615 which becomes double in parser
                               if (v >= 0 && v <= static_cast<double>(std::numeric_limits<uint64_t>::max())) {
                                   result->data = static_cast<uint64_t>(v);
                               } else {
                                   throw std::runtime_error("Value out of range for uint64_t: " + std::to_string(v));
                               }
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from double to "
                                                        + targetType->toString());
                           }
                       },
                       [&](float v) {
                           switch (targetType->tag) {
                           case TypeTag::Float32:
                               result->data = v;
                               break;
                           case TypeTag::Float64:
                               result->data = safe_cast<double>(v);
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = safe_cast<int64_t>(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(v);
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(v);
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(v);
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = safe_cast<uint64_t>(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(v);
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(v);
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(v);
                               break;
                           case TypeTag::String:
                               result->data = std::to_string(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from float to "
                                                        + targetType->toString());
                           }
                       },
                       [&](const std::string &v) {
                           switch (targetType->tag) {
                           case TypeTag::String:
                               result->data = v;
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = std::stoll(v);
                               break;
                           case TypeTag::Int8:
                               result->data = safe_cast<int8_t>(std::stoll(v));
                               break;
                           case TypeTag::Int16:
                               result->data = safe_cast<int16_t>(std::stoll(v));
                               break;
                           case TypeTag::Int32:
                               result->data = safe_cast<int32_t>(std::stoll(v));
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = std::stoull(v);
                               break;
                           case TypeTag::UInt8:
                               result->data = safe_cast<uint8_t>(std::stoull(v));
                               break;
                           case TypeTag::UInt16:
                               result->data = safe_cast<uint16_t>(std::stoull(v));
                               break;
                           case TypeTag::UInt32:
                               result->data = safe_cast<uint32_t>(std::stoull(v));
                               break;
                           case TypeTag::Float32:
                               result->data = std::stof(v);
                               break;
                           case TypeTag::Float64:
                               result->data = std::stod(v);
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from string to "
                                                        + targetType->toString());
                           }
                       },
                       [&](bool v) {
                           switch (targetType->tag) {
                           case TypeTag::Bool:
                               result->data = v;
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = v ? 1LL : 0LL;
                               break;
                           case TypeTag::Int8:
                               result->data = v ? int8_t(1) : int8_t(0);
                               break;
                           case TypeTag::Int16:
                               result->data = v ? int16_t(1) : int16_t(0);
                               break;
                           case TypeTag::Int32:
                               result->data = v ? 1 : 0;
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = v ? 1ULL : 0ULL;
                               break;
                           case TypeTag::UInt8:
                               result->data = v ? uint8_t(1) : uint8_t(0);
                               break;
                           case TypeTag::UInt16:
                               result->data = v ? uint16_t(1) : uint16_t(0);
                               break;
                           case TypeTag::UInt32:
                               result->data = v ? 1U : 0U;
                               break;
                           case TypeTag::Float32:
                               result->data = v ? 1.0f : 0.0f;
                               break;
                           case TypeTag::Float64:
                               result->data = v ? 1.0 : 0.0;
                               break;
                           case TypeTag::String:
                               result->data = v ? "true" : "false";
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from bool to "
                                                        + targetType->toString());
                           }
                       },
                       [&](const std::monostate &) {
                           switch (targetType->tag) {
                           case TypeTag::Nil:
                               result->data = std::monostate{};
                               break;
                           case TypeTag::Bool:
                               result->data = false;
                               break;
                           case TypeTag::Int:
                           case TypeTag::Int64:
                               result->data = 0LL;
                               break;
                           case TypeTag::Int8:
                               result->data = int8_t(0);
                               break;
                           case TypeTag::Int16:
                               result->data = int16_t(0);
                               break;
                           case TypeTag::Int32:
                               result->data = 0;
                               break;
                           case TypeTag::UInt:
                           case TypeTag::UInt64:
                               result->data = 0ULL;
                               break;
                           case TypeTag::UInt8:
                               result->data = uint8_t(0);
                               break;
                           case TypeTag::UInt16:
                               result->data = uint16_t(0);
                               break;
                           case TypeTag::UInt32:
                               result->data = 0U;
                               break;
                           case TypeTag::Float32:
                               result->data = 0.0f;
                               break;
                           case TypeTag::Float64:
                               result->data = 0.0;
                               break;
                           case TypeTag::String:
                               result->data = "nil";
                               break;
                           default:
                               throw std::runtime_error("Unsupported conversion from nil to "
                                                        + targetType->toString());
                           }
                       },
                       [&](const auto &) {
                           throw std::runtime_error("Unsupported conversion from "
                                                    + value->type->toString() + " to "
                                                    + targetType->toString());
                       }},
            value->data);

        return result;
    }

private:
    // Helper method to convert AST::TypeAnnotation to TypePtr (implemented in function_types.cpp)
    TypePtr convertASTTypeToTypePtr(std::shared_ptr<AST::TypeAnnotation> astType);


};