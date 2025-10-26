#include "ast_builder.hh"
#include <sstream>
#include <algorithm>
#include <cctype>

namespace frontend {

    // Constructor
    ASTBuilder::ASTBuilder(const BuildConfig& config) : config_(config) {
        sourceMappings_.reserve(1000);  // Pre-allocate for performance
        errors_.reserve(100);
        deferredResolutions_.reserve(500);  // Pre-allocate for deferred type resolutions
        
        // Initialize builtin types if early type resolution is enabled
        if (config_.enableEarlyTypeResolution) {
            initializeBuiltinTypes();
        }
    }

    // Main transformation entry point
    std::shared_ptr<AST::Program> ASTBuilder::buildAST(const CST::Node& cst) {
        // Clear previous state
        sourceMappings_.clear();
        errors_.clear();
        deferredResolutions_.clear();
        transformedNodeCount_ = 0;
        errorNodeCount_ = 0;
        missingNodeCount_ = 0;
        
        // Reset type resolution context
        typeContext_ = TypeResolutionContext{};
        if (config_.enableEarlyTypeResolution) {
            initializeBuiltinTypes();
        }
        
        // Validate input CST
        if (!validateCST(cst)) {
            reportError("Invalid CST structure provided", cst);
            if (config_.strictMode) {
                return nullptr;
            }
        }
        
        // Create the program node
        auto program = std::make_shared<AST::Program>();
        copySourceInfo(cst, *program);
        
        // Transform based on CST node kind
        if (cst.kind == CST::NodeKind::PROGRAM) {
            // Process all significant child nodes (skip trivia)
            auto significantChildren = getSignificantChildren(cst);
            for (const auto& child : significantChildren) {
                if (child && isValidStatementNode(*child)) {
                    auto stmt = buildStatement(*child);
                    if (stmt) {
                        program->statements.push_back(stmt);
                    }
                } else if (child) {
                    // Handle error recovery nodes
                    auto errorStmt = handleErrorRecoveryNode(*child);
                    if (errorStmt && config_.insertErrorNodes) {
                        auto stmt = std::dynamic_pointer_cast<AST::Statement>(errorStmt);
                        if (stmt) {
                            program->statements.push_back(stmt);
                        }
                    }
                }
            }
        } else {
            reportError("Expected PROGRAM node at root, got " + cst.getKindName(), cst);
            if (config_.strictMode) {
                return nullptr;
            }
        }
        
        // Add source mapping for the program
        addSourceMapping(cst, program);
        incrementTransformedNodes();
        
        return program;
    }

    // Configuration management
    void ASTBuilder::setConfig(const BuildConfig& config) {
        config_ = config;
    }

    // Core transformation methods with type resolution strategy
    std::shared_ptr<AST::Statement> ASTBuilder::buildStatement(const CST::Node& cst, TypeResolutionStrategy strategy) {
        incrementTransformedNodes();
        
        // Enter declaration context for statements that declare types
        bool wasInDeclarationContext = typeContext_.inDeclarationContext;
        if (strategy == TypeResolutionStrategy::IMMEDIATE) {
            enterDeclarationContext();
        }
        
        switch (cst.kind) {
            case CST::NodeKind::VAR_DECLARATION:
                return buildVarDeclaration(cst);
            case CST::NodeKind::FUNCTION_DECLARATION:
                return buildFunctionDeclaration(cst);
            case CST::NodeKind::CLASS_DECLARATION:
                return buildClassDeclaration(cst);
            case CST::NodeKind::TYPE_DECLARATION:
                return buildTypeDeclaration(cst);
            case CST::NodeKind::ENUM_DECLARATION:
                return buildEnumDeclaration(cst);
            case CST::NodeKind::IMPORT_DECLARATION:
                return buildImportStatement(cst);
            case CST::NodeKind::IF_STATEMENT:
                return buildIfStatement(cst);
            case CST::NodeKind::FOR_STATEMENT:
                return buildForStatement(cst);
            case CST::NodeKind::WHILE_STATEMENT:
                return buildWhileStatement(cst);
            case CST::NodeKind::ITER_STATEMENT:
                return buildIterStatement(cst);
            case CST::NodeKind::BLOCK_STATEMENT:
                return buildBlockStatement(cst);
            case CST::NodeKind::RETURN_STATEMENT:
                return buildReturnStatement(cst);
            case CST::NodeKind::BREAK_STATEMENT:
                return buildBreakStatement(cst);
            case CST::NodeKind::CONTINUE_STATEMENT:
                return buildContinueStatement(cst);
            case CST::NodeKind::PRINT_STATEMENT:
                return buildPrintStatement(cst);
            case CST::NodeKind::EXPRESSION_STATEMENT:
                return buildExprStatement(cst);
            case CST::NodeKind::MATCH_STATEMENT:
                return buildMatchStatement(cst);
            case CST::NodeKind::PARALLEL_STATEMENT:
                return buildParallelStatement(cst);
            case CST::NodeKind::CONCURRENT_STATEMENT:
                return buildConcurrentStatement(cst);
            case CST::NodeKind::ERROR_NODE:
            case CST::NodeKind::MISSING_NODE:
            case CST::NodeKind::INCOMPLETE_NODE:
                return std::dynamic_pointer_cast<AST::Statement>(handleErrorRecoveryNode(cst));
            default:
                auto result = createErrorStmt("Unsupported statement type: " + cst.getKindName(), cst);
                // Restore declaration context
                if (strategy == TypeResolutionStrategy::IMMEDIATE && !wasInDeclarationContext) {
                    exitDeclarationContext();
                }
                return result;
        }
        
        // Restore declaration context
        if (strategy == TypeResolutionStrategy::IMMEDIATE && !wasInDeclarationContext) {
            exitDeclarationContext();
        }
        
        return nullptr; // This should never be reached due to switch cases
    }

