#pragma once

#include "error_message.hh"
#include <string>
#include <vector>
#include <ostream>

namespace ErrorHandling {

/**
 * @brief Enhanced source code formatter for error messages
 * 
 * This class provides advanced source code context formatting with:
 * - Line numbers and proper alignment
 * - Visual indicators using Unicode characters
 * - Multi-line context display
 * - Token and range highlighting
 * - Support for different output formats
 */
class SourceCodeFormatter {
public:
    /**
     * @brief Configuration options for source code formatting
     */
    struct FormatOptions {
        int contextLinesBefore;     // Number of lines to show before error
        int contextLinesAfter;      // Number of lines to show after error
        bool useColors;             // Whether to use ANSI color codes
        bool useUnicode;            // Whether to use Unicode characters
        bool showLineNumbers;       // Whether to show line numbers
        int tabWidth;               // Tab width for display
        bool highlightRange;        // Whether to highlight a range vs single token
        int rangeStart;             // Start column for range highlighting
        int rangeEnd;               // End column for range highlighting
        
        FormatOptions() : contextLinesBefore(2), contextLinesAfter(2), useColors(true),
                         useUnicode(true), showLineNumbers(true), tabWidth(4),
                         highlightRange(false), rangeStart(0), rangeEnd(0) {}
    };
    
    /**
     * @brief Get default formatting options
     */
    static FormatOptions getDefaultOptions();
    
    /**
     * @brief Extract and format source code context with line numbers
     * @param sourceCode The complete source code
     * @param errorLine The line where the error occurred (1-based)
     * @param errorColumn The column where the error occurred (1-based)
     * @param options Formatting options
     * @return Vector of formatted context lines
     */
    static std::vector<std::string> formatSourceContext(
        const std::string& sourceCode,
        int errorLine,
        int errorColumn,
        const FormatOptions& options
    );
    
    // Overload with default options
    static std::vector<std::string> formatSourceContext(
        const std::string& sourceCode,
        int errorLine,
        int errorColumn
    );
    
    /**
     * @brief Format source context for a specific token
     * @param sourceCode The complete source code
     * @param errorLine The line where the error occurred
     * @param errorColumn The column where the error occurred
     * @param tokenLength Length of the problematic token
     * @param options Formatting options
     * @return Vector of formatted context lines
     */
    static std::vector<std::string> formatTokenContext(
        const std::string& sourceCode,
        int errorLine,
        int errorColumn,
        int tokenLength,
        const FormatOptions& options
    );
    
    static std::vector<std::string> formatTokenContext(
        const std::string& sourceCode,
        int errorLine,
        int errorColumn,
        int tokenLength
    );
    
    /**
     * @brief Format source context for a range of characters
     * @param sourceCode The complete source code
     * @param errorLine The line where the error occurred
     * @param startColumn Start column of the range
     * @param endColumn End column of the range
     * @param options Formatting options
     * @return Vector of formatted context lines
     */
    static std::vector<std::string> formatRangeContext(
        const std::string& sourceCode,
        int errorLine,
        int startColumn,
        int endColumn,
        const FormatOptions& options
    );
    
    static std::vector<std::string> formatRangeContext(
        const std::string& sourceCode,
        int errorLine,
        int startColumn,
        int endColumn
    );
    
    /**
     * @brief Create visual indicators for pointing to error location
     * @param column The column to point to (1-based)
     * @param length Length of the indicator (for ranges)
     * @param lineNumberWidth Width of line number column for alignment
     * @param options Formatting options
     * @return Formatted indicator line
     */
    static std::string createVisualIndicator(
        int column,
        int length,
        int lineNumberWidth,
        const FormatOptions& options
    );
    
    /**
     * @brief Create a caret line pointing to specific column
     * @param column The column to point to (1-based)
     * @param lineNumberWidth Width of line number column for alignment
     * @param options Formatting options
     * @return Formatted caret line (e.g., "   | ^")
     */
    static std::string createCaretLine(
        int column,
        int lineNumberWidth,
        const FormatOptions& options
    );
    
    /**
     * @brief Create an underline for highlighting ranges
     * @param startColumn Start column for underline
     * @param endColumn End column for underline
     * @param lineNumberWidth Width of line number column for alignment
     * @param options Formatting options
     * @return Formatted underline (e.g., "   | ~~~")
     */
    static std::string createUnderline(
        int startColumn,
        int endColumn,
        int lineNumberWidth,
        const FormatOptions& options
    );
    
    /**
     * @brief Write formatted source context to output stream
     * @param out Output stream to write to
     * @param contextLines Vector of formatted context lines
     * @param options Formatting options
     */
    static void writeFormattedContext(
        std::ostream& out,
        const std::vector<std::string>& contextLines,
        const FormatOptions& options
    );
    
    static void writeFormattedContext(
        std::ostream& out,
        const std::vector<std::string>& contextLines
    );
    
    /**
     * @brief Calculate the width needed for line numbers
     * @param maxLineNumber The highest line number to display
     * @return Width needed for line number column
     */
    static int calculateLineNumberWidth(int maxLineNumber);
    
    /**
     * @brief Split source code into individual lines
     * @param sourceCode The source code to split
     * @return Vector of individual lines
     */
    static std::vector<std::string> splitIntoLines(const std::string& sourceCode);
    
    /**
     * @brief Expand tabs to spaces for consistent display
     * @param line The line to process
     * @param tabWidth Width of tabs in spaces
     * @return Line with tabs expanded to spaces
     */
    static std::string expandTabs(const std::string& line, int tabWidth = 4);
    
    /**
     * @brief Get the display width of a string (accounting for tabs)
     * @param text The text to measure
     * @param tabWidth Width of tabs in spaces
     * @return Display width of the text
     */
    static int getDisplayWidth(const std::string& text, int tabWidth = 4);
    
    /**
     * @brief Create a formatted line number prefix
     * @param lineNumber The line number to format
     * @param width The width to pad to
     * @param isErrorLine Whether this is the error line (for highlighting)
     * @param options Formatting options
     * @return Formatted line number prefix (e.g., " 42 | ")
     */
    static std::string formatLineNumber(
        int lineNumber,
        int width,
        bool isErrorLine,
        const FormatOptions& options
    );

private:
    // ANSI color codes for different elements
    struct Colors {
        static const std::string RESET;
        static const std::string BOLD;
        static const std::string RED;
        static const std::string GREEN;
        static const std::string BLUE;
        static const std::string YELLOW;
        static const std::string CYAN;
        static const std::string GRAY;
    };
    
    // Unicode characters for visual indicators
    struct Unicode {
        static const std::string ARROW_RIGHT;      // →
        static const std::string CARET_UP;         // ^
        static const std::string TILDE;            // ~
        static const std::string VERTICAL_BAR;     // │
        static const std::string HORIZONTAL_BAR;   // ─
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
     * @brief Highlight a specific range within a line
     * @param line The line to highlight
     * @param startCol Start column for highlighting (1-based)
     * @param endCol End column for highlighting (1-based)
     * @param options Formatting options
     * @return Line with highlighted range
     */
    static std::string highlightRange(
        const std::string& line,
        int startCol,
        int endCol,
        const FormatOptions& options
    );
    
    /**
     * @brief Get the appropriate visual character based on options
     * @param unicodeChar The Unicode character to use
     * @param fallbackChar The ASCII fallback character
     * @param useUnicode Whether Unicode is enabled
     * @return The appropriate character to use
     */
    static std::string getVisualChar(const std::string& unicodeChar, char fallbackChar, bool useUnicode);
};

} // namespace ErrorHandling