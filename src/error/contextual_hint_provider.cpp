#include "contextual_hint_provider.hh"
#include <regex>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace ErrorHandling {

ContextualHintProvider& ContextualHintProvider::getInstance() {
    static ContextualHintProvider instance;
    return instance;
}

void ContextualHintProvider::initialize() {
    if (initialized) {
        return; // Already initialized
    }
    
    // Clear any existing data
    hintPatterns.clear();
    suggestionPatterns.clear();
    languageFeatures.clear();
    commonCausePatterns.clear();
    beginnerErrorPatterns.clear();
    
    // Initialize all pattern categories
    initializeLexicalHints();
    initializeSyntaxHints();
    initializeSemanticHints();
    initializeBytecodeHints();
    initializeRuntimeHints();
    initializeLanguageFeatures();
    initializeCommonCauses();
    initializeBeginnerPatterns();
    
    // Sort patterns by priority (higher priority first)
    std::sort(hintPatterns.begin(), hintPatterns.end(),
              [](const HintPattern& a, const HintPattern& b) {
                  return a.priority > b.priority;
              });
    
    std::sort(suggestionPatterns.begin(), suggestionPatterns.end(),
              [](const SuggestionPattern& a, const SuggestionPattern& b) {
                  return a.priority > b.priority;
              });
    
    initialized = true;
}

std::string ContextualHintProvider::generateHint(const std::string& errorMessage, 
                                               const ErrorContext& context,
                                               const ErrorDefinition* definition) const {
    if (!initialized) {
        return "";
    }
    
    // First try to use definition template if available
    if (definition && !definition->hintTemplate.empty()) {
        return substituteContextVariables(definition->hintTemplate, context);
    }
    
    // Find best matching hint pattern
    std::string hint = findBestHint(errorMessage, context);
    
    // If no specific hint found, try to generate educational content
    if (hint.empty()) {
        hint = generateEducationalHint(errorMessage, context);
    }
    
    return hint;
}

std::string ContextualHintProvider::generateSuggestion(const std::string& errorMessage,
                                                     const ErrorContext& context,
                                                     const ErrorDefinition* definition) const {
    if (!initialized) {
        return "";
    }
    
    // First try to use definition template if available
    if (definition && !definition->suggestionTemplate.empty()) {
        return substituteContextVariables(definition->suggestionTemplate, context);
    }
    
    // Find best matching suggestion pattern
    return findBestSuggestion(errorMessage, context);
}

std::string ContextualHintProvider::generateEducationalHint(const std::string& errorMessage,
                                                          const ErrorContext& context) const {
    std::string feature = getRelevantLanguageFeature(errorMessage, context);
    if (!feature.empty()) {
        auto it = languageFeatures.find(feature);
        if (it != languageFeatures.end()) {
            return "Language feature: " + it->second;
        }
    }
    
    // Generate beginner-friendly explanation if this appears to be a beginner error
    if (isBeginnerError(errorMessage, context)) {
        return generateBeginnerExplanation(errorMessage, context);
    }
    
    return "";
}

std::string ContextualHintProvider::explainCommonCauses(const std::string& errorMessage,
                                                      const ErrorContext& context) const {
    // Look for patterns in common causes
    for (const auto& pair : commonCausePatterns) {
        if (matchesPattern(errorMessage, pair.first)) {
            if (!pair.second.empty()) {
                std::ostringstream oss;
                oss << "Common causes: ";
                for (size_t i = 0; i < pair.second.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << pair.second[i];
                }
                return oss.str();
            }
        }
    }
    
    return "";
}

std::string ContextualHintProvider::generateCausedByMessage(const ErrorContext& context) const {
    if (!context.blockContext.has_value()) {
        return "";
    }
    
    const BlockContext& block = context.blockContext.value();
    std::ostringstream oss;
    
    oss << "Caused by: Unterminated " << block.blockType << " starting at line " << block.startLine;
    if (!block.startLexeme.empty()) {
        oss << ":\n" << block.startLine << " | " << block.startLexeme;
        oss << "\n   | " << std::string(block.startLexeme.length(), '-') << " unclosed block starts here";
    }
    
    return oss.str();
}

bool ContextualHintProvider::isBeginnerError(const std::string& errorMessage, 
                                           const ErrorContext& context) const {
    for (const std::string& pattern : beginnerErrorPatterns) {
        if (matchesPattern(errorMessage, pattern)) {
            return true;
        }
    }
    return false;
}

std::string ContextualHintProvider::getLanguageFeatureExplanation(const std::string& featureName) const {
    auto it = languageFeatures.find(featureName);
    return (it != languageFeatures.end()) ? it->second : "";
}

bool ContextualHintProvider::addCustomHintPattern(const std::string& pattern,
                                                std::function<std::string(const ErrorContext&)> hintGenerator) {
    try {
        // Test if pattern is valid regex
        std::regex testRegex(pattern);
        hintPatterns.emplace_back(pattern, hintGenerator, InterpretationStage::SCANNING, 100); // High priority for custom
        return true;
    } catch (const std::regex_error&) {
        return false;
    }
}

