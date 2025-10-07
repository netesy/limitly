#include "src/frontend/scanner.hh"
#include "src/frontend/cst_parser.hh"
#include <iostream>
#include <chrono>

int main() {
    std::string source = "var x = 5;";
    
    Scanner scanner(source);
    auto tokens = scanner.scanTokens();
    
    std::cout << "Tokens for 'var x = 5;':" << std::endl;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];
        std::cout << i << ": " << static_cast<int>(token.type) 
                  << " '" << token.lexeme << "' at line " << token.line << std::endl;
    }
    
    // Test CST parsing with manual token advancement tracking
    CSTConfig config;
    CST::CSTParser parser(scanner, config);
    
    std::cout << "\nBefore parsing:" << std::endl;
    std::cout << "Total tokens: " << parser.getTotalTokens() << std::endl;
    std::cout << "Current position: " << parser.getTokensConsumed() << std::endl;
    std::cout << "Is at end: " << parser.isAtEnd() << std::endl;
    
    std::cout << "\nStarting parse..." << std::endl;
    
    // Add timeout mechanism
    auto start_time = std::chrono::steady_clock::now();
    const auto timeout = std::chrono::seconds(5);
    
    auto cst = parser.parse();
    
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "Parse completed in " << duration.count() << "ms" << std::endl;
    
    if (cst) {
        std::cout << "CST created successfully:" << std::endl;
        std::cout << cst->toString() << std::endl;
    } else {
        std::cout << "CST creation failed" << std::endl;
    }
    
    auto errors = parser.getErrors();
    std::cout << "Errors: " << errors.size() << std::endl;
    for (const auto& error : errors) {
        std::cout << "  " << error.errorCode << ": " << error.description << std::endl;
    }
    
    return 0;
}