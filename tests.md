# Limitly Test Suite Summary

This document lists the status, timing, and outcomes of all tests in both the main (positive) test suite and the negative safety test suite of the Limitly Language compiler.

---

## 📊 High-Level Summary

### 1. Main (Positive) Test Suite
*   **Total Tests Executed:** 80
*   **Passed:** 80 (100.0%)
*   **Failed:** 0 (0.0%)
*   **Hanging/Timeout:** 0 (0.0%)

### 2. Negative Test Suite
*   **Total Tests Executed:** 78
*   **Passed (Rejected Correctly):** 67 (85.9%)
*   **Failed (Incorrectly Compiled):** 11 (14.1%)
*   **Hanging/Timeout:** 0 (0.0%)

---

## ✅ Positive Tests Status (80/80 Passing)

All canonical positive and standard library tests compile and run flawlessly with zero errors and zero hangs.

### 1. Basic Constructs (5/5 Passing)
*   `tests/basic/variables.lm` (0.01s) - Variable declarations and assignments
*   `tests/basic/literals.lm` (0.02s) - Literal expressions (ints, floats, strings, booleans, nil)
*   `tests/basic/control_flow.lm` (0.02s) - If/Elif/Else statements
*   `tests/basic/print_statements.lm` (0.02s) - Print output formatting
*   `tests/basic/list_dict_tuple.lm` (0.02s) - Basic container syntax and usages

### 2. Expressions (5/5 Passing)
*   `tests/expressions/arithmetic.lm` (0.02s) - Arithmetic operations (+, -, *, /, %, **)
*   `tests/expressions/logical.lm` (0.02s) - Short-circuit logical operations (and, or, not)
*   `tests/expressions/ranges.lm` (0.02s) - Inclusive/exclusive ranges (1..10)
*   `tests/expressions/scientific_notation.lm` (0.02s) - Floating point literals with exponent parts
*   `tests/expressions/large_literals.lm` (0.02s) - Large numbers and 64-bit bounds

### 3. Strings (2/2 Passing)
*   `tests/strings/interpolation.lm` (0.02s) - Interpolated strings with variable evaluation
*   `tests/strings/operations.lm` (0.02s) - Character indexing, concatenation, formatting

### 4. Loops & Pattern Matching (5/5 Passing)
*   `tests/loops/for_loops.lm` (0.02s) - Classical C-style for loops
*   `tests/loops/iter_loops.lm` (0.03s) - Modern collection/range iteration
*   `tests/loops/while_loops.lm` (0.03s) - Standard while loops with condition evaluation
*   `tests/loops/match.lm` (0.04s) - Exhaustive enum variant and literal match statements
*   `tests/loops/match_advanced.lm` (0.07s) - Guard clauses and structured pattern matching

### 5. Functions & Closures (4/4 Passing)
*   `tests/functions/basic.lm` (0.03s) - Positional/optional parameter passing and returns
*   `tests/functions/advanced.lm` (0.02s) - Variadic/default argument bindings
*   `tests/functions/closures.lm` (0.04s) - State mutation and captures inside returned lambdas
*   `tests/functions/first_class.lm` (0.04s) - Higher-order functions and callable types

### 6. Type System (7/7 Passing)
*   `tests/types/basic.lm` (0.03s) - Primitive type conversions and aliases
*   `tests/types/unions.lm` (0.03s) - Union types (A | B) and checks
*   `tests/types/options.lm` (0.02s) - Syntax and semantics of Option types (Type?)
*   `tests/types/advanced.lm` (0.04s) - Extensible record types and structural types
*   `tests/types/enums.lm` (0.04s) - Tagged enums with associated data types
*   `tests/types/refined_types.lm` (0.05s) - Under-the-hood checks for refined constraint types
*   `tests/types/structural_type_tests.lm` (0.01s) - Structural record typing and layout

### 7. Modules & Imports (8/8 Passing)
*   `tests/modules/basic_import_test.lm` (0.02s) - Standard import namespaces
*   `tests/modules/comprehensive_module_test.lm` (0.08s) - Multi-module build hierarchy
*   `tests/modules/show_filter_test.lm` (0.03s) - Selective imports using `show` filters
*   `tests/modules/hide_filter_test.lm` (0.03s) - Selective imports using `hide` filters
*   `tests/modules/module_caching_test.lm` (0.05s) - Cyclic/caching modules
*   `tests/modules/function_params_test.lm` (0.04s) - Importing default parameters
*   `tests/modules/alias_import_test.lm` (0.04s) - Aliased namespaces with `as` keyword
*   `tests/modules/multiple_imports_test.lm` (0.05s) - Importing symbols across several modules

### 8. OOP & Traits (5/5 Passing)
*   `tests/oop/frame_declaration.lm` (0.02s) - Frame definitions, init constructors, and methods
*   `tests/oop/traits_dynamic.lm` (0.01s) - Polymorphic dispatch via Traits
*   `tests/oop/traits_inheritance.lm` (0.01s) - Trait inheritance hierarchies
*   `tests/oop/visibility_test.lm` (0.01s) - Public/Protected/Private boundaries on frame fields/methods
*   `tests/oop/composition_test.lm` (0.01s) - Nested frame composition and lifetimes

### 9. Concurrency (2/2 Passing)
*   `tests/concurrency/parallel_blocks.lm` (0.02s) - Thread-safe `parallel` blocks
*   `tests/concurrency/concurrent_blocks.lm` (0.02s) - Structured concurrency with `concurrent` blocks

### 10. Stdlib Core (5/5 Passing)
*   `tests/stdlib/core/string_test.lm` (0.23s)
*   `tests/stdlib/core/math_test.lm` (0.23s)
*   `tests/stdlib/core/option_result_test.lm` (0.13s)
*   `tests/stdlib/core/string_option_result_test.lm` (0.33s)
*   `tests/stdlib/core_module_test.lm` (0.13s)