bool ContextualHintProvider::addCustomSuggestionPattern(const std::string& pattern,
                                                      std::function<std::string(const ErrorContext&)> suggestionGenerator) {
    try {
        // Test if pattern is valid regex
        std::regex testRegex(pattern);
        suggestionPatterns.emplace_back(pattern, suggestionGenerator, InterpretationStage::SCANNING, 100); // High priority for custom
        return true;
    } catch (const std::regex_error&) {
        return false;
    }
}

void ContextualHintProvider::clearCustomPatterns() {
    // Remove custom patterns (those with priority >= 100)
    hintPatterns.erase(
        std::remove_if(hintPatterns.begin(), hintPatterns.end(),
                      [](const HintPattern& p) { return p.priority >= 100; }),
        hintPatterns.end());
    
    suggestionPatterns.erase(
        std::remove_if(suggestionPatterns.begin(), suggestionPatterns.end(),
                      [](const SuggestionPattern& p) { return p.priority >= 100; }),
        suggestionPatterns.end());
}

bool ContextualHintProvider::isInitialized() const {
    return initialized;
}

// Private helper methods

void ContextualHintProvider::initializeLexicalHints() {
    // Lexical/Scanning error hints
    hintPatterns.emplace_back(
        "Invalid character",
        [](const ErrorContext& ctx) {
            return "This character is not recognized by the Limit language scanner. "
                   "Check for special characters that might have been copied from other sources.";
        },
        InterpretationStage::SCANNING, 10
    );
    
    hintPatterns.emplace_back(
        "Unterminated string",
        [](const ErrorContext& ctx) {
            return "String literals must be enclosed in matching quotes. "
                   "If you need a newline in your string, use the escape sequence \\n.";
        },
        InterpretationStage::SCANNING, 10
    );
    
    hintPatterns.emplace_back(
        "Invalid number format",
        [](const ErrorContext& ctx) {
            return "Numbers in Limit can be integers (123) or decimals (123.45). "
                   "Scientific notation is not currently supported.";
        },
        InterpretationStage::SCANNING, 10
    );
    
    // Corresponding suggestions
    suggestionPatterns.emplace_back(
        "Invalid character",
        [](const ErrorContext& ctx) {
            return "Remove the invalid character '" + ctx.lexeme + "' or replace it with a valid token.";
        },
        InterpretationStage::SCANNING, 10
    );
    
    suggestionPatterns.emplace_back(
        "Unterminated string",
        [](const ErrorContext& ctx) {
            return "Add a closing quote (\") at the end of your string literal.";
        },
        InterpretationStage::SCANNING, 10
    );
}

void ContextualHintProvider::initializeSyntaxHints() {
    // Syntax/Parsing error hints
    hintPatterns.emplace_back(
        "Unexpected closing brace",
        [](const ErrorContext& ctx) {
            return "This closing brace '}' doesn't have a matching opening brace '{'. "
                   "Check if you have the right number of opening and closing braces.";
        },
        InterpretationStage::PARSING, 15
    );
    
    hintPatterns.emplace_back(
        "Missing opening brace",
        [](const ErrorContext& ctx) {
            std::string hint = "Block structures like functions, if statements, and loops require opening braces '{'.";
            if (ctx.blockContext.has_value()) {
                hint += " The " + ctx.blockContext->blockType + " block needs an opening brace.";
            }
            return hint;
        },
        InterpretationStage::PARSING, 15
    );
    
    hintPatterns.emplace_back(
        "Expected.*semicolon|Missing semicolon",
        [](const ErrorContext& ctx) {
            return "In Limit, statements must end with a semicolon ';'. "
                   "This helps the parser know where one statement ends and the next begins.";
        },
        InterpretationStage::PARSING, 12
    );
    
    hintPatterns.emplace_back(
        "Invalid factor",
        [](const ErrorContext& ctx) {
            return "An expression factor should be a variable, number, string, or parenthesized expression. "
                   "Check that all parts of your expression are valid.";
        },
        InterpretationStage::PARSING, 10
    );
    
    // Corresponding suggestions
    suggestionPatterns.emplace_back(
        "Unexpected closing brace",
        [](const ErrorContext& ctx) {
            return "Either remove this extra '}' or add a matching '{' before it.";
        },
        InterpretationStage::PARSING, 15
    );
    
    suggestionPatterns.emplace_back(
        "Missing opening brace",
        [](const ErrorContext& ctx) {
            return "Add an opening brace '{' to start the block.";
        },
        InterpretationStage::PARSING, 15
    );
    
    suggestionPatterns.emplace_back(
        "Expected.*semicolon|Missing semicolon",
        [](const ErrorContext& ctx) {
            return "Add a semicolon ';' at the end of the statement.";
        },
        InterpretationStage::PARSING, 12
    );
}