    std::shared_ptr<AST::Expression> ASTBuilder::buildExpression(const CST::Node& cst, TypeResolutionStrategy strategy) {
        incrementTransformedNodes();
        
        // Enter expression context for deferred type resolution
        bool wasInExpressionContext = typeContext_.inExpressionContext;
        if (strategy == TypeResolutionStrategy::DEFERRED) {
            enterExpressionContext();
        }
        
        switch (cst.kind) {
            case CST::NodeKind::BINARY_EXPR:
                return buildBinaryExpr(cst);
            case CST::NodeKind::UNARY_EXPR:
                return buildUnaryExpr(cst);
            case CST::NodeKind::CALL_EXPR:
                return buildCallExpr(cst);
            case CST::NodeKind::MEMBER_EXPR:
                return buildMemberExpr(cst);
            case CST::NodeKind::INDEX_EXPR:
                return buildIndexExpr(cst);
            case CST::NodeKind::LITERAL_EXPR:
                return buildLiteralExpr(cst);
            case CST::NodeKind::VARIABLE_EXPR:
                return buildVariableExpr(cst);
            case CST::NodeKind::GROUPING_EXPR:
                return buildGroupingExpr(cst);
            case CST::NodeKind::ASSIGNMENT_EXPR:
                return buildAssignExpr(cst);
            case CST::NodeKind::CONDITIONAL_EXPR:
                return buildTernaryExpr(cst);
            case CST::NodeKind::RANGE_EXPR:
                return buildRangeExpr(cst);
            case CST::NodeKind::LAMBDA_EXPR:
                return buildLambdaExpr(cst);
            case CST::NodeKind::INTERPOLATION_EXPR:
                return buildInterpolatedStringExpr(cst);
            case CST::NodeKind::ERROR_NODE:
            case CST::NodeKind::MISSING_NODE:
            case CST::NodeKind::INCOMPLETE_NODE: {
                auto result = std::dynamic_pointer_cast<AST::Expression>(handleErrorRecoveryNode(cst));
                // Restore expression context
                if (strategy == TypeResolutionStrategy::DEFERRED && !wasInExpressionContext) {
                    exitExpressionContext();
                }
                return result;
            }
            default: {
                auto errorResult = createErrorExpr("Unsupported expression type: " + cst.getKindName(), cst);
                // Restore expression context
                if (strategy == TypeResolutionStrategy::DEFERRED && !wasInExpressionContext) {
                    exitExpressionContext();
                }
                return errorResult;
            }
        }
        
        // This should never be reached, but restore context just in case
        if (strategy == TypeResolutionStrategy::DEFERRED && !wasInExpressionContext) {
            exitExpressionContext();
        }
        
        return nullptr;
    }

    // Declaration transformation methods
    std::shared_ptr<AST::VarDeclaration> ASTBuilder::buildVarDeclaration(const CST::Node& cst) {
        auto varDecl = std::make_shared<AST::VarDeclaration>();
        copySourceInfo(cst, *varDecl);
        
        // Extract variable name
        auto nameNode = findChild(cst, CST::NodeKind::IDENTIFIER);
        if (nameNode) {
            varDecl->name = extractIdentifier(*nameNode);
        } else {
            reportError("Missing variable name in declaration", cst);
            varDecl->name = "<missing>";
        }
        
        // Resolve type annotation using early type resolution
        resolveDeclarationType(varDecl, cst);
        
        // Extract initializer if present
        auto initNode = findChild(cst, CST::NodeKind::INITIALIZER);
        if (initNode) {
            auto initChildren = getSignificantChildren(*initNode);
            if (!initChildren.empty()) {
                varDecl->initializer = buildExpression(*initChildren[0]);
            }
        }
        
        addSourceMapping(cst, varDecl);
        return varDecl;
    }

    std::shared_ptr<AST::FunctionDeclaration> ASTBuilder::buildFunctionDeclaration(const CST::Node& cst) {
        auto funcDecl = std::make_shared<AST::FunctionDeclaration>();
        copySourceInfo(cst, *funcDecl);
        
        // Extract function name
        auto nameNode = findChild(cst, CST::NodeKind::IDENTIFIER);
        if (nameNode) {
            funcDecl->name = extractIdentifier(*nameNode);
        } else {
            reportError("Missing function name in declaration", cst);
            funcDecl->name = "<missing>";
        }
        
        // Resolve function signature using early type resolution
        resolveFunctionSignature(funcDecl, cst);
        
        // Extract function body
        auto bodyNode = findChild(cst, CST::NodeKind::BLOCK_STATEMENT);
        if (bodyNode) {
            funcDecl->body = buildBlockStatement(*bodyNode);
        } else {
            reportError("Missing function body", cst);
            funcDecl->body = std::make_shared<AST::BlockStatement>();
        }
        
        addSourceMapping(cst, funcDecl);
        return funcDecl;
    }

    std::shared_ptr<AST::ClassDeclaration> ASTBuilder::buildClassDeclaration(const CST::Node& cst) {
        auto classDecl = std::make_shared<AST::ClassDeclaration>();
        copySourceInfo(cst, *classDecl);
        
        // Extract class name
        auto nameNode = findChild(cst, CST::NodeKind::IDENTIFIER);
        if (nameNode) {
            classDecl->name = extractIdentifier(*nameNode);
        } else {
            reportError("Missing class name in declaration", cst);
            classDecl->name = "<missing>";
        }
        
        // Extract fields and methods from class body
        auto bodyNode = findChild(cst, CST::NodeKind::BLOCK_STATEMENT);
        if (bodyNode) {
            auto children = getSignificantChildren(*bodyNode);
            for (const auto& child : children) {
                if (child->kind == CST::NodeKind::VAR_DECLARATION) {
                    auto field = buildVarDeclaration(*child);
                    if (field) {
                        classDecl->fields.push_back(field);
                    }
                } else if (child->kind == CST::NodeKind::FUNCTION_DECLARATION) {
                    auto method = buildFunctionDeclaration(*child);
                    if (method) {
                        classDecl->methods.push_back(method);
                    }
                }
            }
        }
        
        addSourceMapping(cst, classDecl);
        return classDecl;
    }

