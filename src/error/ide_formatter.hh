#pragma once

#include "error_message.hh"
#include <string>
#include <vector>
#include <ostream>
#include <map>

namespace ErrorHandling {

/**
 * @brief IDE formatter for machine-readable error output
 * 
 * This class formats ErrorMessage objects into structured, machine-readable output
 * that IDEs and development tools can parse. Supports multiple output formats
 * including JSON, XML, and LSP (Language Server Protocol) format.
 */
class IDEFormatter {
public:
    /**
     * @brief Output format types for IDE integration
     */
    enum class OutputFormat {
        JSON,           // JSON format for general IDE integration
        XML,            // XML format for legacy IDE support
        LSP,            // Language Server Protocol format
        SARIF,          // Static Analysis Results Interchange Format
        COMPACT         // Compact single-line format
    };
    
    /**
     * @brief Configuration options for IDE formatting
     */
    struct IDEOptions {
        OutputFormat format;            // Output format type
        bool includeMetadata;           // Whether to include metadata fields
        bool includeSourceContext;      // Whether to include source code context
        bool includeHints;              // Whether to include hints and suggestions
        bool batchMode;                 // Whether to format for batch processing
        bool includeStackTrace;         // Whether to include stack trace info
        std::string toolName;           // Name of the tool generating errors
        std::string toolVersion;        // Version of the tool
        
        IDEOptions() 
            : format(OutputFormat::JSON), includeMetadata(true), includeSourceContext(true),
              includeHints(true), batchMode(false), includeStackTrace(false),
              toolName("Limit Compiler"), toolVersion("1.0.0") {}
    };
    
    /**
     * @brief Get default IDE formatting options
     */
    static IDEOptions getDefaultOptions();
    
    /**
     * @brief Format a single error message for IDE consumption
     * 
     * @param errorMessage The error message to format
     * @param options Formatting options
     * @return Formatted error message string
     */
    static std::string formatErrorMessage(
        const ErrorMessage& errorMessage,
        const IDEOptions& options = getDefaultOptions()
    );
    
    /**
     * @brief Format multiple error messages for batch processing
     * 
     * @param errorMessages Vector of error messages to format
     * @param options Formatting options
     * @return Formatted batch error output
     */
    static std::string formatErrorBatch(
        const std::vector<ErrorMessage>& errorMessages,
        const IDEOptions& options = getDefaultOptions()
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
        const IDEOptions& options = getDefaultOptions()
    );
    
    /**
     * @brief Write formatted error batch to output stream
     * @param out Output stream to write to
     * @param errorMessages Vector of error messages to format
     * @param options Formatting options
     */
    static void writeErrorBatch(
        std::ostream& out,
        const std::vector<ErrorMessage>& errorMessages,
        const IDEOptions& options = getDefaultOptions()
    );
    
    /**
     * @brief Convert error severity to standard IDE severity levels
     * @param stage The interpretation stage where error occurred
     * @return Standard severity level (error, warning, info)
     */
    static std::string getSeverityLevel(InterpretationStage stage);
    
    /**
     * @brief Convert error category to standard IDE categories
     * @param errorType The error type from ErrorMessage
     * @return Standard category (syntax, semantic, runtime, etc.)
     */
    static std::string getErrorCategory(const std::string& errorType);
    
    /**
     * @brief Generate unique error ID for tracking
     * @param errorMessage The error message
     * @return Unique identifier for this error instance
     */
    static std::string generateErrorId(const ErrorMessage& errorMessage);

private:
    // Format-specific implementations
    
