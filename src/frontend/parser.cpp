#include "parser.hh"
#include "../common/debugger.hh"
#include <stdexcept>
#include <limits>
#include <set>
#include <cmath>

// Helper methods
Token Parser::peek() {
    return scanner.getTokens()[current];
}

Token Parser::previous() {
    return scanner.getTokens()[current - 1];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::EOF_TOKEN;
}

Token Parser::consume(TokenType type, const std::string &message) {
    if (check(type)) return advance();
    error(message);
    throw std::runtime_error(message);
}

void Parser::synchronize() {
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

void Parser::error(const std::string &message, bool suppressException) {
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

// String parsing helper - removes quotes and processes escape sequences
std::string Parser::parseStringLiteral(const std::string& tokenLexeme) {
    if (tokenLexeme.length() < 2) {
        return tokenLexeme; // Invalid string, return as-is
    }
    
    // Remove surrounding quotes
    char quoteChar = tokenLexeme[0];
    if ((quoteChar != '"' && quoteChar != '\'') || tokenLexeme.back() != quoteChar) {
        return tokenLexeme; // Not a properly quoted string, return as-is
    }
    
    std::string result;
    std::string content = tokenLexeme.substr(1, tokenLexeme.length() - 2); // Remove quotes
    
    // Process escape sequences
    for (size_t i = 0; i < content.length(); ++i) {
        if (content[i] == '\\' && i + 1 < content.length()) {
            char nextChar = content[i + 1];
            switch (nextChar) {
                case 'n': result += '\n'; i++; break;
                case 't': result += '\t'; i++; break;
                case 'r': result += '\r'; i++; break;
                case '\\': result += '\\'; i++; break;
                case '\'': result += '\''; i++; break;
                case '\"': result += '\"'; i++; break;
                case '0': result += '\0'; i++; break;
                case 'a': result += '\a'; i++; break;
                case 'b': result += '\b'; i++; break;
                case 'f': result += '\f'; i++; break;
                case 'v': result += '\v'; i++; break;
                default:
                    // Unknown escape sequence, keep the backslash
                    result += content[i];
                    break;
            }
        } else {
            result += content[i];
        }
    }
    
    return result;
}

// Unified node creation helper - creates CST::Node or AST::Node based on cstMode
template<typename ASTNodeType>
auto Parser::createNode() -> std::conditional_t<std::is_same_v<ASTNodeType, AST::Program>, 
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
        
        // Add to current parent context
        CST::Node* rawCstNode = cstNode.get(); // Keep reference before moving
        addChildToCurrentContext(std::move(cstNode));
        
        // Store CST node reference for trivia attachment (but node is now in tree)
        currentNode = std::unique_ptr<CST::Node>(nullptr); // Reset since we moved it
        
        // Increment counter for testing
        cstNodeCount++;
        
        return astNode;
    } else {
        // Legacy AST mode - just create AST node
        return std::make_shared<ASTNodeType>();
    }
}

// Enhanced node creation with context management
template<typename ASTNodeType>
auto Parser::createNodeWithContext() -> std::conditional_t<std::is_same_v<ASTNodeType, AST::Program>, 
                                                          std::shared_ptr<AST::Program>,
                                                          std::shared_ptr<ASTNodeType>> {
    if (cstMode) {
        // Create AST node
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
        
        // Add to current parent context instead of root
        CST::Node* rawCstNode = cstNode.get(); // Keep reference before moving
        addChildToCurrentContext(std::move(cstNode));
        
        // Set this node as current context for its children (if it's a container node)
        if (isContainerNode(cstKind)) {
            pushCSTContext(rawCstNode);
        }
        
        // Store CST node for trivia attachment
        currentNode = std::unique_ptr<CST::Node>(nullptr); // Reset since we moved it
        
        // Increment counter for testing
        cstNodeCount++;
        
        return astNode;
    } else {
        // Legacy AST mode - just create AST node
        return std::make_shared<ASTNodeType>();
    }
}

// AST to CST NodeKind mapping
CST::NodeKind Parser::mapASTNodeKind(const std::string& astNodeType) {
    // Extract class name from mangled type name
    std::string className = astNodeType;
    
    // Simple mapping based on common patterns
    if (className.find("Program") != std::string::npos) return CST::NodeKind::PROGRAM;
    if (className.find("VarDeclaration") != std::string::npos) return CST::NodeKind::VAR_DECLARATION;
    if (className.find("DestructuringDeclaration") != std::string::npos) return CST::NodeKind::VAR_DECLARATION; // Use same CST kind as VarDeclaration
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
    if (className.find("ParallelStatement") != std::string::npos) return CST::NodeKind::PARALLEL_STATEMENT;
    if (className.find("ConcurrentStatement") != std::string::npos) return CST::NodeKind::CONCURRENT_STATEMENT;
    if (className.find("ContractStatement") != std::string::npos) return CST::NodeKind::CONTRACT_STATEMENT;
    if (className.find("MatchStatement") != std::string::npos) return CST::NodeKind::MATCH_STATEMENT;
    
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
    if (className.find("ThisExpr") != std::string::npos) return CST::NodeKind::VARIABLE_EXPR;
    if (className.find("SuperExpr") != std::string::npos) return CST::NodeKind::VARIABLE_EXPR;
    
    // Default to error node if mapping not found
    return CST::NodeKind::ERROR_NODE;
}

// Token consumption with trivia tracking
Token Parser::consumeWithTrivia(TokenType type, const std::string &message) {
    Token token = consume(type, message);
    attachTriviaFromToken(token);
    return token;
}

Token Parser::advanceWithTrivia() {
    Token token = advance();
    attachTriviaFromToken(token);
    return token;
}

// Trivia attachment helpers
void Parser::attachTriviaFromToken(const Token& token) {
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

void Parser::attachTriviaFromTokens(const std::vector<Token>& tokens) {
    if (cstMode && std::holds_alternative<std::unique_ptr<CST::Node>>(currentNode)) {
        auto& cstNode = std::get<std::unique_ptr<CST::Node>>(currentNode);
        if (cstNode) {
            for (const auto& token : tokens) {
                cstNode->addToken(token);
            }
        }
    }
}

// CST context management methods
void Parser::pushCSTContext(CST::Node* parent) {
    if (cstMode && parent) {
        cstContextStack.push(parent);
    }
}

void Parser::popCSTContext() {
    if (cstMode && !cstContextStack.empty()) {
        cstContextStack.pop();
    }
}

CST::Node* Parser::getCurrentCSTParent() {
    if (cstMode && !cstContextStack.empty()) {
        return cstContextStack.top();
    }
    // If no context is set, return the root node
    return cstRoot.get();
}

void Parser::addChildToCurrentContext(std::unique_ptr<CST::Node> child) {
    if (cstMode && child) {
        CST::Node* parent = getCurrentCSTParent();
        if (parent) {
            parent->addChild(std::move(child));
        }
    }
}

bool Parser::isContainerNode(CST::NodeKind kind) {
    switch (kind) {
        case CST::NodeKind::PROGRAM:
        case CST::NodeKind::BLOCK_STATEMENT:
        case CST::NodeKind::IF_STATEMENT:
        case CST::NodeKind::FOR_STATEMENT:
        case CST::NodeKind::WHILE_STATEMENT:
        case CST::NodeKind::ITER_STATEMENT:
        case CST::NodeKind::FUNCTION_DECLARATION:
        case CST::NodeKind::CLASS_DECLARATION:
        case CST::NodeKind::MATCH_STATEMENT:
        case CST::NodeKind::PARALLEL_STATEMENT:
        case CST::NodeKind::CONCURRENT_STATEMENT:
            return true;
        default:
            return false;
    }
}

// Explicit template instantiations for common AST node types
template auto Parser::createNode<AST::Program>() -> std::shared_ptr<AST::Program>;
template auto Parser::createNode<AST::VarDeclaration>() -> std::shared_ptr<AST::VarDeclaration>;
template auto Parser::createNode<AST::DestructuringDeclaration>() -> std::shared_ptr<AST::DestructuringDeclaration>;
template auto Parser::createNode<AST::FunctionDeclaration>() -> std::shared_ptr<AST::FunctionDeclaration>;
template auto Parser::createNode<AST::ClassDeclaration>() -> std::shared_ptr<AST::ClassDeclaration>;
template auto Parser::createNode<AST::IfStatement>() -> std::shared_ptr<AST::IfStatement>;
template auto Parser::createNode<AST::ForStatement>() -> std::shared_ptr<AST::ForStatement>;
template auto Parser::createNode<AST::WhileStatement>() -> std::shared_ptr<AST::WhileStatement>;
template auto Parser::createNode<AST::IterStatement>() -> std::shared_ptr<AST::IterStatement>;
template auto Parser::createNode<AST::BlockStatement>() -> std::shared_ptr<AST::BlockStatement>;
template auto Parser::createNode<AST::ExprStatement>() -> std::shared_ptr<AST::ExprStatement>;
template auto Parser::createNode<AST::ReturnStatement>() -> std::shared_ptr<AST::ReturnStatement>;
template auto Parser::createNode<AST::PrintStatement>() -> std::shared_ptr<AST::PrintStatement>;
template auto Parser::createNode<AST::ContractStatement>() -> std::shared_ptr<AST::ContractStatement>;
template auto Parser::createNode<AST::MatchStatement>() -> std::shared_ptr<AST::MatchStatement>;
template auto Parser::createNode<AST::ConcurrentStatement>() -> std::shared_ptr<AST::ConcurrentStatement>;
template auto Parser::createNode<AST::ParallelStatement>() -> std::shared_ptr<AST::ParallelStatement>;
template auto Parser::createNode<AST::BinaryExpr>() -> std::shared_ptr<AST::BinaryExpr>;
template auto Parser::createNode<AST::UnaryExpr>() -> std::shared_ptr<AST::UnaryExpr>;
template auto Parser::createNode<AST::LiteralExpr>() -> std::shared_ptr<AST::LiteralExpr>;
template auto Parser::createNode<AST::ObjectLiteralExpr>() -> std::shared_ptr<AST::ObjectLiteralExpr>;
template auto Parser::createNode<AST::VariableExpr>() -> std::shared_ptr<AST::VariableExpr>;
template auto Parser::createNode<AST::CallExpr>() -> std::shared_ptr<AST::CallExpr>;
template auto Parser::createNode<AST::AssignExpr>() -> std::shared_ptr<AST::AssignExpr>;
template auto Parser::createNode<AST::GroupingExpr>() -> std::shared_ptr<AST::GroupingExpr>;
template auto Parser::createNode<AST::MemberExpr>() -> std::shared_ptr<AST::MemberExpr>;
template auto Parser::createNode<AST::IndexExpr>() -> std::shared_ptr<AST::IndexExpr>;
template auto Parser::createNode<AST::ThisExpr>() -> std::shared_ptr<AST::ThisExpr>;
template auto Parser::createNode<AST::SuperExpr>() -> std::shared_ptr<AST::SuperExpr>;

// Explicit template instantiations for createNodeWithContext
template auto Parser::createNodeWithContext<AST::Program>() -> std::shared_ptr<AST::Program>;
template auto Parser::createNodeWithContext<AST::VarDeclaration>() -> std::shared_ptr<AST::VarDeclaration>;
template auto Parser::createNodeWithContext<AST::DestructuringDeclaration>() -> std::shared_ptr<AST::DestructuringDeclaration>;
template auto Parser::createNodeWithContext<AST::FunctionDeclaration>() -> std::shared_ptr<AST::FunctionDeclaration>;
template auto Parser::createNodeWithContext<AST::ClassDeclaration>() -> std::shared_ptr<AST::ClassDeclaration>;
template auto Parser::createNodeWithContext<AST::IfStatement>() -> std::shared_ptr<AST::IfStatement>;
template auto Parser::createNodeWithContext<AST::ForStatement>() -> std::shared_ptr<AST::ForStatement>;
template auto Parser::createNodeWithContext<AST::WhileStatement>() -> std::shared_ptr<AST::WhileStatement>;
template auto Parser::createNodeWithContext<AST::IterStatement>() -> std::shared_ptr<AST::IterStatement>;
template auto Parser::createNodeWithContext<AST::BlockStatement>() -> std::shared_ptr<AST::BlockStatement>;
template auto Parser::createNodeWithContext<AST::ExprStatement>() -> std::shared_ptr<AST::ExprStatement>;
template auto Parser::createNodeWithContext<AST::ReturnStatement>() -> std::shared_ptr<AST::ReturnStatement>;
template auto Parser::createNodeWithContext<AST::PrintStatement>() -> std::shared_ptr<AST::PrintStatement>;
template auto Parser::createNodeWithContext<AST::ContractStatement>() -> std::shared_ptr<AST::ContractStatement>;
template auto Parser::createNodeWithContext<AST::MatchStatement>() -> std::shared_ptr<AST::MatchStatement>;
template auto Parser::createNodeWithContext<AST::ConcurrentStatement>() -> std::shared_ptr<AST::ConcurrentStatement>;
template auto Parser::createNodeWithContext<AST::ParallelStatement>() -> std::shared_ptr<AST::ParallelStatement>;
template auto Parser::createNodeWithContext<AST::LiteralExpr>() -> std::shared_ptr<AST::LiteralExpr>;
template auto Parser::createNodeWithContext<AST::VariableExpr>() -> std::shared_ptr<AST::VariableExpr>;
template auto Parser::createNodeWithContext<AST::GroupingExpr>() -> std::shared_ptr<AST::GroupingExpr>;
template auto Parser::createNodeWithContext<AST::ThisExpr>() -> std::shared_ptr<AST::ThisExpr>;
template auto Parser::createNodeWithContext<AST::SuperExpr>() -> std::shared_ptr<AST::SuperExpr>;

// Main parse method
std::shared_ptr<AST::Program> Parser::parse() {
    auto program = createNodeWithContext<AST::Program>();
    program->line = 1;

    // If in CST mode, create CST root for trivia reconstruction
    if (cstMode) {
        cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, scanner.getSource().size());
        cstRoot->setDescription("Program root node with trivia");
        
        // Initialize the context stack with the root as the initial parent
        pushCSTContext(cstRoot.get());
    }

    try {
        while (!isAtEnd()) {
            auto stmt = declaration();
            if (stmt) {
                program->statements.push_back(stmt);
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

    // In CST mode, we build a hierarchical structure with structured nodes
    // Individual tokens are added to their respective statement/expression nodes
    // No need to add all tokens to root since we have proper structure

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
                addChildToCurrentContext(std::move(errorNode));
            }
        }
    }
    
    return program;
}

