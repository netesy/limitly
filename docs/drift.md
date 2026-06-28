# Drift Analysis (drift.md) - Resolved

## 1. Documentation Drift (Resolved)
- **Keyword Alignment**: All occurrences of `class` have been replaced with `frame` in `learn.md` and `guide.md`.
- **Member Access**: Standardized on `this.` while acknowledging `self` support.
- **Paths**: Updated `limitly` execution paths to `./bin/limitly`.

## 2. Spec Drift (Resolved)
- **language.md**: Created formal specification.
- **stdlib.md**: Created standard library reference.

## 3. Philosophical Drift (Resolved)
- **Zen of Limit**: Updated to reflect the practical implementation of `nil` while maintaining the core "absence as state" philosophy.

## 4. Runtime Drift (Resolved)
- Verified that all documented examples in `learn.md` and `guide.md` compile and run against the current parser implementation.

## 5. Implementation Stubs
- **Frame Modifiers**: The keywords `abstract`, `final`, and `data` are recognized by the scanner and stored in the AST. However, they are currently **not enforced** by the TypeChecker or LIR generator. They remain in the language spec as they are essential for the intended object model, but users should be aware they are currently documentation-only hints.

## 6. Newly Identified Drifts (Audit 2025-05-15)

### Documentation Drift (Beginner/User Risk)
- **`match` Patterns**: Previous documentation used `Ok(v)` and `Err` patterns for fallible types (`Type?`). The actual implementation requires `val v` and `err`.
- **`loop` Keyword**: Documentation frequently used `loop` for infinite loops. The parser does not support `loop`; `while (true)` or `for (;;)` must be used.
- **`-repl` Flag**: `learn.md` mentions a REPL accessible via `limitly -repl`. This flag is not implemented in `src/main.cpp`.

### Spec Drift (Unimplemented Features)
- **Ternary Operator** (`? :`): Documented but not implemented in `Parser::call()`.
- **Elvis Operator** (`?:`): Documented but not implemented in `Parser::call()`.
- **Safe Navigation** (`?.`): Documented but not implemented in `Parser::call()`.
- **Range Steps** (`0..10..2`): Documented as planned but parser only supports `start..end`.
- **`async`/`await`**: Documented but VM runtime lacks support.
- **`comptime`**: Documented but not implemented in parser/interpreter.
- **`contract`**: Documented but not implemented in parser/interpreter.
- **`unsafe`**: Documented but not semantically enforced.

### Runtime Drift
- **Pattern Matching Hierarchy**: The parser prioritizes `val`/`err` keywords for error union patterns, while `Ok`/`Err` were treated as standard bindings, leading to silent failures or incorrect matching logic in previous doc examples.
