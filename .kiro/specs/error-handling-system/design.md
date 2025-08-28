# Design Document

## Overview

The error handling system for Limit implements a zero-cost, union-type based approach to error handling that avoids exceptions in favor of explicit error propagation. The system uses the `?` operator for both marking fallible functions and propagating errors, with compile-time guarantees that errors cannot be silently ignored. The design integrates seamlessly with the existing type system and VM architecture while maintaining performance comparable to Rust/Zig.

## Architecture

### Core Components

1. **Error Union Types** - Extend the existing union type system to support error variants
2. **Fallible Expression AST Nodes** - New AST nodes for `?` operator and error construction
3. **Error Propagation Bytecode** - VM instructions for efficient error handling
4. **Type System Integration** - Compile-time error type checking and inference
5. **Pattern Matching Extensions** - Support for `val`/`err` patterns in match expressions

### Integration Points

- **Frontend**: Extend parser to handle `?` syntax and error type annotations
- **Type System**: Add error union types to existing `UnionType` infrastructure
- **AST**: New expression nodes for fallible operations and error construction
- **Backend**: New bytecode instructions for error handling operations
- **VM**: Runtime support for error propagation and pattern matching

## Components and Interfaces

### 1. AST Extensions

#### New Expression Types

```cpp
// Fallible expression with ? operator
struct FallibleExpr : public Expression {
    std::shared_ptr<Expression> expression;
    std::shared_ptr<Statement> elseHandler;  // Optional else block
    std::string elseVariable;                // Optional error variable name
};

// Error construction expression
struct ErrorConstructExpr : public Expression {
    std::string errorType;                   // Error type name
    std::vector<std::shared_ptr<Expression>> arguments;  // Constructor arguments
};

// Success value construction (ok() function)
struct OkConstructExpr : public Expression {
    std::shared_ptr<Expression> value;
};
```

#### Type Annotation Extensions

```cpp
// Extend existing TypeAnnotation struct
struct TypeAnnotation {
    // ... existing fields ...
    bool isFallible = false;                 // Whether this type can fail (Type?)
    std::vector<std::string> errorTypes;     // Specific error types (Type?Error1, Error2)
};
```

### 2. Type System Extensions

#### Error Union Types

```cpp
// Extend existing UnionType to support error semantics
struct ErrorUnionType {
    TypePtr successType;                     // The success value type
    std::vector<std::string> errorTypes;     // Allowed error type names
    bool isGenericError = false;             // True for Type?, false for Type?Error1, Error2
};

// Add to Type struct extra variant
std::variant<..., ErrorUnionType> extra;
```

#### Built-in Error Types

```cpp
// Standard error types
enum class BuiltinErrorType {
    DivisionByZero,
    IndexOutOfBounds,
    NullReference,
    TypeConversion,
    IOError,
    ParseError,
    NetworkError
};

// Error type registry
class ErrorTypeRegistry {
    std::map<std::string, TypePtr> errorTypes;
    
public:
    void registerBuiltinErrors();
    void registerUserError(const std::string& name, TypePtr type);
    TypePtr getErrorType(const std::string& name);
    bool isErrorType(const std::string& name);
};
```

### 3. Bytecode Extensions

#### New Opcodes

```cpp
enum class Opcode {
    // ... existing opcodes ...
    
    // Error handling operations
    CHECK_ERROR,        // Check if value is error, jump if true
    PROPAGATE_ERROR,    // Propagate error up the call stack
    CONSTRUCT_ERROR,    // Construct error value
    CONSTRUCT_OK,       // Construct success value
    UNWRAP_VALUE,       // Extract value from success union
    MATCH_ERROR_TYPE,   // Match specific error type in pattern matching
    
    // Error union operations
    IS_ERROR,           // Check if union contains error
    IS_SUCCESS,         // Check if union contains success value
    GET_ERROR_TYPE,     // Get error type from error union
};
```

#### Error Propagation Strategy

```cpp
// Error propagation uses stack-based approach
// 1. Function calls push error handler address
// 2. ? operator checks for error and jumps to handler
// 3. Handler either propagates or handles locally
struct ErrorFrame {
    size_t handlerAddress;      // Bytecode address of error handler
    size_t stackBase;           // Stack position when frame created
    TypePtr expectedErrorType;  // Expected error type for this frame
};
```

### 4. VM Runtime Support

#### Error Value Representation

```cpp
// Extend existing Value system
struct ErrorValue {
    std::string errorType;
    std::string message;
    std::vector<ValuePtr> arguments;
    size_t sourceLocation;      // For stack traces
};

// Add to Value variant
std::variant<..., ErrorValue> data;
```

#### Error Propagation Runtime

