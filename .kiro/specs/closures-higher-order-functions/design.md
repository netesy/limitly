# Design Document

## Overview

This design implements closures and higher-order functions for the Limit programming language. The implementation extends the existing function system to support variable capture, function parameters, and function returns. A comprehensive set of builtin higher-order functions will be provided in a separate module for functional programming operations.

The design builds upon the existing VM architecture, extending the current function implementation with closure support and adding new opcodes for closure operations. The builtin functions will be implemented as native VM functions for optimal performance.

## Architecture

### Core Components

1. **Closure System**: Extends the existing function system with variable capture
2. **Higher-Order Function Support**: Enables functions as first-class values
3. **Builtin Functions Module**: Provides essential functional programming utilities
4. **Memory Management**: Handles closure variable lifetime and cleanup
5. **Lambda Expression Support**: Syntax for anonymous functions

### Integration Points

- **VM Extension**: New opcodes for closure operations
- **Value System**: Enhanced function representation with captured variables
- **Type System**: Function types with parameter and return type information
- **Memory Manager**: Closure variable lifetime management
- **Parser**: Lambda expression syntax support

## Components and Interfaces

### 1. Closure Value Representation

```cpp
// Enhanced function value with closure support
struct ClosureValue {
    std::shared_ptr<backend::UserDefinedFunction> function;
    std::shared_ptr<Environment> capturedEnvironment;  // Captured variables
    std::vector<std::string> capturedVariables;       // Names of captured vars
    
    // Execution context
    ValuePtr execute(const std::vector<ValuePtr>& args);
};

// Function type information
struct FunctionType {
    std::vector<TypePtr> paramTypes;
    TypePtr returnType;
    bool isVariadic = false;
    
    // Higher-order function support
    bool acceptsFunctions() const;
    bool returnsFunction() const;
};
```

### 2. New Opcodes for Closures

```cpp
enum class Opcode {
    // Existing opcodes...
    
    // Closure operations
    CREATE_CLOSURE,      // Create closure with captured variables
    CAPTURE_VAR,         // Capture variable in closure
    PUSH_LAMBDA,         // Push lambda function onto stack
    CALL_CLOSURE,        // Call closure with captured environment
    
    // Higher-order function operations
    PUSH_FUNCTION_REF,   // Push function reference onto stack
    CALL_HIGHER_ORDER,   // Call function with function parameters
};
```

### 3. Builtin Functions Interface

```cpp
// Builtin function registry
class BuiltinFunctions {
public:
    static void registerAll(VM* vm);
    
    // Collection operations
    static ValuePtr map(const std::vector<ValuePtr>& args);
    static ValuePtr filter(const std::vector<ValuePtr>& args);
    static ValuePtr reduce(const std::vector<ValuePtr>& args);
    static ValuePtr forEach(const std::vector<ValuePtr>& args);
    
    // Search operations
    static ValuePtr find(const std::vector<ValuePtr>& args);
    static ValuePtr some(const std::vector<ValuePtr>& args);
    static ValuePtr every(const std::vector<ValuePtr>& args);
    
    // Utility operations
    static ValuePtr compose(const std::vector<ValuePtr>& args);
    static ValuePtr curry(const std::vector<ValuePtr>& args);
    static ValuePtr partial(const std::vector<ValuePtr>& args);
};
```

### 4. Lambda Expression AST

```cpp
// Lambda expression AST node
struct LambdaExpr : public Expression {
    std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> params;
    std::shared_ptr<Expression> body;  // Single expression body
    std::optional<std::shared_ptr<TypeAnnotation>> returnType;
    
    // Captured variables (determined during analysis)
    std::vector<std::string> capturedVars;
};
```

### 5. Environment Enhancement

```cpp
// Enhanced environment for closure support
class Environment {
public:
    // Existing methods...
    
    // Closure support
    std::shared_ptr<Environment> createClosureEnvironment(
        const std::vector<std::string>& capturedVars);
    void captureVariable(const std::string& name, ValuePtr value);
    bool isVariableCaptured(const std::string& name) const;
    
private:
    std::unordered_set<std::string> capturedVariables;
    std::shared_ptr<Environment> closureParent;
};
```

## Data Models

### Closure Data Structure