void ContextualHintProvider::initializeSemanticHints() {
    // Semantic error hints
    hintPatterns.emplace_back(
        "Variable.*not found|Undefined variable",
        [](const ErrorContext& ctx) {
            return "Variables must be declared before they can be used. "
                   "In Limit, use 'var variableName: type = value;' to declare variables.";
        },
        InterpretationStage::SEMANTIC, 15
    );
    
    hintPatterns.emplace_back(
        "Function.*not found|Undefined function",
        [](const ErrorContext& ctx) {
            return "Functions must be defined before they can be called. "
                   "Check if the function is defined in this file or imported from a module.";
        },
        InterpretationStage::SEMANTIC, 15
    );
    
    hintPatterns.emplace_back(
        "Type mismatch",
        [](const ErrorContext& ctx) {
            return "Limit has a strong type system. Make sure the types on both sides of operations are compatible. "
                   "You may need explicit type conversion.";
        },
        InterpretationStage::SEMANTIC, 12
    );
    
    // Type checking specific hints
    hintPatterns.emplace_back(
        "Unhandled fallible.*function call",
        [](const ErrorContext& ctx) {
            return "Functions that can fail (return error types) must be handled explicitly. "
                   "Use the '?' operator to propagate errors or 'match' statements to handle them.";
        },
        InterpretationStage::SEMANTIC, 18
    );
    
    hintPatterns.emplace_back(
        "cannot assign.*fallible type.*to non-fallible type",
        [](const ErrorContext& ctx) {
            return "You're trying to assign a value that might be an error to a variable that expects a success value. "
                   "Handle the potential error first using '?' operator or match statement.";
        },
        InterpretationStage::SEMANTIC, 16
    );
    
    hintPatterns.emplace_back(
        "cannot assign non-fallible type.*to fallible type",
        [](const ErrorContext& ctx) {
            return "You're assigning a regular value to a variable that expects a fallible type (can be error or success). "
                   "Wrap the value with ok() to make it compatible.";
        },
        InterpretationStage::SEMANTIC, 16
    );
    
    // Corresponding suggestions
    suggestionPatterns.emplace_back(
        "Variable.*not found|Undefined variable",
        [](const ErrorContext& ctx) {
            return "Check the spelling of '" + ctx.lexeme + "' or declare it with 'var " + ctx.lexeme + ": type = value;'";
        },
        InterpretationStage::SEMANTIC, 15
    );
    
    suggestionPatterns.emplace_back(
        "Function.*not found|Undefined function",
        [](const ErrorContext& ctx) {
            return "Define the function '" + ctx.lexeme + "' or check if it needs to be imported from a module.";
        },
        InterpretationStage::SEMANTIC, 15
    );
    
    suggestionPatterns.emplace_back(
        "Unhandled fallible.*function call",
        [](const ErrorContext& ctx) {
            return "Add '?' after the function call to propagate errors, or use 'match' to handle specific error cases.";
        },
        InterpretationStage::SEMANTIC, 18
    );
    
    suggestionPatterns.emplace_back(
        "cannot assign.*fallible type.*to non-fallible type",
        [](const ErrorContext& ctx) {
            return "Handle the error with '?' operator or 'match' statement before assignment.";
        },
        InterpretationStage::SEMANTIC, 16
    );
    
    suggestionPatterns.emplace_back(
        "cannot assign non-fallible type.*to fallible type",
        [](const ErrorContext& ctx) {
            return "Use ok(" + ctx.lexeme + ") to wrap the value as a success result.";
        },
        InterpretationStage::SEMANTIC, 16
    );
}

