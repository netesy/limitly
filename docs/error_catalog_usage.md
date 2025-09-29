# ErrorCatalog Usage Guide

## Overview

The `ErrorCatalog` is a comprehensive system for managing error definitions, pattern matching, and generating contextual hints and suggestions for the Limit programming language. It provides a centralized repository of error information that can be used to enhance error reporting throughout the compiler and runtime.

## Key Features

- **Comprehensive Error Definitions**: 53+ predefined error definitions covering all interpretation stages
- **Pattern Matching**: Intelligent matching of error messages to appropriate error definitions
- **Template-based Hints and Suggestions**: Contextual help generation using template substitution
- **Stage-based Organization**: Errors organized by interpretation stage (lexical, syntax, semantic, runtime, etc.)
- **Thread-safe Operations**: Safe for use in multi-threaded environments
- **Extensible Design**: Support for adding custom error definitions

## Basic Usage

### 1. Initialize the Catalog

```cpp
#include "error_catalog.hh"

using namespace ErrorHandling;

// Get singleton instance and initialize
ErrorCatalog& catalog = ErrorCatalog::getInstance();
catalog.initialize();
```

### 2. Lookup Error Definitions

#### By Error Code
```cpp
const ErrorDefinition* def = catalog.lookupByCode("E102");
if (def) {
    std::cout << "Error Type: " << def->type << std::endl;
    std::cout << "Pattern: " << def->pattern << std::endl;
    std::cout << "Hint: " << def->hintTemplate << std::endl;
}
```

#### By Message Pattern
```cpp
const ErrorDefinition* def = catalog.lookupByMessage(
    "Unexpected closing brace '}' found", 
    InterpretationStage::PARSING
);
if (def) {
    std::cout << "Matched Error Code: " << def->code << std::endl;
}
```

### 3. Generate Contextual Messages

```cpp
// Create error context
ErrorContext context(
    "example.lm",           // file path
    15,                     // line number
    8,                      // column number
    "let x = y + z;",       // source code
    "y",                    // problematic lexeme
    "declared variable",    // expected value
    InterpretationStage::SEMANTIC
);

// Generate hint and suggestion
const ErrorDefinition* def = catalog.lookupByCode("E201");
if (def) {
    std::string hint = catalog.generateHint(*def, context);
    std::string suggestion = catalog.generateSuggestion(*def, context);
    
    std::cout << "Hint: " << hint << std::endl;
    std::cout << "Suggestion: " << suggestion << std::endl;
}
```

## Error Code Ranges

The ErrorCatalog organizes errors into specific code ranges based on interpretation stage:

| Range | Stage | Error Type | Description |
|-------|-------|------------|-------------|
| E001-E099 | SCANNING | LexicalError | Tokenization and character-level errors |
| E100-E199 | PARSING | SyntaxError | Grammar and syntax parsing errors |
| E200-E299 | SEMANTIC | SemanticError | Semantic analysis and type checking errors |
| E400-E499 | INTERPRETING | RuntimeError | Runtime execution errors |
| E500-E599 | BYTECODE | BytecodeError | Bytecode generation errors |
| E600-E699 | COMPILING | CompilationError | Compilation and linking errors |

## Common Error Definitions

### Lexical Errors (E001-E099)
- **E001**: Invalid character
- **E002**: Unterminated string
- **E003**: Unterminated comment
- **E004**: Invalid number format
- **E005**: Invalid escape sequence

### Syntax Errors (E100-E199)
- **E100**: Unexpected token
- **E101**: Expected specific token
- **E102**: Unexpected closing brace
- **E103**: Missing opening brace
- **E104**: Missing closing brace
- **E105**: Invalid factor
- **E106**: Missing semicolon
- **E107**: Invalid expression
- **E108**: Invalid statement
- **E109**: Unexpected end of file
- **E110**: Invalid function declaration
- **E111**: Invalid parameter list
- **E112**: Invalid variable declaration

### Semantic Errors (E200-E299)
- **E200**: Variable/function not found
- **E201**: Undefined variable
- **E202**: Undefined function
- **E203**: Variable already declared
- **E204**: Function already declared
- **E205**: Type mismatch
- **E206**: Invalid assignment
- **E207**: Invalid function call
- **E208**: Wrong number of arguments
- **E209**: Invalid return type

### Runtime Errors (E400-E499)
- **E400**: Division by zero
- **E401**: Modulo by zero
- **E402-E417**: Various runtime execution errors

## Advanced Usage

### Adding Custom Error Definitions

```cpp
ErrorDefinition customError(
    "E999",                                    // error code
    "CustomError",                             // error type
    "Custom error pattern",                    // pattern to match
    "This is a custom error hint template",    // hint template
    "This is a custom suggestion template",    // suggestion template
    {"Cause 1", "Cause 2"}                    // common causes
);

bool added = catalog.addDefinition(customError);
if (added) {
    std::cout << "Custom error definition added successfully" << std::endl;
}
```

### Getting Stage-specific Definitions

```cpp
auto syntaxErrors = catalog.getDefinitionsForStage(InterpretationStage::PARSING);
std::cout << "Found " << syntaxErrors.size() << " syntax error definitions" << std::endl;

for (const auto* def : syntaxErrors) {
    std::cout << "  " << def->code << ": " << def->pattern << std::endl;
}
```

### Template Substitution

The ErrorCatalog supports template substitution in hint and suggestion templates using the following placeholders:

- `{lexeme}`: The problematic token or lexeme
- `{expected}`: The expected value or token
- `{file}`: The source file path
- `{line}`: The line number
- `{column}`: The column number

Example template:
```
"The variable '{lexeme}' is not declared. Expected a declared variable at line {line}."
```

## Integration with Existing Error System

### With ErrorCodeGenerator

```cpp
#include "error_code_generator.hh"
#include "error_catalog.hh"

// Generate error code
std::string errorCode = ErrorCodeGenerator::generateErrorCode(
    InterpretationStage::PARSING, 
    "Unexpected token"
);

// Look up definition in catalog
const ErrorDefinition* def = catalog.lookupByCode(errorCode);
if (def) {
    // Use definition for enhanced error reporting
    std::cout << "Error: " << def->type << " " << errorCode << std::endl;
    std::cout << "Hint: " << def->hintTemplate << std::endl;
}
```

### With Debugger

```cpp
#include "debugger.hh"
#include "error_catalog.hh"

void enhancedErrorReporting(const std::string& errorMessage, 
                           int line, int column, 
                           InterpretationStage stage,
                           const std::string& code,
                           const std::string& lexeme) {
    
    // Look up error definition
    const ErrorDefinition* def = catalog.lookupByMessage(errorMessage, stage);
    
    if (def) {
        // Create context for template substitution
        ErrorContext context("", line, column, code, lexeme, "", stage);
        
        // Generate enhanced messages
        std::string hint = catalog.generateHint(*def, context);
        std::string suggestion = catalog.generateSuggestion(*def, context);
        
        // Use existing debugger with enhanced information
        Debugger::error(errorMessage, line, column, stage, code, lexeme, suggestion);
        
        // Additional enhanced output
        std::cout << "Enhanced Hint: " << hint << std::endl;
        std::cout << "Common Causes: ";
        auto causes = catalog.getCommonCauses(def->code);
        for (size_t i = 0; i < causes.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << causes[i];
        }
        std::cout << std::endl;
    } else {
        // Fall back to standard error reporting
        Debugger::error(errorMessage, line, column, stage, code, lexeme);
    }
}
```

## Thread Safety

The ErrorCatalog is designed to be thread-safe:

- All public methods use mutex locking for thread safety
- Multiple threads can safely read from the catalog simultaneously
- Initialization is protected against race conditions
- Adding/removing definitions is thread-safe

## Performance Considerations

- **Initialization**: The catalog initializes all definitions once and caches them
- **Pattern Matching**: Uses compiled regex patterns for efficient matching
- **Lookup Operations**: O(1) lookup by error code, O(n) pattern matching
- **Memory Usage**: Definitions are stored in memory for fast access

## Testing

The ErrorCatalog includes comprehensive unit tests covering:

- Singleton pattern behavior
- Initialization and cleanup
- Error definition lookup (by code and message)
- Stage-based filtering
- Custom definition management
- Hint and suggestion generation
- Thread safety
- Comprehensive error coverage

Run tests with:
```bash
tests/run_error_catalog_tests.bat
```

## Best Practices

1. **Initialize Early**: Initialize the catalog once at application startup
2. **Use Pattern Matching**: Leverage message pattern matching for flexible error classification
3. **Provide Context**: Always provide rich ErrorContext for better template substitution
4. **Handle Missing Definitions**: Always check for null returns from lookup methods
5. **Stage-specific Lookup**: Use stage information to improve pattern matching accuracy
6. **Custom Definitions**: Add project-specific error definitions for domain-specific errors

## Example: Complete Error Handling Flow

```cpp
void handleCompilerError(const std::string& sourceFile,
                        const std::string& sourceCode,
                        const std::string& errorMessage,
                        int line, int column,
                        const std::string& lexeme,
                        InterpretationStage stage) {
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    
    // Look up error definition
    const ErrorDefinition* def = catalog.lookupByMessage(errorMessage, stage);
    
    if (def) {
        // Create rich error context
        ErrorContext context(sourceFile, line, column, sourceCode, 
                           lexeme, "", stage);
        
        // Generate enhanced messages
        std::string hint = catalog.generateHint(*def, context);
        std::string suggestion = catalog.generateSuggestion(*def, context);
        auto causes = catalog.getCommonCauses(def->code);
        
        // Create complete error message
        ErrorMessage errorMsg(def->code, def->type, errorMessage,
                            sourceFile, line, column, lexeme, stage);
        errorMsg.hint = hint;
        errorMsg.suggestion = suggestion;
        
        // Output enhanced error information
        std::cout << "Error " << errorMsg.errorCode << " (" << errorMsg.errorType << ")" << std::endl;
        std::cout << "File: " << errorMsg.filePath << ":" << errorMsg.line << ":" << errorMsg.column << std::endl;
        std::cout << "Description: " << errorMsg.description << std::endl;
        std::cout << "Hint: " << errorMsg.hint << std::endl;
        std::cout << "Suggestion: " << errorMsg.suggestion << std::endl;
        
        if (!causes.empty()) {
            std::cout << "Common Causes: ";
            for (size_t i = 0; i < causes.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << causes[i];
            }
            std::cout << std::endl;
        }
    } else {
        // Fall back to basic error reporting
        std::cout << "Error: " << errorMessage << std::endl;
        std::cout << "Location: " << sourceFile << ":" << line << ":" << column << std::endl;
    }
}
```

This comprehensive error handling approach provides users with detailed, contextual information to help them understand and fix errors in their Limit programs.