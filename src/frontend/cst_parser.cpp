#include "cst_parser.hh"
#include "../common/debugger.hh"
#include <stdexcept>
#include <limits>

// Helper methods
Token CSTParser::peek() {
    return scanner.getTokens()[current];
}

Token CSTParser::previous() {
    return scanner.getTokens()[current - 1];
}

Token CSTParser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool CSTParser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
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

bool CSTParser::isAtEnd() {
    return peek().type == TokenType::EOF_TOKEN;
}

Token CSTParser::consume(TokenType type, const std::string &message) {
    if (check(type)) return advance();
    error(message);
    throw std::runtime_error(message);
}

void CSTParser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON) return;

        switch (peek().type) {
            case TokenType::CLASS:
            case TokenType::FN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
            default:
                break;
        }

        advance();
    }
}

void CSTParser::error(const std::string &message, bool suppressException) {
    // Get the current token's lexeme for better error reporting
    std::string lexeme = "";
    int line = 0;
    int column = 0;
    std::string codeContext = "";
    
    if (current < scanner.getTokens().size()) {
        Token currentToken = peek();
        lexeme = currentToken.lexeme;
        line = currentToken.line;
        column = currentToken.start;
        // Extract code context (source line)
        if (line > 0) {
            const std::string& src = scanner.getSource();
            size_t srcLen = src.length();
            size_t lineStart = 0, lineEnd = srcLen;
            int curLine = 1;
            for (size_t i = 0; i < srcLen; ++i) {
                if (curLine == line) {
                    lineStart = i;
                    while (lineStart > 0 && src[lineStart - 1] != '\n') --lineStart;
                    lineEnd = i;
                    while (lineEnd < srcLen && src[lineEnd] != '\n') ++lineEnd;
                    codeContext = src.substr(lineStart, lineEnd - lineStart);
                    break;
                }
                if (src[i] == '\n') ++curLine;
            }
        }
    }
    
    // Check if this is an "Expected expression" error in a trait method
    if (message == "Expected expression." && 
        (current > 0 && current < scanner.getTokens().size() && 
         scanner.getTokens()[current-1].type == TokenType::LEFT_BRACE && 
         scanner.getTokens()[current].type == TokenType::RIGHT_BRACE)) {
        // Let the debugger handle this common case
        Debugger::error(message, line, column, InterpretationStage::PARSING, scanner.getSource(), scanner.getFilePath(), lexeme, codeContext);
        return;
    }
    
    // Check for block-related errors and add "Caused by" information
    std::string enhancedMessage = message;
    if ((message.find("Expected '}'") != std::string::npos || 
         message.find("Unexpected closing brace") != std::string::npos ||
         message.find("Expected '}' after") != std::string::npos) && 
        !blockStack.empty()) {
        
        // Find the most relevant block context (the most recent unclosed block)
        auto blockContext = getCurrentBlockContext();
        if (blockContext.has_value()) {
            std::string causedBy = generateCausedByMessage(blockContext.value());
            enhancedMessage += "\n" + causedBy;
        }
    }
    
    // Use enhanced error reporting with block context if available
    auto blockContext = getCurrentBlockContext();
    if (blockContext.has_value()) {
        Debugger::error(enhancedMessage, line, column, InterpretationStage::PARSING, scanner.getSource(), scanner.getFilePath(), blockContext, lexeme, codeContext);
    } else {
        Debugger::error(enhancedMessage, line, column, InterpretationStage::PARSING, scanner.getSource(), scanner.getFilePath(), lexeme, codeContext);
    }

    // Collect error for multi-error reporting
    errors.push_back(ParseError{enhancedMessage, line, column, codeContext});
    if (errors.size() >= MAX_ERRORS) {
        throw std::runtime_error("Too many syntax errors; aborting parse.");
    }

    // Do not throw for normal errors; let parser continue and synchronize.
}

// Unified node creation helper - creates CST::Node or AST::Node based on cstMode
template<typename ASTNodeType>
auto CSTParser::createNode() -> std::conditional_t<std::is_same_v<ASTNodeType, AST::Program>, 
                                                   std::shared_ptr<AST::Program>,
                                                   std::shared_ptr<ASTNodeType>> {
    if (cstMode) {
        // In CST mode, create CST::Node and return nullptr for AST (will be handled separately)
        // For now, we'll create both for compatibility
        auto astNode = std::make_shared<ASTNodeType>();
        
        // Map AST type to CST NodeKind
        CST::NodeKind cstKind = mapASTNodeKind(typeid(ASTNodeType).name());
        auto cstNode = std::make_unique<CST::Node>(cstKind);
        
        // Set position information
        if (current < scanner.getTokens().size()) {
            Token currentToken = peek();
            cstNode->startPos = currentToken.start;
            cstNode->endPos = currentToken.end;
        }
        
        // Store CST node for trivia attachment
        currentNode = std::move(cstNode);
        
        // Increment counter for testing
        cstNodeCount++;
        
        return astNode;
    } else {
        // Legacy AST mode - just create AST node
        return std::make_shared<ASTNodeType>();
    }
}

// AST to CST NodeKind mapping
CST::NodeKind CSTParser::mapASTNodeKind(const std::string& astNodeType) {
    // Extract class name from mangled type name
    std::string className = astNodeType;
    
    // Simple mapping based on common patterns
    if (className.find("Program") != std::string::npos) return CST::NodeKind::PROGRAM;
    if (className.find("VarDeclaration") != std::string::npos) return CST::NodeKind::VAR_DECLARATION;
    if (className.find("FunctionDeclaration") != std::string::npos) return CST::NodeKind::FUNCTION_DECLARATION;
    if (className.find("ClassDeclaration") != std::string::npos) return CST::NodeKind::CLASS_DECLARATION;
    if (className.find("EnumDeclaration") != std::string::npos) return CST::NodeKind::ENUM_DECLARATION;
    if (className.find("TypeDeclaration") != std::string::npos) return CST::NodeKind::TYPE_DECLARATION;
    if (className.find("TraitDeclaration") != std::string::npos) return CST::NodeKind::TRAIT_DECLARATION;
    if (className.find("InterfaceDeclaration") != std::string::npos) return CST::NodeKind::INTERFACE_DECLARATION;
    if (className.find("ModuleDeclaration") != std::string::npos) return CST::NodeKind::MODULE_DECLARATION;
    if (className.find("ImportStatement") != std::string::npos) return CST::NodeKind::IMPORT_DECLARATION;
    
    if (className.find("IfStatement") != std::string::npos) return CST::NodeKind::IF_STATEMENT;
    if (className.find("ForStatement") != std::string::npos) return CST::NodeKind::FOR_STATEMENT;
    if (className.find("WhileStatement") != std::string::npos) return CST::NodeKind::WHILE_STATEMENT;
    if (className.find("IterStatement") != std::string::npos) return CST::NodeKind::ITER_STATEMENT;
    if (className.find("MatchStatement") != std::string::npos) return CST::NodeKind::MATCH_STATEMENT;
    if (className.find("BlockStatement") != std::string::npos) return CST::NodeKind::BLOCK_STATEMENT;
    if (className.find("ExprStatement") != std::string::npos) return CST::NodeKind::EXPRESSION_STATEMENT;
    if (className.find("ReturnStatement") != std::string::npos) return CST::NodeKind::RETURN_STATEMENT;
    if (className.find("BreakStatement") != std::string::npos) return CST::NodeKind::BREAK_STATEMENT;
    if (className.find("ContinueStatement") != std::string::npos) return CST::NodeKind::CONTINUE_STATEMENT;
    if (className.find("PrintStatement") != std::string::npos) return CST::NodeKind::PRINT_STATEMENT;
    if (className.find("AttemptStatement") != std::string::npos) return CST::NodeKind::ATTEMPT_STATEMENT;
    if (className.find("ParallelStatement") != std::string::npos) return CST::NodeKind::PARALLEL_STATEMENT;
    if (className.find("ConcurrentStatement") != std::string::npos) return CST::NodeKind::CONCURRENT_STATEMENT;
    
    if (className.find("BinaryExpr") != std::string::npos) return CST::NodeKind::BINARY_EXPR;
    if (className.find("UnaryExpr") != std::string::npos) return CST::NodeKind::UNARY_EXPR;
    if (className.find("CallExpr") != std::string::npos) return CST::NodeKind::CALL_EXPR;
    if (className.find("MemberExpr") != std::string::npos) return CST::NodeKind::MEMBER_EXPR;
    if (className.find("IndexExpr") != std::string::npos) return CST::NodeKind::INDEX_EXPR;
    if (className.find("LiteralExpr") != std::string::npos) return CST::NodeKind::LITERAL_EXPR;
    if (className.find("ObjectLiteralExpr") != std::string::npos) return CST::NodeKind::OBJECT_LITERAL_EXPR;
    if (className.find("VariableExpr") != std::string::npos) return CST::NodeKind::VARIABLE_EXPR;
    if (className.find("GroupingExpr") != std::string::npos) return CST::NodeKind::GROUPING_EXPR;
    if (className.find("AssignExpr") != std::string::npos) return CST::NodeKind::ASSIGNMENT_EXPR;
    if (className.find("TernaryExpr") != std::string::npos) return CST::NodeKind::CONDITIONAL_EXPR;
    if (className.find("LambdaExpr") != std::string::npos) return CST::NodeKind::LAMBDA_EXPR;
    if (className.find("RangeExpr") != std::string::npos) return CST::NodeKind::RANGE_EXPR;
    if (className.find("InterpolatedStringExpr") != std::string::npos) return CST::NodeKind::INTERPOLATION_EXPR;
    
    // Default to error node if mapping not found
    return CST::NodeKind::ERROR_NODE;
}

// Token consumption with trivia tracking
Token CSTParser::consumeWithTrivia(TokenType type, const std::string &message) {
    Token token = consume(type, message);
    attachTriviaFromToken(token);
    return token;
}

Token CSTParser::advanceWithTrivia() {
    Token token = advance();
    attachTriviaFromToken(token);
    return token;
}

// Trivia attachment helpers
void CSTParser::attachTriviaFromToken(const Token& token) {
    if (cstMode && std::holds_alternative<std::unique_ptr<CST::Node>>(currentNode)) {
        auto& cstNode = std::get<std::unique_ptr<CST::Node>>(currentNode);
        if (cstNode) {
            // Add the token itself to the elements
            cstNode->addToken(token);
            
            // Extract and attach trivia from the token
            cstNode->attachTriviaFromToken(token);
            
            // Update trivia attachment count for statistics
            triviaAttachmentCount++;
        }
    }
}

void CSTParser::attachTriviaFromTokens(const std::vector<Token>& tokens) {
    if (cstMode && std::holds_alternative<std::unique_ptr<CST::Node>>(currentNode)) {
        auto& cstNode = std::get<std::unique_ptr<CST::Node>>(currentNode);
        if (cstNode) {
            for (const auto& token : tokens) {
                cstNode->addToken(token);
            }
        }
    }
}

// Explicit template instantiations for common AST node types
template auto CSTParser::createNode<AST::Program>() -> std::shared_ptr<AST::Program>;
template auto CSTParser::createNode<AST::VarDeclaration>() -> std::shared_ptr<AST::VarDeclaration>;
template auto CSTParser::createNode<AST::FunctionDeclaration>() -> std::shared_ptr<AST::FunctionDeclaration>;
template auto CSTParser::createNode<AST::ClassDeclaration>() -> std::shared_ptr<AST::ClassDeclaration>;
template auto CSTParser::createNode<AST::IfStatement>() -> std::shared_ptr<AST::IfStatement>;
template auto CSTParser::createNode<AST::ForStatement>() -> std::shared_ptr<AST::ForStatement>;
template auto CSTParser::createNode<AST::WhileStatement>() -> std::shared_ptr<AST::WhileStatement>;
template auto CSTParser::createNode<AST::BlockStatement>() -> std::shared_ptr<AST::BlockStatement>;
template auto CSTParser::createNode<AST::ExprStatement>() -> std::shared_ptr<AST::ExprStatement>;
template auto CSTParser::createNode<AST::ReturnStatement>() -> std::shared_ptr<AST::ReturnStatement>;
template auto CSTParser::createNode<AST::PrintStatement>() -> std::shared_ptr<AST::PrintStatement>;
template auto CSTParser::createNode<AST::BinaryExpr>() -> std::shared_ptr<AST::BinaryExpr>;
template auto CSTParser::createNode<AST::UnaryExpr>() -> std::shared_ptr<AST::UnaryExpr>;
template auto CSTParser::createNode<AST::LiteralExpr>() -> std::shared_ptr<AST::LiteralExpr>;
template auto CSTParser::createNode<AST::ObjectLiteralExpr>() -> std::shared_ptr<AST::ObjectLiteralExpr>;
template auto CSTParser::createNode<AST::VariableExpr>() -> std::shared_ptr<AST::VariableExpr>;
template auto CSTParser::createNode<AST::CallExpr>() -> std::shared_ptr<AST::CallExpr>;
template auto CSTParser::createNode<AST::AssignExpr>() -> std::shared_ptr<AST::AssignExpr>;

