// debugger.cpp

#include "debugger.hh"
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

namespace LM {
namespace Error {

std::vector<std::string> Debugger::sourceCodeLines;
bool Debugger::hadError = false;
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
    
    // Create enhanced error message
    Message enhancedError = createEnhancedErrorMessage(
        errorMessage, line, column, stage, code, "", lexeme, expectedValue
    );
    debugConsole(enhancedError);
    debugLog(enhancedError);
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
    
    // Create enhanced error message with file path
    Message enhancedError = createEnhancedErrorMessage(
        errorMessage, line, column, stage, code, filePath, lexeme, expectedValue
    );
    debugConsole(enhancedError);
    debugLog(enhancedError);
}

void Debugger::error(const std::string &errorMessage,
                     int line,
                     int column,
                     InterpretationStage stage,
                     const std::string &code,
                     const std::string &filePath,
                     const std::optional<BlockContext> &blockContext,
                     const std::string &lexeme,
                     const std::string &expectedValue)
{
    hadError = true;
    
    // Create enhanced error message with block context
    Message enhancedError = createEnhancedErrorMessage(
        errorMessage, line, column, stage, code, filePath, lexeme, expectedValue, blockContext
    );
    debugConsole(enhancedError);
    debugLog(enhancedError);
}

void Debugger::error(const Message &errorMessage)
{
    hadError = true;
    debugConsole(errorMessage);
    debugLog(errorMessage);
}

void Debugger::debugConsole(const Message &errorMessage)
{
    std::cerr << "\n ----------------ERROR----------------\n"
              << "Code: " << errorMessage.errorCode << "\n"
              << "Type: " << errorMessage.errorType << "\n"
              << "Line " << errorMessage.line << ", Column " << errorMessage.column << "\n"
              << "Stage: " << stageToString(errorMessage.stage) << "\n"
              << "Message: " << errorMessage.description << std::endl;

    if (!errorMessage.filePath.empty()) {
        std::cerr << "File: " << errorMessage.filePath << std::endl;
    }

    if (!errorMessage.problematicToken.empty()) {
        std::cerr << "Token: " << errorMessage.problematicToken << std::endl;
    }

    if (!errorMessage.hint.empty()) {
        std::cerr << "Hint: " << errorMessage.hint << std::endl;
    }

    if (!errorMessage.suggestion.empty()) {
        std::cerr << "Suggestion: " << errorMessage.suggestion << std::endl;
    }

    if (!errorMessage.causedBy.empty()) {
        std::cerr << "Caused by: " << errorMessage.causedBy << std::endl;
    }

    std::cerr << "Time: " << getTime();
    std::cerr << " ----------------END----------------\n" << std::endl;
}

void Debugger::debugLog(const Message &errorMessage)
{
    std::ofstream logfile("debug_log.log", std::ios_base::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    logfile << "\n ----------------ERROR----------------\n"
            << "Code: " << errorMessage.errorCode << "\n"
            << "Type: " << errorMessage.errorType << "\n"
            << "Line " << errorMessage.line << ", Column " << errorMessage.column << "\n"
            << "Stage: " << stageToString(errorMessage.stage) << "\n"
            << "Message: " << errorMessage.description << std::endl;

    if (!errorMessage.filePath.empty()) {
        logfile << "File: " << errorMessage.filePath << std::endl;
    }

    if (!errorMessage.problematicToken.empty()) {
        logfile << "Token: " << errorMessage.problematicToken << std::endl;
    }

    if (!errorMessage.hint.empty()) {
        logfile << "Hint: " << errorMessage.hint << std::endl;
    }

    if (!errorMessage.suggestion.empty()) {
        logfile << "Suggestion: " << errorMessage.suggestion << std::endl;
    }

    if (!errorMessage.causedBy.empty()) {
        logfile << "Caused by: " << errorMessage.causedBy << std::endl;
    }

    logfile << "Time: " << getTime();
    logfile << " ----------------END----------------\n" << std::endl;

    logfile.close();
}

void Debugger::printContextLines(std::ostream &out, int errorLine, int errorColumn)
{
    std::string boldOn("\033[1m");
    std::string boldOff("\033[0m");
    std::string colorRed("\033[31m");
    std::string colorBlue("\033[32m");
    std::string colorReset("\033[0m");

    // Print the line before the error
    if (errorLine > 1 && errorLine <= int(sourceCodeLines.size())) {
        out << (errorLine - 1) << " | " << sourceCodeLines[errorLine - 2] << std::endl;
    }

    // Print the error line with the faulty token highlighted
    if (errorLine >= 1 && errorLine <= int(sourceCodeLines.size())) {
        std::string currentLine = sourceCodeLines[errorLine - 1];
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
    if (errorLine < int(sourceCodeLines.size())) {
        out << (errorLine + 1) << " | " << sourceCodeLines[errorLine] << std::endl;
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
    std::string time_str = std::ctime(&current_time_t);
    // Remove trailing newline from ctime
    if (!time_str.empty() && time_str.back() == '\n') {
        time_str.pop_back();
    }
    return time_str;
}

std::string Debugger::getSuggestion(const std::string &errorMessage,
                                    const std::string &expectedValue)
{
    // Provide suggestions based on the error message and expected value
    if (errorMessage.find("Invalid character") != std::string::npos) {
        return "Check for invalid characters in your code.";
    } else if (errorMessage.find("Variable/function not found") != std::string::npos) {
        return "Check the spelling of the variable or function name, or make sure it has been declared or defined before use.";
    } else if (errorMessage.find("Invalid factor") != std::string::npos) {
        return "Check the expression to ensure it follows the correct syntax.";
    } else if (errorMessage.find("Unexpected token") != std::string::npos) {
        if (!expectedValue.empty()) {
            return "Expected '" + expectedValue + "'. Ensure the syntax matches the expected pattern.";
        }
        return "Check your code for syntax errors.";
    } else if (errorMessage.find("Expected") != std::string::npos) {
        return "Ensure the correct syntax is followed. " + errorMessage;
    } else if (errorMessage.find("Division by zero") != std::string::npos) {
        return "Ensure the divisor is not zero.";
    } else if (errorMessage.find("Modulo by zero") != std::string::npos) {
        return "Ensure the divisor is not zero.";
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

Message Debugger::createEnhancedErrorMessage(
    const std::string &errorMessage,
    int line,
    int column,
    InterpretationStage stage,
    const std::string &code,
    const std::string &filePath,
    const std::string &lexeme,
    const std::string &expectedValue,
    const std::optional<BlockContext> &blockContext)
{
    // Create error code based on stage
    std::string errorCode = "E";
    switch (stage) {
    case InterpretationStage::SCANNING:
        errorCode += "001";
        break;
    case InterpretationStage::PARSING:
        errorCode += "002";
        break;
    case InterpretationStage::SEMANTIC:
        errorCode += "003";
        break;
    case InterpretationStage::BYTECODE:
        errorCode += "004";
        break;
    case InterpretationStage::INTERPRETING:
        errorCode += "005";
        break;
    default:
        errorCode += "000";
    }

    // Create error type based on stage
    std::string errorType = stageToString(stage);

    // Create error message
    Message msg(errorCode, errorType, errorMessage, filePath, line, column, lexeme, stage);
    
    // Add suggestion
    msg.suggestion = getSuggestion(errorMessage, expectedValue);
    
    // Add block context if available
    if (blockContext.has_value()) {
        msg.causedBy = "Unclosed " + blockContext->blockType + " block starting at line " + 
                      std::to_string(blockContext->startLine);
    }

    // Split source code into lines for context
    sourceCodeLines = splitLines(code);
    if (line > 0 && line <= int(sourceCodeLines.size())) {
        // Add context lines
        if (line > 1) {
            msg.contextLines.push_back(sourceCodeLines[line - 2]);
        }
        msg.contextLines.push_back(sourceCodeLines[line - 1]);
        if (line < int(sourceCodeLines.size())) {
            msg.contextLines.push_back(sourceCodeLines[line]);
        }
    }

    return msg;
}

} // namespace Error
} // namespace LM
