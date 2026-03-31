#include "parser.hh"
#include "../error/debugger.hh"
#include <stdexcept>
#include <limits>
#include <set>
#include <cmath>
using namespace LM::Frontend;
using namespace LM::Error;

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
    
    // Report error but don't throw - let parser continue
    error(message);
    
    // Return a dummy token to allow parsing to continue
    Token dummy;
    dummy.type = type;
    dummy.lexeme = "";
    dummy.line = peek().line;
    dummy.start = peek().start;
    return dummy;
}

void Parser::synchronize() {
    advance();

    int max_iterations = 1000;  // Prevent infinite loops
    int iterations = 0;
    
    while (!isAtEnd() && iterations < max_iterations) {
        iterations++;
        
        if (previous().type == TokenType::SEMICOLON) return;

        switch (peek().type) {
            case TokenType::FRAME:
            case TokenType::FN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
            case TokenType::IMPORT:
            case TokenType::TRAIT:
            case TokenType::ENUM:
            case TokenType::TYPE:
                return;
            default:
                break;
        }

        advance();
    }
    
    // If we hit max iterations, skip to next statement boundary
    if (iterations >= max_iterations) {
        while (!isAtEnd() && peek().type != TokenType::SEMICOLON && 
               peek().type != TokenType::FN && peek().type != TokenType::VAR &&
               peek().type != TokenType::IF && peek().type != TokenType::WHILE) {
            advance();
        }
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
        
        // For "Expected X" errors, use the previous token's line if we're at a different line
        // This helps report errors on the line where the problem occurred
        if (current > 0 && message.find("Expected") != std::string::npos) {
            Token prevToken = scanner.getTokens()[current - 1];
            // If current token is on a different line, use previous token's line
            if (currentToken.line > prevToken.line) {
                line = prevToken.line;
            } else {
                line = currentToken.line;
            }
        } else {
            line = currentToken.line;
        }
        
        // Calculate column number relative to the start of the line
        const std::string& src = scanner.getSource();
        size_t charOffset = currentToken.start;
        column = 1; // Columns are 1-based
        
        // Find the start of the line
        size_t lineStart = 0;
        for (size_t i = 0; i < charOffset && i < src.length(); ++i) {
            if (src[i] == '\n') {
                lineStart = i + 1; // Start of next line
            }
        }
        
        // Calculate column as offset from line start
        column = (charOffset - lineStart) + 1;
        
        // Extract code context (source line)
        if (line > 0) {
            size_t srcLen = src.length();
            size_t lineStartPos = 0, lineEnd = srcLen;
            int curLine = 1;
            for (size_t i = 0; i < srcLen; ++i) {
                if (curLine == line) {
                    lineStartPos = i;
                    while (lineStartPos > 0 && src[lineStartPos - 1] != '\n') --lineStartPos;
                    lineEnd = i;
                    while (lineEnd < srcLen && src[lineEnd] != '\n') ++lineEnd;
                    codeContext = src.substr(lineStartPos, lineEnd - lineStartPos);
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

std::shared_ptr<LM::Frontend::AST::LiteralExpr> Parser::makeErrorExpr() {
    auto expr = std::make_shared<LM::Frontend::AST::LiteralExpr>();
    expr->line = current > 0 ? scanner.getTokens()[current - 1].line : 1;
    expr->value = nullptr;
    return expr;
}

// Unified node creation helper - creates CST::Node or LM::Frontend::AST::Node based on cstMode
template<typename ASTNodeType>
auto Parser::createNode() -> std::conditional_t<std::is_same_v<ASTNodeType, LM::Frontend::AST::Program>, 
                                                   std::shared_ptr<LM::Frontend::AST::Program>,
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
auto Parser::createNodeWithContext() -> std::conditional_t<std::is_same_v<ASTNodeType, LM::Frontend::AST::Program>, 
                                                          std::shared_ptr<LM::Frontend::AST::Program>,
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
    if (className.find("FrameDeclaration") != std::string::npos) return CST::NodeKind::CLASS_DECLARATION;
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
        case CST::NodeKind::CLASS_DECLARATION: // Also used for FrameDeclaration
        case CST::NodeKind::MATCH_STATEMENT:
        case CST::NodeKind::PARALLEL_STATEMENT:
        case CST::NodeKind::CONCURRENT_STATEMENT:
            return true;
        default:
            return false;
    }
}

// Explicit template instantiations for common AST node types
template auto Parser::createNode<LM::Frontend::AST::Program>() -> std::shared_ptr<LM::Frontend::AST::Program>;
template auto Parser::createNode<LM::Frontend::AST::VarDeclaration>() -> std::shared_ptr<LM::Frontend::AST::VarDeclaration>;
template auto Parser::createNode<LM::Frontend::AST::DestructuringDeclaration>() -> std::shared_ptr<LM::Frontend::AST::DestructuringDeclaration>;
template auto Parser::createNode<LM::Frontend::AST::FunctionDeclaration>() -> std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>;
template auto Parser::createNode<LM::Frontend::AST::IfStatement>() -> std::shared_ptr<LM::Frontend::AST::IfStatement>;
template auto Parser::createNode<LM::Frontend::AST::ForStatement>() -> std::shared_ptr<LM::Frontend::AST::ForStatement>;
template auto Parser::createNode<LM::Frontend::AST::WhileStatement>() -> std::shared_ptr<LM::Frontend::AST::WhileStatement>;
template auto Parser::createNode<LM::Frontend::AST::IterStatement>() -> std::shared_ptr<LM::Frontend::AST::IterStatement>;
template auto Parser::createNode<LM::Frontend::AST::BlockStatement>() -> std::shared_ptr<LM::Frontend::AST::BlockStatement>;
template auto Parser::createNode<LM::Frontend::AST::ExprStatement>() -> std::shared_ptr<LM::Frontend::AST::ExprStatement>;
template auto Parser::createNode<LM::Frontend::AST::ReturnStatement>() -> std::shared_ptr<LM::Frontend::AST::ReturnStatement>;
template auto Parser::createNode<LM::Frontend::AST::PrintStatement>() -> std::shared_ptr<LM::Frontend::AST::PrintStatement>;
template auto Parser::createNode<LM::Frontend::AST::ContractStatement>() -> std::shared_ptr<LM::Frontend::AST::ContractStatement>;
template auto Parser::createNode<LM::Frontend::AST::MatchStatement>() -> std::shared_ptr<LM::Frontend::AST::MatchStatement>;
template auto Parser::createNode<LM::Frontend::AST::ConcurrentStatement>() -> std::shared_ptr<LM::Frontend::AST::ConcurrentStatement>;
template auto Parser::createNode<LM::Frontend::AST::ParallelStatement>() -> std::shared_ptr<LM::Frontend::AST::ParallelStatement>;
template auto Parser::createNode<LM::Frontend::AST::BinaryExpr>() -> std::shared_ptr<LM::Frontend::AST::BinaryExpr>;
template auto Parser::createNode<LM::Frontend::AST::UnaryExpr>() -> std::shared_ptr<LM::Frontend::AST::UnaryExpr>;
template auto Parser::createNode<LM::Frontend::AST::LiteralExpr>() -> std::shared_ptr<LM::Frontend::AST::LiteralExpr>;
template auto Parser::createNode<LM::Frontend::AST::ObjectLiteralExpr>() -> std::shared_ptr<LM::Frontend::AST::ObjectLiteralExpr>;
template auto Parser::createNode<LM::Frontend::AST::VariableExpr>() -> std::shared_ptr<LM::Frontend::AST::VariableExpr>;
template auto Parser::createNode<LM::Frontend::AST::CallExpr>() -> std::shared_ptr<LM::Frontend::AST::CallExpr>;
template auto Parser::createNode<LM::Frontend::AST::AssignExpr>() -> std::shared_ptr<LM::Frontend::AST::AssignExpr>;
template auto Parser::createNode<LM::Frontend::AST::GroupingExpr>() -> std::shared_ptr<LM::Frontend::AST::GroupingExpr>;
template auto Parser::createNode<LM::Frontend::AST::MemberExpr>() -> std::shared_ptr<LM::Frontend::AST::MemberExpr>;
template auto Parser::createNode<LM::Frontend::AST::IndexExpr>() -> std::shared_ptr<LM::Frontend::AST::IndexExpr>;
template auto Parser::createNode<LM::Frontend::AST::ThisExpr>() -> std::shared_ptr<LM::Frontend::AST::ThisExpr>;
template auto Parser::createNode<LM::Frontend::AST::SuperExpr>() -> std::shared_ptr<LM::Frontend::AST::SuperExpr>;

// Explicit template instantiations for createNodeWithContext
template auto Parser::createNodeWithContext<LM::Frontend::AST::Program>() -> std::shared_ptr<LM::Frontend::AST::Program>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::VarDeclaration>() -> std::shared_ptr<LM::Frontend::AST::VarDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::DestructuringDeclaration>() -> std::shared_ptr<LM::Frontend::AST::DestructuringDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::FunctionDeclaration>() -> std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::IfStatement>() -> std::shared_ptr<LM::Frontend::AST::IfStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ForStatement>() -> std::shared_ptr<LM::Frontend::AST::ForStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::WhileStatement>() -> std::shared_ptr<LM::Frontend::AST::WhileStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::IterStatement>() -> std::shared_ptr<LM::Frontend::AST::IterStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::BlockStatement>() -> std::shared_ptr<LM::Frontend::AST::BlockStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ExprStatement>() -> std::shared_ptr<LM::Frontend::AST::ExprStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ReturnStatement>() -> std::shared_ptr<LM::Frontend::AST::ReturnStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::PrintStatement>() -> std::shared_ptr<LM::Frontend::AST::PrintStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ContractStatement>() -> std::shared_ptr<LM::Frontend::AST::ContractStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::MatchStatement>() -> std::shared_ptr<LM::Frontend::AST::MatchStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ConcurrentStatement>() -> std::shared_ptr<LM::Frontend::AST::ConcurrentStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ParallelStatement>() -> std::shared_ptr<LM::Frontend::AST::ParallelStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::LiteralExpr>() -> std::shared_ptr<LM::Frontend::AST::LiteralExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::VariableExpr>() -> std::shared_ptr<LM::Frontend::AST::VariableExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::GroupingExpr>() -> std::shared_ptr<LM::Frontend::AST::GroupingExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::BinaryExpr>() -> std::shared_ptr<LM::Frontend::AST::BinaryExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::UnaryExpr>() -> std::shared_ptr<LM::Frontend::AST::UnaryExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::CallExpr>() -> std::shared_ptr<LM::Frontend::AST::CallExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::MemberExpr>() -> std::shared_ptr<LM::Frontend::AST::MemberExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::IndexExpr>() -> std::shared_ptr<LM::Frontend::AST::IndexExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::AssignExpr>() -> std::shared_ptr<LM::Frontend::AST::AssignExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::SuperExpr>() -> std::shared_ptr<LM::Frontend::AST::SuperExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ThisExpr>() -> std::shared_ptr<LM::Frontend::AST::ThisExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ObjectLiteralExpr>() -> std::shared_ptr<LM::Frontend::AST::ObjectLiteralExpr>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::FrameDeclaration>() -> std::shared_ptr<LM::Frontend::AST::FrameDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::TraitDeclaration>() -> std::shared_ptr<LM::Frontend::AST::TraitDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::EnumDeclaration>() -> std::shared_ptr<LM::Frontend::AST::EnumDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ModuleDeclaration>() -> std::shared_ptr<LM::Frontend::AST::ModuleDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::ImportStatement>() -> std::shared_ptr<LM::Frontend::AST::ImportStatement>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::TypeDeclaration>() -> std::shared_ptr<LM::Frontend::AST::TypeDeclaration>;
template auto Parser::createNodeWithContext<LM::Frontend::AST::InterfaceDeclaration>() -> std::shared_ptr<LM::Frontend::AST::InterfaceDeclaration>;

// Main parse method
std::shared_ptr<LM::Frontend::AST::Program> Parser::parse() {
    auto program = createNodeWithContext<LM::Frontend::AST::Program>();
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
            try {
                auto stmt = declaration();
                if (stmt) {
                    program->statements.push_back(stmt);
                }
            } catch (const std::runtime_error& e) {
                // Check if this is the "too many errors" exception
                if (std::string(e.what()).find("Too many syntax errors") != std::string::npos) {
                    // Re-throw to exit cleanly
                    throw;
                }
                // Handle other parsing errors for individual statements
                synchronize();
                
                // If we've hit too many errors, stop parsing
                if (errors.size() >= MAX_ERRORS) {
                    break;
                }
            } catch (const std::exception &e) {
                // Handle parsing errors for individual statements
                synchronize();
                
                // If we've hit too many errors, stop parsing
                if (errors.size() >= MAX_ERRORS) {
                    break;
                }
            }
        }
    } catch (const std::runtime_error& e) {
        // Check if this is the "too many errors" exception
        if (std::string(e.what()).find("Too many syntax errors") != std::string::npos) {
            // Re-throw to exit cleanly
            throw;
        }
        // Handle other parsing errors at top level
        synchronize();
        
        // Add error info to CST if in CST mode
        if (cstMode && cstRoot) {
            cstRoot->setError("Parse error: " + std::string(e.what()));
        }
    } catch (const std::exception &e) {
        // Handle parsing errors at top level
        synchronize();
        
        // Add error info to CST if in CST mode
        if (cstMode && cstRoot) {
            cstRoot->setError("Parse error: " + std::string(e.what()));
        }
    }

    // In CST mode, we build a hierarchical structure with structured nodes
    // Individual tokens are added to their respective statement/expression nodes
    // No need to add all tokens to root since we have proper structure

    // Errors are now printed via modern diagnostics in debugConsole
    // No need for duplicate summary section
    // Add errors to CST if in CST mode
    if (cstMode && cstRoot && !errors.empty()) {
        for (const auto& err : errors) {
            auto errorNode = std::make_unique<CST::ErrorNode>(err.message, 0, 0);
            addChildToCurrentContext(std::move(errorNode));
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