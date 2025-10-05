#pragma once

#include "types.hh"
#include "../frontend/ast.hh"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

// Forward declarations
class TypeSystem;

// Type checking error information
struct TypeCheckError {
    std::string message;
    int line;
    int column;
    std::string context;
    
    TypeCheckError(const std::string& msg, int ln, int col = 0, const std::string& ctx = "")
        : message(msg), line(ln), column(col), context(ctx) {}
};

// Function signature information for error type checking
struct FunctionSignature {
    std::string name;
    std::vector<TypePtr> paramTypes;
    TypePtr returnType;
    bool canFail = false;
    std::vector<std::string> errorTypes;
    int line;
    
    // Default constructor for use in containers
    FunctionSignature() : name(""), paramTypes(), returnType(nullptr), canFail(false), errorTypes(), line(0) {}
    
    FunctionSignature(const std::string& n, const std::vector<TypePtr>& params, 
                     TypePtr ret, bool fail = false, 
                     const std::vector<std::string>& errors = {}, int ln = 0)
        : name(n), paramTypes(params), returnType(ret), canFail(fail), errorTypes(errors), line(ln) {}
};

// Scope information for tracking variable types and function signatures
struct Scope {
    std::unordered_map<std::string, TypePtr> variables;
    std::unordered_map<std::string, FunctionSignature> functions;
    std::shared_ptr<Scope> parent;
    
    Scope(std::shared_ptr<Scope> p = nullptr) : parent(p) {}
    
    // Look up variable type in this scope or parent scopes
    TypePtr getVariableType(const std::string& name) {
        auto it = variables.find(name);
        if (it != variables.end()) {
            return it->second;
        }
        if (parent) {
            return parent->getVariableType(name);
        }
        return nullptr;
    }
    
    // Look up function signature in this scope or parent scopes
    FunctionSignature* getFunctionSignature(const std::string& name) {
        auto it = functions.find(name);
        if (it != functions.end()) {
            return &it->second;
        }
        if (parent) {
            return parent->getFunctionSignature(name);
        }
        return nullptr;
    }
};

// Compile-time type checker for error handling validation
class TypeChecker {
private:
    TypeSystem& typeSystem;
    std::shared_ptr<Scope> currentScope;
    std::vector<TypeCheckError> errors;

    // Current function context for error propagation validation
    FunctionSignature* currentFunction = nullptr;
    
    // Source context for error reporting
    std::string sourceCode;
    std::string filePath;
    
    // Helper methods
    void addError(const std::string& message, int line, int column = 0, const std::string& context = "");
    void addError(const std::string& message, int line, int column, const std::string& context, const std::string& lexeme, const std::string& expectedValue);
    void enterScope();
    void exitScope();
    TypePtr resolveTypeAnnotation(const std::shared_ptr<AST::TypeAnnotation>& annotation);
    
    // Type checking methods
    TypePtr checkExpression(const std::shared_ptr<AST::Expression>& expr);
    TypePtr checkExpression(const std::shared_ptr<AST::Expression>& expr, TypePtr expectedType);
    void checkStatement(const std::shared_ptr<AST::Statement>& stmt);
    
    // Error handling specific checks
    void checkFallibleExpression(const std::shared_ptr<AST::FallibleExpr>& expr);
    void checkErrorConstructExpression(const std::shared_ptr<AST::ErrorConstructExpr>& expr);
    void checkOkConstructExpression(const std::shared_ptr<AST::OkConstructExpr>& expr);
    void checkFunctionCall(const std::shared_ptr<AST::CallExpr>& expr);
    void checkRegularFunctionCall(FunctionSignature* signature, const std::vector<TypePtr>& argTypes, const std::shared_ptr<AST::CallExpr>& expr);
    void checkHigherOrderFunctionCall(TypePtr functionType, const std::vector<TypePtr>& argTypes, const std::shared_ptr<AST::CallExpr>& expr);
    void checkFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt);
    
    // Error type compatibility checking
    bool isErrorUnionCompatible(TypePtr from, TypePtr to);
    bool canPropagateError(const std::vector<std::string>& sourceErrors, 
                          const std::vector<std::string>& targetErrors);
    std::vector<std::string> getErrorTypesFromType(TypePtr type);
    bool isErrorUnionType(TypePtr type);
    bool requiresErrorHandling(TypePtr type);
    
    // Pattern matching validation for error types
    void checkMatchStatement(const std::shared_ptr<AST::MatchStatement>& stmt);
    bool isExhaustiveErrorMatch(const std::vector<std::shared_ptr<AST::MatchCase>>& cases, TypePtr type);
    
    // Helper methods for error reporting
    std::string joinErrorTypes(const std::vector<std::string>& errorTypes);
    
    // Function signature error type validation
    void validateFunctionErrorTypes(const std::shared_ptr<AST::FunctionDeclaration>& stmt);
    void validateFunctionBodyErrorTypes(const std::shared_ptr<AST::FunctionDeclaration>& stmt);
    void validateErrorTypeCompatibility(const std::shared_ptr<AST::FunctionDeclaration>& caller,
                                       const std::shared_ptr<AST::FunctionDeclaration>& callee);
    bool canFunctionProduceErrorType(const std::shared_ptr<AST::Statement>& body, 
                                    const std::string& errorType);
    std::vector<std::string> inferFunctionErrorTypes(const std::shared_ptr<AST::Statement>& body);
    std::vector<std::string> inferExpressionErrorTypes(const std::shared_ptr<AST::Expression>& expr);
    
    // Register builtin functions for semantic analysis
    void registerBuiltinFunctions();
    
    // Contract and assert validation
    void checkContractStatement(const std::shared_ptr<AST::ContractStatement>& stmt);
    void checkAssertCall(const std::shared_ptr<AST::CallExpr>& expr);
    
    // Helper method to get code context for error reporting
    std::string getCodeContext(int line);
    
public:
    TypeChecker(TypeSystem& ts) : typeSystem(ts), currentScope(std::make_shared<Scope>()) {
        registerBuiltinFunctions();
    }
    
    // Set source context for error reporting
    void setSourceContext(const std::string& source, const std::string& filePath) {
        this->sourceCode = source;
        this->filePath = filePath;
    }
    
    // Main type checking entry point
    std::vector<TypeCheckError> checkProgram(const std::shared_ptr<AST::Program>& program);
    
    // Individual checking methods
    std::vector<TypeCheckError> checkFunction(const std::shared_ptr<AST::FunctionDeclaration>& func);
    
    // Error reporting
    const std::vector<TypeCheckError>& getErrors() const { return errors; }
    bool hasErrors() const { return !errors.empty(); }
    void clearErrors() { errors.clear(); }
};