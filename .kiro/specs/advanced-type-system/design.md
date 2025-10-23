# Design Document

## Overview

The advanced type system for Limit extends the existing type infrastructure to support comprehensive type aliases, union types, generic containers, and advanced type constructs like Option and Result types. The design builds upon the existing TypeSystem class in `backend/types.hh` and the TypeAnnotation structure in `frontend/ast.hh`.

## Current Implementation Status

### ✅ COMPLETED COMPONENTS
- **Type Alias System**: Full implementation with circular dependency detection
- **Error Union Types**: Complete integration with error handling system (`Type?ErrorType`)
- **Function Types**: Comprehensive function type system with parameter/return type checking
- **Tuple Types**: Full tuple support including creation, indexing, destructuring
- **Type Checker**: Comprehensive compile-time type validation with detailed error reporting
- **Type Inference**: Context-aware type inference for variables and expressions

### 🔄 PARTIALLY IMPLEMENTED COMPONENTS
- **Union Types**: Basic parsing and type system infrastructure, needs runtime value support
- **Container Types**: Basic type structures exist, needs parsing and validation
- **Option Types**: Framework exists, needs integration with union type system
- **Structured Types**: Basic support, needs enhancement for complex field validation

### 📋 PLANNED COMPONENTS
- **Pattern Matching**: Runtime union type discrimination and exhaustive case checking
- **Generic Types**: Type parameters and generic type instantiation
- **Runtime Type Safety**: Type introspection and safe variant access

## Cross-Spec Integration

### Harmonization with Error Handling System

This advanced type system provides the foundational union type infrastructure that the error handling system builds upon:

#### Shared Union Type Foundation
- **Union Types**: Both specs use the same underlying union type implementation
- **Result Types**: The advanced type system's `Result<T, E>` maps directly to the error handling system's `T?E` syntax
- **Option Types**: The advanced type system's `Option<T>` provides null safety that complements error handling

#### Syntactic Compatibility
- **Error Handling Syntax**: The `?` operator from the error handling system operates on union types defined in this spec
- **Constructor Functions**: The `err()` and `ok()` functions from the error handling system create union values using this spec's infrastructure
  - `ok(value)` creates a success variant in any union type (not just Result types)
  - `err(ErrorType)` creates an error variant in union types
- **Pattern Matching**: Both specs use the same pattern matching infrastructure for union type discrimination
- **Type Safety**: Both specs enforce explicit handling of all union variants

#### Implementation Coordination
- **Shared Type System**: Both specs extend the same `TypeSystem` class in `backend/types.hh`
- **Shared AST Nodes**: Both specs use the same `TypeAnnotation` and union type AST structures
- **Shared Runtime**: Both specs use the same union value representation and pattern matching runtime

This harmonization ensures that developers have a consistent experience when working with both advanced types and error handling, without duplicate implementations or conflicting behaviors.

## Architecture

### Core Components

1. **Type Declaration Parser** - Extends the frontend parser to handle `type` declarations
2. **Type Alias Registry** - Enhanced type alias system in TypeSystem class  
3. **Union Type Support** - Full union type implementation with pattern matching
4. **Typed Container Types** - Enhanced list and dictionary types with specific element/key-value types
5. **Built-in Type Constructors** - Option and Result type implementations
6. **Type Checker** - Enhanced type checking for complex type relationships
7. **Runtime Type Safety** - Pattern matching and type discrimination at runtime
8. **Type Inference Engine** - Intelligent type inference with ambiguity detection

### Design Rationales

#### Type Alias Distinction (Requirement 1.1)
**Decision**: Treat type aliases as distinct types rather than simple substitutions.
**Rationale**: This provides stronger type safety by preventing accidental mixing of semantically different values that happen to have the same underlying type (e.g., `userId` vs `productId` both being `int`).

#### Union Type Safety (Requirement 2.3)
**Decision**: Require pattern matching or explicit type checking for union type access.
**Rationale**: This prevents runtime errors from accessing the wrong variant and ensures all possible cases are handled, following the principle of making illegal states unrepresentable. This aligns with the error handling system's requirement for explicit error handling.

#### Option/Result Harmonization (Requirement 3.3, 3.4)
**Decision**: Implement Option and Result as union types compatible with the error handling system.
**Rationale**: This creates consistency between the type system and error handling - Result<T, E> maps directly to the error handling system's T?E syntax, and both use the same underlying union type infrastructure. This eliminates duplicate implementations and ensures consistent behavior.

