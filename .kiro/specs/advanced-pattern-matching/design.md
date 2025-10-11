# Design Document

## Overview

This design extends the existing match statement implementation in the Limit programming language to support advanced pattern matching features. The current implementation supports basic literal patterns, type patterns, and default patterns. This enhancement adds destructuring patterns, Result type patterns, proper variable binding with scoping, enhanced string interpolation in match contexts, and improved guard patterns.

The design builds upon the existing AST structures, bytecode generation, and VM execution model while adding new pattern types, variable binding mechanisms, and scope management for pattern-matched variables.

## Architecture

### Current Match System Architecture

The existing match system consists of:
- **Frontend**: Parser creates `MatchStatement` AST nodes with `MatchCase` children
- **Backend**: Bytecode generator creates `MATCH_PATTERN`, `JUMP_IF_FALSE`, and scope management instructions
- **VM**: Executes pattern matching with temporary variable storage and jump logic

### Enhanced Architecture Components

1. **Pattern AST Nodes**: Extended pattern hierarchy for destructuring and Result patterns
2. **Variable Binding System**: Scope management for pattern-bound variables
3. **Result Type System**: Support for `val()`/`err()` constructors and patterns
4. **Enhanced String Interpolation**: Improved variable resolution in match contexts
5. **Guard Pattern Evaluation**: Proper variable scoping for `where` clauses

## Components and Interfaces

### 1. Enhanced Pattern AST Nodes

```cpp
// Base pattern class (existing)
class Pattern : public ASTNode {
public:
    virtual ~Pattern() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};

// New destructuring patterns
class ListDestructurePattern : public Pattern {
    std::vector<std::string> variables;
    size_t expectedSize;
public:
    ListDestructurePattern(std::vector<std::string> vars) : variables(vars), expectedSize(vars.size()) {}
    void accept(ASTVisitor& visitor) override;
};

class TupleDestructurePattern : public Pattern {
    std::vector<std::string> variables;
public:
    TupleDestructurePattern(std::vector<std::string> vars) : variables(vars) {}
    void accept(ASTVisitor& visitor) override;
};

// Result type patterns
class ValPattern : public Pattern {
    std::string variable;
public:
    ValPattern(std::string var) : variable(var) {}
    void accept(ASTVisitor& visitor) override;
};

class ErrPattern : public Pattern {
    std::string variable;
public:
    ErrPattern(std::string var) : variable(var) {}
    void accept(ASTVisitor& visitor) override;
};

// Enhanced variable pattern with binding
class VariablePattern : public Pattern {
    std::string variable;
    std::unique_ptr<Expression> guard; // for where clauses
public:
    VariablePattern(std::string var, std::unique_ptr<Expression> g = nullptr) 
        : variable(var), guard(std::move(g)) {}
    void accept(ASTVisitor& visitor) override;
};
```

### 2. Result Type System

```cpp
// Result type representation
class ResultType : public Type {
    std::unique_ptr<Type> valueType;
    std::unique_ptr<Type> errorType;
public:
    ResultType(std::unique_ptr<Type> val, std::unique_ptr<Type> err) 
        : valueType(std::move(val)), errorType(std::move(err)) {}
};

// Result value constructors
class ValExpression : public Expression {
    std::unique_ptr<Expression> value;
public:
    ValExpression(std::unique_ptr<Expression> val) : value(std::move(val)) {}
    void accept(ASTVisitor& visitor) override;
};

class ErrExpression : public Expression {
    std::unique_ptr<Expression> error;
public:
    ErrExpression(std::unique_ptr<Expression> err) : error(std::move(err)) {}
    void accept(ASTVisitor& visitor) override;
};
```

### 3. Enhanced Variable Binding System

```cpp
// Pattern variable binding context
class PatternBindingContext {
    std::unordered_map<std::string, Value> bindings;
    std::unique_ptr<PatternBindingContext> parent;
public:
    void bindVariable(const std::string& name, const Value& value);
    Value getVariable(const std::string& name);
    bool hasVariable(const std::string& name);
    void enterScope();
    void exitScope();
};

// Enhanced match case with binding context
class MatchCase {
    std::unique_ptr<Pattern> pattern;
    std::unique_ptr<Statement> body;
    PatternBindingContext bindingContext;
public:
    bool matchesValue(const Value& value, PatternBindingContext& context);
    void executeBody(VM& vm);
};
```

