// debugger.cpp

#include "debugger.hh"
#include "../error/error_formatter.hh"
#include "../error/console_formatter.hh"
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

std::vector<std::string> Debugger::sourceCodez;
bool Debugger::hadError = false;
bool Debugger::useEnhancedFormatting = true;
std::set<std::string> Debugger::reportedErrors;

void Debugger::error(const std::string &errorMessage,
                     int line,
                     int column,
                     InterpretationStage stage,
                     const std::string &code,
                     const std::string &lexeme,
                     const std::string &expectedValue)
{
    // Create a unique key for this error to prevent duplicates
    std::string errorKey = errorMessage + ":" + std::to_string(line) + ":" + std::to_string(column);
    
    // Check if we've already reported this error
    if (reportedErrors.find(errorKey) != reportedErrors.end()) {
        return; // Skip duplicate error
    }
    
    // Add to reported errors set
    reportedErrors.insert(errorKey);
    
    hadError = true;
    
    if (useEnhancedFormatting) {
        // Use enhanced error formatting
        ErrorHandling::ErrorMessage enhancedError = createEnhancedErrorMessage(
            errorMessage, line, column, stage, code, "", lexeme, expectedValue
        );
        debugConsole(enhancedError);
        debugLog(enhancedError);
    } else {
        // Fall back to legacy formatting
        sourceCodez = splitLines(code);
        debugConsole(errorMessage, line, column, stage, lexeme, expectedValue);
        debugLog(errorMessage, line, column, stage, lexeme, expectedValue);
    }
}

void Debugger::error(const std::string &errorMessage,
                     int line,
                     int column,
                     InterpretationStage stage,
                     const std::string &code,
                     const std::string &filePath,
                     const std::string &lexeme,
                     const std::string &expectedValue)
{
    // Create a unique key for this error to prevent duplicates
    std::string errorKey = errorMessage + ":" + std::to_string(line) + ":" + std::to_string(column) + ":" + filePath;
    
    // Check if we've already reported this error
    if (reportedErrors.find(errorKey) != reportedErrors.end()) {
        return; // Skip duplicate error
    }
    
    // Add to reported errors set
    reportedErrors.insert(errorKey);
    
    hadError = true;
    
    if (useEnhancedFormatting) {
        // Use enhanced error formatting with file path
        ErrorHandling::ErrorMessage enhancedError = createEnhancedErrorMessage(
            errorMessage, line, column, stage, code, filePath, lexeme, expectedValue
        );
        debugConsole(enhancedError);
        debugLog(enhancedError);
    } else {
        // Fall back to legacy formatting
       // sourceCodez = splitLines(code);
       // debugConsole(errorMessage, line, column, stage, lexeme, expectedValue);
       // debugLog(errorMessage, line, column, stage, lexeme, expectedValue);
    }
}

void Debugger::error(const std::string &errorMessage,
                     int line,
                     int column,
                     InterpretationStage stage,
                     const std::string &code,
                     const std::string &filePath,
                     const std::optional<ErrorHandling::BlockContext> &blockContext,
                     const std::string &lexeme,
                     const std::string &expectedValue)
{
    hadError = true;
    
    if (useEnhancedFormatting) {
        // Use enhanced error formatting with block context
        ErrorHandling::ErrorMessage enhancedError = createEnhancedErrorMessage(
            errorMessage, line, column, stage, code, filePath, lexeme, expectedValue, blockContext
        );
        debugConsole(enhancedError);
        debugLog(enhancedError);
    } else {
        // Fall back to legacy formatting
        sourceCodez = splitLines(code);
        debugConsole(errorMessage, line, column, stage, lexeme, expectedValue);
        debugLog(errorMessage, line, column, stage, lexeme, expectedValue);
    }
}

void Debugger::error(const ErrorHandling::ErrorMessage &errorMessage)
{
    hadError = true;
    debugConsole(errorMessage);
    debugLog(errorMessage);
}

