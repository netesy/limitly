# Design Document

## Overview

This design enhances the Limit programming language with comprehensive pattern matching capabilities including destructuring, guard clauses, and seamless error handling integration. Additionally, it implements zero-cost loop abstractions through advanced compiler optimizations that eliminate runtime overhead while maintaining high-level expressiveness.

The design builds upon the existing match statement infrastructure and extends it with:
1. **Advanced Destructuring**: Tuple, array, struct, and nested pattern support
2. **Enhanced Error Patterns**: Comprehensive error handling with destructuring
3. **Guard Clauses**: Conditional pattern matching with runtime checks
4. **Zero-Cost Loops**: Compiler optimizations for iterator elimination and loop fusion
5. **Type Integration**: Pattern-based type narrowing and exhaustiveness checking

### Integration Points

- **AST**: Extended pattern expression nodes for destructuring and guards
- **Parser**: Enhanced pattern parsing with complex destructuring syntax
- **Type System**: Pattern-based type narrowing and exhaustiveness analysis
- **Backend**: Optimized bytecode generation for patterns and loops
- **VM**: Efficient pattern matching execution and loop optimization

## Architecture

### Pattern Matching Architecture

```
Pattern Expression Hierarchy:
├── BasicPatternExpr (literals, wildcards)
├── DestructuringPatternExpr
│   ├── TuplePatternExpr (a, b, c)
│   ├── ArrayPatternExpr [first, ...rest]
│   ├── StructPatternExpr { field1, field2 }
│   └── NestedPatternExpr (recursive combinations)
├── ErrorPatternExpr
│   ├── OkPatternExpr Ok(value)
│   ├── ErrPatternExpr Err(error)
│   └── TypedErrorPatternExpr Err(CustomError { field })
└── GuardedPatternExpr (pattern if condition)
```

### Loop Optimization Architecture

```
Loop Optimization Pipeline:
1. Loop Analysis Phase
   ├── Bounds Analysis (compile-time known ranges)
   ├── Side Effect Analysis (pure vs impure operations)
   ├── Memory Access Pattern Analysis
   └── Dependency Analysis (loop-carried dependencies)

2. Optimization Phase
   ├── Iterator Elimination (range loops → counter loops)
   ├── Bounds Check Elimination (safe array access)
   ├── Loop Fusion (combine adjacent loops)
   ├── Loop Unrolling (small fixed iterations)
   └── Vectorization Hints (SIMD opportunities)

3. Code Generation Phase
   ├── Optimized Bytecode Emission
   ├── Register Allocation Hints
   └── Cache-Friendly Memory Layout
```

## Components and Interfaces

### Enhanced AST Nodes

#### New Pattern Expression Types

```cpp
// Enhanced tuple destructuring with nested patterns
struct TuplePatternExpr : public Expression {
    std::vector<std::shared_ptr<Expression>> elements;
    std::vector<bool> isWildcard;  // Track _ patterns
    bool hasRestElement = false;
    size_t restElementIndex = 0;
};

// Array destructuring with rest patterns
struct ArrayPatternExpr : public Expression {
    std::vector<std::shared_ptr<Expression>> elements;
    std::optional<std::string> restElement;  // ...rest syntax
    size_t restElementIndex = 0;
    bool hasRestElement = false;
};

// Struct destructuring with field renaming
struct StructPatternExpr : public Expression {
    std::string typeName;
    struct FieldPattern {
        std::string fieldName;
        std::optional<std::string> bindingName;  // field: newName
        std::shared_ptr<Expression> nestedPattern;  // For nested destructuring
    };
    std::vector<FieldPattern> fields;
    bool hasRestElement = false;  // .. syntax
};

// Guard clause support
struct GuardedPatternExpr : public Expression {
    std::shared_ptr<Expression> pattern;
    std::shared_ptr<Expression> guard;
};

// Enhanced error patterns with destructuring
struct EnhancedErrorPatternExpr : public Expression {
    enum class ErrorPatternType {
        Ok,           // Ok(value)
        Err,          // Err(error)
        TypedError    // Err(CustomError { field1, field2 })
    };
    
    ErrorPatternType type;
    std::shared_ptr<Expression> valuePattern;  // Can be destructuring pattern
    std::string errorTypeName;  // For typed errors
};
```

