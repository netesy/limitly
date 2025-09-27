#include "error_formatter.hh"
#include <algorithm>
#include <sstream>

namespace ErrorHandling {

// Static member initialization
bool ErrorFormatter::initialized = false;

ErrorFormatter::FormatterOptions ErrorFormatter::getDefaultOptions() {
    return FormatterOptions();
}

ErrorMessage ErrorFormatter::createErrorMessage(
    const std::string& errorMessage,
    int line,
    int column,
    InterpretationStage stage,
    const std::string& sourceCode,
    const std::string& lexeme,
    const std::string& expectedValue,
    const std::string& filePath,
    const std::optional<BlockContext>& blockContext,
    const FormatterOptions& options)
{
    // Ensure the system is initialized
    if (!initialized) {
        initialize();
    }
    
    // Create error context from parameters
    ErrorContext context = createErrorContext(
        filePath, line, column, sourceCode, lexeme, expectedValue, stage, blockContext
    );
    
    return createErrorMessage(errorMessage, context, options);
}

ErrorMessage ErrorFormatter::createErrorMessage(
    const std::string& errorMessage,
    const ErrorContext& context,
    const FormatterOptions& options)
{
    // Ensure the system is initialized
    if (!initialized) {
        initialize();
    }
    
    // Handle error type specifics and adjust context if needed
    ErrorContext adjustedContext = handleErrorTypeSpecifics(errorMessage, context, options);
    
    // Generate error code and type
    auto [errorCode, errorType] = generateCodeAndType(errorMessage, adjustedContext.stage);
    
    // Create the base error message
    ErrorMessage result(errorCode, errorType, errorMessage, adjustedContext.filePath,
                       adjustedContext.line, adjustedContext.column, adjustedContext.lexeme,
                       adjustedContext.stage);
    
    // Look up error definition from catalog
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    const ErrorDefinition* definition = catalog.lookupByMessage(errorMessage, adjustedContext.stage);
    
    // Generate enhanced information based on options
    if (options.generateHints) {
        result.hint = generateHint(errorMessage, adjustedContext, definition, options);
    }
    
    if (options.generateSuggestions) {
        result.suggestion = generateSuggestion(errorMessage, adjustedContext, definition, options);
    }
    
    if (options.generateCausedBy && adjustedContext.blockContext.has_value()) {
        result.causedBy = generateCausedBy(adjustedContext, options);
    }
    
    if (options.includeSourceContext && !adjustedContext.sourceCode.empty()) {
        result.contextLines = generateSourceContext(adjustedContext, options);
    }
    
    return result;
}

void ErrorFormatter::initialize() {
    if (initialized) {
        return;
    }
    
    // Initialize all underlying components
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    if (!catalog.isInitialized()) {
        catalog.initialize();
    }
    
    ContextualHintProvider& hintProvider = ContextualHintProvider::getInstance();
    if (!hintProvider.isInitialized()) {
        hintProvider.initialize();
    }
    
    initialized = true;
}

bool ErrorFormatter::isInitialized() {
    return initialized && 
           ErrorCatalog::getInstance().isInitialized() &&
           ContextualHintProvider::getInstance().isInitialized();
}

ErrorMessage ErrorFormatter::createMinimalErrorMessage(
    const std::string& errorMessage,
    InterpretationStage stage,
    const std::string& filePath,
    int line,
    int column)
{
    // Ensure the system is initialized
    if (!initialized) {
        initialize();
    }
    
    // Generate error code and type
    auto [errorCode, errorType] = generateCodeAndType(errorMessage, stage);
    
    // Create minimal error message
    ErrorMessage result(errorCode, errorType, errorMessage, filePath, line, column, "", stage);
    
    return result;
}

// Private helper methods

std::pair<std::string, std::string> ErrorFormatter::generateCodeAndType(
    const std::string& errorMessage,
    InterpretationStage stage)
{
    std::string errorCode = ErrorCodeGenerator::generateErrorCode(stage, errorMessage);
    std::string errorType = ErrorCodeGenerator::getErrorType(stage);
    
    return {errorCode, errorType};
}

std::string ErrorFormatter::generateHint(
    const std::string& errorMessage,
    const ErrorContext& context,
    const ErrorDefinition* definition,
    const FormatterOptions& options)
{
    if (!options.generateHints) {
        return "";
    }
    
    ContextualHintProvider& hintProvider = ContextualHintProvider::getInstance();
    return hintProvider.generateHint(errorMessage, context, definition);
}

std::string ErrorFormatter::generateSuggestion(
    const std::string& errorMessage,
    const ErrorContext& context,
    const ErrorDefinition* definition,
    const FormatterOptions& options)
{
    if (!options.generateSuggestions) {
        return "";
    }
    
    ContextualHintProvider& hintProvider = ContextualHintProvider::getInstance();
    return hintProvider.generateSuggestion(errorMessage, context, definition);
}

std::string ErrorFormatter::generateCausedBy(
    const ErrorContext& context,
    const FormatterOptions& options)
{
    if (!options.generateCausedBy || !context.blockContext.has_value()) {
        return "";
    }
    
    ContextualHintProvider& hintProvider = ContextualHintProvider::getInstance();
    return hintProvider.generateCausedByMessage(context);
}

std::vector<std::string> ErrorFormatter::generateSourceContext(
    const ErrorContext& context,
    const FormatterOptions& options)
{
    if (!options.includeSourceContext || context.sourceCode.empty()) {
        return {};
    }
    
    // Configure source code formatter options
    SourceCodeFormatter::FormatOptions formatOptions;
    formatOptions.contextLinesBefore = options.contextLinesBefore;
    formatOptions.contextLinesAfter = options.contextLinesAfter;
    formatOptions.useColors = options.useColors;
    formatOptions.useUnicode = options.useUnicode;
    formatOptions.showLineNumbers = true;
    
    // Determine the appropriate formatting method based on lexeme length
    if (!context.lexeme.empty() && context.lexeme.length() > 1) {
        // Use token context for multi-character tokens
        return SourceCodeFormatter::formatTokenContext(
            context.sourceCode, context.line, context.column, 
            static_cast<int>(context.lexeme.length()), formatOptions
        );
    } else {
        // Use simple source context for single characters or unknown tokens
        return SourceCodeFormatter::formatSourceContext(
            context.sourceCode, context.line, context.column, formatOptions
        );
    }
}

ErrorContext ErrorFormatter::createErrorContext(
    const std::string& filePath,
    int line,
    int column,
    const std::string& sourceCode,
    const std::string& lexeme,
    const std::string& expectedValue,
    InterpretationStage stage,
    const std::optional<BlockContext>& blockContext)
{
    ErrorContext context;
    context.filePath = filePath;
    context.line = line;
    context.column = column;
    context.sourceCode = sourceCode;
    context.lexeme = lexeme;
    context.expectedValue = expectedValue;
    context.stage = stage;
    context.blockContext = blockContext;
    
    return context;
}

ErrorContext ErrorFormatter::handleErrorTypeSpecifics(
    const std::string& errorMessage,
    const ErrorContext& context,
    const FormatterOptions& options)
{
    ErrorContext adjustedContext = context;
    
    // Handle specific error types that might need context adjustments
    
    // For block-related errors, ensure we have proper block context
    if (errorMessage.find("brace") != std::string::npos || 
        errorMessage.find("block") != std::string::npos) {
        
        // If we don't have block context but this seems like a block error,
        // try to infer it from the error message and lexeme
        if (!adjustedContext.blockContext.has_value()) {
            if (adjustedContext.lexeme == "}" || errorMessage.find("closing brace") != std::string::npos) {
                // This might be an unclosed block error
                // We could try to find the opening block, but for now just note it
                BlockContext inferredBlock;
                inferredBlock.blockType = "unknown";
                inferredBlock.startLine = std::max(1, adjustedContext.line - 5); // Guess
                inferredBlock.startColumn = 1;
                inferredBlock.startLexeme = "{";
                adjustedContext.blockContext = inferredBlock;
            }
        }
    }
    
    // For syntax errors, ensure we have the problematic token
    if (adjustedContext.stage == InterpretationStage::PARSING && 
        adjustedContext.lexeme.empty() && 
        errorMessage.find("Unexpected") != std::string::npos) {
        
        // Try to extract the token from the error message
        size_t tokenStart = errorMessage.find("'");
        if (tokenStart != std::string::npos) {
            size_t tokenEnd = errorMessage.find("'", tokenStart + 1);
            if (tokenEnd != std::string::npos) {
                adjustedContext.lexeme = errorMessage.substr(tokenStart + 1, tokenEnd - tokenStart - 1);
            }
        }
    }
    
    // For semantic errors, ensure we have the identifier
    if (adjustedContext.stage == InterpretationStage::SEMANTIC && 
        adjustedContext.lexeme.empty() &&
        (errorMessage.find("not found") != std::string::npos ||
         errorMessage.find("Undefined") != std::string::npos)) {
        
        // Try to extract the identifier from the error message
        size_t quoteStart = errorMessage.find("'");
        if (quoteStart != std::string::npos) {
            size_t quoteEnd = errorMessage.find("'", quoteStart + 1);
            if (quoteEnd != std::string::npos) {
                adjustedContext.lexeme = errorMessage.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
            }
        }
    }
    
    // For runtime errors, adjust context based on error type
    if (adjustedContext.stage == InterpretationStage::INTERPRETING) {
        // Runtime errors might not have source context, which is fine
        // The error message itself should be descriptive enough
    }
    
    return adjustedContext;
}

} // namespace ErrorHandling