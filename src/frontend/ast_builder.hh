#ifndef AST_BUILDER_H
#define AST_BUILDER_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include "ast.hh"
#include "cst.hh"

namespace frontend {

    // Type resolution strategy for different AST nodes
    enum class TypeResolutionStrategy {
        IMMEDIATE,      // Resolve types immediately (declarations)
        DEFERRED,       // Defer type resolution (expressions)
        PARTIAL,        // Resolve what's available, defer the rest
        NONE           // No type resolution
    };

    // Configuration for controlling error-tolerant transformation behavior
    struct BuildConfig {
        bool insertErrorNodes = true;       // Insert Error nodes for invalid CST
        bool insertMissingNodes = true;     // Insert Missing nodes for incomplete CST
        bool preserveSourceMapping = true;  // Maintain CST → AST mapping
        bool validateSemantics = false;     // Perform semantic validation
        bool strictMode = false;            // Fail on any errors instead of creating error nodes
        bool preserveComments = false;      // Preserve comments in AST (future feature)
        size_t maxErrors = 100;             // Maximum number of errors before aborting
        
        // Type resolution configuration
        bool enableEarlyTypeResolution = true;     // Enable early type resolution for declarations
        bool deferExpressionTypes = true;          // Defer expression type inference
        bool resolveBuiltinTypes = true;           // Resolve primitive/builtin types immediately
        bool validateTypeAnnotations = true;       // Validate type annotations during conversion
        size_t maxTypeResolutionDepth = 10;        // Maximum depth for recursive type resolution
    };

    // Source mapping for error reporting and debugging
    struct SourceMapping {
        const CST::Node* cstNode;           // Original CST node
        std::shared_ptr<AST::Node> astNode; // Corresponding AST node
        size_t startPos;                    // Source start position
        size_t endPos;                      // Source end position
        std::string sourceText;             // Original source text (optional)
        
        SourceMapping(const CST::Node* cst, std::shared_ptr<AST::Node> ast)
            : cstNode(cst), astNode(ast), startPos(cst->startPos), endPos(cst->endPos) {}
    };

    // Error information for transformation issues
    struct TransformationError {
        std::string message;                // Error description
        const CST::Node* cstNode;          // CST node that caused the error
        size_t line;                       // Line number
        size_t column;                     // Column number
        std::string context;               // Surrounding context
        std::vector<std::string> suggestions; // Possible fixes
        
        TransformationError(const std::string& msg, const CST::Node* node)
            : message(msg), cstNode(node), line(0), column(0) {}
    };

    // Type resolution context for tracking resolution state
    struct TypeResolutionContext {
        std::unordered_map<std::string, std::shared_ptr<AST::TypeAnnotation>> declaredTypes;
        std::unordered_map<std::string, std::shared_ptr<AST::TypeAnnotation>> builtinTypes;
        std::vector<std::string> currentScope;
        size_t resolutionDepth = 0;
        bool inDeclarationContext = false;
        bool inExpressionContext = false;
        
        // Type resolution cache
        std::unordered_map<std::string, std::shared_ptr<AST::TypeAnnotation>> typeCache;
        
        void enterScope(const std::string& scopeName);
        void exitScope();
        void addDeclaredType(const std::string& name, std::shared_ptr<AST::TypeAnnotation> type);
        std::shared_ptr<AST::TypeAnnotation> lookupType(const std::string& name) const;
        std::string getCurrentScopePath() const;
    };

    // Deferred type resolution entry for expressions
    struct DeferredTypeResolution {
        std::shared_ptr<AST::Expression> expression;
        const CST::Node* originalCST;
        std::string contextInfo;
        TypeResolutionStrategy strategy;
        
        DeferredTypeResolution(std::shared_ptr<AST::Expression> expr, const CST::Node* cst, 
                             const std::string& context, TypeResolutionStrategy strat)
            : expression(expr), originalCST(cst), contextInfo(context), strategy(strat) {}
    };

    // Main ASTBuilder class for CST to AST transformation with unified type resolution
    class ASTBuilder {
    public:
        // Constructor
        explicit ASTBuilder(const BuildConfig& config = BuildConfig{});
        
        // Main transformation entry point
        std::shared_ptr<AST::Program> buildAST(const CST::Node& cst);
        
