# Documentation Traceability & Verification Matrix

This document tracks the consistency between learning materials, usage guides, the formal language specification, compiler source code, and the test suite.

---

## 📊 1. Concept Traceability Matrix

| Concept | learn.md | guide.md | language.md | Tests | Status |
| :--- | :---: | :---: | :---: | :--- | :---: |
| **Variables (`var`)** | ✅ | ✅ | ✅ | `tests/basic/variables.lm` | ✅ |
| **Constants (`val`/`const`)** | ✅ | ✅ | ✅ | `tests/basic/variables.lm` | ✅ |
| **Integers (`int`/`i32`/etc)** | ✅ | ✅ | ✅ | `tests/types/basic.lm` | ✅ |
| **Decimals (`d2`/`d4`/`d6`)** | ✅ | ✅ | ✅ | `tests/decimal_tests.lm` | ✅ |
| **Frames (`frame`)** | ✅ | ✅ | ✅ | `tests/oop/frame_declaration.lm` | ✅ |
| **Self Reference (`self`)** | ✅ | ✅ | ✅ | `tests/oop/frame_declaration.lm` | ✅ |
| **Traits (`trait`)** | ✅ | ✅ | ✅ | `tests/oop/traits_dynamic.lm` | ✅ |
| **Modules (`import`)** | ✅ | ✅ | ✅ | `tests/modules/*` | ✅ |
| **Fallible (`Type?`)** | ✅ | ✅ | ✅ | `tests/error_handling/unified_type_system.lm` | ✅ |
| **Structured Concurrency** | ✅ | ✅ | ✅ | `tests/concurrency/*` | ✅ |
| **Pattern Match (`match`)** | ✅ | ✅ | ✅ | `tests/loops/match.lm` | ✅ |
| **Ternary (`? :`)** | ❌ | ⚠️ (Planned) | ⚠️ (Planned) | ❌ | 🚨 (Spec Drift) |
| **Safe Access (`?.`)** | ❌ | ❌ | ⚠️ (Planned) | ❌ | 🚨 (Spec Drift) |
| **Elvis (`?:`)** | ❌ | ❌ | ⚠️ (Planned) | ❌ | 🚨 (Spec Drift) |

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
- **Ok/Err Constructors**: Prior documentation taught uppercase `Ok(value)` and `Err(error)` constructs for native `Type?` return values. In reality, the compiler and TypeChecker expect lowercase `ok(value)` and `err()` (with uppercase variants reserved for stdlib wrappers in `std.result`). *[RESOLVED]*
- **Frame Field `var` Keyword**: Prior onboarding code blocks taught frame field declarations as `pub var name: str`, whereas the compiler syntax parser disallows the `var` keyword inside frame field declarations (which must be `pub name: str`). *[RESOLVED]*

### 2.3 Doc ↔ Test Mismatches
- **`this` Receiver**: Previous documentation mentioned `this` as a valid frame receiver. However, all test files (such as `tests/oop/frame_declaration.lm`) and compiler AST parsing strictly require `self` as the canonical receiver. *[RESOLVED]*
- **`-repl` Command Line Flag**: Documentation mentioned a `-repl` flag. The actual CLI driver simply defaults to the REPL when run without arguments, and the flag is not natively supported. *[RESOLVED]*

### 2.4 Philosophy Violations
- **No Implicit Coercion**: Any implicit conversion of float to decimal types or comparisons with mismatched decimal scales throws strict compile-time type-check errors to satisfy the *"Explicit is better than implicit"* principles in `zen.md`. No violations were found in implementation files.

### 2.5 Teaching Inconsistencies
- **Upper-case constructors for native types**: Solved by documenting the distinction between standard library wrappers in `std.result` (uppercase `Ok`/`Err` structs) and native compiler fallible primitives (lowercase `ok`/`err` constructors).

---

## 🏁 3. Final Integrity Check

### Is the language teachable without misleading users?
**YES**. All outdated syntax guides, incorrect uppercase error constructor claims, invalid receiver keywords (`this`), and invalid frame field modifiers have been systematically resolved and corrected across `learn.md` and `guide.md`.

### Is the documentation system internally consistent?
**YES**. The spec `language.md`, the developer guide `guide.md`, and the onboarding resource `learn.md` are completely synchronized on keyword usage (`frame`, `self`), optional/fallible semantics (`Type?`, `ok()`, `err()`), and pattern matching syntax (`val x`, `err e`). All planned or unimplemented features are clearly flagged with `(Planned)`.

### Is the philosophy actually enforced?
**YES**. Philosophical principles defined in `zen.md` (Explicit over Implicit, Errors as Values, Structured Concurrency, Region Safety, Explicit Null Handling) map directly to active, checked compiler subsystems within `src/frontend/type_checker/` and `src/frontend/memory_checker.cpp`. No drift exists between philosophy and code.
