#pragma once

#include <string>
#include <vector>
#include <optional>

// Forward declaration to avoid circular dependency
enum class InterpretationStage { SCANNING, PARSING, SYNTAX, SEMANTIC, BYTECODE, INTERPRETING, COMPILING };

namespace ErrorHandling {

/**
 * @brief Represents context information about a block structure (function, if, while, etc.)
 * Used for tracking unclosed constructs and providing "Caused by" messages
 */
struct BlockContext {
    std::string blockType;      // "function", "if", "while", "for", "class", etc.
    int startLine;              // Line where the block starts
    int startColumn;            // Column where the block starts
    std::string startLexeme;    // The opening token/keyword that started the block
    
    BlockContext() = default;
    BlockContext(const std::string& type, int line, int column, const std::string& lexeme)
        : blockType(type), startLine(line), startColumn(column), startLexeme(lexeme) {}
};

/**
 * @brief Enhanced context information for error reporting
 * Contains all the contextual information needed to generate comprehensive error messages
 */
struct ErrorContext {
    std::string filePath;                           // Path to the source file
    int line;                                       // Line number where error occurred
    int column;                                     // Column number where error occurred
    std::string sourceCode;                         // Complete source code for context display
    std::string lexeme;                             // The specific token causing the issue
    std::string expectedValue;                      // What was expected (if applicable)
    InterpretationStage stage;                      // Stage where the error occurred
    std::optional<BlockContext> blockContext;      // Block context for unclosed constructs
    
    ErrorContext() = default;
    ErrorContext(const std::string& file, int ln, int col, const std::string& code,
                 const std::string& lex, const std::string& expected, InterpretationStage st)
        : filePath(file), line(ln), column(col), sourceCode(code), 
          lexeme(lex), expectedValue(expected), stage(st) {}
};

/**
 * @brief Definition of an error type in the error catalog
 * Contains templates and patterns for generating consistent error messages
 */
struct ErrorDefinition {
    std::string code;                               // Error code (e.g., "E102")
    std::string type;                               // Error type (e.g., "SyntaxError")
    std::string pattern;                            // Pattern to match error message
    std::string hintTemplate;                       // Template for hint generation
    std::string suggestionTemplate;                 // Template for suggestion generation
    std::vector<std::string> commonCauses;          // Common root causes for this error
    
    ErrorDefinition() = default;
    ErrorDefinition(const std::string& errorCode, const std::string& errorType,
                   const std::string& messagePattern, const std::string& hint,
                   const std::string& suggestion, const std::vector<std::string>& causes = {})
        : code(errorCode), type(errorType), pattern(messagePattern),
          hintTemplate(hint), suggestionTemplate(suggestion), commonCauses(causes) {}
};

/**
 * @brief Complete structured error message with all enhanced information
 * This is the main data structure that contains all the information needed
 * for generating both human-readable and machine-readable error output
 */
struct ErrorMessage {
    std::string errorCode;                          // Unique error code (e.g., "E102")
    std::string errorType;                          // Error type (e.g., "SyntaxError")
    std::string description;                        // Main error description
    std::string filePath;                           // Source file path
    int line;                                       // Line number
    int column;                                     // Column number
    std::string problematicToken;                   // The specific token causing the issue
    std::string hint;                               // Contextual hint about the error
    std::string suggestion;                         // Actionable suggestion for fixing
    std::string causedBy;                           // Root cause information (for block errors)
    std::vector<std::string> contextLines;          // Source code context lines
    InterpretationStage stage;                      // Stage where error occurred
    
    // Constructor with all required fields
    ErrorMessage(const std::string& code, const std::string& type, const std::string& desc,
                const std::string& file, int ln, int col, const std::string& token,
                InterpretationStage errorStage)
        : errorCode(code), errorType(type), description(desc), filePath(file),
          line(ln), column(col), problematicToken(token), stage(errorStage) {}
    
    // Default constructor
    ErrorMessage() : line(0), column(0), stage(InterpretationStage::SCANNING) {}
    
    // Method to check if this is a complete error message
    bool isComplete() const {
        return !errorCode.empty() && !errorType.empty() && !description.empty() && 
               line > 0 && column > 0;
    }
    
    // Method to check if enhanced information is available
    bool hasEnhancedInfo() const {
        return !hint.empty() || !suggestion.empty() || !causedBy.empty() || !contextLines.empty();
    }
};

} // namespace ErrorHandling