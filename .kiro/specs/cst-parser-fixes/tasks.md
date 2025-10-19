# Implementation Plan

- [x] 1. Enhance Token Structure for Trivia Storage






  - Add leadingTrivia and trailingTrivia vectors to existing Token class
  - Add default empty constructors to maintain backward compatibility with legacy parser
  - Implement getLeadingTrivia() and getTrailingTrivia() accessor methods
  - Add reconstructSource() method to rebuild original text with trivia
  - _Requirements: 3.1, 3.2, 3.3_

- [x] 2. Modify Scanner to Collect and Attach Trivia Automatically






  - Update Scanner::scanTokens() to collect trivia and attach to tokens when in CST mode
  - When scanning meaningful tokens, collect preceding whitespace/comments as leadingTrivia
  - Collect trailing trivia after each token until next meaningful token is found
  - Add scanMode parameter: LEGACY (no trivia) vs CST (with trivia) for backward compatibility
  - _Requirements: 3.1, 3.2, 6.4_

- [x] 3. Create New CST Parser by Copying Legacy Parser










  - Copy parser.cpp to cst_parser.cpp and parser.hh to cst_parser.hh
  - Keep existing parser.cpp/hh completely unchanged for safety
  - Rename Parser class to CSTParser in new files to avoid conflicts
  - Add boolean cstMode flag to CSTParser constructor (default true for CST mode)
  - _Requirements: 1.1, 2.4, 6.2, 6.3_

- [x] 4. Update New CST Parser Node Creation Methods






  - Modify all parsing methods in cst_parser.cpp to create CST::Node instead of AST::Node
  - Add fallback mode: if cstMode=false, create AST::Node for compatibility testing
  - Attach token trivia automatically from consumed tokens when creating CST nodes
  - Map all AST node types to appropriate CST NodeKind enum values
  - _Requirements: 2.4, 3.5, 6.3_

- [x] 5. Fix Specific Parsing Issues in New CST Parser





  - Add ELIF token recognition and parsing (currently parsed as function call)
  - Fix object literal syntax parsing for constructs like Some { kind: "Some", value: 42 }
  - Test fixes work correctly in new CST parser before applying to legacy parser
  - _Requirements: 2.1, 2.2, 2.3_
-

- [x] 6. Implement CST Node Trivia Integration


  - Add leadingTrivia and trailingTrivia vectors to CST Node class ✅ DONE
  - Implement attachTriviaFromToken() method to extract trivia from consumed tokens (enhance existing basic implementation)
  - Add reconstructSource() method to CST Node class to rebuild original source with all trivia
  - Test trivia preservation with whitespace and comment-heavy files
  - _Requirements: 3.1, 3.2, 3.3_

- [x] 7. Update Test Parser to Use New CST Parser






  - Modify test_parser.cpp to instantiate CSTParser from cst_parser.cpp for -cst flag
  - Keep existing legacy Parser usage for -legacy flag (no changes)
  - Ensure -cst flag works without std::bad_alloc by using proven parsing logic
  - Compare output format between -cst and -legacy flags for consistency
  - _Requirements: 1.1, 6.1, 6.2_

- [x] 8. Test All Files in Tests Directory with Both Parsers





  - Run legacy Parser (AST mode) and new CSTParser (CST mode) on all test files
  - Compare parsing results to ensure equivalent parsing logic between both
  - Test with comprehensive_language_test.lm to verify no std::bad_alloc in new CST parser
  - Verify memory usage is reasonable and no crashes occur in either parser
  - _Requirements: 7.1, 7.2, 1.2, 1.4_

- [x] 9. Validate Trivia Preservation and Source Reconstruction













  - Test that CST mode preserves all whitespace and comments from original source
  - Verify reconstructSource() method produces identical output to original input
  - Test with files containing complex trivia patterns (nested comments, mixed whitespace)
  - Ensure trivia is correctly associated with appropriate tokens and nodes
  - _Requirements: 3.1, 3.2, 3.3, 7.3_

- [x] 10. Performance and Memory Optimization






  - Profile memory usage of new CSTParser vs legacy Parser
  - Optimize trivia storage in tokens to minimize memory overhead
  - Add benchmarks comparing parsing speed between new CST parser and legacy parser
  - Ensure new CST parser performance is within 2x of legacy parser
  - _Requirements: 5.1, 5.2, 5.4_

- [x] 11. Achieve Parity and Replace Old CST Parser







  - Verify new CSTParser handles all test cases as well as legacy Parser
  - Ensure no regressions in parsing accuracy or performance
  - Once parity achieved, remove old problematic parser.cpp/hh files
  - Rename cst_parser.cpp/hh to parser.cpp/hh
  - _Requirements: 1.1, 6.3, 7.1, 7.2_