// Parse declarations
// Helper to collect leading annotations
std::vector<Token> Parser::collectAnnotations() {
    std::vector<Token> annotations;
    while (check(TokenType::PUBLIC) || check(TokenType::PRIVATE) || check(TokenType::PROTECTED)) {
        // Note: PUB, PROT, STATIC, ABSTRACT, FINAL, and DATA are not collected as annotations
        // They are handled as visibility/class modifiers in the declaration() function
        annotations.push_back(advance());
    }
    return annotations;
}

void Parser::skipTrivia() {
    // Skip trivia tokens (whitespace, comments, newlines) in CST mode
    // These are handled separately and shouldn't interfere with parsing logic
    while (!isAtEnd() && 
           (check(TokenType::WHITESPACE) || 
            check(TokenType::NEWLINE) || 
            check(TokenType::COMMENT_LINE) || 
            check(TokenType::COMMENT_BLOCK))) {
        
        // In CST mode, we can collect these tokens for the CST tree
        if (cstMode && cstRoot) {
            Token triviaToken = advance();
            
            // Create appropriate trivia node and add to CST
            if (triviaToken.type == TokenType::WHITESPACE || triviaToken.type == TokenType::NEWLINE) {
                auto whitespaceNode = std::make_unique<CST::WhitespaceNode>(triviaToken);
                addChildToCurrentContext(std::move(whitespaceNode));
            } else if (triviaToken.type == TokenType::COMMENT_LINE || triviaToken.type == TokenType::COMMENT_BLOCK) {
                auto commentNode = std::make_unique<CST::CommentNode>(triviaToken);
                addChildToCurrentContext(std::move(commentNode));
            }
        } else {
            advance(); // Just skip the trivia token
        }
    }
}

