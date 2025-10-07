# Implementation Plan

- [x] 1. Extend Scanner for CST Support








  - Add new TokenType values (WHITESPACE, NEWLINE, COMMENT_LINE, COMMENT_BLOCK, ERROR, MISSING) to existing enum in scanner.hh
  - Implement scanAllTokens() method in Scanner class that preserves whitespace and comments
  - Add CSTConfig struct for configuring trivia preservation behavior
  - Implement scanWhitespace(), scanComment(), and createErrorToken() methods in scanner.cpp
  - Modify existing scanToken() to optionally preserve trivia based on configuration
  - Ensure all existing Scanner functionality remains unchanged for backward compatibility
  - _Requirements: 1.1, 1.2, 1.3, 1.4, 1.5_

- [x] 2. Create CST Node Structure and Headers





  - Create new file src/frontend/cst.hh with CST namespace and NodeKind enum
  - Define NodeKind enum covering all language constructs (statements, expressions, declarations)
  - Implement base CST::Node class with children vector, tokens vector, and utility methods
  - Add source position tracking (startPos, endPos) and validation flags to Node class
  - Create factory functions (createNode, createErrorNode, createMissingNode) in cst.hh
  - Implement utility methods: getText(), getAllTokens(), findChild(), findChildren()
  - _Requirements: 2.1, 2.2, 2.3, 2.4, 2.5_

- [x] 3. Implement Error Recovery Node Types





  - Create ErrorNode class extending CST::Node for invalid syntax with error messages
  - Create MissingNode class extending CST::Node for missing required elements
  - Create IncompleteNode class extending CST::Node for partial constructs
  - Add skippedTokens vector to ErrorNode for tokens consumed during error recovery
  - Add expectedKind and description fields to MissingNode and IncompleteNode
  - Implement specialized factory methods for each error node type
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_

- [x] 4. Create CSTParser Class Foundation




  - Create new file src/frontend/cst_parser.hh with CSTParser class declaration
  - Implement CSTParser constructor taking vector of tokens from enhanced Scanner
  - Add RecoveryConfig struct for configuring synchronization points and error limits
  - Create ParseError struct with enhanced context, suggestions, and source spans
  - Implement core token consumption methods: consume(), consumeOrError(), match()
  - Add trivia handling methods: consumeTrivia(), collectTrivia(), attachTrivia()
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_

- [x] 5. Implement Core CST Parsing Methods







  - Create src/frontend/cst_parser.cpp with main parsing entry point parseCST()
  - Implement parseProgram() method creating program-level CST nodes with all tokens
  - Create parseStatement() method handling all statement types with error recovery
  - Implement parseExpression() method with operator precedence and error tolerance
  - Add parseBlock() method preserving all tokens including braces and internal whitespace
  - Ensure all parsing methods return CST::Node pointers instead of AST nodes
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_

- [x] 6. Add Statement Parsing with Error Recovery










  - Implement parseIfStatement() with recovery for missing conditions, braces, and else clauses
  - Create parseForStatement(), ParseMatchStatement(), ParseIterStatement() and parseWhileStatement() with loop-specific error handling
  - Add parseVarDeclaration() with recovery for missing types, initializers, and semicolons
  - Implement parseFunctionDeclaration() with parameter and body error recovery
  - Add parseClassDeclaration() with inheritance and member declaration error handling
  - Implement statement-level synchronization using semicolons, braces, and keywords
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_

- [x] 7. Add Expression Parsing with Error Recovery













  - Implement parseBinaryExpr() with operator precedence and missing operand recovery
  - Create parseUnaryExpr() with recovery for missing operands after unary operators
  - Add parseCallExpr() with recovery for missing arguments, parentheses, and commas
  - Implement parseMemberExpr() with recovery for missing member names after dots
  - Add parseLiteralExpr() and parseVariableExpr() with error node creation for invalid tokens
  - Implement parseGroupingExpr() with recovery for missing closing parentheses
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_

- [x] 8. Implement Error Recovery and Synchronization




  - ✅ Add reportError() method with enhanced context, source spans, and fix suggestions
  - ✅ Implement synchronize() method that skips tokens until synchronization points
  - ✅ Create createErrorRecoveryNode() for wrapping sequences of skipped tokens
  - ✅ Add sync token detection for semicolons, braces, keywords (fn, class, var, if)
  - ✅ Implement partial node construction for incomplete syntax with missing element tracking
  - ✅ Add error limit checking to prevent infinite error cascades
  - ✅ Integrate with existing Debugger::error() system for consistent error reporting
  - ✅ Add block context tracking for better error messages about unclosed constructs
  - ✅ Use ErrorFormatter system for enhanced error messages with hints and suggestions
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_