### 11. Stdlib Collections (7/7 Passing)
*   `tests/stdlib/collections/list_test.lm` (0.07s)
*   `tests/stdlib/collections/vector_test.lm` (0.80s) - **SLOW**
*   `tests/stdlib/collections/queue_stack_test.lm` (0.42s)
*   `tests/stdlib/collections/queue_stack_bitset_test.lm` (0.82s) - **SLOW**
*   `tests/stdlib/collections/arraylist_test.lm` (0.76s) - **SLOW**
*   `tests/stdlib/collections/priority_queue_test.lm` (0.81s) - **SLOW**
*   `tests/stdlib/collections_module_test.lm` (0.97s) - **SLOW**

### 12. Stdlib Math & Algorithms (7/7 Passing)
*   `tests/stdlib/algorithm_module_test.lm` (0.46s)
*   `tests/stdlib/iterator/iterator_test.lm` (0.13s)
*   `tests/stdlib/iterator_module_test.lm` (0.20s)
*   `tests/stdlib/math_module_test.lm` (0.85s) - **SLOW**
*   `tests/stdlib/string_module_test.lm` (0.23s)
*   `tests/stdlib/unicode_module_test.lm` (0.14s)
*   `tests/stdlib/regex_module_test.lm` (0.22s)

### 13. Stdlib Utility Modules (10/10 Passing)
*   `tests/stdlib/env_module_test.lm` (0.04s)
*   `tests/stdlib/process_module_test.lm` (0.05s)
*   `tests/stdlib/time_module_test.lm` (0.32s)
*   `tests/stdlib/random_module_test.lm` (0.26s)
*   `tests/stdlib/parse_module_test.lm` (0.46s)
*   `tests/stdlib/format_module_test.lm` (0.39s)
*   `tests/stdlib/search/search_test.lm` (0.06s)
*   `tests/stdlib/range/range_test.lm` (0.05s)
*   `tests/stdlib/sort/sort_test.lm` (0.17s)
*   `tests/stdlib/path/path_test.lm` (0.04s)

### 14. Stdlib Network & Protocols (5/5 Passing)
*   `tests/stdlib/semver_test.lm` (0.36s)
*   `tests/stdlib/url_test.lm` (0.39s)
*   `tests/stdlib/mime_test.lm` (0.39s)
*   `tests/stdlib/uuid_test.lm` (0.58s) - **SLOW**
*   `tests/stdlib/crypto/hash_test.lm` (0.15s)
*   `tests/stdlib/net/net_test.lm` (0.25s)

### 15. Regression (2/2 Passing)
*   `tests/regression/ownership_refactor_test.lm` (0.01s)
*   `tests/regression/trait_dispatch_test.lm` (0.01s)

---

## 🛑 Negative Tests Status (67/78 Passing, 11/78 Failed)

The negative test suite checks that the compiler safely detects and rejects illegal code.

### Summary by Category:
*   **bounds_checking:** 8/8 (100.0% Passing)
*   **patterns:** 7/7 (100.0% Passing)
*   **soundness:** 14/14 (100.0% Passing)
*   **syntax:** 5/5 (100.0% Passing)
*   **traits:** 4/4 (100.0% Passing)
*   **type_safety:** 8/8 (100.0% Passing)
*   **visibility:** 4/4 (100.0% Passing)
*   **closures:** 5/7 (71.4% Passing)
*   **concurrency:** 3/4 (75.0% Passing)
*   **control_flow:** 5/6 (83.3% Passing)
*   **memory:** 2/3 (66.7% Passing)
*   **arithmetic:** 2/8 (25.0% Passing)

### ✗ Failed Negative Tests Detail (Compile cleanly instead of raising error):

1.  **arithmetic/exponent_overflow.lm** - silent runtime wrapping (underlying host platform behavior).
2.  **arithmetic/integer_overflow.lm** - silent runtime wrapping.
3.  **arithmetic/multiplication_overflow.lm** - silent runtime wrapping.
4.  **arithmetic/negative_shift.lm** - silent runtime wrapping.
5.  **arithmetic/shift_overflow.lm** - silent runtime wrapping.
6.  **arithmetic/subtraction_underflow.lm** - silent runtime wrapping.
7.  **closures/capture_mutable_conflict.lm** - mutating captured local variables is natively supported in the VM, and required for positive closure tests (`closures.lm`).
8.  **closures/closure_lifetime_violation.lm** - returning lambda closures that capture local non-function variables is natively supported and required for positive closure tests.
9.  **concurrency/worker_shared_state.lm** - compile-time shared state checker currently lets this pass.
10. **control_flow/return_in_global_scope.lm** - global scope return permitted as program termination in this VM revision.
11. **memory/memory_leak.lm** - static leak analysis is disabled in the current memory checker.

---

## 🐢 Slow Tests Summary

The following tests take longer than 0.5 seconds to run. This is expected due to their extensive assertions, math iterations, collection allocations, or cryptographic operations:

1.  `tests/stdlib/math_module_test.lm` (~0.85s)
2.  `tests/stdlib/collections_module_test.lm` (~0.97s)
3.  `tests/stdlib/collections/vector_test.lm` (~0.80s)
4.  `tests/stdlib/collections/queue_stack_bitset_test.lm` (~0.82s)
5.  `tests/stdlib/collections/arraylist_test.lm` (~0.76s)
6.  `tests/stdlib/collections/priority_queue_test.lm` (~0.81s)
7.  `tests/stdlib/uuid_test.lm` (~0.58s)
8.  `tests/stdlib/time_module_test.lm` (~0.58s)

---

## 🚫 Hanging or Timeout Tests

*   **Hanging/Timeout Tests:** None.
