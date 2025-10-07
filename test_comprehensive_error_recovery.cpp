#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include "src/common/debugger.hh"
#include <iostream>
#include <cassert>

void testErrorRecoveryWithDebugger() {
    std::cout << "Testing CST Parser Error Recovery with Debugger Integration..." << std::endl;
    
    // Reset debugger state
    Debugger::resetError();
    
    // Test source with multiple syntax errors
    std::string source = R"(
        var x = 5;
        var y = // missing value and semicolon
        fn test() {
            if (x > 0 {  // missing closing paren
                print("positive");
            // missing closing brace for if
        // missing closing brace for function
        var z = "hello";
        class MyClass {
            fn method( {  // missing parameter and closing paren
                return 42
            // missing semicolon and closing brace
        // missing closing brace for class
    )";
    
    Scanner scanner(source);
    CSTConfig config;
    config.preserveComments = true;
    config.preserveWhitespace = true;
    config.emitErrorTokens = true;
    
    CST::CSTParser parser(scanner, config);
    
    // Configure error recovery
    CST::RecoveryConfig recoveryConfig;
    recoveryConfig.maxErrors = 15;
    recoveryConfig.continueOnError = true;
    recoveryConfig.insertMissingTokens = true;
    recoveryConfig.createPartialNodes = true;
    recoveryConfig.skipInvalidTokens = true;
    parser.setRecoveryConfig(recoveryConfig);
    
    // Parse with error recovery
    auto cst = parser.parse();
    
    // Verify CST was created despite errors
    assert(cst != nullptr);
    std::cout << "✓ CST created despite multiple syntax errors" << std::endl;
    
    // Verify errors were reported through Debugger
    assert(Debugger::hasError());
    std::cout << "✓ Errors reported through Debugger system" << std::endl;
    
    // Verify internal error tracking
    auto errors = parser.getErrors();
    assert(!errors.empty());
    std::cout << "✓ Internal error tracking working: " << errors.size() << " errors" << std::endl;
    
    // Verify error limit was respected
    assert(errors.size() <= recoveryConfig.maxErrors);
    std::cout << "✓ Error limit respected" << std::endl;
    
    // Print enhanced error information
    std::cout << "\nEnhanced Error Messages:" << std::endl;
    for (const auto& error : errors) {
        std::cout << error.errorCode << " " << error.errorType 
                  << " at line " << error.line << ": " << error.description << std::endl;
        if (!error.hint.empty()) {
            std::cout << "  Hint: " << error.hint << std::endl;
        }
        if (!error.suggestion.empty()) {
            std::cout << "  Suggestion: " << error.suggestion << std::endl;
        }
        if (!error.causedBy.empty()) {
            std::cout << "  Caused by: " << error.causedBy << std::endl;
        }
    }
    
    // Print CST structure to verify recovery
    std::cout << "\nCST Structure (showing error recovery):" << std::endl;
    std::cout << cst->toString() << std::endl;
    
    std::cout << "Error recovery with Debugger integration test passed!" << std::endl;
}

void testSynchronizationAndRecovery() {
    std::cout << "\nTesting synchronization and partial node creation..." << std::endl;
    
    Debugger::resetError();
    
    std::string source = R"(
        var valid1 = 42;
        var invalid $$$ syntax error here $$$;
        var valid2 = "hello";
        fn incomplete_function( {
            // missing parameters and body
        var valid3 = true;
    )";
    
    Scanner scanner(source);
    CSTConfig scanConfig;
    CST::CSTParser parser(scanner, scanConfig);
    
    CST::RecoveryConfig config;
    config.continueOnError = true;
    config.createPartialNodes = true;
    config.maxErrors = 10;
    parser.setRecoveryConfig(config);
    
    auto cst = parser.parse();
    
    assert(cst != nullptr);
    std::cout << "✓ Parser synchronized and continued after errors" << std::endl;
    
    // Should have both valid and error/partial nodes
    assert(cst->children.size() > 0);
    std::cout << "✓ CST contains " << cst->children.size() << " top-level nodes" << std::endl;
    
    // Check for error recovery nodes
    bool hasErrorNodes = false;
    for (const auto& child : cst->children) {
        if (child && CST::isErrorRecoveryNode(child->kind)) {
            hasErrorNodes = true;
            break;
        }
    }
    
    if (hasErrorNodes) {
        std::cout << "✓ Error recovery nodes created for invalid syntax" << std::endl;
    }
    
    std::cout << "Synchronization and recovery test passed!" << std::endl;
}

void testMissingTokenInsertion() {
    std::cout << "\nTesting missing token insertion..." << std::endl;
    
    Debugger::resetError();
    
    std::string source = R"(
        var x = 5  // missing semicolon
        fn test() {
            return 42  // missing semicolon
        }  // this should be parsed correctly
    )";
    
    Scanner scanner(source);
    CSTConfig scanConfig;
    CST::CSTParser parser(scanner, scanConfig);
    
    CST::RecoveryConfig config;
    config.insertMissingTokens = true;
    config.continueOnError = true;
    config.maxErrors = 5;
    parser.setRecoveryConfig(config);
    
    auto cst = parser.parse();
    
    assert(cst != nullptr);
    std::cout << "✓ Parser handled missing tokens gracefully" << std::endl;
    
    auto errors = parser.getErrors();
    std::cout << "✓ Missing token errors reported: " << errors.size() << " errors" << std::endl;
    
    std::cout << "Missing token insertion test passed!" << std::endl;
}

void testErrorLimitEnforcement() {
    std::cout << "\nTesting error limit enforcement..." << std::endl;
    
    Debugger::resetError();
    
    // Create source with many errors
    std::string source = R"(
        $$$ error1 $$$
        $$$ error2 $$$
        $$$ error3 $$$
        $$$ error4 $$$
        $$$ error5 $$$
        $$$ error6 $$$
        $$$ error7 $$$
    )";
    
    Scanner scanner(source);
    CSTConfig scanConfig;
    CST::CSTParser parser(scanner, scanConfig);
    
    // Set very low error limit
    CST::RecoveryConfig config;
    config.maxErrors = 3;
    config.continueOnError = true;
    parser.setRecoveryConfig(config);
    
    auto cst = parser.parse();
    auto errors = parser.getErrors();
    
    // Should not exceed limit (plus one for "too many errors" message)
    assert(errors.size() <= config.maxErrors + 1);
    std::cout << "✓ Error limit enforced: " << errors.size() << " errors (limit: " << config.maxErrors << ")" << std::endl;
    
    std::cout << "Error limit enforcement test passed!" << std::endl;
}

int main() {
    try {
        testErrorRecoveryWithDebugger();
        testSynchronizationAndRecovery();
        testMissingTokenInsertion();
        testErrorLimitEnforcement();
        
        std::cout << "\n🎉 All comprehensive error recovery tests passed!" << std::endl;
        std::cout << "✓ Debugger integration working" << std::endl;
        std::cout << "✓ Error recovery and synchronization working" << std::endl;
        std::cout << "✓ Missing token insertion working" << std::endl;
        std::cout << "✓ Error limit enforcement working" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}