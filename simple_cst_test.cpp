#include "src/frontend/cst_parser.hh"
#include "src/frontend/scanner.hh"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Simple CST Statement Parsing Test ===" << std::endl;
    
    // Test source with error recovery scenarios
    std::string source = R"(
        // Valid variable declaration
        var x: int = 42;
        
        // Variable declaration with missing semicolon
        var y: str = "hello"
        
        // Function with missing parameter list
        fn broken_func {
            return 1;
        }
        
        // If statement with missing condition
        if () {
            var z: int = 1;
        }
        
        // For loop with missing parts
        for (;;) {
            break;
        }
        
        // Iter statement
        iter (i in 1..10) {
            var temp: int = i;
        }
        
        // Match statement
        match (x) {
            1 => var a: int = 1;
            default => var b: int = 2;
        }
        
        // Class declaration
        class Person {
            var name: str;
        }
        
        // Type declaration
        type UserId = int;
        
        // Trait declaration
        trait Drawable {
            fn draw();
        }
    )";
    
    try {
        // Create scanner
        Scanner scanner(source);
        
        // Create CST parser with basic configuration
        CSTConfig config;
        config.preserveWhitespace = false;  // Simplified for testing
        config.preserveComments = false;
        config.emitErrorTokens = true;
        
        CST::CSTParser parser(scanner, config);
        
        // Configure error recovery
        CST::RecoveryConfig recoveryConfig;
        recoveryConfig.continueOnError = true;
        recoveryConfig.insertMissingTokens = true;
        recoveryConfig.createPartialNodes = true;
        recoveryConfig.maxErrors = 10;
        parser.setRecoveryConfig(recoveryConfig);
        
        // Parse to CST
        std::cout << "Parsing source..." << std::endl;
        auto cst = parser.parse();
        
        std::cout << "Parse completed!" << std::endl;
        std::cout << "Errors found: " << parser.getErrorCount() << std::endl;
        std::cout << "CST created: " << (cst ? "Yes" : "No") << std::endl;
        
        if (parser.hasErrors()) {
            std::cout << "\nErrors:" << std::endl;
            for (const auto& error : parser.getErrors()) {
                std::cout << "  Line " << error.line << ": " << error.message << std::endl;
            }
        }
        
        if (cst) {
            std::cout << "\nCST Root: " << cst->getKindName() << std::endl;
            std::cout << "Children: " << cst->children.size() << std::endl;
            std::cout << "Tokens: " << cst->tokens.size() << std::endl;
        }
        
        std::cout << "\n=== Test Completed Successfully ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}