- [x] 9. Create ASTBuilder for CST to AST Transformation




  - Create new file src/frontend/ast_builder.hh with ASTBuilder class declaration
  - Implement ASTBuilder class that transforms CST nodes to existing AST node types
  - Add BuildConfig struct for controlling error-tolerant transformation behavior
  - Create transformation methods: buildStatement(), buildExpression(), buildDeclaration()
  - Implement error-tolerant node creation: createErrorExpr(), createMissingExpr()
  - Add SourceMapping struct to preserve CST→AST relationships for error reporting
  - _Requirements: 4.1, 4.2, 4.3, 4.4, 4.5_

- [x] 10. Add CST Utility Functions and Debugging





  - Create src/frontend/cst_utils.hh with utility functions for CST manipulation
  - Create src/frontend/cst_printer.hh with with indented tree visualization or json
  - Implement printCST() function for debugging using cst_printer
  - Create serializeCST() function for JSON output supporting testing and analysis
  - Add traversal utilities: forEachChild(), getTokens(), getText() for CST navigation
  - Implement reconstructSource() for round-trip source reconstruction from CST
  - Create validateCST() utilities for checking completeness and structural correctness
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_

- [x] 11. Implement Unified Grammar System with Dual Output Modes





  - Create UnifiedParser class with shared grammar table that can produce both CST and AST
  - Implement GrammarRule struct with production rules that support dual output generation
  - Add ParserMode enum (DIRECT_AST, CST_THEN_AST, CST_ONLY) for different use cases
  - Create shared parsing combinators that can build either CST nodes or AST nodes based on mode
  - Implement grammar table with rule definitions that work for both CST preservation and AST optimization
  - Add ParseContext struct to track current parsing mode and output target during rule execution
  - Create rule execution engine that interprets grammar table and produces appropriate output type
  - Ensure zero code duplication between CST and AST parsing paths through shared rule definitions
  - Add performance optimization to skip trivia collection when in DIRECT_AST mode for compilation
  - Implement template-based output generation: `parseRule<OutputType>(rule, context)` for type safety
  - Create grammar DSL or builder pattern for defining rules: `rule("varDecl").sequence("var", "identifier", ":", "type")`
  - Add rule caching and memoization for frequently used grammar productions to improve performance
  - Implement context-sensitive parsing that enables CST mode for IDE features and AST mode for compilation
  
 
  - _Requirements: 6.1, 6.2, 6.3, 6.4, 6.5_

- [ ] 12. Create Comprehensive Test Suite








  - Create tests/cst/ directory structure with scanner/, parser/, ast_builder/, integration/ subdirectories
  - Add scanner tests for whitespace preservation, comment preservation, and error token generation
  - Using the cst_parser run the existing code in the tests folder and check them for errors run them individually
  - Create CST parser tests for valid syntax parsing, invalid syntax recovery, and error node creation
  - Implement AST builder tests for transformation accuracy and error-tolerant conversion
  - Add round-trip tests verifying exact source reconstruction from CST
  - Create performance benchmarks comparing CST parser speed with existing parser
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_

- [ ] 13. Add Advanced CST Features for Tooling
  - Implement incremental parsing support for efficiently re-parsing modified source sections
  - Add token classification system for syntax highlighting with context information
  - Create code folding region detection for blocks, comments, imports, and functions
  - Implement CST-based formatter foundation enabling lossless source reconstruction
  - Add language server protocol support hooks for IDE integration and completion
  - Create CST query system for advanced code analysis and refactoring tools
  - _Requirements: 7.1, 7.2, 7.3, 7.4, 7.5_

- [ ] 14. Performance Optimization and Validation
  - Profile CST node allocation patterns and implement memory pool optimization
  - Add comprehensive performance benchmarks comparing CST vs legacy parser
  - Implement CST node pooling for frequently created node types (expressions, statements)
  - Optimize trivia attachment algorithms and token stream processing efficiency
  - Validate that performance regression remains within acceptable bounds (<20% slowdown)
  - Add memory usage profiling to ensure CST doesn't cause excessive memory consumption
  - _Requirements: 6.1, 6.2, 6.3, 6.4, 6.5_

- [ ] 15. Documentation and Examples
  - Create comprehensive documentation in docs/cst/ covering architecture and usage
  - Add practical examples showing CST-based tooling (formatting, error recovery, highlighting)
  - Document complete migration guide for projects adopting CST parsing
  - Create detailed API documentation for CSTParser, ASTBuilder, and utility functions
  - Add troubleshooting guide covering common CST integration issues and solutions
  - Create developer guide explaining CST node structure and traversal patterns
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_