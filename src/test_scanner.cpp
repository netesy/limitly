#include "frontend/scanner.hh"
#include <iostream>

int main() {
    std::string source = "var name = \"World\";\nprint(\"Hello, {name}!\");";
    
    Scanner scanner(source);
    CSTConfig config;
    config.preserveWhitespace = true;
    config.preserveComments = true;
    config.emitErrorTokens = true;
    
    auto tokens = scanner.scanAllTokens(config);
    
    std::cout << "Tokens:\n";
    for (const auto& token : tokens) {
        std::cout << "  " << static_cast<int>(token.type) << " '" << token.lexeme << "'\n";
    }
    
    return 0;
}