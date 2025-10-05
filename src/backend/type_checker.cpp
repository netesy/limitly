#include "type_checker.hh"
#include "types.hh"
#include <algorithm>
#include <sstream>
#include <string>
#include <variant>

void TypeChecker::addError(const std::string& message, int line, int column, const std::string& context) {
    errors.emplace_back(message, line, column, context);
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
}

void TypeChecker::enterScope() {
    currentScope = std::make_shared<Scope>(currentScope);
}

void TypeChecker::exitScope() {
    if (currentScope->parent) {
        currentScope = currentScope->parent;
    }
}

std::vector<TypeCheckError> TypeChecker::checkProgram(const std::shared_ptr<AST::Program>& program) {
    errors.clear();
    
    // First pass: collect all function signatures
    for (const auto& stmt : program->statements) {
        if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            // Extract function signature information
            std::vector<TypePtr> paramTypes;
            for (const auto& param : funcDecl->params) {
                if (param.second) {
                    // Convert TypeAnnotation to TypePtr
                    TypePtr paramType = resolveTypeAnnotation(param.second);
                    paramTypes.push_back(paramType);
                } else {
                    paramTypes.push_back(typeSystem.ANY_TYPE);
                }
            }
            
            TypePtr returnType = typeSystem.NIL_TYPE;
            bool canFail = funcDecl->canFail || funcDecl->throws;
            std::vector<std::string> errorTypes = funcDecl->declaredErrorTypes;
            
            if (funcDecl->returnType && *funcDecl->returnType) {
                returnType = resolveTypeAnnotation(*funcDecl->returnType);
                
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
            
            currentScope->functions.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(funcDecl->name),
                std::forward_as_tuple(funcDecl->name, paramTypes, returnType, canFail, errorTypes, funcDecl->line)
            );
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
        // Create function type with parameter types and return type
        std::vector<TypePtr> paramTypes;
        for (const auto& param : annotation->functionParams) {
            paramTypes.push_back(resolveTypeAnnotation(param));
        }
        
        TypePtr returnType = typeSystem.NIL_TYPE;
        if (annotation->returnType) {
            returnType = resolveTypeAnnotation(annotation->returnType);
        }
        
        return typeSystem.createFunctionType(paramTypes, returnType);
    }
    
    // Handle basic types
    TypePtr baseType = typeSystem.getType(annotation->typeName);
    
    // Handle error union types (Type? or Type?Error1,Error2)
    if (annotation->isFallible) {
        std::vector<std::string> errorTypeNames = annotation->errorTypes;
        bool isGeneric = errorTypeNames.empty();
        
        return typeSystem.createErrorUnionType(baseType, errorTypeNames, isGeneric);
    }
    
    return baseType;
}

void TypeChecker::checkStatement(const std::shared_ptr<AST::Statement>& stmt) {
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        TypePtr varType = typeSystem.ANY_TYPE;
        
        if (varDecl->type && *varDecl->type) {
            varType = resolveTypeAnnotation(*varDecl->type);
        }
        
        if (varDecl->initializer) {
            TypePtr initType = checkExpression(varDecl->initializer);
            
            // Check for unhandled fallible expressions in variable declarations
            if (requiresErrorHandling(initType)) {
                // Check if this is a function call that returns an error union
                if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(varDecl->initializer)) {
                    if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
                        FunctionSignature* signature = currentScope->getFunctionSignature(varExpr->name);
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
            
            // Enhanced type compatibility checking for error unions
            if (varType != typeSystem.ANY_TYPE && !typeSystem.isCompatible(initType, varType)) {
                // Provide more specific error messages for error union types
                if (isErrorUnionType(varType) || isErrorUnionType(initType)) {
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
        
        currentScope->variables[varDecl->name] = varType;
        
    } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        checkFunctionDeclaration(funcDecl);
        
    } else if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        enterScope();
        for (const auto& statement : blockStmt->statements) {
            checkStatement(statement);
        }
        exitScope();
        
    } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        TypePtr condType = checkExpression(ifStmt->condition);
        if (condType != typeSystem.BOOL_TYPE && condType != typeSystem.ANY_TYPE) {
            addError("If condition must be boolean, got " + condType->toString(), ifStmt->line);
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
                    FunctionSignature* signature = currentScope->getFunctionSignature(varExpr->name);
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
            if (!typeSystem.isCompatible(returnType, currentFunction->returnType)) {
                addError("Return type mismatch: expected " + currentFunction->returnType->toString() + 
                        ", got " + returnType->toString(), returnStmt->line);
            }
        }
    } else if (auto contractStmt = std::dynamic_pointer_cast<AST::ContractStatement>(stmt)) {
        checkContractStatement(contractStmt);
    }
    
    // Handle other statement types as needed
}

