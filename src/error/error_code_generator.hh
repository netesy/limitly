#pragma once

#include "error_message.hh"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

namespace ErrorHandling {

/**
 * @brief Generates unique error codes based on InterpretationStage
 * 
 * This class provides static methods to generate consistent, unique error codes
 * for different types of errors that occur during language processing.
 * 
 * Error code ranges:
 * - E001-E099: Lexical/Scanning errors
 * - E100-E199: Syntax/Parsing errors  
 * - E200-E299: Semantic errors
 * - E300-E399: Type errors
 * - E400-E499: Runtime/Interpreting errors
 * - E500-E599: Bytecode generation errors
 * - E600-E699: Compilation errors
 */
class ErrorCodeGenerator {
public:
    /**
     * @brief Generate a unique error code for the given interpretation stage
     * @param stage The stage where the error occurred
     * @param errorMessage Optional error message for more specific code generation
     * @return A unique error code string (e.g., "E102")
     */
    static std::string generateErrorCode(InterpretationStage stage, 
                                       const std::string& errorMessage = "");
    
    /**
     * @brief Get the error type string for a given interpretation stage
     * @param stage The interpretation stage
     * @return The corresponding error type (e.g., "SyntaxError")
     */
    static std::string getErrorType(InterpretationStage stage);
    
    /**
     * @brief Check if an error code is already registered
     * @param errorCode The error code to check
     * @return True if the code is already in use
     */
    static bool isCodeRegistered(const std::string& errorCode);
    
    /**
     * @brief Get the next available error code in a specific range
     * @param stage The interpretation stage to get the range for
     * @return The next available error code in that range
     */
    static std::string getNextAvailableCode(InterpretationStage stage);
    
    /**
     * @brief Register an error code to prevent conflicts
     * @param errorCode The error code to register
     * @param stage The stage this code belongs to
     * @param description Optional description of what this code represents
     */
    static void registerErrorCode(const std::string& errorCode, 
                                InterpretationStage stage,
                                const std::string& description = "");
    
    /**
     * @brief Get all registered error codes for a specific stage
     * @param stage The interpretation stage
     * @return Set of all registered codes for that stage
     */
    static std::unordered_set<std::string> getRegisteredCodes(InterpretationStage stage);
    
    /**
     * @brief Clear all registered error codes (mainly for testing)
     */
    static void clearRegistry();
    
    /**
     * @brief Get the total number of registered error codes
     * @return Total count of registered codes
     */
    static size_t getRegisteredCodeCount();

private:
    // Error code ranges for different stages
    struct CodeRange {
        int start;
        int end;
        std::string prefix;
    };
    
    // Get the code range for a specific interpretation stage
    static CodeRange getCodeRange(InterpretationStage stage);
    
    // Generate a formatted error code from a number
    static std::string formatErrorCode(int codeNumber);
    
    // Thread-safe registry of used error codes
    static std::unordered_set<std::string> registeredCodes;
    
    // Counter for each stage to track next available code
    static std::unordered_map<InterpretationStage, int> stageCounters;
    
    // Mutex for thread-safe access to the registry
    static std::mutex registryMutex;
    
    // Map error messages to specific codes for consistency
    static std::unordered_map<std::string, std::string> messageToCodeMap;
    
    // Initialize the message-to-code mapping
    static void initializeMessageMapping();
    
    // Check if message mapping has been initialized
    static bool messageMappingInitialized;
};

} // namespace ErrorHandling