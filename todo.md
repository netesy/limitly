# AOT Test Suite Results (`tests/build_tests.py`)

## Summary
- **Total tests:** 80
- **Passed:** 41
- **Failed:** 39 (0 Build Failures, 26 Runtime Failures/Crashes, 12 Output Mismatches, 1 Timeout)

---

## Completed / Passing Tests (`[x]`)

- [x] `tests/basic/literals.lm` - PASS
- [x] `tests/expressions/logical.lm` - PASS
- [x] `tests/loops/for_loops.lm` - PASS
- [x] `tests/loops/while_loops.lm` - PASS
- [x] `tests/stdlib/search/search_test.lm` - PASS
- [x] `tests/stdlib/range/range_test.lm` - PASS
- [x] `tests/basic/print_statements.lm` - PASS
- [x] `tests/basic/variables.lm` - PASS
- [x] `tests/basic/control_flow.lm` - PASS
- [x] `tests/expressions/arithmetic.lm` - PASS
- [x] `tests/expressions/large_literals.lm` - PASS
- [x] `tests/expressions/scientific_notation.lm` - PASS
- [x] `tests/functions/basic.lm` - PASS
- [x] `tests/stdlib/core/math_test.lm` - PASS
- [x] `tests/stdlib/crypto/hash_test.lm` - PASS
- [x] `tests/basic/list_dict_tuple.lm` - PASS
- [x] `tests/expressions/ranges.lm` - PASS
- [x] `tests/functions/first_class.lm` - PASS
- [x] `tests/regression/ownership_refactor_test.lm` - PASS
- [x] `tests/stdlib/net/net_test.lm` - PASS
- [x] `tests/stdlib/path/path_test.lm` - PASS
- [x] `tests/strings/interpolation.lm` - PASS
- [x] `tests/strings/operations.lm` - PASS
- [x] `tests/strings/simple_string_test.lm` - PASS
- [x] `tests/strings/string_runtime_test.lm` - PASS
- [x] `tests/strings/lstring_api_test.lm` - PASS
- [x] `tests/loops/match.lm` - PASS
- [x] `tests/loops/match_advanced.lm` - PASS
- [x] `tests/types/basic.lm` - PASS
- [x] `tests/types/enums.lm` - PASS
- [x] `tests/types/options.lm` - PASS
- [x] `tests/types/advanced.lm` - PASS
- [x] `tests/types/refined_types.lm` - PASS
- [x] `tests/types/structural_type_tests.lm` - PASS
- [x] `tests/types/unions.lm` - PASS
- [x] `tests/oop/frame_declaration.lm` - PASS
- [x] `tests/oop/composition_test.lm` - PASS
- [x] `tests/oop/traits_inheritance.lm` - PASS
- [x] `tests/oop/visibility_test.lm` - PASS
- [x] `tests/regression/trait_dispatch_test.lm` - PASS

---

## Failing Tests (`[ ]`) - Ranked by Ease of Fix

### Category 1: Newline Character Output Differences (Easiest - Print formatting & newline alignment)
*Reason:* In string print statements, newlines or spaces are appended with vertical tab / non-standard newline byte representation instead of standard `\n`.

1. [x] `tests/basic/print_statements.lm` - PASS
2. [x] `tests/basic/variables.lm` - PASS
3. [x] `tests/basic/control_flow.lm` - PASS
4. [x] `tests/expressions/arithmetic.lm` - PASS
5. [x] `tests/expressions/large_literals.lm` - PASS
6. [x] `tests/expressions/scientific_notation.lm` - PASS
7. [x] `tests/functions/basic.lm` - PASS
8. [x] `tests/stdlib/core/math_test.lm` - PASS
9. [x] `tests/stdlib/crypto/hash_test.lm` - PASS

---

### Category 2: Multiple Print Arguments & Tuple/List Inlining (Easy - Print handling)
*Reason:* `print(a, b, c)` statement lowering in `builder.cpp` handles single register arguments cleanly, but multi-argument calls or list/tuple register printing require pointer dereference fixes.

10. [x] `tests/basic/list_dict_tuple.lm` - PASS
11. [x] `tests/expressions/ranges.lm` - PASS
12. [x] `tests/functions/first_class.lm` - PASS
13. [x] `tests/regression/ownership_refactor_test.lm` - PASS
14. [x] `tests/stdlib/net/net_test.lm` - PASS
15. [x] `tests/stdlib/path/path_test.lm` - PASS

---

### Category 3: String Interpolation & Format Module (Moderate - String Formatting)
*Reason:* `STR_FORMAT` and `lm_rt_str_format` dynamic template string substitution for multi-variable placeholders.

