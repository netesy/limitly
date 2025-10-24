# Unified Error Handling and Optional Value System Documentation

## Overview

The Limit programming language implements a zero-cost, union-type based system that handles both errors and optional values through a unified `Type?` syntax. This system provides type-safe error propagation and null-safety without the overhead of exceptions or null pointers. The system is designed to be both performant and ergonomic, ensuring that errors and absent values cannot be silently ignored while maintaining excellent runtime performance and Limit's null-free design principles.

## Core Concepts

### Unified Optional and Error Types

The `Type?` syntax represents values that can either be successful results or error/absent conditions. This unified system handles both explicit errors and optional values (where absence is treated as an error condition):

```limit
// Optional value (absence treated as error)
fn find_user(id: int): str? {
    if (id == 1) {
        return ok("Alice");  // Present value
    }
    return err();  // Absent value (error condition, not null)
}

// Specific error type
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero("Cannot divide by zero"));
    }
    return ok(a / b);
}
```

### Error and Absence Propagation

The `?` operator automatically propagates both errors and absent values up the call stack:

```limit
fn calculate(): int? {
    var result = divide(10, 0)?;  // Error/absence propagates automatically
    return ok(result * 2);
}

fn process_user(id: int): str? {
    var user = find_user(id)?;  // Absent value propagates as error
    return ok("Processing " + user);
}
```

### Handling Errors and Absent Values

Both errors and absent values can be handled using the `?else` syntax or pattern matching:

```limit
// Using ?else for inline handling
var result = divide(10, 0)? else {
    print("Division failed or result absent");
    return 0;  // Default value (not null - Limit is null-free)
};

// Using pattern matching
match divide(10, 0) {
    Ok(result) => print("Success: " + result),
    Err => print("Division failed")  // Handles both errors and absence
}

// Pattern matching with specific error types
match divide_with_error(10, 0) {
    Ok(result) => print("Success: " + result),
    Err(DivisionByZero(msg)) => print("Division error: " + msg)
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

Optional and error types are part of function signatures:

```limit
fn risky_operation(): int?Error1, Error2 {
    // Can return int, Error1, or Error2
}

fn optional_operation(): str? {
    // Can return str or be absent (treated as error)
}
```

### Type System Integration

The unified optional/error system integrates seamlessly with the type system:

- Type inference works with optional and error types
- Generic functions can be fallible or return optional values
- The system maintains Limit's null-free design principles
- Error and optional types participate in type checking

### Pattern Matching

The unified system works seamlessly with pattern matching:

```limit
match some_operation() {
    Ok(result) => handle_success(result),
    Err => handle_absence_or_generic_error()
}

match specific_operation() {
    Ok(result) => handle_success(result),
    Err(Error1(msg)) => handle_error1(msg),
    Err(Error2(code, msg)) => handle_error2(code, msg)
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

The Limit unified optional value and error handling system provides a robust, performant, and ergonomic approach to managing both errors and absent values. By combining zero-cost abstractions with comprehensive type safety and null-free design principles, it enables developers to write reliable code without sacrificing performance.

The system's design prioritizes the common case (success/present values) while providing efficient handling of error conditions and absent values. Through careful optimization and thoughtful API design, it achieves the goal of making both error handling and optional value management safe, fast, and consistent.

Key benefits of the unified approach:
- **Single learning curve**: One system handles both errors and optional values
- **Null-free safety**: No null pointers or null references
- **Consistent syntax**: `?` operator works for both error and absence propagation
- **Type safety**: Compiler enforces handling of both error and absence cases
- **Performance**: Zero-cost abstractions with optimized success paths