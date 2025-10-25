# Type System Refinement Requirements

## Introduction

This specification defines the refinement of the Limit programming language's type system to achieve better simplicity, safety, and performance. The goal is to consolidate existing type features into a more coherent system that eliminates redundancy while adding missing capabilities for domain precision and compile-time safety.

## Glossary

- **Type_System**: The Limit language's compile-time type checking and inference system
- **Discriminated_Union**: A single union type that replaces separate sum and union types
- **Flow_Sensitive_Narrowing**: Type checking that tracks type changes through control flow
- **Error_Propagation**: Automatic forwarding of error values through function call chains
- **Refinement_Types**: Types with value-based constraints (e.g., `int where x > 0`)
- **Exhaustive_Pattern_Matching**: Pattern matching that ensures all cases are handled at compile time
- **Structural_Typing**: Type compatibility based on structure rather than inheritance
- **Tag_Binding**: Extracting discriminant values in pattern matching

## Requirements

### Requirement 1: Unified Discriminated Union System

**User Story:** As a language developer, I want a single discriminated union type system, so that I can eliminate complexity from having separate union and sum types.

#### Acceptance Criteria

1. THE Type_System SHALL replace existing union and sum types with a single discriminated union implementation
2. WHEN a union type is declared, THE Type_System SHALL automatically generate discriminant tags for each variant
3. THE Type_System SHALL ensure all union variants are properly tagged at runtime
4. THE Type_System SHALL provide compile-time validation for union type operations
5. WHERE existing union/sum type code exists, THE Type_System SHALL maintain backward compatibility during migration

### Requirement 2: Flow-Sensitive Type Narrowing

**User Story:** As a developer, I want the type checker to track type changes through control flow, so that I need fewer runtime type checks.

#### Acceptance Criteria

1. WHEN a type guard or pattern match occurs, THE Type_System SHALL narrow the type in subsequent code paths
2. THE Type_System SHALL track type information through if/else branches, loops, and function calls
3. IF a variable is checked for a specific type, THEN THE Type_System SHALL remember that type in the positive branch
4. THE Type_System SHALL eliminate redundant runtime type checks when compile-time information is sufficient
5. WHERE control flow merges, THE Type_System SHALL compute the union of possible types

### Requirement 3: Enhanced Error Handling with Propagation

**User Story:** As a developer, I want ergonomic error handling with automatic propagation, so that error handling is both safe and convenient.

#### Acceptance Criteria

1. THE Type_System SHALL support typed error values with automatic propagation using the `?` operator
2. WHEN an error-returning function is called with `?`, THE Type_System SHALL automatically propagate errors to the caller
3. THE Type_System SHALL enforce static checking that all error types are handled or propagated
4. THE Type_System SHALL provide compile-time validation of error handling completeness
5. WHERE error propagation occurs, THE Type_System SHALL maintain type safety for both success and error paths

### Requirement 4: Value-Based Refinement Types

**User Story:** As a developer, I want to define types with value constraints, so that I can express domain-specific requirements precisely.

#### Acceptance Criteria

1. THE Type_System SHALL support refinement types with value-based constraints using `where` clauses
2. WHEN a refinement type is declared, THE Type_System SHALL validate constraints at compile time where possible
3. THE Type_System SHALL generate runtime checks for refinement constraints that cannot be verified statically
4. THE Type_System SHALL provide clear error messages when refinement constraints are violated
5. WHERE refinement types are used in function signatures, THE Type_System SHALL enforce constraint satisfaction

### Requirement 5: Exhaustive Pattern Matching with Tag Binding

**User Story:** As a developer, I want pattern matching that ensures all cases are handled, so that I have compile-time safety guarantees.

#### Acceptance Criteria

1. THE Type_System SHALL enforce exhaustiveness checking for all pattern match expressions
2. WHEN pattern matching on discriminated unions, THE Type_System SHALL require all variants to be handled
3. THE Type_System SHALL support tag binding to extract discriminant values in patterns
4. IF a pattern match is non-exhaustive, THEN THE Type_System SHALL report a compile-time error
5. WHERE new variants are added to unions, THE Type_System SHALL identify all pattern matches that need updating

### Requirement 6: Structural Typing System

**User Story:** As a developer, I want type compatibility based on structure rather than inheritance, so that the system remains compatible with bare-metal programming.

#### Acceptance Criteria

1. THE Type_System SHALL maintain structural typing for type aliases where aliases resolve to their underlying types
2. WHEN two types have compatible structure, THE Type_System SHALL allow assignment and parameter passing
3. THE Type_System SHALL support interface-like contracts through structural requirements
4. THE Type_System SHALL eliminate the need for explicit inheritance hierarchies
5. WHERE type aliases are used, THE Type_System SHALL treat them as transparent references to their underlying types

### Requirement 7: Concrete Type System Without Generics

**User Story:** As a language designer, I want to avoid generics in favor of unions and refinement types, so that the type system remains concrete and predictable.

#### Acceptance Criteria

1. THE Type_System SHALL use discriminated unions instead of generic type parameters where possible
2. THE Type_System SHALL use refinement types for constraining type behavior instead of generic bounds
3. THE Type_System SHALL maintain concrete types throughout compilation for better performance
4. THE Type_System SHALL provide type safety equivalent to generics through union and refinement combinations
5. WHERE generic-like behavior is needed, THE Type_System SHALL guide developers toward union/refinement solutions

### Requirement 8: Nil Type and Collection Initialization

**User Story:** As a developer, I want clear semantics for nil types and empty collections, so that I understand when values represent absence versus empty containers.

#### Acceptance Criteria

1. THE Type_System SHALL define `nil` as the unit type representing "no value"
2. WHEN a function has no explicit return type, THE Type_System SHALL infer the return type as `nil`
3. THE Type_System SHALL require explicit type annotations for empty collection declarations
4. THE Type_System SHALL provide clear documentation distinguishing nil from empty collections
5. WHERE nil values are used, THE Type_System SHALL limit operations to prevent meaningless computations