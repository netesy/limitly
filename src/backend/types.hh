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
    
    // Handle frame-to-trait conversions
    if (from->tag == TypeTag::Frame && to->tag == TypeTag::Trait) {
        auto fromFrameType = std::get_if<FrameType>(&from->extra);
        auto toTraitType = std::get_if<TraitType>(&to->extra);
        std::cerr << "[DEBUG canConvert] Frame->Trait: fromFrame=" << (fromFrameType ? fromFrameType->name : "null") 
                  << ", toTrait=" << (toTraitType ? toTraitType->name : "null") << std::endl;
        if (fromFrameType && toTraitType) {
            std::cerr << "[DEBUG canConvert] Frame implements: ";
            for (const auto& t : fromFrameType->implements) std::cerr << t << " ";
            std::cerr << std::endl;
            // Check direct implements
            for (const auto& traitName : fromFrameType->implements) {
                if (traitName == toTraitType->name) {
                    std::cerr << "[DEBUG canConvert] Found match!" << std::endl;
                    return true;
                }
            }
            
            // Check frame registry for more complete info
            if (frameRegistry.count(fromFrameType->name)) {
                const auto& info = frameRegistry.at(fromFrameType->name);
                std::cerr << "[DEBUG canConvert] Frame registry implements: ";
                for (const auto& t : info.implements) std::cerr << t << " ";
                std::cerr << std::endl;
                for (const auto& traitName : info.implements) {
                    if (traitName == toTraitType->name) {
                        std::cerr << "[DEBUG canConvert] Found match in registry!" << std::endl;
                        return true;
                    }
                }
            }
        }
    }

    // Handle frame type conversions
    if (from->tag == TypeTag::Frame && to->tag == TypeTag::Frame) {
        // Get frame names from both types
        auto fromFrameType = std::get_if<FrameType>(&from->extra);
        auto toFrameType = std::get_if<FrameType>(&to->extra);
        
        if (fromFrameType && toFrameType) {
            // Frames are compatible if they have the same name
            return fromFrameType->name == toFrameType->name;
        }
        
        // If we can't get frame type info, fall back to pointer comparison
        return from == to;
    }

    // Handle enum type conversions - Strict identity enforcement
    if (from->tag == TypeTag::Enum && to->tag == TypeTag::Enum) {
        auto fromEnumType = std::get_if<EnumType>(&from->extra);
        auto toEnumType = std::get_if<EnumType>(&to->extra);

        if (fromEnumType && toEnumType) {
            // Enums must be strong, name-based unique types
            return fromEnumType->name == toEnumType->name;
        }
        return false; // Identity is not preserved if info is missing
    }

    // Handle Refined Types - Mandate 7
    if (from->tag == TypeTag::Refined) {
        if (auto* refined = std::get_if<RefinedType>(&from->extra)) {
            return canConvert(refined->baseType, to);
        }
    }
    if (to->tag == TypeTag::Refined) {
        if (auto* refined = std::get_if<RefinedType>(&to->extra)) {
            return canConvert(from, refined->baseType);
        }
    }

    // Handle Structural Type Compatibility
    if (to->tag == TypeTag::Structural) {
        auto toStruct = std::get_if<StructuralType>(&to->extra);
        if (!toStruct) return false;

        if (from->tag == TypeTag::Structural) {
            auto fromStruct = std::get_if<StructuralType>(&from->extra);
            if (!fromStruct) return false;

            // Target must be a subset of source (or equal)
            for (const auto& targetField : toStruct->fields) {
                bool found = false;
                for (const auto& sourceField : fromStruct->fields) {
                    if (targetField.first == sourceField.first) {
                        if (!canConvert(sourceField.second, targetField.second)) return false;
                        found = true;
                        break;
                    }
                }
                if (!found) return false;
            }
            return true;
        }

        if (from->tag == TypeTag::Frame) {
            auto fromFrame = std::get_if<FrameType>(&from->extra);
            if (!fromFrame) return false;

            // Frames can satisfy structural types if they have all required fields
            for (const auto& targetField : toStruct->fields) {
                bool found = false;
                
                // Check local frame info
                for (const auto& sourceField : fromFrame->fields) {
                    if (targetField.first == sourceField.first) {
                        if (!canConvert(sourceField.second, targetField.second)) return false;
                        found = true;
                        break;
                    }
                }
                
                // Check registry if not found locally
                if (!found && frameRegistry.count(fromFrame->name)) {
                    const auto& info = frameRegistry.at(fromFrame->name);
                    for (const auto& sourceField : info.fields) {
                        if (targetField.first == sourceField.first) {
                            if (!canConvert(sourceField.second, targetField.second)) return false;
                            found = true;
                            break;
                        }
                    }
                }
                
                if (!found) return false;
            }
            return true;
        }
    }

        // Numeric type conversions - Strict enforcement (Mandate 10)
        bool fromIsInt = (from->tag == TypeTag::Int || from->tag == TypeTag::Int8 || 
                         from->tag == TypeTag::Int16 || from->tag == TypeTag::Int32 || 
                         from->tag == TypeTag::Int64 || from->tag == TypeTag::Int128 ||
                         from->tag == TypeTag::UInt || from->tag == TypeTag::UInt8 || 
                         from->tag == TypeTag::UInt16 || from->tag == TypeTag::UInt32 || 
                         from->tag == TypeTag::UInt64 || from->tag == TypeTag::UInt128);
        bool toIsInt = (to->tag == TypeTag::Int || to->tag == TypeTag::Int8 || 
                       to->tag == TypeTag::Int16 || to->tag == TypeTag::Int32 || 
                       to->tag == TypeTag::Int64 || to->tag == TypeTag::Int128 ||
                       to->tag == TypeTag::UInt || to->tag == TypeTag::UInt8 || 
                       to->tag == TypeTag::UInt16 || to->tag == TypeTag::UInt32 || 
                       to->tag == TypeTag::UInt64 || to->tag == TypeTag::UInt128);
        
        if (fromIsInt && toIsInt) {
            return true;
        }
        
        // Float type conversions
        bool fromIsFloat = (from->tag == TypeTag::Float32 || from->tag == TypeTag::Float64);
        bool toIsFloat = (to->tag == TypeTag::Float32 || to->tag == TypeTag::Float64);
        
        if (fromIsFloat && toIsFloat) {
            return true;
        }
        
        // Mandate 10: No implicit int -> float
        // Explicitly removed the promotion branch here.

        // Handle list and dict type compatibility
        if (from->tag == TypeTag::List && to->tag == TypeTag::List) {
            auto fromListType = std::get_if<ListType>(&from->extra);
            auto toListType = std::get_if<ListType>(&to->extra);
            if (fromListType && toListType) {
                return canConvert(fromListType->elementType, toListType->elementType);
            }
            return true; // Generic list
        }

        if (from->tag == TypeTag::Dict && to->tag == TypeTag::Dict) {
            auto fromDictType = std::get_if<DictType>(&from->extra);
            auto toDictType = std::get_if<DictType>(&to->extra);
            if (fromDictType && toDictType) {
                return canConvert(fromDictType->keyType, toDictType->keyType) &&
                       canConvert(fromDictType->valueType, toDictType->valueType);
            }
            return true; // Generic dict
        }

        // Handle tuple type compatibility
        if (from->tag == TypeTag::Tuple && to->tag == TypeTag::Tuple) {
            auto fromTupleType = std::get_if<TupleType>(&from->extra);
            auto toTupleType = std::get_if<TupleType>(&to->extra);
            
            if (fromTupleType && toTupleType) {
                // Tuples must have same number of elements
                if (fromTupleType->elementTypes.size() != toTupleType->elementTypes.size()) {
                    return false;
                }
                
                // All corresponding element types must be compatible
                for (size_t i = 0; i < fromTupleType->elementTypes.size(); ++i) {
                    if (!canConvert(fromTupleType->elementTypes[i], toTupleType->elementTypes[i])) {
                        return false;
                    }
                }
                return true;
            }
            return true;
        }

        // Union and sum type compatibility - Mandate 9
        if (from->tag == TypeTag::Union) {
            if (auto* unionType = std::get_if<UnionType>(&from->extra)) {
                // ALL members of source union must be compatible with target
                return std::all_of(unionType->types.begin(), unionType->types.end(),
                                   [&](TypePtr type) { return canConvert(type, to); });
            }
        }
        
        // Target is union type - source can convert if it matches any member
        if (to->tag == TypeTag::Union) {
            if (auto* unionType = std::get_if<UnionType>(&to->extra)) {
                // For optional types (T?), allow T to be passed directly
                return std::any_of(unionType->types.begin(), unionType->types.end(),
                                   [&](TypePtr type) { return canConvert(from, type); });
            }
        }

        // Error union type compatibility
        if (from->tag == TypeTag::ErrorUnion && to->tag == TypeTag::ErrorUnion) {
            auto fromErrorUnion = std::get_if<ErrorUnionType>(&from->extra);
            auto toErrorUnion = std::get_if<ErrorUnionType>(&to->extra);
            
            if (fromErrorUnion && toErrorUnion) {
                // Success types must be compatible
                if (!canConvert(fromErrorUnion->successType, toErrorUnion->successType)) {
                    return false;
                }
                
                // If target is generic error (Type?), any error union is compatible
                if (toErrorUnion->isGenericError) {
                    return true;
                }
                
                // If source is generic error, it's only compatible with generic target
                if (fromErrorUnion->isGenericError) {
                    return toErrorUnion->isGenericError;
                }
                
                // Check that all source error types are in target error types
                for (const auto& sourceError : fromErrorUnion->errorTypes) {
                    bool found = std::find(toErrorUnion->errorTypes.begin(), 
                                         toErrorUnion->errorTypes.end(), 
                                         sourceError) != toErrorUnion->errorTypes.end();
                    if (!found) {
                        return false;
                    }
                }
                
                return true;
            }
            return true;
        }
        
        // Success type can be converted to error union if success types are compatible
        if (to->tag == TypeTag::ErrorUnion) {
            if (auto* toErrorUnion = std::get_if<ErrorUnionType>(&to->extra)) {
                return canConvert(from, toErrorUnion->successType);
            }
        }

        // Function type compatibility
        if (from->tag == TypeTag::Function && to->tag == TypeTag::Function) {
            // Handle case where one or both types don't have function type information
            auto fromFuncType = std::get_if<FunctionType>(&from->extra);
            auto toFuncType = std::get_if<FunctionType>(&to->extra);
            
            // If neither has specific function type info, they're compatible (generic function types)
            if (!fromFuncType && !toFuncType) {
                return true;
            }
            
            // If one is generic function type and other is specific, they're compatible
            if (!fromFuncType || !toFuncType) {
                return true;
            }
            
            // Both have specific function type information - do detailed compatibility check
            // Check parameter count
            if (fromFuncType->paramTypes.size() != toFuncType->paramTypes.size()) {
                return false;
            }
            
            // Check parameter types (contravariant)
            for (size_t i = 0; i < fromFuncType->paramTypes.size(); ++i) {
                if (!canConvert(toFuncType->paramTypes[i], fromFuncType->paramTypes[i])) {
                    return false;
                }
            }
            
            // Check return type (covariant)
            return canConvert(fromFuncType->returnType, toFuncType->returnType);
        }

        return false;
    }

