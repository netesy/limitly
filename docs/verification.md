# Documentation Traceability & Verification Matrix

This document tracks traceability and consistency between learning materials (`learn.md`), usage guides (`guide.md`), formal specifications (`language.md`), implementation code, and the test suite.

---

## 1. Concept Traceability Matrix

| Concept | learn.md | guide.md | language.md | Tests | Status |
| :--- | :---: | :---: | :---: | :--- | :---: |
| **Variables (`var`)** | [x] | [x] | [x] | `tests/basic/variables.lm` | ✅ Fully consistent |
| **Constants (`val`/`const`)** | [x] | [x] | [x] | `tests/basic/variables.lm` | ✅ Fully consistent |
| **Integers (`int`/`i32`/etc)** | [x] | [x] | [x] | `tests/types/basic.lm` | ✅ Fully consistent |
| **Decimals (`d2`/`d4`/`d6`)** | [x] | [x] | [x] | `tests/decimal_tests.lm` | ✅ Fully consistent |
| **Frames (`frame`)** | [x] | [x] | [x] | `tests/oop/frame_declaration.lm` | ✅ Fully consistent |
| **Self Reference (`self`)** | [x] | [x] | [x] | `tests/oop/frame_declaration.lm` | ✅ Fully consistent |
| **Traits (`trait`)** | [x] | [x] | [x] | `tests/oop/traits_dynamic.lm` | ✅ Fully consistent |
| **Modules (`import`)** | [x] | [x] | [x] | `tests/modules/*` | ✅ Fully consistent |
| **Fallible (`Type?`)** | [x] | [x] | [x] | `tests/stdlib/core/option_result_test.lm` | ✅ Fully consistent |
| **Structured Concurrency** | [x] | [x] | [x] | `tests/concurrency/*` | ✅ Fully consistent |
| **Pattern Match (`match`)** | [x] | [x] | [x] | `tests/loops/match.lm` | ✅ Fully consistent |
| **Safe Access (`?.`)** | [x] | [x] | [x] | `tests/types/options.lm` | ✅ Fully consistent |
| **Range Steps (`0..10..2`)** | [x] | [x] | [x] | `tests/expressions/ranges.lm` | ✅ Fully consistent |

---

## 2. Verification Addendum

### 2.1 Documentation Coverage Gaps
- **Safe Access Operator (`?.`)**: Implemented and verified in AST, Parser, TypeChecker, LIR Generator, and `tests/types/options.lm`.
- **Range Step Iteration (`0..10..2`)**: Implemented and verified in Parser, TypeChecker, LIR Generator, and `tests/expressions/ranges.lm`.

### 2.2 Doc ↔ Code Mismatches
- **Task Argument Syntax**: `learn.md` previously omitted required parentheses for `task()` statements. Corrected to `task()` across onboarding materials.
- **Channel Method Names**: `learn.md` referenced `ch.receive()`, whereas the compiler type checker exclusively recognizes `ch.recv()`. Corrected in `learn.md`.
- **Concurrent Scope Binding**: `learn.md` omitted channel parameters in `concurrent` block headers. Corrected to `concurrent(ch = ch)`.
- **Tuple Indexing Syntax**: `guide.md` taught dot-indexing (`tuple.0`). The compiler AST expects array-style indexing (`tuple[0]`). Corrected in `guide.md`.
- **Enum Constructor Qualification**: `guide.md` used bare variant constructors. Corrected to fully qualified variant names (`Option.Some(...)`).

### 2.3 Doc ↔ Test Mismatches
- **`this` Keyword**: Previous docs referred to `this` as a frame receiver. All tests (`tests/oop/*`) and parser rules strictly enforce `self`.
- **`-repl` CLI Flag**: Previous docs referred to `-repl`. Running the binary without subcommands launches the REPL natively.

### 2.4 Philosophy Violations
- **No Implicit Coercion**: Compile-time type checking enforces strict typing with explicit `as` casts required for float and decimal type coercions.
- **Structured Scope Lifetimes**: Parser and LIR generator enforce that all parallel and concurrent tasks are lexical scope-bound.

### 2.5 Teaching Inconsistencies
- **Native Fallible Constructors vs Stdlib Wrappers**: Clear distinction established between native compiler `Type?` constructors (`ok()`, `err()`) and standard library wrapper structs in `std.result` (`Ok`, `Err`).

---

## 3. Proof Policies & Verification Modes

Lymar supports two proof policies without changing source syntax:

- `--verify=hybrid` (default) erases proven contracts and retains runtime assertions for obligations outside the native solver fragment.
- `--verify=strict` rejects every contract or refinement obligation that is false, unsupported, or unknown. Strict builds therefore contain no dynamic fallback for required verification conditions.

The native verifier preserves boolean `and`, `or`, and `not` structure and uses exact linear-integer reasoning for arithmetic leaves. Counterexamples are compile errors in both modes.

---

## 4. Final Integrity Check

- **Is the language teachable without misleading users?** **YES**
  - All examples in `learn.md` and `guide.md` compile and pass.
- **Is the documentation system internally consistent?** **YES**
  - Hierarchy of truth is maintained across tests, source code, `language.md`, `stdlib.md`, `guide.md`, `learn.md`, and `zen.md`.
- **Is the philosophy actually enforced?** **YES**
  - All 17 principles in `zen.md` are mapped directly to concrete compiler source files and test suites.
