#include "frontend/scanner.hh"
#include <iostream>

int main() {
    std::cout << "Testing Token enhancements...\n\n";
    
    // Test 1: Default constructors
    std::cout << "Test 1: Default constructors\n";
    Token defaultToken;
    std::cout << "  Default token type: " << static_cast<int>(defaultToken.type) << "\n";
    std::cout << "  Default token lexeme: '" << defaultToken.lexeme << "'\n";
    std::cout << "  Default token line: " << defaultToken.line << "\n\n";
    
    // Test 2: Constructor with parameters
    std::cout << "Test 2: Constructor with parameters\n";
    Token paramToken(TokenType::IDENTIFIER, "testVar", 1, 0, 7);
    std::cout << "  Param token type: " << static_cast<int>(paramToken.type) << "\n";
    std::cout << "  Param token lexeme: '" << paramToken.lexeme << "'\n";
    std::cout << "  Param token line: " << paramToken.line << "\n";
    std::cout << "  Param token start: " << paramToken.start << "\n";
    std::cout << "  Param token end: " << paramToken.end << "\n\n";
    
    // Test 3: Trivia accessors
    std::cout << "Test 3: Trivia accessors\n";
    Token triviaToken(TokenType::IDENTIFIER, "main", 1, 5, 9);
    
    // Add some leading trivia
    Token leadingSpace(TokenType::WHITESPACE, "  ", 1, 0, 2);
    Token leadingComment(TokenType::COMMENT_LINE, "// comment", 1, 2, 12);
    triviaToken.leadingTrivia.push_back(leadingSpace);
    triviaToken.leadingTrivia.push_back(leadingComment);
    
    // Add some trailing trivia
    Token trailingSpace(TokenType::WHITESPACE, " ", 1, 9, 10);
    triviaToken.trailingTrivia.push_back(trailingSpace);
    
    std::cout << "  Leading trivia count: " << triviaToken.getLeadingTrivia().size() << "\n";
    std::cout << "  Trailing trivia count: " << triviaToken.getTrailingTrivia().size() << "\n";
    
    for (size_t i = 0; i < triviaToken.getLeadingTrivia().size(); ++i) {
        const auto& trivia = triviaToken.getLeadingTrivia()[i];
        std::cout << "    Leading trivia " << i << ": '" << trivia.lexeme << "'\n";
    }
    
    for (size_t i = 0; i < triviaToken.getTrailingTrivia().size(); ++i) {
        const auto& trivia = triviaToken.getTrailingTrivia()[i];
        std::cout << "    Trailing trivia " << i << ": '" << trivia.lexeme << "'\n";
    }
    
    // Test 4: reconstructSource method
    std::cout << "\nTest 4: reconstructSource method\n";
    std::string reconstructed = triviaToken.reconstructSource();
    std::cout << "  Reconstructed source: '" << reconstructed << "'\n";
    std::cout << "  Expected: '  // commentmain '\n";
    std::cout << "  Match: " << (reconstructed == "  // commentmain " ? "YES" : "NO") << "\n\n";
    
    // Test 5: Scanner integration
    std::cout << "Test 5: Scanner integration\n";
    std::string source = "var name = \"World\";\nprint(\"Hello, {name}!\");";
    
    Scanner scanner(source);
    CSTConfig config;
    config.preserveWhitespace = true;
    config.preserveComments = true;
    config.emitErrorTokens = true;
    
    auto tokens = scanner.scanAllTokens(config);
    
    std::cout << "  Scanned " << tokens.size() << " tokens\n";
    for (size_t i = 0; i < std::min(tokens.size(), size_t(5)); ++i) {
        const auto& token = tokens[i];
        std::cout << "    Token " << i << ": " << static_cast<int>(token.type) 
                  << " '" << token.lexeme << "' (leading: " << token.getLeadingTrivia().size()
                  << ", trailing: " << token.getTrailingTrivia().size() << ")\n";
    }
    
    std::cout << "\nAll Token enhancement tests completed!\n";
    return 0;
}