// Main parse method
std::shared_ptr<AST::Program> CSTParser::parse() {
    auto program = createNode<AST::Program>();
    program->line = 1;

    // If in CST mode, the createNode call above created the CST root
    if (cstMode && std::holds_alternative<std::unique_ptr<CST::Node>>(currentNode)) {
        // Move the current CST node to be our root
        cstRoot = std::move(std::get<std::unique_ptr<CST::Node>>(currentNode));
        cstRoot->setDescription("Program root node");
    }

    try {
        while (!isAtEnd()) {
            auto stmt = declaration();
            if (stmt) {
                program->statements.push_back(stmt);
                
                // In CST mode, the declaration() method will have created CST nodes
                // and they will be automatically attached to the tree structure
            }
        }
    } catch (const std::exception &e) {
        // Handle parsing errors
        synchronize();
        
        // Add error info to CST if in CST mode
        if (cstMode && cstRoot) {
            cstRoot->setError("Parse error: " + std::string(e.what()));
        }
    }

    // After parsing, print all collected errors if any
    if (!errors.empty()) {
        std::cerr << "\n--- Syntax Errors ---\n";
        for (const auto& err : errors) {
            std::cerr << "[Line " << err.line << ", Col " << err.column << "]: " << err.message << "\n";
            if (!err.codeContext.empty()) {
                std::cerr << "    " << err.codeContext << "\n";
            }
        }
        std::cerr << "---------------------\n";
        
        // Add errors to CST if in CST mode
        if (cstMode && cstRoot) {
            for (const auto& err : errors) {
                auto errorNode = std::make_unique<CST::ErrorNode>(err.message, 0, 0);
                cstRoot->addChild(std::move(errorNode));
            }
        }
    }
    
    return program;
}

// Parse declarations
// Helper to collect leading annotations
std::vector<Token> CSTParser::collectAnnotations() {
    std::vector<Token> annotations;
    while (check(TokenType::PUBLIC) || check(TokenType::PRIVATE) || check(TokenType::PROTECTED)) {
        annotations.push_back(advance());
    }
    return annotations;
}

std::shared_ptr<AST::Statement> CSTParser::declaration() {
    try {
        // Collect leading annotations
        std::vector<Token> annotations = collectAnnotations();
        if (match({TokenType::CLASS})) {
            auto decl = classDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::FN})) {
            auto decl = function("function");
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::ASYNC})) {
            consume(TokenType::FN, "Expected 'fn' after 'async'.");
            auto asyncFn = std::make_shared<AST::AsyncFunctionDeclaration>(*function("async function"));
            asyncFn->annotations = annotations;
            return asyncFn;
        }
        if (match({TokenType::VAR})) {
            auto decl = varDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::ENUM})) {
            auto decl = enumDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::IMPORT})) {
            auto decl = importStatement();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::TYPE})) {
            auto decl = typeDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::TRAIT})) {
            auto decl = traitDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::INTERFACE})) {
            auto decl = interfaceDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::MODULE})) {
            auto decl = moduleDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }

        auto stmt = statement();
        if (stmt) stmt->annotations = annotations;
        return stmt;
    } catch (const std::exception &e) {
        synchronize();
        return nullptr;
    }
}

std::shared_ptr<AST::Statement> CSTParser::varDeclaration() {
    auto var = createNode<AST::VarDeclaration>();
    var->line = previous().line;
    
    // Store the current CST node for this variable declaration
    std::unique_ptr<CST::Node> varCSTNode;
    if (cstMode && std::holds_alternative<std::unique_ptr<CST::Node>>(currentNode)) {
        varCSTNode = std::move(std::get<std::unique_ptr<CST::Node>>(currentNode));
        varCSTNode->setDescription("var declaration");
    }

    // Add 'var' keyword token to CST with its trivia
    Token varToken = previous();
    if (cstMode && varCSTNode) {
        // Add leading trivia (comments, whitespace before 'var')
        for (const auto& trivia : varToken.getLeadingTrivia()) {
            if (trivia.type == TokenType::COMMENT_LINE || trivia.type == TokenType::COMMENT_BLOCK) {
                auto commentNode = std::make_unique<CST::CommentNode>(trivia);
                varCSTNode->addChild(std::move(commentNode));
            } else if (trivia.type == TokenType::WHITESPACE || trivia.type == TokenType::NEWLINE) {
                auto whitespaceNode = std::make_unique<CST::WhitespaceNode>(trivia);
                varCSTNode->addChild(std::move(whitespaceNode));
            }
        }
        
        // Add the 'var' keyword as a direct token (not wrapped in a node)
        varCSTNode->addToken(varToken);
    }

    // Parse variable name with semantic structure
    Token name = consumeWithTrivia(TokenType::IDENTIFIER, "Expected variable name.");
    var->name = name.lexeme;
    
    // Create IDENTIFIER semantic node
    if (cstMode && varCSTNode) {
        auto identifierNode = std::make_unique<CST::Node>(CST::NodeKind::IDENTIFIER, name.start, name.end);
        
        // Add any trivia before the identifier
        for (const auto& trivia : name.getLeadingTrivia()) {
            if (trivia.type == TokenType::WHITESPACE || trivia.type == TokenType::NEWLINE) {
                auto whitespaceNode = std::make_unique<CST::WhitespaceNode>(trivia);
                varCSTNode->addChild(std::move(whitespaceNode));
            }
        }
        
        // Add the identifier token to the IDENTIFIER node
        identifierNode->addToken(name);
        varCSTNode->addChild(std::move(identifierNode));
    }

    // Parse optional type annotation with semantic structure
    if (match({TokenType::COLON})) {
        Token colon = previous();
        
        if (cstMode && varCSTNode) {
            // Create TYPE_ANNOTATION semantic node
            auto typeAnnotationNode = std::make_unique<CST::Node>(CST::NodeKind::ANNOTATION, colon.start, 0);
            
            // Add colon token directly to TYPE_ANNOTATION
            typeAnnotationNode->addToken(colon);
            
            var->type = parseTypeAnnotation();
            
            // Add the actual type token to TYPE_ANNOTATION
            Token typeToken = previous(); // The type token (int, str, etc.)
            
            // Create PRIMITIVE_TYPE semantic node
            auto primitiveTypeNode = std::make_unique<CST::Node>(CST::NodeKind::PRIMITIVE_TYPE, typeToken.start, typeToken.end);
            primitiveTypeNode->addToken(typeToken);
            
            typeAnnotationNode->addChild(std::move(primitiveTypeNode));
            typeAnnotationNode->endPos = typeToken.end;
            
            varCSTNode->addChild(std::move(typeAnnotationNode));
        } else {
            var->type = parseTypeAnnotation();
        }
    }

    // Parse optional initializer with semantic structure
    if (match({TokenType::EQUAL})) {
        Token equal = previous();
        
        if (cstMode && varCSTNode) {
            // Create ASSIGNMENT semantic node
            auto assignmentNode = std::make_unique<CST::Node>(CST::NodeKind::ASSIGNMENT_EXPR, equal.start, 0);
            
            // Add = token directly to ASSIGNMENT
            assignmentNode->addToken(equal);
            
            var->initializer = expression();
            
            // Add the actual value token to ASSIGNMENT
            Token valueToken = previous(); // The value token (42, "hello", etc.)
            
            // Create LITERAL semantic node
            auto literalNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR, valueToken.start, valueToken.end);
            literalNode->addToken(valueToken);
            
            assignmentNode->addChild(std::move(literalNode));
            assignmentNode->endPos = valueToken.end;
            
            varCSTNode->addChild(std::move(assignmentNode));
        } else {
            var->initializer = expression();
        }
    }

    // Make semicolon optional
    if (match({TokenType::SEMICOLON})) {
        Token semicolon = previous();
        if (cstMode && varCSTNode) {
            varCSTNode->addToken(semicolon);
        }
    }
    
    // Add this variable declaration to the program root
    if (cstMode && cstRoot && varCSTNode) {
        cstRoot->addChild(std::move(varCSTNode));
    }
    
    return var;
}

std::shared_ptr<AST::Statement> CSTParser::statement() {
    if (match({TokenType::PRINT})) {
        return printStatement();
    }
    if (match({TokenType::IF})) {
        return ifStatement();
    }
    if (match({TokenType::FOR})) {
        return forStatement();
    }
    if (match({TokenType::WHILE})) {
        return whileStatement();
    }
    if (match({TokenType::BREAK})) {
        return breakStatement();
    }
    if (match({TokenType::CONTINUE})) {
        return continueStatement();
    }
    if (match({TokenType::ITER})) {
        return iterStatement();
    }
    if (match({TokenType::LEFT_BRACE})) {
        return block();
    }
    if (match({TokenType::RETURN})) {
        return returnStatement();
    }
    if (match({TokenType::PARALLEL})) {
        return parallelStatement();
    }
    if (match({TokenType::CONCURRENT})) {
        return concurrentStatement();
    }
    if (match({TokenType::MATCH})) {
        return matchStatement();
    }
    if (match({TokenType::UNSAFE})) {
        return unsafeBlock();
    }
    if (match({TokenType::CONTRACT})) {
        return contractStatement();
    }
    if (match({TokenType::COMPTIME})) {
        return comptimeStatement();
    }

    return expressionStatement();
}

std::shared_ptr<AST::Statement> CSTParser::expressionStatement() {
    try {
        auto expr = expression();
        // Make semicolon optional
        match({TokenType::SEMICOLON});

        auto stmt = std::make_shared<AST::ExprStatement>();
        stmt->line = expr->line;
        stmt->expression = expr;
        return stmt;
    } catch (const std::exception &e) {
        // If we can't parse an expression, return an empty statement
        auto stmt = std::make_shared<AST::ExprStatement>();
        stmt->line = peek().line;
        stmt->expression = nullptr;
        return stmt;
    }
}

std::shared_ptr<AST::Statement> CSTParser::printStatement() {
    auto stmt = createNode<AST::PrintStatement>();
    stmt->line = previous().line;

    attachTriviaFromToken(previous());

    // Parse arguments
    consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'print'.");

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            stmt->arguments.push_back(expression());
            if (match({TokenType::COMMA})) {
                attachTriviaFromToken(previous());
            }
        } while (previous().type == TokenType::COMMA);
    }

    consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after print arguments.");
    
    // Make semicolon optional
    if (match({TokenType::SEMICOLON})) {
        attachTriviaFromToken(previous());
    }
    
    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::taskStatement() {
    auto stmt = std::make_shared<AST::TaskStatement>();
    stmt->line = peek().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'task'.");
    
    // Parse loop variable if present
    if (check(TokenType::IDENTIFIER)) {
        stmt->loopVar = consume(TokenType::IDENTIFIER, "Expected loop variable name.").lexeme;
        consume(TokenType::IN, "Expected 'in' after loop variable.");
    }
    
    // Parse the iterable expression (could be a range, list, etc.)
    stmt->iterable = expression();
    
    consume(TokenType::RIGHT_PAREN, "Expected ')' after task arguments.");

    // Parse the task body
    consume(TokenType::LEFT_BRACE, "Expected '{' before task body.");
    stmt->body = block();

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::workerStatement() {
    auto stmt = std::make_shared<AST::WorkerStatement>();
    stmt->line = peek().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'worker'.");
    if (check(TokenType::RIGHT_PAREN)) {
        // No parameter
    } else {
        stmt->param = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
    }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after worker arguments.");

    consume(TokenType::LEFT_BRACE, "Expected '{' before worker body.");
    stmt->body = block();

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::traitDeclaration() {
    // Create a new trait declaration statement
    auto traitDecl = std::make_shared<AST::TraitDeclaration>();
    traitDecl->line = previous().line;

    // Check for @open annotation
    if (match({TokenType::OPEN})) {
        traitDecl->isOpen = true;
    }

    // Parse trait name
    Token name = consume(TokenType::IDENTIFIER, "Expected trait name.");
    traitDecl->name = name.lexeme;

    // Parse trait body
    consume(TokenType::LEFT_BRACE, "Expected '{' before trait body.");

    // Parse trait methods
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FN})) {
            // For traits, we need to handle method declarations that might not have bodies
            auto method = std::make_shared<AST::FunctionDeclaration>();
            method->line = previous().line;
            
            // Parse function name
            Token name = consume(TokenType::IDENTIFIER, "Expected method name.");
            method->name = name.lexeme;
            
            consume(TokenType::LEFT_PAREN, "Expected '(' after method name.");
            
            // Parse parameters
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                    
                    // Parse parameter type
                    consume(TokenType::COLON, "Expected ':' after parameter name.");
                    auto paramType = parseTypeAnnotation();
                    
                    method->params.push_back({paramName, paramType});
                } while (match({TokenType::COMMA}));
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");
            
            // Parse return type
            if (match({TokenType::COLON})) {
                method->returnType = parseTypeAnnotation();
            }
            
            // Check if there's a semicolon (no body) or a brace (with body)
            if (match({TokenType::SEMICOLON})) {
                // Method declaration without body (interface/trait style)
                method->body = std::make_shared<AST::BlockStatement>();
                method->body->line = method->line;
            } else {
                // Method with body
                consume(TokenType::LEFT_BRACE, "Expected '{' or ';' after method declaration.");
                method->body = block();
            }
            
            traitDecl->methods.push_back(method);
        } else {
            error("Expected method declaration in trait.");
            // Create a placeholder expression to allow parsing to continue
            auto errorExpr = std::make_shared<AST::LiteralExpr>();
            errorExpr->line = peek().line;
            errorExpr->value = nullptr; // Use null as a placeholder
            // return errorExpr;
           break;
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after trait body.");

    return traitDecl;
}

