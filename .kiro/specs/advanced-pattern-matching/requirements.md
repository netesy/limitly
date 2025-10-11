# Requirements Document

## Introduction

This feature extends the existing basic match statement functionality in the Limit programming language to support advanced pattern matching capabilities including destructuring patterns, Result type patterns with val()/err(), proper variable binding, and improved string interpolation within match contexts. These enhancements will make pattern matching more expressive and powerful for complex data manipulation and error handling scenarios.

## Requirements

### Requirement 1: Destructuring Patterns

**User Story:** As a developer, I want to destructure lists and tuples in match patterns, so that I can extract individual elements and bind them to variables for use in match case bodies.

#### Acceptance Criteria

1. WHEN a match statement contains a list destructuring pattern `[a, b, c]` THEN the system SHALL bind the list elements to variables a, b, c respectively
2. WHEN a match statement contains a tuple destructuring pattern `(x, y)` THEN the system SHALL bind the tuple elements to variables x, y respectively
3. WHEN a destructuring pattern has fewer variables than elements THEN the system SHALL bind available elements and ignore extras
4. WHEN a destructuring pattern has more variables than elements THEN the system SHALL report a pattern match failure
5. WHEN destructured variables are used in the match case body THEN the system SHALL provide access to the bound values

### Requirement 2: Result Type Pattern Matching

**User Story:** As a developer, I want to match against Result types using val() and err() patterns, so that I can handle success and error cases elegantly in pattern matching.

#### Acceptance Criteria

1. WHEN a function returns a Result type `int?str` THEN the system SHALL support matching with `val(x)` and `err(msg)` patterns
2. WHEN a match pattern uses `val(x)` THEN the system SHALL bind the success value to variable x
3. WHEN a match pattern uses `err(msg)` THEN the system SHALL bind the error value to variable msg
4. WHEN Result type constructors `val()` and `err()` are used THEN the system SHALL create appropriate Result type values
5. WHEN function return type syntax `-> Type?ErrorType` is used THEN the system SHALL parse and validate Result type signatures

### Requirement 3: Proper Variable Binding and Scoping

**User Story:** As a developer, I want variables bound in match patterns to be properly scoped and accessible without semantic errors, so that I can use pattern-bound variables reliably in match case bodies.

#### Acceptance Criteria

1. WHEN a variable is bound in a match pattern THEN the system SHALL make it available in the corresponding case body without semantic errors
2. WHEN a variable is bound in a match pattern THEN the system SHALL scope it only to that specific case body
3. WHEN guard patterns use bound variables THEN the system SHALL validate variable access without undefined variable errors
4. WHEN multiple patterns bind the same variable name THEN the system SHALL maintain separate scopes for each case
5. WHEN pattern-bound variables are used THEN the system SHALL provide proper type information and validation

### Requirement 4: String Interpolation in Match Context

**User Story:** As a developer, I want string interpolation to work correctly within match case bodies, so that I can display pattern-bound variables and other expressions in output strings.

#### Acceptance Criteria

1. WHEN string interpolation `{variable}` is used in match case bodies THEN the system SHALL properly substitute variable values
2. WHEN pattern-bound variables are used in string interpolation THEN the system SHALL access their bound values correctly
3. WHEN complex expressions are used in string interpolation within match cases THEN the system SHALL evaluate them properly
4. WHEN string interpolation fails in match context THEN the system SHALL provide clear error messages
5. WHEN multiple interpolated expressions are used in match case strings THEN the system SHALL handle all substitutions correctly

### Requirement 5: Enhanced Guard Patterns

**User Story:** As a developer, I want guard patterns with `where` clauses to work without semantic errors, so that I can add conditional logic to pattern matching.

#### Acceptance Criteria

1. WHEN guard patterns use `where` clauses THEN the system SHALL evaluate the condition without undefined variable errors
2. WHEN guard conditions reference pattern-bound variables THEN the system SHALL provide proper variable access
3. WHEN guard conditions are false THEN the system SHALL continue to the next pattern
4. WHEN guard conditions are true THEN the system SHALL execute the corresponding case body
5. WHEN multiple guard patterns are used THEN the system SHALL evaluate them in order until one matches