private:
    bool isListType(TypePtr type) const { return type->tag == TypeTag::List; }
    bool isDictType(TypePtr type) const { return type->tag == TypeTag::Dict; }
    ValuePtr stringToNumber(const std::string &str, TypePtr targetType)
    {
        ValuePtr result = std::make_shared<Value>();
        result->type = targetType;

        try {
            // Handle all numeric types
            if (targetType->tag == TypeTag::Int || targetType->tag == TypeTag::Int8 || 
                targetType->tag == TypeTag::Int16 || targetType->tag == TypeTag::Int32 || 
                targetType->tag == TypeTag::Int64 || targetType->tag == TypeTag::Int128 ||
                targetType->tag == TypeTag::UInt || targetType->tag == TypeTag::UInt8 || 
                targetType->tag == TypeTag::UInt16 || targetType->tag == TypeTag::UInt32 || 
                targetType->tag == TypeTag::UInt64 || targetType->tag == TypeTag::UInt128) {
                // Check if string contains scientific notation or decimal point
                if (str.find('e') != std::string::npos || str.find('E') != std::string::npos || 
                    str.find('.') != std::string::npos) {
                    // Parse as long double first, then convert to integer if it's a whole number
                    long double doubleVal = std::stod(str);
                    if (doubleVal != std::floor(doubleVal)) {
                        throw std::runtime_error("Cannot convert non-integer value to integer type");
                    }
                    // Convert to integer string
                    result->data = std::to_string(static_cast<long long>(doubleVal));
                } else {
                    // Use string directly for integer values
                    result->data = str;
                }
            } else if (targetType->tag == TypeTag::Float32 || targetType->tag == TypeTag::Float64) {
                // Parse as floating point
                long double doubleVal = std::stold(str);
                std::ostringstream oss;
                if (targetType->tag == TypeTag::Float32) {
                    oss << std::setprecision(7) << std::fixed << static_cast<float>(doubleVal);
                } else {
                    oss << std::setprecision(15) << std::fixed << static_cast<double>(doubleVal);
                }
                result->data = oss.str();
            } else {
                throw std::runtime_error("Unsupported target type for numeric conversion");
            }
        } catch (const std::invalid_argument &e) {
            throw std::runtime_error("Invalid number format: " + str + " (" + std::string(e.what()) + ")");
        } catch (const std::out_of_range &e) {
            throw std::runtime_error("Number out of range: " + str + " (" + std::string(e.what()) + ")");
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to convert string to number: " + std::string(e.what()));
        }

        return result;
    }
    ValuePtr numberToString(const ValuePtr &value)
    {
        ValuePtr result = std::make_shared<Value>();
        result->type = STRING_TYPE;

        // For numeric types, the data is already a string representation
        if (value->type->tag == TypeTag::Int || value->type->tag == TypeTag::Int8 || 
            value->type->tag == TypeTag::Int16 || value->type->tag == TypeTag::Int32 ||
            value->type->tag == TypeTag::Int64 || value->type->tag == TypeTag::Int128 ||
            value->type->tag == TypeTag::UInt || value->type->tag == TypeTag::UInt64 || 
            value->type->tag == TypeTag::UInt8 || value->type->tag == TypeTag::UInt16 || 
            value->type->tag == TypeTag::UInt32 || value->type->tag == TypeTag::Float32 || 
            value->type->tag == TypeTag::Float64) {
            result->data = value->data;
        } else {
            throw std::runtime_error("Unexpected type in numberToString");
        }

        return result;
    }