        // Configuration management
        void setConfig(const BuildConfig& config);
        const BuildConfig& getConfig() const { return config_; }
        
        // Type resolution management
        const TypeResolutionContext& getTypeContext() const { return typeContext_; }
        const std::vector<DeferredTypeResolution>& getDeferredResolutions() const { return deferredResolutions_; }
        void processDeferredResolutions();  // Process deferred type resolutions
        
        // Error and mapping access
        const std::vector<SourceMapping>& getSourceMappings() const { return sourceMappings_; }
        const std::vector<TransformationError>& getErrors() const { return errors_; }
        bool hasErrors() const { return !errors_.empty(); }
        void clearErrors() { errors_.clear(); }
        
        // Statistics
        size_t getTransformedNodeCount() const { return transformedNodeCount_; }
        size_t getErrorNodeCount() const { return errorNodeCount_; }
        size_t getMissingNodeCount() const { return missingNodeCount_; }
        
    private:
        BuildConfig config_;
        std::vector<SourceMapping> sourceMappings_;
        std::vector<TransformationError> errors_;
        size_t transformedNodeCount_ = 0;
        size_t errorNodeCount_ = 0;
        size_t missingNodeCount_ = 0;
        
        // Type resolution state
        TypeResolutionContext typeContext_;
        std::vector<DeferredTypeResolution> deferredResolutions_;
        
        // Core transformation methods with type resolution strategy
        std::shared_ptr<AST::Statement> buildStatement(const CST::Node& cst, TypeResolutionStrategy strategy = TypeResolutionStrategy::IMMEDIATE);
        std::shared_ptr<AST::Expression> buildExpression(const CST::Node& cst, TypeResolutionStrategy strategy = TypeResolutionStrategy::DEFERRED);
        std::shared_ptr<AST::TypeAnnotation> buildTypeAnnotation(const CST::Node& cst, TypeResolutionStrategy strategy = TypeResolutionStrategy::IMMEDIATE);
        
        // Unified type resolution methods
        std::shared_ptr<AST::TypeAnnotation> resolveTypeImmediate(const CST::Node& cst);
        std::shared_ptr<AST::TypeAnnotation> resolveTypeDeferred(const CST::Node& cst, std::shared_ptr<AST::Expression> expr);
        std::shared_ptr<AST::TypeAnnotation> resolveTypePartial(const CST::Node& cst);
        
        // Type resolution utilities
        std::shared_ptr<AST::TypeAnnotation> resolveBuiltinType(const std::string& typeName);
        std::shared_ptr<AST::TypeAnnotation> resolveUserDefinedType(const std::string& typeName);
        std::shared_ptr<AST::TypeAnnotation> resolveGenericType(const CST::Node& cst);
        std::shared_ptr<AST::TypeAnnotation> resolveUnionType(const CST::Node& cst);
        std::shared_ptr<AST::TypeAnnotation> resolveFunctionType(const CST::Node& cst);
        std::shared_ptr<AST::TypeAnnotation> resolveContainerType(const CST::Node& cst);
        
        // Declaration-specific type resolution (immediate)
        void resolveDeclarationType(std::shared_ptr<AST::VarDeclaration> varDecl, const CST::Node& cst);
        void resolveFunctionSignature(std::shared_ptr<AST::FunctionDeclaration> funcDecl, const CST::Node& cst);
        void resolveClassTypes(std::shared_ptr<AST::ClassDeclaration> classDecl, const CST::Node& cst);
        
        // Expression-specific type handling (deferred)
        void deferExpressionType(std::shared_ptr<AST::Expression> expr, const CST::Node& cst, const std::string& context);
        void markForTypeInference(std::shared_ptr<AST::Expression> expr, const CST::Node& cst);
        
        // Declaration transformation methods
        std::shared_ptr<AST::VarDeclaration> buildVarDeclaration(const CST::Node& cst);
        std::shared_ptr<AST::FunctionDeclaration> buildFunctionDeclaration(const CST::Node& cst);
        std::shared_ptr<AST::ClassDeclaration> buildClassDeclaration(const CST::Node& cst);
        std::shared_ptr<AST::TypeDeclaration> buildTypeDeclaration(const CST::Node& cst);
        std::shared_ptr<AST::EnumDeclaration> buildEnumDeclaration(const CST::Node& cst);
        std::shared_ptr<AST::ImportStatement> buildImportStatement(const CST::Node& cst);
        