```cpp
struct ClosureData {
    // Function metadata
    std::string functionName;
    size_t startAddress;
    size_t endAddress;
    
    // Parameter information
    std::vector<std::string> paramNames;
    std::vector<TypePtr> paramTypes;
    std::vector<std::pair<std::string, ValuePtr>> defaultValues;
    
    // Captured variables
    std::unordered_map<std::string, ValuePtr> capturedValues;
    std::shared_ptr<Environment> captureEnvironment;
    
    // Type information
    TypePtr returnType;
    bool isVariadic;
};
```

### Function Call Frame

```cpp
struct CallFrame {
    // Existing fields...
    
    // Closure support
    std::shared_ptr<Environment> closureEnvironment;
    std::unordered_map<std::string, ValuePtr> capturedVariables;
    
    // Higher-order function support
    std::vector<ValuePtr> functionParameters;
    bool isHigherOrderCall;
};
```

## Error Handling

### Closure-Specific Errors

1. **Variable Capture Errors**
   - Attempting to capture non-existent variables
   - Capturing variables that go out of scope
   - Circular capture references

2. **Function Type Errors**
   - Passing incompatible function types
   - Missing required function parameters
   - Return type mismatches

3. **Lambda Expression Errors**
   - Invalid lambda syntax
   - Type inference failures
   - Capture scope violations

### Error Recovery Strategies

- **Graceful Degradation**: Fall back to regular function calls when closure features fail
- **Type Inference**: Attempt to infer types when explicit annotations are missing
- **Scope Analysis**: Validate variable capture at compile time when possible

## Testing Strategy

### Unit Tests

1. **Closure Creation and Execution**
   - Basic closure creation with variable capture
   - Closure execution with captured variables
   - Nested closure scenarios

2. **Higher-Order Functions**
   - Functions accepting function parameters
   - Functions returning functions
   - Function composition and currying

3. **Builtin Functions**
   - Each builtin function with various input types
   - Error handling for invalid inputs
   - Performance characteristics

4. **Lambda Expressions**
   - Lambda syntax parsing
   - Lambda execution with captures
   - Lambda type inference

### Integration Tests

1. **Complex Functional Patterns**
   - Map-reduce operations
   - Function composition chains
   - Curried function applications

2. **Memory Management**
   - Closure variable lifetime
   - Garbage collection of closures
   - Memory leak detection

3. **Performance Tests**
   - Closure creation overhead
   - Function call performance
   - Builtin function efficiency

### Test Files Structure

```
tests/functions/
├── closures/
│   ├── basic_closure.lm
│   ├── nested_closures.lm
│   ├── closure_capture.lm
│   └── closure_memory.lm
├── higher_order/
│   ├── function_parameters.lm
│   ├── function_returns.lm
│   ├── composition.lm
│   └── currying.lm
├── builtins/
│   ├── map_filter_reduce.lm
│   ├── search_functions.lm
│   ├── utility_functions.lm
│   └── error_handling.lm
└── lambdas/
    ├── lambda_syntax.lm
    ├── lambda_capture.lm
    └── lambda_types.lm
```

## Implementation Phases

### Phase 1: Core Closure Support
- Extend Value system with ClosureValue
- Add closure opcodes to VM
- Implement basic variable capture
- Create simple closure test cases

### Phase 2: Lambda Expressions
- Add LambdaExpr to AST
- Implement lambda parsing
- Add lambda bytecode generation
- Test lambda execution

### Phase 3: Higher-Order Functions
- Enhance function call mechanism
- Support functions as parameters/returns
- Implement function type checking
- Test complex function compositions

### Phase 4: Builtin Functions
- Create builtin functions module
- Implement core functional operations
- Integrate with VM startup
- Comprehensive builtin testing

### Phase 5: Memory Management
- Optimize closure memory usage
- Implement proper cleanup
- Add garbage collection support
- Performance optimization

## Performance Considerations

### Optimization Strategies

1. **Closure Creation**: Minimize overhead when creating closures
2. **Variable Capture**: Efficient storage and access of captured variables
3. **Function Calls**: Fast dispatch for both regular and closure calls
4. **Memory Usage**: Compact representation of closure data

### Benchmarking Targets

- Closure creation: < 100ns overhead
- Closure calls: < 50ns additional overhead vs regular calls
- Builtin functions: Comparable to native implementations
- Memory usage: < 64 bytes per closure on average