    // Expression transformation methods
    std::shared_ptr<AST::BinaryExpr> ASTBuilder::buildBinaryExpr(const CST::Node& cst) {
        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        copySourceInfo(cst, *binaryExpr);
        
        // Binary expressions should have left operand, operator, right operand
        auto children = getSignificantChildren(cst);
        auto tokens = getSignificantTokens(cst);
        
        if (children.size() >= 2) {
            binaryExpr->left = buildExpression(*children[0]);
            binaryExpr->right = buildExpression(*children[children.size() - 1]);
            
            // Extract operator from tokens
            if (!tokens.empty()) {
                // Find the operator token (usually in the middle)
                for (const auto& token : tokens) {
                    if (ASTBuilderUtils::isBinaryOperator(token.type)) {
                        binaryExpr->op = token.type;
                        break;
                    }
                }
                if (binaryExpr->op == TokenType::UNDEFINED) {
                    binaryExpr->op = tokens[0].type; // Fallback to first token
                }
            } else {
                reportError("Missing operator in binary expression", cst);
                binaryExpr->op = TokenType::PLUS; // Default fallback
            }
        } else {
            reportError("Invalid binary expression structure", cst);
            binaryExpr->left = createErrorExpr("Missing left operand", cst);
            binaryExpr->right = createErrorExpr("Missing right operand", cst);
            binaryExpr->op = TokenType::PLUS;
        }
        
        addSourceMapping(cst, binaryExpr);
        
        // Defer type resolution for binary expressions
        if (config_.deferExpressionTypes && typeContext_.inExpressionContext) {
            deferExpressionType(binaryExpr, cst, "binary_expression");
        }
        
        return binaryExpr;
    }

    std::shared_ptr<AST::LiteralExpr> ASTBuilder::buildLiteralExpr(const CST::Node& cst) {
        auto literalExpr = std::make_shared<AST::LiteralExpr>();
        copySourceInfo(cst, *literalExpr);
        
        auto tokens = getSignificantTokens(cst);
        if (!tokens.empty()) {
            const auto& token = tokens[0];
            
            switch (token.type) {
                case TokenType::NUMBER:
                    // Try to parse as integer first, then as double
                    try {
                        if (token.lexeme.find('.') != std::string::npos) {
                            literalExpr->value = std::stod(token.lexeme);
                        } else {
                            literalExpr->value = std::stoll(token.lexeme);
                        }
                    } catch (const std::exception&) {
                        reportError("Invalid number literal: " + token.lexeme, cst);
                        literalExpr->value = 0LL;
                    }
                    break;
                    
                case TokenType::STRING:
                    literalExpr->value = ASTBuilderUtils::extractStringLiteral(token);
                    break;
                    
                case TokenType::TRUE:
                    literalExpr->value = true;
                    break;
                    
                case TokenType::FALSE:
                    literalExpr->value = false;
                    break;
                    
                case TokenType::NIL:
                    literalExpr->value = nullptr;
                    break;
                    
                default:
                    reportError("Unsupported literal type: " + token.lexeme, cst);
                    literalExpr->value = token.lexeme;
                    break;
            }
        } else {
            reportError("Empty literal expression", cst);
            literalExpr->value = nullptr;
        }
        
        addSourceMapping(cst, literalExpr);
        return literalExpr;
    }

    std::shared_ptr<AST::VariableExpr> ASTBuilder::buildVariableExpr(const CST::Node& cst) {
        auto varExpr = std::make_shared<AST::VariableExpr>();
        copySourceInfo(cst, *varExpr);
        
        auto tokens = getSignificantTokens(cst);
        if (!tokens.empty() && tokens[0].type == TokenType::IDENTIFIER) {
            varExpr->name = tokens[0].lexeme;
        } else {
            reportError("Invalid variable expression", cst);
            varExpr->name = "<invalid>";
        }
        
        addSourceMapping(cst, varExpr);
        return varExpr;
    }

    // Error-tolerant node creation
    std::shared_ptr<AST::Expression> ASTBuilder::createErrorExpr(const std::string& message, const CST::Node& cst) {
        incrementErrorNodes();
        reportError(message, cst);
        
        if (!config_.insertErrorNodes) {
            return nullptr;
        }
        
        // Create a literal expression with error message as placeholder
        auto errorExpr = std::make_shared<AST::LiteralExpr>();
        copySourceInfo(cst, *errorExpr);
        errorExpr->value = "<ERROR: " + message + ">";
        
        addSourceMapping(cst, errorExpr);
        return errorExpr;
    }

    std::shared_ptr<AST::Statement> ASTBuilder::createErrorStmt(const std::string& message, const CST::Node& cst) {
        incrementErrorNodes();
        reportError(message, cst);
        
        if (!config_.insertErrorNodes) {
            return nullptr;
        }
        
        // Create an expression statement with error expression
        auto errorStmt = std::make_shared<AST::ExprStatement>();
        copySourceInfo(cst, *errorStmt);
        errorStmt->expression = createErrorExpr(message, cst);
        
        addSourceMapping(cst, errorStmt);
        return errorStmt;
    }

    std::shared_ptr<AST::Expression> ASTBuilder::createMissingExpr(const std::string& description, const CST::Node& cst) {
        incrementMissingNodes();
        
        if (!config_.insertMissingNodes) {
            return nullptr;
        }
        
        // Create a literal expression with missing description
        auto missingExpr = std::make_shared<AST::LiteralExpr>();
        copySourceInfo(cst, *missingExpr);
        missingExpr->value = "<MISSING: " + description + ">";
        
        addSourceMapping(cst, missingExpr);
        return missingExpr;
    }

