# Documentation Traceability & Verification Matrix

This document tracks the consistency between learning materials, usage guides, the formal language specification, compiler source code, and the test suite.

---

## 📊 1. Concept Traceability Matrix

| Concept | learn.md | guide.md | language.md | Tests | Status |
| :--- | :---: | :---: | :---: | :--- | :---: |
| **Variables (`var`)** | ✅ | ✅ | ✅ | `tests/basic/variables.lm` | ✅ Fully consistent |
| **Constants (`val`/`const`)** | ✅ | ✅ | ✅ | `tests/basic/variables.lm` | ✅ Fully consistent |
| **Integers (`int`/`i32`/etc)** | ✅ | ✅ | ✅ | `tests/types/basic.lm` | ✅ Fully consistent |
| **Decimals (`d2`/`d4`/`d6`)** | ✅ | ✅ | ✅ | `tests/decimal_tests.lm` | ✅ Fully consistent |
| **Frames (`frame`)** | ✅ | ✅ | ✅ | `tests/oop/frame_declaration.lm` | ✅ Fully consistent |
| **Self Reference (`self`)** | ✅ | ✅ | ✅ | `tests/oop/frame_declaration.lm` | ✅ Fully consistent |
| **Traits (`trait`)** | ✅ | ✅ | ✅ | `tests/oop/traits_dynamic.lm` | ✅ Fully consistent |
| **Modules (`import`)** | ✅ | ✅ | ✅ | `tests/modules/*` | ✅ Fully consistent |
| **Fallible (`Type?`)** | ✅ | ✅ | ✅ | `tests/error_handling/unified_type_system.lm` | ✅ Fully consistent |
| **Structured Concurrency** | ✅ | ✅ | ✅ | `tests/concurrency/*` | ✅ Fully consistent |
| **Pattern Match (`match`)** | ✅ | ✅ | ✅ | `tests/loops/match.lm` | ✅ Fully consistent |
| **Unsafe Blocks (`unsafe`)** | ❌ | ⚠️ (Disabled) | ⚠️ (Disabled) | ❌ | 🚨 Spec Drift (Disabled) |
| **Contract Stmts (`contract`)**| ❌ | ⚠️ (Planned) | ⚠️ (Planned) | ❌ | 🚨 Spec Drift (Unimplemented) |
| **Comptime (`comptime`)** | ❌ | ⚠️ (Disabled) | ⚠️ (Disabled) | ❌ | 🚨 Spec Drift (Disabled) |
| **Ternary (`? :`)** | ❌ | ⚠️ (Planned) | ⚠️ (Planned) | ❌ | 🚨 Spec Drift (Planned) |
| **Safe Access (`?.`)** | ❌ | ❌ | ⚠️ (Planned) | ❌ | 🚨 Spec Drift (Planned) |
| **Elvis (`?:`)** | ❌ | ❌ | ⚠️ (Planned) | ❌ | 🚨 Spec Drift (Planned) |

**Statuses:**
- ✅ **Fully consistent**: Concept is fully documented, correctly taught, and covered by passing tests.
- ⚠️ **Partial/missing links**: Concept is documented and tested, but omitted from some learning/introductory guides due to advanced scope (e.g. traits, concurrency).
- 🚨 **Contradiction / Spec Drift**: Feature is mentioned in specifications/guides but is unimplemented in code/untested.

---

## 🚨 2. Surfaced Violations & Gaps

### 2.1 Documentation Coverage Gaps
- **Traits/Interfaces in Onboarding**: `learn.md` does not introduce `trait` or polymorphic composition, focusing purely on basic frames. *[RESOLVED]*
- **Structured Concurrency in Onboarding**: `learn.md` lacks a dedicated introduction to structured concurrency blocks (`parallel`/`concurrent`), leaving a gap for beginner systems-level learners. *[RESOLVED]*

### 2.2 Doc ↔ Code Mismatches
- **`iter` Loop Syntax**: `learn.md` previously taught `iter (color: str in colors)`. Fixed to `iter (color in colors)` to match parser rules. *[RESOLVED]*
- **Match Expression Syntax**: `learn.md` previously taught `match result { ... }`. Fixed to `match (result) { ... }` requiring parentheses. *[RESOLVED]*
- **Task Invocation Syntax**: `learn.md` previously taught `task { ... }`. Fixed to `task() { ... }` matching parser expectation. *[RESOLVED]*
- **Channel Method**: `learn.md` taught `ch.receive()`. Fixed to `ch.recv()`. *[RESOLVED]*

### 2.3 Doc ↔ Test Mismatches
- **`data frame` Syntax**: `guide.md` taught `data frame User { ... }`. Marked as removed/deprecated in alignment with parser AST rules. *[RESOLVED]*
- **Disabled Keywords in Usage Examples**: `guide.md` presented `unsafe`, `comptime`, and `contract` as fully usable code. Added explicit warning notices and disabled non-functional examples. *[RESOLVED]*

### 2.4 Philosophy Violations
- **No Implicit Coercion**: Any implicit conversion of float to decimal types or comparisons with mismatched decimal scales throws strict compile-time type-check errors to satisfy the *"Explicit is better than implicit"* principles in `zen.md`. Verified against `src/frontend/type_checker/types.cpp:258`.

### 2.5 Teaching Inconsistencies
- **Upper-case constructors for native types**: Solved by documenting the distinction between standard library wrappers in `std.result` (uppercase `Ok`/`Err` structs) and native compiler fallible primitives (lowercase `ok`/`err` constructors).

---

## 🏁 3. Final Integrity Check

### Is the language teachable without misleading users?
**YES**. Every code block in `learn.md` and `guide.md` has been audited and validated against the Limitly compiler binary (`./bin/limitly`). All non-compiling examples, invalid type annotations, unparenthesized expressions, and disabled keywords have been fixed or explicitly flagged.

### Is the documentation system internally consistent?
**YES**. The formal spec (`language.md`), practical guide (`guide.md`), onboarding material (`learn.md`), philosophy contract (`zen.md`), and drift audit (`drift.md`) are completely synchronized with the codebase and test suite.

### Is the philosophy actually enforced?
**YES**. Design principles in `zen.md` directly map to active compiler checks in `src/frontend/type_checker/`, `src/frontend/memory_checker.cpp`, and test cases under `tests/`.

### Ranking of Unimplemented / Disabled Features (Spec Drift)
1. **Disabled Features (`unsafe`, `comptime`)**: Keywords are reserved and parsed, but LIR lowering disabled pending memory boundary validation.
2. **Planned Control Flow Constructs (`contract(...)`, ternary `? :`, Elvis `?:`, Safe member access `?.`)**: Keywords reserved but lowerings remain unimplemented.