    /**
     * @brief Format error message as JSON
     * @param errorMessage The error message to format
     * @param options Formatting options
     * @return JSON formatted string
     */
    static std::string formatAsJSON(
        const ErrorMessage& errorMessage,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error batch as JSON
     * @param errorMessages Vector of error messages
     * @param options Formatting options
     * @return JSON formatted string
     */
    static std::string formatBatchAsJSON(
        const std::vector<ErrorMessage>& errorMessages,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error message as XML
     * @param errorMessage The error message to format
     * @param options Formatting options
     * @return XML formatted string
     */
    static std::string formatAsXML(
        const ErrorMessage& errorMessage,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error batch as XML
     * @param errorMessages Vector of error messages
     * @param options Formatting options
     * @return XML formatted string
     */
    static std::string formatBatchAsXML(
        const std::vector<ErrorMessage>& errorMessages,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error message as LSP diagnostic
     * @param errorMessage The error message to format
     * @param options Formatting options
     * @return LSP diagnostic formatted string
     */
    static std::string formatAsLSP(
        const ErrorMessage& errorMessage,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error batch as LSP diagnostics
     * @param errorMessages Vector of error messages
     * @param options Formatting options
     * @return LSP diagnostics formatted string
     */
    static std::string formatBatchAsLSP(
        const std::vector<ErrorMessage>& errorMessages,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error message as SARIF result
     * @param errorMessage The error message to format
     * @param options Formatting options
     * @return SARIF formatted string
     */
    static std::string formatAsSARIF(
        const ErrorMessage& errorMessage,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error batch as SARIF report
     * @param errorMessages Vector of error messages
     * @param options Formatting options
     * @return SARIF formatted string
     */
    static std::string formatBatchAsSARIF(
        const std::vector<ErrorMessage>& errorMessages,
        const IDEOptions& options
    );
    
    /**
     * @brief Format error message in compact single-line format
     * @param errorMessage The error message to format
     * @param options Formatting options
     * @return Compact formatted string
     */
    static std::string formatAsCompact(
        const ErrorMessage& errorMessage,
        const IDEOptions& options
    );
    
    // Helper methods for JSON formatting
    
    /**
     * @brief Escape string for JSON output
     * @param str String to escape
     * @return JSON-escaped string
     */
    static std::string escapeJSON(const std::string& str);
    
    /**
     * @brief Convert string vector to JSON array
     * @param strings Vector of strings
     * @return JSON array string
     */
    static std::string vectorToJSONArray(const std::vector<std::string>& strings);
    
    /**
     * @brief Create JSON object from key-value pairs
     * @param pairs Map of key-value pairs
     * @return JSON object string
     */
    static std::string createJSONObject(const std::map<std::string, std::string>& pairs);
    
    // Helper methods for XML formatting
    
    /**
     * @brief Escape string for XML output
     * @param str String to escape
     * @return XML-escaped string
     */
    static std::string escapeXML(const std::string& str);
    
    /**
     * @brief Create XML element with content
     * @param tagName XML tag name
     * @param content Element content
     * @param attributes Optional attributes
     * @return XML element string
     */
    static std::string createXMLElement(
        const std::string& tagName,
        const std::string& content,
        const std::map<std::string, std::string>& attributes = {}
    );
    
    // Helper methods for LSP formatting
    
    /**
     * @brief Convert line/column to LSP position
     * @param line Line number (1-based)
     * @param column Column number (1-based)
     * @return LSP position object string
     */
    static std::string createLSPPosition(int line, int column);
    
    /**
     * @brief Convert error to LSP diagnostic severity
     * @param stage Interpretation stage
     * @return LSP diagnostic severity number
     */
    static int getLSPSeverity(InterpretationStage stage);
    
    // Helper methods for SARIF formatting
    
    /**
     * @brief Create SARIF location object
     * @param errorMessage The error message
     * @return SARIF location object string
     */
    static std::string createSARIFLocation(const ErrorMessage& errorMessage);
    
    /**
     * @brief Create SARIF rule object
     * @param errorMessage The error message
     * @return SARIF rule object string
     */
    static std::string createSARIFRule(const ErrorMessage& errorMessage);
    
    // Utility methods
    
    /**
     * @brief Get current timestamp in ISO 8601 format
     * @return ISO 8601 timestamp string
     */
    static std::string getCurrentTimestamp();
    
    /**
     * @brief Generate hash from error message for consistent IDs
     * @param errorMessage The error message
     * @return Hash string
     */
    static std::string generateHash(const ErrorMessage& errorMessage);
};

} // namespace ErrorHandling