#### Typed Container Safety (Requirement 4.4)
**Decision**: Enforce type constraints at both compile-time and runtime for container operations.
**Rationale**: This maintains type safety for homogeneous containers, preventing type confusion and ensuring all elements/key-value pairs conform to the declared types.

#### Conservative Type Inference (Requirement 7.4)
**Decision**: Require explicit annotations when type inference is ambiguous.
**Rationale**: This prevents subtle bugs from incorrect type assumptions while still providing convenience for clear cases.

#### Cross-Spec Type Compatibility
**Decision**: Ensure Option and Result types are fully compatible with the error handling system's union types and syntax.
**Rationale**: This prevents having two different error handling mechanisms in the language. The advanced type system provides the foundational union types, while the error handling system provides the syntactic sugar (`?` operator, `err()`/`ok()` functions) that operates on these same union types.

### Integration Points

- **Frontend Parser** (`frontend/parser.cpp`) - Parse type declarations and annotations
- **AST Nodes** (`frontend/ast.hh`) - TypeDeclaration and enhanced TypeAnnotation
- **Type System** (`backend/types.hh`) - Core type management and checking
- **Value System** (`backend/value.hh`) - Runtime value representation
- **Backend Compiler** (`backend/backend.cpp`) - Code generation for type operations

## Components and Interfaces

### 1. Type Declaration Syntax

```limit
// === Primitive type aliases ===
type date = i64;
type numbers = u64;
type amount = f64;
type isTrue = bool;
type string = str;

// === Basic descriptive aliases ===
type Id = uint;
type Name = str;
type Age = uint;


// Structured types
type Some = { kind: "Some", value: any }; // 
type None = { kind: "None" };
type Success = { kind: "Success", value: any };
type Error = { kind: "Error", error: any };


// === Union Types with Structured Variants ===

// Option: a value that might be present or not
type Option = Some | None;

// Result: represents a success or an error (compatible with error handling system)
type Result = Success | Error;

// Note: The error handling system provides syntactic sugar that works with these union types:
// - Function return type `Type?` creates a union of `Type | Error`
// - Function return type `Type?ErrorType` creates a union of `Type | ErrorType`
// - The `ok(value)` function creates success variants in any union type
// - The `err(ErrorType)` function creates error variants in union types
// - The `?` operator propagates errors from these union types
// === Typed Containers ===

// List: a sequence of elements of a specific type
type ListOfInt = [int];
type ListOfString = [string];
type DictOfIntToFloat = { int: float };
type DictOfStringToInt = { string: int };

// Complex structured types
type ParsedResult = { data: string };
type StreamEvent = { raw: string, timestamp: date };
```

### 2. Parser Extensions

#### New AST Nodes
```cpp
// Enhanced TypeDeclaration in ast.hh
struct TypeDeclaration : public Statement {
    std::string name;
    std::shared_ptr<TypeAnnotation> type;
    bool isAlias = true;  // true for aliases, false for new types
};

// Enhanced TypeAnnotation for union types
struct TypeAnnotation {
    // ... existing fields ...
    bool isUnion = false;
    std::vector<std::shared_ptr<TypeAnnotation>> unionTypes;
    
    // Structured type support
    bool isStructural = false;
    std::vector<StructuralTypeField> structuralFields;
    
    // Typed container support
    std::shared_ptr<TypeAnnotation> keyType = nullptr;
    std::shared_ptr<TypeAnnotation> valueType = nullptr;
    std::shared_ptr<TypeAnnotation> elementType = nullptr;
};
```

#### Parser Methods
```cpp
class Parser {
    // New parsing methods
    std::shared_ptr<AST::TypeDeclaration> parseTypeDeclaration();
    std::shared_ptr<AST::TypeAnnotation> parseTypeAnnotation();
    std::shared_ptr<AST::TypeAnnotation> parseUnionType();
    std::shared_ptr<AST::TypeAnnotation> parseStructuralType();
    std::shared_ptr<AST::TypeAnnotation> parseContainerType();
};
```

### 3. Type System Enhancements

