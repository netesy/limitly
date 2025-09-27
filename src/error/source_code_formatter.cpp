#include "source_code_formatter.hh"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace ErrorHandling {

SourceCodeFormatter::FormatOptions SourceCodeFormatter::getDefaultOptions() {
    return FormatOptions();
}

// ANSI color codes
const std::string SourceCodeFormatter::Colors::RESET = "\033[0m";
const std::string SourceCodeFormatter::Colors::BOLD = "\033[1m";
const std::string SourceCodeFormatter::Colors::RED = "\033[31m";
const std::string SourceCodeFormatter::Colors::GREEN = "\033[32m";
const std::string SourceCodeFormatter::Colors::BLUE = "\033[34m";
const std::string SourceCodeFormatter::Colors::YELLOW = "\033[33m";
const std::string SourceCodeFormatter::Colors::CYAN = "\033[36m";
const std::string SourceCodeFormatter::Colors::GRAY = "\033[90m";

// Unicode characters
const std::string SourceCodeFormatter::Unicode::ARROW_RIGHT = "→";
const std::string SourceCodeFormatter::Unicode::CARET_UP = "^";
const std::string SourceCodeFormatter::Unicode::TILDE = "~";
const std::string SourceCodeFormatter::Unicode::VERTICAL_BAR = "│";
const std::string SourceCodeFormatter::Unicode::HORIZONTAL_BAR = "─";

std::vector<std::string> SourceCodeFormatter::formatSourceContext(
    const std::string& sourceCode,
    int errorLine,
    int errorColumn,
    const FormatOptions& options)
{
    std::vector<std::string> result;
    std::vector<std::string> lines = splitIntoLines(sourceCode);
    
    if (lines.empty() || errorLine < 1 || errorLine > static_cast<int>(lines.size())) {
        return result;
    }
    
    // Calculate line range to display
    int startLine = std::max(1, errorLine - options.contextLinesBefore);
    int endLine = std::min(static_cast<int>(lines.size()), errorLine + options.contextLinesAfter);
    
    // Calculate line number width for alignment
    int lineNumberWidth = calculateLineNumberWidth(endLine);
    
    // Add context lines
    for (int lineNum = startLine; lineNum <= endLine; ++lineNum) {
        bool isErrorLine = (lineNum == errorLine);
        std::string line = lines[lineNum - 1]; // Convert to 0-based index
        
        // Expand tabs for consistent display
        line = expandTabs(line, options.tabWidth);
        
        // Format line number
        std::string linePrefix = formatLineNumber(lineNum, lineNumberWidth, isErrorLine, options);
        
        // Highlight the problematic token if this is the error line
        if (isErrorLine && errorColumn > 0) {
            line = highlightRange(line, errorColumn, errorColumn, options);
        }
        
        result.push_back(linePrefix + line);
        
        // Add visual indicator after error line
        if (isErrorLine && errorColumn > 0) {
            std::string indicator = createCaretLine(errorColumn, lineNumberWidth, options);
            result.push_back(indicator);
        }
    }
    
    return result;
}

std::vector<std::string> SourceCodeFormatter::formatTokenContext(
    const std::string& sourceCode,
    int errorLine,
    int errorColumn,
    int tokenLength,
    const FormatOptions& options)
{
    std::vector<std::string> result;
    std::vector<std::string> lines = splitIntoLines(sourceCode);
    
    if (lines.empty() || errorLine < 1 || errorLine > static_cast<int>(lines.size())) {
        return result;
    }
    
    // Calculate line range to display
    int startLine = std::max(1, errorLine - options.contextLinesBefore);
    int endLine = std::min(static_cast<int>(lines.size()), errorLine + options.contextLinesAfter);
    
    // Calculate line number width for alignment
    int lineNumberWidth = calculateLineNumberWidth(endLine);
    
    // Add context lines
    for (int lineNum = startLine; lineNum <= endLine; ++lineNum) {
        bool isErrorLine = (lineNum == errorLine);
        std::string line = lines[lineNum - 1]; // Convert to 0-based index
        
        // Expand tabs for consistent display
        line = expandTabs(line, options.tabWidth);
        
        // Format line number
        std::string linePrefix = formatLineNumber(lineNum, lineNumberWidth, isErrorLine, options);
        
        // Highlight the problematic token if this is the error line
        if (isErrorLine && errorColumn > 0) {
            int endColumn = errorColumn + std::max(1, tokenLength) - 1;
            line = highlightRange(line, errorColumn, endColumn, options);
        }
        
        result.push_back(linePrefix + line);
        
        // Add visual indicator after error line
        if (isErrorLine && errorColumn > 0) {
            int indicatorLength = std::max(1, tokenLength);
            std::string indicator = createUnderline(errorColumn, errorColumn + indicatorLength - 1, 
                                                  lineNumberWidth, options);
            result.push_back(indicator);
        }
    }
    
    return result;
}

