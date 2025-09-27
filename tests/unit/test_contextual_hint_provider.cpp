#include "../../src/contextual_hint_provider.hh"
#include <cassert>
#include <iostream>
#include <string>

using namespace ErrorHandling;

// Test helper function
void assertContains(const std::string& text, const std::string& substring, const std::string& testName) {
    if (text.find(substring) == std::string::npos) {
        std::cerr << "FAIL: " << testName << " - Expected '" << text << "' to contain '" << substring << "'" << std::endl;
        assert(false);
    } else {
        std::cout << "PASS: " << testName << std::endl;
    }
}

void assertNotEmpty(const std::string& text, const std::string& testName) {
    if (text.empty()) {
        std::cerr << "FAIL: " << testName << " - Expected non-empty string" << std::endl;
        assert(false);
    } else {
        std::cout << "PASS: " << testName << std::endl;
    }
}

void assertEqual(const std::string& actual, const std::string& expected, const std::string& testName) {
    if (actual != expected) {
        std::cerr << "FAIL: " << testName << " - Expected '" << expected << "' but got '" << actual << "'" << std::endl;
        assert(false);
    } else {
        std::cout << "PASS: " << testName << std::endl;
    }
}

void assertTrue(bool condition, const std::string& testName) {
    if (!condition) {
        std::cerr << "FAIL: " << testName << " - Expected true" << std::endl;
        assert(false);
    } else {
        std::cout << "PASS: " << testName << std::endl;
    }
}

// Test initialization
void testInitialization() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    
    // Should not be initialized initially
    assertTrue(!provider.isInitialized(), "Provider not initialized initially");
    
    // Initialize
    provider.initialize();
    assertTrue(provider.isInitialized(), "Provider initialized after initialize()");
    
    // Should be safe to initialize multiple times
    provider.initialize();
    assertTrue(provider.isInitialized(), "Provider still initialized after second initialize()");
}

// Test lexical error hints
void testLexicalErrorHints() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 5, 10, "let x = 'unterminated", "'", "", InterpretationStage::SCANNING);
    
    // Test unterminated string hint
    std::string hint = provider.generateHint("Unterminated string", context);
    assertContains(hint, "String literals must be enclosed", "Unterminated string hint");
    assertContains(hint, "escape sequence", "Unterminated string hint mentions escape");
    
    // Test unterminated string suggestion
    std::string suggestion = provider.generateSuggestion("Unterminated string", context);
    assertContains(suggestion, "closing quote", "Unterminated string suggestion");
    
    // Test invalid character
    context.lexeme = "@";
    hint = provider.generateHint("Invalid character", context);
    assertContains(hint, "not recognized", "Invalid character hint");
    
    suggestion = provider.generateSuggestion("Invalid character", context);
    assertContains(suggestion, "Remove the invalid character", "Invalid character suggestion");
    assertContains(suggestion, "@", "Invalid character suggestion includes lexeme");
}

// Test syntax error hints
void testSyntaxErrorHints() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 10, 5, "fn test() { let x = 5 }", "}", "", InterpretationStage::PARSING);
    
    // Test unexpected closing brace
    std::string hint = provider.generateHint("Unexpected closing brace", context);
    assertContains(hint, "doesn't have a matching opening brace", "Unexpected closing brace hint");
    
    std::string suggestion = provider.generateSuggestion("Unexpected closing brace", context);
    assertContains(suggestion, "remove this extra", "Unexpected closing brace suggestion");
    
    // Test missing semicolon
    hint = provider.generateHint("Missing semicolon", context);
    assertContains(hint, "statements must end with a semicolon", "Missing semicolon hint");
    
    suggestion = provider.generateSuggestion("Missing semicolon", context);
    assertContains(suggestion, "Add a semicolon", "Missing semicolon suggestion");
    
    // Test with block context
    context.blockContext = BlockContext("function", 8, 1, "fn test()");
    hint = provider.generateHint("Missing opening brace", context);
    assertContains(hint, "function block needs", "Missing opening brace with block context");
}

