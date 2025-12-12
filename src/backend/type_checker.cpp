#include "type_checker.hh"
#include "types.hh"
#include "../common/debugger.hh"
#include "../frontend/scanner.hh"
#include "../frontend/parser.hh"
#include "../common/big_int.hh"
#include <algorithm>
#include <sstream>
#include <string>
#include <variant>
#include <fstream>
#include <set>
#include <cmath>
#include <limits>

void TypeChecker::addError(const std::string& message, int line, int column, const std::string& context) {
    errors.emplace_back(message, line, column, context);
    
    // Don't report immediately - let backend.cpp handle error display with proper context
}

void TypeChecker::addError(const std::string& message, int line, int column, const std::string& context, const std::string& lexeme, const std::string& expectedValue) {
    // Enhanced error with lexeme and expected value information
    std::string enhancedMessage = message;
    if (!lexeme.empty()) {
        enhancedMessage += " (at '" + lexeme + "')";
    }
    if (!expectedValue.empty()) {
        enhancedMessage += " - expected: " + expectedValue;
    }
    errors.emplace_back(enhancedMessage, line, column, context);
    
    // Don't report immediately - let backend.cpp handle error display with proper context
}

// No-op. The SymbolTable class now handles this.
void TypeChecker::enterScope() {
    symbolTable.enterScope();
}

void TypeChecker::exitScope() {
    symbolTable.exitScope();
}

std::vector<TypeCheckError> TypeChecker::checkProgram(const std::shared_ptr<AST::Program>& program) {
    errors.clear();
    
    // Extract visibility information from AST
    extractModuleVisibility(program);
    
    // First pass: collect type aliases and function signatures
    for (const auto& stmt : program->statements) {
        if (auto typeDecl = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) {
            // Register type alias
            TypePtr aliasType = resolveTypeAnnotation(typeDecl->type);
            if (aliasType) {
                typeSystem.registerTypeAlias(typeDecl->name, aliasType);
            } else {
                addError("Invalid type in type alias '" + typeDecl->name + "'", typeDecl->line);
            }
        } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            // Extract function signature information
            std::vector<TypePtr> paramTypes;
            std::vector<bool> optionalParams;
            std::vector<bool> hasDefaultValues;
            
            // Process required parameters
            for (const auto& param : funcDecl->params) {
                if (param.second) {
                    // Convert TypeAnnotation to TypePtr
                    TypePtr paramType = resolveTypeAnnotation(param.second);
                    paramTypes.push_back(paramType);
                } else {
                    paramTypes.push_back(typeSystem.ANY_TYPE);
                }
                optionalParams.push_back(false);  // Required parameters are not optional
                hasDefaultValues.push_back(false); // Required parameters don't have defaults
            }
            
            // Process optional parameters
            for (const auto& optParam : funcDecl->optionalParams) {
                if (optParam.second.first) {
                    // Convert TypeAnnotation to TypePtr
                    TypePtr paramType = resolveTypeAnnotation(optParam.second.first);
                    paramTypes.push_back(paramType);
                } else {
                    paramTypes.push_back(typeSystem.ANY_TYPE);
                }
                optionalParams.push_back(true);  // These are optional parameters
                hasDefaultValues.push_back(optParam.second.second != nullptr); // Has default if expression exists
            }
            
            TypePtr returnType = typeSystem.NIL_TYPE;
            bool canFail = funcDecl->canFail || funcDecl->throws;
            std::vector<std::string> errorTypes = funcDecl->declaredErrorTypes;
            
            if (funcDecl->returnType && *funcDecl->returnType) {
                returnType = resolveTypeAnnotation(*funcDecl->returnType);
                
                // Special case: if return type is generic "function", keep it generic
                if ((*funcDecl->returnType)->typeName == "function" && !(*funcDecl->returnType)->isFunction) {
                    returnType = typeSystem.FUNCTION_TYPE;
                }
                
                // Check if return type is an error union
                if (returnType->tag == TypeTag::ErrorUnion) {
                    canFail = true;
                    auto errorUnion = std::get<ErrorUnionType>(returnType->extra);
                    
                    // If no explicit error types declared, use those from return type
                    if (errorTypes.empty()) {
                        errorTypes = errorUnion.errorTypes;
                    }
                }
            }
            
            // Register function signature in symbol table
            FunctionSignature signature(funcDecl->name, paramTypes, returnType, canFail, errorTypes, funcDecl->line, optionalParams, hasDefaultValues);
            symbolTable.addFunction(funcDecl->name, signature);
        }
    }
    
    // Second pass: type check all statements
    for (const auto& stmt : program->statements) {
        checkStatement(stmt);
    }
    
    return errors;
}

TypePtr TypeChecker::resolveTypeAnnotation(const std::shared_ptr<AST::TypeAnnotation>& annotation) {
    if (!annotation) {
        return typeSystem.NIL_TYPE;
    }
    

    
    // Handle function types
    if (annotation->isFunction) {
        // Check if this is a FunctionTypeAnnotation with specific signature
        if (auto funcTypeAnnotation = std::dynamic_pointer_cast<AST::FunctionTypeAnnotation>(annotation)) {
            return typeSystem.createFunctionTypeFromAST(*funcTypeAnnotation);
        }
        
        // Check if this is a generic function type (no parameters or return type specified)
        if (annotation->functionParameters.empty() && annotation->functionParams.empty() && 
            !annotation->returnType && annotation->typeName == "function") {
            return typeSystem.FUNCTION_TYPE;
        }
        
        // Handle legacy function type annotation
        std::vector<TypePtr> paramTypes;
        std::vector<std::string> paramNames;
        
        // Use new parameter format if available
        if (!annotation->functionParameters.empty()) {
            for (const auto& param : annotation->functionParameters) {
                paramNames.push_back(param.name);
                if (param.type) {
                    paramTypes.push_back(resolveTypeAnnotation(param.type));
                } else {
                    paramTypes.push_back(typeSystem.ANY_TYPE);
                }
            }
        } else {
            // Use legacy parameter format
            for (const auto& param : annotation->functionParams) {
                paramTypes.push_back(resolveTypeAnnotation(param));
            }
        }
        
        TypePtr returnType = typeSystem.NIL_TYPE;
        if (annotation->returnType) {
            returnType = resolveTypeAnnotation(annotation->returnType);
        }
        
        if (!paramNames.empty()) {
            return typeSystem.createFunctionType(paramNames, paramTypes, returnType);
        } else {
            return typeSystem.createFunctionType(paramTypes, returnType);
        }
    }
    
    // Handle union types (Type1 | Type2 | ...)
    if (!annotation->unionTypes.empty()) {
        std::vector<TypePtr> unionTypes;
        for (const auto& unionType : annotation->unionTypes) {
            TypePtr resolvedType = resolveTypeAnnotation(unionType);
            if (resolvedType) {
                unionTypes.push_back(resolvedType);
            }
        }
        
        if (!unionTypes.empty()) {
            return typeSystem.createUnionType(unionTypes);
        }
    }
    
    // Handle basic types
    TypePtr baseType = typeSystem.getType(annotation->typeName);
    
    // If baseType is NIL_TYPE, it might be a type alias that wasn't found
    // This can happen during the first pass before all type aliases are registered
    if (baseType == typeSystem.NIL_TYPE && annotation->typeName != "nil") {
        // Try to resolve as type alias
        TypePtr aliasType = typeSystem.resolveTypeAlias(annotation->typeName);
        if (aliasType) {
            baseType = aliasType;
        }
    }
    
    // Special handling for generic function type
    if (annotation->typeName == "function" && !annotation->isFunction) {
        return typeSystem.FUNCTION_TYPE;
    }
    
    // Handle optional types (Type?) - these are for null safety
    if (annotation->isOptional) {
        // Optional types are error unions with no specific error types (generic)
        return typeSystem.createErrorUnionType(baseType, {}, true);
    }
    
    // Handle error union types (Type?Error1,Error2) - these are for error handling
    if (annotation->isFallible) {
        std::vector<std::string> errorTypeNames = annotation->errorTypes;
        bool isGeneric = errorTypeNames.empty();
        
        return typeSystem.createErrorUnionType(baseType, errorTypeNames, isGeneric);
    }
    
    // Handle typed list types (e.g., [int], [str])
    if (annotation->isList && annotation->elementType) {
        TypePtr elementType = resolveTypeAnnotation(annotation->elementType);
        return typeSystem.createTypedListType(elementType);
    }
    
    // Handle typed dictionary types (e.g., {str: int}, {int: float})
    if (annotation->isDict && annotation->keyType && annotation->valueType) {
        TypePtr keyType = resolveTypeAnnotation(annotation->keyType);
        TypePtr valueType = resolveTypeAnnotation(annotation->valueType);
        return typeSystem.createTypedDictType(keyType, valueType);
    }
    
    // Handle tuple types (e.g., (int, str, bool))
    if (annotation->isTuple && !annotation->tupleTypes.empty()) {
        std::vector<TypePtr> elementTypes;
        for (const auto& tupleType : annotation->tupleTypes) {
            TypePtr resolvedType = resolveTypeAnnotation(tupleType);
            if (resolvedType) {
                elementTypes.push_back(resolvedType);
            }
        }
        
        if (!elementTypes.empty()) {
            return typeSystem.createTupleType(elementTypes);
        }
    }
    
    return baseType;
}

void TypeChecker::checkStatement(const std::shared_ptr<AST::Statement>& stmt) {
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        // Store top-level variable declaration for visibility checking
        topLevelVariables[varDecl->name] = varDecl;
        
        TypePtr varType = typeSystem.ANY_TYPE;
        
        if (varDecl->type && *varDecl->type) {
            varType = resolveTypeAnnotation(*varDecl->type);
            
        }
        
        if (varDecl->initializer) {
            TypePtr initType = checkExpression(varDecl->initializer, varType);
            
            // Check for unhandled fallible expressions in variable declarations
            if (requiresErrorHandling(initType)) {
                // Check if this is a function call that returns an error union
                if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(varDecl->initializer)) {
                    if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
                        FunctionSignature* signature = symbolTable.findFunction(varExpr->name);
                        if (signature && signature->canFail) {
                            std::string errorTypesList = joinErrorTypes(signature->errorTypes);
                            addError("Unhandled fallible function call to '" + signature->name + 
                                    "' in variable declaration '" + varDecl->name + 
                                    "' that can return errors: [" + errorTypesList + 
                                    "]. Must use '?' operator for error propagation or 'match' statement for error handling", 
                                    varDecl->line);
                        } else {
                            addError("Unhandled fallible expression in variable declaration '" + varDecl->name + 
                                    "': must use '?' operator or match statement", 
                                    varDecl->line);
                        }
                    }
                } else {
                    addError("Unhandled fallible expression in variable declaration '" + varDecl->name + 
                            "': must use '?' operator or match statement", 
                            varDecl->line);
                }
            }
            
            // Enhanced type compatibility checking for union types, error unions and function types
            if (varType != typeSystem.ANY_TYPE && !typeSystem.isCompatible(initType, varType)) {
                // Provide more specific error messages for union types
                if (isUnionType(varType) || isUnionType(initType)) {
                    std::string varTypeStr = varType->toString();
                    std::string initTypeStr = initType->toString();
                    
                    if (isUnionType(varType) && !isUnionType(initType)) {
                        // Check if the init type is compatible with any variant of the union
                        if (const auto* unionType = std::get_if<UnionType>(&varType->extra)) {
                            bool compatibleWithAnyVariant = false;
                            for (const auto& variantType : unionType->types) {
                                if (typeSystem.isCompatible(initType, variantType)) {
                                    compatibleWithAnyVariant = true;
                                    break;
                                }
                            }
                            
                            if (!compatibleWithAnyVariant) {
                                addError("Type mismatch in variable declaration '" + varDecl->name + 
                                        "': type " + initTypeStr + " is not compatible with any variant of union type " + 
                                        varTypeStr, varDecl->line);
                            }
                        }
                    } else if (!isUnionType(varType) && isUnionType(initType)) {
                        addError("Type mismatch in variable declaration '" + varDecl->name + 
                                "': cannot assign union type " + initTypeStr + 
                                " to non-union type " + varTypeStr + 
                                ". Consider using pattern matching to extract the value", 
                                varDecl->line);
                    } else {
                        // Both are union types but incompatible
                        addError("Type mismatch in variable declaration '" + varDecl->name + 
                                "': incompatible union types " + initTypeStr + 
                                " and " + varTypeStr, 
                                varDecl->line);
                    }
                } else if (isErrorUnionType(varType) || isErrorUnionType(initType)) {
                    std::string varTypeStr = varType->toString();
                    std::string initTypeStr = initType->toString();
                    
                    if (isErrorUnionType(varType) && !isErrorUnionType(initType)) {
                        addError("Type mismatch in variable declaration '" + varDecl->name + 
                                "': cannot assign non-fallible type " + initTypeStr + 
                                " to fallible type " + varTypeStr + 
                                ". Use ok(" + varDecl->name + ") to wrap the value", 
                                varDecl->line);
                    } else if (!isErrorUnionType(varType) && isErrorUnionType(initType)) {
                        addError("Type mismatch in variable declaration '" + varDecl->name + 
                                "': cannot assign fallible type " + initTypeStr + 
                                " to non-fallible type " + varTypeStr + 
                                ". Handle the error with '?' or 'match' first", 
                                varDecl->line);
                    } else {
                        // Both are error unions but incompatible
                        addError("Type mismatch in variable declaration '" + varDecl->name + 
                                "': incompatible error union types " + initTypeStr + 
                                " and " + varTypeStr, 
                                varDecl->line);
                    }
                } else if (varType->tag == TypeTag::Function && initType->tag == TypeTag::Function) {
                    // Enhanced function type error messages
                    std::string varTypeStr = varType->toString();
                    std::string initTypeStr = initType->toString();
                    
                    // Check if both are generic function types
                    bool varIsGeneric = !std::holds_alternative<FunctionType>(varType->extra);
                    bool initIsGeneric = !std::holds_alternative<FunctionType>(initType->extra);
                    
                    if (varIsGeneric && initIsGeneric) {
                        // Both are generic - this should be compatible, but if we get here there's another issue
                        addError("Function type compatibility issue in variable declaration '" + varDecl->name + 
                                "': both types are generic functions but incompatible", 
                                varDecl->line);
                    } else if (varIsGeneric) {
                        // Variable is generic function, initializer is specific - should be compatible
                        // This case should not occur with our enhanced compatibility checking
                        addError("Function type mismatch in variable declaration '" + varDecl->name + 
                                "': cannot assign specific function type " + initTypeStr + 
                                " to generic function type", 
                                varDecl->line);
                    } else if (initIsGeneric) {
                        // Variable is specific function, initializer is generic - should be compatible
                        addError("Function type mismatch in variable declaration '" + varDecl->name + 
                                "': cannot assign generic function type to specific function type " + varTypeStr, 
                                varDecl->line);
                    } else {
                        // Both are specific function types - provide detailed mismatch info
                        addError("Function signature mismatch in variable declaration '" + varDecl->name + 
                                "': cannot assign function " + initTypeStr + 
                                " to variable of type " + varTypeStr + 
                                ". Function signatures must be compatible", 
                                varDecl->line);
                    }
                } else if (varType->tag == TypeTag::List && initType->tag == TypeTag::List) {
                    // Enhanced list type error messages
                    auto varListType = std::get<ListType>(varType->extra);
                    auto initListType = std::get<ListType>(initType->extra);
                    addError("List element type mismatch in variable declaration '" + varDecl->name + 
                            "': cannot assign [" + initListType.elementType->toString() + 
                            "] to variable of type [" + varListType.elementType->toString() + "]", 
                            varDecl->line);
                } else if (varType->tag == TypeTag::Dict && initType->tag == TypeTag::Dict) {
                    // Enhanced dictionary type error messages
                    auto varDictType = std::get<DictType>(varType->extra);
                    auto initDictType = std::get<DictType>(initType->extra);
                    addError("Dictionary type mismatch in variable declaration '" + varDecl->name + 
                            "': cannot assign {" + initDictType.keyType->toString() + 
                            ": " + initDictType.valueType->toString() + "} to variable of type {" + 
                            varDictType.keyType->toString() + ": " + varDictType.valueType->toString() + "}", 
                            varDecl->line);
                } else if (varType->tag == TypeTag::Tuple && initType->tag == TypeTag::Tuple) {
                    // Enhanced tuple type error messages
                    auto varTupleType = std::get<TupleType>(varType->extra);
                    auto initTupleType = std::get<TupleType>(initType->extra);
                    
                    if (varTupleType.elementTypes.size() != initTupleType.elementTypes.size()) {
                        addError("Tuple size mismatch in variable declaration '" + varDecl->name + 
                                "': cannot assign tuple with " + std::to_string(initTupleType.elementTypes.size()) + 
                                " elements to variable expecting " + std::to_string(varTupleType.elementTypes.size()) + 
                                " elements", varDecl->line);
                    } else {
                        addError("Tuple element type mismatch in variable declaration '" + varDecl->name + 
                                "': tuple element types are incompatible", 
                                varDecl->line);
                    }
                } else {
                    addError("Type mismatch in variable declaration '" + varDecl->name + 
                            "': cannot assign " + initType->toString() + 
                            " to " + varType->toString(), 
                            varDecl->line);
                }
            }
            
            // If initializer type is more specific, use it
            if (varType == typeSystem.ANY_TYPE) {
                varType = initType;
            }
        }
        
        symbolTable.addVariable(varDecl->name, varType, varDecl->line);
        
    } else if (auto destructDecl = std::dynamic_pointer_cast<AST::DestructuringDeclaration>(stmt)) {
        // Type check tuple destructuring assignment
        TypePtr tupleType = checkExpression(destructDecl->initializer);
        
        // For now, assume all destructured variables have ANY_TYPE
        // In a more sophisticated implementation, we could infer types from tuple element types
        for (const std::string& varName : destructDecl->names) {
            symbolTable.addVariable(varName, typeSystem.ANY_TYPE, destructDecl->line);
        }
        
    } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        // Store top-level function declaration for visibility checking
        topLevelFunctions[funcDecl->name] = funcDecl;
        
        checkFunctionDeclaration(funcDecl);
        
    } else if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        enterScope();
        for (const auto& statement : blockStmt->statements) {
            checkStatement(statement);
        }
        exitScope();
        
    } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        TypePtr condType = checkExpression(ifStmt->condition);
        // Allow boolean types, any type, optional types (str?, int?), and error union types
        if (condType != typeSystem.BOOL_TYPE && 
            condType != typeSystem.ANY_TYPE && 
            !isOptionalType(condType) &&
            !isErrorUnionType(condType)) {
            addError("If condition must be boolean or optional type, got " + condType->toString(), ifStmt->line);
        }
        
        checkStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch) {
            checkStatement(ifStmt->elseBranch);
        }
        
    } else if (auto matchStmt = std::dynamic_pointer_cast<AST::MatchStatement>(stmt)) {
        checkMatchStatement(matchStmt);
        
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        TypePtr exprType = checkExpression(exprStmt->expression);
        
        // Enhanced unhandled fallible expression detection
        if (requiresErrorHandling(exprType)) {
            // Check if this is a function call that returns an error union
            if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(exprStmt->expression)) {
                if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
                    FunctionSignature* signature = symbolTable.findFunction(varExpr->name);
                    if (signature && signature->canFail) {
                        std::string errorTypesList = joinErrorTypes(signature->errorTypes);
                        addError("Unhandled fallible function call to '" + signature->name + 
                                "' that can return errors: [" + errorTypesList + 
                                "]. Must use '?' operator for error propagation or 'match' statement for error handling", 
                                exprStmt->line);
                    } else {
                        addError("Unhandled fallible expression: must use '?' operator or match statement", 
                                exprStmt->line);
                    }
                }
            } else {
                addError("Unhandled fallible expression: must use '?' operator or match statement", 
                        exprStmt->line);
            }
        }
        
    } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        if (currentFunction) {
            TypePtr returnType = typeSystem.NIL_TYPE;
            if (returnStmt->value) {
                // Pass expected return type as context for better type inference
                returnType = checkExpression(returnStmt->value, currentFunction->returnType);
                

            }
            
            // Check return type compatibility
            // Be more lenient with ANY_TYPE - it can be compatible with any expected type
            if (!typeSystem.isCompatible(returnType, currentFunction->returnType) && 
                returnType->tag != TypeTag::Any && currentFunction->returnType->tag != TypeTag::Any) {
                
                // Add more context to the error message
                std::string returnExpr = "";
                if (returnStmt->value) {
                    // Try to extract some context about what's being returned
                    if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(returnStmt->value)) {
                        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
                            returnExpr = varExpr->name + "()";
                        }
                    }
                }
                
                addError("Return type mismatch: expected " + currentFunction->returnType->toString() + 
                        ", got " + returnType->toString(), returnStmt->line, 0, 
                        "Return statement", returnExpr, 
                        "expression of type " + currentFunction->returnType->toString());
            }
        }
    } else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) {
        checkClassDeclaration(classDecl);
    } else if (auto moduleDecl = std::dynamic_pointer_cast<AST::ModuleDeclaration>(stmt)) {
        checkModuleDeclaration(moduleDecl);
    } else if (auto importStmt = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) {
        checkImportStatement(importStmt);
    } else if (auto contractStmt = std::dynamic_pointer_cast<AST::ContractStatement>(stmt)) {
        checkContractStatement(contractStmt);
    }
    
    // Handle other statement types as needed
}

