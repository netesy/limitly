# Enhanced Error Messages Design Document

## Overview

This design document outlines the refactoring of the Limit programming language's error messaging system to provide more direct, informational, and useful error messages. The current system in `debugger.cpp` provides basic error reporting but lacks structured formatting, error codes, and modern compiler-style error presentation. The enhanced system will follow industry standards for compiler error messages while maintaining backward compatibility.

## Architecture

### Current System Analysis

The existing error handling system consists of:
- `Debugger` class with static methods for error reporting
- `InterpretationStage` enum for categorizing error types
- Basic console and file logging functionality
- Simple context line printing with basic highlighting
- Generic suggestion and sample solution generation

### Enhanced System Architecture

The new system will maintain the existing `Debugger` interface while significantly enhancing the internal implementation:

```
┌─────────────────────────────────────────────────────────────┐
│                    Enhanced Debugger                        │
├─────────────────────────────────────────────────────────────┤
│  ErrorFormatter                                             │
│  ├── StructuredErrorMessage                                 │
│  ├── ErrorCodeGenerator                                     │
│  ├── ContextualHintProvider                                 │
│  └── SourceCodeFormatter                                    │
├─────────────────────────────────────────────────────────────┤
│  ErrorCatalog                                               │
│  ├── ErrorDefinitions                                       │
│  ├── HintDatabase                                           │
│  └── SuggestionEngine                                       │
├─────────────────────────────────────────────────────────────┤
│  OutputFormatters                                           │
│  ├── ConsoleFormatter (human-readable)                     │
│  ├── IDEFormatter (machine-readable)                       │
│  └── LogFormatter (detailed logging)                       │
└─────────────────────────────────────────────────────────────┘
```

## Components and Interfaces

### 1. ErrorFormatter

**Purpose**: Central component responsible for creating structured error messages.

**Interface**:
```cpp
class ErrorFormatter {
public:
    struct ErrorMessage {
        std::string errorCode;        // e.g., "E102"
        std::string errorType;        // e.g., "SyntaxError"
        std::string description;      // Main error description
        std::string filePath;         // Source file path
        int line;                     // Line number
        int column;                   // Column number
        std::string problematicToken; // The specific token causing the issue
        std::string hint;             // Contextual hint
        std::string suggestion;       // Actionable suggestion
        std::string causedBy;         // Root cause information
        std::vector<std::string> contextLines; // Source code context
    };
    
    static ErrorMessage createErrorMessage(
        const std::string& errorMessage,
        int line, int column,
        InterpretationStage stage,
        const std::string& code,
        const std::string& lexeme = "",
        const std::string& expectedValue = "",
        const std::string& filePath = ""
    );
};
```

### 2. ErrorCodeGenerator

**Purpose**: Generates unique error codes based on error type and stage.

**Implementation Strategy**:
- Error codes follow format: `E###` where ### is a unique 3-digit number
- Code ranges allocated by category:
  - E001-E099: Lexical/Scanning errors
  - E100-E199: Syntax/Parsing errors  
  - E200-E299: Semantic errors
  - E300-E399: Type errors
  - E400-E499: Runtime errors
  - E500-E599: Bytecode generation errors

### 3. ContextualHintProvider

**Purpose**: Provides intelligent hints and suggestions based on error context.

**Features**:
- Pattern matching against common error scenarios
- Context-aware suggestions (e.g., missing braces, unclosed blocks)
- Educational hints for language-specific features
- Integration with error catalog for consistent messaging

### 4. SourceCodeFormatter

**Purpose**: Enhanced source code context display with better visual indicators.

**Features**:
- Multi-line context display with line numbers
- Visual indicators using Unicode characters (arrows, underlines)
- Syntax highlighting for better readability
- Block structure visualization for unclosed constructs

### 5. OutputFormatters

**Purpose**: Multiple output formats for different consumers.

**ConsoleFormatter**: Human-readable format following the specified pattern:
```
error[E102][SyntaxError]: Unexpected closing brace `}`
--> src/utils.calc:15:113
   |
14 |     let x = 514
15 |     return x + 1;
15 | }
   | ^ unexpected closing brace

Hint: It looks like you're missing an opening `{` before this line.
Suggestion: Did you forget to wrap a block like an `if`, `while`, or `function`?
Caused by: Unterminated block starting at line 11:
11 | function compute(x, y) =>
   | ----------------------- unclosed block starts here

File: src/utils.calc
```

## Data Models

### ErrorDefinition Structure
```cpp
struct ErrorDefinition {
    std::string code;           // Error code (e.g., "E102")
    std::string type;           // Error type (e.g., "SyntaxError")
    std::string pattern;        // Pattern to match error message
    std::string hintTemplate;   // Template for hint generation
    std::string suggestionTemplate; // Template for suggestion
    std::vector<std::string> commonCauses; // Common root causes
};
```

### Enhanced Error Context
```cpp
struct ErrorContext {
    std::string filePath;
    int line;
    int column;
    std::string sourceCode;
    std::string lexeme;
    std::string expectedValue;
    InterpretationStage stage;
    std::optional<BlockContext> blockContext; // For unclosed blocks
};

struct BlockContext {
    std::string blockType;      // "function", "if", "while", etc.
    int startLine;
    int startColumn;
    std::string startLexeme;
};
```

## Error Handling

### Error Code Assignment Strategy
- Maintain a central registry of error codes to prevent conflicts
- Use semantic versioning for error code compatibility
- Provide migration path for existing error handling code

### Backward Compatibility
- Maintain existing `Debugger::error()` method signature
- Add new overloaded methods for enhanced functionality
- Ensure existing error handling code continues to work

### Performance Considerations
- Lazy loading of error catalog and hint database
- Efficient string formatting using modern C++ techniques
- Minimal overhead for error-free execution paths

## Testing Strategy

### Unit Tests
- Test error code generation for all error types
- Verify hint and suggestion generation accuracy
- Test source code formatting with various edge cases
- Validate output format consistency

### Integration Tests
- Test error reporting through complete compilation pipeline
- Verify error messages in various file contexts
- Test multi-line error scenarios
- Validate IDE integration compatibility

### Regression Tests
- Ensure all existing error scenarios continue to work
- Test backward compatibility with existing error handling
- Verify performance impact is minimal

### Error Message Quality Tests
- Manual review of error message clarity and usefulness
- User experience testing with common error scenarios
- Validation against modern compiler error message standards

## Implementation Phases

### Phase 1: Core Infrastructure
- Implement `ErrorFormatter` and `ErrorMessage` structure
- Create `ErrorCodeGenerator` with basic code assignment
- Enhance `SourceCodeFormatter` with better context display

### Phase 2: Error Catalog and Intelligence
- Build comprehensive error catalog with codes and templates
- Implement `ContextualHintProvider` with pattern matching
- Add block context tracking for unclosed construct detection

### Phase 3: Output Formatting
- Implement multiple output formatters (Console, IDE, Log)
- Add configuration options for different output styles
- Integrate with existing logging infrastructure

### Phase 4: Advanced Features
- Add educational hints and language concept explanations
- Implement error grouping and relationship detection
- Add support for fix suggestions with code examples

## Migration Strategy

### Gradual Rollout
1. Implement new system alongside existing one
2. Add feature flags to switch between old and new systems
3. Gradually migrate error reporting call sites
4. Remove old system once migration is complete

### Configuration Options
- Allow users to choose between verbose and concise error formats
- Provide options for educational vs. expert-level messaging
- Support for different color schemes and formatting preferences