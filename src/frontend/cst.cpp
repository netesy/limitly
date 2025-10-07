#include "cst.hh"
#include <sstream>
#include <algorithm>

namespace CST {

    // Node utility methods implementation
    void Node::addNode(std::unique_ptr<Node> node) {
        if (node) {
            // Update source span to include node
            if (elements.empty()) {
                startPos = node->startPos;
                endPos = node->endPos;
            } else {
                startPos = std::min(startPos, node->startPos);
                endPos = std::max(endPos, node->endPos);
            }
            
            elements.emplace_back(std::move(node));
        }
    }

    void Node::addToken(const Token& token) {
        // Classify token and create appropriate node or add directly
        if (isWhitespaceToken(token)) {
            addWhitespace(token);
        } else if (isCommentToken(token)) {
            addComment(token);
        } else if (isTriviaToken(token)) {
            addTrivia(token);
        } else {
            // Add significant token directly
            elements.emplace_back(token);
            
            // Update source span
            if (elements.size() == 1) {
                startPos = token.start;
                endPos = token.end > 0 ? token.end : token.start + token.lexeme.length();
            } else {
                startPos = std::min(startPos, token.start);
                size_t tokenEnd = token.end > 0 ? token.end : token.start + token.lexeme.length();
                endPos = std::max(endPos, tokenEnd);
            }
        }
    }

    void Node::addWhitespace(const Token& whitespace) {
        auto wsNode = createWhitespaceNode(whitespace);
        addNode(std::move(wsNode));
    }

    void Node::addComment(const Token& comment) {
        auto commentNode = createCommentNode(comment);
        addNode(std::move(commentNode));
    }

    void Node::addTrivia(const Token& trivia) {
        auto triviaNode = createTriviaNode(trivia);
        addNode(std::move(triviaNode));
    }