// Test semantic error hints
void testSemanticErrorHints() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 15, 8, "let y = x + 5;", "x", "", InterpretationStage::SEMANTIC);
    
    // Test undefined variable
    std::string hint = provider.generateHint("Variable not found", context);
    assertContains(hint, "must be declared before", "Undefined variable hint");
    assertContains(hint, "let variableName", "Undefined variable hint shows syntax");
    
    std::string suggestion = provider.generateSuggestion("Variable not found", context);
    assertContains(suggestion, "Check the spelling", "Undefined variable suggestion");
    assertContains(suggestion, "x", "Undefined variable suggestion includes variable name");
    
    // Test undefined function
    context.lexeme = "myFunction";
    hint = provider.generateHint("Function not found", context);
    assertContains(hint, "must be defined before", "Undefined function hint");
    
    suggestion = provider.generateSuggestion("Function not found", context);
    assertContains(suggestion, "Define the function", "Undefined function suggestion");
    assertContains(suggestion, "myFunction", "Undefined function suggestion includes function name");
    
    // Test type mismatch
    hint = provider.generateHint("Type mismatch", context);
    assertContains(hint, "strong type system", "Type mismatch hint");
    assertContains(hint, "explicit type conversion", "Type mismatch hint mentions conversion");
}

// Test runtime error hints
void testRuntimeErrorHints() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 20, 12, "let result = x / 0;", "0", "", InterpretationStage::INTERPRETING);
    
    // Test division by zero
    std::string hint = provider.generateHint("Division by zero", context);
    assertContains(hint, "mathematically undefined", "Division by zero hint");
    assertContains(hint, "check that your divisor", "Division by zero hint mentions checking");
    
    std::string suggestion = provider.generateSuggestion("Division by zero", context);
    assertContains(suggestion, "Add a check", "Division by zero suggestion");
    assertContains(suggestion, "!= 0", "Division by zero suggestion shows check syntax");
    
    // Test stack overflow
    hint = provider.generateHint("Stack overflow", context);
    assertContains(hint, "infinite recursion", "Stack overflow hint");
    assertContains(hint, "base cases", "Stack overflow hint mentions base cases");
    
    suggestion = provider.generateSuggestion("Stack overflow", context);
    assertContains(suggestion, "base case", "Stack overflow suggestion");
    
    // Test null reference
    hint = provider.generateHint("Null reference", context);
    assertContains(hint, "uninitialized or null", "Null reference hint");
    assertContains(hint, "Option types", "Null reference hint mentions Option types");
}

// Test educational hints
void testEducationalHints() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 5, 10, "let x = y;", "y", "", InterpretationStage::SEMANTIC);
    
    // Test educational hint generation
    std::string educationalHint = provider.generateEducationalHint("Variable not found", context);
    assertNotEmpty(educationalHint, "Educational hint generated for variable error");
    
    // Test language feature explanations
    std::string explanation = provider.getLanguageFeatureExplanation("variables");
    assertContains(explanation, "let name: type", "Variables explanation contains syntax");
    
    explanation = provider.getLanguageFeatureExplanation("functions");
    assertContains(explanation, "fn name(params)", "Functions explanation contains syntax");
    
    explanation = provider.getLanguageFeatureExplanation("nonexistent");
    assertTrue(explanation.empty(), "Non-existent feature returns empty string");
}

// Test beginner error detection
void testBeginnerErrorDetection() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 5, 10, "let x = 5", "", "", InterpretationStage::PARSING);
    
    // Test beginner error detection
    assertTrue(provider.isBeginnerError("Missing semicolon", context), "Missing semicolon is beginner error");
    assertTrue(provider.isBeginnerError("Invalid character", context), "Invalid character is beginner error");
    assertTrue(provider.isBeginnerError("Variable not found", context), "Undefined variable is beginner error");
    assertTrue(!provider.isBeginnerError("Stack overflow", context), "Stack overflow is not beginner error");
    assertTrue(!provider.isBeginnerError("Complex type inference error", context), "Complex error is not beginner error");
}

// Test caused by message generation
void testCausedByMessages() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 15, 5, "fn test() { let x = 5; }", "", "", InterpretationStage::PARSING);
    
    // Test without block context
    std::string causedBy = provider.generateCausedByMessage(context);
    assertTrue(causedBy.empty(), "No caused by message without block context");
    
    // Test with block context
    context.blockContext = BlockContext("function", 10, 1, "fn test()");
    causedBy = provider.generateCausedByMessage(context);
    assertContains(causedBy, "Caused by", "Caused by message starts correctly");
    assertContains(causedBy, "function", "Caused by message mentions block type");
    assertContains(causedBy, "line 10", "Caused by message mentions line number");
    assertContains(causedBy, "fn test()", "Caused by message includes start lexeme");
}