```cpp
class ErrorHandler {
    std::stack<ErrorFrame> errorFrames;
    
public:
    void pushErrorFrame(size_t handlerAddr, TypePtr errorType);
    void popErrorFrame();
    bool propagateError(ValuePtr errorValue);
    ValuePtr handleError(ValuePtr errorValue, const std::string& expectedType);
};
```

## Data Models

### Error Union Value Layout

```cpp
// Zero-cost error representation using tagged union
struct ErrorUnion {
    enum class Tag : uint8_t { SUCCESS, ERROR };
    
    Tag tag;
    union {
        ValuePtr successValue;
        ErrorValue errorValue;
    };
    
    // Efficient construction/destruction
    ErrorUnion(ValuePtr success) : tag(Tag::SUCCESS), successValue(success) {}
    ErrorUnion(ErrorValue error) : tag(Tag::ERROR), errorValue(error) {}
};
```

### Function Signature Representation

```cpp
// Extend existing FunctionType
struct FunctionType {
    std::vector<TypePtr> paramTypes;
    TypePtr returnType;
    bool canFail = false;                    // Whether function can return errors
    std::vector<std::string> errorTypes;     // Specific error types function can return
};
```

## Error Handling

### Compile-Time Error Checking

1. **Unhandled Fallible Calls**: Detect when fallible functions are called without `?` or `match`
2. **Error Type Compatibility**: Ensure propagated errors are compatible with function signatures
3. **Exhaustive Pattern Matching**: Require all error types to be handled in match expressions
4. **Dead Code Detection**: Identify unreachable code after error propagation

### Runtime Error Propagation

1. **Stack-Based Propagation**: Use call stack to propagate errors efficiently
2. **Zero-Cost Success Path**: No overhead when no errors occur
3. **Efficient Error Construction**: Minimize allocations for error values
4. **Stack Trace Generation**: Maintain call stack information for debugging

## Testing Strategy

### Unit Tests

1. **Parser Tests**: Verify correct parsing of `?` syntax and error type annotations
2. **Type System Tests**: Test error union type compatibility and inference
3. **Bytecode Generation Tests**: Verify correct bytecode for error handling constructs
4. **VM Execution Tests**: Test runtime error propagation and handling

### Integration Tests

1. **End-to-End Error Flows**: Test complete error propagation from creation to handling
2. **Pattern Matching Tests**: Verify correct matching on success/error values
3. **Performance Tests**: Ensure zero-cost abstractions for success paths
4. **Interoperability Tests**: Test error handling with existing language features

### Error Scenarios

1. **Division by Zero**: Built-in arithmetic error handling
2. **Array Bounds**: Index out of bounds error propagation
3. **File I/O**: Simulated I/O error handling
4. **Type Conversion**: Invalid conversion error handling
5. **Nested Error Propagation**: Multiple levels of error propagation

## Implementation Phases

### Phase 1: Core Infrastructure
- Extend AST with error handling nodes
- Add error union types to type system
- Implement basic error type registry
- Add new bytecode opcodes

### Phase 2: Parser Integration
- Extend parser to handle `?` syntax
- Parse error type annotations in function signatures
- Parse `err()` and `ok()` constructor calls
- Parse error patterns in match expressions

### Phase 3: Type System Integration
- Implement error union type checking
- Add error propagation type inference
- Implement exhaustive pattern matching checks
- Add compile-time error compatibility validation

### Phase 4: VM Implementation
- Implement error handling opcodes in VM
- Add error propagation runtime support
- Implement efficient error value representation
- Add stack trace generation for errors

### Phase 5: Built-in Error Types
- Implement standard error types
- Add error handling to arithmetic operations
- Add error handling to array/dict operations
- Add error handling to type conversions

### Phase 6: Pattern Matching
- Extend match expressions for error patterns
- Implement `val`/`err` pattern matching
- Add specific error type pattern matching
- Implement error parameter extraction

## Performance Considerations

### Zero-Cost Abstractions

1. **Success Path Optimization**: No runtime overhead when no errors occur
2. **Compile-Time Error Checking**: Move error validation to compile time
3. **Efficient Error Representation**: Use tagged unions for minimal memory overhead
4. **Stack-Based Propagation**: Avoid heap allocations for error propagation

### Memory Management

1. **Error Value Pooling**: Reuse error value objects to reduce allocations
2. **Stack Trace Optimization**: Lazy stack trace generation only when needed
3. **Error Type Interning**: Intern error type names to reduce string allocations
4. **Union Type Optimization**: Optimize union type layout for cache efficiency

## Security Considerations

1. **Error Information Leakage**: Ensure error messages don't leak sensitive information
2. **Stack Trace Sanitization**: Filter sensitive information from stack traces
3. **Error Injection Prevention**: Validate error construction to prevent injection attacks
4. **Resource Cleanup**: Ensure proper resource cleanup during error propagation