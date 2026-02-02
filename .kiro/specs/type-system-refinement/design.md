# Type System Refinement Design

## Overview

This design document outlines the refinement of the Limit programming language's type system to achieve better simplicity, safety, and performance. The refined system consolidates existing type features into a more coherent architecture while adding missing capabilities for domain precision and compile-time safety.

## Architecture

### Core Type System Principles

The refined type system is built on these foundational principles:

1. **Structural Transparency**: Type aliases are transparent references to underlying types
2. **Union-First Design**: Use discriminated unions instead of generics for type flexibility
3. **Flow-Sensitive Analysis**: Track type changes through control flow for better inference
4. **Explicit Safety**: Require explicit types where ambiguity could cause errors
5. **Concrete Types**: Maintain concrete types throughout compilation for predictable performance

### Type Hierarchy

```
Type System
├── Primitive Types (int, uint, float, bool, str, nil)
├── Discriminated Unions (T | U with automatic tagging)
├── Refinement Types (T where condition)
├── Collection Types ([T], {K: V}, (T, U, V))
├── Function Types ((T, U) -> V)
├── Error Union Types (T?ErrorType)
└── Option Types (T | nil)
```

## Components and Interfaces

### 1. Unified Discriminated Union System

**Current State**: Separate union and sum types exist with different semantics
**Target State**: Single discriminated union type with automatic tagging

```cpp
// New unified union type structure
struct DiscriminatedUnion {
    std::vector<TypePtr> variants;
    std::map<size_t, std::string> variantTags;  // Auto-generated tags
    bool isExhaustive = true;  // For pattern matching validation
};
```

**Implementation Strategy**:
- Replace existing `UnionType` and `SumType` with `DiscriminatedUnion`
- Auto-generate discriminant tags for runtime type identification
- Maintain backward compatibility during migration phase

### 2. Flow-Sensitive Type Narrowing

**Architecture**: Extend type checker with control flow analysis

```cpp
class FlowSensitiveTypeChecker {
    struct TypeState {
        std::map<std::string, TypePtr> variableTypes;
        std::set<std::string> narrowedVariables;
    };
    
    std::stack<TypeState> controlFlowStack;
    
public:
    void enterBranch(const TypeGuard& guard);
    void exitBranch();
    TypePtr getNarrowedType(const std::string& variable);
    void mergeControlFlows(const std::vector<TypeState>& branches);
};
```

**Key Features**:
- Track type guards (`if x is int`) and narrow types in positive branches
- Merge type information at control flow join points
- Eliminate redundant runtime checks when compile-time information is sufficient

### 3. Enhanced Error Handling System

**Current State**: Basic error union types with manual propagation
**Target State**: Automatic error propagation with static validation

```cpp
struct ErrorPropagationSystem {
    // Automatic error propagation using ? operator
    bool validateErrorHandling(const FunctionDecl& func);
    
    // Static analysis of error paths
    std::set<std::string> inferPossibleErrors(const Expression& expr);
    
    // Compile-time completeness checking
    bool isErrorHandlingComplete(const MatchExpression& match);
};
```

### 4. Refinement Type System

**New Component**: Value-based type constraints validated at compile-time

```cpp
struct RefinementType {
    TypePtr baseType;
    std::string constraintExpression;  // e.g., "x > 0"
    bool isStaticallyVerifiable;
    
    // Compile-time constraint validation
    bool validateStatically() const;
};
```

**Examples**:
```limit
type PositiveInt = int where x > 0;
type NonEmptyString = str where len(x) > 0;
type ValidEmail = str where matches(x, email_regex);
```

## JIT Compilation Strategy

### Compile-Time Type Specialization

The type system enables aggressive compile-time specialization for JIT compilation:

#### 1. Monomorphic Specialization
- **Concept**: Generate specialized code for each concrete type combination
- **Benefit**: Eliminates runtime type checks and enables inline caching
- **Example**:
  ```limit
  fn process(value: int | str) {
      match value {
          case int(x) -> print("Int: {x}");
          case str(s) -> print("Str: {s}");
      }
  }
  
  // JIT generates two specialized versions:
  // process_int(int) - direct int handling
  // process_str(str) - direct str handling
  ```

