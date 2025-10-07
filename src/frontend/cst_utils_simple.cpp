#include "cst.hh"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>

namespace CST {

    // Simple utility functions for CST manipulation
    namespace Utils {
        
        // Text reconstruction
        std::string getText(const Node* node) {
            if (!node) return "";
            return node->getText();
        }
        
        std::string getTextWithoutTrivia(const Node* node) {
            if (!node) return "";
            return node->getTextWithoutTrivia();
        }
        
        // Token extraction
        std::vector<Token> getAllTokens(const Node* node) {
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
        
        // Tree traversal
        void forEachChild(const Node* node, std::function<void(const Node*)> visitor) {
            if (!node || !visitor) return;
            
            auto children = node->getChildNodes();
            for (const auto* child : children) {
                if (child) {
                    visitor(child);
                }
            }
        }
        
        void forEachDescendant(const Node* node, std::function<void(const Node*)> visitor) {
            if (!node || !visitor) return;
            
            visitor(node);
            
            auto children = node->getChildNodes();
            for (const auto* child : children) {
                if (child) {
                    forEachDescendant(child, visitor);
                }
            }
        }
        
        // Find operations
        const Node* findByKind(const Node* root, NodeKind kind) {
            if (!root) return nullptr;
            
            if (root->kind == kind) {
                return root;
            }
            
            auto children = root->getChildNodes();
            for (const auto* child : children) {
                if (child) {
                    const Node* result = findByKind(child, kind);
                    if (result) {
                        return result;
                    }
                }
            }
            
            return nullptr;
        }
        
        std::vector<const Node*> findAllByKind(const Node* root, NodeKind kind) {
            std::vector<const Node*> results;
            if (!root) return results;
            
            forEachDescendant(root, [&](const Node* node) {
                if (node->kind == kind) {
                    results.push_back(node);
                }
            });
            
            return results;
        }
        
        // Source reconstruction
        std::string reconstructSource(const Node* node) {
            if (!node) return "";
            
            std::string result;
            
            for (const auto& element : node->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    result += token.lexeme;
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        result += reconstructSource(childNode.get());
                    }
                }
            }
            
            return result;
        }
        
        // Validation
        bool validateCST(const Node* root) {
            if (!root) return false;
            
            bool isValid = true;
            
            forEachDescendant(root, [&](const Node* node) {
                if (!node->isValid) {
                    isValid = false;
                }
            });
            
            return isValid;
        }
        
        // Statistics
        size_t countNodes(const Node* root) {
            if (!root) return 0;
            
            size_t count = 0;
            forEachDescendant(root, [&](const Node* node) {
                count++;
            });
            
            return count;
        }
        
        size_t countTokens(const Node* root) {
            if (!root) return 0;
            
            auto tokens = root->getAllTokens();
            return tokens.size();
        }
        
        std::vector<const Node*> findErrorNodes(const Node* root) {
            return findAllByKind(root, NodeKind::ERROR_NODE);
        }
        
    } // namespace Utils

    // Simple printing utilities
    namespace Printer {
        
        // Forward declaration
        void printNode(const Node* node, std::ostream& out, int indent, bool includeTrivia);
        
        std::string printCST(const Node* root, bool includeTrivia) {
            if (!root) return "null";
            
            std::ostringstream oss;
            printNode(root, oss, 0, includeTrivia);
            return oss.str();
        }
        
        void printNode(const Node* node, std::ostream& out, int indent, bool includeTrivia) {
            if (!node) {
                out << std::string(indent * 2, ' ') << "null\n";
                return;
            }
            
            std::string indentStr(indent * 2, ' ');
            out << indentStr << "+ " << nodeKindToString(node->kind);
            
            if (!node->isValid) {
                out << " [ERROR: " << node->errorMessage << "]";
            }
            
            if (!node->description.empty()) {
                out << " (" << node->description << ")";
            }
            
            out << "\n";
            
            // Print elements
            for (const auto& element : node->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    if (includeTrivia || isSignificantToken(token)) {
                        out << indentStr << "  | Token: '" << token.lexeme << "'\n";
                    }
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        printNode(childNode.get(), out, indent + 1, includeTrivia);
                    }
                }
            }
        }
        
        std::string serializeToJSON(const Node* root) {
            if (!root) return "null";
            
            std::ostringstream oss;
            oss << "{\n";
            oss << "  \"kind\": \"" << nodeKindToString(root->kind) << "\",\n";
            oss << "  \"startPos\": " << root->startPos << ",\n";
            oss << "  \"endPos\": " << root->endPos << ",\n";
            oss << "  \"isValid\": " << (root->isValid ? "true" : "false");
            
            if (!root->errorMessage.empty()) {
                oss << ",\n  \"errorMessage\": \"" << root->errorMessage << "\"";
            }
            
            if (!root->description.empty()) {
                oss << ",\n  \"description\": \"" << root->description << "\"";
            }
            
            auto children = root->getChildNodes();
            if (!children.empty()) {
                oss << ",\n  \"children\": [\n";
                for (size_t i = 0; i < children.size(); ++i) {
                    if (i > 0) oss << ",\n";
                    oss << "    " << serializeToJSON(children[i]);
                }
                oss << "\n  ]";
            }
            
            auto tokens = root->getTokens();
            if (!tokens.empty()) {
                oss << ",\n  \"tokens\": [\n";
                for (size_t i = 0; i < tokens.size(); ++i) {
                    if (i > 0) oss << ",\n";
                    oss << "    {\"type\": " << static_cast<int>(tokens[i].type) 
                        << ", \"lexeme\": \"" << tokens[i].lexeme << "\"}";
                }
                oss << "\n  ]";
            }
            
            oss << "\n}";
            return oss.str();
        }
        
    } // namespace Printer

} // namespace CST