#### Enhanced TypeSystem Class
```cpp
class TypeSystem {
private:
    std::map<std::string, TypePtr> typeAliases;
    std::map<std::string, TypePtr> userDefinedTypes;
    
public:
    // Type alias management (Requirement 1)
    void registerTypeAlias(const std::string& name, TypePtr type);
    TypePtr resolveTypeAlias(const std::string& name);
    bool isDistinctType(TypePtr type);  // For treating aliases as distinct types
    
    // Union type support (Requirement 2)
    TypePtr createUnionType(const std::vector<TypePtr>& types);
    bool isUnionType(TypePtr type);
    std::vector<TypePtr> getUnionVariants(TypePtr type);
    bool requiresPatternMatching(TypePtr type);  // Safety requirement
    
    // Typed container support (Requirement 4)
    TypePtr createTypedListType(TypePtr elementType);
    TypePtr createTypedDictType(TypePtr keyType, TypePtr valueType);
    bool validateContainerAccess(TypePtr containerType, TypePtr accessType);
    
    // Built-in type constructors (Requirement 3) - Compatible with error handling system
    TypePtr createOptionType(TypePtr valueType);
    TypePtr createResultType(TypePtr successType, TypePtr errorType);
    bool requiresExplicitHandling(TypePtr type);  // For Option/Result safety
    
    // Error handling system compatibility
    TypePtr createFallibleType(TypePtr successType, const std::vector<std::string>& errorTypes);
    bool isFallibleType(TypePtr type);  // Check if type is compatible with ? operator
    
    // Enhanced type checking (Requirement 6)
    bool isAssignableFrom(TypePtr source, TypePtr target);
    TypePtr getCommonSupertype(const std::vector<TypePtr>& types);
    std::string generateTypeError(TypePtr expected, TypePtr actual);
    bool validateTypeConsistency(const std::vector<TypePtr>& types);
    
    // Type inference (Requirement 7)
    TypePtr inferType(ValuePtr value);
    TypePtr inferFromContext(const std::vector<TypePtr>& contextTypes);
    bool isInferenceAmbiguous(const std::vector<TypePtr>& candidates);
    
    // Runtime type safety (Requirement 8)
    bool providesTypeIntrospection(TypePtr type);
    TypePtr getRuntimeTypeInfo(ValuePtr value);
};
```

### 4. Built-in Type Implementations

#### Option Type (Compatible with Error Handling System)
```cpp
// Option<T> implemented as union type: T | None
// This aligns with the error handling system's union approach
struct OptionType {
    TypePtr valueType;
    bool isSome;
    ValuePtr value;  // Only valid when isSome is true
};

// Runtime constructors that create union values
ValuePtr createSome(TypePtr valueType, ValuePtr value);
ValuePtr createNone(TypePtr valueType);
```

#### Result Type (Harmonized with Error Handling System)
```cpp
// Result<T, E> implemented as union type: T | E
// This directly aligns with the error handling system's T?E syntax
// The error handling system's Type?ErrorType maps to Result<Type, ErrorType>
struct ResultType {
    TypePtr successType;
    TypePtr errorType;
    bool isSuccess;
    ValuePtr value;  // Success value or error value
};

// Runtime constructors compatible with err()/ok() syntax from error handling
ValuePtr createSuccess(TypePtr successType, ValuePtr value);  // Used internally by ok()
ValuePtr createError(TypePtr errorType, ValuePtr error);      // Used internally by err()
```

### 5. Pattern Matching Integration

#### Type Discrimination and Safety
```cpp
class TypeMatcher {
public:
    // Basic pattern matching (Requirement 2.3, 8.2)
    bool matchesType(ValuePtr value, TypePtr pattern);
    std::vector<ValuePtr> extractValues(ValuePtr value, TypePtr pattern);
    
    // Union type matching with safety (Requirement 2.3, 8.1)
    bool matchesUnionVariant(ValuePtr value, TypePtr unionType, size_t variantIndex);
    bool isExhaustiveMatch(TypePtr unionType, const std::vector<TypePtr>& patterns);
    
    // Safe field access (Requirement 8.3)
    bool canAccessField(ValuePtr value, const std::string& fieldName);
    ValuePtr safeFieldAccess(ValuePtr value, const std::string& fieldName);
    
    // Option/Result matching (Requirement 3.4, 8.1)
    bool isSome(ValuePtr optionValue);
    bool isNone(ValuePtr optionValue);
    bool isSuccess(ValuePtr resultValue);
    bool isError(ValuePtr resultValue);
    
    // Runtime introspection (Requirement 8.4)
    std::string getTypeName(ValuePtr value);
    std::vector<std::string> getFieldNames(ValuePtr value);
    TypePtr getFieldType(ValuePtr value, const std::string& fieldName);
};
```

### 6. Type Inference Engine