void ContextualHintProvider::initializeBytecodeHints() {
    // Bytecode generation error hints
    hintPatterns.emplace_back(
        "Unsupported statement type",
        [](const ErrorContext& ctx) {
            return "The bytecode generator doesn't know how to handle this type of statement. "
                   "This might be a new language feature that hasn't been implemented yet.";
        },
        InterpretationStage::BYTECODE, 15
    );
    
    hintPatterns.emplace_back(
        "Unsupported expression type",
        [](const ErrorContext& ctx) {
            return "The bytecode generator doesn't know how to handle this type of expression. "
                   "This might be a new language feature that hasn't been implemented yet.";
        },
        InterpretationStage::BYTECODE, 15
    );
    
    hintPatterns.emplace_back(
        "'break' statement used outside of loop context",
        [](const ErrorContext& ctx) {
            return "The 'break' statement can only be used inside loop bodies (while, for, or iter loops). "
                   "It's used to exit the loop early.";
        },
        InterpretationStage::BYTECODE, 18
    );
    
    hintPatterns.emplace_back(
        "'continue' statement used outside of loop context",
        [](const ErrorContext& ctx) {
            return "The 'continue' statement can only be used inside loop bodies (while, for, or iter loops). "
                   "It's used to skip to the next iteration of the loop.";
        },
        InterpretationStage::BYTECODE, 18
    );
    
    hintPatterns.emplace_back(
        "Unsupported binary operator",
        [](const ErrorContext& ctx) {
            return "This binary operator is not supported by the Limit language. "
                   "Supported operators include: +, -, *, /, %, ==, !=, <, >, <=, >=, &&, ||.";
        },
        InterpretationStage::BYTECODE, 14
    );
    
    hintPatterns.emplace_back(
        "Unknown unary operator",
        [](const ErrorContext& ctx) {
            return "This unary operator is not supported by the Limit language. "
                   "Supported unary operators are: - (negation) and ! (logical not).";
        },
        InterpretationStage::BYTECODE, 14
    );
    
    hintPatterns.emplace_back(
        "Named arguments not yet supported",
        [](const ErrorContext& ctx) {
            return "Named function arguments are a planned feature but not yet implemented. "
                   "Use positional arguments for now.";
        },
        InterpretationStage::BYTECODE, 12
    );
    
    hintPatterns.emplace_back(
        "Index assignment not yet implemented",
        [](const ErrorContext& ctx) {
            return "Array/list index assignment (arr[i] = value) is not yet implemented. "
                   "Use simple variable assignment for now.";
        },
        InterpretationStage::BYTECODE, 12
    );
    
    hintPatterns.emplace_back(
        "Unknown compound assignment operator",
        [](const ErrorContext& ctx) {
            return "This compound assignment operator is not supported. "
                   "Supported compound assignments are: +=, -=, *=, /=, %=.";
        },
        InterpretationStage::BYTECODE, 13
    );
    
    hintPatterns.emplace_back(
        "Invalid assignment expression",
        [](const ErrorContext& ctx) {
            return "This assignment expression is not valid. "
                   "Valid assignments include: variable = value, variable += value, etc.";
        },
        InterpretationStage::BYTECODE, 13
    );
    
    hintPatterns.emplace_back(
        "Could not open module file",
        [](const ErrorContext& ctx) {
            return "The module file could not be found or opened. "
                   "Check that the file path is correct and the file exists.";
        },
        InterpretationStage::BYTECODE, 16
    );
    
    // Corresponding suggestions
    suggestionPatterns.emplace_back(
        "Unsupported statement type",
        [](const ErrorContext& ctx) {
            return "Use supported statement types: variable declarations, function declarations, if statements, loops, or expression statements.";
        },
        InterpretationStage::BYTECODE, 15
    );
    
    suggestionPatterns.emplace_back(
        "Unsupported expression type",
        [](const ErrorContext& ctx) {
            return "Use supported expressions: binary operations, unary operations, literals, variables, function calls, or grouping expressions.";
        },
        InterpretationStage::BYTECODE, 15
    );
    
    suggestionPatterns.emplace_back(
        "'break' statement used outside of loop context",
        [](const ErrorContext& ctx) {
            return "Move the 'break' statement inside a loop body (while, for, or iter loop).";
        },
        InterpretationStage::BYTECODE, 18
    );
    
    suggestionPatterns.emplace_back(
        "'continue' statement used outside of loop context",
        [](const ErrorContext& ctx) {
            return "Move the 'continue' statement inside a loop body (while, for, or iter loop).";
        },
        InterpretationStage::BYTECODE, 18
    );
    
    suggestionPatterns.emplace_back(
        "Unsupported binary operator",
        [](const ErrorContext& ctx) {
            return "Use a supported binary operator: +, -, *, /, %, ==, !=, <, >, <=, >=, &&, ||.";
        },
        InterpretationStage::BYTECODE, 14
    );
    
    suggestionPatterns.emplace_back(
        "Unknown unary operator",
        [](const ErrorContext& ctx) {
            return "Use a supported unary operator: - (negation) or ! (logical not).";
        },
        InterpretationStage::BYTECODE, 14
    );
    
    suggestionPatterns.emplace_back(
        "Named arguments not yet supported",
        [](const ErrorContext& ctx) {
            return "Use positional arguments instead: functionName(arg1, arg2, arg3).";
        },
        InterpretationStage::BYTECODE, 12
    );
    
    suggestionPatterns.emplace_back(
        "Index assignment not yet implemented",
        [](const ErrorContext& ctx) {
            return "Use simple variable assignment: variable = value.";
        },
        InterpretationStage::BYTECODE, 12
    );
    
    suggestionPatterns.emplace_back(
        "Unknown compound assignment operator",
        [](const ErrorContext& ctx) {
            return "Use a supported compound assignment: +=, -=, *=, /=, or %=.";
        },
        InterpretationStage::BYTECODE, 13
    );
    
    suggestionPatterns.emplace_back(
        "Invalid assignment expression",
        [](const ErrorContext& ctx) {
            return "Use a valid assignment: variable = value or variable += value.";
        },
        InterpretationStage::BYTECODE, 13
    );
    
    suggestionPatterns.emplace_back(
        "Could not open module file",
        [](const ErrorContext& ctx) {
            return "Check the file path and ensure the module file exists and is readable.";
        },
        InterpretationStage::BYTECODE, 16
    );
}