#### 2. Union Type Specialization
- **Concept**: Generate optimized code paths for each union variant
- **Benefit**: Eliminates discriminant checks in hot paths
- **Implementation**:
  - Discriminated unions generate tag-based dispatch
  - JIT inlines tag checks for monomorphic call sites
  - Polymorphic call sites use efficient jump tables

#### 3. Refinement Type Specialization
- **Concept**: Generate specialized code for refined types
- **Benefit**: Eliminates unnecessary constraint checks when statically verifiable
- **Example**:
  ```limit
  type PositiveInt = int where x > 0;
  
  fn double(x: PositiveInt) -> PositiveInt {
      return x * 2;  // No constraint check needed - JIT knows x > 0
  }
  ```

#### 4. Flow-Sensitive Specialization
- **Concept**: Generate specialized code based on type narrowing
- **Benefit**: Eliminates unnecessary type checks after narrowing
- **Example**:
  ```limit
  var value: int | str = ...;
  if value is int {
      // JIT specializes this block to int-only operations
      print(value + 1);  // No type check needed
  }
  ```

### Code Generation for JIT

#### LIR Generation with Type Information
- **Type Tags**: Include type information in LIR for optimization
- **Specialization Hints**: Mark code paths for specialization
- **Constraint Information**: Embed refinement type constraints in LIR

#### Optimization Passes
1. **Type Specialization Pass**
   - Identify monomorphic call sites
   - Generate specialized code versions
   - Create dispatch tables for polymorphic sites

2. **Constraint Elimination Pass**
   - Remove unnecessary constraint checks when statically verifiable
   - Eliminate checks after type narrowing
   - Optimize discriminant checks

3. **Inline Caching Pass**
   - Cache type information at call sites
   - Inline frequently used type paths
   - Generate fallback paths for uncommon types

#### Native Code Generation
- **Discriminated Unions**: Generate efficient tag-based dispatch
- **Pattern Matching**: Generate optimized jump tables
- **Type Checks**: Inline type checks where possible
- **Constraint Validation**: Generate minimal validation code

### Register VM (Development Only)

The register VM is used for development and testing:
- **Interpretation**: Direct interpretation of LIR instructions
- **Debugging**: Full debugging capabilities with breakpoints
- **Testing**: Comprehensive test execution
- **Not for Production**: Register VM is never used in production execution

### Performance Characteristics

#### Compile-Time Overhead
- Type specialization analysis: O(n) where n = number of call sites
- Code generation: O(m) where m = number of specialized versions
- Optimization passes: O(k) where k = code size

#### Runtime Performance
- **Monomorphic Calls**: Direct function calls (no dispatch overhead)
- **Polymorphic Calls**: Efficient jump tables (minimal overhead)
- **Type Checks**: Inlined where possible (single instruction)
- **Constraint Checks**: Eliminated when statically verifiable

#### Memory Usage
- **Code Size**: Increases with specialization (typically 1.5-2x)
- **Type Information**: Minimal overhead in compiled code
- **Dispatch Tables**: Compact jump tables for polymorphic sites

## Data Models

### Type Inference Engine

```cpp
class TypeInferenceEngine {
public:
    // Variable inference (locked after first assignment)
    TypePtr inferVariableType(const VariableDecl& decl);
    
    // Collection inference with homogeneity rules
    TypePtr inferCollectionType(const ListLiteral& list);
    TypePtr inferDictType(const DictLiteral& dict);
    
    // Union type inference for heterogeneous collections
    TypePtr inferUnionType(const std::vector<TypePtr>& elementTypes);
    
    // Empty collection handling
    bool requiresExplicitType(const CollectionLiteral& literal);
};
```

### Type Alias Semantics

**Structural Transparency**: Type aliases resolve completely to underlying types

```cpp
class TypeAliasResolver {
    // Resolve alias chains to concrete types
    TypePtr resolveToConcreteType(const std::string& aliasName);
    
    // Check structural compatibility
    bool areStructurallyCompatible(TypePtr a, TypePtr b);
    
    // Prevent circular dependencies
    bool hasCircularDependency(const std::string& alias, TypePtr type);
};
```