    // Helper methods for CST navigation
    const CST::Node* ASTBuilder::findChild(const CST::Node& parent, CST::NodeKind kind) const {
        return parent.findChild(kind);
    }

    std::vector<const CST::Node*> ASTBuilder::findChildren(const CST::Node& parent, CST::NodeKind kind) const {
        auto children = parent.findChildren(kind);
        std::vector<const CST::Node*> result;
        for (auto* child : children) {
            result.push_back(child);
        }
        return result;
    }

    std::vector<Token> ASTBuilder::getSignificantTokens(const CST::Node& node) const {
        return node.getSignificantTokens();
    }

    std::vector<const CST::Node*> ASTBuilder::getSignificantChildren(const CST::Node& node) const {
        auto children = node.getSignificantChildren();
        std::vector<const CST::Node*> result;
        for (auto* child : children) {
            result.push_back(child);
        }
        return result;
    }

    Token ASTBuilder::findFirstToken(const CST::Node& node, TokenType type) const {
        auto tokens = node.getSignificantTokens();
        for (const auto& token : tokens) {
            if (token.type == type) {
                return token;
            }
        }
        return Token{TokenType::UNDEFINED, "", 0, 0, 0, {}, {}};
    }

    std::string ASTBuilder::reconstructSource(const CST::Node& node, bool includeTrivia) const {
        return includeTrivia ? node.getText() : node.getTextWithoutTrivia();
    }

    std::string ASTBuilder::extractIdentifier(const CST::Node& node) const {
        auto tokens = node.getSignificantTokens();
        for (const auto& token : tokens) {
            if (token.type == TokenType::IDENTIFIER) {
                return token.lexeme;
            }
        }
        return "<invalid>";
    }

    // Source mapping utilities
    void ASTBuilder::addSourceMapping(const CST::Node& cst, std::shared_ptr<AST::Node> ast) {
        if (config_.preserveSourceMapping) {
            sourceMappings_.emplace_back(&cst, ast);
        }
    }

    void ASTBuilder::copySourceInfo(const CST::Node& cst, AST::Node& ast) {
        // For now, we'll use startPos as line number (this could be enhanced)
        ast.line = static_cast<int>(cst.startPos);
    }

    // Error reporting utilities
    void ASTBuilder::reportError(const std::string& message, const CST::Node& cst) {
        if (errors_.size() >= config_.maxErrors) {
            return; // Stop reporting after max errors
        }
        
        errors_.emplace_back(message, &cst);
    }

    bool ASTBuilder::shouldContinueOnError() const {
        return !config_.strictMode && errors_.size() < config_.maxErrors;
    }

    // Validation utilities
    bool ASTBuilder::validateCST(const CST::Node& cst) const {
        return cst.kind != CST::NodeKind::ERROR_NODE || config_.insertErrorNodes;
    }

    bool ASTBuilder::isValidStatementNode(const CST::Node& cst) const {
        return ASTBuilderUtils::isStatementKind(cst.kind) || 
               ASTBuilderUtils::isDeclarationKind(cst.kind) ||
               (cst.kind == CST::NodeKind::ERROR_NODE && config_.insertErrorNodes);
    }

    bool ASTBuilder::isValidExpressionNode(const CST::Node& cst) const {
        return ASTBuilderUtils::isExpressionKind(cst.kind) ||
               (cst.kind == CST::NodeKind::ERROR_NODE && config_.insertErrorNodes);
    }

    // Handle error recovery nodes
    std::shared_ptr<AST::Node> ASTBuilder::handleErrorRecoveryNode(const CST::Node& cst) {
        switch (cst.kind) {
            case CST::NodeKind::ERROR_NODE:
                return createErrorExpr("Error in source: " + cst.errorMessage, cst);
            case CST::NodeKind::MISSING_NODE:
                return handleMissingNode(static_cast<const CST::MissingNode&>(cst));
            case CST::NodeKind::INCOMPLETE_NODE:
                return handleIncompleteNode(static_cast<const CST::IncompleteNode&>(cst));
            default:
                return createErrorExpr("Unknown error recovery node", cst);
        }
    }

    std::shared_ptr<AST::Node> ASTBuilder::handleMissingNode(const CST::MissingNode& missing) {
        std::string description = "Missing " + CST::nodeKindToString(missing.expectedKind);
        if (!missing.description.empty()) {
            description += ": " + missing.description;
        }
        return createMissingExpr(description, missing);
    }

    std::shared_ptr<AST::Node> ASTBuilder::handleIncompleteNode(const CST::IncompleteNode& incomplete) {
        std::string description = "Incomplete " + CST::nodeKindToString(incomplete.targetKind);
        if (!incomplete.description.empty()) {
            description += ": " + incomplete.description;
        }
        return createErrorExpr(description, incomplete);
    }

    // Type annotation building with strategy support
    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::buildTypeAnnotation(const CST::Node& cst, TypeResolutionStrategy strategy) {
        // Basic implementation - can be expanded
        auto typeAnnotation = std::make_shared<AST::TypeAnnotation>();
        
        // Use the appropriate resolution strategy
        switch (strategy) {
            case TypeResolutionStrategy::IMMEDIATE:
                return resolveTypeImmediate(cst);
            case TypeResolutionStrategy::DEFERRED:
                return createDeferredType("deferred_type");
            case TypeResolutionStrategy::PARTIAL:
                return resolveTypePartial(cst);
            default:
                break;
        }
        
        // Fallback to basic implementation
        auto tokens = getSignificantTokens(cst);
        if (!tokens.empty()) {
            typeAnnotation->typeName = tokens[0].lexeme;
            typeAnnotation->isPrimitive = ASTBuilderUtils::isPrimitiveTypeName(typeAnnotation->typeName);
        }
        
        return typeAnnotation;
    }

