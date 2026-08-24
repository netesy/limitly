# AOT Test Suite Results (`tests/build_tests.py`)

## Summary
- **Total tests:** 80
- **Passed:** 30
- **Failed:** 50
  - **Runtime Failures (Crashes):** 31
  - **Output Mismatches:** 18
  - **Timeouts:** 1
  - **Build Failures:** 0

---

## Completed / Passing Tests (`[x]`)

1. [x] `tests/basic/control_flow.lm` - PASS
2. [x] `tests/expressions/logical.lm` - PASS
3. [x] `tests/expressions/ranges.lm` - PASS
4. [x] `tests/loops/for_loops.lm` - PASS
5. [x] `tests/loops/iter_loops.lm` - PASS
6. [x] `tests/loops/while_loops.lm` - PASS
7. [x] `tests/functions/basic.lm` - PASS
8. [x] `tests/types/options.lm` - PASS
9. [x] `tests/types/structural_type_tests.lm` - PASS
10. [x] `tests/modules/function_params_test.lm` - PASS
11. [x] `tests/oop/frame_declaration.lm` - PASS
12. [x] `tests/oop/traits_inheritance.lm` - PASS
13. [x] `tests/oop/visibility_test.lm` - PASS
14. [x] `tests/oop/composition_test.lm` - PASS
15. [x] `tests/stdlib/core/math_test.lm` - PASS
16. [x] `tests/stdlib/core/option_result_test.lm` - PASS
17. [x] `tests/stdlib/core/string_option_result_test.lm` - PASS
18. [x] `tests/stdlib/collections/list_test.lm` - PASS
19. [x] `tests/stdlib/collections/vector_test.lm` - PASS
20. [x] `tests/stdlib/collections/queue_stack_bitset_test.lm` - PASS
21. [x] `tests/stdlib/collections/arraylist_test.lm` - PASS
22. [x] `tests/stdlib/iterator/iterator_test.lm` - PASS
23. [x] `tests/stdlib/env_module_test.lm` - PASS
24. [x] `tests/stdlib/process_module_test.lm` - PASS
25. [x] `tests/stdlib/search/search_test.lm` - PASS
26. [x] `tests/stdlib/range/range_test.lm` - PASS
27. [x] `tests/stdlib/sort/sort_test.lm` - PASS
28. [x] `tests/stdlib/crypto/hash_test.lm` - PASS
29. [x] `tests/regression/ownership_refactor_test.lm` - PASS
30. [x] `tests/regression/trait_dispatch_test.lm` - PASS

---

## Failing Tests (`[ ]`)

### Category 1: Runtime Failures (SIGSEGV / Arithmetic Exceptions)

1. [ ] `tests/basic/variables.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
2. [ ] `tests/basic/literals.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
3. [ ] `tests/expressions/arithmetic.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
4. [ ] `tests/expressions/scientific_notation.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
5. [ ] `tests/expressions/large_literals.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
6. [ ] `tests/strings/interpolation.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
7. [ ] `tests/loops/match.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
8. [ ] `tests/loops/match_advanced.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
9. [ ] `tests/functions/closures.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
10. [ ] `tests/functions/first_class.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
11. [ ] `tests/types/basic.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
12. [ ] `tests/types/unions.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
13. [ ] `tests/types/advanced.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
14. [ ] `tests/types/enums.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
15. [ ] `tests/types/refined_types.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
16. [ ] `tests/modules/basic_import_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
17. [ ] `tests/modules/comprehensive_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
18. [ ] `tests/modules/show_filter_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
19. [ ] `tests/modules/hide_filter_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
20. [ ] `tests/modules/module_caching_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
21. [ ] `tests/modules/multiple_imports_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
22. [ ] `tests/concurrency/parallel_blocks.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
23. [ ] `tests/concurrency/concurrent_blocks.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
24. [ ] `tests/stdlib/math_module_test.lm` - Runtime Failure: `Exit code: -8` (SIGFPE arithmetic exception).
25. [ ] `tests/stdlib/time_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
26. [ ] `tests/stdlib/random_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
27. [ ] `tests/stdlib/parse_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
28. [ ] `tests/stdlib/format_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
29. [ ] `tests/stdlib/semver_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
30. [ ] `tests/stdlib/uuid_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).
31. [ ] `tests/stdlib/net/net_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV).

---

### Category 2: Standard Output / Standard Error Mismatches

32. [ ] `tests/basic/print_statements.lm` - Output Mismatch: Standard output mismatch (e.g. `2` printed for `nil`).
33. [ ] `tests/basic/list_dict_tuple.lm` - Output Mismatch: Standard output mismatch.
34. [ ] `tests/strings/operations.lm` - Output Mismatch: Standard output mismatch.
35. [ ] `tests/functions/advanced.lm` - Output Mismatch: Standard output mismatch.
36. [ ] `tests/modules/alias_import_test.lm` - Output Mismatch: Standard output mismatch.
37. [ ] `tests/oop/traits_dynamic.lm` - Output Mismatch: Standard output mismatch.
38. [ ] `tests/stdlib/core/string_test.lm` - Output Mismatch: Standard output mismatch.
39. [ ] `tests/stdlib/core_module_test.lm` - Output Mismatch: Standard output mismatch.
40. [ ] `tests/stdlib/collections/queue_stack_test.lm` - Output Mismatch: Standard output mismatch.
41. [ ] `tests/stdlib/collections/priority_queue_test.lm` - Output Mismatch: Standard output mismatch.
42. [ ] `tests/stdlib/collections_module_test.lm` - Output Mismatch: Standard output mismatch.
43. [ ] `tests/stdlib/algorithm_module_test.lm` - Output Mismatch: Standard output mismatch.
44. [ ] `tests/stdlib/string_module_test.lm` - Output Mismatch: Standard output mismatch.
45. [ ] `tests/stdlib/unicode_module_test.lm` - Output Mismatch: Standard output mismatch.
46. [ ] `tests/stdlib/regex_module_test.lm` - Output Mismatch: Standard output mismatch.
47. [ ] `tests/stdlib/path/path_test.lm` - Output Mismatch: Standard output mismatch.
48. [ ] `tests/stdlib/url_test.lm` - Output Mismatch: Standard output mismatch.
49. [ ] `tests/stdlib/mime_test.lm` - Output Mismatch: Standard output mismatch.

---

### Category 3: Timeouts (> 30s Execution)

50. [ ] `tests/stdlib/iterator_module_test.lm` - Timeout: Executable exceeded maximum runtime of 30 seconds.
