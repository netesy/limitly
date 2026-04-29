# Limitly Language - AI Agent Guidelines

This document provides essential guidelines for AI agents working with the Limitly language. It highlights the current state of the compiler (Parser vs. TypeChecker vs. Backend) to avoid using features that are "syntax-only".

## 📊 **Semantic Implementation Status**

| Feature | Parser | TypeChecker | Backend (VM/AOT) | Notes |
| :--- | :---: | :---: | :---: | :--- |
| **Basic Types (int, float, str, bool)** | ✅ | ✅ | ✅ | Fully supported. |
| **Type Aliases** | ✅ | ✅ | ✅ | Basic aliases work. |
| **Union Types (`int \| str`)** | ✅ | ✅ | ⚠️ | Checked, but runtime behavior for complex unions may vary. |
| **Optional Types (`T?`)** | ✅ | ✅ | ✅ | Implemented as ErrorUnions internally. |
| **Lists (`[T]`)** | ✅ | ⚠️ | ✅ | TypeChecker often falls back to `any` for empty or nested lists. |
| **Dicts (`{K: V}`)** | ✅ | ⚠️ | ✅ | Similar to Lists, type inference is incomplete. |
| **Frames (Classes)** | ✅ | ✅ | ✅ | Basic methods and fields work. |
| **Traits (Interfaces)** | ✅ | ✅ | ⚠️ | Dynamic dispatch is partially implemented. |
| **Closures / Lambdas** | ✅ | ⚠️ | ⚠️ | Parsed and basic check, but capture logic is fragile. |
| **Channels / Concurrency** | ✅ | ⚠️ | ✅ | Runtime works, but TypeChecker lacks deep channel type validation. |
| **Match Statements** | ✅ | ✅ | ⚠️ | Exhaustiveness checking exists but is not exhaustive for all types. |
| **Structural Types (`{f: T}`)** | ✅ | ⚠️ | ❌ | Parsed, but literal instantiation and field access are incomplete. |

## 🚫 **STRICTLY AVOID (Syntax-only or Unimplemented)**

The following are present in the parser but **NOT** semantically implemented or checked. Using them will likely cause silent failures or crashes:

- ❌ **`break` / `continue`**: Parsed but ignored by the TypeChecker and VM.
- ❌ **`unsafe { ... }`**: Parsed but has no effect.
- ❌ **`comptime { ... }`**: Parsed but not executed at compile time.
- ❌ **Object Literals**: `{ name: "val" }` (structural literals) are not yet supported.
- ❌ **Interface Declarations**: Use `trait` instead; `interface` is parsed but stashed.
- ❌ **Generics**: `fn func<T>(...)` - Completely unsupported (syntax error or ignored).
- ❌ **Async/Await**: `async fn` and `await` are not yet functional.

## ⚠️ **KNOWN TYPECHECKER ISSUES**

- **`ANY_TYPE` Fallbacks**: The TypeChecker frequently defaults to `any` when it cannot resolve a type (e.g., in complex lambdas, worker parameters, or empty collections). This bypasses safety.
- **Linear Types**: The linear type system (move semantics) is implemented but should be used with caution as it's still being refined.
- **Reference Invalidation**: Manual generation-based reference tracking is experimental.
- **Incomplete Exhaustiveness**: Match statements on custom unions might miss some edge cases.

## ✅ **SAFE TO USE (Recommended)**

- **Variable Declarations**: `var x: int = 10`
- **Functions**: `fn add(a: int, b: int): int { return a + b }`
- **Control Flow**: `if/else`, `while`, `for`, `iter`
- **Error Unions**: `fn work(): int!Error { ... }` and `?` operator.
- **Frames/Traits**: Basic object-oriented patterns.
- **Concurrency**: `concurrent { ... }`, `task(i in range) { ... }`, and channels.

## 📝 **Code Examples**

### **Correct Usage**
```limit
// Concrete types and basic flow
fn process(val: int): int {
    if (val > 0) {
        return val * 2
    }
    return 0
}

// Error handling
fn fallible(): int! {
    return err("Failure")
}

var x = fallible() ? else { return 0 }
```

### **Incorrect Usage - DO NOT DO THIS**
```limit
// ❌ NO OBJECT LITERALS
var p = { name: "Alice", age: 30 }; // Parsed but will fail semantically

// ❌ NO BREAK/CONTINUE
while (true) {
    if (done) break; // Parser accepts, but it won't actually break the loop
}

// ❌ NO GENERICS
fn identity<T>(x: T): T { return x }
```

## 🎯 **Key Principles**

1. **Explicit Types**: Avoid relying on inference for complex structures; the TypeChecker may default to `any`.
2. **Avoid Structural Literals**: Use `frame` and `FrameName()` instead.
3. **Trait Dispatch**: Keep trait hierarchies simple.
4. **Check `run_tests.sh`**: Always verify your logic against the tests in the `tests/` directory.

---
*Updated based on analysis of `src/frontend/type_checker.cpp` and `src/frontend/ast.hh`.*

## 🚨 **CRITICAL: Test Suite Reliability**

- **False Positives**: The `./tests/run_tests.sh` script may report **PASS** even if the compiler binary (`./bin/limitly`) is missing or failing to execute. It only marks a failure if it specifically finds "Error" or "RuntimeError" in the output.
- **Build Failures**: Currently, the project may have build issues due to missing dependencies (e.g., `fyra` IR headers). Always verify that `./bin/limitly` exists and is functional before trusting test results.
- **Skipped Tests**: Over 100 tests in the `tests/` directory are currently **NOT** included in the automated test suite. Many of these contain the "rigorous" or "error" cases that would reveal the TypeChecker's current limitations.
