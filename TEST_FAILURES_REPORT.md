# Limitly VM Test Failures Report

## Overview
This report documents all test failures found when running the Limitly language test suite individually. Tests were run to identify VM implementation issues that need to be fixed.

## Test Results Summary
- **Total Tests Run**: 42
- **Passing Tests**: 26
- **Failing Tests**: 16
- **Critical Issues**: 8

---

## 🚨 Critical Failures (Compile-Time Errors)

### 7. **Range Iteration Semantics**
**File**: `tests/loops/iter_loops.lm`
**Error**: `Assertion failed: Nested iter should iterate 6 times (2x3)`
```limit
// Expected: 6 iterations (2 outer × 3 inner)
// Actual: 4 iterations (2 outer × 2 inner)
```
**VM Component**: Range Operations/Loop Execution
**Priority**: HIGH
**Impact**: Range behavior inconsistent with expectations

### 8. **Nested Loop Calculations**
**File**: `tests/loops/while_loops.lm`
**Error**: `Assertion failed: Sum of pairs should be 9`
```limit
// Expected sum: (0,0)+(0,1)+(0,2)+(1,0)+(1,1)+(1,2) = 9
// Actual sum: 6 (missing some iterations)
```
**VM Component**: Loop Execution/Variable Management
**Priority**: MEDIUM
**Impact**: Nested loop logic incorrect

---

## 🔧 Function System Failures

### 9. **Closure Return Values**
**File**: `tests/functions/closures.lm`
**Error**: All closure functions return `nil` instead of expected values
```limit
var greeting1 = sayHello("World");
// Expected: "Hello, World!"
// Actual: nil
```
**VM Component**: Closure Implementation
**Priority**: HIGH
**Impact**: Closure system completely broken

### 10. **First-Class Function Returns**
**File**: `tests/functions/first_class.lm`
**Error**: Functions returning functions return `nil`
```limit
var addFive = createAdder(5);
var result = addFive(3);
// Expected: 8
// Actual: nil
```
**VM Component**: Function Implementation
**Priority**: HIGH
**Impact**: Higher-order functions non-functional

### 11. **Function Composition**
**File**: `tests/functions/first_class.lm`
**Error**: Function composition returns wrong values
```limit
var comp1 = squareThenIncrement(4);
// Expected: 17 (4² + 1)
// Actual: 4
```
**VM Component**: Function Call Chain
**Priority**: HIGH
**Impact**: Functional programming patterns broken

---

## 📦 Module System Issues

### 12. **Module Variable Access**
**File**: `tests/modules/basic_import_test.lm`
**Error**: `Assertion failed: Module variable should be accessible`
```limit
assert(basic.moduleVar == "Hello from module");
// Expected: "Hello from module"
// Actual: nil
```
**VM Component**: Module System/Variable Resolution
**Priority**: HIGH
**Impact**: Basic module functionality broken

---

## 🚀 Concurrency System Failures

### 13. **Parallel Block Execution**
**File**: `tests/concurrency/parallel_blocks.lm`
**Error**: Parallel execution incorrect
```limit
// Expected: 100 iterations
// Actual: 99 iterations
// Expected: All results collected
// Actual: Only 32 results collected
```
**VM Component**: Parallel Execution Engine
**Priority**: HIGH
**Impact**: Concurrency completely unreliable

### 14. **Channel Communication**
**File**: `tests/concurrency/parallel_blocks.lm`
**Error**: Channel results lost/corrupted
```limit
// Expected: Sum = 59700
// Actual: Sum = 0
```
**VM Component**: Channel Implementation
**Priority**: HIGH
**Impact**: Inter-thread communication broken

---

## 🔄 Union Type Issues

### 15. **Union Return Values**
**File**: `tests/types/unions.lm`
**Error**: Union function returns `nil` for string branch
```limit
var result2: Result = processValue(-1);
// Expected: "Invalid input"
// Actual: nil
```
**VM Component**: Union Type System
**Priority**: MEDIUM
**Impact**: Type system partially broken

---

## 🧪 Large Literal Parsing

### 16. **Large Number Handling**
**File**: `tests/expressions/large_literals.lm`
**Error**: Test exits early (likely assertion failure or crash)
**VM Component**: Literal Parser/Numeric Handling
**Priority**: MEDIUM
**Impact**: Large number support uncertain

---

## 📊 Impact Assessment

### **Critical VM Components (Need Immediate Fix)**
1. **Parser** - Tuple indexing, complex expressions
2. **String Operations** - Indexing, type comparison
3. **Closure System** - Return values, variable capture
4. **Function System** - Return values, composition
5. **Parallel Execution** - Thread management, result collection
6. **Module System** - Variable resolution

### **Medium Priority Issues**
1. **Range Semantics** - Iteration behavior
2. **Type System** - Union returns, access control
3. **Loop Execution** - Nested calculations
4. **Large Literals** - Numeric parsing

---

## 🔨 Recommended Fix Order

### **Phase 1: Core Language Features**
1. Fix parser for complex boolean expressions in function calls
2. Implement tuple indexing support
3. Fix variable scope resolution in blocks
4. Implement string indexing
5. Fix string-number type comparison

### **Phase 2: Function System**
1. Fix closure return values and variable capture
2. Fix first-class function returns
3. Fix function composition
4. Fix union type returns

### **Phase 3: Advanced Features**
1. Fix range iteration semantics
2. Fix parallel execution engine
3. Fix channel communication
4. Fix module variable resolution
5. Fix large literal parsing

---

## 📝 Notes

- Some "failures" are actually correct behavior (e.g., private field access enforcement)
- Tests need to be updated to reflect correct VM behavior where appropriate
- Many failures indicate fundamental VM components are non-functional
- Priority should be given to core language features before advanced features

This report provides a roadmap for systematically fixing the Limitly VM implementation.
