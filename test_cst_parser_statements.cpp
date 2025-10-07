#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }
    
    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

void printCST(const CST::Node* node, int indent = 0) {
    if (!node) return;
    
    std::string indentStr(indent * 2, ' ');
    std::cout << indentStr << node->getKindName();
    
    if (!node->tokens.empty()) {
        std::cout << " [";
        for (size_t i = 0; i < node->tokens.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << "'" << node->tokens[i].lexeme << "'";
        }
        std::cout << "]";
    }
    
    if (!node->isValid) {
        std::cout << " (ERROR: " << node->errorMessage << ")";
    }
    
    std::cout << std::endl;
    
    for (const auto& child : node->children) {
        printCST(child.get(), indent + 1);
    }
}

int main(int argc, char* argv[]) {
    std::string filename = "test_cst_statement_parsing.lm";
    if (argc > 1) {
        filename = argv[1];
    }
    
    std::string source = readFile(filename);
    if (source.empty()) {
        return 1;
    }
    
    std::cout << "=== Testing CST Statement Parsing with Error Recovery ===" << std::endl;
    std::cout << "Source file: " << filename << std::endl;
    std::cout << std::endl;
    
    try {
        // Create scanner with CST configuration
        Scanner scanner(source, filename);
        CSTConfig config;
        config.preserveWhitespace = true;
        config.preserveComments = true;
        config.emitErrorTokens = true;
        
        // Create CST parser
        CST::CSTParser parser(scanner, config);
        
        // Configure error recovery
        CST::RecoveryConfig recoveryConfig;
        recoveryConfig.continueOnError = true;
        recoveryConfig.insertMissingTokens = true;
        recoveryConfig.createPartialNodes = true;
        recoveryConfig.maxErrors = 50;
        parser.setRecoveryConfig(recoveryConfig);
        
        // Parse to CST
        auto cst = parser.parse();
        
        std::cout << "=== Parse Results ===" << std::endl;
        std::cout << "Errors found: " << parser.getErrorCount() << std::endl;
        
        if (parser.hasErrors()) {
            std::cout << std::endl << "=== Parse Errors ===" << std::endl;
            for (const auto& error : parser.getErrors()) {
                std::cout << "Line " << error.line << ", Column " << error.column 
                         << ": " << error.message << std::endl;
                if (!error.context.empty()) {
                    std::cout << "  Context: " << error.context << std::endl;
                }
                if (!error.suggestions.empty()) {
                    std::cout << "  Suggestions:" << std::endl;
                    for (const auto& suggestion : error.suggestions) {
                        std::cout << "    - " << suggestion << std::endl;
                    }
                }
                std::cout << std::endl;
            }
        }
        
        std::cout << "=== CST Structure ===" << std::endl;
        if (cst) {
            printCST(cst.get());
        } else {
            std::cout << "Failed to create CST" << std::endl;
        }
        
        std::cout << std::endl << "=== Summary ===" << std::endl;
        std::cout << "Total tokens processed: " << parser.getTotalTokens() << std::endl;
        std::cout << "Tokens consumed: " << parser.getTokensConsumed() << std::endl;
        std::cout << "Parse completed: " << (cst ? "Yes" : "No") << std::endl;
        std::cout << "Error recovery successful: " << (parser.hasErrors() && cst ? "Yes" : "N/A") << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Exception during parsing: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}