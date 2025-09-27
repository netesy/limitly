#pragma once

#include "error_message.hh"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

namespace ErrorHandling {

/**
 * @brief Provides intelligent hint generation based on error context and patterns
 * 
 * The ContextualHintProvider analyzes error contexts and generates helpful hints,
 * actionable suggestions, and educational content to help developers understand
 * and fix errors in their code. It uses pattern matching and context analysis
 * to provide targeted assistance.
 */
class ContextualHintProvider {
public:
    /**
     * @brief Get the singleton instance of the ContextualHintProvider
     * @return Reference to the singleton ContextualHintProvider instance
     */
    static ContextualHintProvider& getInstance();
    
    /**
     * @brief Initialize the hint provider with predefined patterns and rules
     * This method sets up the hint generation system with comprehensive
     * patterns for common error scenarios and language features.
     */
    void initialize();
    
    /**
     * @brief Generate a contextual hint based on error information
     * @param errorMessage The main error message
     * @param context The error context with detailed information
     * @param definition Optional error definition from catalog
     * @return Generated hint string, empty if no specific hint available
     */
    std::string generateHint(const std::string& errorMessage, 
                           const ErrorContext& context,
                           const ErrorDefinition* definition = nullptr) const;
    
    /**
     * @brief Generate an actionable suggestion for fixing the error
     * @param errorMessage The main error message
     * @param context The error context with detailed information
     * @param definition Optional error definition from catalog
     * @return Generated suggestion string, empty if no specific suggestion available
     */
    std::string generateSuggestion(const std::string& errorMessage,
                                 const ErrorContext& context,
                                 const ErrorDefinition* definition = nullptr) const;
    
    /**
     * @brief Generate educational hints about language features
     * @param errorMessage The main error message
     * @param context The error context
     * @return Educational content about relevant language features
     */
    std::string generateEducationalHint(const std::string& errorMessage,
                                      const ErrorContext& context) const;
    
    /**
     * @brief Detect and explain common error causes
     * @param errorMessage The main error message
     * @param context The error context
     * @return Explanation of likely causes for this error
     */
    std::string explainCommonCauses(const std::string& errorMessage,
                                  const ErrorContext& context) const;
    
    /**
     * @brief Generate "Caused by" information for block-related errors
     * @param context The error context with block information
     * @return "Caused by" message showing related context, empty if not applicable
     */
    std::string generateCausedByMessage(const ErrorContext& context) const;
    
    /**
     * @brief Check if an error is likely caused by a common beginner mistake
     * @param errorMessage The main error message
     * @param context The error context
     * @return True if this appears to be a beginner-level error
     */
    bool isBeginnerError(const std::string& errorMessage, const ErrorContext& context) const;
    
    /**
     * @brief Get language feature explanation for educational purposes
     * @param featureName The name of the language feature
     * @return Explanation of the language feature, empty if not found
     */
    std::string getLanguageFeatureExplanation(const std::string& featureName) const;
    
    /**
     * @brief Add a custom hint pattern for specific error scenarios
     * @param pattern Regex pattern to match error messages
     * @param hintGenerator Function that generates hints for matching errors
     * @return True if pattern was added successfully
     */
    bool addCustomHintPattern(const std::string& pattern,
                            std::function<std::string(const ErrorContext&)> hintGenerator);
    
    /**
     * @brief Add a custom suggestion pattern for specific error scenarios
     * @param pattern Regex pattern to match error messages
     * @param suggestionGenerator Function that generates suggestions for matching errors
     * @return True if pattern was added successfully
     */
    bool addCustomSuggestionPattern(const std::string& pattern,
                                  std::function<std::string(const ErrorContext&)> suggestionGenerator);
    
    /**
     * @brief Clear all custom patterns (mainly for testing)
     */
    void clearCustomPatterns();
    
    /**
     * @brief Check if the hint provider has been initialized
     * @return True if initialized, false otherwise
     */
    bool isInitialized() const;

private:
    // Private constructor for singleton pattern
    ContextualHintProvider() = default;
    
    // Prevent copying
    ContextualHintProvider(const ContextualHintProvider&) = delete;
    ContextualHintProvider& operator=(const ContextualHintProvider&) = delete;
    
    // Pattern matching structures for hint generation
    struct HintPattern {
        std::string pattern;                                    // Regex pattern to match
        std::function<std::string(const ErrorContext&)> generator; // Hint generator function
        InterpretationStage stage;                              // Applicable stage
        int priority;                                           // Priority for matching (higher = more specific)
        
        HintPattern(const std::string& pat, 
                   std::function<std::string(const ErrorContext&)> gen,
                   InterpretationStage st = InterpretationStage::SCANNING,
                   int prio = 0)
            : pattern(pat), generator(gen), stage(st), priority(prio) {}
    };
    
    struct SuggestionPattern {
        std::string pattern;                                    // Regex pattern to match
        std::function<std::string(const ErrorContext&)> generator; // Suggestion generator function
        InterpretationStage stage;                              // Applicable stage
        int priority;                                           // Priority for matching
        
        SuggestionPattern(const std::string& pat,
                         std::function<std::string(const ErrorContext&)> gen,
                         InterpretationStage st = InterpretationStage::SCANNING,
                         int prio = 0)
            : pattern(pat), generator(gen), stage(st), priority(prio) {}
    };
    
    // Storage for patterns
    std::vector<HintPattern> hintPatterns;
    std::vector<SuggestionPattern> suggestionPatterns;
    
    // Language feature explanations
    std::unordered_map<std::string, std::string> languageFeatures;
    
    // Common error cause patterns
    std::unordered_map<std::string, std::vector<std::string>> commonCausePatterns;
    
    // Beginner error patterns
    std::vector<std::string> beginnerErrorPatterns;
    
    // Initialization flag
    bool initialized = false;
    
    // Helper methods for initialization
    void initializeLexicalHints();
    void initializeSyntaxHints();
    void initializeSemanticHints();
    void initializeBytecodeHints();
    void initializeRuntimeHints();
    void initializeLanguageFeatures();
    void initializeCommonCauses();
    void initializeBeginnerPatterns();
    
    // Helper methods for pattern matching
    bool matchesPattern(const std::string& message, const std::string& pattern) const;
    std::string findBestHint(const std::string& errorMessage, const ErrorContext& context) const;
    std::string findBestSuggestion(const std::string& errorMessage, const ErrorContext& context) const;
    
    // Template substitution helpers
    std::string substituteContextVariables(const std::string& text, const ErrorContext& context) const;
    std::string formatCodeExample(const std::string& code) const;
    
    // Context analysis helpers
    bool isInFunction(const ErrorContext& context) const;
    bool isInLoop(const ErrorContext& context) const;
    bool isInConditional(const ErrorContext& context) const;
    std::string analyzeNearbyCode(const ErrorContext& context) const;
    
    // Educational content helpers
    std::string getRelevantLanguageFeature(const std::string& errorMessage, const ErrorContext& context) const;
    std::string generateBeginnerExplanation(const std::string& errorMessage, const ErrorContext& context) const;
};

} // namespace ErrorHandling