#### Loop Optimization Metadata

```cpp
// Loop analysis metadata for optimization
struct LoopOptimizationInfo {
    bool hasKnownBounds = false;
    int64_t startBound = 0;
    int64_t endBound = 0;
    int64_t stepSize = 1;
    
    bool isPure = true;  // No side effects
    bool accessesMemorySequentially = false;
    bool canVectorize = false;
    bool canUnroll = false;
    size_t unrollFactor = 1;
    
    std::vector<std::string> invariantExpressions;
    std::vector<std::string> loopCarriedDependencies;
};

// Enhanced loop statements with optimization hints
struct OptimizedForStatement : public ForStatement {
    LoopOptimizationInfo optimizationInfo;
    bool isZeroCost = false;  // Compiler can eliminate overhead
};

struct OptimizedIterStatement : public IterStatement {
    LoopOptimizationInfo optimizationInfo;
    bool canEliminateIterator = false;  // Convert to index-based loop
};
```

### Enhanced Bytecode Instructions

```cpp
// Pattern matching bytecode operations
enum class PatternOpcode {
    // Destructuring operations
    DESTRUCTURE_TUPLE,      // Extract tuple elements to stack
    DESTRUCTURE_ARRAY,      // Extract array elements with rest support
    DESTRUCTURE_STRUCT,     // Extract struct fields by name
    
    // Pattern matching control flow
    MATCH_PATTERN_GUARD,    // Execute pattern with guard clause
    MATCH_EXHAUSTIVE_CHECK, // Verify all patterns covered
    
    // Error pattern operations
    MATCH_OK_PATTERN,       // Match Ok(value) pattern
    MATCH_ERR_PATTERN,      // Match Err(error) pattern
    MATCH_TYPED_ERROR,      // Match specific error type with destructuring
    
    // Loop optimization operations
    OPTIMIZED_RANGE_LOOP,   // Zero-cost range iteration
    BOUNDS_CHECK_ELIM,      // Eliminated bounds check marker
    VECTORIZED_OPERATION,   // SIMD operation hint
};
```

### Type System Integration

#### Pattern Type Analysis

```cpp
class PatternTypeAnalyzer {
public:
    // Analyze pattern and return extracted variable types
    std::unordered_map<std::string, TypePtr> analyzePattern(
        std::shared_ptr<Expression> pattern, 
        TypePtr matchedType
    );
    
    // Check if patterns are exhaustive for given type
    bool isExhaustiveMatch(
        const std::vector<std::shared_ptr<Expression>>& patterns,
        TypePtr matchedType
    );
    
    // Detect unreachable patterns
    std::vector<size_t> findUnreachablePatterns(
        const std::vector<std::shared_ptr<Expression>>& patterns
    );
    
    // Type narrowing for match branches
    TypePtr narrowTypeForPattern(
        TypePtr originalType,
        std::shared_ptr<Expression> pattern
    );
};
```

#### Loop Optimization Analysis

```cpp
class LoopOptimizer {
public:
    // Analyze loop for optimization opportunities
    LoopOptimizationInfo analyzeLoop(std::shared_ptr<Statement> loop);
    
    // Check if loop can be converted to zero-cost form
    bool canOptimizeToZeroCost(std::shared_ptr<Statement> loop);
    
    // Detect vectorization opportunities
    bool canVectorize(std::shared_ptr<Statement> loop);
    
    // Analyze memory access patterns
    MemoryAccessPattern analyzeMemoryAccess(std::shared_ptr<Statement> loop);
    
    // Detect loop invariants
    std::vector<std::shared_ptr<Expression>> findInvariants(
        std::shared_ptr<Statement> loop
    );
};
```