    std::vector<Node*> Node::getChildNodes() const {
        std::vector<Node*> nodes;
        for (const auto& element : elements) {
            if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                nodes.push_back(std::get<std::unique_ptr<Node>>(element).get());
            }
        }
        return nodes;
    }

    std::vector<Token> Node::getTokens() const {
        std::vector<Token> tokens;
        for (const auto& element : elements) {
            if (std::holds_alternative<Token>(element)) {
                tokens.push_back(std::get<Token>(element));
            }
        }
        return tokens;
    }

    std::vector<Token> Node::getAllTokens() const {
        std::vector<Token> allTokens;
        
        for (const auto& element : elements) {
            if (std::holds_alternative<Token>(element)) {
                allTokens.push_back(std::get<Token>(element));
            } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                const auto& node = std::get<std::unique_ptr<Node>>(element);
                if (node) {
                    auto childTokens = node->getAllTokens();
                    allTokens.insert(allTokens.end(), childTokens.begin(), childTokens.end());
                }
            }
        }
        
        return allTokens;
    }

    Node* Node::findChild(NodeKind nodeKind) const {
        for (const auto& element : elements) {
            if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                const auto& node = std::get<std::unique_ptr<Node>>(element);
                if (node && node->kind == nodeKind) {
                    return node.get();
                }
            }
        }
        return nullptr;
    }

    std::vector<Node*> Node::findChildren(NodeKind nodeKind) const {
        std::vector<Node*> result;
        
        for (const auto& element : elements) {
            if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                const auto& node = std::get<std::unique_ptr<Node>>(element);
                if (node && node->kind == nodeKind) {
                    result.push_back(node.get());
                }
            }
        }
        
        return result;
    }

    std::string Node::getText() const {
        std::string result;
        
        for (const auto& element : elements) {
            if (std::holds_alternative<Token>(element)) {
                result += std::get<Token>(element).lexeme;
            } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                const auto& node = std::get<std::unique_ptr<Node>>(element);
                if (node) {
                    result += node->getText();
                }
            }
        }
        
        return result;
    }

    std::string Node::getTextWithoutTrivia() const {
        std::string result;
        
        for (const auto& element : elements) {
            if (std::holds_alternative<Token>(element)) {
                const auto& token = std::get<Token>(element);
                if (isSignificantToken(token)) {
                    result += token.lexeme;
                }
            } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                const auto& node = std::get<std::unique_ptr<Node>>(element);
                if (node && !isTriviaNode(node->kind)) {
                    result += node->getTextWithoutTrivia();
                }
            }
        }
        
        return result;
    }

    std::vector<Node*> Node::getSignificantChildren() const {
        std::vector<Node*> result;
        
        for (const auto& element : elements) {
            if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                const auto& node = std::get<std::unique_ptr<Node>>(element);
                if (node && !isTriviaNode(node->kind)) {
                    result.push_back(node.get());
                }
            }
        }
        
        return result;
    }

    std::vector<Token> Node::getSignificantTokens() const {
        std::vector<Token> result;
        
        for (const auto& element : elements) {
            if (std::holds_alternative<Token>(element)) {
                const auto& token = std::get<Token>(element);
                if (isSignificantToken(token)) {
                    result.push_back(token);
                }
            }
        }
        
        return result;
    }

    void Node::setSourceSpan(size_t start, size_t end) {
        startPos = start;
        endPos = end;
    }

    void Node::setError(const std::string& message) {
        errorMessage = message;
        isValid = false;
    }

    void Node::setDescription(const std::string& desc) {
        description = desc;
    }

    bool Node::hasErrors() const {
        if (!isValid) {
            return true;
        }
        
        // Check child nodes for errors
        auto childNodes = getChildNodes();
        for (const auto& child : childNodes) {
            if (child && child->hasErrors()) {
                return true;
            }
        }
        
        return false;
    }

    std::vector<std::string> Node::getErrorMessages() const {
        std::vector<std::string> messages;
        
        if (!isValid && !errorMessage.empty()) {
            messages.push_back(errorMessage);
        }
        
        // Collect error messages from child nodes
        auto childNodes = getChildNodes();
        for (const auto& child : childNodes) {
            if (child) {
                auto childMessages = child->getErrorMessages();
                messages.insert(messages.end(), childMessages.begin(), childMessages.end());
            }
        }
        
        return messages;
    }

    std::string Node::getKindName() const {
        return nodeKindToString(kind);
    }

    std::string Node::toString(int indent) const {
        std::string indentStr(indent * 2, ' ');
        std::ostringstream oss;
        
        oss << indentStr << "+ Node: " << getKindName();
        
        if (!isValid) {
            oss << " [ERROR: " << errorMessage << "]";
        }
        
        if (!description.empty()) {
            oss << " (" << description << ")";
        }
        
        oss << "\n";
        
        // Print all elements (nodes and tokens) in source order
        for (const auto& element : elements) {
            if (std::holds_alternative<Token>(element)) {
                const auto& token = std::get<Token>(element);
                oss << indentStr << "  | Token: '" << token.lexeme << "'\n";
            } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                const auto& node = std::get<std::unique_ptr<Node>>(element);
                if (node) {
                    oss << node->toString(indent + 1);
                }
            }
        }
        
        return oss.str();
    }

    std::string Node::toStringWithTrivia(int indent) const {
        // Same as toString since we now preserve all trivia
        return toString(indent);
    }

    // Factory functions implementation
    std::unique_ptr<Node> createNode(NodeKind kind, size_t start, size_t end) {
        return std::make_unique<Node>(kind, start, end);
    }

    std::unique_ptr<TokenNode> createTokenNode(const Token& token) {
        return std::make_unique<TokenNode>(token);
    }

    std::unique_ptr<WhitespaceNode> createWhitespaceNode(const Token& whitespace) {
        return std::make_unique<WhitespaceNode>(whitespace);
    }

    std::unique_ptr<CommentNode> createCommentNode(const Token& comment) {
        return std::make_unique<CommentNode>(comment);
    }

    std::unique_ptr<TriviaNode> createTriviaNode(const Token& trivia) {
        return std::make_unique<TriviaNode>(trivia);
    }

    std::unique_ptr<ErrorNode> createErrorNode(const std::string& message, size_t start, size_t end) {
        return std::make_unique<ErrorNode>(message, start, end);
    }

    std::unique_ptr<MissingNode> createMissingNode(NodeKind expectedKind, const std::string& description, size_t start, size_t end) {
        return std::make_unique<MissingNode>(expectedKind, description, start, end);
    }

    std::unique_ptr<IncompleteNode> createIncompleteNode(NodeKind targetKind, const std::string& description, size_t start, size_t end) {
        return std::make_unique<IncompleteNode>(targetKind, description, start, end);
    }

    // Utility functions implementation
    std::string nodeKindToString(NodeKind kind) {
        switch (kind) {
            // Program structure
            case NodeKind::PROGRAM: return "PROGRAM";
            case NodeKind::STATEMENT_LIST: return "STATEMENT_LIST";
            
            // Declarations
            case NodeKind::VAR_DECLARATION: return "VAR_DECLARATION";
            case NodeKind::FUNCTION_DECLARATION: return "FUNCTION_DECLARATION";
            case NodeKind::CLASS_DECLARATION: return "CLASS_DECLARATION";
            case NodeKind::ENUM_DECLARATION: return "ENUM_DECLARATION";
            case NodeKind::TYPE_DECLARATION: return "TYPE_DECLARATION";
            case NodeKind::TRAIT_DECLARATION: return "TRAIT_DECLARATION";
            case NodeKind::INTERFACE_DECLARATION: return "INTERFACE_DECLARATION";
            case NodeKind::MODULE_DECLARATION: return "MODULE_DECLARATION";
            case NodeKind::IMPORT_DECLARATION: return "IMPORT_DECLARATION";
            
            // Statements
            case NodeKind::IF_STATEMENT: return "IF_STATEMENT";
            case NodeKind::FOR_STATEMENT: return "FOR_STATEMENT";
            case NodeKind::WHILE_STATEMENT: return "WHILE_STATEMENT";
            case NodeKind::ITER_STATEMENT: return "ITER_STATEMENT";
            case NodeKind::MATCH_STATEMENT: return "MATCH_STATEMENT";
            case NodeKind::BLOCK_STATEMENT: return "BLOCK_STATEMENT";
            case NodeKind::EXPRESSION_STATEMENT: return "EXPRESSION_STATEMENT";
            case NodeKind::RETURN_STATEMENT: return "RETURN_STATEMENT";
            case NodeKind::BREAK_STATEMENT: return "BREAK_STATEMENT";
            case NodeKind::CONTINUE_STATEMENT: return "CONTINUE_STATEMENT";
            case NodeKind::PRINT_STATEMENT: return "PRINT_STATEMENT";
            case NodeKind::ATTEMPT_STATEMENT: return "ATTEMPT_STATEMENT";
            case NodeKind::HANDLE_STATEMENT: return "HANDLE_STATEMENT";
            case NodeKind::PARALLEL_STATEMENT: return "PARALLEL_STATEMENT";
            case NodeKind::CONCURRENT_STATEMENT: return "CONCURRENT_STATEMENT";
            case NodeKind::ASYNC_STATEMENT: return "ASYNC_STATEMENT";
            case NodeKind::AWAIT_STATEMENT: return "AWAIT_STATEMENT";
            case NodeKind::CONTRACT_STATEMENT: return "CONTRACT_STATEMENT";
            
            // Expressions
            case NodeKind::BINARY_EXPR: return "BINARY_EXPR";
            case NodeKind::UNARY_EXPR: return "UNARY_EXPR";
            case NodeKind::CALL_EXPR: return "CALL_EXPR";
            case NodeKind::MEMBER_EXPR: return "MEMBER_EXPR";
            case NodeKind::INDEX_EXPR: return "INDEX_EXPR";
            case NodeKind::LITERAL_EXPR: return "LITERAL_EXPR";
            case NodeKind::VARIABLE_EXPR: return "VARIABLE_EXPR";
            case NodeKind::GROUPING_EXPR: return "GROUPING_EXPR";
            case NodeKind::ASSIGNMENT_EXPR: return "ASSIGNMENT_EXPR";
            case NodeKind::LOGICAL_EXPR: return "LOGICAL_EXPR";
            case NodeKind::CONDITIONAL_EXPR: return "CONDITIONAL_EXPR";
            case NodeKind::LAMBDA_EXPR: return "LAMBDA_EXPR";
            case NodeKind::RANGE_EXPR: return "RANGE_EXPR";
            case NodeKind::INTERPOLATION_EXPR: return "INTERPOLATION_EXPR";
            case NodeKind::CAST_EXPR: return "CAST_EXPR";
            
            // Types
            case NodeKind::PRIMITIVE_TYPE: return "PRIMITIVE_TYPE";
            case NodeKind::FUNCTION_TYPE: return "FUNCTION_TYPE";
            case NodeKind::LIST_TYPE: return "LIST_TYPE";
            case NodeKind::DICT_TYPE: return "DICT_TYPE";
            case NodeKind::ARRAY_TYPE: return "ARRAY_TYPE";
            case NodeKind::UNION_TYPE: return "UNION_TYPE";
            case NodeKind::OPTION_TYPE: return "OPTION_TYPE";
            case NodeKind::RESULT_TYPE: return "RESULT_TYPE";
            case NodeKind::USER_TYPE: return "USER_TYPE";
            case NodeKind::GENERIC_TYPE: return "GENERIC_TYPE";
            
            // Patterns
            case NodeKind::LITERAL_PATTERN: return "LITERAL_PATTERN";
            case NodeKind::VARIABLE_PATTERN: return "VARIABLE_PATTERN";
            case NodeKind::WILDCARD_PATTERN: return "WILDCARD_PATTERN";
            case NodeKind::CONSTRUCTOR_PATTERN: return "CONSTRUCTOR_PATTERN";
            case NodeKind::TUPLE_PATTERN: return "TUPLE_PATTERN";
            case NodeKind::LIST_PATTERN: return "LIST_PATTERN";
            
            // Parameters and arguments
            case NodeKind::PARAMETER: return "PARAMETER";
            case NodeKind::PARAMETER_LIST: return "PARAMETER_LIST";
            case NodeKind::ARGUMENT: return "ARGUMENT";
            case NodeKind::ARGUMENT_LIST: return "ARGUMENT_LIST";
            
            // Other constructs
            case NodeKind::IDENTIFIER: return "IDENTIFIER";
            case NodeKind::LITERAL: return "LITERAL";
            case NodeKind::BLOCK: return "BLOCK";
            case NodeKind::CONDITION: return "CONDITION";
            case NodeKind::INITIALIZER: return "INITIALIZER";
            case NodeKind::MODIFIER: return "MODIFIER";
            case NodeKind::ANNOTATION: return "ANNOTATION";
            
            // Concrete syntax elements
            case NodeKind::TOKEN_NODE: return "TOKEN_NODE";
            case NodeKind::WHITESPACE_NODE: return "WHITESPACE_NODE";
            case NodeKind::COMMENT_NODE: return "COMMENT_NODE";
            case NodeKind::TRIVIA_NODE: return "TRIVIA_NODE";
            
            // Error recovery nodes
            case NodeKind::ERROR_NODE: return "ERROR_NODE";
            case NodeKind::MISSING_NODE: return "MISSING_NODE";
            case NodeKind::INCOMPLETE_NODE: return "INCOMPLETE_NODE";
            
            default: return "UNKNOWN";
        }
    }

    bool isStatementNode(NodeKind kind) {
        switch (kind) {
            case NodeKind::IF_STATEMENT:
            case NodeKind::FOR_STATEMENT:
            case NodeKind::WHILE_STATEMENT:
            case NodeKind::ITER_STATEMENT:
            case NodeKind::MATCH_STATEMENT:
            case NodeKind::BLOCK_STATEMENT:
            case NodeKind::EXPRESSION_STATEMENT:
            case NodeKind::RETURN_STATEMENT:
            case NodeKind::BREAK_STATEMENT:
            case NodeKind::CONTINUE_STATEMENT:
            case NodeKind::PRINT_STATEMENT:
            case NodeKind::ATTEMPT_STATEMENT:
            case NodeKind::HANDLE_STATEMENT:
            case NodeKind::PARALLEL_STATEMENT:
            case NodeKind::CONCURRENT_STATEMENT:
            case NodeKind::ASYNC_STATEMENT:
            case NodeKind::AWAIT_STATEMENT:
            case NodeKind::CONTRACT_STATEMENT:
                return true;
            default:
                return false;
        }
    }

    bool isExpressionNode(NodeKind kind) {
        switch (kind) {
            case NodeKind::BINARY_EXPR:
            case NodeKind::UNARY_EXPR:
            case NodeKind::CALL_EXPR:
            case NodeKind::MEMBER_EXPR:
            case NodeKind::INDEX_EXPR:
            case NodeKind::LITERAL_EXPR:
            case NodeKind::VARIABLE_EXPR:
            case NodeKind::GROUPING_EXPR:
            case NodeKind::ASSIGNMENT_EXPR:
            case NodeKind::LOGICAL_EXPR:
            case NodeKind::CONDITIONAL_EXPR:
            case NodeKind::LAMBDA_EXPR:
            case NodeKind::RANGE_EXPR:
            case NodeKind::INTERPOLATION_EXPR:
            case NodeKind::CAST_EXPR:
                return true;
            default:
                return false;
        }
    }

    bool isDeclarationNode(NodeKind kind) {
        switch (kind) {
            case NodeKind::VAR_DECLARATION:
            case NodeKind::FUNCTION_DECLARATION:
            case NodeKind::CLASS_DECLARATION:
            case NodeKind::ENUM_DECLARATION:
            case NodeKind::TYPE_DECLARATION:
            case NodeKind::TRAIT_DECLARATION:
            case NodeKind::INTERFACE_DECLARATION:
            case NodeKind::MODULE_DECLARATION:
            case NodeKind::IMPORT_DECLARATION:
                return true;
            default:
                return false;
        }
    }

    bool isErrorRecoveryNode(NodeKind kind) {
        switch (kind) {
            case NodeKind::ERROR_NODE:
            case NodeKind::MISSING_NODE:
            case NodeKind::INCOMPLETE_NODE:
                return true;
            default:
                return false;
        }
    }

    bool isTriviaNode(NodeKind kind) {
        switch (kind) {
            case NodeKind::WHITESPACE_NODE:
            case NodeKind::COMMENT_NODE:
            case NodeKind::TRIVIA_NODE:
                return true;
            default:
                return false;
        }
    }

    // Token classification helpers
    bool isWhitespaceToken(const Token& token) {
        return token.type == TokenType::WHITESPACE || 
               token.type == TokenType::NEWLINE;
    }

    bool isCommentToken(const Token& token) {
        return token.type == TokenType::COMMENT_LINE ||
               token.type == TokenType::COMMENT_BLOCK;
    }

    bool isTriviaToken(const Token& token) {
        return isWhitespaceToken(token) || isCommentToken(token);
    }

    bool isSignificantToken(const Token& token) {
        return !isTriviaToken(token);
    }

    // CST Builder implementation
    void CSTBuilder::addSignificantNode(std::unique_ptr<Node> node) {
        if (node) {
            if (elements_.empty()) {
                startPos_ = node->startPos;
                endPos_ = node->endPos;
            } else {
                startPos_ = std::min(startPos_, node->startPos);
                endPos_ = std::max(endPos_, node->endPos);
            }
            elements_.emplace_back(std::move(node));
        }
    }

    void CSTBuilder::addToken(const Token& token) {
        elements_.emplace_back(token);
        
        if (elements_.size() == 1) {
            startPos_ = token.start;
            endPos_ = token.end > 0 ? token.end : token.start + token.lexeme.length();
        } else {
            startPos_ = std::min(startPos_, token.start);
            size_t tokenEnd = token.end > 0 ? token.end : token.start + token.lexeme.length();
            endPos_ = std::max(endPos_, tokenEnd);
        }
    }

    void CSTBuilder::addAllTokens(const std::vector<Token>& tokens) {
        for (const auto& token : tokens) {
            addToken(token);
        }
    }

    std::unique_ptr<Node> CSTBuilder::build(NodeKind rootKind) {
        auto root = createNode(rootKind, startPos_, endPos_);
        
        // Move all elements to the root node
        for (auto& element : elements_) {
            root->elements.push_back(std::move(element));
        }
        
        // Clear builder state
        elements_.clear();
        startPos_ = 0;
        endPos_ = 0;
        
        return root;
    }

} // namespace CST