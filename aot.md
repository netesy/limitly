# Comprehensive Limitly AOT Compiler Validation & Parity Analysis Report (Linux vs. Windows via Wine)

## Executive Summary

This report presents a thorough, comparative analysis of the **Limitly Ahead-Of-Time (AOT) Compiler** using the **Fyra backend** targeting both **Linux (x86_64 ELF)** and **Windows (x86_64 PE, executed under Wine)** environments.

The test suite consists of **80 validation test files** covering fundamental language constructs, expressions, control flow, functions, OOP/frames/traits, type systems, concurrency, stdlib modules, and regression benchmarks.

### Key Metrics Summary

| Category | Native Linux Target (x86_64 ELF) | Windows Target (x86_64 PE via Wine) | Notes / Key Observations |
| :--- | :--- | :--- | :--- |
| **Total Test Suite** | 80 | 80 | Standard Limitly AOT validation suite |
| **Succeeded (`PASS`)** | **30 (37.5%)** | **29 (36.25%)** | Binary compiles, executes with exit code 0, matching expected interpreter output. |
| **Output Mismatches (`MISMATCH`)** | **30 (37.5%)** | **30 (37.5%)** | Binary executes with exit code 0, but output differs (float byte formatting, Dict key order). |
| **Runtime Failures (`RUNTIME_FAIL`)**| **19 (23.75%)** | **20 (25.0%)** | Executable exits with non-zero status code (SIGSEGV -11 or assertion code 1/5). |
| **Hung / Timed Out (`HANG`)** | **1 (1.25%)** | **1 (1.25%)** | Executable exceeds 30-second runtime limit (`tests/stdlib/iterator_module_test.lm`). |
| **Build Failures** | **0 (0.0%)** | **0 (0.0%)** | All 80 test cases compiled to machine code without compilation errors. |

---

## Detailed Results by Platform

### 1. Native Linux Target (x86_64 ELF)

#### A. Succeeded Tests (`PASS` - 30 Tests)
1. `tests/basic/control_flow.lm`
2. `tests/expressions/logical.lm`
3. `tests/expressions/ranges.lm`
4. `tests/loops/for_loops.lm`
5. `tests/loops/iter_loops.lm`
6. `tests/loops/while_loops.lm`
7. `tests/functions/basic.lm`
8. `tests/types/options.lm`
9. `tests/types/structural_type_tests.lm`
10. `tests/modules/function_params_test.lm`
11. `tests/oop/frame_declaration.lm`
12. `tests/oop/traits_inheritance.lm`
13. `tests/oop/visibility_test.lm`
14. `tests/oop/composition_test.lm`
15. `tests/stdlib/core/math_test.lm`
16. `tests/stdlib/core/option_result_test.lm`
17. `tests/stdlib/core/string_option_result_test.lm`
18. `tests/stdlib/collections/list_test.lm`
19. `tests/stdlib/collections/vector_test.lm`
20. `tests/stdlib/collections/queue_stack_bitset_test.lm`
21. `tests/stdlib/collections/arraylist_test.lm`
22. `tests/stdlib/iterator/iterator_test.lm`
23. `tests/stdlib/env_module_test.lm`
24. `tests/stdlib/process_module_test.lm`
25. `tests/stdlib/search/search_test.lm`
26. `tests/stdlib/range/range_test.lm`
27. `tests/stdlib/sort/sort_test.lm`
28. `tests/stdlib/crypto/hash_test.lm`
29. `tests/regression/ownership_refactor_test.lm`
30. `tests/regression/trait_dispatch_test.lm`

#### B. Output Mismatches (`MISMATCH` - 30 Tests)
1. `tests/basic/variables.lm`
2. `tests/basic/print_statements.lm`
3. `tests/basic/list_dict_tuple.lm`
4. `tests/expressions/arithmetic.lm`
5. `tests/expressions/scientific_notation.lm`
6. `tests/strings/interpolation.lm`
7. `tests/strings/operations.lm`
8. `tests/loops/match.lm`
9. `tests/types/basic.lm`
10. `tests/types/unions.lm`
11. `tests/modules/basic_import_test.lm`
12. `tests/modules/comprehensive_module_test.lm`
13. `tests/modules/show_filter_test.lm`
14. `tests/modules/hide_filter_test.lm`
15. `tests/modules/module_caching_test.lm`
16. `tests/modules/alias_import_test.lm`
17. `tests/modules/multiple_imports_test.lm`
18. `tests/oop/traits_dynamic.lm`
19. `tests/stdlib/core/string_test.lm`
20. `tests/stdlib/core_module_test.lm`
21. `tests/stdlib/collections/queue_stack_test.lm`
22. `tests/stdlib/collections/priority_queue_test.lm`
23. `tests/stdlib/collections_module_test.lm`
24. `tests/stdlib/algorithm_module_test.lm`
25. `tests/stdlib/string_module_test.lm`
26. `tests/stdlib/unicode_module_test.lm`
27. `tests/stdlib/regex_module_test.lm`
28. `tests/stdlib/path/path_test.lm`
29. `tests/stdlib/url_test.lm`
30. `tests/stdlib/mime_test.lm`