TypePtr TypeChecker::checkExpression(const std::shared_ptr<AST::Expression>& expr) {
    return checkExpression(expr, nullptr);
}

TypePtr TypeChecker::checkExpression(const std::shared_ptr<AST::Expression>& expr, TypePtr expectedType) {
    if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        // Infer type from literal value using variant index
        switch (literalExpr->value.index()) {
            case 0: // long long (int64_t)
                // Use the expected type if it's a compatible numeric type
                if (expectedType && typeSystem.isNumericType(expectedType->tag)) {
                    if (expectedType->tag == TypeTag::Float32 || expectedType->tag == TypeTag::Float64) {
                        return expectedType; // Allow int literals to be used as floats
                    }
                }
                return typeSystem.INT_TYPE;
            case 1: // double
                // Check if we have an expected type context for better inference
                if (expectedType) {
                    if (expectedType->tag == TypeTag::Int || expectedType->tag == TypeTag::Int64) {
                        // If expecting int but got double, check if it's a whole number
                        long double doubleVal = std::get<long double>(literalExpr->value);
                        if (doubleVal == std::floor(doubleVal) && 
                            doubleVal >= std::numeric_limits<long long>::min() && 
                            doubleVal <= std::numeric_limits<long long>::max()) {
                            // It's a whole number that fits in long long, but was parsed as double
                            // This can happen with very large integers or scientific notation like 2e5
                            return expectedType;
                        }
                    } else if (expectedType->tag == TypeTag::Float32) {
                        // Check if the long double value fits in float32 without precision loss
                        long double doubleVal = std::get<long double>(literalExpr->value);
                        if (std::abs(doubleVal) <= std::numeric_limits<float>::max()) {
                            float floatVal = static_cast<float>(doubleVal);
                            if (static_cast<double>(floatVal) == doubleVal) {
                                return typeSystem.FLOAT32_TYPE;
                            }
                        }
                    }
                }
                return typeSystem.FLOAT64_TYPE;
            case 2: // std::string
                return typeSystem.STRING_TYPE;
            case 3: // bool
                return typeSystem.BOOL_TYPE;
            case 4: // std::nullptr_t
                return typeSystem.NIL_TYPE;
            case 5: // BigInt
                {
                    // For BigInt literals, try to infer the most appropriate type
                    const BigInt& bigIntValue = std::get<BigInt>(literalExpr->value);
                    
                    // If we have an expected type context and it's compatible, use it
                    if (expectedType && typeSystem.isNumericType(expectedType->tag)) {
                        return expectedType;
                    }
                    
                    // Try to determine the best fit type based on the value
                    try {
                        // Check if it fits in int64
                        int64_t int64Val = bigIntValue.to_int64();
                        
                        // Value fits in int64
                        if (int64Val >= 0) {
                            // Non-negative value that fits in int64 - default to int64
                            return typeSystem.INT64_TYPE;
                        } else {
                            // Negative value, must be signed int64
                            return typeSystem.INT64_TYPE;
                        }
                    } catch (const std::overflow_error&) {
                        // Value doesn't fit in int64, check if it could be uint64 or larger
                        try {
                            // Check if BigInt is stored as uint64 internally
                            if (bigIntValue.get_type().find("u64") != std::string::npos) {
                                // Check if the value actually fits in uint64 range
                                std::string bigIntStr = bigIntValue.to_string();
                                if (bigIntStr.length() <= 20) { // UINT64_MAX has 20 digits
                                    return typeSystem.UINT64_TYPE;
                                } else {
                                    // Too large for uint64, must be uint128
                                    return typeSystem.UINT128_TYPE;
                                }
                            }
                            
                            // Check if the value is positive and determine size
                            std::string bigIntStr = bigIntValue.to_string();
                            if (!bigIntStr.empty() && bigIntStr[0] != '-') {
                                // Positive number that doesn't fit in int64
                                if (bigIntStr.length() <= 20) { // UINT64_MAX has 20 digits
                                    return typeSystem.UINT64_TYPE;
                                } else {
                                    // Larger than uint64, must be uint128
                                    return typeSystem.UINT128_TYPE;
                                }
                            }
                        } catch (...) {
                            // Fallback to INT128_TYPE
                        }
                        
                        // Default to INT128_TYPE for negative large numbers
                        return typeSystem.INT128_TYPE;
                    }
                }
            default:
                break;
        }
        return typeSystem.ANY_TYPE;
        
    } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        Symbol* symbol = symbolTable.findVariable(varExpr->name);
        if (symbol) {
            // Check variable visibility if it's a module-level variable
            // Note: We need to check if this is actually a module-level variable first
            // For now, we'll check visibility for all variables
            AST::VisibilityLevel varVisibility = getModuleMemberVisibility(currentModulePath, varExpr->name);
            if (varVisibility != AST::VisibilityLevel::Public && varVisibility != AST::VisibilityLevel::Const) {
                // For non-public variables, check if access is allowed
                if (!canAccessModuleMember(currentModulePath, varExpr->name)) {
                    std::string visibilityStr;
                    switch (varVisibility) {
                        case AST::VisibilityLevel::Private:
                            visibilityStr = "private";
                            break;
                        case AST::VisibilityLevel::Protected:
                            visibilityStr = "protected";
                            break;
                        case AST::VisibilityLevel::Public:
                            visibilityStr = "public";
                            break;
                        case AST::VisibilityLevel::Const:
                            visibilityStr = "const";
                            break;
                    }
                    
                    addError("Cannot access " + visibilityStr + " variable '" + varExpr->name + 
                            "' from current context", expr->line);
                    return typeSystem.ANY_TYPE;
                }
            }
            return symbol->type;
        }
        
        // Check if it's a function being referenced (not called)
        FunctionSignature* signature = symbolTable.findFunction(varExpr->name);
        if (signature) {
            // Check function visibility for function references too
            AST::VisibilityLevel funcVisibility = getModuleMemberVisibility(currentModulePath, varExpr->name);
            if (funcVisibility != AST::VisibilityLevel::Public && funcVisibility != AST::VisibilityLevel::Const) {
                // For non-public functions, check if access is allowed
                if (!canAccessModuleMember(currentModulePath, varExpr->name)) {
                    std::string visibilityStr;
                    switch (funcVisibility) {
                        case AST::VisibilityLevel::Private:
                            visibilityStr = "private";
                            break;
                        case AST::VisibilityLevel::Protected:
                            visibilityStr = "protected";
                            break;
                        case AST::VisibilityLevel::Public:
                            visibilityStr = "public";
                            break;
                        case AST::VisibilityLevel::Const:
                            visibilityStr = "const";
                            break;
                    }
                    
                    addError("Cannot access " + visibilityStr + " function '" + varExpr->name + 
                            "' from current context", expr->line);
                    return typeSystem.ANY_TYPE;
                }
            }
         
            // Return a function type for the function reference
            TypePtr funcType = typeSystem.createFunctionType(signature->paramTypes, signature->returnType);
            return funcType;
        }
        
        addError("Undefined variable", expr->line, 0, "Variable lookup", varExpr->name, "declared variable name");
        return typeSystem.ANY_TYPE;
        
    } else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        checkFunctionCall(callExpr);
        
        // Get function signature or function type to determine return type
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
            // Check if this is a class constructor call
            if (classDeclarations.find(varExpr->name) != classDeclarations.end()) {
                // This is a constructor call - return a UserDefined type with the class name
                UserDefinedType userType;
                userType.name = varExpr->name;
                TypePtr classType = std::make_shared<Type>(TypeTag::UserDefined);
                classType->extra = userType;
                return classType;
            }
            
            // First check if it's a regular function
            FunctionSignature* signature = symbolTable.findFunction(varExpr->name);
            if (signature) {
                return signature->returnType;
            }
            
            // Check if it's a function-typed variable
            Symbol* symbol = symbolTable.findVariable(varExpr->name);
            if (symbol && symbol->type->tag == TypeTag::Function) {
                if (std::holds_alternative<FunctionType>(symbol->type->extra)) {
                    auto funcType = std::get<FunctionType>(symbol->type->extra);
                    return funcType.returnType;
                } else {
                    // Generic function type - try to infer return type from context
                    // For now, if we're in a function that expects a specific return type,
                    // assume the function call can return that type
                    if (currentFunction && currentFunction->returnType->tag != TypeTag::Any) {
                        return currentFunction->returnType;
                    }
                    return typeSystem.ANY_TYPE;
                }
            }
        } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(callExpr->callee)) {
            // This is likely a method call. The validation is done in checkFunctionCall.
            // Here, we just need to get the return type.
            std::vector<TypePtr> argTypes;
            for (const auto& arg : callExpr->arguments) {
                argTypes.push_back(checkExpression(arg));
            }
            return checkClassMethodCall(memberExpr, argTypes, callExpr);
        }
        return typeSystem.ANY_TYPE;
        
    } else if (auto unaryExpr = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        TypePtr rightType = checkExpression(unaryExpr->right);
        
        // Handle unary operators
        if (unaryExpr->op == TokenType::MINUS) {
            // Unary minus: special handling for unsigned types that might overflow
            if (rightType == typeSystem.UINT64_TYPE) {
                // Check if the operand is a BigInt literal that would overflow int64
                if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(unaryExpr->right)) {
                    if (std::holds_alternative<BigInt>(literalExpr->value)) {
                        const BigInt& bigIntValue = std::get<BigInt>(literalExpr->value);
                        try {
                            // Try to convert to int64 - if it overflows, we need int128
                            bigIntValue.to_int64();
                            // If we get here, it fits in int64, so int64 is fine
                            return typeSystem.INT64_TYPE;
                        } catch (const std::overflow_error&) {
                            // Overflows int64, need int128 for the negation
                            return typeSystem.INT128_TYPE;
                        }
                    }
                }
            }
            // Default: return the same type as the operand
            return rightType;
        } else if (unaryExpr->op == TokenType::BANG) {
            // Logical NOT: must be boolean
            if (rightType != typeSystem.BOOL_TYPE) {
                addError("Logical NOT operator requires boolean operand, got " + rightType->toString(), unaryExpr->line);
            }
            return typeSystem.BOOL_TYPE;
        } else {
            // Other unary operators (if any)
            return rightType;
        }
        
    } else if (auto fallibleExpr = std::dynamic_pointer_cast<AST::FallibleExpr>(expr)) {
        checkFallibleExpression(fallibleExpr);
        
        // Fallible expression unwraps the success type from error union
        TypePtr exprType = checkExpression(fallibleExpr->expression);
        if (isErrorUnionType(exprType)) {
            auto errorUnion = std::get<ErrorUnionType>(exprType->extra);
            // Both cases (with and without else handler) return the success type
            // With else handler: errors are handled locally, success value is returned
            // Without else handler: errors are propagated, success value is returned
            return errorUnion.successType;
        }
        return exprType;
        
    } else if (auto errorExpr = std::dynamic_pointer_cast<AST::ErrorConstructExpr>(expr)) {
        checkErrorConstructExpression(errorExpr);
        
        // Error construction should return the function's declared error union type if we're in a function context
        if (currentFunction && currentFunction->canFail) {
            // Return the function's declared return type (which is already an error union)
            return currentFunction->returnType;
        } else {
            // If not in a function context, create a new error union type
            if (typeSystem.isErrorType(errorExpr->errorType)) {
                return typeSystem.createErrorUnionType(typeSystem.ANY_TYPE, {errorExpr->errorType}, false);
            }
            addError("Unknown error type: " + errorExpr->errorType, expr->line);
            return typeSystem.ANY_TYPE;
        }
        
    } else if (auto okExpr = std::dynamic_pointer_cast<AST::OkConstructExpr>(expr)) {
        checkOkConstructExpression(okExpr);
        
        // Ok construction should return the function's declared error union type if we're in a function context
        if (currentFunction && currentFunction->canFail) {
            // Return the function's declared return type (which is already an error union)
            return currentFunction->returnType;
        } else {
            // If not in a function context, create a new error union type
            TypePtr valueType = checkExpression(okExpr->value);
            return typeSystem.createErrorUnionType(valueType, {}, true);
        }
        
    } else if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        TypePtr leftType = checkExpression(binaryExpr->left);
        TypePtr rightType = checkExpression(binaryExpr->right);
        
        // Handle comparison operators
        if (binaryExpr->op == TokenType::GREATER || binaryExpr->op == TokenType::LESS ||
            binaryExpr->op == TokenType::GREATER_EQUAL || binaryExpr->op == TokenType::LESS_EQUAL ||
            binaryExpr->op == TokenType::EQUAL_EQUAL || binaryExpr->op == TokenType::BANG_EQUAL) {
            return typeSystem.BOOL_TYPE;
        }
        
        // Handle logical operators
        if (binaryExpr->op == TokenType::AND || binaryExpr->op == TokenType::OR) {
            return typeSystem.BOOL_TYPE;
        }
        
        // Handle division operator - only returns error union for built-in error handling
        if (binaryExpr->op == TokenType::SLASH) {
            TypePtr resultType = typeSystem.getCommonType(leftType, rightType);
            // For now, return regular type - built-in error handling will be added later
            return resultType;
        }
        
        // Basic binary operation type checking for other arithmetic operations
        return typeSystem.getCommonType(leftType, rightType);
        
    } else if (auto assignExpr = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
        TypePtr valueType = checkExpression(assignExpr->value);
        
        // For simple variable assignment (x = value)
        if (!assignExpr->name.empty()) {
            symbolTable.addVariable(assignExpr->name, valueType, assignExpr->line);
        }
        
        return valueType;
        
    } else if (auto listExpr = std::dynamic_pointer_cast<AST::ListExpr>(expr)) {
        // Handle list expressions [1, 2, 3] or [expr1, expr2, ...]
        if (listExpr->elements.empty()) {
            // Empty list - return generic list type
            return typeSystem.createTypedListType(typeSystem.ANY_TYPE);
        }
        
        // Check all elements and infer common element type
        std::vector<TypePtr> elementTypes;
        for (const auto& element : listExpr->elements) {
            TypePtr elementType = checkExpression(element);
            elementTypes.push_back(elementType);
        }
        
        // Find common type for all elements
        TypePtr commonElementType = elementTypes[0];
        for (size_t i = 1; i < elementTypes.size(); ++i) {
            try {
                commonElementType = typeSystem.getCommonType(commonElementType, elementTypes[i]);
            } catch (const std::runtime_error& e) {
                addError("Inconsistent element types in list literal: cannot mix " + 
                        commonElementType->toString() + " and " + elementTypes[i]->toString(), 
                        expr->line);
                return typeSystem.createTypedListType(typeSystem.ANY_TYPE);
            }
        }
        
        return typeSystem.createTypedListType(commonElementType);
        
    } else if (auto dictExpr = std::dynamic_pointer_cast<AST::DictExpr>(expr)) {
        // Handle dictionary expressions {"key": value, ...}
        if (dictExpr->entries.empty()) {
            // Empty dictionary - return generic dict type
            return typeSystem.createTypedDictType(typeSystem.STRING_TYPE, typeSystem.ANY_TYPE);
        }
        
        // Check all entries and infer common key and value types
        std::vector<TypePtr> keyTypes;
        std::vector<TypePtr> valueTypes;
        
        for (const auto& [keyExpr, valueExpr] : dictExpr->entries) {
            TypePtr keyType = checkExpression(keyExpr);
            TypePtr valueType = checkExpression(valueExpr);
            keyTypes.push_back(keyType);
            valueTypes.push_back(valueType);
        }
        
        // Find common types for keys and values
        TypePtr commonKeyType = keyTypes[0];
        TypePtr commonValueType = valueTypes[0];
        
        for (size_t i = 1; i < keyTypes.size(); ++i) {
            try {
                commonKeyType = typeSystem.getCommonType(commonKeyType, keyTypes[i]);
            } catch (const std::runtime_error& e) {
                addError("Inconsistent key types in dictionary literal: cannot mix " + 
                        commonKeyType->toString() + " and " + keyTypes[i]->toString(), 
                        expr->line);
                return typeSystem.createTypedDictType(typeSystem.ANY_TYPE, typeSystem.ANY_TYPE);
            }
        }
        
        for (size_t i = 1; i < valueTypes.size(); ++i) {
            try {
                commonValueType = typeSystem.getCommonType(commonValueType, valueTypes[i]);
            } catch (const std::runtime_error& e) {
                addError("Inconsistent value types in dictionary literal: cannot mix " + 
                        commonValueType->toString() + " and " + valueTypes[i]->toString(), 
                        expr->line);
                return typeSystem.createTypedDictType(commonKeyType, typeSystem.ANY_TYPE);
            }
        }
        
        return typeSystem.createTypedDictType(commonKeyType, commonValueType);
        
    } else if (auto tupleExpr = std::dynamic_pointer_cast<AST::TupleExpr>(expr)) {
        // Handle tuple expressions (expr1, expr2, ...)
        std::vector<TypePtr> elementTypes;
        for (const auto& element : tupleExpr->elements) {
            TypePtr elementType = checkExpression(element);
            elementTypes.push_back(elementType);
        }
        
        return typeSystem.createTupleType(elementTypes);
        
    } else if (auto lambdaExpr = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) {
        // Handle lambda expressions
        enterScope(); // Create new scope for lambda parameters
        
        // Process parameters and add them to the scope
        std::vector<TypePtr> paramTypes;
        for (const auto& param : lambdaExpr->params) {
            TypePtr paramType = typeSystem.ANY_TYPE;
            if (param.second) {
                paramType = resolveTypeAnnotation(param.second);
            }
            paramTypes.push_back(paramType);
            symbolTable.addVariable(param.first, paramType, lambdaExpr->line);
        }
        
        // Determine return type
        TypePtr returnType = typeSystem.ANY_TYPE;
        if (lambdaExpr->returnType.has_value()) {
            returnType = resolveTypeAnnotation(lambdaExpr->returnType.value());
        } else {
            // Enhanced return type inference from lambda body
            returnType = inferLambdaReturnType(lambdaExpr->body);
        }
        
        // Set up function context for the lambda
        FunctionSignature* prevFunction = currentFunction;
        FunctionSignature lambdaFunction("__lambda", paramTypes, returnType, false, {}, 0);
        currentFunction = &lambdaFunction;
        
        // Check the lambda body
        if (lambdaExpr->body) {
            checkStatement(lambdaExpr->body);
        }
        
        // Restore previous function context
        currentFunction = prevFunction;
        
        exitScope(); // Exit lambda scope
        
        // Create and return function type
        TypePtr functionType = typeSystem.createFunctionType(paramTypes, returnType);
        

        
        return functionType;
        
    } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        // Check member access with visibility enforcement
        return checkMemberAccess(memberExpr);
    }
    
    // Default case for other expression types
    return typeSystem.ANY_TYPE;
}

