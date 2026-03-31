#include "../src/frontend/scanner.hh"
#include <iostream>
#include <vector>

int main() {
    std::string source = "Active => { return true; }";
    LM::Frontend::Scanner scanner(source);
    std::vector<LM::Frontend::Token> tokens = scanner.scanTokens(LM::Frontend::ScanMode::LEGACY);
    
    for (const auto& token : tokens) {
        std::cout << "Lexeme: '" << token.lexeme << "', Type: " << (int)token.type << std::endl;
    }
    return 0;
}
