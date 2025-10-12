#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

/**
 * Comprehensive Error Handling Include File
 * 
 * This file includes all necessary error handling components to prevent
 * linking issues when using the error handling system. Simply include
 * this file instead of individual error handling headers.
 * 
 * Usage:
 *   #include "src/error/error_handling.hh"
 * 
 * This will automatically include all required headers and ensure
 * proper linking of the error handling system.
 */

// Core error handling components
#include "error_message.hh"
#include "error_formatter.hh"
#include "console_formatter.hh"
#include "source_code_formatter.hh"
#include "ide_formatter.hh"

// Error management and cataloging
#include "error_catalog.hh"
#include "error_code_generator.hh"
#include "contextual_hint_provider.hh"
#include "enhanced_error_reporting.hh"

// Standard library includes needed by error handling
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <optional>

// Forward declarations to avoid circular dependencies
// Forward declarations
class Scanner;
class Token;
enum class InterpretationStage;

namespace ErrorHandling {
    // Re-export commonly used types for convenience
    using ErrorMessage = ErrorHandling::ErrorMessage;
    using ErrorFormatter = ErrorHandling::ErrorFormatter;
    using ConsoleFormatter = ErrorHandling::ConsoleFormatter;
    using SourceCodeFormatter = ErrorHandling::SourceCodeFormatter;
    using ErrorCatalog = ErrorHandling::ErrorCatalog;
    using ErrorCodeGenerator = ErrorHandling::ErrorCodeGenerator;
    using ContextualHintProvider = ErrorHandling::ContextualHintProvider;
    
    /**
     * Initialize the error handling system
     * Call this once at program startup to ensure all components are ready
     */
    inline void initializeErrorHandling() {
        // Initialize error catalog
        auto& catalog = ErrorCatalog::getInstance();
        if (!catalog.isInitialized()) {
            catalog.initialize();
        }
        
        // Initialize contextual hint provider
        auto& hintProvider = ContextualHintProvider::getInstance();
        if (!hintProvider.isInitialized()) {
            hintProvider.initialize();
        }
    }
    
    /**
     * Convenience function to format and display an error
     */
    inline void displayError(const std::string& message, 
                           int line, 
                           int column, 
                           InterpretationStage stage,
                           const std::string& sourceCode = "",
                           const std::string& filePath = "",
                           const std::string& lexeme = "",
                           const std::string& expectedValue = "") {
        
        // Ensure error handling is initialized
        initializeErrorHandling();
        
        // Create and format error message
        auto formatter = ErrorFormatter();
        auto options = ErrorFormatter::getDefaultOptions();
        
        auto errorMessage = ErrorFormatter::createErrorMessage(
            message, line, column, stage, sourceCode, filePath, 
            lexeme, expectedValue, std::nullopt, options
        );
        
        // Display using console formatter
        auto consoleFormatter = ConsoleFormatter();
        auto consoleOptions = ConsoleFormatter::getDefaultOptions();
        
        std::string formattedError = ConsoleFormatter::formatErrorMessage(
            errorMessage, consoleOptions
        );
        
        std::cerr << formattedError << std::endl;
    }
    
    /**
     * Quick error reporting function for simple cases
     */
    inline void reportError(const std::string& message) {
        std::cerr << "Error: " << message << std::endl;
    }
    
    /**
     * Quick warning reporting function
     */
    inline void reportWarning(const std::string& message) {
        std::cerr << "Warning: " << message << std::endl;
    }
    
} // namespace ErrorHandling

#endif // ERROR_HANDLING_H