TypePtr TypeChecker::inferLambdaReturnType(const std::shared_ptr<AST::Statement>& body) {
    // Try to infer return type from lambda body
    if (!body) {
        return typeSystem.NIL_TYPE;
    }
    
    // If body is a block statement, look for return statements
    if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(body)) {
        std::vector<TypePtr> returnTypes;
        
        for (const auto& stmt : blockStmt->statements) {
            if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
                if (returnStmt->value) {
                    TypePtr returnType = checkExpression(returnStmt->value);
                    returnTypes.push_back(returnType);
                } else {
                    returnTypes.push_back(typeSystem.NIL_TYPE);
                }
            }
        }
        
        // If we found return statements, try to find common type
        if (!returnTypes.empty()) {
            TypePtr commonType = returnTypes[0];
            for (size_t i = 1; i < returnTypes.size(); ++i) {
                try {
                    commonType = typeSystem.getCommonType(commonType, returnTypes[i]);
                } catch (const std::exception&) {
                    // If types are incompatible, fall back to ANY_TYPE
                    return typeSystem.ANY_TYPE;
                }
            }
            return commonType;
        }
        
        // No explicit return statements found, assume NIL return
        return typeSystem.NIL_TYPE;
    }
    
    // If body is an expression statement, infer from the expression
    if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(body)) {
        return checkExpression(exprStmt->expression);
    }
    
    // For other statement types, assume NIL return
    return typeSystem.NIL_TYPE;
}

void TypeChecker::checkFallibleExpression(const std::shared_ptr<AST::FallibleExpr>& expr) {
    TypePtr exprType = checkExpression(expr->expression);
    
    // Check that the expression is actually fallible
    if (!isErrorUnionType(exprType)) {
        addError("'?' operator can only be used with fallible expressions", expr->line);
        return;
    }
    
    // If there's an else handler, the error is handled locally - no propagation needed
    if (expr->elseHandler) {
        // Check the else handler statement
        checkStatement(expr->elseHandler);
        return;
    }
    
    // Enhanced error type propagation validation (only when no else handler)
    if (currentFunction) {
        auto errorUnion = std::get<ErrorUnionType>(exprType->extra);
        
        if (!currentFunction->canFail) {
            addError("Cannot propagate error in non-fallible function '" + currentFunction->name + 
                    "'. Function must return error union type to use '?' operator", 
                    expr->line);
        } else {
            // Detailed error type compatibility checking
            if (!canPropagateError(errorUnion.errorTypes, currentFunction->errorTypes)) {
                std::string sourceErrors = joinErrorTypes(errorUnion.errorTypes);
                std::string targetErrors = joinErrorTypes(currentFunction->errorTypes);
                
                addError("Error type propagation mismatch in function '" + currentFunction->name + 
                        "'. Expression can produce errors: [" + sourceErrors + 
                        "], but function signature only allows: [" + targetErrors + "]", 
                        expr->line);
            }
            
            // Check for specific error type compatibility
            if (!errorUnion.isGenericError && !currentFunction->errorTypes.empty()) {
                for (const auto& sourceError : errorUnion.errorTypes) {
                    bool found = std::find(currentFunction->errorTypes.begin(), 
                                         currentFunction->errorTypes.end(), 
                                         sourceError) != currentFunction->errorTypes.end();
                    if (!found) {
                        addError("Error type '" + sourceError + 
                                "' cannot be propagated by function '" + currentFunction->name + 
                                "' which only declares error types: [" + joinErrorTypes(currentFunction->errorTypes) + "]", 
                                expr->line);
                    }
                }
            }
        }
    } else {
        addError("'?' operator can only be used inside functions", expr->line);
    }
}

void TypeChecker::checkErrorConstructExpression(const std::shared_ptr<AST::ErrorConstructExpr>& expr) {
    // Enhanced error type validation
    if (!typeSystem.isErrorType(expr->errorType)) {
        addError("Unknown error type '" + expr->errorType + 
                "'. Error type must be declared or be a built-in error type", expr->line);
        return;
    }
    
    // Check if error type is compatible with current function signature
    if (currentFunction && currentFunction->canFail && !currentFunction->errorTypes.empty()) {
        bool isCompatible = std::find(currentFunction->errorTypes.begin(), 
                                    currentFunction->errorTypes.end(), 
                                    expr->errorType) != currentFunction->errorTypes.end();
        if (!isCompatible) {
            addError("Error type '" + expr->errorType + 
                    "' is not declared in function signature. Function '" + currentFunction->name + 
                    "' can only return error types: [" + joinErrorTypes(currentFunction->errorTypes) + "]", 
                    expr->line);
        }
    }
    
    // Check argument types if any
    for (const auto& arg : expr->arguments) {
        checkExpression(arg);
    }
}

void TypeChecker::checkOkConstructExpression(const std::shared_ptr<AST::OkConstructExpr>& expr) {
    // Just check the wrapped value
    checkExpression(expr->value);
}

void TypeChecker::checkFunctionCall(const std::shared_ptr<AST::CallExpr>& expr) {
    // Check arguments
    std::vector<TypePtr> argTypes;
    for (const auto& arg : expr->arguments) {
        argTypes.push_back(checkExpression(arg));
    }
    
    // Get function signature or check if it's a function-typed variable
    if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        // Special handling for assert function
        if (varExpr->name == "assert") {
            checkAssertCall(expr);
            return;
        }
        
        // Check if this is a class constructor call first
        if (classDeclarations.find(varExpr->name) != classDeclarations.end()) {
            // This is a constructor call - no additional validation needed here
            // The constructor call will be handled by the VM
            return;
        }
        
        // First check if it's a regular function
        FunctionSignature* signature = symbolTable.findFunction(varExpr->name);
        if (signature) {
            // Check function visibility before allowing the call
            AST::VisibilityLevel funcVisibility = getModuleMemberVisibility(currentModulePath, varExpr->name);
            if (funcVisibility != AST::VisibilityLevel::Public && funcVisibility != AST::VisibilityLevel::Const) {
                // For non-public functions, check if access is allowed
                if (!canAccessModuleMember(currentModulePath, varExpr->name)) {
                    std::string visibilityStr;
                    switch (funcVisibility) {
                        case AST::VisibilityLevel::Private:
                            visibilityStr = "private";
                            break;
                        case AST::VisibilityLevel::Protected:
                            visibilityStr = "protected";
                            break;
                        case AST::VisibilityLevel::Public:
                            visibilityStr = "public";
                            break;
                        case AST::VisibilityLevel::Const:
                            visibilityStr = "const";
                            break;
                    }
                    
                    addError("Cannot access " + visibilityStr + " function '" + varExpr->name + 
                            "' from current context", expr->line);
                    return;
                }
            }
            
            // Handle regular function call
            checkRegularFunctionCall(signature, argTypes, expr);
            return;
        }
        
        // Check if it's a function-typed variable (like a function parameter)
        TypePtr varType = symbolTable.getType(varExpr->name);
        if (varType && (varType->tag == TypeTag::Function || varType->tag == TypeTag::Any)) {
            // Handle higher-order function call or ANY_TYPE (which could be a function at runtime)
            if (varType->tag == TypeTag::Function) {
                checkHigherOrderFunctionCall(varType, argTypes, expr);
            }
            // For ANY_TYPE, we allow the call but can't do detailed type checking
            return;
        }
        
        addError("Undefined function", expr->line, 0, "Function call", varExpr->name, "declared function name");
        return;
    }
    
    // Handle module member function calls (e.g., module.function())
    if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->callee)) {
        checkModuleMemberFunctionCall(memberExpr, argTypes, expr);
        return;
    }
    
    addError("Invalid function call expression", expr->line);
}

void TypeChecker::checkRegularFunctionCall(FunctionSignature* signature, const std::vector<TypePtr>& argTypes, const std::shared_ptr<AST::CallExpr>& expr) {
    // Check argument count with optional parameter support
    if (!signature->isValidArgCount(argTypes.size())) {
        size_t minArgs = signature->getMinRequiredArgs();
        size_t maxArgs = signature->paramTypes.size();
        
        std::string expectedMsg;
        if (minArgs == maxArgs) {
            expectedMsg = std::to_string(minArgs) + " arguments";
        } else {
            expectedMsg = std::to_string(minArgs) + "-" + std::to_string(maxArgs) + " arguments";
        }
        
        addError("Function argument count mismatch `" + signature->name + "`", expr->line, 0, "Function call", 
                signature->name, 
                expectedMsg + ", got " + std::to_string(argTypes.size()));
        return;
    }
    
    // Check argument types
    for (size_t i = 0; i < argTypes.size(); ++i) {
        if (!typeSystem.isCompatible(argTypes[i], signature->paramTypes[i])) {
            addError("Argument " + std::to_string(i + 1) + " type mismatch: expected " + 
                    signature->paramTypes[i]->toString() + ", got " + argTypes[i]->toString(), 
                    expr->line);
        }
    }
    
    // Enhanced error union compatibility checking for function calls
    if (signature->canFail) {
        // Check if the function call is being handled properly
        // This will be checked at the expression statement level
        
        // Validate error union compatibility if this call is part of error propagation
        if (currentFunction && currentFunction->canFail) {
            if (!isErrorUnionCompatible(signature->returnType, currentFunction->returnType)) {
                addError("Function call returns incompatible error types. Expected error types: [" +
                        joinErrorTypes(currentFunction->errorTypes) + "], but function returns: [" +
                        joinErrorTypes(signature->errorTypes) + "]", expr->line);
            }
        }
    }
}

