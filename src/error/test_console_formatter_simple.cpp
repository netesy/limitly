#include "console_formatter.hh"
#include <iostream>
#include <cassert>

using namespace ErrorHandling;

int main() {
    std::cout << "Running simple ConsoleFormatter tests...\n" << std::endl;
    
    try {
        // Test 1: Basic error message formatting
        std::cout << "Test 1: Basic error message formatting..." << std::endl;
        
        ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace `}`", 
                          "src/test.lm", 15, 5, "}", InterpretationStage::PARSING);
        
        ConsoleFormatter::ConsoleOptions options;
        options.useColors = false;
        
        std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
        
        // Check basic components
        assert(formatted.find("error[E102][SyntaxError]: Unexpected closing brace") != std::string::npos);
        assert(formatted.find("--> src/test.lm:15:5") != std::string::npos);
        
        std::cout << "✓ Basic formatting test passed" << std::endl;
        
        // Test 2: Error with hint and suggestion
        std::cout << "\nTest 2: Error with hint and suggestion..." << std::endl;
        
        error.hint = "It looks like you're missing an opening `{` before this line.";
        error.suggestion = "Did you forget to wrap a block like an `if`, `while`, or `function`?";
        
        formatted = ConsoleFormatter::formatErrorMessage(error, options);
        
        assert(formatted.find("Hint: It looks like you're missing") != std::string::npos);
        assert(formatted.find("Suggestion: Did you forget to wrap") != std::string::npos);
        
        std::cout << "✓ Hint and suggestion test passed" << std::endl;
        
        // Test 3: Complete error message display
        std::cout << "\nTest 3: Complete error message display..." << std::endl;
        
        // Add context lines
        error.contextLines = {
            "14 |     let x = 514",
            "15 |     return x + 1;",
            "15 | }",
            "   | ^ unexpected closing brace"
        };
        
        // Add caused by information
        error.causedBy = "Unterminated block starting at line 11:\n11 | function compute(x, y) =>\n   | ----------------------- unclosed block starts here";
        
        formatted = ConsoleFormatter::formatErrorMessage(error, options);
        
        std::cout << "\nComplete formatted error message:\n";
        std::cout << "=====================================\n";
        std::cout << formatted;
        std::cout << "=====================================\n";
        
        // Verify all components are present
        assert(formatted.find("error[E102][SyntaxError]") != std::string::npos);
        assert(formatted.find("--> src/test.lm:15:5") != std::string::npos);
        assert(formatted.find("14 |     let x = 514") != std::string::npos);
        assert(formatted.find("Hint:") != std::string::npos);
        assert(formatted.find("Suggestion:") != std::string::npos);
        assert(formatted.find("Caused by:") != std::string::npos);
        
        std::cout << "✓ Complete error message test passed" << std::endl;
        
        // Test 4: Color formatting
        std::cout << "\nTest 4: Color formatting..." << std::endl;
        
        options.useColors = true;
        formatted = ConsoleFormatter::formatErrorMessage(error, options);
        
        // Should contain ANSI color codes
        assert(formatted.find("\033[") != std::string::npos);
        
        std::cout << "✓ Color formatting test passed" << std::endl;
        
        // Test 5: Minimal error message
        std::cout << "\nTest 5: Minimal error message..." << std::endl;
        
        ErrorMessage minimalError("E001", "LexicalError", "Invalid character", 
                                 "", 0, 0, "", InterpretationStage::SCANNING);
        
        options.useColors = false;
        formatted = ConsoleFormatter::formatErrorMessage(minimalError, options);
        
        assert(formatted.find("error[E001][LexicalError]: Invalid character") != std::string::npos);
        // Should not contain file location since no file path
        assert(formatted.find("-->") == std::string::npos);
        
        std::cout << "✓ Minimal error message test passed" << std::endl;
        
        std::cout << "\n✅ All ConsoleFormatter tests passed!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
}