void ContextualHintProvider::initializeRuntimeHints() {
    // Runtime error hints
    hintPatterns.emplace_back(
        "Division by zero",
        [](const ErrorContext& ctx) {
            return "Division by zero is mathematically undefined and causes runtime errors. "
                   "Always check that your divisor is not zero before performing division.";
        },
        InterpretationStage::INTERPRETING, 20
    );
    
    hintPatterns.emplace_back(
        "Modulo by zero",
        [](const ErrorContext& ctx) {
            return "Modulo by zero is mathematically undefined and causes runtime errors. "
                   "The modulo operation requires a non-zero divisor.";
        },
        InterpretationStage::INTERPRETING, 20
    );
    
    hintPatterns.emplace_back(
        "Stack overflow",
        [](const ErrorContext& ctx) {
            return "Stack overflow usually indicates infinite recursion. "
                   "Check that your recursive functions have proper base cases.";
        },
        InterpretationStage::INTERPRETING, 18
    );
    
    hintPatterns.emplace_back(
        "Null reference",
        [](const ErrorContext& ctx) {
            return "Null reference errors occur when trying to use an uninitialized or null value. "
                   "In Limit, consider using Option types (Some | None) for values that might be absent.";
        },
        InterpretationStage::INTERPRETING, 15
    );
    
    hintPatterns.emplace_back(
        "Stack underflow",
        [](const ErrorContext& ctx) {
            return "Stack underflow occurs when trying to pop more values from the stack than are available. "
                   "This usually indicates a bug in the compiler's bytecode generation or VM implementation.";
        },
        InterpretationStage::INTERPRETING, 17
    );
    
    hintPatterns.emplace_back(
        "Error executing.*instruction|Error executing bytecode",
        [](const ErrorContext& ctx) {
            return "An error occurred while executing bytecode instructions. "
                   "This could be due to invalid bytecode, runtime type errors, or resource issues.";
        },
        InterpretationStage::INTERPRETING, 15
    );
    
    hintPatterns.emplace_back(
        "Unknown opcode",
        [](const ErrorContext& ctx) {
            return "The VM encountered an unknown bytecode instruction. "
                   "This indicates a bug in the bytecode generator or corrupted bytecode.";
        },
        InterpretationStage::INTERPRETING, 16
    );
    
    hintPatterns.emplace_back(
        "Unexpected character",
        [](const ErrorContext& ctx) {
            return "The scanner encountered a character that is not valid in the Limit language. "
                   "Check for typos, invalid Unicode characters, or characters from other languages.";
        },
        InterpretationStage::SCANNING, 18
    );
    
    hintPatterns.emplace_back(
        "Unterminated string",
        [](const ErrorContext& ctx) {
            return "String literals must be closed with a matching quote. "
                   "Make sure every opening quote has a corresponding closing quote.";
        },
        InterpretationStage::SCANNING, 19
    );
    
    hintPatterns.emplace_back(
        "Unterminated string interpolation",
        [](const ErrorContext& ctx) {
            return "String interpolation expressions must be closed with '}'. "
                   "Every '{' in a string interpolation must have a matching '}'.";
        },
        InterpretationStage::SCANNING, 19
    );
    
    // Corresponding suggestions
    suggestionPatterns.emplace_back(
        "Division by zero",
        [](const ErrorContext& ctx) {
            return "Add a check: 'if (divisor != 0) { ... }' before performing the division.";
        },
        InterpretationStage::INTERPRETING, 20
    );
    
    suggestionPatterns.emplace_back(
        "Modulo by zero",
        [](const ErrorContext& ctx) {
            return "Add a check: 'if (divisor != 0) { ... }' before performing the modulo operation.";
        },
        InterpretationStage::INTERPRETING, 20
    );
    
    suggestionPatterns.emplace_back(
        "Stack overflow",
        [](const ErrorContext& ctx) {
            return "Review your recursive function to ensure it has a base case that will eventually be reached.";
        },
        InterpretationStage::INTERPRETING, 18
    );
    
    suggestionPatterns.emplace_back(
        "Stack underflow",
        [](const ErrorContext& ctx) {
            return "Report this as a compiler bug - the bytecode generator may have produced invalid code.";
        },
        InterpretationStage::INTERPRETING, 17
    );
    
    suggestionPatterns.emplace_back(
        "Error executing.*instruction|Error executing bytecode",
        [](const ErrorContext& ctx) {
            return "Check for type errors, null values, or resource constraints in your code.";
        },
        InterpretationStage::INTERPRETING, 15
    );
    
    suggestionPatterns.emplace_back(
        "Unknown opcode",
        [](const ErrorContext& ctx) {
            return "Report this as a compiler bug - invalid bytecode was generated.";
        },
        InterpretationStage::INTERPRETING, 16
    );
    
    suggestionPatterns.emplace_back(
        "Unexpected character",
        [](const ErrorContext& ctx) {
            return "Remove the invalid character or replace it with a valid identifier, operator, or literal.";
        },
        InterpretationStage::SCANNING, 18
    );
    
    suggestionPatterns.emplace_back(
        "Unterminated string",
        [](const ErrorContext& ctx) {
            return "Add a closing quote (\") at the end of your string literal.";
        },
        InterpretationStage::SCANNING, 19
    );
    
    suggestionPatterns.emplace_back(
        "Unterminated string interpolation",
        [](const ErrorContext& ctx) {
            return "Add a closing brace (}) to complete the interpolation expression.";
        },
        InterpretationStage::SCANNING, 19
    );
    
    // VM-specific runtime error hints
    hintPatterns.emplace_back(
        "Stack underflow.*attempted to pop from empty stack",
        [](const ErrorContext& ctx) {
            return "Stack underflow indicates that the VM tried to pop a value from an empty stack. "
                   "This usually means an expression or operation expected a value that wasn't provided.";
        },
        InterpretationStage::INTERPRETING, 18
    );
    
    hintPatterns.emplace_back(
        "Stack underflow.*attempted to peek",
        [](const ErrorContext& ctx) {
            return "Stack underflow during peek operation means the VM tried to access a stack position that doesn't exist. "
                   "This indicates insufficient values on the stack for the current operation.";
        },
        InterpretationStage::INTERPRETING, 18
    );
    
    hintPatterns.emplace_back(
        "Stack underflow in STORE_VAR",
        [](const ErrorContext& ctx) {
            return "Variable assignment requires a value to be on the stack. "
                   "Make sure the right-hand side of the assignment produces a value.";
        },
        InterpretationStage::INTERPRETING, 19
    );
    
    hintPatterns.emplace_back(
        "Undefined variable",
        [](const ErrorContext& ctx) {
            return "Variables must be declared before they can be used. "
                   "In Limit, declare variables with 'var name: type = value;' or ensure the variable is in scope.";
        },
        InterpretationStage::INTERPRETING, 17
    );
    
    hintPatterns.emplace_back(
        "Cannot.*non-integer.*atomic variable",
        [](const ErrorContext& ctx) {
            return "Atomic variables in Limit can only store integer values. "
                   "They are designed for thread-safe integer operations.";
        },
        InterpretationStage::INTERPRETING, 16
    );
    
    hintPatterns.emplace_back(
        "Invalid temporary variable index",
        [](const ErrorContext& ctx) {
            return "Temporary variable index is out of bounds. "
                   "This is usually a compiler bug in bytecode generation.";
        },
        InterpretationStage::INTERPRETING, 15
    );
    
    hintPatterns.emplace_back(
        "Integer.*overflow",
        [](const ErrorContext& ctx) {
            return "Integer overflow occurs when the result of an arithmetic operation exceeds the maximum value "
                   "that can be stored in the integer type. Consider using larger integer types or checking bounds.";
        },
        InterpretationStage::INTERPRETING, 17
    );
    
    hintPatterns.emplace_back(
        "Cannot.*operands of types",
        [](const ErrorContext& ctx) {
            return "Type mismatch in arithmetic operation. "
                   "Both operands must be compatible numeric types (int, float) for arithmetic operations.";
        },
        InterpretationStage::INTERPRETING, 16
    );
    
    hintPatterns.emplace_back(
        "Cannot compare values of different types",
        [](const ErrorContext& ctx) {
            return "Comparison operations require both operands to be of the same type. "
                   "You may need to convert one operand to match the other's type.";
        },
        InterpretationStage::INTERPRETING, 16
    );
    
    // VM-specific suggestions
    suggestionPatterns.emplace_back(
        "Stack underflow.*attempted to pop from empty stack",
        [](const ErrorContext& ctx) {
            return "Ensure that expressions and statements provide the expected values. Check for missing operands or incomplete expressions.";
        },
        InterpretationStage::INTERPRETING, 18
    );
    
    suggestionPatterns.emplace_back(
        "Stack underflow.*attempted to peek",
        [](const ErrorContext& ctx) {
            return "Verify that all operations have the required number of operands available on the stack.";
        },
        InterpretationStage::INTERPRETING, 18
    );
    
    suggestionPatterns.emplace_back(
        "Stack underflow in STORE_VAR",
        [](const ErrorContext& ctx) {
            return "Provide a value for the assignment: '" + ctx.lexeme + " = someValue;'";
        },
        InterpretationStage::INTERPRETING, 19
    );
    
    suggestionPatterns.emplace_back(
        "Undefined variable",
        [](const ErrorContext& ctx) {
            return "Declare the variable '" + ctx.lexeme + "' with 'var " + ctx.lexeme + ": type = value;' or check if it's in the correct scope.";
        },
        InterpretationStage::INTERPRETING, 17
    );
    
    suggestionPatterns.emplace_back(
        "Cannot.*non-integer.*atomic variable",
        [](const ErrorContext& ctx) {
            return "Use integer values with atomic variables, or use regular variables for non-integer types.";
        },
        InterpretationStage::INTERPRETING, 16
    );
    
    suggestionPatterns.emplace_back(
        "Invalid temporary variable index",
        [](const ErrorContext& ctx) {
            return "Report this as a compiler bug - invalid bytecode was generated for temporary variables.";
        },
        InterpretationStage::INTERPRETING, 15
    );
    
    suggestionPatterns.emplace_back(
        "Integer.*overflow",
        [](const ErrorContext& ctx) {
            return "Use bounds checking before arithmetic operations or consider using larger integer types (int64).";
        },
        InterpretationStage::INTERPRETING, 17
    );
    
    suggestionPatterns.emplace_back(
        "Cannot.*operands of types",
        [](const ErrorContext& ctx) {
            return "Ensure both operands are numeric types (int, float) or convert them to compatible types.";
        },
        InterpretationStage::INTERPRETING, 16
    );
    
    suggestionPatterns.emplace_back(
        "Cannot compare values of different types",
        [](const ErrorContext& ctx) {
            return "Convert one operand to match the other's type, or use type-specific comparison methods.";
        },
        InterpretationStage::INTERPRETING, 16
    );
}

