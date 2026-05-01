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

### 1. **Tuple Indexing Support**
**File**: `tests/basic/list_dict_tuple.lm`
**Error**: `Cannot index type '(String, String, String)'`
```limit
assert(fruetes[0] == "Apples", "First tuple element should be Apples");
```
**VM Component**: Parser/Type Checker
**Priority**: HIGH
**Impact**: Tuple operations completely broken

### 2. **Complex Boolean Expressions in Assert**
**File**: `tests/expressions/arithmetic.lm`
**Error**: `Expected ')' after arguments` and `Expected expression`
```limit
assert(floatSum > 5.13 && floatSum < 5.15, "message");

```
**VM Component**: Parser
**Priority**: HIGH
**Impact**: Complex boolean expressions in function calls fail (test needs fix)
**Solution**: Change the test file to use and else or not && and ||

### 3. **Variable Scope in Blocks**
**File**: `tests/types/basic.lm`
**Error**: `Undefined variable or variant: globalVar`
```limit
{
    var globalVar: GlobalType = 999;
}
assert(globalVar == 999, "Global type alias should work in local scope");
```
**VM Component**: Type Checker/Scope Resolution
**Priority**: HIGH
**Impact**: Block-scoped variables inaccessible outside blocks

### 4. **Private Field Access Enforcement**
**File**: `tests/oop/traits_inheritance.lm`
**Error**: `Cannot access private field 'id' of frame 'MyFrame'`
```limit
assert(f.id == 42, "Frame field should be initialized correctly");
```
**VM Component**: Type Checker (Access Control)
**Priority**: MEDIUM
**Impact**: Privacy enforcement working correctly (test needs fix)

---

## ⚠️ Runtime Failures (Assertion Errors)

### 5. **String Indexing Returns nil**
**File**: `tests/strings/operations.lm`
**Error**: `Assertion failed: First character should be 'L'`
```limit
assert(testStr[0] == "L", "First character should be 'L'");
// Actual: testStr[0] returns nil
```
**VM Component**: String Operations
**Priority**: HIGH
**Impact**: String indexing completely non-functional

### 6. **String-Number Type Comparison**
**File**: `tests/strings/operations.lm`
**Error**: `Assertion failed: String '42' should not equal number 42`
```limit
assert("42" != 42, "String should not equal number");
// Actual: "42" == 42 returns true
```
**VM Component**: Type System/Comparison Operations
**Priority**: HIGH
**Impact**: Type safety compromised

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
