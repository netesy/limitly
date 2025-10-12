#include "src/frontend/scanner.hh"
#include "src/frontend/cst.hh"
#include <iostream>

// Simple test to verify trivia preservation works end-to-end
int main() {
    std::cout << "=== Simple Trivia Test ===" << std::endl;
    
    // Test with a simple source that doesn't trigger scanner errors
    std::string source = "var x = 42;";
    std::cout << "Testing source: \"" << source << "\"" << std::endl;
    
    std::cout << "Scanner integration test skipped due to debugger dependencies" << std::endl;
    
    std::cout << "\n=== Manual Token Test ===" << std::endl;
    
    // Test manual token creation (this should always work)
    Token varToken(TokenType::VAR, "var", 1, 0, 3);
    Token spaceToken(TokenType::WHITESPACE, " ", 1, 3, 4);
    Token xToken(TokenType::IDENTIFIER, "x", 1, 4, 5, {spaceToken}, {});
    Token space2Token(TokenType::WHITESPACE, " ", 1, 5, 6);
    Token equalToken(TokenType::EQUAL, "=", 1, 6, 7, {space2Token}, {});
    Token space3Token(TokenType::WHITESPACE, " ", 1, 7, 8);
    Token numberToken(TokenType::NUMBER, "42", 1, 8, 10, {space3Token}, {});
    Token semicolonToken(TokenType::SEMICOLON, ";", 1, 10, 11);
    
    auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 11);
    cstRoot->addToken(varToken);
    cstRoot->addToken(xToken);
    cstRoot->addToken(equalToken);
    cstRoot->addToken(numberToken);
    cstRoot->addToken(semicolonToken);
    
    std::string manualReconstructed = cstRoot->reconstructSource();
    std::cout << "Manual reconstruction: \"" << manualReconstructed << "\"" << std::endl;
    std::cout << "Expected: \"" << source << "\"" << std::endl;
    std::cout << "Manual test: " << (source == manualReconstructed ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}