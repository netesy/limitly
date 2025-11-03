# Implementation Plan

- [x] 1. Enhance TypeChecker class with visibility tracking structures





  - Add visibility information storage structures (MemberVisibilityInfo, ClassVisibilityInfo, ModuleVisibilityInfo) to type_checker.hh
  - Add module and class registry maps to TypeChecker class
  - Add current context tracking variables (currentModulePath, currentClassName)
  - _Requirements: 6.1, 6.5_

- [x] 2. Implement visibility information extraction from AST








  - [x] 2.1 Create extractModuleVisibility method in TypeChecker



    - Traverse Program AST node to extract top-level declarations
    - Store function and variable visibility information with module context
    - Handle default visibility rules (private for module members)
    - _Requirements: 6.1, 6.4_

  - [x] 2.2 Create extractClassVisibility method in TypeChecker

    - Extract class member visibility from ClassDeclaration AST nodes (NOT class-level visibility)
    - Store field and method visibility information in classRegistry
    - Handle inheritance relationships and store superclass information
    - Ensure class declarations themselves have no visibility modifiers
    - _Requirements: 6.1, 6.2, 6.6, 6.7_

  - [x] 2.3 Create extractFunctionVisibility and extractVariableVisibility methods

    - Extract visibility from FunctionDeclaration and VarDeclaration AST nodes
    - Store visibility information with declaring module context
    - Handle static and abstract modifiers
    - _Requirements: 6.1, 6.4_

- [-] 3. Implement core access validation logic





  - [x] 3.1 Create validateClassMemberAccess method for MemberExpr validation









    - Check class member access against stored visibility rules using only class-based context
    - Validate access context (same class, subclass) without considering module boundaries
    - Return validation result with error details
    - Ensure no mixing of class and module visibility rules
    - _Requirements: 1.1, 1.5, 3.1, 3.2, 3.3, 3.4, 3.6, 3.7, 6.1, 6.5_

  - [ ] 3.2 Create validateModuleFunctionCall method for CallExpr validation
    - Validate module-level function call access based on function visibility
    - Check module-level function access rules using only module-based context
    - Distinguish between class method calls and module function calls
    - _Requirements: 2.1, 2.2, 2.3, 2.5, 2.6, 6.2, 6.5_

  - [ ] 3.3 Create validateModuleVariableAccess method for VariableExpr validation
    - Validate module-level variable access based on variable visibility
    - Check module-level variable access rules using only module-based context
    - Distinguish between class field access and module variable access
    - _Requirements: 2.1, 2.2, 2.3, 2.5, 2.6, 6.2, 6.5_

- [ ] 4. Implement module-level access control
  - [ ] 4.1 Create canAccessModuleMember method (separate from class access)
    - Implement module-level access rules (private, protected, public) independently from class rules
    - Compare current module path with declaring module path
    - Handle same-module access permissions without considering class context
    - _Requirements: 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 6.2, 6.5_

  - [ ] 4.2 Enhance checkExpression to validate member access with proper separation
    - Integrate validateClassMemberAccess into MemberExpr type checking for class members
    - Integrate validateModuleVariableAccess into VariableExpr type checking for module variables
    - Add visibility violation error reporting with clear context (class vs module)
    - Ensure validation occurs before type compatibility checking
    - _Requirements: 1.1, 1.2, 1.5, 6.4, 6.5_

  - [ ] 4.3 Enhance checkStatement to validate function and variable access with proper separation
    - Integrate validateModuleFunctionCall into CallExpr processing for module functions
    - Integrate validateModuleVariableAccess into VariableExpr processing for module variables
    - Add comprehensive error reporting for all access violations with clear context
    - Ensure class method calls use class-based validation, not module-based
    - _Requirements: 1.1, 1.2, 1.5, 6.4, 6.5_

- [ ] 5. Implement inheritance-based access control
  - [ ] 5.1 Create isSubclassOf method for inheritance checking
    - Traverse class inheritance hierarchy using AST information
    - Check direct and indirect inheritance relationships
    - Handle multiple inheritance scenarios
    - _Requirements: 4.1, 4.3_

  - [ ] 5.2 Create canAccessThroughInheritance method
    - Validate protected member access through inheritance
    - Check inheritance relationships across module boundaries
    - Handle complex inheritance hierarchies
    - _Requirements: 4.1, 4.2, 4.3_

  - [ ] 5.3 Create getInheritanceChain method
    - Build complete inheritance chain for a given class
    - Use AST ClassDeclaration superClassName information
    - Cache inheritance chains for performance
    - _Requirements: 4.3, 4.4_