std::shared_ptr<AST::Statement> CSTParser::interfaceDeclaration() {
    // Create a new interface declaration statement
    auto interfaceDecl = std::make_shared<AST::InterfaceDeclaration>();
    interfaceDecl->line = previous().line;

    // Check for @open annotation
    if (match({TokenType::AT_SIGN})) {
        Token annotation = consume(TokenType::IDENTIFIER, "Expected annotation name after '@'.");
        if (annotation.lexeme == "open") {
            interfaceDecl->isOpen = true;
        }
    }

    // Parse interface name
    Token name = consume(TokenType::IDENTIFIER, "Expected interface name.");
    interfaceDecl->name = name.lexeme;

    // Parse interface body
    consume(TokenType::LEFT_BRACE, "Expected '{' before interface body.");

    // Parse interface methods
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FN})) {
            auto method = function("method");
            interfaceDecl->methods.push_back(method);
        } else {
            error("Expected method declaration in interface.");
            break;
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after interface body.");

    return interfaceDecl;
}

std::shared_ptr<AST::Statement> CSTParser::moduleDeclaration() {
    // Create a new module declaration statement
    auto moduleDecl = std::make_shared<AST::ModuleDeclaration>();
    moduleDecl->line = previous().line;

    // Parse module name
    Token name = consume(TokenType::IDENTIFIER, "Expected module name.");
    moduleDecl->name = name.lexeme;

    // Parse module body
    consume(TokenType::LEFT_BRACE, "Expected '{' before module body.");

    // Parse module members
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // Check for visibility annotations
        bool isPublic = false;
        bool isProtected = false;

        if (match({TokenType::AT_SIGN})) {
            Token annotation = consume(TokenType::IDENTIFIER, "Expected annotation name after '@'.");
            if (annotation.lexeme == "public") {
                isPublic = true;
            } else if (annotation.lexeme == "protected") {
                isProtected = true;
            }
        }

        // Parse module member
        auto member = declaration();
        if (member) {
            if (isPublic) {
                moduleDecl->publicMembers.push_back(member);
            } else if (isProtected) {
                moduleDecl->protectedMembers.push_back(member);
            } else {
                moduleDecl->privateMembers.push_back(member);
            }
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after module body.");

    return moduleDecl;
}

std::shared_ptr<AST::Statement> CSTParser::iterStatement() {
    auto stmt = std::make_shared<AST::IterStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'iter'.");

    // Parse loop variables
    if (match({TokenType::VAR})) {
        // Variable declaration in loop
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
        stmt->loopVars.push_back(name.lexeme);

        // Check for multiple variables (key, value)
        if (match({TokenType::COMMA})) {
            Token secondVar = consume(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);
        }

        consume(TokenType::IN, "Expected 'in' after loop variables.");
        stmt->iterable = expression();
    } else if (match({TokenType::IDENTIFIER})) {
        // Identifier directly
        std::string firstVar = previous().lexeme;
        stmt->loopVars.push_back(firstVar);

        // Check for multiple variables (key, value)
        if (match({TokenType::COMMA})) {
            Token secondVar = consume(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);

            consume(TokenType::IN, "Expected 'in' after loop variables.");
            stmt->iterable = expression();
        } else if (match({TokenType::IN})) {
            stmt->iterable = expression();
        } else {
            error("Expected 'in' after loop variable.");
        }
    } else {
        error("Expected variable name or identifier after 'iter ('.");
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after iter clauses.");

    // Parse loop body
    stmt->body = statement();

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::breakStatement() {
    auto stmt = std::make_shared<AST::BreakStatement>();
    stmt->line = previous().line;
    consume(TokenType::SEMICOLON, "Expected ';' after 'break'.");
    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::continueStatement() {
    auto stmt = std::make_shared<AST::ContinueStatement>();
    stmt->line = previous().line;
    consume(TokenType::SEMICOLON, "Expected ';' after 'continue'.");
    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::unsafeBlock() {
    auto stmt = std::make_shared<AST::UnsafeStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_BRACE, "Expected '{' after 'unsafe'.");
    stmt->body = block();

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::contractStatement() {
    auto stmt = std::make_shared<AST::ContractStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'contract'.");
    stmt->condition = expression();

    if (match({TokenType::COMMA})) {
        // Parse error message
        if (match({TokenType::STRING})) {
            auto literalExpr = std::make_shared<AST::LiteralExpr>();
            literalExpr->line = previous().line;
            literalExpr->value = previous().lexeme;
            stmt->message = literalExpr;
        } else {
            stmt->message = expression();
        }
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after contract condition.");
    consume(TokenType::SEMICOLON, "Expected ';' after contract statement.");

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::comptimeStatement() {
    auto stmt = std::make_shared<AST::ComptimeStatement>();
    stmt->line = previous().line;

    // Parse the declaration that should be evaluated at compile time
    stmt->declaration = declaration();

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::ifStatement() {
    auto stmt = createNode<AST::IfStatement>();
    Token ifToken = previous();
    stmt->line = ifToken.line;

    attachTriviaFromToken(ifToken);

    consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
    stmt->condition = expression();
    consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after if condition.");

    stmt->thenBranch = parseStatementWithContext("if", ifToken);

    // Handle elif chains
    while (match({TokenType::ELIF})) {
        Token elifToken = previous();
        attachTriviaFromToken(elifToken);
        
        // Create a nested if statement for the elif
        auto elifStmt = createNode<AST::IfStatement>();
        elifStmt->line = elifToken.line;
        
        consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'elif'.");
        elifStmt->condition = expression();
        consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after elif condition.");
        
        elifStmt->thenBranch = parseStatementWithContext("elif", elifToken);
        
        // Chain the elif as the else branch of the previous statement
        if (!stmt->elseBranch) {
            stmt->elseBranch = elifStmt;
        } else {
            // Find the last elif in the chain and attach this one
            auto current = std::dynamic_pointer_cast<AST::IfStatement>(stmt->elseBranch);
            while (current && current->elseBranch && 
                   std::dynamic_pointer_cast<AST::IfStatement>(current->elseBranch)) {
                current = std::dynamic_pointer_cast<AST::IfStatement>(current->elseBranch);
            }
            if (current) {
                current->elseBranch = elifStmt;
            }
        }
    }

    if (match({TokenType::ELSE})) {
        Token elseToken = previous();
        attachTriviaFromToken(elseToken);
        
        auto elseStmt = parseStatementWithContext("else", elseToken);
        
        // Attach else to the end of the elif chain
        if (!stmt->elseBranch) {
            stmt->elseBranch = elseStmt;
        } else {
            // Find the last elif in the chain and attach the else
            auto current = std::dynamic_pointer_cast<AST::IfStatement>(stmt->elseBranch);
            while (current && current->elseBranch && 
                   std::dynamic_pointer_cast<AST::IfStatement>(current->elseBranch)) {
                current = std::dynamic_pointer_cast<AST::IfStatement>(current->elseBranch);
            }
            if (current) {
                current->elseBranch = elseStmt;
            }
        }
    }

    return stmt;
}

std::shared_ptr<AST::BlockStatement> CSTParser::block() {
    auto block = std::make_shared<AST::BlockStatement>();
    Token leftBrace = previous();
    block->line = leftBrace.line;

    // Handle empty blocks
    if (check(TokenType::RIGHT_BRACE)) {
        consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
        return block;
    }

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        try {
            if (in_concurrent_block) {
                bool is_async = match({TokenType::ASYNC});
                if (peek().type == TokenType::IDENTIFIER) {
                    if (peek().lexeme == "task") {
                        advance(); // consume 'task'
                        auto stmt = taskStatement();
                        auto task_stmt = std::dynamic_pointer_cast<AST::TaskStatement>(stmt);
                        if (task_stmt) task_stmt->isAsync = is_async;
                        block->statements.push_back(stmt);
                        continue;
                    }
                    if (peek().lexeme == "worker") {
                        advance(); // consume 'worker'
                        auto stmt = workerStatement();
                        auto worker_stmt = std::dynamic_pointer_cast<AST::WorkerStatement>(stmt);
                        if (worker_stmt) worker_stmt->isAsync = is_async;
                        block->statements.push_back(stmt);
                        continue;
                    }
                }
                if (is_async) {
                    // if we matched 'async' but not 'task' or 'worker', it's an error.
                    error("Expected 'task' or 'worker' after 'async' in this context.");
                }
            }
            // Try to parse a declaration
            auto declaration = this->declaration();
            if (declaration) {
                block->statements.push_back(declaration);
            }
        } catch (const std::exception &e) {
            // Skip invalid statements and continue parsing
            synchronize();
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
    return block;
}

std::shared_ptr<AST::Statement> CSTParser::forStatement() {
    auto stmt = std::make_shared<AST::ForStatement>();
    Token forToken = previous();
    stmt->line = forToken.line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'for'.");

    // Check for the type of for loop
    if (match({TokenType::VAR})) {
        // Could be either traditional or iterable loop
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");

        if (match({TokenType::IN})) {
            // Iterable loop: for (var i in range(10))
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(name.lexeme);
            stmt->iterable = expression();
        } else {
            // Traditional loop: for (var i = 0; i < 5; i++)
            auto initializer = std::make_shared<AST::VarDeclaration>();
            initializer->line = name.line;
            initializer->name = name.lexeme;

            // Parse optional type annotation
            if (match({TokenType::COLON})) {
                initializer->type = parseTypeAnnotation();
            }

            // Parse initializer
            if (match({TokenType::EQUAL})) {
                initializer->initializer = expression();
            }

            stmt->initializer = initializer;

            consume(TokenType::SEMICOLON, "Expected ';' after loop initializer.");

            // Parse condition
            if (!check(TokenType::SEMICOLON)) {
                stmt->condition = expression();
            }

            consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

            // Parse increment
            if (!check(TokenType::RIGHT_PAREN)) {
                stmt->increment = expression();
            }
        }
    } else if (match({TokenType::IDENTIFIER})) {
        // Check if it's an iterable loop with multiple variables
        std::string firstVar = previous().lexeme;

        if (match({TokenType::COMMA})) {
            // Multiple variables: for (key, value in dict)
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(firstVar);

            Token secondVar = consume(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);

            consume(TokenType::IN, "Expected 'in' after loop variables.");
            stmt->iterable = expression();
        } else if (match({TokenType::IN})) {
            // Single variable: for (key in list)
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(firstVar);
            stmt->iterable = expression();
        } else {
            // Traditional loop with an expression as initializer
            current--; // Rewind to re-parse the identifier
            stmt->initializer = expressionStatement();

            // Parse condition
            if (!check(TokenType::SEMICOLON)) {
                stmt->condition = expression();
            }

            consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

            // Parse increment
            if (!check(TokenType::RIGHT_PAREN)) {
                stmt->increment = expression();
            }
        }
    } else if (!match({TokenType::SEMICOLON})) {
        // Traditional loop with an expression as initializer
        stmt->initializer = expressionStatement();

        // Parse condition
        if (!check(TokenType::SEMICOLON)) {
            stmt->condition = expression();
        }

        consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

        // Parse increment
        if (!check(TokenType::RIGHT_PAREN)) {
            stmt->increment = expression();
        }
    } else {
        // Traditional loop with no initializer
        // Parse condition
        if (!check(TokenType::SEMICOLON)) {
            stmt->condition = expression();
        }

        consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

        // Parse increment
        if (!check(TokenType::RIGHT_PAREN)) {
            stmt->increment = expression();
        }
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after for clauses.");
    
    stmt->body = parseStatementWithContext("for", forToken);

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::whileStatement() {
    auto stmt = std::make_shared<AST::WhileStatement>();
    Token whileToken = previous();
    stmt->line = whileToken.line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'while'.");
    stmt->condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after while condition.");

    stmt->body = parseStatementWithContext("while", whileToken);

    return stmt;
}

std::shared_ptr<AST::FunctionDeclaration> CSTParser::function(const std::string& kind) {
    auto func = createNode<AST::FunctionDeclaration>();
    func->line = previous().line;
    
    attachTriviaFromToken(previous());

    // Parse function name
    Token name = consume(TokenType::IDENTIFIER, "Expected " + kind + " name.");
    func->name = name.lexeme;

    // Check for generic parameters
    if (match({TokenType::LEFT_BRACKET})) {
        do {
            func->genericParams.push_back(consume(TokenType::IDENTIFIER, "Expected generic parameter name.").lexeme);
        } while (match({TokenType::COMMA}));

        consume(TokenType::RIGHT_BRACKET, "Expected ']' after generic parameters.");
    }

    consume(TokenType::LEFT_PAREN, "Expected '(' after " + kind + " name.");

    // Parse parameters
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;

            // Parse optional parameter type
            std::shared_ptr<AST::TypeAnnotation> paramType = nullptr;
            if (match({TokenType::COLON})) {
                paramType = parseTypeAnnotation();
            }

            // Check if parameter has a default value (making it optional)
            if (match({TokenType::EQUAL})) {
                // This is an optional parameter with a default value
                std::shared_ptr<AST::Expression> defaultValue = expression();
                func->optionalParams.push_back({paramName, {paramType, defaultValue}});
            } else if (paramType && paramType->isOptional) {
                // This is an optional parameter with nullable type (no default value)
                func->optionalParams.push_back({paramName, {paramType, nullptr}});
            } else {
                // This is a required parameter
                func->params.push_back({paramName, paramType});
            }
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");

    // Parse return type
    if (match({TokenType::COLON})) {
        func->returnType = parseTypeAnnotation();
        
        // Extract error type information from return type annotation
        if (func->returnType && (*func->returnType)->isFallible) {
            func->canFail = true;
            func->declaredErrorTypes = (*func->returnType)->errorTypes;
        }
    }

    // Check if function throws and parse error types (legacy syntax)
    if (match({TokenType::THROWS})) {
        func->throws = true;
        func->canFail = true;
        
        // Parse specific error types if provided
        if (!check(TokenType::LEFT_BRACE)) {
            do {
                Token errorType = consume(TokenType::IDENTIFIER, "Expected error type name after 'throws'.");
                func->declaredErrorTypes.push_back(errorType.lexeme);
            } while (match({TokenType::COMMA}));
        }
    }

    // Parse function body
    Token leftBrace = consume(TokenType::LEFT_BRACE, "Expected '{' before " + kind + " body.");
    pushBlockContext("function", leftBrace);
    func->body = block();
    popBlockContext();

    return func;
}

std::shared_ptr<AST::Statement> CSTParser::returnStatement() {
    auto stmt = std::make_shared<AST::ReturnStatement>();
    stmt->line = previous().line;

    if (!check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE)) {
        stmt->value = expression();
    }

    // Make semicolon optional
    match({TokenType::SEMICOLON});

    return stmt;
}

std::shared_ptr<AST::ClassDeclaration> CSTParser::classDeclaration() {
    auto classDecl = std::make_shared<AST::ClassDeclaration>();
    classDecl->line = previous().line;

    // Parse class name
    Token name = consume(TokenType::IDENTIFIER, "Expected class name.");
    classDecl->name = name.lexeme;

    // Check for inline constructor parameters
    if (check(TokenType::LEFT_PAREN)) {
        classDecl->hasInlineConstructor = true;
        advance(); // consume '('
        
        // Parse constructor parameters
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                consume(TokenType::COLON, "Expected ':' after parameter name.");
                auto paramType = parseTypeAnnotation();
                classDecl->constructorParams.push_back({paramName, paramType});
            } while (match({TokenType::COMMA}));
        }
        
        consume(TokenType::RIGHT_PAREN, "Expected ')' after constructor parameters.");
    }

    // Check for inheritance
    if (match({TokenType::COLON})) {
        // Parse superclass name
        Token superName = consume(TokenType::IDENTIFIER, "Expected superclass name.");
        classDecl->superClassName = superName.lexeme;
        
        // Check for super constructor call
        if (check(TokenType::LEFT_PAREN)) {
            advance(); // consume '('
            
            // Parse super constructor arguments
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    classDecl->superConstructorArgs.push_back(expression());
                } while (match({TokenType::COMMA}));
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')' after super constructor arguments.");
        }
    }

    Token leftBrace = consume(TokenType::LEFT_BRACE, "Expected '{' before class body.");
    pushBlockContext("class", leftBrace);

    // Parse class members
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::VAR})) {
            // Parse field
            auto field = std::dynamic_pointer_cast<AST::VarDeclaration>(varDeclaration());
            if (field) {
                classDecl->fields.push_back(field);
            }
        } else if (match({TokenType::FN})) {
            // Parse method
            auto method = function("method");
            if (method) {
                classDecl->methods.push_back(method);
            }
        } else if (check(TokenType::IDENTIFIER) && peek().lexeme == classDecl->name) {
            // Parse constructor
            advance(); // Consume the class name
            auto constructor = std::make_shared<AST::FunctionDeclaration>();
            constructor->line = previous().line;
            constructor->name = classDecl->name;
            
            consume(TokenType::LEFT_PAREN, "Expected '(' after constructor name.");
            
            // Parse parameters
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                    
                    // Parse parameter type
                    consume(TokenType::COLON, "Expected ':' after parameter name.");
                    auto paramType = parseTypeAnnotation();
                    
                    constructor->params.push_back({paramName, paramType});
                } while (match({TokenType::COMMA}));
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");
            
            // Parse constructor body
            consume(TokenType::LEFT_BRACE, "Expected '{' before constructor body.");
            constructor->body = block();
            
            classDecl->methods.push_back(constructor);
        } else {
            error("Expected class member declaration.");
            break;
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after class body.");
    popBlockContext();

    // Generate automatic init constructor if class has inline constructor parameters
    if (classDecl->hasInlineConstructor) {
        auto initMethod = std::make_shared<AST::FunctionDeclaration>();
        initMethod->line = classDecl->line;
        initMethod->name = "init";
        
        // Copy constructor parameters to init method
        for (const auto& param : classDecl->constructorParams) {
            initMethod->params.push_back(param);
        }
        
        // Create constructor body
        auto body = std::make_shared<AST::BlockStatement>();
        body->line = classDecl->line;
        
        // Add super constructor call if there's inheritance
        if (!classDecl->superClassName.empty()) {
            // Create super.init() call
            auto superCall = std::make_shared<AST::ExprStatement>();
            superCall->line = classDecl->line;
            
            auto callExpr = std::make_shared<AST::CallExpr>();
            callExpr->line = classDecl->line;
            
            // Create super.init member expression
            auto memberExpr = std::make_shared<AST::MemberExpr>();
            memberExpr->line = classDecl->line;
            memberExpr->name = "init";
            
            auto superExpr = std::make_shared<AST::VariableExpr>();
            superExpr->line = classDecl->line;
            superExpr->name = "super";
            memberExpr->object = superExpr;
            
            callExpr->callee = memberExpr;
            
            // Add super constructor arguments
            for (const auto& arg : classDecl->superConstructorArgs) {
                callExpr->arguments.push_back(arg);
            }
            
            superCall->expression = callExpr;
            body->statements.push_back(superCall);
        }
        
        // Add automatic field assignments for constructor parameters
        for (const auto& param : classDecl->constructorParams) {
            auto assignment = std::make_shared<AST::ExprStatement>();
            assignment->line = classDecl->line;
            
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = classDecl->line;
            assignExpr->op = TokenType::EQUAL;
            
            // Create self.paramName member expression
            auto memberExpr = std::make_shared<AST::MemberExpr>();
            memberExpr->line = classDecl->line;
            memberExpr->name = param.first;
            
            auto thisExpr = std::make_shared<AST::ThisExpr>();
            thisExpr->line = classDecl->line;
            memberExpr->object = thisExpr;
            
            assignExpr->object = memberExpr;
            assignExpr->member = param.first;
            
            // Create parameter variable expression
            auto paramExpr = std::make_shared<AST::VariableExpr>();
            paramExpr->line = classDecl->line;
            paramExpr->name = param.first;
            
            assignExpr->value = paramExpr;
            assignment->expression = assignExpr;
            body->statements.push_back(assignment);
        }
        
        initMethod->body = body;
        classDecl->methods.push_back(initMethod);
    }

    return classDecl;
}

std::shared_ptr<AST::Statement> CSTParser::attemptStatement() {
    auto stmt = std::make_shared<AST::AttemptStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_BRACE, "Expected '{' after 'attempt'.");
    stmt->tryBlock = block();

    // Parse handlers
    while (match({TokenType::HANDLE})) {
        AST::HandleClause handler;

        // Parse error type
        handler.errorType = consume(TokenType::IDENTIFIER, "Expected error type after 'handle'.").lexeme;

        // Parse optional error variable
        if (match({TokenType::LEFT_PAREN})) {
            handler.errorVar = consume(TokenType::IDENTIFIER, "Expected error variable name.").lexeme;
            consume(TokenType::RIGHT_PAREN, "Expected ')' after error variable.");
        }

        // Parse handler body
        consume(TokenType::LEFT_BRACE, "Expected '{' after handle clause.");
        handler.body = block();

        stmt->handlers.push_back(handler);
    }

    return stmt;
}

void CSTParser::parseConcurrencyParams(
    std::string& channel,
    std::string& mode,
    std::string& cores,
    std::string& onError,
    std::string& timeout,
    std::string& grace,
    std::string& onTimeout
) {
    if (match({TokenType::LEFT_PAREN})) {
        while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
            // Parse parameter name
            std::string paramName = consume(TokenType::IDENTIFIER, "Expected parameter name").lexeme;
            
            // Check if this is type annotation (param: Type) or assignment (param = value)
            if (match({TokenType::COLON})) {
                // Type annotation syntax: param: Type
                // For now, we'll skip the type and treat it as a parameter with the type name as value
                std::string typeName = consume(TokenType::IDENTIFIER, "Expected type name after ':'").lexeme;
                // Store the type name as the parameter value for now
                if (paramName == "events") {
                    // This is a special case for event type annotation
                    // We can ignore it for now or store it for later use
                }
                // Continue to next parameter
                if (!match({TokenType::COMMA}) && !check(TokenType::RIGHT_PAREN)) {
                    error("Expected ',' or ')' after type annotation");
                    break;
                }
                continue;
            } else if (match({TokenType::EQUAL})) {
                // Assignment syntax: param = value
                // Continue with existing logic
            } else {
                error("Expected '=' or ':' after parameter name");
                break;
            }
            
            // Parse parameter value
            std::string paramValue;
            if (check(TokenType::STRING)) {
                paramValue = consume(TokenType::STRING, "Expected string value").lexeme;
                // Remove quotes
                if (paramValue.size() >= 2) {
                    paramValue = paramValue.substr(1, paramValue.size() - 2);
                }
            } else if (check(TokenType::NUMBER)) {
                // Get the number value
                paramValue = consume(TokenType::NUMBER, "Expected number value").lexeme;
                
                // Check for time unit (s, ms, etc.)
                if (check(TokenType::IDENTIFIER)) {
                    std::string unit = peek().lexeme;
                    if (unit == "s" || unit == "ms" || unit == "us" || unit == "ns") {
                        advance();  // Consume the unit
                        paramValue += unit;
                    }
                }
            } else if (check(TokenType::IDENTIFIER)) {
                paramValue = consume(TokenType::IDENTIFIER, "Expected identifier").lexeme;
            } else {
                error("Expected string, number, or identifier as parameter value");
                break;
            }

            // Assign parameter value to the appropriate field
            if (paramName == "ch") {
                channel = paramValue;
            } else if (paramName == "mode") {
                mode = paramValue;
            } else if (paramName == "cores") {
                cores = paramValue;
            } else if (paramName == "on_error") {
                onError = paramValue;
            } else if (paramName == "timeout") {
                timeout = paramValue;
            } else if (paramName == "grace") {
                grace = paramValue;
            } else if (paramName == "on_timeout") {
                onTimeout = paramValue;
            } else {
                error("Unknown parameter: " + paramName);
            }

            // Check for comma or end of parameters
            if (!match({TokenType::COMMA}) && !check(TokenType::RIGHT_PAREN)) {
                error("Expected ',' or ')' after parameter");
                break;
            }
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters");
    }
}

std::shared_ptr<AST::Statement> CSTParser::parallelStatement() {
    auto stmt = std::make_shared<AST::ParallelStatement>();
    stmt->line = previous().line;

    // Set default values
    stmt->channel = "";
    stmt->mode = "fork-join";  // Default mode for parallel blocks
    stmt->cores = "auto";
    stmt->onError = "stop";
    stmt->timeout = "0";
    stmt->grace = "0";
    stmt->onTimeout = "partial";

    // Parse parameters
    parseConcurrencyParams(stmt->channel, stmt->mode, stmt->cores, stmt->onError, stmt->timeout, stmt->grace, stmt->onTimeout);

    // Parse the block
    consume(TokenType::LEFT_BRACE, "Expected '{' after 'parallel'.");
    in_concurrent_block = true;
    stmt->body = block();
    in_concurrent_block = false;

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::concurrentStatement() {
    auto stmt = std::make_shared<AST::ConcurrentStatement>();
    stmt->line = previous().line;

    // Set default values
    stmt->channel = "";
    stmt->mode = "batch";
    stmt->cores = "auto";
    stmt->onError = "stop";
    stmt->timeout = "0";
    stmt->grace = "0";
    stmt->onTimeout = "partial";

    // Parse parameters
    parseConcurrencyParams(stmt->channel, stmt->mode, stmt->cores, stmt->onError, stmt->timeout, stmt->grace, stmt->onTimeout);

    // Parse the block
    consume(TokenType::LEFT_BRACE, "Expected '{' after 'concurrent'.");
    in_concurrent_block = true;
    stmt->body = block();
    in_concurrent_block = false;

    return stmt;
}

std::shared_ptr<AST::Statement> CSTParser::importStatement() {
    auto stmt = std::make_shared<AST::ImportStatement>();
    stmt->line = previous().line;

    // Parse module path
    if (check(TokenType::IDENTIFIER) || check(TokenType::MODULE)) {
        stmt->modulePath = advance().lexeme;
        while (match({TokenType::DOT})) {
            if (check(TokenType::IDENTIFIER) || check(TokenType::MODULE)) {
                stmt->modulePath += "." + advance().lexeme;
            } else {
                error("Expected module path component.");
                return nullptr;
            }
        }
    } else if (match({TokenType::LEFT_PAREN})) {
        stmt->isStringLiteralPath = true;
        stmt->modulePath = consume(TokenType::STRING, "Expected string literal for module path.").lexeme;
        consume(TokenType::RIGHT_PAREN, "Expected ')' after module path string.");
    } else {
        error("Expected module path or string literal after 'import'.");
        return nullptr;
    }

    // Parse optional alias
    if (match({TokenType::AS})) {
        stmt->alias = consume(TokenType::IDENTIFIER, "Expected alias name.").lexeme;
    }

    // Parse optional filter
    if (match({TokenType::SHOW, TokenType::HIDE})) {
        AST::ImportFilter filter;
        filter.type = previous().type == TokenType::SHOW ? AST::ImportFilterType::Show : AST::ImportFilterType::Hide;

        do {
            if (check(TokenType::IDENTIFIER) || check(TokenType::MODULE)) {
                filter.identifiers.push_back(advance().lexeme);
            } else {
                error("Expected identifier in filter list.");
                return nullptr;
            }
        } while (match({TokenType::COMMA}));

        stmt->filter = filter;
    }

    // Make semicolon optional
    match({TokenType::SEMICOLON});

    return stmt;
}

std::shared_ptr<AST::EnumDeclaration> CSTParser::enumDeclaration() {
    auto enumDecl = std::make_shared<AST::EnumDeclaration>();
    enumDecl->line = previous().line;

    // Parse enum name
    Token name = consume(TokenType::IDENTIFIER, "Expected enum name.");
    enumDecl->name = name.lexeme;

    consume(TokenType::LEFT_BRACE, "Expected '{' before enum body.");

    // Parse enum variants
    if (!check(TokenType::RIGHT_BRACE)) {
        do {
            std::string variantName = consume(TokenType::IDENTIFIER, "Expected variant name.").lexeme;

            std::optional<std::shared_ptr<AST::TypeAnnotation>> variantType;
            if (match({TokenType::LEFT_PAREN})) {
                variantType = parseTypeAnnotation();
                consume(TokenType::RIGHT_PAREN, "Expected ')' after variant type.");
            }

            enumDecl->variants.push_back({variantName, variantType});
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after enum body.");
    return enumDecl;
}

// Parse match statement: match(value) { pattern => statement, ... }
std::shared_ptr<AST::Statement> CSTParser::matchStatement() {
    auto stmt = std::make_shared<AST::MatchStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'match'.");
    stmt->value = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after match value.");

    consume(TokenType::LEFT_BRACE, "Expected '{' before match cases.");

    // Parse match cases: pattern => statement, ...
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        AST::MatchCase matchCase;

        // Parse pattern
        matchCase.pattern = parsePattern();

        // Parse optional guard
        if (match({TokenType::WHERE})) {
            matchCase.guard = expression();
        }

        consume(TokenType::ARROW, "Expected '=>' after match pattern.");

        // Parse body as a statement
        matchCase.body = statement();

        // Optional comma between cases
        if (match({TokenType::COMMA})) {
            // Allow trailing comma before '}'
            if (check(TokenType::RIGHT_BRACE)) break;
        }
        stmt->cases.push_back(matchCase);
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after match cases.");

    return stmt;
}

std::shared_ptr<AST::Expression> CSTParser::parsePattern() {
    // Error pattern matching: val identifier
    if (check(TokenType::VAL)) {
        return parseValPattern();
    }

    // Error pattern matching: err identifier or err ErrorType
    if (check(TokenType::ERR)) {
        return parseErrPattern();
    }

    // Specific error type pattern: ErrorType or ErrorType(params)
    if (check(TokenType::IDENTIFIER) && isErrorType(peek().lexeme)) {
        return parseErrorTypePattern();
    }

    // Wildcard pattern
    if (match({TokenType::DEFAULT}) || (check(TokenType::IDENTIFIER) && peek().lexeme == "_")) {
        if (previous().type != TokenType::DEFAULT) advance(); // consume '_' if it was an identifier
        auto pattern = std::make_shared<AST::LiteralExpr>();
        pattern->line = previous().line;
        pattern->value = nullptr; // Represent wildcard with null
        return pattern;
    }

    // List pattern
    if (check(TokenType::LEFT_BRACKET)) {
        return parseListPattern();
    }

    // Dictionary/Record destructuring pattern
    if (check(TokenType::LEFT_BRACE)) {
        return parseDictPattern();
    }

    // Tuple destructuring pattern
    if (check(TokenType::LEFT_PAREN)) {
        return parseTuplePattern();
    }

    // Binding pattern (e.g. Some(x))
    if (check(TokenType::IDENTIFIER) && current + 1 < scanner.getTokens().size() && 
        scanner.getTokens()[current + 1].type == TokenType::LEFT_PAREN) {
        return parseBindingPattern();
    }

    // Type pattern - check for primitive types and collection types
    if (isPrimitiveType(peek().type) || 
        check(TokenType::LIST_TYPE) || check(TokenType::DICT_TYPE) ||
        (check(TokenType::IDENTIFIER) && (peek().lexeme == "string" || peek().lexeme == "list" || peek().lexeme == "dict"))) {
        auto typePattern = std::make_shared<AST::TypePatternExpr>();
        typePattern->line = peek().line;
        typePattern->type = parseTypeAnnotation();
        return typePattern;
    }

    // Literal pattern
    if (check(TokenType::IDENTIFIER) ||
               check(TokenType::NUMBER) || check(TokenType::STRING) ||
               check(TokenType::TRUE) || check(TokenType::FALSE) ||
               check(TokenType::NIL)) {
        return primary();
    }

    error("Expected pattern in match case.");
    return makeErrorExpr();
}

std::shared_ptr<AST::Expression> CSTParser::parseBindingPattern() {
    auto pattern = std::make_shared<AST::BindingPatternExpr>();
    pattern->line = peek().line;
    pattern->typeName = consume(TokenType::IDENTIFIER, "Expected type name in binding pattern.").lexeme;
    consume(TokenType::LEFT_PAREN, "Expected '(' after type name in binding pattern.");
    pattern->variableName = consume(TokenType::IDENTIFIER, "Expected variable name in binding pattern.").lexeme;
    consume(TokenType::RIGHT_PAREN, "Expected ')' after variable name in binding pattern.");
    return pattern;
}

std::shared_ptr<AST::Expression> CSTParser::parseListPattern() {
    auto pattern = std::make_shared<AST::ListPatternExpr>();
    pattern->line = peek().line;
    consume(TokenType::LEFT_BRACKET, "Expected '[' at start of list pattern.");

    if (!check(TokenType::RIGHT_BRACKET)) {
        do {
            if (match({TokenType::ELLIPSIS})) {
                pattern->restElement = consume(TokenType::IDENTIFIER, "Expected identifier for rest element.").lexeme;
                break;
            }
            pattern->elements.push_back(parsePattern());
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_BRACKET, "Expected ']' at end of list pattern.");
    return pattern;
}

std::shared_ptr<AST::Expression> CSTParser::parseDictPattern() {
    auto pattern = std::make_shared<AST::DictPatternExpr>();
    pattern->line = peek().line;
    consume(TokenType::LEFT_BRACE, "Expected '{' at start of dict pattern.");

    if (!check(TokenType::RIGHT_BRACE)) {
        do {
            if (match({TokenType::ELLIPSIS})) {
                // Rest pattern: ...rest
                pattern->hasRestElement = true;
                if (check(TokenType::IDENTIFIER)) {
                    pattern->restBinding = advance().lexeme;
                }
                break;
            }

            // Parse field pattern: key or key: binding
            std::string key = consume(TokenType::IDENTIFIER, "Expected field name in dict pattern.").lexeme;
            AST::DictPatternExpr::Field field;
            field.key = key;

            if (match({TokenType::COLON})) {
                // Explicit binding: key: binding
                field.binding = consume(TokenType::IDENTIFIER, "Expected binding name after ':' in dict pattern.").lexeme;
            } else {
                // Shorthand: key (binding is same as key)
                field.binding = key;
            }

            pattern->fields.push_back(field);
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' at end of dict pattern.");
    return pattern;
}

std::shared_ptr<AST::Expression> CSTParser::parseTuplePattern() {
    auto pattern = std::make_shared<AST::TuplePatternExpr>();
    pattern->line = peek().line;
    consume(TokenType::LEFT_PAREN, "Expected '(' at start of tuple pattern.");

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            pattern->elements.push_back(parsePattern());
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' at end of tuple pattern.");
    return pattern;
}

// Expression parsing methods
std::shared_ptr<AST::Expression> CSTParser::expression() {
    return assignment();
}

std::shared_ptr<AST::Expression> CSTParser::assignment() {
    auto expr = logicalOr();

    if (match({TokenType::EQUAL, TokenType::PLUS_EQUAL, TokenType::MINUS_EQUAL,
               TokenType::STAR_EQUAL, TokenType::SLASH_EQUAL, TokenType::MODULUS_EQUAL})) {
        auto op = previous();
        auto value = assignment();

        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->name = varExpr->name;
            assignExpr->op = op.type;
            assignExpr->value = value;
            return assignExpr;
        } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->object = memberExpr->object;
            assignExpr->member = memberExpr->name;
            assignExpr->op = op.type;
            assignExpr->value = value;
            return assignExpr;
        } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->object = indexExpr->object;
            assignExpr->index = indexExpr->index;
            assignExpr->op = op.type;
            assignExpr->value = value;
            return assignExpr;
        }

        error("Invalid assignment target.");
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::logicalOr() {
    auto expr = logicalAnd();

    while (match({TokenType::OR})) {
        auto op = previous();
        auto right = logicalAnd();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::logicalAnd() {
    auto expr = equality();

    while (match({TokenType::AND})) {
        auto op = previous();
        auto right = equality();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::equality() {
    auto expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        auto op = previous();
        auto right = comparison();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::comparison() {
    auto expr = term();

    // Check for range expressions (e.g., 1..10)
    if (match({TokenType::RANGE})) {
        auto rangeExpr = std::make_shared<AST::RangeExpr>();
        rangeExpr->line = previous().line;
        rangeExpr->start = expr;
        rangeExpr->end = term();
        rangeExpr->step = nullptr; // No step value for now
        rangeExpr->inclusive = true; // Default to inclusive range
        return rangeExpr;
    }

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        auto op = previous();
        auto right = term();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::term() {
    auto expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS})) {
        auto op = previous();
        auto right = factor();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::factor() {
    auto expr = power();

    while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULUS})) {
        auto op = previous();
        auto right = unary();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::power() {
    auto expr = unary();
    while (match({TokenType::POWER})) { // Assuming POWER is '**'
        auto op = previous();
        auto right = power(); // Right-associative!
        auto binaryExpr = createNode<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;
        attachTriviaFromToken(op);
        expr = binaryExpr;
    }
    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS, TokenType::PLUS})) {
        auto op = previous();
        auto right = unary();

        auto unaryExpr = std::make_shared<AST::UnaryExpr>();
        unaryExpr->line = op.line;
        unaryExpr->op = op.type;
        unaryExpr->right = right;

        return unaryExpr;
    }

    if (match({TokenType::AWAIT})) {
        auto awaitExpr = std::make_shared<AST::AwaitExpr>();
        awaitExpr->line = previous().line;
        awaitExpr->expression = unary();
        return awaitExpr;
    }

    return call();
}

std::shared_ptr<AST::Expression> CSTParser::call() {
    auto expr = primary();

    while (true) {
        if (match({TokenType::LEFT_PAREN})) {
            expr = finishCall(expr);
        } else if (match({TokenType::DOT})) {
            auto name = consume(TokenType::IDENTIFIER, "Expected property name after '.'.");

            auto memberExpr = std::make_shared<AST::MemberExpr>();
            memberExpr->line = name.line;
            memberExpr->object = expr;
            memberExpr->name = name.lexeme;

            expr = memberExpr;
        } else if (match({TokenType::LEFT_BRACKET})) {
            auto index = expression();
            consume(TokenType::RIGHT_BRACKET, "Expected ']' after index.");

            auto indexExpr = std::make_shared<AST::IndexExpr>();
            indexExpr->line = previous().line;
            indexExpr->object = expr;
            indexExpr->index = index;

            expr = indexExpr;
        } else if (match({TokenType::QUESTION})) {
            // Handle fallible expression with ? operator
            auto fallibleExpr = std::make_shared<AST::FallibleExpr>();
            fallibleExpr->line = previous().line;
            fallibleExpr->expression = expr;
            
            // Check for optional else handler
            if (match({TokenType::ELSE})) {
                // Parse optional error variable binding
                if (check(TokenType::IDENTIFIER)) {
                    fallibleExpr->elseVariable = consume(TokenType::IDENTIFIER, "Expected error variable name.").lexeme;
                }
                
                // Parse else handler block or statement
                fallibleExpr->elseHandler = statement();
            }
            
            expr = fallibleExpr;
        } else {
            break;
        }
    }

    return expr;
}

std::shared_ptr<AST::Expression> CSTParser::finishCall(std::shared_ptr<AST::Expression> callee) {
    std::vector<std::shared_ptr<AST::Expression>> arguments;
    std::unordered_map<std::string, std::shared_ptr<AST::Expression>> namedArgs;

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            // Check for named arguments
            if (check(TokenType::IDENTIFIER) && peek().lexeme.length() > 0) {
                Token nameToken = peek();
                advance();

                if (match({TokenType::EQUAL})) {
                    // This is a named argument
                    auto argValue = expression();
                    namedArgs[nameToken.lexeme] = argValue;
                    continue;
                } else {
                    // Not a named argument, rewind and parse as regular expression
                    current--; // Rewind to before the identifier
                }
            }

            // Regular positional argument
            arguments.push_back(expression());
        } while (match({TokenType::COMMA}));
    }

    auto paren = consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments.");

    auto callExpr = std::make_shared<AST::CallExpr>();
    callExpr->line = paren.line;
    callExpr->callee = callee;
    callExpr->arguments = arguments;
    callExpr->namedArgs = namedArgs;
    return callExpr;
}

std::shared_ptr<AST::InterpolatedStringExpr> CSTParser::interpolatedString() {
    auto interpolated = std::make_shared<AST::InterpolatedStringExpr>();
    interpolated->line = previous().line;
    
    // Add the initial string part
    interpolated->addStringPart(previous().lexeme);
    
    // Parse interpolation parts
    while (check(TokenType::INTERPOLATION_START)) {
        advance(); // consume INTERPOLATION_START
        
        // Parse the expression inside the interpolation
        auto expr = expression();
        interpolated->addExpressionPart(expr);
        
        // Expect INTERPOLATION_END
        consume(TokenType::INTERPOLATION_END, "Expected '}' after interpolation expression.");
        
        // Check if there's another string part after this interpolation
        if (check(TokenType::STRING)) {
            advance();
            interpolated->addStringPart(previous().lexeme);
        }
    }
    
    return interpolated;
}

std::shared_ptr<AST::Expression> CSTParser::primary() {
    if (match({TokenType::FALSE})) {
        auto literalExpr = createNode<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = false;
        attachTriviaFromToken(previous());
        return literalExpr;
    }

    if (match({TokenType::TRUE})) {
        auto literalExpr = createNode<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = true;
        attachTriviaFromToken(previous());
        return literalExpr;
    }

    if (match({TokenType::NONE})) {
        auto literalExpr = createNode<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = nullptr;
        attachTriviaFromToken(previous());
        return literalExpr;
    }

    if (match({TokenType::NIL})) {
        auto literalExpr = createNode<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = nullptr;
        attachTriviaFromToken(previous());
        return literalExpr;
    }

    if (match({TokenType::NUMBER})) {
        auto token = previous();
        auto literalExpr = createNode<AST::LiteralExpr>();
        literalExpr->line = token.line;
        attachTriviaFromToken(token);

        // Check if the number is an integer or a float
        // Numbers with decimal points or scientific notation are treated as floats
        if (token.lexeme.find('.') != std::string::npos || 
            token.lexeme.find('e') != std::string::npos || 
            token.lexeme.find('E') != std::string::npos) {
            try {
                literalExpr->value = std::stod(token.lexeme);
            } catch (const std::exception& e) {
                error("Invalid floating-point number: " + token.lexeme);
                literalExpr->value = 0.0;
            }
        } else {
            try {
                // Try to parse as signed long long first
                literalExpr->value = std::stoll(token.lexeme);
            } catch (const std::out_of_range& e) {
                try {
                    // If that fails, try unsigned long long and convert to double if needed
                    unsigned long long ullValue = std::stoull(token.lexeme);
                    
                    // If the value fits in long long, use it as long long
                    if (ullValue <= static_cast<unsigned long long>(std::numeric_limits<long long>::max())) {
                        literalExpr->value = static_cast<long long>(ullValue);
                    } else {
                        // Otherwise, convert to double (may lose precision for very large values)
                        literalExpr->value = static_cast<double>(ullValue);
                    }
                } catch (const std::exception& e2) {
                    // If both fail, treat as double
                    try {
                        literalExpr->value = std::stod(token.lexeme);
                    } catch (const std::exception& e3) {
                        error("Invalid number: " + token.lexeme);
                        literalExpr->value = 0LL;
                    }
                }
            } catch (const std::exception& e) {
                error("Invalid integer number: " + token.lexeme);
                literalExpr->value = 0LL;
            }
        }

        return literalExpr;
    }

    if (match({TokenType::STRING})) {
        // Check if this is an interpolated string (followed by INTERPOLATION_START)
        if (check(TokenType::INTERPOLATION_START)) {
            // This is an interpolated string
            return interpolatedString();
        } else {
            // Regular string literal
            auto literalExpr = std::make_shared<AST::LiteralExpr>();
            literalExpr->line = previous().line;
            literalExpr->value = previous().lexeme;
            return literalExpr;
        }
    }

    // Handle interpolated strings that start with interpolation (no initial string part)
    if (match({TokenType::INTERPOLATION_START})) {
        // This is an interpolated string starting with interpolation
        // We need to "back up" and call interpolatedString with an empty initial string
        current--; // Back up to before INTERPOLATION_START
        
        auto interpolated = std::make_shared<AST::InterpolatedStringExpr>();
        interpolated->line = peek().line;
        
        // Add empty initial string part
        interpolated->addStringPart("");
        
        // Parse interpolation parts
        while (check(TokenType::INTERPOLATION_START)) {
            advance(); // consume INTERPOLATION_START
            
            // Parse the expression inside the interpolation
            auto expr = expression();
            interpolated->addExpressionPart(expr);
            
            // Expect INTERPOLATION_END
            consume(TokenType::INTERPOLATION_END, "Expected '}' after interpolation expression.");
            
            // Check if there's another string part after this interpolation
            if (check(TokenType::STRING)) {
                advance();
                interpolated->addStringPart(previous().lexeme);
            }
        }
        
        return interpolated;
    }

    if (match({TokenType::THIS})) {
        auto thisExpr = std::make_shared<AST::ThisExpr>();
        thisExpr->line = previous().line;
        return thisExpr;
    }

    if (match({TokenType::IDENTIFIER})) {
        auto token = previous();
        // Check if this is 'self' keyword
        if (token.lexeme == "self" || token.lexeme == "this" ) {
            auto thisExpr = std::make_shared<AST::ThisExpr>();
            thisExpr->line = token.line;
            return thisExpr;
        } else {
            // Check if this is an object literal: Identifier { ... }
            if (check(TokenType::LEFT_BRACE)) {
                // This is an object literal with constructor name
                auto objExpr = std::make_shared<AST::ObjectLiteralExpr>();
                objExpr->line = token.line;
                objExpr->constructorName = token.lexeme;
                
                advance(); // consume LEFT_BRACE
                
                // Parse key-value pairs
                if (!check(TokenType::RIGHT_BRACE)) {
                    do {
                        // Parse key
                        Token keyToken = consume(TokenType::IDENTIFIER, "Expected property name in object literal.");
                        consume(TokenType::COLON, "Expected ':' after property name.");
                        
                        // Parse value
                        auto value = expression();
                        
                        objExpr->properties[keyToken.lexeme] = value;
                    } while (match({TokenType::COMMA}));
                }
                
                consume(TokenType::RIGHT_BRACE, "Expected '}' after object literal properties.");
                return objExpr;
            } else {
                auto varExpr = std::make_shared<AST::VariableExpr>();
                varExpr->line = token.line;
                varExpr->name = token.lexeme;
                return varExpr;
            }
        }
    }

    if (match({TokenType::SLEEP})) {
        // Treat SLEEP as a function call
        auto varExpr = std::make_shared<AST::VariableExpr>();
        varExpr->line = previous().line;
        varExpr->name = "sleep";
        return varExpr;
    }

    // Handle error construction: err(ErrorType) or err(ErrorType(args))
    if (match({TokenType::ERR})) {
        auto errorExpr = std::make_shared<AST::ErrorConstructExpr>();
        errorExpr->line = previous().line;
        
        consume(TokenType::LEFT_PAREN, "Expected '(' after 'err'.");
        
        // Parse error type
        errorExpr->errorType = consume(TokenType::IDENTIFIER, "Expected error type name.").lexeme;
        
        // Check if there are constructor arguments
        if (match({TokenType::LEFT_PAREN})) {
            // Parse constructor arguments: err(ErrorType(arg1, arg2))
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    errorExpr->arguments.push_back(expression());
                } while (match({TokenType::COMMA}));
            }
            consume(TokenType::RIGHT_PAREN, "Expected ')' after error constructor arguments.");
        }
        
        consume(TokenType::RIGHT_PAREN, "Expected ')' after error construction.");
        return errorExpr;
    }

    // Handle success construction: ok(value)
    if (match({TokenType::OK})) {
        auto okExpr = std::make_shared<AST::OkConstructExpr>();
        okExpr->line = previous().line;
        
        consume(TokenType::LEFT_PAREN, "Expected '(' after 'ok'.");
        okExpr->value = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after ok value.");
        
        return okExpr;
    }

    // Check for lambda expression: fn(param1, param2): returnType {body}
    if (check(TokenType::FN)) {
        return lambdaExpression();
    }

    if (match({TokenType::LEFT_PAREN})) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");

        auto groupingExpr = std::make_shared<AST::GroupingExpr>();
        groupingExpr->line = previous().line;
        groupingExpr->expression = expr;

        return groupingExpr;
    }

    if (match({TokenType::LEFT_BRACKET})) {
        // Parse list literal
        std::vector<std::shared_ptr<AST::Expression>> elements;

        if (!check(TokenType::RIGHT_BRACKET)) {
            do {
                elements.push_back(expression());
            } while (match({TokenType::COMMA}));
        }

        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list elements.");

        auto listExpr = std::make_shared<AST::ListExpr>();
        listExpr->line = previous().line;
        listExpr->elements = elements;

        return listExpr;
    }

    if (match({TokenType::LEFT_BRACE})) {
        // Parse dictionary literal
        std::vector<std::pair<std::shared_ptr<AST::Expression>, std::shared_ptr<AST::Expression>>> entries;

        if (!check(TokenType::RIGHT_BRACE)) {
            do {
                auto key = expression();
                consume(TokenType::COLON, "Expected ':' after dictionary key.");
                auto value = expression();

                entries.push_back({key, value});
            } while (match({TokenType::COMMA}));
        }

        consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary entries.");

        auto dictExpr = std::make_shared<AST::DictExpr>();
        dictExpr->line = previous().line;
        dictExpr->entries = entries;

        return dictExpr;
    }

    // Check if we're in a trait method or other context where an empty expression might be valid
    if (current > 0 && current < scanner.getTokens().size() && 
        scanner.getTokens()[current-1].type == TokenType::LEFT_BRACE && 
        scanner.getTokens()[current].type == TokenType::RIGHT_BRACE) {
        // This is likely an empty block, so we'll create a placeholder expression
        auto placeholderExpr = std::make_shared<AST::LiteralExpr>();
        placeholderExpr->line = peek().line;
        placeholderExpr->value = nullptr; // Use null as a placeholder
        return placeholderExpr;
    } else if (match({TokenType::SELF, TokenType::THIS})) {
        // Handle 'self' as a special case
        auto thisExpr = std::make_shared<AST::ThisExpr>();
        thisExpr->line = previous().line;
        return thisExpr;
    } else if (match({TokenType::SUPER})) {
        // Handle 'super' for parent class access
        auto superExpr = std::make_shared<AST::SuperExpr>();
        superExpr->line = previous().line;
        return superExpr;
    } else {
        // Only report error if we're not at the end of input or at a statement terminator
        if (!isAtEnd() && !check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE) && 
            !check(TokenType::RIGHT_PAREN) && !check(TokenType::RIGHT_BRACKET)) {
            error("Expected expression.", false);
            advance(); // Move past the error token to avoid infinite loop
        }
        return makeErrorExpr();
    }
}

std::shared_ptr<AST::Statement> CSTParser::typeDeclaration() {
    // Create a new type declaration statement
    auto typeDecl = std::make_shared<AST::TypeDeclaration>();
    typeDecl->line = previous().line;

    // Parse type name
    Token name = consume(TokenType::IDENTIFIER, "Expected type name.");
    typeDecl->name = name.lexeme;
    
    // Parse equals sign
    consume(TokenType::EQUAL, "Expected '=' after type name.");
    
    // Parse the right-hand side of the type declaration
    
    // For list literals like [any], [str], [Person]
    if (match({TokenType::LEFT_BRACKET})) {
        auto listType = std::make_shared<AST::TypeAnnotation>();
        listType->typeName = "list";
        listType->isList = true;
        
        // Parse element type (e.g., any in [any])
        if (!check(TokenType::RIGHT_BRACKET)) {
            // Parse the element type
            auto elementType = parseTypeAnnotation();
            listType->elementType = elementType;
        } else {
            // Default to any if no element type is specified
            auto anyType = std::make_shared<AST::TypeAnnotation>();
            anyType->typeName = "any";
            anyType->isPrimitive = true;
            listType->elementType = anyType;
        }
        
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type.");
        typeDecl->type = listType;
    }
    // For dictionary literals like {any: any}, {str: str}, {int: User} or structural types like {name: str, age: int}
    else if (match({TokenType::LEFT_BRACE})) {
        // We need to determine if this is a dictionary type or a structural type
        // Dictionary types have the pattern: {KeyType: ValueType} (single key-value pair)
        // Structural types have the pattern: {field: Type, field: Type, ...} (field names)
        
        // Look ahead to determine the type
        size_t savedCurrent = current;
        bool isDictionary = false;
        
        // Check if the first token is a type (for dictionary) or identifier (for field name)
        if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
            Token firstToken = peek();
            advance(); // Consume the first token
            
            if (match({TokenType::COLON})) {
                // We have a colon, now check what comes after
                if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
                    Token secondToken = peek();
                    advance(); // Consume the second token
                    
                    // If we immediately hit a closing brace, it's a dictionary type
                    if (check(TokenType::RIGHT_BRACE)) {
                        isDictionary = true;
                    }
                    // If the first token is a primitive type and second is also a type, it's likely a dictionary
                    else if (isPrimitiveType(firstToken.type) && (isPrimitiveType(secondToken.type) || 
                             secondToken.lexeme == "any" || secondToken.lexeme == "str" || 
                             secondToken.lexeme == "int" || secondToken.lexeme == "float")) {
                        isDictionary = true;
                    }
                }
            }
        }
        
        // Reset the parser position
        current = savedCurrent;
        
        if (isDictionary) {
            // Parse as dictionary type
            auto dictType = std::make_shared<AST::TypeAnnotation>();
            dictType->typeName = "dict";
            dictType->isDict = true;
            
            // Parse key type
            Token keyToken = advance();
            auto keyType = std::make_shared<AST::TypeAnnotation>();
            if (isPrimitiveType(keyToken.type)) {
                keyType->typeName = tokenTypeToString(keyToken.type);
                keyType->isPrimitive = true;
            } else if (keyToken.lexeme == "any") {
                keyType->typeName = "any";
                keyType->isPrimitive = true;
            } else if (keyToken.lexeme == "int") {
                keyType->typeName = "int";
                keyType->isPrimitive = true;
            } else if (keyToken.lexeme == "str") {
                keyType->typeName = "str";
                keyType->isPrimitive = true;
            } else {
                keyType->typeName = keyToken.lexeme;
                keyType->isUserDefined = true;
            }
            
            consume(TokenType::COLON, "Expected ':' in dictionary type.");
            
            // Parse value type
            auto valueType = parseTypeAnnotation();
            
            // Set the key and value types
            dictType->keyType = keyType;
            dictType->valueType = valueType;
            
            consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
            typeDecl->type = dictType;
        } else {
            // Parse as structural type
            auto structType = std::make_shared<AST::TypeAnnotation>();
            structType->typeName = "struct";
            structType->isStructural = true;
            
            // Parse fields until we hit a closing brace
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                // Check for rest parameter (...) or extensible record (...baseRecord)
                if (match({TokenType::ELLIPSIS})) {
                    structType->hasRest = true;
                    
                    // Check if there's a base record identifier after ...
                    if (check(TokenType::IDENTIFIER)) {
                        // This is an extensible record with a base record
                        std::string baseRecordName = consume(TokenType::IDENTIFIER, "Expected base record name after '...'.").lexeme;
                        
                        // Store the base record name
                        if (structType->baseRecord.empty()) {
                            structType->baseRecord = baseRecordName;
                        }
                        
                        // Also add to the list of base records for multiple inheritance
                        structType->baseRecords.push_back(baseRecordName);
                    }
                    
                    // Check for comma to continue with more fields
                    if (check(TokenType::COMMA)) {
                        consume(TokenType::COMMA, "Expected ',' after rest parameter.");
                        continue;
                    } else if (check(TokenType::RIGHT_BRACE)) {
                        // End of record definition
                        break;
                    } else {
                        error("Expected ',' or '}' after rest parameter.");
                    }
                }
                
                // Parse field name
                std::string fieldName;
                if (check(TokenType::IDENTIFIER)) {
                    fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
                } else if (check(TokenType::STRING)) {
                    // Handle string literals as field names (e.g., { "kind": "Some" })
                    Token stringToken = consume(TokenType::STRING, "Expected field name.");
                    fieldName = stringToken.lexeme;
                    // Remove quotes if present
                    if (fieldName.size() >= 2 && (fieldName[0] == '"' || fieldName[0] == '\'') && 
                        (fieldName[fieldName.size()-1] == '"' || fieldName[fieldName.size()-1] == '\'')) {
                        fieldName = fieldName.substr(1, fieldName.size() - 2);
                    }
                } else {
                    error("Expected field name.");
                    return typeDecl;
                }
                
                // Parse field type
                consume(TokenType::COLON, "Expected ':' after field name.");
                auto fieldType = parseTypeAnnotation();
                
                // Add field to structural type
                structType->structuralFields.push_back({fieldName, fieldType});
                
                // Check for comma or end of struct
                if (!check(TokenType::RIGHT_BRACE)) {
                    match({TokenType::COMMA}); // Optional comma
                }
            }
            
            consume(TokenType::RIGHT_BRACE, "Expected '}' after structural type.");
            typeDecl->type = structType;
        }
    }
    // For union types like Some | None, Success | Error
    else if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
        // Parse the first type in the union
        auto firstType = parseTypeAnnotation();
        
        // Check if this is a union type (e.g., Some | None)
        if (match({TokenType::PIPE})) {
            // This is a union type
            auto unionType = std::make_shared<AST::TypeAnnotation>();
            unionType->typeName = "union";
            unionType->isUnion = true;
            unionType->unionTypes.push_back(firstType);
            
            // Parse the right side of the union
            do {
                unionType->unionTypes.push_back(parseTypeAnnotation());
            } while (match({TokenType::PIPE}));
            
            typeDecl->type = unionType;
        }
        // Check if this is an intersection type (e.g., HasName and HasAge)
        else if (match({TokenType::AND})) {
            // This is an intersection type
            auto intersectionType = std::make_shared<AST::TypeAnnotation>();
            intersectionType->typeName = "intersection";
            intersectionType->isIntersection = true;
            intersectionType->unionTypes.push_back(firstType);
            
            // Parse the right side of the intersection
            do {
                intersectionType->unionTypes.push_back(parseTypeAnnotation());
            } while (match({TokenType::AND}));
            
            typeDecl->type = intersectionType;
        }
        // Check if this is a refined type (e.g., int where value > 0)
        else if (match({TokenType::WHERE})) {
            // This is a refined type
            firstType->isRefined = true;
            firstType->refinementCondition = expression();
            typeDecl->type = firstType;
        }
        // Otherwise, it's a simple type alias
        else {
            typeDecl->type = firstType;
        }
    }
    // For nil type
    else if (match({TokenType::NIL})) {
        auto nilType = std::make_shared<AST::TypeAnnotation>();
        nilType->typeName = "nil";
        nilType->isPrimitive = true;
        typeDecl->type = nilType;
    }
    else {
        error("Expected type definition after '='.");
    }
    
    // Parse optional semicolon
    match({TokenType::SEMICOLON});
    
    return typeDecl;
}
            
