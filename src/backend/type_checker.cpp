#include "type_checker.hh"
#include "type_system.hh"
#include "../common/debugger.hh"
#include "../frontend/scanner.hh"
#include "../frontend/parser.hh"
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
}

void TypeChecker::addError(const std::string& message, int line, int column, const std::string& context, const std::string& lexeme, const std::string& expectedValue) {
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
    symbolTable.enterScope();
}

void TypeChecker::exitScope() {
    symbolTable.exitScope();
}

std::vector<TypeCheckError> TypeChecker::checkProgram(const std::shared_ptr<AST::Program>& program) {
    errors.clear();
    extractModuleVisibility(program);
    for (const auto& stmt : program->statements) {
        if (auto typeDecl = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) {
            TypePtr aliasType = resolveTypeAnnotation(typeDecl->type);
            if (aliasType) {
                typeSystem.registerTypeAlias(typeDecl->name, aliasType);
            } else {
                addError("Invalid type in type alias '" + typeDecl->name + "'", typeDecl->line);
            }
        } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            std::vector<TypePtr> paramTypes;
            std::vector<bool> optionalParams;
            std::vector<bool> hasDefaultValues;
            for (const auto& param : funcDecl->params) {
                paramTypes.push_back(param.second ? resolveTypeAnnotation(param.second) : typeSystem.ANY_TYPE);
                optionalParams.push_back(false);
                hasDefaultValues.push_back(false);
            }
            for (const auto& optParam : funcDecl->optionalParams) {
                paramTypes.push_back(optParam.second.first ? resolveTypeAnnotation(optParam.second.first) : typeSystem.ANY_TYPE);
                optionalParams.push_back(true);
                hasDefaultValues.push_back(optParam.second.second != nullptr);
            }
            TypePtr returnType = typeSystem.NIL_TYPE;
            if (funcDecl->returnType && *funcDecl->returnType) {
                returnType = resolveTypeAnnotation(*funcDecl->returnType);
            }
            bool canFail = funcDecl->canFail || funcDecl->throws;
            std::vector<std::string> errorTypes = funcDecl->declaredErrorTypes;
            if (std::holds_alternative<ErrorUnionType>(returnType->data)) {
                canFail = true;
                auto errorUnion = std::get<ErrorUnionType>(returnType->data);
                if (errorTypes.empty()) {
                    errorTypes = errorUnion.errorTypes;
                }
            }
            FunctionSignature signature(funcDecl->name, paramTypes, returnType, canFail, errorTypes, funcDecl->line, optionalParams, hasDefaultValues);
            symbolTable.addFunction(funcDecl->name, signature);
        }
    }
    for (const auto& stmt : program->statements) {
        checkStatement(stmt);
    }
    return errors;
}

TypePtr TypeChecker::resolveTypeAnnotation(const std::shared_ptr<AST::TypeAnnotation>& annotation) {
    if (!annotation) {
        return typeSystem.NIL_TYPE;
    }
    return typeSystem.ANY_TYPE; // Simplified for now
}

void TypeChecker::checkStatement(const std::shared_ptr<AST::Statement>& stmt) {
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        topLevelVariables[varDecl->name] = varDecl;
        TypePtr varType = (varDecl->type && *varDecl->type) ? resolveTypeAnnotation(*varDecl->type) : typeSystem.ANY_TYPE;
        if (varDecl->initializer) {
            TypePtr initType = checkExpression(varDecl->initializer);
            if (!typeSystem.isCompatible(initType, varType)) {
                addError("Type mismatch in variable declaration '" + varDecl->name + "'", varDecl->line);
            }
            if (std::holds_alternative<AnyType>(varType->data)) {
                varType = initType;
            }
        }
        symbolTable.addVariable(varDecl->name, varType, varDecl->line);
    } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
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
        checkStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch) {
            checkStatement(ifStmt->elseBranch);
        }
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        checkExpression(exprStmt->expression);
    } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        if (currentFunction) {
            TypePtr returnType = returnStmt->value ? checkExpression(returnStmt->value, currentFunction->returnType) : typeSystem.NIL_TYPE;
            if (!typeSystem.isCompatible(returnType, currentFunction->returnType)) {
                 addError("Return type mismatch", returnStmt->line);
            }
        }
    } else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) {
        checkClassDeclaration(classDecl);
    }
}

TypePtr TypeChecker::checkExpression(const std::shared_ptr<AST::Expression>& expr) {
    return checkExpression(expr, nullptr);
}

TypePtr TypeChecker::checkExpression(const std::shared_ptr<AST::Expression>& expr, TypePtr expectedType) {
    if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        switch (literalExpr->value.index()) {
            case 0: return typeSystem.INT64_TYPE;
            case 1: return typeSystem.UINT64_TYPE;
            case 2: return typeSystem.FLOAT64_TYPE;
            case 3: return typeSystem.STRING_TYPE;
            case 4: return typeSystem.BOOL_TYPE;
            case 5: return typeSystem.NIL_TYPE;
            default: return typeSystem.ANY_TYPE;
        }
    } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        Symbol* symbol = symbolTable.findVariable(varExpr->name);
        if (symbol) {
            return symbol->type;
        }
        addError("Undefined variable '" + varExpr->name + "'", expr->line);
        return typeSystem.ANY_TYPE;
    }
    return typeSystem.ANY_TYPE;
}
