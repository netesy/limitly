// debugger.cpp
#include "debugger.hpp"

void Debugger::debugInfo(const std::string& errorMessage, int lineNumber, int position, InterpretationStage stage, const std::string& expectedValue) {
    std::cerr << "Debug Info (" << stageToString(stage) << "):" << std::endl;
    std::cerr << "Line number: " << lineNumber << ", Position: " << position << std::endl;
    std::cerr << "Error: " << errorMessage << std::endl;
    if (!expectedValue.empty()) {
        std::cerr << "Expected value: " << expectedValue << std::endl;
    }
    std::cerr << "Suggestion: " << getSuggestion(errorMessage) << std::endl;
}

void Debugger::error(const std::string &errorMessage,
                     int lineNumber,
                     int position,
                     InterpretationStage stage,
                     const std::string &token,
                     const std::string &expectedValue)
{
    std::cerr << "Error at line " << lineNumber << ", position " << position << " (" << stageToString(stage) << "): " << errorMessage << std::endl;
    if (!token.empty()) {
        std::cerr << "Token: " << token << std::endl;
    }
    if (!expectedValue.empty()) {
        std::cerr << "Expected value: " << expectedValue << std::endl;
    }
    std::cerr << "Suggestion: " << getSuggestion(errorMessage) << std::endl;
}

std::string Debugger::getSuggestion(const std::string& errorMessage) {
    // Provide suggestions based on the error message
    if (errorMessage == "Invalid character.") {
        return "Check for invalid characters in your code.";
    } else if (errorMessage == "Variable/function not found") {
        return "Check the spelling of the variable or function name, or make sure it has been declared or defined before use.";
    } else if (errorMessage == "Invalid factor") {
        return "Check the expression to ensure it follows the correct syntax.";
    } else {
        return "Check your code for errors.";
    }
}

std::string Debugger::stageToString(InterpretationStage stage) {
    switch (stage) {
        case InterpretationStage::SCANNING:
            return "Scanning";
        case InterpretationStage::PARSING:
            return "Parsing";
        case InterpretationStage::SYNTAX:
            return "Syntax Parsing";
        case InterpretationStage::SEMANTIC:
            return "Semantic Parsing";
        case InterpretationStage::INTERPRETING:
            return "Interpreting";
        default:
            return "Unknown stage";
    }
}