    // Additional stub implementations for completeness
    std::shared_ptr<AST::TypeDeclaration> ASTBuilder::buildTypeDeclaration(const CST::Node& cst) {
        return std::make_shared<AST::TypeDeclaration>();
    }

    std::shared_ptr<AST::EnumDeclaration> ASTBuilder::buildEnumDeclaration(const CST::Node& cst) {
        return std::make_shared<AST::EnumDeclaration>();
    }

    std::shared_ptr<AST::ImportStatement> ASTBuilder::buildImportStatement(const CST::Node& cst) {
        return std::make_shared<AST::ImportStatement>();
    }

    std::shared_ptr<AST::IfStatement> ASTBuilder::buildIfStatement(const CST::Node& cst) {
        return std::make_shared<AST::IfStatement>();
    }

    std::shared_ptr<AST::ForStatement> ASTBuilder::buildForStatement(const CST::Node& cst) {
        return std::make_shared<AST::ForStatement>();
    }

    std::shared_ptr<AST::WhileStatement> ASTBuilder::buildWhileStatement(const CST::Node& cst) {
        return std::make_shared<AST::WhileStatement>();
    }

    std::shared_ptr<AST::IterStatement> ASTBuilder::buildIterStatement(const CST::Node& cst) {
        return std::make_shared<AST::IterStatement>();
    }

    std::shared_ptr<AST::BlockStatement> ASTBuilder::buildBlockStatement(const CST::Node& cst) {
        auto blockStmt = std::make_shared<AST::BlockStatement>();
        copySourceInfo(cst, *blockStmt);
        
        // Transform all significant child statements
        auto children = getSignificantChildren(cst);
        for (const auto& child : children) {
            if (child && isValidStatementNode(*child)) {
                auto stmt = buildStatement(*child);
                if (stmt) {
                    blockStmt->statements.push_back(stmt);
                }
            }
        }
        
        addSourceMapping(cst, blockStmt);
        return blockStmt;
    }

    std::shared_ptr<AST::ReturnStatement> ASTBuilder::buildReturnStatement(const CST::Node& cst) {
        return std::make_shared<AST::ReturnStatement>();
    }

    std::shared_ptr<AST::BreakStatement> ASTBuilder::buildBreakStatement(const CST::Node& cst) {
        return std::make_shared<AST::BreakStatement>();
    }

    std::shared_ptr<AST::ContinueStatement> ASTBuilder::buildContinueStatement(const CST::Node& cst) {
        return std::make_shared<AST::ContinueStatement>();
    }

    std::shared_ptr<AST::PrintStatement> ASTBuilder::buildPrintStatement(const CST::Node& cst) {
        return std::make_shared<AST::PrintStatement>();
    }

    std::shared_ptr<AST::ExprStatement> ASTBuilder::buildExprStatement(const CST::Node& cst) {
        auto exprStmt = std::make_shared<AST::ExprStatement>();
        copySourceInfo(cst, *exprStmt);
        
        auto children = getSignificantChildren(cst);
        if (!children.empty()) {
            exprStmt->expression = buildExpression(*children[0]);
        }
        
        addSourceMapping(cst, exprStmt);
        return exprStmt;
    }

    std::shared_ptr<AST::MatchStatement> ASTBuilder::buildMatchStatement(const CST::Node& cst) {
        return std::make_shared<AST::MatchStatement>();
    }

    std::shared_ptr<AST::ParallelStatement> ASTBuilder::buildParallelStatement(const CST::Node& cst) {
        return std::make_shared<AST::ParallelStatement>();
    }

    std::shared_ptr<AST::ConcurrentStatement> ASTBuilder::buildConcurrentStatement(const CST::Node& cst) {
        return std::make_shared<AST::ConcurrentStatement>();
    }

    std::shared_ptr<AST::UnaryExpr> ASTBuilder::buildUnaryExpr(const CST::Node& cst) {
        return std::make_shared<AST::UnaryExpr>();
    }

    std::shared_ptr<AST::CallExpr> ASTBuilder::buildCallExpr(const CST::Node& cst) {
        return std::make_shared<AST::CallExpr>();
    }

    std::shared_ptr<AST::MemberExpr> ASTBuilder::buildMemberExpr(const CST::Node& cst) {
        return std::make_shared<AST::MemberExpr>();
    }

    std::shared_ptr<AST::IndexExpr> ASTBuilder::buildIndexExpr(const CST::Node& cst) {
        return std::make_shared<AST::IndexExpr>();
    }

    std::shared_ptr<AST::GroupingExpr> ASTBuilder::buildGroupingExpr(const CST::Node& cst) {
        return std::make_shared<AST::GroupingExpr>();
    }

    std::shared_ptr<AST::AssignExpr> ASTBuilder::buildAssignExpr(const CST::Node& cst) {
        return std::make_shared<AST::AssignExpr>();
    }

    std::shared_ptr<AST::TernaryExpr> ASTBuilder::buildTernaryExpr(const CST::Node& cst) {
        return std::make_shared<AST::TernaryExpr>();
    }

    std::shared_ptr<AST::RangeExpr> ASTBuilder::buildRangeExpr(const CST::Node& cst) {
        return std::make_shared<AST::RangeExpr>();
    }

    std::shared_ptr<AST::ListExpr> ASTBuilder::buildListExpr(const CST::Node& cst) {
        return std::make_shared<AST::ListExpr>();
    }

    std::shared_ptr<AST::DictExpr> ASTBuilder::buildDictExpr(const CST::Node& cst) {
        return std::make_shared<AST::DictExpr>();
    }

    std::shared_ptr<AST::LambdaExpr> ASTBuilder::buildLambdaExpr(const CST::Node& cst) {
        return std::make_shared<AST::LambdaExpr>();
    }

    std::shared_ptr<AST::InterpolatedStringExpr> ASTBuilder::buildInterpolatedStringExpr(const CST::Node& cst) {
        return std::make_shared<AST::InterpolatedStringExpr>();
    }