std::shared_ptr<AST::Statement> Parser::declaration() {
    try {
        // Collect leading annotations
        std::vector<Token> annotations = collectAnnotations();
        
        // Parse modifiers for module-level declarations
        AST::VisibilityLevel visibility = AST::VisibilityLevel::Private; // Default to private
        bool isStatic = false;
        bool isAbstract = false;
        bool isFinal = false;
        bool isDataClass = false;
        
        // Parse visibility and modifiers
        while (check(TokenType::PUB) || check(TokenType::PROT) || check(TokenType::CONST) || 
               check(TokenType::STATIC) || check(TokenType::ABSTRACT) || check(TokenType::FINAL) || 
               check(TokenType::DATA)) {
            
            if (match({TokenType::PUB})) {
                visibility = AST::VisibilityLevel::Public;
            } else if (match({TokenType::PROT})) {
                visibility = AST::VisibilityLevel::Protected;
            } else if (match({TokenType::CONST})) {
                visibility = AST::VisibilityLevel::Const;
            } else if (match({TokenType::STATIC})) {
                isStatic = true;
            } else if (match({TokenType::ABSTRACT})) {
                isAbstract = true;
            } else if (match({TokenType::FINAL})) {
                isFinal = true;
            } else if (match({TokenType::DATA})) {
                isDataClass = true;
                isFinal = true; // Data classes are automatically final
            }
        }
        
        if (match({TokenType::CLASS})) {
            auto decl = classDeclaration();
            if (decl) {
                decl->annotations = annotations;
                decl->isAbstract = isAbstract;
                decl->isFinal = isFinal;
                decl->isDataClass = isDataClass;
            }
            return decl;
        }
        if (match({TokenType::FN})) {
            auto decl = function("function");
            if (decl) {
                decl->annotations = annotations;
                decl->visibility = visibility;
                decl->isStatic = isStatic;
                decl->isAbstract = isAbstract;
                decl->isFinal = isFinal;
            }
            return decl;
        }
        // if (match({TokenType::ASYNC})) {
        //     consume(TokenType::FN, "Expected 'fn' after 'async'.");
        //     auto asyncFn = std::make_shared<AST::AsyncFunctionDeclaration>(*function("async function"));
        //     asyncFn->annotations = annotations;
        //     asyncFn->visibility = visibility;
        //     asyncFn->isStatic = isStatic;
        //     asyncFn->isAbstract = isAbstract;
        //     asyncFn->isFinal = isFinal;
        //     return asyncFn;
        // }
        if (match({TokenType::VAR})) {
            auto decl = varDeclaration();
            if (decl) {
                decl->annotations = annotations;
                // Cast to VarDeclaration to access visibility fields
                if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(decl)) {
                    varDecl->visibility = visibility;
                    varDecl->isStatic = isStatic;
                }
            }
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

std::shared_ptr<AST::Statement> Parser::varDeclaration() {
    int line = previous().line;

    // Check for tuple destructuring: var (a, b, c) = tuple;
    if (check(TokenType::LEFT_PAREN)) {
        // This is tuple destructuring - create DestructuringDeclaration
        auto destructuring = std::make_shared<AST::DestructuringDeclaration>();
        destructuring->line = line;
        destructuring->isTuple = true;
        
        advance(); // consume '('
        
        // Parse variable names
        Token firstName = consume(TokenType::IDENTIFIER, "Expected variable name in tuple destructuring.");
        destructuring->names.push_back(firstName.lexeme);
        
        // Parse remaining variables
        while (match({TokenType::COMMA})) {
            Token varName = consume(TokenType::IDENTIFIER, "Expected variable name in tuple destructuring.");
            destructuring->names.push_back(varName.lexeme);
        }
        
        consume(TokenType::RIGHT_PAREN, "Expected ')' after tuple destructuring variables.");
        
        // Parse assignment
        consume(TokenType::EQUAL, "Expected '=' in tuple destructuring assignment.");
        destructuring->initializer = expression();
        
        // Make semicolon optional
        match({TokenType::SEMICOLON});
        
        return destructuring;
    }

    // Regular variable declaration
    auto var = createNodeWithContext<AST::VarDeclaration>();
    var->line = line;

    // Parse variable name
    Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
    var->name = name.lexeme;

    // Parse optional type annotation
    if (match({TokenType::COLON})) {
        var->type = parseTypeAnnotation();
    }

    // Parse optional initializer
    if (match({TokenType::EQUAL})) {
        var->initializer = expression();
    }

    // Make semicolon optional
    match({TokenType::SEMICOLON});
    
    return var;
}

std::shared_ptr<AST::Statement> Parser::statement() {
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

std::shared_ptr<AST::Statement> Parser::expressionStatement() {
    try {
        // Create expression statement using createNodeWithContext for proper CST support
        auto stmt = createNodeWithContext<AST::ExprStatement>();
        stmt->line = peek().line;
        
        // Parse the expression - this will be a child of the EXPRESSION_STATEMENT CST node
        auto expr = expression();
        stmt->expression = expr;
        
        // Make semicolon optional
        match({TokenType::SEMICOLON});
        
        return stmt;
    } catch (const std::exception &e) {
        // If we can't parse an expression, return an empty statement
        auto stmt = createNodeWithContext<AST::ExprStatement>();
        stmt->line = peek().line;
        stmt->expression = nullptr;
        return stmt;
    }
}

std::shared_ptr<AST::Statement> Parser::printStatement() {
    auto stmt = createNodeWithContext<AST::PrintStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'print'.");

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            stmt->arguments.push_back(expression());
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after print arguments.");
    
    // Make semicolon optional
    match({TokenType::SEMICOLON});
    
    return stmt;
}

std::shared_ptr<AST::Statement> Parser::taskStatement() {
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

std::shared_ptr<AST::Statement> Parser::workerStatement() {
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

std::shared_ptr<AST::Statement> Parser::traitDeclaration() {
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

std::shared_ptr<AST::Statement> Parser::interfaceDeclaration() {
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

std::shared_ptr<AST::Statement> Parser::moduleDeclaration() {
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

std::shared_ptr<AST::Statement> Parser::iterStatement() {
    auto stmt = createNodeWithContext<AST::IterStatement>();
    Token iterToken = previous();
    stmt->line = iterToken.line;

    // Get the current CST parent (should be the ITER_STATEMENT node we just created)
    CST::Node* iterCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        iterCSTNode = cstContextStack.top();
        if (iterCSTNode && iterCSTNode->kind == CST::NodeKind::ITER_STATEMENT) {
            iterCSTNode->setDescription("iter statement");
            iterCSTNode->addToken(iterToken);
        }
    }

    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'iter'.");
    if (cstMode && iterCSTNode) {
        iterCSTNode->addToken(leftParen);
    }

    // Parse loop variables
    if (match({TokenType::VAR})) {
        // Variable declaration in loop
        Token varToken = previous();
        if (cstMode && iterCSTNode) {
            iterCSTNode->addToken(varToken);
        }
        
        Token name = consumeWithTrivia(TokenType::IDENTIFIER, "Expected variable name.");
        stmt->loopVars.push_back(name.lexeme);
        if (cstMode && iterCSTNode) {
            iterCSTNode->addToken(name);
        }

        // Check for multiple variables (key, value)
        if (match({TokenType::COMMA})) {
            Token comma = previous();
            if (cstMode && iterCSTNode) {
                iterCSTNode->addToken(comma);
            }
            
            Token secondVar = consumeWithTrivia(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);
            if (cstMode && iterCSTNode) {
                iterCSTNode->addToken(secondVar);
            }
        }

        Token inToken = consumeWithTrivia(TokenType::IN, "Expected 'in' after loop variables.");
        if (cstMode && iterCSTNode) {
            iterCSTNode->addToken(inToken);
        }
        
        // Capture the current position before parsing iterable expression
        size_t iterableStart = current;
        stmt->iterable = expression();
        size_t iterableEnd = current;
        
        // Capture iterable tokens for CST
        if (cstMode && iterCSTNode) {
            for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) {
                iterCSTNode->addToken(scanner.getTokens()[i]);
            }
        }
    } else if (match({TokenType::IDENTIFIER})) {
        // Identifier directly
        Token firstVarToken = previous();
        std::string firstVar = firstVarToken.lexeme;
        stmt->loopVars.push_back(firstVar);
        if (cstMode && iterCSTNode) {
            iterCSTNode->addToken(firstVarToken);
        }

        // Check for multiple variables (key, value)
        if (match({TokenType::COMMA})) {
            Token comma = previous();
            if (cstMode && iterCSTNode) {
                iterCSTNode->addToken(comma);
            }
            
            Token secondVar = consumeWithTrivia(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);
            if (cstMode && iterCSTNode) {
                iterCSTNode->addToken(secondVar);
            }

            Token inToken = consumeWithTrivia(TokenType::IN, "Expected 'in' after loop variables.");
            if (cstMode && iterCSTNode) {
                iterCSTNode->addToken(inToken);
            }
            
            // Capture the current position before parsing iterable expression
            size_t iterableStart = current;
            stmt->iterable = expression();
            size_t iterableEnd = current;
            
            // Capture iterable tokens for CST
            if (cstMode && iterCSTNode) {
                for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) {
                    iterCSTNode->addToken(scanner.getTokens()[i]);
                }
            }
        } else if (match({TokenType::IN})) {
            Token inToken = previous();
            if (cstMode && iterCSTNode) {
                iterCSTNode->addToken(inToken);
            }
            
            // Capture the current position before parsing iterable expression
            size_t iterableStart = current;
            stmt->iterable = expression();
            size_t iterableEnd = current;
            
            // Capture iterable tokens for CST
            if (cstMode && iterCSTNode) {
                for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) {
                    iterCSTNode->addToken(scanner.getTokens()[i]);
                }
            }
        } else {
            error("Expected 'in' after loop variable.");
        }
    } else {
        error("Expected variable name or identifier after 'iter ('.");
    }

    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after iter clauses.");
    if (cstMode && iterCSTNode) {
        iterCSTNode->addToken(rightParen);
    }

    // Parse loop body with context
    stmt->body = parseStatementWithContext("iter", iterToken);

    // Pop CST context when exiting iter statement
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::breakStatement() {
    auto stmt = std::make_shared<AST::BreakStatement>();
    stmt->line = previous().line;
    consume(TokenType::SEMICOLON, "Expected ';' after 'break'.");
    return stmt;
}

std::shared_ptr<AST::Statement> Parser::continueStatement() {
    auto stmt = std::make_shared<AST::ContinueStatement>();
    stmt->line = previous().line;
    consume(TokenType::SEMICOLON, "Expected ';' after 'continue'.");
    return stmt;
}

std::shared_ptr<AST::Statement> Parser::unsafeBlock() {
    auto stmt = std::make_shared<AST::UnsafeStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_BRACE, "Expected '{' after 'unsafe'.");
    stmt->body = block();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::contractStatement() {
    auto stmt = createNodeWithContext<AST::ContractStatement>();
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

std::shared_ptr<AST::Statement> Parser::comptimeStatement() {
    auto stmt = std::make_shared<AST::ComptimeStatement>();
    stmt->line = previous().line;

    // Parse the declaration that should be evaluated at compile time
    stmt->declaration = declaration();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::ifStatement() {
    auto stmt = createNodeWithContext<AST::IfStatement>();
    Token ifToken = previous();
    stmt->line = ifToken.line;

    // Get the current CST parent (should be the IF_STATEMENT node we just created)
    CST::Node* ifCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        ifCSTNode = cstContextStack.top();
        if (ifCSTNode && ifCSTNode->kind == CST::NodeKind::IF_STATEMENT) {
            ifCSTNode->setDescription("if statement");
            ifCSTNode->addToken(ifToken);
        }
    }

    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
    if (cstMode && ifCSTNode) {
        ifCSTNode->addToken(leftParen);
    }
    
    // Capture the current position before parsing condition expression
    size_t conditionStart = current;
    stmt->condition = expression();
    size_t conditionEnd = current;
    
    // Add all tokens consumed by the condition expression to the CST node
    if (cstMode && ifCSTNode) {
        const auto& tokens = scanner.getTokens();
        for (size_t i = conditionStart; i < conditionEnd; ++i) {
            if (i < tokens.size()) {
                ifCSTNode->addToken(tokens[i]);
            }
        }
    }
    
    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after if condition.");
    if (cstMode && ifCSTNode) {
        ifCSTNode->addToken(rightParen);
    }

    stmt->thenBranch = parseStatementWithContext("if", ifToken);

    // Handle elif chains
    while (match({TokenType::ELIF})) {
        Token elifToken = previous();
        
        // Create a nested if statement for the elif with proper CST context
        auto elifStmt = createNodeWithContext<AST::IfStatement>();
        elifStmt->line = elifToken.line;
        
        // Get the elif CST node that was just created
        CST::Node* elifCSTNode = nullptr;
        if (cstMode && !cstContextStack.empty()) {
            elifCSTNode = cstContextStack.top();
            if (elifCSTNode && elifCSTNode->kind == CST::NodeKind::IF_STATEMENT) {
                elifCSTNode->setDescription("elif statement");
                elifCSTNode->addToken(elifToken);
            }
        }
        
        Token elifLeftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'elif'.");
        if (cstMode && elifCSTNode) {
            elifCSTNode->addToken(elifLeftParen);
        }
        
        // Capture the current position before parsing elif condition expression
        size_t elifConditionStart = current;
        elifStmt->condition = expression();
        size_t elifConditionEnd = current;
        
        // Add all tokens consumed by the elif condition expression to the CST node
        if (cstMode && elifCSTNode) {
            const auto& tokens = scanner.getTokens();
            for (size_t i = elifConditionStart; i < elifConditionEnd; ++i) {
                if (i < tokens.size()) {
                    elifCSTNode->addToken(tokens[i]);
                }
            }
        }
        
        Token elifRightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after elif condition.");
        if (cstMode && elifCSTNode) {
            elifCSTNode->addToken(elifRightParen);
        }
        
        elifStmt->thenBranch = parseStatementWithContext("elif", elifToken);
        
        // Pop the elif CST context since we're done parsing its contents
        if (cstMode && elifCSTNode && elifCSTNode->kind == CST::NodeKind::IF_STATEMENT) {
            popCSTContext();
        }
        
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
        if (cstMode && ifCSTNode) {
            ifCSTNode->addToken(elseToken);
        }
        
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

    // Pop the IF_STATEMENT context since we're done parsing its contents
    if (cstMode && ifCSTNode && ifCSTNode->kind == CST::NodeKind::IF_STATEMENT) {
        popCSTContext();
    }

    return stmt;
}

std::shared_ptr<AST::BlockStatement> Parser::block() {
    // Use createNode instead of createNodeWithContext for manual context management
    auto block = createNodeWithContext<AST::BlockStatement>();
    Token leftBrace = previous();
    block->line = leftBrace.line;
    
    // Create BLOCK_STATEMENT CST node and set it as parent context
    CST::Node* blockCSTNode = nullptr;
    if (cstMode) {
        // Create CST node for this block statement
        auto cstNode = std::make_unique<CST::Node>(CST::NodeKind::BLOCK_STATEMENT, leftBrace.start, 0);
        cstNode->setDescription("block statement");
        
        // Add opening brace token to CST node
        cstNode->addToken(leftBrace);
        
        // Keep reference before moving
        blockCSTNode = cstNode.get();
        
        // Add to current parent context
        addChildToCurrentContext(std::move(cstNode));
        
        // Set this block as the current parent context for its child statements
        pushCSTContext(blockCSTNode);
    }

    // Handle empty blocks
    if (check(TokenType::RIGHT_BRACE)) {
        Token rightBrace = consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
        if (cstMode && blockCSTNode) {
            blockCSTNode->addToken(rightBrace);
            blockCSTNode->endPos = rightBrace.end;
            popCSTContext();
        }
        return block;
    }

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        try {
            if (in_concurrent_block) {
                // bool is_async = match({TokenType::ASYNC});
                bool is_async = false; // Temporarily disabled async support
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
            // Parse declarations - they will be automatically added as children 
            // of the current CST context (this block) by the declaration methods
            auto declaration = this->declaration();
            if (declaration) {
                block->statements.push_back(declaration);
            }
        } catch (const std::exception &e) {
            // Skip invalid statements and continue parsing
            synchronize();
        }
    }

    Token rightBrace = consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
    if (cstMode && blockCSTNode) {
        // Add closing brace token to CST node
        blockCSTNode->addToken(rightBrace);
        blockCSTNode->endPos = rightBrace.end;
        
        // Pop this block from the context stack
        popCSTContext();
    }
    return block;
}

std::shared_ptr<AST::Statement> Parser::forStatement() {
    auto stmt = createNodeWithContext<AST::ForStatement>();
    Token forToken = previous();
    stmt->line = forToken.line;

    // Get the current CST parent (should be the FOR_STATEMENT node we just created)
    CST::Node* forCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        forCSTNode = cstContextStack.top();
        if (forCSTNode && forCSTNode->kind == CST::NodeKind::FOR_STATEMENT) {
            forCSTNode->setDescription("for statement");
            forCSTNode->addToken(forToken);
        }
    }

    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'for'.");
    if (cstMode && forCSTNode) {
        forCSTNode->addToken(leftParen);
    }

    // Check for the type of for loop
    if (match({TokenType::VAR})) {
        // Could be either traditional or iterable loop
        Token varToken = previous();
        if (cstMode && forCSTNode) {
            forCSTNode->addToken(varToken);
        }
        
        Token name = consumeWithTrivia(TokenType::IDENTIFIER, "Expected variable name.");
        if (cstMode && forCSTNode) {
            forCSTNode->addToken(name);
        }

        if (match({TokenType::IN})) {
            // Iterable loop: for (var i in range(10))
            Token inToken = previous();
            if (cstMode && forCSTNode) {
                forCSTNode->addToken(inToken);
            }
            
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(name.lexeme);
            
            // Capture the current position before parsing iterable expression
            size_t iterableStart = current;
            stmt->iterable = expression();
            size_t iterableEnd = current;
            
            // Capture iterable tokens for CST
            if (cstMode && forCSTNode) {
                for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) {
                    forCSTNode->addToken(scanner.getTokens()[i]);
                }
            }
        } else {
            // Traditional loop: for (var i = 0; i < 5; i++)
            auto initializer = std::make_shared<AST::VarDeclaration>();
            initializer->line = name.line;
            initializer->name = name.lexeme;

            // Parse optional type annotation
            if (match({TokenType::COLON})) {
                Token colon = previous();
                if (cstMode && forCSTNode) {
                    forCSTNode->addToken(colon);
                }
                initializer->type = parseTypeAnnotation();
            }

            // Parse initializer
            if (match({TokenType::EQUAL})) {
                Token equal = previous();
                if (cstMode && forCSTNode) {
                    forCSTNode->addToken(equal);
                }
                
                // Capture the current position before parsing initializer expression
                size_t initStart = current;
                initializer->initializer = expression();
                size_t initEnd = current;
                
                // Capture initializer tokens for CST
                if (cstMode && forCSTNode) {
                    for (size_t i = initStart; i < initEnd && i < scanner.getTokens().size(); i++) {
                        forCSTNode->addToken(scanner.getTokens()[i]);
                    }
                }
            }

            stmt->initializer = initializer;

            Token semicolon1 = consumeWithTrivia(TokenType::SEMICOLON, "Expected ';' after loop initializer.");
            if (cstMode && forCSTNode) {
                forCSTNode->addToken(semicolon1);
            }

            // Parse condition
            if (!check(TokenType::SEMICOLON)) {
                // Capture the current position before parsing condition expression
                size_t conditionStart = current;
                stmt->condition = expression();
                size_t conditionEnd = current;
                
                // Capture condition tokens for CST
                if (cstMode && forCSTNode) {
                    for (size_t i = conditionStart; i < conditionEnd && i < scanner.getTokens().size(); i++) {
                        forCSTNode->addToken(scanner.getTokens()[i]);
                    }
                }
            }

            Token semicolon2 = consumeWithTrivia(TokenType::SEMICOLON, "Expected ';' after loop condition.");
            if (cstMode && forCSTNode) {
                forCSTNode->addToken(semicolon2);
            }

            // Parse increment
            if (!check(TokenType::RIGHT_PAREN)) {
                // Capture the current position before parsing increment expression
                size_t incrementStart = current;
                stmt->increment = expression();
                size_t incrementEnd = current;
                
                // Capture increment tokens for CST
                if (cstMode && forCSTNode) {
                    for (size_t i = incrementStart; i < incrementEnd && i < scanner.getTokens().size(); i++) {
                        forCSTNode->addToken(scanner.getTokens()[i]);
                    }
                }
            }
        }
    } else if (match({TokenType::IDENTIFIER})) {
        // Check if it's an iterable loop with multiple variables
        Token firstVarToken = previous();
        std::string firstVar = firstVarToken.lexeme;
        if (cstMode && forCSTNode) {
            forCSTNode->addToken(firstVarToken);
        }

        if (match({TokenType::COMMA})) {
            // Multiple variables: for (key, value in dict)
            Token comma = previous();
            if (cstMode && forCSTNode) {
                forCSTNode->addToken(comma);
            }
            
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(firstVar);

            Token secondVar = consumeWithTrivia(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);
            if (cstMode && forCSTNode) {
                forCSTNode->addToken(secondVar);
            }

            Token inToken = consumeWithTrivia(TokenType::IN, "Expected 'in' after loop variables.");
            if (cstMode && forCSTNode) {
                forCSTNode->addToken(inToken);
            }
            // Capture the current position before parsing iterable expression
            size_t iterableStart = current;
            stmt->iterable = expression();
            size_t iterableEnd = current;
            
            // Capture iterable tokens for CST
            if (cstMode && forCSTNode) {
                for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) {
                    forCSTNode->addToken(scanner.getTokens()[i]);
                }
            }
        } else if (match({TokenType::IN})) {
            // Single variable: for (key in list)
            Token inToken = previous();
            if (cstMode && forCSTNode) {
                forCSTNode->addToken(inToken);
            }
            
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(firstVar);
            
            // Capture the current position before parsing iterable expression
            size_t iterableStart = current;
            stmt->iterable = expression();
            size_t iterableEnd = current;
            
            // Capture iterable tokens for CST
            if (cstMode && forCSTNode) {
                for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) {
                    forCSTNode->addToken(scanner.getTokens()[i]);
                }
            }
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

    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after for clauses.");
    if (cstMode && forCSTNode) {
        forCSTNode->addToken(rightParen);
    }
    
    stmt->body = parseStatementWithContext("for", forToken);

    // Pop CST context when exiting for statement
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::whileStatement() {
    auto stmt = createNodeWithContext<AST::WhileStatement>();
    Token whileToken = previous();
    stmt->line = whileToken.line;

    // Get the current CST parent (should be the WHILE_STATEMENT node we just created)
    CST::Node* whileCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        whileCSTNode = cstContextStack.top();
        if (whileCSTNode && whileCSTNode->kind == CST::NodeKind::WHILE_STATEMENT) {
            whileCSTNode->setDescription("while statement");
            whileCSTNode->addToken(whileToken);
        }
    }

    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'while'.");
    if (cstMode && whileCSTNode) {
        whileCSTNode->addToken(leftParen);
    }
    
    // Capture the current position before parsing condition expression
    size_t conditionStart = current;
    stmt->condition = expression();
    size_t conditionEnd = current;
    
    // Capture condition tokens for CST
    if (cstMode && whileCSTNode) {
        for (size_t i = conditionStart; i < conditionEnd && i < scanner.getTokens().size(); i++) {
            whileCSTNode->addToken(scanner.getTokens()[i]);
        }
    }
    
    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after while condition.");
    if (cstMode && whileCSTNode) {
        whileCSTNode->addToken(rightParen);
    }

    stmt->body = parseStatementWithContext("while", whileToken);

    // Pop CST context when exiting while statement
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

    return stmt;
}

std::shared_ptr<AST::FunctionDeclaration> Parser::function(const std::string& kind) {
    auto func = createNodeWithContext<AST::FunctionDeclaration>();
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
    // if (match({TokenType::THROWS})) {
    //     func->throws = true;
    //     func->canFail = true;
    //     
    //     // Parse specific error types if provided
    //     if (!check(TokenType::LEFT_BRACE)) {
    //         do {
    //             Token errorType = consume(TokenType::IDENTIFIER, "Expected error type name after 'throws'.");
    //             func->declaredErrorTypes.push_back(errorType.lexeme);
    //         } while (match({TokenType::COMMA}));
    //     }
    // }

    // Parse function body (or semicolon for abstract methods)
    if (check(TokenType::SEMICOLON)) {
        // Abstract method - no body
        advance(); // consume ';'
        func->body = nullptr; // No body for abstract methods
    } else {
        // Regular method with body
        Token leftBrace = consume(TokenType::LEFT_BRACE, "Expected '{' before " + kind + " body.");
        pushBlockContext("function", leftBrace);
        func->body = block();
        popBlockContext();
    }

    // Pop CST context when exiting function declaration
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

    return func;
}

std::shared_ptr<AST::Statement> Parser::returnStatement() {
    auto stmt = std::make_shared<AST::ReturnStatement>();
    stmt->line = previous().line;

    if (!check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE)) {
        stmt->value = expression();
    }

    // Make semicolon optional
    match({TokenType::SEMICOLON});

    return stmt;
}

std::shared_ptr<AST::ClassDeclaration> Parser::classDeclaration() {
    auto classDecl = createNodeWithContext<AST::ClassDeclaration>();
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
        // Parse visibility modifiers
        AST::VisibilityLevel visibility = AST::VisibilityLevel::Private; // Default to private
        bool isStatic = false;
        bool isAbstract = false;
        bool isFinal = false;
        bool isConst = false;
        
        // Parse visibility and modifier keywords
        while (check(TokenType::PUB) || check(TokenType::PROT) || check(TokenType::CONST) || 
               check(TokenType::STATIC) || check(TokenType::ABSTRACT) || check(TokenType::FINAL)) {
            
            if (match({TokenType::PUB})) {
                visibility = AST::VisibilityLevel::Public;
            } else if (match({TokenType::PROT})) {
                visibility = AST::VisibilityLevel::Protected;
            } else if (match({TokenType::CONST})) {
                visibility = AST::VisibilityLevel::Const;
                isConst = true;
            } else if (match({TokenType::STATIC})) {
                isStatic = true;
            } else if (match({TokenType::ABSTRACT})) {
                isAbstract = true;
            } else if (match({TokenType::FINAL})) {
                isFinal = true;
            }
        }
        
        if (match({TokenType::VAR})) {
            // Parse field
            auto field = std::dynamic_pointer_cast<AST::VarDeclaration>(varDeclaration());
            if (field) {
                classDecl->fields.push_back(field);
                
                // Store visibility information
                classDecl->fieldVisibility[field->name] = visibility;
                if (isStatic) {
                    classDecl->staticMembers.insert(field->name);
                }
                if (isConst) {
                    classDecl->readOnlyFields.insert(field->name);
                }
            }
        } else if (match({TokenType::FN})) {
            // Parse method
            auto method = function("method");
            if (method) {
                classDecl->methods.push_back(method);
                
                // Store visibility information
                classDecl->methodVisibility[method->name] = visibility;
                method->visibility = visibility; // Set visibility on the method itself
                if (isStatic) {
                    classDecl->staticMembers.insert(method->name);
                }
                if (isAbstract) {
                    classDecl->abstractMethods.insert(method->name);
                    
                    // Abstract methods don't have a body - handle this case
                    if (method->body && method->body->statements.empty()) {
                        // This is fine for abstract methods
                    }
                }
                if (isFinal) {
                    classDecl->finalMethods.insert(method->name);
                }
            }
        } else if (check(TokenType::VAR)) {
            // Handle var without visibility modifiers
            match({TokenType::VAR});
            auto field = std::dynamic_pointer_cast<AST::VarDeclaration>(varDeclaration());
            if (field) {
                classDecl->fields.push_back(field);
                classDecl->fieldVisibility[field->name] = AST::VisibilityLevel::Private; // Default to private
            }
        } else if (check(TokenType::FN)) {
            // Handle fn without visibility modifiers
            match({TokenType::FN});
            auto method = function("method");
            if (method) {
                classDecl->methods.push_back(method);
                classDecl->methodVisibility[method->name] = AST::VisibilityLevel::Private; // Default to private
                method->visibility = AST::VisibilityLevel::Private; // Set visibility on the method itself
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
        } else if (check(TokenType::IDENTIFIER)) {
            // Parse direct field declaration (without 'var' keyword)
            // Format: [visibility] fieldName: type [= initializer];
            Token fieldName = advance(); // consume field name
            
            if (check(TokenType::COLON)) {
                advance(); // consume ':'
                
                // Create a VarDeclaration for this field
                auto field = std::make_shared<AST::VarDeclaration>();
                field->line = fieldName.line;
                field->name = fieldName.lexeme;
                field->type = parseTypeAnnotation();
                
                // Check for initializer
                if (match({TokenType::EQUAL})) {
                    field->initializer = expression();
                }
                
                consume(TokenType::SEMICOLON, "Expected ';' after field declaration.");
                
                classDecl->fields.push_back(field);
                
                // Store visibility information
                classDecl->fieldVisibility[field->name] = visibility;
                if (isStatic) {
                    classDecl->staticMembers.insert(field->name);
                }
                if (isConst) {
                    classDecl->readOnlyFields.insert(field->name);
                }
            } else {
                error("Expected ':' after field name in class member declaration.");
                break;
            }
        } else {
            error("Expected class member declaration.");
            break;
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after class body.");
    popBlockContext();

    // Pop CST context when exiting class declaration
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

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

void Parser::parseConcurrencyParams(
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

std::shared_ptr<AST::Statement> Parser::parallelStatement() {
    auto stmt = createNodeWithContext<AST::ParallelStatement>();
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

    // Pop CST context when exiting parallel statement
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::concurrentStatement() {
    auto stmt = createNodeWithContext<AST::ConcurrentStatement>();
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

    // Pop CST context when exiting concurrent statement
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::importStatement() {
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

std::shared_ptr<AST::EnumDeclaration> Parser::enumDeclaration() {
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
std::shared_ptr<AST::Statement> Parser::matchStatement() {
    auto stmt = createNodeWithContext<AST::MatchStatement>();
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

    // Pop CST context when exiting match statement
    if (cstMode && !cstContextStack.empty()) {
        popCSTContext();
    }

    return stmt;
}

std::shared_ptr<AST::Expression> Parser::parsePattern() {
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

std::shared_ptr<AST::Expression> Parser::parseBindingPattern() {
    auto pattern = std::make_shared<AST::BindingPatternExpr>();
    pattern->line = peek().line;
    pattern->typeName = consume(TokenType::IDENTIFIER, "Expected type name in binding pattern.").lexeme;
    consume(TokenType::LEFT_PAREN, "Expected '(' after type name in binding pattern.");
    pattern->variableName = consume(TokenType::IDENTIFIER, "Expected variable name in binding pattern.").lexeme;
    consume(TokenType::RIGHT_PAREN, "Expected ')' after variable name in binding pattern.");
    return pattern;
}

std::shared_ptr<AST::Expression> Parser::parseListPattern() {
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

std::shared_ptr<AST::Expression> Parser::parseDictPattern() {
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

std::shared_ptr<AST::Expression> Parser::parseTuplePattern() {
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
std::shared_ptr<AST::Expression> Parser::expression() {
    try {
        auto expr = assignment();
        
        // Create hierarchical CST node for complex expressions if enabled
        if (cstMode && config.detailedExpressionNodes && expr) {
            // For top-level expressions, we may want to wrap them in an EXPRESSION node
            // This helps maintain the hierarchical structure
            auto exprCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            exprCSTNode->setDescription("top-level expression");
            
            // The actual expression tokens are already captured by the specific expression methods
            // This node serves as a container for the expression hierarchy
            addChildToCurrentContext(std::move(exprCSTNode));
        }
        
        return expr;
    } catch (const std::exception& e) {
        // Invalid syntax recovery for CST parser
        if (cstMode) {
            // Create an error node for invalid syntax
            auto errorCSTNode = std::make_unique<CST::Node>(CST::NodeKind::ERROR_NODE);
            errorCSTNode->setDescription("Invalid expression syntax: " + std::string(e.what()));
            errorCSTNode->setError("error recovery in expression");
            
            // Skip tokens until we find a synchronization point
            while (!isAtEnd() && !check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE) && 
                   !check(TokenType::RIGHT_PAREN) && !check(TokenType::COMMA) && !check(TokenType::NEWLINE)) {
                errorCSTNode->addToken(advance());
            }
            
            addChildToCurrentContext(std::move(errorCSTNode));
        }
        
        // Return a placeholder error expression
        return makeErrorExpr();
    }
}

std::shared_ptr<AST::Expression> Parser::assignment() {
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

            // Create detailed CST node if enabled
            if (cstMode && config.detailedExpressionNodes) {
                auto assignCSTNode = std::make_unique<CST::Node>(CST::NodeKind::ASSIGNMENT_EXPR);
                assignCSTNode->setDescription("assignment expression");
                assignCSTNode->addToken(op);
                attachTriviaFromToken(op);
                addChildToCurrentContext(std::move(assignCSTNode));
            }

            return assignExpr;
        } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->object = memberExpr->object;
            assignExpr->member = memberExpr->name;
            assignExpr->op = op.type;
            assignExpr->value = value;

            // Create detailed CST node if enabled
            if (cstMode && config.detailedExpressionNodes) {
                auto assignCSTNode = std::make_unique<CST::Node>(CST::NodeKind::ASSIGNMENT_EXPR);
                assignCSTNode->setDescription("member assignment expression");
                assignCSTNode->addToken(op);
                attachTriviaFromToken(op);
                addChildToCurrentContext(std::move(assignCSTNode));
            }

            return assignExpr;
        } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->object = indexExpr->object;
            assignExpr->index = indexExpr->index;
            assignExpr->op = op.type;
            assignExpr->value = value;

            // Create detailed CST node if enabled
            if (cstMode && config.detailedExpressionNodes) {
                auto assignCSTNode = std::make_unique<CST::Node>(CST::NodeKind::ASSIGNMENT_EXPR);
                assignCSTNode->setDescription("index assignment expression");
                assignCSTNode->addToken(op);
                attachTriviaFromToken(op);
                addChildToCurrentContext(std::move(assignCSTNode));
            }

            return assignExpr;
        }

        error("Invalid assignment target.");
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::logicalOr() {
    auto expr = logicalAnd();

    while (match({TokenType::OR})) {
        auto op = previous();
        auto right = logicalAnd();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("logical or expression");
            
            // Set up hierarchical context for this binary expression
            pushCSTContext(binaryCSTNode.get());
            
            // Capture the operator token with its trivia
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire binary expression
            if (expr && right) {
                // Estimate span from left operand to right operand
                binaryCSTNode->setSourceSpan(op.start, op.end);
            }
            
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::logicalAnd() {
    auto expr = equality();

    while (match({TokenType::AND})) {
        auto op = previous();
        auto right = equality();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("logical and expression");
            
            // Set up hierarchical context for this binary expression
            pushCSTContext(binaryCSTNode.get());
            
            // Capture the operator token with its trivia
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire binary expression
            binaryCSTNode->setSourceSpan(op.start, op.end);
            
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::equality() {
    auto expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        auto op = previous();
        auto right = comparison();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("equality expression");
            
            // Set up hierarchical context for this binary expression
            pushCSTContext(binaryCSTNode.get());
            
            // Capture the operator token with its trivia
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire binary expression
            binaryCSTNode->setSourceSpan(op.start, op.end);
            
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::comparison() {
    auto expr = term();

    // Check for range expressions (e.g., 1..10)
    if (match({TokenType::RANGE})) {
        auto rangeExpr = std::make_shared<AST::RangeExpr>();
        rangeExpr->line = previous().line;
        rangeExpr->start = expr;
        rangeExpr->end = term();
        rangeExpr->step = nullptr; // No step value for now
        rangeExpr->inclusive = true; // Default to inclusive range
        
        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto rangeCSTNode = std::make_unique<CST::Node>(CST::NodeKind::RANGE_EXPR);
            rangeCSTNode->setDescription("range expression");
            
            // Set up hierarchical context for this range expression
            pushCSTContext(rangeCSTNode.get());
            
            // Capture the range operator token with its trivia
            Token rangeToken = previous();
            rangeCSTNode->addToken(rangeToken);
            attachTriviaFromToken(rangeToken);
            
            // Update source span to cover the entire range expression
            rangeCSTNode->setSourceSpan(rangeToken.start, rangeToken.end);
            
            addChildToCurrentContext(std::move(rangeCSTNode));
            popCSTContext();
        }
        
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

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("comparison expression");
            
            // Set up hierarchical context for this binary expression
            pushCSTContext(binaryCSTNode.get());
            
            // Capture the operator token with its trivia
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire binary expression
            binaryCSTNode->setSourceSpan(op.start, op.end);
            
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::term() {
    auto expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS})) {
        auto op = previous();
        auto right = factor();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("arithmetic term expression");
            
            // Set up hierarchical context for this binary expression
            pushCSTContext(binaryCSTNode.get());
            
            // Capture the operator token with its trivia
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire binary expression
            binaryCSTNode->setSourceSpan(op.start, op.end);
            
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::factor() {
    auto expr = power();

    while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULUS})) {
        auto op = previous();
        auto right = unary();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("arithmetic factor expression");
            
            // Set up hierarchical context for this binary expression
            pushCSTContext(binaryCSTNode.get());
            
            // Capture the operator token with its trivia
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire binary expression
            binaryCSTNode->setSourceSpan(op.start, op.end);
            
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::power() {
    auto expr = unary();
    while (match({TokenType::POWER})) { // Assuming POWER is '**'
        auto op = previous();
        auto right = power(); // Right-associative!
        auto binaryExpr = createNodeWithContext<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;
        
        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("power expression");
            
            // Set up hierarchical context for this binary expression
            pushCSTContext(binaryCSTNode.get());
            
            // Capture the operator token with its trivia
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire binary expression
            binaryCSTNode->setSourceSpan(op.start, op.end);
            
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        } else {
            attachTriviaFromToken(op);
        }
        
        expr = binaryExpr;
    }
    return expr;
}

std::shared_ptr<AST::Expression> Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS, TokenType::PLUS})) {
        auto op = previous();
        auto right = unary();

        auto unaryExpr = std::make_shared<AST::UnaryExpr>();
        unaryExpr->line = op.line;
        unaryExpr->op = op.type;
        unaryExpr->right = right;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto unaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::UNARY_EXPR);
            unaryCSTNode->setDescription("unary expression");
            
            // Set up hierarchical context for this unary expression
            pushCSTContext(unaryCSTNode.get());
            
            // Capture the operator token with its trivia
            unaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            
            // Update source span to cover the entire unary expression
            unaryCSTNode->setSourceSpan(op.start, op.end);
            
            addChildToCurrentContext(std::move(unaryCSTNode));
            popCSTContext();
        }

        return unaryExpr;
    }

    // if (match({TokenType::AWAIT})) {
    //     auto awaitToken = previous();
    //     auto awaitExpr = std::make_shared<AST::AwaitExpr>();
    //     awaitExpr->line = awaitToken.line;
    //     awaitExpr->expression = unary();
    //
    //     // Create detailed CST node if enabled
    //     if (cstMode && config.detailedExpressionNodes) {
    //         auto awaitCSTNode = std::make_unique<CST::Node>(CST::NodeKind::UNARY_EXPR);
    //         awaitCSTNode->setDescription("await expression");
    //         
    //         // Set up hierarchical context for this await expression
    //         pushCSTContext(awaitCSTNode.get());
    //         
    //         // Capture the await token with its trivia
    //         awaitCSTNode->addToken(awaitToken);
    //         attachTriviaFromToken(awaitToken);
    //         
    //         // Update source span to cover the entire await expression
    //         awaitCSTNode->setSourceSpan(awaitToken.start, awaitToken.end);
    //         
    //         addChildToCurrentContext(std::move(awaitCSTNode));
    //         popCSTContext();
    //     }
    //
    //     return awaitExpr;
    // }

    return call();
}

std::shared_ptr<AST::Expression> Parser::call() {
    auto expr = primary();

    while (true) {
        if (match({TokenType::LEFT_PAREN})) {
            expr = finishCall(expr);
        } else if (match({TokenType::DOT})) {
            auto dotToken = previous();
            
            // Check for tuple indexing (e.g., tuple.0, tuple.1)
            if (check(TokenType::NUMBER)) {
                auto numberToken = advance();
                
                // Create an index expression for tuple access
                auto indexExpr = std::make_shared<AST::IndexExpr>();
                indexExpr->line = numberToken.line;
                indexExpr->object = expr;
                
                // Create a literal expression for the index
                auto indexLiteral = std::make_shared<AST::LiteralExpr>();
                indexLiteral->line = numberToken.line;
                
                // Parse the number as a string
                try {
                    // Validate integer format
                    size_t pos;
                    long long indexValue = std::stoll(numberToken.lexeme, &pos);
                    if (pos != numberToken.lexeme.length()) {
                        throw std::invalid_argument("Invalid characters in integer");
                    }
                    indexLiteral->value = numberToken.lexeme; // Store as string
                } catch (const std::exception&) {
                    error("Invalid tuple index: " + numberToken.lexeme);
                    indexLiteral->value = "0";
                }
                
                indexExpr->index = indexLiteral;
                expr = indexExpr;
            } else {
                // Regular member access
                auto name = consume(TokenType::IDENTIFIER, "Expected property name after '.'.");

                auto memberExpr = std::make_shared<AST::MemberExpr>();
                memberExpr->line = name.line;
                memberExpr->object = expr;
                memberExpr->name = name.lexeme;

                // Create detailed CST node if enabled
                if (cstMode && config.detailedExpressionNodes) {
                    auto memberCSTNode = std::make_unique<CST::Node>(CST::NodeKind::MEMBER_EXPR);
                    memberCSTNode->setDescription("member access expression");
                    
                    // Set up hierarchical context for this member expression
                    pushCSTContext(memberCSTNode.get());
                    
                    // Capture the dot and identifier tokens with their trivia
                    memberCSTNode->addToken(dotToken);
                    memberCSTNode->addToken(name);
                    attachTriviaFromToken(dotToken);
                    attachTriviaFromToken(name);
                    
                    // Update source span to cover the entire member access
                    memberCSTNode->setSourceSpan(dotToken.start, name.end);
                    
                    addChildToCurrentContext(std::move(memberCSTNode));
                    popCSTContext();
                }

                expr = memberExpr;
            }
        } else if (match({TokenType::LEFT_BRACKET})) {
            auto leftBracket = previous();
            auto index = expression();
            auto rightBracket = consume(TokenType::RIGHT_BRACKET, "Expected ']' after index.");

            auto indexExpr = std::make_shared<AST::IndexExpr>();
            indexExpr->line = rightBracket.line;
            indexExpr->object = expr;
            indexExpr->index = index;

            // Create detailed CST node if enabled
            if (cstMode && config.detailedExpressionNodes) {
                auto indexCSTNode = std::make_unique<CST::Node>(CST::NodeKind::INDEX_EXPR);
                indexCSTNode->setDescription("index access expression");
                
                // Set up hierarchical context for this index expression
                pushCSTContext(indexCSTNode.get());
                
                // Capture the bracket tokens with their trivia
                indexCSTNode->addToken(leftBracket);
                indexCSTNode->addToken(rightBracket);
                attachTriviaFromToken(leftBracket);
                attachTriviaFromToken(rightBracket);
                
                // Update source span to cover the entire index access
                indexCSTNode->setSourceSpan(leftBracket.start, rightBracket.end);
                
                addChildToCurrentContext(std::move(indexCSTNode));
                popCSTContext();
            }

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

std::shared_ptr<AST::Expression> Parser::finishCall(std::shared_ptr<AST::Expression> callee) {
    std::vector<std::shared_ptr<AST::Expression>> arguments;
    std::unordered_map<std::string, std::shared_ptr<AST::Expression>> namedArgs;
    std::vector<Token> callTokens; // Track tokens for CST

    // Track left paren for CST
    Token leftParen = previous(); // The LEFT_PAREN that got us here
    if (cstMode && config.detailedExpressionNodes) {
        callTokens.push_back(leftParen);
    }

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            // Check for named arguments
            if (check(TokenType::IDENTIFIER) && peek().lexeme.length() > 0) {
                Token nameToken = peek();
                advance();

                if (match({TokenType::EQUAL})) {
                    // This is a named argument
                    Token equalToken = previous();
                    if (cstMode && config.detailedExpressionNodes) {
                        callTokens.push_back(nameToken);
                        callTokens.push_back(equalToken);
                    }
                    auto argValue = expression();
                    namedArgs[nameToken.lexeme] = argValue;
                } else {
                    // Not a named argument, rewind and parse as regular expression
                    current--; // Rewind to before the identifier
                    // Regular positional argument
                    arguments.push_back(expression());
                }
            } else {
                // Regular positional argument
                arguments.push_back(expression());
            }
            
            // Track comma tokens for CST and continue if there's a comma
            if (!match({TokenType::COMMA})) {
                break; // No more arguments
            }
            if (cstMode && config.detailedExpressionNodes) {
                callTokens.push_back(previous());
            }
        } while (true);
    }

    auto paren = consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments.");
    if (cstMode && config.detailedExpressionNodes) {
        callTokens.push_back(paren);
    }

    auto callExpr = std::make_shared<AST::CallExpr>();
    callExpr->line = paren.line;
    callExpr->callee = callee;
    callExpr->arguments = arguments;
    callExpr->namedArgs = namedArgs;

    // Create detailed CST node if enabled
    if (cstMode && config.detailedExpressionNodes) {
        auto callCSTNode = std::make_unique<CST::Node>(CST::NodeKind::CALL_EXPR);
        callCSTNode->setDescription("function call expression");
        
        // Set up hierarchical context for this call expression
        pushCSTContext(callCSTNode.get());
        
        // Capture all call-related tokens with their trivia
        for (const auto& token : callTokens) {
            callCSTNode->addToken(token);
            attachTriviaFromToken(token);
        }
        
        // Update source span to cover the entire function call
        if (!callTokens.empty()) {
            callCSTNode->setSourceSpan(callTokens.front().start, callTokens.back().end);
        }
        
        addChildToCurrentContext(std::move(callCSTNode));
        popCSTContext();
    }

    return callExpr;
}

std::shared_ptr<AST::Expression> Parser::primary() {
    if (match({TokenType::FALSE})) {
        auto literalExpr = createNodeWithContext<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = false;
        
        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("boolean literal (false)");
            literalCSTNode->addToken(previous());
            attachTriviaFromToken(previous());
            literalCSTNode->setSourceSpan(previous().start, previous().end);
            addChildToCurrentContext(std::move(literalCSTNode));
        } else {
            attachTriviaFromToken(previous());
        }
        
        return literalExpr;
    }

    if (match({TokenType::TRUE})) {
        auto literalExpr = createNodeWithContext<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = true;
        
        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("boolean literal (true)");
            literalCSTNode->addToken(previous());
            attachTriviaFromToken(previous());
            literalCSTNode->setSourceSpan(previous().start, previous().end);
            addChildToCurrentContext(std::move(literalCSTNode));
        } else {
            attachTriviaFromToken(previous());
        }
        
        return literalExpr;
    }

    // if (match({TokenType::NONE})) {
    //     auto literalExpr = createNodeWithContext<AST::LiteralExpr>();
    //     literalExpr->line = previous().line;
    //     literalExpr->value = nullptr;
    //     attachTriviaFromToken(previous());
    //     return literalExpr;
    // }

    if (match({TokenType::NIL})) {
        auto literalExpr = createNodeWithContext<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = nullptr;
        attachTriviaFromToken(previous());
        return literalExpr;
    }

    if (match({TokenType::NUMBER})) {
        auto token = previous();
        auto literalExpr = createNodeWithContext<AST::LiteralExpr>();
        literalExpr->line = token.line;
        
        // Enhanced numeric literal parsing with string-based values
        bool hasDecimal = token.lexeme.find('.') != std::string::npos;
        bool hasScientific = token.lexeme.find('e') != std::string::npos || token.lexeme.find('E') != std::string::npos;
        
        if (hasDecimal || hasScientific) {
            // Parse as floating-point number and store as string
            try {
                long double doubleValue = std::stold(token.lexeme);
                
                // Check for special values
                if (std::isnan(doubleValue)) {
                    error("Invalid floating-point number (NaN): " + token.lexeme);
                    literalExpr->value = std::string("0.0");
                } else if (std::isinf(doubleValue)) {
                    // Allow infinity for very large scientific notation
                    literalExpr->value = token.lexeme; // Store original string
                } else {
                    // Store as string for all floats
                    literalExpr->value = token.lexeme;
                }
            } catch (const std::out_of_range& e) {
                error("Floating-point number out of range: " + token.lexeme);
                literalExpr->value = std::string("0.0");
            } catch (const std::invalid_argument& e) {
                error("Invalid floating-point number format: " + token.lexeme);
                literalExpr->value = std::string("0.0");
            } catch (const std::exception& e) {
                error("Invalid floating-point number: " + token.lexeme);
                literalExpr->value = std::string("0.0");
            }
        } else {
            // Parse as integer and store as string
            try {
                // Validate integer format
                size_t pos;
                unsigned long long uintValue = std::stoull(token.lexeme, &pos);
                if (pos != token.lexeme.length()) {
                    throw std::invalid_argument("Invalid characters in integer");
                }
                
                // Check if the value fits in 64-bit unsigned range
                const unsigned long long MAX_UINT64_VALUE = 0xFFFFFFFFFFFFFFFFULL;
                if (uintValue > MAX_UINT64_VALUE) {
                    throw std::out_of_range("Integer value exceeds uint64 range");
                }
                
                literalExpr->value = token.lexeme; // Store as string
            } catch (const std::out_of_range&) {
                // If stoull fails with out_of_range, try stoll for very large negative numbers
                try {
                    size_t pos;
                    long long intValue = std::stoll(token.lexeme, &pos);
                    if (pos != token.lexeme.length()) {
                        throw std::invalid_argument("Invalid characters in integer");
                    }
                    literalExpr->value = token.lexeme; // Store as string
                } catch (const std::exception& e) {
                    error("Invalid integer format: " + token.lexeme + " - " + e.what());
                    literalExpr->value = std::string("0");
                }
            } catch (const std::exception& e) {
                error("Invalid integer format: " + token.lexeme + " - " + e.what());
                literalExpr->value = std::string("0");
            }
        }
        
        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("number literal");
            literalCSTNode->addToken(token);
            attachTriviaFromToken(token);
            literalCSTNode->setSourceSpan(token.start, token.end);
            addChildToCurrentContext(std::move(literalCSTNode));
        } else {
            attachTriviaFromToken(token);
        }
        
        return literalExpr;
    }
    
    if (match({TokenType::STRING})) {
        // Regular string literal (interpolated strings start with INTERPOLATION_START, not STRING)
        auto literalExpr = std::make_shared<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        
        // AST gets the parsed string value (without quotes)
        literalExpr->value = parseStringLiteral(previous().lexeme);
        
        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("string literal");
            // CST gets the original token (with quotes) for exact source reconstruction
            literalCSTNode->addToken(previous());
            attachTriviaFromToken(previous());
            literalCSTNode->setSourceSpan(previous().start, previous().end);
            addChildToCurrentContext(std::move(literalCSTNode));
        }
        
        return literalExpr;
    }

    // Handle interpolated strings that start with interpolation (no initial string part)
    if (match({TokenType::INTERPOLATION_START})) {
        // This is an interpolated string starting with interpolation
        // Extract the string part from the INTERPOLATION_START token
        std::string startPart = previous().lexeme;
        // Remove quotes: "Hello, " -> Hello, 
        if (startPart.size() >= 2 && startPart.front() == '"' && startPart.back() == '"') {
            startPart = startPart.substr(1, startPart.length() - 2);
        }
        
        auto interpolated = std::make_shared<AST::InterpolatedStringExpr>();
        interpolated->line = previous().line;
        
        // Add the string part from INTERPOLATION_START token
        interpolated->addStringPart(startPart);
        
        // Parse the expression inside the interpolation  
        auto expr = expression();
        interpolated->addExpressionPart(expr);
        
        // Expect INTERPOLATION_END
        consume(TokenType::INTERPOLATION_END, "Expected '}' after interpolation expression.");
        
        // Parse remaining interpolation parts (like interpolatedString() does)
        while (check(TokenType::INTERPOLATION_START)) {
            advance(); // consume INTERPOLATION_START
            
            // Extract string part from INTERPOLATION_START token
            std::string nextPart = previous().lexeme;
            // Remove quotes: ", b=" -> , b=
            if (nextPart.size() >= 2 && nextPart.front() == '"' && nextPart.back() == '"') {
                nextPart = nextPart.substr(1, nextPart.length() - 2);
            }
            interpolated->addStringPart(nextPart);
            
            // Parse the expression inside the interpolation
            auto nextExpr = expression();
            interpolated->addExpressionPart(nextExpr);
            
            // Expect INTERPOLATION_END
            consume(TokenType::INTERPOLATION_END, "Expected '}' after interpolation expression.");
        }
        
        // Check if there's another string part after this interpolation
        if (check(TokenType::STRING)) {
            advance();
            interpolated->addStringPart(parseStringLiteral(previous().lexeme));
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
                auto varExpr = createNodeWithContext<AST::VariableExpr>();
                varExpr->line = token.line;
                varExpr->name = token.lexeme;
                
                // Create detailed CST node if enabled
                if (cstMode && config.detailedExpressionNodes) {
                    auto varCSTNode = std::make_unique<CST::Node>(CST::NodeKind::VARIABLE_EXPR);
                    varCSTNode->setDescription("variable reference");
                    varCSTNode->addToken(token);
                    attachTriviaFromToken(token);
                    varCSTNode->setSourceSpan(token.start, token.end);
                    addChildToCurrentContext(std::move(varCSTNode));
                } else {
                    attachTriviaFromToken(token);
                }
                
                return varExpr;
            }
        }
    }

    if (match({TokenType::SLEEP})) {
        // Treat SLEEP as a function call
        auto varExpr = createNodeWithContext<AST::VariableExpr>();
        varExpr->line = previous().line;
        varExpr->name = "sleep";
        attachTriviaFromToken(previous());
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
        auto leftParen = previous();
        
        // Check for empty tuple: ()
        if (check(TokenType::RIGHT_PAREN)) {
            auto rightParen = consume(TokenType::RIGHT_PAREN, "Expected ')' after empty tuple.");
            
            auto tupleExpr = std::make_shared<AST::TupleExpr>();
            tupleExpr->line = rightParen.line;
            // Empty tuple
            
            return tupleExpr;
        }
        
        auto firstExpr = expression();
        
        // Check if this is a tuple (has comma) or grouping expression
        if (match({TokenType::COMMA})) {
            // This is a tuple
            std::vector<std::shared_ptr<AST::Expression>> elements;
            elements.push_back(firstExpr);
            
            // Parse remaining elements
            do {
                if (check(TokenType::RIGHT_PAREN)) {
                    break; // Allow trailing comma
                }
                elements.push_back(expression());
            } while (match({TokenType::COMMA}));
            
            auto rightParen = consume(TokenType::RIGHT_PAREN, "Expected ')' after tuple elements.");
            
            auto tupleExpr = std::make_shared<AST::TupleExpr>();
            tupleExpr->line = rightParen.line;
            tupleExpr->elements = elements;
            
            return tupleExpr;
        } else {
            // This is a grouping expression
            auto rightParen = consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");

            auto groupingExpr = std::make_shared<AST::GroupingExpr>();
            groupingExpr->line = rightParen.line;
            groupingExpr->expression = firstExpr;

            // Create detailed CST node if enabled
            if (cstMode && config.detailedExpressionNodes) {
                auto groupingCSTNode = std::make_unique<CST::Node>(CST::NodeKind::GROUPING_EXPR);
                groupingCSTNode->setDescription("grouping expression");
                
                // Set up hierarchical context for this grouping expression
                pushCSTContext(groupingCSTNode.get());
                
                // Capture the parentheses tokens with their trivia
                groupingCSTNode->addToken(leftParen);
                groupingCSTNode->addToken(rightParen);
                attachTriviaFromToken(leftParen);
                attachTriviaFromToken(rightParen);
                
                // Update source span to cover the entire grouping
                groupingCSTNode->setSourceSpan(leftParen.start, rightParen.end);
                
                addChildToCurrentContext(std::move(groupingCSTNode));
                popCSTContext();
            }

            return groupingExpr;
        }
    }

    if (match({TokenType::LEFT_BRACKET})) {
        // Parse list literal
        auto leftBracket = previous();
        std::vector<std::shared_ptr<AST::Expression>> elements;

        if (!check(TokenType::RIGHT_BRACKET)) {
            do {
                elements.push_back(expression());
            } while (match({TokenType::COMMA}));
        }

        auto rightBracket = consume(TokenType::RIGHT_BRACKET, "Expected ']' after list elements.");

        auto listExpr = std::make_shared<AST::ListExpr>();
        listExpr->line = rightBracket.line;
        listExpr->elements = elements;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto listCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            listCSTNode->setDescription("list literal expression");
            listCSTNode->addToken(leftBracket);
            listCSTNode->addToken(rightBracket);
            attachTriviaFromToken(leftBracket);
            attachTriviaFromToken(rightBracket);
            addChildToCurrentContext(std::move(listCSTNode));
        }

        return listExpr;
    }

    if (match({TokenType::LEFT_BRACE})) {
        // Parse dictionary literal
        auto leftBrace = previous();
        std::vector<std::pair<std::shared_ptr<AST::Expression>, std::shared_ptr<AST::Expression>>> entries;

        if (!check(TokenType::RIGHT_BRACE)) {
            do {
                auto key = expression();
                consume(TokenType::COLON, "Expected ':' after dictionary key.");
                auto value = expression();

                entries.push_back({key, value});
            } while (match({TokenType::COMMA}));
        }

        auto rightBrace = consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary entries.");

        auto dictExpr = std::make_shared<AST::DictExpr>();
        dictExpr->line = rightBrace.line;
        dictExpr->entries = entries;

        // Create detailed CST node if enabled
        if (cstMode && config.detailedExpressionNodes) {
            auto dictCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            dictCSTNode->setDescription("dictionary literal expression");
            dictCSTNode->addToken(leftBrace);
            dictCSTNode->addToken(rightBrace);
            attachTriviaFromToken(leftBrace);
            attachTriviaFromToken(rightBrace);
            addChildToCurrentContext(std::move(dictCSTNode));
        }

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
        auto thisExpr = createNodeWithContext<AST::ThisExpr>();
        thisExpr->line = previous().line;
        attachTriviaFromToken(previous());
        return thisExpr;
    } else if (match({TokenType::SUPER})) {
        // Handle 'super' for parent class access
        auto superExpr = createNodeWithContext<AST::SuperExpr>();
        superExpr->line = previous().line;
        attachTriviaFromToken(previous());
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

std::shared_ptr<AST::Statement> Parser::typeDeclaration() {
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
                // Value type can be: primitive type, identifier, [elementType], or {nestedDict}
                if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type) || 
                    check(TokenType::LEFT_BRACKET) || check(TokenType::LEFT_BRACE)) {
                    
                    // If the first token is a type (primitive or known type name), it's a dictionary
                    if (isPrimitiveType(firstToken.type) || 
                        (firstToken.type == TokenType::IDENTIFIER && isKnownTypeName(firstToken.lexeme))) {
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
std::shared_ptr<AST::TypeAnnotation> Parser::parseTypeAnnotation() {
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
bool Parser::isPrimitiveType(TokenType type) {
    return type == TokenType::INT_TYPE || type == TokenType::INT8_TYPE || type == TokenType::INT16_TYPE ||
           type == TokenType::INT32_TYPE || type == TokenType::INT64_TYPE || type == TokenType::INT128_TYPE ||
           type == TokenType::UINT_TYPE || type == TokenType::UINT8_TYPE || type == TokenType::UINT16_TYPE || type == TokenType::UINT32_TYPE ||
           type == TokenType::UINT64_TYPE || type == TokenType::UINT128_TYPE || type == TokenType::FLOAT_TYPE || type == TokenType::FLOAT32_TYPE ||
           type == TokenType::FLOAT64_TYPE || type == TokenType::STR_TYPE || type == TokenType::BOOL_TYPE ||
           type == TokenType::ANY_TYPE || type == TokenType::NIL_TYPE;
}

// Helper method to convert a token type to a string
std::string Parser::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT_TYPE: return "int";
        case TokenType::INT8_TYPE: return "i8";
        case TokenType::INT16_TYPE: return "i16";
        case TokenType::INT32_TYPE: return "i32";
        case TokenType::INT64_TYPE: return "i64";
        case TokenType::INT128_TYPE: return "i128";
        case TokenType::UINT_TYPE: return "uint";
        case TokenType::UINT8_TYPE: return "u8";
        case TokenType::UINT16_TYPE: return "u16";
        case TokenType::UINT32_TYPE: return "u32";
        case TokenType::UINT64_TYPE: return "u64";
        case TokenType::UINT128_TYPE: return "u128";
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
std::shared_ptr<AST::TypeAnnotation> Parser::parseUnionType() {
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
std::shared_ptr<AST::TypeAnnotation> Parser::parseBasicType() {
    auto type = std::make_shared<AST::TypeAnnotation>();

    // Check for container types (e.g., [int], {str: int})
    if (match({TokenType::LEFT_BRACKET})) {
        // Parse list type [elementType] - [ is already consumed
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->isList = true;
        type->typeName = "list";
        
        // Parse element type (e.g., int in [int])
        if (!check(TokenType::RIGHT_BRACKET)) {
            // Use parseBasicType to avoid recursion issues
            type->elementType = parseBasicType();
        } else {
            // Default to any if no element type is specified
            auto anyType = std::make_shared<AST::TypeAnnotation>();
            anyType->typeName = "list";
            anyType->isPrimitive = true;
            type->elementType = anyType;
        }
        
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type.");
        return type;
    }
    
    // Check for tuple types (e.g., (int, str, bool))
    if (match({TokenType::LEFT_PAREN})) {
        type->isTuple = true;
        type->typeName = "tuple";
        
        // Parse tuple element types
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                type->tupleTypes.push_back(parseBasicType());
            } while (match({TokenType::COMMA}));
        }
        
        consume(TokenType::RIGHT_PAREN, "Expected ')' after tuple element types.");
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
    } else if (match({TokenType::INT128_TYPE})) {
        type->typeName = "i128";
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
    } else if (match({TokenType::UINT128_TYPE})) {
        type->typeName = "u128";
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
    } else if (match({TokenType::FN})) {
        // Parse function type with unified syntax: fn(param1: Type1, param2: Type2): ReturnType
        auto funcType = parseFunctionTypeAnnotation();
        // Convert to TypeAnnotation for compatibility
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->typeName = "function";
        type->isFunction = true;
        type->functionParameters = funcType->parameters;
        type->returnType = funcType->returnType;
        return type;
    } else if (match({TokenType::FUNCTION_TYPE})) {
        // Legacy function type support - redirect to unified parsing
        return parseLegacyFunctionType();
    } else if (match({TokenType::FUNCTION_TYPE})) {
        // Legacy function type support
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
                            type->functionParams.push_back(parseBasicType());
                        }
                    } else {
                        // Just a type without parameter name
                        type->functionParams.push_back(parseBasicType());
                    }
                } while (match({TokenType::COMMA}));
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')' after function parameters.");
            
            // Check for return type
            if (match({TokenType::COLON})) {
                type->returnType = parseBasicType();
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
std::shared_ptr<AST::TypeAnnotation> Parser::parseBraceType() {
    // Opening brace is already consumed by parseBasicType()
    
    // Improved heuristic to distinguish dictionary from structural type:
    // Dictionary: {keyType: valueType} - first token is a type (primitive or known type name)
    // Structural: {fieldName: fieldType, ...} - first token is an identifier (field name)
    bool isDictionary = false;
    
    if (!check(TokenType::RIGHT_BRACE)) { // Not empty
        Token firstToken = peek();
        
        // Dictionary type heuristic:
        // 1. First token is a primitive type token (STR_TYPE, INT_TYPE, etc.)
        // 2. OR first token is an identifier that's a known type name
        if (isPrimitiveType(firstToken.type)) {
            isDictionary = true;
        } else if (firstToken.type == TokenType::IDENTIFIER && isKnownTypeName(firstToken.lexeme)) {
            isDictionary = true;
        }
        // Otherwise, assume it's a structural type with field names
    }
    
    if (isDictionary) {
        // Parse dictionary type - { is already consumed
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->isDict = true;
        type->typeName = "dict";
        
        // Parse key type - use parseBasicType to avoid recursion issues
        auto keyType = parseBasicType();
        consume(TokenType::COLON, "Expected ':' in dictionary type.");
        
        // Parse value type - use parseBasicType to avoid recursion issues
        auto valueType = parseBasicType();
        
        type->keyType = keyType;
        type->valueType = valueType;
        
        consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
        return type;
    } else {
        // Parse structural type - { is already consumed
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->isStructural = true;
        type->typeName = "struct";

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
}

// Parse dictionary type {keyType: valueType} - assumes '{' is already consumed
std::shared_ptr<AST::TypeAnnotation> Parser::parseDictionaryType() {
    auto type = std::make_shared<AST::TypeAnnotation>();
    type->isDict = true;
    type->typeName = "dict";
    
    // Parse key type - use parseBasicType to avoid recursion issues
    auto keyType = parseBasicType();
    consume(TokenType::COLON, "Expected ':' in dictionary type.");
    
    // Parse value type - use parseBasicType to avoid recursion issues
    auto valueType = parseBasicType();
    
    type->keyType = keyType;
    type->valueType = valueType;
    
    consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
    return type;
}

// Helper method to check if a lexeme is a known type name
bool Parser::isKnownTypeName(const std::string& name) {
    return name == "any" || name == "str" || name == "int" || name == "float" || 
           name == "bool" || name == "list" || name == "dict" || name == "option" || 
           name == "result" || name == "i8" || name == "i16" || name == "i32" || 
           name == "i64" || name == "u8" || name == "u16" || name == "u32" || 
           name == "u64" || name == "f32" || name == "f64" || name == "uint" ||
           name == "nil" || name == "tuple" || name == "function";
}

// Parse structural type (e.g., { name: str, age: int, ...baseRecord })
std::shared_ptr<AST::TypeAnnotation> Parser::parseStructuralType(const std::string& typeName) {
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

// Parse container type - handles both [elementType] and {keyType: valueType} syntax
std::shared_ptr<AST::TypeAnnotation> Parser::parseContainerType() {
    // Check for list type [elementType]
    if (check(TokenType::LEFT_BRACKET)) {
        advance(); // consume '['
        
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->isList = true;
        type->typeName = "list";
        
        // Parse element type (e.g., int in [int])
        if (!check(TokenType::RIGHT_BRACKET)) {
            // Use parseTypeAnnotation to handle complex element types like [int] or {str: int}
            type->elementType = parseTypeAnnotation();
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
    
    // Check for dictionary type {keyType: valueType}
    if (check(TokenType::LEFT_BRACE)) {
        advance(); // consume '{'
        
        auto type = std::make_shared<AST::TypeAnnotation>();
        type->isDict = true;
        type->typeName = "dict";
        
        // Parse key type - use parseBasicType to avoid recursion issues
        auto keyType = parseBasicType();
        consume(TokenType::COLON, "Expected ':' in dictionary type.");
        
        // Parse value type - use parseBasicType to avoid recursion issues
        auto valueType = parseBasicType();
        
        type->keyType = keyType;
        type->valueType = valueType;
        
        consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
        return type;
    }
    
    // If we get here, it's not a container type
    error("Expected '[' or '{' for container type.");
    return nullptr;
}

// Error pattern parsing methods

// Parse val pattern: val identifier
std::shared_ptr<AST::Expression> Parser::parseValPattern() {
    auto pattern = std::make_shared<AST::ValPatternExpr>();
    pattern->line = peek().line;
    
    consume(TokenType::VAL, "Expected 'val' keyword.");
    pattern->variableName = consume(TokenType::IDENTIFIER, "Expected variable name after 'val'.").lexeme;
    
    return pattern;
}

// Parse err pattern: err identifier or err ErrorType
std::shared_ptr<AST::Expression> Parser::parseErrPattern() {
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
std::shared_ptr<AST::Expression> Parser::parseErrorTypePattern() {
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
bool Parser::isErrorType(const std::string& name) {
    // Built-in error types
    return name == "DivisionByZero" || name == "IndexOutOfBounds" || 
           name == "NullReference" || name == "TypeConversion" || 
           name == "IOError" || name == "ParseError" || name == "NetworkError" ||
           name == "Error"; // Generic error type
}


// Block context tracking methods implementation

void Parser::pushBlockContext(const std::string& blockType, const Token& startToken) {
    ErrorHandling::BlockContext context(blockType, startToken.line, startToken.start, startToken.lexeme);
    blockStack.push(context);
}

void Parser::popBlockContext() {
    if (!blockStack.empty()) {
        blockStack.pop();
    }
}

std::optional<ErrorHandling::BlockContext> Parser::getCurrentBlockContext() const {
    if (blockStack.empty()) {
        return std::nullopt;
    }
    return blockStack.top();
}

std::string Parser::generateCausedByMessage(const ErrorHandling::BlockContext& context) const {
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

std::shared_ptr<AST::Statement> Parser::parseStatementWithContext(const std::string& blockType, const Token& contextToken) {
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
std::shared_ptr<AST::LambdaExpr> Parser::lambdaExpression() {
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

// Parse unified function type annotation: fn(param1: Type1, param2: Type2): ReturnType
std::shared_ptr<AST::FunctionTypeAnnotation> Parser::parseFunctionTypeAnnotation() {
    auto funcType = std::make_shared<AST::FunctionTypeAnnotation>();
    // Note: FunctionTypeAnnotation inherits from TypeAnnotation which has line field
    
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'fn' in function type.");
    
    // Parse parameter types with optional names
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            AST::FunctionParameter param = parseFunctionParameter();
            funcType->parameters.push_back(param);
        } while (match({TokenType::COMMA}));
    }
    
    consume(TokenType::RIGHT_PAREN, "Expected ')' after function parameters.");
    
    // Parse return type
    if (match({TokenType::COLON})) {
        funcType->returnType = parseTypeAnnotation(); // Use full type annotation parsing for union types
    } else {
        // Default to void/nil return type if not specified
        auto voidType = std::make_shared<AST::TypeAnnotation>();
        voidType->typeName = "nil";
        voidType->isPrimitive = true;
        funcType->returnType = voidType;
    }
    
    return funcType;
}

// Parse legacy function type for backward compatibility
std::shared_ptr<AST::TypeAnnotation> Parser::parseLegacyFunctionType() {
    auto type = std::make_shared<AST::TypeAnnotation>();
    type->typeName = "function";
    type->isFunction = true;
    
    // Check for function signature: (param1: Type1, param2: Type2): ReturnType
    if (match({TokenType::LEFT_PAREN})) {
        // Parse parameter types
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                // Skip parameter name if present (we only care about types for legacy)
                if (check(TokenType::IDENTIFIER) && peek().lexeme != "int" && peek().lexeme != "str" && 
                    peek().lexeme != "bool" && peek().lexeme != "float") {
                    advance(); // consume parameter name
                    if (match({TokenType::COLON})) {
                        // Parse parameter type
                        type->functionParams.push_back(parseBasicType());
                    }
                } else {
                    // Just a type without parameter name
                    type->functionParams.push_back(parseBasicType());
                }
            } while (match({TokenType::COMMA}));
        }
        
        consume(TokenType::RIGHT_PAREN, "Expected ')' after function parameters.");
        
        // Check for return type
        if (match({TokenType::COLON})) {
            type->returnType = parseBasicType();
        }
    }
    
    return type;
}

// Parse a single function parameter with optional name and type
AST::FunctionParameter Parser::parseFunctionParameter() {
    AST::FunctionParameter param;
    
    // Check if we have a parameter name followed by colon
    if (check(TokenType::IDENTIFIER)) {
        Token nameToken = peek();
        advance(); // consume potential parameter name
        
        // Check for optional parameter syntax: name?: type
        if (match({TokenType::QUESTION})) {
            // This is optional parameter syntax: name?: type
            consume(TokenType::COLON, "Expected ':' after '?' in optional parameter.");
            if (isValidParameterName(nameToken.lexeme)) {
                param.name = nameToken.lexeme;
                param.hasDefaultValue = true;
            } else {
                error("Invalid parameter name: " + nameToken.lexeme);
            }
            param.type = parseTypeAnnotation(); // Use full type annotation parsing for union types
        } else if (match({TokenType::COLON})) {
            // This was a parameter name with regular syntax: name: type
            if (isValidParameterName(nameToken.lexeme)) {
                param.name = nameToken.lexeme;
            } else {
                error("Invalid parameter name: " + nameToken.lexeme);
            }
            param.type = parseTypeAnnotation(); // Use full type annotation parsing for union types
            
            // The type itself might be optional (e.g., name: int?)
            // This is handled in parseTypeAnnotation already
        } else {
            // This was actually a type name, backtrack
            current--; // Go back to the identifier
            param.type = parseTypeAnnotation(); // Use full type annotation parsing
        }
    } else {
        // Just a type without parameter name
        param.type = parseTypeAnnotation(); // Use full type annotation parsing
    }
    
    return param;
}

// Check if a name is a valid parameter name (not a reserved type name)
bool Parser::isValidParameterName(const std::string& name) {
    // List of reserved type names that cannot be used as parameter names
    static const std::set<std::string> reservedTypes = {
        "int", "i8", "i16", "i32", "i64",
        "uint", "u8", "u16", "u32", "u64", 
        "float", "f32", "f64",
        "str", "string", "bool", "nil", "any",
        "list", "dict", "array", "function",
        "option", "result", "channel", "atomic"
    };
    
    return reservedTypes.find(name) == reservedTypes.end();
}