16. [x] `tests/strings/interpolation.lm` - PASS
17. [x] `tests/strings/operations.lm` - PASS
18. [x] `tests/strings/simple_string_test.lm` - PASS
19. [x] `tests/strings/string_runtime_test.lm` - PASS
20. [x] `tests/strings/lstring_api_test.lm` - PASS
21. [x] `tests/strings/test_string_interpolation.lm` - PASS
22. [ ] `tests/stdlib/format_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in string format helper).
23. [ ] `tests/stdlib/string_module_test.lm` - Output Mismatch: String module helper function output diff.
24. [ ] `tests/stdlib/parse_module_test.lm` - Output Mismatch: String parsing helper output diff.
25. [ ] `tests/stdlib/unicode_module_test.lm` - Output Mismatch: Unicode rune string output diff.
26. [ ] `tests/stdlib/mime_test.lm` - Output Mismatch: MIME string parsing output diff.

---

### Category 4: Module Import & Variable Scoping (Moderate - Codegen & Globals)
*Reason:* Global variable scoping and module symbol relocation in AOT generated executables.

27. [x] `tests/modules/basic_import_test.lm` - PASS
28. [x] `tests/modules/alias_import_test.lm` - PASS
29. [x] `tests/modules/comprehensive_module_test.lm` - PASS
30. [x] `tests/modules/function_params_test.lm` - PASS
31. [x] `tests/modules/hide_filter_test.lm` - PASS
32. [x] `tests/modules/module_caching_test.lm` - PASS
33. [x] `tests/modules/multiple_imports_test.lm` - PASS
34. [x] `tests/modules/show_filter_test.lm` - PASS

---

### Category 5: Pattern Matching & Enums (Hard - Control Flow & Data Layout)
*Reason:* Enum tag and payload layout in Fyra IR branch lowering.

35. [x] `tests/loops/match.lm` - PASS
36. [x] `tests/loops/match_advanced.lm` - PASS
37. [x] `tests/types/basic.lm` - PASS
38. [x] `tests/types/enums.lm` - PASS
39. [x] `tests/types/options.lm` - PASS
40. [x] `tests/types/advanced.lm` - PASS
41. [x] `tests/types/refined_types.lm` - PASS
42. [x] `tests/types/structural_type_tests.lm` - PASS
43. [x] `tests/types/unions.lm` - PASS

---

### Category 6: OOP & Frame Field Lowering (Hard - Memory & Vtables)
*Reason:* Frame field offset calculations and dynamic trait/method dispatch.

44. [x] `tests/oop/frame_declaration.lm` - PASS
45. [x] `tests/oop/composition_test.lm` - PASS
46. [ ] `tests/oop/traits_dynamic.lm` - Output Mismatch: Dynamic trait dispatch output diff.
47. [x] `tests/oop/traits_inheritance.lm` - PASS
48. [x] `tests/oop/visibility_test.lm` - PASS
49. [x] `tests/regression/trait_dispatch_test.lm` - PASS

---

### Category 7: Standard Library Collections & Algorithms (Hard - Memory Allocation & Collections)
*Reason:* Dynamic array reallocation and list/dict/tuple memory layout in Fyra IR runtime functions.

50. [ ] `tests/stdlib/collections/list_test.lm` - Output Mismatch: List operation diff.
51. [ ] `tests/stdlib/collections/vector_test.lm` - Output Mismatch: Vector operation diff.
52. [ ] `tests/stdlib/collections/arraylist_test.lm` - Output Mismatch: ArrayList operation diff.
53. [ ] `tests/stdlib/collections/queue_stack_test.lm` - Output Mismatch: Queue/Stack operation diff.
54. [ ] `tests/stdlib/collections/queue_stack_bitset_test.lm` - Output Mismatch: BitSet operation diff.
55. [ ] `tests/stdlib/collections/priority_queue_test.lm` - Output Mismatch: PriorityQueue operation diff.
56. [ ] `tests/stdlib/collections_module_test.lm` - Output Mismatch: Collections module operation diff.
57. [ ] `tests/stdlib/algorithm_module_test.lm` - Output Mismatch: Algorithm module operation diff.
58. [ ] `tests/stdlib/sort/sort_test.lm` - Output Mismatch: Sorting algorithm operation diff.

---

### Category 8: Standard Library System & Specialized Modules (Hard - Complex Runtime)
*Reason:* Complex stdlib module dependencies, thread/timer scheduling, and external system calls.

59. [ ] `tests/stdlib/core_module_test.lm` - Output Mismatch: Core module helper function output diff.
60. [ ] `tests/stdlib/core/string_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in core string utilities).
61. [ ] `tests/stdlib/core/option_result_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in option/result monad methods).
62. [ ] `tests/stdlib/core/string_option_result_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in string option/result helpers).
63. [ ] `tests/stdlib/iterator/iterator_test.lm` - PASS (Included in passing tests above).
64. [ ] `tests/stdlib/iterator_module_test.lm` - Timeout: Exceeded maximum runtime of 30 seconds.
65. [ ] `tests/stdlib/math_module_test.lm` - Runtime Failure: `Exit code: -8` (SIGFPE arithmetic exception).
66. [ ] `tests/stdlib/env_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in environment variable access).
67. [ ] `tests/stdlib/process_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in sub-process execution).
68. [ ] `tests/stdlib/time_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in time/timer functions).
69. [ ] `tests/stdlib/random_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in random generator frame).
70. [ ] `tests/stdlib/semver_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in semver parser).
71. [ ] `tests/stdlib/url_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in URL parser).
72. [ ] `tests/stdlib/uuid_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in UUID generator).
73. [ ] `tests/stdlib/regex_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in regex engine).
74. [ ] `tests/concurrency/concurrent_blocks.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in thread spawn).
75. [ ] `tests/concurrency/parallel_blocks.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in parallel thread join).
