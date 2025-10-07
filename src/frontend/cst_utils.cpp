#include "cst_utils.hh"
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <set>
#include <cmath>

namespace CST {

    // Traversal utilities implementation
    namespace Traversal {
        
        void forEachChild(const CST::Node* node, CST::NodeVisitor visitor) {
            if (!node || !visitor) return;
            
            auto children = node->getChildNodes();
            for (const auto* child : children) {
                if (child) {
                    visitor(child);
                }
            }
        }
        
        void forEachDescendant(const CST::Node* node, CST::NodeVisitor visitor) {
            if (!node || !visitor) return;
            
            traversePreOrder(node, visitor);
        }
        
        void forEachToken(const Node* node, TokenVisitor visitor) {
            if (!node || !visitor) return;
            
            auto tokens = node->getAllTokens();
            for (const auto& token : tokens) {
                visitor(token);
            }
        }
        
        void forEachSignificantToken(const Node* node, TokenVisitor visitor) {
            if (!node || !visitor) return;
            
            auto tokens = node->getAllTokens();
            for (const auto& token : tokens) {
                if (isSignificantToken(token)) {
                    visitor(token);
                }
            }
        }
        
        void traversePreOrder(const Node* node, NodeVisitor visitor) {
            if (!node || !visitor) return;
            
            visitor(node);
            
            auto children = node->getChildNodes();
            for (const auto* child : children) {
                if (child) {
                    traversePreOrder(child, visitor);
                }
            }
        }
        
        void traversePostOrder(const Node* node, NodeVisitor visitor) {
            if (!node || !visitor) return;
            
            auto children = node->getChildNodes();
            for (const auto* child : children) {
                if (child) {
                    traversePostOrder(child, visitor);
                }
            }
            
            visitor(node);
        }
        
        void traverseBreadthFirst(const Node* node, NodeVisitor visitor) {
            if (!node || !visitor) return;
            
            std::queue<const Node*> queue;
            queue.push(node);
            
            while (!queue.empty()) {
                const Node* current = queue.front();
                queue.pop();
                
                visitor(current);
                
                auto children = current->getChildNodes();
                for (const auto* child : children) {
                    if (child) {
                        queue.push(child);
                    }
                }
            }
        }
        
        const Node* findFirst(const Node* root, NodePredicate predicate) {
            if (!root || !predicate) return nullptr;
            
            const Node* result = nullptr;
            traversePreOrder(root, [&](const Node* node) {
                if (!result && predicate(node)) {
                    result = node;
                }
            });
            
            return result;
        }
        
        std::vector<const Node*> findAll(const Node* root, NodePredicate predicate) {
            std::vector<const Node*> results;
            if (!root || !predicate) return results;
            
            traversePreOrder(root, [&](const Node* node) {
                if (predicate(node)) {
                    results.push_back(node);
                }
            });
            
            return results;
        }
        
        const Node* findByKind(const Node* root, NodeKind kind) {
            return findFirst(root, [kind](const Node* node) {
                return node->kind == kind;
            });
        }
        
        std::vector<const Node*> findAllByKind(const Node* root, NodeKind kind) {
            return findAll(root, [kind](const Node* node) {
                return node->kind == kind;
            });
        }
        
        std::vector<const Node*> getPath(const Node* root, const Node* target) {
            std::vector<const Node*> path;
            if (!root || !target) return path;
            
            std::function<bool(const Node*, std::vector<const Node*>&)> findPath = 
                [&](const Node* node, std::vector<const Node*>& currentPath) -> bool {
                currentPath.push_back(node);
                
                if (node == target) {
                    return true;
                }
                
                auto children = node->getChildNodes();
                for (const auto* child : children) {
                    if (child && findPath(child, currentPath)) {
                        return true;
                    }
                }
                
                currentPath.pop_back();
                return false;
            };
            
            findPath(root, path);
            return path;
        }
        
        const Node* getParent(const Node* root, const Node* child) {
            if (!root || !child || root == child) return nullptr;
            
            const Node* parent = nullptr;
            traversePreOrder(root, [&](const Node* node) {
                if (!parent) {
                    auto children = node->getChildNodes();
                    for (const auto* nodeChild : children) {
                        if (nodeChild == child) {
                            parent = node;
                            break;
                        }
                    }
                }
            });
            
            return parent;
        }
        
