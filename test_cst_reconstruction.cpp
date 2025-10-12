#include "src/frontend/scanner.hh"
#include "src/frontend/cst.hh"
#include <iostream>

int main() {
    std::cout << "=== CST Reconstruction Test ===" << std::endl;
    
    std::string source = "// Comment\nvar x: int = 42;";
    std::cout << "Original: \"" << source << "\"" << std::endl;
    
    // Test scanner with trivia attachment
    Scanner scanner(source, "test.lm");
    auto tokens = scanner.scanTokens(ScanMode::CST);
    
    std::cout << "Tokens produced: " << tokens.size() << std::endl;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];
        std::cout << "[" << i << "] " << static_cast<int>(token.type) << ": \"" << token.lexeme << "\"";
        
        if (!token.getLeadingTrivia().empty()) {
            std::cout << " [Leading: ";
            for (const auto& trivia : token.getLeadingTrivia()) {
                std::cout << "\"" << trivia.lexeme << "\" ";
            }
            std::cout << "]";
        }
        
        if (!token.getTrailingTrivia().empty()) {
            std::cout << " [Trailing: ";
            for (const auto& trivia : token.getTrailingTrivia()) {
                std::cout << "\"" << trivia.lexeme << "\" ";
            }
            std::cout << "]";
        }
        
        std::cout << std::endl;
    }
    
    // Test CST reconstruction
    auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
    
    for (const auto& token : tokens) {
        if (token.type != TokenType::EOF_TOKEN) {
            cstRoot->addToken(token);
        }
    }
    
    std::string reconstructed = cstRoot->reconstructSource();
    std::cout << "Reconstructed: \"" << reconstructed << "\"" << std::endl;
    
    bool exactMatch = (source == reconstructed);
    std::cout << "Exact match: " << (exactMatch ? "YES" : "NO") << std::endl;
    
    if (!exactMatch) {
        std::cout << "Original size: " << source.size() << std::endl;
        std::cout << "Reconstructed size: " << reconstructed.size() << std::endl;
    }
    
    return 0;
}