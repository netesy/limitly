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
  - _Requirements: 7.1, 7.4, 7.5, 6.5_