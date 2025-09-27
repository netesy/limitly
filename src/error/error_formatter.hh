#pragma once

#include "error_message.hh"
#include "error_code_generator.hh"
#include "contextual_hint_provider.hh"
#include "source_code_formatter.hh"
#include "error_catalog.hh"
#include <string>
#include <memory>

namespace ErrorHandling {

/**
 * @brief Central coordinator for creating enhanced error messages
 * 
 * The ErrorFormatter class serves as the main orchestrator that integrates
 * all error handling components to create comprehensive, structured error messages.
 * It coordinates ErrorCodeGenerator, ContextualHintProvider, SourceCodeFormatter,
 * and ErrorCatalog to produce complete ErrorMessage objects.
 */
class ErrorFormatter {
public:
    /**
     * @brief Configuration options for error message formatting
     */
    struct FormatterOptions {
        bool generateHints;             // Whether to generate contextual hints
        bool generateSuggestions;       // Whether to generate actionable suggestions
        bool includeSourceContext;      // Whether to include source code context
        bool generateCausedBy;          // Whether to generate "Caused by" messages
        bool useColors;                 // Whether to use colors in source context
        bool useUnicode;                // Whether to use Unicode characters
        int contextLinesBefore;         // Lines of context before error
        int contextLinesAfter;          // Lines of context after error
        
        FormatterOptions() 
            : generateHints(true), generateSuggestions(true), includeSourceContext(true),
              generateCausedBy(true), useColors(true), useUnicode(true),
              contextLinesBefore(2), contextLinesAfter(2) {}
    };
    
    /**
     * @brief Get default formatter options
     */
    static FormatterOptions getDefaultOptions();
    
    /**
     * @brief Create a complete enhanced error message
     * 
     * This is the main method that orchestrates all components to create
     * a comprehensive error message with all enhanced information.
     * 
     * @param errorMessage The basic error message text
     * @param line Line number where error occurred (1-based)
     * @param column Column number where error occurred (1-based)
     * @param stage The interpretation stage where error occurred
     * @param sourceCode Complete source code for context display
     * @param lexeme The specific token causing the issue (optional)
     * @param expectedValue What was expected (optional)
     * @param filePath Path to the source file (optional)
     * @param blockContext Block context for unclosed constructs (optional)
     * @param options Formatting options
     * @return Complete ErrorMessage with all enhanced information
     */
    static ErrorMessage createErrorMessage(
        const std::string& errorMessage,
        int line,
        int column,
        InterpretationStage stage,
        const std::string& sourceCode,
        const std::string& lexeme = "",
        const std::string& expectedValue = "",
        const std::string& filePath = "",
        const std::optional<BlockContext>& blockContext = std::nullopt,
        const FormatterOptions& options = getDefaultOptions()
    );
    
    /**
     * @brief Create error message from ErrorContext
     * 
     * Convenience method that creates an error message from a pre-built
     * ErrorContext object.
     * 
     * @param errorMessage The basic error message text
     * @param context The error context with all details
     * @param options Formatting options
     * @return Complete ErrorMessage with all enhanced information
     */
    static ErrorMessage createErrorMessage(
        const std::string& errorMessage,
        const ErrorContext& context,
        const FormatterOptions& options = getDefaultOptions()
    );
    
    /**
     * @brief Initialize the error formatting system
     * 
     * This method initializes all the underlying components (ErrorCatalog,
     * ContextualHintProvider) to ensure they are ready for use.
     */
    static void initialize();
    
    /**
     * @brief Check if the error formatting system is initialized
     * @return True if all components are initialized
     */
    static bool isInitialized();
    
    /**
     * @brief Create a minimal error message for cases where full context is not available
     * 
     * @param errorMessage The basic error message text
     * @param stage The interpretation stage where error occurred
     * @param filePath Path to the source file (optional)
     * @param line Line number (optional, 0 if unknown)
     * @param column Column number (optional, 0 if unknown)
     * @return Basic ErrorMessage with minimal information
     */
    static ErrorMessage createMinimalErrorMessage(
        const std::string& errorMessage,
        InterpretationStage stage,
        const std::string& filePath = "",
        int line = 0,
        int column = 0
    );

private:
    // Helper methods for different aspects of error message creation
    
    /**
     * @brief Generate error code and type for the error
     * @param errorMessage The error message text
     * @param stage The interpretation stage
     * @return Pair of (errorCode, errorType)
     */
    static std::pair<std::string, std::string> generateCodeAndType(
        const std::string& errorMessage,
        InterpretationStage stage
    );
    
    /**
     * @brief Generate contextual hint for the error
     * @param errorMessage The error message text
     * @param context The error context
     * @param definition Optional error definition from catalog
     * @param options Formatting options
     * @return Generated hint string
     */
    static std::string generateHint(
        const std::string& errorMessage,
        const ErrorContext& context,
        const ErrorDefinition* definition,
        const FormatterOptions& options
    );
    
    /**
     * @brief Generate actionable suggestion for the error
     * @param errorMessage The error message text
     * @param context The error context
     * @param definition Optional error definition from catalog
     * @param options Formatting options
     * @return Generated suggestion string
     */
    static std::string generateSuggestion(
        const std::string& errorMessage,
        const ErrorContext& context,
        const ErrorDefinition* definition,
        const FormatterOptions& options
    );
    
    /**
     * @brief Generate "Caused by" message for block-related errors
     * @param context The error context with block information
     * @param options Formatting options
     * @return "Caused by" message string
     */
    static std::string generateCausedBy(
        const ErrorContext& context,
        const FormatterOptions& options
    );
    
    /**
     * @brief Generate source code context lines
     * @param context The error context with source code
     * @param options Formatting options
     * @return Vector of formatted context lines
     */
    static std::vector<std::string> generateSourceContext(
        const ErrorContext& context,
        const FormatterOptions& options
    );
    
    /**
     * @brief Create ErrorContext from individual parameters
     * @param filePath Path to the source file
     * @param line Line number
     * @param column Column number
     * @param sourceCode Complete source code
     * @param lexeme The problematic token
     * @param expectedValue What was expected
     * @param stage The interpretation stage
     * @param blockContext Optional block context
     * @return Constructed ErrorContext
     */
    static ErrorContext createErrorContext(
        const std::string& filePath,
        int line,
        int column,
        const std::string& sourceCode,
        const std::string& lexeme,
        const std::string& expectedValue,
        InterpretationStage stage,
        const std::optional<BlockContext>& blockContext
    );
    
    /**
     * @brief Handle different error types and stages appropriately
     * @param errorMessage The error message
     * @param context The error context
     * @param options Formatting options
     * @return Adjusted context or processing flags
     */
    static ErrorContext handleErrorTypeSpecifics(
        const std::string& errorMessage,
        const ErrorContext& context,
        const FormatterOptions& options
    );
    
    // Static initialization flag
    static bool initialized;
};

} // namespace ErrorHandling