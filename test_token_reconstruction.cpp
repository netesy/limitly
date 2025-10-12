#include "src/frontend/scanner.hh"
#include "src/frontend/cst.hh"
#include <iostream>
#include <vector>

// Test token reconstruction without scanner dependencies
int main() {
    std::cout << "=== Token Reconstruction Test ===" << std::endl;
    
    // Test 1: Manual token creation with trivia
    {
        std::cout << "\n--- Test 1: Manual Token with Trivia ---" << std::endl;
        
        // Create trivia tokens
        Token commentTrivia(TokenType::COMMENT_LINE, "// Comment", 1, 0, 10);
        Token newlineTrivia(TokenType::NEWLINE, "\n", 1, 10, 11);
        Token whitespaceTrivia(TokenType::WHITESPACE, " ", 2, 11, 12);
        
        // Create main token with trivia
        std::vector<Token> leadingTrivia = {commentTrivia, newlineTrivia};
        std::vector<Token> trailingTrivia = {};
        
        Token varToken(TokenType::VAR, "var", 2, 12, 15, leadingTrivia, trailingTrivia);
        
        std::string reconstructed = varToken.reconstructSource();
        std::string expected = "// Comment\nvar";
        
        std::cout << "Expected: \"" << expected << "\"" << std::endl;
        std::cout << "Reconstructed: \"" << reconstructed << "\"" << std::endl;
        std::cout << "Match: " << (expected == reconstructed ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 2: CST Node reconstruction with multiple tokens
    {
        std::cout << "\n--- Test 2: CST Node with Multiple Tokens ---" << std::endl;
        
        // Create tokens with trivia
        Token commentTrivia(TokenType::COMMENT_LINE, "// Comment", 1, 0, 10);
        Token newlineTrivia(TokenType::NEWLINE, "\n", 1, 10, 11);
        
        std::vector<Token> varLeadingTrivia = {commentTrivia, newlineTrivia};
        Token varToken(TokenType::VAR, "var", 2, 11, 14, varLeadingTrivia, {});
        
        std::vector<Token> xLeadingTrivia = {Token(TokenType::WHITESPACE, " ", 2, 14, 15)};
        Token xToken(TokenType::IDENTIFIER, "x", 2, 15, 16, xLeadingTrivia, {});
        
        std::vector<Token> equalLeadingTrivia = {Token(TokenType::WHITESPACE, " ", 2, 16, 17)};
        Token equalToken(TokenType::EQUAL, "=", 2, 17, 18, equalLeadingTrivia, {});
        
        std::vector<Token> numberLeadingTrivia = {Token(TokenType::WHITESPACE, " ", 2, 18, 19)};
        Token numberToken(TokenType::NUMBER, "42", 2, 19, 21, numberLeadingTrivia, {});
        
        Token semicolonToken(TokenType::SEMICOLON, ";", 2, 21, 22, {}, {});
        
        // Create CST node and add tokens
        auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 22);
        cstRoot->addToken(varToken);
        cstRoot->addToken(xToken);
        cstRoot->addToken(equalToken);
        cstRoot->addToken(numberToken);
        cstRoot->addToken(semicolonToken);
        
        std::string reconstructed = cstRoot->reconstructSource();
        std::string expected = "// Comment\nvar x = 42;";
        
        std::cout << "Expected: \"" << expected << "\"" << std::endl;
        std::cout << "Reconstructed: \"" << reconstructed << "\"" << std::endl;
        std::cout << "Match: " << (expected == reconstructed ? "PASS" : "FAIL") << std::endl;
        
        if (expected != reconstructed) {
            std::cout << "Expected size: " << expected.size() << std::endl;
            std::cout << "Reconstructed size: " << reconstructed.size() << std::endl;
        }
    }
    
    // Test 3: Complex trivia patterns
    {
        std::cout << "\n--- Test 3: Complex Trivia Patterns ---" << std::endl;
        
        // Block comment + line comment + multiple whitespace
        Token blockComment(TokenType::COMMENT_BLOCK, "/* Block */", 1, 0, 11);
        Token newline1(TokenType::NEWLINE, "\n", 1, 11, 12);
        Token lineComment(TokenType::COMMENT_LINE, "// Line", 2, 12, 19);
        Token newline2(TokenType::NEWLINE, "\n", 2, 19, 20);
        Token spaces(TokenType::WHITESPACE, "   ", 3, 20, 23);
        
        std::vector<Token> complexTrivia = {blockComment, newline1, lineComment, newline2, spaces};
        Token varToken(TokenType::VAR, "var", 3, 23, 26, complexTrivia, {});
        
        std::string reconstructed = varToken.reconstructSource();
        std::string expected = "/* Block */\n// Line\n   var";
        
        std::cout << "Expected: \"" << expected << "\"" << std::endl;
        std::cout << "Reconstructed: \"" << reconstructed << "\"" << std::endl;
        std::cout << "Match: " << (expected == reconstructed ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 4: Trivia association correctness
    {
        std::cout << "\n--- Test 4: Trivia Association ---" << std::endl;
        
        // Test that trivia is correctly associated with appropriate tokens
        Token comment(TokenType::COMMENT_LINE, "// Variable declaration", 1, 0, 23);
        Token newline(TokenType::NEWLINE, "\n", 1, 23, 24);
        
        std::vector<Token> leadingTrivia = {comment, newline};
        Token varToken(TokenType::VAR, "var", 2, 24, 27, leadingTrivia, {});
        
        // Verify trivia is accessible
        const auto& trivia = varToken.getLeadingTrivia();
        bool hasComment = false;
        bool hasNewline = false;
        
        for (const auto& t : trivia) {
            if (t.type == TokenType::COMMENT_LINE && t.lexeme == "// Variable declaration") {
                hasComment = true;
            }
            if (t.type == TokenType::NEWLINE && t.lexeme == "\n") {
                hasNewline = true;
            }
        }
        
        std::cout << "Comment found: " << (hasComment ? "YES" : "NO") << std::endl;
        std::cout << "Newline found: " << (hasNewline ? "YES" : "NO") << std::endl;
        std::cout << "Association: " << (hasComment && hasNewline ? "PASS" : "FAIL") << std::endl;
    }
    
    std::cout << "\n=== All Tests Complete ===" << std::endl;
    return 0;
}