TypePtr TypeChecker::checkExpression(const std::shared_ptr<AST::Expression>& expr) {
    if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        // Infer type from literal value using variant index
        switch (literalExpr->value.index()) {
            case 0: // int64_t
                return typeSystem.INT_TYPE;
            case 1: // double
                return typeSystem.FLOAT64_TYPE;
            case 2: // std::string
                return typeSystem.STRING_TYPE;
            case 3: // bool
                return typeSystem.BOOL_TYPE;
            default:
                break;
        }
        return typeSystem.ANY_TYPE;
        
    } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        TypePtr varType = currentScope->getVariableType(varExpr->name);
        if (varType) {
            return varType;
        }
        
        // Check if it's a function being referenced (not called)
        FunctionSignature* signature = currentScope->getFunctionSignature(varExpr->name);
        if (signature) {
            // Return a function type for the function reference
            return typeSystem.createFunctionType(signature->paramTypes, signature->returnType);
        }
        
        addError("Undefined variable", expr->line, 0, "Variable lookup", varExpr->name, "declared variable name");
        return typeSystem.ANY_TYPE;
        
    } else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        checkFunctionCall(callExpr);
        
        // Get function signature or function type to determine return type
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(callExpr->callee)) {
            // First check if it's a regular function
            FunctionSignature* signature = currentScope->getFunctionSignature(varExpr->name);
            if (signature) {
                return signature->returnType;
            }
            
            // Check if it's a function-typed variable
            TypePtr varType = currentScope->getVariableType(varExpr->name);
            if (varType && varType->tag == TypeTag::Function) {
                if (std::holds_alternative<FunctionType>(varType->extra)) {
                    auto funcType = std::get<FunctionType>(varType->extra);
                    return funcType.returnType;
                }
            }
        }
        return typeSystem.ANY_TYPE;
        
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
            TypePtr varType = currentScope->getVariableType(assignExpr->name);
            if (varType && !typeSystem.isCompatible(valueType, varType)) {
                addError("Type mismatch in assignment: cannot assign " + 
                        valueType->toString() + " to " + varType->toString(), 
                        expr->line);
            }
        }
        
        return valueType;
        
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
            currentScope->variables[param.first] = paramType;
        }
        
        // Determine return type
        TypePtr returnType = typeSystem.ANY_TYPE;
        if (lambdaExpr->returnType.has_value()) {
            returnType = resolveTypeAnnotation(lambdaExpr->returnType.value());
        } else {
            // Try to infer return type from body if possible
            // For now, use ANY_TYPE - could be enhanced with return type inference
            returnType = typeSystem.ANY_TYPE;
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
    }
    
    // Default case for other expression types
    return typeSystem.ANY_TYPE;
}

TypePtr TypeChecker::checkExpression(const std::shared_ptr<AST::Expression>& expr, TypePtr expectedType) {
    if (auto errorExpr = std::dynamic_pointer_cast<AST::ErrorConstructExpr>(expr)) {
        checkErrorConstructExpression(errorExpr);
        
        // Error construction with expected type context
        if (typeSystem.isErrorType(errorExpr->errorType)) {
            // If expected type is an error union, return the expected type directly
            if (expectedType && expectedType->tag == TypeTag::ErrorUnion) {
                auto expectedErrorUnion = std::get<ErrorUnionType>(expectedType->extra);
                // Verify that the error type is compatible with the expected error types
                if (expectedErrorUnion.isGenericError || 
                    std::find(expectedErrorUnion.errorTypes.begin(), expectedErrorUnion.errorTypes.end(), 
                             errorExpr->errorType) != expectedErrorUnion.errorTypes.end()) {
                    return expectedType;
                }
            }
            // Fallback to creating new error union if no compatible expected type
            return typeSystem.createErrorUnionType(typeSystem.ANY_TYPE, {errorExpr->errorType}, false);
        }
        addError("Unknown error type: " + errorExpr->errorType, expr->line);
        return typeSystem.ANY_TYPE;
        
    } else if (auto okExpr = std::dynamic_pointer_cast<AST::OkConstructExpr>(expr)) {
        checkOkConstructExpression(okExpr);
        
        // Ok construction with expected type context
        TypePtr valueType = checkExpression(okExpr->value);
        
        // If expected type is an error union, return the expected type directly
        if (expectedType && expectedType->tag == TypeTag::ErrorUnion) {
            auto expectedErrorUnion = std::get<ErrorUnionType>(expectedType->extra);
            // Verify that the value type is compatible with the expected success type
            if (typeSystem.isCompatible(valueType, expectedErrorUnion.successType)) {
                return expectedType;
            }
        }
        // Fallback to creating new error union if no compatible expected type
        return typeSystem.createErrorUnionType(valueType, {}, true);
    }
    
    // For all other expressions, delegate to the original method
    return checkExpression(expr);
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
        
        // First check if it's a regular function
        FunctionSignature* signature = currentScope->getFunctionSignature(varExpr->name);
        if (signature) {
            // Handle regular function call
            checkRegularFunctionCall(signature, argTypes, expr);
            return;
        }
        
        // Check if it's a function-typed variable (like a function parameter)
        TypePtr varType = currentScope->getVariableType(varExpr->name);
        if (varType && varType->tag == TypeTag::Function) {
            // Handle higher-order function call
            checkHigherOrderFunctionCall(varType, argTypes, expr);
            return;
        }
        
        addError("Undefined function", expr->line, 0, "Function call", varExpr->name, "declared function name");
        return;
    }
}

