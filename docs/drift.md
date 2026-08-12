# Limit Language Drift Analysis (Extended Audit)

This document tracks "Spec Drift" (unimplemented features), "Doc Drift" (inconsistent documentation), "Philosophical Drift", and "Runtime Drift" across the entire Limitly system.

---

## 🚨 1. Spec Drift (language.md Mismatch)
Features defined in `language.md` (the formal spec) but are either unimplemented or only partially implemented in the compiler/parser.

| Feature | Spec Definition | Actual Implementation Status | Severity |
| :--- | :--- | :--- | :--- |
| **Ternary Operator (`? :`)** | `condition ? thenExpr : elseExpr` | Unimplemented in the LIR generator (triggers "not yet implemented" error). | **MEDIUM** |
| **Elvis Operator (`?:`)** | Coalescing operator | Unimplemented in parser and LIR generator. | **MEDIUM** |
| **Safe Access (`?.`)** | Optional member access | Unimplemented in parser and LIR generator. | **MEDIUM** |
| **Range Steps (`0..10..2`)** | `start..end..step` syntax | Unimplemented in the parser/generator. Range expressions only support `start..end`. | **LOW** |
| **Async/Await** | `async fn` / `await` expressions | Reserved keywords; currently unimplemented at parser/LIR generator level. | **HIGH** |
| **Contract Statements** | `contract(cond, msg)` | Keyword is reserved but unsupported as a language-level compiler check. | **MEDIUM** |
| **Compile-Time Execution (`comptime`)** | `comptime { block }` | Keyword is reserved but actual compile-time macro execution is unimplemented. | **MEDIUM** |
| **Unsafe Blocks** | `unsafe { block }` | Keyword is reserved but block semantics are parsed as normal block statements without isolation. | **MEDIUM** |
| **Frame Modifiers (`abstract`, `final`, `data`)** | Restricting frame instantiation/extension | Keywords parsed, but restrictions are not enforced by the TypeChecker. | **MEDIUM** |

---

## ⚠️ 2. Doc Drift (Beginner & User Risks)
Inconsistencies between teaching materials (`learn.md`, `guide.md`) and the actual compiler syntax/VM rules.

### 2.1 Doc Drift (Beginner Risk) → `learn.md` Issues
- **Ok/Err Pattern Matching Mismatch** (RESOLVED/FLAGGED):
  - *Drift*: `learn.md` previously taught `Ok(value) => ...` and `Err => ...` patterns for matching on the native fallible type `Type?`.
  - *Actual Behavior*: The TypeChecker and Register VM expect `val value => ...` (success pattern) and `err => ...` or `err e => ...` (error pattern).
  - *Action Taken*: Standardized on `val` and `err` matching in `learn.md`.
- **Frame Field Declaration with `var`** (RESOLVED/FLAGGED):
  - *Drift*: `learn.md` previously taught `pub var name: str = "World";` inside a frame.
  - *Actual Behavior*: The compiler expects frame fields to be declared without the `var` keyword (e.g., `pub name: str = "World";`).
  - *Action Taken*: Standardized field declarations across `learn.md` to match actual compiler rules.
- **Usage of `this` Keyword** (RESOLVED):
  - *Drift*: Taught using `this` instead of `self` for frame receivers.
  - *Actual Behavior*: The compiler only recognizes `self`. `this` is unsupported.
  - *Action Taken*: Standardized entirely on `self`.
- **`-repl` flag** (RESOLVED):
  - *Drift*: Documented `-repl` flag to start REPL.
  - *Actual Behavior*: Executing `./bin/limitly` with no arguments automatically starts the REPL.

### 2.2 Doc Drift (User Risk) → `guide.md` Issues
- **Uppercase Ok/Err Constructors** (RESOLVED/FLAGGED):
  - *Drift*: `guide.md` used uppercase `Ok(...)` and `Err(...)` as constructors for the native `Type?` system (e.g. `return Ok(a / b);`).
  - *Actual Behavior*: The native unified error system uses lowercase constructors `ok(...)` and `err(...)` or `err(Type)`. Uppercase variants are only used as standard library wrappers in `std.result`.
  - *Action Taken*: Corrected all native fallible examples in `guide.md` to use lowercase `ok` and `err`.
- **Usage of `class` Keyword** (RESOLVED):
  - *Drift*: Explanations in `guide.md` referred to `class` instead of `frame`.
  - *Actual Behavior*: `frame` is the exclusive keyword for object-oriented structures in Limitly.
  - *Action Taken*: Completely standardized on `frame`.

---

## 🚨 3. Philosophical Drift (zen.md Issues)
Principles declared in the language philosophy contract (`zen.md`) versus actual compiler/runtime enforcement.

| Principle | Enforcement Mechanism | Status | Evidence / Notes |
| :--- | :--- | :--- | :--- |
| **"Explicit is better than implicit"** | Strict compatibility checking in `TypeChecker::is_type_compatible`. No implicit conversion allowed between float and decimal types. | **ENFORCED** | `src/frontend/type_checker/types.cpp:258` returns `false` for mismatched types, requiring explicit `as` casts. |
| **"Errors are not exceptions; they are values to be handled"** | The native fallible `Type?` unified system. `TypeChecker::is_exhaustive_error_match` enforces exhaustive error pattern coverage. | **ENFORCED** | `src/frontend/type_checker/types.cpp:822` validates that match statements over fallible types cover both values and errors. |
| **"Concurrency should be structured, not chaotic"** | Scope-bound `parallel` and `concurrent` block statements in the parser and LIR generator. | **ENFORCED** | `src/frontend/parser/statements.cpp` parses structured scopes and binds execution of tasks/workers to their lexical scope lifetimes. |
| **"Safety should not be a sacrifice for performance"** | Region-based memory safety tracker. | **ENFORCED** | `src/frontend/memory_checker.cpp` manages and tracks scopes for region-based automatic memory allocation and deterministic destruction. |
| **"The absence of a value is a state to be handled explicitly, not a source of crashes"** | Compile-time optional type validation (`is_optional_type`). | **ENFORCED** | Checked in `TypeChecker::is_optional_type` to guarantee explicit unwrap checks before accessing underlying values. |

---

## 🚨 4. Runtime Drift (Code vs Tests Mismatch)
Discrepancies where code implementation differs from expectations in testing files or VM execution.

- **`pop()` on primitive lists**:
  - *Drift*: `.pop()` is standard across collections, but the native LIR Generator does not natively lower `.pop()` on primitive lists.
  - *Tested behavior*: Standard pure code uses copy loops to manually pop elements from primitive lists rather than calling a native method.
- **In-place Field Mutation of collections**:
  - *Drift*: Modifying collections inside frame fields directly (e.g. `self.data[key] = value`) doesn't write back to the reference in the frame unless accompanied by explicit re-assignment (e.g. `self.data = d`).
  - *Tested behavior*: The VM enforces this mutation design pattern where field collections must be reassigned explicitly to persist updates.