void TypeChecker::checkHigherOrderFunctionCall(TypePtr functionType, const std::vector<TypePtr>& argTypes, const std::shared_ptr<AST::CallExpr>& expr) {
    // Extract function type information
    if (std::holds_alternative<FunctionType>(functionType->extra)) {
        auto funcType = std::get<FunctionType>(functionType->extra);
        
        // Check argument count
        if (argTypes.size() != funcType.paramTypes.size()) {
            addError("Function argument count mismatch", expr->line, 0, "Higher-order function call", 
                    "", 
                    std::to_string(funcType.paramTypes.size()) + " arguments, got " + std::to_string(argTypes.size()));
            return;
        }
        
        // Check argument types
        for (size_t i = 0; i < argTypes.size(); ++i) {
            if (!typeSystem.isCompatible(argTypes[i], funcType.paramTypes[i])) {
                addError("Argument " + std::to_string(i + 1) + " type mismatch: expected " + 
                        funcType.paramTypes[i]->toString() + ", got " + argTypes[i]->toString(), 
                        expr->line);
            }
        }
    } else {
        // For generic function types, we should be more permissive
        if (functionType->tag == TypeTag::Function) {
            // Generic function type - allow any function call
            // This handles cases where function parameter is declared as generic 'function'
            return;
        }
        
        std::string functionName = "";
        if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
            if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
                functionName = varExpr->name;
            }
        }
        
        addError("Invalid function type in higher-order function call", expr->line, 0, 
                "Function call", functionName, "specific function signature or compatible function type");
    }
}

// Helper method to join error types for error messages
std::string TypeChecker::joinErrorTypes(const std::vector<std::string>& errorTypes) {
    if (errorTypes.empty()) {
        return "any error";
    }
    
    std::string result;
    for (size_t i = 0; i < errorTypes.size(); ++i) {
        if (i > 0) result += ", ";
        result += errorTypes[i];
    }
    return result;
}

void TypeChecker::checkFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    // Set current function context
    FunctionSignature* signature = symbolTable.findFunction(stmt->name);
    FunctionSignature* prevFunction = currentFunction;
    currentFunction = signature;
    
    // Validate error type annotations consistency
    validateFunctionErrorTypes(stmt);
    
    // Enter function scope
    enterScope();
    
    // Add parameters to scope (both required and optional)
    for (const auto& param : stmt->params) {
        TypePtr paramType = typeSystem.ANY_TYPE;
        if (param.second) {
            paramType = resolveTypeAnnotation(param.second);
        }
        symbolTable.addVariable(param.first, paramType, stmt->line);
        
    }
    
    // Add optional parameters to scope
    for (const auto& optParam : stmt->optionalParams) {
        TypePtr paramType = typeSystem.ANY_TYPE;
        if (optParam.second.first) {
            paramType = resolveTypeAnnotation(optParam.second.first);
        }
        symbolTable.addVariable(optParam.first, paramType, stmt->line);
    }
    
    // Check function body
    checkStatement(stmt->body);
    
    // Infer error types if function uses ? operator but doesn't explicitly declare error types
    if (!stmt->canFail) {
        std::vector<std::string> inferredErrorTypes = inferFunctionErrorTypes(stmt->body);
        if (!inferredErrorTypes.empty()) {
            // Function uses ? operator but doesn't declare error types
            addError("Function '" + stmt->name + "' uses fallible expressions but does not declare error handling. " +
                    "Add error type annotation to return type (e.g., 'Type?ErrorType') or use 'throws' keyword", 
                    stmt->line);
        }
    } else {
        // Validate that function body can produce declared error types
        validateFunctionBodyErrorTypes(stmt);
    }
    
    // Exit function scope
    exitScope();
    currentFunction = prevFunction;
}

void TypeChecker::checkMatchStatement(const std::shared_ptr<AST::MatchStatement>& stmt) {
    // Check the matched expression
    TypePtr matchType = checkExpression(stmt->value);
    
    // Check each case
    for (const auto& matchCase : stmt->cases) {
        // Check the pattern and guard if present
        if (matchCase.guard) {
            TypePtr guardType = checkExpression(matchCase.guard);
            if (guardType != typeSystem.BOOL_TYPE && guardType != typeSystem.ANY_TYPE) {
                addError("Match guard must be a boolean expression", stmt->line);
            }
        }
        
        // Check the case body
        checkStatement(matchCase.body);
        
        // Validate pattern compatibility with matched type
        validatePatternCompatibility(matchCase.pattern, matchType, stmt->line);
    }
    
    // Enhanced exhaustiveness checking for different type categories
    if (isErrorUnionType(matchType)) {
        std::vector<std::shared_ptr<AST::MatchCase>> cases;
        for (const auto& c : stmt->cases) {
            cases.push_back(std::make_shared<AST::MatchCase>(c));
        }
        
        if (!isExhaustiveErrorMatch(cases, matchType)) {
            auto errorUnion = std::get<ErrorUnionType>(matchType->extra);
            
            if (errorUnion.isGenericError) {
                addError("Match statement is not exhaustive for error union type. Must handle both success case (val pattern) and error case (err pattern)", 
                        stmt->line);
            } else {
                std::string missingPatterns = "Must handle success case (val pattern) and all error types: [" +
                                            joinErrorTypes(errorUnion.errorTypes) + "]";
                addError("Match statement is not exhaustive for error union type. " + missingPatterns, 
                        stmt->line);
            }
        }
    } else if (isUnionType(matchType)) {
        // Union type exhaustiveness checking
        std::vector<std::shared_ptr<AST::MatchCase>> cases;
        for (const auto& c : stmt->cases) {
            cases.push_back(std::make_shared<AST::MatchCase>(c));
        }
        
        if (!isExhaustiveUnionMatch(matchType, cases)) {
            auto unionType = std::get<UnionType>(matchType->extra);
            std::string missingVariants = getMissingUnionVariants(matchType, cases);
            addError("Match statement is not exhaustive for union type " + matchType->toString() + 
                    ". Missing patterns for: " + missingVariants, stmt->line);
        }
    } else if (typeSystem.isOptionType(matchType)) {
        // Option type exhaustiveness checking
        std::vector<std::shared_ptr<AST::MatchCase>> cases;
        for (const auto& c : stmt->cases) {
            cases.push_back(std::make_shared<AST::MatchCase>(c));
        }
        
        if (!isExhaustiveOptionMatch(cases)) {
            addError("Match statement is not exhaustive for Option type. Must handle both Some and None cases", 
                    stmt->line);
        }
    }
}

bool TypeChecker::isErrorUnionCompatible(TypePtr from, TypePtr to) {
    if (from->tag != TypeTag::ErrorUnion || to->tag != TypeTag::ErrorUnion) {
        return false;
    }
    
    auto fromErrorUnion = std::get<ErrorUnionType>(from->extra);
    auto toErrorUnion = std::get<ErrorUnionType>(to->extra);
    
    // Success types must be compatible
    if (!typeSystem.isCompatible(fromErrorUnion.successType, toErrorUnion.successType)) {
        return false;
    }
    
    // Check error type compatibility
    return canPropagateError(fromErrorUnion.errorTypes, toErrorUnion.errorTypes);
}

bool TypeChecker::canPropagateError(const std::vector<std::string>& sourceErrors, 
                                  const std::vector<std::string>& targetErrors) {
    // If target allows generic errors, any source is compatible
    if (targetErrors.empty()) {
        return true;
    }
    
    // Check that all source errors are in target errors
    for (const auto& sourceError : sourceErrors) {
        bool found = std::find(targetErrors.begin(), targetErrors.end(), sourceError) != targetErrors.end();
        if (!found) {
            return false;
        }
    }
    
    return true;
}

std::vector<std::string> TypeChecker::getErrorTypesFromType(TypePtr type) {
    if (type->tag == TypeTag::ErrorUnion) {
        auto errorUnion = std::get<ErrorUnionType>(type->extra);
        return errorUnion.errorTypes;
    }
    return {};
}

bool TypeChecker::isErrorUnionType(TypePtr type) {
    return type && type->tag == TypeTag::ErrorUnion;
}

bool TypeChecker::isUnionType(TypePtr type) {
    return type && type->tag == TypeTag::Union;
}

bool TypeChecker::requiresErrorHandling(TypePtr type) {
    return isErrorUnionType(type);
}

bool TypeChecker::isExhaustiveErrorMatch(const std::vector<std::shared_ptr<AST::MatchCase>>& cases, TypePtr type) {
    if (!isErrorUnionType(type)) {
        return true; // Non-error types don't need exhaustive error matching
    }
    
    auto errorUnion = std::get<ErrorUnionType>(type->extra);
    
    bool hasSuccessCase = false;
    bool hasGenericErrorCase = false;
    std::unordered_set<std::string> coveredErrors;
    
    for (const auto& matchCase : cases) {
        // Enhanced pattern analysis for error matching
        if (auto valPattern = std::dynamic_pointer_cast<AST::ValPatternExpr>(matchCase->pattern)) {
            hasSuccessCase = true;
        } else if (auto errPattern = std::dynamic_pointer_cast<AST::ErrPatternExpr>(matchCase->pattern)) {
            if (errPattern->errorType.has_value()) {
                // Specific error type in err pattern
                coveredErrors.insert(errPattern->errorType.value());
            } else {
                // Generic error pattern
                hasGenericErrorCase = true;
            }
        } else if (auto errorTypePattern = std::dynamic_pointer_cast<AST::ErrorTypePatternExpr>(matchCase->pattern)) {
            // Specific error type pattern
            coveredErrors.insert(errorTypePattern->errorType);
        } else if (auto bindingPattern = std::dynamic_pointer_cast<AST::BindingPatternExpr>(matchCase->pattern)) {
            if (bindingPattern->typeName == "val") {
                hasSuccessCase = true;
            } else if (bindingPattern->typeName == "err") {
                hasGenericErrorCase = true;
            } else {
                // Specific error type pattern
                coveredErrors.insert(bindingPattern->typeName);
            }
        } else if (auto typePattern = std::dynamic_pointer_cast<AST::TypePatternExpr>(matchCase->pattern)) {
            // Check if this is an error type pattern
            if (typePattern->type && typeSystem.isErrorType(typePattern->type->typeName)) {
                coveredErrors.insert(typePattern->type->typeName);
            }
        } else {
            // Wildcard or other patterns - assume they cover everything
            hasSuccessCase = true;
            hasGenericErrorCase = true;
        }
    }
    
    // For generic error unions, we need at least success and error cases
    if (errorUnion.isGenericError) {
        return hasSuccessCase && hasGenericErrorCase;
    }
    
    // For specific error unions, all error types must be covered plus success case
    bool allErrorsCovered = hasGenericErrorCase || 
                           (coveredErrors.size() >= errorUnion.errorTypes.size() &&
                            std::all_of(errorUnion.errorTypes.begin(), errorUnion.errorTypes.end(),
                                       [&coveredErrors](const std::string& errorType) {
                                           return coveredErrors.find(errorType) != coveredErrors.end();
                                       }));
    
    return hasSuccessCase && allErrorsCovered;
}

std::vector<TypeCheckError> TypeChecker::checkFunction(const std::shared_ptr<AST::FunctionDeclaration>& func) {
    errors.clear();
    checkFunctionDeclaration(func);
    return errors;
}
// Function signature error type validation methods

void TypeChecker::validateFunctionErrorTypes(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    // Validate consistency between return type and declared error types
    if (stmt->returnType && *stmt->returnType) {
        auto returnType = resolveTypeAnnotation(*stmt->returnType);
        
        if (isErrorUnionType(returnType)) {
            auto errorUnion = std::get<ErrorUnionType>(returnType->extra);
            
            // If function declares specific error types, they should match return type
            if (stmt->canFail && !stmt->declaredErrorTypes.empty()) {
                // Check that declared error types match return type error types
                if (!errorUnion.isGenericError) {
                    for (const auto& declaredError : stmt->declaredErrorTypes) {
                        if (std::find(errorUnion.errorTypes.begin(), errorUnion.errorTypes.end(), declaredError) == errorUnion.errorTypes.end()) {
                            addError("Function '" + stmt->name + "' declares error type '" + declaredError + 
                                    "' but return type does not include this error type", stmt->line);
                        }
                    }
                    
                    for (const auto& returnError : errorUnion.errorTypes) {
                        if (std::find(stmt->declaredErrorTypes.begin(), stmt->declaredErrorTypes.end(), returnError) == stmt->declaredErrorTypes.end()) {
                            addError("Function '" + stmt->name + "' return type includes error type '" + returnError + 
                                    "' but it is not declared in function signature", stmt->line);
                        }
                    }
                }
            }
        } else if (stmt->canFail) {
            // Function declares it can fail but return type is not an error union
            addError("Function '" + stmt->name + "' declares 'throws' but return type is not an error union type", stmt->line);
        }
    } else if (stmt->canFail) {
        // Function declares it can fail but has no return type annotation
        addError("Function '" + stmt->name + "' declares 'throws' but has no return type annotation. " +
                "Use 'Type?' for generic errors or 'Type?ErrorType1,ErrorType2' for specific error types", stmt->line);
    }
}

void TypeChecker::validateFunctionBodyErrorTypes(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    if (!stmt->canFail) {
        return; // No error type validation needed for non-fallible functions
    }
    
    // Infer error types that the function body can actually produce
    std::vector<std::string> inferredErrorTypes = inferFunctionErrorTypes(stmt->body);
    
    // If function declares specific error types, validate they can be produced
    if (!stmt->declaredErrorTypes.empty()) {
        for (const auto& declaredError : stmt->declaredErrorTypes) {
            if (!canFunctionProduceErrorType(stmt->body, declaredError)) {
                addError("Function '" + stmt->name + "' declares error type '" + declaredError + 
                        "' but function body cannot produce this error type", stmt->line);
            }
        }
        
        // Check for undeclared error types that the body might produce
        for (const auto& inferredError : inferredErrorTypes) {
            if (std::find(stmt->declaredErrorTypes.begin(), stmt->declaredErrorTypes.end(), inferredError) == stmt->declaredErrorTypes.end()) {
                addError("Function '" + stmt->name + "' body can produce error type '" + inferredError + 
                        "' but it is not declared in function signature", stmt->line);
            }
        }
    }
}

void TypeChecker::validateErrorTypeCompatibility(const std::shared_ptr<AST::FunctionDeclaration>& caller,
                                               const std::shared_ptr<AST::FunctionDeclaration>& callee) {
    if (!callee->canFail) {
        return; // Callee doesn't produce errors, no compatibility check needed
    }
    
    if (!caller->canFail) {
        // Caller doesn't handle errors but callee can produce them
        addError("Function '" + caller->name + "' calls fallible function '" + callee->name + 
                "' but does not declare error handling. Add 'throws' to function signature or handle errors explicitly", 
                caller->line);
        return;
    }
    
    // Check error type compatibility
    if (!caller->declaredErrorTypes.empty() && !callee->declaredErrorTypes.empty()) {
        if (!canPropagateError(callee->declaredErrorTypes, caller->declaredErrorTypes)) {
            std::string calleeErrors = joinErrorTypes(callee->declaredErrorTypes);
            std::string callerErrors = joinErrorTypes(caller->declaredErrorTypes);
            addError("Function '" + caller->name + "' cannot propagate all error types from '" + callee->name + 
                    "'. Callee errors: [" + calleeErrors + "], Caller errors: [" + callerErrors + "]", 
                    caller->line);
        }
    }
}

bool TypeChecker::canFunctionProduceErrorType(const std::shared_ptr<AST::Statement>& body, 
                                             const std::string& errorType) {
    // Check if the function body can produce the specified error type
    
    if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(body)) {
        for (const auto& stmt : blockStmt->statements) {
            if (canFunctionProduceErrorType(stmt, errorType)) {
                return true;
            }
        }
    } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(body)) {
        if (returnStmt->value) {
            // Check if the return expression can produce the error type
            auto returnErrors = inferExpressionErrorTypes(returnStmt->value);
            return std::find(returnErrors.begin(), returnErrors.end(), errorType) != returnErrors.end();
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(body)) {
        return canFunctionProduceErrorType(ifStmt->thenBranch, errorType) ||
               (ifStmt->elseBranch && canFunctionProduceErrorType(ifStmt->elseBranch, errorType));
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(body)) {
        // Check for fallible expressions that might propagate errors
        auto exprErrors = inferExpressionErrorTypes(exprStmt->expression);
        return std::find(exprErrors.begin(), exprErrors.end(), errorType) != exprErrors.end();
    }
    
    return false;
}

