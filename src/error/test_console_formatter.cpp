#include "console_formatter.hh"
#include "error_formatter.hh"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace ErrorHandling;

void testBasicErrorFormatting() {
    std::cout << "Testing basic error formatting..." << std::endl;
    
    // Create a basic error message
    ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace", 
                      "src/test.lm", 15, 5, "}", InterpretationStage::PARSING);
    
    // Format without colors for easier testing
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Check that it contains the expected components
    assert(formatted.find("error[E102][SyntaxError]: Unexpected closing brace") != std::string::npos);
    assert(formatted.find("--> src/test.lm:15:5") != std::string::npos);
    
    std::cout << "✓ Basic error formatting test passed" << std::endl;
}

void testErrorWithContext() {
    std::cout << "Testing error with source context..." << std::endl;
    
    // Create an error message with context
    ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace `}`", 
                      "src/test.lm", 15, 5, "}", InterpretationStage::PARSING);
    
    // Add some context lines (simulating SourceCodeFormatter output)
    error.contextLines = {
        "14 |     let x = 514",
        "15 |     return x + 1;",
        "15 | }",
        "   | ^ unexpected closing brace"
    };
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Check that context is included
    assert(formatted.find("14 |     let x = 514") != std::string::npos);
    assert(formatted.find("15 |     return x + 1;") != std::string::npos);
    assert(formatted.find("   | ^ unexpected closing brace") != std::string::npos);
    
    std::cout << "✓ Error with context test passed" << std::endl;
}

void testErrorWithHintAndSuggestion() {
    std::cout << "Testing error with hint and suggestion..." << std::endl;
    
    ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace `}`", 
                      "src/test.lm", 15, 5, "}", InterpretationStage::PARSING);
    
    error.hint = "It looks like you're missing an opening `{` before this line.";
    error.suggestion = "Did you forget to wrap a block like an `if`, `while`, or `function`?";
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Check that hint and suggestion are included
    assert(formatted.find("Hint: It looks like you're missing an opening") != std::string::npos);
    assert(formatted.find("Suggestion: Did you forget to wrap a block") != std::string::npos);
    
    std::cout << "✓ Error with hint and suggestion test passed" << std::endl;
}

void testErrorWithCausedBy() {
    std::cout << "Testing error with 'Caused by' information..." << std::endl;
    
    ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace `}`", 
                      "src/test.lm", 15, 5, "}", InterpretationStage::PARSING);
    
    error.causedBy = "Unterminated block starting at line 11:\n11 | function compute(x, y) =>\n   | ----------------------- unclosed block starts here";
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Check that "Caused by" section is included
    assert(formatted.find("Caused by: Unterminated block starting") != std::string::npos);
    assert(formatted.find("11 | function compute(x, y) =>") != std::string::npos);
    
    std::cout << "✓ Error with 'Caused by' test passed" << std::endl;
}

void testCompleteErrorMessage() {
    std::cout << "Testing complete error message with all components..." << std::endl;
    
    ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace `}`", 
                      "src/utils.calc", 15, 113, "}", InterpretationStage::PARSING);
    
    // Add all components
    error.contextLines = {
        "14 |     let x = 514",
        "15 |     return x + 1;",
        "15 | }",
        "   | ^ unexpected closing brace"
    };
    
    error.hint = "It looks like you're missing an opening `{` before this line.";
    error.suggestion = "Did you forget to wrap a block like an `if`, `while`, or `function`?";
    error.causedBy = "Unterminated block starting at line 11:\n11 | function compute(x, y) =>\n   | ----------------------- unclosed block starts here";
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    options.showFilePath = true;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Print the complete formatted message for visual inspection
    std::cout << "\nComplete formatted error message:\n";
    std::cout << "=====================================\n";
    std::cout << formatted;
    std::cout << "=====================================\n";
    
    // Check all components are present
    assert(formatted.find("error[E102][SyntaxError]") != std::string::npos);
    assert(formatted.find("--> src/utils.calc:15:113") != std::string::npos);
    assert(formatted.find("Hint:") != std::string::npos);
    assert(formatted.find("Suggestion:") != std::string::npos);
    assert(formatted.find("Caused by:") != std::string::npos);
    assert(formatted.find("File: src/utils.calc") != std::string::npos);
    
    std::cout << "✓ Complete error message test passed" << std::endl;
}

void testColorFormatting() {
    std::cout << "Testing color formatting..." << std::endl;
    
    ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace `}`", 
                      "src/test.lm", 15, 5, "}", InterpretationStage::PARSING);
    
    error.hint = "This is a hint";
    error.suggestion = "This is a suggestion";
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = true;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Check that ANSI color codes are present
    assert(formatted.find("\033[") != std::string::npos); // Should contain ANSI codes
    
    std::cout << "✓ Color formatting test passed" << std::endl;
}

void testMinimalErrorMessage() {
    std::cout << "Testing minimal error message..." << std::endl;
    
    // Create a minimal error with just the required fields
    ErrorMessage error("E001", "LexicalError", "Invalid character", 
                      "", 0, 0, "", InterpretationStage::SCANNING);
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Should still format properly even with minimal information
    assert(formatted.find("error[E001][LexicalError]: Invalid character") != std::string::npos);
    // Should not contain file location line since no file path
    assert(formatted.find("-->") == std::string::npos);
    
    std::cout << "✓ Minimal error message test passed" << std::endl;
}

void testTokenEscaping() {
    std::cout << "Testing token escaping..." << std::endl;
    
    // Test with special characters in token
    ErrorMessage error("E101", "SyntaxError", "Unexpected token", 
                      "src/test.lm", 5, 10, "\n", InterpretationStage::PARSING);
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    
    std::string formatted = ConsoleFormatter::formatErrorMessage(error, options);
    
    // Should escape the newline character
    assert(formatted.find("\\n") != std::string::npos);
    
    std::cout << "✓ Token escaping test passed" << std::endl;
}

void testStreamOutput() {
    std::cout << "Testing stream output..." << std::endl;
    
    ErrorMessage error("E102", "SyntaxError", "Test error", 
                      "src/test.lm", 10, 5, "test", InterpretationStage::PARSING);
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = false;
    
    std::ostringstream stream;
    ConsoleFormatter::writeErrorMessage(stream, error, options);
    
    std::string output = stream.str();
    assert(output.find("error[E102][SyntaxError]: Test error") != std::string::npos);
    
    std::cout << "✓ Stream output test passed" << std::endl;
}

int main() {
    std::cout << "Running ConsoleFormatter tests...\n" << std::endl;
    
    try {
        testBasicErrorFormatting();
        testErrorWithContext();
        testErrorWithHintAndSuggestion();
        testErrorWithCausedBy();
        testCompleteErrorMessage();
        testColorFormatting();
        testMinimalErrorMessage();
        testTokenEscaping();
        testStreamOutput();
        
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