# Comprehensive Limitly AOT Compiler Validation & Parity Analysis Report (Linux vs. Windows via Wine)

## Executive Summary

This report presents a thorough, comparative analysis of the **Limitly Ahead-Of-Time (AOT) Compiler** using the **Fyra backend** targeting both **Linux (x86_64 ELF)** and **Windows (x86_64 PE, executed under Wine)** environments.

The test suite consists of **80 validation test files** covering fundamental language constructs, expressions, control flow, functions, OOP/frames/traits, type systems, concurrency, stdlib modules, and regression benchmarks.

### Key Metrics Summary

| Category | Native Linux Target (x86_64 ELF) | Windows Target (x86_64 PE) | Notes / Key Observations |
| :--- | :--- | :--- | :--- |
| **Total Test Suite** | 80 | 80 | Standard Limitly AOT validation suite |
| **Succeeded (`PASS`)** | **32 (40.0%)** | **31 (38.75%)** | Binary compiles, executes with exit code 0, matching expected interpreter output (`variables.lm` fixed). |
| **Output Mismatches (`MISMATCH`)** | **31 (38.75%)** | **31 (38.75%)** | Binary executes with exit code 0, but output differs. |
| **Runtime Failures (`RUNTIME_FAIL`)**| **16 (20.0%)** | **17 (21.25%)** | Executable exits with non-zero status code (SIGSEGV -11 or assertion exit code 1). |
| **Hung / Timed Out (`HANG`)** | **1 (1.25%)** | **1 (1.25%)** | Executable exceeds runtime limit (`tests/stdlib/iterator_module_test.lm`). |
| **Build Failures** | **0 (0.0%)** | **0 (0.0%)** | All 80 test cases compiled to machine code without compilation errors. |

---

## Detailed Results by Platform

### 1. Native Linux Target (x86_64 ELF)

#### A. Succeeded Tests (`PASS` - 32 Tests)
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
31. `tests/basic/variables.lm`
32. `tests/types/unions.lm`

#### B. Output Mismatches (`MISMATCH` - 31 Tests)
1. `tests/basic/print_statements.lm`
2. `tests/basic/list_dict_tuple.lm`
3. `tests/expressions/arithmetic.lm`
4. `tests/expressions/scientific_notation.lm`
5. `tests/strings/interpolation.lm`
6. `tests/strings/operations.lm`
7. `tests/loops/match.lm`
8. `tests/types/basic.lm`
9. `tests/modules/basic_import_test.lm`
10. `tests/modules/comprehensive_module_test.lm`
11. `tests/modules/show_filter_test.lm`
12. `tests/modules/hide_filter_test.lm`
13. `tests/modules/module_caching_test.lm`
14. `tests/modules/alias_import_test.lm`
15. `tests/modules/multiple_imports_test.lm`
16. `tests/oop/traits_dynamic.lm`
17. `tests/stdlib/core/string_test.lm`
18. `tests/stdlib/core_module_test.lm`
19. `tests/stdlib/collections/queue_stack_test.lm`
20. `tests/stdlib/collections/priority_queue_test.lm`
21. `tests/stdlib/collections_module_test.lm`
22. `tests/stdlib/algorithm_module_test.lm`
23. `tests/stdlib/string_module_test.lm`
24. `tests/stdlib/unicode_module_test.lm`
25. `tests/stdlib/regex_module_test.lm`
26. `tests/stdlib/path/path_test.lm`
27. `tests/stdlib/url_test.lm`
28. `tests/stdlib/mime_test.lm`
29. `tests/types/advanced.lm`
30. `tests/types/enums.lm`
31. `tests/types/refined_types.lm`

#### C. Runtime Failures (`RUNTIME_FAIL` - 16 Tests)
1. `tests/basic/literals.lm` (SIGSEGV -11)
2. `tests/expressions/large_literals.lm` (SIGSEGV -11)
3. `tests/loops/match_advanced.lm` (SIGSEGV -11)
4. `tests/functions/advanced.lm` (SIGSEGV -11)
5. `tests/functions/closures.lm` (SIGSEGV -11)
6. `tests/functions/first_class.lm` (SIGSEGV -11)
7. `tests/concurrency/parallel_blocks.lm` (SIGSEGV -11)
8. `tests/concurrency/concurrent_blocks.lm` (SIGSEGV -11)
9. `tests/stdlib/math_module_test.lm` (SIGSEGV -11)
10. `tests/stdlib/time_module_test.lm` (SIGSEGV -11)
11. `tests/stdlib/random_module_test.lm` (SIGSEGV -11)
12. `tests/stdlib/parse_module_test.lm` (SIGSEGV -11)
13. `tests/stdlib/format_module_test.lm` (SIGSEGV -11)
14. `tests/stdlib/semver_test.lm` (SIGSEGV -11)
15. `tests/stdlib/uuid_test.lm` (SIGSEGV -11)
16. `tests/stdlib/net/net_test.lm` (SIGSEGV -11)