#### Inference Strategy (Requirement 7)
```cpp
class TypeInferenceEngine {
private:
    TypeSystem* typeSystem;
    std::map<std::string, TypePtr> inferredTypes;
    
public:
    // Variable type inference (Requirement 7.1)
    TypePtr inferFromInitializer(ValuePtr initValue);
    TypePtr inferFromUsage(const std::string& varName, const std::vector<UsageContext>& contexts);
    
    // Type alias inference (Requirement 7.2)
    TypePtr inferAliasedType(const std::string& aliasName, ValuePtr value);
    bool isAliasCompatible(TypePtr aliasType, TypePtr valueType);
    
    // Container type inference (Requirement 7.3)
    TypePtr inferContainerElementType(const std::vector<ValuePtr>& elements);
    TypePtr inferDictionaryTypes(const std::vector<std::pair<ValuePtr, ValuePtr>>& pairs);
    
    // Ambiguity detection (Requirement 7.4)
    bool isAmbiguous(const std::vector<TypePtr>& candidates);
    std::string generateAmbiguityError(const std::vector<TypePtr>& candidates);
    TypePtr requireExplicitAnnotation(const std::string& context);
    
    // Context-based inference
    TypePtr inferFromFunctionCall(const std::string& funcName, const std::vector<TypePtr>& argTypes);
    TypePtr inferFromAssignment(TypePtr lhsType, ValuePtr rhsValue);
};
```

#### Design Rationale for Type Inference
The type inference engine is designed to balance convenience with safety:
- **Conservative approach**: When inference is ambiguous, require explicit annotations rather than guessing
- **Context-aware**: Use surrounding code context to improve inference accuracy
- **Alias-aware**: Properly handle type aliases in inference to maintain type distinctions
- **Container-smart**: Infer typed container types from their contents and usage patterns

## Data Models

### Type Representation

```cpp
enum class TypeTag {
    // ... existing types ...
    TypeAlias,      // For type aliases
    Union,          // For union types
    Option,         // For Option<T>
    Result,         // For Result<T, E>
    Container,      // For typed container types
};

struct Type {
    TypeTag tag;
    std::string name;  // For named types and aliases
    
    // Union type data
    std::vector<TypePtr> unionVariants;
    
    // Container type data
    TypePtr elementType;  // For lists
    TypePtr keyType;      // For dictionaries
    TypePtr valueType;    // For dictionaries
    
    // Alias data
    TypePtr aliasTarget;  // What this alias points to
    bool isDistinct = false;  // Whether this creates a distinct type
};
```

### Value Representation

```cpp
struct Value {
    // ... existing fields ...
    
    // Union type support
    size_t activeUnionVariant = 0;  // Which variant is active
    
    // Option type support
    bool isOptionSome = false;
    
    // Result type support
    bool isResultSuccess = false;
};
```

## Error Handling

### Compile-Time Errors

1. **Type Alias Errors** (Requirement 1.4, 6.1, 6.2)
   - Circular type alias definitions with clear error messages
   - Undefined type references with suggestions for similar types
   - Invalid type alias syntax with correction hints
   - Type compatibility violations between aliases and base types

2. **Union Type Errors** (Requirement 2.3, 6.1)
   - Empty union types with requirement for at least one variant
   - Duplicate variants in unions with deduplication suggestions
   - Invalid union member types with supported type recommendations
   - Missing pattern matching cases with exhaustiveness checking

3. **Container Type Errors** (Requirement 4.4, 6.3)
   - Invalid container element types with supported type recommendations
   - Container type safety violations with element/key-value type mismatches
   - Dictionary key type incompatibilities with expected key types
   - List element type violations with homogeneous type requirements

4. **Structured Type Errors** (Requirement 5.1, 5.2, 5.3)
   - Missing required fields with field name suggestions
   - Invalid field types with expected type information
   - Field existence checking failures with available field lists
   - Nested structure validation errors with path information

5. **Type Inference Errors** (Requirement 7.4)
   - Ambiguous type inference with explicit annotation requirements
   - Insufficient context for inference with additional context suggestions
   - Conflicting type constraints with resolution recommendations

### Runtime Errors

1. **Type Discrimination Errors** (Requirement 8.1, 8.3)
   - Accessing wrong union variant with safe discrimination requirements
   - Unwrapping None option values with explicit handling enforcement
   - Accessing error in success results with proper Result handling
   - Field access on incorrect variant with variant validation

2. **Type Safety Violations** (Requirement 3.4, 8.3)
   - Accessing fields that don't exist in current variant
   - Bypassing required pattern matching for union types
   - Incomplete handling of Option/Result variants
   - Runtime type assertion failures with introspection support

