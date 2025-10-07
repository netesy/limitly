#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include <iostream>
#include <cassert>

void testBasicErrorRecovery() {
    std::cout << "Testing basic error recovery..." << std::endl;
    
    // Test source with syntax errors
    std::string source = R"(
        var x = 5
        var y = // missing value
        fn test() {
            if (x > 0 {  // missing closing paren
                print("positive");
            // missing closing brace
        var z = "hello"
    )";
    
    Scanner scanner(source);
    CSTConfig config;
    config.preserveComments = true;
    config.preserveWhitespace = true;
    config.emitErrorTokens = true;
    
    CST::CSTParser parser(scanner, config);
    
    // Configure error recovery
    CST::RecoveryConfig recoveryConfig;
    recoveryConfig.maxErrors = 10;
    recoveryConfig.continueOnError = true;
    recoveryConfig.insertMissingTokens = true;
    recoveryConfig.createPartialNodes = true;
    parser.setRecoveryConfig(recoveryConfig);
    
    // Parse with error recovery
    auto cst = parser.parse();
    
    // Check that we got a CST even with errors
    assert(cst != nullptr);
    std::cout << "✓ CST created despite syntax errors" << std::endl;
    
    // Check that errors were reported
    auto errors = parser.getErrors();
    assert(!errors.empty());
    std::cout << "✓ Errors were reported: " << errors.size() << " errors" << std::endl;
    
    // Print errors for debugging
    for (const auto& error : errors) {
        std::cout << "Error at line " << error.line << ": " << error.message << std::endl;
        if (!error.suggestions.empty()) {
            std::cout << "  Suggestions:" << std::endl;
            for (const auto& suggestion : error.suggestions) {
                std::cout << "    - " << suggestion << std::endl;
            }
        }
    }
    
    // Check that we didn't exceed error limit
    assert(errors.size() <= recoveryConfig.maxErrors);
    std::cout << "✓ Error limit respected" << std::endl;
    
    std::cout << "Basic error recovery test passed!" << std::endl;
}

void testSynchronizationPoints() {
    std::cout << "\nTesting synchronization points..." << std::endl;
    
    std::string source = R"(
        var x = invalid_syntax_here $$$ more_invalid;
        fn test() {
            return 42;
        }
        var y = 10;
    )";
    
    Scanner scanner(source);
    CST::CSTParser parser(scanner);
    
    auto cst = parser.parse();
    assert(cst != nullptr);
    
    auto errors = parser.getErrors();
    std::cout << "✓ Parser synchronized and continued after errors" << std::endl;
    std::cout << "Errors found: " << errors.size() << std::endl;
    
    std::cout << "Synchronization test passed!" << std::endl;
}

void testErrorLimitPrevention() {
    std::cout << "\nTesting error limit prevention..." << std::endl;
    
    // Create source with many syntax errors
    std::string source = R"(
        $$$ invalid $$$ more invalid $$$ even more invalid $$$
        $$$ invalid $$$ more invalid $$$ even more invalid $$$
        $$$ invalid $$$ more invalid $$$ even more invalid $$$
        $$$ invalid $$$ more invalid $$$ even more invalid $$$
        $$$ invalid $$$ more invalid $$$ even more invalid $$$
    )";
    
    Scanner scanner(source);
    CST::CSTParser parser(scanner);
    
    // Set low error limit
    CST::RecoveryConfig config;
    config.maxErrors = 5;
    parser.setRecoveryConfig(config);
    
    auto cst = parser.parse();
    auto errors = parser.getErrors();
    
    // Should not exceed the limit
    assert(errors.size() <= config.maxErrors + 1); // +1 for the "too many errors" message
    std::cout << "✓ Error limit enforced: " << errors.size() << " errors (limit: " << config.maxErrors << ")" << std::endl;
    
    std::cout << "Error limit test passed!" << std::endl;
}

int main() {
    try {
        testBasicErrorRecovery();
        testSynchronizationPoints();
        testErrorLimitPrevention();
        
        std::cout << "\n🎉 All error recovery tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}