#include "../../src/error_formatter.hh"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace ErrorHandling;

// Test helper functions
void testBasicErrorMessageCreation();
void testErrorMessageWithSourceContext();
void testErrorMessageWithBlockContext();
void testErrorMessageWithAllEnhancements();
void testMinimalErrorMessage();
void testErrorTypeSpecificHandling();
void testFormatterOptions();
void testInitialization();
void testIntegrationWithAllComponents();

// Helper function to create sample source code
std::string createSampleSourceCode() {
    return R"(fn main() {
    let x: int = 42;
    let y: int = 0;
    
    if (x > 0) {
        print("x is positive");
        let result = x / y;
    }
    
    return 0;
})";
}

// Helper function to print error message details
void printErrorMessage(const ErrorMessage& error) {
    std::cout << "Error Code: " << error.errorCode << std::endl;
    std::cout << "Error Type: " << error.errorType << std::endl;
    std::cout << "Description: " << error.description << std::endl;
    std::cout << "File: " << error.filePath << std::endl;
    std::cout << "Location: " << error.line << ":" << error.column << std::endl;
    std::cout << "Token: " << error.problematicToken << std::endl;
    
    if (!error.hint.empty()) {
        std::cout << "Hint: " << error.hint << std::endl;
    }
    
    if (!error.suggestion.empty()) {
        std::cout << "Suggestion: " << error.suggestion << std::endl;
    }
    
    if (!error.causedBy.empty()) {
        std::cout << "Caused by: " << error.causedBy << std::endl;
    }
    
    if (!error.contextLines.empty()) {
        std::cout << "Context:" << std::endl;
        for (const auto& line : error.contextLines) {
            std::cout << line << std::endl;
        }
    }
    
    std::cout << "---" << std::endl;
}