        std::vector<const Node*> getSiblings(const Node* root, const Node* node) {
            std::vector<const Node*> siblings;
            if (!root || !node) return siblings;
            
            const Node* parent = getParent(root, node);
            if (!parent) return siblings;
            
            auto children = parent->getChildNodes();
            for (const auto* child : children) {
                if (child && child != node) {
                    siblings.push_back(child);
                }
            }
            
            return siblings;
        }
        
        const Node* findNodeAtPosition(const Node* root, size_t position) {
            if (!root) return nullptr;
            
            const Node* result = nullptr;
            traversePreOrder(root, [&](const Node* node) {
                if (!result && position >= node->startPos && position <= node->endPos) {
                    result = node;
                }
            });
            
            return result;
        }
        
        std::vector<const Node*> findNodesInRange(const Node* root, size_t start, size_t end) {
            std::vector<const Node*> results;
            if (!root) return results;
            
            traversePreOrder(root, [&](const Node* node) {
                // Check if node overlaps with the range
                if (!(node->endPos < start || node->startPos > end)) {
                    results.push_back(node);
                }
            });
            
            return results;
        }
        
    } // namespace Traversal

    // Token extraction utilities implementation
    namespace TokenUtils {
        
        std::vector<Token> getTokens(const Node* node) {
            if (!node) return {};
            return node->getAllTokens();
        }
        
        std::vector<Token> getSignificantTokens(const Node* node) {
            if (!node) return {};
            
            auto allTokens = node->getAllTokens();
            std::vector<Token> significant;
            
            for (const auto& token : allTokens) {
                if (isSignificantToken(token)) {
                    significant.push_back(token);
                }
            }
            
            return significant;
        }
        
        std::vector<Token> getTriviaTokens(const Node* node) {
            if (!node) return {};
            
            auto allTokens = node->getAllTokens();
            std::vector<Token> trivia;
            
            for (const auto& token : allTokens) {
                if (isTriviaToken(token)) {
                    trivia.push_back(token);
                }
            }
            
            return trivia;
        }
        
        std::vector<Token> getTokensByType(const Node* node, TokenType type) {
            if (!node) return {};
            
            auto allTokens = node->getAllTokens();
            std::vector<Token> filtered;
            
            for (const auto& token : allTokens) {
                if (token.type == type) {
                    filtered.push_back(token);
                }
            }
            
            return filtered;
        }
        
        std::vector<Token> getWhitespaceTokens(const Node* node) {
            if (!node) return {};
            
            auto allTokens = node->getAllTokens();
            std::vector<Token> whitespace;
            
            for (const auto& token : allTokens) {
                if (isWhitespaceToken(token)) {
                    whitespace.push_back(token);
                }
            }
            
            return whitespace;
        }
        
        std::vector<Token> getCommentTokens(const Node* node) {
            if (!node) return {};
            
            auto allTokens = node->getAllTokens();
            std::vector<Token> comments;
            
            for (const auto& token : allTokens) {
                if (isCommentToken(token)) {
                    comments.push_back(token);
                }
            }
            
            return comments;
        }
        
        std::vector<Token> filterTokens(const std::vector<Token>& tokens, TokenPredicate predicate) {
            std::vector<Token> filtered;
            if (!predicate) return filtered;
            
            for (const auto& token : tokens) {
                if (predicate(token)) {
                    filtered.push_back(token);
                }
            }
            
            return filtered;
        }
        
        std::vector<Token> excludeTrivia(const std::vector<Token>& tokens) {
            return filterTokens(tokens, [](const Token& token) {
                return !isTriviaToken(token);
            });
        }
        
        std::vector<Token> onlyTrivia(const std::vector<Token>& tokens) {
            return filterTokens(tokens, [](const Token& token) {
                return isTriviaToken(token);
            });
        }
        
        Token getFirstToken(const Node* node) {
            if (!node) return Token{};
            
            auto tokens = node->getAllTokens();
            if (tokens.empty()) return Token{};
            
            return tokens.front();
        }
        
        Token getLastToken(const Node* node) {
            if (!node) return Token{};
            
            auto tokens = node->getAllTokens();
            if (tokens.empty()) return Token{};
            
            return tokens.back();
        }
        
