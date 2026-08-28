# The Zen of Limit

*Explicit is better than implicit.*

*Errors are not exceptions; they are values to be handled.*

*Concurrency should be structured, not chaotic.*

*Safety should not be a sacrifice for performance.*

*Clarity is king; code is read more often than it is written.*

*The absence of a value is a state to be handled explicitly, not a source of crashes.*

*If the implementation is hard to explain, it's a bad idea.*

*If the implementation is easy to explain, it may be a good idea.*

*Modules are one honking great idea -- let's do more of those.*

*Readability counts.*

*Special cases aren't special enough to break the rules.*

*Although practicality beats purity.*

*In the face of ambiguity, refuse the temptation to guess.*

*There should be one-- and preferably only one --obvious way to do it.*

*Although that way may not be obvious at first unless you're a Limiter.*

*Now is better than never.*

*Although never is often better than *right* now.*

---

## Concrete Philosophy Mapping & Enforcement Audit

### Principle: "Explicit is better than implicit"
- **Enforced In**:
  - `TypeChecker::is_type_compatible`: `src/frontend/type_checker/types.cpp:258` (Strict decimal and primitive compatibility; no implicit conversions allowed).
  - `Parser::varDeclaration`: `src/frontend/parser/statements.cpp:138` (Explicit type annotations and explicit const/val initialization).
- **Tests**:
  - `tests/decimal_tests.lm`
  - `tests/types/basic.lm`
- **Violations**: None.

### Principle: "Errors are not exceptions; they are values to be handled"
- **Enforced In**:
  - Unified `Type?` system: `src/frontend/type_checker/types.cpp:822` (`TypeChecker::is_exhaustive_error_match` enforces exhaustive error pattern coverage for `ok(...)` / `err()`).
  - Native constructors: `src/lir/generator/expressions.cpp` (Lowers `ok` and `err` to value boxes).
- **Tests**:
  - `tests/error_handling/unified_type_system.lm`
- **Violations**: None.

### Principle: "Concurrency should be structured, not chaotic"
- **Enforced In**:
  - AST Parser & LIR Generator: `src/frontend/parser/statements.cpp:520` (`parallelStatement` and `concurrentStatement` bind task lifetimes strictly to lexical scopes).
  - LIR Generator: `src/lir/generator/concurrency.cpp:15` (Emits scoped join barriers at block exits).
- **Tests**:
  - `tests/concurrency/test_structured.lm`
- **Violations**: None.

### Principle: "Safety should not be a sacrifice for performance"
- **Enforced In**:
  - Memory Checker: `src/frontend/memory_checker.cpp` (Region-based deterministic scope tracking without GC pauses).
  - Type Checker: `src/frontend/type_checker/memory.cpp` (Scope lifetime tracking and move verification).
- **Tests**:
  - `tests/valloc_test.cpp`
- **Violations**: None.

### Principle: "The absence of a value is a state to be handled explicitly, not a source of crashes"
- **Enforced In**:
  - Type Checker: `src/frontend/type_checker/types.cpp:710` (`is_optional_type` guarantees explicit pattern checks or `?` / `? else` unwrap before member access).
- **Tests**:
  - `tests/error_handling/unified_type_system.lm`
- **Violations**: None.

### Principle: "Modules are one honking great idea -- let's do more of those"
- **Enforced In**:
  - Module Manager: `src/frontend/module_manager.cpp:45` (Strict isolation, namespace resolution, and visibility enforcement).
- **Tests**:
  - `tests/modules/test_import.lm`
- **Violations**: None.
