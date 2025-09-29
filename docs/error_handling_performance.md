# Error Handling Performance Guide

## Overview

This guide provides detailed information about the performance characteristics of Limit's error handling system and best practices for achieving optimal performance.

## Zero-Cost Abstractions

### Success Path Optimization

The error handling system is designed to have minimal impact on the success path:

```limit
# This code has near-zero overhead compared to non-fallible equivalent
fn fast_computation(data: List<int>) : int {
    var sum = 0;
    iter (value in data) {
        var processed = process_value(value)?;  # Zero-cost when successful
        sum = sum + processed;
    }
    return sum;
}
```

### Performance Characteristics

- **Success path overhead**: < 5% compared to non-fallible code
- **Error path latency**: Optimized for quick error propagation
- **Memory overhead**: Minimal additional memory usage
- **Cache efficiency**: Optimized data structures for cache performance

## Optimization Techniques

### 1. Error Value Pooling

The system automatically pools error values to reduce allocation overhead:

```cpp
// Automatic pooling for common error patterns
ValuePtr error = createPooledErrorValue("CommonError", "Message");
```

Benefits:
- Reduces garbage collection pressure
- Improves allocation performance
- Minimizes memory fragmentation

### 2. Efficient Error Propagation

Error propagation uses stack-based mechanisms:

```limit
fn deeply_nested() : int?Error {
    return level1()?;  # Efficient propagation through call stack
}

fn level1() : int?Error {
    return level2()?;
}

fn level2() : int?Error {
    return level3()?;
}
```

Optimizations:
- Stack-based error frames
- Minimal frame overhead
- Fast unwinding for error cases

### 3. Branch Prediction Optimization

Code is structured to favor success paths:

```cpp
// Compiler hints for better branch prediction
if (isErrorValue(value)) [[unlikely]] {
    handleError(value);
} else [[likely]] {
    handleSuccess(value);
}
```

### 4. Cache-Friendly Data Structures

Error unions use optimized memory layout:

```cpp
class ErrorUnion {
    alignas(8) Tag tag_;  // Cache-aligned
    union alignas(8) {    // Optimized union layout
        ValuePtr successValue_;
        ErrorValue errorValue_;
    };
};
```

## Performance Monitoring

### Built-in Statistics

The VM provides comprehensive performance statistics:

```cpp
// Access performance statistics
const auto& stats = vm.getErrorStats();
std::cout << "Success ratio: " << stats.getSuccessPathRatio() << std::endl;
std::cout << "Pool hit ratio: " << stats.getPoolHitRatio() << std::endl;
```

### Key Metrics

1. **Success Path Ratio**: Percentage of operations that succeed
2. **Pool Hit Ratio**: Efficiency of error value pooling
3. **Frame Push/Pop Ratio**: Error frame stack efficiency
4. **Allocation Rate**: Error value allocation frequency

### Performance Profiling

```limit
# Enable performance monitoring
fn profile_error_handling() {
    var iterations = 10000;
    var start_time = clock();
    
    iter (i in 1..iterations) {
        var result = potentially_failing_operation(i)?;
        process_result(result);
    }
    
    var end_time = clock();
    var duration = end_time - start_time;
    var ops_per_second = iterations / duration;
    
    print("Operations per second: " + ops_per_second);
}
```

## Best Practices

### 1. Optimize for Success

Structure your code to minimize error conditions:

```limit
# Good: Check preconditions early
fn safe_divide(a: int, b: int) : int?DivisionByZero {
    if (b == 0) {  # Early check
        return err(DivisionByZero("Division by zero"));
    }
    return a / b;  # Fast path
}

# Avoid: Complex error logic in hot paths
fn inefficient_divide(a: int, b: int) : int?DivisionByZero {
    try {
        var result = complex_calculation(a, b);
        if (is_invalid(result)) {
            return err(DivisionByZero("Complex error"));
        }
        return result;
    } catch {
        return err(DivisionByZero("Caught exception"));
    }
}
```

### 2. Use Specific Error Types

Prefer specific error types over generic ones:

```limit
// Good: Specific error types
fn parse_number(text: str) : int?ParseError {
    // Specific error handling
}

# Less optimal: Generic error types
fn parse_number(text: str) : int? {
    # Generic error handling has more overhead
}
```

### 3. Handle Errors Locally

Handle errors close to their source when possible:

