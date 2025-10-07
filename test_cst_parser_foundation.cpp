#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include "src/error/error_handling.hh"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Testing CSTParser Foundation..." << std::endl;
    
    // Test 1: Basic constructor with tokens
    std::vector<Token> testTokens;
    Token token1;
    token1.type = TokenType::IDENTIFIER;
    token1.lexeme = "test";
    token1.line = 1;
    token1.start = 0;
    token1.end = 4;
    testTokens.push_back(token1);
    
    Token eofToken;
    eofToken.type = TokenType::EOF_TOKEN;
    eofToken.lexeme = "";
    eofToken.line = 1;
    eofToken.start = 4;
    eofToken.end = 4;
    testTokens.push_back(eofToken);
    
    CST::CSTParser parser(testTokens);
    
    // Test 2: Configuration
    CST::RecoveryConfig config;
    config.maxErrors = 50;
    config.continueOnError = true;
    parser.setRecoveryConfig(config);
    
    assert(parser.getRecoveryConfig().maxErrors == 50);
    assert(parser.getRecoveryConfig().continueOnError == true);
    
    // Test 3: Basic parsing (should create empty program node)
    auto cst = parser.parse();
    assert(cst != nullptr);
    assert(cst->kind == CST::NodeKind::PROGRAM);
    
    // Test 4: Error handling
    assert(!parser.hasErrors());  // Should have no errors for empty program
    assert(parser.getErrorCount() == 0);
    
    // Test 5: Token consumption tracking
    assert(parser.getTotalTokens() == 2);  // identifier + EOF
    
    std::cout << "✓ CSTParser constructor works" << std::endl;
    std::cout << "✓ Configuration methods work" << std::endl;
    std::cout << "✓ Basic parsing creates program node" << std::endl;
    std::cout << "✓ Error handling infrastructure works" << std::endl;
    std::cout << "✓ Token tracking works" << std::endl;
    
    // Test 6: Scanner integration
    std::string source = "var x = 42;";
    Scanner scanner(source);
    CSTConfig cstConfig;
    cstConfig.preserveWhitespace = true;
    cstConfig.preserveComments = true;
    
    CST::CSTParser scannerParser(scanner, cstConfig);
    auto cst2 = scannerParser.parse();
    assert(cst2 != nullptr);
    assert(cst2->kind == CST::NodeKind::PROGRAM);
    
    std::cout << "✓ Scanner integration works" << std::endl;
    
    // Test 7: Utility functions
    CST::RecoveryConfig parseConfig;
    auto cst3 = CST::parseTokensToCST(testTokens, parseConfig);
    assert(cst3 != nullptr);
    assert(cst3->kind == CST::NodeKind::PROGRAM);
    
    std::cout << "✓ Utility functions work" << std::endl;
    
    // Test 8: ParseError structure
    CST::ParseError error("Test error", 10, 1, 5);
    assert(error.message == "Test error");
    assert(error.position == 10);
    assert(error.line == 1);
    assert(error.column == 5);
    assert(error.severity == CST::ParseError::Severity::ERROR);
    
    std::cout << "✓ ParseError structure works" << std::endl;
    
    // Test 9: RecoveryConfig structure
    CST::RecoveryConfig testConfig;
    assert(testConfig.maxErrors == 100);  // Default value
    assert(testConfig.continueOnError == true);  // Default value
    assert(testConfig.preserveTrivia == true);  // Default value
    assert(!testConfig.syncTokens.empty());  // Should have default sync tokens
    
    std::cout << "✓ RecoveryConfig structure works" << std::endl;
    
    std::cout << std::endl << "All CSTParser foundation tests passed! ✓" << std::endl;
    
    return 0;
}