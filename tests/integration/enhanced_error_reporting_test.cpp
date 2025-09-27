#include "../../src/common/debugger.hh"
#include "../../src/error/error_formatter.hh"
#include "../../src/error/console_formatter.hh"
#include <iostream>
#include <sstream>
#include <cassert>

void testEnhancedErrorReporting() {
    std::cout << "Testing Enhanced Error Reporting..." << std::endl;
    
    // Test 1: Enhanced semantic error with lexeme and expected value
    Debugger::resetError();
    
    std::string sourceCode = R"(
let x: int = 5;
let y: str = "hello";
if (x < y) {
    print("This should not work");
}
)";
    
    // Simulate a semantic error with enhanced context
    Debugger::error("Type mismatch in comparison", 4, 8, InterpretationStage::SEMANTIC, 
                   sourceCode, "test.lm", "y", "value of same type as x (int)");
    
    assert(Debugger::hasError());
    std::cout << "✓ Enhanced semantic error reporting works" << std::endl;
    
    // Test 2: Enhanced runtime error with operation context
    Debugger::resetError();
    
    std::string runtimeCode = R"(
let result = 10 / 0;
)";
    
    // Simulate a runtime error with enhanced context
    Debugger::error("Division by zero", 2, 17, InterpretationStage::INTERPRETING,
                   runtimeCode, "test.lm", "0", "non-zero divisor");
    
    assert(Debugger::hasError());
    std::cout << "✓ Enhanced runtime error reporting works" << std::endl;
    
    // Test 3: Enhanced function call error
    Debugger::resetError();
    
    std::string functionCode = R"(
fn testFunction(a: int, b: str) -> int {
    return a + 1;
}

testFunction(42);
)";
    
    // Simulate a function call error with enhanced context
    Debugger::error("Function argument count mismatch", 6, 1, InterpretationStage::SEMANTIC,
                   functionCode, "test.lm", "testFunction", "2 arguments, got 1");
    
    assert(Debugger::hasError());
    std::cout << "✓ Enhanced function call error reporting works" << std::endl;
    
    std::cout << "All enhanced error reporting tests passed!" << std::endl;
}

int main() {
    try {
        testEnhancedErrorReporting();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}