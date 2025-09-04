//types.hh
#pragma once

#include "memory.hh"
#include "value.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

class TypeSystem
{
private:
    std::map<std::string, TypePtr> userDefinedTypes;
    std::map<std::string, TypePtr> typeAliases;
    std::map<std::string, TypePtr> errorTypes;
    MemoryManager<> &memoryManager;
    MemoryManager<>::Region &region;

private:
    // Helper method to compare types for equality (more sophisticated than just tag comparison)
    bool areTypesEqual(TypePtr a, TypePtr b) {
        if (!a || !b) {
            return a == b;
        }
        
        if (a->tag != b->tag) {
            return false;
        }
        
        // For user-defined types, compare names
        if (a->tag == TypeTag::UserDefined) {
            const auto* aUserType = std::get_if<UserDefinedType>(&a->extra);
            const auto* bUserType = std::get_if<UserDefinedType>(&b->extra);
            if (aUserType && bUserType) {
                return aUserType->name == bUserType->name;
            }
        }
        
        // For other types, tag comparison is sufficient for now
        return true;
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

        // Union type compatibility (Requirement 2.2, 2.4)
        if (from->tag == TypeTag::Union) {
            // A union type can be converted to another type if any of its variants can be converted
            auto unionTypes = std::get<UnionType>(from->extra).types;
            return std::any_of(unionTypes.begin(), unionTypes.end(),
                               [&](TypePtr type) { return canConvert(type, to); });
        }
        
        // Converting to union type (Requirement 2.2)
        if (to->tag == TypeTag::Union) {
            // A type can be converted to a union type if it's compatible with any variant
            auto unionTypes = std::get<UnionType>(to->extra).types;
            return std::any_of(unionTypes.begin(), unionTypes.end(),
                               [&](TypePtr type) { return canConvert(from, type); });
        }
        
        // Union to union compatibility (Requirement 2.4)
        if (from->tag == TypeTag::Union && to->tag == TypeTag::Union) {
            auto fromUnionTypes = std::get<UnionType>(from->extra).types;
            auto toUnionTypes = std::get<UnionType>(to->extra).types;
            
            // All variants in 'from' must be convertible to at least one variant in 'to'
            return std::all_of(fromUnionTypes.begin(), fromUnionTypes.end(),
                [&](TypePtr fromType) {
                    return std::any_of(toUnionTypes.begin(), toUnionTypes.end(),
                        [&](TypePtr toType) { return canConvert(fromType, toType); });
                });
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
    const TypePtr ENUM_TYPE = std::make_shared<Type>(TypeTag::Enum);
    const TypePtr SUM_TYPE = std::make_shared<Type>(TypeTag::Sum);
    const TypePtr OBJECT_TYPE = std::make_shared<Type>(TypeTag::Object);
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
        if (name == "int") return INT_TYPE;
        if (name == "float") return FLOAT64_TYPE;
        if (name == "string") return STRING_TYPE;
        if (name == "bool") return BOOL_TYPE;
        if (name == "list") return LIST_TYPE;
        if (name == "dict") return DICT_TYPE;
        if (name == "object") return OBJECT_TYPE;
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
            // For union types, create a value with the first variant (Requirement 2.1)
            if (const auto *unionType = std::get_if<UnionType>(&type->extra)) {
                if (!unionType->types.empty()) {
                    // Create a value of the first variant type
                    ValuePtr variantValue = createValue(unionType->types[0]);
                    value->data = variantValue->data;
                    // Keep the union type but store the variant data
                    value->type = type;
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
    
    // Public wrapper for canConvert (needed by TypeMatcher)
    bool isConvertible(TypePtr from, TypePtr to) { return canConvert(from, to); }

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

    // Handle union types (Requirement 2.4)
    if (a->tag == TypeTag::Union && b->tag == TypeTag::Union) {
        // Merge two union types
        auto aVariants = std::get<UnionType>(a->extra).types;
        auto bVariants = std::get<UnionType>(b->extra).types;
        
        std::vector<TypePtr> mergedTypes = aVariants;
        for (const auto& bType : bVariants) {
            bool found = false;
            for (const auto& aType : aVariants) {
                if (aType->tag == bType->tag) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                mergedTypes.push_back(bType);
            }
        }
        
        return createUnionType(mergedTypes);
    }
    
    if (a->tag == TypeTag::Union) {
        // Check if b is compatible with any variant in a
        auto aVariants = std::get<UnionType>(a->extra).types;
        for (const auto& variant : aVariants) {
            if (canConvert(b, variant)) {
                return a; // Union already contains compatible type
            }
        }
        // Add b as a new variant
        auto newVariants = aVariants;
        newVariants.push_back(b);
        return createUnionType(newVariants);
    }
    
    if (b->tag == TypeTag::Union) {
        // Check if a is compatible with any variant in b
        auto bVariants = std::get<UnionType>(b->extra).types;
        for (const auto& variant : bVariants) {
            if (canConvert(a, variant)) {
                return b; // Union already contains compatible type
            }
        }
        // Add a as a new variant
        auto newVariants = bVariants;
        newVariants.push_back(a);
        return createUnionType(newVariants);
    }

    // Handle other type conversions
    if (canConvert(a, b)) return b;
    if (canConvert(b, a)) return a;
    
    // If no direct conversion is possible, create a union type
    return createUnionType({a, b});
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

    void addTypeAlias(const std::string &alias, TypePtr type) { typeAliases[alias] = type; }

    TypePtr getTypeAlias(const std::string &alias)
    {
        if (typeAliases.find(alias) != typeAliases.end()) {
            return typeAliases[alias];
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

    // Create union type (Requirement 2.1, 2.2)
    TypePtr createUnionType(const std::vector<TypePtr>& types) {
        if (types.empty()) {
            throw std::runtime_error("Cannot create empty union type");
        }
        
        // Remove duplicates and flatten nested unions
        std::vector<TypePtr> flattenedTypes;
        for (const auto& type : types) {
            if (type->tag == TypeTag::Union) {
                // Flatten nested union types
                const auto& unionType = std::get<UnionType>(type->extra);
                for (const auto& nestedType : unionType.types) {
                    // Check for duplicates with more sophisticated comparison
                    bool found = false;
                    for (const auto& existing : flattenedTypes) {
                        if (areTypesEqual(existing, nestedType)) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        flattenedTypes.push_back(nestedType);
                    }
                }
            } else {
                // Check for duplicates with more sophisticated comparison
                bool found = false;
                for (const auto& existing : flattenedTypes) {
                    if (areTypesEqual(existing, type)) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    flattenedTypes.push_back(type);
                }
            }
        }
        
        // If only one type remains after flattening, return it directly
        if (flattenedTypes.size() == 1) {
            return flattenedTypes[0];
        }
        
        UnionType unionType;
        unionType.types = flattenedTypes;
        
        return std::make_shared<Type>(TypeTag::Union, unionType);
    }
    
    // Check if a type is a union type (Requirement 2.1)
    bool isUnionType(TypePtr type) {
        return type && type->tag == TypeTag::Union;
    }
    
    // Get union type variants (Requirement 2.1)
    std::vector<TypePtr> getUnionVariants(TypePtr type) {
        if (!isUnionType(type)) {
            throw std::runtime_error("Type is not a union type");
        }
        
        const auto& unionType = std::get<UnionType>(type->extra);
        return unionType.types;
    }
    
    // Check if union type requires pattern matching (Requirement 2.3)
    bool requiresPatternMatching(TypePtr type) {
        return isUnionType(type);
    }
    
    // Create a union value with a specific variant (Requirement 2.1, 2.2)
    ValuePtr createUnionValue(TypePtr unionType, TypePtr variantType, ValuePtr variantValue) {
        if (!isUnionType(unionType)) {
            throw std::runtime_error("Type is not a union type");
        }
        
        const auto& unionVariants = std::get<UnionType>(unionType->extra).types;
        
        // Check if the variant type is valid for this union
        bool validVariant = false;
        for (const auto& variant : unionVariants) {
            if (canConvert(variantType, variant)) {
                validVariant = true;
                break;
            }
        }
        
        if (!validVariant) {
            throw std::runtime_error("Variant type is not compatible with union type");
        }
        
        ValuePtr unionValue = memoryManager.makeRef<Value>(region);
        unionValue->type = unionType;
        unionValue->data = variantValue->data;
        
        return unionValue;
    }
    
    // Get the active variant type from a union value (Requirement 2.3)
    TypePtr getActiveVariantType(ValuePtr unionValue) {
        if (!isUnionType(unionValue->type)) {
            throw std::runtime_error("Value is not a union type");
        }
        
        const auto& unionVariants = std::get<UnionType>(unionValue->type->extra).types;
        
        // Try to determine which variant type matches the current data
        for (const auto& variant : unionVariants) {
            ValuePtr testValue = memoryManager.makeRef<Value>(region);
            testValue->type = variant;
            testValue->data = unionValue->data;
            
            if (checkType(testValue, variant)) {
                return variant;
            }
        }
        
        throw std::runtime_error("Cannot determine active variant type");
    }

    // Create error union type
    TypePtr createErrorUnionType(TypePtr successType, const std::vector<std::string>& errorTypeNames = {}, bool isGeneric = false) {
        ErrorUnionType errorUnion;
        errorUnion.successType = successType;
        errorUnion.errorTypes = errorTypeNames;
        errorUnion.isGenericError = isGeneric;
        
        return std::make_shared<Type>(TypeTag::ErrorUnion, errorUnion);
    }

    // Option type implementation (Requirement 3.1, 3.2, 3.3, 3.4)
    // Create Option<T> type as union of Some<T> and None
    TypePtr createOptionType(TypePtr valueType) {
        // Create Some variant type with structured fields
        UserDefinedType someType;
        someType.name = "Some";
        std::map<std::string, TypePtr> someFields;
        someFields["kind"] = STRING_TYPE;
        someFields["value"] = valueType;
        someType.fields.push_back({"Some", someFields});
        TypePtr someTypePtr = std::make_shared<Type>(TypeTag::UserDefined, someType);
        
        // Create None variant type with structured fields
        UserDefinedType noneType;
        noneType.name = "None";
        std::map<std::string, TypePtr> noneFields;
        noneFields["kind"] = STRING_TYPE;
        noneType.fields.push_back({"None", noneFields});
        TypePtr noneTypePtr = std::make_shared<Type>(TypeTag::UserDefined, noneType);
        
        // Create union type of Some and None
        return createUnionType({someTypePtr, noneTypePtr});
    }
    
    // Create Some<T> value (compatible with ok() from error handling system)
    ValuePtr createSome(TypePtr valueType, ValuePtr value) {
        TypePtr optionType = createOptionType(valueType);
        
        // Create Some variant with structured data
        UserDefinedValue someValue;
        someValue.variantName = "Some";
        someValue.fields["kind"] = memoryManager.makeRef<Value>(region, STRING_TYPE, "Some");
        someValue.fields["value"] = value;
        
        ValuePtr someVariant = memoryManager.makeRef<Value>(region);
        someVariant->type = optionType;
        someVariant->data = someValue;
        
        return someVariant;
    }
    
    // Create None value (compatible with error handling system)
    ValuePtr createNone(TypePtr valueType) {
        TypePtr optionType = createOptionType(valueType);
        
        // Create None variant with structured data
        UserDefinedValue noneValue;
        noneValue.variantName = "None";
        noneValue.fields["kind"] = memoryManager.makeRef<Value>(region, STRING_TYPE, "None");
        
        ValuePtr noneVariant = memoryManager.makeRef<Value>(region);
        noneVariant->type = optionType;
        noneVariant->data = noneValue;
        
        return noneVariant;
    }
    
    // Check if a value is Some variant
    bool isSome(ValuePtr optionValue) {
        if (!optionValue || !isUnionType(optionValue->type)) {
            return false;
        }
        
        if (const auto* userDefined = std::get_if<UserDefinedValue>(&optionValue->data)) {
            return userDefined->variantName == "Some";
        }
        
        return false;
    }
    
    // Check if a value is None variant
    bool isNone(ValuePtr optionValue) {
        if (!optionValue || !isUnionType(optionValue->type)) {
            return false;
        }
        
        if (const auto* userDefined = std::get_if<UserDefinedValue>(&optionValue->data)) {
            return userDefined->variantName == "None";
        }
        
        return false;
    }
    
    // Extract value from Some variant (requires pattern matching for safety)
    ValuePtr extractSomeValue(ValuePtr optionValue) {
        if (!isSome(optionValue)) {
            throw std::runtime_error("Cannot extract value from None or non-Option type");
        }
        
        const auto* userDefined = std::get_if<UserDefinedValue>(&optionValue->data);
        if (!userDefined) {
            throw std::runtime_error("Invalid Option value structure");
        }
        
        auto valueIt = userDefined->fields.find("value");
        if (valueIt == userDefined->fields.end()) {
            throw std::runtime_error("Some variant missing value field");
        }
        
        return valueIt->second;
    }
    
    // Check if type requires explicit handling (for Option/Result safety)
    bool requiresExplicitHandling(TypePtr type) {
        return isUnionType(type);
    }
    
    // Result type implementation (Requirement 3.1, 3.2, 3.3, 3.4)
    // Create Result<T, E> type as union of Success<T> and Error<E>
    TypePtr createResultType(TypePtr successType, TypePtr errorType) {
        // Create Success variant type with structured fields
        UserDefinedType successVariantType;
        successVariantType.name = "Success";
        std::map<std::string, TypePtr> successFields;
        successFields["kind"] = STRING_TYPE;
        successFields["value"] = successType;
        successVariantType.fields.push_back({"Success", successFields});
        TypePtr successTypePtr = std::make_shared<Type>(TypeTag::UserDefined, successVariantType);
        
        // Create Error variant type with structured fields
        UserDefinedType errorVariantType;
        errorVariantType.name = "Error";
        std::map<std::string, TypePtr> errorFields;
        errorFields["kind"] = STRING_TYPE;
        errorFields["error"] = errorType;
        errorVariantType.fields.push_back({"Error", errorFields});
        TypePtr errorTypePtr = std::make_shared<Type>(TypeTag::UserDefined, errorVariantType);
        
        // Create union type of Success and Error
        return createUnionType({successTypePtr, errorTypePtr});
    }
    
    // Create Success<T> value (compatible with ok() from error handling system)
    ValuePtr createSuccess(TypePtr successType, ValuePtr value) {
        TypePtr resultType = createResultType(successType, STRING_TYPE); // Default error type to string
        
        // Create Success variant with structured data
        UserDefinedValue successValue;
        successValue.variantName = "Success";
        successValue.fields["kind"] = memoryManager.makeRef<Value>(region, STRING_TYPE, "Success");
        successValue.fields["value"] = value;
        
        ValuePtr successVariant = memoryManager.makeRef<Value>(region);
        successVariant->type = resultType;
        successVariant->data = successValue;
        
        return successVariant;
    }
    
    // Create Error<E> value (compatible with err() from error handling system)
    ValuePtr createError(TypePtr errorType, ValuePtr error) {
        TypePtr resultType = createResultType(STRING_TYPE, errorType); // Default success type to string
        
        // Create Error variant with structured data
        UserDefinedValue errorValue;
        errorValue.variantName = "Error";
        errorValue.fields["kind"] = memoryManager.makeRef<Value>(region, STRING_TYPE, "Error");
        errorValue.fields["error"] = error;
        
        ValuePtr errorVariant = memoryManager.makeRef<Value>(region);
        errorVariant->type = resultType;
        errorVariant->data = errorValue;
        
        return errorVariant;
    }
    
    // Check if a value is Success variant
    bool isSuccess(ValuePtr resultValue) {
        if (!resultValue || !isUnionType(resultValue->type)) {
            return false;
        }
        
        if (const auto* userDefined = std::get_if<UserDefinedValue>(&resultValue->data)) {
            return userDefined->variantName == "Success";
        }
        
        return false;
    }
    
    // Check if a value is Error variant
    bool isError(ValuePtr resultValue) {
        if (!resultValue || !isUnionType(resultValue->type)) {
            return false;
        }
        
        if (const auto* userDefined = std::get_if<UserDefinedValue>(&resultValue->data)) {
            return userDefined->variantName == "Error";
        }
        
        return false;
    }
    
    // Extract value from Success variant (requires pattern matching for safety)
    ValuePtr extractSuccessValue(ValuePtr resultValue) {
        if (!isSuccess(resultValue)) {
            throw std::runtime_error("Cannot extract value from Error or non-Result type");
        }
        
        const auto* userDefined = std::get_if<UserDefinedValue>(&resultValue->data);
        if (!userDefined) {
            throw std::runtime_error("Invalid Result value structure");
        }
        
        auto valueIt = userDefined->fields.find("value");
        if (valueIt == userDefined->fields.end()) {
            throw std::runtime_error("Success variant missing value field");
        }
        
        return valueIt->second;
    }
    
    // Extract error from Error variant (requires pattern matching for safety)
    ValuePtr extractErrorValue(ValuePtr resultValue) {
        if (!isError(resultValue)) {
            throw std::runtime_error("Cannot extract error from Success or non-Result type");
        }
        
        const auto* userDefined = std::get_if<UserDefinedValue>(&resultValue->data);
        if (!userDefined) {
            throw std::runtime_error("Invalid Result value structure");
        }
        
        auto errorIt = userDefined->fields.find("error");
        if (errorIt == userDefined->fields.end()) {
            throw std::runtime_error("Error variant missing error field");
        }
        
        return errorIt->second;
    }

    // Typed container support (Requirement 4.1, 4.2, 4.3, 4.4)
    
    // Create typed list type [elementType]
    TypePtr createTypedListType(TypePtr elementType) {
        if (!elementType) {
            throw std::runtime_error("Element type cannot be null for typed list");
        }
        
        ListType listType;
        listType.elementType = elementType;
        
        return std::make_shared<Type>(TypeTag::List, listType);
    }
    
    // Create typed dictionary type {keyType: valueType}
    TypePtr createTypedDictType(TypePtr keyType, TypePtr valueType) {
        if (!keyType || !valueType) {
            throw std::runtime_error("Key and value types cannot be null for typed dictionary");
        }
        
        DictType dictType;
        dictType.keyType = keyType;
        dictType.valueType = valueType;
        
        return std::make_shared<Type>(TypeTag::Dict, dictType);
    }
    
    // Validate homogeneous type for containers (Requirement 4.4)
    bool validateContainerHomogeneity(TypePtr containerType, const std::vector<ValuePtr>& elements) {
        if (!containerType) return false;
        
        if (containerType->tag == TypeTag::List) {
            auto listType = std::get<ListType>(containerType->extra);
            TypePtr expectedElementType = listType.elementType;
            
            for (const auto& element : elements) {
                if (!canConvert(element->type, expectedElementType)) {
                    return false;
                }
            }
            return true;
        }
        
        return false; // Not a supported container type
    }
    
    // Validate dictionary key-value pairs for homogeneous typing (Requirement 4.4)
    bool validateDictHomogeneity(TypePtr dictType, const std::vector<std::pair<ValuePtr, ValuePtr>>& pairs) {
        if (!dictType || dictType->tag != TypeTag::Dict) return false;
        
        auto dictTypeInfo = std::get<DictType>(dictType->extra);
        TypePtr expectedKeyType = dictTypeInfo.keyType;
        TypePtr expectedValueType = dictTypeInfo.valueType;
        
        for (const auto& pair : pairs) {
            if (!canConvert(pair.first->type, expectedKeyType) || 
                !canConvert(pair.second->type, expectedValueType)) {
                return false;
            }
        }
        return true;
    }
    
    // Get element type from a typed list (Requirement 4.1)
    TypePtr getListElementType(TypePtr listType) {
        if (!listType || listType->tag != TypeTag::List) {
            return nullptr;
        }
        
        auto listTypeInfo = std::get<ListType>(listType->extra);
        return listTypeInfo.elementType;
    }
    
    // Get key and value types from a typed dictionary (Requirement 4.2)
    std::pair<TypePtr, TypePtr> getDictTypes(TypePtr dictType) {
        if (!dictType || dictType->tag != TypeTag::Dict) {
            return {nullptr, nullptr};
        }
        
        auto dictTypeInfo = std::get<DictType>(dictType->extra);
        return {dictTypeInfo.keyType, dictTypeInfo.valueType};
    }

    // Error handling system compatibility
    TypePtr createFallibleType(TypePtr successType, const std::vector<std::string>& errorTypes) {
        // Create a union type compatible with the error handling system
        // This maps to the error handling system's Type?ErrorType syntax
        std::vector<TypePtr> unionTypes = {successType};
        
        // Add error types to the union
        for (const auto& errorTypeName : errorTypes) {
            if (isErrorType(errorTypeName)) {
                unionTypes.push_back(getErrorType(errorTypeName));
            } else {
                // Create a user-defined error type
                UserDefinedType errorType;
                errorType.name = errorTypeName;
                TypePtr errorTypePtr = std::make_shared<Type>(TypeTag::UserDefined, errorType);
                unionTypes.push_back(errorTypePtr);
            }
        }
        
        return createUnionType(unionTypes);
    }
    
    // Check if type is compatible with ? operator from error handling system
    bool isFallibleType(TypePtr type) {
        return isUnionType(type) || type->tag == TypeTag::ErrorUnion;
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

        case TypeTag::Any:
            // Any type always matches
            return true;

        case TypeTag::Union: {
            // Union type checking is handled after the switch statement
            break;
        }

        case TypeTag::ErrorUnion: {
            // ErrorUnion type checking - check if value matches success type or error types
            const auto &errorUnionType = std::get<ErrorUnionType>(expectedType->extra);
            return checkType(value, errorUnionType.successType);
        }

        case TypeTag::Range:
            // Range type checking - for now, just check if it's a range
            return true;

        case TypeTag::UserDefined: {
            // UserDefined type checking - check if the variant name matches
            if (const auto *userValue = std::get_if<UserDefinedValue>(&value->data)) {
                return true; // Basic check - could be enhanced
            }
            return false;
        }

        case TypeTag::Class:
            // Class type checking
            return true;

        case TypeTag::Object:
            // Object type checking
            return true;

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
};

// Type Matcher class for pattern matching and type discrimination (Requirement 8.1, 8.2, 8.3, 8.4)
class TypeMatcher {
private:
    TypeSystem* typeSystem;
    MemoryManager<>& memoryManager;
    MemoryManager<>::Region& region;

public:
    TypeMatcher(TypeSystem* ts, MemoryManager<>& memManager, MemoryManager<>::Region& reg)
        : typeSystem(ts), memoryManager(memManager), region(reg) {}

    // Basic pattern matching (Requirement 2.3, 8.2)
    bool matchesType(ValuePtr value, TypePtr pattern) {
        if (!value || !pattern) {
            return false;
        }
        
        return typeSystem->isConvertible(value->type, pattern);
    }
    
    // Extract values from pattern matching
    std::vector<ValuePtr> extractValues(ValuePtr value, TypePtr pattern) {
        std::vector<ValuePtr> extracted;
        
        if (!matchesType(value, pattern)) {
            return extracted;
        }
        
        // For union types, extract the active variant
        if (typeSystem->isUnionType(value->type)) {
            extracted.push_back(value);
        } else {
            extracted.push_back(value);
        }
        
        return extracted;
    }
    
    // Union type matching with safety (Requirement 2.3, 8.1)
    bool matchesUnionVariant(ValuePtr value, TypePtr unionType, size_t variantIndex) {
        if (!typeSystem->isUnionType(unionType)) {
            return false;
        }
        
        auto variants = typeSystem->getUnionVariants(unionType);
        if (variantIndex >= variants.size()) {
            return false;
        }
        
        TypePtr expectedVariant = variants[variantIndex];
        return matchesType(value, expectedVariant);
    }
    
    // Check if pattern matching is exhaustive
    bool isExhaustiveMatch(TypePtr unionType, const std::vector<TypePtr>& patterns) {
        if (!typeSystem->isUnionType(unionType)) {
            return true; // Non-union types don't require exhaustive matching
        }
        
        auto variants = typeSystem->getUnionVariants(unionType);
        
        // Check that each variant is covered by at least one pattern
        for (const auto& variant : variants) {
            bool covered = false;
            for (const auto& pattern : patterns) {
                if (typeSystem->isConvertible(variant, pattern)) {
                    covered = true;
                    break;
                }
            }
            if (!covered) {
                return false;
            }
        }
        
        return true;
    }
    
    // Safe field access (Requirement 8.3)
    bool canAccessField(ValuePtr value, const std::string& fieldName) {
        if (!value) {
            return false;
        }
        
        if (const auto* userDefined = std::get_if<UserDefinedValue>(&value->data)) {
            return userDefined->fields.find(fieldName) != userDefined->fields.end();
        }
        
        return false;
    }
    
    ValuePtr safeFieldAccess(ValuePtr value, const std::string& fieldName) {
        if (!canAccessField(value, fieldName)) {
            throw std::runtime_error("Field '" + fieldName + "' does not exist in current variant");
        }
        
        const auto* userDefined = std::get_if<UserDefinedValue>(&value->data);
        return userDefined->fields.at(fieldName);
    }
    
    // Option/Result matching (Requirement 3.4, 8.1)
    bool isSome(ValuePtr optionValue) {
        return typeSystem->isSome(optionValue);
    }
    
    bool isNone(ValuePtr optionValue) {
        return typeSystem->isNone(optionValue);
    }
    
    bool isSuccess(ValuePtr resultValue) {
        return typeSystem->isSuccess(resultValue);
    }
    
    bool isError(ValuePtr resultValue) {
        return typeSystem->isError(resultValue);
    }
    
    // Runtime introspection (Requirement 8.4)
    std::string getTypeName(ValuePtr value) {
        if (!value || !value->type) {
            return "unknown";
        }
        
        if (const auto* userDefined = std::get_if<UserDefinedValue>(&value->data)) {
            return userDefined->variantName;
        }
        
        return value->type->toString();
    }
    
    std::vector<std::string> getFieldNames(ValuePtr value) {
        std::vector<std::string> fieldNames;
        
        if (!value) {
            return fieldNames;
        }
        
        if (const auto* userDefined = std::get_if<UserDefinedValue>(&value->data)) {
            for (const auto& [fieldName, _] : userDefined->fields) {
                fieldNames.push_back(fieldName);
            }
        }
        
        return fieldNames;
    }
    
    TypePtr getFieldType(ValuePtr value, const std::string& fieldName) {
        if (!canAccessField(value, fieldName)) {
            throw std::runtime_error("Field '" + fieldName + "' does not exist");
        }
        
        ValuePtr fieldValue = safeFieldAccess(value, fieldName);
        return fieldValue ? fieldValue->type : nullptr;
    }
};