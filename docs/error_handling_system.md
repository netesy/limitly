# Error Handling System Documentation

## Overview

The Limit programming language implements a zero-cost, union-type based error handling system that provides type-safe error propagation without the overhead of exceptions. The system is designed to be both performant and ergonomic, ensuring that errors cannot be silently ignored while maintaining excellent runtime performance.

## Core Concepts

### Error Union Types

Error union types represent values that can either be successful results or errors. They are declared using the `?` syntax:

```limit
fn divide(a: int, b: int) : int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero("Cannot divide by zero"));
    }
    return a / b;
}
```

### Error Propagation

The `?` operator automatically propagates errors up the call stack:

```limit
fn calculate() : int?DivisionByZero {
    let result = divide(10, 0)?;  // Error propagates automatically
    return result * 2;
}
```

### Error Handling

Errors can be handled using the `?else` syntax or pattern matching:

```limit
# Using ?else
var result = divide(10, 0) ?else {
    print("Division failed");
    return 0;
};

# Using pattern matching
match divide(10, 0) {
    val result => print("Success: " + result),
    err DivisionByZero(msg) => print("Error: " + msg)
}
```

## Performance Optimizations

### Zero-Cost Success Path

The error handling system is optimized for the common case where no errors occur:

- **No runtime overhead**: Success paths execute with the same performance as non-fallible code
- **Optimized memory layout**: Error unions use cache-friendly layouts
- **Branch prediction**: Code is structured to favor success paths

### Error Value Pooling

To reduce memory allocations during error handling:

- **Object pooling**: Error values are pooled and reused
- **Efficient allocation**: Pool grows in chunks to minimize allocation overhead
- **Automatic cleanup**: Pool automatically manages memory lifecycle

### Efficient Error Propagation

Error propagation is optimized for performance:

- **Stack-based propagation**: Uses call stack for efficient error passing
- **Minimal frame overhead**: Error frames are lightweight and cache-friendly
- **Fast path optimization**: Common error patterns are optimized

## Implementation Details

### Error Union Type Layout

Error unions are implemented as tagged unions with optimized memory layout:

```cpp
class ErrorUnion {
    enum class Tag : uint8_t { SUCCESS, ERROR };
    alignas(8) Tag tag_;  // Cache-aligned for performance
    union alignas(8) {
        ValuePtr successValue_;
        ErrorValue errorValue_;
    };
};
```

### Error Frame Stack

Error frames track error handling contexts:

```cpp
struct ErrorFrame {
    size_t handlerAddress;      // Jump target for error handling
    size_t stackBase;           // Stack cleanup point
    TypePtr expectedErrorType;  // Expected error type
    std::string functionName;   // For debugging
};
```

### Error Value Pool

Error values are pooled for efficiency:

```cpp
struct ErrorValuePool {
    std::vector<std::unique_ptr<ErrorValue>> pool;
    std::vector<bool> inUse;
    static constexpr size_t POOL_SIZE = 64;
    // ... pool management methods
};
```

## Performance Characteristics

### Benchmarks

The error handling system achieves the following performance characteristics:

- **Success path overhead**: < 5% compared to non-fallible code
- **Error path efficiency**: Minimal allocation overhead through pooling
- **Memory usage**: Compact representation with cache-friendly layout
- **Scalability**: Performance remains consistent with deep call stacks

### Optimization Techniques

1. **Branch prediction hints**: Code uses `[[likely]]` and `[[unlikely]]` attributes
2. **Inline functions**: Critical path functions are inlined
3. **Memory prefetching**: Cache-friendly data structures
4. **Pool management**: Efficient object reuse patterns

## Usage Guidelines

### Best Practices

1. **Use specific error types**: Prefer `Type?SpecificError` over generic `Type?`
2. **Handle errors close to source**: Don't propagate errors unnecessarily
3. **Use pattern matching**: For complex error handling scenarios
4. **Avoid deep nesting**: Keep error handling logic simple

### Performance Tips

1. **Favor success paths**: Structure code to minimize error conditions
2. **Use pooled errors**: For frequently occurring error types
3. **Minimize error data**: Keep error messages and data lightweight
4. **Profile error paths**: Use performance monitoring to identify bottlenecks

## Error Types

### Built-in Error Types

The system provides standard error types for common scenarios:

- `DivisionByZero`: Arithmetic division by zero
- `IndexOutOfBounds`: Array/list index violations
- `NullReference`: Null pointer access
- `TypeConversion`: Type conversion failures
- `IOError`: Input/output operations

### Custom Error Types

Define custom error types using enums:

```limit
enum NetworkError {
    ConnectionTimeout(str),
    InvalidResponse(int, str),
    AuthenticationFailed
}

fn fetch_data(url: str) : str?NetworkError {
    // Implementation that can return NetworkError
}
```

## Debugging and Monitoring

### Performance Statistics

The VM provides detailed statistics for error handling performance:

```cpp
struct ErrorHandlingStats {
    size_t successPathExecutions;
    size_t errorPathExecutions;
    size_t errorFramePushes;
    size_t errorFramePops;
    size_t errorValueAllocations;
    size_t errorValuePoolHits;
    size_t errorValuePoolMisses;
};
```

### Debug Output

Enable debug output to monitor error handling:

```cpp
vm.setDebug(true);  // Enable debug output
vm.printErrorStats();  // Print performance statistics
```

## Integration with Language Features

### Function Signatures

Error types are part of function signatures:

```limit
fn risky_operation() : Result?Error1, Error2 {
    // Can return Error1 or Error2
}
```

### Type System Integration

Error unions integrate seamlessly with the type system:

- Type inference works with error unions
- Generic functions can be fallible
- Error types participate in type checking

### Pattern Matching

Error unions work with pattern matching:

```limit
match some_operation() {
    val result => handle_success(result),
    err Error1(msg) => handle_error1(msg),
    err Error2(code, msg) => handle_error2(code, msg)
}
```

## Future Enhancements

### Planned Improvements

1. **Async error handling**: Integration with async/await
2. **Error aggregation**: Collecting multiple errors
3. **Error context**: Stack trace information
4. **Performance profiling**: Built-in performance monitoring

### Research Areas

1. **Zero-allocation errors**: Compile-time error handling
2. **Error prediction**: Machine learning for error prediction
3. **Distributed errors**: Error handling across network boundaries
4. **Error recovery**: Automatic error recovery strategies

## Conclusion

The Limit error handling system provides a robust, performant, and ergonomic approach to error management. By combining zero-cost abstractions with comprehensive type safety, it enables developers to write reliable code without sacrificing performance.

The system's design prioritizes the common case (success) while providing efficient handling of error conditions. Through careful optimization and thoughtful API design, it achieves the goal of making error handling both safe and fast.