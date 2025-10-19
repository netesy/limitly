# CST Parser Fixes - Requirements Document

## Introduction

The CST (Concrete Syntax Tree) parser is currently failing with memory allocation errors (`std::bad_alloc`) when parsing test files, while the legacy parser works correctly but has some parsing issues. This specification addresses fixing the CST parser to be accurate, memory-efficient, and compatible with all existing test files.

## Requirements

### Requirement 1: Memory Management and Stability

**User Story:** As a developer, I want the CST parser to handle large files without crashing, so that I can parse any valid Limit language file reliably.

#### Acceptance Criteria

1. WHEN parsing any test file THEN the CST parser SHALL NOT throw `std::bad_alloc` or other memory-related exceptions
2. WHEN parsing files with complex nested structures THEN the parser SHALL manage memory efficiently using RAII principles
3. WHEN encountering parsing errors THEN the parser SHALL recover gracefully without memory leaks
4. WHEN parsing large files THEN memory usage SHALL grow linearly with file size, not exponentially
5. IF memory allocation fails THEN the parser SHALL report a clear error message and exit gracefully

### Requirement 2: Parsing Accuracy and Compatibility

**User Story:** As a developer, I want the CST parser to produce the same parsing results as the legacy parser, so that I can trust the CST parser for all language features.

#### Acceptance Criteria

1. WHEN parsing string interpolation with `&&` and `||` operators THEN the parser SHALL correctly handle these operators within interpolation expressions
2. WHEN parsing `elif` statements THEN the parser SHALL recognize `elif` as a keyword, not a function call
3. WHEN parsing object literal syntax like `Some { kind: "Some", value: 42 }` THEN the parser SHALL correctly parse the object structure
4. WHEN parsing all test files in the `tests/` directory THEN the CST parser SHALL produce equivalent results to the legacy parser
5. WHEN encountering syntax errors THEN the parser SHALL provide clear, actionable error messages

### Requirement 3: Trivia Preservation and CST Completeness

**User Story:** As a tool developer, I want the CST parser to preserve all source code information including whitespace and comments, so that I can build accurate code formatting and refactoring tools.

#### Acceptance Criteria

1. WHEN parsing source code THEN the CST SHALL preserve all whitespace tokens between meaningful tokens
2. WHEN parsing source code with comments THEN the CST SHALL preserve all comment tokens with their exact content
3. WHEN reconstructing source code from CST THEN the output SHALL be identical to the original input
4. WHEN parsing incomplete or erroneous code THEN the CST SHALL still preserve trivia information where possible
5. WHEN accessing trivia information THEN the API SHALL provide efficient access to leading and trailing trivia for each node

### Requirement 4: Error Recovery and Robustness

**User Story:** As a developer, I want the CST parser to continue parsing after encountering errors, so that I can get comprehensive error reporting and partial parsing results.

#### Acceptance Criteria

1. WHEN encountering a syntax error THEN the parser SHALL report the error and attempt to continue parsing
2. WHEN multiple syntax errors exist THEN the parser SHALL report all errors up to a reasonable limit (100 errors)
3. WHEN recovering from errors THEN the parser SHALL synchronize at statement boundaries or other logical points
4. WHEN creating partial nodes for incomplete constructs THEN the nodes SHALL be clearly marked as incomplete
5. WHEN error recovery fails THEN the parser SHALL provide context about what it was trying to parse

### Requirement 5: Performance and Efficiency

**User Story:** As a developer, I want the CST parser to be reasonably fast, so that it doesn't significantly slow down my development workflow.

#### Acceptance Criteria

1. WHEN parsing typical source files THEN the CST parser SHALL complete parsing within 2x the time of the legacy parser
2. WHEN parsing the same file multiple times THEN the parser SHALL show consistent performance
3. WHEN using memoization THEN frequently accessed parsing rules SHALL be cached appropriately
4. WHEN parsing in direct AST mode THEN performance SHALL be comparable to the legacy parser
5. WHEN memory usage exceeds reasonable limits THEN the parser SHALL provide warnings or fail gracefully

### Requirement 6: API Compatibility and Usability

**User Story:** As a developer, I want to easily switch between CST and legacy parsers, so that I can test and compare parsing results.

#### Acceptance Criteria

