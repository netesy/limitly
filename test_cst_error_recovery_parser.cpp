#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    try {
        std::cout << "Testing CST Error Recovery with detailed test file..." << std::endl;
        
        // Read the test file
        std::string source = readFile("test_cst_error_recovery_detailed.lm");
        
        // Create scanner and parser
        Scanner scanner(source);
        CSTConfig config;
        config.preserveComments = true;
        config.preserveWhitespace = true;
        config.emitErrorTokens = true;
        
        CST::CSTParser parser(scanner, config);
        
        // Configure error recovery
        CST::RecoveryConfig recoveryConfig;
        recoveryConfig.maxErrors = 50;
        recoveryConfig.continueOnError = true;
        recoveryConfig.insertMissingTokens = true;
        recoveryConfig.createPartialNodes = true;
        recoveryConfig.skipInvalidTokens = true;
        parser.setRecoveryConfig(recoveryConfig);
        
        // Parse with error recovery
        std::cout << "Parsing source with error recovery..." << std::endl;
        auto cst = parser.parse();
        
        // Check results
        if (cst) {
            std::cout << "✓ CST created successfully despite syntax errors" << std::endl;
            std::cout << "CST Node Kind: " << cst->getKindName() << std::endl;
            std::cout << "CST has " << cst->children.size() << " top-level children" << std::endl;
        } else {
            std::cout << "✗ Failed to create CST" << std::endl;
            return 1;
        }
        
        // Report errors
        auto errors = parser.getErrors();
        std::cout << "\nError Recovery Results:" << std::endl;
        std::cout << "Total errors found: " << errors.size() << std::endl;
        std::cout << "Parser consumed " << parser.getTokensConsumed() << " of " << parser.getTotalTokens() << " tokens" << std::endl;
        
        // Categorize errors
        int errorCount = 0, warningCount = 0, infoCount = 0;
        for (const auto& error : errors) {
            switch (error.severity) {
                case CST::ParseError::Severity::ERROR: errorCount++; break;
                case CST::ParseError::Severity::WARNING: warningCount++; break;
                case CST::ParseError::Severity::INFO: infoCount++; break;
            }
        }
        
        std::cout << "Errors: " << errorCount << ", Warnings: " << warningCount << ", Info: " << infoCount << std::endl;
        
        // Print detailed error information
        std::cout << "\nDetailed Error Report:" << std::endl;
        std::cout << "=====================" << std::endl;
        
        for (size_t i = 0; i < errors.size() && i < 20; ++i) {  // Limit to first 20 errors
            const auto& error = errors[i];
            std::cout << "\n[" << (i + 1) << "] Line " << error.line << ", Column " << error.column << std::endl;
            std::cout << "    Message: " << error.message << std::endl;
            
            if (!error.context.empty()) {
                std::cout << "    Context: " << error.context << std::endl;
            }
            
            if (error.expectedToken != TokenType::UNDEFINED && error.actualToken != TokenType::UNDEFINED) {
                std::cout << "    Expected: " << static_cast<int>(error.expectedToken) 
                         << ", Got: " << static_cast<int>(error.actualToken) << std::endl;
            }
            
            if (!error.suggestions.empty()) {
                std::cout << "    Suggestions:" << std::endl;
                for (const auto& suggestion : error.suggestions) {
                    std::cout << "      - " << suggestion << std::endl;
                }
            }
        }
        
        if (errors.size() > 20) {
            std::cout << "\n... and " << (errors.size() - 20) << " more errors" << std::endl;
        }
        
        // Test CST structure
        std::cout << "\nCST Structure (first 3 levels):" << std::endl;
        std::cout << "================================" << std::endl;
        if (cst) {
            std::cout << cst->toString(0);
        }
        
        std::cout << "\n🎉 Error recovery test completed successfully!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}