### 4. Enhanced Bytecode Instructions

```cpp
// New bytecode instructions for advanced patterns
enum class OpCode {
    // Existing instructions...
    
    // Destructuring patterns
    DESTRUCTURE_LIST,      // Pop list, push elements, bind to variables
    DESTRUCTURE_TUPLE,     // Pop tuple, push elements, bind to variables
    CHECK_LIST_SIZE,       // Verify list has expected number of elements
    
    // Result type patterns
    MATCH_VAL_PATTERN,     // Match val() pattern and bind variable
    MATCH_ERR_PATTERN,     // Match err() pattern and bind variable
    CREATE_VAL,            // Create val(value) Result
    CREATE_ERR,            // Create err(error) Result
    
    // Variable binding
    BIND_PATTERN_VAR,      // Bind pattern variable in current scope
    ENTER_PATTERN_SCOPE,   // Enter pattern matching scope
    EXIT_PATTERN_SCOPE,    // Exit pattern matching scope
    
    // Guard evaluation
    EVALUATE_GUARD,        // Evaluate guard condition with bound variables
};
```

## Data Models

### 1. Pattern Matching Value Types

```cpp
// Enhanced Value type with Result support
class Value {
public:
    enum class Type {
        // Existing types...
        RESULT_VAL,
        RESULT_ERR
    };
    
    struct ResultValue {
        Value value;
        bool isError;
    };
    
    std::variant<int, double, std::string, bool, std::vector<Value>, 
                 std::unordered_map<std::string, Value>, ResultValue> data;
};
```

### 2. Pattern Binding Scope

```cpp
// Scope management for pattern variables
class PatternScope {
    std::unordered_map<std::string, Value> variables;
    std::unique_ptr<PatternScope> parent;
    
public:
    void bind(const std::string& name, const Value& value);
    Value resolve(const std::string& name);
    bool exists(const std::string& name);
    void enterNestedScope();
    void exitNestedScope();
};
```

## Error Handling

### 1. Pattern Matching Errors

- **DestructuringError**: When destructuring patterns don't match value structure
- **ResultPatternError**: When val()/err() patterns are used on non-Result values
- **VariableBindingError**: When pattern variables conflict or are improperly scoped
- **GuardEvaluationError**: When guard conditions fail to evaluate

### 2. Compile-Time Validation

- Validate destructuring pattern arity against known types
- Ensure Result type patterns are used with Result values
- Check variable binding conflicts within patterns
- Validate guard expression types and variable access

### 3. Runtime Error Recovery

- Graceful failure when patterns don't match
- Clear error messages for pattern matching failures
- Proper cleanup of pattern binding scopes on errors

## Testing Strategy

### 1. Unit Tests for Pattern Types

- Test each new pattern type (ListDestructure, TupleDestructure, Val, Err, Variable)
- Verify AST construction and visitor pattern implementation
- Test pattern matching logic in isolation

### 2. Integration Tests for Match Statements

- Test complete match statements with new pattern types
- Verify bytecode generation for enhanced patterns
- Test VM execution of advanced pattern matching

### 3. Variable Binding Tests

- Test variable scoping in pattern contexts
- Verify proper binding and resolution of pattern variables
- Test guard pattern variable access

### 4. Result Type Tests

- Test Result type construction with val()/err()
- Verify Result pattern matching
- Test function return type parsing for Result types

### 5. String Interpolation Tests

- Test string interpolation with pattern-bound variables
- Verify complex expression evaluation in match contexts
- Test error handling for interpolation failures

### 6. Error Handling Tests

- Test pattern matching failures and error reporting
- Verify proper scope cleanup on errors
- Test compile-time validation of pattern usage

### 7. Performance Tests

- Benchmark pattern matching performance with new features
- Test memory usage of pattern binding contexts
- Verify no performance regression in basic pattern matching