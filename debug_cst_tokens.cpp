#include "src/frontend/scanner.hh"
#include "src/frontend/cst_parser.hh"
#include <iostream>

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
    
    // Test CST parsing
    CSTConfig config;
    CST::CSTParser parser(scanner, config);
    
    std::cout << "\nParsing with CST parser..." << std::endl;
    auto cst = parser.parse();
    
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