    std::shared_ptr<AST::FallibleExpr> ASTBuilder::buildFallibleExpr(const CST::Node& cst) {
        return std::make_shared<AST::FallibleExpr>();
    }

    std::vector<std::pair<std::string, std::shared_ptr<AST::TypeAnnotation>>> 
    ASTBuilder::buildParameterList(const CST::Node& cst) {
        std::vector<std::pair<std::string, std::shared_ptr<AST::TypeAnnotation>>> params;
        // Implementation stub
        return params;
    }

    std::vector<std::shared_ptr<AST::Expression>> ASTBuilder::buildArgumentList(const CST::Node& cst) {
        std::vector<std::shared_ptr<AST::Expression>> args;
        // Implementation stub
        return args;
    }

    std::shared_ptr<AST::Expression> ASTBuilder::buildPattern(const CST::Node& cst) {
        return std::make_shared<AST::LiteralExpr>();
    }

    std::vector<AST::MatchCase> ASTBuilder::buildMatchCases(const CST::Node& cst) {
        std::vector<AST::MatchCase> cases;
        // Implementation stub
        return cases;
    }

    // Utility functions implementation
    namespace ASTBuilderUtils {
        bool isStatementKind(CST::NodeKind kind) {
            switch (kind) {
                case CST::NodeKind::IF_STATEMENT:
                case CST::NodeKind::FOR_STATEMENT:
                case CST::NodeKind::WHILE_STATEMENT:
                case CST::NodeKind::ITER_STATEMENT:
                case CST::NodeKind::BLOCK_STATEMENT:
                case CST::NodeKind::EXPRESSION_STATEMENT:
                case CST::NodeKind::RETURN_STATEMENT:
                case CST::NodeKind::BREAK_STATEMENT:
                case CST::NodeKind::CONTINUE_STATEMENT:
                case CST::NodeKind::PRINT_STATEMENT:
                case CST::NodeKind::MATCH_STATEMENT:
                case CST::NodeKind::ATTEMPT_STATEMENT:
                case CST::NodeKind::PARALLEL_STATEMENT:
                case CST::NodeKind::CONCURRENT_STATEMENT:
                    return true;
                default:
                    return false;
            }
        }

        bool isExpressionKind(CST::NodeKind kind) {
            switch (kind) {
                case CST::NodeKind::BINARY_EXPR:
                case CST::NodeKind::UNARY_EXPR:
                case CST::NodeKind::CALL_EXPR:
                case CST::NodeKind::MEMBER_EXPR:
                case CST::NodeKind::INDEX_EXPR:
                case CST::NodeKind::LITERAL_EXPR:
                case CST::NodeKind::VARIABLE_EXPR:
                case CST::NodeKind::GROUPING_EXPR:
                case CST::NodeKind::ASSIGNMENT_EXPR:
                case CST::NodeKind::CONDITIONAL_EXPR:
                case CST::NodeKind::LAMBDA_EXPR:
                case CST::NodeKind::RANGE_EXPR:
                case CST::NodeKind::INTERPOLATION_EXPR:
                    return true;
                default:
                    return false;
            }
        }

        bool isDeclarationKind(CST::NodeKind kind) {
            switch (kind) {
                case CST::NodeKind::VAR_DECLARATION:
                case CST::NodeKind::FUNCTION_DECLARATION:
                case CST::NodeKind::CLASS_DECLARATION:
                case CST::NodeKind::ENUM_DECLARATION:
                case CST::NodeKind::TYPE_DECLARATION:
                case CST::NodeKind::TRAIT_DECLARATION:
                case CST::NodeKind::INTERFACE_DECLARATION:
                case CST::NodeKind::MODULE_DECLARATION:
                case CST::NodeKind::IMPORT_DECLARATION:
                    return true;
                default:
                    return false;
            }
        }

        bool isTypeKind(CST::NodeKind kind) {
            switch (kind) {
                case CST::NodeKind::PRIMITIVE_TYPE:
                case CST::NodeKind::FUNCTION_TYPE:
                case CST::NodeKind::LIST_TYPE:
                case CST::NodeKind::DICT_TYPE:
                case CST::NodeKind::ARRAY_TYPE:
                case CST::NodeKind::UNION_TYPE:
                case CST::NodeKind::OPTION_TYPE:
                case CST::NodeKind::RESULT_TYPE:
                case CST::NodeKind::USER_TYPE:
                case CST::NodeKind::GENERIC_TYPE:
                    return true;
                default:
                    return false;
            }
        }

        std::string extractStringLiteral(const Token& token) {
            std::string result = token.lexeme;
            // Remove quotes if present
            if (result.length() >= 2 && result.front() == '"' && result.back() == '"') {
                result = result.substr(1, result.length() - 2);
            }
            return result;
        }

        long long extractIntegerLiteral(const Token& token) {
            try {
                return std::stoll(token.lexeme);
            } catch (const std::exception&) {
                return 0;
            }
        }

        double extractFloatLiteral(const Token& token) {
            try {
                return std::stod(token.lexeme);
            } catch (const std::exception&) {
                return 0.0;
            }
        }

        bool extractBooleanLiteral(const Token& token) {
            return token.type == TokenType::TRUE;
        }

        bool isPrimitiveTypeName(const std::string& name) {
            return name == "int" || name == "uint" || name == "float" || 
                   name == "bool" || name == "str" || name == "void";
        }

        bool isOptionalTypeAnnotation(const std::string& annotation) {
            return annotation.back() == '?';
        }

        std::vector<std::string> parseUnionTypes(const std::string& typeStr) {
            std::vector<std::string> types;
            std::stringstream ss(typeStr);
            std::string type;
            
            while (std::getline(ss, type, '|')) {
                // Trim whitespace
                type.erase(0, type.find_first_not_of(" \t"));
                type.erase(type.find_last_not_of(" \t") + 1);
                if (!type.empty()) {
                    types.push_back(type);
                }
            }
            
            return types;
        }