1. WHEN using the test_parser utility THEN both `-cst` and `-legacy` flags SHALL work correctly
2. WHEN comparing parser outputs THEN the CST parser SHALL provide equivalent AST structures to the legacy parser
3. WHEN accessing parsing results THEN the API SHALL provide clear methods to get CST nodes, AST nodes, or error information
4. WHEN switching parser modes THEN the interface SHALL be consistent and intuitive
5. WHEN debugging parsing issues THEN the parser SHALL provide detailed diagnostic information

### Requirement 7: Hierarchical CST Structure and Node Nesting

**User Story:** As a tool developer, I want the CST to represent the hierarchical structure of the source code accurately, so that I can build tools that understand the nested relationships between statements and expressions.

#### Acceptance Criteria

1. WHEN parsing block statements THEN child statements SHALL be nested under their parent block CST node, not added to the root level
2. WHEN parsing if statements with blocks THEN the statements inside the if block SHALL be children of the if statement CST node
3. WHEN parsing loop statements (for, while, iter) THEN the loop body statements SHALL be nested under the loop CST node
4. WHEN parsing function declarations THEN the function body statements SHALL be nested under the function CST node
5. WHEN parsing class declarations THEN method and field declarations SHALL be nested under the class CST node
6. WHEN parsing nested structures THEN the CST SHALL maintain proper parent-child relationships at all levels
7. WHEN traversing the CST THEN tools SHALL be able to navigate from parent to child nodes and vice versa

### Requirement 8: Enhanced Statement and Expression CST Nodes

**User Story:** As a developer, I want all statement and expression types to have proper CST node representation, so that the CST provides complete structural information about the source code.

#### Acceptance Criteria

1. WHEN parsing block statements THEN the parser SHALL create BLOCK_STATEMENT CST nodes using createNode<AST::BlockStatement>()
2. WHEN parsing loop statements (for, while, iter) THEN the parser SHALL create structured CST nodes with proper token capture
3. WHEN parsing function declarations THEN the parser SHALL create FUNCTION_DECLARATION CST nodes with parameter and body structure
4. WHEN parsing class declarations THEN the parser SHALL create CLASS_DECLARATION CST nodes with member structure
5. WHEN parsing complex expressions THEN the parser SHALL optionally create structured CST nodes for binary expressions, member access, and function calls
6. WHEN parsing expression statements THEN the parser SHALL create EXPRESSION_STATEMENT CST nodes that properly contain their expression tokens
7. WHEN parsing any statement type THEN all consumed tokens SHALL be captured in the appropriate CST node hierarchy

### Requirement 9: CST Node Parent-Child Relationship Management

**User Story:** As a tool developer, I want a clear API for managing parent-child relationships in CST nodes, so that I can build and manipulate hierarchical CST structures programmatically.

#### Acceptance Criteria

1. WHEN creating nested CST structures THEN the parser SHALL provide a mechanism to set the current parent CST node context
2. WHEN parsing statements within a block THEN new statement CST nodes SHALL be added as children of the current block CST node
3. WHEN entering a new scope (block, function, class) THEN the parser SHALL push the new CST node as the current parent context
4. WHEN exiting a scope THEN the parser SHALL pop the parent context and return to the previous parent
5. WHEN adding child nodes THEN the CST node API SHALL maintain bidirectional parent-child references
6. WHEN querying CST structure THEN tools SHALL be able to access parent nodes, child nodes, and sibling nodes efficiently
7. WHEN building CST incrementally THEN the parser SHALL ensure all nodes are properly connected in the hierarchy

### Requirement 10: Test Coverage and Validation

**User Story:** As a developer, I want comprehensive test coverage for the CST parser, so that I can be confident in its correctness across all language features.

#### Acceptance Criteria

1. WHEN running all tests in the `tests/` directory THEN the CST parser SHALL pass all tests that the legacy parser passes
2. WHEN testing specific language features THEN each feature SHALL have dedicated CST parser tests
3. WHEN comparing CST and legacy parser outputs THEN automated tests SHALL verify equivalence
4. WHEN testing error conditions THEN the CST parser SHALL handle errors as well as or better than the legacy parser
5. WHEN running performance benchmarks THEN the CST parser SHALL meet performance requirements consistently
6. WHEN testing hierarchical structures THEN the CST SHALL correctly represent nested relationships for all statement types
7. WHEN testing CST reconstruction THEN nested structures SHALL be properly preserved and reconstructed