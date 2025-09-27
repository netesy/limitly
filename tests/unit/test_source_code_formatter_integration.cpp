#include "../../src/source_code_formatter.hh"
#include "../../src/error_code_generator.hh"
#include <iostream>
#include <sstream>

using namespace ErrorHandling;

void demonstrateBasicErrorFormatting() {
    std::cout << "\n=== Basic Error Formatting Demo ===" << std::endl;
    
    std::string sourceCode = 
        "function calculateSum(a, b) {\n"
        "    var result = a + b;\n"
        "    return result;\n"
        "}\n"
        "\n"
        "var x = calculateSum(5, );\n"  // Missing argument
        "print(x);";
    
    // Simulate an error at line 6, column 21 (missing argument)
    int errorLine = 6;
    int errorColumn = 21;
    
    // Generate error code
    std::string errorCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Missing argument");
    std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING);
    
    // Format source context
    auto contextLines = SourceCodeFormatter::formatSourceContext(sourceCode, errorLine, errorColumn);
    
    std::cout << "error[" << errorCode << "][" << errorType << "]: Missing argument in function call" << std::endl;
    std::cout << "--> example.lm:" << errorLine << ":" << errorColumn << std::endl;
    std::cout << "   |" << std::endl;
    
    for (const auto& line : contextLines) {
        std::cout << line << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Hint: Function calls require all parameters to be provided." << std::endl;
    std::cout << "Suggestion: Add the missing argument or use a default parameter." << std::endl;
}

void demonstrateTokenHighlighting() {
    std::cout << "\n=== Token Highlighting Demo ===" << std::endl;
    
    std::string sourceCode = 
        "let x = 42;\n"
        "let y = undefinedVariable;\n"  // Undefined variable
        "print(y);";
    
    // Simulate an error at line 2, column 9 (undefined variable, 16 chars long)
    int errorLine = 2;
    int errorColumn = 9;
    int tokenLength = 16; // "undefinedVariable"
    
    // Generate error code
    std::string errorCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC, "Undefined variable");
    std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::SEMANTIC);
    
    // Format source context with token highlighting
    auto contextLines = SourceCodeFormatter::formatTokenContext(sourceCode, errorLine, errorColumn, tokenLength);
    
    std::cout << "error[" << errorCode << "][" << errorType << "]: Use of undefined variable 'undefinedVariable'" << std::endl;
    std::cout << "--> example.lm:" << errorLine << ":" << errorColumn << std::endl;
    std::cout << "   |" << std::endl;
    
    for (const auto& line : contextLines) {
        std::cout << line << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Hint: Variables must be declared before use." << std::endl;
    std::cout << "Suggestion: Check the spelling or declare the variable first." << std::endl;
}

void demonstrateRangeHighlighting() {
    std::cout << "\n=== Range Highlighting Demo ===" << std::endl;
    
    std::string sourceCode = 
        "if (x > 0) {\n"
        "    print(\"positive\");\n"
        "    // Missing closing brace\n"
        "print(\"done\");";
    
    // Simulate an error at line 4, highlighting the entire print statement
    int errorLine = 4;
    int startColumn = 1;
    int endColumn = 15; // "print(\"done\");"
    
    // Generate error code
    std::string errorCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unclosed block");
    std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING);
    
    // Format source context with range highlighting
    auto contextLines = SourceCodeFormatter::formatRangeContext(sourceCode, errorLine, startColumn, endColumn);
    
    std::cout << "error[" << errorCode << "][" << errorType << "]: Unexpected statement outside block" << std::endl;
    std::cout << "--> example.lm:" << errorLine << ":" << startColumn << std::endl;
    std::cout << "   |" << std::endl;
    
    for (const auto& line : contextLines) {
        std::cout << line << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Hint: This statement appears to be outside a block structure." << std::endl;
    std::cout << "Suggestion: Check for missing closing braces in the block above." << std::endl;
    std::cout << "Caused by: Unclosed block starting at line 1:" << std::endl;
    std::cout << " 1 | if (x > 0) {" << std::endl;
    std::cout << "   | ----------- unclosed block starts here" << std::endl;
}

void demonstrateCustomFormatting() {
    std::cout << "\n=== Custom Formatting Options Demo ===" << std::endl;
    
    std::string sourceCode = 
        "// This is a longer example\n"
        "function processData(data) {\n"
        "    if (data == null) {\n"
        "        return null;\n"
        "    }\n"
        "    \n"
        "    let result = data.process();\n"  // Error here
        "    return result;\n"
        "}";
    
    // Create custom formatting options
    SourceCodeFormatter::FormatOptions options;
    options.contextLinesBefore = 3;  // Show more context
    options.contextLinesAfter = 2;
    options.useColors = false;       // Disable colors for this demo
    options.useUnicode = false;      // Use ASCII characters
    options.showLineNumbers = true;
    options.tabWidth = 4;
    
    int errorLine = 7;
    int errorColumn = 18;
    int tokenLength = 9; // ".process()"
    
    // Generate error code
    std::string errorCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC, "Method not found");
    std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::SEMANTIC);
    
    // Format source context with custom options
    auto contextLines = SourceCodeFormatter::formatTokenContext(sourceCode, errorLine, errorColumn, tokenLength, options);
    
    std::cout << "error[" << errorCode << "][" << errorType << "]: Method 'process' not found on object" << std::endl;
    std::cout << "--> example.lm:" << errorLine << ":" << errorColumn << std::endl;
    std::cout << "   |" << std::endl;
    
    for (const auto& line : contextLines) {
        std::cout << line << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Hint: The object may not have a 'process' method." << std::endl;
    std::cout << "Suggestion: Check the object's available methods or verify the method name." << std::endl;
}

void demonstrateWriteToStream() {
    std::cout << "\n=== Stream Output Demo ===" << std::endl;
    
    std::string sourceCode = "let x = 5 + ;";  // Syntax error
    
    auto contextLines = SourceCodeFormatter::formatSourceContext(sourceCode, 1, 13);
    
    std::ostringstream oss;
    oss << "error[E101][SyntaxError]: Expected expression after '+'" << std::endl;
    oss << "--> example.lm:1:13" << std::endl;
    oss << "   |" << std::endl;
    
    SourceCodeFormatter::writeFormattedContext(oss, contextLines);
    
    oss << std::endl;
    oss << "Hint: Binary operators require operands on both sides." << std::endl;
    oss << "Suggestion: Add an expression after the '+' operator." << std::endl;
    
    std::cout << "Generated error message:" << std::endl;
    std::cout << oss.str() << std::endl;
}

int main() {
    std::cout << "SourceCodeFormatter Integration Tests" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    demonstrateBasicErrorFormatting();
    demonstrateTokenHighlighting();
    demonstrateRangeHighlighting();
    demonstrateCustomFormatting();
    demonstrateWriteToStream();
    
    std::cout << "=====================================" << std::endl;
    std::cout << "Integration tests completed!" << std::endl;
    
    return 0;
}