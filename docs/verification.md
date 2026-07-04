# Documentation Traceability & Verification Matrix

This document tracks the consistency between learning materials, guides, the formal language specification, and the actual test suite.

## Concept Traceability Matrix

| Concept | learn.md | guide.md | language.md | Tests | Status |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Variables (`var`)** | ✅ | ✅ | ✅ | `tests/basic/variables.lm` | ✅ |
| **Constants (`val`/`const`)** | ❌ | ❌ | ✅ | `tests/basic/variables.lm` | ⚠️ |
| **Integers (`int`)** | ✅ | ✅ | ✅ | `tests/types/basic.lm` | ✅ |
| **Decimals (`d2`, `d4`)** | ❌ | ❌ | ✅ | `tests/decimal_tests.lm` | ⚠️ |
| **Frames (`frame`)** | ✅ | ✅ | ✅ | `tests/oop/frame_declaration.lm`| ✅ |
| **Self reference (`self`)**| ✅ | ✅ | ✅ | `tests/oop/frame_declaration.lm`| ✅ |
| **Traits (`trait`)** | ❌ | ✅ | ✅ | `tests/oop/traits_dynamic.lm` | ✅ |
| **Modules (`import`)** | ✅ | ✅ | ✅ | `tests/modules/*` | ✅ |
| **Fallible (`Type?`)** | ✅ | ✅ | ✅ | `tests/types/options.lm` | ✅ |
| **Structured Concurrency**| ❌ | ✅ | ✅ | `tests/concurrency/*` | ✅ |
| **Pattern Match** | ✅ | ✅ | ✅ | `tests/loops/match.lm` | ✅ |
| **Ternary (`? :`)** | ❌ | ⚠️ | ⚠️ | ❌ | 🚨 |
| **Safe Access (`?.`)** | ❌ | ❌ | ⚠️ | ❌ | 🚨 |

**Statuses:**
- ✅ Fully consistent
- ⚠️ Partial / missing links (documented but not fully tested or implemented)
- 🚨 Contradiction / Spec Drift (documented but not implemented)

## 🚨 Surfaced Violations

### Philosophical Drift (zen.md)
- **Principle**: "The absence of a value is a state to be handled explicitly, not a source of crashes."
- **Status**: Implemented via `Type?` system.

### Spec Drift (language.md)
- **Feature**: Ternary operator (`? :`) is documented but not implemented in the parser.
- **Feature**: Safe access operator (`?.`) is documented but not implemented.
- **Feature**: Range steps (`0..10..2`) are documented but not implemented.

### Doc Drift (Beginner Risk - learn.md)
- **Violation**: `learn.md` mentions `this` as supported, but `language.md` explicitly states it is no longer a keyword.
- **Violation**: `learn.md` mentions a `-repl` flag that is not implemented in the CLI.

### Doc Drift (User Risk - guide.md)
- **Violation**: `guide.md` uses `class` in some descriptions while the language uses `frame`.
- **Violation**: `guide.md` documents `data frame` which is not enforced/implemented.

## 🏁 Final Integrity Check

1. **Is the language teachable without misleading users?**
   - **NO**. The inclusion of `this`, `class`, and unimplemented operators like ternary and safe-access in the guides and specification will mislead users.

2. **Is the documentation system internally consistent?**
   - **NO**. `language.md` contradicts `learn.md` regarding `this` vs `self`.

3. **Is the philosophy actually enforced?**
   - **YES**. Philosophical principles like explicit decimal scaling and structured concurrency are strictly enforced in the compiler and runtime.