void ContextualHintProvider::initializeLanguageFeatures() {
    languageFeatures["variables"] = "Variables in Limit are declared with 'var name: type = value;' "
                                   "Type annotations are optional when the type can be inferred.";
    
    languageFeatures["functions"] = "Functions are declared with 'fn name(params) : returnType { ... }' "
                                   "Parameters can have optional types with '?' and default values.";
    
    languageFeatures["types"] = "Limit has a strong static type system with primitives (int, float, bool, str), "
                               "type aliases, union types, and Option types for null safety.";
    
    languageFeatures["modules"] = "Use 'import module as alias' to import code from other files. "
                                 "You can filter imports with 'show' and 'hide' clauses.";
    
    languageFeatures["error_handling"] = "Limit uses Result types and the '?' operator for error handling. "
                                        "Functions that might fail return 'T?ErrorType'.";
    
    languageFeatures["control_flow"] = "Limit supports if/else statements, while loops, for loops, "
                                      "and pattern matching with match expressions.";
    
    languageFeatures["strings"] = "String interpolation uses curly braces: \"Hello {name}!\". "
                                 "Strings support escape sequences like \\n, \\t, \\\", and \\\\.";
    
    languageFeatures["iterators"] = "Use 'iter (item in collection)' for iteration. "
                                   "Range syntax: '1..10' for inclusive ranges, '1..<10' for exclusive.";
}

