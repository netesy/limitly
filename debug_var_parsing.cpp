#include "src/frontend/scanner.hh"
#include "src/frontend/cst_parser.hh"
#include <iostream>

int main() {
    std::string source = "var y = // missing value\nfn test() { return 42; }";
    
    Scanner scanner(source);
    CSTConfig config;
    config.preserveComments = true;
    config.preserveWhitespace = true;
    config.emitErrorTokens = true;
    
    // Get tokens using scanAllTokens (same as CST parser)
    auto tokens = scanner.scanAllTokens(config);
    
    std::cout << "Tokens from scanAllTokens for 'var x = 5;':" << std::endl;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];
        std::cout << i << ": " << static_cast<int>(token.type) 
                  << " '" << token.lexeme << "' at line " << token.line 
                  << " [" << token.start << "-" << token.end << "]" << std::endl;
    }
    
    // Test CST parsing step by step
    CST::CSTParser parser(scanner, config);
    
    std::cout << "\nParser state before parsing:" << std::endl;
    std::cout << "Total tokens: " << parser.getTotalTokens() << std::endl;
    std::cout << "Current position: " << parser.getTokensConsumed() << std::endl;
    
    auto cst = parser.parse();
    
    std::cout << "\nParser state after parsing:" << std::endl;
    std::cout << "Current position: " << parser.getTokensConsumed() << std::endl;
    
    if (cst) {
        std::cout << "\nCST Structure:" << std::endl;
        std::cout << cst->toString() << std::endl;
    }
    
    auto errors = parser.getErrors();
    std::cout << "\nErrors: " << errors.size() << std::endl;
    for (const auto& error : errors) {
        std::cout << "  " << error.errorCode << ": " << error.description << std::endl;
    }
    
    return 0;
}