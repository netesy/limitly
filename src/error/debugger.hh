#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <optional>
#include <set>

#include "message.hh"

namespace LM {
namespace Error {

/**
 * @brief Debugger class for error reporting and diagnostics
 * Provides centralized error reporting with support for:
 * - Multiple error reporting methods
 * - Duplicate error prevention
 * - Console and log file output
 * - Context-aware error messages
 * - Modern compiler-style diagnostics (Rust/Go/TypeScript style) - internal only
 */
class Debugger {
public:
    /**
     * @brief Report error with source code context
     * @param errorMessage The error message text
     * @param line Line number where error occurred
     * @param column Column number where error occurred
     * @param stage Interpretation stage when error occurred
     * @param code Complete source code for context
     * @param lexeme The specific token causing the error
     * @param expectedValue What was expected (if applicable)
     */
    static void error(const std::string &errorMessage,
                      int line,
                      int column,
                      InterpretationStage stage,
                      const std::string &code,
                      const std::string &lexeme = "",
                      const std::string &expectedValue = "");

    /**
     * @brief Report error with file path
     * @param errorMessage The error message text
     * @param line Line number where error occurred
     * @param column Column number where error occurred
     * @param stage Interpretation stage when error occurred
     * @param code Complete source code for context
     * @param filePath Path to the source file
     * @param lexeme The specific token causing the error
     * @param expectedValue What was expected (if applicable)
     */
    static void error(const std::string &errorMessage,
                      int line,
                      int column,
                      InterpretationStage stage,
                      const std::string &code,
                      const std::string &filePath,
                      const std::string &lexeme = "",
                      const std::string &expectedValue = "");

    /**
     * @brief Report error with block context for unclosed constructs
     * @param errorMessage The error message text
     * @param line Line number where error occurred
     * @param column Column number where error occurred
     * @param stage Interpretation stage when error occurred
     * @param code Complete source code for context
     * @param filePath Path to the source file
     * @param blockContext Context about unclosed block (function, if, while, etc.)
     * @param lexeme The specific token causing the error
     * @param expectedValue What was expected (if applicable)
     */
    static void error(const std::string &errorMessage,
                      int line,
                      int column,
                      InterpretationStage stage,
                      const std::string &code,
                      const std::string &filePath,
                      const std::optional<BlockContext> &blockContext,
                      const std::string &lexeme = "",
                      const std::string &expectedValue = "");

    /**
     * @brief Report pre-built error message
     * @param errorMessage Complete Message structure
     */
    static void error(const Message &errorMessage);

    /**
     * @brief Check if any errors have been reported
     * @return true if errors occurred, false otherwise
     */
    static bool hasError() { return hadError; }

    /**
     * @brief Reset error state for fresh error reporting
     */
    static void resetError() { 
        hadError = false; 
        reportedErrors.clear();
        collectedDiagnostics.clear();
        errorCount = 0;
        warningCount = 0;
    }

    /**
     * @brief Enable modern compiler-style diagnostics output
     */
    static void enableModernDiagnostics(bool enable) { useModernDiagnostics = enable; }

private:
    static std::vector<std::string> sourceCodeLines;
    static bool hadError;
    static std::set<std::string> reportedErrors;
    static bool debugMode;
    static bool useModernDiagnostics;
    static size_t errorCount;
    static size_t warningCount;
    
    // Modern diagnostics storage (internal only)
    struct Diagnostic {
        std::string code;
        std::string severity;  // "error", "warning", "note"
        std::string message;
        std::string filePath;
        int line;
        int column;
        std::string sourceSnippet;
        std::string hint;
    };
    static std::vector<Diagnostic> collectedDiagnostics;

    // Console and log output methods
    static void debugConsole(const Message &errorMessage);
    static void debugLog(const Message &errorMessage);

    // Modern diagnostics output (internal only)
    static void printModernDiagnostic(const Diagnostic &diag, bool useColor);
    static std::string createCaretLine(int column);

    // Helper methods
    static void printContextLines(std::ostream &out, int errorLine, int errorColumn);
    static std::vector<std::string> splitLines(const std::string &sourceCode);
    static std::string getTime();
    static std::string getSuggestion(const std::string &errorMessage,
                                     const std::string &expectedValue);
    static std::string stageToString(InterpretationStage stage);
    static std::string stageToErrorCode(InterpretationStage stage);

    // Create enhanced error message from components
    static Message createEnhancedErrorMessage(
        const std::string &errorMessage,
        int line,
        int column,
        InterpretationStage stage,
        const std::string &code,
        const std::string &filePath = "",
        const std::string &lexeme = "",
        const std::string &expectedValue = "",
        const std::optional<BlockContext> &blockContext = std::nullopt);
    
    // Collect diagnostic for modern output (internal only)
    static void collectDiagnostic(const std::string &code, const std::string &severity,
                                  const std::string &message, const std::string &filePath,
                                  int line, int column, const std::string &sourceSnippet,
                                  const std::string &hint);
};

} // namespace Error
} // namespace LM
