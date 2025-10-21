#include "types.hh"
#include "../frontend/ast.hh"

// Create function type from AST function type annotation
TypePtr TypeSystem::createFunctionTypeFromAST(const AST::FunctionTypeAnnotation& funcTypeAnnotation) {
    std::vector<std::string> paramNames;
    std::vector<TypePtr> paramTypes;
    std::vector<bool> hasDefaults;
    
    // Convert AST parameters to TypePtr
    for (const auto& param : funcTypeAnnotation.parameters) {
        paramNames.push_back(param.name);
        hasDefaults.push_back(param.hasDefaultValue);
        
        // Convert AST::TypeAnnotation to TypePtr
        if (param.type) {
            TypePtr paramType = convertASTTypeToTypePtr(param.type);
            paramTypes.push_back(paramType);
        } else {
            paramTypes.push_back(ANY_TYPE); // Default to any if no type specified
        }
    }
    
    // Convert return type
    TypePtr returnType = ANY_TYPE; // Default return type
    if (funcTypeAnnotation.returnType) {
        returnType = convertASTTypeToTypePtr(funcTypeAnnotation.returnType);
    }
    
    return createFunctionType(paramNames, paramTypes, returnType, hasDefaults);
}

// Function type inference for lambda expressions
TypePtr TypeSystem::inferFunctionType(const AST::LambdaExpr& lambda) {
    std::vector<std::string> paramNames;
    std::vector<TypePtr> paramTypes;
    std::vector<bool> hasDefaults;
    
    // Extract parameter information from lambda
    for (const auto& param : lambda.params) {
        paramNames.push_back(param.first);
        hasDefaults.push_back(false); // Lambdas don't have default parameters yet
        
        if (param.second) {
            TypePtr paramType = convertASTTypeToTypePtr(param.second);
            paramTypes.push_back(paramType);
        } else {
            paramTypes.push_back(ANY_TYPE); // Infer as any if no type specified
        }
    }
    
    // Infer return type
    TypePtr returnType = ANY_TYPE; // Default return type
    if (lambda.returnType.has_value()) {
        returnType = convertASTTypeToTypePtr(lambda.returnType.value());
    }
    
    return createFunctionType(paramNames, paramTypes, returnType, hasDefaults);
}

// Helper method to convert AST::TypeAnnotation to TypePtr
TypePtr TypeSystem::convertASTTypeToTypePtr(std::shared_ptr<AST::TypeAnnotation> astType) {
    if (!astType) {
        return ANY_TYPE;
    }
    
    // Handle primitive types
    if (astType->isPrimitive) {
        if (astType->typeName == "int") return INT_TYPE;
        if (astType->typeName == "i8") return INT8_TYPE;
        if (astType->typeName == "i16") return INT16_TYPE;
        if (astType->typeName == "i32") return INT32_TYPE;
        if (astType->typeName == "i64") return INT64_TYPE;
        if (astType->typeName == "uint") return UINT_TYPE;
        if (astType->typeName == "u8") return UINT8_TYPE;
        if (astType->typeName == "u16") return UINT16_TYPE;
        if (astType->typeName == "u32") return UINT32_TYPE;
        if (astType->typeName == "u64") return UINT64_TYPE;
        if (astType->typeName == "float" || astType->typeName == "f64") return FLOAT64_TYPE;
        if (astType->typeName == "f32") return FLOAT32_TYPE;
        if (astType->typeName == "str" || astType->typeName == "string") return STRING_TYPE;
        if (astType->typeName == "bool") return BOOL_TYPE;
        if (astType->typeName == "nil") return NIL_TYPE;
        if (astType->typeName == "any") return ANY_TYPE;
    }
    
    // Handle function types
    if (astType->isFunction) {
        if (astType->functionParameters.empty() && astType->functionParams.empty()) {
            return FUNCTION_TYPE; // Generic function type
        }
        
        // Create specific function type
        std::vector<TypePtr> paramTypes;
        
        // Use new parameter format if available
        if (!astType->functionParameters.empty()) {
            for (const auto& param : astType->functionParameters) {
                if (param.type) {
                    paramTypes.push_back(convertASTTypeToTypePtr(param.type));
                } else {
                    paramTypes.push_back(ANY_TYPE);
                }
            }
        } else {
            // Use legacy parameter format
            for (const auto& param : astType->functionParams) {
                paramTypes.push_back(convertASTTypeToTypePtr(param));
            }
        }
        
        TypePtr returnType = ANY_TYPE;
        if (astType->returnType) {
            returnType = convertASTTypeToTypePtr(astType->returnType);
        }
        
        return createFunctionType(paramTypes, returnType);
    }
    
    // Handle list types
    if (astType->isList) {
        TypePtr elementType = ANY_TYPE;
        if (astType->elementType) {
            elementType = convertASTTypeToTypePtr(astType->elementType);
        }
        
        ListType listType;
        listType.elementType = elementType;
        return std::make_shared<Type>(TypeTag::List, listType);
    }
    
    // Handle dictionary types
    if (astType->isDict) {
        TypePtr keyType = STRING_TYPE; // Default key type
        TypePtr valueType = ANY_TYPE; // Default value type
        
        if (astType->keyType) {
            keyType = convertASTTypeToTypePtr(astType->keyType);
        }
        if (astType->valueType) {
            valueType = convertASTTypeToTypePtr(astType->valueType);
        }
        
        DictType dictType;
        dictType.keyType = keyType;
        dictType.valueType = valueType;
        return std::make_shared<Type>(TypeTag::Dict, dictType);
    }
    
    // Handle union types
    if (astType->isUnion) {
        std::vector<TypePtr> unionTypes;
        for (const auto& unionMember : astType->unionTypes) {
            unionTypes.push_back(convertASTTypeToTypePtr(unionMember));
        }
        
        UnionType unionType;
        unionType.types = unionTypes;
        return std::make_shared<Type>(TypeTag::Union, unionType);
    }
    
    // Handle error union types
    if (astType->isFallible) {
        // Get the base type without the fallible flag
        TypePtr successType = getType(astType->typeName);
        return createErrorUnionType(successType, astType->errorTypes, astType->errorTypes.empty());
    }
    
    // Handle optional types
    if (astType->isOptional) {
        // Create Option<T> type
        TypePtr baseType = getType(astType->typeName);
        std::vector<TypePtr> optionTypes = {baseType, NIL_TYPE};
        
        UnionType optionType;
        optionType.types = optionTypes;
        return std::make_shared<Type>(TypeTag::Union, optionType);
    }
    
    // Handle user-defined types
    if (astType->isUserDefined) {
        return getType(astType->typeName);
    }
    
    // Default case - try to resolve by name
    return getType(astType->typeName);
}