        // Statement transformation methods
        std::shared_ptr<AST::IfStatement> buildIfStatement(const CST::Node& cst);
        std::shared_ptr<AST::ForStatement> buildForStatement(const CST::Node& cst);
        std::shared_ptr<AST::WhileStatement> buildWhileStatement(const CST::Node& cst);
        std::shared_ptr<AST::IterStatement> buildIterStatement(const CST::Node& cst);
        std::shared_ptr<AST::BlockStatement> buildBlockStatement(const CST::Node& cst);
        std::shared_ptr<AST::ReturnStatement> buildReturnStatement(const CST::Node& cst);
        std::shared_ptr<AST::BreakStatement> buildBreakStatement(const CST::Node& cst);
        std::shared_ptr<AST::ContinueStatement> buildContinueStatement(const CST::Node& cst);
        std::shared_ptr<AST::PrintStatement> buildPrintStatement(const CST::Node& cst);
        std::shared_ptr<AST::ExprStatement> buildExprStatement(const CST::Node& cst);
        std::shared_ptr<AST::MatchStatement> buildMatchStatement(const CST::Node& cst);
        std::shared_ptr<AST::ParallelStatement> buildParallelStatement(const CST::Node& cst);
        std::shared_ptr<AST::ConcurrentStatement> buildConcurrentStatement(const CST::Node& cst);
        
        // Expression transformation methods
        std::shared_ptr<AST::BinaryExpr> buildBinaryExpr(const CST::Node& cst);
        std::shared_ptr<AST::UnaryExpr> buildUnaryExpr(const CST::Node& cst);
        std::shared_ptr<AST::CallExpr> buildCallExpr(const CST::Node& cst);
        std::shared_ptr<AST::MemberExpr> buildMemberExpr(const CST::Node& cst);
        std::shared_ptr<AST::IndexExpr> buildIndexExpr(const CST::Node& cst);
        std::shared_ptr<AST::LiteralExpr> buildLiteralExpr(const CST::Node& cst);
        std::shared_ptr<AST::VariableExpr> buildVariableExpr(const CST::Node& cst);
        std::shared_ptr<AST::GroupingExpr> buildGroupingExpr(const CST::Node& cst);
        std::shared_ptr<AST::AssignExpr> buildAssignExpr(const CST::Node& cst);
        std::shared_ptr<AST::TernaryExpr> buildTernaryExpr(const CST::Node& cst);
        std::shared_ptr<AST::RangeExpr> buildRangeExpr(const CST::Node& cst);
        std::shared_ptr<AST::ListExpr> buildListExpr(const CST::Node& cst);
        std::shared_ptr<AST::DictExpr> buildDictExpr(const CST::Node& cst);
        std::shared_ptr<AST::LambdaExpr> buildLambdaExpr(const CST::Node& cst);
        std::shared_ptr<AST::InterpolatedStringExpr> buildInterpolatedStringExpr(const CST::Node& cst);
        std::shared_ptr<AST::FallibleExpr> buildFallibleExpr(const CST::Node& cst);
        
        // Error-tolerant node creation
        std::shared_ptr<AST::Expression> createErrorExpr(const std::string& message, const CST::Node& cst);
        std::shared_ptr<AST::Statement> createErrorStmt(const std::string& message, const CST::Node& cst);
        std::shared_ptr<AST::Expression> createMissingExpr(const std::string& description, const CST::Node& cst);
        std::shared_ptr<AST::Statement> createMissingStmt(const std::string& description, const CST::Node& cst);
        
        // Helper methods for CST navigation
        const CST::Node* findChild(const CST::Node& parent, CST::NodeKind kind) const;
        std::vector<const CST::Node*> findChildren(const CST::Node& parent, CST::NodeKind kind) const;
        std::string extractTokenText(const CST::Node& node) const;
        std::string extractIdentifier(const CST::Node& node) const;
        TokenType extractOperator(const CST::Node& node) const;
        
        // CST element navigation helpers
        std::vector<Token> getSignificantTokens(const CST::Node& node) const;
        std::vector<const CST::Node*> getSignificantChildren(const CST::Node& node) const;
        Token findFirstToken(const CST::Node& node, TokenType type) const;
        std::string reconstructSource(const CST::Node& node, bool includeTrivia = true) const;
        