        bool isBinaryOperator(TokenType type) {
            switch (type) {
                case TokenType::PLUS:
                case TokenType::MINUS:
                case TokenType::STAR:
                case TokenType::SLASH:
                case TokenType::MODULUS:
                case TokenType::EQUAL_EQUAL:
                case TokenType::BANG_EQUAL:
                case TokenType::GREATER:
                case TokenType::GREATER_EQUAL:
                case TokenType::LESS:
                case TokenType::LESS_EQUAL:
                case TokenType::AND:
                case TokenType::OR:
                case TokenType::AMPERSAND:
                case TokenType::PIPE:
                case TokenType::CARET:
                    return true;
                default:
                    return false;
            }
        }

        bool isUnaryOperator(TokenType type) {
            switch (type) {
                case TokenType::BANG:
                case TokenType::MINUS:
                case TokenType::TILDE:
                    return true;
                default:
                    return false;
            }
        }

        bool isAssignmentOperator(TokenType type) {
            switch (type) {
                case TokenType::EQUAL:
                case TokenType::PLUS_EQUAL:
                case TokenType::MINUS_EQUAL:
                case TokenType::STAR_EQUAL:
                case TokenType::SLASH_EQUAL:
                case TokenType::MODULUS_EQUAL:
                    return true;
                default:
                    return false;
            }
        }
    }

    // Type resolution context methods
    void TypeResolutionContext::enterScope(const std::string& scopeName) {
        currentScope.push_back(scopeName);
    }

    void TypeResolutionContext::exitScope() {
        if (!currentScope.empty()) {
            currentScope.pop_back();
        }
    }

    void TypeResolutionContext::addDeclaredType(const std::string& name, std::shared_ptr<AST::TypeAnnotation> type) {
        std::string fullName = getCurrentScopePath() + "::" + name;
        declaredTypes[fullName] = type;
        declaredTypes[name] = type;  // Also add unqualified name for current scope
    }

    std::shared_ptr<AST::TypeAnnotation> TypeResolutionContext::lookupType(const std::string& name) const {
        // Try fully qualified name first
        std::string fullName = getCurrentScopePath() + "::" + name;
        auto it = declaredTypes.find(fullName);
        if (it != declaredTypes.end()) {
            return it->second;
        }
        
        // Try unqualified name
        it = declaredTypes.find(name);
        if (it != declaredTypes.end()) {
            return it->second;
        }
        
        // Try builtin types
        auto builtinIt = builtinTypes.find(name);
        if (builtinIt != builtinTypes.end()) {
            return builtinIt->second;
        }
        
        return nullptr;
    }

    std::string TypeResolutionContext::getCurrentScopePath() const {
        std::string path;
        for (size_t i = 0; i < currentScope.size(); ++i) {
            if (i > 0) path += "::";
            path += currentScope[i];
        }
        return path;
    }