```limit
# Good: Local error handling
fn process_data(data: List<str>) : List<int> {
    var results = [];
    iter (item in data) {
        var parsed = parse_int(item) ?else {
            continue;  // Handle locally
        };
        results.append(parsed);
    }
    return results;
}

# Less optimal: Propagating all errors
fn process_data(data: List<str>) : List<int>?ParseError {
    var results = [];
    iter (item in data) {
        var parsed = parse_int(item)?;  // Propagates all errors
        results.append(parsed);
    }
    return results;
}
```

### 4. Minimize Error Data

Keep error messages and data lightweight:

```limit
# Good: Lightweight error data
enum NetworkError {
    Timeout,
    ConnectionRefused,
    InvalidResponse(int)  # Minimal data
}

# Less optimal: Heavy error data
enum NetworkError {
    Timeout(str, List<str>, Dict<str, str>),  // Too much data
    ConnectionRefused(ComplexObject),
    InvalidResponse(str, List<ComplexObject>)
}
```

## Performance Testing

### Benchmark Framework

```limit
# Performance test framework
fn benchmark_error_handling() {
    var test_cases = [
        ("success_heavy", test_success_heavy),
        ("error_heavy", test_error_heavy),
        ("mixed_workload", test_mixed_workload)
    ];
    
    iter ((name, test_fn) in test_cases) {
        var start_time = clock();
        test_fn();
        var duration = clock() - start_time;
        print(name + ": " + duration + " seconds");
    }
}

fn test_success_heavy() {
    iter (i in 1..10000) {
        var result = always_succeeds(i)?;
        process_result(result);
    }
}

fn test_error_heavy() {
    iter (i in 1..1000) {
        var result = always_fails(i) ?else {
            continue;
        };
        process_result(result);
    }
}

fn test_mixed_workload() {
    iter (i in 1..5000) {
        var result = sometimes_fails(i) ?else {
            continue;
        };
        process_result(result);
    }
}
```

### Performance Targets

Target performance characteristics:

- **Success path overhead**: < 5%
- **Error propagation latency**: < 100ns
- **Memory overhead**: < 10% additional memory
- **Pool hit ratio**: > 90% for common errors

## Optimization Checklist

### Code Review Checklist

- [ ] Error types are specific and lightweight
- [ ] Success paths are optimized
- [ ] Error handling is local when possible
- [ ] Error messages are concise
- [ ] Performance-critical paths avoid complex error logic

### Performance Validation

- [ ] Benchmark success path performance
- [ ] Measure error propagation latency
- [ ] Validate pool hit ratios
- [ ] Profile memory usage
- [ ] Test with realistic workloads

## Common Performance Pitfalls

### 1. Over-Engineering Error Types

```limit
# Avoid: Complex error hierarchies
enum OverEngineeredError {
    NetworkError(NetworkSubError),
    DatabaseError(DatabaseSubError),
    ValidationError(ValidationSubError)
}

# Prefer: Simple, flat error types
enum SimpleError {
    NetworkTimeout,
    DatabaseConnectionFailed,
    InvalidInput(str)
}
```

### 2. Excessive Error Propagation

```limit
# Avoid: Propagating every error
fn process_items(items: List<Item>) : List<Result>?Error {
    var results = [];
    iter (item in items) {
        var result = process_item(item)?;  # Stops on first error
        results.append(result);
    }
    return results;
}

# Prefer: Collect errors or handle locally
fn process_items(items: List<Item>) : List<Result> {
    var results = [];
    iter (item in items) {
        var result = process_item(item) ?else {
            continue;  # Skip failed items
        };
        results.append(result);
    }
    return results;
}
```

### 3. Heavy Error Context

```limit
# Avoid: Including too much context in errors
fn parse_config(file: str) : Config?ParseError {
    return err(ParseError(
        file,
        read_entire_file(file),  # Too much data
        get_system_info(),       # Unnecessary context
        get_call_stack()         # Expensive to generate
    ));
}

# Prefer: Minimal error context
fn parse_config(file: str) : Config?ParseError {
    return err(ParseError("Invalid config format"));
}
```

## Conclusion

The Limit error handling system achieves high performance through careful optimization of common patterns. By following the guidelines in this document, you can ensure that your error handling code is both safe and fast.

Key takeaways:
- Optimize for the success path
- Use specific, lightweight error types
- Handle errors locally when possible
- Monitor performance with built-in statistics
- Follow the performance testing framework

Remember that the goal is to make error handling so efficient that it doesn't discourage proper error checking and handling in your applications.