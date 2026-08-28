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
- **`iter` Loop Type Annotation** (RESOLVED/FLAGGED):
  - *Drift*: `learn.md` previously taught `iter (color: str in colors)`.
  - *Actual Behavior*: Parser expects `iter (color in colors)` without type annotation on loop variable.
  - *Action Taken*: Corrected syntax in `learn.md`.
- **Unparenthesized Match Expression** (RESOLVED/FLAGGED):
  - *Drift*: `learn.md` previously taught `match result { ... }`.
  - *Actual Behavior*: Parser strictly requires parentheses around the match expression: `match (result) { ... }`.
  - *Action Taken*: Updated all match expressions in `learn.md` to `match (...)`.
- **Task Argument Syntax** (RESOLVED/FLAGGED):
  - *Drift*: `learn.md` previously taught `task { ... }`.
  - *Actual Behavior*: Parser expects argument parentheses: `task() { ... }`.
  - *Action Taken*: Updated all task invocations in `learn.md` to `task()`.
- **Channel Method `recv()`** (RESOLVED/FLAGGED):
  - *Drift*: `learn.md` previously taught `ch.receive()`.
  - *Actual Behavior*: Native channel implementation uses `.recv()`.
  - *Action Taken*: Updated `learn.md` to use `.recv()`.

### 2.2 Doc Drift (User Risk) → `guide.md` Issues
- **`data frame` Syntax** (RESOLVED/FLAGGED):
  - *Drift*: `guide.md` documented `data frame User { ... }`.
  - *Actual Behavior*: `data` keyword modifier is removed/unsupported in frame declarations.
  - *Action Taken*: Marked `data frame` as removed and updated examples to standard `frame`.
- **Abstract Method Bodies** (RESOLVED/FLAGGED):
  - *Drift*: `guide.md` showed `abstract fn area(): float;` without body.
  - *Actual Behavior*: Compiler parser currently requires block bodies for frame methods.
  - *Action Taken*: Added default return bodies in `guide.md` examples.
- **Intersection Type Alias Syntax** (RESOLVED/FLAGGED):
  - *Drift*: `guide.md` showed `type Person = HasName & HasAge;`.
  - *Actual Behavior*: Parser uses `and` for intersection type alias definitions (`HasName and HasAge`).
  - *Action Taken*: Updated operator in `guide.md`.
- **Disabled Keywords Flagged (`unsafe`, `comptime`, `contract`)** (RESOLVED/FLAGGED):
  - *Drift*: `guide.md` presented `unsafe`, `comptime`, and `contract` as fully active usage patterns.
  - *Actual Behavior*: These constructs are parsed as keywords but currently disabled/unimplemented in LIR lowering.
  - *Action Taken*: Added explicit warning notices and commented out non-functional code blocks in `guide.md`.

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
