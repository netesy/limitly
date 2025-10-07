#ifndef CST_UTILS_SIMPLE_H
#define CST_UTILS_SIMPLE_H

#include "cst.hh"
#include <functional>
#include <vector>
#include <string>
#include <ostream>

namespace CST {

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
        
    } // namespace Utils

    // Simple printing utilities
    namespace Printer {
        
        // Print CST as indented tree
        std::string printCST(const Node* root, bool includeTrivia = true);
        void printNode(const Node* node, std::ostream& out, int indent, bool includeTrivia);
        
        // Serialize CST to JSON
        std::string serializeToJSON(const Node* root);
        
    } // namespace Printer

    // Convenience functions
    inline std::string printCST(const Node* root) {
        return Printer::printCST(root);
    }
    
    inline std::string printCSTAsJSON(const Node* root) {
        return Printer::serializeToJSON(root);
    }
    
    inline std::string debugCST(const Node* root) {
        return Printer::printCST(root, true);
    }

} // namespace CST

#endif // CST_UTILS_SIMPLE_H