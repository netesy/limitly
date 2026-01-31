#ifndef CST_UTILS_H
#define CST_UTILS_H

#include "../cst.hh"
#include <functional>
#include <vector>
#include <string>
#include <unordered_set>
#include <ostream>

namespace LM {
namespace Frontend {
namespace CST {

    // Forward declarations
    class Node;

    // Forward declarations for function types
    using NodeVisitor = std::function<void(const LM::Frontend::CST::Node*)>;
    using NodePredicate = std::function<bool(const LM::Frontend::CST::Node*)>;
    using TokenVisitor = std::function<void(const LM::Frontend::Token&)>;
    using TokenPredicate = std::function<bool(const LM::Frontend::Token&)>;

    // Traversal utilities
    namespace Traversal {
        
        // Tree traversal methods
        void forEachChild(const LM::Frontend::CST::Node* node, NodeVisitor visitor);
        void forEachDescendant(const LM::Frontend::CST::Node* node, NodeVisitor visitor);
        void forEachToken(const LM::Frontend::CST::Node* node, TokenVisitor visitor);
        void forEachSignificantToken(const LM::Frontend::CST::Node* node, TokenVisitor visitor);
        
        // Depth-first traversal with pre/post order options
        void traversePreOrder(const LM::Frontend::CST::Node* node, NodeVisitor visitor);
        void traversePostOrder(const LM::Frontend::CST::Node* node, NodeVisitor visitor);
        
        // Breadth-first traversal
        void traverseBreadthFirst(const LM::Frontend::CST::Node* node, NodeVisitor visitor);
        
        // Find operations
        const LM::Frontend::CST::Node* findFirst(const LM::Frontend::CST::Node* root, NodePredicate predicate);
        std::vector<const LM::Frontend::CST::Node*> findAll(const LM::Frontend::CST::Node* root, NodePredicate predicate);
        const LM::Frontend::CST::Node* findByKind(const LM::Frontend::CST::Node* root, LM::Frontend::CST::NodeKind kind);
        std::vector<const LM::Frontend::CST::Node*> findAllByKind(const LM::Frontend::CST::Node* root, LM::Frontend::CST::NodeKind kind);
        
        // Path operations
        std::vector<const LM::Frontend::CST::Node*> getPath(const LM::Frontend::CST::Node* root, const LM::Frontend::CST::Node* target);
        const LM::Frontend::CST::Node* getParent(const LM::Frontend::CST::Node* root, const LM::Frontend::CST::Node* child);
        std::vector<const LM::Frontend::CST::Node*> getSiblings(const LM::Frontend::CST::Node* root, const LM::Frontend::CST::Node* node);
        
        // Position-based queries
        const LM::Frontend::CST::Node* findNodeAtPosition(const LM::Frontend::CST::Node* root, size_t position);
        std::vector<const LM::Frontend::CST::Node*> findNodesInRange(const LM::Frontend::CST::Node* root, size_t start, size_t end);
        
    } // namespace Traversal

    // Token extraction utilities
    namespace TokenUtils {
        
        // Get all tokens from a node and its descendants
        std::vector<LM::Frontend::Token> getTokens(const LM::Frontend::CST::Node* node);
        std::vector<LM::Frontend::Token> getSignificantTokens(const LM::Frontend::CST::Node* node);
        std::vector<LM::Frontend::Token> getTriviaTokens(const LM::Frontend::CST::Node* node);
        
        // Get tokens by type
        std::vector<LM::Frontend::Token> getTokensByType(const LM::Frontend::CST::Node* node, LM::Frontend::TokenType type);
        std::vector<LM::Frontend::Token> getWhitespaceTokens(const LM::Frontend::CST::Node* node);
        std::vector<LM::Frontend::Token> getCommentTokens(const LM::Frontend::CST::Node* node);
        
        // Token filtering
        std::vector<LM::Frontend::Token> filterTokens(const std::vector<LM::Frontend::Token>& tokens, TokenPredicate predicate);
        std::vector<LM::Frontend::Token> excludeTrivia(const std::vector<LM::Frontend::Token>& tokens);
        std::vector<LM::Frontend::Token> onlyTrivia(const std::vector<LM::Frontend::Token>& tokens);
        
        // Token position utilities
        LM::Frontend::Token getFirstToken(const LM::Frontend::CST::Node* node);
        LM::Frontend::Token getLastToken(const LM::Frontend::CST::Node* node);
        std::vector<LM::Frontend::Token> getTokensInRange(const LM::Frontend::CST::Node* node, size_t start, size_t end);
        
    } // namespace TokenUtils

    // Text reconstruction utilities
    namespace TextUtils {
        
