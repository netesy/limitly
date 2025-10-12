#include "src/frontend/scanner.hh"
#include "src/frontend/cst.hh"
#include "src/frontend/parser.hh"
#include <iostream>
#include <fstream>
#include <cassert>

struct TestResult {
    std::string testName;
    bool passed;
    std::string errorMessage;
    std::string originalSource;
    std::string reconstructedSource;
};

class TriviaValidator {
public:
    std::vector<TestResult> runAllTests() {
        std::vector<TestResult> results;
        
        // Test 1: Simple comment preservation
        results.push_back(testSimpleComment());
        
        // Test 2: Complex whitespace and comments
        results.push_back(testComplexTrivia());
        
        // Test 3: Nested comments
        results.push_back(testNestedComments());
        
        // Test 4: Mixed trivia patterns
        results.push_back(testMixedTrivia());
        
        // Test 5: Token-level trivia attachment
        results.push_back(testTokenTriviaAttachment());
        
        // Test 6: CST reconstruction accuracy
        results.push_back(testCSTReconstruction());
        
        return results;
    }

private:
    TestResult testSimpleComment() {
        TestResult result;
        result.testName = "Simple Comment Preservation";
        
        std::string source = "// Simple comment\nvar x = 42;";
        result.originalSource = source;
        
        try {
            Scanner scanner(source, "test.lm");
            auto tokens = scanner.scanTokens(ScanMode::CST);
            
            // Verify trivia is attached to tokens
            bool foundComment = false;
            for (const auto& token : tokens) {
                if (!token.getLeadingTrivia().empty()) {
                    for (const auto& trivia : token.getLeadingTrivia()) {
                        if (trivia.lexeme == "// Simple comment") {
                            foundComment = true;
                            break;
                        }
                    }
                }
            }
            
            if (!foundComment) {
                result.passed = false;
                result.errorMessage = "Comment not found in token trivia";
                return result;
            }
            
            // Test CST reconstruction
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
            for (const auto& token : tokens) {
                if (token.type != TokenType::EOF_TOKEN) {
                    cstRoot->addToken(token);
                }
            }
            
            std::string reconstructed = cstRoot->reconstructSource();
            result.reconstructedSource = reconstructed;
            
            result.passed = (source == reconstructed);
            if (!result.passed) {
                result.errorMessage = "Reconstruction mismatch";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testComplexTrivia() {
        TestResult result;
        result.testName = "Complex Trivia Patterns";
        
        std::string source = "/* Block */\n// Line\nvar   x   =   42   ;";
        result.originalSource = source;
        
        try {
            Scanner scanner(source, "test.lm");
            auto tokens = scanner.scanTokens(ScanMode::CST);
            
            // Test CST reconstruction
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
            for (const auto& token : tokens) {
                if (token.type != TokenType::EOF_TOKEN) {
                    cstRoot->addToken(token);
                }
            }
            
            std::string reconstructed = cstRoot->reconstructSource();
            result.reconstructedSource = reconstructed;
            
            result.passed = (source == reconstructed);
            if (!result.passed) {
                result.errorMessage = "Complex trivia reconstruction failed";
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
        
        std::string source = "/* Outer /* nested */ comment */\nvar x = 42;";
        result.originalSource = source;
        
        try {
            Scanner scanner(source, "test.lm");
            auto tokens = scanner.scanTokens(ScanMode::CST);
            
            // Test CST reconstruction
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
            for (const auto& token : tokens) {
                if (token.type != TokenType::EOF_TOKEN) {
                    cstRoot->addToken(token);
                }
            }
            
            std::string reconstructed = cstRoot->reconstructSource();
            result.reconstructedSource = reconstructed;
            
            result.passed = (source == reconstructed);
            if (!result.passed) {
                result.errorMessage = "Nested comment reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testMixedTrivia() {
        TestResult result;
        result.testName = "Mixed Trivia Patterns";
        
        std::string source = "\t// Tab comment\n   var x = 42;   // Trailing\n";
        result.originalSource = source;
        
        try {
            Scanner scanner(source, "test.lm");
            auto tokens = scanner.scanTokens(ScanMode::CST);
            
            // Test CST reconstruction
            auto cstRoot = std::make_unique<CST::Node>(CST::NodeKind::PROGRAM, 0, source.size());
            for (const auto& token : tokens) {
                if (token.type != TokenType::EOF_TOKEN) {
                    cstRoot->addToken(token);
                }
            }
            
            std::string reconstructed = cstRoot->reconstructSource();
            result.reconstructedSource = reconstructed;
            
            result.passed = (source == reconstructed);
            if (!result.passed) {
                result.errorMessage = "Mixed trivia reconstruction failed";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testTokenTriviaAttachment() {
        TestResult result;
        result.testName = "Token Trivia Attachment";
        
        std::string source = "// Comment\nvar x = 42;";
        result.originalSource = source;
        
        try {
            Scanner scanner(source, "test.lm");
            auto tokens = scanner.scanTokens(ScanMode::CST);
            
            // Verify each meaningful token has appropriate trivia
            bool varHasComment = false;
            bool xHasWhitespace = false;
            
            for (const auto& token : tokens) {
                if (token.type == TokenType::VAR && !token.getLeadingTrivia().empty()) {
                    for (const auto& trivia : token.getLeadingTrivia()) {
                        if (trivia.type == TokenType::COMMENT_LINE) {
                            varHasComment = true;
                        }
                    }
                }
                if (token.type == TokenType::IDENTIFIER && token.lexeme == "x" && !token.getLeadingTrivia().empty()) {
                    for (const auto& trivia : token.getLeadingTrivia()) {
                        if (trivia.type == TokenType::WHITESPACE) {
                            xHasWhitespace = true;
                        }
                    }
                }
            }
            
            result.passed = varHasComment && xHasWhitespace;
            if (!result.passed) {
                result.errorMessage = "Trivia not properly attached to tokens";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
    
    TestResult testCSTReconstruction() {
        TestResult result;
        result.testName = "CST Parser Reconstruction";
        
        std::string source = "// Function comment\nfn test() {\n    var x = 42; // Local var\n}";
        result.originalSource = source;
        
        try {
            Scanner scanner(source, "test.lm");
            Parser parser(scanner, true); // CST mode
            
            auto program = parser.parse();
            auto cstRoot = parser.getCST();
            
            if (cstRoot) {
                std::string reconstructed = cstRoot->reconstructSource();
                result.reconstructedSource = reconstructed;
                
                result.passed = (source == reconstructed);
                if (!result.passed) {
                    result.errorMessage = "CST parser reconstruction failed";
                }
            } else {
                result.passed = false;
                result.errorMessage = "No CST root generated";
            }
            
        } catch (const std::exception& e) {
            result.passed = false;
            result.errorMessage = "Exception: " + std::string(e.what());
        }
        
        return result;
    }
};

int main() {
    std::cout << "=== Trivia Preservation and Source Reconstruction Tests ===" << std::endl;
    
    TriviaValidator validator;
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
        } else {
            passed++;
        }
    }
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Passed: " << passed << "/" << total << std::endl;
    std::cout << "Success Rate: " << (100.0 * passed / total) << "%" << std::endl;
    
    return (passed == total) ? 0 : 1;
}