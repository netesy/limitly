#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include "../../src/frontend/scanner.hh"
#include "../../src/frontend/parser.hh"
#include "../../src/common/backend.hh"
#include "../../src/backend/vm.hh"
#include "../../src/common/debugger.hh"
#include "../../src/error/error_formatter.hh"
#include "../../src/error/console_formatter.hh"

// Test helper to capture error output
class ErrorCapture {
private:
    std::stringstream capturedOutput;
    std::streambuf* originalCerr;
    
public:
    ErrorCapture() {
        originalCerr = std::cerr.rdbuf();
        std::cerr.rdbuf(capturedOutput.rdbuf());
    }
    
    ~ErrorCapture() {
        std::cerr.rdbuf(originalCerr);
    }
    
    std::string getCapturedOutput() const {
        return capturedOutput.str();
    }
    
    void clear() {
        capturedOutput.str("");
        capturedOutput.clear();
    }
};

// Test cases for enhanced error reporting
struct ErrorTestCase {
    std::string name;
    std::string code;
    std::string expectedErrorPattern;
    std::string expectedHintPattern;
    std::string expectedSuggestionPattern;
    InterpretationStage expectedStage;
};

std::vector<ErrorTestCase> getTestCases() {
    return {
        // Lexical errors
        {
            "Invalid character",
            "var x = 5; @invalid",
            "error\\[E\\d+\\]\\[.*Error\\].*Invalid character",
            "character is not recognized",
            "Remove the invalid character"
        },
        
        // Syntax errors
        {
            "Missing semicolon",
            "var x = 5\nvar y = 10;",
            "error\\[E\\d+\\]\\[.*Error\\].*semicolon",
            "statements must end with a semicolon",
            "Add a semicolon"
        },
        
        {
            "Unexpected closing brace",
            "var x = 5; }",
            "error\\[E\\d+\\]\\[.*Error\\].*closing brace",
            "doesn't have a matching opening brace",
            "remove this extra"
        },
        
        // Semantic errors
        {
            "Undefined variable",
            "var x = undefinedVar;",
            "error\\[E\\d+\\]\\[.*Error\\].*Undefined variable",
            "Variables must be declared before",
            "Check the spelling.*or declare it"
        },
        
        {
            "Type mismatch",
            "var x: int = \"string\";",
            "error\\[E\\d+\\]\\[.*Error\\].*Type mismatch",
            "strong type system",
            "cannot assign"
        },
        
        // Runtime errors
        {
            "Division by zero",
            "var x = 5 / 0;",
            "error\\[E\\d+\\]\\[.*Error\\].*Division by zero",
            "mathematically undefined",
            "Add a check.*divisor != 0"
        },
        
        {
            "Modulo by zero",
            "var x = 5 % 0;",
            "error\\[E\\d+\\]\\[.*Error\\].*Modulo by zero",
            "mathematically undefined",
            "Add a check.*divisor != 0"
        }
    };
}

bool testErrorReporting(const ErrorTestCase& testCase) {
    std::cout << "Testing: " << testCase.name << std::endl;
    
    // Reset error state
    Debugger::resetError();
    
    // Capture error output
    ErrorCapture capture;
    
    try {
        // Create scanner and parser
        Scanner scanner(testCase.code);
        std::vector<Token> tokens = scanner.scanTokens();
        
        Parser parser(tokens);
        auto program = parser.parse();
        
        if (program) {
            // Create bytecode generator
            BytecodeGenerator generator;
            generator.setSourceContext(testCase.code, "test.lm");
            generator.process(program);
            
            // Create VM and execute
            VM vm;
            vm.setSourceContext(testCase.code, "test.lm");
            auto result = vm.execute(generator.getBytecode());
        }
    } catch (const std::exception& e) {
        // Expected for some test cases
    }
    
    std::string errorOutput = capture.getCapturedOutput();
    
    // Check if error was captured
    if (errorOutput.empty()) {
        std::cout << "  FAIL: No error output captured" << std::endl;
        return false;
    }
    
    std::cout << "  Captured output: " << errorOutput.substr(0, 200) << "..." << std::endl;
    
    // Basic validation - check for enhanced error format
    bool hasErrorCode = errorOutput.find("error[E") != std::string::npos;
    bool hasFilePath = errorOutput.find("test.lm") != std::string::npos;
    bool hasLineNumber = errorOutput.find("-->") != std::string::npos;
    bool hasSourceContext = errorOutput.find("|") != std::string::npos;
    
    if (!hasErrorCode) {
        std::cout << "  FAIL: Missing error code format" << std::endl;
        return false;
    }
    
    if (!hasFilePath) {
        std::cout << "  FAIL: Missing file path" << std::endl;
        return false;
    }
    
    if (!hasLineNumber) {
        std::cout << "  FAIL: Missing line number format" << std::endl;
        return false;
    }
    
    if (!hasSourceContext) {
        std::cout << "  FAIL: Missing source context" << std::endl;
        return false;
    }
    
    std::cout << "  PASS: Enhanced error format detected" << std::endl;
    return true;
}