        // Basic text extraction
        std::string getText(const LM::Frontend::CST::Node* node);
        std::string getTextWithoutTrivia(const LM::Frontend::CST::Node* node);
        std::string getTextWithNormalizedWhitespace(const LM::Frontend::CST::Node* node);
        
        // Source reconstruction with formatting options
        struct ReconstructionOptions {
            bool preserveWhitespace = true;
            bool preserveComments = true;
            bool normalizeNewlines = false;
            std::string indentString = "    ";  // 4 spaces
            bool addMissingWhitespace = false;
        };
        
        std::string reconstructSource(const LM::Frontend::CST::Node* node, const ReconstructionOptions& options = {});
        
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
        
        SourceSpan getSourceSpan(const LM::Frontend::CST::Node* node);
        std::vector<SourceSpan> getSourceSpans(const std::vector<const LM::Frontend::CST::Node*>& nodes);
        
    } // namespace TextUtils

    // Validation utilities
    namespace Validation {
        
        // Validation result structure
        struct ValidationResult {
            bool isValid = true;
            std::vector<std::string> errors;
            std::vector<std::string> warnings;
            std::vector<const LM::Frontend::CST::Node*> errorNodes;
            std::vector<const LM::Frontend::CST::Node*> warningNodes;
            
            void addError(const std::string& message, const LM::Frontend::CST::Node* node = nullptr);
            void addWarning(const std::string& message, const LM::Frontend::CST::Node* node = nullptr);
            bool hasErrors() const { return !errors.empty(); }
            bool hasWarnings() const { return !warnings.empty(); }
        };
        
        // Validation functions
        ValidationResult validateCST(const LM::Frontend::CST::Node* root);
        ValidationResult validateStructure(const LM::Frontend::CST::Node* root);
        ValidationResult validateSourceSpans(const LM::Frontend::CST::Node* root);
        ValidationResult validateTokenOrder(const LM::Frontend::CST::Node* root);
        ValidationResult validateCompleteness(const LM::Frontend::CST::Node* root);
        
        // Specific validation checks
        bool hasValidSourceSpans(const LM::Frontend::CST::Node* node);
        bool hasConsistentTokenOrder(const LM::Frontend::CST::Node* node);
        bool isComplete(const LM::Frontend::CST::Node* node);
        bool hasCircularReferences(const LM::Frontend::CST::Node* root);
        
        // Error node analysis
        std::vector<const LM::Frontend::CST::Node*> findErrorNodes(const LM::Frontend::CST::Node* root);
        std::vector<const LM::Frontend::CST::Node*> findMissingNodes(const LM::Frontend::CST::Node* root);
        std::vector<const LM::Frontend::CST::Node*> findIncompleteNodes(const LM::Frontend::CST::Node* root);
        
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
            std::unordered_map<LM::Frontend::CST::NodeKind, size_t> nodeKindCounts;
            std::unordered_map<LM::Frontend::TokenType, size_t> tokenTypeCounts;
        };
        
        TreeStatistics analyzeTree(const LM::Frontend::CST::Node* root);
        
        // Node relationship analysis
        std::vector<const LM::Frontend::CST::Node*> getAncestors(const LM::Frontend::CST::Node* root, const LM::Frontend::CST::Node* node);
        std::vector<const LM::Frontend::CST::Node*> getDescendants(const LM::Frontend::CST::Node* node);
        size_t getDepth(const LM::Frontend::CST::Node* root, const LM::Frontend::CST::Node* node);
        size_t getMaxDepth(const LM::Frontend::CST::Node* root);
        
        // Content analysis
        std::vector<std::string> extractIdentifiers(const LM::Frontend::CST::Node* root);
        std::vector<std::string> extractLiterals(const LM::Frontend::CST::Node* root);
        std::vector<std::string> extractComments(const LM::Frontend::CST::Node* root);
        
        // Complexity metrics
        size_t countNodes(const LM::Frontend::CST::Node* root);
        size_t countTokens(const LM::Frontend::CST::Node* root);
        size_t countSignificantNodes(const LM::Frontend::CST::Node* root);
        double calculateComplexity(const LM::Frontend::CST::Node* root);
        
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
            std::vector<const LM::Frontend::CST::Node*> differentNodes;
            
            void addDifference(const std::string& message, const LM::Frontend::CST::Node* node = nullptr);
        };
        
        // Tree comparison functions
        ComparisonResult compareCSTs(const LM::Frontend::CST::Node* left, const LM::Frontend::CST::Node* right, const ComparisonOptions& options = {});
        bool areEqual(const LM::Frontend::CST::Node* left, const LM::Frontend::CST::Node* right, const ComparisonOptions& options = {});
        bool areStructurallyEqual(const LM::Frontend::CST::Node* left, const LM::Frontend::CST::Node* right);
        bool areTextuallyEqual(const LM::Frontend::CST::Node* left, const LM::Frontend::CST::Node* right);
        
    } // namespace Comparison

