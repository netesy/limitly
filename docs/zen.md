# The Zen of Lymar

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

*Although that way may not be obvious at first unless you're a Lymarer.*

*Now is better than never.*

*Although never is often better than *right* now.*

---

## Philosophy Audit & Mapping

Principle: "Explicit is better than implicit"
Enforced In:
  - TypeChecker: src/frontend/type_checker/types.cpp
  - Tests: tests/types/basic.lm
Violations: None
Severity: NONE

Principle: "Errors are not exceptions; they are values to be handled"
Enforced In:
  - TypeChecker: src/frontend/type_checker/types.cpp
  - Tests: tests/stdlib/core/option_result_test.lm
Violations: None
Severity: NONE

Principle: "Concurrency should be structured, not chaotic"
Enforced In:
  - Parser: src/frontend/parser/statements.cpp
  - Tests: tests/concurrency/concurrent_blocks.lm
Violations: None
Severity: NONE

Principle: "Safety should not be a sacrifice for performance"
Enforced In:
  - MemoryChecker: src/frontend/memory_checker.cpp
  - Tests: tests/ffi/test_hardening.lm
Violations: None
Severity: NONE

Principle: "Clarity is king; code is read more often than it is written"
Enforced In:
  - Formatter: src/formatter.cpp
  - Tests: tests/basic/variables.lm
Violations: None
Severity: NONE

Principle: "The absence of a value is a state to be handled explicitly, not a source of crashes"
Enforced In:
  - TypeChecker: src/frontend/type_checker/types.cpp
  - Tests: tests/types/options.lm
Violations: None
Severity: NONE

Principle: "If the implementation is hard to explain, it's a bad idea"
Enforced In:
  - LIR Generator: src/lir/generator.cpp
  - Tests: tests/lir/test_round_trip.cpp
Violations: None
Severity: NONE

Principle: "If the implementation is easy to explain, it may be a good idea"
Enforced In:
  - CST Printer: src/frontend/cst.cpp
  - Tests: tests/basic/variables.lm
Violations: None
Severity: NONE

Principle: "Modules are one honking great idea -- let's do more of those"
Enforced In:
  - ModuleManager: src/frontend/module_manager.cpp
  - Tests: tests/modules/comprehensive_module_test.lm
Violations: None
Severity: NONE

Principle: "Readability counts"
Enforced In:
  - Formatter: src/formatter.cpp
  - Tests: tests/basic/print_statements.lm
Violations: None
Severity: NONE

Principle: "Special cases aren't special enough to break the rules"
Enforced In:
  - TypeChecker: src/frontend/type_checker/core.cpp
  - Tests: tests/types/structural_type_tests.lm
Violations: None
Severity: NONE

Principle: "Although practicality beats purity"
Enforced In:
  - VM Operations: src/backend/vm/ops/ffi.cpp
  - Tests: tests/ffi/test_trampoline.lm
Violations: None
Severity: NONE

Principle: "In the face of ambiguity, refuse the temptation to guess"
Enforced In:
  - Parser: src/frontend/parser/statements.cpp
  - Tests: tests/basic/control_flow.lm
Violations: None
Severity: NONE

Principle: "There should be one-- and preferably only one --obvious way to do it"
Enforced In:
  - Frame Receiver Rule: src/frontend/parser/statements.cpp
  - Tests: tests/oop/frame_declaration.lm
Violations: None
Severity: NONE

Principle: "Although that way may not be obvious at first unless you're a Lymarer"
Enforced In:
  - Language Spec: docs/language.md
  - Tests: tests/loops/match_advanced.lm
Violations: None
Severity: NONE

Principle: "Now is better than never"
Enforced In:
  - Constraint Engine: src/frontend/constraint_engine.cpp
  - Tests: tests/devx_roadmap_test.lm
Violations: None
Severity: NONE

Principle: "Although never is often better than *right* now"
Enforced In:
  - LIR Verifier: src/lir/verifier.cpp
  - Tests: tests/lir/test_round_trip.cpp
Violations: None
Severity: NONE
