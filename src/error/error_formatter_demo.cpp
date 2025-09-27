#include "error_formatter.hh"
#include <iostream>

using namespace ErrorHandling;

void demonstrateErrorFormatter() {
    std::cout << "=== ErrorFormatter Demonstration ===" << std::endl;
    
    // Initialize the error formatting system
    ErrorFormatter::initialize();
    
    // Example 1: Syntax error with source context
    std::cout << "\n1. Syntax Error with Source Context:" << std::endl;
    std::string sourceCode1 = R"(fn main() {
    let x: int = 42;
    let y: int = 0
    return x / y;
})";
    
    ErrorMessage syntaxError = ErrorFormatter::createErrorMessage(
        "Missing semicolon",
        3, 19,
        InterpretationStage::PARSING,
        sourceCode1,
        "",
        ";",
        "example.lm"
    );
    
    std::cout << "Error: " << syntaxError.errorCode << " - " << syntaxError.errorType << std::endl;
    std::cout << "Description: " << syntaxError.description << std::endl;
    std::cout << "Location: " << syntaxError.filePath << ":" << syntaxError.line << ":" << syntaxError.column << std::endl;
    std::cout << "Hint: " << syntaxError.hint << std::endl;
    std::cout << "Suggestion: " << syntaxError.suggestion << std::endl;
    std::cout << "Context:" << std::endl;
    for (const auto& line : syntaxError.contextLines) {
        std::cout << line << std::endl;
    }
    
    // Example 2: Runtime error
    std::cout << "\n2. Runtime Error:" << std::endl;
    ErrorMessage runtimeError = ErrorFormatter::createErrorMessage(
        "Division by zero",
        4, 12,
        InterpretationStage::INTERPRETING,
        sourceCode1,
        "/",
        "",
        "example.lm"
    );
    
    std::cout << "Error: " << runtimeError.errorCode << " - " << runtimeError.errorType << std::endl;
    std::cout << "Description: " << runtimeError.description << std::endl;
    std::cout << "Hint: " << runtimeError.hint << std::endl;
    std::cout << "Suggestion: " << runtimeError.suggestion << std::endl;
    
    // Example 3: Block context error
    std::cout << "\n3. Block Context Error:" << std::endl;
    std::string sourceCode2 = R"(fn compute(x: int) -> int {
    if (x > 0) {
        return x * 2;
    // Missing closing brace
    return -1;
})";
    
    BlockContext blockContext("if", 2, 5, "if (x > 0) {");
    
    ErrorMessage blockError = ErrorFormatter::createErrorMessage(
        "Unexpected closing brace '}'",
        6, 1,
        InterpretationStage::PARSING,
        sourceCode2,
        "}",
        "",
        "compute.lm",
        blockContext
    );
    
    std::cout << "Error: " << blockError.errorCode << " - " << blockError.errorType << std::endl;
    std::cout << "Description: " << blockError.description << std::endl;
    std::cout << "Hint: " << blockError.hint << std::endl;
    std::cout << "Suggestion: " << blockError.suggestion << std::endl;
    std::cout << "Caused by: " << blockError.causedBy << std::endl;
    
    // Example 4: Semantic error
    std::cout << "\n4. Semantic Error:" << std::endl;
    std::string sourceCode3 = R"(fn main() {
    let result = undefinedVariable + 42;
    return result;
})";
    
    ErrorMessage semanticError = ErrorFormatter::createErrorMessage(
        "Undefined variable 'undefinedVariable'",
        2, 18,
        InterpretationStage::SEMANTIC,
        sourceCode3,
        "undefinedVariable",
        "",
        "main.lm"
    );
    
    std::cout << "Error: " << semanticError.errorCode << " - " << semanticError.errorType << std::endl;
    std::cout << "Description: " << semanticError.description << std::endl;
    std::cout << "Hint: " << semanticError.hint << std::endl;
    std::cout << "Suggestion: " << semanticError.suggestion << std::endl;
    
    // Example 5: Minimal error message
    std::cout << "\n5. Minimal Error Message:" << std::endl;
    ErrorMessage minimalError = ErrorFormatter::createMinimalErrorMessage(
        "Compilation failed",
        InterpretationStage::COMPILING,
        "project.lm"
    );
    
    std::cout << "Error: " << minimalError.errorCode << " - " << minimalError.errorType << std::endl;
    std::cout << "Description: " << minimalError.description << std::endl;
    std::cout << "File: " << minimalError.filePath << std::endl;
    
    std::cout << "\n=== Demonstration Complete ===" << std::endl;
}

int main() {
    try {
        demonstrateErrorFormatter();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}