// Test common causes explanation
void testCommonCausesExplanation() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 5, 10, "let x = 'test", "", "", InterpretationStage::SCANNING);
    
    // Test common causes for unterminated string
    std::string causes = provider.explainCommonCauses("Unterminated string", context);
    assertContains(causes, "Common causes", "Common causes explanation starts correctly");
    assertContains(causes, "Missing closing quote", "Common causes includes missing quote");
    
    // Test common causes for variable not found
    causes = provider.explainCommonCauses("Variable not found", context);
    assertContains(causes, "Typo in variable name", "Common causes includes typo");
    assertContains(causes, "Variable not declared", "Common causes includes not declared");
}

// Test custom pattern addition
void testCustomPatterns() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    // Clear any existing custom patterns
    provider.clearCustomPatterns();
    
    // Add custom hint pattern
    bool success = provider.addCustomHintPattern(
        "Custom error pattern",
        [](const ErrorContext& ctx) {
            return "This is a custom hint for: " + ctx.lexeme;
        }
    );
    assertTrue(success, "Custom hint pattern added successfully");
    
    // Add custom suggestion pattern
    success = provider.addCustomSuggestionPattern(
        "Custom error pattern",
        [](const ErrorContext& ctx) {
            return "Custom suggestion: fix " + ctx.lexeme;
        }
    );
    assertTrue(success, "Custom suggestion pattern added successfully");
    
    // Test custom patterns work
    ErrorContext context("test.lm", 5, 10, "some code", "token", "", InterpretationStage::PARSING);
    std::string hint = provider.generateHint("Custom error pattern", context);
    assertContains(hint, "This is a custom hint", "Custom hint pattern works");
    assertContains(hint, "token", "Custom hint includes lexeme");
    
    std::string suggestion = provider.generateSuggestion("Custom error pattern", context);
    assertContains(suggestion, "Custom suggestion", "Custom suggestion pattern works");
    assertContains(suggestion, "token", "Custom suggestion includes lexeme");
    
    // Test invalid regex pattern
    success = provider.addCustomHintPattern("[invalid regex", [](const ErrorContext&) { return ""; });
    assertTrue(!success, "Invalid regex pattern rejected");
    
    // Clear custom patterns
    provider.clearCustomPatterns();
    hint = provider.generateHint("Custom error pattern", context);
    assertTrue(hint.empty() || hint.find("This is a custom hint") == std::string::npos, 
               "Custom patterns cleared successfully");
}

// Test template substitution with error definitions
void testTemplateSubstitution() {
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    ErrorContext context("test.lm", 10, 5, "let x = y;", "y", "identifier", InterpretationStage::SEMANTIC);
    
    // Create a mock error definition with templates
    ErrorDefinition definition("E200", "SemanticError", "Variable not found",
                              "The variable '{lexeme}' at line {line} is not declared.",
                              "Declare '{lexeme}' before using it at line {line}.");
    
    std::string hint = provider.generateHint("Variable not found", context, &definition);
    assertContains(hint, "variable 'y'", "Template substitution replaces lexeme");
    assertContains(hint, "line 10", "Template substitution replaces line");
    
    std::string suggestion = provider.generateSuggestion("Variable not found", context, &definition);
    assertContains(suggestion, "Declare 'y'", "Template substitution in suggestion");
    assertContains(suggestion, "line 10", "Template substitution replaces line in suggestion");
}

int main() {
    std::cout << "Running ContextualHintProvider tests..." << std::endl;
    
    try {
        testInitialization();
        testLexicalErrorHints();
        testSyntaxErrorHints();
        testSemanticErrorHints();
        testRuntimeErrorHints();
        testEducationalHints();
        testBeginnerErrorDetection();
        testCausedByMessages();
        testCommonCausesExplanation();
        testCustomPatterns();
        testTemplateSubstitution();
        
        std::cout << "\nAll ContextualHintProvider tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}