        std::vector<Token> getTokensInRange(const Node* node, size_t start, size_t end) {
            if (!node) return {};
            
            auto allTokens = node->getAllTokens();
            std::vector<Token> inRange;
            
            for (const auto& token : allTokens) {
                size_t tokenEnd = token.end > 0 ? token.end : token.start + token.lexeme.length();
                if (!(tokenEnd < start || token.start > end)) {
                    inRange.push_back(token);
                }
            }
            
            return inRange;
        }
        
    } // namespace TokenUtils

    // Text reconstruction utilities implementation
    namespace TextUtils {
        
        std::string getText(const Node* node) {
            if (!node) return "";
            return node->getText();
        }
        
        std::string getTextWithoutTrivia(const Node* node) {
            if (!node) return "";
            return node->getTextWithoutTrivia();
        }
        
        std::string getTextWithNormalizedWhitespace(const Node* node) {
            if (!node) return "";
            
            std::string text = node->getText();
            return normalizeWhitespace(text);
        }
        
        std::string reconstructSource(const Node* node, const ReconstructionOptions& options) {
            if (!node) return "";
            
            std::string result;
            
            for (const auto& element : node->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    
                    if (!options.preserveWhitespace && isWhitespaceToken(token)) {
                        if (options.addMissingWhitespace) {
                            result += " ";  // Replace with single space
                        }
                        continue;
                    }
                    
                    if (!options.preserveComments && isCommentToken(token)) {
                        continue;
                    }
                    
                    std::string tokenText = token.lexeme;
                    if (options.normalizeNewlines && token.type == TokenType::NEWLINE) {
                        tokenText = "\n";
                    }
                    
                    result += tokenText;
                    
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        result += reconstructSource(childNode.get(), options);
                    }
                }
            }
            
