#include "console_formatter.hh"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <regex>

namespace ErrorHandling {

// ANSI color code definitions
const std::string ConsoleFormatter::Colors::RESET = "\033[0m";
const std::string ConsoleFormatter::Colors::BOLD = "\033[1m";
const std::string ConsoleFormatter::Colors::RED = "\033[31m";
const std::string ConsoleFormatter::Colors::GREEN = "\033[32m";
const std::string ConsoleFormatter::Colors::BLUE = "\033[34m";
const std::string ConsoleFormatter::Colors::YELLOW = "\033[33m";
const std::string ConsoleFormatter::Colors::CYAN = "\033[36m";
const std::string ConsoleFormatter::Colors::GRAY = "\033[90m";
const std::string ConsoleFormatter::Colors::BRIGHT_RED = "\033[91m";
const std::string ConsoleFormatter::Colors::BRIGHT_BLUE = "\033[94m";

ConsoleFormatter::ConsoleOptions ConsoleFormatter::getDefaultOptions() {
    return ConsoleOptions();
}

std::string ConsoleFormatter::formatErrorMessage(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    std::ostringstream result;
    
    // Format error header
    result << formatErrorHeader(errorMessage, options) << "\n";
    
    // Format file location if we have file path and line info
    if (!errorMessage.filePath.empty() && errorMessage.line > 0) {
        result << formatFileLocation(errorMessage, options) << "\n";
    }
    
    // Format source context if available
    if (!errorMessage.contextLines.empty()) {
        auto contextLines = formatSourceContext(errorMessage, options);
        for (const auto& line : contextLines) {
            result << line << "\n";
        }
    }
    
    // Add empty line before additional information if we have context
    if (!errorMessage.contextLines.empty() && 
        (!errorMessage.hint.empty() || !errorMessage.suggestion.empty() || !errorMessage.causedBy.empty())) {
        result << "\n";
    }
    
    // Format hint if available
    std::string hint = formatHint(errorMessage, options);
    if (!hint.empty()) {
        result << hint << "\n";
    }
    
    // Format suggestion if available
    std::string suggestion = formatSuggestion(errorMessage, options);
    if (!suggestion.empty()) {
        result << suggestion << "\n";
    }
    
    // Format "Caused by" section if available
    if (!errorMessage.causedBy.empty()) {
        auto causedByLines = formatCausedBy(errorMessage, options);
        for (const auto& line : causedByLines) {
            result << line << "\n";
        }
    }
    
    // Format file path footer if enabled and different from header
    std::string footer = formatFilePathFooter(errorMessage, options);
    if (!footer.empty()) {
        if (!errorMessage.hint.empty() || !errorMessage.suggestion.empty() || !errorMessage.causedBy.empty()) {
            result << "\n";
        }
        result << footer << "\n";
    }
    
    return result.str();
}

void ConsoleFormatter::writeErrorMessage(
    std::ostream& out,
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    out << formatErrorMessage(errorMessage, options);
}

std::string ConsoleFormatter::formatErrorHeader(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    std::ostringstream header;
    
    // Format: error[E102][SyntaxError]: Unexpected closing brace `}`
    header << colorize("error", Colors::BOLD + Colors::RED, options.useColors);
    header << colorize("[" + errorMessage.errorCode + "]", Colors::BOLD, options.useColors);
    header << colorize("[" + errorMessage.errorType + "]", Colors::BOLD, options.useColors);
    header << colorize(": ", Colors::BOLD, options.useColors);
    
    // Add the error description
    std::string description = errorMessage.description;
    
    // If we have a problematic token, ensure it's properly highlighted in the description
    if (!errorMessage.problematicToken.empty()) {
        std::string escapedToken = escapeToken(errorMessage.problematicToken);
        
        // Look for the token in the description and highlight it
        size_t tokenPos = description.find(errorMessage.problematicToken);
        if (tokenPos == std::string::npos) {
            // Token not found as-is, try with backticks
            tokenPos = description.find("`" + errorMessage.problematicToken + "`");
        }
        
        if (tokenPos != std::string::npos) {
            // Token found, make sure it's properly formatted
            if (description[tokenPos] != '`') {
                // Add backticks if not already present
                description.replace(tokenPos, errorMessage.problematicToken.length(), 
                                  "`" + escapedToken + "`");
            }
        } else {
            // Token not found in description, append it
            description += " `" + escapedToken + "`";
        }
    }
    
    header << description;
    
    return header.str();
}

std::string ConsoleFormatter::formatFileLocation(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    std::ostringstream location;
    
    // Format: --> src/utils.calc:15:113
    location << colorize("--> ", Colors::BLUE, options.useColors);
    location << colorize(errorMessage.filePath, Colors::BLUE, options.useColors);
    
    if (errorMessage.line > 0) {
        location << colorize(":", Colors::BLUE, options.useColors);
        location << colorize(std::to_string(errorMessage.line), Colors::BLUE, options.useColors);
        
        if (errorMessage.column > 0) {
            location << colorize(":", Colors::BLUE, options.useColors);
            location << colorize(std::to_string(errorMessage.column), Colors::BLUE, options.useColors);
        }
    }
    
    return location.str();
}

std::vector<std::string> ConsoleFormatter::formatSourceContext(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    std::vector<std::string> result;
    
    if (errorMessage.contextLines.empty()) {
        return result;
    }
    
    // Calculate line number width for alignment
    int lineNumberWidth = calculateLineNumberWidth(errorMessage.contextLines);
    
    // Add separator line before context
    result.push_back(createSeparatorLine(options));
    
    // Format each context line
    for (const auto& contextLine : errorMessage.contextLines) {
        std::string formatted = formatContextLine(contextLine, lineNumberWidth, options);
        result.push_back(formatted);
    }
    
    return result;
}

std::string ConsoleFormatter::formatHint(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    if (errorMessage.hint.empty()) {
        return "";
    }
    
    std::ostringstream hint;
    hint << colorize("Hint: ", Colors::BOLD + Colors::YELLOW, options.useColors);
    hint << errorMessage.hint;
    
    return hint.str();
}

std::string ConsoleFormatter::formatSuggestion(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    if (errorMessage.suggestion.empty()) {
        return "";
    }
    
    std::ostringstream suggestion;
    suggestion << colorize("Suggestion: ", Colors::BOLD + Colors::GREEN, options.useColors);
    suggestion << errorMessage.suggestion;
    
    return suggestion.str();
}

std::vector<std::string> ConsoleFormatter::formatCausedBy(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    std::vector<std::string> result;
    
    if (errorMessage.causedBy.empty()) {
        return result;
    }
    
    // Split the causedBy message into lines
    std::istringstream stream(errorMessage.causedBy);
    std::string line;
    bool isFirstLine = true;
    
    while (std::getline(stream, line)) {
        if (isFirstLine) {
            // First line gets the "Caused by:" prefix
            std::ostringstream causedByLine;
            causedByLine << colorize("Caused by: ", Colors::BOLD + Colors::BRIGHT_BLUE, options.useColors);
            causedByLine << line;
            result.push_back(causedByLine.str());
            isFirstLine = false;
        } else {
            // Subsequent lines are indented to align with the content
            std::string indentedLine = std::string(11, ' ') + line; // "Caused by: " is 11 chars
            result.push_back(indentedLine);
        }
    }
    
    return result;
}

std::string ConsoleFormatter::formatFilePathFooter(
    const ErrorMessage& errorMessage,
    const ConsoleOptions& options)
{
    if (!options.showFilePath || errorMessage.filePath.empty()) {
        return "";
    }
    
    // Only show footer if we have additional information (hint, suggestion, or causedBy)
    // and the file path wasn't already shown in the header
    if (errorMessage.hint.empty() && errorMessage.suggestion.empty() && errorMessage.causedBy.empty()) {
        return "";
    }
    
    std::ostringstream footer;
    footer << colorize("File: ", Colors::BOLD + Colors::BLUE, options.useColors);
    footer << colorize(errorMessage.filePath, Colors::BLUE, options.useColors);
    
    return footer.str();
}

// Private helper methods

std::string ConsoleFormatter::colorize(const std::string& text, const std::string& color, bool useColors) {
    if (!useColors) {
        return text;
    }
    return color + text + Colors::RESET;
}

std::vector<std::string> ConsoleFormatter::wrapText(const std::string& text, int maxWidth, const std::string& indent) {
    std::vector<std::string> result;
    
    if (text.empty()) {
        return result;
    }
    
    std::istringstream words(text);
    std::string word;
    std::string currentLine = indent;
    
    while (words >> word) {
        // Check if adding this word would exceed the width
        if (!currentLine.empty() && currentLine != indent && 
            static_cast<int>(currentLine.length() + word.length() + 1) > maxWidth) {
            // Start a new line
            result.push_back(currentLine);
            currentLine = indent + word;
        } else {
            // Add word to current line
            if (currentLine != indent) {
                currentLine += " ";
            }
            currentLine += word;
        }
    }
    
    // Add the last line if it's not empty
    if (!currentLine.empty()) {
        result.push_back(currentLine);
    }
    
    return result;
}

int ConsoleFormatter::calculateLineNumberWidth(const std::vector<std::string>& contextLines) {
    int maxLineNumber = 0;
    
    for (const auto& line : contextLines) {
        int lineNumber = extractLineNumber(line);
        if (lineNumber > maxLineNumber) {
            maxLineNumber = lineNumber;
        }
    }
    
    // Calculate width needed for the highest line number
    if (maxLineNumber == 0) {
        return 2; // Default minimum width
    }
    
    return std::to_string(maxLineNumber).length();
}

int ConsoleFormatter::extractLineNumber(const std::string& contextLine) {
    // Context lines from SourceCodeFormatter typically start with line number
    // Format: "15 | some code" or "   | ^"
    
    std::regex lineNumberRegex(R"(^\s*(\d+)\s*\|)");
    std::smatch match;
    
    if (std::regex_search(contextLine, match, lineNumberRegex)) {
        try {
            return std::stoi(match[1].str());
        } catch (const std::exception&) {
            return 0;
        }
    }
    
    return 0;
}

std::string ConsoleFormatter::formatContextLine(
    const std::string& contextLine,
    int lineNumberWidth,
    const ConsoleOptions& options)
{
    // Context lines are already formatted by SourceCodeFormatter
    // We just need to apply colors if enabled
    
    if (!options.useColors) {
        return contextLine;
    }
    
    // Check if this is a line number line or an indicator line
    std::regex lineNumberRegex(R"(^(\s*)(\d+)(\s*\|\s*)(.*)$)");
    std::regex indicatorRegex(R"(^(\s*\|\s*)([^\w\s].*)$)");
    
    std::smatch match;
    
    if (std::regex_match(contextLine, match, lineNumberRegex)) {
        // This is a source code line with line number
        std::ostringstream formatted;
        formatted << match[1].str(); // Leading whitespace
        formatted << colorize(match[2].str(), Colors::CYAN, true); // Line number
        formatted << colorize(match[3].str(), Colors::GRAY, true); // " | "
        formatted << match[4].str(); // Source code (keep original formatting)
        return formatted.str();
    } else if (std::regex_match(contextLine, match, indicatorRegex)) {
        // This is an indicator line (caret, underline, etc.)
        std::ostringstream formatted;
        formatted << colorize(match[1].str(), Colors::GRAY, true); // " | "
        formatted << colorize(match[2].str(), Colors::BRIGHT_RED, true); // Indicator
        return formatted.str();
    }
    
    // Default: return as-is with gray coloring for separator lines
    if (contextLine.find("|") != std::string::npos && contextLine.find_first_not_of(" |") == std::string::npos) {
        return colorize(contextLine, Colors::GRAY, true);
    }
    
    return contextLine;
}

std::string ConsoleFormatter::createSeparatorLine(const ConsoleOptions& options) {
    std::string separator = "   |";
    return colorize(separator, Colors::GRAY, options.useColors);
}

std::string ConsoleFormatter::escapeToken(const std::string& token) {
    // Escape special characters for display
    std::string escaped = token;
    
    // Replace common escape sequences
    size_t pos = 0;
    while ((pos = escaped.find('\n', pos)) != std::string::npos) {
        escaped.replace(pos, 1, "\\n");
        pos += 2;
    }
    
    pos = 0;
    while ((pos = escaped.find('\t', pos)) != std::string::npos) {
        escaped.replace(pos, 1, "\\t");
        pos += 2;
    }
    
    pos = 0;
    while ((pos = escaped.find('\r', pos)) != std::string::npos) {
        escaped.replace(pos, 1, "\\r");
        pos += 2;
    }
    
    return escaped;
}

} // namespace ErrorHandling