- [ ] 6. Implement comprehensive error reporting
  - [ ] 6.1 Create reportVisibilityViolation method
    - Generate detailed error messages for visibility violations
    - Include member name, visibility level, and access context
    - Add line and column information from AST nodes
    - _Requirements: 5.1, 5.5_

  - [ ] 6.2 Create VisibilityErrorReporter class
    - Implement formatPrivateMemberError for private access violations
    - Implement formatProtectedMemberError for protected access violations
    - Implement formatCrossModuleError for cross-module violations
    - Implement formatInheritanceError for inheritance-related violations
    - _Requirements: 5.1, 5.2, 5.3, 5.4_

  - [ ] 6.3 Enhance existing error reporting integration
    - Integrate visibility error reporting with existing TypeChecker error system
    - Ensure all visibility violations are collected and reported in single pass
    - Add context-specific error suggestions
    - _Requirements: 5.4, 5.5_

- [ ] 7. Integrate visibility checking into type checker workflow
  - [ ] 7.1 Modify checkProgram to extract visibility information first
    - Add visibility extraction as first pass before type checking
    - Build complete module and class registries
    - Set up current module context
    - _Requirements: 1.3, 6.1_

  - [ ] 7.2 Update expression and statement checking methods
    - Integrate visibility validation into all relevant expression types
    - Ensure visibility checks occur before bytecode generation
    - Maintain existing type checking functionality
    - _Requirements: 1.1, 1.3_

  - [ ] 7.3 Add visibility context management
    - Track current class context during class method checking
    - Update current module context appropriately
    - Handle nested scope visibility correctly
    - _Requirements: 6.5_

- [ ] 8. Create comprehensive test cases
  - [ ] 8.1 Create unit tests for visibility extraction
    - Test extractModuleVisibility with various declaration types
    - Test extractClassVisibility with different member types
    - Test visibility information storage and retrieval
    - _Requirements: 6.1, 6.2_

  - [ ] 8.2 Create unit tests for access validation
    - Test validateMemberAccess with all visibility levels
    - Test module-level access validation
    - Test inheritance-based access validation
    - _Requirements: 1.1, 2.1, 3.1, 4.1_

  - [ ] 8.3 Create integration tests for complete workflow
    - Test end-to-end visibility enforcement
    - Test error reporting accuracy and completeness
    - Test performance with complex inheritance hierarchies
    - _Requirements: 1.2, 5.4_

- [ ] 9. Update existing test files and create new test cases
  - [ ] 9.1 Fix class visibility syntax in test files
    - Remove any `pub class` or `prot class` declarations from test files
    - Ensure classes are declared without visibility modifiers
    - Update test cases to use proper member visibility syntax only
    - Verify test files follow correct language design (classes have no visibility, only members do)
    - _Requirements: 6.6, 6.7_

  - [ ] 9.2 Update test_type_check_visibility.lm test file
    - Ensure all test cases properly exercise visibility enforcement
    - Add additional edge cases for same-module access
    - Verify expected behavior matches implementation
    - Test separation between class and module visibility
    - _Requirements: 2.4, 3.5, 6.1, 6.2, 6.5_

  - [ ] 9.3 Update test_cross_module_visibility.lm test file
    - Add comprehensive cross-module access test cases
    - Test inheritance-based protected access across modules
    - Verify proper error reporting for access violations
    - Test clear separation between class and module visibility across modules
    - _Requirements: 2.1, 2.2, 4.1, 4.2, 6.1, 6.2_

  - [ ] 9.4 Create additional test files for edge cases
    - Create tests for complex inheritance hierarchies with proper class member visibility
    - Create tests for multiple module interactions with clear separation
    - Create tests for error message accuracy distinguishing class vs module context
    - Create tests verifying classes cannot have visibility modifiers
    - _Requirements: 4.4, 5.1, 5.2, 5.3, 6.6, 6.7_