#### C. Runtime Failures (`RUNTIME_FAIL` - 19 Tests)
1. `tests/basic/literals.lm` (SIGSEGV -11)
2. `tests/expressions/large_literals.lm` (SIGSEGV -11)
3. `tests/loops/match_advanced.lm` (SIGSEGV -11)
4. `tests/functions/advanced.lm` (SIGSEGV -11)
5. `tests/functions/closures.lm` (SIGSEGV -11)
6. `tests/functions/first_class.lm` (SIGSEGV -11)
7. `tests/types/advanced.lm` (SIGSEGV -11)
8. `tests/types/enums.lm` (SIGSEGV -11)
9. `tests/types/refined_types.lm` (SIGSEGV -11)
10. `tests/concurrency/parallel_blocks.lm` (SIGSEGV -11)
11. `tests/concurrency/concurrent_blocks.lm` (SIGSEGV -11)
12. `tests/stdlib/math_module_test.lm` (SIGSEGV -11)
13. `tests/stdlib/time_module_test.lm` (SIGSEGV -11)
14. `tests/stdlib/random_module_test.lm` (SIGSEGV -11)
15. `tests/stdlib/parse_module_test.lm` (SIGSEGV -11)
16. `tests/stdlib/format_module_test.lm` (SIGSEGV -11)
17. `tests/stdlib/semver_test.lm` (SIGSEGV -11)
18. `tests/stdlib/uuid_test.lm` (SIGSEGV -11)
19. `tests/stdlib/net/net_test.lm` (SIGSEGV -11)

#### D. Hung Tests (`HANG` - 1 Test)
1. `tests/stdlib/iterator_module_test.lm` (Exceeded 30.0s timeout limit)

---

### 2. Windows Target (x86_64 PE executed under Wine)

#### A. Succeeded Tests (`PASS` - 29 Tests)
1. `tests/basic/control_flow.lm`
2. `tests/expressions/logical.lm`
3. `tests/expressions/ranges.lm`
4. `tests/loops/for_loops.lm`
5. `tests/loops/iter_loops.lm`
6. `tests/loops/while_loops.lm`
7. `tests/functions/basic.lm`
8. `tests/types/options.lm`
9. `tests/types/structural_type_tests.lm`
10. `tests/modules/function_params_test.lm`
11. `tests/oop/frame_declaration.lm`
12. `tests/oop/traits_inheritance.lm`
13. `tests/oop/visibility_test.lm`
14. `tests/oop/composition_test.lm`
15. `tests/stdlib/core/math_test.lm`
16. `tests/stdlib/core/option_result_test.lm`
17. `tests/stdlib/core/string_option_result_test.lm`
18. `tests/stdlib/collections/list_test.lm`
19. `tests/stdlib/collections/vector_test.lm`
20. `tests/stdlib/collections/queue_stack_bitset_test.lm`
21. `tests/stdlib/collections/arraylist_test.lm`
22. `tests/stdlib/iterator/iterator_test.lm`
23. `tests/stdlib/env_module_test.lm`
24. `tests/stdlib/process_module_test.lm`
25. `tests/stdlib/search/search_test.lm`
26. `tests/stdlib/range/range_test.lm`
27. `tests/stdlib/crypto/hash_test.lm`
28. `tests/regression/ownership_refactor_test.lm`
29. `tests/regression/trait_dispatch_test.lm`