int main() {
    std::cout << "Testing ErrorFormatter Integration..." << std::endl;
    
    try {
        testInitialization();
        testBasicErrorMessageCreation();
        testErrorMessageWithSourceContext();
        testErrorMessageWithBlockContext();
        testErrorMessageWithAllEnhancements();
        testMinimalErrorMessage();
        testErrorTypeSpecificHandling();
        testFormatterOptions();
        testIntegrationWithAllComponents();
        
        std::cout << "All ErrorFormatter integration tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}

void testInitialization() {
    std::cout << "Testing initialization..." << std::endl;
    
    // Test that initialization works
    ErrorFormatter::initialize();
    assert(ErrorFormatter::isInitialized());
    
    // Test that multiple initializations are safe
    ErrorFormatter::initialize();
    assert(ErrorFormatter::isInitialized());
    
    std::cout << "Initialization test passed." << std::endl;
}

void testBasicErrorMessageCreation() {
    std::cout << "Testing basic error message creation..." << std::endl;
    
    ErrorMessage error = ErrorFormatter::createErrorMessage(
        "Unexpected token '}'",
        5, 10,
        InterpretationStage::PARSING,
        "",  // No source code
        "}",
        "{",
        "test.lm"
    );
    
    // Verify basic fields are populated
    assert(!error.errorCode.empty());
    assert(!error.errorType.empty());
    assert(error.description == "Unexpected token '}'");
    assert(error.filePath == "test.lm");
    assert(error.line == 5);
    assert(error.column == 10);
    assert(error.problematicToken == "}");
    assert(error.stage == InterpretationStage::PARSING);
    assert(error.isComplete());
    
    // Should have error code in E100-E199 range for parsing errors
    assert(error.errorCode[0] == 'E');
    int codeNum = std::stoi(error.errorCode.substr(1));
    assert(codeNum >= 100 && codeNum <= 199);
    
    std::cout << "Basic error message creation test passed." << std::endl;
}

void testErrorMessageWithSourceContext() {
    std::cout << "Testing error message with source context..." << std::endl;
    
    std::string sourceCode = createSampleSourceCode();
    
    ErrorMessage error = ErrorFormatter::createErrorMessage(
        "Division by zero",
        7, 21,
        InterpretationStage::INTERPRETING,
        sourceCode,
        "/",
        "",
        "test.lm"
    );
    
    // Verify source context is included
    assert(!error.contextLines.empty());
    assert(error.hasEnhancedInfo());
    
    // Should have runtime error code (E400-E499)
    int codeNum = std::stoi(error.errorCode.substr(1));
    assert(codeNum >= 400 && codeNum <= 499);
    
    // Should have hint and suggestion for division by zero
    assert(!error.hint.empty());
    assert(!error.suggestion.empty());
    
    printErrorMessage(error);
    
    std::cout << "Source context test passed." << std::endl;
}

void testErrorMessageWithBlockContext() {
    std::cout << "Testing error message with block context..." << std::endl;
    
    std::string sourceCode = R"(fn compute(x: int) {
    if (x > 0) {
        return x * 2;
    // Missing closing brace for if block
    return -1;
})";
    
    BlockContext blockContext("if", 2, 5, "if (x > 0) {");
    
    ErrorMessage error = ErrorFormatter::createErrorMessage(
        "Unexpected closing brace '}'",
        6, 1,
        InterpretationStage::PARSING,
        sourceCode,
        "}",
        "",
        "test.lm",
        blockContext
    );
    
    // Verify block context generates "Caused by" message
    assert(!error.causedBy.empty());
    assert(error.causedBy.find("Caused by") != std::string::npos);
    assert(error.causedBy.find("if") != std::string::npos);
    assert(error.causedBy.find("line 2") != std::string::npos);
    
    printErrorMessage(error);
    
    std::cout << "Block context test passed." << std::endl;
}

void testErrorMessageWithAllEnhancements() {
    std::cout << "Testing error message with all enhancements..." << std::endl;
    
    std::string sourceCode = R"(fn main() {
    let x: int = 42;
    let undefinedVar = someUndefinedFunction();
    return 0;
})";
    
    ErrorMessage error = ErrorFormatter::createErrorMessage(
        "Undefined function 'someUndefinedFunction'",
        3, 20,
        InterpretationStage::SEMANTIC,
        sourceCode,
        "someUndefinedFunction",
        "",
        "test.lm"
    );
    
    // Verify all enhancements are present
    assert(!error.errorCode.empty());
    assert(!error.errorType.empty());
    assert(!error.hint.empty());
    assert(!error.suggestion.empty());
    assert(!error.contextLines.empty());
    assert(error.hasEnhancedInfo());
    
    // Should have semantic error code (E200-E299)
    int codeNum = std::stoi(error.errorCode.substr(1));
    assert(codeNum >= 200 && codeNum <= 299);
    
    // Verify hint mentions function definition
    assert(error.hint.find("function") != std::string::npos || 
           error.hint.find("defined") != std::string::npos);
    
    // Verify suggestion mentions the function name
    assert(error.suggestion.find("someUndefinedFunction") != std::string::npos);
    
    printErrorMessage(error);
    
    std::cout << "All enhancements test passed." << std::endl;
}

void testMinimalErrorMessage() {
    std::cout << "Testing minimal error message..." << std::endl;
    
    ErrorMessage error = ErrorFormatter::createMinimalErrorMessage(
        "Compilation failed",
        InterpretationStage::COMPILING,
        "project.lm",
        0, 0
    );
    
    // Verify minimal fields are populated
    assert(!error.errorCode.empty());
    assert(!error.errorType.empty());
    assert(error.description == "Compilation failed");
    assert(error.filePath == "project.lm");
    assert(error.stage == InterpretationStage::COMPILING);
    
    // Should have compilation error code (E600-E699)
    int codeNum = std::stoi(error.errorCode.substr(1));
    assert(codeNum >= 600 && codeNum <= 699);
    
    // Minimal message should not have enhanced info
    assert(error.hint.empty());
    assert(error.suggestion.empty());
    assert(error.causedBy.empty());
    assert(error.contextLines.empty());
    
    std::cout << "Minimal error message test passed." << std::endl;
}