bool testSpecificErrorTypes() {
    std::cout << "\n=== Testing Specific Error Types ===" << std::endl;
    
    int passed = 0;
    int total = 0;
    
    auto testCases = getTestCases();
    for (const auto& testCase : testCases) {
        total++;
        if (testErrorReporting(testCase)) {
            passed++;
        }
        std::cout << std::endl;
    }
    
    std::cout << "Results: " << passed << "/" << total << " tests passed" << std::endl;
    return passed == total;
}

bool testErrorMessageComponents() {
    std::cout << "\n=== Testing Error Message Components ===" << std::endl;
    
    // Test that error messages contain all required components
    Debugger::resetError();
    ErrorCapture capture;
    
    // Generate a simple error
    std::string code = "var x = undefinedVariable;";
    std::string filePath = "test_components.lm";
    
    try {
        Scanner scanner(code);
        std::vector<Token> tokens = scanner.scanTokens();
        
        Parser parser(tokens);
        auto program = parser.parse();
        
        if (program) {
            BytecodeGenerator generator;
            generator.setSourceContext(code, filePath);
            generator.process(program);
            
            VM vm;
            vm.setSourceContext(code, filePath);
            auto result = vm.execute(generator.getBytecode());
        }
    } catch (const std::exception& e) {
        // Expected
    }
    
    std::string output = capture.getCapturedOutput();
    
    // Check for all required components
    std::vector<std::string> requiredComponents = {
        "error[E",           // Error code
        "][",                // Error type bracket
        "-->",               // File location indicator
        "test_components.lm", // File path
        "|",                 // Source context line indicator
        "Hint:",             // Hint section
        "Suggestion:"        // Suggestion section
    };
    
    bool allPresent = true;
    for (const auto& component : requiredComponents) {
        if (output.find(component) == std::string::npos) {
            std::cout << "  FAIL: Missing component: " << component << std::endl;
            allPresent = false;
        }
    }
    
    if (allPresent) {
        std::cout << "  PASS: All required components present" << std::endl;
    }
    
    return allPresent;
}

bool testContextualHints() {
    std::cout << "\n=== Testing Contextual Hints ===" << std::endl;
    
    // Test that contextual hints are being generated
    Debugger::resetError();
    ErrorCapture capture;
    
    // Test division by zero hint
    std::string code = "var result = 10 / 0;";
    
    try {
        Scanner scanner(code);
        std::vector<Token> tokens = scanner.scanTokens();
        
        Parser parser(tokens);
        auto program = parser.parse();
        
        if (program) {
            BytecodeGenerator generator;
            generator.setSourceContext(code, "test_hints.lm");
            generator.process(program);
            
            VM vm;
            vm.setSourceContext(code, "test_hints.lm");
            auto result = vm.execute(generator.getBytecode());
        }
    } catch (const std::exception& e) {
        // Expected
    }
    
    std::string output = capture.getCapturedOutput();
    
    // Check for specific hint content
    bool hasHint = output.find("Hint:") != std::string::npos;
    bool hasSuggestion = output.find("Suggestion:") != std::string::npos;
    bool hasRelevantContent = output.find("divisor") != std::string::npos || 
                             output.find("zero") != std::string::npos;
    
    if (hasHint && hasSuggestion && hasRelevantContent) {
        std::cout << "  PASS: Contextual hints generated" << std::endl;
        return true;
    } else {
        std::cout << "  FAIL: Missing contextual hints" << std::endl;
        std::cout << "  Has hint: " << hasHint << std::endl;
        std::cout << "  Has suggestion: " << hasSuggestion << std::endl;
        std::cout << "  Has relevant content: " << hasRelevantContent << std::endl;
        return false;
    }
}

int main() {
    std::cout << "Enhanced Error Reporting Integration Tests" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    bool allPassed = true;
    
    // Test specific error types
    if (!testSpecificErrorTypes()) {
        allPassed = false;
    }
    
    // Test error message components
    if (!testErrorMessageComponents()) {
        allPassed = false;
    }
    
    // Test contextual hints
    if (!testContextualHints()) {
        allPassed = false;
    }
    
    std::cout << "\n=== Final Results ===" << std::endl;
    if (allPassed) {
        std::cout << "ALL TESTS PASSED: Enhanced error reporting is working correctly" << std::endl;
        return 0;
    } else {
        std::cout << "SOME TESTS FAILED: Enhanced error reporting needs fixes" << std::endl;
        return 1;
    }
}