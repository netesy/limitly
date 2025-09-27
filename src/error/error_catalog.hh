#pragma once

#include "error_message.hh"
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <memory>
#include <mutex>

namespace ErrorHandling {

/**
 * @brief Comprehensive catalog of error definitions with pattern matching capabilities
 * 
 * The ErrorCatalog provides a centralized repository of error definitions, each containing
 * error codes, types, patterns, and templates for hints and suggestions. It supports
 * pattern matching to classify error messages and lookup appropriate definitions.
 */
class ErrorCatalog {
public:
    /**
     * @brief Get the singleton instance of the ErrorCatalog
     * @return Reference to the singleton ErrorCatalog instance
     */
    static ErrorCatalog& getInstance();
    
    /**
     * @brief Initialize the catalog with predefined error definitions
     * This method populates the catalog with comprehensive error definitions
     * for all interpretation stages and common error scenarios.
     */
    void initialize();
    
    /**
     * @brief Lookup error definition by message pattern matching
     * @param errorMessage The error message to match against patterns
     * @param stage The interpretation stage where the error occurred
     * @return Pointer to matching ErrorDefinition, or nullptr if no match found
     */
    const ErrorDefinition* lookupByMessage(const std::string& errorMessage, 
                                          InterpretationStage stage) const;
    
    /**
     * @brief Lookup error definition by exact error code
     * @param errorCode The error code to lookup (e.g., "E102")
     * @return Pointer to ErrorDefinition, or nullptr if not found
     */
    const ErrorDefinition* lookupByCode(const std::string& errorCode) const;
    
    /**
     * @brief Get all error definitions for a specific interpretation stage
     * @param stage The interpretation stage
     * @return Vector of ErrorDefinition pointers for that stage
     */
    std::vector<const ErrorDefinition*> getDefinitionsForStage(InterpretationStage stage) const;
    
    /**
     * @brief Add a custom error definition to the catalog
     * @param definition The error definition to add
     * @return True if added successfully, false if code already exists
     */
    bool addDefinition(const ErrorDefinition& definition);
    
    /**
     * @brief Remove an error definition by code
     * @param errorCode The error code to remove
     * @return True if removed successfully, false if not found
     */
    bool removeDefinition(const std::string& errorCode);
    
    /**
     * @brief Get the total number of error definitions in the catalog
     * @return Total count of error definitions
     */
    size_t getDefinitionCount() const;
    
    /**
     * @brief Clear all error definitions (mainly for testing)
     */
    void clear();
    
    /**
     * @brief Check if the catalog has been initialized
     * @return True if initialized, false otherwise
     */
    bool isInitialized() const;
    
    /**
     * @brief Generate a hint based on error context and definition
     * @param definition The error definition containing hint template
     * @param context The error context with specific details
     * @return Generated hint string
     */
    std::string generateHint(const ErrorDefinition& definition, 
                           const ErrorContext& context) const;
    
    /**
     * @brief Generate a suggestion based on error context and definition
     * @param definition The error definition containing suggestion template
     * @param context The error context with specific details
     * @return Generated suggestion string
     */
    std::string generateSuggestion(const ErrorDefinition& definition, 
                                 const ErrorContext& context) const;
    
    /**
     * @brief Get common causes for a specific error type
     * @param errorCode The error code to get causes for
     * @return Vector of common cause descriptions
     */
    std::vector<std::string> getCommonCauses(const std::string& errorCode) const;

private:
    // Private constructor for singleton pattern
    ErrorCatalog() = default;
    
    // Prevent copying
    ErrorCatalog(const ErrorCatalog&) = delete;
    ErrorCatalog& operator=(const ErrorCatalog&) = delete;
    
    // Storage for error definitions
    std::unordered_map<std::string, std::unique_ptr<ErrorDefinition>> definitions;
    
    // Pattern matching structures for efficient lookup
    struct PatternMatcher {
        std::regex pattern;
        std::string errorCode;
        InterpretationStage stage;
        
        PatternMatcher(const std::string& pat, const std::string& code, InterpretationStage st)
            : pattern(pat, std::regex_constants::icase), errorCode(code), stage(st) {}
    };
    
    std::vector<PatternMatcher> patternMatchers;
    
    // Stage-based lookup for efficient filtering
    std::unordered_map<InterpretationStage, std::vector<std::string>> stageToCodesMap;
    
    // Thread safety
    mutable std::mutex catalogMutex;
    
    // Initialization flag
    bool initialized = false;
    
    // Helper methods for initialization
    void initializeLexicalErrors();
    void initializeSyntaxErrors();
    void initializeSemanticErrors();
    void initializeRuntimeErrors();
    void initializeBytecodeErrors();
    void initializeCompilationErrors();
    
    // Helper method to add definition and update indices
    void addDefinitionInternal(std::unique_ptr<ErrorDefinition> definition);
    
    // Helper method to create pattern matcher from definition
    void createPatternMatcher(const ErrorDefinition& definition);
    
    // Template substitution helper
    std::string substituteTemplate(const std::string& templateStr, 
                                 const ErrorContext& context) const;
    
    // Pattern matching helper
    bool matchesPattern(const std::string& message, const std::string& pattern) const;
};

} // namespace ErrorHandling