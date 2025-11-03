# Requirements Document

## Introduction

This feature ensures that visibility enforcement for class members and module members is correctly implemented in the type checker during the semantic analysis stage, before bytecode generation. The system should use AST visibility information to enforce access control rules, treating each file as a separate module.

## Requirements

### Requirement 1

**User Story:** As a language developer, I want visibility enforcement to happen during semantic analysis, so that access violations are caught at compile-time before bytecode generation.

#### Acceptance Criteria

1. WHEN the type checker encounters a member access expression THEN it SHALL validate visibility rules before allowing the access
2. WHEN a visibility violation is detected THEN the type checker SHALL report a compile-time error with specific details about the violation
3. WHEN bytecode generation begins THEN all visibility violations SHALL have already been detected and reported
4. WHEN the type checker processes member access THEN it SHALL use AST visibility information rather than runtime checks
5. WHEN validating member access THEN the type checker SHALL clearly distinguish between class member access and module member access

### Requirement 2

**User Story:** As a language developer, I want proper module-level visibility enforcement, so that private and protected declarations are correctly scoped to their defining module.

#### Acceptance Criteria

1. WHEN accessing a private module member from a different file THEN the type checker SHALL report an access violation error
2. WHEN accessing a protected module member from a different file without inheritance THEN the type checker SHALL report an access violation error
3. WHEN accessing a public module member from any file THEN the type checker SHALL allow the access
4. WHEN accessing any member from within the same module THEN the type checker SHALL allow the access regardless of visibility level
5. WHEN determining module member visibility THEN the type checker SHALL use only module-level visibility rules and NOT class-level rules
6. WHEN a module member is accessed THEN the type checker SHALL validate access using the member's declaring module as the primary context

### Requirement 3

**User Story:** As a language developer, I want proper class member visibility enforcement, so that private, protected, and public class members are accessed according to their visibility rules.

#### Acceptance Criteria

1. WHEN accessing a private class member from outside the defining class THEN the type checker SHALL report an access violation error regardless of module context
2. WHEN accessing a protected class member from a subclass THEN the type checker SHALL allow the access even across module boundaries
3. WHEN accessing a protected class member from outside the class hierarchy THEN the type checker SHALL report an access violation error
4. WHEN accessing a public class member from anywhere THEN the type checker SHALL allow the access
5. WHEN accessing any class member from within the same class THEN the type checker SHALL allow the access
6. WHEN determining class member visibility THEN the type checker SHALL use class-level visibility rules independently from module-level rules
7. WHEN a class member is accessed THEN the type checker SHALL validate access using the member's declaring class as the primary context

### Requirement 4

**User Story:** As a language developer, I want inheritance-based access control, so that subclasses can access protected members from their parent classes even across module boundaries.

#### Acceptance Criteria

1. WHEN a subclass accesses a protected member of its parent class THEN the type checker SHALL allow the access even if they are in different modules
2. WHEN a non-subclass accesses a protected member THEN the type checker SHALL report an access violation error
3. WHEN determining inheritance relationships THEN the type checker SHALL use AST class declaration information
4. WHEN validating protected access THEN the type checker SHALL traverse the inheritance hierarchy to verify access rights

### Requirement 5

**User Story:** As a language developer, I want comprehensive error reporting for visibility violations, so that developers receive clear feedback about access control issues.

#### Acceptance Criteria

1. WHEN a visibility violation occurs THEN the error message SHALL include the member name, its visibility level, and the access context
2. WHEN reporting cross-module violations THEN the error message SHALL specify the source and target modules
3. WHEN reporting inheritance-related violations THEN the error message SHALL explain the class hierarchy requirements
4. WHEN multiple visibility violations exist THEN the type checker SHALL report all violations in a single pass
5. WHEN a visibility violation is detected THEN the error SHALL include the line number and column information

### Requirement 6

**User Story:** As a language developer, I want clear logical separation between class and module visibility enforcement, so that the two visibility systems work independently and correctly.

#### Acceptance Criteria

1. WHEN accessing a class member THEN the type checker SHALL use only class-based visibility rules and inheritance relationships
2. WHEN accessing a module member THEN the type checker SHALL use only module-based visibility rules and module boundaries
3. WHEN a class is defined in a module THEN the class members SHALL have their own visibility independent of the module's visibility rules
4. WHEN determining access context THEN the type checker SHALL clearly identify whether the access is class-based or module-based
5. WHEN validating member access THEN the type checker SHALL NOT mix class visibility rules with module visibility rules
6. WHEN parsing class declarations THEN the type checker SHALL NOT accept visibility modifiers on the class declaration itself (no `pub class` or `prot class`)
7. WHEN a class is declared THEN only the class members SHALL have visibility modifiers, not the class declaration

### Requirement 7

**User Story:** As a language developer, I want the type checker to use AST visibility information, so that visibility enforcement is based on the parsed source code structure.

#### Acceptance Criteria

1. WHEN processing class declarations THEN the type checker SHALL extract and store visibility information from AST nodes
2. WHEN processing module-level declarations THEN the type checker SHALL determine visibility from AST declaration nodes
3. WHEN validating member access THEN the type checker SHALL query stored AST visibility information
4. WHEN no explicit visibility is specified THEN the type checker SHALL apply default visibility rules (private for class members, private for module members)
5. WHEN storing visibility information THEN the type checker SHALL associate it with the declaring module path
6. WHEN storing class member visibility THEN the type checker SHALL associate it with the declaring class independently from module context