std::vector<std::string> SourceCodeFormatter::formatRangeContext(
    const std::string& sourceCode,
    int errorLine,
    int startColumn,
    int endColumn,
    const FormatOptions& options)
{
    std::vector<std::string> result;
    std::vector<std::string> lines = splitIntoLines(sourceCode);
    
    if (lines.empty() || errorLine < 1 || errorLine > static_cast<int>(lines.size())) {
        return result;
    }
    
    // Calculate line range to display
    int startLine = std::max(1, errorLine - options.contextLinesBefore);
    int endLine = std::min(static_cast<int>(lines.size()), errorLine + options.contextLinesAfter);
    
    // Calculate line number width for alignment
    int lineNumberWidth = calculateLineNumberWidth(endLine);
    
    // Add context lines
    for (int lineNum = startLine; lineNum <= endLine; ++lineNum) {
        bool isErrorLine = (lineNum == errorLine);
        std::string line = lines[lineNum - 1]; // Convert to 0-based index
        
        // Expand tabs for consistent display
        line = expandTabs(line, options.tabWidth);
        
        // Format line number
        std::string linePrefix = formatLineNumber(lineNum, lineNumberWidth, isErrorLine, options);
        
        // Highlight the range if this is the error line
        if (isErrorLine && startColumn > 0 && endColumn > 0) {
            line = highlightRange(line, startColumn, endColumn, options);
        }
        
        result.push_back(linePrefix + line);
        
        // Add visual indicator after error line
        if (isErrorLine && startColumn > 0 && endColumn > 0) {
            std::string indicator = createUnderline(startColumn, endColumn, lineNumberWidth, options);
            result.push_back(indicator);
        }
    }
    
    return result;
}

std::string SourceCodeFormatter::createVisualIndicator(
    int column,
    int length,
    int lineNumberWidth,
    const FormatOptions& options)
{
    if (length <= 1) {
        return createCaretLine(column, lineNumberWidth, options);
    } else {
        return createUnderline(column, column + length - 1, lineNumberWidth, options);
    }
}

std::string SourceCodeFormatter::createCaretLine(
    int column,
    int lineNumberWidth,
    const FormatOptions& options)
{
    std::ostringstream oss;
    
    // Add line number spacing
    if (options.showLineNumbers) {
        oss << std::string(lineNumberWidth, ' ');
        oss << colorize(getVisualChar(Unicode::VERTICAL_BAR, '|', options.useUnicode), 
                       Colors::BLUE, options.useColors);
        oss << " ";
    }
    
    // Add spaces to align with the error column
    if (column > 1) {
        oss << std::string(column - 1, ' ');
    }
    
    // Add the caret
    oss << colorize(getVisualChar(Unicode::CARET_UP, '^', options.useUnicode), 
                   Colors::RED, options.useColors);
    
    return oss.str();
}

std::string SourceCodeFormatter::createUnderline(
    int startColumn,
    int endColumn,
    int lineNumberWidth,
    const FormatOptions& options)
{
    std::ostringstream oss;
    
    // Add line number spacing
    if (options.showLineNumbers) {
        oss << std::string(lineNumberWidth, ' ');
        oss << colorize(getVisualChar(Unicode::VERTICAL_BAR, '|', options.useUnicode), 
                       Colors::BLUE, options.useColors);
        oss << " ";
    }
    
    // Add spaces to align with the start column
    if (startColumn > 1) {
        oss << std::string(startColumn - 1, ' ');
    }
    
    // Add the underline
    int underlineLength = std::max(1, endColumn - startColumn + 1);
    std::string underlineChar = getVisualChar(Unicode::TILDE, '~', options.useUnicode);
    oss << colorize(std::string(underlineLength, underlineChar[0]), 
                   Colors::RED, options.useColors);
    
    return oss.str();
}

void SourceCodeFormatter::writeFormattedContext(
    std::ostream& out,
    const std::vector<std::string>& contextLines,
    const FormatOptions& options)
{
    for (const auto& line : contextLines) {
        out << line << std::endl;
    }
}

