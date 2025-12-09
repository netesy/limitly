#pragma once

#include "types.hh"
#include "symbol_table.hh"
#include "type_system.hh"
#include "../frontend/ast.hh"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

// Visibility information storage structures
struct MemberVisibilityInfo {
    std::string memberName;
    AST::VisibilityLevel visibility;
    std::string declaringModule;
    std::string declaringClass;  // Empty for module-level members
    int declarationLine;
    
    MemberVisibilityInfo() : memberName(""), visibility(AST::VisibilityLevel::Private), 
                           declaringModule(""), declaringClass(""), declarationLine(0) {}
    
    MemberVisibilityInfo(const std::string& name, AST::VisibilityLevel vis, 
                        const std::string& module, const std::string& className = "", int line = 0)
        : memberName(name), visibility(vis), declaringModule(module), 
          declaringClass(className), declarationLine(line) {}
};

struct ClassVisibilityInfo {
    std::string className;
    std::string declaringModule;
    std::string superClassName;  // For inheritance checking
    std::unordered_map<std::string, MemberVisibilityInfo> fields;
    std::unordered_map<std::string, MemberVisibilityInfo> methods;
    
    ClassVisibilityInfo() : className(""), declaringModule(""), superClassName("") {}
    
    ClassVisibilityInfo(const std::string& name, const std::string& module, 
                       const std::string& superClass = "")
        : className(name), declaringModule(module), superClassName(superClass) {}
};

struct ModuleVisibilityInfo {
    std::string modulePath;
    std::unordered_map<std::string, MemberVisibilityInfo> functions;
    std::unordered_map<std::string, MemberVisibilityInfo> variables;
    std::unordered_map<std::string, ClassVisibilityInfo> classes;
    
    ModuleVisibilityInfo() : modulePath("") {}
    
    explicit ModuleVisibilityInfo(const std::string& path) : modulePath(path) {}
};

// Type checking error information
struct TypeCheckError {
    std::string message;
    int line;
    int column;
    std::string context;
    
    TypeCheckError(const std::string& msg, int ln, int col = 0, const std::string& ctx = "")
        : message(msg), line(ln), column(col), context(ctx) {}
};

// Compile-time type checker for error handling validation
class TypeChecker {
private:
    TypeSystem& typeSystem;
    SymbolTable symbolTable;
    std::vector<TypeCheckError> errors;

    // Current function context for error propagation validation
    FunctionSignature* currentFunction = nullptr;
    
    // Visibility tracking structures
    std::unordered_map<std::string, ModuleVisibilityInfo> moduleRegistry;
    std::unordered_map<std::string, ClassVisibilityInfo> classRegistry;
    std::unordered_map<std::string, std::string> classToModuleMap;
    
    // Current context tracking variables
    std::string currentModulePath;
    std::string currentClassName;
    
    // Import tracking for module alias resolution
    std::unordered_map<std::string, std::string> moduleAliases; // alias -> actual module path
    
    // Legacy visibility checking structures (kept for backward compatibility)
    std::shared_ptr<AST::ClassDeclaration> currentClassDecl = nullptr;
    std::unordered_map<std::string, std::shared_ptr<AST::ClassDeclaration>> classDeclarations;
    std::unordered_map<std::string, std::shared_ptr<AST::ModuleDeclaration>> moduleDeclarations;
    std::unordered_map<std::string, std::shared_ptr<AST::VarDeclaration>> topLevelVariables;
    std::unordered_map<std::string, std::shared_ptr<AST::FunctionDeclaration>> topLevelFunctions;
    
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
    
    // Visibility enforcement methods
    TypePtr checkMemberAccess(const std::shared_ptr<AST::MemberExpr>& expr);
    bool canAccessMember(const std::string& className, const std::string& memberName, AST::VisibilityLevel memberVisibility);
    bool canAccessModuleMember(const std::string& moduleName, const std::string& memberName);
    std::string getCurrentClassName();
    AST::VisibilityLevel getMemberVisibility(const std::string& className, const std::string& memberName);
    
    // Inheritance checking
    bool isSubclassOf(const std::string& subclass, const std::string& superclass);
    
    // Top-level declaration visibility checking
    AST::VisibilityLevel getTopLevelDeclarationVisibility(const std::string& name);
    
    // Module-based access checking (each file is a module)
    bool canAccessFromCurrentModule(AST::VisibilityLevel visibility, const std::string& declaringModule = "");
    
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
    bool isUnionType(TypePtr type);
    bool requiresErrorHandling(TypePtr type);
    
    // Pattern matching validation for error types
    void checkMatchStatement(const std::shared_ptr<AST::MatchStatement>& stmt);
    bool isExhaustiveErrorMatch(const std::vector<std::shared_ptr<AST::MatchCase>>& cases, TypePtr type);
    