void Debugger::debugConsole(const ErrorHandling::ErrorMessage &errorMessage)
{
    // Use the enhanced ConsoleFormatter for human-readable output
    ErrorHandling::ConsoleFormatter::ConsoleOptions options = 
        ErrorHandling::ConsoleFormatter::getDefaultOptions();
    
    // Write the formatted error message to stderr
    std::cerr << ErrorHandling::ConsoleFormatter::formatErrorMessage(errorMessage, options) << std::endl;
}


void Debugger::debugLog(const ErrorHandling::ErrorMessage &errorMessage)
{
    // Use the enhanced ConsoleFormatter for human-readable output
    ErrorHandling::ConsoleFormatter::ConsoleOptions options = 
        ErrorHandling::ConsoleFormatter::getDefaultOptions();
    

    // Write the formatted error message to stderr
    std::ofstream logfile("debug_log.log", std::ios_base::app); // Open log file for appending
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }
    logfile << ErrorHandling::ConsoleFormatter::formatErrorMessage(errorMessage, options) << std::endl;
    logfile.close(); // Close the log file
}

void Debugger::debugConsole(const std::string &errorMessage,
                            int line,
                            int column,
                            InterpretationStage stage,
                            const std::string &lexeme,
                            const std::string &expectedValue)
{
    std::cerr << "\n ----------------DEBUG----------------\n"
              << "Line " << line << " ("
              << stageToString(stage) << "): " << errorMessage << std::endl;

    if (!expectedValue.empty()) {
        std::cerr << "Expected value: " << expectedValue << std::endl;
    }

    std::cerr << "Time: " << getTime() << std::endl;

    // Show the line before, the error line (in bold), and the line after
    printContextLines(std::cerr, line, column);

    std::cerr << "Suggestion: " << getSuggestion(errorMessage, expectedValue) << std::endl;
    std::cerr << "Sample Solution: " << getSampleSolution(errorMessage, expectedValue)
              << "\n ----------------END----------------\n"
              << std::endl;
}

void Debugger::debugLog(const std::string &errorMessage,
                        int line,
                        int column,
                        InterpretationStage stage,
                        const std::string &lexeme,
                        const std::string &expectedValue)
{
    std::ofstream logfile("debug_log.log", std::ios_base::app); // Open log file for appending
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    logfile << "\n ----------------DEBUG----------------\n"
            << "Line " << line << " ("
            << stageToString(stage) << "): " << errorMessage << std::endl;

    if (!expectedValue.empty()) {
        logfile << "Expected value: " << expectedValue << std::endl;
    }

    logfile << "Time: " << getTime() << std::endl;

    // Show the line before, the error line, and the line after
    printContextLines(logfile, line, column);

    logfile << "Suggestion: " << getSuggestion(errorMessage, expectedValue) << std::endl;
    logfile << "Sample Solution: " << getSampleSolution(errorMessage, expectedValue)
            << "\n ----------------END----------------\n"
            << std::endl;

    logfile.close(); // Close the log file
}

void Debugger::printContextLines(std::ostream &out, int errorLine, int errorColumn)
{
    std::string boldOn("\033[1m");
    std::string boldOff("\033[0m");
    std::string colorRed("\033[31m");
    std::string colorBlue("\033[32m");
    std::string colorReset("\033[0m");

    // Print the line before the error
    if (errorLine > 1 && errorLine <= int(sourceCodez.size())) {
        out << (errorLine - 1) << " | " << sourceCodez[errorLine - 2] << std::endl;
    }

    // Print the error line with the faulty token highlighted
    if (errorLine >= 1 && errorLine <= int(sourceCodez.size())) {
        std::string currentLine = sourceCodez[errorLine - 1];
        out << errorLine << colorBlue << " > " << colorReset << boldOn;

        // Highlight only the faulty token
        int currentColumn = 1;
        for (char c : currentLine) {
            if (currentColumn == errorColumn) {
                out << colorRed;
            }
            out << c;
            if (currentColumn == errorColumn) {
                out << colorReset;
            }
            if (c == '\t') {
                currentColumn += 4; // Assuming tab width of 4
            } else {
                currentColumn++;
            }
        }

        out << boldOff << std::endl;
    }

    // Print the line after the error
    if (errorLine < int(sourceCodez.size())) {
        out << (errorLine + 1) << " | " << sourceCodez[errorLine] << std::endl;
    }

    out << std::endl;
}

