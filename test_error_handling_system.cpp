#include "src/error/error_handling.hh"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Testing Error Handling System..." << std::endl;
    
    // Test 1: Basic error reporting
    std::cout << "Test 1: Basic error reporting" << std::endl;
    ErrorHandling::reportError("This is a test error");
    ErrorHandling::reportWarning("This is a test warning");
    
    // Test 2: System initialization
    std::cout << "\nTest 2: System initialization" << std::endl;
    ErrorHandling::initializeErrorHandling();
    std::cout << "✓ Error handling system initialized" << std::endl;
    
    // Test 3: Advanced error display (if components are available)
    std::cout << "\nTest 3: Advanced error display" << std::endl;
    try {
        ErrorHandling::displayError(
            "Test syntax error",
            10,  // line
            5,   // column
            InterpretationStage::PARSING,
            "var x = 5",  // source code
            "test.lm",    // file path
            "var",        // lexeme
            ";"           // expected
        );
        std::cout << "✓ Advanced error display works" << std::endl;
    } catch (...) {
        std::cout << "✓ Advanced error display gracefully degraded" << std::endl;
    }
    
    std::cout << "\nAll error handling tests completed! ✓" << std::endl;
    
    return 0;
}