// Type annotation parsing
std::shared_ptr<AST::TypeAnnotation> CSTParser::parseTypeAnnotation() {
    // Parse the base type first
    auto type = parseBasicType();
    
    // Check for union types (e.g., int | float)
    if (check(TokenType::PIPE)) {
        // This is a union type - create a union and add the first type
        auto unionType = std::make_shared<AST::TypeAnnotation>();
        unionType->typeName = "union";
        unionType->isUnion = true;
        unionType->unionTypes.push_back(type);
        
        // Parse the remaining union types
        while (match({TokenType::PIPE})) {
            auto nextType = parseBasicType();
            unionType->unionTypes.push_back(nextType);
        }
        
        return unionType;
    }
    
    // Check for intersection types (e.g., HasName and HasAge)
    if (check(TokenType::AND)) {
        // This is an intersection type
        auto intersectionType = std::make_shared<AST::TypeAnnotation>();
        intersectionType->typeName = "intersection";
        intersectionType->isIntersection = true;
        intersectionType->unionTypes.push_back(type); // Reuse unionTypes for intersection types

        // Parse the right side of the intersection
        while (match({TokenType::AND})) {
            auto nextType = parseBasicType();
            intersectionType->unionTypes.push_back(nextType);
        }

        return intersectionType;
    }

    // Check for refined types (e.g., int where value > 0)
    if (match({TokenType::WHERE})) {
        // This is a refined type with a constraint
        type->isRefined = true;
        
        // Parse the refinement condition
        // For example: "value > 0" or "matches(value, pattern)"
        type->refinementCondition = expression();
    }

    return type;
}