3. **Type Conversion Errors** (Requirement 1.3, 4.4)
   - Invalid type casts between incompatible types
   - Incompatible type assignments with alias distinctions
   - Container element type violations in operations
   - Container element type safety violations

## Testing Strategy

### Unit Tests

1. **Type Declaration Tests** (Requirements 1.1-1.4)
   - Parse various type declaration syntaxes for all primitive types
   - Validate type alias resolution and distinction from base types
   - Test circular dependency detection with clear error messages
   - Verify compile-time error reporting for invalid type assignments

2. **Union Type Tests** (Requirements 2.1-2.4)
   - Create and manipulate union types with structured variants
   - Test type compatibility checking for complex hierarchies
   - Validate pattern matching behavior and exhaustiveness checking
   - Test nested union types and variant field access safety

3. **Typed Container Tests** (Requirements 4.1-4.4)
   - Test list and dictionary type declarations with various element types
   - Validate element type enforcement during container operations
   - Test container type validation and homogeneous type requirements
   - Verify container access type safety and constraint enforcement

4. **Option/Result Tests** (Requirements 3.1-3.4)
   - Test Option type creation with Some/None variants
   - Test Result type success/error handling with proper typing
   - Validate pattern matching on Option/Result with exhaustive cases
   - Verify explicit handling requirements for both variants

5. **Structured Type Tests** (Requirements 5.1-5.4)
   - Test structured type creation with named fields
   - Validate field type constraints and existence checking
   - Test required field validation during instance creation
   - Verify composition and nesting of structured types

6. **Type Inference Tests** (Requirements 7.1-7.4)
   - Test variable type inference from initialization values
   - Validate type alias inference in expressions
   - Test container element type inference from contents
   - Verify ambiguity detection and explicit annotation requirements

### Integration Tests

1. **End-to-End Type System Tests** (Requirements 6.1-6.4)
   - Complex type hierarchies with multiple levels of nesting
   - Mixed type alias and union usage in real-world scenarios
   - Typed containers with union elements and structured types
   - Type consistency validation across entire programs

2. **Runtime Type Safety Tests** (Requirements 8.1-8.4)
   - Pattern matching exhaustiveness with union types
   - Type discrimination accuracy for complex variants
   - Memory safety with complex types and nested structures
   - Runtime introspection capabilities for debugging

3. **Comprehensive Error Handling Tests** (Requirements 6.1-6.3)
   - Clear error messages for type mismatches with suggestions
   - Compile-time prevention of incompatible operations
   - Undefined type detection with helpful recommendations
   - Error recovery and continued compilation after type errors

### Performance Tests

1. **Type Checking Performance**
   - Large type hierarchies
   - Complex union type checking
   - Generic type instantiation overhead

2. **Runtime Performance**
   - Union type discrimination speed
   - Option/Result unwrapping performance
   - Pattern matching efficiency

## Implementation Status and Next Steps

### ✅ Phase 1: Basic Type Aliases - COMPLETED
- ✅ Implement type declaration parsing
- ✅ Add type alias registry to TypeSystem
- ✅ Support primitive type aliases
- ✅ Basic type resolution with circular dependency detection

### 🔄 Phase 2: Union Types - PARTIALLY COMPLETED
- ✅ Implement union type syntax parsing
- ✅ Add union type support to TypeSystem
- 📋 **NEEDS COMPLETION**: Runtime union value representation
- 📋 **NEEDS COMPLETION**: Pattern matching integration

### 🔄 Phase 3: Typed Containers - PARTIALLY COMPLETED
- ✅ Enhanced list/dictionary type infrastructure
- 📋 **NEEDS COMPLETION**: Container type parsing (`[elementType]`, `{keyType: valueType}`)
- 📋 **NEEDS COMPLETION**: Container type validation
- 📋 **NEEDS COMPLETION**: Homogeneous type enforcement

### 🔄 Phase 4: Built-in Types - PARTIALLY COMPLETED
- 📋 **NEEDS COMPLETION**: Option type implementation as union type
- ✅ Result type implementation (via error handling system)
- 📋 **NEEDS COMPLETION**: Pattern matching integration
- 📋 **NEEDS COMPLETION**: Runtime type discrimination

### 📋 Phase 5: Advanced Features - PLANNED
- 🔄 Type inference improvements (mostly complete)
- 📋 Complex type relationships and constraints
- 📋 Performance optimizations for type checking
- ✅ Comprehensive error handling (completed)

