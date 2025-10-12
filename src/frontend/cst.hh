#ifndef CST_H
#define CST_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include "scanner.hh"

namespace CST {

    // NodeKind enum covering all language constructs
    enum class NodeKind {
        // Program structure
        PROGRAM,
        STATEMENT_LIST,
        
        // Declarations
        VAR_DECLARATION,
        FUNCTION_DECLARATION,
        CLASS_DECLARATION,
        ENUM_DECLARATION,
        TYPE_DECLARATION,
        TRAIT_DECLARATION,
        INTERFACE_DECLARATION,
        MODULE_DECLARATION,
        IMPORT_DECLARATION,
        
        // Statements
        IF_STATEMENT,
        FOR_STATEMENT,
        WHILE_STATEMENT,
        ITER_STATEMENT,
        MATCH_STATEMENT,
        BLOCK_STATEMENT,
        EXPRESSION_STATEMENT,
        RETURN_STATEMENT,
        BREAK_STATEMENT,
        CONTINUE_STATEMENT,
        PRINT_STATEMENT,
        ATTEMPT_STATEMENT,
        HANDLE_STATEMENT,
        PARALLEL_STATEMENT,
        CONCURRENT_STATEMENT,
        ASYNC_STATEMENT,
        AWAIT_STATEMENT,
        CONTRACT_STATEMENT,
        
        // Expressions
        BINARY_EXPR,
        UNARY_EXPR,
        CALL_EXPR,
        MEMBER_EXPR,
        INDEX_EXPR,
        LITERAL_EXPR,
        OBJECT_LITERAL_EXPR,
        VARIABLE_EXPR,
        GROUPING_EXPR,
        ASSIGNMENT_EXPR,
        LOGICAL_EXPR,
        CONDITIONAL_EXPR,
        LAMBDA_EXPR,
        RANGE_EXPR,
        INTERPOLATION_EXPR,
        CAST_EXPR,
        
        // Types
        PRIMITIVE_TYPE,
        FUNCTION_TYPE,
        LIST_TYPE,
        DICT_TYPE,
        ARRAY_TYPE,
        UNION_TYPE,
        OPTION_TYPE,
        RESULT_TYPE,
        USER_TYPE,
        GENERIC_TYPE,
        
        // Patterns (for match expressions)
        LITERAL_PATTERN,
        VARIABLE_PATTERN,
        WILDCARD_PATTERN,
        CONSTRUCTOR_PATTERN,
        TUPLE_PATTERN,
        LIST_PATTERN,
        
        // Parameters and arguments
        PARAMETER,
        PARAMETER_LIST,
        ARGUMENT,
        ARGUMENT_LIST,
        
        // Other constructs
        IDENTIFIER,
        LITERAL,
        BLOCK,
        CONDITION,
        INITIALIZER,
        MODIFIER,
        ANNOTATION,
        
        // Concrete syntax elements (preserving all source)
        TOKEN_NODE,           // Individual token wrapper
        WHITESPACE_NODE,      // Whitespace preservation
        COMMENT_NODE,         // Comment preservation
        TRIVIA_NODE,          // General trivia (newlines, etc.)
        
        // Error recovery nodes
        ERROR_NODE,           // Invalid syntax
        MISSING_NODE,         // Missing required elements
        INCOMPLETE_NODE,      // Partial constructs
    };

    // Forward declarations
    class Node;
    class TokenNode;
    class WhitespaceNode;
    class CommentNode;
    class TriviaNode;

    // CST Element - can be either a structural node or a token
    using CSTElement = std::variant<std::unique_ptr<Node>, Token>;

    // Base CST Node class - represents structural elements
    class Node {
    public:
        NodeKind kind;
        size_t startPos;              // Source position start
        size_t endPos;                // Source position end
        
        // CST preserves ALL source elements in order
        std::vector<CSTElement> elements;
        
        // Trivia integration for precise source reconstruction
        std::vector<Token> leadingTrivia;     // Trivia before this node
        std::vector<Token> trailingTrivia;    // Trivia after this node
        
        // Optional metadata
        bool isValid = true;          // Validation flag
        std::string errorMessage;     // For error nodes
        std::string description;      // Human-readable description
        
        // Constructor
        explicit Node(NodeKind nodeKind, size_t start = 0, size_t end = 0)
            : kind(nodeKind), startPos(start), endPos(end) {}
        
        // Virtual destructor for proper cleanup
        virtual ~Node() = default;
        
        // Element management
        void addNode(std::unique_ptr<Node> node);
        void addChild(std::unique_ptr<Node> node) { addNode(std::move(node)); }
        void addToken(const Token& token);
        void addWhitespace(const Token& whitespace);
        void addComment(const Token& comment);
        void addTrivia(const Token& trivia);
        
        // Navigation helpers
        std::vector<Node*> getChildNodes() const;
        std::vector<Token> getTokens() const;
        std::vector<Token> getAllTokens() const;
        Node* findChild(NodeKind nodeKind) const;
        std::vector<Node*> findChildren(NodeKind nodeKind) const;
        
        // Source reconstruction
        std::string getText() const;
        std::string getTextWithoutTrivia() const;
        std::string reconstructSource() const;  // Rebuild original source with all trivia
        
        // Trivia management
        void attachTriviaFromToken(const Token& token);
        void addLeadingTrivia(const std::vector<Token>& trivia);
        void addTrailingTrivia(const std::vector<Token>& trivia);
        const std::vector<Token>& getLeadingTrivia() const { return leadingTrivia; }
        const std::vector<Token>& getTrailingTrivia() const { return trailingTrivia; }
        
        // Tree traversal helpers
        void setSourceSpan(size_t start, size_t end);
        void setError(const std::string& message);
        void setDescription(const std::string& desc);
        