    // Transformation utilities
    namespace Transform {
        
        // Node transformation functions
        using NodeTransformer = std::function<std::unique_ptr<Node>(const LM::Frontend::CST::Node*)>;
        using TokenTransformer = std::function<LM::Frontend::Token(const LM::Frontend::Token&)>;
        
        std::unique_ptr<Node> transformTree(const LM::Frontend::CST::Node* root, NodeTransformer transformer);
        std::unique_ptr<Node> transformTokens(const LM::Frontend::CST::Node* root, TokenTransformer transformer);
        
        // Common transformations
        std::unique_ptr<Node> removeTrivia(const LM::Frontend::CST::Node* root);
        std::unique_ptr<Node> removeComments(const LM::Frontend::CST::Node* root);
        std::unique_ptr<Node> removeErrorNodes(const LM::Frontend::CST::Node* root);
        std::unique_ptr<Node> normalizeWhitespace(const LM::Frontend::CST::Node* root);
        
        // Filtering transformations
        std::unique_ptr<Node> filterNodes(const LM::Frontend::CST::Node* root, NodePredicate predicate);
        std::unique_ptr<Node> filterTokens(const LM::Frontend::CST::Node* root, TokenPredicate predicate);
        
    } // namespace Transform

    // Query utilities
    namespace Query {
        
        // XPath-like query system for CST
        class CSTQuery {
        public:
            explicit CSTQuery(const std::string& queryString);
            
            std::vector<const LM::Frontend::CST::Node*> execute(const LM::Frontend::CST::Node* root) const;
            const LM::Frontend::CST::Node* executeFirst(const LM::Frontend::CST::Node* root) const;
            
            // Query builder methods
            static CSTQuery byKind(LM::Frontend::CST::NodeKind kind);
            static CSTQuery byText(const std::string& text);
            static CSTQuery byPosition(size_t position);
            static CSTQuery byRange(size_t start, size_t end);
            
        private:
            std::string query_;
            // Query parsing and execution implementation
        };
        
        // Convenience query functions
        std::vector<const LM::Frontend::CST::Node*> selectByKind(const LM::Frontend::CST::Node* root, LM::Frontend::CST::NodeKind kind);
        std::vector<const LM::Frontend::CST::Node*> selectByText(const LM::Frontend::CST::Node* root, const std::string& text);
        std::vector<const LM::Frontend::CST::Node*> selectByPredicate(const LM::Frontend::CST::Node* root, NodePredicate predicate);
        
    } // namespace Query

    // Simple utility functions for CST manipulation
    namespace Utils {
        
        // Text reconstruction utilities
        std::string getText(const LM::Frontend::CST::Node* node);
        std::string getTextWithoutTrivia(const LM::Frontend::CST::Node* node);
        std::string reconstructSource(const LM::Frontend::CST::Node* node);
        
        // Token extraction utilities
        std::vector<LM::Frontend::Token> getAllTokens(const LM::Frontend::CST::Node* node);
        std::vector<LM::Frontend::Token> getSignificantTokens(const LM::Frontend::CST::Node* node);
        
        // Tree traversal utilities
        void forEachChild(const LM::Frontend::CST::Node* node, std::function<void(const LM::Frontend::CST::Node*)> visitor);
        void forEachDescendant(const LM::Frontend::CST::Node* node, std::function<void(const LM::Frontend::CST::Node*)> visitor);
        
        // Find operations
        const LM::Frontend::CST::Node* findByKind(const LM::Frontend::CST::Node* root, LM::Frontend::CST::NodeKind kind);
        std::vector<const LM::Frontend::CST::Node*> findAllByKind(const LM::Frontend::CST::Node* root, LM::Frontend::CST::NodeKind kind);
        
        // Validation utilities
        bool validateCST(const LM::Frontend::CST::Node* root);
        std::vector<const LM::Frontend::CST::Node*> findErrorNodes(const LM::Frontend::CST::Node* root);
        
        // Analysis utilities
        size_t countNodes(const LM::Frontend::CST::Node* root);
        size_t countTokens(const LM::Frontend::CST::Node* root);

        // Simple printing utilities
        namespace Printer {

        // Forward declaration
        void printNode(const LM::Frontend::CST::Node* node, std::ostream& out, int indent, bool includeTrivia);

        std::string printCST(const LM::Frontend::CST::Node* root, bool includeTrivia);

        std::string serializeToJSON(const LM::Frontend::CST::Node* root);

        } // namespace Printer
        
    } // namespace Utils

} // namespace CST
} // namespace Frontend
} // namespace LM

#endif // CST_UTILS_H
