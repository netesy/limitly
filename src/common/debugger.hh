// debugger.h
#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <optional>
#include <set>

// Include error handling structures
#include "../error/error_message.hh"

class Debugger
{
public:
    // Original method for reporting errors with source code (maintained for backward compatibility)
    static void error(const std::string &errorMessage,
                      int line,
                      int column,
                      InterpretationStage stage,
                      const std::string &code,
                      const std::string &lexeme = "",
                      const std::string &expectedValue = "");

    // Enhanced error reporting methods with file path support
    static void error(const std::string &errorMessage,
                      int line,
                      int column,
                      InterpretationStage stage,
                      const std::string &code,
                      const std::string &filePath,
                      const std::string &lexeme = "",
                      const std::string &expectedValue = "");

    // Enhanced error reporting with block context for unclosed constructs
    static void error(const std::string &errorMessage,
                      int line,
                      int column,
                      InterpretationStage stage,
                      const std::string &code,
                      const std::string &filePath,
                      const std::optional<ErrorHandling::BlockContext> &blockContext,
                      const std::string &lexeme = "",
                      const std::string &expectedValue = "");

    // Method for reporting errors with pre-built ErrorMessage
    static void error(const ErrorHandling::ErrorMessage &errorMessage);

    // Method to check if any errors have occurred
    static bool hasError() { return hadError; }

    // Method to reset error state
    static void resetError() { 
        hadError = false; 
        reportedErrors.clear(); // Clear reported errors to allow fresh error reporting
    }

private:
    static std::vector<std::string> sourceCodez;
    static bool hadError;
    static bool useEnhancedFormatting;
    static std::set<std::string> reportedErrors; // Track reported errors to prevent duplicates

    // Enhanced console and log methods using new formatters
    static void debugConsole(const ErrorHandling::ErrorMessage &errorMessage);
    static void debugLog(const ErrorHandling::ErrorMessage &errorMessage);

    // Legacy methods (kept for backward compatibility)
    static void debugConsole(const std::string &errorMessage,
                             int line,
                             int column,
                             InterpretationStage stage,
                             const std::string &lexeme,
                             const std::string &expectedValue);
    static void debugLog(const std::string &errorMessage,
                         int line,
                         int column,
                         InterpretationStage stage,
                         const std::string &lexeme,
                         const std::string &expectedValue);

    // Legacy helper methods (kept for backward compatibility)
    static void printContextLines(std::ostream &out, int errorLine, int errorColumn);
    static std::vector<std::string> splitLines(const std::string &sourceCode);
    static std::string getTime();
    static std::string getSuggestion(const std::string &errorMessage,
                                     const std::string &expectedValue);
    static std::string getSampleSolution(const std::string &errorMessage,
                                         const std::string &expectedValue);
    static std::string stageToString(InterpretationStage stage);

    // Helper method to create enhanced error message
    static ErrorHandling::ErrorMessage createEnhancedErrorMessage(
        const std::string &errorMessage,
        int line,
        int column,
        InterpretationStage stage,
        const std::string &code,
        const std::string &filePath = "",
        const std::string &lexeme = "",
        const std::string &expectedValue = "",
        const std::optional<ErrorHandling::BlockContext> &blockContext = std::nullopt);

    // Method to enable/disable enhanced formatting
    static void setEnhancedFormatting(bool enabled) { useEnhancedFormatting = enabled; }
};