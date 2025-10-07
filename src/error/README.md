# Error Handling System

This directory contains the comprehensive error handling system for the Limit programming language. The system provides advanced error reporting, formatting, and recovery capabilities.

## Quick Start

### Simple Include (Recommended)

```cpp
#include "src/error/error_handling.hh"

int main() {
    // Error handling is automatically initialized
    ErrorHandling::reportError("Something went wrong!");
    return 0;
}
```

### Compilation

#### Using the Batch Script (Windows)
```bash
compile_with_error_handling.bat your_source.cpp your_output.exe
```

#### Using CMake
```bash
# In your CMakeLists.txt
add_subdirectory(src/error)
target_link_libraries(your_target ErrorHandling::ErrorHandling)
```

#### Manual Compilation
```bash
g++ -std=c++17 -I. your_source.cpp \
    src/error/console_formatter.cpp \
    src/error/error_formatter.cpp \
    src/error/error_catalog.cpp \
    src/error/contextual_hint_provider.cpp \
    src/error/error_code_generator.cpp \
    src/error/source_code_formatter.cpp \
    src/error/enhanced_error_reporting.cpp \
    src/error/ide_formatter.cpp \
    -o your_output
```

## Components

### Core Files
- `error_handling.hh/cpp` - Main include file and utilities
- `error_message.hh` - Error message structure definitions
- `error_formatter.hh/cpp` - Core error formatting logic

### Formatters
- `console_formatter.hh/cpp` - Console/terminal output formatting
- `source_code_formatter.hh/cpp` - Source code context formatting
- `ide_formatter.hh/cpp` - IDE-specific formatting

### Advanced Features
- `error_catalog.hh/cpp` - Error cataloging and lookup
- `error_code_generator.hh/cpp` - Error code generation
- `contextual_hint_provider.hh/cpp` - Context-aware suggestions
- `enhanced_error_reporting.hh/cpp` - Advanced reporting features

## Usage Examples

### Basic Error Reporting
```cpp
#include "src/error/error_handling.hh"

// Simple error
ErrorHandling::reportError("File not found");

// Detailed error with context
ErrorHandling::displayError(
    "Syntax error: missing semicolon",
    42,  // line
    15,  // column
    InterpretationStage::PARSING,
    sourceCode,
    "main.lm",
    "var x = 5",  // lexeme
    ";"           // expected
);
```

### Integration with Scanner/Parser
```cpp
#include "src/error/error_handling.hh"
#include "src/frontend/scanner.hh"

Scanner scanner(source);
auto tokens = scanner.scanTokens();
// Error handling is automatically integrated
```

## Benefits

1. **Single Include**: Just include `error_handling.hh` for everything
2. **Automatic Linking**: The compile script handles all dependencies
3. **Graceful Degradation**: Works even if some components are missing
4. **Cross-Platform**: Works with both batch scripts and CMake
5. **Comprehensive**: Covers all error handling needs

## Troubleshooting

### Linking Errors
If you get undefined reference errors, use the provided compile script:
```bash
compile_with_error_handling.bat your_file.cpp output.exe
```

### Missing Components
The system gracefully handles missing components and will fall back to basic error reporting if advanced features aren't available.

### CMake Integration
Add the error handling library to your CMakeLists.txt:
```cmake
add_subdirectory(src/error)
target_link_libraries(your_target ErrorHandling::ErrorHandling)
```