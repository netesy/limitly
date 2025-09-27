#pragma once

#include "error_message.hh"
#include <string>
#include <ostream>
#include <sstream>

namespace ErrorHandling {

/**
 * @brief Console formatter for human-readable error output
 * 
 * This class formats ErrorMessage objects into human-readable console output
 * following the specified error message format with proper spacing, alignment,
 * and visual hierarchy. Supports color output for enhanced readability.
 */
class ConsoleFormatter {
public:
    /**
     * @brief Configuration options for console formatting
     */
    struct ConsoleOptions {
        bool useColors;             // Whether to use ANSI color codes
        bool showFilePath;          // Whether to show file path at the end
        bool compactMode;           // Whether to use compact formatting
        int maxLineWidth;           // Maximum line width for wrapping
        bool showLineNumbers;       // Whether to show line numbers in context
        
        ConsoleOptions() 
            : useColors(true), showFilePath(true), compactMode(false),
              maxLineWidth(120), showLineNumbers(true) {}
    };
    
    /**
     * @brief Get default console formatting options
     */
    static ConsoleOptions getDefaultOptions();
    
    /**
     * @brief Format an error message for console output
     * 
     * Produces the complete human-readable error message following the format:
     * error[E102][SyntaxError]: Unexpected closing brace `}`
     * --> src/utils.calc:15:113
     *    |
     * 14 |     let x = 514
     * 15 |     return x + 1;
     * 15 | }
     *    | ^ unexpected closing brace
     * 
     * Hint: It looks like you're missing an opening `{` before this line.
     * Suggestion: Did you forget to wrap a block like an `if`, `while`, or `function`?
     * Caused by: Unterminated block starting at line 11:
     * 11 | function compute(x, y) =>
     *    | ----------------------- unclosed block starts here
     * 
     * File: src/utils.calc
     * 
     * @param errorMessage The error message to format
     * @param options Formatting options
     * @return Formatted error message string
     */
    static std::string formatErrorMessage(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options = getDefaultOptions()
    );
    
    /**
     * @brief Write formatted error message to output stream
     * @param out Output stream to write to
     * @param errorMessage The error message to format
     * @param options Formatting options
     */
    static void writeErrorMessage(
        std::ostream& out,
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options = getDefaultOptions()
    );
    
    /**
     * @brief Format the error header line
     * @param errorMessage The error message
     * @param options Formatting options
     * @return Formatted header (e.g., "error[E102][SyntaxError]: Unexpected closing brace `}`")
     */
    static std::string formatErrorHeader(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options
    );
    
    /**
     * @brief Format the file location line
     * @param errorMessage The error message
     * @param options Formatting options
     * @return Formatted location (e.g., "--> src/utils.calc:15:113")
     */
    static std::string formatFileLocation(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options
    );
    
    /**
     * @brief Format the source code context section
     * @param errorMessage The error message
     * @param options Formatting options
     * @return Vector of formatted context lines
     */
    static std::vector<std::string> formatSourceContext(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options
    );
    
    /**
     * @brief Format the hint section
     * @param errorMessage The error message
     * @param options Formatting options
     * @return Formatted hint line (empty if no hint)
     */
    static std::string formatHint(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options
    );
    
    /**
     * @brief Format the suggestion section
     * @param errorMessage The error message
     * @param options Formatting options
     * @return Formatted suggestion line (empty if no suggestion)
     */
    static std::string formatSuggestion(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options
    );
    
    /**
     * @brief Format the "Caused by" section
     * @param errorMessage The error message
     * @param options Formatting options
     * @return Vector of formatted "Caused by" lines (empty if no caused by info)
     */
    static std::vector<std::string> formatCausedBy(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options
    );
    
    /**
     * @brief Format the file path footer
     * @param errorMessage The error message
     * @param options Formatting options
     * @return Formatted file path line (empty if disabled or no file path)
     */
    static std::string formatFilePathFooter(
        const ErrorMessage& errorMessage,
        const ConsoleOptions& options
    );

private:
    // ANSI color codes for different error message components
    struct Colors {
        static const std::string RESET;
        static const std::string BOLD;
        static const std::string RED;           // Error header
        static const std::string GREEN;         // Suggestions
        static const std::string BLUE;          // File paths
        static const std::string YELLOW;        // Hints
        static const std::string CYAN;          // Line numbers
        static const std::string GRAY;          // Context lines
        static const std::string BRIGHT_RED;    // Error indicators
        static const std::string BRIGHT_BLUE;   // Caused by
    };
    
    /**
     * @brief Apply color formatting to text
     * @param text The text to colorize
     * @param color The color code to apply
     * @param useColors Whether colors are enabled
     * @return Colorized text (or original if colors disabled)
     */
    static std::string colorize(const std::string& text, const std::string& color, bool useColors);
    
    /**
     * @brief Wrap text to specified width while preserving indentation
     * @param text The text to wrap
     * @param maxWidth Maximum line width
     * @param indent Indentation to preserve
     * @return Vector of wrapped lines
     */
    static std::vector<std::string> wrapText(const std::string& text, int maxWidth, const std::string& indent = "");
    
    /**
     * @brief Calculate the width needed for line number display
     * @param contextLines The context lines to analyze
     * @return Width needed for line numbers
     */
    static int calculateLineNumberWidth(const std::vector<std::string>& contextLines);
    
    /**
     * @brief Extract line number from a formatted context line
     * @param contextLine A formatted context line
     * @return Line number (0 if not found)
     */
    static int extractLineNumber(const std::string& contextLine);
    
    /**
     * @brief Format a single context line with proper alignment
     * @param contextLine The context line to format
     * @param lineNumberWidth Width for line number alignment
     * @param options Formatting options
     * @return Formatted context line
     */
    static std::string formatContextLine(
        const std::string& contextLine,
        int lineNumberWidth,
        const ConsoleOptions& options
    );
    
    /**
     * @brief Create the separator line between sections
     * @param options Formatting options
     * @return Separator line (e.g., "   |")
     */
    static std::string createSeparatorLine(const ConsoleOptions& options);
    
    /**
     * @brief Escape special characters in token display
     * @param token The token to escape
     * @return Escaped token for display
     */
    static std::string escapeToken(const std::string& token);
};

} // namespace ErrorHandling