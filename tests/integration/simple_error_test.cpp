#include "../../src/common/debugger.hh"
#include <iostream>

int main() {
    std::cout << "Testing basic error reporting..." << std::endl;
    
    // Reset error state
    Debugger::resetError();
    
    // Test basic error reporting
    Debugger::error("Test error message", 10, 5, InterpretationStage::PARSING, "test code", "test.lm", "token", "expected");
    
    // Check that error was reported
    if (Debugger::hasError()) {
        std::cout << "✓ Error reporting works correctly" << std::endl;
        return 0;
    } else {
        std::cout << "✗ Error reporting failed" << std::endl;
        return 1;
    }
}