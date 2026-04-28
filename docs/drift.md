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