    // Union type pattern matching validation
    bool isExhaustiveUnionMatch(TypePtr unionType, const std::vector<std::shared_ptr<AST::MatchCase>>& cases);
    void validateUnionVariantAccess(TypePtr unionType, const std::string& variantName, int line);
    void validatePatternCompatibility(const std::shared_ptr<AST::Expression>& pattern, TypePtr matchType, int line);
    std::string getMissingUnionVariants(TypePtr unionType, const std::vector<std::shared_ptr<AST::MatchCase>>& cases);
    
    // Option type pattern matching validation
    bool isExhaustiveOptionMatch(const std::vector<std::shared_ptr<AST::MatchCase>>& cases);
    
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
    
    // Class declaration validation
    void checkClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& classDecl);
    
    // Module declaration validation
    void checkModuleDeclaration(const std::shared_ptr<AST::ModuleDeclaration>& moduleDecl);
    
    // Contract and assert validation
    void checkContractStatement(const std::shared_ptr<AST::ContractStatement>& stmt);
    void checkAssertCall(const std::shared_ptr<AST::CallExpr>& expr);
    
    // Helper method to get code context for error reporting
    std::string getCodeContext(int line);
    
    // Lambda return type inference
    TypePtr inferLambdaReturnType(const std::shared_ptr<AST::Statement>& body);
    

    
    // Import handling for module alias resolution
    void handleImportStatement(const std::shared_ptr<AST::ImportStatement>& importStmt);
    std::string resolveModulePath(const std::string& modulePath);
    std::string resolveModuleAlias(const std::string& alias);
    void loadModuleVisibilityInfo(const std::string& modulePath);
    
    // Type checking helper functions
    bool isOptionalType(TypePtr type);
    
public:
    TypeChecker(TypeSystem& ts) : typeSystem(ts), symbolTable() {
        registerBuiltinFunctions();
    }
    
    // Set source context for error reporting
    void setSourceContext(const std::string& source, const std::string& filePath) {
        this->sourceCode = source;
        this->filePath = filePath;
        this->currentModulePath = filePath; // Each file is a module
    }
    
    // Main type checking entry point
    std::vector<TypeCheckError> checkProgram(const std::shared_ptr<AST::Program>& program);
    
    // Individual checking methods
    std::vector<TypeCheckError> checkFunction(const std::shared_ptr<AST::FunctionDeclaration>& func);
    
    // Error reporting
    const std::vector<TypeCheckError>& getErrors() const { return errors; }
    bool hasErrors() const { return !errors.empty(); }
    void clearErrors() { errors.clear(); }
    
    // Public methods for backend access
    std::string getCurrentModulePath() const { return currentModulePath; }
    AST::VisibilityLevel getModuleMemberVisibility(const std::string& moduleName, const std::string& memberName);
    
    // Module function reference validation
    bool isValidModuleFunctionReference(const std::string& functionRef);
    std::string extractModuleFunctionName(const std::string& functionRef);
    
    // Import validation
    void validateImportFilter(const AST::ImportFilter& filter, const std::string& modulePath);
    
    // Module member function call validation
    void checkModuleMemberFunctionCall(const std::shared_ptr<AST::MemberExpr>& memberExpr, 
                                      const std::vector<TypePtr>& argTypes, 
                                      const std::shared_ptr<AST::CallExpr>& callExpr);

    // Class method call validation
    TypePtr checkClassMethodCall(const std::shared_ptr<AST::MemberExpr>& memberExpr,
                                 const std::vector<TypePtr>& argTypes,
                                 const std::shared_ptr<AST::CallExpr>& callExpr);
    
    // Import statement checking
    void checkImportStatement(const std::shared_ptr<AST::ImportStatement>& importStmt);
    
    // Visibility information extraction methods
    void extractModuleVisibility(const std::shared_ptr<AST::Program>& program);
    void extractClassVisibility(const std::shared_ptr<AST::ClassDeclaration>& classDecl);
    void extractFunctionVisibility(const std::shared_ptr<AST::FunctionDeclaration>& funcDecl);
    void extractVariableVisibility(const std::shared_ptr<AST::VarDeclaration>& varDecl);
    
    // Core access validation logic methods
    bool validateClassMemberAccess(const std::shared_ptr<AST::MemberExpr>& expr);
    bool validateModuleFunctionCall(const std::shared_ptr<AST::CallExpr>& expr);
    bool validateModuleVariableAccess(const std::shared_ptr<AST::VariableExpr>& expr);
    
    // Class-based and module-based access checking methods
    bool canAccessClassMember(const std::string& className, const std::string& memberName, AST::VisibilityLevel memberVisibility);
    bool canAccessModuleMember(AST::VisibilityLevel visibility, const std::string& declaringModule, const std::string& accessingModule);
};