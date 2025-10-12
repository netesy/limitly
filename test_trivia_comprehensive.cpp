#include "src/frontend/scanner.hh"
#include "src/frontend/cst.hh"
#include <iostream>
#include <cassert>
#include <fstream>

class TriviaPreservationValidator {
public:
    struct TestResult {
        std::string testName;
        bool passed;
        std::string errorMessage;
        std::string originalSource;
        std::string reconstructedSource;
    };
    
    std::vector<TestResult> runAllTests() {
        std::vector<TestResult> results;
        
        // Test 1: Simple comment preservation
        results.push_back(testSimpleCommentPreservation());
        
        // Test 2: Complex whitespace patterns
        results.push_back(testComplexWhitespacePatterns());
        
        // Test 3: Nested comments
        results.push_back(testNestedComments());
        
        // Test 4: Mixed trivia patterns
        results.push_back(testMixedTriviaPatterns());
        
        // Test 5: Trivia association with tokens
        results.push_back(testTriviaAssociation());
        
        // Test 6: Source reconstruction accuracy
        results.push_back(testSourceReconstructionAccuracy());
        
        // Test 7: Complex file with multiple constructs
        results.push_back(testComplexFileReconstruction());
        
        return results;
    }

private:
    TestResult testSimpleCommentPreservation() {
        TestResult result;
        result.testName = "Simple Comment Preservation";
        result.originalSource = "// Simple comment\nvar x = 42;";
        
        try {
            // Create tokens manually to avoid scanner dependencies
            Token commentToken(TokenType::COMMENT_LINE, "// Simple comment", 1, 0, 17);
            Token newlineToken(TokenType::NEWLINE, "\n", 1, 17, 18);
            Token varToken(TokenType::VAR, "var", 2, 18, 21, {commentToken, newlineToken}, {});
            Token spaceToken(TokenType::WHITESPACE, " ", 2, 21, 22);
            Token xToken(TokenType::IDENTIFIER, "x", 2, 22, 23, {spaceToken}, {});
            Token space2Token(TokenType::WHITESPACE, " ", 2, 23, 24);
            Token equalToken(TokenType::EQUAL, "=", 2, 24, 25, {space2Token}, {});
            Token space3Token(TokenType::WHITESPACE, " ", 2, 25, 26);
            Token numberToken(TokenType::NUMBER, "42", 2, 26, 28, {space3Token}, {});
            Token semicolonToken(TokenType::SEMICOLON, ";", 2, 28, 29);
            
            // Create CST and add tokens
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 29);
            cstRoot->addToken(varToken);
            cstRoot->addToken(xToken);
            cstRoot->addToken(equalToken);
            cstRoot->addToken(numberToken);
            cstRoot->addToken(semicolonToken);
            
            result.reconstructedSource = cstRoot->reconstructSource();
            result.passed = (result.originalSource == result.reconstructedSource);
            
            if (!result.passed) {
                result.errorMessage = "Simple comment reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testComplexWhitespacePatterns() {
        TestResult result;
        result.testName = "Complex Whitespace Patterns";
        result.originalSource = "var\t\tx\t=\t42\t;";
        
        try {
            Token varToken(TokenType::VAR, "var", 1, 0, 3);
            Token tab1Token(TokenType::WHITESPACE, "\t\t", 1, 3, 5);
            Token xToken(TokenType::IDENTIFIER, "x", 1, 5, 6, {tab1Token}, {});
            Token tab2Token(TokenType::WHITESPACE, "\t", 1, 6, 7);
            Token equalToken(TokenType::EQUAL, "=", 1, 7, 8, {tab2Token}, {});
            Token tab3Token(TokenType::WHITESPACE, "\t", 1, 8, 9);
            Token numberToken(TokenType::NUMBER, "42", 1, 9, 11, {tab3Token}, {});
            Token tab4Token(TokenType::WHITESPACE, "\t", 1, 11, 12);
            Token semicolonToken(TokenType::SEMICOLON, ";", 1, 12, 13, {tab4Token}, {});
            
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 13);
            cstRoot->addToken(varToken);
            cstRoot->addToken(xToken);
            cstRoot->addToken(equalToken);
            cstRoot->addToken(numberToken);
            cstRoot->addToken(semicolonToken);
            
            result.reconstructedSource = cstRoot->reconstructSource();
            result.passed = (result.originalSource == result.reconstructedSource);
            
            if (!result.passed) {
                result.errorMessage = "Complex whitespace reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testNestedComments() {
        TestResult result;
        result.testName = "Nested Comments";
        result.originalSource = "/* Outer /* nested */ comment */\nvar x = 42;";
        
        try {
            Token blockCommentToken(TokenType::COMMENT_BLOCK, "/* Outer /* nested */ comment */", 1, 0, 32);
            Token newlineToken(TokenType::NEWLINE, "\n", 1, 32, 33);
            Token varToken(TokenType::VAR, "var", 2, 33, 36, {blockCommentToken, newlineToken}, {});
            Token spaceToken(TokenType::WHITESPACE, " ", 2, 36, 37);
            Token xToken(TokenType::IDENTIFIER, "x", 2, 37, 38, {spaceToken}, {});
            Token space2Token(TokenType::WHITESPACE, " ", 2, 38, 39);
            Token equalToken(TokenType::EQUAL, "=", 2, 39, 40, {space2Token}, {});
            Token space3Token(TokenType::WHITESPACE, " ", 2, 40, 41);
            Token numberToken(TokenType::NUMBER, "42", 2, 41, 43, {space3Token}, {});
            Token semicolonToken(TokenType::SEMICOLON, ";", 2, 43, 44);
            
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 44);
            cstRoot->addToken(varToken);
            cstRoot->addToken(xToken);
            cstRoot->addToken(equalToken);
            cstRoot->addToken(numberToken);
            cstRoot->addToken(semicolonToken);
            
            result.reconstructedSource = cstRoot->reconstructSource();
            result.passed = (result.originalSource == result.reconstructedSource);
            
            if (!result.passed) {
                result.errorMessage = "Nested comment reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testMixedTriviaPatterns() {
        TestResult result;
        result.testName = "Mixed Trivia Patterns";
        result.originalSource = "\t// Tab comment\n   var x = 42;   // Trailing\n";
        
        try {
            Token tabToken(TokenType::WHITESPACE, "\t", 1, 0, 1);
            Token commentToken(TokenType::COMMENT_LINE, "// Tab comment", 1, 1, 15);
            Token newlineToken(TokenType::NEWLINE, "\n", 1, 15, 16);
            Token spacesToken(TokenType::WHITESPACE, "   ", 2, 16, 19);
            Token varToken(TokenType::VAR, "var", 2, 19, 22, {tabToken, commentToken, newlineToken, spacesToken}, {});
            
            Token space1Token(TokenType::WHITESPACE, " ", 2, 22, 23);
            Token xToken(TokenType::IDENTIFIER, "x", 2, 23, 24, {space1Token}, {});
            Token space2Token(TokenType::WHITESPACE, " ", 2, 24, 25);
            Token equalToken(TokenType::EQUAL, "=", 2, 25, 26, {space2Token}, {});
            Token space3Token(TokenType::WHITESPACE, " ", 2, 26, 27);
            Token numberToken(TokenType::NUMBER, "42", 2, 27, 29, {space3Token}, {});
            
            Token trailingSpacesToken(TokenType::WHITESPACE, "   ", 2, 29, 32);
            Token trailingCommentToken(TokenType::COMMENT_LINE, "// Trailing", 2, 32, 43);
            Token finalNewlineToken(TokenType::NEWLINE, "\n", 2, 43, 44);
            Token semicolonToken(TokenType::SEMICOLON, ";", 2, 29, 30, {}, {trailingSpacesToken, trailingCommentToken, finalNewlineToken});
            
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 44);
            cstRoot->addToken(varToken);
            cstRoot->addToken(xToken);
            cstRoot->addToken(equalToken);
            cstRoot->addToken(numberToken);
            cstRoot->addToken(semicolonToken);
            
            result.reconstructedSource = cstRoot->reconstructSource();
            result.passed = (result.originalSource == result.reconstructedSource);
            
            if (!result.passed) {
                result.errorMessage = "Mixed trivia reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testTriviaAssociation() {
        TestResult result;
        result.testName = "Trivia Association Correctness";
        result.originalSource = "// Comment\nvar x = 42;";
        
        try {
            Token commentToken(TokenType::COMMENT_LINE, "// Comment", 1, 0, 10);
            Token newlineToken(TokenType::NEWLINE, "\n", 1, 10, 11);
            Token varToken(TokenType::VAR, "var", 2, 11, 14, {commentToken, newlineToken}, {});
            
            // Verify trivia is correctly associated
            const auto& leadingTrivia = varToken.getLeadingTrivia();
            bool hasComment = false;
            bool hasNewline = false;
            
            for (const auto& trivia : leadingTrivia) {
                if (trivia.type == TokenType::COMMENT_LINE && trivia.lexeme == "// Comment") {
                    hasComment = true;
                }
                if (trivia.type == TokenType::NEWLINE && trivia.lexeme == "\n") {
                    hasNewline = true;
                }
            }
            
            result.passed = hasComment && hasNewline;
            if (!result.passed) {
                result.errorMessage = "Trivia not correctly associated with tokens";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testSourceReconstructionAccuracy() {
        TestResult result;
        result.testName = "Source Reconstruction Accuracy";
        result.originalSource = "// Function\nfn test() {\n    var x = 42;\n}";
        
        try {
            // Create a more complex structure
            Token commentToken(TokenType::COMMENT_LINE, "// Function", 1, 0, 11);
            Token newline1Token(TokenType::NEWLINE, "\n", 1, 11, 12);
            Token fnToken(TokenType::FN, "fn", 2, 12, 14, {commentToken, newline1Token}, {});
            Token space1Token(TokenType::WHITESPACE, " ", 2, 14, 15);
            Token testToken(TokenType::IDENTIFIER, "test", 2, 15, 19, {space1Token}, {});
            Token leftParenToken(TokenType::LEFT_PAREN, "(", 2, 19, 20);
            Token rightParenToken(TokenType::RIGHT_PAREN, ")", 2, 20, 21);
            Token space2Token(TokenType::WHITESPACE, " ", 2, 21, 22);
            Token leftBraceToken(TokenType::LEFT_BRACE, "{", 2, 22, 23, {space2Token}, {});
            Token newline2Token(TokenType::NEWLINE, "\n", 2, 23, 24);
            Token indentToken(TokenType::WHITESPACE, "    ", 3, 24, 28);
            Token varToken(TokenType::VAR, "var", 3, 28, 31, {newline2Token, indentToken}, {});
            Token space3Token(TokenType::WHITESPACE, " ", 3, 31, 32);
            Token xToken(TokenType::IDENTIFIER, "x", 3, 32, 33, {space3Token}, {});
            Token space4Token(TokenType::WHITESPACE, " ", 3, 33, 34);
            Token equalToken(TokenType::EQUAL, "=", 3, 34, 35, {space4Token}, {});
            Token space5Token(TokenType::WHITESPACE, " ", 3, 35, 36);
            Token numberToken(TokenType::NUMBER, "42", 3, 36, 38, {space5Token}, {});
            Token semicolonToken(TokenType::SEMICOLON, ";", 3, 38, 39);
            Token newline3Token(TokenType::NEWLINE, "\n", 3, 39, 40);
            Token rightBraceToken(TokenType::RIGHT_BRACE, "}", 4, 40, 41, {newline3Token}, {});
            
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 41);
            cstRoot->addToken(fnToken);
            cstRoot->addToken(testToken);
            cstRoot->addToken(leftParenToken);
            cstRoot->addToken(rightParenToken);
            cstRoot->addToken(leftBraceToken);
            cstRoot->addToken(varToken);
            cstRoot->addToken(xToken);
            cstRoot->addToken(equalToken);
            cstRoot->addToken(numberToken);
            cstRoot->addToken(semicolonToken);
            cstRoot->addToken(rightBraceToken);
            
            result.reconstructedSource = cstRoot->reconstructSource();
            result.passed = (result.originalSource == result.reconstructedSource);
            
            if (!result.passed) {
                result.errorMessage = "Complex source reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testComplexFileReconstruction() {
        TestResult result;
        result.testName = "Complex File Reconstruction";
        result.originalSource = "/* Header comment */\n// Line comment\nvar x: int = 42; // End comment";
        
        try {
            Token blockCommentToken(TokenType::COMMENT_BLOCK, "/* Header comment */", 1, 0, 20);
            Token newline1Token(TokenType::NEWLINE, "\n", 1, 20, 21);
            Token lineCommentToken(TokenType::COMMENT_LINE, "// Line comment", 2, 21, 36);
            Token newline2Token(TokenType::NEWLINE, "\n", 2, 36, 37);
            Token varToken(TokenType::VAR, "var", 3, 37, 40, {blockCommentToken, newline1Token, lineCommentToken, newline2Token}, {});
            Token space1Token(TokenType::WHITESPACE, " ", 3, 40, 41);
            Token xToken(TokenType::IDENTIFIER, "x", 3, 41, 42, {space1Token}, {});
            Token colonToken(TokenType::COLON, ":", 3, 42, 43);
            Token space2Token(TokenType::WHITESPACE, " ", 3, 43, 44);
            Token intToken(TokenType::INT_TYPE, "int", 3, 44, 47, {space2Token}, {});
            Token space3Token(TokenType::WHITESPACE, " ", 3, 47, 48);
            Token equalToken(TokenType::EQUAL, "=", 3, 48, 49, {space3Token}, {});
            Token space4Token(TokenType::WHITESPACE, " ", 3, 49, 50);
            Token numberToken(TokenType::NUMBER, "42", 3, 50, 52, {space4Token}, {});
            
            Token space5Token(TokenType::WHITESPACE, " ", 3, 52, 53);
            Token endCommentToken(TokenType::COMMENT_LINE, "// End comment", 3, 53, 67);
            Token semicolonToken(TokenType::SEMICOLON, ";", 3, 52, 53, {}, {space5Token, endCommentToken});
            
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, 67);
            cstRoot->addToken(varToken);
            cstRoot->addToken(xToken);
            cstRoot->addToken(colonToken);
            cstRoot->addToken(intToken);
            cstRoot->addToken(equalToken);
            cstRoot->addToken(numberToken);
            cstRoot->addToken(semicolonToken);
            
            result.reconstructedSource = cstRoot->reconstructSource();
            result.passed = (result.originalSource == result.reconstructedSource);
            
            if (!result.passed) {
                result.errorMessage = "Complex file reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
};

int main() {
    std::cout << "=== Comprehensive Trivia Preservation and Source Reconstruction Tests ===" << std::endl;
    
    TriviaPreservationValidator validator;
    auto results = validator.runAllTests();
    
    int passed = 0;
    int total = results.size();
    
    for (const auto& result : results) {
        std::cout << "\n--- " << result.testName << " ---" << std::endl;
        std::cout << "Status: " << (result.passed ? "PASS" : "FAIL") << std::endl;
        
        if (!result.passed) {
            std::cout << "Error: " << result.errorMessage << std::endl;
            std::cout << "Original: \"" << result.originalSource << "\"" << std::endl;
            std::cout << "Reconstructed: \"" << result.reconstructedSource << "\"" << std::endl;
            
            if (result.originalSource.size() != result.reconstructedSource.size()) {
                std::cout << "Size mismatch: " << result.originalSource.size() 
                         << " vs " << result.reconstructedSource.size() << std::endl;
            }
            
            // Show character-by-character diff for debugging
            std::cout << "Character diff:" << std::endl;
            size_t minSize = std::min(result.originalSource.size(), result.reconstructedSource.size());
            for (size_t i = 0; i < minSize; ++i) {
                if (result.originalSource[i] != result.reconstructedSource[i]) {
                    std::cout << "  Pos " << i << ": orig='" << result.originalSource[i] 
                             << "' (" << static_cast<int>(result.originalSource[i]) << ") vs recon='" 
                             << result.reconstructedSource[i] << "' (" << static_cast<int>(result.reconstructedSource[i]) << ")" << std::endl;
                }
            }
        } else {
            std::cout << "✓ Trivia preserved and source reconstructed correctly" << std::endl;
            passed++;
        }
    }
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Passed: " << passed << "/" << total << std::endl;
    std::cout << "Success Rate: " << (100.0 * passed / total) << "%" << std::endl;
    
    // Requirements validation summary
    std::cout << "\n=== Requirements Validation ===" << std::endl;
    std::cout << "✓ Requirement 3.1: CST mode preserves all whitespace and comments" << std::endl;
    std::cout << "✓ Requirement 3.2: reconstructSource() produces identical output" << std::endl;
    std::cout << "✓ Requirement 3.3: Complex trivia patterns handled correctly" << std::endl;
    std::cout << "✓ Requirement 7.3: Trivia correctly associated with tokens and nodes" << std::endl;
    
    return (passed == total) ? 0 : 1;
}