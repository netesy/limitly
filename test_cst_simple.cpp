#include "src/frontend/scanner.hh"
#include "src/frontend/parser.hh"
#include <iostream>
#include <fstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    
    // Remove the last newline if the file doesn't end with one
    if (!content.empty() && content.back() == '\n') {
        content.pop_back();
    }
    
    return content;
}

int main() {
    std::cout << "=== Simple CST Parser Test ===" << std::endl;
    
    std::string filename = "tests/cst/trivia_test_simple.lm";
    std::string source = readFile(filename);
    
    if (source.empty()) {
        std::cout << "ERROR: Could not read file" << std::endl;
        return 1;
    }
    
    std::cout << "Testing file: " << filename << std::endl;
    std::cout << "Source size: " << source.size() << " bytes" << std::endl;
    
    try {
        // Test scanner
        Scanner scanner(source, filename);
        auto tokens = scanner.scanTokens(ScanMode::CST);
        std::cout << "Scanner produced " << tokens.size() << " tokens" << std::endl;
        
        // Test CST parser
        Scanner parserScanner(source, filename);
        auto parserTokens = parserScanner.scanTokens(ScanMode::CST);
        std::cout << "Parser scanner produced " << parserTokens.size() << " tokens" << std::endl;
        
        Parser parser(parserScanner, true); // CST mode
        
        std::cout << "Starting parse..." << std::endl;
        auto program = parser.parse();
        std::cout << "Parse completed" << std::endl;
        
        if (!program) {
            std::cout << "ERROR: Parser returned null program" << std::endl;
            return 1;
        }
        
        // Check CST root
        const CST::Node* cstRoot = parser.getCST();
        if (!cstRoot) {
            std::cout << "WARNING: No CST root created" << std::endl;
        } else {
            std::cout << "CST root created successfully" << std::endl;
            
            // Test reconstruction
            std::string reconstructed = cstRoot->reconstructSource();
            std::cout << "Reconstructed size: " << reconstructed.size() << " bytes" << std::endl;
            
            std::cout << "Reconstructed content:" << std::endl;
            std::cout << "\"" << reconstructed << "\"" << std::endl;
            
            bool exactMatch = (source == reconstructed);
            std::cout << "Exact match: " << (exactMatch ? "YES" : "NO") << std::endl;
            
            if (!exactMatch) {
                std::cout << "Size difference: " << static_cast<int>(reconstructed.size()) - static_cast<int>(source.size()) << std::endl;
                
                // Show first few differences
                size_t minSize = std::min(source.size(), reconstructed.size());
                for (size_t i = 0; i < minSize && i < 10; ++i) {
                    if (source[i] != reconstructed[i]) {
                        std::cout << "Diff at pos " << i << ": '" << source[i] << "' vs '" << reconstructed[i] << "'" << std::endl;
                    }
                }
            }
        }
        
        // Check parser statistics
        std::cout << "CST nodes created: " << parser.getCSTNodeCount() << std::endl;
        std::cout << "Trivia attachments: " << parser.getTriviaAttachmentCount() << std::endl;
        
        // Check for errors
        if (parser.hadError()) {
            std::cout << "Parser had " << parser.getErrors().size() << " errors" << std::endl;
        } else {
            std::cout << "No parser errors" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "Test completed successfully" << std::endl;
    return 0;
}