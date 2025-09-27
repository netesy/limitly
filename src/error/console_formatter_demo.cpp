#include "console_formatter.hh"
#include <iostream>

using namespace ErrorHandling;

void demonstrateSyntaxError() {
    std::cout << "=== Syntax Error Example ===\n" << std::endl;
    
    ErrorMessage error("E102", "SyntaxError", "Unexpected closing brace `}`", 
                      "src/utils.calc", 15, 113, "}", InterpretationStage::PARSING);
    
    // Add source context
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
    options.useColors = true;
    
    std::cout << ConsoleFormatter::formatErrorMessage(error, options) << std::endl;
}

void demonstrateSemanticError() {
    std::cout << "=== Semantic Error Example ===\n" << std::endl;
    
    ErrorMessage error("E201", "SemanticError", "Undefined variable 'count'", 
                      "src/main.lm", 42, 8, "count", InterpretationStage::SEMANTIC);
    
    // Add source context
    error.contextLines = {
        "41 |     let total = 0;",
        "42 |     total += count;",
        "   |              ^^^^^ undefined variable",
        "43 |     return total;"
    };
    
    error.hint = "The variable 'count' has not been declared in this scope.";
    error.suggestion = "Did you mean 'counter'? Or did you forget to declare 'count'?";
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = true;
    
    std::cout << ConsoleFormatter::formatErrorMessage(error, options) << std::endl;
}

void demonstrateTypeError() {
    std::cout << "=== Type Error Example ===\n" << std::endl;
    
    ErrorMessage error("E301", "TypeError", "Cannot assign 'string' to 'int'", 
                      "src/calculator.lm", 28, 15, "\"hello\"", InterpretationStage::SEMANTIC);
    
    // Add source context
    error.contextLines = {
        "27 |     let result: int = 0;",
        "28 |     result = \"hello\";",
        "   |              ^^^^^^^ type mismatch",
        "29 |     return result;"
    };
    
    error.hint = "The variable 'result' is declared as 'int' but you're trying to assign a string value.";
    error.suggestion = "Either change the variable type to 'string' or assign a numeric value.";
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = true;
    
    std::cout << ConsoleFormatter::formatErrorMessage(error, options) << std::endl;
}

void demonstrateRuntimeError() {
    std::cout << "=== Runtime Error Example ===\n" << std::endl;
    
    ErrorMessage error("E401", "RuntimeError", "Division by zero", 
                      "src/math_utils.lm", 156, 20, "/", InterpretationStage::INTERPRETING);
    
    // Add source context
    error.contextLines = {
        "155 |     let divisor = getValue();",
        "156 |     return numerator / divisor;",
        "    |                      ^ division by zero",
        "157 | }"
    };
    
    error.hint = "The divisor evaluated to zero, which would cause a division by zero error.";
    error.suggestion = "Add a check to ensure the divisor is not zero before performing division.";
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = true;
    
    std::cout << ConsoleFormatter::formatErrorMessage(error, options) << std::endl;
}

void demonstrateMinimalError() {
    std::cout << "=== Minimal Error Example ===\n" << std::endl;
    
    ErrorMessage error("E001", "LexicalError", "Invalid character '§'", 
                      "", 0, 0, "§", InterpretationStage::SCANNING);
    
    ConsoleFormatter::ConsoleOptions options;
    options.useColors = true;
    
    std::cout << ConsoleFormatter::formatErrorMessage(error, options) << std::endl;
}

void demonstrateColorOptions() {
    std::cout << "=== Color Options Comparison ===\n" << std::endl;
    
    ErrorMessage error("E102", "SyntaxError", "Missing semicolon", 
                      "src/test.lm", 10, 15, "", InterpretationStage::PARSING);
    
    error.hint = "Statements in Limit must end with a semicolon.";
    error.suggestion = "Add a semicolon ';' at the end of the statement.";
    
    std::cout << "With colors:\n";
    ConsoleFormatter::ConsoleOptions colorOptions;
    colorOptions.useColors = true;
    std::cout << ConsoleFormatter::formatErrorMessage(error, colorOptions) << std::endl;
    
    std::cout << "Without colors:\n";
    ConsoleFormatter::ConsoleOptions noColorOptions;
    noColorOptions.useColors = false;
    std::cout << ConsoleFormatter::formatErrorMessage(error, noColorOptions) << std::endl;
}

int main() {
    std::cout << "ConsoleFormatter Demonstration\n";
    std::cout << "==============================\n" << std::endl;
    
    demonstrateSyntaxError();
    demonstrateSemanticError();
    demonstrateTypeError();
    demonstrateRuntimeError();
    demonstrateMinimalError();
    demonstrateColorOptions();
    
    std::cout << "Demonstration complete!" << std::endl;
    return 0;
}