// Helper method to check if a token type is a primitive type
bool CSTParser::isPrimitiveType(TokenType type) {
    return type == TokenType::INT_TYPE || type == TokenType::INT8_TYPE || type == TokenType::INT16_TYPE ||
           type == TokenType::INT32_TYPE || type == TokenType::INT64_TYPE || type == TokenType::UINT_TYPE ||
           type == TokenType::UINT8_TYPE || type == TokenType::UINT16_TYPE || type == TokenType::UINT32_TYPE ||
           type == TokenType::UINT64_TYPE || type == TokenType::FLOAT_TYPE || type == TokenType::FLOAT32_TYPE ||
           type == TokenType::FLOAT64_TYPE || type == TokenType::STR_TYPE || type == TokenType::BOOL_TYPE ||
           type == TokenType::ANY_TYPE || type == TokenType::NIL_TYPE;
}

// Helper method to convert a token type to a string
std::string CSTParser::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT_TYPE: return "int";
        case TokenType::INT8_TYPE: return "i8";
        case TokenType::INT16_TYPE: return "i16";
        case TokenType::INT32_TYPE: return "i32";
        case TokenType::INT64_TYPE: return "i64";
        case TokenType::UINT_TYPE: return "uint";
        case TokenType::UINT8_TYPE: return "u8";
        case TokenType::UINT16_TYPE: return "u16";
        case TokenType::UINT32_TYPE: return "u32";
        case TokenType::UINT64_TYPE: return "u64";
        case TokenType::FLOAT_TYPE: return "float";
        case TokenType::FLOAT32_TYPE: return "f32";
        case TokenType::FLOAT64_TYPE: return "f64";
        case TokenType::STR_TYPE: return "str";
        case TokenType::BOOL_TYPE: return "bool";
        case TokenType::ANY_TYPE: return "any";
        case TokenType::NIL_TYPE: return "nil";
        default: return "unknown";
    }
}