        // Validation helpers
        bool hasErrors() const;
        std::vector<std::string> getErrorMessages() const;
        
        // Debug helpers
        std::string getKindName() const;
        std::string toString(int indent = 0) const;
        std::string toStringWithTrivia(int indent = 0) const;
        
        // Filtering helpers
        std::vector<Node*> getSignificantChildren() const;  // Excludes trivia
        std::vector<Token> getSignificantTokens() const;    // Excludes trivia
    };

    // Specialized node for individual tokens
    class TokenNode : public Node {
    public:
        Token token;
        
        explicit TokenNode(const Token& tok)
            : Node(NodeKind::TOKEN_NODE, tok.start, tok.end), token(tok) {}
        
        std::string getText() const { return token.lexeme; }
    };

    // Specialized node for whitespace preservation
    class WhitespaceNode : public Node {
    public:
        Token whitespace;
        
        explicit WhitespaceNode(const Token& ws)
            : Node(NodeKind::WHITESPACE_NODE, ws.start, ws.end), whitespace(ws) {}
        
        std::string getText() const { return whitespace.lexeme; }
        std::string reconstructSource() const { return whitespace.lexeme; }
    };

    // Specialized node for comment preservation
    class CommentNode : public Node {
    public:
        Token comment;
        bool isLineComment;
        bool isBlockComment;
        
        explicit CommentNode(const Token& comm)
            : Node(NodeKind::COMMENT_NODE, comm.start, comm.end), 
              comment(comm),
              isLineComment(comm.lexeme.substr(0, 2) == "//"),
              isBlockComment(comm.lexeme.substr(0, 2) == "/*") {}
        
        std::string getText() const { return comment.lexeme; }
    };

    // Specialized node for general trivia (newlines, etc.)
    class TriviaNode : public Node {
    public:
        Token trivia;
        
        explicit TriviaNode(const Token& triv)
            : Node(NodeKind::TRIVIA_NODE, triv.start, triv.end), trivia(triv) {}
        
        std::string getText() const { return trivia.lexeme; }
    };

    // Specialized error recovery node types
    class ErrorNode : public Node {
    public:
        std::vector<Token> skippedTokens;  // Tokens skipped during recovery
        std::string expectedTokenName;     // What was expected (as string)
        std::string actualTokenName;       // What was found (as string)
        
        ErrorNode(const std::string& message, size_t start = 0, size_t end = 0)
            : Node(NodeKind::ERROR_NODE, start, end), 
              expectedTokenName("UNDEFINED"), 
              actualTokenName("UNDEFINED") {
            setError(message);
            isValid = false;
        }
        
        void addSkippedToken(const Token& token) {
            skippedTokens.push_back(token);
        }
        
        void setExpectedActual(const std::string& expected, const std::string& actual) {
            expectedTokenName = expected;
            actualTokenName = actual;
        }
    };

    class MissingNode : public Node {
    public:
        NodeKind expectedKind;             // What kind of node was expected
        
        MissingNode(NodeKind expected, const std::string& description, size_t start = 0, size_t end = 0)
            : Node(NodeKind::MISSING_NODE, start, end), expectedKind(expected) {
            setDescription(description);
            isValid = false;
        }
    };

    class IncompleteNode : public Node {
    public:
        NodeKind targetKind;               // What this was trying to be
        std::vector<std::string> missingElements;  // What's missing
        
        IncompleteNode(NodeKind target, const std::string& description, size_t start = 0, size_t end = 0)
            : Node(NodeKind::INCOMPLETE_NODE, start, end), targetKind(target) {
            setDescription(description);
            isValid = false;
        }
        
        void addMissingElement(const std::string& element) {
            missingElements.push_back(element);
        }
    };

    // Factory functions for creating nodes
    std::unique_ptr<Node> createNode(NodeKind kind, size_t start = 0, size_t end = 0);
    std::unique_ptr<TokenNode> createTokenNode(const Token& token);
    std::unique_ptr<WhitespaceNode> createWhitespaceNode(const Token& whitespace);
    std::unique_ptr<CommentNode> createCommentNode(const Token& comment);
    std::unique_ptr<TriviaNode> createTriviaNode(const Token& trivia);
    std::unique_ptr<ErrorNode> createErrorNode(const std::string& message, size_t start = 0, size_t end = 0);
    std::unique_ptr<MissingNode> createMissingNode(NodeKind expectedKind, const std::string& description, size_t start = 0, size_t end = 0);
    std::unique_ptr<IncompleteNode> createIncompleteNode(NodeKind targetKind, const std::string& description, size_t start = 0, size_t end = 0);
    
    // Utility functions
    std::string nodeKindToString(NodeKind kind);
    bool isStatementNode(NodeKind kind);
    bool isExpressionNode(NodeKind kind);
    bool isDeclarationNode(NodeKind kind);
    bool isErrorRecoveryNode(NodeKind kind);
    bool isTriviaNode(NodeKind kind);
    
    // Token classification helpers
    bool isWhitespaceToken(const Token& token);
    bool isCommentToken(const Token& token);
    bool isTriviaToken(const Token& token);
    bool isSignificantToken(const Token& token);
    
    // CST construction helpers
    class CSTBuilder {
    public:
        // Add elements while preserving source order
        void addSignificantNode(std::unique_ptr<Node> node);
        void addToken(const Token& token);
        void addAllTokens(const std::vector<Token>& tokens);
        
        // Finalize and return the CST
        std::unique_ptr<Node> build(NodeKind rootKind);
        
    private:
        std::vector<CSTElement> elements_;
        size_t startPos_ = 0;
        size_t endPos_ = 0;
    };
    
} // namespace CST

#endif // CST_H