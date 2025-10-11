#include "cst_printer.hh"
#include "cst_utils.hh"
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace CST {

    // Printer utilities implementation
    namespace Printer {
        
        std::string printCST(const Node* root, const PrintOptions& options) {
            if (!root) return "";
            
            switch (options.format) {
                case PrintFormat::TREE:
                    return printAsTree(root, options);
                case PrintFormat::JSON:
                    return printAsJSON(root, options);
                case PrintFormat::XML:
                    return printAsXML(root, options);
                case PrintFormat::COMPACT:
                    return printAsCompact(root, options);
                case PrintFormat::DEBUG:
                    return printAsDebug(root, options);
                default:
                    return printAsTree(root, options);
            }
        }
        
        void printCST(const Node* root, std::ostream& out, const PrintOptions& options) {
            out << printCST(root, options);
        }
        
        std::string printAsTree(const Node* root, const PrintOptions& options) {
            return TreeViz::visualizeTree(root, TreeViz::TreeVizOptions{
                .showTokens = options.includeTokens,
                .showTrivia = options.includeTrivia,
                .showPositions = options.includeSourcePositions,
                .showTypes = true,
                .colorNodes = options.colorOutput,
                .compactMode = false,
                .maxWidth = 120
            });
        }
        
        std::string printAsJSON(const Node* root, const PrintOptions& options) {
            return JSON::serializeCST(root, JSON::JSONOptions{
                .prettyPrint = true,
                .indentSize = 2,
                .includeTrivia = options.includeTrivia,
                .includeSourcePositions = options.includeSourcePositions,
                .includeMetadata = options.includeErrorInfo,
                .escapeStrings = true,
                .includeNodeIds = options.showNodeIds
            });
        }
        
        std::string printAsXML(const Node* root, const PrintOptions& options) {
            return XML::serializeCST(root, XML::XMLOptions{
                .prettyPrint = true,
                .indentSize = 2,
                .includeTrivia = options.includeTrivia,
                .includeSourcePositions = options.includeSourcePositions,
                .includeMetadata = options.includeErrorInfo,
                .useAttributes = true
            });
        }
        
        std::string printAsCompact(const Node* root, const PrintOptions& options) {
            if (!root) return "";
            
            std::ostringstream oss;
            oss << nodeKindToString(root->kind);
            
            if (options.includeSourcePositions) {
                oss << "@" << root->startPos << "-" << root->endPos;
            }
            
            if (!root->isValid && options.includeErrorInfo) {
                oss << "[ERROR]";
            }
            
            auto children = root->getChildNodes();
            if (!children.empty()) {
                oss << "(";
                for (size_t i = 0; i < children.size(); ++i) {
                    if (i > 0) oss << ",";
                    oss << printAsCompact(children[i], options);
                }
                oss << ")";
            }
            
            if (options.includeTokens) {
                auto tokens = root->getTokens();
                if (!tokens.empty()) {
                    oss << "[";
                    for (size_t i = 0; i < tokens.size(); ++i) {
                        if (i > 0) oss << ",";
                        oss << "'" << tokens[i].lexeme << "'";
                    }
                    oss << "]";
                }
            }
            
            return oss.str();
        }
        
        std::string printAsDebug(const Node* root, const PrintOptions& options) {
            return Debug::debugPrint(root, Debug::DebugOptions{
                .level = Debug::DebugLevel::DETAILED,
                .showMemoryAddresses = false,
                .showValidationInfo = options.includeErrorInfo,
                .showStatistics = true,
                .highlightErrors = true,
                .showTokenDetails = options.includeTokens,
                .showRelationships = false
            });
        }
        
        std::string printNodeInfo(const Node* node, const PrintOptions& options) {
            if (!node) return "null";
            
            std::ostringstream oss;
            oss << nodeKindToString(node->kind);
            
            if (options.includeSourcePositions) {
                oss << " [" << node->startPos << "-" << node->endPos << "]";
            }
            
            if (!node->isValid && options.includeErrorInfo) {
                oss << " ERROR: " << node->errorMessage;
            }
            
            if (!node->description.empty()) {
                oss << " (" << node->description << ")";
            }
            
            return oss.str();
        }
        
        std::string printTokenInfo(const Token& token, const PrintOptions& options) {
            std::ostringstream oss;
            oss << "'" << token.lexeme << "'";
            
            if (options.includeSourcePositions) {
                oss << " [" << token.start;
                if (token.end > 0) {
                    oss << "-" << token.end;
                }
                oss << "]";
            }
            
            return oss.str();
        }
        
        std::string printSourceSpan(const Node* node) {
            if (!node) return "";
            
            std::ostringstream oss;
            oss << "[" << node->startPos << "-" << node->endPos << "]";
            return oss.str();
        }
        
        std::string printErrorInfo(const Node* node) {
            if (!node || node->isValid) return "";
            
            std::ostringstream oss;
            oss << "ERROR: " << node->errorMessage;
            
            if (node->kind == NodeKind::ERROR_NODE) {
                const auto* errorNode = static_cast<const ErrorNode*>(node);
                if (!errorNode->skippedTokens.empty()) {
                    oss << " (skipped " << errorNode->skippedTokens.size() << " tokens)";
                }
            }
            
            return oss.str();
        }
        
    } // namespace Printer

    // Tree visualization implementation
    namespace TreeViz {
        
        std::string visualizeTree(const Node* root, const TreeVizOptions& options) {
            if (!root) return "";
            
            std::ostringstream oss;
            
            // Show root node with + prefix
            oss << "+ " << formatNodeLine(root, options) << "\n";
            
            // Process all elements in order (preserving source structure)
            for (size_t i = 0; i < root->elements.size(); ++i) {
                const auto& element = root->elements[i];
                bool isLast = (i == root->elements.size() - 1);
                
                if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        oss << visualizeSubtree(childNode.get(), "", isLast, options);
                    }
                } else if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    if (options.showTokens && (options.showTrivia || !isTriviaToken(token))) {
                        std::string connector = isLast ? options.chars.lastBranch : options.chars.branch;
                        oss << connector << options.chars.connector << " " << formatTokenLine(token, options) << "\n";
                    }
                }
            }
            
            return oss.str();
        }
        
        std::string visualizeSubtree(const Node* node, const std::string& prefix, bool isLast, const TreeVizOptions& options) {
            if (!node) return "";
            
            std::ostringstream oss;
            
            // Current node line with + prefix for structural nodes
            std::string connector = isLast ? options.chars.lastBranch : options.chars.branch;
            oss << prefix << connector << options.chars.connector << " + " << formatNodeLine(node, options) << "\n";
            
            // Prepare prefix for children
            std::string childPrefix = prefix + (isLast ? options.chars.space : options.chars.vertical) + " ";
            
            // Process all elements in order (preserving source structure)
            for (size_t i = 0; i < node->elements.size(); ++i) {
                const auto& element = node->elements[i];
                bool elementIsLast = (i == node->elements.size() - 1);
                
                if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        oss << visualizeSubtree(childNode.get(), childPrefix, elementIsLast, options);
                    }
                } else if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    if (options.showTokens && (options.showTrivia || !isTriviaToken(token))) {
                        std::string tokenConnector = elementIsLast ? options.chars.lastBranch : options.chars.branch;
                        oss << childPrefix << tokenConnector << options.chars.connector << " " 
                            << formatTokenLine(token, options) << "\n";
                    }
                }
            }
            
            return oss.str();
        }
        
        std::string formatNodeLine(const Node* node, const TreeVizOptions& options) {
            if (!node) return "null";
            
            std::ostringstream oss;
            
            // Check if this is a token-specific node and show token value
            if (node->kind == NodeKind::TOKEN_NODE) {
                const auto* tokenNode = static_cast<const TokenNode*>(node);
                oss << "Node: " << nodeKindToString(node->kind) << " | Token: " << tokenNode->token.lexeme;
            } else if (node->kind == NodeKind::WHITESPACE_NODE) {
                const auto* wsNode = static_cast<const WhitespaceNode*>(node);
                oss << "Node: " << nodeKindToString(node->kind) << " | Token: " << wsNode->whitespace.lexeme;
            } else if (node->kind == NodeKind::COMMENT_NODE) {
                const auto* commentNode = static_cast<const CommentNode*>(node);
                oss << "Node: " << nodeKindToString(node->kind) << " | Token: " << commentNode->comment.lexeme;
            } else if (node->kind == NodeKind::TRIVIA_NODE) {
                const auto* triviaNode = static_cast<const TriviaNode*>(node);
                oss << "Node: " << nodeKindToString(node->kind) << " | Token: " << triviaNode->trivia.lexeme;
            } else {
                // For structural nodes, show node type
                oss << "Node: " << nodeKindToString(node->kind);
            }
            
            if (options.showPositions) {
                oss << " [" << node->startPos << "-" << node->endPos << "]";
            }
            
            if (!node->isValid) {
                oss << " ERROR: " << node->errorMessage;
            }
            
            if (!node->description.empty()) {
                oss << " (" << truncateText(node->description, options.maxWidth / 2) << ")";
            }
            
            return oss.str();
        }
        
        std::string formatTokenLine(const Token& token, const TreeVizOptions& options) {
            std::ostringstream oss;
            oss << "Token: " << truncateText(token.lexeme, 20);
            
            if (options.showPositions) {
                oss << " [" << token.start;
                if (token.end > 0) {
                    oss << "-" << token.end;
                }
                oss << "]";
            }
            
            return oss.str();
        }
        
        std::string truncateText(const std::string& text, int maxLength) {
            if (text.length() <= static_cast<size_t>(maxLength)) {
                return text;
            }
            
            return text.substr(0, maxLength - 3) + "...";
        }
        
    } // namespace TreeViz

    // JSON serialization implementation
    namespace JSON {
        
        std::string serializeCST(const Node* root, const JSONOptions& options) {
            if (!root) return "null";
            
            std::ostringstream oss;
            oss << "{\n";
            oss << getIndent(1, options.indentSize) << "\"type\": \"cst\",\n";
            oss << getIndent(1, options.indentSize) << "\"root\": ";
            oss << serializeNode(root, options, 1);
            oss << "\n}";
            
            return oss.str();
        }
        
        std::string serializeNode(const Node* node, const JSONOptions& options, int depth) {
            if (!node) return "null";
            
            std::ostringstream oss;
            std::string indent = getIndent(depth, options.indentSize);
            std::string nextIndent = getIndent(depth + 1, options.indentSize);
            
            oss << "{\n";
            oss << nextIndent << "\"kind\": " << formatJSONValue(nodeKindToString(node->kind)) << ",\n";
            
            if (options.includeSourcePositions) {
                oss << nextIndent << "\"startPos\": " << node->startPos << ",\n";
                oss << nextIndent << "\"endPos\": " << node->endPos << ",\n";
            }
            
            if (options.includeMetadata) {
                oss << nextIndent << "\"isValid\": " << (node->isValid ? "true" : "false") << ",\n";
                
                if (!node->errorMessage.empty()) {
                    oss << nextIndent << "\"errorMessage\": " << formatJSONValue(node->errorMessage) << ",\n";
                }
                
                if (!node->description.empty()) {
                    oss << nextIndent << "\"description\": " << formatJSONValue(node->description) << ",\n";
                }
            }
            
            // Serialize elements (children and tokens)
            oss << nextIndent << "\"elements\": [\n";
            
            bool first = true;
            for (const auto& element : node->elements) {
                if (!first) oss << ",\n";
                first = false;
                
                oss << getIndent(depth + 2, options.indentSize);
                
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    if (!options.includeTrivia && isTriviaToken(token)) {
                        continue;
                    }
                    oss << serializeToken(token, options);
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        oss << serializeNode(childNode.get(), options, depth + 2);
                    } else {
                        oss << "null";
                    }
                }
            }
            
            oss << "\n" << nextIndent << "]\n";
            oss << indent << "}";
            
            return oss.str();
        }
        
        std::string serializeToken(const Token& token, const JSONOptions& options) {
            std::ostringstream oss;
            oss << "{\n";
            oss << "  \"type\": \"token\",\n";
            oss << "  \"tokenType\": " << formatJSONValue(std::to_string(static_cast<int>(token.type))) << ",\n";
            oss << "  \"lexeme\": " << formatJSONValue(token.lexeme) << ",\n";
            oss << "  \"line\": " << token.line;
            
            if (options.includeSourcePositions) {
                oss << ",\n  \"start\": " << token.start;
                if (token.end > 0) {
                    oss << ",\n  \"end\": " << token.end;
                }
            }
            
            oss << "\n}";
            return oss.str();
        }
        
        std::string escapeJSONString(const std::string& str) {
            std::ostringstream oss;
            for (char c : str) {
                switch (c) {
                    case '"': oss << "\\\""; break;
                    case '\\': oss << "\\\\"; break;
                    case '\b': oss << "\\b"; break;
                    case '\f': oss << "\\f"; break;
                    case '\n': oss << "\\n"; break;
                    case '\r': oss << "\\r"; break;
                    case '\t': oss << "\\t"; break;
                    default:
                        if (c < 0x20) {
                            oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
                        } else {
                            oss << c;
                        }
                        break;
                }
            }
            return oss.str();
        }
        
        std::string formatJSONValue(const std::string& value, bool isString) {
            if (isString) {
                return "\"" + escapeJSONString(value) + "\"";
            }
            return value;
        }
        
        std::string getIndent(int depth, int indentSize) {
            return std::string(depth * indentSize, ' ');
        }
        
        std::string serializeNodeMetadata(const Node* node, const JSONOptions& options) {
            if (!node) return "{}";
            
            std::ostringstream oss;
            oss << "{\n";
            oss << "  \"isValid\": " << (node->isValid ? "true" : "false");
            
            if (!node->errorMessage.empty()) {
                oss << ",\n  \"errorMessage\": " << formatJSONValue(node->errorMessage);
            }
            
            if (!node->description.empty()) {
                oss << ",\n  \"description\": " << formatJSONValue(node->description);
            }
            
            oss << "\n}";
            return oss.str();
        }
        
        std::string serializeTokenMetadata(const Token& token, const JSONOptions& options) {
            std::ostringstream oss;
            oss << "{\n";
            oss << "  \"line\": " << token.line;
            
            if (options.includeSourcePositions) {
                oss << ",\n  \"start\": " << token.start;
                if (token.end > 0) {
                    oss << ",\n  \"end\": " << token.end;
                }
            }
            
            oss << "\n}";
            return oss.str();
        }
        
        std::string serializeSourcePosition(size_t start, size_t end) {
            std::ostringstream oss;
            oss << "{\"start\": " << start << ", \"end\": " << end << "}";
            return oss.str();
        }
        
        std::string serializeErrorInfo(const Node* node) {
            if (!node || node->isValid) return "null";
            
            std::ostringstream oss;
            oss << "{\n";
            oss << "  \"hasError\": true,\n";
            oss << "  \"errorMessage\": " << formatJSONValue(node->errorMessage) << ",\n";
            oss << "  \"nodeKind\": " << formatJSONValue(nodeKindToString(node->kind));
            oss << "\n}";
            
            return oss.str();
        }
        
    } // namespace JSON

    // XML serialization implementation
    namespace XML {
        
        std::string serializeCST(const Node* root, const XMLOptions& options) {
            if (!root) return "<null/>";
            
            // Simple XML implementation for now
            std::ostringstream xml;
            xml << "<node kind=\"" << nodeKindToString(root->kind) << "\">";
            
            // Add tokens
            for (const auto& token : root->getTokens()) {
                xml << "<token type=\"" << static_cast<int>(token.type) << "\">";
                xml << token.lexeme;
                xml << "</token>";
            }
            
            // Add children
            for (const auto& child : root->getChildNodes()) {
                xml << serializeCST(child, options);
            }
            
            xml << "</node>";
            return xml.str();
        }
        
        std::string getXMLIndent(int depth, int indentSize) {
            return std::string(depth * indentSize, ' ');
        }
        
    } // namespace XML

    // Debug printing implementation
    namespace Debug {
        
        std::string debugPrint(const Node* root, const DebugOptions& options) {
            if (!root) return "null";
            
            std::ostringstream oss;
            
            if (options.showStatistics) {
                oss << "=== CST Debug Information ===\n";
                oss << printStatistics(root) << "\n";
            }
            
            if (options.showValidationInfo) {
                oss << "=== Validation Report ===\n";
                oss << printValidationReport(root) << "\n";
            }
            
            oss << "=== CST Structure ===\n";
            oss << debugPrintNode(root, options, 0);
            
            if (options.highlightErrors) {
                auto errorNodes = Validation::findErrorNodes(root);
                if (!errorNodes.empty()) {
                    oss << "\n=== Error Nodes ===\n";
                    for (const auto* errorNode : errorNodes) {
                        oss << "- " << nodeKindToString(errorNode->kind) 
                            << ": " << errorNode->errorMessage << "\n";
                    }
                }
            }
            
            return oss.str();
        }
        
        std::string debugPrintNode(const Node* node, const DebugOptions& options, int depth) {
            if (!node) return std::string(depth * 2, ' ') + "null\n";
            
            std::ostringstream oss;
            std::string indent(depth * 2, ' ');
            
            oss << indent << "+ " << nodeKindToString(node->kind);
            
            if (options.showMemoryAddresses) {
                oss << " @" << std::hex << reinterpret_cast<uintptr_t>(node) << std::dec;
            }
            
            oss << " [" << node->startPos << "-" << node->endPos << "]";
            
            if (!node->isValid) {
                oss << " ERROR: " << node->errorMessage;
            }
            
            if (!node->description.empty()) {
                oss << " (" << node->description << ")";
            }
            
            oss << "\n";
            
            // Print elements
            for (const auto& element : node->elements) {
                if (std::holds_alternative<Token>(element)) {
                    const auto& token = std::get<Token>(element);
                    if (options.showTokenDetails) {
                        oss << indent << "  | " << debugPrintToken(token, options) << "\n";
                    }
                } else if (std::holds_alternative<std::unique_ptr<Node>>(element)) {
                    const auto& childNode = std::get<std::unique_ptr<Node>>(element);
                    if (childNode) {
                        oss << debugPrintNode(childNode.get(), options, depth + 1);
                    }
                }
            }
            
            return oss.str();
        }
        
        std::string debugPrintToken(const Token& token, const DebugOptions& options) {
            std::ostringstream oss;
            oss << "Token[" << static_cast<int>(token.type) << "]: '" << token.lexeme << "'";
            oss << " @" << token.start;
            if (token.end > 0) {
                oss << "-" << token.end;
            }
            oss << " line:" << token.line;
            return oss.str();
        }
        
        std::string printDiagnostics(const Node* root) {
            if (!root) return "No root node";
            
            auto validationResult = Validation::validateCST(root);
            std::ostringstream oss;
            
            oss << "Validation Status: " << (validationResult.isValid ? "VALID" : "INVALID") << "\n";
            oss << "Errors: " << validationResult.errors.size() << "\n";
            oss << "Warnings: " << validationResult.warnings.size() << "\n";
            
            if (!validationResult.errors.empty()) {
                oss << "\nErrors:\n";
                for (const auto& error : validationResult.errors) {
                    oss << "  - " << error << "\n";
                }
            }
            
            if (!validationResult.warnings.empty()) {
                oss << "\nWarnings:\n";
                for (const auto& warning : validationResult.warnings) {
                    oss << "  - " << warning << "\n";
                }
            }
            
            return oss.str();
        }
        
        std::string printValidationReport(const Node* root) {
            return printDiagnostics(root);
        }
        
        std::string printStatistics(const Node* root) {
            if (!root) return "No statistics available";
            
            // This would use the Analysis utilities once implemented
            std::ostringstream oss;
            
            size_t nodeCount = 0;
            size_t tokenCount = 0;
            size_t errorCount = 0;
            
            Traversal::traversePreOrder(root, [&](const Node* node) {
                nodeCount++;
                if (!node->isValid) errorCount++;
            });
            
            auto allTokens = root->getAllTokens();
            tokenCount = allTokens.size();
            
            oss << "Total Nodes: " << nodeCount << "\n";
            oss << "Total Tokens: " << tokenCount << "\n";
            oss << "Error Nodes: " << errorCount << "\n";
            
            return oss.str();
        }
        
        std::string printErrorSummary(const Node* root) {
            auto errorNodes = Validation::findErrorNodes(root);
            auto missingNodes = Validation::findMissingNodes(root);
            auto incompleteNodes = Validation::findIncompleteNodes(root);
            
            std::ostringstream oss;
            oss << "Error Summary:\n";
            oss << "  Error Nodes: " << errorNodes.size() << "\n";
            oss << "  Missing Nodes: " << missingNodes.size() << "\n";
            oss << "  Incomplete Nodes: " << incompleteNodes.size() << "\n";
            
            return oss.str();
        }
        
        std::string printMemoryUsage(const Node* root) {
            // Placeholder for memory usage analysis
            return "Memory usage analysis not implemented";
        }
        
        std::string printPerformanceMetrics(const Node* root) {
            // Placeholder for performance metrics
            return "Performance metrics not implemented";
        }
        
    } // namespace Debug

    // Stream operators implementation
    std::ostream& operator<<(std::ostream& os, const Node& node) {
        os << printCST(&node);
        return os;
    }
    
    std::ostream& operator<<(std::ostream& os, const Node* node) {
        if (node) {
            os << printCST(node);
        } else {
            os << "null";
        }
        return os;
    }

} // namespace CST