**Examples**:
```limit
type UserId = int;
type UserName = str;

// These are structurally equivalent to their base types
var id: UserId = 42;        // Same as: var id: int = 42;
var name: UserName = "Bob"; // Same as: var name: str = "Bob";

// Structural compatibility allows this:
fn processId(id: int) { ... }
processId(userId);  // Valid - UserId is structurally int
```

## Error Handling

### Comprehensive Type Inference Rules

1. **Variables**: Type locked after first inference/assignment
2. **Collections**: Must be homogeneous unless explicitly typed as `[any]`
3. **Dictionaries**: Keys and values inferred separately, unions created for heterogeneous content
4. **Empty Collections**: Require explicit type annotations
5. **Functions**: Return type inferred from return statements, nil if no explicit returns

### Pattern Matching Constraints

**Match as Statement Only**: Pattern matching is statement-only to maintain clear control flow

```limit
// Valid: match as statement
match value {
    case int(x) -> print("Integer: {x}");
    case str(s) -> print("String: {s}");
}

// Invalid: match as expression
var result = match value {  // Compile error
    case int(x) -> x * 2;
    case str(s) -> len(s);
};

// Alternative: use if-else expressions for simple cases
var result = if value is int then value * 2 else 0;
```

### Common Type Errors and Solutions

```limit
// Error: Empty collection without type
var list = [];  // Compile error: Cannot infer type of empty list
var list: [int] = [];  // Solution: Explicit type annotation

// Error: Heterogeneous collection without [any]
var mixed = [1, "hello"];  // Compile error: Incompatible types
var mixed: [any] = [1, "hello"];  // Solution: Explicit any type

// Error: Match used as expression
var x = match y { ... };  // Compile error: Match is statement-only
// Solution: Use if-else or separate match statement

// Error: Function without return type returning values
fn compute() {  // Compile error: Inconsistent return behavior
    if condition {
        return 42;
    }
    // Implicit nil return
}
// Solution: Explicit return type or consistent returns
fn compute(): int? { ... }  // Or make return optional
```

## Testing Strategy

### Type System Validation Tests

1. **Union Type Migration**: Verify existing union/sum code works with new discriminated unions
2. **Flow-Sensitive Narrowing**: Test type narrowing in various control flow scenarios
3. **Error Propagation**: Validate automatic error handling and static analysis
4. **Refinement Types**: Test constraint validation and error reporting
5. **Type Inference**: Comprehensive tests for all inference scenarios

### Performance Benchmarks

1. **Compile-Time Performance**: Measure type checking speed with flow-sensitive analysis
2. **Runtime Performance**: Verify discriminated unions don't add overhead
3. **Memory Usage**: Test type system memory consumption with complex type hierarchies

## Language Design Resolutions

### Resolved Design Questions

1. **Empty Collections**: YES, require explicit types to prevent ambiguity
2. **If-Else**: Expression form supported for simple cases, statement form for complex logic
3. **Type Aliases**: Structural (transparent) - resolve completely to underlying types
4. **Match Expressions**: Statement-only to maintain clear control flow semantics
5. **Union Type Complexity**: Limit to 8 variants for performance, suggest refinement types for complex cases

### Type System Documentation Structure

```
docs/type-system/
├── principles.md           # Core type system principles
├── inference.md           # Comprehensive inference rules
├── unions-and-options.md  # Discriminated unions and Option types
├── refinement-types.md    # Value-based type constraints
├── error-handling.md      # Error propagation and validation
├── flow-analysis.md       # Flow-sensitive type narrowing
├── common-errors.md       # Typical mistakes and solutions
└── migration-guide.md     # Upgrading from current system
```

## Implementation Phases

### Phase 1: Foundation (Weeks 1-2)
- Implement discriminated union system
- Create flow-sensitive type checker infrastructure
- Add refinement type parsing and validation

### Phase 2: Integration (Weeks 3-4)
- Migrate existing union/sum types to discriminated unions
- Implement error propagation system
- Add comprehensive type inference rules

### Phase 3: Validation (Weeks 5-6)
- Complete test suite for all new features
- Performance optimization and benchmarking
- Documentation and migration guide creation

### Phase 4: Polish (Week 7)
- Error message improvements
- Edge case handling
- Final integration testing