void ContextualHintProvider::initializeCommonCauses() {
    commonCausePatterns["Invalid character"] = {"Copy-paste from another language", "Encoding issues", "Special Unicode characters"};
    commonCausePatterns["Unterminated string"] = {"Missing closing quote", "Newline in string without escape", "Nested quotes"};
    commonCausePatterns["Unexpected.*brace"] = {"Mismatched braces", "Extra closing brace", "Missing opening brace"};
    commonCausePatterns["Variable.*not found"] = {"Typo in variable name", "Variable not declared", "Out of scope"};
    commonCausePatterns["Function.*not found"] = {"Typo in function name", "Function not defined", "Missing import"};
    commonCausePatterns["Type mismatch"] = {"Incompatible types", "Missing type conversion", "Wrong type annotation"};
    commonCausePatterns["Division by zero"] = {"Uninitialized variable", "Logic error in calculation", "Missing validation"};
    commonCausePatterns["Stack underflow"] = {"Compiler bug", "Invalid bytecode", "VM implementation error"};
    commonCausePatterns["break.*outside.*loop"] = {"Misplaced break statement", "Missing loop context", "Wrong control structure"};
    commonCausePatterns["continue.*outside.*loop"] = {"Misplaced continue statement", "Missing loop context", "Wrong control structure"};
    commonCausePatterns["Unsupported.*operator"] = {"Typo in operator", "Unsupported language feature", "Wrong operator syntax"};
    commonCausePatterns["Named arguments.*not.*supported"] = {"Using unimplemented feature", "Wrong function call syntax"};
    commonCausePatterns["Index assignment.*not.*implemented"] = {"Using unimplemented feature", "Wrong assignment syntax"};
    commonCausePatterns["Could not open module"] = {"Wrong file path", "Missing file", "Permission issues", "File system error"};
    commonCausePatterns["Unhandled fallible"] = {"Missing error handling", "Forgot ? operator", "Missing match statement"};
    commonCausePatterns["cannot assign.*fallible.*non-fallible"] = {"Type mismatch", "Missing error handling", "Wrong variable type"};
    commonCausePatterns["cannot assign non-fallible.*fallible"] = {"Type mismatch", "Missing ok() wrapper", "Wrong variable type"};
}

void ContextualHintProvider::initializeBeginnerPatterns() {
    beginnerErrorPatterns = {
        "Missing semicolon",
        "Invalid character",
        "Unterminated string",
        "Variable.*not found",
        "Expected.*",
        "Unexpected token",
        "Invalid factor",
        "break.*outside.*loop",
        "continue.*outside.*loop",
        "Unsupported.*operator",
        "Type mismatch",
        "Invalid assignment",
        "Unhandled fallible"
    };
}

bool ContextualHintProvider::matchesPattern(const std::string& message, const std::string& pattern) const {
    try {
        std::regex regex_pattern(pattern, std::regex_constants::icase);
        return std::regex_search(message, regex_pattern);
    } catch (const std::regex_error&) {
        // If regex is invalid, fall back to simple string matching
        return message.find(pattern) != std::string::npos;
    }
}