// Parse union type (e.g., Some | None, int | str | bool)
std::shared_ptr<AST::TypeAnnotation> CSTParser::parseUnionType() {
    auto unionType = std::make_shared<AST::TypeAnnotation>();
    unionType->typeName = "union";
    unionType->isUnion = true;
    
    // Parse the first type in the union (call parseBasicType to avoid recursion)
    auto firstType = parseBasicType();
    unionType->unionTypes.push_back(firstType);
    
    // Parse additional types separated by PIPE tokens
    while (match({TokenType::PIPE})) {
        auto nextType = parseBasicType();
        unionType->unionTypes.push_back(nextType);
    }
    
    return unionType;
}

// Parse a basic type without union/intersection logic (to avoid recursion)
std::shared_ptr<AST::TypeAnnotation> CSTParser::parseBasicType() {
    auto type = std::make_shared<AST::TypeAnnotation>();

    // Check for list types (e.g., [int], [str], [Person])
    if (match({TokenType::LEFT_BRACKET})) {
        type->isList = true;
        type->typeName = "list";
        
        // Parse element type (e.g., int in [int])
        if (!check(TokenType::RIGHT_BRACKET)) {
            // Parse the element type
            type->elementType = parseBasicType();
        } else {
            // Default to any if no element type is specified
            auto anyType = std::make_shared<AST::TypeAnnotation>();
            anyType->typeName = "any";
            anyType->isPrimitive = true;
            type->elementType = anyType;
        }
        
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type.");
        return type;
    }
    
    // Check for dictionary types (e.g., {str: int}) or structural types (e.g., { name: str, age: int })
    if (match({TokenType::LEFT_BRACE})) {
        return parseBraceType();
    }

    // Parse primitive and user-defined types
    if (match({TokenType::INT_TYPE})) {
        type->typeName = "int";
        type->isPrimitive = true;
    } else if (match({TokenType::INT8_TYPE})) {
        type->typeName = "i8";
        type->isPrimitive = true;
    } else if (match({TokenType::INT16_TYPE})) {
        type->typeName = "i16";
        type->isPrimitive = true;
    } else if (match({TokenType::INT32_TYPE})) {
        type->typeName = "i32";
        type->isPrimitive = true;
    } else if (match({TokenType::INT64_TYPE})) {
        type->typeName = "i64";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT_TYPE})) {
        type->typeName = "uint";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT8_TYPE})) {
        type->typeName = "u8";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT16_TYPE})) {
        type->typeName = "u16";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT32_TYPE})) {
        type->typeName = "u32";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT64_TYPE})) {
        type->typeName = "u64";
        type->isPrimitive = true;
    } else if (match({TokenType::FLOAT_TYPE})) {
        type->typeName = "float";
        type->isPrimitive = true;
    } else if (match({TokenType::FLOAT32_TYPE})) {
        type->typeName = "f32";
        type->isPrimitive = true;
    } else if (match({TokenType::FLOAT64_TYPE})) {
        type->typeName = "f64";
        type->isPrimitive = true;
    } else if (match({TokenType::STR_TYPE})) {
        type->typeName = "str";
        type->isPrimitive = true;
    } else if (match({TokenType::BOOL_TYPE})) {
        type->typeName = "bool";
        type->isPrimitive = true;
    } else if (match({TokenType::ANY_TYPE})) {
        type->typeName = "any";
        type->isPrimitive = true;
    } else if (match({TokenType::NIL_TYPE})) {
        type->typeName = "nil";
        type->isPrimitive = true;
    } else if (match({TokenType::NIL})) {
        type->typeName = "nil";
        type->isPrimitive = true;
    } else if (match({TokenType::LIST_TYPE})) {
        type->typeName = "list";
        type->isList = true;
    } else if (match({TokenType::DICT_TYPE})) {
        type->typeName = "dict";
        type->isDict = true;
    } else if (match({TokenType::ARRAY_TYPE})) {
        type->typeName = "array";
        type->isList = true;
    } else if (match({TokenType::OPTION_TYPE})) {
        type->typeName = "option";
    } else if (match({TokenType::RESULT_TYPE})) {
        type->typeName = "result";
    } else if (match({TokenType::CHANNEL_TYPE})) {
        type->typeName = "channel";
    } else if (match({TokenType::ATOMIC_TYPE})) {
        type->typeName = "atomic";
    } else if (match({TokenType::FUNCTION_TYPE})) {
        type->typeName = "function";
        type->isFunction = true;
        
        // Check for function signature: (param1: Type1, param2: Type2): ReturnType
        if (match({TokenType::LEFT_PAREN})) {
            // Parse parameter types
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    // Skip parameter name if present (we only care about types)
                    if (check(TokenType::IDENTIFIER) && peek().lexeme != "int" && peek().lexeme != "str" && 
                        peek().lexeme != "bool" && peek().lexeme != "float") {
                        advance(); // consume parameter name
                        if (match({TokenType::COLON})) {
                            // Parse parameter type
                            type->functionParams.push_back(parseTypeAnnotation());
                        }
                    } else {
                        // Just a type without parameter name
                        type->functionParams.push_back(parseTypeAnnotation());
                    }
                } while (match({TokenType::COMMA}));
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')' after function parameters.");
            
            // Check for return type
            if (match({TokenType::COLON})) {
                type->returnType = parseTypeAnnotation();
            }
        }
    } else if (match({TokenType::ENUM_TYPE})) {
        type->typeName = "enum";
    } else if (match({TokenType::SUM_TYPE})) {
        type->typeName = "sum";
    } else if (match({TokenType::UNION_TYPE})) {
        type->typeName = "union";
        type->isUnion = true;
    } else if (match({TokenType::STRING})) {
        // Handle string literals as literal types (e.g., "Some", "None")
        std::string literalValue = previous().lexeme;
        // Remove quotes if present
        if (literalValue.size() >= 2 && (literalValue[0] == '"' || literalValue[0] == '\'') && 
            (literalValue[literalValue.size()-1] == '"' || literalValue[literalValue.size()-1] == '\'')) {
            literalValue = literalValue.substr(1, literalValue.size() - 2);
        }
        type->typeName = "\"" + literalValue + "\""; // Keep quotes to indicate it's a literal type
        type->isPrimitive = true; // Treat literal types as primitive
    } else {
        // Handle user-defined types
        if (check(TokenType::IDENTIFIER)) {
            // Parse the user-defined type name
            std::string typeName = consume(TokenType::IDENTIFIER, "Expected type name.").lexeme;
            type->typeName = typeName;
            type->isUserDefined = true;
        } else {
            // Fall back to identifier for user-defined types
            type->typeName = consume(TokenType::IDENTIFIER, "Expected type name for definition.").lexeme;
            type->isUserDefined = true;
        }
    }

    // Check for optional type or error union type
    if (match({TokenType::QUESTION})) {
        // This could be either optional (Type?) or error union (Type?ErrorType1, ErrorType2)
        if (check(TokenType::IDENTIFIER)) {
            // This is an error union type: Type?ErrorType1, ErrorType2
            type->isFallible = true;
            
            // Parse the first error type
            std::string errorType = consume(TokenType::IDENTIFIER, "Expected error type after '?'.").lexeme;
            type->errorTypes.push_back(errorType);
            
            // Parse additional error types separated by commas
            while (match({TokenType::COMMA})) {
                std::string additionalErrorType = consume(TokenType::IDENTIFIER, "Expected error type after ','.").lexeme;
                type->errorTypes.push_back(additionalErrorType);
            }
        } else {
            // This is a simple optional type: Type?
            type->isOptional = true;
        }
    }

    return type;
}

