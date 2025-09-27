# ErrorCodeGenerator Implementation

## Overview

The `ErrorCodeGenerator` class provides a systematic way to generate unique, consistent error codes for the Limit programming language. It's designed to integrate seamlessly with the existing error handling system while providing enhanced error reporting capabilities.

## Features

### 1. Stage-Based Code Allocation
Error codes are allocated based on the `InterpretationStage` where the error occurs:

- **E001-E099**: Lexical/Scanning errors
- **E100-E199**: Syntax/Parsing errors  
- **E200-E299**: Semantic errors
- **E300-E399**: Type errors (reserved for future use)
- **E400-E499**: Runtime/Interpreting errors
- **E500-E599**: Bytecode generation errors
- **E600-E699**: Compilation errors

### 2. Message-Specific Code Mapping
Common error messages are mapped to specific codes for consistency:

```cpp
// Examples of predefined mappings
"Division by zero" -> E400
"Unexpected token" -> E100
"Invalid character" -> E001
"Variable/function not found" -> E200
```

### 3. Thread-Safe Operation
The class uses mutex protection to ensure thread-safe code generation and registration, making it suitable for concurrent compilation scenarios.

### 4. Error Type Mapping
Automatic mapping from `InterpretationStage` to human-readable error types:

```cpp
InterpretationStage::SCANNING -> "LexicalError"
InterpretationStage::PARSING -> "SyntaxError"
InterpretationStage::SEMANTIC -> "SemanticError"
InterpretationStage::INTERPRETING -> "RuntimeError"
// etc.
```

## Usage

### Basic Error Code Generation

```cpp
#include "error_code_generator.hh"
using namespace ErrorHandling;

// Generate code for a specific stage
std::string code = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
// Returns: "E100" (or next available code in range)

// Generate code for specific error message
std::string divCode = ErrorCodeGenerator::generateErrorCode(
    InterpretationStage::INTERPRETING, 
    "Division by zero"
);
// Returns: "E400" (consistent mapping)
```

### Getting Error Types

```cpp
std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING);
// Returns: "SyntaxError"
```

### Creating Complete Error Messages

```cpp
// Generate code and type
std::string errorCode = ErrorCodeGenerator::generateErrorCode(
    InterpretationStage::PARSING, 
    "Unexpected token"
);
std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING);

// Create complete error message
ErrorMessage errorMsg(
    errorCode,                    // "E100"
    errorType,                    // "SyntaxError"
    "Unexpected token ';'",       // Description
    "src/main.lm",               // File path
    15,                          // Line
    23,                          // Column
    ";",                         // Problematic token
    InterpretationStage::PARSING // Stage
);
```

### Registry Management

```cpp
// Check if a code is registered
bool isRegistered = ErrorCodeGenerator::isCodeRegistered("E100");

// Get all codes for a specific stage
auto parsingCodes = ErrorCodeGenerator::getRegisteredCodes(InterpretationStage::PARSING);

// Get total registered code count
size_t totalCodes = ErrorCodeGenerator::getRegisteredCodeCount();

// Clear registry (mainly for testing)
ErrorCodeGenerator::clearRegistry();
```

## Data Structures

### ErrorMessage
Complete structured error message with all enhanced information:

```cpp
struct ErrorMessage {
    std::string errorCode;        // "E102"
    std::string errorType;        // "SyntaxError"
    std::string description;      // Main error description
    std::string filePath;         // Source file path
    int line;                     // Line number
    int column;                   // Column number
    std::string problematicToken; // Specific token causing issue
    std::string hint;             // Contextual hint
    std::string suggestion;       // Actionable suggestion
    std::string causedBy;         // Root cause information
    std::vector<std::string> contextLines; // Source code context
    InterpretationStage stage;    // Stage where error occurred
    
    bool isComplete() const;      // Check if all required fields are set
    bool hasEnhancedInfo() const; // Check if enhanced info is available
};
```

### ErrorContext
Enhanced context information for error reporting:

```cpp
struct ErrorContext {
    std::string filePath;
    int line;
    int column;
    std::string sourceCode;
    std::string lexeme;
    std::string expectedValue;
    InterpretationStage stage;
    std::optional<BlockContext> blockContext; // For unclosed constructs
};
```

### BlockContext
Information about block structures for "Caused by" messages:

```cpp
struct BlockContext {
    std::string blockType;      // "function", "if", "while", etc.
    int startLine;
    int startColumn;
    std::string startLexeme;    // Opening token/keyword
};
```

## Integration with Existing System

The ErrorCodeGenerator is designed to work alongside the existing `Debugger` class:

```cpp
// Current debugger usage
Debugger::error("Unexpected token", line, column, stage, code, lexeme, expected);

// Enhanced usage with ErrorCodeGenerator
std::string errorCode = ErrorCodeGenerator::generateErrorCode(stage, "Unexpected token");
std::string errorType = ErrorCodeGenerator::getErrorType(stage);

ErrorMessage enhancedError(errorCode, errorType, "Unexpected token", 
                          filePath, line, column, lexeme, stage);
// Use enhancedError for formatted output
```

## Testing

The implementation includes comprehensive unit tests:

### Test Files
- `tests/unit/test_error_code_generator.cpp` - Core functionality tests
- `tests/unit/test_error_code_integration.cpp` - Integration tests
- `tests/unit/error_code_generator_demo.cpp` - Usage demonstration

### Running Tests

```bash
# Windows
cd tests/unit
g++ -std=c++17 -I../../src -o ../../bin/test_error_code_generator.exe test_error_code_generator.cpp ../../src/error_code_generator.cpp
../../bin/test_error_code_generator.exe

# Or use the provided build script
build_and_test_error_code_generator.bat
```

### Test Coverage
- ✅ Basic error code generation for all stages
- ✅ Error type mapping consistency
- ✅ Message-specific code generation
- ✅ Code registration and conflict prevention
- ✅ Thread safety with concurrent code generation
- ✅ Edge cases (empty messages, unknown messages, case sensitivity)
- ✅ Integration with existing InterpretationStage enum
- ✅ ErrorMessage and context structure creation

## Performance Considerations

- **Lazy Initialization**: Message mapping is initialized only when first needed
- **Efficient Lookups**: Uses hash maps for O(1) code registration checks
- **Minimal Overhead**: Code generation has minimal impact on error-free execution paths
- **Thread Safety**: Mutex protection with minimal lock contention

## Future Enhancements

The ErrorCodeGenerator provides a foundation for:

1. **ErrorFormatter**: Central coordinator for creating complete error messages
2. **ContextualHintProvider**: Intelligent hint generation based on error patterns
3. **SourceCodeFormatter**: Enhanced source code context display
4. **OutputFormatters**: Multiple output formats (console, IDE, log)
5. **ErrorCatalog**: Comprehensive database of error definitions and templates

## Error Code Registry

The system maintains a registry of all generated error codes to prevent conflicts and ensure uniqueness. This registry is thread-safe and provides methods for:

- Checking if a code is already registered
- Getting all codes for a specific stage
- Clearing the registry (for testing)
- Getting total registered code count

## Consistency Guarantees

- **Same Message, Same Code**: Identical error messages in the same stage always get the same code
- **Stage Isolation**: Codes are allocated within stage-specific ranges
- **Thread Safety**: Concurrent code generation produces unique codes
- **Deterministic**: Code generation is deterministic for the same sequence of calls

This implementation provides a solid foundation for the enhanced error messaging system while maintaining compatibility with the existing codebase.