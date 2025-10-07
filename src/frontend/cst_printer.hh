#ifndef CST_PRINTER_H
#define CST_PRINTER_H

#include "cst.hh"
#include <string>
#include <ostream>
#include <memory>

namespace CST {

    // Forward declarations
    class Node;

    // Printing utilities
    namespace Printer {
        
        // Print format options
        enum class PrintFormat {
            TREE,           // Indented tree format
            JSON,           // JSON format
            XML,            // XML format
            COMPACT,        // Compact single-line format
            DEBUG           // Debug format with extra information
        };
        
        // Print options for customizing output
        struct PrintOptions {
            PrintFormat format = PrintFormat::TREE;
            bool includeTrivia = true;
            bool includeTokens = true;
            bool includeSourcePositions = false;
            bool includeErrorInfo = true;
            bool colorOutput = false;
            std::string indentString = "  ";
            int maxDepth = -1;  // -1 for unlimited
            bool compactArrays = false;
            bool showNodeIds = false;
        };
        
        // Main printing functions
        std::string printCST(const Node* root, const PrintOptions& options = {});
        void printCST(const Node* root, std::ostream& out, const PrintOptions& options = {});
        
        // Format-specific printing functions
        std::string printAsTree(const Node* root, const PrintOptions& options = {});
        std::string printAsJSON(const Node* root, const PrintOptions& options = {});
        std::string printAsXML(const Node* root, const PrintOptions& options = {});
        std::string printAsCompact(const Node* root, const PrintOptions& options = {});
        std::string printAsDebug(const Node* root, const PrintOptions& options = {});
        
        // Specialized printing functions
        std::string printNodeInfo(const Node* node, const PrintOptions& options = {});
        std::string printTokenInfo(const Token& token, const PrintOptions& options = {});
        std::string printSourceSpan(const Node* node);
        std::string printErrorInfo(const Node* node);
        
    } // namespace Printer

    // Tree visualization utilities
    namespace TreeViz {
        
        // ASCII tree drawing characters
        struct TreeChars {
            std::string vertical = "│";
            std::string horizontal = "─";
            std::string branch = "├";
            std::string lastBranch = "└";
            std::string connector = "─";
            std::string space = " ";
        };
        
        // Tree visualization options
        struct TreeVizOptions {
            TreeChars chars;
            bool showTokens = true;
            bool showTrivia = false;
            bool showPositions = false;
            bool showTypes = true;
            bool colorNodes = false;
            bool compactMode = false;
            int maxWidth = 80;
        };
        
        // Tree visualization functions
        std::string visualizeTree(const Node* root, const TreeVizOptions& options = {});
        std::string visualizeSubtree(const Node* node, const std::string& prefix, bool isLast, const TreeVizOptions& options);
        
        // Helper functions for tree drawing
        std::string formatNodeLine(const Node* node, const TreeVizOptions& options);
        std::string formatTokenLine(const Token& token, const TreeVizOptions& options);
        std::string truncateText(const std::string& text, int maxLength);
        
    } // namespace TreeViz

    // JSON serialization utilities
    namespace JSON {
        
        // JSON serialization options
        struct JSONOptions {
            bool prettyPrint = true;
            int indentSize = 2;
            bool includeTrivia = true;
            bool includeSourcePositions = true;
            bool includeMetadata = true;
            bool escapeStrings = true;
            bool includeNodeIds = false;
            bool includeParentRefs = false;
        };
        
        // JSON serialization functions
        std::string serializeCST(const Node* root, const JSONOptions& options = {});
        std::string serializeNode(const Node* node, const JSONOptions& options, int depth = 0);
        std::string serializeToken(const Token& token, const JSONOptions& options);
        
        // JSON utility functions
        std::string escapeJSONString(const std::string& str);
        std::string formatJSONValue(const std::string& value, bool isString = true);
        std::string getIndent(int depth, int indentSize);
        
        // Specialized JSON serializers
        std::string serializeNodeMetadata(const Node* node, const JSONOptions& options);
        std::string serializeTokenMetadata(const Token& token, const JSONOptions& options);
        std::string serializeSourcePosition(size_t start, size_t end);
        std::string serializeErrorInfo(const Node* node);
        
    } // namespace JSON

    // XML serialization utilities
    namespace XML {
        
        // XML serialization options
        struct XMLOptions {
            bool prettyPrint = true;
            int indentSize = 2;
            bool includeTrivia = true;
            bool includeSourcePositions = true;
            bool includeMetadata = true;
            bool useAttributes = true;  // Use attributes vs child elements
            std::string rootElementName = "cst";
            bool includeXMLDeclaration = true;
        };
        
