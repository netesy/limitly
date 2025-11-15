#ifndef CST_UTILS_H
#define CST_UTILS_H

#include "cst.hh"
#include <functional>
#include <vector>
#include <string>
#include <unordered_set>
#include <ostream>

namespace CST {

    // Forward declarations
    class Node;

    // Forward declarations for function types
    using NodeVisitor = std::function<void(const Node*)>;
    using NodePredicate = std::function<bool(const Node*)>;
    using TokenVisitor = std::function<void(const Token&)>;
    using TokenPredicate = std::function<bool(const Token&)>;

    // Traversal utilities
    namespace Traversal {
        
        // Tree traversal methods
        void forEachChild(const Node* node, NodeVisitor visitor);
        void forEachDescendant(const Node* node, NodeVisitor visitor);
        void forEachToken(const Node* node, TokenVisitor visitor);
        void forEachSignificantToken(const Node* node, TokenVisitor visitor);
        
        // Depth-first traversal with pre/post order options
        void traversePreOrder(const Node* node, NodeVisitor visitor);
        void traversePostOrder(const Node* node, NodeVisitor visitor);
        
        // Breadth-first traversal
        void traverseBreadthFirst(const Node* node, NodeVisitor visitor);
        
        // Find operations
        const Node* findFirst(const Node* root, NodePredicate predicate);
        std::vector<const Node*> findAll(const Node* root, NodePredicate predicate);
        const Node* findByKind(const Node* root, NodeKind kind);
        std::vector<const Node*> findAllByKind(const Node* root, NodeKind kind);
        
        // Path operations
        std::vector<const Node*> getPath(const Node* root, const Node* target);
        const Node* getParent(const Node* root, const Node* child);
        std::vector<const Node*> getSiblings(const Node* root, const Node* node);
        
        // Position-based queries
        const Node* findNodeAtPosition(const Node* root, size_t position);
        std::vector<const Node*> findNodesInRange(const Node* root, size_t start, size_t end);
        
    } // namespace Traversal

    // Token extraction utilities
    namespace TokenUtils {
        
        // Get all tokens from a node and its descendants
        std::vector<Token> getTokens(const Node* node);
        std::vector<Token> getSignificantTokens(const Node* node);
        std::vector<Token> getTriviaTokens(const Node* node);
        
        // Get tokens by type
        std::vector<Token> getTokensByType(const Node* node, TokenType type);
        std::vector<Token> getWhitespaceTokens(const Node* node);
        std::vector<Token> getCommentTokens(const Node* node);
        
        // Token filtering
        std::vector<Token> filterTokens(const std::vector<Token>& tokens, TokenPredicate predicate);
        std::vector<Token> excludeTrivia(const std::vector<Token>& tokens);
        std::vector<Token> onlyTrivia(const std::vector<Token>& tokens);
        
        // Token position utilities
        Token getFirstToken(const Node* node);
        Token getLastToken(const Node* node);
        std::vector<Token> getTokensInRange(const Node* node, size_t start, size_t end);
        
    } // namespace TokenUtils

    // Text reconstruction utilities
    namespace TextUtils {
        
        // Basic text extraction
        std::string getText(const Node* node);
        std::string getTextWithoutTrivia(const Node* node);
        std::string getTextWithNormalizedWhitespace(const Node* node);
        
        // Source reconstruction with formatting options
        struct ReconstructionOptions {
            bool preserveWhitespace = true;
            bool preserveComments = true;
            bool normalizeNewlines = false;
            std::string indentString = "    ";  // 4 spaces
            bool addMissingWhitespace = false;
        };
        
        std::string reconstructSource(const Node* node, const ReconstructionOptions& options = {});
        
        // Text manipulation
        std::string normalizeWhitespace(const std::string& text);
        std::string removeComments(const std::string& text);
        std::string addIndentation(const std::string& text, int indentLevel, const std::string& indentString = "    ");
        
        // Source span utilities
        struct SourceSpan {
            size_t start;
            size_t end;
            size_t line;
            size_t column;
            std::string text;
        };
        
        SourceSpan getSourceSpan(const Node* node);
        std::vector<SourceSpan> getSourceSpans(const std::vector<const Node*>& nodes);
        
    } // namespace TextUtils

    // Validation utilities
    namespace Validation {
        
        // Validation result structure
        struct ValidationResult {
            bool isValid = true;
            std::vector<std::string> errors;
            std::vector<std::string> warnings;
            std::vector<const Node*> errorNodes;
            std::vector<const Node*> warningNodes;
            
            void addError(const std::string& message, const Node* node = nullptr);
            void addWarning(const std::string& message, const Node* node = nullptr);
            bool hasErrors() const { return !errors.empty(); }
            bool hasWarnings() const { return !warnings.empty(); }
        };
        
        // Validation functions
        ValidationResult validateCST(const Node* root);
        ValidationResult validateStructure(const Node* root);
        ValidationResult validateSourceSpans(const Node* root);
        ValidationResult validateTokenOrder(const Node* root);
        ValidationResult validateCompleteness(const Node* root);
        
        // Specific validation checks
        bool hasValidSourceSpans(const Node* node);
        bool hasConsistentTokenOrder(const Node* node);
        bool isComplete(const Node* node);
        bool hasCircularReferences(const Node* root);
        
        // Error node analysis
        std::vector<const Node*> findErrorNodes(const Node* root);
        std::vector<const Node*> findMissingNodes(const Node* root);
        std::vector<const Node*> findIncompleteNodes(const Node* root);
        
    } // namespace Validation

