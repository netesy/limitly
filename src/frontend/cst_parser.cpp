#include "cst_parser.hh"
#include "ast_builder.hh"
#include "../error/error_handling.hh"
#include "../error/error_formatter.hh"
#include "../error/contextual_hint_provider.hh"
#include "../common/debugger.hh"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <chrono>
#include <cassert>
#include <iostream>

namespace CST {

    // Constructor taking vector of tokens from enhanced Scanner
    CSTParser::CSTParser(const std::vector<Token>& tokens) 
        : tokens(tokens), current(0), scanner(nullptr) {
        // Initialize with default recovery configuration
        recoveryConfig = RecoveryConfig{};
    }

    // Alternative constructor taking Scanner directly
    CSTParser::CSTParser(Scanner& scanner, const CSTConfig& config) 
        : current(0), scanner(&scanner) {
        // Scan all tokens including trivia if CST config specifies
        tokens = scanner.scanAllTokens(config);
        
        // Configure recovery based on CST config
        recoveryConfig.preserveTrivia = config.preserveComments || config.preserveWhitespace;
        recoveryConfig.continueOnError = config.emitErrorTokens;
        
        // Initialize unified grammar system
        // initializeUnifiedGrammar(); // Temporarily disabled for compilation
    }

    // Unified Grammar System Implementation
    
    void CSTParser::initializeUnifiedGrammar() {
        // Initialize the unified grammar table with all language rules
        // Temporarily disabled for compilation
        // uncommeted
        initializeCoreGrammar();
        initializeStatementGrammar();
        initializeExpressionGrammar();
        initializeDeclarationGrammar();
        initializeTypeGrammar();
        
        // Optimize rule order for performance
        grammar.optimizeRuleOrder();
        
        // Enable memoization for frequently used rules
        grammar.enableMemoization(true);
        // uncommeted end
    }
    
    void CSTParser::initializeCoreGrammar() {
        // Temporarily disabled for compilation
        // uncommeted
        // Core program structure
        grammar.addRule("program", [this](ParseContext& ctx) -> RuleResult {
            if (ctx.mode == ParserMode::DIRECT_AST) {
                // Direct AST generation
                auto program = std::make_shared<AST::Program>();
                program->line = ctx.peek().line;
                
                while (!ctx.isAtEnd()) {
                    auto stmtResult = executeRule("statement", ctx);
                    if (stmtResult.success && stmtResult.hasAST()) {
                        if (auto stmt = stmtResult.getAST<AST::Statement>()) {
                            program->statements.push_back(stmt);
                        }
                    }
                }
                
                RuleResult result;
                result.node = std::static_pointer_cast<AST::Node>(program);
                result.success = true;
                result.tokensConsumed = ctx.currentToken;
                return result;
            } else {
                // CST generation
                auto programNode = createNode(NodeKind::PROGRAM);
                
                while (!ctx.isAtEnd()) {
                    if (!ctx.skipTriviaCollection) {
                        ctx.collectTrivia();
                    }
                    
                    auto stmtResult = executeRule("statement", ctx);
                    if (stmtResult.success && stmtResult.hasCST()) {
                        // Note: getCST() returns a pointer, we need to create a new unique_ptr
                        // This is a simplified approach - in practice we'd need proper node transfer
                        auto cstNode = stmtResult.getCST();
                        if (cstNode) {
                            // For now, skip adding CST nodes to avoid ownership issues
                            // This would need proper implementation in a real system
                        }
                    }
                }
                
                RuleResult result;
                result.node = std::move(programNode);
                result.success = true;
                result.tokensConsumed = ctx.currentToken;
                return result;
            }
        });
        
        // Core token matching rules
        grammar.addRule("identifier", [this](ParseContext& ctx) -> RuleResult {
            return parseIdentifier(ctx);
        });
        
        grammar.addRule("literal", [this](ParseContext& ctx) -> RuleResult {
            return parseLiteral(ctx);
        });
        // uncommeted end
    }
    
    void CSTParser::initializeStatementGrammar() {
        // Temporarily disabled for compilation
        // uncommeted
        // Statement rule - choice between different statement types
        grammar.addRule("statement", [this](ParseContext& ctx) -> RuleResult {
            return parseChoice({
                "varDeclaration",
                "functionDeclaration", 
                "classDeclaration",
                "ifStatement",
                "forStatement",
                "whileStatement",
                "returnStatement",
                "expressionStatement"
            }, ctx);
        });
        
        // Variable declaration: var identifier : type = expression ;
        grammar.addRule("varDeclaration", [this](ParseContext& ctx) -> RuleResult {
            auto seqResult = parseSequence({
                "var_keyword",
                "identifier",
                "optional_type_annotation",
                "optional_initializer",
                "semicolon"
            }, ctx);
            
            if (ctx.mode == ParserMode::DIRECT_AST && seqResult.success) {
                // Transform to AST VarDeclaration
                auto varDecl = std::make_shared<AST::VarDeclaration>();
                varDecl->line = ctx.peek().line;
                // TODO: Extract name, type, initializer from sequence result
                
                RuleResult result;
                result.node = std::static_pointer_cast<AST::Node>(varDecl);
                result.success = true;
                result.tokensConsumed = seqResult.tokensConsumed;
                return result;
            }
            
            return seqResult;
        });
        
        // Expression statement: expression ;
        grammar.addRule("expressionStatement", [this](ParseContext& ctx) -> RuleResult {
            auto exprResult = executeRule("expression", ctx);
            if (!exprResult.success) return exprResult;
            
            // Optional semicolon
            auto semiResult = executeRule("optional_semicolon", ctx);
            
            if (ctx.mode == ParserMode::DIRECT_AST) {
                auto exprStmt = std::make_shared<AST::ExprStatement>();
                exprStmt->line = ctx.peek().line;
                exprStmt->expression = exprResult.getAST<AST::Expression>();
                
                RuleResult result;
                result.node = std::static_pointer_cast<AST::Node>(exprStmt);
                result.success = true;
                result.tokensConsumed = exprResult.tokensConsumed + semiResult.tokensConsumed;
                return result;
            } else {
                // CST mode - create expression statement node
                auto exprStmtNode = createNode(NodeKind::EXPRESSION_STATEMENT);
                if (exprResult.hasCST()) {
                    // Skip CST node addition for now due to ownership complexity
                }
                
                RuleResult result;
                result.node = std::move(exprStmtNode);
                result.success = true;
                result.tokensConsumed = exprResult.tokensConsumed + semiResult.tokensConsumed;
                return result;
            }
        });
        // uncommeted end
    }
    
    void CSTParser::initializeExpressionGrammar() {
        // Temporarily disabled for compilation
        // uncommeted
        // Expression hierarchy with operator precedence
        grammar.addRule("expression", [this](ParseContext& ctx) -> RuleResult {
            return executeRule("assignmentExpression", ctx);
        });
        
        grammar.addRule("assignmentExpression", [this](ParseContext& ctx) -> RuleResult {
            return executeRule("logicalOrExpression", ctx);
        });
        
        grammar.addRule("logicalOrExpression", [this](ParseContext& ctx) -> RuleResult {
            return parseBinaryExpressionRule("logicalAndExpression", {TokenType::OR}, ctx);
        });
        
        grammar.addRule("logicalAndExpression", [this](ParseContext& ctx) -> RuleResult {
            return parseBinaryExpressionRule("equalityExpression", {TokenType::AND}, ctx);
        });
        
        grammar.addRule("equalityExpression", [this](ParseContext& ctx) -> RuleResult {
            return parseBinaryExpressionRule("comparisonExpression", {TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL}, ctx);
        });
        
        grammar.addRule("comparisonExpression", [this](ParseContext& ctx) -> RuleResult {
            return parseBinaryExpressionRule("termExpression", {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL}, ctx);
        });
        
        grammar.addRule("termExpression", [this](ParseContext& ctx) -> RuleResult {
            return parseBinaryExpressionRule("factorExpression", {TokenType::PLUS, TokenType::MINUS}, ctx);
        });
        
        grammar.addRule("factorExpression", [this](ParseContext& ctx) -> RuleResult {
            return parseBinaryExpressionRule("unaryExpression", {TokenType::STAR, TokenType::SLASH, TokenType::MODULUS}, ctx);
        });
        
        grammar.addRule("unaryExpression", [this](ParseContext& ctx) -> RuleResult {
            if (ctx.match({TokenType::BANG, TokenType::MINUS})) {
                Token op = ctx.advance();
                auto rightResult = executeRule("unaryExpression", ctx);
                
                if (ctx.mode == ParserMode::DIRECT_AST) {
                    auto unaryExpr = std::make_shared<AST::UnaryExpr>();
                    unaryExpr->line = op.line;
                    unaryExpr->op = op.type;
                    unaryExpr->right = rightResult.getAST<AST::Expression>();
                    
                    RuleResult result;
                    result.node = std::static_pointer_cast<AST::Node>(unaryExpr);
                    result.success = true;
                    result.tokensConsumed = 1 + rightResult.tokensConsumed;
                    return result;
                } else {
                    auto unaryNode = createNode(NodeKind::UNARY_EXPR);
                    unaryNode->addToken(op);
                    if (rightResult.hasCST()) {
                        unaryNode->addNode(std::unique_ptr<Node>(rightResult.getCST()));
                    }
                    
                    RuleResult result;
                    result.node = std::move(unaryNode);
                    result.success = true;
                    result.tokensConsumed = 1 + rightResult.tokensConsumed;
                    return result;
                }
            }
            
            return executeRule("primaryExpression", ctx);
        });
        
        grammar.addRule("primaryExpression", [this](ParseContext& ctx) -> RuleResult {
            return parseChoice({
                "literal",
                "identifier", 
                "groupingExpression"
            }, ctx);
        });
        
        grammar.addRule("groupingExpression", [this](ParseContext& ctx) -> RuleResult {
            if (!ctx.match(TokenType::LEFT_PAREN)) {
                RuleResult result;
                result.success = false;
                result.errorMessage = "Expected '('";
                return result;
            }
            
            Token leftParen = ctx.advance();
            auto exprResult = executeRule("expression", ctx);
            
            if (!ctx.match(TokenType::RIGHT_PAREN)) {
                RuleResult result;
                result.success = false;
                result.errorMessage = "Expected ')' after expression";
                return result;
            }
            
            Token rightParen = ctx.advance();
            
            if (ctx.mode == ParserMode::DIRECT_AST) {
                auto groupingExpr = std::make_shared<AST::GroupingExpr>();
                groupingExpr->line = leftParen.line;
                groupingExpr->expression = exprResult.getAST<AST::Expression>();
                
                RuleResult result;
                result.node = std::static_pointer_cast<AST::Node>(groupingExpr);
                result.success = true;
                result.tokensConsumed = 2 + exprResult.tokensConsumed;
                return result;
            } else {
                auto groupingNode = createNode(NodeKind::GROUPING_EXPR);
                groupingNode->addToken(leftParen);
                if (exprResult.hasCST()) {
                    groupingNode->addNode(std::unique_ptr<Node>(exprResult.getCST()));
                }
                groupingNode->addToken(rightParen);
                
                RuleResult result;
                result.node = std::move(groupingNode);
                result.success = true;
                result.tokensConsumed = 2 + exprResult.tokensConsumed;
                return result;
            }
        });
        // uncommeted end
    }
    
    void CSTParser::initializeDeclarationGrammar() {
        // Temporarily disabled for compilation
        // uncommeted
        // Function declaration
        grammar.addRule("functionDeclaration", [this](ParseContext& ctx) -> RuleResult {
            return parseSequence({
                "fn_keyword",
                "identifier",
                "parameterList",
                "optional_return_type",
                "blockStatement"
            }, ctx);
        });
        
        // Class declaration  
        grammar.addRule("classDeclaration", [this](ParseContext& ctx) -> RuleResult {
            return parseSequence({
                "class_keyword",
                "identifier", 
                "optional_inheritance",
                "classBody"
            }, ctx);
        });
        // uncommeted end
    }
    
    void CSTParser::initializeTypeGrammar() {
        // Temporarily disabled for compilation
        // uncommeted
        // Type annotations
        grammar.addRule("typeAnnotation", [this](ParseContext& ctx) -> RuleResult {
            return parseChoice({
                "primitiveType",
                "userType",
                "unionType",
                "optionType"
            }, ctx);
        });
        
        // Optional type annotation: : type
        grammar.addRule("optional_type_annotation", [this](ParseContext& ctx) -> RuleResult {
            if (ctx.match(TokenType::COLON)) {
                ctx.advance();
                return executeRule("typeAnnotation", ctx);
            }
            
            RuleResult result;
            result.success = true;  // Optional, so success even if not present
            result.tokensConsumed = 0;
            return result;
        });
        // uncommeted end
    }

    // Main parsing entry point
    std::unique_ptr<Node> CSTParser::parse() {
        // Clear any previous errors
        errors.clear();
        current = 0;
        
        // Delegate to parseCST for the actual parsing logic
        return parseCST();
    }
    
    // Unified grammar parsing methods
    
    template<typename OutputType>
    std::shared_ptr<OutputType> CSTParser::parseRule(const std::string& ruleName, ParserMode mode) {
        setParserMode(mode);
        
        ParseContext context(mode, this, tokens);
        auto result = executeRule(ruleName, context);
        
        if (result.success) {
            return result.getAST<OutputType>();
        }
        
        return nullptr;
    }
    
    std::shared_ptr<AST::Program> CSTParser::parseAST() {
        return parseRule<AST::Program>("program", ParserMode::DIRECT_AST);
    }
    
    std::shared_ptr<AST::Program> CSTParser::parseViaCST() {
        // First generate CST
        auto cst = parseRule<CST::Node>("program", ParserMode::CST_ONLY);
        if (!cst) return nullptr;
        
        // Then transform to AST using ASTBuilder
        frontend::ASTBuilder builder;
        return builder.buildAST(*cst);
    }
    
    RuleResult CSTParser::executeRule(const std::string& ruleName, ParseContext& context) {
        // Check cache first if memoization is enabled
        if (shouldUseCache(ruleName)) {
            auto cached = getCachedResult(ruleName, context.currentToken);
            if (cached) {
                stats.cacheHits++;
                return std::move(*cached);
            }
            stats.cacheMisses++;
        }
        
        // Execute the rule
        auto startTime = std::chrono::high_resolution_clock::now();
        auto result = grammar.executeRule(ruleName, context);
        auto endTime = std::chrono::high_resolution_clock::now();
        
        // Update statistics
        stats.rulesExecuted++;
        stats.parseTimeMs += std::chrono::duration<double, std::milli>(endTime - startTime).count();
        
        // Cache the result if appropriate
        if (shouldUseCache(ruleName) && result.success) {
            cacheResult(ruleName, context.currentToken, result);
        }
        
        return result;
    }
    
    // Core parsing combinators implementation

    RuleResult CSTParser::parseSequence(const std::vector<std::string>& elements, ParseContext& context) {
        RuleResult result;
        result.success = true;
        result.tokensConsumed = 0;
        
        std::vector<RuleResult> elementResults;
        
        for (const auto& element : elements) {
            auto elementResult = executeRule(element, context);
            if (!elementResult.success) {
                result.success = false;
                result.errorMessage = "Failed to parse sequence element: " + element + " - " + elementResult.errorMessage;
                return result;
            }
            
            elementResults.push_back(std::move(elementResult));
            result.tokensConsumed += elementResult.tokensConsumed;
        }
        
        // Create appropriate output node based on mode
        if (context.mode == ParserMode::DIRECT_AST) {
            // For AST mode, we need to combine the results appropriately
            // This is context-dependent and would be handled by specific rule implementations
            result.success = true;
        } else {
            // For CST mode, create a sequence node containing all elements
            auto sequenceNode = createNode(NodeKind::STATEMENT_LIST);  // Generic sequence node
            for (auto& elementResult : elementResults) {
                if (elementResult.hasCST()) {
                    sequenceNode->addNode(std::unique_ptr<Node>(elementResult.getCST()));
                }
            }
            result.node = std::move(sequenceNode);
        }
        
        return result;
    }
    
    RuleResult CSTParser::parseChoice(const std::vector<std::string>& alternatives, ParseContext& context) {
        size_t startToken = context.currentToken;
        
        for (const auto& alternative : alternatives) {
            // Reset position for each alternative
            context.currentToken = startToken;
            
            auto result = executeRule(alternative, context);
            if (result.success) {
                return result;
            }
        }
        
        // None of the alternatives matched
        RuleResult result;
        result.success = false;
        result.errorMessage = "No alternative matched in choice";
        return result;
    }
    