## Critical Implementation Gaps

### 1. Union Type Runtime Support
**Current State**: Union types can be parsed and type-checked, but lack runtime value representation.

**Required Implementation**:
```cpp
// Enhanced Value struct for union types
struct Value {
    // ... existing fields ...
    
    // Union type support
    size_t activeUnionVariant = 0;  // Which variant is currently active
    std::vector<ValuePtr> unionVariants;  // Storage for all possible variants
    
    // Helper methods
    bool isUnionType() const;
    size_t getActiveVariant() const;
    ValuePtr getVariantValue(size_t index) const;
    void setActiveVariant(size_t index, ValuePtr value);
};

// VM support for union operations
enum class OpCode {
    // ... existing opcodes ...
    CREATE_UNION,      // Create union value with specific variant
    GET_UNION_VARIANT, // Get active variant from union
    CHECK_UNION_TYPE,  // Check if union is specific variant
    MATCH_UNION,       // Pattern match on union type
};
```

### 2. Typed Container Parsing
**Current State**: Container type infrastructure exists but lacks parsing support.

**Required Implementation**:
```cpp
// Parser extensions for typed containers
class Parser {
    std::shared_ptr<AST::TypeAnnotation> parseContainerType();
    std::shared_ptr<AST::TypeAnnotation> parseListType();      // [elementType]
    std::shared_ptr<AST::TypeAnnotation> parseDictType();      // {keyType: valueType}
    std::shared_ptr<AST::TypeAnnotation> parseTupleType();     // (type1, type2, ...)
};

// Enhanced TypeAnnotation for containers
struct TypeAnnotation {
    // ... existing fields ...
    
    // Container type support
    bool isTypedContainer = false;
    std::shared_ptr<TypeAnnotation> elementType = nullptr;     // For lists
    std::shared_ptr<TypeAnnotation> keyType = nullptr;         // For dictionaries
    std::shared_ptr<TypeAnnotation> valueType = nullptr;       // For dictionaries
    std::vector<std::shared_ptr<TypeAnnotation>> tupleTypes;   // For tuples
};
```

### 3. Pattern Matching Integration
**Current State**: Match expressions exist syntactically but lack union type integration.

**Required Implementation**:
```cpp
// Enhanced match statement for union types
class TypeChecker {
    void checkMatchStatement(const std::shared_ptr<AST::MatchStatement>& stmt);
    bool isExhaustiveUnionMatch(TypePtr unionType, const std::vector<std::shared_ptr<AST::MatchCase>>& cases);
    void validateUnionVariantAccess(TypePtr unionType, const std::string& variantName);
};

// Runtime pattern matching support
class VM {
    void executeMatchUnion(const std::shared_ptr<AST::MatchStatement>& stmt);
    bool matchesUnionVariant(ValuePtr value, const std::string& pattern);
    ValuePtr extractUnionVariantValue(ValuePtr unionValue, size_t variantIndex);
};
```

### 4. Option Type Integration
**Current State**: Option type framework exists but needs union type integration.

**Required Implementation**:
```cpp
// Option type as union type
type Option<T> = Some<T> | None;

// Built-in constructors
ValuePtr createSome(TypePtr valueType, ValuePtr value) {
    // Create union value with Some variant active
    auto unionType = createUnionType({createSomeType(valueType), createNoneType()});
    auto unionValue = createUnionValue(unionType, 0, value);  // Some is variant 0
    return unionValue;
}

ValuePtr createNone(TypePtr valueType) {
    // Create union value with None variant active
    auto unionType = createUnionType({createSomeType(valueType), createNoneType()});
    auto unionValue = createUnionValue(unionType, 1, nullptr);  // None is variant 1
    return unionValue;
}

// Pattern matching for Option types
match optionValue {
    Some(value) => { /* use value */ },
    None => { /* handle absence */ }
}
```

## Implementation Priority

### HIGH PRIORITY (Core Functionality)
1. **Union Type Runtime Support** - Essential for union type functionality
2. **Pattern Matching Integration** - Required for safe union type access

### MEDIUM PRIORITY (Enhanced Features)
3. **Typed Container Parsing** - Improves type safety for collections
4. **Option Type Integration** - Enhances null safety

### LOW PRIORITY (Advanced Features)
5. **Generic Type Parameters** - Advanced type system features
6. **Runtime Type Introspection** - Debugging and reflection capabilities