## Data Models

### Pattern Matching Data Flow

```
Input Expression → Pattern Analysis → Type Narrowing → Code Generation
                                  ↓
                              Guard Evaluation → Branch Selection → Variable Binding
```

### Loop Optimization Data Flow

```
Loop AST → Analysis Phase → Optimization Decisions → Optimized Bytecode
         ↓                 ↓                        ↓
    Bounds Analysis   Iterator Elimination    Zero-Cost Execution
    Side Effects      Loop Fusion            
    Memory Patterns   Vectorization
```

### Pattern Matching Runtime Model

```cpp
struct PatternMatchContext {
    ValuePtr matchedValue;
    std::unordered_map<std::string, ValuePtr> bindings;
    std::vector<std::shared_ptr<Expression>> remainingPatterns;
    bool hasMatched = false;
};

struct DestructuringResult {
    bool success;
    std::unordered_map<std::string, ValuePtr> extractedValues;
    std::string errorMessage;  // If destructuring failed
};
```

## Error Handling

### Pattern Matching Errors

1. **Compile-Time Errors**:
   - Non-exhaustive pattern matching
   - Unreachable patterns
   - Type mismatches in destructuring
   - Invalid field names in struct patterns
   - Guard clause type errors

2. **Runtime Errors**:
   - Destructuring failures (wrong structure)
   - Guard clause evaluation errors
   - Pattern matching stack overflow

### Loop Optimization Errors

1. **Analysis Errors**:
   - Unable to determine loop bounds
   - Complex side effects preventing optimization
   - Unsafe memory access patterns

2. **Optimization Failures**:
   - Graceful fallback to unoptimized loops
   - Clear diagnostic messages for failed optimizations

## Testing Strategy

### Pattern Matching Tests

1. **Basic Destructuring Tests**:
   ```limit
   // Tuple destructuring
   match (1, 2, 3) {
       (a, b, c) => print("a={a}, b={b}, c={c}")
   }
   
   // Array destructuring with rest
   match [1, 2, 3, 4, 5] {
       [first, second, ...rest] => print("first={first}, rest={rest}")
   }
   
   // Struct destructuring
   match person {
       Person { name, age } => print("name={name}, age={age}")
       Person { name: n, .. } => print("name={n}")
   }
   ```

2. **Error Pattern Tests**:
   ```limit
   match result {
       Ok(value) => print("success: {value}")
       Err(NetworkError { code, message }) => print("network error: {code} - {message}")
       Err(error) => print("other error: {error}")
   }
   ```

3. **Guard Clause Tests**:
   ```limit
   match value {
       x if x > 0 => print("positive")
       x if x < 0 => print("negative")
       _ => print("zero")
   }
   ```

### Loop Optimization Tests

1. **Zero-Cost Range Loops**:
   ```limit
   // Should compile to simple counter loop
   for i in 0..1000 {
       array[i] = i * 2;
   }
   ```

2. **Iterator Elimination**:
   ```limit
   // Should eliminate iterator object
   iter (item in collection) {
       process(item);
   }
   ```

3. **Loop Fusion**:
   ```limit
   // Should fuse into single loop
   for i in 0..n { a[i] = i; }
   for i in 0..n { b[i] = a[i] * 2; }
   ```

### Performance Benchmarks

1. **Pattern Matching Performance**:
   - Compare against manual if-else chains
   - Measure destructuring overhead
   - Test guard clause evaluation cost

2. **Loop Optimization Performance**:
   - Compare optimized vs unoptimized loops
   - Measure iterator elimination benefits
   - Test vectorization improvements

### Integration Tests

1. **End-to-End Pattern Matching**:
   - Complex nested destructuring scenarios
   - Error handling with pattern matching
   - Type system integration

2. **Complete Loop Optimization Pipeline**:
   - Analysis → Optimization → Code Generation
   - Fallback behavior for complex loops
   - Integration with existing VM