        // Source mapping utilities
        void addSourceMapping(const CST::Node& cst, std::shared_ptr<AST::Node> ast);
        void preserveSourceSpan(const CST::Node& cst, std::shared_ptr<AST::Node> ast);
        void copySourceInfo(const CST::Node& cst, AST::Node& ast);
        
        // Error reporting utilities
        void reportError(const std::string& message, const CST::Node& cst);
        void reportWarning(const std::string& message, const CST::Node& cst);
        bool shouldContinueOnError() const;
        
        // Validation utilities
        bool validateCST(const CST::Node& cst) const;
        bool isValidStatementNode(const CST::Node& cst) const;
        bool isValidExpressionNode(const CST::Node& cst) const;
        
        // Type system helpers
        std::shared_ptr<AST::TypeAnnotation> createPrimitiveType(const std::string& typeName);
        std::shared_ptr<AST::TypeAnnotation> createOptionalType(std::shared_ptr<AST::TypeAnnotation> baseType);
        std::shared_ptr<AST::TypeAnnotation> createUnionType(const std::vector<std::shared_ptr<AST::TypeAnnotation>>& types);
        std::shared_ptr<AST::TypeAnnotation> createDeferredType(const std::string& placeholder);
        std::shared_ptr<AST::TypeAnnotation> createInferredType(const std::string& hint = "");
        
        // Type validation and compatibility
        bool validateTypeAnnotation(const std::shared_ptr<AST::TypeAnnotation>& type);
        bool isCompatibleType(const std::shared_ptr<AST::TypeAnnotation>& expected, 
                             const std::shared_ptr<AST::TypeAnnotation>& actual);
        std::string getTypeSignature(const std::shared_ptr<AST::TypeAnnotation>& type);
        
        // Builtin type initialization
        void initializeBuiltinTypes();
        void registerBuiltinType(const std::string& name, bool isPrimitive = true);
        
        // Type context management
        void enterDeclarationContext();
        void exitDeclarationContext();
        void enterExpressionContext();
        void exitExpressionContext();
        
        // Parameter and argument helpers
        std::vector<std::pair<std::string, std::shared_ptr<AST::TypeAnnotation>>> 
            buildParameterList(const CST::Node& cst);
        std::vector<std::shared_ptr<AST::Expression>> buildArgumentList(const CST::Node& cst);
        
        // Pattern matching helpers (for match statements)
        std::shared_ptr<AST::Expression> buildPattern(const CST::Node& cst);
        std::vector<AST::MatchCase> buildMatchCases(const CST::Node& cst);
        
        // Utility for handling error recovery nodes
        std::shared_ptr<AST::Node> handleErrorRecoveryNode(const CST::Node& cst);
        std::shared_ptr<AST::Node> handleMissingNode(const CST::MissingNode& missing);
        std::shared_ptr<AST::Node> handleIncompleteNode(const CST::IncompleteNode& incomplete);
        
        // Statistics tracking
        void incrementTransformedNodes() { transformedNodeCount_++; }
        void incrementErrorNodes() { errorNodeCount_++; }
        void incrementMissingNodes() { missingNodeCount_++; }
    };

    // Utility functions for common transformations
    namespace ASTBuilderUtils {
        // Convert CST NodeKind to appropriate AST node type
        bool isStatementKind(CST::NodeKind kind);
        bool isExpressionKind(CST::NodeKind kind);
        bool isDeclarationKind(CST::NodeKind kind);
        bool isTypeKind(CST::NodeKind kind);
        
        // Token extraction utilities
        std::string extractStringLiteral(const Token& token);
        long long extractIntegerLiteral(const Token& token);
        double extractFloatLiteral(const Token& token);
        bool extractBooleanLiteral(const Token& token);
        
        // Operator conversion utilities
        TokenType cstOperatorToASTOperator(const std::string& op);
        bool isBinaryOperator(TokenType type);
        bool isUnaryOperator(TokenType type);
        bool isAssignmentOperator(TokenType type);
        
        // Type annotation utilities
        bool isPrimitiveTypeName(const std::string& name);
        bool isOptionalTypeAnnotation(const std::string& annotation);
        std::vector<std::string> parseUnionTypes(const std::string& typeStr);
    }

} // namespace frontend

#endif // AST_BUILDER_H