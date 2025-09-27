# Implementation Plan

- [x] 1. Create core error message data structures





  - Define `ErrorMessage` struct with all required fields (errorCode, errorType, description, filePath, line, column, etc.)
  - Define `ErrorContext` and `BlockContext` structs for enhanced context tracking
  - Create `ErrorDefinition` struct for error catalog entries
  - _Requirements: 1.1, 1.2, 1.3, 1.4_

- [x] 2. Implement ErrorCodeGenerator class





  - Create static method to generate unique error codes based on InterpretationStage
  - Implement code range allocation (E001-E099 for lexical, E100-E199 for syntax, etc.)
  - Add error code registry to prevent conflicts
  - Write unit tests for error code generation consistency
  - _Requirements: 1.1_

- [x] 3. Create enhanced SourceCodeFormatter class





  - Implement method to extract and format source code context with line numbers
  - Add visual indicators using Unicode characters (arrows, underlines, carets)
  - Create multi-line context display with proper alignment
  - Add support for highlighting specific tokens and ranges
  - Write unit tests for various source code formatting scenarios
  - _Requirements: 1.4, 3.1, 3.2, 3.3, 3.4_

- [x] 4. Build ErrorCatalog with predefined error definitions






  - Create comprehensive catalog of error definitions with codes, types, and templates
  - Implement pattern matching system for error message classification
  - Add hint and suggestion templates for common error scenarios
  - Create method to lookup error definitions by message pattern
  - Write unit tests for error catalog lookup and matching
  - _Requirements: 2.1, 2.2, 5.1, 5.2_

- [x] 5. Implement ContextualHintProvider class





  - Create intelligent hint generation based on error context and patterns
  - Implement suggestion engine with actionable recommendations
  - Add support for educational hints about language features
  - Create method to detect and explain common error causes
  - Write unit tests for hint and suggestion generation accuracy
  - _Requirements: 2.1, 2.2, 2.3, 5.1, 5.2, 5.3, 5.4_

- [x] 6. Develop block context tracking system





  - ✅ Enhance parser to track block start locations (functions, if statements, loops)
  - ✅ Implement BlockContext detection for unclosed constructs
  - ✅ Add method to correlate closing brace errors with their opening counterparts
  - ✅ Create "Caused by" message generation for block-related errors
  - ✅ Write unit tests for block context tracking and error correlation
  - _Requirements: 2.4, 3.1_

- [x] 7. Create ErrorFormatter class as central coordinator




  - Implement main `createErrorMessage` method that orchestrates all components
  - Integrate ErrorCodeGenerator, ContextualHintProvider, and SourceCodeFormatter
  - Add logic to populate all ErrorMessage fields from input parameters
  - Create method to handle different error types and stages appropriately
  - Write integration tests for complete error message creation
  - _Requirements: 1.1, 1.2, 1.3, 1.4, 2.1, 2.2, 2.3, 2.4_

- [x] 8. Implement ConsoleFormatter for human-readable output





  - Create formatter that produces the specified error message format
  - Implement proper spacing, alignment, and visual hierarchy
  - Add color support for different error message components
  - Create method to format file path, line, and column information
  - Write unit tests for console output formatting consistency
  - _Requirements: 1.1, 1.2, 1.3, 1.4, 3.2, 3.3, 3.4_

- [x] 9. Create IDEFormatter for machine-readable output











  - Implement structured output format that IDEs can parse
  - Add metadata fields required for IDE integration
  - Add the correct Hints and Suggestions for all errors in our codebase (vm.cpp, backend.cpp and type_checker.cpp) in contextual_hint_provider.cpp 
  - Create consistent format for batch error processing
  - _Requirements: 4.1, 4.2, 4.3, 4.4_

- [x] 10. Enhance Debugger class with new error formatting




  - Modify existing `error` method to use new ErrorFormatter
  - Add new overloaded methods for enhanced error reporting with file paths
  - Integrate new formatters 
  - Update `debugConsole` and `debugLog` methods to use new formatting
  - move the error reporting files to src/error/  and debugger.hh/.cpp to src/common/
  - Write integration tests to ensure existing error handling still works
  - _Requirements: 1.1, 1.2, 1.3, 1.4, 4.4_

- [ ] 11. Add configuration system for error message customization
  - Create configuration options for verbose vs. concise error formats
  - Add settings for educational vs. expert-level messaging
  - Implement color scheme and formatting preference options
  - Create method to load and apply configuration settings
  - Write unit tests for configuration system functionality
  - _Requirements: 5.1, 5.2, 5.3, 5.4_

- [x] 12. Update error reporting call sites throughout codebase









  - Always show the code where the error is encountered with the expected values.
  - Enhance error messages with more specific context and lexeme information
  - Add the correct expected value based on what is seen and show how he correct code may be
  - Refactor the code when we encounter SemanticError to be more deailed and show the line where we encounter the error
  - Write integration tests for updated error reporting / remove the old error reporting mechanism 
  - _Requirements: 1.1, 1.2, 1.3, 1.4, 3.1_

- [ ] 13. Create comprehensive test suite for error message quality
  - Write tests for all error code ranges and types
  - Create test cases for common syntax errors with expected output
  - Add tests for block context detection and "Caused by" messages
  - Implement regression tests for existing error scenarios
  - Write performance tests to ensure minimal overhead
  - _Requirements: 1.1, 1.2, 1.3, 1.4, 2.1, 2.2, 2.3, 2.4, 3.1, 3.2, 3.3, 3.4_

- [ ] 14. Add error message documentation and examples
  - Create documentation for all error codes and their meanings
  - Add examples of common error scenarios and their enhanced messages
  - Document configuration options and customization capabilities
  - Create migration guide for existing error handling code
  - Write developer guide for adding new error types and messages
  - _Requirements: 5.1, 5.2, 5.3, 5.4_