void testErrorTypeSpecificHandling() {
    std::cout << "Testing error type specific handling..." << std::endl;
    
    // Test lexical error
    ErrorMessage lexicalError = ErrorFormatter::createErrorMessage(
        "Invalid character '@'",
        1, 5,
        InterpretationStage::SCANNING,
        "let @ = 42;",
        "@",
        "",
        "test.lm"
    );
    
    // Should have lexical error code (E001-E099)
    int lexicalCodeNum = std::stoi(lexicalError.errorCode.substr(1));
    assert(lexicalCodeNum >= 1 && lexicalCodeNum <= 99);
    assert(lexicalError.errorType == "LexicalError");
    
    // Test syntax error with token extraction
    ErrorMessage syntaxError = ErrorFormatter::createErrorMessage(
        "Expected ';' but found '}'",
        3, 8,
        InterpretationStage::PARSING,
        "let x = 42\n}",
        "",  // Empty lexeme - should be extracted from message
        ";",
        "test.lm"
    );
    
    // Should have syntax error code (E100-E199)
    int syntaxCodeNum = std::stoi(syntaxError.errorCode.substr(1));
    assert(syntaxCodeNum >= 100 && syntaxCodeNum <= 199);
    assert(syntaxError.errorType == "SyntaxError");
    
    std::cout << "Error type specific handling test passed." << std::endl;
}

void testFormatterOptions() {
    std::cout << "Testing formatter options..." << std::endl;
    
    std::string sourceCode = createSampleSourceCode();
    
    // Test with all options disabled
    ErrorFormatter::FormatterOptions options;
    options.generateHints = false;
    options.generateSuggestions = false;
    options.includeSourceContext = false;
    options.generateCausedBy = false;
    
    ErrorMessage error = ErrorFormatter::createErrorMessage(
        "Division by zero",
        7, 21,
        InterpretationStage::INTERPRETING,
        sourceCode,
        "/",
        "",
        "test.lm",
        std::nullopt,
        options
    );
    
    // Verify enhancements are disabled
    assert(error.hint.empty());
    assert(error.suggestion.empty());
    assert(error.causedBy.empty());
    assert(error.contextLines.empty());
    
    // Test with custom context lines
    ErrorFormatter::FormatterOptions contextOptions;
    contextOptions.contextLinesBefore = 1;
    contextOptions.contextLinesAfter = 1;
    
    ErrorMessage contextError = ErrorFormatter::createErrorMessage(
        "Division by zero",
        7, 21,
        InterpretationStage::INTERPRETING,
        sourceCode,
        "/",
        "",
        "test.lm",
        std::nullopt,
        contextOptions
    );
    
    // Should have limited context lines
    assert(!contextError.contextLines.empty());
    // Context should be limited (exact count depends on formatting)
    
    std::cout << "Formatter options test passed." << std::endl;
}

void testIntegrationWithAllComponents() {
    std::cout << "Testing integration with all components..." << std::endl;
    
    // Test that ErrorFormatter properly integrates with:
    // 1. ErrorCodeGenerator
    // 2. ContextualHintProvider  
    // 3. SourceCodeFormatter
    // 4. ErrorCatalog
    
    std::string sourceCode = R"(fn factorial(n: int) -> int {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
    // Missing closing brace
)";
    
    BlockContext blockContext("function", 1, 1, "fn factorial(n: int) -> int {");
    
    ErrorMessage error = ErrorFormatter::createErrorMessage(
        "Unexpected end of file",
        7, 25,
        InterpretationStage::PARSING,
        sourceCode,
        "",
        "}",
        "factorial.lm",
        blockContext
    );
    
    // Verify ErrorCodeGenerator integration
    assert(!error.errorCode.empty());
    assert(error.errorCode[0] == 'E');
    assert(!error.errorType.empty());
    
    // Verify ContextualHintProvider integration
    assert(!error.hint.empty());
    assert(!error.suggestion.empty());
    
    // Verify SourceCodeFormatter integration
    assert(!error.contextLines.empty());
    
    // Verify ErrorCatalog integration (should find definition for "Unexpected end of file")
    // The hint should contain relevant information about the error
    assert(!error.hint.empty());
    
    // Verify block context integration
    assert(!error.causedBy.empty());
    assert(error.causedBy.find("function") != std::string::npos);
    
    printErrorMessage(error);
    
    std::cout << "Integration with all components test passed." << std::endl;
}