#### D. Hung Tests (`HANG` - 1 Test)
1. `tests/stdlib/iterator_module_test.lm` (Exceeded runtime timeout limit)

---

### 2. Windows Target (x86_64 PE)

#### A. Succeeded Tests (`PASS` - 31 Tests)
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
30. `tests/basic/variables.lm`
31. `tests/types/unions.lm`

#### B. Output Mismatches (`MISMATCH` - 31 Tests)
1. `tests/basic/print_statements.lm`
2. `tests/basic/list_dict_tuple.lm`
3. `tests/expressions/arithmetic.lm`
4. `tests/expressions/scientific_notation.lm`
5. `tests/strings/interpolation.lm`
6. `tests/strings/operations.lm`
7. `tests/types/basic.lm`
8. `tests/modules/basic_import_test.lm`
9. `tests/modules/comprehensive_module_test.lm`
10. `tests/modules/show_filter_test.lm`
11. `tests/modules/hide_filter_test.lm`
12. `tests/modules/module_caching_test.lm`
13. `tests/modules/alias_import_test.lm`
14. `tests/modules/multiple_imports_test.lm`
15. `tests/oop/traits_dynamic.lm`
16. `tests/stdlib/core/string_test.lm`
17. `tests/stdlib/core_module_test.lm`
18. `tests/stdlib/collections/queue_stack_test.lm`
19. `tests/stdlib/collections/priority_queue_test.lm`
20. `tests/stdlib/collections_module_test.lm`
21. `tests/stdlib/string_module_test.lm`
22. `tests/stdlib/unicode_module_test.lm`
23. `tests/stdlib/regex_module_test.lm`
24. `tests/stdlib/time_module_test.lm`
25. `tests/stdlib/format_module_test.lm`
26. `tests/stdlib/path/path_test.lm`
27. `tests/stdlib/url_test.lm`
28. `tests/stdlib/mime_test.lm`
29. `tests/types/advanced.lm`
30. `tests/types/enums.lm`
31. `tests/types/refined_types.lm`

#### C. Runtime Failures (`RUNTIME_FAIL` - 17 Tests)
1. `tests/basic/literals.lm`
2. `tests/expressions/large_literals.lm`
3. `tests/loops/match.lm`
4. `tests/loops/match_advanced.lm`
5. `tests/functions/advanced.lm`
6. `tests/functions/closures.lm`
7. `tests/functions/first_class.lm`
8. `tests/concurrency/parallel_blocks.lm`
9. `tests/concurrency/concurrent_blocks.lm`
10. `tests/stdlib/algorithm_module_test.lm`
11. `tests/stdlib/math_module_test.lm`
12. `tests/stdlib/random_module_test.lm`
13. `tests/stdlib/parse_module_test.lm`
14. `tests/stdlib/sort/sort_test.lm`
15. `tests/stdlib/semver_test.lm`
16. `tests/stdlib/uuid_test.lm`
17. `tests/stdlib/net/net_test.lm`

#### D. Hung Tests (`HANG` - 1 Test)
1. `tests/stdlib/iterator_module_test.lm` (Exceeded runtime limit)

---

## Technical Root Cause Analysis of AOT Compiler Deficiencies

1. **Float Packing & Constant Literal Formatting**:
   - **Root Cause**: `src/backend/fyra/builder.cpp` previously created 16-byte global string headers (`str_hdr_X`) for double literal values and set `data_ptr` to offset +24 (out of bounds memory). At runtime, when printed via string formatting (`lm_rt_str_format`), `data_ptr` read out-of-bounds null bytes, producing empty outputs. Furthermore, in `src/lir/generator/expressions.cpp`, string interpolation `STR_FORMAT` omitted argument type propagation, defaulting operand type `type_b` to integer instead of float.
   - **Fix**:
     1. Updated `STR_FORMAT` emission in `src/lir/generator/expressions.cpp` to correctly record and pass `type_b` from argument language types.
     2. Refactored `src/backend/fyra/builder.cpp` to pass global string pointers directly without redundant extra string headers, and to call `emit_float_to_str_inline` for floating-point operands.
2. **Closure Environment Allocation**:
   - Dynamic functions and closures require passing env pointers in registers.
3. **Dictionary Key Iteration Order**:
   - VM interpreter hash bucket order differs from AOT memory address order.
4. **Threading & Concurrency**:
   - OS-specific wrapper stubs are needed for `pthread` and WinAPI worker threads.
