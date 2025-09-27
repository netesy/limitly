# ContextualHintProvider Usage Guide

## Overview

The `ContextualHintProvider` class is a key component of the enhanced error messaging system in the Limit programming language. It provides intelligent hint generation, actionable suggestions, and educational content to help developers understand and fix errors in their code.

## Features

### 1. Intelligent Hint Generation
- Context-aware hints based on error patterns and interpretation stage
- Educational explanations about language features
- Beginner-friendly explanations for common errors

### 2. Actionable Suggestions
- Specific recommendations for fixing errors
- Code examples and syntax guidance
- Step-by-step fix instructions

### 3. Educational Content
- Language feature explanations
- Common error cause analysis
- Beginner error detection and special handling

### 4. Block Context Tracking
- "Caused by" messages for unclosed constructs
- Block relationship analysis
- Context-aware error correlation

### 5. Extensibility
- Custom pattern registration
- Template-based message generation
- Priority-based pattern matching

## Basic Usage

### Initialization

```cpp
#include "contextual_hint_provider.hh"

using namespace ErrorHandling;

// Get singleton instance and initialize
ContextualHintProvider& provider = ContextualHintProvider::getInstance();
provider.initialize();
```

### Generating Hints and Suggestions

```cpp
// Create error context
ErrorContext context("example.lm", 10, 5, sourceCode, "variableName", "", InterpretationStage::SEMANTIC);

// Generate hint
std::string hint = provider.generateHint("Variable not found", context);
// Result: "Variables must be declared before they can be used. In Limit, use 'let variableName: type = value;' to declare variables."

// Generate suggestion
std::string suggestion = provider.generateSuggestion("Variable not found", context);
// Result: "Check the spelling of 'variableName' or declare it with 'let variableName: type = value;'"
```

### Educational Content

```cpp
// Get language feature explanation
std::string explanation = provider.getLanguageFeatureExplanation("functions");
// Result: "Functions are declared with 'fn name(params) -> returnType { ... }' Parameters can have optional types with '?' and default values."

// Generate educational hint
std::string educationalHint = provider.generateEducationalHint("Variable not found", context);
// Result: "Language feature: Variables in Limit are declared with 'let name: type = value;' Type annotations are optional when the type can be inferred."
```

### Block Context and "Caused By" Messages

```cpp
// Create context with block information
ErrorContext context("example.lm", 15, 1, sourceCode, "}", "", InterpretationStage::PARSING);
context.blockContext = BlockContext("function", 10, 1, "fn test()");

// Generate "caused by" message
std::string causedBy = provider.generateCausedByMessage(context);
// Result: "Caused by: Unterminated function starting at line 10:\n10 | fn test()\n   | --------- unclosed block starts here"
```

## Advanced Usage

### Custom Pattern Registration

```cpp
// Add custom hint pattern
bool success = provider.addCustomHintPattern(
    "Custom validation error",
    [](const ErrorContext& ctx) {
        return "This is a custom validation error. Check your input data at line " + 
               std::to_string(ctx.line) + ".";
    }
);

// Add custom suggestion pattern
success = provider.addCustomSuggestionPattern(
    "Custom validation error",
    [](const ErrorContext& ctx) {
        return "Validate your input using the validation framework before processing.";
    }
);
```

### Template-Based Generation with Error Definitions

```cpp
// Create error definition with templates
ErrorDefinition definition("E200", "SemanticError", "Variable not found",
                          "The variable '{lexeme}' at line {line} is not declared.",
                          "Declare '{lexeme}' before using it at line {line}.");

// Generate hint using definition template
std::string hint = provider.generateHint("Variable not found", context, &definition);
// Result: "The variable 'variableName' at line 10 is not declared."
```

## Error Categories and Patterns

### Lexical Errors (Scanning Stage)
- Invalid characters
- Unterminated strings
- Invalid number formats
- Invalid escape sequences

### Syntax Errors (Parsing Stage)
- Unexpected tokens
- Missing delimiters (braces, semicolons)
- Invalid expressions
- Malformed statements

### Semantic Errors (Semantic Stage)
- Undefined variables/functions
- Type mismatches
- Invalid assignments
- Wrong parameter counts

### Runtime Errors (Interpreting Stage)
- Division by zero
- Stack overflow
- Null references
- Out of bounds access

## Integration with Error Catalog

The `ContextualHintProvider` works seamlessly with the `ErrorCatalog`:

```cpp
#include "error_catalog.hh"

// Get error definition from catalog
const ErrorDefinition* definition = ErrorCatalog::getInstance().lookupByMessage("Variable not found", InterpretationStage::SEMANTIC);

// Use definition for enhanced hint generation
std::string hint = provider.generateHint("Variable not found", context, definition);
```

## Best Practices

### 1. Initialize Once
```cpp
// Initialize the provider once at application startup
ContextualHintProvider& provider = ContextualHintProvider::getInstance();
provider.initialize();
```

### 2. Provide Complete Context
```cpp
// Always provide as much context as possible
ErrorContext context(filePath, line, column, sourceCode, lexeme, expectedValue, stage);

// Add block context when available
if (inBlock) {
    context.blockContext = BlockContext(blockType, startLine, startColumn, startLexeme);
}
```

### 3. Use Appropriate Error Stages
```cpp
// Match the interpretation stage to the error type
ErrorContext lexicalContext(..., InterpretationStage::SCANNING);
ErrorContext syntaxContext(..., InterpretationStage::PARSING);
ErrorContext semanticContext(..., InterpretationStage::SEMANTIC);
ErrorContext runtimeContext(..., InterpretationStage::INTERPRETING);
```

### 4. Handle Empty Results
```cpp
std::string hint = provider.generateHint(errorMessage, context);
if (!hint.empty()) {
    // Display hint to user
    std::cout << "Hint: " << hint << std::endl;
}
```

## Testing

The implementation includes comprehensive unit tests covering:

- Pattern matching accuracy
- Template substitution
- Educational content generation
- Custom pattern functionality
- Block context handling
- Beginner error detection

Run tests with:
```bash
g++ -std=c++17 -I./src -o test_contextual_hint_provider.exe tests/unit/test_contextual_hint_provider.cpp src/contextual_hint_provider.cpp
./test_contextual_hint_provider.exe
```

## Performance Considerations

- Patterns are sorted by priority for efficient matching
- Regex compilation is cached
- Thread-safe singleton implementation
- Lazy initialization of language features

## Extensibility

The system is designed for easy extension:

1. **Add New Error Categories**: Extend initialization methods
2. **Custom Pattern Types**: Implement new pattern matching strategies  
3. **Language Feature Updates**: Update language feature explanations
4. **Integration Points**: Easy integration with other error handling components

## Example Output

```
--- Semantic Error: Undefined Variable ---
Error: Variable not found
Location: example.lm:8:10
Hint: Variables must be declared before they can be used. In Limit, use 'let variableName: type = value;' to declare variables.
Suggestion: Check the spelling of 'unknownVar' or declare it with 'let unknownVar: type = value;'
Educational: Language feature: Variables in Limit are declared with 'let name: type = value;' Type annotations are optional when the type can be inferred.
Common Causes: Common causes: Typo in variable name, Variable not declared, Out of scope
Note: This appears to be a common beginner error.
```

This comprehensive hint system significantly improves the developer experience by providing contextual, actionable, and educational error messages.