// Parse brace type - either dictionary {keyType: valueType} or structural {field: type, ...}
std::shared_ptr<AST::TypeAnnotation> CSTParser::parseBraceType() {
    // Look ahead to determine if this is a dictionary type or structural type
    size_t savedCurrent = current;
    bool isDictionary = false;
    
    // Check the pattern to distinguish dictionary from structural type
    if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
        Token firstToken = peek();
        advance();
        
        if (match({TokenType::COLON})) {
            // We have a colon, check what comes after
            // Dictionary types can have complex value types like [int] or {str: int}
            if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type) || 
                check(TokenType::LEFT_BRACKET) || check(TokenType::LEFT_BRACE)) {
                
                // If the first token is a primitive type, it's likely a dictionary
                if (isPrimitiveType(firstToken.type)) {
                    isDictionary = true;
                } else {
                    // For identifiers, check if it's a known type name
                    if (isKnownTypeName(firstToken.lexeme)) {
                        isDictionary = true;
                    } else {
                        // Look at the value type to make a decision
                        if (check(TokenType::LEFT_BRACKET) || check(TokenType::LEFT_BRACE) ||
                            isPrimitiveType(peek().type) || isKnownTypeName(peek().lexeme)) {
                            isDictionary = true;
                        }
                    }
                }
            }
        }
    }
    
    // Reset parser position
    current = savedCurrent;
    
    if (isDictionary) {
        return parseDictionaryType();
    } else {
        return parseStructuralType();
    }
}