    RuleResult CSTParser::parseOptional(const std::string& element, ParseContext& context) {
        size_t startToken = context.currentToken;
        
        auto result = executeRule(element, context);
        if (result.success) {
            return result;
        }
        
        // Optional element not present - reset position and return success
        context.currentToken = startToken;
        
        RuleResult optionalResult;
        optionalResult.success = true;
        optionalResult.tokensConsumed = 0;
        return optionalResult;
    }
    
    RuleResult CSTParser::parseZeroOrMore(const std::string& element, ParseContext& context) {
        RuleResult result;
        result.success = true;
        result.tokensConsumed = 0;
        
        std::vector<RuleResult> elementResults;
        
        while (!context.isAtEnd()) {
            size_t startToken = context.currentToken;
            auto elementResult = executeRule(element, context);
            
            if (!elementResult.success) {
                // Reset position and break
                context.currentToken = startToken;
                break;
            }
            
            elementResults.push_back(std::move(elementResult));
            result.tokensConsumed += elementResult.tokensConsumed;
        }
        
        // Create appropriate output based on mode
        if (context.mode == ParserMode::DIRECT_AST) {
            // AST mode - results would be combined by specific rule implementations
            result.success = true;
        } else {
            // CST mode - create a list node
            auto listNode = createNode(NodeKind::STATEMENT_LIST);
            for (auto& elementResult : elementResults) {
                if (elementResult.hasCST()) {
                    listNode->addNode(std::unique_ptr<Node>(elementResult.getCST()));
                }
            }
            result.node = std::move(listNode);
        }
        
        return result;
    }
    
    RuleResult CSTParser::parseOneOrMore(const std::string& element, ParseContext& context) {
        auto firstResult = executeRule(element, context);
        if (!firstResult.success) {
            return firstResult;
        }
        
        auto restResult = parseZeroOrMore(element, context);
        
        RuleResult result;
        result.success = true;
        result.tokensConsumed = firstResult.tokensConsumed + restResult.tokensConsumed;
        
        // Combine first and rest results
        if (context.mode == ParserMode::DIRECT_AST) {
            result.success = true;
        } else {
            auto listNode = createNode(NodeKind::STATEMENT_LIST);
            if (firstResult.hasCST()) {
                listNode->addNode(std::unique_ptr<Node>(firstResult.getCST()));
            }
            if (restResult.hasCST()) {
                // Add children from rest result
                auto restNode = restResult.getCST();
                for (auto& child : restNode->getChildNodes()) {
                    // Note: This is a simplified approach - in practice we'd need proper node transfer
                }
            }
            result.node = std::move(listNode);
        }
        
        return result;
    }
    
    RuleResult CSTParser::parseSeparated(const std::string& element, const std::string& separator, ParseContext& context) {
        auto firstResult = executeRule(element, context);
        if (!firstResult.success) {
            RuleResult result;
            result.success = true;  // Empty list is valid for separated
            result.tokensConsumed = 0;
            return result;
        }
        
        RuleResult result;
        result.success = true;
        result.tokensConsumed = firstResult.tokensConsumed;
        
        std::vector<RuleResult> elementResults;
        elementResults.push_back(std::move(firstResult));
        
        while (!context.isAtEnd()) {
            size_t startToken = context.currentToken;
            
            auto sepResult = executeRule(separator, context);
            if (!sepResult.success) {
                context.currentToken = startToken;
                break;
            }
            
            auto elemResult = executeRule(element, context);
            if (!elemResult.success) {
                context.currentToken = startToken;
                break;
            }
            
            result.tokensConsumed += sepResult.tokensConsumed + elemResult.tokensConsumed;
            elementResults.push_back(std::move(elemResult));
        }
        
        // Create output based on mode
        if (context.mode == ParserMode::DIRECT_AST) {
            result.success = true;
        } else {
            auto listNode = createNode(NodeKind::STATEMENT_LIST);
            for (auto& elementResult : elementResults) {
                if (elementResult.hasCST()) {
                    listNode->addNode(std::unique_ptr<Node>(elementResult.getCST()));
                }
            }
            result.node = std::move(listNode);
        }
        
        return result;
    }
    
    // Core CST parsing methods implementation (Task 5)
    
    std::unique_ptr<Node> CSTParser::parseCST() {
        // Main parsing entry point - creates program-level CST node
        return parseProgram();
    }
    
    std::unique_ptr<Node> CSTParser::parseProgram() {
        // Create program-level CST node with all tokens
        auto programNode = createNode(NodeKind::PROGRAM);
        Token startToken = peek();
        
        // Consume any leading trivia
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
            attachLeadingTrivia(*programNode);
        }
        
        // Parse all statements in the program
        while (!isAtEnd() && shouldContinueParsing()) {
            // Skip any trivia between statements
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
            
            // Check for EOF after consuming trivia
            if (peek().type == TokenType::EOF_TOKEN) {
                break;
            }
            
            // Parse the next statement
            auto stmt = parseStatement();
            if (stmt) {
                programNode->addNode(std::move(stmt));
            } else {
                // If parseStatement returns nullptr, we need to advance to prevent infinite loop
                // This can happen with EOF or unrecoverable errors
                if (!isAtEnd() && peek().type == TokenType::EOF_TOKEN) {
                    break;
                }
                // For other cases, advance to prevent infinite loop
                if (!isAtEnd()) {
                    advance();
                }
            }
            
            // Handle error recovery if needed
            if (!canRecover()) {
                break;
            }
        }
        