std::vector<std::string> TypeChecker::inferFunctionErrorTypes(const std::shared_ptr<AST::Statement>& body) {
    std::vector<std::string> errorTypes;
    
    if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(body)) {
        for (const auto& stmt : blockStmt->statements) {
            auto stmtErrors = inferFunctionErrorTypes(stmt);
            errorTypes.insert(errorTypes.end(), stmtErrors.begin(), stmtErrors.end());
        }
    } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(body)) {
        if (returnStmt->value) {
            auto returnErrors = inferExpressionErrorTypes(returnStmt->value);
            errorTypes.insert(errorTypes.end(), returnErrors.begin(), returnErrors.end());
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(body)) {
        auto thenErrors = inferFunctionErrorTypes(ifStmt->thenBranch);
        errorTypes.insert(errorTypes.end(), thenErrors.begin(), thenErrors.end());
        
        if (ifStmt->elseBranch) {
            auto elseErrors = inferFunctionErrorTypes(ifStmt->elseBranch);
            errorTypes.insert(errorTypes.end(), elseErrors.begin(), elseErrors.end());
        }
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(body)) {
        // Check for fallible expressions that might propagate errors
        auto exprErrors = inferExpressionErrorTypes(exprStmt->expression);
        errorTypes.insert(errorTypes.end(), exprErrors.begin(), exprErrors.end());
    }
    
    // Remove duplicates
    std::sort(errorTypes.begin(), errorTypes.end());
    errorTypes.erase(std::unique(errorTypes.begin(), errorTypes.end()), errorTypes.end());
    
    return errorTypes;
}


