#include <iostream>
#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"

int main() {
    std::string source = "x = 100;";
    Scanner scanner(source);
    auto tokens = scanner.scanTokens();
    
    std::cout << "Tokens generated:" << std::endl;
    for (const auto& token : tokens) {
        std::cout << "  " << static_cast<int>(token.type) << ": '" << token.lexeme << "'" << std::endl;
    }
    
    return 0;
}