        // Consume any trailing trivia
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
            attachTrailingTrivia(*programNode);
        }
        
        // Set the span for the entire program
        if (!tokens.empty()) {
            Token endToken = isAtEnd() ? tokens.back() : peek();
            setNodeSpanFromTokens(*programNode, startToken, endToken);
        }
        
        return programNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseStatement() {
        // Handle all statement types with error recovery
        if (isAtEnd()) {
            return nullptr;
        }
        
        Token startToken = peek();
        
        try {
            // Consume leading trivia for this statement
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
            
            // Determine statement type and parse accordingly
            TokenType currentType = peek().type;
            
            // Handle EOF token explicitly
            if (currentType == TokenType::EOF_TOKEN) {
                return nullptr;
            }
            
            if (isDeclarationStart(currentType)) {
                return parseDeclaration();
            } else if (isStatementStart(currentType)) {
                return parseStatementByType();
            } else if (isExpressionStart(currentType)) {
                // Expression statement
                auto exprStmt = createNode(NodeKind::EXPRESSION_STATEMENT);
                auto expr = parseExpression();
                if (expr) {
                    exprStmt->addNode(std::move(expr));
                }
                
                // Consume optional semicolon
                if (check(TokenType::SEMICOLON)) {
                    exprStmt->addToken(advance());
                }
                
                setNodeSpanFromTokens(*exprStmt, startToken, previous());
                return exprStmt;
            } else {
                // Unknown statement - try error recovery
                std::string errorMsg = "Unexpected token '" + peek().lexeme + "' in statement";
                reportError(errorMsg, TokenType::IDENTIFIER, currentType);
                
                // Skip the problematic token to avoid infinite loops
                Token problematicToken = advance();
                
                // Try to recover by creating a partial statement
                if (recoveryConfig.createPartialNodes) {
                    auto partialNode = createPartialNode(NodeKind::EXPRESSION_STATEMENT, 
                                                       "Incomplete statement starting with '" + problematicToken.lexeme + "'");
                    partialNode->addToken(problematicToken);
                    return partialNode;
                } else {
                    auto errorNode = createErrorRecoveryNode("Invalid statement");
                    errorNode->addToken(problematicToken);
                    return errorNode;
                }
            }
            
        } catch (...) {
            // Error recovery - synchronize and create error node
            reportError("Unexpected error parsing statement");
            
            if (attemptErrorRecovery("statement parsing")) {
                return createErrorRecoveryNode("Statement parsing error");
            } else {
                // Cannot recover - return null to stop parsing
                return nullptr;
            }
        }
    }
    
    std::unique_ptr<Node> CSTParser::parseExpression() {
        // Parse expressions with operator precedence and error tolerance
        if (isAtEnd()) {
            return nullptr;
        }
        
        // Consume any leading trivia
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        Token startToken = peek();
        try {
            // Start with assignment expression (lowest precedence)
            return parseAssignmentExpression();
            
        } catch (...) {
            // Error recovery for expressions
            reportError("Unexpected error parsing expression");
            
            // Try different recovery strategies
            if (recoveryConfig.createPartialNodes) {
                // Try to create a partial expression node
                auto partialExpr = createPartialNode(NodeKind::LITERAL_EXPR, 
                                                   "Incomplete expression");
                
                // Skip tokens until we find expression boundary
                while (!isAtEnd() && !check(TokenType::SEMICOLON) && 
                       !check(TokenType::RIGHT_PAREN) && !check(TokenType::RIGHT_BRACE) && 
                       !check(TokenType::COMMA) && shouldContinueParsing()) {
                    
                    // Stop if we hit another expression or statement start
                    if (isExpressionStart(peek().type) || isStatementStart(peek().type)) {
                        break;
                    }
                    
                    partialExpr->addToken(advance());
                }
                
                return partialExpr;
            } else {
                return createErrorRecoveryNode("Expression parsing error");
            }
        }
    }
    
    std::unique_ptr<Node> CSTParser::parseBlock() {
        // Parse block preserving all tokens including braces and internal whitespace
        if (!check(TokenType::LEFT_BRACE)) {
            reportError("Expected '{' to start block", TokenType::LEFT_BRACE, peek().type);
            return createErrorRecoveryNode("Missing block start");
        }
        
        auto blockNode = createNode(NodeKind::BLOCK_STATEMENT);
        Token startToken = peek();
        
        // Track block context for better error messages
        pushBlockContext("block", startToken);
        
        // Consume opening brace
        blockNode->addToken(advance()); // '{'
        
        // Consume any whitespace/trivia after opening brace
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse statements within the block
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd() && shouldContinueParsing()) {
            // Parse each statement in the block
            auto stmt = parseStatement();
            if (stmt) {
                blockNode->addNode(std::move(stmt));
            }
            
            // Preserve whitespace between statements
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
        }
        
        // Consume closing brace
        if (check(TokenType::RIGHT_BRACE)) {
            blockNode->addToken(advance()); // '}'
            popBlockContext(); // Successfully closed block
        } else {
            // Enhanced error message with block context
            auto blockContext = getCurrentBlockContext();
            if (blockContext.has_value()) {
                std::string enhancedMessage = "Expected '}' to close block\n" + 
                                            generateCausedByMessage(blockContext.value());
                reportErrorWithSuggestions(enhancedMessage, {"Add closing brace '}'"});
            } else {
                reportError("Expected '}' to close block", TokenType::RIGHT_BRACE, peek().type);
            }
            
            if (recoveryConfig.insertMissingTokens) {
                // Create a missing closing brace token
                Token missingBrace;
                missingBrace.type = TokenType::RIGHT_BRACE;
                missingBrace.lexeme = "}";
                missingBrace.line = peek().line;
                missingBrace.start = getCurrentPosition();
                missingBrace.end = getCurrentPosition();
                blockNode->addToken(missingBrace);
            }
            
            popBlockContext(); // Remove from stack even if not properly closed
        }
        
        // Set span from opening to closing brace
        setNodeSpanFromTokens(*blockNode, startToken, previous());
        
        return blockNode;
    }

    // Configuration methods
    void CSTParser::setRecoveryConfig(const RecoveryConfig& config) {
        recoveryConfig = config;
    }

    // Core token consumption methods
    Token CSTParser::consume(TokenType type, const std::string& message) {
        if (check(type)) {
            return advance();
        }
        
        reportError(message, type, peek().type);
        
        // Try error recovery strategies
        if (recoveryConfig.insertMissingTokens && isRecoverableError(type, peek().type)) {
            // Create a missing token placeholder
            Token missingToken;
            missingToken.type = type;
            missingToken.lexeme = tokenTypeToString(type);
            missingToken.line = peek().line;
            missingToken.start = getCurrentPosition();
            missingToken.end = getCurrentPosition();
            return missingToken;
        }
        
        // Return current token as fallback (don't advance)
        Token errorToken = peek();
        return errorToken;
    }

    Token CSTParser::consumeOrError(TokenType type, const std::string& message) {
        if (check(type)) {
            return advance();
        }
        
        // Report the error with enhanced context
        reportError(message, type, peek().type);
        
        if (recoveryConfig.insertMissingTokens && isRecoverableError(type, peek().type)) {
            // Create a missing token placeholder
            Token missingToken;
            missingToken.type = type;
            missingToken.lexeme = "<missing:" + tokenTypeToString(type) + ">";
            missingToken.line = peek().line;
            missingToken.start = getCurrentPosition();
            missingToken.end = getCurrentPosition();
            return missingToken;
        }
        
        // For non-recoverable errors, try to synchronize
        if (!isRecoverableError(type, peek().type)) {
            synchronize();
        }
        
        return peek();  // Return current token as fallback
    }

    bool CSTParser::match(std::initializer_list<TokenType> types) {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool CSTParser::match(TokenType type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }

    bool CSTParser::check(TokenType type) const {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    // Token access methods
    Token CSTParser::advance() {
        if (!isAtEnd()) {
            Token result = tokens[current];
            current++;
            // Skip whitespace tokens during parsing
            while (current < tokens.size() && isTrivia(tokens[current].type)) {
                current++;
            }
            return result;
        }
        return tokens.empty() ? Token{} : tokens.back();
    }

    Token CSTParser::peek() const {
        size_t pos = current;
        // Skip whitespace tokens to find the next meaningful token
        while (pos < tokens.size() && isTrivia(tokens[pos].type)) {
            pos++;
        }
        
        if (pos >= tokens.size()) {
            // Return EOF token
            Token eofToken;
            eofToken.type = TokenType::EOF_TOKEN;
            eofToken.lexeme = "";
            eofToken.line = tokens.empty() ? 1 : tokens.back().line;
            eofToken.start = tokens.empty() ? 0 : tokens.back().end;
            eofToken.end = eofToken.start;
            return eofToken;
        }
        return tokens[pos];
    }

    Token CSTParser::previous() const {
        if (current == 0) {
            Token startToken;
            startToken.type = TokenType::UNDEFINED;
            startToken.lexeme = "";
            startToken.line = 1;
            startToken.start = 0;
            startToken.end = 0;
            return startToken;
        }
        return tokens[current - 1];
    }

    Token CSTParser::peekAhead(size_t offset) const {
        size_t targetIndex = current + offset;
        if (targetIndex >= tokens.size()) {
            return peek();  // Return EOF token
        }
        return tokens[targetIndex];
    }

    // Trivia handling methods
    void CSTParser::consumeTrivia() {
        triviaBuffer.clear();
        
        while (!isAtEnd() && isTrivia(peek().type)) {
            triviaBuffer.push_back(advance());
        }
    }

    std::vector<Token> CSTParser::collectTrivia() {
        std::vector<Token> trivia;
        
        while (!isAtEnd() && isTrivia(peek().type)) {
            trivia.push_back(advance());
        }
        
        return trivia;
    }

    void CSTParser::attachTrivia(Node& node) {
        if (!recoveryConfig.attachTrivia || triviaBuffer.empty()) {
            return;
        }
        
        // Add trivia tokens to the node
        for (const Token& token : triviaBuffer) {
            node.addToken(token);
        }
        
        triviaBuffer.clear();
    }

    void CSTParser::attachLeadingTrivia(Node& node) {
        if (!recoveryConfig.preserveTrivia) {
            return;
        }
        
        // Collect any trivia before the current position
        std::vector<Token> leadingTrivia = collectTrivia();
        
        for (const Token& token : leadingTrivia) {
            node.addToken(token);
        }
    }

    void CSTParser::attachTrailingTrivia(Node& node) {
        if (!recoveryConfig.preserveTrivia) {
            return;
        }
        
        // Look ahead for trivia after current token
        size_t savedCurrent = current;
        std::vector<Token> trailingTrivia = collectTrivia();
        
        for (const Token& token : trailingTrivia) {
            node.addToken(token);
        }
        
        // Don't advance current - trivia will be consumed by next parsing operation
        current = savedCurrent;
    }

    bool CSTParser::isTrivia(TokenType type) const {
        return type == TokenType::WHITESPACE || 
               type == TokenType::NEWLINE || 
               type == TokenType::COMMENT_LINE || 
               type == TokenType::COMMENT_BLOCK;
    }

    // Error recovery methods
    void CSTParser::reportError(const std::string& message) {
        if (errors.size() >= recoveryConfig.maxErrors) {
            // Add a final error indicating we've hit the limit
            if (errors.size() == recoveryConfig.maxErrors) {
                Token currentToken = peek();
                auto [line, column] = getLineColumn(getCurrentPosition());
                ErrorHandling::ErrorMessage limitError("E299", "CST_TooManyErrors", 
                                                     "Too many errors - stopping error reporting", 
                                                     scanner ? scanner->getFilePath() : "", 
                                                     line, column, currentToken.lexeme, 
                                                     InterpretationStage::PARSING);
                errors.push_back(limitError);
            }
            return;
        }
        
        Token currentToken = peek();
        auto [line, column] = getLineColumn(getCurrentPosition());
        
        // Create enhanced error message using ErrorFormatter
        auto options = ErrorHandling::ErrorFormatter::getDefaultOptions();
        
        ErrorHandling::ErrorMessage enhancedError = ErrorHandling::ErrorFormatter::createErrorMessage(
            message, line, column, InterpretationStage::PARSING,
            scanner ? scanner->getSource() : "",
            scanner ? scanner->getFilePath() : "",
            currentToken.lexeme, "", std::nullopt, options
        );
        
        // Use Debugger::error with the enhanced error message
        Debugger::error(enhancedError);
        
        // Store for recovery logic
        errors.push_back(enhancedError);
    }

    void CSTParser::reportError(const std::string& message, TokenType expected, TokenType actual) {
        if (errors.size() >= recoveryConfig.maxErrors) {
            return;
        }
        
        Token currentToken = peek();
        auto [line, column] = getLineColumn(getCurrentPosition());
        
        // Generate expected value string
        std::string expectedValue = tokenTypeToString(expected);
        
        // Create enhanced error message using ErrorFormatter
        auto options = ErrorHandling::ErrorFormatter::getDefaultOptions();
        
        ErrorHandling::ErrorMessage enhancedError = ErrorHandling::ErrorFormatter::createErrorMessage(
            message, line, column, InterpretationStage::PARSING,
            scanner ? scanner->getSource() : "",
            scanner ? scanner->getFilePath() : "",
            currentToken.lexeme, expectedValue, std::nullopt, options
        );
        
        // Add CST-specific suggestions
        auto suggestions = generateSuggestions(expected, actual);
        if (!suggestions.empty() && enhancedError.suggestion.empty()) {
            enhancedError.suggestion = suggestions[0];
        }
        
        // Use Debugger::error with the enhanced error message
        Debugger::error(enhancedError);
        
        // Store for recovery logic
        errors.push_back(enhancedError);
    }

    void CSTParser::reportErrorWithSuggestions(const std::string& message, 
                                              const std::vector<std::string>& suggestions) {
        if (errors.size() >= recoveryConfig.maxErrors) {
            return;
        }
        
        Token currentToken = peek();
        auto [line, column] = getLineColumn(getCurrentPosition());
        
        // Create enhanced message with suggestions
        std::string enhancedMessage = message;
        if (!suggestions.empty()) {
            enhancedMessage += "\nSuggestions:";
            for (const auto& suggestion : suggestions) {
                enhancedMessage += "\n  - " + suggestion;
            }
        }
        
        // Use Debugger::error for consistent error reporting
        if (scanner) {
            Debugger::error(enhancedMessage, line, column, InterpretationStage::PARSING, 
                          scanner->getSource(), scanner->getFilePath(), 
                          currentToken.lexeme, "");
        } else {
            // Fallback when no scanner available
            Debugger::error(enhancedMessage, line, column, InterpretationStage::PARSING, 
                          "", "", currentToken.lexeme, "");
        }
        
        // Still maintain internal error list for recovery logic
        ErrorHandling::ErrorMessage error("E202", "CST_SuggestionError", message, 
                                         scanner ? scanner->getFilePath() : "", 
                                         line, column, currentToken.lexeme, 
                                         InterpretationStage::PARSING);
        
        // Add suggestions to the error
        if (!suggestions.empty()) {
            error.suggestion = suggestions[0]; // Use first suggestion as primary
            // Could also join all suggestions if needed
        }
        
        errors.push_back(error);
    }

    void CSTParser::synchronize() {
        if (!recoveryConfig.continueOnError) {
            return;
        }
        
        // Don't skip the current token automatically - let the caller decide
        // This prevents double-skipping of tokens
        
        // Skip tokens until we find a synchronization point
        while (!isAtEnd() && shouldContinueParsing()) {
            // Check if current token is a synchronization point
            if (isSyncToken(peek().type)) {
                return;  // Found synchronization point
            }
            
            // Skip trivia tokens during synchronization
            if (isTrivia(peek().type)) {
                advance();
                continue;
            }
            
            // Skip error tokens
            if (peek().type == TokenType::ERROR) {
                advance();
                continue;
            }
            
            // Check if previous token was a statement terminator
            if (current > 0 && previous().type == TokenType::SEMICOLON) {
                return;  // Found statement boundary
            }
            
            advance();
        }
    }

    std::unique_ptr<Node> CSTParser::createErrorRecoveryNode() {
        return createErrorRecoveryNode("Syntax error");
    }

    std::unique_ptr<Node> CSTParser::createErrorRecoveryNode(const std::string& message) {
        size_t startPos = getCurrentPosition();
        auto errorNode = CST::createErrorNode(message, startPos, startPos);
        
        // Collect skipped tokens during error recovery
        std::vector<Token> skippedTokens;
        size_t tokensSkipped = 0;
        const size_t maxSkipTokens = 50; // Prevent infinite loops
        
        while (!isAtEnd() && !isSyncToken(peek().type) && 
               tokensSkipped < maxSkipTokens && shouldContinueParsing()) {
            
            Token skippedToken = advance();
            skippedTokens.push_back(skippedToken);
            errorNode->addSkippedToken(skippedToken);
            tokensSkipped++;
            
            // Stop skipping if we encounter meaningful structure
            if (isStatementStart(skippedToken.type) || 
                isDeclarationStart(skippedToken.type) ||
                skippedToken.type == TokenType::RIGHT_BRACE ||
                skippedToken.type == TokenType::SEMICOLON) {
                // Back up one token so the next parser can handle it
                if (current > 0) {
                    current--;
                    skippedTokens.pop_back();
                    if (!errorNode->skippedTokens.empty()) {
                        errorNode->skippedTokens.pop_back();
                    }
                }
                break;
            }
        }
        
        // Update error node span to cover all skipped tokens
        if (!skippedTokens.empty()) {
            errorNode->setSourceSpan(startPos, skippedTokens.back().end);
        }
        
        return errorNode;
    }

    // Error context and suggestions
    std::string CSTParser::getSourceContext(size_t position, size_t contextLines) const {
        std::ostringstream context;
        
        // Show current token and surrounding tokens for context
        context << "Near: ";
        
        // Show previous token if available
        if (current > 0) {
            context << "'" << previous().lexeme << "' ";
        }
        
        // Show current token
        if (!isAtEnd()) {
            context << ">>> '" << peek().lexeme << "' <<<";
        } else {
            context << ">>> END OF FILE <<<";
        }
        
        // Show next token if available
        if (current + 1 < tokens.size()) {
            context << " '" << peekAhead(1).lexeme << "'";
        }
        
        return context.str();
    }

    std::vector<std::string> CSTParser::generateSuggestions(TokenType expected, TokenType actual) const {
        std::vector<std::string> suggestions;
        
        // Generate context-specific suggestions based on expected vs actual tokens
        if (expected == TokenType::SEMICOLON) {
            suggestions.push_back("Add a semicolon ';' to end the statement");
            if (actual == TokenType::NEWLINE) {
                suggestions.push_back("Semicolon may be optional in some contexts");
            }
        } else if (expected == TokenType::RIGHT_BRACE) {
            suggestions.push_back("Add a closing brace '}' to close the block");
            suggestions.push_back("Check for matching opening brace '{'");
        } else if (expected == TokenType::RIGHT_PAREN) {
            suggestions.push_back("Add a closing parenthesis ')' to close the expression");
            suggestions.push_back("Check for matching opening parenthesis '('");
        } else if (expected == TokenType::LEFT_BRACE) {
            suggestions.push_back("Add an opening brace '{' to start the block");
        } else if (expected == TokenType::IDENTIFIER) {
            suggestions.push_back("Provide a valid identifier name");
            if (actual == TokenType::NUMBER) {
                suggestions.push_back("Identifiers cannot start with numbers");
            } else if (actual == TokenType::STRING) {
                suggestions.push_back("Remove quotes if this should be an identifier");
            }
        } else if (expected == TokenType::EQUAL) {
            suggestions.push_back("Add '=' for assignment");
        } else if (expected == TokenType::COLON) {
            suggestions.push_back("Add ':' for type annotation");
        }
        
        // General suggestions based on actual token
        if (actual == TokenType::EOF_TOKEN) {
            suggestions.push_back("Unexpected end of file - check for missing closing brackets or braces");
        } else if (actual == TokenType::ERROR) {
            suggestions.push_back("Fix the invalid token or character");
        }
        
        // Context-specific suggestions
        if (isStatementStart(actual)) {
            suggestions.push_back("This looks like the start of a new statement - check previous statement completion");
        }
        
        return suggestions;
    }

    void CSTParser::addErrorContext(ParseError& error, const Node* node) const {
        if (node) {
            // Since ErrorMessage doesn't have relatedNode, we can add context to hint
            if (error.hint.empty()) {
                error.hint = "Related to " + node->getKindName() + " node";
            } else {
                error.hint += " (Related to " + node->getKindName() + " node)";
            }
        }
    }

    // Synchronization helpers
    bool CSTParser::isSyncToken(TokenType type) const {
        return std::find(recoveryConfig.syncTokens.begin(), 
                        recoveryConfig.syncTokens.end(), 
                        type) != recoveryConfig.syncTokens.end();
    }

    void CSTParser::skipToSyncPoint() {
        while (!isAtEnd() && !isSyncToken(peek().type) && shouldContinueParsing()) {
            advance();
        }
    }

    void CSTParser::skipInvalidTokens() {
        size_t tokensSkipped = 0;
        const size_t maxSkipTokens = 20; // Prevent infinite loops
        
        while (!isAtEnd() && tokensSkipped < maxSkipTokens && shouldContinueParsing()) {
            TokenType currentType = peek().type;
            
            // Skip error tokens
            if (currentType == TokenType::ERROR) {
                advance();
                tokensSkipped++;
                continue;
            }
            
            // Skip tokens that don't make sense in current context
            if (recoveryConfig.skipInvalidTokens) {
                // This would need context-specific logic
                // For now, just break if we find a meaningful token
                if (isMeaningfulToken(currentType)) {
                    break;
                }
            }
            
            break; // Don't skip valid tokens
        }
    }

    // Node creation helpers
    std::unique_ptr<Node> CSTParser::createNode(NodeKind kind) {
        return CST::createNode(kind, getCurrentPosition(), getCurrentPosition());
    }

    std::unique_ptr<Node> CSTParser::createNodeWithSpan(NodeKind kind, size_t start, size_t end) {
        return CST::createNode(kind, start, end);
    }

    void CSTParser::setNodeSpan(Node& node, size_t start, size_t end) {
        node.setSourceSpan(start, end);
    }

    void CSTParser::setNodeSpanFromTokens(Node& node, const Token& startToken, const Token& endToken) {
        node.setSourceSpan(startToken.start, endToken.end);
    }

    // Utility methods for error recovery
    bool CSTParser::canRecover() const {
        return errors.size() < recoveryConfig.maxErrors && recoveryConfig.continueOnError;
    }

    bool CSTParser::shouldContinueParsing() const {
        return !isAtEnd() && canRecover();
    }

    void CSTParser::incrementErrorCount() {
        // Error count is tracked by the size of the errors vector
        // This method is here for potential future use
    }

    // Token classification helpers
    bool CSTParser::isMeaningfulToken(TokenType type) const {
        return !isTrivia(type) && type != TokenType::ERROR && type != TokenType::MISSING && type != TokenType::EOF_TOKEN;
    }

    bool CSTParser::isStatementStart(TokenType type) const {
        return type == TokenType::VAR || type == TokenType::FN || type == TokenType::CLASS ||
               type == TokenType::IF || type == TokenType::FOR || type == TokenType::WHILE ||
               type == TokenType::RETURN || type == TokenType::BREAK || type == TokenType::CONTINUE ||
               type == TokenType::PRINT || type == TokenType::LEFT_BRACE;
    }

    bool CSTParser::isExpressionStart(TokenType type) const {
        return type == TokenType::IDENTIFIER || type == TokenType::NUMBER || type == TokenType::STRING ||
               type == TokenType::TRUE || type == TokenType::FALSE || type == TokenType::NIL ||
               type == TokenType::LEFT_PAREN || type == TokenType::MINUS || type == TokenType::BANG;
    }

    bool CSTParser::isDeclarationStart(TokenType type) const {
        return type == TokenType::VAR || type == TokenType::FN || type == TokenType::CLASS ||
               type == TokenType::TYPE || type == TokenType::TRAIT || type == TokenType::INTERFACE;
    }

    // Source position helpers
    size_t CSTParser::getCurrentPosition() const {
        if (isAtEnd()) {
            return tokens.empty() ? 0 : tokens.back().end;
        }
        return tokens[current].start;
    }

    size_t CSTParser::getTokenPosition(const Token& token) const {
        return token.start;
    }

    std::pair<size_t, size_t> CSTParser::getLineColumn(size_t position) const {
        Token currentToken = peek();
        
        // If we have a scanner, we can get more accurate position info
        if (scanner) {
            // Use the token's line number and try to calculate column from position
            size_t line = currentToken.line;
            size_t column = 1;
            
            // Try to calculate column based on token start position
            if (currentToken.start > 0) {
                // This is a simplified calculation - ideally we'd scan back to line start
                column = (currentToken.start % 80) + 1; // Rough estimate
            }
            
            return {line, column};
        }
        
        // Fallback to token line with column 1
        return {currentToken.line, 1};
    }

    // Debug and diagnostic helpers
    std::string CSTParser::getCurrentTokenInfo() const {
        Token token = peek();
        std::ostringstream info;
        info << "Token: " << static_cast<int>(token.type) << " ('" << token.lexeme << "') at line " << token.line;
        return info.str();
    }

    std::string CSTParser::getParsingContext() const {
        std::ostringstream context;
        context << "Parsing at position " << current << "/" << tokens.size();
        if (!isAtEnd()) {
            context << ", current token: " << getCurrentTokenInfo();
        }
        return context.str();
    }

    void CSTParser::logParsingState(const std::string& context) const {
        // For debugging - could output to stderr or a log file
        // std::cerr << "[CSTParser] " << context << " - " << getParsingContext() << std::endl;
    }

    // Additional error recovery helper methods
    
    std::unique_ptr<Node> CSTParser::createPartialNode(NodeKind targetKind, const std::string& description) {
        size_t startPos = getCurrentPosition();
        auto incompleteNode = CST::createIncompleteNode(targetKind, description, startPos, startPos);
        
        // Don't automatically consume tokens here - let the caller handle token consumption
        // This prevents infinite loops when the caller has already advanced past a problematic token
        
        return incompleteNode;
    }
    
    bool CSTParser::attemptErrorRecovery(const std::string& context) {
        if (!canRecover()) {
            return false;
        }
        
        // Log the recovery attempt
        reportError("Attempting error recovery in " + context);
        
        // Try different recovery strategies
        
        // Strategy 1: Skip to next statement
        if (isSyncToken(peek().type)) {
            return true; // Already at sync point
        }
        
        // Strategy 2: Look for missing punctuation
        if (recoveryConfig.insertMissingTokens) {
            // This would need context-specific logic
            // For now, just synchronize
            synchronize();
            return !isAtEnd();
        }
        
        // Strategy 3: Skip invalid tokens
        if (recoveryConfig.skipInvalidTokens) {
            skipInvalidTokens();
            return !isAtEnd();
        }
        
        // Default: synchronize
        synchronize();
        return !isAtEnd();
    }
    
    void CSTParser::reportDetailedError(const std::string& message, 
                                       const std::string& context,
                                       const std::vector<std::string>& suggestions) {
        if (errors.size() >= recoveryConfig.maxErrors) {
            return;
        }
        
        Token currentToken = peek();
        auto [line, column] = getLineColumn(getCurrentPosition());
        
        // Create enhanced message with context and suggestions
        std::string enhancedMessage = message;
        if (!context.empty()) {
            enhancedMessage += "\nContext: " + context;
        }
        if (!suggestions.empty()) {
            enhancedMessage += "\nSuggestions:";
            for (const auto& suggestion : suggestions) {
                enhancedMessage += "\n  - " + suggestion;
            }
        }
        
        // Use Debugger::error for consistent error reporting
        if (scanner) {
            Debugger::error(enhancedMessage, line, column, InterpretationStage::PARSING, 
                          scanner->getSource(), scanner->getFilePath(), 
                          currentToken.lexeme, "");
        } else {
            // Fallback when no scanner available
            Debugger::error(enhancedMessage, line, column, InterpretationStage::PARSING, 
                          "", "", currentToken.lexeme, "");
        }
        
        // Still maintain internal error list for recovery logic
        ErrorHandling::ErrorMessage error("E203", "CST_DetailedError", message, 
                                         scanner ? scanner->getFilePath() : "", 
                                         line, column, currentToken.lexeme, 
                                         InterpretationStage::PARSING);
        
        // Add context and suggestions
        if (!context.empty()) {
            error.hint = context;
        }
        if (!suggestions.empty()) {
            error.suggestion = suggestions[0]; // Use first suggestion as primary
        }
        
        errors.push_back(error);
    }
    
    void CSTParser::reportErrorAtToken(const std::string& message, const Token& errorToken, 
                                      TokenType expected, TokenType actual) {
        if (errors.size() >= recoveryConfig.maxErrors) {
            return;
        }
        
        // Use the specific token's position information
        size_t line = errorToken.line;
        size_t column = errorToken.start + 1; // Use token's actual start position
        
        // Generate expected value string if provided
        std::string expectedValue = (expected != TokenType::UNDEFINED) ? tokenTypeToString(expected) : "";
        TokenType actualType = (actual != TokenType::UNDEFINED) ? actual : peek().type;
        
        // Create enhanced error message using ErrorFormatter
        auto options = ErrorHandling::ErrorFormatter::getDefaultOptions();
        
        ErrorHandling::ErrorMessage enhancedError = ErrorHandling::ErrorFormatter::createErrorMessage(
            message, line, column, InterpretationStage::PARSING,
            scanner ? scanner->getSource() : "",
            scanner ? scanner->getFilePath() : "",
            errorToken.lexeme, expectedValue, std::nullopt, options
        );
        
        // Use Debugger::error with the enhanced error message
        Debugger::error(enhancedError);
        
        // Store for recovery logic
        errors.push_back(enhancedError);
    }
    
    bool CSTParser::isRecoverableError(TokenType expected, TokenType actual) const {
        // Some errors are more recoverable than others
        
        // Missing punctuation is usually recoverable
        if (expected == TokenType::SEMICOLON || 
            expected == TokenType::RIGHT_PAREN || 
            expected == TokenType::RIGHT_BRACE) {
            return true;
        }
        
        // Identifier mismatches might be recoverable
        if (expected == TokenType::IDENTIFIER && actual != TokenType::EOF_TOKEN) {
            return true;
        }
        
        // EOF is usually not recoverable
        if (actual == TokenType::EOF_TOKEN) {
            return false;
        }
        
        return recoveryConfig.continueOnError;
    }
    
    std::unique_ptr<Node> CSTParser::handleMissingToken(TokenType expectedType, const std::string& context) {
        if (!recoveryConfig.insertMissingTokens) {
            return nullptr;
        }
        
        // Create a missing node for the expected token
        std::string description = "Missing " + tokenTypeToString(expectedType);
        if (!context.empty()) {
            description += " in " + context;
        }
        
        auto missingNode = CST::createMissingNode(NodeKind::MISSING_NODE, description, 
                                                 getCurrentPosition(), getCurrentPosition());
        
        // Report the error
        reportError("Expected " + tokenTypeToString(expectedType), expectedType, peek().type);
        
        return missingNode;
    }
    
    std::string CSTParser::tokenTypeToString(TokenType type) const {
        // This would ideally be in a shared utility, but for now implement here
        switch (type) {
            case TokenType::SEMICOLON: return "';'";
            case TokenType::LEFT_BRACE: return "'{'";
            case TokenType::RIGHT_BRACE: return "'}'";
            case TokenType::LEFT_PAREN: return "'('";
            case TokenType::RIGHT_PAREN: return "')'";
            case TokenType::IDENTIFIER: return "identifier";
            case TokenType::NUMBER: return "number";
            case TokenType::STRING: return "string";
            case TokenType::IF: return "'if'";
            case TokenType::FN: return "'fn'";
            case TokenType::VAR: return "'var'";
            case TokenType::CLASS: return "'class'";
            case TokenType::EOF_TOKEN: return "end of file";
            default: return "token";
        }
    }
    
    // Block context tracking methods implementation
    
    void CSTParser::pushBlockContext(const std::string& blockType, const Token& startToken) {
        auto [line, column] = getLineColumn(startToken.start);
        ErrorHandling::BlockContext context(blockType, line, column, startToken.lexeme);
        blockStack.push_back(context);
    }
    
    void CSTParser::popBlockContext() {
        if (!blockStack.empty()) {
            blockStack.pop_back();
        }
    }
    
    std::optional<ErrorHandling::BlockContext> CSTParser::getCurrentBlockContext() const {
        if (blockStack.empty()) {
            return std::nullopt;
        }
        return blockStack.back();
    }
    
    std::string CSTParser::generateCausedByMessage(const ErrorHandling::BlockContext& context) const {
        std::ostringstream message;
        message << "Caused by: Unclosed " << context.blockType 
                << " starting at line " << context.startLine 
                << " ('" << context.startLexeme << "')";
        return message.str();
    }

    // Utility functions for working with CSTParser

    std::unique_ptr<Node> parseSourceToCST(const std::string& source, 
                                          const CSTConfig& scanConfig,
                                          const RecoveryConfig& parseConfig) {
        Scanner scanner(source);
        CSTParser parser(scanner, scanConfig);
        parser.setRecoveryConfig(parseConfig);
        return parser.parse();
    }

    std::unique_ptr<Node> parseTokensToCST(const std::vector<Token>& tokens,
                                          const RecoveryConfig& config) {
        CSTParser parser(tokens);
        parser.setRecoveryConfig(config);
        return parser.parse();
    }

    bool isParsingSuccessful(const std::vector<ParseError>& errors) {
        // Check if there are any errors (all ErrorMessage objects represent errors)
        return errors.empty();
    }

    std::string formatErrors(const std::vector<ParseError>& errors) {
        std::ostringstream formatted;
        
        for (const auto& error : errors) {
            formatted << error.errorCode << " " << error.errorType 
                     << " at line " << error.line << ", column " << error.column 
                     << ": " << error.description << std::endl;
            
            if (!error.hint.empty()) {
                formatted << "  Hint: " << error.hint << std::endl;
            }
            
            if (!error.suggestion.empty()) {
                formatted << "  Suggestion: " << error.suggestion << std::endl;
            }
            
            if (!error.causedBy.empty()) {
                formatted << "  Caused by: " << error.causedBy << std::endl;
            }
            
            formatted << std::endl;
        }
        
        return formatted.str();
    }

    std::vector<ParseError> filterErrorsByType(const std::vector<ParseError>& errors,
                                              const std::string& errorType) {
        std::vector<ParseError> filtered;
        
        for (const auto& error : errors) {
            if (error.errorType == errorType) {
                filtered.push_back(error);
            }
        }
        
        return filtered;
    }

    // Helper methods for statement parsing
    
    std::unique_ptr<Node> CSTParser::parseDeclaration() {
        TokenType type = peek().type;
        Token startToken = peek();
        
        switch (type) {
            case TokenType::VAR:
                return parseVariableDeclaration();
            case TokenType::FN:
                return parseFunctionDeclaration();
            case TokenType::CLASS:
                return parseClassDeclaration();
            case TokenType::TYPE:
                return parseTypeDeclaration();
            case TokenType::TRAIT:
                return parseTraitDeclaration();
            case TokenType::INTERFACE:
                return parseInterfaceDeclaration();
            default:
                reportError("Unknown declaration type");
                return createErrorRecoveryNode("Invalid declaration");
        }
    }
    
    std::unique_ptr<Node> CSTParser::parseStatementByType() {
        TokenType type = peek().type;
        Token startToken = peek();
        
        switch (type) {
            case TokenType::IF:
                return parseIfStatement();
            case TokenType::FOR:
                return parseForStatement();
            case TokenType::WHILE:
                return parseWhileStatement();
            case TokenType::ITER:
                return parseIterStatement();
            case TokenType::MATCH:
                return parseMatchStatement();
            case TokenType::RETURN:
                return parseReturnStatement();
            case TokenType::BREAK:
                return parseBreakStatement();
            case TokenType::CONTINUE:
                return parseContinueStatement();
            case TokenType::PRINT:
                return parsePrintStatement();
            case TokenType::LEFT_BRACE:
                return parseBlock();
            default:
                reportError("Unknown statement type");
                return createErrorRecoveryNode("Invalid statement");
        }
    }
    
    std::unique_ptr<Node> CSTParser::parseAssignmentExpression() {
        auto expr = parseLogicalOrExpression();
        
        if (match(TokenType::EQUAL)) {
            Token operatorToken = previous();
            auto assignNode = createNode(NodeKind::ASSIGNMENT_EXPR);
            assignNode->addNode(std::move(expr));
            assignNode->addToken(operatorToken);
            
            auto value = parseAssignmentExpression();
            if (value) {
                assignNode->addNode(std::move(value));
            }
            
            return assignNode;
        }
        
        return expr;
    }
    
    std::unique_ptr<Node> CSTParser::parseLogicalOrExpression() {
        auto expr = parseLogicalAndExpression();
        
        while (match(TokenType::OR)) {
            Token operatorToken = previous();
            auto logicalNode = createNode(NodeKind::LOGICAL_EXPR);
            logicalNode->addNode(std::move(expr));
            logicalNode->addToken(operatorToken);
            
            auto right = parseLogicalAndExpression();
            if (right) {
                logicalNode->addNode(std::move(right));
            }
            
            expr = std::move(logicalNode);
        }
        
        return expr;
    }
    
    std::unique_ptr<Node> CSTParser::parseLogicalAndExpression() {
        auto expr = parseEqualityExpression();
        
        while (match(TokenType::AND)) {
            Token operatorToken = previous();
            auto logicalNode = createNode(NodeKind::LOGICAL_EXPR);
            logicalNode->addNode(std::move(expr));
            logicalNode->addToken(operatorToken);
            
            auto right = parseEqualityExpression();
            if (right) {
                logicalNode->addNode(std::move(right));
            }
            
            expr = std::move(logicalNode);
        }
        
        return expr;
    }
    
    std::unique_ptr<Node> CSTParser::parseEqualityExpression() {
        return parseBinaryExpr(&CSTParser::parseComparisonExpression, 
            {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL});
    }
    
    std::unique_ptr<Node> CSTParser::parseComparisonExpression() {
        return parseBinaryExpr(&CSTParser::parseTermExpression, 
            {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL});
    }
    
    std::unique_ptr<Node> CSTParser::parseTermExpression() {
        return parseBinaryExpr(&CSTParser::parseFactorExpression, 
            {TokenType::MINUS, TokenType::PLUS});
    }
    
    std::unique_ptr<Node> CSTParser::parseFactorExpression() {
        return parseBinaryExpr(&CSTParser::parseUnaryExpression, 
            {TokenType::SLASH, TokenType::STAR, TokenType::MODULUS});
    }
    
    std::unique_ptr<Node> CSTParser::parseUnaryExpression() {
        if (match({TokenType::BANG, TokenType::MINUS})) {
            Token operatorToken = previous();
            auto unaryNode = createNode(NodeKind::UNARY_EXPR);
            unaryNode->addToken(operatorToken);
            
            // Enhanced error recovery for missing operands after unary operators
            auto expr = parseUnaryExpression();
            if (expr) {
                unaryNode->addNode(std::move(expr));
            } else {
                // Create specific error recovery for missing operand
                reportErrorWithSuggestions("Expected expression after unary operator '" + operatorToken.lexeme + "'",
                    {"Add an expression after the unary operator", 
                     "Use parentheses to group complex expressions",
                     "Check for missing operand"});
                
                // Create missing node for the expected operand
                auto missingOperand = CST::createMissingNode(NodeKind::UNARY_EXPR, 
                    "Missing operand after unary operator '" + operatorToken.lexeme + "'");
                unaryNode->addNode(std::move(missingOperand));
            }
            
            return unaryNode;
        }
        
        return parseCallExpression();
    }
    
    std::unique_ptr<Node> CSTParser::parseCallExpression() {
        auto expr = parsePrimaryExpression();
        
        while (true) {
            if (match(TokenType::LEFT_PAREN)) {
                // Function call with enhanced error recovery
                Token openParen = previous();
                auto callNode = createNode(NodeKind::CALL_EXPR);
                callNode->addNode(std::move(expr));
                callNode->addToken(openParen);
                
                // Parse arguments with recovery for missing arguments and commas
                if (!check(TokenType::RIGHT_PAREN)) {
                    do {
                        auto arg = parseExpression();
                        if (arg) {
                            callNode->addNode(std::move(arg));
                        } else {
                            // Recovery for missing argument
                            reportErrorWithSuggestions("Expected argument in function call",
                                {"Add a valid expression as argument",
                                 "Remove extra comma if no argument intended",
                                 "Check for missing closing parenthesis"});
                            
                            auto missingArg = CST::createMissingNode(NodeKind::ARGUMENT, "Missing function argument");
                            callNode->addNode(std::move(missingArg));
                        }
                        
                        // Handle comma recovery
                        if (match(TokenType::COMMA)) {
                            callNode->addToken(previous());
                            
                            // Check for trailing comma before closing paren
                            if (check(TokenType::RIGHT_PAREN)) {
                                reportErrorWithSuggestions("Unexpected trailing comma in function call",
                                    {"Remove the trailing comma",
                                     "Add another argument after the comma"});
                                break;
                            }
                        } else {
                            break;
                        }
                    } while (true);
                }
                
                // Recovery for missing closing parenthesis
                if (check(TokenType::RIGHT_PAREN)) {
                    callNode->addToken(advance());
                } else {
                    reportErrorWithSuggestions("Expected ')' after function arguments", 
                        {"Add closing parenthesis ')' to complete function call",
                         "Check for missing or extra arguments",
                         "Verify proper comma separation between arguments"});
                    
                    if (recoveryConfig.insertMissingTokens) {
                        // Insert missing closing parenthesis
                        Token missingParen;
                        missingParen.type = TokenType::RIGHT_PAREN;
                        missingParen.lexeme = ")";
                        missingParen.line = peek().line;
                        missingParen.start = getCurrentPosition();
                        missingParen.end = getCurrentPosition();
                        callNode->addToken(missingParen);
                    }
                }
                
                expr = std::move(callNode);
            } else if (match(TokenType::DOT)) {
                // Member access with enhanced error recovery
                Token dot = previous();
                auto memberNode = createNode(NodeKind::MEMBER_EXPR);
                memberNode->addNode(std::move(expr));
                memberNode->addToken(dot);
                
                // Recovery for missing member names after dots
                if (check(TokenType::IDENTIFIER)) {
                    memberNode->addToken(advance());
                } else {
                    reportErrorWithSuggestions("Expected property name after '.'", 
                        {"Add a valid identifier after the dot",
                         "Remove the dot if member access not intended",
                         "Check for typos in property name"});
                    
                    if (recoveryConfig.insertMissingTokens) {
                        // Create missing identifier token
                        Token missingId;
                        missingId.type = TokenType::IDENTIFIER;
                        missingId.lexeme = "<missing_property>";
                        missingId.line = peek().line;
                        missingId.start = getCurrentPosition();
                        missingId.end = getCurrentPosition();
                        memberNode->addToken(missingId);
                    } else {
                        // Create missing node for the property
                        auto missingProperty = CST::createMissingNode(NodeKind::IDENTIFIER, 
                            "Missing property name after '.'");
                        memberNode->addNode(std::move(missingProperty));
                    }
                }
                
                expr = std::move(memberNode);
            } else if (match(TokenType::LEFT_BRACKET)) {
                // Index access
                Token openBracket = previous();
                auto indexNode = createNode(NodeKind::INDEX_EXPR);
                indexNode->addNode(std::move(expr));
                indexNode->addToken(openBracket);
                
                auto index = parseExpression();
                if (index) {
                    indexNode->addNode(std::move(index));
                } else {
                    // Recovery for missing index expression
                    reportErrorWithSuggestions("Expected index expression after '['",
                        {"Add a valid expression for array/object indexing",
                         "Use a number for array indexing",
                         "Use a string for object property access"});
                    
                    auto missingIndex = CST::createMissingNode(NodeKind::INDEX_EXPR, "Missing index expression");
                    indexNode->addNode(std::move(missingIndex));
                }
                
                if (check(TokenType::RIGHT_BRACKET)) {
                    indexNode->addToken(advance());
                } else {
                    reportErrorWithSuggestions("Expected ']' after index expression", 
                        {"Add closing bracket ']' to complete index access",
                         "Check for missing or invalid index expression"});
                    
                    if (recoveryConfig.insertMissingTokens) {
                        // Insert missing closing bracket
                        Token missingBracket;
                        missingBracket.type = TokenType::RIGHT_BRACKET;
                        missingBracket.lexeme = "]";
                        missingBracket.line = peek().line;
                        missingBracket.start = getCurrentPosition();
                        missingBracket.end = getCurrentPosition();
                        indexNode->addToken(missingBracket);
                    }
                }
                
                expr = std::move(indexNode);
            } else {
                break;
            }
        }
        
        return expr;
    }
    
    std::unique_ptr<Node> CSTParser::parsePrimaryExpression() {
        // Handle literals
        if (check(TokenType::TRUE) || check(TokenType::FALSE) || check(TokenType::NIL) ||
            check(TokenType::NUMBER) || check(TokenType::STRING)) {
            // Check if this is the start of an interpolated string
            if (check(TokenType::STRING) && peekAhead(1).type == TokenType::INTERPOLATION_START) {
                // Consume the STRING token first
                advance();
                return parseInterpolatedString();
            }
            return parseLiteralExpr();
        }
        
        // Handle variables
        if (check(TokenType::IDENTIFIER)) {
            return parseVariableExpr();
        }
        
        // Handle parenthesized expressions
        if (match(TokenType::LEFT_PAREN)) {
            auto expr = parseExpression();
            if (!match(TokenType::RIGHT_PAREN)) {
                reportError("Expected ')' after expression");
            }
            return expr;
        }
        
        // If we get here, we have an unexpected token
        reportError("Unexpected token in expression");
        return nullptr;
    }
    
    // Enhanced parseLiteralExpr with error node creation for invalid tokens
    std::unique_ptr<Node> CSTParser::parseLiteralExpr() {
        if (match(TokenType::TRUE) || match(TokenType::FALSE) || match(TokenType::NIL)) {
            auto literalNode = createNode(NodeKind::LITERAL_EXPR);
            literalNode->addToken(previous());
            return literalNode;
        }
        
        if (match(TokenType::NUMBER) || match(TokenType::STRING)) {
            auto literalNode = createNode(NodeKind::LITERAL_EXPR);
            Token literalToken = previous();
            
            // Note: String validation is handled by the scanner
            
            if (literalToken.type == TokenType::NUMBER && literalToken.lexeme.empty()) {
                // Invalid number literal
                reportErrorWithSuggestions("Invalid number literal",
                    {"Provide a valid numeric value",
                     "Check for proper decimal notation",
                     "Ensure no invalid characters in number"});
                
                auto errorNode = CST::createErrorNode("Invalid number literal", 
                    literalToken.start, literalToken.end);
                errorNode->addToken(literalToken);
                return errorNode;
            }
            
            literalNode->addToken(literalToken);
            return literalNode;
        }
        
        // If we get here, this is not a literal
        return nullptr;
    }
    
    // Enhanced parseVariableExpr with error node creation for invalid tokens
    std::unique_ptr<Node> CSTParser::parseVariableExpr() {
        if (match(TokenType::IDENTIFIER)) {
            Token identifierToken = previous();
            auto varNode = createNode(NodeKind::VARIABLE_EXPR);
            
            // Validate identifier token
            if (identifierToken.lexeme.empty()) {
                reportErrorWithSuggestions("Empty identifier",
                    {"Provide a valid variable name",
                     "Check for typos in identifier",
                     "Ensure identifier follows naming rules"});
                
                auto errorNode = CST::createErrorNode("Invalid identifier", 
                    identifierToken.start, identifierToken.end);
                errorNode->addToken(identifierToken);
                return errorNode;
            }
            
            // Check for reserved keywords used as identifiers
            if (isReservedKeyword(identifierToken.lexeme)) {
                reportErrorWithSuggestions("Cannot use reserved keyword '" + identifierToken.lexeme + "' as identifier",
                    {"Choose a different variable name",
                     "Add prefix or suffix to make it unique",
                     "Check language reserved words list"});
                
                auto errorNode = CST::createErrorNode("Reserved keyword used as identifier", 
                    identifierToken.start, identifierToken.end);
                errorNode->addToken(identifierToken);
                return errorNode;
            }
            
            varNode->addToken(identifierToken);
            return varNode;
        }
        
        return parseGroupingExpr();
    }
    
    // Enhanced parseGroupingExpr with recovery for missing closing parentheses
    std::unique_ptr<Node> CSTParser::parseGroupingExpr() {
        if (match(TokenType::LEFT_PAREN)) {
            Token openParen = previous();
            auto groupingNode = createNode(NodeKind::GROUPING_EXPR);
            groupingNode->addToken(openParen);
            
            auto expr = parseExpression();
            if (expr) {
                groupingNode->addNode(std::move(expr));
            } else {
                // Recovery for missing expression inside parentheses
                reportErrorWithSuggestions("Expected expression inside parentheses",
                    {"Add a valid expression between the parentheses",
                     "Remove empty parentheses if not needed",
                     "Check for syntax errors in the expression"});
                
                auto missingExpr = CST::createMissingNode(NodeKind::GROUPING_EXPR, 
                    "Missing expression inside parentheses");
                groupingNode->addNode(std::move(missingExpr));
            }
            
            // Enhanced recovery for missing closing parentheses
            if (check(TokenType::RIGHT_PAREN)) {
                groupingNode->addToken(advance());
            } else {
                reportErrorWithSuggestions("Expected ')' after expression", 
                    {"Add closing parenthesis ')' to complete grouped expression",
                     "Check for nested parentheses balance",
                     "Verify expression syntax inside parentheses"});
                
                if (recoveryConfig.insertMissingTokens) {
                    // Insert missing closing parenthesis
                    Token missingParen;
                    missingParen.type = TokenType::RIGHT_PAREN;
                    missingParen.lexeme = ")";
                    missingParen.line = peek().line;
                    missingParen.start = getCurrentPosition();
                    missingParen.end = getCurrentPosition();
                    groupingNode->addToken(missingParen);
                } else {
                    // Create incomplete node to indicate missing closing paren
                    auto incompleteNode = CST::createIncompleteNode(NodeKind::GROUPING_EXPR,
                        "Missing closing parenthesis");
                    incompleteNode->addMissingElement("closing parenthesis ')'");
                    return incompleteNode;
                }
            }
            
            return groupingNode;
        }
        
        // If we reach here, we have an invalid token for an expression
        Token invalidToken = peek();
        reportErrorWithSuggestions("Expected expression, found '" + invalidToken.lexeme + "'",
            {"Provide a valid expression (literal, variable, or grouped expression)",
             "Check for missing operators or operands",
             "Verify syntax is correct at this position"});
        
        // Create error node for invalid expression token
        auto errorNode = CST::createErrorNode("Invalid expression token", 
            invalidToken.start, invalidToken.end);
        
        if (!isAtEnd()) {
            errorNode->addToken(advance()); // Consume the invalid token
        }
        
        return errorNode;
    }

    // Task 6: Statement parsing methods with error recovery
    
    std::unique_ptr<Node> CSTParser::parseVariableDeclaration() {
        // Parse: var name: type = initializer;
        Token startToken = peek();
        auto varNode = createNode(NodeKind::VAR_DECLARATION);
        
        // Consume 'var' keyword
        if (check(TokenType::VAR)) {
            varNode->addToken(advance());
        } else {
            reportError("Expected 'var' keyword", TokenType::VAR, peek().type);
            return createErrorRecoveryNode("Invalid variable declaration");
        }
        
        // Consume any trivia after 'var' keyword
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse variable name
        if (check(TokenType::IDENTIFIER)) {
            varNode->addToken(advance());
        } else {
            reportError("Expected variable name after 'var'", TokenType::IDENTIFIER, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingName;
                missingName.type = TokenType::IDENTIFIER;
                missingName.lexeme = "<missing_name>";
                missingName.line = peek().line;
                missingName.start = getCurrentPosition();
                missingName.end = getCurrentPosition();
                varNode->addToken(missingName);
            }
        }
        
        // Consume trivia before checking for type annotation
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse optional type annotation
        if (match(TokenType::COLON)) {
            varNode->addToken(previous()); // ':'
            
            // Consume trivia after colon
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
            
            // Parse type
            if (isTypeStart(peek().type)) {
                auto typeNode = parseType();
                if (typeNode) {
                    varNode->addNode(std::move(typeNode));
                }
            } else {
                reportError("Expected type after ':'", TokenType::IDENTIFIER, peek().type);
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingType = createMissingNode(NodeKind::USER_TYPE, "Missing type annotation");
                    varNode->addNode(std::move(missingType));
                }
            }
        }
        
        // Consume trivia before checking for initializer
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse optional initializer
        if (match(TokenType::EQUAL)) {
            Token equalsToken = previous();
            varNode->addToken(equalsToken); // '='
            
            // Consume trivia after equals
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
            
            // Check what comes after the equals sign
            TokenType nextType = peek().type;
            
            // If we immediately hit a semicolon, newline, or statement start, the initializer is missing
            if (nextType == TokenType::SEMICOLON || 
                nextType == TokenType::NEWLINE ||
                isStatementStart(nextType) || 
                isDeclarationStart(nextType) ||
                nextType == TokenType::EOF_TOKEN) {
                
                // Report error at the equals sign location, not the next token
                reportErrorAtToken("Expected initializer expression after '='", equalsToken, 
                                 TokenType::IDENTIFIER, nextType);
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingInit = createMissingNode(NodeKind::LITERAL_EXPR, "Missing initializer");
                    varNode->addNode(std::move(missingInit));
                }
            } else {
                // Try to parse the expression
                auto initializer = parseExpression();
                if (initializer) {
                    varNode->addNode(std::move(initializer));
                } else {
                    // Expression parsing failed
                    reportError("Invalid initializer expression after '='");
                    
                    if (recoveryConfig.createPartialNodes) {
                        auto missingInit = createMissingNode(NodeKind::LITERAL_EXPR, "Invalid initializer");
                        varNode->addNode(std::move(missingInit));
                    }
                }
            }
        }
        
        // Consume trivia before checking for semicolon
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse semicolon
        if (check(TokenType::SEMICOLON)) {
            varNode->addToken(advance());
        } else {
            // Check if we're at end of line or statement - this might be acceptable
            TokenType currentType = peek().type;
            if (currentType == TokenType::NEWLINE || 
                isStatementStart(currentType) || 
                isDeclarationStart(currentType) ||
                currentType == TokenType::EOF_TOKEN) {
                
                // Missing semicolon at end of variable declaration
                reportError("Expected ';' after variable declaration", TokenType::SEMICOLON, currentType);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingSemicolon;
                    missingSemicolon.type = TokenType::SEMICOLON;
                    missingSemicolon.lexeme = ";";
                    missingSemicolon.line = previous().line; // Use previous token's line
                    missingSemicolon.start = previous().end;  // Place after previous token
                    missingSemicolon.end = previous().end;
                    varNode->addToken(missingSemicolon);
                }
            } else {
                // Unexpected token where semicolon expected
                reportError("Expected ';' after variable declaration, found '" + peek().lexeme + "'", 
                           TokenType::SEMICOLON, currentType);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingSemicolon;
                    missingSemicolon.type = TokenType::SEMICOLON;
                    missingSemicolon.lexeme = ";";
                    missingSemicolon.line = peek().line;
                    missingSemicolon.start = getCurrentPosition();
                    missingSemicolon.end = getCurrentPosition();
                    varNode->addToken(missingSemicolon);
                }
            }
        }
        
        setNodeSpanFromTokens(*varNode, startToken, previous());
        return varNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseFunctionDeclaration() {
        // Parse: fn name(param1: type1, param2: type2): returnType { body }
        Token startToken = peek();
        auto fnNode = createNode(NodeKind::FUNCTION_DECLARATION);
        
        // Consume 'fn' keyword
        if (check(TokenType::FN)) {
            fnNode->addToken(advance());
        } else {
            reportError("Expected 'fn' keyword", TokenType::FN, peek().type);
            return createErrorRecoveryNode("Invalid function declaration");
        }
        
        // Consume trivia after 'fn' keyword
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse function name
        if (check(TokenType::IDENTIFIER)) {
            fnNode->addToken(advance());
        } else {
            reportError("Expected function name after 'fn'", TokenType::IDENTIFIER, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingName;
                missingName.type = TokenType::IDENTIFIER;
                missingName.lexeme = "<missing_function_name>";
                missingName.line = peek().line;
                missingName.start = getCurrentPosition();
                missingName.end = getCurrentPosition();
                fnNode->addToken(missingName);
            }
        }
        
        // Parse parameter list
        if (check(TokenType::LEFT_PAREN)) {
            fnNode->addToken(advance()); // '('
            
            // Parse parameters
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    // Consume trivia before parameter
                    if (recoveryConfig.preserveTrivia) {
                        consumeTrivia();
                    }
                    
                    auto param = parseParameter();
                    if (param) {
                        fnNode->addNode(std::move(param));
                    }
                    
                    // Consume trivia after parameter
                    if (recoveryConfig.preserveTrivia) {
                        consumeTrivia();
                    }
                } while (match(TokenType::COMMA));
            }
            
            if (check(TokenType::RIGHT_PAREN)) {
                fnNode->addToken(advance()); // ')'
            } else {
                reportError("Expected ')' after parameter list", TokenType::RIGHT_PAREN, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingParen;
                    missingParen.type = TokenType::RIGHT_PAREN;
                    missingParen.lexeme = ")";
                    missingParen.line = peek().line;
                    missingParen.start = getCurrentPosition();
                    missingParen.end = getCurrentPosition();
                    fnNode->addToken(missingParen);
                }
            }
        } else {
            reportError("Expected '(' after function name", TokenType::LEFT_PAREN, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingOpenParen;
                missingOpenParen.type = TokenType::LEFT_PAREN;
                missingOpenParen.lexeme = "(";
                missingOpenParen.line = peek().line;
                missingOpenParen.start = getCurrentPosition();
                missingOpenParen.end = getCurrentPosition();
                fnNode->addToken(missingOpenParen);
                
                Token missingCloseParen;
                missingCloseParen.type = TokenType::RIGHT_PAREN;
                missingCloseParen.lexeme = ")";
                missingCloseParen.line = peek().line;
                missingCloseParen.start = getCurrentPosition();
                missingCloseParen.end = getCurrentPosition();
                fnNode->addToken(missingCloseParen);
            }
        }
        
        // Consume trivia after parameter list
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse optional return type (using ':' instead of '->')
        if (match(TokenType::COLON)) {
            fnNode->addToken(previous()); // ':'
            
            // Consume trivia after colon
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
            
            if (isTypeStart(peek().type)) {
                auto returnType = parseType();
                if (returnType) {
                    fnNode->addNode(std::move(returnType));
                }
            } else {
                reportError("Expected return type after ':'");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingReturnType = createMissingNode(NodeKind::USER_TYPE, "Missing return type");
                    fnNode->addNode(std::move(missingReturnType));
                }
            }
        }
        
        // Consume trivia before function body
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse function body
        if (check(TokenType::LEFT_BRACE)) {
            auto body = parseBlock();
            if (body) {
                fnNode->addNode(std::move(body));
            }
        } else {
            reportError("Expected '{' to start function body", TokenType::LEFT_BRACE, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing function body");
                fnNode->addNode(std::move(missingBody));
            }
        }
        
        setNodeSpanFromTokens(*fnNode, startToken, previous());
        return fnNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseClassDeclaration() {
        // Parse: class Name extends SuperClass { members }
        Token startToken = peek();
        auto classNode = createNode(NodeKind::CLASS_DECLARATION);
        
        // Consume 'class' keyword
        if (check(TokenType::CLASS)) {
            classNode->addToken(advance());
        } else {
            reportError("Expected 'class' keyword", TokenType::CLASS, peek().type);
            return createErrorRecoveryNode("Invalid class declaration");
        }
        
        // Consume trivia after 'class' keyword
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse class name
        if (check(TokenType::IDENTIFIER)) {
            classNode->addToken(advance());
        } else {
            reportError("Expected class name after 'class'", TokenType::IDENTIFIER, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingName;
                missingName.type = TokenType::IDENTIFIER;
                missingName.lexeme = "<missing_class_name>";
                missingName.line = peek().line;
                missingName.start = getCurrentPosition();
                missingName.end = getCurrentPosition();
                classNode->addToken(missingName);
            }
        }
        
        // Parse optional inheritance
        if (match(TokenType::COLON)) {
            classNode->addToken(previous()); // ':'
            
            if (check(TokenType::IDENTIFIER)) {
                classNode->addToken(advance()); // superclass name
            } else {
                reportError("Expected superclass name after ':'", TokenType::IDENTIFIER, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingSuperclass;
                    missingSuperclass.type = TokenType::IDENTIFIER;
                    missingSuperclass.lexeme = "<missing_superclass>";
                    missingSuperclass.line = peek().line;
                    missingSuperclass.start = getCurrentPosition();
                    missingSuperclass.end = getCurrentPosition();
                    classNode->addToken(missingSuperclass);
                }
            }
        }
        
        // Parse class body
        if (check(TokenType::LEFT_BRACE)) {
            classNode->addToken(advance()); // '{'
            
            // Parse class members
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd() && shouldContinueParsing()) {
                // Skip trivia
                if (recoveryConfig.preserveTrivia) {
                    consumeTrivia();
                }
                
                // Parse member declaration
                if (isDeclarationStart(peek().type)) {
                    auto member = parseDeclaration();
                    if (member) {
                        classNode->addNode(std::move(member));
                    }
                } else if (peek().type == TokenType::RIGHT_BRACE) {
                    break; // End of class body
                } else {
                    reportError("Expected member declaration in class body");
                    
                    // Skip invalid tokens until we find a sync point
                    auto errorNode = createErrorRecoveryNode("Invalid class member");
                    while (!isAtEnd() && !isSyncToken(peek().type) && !check(TokenType::RIGHT_BRACE)) {
                        errorNode->addToken(advance());
                    }
                    classNode->addNode(std::move(errorNode));
                }
            }
            
            if (check(TokenType::RIGHT_BRACE)) {
                classNode->addToken(advance()); // '}'
            } else {
                reportError("Expected '}' to close class body", TokenType::RIGHT_BRACE, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingBrace;
                    missingBrace.type = TokenType::RIGHT_BRACE;
                    missingBrace.lexeme = "}";
                    missingBrace.line = peek().line;
                    missingBrace.start = getCurrentPosition();
                    missingBrace.end = getCurrentPosition();
                    classNode->addToken(missingBrace);
                }
            }
        } else {
            reportError("Expected '{' to start class body", TokenType::LEFT_BRACE, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing class body");
                classNode->addNode(std::move(missingBody));
            }
        }
        
        setNodeSpanFromTokens(*classNode, startToken, previous());
        return classNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseIfStatement() {
        // Parse: if (condition) { thenBranch } else { elseBranch }
        Token startToken = peek();
        auto ifNode = createNode(NodeKind::IF_STATEMENT);
        
        // Consume 'if' keyword
        if (check(TokenType::IF)) {
            ifNode->addToken(advance());
        } else {
            reportError("Expected 'if' keyword", TokenType::IF, peek().type);
            return createErrorRecoveryNode("Invalid if statement");
        }
        
        // Consume trivia after 'if' keyword
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse condition (with optional parentheses)
        bool hasParens = false;
        if (match(TokenType::LEFT_PAREN)) {
            ifNode->addToken(previous()); // '('
            hasParens = true;
            
            // Consume trivia after opening paren
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
        }
        
        auto condition = parseExpression();
        if (condition) {
            ifNode->addNode(std::move(condition));
        } else {
            reportError("Expected condition after 'if'");
            
            if (recoveryConfig.createPartialNodes) {
                auto missingCondition = createMissingNode(NodeKind::LITERAL_EXPR, "Missing if condition");
                ifNode->addNode(std::move(missingCondition));
            }
        }
        
        if (hasParens) {
            // Consume trivia before closing paren
            if (recoveryConfig.preserveTrivia) {
                consumeTrivia();
            }
            
            if (check(TokenType::RIGHT_PAREN)) {
                ifNode->addToken(advance()); // ')'
            } else {
                reportError("Expected ')' after if condition", TokenType::RIGHT_PAREN, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingParen;
                    missingParen.type = TokenType::RIGHT_PAREN;
                    missingParen.lexeme = ")";
                    missingParen.line = peek().line;
                    missingParen.start = getCurrentPosition();
                    missingParen.end = getCurrentPosition();
                    ifNode->addToken(missingParen);
                }
            }
        }
        
        // Consume trivia before then branch
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse then branch
        if (check(TokenType::LEFT_BRACE)) {
            auto thenBranch = parseBlock();
            if (thenBranch) {
                ifNode->addNode(std::move(thenBranch));
            }
        } else {
            // Single statement without braces
            auto stmt = parseStatement();
            if (stmt) {
                ifNode->addNode(std::move(stmt));
            } else {
                reportError("Expected statement or '{' after if condition");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingThen = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing then branch");
                    ifNode->addNode(std::move(missingThen));
                }
            }
        }
        
        // Parse optional else branch
        if (match(TokenType::ELSE)) {
            ifNode->addToken(previous()); // 'else'
            
            if (check(TokenType::IF)) {
                // else if - parse as nested if statement
                auto elseIf = parseIfStatement();
                if (elseIf) {
                    ifNode->addNode(std::move(elseIf));
                }
            } else if (check(TokenType::LEFT_BRACE)) {
                // else block
                auto elseBranch = parseBlock();
                if (elseBranch) {
                    ifNode->addNode(std::move(elseBranch));
                }
            } else {
                // Single statement without braces
                auto stmt = parseStatement();
                if (stmt) {
                    ifNode->addNode(std::move(stmt));
                } else {
                    reportError("Expected statement or '{' after 'else'");
                    
                    if (recoveryConfig.createPartialNodes) {
                        auto missingElse = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing else branch");
                        ifNode->addNode(std::move(missingElse));
                    }
                }
            }
        }
        
        setNodeSpanFromTokens(*ifNode, startToken, previous());
        return ifNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseForStatement() {
        // Parse: for (init; condition; update) { body }
        Token startToken = peek();
        auto forNode = createNode(NodeKind::FOR_STATEMENT);
        
        // Consume 'for' keyword
        if (check(TokenType::FOR)) {
            forNode->addToken(advance());
        } else {
            reportError("Expected 'for' keyword", TokenType::FOR, peek().type);
            return createErrorRecoveryNode("Invalid for statement");
        }
        
        // Parse for loop header
        if (check(TokenType::LEFT_PAREN)) {
            forNode->addToken(advance()); // '('
            
            // Parse initializer (can be variable declaration or expression)
            if (check(TokenType::VAR)) {
                auto init = parseVariableDeclaration();
                if (init) {
                    forNode->addNode(std::move(init));
                }
            } else if (!check(TokenType::SEMICOLON)) {
                auto init = parseExpression();
                if (init) {
                    forNode->addNode(std::move(init));
                }
                
                if (check(TokenType::SEMICOLON)) {
                    forNode->addToken(advance()); // ';'
                } else {
                    reportError("Expected ';' after for loop initializer", TokenType::SEMICOLON, peek().type);
                }
            } else {
                forNode->addToken(advance()); // ';' (empty initializer)
            }
            
            // Parse condition
            if (!check(TokenType::SEMICOLON)) {
                auto condition = parseExpression();
                if (condition) {
                    forNode->addNode(std::move(condition));
                }
            } else {
                // Empty condition - create a missing node
                if (recoveryConfig.createPartialNodes) {
                    auto missingCondition = createMissingNode(NodeKind::LITERAL_EXPR, "Missing for condition");
                    forNode->addNode(std::move(missingCondition));
                }
            }
            
            if (check(TokenType::SEMICOLON)) {
                forNode->addToken(advance()); // ';'
            } else {
                reportError("Expected ';' after for loop condition", TokenType::SEMICOLON, peek().type);
            }
            
            // Parse update expression
            if (!check(TokenType::RIGHT_PAREN)) {
                auto update = parseExpression();
                if (update) {
                    forNode->addNode(std::move(update));
                }
            }
            
            if (check(TokenType::RIGHT_PAREN)) {
                forNode->addToken(advance()); // ')'
            } else {
                reportError("Expected ')' after for loop header", TokenType::RIGHT_PAREN, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingParen;
                    missingParen.type = TokenType::RIGHT_PAREN;
                    missingParen.lexeme = ")";
                    missingParen.line = peek().line;
                    missingParen.start = getCurrentPosition();
                    missingParen.end = getCurrentPosition();
                    forNode->addToken(missingParen);
                }
            }
        } else {
            reportError("Expected '(' after 'for'", TokenType::LEFT_PAREN, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                // Create missing for loop header
                auto missingHeader = createMissingNode(NodeKind::PARAMETER_LIST, "Missing for loop header");
                forNode->addNode(std::move(missingHeader));
            }
        }
        
        // Parse loop body
        if (check(TokenType::LEFT_BRACE)) {
            auto body = parseBlock();
            if (body) {
                forNode->addNode(std::move(body));
            }
        } else {
            // Single statement without braces
            auto stmt = parseStatement();
            if (stmt) {
                forNode->addNode(std::move(stmt));
            } else {
                reportError("Expected statement or '{' for loop body");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing for loop body");
                    forNode->addNode(std::move(missingBody));
                }
            }
        }
        
        setNodeSpanFromTokens(*forNode, startToken, previous());
        return forNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseWhileStatement() {
        // Parse: while (condition) { body }
        Token startToken = peek();
        auto whileNode = createNode(NodeKind::WHILE_STATEMENT);
        
        // Consume 'while' keyword
        if (check(TokenType::WHILE)) {
            whileNode->addToken(advance());
        } else {
            reportError("Expected 'while' keyword", TokenType::WHILE, peek().type);
            return createErrorRecoveryNode("Invalid while statement");
        }
        
        // Parse condition (with optional parentheses)
        bool hasParens = false;
        if (match(TokenType::LEFT_PAREN)) {
            whileNode->addToken(previous()); // '('
            hasParens = true;
        }
        
        auto condition = parseExpression();
        if (condition) {
            whileNode->addNode(std::move(condition));
        } else {
            reportError("Expected condition after 'while'");
            
            if (recoveryConfig.createPartialNodes) {
                auto missingCondition = createMissingNode(NodeKind::LITERAL_EXPR, "Missing while condition");
                whileNode->addNode(std::move(missingCondition));
            }
        }
        
        if (hasParens) {
            if (check(TokenType::RIGHT_PAREN)) {
                whileNode->addToken(advance()); // ')'
            } else {
                reportError("Expected ')' after while condition", TokenType::RIGHT_PAREN, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingParen;
                    missingParen.type = TokenType::RIGHT_PAREN;
                    missingParen.lexeme = ")";
                    missingParen.line = peek().line;
                    missingParen.start = getCurrentPosition();
                    missingParen.end = getCurrentPosition();
                    whileNode->addToken(missingParen);
                }
            }
        }
        
        // Parse loop body
        if (check(TokenType::LEFT_BRACE)) {
            auto body = parseBlock();
            if (body) {
                whileNode->addNode(std::move(body));
            }
        } else {
            // Single statement without braces
            auto stmt = parseStatement();
            if (stmt) {
                whileNode->addNode(std::move(stmt));
            } else {
                reportError("Expected statement or '{' for while body");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing while loop body");
                    whileNode->addNode(std::move(missingBody));
                }
            }
        }
        
        setNodeSpanFromTokens(*whileNode, startToken, previous());
        return whileNode;
    }

    // Helper methods for statement parsing
    
    std::unique_ptr<Node> CSTParser::parseParameter() {
        // Parse: name: type or name: type = default
        auto paramNode = createNode(NodeKind::PARAMETER);
        Token startToken = peek();
        
        // Parse parameter name
        if (check(TokenType::IDENTIFIER)) {
            paramNode->addToken(advance());
        } else {
            reportError("Expected parameter name", TokenType::IDENTIFIER, peek().type);
            return createErrorRecoveryNode("Invalid parameter");
        }
        
        // Parse type annotation
        if (match(TokenType::COLON)) {
            paramNode->addToken(previous()); // ':'
            
            if (isTypeStart(peek().type)) {
                auto type = parseType();
                if (type) {
                    paramNode->addNode(std::move(type));
                }
            } else {
                reportError("Expected type after ':'", TokenType::IDENTIFIER, peek().type);
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingType = createMissingNode(NodeKind::USER_TYPE, "Missing parameter type");
                    paramNode->addNode(std::move(missingType));
                }
            }
        }
        
        // Parse optional default value
        if (match(TokenType::EQUAL)) {
            paramNode->addToken(previous()); // '='
            
            auto defaultValue = parseExpression();
            if (defaultValue) {
                paramNode->addNode(std::move(defaultValue));
            } else {
                reportError("Expected default value after '='");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingDefault = createMissingNode(NodeKind::LITERAL_EXPR, "Missing default value");
                    paramNode->addNode(std::move(missingDefault));
                }
            }
        }
        
        setNodeSpanFromTokens(*paramNode, startToken, previous());
        return paramNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseType() {
        // Simple type parsing - can be extended for complex types
        if (check(TokenType::IDENTIFIER) || isBuiltinType(peek().type)) {
            auto typeNode = createNode(NodeKind::USER_TYPE);
            typeNode->addToken(advance());
            return typeNode;
        }
        
        reportError("Expected type");
        return createErrorRecoveryNode("Invalid type");
    }
    
    bool CSTParser::isTypeStart(TokenType type) const {
        return type == TokenType::IDENTIFIER || isBuiltinType(type);
    }
    
    bool CSTParser::isBuiltinType(TokenType type) const {
        return type == TokenType::INT_TYPE || type == TokenType::FLOAT_TYPE || 
               type == TokenType::STR_TYPE || type == TokenType::BOOL_TYPE ||
               type == TokenType::LIST_TYPE || type == TokenType::DICT_TYPE;
    }

    // Stub implementations for remaining statement types
    
    std::unique_ptr<Node> CSTParser::parseTypeDeclaration() {
        // Parse: type Name = Type;
        Token startToken = peek();
        auto typeNode = createNode(NodeKind::TYPE_DECLARATION);
        
        // Consume 'type' keyword
        if (check(TokenType::TYPE)) {
            typeNode->addToken(advance());
        } else {
            reportError("Expected 'type' keyword", TokenType::TYPE, peek().type);
            return createErrorRecoveryNode("Invalid type declaration");
        }
        
        // Parse type name
        if (check(TokenType::IDENTIFIER)) {
            typeNode->addToken(advance());
        } else {
            reportError("Expected type name after 'type'", TokenType::IDENTIFIER, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingName;
                missingName.type = TokenType::IDENTIFIER;
                missingName.lexeme = "<missing_type_name>";
                missingName.line = peek().line;
                missingName.start = getCurrentPosition();
                missingName.end = getCurrentPosition();
                typeNode->addToken(missingName);
            }
        }
        
        // Parse '=' for type alias
        if (check(TokenType::EQUAL)) {
            typeNode->addToken(advance());
            
            // Parse the aliased type
            if (isTypeStart(peek().type)) {
                auto aliasedType = parseType();
                if (aliasedType) {
                    typeNode->addNode(std::move(aliasedType));
                }
            } else {
                reportError("Expected type after '='");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingType = createMissingNode(NodeKind::USER_TYPE, "Missing aliased type");
                    typeNode->addNode(std::move(missingType));
                }
            }
        } else {
            reportError("Expected '=' after type name", TokenType::EQUAL, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingEqual;
                missingEqual.type = TokenType::EQUAL;
                missingEqual.lexeme = "=";
                missingEqual.line = peek().line;
                missingEqual.start = getCurrentPosition();
                missingEqual.end = getCurrentPosition();
                typeNode->addToken(missingEqual);
                
                // Also add a missing type
                if (recoveryConfig.createPartialNodes) {
                    auto missingType = createMissingNode(NodeKind::USER_TYPE, "Missing aliased type");
                    typeNode->addNode(std::move(missingType));
                }
            }
        }
        
        // Parse semicolon
        if (check(TokenType::SEMICOLON)) {
            typeNode->addToken(advance());
        } else {
            reportError("Expected ';' after type declaration", TokenType::SEMICOLON, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingSemicolon;
                missingSemicolon.type = TokenType::SEMICOLON;
                missingSemicolon.lexeme = ";";
                missingSemicolon.line = peek().line;
                missingSemicolon.start = getCurrentPosition();
                missingSemicolon.end = getCurrentPosition();
                typeNode->addToken(missingSemicolon);
            }
        }
        
        setNodeSpanFromTokens(*typeNode, startToken, previous());
        return typeNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseTraitDeclaration() {
        // Parse: trait Name { methods }
        Token startToken = peek();
        auto traitNode = createNode(NodeKind::TRAIT_DECLARATION);
        
        // Consume 'trait' keyword
        if (check(TokenType::TRAIT)) {
            traitNode->addToken(advance());
        } else {
            reportError("Expected 'trait' keyword", TokenType::TRAIT, peek().type);
            return createErrorRecoveryNode("Invalid trait declaration");
        }
        
        // Parse trait name
        if (check(TokenType::IDENTIFIER)) {
            traitNode->addToken(advance());
        } else {
            reportError("Expected trait name after 'trait'", TokenType::IDENTIFIER, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingName;
                missingName.type = TokenType::IDENTIFIER;
                missingName.lexeme = "<missing_trait_name>";
                missingName.line = peek().line;
                missingName.start = getCurrentPosition();
                missingName.end = getCurrentPosition();
                traitNode->addToken(missingName);
            }
        }
        
        // Parse trait body
        if (check(TokenType::LEFT_BRACE)) {
            traitNode->addToken(advance()); // '{'
            
            // Parse trait methods and declarations
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd() && shouldContinueParsing()) {
                // Skip trivia
                if (recoveryConfig.preserveTrivia) {
                    consumeTrivia();
                }
                
                // Parse trait member (typically function declarations)
                if (isDeclarationStart(peek().type)) {
                    auto member = parseDeclaration();
                    if (member) {
                        traitNode->addNode(std::move(member));
                    }
                } else if (peek().type == TokenType::RIGHT_BRACE) {
                    break; // End of trait body
                } else {
                    reportError("Expected method declaration in trait body");
                    
                    // Skip invalid tokens until we find a sync point
                    auto errorNode = createErrorRecoveryNode("Invalid trait member");
                    while (!isAtEnd() && !isSyncToken(peek().type) && !check(TokenType::RIGHT_BRACE)) {
                        errorNode->addToken(advance());
                    }
                    traitNode->addNode(std::move(errorNode));
                }
            }
            
            if (check(TokenType::RIGHT_BRACE)) {
                traitNode->addToken(advance()); // '}'
            } else {
                reportError("Expected '}' to close trait body", TokenType::RIGHT_BRACE, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingBrace;
                    missingBrace.type = TokenType::RIGHT_BRACE;
                    missingBrace.lexeme = "}";
                    missingBrace.line = peek().line;
                    missingBrace.start = getCurrentPosition();
                    missingBrace.end = getCurrentPosition();
                    traitNode->addToken(missingBrace);
                }
            }
        } else {
            reportError("Expected '{' to start trait body", TokenType::LEFT_BRACE, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing trait body");
                traitNode->addNode(std::move(missingBody));
            }
        }
        
        setNodeSpanFromTokens(*traitNode, startToken, previous());
        return traitNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseInterfaceDeclaration() {
        // Parse: interface Name { method signatures }
        Token startToken = peek();
        auto interfaceNode = createNode(NodeKind::INTERFACE_DECLARATION);
        
        // Consume 'interface' keyword
        if (check(TokenType::INTERFACE)) {
            interfaceNode->addToken(advance());
        } else {
            reportError("Expected 'interface' keyword", TokenType::INTERFACE, peek().type);
            return createErrorRecoveryNode("Invalid interface declaration");
        }
        
        // Parse interface name
        if (check(TokenType::IDENTIFIER)) {
            interfaceNode->addToken(advance());
        } else {
            reportError("Expected interface name after 'interface'", TokenType::IDENTIFIER, peek().type);
            
            if (recoveryConfig.insertMissingTokens) {
                Token missingName;
                missingName.type = TokenType::IDENTIFIER;
                missingName.lexeme = "<missing_interface_name>";
                missingName.line = peek().line;
                missingName.start = getCurrentPosition();
                missingName.end = getCurrentPosition();
                interfaceNode->addToken(missingName);
            }
        }
        
        // Parse interface body
        if (check(TokenType::LEFT_BRACE)) {
            interfaceNode->addToken(advance()); // '{'
            
            // Parse interface method signatures
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd() && shouldContinueParsing()) {
                // Skip trivia
                if (recoveryConfig.preserveTrivia) {
                    consumeTrivia();
                }
                
                // Parse interface member (typically function signatures)
                if (isDeclarationStart(peek().type)) {
                    auto member = parseDeclaration();
                    if (member) {
                        interfaceNode->addNode(std::move(member));
                    }
                } else if (peek().type == TokenType::RIGHT_BRACE) {
                    break; // End of interface body
                } else {
                    reportError("Expected method signature in interface body");
                    
                    // Skip invalid tokens until we find a sync point
                    auto errorNode = createErrorRecoveryNode("Invalid interface member");
                    while (!isAtEnd() && !isSyncToken(peek().type) && !check(TokenType::RIGHT_BRACE)) {
                        errorNode->addToken(advance());
                    }
                    interfaceNode->addNode(std::move(errorNode));
                }
            }
            
            if (check(TokenType::RIGHT_BRACE)) {
                interfaceNode->addToken(advance()); // '}'
            } else {
                reportError("Expected '}' to close interface body", TokenType::RIGHT_BRACE, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingBrace;
                    missingBrace.type = TokenType::RIGHT_BRACE;
                    missingBrace.lexeme = "}";
                    missingBrace.line = peek().line;
                    missingBrace.start = getCurrentPosition();
                    missingBrace.end = getCurrentPosition();
                    interfaceNode->addToken(missingBrace);
                }
            }
        } else {
            reportError("Expected '{' to start interface body", TokenType::LEFT_BRACE, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing interface body");
                interfaceNode->addNode(std::move(missingBody));
            }
        }
        
        setNodeSpanFromTokens(*interfaceNode, startToken, previous());
        return interfaceNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseIterStatement() {
        // Parse: iter (variable in iterable) { body }
        Token startToken = peek();
        auto iterNode = createNode(NodeKind::ITER_STATEMENT);
        
        // Consume 'iter' keyword
        if (check(TokenType::ITER)) {
            iterNode->addToken(advance());
        } else {
            reportError("Expected 'iter' keyword", TokenType::ITER, peek().type);
            return createErrorRecoveryNode("Invalid iter statement");
        }
        
        // Parse iter header with parentheses
        if (check(TokenType::LEFT_PAREN)) {
            iterNode->addToken(advance()); // '('
            
            // Parse iterator variable
            if (check(TokenType::IDENTIFIER)) {
                iterNode->addToken(advance());
            } else {
                reportError("Expected iterator variable name", TokenType::IDENTIFIER, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingVar;
                    missingVar.type = TokenType::IDENTIFIER;
                    missingVar.lexeme = "<missing_var>";
                    missingVar.line = peek().line;
                    missingVar.start = getCurrentPosition();
                    missingVar.end = getCurrentPosition();
                    iterNode->addToken(missingVar);
                }
            }
            
            // Parse 'in' keyword
            if (check(TokenType::IN)) {
                iterNode->addToken(advance());
            } else {
                reportError("Expected 'in' after iterator variable", TokenType::IN, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingIn;
                    missingIn.type = TokenType::IN;
                    missingIn.lexeme = "in";
                    missingIn.line = peek().line;
                    missingIn.start = getCurrentPosition();
                    missingIn.end = getCurrentPosition();
                    iterNode->addToken(missingIn);
                }
            }
            
            // Parse iterable expression
            auto iterable = parseExpression();
            if (iterable) {
                iterNode->addNode(std::move(iterable));
            } else {
                reportError("Expected iterable expression after 'in'");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingIterable = createMissingNode(NodeKind::LITERAL_EXPR, "Missing iterable expression");
                    iterNode->addNode(std::move(missingIterable));
                }
            }
            
            // Parse closing parenthesis
            if (check(TokenType::RIGHT_PAREN)) {
                iterNode->addToken(advance()); // ')'
            } else {
                reportError("Expected ')' after iter expression", TokenType::RIGHT_PAREN, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingParen;
                    missingParen.type = TokenType::RIGHT_PAREN;
                    missingParen.lexeme = ")";
                    missingParen.line = peek().line;
                    missingParen.start = getCurrentPosition();
                    missingParen.end = getCurrentPosition();
                    iterNode->addToken(missingParen);
                }
            }
        } else {
            reportError("Expected '(' after 'iter'", TokenType::LEFT_PAREN, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                // Create missing iter header
                auto missingHeader = createMissingNode(NodeKind::PARAMETER_LIST, "Missing iter header");
                iterNode->addNode(std::move(missingHeader));
            }
        }
        
        // Parse loop body
        if (check(TokenType::LEFT_BRACE)) {
            auto body = parseBlock();
            if (body) {
                iterNode->addNode(std::move(body));
            }
        } else {
            // Single statement without braces
            auto stmt = parseStatement();
            if (stmt) {
                iterNode->addNode(std::move(stmt));
            } else {
                reportError("Expected statement or '{' for iter body");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing iter loop body");
                    iterNode->addNode(std::move(missingBody));
                }
            }
        }
        
        setNodeSpanFromTokens(*iterNode, startToken, previous());
        return iterNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseMatchStatement() {
        // Parse: match (expression) { case pattern => statement ... }
        Token startToken = peek();
        auto matchNode = createNode(NodeKind::MATCH_STATEMENT);
        
        // Consume 'match' keyword
        if (check(TokenType::MATCH)) {
            matchNode->addToken(advance());
        } else {
            reportError("Expected 'match' keyword", TokenType::MATCH, peek().type);
            return createErrorRecoveryNode("Invalid match statement");
        }
        
        // Parse match expression with parentheses
        if (check(TokenType::LEFT_PAREN)) {
            matchNode->addToken(advance()); // '('
            
            auto expr = parseExpression();
            if (expr) {
                matchNode->addNode(std::move(expr));
            } else {
                reportError("Expected expression after 'match ('");
                
                if (recoveryConfig.createPartialNodes) {
                    auto missingExpr = createMissingNode(NodeKind::LITERAL_EXPR, "Missing match expression");
                    matchNode->addNode(std::move(missingExpr));
                }
            }
            
            if (check(TokenType::RIGHT_PAREN)) {
                matchNode->addToken(advance()); // ')'
            } else {
                reportError("Expected ')' after match expression", TokenType::RIGHT_PAREN, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingParen;
                    missingParen.type = TokenType::RIGHT_PAREN;
                    missingParen.lexeme = ")";
                    missingParen.line = peek().line;
                    missingParen.start = getCurrentPosition();
                    missingParen.end = getCurrentPosition();
                    matchNode->addToken(missingParen);
                }
            }
        } else {
            reportError("Expected '(' after 'match'", TokenType::LEFT_PAREN, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                auto missingExpr = createMissingNode(NodeKind::LITERAL_EXPR, "Missing match expression");
                matchNode->addNode(std::move(missingExpr));
            }
        }
        
        // Parse match body with cases
        if (check(TokenType::LEFT_BRACE)) {
            matchNode->addToken(advance()); // '{'
            
            // Parse match cases
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd() && shouldContinueParsing()) {
                // Skip trivia between cases
                if (recoveryConfig.preserveTrivia) {
                    consumeTrivia();
                }
                
                // Parse case pattern and statement
                // For now, treat each case as a statement until we have proper pattern parsing
                auto caseStmt = parseStatement();
                if (caseStmt) {
                    matchNode->addNode(std::move(caseStmt));
                }
                
                // Handle error recovery within match body
                if (!canRecover()) {
                    break;
                }
            }
            
            if (check(TokenType::RIGHT_BRACE)) {
                matchNode->addToken(advance()); // '}'
            } else {
                reportError("Expected '}' to close match body", TokenType::RIGHT_BRACE, peek().type);
                
                if (recoveryConfig.insertMissingTokens) {
                    Token missingBrace;
                    missingBrace.type = TokenType::RIGHT_BRACE;
                    missingBrace.lexeme = "}";
                    missingBrace.line = peek().line;
                    missingBrace.start = getCurrentPosition();
                    missingBrace.end = getCurrentPosition();
                    matchNode->addToken(missingBrace);
                }
            }
        } else {
            reportError("Expected '{' for match body", TokenType::LEFT_BRACE, peek().type);
            
            if (recoveryConfig.createPartialNodes) {
                auto missingBody = createMissingNode(NodeKind::BLOCK_STATEMENT, "Missing match body");
                matchNode->addNode(std::move(missingBody));
            }
        }
        
        setNodeSpanFromTokens(*matchNode, startToken, previous());
        return matchNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseReturnStatement() {
        // Parse: return expression;
        Token startToken = peek();
        auto returnNode = createNode(NodeKind::RETURN_STATEMENT);
        
        if (check(TokenType::RETURN)) {
            returnNode->addToken(advance());
        }
        
        // Consume trivia after 'return' keyword
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse optional return value
        if (!check(TokenType::SEMICOLON) && !isAtEnd()) {
            auto expr = parseExpression();
            if (expr) {
                returnNode->addNode(std::move(expr));
            }
        }
        
        // Consume trivia before semicolon
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse semicolon
        if (check(TokenType::SEMICOLON)) {
            returnNode->addToken(advance());
        }
        
        setNodeSpanFromTokens(*returnNode, startToken, previous());
        return returnNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseBreakStatement() {
        // Parse: break;
        Token startToken = peek();
        auto breakNode = createNode(NodeKind::BREAK_STATEMENT);
        
        if (check(TokenType::BREAK)) {
            breakNode->addToken(advance());
        }
        
        if (check(TokenType::SEMICOLON)) {
            breakNode->addToken(advance());
        }
        
        setNodeSpanFromTokens(*breakNode, startToken, previous());
        return breakNode;
    }
    
    std::unique_ptr<Node> CSTParser::parseContinueStatement() {
        // Parse: continue;
        Token startToken = peek();
        auto continueNode = createNode(NodeKind::CONTINUE_STATEMENT);
        
        if (check(TokenType::CONTINUE)) {
            continueNode->addToken(advance());
        }
        
        if (check(TokenType::SEMICOLON)) {
            continueNode->addToken(advance());
        }
        
        setNodeSpanFromTokens(*continueNode, startToken, previous());
        return continueNode;
    }
    
    std::unique_ptr<Node> CSTParser::parsePrintStatement() {
        // Parse: print expression;
        Token startToken = peek();
        auto printNode = createNode(NodeKind::PRINT_STATEMENT);
        
        if (check(TokenType::PRINT)) {
            printNode->addToken(advance());
        }
        
        // Consume trivia after 'print' keyword
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse expression to print
        auto expr = parseExpression();
        if (expr) {
            printNode->addNode(std::move(expr));
        }
        
        // Consume trivia before semicolon
        if (recoveryConfig.preserveTrivia) {
            consumeTrivia();
        }
        
        // Parse semicolon
        if (check(TokenType::SEMICOLON)) {
            printNode->addToken(advance());
        }
        
        setNodeSpanFromTokens(*printNode, startToken, previous());
        return printNode;
    }
    
    // Enhanced parseBinaryExpr with operator precedence and missing operand recovery
    std::unique_ptr<Node> CSTParser::parseBinaryExpr(std::unique_ptr<Node> (CSTParser::*parseNext)(), 
                                                     const std::vector<TokenType>& operators) {
        auto expr = (this->*parseNext)();
        
        while (true) {
            bool foundOperator = false;
            TokenType currentOp = TokenType::UNDEFINED;
            
            // Check if current token matches any of the operators
            for (TokenType op : operators) {
                if (check(op)) {
                    foundOperator = true;
                    currentOp = op;
                    break;
                }
            }
            
            if (!foundOperator) {
                break;
            }
            
            // Consume the operator
            advance();
            Token operatorToken = previous();
            
            auto binaryNode = createNode(NodeKind::BINARY_EXPR);
            binaryNode->addNode(std::move(expr));
            binaryNode->addToken(operatorToken);
            
            // Parse right operand with enhanced error recovery
            auto right = (this->*parseNext)();
            if (right) {
                binaryNode->addNode(std::move(right));
            } else {
                // Enhanced recovery for missing operand after binary operator
                reportErrorWithSuggestions("Expected expression after binary operator '" + operatorToken.lexeme + "'",
                    {"Add a valid expression after the operator",
                     "Check for missing operand or extra operator",
                     "Verify operator precedence and grouping"});
                
                // Create missing node for the expected right operand
                auto missingOperand = CST::createMissingNode(NodeKind::BINARY_EXPR, 
                    "Missing right operand for binary operator '" + operatorToken.lexeme + "'");
                binaryNode->addNode(std::move(missingOperand));
                
                // Try to recover by synchronizing to next meaningful token
                if (recoveryConfig.continueOnError) {
                    // Look ahead to see if we can find a valid expression start
                    if (isExpressionStart(peek().type)) {
                        // Continue parsing - the missing operand error is recorded
                    } else {
                        // Skip to synchronization point
                        synchronize();
                    }
                }
            }
            
            expr = std::move(binaryNode);
        }
        
        return expr;
    }
    
    // Helper method to check if an identifier is a reserved keyword
    bool CSTParser::isReservedKeyword(const std::string& identifier) const {
        static const std::unordered_set<std::string> reservedKeywords = {
            "var", "fn", "class", "if", "elif", "else", "for", "while", "where", "iter", "in",
            "match", "return", "break", "continue", "print", "true", "false", "nil",
            "and", "as", "not", "type", "trait", "interface", "import", "export",
            "module", "async", "await", "parallel", "concurrent", "attempt", "handle",
            "contract", "requires", "ensures", "invariant", "contract", "assert", "assume",
            "int", "uint", "float", "bool", "str", "list", "dict", "array",
            "Some", "None", "Ok", "Err", "Result", "Option"
        };
        
        return reservedKeywords.find(identifier) != reservedKeywords.end();
    }

    // Unified Grammar System - Token matching implementations
    
    RuleResult CSTParser::parseToken(TokenType type, ParseContext& context) {
        if (!context.match(type)) {
            RuleResult result;
            result.success = false;
            result.errorMessage = "Expected token type " + std::to_string(static_cast<int>(type));
            return result;
        }
        
        Token token = context.advance();
        
        RuleResult result;
        result.success = true;
        result.tokensConsumed = 1;
        
        if (context.mode == ParserMode::DIRECT_AST) {
            // For AST mode, tokens are typically incorporated into parent nodes
            result.success = true;
        } else {
            // For CST mode, create a token node
            auto tokenNode = createTokenNode(token);
            result.node = std::move(tokenNode);
        }
        
        return result;
    }
    
    RuleResult CSTParser::parseKeyword(const std::string& keyword, ParseContext& context) {
        Token token = context.peek();
        if (token.type != TokenType::IDENTIFIER || token.lexeme != keyword) {
            RuleResult result;
            result.success = false;
            result.errorMessage = "Expected keyword '" + keyword + "'";
            return result;
        }
        
        context.advance();
        
        RuleResult result;
        result.success = true;
        result.tokensConsumed = 1;
        
        if (context.mode == ParserMode::DIRECT_AST) {
            result.success = true;
        } else {
            auto tokenNode = createTokenNode(token);
            result.node = std::move(tokenNode);
        }
        
        return result;
    }
    
    RuleResult CSTParser::parseIdentifier(ParseContext& context) {
        if (!context.match(TokenType::IDENTIFIER)) {
            RuleResult result;
            result.success = false;
            result.errorMessage = "Expected identifier";
            return result;
        }
        
        Token token = context.advance();
        
        RuleResult result;
        result.success = true;
        result.tokensConsumed = 1;
        
        if (context.mode == ParserMode::DIRECT_AST) {
            auto varExpr = std::make_shared<AST::VariableExpr>();
            varExpr->line = token.line;
            varExpr->name = token.lexeme;
            result.node = std::static_pointer_cast<AST::Node>(varExpr);
        } else {
            auto identifierNode = createNode(NodeKind::IDENTIFIER);
            identifierNode->addToken(token);
            result.node = std::move(identifierNode);
        }
        
        return result;
    }
    
    RuleResult CSTParser::parseLiteral(ParseContext& context) {
        Token token = context.peek();
        
        if (!context.match({TokenType::NUMBER, TokenType::STRING, TokenType::TRUE, TokenType::FALSE, TokenType::NIL})) {
            RuleResult result;
            result.success = false;
            result.errorMessage = "Expected literal value";
            return result;
        }
        
        context.advance();
        
        RuleResult result;
        result.success = true;
        result.tokensConsumed = 1;
        
        if (context.mode == ParserMode::DIRECT_AST) {
            auto literalExpr = std::make_shared<AST::LiteralExpr>();
            literalExpr->line = token.line;
            
            // Convert token to appropriate literal value
            switch (token.type) {
                case TokenType::NUMBER:
                    if (token.lexeme.find('.') != std::string::npos) {
                        literalExpr->value = std::stod(token.lexeme);
                    } else {
                        literalExpr->value = std::stoll(token.lexeme);
                    }
                    break;
                case TokenType::STRING:
                    literalExpr->value = token.lexeme;
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
                    break;
            }
            
            result.node = std::static_pointer_cast<AST::Node>(literalExpr);
        } else {
            auto literalNode = createNode(NodeKind::LITERAL);
            literalNode->addToken(token);
            result.node = std::move(literalNode);
        }
        
        return result;
    }
    
    // Helper method for binary expressions in unified grammar
    RuleResult CSTParser::parseBinaryExpressionRule(const std::string& nextRule, const std::vector<TokenType>& operators, ParseContext& context) {
        auto leftResult = executeRule(nextRule, context);
        if (!leftResult.success) {
            return leftResult;
        }
        
        while (!context.isAtEnd() && std::find(operators.begin(), operators.end(), context.peek().type) != operators.end()) {
            Token op = context.advance();
            auto rightResult = executeRule(nextRule, context);
            
            if (!rightResult.success) {
                RuleResult result;
                result.success = false;
                result.errorMessage = "Expected right operand for binary expression";
                return result;
            }
            
            if (context.mode == ParserMode::DIRECT_AST) {
                auto binaryExpr = std::make_shared<AST::BinaryExpr>();
                binaryExpr->line = op.line;
                binaryExpr->left = leftResult.getAST<AST::Expression>();
                binaryExpr->op = op.type;
                binaryExpr->right = rightResult.getAST<AST::Expression>();
                
                leftResult.node = std::static_pointer_cast<AST::Node>(binaryExpr);
                leftResult.tokensConsumed += 1 + rightResult.tokensConsumed;
            } else {
                auto binaryNode = createNode(NodeKind::BINARY_EXPR);
                if (leftResult.hasCST()) {
                    // Skip CST node addition for now due to ownership complexity
                }
                binaryNode->addToken(op);
                if (rightResult.hasCST()) {
                    // Skip CST node addition for now due to ownership complexity
                }
                
                leftResult.node = std::move(binaryNode);
                leftResult.tokensConsumed += 1 + rightResult.tokensConsumed;
            }
        }
        
        return leftResult;
    }
    
    // Performance and caching methods
    
    bool CSTParser::shouldUseCache(const std::string& ruleName) const {
        // Enable caching for expensive rules
        static const std::unordered_set<std::string> cacheableRules = {
            "expression", "statement", "typeAnnotation", "primaryExpression"
        };
        
        return cacheableRules.find(ruleName) != cacheableRules.end();
    }
    
    void CSTParser::cacheResult(const std::string& ruleName, size_t tokenPos, const RuleResult& result) const {
        // Caching disabled for now due to RuleResult move-only semantics
        // if (result.success) {
        //     ruleCache[ruleName][tokenPos] = std::move(result);
        // }
    }
    
    std::optional<RuleResult> CSTParser::getCachedResult(const std::string& ruleName, size_t tokenPos) const {
        // Caching disabled for now due to RuleResult move-only semantics
        return std::nullopt;
    }
    
    void CSTParser::updateStats(const RuleResult& result) const {
        stats.tokensConsumed += result.tokensConsumed;
    }
    
    std::string CSTParser::getCurrentRuleContext(ParseContext& context) const {
        if (context.currentToken < context.tokens.size()) {
            return "at token: " + context.tokens[context.currentToken].lexeme;
        }
        return "at end of input";
    }

    // ParseContext implementation
    
    Token ParseContext::peek(size_t offset) const {
        size_t pos = currentToken + offset;
        if (pos >= tokens.size()) {
            Token eofToken;
            eofToken.type = TokenType::EOF_TOKEN;
            eofToken.lexeme = "";
            eofToken.line = tokens.empty() ? 1 : tokens.back().line;
            return eofToken;
        }
        return tokens[pos];
    }
    
    Token ParseContext::advance() {
        if (currentToken < tokens.size()) {
            return tokens[currentToken++];
        }
        return peek();
    }
    
    bool ParseContext::match(TokenType type) {
        return peek().type == type;
    }
    
    bool ParseContext::match(std::initializer_list<TokenType> types) {
        TokenType current = peek().type;
        return std::find(types.begin(), types.end(), current) != types.end();
    }
    
    void ParseContext::reportError(const std::string& message) {
        if (errors.size() < maxErrors) {
            errors.push_back(message);
        }
    }
    
    void ParseContext::collectTrivia() {
        if (skipTriviaCollection) return;
        
        while (currentToken < tokens.size()) {
            Token token = tokens[currentToken];
            if (token.type == TokenType::WHITESPACE || 
                token.type == TokenType::NEWLINE ||
                token.type == TokenType::COMMENT_LINE ||
                token.type == TokenType::COMMENT_BLOCK) {
                triviaBuffer.push_back(token);
                currentToken++;
            } else {
                break;
            }
        }
    }

    // GrammarTable implementation
    
    void GrammarTable::addRule(const GrammarRule& rule) {
        rules_.emplace(rule.name, rule);
    }
    
    void GrammarTable::addRule(const std::string& name, GrammarRule::RuleFunction func) {
        rules_.emplace(name, GrammarRule(name, func));
    }
    
    const GrammarRule* GrammarTable::getRule(const std::string& name) const {
        auto it = rules_.find(name);
        return it != rules_.end() ? &it->second : nullptr;
    }
    
    bool GrammarTable::hasRule(const std::string& name) const {
        return rules_.find(name) != rules_.end();
    }
    
    RuleResult GrammarTable::executeRule(const std::string& name, ParseContext& context) const {
        auto rule = getRule(name);
        if (!rule) {
            RuleResult result;
            result.success = false;
            result.errorMessage = "Unknown rule: " + name;
            return result;
        }
        
        // Memoization disabled for now due to RuleResult move-only semantics
        
        // Execute the rule
        auto result = rule->execute(context);
        
        // Caching disabled for now due to RuleResult move-only semantics
        
        return result;
    }
    
    std::vector<std::string> GrammarTable::getAllRuleNames() const {
        std::vector<std::string> names;
        for (const auto& pair : rules_) {
            names.push_back(pair.first);
        }
        return names;
    }
    
    void GrammarTable::optimizeRuleOrder() {
        // Sort rules by priority (higher priority first)
        // This is a simplified implementation - in practice we'd do more sophisticated optimization
    }
    
    std::string GrammarTable::getMemoKey(const std::string& ruleName, size_t tokenPos) const {
        return ruleName + "_" + std::to_string(tokenPos);
    }
    
    // Utility functions
    
    RuleBuilder rule(const std::string& name) {
        return RuleBuilder(name);
    }
    
    template<typename OutputType>
    std::shared_ptr<OutputType> parseSource(const std::string& source, ParserMode mode) {
        Scanner scanner(source);
        CSTParser parser(scanner);
        return parser.parseRule<OutputType>("program", mode);
    }
    
    PerformanceComparison benchmarkModes(const std::string& source) {
        PerformanceComparison comparison;
        
        Scanner scanner(source);
        CSTParser parser(scanner);
        
        // Benchmark DIRECT_AST mode
        auto start = std::chrono::high_resolution_clock::now();
        auto astResult = parser.parseRule<AST::Program>("program", ParserMode::DIRECT_AST);
        auto end = std::chrono::high_resolution_clock::now();
        comparison.directASTTime = std::chrono::duration<double, std::milli>(end - start).count();
        
        // Benchmark CST_THEN_AST mode
        start = std::chrono::high_resolution_clock::now();
        auto cstAstResult = parser.parseRule<AST::Program>("program", ParserMode::CST_THEN_AST);
        end = std::chrono::high_resolution_clock::now();
        comparison.cstThenASTTime = std::chrono::duration<double, std::milli>(end - start).count();
        
        // Benchmark CST_ONLY mode
        start = std::chrono::high_resolution_clock::now();
        auto cstResult = parser.parse(); // Use public parse method instead
        end = std::chrono::high_resolution_clock::now();
        comparison.cstOnlyTime = std::chrono::duration<double, std::milli>(end - start).count();
        
        comparison.tokensProcessed = parser.getTotalTokens();
        
        return comparison;
    }
    
    void PerformanceComparison::print() const {
        std::cout << "Performance Comparison:\n";
        std::cout << "  Direct AST:    " << directASTTime << " ms\n";
        std::cout << "  CST then AST:  " << cstThenASTTime << " ms\n";
        std::cout << "  CST only:      " << cstOnlyTime << " ms\n";
        std::cout << "  Tokens:        " << tokensProcessed << "\n";
        std::cout << "  Speedup:       " << getSpeedup() << "x\n";
    }
    
    bool validateUnifiedGrammar(const GrammarTable& grammar) {
        // Basic validation - check for circular dependencies, missing rules, etc.
        auto issues = findGrammarIssues(grammar);
        return issues.empty();
    }
    
    std::vector<std::string> findGrammarIssues(const GrammarTable& grammar) {
        std::vector<std::string> issues;
        
        // Check for missing rules referenced by other rules
        auto allRules = grammar.getAllRuleNames();
        std::unordered_set<std::string> ruleSet(allRules.begin(), allRules.end());
        
        for (const auto& ruleName : allRules) {
            auto rule = grammar.getRule(ruleName);
            if (rule) {
                for (const auto& dep : rule->dependencies) {
                    if (ruleSet.find(dep) == ruleSet.end()) {
                        issues.push_back("Rule '" + ruleName + "' depends on missing rule '" + dep + "'");
                    }
                }
            }
        }
        
        return issues;
    }

    // Template specializations
    
    template<>
    std::shared_ptr<AST::Program> CSTParser::parseRule<AST::Program>(const std::string& ruleName, ParserMode mode) {
        setParserMode(mode);
        ParseContext context(mode, this, tokens);
        auto result = executeRule(ruleName, context);
        
        if (result.success) {
            return result.getAST<AST::Program>();
        }
        return nullptr;
    }
    
    template<>
    std::shared_ptr<AST::Statement> CSTParser::parseRule<AST::Statement>(const std::string& ruleName, ParserMode mode) {
        setParserMode(mode);
        ParseContext context(mode, this, tokens);
        auto result = executeRule(ruleName, context);
        
        if (result.success) {
            return result.getAST<AST::Statement>();
        }
        return nullptr;
    }
    
    template<>
    std::shared_ptr<AST::Expression> CSTParser::parseRule<AST::Expression>(const std::string& ruleName, ParserMode mode) {
        setParserMode(mode);
        ParseContext context(mode, this, tokens);
        auto result = executeRule(ruleName, context);
        
        if (result.success) {
            return result.getAST<AST::Expression>();
        }
        return nullptr;
    }
    
    std::unique_ptr<Node> CSTParser::parseInterpolatedString() {
        // Handle interpolated strings properly
        // The scanner generates: STRING INTERPOLATION_START expression INTERPOLATION_END STRING ...
        auto node = createNode(NodeKind::INTERPOLATION_EXPR);
        
        // Add the initial string part (we've already confirmed it exists and consumed the STRING token)
        auto stringNode = createNode(NodeKind::LITERAL_EXPR);
        stringNode->addToken(previous()); // The STRING token that was consumed to get here
        node->addNode(std::move(stringNode));
        
        // Handle interpolation parts
        while (check(TokenType::INTERPOLATION_START)) {
            // Consume INTERPOLATION_START
            node->addToken(advance());
            
            // Parse expression inside interpolation
            auto expr = parseExpression();
            if (expr) {
                node->addNode(std::move(expr));
            }
            
            // Expect INTERPOLATION_END
            if (check(TokenType::INTERPOLATION_END)) {
                node->addToken(advance());
            } else {
                reportError("Expected '}' after interpolation expression", TokenType::INTERPOLATION_END, peek().type);
            }
            
            // Check if there's another string part after this interpolation
            if (check(TokenType::STRING)) {
                auto stringNode = createNode(NodeKind::LITERAL_EXPR);
                stringNode->addToken(advance());
                node->addNode(std::move(stringNode));
            }
        }
        
        return node;
    }
} // namespace CST