# Documentation Traceability & Verification Report

## 1. Traceability Matrix

| Concept | learn.md | guide.md | language.md | Tests | Implementation | Status |
|---------|----------|----------|-------------|-------|----------------|--------|
| Variables (`var`) | ✅ | ✅ | ❌ (Missing) | `tests/basic/variables.lm` | `src/frontend/parser/statements.cpp` | ⚠️ Partial |
| Frame Declarations | ❌ (Uses `class`) | ✅ (Mentions `frame`) | ❌ (Missing) | `tests/oop/frame_declaration.lm` | `src/frontend/parser/statements.cpp` | 🚨 Contradiction |
| Class Declarations | ✅ | ✅ | ❌ (Missing) | ❌ (None) | ❌ (Not in parser) | 🚨 Spec Drift |
| `self` vs `this` | ✅ (Uses both) | ✅ (Uses both) | ❌ (Missing) | `tests/oop/frame_declaration.lm` (uses `this`) | `src/frontend/parser/expressions.cpp` | ✅ Consistent (both supported) |
| Optional/Error System | ✅ | ✅ | ❌ (Missing) | `tests/types/options.lm` | `src/frontend/parser/expressions.cpp` | ✅ Consistent |
| `ok()` / `err()` | ✅ | ✅ | ❌ (Missing) | `tests/types/options.lm` | `src/frontend/parser/expressions.cpp` | ✅ Consistent |
| `nil` literal | ✅ | ✅ | ❌ (Missing) | `tests/basic/literals.lm` | `src/frontend/parser/expressions.cpp` | ✅ Consistent |
| Structured Concurrency | ✅ (Brief) | ✅ | ❌ (Missing) | `tests/concurrency/` | `src/frontend/parser/statements.cpp` | ✅ Consistent |

## 2. Documentation Coverage Gaps

- **language.md**: Completely missing. This is the primary spec drift.
- **stdlib.md**: Missing, though `std/core.lm` exists and serves as a de facto spec.
- **Class vs Frame**: Documentation heavily uses `class` but implementation and tests use `frame`.

## 3. Philosophy Violations (zen.md)

| Principle | Enforced In | Tests | Violations | Severity |
|-----------|-------------|-------|------------|----------|
| "Explicit is better than implicit" | `TypeChecker` | `tests/types/` | `learn.md` suggests type inference is common but doesn't show its limits. | LOW |
| "The absence of a value is an error condition..." | `std/core.lm`, Parser | `tests/types/options.lm` | None found in code. | ✅ |
| "Errors are not exceptions" | `std/core.lm`, Parser | `tests/integration/error_handling_vm.lm` | None found in code. | ✅ |

## 4. Teaching Inconsistencies (learn.md)

- **Concept Progression**: Progression is generally good (Variables -> Control Flow -> Functions -> Modules -> Collections -> Errors).
- **Misleading Simplifications**: `learn.md` uses `class` which is NOT supported by the parser for declarations, only as a token that causes a parse error if used for a frame-like block.

## 5. Verification Results Summary

- **Can the language be taught without misleading users?**: NO. `learn.md` teaches `class` syntax which fails to parse.
- **Is the documentation system internally consistent?**: NO. `learn.md`, `guide.md`, and `README.md` have conflicting terms (`class` vs `frame`).
- **Is the philosophy actually enforced?**: YES. The code implementation of `Option`/`Result` and the `?` operator strictly follows the "Errors are values" philosophy.

## 6. Blocking Issues & Ranking

1. **[HIGH] Pedagogy-Syntax Mismatch**: `learn.md` teaches `class` syntax while the parser only accepts `frame`. This is a critical blocker for new users.
2. **[MEDIUM] Missing Formal Spec**: The absence of `language.md` makes it impossible to verify behavior without reverse-engineering tests.
3. **[LOW] Philosophical Contradiction**: `zen.md` claims the language is null-free while `nil` exists in the parser and standard library.