// Parse dictionary type {keyType: valueType}
std::shared_ptr<AST::TypeAnnotation> CSTParser::parseDictionaryType() {
    auto type = std::make_shared<AST::TypeAnnotation>();
    type->isDict = true;
    type->typeName = "dict";
    
    // Parse key type
    auto keyType = parseBasicType();
    consume(TokenType::COLON, "Expected ':' in dictionary type.");
    
    // Parse value type
    auto valueType = parseBasicType();
    
    type->keyType = keyType;
    type->valueType = valueType;
    
    consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
    return type;
}

// Helper method to check if a lexeme is a known type name
bool CSTParser::isKnownTypeName(const std::string& name) {
    return name == "any" || name == "str" || name == "int" || name == "float" || 
           name == "bool" || name == "list" || name == "dict" || name == "option" || 
           name == "result";
}

// Parse structural type (e.g., { name: str, age: int, ...baseRecord })
std::shared_ptr<AST::TypeAnnotation> CSTParser::parseStructuralType(const std::string& typeName) {
    auto type = std::make_shared<AST::TypeAnnotation>();
    type->isStructural = true;
    type->typeName = typeName.empty() ? "struct" : typeName;

    // Parse fields until we hit a closing brace
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // Check for rest parameter (...) or extensible record (...baseRecord)
        if (match({TokenType::ELLIPSIS})) {
            type->hasRest = true;
            
            // Check if there's a base record identifier after ...
            if (check(TokenType::IDENTIFIER)) {
                // This is an extensible record with a base record
                std::string baseRecordName = consume(TokenType::IDENTIFIER, "Expected base record name after '...'.").lexeme;
                
                // Store the base record name
                if (type->baseRecord.empty()) {
                    type->baseRecord = baseRecordName;
                }
                
                // Also add to the list of base records for multiple inheritance
                type->baseRecords.push_back(baseRecordName);
            }
            
            // Check for comma to continue with more fields
            if (check(TokenType::COMMA)) {
                consume(TokenType::COMMA, "Expected ',' after rest parameter.");
                continue;
            } else if (check(TokenType::RIGHT_BRACE)) {
                // End of record definition
                break;
            } else {
                error("Expected ',' or '}' after rest parameter.");
            }
        }

        // Parse field name
        std::string fieldName;
        if (check(TokenType::IDENTIFIER)) {
            fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
        } else if (check(TokenType::STRING)) {
            // Handle string literals as field names (e.g., { "kind": "Some" })
            Token stringToken = consume(TokenType::STRING, "Expected field name.");
            fieldName = stringToken.lexeme;
            // Remove quotes if present
            if (fieldName.size() >= 2 && (fieldName[0] == '"' || fieldName[0] == '\'') && 
                (fieldName[fieldName.size()-1] == '"' || fieldName[fieldName.size()-1] == '\'')) {
                fieldName = fieldName.substr(1, fieldName.size() - 2);
            }
        } else {
            error("Expected field name.");
            break;
        }

        // Parse field type
        consume(TokenType::COLON, "Expected ':' after field name.");
        auto fieldType = parseBasicType();

        // Add field to structural type
        type->structuralFields.push_back({fieldName, fieldType});

        // Check for comma or end of struct
        if (!check(TokenType::RIGHT_BRACE)) {
            match({TokenType::COMMA}); // Optional comma
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after structural type.");
    return type;
}
// Error pattern parsing methods

// Parse val pattern: val identifier
std::shared_ptr<AST::Expression> CSTParser::parseValPattern() {
    auto pattern = std::make_shared<AST::ValPatternExpr>();
    pattern->line = peek().line;
    
    consume(TokenType::VAL, "Expected 'val' keyword.");
    pattern->variableName = consume(TokenType::IDENTIFIER, "Expected variable name after 'val'.").lexeme;
    
    return pattern;
}

// Parse err pattern: err identifier or err ErrorType
std::shared_ptr<AST::Expression> CSTParser::parseErrPattern() {
    auto pattern = std::make_shared<AST::ErrPatternExpr>();
    pattern->line = peek().line;
    
    consume(TokenType::ERR, "Expected 'err' keyword.");
    
    // Check if this is a specific error type pattern or generic error pattern
    if (check(TokenType::IDENTIFIER)) {
        std::string identifier = consume(TokenType::IDENTIFIER, "Expected identifier after 'err'.").lexeme;
        
        // Check if this identifier is an error type or a variable name
        if (isErrorType(identifier)) {
            // This is a specific error type pattern: err ErrorType
            pattern->errorType = identifier;
            pattern->variableName = identifier; // Use error type as variable name by default
        } else {
            // This is a generic error pattern: err variable
            pattern->variableName = identifier;
        }
    } else {
        error("Expected identifier after 'err'.");
    }
    
    return pattern;
}

// Parse specific error type pattern: ErrorType or ErrorType(params)
std::shared_ptr<AST::Expression> CSTParser::parseErrorTypePattern() {
    auto pattern = std::make_shared<AST::ErrorTypePatternExpr>();
    pattern->line = peek().line;
    
    pattern->errorType = consume(TokenType::IDENTIFIER, "Expected error type name.").lexeme;
    
    // Check for parameter extraction: ErrorType(param1, param2, ...)
    if (match({TokenType::LEFT_PAREN})) {
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                std::string paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                pattern->parameterNames.push_back(paramName);
            } while (match({TokenType::COMMA}));
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after error type parameters.");
    }
    
    return pattern;
}

// Helper method to check if an identifier is an error type
bool CSTParser::isErrorType(const std::string& name) {
    // Built-in error types
    return name == "DivisionByZero" || name == "IndexOutOfBounds" || 
           name == "NullReference" || name == "TypeConversion" || 
           name == "IOError" || name == "ParseError" || name == "NetworkError" ||
           name == "Error"; // Generic error type
}


// Block context tracking methods implementation

void CSTParser::pushBlockContext(const std::string& blockType, const Token& startToken) {
    ErrorHandling::BlockContext context(blockType, startToken.line, startToken.start, startToken.lexeme);
    blockStack.push(context);
}

void CSTParser::popBlockContext() {
    if (!blockStack.empty()) {
        blockStack.pop();
    }
}

std::optional<ErrorHandling::BlockContext> CSTParser::getCurrentBlockContext() const {
    if (blockStack.empty()) {
        return std::nullopt;
    }
    return blockStack.top();
}

std::string CSTParser::generateCausedByMessage(const ErrorHandling::BlockContext& context) const {
    std::string message = "Caused by: Unterminated " + context.blockType + " starting at line " + 
                         std::to_string(context.startLine) + ":";
    message += "\n" + std::to_string(context.startLine) + " | " + context.startLexeme;
    if (context.blockType == "function" || context.blockType == "class") {
        message += " - unclosed " + context.blockType + " starts here";
    } else {
        message += " - unclosed block starts here";
    }
    

    
    return message;
}

std::shared_ptr<AST::Statement> CSTParser::parseStatementWithContext(const std::string& blockType, const Token& contextToken) {
    if (check(TokenType::LEFT_BRACE)) {
        pushBlockContext(blockType, contextToken);
        auto stmt = statement();
        popBlockContext();
        return stmt;
    } else {
        return statement();
    }
}

// Parse lambda expression: fn(param1, param2): returnType {body}
std::shared_ptr<AST::LambdaExpr> CSTParser::lambdaExpression() {
    auto lambda = std::make_shared<AST::LambdaExpr>();
    lambda->line = peek().line;
    
    // Consume 'fn'
    consume(TokenType::FN, "Expected 'fn' at start of lambda expression.");
    
    // Consume opening (
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'fn'.");
    
    // Parse parameters
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            std::string paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
            
            // Check for type annotation
            std::shared_ptr<AST::TypeAnnotation> paramType = nullptr;
            if (match({TokenType::COLON})) {
                paramType = parseTypeAnnotation();
            }
            
            lambda->params.push_back({paramName, paramType});
        } while (match({TokenType::COMMA}));
    }
    
    // Consume closing )
    consume(TokenType::RIGHT_PAREN, "Expected ')' after lambda parameters.");
    
    // Check for return type annotation
    if (match({TokenType::COLON})) {
        lambda->returnType = parseTypeAnnotation();
    }
    
    // Parse lambda body (block statement)
    consume(TokenType::LEFT_BRACE, "Expected '{' before lambda body.");
    
    auto lambdaBody = std::make_shared<AST::BlockStatement>();
    lambdaBody->line = previous().line;
    
    // Parse statements in the lambda body
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        lambdaBody->statements.push_back(declaration());
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}' after lambda body.");
    lambda->body = lambdaBody;
    
    return lambda;
}