            return result;
        }
        
        std::string normalizeWhitespace(const std::string& text) {
            std::string result;
            bool inWhitespace = false;
            
            for (char c : text) {
                if (std::isspace(c)) {
                    if (!inWhitespace) {
                        result += ' ';
                        inWhitespace = true;
                    }
                } else {
                    result += c;
                    inWhitespace = false;
                }
            }
            
            return result;
        }
        
        std::string removeComments(const std::string& text) {
            std::string result;
            bool inLineComment = false;
            bool inBlockComment = false;
            
            for (size_t i = 0; i < text.length(); ++i) {
                if (!inLineComment && !inBlockComment) {
                    if (i + 1 < text.length() && text.substr(i, 2) == "//") {
                        inLineComment = true;
                        i++; // Skip the second '/'
                        continue;
                    } else if (i + 1 < text.length() && text.substr(i, 2) == "/*") {
                        inBlockComment = true;
                        i++; // Skip the '*'
                        continue;
                    }
                }
                
                if (inLineComment && text[i] == '\n') {
                    inLineComment = false;
                    result += text[i]; // Keep the newline
                } else if (inBlockComment && i + 1 < text.length() && text.substr(i, 2) == "*/") {
                    inBlockComment = false;
                    i++; // Skip the '/'
                } else if (!inLineComment && !inBlockComment) {
                    result += text[i];
                }
            }
            
            return result;
        }
        
        std::string addIndentation(const std::string& text, int indentLevel, const std::string& indentString) {
            if (indentLevel <= 0) return text;
            
            std::string indent;
            for (int i = 0; i < indentLevel; ++i) {
                indent += indentString;
            }
            
            std::istringstream iss(text);
            std::ostringstream oss;
            std::string line;
            bool first = true;
            
            while (std::getline(iss, line)) {
                if (!first) {
                    oss << "\n";
                }
                oss << indent << line;
                first = false;
            }
            
            return oss.str();
        }
        
        SourceSpan getSourceSpan(const Node* node) {
            if (!node) return {0, 0, 0, 0, ""};
            
            return {
                node->startPos,
                node->endPos,
                0, // line calculation would need source context
                0, // column calculation would need source context
                node->getText()
            };
        }
        
        std::vector<SourceSpan> getSourceSpans(const std::vector<const Node*>& nodes) {
            std::vector<SourceSpan> spans;
            for (const auto* node : nodes) {
                spans.push_back(getSourceSpan(node));
            }
            return spans;
        }
        
    } // namespace TextUtils

    // Validation utilities implementation
    namespace Validation {
        
        void ValidationResult::addError(const std::string& message, const Node* node) {
            errors.push_back(message);
            if (node) {
                errorNodes.push_back(node);
            }
            isValid = false;
        }
        
        void ValidationResult::addWarning(const std::string& message, const Node* node) {
            warnings.push_back(message);
            if (node) {
                warningNodes.push_back(node);
            }
        }
        
        ValidationResult validateCST(const Node* root) {
            ValidationResult result;
            if (!root) {
                result.addError("Root node is null");
                return result;
            }
            
            // Combine all validation checks
            auto structureResult = validateStructure(root);
            auto spanResult = validateSourceSpans(root);
            auto tokenResult = validateTokenOrder(root);
            auto completenessResult = validateCompleteness(root);
            
            // Merge results
            result.errors.insert(result.errors.end(), structureResult.errors.begin(), structureResult.errors.end());
            result.warnings.insert(result.warnings.end(), structureResult.warnings.begin(), structureResult.warnings.end());
            result.errorNodes.insert(result.errorNodes.end(), structureResult.errorNodes.begin(), structureResult.errorNodes.end());
            result.warningNodes.insert(result.warningNodes.end(), structureResult.warningNodes.begin(), structureResult.warningNodes.end());
            
            result.errors.insert(result.errors.end(), spanResult.errors.begin(), spanResult.errors.end());
            result.warnings.insert(result.warnings.end(), spanResult.warnings.begin(), spanResult.warnings.end());
            result.errorNodes.insert(result.errorNodes.end(), spanResult.errorNodes.begin(), spanResult.errorNodes.end());
            result.warningNodes.insert(result.warningNodes.end(), spanResult.warningNodes.begin(), spanResult.warningNodes.end());
            
            result.errors.insert(result.errors.end(), tokenResult.errors.begin(), tokenResult.errors.end());
            result.warnings.insert(result.warnings.end(), tokenResult.warnings.begin(), tokenResult.warnings.end());
            result.errorNodes.insert(result.errorNodes.end(), tokenResult.errorNodes.begin(), tokenResult.errorNodes.end());
            result.warningNodes.insert(result.warningNodes.end(), tokenResult.warningNodes.begin(), tokenResult.warningNodes.end());
            
            result.errors.insert(result.errors.end(), completenessResult.errors.begin(), completenessResult.errors.end());
            result.warnings.insert(result.warnings.end(), completenessResult.warnings.begin(), completenessResult.warnings.end());
            result.errorNodes.insert(result.errorNodes.end(), completenessResult.errorNodes.begin(), completenessResult.errorNodes.end());
            result.warningNodes.insert(result.warningNodes.end(), completenessResult.warningNodes.begin(), completenessResult.warningNodes.end());
            
            result.isValid = result.errors.empty();
            return result;
        }
        
        ValidationResult validateStructure(const Node* root) {
            ValidationResult result;
            if (!root) {
                result.addError("Root node is null");
                return result;
            }
            
            // Check for circular references
            if (hasCircularReferences(root)) {
                result.addError("Circular references detected in CST", root);
            }
            
            // Validate each node
            Traversal::traversePreOrder(root, [&](const Node* node) {
                if (!node) {
                    result.addError("Null node found in tree");
                    return;
                }
                
                // Check node kind validity
                if (node->kind == static_cast<NodeKind>(-1)) {
                    result.addError("Invalid node kind", node);
                }
                
                // Check error nodes
                if (isErrorRecoveryNode(node->kind) && node->errorMessage.empty()) {
                    result.addWarning("Error recovery node without error message", node);
                }
            });
            
            return result;
        }
        
        ValidationResult validateSourceSpans(const Node* root) {
            ValidationResult result;
            if (!root) {
                result.addError("Root node is null");
                return result;
            }
            
            Traversal::traversePreOrder(root, [&](const Node* node) {
                if (!hasValidSourceSpans(node)) {
                    result.addError("Invalid source spans", node);
                }
                
                // Check that child spans are within parent spans
                auto children = node->getChildNodes();
                for (const auto* child : children) {
                    if (child && (child->startPos < node->startPos || child->endPos > node->endPos)) {
                        result.addWarning("Child node spans extend beyond parent", child);
                    }
                }
            });
            
            return result;
        }
        
        ValidationResult validateTokenOrder(const Node* root) {
            ValidationResult result;
            if (!root) {
                result.addError("Root node is null");
                return result;
            }
            
            if (!hasConsistentTokenOrder(root)) {
                result.addError("Inconsistent token order", root);
            }
            
            return result;
        }
        
        ValidationResult validateCompleteness(const Node* root) {
            ValidationResult result;
            if (!root) {
                result.addError("Root node is null");
                return result;
            }
            
            Traversal::traversePreOrder(root, [&](const Node* node) {
                if (!isComplete(node)) {
                    result.addWarning("Incomplete node", node);
                }
            });
            
            return result;
        }
        
        bool hasValidSourceSpans(const Node* node) {
            if (!node) return false;
            return node->startPos <= node->endPos;
        }
        
        bool hasConsistentTokenOrder(const Node* node) {
            if (!node) return false;
            
            auto tokens = node->getAllTokens();
            for (size_t i = 1; i < tokens.size(); ++i) {
                if (tokens[i].start < tokens[i-1].start) {
                    return false;
                }
            }
            
            return true;
        }
        
        bool isComplete(const Node* node) {
            if (!node) return false;
            
            // Check if this is an error recovery node
            if (isErrorRecoveryNode(node->kind)) {
                return false;
            }
            
            // Check if node has required elements based on its kind
            // This would need language-specific knowledge
            return node->isValid;
        }
        
        bool hasCircularReferences(const Node* root) {
            if (!root) return false;
            
            std::set<const Node*> visited;
            std::set<const Node*> recursionStack;
            
            std::function<bool(const Node*)> checkCircular = [&](const Node* node) -> bool {
                if (!node) return false;
                
                if (recursionStack.count(node)) {
                    return true; // Circular reference found
                }
                
                if (visited.count(node)) {
                    return false; // Already processed
                }
                
                visited.insert(node);
                recursionStack.insert(node);
                
                auto children = node->getChildNodes();
                for (const auto* child : children) {
                    if (checkCircular(child)) {
                        return true;
                    }
                }
                
                recursionStack.erase(node);
                return false;
            };
            
            return checkCircular(root);
        }
        
        std::vector<const Node*> findErrorNodes(const Node* root) {
            return Traversal::findAll(root, [](const Node* node) {
                return node->kind == NodeKind::ERROR_NODE;
            });
        }
        
        std::vector<const Node*> findMissingNodes(const Node* root) {
            return Traversal::findAll(root, [](const Node* node) {
                return node->kind == NodeKind::MISSING_NODE;
            });
        }
        
        std::vector<const Node*> findIncompleteNodes(const Node* root) {
            return Traversal::findAll(root, [](const Node* node) {
                return node->kind == NodeKind::INCOMPLETE_NODE;
            });
        }
        
    } // namespace Validation

    // Analysis utilities implementation - temporarily disabled
    /*
    namespace Analysis {
        
        Analysis::TreeStatistics analyzeTree(const CST::Node* root) {
            Analysis::TreeStatistics stats;
            if (!root) return stats;
            
            CST::Traversal::traversePreOrder(root, [&](const CST::Node* node) {
                stats.totalNodes++;
                stats.nodeKindCounts[node->kind]++;
                
                if (CST::isErrorRecoveryNode(node->kind)) {
                    stats.errorNodes++;
                }
                
                // Count tokens in this node
                auto tokens = node->getTokens();
                stats.totalTokens += tokens.size();
                
                for (const auto& token : tokens) {
                    stats.tokenTypeCounts[token.type]++;
                    if (isSignificantToken(token)) {
                        stats.significantTokens++;
                    } else {
                        stats.triviaTokens++;
                    }
                }
            });
            
            // Calculate max depth
            stats.maxDepth = getMaxDepth(root);
            
            return stats;
        }
        
        std::vector<const CST::Node*> getAncestors(const CST::Node* root, const CST::Node* node) {
            if (!root || !node) return {};
            
            auto path = CST::Traversal::getPath(root, node);
            if (path.empty()) return {};
            
            // Remove the target node itself, keep only ancestors
            path.pop_back();
            return path;
        }
        
        std::vector<const CST::Node*> getDescendants(const CST::Node* node) {
            std::vector<const CST::Node*> descendants;
            if (!node) return descendants;
            
            CST::Traversal::traversePreOrder(node, [&](const CST::Node* n) {
                if (n != node) { // Exclude the node itself
                    descendants.push_back(n);
                }
            });
            
            return descendants;
        }
        
        size_t getDepth(const Node* root, const Node* node) {
            if (!root || !node) return 0;
            
            auto path = Traversal::getPath(root, node);
            return path.size() > 0 ? path.size() - 1 : 0;
        }
        
        size_t getMaxDepth(const Node* root) {
            if (!root) return 0;
            
            size_t maxDepth = 0;
            
            std::function<size_t(const Node*, size_t)> calculateDepth = 
                [&](const Node* node, size_t currentDepth) -> size_t {
                if (!node) return currentDepth;
                
                maxDepth = std::max(maxDepth, currentDepth);
                
                auto children = node->getChildNodes();
                size_t childMaxDepth = currentDepth;
                
                for (const auto* child : children) {
                    childMaxDepth = std::max(childMaxDepth, calculateDepth(child, currentDepth + 1));
                }
                
                return childMaxDepth;
            };
            
            calculateDepth(root, 0);
            return maxDepth;
        }
        
        std::vector<std::string> extractIdentifiers(const Node* root) {
            std::vector<std::string> identifiers;
            if (!root) return identifiers;
            
            Traversal::forEachToken(root, [&](const Token& token) {
                if (token.type == TokenType::IDENTIFIER) {
                    identifiers.push_back(token.lexeme);
                }
            });
            
            return identifiers;
        }
        
        std::vector<std::string> extractLiterals(const Node* root) {
            std::vector<std::string> literals;
            if (!root) return literals;
            
            Traversal::forEachToken(root, [&](const Token& token) {
                if (token.type == TokenType::STRING || 
                    token.type == TokenType::NUMBER ||
                    token.type == TokenType::TRUE ||
                    token.type == TokenType::FALSE) {
                    literals.push_back(token.lexeme);
                }
            });
            
            return literals;
        }
        
        std::vector<std::string> extractComments(const Node* root) {
            std::vector<std::string> comments;
            if (!root) return comments;
            
            Traversal::forEachToken(root, [&](const Token& token) {
                if (isCommentToken(token)) {
                    comments.push_back(token.lexeme);
                }
            });
            
            return comments;
        }
        
        size_t countNodes(const Node* root) {
            if (!root) return 0;
            
            size_t count = 0;
            Traversal::traversePreOrder(root, [&](const Node* node) {
                count++;
            });
            
            return count;
        }
        
        size_t countTokens(const Node* root) {
            if (!root) return 0;
            
            auto tokens = root->getAllTokens();
            return tokens.size();
        }
        
        size_t countSignificantNodes(const Node* root) {
            if (!root) return 0;
            
            size_t count = 0;
            Traversal::traversePreOrder(root, [&](const Node* node) {
                if (!isTriviaNode(node->kind)) {
                    count++;
                }
            });
            
            return count;
        }
        
        double calculateComplexity(const Node* root) {
            if (!root) return 0.0;
            
            // Simple complexity metric based on node count and depth
            size_t nodeCount = countNodes(root);
            size_t maxDepth = getMaxDepth(root);
            
            // Complexity = nodes * log(depth + 1)
            return static_cast<double>(nodeCount) * std::log(static_cast<double>(maxDepth + 1));
        }
        
    } // namespace Analysis
    */

    // Comparison utilities implementation - temporarily disabled
    /*
    namespace Comparison {
        
        void ComparisonResult::addDifference(const std::string& message, const Node* node) {
            differences.push_back(message);
            if (node) {
                differentNodes.push_back(node);
            }
            isEqual = false;
        }
        
        ComparisonResult compareCSTs(const Node* left, const Node* right, const ComparisonOptions& options) {
            ComparisonResult result;
            
            if (!left && !right) {
                return result; // Both null, equal
            }
            
            if (!left || !right) {
                result.addDifference("One tree is null while the other is not");
                return result;
            }
            
            // Compare node kinds
            if (left->kind != right->kind) {
                result.addDifference("Node kinds differ: " + nodeKindToString(left->kind) + 
                                   " vs " + nodeKindToString(right->kind), left);
                return result;
            }
            
            // Compare source positions if requested
            if (!options.ignoreSourcePositions) {
                if (left->startPos != right->startPos || left->endPos != right->endPos) {
                    result.addDifference("Source positions differ", left);
                }
            }
            
            // Compare error status if requested
            if (!options.ignoreErrorNodes) {
                if (left->isValid != right->isValid) {
                    result.addDifference("Validity status differs", left);
                }
                
                if (left->errorMessage != right->errorMessage) {
                    result.addDifference("Error messages differ", left);
                }
            }
            
            // Compare structure
            if (options.compareNodeStructure) {
                auto leftChildren = left->getChildNodes();
                auto rightChildren = right->getChildNodes();
                
                if (leftChildren.size() != rightChildren.size()) {
                    result.addDifference("Number of children differs", left);
                    return result;
                }
                
                // Recursively compare children
                for (size_t i = 0; i < leftChildren.size(); ++i) {
                    auto childResult = compareCSTs(leftChildren[i], rightChildren[i], options);
                    if (!childResult.isEqual) {
                        result.differences.insert(result.differences.end(), 
                                                childResult.differences.begin(), 
                                                childResult.differences.end());
                        result.differentNodes.insert(result.differentNodes.end(),
                                                   childResult.differentNodes.begin(),
                                                   childResult.differentNodes.end());
                        result.isEqual = false;
                    }
                }
            }
            
            // Compare tokens if requested
            if (options.compareTokenText) {
                auto leftTokens = left->getTokens();
                auto rightTokens = right->getTokens();
                
                if (options.ignoreTrivia) {
                    leftTokens = TokenUtils::excludeTrivia(leftTokens);
                    rightTokens = TokenUtils::excludeTrivia(rightTokens);
                }
                
                if (leftTokens.size() != rightTokens.size()) {
                    result.addDifference("Number of tokens differs", left);
                } else {
                    for (size_t i = 0; i < leftTokens.size(); ++i) {
                        if (leftTokens[i].lexeme != rightTokens[i].lexeme) {
                            result.addDifference("Token text differs: '" + leftTokens[i].lexeme + 
                                               "' vs '" + rightTokens[i].lexeme + "'", left);
                        }
                    }
                }
            }
            
            return result;
        }
        
        bool areEqual(const Node* left, const Node* right, const ComparisonOptions& options) {
            auto result = compareCSTs(left, right, options);
            return result.isEqual;
        }
        
        bool areStructurallyEqual(const Node* left, const Node* right) {
            ComparisonOptions options;
            options.ignoreTrivia = true;
            options.ignoreSourcePositions = true;
            options.compareTokenText = false;
            options.compareNodeStructure = true;
            
            return areEqual(left, right, options);
        }
        
        bool areTextuallyEqual(const Node* left, const Node* right) {
            if (!left || !right) return left == right;
            
            return left->getText() == right->getText();
        }
        
    } // namespace Comparison
    */

    // Transformation utilities implementation - temporarily disabled
    /*
    namespace Transform {
        
        std::unique_ptr<Node> transformTree(const Node* root, NodeTransformer transformer) {
            if (!root || !transformer) return nullptr;
            
            return transformer(root);
        }
        
        std::unique_ptr<Node> transformTokens(const Node* root, TokenTransformer transformer) {
            if (!root || !transformer) return nullptr;
            
            auto newNode = createNode(root->kind, root->startPos, root->endPos);
            newNode->isValid = root->isValid;
            newNode->errorMessage = root->errorMessage;
            newNode->description = root->description;
            
            for (const auto& element : root->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    auto transformedToken = transformer(token);
                    newNode->addToken(transformedToken);
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        auto transformedChild = transformTokens(childNode.get(), transformer);
                        newNode->addNode(std::move(transformedChild));
                    }
                }
            }
            
            return newNode;
        }
        
        std::unique_ptr<Node> removeTrivia(const Node* root) {
            if (!root) return nullptr;
            
            auto newNode = createNode(root->kind, root->startPos, root->endPos);
            newNode->isValid = root->isValid;
            newNode->errorMessage = root->errorMessage;
            newNode->description = root->description;
            
            for (const auto& element : root->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    if (!isTriviaToken(token)) {
                        newNode->addToken(token);
                    }
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode && !isTriviaNode(childNode->kind)) {
                        auto cleanChild = removeTrivia(childNode.get());
                        newNode->addNode(std::move(cleanChild));
                    }
                }
            }
            
            return newNode;
        }
        
        std::unique_ptr<Node> removeComments(const Node* root) {
            return transformTokens(root, [](const Token& token) -> Token {
                if (isCommentToken(token)) {
                    // Replace comment with whitespace
                    Token whitespace = token;
                    whitespace.type = TokenType::WHITESPACE;
                    whitespace.lexeme = " ";
                    return whitespace;
                }
                return token;
            });
        }
        
        std::unique_ptr<Node> removeErrorNodes(const Node* root) {
            return filterNodes(root, [](const Node* node) {
                return !isErrorRecoveryNode(node->kind);
            });
        }
        
        std::unique_ptr<Node> normalizeWhitespace(const Node* root) {
            return transformTokens(root, [](const Token& token) -> Token {
                if (isWhitespaceToken(token)) {
                    Token normalized = token;
                    normalized.lexeme = " "; // Normalize to single space
                    return normalized;
                }
                return token;
            });
        }
        
        std::unique_ptr<Node> filterNodes(const Node* root, NodePredicate predicate) {
            if (!root || !predicate) return nullptr;
            
            if (!predicate(root)) {
                return nullptr; // Filter out this node
            }
            
            auto newNode = createNode(root->kind, root->startPos, root->endPos);
            newNode->isValid = root->isValid;
            newNode->errorMessage = root->errorMessage;
            newNode->description = root->description;
            
            for (const auto& element : root->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    newNode->addToken(token);
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        auto filteredChild = filterNodes(childNode.get(), predicate);
                        if (filteredChild) {
                            newNode->addNode(std::move(filteredChild));
                        }
                    }
                }
            }
            
            return newNode;
        }
        
        std::unique_ptr<Node> filterTokens(const Node* root, TokenPredicate predicate) {
            if (!root || !predicate) return nullptr;
            
            auto newNode = createNode(root->kind, root->startPos, root->endPos);
            newNode->isValid = root->isValid;
            newNode->errorMessage = root->errorMessage;
            newNode->description = root->description;
            
            for (const auto& element : root->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    if (predicate(token)) {
                        newNode->addToken(token);
                    }
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        auto filteredChild = filterTokens(childNode.get(), predicate);
                        newNode->addNode(std::move(filteredChild));
                    }
                }
            }
            
            return newNode;
        }
        
    } // namespace Transform
    */

    // Query utilities implementation - temporarily disabled
    /*
    namespace Query {
        
        CSTQuery::CSTQuery(const std::string& queryString) : query_(queryString) {
            // Query parsing would be implemented here
        }
        
        std::vector<const Node*> CSTQuery::execute(const Node* root) const {
            // Simple implementation - would be expanded for full query language
            return {};
        }
        
        const Node* CSTQuery::executeFirst(const Node* root) const {
            auto results = execute(root);
            return results.empty() ? nullptr : results[0];
        }
        
        CSTQuery CSTQuery::byKind(NodeKind kind) {
            return CSTQuery("kind=" + nodeKindToString(kind));
        }
        
        CSTQuery CSTQuery::byText(const std::string& text) {
            return CSTQuery("text=" + text);
        }
        
        CSTQuery CSTQuery::byPosition(size_t position) {
            return CSTQuery("position=" + std::to_string(position));
        }
        
        CSTQuery CSTQuery::byRange(size_t start, size_t end) {
            return CSTQuery("range=" + std::to_string(start) + "-" + std::to_string(end));
        }
        
        std::vector<const Node*> selectByKind(const Node* root, NodeKind kind) {
            return Traversal::findAllByKind(root, kind);
        }
        
        std::vector<const Node*> selectByText(const Node* root, const std::string& text) {
            return Traversal::findAll(root, [&text](const Node* node) {
                return node->getText() == text;
            });
        }
        
        std::vector<const Node*> selectByPredicate(const Node* root, NodePredicate predicate) {
            return Traversal::findAll(root, predicate);
        }
        
    } // namespace Query
    */

} // namespace CST