std::vector<std::string> TypeChecker::inferExpressionErrorTypes(const std::shared_ptr<AST::Expression>& expr) {
    std::vector<std::string> errorTypes;
    
    if (auto errorConstruct = std::dynamic_pointer_cast<AST::ErrorConstructExpr>(expr)) {
        // Direct error construction
        errorTypes.push_back(errorConstruct->errorType);
        
    } else if (auto fallibleExpr = std::dynamic_pointer_cast<AST::FallibleExpr>(expr)) {
        // Fallible expression with ? operator - propagates errors from inner expression
        auto innerErrors = inferExpressionErrorTypes(fallibleExpr->expression);
        errorTypes.insert(errorTypes.end(), innerErrors.begin(), innerErrors.end());
        
    } else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        // Function call - check if called function can produce errors
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
            FunctionSignature* signature = symbolTable.findFunction(varExpr->name);
            if (signature && signature->canFail) {
                errorTypes.insert(errorTypes.end(), signature->errorTypes.begin(), signature->errorTypes.end());
            }
        }
        
    } else if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        // Binary expressions might produce built-in errors (e.g., division by zero)
        if (binaryExpr->op == TokenType::SLASH) {
            errorTypes.push_back("DivisionByZero");
        }
        
        // Also check operands for error propagation
        auto leftErrors = inferExpressionErrorTypes(binaryExpr->left);
        auto rightErrors = inferExpressionErrorTypes(binaryExpr->right);
        errorTypes.insert(errorTypes.end(), leftErrors.begin(), leftErrors.end());
        errorTypes.insert(errorTypes.end(), rightErrors.begin(), rightErrors.end());
        
    } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
        // Array/dict indexing can produce IndexOutOfBounds errors
        errorTypes.push_back("IndexOutOfBounds");
        
        // Also check object and index expressions
        auto objectErrors = inferExpressionErrorTypes(indexExpr->object);
        auto indexErrors = inferExpressionErrorTypes(indexExpr->index);
        errorTypes.insert(errorTypes.end(), objectErrors.begin(), objectErrors.end());
        errorTypes.insert(errorTypes.end(), indexErrors.begin(), indexErrors.end());
    }
    
    // Remove duplicates
    std::sort(errorTypes.begin(), errorTypes.end());
    errorTypes.erase(std::unique(errorTypes.begin(), errorTypes.end()), errorTypes.end());
    
    return errorTypes;
}
void TypeChecker::registerBuiltinFunctions() {
    // Register builtin functions so they're recognized during semantic analysis
    
    // Core utility functions
    symbolTable.addFunction("len", FunctionSignature(
        "len", {typeSystem.ANY_TYPE}, typeSystem.INT_TYPE, false, {}, 0));
    
    symbolTable.addFunction("typeOf", FunctionSignature(
        "typeOf", {typeSystem.ANY_TYPE}, typeSystem.STRING_TYPE, false, {}, 0));
    
    symbolTable.addFunction("time", FunctionSignature(
        "time", {}, typeSystem.INT64_TYPE, false, {}, 0));
    
    symbolTable.addFunction("date", FunctionSignature(
        "date", {}, typeSystem.STRING_TYPE, false, {}, 0));
    
    symbolTable.addFunction("now", FunctionSignature(
        "now", {}, typeSystem.STRING_TYPE, false, {}, 0));
    
    symbolTable.addFunction("clock", FunctionSignature(
        "clock", {}, typeSystem.FLOAT64_TYPE, false, {}, 0));
    
    symbolTable.addFunction("sleep", FunctionSignature(
        "sleep", {typeSystem.FLOAT64_TYPE}, typeSystem.NIL_TYPE, false, {}, 0));
    
    symbolTable.addFunction("round", FunctionSignature(
        "round", {typeSystem.FLOAT64_TYPE, typeSystem.INT_TYPE}, typeSystem.FLOAT64_TYPE, false, {}, 0));
    
    symbolTable.addFunction("debug", FunctionSignature(
        "debug", {typeSystem.ANY_TYPE}, typeSystem.NIL_TYPE, false, {}, 0));
    
    symbolTable.addFunction("input", FunctionSignature(
        "input", {typeSystem.STRING_TYPE}, typeSystem.STRING_TYPE, false, {}, 0));
    
    symbolTable.addFunction("assert", FunctionSignature(
        "assert", {typeSystem.BOOL_TYPE, typeSystem.STRING_TYPE}, typeSystem.NIL_TYPE, false, {}, 0));
    
    // Higher-order functions
    symbolTable.addFunction("map", FunctionSignature(
        "map", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("filter", FunctionSignature(
        "filter", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("reduce", FunctionSignature(
        "reduce", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("forEach", FunctionSignature(
        "forEach", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("find", FunctionSignature(
        "find", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("some", FunctionSignature(
        "some", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.BOOL_TYPE, false, {}, 0));
    
    symbolTable.addFunction("every", FunctionSignature(
        "every", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.BOOL_TYPE, false, {}, 0));
    
    symbolTable.addFunction("compose", FunctionSignature(
        "compose", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("curry", FunctionSignature(
        "curry", {typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("partial", FunctionSignature(
        "partial", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    // Channel functions (VM-implemented)
    symbolTable.addFunction("channel", FunctionSignature(
        "channel", {}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("send", FunctionSignature(
        "send", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.NIL_TYPE, false, {}, 0));
    
    symbolTable.addFunction("receive", FunctionSignature(
        "receive", {typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0));
    
    symbolTable.addFunction("close", FunctionSignature(
        "close", {typeSystem.ANY_TYPE}, typeSystem.NIL_TYPE, false, {}, 0));
}

void TypeChecker::checkContractStatement(const std::shared_ptr<AST::ContractStatement>& stmt) {
    if (!stmt->condition) {
        addError("contract statement missing condition", stmt->line, 0, 
                getCodeContext(stmt->line), "contract", "contract(condition, message)");
        return;
    }
    
    if (!stmt->message) {
        addError("contract statement missing message", stmt->line, 0, 
                getCodeContext(stmt->line), "contract", "contract(condition, message)");
        return;
    }
    
    // Check condition is boolean
    TypePtr conditionType = checkExpression(stmt->condition);
    if (conditionType != typeSystem.BOOL_TYPE && conditionType != typeSystem.ANY_TYPE) {
        addError("contract condition must be boolean, got " + conditionType->toString(), 
                stmt->line, 0, getCodeContext(stmt->line), "condition", "boolean expression");
    }
    
    // Check message is string
    TypePtr messageType = checkExpression(stmt->message);
    if (messageType != typeSystem.STRING_TYPE && messageType != typeSystem.ANY_TYPE) {
        addError("contract message must be string, got " + messageType->toString(), 
                stmt->line, 0, getCodeContext(stmt->line), "message", "string literal or expression");
    }
}

void TypeChecker::checkAssertCall(const std::shared_ptr<AST::CallExpr>& expr) {
    if (expr->arguments.size() != 2) {
        addError("assert() expects exactly 2 arguments: condition (bool) and message (string), got " + 
                std::to_string(expr->arguments.size()), expr->line, 0, 
                getCodeContext(expr->line), "assert(...)", "assert(condition, message)");
        return;
    }
    
    // Check first argument (condition) is boolean
    TypePtr conditionType = checkExpression(expr->arguments[0]);
    if (conditionType != typeSystem.BOOL_TYPE && conditionType != typeSystem.ANY_TYPE) {
        addError("assert() first argument must be boolean, got " + conditionType->toString(), 
                expr->line, 0, getCodeContext(expr->line), "condition", "boolean expression");
    }
    
    // Check second argument (message) is string
    TypePtr messageType = checkExpression(expr->arguments[1]);
    if (messageType != typeSystem.STRING_TYPE && messageType != typeSystem.ANY_TYPE) {
        addError("assert() second argument must be string, got " + messageType->toString(), 
                expr->line, 0, getCodeContext(expr->line), "message", "string literal or expression");
    }
}

std::string TypeChecker::getCodeContext(int line) {
    if (sourceCode.empty() || line <= 0) {
        return "";
    }
    
    std::istringstream stream(sourceCode);
    std::string currentLine;
    int currentLineNumber = 1;
    
    // Find the target line
    while (std::getline(stream, currentLine) && currentLineNumber < line) {
        currentLineNumber++;
    }
    
    if (currentLineNumber == line) {
        return currentLine;
    }
    
    return "";
}
// Helper functions for type checking

bool TypeChecker::isOptionalType(TypePtr type) {
    if (!type || type->tag != TypeTag::ErrorUnion) {
        return false;
    }
    
    // Both optional types (str?) and fallible types (int?DivisionByZero) 
    // should be allowed in if conditions for null/error checking
    auto errorUnion = std::get<ErrorUnionType>(type->extra);
    
    // Optional types: empty error types and marked as generic (str?)
    bool isOptional = errorUnion.errorTypes.empty() && errorUnion.isGenericError;
    
    // Fallible types: have specific error types (int?DivisionByZero)
    bool isFallible = !errorUnion.errorTypes.empty();
    
    return isOptional || isFallible;
}

// Union type pattern matching validation methods

bool TypeChecker::isExhaustiveUnionMatch(TypePtr unionType, const std::vector<std::shared_ptr<AST::MatchCase>>& cases) {
    if (!unionType || unionType->tag != TypeTag::Union) {
        return true; // Non-union types don't need union exhaustiveness checking
    }
    
    const auto* unionTypeInfo = std::get_if<UnionType>(&unionType->extra);
    if (!unionTypeInfo) {
        return true;
    }
    
    std::set<TypeTag> coveredTypeTags;
    std::set<std::string> coveredTypeNames;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<AST::BindingPatternExpr>(matchCase->pattern)) {
            // Pattern like Some(x), None, etc.
            coveredTypeNames.insert(bindingPattern->typeName);
        } else if (auto typePattern = std::dynamic_pointer_cast<AST::TypePatternExpr>(matchCase->pattern)) {
            // Pattern matching specific types
            if (typePattern->type) {
                coveredTypeNames.insert(typePattern->type->typeName);
                // Also resolve the type to get its tag
                TypePtr resolvedType = resolveTypeAnnotation(typePattern->type);
                if (resolvedType) {
                    coveredTypeTags.insert(resolvedType->tag);
                }
            }
        } else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(matchCase->pattern)) {
            // Literal patterns - check if they match union variant types
            if (std::holds_alternative<std::string>(literalExpr->value)) {
                std::string literalValue = std::get<std::string>(literalExpr->value);
                coveredTypeNames.insert(literalValue);
            } else if (std::holds_alternative<std::nullptr_t>(literalExpr->value)) {
                // This is a wildcard pattern represented as nil literal
                hasWildcard = true;
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(matchCase->pattern)) {
            // Variable patterns - check for wildcard or specific variant names
            if (varExpr->name == "_") {
                hasWildcard = true;
            } else {
                // This is a type pattern like 'int', 'str', 'bool', 'f64'
                coveredTypeNames.insert(varExpr->name);
                
                // Map type names to type tags for better matching
                if (varExpr->name == "int") coveredTypeTags.insert(TypeTag::Int);
                else if (varExpr->name == "str") coveredTypeTags.insert(TypeTag::String);
                else if (varExpr->name == "bool") coveredTypeTags.insert(TypeTag::Bool);
                else if (varExpr->name == "f64") coveredTypeTags.insert(TypeTag::Float64);
                else if (varExpr->name == "float") coveredTypeTags.insert(TypeTag::Float64);
                else if (varExpr->name == "i64") coveredTypeTags.insert(TypeTag::Int64);
                else if (varExpr->name == "u64") coveredTypeTags.insert(TypeTag::UInt64);
            }
        }
    }
    
    // If we have a wildcard, the match is exhaustive
    if (hasWildcard) {
        return true;
    }
    
    // Check if all union variants are covered
    for (const auto& variantType : unionTypeInfo->types) {
        bool variantCovered = false;
        
        // Check by type tag (most reliable for primitive types)
        if (coveredTypeTags.find(variantType->tag) != coveredTypeTags.end()) {
            variantCovered = true;
        }
        
        // Check by type name
        std::string variantName = variantType->toString();
        if (coveredTypeNames.find(variantName) != coveredTypeNames.end()) {
            variantCovered = true;
        }
        
        // Additional checks for common type name variations
        if (variantType->tag == TypeTag::Int && 
            (coveredTypeNames.find("int") != coveredTypeNames.end() || 
             coveredTypeNames.find("Int") != coveredTypeNames.end())) {
            variantCovered = true;
        }
        
        if (variantType->tag == TypeTag::String && 
            (coveredTypeNames.find("str") != coveredTypeNames.end() || 
             coveredTypeNames.find("String") != coveredTypeNames.end())) {
            variantCovered = true;
        }
        
        if (variantType->tag == TypeTag::Bool && 
            (coveredTypeNames.find("bool") != coveredTypeNames.end() || 
             coveredTypeNames.find("Bool") != coveredTypeNames.end())) {
            variantCovered = true;
        }
        
        if (variantType->tag == TypeTag::Float64 && 
            (coveredTypeNames.find("f64") != coveredTypeNames.end() || 
             coveredTypeNames.find("Float64") != coveredTypeNames.end() ||
             coveredTypeNames.find("float") != coveredTypeNames.end())) {
            variantCovered = true;
        }
        
        if (!variantCovered) {
            return false;
        }
    }
    
    return true;
}

void TypeChecker::validateUnionVariantAccess(TypePtr unionType, const std::string& variantName, int line) {
    if (!unionType || unionType->tag != TypeTag::Union) {
        addError("Attempted to access variant '" + variantName + "' on non-union type " + 
                unionType->toString(), line);
        return;
    }
    
    const auto* unionTypeInfo = std::get_if<UnionType>(&unionType->extra);
    if (!unionTypeInfo) {
        addError("Invalid union type structure for variant access", line);
        return;
    }
    
    // Check if the variant exists in the union
    bool variantExists = false;
    for (const auto& variantType : unionTypeInfo->types) {
        if (variantType->toString() == variantName) {
            variantExists = true;
            break;
        }
    }
    
    if (!variantExists) {
        std::string availableVariants;
        for (size_t i = 0; i < unionTypeInfo->types.size(); ++i) {
            if (i > 0) availableVariants += ", ";
            availableVariants += unionTypeInfo->types[i]->toString();
        }
        
        addError("Variant '" + variantName + "' does not exist in union type " + 
                unionType->toString() + ". Available variants: " + availableVariants, line);
    }
}

void TypeChecker::validatePatternCompatibility(const std::shared_ptr<AST::Expression>& pattern, TypePtr matchType, int line) {
    if (!pattern || !matchType) {
        return;
    }
    
    // Validate that the pattern is compatible with the matched type
    if (auto bindingPattern = std::dynamic_pointer_cast<AST::BindingPatternExpr>(pattern)) {
        // For union types, validate that the variant exists
        if (isUnionType(matchType)) {
            validateUnionVariantAccess(matchType, bindingPattern->typeName, line);
        }
    } else if (auto typePattern = std::dynamic_pointer_cast<AST::TypePatternExpr>(pattern)) {
        // Type patterns should be compatible with the matched type
        if (typePattern->type) {
            TypePtr patternType = resolveTypeAnnotation(typePattern->type);
            if (patternType && !typeSystem.isCompatible(patternType, matchType) && 
                !typeSystem.isCompatible(matchType, patternType)) {
                // For union types, check if the pattern type is one of the variants
                if (isUnionType(matchType)) {
                    const auto* unionTypeInfo = std::get_if<UnionType>(&matchType->extra);
                    bool isVariant = false;
                    if (unionTypeInfo) {
                        for (const auto& variantType : unionTypeInfo->types) {
                            if (typeSystem.isCompatible(patternType, variantType)) {
                                isVariant = true;
                                break;
                            }
                        }
                    }
                    
                    if (!isVariant) {
                        addError("Pattern type " + patternType->toString() + 
                                " is not a variant of union type " + matchType->toString(), line);
                    }
                } else {
                    addError("Pattern type " + patternType->toString() + 
                            " is not compatible with matched type " + matchType->toString(), line);
                }
            }
        }
    }
}

std::string TypeChecker::getMissingUnionVariants(TypePtr unionType, const std::vector<std::shared_ptr<AST::MatchCase>>& cases) {
    if (!unionType || unionType->tag != TypeTag::Union) {
        return "";
    }
    
    const auto* unionTypeInfo = std::get_if<UnionType>(&unionType->extra);
    if (!unionTypeInfo) {
        return "";
    }
    
    std::set<TypeTag> coveredTypeTags;
    std::set<std::string> coveredTypeNames;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<AST::BindingPatternExpr>(matchCase->pattern)) {
            coveredTypeNames.insert(bindingPattern->typeName);
        } else if (auto typePattern = std::dynamic_pointer_cast<AST::TypePatternExpr>(matchCase->pattern)) {
            if (typePattern->type) {
                coveredTypeNames.insert(typePattern->type->typeName);
                TypePtr resolvedType = resolveTypeAnnotation(typePattern->type);
                if (resolvedType) {
                    coveredTypeTags.insert(resolvedType->tag);
                }
            }
        } else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(matchCase->pattern)) {
            // Check for wildcard pattern represented as nil literal
            if (std::holds_alternative<std::nullptr_t>(literalExpr->value)) {
                hasWildcard = true;
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_") {
                hasWildcard = true;
            } else {
                coveredTypeNames.insert(varExpr->name);
                
                // Map type names to type tags
                if (varExpr->name == "int") coveredTypeTags.insert(TypeTag::Int);
                else if (varExpr->name == "str") coveredTypeTags.insert(TypeTag::String);
                else if (varExpr->name == "bool") coveredTypeTags.insert(TypeTag::Bool);
                else if (varExpr->name == "f64") coveredTypeTags.insert(TypeTag::Float64);
                else if (varExpr->name == "float") coveredTypeTags.insert(TypeTag::Float64);
            }
        }
    }
    
    if (hasWildcard) {
        return ""; // Wildcard covers everything
    }
    
    std::vector<std::string> missingVariants;
    for (const auto& variantType : unionTypeInfo->types) {
        bool variantCovered = false;
        
        // Check by type tag
        if (coveredTypeTags.find(variantType->tag) != coveredTypeTags.end()) {
            variantCovered = true;
        }
        
        // Check by type name with variations
        if (variantType->tag == TypeTag::Int && 
            (coveredTypeNames.find("int") != coveredTypeNames.end() || 
             coveredTypeNames.find("Int") != coveredTypeNames.end())) {
            variantCovered = true;
        } else if (variantType->tag == TypeTag::String && 
                  (coveredTypeNames.find("str") != coveredTypeNames.end() || 
                   coveredTypeNames.find("String") != coveredTypeNames.end())) {
            variantCovered = true;
        } else if (variantType->tag == TypeTag::Bool && 
                  (coveredTypeNames.find("bool") != coveredTypeNames.end() || 
                   coveredTypeNames.find("Bool") != coveredTypeNames.end())) {
            variantCovered = true;
        } else if (variantType->tag == TypeTag::Float64 && 
                  (coveredTypeNames.find("f64") != coveredTypeNames.end() || 
                   coveredTypeNames.find("Float64") != coveredTypeNames.end() ||
                   coveredTypeNames.find("float") != coveredTypeNames.end())) {
            variantCovered = true;
        }
        
        if (!variantCovered) {
            // Use canonical type names for missing variants
            switch (variantType->tag) {
                case TypeTag::Int: missingVariants.push_back("int"); break;
                case TypeTag::String: missingVariants.push_back("str"); break;
                case TypeTag::Bool: missingVariants.push_back("bool"); break;
                case TypeTag::Float64: missingVariants.push_back("f64"); break;
                default: missingVariants.push_back(variantType->toString()); break;
            }
        }
    }
    
    std::string result;
    for (size_t i = 0; i < missingVariants.size(); ++i) {
        if (i > 0) result += ", ";
        result += missingVariants[i];
    }
    
    return result;
}

bool TypeChecker::isExhaustiveOptionMatch(const std::vector<std::shared_ptr<AST::MatchCase>>& cases) {
    bool hasSomeCase = false;
    bool hasNoneCase = false;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<AST::BindingPatternExpr>(matchCase->pattern)) {
            if (bindingPattern->typeName == "Some") {
                hasSomeCase = true;
            } else if (bindingPattern->typeName == "None") {
                hasNoneCase = true;
            }
        } else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(matchCase->pattern)) {
            // Check for wildcard pattern represented as nil literal
            if (std::holds_alternative<std::nullptr_t>(literalExpr->value)) {
                hasWildcard = true;
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_") {
                hasWildcard = true;
            }
        }
    }
    
    return (hasSomeCase && hasNoneCase) || hasWildcard;
}


void TypeChecker::checkClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& classDecl) {
    // Store the class declaration for visibility checking
    classDeclarations[classDecl->name] = classDecl;
    
    // Track which module this class is defined in
    classToModuleMap[classDecl->name] = currentModulePath;
    
    // Set current class context for visibility checking
    std::string previousClassName = currentClassName;
    auto previousClassDecl = currentClassDecl;
    currentClassName = classDecl->name;
    currentClassDecl = classDecl;
    
    // Register the class name as a callable constructor function
    // This allows the class name to be used as a function call for creating instances
    
    // Create a function signature for the class constructor
    FunctionSignature constructorSignature;
    constructorSignature.name = classDecl->name;
    constructorSignature.returnType = typeSystem.OBJECT_TYPE; // Classes return object instances
    
    // Check if the class has an 'init' method to determine constructor parameters
    for (const auto& method : classDecl->methods) {
        if (method->name == "init") {
            // Use the init method's parameters as constructor parameters
            for (const auto& param : method->params) {
                TypePtr paramType = typeSystem.ANY_TYPE;
                if (param.second) {
                    paramType = resolveTypeAnnotation(param.second);
                }
                constructorSignature.paramTypes.push_back(paramType);
                constructorSignature.optionalParams.push_back(false); // Regular parameters
                constructorSignature.hasDefaultValues.push_back(false);
            }
            
            // Handle optional parameters
            for (const auto& optParam : method->optionalParams) {
                TypePtr paramType = typeSystem.ANY_TYPE;
                if (optParam.second.first) {
                    paramType = resolveTypeAnnotation(optParam.second.first);
                }
                constructorSignature.paramTypes.push_back(paramType);
                constructorSignature.optionalParams.push_back(true); // Optional parameters
                constructorSignature.hasDefaultValues.push_back(optParam.second.second != nullptr);
            }
            break;
        }
    }
    
    // Register the constructor signature in the symbol table
    symbolTable.addFunction(classDecl->name, constructorSignature);
    
    // Type check all methods in the class (with class context set)
    for (const auto& method : classDecl->methods) {
        checkFunctionDeclaration(method);
    }
    
    // Restore previous class context
    currentClassName = previousClassName;
    currentClassDecl = previousClassDecl;
}

void TypeChecker::checkModuleDeclaration(const std::shared_ptr<AST::ModuleDeclaration>& moduleDecl) {
    // Store the module declaration for visibility checking
    moduleDeclarations[moduleDecl->name] = moduleDecl;
    
    // Check public members
    for (const auto& member : moduleDecl->publicMembers) {
        checkStatement(member);
    }
    
    // Check protected members
    for (const auto& member : moduleDecl->protectedMembers) {
        checkStatement(member);
    }
    
    // Check private members
    for (const auto& member : moduleDecl->privateMembers) {
        checkStatement(member);
    }
}
// Visibility enforcement methods

TypePtr TypeChecker::checkMemberAccess(const std::shared_ptr<AST::MemberExpr>& expr) {
    // First, check the object type
    TypePtr objectType = checkExpression(expr->object);
    
    if (!objectType) {
        addError("Cannot access member '" + expr->name + "' on invalid object", expr->line);
        return typeSystem.ANY_TYPE;
    }
    
    // Handle class member access using the new validateClassMemberAccess method
    if (objectType->tag == TypeTag::Object || objectType->tag == TypeTag::UserDefined) {
        // Use the new validateClassMemberAccess method for proper class-based validation
        bool accessValid = validateClassMemberAccess(expr);
        
        if (!accessValid) {
            // Error already reported by validateClassMemberAccess
            return typeSystem.ANY_TYPE;
        }
        
        // TODO: Return proper member type based on class field/method definitions
        return typeSystem.ANY_TYPE;
    }
    
    // Handle module member access
    if (objectType->tag == TypeTag::Module) {
        // Get the module name from the object expression
        std::string moduleName;
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->object)) {
            moduleName = varExpr->name; // This would be the module alias or name
        }
        
        if (!moduleName.empty()) {
            // Resolve the module alias to the actual module path
            std::string targetModulePath = resolveModuleAlias(moduleName);
            
            if (targetModulePath.empty()) {
                // Check if it's a direct module path (not an alias)
                targetModulePath = moduleName;
                
                // Verify the module exists in our registry
                if (moduleRegistry.find(targetModulePath) == moduleRegistry.end()) {
                    addError("Undefined module '" + moduleName + "'", expr->line);
                    return typeSystem.ANY_TYPE;
                }
            }
            
            // Get member visibility from the target module
            AST::VisibilityLevel memberVisibility = getModuleMemberVisibility(targetModulePath, expr->name);
            
            // Check if cross-module access is allowed
            if (memberVisibility == AST::VisibilityLevel::Private) {
                // Private members are not accessible across modules
                addError("Cannot access private member '" + expr->name + 
                        "' of module '" + moduleName + "' from different module", expr->line);
                return typeSystem.ANY_TYPE;
            } else if (memberVisibility == AST::VisibilityLevel::Protected) {
                // Protected members have limited cross-module access
                // For now, we'll be conservative and block cross-module protected access
                addError("Cannot access protected member '" + expr->name + 
                        "' of module '" + moduleName + "' from different module", expr->line);
                return typeSystem.ANY_TYPE;
            }
            
            // Public and const members are accessible across modules
            return typeSystem.ANY_TYPE;
        }
        
        // If we can't determine the module name, allow access for now
        return typeSystem.ANY_TYPE;
    }
    
    // Handle dict/object literal access
    if (objectType->tag == TypeTag::Dict) {
        // Dict access is always allowed
        return typeSystem.ANY_TYPE;
    }
    
    // For other types, allow access but warn if it doesn't make sense
    return typeSystem.ANY_TYPE;
}

bool TypeChecker::canAccessMember(const std::string& className, const std::string& memberName, AST::VisibilityLevel memberVisibility) {
    switch (memberVisibility) {
        case AST::VisibilityLevel::Public:
        case AST::VisibilityLevel::Const:
            return true; // Public and const members are always accessible across modules
            
        case AST::VisibilityLevel::Protected: {
            // Protected members are accessible from:
            // 1. The same class
            // 2. Subclasses (even across modules)
            // 3. The same module (file)
            
            if (!currentClassName.empty() && currentClassName == className) {
                return true; // Same class can always access
            }
            
            if (!currentClassName.empty() && currentClassDecl) {
                if (isSubclassOf(currentClassName, className)) {
                    return true; // Subclass can access protected members
                }
            }
            
            // Check if accessing from the same module
            auto classModuleIt = classToModuleMap.find(className);
            if (classModuleIt != classToModuleMap.end()) {
                return classModuleIt->second == currentModulePath;
            }
            
            return false;
        }
            
        case AST::VisibilityLevel::Private:
        default: {
            // Private members are accessible from:
            // 1. The same class
            // 2. The same module (file) - since each file is a module
            
            if (!currentClassName.empty() && currentClassName == className) {
                return true; // Same class can always access
            }
            
            // Check if accessing from the same module (file)
            auto classModuleIt = classToModuleMap.find(className);
            if (classModuleIt != classToModuleMap.end()) {
                return classModuleIt->second == currentModulePath;
            }
            
            return false;
        }
    }
}

bool TypeChecker::canAccessClassMember(const std::string& className, const std::string& memberName, AST::VisibilityLevel memberVisibility) {
    // Class-based access checking logic (independent from module rules)
    switch (memberVisibility) {
        case AST::VisibilityLevel::Public:
        case AST::VisibilityLevel::Const:
            return true; // Public and const members are always accessible
            
        case AST::VisibilityLevel::Protected: {
            // Protected members are accessible from:
            // 1. The same class
            // 2. Subclasses (even across modules)
            
            if (!currentClassName.empty() && currentClassName == className) {
                return true; // Same class can always access
            }
            
            if (!currentClassName.empty()) {
                if (isSubclassOf(currentClassName, className)) {
                    return true; // Subclass can access protected members
                }
            }
            
            return false; // Protected access denied
        }
            
        case AST::VisibilityLevel::Private:
        default: {
            // Private members are accessible only from the same class
            if (!currentClassName.empty() && currentClassName == className) {
                return true; // Same class can always access
            }
            
            return false; // Private access denied
        }
    }
}

bool TypeChecker::canAccessModuleMember(AST::VisibilityLevel visibility, const std::string& declaringModule, const std::string& accessingModule) {
    // Module-based access checking logic (independent from class rules)
    switch (visibility) {
        case AST::VisibilityLevel::Public:
        case AST::VisibilityLevel::Const:
            return true; // Public and const members are always accessible across modules
            
        case AST::VisibilityLevel::Protected:
            // Protected members are accessible within the same module
            return declaringModule == accessingModule;
            
        case AST::VisibilityLevel::Private:
        default:
            // Private members are only accessible within the same module
            return declaringModule == accessingModule;
    }
}

std::string TypeChecker::getCurrentClassName() {
    return currentClassName;
}

AST::VisibilityLevel TypeChecker::getModuleMemberVisibility(const std::string& moduleName, const std::string& memberName) {
    if (memberName.empty() || moduleName.empty()) {
        return AST::VisibilityLevel::Private;
    }
    
    // First try to get visibility from the extracted module registry
    auto moduleIt = moduleRegistry.find(moduleName);
    if (moduleIt != moduleRegistry.end()) {
        const ModuleVisibilityInfo& moduleInfo = moduleIt->second;
        
        // Check functions first
        auto funcIt = moduleInfo.functions.find(memberName);
        if (funcIt != moduleInfo.functions.end()) {
            return funcIt->second.visibility;
        }
        
        // Check variables
        auto varIt = moduleInfo.variables.find(memberName);
        if (varIt != moduleInfo.variables.end()) {
            return varIt->second.visibility;
        }
        
        // Check classes
        auto classIt = moduleInfo.classes.find(memberName);
        if (classIt != moduleInfo.classes.end()) {
            // For classes, we assume they are public by default unless explicitly marked
            // This is a design decision - classes are typically public to be usable
            return AST::VisibilityLevel::Public;
        }
    }
    
    // Fallback to legacy module declarations for backward compatibility
    auto legacyModuleIt = moduleDeclarations.find(moduleName);
    if (legacyModuleIt != moduleDeclarations.end()) {
        auto moduleDecl = legacyModuleIt->second;
        
        // Helper lambda to check member visibility in a list
        auto checkMemberInList = [&memberName](const std::vector<std::shared_ptr<AST::Statement>>& members) -> std::optional<AST::VisibilityLevel> {
            for (const auto& member : members) {
                if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(member)) {
                    if (varDecl->name == memberName) {
                        return varDecl->visibility; // Use the declaration's own visibility
                    }
                } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(member)) {
                    if (funcDecl->name == memberName) {
                        return funcDecl->visibility; // Use the declaration's own visibility
                    }
                } else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(member)) {
                    if (classDecl->name == memberName) {
                        // Classes don't have individual visibility, use the list they're in
                        return std::nullopt; // Will be handled by caller
                    }
                }
            }
            return std::nullopt;
        };
        
        // Check public members
        auto visibility = checkMemberInList(moduleDecl->publicMembers);
        if (visibility.has_value()) {
            return visibility.value();
        }
        // If found in public list but no individual visibility, it's public
        for (const auto& member : moduleDecl->publicMembers) {
            if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(member)) {
                if (classDecl->name == memberName) {
                    return AST::VisibilityLevel::Public;
                }
            }
        }
        
        // Check protected members
        visibility = checkMemberInList(moduleDecl->protectedMembers);
        if (visibility.has_value()) {
            return visibility.value();
        }
        // If found in protected list but no individual visibility, it's protected
        for (const auto& member : moduleDecl->protectedMembers) {
            if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(member)) {
                if (classDecl->name == memberName) {
                    return AST::VisibilityLevel::Protected;
                }
            }
        }
        
        // Check private members
        visibility = checkMemberInList(moduleDecl->privateMembers);
        if (visibility.has_value()) {
            return visibility.value();
        }
        // If found in private list but no individual visibility, it's private
        for (const auto& member : moduleDecl->privateMembers) {
            if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(member)) {
                if (classDecl->name == memberName) {
                    return AST::VisibilityLevel::Private;
                }
            }
        }
    }
    
    // All module members are private by default according to language design
    return AST::VisibilityLevel::Private;
}

bool TypeChecker::canAccessModuleMember(const std::string& moduleName, const std::string& memberName) {
    AST::VisibilityLevel memberVisibility = getModuleMemberVisibility(moduleName, memberName);
    
    switch (memberVisibility) {
        case AST::VisibilityLevel::Public:
        case AST::VisibilityLevel::Const:
            return true; // Public and const members are always accessible across modules
            
        case AST::VisibilityLevel::Protected:
            // Protected members are accessible from the same module
            return moduleName == currentModulePath;
            
        case AST::VisibilityLevel::Private:
        default:
            // Private members are only accessible from the same module
            return moduleName == currentModulePath;
    }
}

bool TypeChecker::isSubclassOf(const std::string& subclass, const std::string& superclass) {
    if (subclass == superclass) {
        return true; // A class is considered a subclass of itself
    }
    
    // Find the subclass declaration
    auto subclassIt = classDeclarations.find(subclass);
    if (subclassIt == classDeclarations.end()) {
        return false; // Subclass not found
    }
    
    auto subclassDecl = subclassIt->second;
    
    // Check if it has a superclass
    if (subclassDecl->superClassName.empty()) {
        return false; // No inheritance
    }
    
    // Check if the direct superclass matches
    if (subclassDecl->superClassName == superclass) {
        return true;
    }
    
    // Recursively check the inheritance chain
    return isSubclassOf(subclassDecl->superClassName, superclass);
}

AST::VisibilityLevel TypeChecker::getTopLevelDeclarationVisibility(const std::string& name) {
    // Check top-level variables
    auto varIt = topLevelVariables.find(name);
    if (varIt != topLevelVariables.end()) {
        return varIt->second->visibility;
    }
    
    // Check top-level functions
    auto funcIt = topLevelFunctions.find(name);
    if (funcIt != topLevelFunctions.end()) {
        return funcIt->second->visibility;
    }
    
    // Check top-level classes
    auto classIt = classDeclarations.find(name);
    if (classIt != classDeclarations.end()) {
        // Classes don't have individual visibility at top level, they're public by default
        // unless they're inside a module
        return AST::VisibilityLevel::Public;
    }
    
    // Default to private if not found
    return AST::VisibilityLevel::Private;
}

bool TypeChecker::canAccessFromCurrentModule(AST::VisibilityLevel visibility, const std::string& declaringModule) {
    switch (visibility) {
        case AST::VisibilityLevel::Public:
        case AST::VisibilityLevel::Const:
            return true; // Public and const members are accessible from any module
            
        case AST::VisibilityLevel::Protected:
            // Protected members are accessible from the same module or subclasses
            // For now, we'll allow access from the same module and let inheritance handle the rest
            if (declaringModule.empty() || currentModulePath.empty()) {
                return true; // Conservative approach when module info is missing
            }
            return declaringModule == currentModulePath;
            
        case AST::VisibilityLevel::Private:
        default:
            // Private members are only accessible from the same module (file)
            if (declaringModule.empty() || currentModulePath.empty()) {
                return true; // Conservative approach when module info is missing
            }
            return declaringModule == currentModulePath;
    }
}

bool TypeChecker::isValidModuleFunctionReference(const std::string& functionRef) {
    // Check if this is a module function reference (format: "module_function:functionName")
    if (functionRef.substr(0, 16) == "module_function:") {
        std::string functionName = functionRef.substr(16);
        
        // Validate that the function name is not empty
        if (functionName.empty()) {
            return false;
        }
        
        // Check if the function exists in any loaded module
        for (const auto& [modulePath, moduleInfo] : moduleRegistry) {
            auto funcIt = moduleInfo.functions.find(functionName);
            if (funcIt != moduleInfo.functions.end()) {
                // Check if the function is accessible (public or const)
                AST::VisibilityLevel visibility = funcIt->second.visibility;
                return (visibility == AST::VisibilityLevel::Public || 
                        visibility == AST::VisibilityLevel::Const);
            }
        }
        
        return false; // Function not found in any module
    }
    
    return false; // Not a module function reference
}

std::string TypeChecker::extractModuleFunctionName(const std::string& functionRef) {
    // Extract function name from module function reference
    if (functionRef.substr(0, 16) == "module_function:") {
        return functionRef.substr(16);
    }
    return ""; // Not a module function reference
}

void TypeChecker::validateImportFilter(const AST::ImportFilter& filter, const std::string& modulePath) {
    // Get module visibility info
    auto moduleIt = moduleRegistry.find(modulePath);
    if (moduleIt == moduleRegistry.end()) {
        return; // Module not loaded, can't validate
    }
    
    const ModuleVisibilityInfo& moduleInfo = moduleIt->second;
    
    // Collect all public/const symbols from the module
    std::set<std::string> availableSymbols;
    
    // Add public/const functions
    for (const auto& [funcName, funcInfo] : moduleInfo.functions) {
        if (funcInfo.visibility == AST::VisibilityLevel::Public || 
            funcInfo.visibility == AST::VisibilityLevel::Const) {
            availableSymbols.insert(funcName);
        }
    }
    
    // Add public/const variables
    for (const auto& [varName, varInfo] : moduleInfo.variables) {
        if (varInfo.visibility == AST::VisibilityLevel::Public || 
            varInfo.visibility == AST::VisibilityLevel::Const) {
            availableSymbols.insert(varName);
        }
    }
    
    // Validate filter identifiers
    for (const std::string& identifier : filter.identifiers) {
        if (availableSymbols.find(identifier) == availableSymbols.end()) {
            if (filter.type == AST::ImportFilterType::Show) {
                addError("Cannot import '" + identifier + "' from module '" + modulePath + 
                        "': symbol not found or not accessible", 0);
            }
            // For hide filters, we don't error on non-existent symbols
        }
    }
}

void TypeChecker::checkModuleMemberFunctionCall(const std::shared_ptr<AST::MemberExpr>& memberExpr, 
                                               const std::vector<TypePtr>& argTypes, 
                                               const std::shared_ptr<AST::CallExpr>& callExpr) {
    // Get the object name from the member expression
    std::string objectName;
    if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(memberExpr->object)) {
        objectName = varExpr->name;
    } else {
        addError("Invalid object reference in function call", callExpr->line);
        return;
    }
    
    // First check if this is actually a module (not an object instance)
    TypePtr objectType = symbolTable.getType(objectName);
    if (!objectType || objectType->tag != TypeTag::Module) {
        // This is not a module call - it's likely an object method call
        // Let the regular expression checking handle it
        return;
    }
    
    // Resolve module alias to actual path
    std::string targetModulePath = resolveModuleAlias(objectName);
    if (targetModulePath.empty()) {
        addError("Undefined module '" + objectName + "' in function call", callExpr->line);
        return;
    }
    
    // Check if the function exists in the target module
    auto moduleIt = moduleRegistry.find(targetModulePath);
    if (moduleIt == moduleRegistry.end()) {
        addError("Module '" + objectName + "' not loaded", callExpr->line);
        return;
    }
    
    const ModuleVisibilityInfo& moduleInfo = moduleIt->second;
    auto funcIt = moduleInfo.functions.find(memberExpr->name);
    if (funcIt == moduleInfo.functions.end()) {
        addError("Function '" + memberExpr->name + "' not found in module '" + objectName + "'", callExpr->line);
        return;
    }
    
    const MemberVisibilityInfo& funcInfo = funcIt->second;
    
    // Check visibility
    if (funcInfo.visibility == AST::VisibilityLevel::Private) {
        addError("Cannot access private function '" + memberExpr->name + 
                "' from module '" + objectName + "'", callExpr->line);
        return;
    }
    
    // TODO: Add parameter count and type validation here
    // For now, we'll just validate that the function is accessible
}

TypePtr TypeChecker::checkClassMethodCall(const std::shared_ptr<AST::MemberExpr>& memberExpr,
                                          const std::vector<TypePtr>& argTypes,
                                          const std::shared_ptr<AST::CallExpr>& callExpr) {
    // 1. Get object and class information
    TypePtr objectType = checkExpression(memberExpr->object);
    if (!objectType || (objectType->tag != TypeTag::Object && objectType->tag != TypeTag::UserDefined)) {
        // This isn't a class instance, so it can't be a method call.
        // Let other parts of the type checker handle it (e.g., function-typed fields).
        return typeSystem.ANY_TYPE;
    }

    std::string className;
    if (objectType->tag == TypeTag::UserDefined) {
        if (std::holds_alternative<UserDefinedType>(objectType->extra)) {
            className = std::get<UserDefinedType>(objectType->extra).name;
        }
    }

    if (className.empty()) {
        addError("Could not determine class for method call '" + memberExpr->name + "'", callExpr->line);
        return typeSystem.ANY_TYPE;
    }

    // 2. Find the method and check for its existence
    auto classIt = classDeclarations.find(className);
    if (classIt == classDeclarations.end()) {
        addError("Class '" + className + "' not found for method call.", callExpr->line);
        return typeSystem.ANY_TYPE;
    }
    auto classDecl = classIt->second;

    std::shared_ptr<AST::FunctionDeclaration> methodDecl = nullptr;
    for (const auto& method : classDecl->methods) {
        if (method->name == memberExpr->name) {
            methodDecl = method;
            break;
        }
    }

    if (!methodDecl) {
        addError("Method '" + memberExpr->name + "' not found in class '" + className + "'", callExpr->line);
        return typeSystem.ANY_TYPE;
    }

    // 3. Check visibility
    AST::VisibilityLevel visibility = getMemberVisibility(className, memberExpr->name);
    if (!canAccessClassMember(className, memberExpr->name, visibility)) {
        std::string visibilityStr = "private";
        if (visibility == AST::VisibilityLevel::Protected) {
            visibilityStr = "protected";
        }
        addError("Cannot access " + visibilityStr + " method '" + memberExpr->name + "' of class '" + className + "'", callExpr->line);
        return typeSystem.ANY_TYPE;
    }

    // 4. Check arguments
    // Construct a temporary FunctionSignature for validation
    std::vector<TypePtr> paramTypes;
    for (const auto& param : methodDecl->params) {
        paramTypes.push_back(param.second ? resolveTypeAnnotation(param.second) : typeSystem.ANY_TYPE);
    }
     for (const auto& optParam : methodDecl->optionalParams) {
        paramTypes.push_back(optParam.second.first ? resolveTypeAnnotation(optParam.second.first) : typeSystem.ANY_TYPE);
    }

    if (argTypes.size() != paramTypes.size()) {
         addError("Method '" + methodDecl->name + "' expects " + std::to_string(paramTypes.size()) + " arguments, but got " + std::to_string(argTypes.size()), callExpr->line);
        return typeSystem.ANY_TYPE;
    }

    for (size_t i = 0; i < argTypes.size(); ++i) {
        if (!typeSystem.isCompatible(argTypes[i], paramTypes[i])) {
            addError("Argument " + std::to_string(i + 1) + " type mismatch in call to '" + methodDecl->name + "': expected " +
                     paramTypes[i]->toString() + ", got " + argTypes[i]->toString(),
                     callExpr->line);
        }
    }


    // 5. Return type
    if (methodDecl->returnType && *methodDecl->returnType) {
        return resolveTypeAnnotation(*methodDecl->returnType);
    }

    return typeSystem.NIL_TYPE;
}

void TypeChecker::checkImportStatement(const std::shared_ptr<AST::ImportStatement>& importStmt) {
    // Handle the import during type checking phase
    handleImportStatement(importStmt);
    
    // Determine the alias name (same logic as in handleImportStatement)
    std::string aliasName;
    if (importStmt->alias) {
        aliasName = *importStmt->alias;
    } else {
        // Use the last component of the module path as the default alias
        size_t lastDot = importStmt->modulePath.find_last_of('.');
        if (lastDot != std::string::npos) {
            aliasName = importStmt->modulePath.substr(lastDot + 1);
        } else {
            aliasName = importStmt->modulePath;
        }
    }
    
    // Register the module alias as a variable of Module type in the current scope
    // This allows expressions like `math.add()` to be type-checked properly
    symbolTable.addVariable(aliasName, typeSystem.MODULE_TYPE, importStmt->line);
}

AST::VisibilityLevel TypeChecker::getMemberVisibility(const std::string& className, const std::string& memberName) {
    if (memberName.empty() || className.empty()) {
        return AST::VisibilityLevel::Private;
    }
    
    // First try to get visibility from the extracted class registry
    auto classIt = classRegistry.find(className);
    if (classIt != classRegistry.end()) {
        const ClassVisibilityInfo& classInfo = classIt->second;
        
        // Check fields first
        auto fieldIt = classInfo.fields.find(memberName);
        if (fieldIt != classInfo.fields.end()) {
            return fieldIt->second.visibility;
        }
        
        // Check methods
        auto methodIt = classInfo.methods.find(memberName);
        if (methodIt != classInfo.methods.end()) {
            return methodIt->second.visibility;
        }
    }
    
    // Fallback to legacy class declarations for backward compatibility
    auto legacyClassIt = classDeclarations.find(className);
    if (legacyClassIt != classDeclarations.end()) {
        auto classDecl = legacyClassIt->second;
        
        // First check the class-level visibility maps (these take precedence)
        auto fieldVisIt = classDecl->fieldVisibility.find(memberName);
        if (fieldVisIt != classDecl->fieldVisibility.end()) {
            return fieldVisIt->second;
        }
        
        auto methodVisIt = classDecl->methodVisibility.find(memberName);
        if (methodVisIt != classDecl->methodVisibility.end()) {
            return methodVisIt->second;
        }
        
        // If not found in visibility maps, check individual field/method declarations
        // Check fields
        for (const auto& field : classDecl->fields) {
            if (field->name == memberName) {
                return field->visibility;
            }
        }
        
        // Check methods
        for (const auto& method : classDecl->methods) {
            if (method->name == memberName) {
                return method->visibility;
            }
        }
    }
    
    // All members are private by default according to language design
    return AST::VisibilityLevel::Private;
}

// Visibility information extraction methods

void TypeChecker::extractModuleVisibility(const std::shared_ptr<AST::Program>& program) {
    // Create or get module visibility info for current module
    ModuleVisibilityInfo& moduleInfo = moduleRegistry[currentModulePath];
    moduleInfo.modulePath = currentModulePath;
    
    // Traverse Program AST node to extract top-level declarations
    for (const auto& stmt : program->statements) {
        if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            extractFunctionVisibility(funcDecl);
        } else if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
            extractVariableVisibility(varDecl);
        } else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) {
            extractClassVisibility(classDecl);
        } else if (auto importStmt = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) {
            handleImportStatement(importStmt);
        }
    }
}