    // Unified type resolution methods
    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveTypeImmediate(const CST::Node& cst) {
        auto tokens = getSignificantTokens(cst);
        if (tokens.empty()) {
            return nullptr;
        }
        
        const std::string& typeName = tokens[0].lexeme;
        
        // Try builtin types first
        auto builtinType = resolveBuiltinType(typeName);
        if (builtinType) {
            return builtinType;
        }
        
        // Try user-defined types
        auto userType = resolveUserDefinedType(typeName);
        if (userType) {
            return userType;
        }
        
        // Handle complex types (generics, unions, etc.)
        switch (cst.kind) {
            case CST::NodeKind::UNION_TYPE:
                return resolveUnionType(cst);
            case CST::NodeKind::FUNCTION_TYPE:
                return resolveFunctionType(cst);
            case CST::NodeKind::LIST_TYPE:
            case CST::NodeKind::DICT_TYPE:
            case CST::NodeKind::ARRAY_TYPE:
                return resolveContainerType(cst);
            case CST::NodeKind::GENERIC_TYPE:
                return resolveGenericType(cst);
            default:
                break;
        }
        
        // Create a user-defined type placeholder
        auto typeAnnotation = std::make_shared<AST::TypeAnnotation>();
        typeAnnotation->typeName = typeName;
        typeAnnotation->isUserDefined = true;
        
        return typeAnnotation;
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveTypePartial(const CST::Node& cst) {
        // Try immediate resolution first, fall back to deferred if needed
        auto immediateType = resolveTypeImmediate(cst);
        if (immediateType && immediateType->isPrimitive) {
            return immediateType;  // Primitives can be resolved immediately
        }
        
        // For complex types, create a partial resolution
        return createDeferredType("partial_" + std::to_string(deferredResolutions_.size()));
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveTypeDeferred(const CST::Node& cst, std::shared_ptr<AST::Expression> expr) {
        // Create a deferred type placeholder
        auto deferredType = createDeferredType("deferred_" + std::to_string(deferredResolutions_.size()));
        
        // Add to deferred resolutions
        deferredResolutions_.emplace_back(expr, &cst, "expression_type", TypeResolutionStrategy::DEFERRED);
        
        return deferredType;
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveBuiltinType(const std::string& typeName) {
        auto it = typeContext_.builtinTypes.find(typeName);
        if (it != typeContext_.builtinTypes.end()) {
            return it->second;
        }
        return nullptr;
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveUserDefinedType(const std::string& typeName) {
        return typeContext_.lookupType(typeName);
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::createDeferredType(const std::string& placeholder) {
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->typeName = placeholder;
        type->isUserDefined = true;  // Mark as user-defined to distinguish from primitives
        return type;
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::createInferredType(const std::string& hint) {
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->typeName = hint.empty() ? "inferred" : ("inferred_" + hint);
        type->isUserDefined = true;
        return type;
    }

    void ASTBuilder::initializeBuiltinTypes() {
        // Initialize primitive types
        registerBuiltinType("int", true);
        registerBuiltinType("uint", true);
        registerBuiltinType("float", true);
        registerBuiltinType("bool", true);
        registerBuiltinType("str", true);
        registerBuiltinType("void", true);
        
        // Initialize container types
        registerBuiltinType("list", false);
        registerBuiltinType("dict", false);
        registerBuiltinType("array", false);
        
        // Initialize special types
        registerBuiltinType("Option", false);
        registerBuiltinType("Result", false);
        registerBuiltinType("None", false);
        registerBuiltinType("Some", false);
    }

    void ASTBuilder::registerBuiltinType(const std::string& name, bool isPrimitive) {
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->typeName = name;
        type->isPrimitive = isPrimitive;
        type->isUserDefined = false;
        
        typeContext_.builtinTypes[name] = type;
    }

    void ASTBuilder::enterDeclarationContext() {
        typeContext_.inDeclarationContext = true;
    }

    void ASTBuilder::exitDeclarationContext() {
        typeContext_.inDeclarationContext = false;
    }

    void ASTBuilder::enterExpressionContext() {
        typeContext_.inExpressionContext = true;
    }

    void ASTBuilder::exitExpressionContext() {
        typeContext_.inExpressionContext = false;
    }

    void ASTBuilder::resolveDeclarationType(std::shared_ptr<AST::VarDeclaration> varDecl, const CST::Node& cst) {
        if (!config_.enableEarlyTypeResolution) {
            return;
        }
        
        // Find type annotation in CST
        auto typeNode = findChild(cst, CST::NodeKind::PRIMITIVE_TYPE);
        if (!typeNode) typeNode = findChild(cst, CST::NodeKind::USER_TYPE);
        if (!typeNode) typeNode = findChild(cst, CST::NodeKind::UNION_TYPE);
        
        if (typeNode) {
            varDecl->type = resolveTypeImmediate(*typeNode);
            
            // Add to type context for future lookups
            if (varDecl->type) {
                typeContext_.addDeclaredType(varDecl->name, *varDecl->type);
            }
        }
    }

    void ASTBuilder::resolveFunctionSignature(std::shared_ptr<AST::FunctionDeclaration> funcDecl, const CST::Node& cst) {
        if (!config_.enableEarlyTypeResolution) {
            return;
        }
        
        // Resolve parameter types
        auto paramListNode = findChild(cst, CST::NodeKind::PARAMETER_LIST);
        if (paramListNode) {
            auto paramNodes = findChildren(*paramListNode, CST::NodeKind::PARAMETER);
            for (const auto& paramNode : paramNodes) {
                auto typeNode = findChild(*paramNode, CST::NodeKind::PRIMITIVE_TYPE);
                if (!typeNode) typeNode = findChild(*paramNode, CST::NodeKind::USER_TYPE);
                
                if (typeNode) {
                    auto paramType = resolveTypeImmediate(*typeNode);
                    // Parameter types are resolved and stored in funcDecl->params
                }
            }
        }
        
        // Resolve return type
        auto returnTypeNode = findChild(cst, CST::NodeKind::FUNCTION_TYPE);
        if (returnTypeNode) {
            funcDecl->returnType = resolveTypeImmediate(*returnTypeNode);
        }
    }

    void ASTBuilder::deferExpressionType(std::shared_ptr<AST::Expression> expr, const CST::Node& cst, const std::string& context) {
        if (config_.deferExpressionTypes) {
            deferredResolutions_.emplace_back(expr, &cst, context, TypeResolutionStrategy::DEFERRED);
        }
    }

    void ASTBuilder::processDeferredResolutions() {
        // This method would be called later during semantic analysis
        // to resolve deferred expression types based on context and inference
        for (auto& deferred : deferredResolutions_) {
            // Placeholder for future type inference implementation
            // This would involve analyzing the expression context and inferring types
        }
    }

    // Stub implementations for complex type resolution
    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveUnionType(const CST::Node& cst) {
        auto unionType = std::make_shared<AST::TypeAnnotation>();
        unionType->isUnion = true;
        unionType->typeName = "union";
        
        // Extract union member types
        auto children = getSignificantChildren(cst);
        for (const auto& child : children) {
            auto memberType = resolveTypeImmediate(*child);
            if (memberType) {
                unionType->unionTypes.push_back(memberType);
            }
        }
        
        return unionType;
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveFunctionType(const CST::Node& cst) {
        auto funcType = std::make_shared<AST::TypeAnnotation>();
        funcType->isFunction = true;
        funcType->typeName = "function";
        
        // Resolve parameter and return types
        // Implementation would extract function signature from CST
        
        return funcType;
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveContainerType(const CST::Node& cst) {
        auto containerType = std::make_shared<AST::TypeAnnotation>();
        
        switch (cst.kind) {
            case CST::NodeKind::LIST_TYPE:
                containerType->isList = true;
                containerType->typeName = "list";
                break;
            case CST::NodeKind::DICT_TYPE:
                containerType->isDict = true;
                containerType->typeName = "dict";
                break;
            case CST::NodeKind::ARRAY_TYPE:
                containerType->isList = true;  // Arrays are treated as lists
                containerType->typeName = "array";
                break;
            default:
                break;
        }
        
        // Resolve element types
        auto children = getSignificantChildren(cst);
        if (!children.empty()) {
            containerType->elementType = resolveTypeImmediate(*children[0]);
        }
        
        return containerType;
    }

    std::shared_ptr<AST::TypeAnnotation> ASTBuilder::resolveGenericType(const CST::Node& cst) {
        // Placeholder for generic type resolution
        auto genericType = std::make_shared<AST::TypeAnnotation>();
        genericType->typeName = "generic";
        genericType->isUserDefined = true;
        return genericType;
    }

} // namespace frontend