        // XML serialization functions
        std::string serializeCST(const Node* root, const XMLOptions& options = {});
        std::string serializeNode(const Node* node, const XMLOptions& options, int depth = 0);
        std::string serializeToken(const Token& token, const XMLOptions& options, int depth = 0);
        
        // XML utility functions
        std::string escapeXMLText(const std::string& text);
        std::string escapeXMLAttribute(const std::string& attr);
        std::string formatXMLElement(const std::string& name, const std::string& content, 
                                   const std::vector<std::pair<std::string, std::string>>& attributes = {});
        std::string getXMLIndent(int depth, int indentSize);
        
    } // namespace XML

    // Debug printing utilities
    namespace Debug {
        
        // Debug information levels
        enum class DebugLevel {
            BASIC,      // Basic node and token info
            DETAILED,   // Include source positions and metadata
            VERBOSE,    // Include all available information
            DIAGNOSTIC  // Include validation and analysis info
        };
        
        // Debug printing options
        struct DebugOptions {
            DebugLevel level = DebugLevel::DETAILED;
            bool showMemoryAddresses = false;
            bool showValidationInfo = true;
            bool showStatistics = true;
            bool highlightErrors = true;
            bool showTokenDetails = true;
            bool showRelationships = false;
        };
        
        // Debug printing functions
        std::string debugPrint(const Node* root, const DebugOptions& options = {});
        std::string debugPrintNode(const Node* node, const DebugOptions& options, int depth = 0);
        std::string debugPrintToken(const Token& token, const DebugOptions& options);
        
        // Diagnostic functions
        std::string printDiagnostics(const Node* root);
        std::string printValidationReport(const Node* root);
        std::string printStatistics(const Node* root);
        std::string printErrorSummary(const Node* root);
        
        // Memory and performance diagnostics
        std::string printMemoryUsage(const Node* root);
        std::string printPerformanceMetrics(const Node* root);
        
    } // namespace Debug

    // Diff and comparison printing
    namespace Diff {
        
        // Diff display options
        struct DiffOptions {
            bool showContext = true;
            int contextLines = 3;
            bool colorOutput = false;
            bool showLineNumbers = true;
            bool unifiedFormat = true;
            bool ignoreWhitespace = false;
        };
        
        // Diff printing functions
        std::string printDiff(const Node* left, const Node* right, const DiffOptions& options = {});
        std::string printStructuralDiff(const Node* left, const Node* right, const DiffOptions& options = {});
        std::string printTextualDiff(const Node* left, const Node* right, const DiffOptions& options = {});
        
        // Diff utility functions
        std::vector<std::string> generateDiffLines(const std::string& leftText, const std::string& rightText);
        std::string formatDiffLine(const std::string& line, char prefix, int lineNumber = -1);
        
    } // namespace Diff

    // Export utilities
    namespace Export {
        
        // Export formats
        enum class ExportFormat {
            JSON,
            XML,
            YAML,
            DOT,        // Graphviz DOT format
            HTML,       // HTML with syntax highlighting
            MARKDOWN    // Markdown format
        };
        
        // Export options
        struct ExportOptions {
            ExportFormat format = ExportFormat::JSON;
            std::string outputPath;
            bool includeTrivia = true;
            bool includeMetadata = true;
            bool prettyPrint = true;
            std::string title = "CST Export";
            std::string description;
        };
        
        // Export functions
        bool exportCST(const Node* root, const ExportOptions& options);
        std::string exportToString(const Node* root, const ExportOptions& options);
        
        // Format-specific export functions
        std::string exportToJSON(const Node* root, const ExportOptions& options);
        std::string exportToXML(const Node* root, const ExportOptions& options);
        std::string exportToYAML(const Node* root, const ExportOptions& options);
        std::string exportToDOT(const Node* root, const ExportOptions& options);
        std::string exportToHTML(const Node* root, const ExportOptions& options);
        std::string exportToMarkdown(const Node* root, const ExportOptions& options);
        
    } // namespace Export

    // Convenience functions for common use cases
    
    // Quick print functions
    inline std::string printCST(const Node* root) {
        return Printer::printCST(root);
    }
    
    inline std::string printCSTAsJSON(const Node* root) {
        return JSON::serializeCST(root);
    }
    
    inline std::string printCSTAsTree(const Node* root) {
        return TreeViz::visualizeTree(root);
    }
    
    inline std::string debugCST(const Node* root) {
        return Debug::debugPrint(root);
    }
    
    // Stream operators for easy printing
    std::ostream& operator<<(std::ostream& os, const Node& node);
    std::ostream& operator<<(std::ostream& os, const Node* node);

} // namespace CST

#endif // CST_PRINTER_H