public:
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

    // --- Persistence Methods ---
    void registerFrame(const std::string& name, const FrameInfo& info) {
        frameRegistry[name] = info;
        
        // Also update the cached frame type with implements info
        auto it = userDefinedTypes.find(name);
        if (it != userDefinedTypes.end()) {
            auto frameTypePtr = std::get_if<FrameType>(&it->second->extra);
            if (frameTypePtr) {
                frameTypePtr->implements = info.implements;
            }
        }
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

    // Built-in error types
    const TypePtr DIVISION_BY_ZERO_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr INDEX_OUT_OF_BOUNDS_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr NULL_REFERENCE_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr TYPE_CONVERSION_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr IO_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr PARSE_ERROR = std::make_shared<Type>(TypeTag::UserDefined);
    const TypePtr NETWORK_ERROR = std::make_shared<Type>(TypeTag::UserDefined);

    // Built-in Error Constants
    const std::string DIVISION_BY_ZERO_ERROR_STR = "DivisionByZeroError";
    const std::string INDEX_OUT_OF_BOUNDS_ERROR_STR = "IndexOutOfBoundsError";
    const std::string KEY_NOT_FOUND_ERROR_STR = "KeyNotFoundError";
    const std::string TYPE_MISMATCH_ERROR_STR = "TypeMismatchError";
    const std::string NULL_POINTER_ERROR_STR = "NullPointerError";
    const std::string IO_ERROR_STR = "IOError";
    const std::string NETWORK_ERROR_STR = "NetworkError";
    const std::string PERMISSION_DENIED_ERROR_STR = "PermissionDeniedError";
    const std::string OVERFLOW_ERROR_STR = "OverflowError";
    const std::string TIMEOUT_ERROR_STR = "TimeoutError";

    TypePtr getType(const std::string& name) {
        // 1. Check contextual scopes (inner to outer)
        for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                if (name == "Shape") {
                    std::cerr << "[DEBUG getType] Shape found in scopeStack, tag=" << static_cast<int>(found->second->tag);
                    if (found->second->tag == TypeTag::Trait) {
                        if (const auto* traitData = std::get_if<TraitType>(&found->second->extra)) {
                            std::cerr << ", traitName=" << traitData->name;
                        } else {
                            std::cerr << ", NO TraitType data!";
                        }
                    }
                    std::cerr << std::endl;
                }
                return found->second;
            }
        }

        // 2. Check user-defined types (includes traits registered in Pass 1)
        auto it = userDefinedTypes.find(name);
        if (it != userDefinedTypes.end()) {
            if (name == "Shape") {
                std::cerr << "[DEBUG getType] Shape found in userDefinedTypes, tag=" << static_cast<int>(it->second->tag);
                if (it->second->tag == TypeTag::Trait) {
                    if (const auto* traitData = std::get_if<TraitType>(&it->second->extra)) {
                        std::cerr << ", traitName=" << traitData->name;
                    } else {
                        std::cerr << ", NO TraitType data!";
                    }
                }
                std::cerr << std::endl;
            }
            return it->second;
        }
        
        // 3. Check persistent registries for frames/traits
        if (frameRegistry.count(name)) return createFrameType(name);
        if (traitRegistry.count(name)) {
            std::cerr << "[DEBUG] getType('" << name << "') found in traitRegistry" << std::endl;
            return getCanonicalType("trait:" + name, [&]() {
                TraitType traitTypeData;
                traitTypeData.name = name;
                return std::make_shared<Type>(TypeTag::Trait, traitTypeData);
            });
        }

        // 4. Check built-in types
        if (name == "bigint" || name == "int" || name == "i64" || name == "u64" || 
            name == "i32" || name == "u32" || name == "i16" || name == "u16" ||
            name == "i8" || name == "u8" || name == "i128" || name == "u128" ||
            name == "uint" || name == "f32" || name == "f64" || name == "float") {
            // Map type names to appropriate types
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
            return INT64_TYPE; // Default fallback
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
        if (name == "function") return FUNCTION_TYPE;  // Generic function type
        if (name == "object") return OBJECT_TYPE;
        if (name == "module") return MODULE_TYPE;
        
        // Check type aliases
        TypePtr aliasType = resolveTypeAlias(name);
        if (aliasType) {
            return aliasType;
        }
        
        return NIL_TYPE;
    }

    ValuePtr createValue(TypePtr type)
    {
        ValuePtr value = std::make_shared<Value>();
        value->type = type;

        switch (type->tag) {
        case TypeTag::Nil:
            value->data = ""; // Empty string represents nil
            break;
        case TypeTag::Bool:
            value->data = false;
            break;
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
            value->data = std::to_string(0);
            break;
        case TypeTag::Float32:
        case TypeTag::Float64:
            value->data = std::to_string(0.0);
            break;
        case TypeTag::String:
            value->data = std::string("");
            break;
        case TypeTag::List:
            value->complexData = ListValue{};
            break;
        case TypeTag::Dict:
            value->complexData = DictValue{};
            break;
        case TypeTag::Tuple:
            // For tuple types, create tuple with default values for each element
            if (const auto *tupleType = std::get_if<TupleType>(&type->extra)) {
                TupleValue tupleValue;
                for (const auto& elementType : tupleType->elementTypes) {
                    tupleValue.elements.push_back(createValue(elementType));
                }
                value->complexData = tupleValue;
            } else {
                // Empty tuple
                value->complexData = TupleValue{};
            }
            break;
        case TypeTag::Enum:
            // For enums, we'll set it to the first value in the enum
            if (const auto *enumType = std::get_if<EnumType>(&type->extra)) {
                if (!enumType->values.empty()) {
                    value->complexData = EnumValue(enumType->values[0], type);
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
                    value->complexData = SumValue{0, createValue(sumType->variants[0])};
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
                    ValuePtr firstVariantValue = createValue(unionType->types[0]);
                    value->data = firstVariantValue->data;
                    value->complexData = firstVariantValue->complexData;
                    value->activeUnionVariant = 0; // Set to first variant
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
                ValuePtr successValue = createValue(errorUnionType->successType);
                value->data = successValue->data;
                value->complexData = successValue->complexData;
            } else {
                throw std::runtime_error("Invalid error union type");
            }
            break;
        case TypeTag::UserDefined:
            value->complexData = UserDefinedValue{};
            break;
        case TypeTag::Function:
            // Functions are typically not instantiated as values
            throw std::runtime_error("Cannot create a value for Function type");
        case TypeTag::Closure:
            // Closures are typically not instantiated as default values
            throw std::runtime_error("Cannot create a default value for Closure type");
        case TypeTag::Any:
            // For Any type, we'll use empty string as a placeholder
            value->data = "";
            break;
        default:
            throw std::runtime_error("Unsupported type tag: "
                                     + std::to_string(static_cast<int>(type->tag)));
        }

        return value;
    }

    bool isCompatible(TypePtr source, TypePtr target) { return canConvert(source, target); }

    // --- Helper Methods ---
    bool isListType(TypePtr type) { return type && type->tag == TypeTag::List; }
    bool isDictType(TypePtr type) { return type && type->tag == TypeTag::Dict; }
    bool isTupleType(TypePtr type) { return type && type->tag == TypeTag::Tuple; }
    bool isStringType(TypePtr type) { return type && type->tag == TypeTag::String; }
    bool isIntegerType(TypePtr type) {
        return type && (type->tag >= TypeTag::Int && type->tag <= TypeTag::UInt128);
    }
    bool isFloatType(TypePtr type) {
        return type && (type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64);
    }
    bool isNumericType(TypePtr type) {
        return isIntegerType(type) || isFloatType(type);
    }

    double stringToNumber(const std::string& str) {
        try {
            return std::stod(str);
        } catch (...) {
            return 0.0;
        }
    }

    TypePtr getCommonType(TypePtr a, TypePtr b)
    {
        if (!a || !b) return nullptr;
        if (a->tag == TypeTag::Any) return b;
        if (b->tag == TypeTag::Any) return a;

        // Unify element types for collections (Mandate 3)
        if (a->tag == TypeTag::List && b->tag == TypeTag::List) {
            auto aList = std::get_if<ListType>(&a->extra);
            auto bList = std::get_if<ListType>(&b->extra);
            if (aList && bList) {
                return createTypedListType(getCommonType(aList->elementType, bList->elementType));
            }
        }

        if (a->tag == TypeTag::Dict && b->tag == TypeTag::Dict) {
            auto aDict = std::get_if<DictType>(&a->extra);
            auto bDict = std::get_if<DictType>(&b->extra);
            if (aDict && bDict) {
                return createTypedDictType(
                    getCommonType(aDict->keyType, bDict->keyType),
                    getCommonType(aDict->valueType, bDict->valueType)
                );
            }
        }

        // Numeric unification rules (Mandate 10)
        bool aIsFloat = (a->tag == TypeTag::Float32 || a->tag == TypeTag::Float64);
        bool bIsFloat = (b->tag == TypeTag::Float32 || b->tag == TypeTag::Float64);
        bool aIsInt = isIntegerType(a);
        bool bIsInt = isIntegerType(b);

        if (aIsFloat || bIsFloat) {
            if ((aIsFloat || aIsInt) && (bIsFloat || bIsInt)) return FLOAT64_TYPE;
        }

        if (canConvert(a, b)) return b;
        if (canConvert(b, a)) return a;

        throw std::runtime_error("Incompatible types: " + a->toString() + " and " + b->toString());
    }

    TypePtr unwrapRefined(TypePtr type) {
        if (!type) return nullptr;
        if (type->tag == TypeTag::Refined) {
            if (auto* refined = std::get_if<RefinedType>(&type->extra)) {
                return unwrapRefined(refined->baseType);
            }
        }
        return type;
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

    // Create error union type (Type? syntax - unified system)
    TypePtr createErrorUnionType(TypePtr successType, const std::vector<std::string>& errorTypeNames = {}, bool isGeneric = true) {
        ErrorUnionType errorUnion;
        errorUnion.successType = successType;
        errorUnion.errorTypes = errorTypeNames;
        errorUnion.isGenericError = isGeneric; // Default to generic for Type? syntax
        
        return std::make_shared<Type>(TypeTag::ErrorUnion, errorUnion);
    }
    
    // Create Type? (unified error system) - syntactic sugar for Result<Type, DefaultError>
    TypePtr createFallibleType(TypePtr successType) {
        return createErrorUnionType(successType, {}, true); // Generic error union
    }
    
    // Check if a type is a fallible type (Type?)
    bool isFallibleType(TypePtr type) {
        return type && type->tag == TypeTag::ErrorUnion;
    }
    
    // Create ok(value) - success value construction
    ValuePtr createOkValue(TypePtr successType, ValuePtr value) {
        if (!value) {
            throw std::runtime_error("Cannot create ok() with null value");
        }
        
        // Validate that the value type is compatible with the expected type
        if (!isCompatible(value->type, successType)) {
            throw std::runtime_error("Value type incompatible with success type");
        }
        
        TypePtr fallibleType = createFallibleType(successType);
        
        // Create a value that represents the success case
        ValuePtr okValue = std::make_shared<Value>();
        okValue->type = fallibleType;
        okValue->data = value->data;
        okValue->complexData = value->complexData;
        
        return okValue;
    }
    
    // Create err() - error value construction (generic error)
    ValuePtr createErrValue(TypePtr successType, const std::string& errorMessage = "") {
        TypePtr fallibleType = createFallibleType(successType);
        
        // Create error value
        ErrorValue errorValue("DefaultError", errorMessage);
        
        ValuePtr errValue = std::make_shared<Value>();
        errValue->type = fallibleType;
        errValue->complexData = errorValue;
        
        return errValue;
    }
    
    // Check if a value is Ok (success)
    bool isOk(ValuePtr value) {
        if (!value || !isFallibleType(value->type)) {
            return false;
        }
        
        // Check if it's not an error
        return !std::holds_alternative<ErrorValue>(value->complexData);
    }
    
    // Check if a value is Err (error)
    bool isErr(ValuePtr value) {
        if (!value || !isFallibleType(value->type)) {
            return false;
        }
        
        // Check if it contains an error
        return std::holds_alternative<ErrorValue>(value->complexData);
    }
    
    // Unwrap Ok value (throws if Err)
    ValuePtr unwrapOk(ValuePtr fallibleValue) {
        if (!isOk(fallibleValue)) {
            throw std::runtime_error("Attempted to unwrap Err as Ok");
        }
        
        // Get the success type from the fallible type
        TypePtr successType = getFallibleSuccessType(fallibleValue->type);
        if (!successType) {
            throw std::runtime_error("Invalid fallible type structure");
        }
        
        // Create a new value with the extracted data and correct type
        ValuePtr extractedValue = std::make_shared<Value>();
        extractedValue->type = successType;
        extractedValue->data = fallibleValue->data;
        extractedValue->complexData = fallibleValue->complexData;
        
        return extractedValue;
    }
    
    // Unwrap Ok value safely (returns nullptr if Err)
    ValuePtr unwrapOkSafe(ValuePtr fallibleValue) {
        if (!isOk(fallibleValue)) {
            return nullptr;
        }
        
        // Get the success type from the fallible type
        TypePtr successType = getFallibleSuccessType(fallibleValue->type);
        if (!successType) {
            return nullptr;
        }
        
        // Create a new value with the extracted data and correct type
        ValuePtr extractedValue = std::make_shared<Value>();
        extractedValue->type = successType;
        extractedValue->data = fallibleValue->data;
        extractedValue->complexData = fallibleValue->complexData;
        
        return extractedValue;
    }
    
    // Get success type from fallible type (the T in T?)
    TypePtr getFallibleSuccessType(TypePtr fallibleType) {
        if (!isFallibleType(fallibleType)) {
            return nullptr;
        }
        
        const auto* errorUnionType = std::get_if<ErrorUnionType>(&fallibleType->extra);
        if (!errorUnionType) {
            return nullptr;
        }
        
        return errorUnionType->successType;
    }
    
    // Create union type
    TypePtr createUnionType(const std::vector<TypePtr>& types, const std::vector<std::string>& names = {}) {
        if (types.empty()) {
            return NIL_TYPE;
        }
        if (types.size() == 1) {
            return types[0];
        }
        
        UnionType unionType;
        unionType.types = types;
        if (names.empty()) {
            for (const auto& t : types) {
                unionType.variantNames.push_back(t->toString());
            }
        } else {
            unionType.variantNames = names;
        }
        
        return std::make_shared<Type>(TypeTag::Union, unionType);
    }

    // Create union value with specific variant
    ValuePtr createUnionValue(TypePtr unionType, size_t variantIndex, ValuePtr variantValue) {
        if (!unionType || unionType->tag != TypeTag::Union) {
            throw std::runtime_error("Invalid union type");
        }
        
        const auto* unionTypeInfo = std::get_if<UnionType>(&unionType->extra);
        if (!unionTypeInfo || variantIndex >= unionTypeInfo->types.size()) {
            throw std::runtime_error("Invalid union variant index");
        }
        
        // Validate that the variant value matches the expected type
        if (variantValue && !isCompatible(variantValue->type, unionTypeInfo->types[variantIndex])) {
            throw std::runtime_error("Union variant value type mismatch");
        }
        
        ValuePtr unionValue = std::make_shared<Value>();
        unionValue->type = unionType;
        unionValue->activeUnionVariant = variantIndex;
        
        if (variantValue) {
            unionValue->data = variantValue->data;
        } else {
            // Create default value for the variant type
            ValuePtr defaultValue = createValue(unionTypeInfo->types[variantIndex]);
            unionValue->data = defaultValue->data;
        }
        
        return unionValue;
    }

    // Get union variant types
    std::vector<TypePtr> getUnionVariantTypes(TypePtr unionType) {
        if (!unionType || unionType->tag != TypeTag::Union) {
            return {};
        }
        
        const auto* unionTypeInfo = std::get_if<UnionType>(&unionType->extra);
        if (!unionTypeInfo) {
            return {};
        }
        
        return unionTypeInfo->types;
    }

    // Check if a type is a union type
    bool isUnionType(TypePtr type) {
        return type && type->tag == TypeTag::Union;
    }

    // Get the number of variants in a union type
    size_t getUnionVariantCount(TypePtr unionType) {
        if (!unionType || unionType->tag != TypeTag::Union) {
            return 0;
        }
        
        const auto* unionTypeInfo = std::get_if<UnionType>(&unionType->extra);
        if (!unionTypeInfo) {
            return 0;
        }
        
        return unionTypeInfo->types.size();
    }

    // Enhanced numeric type inference for literals
    TypePtr inferNumericType(const std::string& literalStr) {
        // Check if it's a floating point number
        if (literalStr.find('.') != std::string::npos || 
            literalStr.find('e') != std::string::npos || 
            literalStr.find('E') != std::string::npos) {
            return FLOAT64_TYPE;
        }
        
        // For integers, determine the appropriate size
        try {
            int64_t intVal = std::stoll(literalStr);
            
            if (intVal >= std::numeric_limits<int8_t>::min() && intVal <= std::numeric_limits<int8_t>::max()) {
                return INT8_TYPE;
            } else if (intVal >= std::numeric_limits<int16_t>::min() && intVal <= std::numeric_limits<int16_t>::max()) {
                return INT16_TYPE;
            } else if (intVal >= std::numeric_limits<int32_t>::min() && intVal <= std::numeric_limits<int32_t>::max()) {
                return INT32_TYPE;
            } else if (intVal >= std::numeric_limits<int64_t>::min() && intVal <= std::numeric_limits<int64_t>::max()) {
                return INT64_TYPE;
            } else {
                // If too large for int64, use Int128
                return INT128_TYPE;
            }
        } catch (const std::exception&) {
            // If parsing fails, treat as string
            return STRING_TYPE;
        }
    }

    // Check if a numeric literal string represents a large integer that should be treated as float
    bool shouldTreatAsFloat(const std::string& literalStr) {
        if (literalStr.find('.') != std::string::npos || 
            literalStr.find('e') != std::string::npos || 
            literalStr.find('E') != std::string::npos) {
            return true; // Already has decimal or scientific notation
        }
        
        try {
            std::stoll(literalStr);
            return false; // Fits in long long, keep as integer
        } catch (const std::out_of_range&) {
            try {
                unsigned long long val = std::stoull(literalStr);
                // If it's larger than max signed long long, treat as float
                return val > static_cast<unsigned long long>(std::numeric_limits<long long>::max());
            } catch (const std::exception&) {
                return true; // Invalid format, treat as float
            }
        } catch (const std::exception&) {
            return false; // Invalid format, but not due to size
        }
    }

    // Option type support - implemented as union type (T | Nil) for null safety
    TypePtr createOptionType(TypePtr valueType) {
        if (!valueType) {
            valueType = ANY_TYPE;
        }
        
        // Option<T> is simply T | Nil - this provides true null safety
        // The value can either be of type T or be nil (absence of value)
        std::vector<TypePtr> optionVariants = {valueType, NIL_TYPE};
        return createUnionType(optionVariants);
    }
    
    // Check if a type is an Option type (T | Nil)
    bool isOptionType(TypePtr type) {
        if (!type || type->tag != TypeTag::Union) {
            return false;
        }
        
        const auto* unionType = std::get_if<UnionType>(&type->extra);
        if (!unionType || unionType->types.size() != 2) {
            return false;
        }
        
        // Check if the union has exactly one non-nil type and nil
        bool hasNil = false;
        bool hasNonNil = false;
        for (const auto& variantType : unionType->types) {
            if (variantType->tag == TypeTag::Nil) {
                hasNil = true;
            } else {
                hasNonNil = true;
            }
        }
        
        return hasNil && hasNonNil;
    }
    
    // Create Some value using existing union infrastructure
    ValuePtr createSome(TypePtr valueType, ValuePtr value) {
        if (!value) {
            throw std::runtime_error("Cannot create Some with null value");
        }
        
        // Validate that the value type is compatible with the expected type
        if (!isCompatible(value->type, valueType)) {
            throw std::runtime_error("Value type incompatible with Option value type");
        }
        
        TypePtr optionType = createOptionType(valueType);
        
        // Use existing union infrastructure - variant 0 is the value type
        return createUnionValue(optionType, 0, value);
    }
    
    // Create None value using existing union infrastructure
    ValuePtr createNone(TypePtr valueType) {
        TypePtr optionType = createOptionType(valueType);
        
        // Create nil value
        ValuePtr nilValue = std::make_shared<Value>();
        nilValue->type = NIL_TYPE;
        nilValue->data = ""; // Empty string represents nil
        
        // Use existing union infrastructure - variant 1 is nil
        return createUnionValue(optionType, 1, nilValue);
    }
    
    // Check if a value is Some (has a non-nil value)
    bool isSome(ValuePtr value) {
        if (!value || !isOptionType(value->type)) {
            return false;
        }
        
        // Some means the value is not nil
        return value->type->tag != TypeTag::Nil;
    }
    
    // Check if a value is None (is nil)
    bool isNone(ValuePtr value) {
        if (!value || !isOptionType(value->type)) {
            return false;
        }
        
        // None means the value is nil
        return value->type->tag == TypeTag::Nil;
    }
    
    // Extract value from Some (throws if None)
    ValuePtr unwrapSome(ValuePtr optionValue) {
        if (!isSome(optionValue)) {
            throw std::runtime_error("Attempted to unwrap None as Some");
        }
        
        // Get the value type from the Option<T>
        TypePtr valueType = getOptionValueType(optionValue->type);
        if (!valueType) {
            throw std::runtime_error("Invalid Option type structure");
        }
        
        // Create a new value with the extracted data and correct type
        ValuePtr extractedValue = std::make_shared<Value>();
        extractedValue->type = valueType;
        extractedValue->data = optionValue->data;
        
        return extractedValue;
    }
    
    // Extract value from Some safely (returns nullptr if None)
    ValuePtr unwrapSomeSafe(ValuePtr optionValue) {
        if (!isSome(optionValue)) {
            return nullptr;
        }
        
        // Get the value type from the Option<T>
        TypePtr valueType = getOptionValueType(optionValue->type);
        if (!valueType) {
            return nullptr;
        }
        
        // Create a new value with the extracted data and correct type
        ValuePtr extractedValue = std::make_shared<Value>();
        extractedValue->type = valueType;
        extractedValue->data = optionValue->data;
        
        return extractedValue;
    }
    
    // Get Option value type (the T in Option<T>)
    TypePtr getOptionValueType(TypePtr optionType) {
        if (!isOptionType(optionType)) {
            return nullptr;
        }
        
        const auto* unionType = std::get_if<UnionType>(&optionType->extra);
        if (!unionType || unionType->types.size() != 2) {
            return nullptr;
        }
        
        // Find the non-nil type in the union (T | Nil)
        for (const auto& variantType : unionType->types) {
            if (variantType->tag != TypeTag::Nil) {
                return variantType;
            }
        }
        
        return nullptr; // Should not happen for valid Option types
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
                              const std::vector<bool>& hasDefaults = {},
                              const std::vector<std::string>& typeParameters = {}) {
        FunctionType functionType(paramNames, paramTypes, returnType, hasDefaults, typeParameters);
        return std::make_shared<Type>(TypeTag::Function, functionType);
    }
    
    // Create tuple type
    TypePtr createTupleType(const std::vector<TypePtr>& elementTypes) {
        TupleType tupleType(elementTypes);
        return std::make_shared<Type>(TypeTag::Tuple, tupleType);
    }
    
    // Create typed list type (e.g., [int], [str])
    TypePtr createTypedListType(TypePtr elementType) {
        if (!elementType) {
            elementType = ANY_TYPE; // Default to any if no element type specified
        }
        
        ListType listType;
        listType.elementType = elementType;
        return std::make_shared<Type>(TypeTag::List, listType);
    }
    
    // Create typed dictionary type (e.g., {str: int}, {int: float})
    TypePtr createTypedDictType(TypePtr keyType, TypePtr valueType) {
        if (!keyType) {
            keyType = STRING_TYPE; // Default key type to string
        }
        if (!valueType) {
            valueType = ANY_TYPE; // Default value type to any
        }
        
        DictType dictType;
        dictType.keyType = keyType;
        dictType.valueType = valueType;
        return std::make_shared<Type>(TypeTag::Dict, dictType);
    }
    
    // Create frame type (for OOP frames)
    TypePtr createFrameType(const std::string& frameName) {
        // Check if frame type already exists
        auto it = userDefinedTypes.find(frameName);
        if (it != userDefinedTypes.end()) {
            return it->second;
        }
        
        // Create a FrameType with the frame name
        FrameType frameTypeData;
        frameTypeData.name = frameName;
        
        // Populate implements from frame registry if available
        auto frameInfoIt = frameRegistry.find(frameName);
        if (frameInfoIt != frameRegistry.end()) {
            frameTypeData.implements = frameInfoIt->second.implements;
        }
        
        // Create a frame type with the Frame tag and FrameType data
        TypePtr frameType = std::make_shared<Type>(TypeTag::Frame, frameTypeData);
        
        // Store the frame name in the user-defined types map
        userDefinedTypes[frameName] = frameType;
        
        return frameType;
    }
    
    // Create structural type
    TypePtr createStructuralType(const std::vector<std::pair<std::string, TypePtr>>& fields, bool hasRest = false) {
        StructuralType structType;
        structType.fields = fields;
        structType.hasRest = hasRest;
        return std::make_shared<Type>(TypeTag::Structural, structType);
    }
    
    // Create function type from AST function type annotation (implemented below)
    TypePtr createFunctionTypeFromAST(const LM::Frontend::AST::FunctionTypeAnnotation& funcTypeAnnotation);
    
    // Function type inference for lambda expressions (implemented below)
    TypePtr inferFunctionType(const LM::Frontend::AST::LambdaExpr& lambda);
    
    // Function type compatibility checking
    bool areFunctionTypesCompatible(TypePtr fromFunc, TypePtr toFunc) {
        if (!fromFunc || !toFunc || 
            fromFunc->tag != TypeTag::Function || 
            toFunc->tag != TypeTag::Function) {
            return false;
        }
        
        auto* fromFuncType = std::get_if<FunctionType>(&fromFunc->extra);
        auto* toFuncType = std::get_if<FunctionType>(&toFunc->extra);
        
        if (fromFuncType && toFuncType) {
            return fromFuncType->isCompatibleWith(*toFuncType);
        }
        return true; // Generic function types
    }
    
    // Container type validation methods
    bool validateContainerHomogeneity(TypePtr containerType, const std::vector<ValuePtr>& elements) {
        if (!containerType || elements.empty()) {
            return true; // Empty containers are valid
        }
        
        if (containerType->tag == TypeTag::List) {
            if (auto* listType = std::get_if<ListType>(&containerType->extra)) {
                for (const auto& element : elements) {
                    if (!isCompatible(element->type, listType->elementType)) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        return true; // Other container types handled elsewhere
    }
    
    bool validateDictHomogeneity(TypePtr dictType, const std::vector<std::pair<ValuePtr, ValuePtr>>& entries) {
        if (!dictType || entries.empty()) {
            return true; // Empty dictionaries are valid
        }
        
        if (dictType->tag == TypeTag::Dict) {
            if (auto* dictTypeInfo = std::get_if<DictType>(&dictType->extra)) {
                for (const auto& [key, value] : entries) {
                    if (!isCompatible(key->type, dictTypeInfo->keyType) || 
                        !isCompatible(value->type, dictTypeInfo->valueType)) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        return true;
    }
    
    // Get container element type for type inference
    TypePtr getContainerElementType(TypePtr containerType) {
        if (!containerType) {
            return ANY_TYPE;
        }
        
        if (containerType->tag == TypeTag::List) {
            if (auto* listType = std::get_if<ListType>(&containerType->extra)) {
                return listType->elementType;
            }
        }
        
        return ANY_TYPE;
    }
    
    // Get dictionary key and value types
    std::pair<TypePtr, TypePtr> getDictTypes(TypePtr dictType) {
        if (!dictType || dictType->tag != TypeTag::Dict) {
            return {STRING_TYPE, ANY_TYPE}; // Default types
        }
        
        if (auto* dictTypeInfo = std::get_if<DictType>(&dictType->extra)) {
            return {dictTypeInfo->keyType, dictTypeInfo->valueType};
        }
        return {STRING_TYPE, ANY_TYPE};
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
        case TypeTag::Int128:
        case TypeTag::UInt:
        case TypeTag::UInt8:
        case TypeTag::UInt16:
        case TypeTag::UInt32:
        case TypeTag::UInt64:
        case TypeTag::UInt128:
        case TypeTag::Float32:
        case TypeTag::Float64:
        case TypeTag::Bool:
        case TypeTag::String:
        case TypeTag::Nil:
            return true; // Simple types match by tag alone

        case TypeTag::List: {
            if (const auto* listType = std::get_if<ListType>(&expectedType->extra)) {
                if (const auto *listValue = std::get_if<ListValue>(&value->complexData)) {
                    for (const auto &element : listValue->elements) {
                        if (!checkType(element, listType->elementType)) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return true;
        }

        case TypeTag::Dict: {
            if (const auto* dictType = std::get_if<DictType>(&expectedType->extra)) {
                if (const auto *dictValue = std::get_if<DictValue>(&value->complexData)) {
                    for (const auto &[key, val] : dictValue->elements) {
                        if (!checkType(key, dictType->keyType) || !checkType(val, dictType->valueType)) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return true;
        }

        case TypeTag::Tuple: {
            if (const auto* tupleType = std::get_if<TupleType>(&expectedType->extra)) {
                if (const auto *tupleValue = std::get_if<TupleValue>(&value->complexData)) {
                    // Check that tuple has correct number of elements
                    if (tupleValue->elements.size() != tupleType->elementTypes.size()) {
                        return false;
                    }
                    
                    // Check each element type
                    for (size_t i = 0; i < tupleValue->elements.size(); ++i) {
                        if (!checkType(tupleValue->elements[i], tupleType->elementTypes[i])) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return true;
        }

        case TypeTag::Sum: {
            if (const auto* sumType = std::get_if<SumType>(&expectedType->extra)) {
                if (const auto *sumValue = std::get_if<SumValue>(&value->complexData)) {
                    if (sumValue->activeVariant >= sumType->variants.size()) {
                        return false;
                    }
                    const auto &variantType = sumType->variants[sumValue->activeVariant];
                    return checkType(sumValue->value, variantType);
                }
            }
            return true;
        }

       case TypeTag::Enum: {
            if (const auto *enumType = std::get_if<EnumType>(&expectedType->extra)) {
                if (!enumType->values.empty()) {
                    value->complexData = EnumValue(enumType->values[0], expectedType);
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
            return std::holds_alternative<ClosureValue>(value->complexData);

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
        case TypeTag::Object:
        case TypeTag::Module:
        case TypeTag::Frame:
        case TypeTag::Trait:
        case TypeTag::Refined: {
            if (const auto* refined = std::get_if<RefinedType>(&expectedType->extra)) {
                // Check if value matches the base type
                // In a full implementation, we'd also evaluate the condition
                return checkType(value, refined->baseType);
            }
            return false;
        }

        case TypeTag::Structural: {
            if (const auto* structType = std::get_if<StructuralType>(&expectedType->extra)) {
                // Basic structural check - ensure it's a UserDefinedValue or similar
                // that contains fields matching the structural type's fields
                return std::holds_alternative<UserDefinedValue>(value->complexData);
            }
            return false;
        }

        case TypeTag::TraitObject:
            // TODO: implement checks for these
            return false;
        }

        // Handle Union type separately, as it can match multiple types
        if (expectedType->tag == TypeTag::Union) {
            const auto* unionPtr = std::get_if<UnionType>(&expectedType->extra);
            if (unionPtr) {
                for (const auto &type : unionPtr->types) {
                    if (checkType(value, type)) {
                        return true;
                    }
                }
            }
            return false;
        }

        // Handle ErrorUnion type separately
        if (expectedType->tag == TypeTag::ErrorUnion) {
            const auto* errorUnionPtr = std::get_if<ErrorUnionType>(&expectedType->extra);
            if (!errorUnionPtr) return false;
            const auto& errorUnionType = *errorUnionPtr;
            
            // Check if value is an error
            if (const auto *errorValue = std::get_if<ErrorValue>(&value->complexData)) {
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

        // Handle primitive types using the data string member
        switch (value->type->tag) {
        case TypeTag::Int:
        case TypeTag::Int64:
        case TypeTag::Int8:
        case TypeTag::Int16:
        case TypeTag::Int32: {
            int64_t sourceValue = ValueConverters::toInt64(value->data).value_or(0);
            switch (targetType->tag) {
            case TypeTag::Int:
            case TypeTag::Int64:
                result->data = std::to_string(sourceValue);
                break;
            case TypeTag::Int8:
                result->data = std::to_string(static_cast<int8_t>(sourceValue));
                break;
            case TypeTag::Int16:
                result->data = std::to_string(static_cast<int16_t>(sourceValue));
                break;
            case TypeTag::Int32:
                result->data = std::to_string(static_cast<int32_t>(sourceValue));
                break;
            case TypeTag::UInt:
            case TypeTag::UInt64:
                result->data = std::to_string(static_cast<uint64_t>(sourceValue));
                break;
            case TypeTag::UInt8:
                result->data = std::to_string(static_cast<uint8_t>(sourceValue));
                break;
            case TypeTag::UInt16:
                result->data = std::to_string(static_cast<uint16_t>(sourceValue));
                break;
            case TypeTag::UInt32:
                result->data = std::to_string(static_cast<uint32_t>(sourceValue));
                break;
            case TypeTag::Float32:
                result->data = std::to_string(static_cast<float>(sourceValue));
                break;
            case TypeTag::Float64:
                result->data = std::to_string(static_cast<double>(sourceValue));
                break;
            case TypeTag::String:
                result->data = std::to_string(sourceValue);
                break;
            default:
                throw std::runtime_error("Unsupported conversion from int to "
                                         + targetType->toString());
            }
            break;
        }
        case TypeTag::UInt:
        case TypeTag::UInt64:
        case TypeTag::UInt8:
        case TypeTag::UInt16:
        case TypeTag::UInt32: {
            uint64_t sourceValue = static_cast<uint64_t>(ValueConverters::toInt64(value->data).value_or(0));
            switch (targetType->tag) {
            case TypeTag::Int:
            case TypeTag::Int64:
                result->data = std::to_string(static_cast<int64_t>(sourceValue));
                break;
            case TypeTag::Int8:
                result->data = std::to_string(static_cast<int8_t>(sourceValue));
                break;
            case TypeTag::Int16:
                result->data = std::to_string(static_cast<int16_t>(sourceValue));
                break;
            case TypeTag::Int32:
                result->data = std::to_string(static_cast<int32_t>(sourceValue));
                break;
            case TypeTag::UInt:
            case TypeTag::UInt64:
                result->data = std::to_string(sourceValue);
                break;
            case TypeTag::UInt8:
                result->data = std::to_string(static_cast<uint8_t>(sourceValue));
                break;
            case TypeTag::UInt16:
                result->data = std::to_string(static_cast<uint16_t>(sourceValue));
                break;
            case TypeTag::UInt32:
                result->data = std::to_string(static_cast<uint32_t>(sourceValue));
                break;
            case TypeTag::Float32:
                result->data = std::to_string(static_cast<float>(sourceValue));
                break;
            case TypeTag::Float64:
                result->data = std::to_string(static_cast<double>(sourceValue));
                break;
            case TypeTag::String:
                result->data = std::to_string(sourceValue);
                break;
            default:
                throw std::runtime_error("Unsupported conversion from uint to "
                                         + targetType->toString());
            }
            break;
        }
        case TypeTag::Float32:
        case TypeTag::Float64: {
            double sourceValue = ValueConverters::toDouble(value->data).value_or(0.0);
            switch (targetType->tag) {
            case TypeTag::Int:
            case TypeTag::Int64:
                result->data = std::to_string(static_cast<int64_t>(sourceValue));
                break;
            case TypeTag::Int8:
                result->data = std::to_string(static_cast<int8_t>(sourceValue));
                break;
            case TypeTag::Int16:
                result->data = std::to_string(static_cast<int16_t>(sourceValue));
                break;
            case TypeTag::Int32:
                result->data = std::to_string(static_cast<int32_t>(sourceValue));
                break;
            case TypeTag::UInt:
            case TypeTag::UInt64:
                result->data = std::to_string(static_cast<uint64_t>(sourceValue));
                break;
            case TypeTag::UInt8:
                result->data = std::to_string(static_cast<uint8_t>(sourceValue));
                break;
            case TypeTag::UInt16:
                result->data = std::to_string(static_cast<uint16_t>(sourceValue));
                break;
            case TypeTag::UInt32:
                result->data = std::to_string(static_cast<uint32_t>(sourceValue));
                break;
            case TypeTag::Float32:
                result->data = std::to_string(static_cast<float>(sourceValue));
                break;
            case TypeTag::Float64:
                result->data = std::to_string(sourceValue);
                break;
            case TypeTag::String:
                result->data = std::to_string(sourceValue);
                break;
            default:
                throw std::runtime_error("Unsupported conversion from float to "
                                         + targetType->toString());
            }
            break;
        }
        case TypeTag::String: {
            const std::string& sourceValue = value->data;
            switch (targetType->tag) {
            case TypeTag::String:
                result->data = sourceValue;
                break;
            case TypeTag::Int:
            case TypeTag::Int64:
                result->data = std::to_string(std::stoll(sourceValue));
                break;
            case TypeTag::Int8:
                result->data = std::to_string(static_cast<int8_t>(std::stoll(sourceValue)));
                break;
            case TypeTag::Int16:
                result->data = std::to_string(static_cast<int16_t>(std::stoll(sourceValue)));
                break;
            case TypeTag::Int32:
                result->data = std::to_string(std::stoll(sourceValue));
                break;
            case TypeTag::UInt:
            case TypeTag::UInt64:
                result->data = std::to_string(std::stoull(sourceValue));
                break;
            case TypeTag::UInt8:
                result->data = std::to_string(static_cast<uint8_t>(std::stoull(sourceValue)));
                break;
            case TypeTag::UInt16:
                result->data = std::to_string(static_cast<uint16_t>(std::stoull(sourceValue)));
                break;
            case TypeTag::UInt32:
                result->data = std::to_string(std::stoull(sourceValue));
                break;
            case TypeTag::Float32:
                result->data = std::to_string(std::stof(sourceValue));
                break;
            case TypeTag::Float64:
                result->data = std::to_string(std::stod(sourceValue));
                break;
            default:
                throw std::runtime_error("Unsupported conversion from string to "
                                         + targetType->toString());
            }
            break;
        }
        case TypeTag::Bool: {
            bool sourceValue = ValueConverters::toBool(value->data);
            switch (targetType->tag) {
            case TypeTag::Bool:
                result->data = sourceValue;
                break;
            case TypeTag::Int:
            case TypeTag::Int64:
                result->data = std::to_string(sourceValue ? 1LL : 0LL);
                break;
            case TypeTag::Int8:
                result->data = std::to_string(sourceValue ? int8_t(1) : int8_t(0));
                break;
            case TypeTag::Int16:
                result->data = std::to_string(sourceValue ? int16_t(1) : int16_t(0));
                break;
            case TypeTag::Int32:
                result->data = std::to_string(sourceValue ? 1 : 0);
                break;
            case TypeTag::UInt:
            case TypeTag::UInt64:
                result->data = std::to_string(sourceValue ? 1ULL : 0ULL);
                break;
            case TypeTag::UInt8:
                result->data = std::to_string(sourceValue ? uint8_t(1) : uint8_t(0));
                break;
            case TypeTag::UInt16:
                result->data = std::to_string(sourceValue ? uint16_t(1) : uint16_t(0));
                break;
            case TypeTag::UInt32:
                result->data = std::to_string(sourceValue ? 1ULL : 0ULL);
                break;
            case TypeTag::Float32:
                result->data = std::to_string(sourceValue ? 1.0f : 0.0f);
                break;
            case TypeTag::Float64:
                result->data = std::to_string(sourceValue ? 1.0 : 0.0);
                break;
            case TypeTag::String:
                result->data = sourceValue ? "true" : "false";
                break;
            default:
                throw std::runtime_error("Unsupported conversion from bool to "
                                         + targetType->toString());
            }
            break;
        }
        case TypeTag::Nil: {
            switch (targetType->tag) {
            case TypeTag::Nil:
                result->data = ""; // Empty string represents nil
                break;
            case TypeTag::Bool:
                result->data = false;
                break;
            case TypeTag::Int:
            case TypeTag::Int64:
                result->data = std::to_string(0);
                break;
            case TypeTag::Int8:
                result->data = std::to_string(int8_t(0));
                break;
            case TypeTag::Int16:
                result->data = std::to_string(int16_t(0));
                break;
            case TypeTag::Int32:
                result->data = std::to_string(0);
                break;
            case TypeTag::UInt:
            case TypeTag::UInt64:
                result->data = std::to_string(0U);
                break;
            case TypeTag::UInt8:
                result->data = std::to_string(uint8_t(0));
                break;
            case TypeTag::UInt16:
                result->data = std::to_string(uint16_t(0));
                break;
            case TypeTag::UInt32:
                result->data = std::to_string(0U);
                break;
            case TypeTag::Float32:
                result->data = std::to_string(0.0f);
                break;
            case TypeTag::Float64:
                result->data = std::to_string(0.0);
                break;
            case TypeTag::String:
                result->data = "nil";
                break;
            default:
                throw std::runtime_error("Unsupported conversion from nil to "
                                         + targetType->toString());
            }
            break;
        }
        default:
            // Handle complex types using complexData
            result->complexData = value->complexData;
            break;
        }

        return result;
    }



private:
    // Helper method to convert AST::TypeAnnotation to TypePtr (implemented in function_types.cpp)
    TypePtr convertASTTypeToTypePtr(std::shared_ptr<LM::Frontend::AST::TypeAnnotation> astType);


};