- [x] 12. Final Testing and Documentation




  - Run comprehensive test suite with both legacy Parser and new CSTParser
  - Document the new approach: clean CST parser based on proven legacy parser
  - Add usage examples for both AST and CST generation
  - Create migration guide from old complex CST parser to new simple approach
  - _Requirements: 10.1, 10.4, 10.5, 6.5_

- [x] 13. Implement CST Node Parent-Child Context Management






  - Add CST node context stack to Parser class to track current parent CST node
  - Implement pushCSTContext() and popCSTContext() methods for scope management
  - Modify statement parsing methods to add child nodes to current parent context instead of root
  - Add getCurrentCSTParent() method to get the current parent CST node
  - _Requirements: 9.1, 9.2, 9.3, 9.4_

- [x] 14. Update Block Statement Parsing for Hierarchical CST





  - Modify block() method to use createNode<AST::BlockStatement>() instead of std::make_shared
  - Create BLOCK_STATEMENT CST node and set it as parent context when parsing block contents
  - Ensure all statements within the block are added as children of the BLOCK_STATEMENT CST node
  - Add proper token capture for opening and closing braces in block CST nodes
  - _Requirements: 7.1, 7.2, 8.1, 9.2_

- [x] 15. Enhance If Statement CST with Nested Block Structure






  - Update ifStatement() method to properly handle nested block statements as children
  - Ensure the print statement inside if blocks appears as child of IF_STATEMENT, not at root level
  - Add proper CST structure for elif and else branches with their nested statements
  - Capture all tokens including block braces in the IF_STATEMENT CST node hierarchy
  - _Requirements: 7.2, 7.6, 8.2, 9.2_

- [x] 16. Implement Enhanced Loop Statement CST Nodes






  - Update forStatement(), whileStatement(), matchStatement() and iterStatement() methods to use createNode pattern
  - Create structured CST nodes (FOR_STATEMENT, WHILE_STATEMENT, ITER_STATEMENT) with proper token capture
  - Implement nested block structure for loop bodies with statements as children of loop CST nodes
  - Add proper token capture for loop keywords, conditions, and iteration expressions
  - _Requirements: 7.3, 7.6, 8.2, 8.6_


- [x] 17. Implement Function and Class Declaration CST Hierarchy





  - Update function() and classDeclaration() methods to create hierarchical CST structures
  - Ensure function body statements are nested under FUNCTION_DECLARATION CST nodes
  - Ensure class member declarations are nested under CLASS_DECLARATION CST nodes
  - Add proper token capture for function signatures, class names, and member declarations
  - _Requirements: 7.4, 7.5, 8.3, 8.4_

- [x] 18. Add Expression Statement CST Node Support






  - Update expressionStatement() method to use createNode<AST::ExprStatement>()
  - create structured cst nodes for (CONTRACT, MATCH, CONCURRENT, PARALLEL) with proper token capture
  - Ensure the expression inside the statement appears as child of EXPRESSION_STATEMENT, not at root
  - Create EXPRESSION_STATEMENT CST nodes that properly contain their expression tokens
  - Implement token range capture for complex expressions within expression statements
  - Ensure expression tokens are nested under EXPRESSION_STATEMENT nodes, not added to root
  - _Requirements: 8.6, 8.7, 9.2_

- [x] 19. Implement Optional Complex Expression CST Nodes












  - Update expression() method to create hierarchical CST nodes for complex expressions ✅ DONE
  - Invalid syntax recovery should be handled by the CST parser ✅ DONE
  - Add createNode support for binary expressions, member access, and function calls ✅ DONE
  - Create structured CST nodes for BINARY_EXPR, MEMBER_EXPR, and CALL_EXPR when beneficial ✅ DONE
  - Implement hierarchical token capture for complex nested expressions ✅ DONE
  - Add configuration option to enable/disable detailed expression CST nodes ✅ DONE
  - _Requirements: 8.5, 8.7, 7.6_

- [x] 20. Test and Validate Hierarchical CST Structure





  - Create comprehensive test cases for nested CST structures (if blocks, loops, modules, functions, classes)
  - Verify that statements inside blocks appear as children of their parent CST nodes, not at root level
  - Test CST traversal APIs for parent-child navigation and sibling access
  - Validate CST reconstruction maintains proper hierarchical structure
  - Delete all the test files not in the tests folder
  - Remove "" from string for the AST but let it remain for the CST
  - _Requirements: 10.6, 10.7, 7.6, 9.6_