int SourceCodeFormatter::calculateLineNumberWidth(int maxLineNumber)
{
    if (maxLineNumber <= 0) return 1;
    
    int width = 0;
    int temp = maxLineNumber;
    while (temp > 0) {
        width++;
        temp /= 10;
    }
    return std::max(width, 1);
}

std::vector<std::string> SourceCodeFormatter::splitIntoLines(const std::string& sourceCode)
{
    std::vector<std::string> lines;
    std::istringstream stream(sourceCode);
    std::string line;
    
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    
    // Handle case where source code doesn't end with newline
    if (!sourceCode.empty() && sourceCode.back() != '\n' && sourceCode.back() != '\r') {
        // The last line was already added by getline
    }
    
    return lines;
}

std::string SourceCodeFormatter::expandTabs(const std::string& line, int tabWidth)
{
    std::string result;
    int column = 0;
    
    for (char c : line) {
        if (c == '\t') {
            // Calculate spaces needed to reach next tab stop
            int spacesToAdd = tabWidth - (column % tabWidth);
            result.append(spacesToAdd, ' ');
            column += spacesToAdd;
        } else {
            result += c;
            column++;
        }
    }
    
    return result;
}

int SourceCodeFormatter::getDisplayWidth(const std::string& text, int tabWidth)
{
    int width = 0;
    for (char c : text) {
        if (c == '\t') {
            width += tabWidth - (width % tabWidth);
        } else {
            width++;
        }
    }
    return width;
}

std::string SourceCodeFormatter::formatLineNumber(
    int lineNumber,
    int width,
    bool isErrorLine,
    const FormatOptions& options)
{
    std::ostringstream oss;
    
    if (options.showLineNumbers) {
        // Format line number with proper width
        oss << std::setw(width) << lineNumber;
        
        // Add separator
        if (isErrorLine) {
            oss << colorize(" " + getVisualChar(Unicode::ARROW_RIGHT, '>', options.useUnicode) + " ", 
                           Colors::RED, options.useColors);
        } else {
            oss << colorize(" " + getVisualChar(Unicode::VERTICAL_BAR, '|', options.useUnicode) + " ", 
                           Colors::BLUE, options.useColors);
        }
    }
    
    return oss.str();
}

std::string SourceCodeFormatter::colorize(const std::string& text, const std::string& color, bool useColors)
{
    if (!useColors) {
        return text;
    }
    return color + text + Colors::RESET;
}

std::string SourceCodeFormatter::highlightRange(
    const std::string& line,
    int startCol,
    int endCol,
    const FormatOptions& options)
{
    if (startCol < 1 || startCol > static_cast<int>(line.length()) || endCol < startCol) {
        return line;
    }
    
    // Adjust for 0-based indexing
    int start = startCol - 1;
    int end = std::min(endCol - 1, static_cast<int>(line.length()) - 1);
    
    if (!options.useColors) {
        return line;
    }
    
    std::string result;
    result += line.substr(0, start);
    result += colorize(line.substr(start, end - start + 1), Colors::RED + Colors::BOLD, true);
    if (end + 1 < static_cast<int>(line.length())) {
        result += line.substr(end + 1);
    }
    
    return result;
}

std::string SourceCodeFormatter::getVisualChar(const std::string& unicodeChar, char fallbackChar, bool useUnicode)
{
    return useUnicode ? unicodeChar : std::string(1, fallbackChar);
}

// Overloaded methods with default options
std::vector<std::string> SourceCodeFormatter::formatSourceContext(
    const std::string& sourceCode,
    int errorLine,
    int errorColumn)
{
    return formatSourceContext(sourceCode, errorLine, errorColumn, getDefaultOptions());
}

std::vector<std::string> SourceCodeFormatter::formatTokenContext(
    const std::string& sourceCode,
    int errorLine,
    int errorColumn,
    int tokenLength)
{
    return formatTokenContext(sourceCode, errorLine, errorColumn, tokenLength, getDefaultOptions());
}

std::vector<std::string> SourceCodeFormatter::formatRangeContext(
    const std::string& sourceCode,
    int errorLine,
    int startColumn,
    int endColumn)
{
    return formatRangeContext(sourceCode, errorLine, startColumn, endColumn, getDefaultOptions());
}

void SourceCodeFormatter::writeFormattedContext(
    std::ostream& out,
    const std::vector<std::string>& contextLines)
{
    writeFormattedContext(out, contextLines, getDefaultOptions());
}

} // namespace ErrorHandling