std::string ContextualHintProvider::findBestHint(const std::string& errorMessage, 
                                               const ErrorContext& context) const {
    // Try patterns in priority order
    for (const HintPattern& pattern : hintPatterns) {
        if (pattern.stage == context.stage || pattern.stage == InterpretationStage::SCANNING) {
            if (matchesPattern(errorMessage, pattern.pattern)) {
                return pattern.generator(context);
            }
        }
    }
    
    return "";
}

std::string ContextualHintProvider::findBestSuggestion(const std::string& errorMessage,
                                                     const ErrorContext& context) const {
    // Try patterns in priority order
    for (const SuggestionPattern& pattern : suggestionPatterns) {
        if (pattern.stage == context.stage || pattern.stage == InterpretationStage::SCANNING) {
            if (matchesPattern(errorMessage, pattern.pattern)) {
                return pattern.generator(context);
            }
        }
    }
    
    return "";
}

std::string ContextualHintProvider::substituteContextVariables(const std::string& text, 
                                                             const ErrorContext& context) const {
    std::string result = text;
    
    // Replace context variables
    size_t pos = result.find("{lexeme}");
    if (pos != std::string::npos) {
        result.replace(pos, 8, context.lexeme);
    }
    
    pos = result.find("{expected}");
    if (pos != std::string::npos) {
        result.replace(pos, 10, context.expectedValue);
    }
    
    pos = result.find("{file}");
    if (pos != std::string::npos) {
        result.replace(pos, 6, context.filePath);
    }
    
    pos = result.find("{line}");
    if (pos != std::string::npos) {
        result.replace(pos, 6, std::to_string(context.line));
    }
    
    pos = result.find("{column}");
    if (pos != std::string::npos) {
        result.replace(pos, 8, std::to_string(context.column));
    }
    
    return result;
}

std::string ContextualHintProvider::formatCodeExample(const std::string& code) const {
    return "```\n" + code + "\n```";
}

bool ContextualHintProvider::isInFunction(const ErrorContext& context) const {
    return context.blockContext.has_value() && 
           context.blockContext->blockType == "function";
}

bool ContextualHintProvider::isInLoop(const ErrorContext& context) const {
    return context.blockContext.has_value() && 
           (context.blockContext->blockType == "while" || 
            context.blockContext->blockType == "for" ||
            context.blockContext->blockType == "iter");
}

bool ContextualHintProvider::isInConditional(const ErrorContext& context) const {
    return context.blockContext.has_value() && 
           context.blockContext->blockType == "if";
}

std::string ContextualHintProvider::analyzeNearbyCode(const ErrorContext& context) const {
    // Simple analysis of nearby code patterns
    if (!context.sourceCode.empty() && context.line > 0) {
        std::istringstream iss(context.sourceCode);
        std::string line;
        int currentLine = 1;
        
        // Find the error line and nearby lines
        while (std::getline(iss, line) && currentLine <= context.line + 2) {
            if (currentLine >= context.line - 2 && currentLine <= context.line + 2) {
                // Analyze this line for common patterns
                if (line.find("var") != std::string::npos && line.find(";") == std::string::npos) {
                    return "Nearby variable declaration might be missing a semicolon.";
                }
                if (line.find("fn") != std::string::npos && line.find("{") == std::string::npos) {
                    return "Nearby function declaration might be missing an opening brace.";
                }
            }
            currentLine++;
        }
    }
    
    return "";
}

std::string ContextualHintProvider::getRelevantLanguageFeature(const std::string& errorMessage,
                                                             const ErrorContext& context) const {
    if (errorMessage.find("variable") != std::string::npos || 
        errorMessage.find("Variable") != std::string::npos) {
        return "variables";
    }
    if (errorMessage.find("function") != std::string::npos || 
        errorMessage.find("Function") != std::string::npos) {
        return "functions";
    }
    if (errorMessage.find("type") != std::string::npos || 
        errorMessage.find("Type") != std::string::npos) {
        return "types";
    }
    if (errorMessage.find("string") != std::string::npos || 
        errorMessage.find("String") != std::string::npos) {
        return "strings";
    }
    if (errorMessage.find("import") != std::string::npos || 
        errorMessage.find("module") != std::string::npos) {
        return "modules";
    }
    
    return "";
}

std::string ContextualHintProvider::generateBeginnerExplanation(const std::string& errorMessage,
                                                              const ErrorContext& context) const {
    if (errorMessage.find("semicolon") != std::string::npos) {
        return "Beginner tip: In Limit, every statement must end with a semicolon ';'. "
               "This is different from some languages like Python, but similar to C++ or Java.";
    }
    
    if (errorMessage.find("brace") != std::string::npos) {
        return "Beginner tip: Braces '{}' are used to group statements into blocks. "
               "Every opening brace '{' must have a matching closing brace '}'.";
    }
    
    if (errorMessage.find("Variable") != std::string::npos && errorMessage.find("not found") != std::string::npos) {
        return "Beginner tip: Variables must be declared before use. "
               "Use 'var variableName: type = value;' to create a new variable.";
    }
    
    return "This appears to be a common beginner error. Check the syntax carefully and refer to the language documentation.";
}

} // namespace ErrorHandling