#### B. Output Mismatches (`MISMATCH` - 30 Tests)
1. `tests/basic/variables.lm`
2. `tests/basic/print_statements.lm`
3. `tests/basic/list_dict_tuple.lm`
4. `tests/expressions/arithmetic.lm`
5. `tests/expressions/scientific_notation.lm`
6. `tests/strings/interpolation.lm`
7. `tests/strings/operations.lm`
8. `tests/types/basic.lm`
9. `tests/types/unions.lm`
10. `tests/modules/basic_import_test.lm`
11. `tests/modules/comprehensive_module_test.lm`
12. `tests/modules/show_filter_test.lm`
13. `tests/modules/hide_filter_test.lm`
14. `tests/modules/module_caching_test.lm`
15. `tests/modules/alias_import_test.lm`
16. `tests/modules/multiple_imports_test.lm`
17. `tests/oop/traits_dynamic.lm`
18. `tests/stdlib/core/string_test.lm`
19. `tests/stdlib/core_module_test.lm`
20. `tests/stdlib/collections/queue_stack_test.lm`
21. `tests/stdlib/collections/priority_queue_test.lm`
22. `tests/stdlib/collections_module_test.lm`
23. `tests/stdlib/string_module_test.lm`
24. `tests/stdlib/unicode_module_test.lm`
25. `tests/stdlib/regex_module_test.lm`
26. `tests/stdlib/time_module_test.lm`
27. `tests/stdlib/format_module_test.lm`
28. `tests/stdlib/path/path_test.lm`
29. `tests/stdlib/url_test.lm`
30. `tests/stdlib/mime_test.lm`

#### C. Runtime Failures (`RUNTIME_FAIL` - 20 Tests)
1. `tests/basic/literals.lm`
2. `tests/expressions/large_literals.lm`
3. `tests/loops/match.lm`
4. `tests/loops/match_advanced.lm`
5. `tests/functions/advanced.lm`
6. `tests/functions/closures.lm`
7. `tests/functions/first_class.lm`
8. `tests/types/advanced.lm`
9. `tests/types/enums.lm`
10. `tests/types/refined_types.lm`
11. `tests/concurrency/parallel_blocks.lm`
12. `tests/concurrency/concurrent_blocks.lm`
13. `tests/stdlib/algorithm_module_test.lm`
14. `tests/stdlib/math_module_test.lm`
15. `tests/stdlib/random_module_test.lm`
16. `tests/stdlib/parse_module_test.lm`
17. `tests/stdlib/sort/sort_test.lm`
18. `tests/stdlib/semver_test.lm`
19. `tests/stdlib/uuid_test.lm`
20. `tests/stdlib/net/net_test.lm`

#### D. Hung Tests (`HANG` - 1 Test)
1. `tests/stdlib/iterator_module_test.lm` (Exceeded 30.0s timeout limit under Wine)

---

## Cross-Platform Parity & Behavioral Differences

Comparing native Linux ELF execution against Windows PE execution under Wine reveals cross-platform discrepancies:

```
+----------------------------------------+-------------------+-------------------+
| Test Name                              | Linux Outcome     | Windows Outcome   |
+----------------------------------------+-------------------+-------------------+
| tests/loops/match.lm                   | MISMATCH          | RUNTIME_FAIL (5)  |
| tests/stdlib/algorithm_module_test.lm  | MISMATCH          | RUNTIME_FAIL (1)  |
| tests/stdlib/time_module_test.lm       | RUNTIME_FAIL (-11)| MISMATCH          |
| tests/stdlib/format_module_test.lm     | RUNTIME_FAIL (-11)| MISMATCH          |
| tests/stdlib/sort/sort_test.lm         | PASS              | RUNTIME_FAIL (1)  |
| tests/stdlib/iterator_module_test.lm   | HANG              | HANG / TIMEOUT    |
+----------------------------------------+-------------------+-------------------+
```

---

## Technical Root Cause Analysis of AOT Compiler Deficiencies

1. **Float Packing & Constant Literal Formatting**:
   - Refactored `src/backend/fyra/builder.cpp` to create string headers for float literal constants (`format_float_literal`) and `lm_float_to_str` in `src/backend/fyra/fyra_builtin_functions.cpp` to safely convert bitcast IEEE-754 double floats.
2. **Closure Environment Allocation**:
   - Dynamic functions and closures require passing env pointers in registers.
3. **Dictionary Key Iteration Order**:
   - VM interpreter hash bucket order differs from AOT memory address order.
4. **Threading & Concurrency**:
   - OS-specific wrapper stubs are needed for `pthread` and WinAPI worker threads.