void TypeChecker::checkRegularFunctionCall(FunctionSignature* signature, const std::vector<TypePtr>& argTypes, const std::shared_ptr<AST::CallExpr>& expr) {
    // Check argument count
    if (argTypes.size() != signature->paramTypes.size()) {
        addError("Function argument count mismatch", expr->line, 0, "Function call", 
                signature->name, 
                std::to_string(signature->paramTypes.size()) + " arguments, got " + std::to_string(argTypes.size()));
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
        addError("Invalid function type in higher-order function call", expr->line);
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
    FunctionSignature* signature = currentScope->getFunctionSignature(stmt->name);
    FunctionSignature* prevFunction = currentFunction;
    currentFunction = signature;
    
    // Validate error type annotations consistency
    validateFunctionErrorTypes(stmt);
    
    // Enter function scope
    enterScope();
    
    // Add parameters to scope
    for (const auto& param : stmt->params) {
        TypePtr paramType = typeSystem.ANY_TYPE;
        if (param.second) {
            paramType = resolveTypeAnnotation(param.second);
        }
        currentScope->variables[param.first] = paramType;
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
    }
    
    // Enhanced exhaustiveness checking for error types
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
            FunctionSignature* signature = currentScope->getFunctionSignature(varExpr->name);
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
    currentScope->functions["len"] = FunctionSignature(
        "len", {typeSystem.ANY_TYPE}, typeSystem.INT_TYPE, false, {}, 0);
    
    currentScope->functions["typeOf"] = FunctionSignature(
        "typeOf", {typeSystem.ANY_TYPE}, typeSystem.STRING_TYPE, false, {}, 0);
    
    currentScope->functions["time"] = FunctionSignature(
        "time", {}, typeSystem.INT64_TYPE, false, {}, 0);
    
    currentScope->functions["date"] = FunctionSignature(
        "date", {}, typeSystem.STRING_TYPE, false, {}, 0);
    
    currentScope->functions["now"] = FunctionSignature(
        "now", {}, typeSystem.STRING_TYPE, false, {}, 0);
    
    currentScope->functions["clock"] = FunctionSignature(
        "clock", {}, typeSystem.FLOAT64_TYPE, false, {}, 0);
    
    currentScope->functions["sleep"] = FunctionSignature(
        "sleep", {typeSystem.FLOAT64_TYPE}, typeSystem.NIL_TYPE, false, {}, 0);
    
    currentScope->functions["round"] = FunctionSignature(
        "round", {typeSystem.FLOAT64_TYPE, typeSystem.INT_TYPE}, typeSystem.FLOAT64_TYPE, false, {}, 0);
    
    currentScope->functions["debug"] = FunctionSignature(
        "debug", {typeSystem.ANY_TYPE}, typeSystem.NIL_TYPE, false, {}, 0);
    
    currentScope->functions["input"] = FunctionSignature(
        "input", {typeSystem.STRING_TYPE}, typeSystem.STRING_TYPE, false, {}, 0);
    
    currentScope->functions["assert"] = FunctionSignature(
        "assert", {typeSystem.BOOL_TYPE, typeSystem.STRING_TYPE}, typeSystem.NIL_TYPE, false, {}, 0);
    
    // Higher-order functions
    currentScope->functions["map"] = FunctionSignature(
        "map", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["filter"] = FunctionSignature(
        "filter", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["reduce"] = FunctionSignature(
        "reduce", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["forEach"] = FunctionSignature(
        "forEach", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["find"] = FunctionSignature(
        "find", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["some"] = FunctionSignature(
        "some", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.BOOL_TYPE, false, {}, 0);
    
    currentScope->functions["every"] = FunctionSignature(
        "every", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.BOOL_TYPE, false, {}, 0);
    
    currentScope->functions["compose"] = FunctionSignature(
        "compose", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["curry"] = FunctionSignature(
        "curry", {typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["partial"] = FunctionSignature(
        "partial", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    // Channel functions (VM-implemented)
    currentScope->functions["channel"] = FunctionSignature(
        "channel", {}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["send"] = FunctionSignature(
        "send", {typeSystem.ANY_TYPE, typeSystem.ANY_TYPE}, typeSystem.NIL_TYPE, false, {}, 0);
    
    currentScope->functions["receive"] = FunctionSignature(
        "receive", {typeSystem.ANY_TYPE}, typeSystem.ANY_TYPE, false, {}, 0);
    
    currentScope->functions["close"] = FunctionSignature(
        "close", {typeSystem.ANY_TYPE}, typeSystem.NIL_TYPE, false, {}, 0);
    
    // Register assert function (contract is a statement, not a function)
    currentScope->functions["assert"] = FunctionSignature(
        "assert", {typeSystem.BOOL_TYPE, typeSystem.STRING_TYPE}, typeSystem.NIL_TYPE, false, {}, 0);
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