    // Analysis utilities
    namespace Analysis {
        
        // Tree statistics
        struct TreeStatistics {
            size_t totalNodes = 0;
            size_t totalTokens = 0;
            size_t significantTokens = 0;
            size_t triviaTokens = 0;
            size_t errorNodes = 0;
            size_t maxDepth = 0;
            std::unordered_map<NodeKind, size_t> nodeKindCounts;
            std::unordered_map<TokenType, size_t> tokenTypeCounts;
        };
        
        TreeStatistics analyzeTree(const Node* root);
        
        // Node relationship analysis
        std::vector<const Node*> getAncestors(const Node* root, const Node* node);
        std::vector<const Node*> getDescendants(const Node* node);
        size_t getDepth(const Node* root, const Node* node);
        size_t getMaxDepth(const Node* root);
        
        // Content analysis
        std::vector<std::string> extractIdentifiers(const Node* root);
        std::vector<std::string> extractLiterals(const Node* root);
        std::vector<std::string> extractComments(const Node* root);
        
        // Complexity metrics
        size_t countNodes(const Node* root);
        size_t countTokens(const Node* root);
        size_t countSignificantNodes(const Node* root);
        double calculateComplexity(const Node* root);
        
    } // namespace Analysis

    // Comparison utilities
    namespace Comparison {
        
        // Tree comparison options
        struct ComparisonOptions {
            bool ignoreTrivia = false;
            bool ignoreSourcePositions = true;
            bool ignoreErrorNodes = false;
            bool compareTokenText = true;
            bool compareNodeStructure = true;
        };
        
        // Comparison results
        struct ComparisonResult {
            bool isEqual = true;
            std::vector<std::string> differences;
            std::vector<const Node*> differentNodes;
            
            void addDifference(const std::string& message, const Node* node = nullptr);
        };
        
        // Tree comparison functions
        ComparisonResult compareCSTs(const Node* left, const Node* right, const ComparisonOptions& options = {});
        bool areEqual(const Node* left, const Node* right, const ComparisonOptions& options = {});
        bool areStructurallyEqual(const Node* left, const Node* right);
        bool areTextuallyEqual(const Node* left, const Node* right);
        
    } // namespace Comparison

    // Transformation utilities
    namespace Transform {
        
        // Node transformation functions
        using NodeTransformer = std::function<std::unique_ptr<Node>(const Node*)>;
        using TokenTransformer = std::function<Token(const Token&)>;
        
        std::unique_ptr<Node> transformTree(const Node* root, NodeTransformer transformer);
        std::unique_ptr<Node> transformTokens(const Node* root, TokenTransformer transformer);
        
        // Common transformations
        std::unique_ptr<Node> removeTrivia(const Node* root);
        std::unique_ptr<Node> removeComments(const Node* root);
        std::unique_ptr<Node> removeErrorNodes(const Node* root);
        std::unique_ptr<Node> normalizeWhitespace(const Node* root);
        
        // Filtering transformations
        std::unique_ptr<Node> filterNodes(const Node* root, NodePredicate predicate);
        std::unique_ptr<Node> filterTokens(const Node* root, TokenPredicate predicate);
        
    } // namespace Transform

    // Query utilities
    namespace Query {
        
        // XPath-like query system for CST
        class CSTQuery {
        public:
            explicit CSTQuery(const std::string& queryString);
            
            std::vector<const Node*> execute(const Node* root) const;
            const Node* executeFirst(const Node* root) const;
            
            // Query builder methods
            static CSTQuery byKind(NodeKind kind);
            static CSTQuery byText(const std::string& text);
            static CSTQuery byPosition(size_t position);
            static CSTQuery byRange(size_t start, size_t end);
            
        private:
            std::string query_;
            // Query parsing and execution implementation
        };
        
        // Convenience query functions
        std::vector<const Node*> selectByKind(const Node* root, NodeKind kind);
        std::vector<const Node*> selectByText(const Node* root, const std::string& text);
        std::vector<const Node*> selectByPredicate(const Node* root, NodePredicate predicate);
        
    } // namespace Query

    // Simple utility functions for CST manipulation
    namespace Utils {
        
        // Text reconstruction utilities
        std::string getText(const Node* node);
        std::string getTextWithoutTrivia(const Node* node);
        std::string reconstructSource(const Node* node);
        
        // Token extraction utilities
        std::vector<Token> getAllTokens(const Node* node);
        std::vector<Token> getSignificantTokens(const Node* node);
        
        // Tree traversal utilities
        void forEachChild(const Node* node, std::function<void(const Node*)> visitor);
        void forEachDescendant(const Node* node, std::function<void(const Node*)> visitor);
        
        // Find operations
        const Node* findByKind(const Node* root, NodeKind kind);
        std::vector<const Node*> findAllByKind(const Node* root, NodeKind kind);
        
        // Validation utilities
        bool validateCST(const Node* root);
        std::vector<const Node*> findErrorNodes(const Node* root);
        
        // Analysis utilities
        size_t countNodes(const Node* root);
        size_t countTokens(const Node* root);

        // Simple printing utilities
        namespace Printer {

        // Forward declaration
        void printNode(const Node* node, std::ostream& out, int indent, bool includeTrivia);

        std::string printCST(const Node* root, bool includeTrivia);

        std::string serializeToJSON(const Node* root);

        } // namespace Printer
        
    } // namespace Utils

} // namespace CST

#endif // CST_UTILS_H
