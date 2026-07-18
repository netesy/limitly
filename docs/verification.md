# Documentation Traceability & Verification Matrix

This document tracks the consistency between learning materials, guides, the formal language specification, and the actual test suite.

## Concept Traceability Matrix

| Concept | learn.md | guide.md | language.md | Tests | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Variables (`var`)** | [OK] | [OK] | [OK] | `tests/basic/variables.lm` | [OK] |
| **Constants (`val`/`const`)** | [OK] | [OK] | [OK] | `tests/basic/variables.lm` | [OK] |
| **Integers (`int`)** | [OK] | [OK] | [OK] | `tests/types/basic.lm` | [OK] |
| **Decimals (`d2`, `d4`)** | [OK] | [OK] | [OK] | `tests/decimal_tests.lm` | [OK] |
| **Frames (`frame`)** | [OK] | [OK] | [OK] | `tests/oop/frame_declaration.lm`| [OK] |
| **Self reference (`self`)**| [OK] | [OK] | [OK] | `tests/oop/frame_declaration.lm`| [OK] |
| **Traits (`trait`)** | [FAIL] | [OK] | [OK] | `tests/oop/traits_dynamic.lm` | [OK] |
| **Modules (`import`)** | [OK] | [OK] | [OK] | `tests/modules/*` | [OK] |
| **Fallible (`Type?`)** | [OK] | [OK] | [OK] | `tests/types/options.lm` | [OK] |
| **Structured Concurrency**| [FAIL] | [OK] | [OK] | `tests/concurrency/*` | [OK] |
| **Pattern Match** | [OK] | [OK] | [OK] | `tests/loops/match.lm` | [OK] |
| **Ternary (`? :`)** | [FAIL] | [WARN] | [WARN] | [FAIL] | 🚨 |
| **Safe Access (`?.`)** | [FAIL] | [FAIL] | [WARN] | [FAIL] | 🚨 |

**Statuses:**
- [OK] Fully consistent
- [WARN] Partial / missing links (documented but not fully tested or implemented)
- 🚨 Contradiction / Spec Drift (documented but not implemented)

## 🚨 Surfaced Violations (Resolved/Flagged)

### Philosophical Drift (zen.md)
- **Principle**: "The absence of a value is a state to be handled explicitly, not a source of crashes."
- **Status**: Implemented via `Type?` system.

### Spec Drift (language.md)
- **Feature**: Ternary operator (`? :`) is documented but not implemented in the parser. (Flagged as Planned)
- **Feature**: Safe access operator (`?.`) is documented but not implemented. (Flagged as Planned)
- **Feature**: Range steps (`0..10..2`) are documented but not implemented. (Flagged as Planned)

### Doc Drift (Resolved)
- **Violation**: `learn.md` previously mentioned `this` as supported. (Fixed: Now only uses `self`)
- **Violation**: `learn.md` previously mentioned a `-repl` flag. (Fixed: Compiler now defaults to REPL mode if no args given, flag removed from docs)
- **Violation**: `guide.md` used `class` in some descriptions. (Fixed: Standardized on `frame`)
- **Violation**: `guide.md` documented `data frame` as implemented. (Fixed: Flagged as Planned)

## 🏁 Final Integrity Check

1. **Is the language teachable without misleading users?**
   - **YES**. Keywords and features have been standardized. Unimplemented features are explicitly marked as "Planned".

2. **Is the documentation system internally consistent?**
   - **YES**. `language.md`, `learn.md`, and `guide.md` are now synchronized on terminology and expected behavior.

3. **Is the philosophy actually enforced?**
   - **YES**. Philosophical principles like explicit decimal scaling and structured concurrency are strictly enforced in the compiler and runtime.
