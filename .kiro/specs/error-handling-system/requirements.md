# Requirements Document

## Introduction

The error handling system for the Limit programming language provides a concise, type-safe approach to handling errors through union types and explicit propagation. This system avoids verbose try/catch patterns in favor of a minimal syntax using the `?` operator for both marking fallible functions and propagating errors. The design ensures errors cannot be silently ignored while maintaining zero-cost abstractions comparable to Rust/Zig performance. All error handling is explicit and visible in function signatures and call sites.

## Requirements

### Requirement 1

**User Story:** As a developer, I want to declare functions that can return errors using union types, so that I can explicitly indicate which operations might fail with minimal syntax.

#### Acceptance Criteria

1. WHEN a function is declared with return type `Type?` THEN the system SHALL treat this as a union of `Type | Error`
2. WHEN a function is declared with return type `Type?ErrorType` THEN the system SHALL allow only the specified error type to be returned
3. WHEN a function is declared with return type `Type?ErrorType1, ErrorType2` THEN the system SHALL allow any of the specified error types to be returned
4. WHEN a function is declared with return type `Type | ErrorType1 | ErrorType2` THEN the system SHALL allow explicit union syntax as an alternative
5. WHEN a function attempts to return an error type not in its declared error list THEN the system SHALL produce a compile-time error

### Requirement 2

**User Story:** As a developer, I want to create and return error values using concise syntax, so that I can provide meaningful error information without verbose constructions.

#### Acceptance Criteria

1. WHEN I use `return err(ErrorType)` syntax THEN the system SHALL create and return an error value of the specified type
2. WHEN I use `return err(ErrorType(args))` syntax THEN the system SHALL create an error value with the provided arguments
3. WHEN I use `return ok(value)` syntax THEN the system SHALL create and return a success value
4. WHEN I return a value directly from a fallible function THEN the system SHALL automatically wrap it as a success value
5. WHEN error construction arguments are invalid THEN the system SHALL produce a compile-time error

### Requirement 3

**User Story:** As a developer, I want to call fallible functions with automatic error propagation, so that I can write clean code without explicit error checking at every call site.

#### Acceptance Criteria

1. WHEN I call a fallible function with `expr?` syntax THEN the system SHALL automatically propagate errors to the calling context if one occurs
2. WHEN I call a fallible function with `expr?` syntax and no error occurs THEN the system SHALL return the unwrapped success value
3. WHEN I use `?` in a function that doesn't return a compatible error type THEN the system SHALL produce a compile-time error
4. WHEN a fallible expression succeeds THEN the system SHALL extract the value from the union type automatically
5. WHEN error propagation would cause type incompatibility THEN the system SHALL produce a clear compile-time error message

### Requirement 4

**User Story:** As a developer, I want to pattern match on union results to handle different outcomes ergonomically, so that I can provide specific handling logic for success and error cases.

#### Acceptance Criteria

1. WHEN I use `match expr` on a fallible result THEN the system SHALL support `val identifier` patterns for success cases
2. WHEN I use `match expr` on a fallible result THEN the system SHALL support `err identifier` patterns for error cases
3. WHEN I use `match expr` on a typed error union THEN the system SHALL support `ErrorType` patterns for specific error types
4. WHEN I use `match expr` on a typed error union THEN the system SHALL support `ErrorType(params)` patterns to extract error parameters
5. WHEN a match expression doesn't cover all union variants THEN the system SHALL produce a compile-time error requiring exhaustive matching

### Requirement 5

**User Story:** As a developer, I want the type system to enforce explicit error handling, so that errors cannot be silently ignored and all failure paths are visible.

#### Acceptance Criteria

1. WHEN a function calls a fallible function without using `?` or `match` THEN the system SHALL produce a compile-time error
2. WHEN a function uses `?` to propagate errors THEN the system SHALL require the calling function to have a compatible return type
3. WHEN a function handles all errors through pattern matching THEN the system SHALL not require error types in the function signature
4. WHEN error union types are incompatible between caller and callee THEN the system SHALL produce a compile-time error with suggested fixes
5. WHEN a fallible result is assigned to a variable without handling THEN the system SHALL produce a compile-time error

### Requirement 6

**User Story:** As a developer, I want built-in error types for common failure scenarios, so that I have consistent error handling across the language ecosystem.

#### Acceptance Criteria

1. WHEN the system encounters division by zero THEN it SHALL return a `DivisionByZero` error value
2. WHEN the system encounters array bounds violations THEN it SHALL return an `IndexOutOfBounds` error value
3. WHEN the system encounters null reference access THEN it SHALL return a `NullReference` error value
4. WHEN the system encounters type conversion failures THEN it SHALL return a `TypeConversion` error value
5. WHEN the system encounters I/O failures THEN it SHALL return appropriate `IOError` subtypes as error values

### Requirement 7

**User Story:** As a developer, I want zero-cost error handling with efficient runtime representation, so that error handling doesn't impact performance of success paths.

#### Acceptance Criteria

1. WHEN a function returns a success value THEN the system SHALL use the same memory layout as a non-fallible function
2. WHEN error propagation occurs THEN the system SHALL avoid heap allocation and use stack-based error passing
3. WHEN pattern matching on results THEN the system SHALL compile to efficient branch instructions without boxing
4. WHEN errors are not handled THEN the system SHALL provide clear compile-time errors with suggested fixes
5. WHEN the VM executes error handling code THEN it SHALL distinguish between normal values and error values without runtime type checking overhead