void TypeChecker::extractClassVisibility(const std::shared_ptr<AST::ClassDeclaration>& classDecl) {
    // Create class visibility info
    ClassVisibilityInfo classInfo(classDecl->name, currentModulePath, classDecl->superClassName);
    
    // Extract field visibility information
    for (const auto& field : classDecl->fields) {
        AST::VisibilityLevel fieldVisibility = AST::VisibilityLevel::Private; // Default
        
        // Check if field has explicit visibility in the class declaration
        auto visibilityIt = classDecl->fieldVisibility.find(field->name);
        if (visibilityIt != classDecl->fieldVisibility.end()) {
            fieldVisibility = visibilityIt->second;
        } else {
            // Use field's own visibility if available
            fieldVisibility = field->visibility;
        }
        
        MemberVisibilityInfo memberInfo(field->name, fieldVisibility, currentModulePath, classDecl->name, field->line);
        classInfo.fields[field->name] = memberInfo;
    }
    
    // Extract method visibility information
    for (const auto& method : classDecl->methods) {
        AST::VisibilityLevel methodVisibility = AST::VisibilityLevel::Private; // Default
        
        // Check if method has explicit visibility in the class declaration
        auto visibilityIt = classDecl->methodVisibility.find(method->name);
        if (visibilityIt != classDecl->methodVisibility.end()) {
            methodVisibility = visibilityIt->second;
        } else {
            // Use method's own visibility if available
            methodVisibility = method->visibility;
        }
        
        MemberVisibilityInfo memberInfo(method->name, methodVisibility, currentModulePath, classDecl->name, method->line);
        classInfo.methods[method->name] = memberInfo;
    }
    
    // Store class visibility information in registries
    classRegistry[classDecl->name] = classInfo;
    classToModuleMap[classDecl->name] = currentModulePath;
    
    // Also store in module registry
    ModuleVisibilityInfo& moduleInfo = moduleRegistry[currentModulePath];
    moduleInfo.classes[classDecl->name] = classInfo;
}

