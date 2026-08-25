# AOT Test Suite Results (`tests/build_tests.py`)

## Summary
- **Total tests:** 80
- **Passed:** 34
- **Failed:** 46
  - **Runtime Failures (Crashes):** 19
  - **Output Mismatches:** 26
  - **Timeouts:** 1
  - **Build Failures:** 0

---

## Completed / Passing Tests (`[x]`)

1. [x] `tests/basic/variables.lm` - PASS
2. [x] `tests/basic/literals.lm` - PASS
3. [x] `tests/basic/control_flow.lm` - PASS
4. [x] `tests/expressions/arithmetic.lm` - PASS
5. [x] `tests/expressions/logical.lm` - PASS
6. [x] `tests/expressions/ranges.lm` - PASS
7. [x] `tests/expressions/scientific_notation.lm` - PASS
8. [x] `tests/expressions/large_literals.lm` - PASS
9. [x] `tests/strings/interpolation.lm` - PASS
10. [x] `tests/loops/for_loops.lm` - PASS
11. [x] `tests/loops/iter_loops.lm` - PASS
12. [x] `tests/loops/match.lm` - PASS
13. [x] `tests/loops/while_loops.lm` - PASS
14. [x] `tests/functions/basic.lm` - PASS
15. [x] `tests/functions/closures.lm` - PASS
16. [x] `tests/functions/first_class.lm` - PASS
17. [x] `tests/types/basic.lm` - PASS
18. [x] `tests/types/unions.lm` - PASS
19. [x] `tests/types/options.lm` - PASS
20. [x] `tests/types/advanced.lm` - PASS
21. [x] `tests/types/enums.lm` - PASS
22. [x] `tests/types/structural_type_tests.lm` - PASS
23. [x] `tests/modules/function_params_test.lm` - PASS
24. [x] `tests/oop/frame_declaration.lm` - PASS
25. [x] `tests/oop/traits_inheritance.lm` - PASS
26. [x] `tests/oop/visibility_test.lm` - PASS
27. [x] `tests/oop/composition_test.lm` - PASS
28. [x] `tests/stdlib/core/math_test.lm` - PASS
29. [x] `tests/stdlib/core/option_result_test.lm` - PASS
30. [x] `tests/stdlib/core/string_option_result_test.lm` - PASS
31. [x] `tests/stdlib/collections/list_test.lm` - PASS
32. [x] `tests/stdlib/collections/vector_test.lm` - PASS
33. [x] `tests/stdlib/collections/queue_stack_bitset_test.lm` - PASS
34. [x] `tests/stdlib/collections/arraylist_test.lm` - PASS
35. [x] `tests/stdlib/iterator/iterator_test.lm` - PASS
36. [x] `tests/stdlib/env_module_test.lm` - PASS
37. [x] `tests/stdlib/process_module_test.lm` - PASS
38. [x] `tests/stdlib/search/search_test.lm` - PASS
39. [x] `tests/stdlib/range/range_test.lm` - PASS
40. [x] `tests/stdlib/sort/sort_test.lm` - PASS
41. [x] `tests/stdlib/crypto/hash_test.lm` - PASS
42. [x] `tests/regression/ownership_refactor_test.lm` - PASS
43. [x] `tests/regression/trait_dispatch_test.lm` - PASS

---

## Failing Tests (`[ ]`)

### Category 1: Runtime Failures (SIGSEGV / Arithmetic Exceptions)

1. [ ] `tests/loops/match_advanced.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
6. [ ] `tests/types/refined_types.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
7. [ ] `tests/modules/basic_import_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
8. [ ] `tests/modules/comprehensive_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
9. [ ] `tests/modules/show_filter_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
10. [ ] `tests/modules/hide_filter_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
11. [ ] `tests/modules/module_caching_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
12. [ ] `tests/modules/multiple_imports_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
13. [ ] `tests/concurrency/parallel_blocks.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
14. [ ] `tests/concurrency/concurrent_blocks.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
15. [ ] `tests/stdlib/math_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
16. [ ] `tests/stdlib/time_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
17. [ ] `tests/stdlib/random_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
18. [ ] `tests/stdlib/parse_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
19. [ ] `tests/stdlib/format_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
20. [ ] `tests/stdlib/semver_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
21. [ ] `tests/stdlib/uuid_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
22. [ ] `tests/stdlib/net/net_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).

---

### Category 2: Standard Output / Standard Error Mismatches

23. [ ] `tests/basic/print_statements.lm` - Output Mismatch.
24. [ ] `tests/basic/list_dict_tuple.lm` - Output Mismatch.
25. [ ] `tests/strings/operations.lm` - Output Mismatch.
26. [ ] `tests/functions/advanced.lm` - Output Mismatch.
27. [ ] `tests/modules/alias_import_test.lm` - Output Mismatch.
28. [ ] `tests/oop/traits_dynamic.lm` - Output Mismatch.
29. [ ] `tests/stdlib/core/string_test.lm` - Output Mismatch.
30. [ ] `tests/stdlib/core_module_test.lm` - Output Mismatch.
31. [ ] `tests/stdlib/collections/queue_stack_test.lm` - Output Mismatch.
32. [ ] `tests/stdlib/collections/priority_queue_test.lm` - Output Mismatch.
33. [ ] `tests/stdlib/collections_module_test.lm` - Output Mismatch.
34. [ ] `tests/stdlib/algorithm_module_test.lm` - Output Mismatch.
35. [ ] `tests/stdlib/string_module_test.lm` - Output Mismatch.
36. [ ] `tests/stdlib/unicode_module_test.lm` - Output Mismatch.
37. [ ] `tests/stdlib/regex_module_test.lm` - Output Mismatch.
38. [ ] `tests/stdlib/path/path_test.lm` - Output Mismatch.
39. [ ] `tests/stdlib/url_test.lm` - Output Mismatch.
40. [ ] `tests/stdlib/mime_test.lm` - Output Mismatch.

---

### Category 3: Timeouts (> 30s Execution)

41. [ ] `tests/stdlib/iterator_module_test.lm` - Timeout: Executable exceeded maximum runtime of 30 seconds.