std::vector<std::string> Debugger::splitLines(const std::string &sourceCode)
{
    std::vector<std::string> lines;
    std::stringstream ss(sourceCode);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::string Debugger::getTime()
{
    auto current_time = std::chrono::system_clock::now();
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
    return std::ctime(&current_time_t);
}

std::string Debugger::getSuggestion(const std::string &errorMessage,
                                    const std::string &expectedValue)
{
    // Provide suggestions based on the error message and expected value
    if (errorMessage.find("Invalid character") != std::string::npos) {
        return "Check for invalid characters in your code.";
    } else if (errorMessage.find("Variable/function not found") != std::string::npos) {
        return "Check the spelling of the variable or function name, or make sure it has been "
               "declared or defined before use.";
    } else if (errorMessage.find("Invalid factor") != std::string::npos) {
        return "Check the expression to ensure it follows the correct syntax.";
    } else if (errorMessage.find("Unexpected token") != std::string::npos) {
        if (!expectedValue.empty()) {
            return "Expected '" + expectedValue
                   + "'. Ensure the syntax matches the expected pattern.";
        }
        return "Check your code for syntax errors.";
    } else if (errorMessage.find("Expected") != std::string::npos) {
        return "Ensure the correct syntax is followed. " + errorMessage;
    } else if (errorMessage.find("Invalid value stack for unary operation") != std::string::npos) {
        return "Ensure the stack has sufficient values for the operation.";
    } else if (errorMessage.find("Invalid value stack for binary operation") != std::string::npos) {
        return "Ensure the stack has two values for the binary operation.";
    } else if (errorMessage.find("Unsupported type for NEGATE operation") != std::string::npos) {
        return "NEGATE operation supports only int32_t and double types.";
    } else if (errorMessage.find("Unsupported type for NOT operation") != std::string::npos) {
        return "NOT operation supports only bool type.";
    } else if (errorMessage.find("Division by zero") != std::string::npos) {
        return "Ensure the divisor is not zero.";
    } else if (errorMessage.find("Modulo by zero") != std::string::npos) {
        return "Ensure the divisor is not zero.";
    } else if (errorMessage.find("Unsupported types for binary operation") != std::string::npos) {
        return "Binary operations support int32_t and double types.";
    } else if (errorMessage.find("Insufficient value stack for logical operation")
               != std::string::npos) {
        return "Ensure the stack has two values for the logical operation.";
    } else if (errorMessage.find("Unsupported types for logical operation") != std::string::npos) {
        return "Logical operations support only bool type.";
    } else if (errorMessage.find("Insufficient value stack for comparison operation")
               != std::string::npos) {
        return "Ensure the stack has two values for the comparison operation.";
    } else if (errorMessage.find("Unsupported types for comparison operation")
               != std::string::npos) {
        return "Comparison operations support int32_t and double types.";
    } else if (errorMessage.find("Invalid variable index") != std::string::npos) {
        return "Ensure the variable index is within the valid range.";
    } else if (errorMessage.find("value stack underflow") != std::string::npos) {
        return "Ensure there are enough values on the stack for the operation.";
    } else if (errorMessage.find("Invalid jump offset type") != std::string::npos) {
        return "Ensure the jump offset is of type int32_t.";
    } else if (errorMessage.find("JUMP_IF_FALSE requires a boolean condition")
               != std::string::npos) {
        return "Ensure the condition for JUMP_IF_FALSE is a boolean.";
    } else {
        return "Check your code for errors.";
    }
}

std::string Debugger::getSampleSolution(const std::string &errorMessage,
                                        const std::string &expectedValue)
{
    // Provide a sample solution based on the error message and expected value
    if (errorMessage.find("Invalid character") != std::string::npos) {
        return "Check for invalid characters in your code.";
    } else if (errorMessage.find("Variable/function not found") != std::string::npos) {
        return "Check the spelling of the variable or function name, or make sure it has been "
               "declared or defined before use.";
    } else if (errorMessage.find("Invalid factor") != std::string::npos) {
        return "Ensure the expression follows the correct syntax, with valid operators and "
               "operands.";
    } else if (errorMessage.find("Unexpected token") != std::string::npos) {
        if (!expectedValue.empty()) {
            return "Expected '" + expectedValue
                   + "'. Ensure the syntax matches the expected pattern.";
        }
        return "Check your code for syntax errors, such as missing or misplaced tokens.";
    } else if (errorMessage.find("Expected") != std::string::npos) {
        return "Ensure the correct syntax is followed. " + errorMessage;
    } else if (errorMessage.find("Invalid value stack for unary operation") != std::string::npos) {
        return "Ensure the stack has enough values for the operation.";
    } else if (errorMessage.find("Invalid value stack for binary operation") != std::string::npos) {
        return "Ensure the stack has two values for the binary operation.";
    } else if (errorMessage.find("Unsupported type for NEGATE operation") != std::string::npos) {
        return "NEGATE operation only supports int32_t and double types.";
    } else if (errorMessage.find("Unsupported type for NOT operation") != std::string::npos) {
        return "NOT operation only supports bool type.";
    } else if (errorMessage.find("Division by zero") != std::string::npos) {
        return "Ensure the divisor is not zero.";
    } else if (errorMessage.find("Modulo by zero") != std::string::npos) {
        return "Ensure the divisor is not zero.";
    } else if (errorMessage.find("Unsupported types for binary operation") != std::string::npos) {
        return "Binary operations support int32_t and double types.";
    } else if (errorMessage.find("Insufficient value stack for logical operation")
               != std::string::npos) {
        return "Ensure the stack has two values for the logical operation.";
    } else if (errorMessage.find("Unsupported types for logical operation") != std::string::npos) {
        return "Logical operations only support bool type.";
    } else if (errorMessage.find("Insufficient value stack for comparison operation")
               != std::string::npos) {
        return "Ensure the stack has two values for the comparison operation.";
    } else if (errorMessage.find("Unsupported types for comparison operation")
               != std::string::npos) {
        return "Comparison operations support int32_t and double types.";
    } else if (errorMessage.find("Invalid variable index") != std::string::npos) {
        return "Ensure the variable index is within the valid range.";
    } else if (errorMessage.find("value stack underflow") != std::string::npos) {
        return "Ensure there are enough values on the stack for the operation.";
    } else if (errorMessage.find("Invalid jump offset type") != std::string::npos) {
        return "Ensure the jump offset is of type int32_t.";
    } else if (errorMessage.find("JUMP_IF_FALSE requires a boolean condition")
               != std::string::npos) {
        return "Ensure the condition for JUMP_IF_FALSE is a boolean.";
    } else {
        return "Check your code for errors.";
    }
}

std::string Debugger::stageToString(InterpretationStage stage)
{
    switch (stage) {
    case InterpretationStage::SCANNING:
        return "Lexical Error";
    case InterpretationStage::PARSING:
        return "Syntax Error";
    case InterpretationStage::SYNTAX:
        return "Syntax Parsing";
    case InterpretationStage::SEMANTIC:
        return "Semantic Parsing";
    case InterpretationStage::MEMORY:
        return "Memory Safety";
    case InterpretationStage::BYTECODE:
        return "Bytecode Generation";
    case InterpretationStage::INTERPRETING:
        return "Interpreting";
    case InterpretationStage::COMPILING:
        return "Compiling";
    default:
        return "Unknown stage";
    }
}

// Helper method to create enhanced error message
ErrorHandling::ErrorMessage Debugger::createEnhancedErrorMessage(
    const std::string &errorMessage,
    int line,
    int column,
    InterpretationStage stage,
    const std::string &code,
    const std::string &filePath,
    const std::string &lexeme,
    const std::string &expectedValue,
    const std::optional<ErrorHandling::BlockContext> &blockContext)
{
    // Use ErrorFormatter to create the enhanced error message
    return ErrorHandling::ErrorFormatter::createErrorMessage(
        errorMessage, line, column, stage, code, lexeme, expectedValue, filePath
    );
}