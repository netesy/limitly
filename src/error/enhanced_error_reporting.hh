#pragma once

#include "../common/debugger.hh"
#include "error_formatter.hh"
#include "ide_formatter.hh"
#include <string>
#include <vector>

namespace ErrorHandling {

/**
 * @brief Enhanced error reporting utilities for the Limit compiler
 * 
 * This class provides enhanced error reporting functions that automatically
 * generate appropriate hints and suggestions for common error scenarios
 * throughout the Limit compiler codebase.
 */
class EnhancedErrorReporting {
public:
    /**
     * @brief Report an unsupported statement type error with enhanced context
     */
    static void reportUnsupportedStatement(
        const std::string& actualType,
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report an unsupported expression type error with enhanced context
     */
    static void reportUnsupportedExpression(
        const std::string& actualType,
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report a break statement outside loop error with enhanced context
     */
    static void reportBreakOutsideLoop(
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report a continue statement outside loop error with enhanced context
     */
    static void reportContinueOutsideLoop(
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report an unsupported binary operator error with enhanced context
     */
    static void reportUnsupportedBinaryOperator(
        const std::string& operatorToken,
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report an unsupported unary operator error with enhanced context
     */
    static void reportUnsupportedUnaryOperator(
        const std::string& operatorToken,
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report named arguments not supported error with enhanced context
     */
    static void reportNamedArgumentsNotSupported(
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report index assignment not implemented error with enhanced context
     */
    static void reportIndexAssignmentNotImplemented(
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report unknown compound assignment operator error with enhanced context
     */
    static void reportUnknownCompoundAssignment(
        const std::string& operatorToken,
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report invalid assignment expression error with enhanced context
     */
    static void reportInvalidAssignment(
        int line,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report type error with enhanced context
     */
    static void reportTypeError(
        const std::string& message,
        int line,
        int column,
        const std::string& sourceCode,
        const std::string& filePath,
        const std::string& context = ""
    );
    
    /**
     * @brief Report undefined variable error with enhanced context
     */
    static void reportUndefinedVariable(
        const std::string& variableName,
        int line,
        int column,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report undefined function error with enhanced context
     */
    static void reportUndefinedFunction(
        const std::string& functionName,
        int line,
        int column,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report function argument mismatch error with enhanced context
     */
    static void reportArgumentMismatch(
        const std::string& functionName,
        int expected,
        int actual,
        int line,
        int column,
        const std::string& sourceCode,
        const std::string& filePath
    );
    
    /**
     * @brief Report syntax error with enhanced context
     */
    static void reportSyntaxError(
        const std::string& message,
        const std::string& token,
        int line,
        int column,
        const std::string& sourceCode,
        const std::string& filePath,
        const std::string& expected = ""
    );
    
    /**
     * @brief Report runtime error with enhanced context
     */
    static void reportRuntimeError(
        const std::string& message,
        int line,
        const std::string& sourceCode,
        const std::string& filePath,
        const std::string& context = ""
    );

private:
    /**
     * @brief Generate hint for unsupported feature errors
     */
    static std::string generateUnsupportedFeatureHint(const std::string& feature);
    
    /**
     * @brief Generate suggestion for unsupported feature errors
     */
    static std::string generateUnsupportedFeatureSuggestion(const std::string& feature);
    
    /**
     * @brief Generate hint for control flow errors
     */
    static std::string generateControlFlowHint(const std::string& statement);
    
    /**
     * @brief Generate suggestion for control flow errors
     */
    static std::string generateControlFlowSuggestion(const std::string& statement);
    
    /**
     * @brief Generate hint for operator errors
     */
    static std::string generateOperatorHint(const std::string& operator_);
    
    /**
     * @brief Generate suggestion for operator errors
     */
    static std::string generateOperatorSuggestion(const std::string& operator_);
    
    /**
     * @brief Generate hint for type errors
     */
    static std::string generateTypeErrorHint(const std::string& message);
    
    /**
     * @brief Generate suggestion for type errors
     */
    static std::string generateTypeErrorSuggestion(const std::string& message);
    
    /**
     * @brief Generate hint for undefined identifier errors
     */
    static std::string generateUndefinedIdentifierHint(const std::string& identifier);
    
    /**
     * @brief Generate suggestion for undefined identifier errors
     */
    static std::string generateUndefinedIdentifierSuggestion(const std::string& identifier);
};

} // namespace ErrorHandling