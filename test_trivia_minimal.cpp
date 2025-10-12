#include "src/frontend/scanner.hh"
#include "src/frontend/cst.hh"
#include <iostream>
#include <cassert>

// Simple test without debugger dependencies
int main() {
    std::cout << "=== Minimal Trivia Preservation Test ===" << std::endl;
    
    // Test 1: Simple comment and whitespace
    {
        std::cout << "\n--- Test 1: Simple Comment ---" << std::endl;
        std::string source = "// Comment\nvar x = 42;";
        std::cout << "Original: \"" << source << "\"" << std::endl;
        
        Scanner scanner(source, "test.lm");
        auto tokens = scanner.scanTokens(ScanMode::CST);
        
        std::cout << "Tokens: " << tokens.size() << std::endl;
        
        // Create CST and reconstruct
        auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
        for (const auto& token : tokens) {
            if (token.type != TokenType::EOF_TOKEN) {
                cstRoot->addToken(token);
            }
        }
        
        std::string reconstructed = cstRoot->reconstructSource();
        std::cout << "Reconstructed: \"" << reconstructed << "\"" << std::endl;
        
        bool match = (source == reconstructed);
        std::cout << "Match: " << (match ? "PASS" : "FAIL") << std::endl;
        
        if (!match) {
            std::cout << "Original size: " << source.size() << std::endl;
            std::cout << "Reconstructed size: " << reconstructed.size() << std::endl;
        }
    }
    
    // Test 2: Multiple whitespace patterns
    {
        std::cout << "\n--- Test 2: Multiple Whitespace ---" << std::endl;
        std::string source = "var   x   =   42   ;";
        std::cout << "Original: \"" << source << "\"" << std::endl;
        
        Scanner scanner(source, "test.lm");
        auto tokens = scanner.scanTokens(ScanMode::CST);
        
        // Create CST and reconstruct
        auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
        for (const auto& token : tokens) {
            if (token.type != TokenType::EOF_TOKEN) {
                cstRoot->addToken(token);
            }
        }
        
        std::string reconstructed = cstRoot->reconstructSource();
        std::cout << "Reconstructed: \"" << reconstructed << "\"" << std::endl;
        
        bool match = (source == reconstructed);
        std::cout << "Match: " << (match ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 3: Block comment
    {
        std::cout << "\n--- Test 3: Block Comment ---" << std::endl;
        std::string source = "/* Block */\nvar x = 42;";
        std::cout << "Original: \"" << source << "\"" << std::endl;
        
        Scanner scanner(source, "test.lm");
        auto tokens = scanner.scanTokens(ScanMode::CST);
        
        // Create CST and reconstruct
        auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
        for (const auto& token : tokens) {
            if (token.type != TokenType::EOF_TOKEN) {
                cstRoot->addToken(token);
            }
        }
        
        std::string reconstructed = cstRoot->reconstructSource();
        std::cout << "Reconstructed: \"" << reconstructed << "\"" << std::endl;
        
        bool match = (source == reconstructed);
        std::cout << "Match: " << (match ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 4: Token trivia attachment verification
    {
        std::cout << "\n--- Test 4: Token Trivia Attachment ---" << std::endl;
        std::string source = "// Comment\nvar x = 42;";
        
        Scanner scanner(source, "test.lm");
        auto tokens = scanner.scanTokens(ScanMode::CST);
        
        bool foundCommentTrivia = false;
        bool foundWhitespaceTrivia = false;
        
        for (const auto& token : tokens) {
            if (token.type == TokenType::VAR) {
                std::cout << "VAR token has " << token.getLeadingTrivia().size() << " leading trivia" << std::endl;
                for (const auto& trivia : token.getLeadingTrivia()) {
                    std::cout << "  Trivia type: " << static_cast<int>(trivia.type) << " lexeme: \"" << trivia.lexeme << "\"" << std::endl;
                    if (trivia.type == TokenType::COMMENT_LINE) {
                        foundCommentTrivia = true;
                    }
                }
            }
            if (token.type == TokenType::IDENTIFIER && token.lexeme == "x") {
                std::cout << "IDENTIFIER 'x' has " << token.getLeadingTrivia().size() << " leading trivia" << std::endl;
                for (const auto& trivia : token.getLeadingTrivia()) {
                    std::cout << "  Trivia type: " << static_cast<int>(trivia.type) << " lexeme: \"" << trivia.lexeme << "\"" << std::endl;
                    if (trivia.type == TokenType::WHITESPACE || trivia.type == TokenType::NEWLINE) {
                        foundWhitespaceTrivia = true;
                    }
                }
            }
        }
        
        std::cout << "Comment trivia found: " << (foundCommentTrivia ? "YES" : "NO") << std::endl;
        std::cout << "Whitespace trivia found: " << (foundWhitespaceTrivia ? "YES" : "NO") << std::endl;
        std::cout << "Trivia attachment: " << (foundCommentTrivia && foundWhitespaceTrivia ? "PASS" : "FAIL") << std::endl;
    }
    
    std::cout << "\n=== Test Complete ===" << std::endl;
    return 0;
}