void TypeChecker::extractFunctionVisibility(const std::shared_ptr<AST::FunctionDeclaration>& funcDecl) {
    // Handle default visibility rules (private for module members)
    AST::VisibilityLevel visibility = funcDecl->visibility;
    if (visibility == AST::VisibilityLevel::Private && funcDecl->visibility == AST::VisibilityLevel::Private) {
        // Default to private for module-level functions
        visibility = AST::VisibilityLevel::Private;
    }
    
    // Create member visibility info
    MemberVisibilityInfo memberInfo(funcDecl->name, visibility, currentModulePath, "", funcDecl->line);
    
    // Store in module registry
    ModuleVisibilityInfo& moduleInfo = moduleRegistry[currentModulePath];
    moduleInfo.functions[funcDecl->name] = memberInfo;
}

void TypeChecker::extractVariableVisibility(const std::shared_ptr<AST::VarDeclaration>& varDecl) {
    // Handle default visibility rules (private for module members)
    AST::VisibilityLevel visibility = varDecl->visibility;
    if (visibility == AST::VisibilityLevel::Private && varDecl->visibility == AST::VisibilityLevel::Private) {
        // Default to private for module-level variables
        visibility = AST::VisibilityLevel::Private;
    }
    
    // Create member visibility info
    MemberVisibilityInfo memberInfo(varDecl->name, visibility, currentModulePath, "", varDecl->line);
    
    // Store in module registry
    ModuleVisibilityInfo& moduleInfo = moduleRegistry[currentModulePath];
    moduleInfo.variables[varDecl->name] = memberInfo;
}
// Import  handling methods

void TypeChecker::handleImportStatement(const std::shared_ptr<AST::ImportStatement>& importStmt) {
    // Resolve the module path to actual file path
    std::string actualModulePath = resolveModulePath(importStmt->modulePath);
    
    // Determine the alias name
    std::string aliasName;
    if (importStmt->alias) {
        aliasName = *importStmt->alias;
    } else {
        // Use the last component of the module path as the default alias
        size_t lastDot = importStmt->modulePath.find_last_of('.');
        if (lastDot != std::string::npos) {
            aliasName = importStmt->modulePath.substr(lastDot + 1);
        } else {
            aliasName = importStmt->modulePath;
        }
    }
    
    // Store the alias mapping
    moduleAliases[aliasName] = actualModulePath;
    
    // Load visibility information for the imported module
    loadModuleVisibilityInfo(actualModulePath);
    
    // Validate import filters against available symbols
    if (importStmt->filter) {
        validateImportFilter(*importStmt->filter, actualModulePath);
    }
}

std::string TypeChecker::resolveModulePath(const std::string& modulePath) {
    // Convert module path (e.g., "tests.modules.math_module") to file path
    std::string filePath = modulePath;
    
    // Replace dots with directory separators
    for (char& c : filePath) {
        if (c == '.') {
            c = '/';
        }
    }
    
    // Add .lm extension
    filePath += ".lm";
    
    return filePath;
}

std::string TypeChecker::resolveModuleAlias(const std::string& alias) {
    auto it = moduleAliases.find(alias);
    if (it != moduleAliases.end()) {
        return it->second;
    }
    return ""; // Alias not found
}

void TypeChecker::loadModuleVisibilityInfo(const std::string& modulePath) {
    // Check if we already have visibility info for this module
    if (moduleRegistry.find(modulePath) != moduleRegistry.end()) {
        return; // Already loaded
    }
    
    // Load and parse the module to extract visibility information
    std::ifstream file(modulePath);
    if (!file.is_open()) {
        // Module file not found - this will be handled elsewhere
        return;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    // Parse the module
    Scanner scanner(source);
    scanner.scanTokens();
    Parser parser(scanner);
    auto moduleAst = parser.parse();
    
    // Temporarily set the current module path to the imported module
    std::string originalModulePath = currentModulePath;
    currentModulePath = modulePath;
    
    // Extract visibility information from the imported module
    extractModuleVisibility(moduleAst);
    
    // Restore the original module path
    currentModulePath = originalModulePath;
}

// Core access validation logic methods

bool TypeChecker::validateClassMemberAccess(const std::shared_ptr<AST::MemberExpr>& expr) {
    // Check class member access against stored visibility rules using only class-based context
    // Validate access context (same class, subclass) without considering module boundaries
    // Return validation result with error details
    // Ensure no mixing of class and module visibility rules
    
    // First, determine the class type of the object being accessed
    TypePtr objectType = checkExpression(expr->object);
    if (!objectType) {
        addError("Cannot access member '" + expr->name + "' on invalid object", expr->line);
        return false;
    }
    
    // Only handle class member access - not module or other types
    // This ensures no mixing of class and module visibility rules
    if (objectType->tag != TypeTag::Object && objectType->tag != TypeTag::UserDefined) {
        return true; // Not a class member access, let other validators handle it
    }
    
    // Extract class name from the object type
    std::string className;
    if (objectType->tag == TypeTag::UserDefined) {
        if (std::holds_alternative<UserDefinedType>(objectType->extra)) {
            auto userType = std::get<UserDefinedType>(objectType->extra);
            className = userType.name;
        }
    } else if (objectType->tag == TypeTag::Object) {
        // Try to infer class name from variable expression
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->object)) {
            TypePtr varType = symbolTable.getType(varExpr->name);
            if (varType) {
                if (varType->tag == TypeTag::UserDefined) {
                    if (std::holds_alternative<UserDefinedType>(varType->extra)) {
                        auto userType = std::get<UserDefinedType>(varType->extra);
                        className = userType.name;
                    }
                } else if (varType->tag == TypeTag::Object) {
                    // For Object types, we cannot determine the class name
                    // This should not happen with proper type tracking
                    // If we reach here, it means the type system needs improvement
                    return true; // Let other validators handle it
                }
            }
        }
    }
    
    if (className.empty()) {
        // Cannot determine class name - this might not be a class member access
        return true; // Let other validators handle non-class member access
    }
    
    // Get member visibility from class registry (class-based context only)
    // This uses stored visibility rules from AST extraction
    AST::VisibilityLevel memberVisibility = getMemberVisibility(className, expr->name);
    
    // Check if the member exists in the class using both new and legacy systems
    bool memberExists = false;
    bool isField = false;
    bool isMethod = false;
    
    // Check new class registry first
    auto classIt = classRegistry.find(className);
    if (classIt != classRegistry.end()) {
        const ClassVisibilityInfo& classInfo = classIt->second;
        if (classInfo.fields.find(expr->name) != classInfo.fields.end()) {
            memberExists = true;
            isField = true;
        } else if (classInfo.methods.find(expr->name) != classInfo.methods.end()) {
            memberExists = true;
            isMethod = true;
        }
    }
    
    // If member doesn't exist in class registry, check legacy declarations
    if (!memberExists) {
        auto legacyClassIt = classDeclarations.find(className);
        if (legacyClassIt != classDeclarations.end()) {
            auto classDecl = legacyClassIt->second;
            
            // Check fields
            for (const auto& field : classDecl->fields) {
                if (field->name == expr->name) {
                    memberExists = true;
                    isField = true;
                    break;
                }
            }
            
            // Check methods if not found in fields
            if (!memberExists) {
                for (const auto& method : classDecl->methods) {
                    if (method->name == expr->name) {
                        memberExists = true;
                        isMethod = true;
                        break;
                    }
                }
            }
        }
    }
    
    // If member doesn't exist, report error with helpful context
    if (!memberExists) {
        addError("Class '" + className + "' has no member named '" + expr->name + "'", expr->line);
        return false;
    }
    
    // Validate access context using only class-based rules (no module boundaries)
    // This ensures proper separation between class and module visibility systems
    bool accessAllowed = canAccessClassMember(className, expr->name, memberVisibility);
    
    if (!accessAllowed) {
        // Return validation result with error details
        std::string visibilityStr;
        switch (memberVisibility) {
            case AST::VisibilityLevel::Private:
                visibilityStr = "private";
                break;
            case AST::VisibilityLevel::Protected:
                visibilityStr = "protected";
                break;
            case AST::VisibilityLevel::Public:
                visibilityStr = "public";
                break;
            case AST::VisibilityLevel::Const:
                visibilityStr = "const";
                break;
        }
        
        // Provide detailed context information for error reporting
        std::string memberType = isField ? "field" : (isMethod ? "method" : "member");
        std::string contextInfo;
        std::string accessSuggestion;
        
        if (currentClassName.empty()) {
            contextInfo = "from outside any class";
            if (memberVisibility == AST::VisibilityLevel::Protected) {
                accessSuggestion = " (protected " + memberType + "s can only be accessed from the same class or subclasses)";
            } else if (memberVisibility == AST::VisibilityLevel::Private) {
                accessSuggestion = " (private " + memberType + "s can only be accessed from within the same class)";
            }
        } else {
            contextInfo = "from class '" + currentClassName + "'";
            if (memberVisibility == AST::VisibilityLevel::Protected) {
                if (!isSubclassOf(currentClassName, className)) {
                    accessSuggestion = " (protected " + memberType + "s require inheritance relationship - '" + 
                                     currentClassName + "' must inherit from '" + className + "')";
                } else {
                    // This shouldn't happen if canAccessClassMember is working correctly
                    accessSuggestion = " (inheritance check failed)";
                }
            } else if (memberVisibility == AST::VisibilityLevel::Private) {
                if (currentClassName != className) {
                    accessSuggestion = " (private " + memberType + "s can only be accessed from within the same class '" + className + "')";
                } else {
                    // This shouldn't happen if canAccessClassMember is working correctly
                    accessSuggestion = " (same class check failed)";
                }
            }
        }
        
        addError("Cannot access " + visibilityStr + " " + memberType + " '" + expr->name + 
                "' of class '" + className + "' " + contextInfo + accessSuggestion, expr->line);
        return false;
    }
    
    return true;
}

bool TypeChecker::validateModuleFunctionCall(const std::shared_ptr<AST::CallExpr>& expr) {
    // Validate module-level function call access based on function visibility
    
    // Check if this is a direct function call (not a method call)
    auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee);
    if (!varExpr) {
        return true; // Not a direct function call, let other validators handle it
    }
    
    // Check if it's a function-typed variable (higher-order function)
    TypePtr varType = symbolTable.getType(varExpr->name);
    if (varType && varType->tag == TypeTag::Function) {
        return true; // Function-typed variable, not a module function
    }
    
    // Check if it's a regular function signature
    FunctionSignature* signature = symbolTable.findFunction(varExpr->name);
    if (!signature) {
        return true; // Function not found, let other error handling deal with it
    }
    
    // Distinguish between class method calls and module function calls
    if (!currentClassName.empty()) {
        // We're inside a class - check if this is a method of the current class
        AST::VisibilityLevel methodVisibility = getMemberVisibility(currentClassName, varExpr->name);
        if (methodVisibility != AST::VisibilityLevel::Private || 
            classRegistry.find(currentClassName) != classRegistry.end()) {
            // This might be a method call, not a module function call
            return true;
        }
    }
    
    // Check module-level function access rules using only module-based context
    AST::VisibilityLevel funcVisibility = getModuleMemberVisibility(currentModulePath, varExpr->name);
    
    // Get the declaring module of the function
    std::string declaringModule = currentModulePath; // Default to current module
    auto moduleIt = moduleRegistry.find(currentModulePath);
    if (moduleIt != moduleRegistry.end()) {
        auto funcIt = moduleIt->second.functions.find(varExpr->name);
        if (funcIt != moduleIt->second.functions.end()) {
            declaringModule = funcIt->second.declaringModule;
        }
    }
    
    // Validate access using module-based rules only
    bool accessAllowed = canAccessModuleMember(funcVisibility, declaringModule, currentModulePath);
    
    if (!accessAllowed) {
        std::string visibilityStr;
        switch (funcVisibility) {
            case AST::VisibilityLevel::Private:
                visibilityStr = "private";
                break;
            case AST::VisibilityLevel::Protected:
                visibilityStr = "protected";
                break;
            case AST::VisibilityLevel::Public:
                visibilityStr = "public";
                break;
            case AST::VisibilityLevel::Const:
                visibilityStr = "const";
                break;
        }
        
        addError("Cannot access " + visibilityStr + " function '" + varExpr->name + 
                "' from module '" + currentModulePath + "' (declared in '" + declaringModule + "')", 
                expr->line);
        return false;
    }
    
    return true;
}

bool TypeChecker::validateModuleVariableAccess(const std::shared_ptr<AST::VariableExpr>& expr) {
    // Validate module-level variable access based on variable visibility
    
    // Check if this is a local variable (in current scope)
    TypePtr varType = symbolTable.getType(expr->name);
    if (varType) {
        // Check if this is actually a module-level variable
        auto moduleIt = moduleRegistry.find(currentModulePath);
        if (moduleIt != moduleRegistry.end()) {
            auto varIt = moduleIt->second.variables.find(expr->name);
            if (varIt == moduleIt->second.variables.end()) {
                return true; // Not a module-level variable, it's a local variable
            }
        } else {
            return true; // No module registry info, assume it's local
        }
    }
    
    // Distinguish between class field access and module variable access
    if (!currentClassName.empty()) {
        // We're inside a class - check if this is a field of the current class
        AST::VisibilityLevel fieldVisibility = getMemberVisibility(currentClassName, expr->name);
        if (fieldVisibility != AST::VisibilityLevel::Private || 
            classRegistry.find(currentClassName) != classRegistry.end()) {
            // This might be a field access, not a module variable access
            return true;
        }
    }
    
    // Check module-level variable access rules using only module-based context
    AST::VisibilityLevel varVisibility = getModuleMemberVisibility(currentModulePath, expr->name);
    
    // Get the declaring module of the variable
    std::string declaringModule = currentModulePath; // Default to current module
    auto moduleIt = moduleRegistry.find(currentModulePath);
    if (moduleIt != moduleRegistry.end()) {
        auto varIt = moduleIt->second.variables.find(expr->name);
        if (varIt != moduleIt->second.variables.end()) {
            declaringModule = varIt->second.declaringModule;
        }
    }
    
    // Validate access using module-based rules only
    bool accessAllowed = canAccessModuleMember(varVisibility, declaringModule, currentModulePath);
    
    if (!accessAllowed) {
        std::string visibilityStr;
        switch (varVisibility) {
            case AST::VisibilityLevel::Private:
                visibilityStr = "private";
                break;
            case AST::VisibilityLevel::Protected:
                visibilityStr = "protected";
                break;
            case AST::VisibilityLevel::Public:
                visibilityStr = "public";
                break;
            case AST::VisibilityLevel::Const:
                visibilityStr = "const";
                break;
        }
        
        addError("Cannot access " + visibilityStr + " variable '" + expr->name + 
                "' from module '" + currentModulePath + "' (declared in '" + declaringModule + "')", 
                expr->line);
        return false;
    }
    
    return true;
}