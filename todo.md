# AOT Test Suite Results (`tests/build_tests.py`)

## Summary
- **Total tests:** 80
- **Passed:** 22
- **Failed:** 58 (0 Build Failures, 32 Runtime Failures/Crashes, 25 Output Mismatches, 1 Timeout)

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

16. [ ] `tests/strings/interpolation.lm` - Output Mismatch: Format template placeholder substitution output diff.
17. [ ] `tests/strings/operations.lm` - Output Mismatch: Substring/replace string operations format diff.
18. [ ] `tests/strings/simple_string_test.lm` - Output Mismatch: Basic string format output diff.
19. [ ] `tests/strings/string_runtime_test.lm` - Output Mismatch: String runtime format output diff.
20. [ ] `tests/strings/lstring_api_test.lm` - Output Mismatch: Limit string API format output diff.
21. [x] `tests/strings/test_string_interpolation.lm` - PASS
22. [ ] `tests/stdlib/format_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in string format helper).
23. [ ] `tests/stdlib/string_module_test.lm` - Output Mismatch: String module helper function output diff.
24. [ ] `tests/stdlib/parse_module_test.lm` - Output Mismatch: String parsing helper output diff.
25. [ ] `tests/stdlib/unicode_module_test.lm` - Output Mismatch: Unicode rune string output diff.
26. [ ] `tests/stdlib/mime_test.lm` - Output Mismatch: MIME string parsing output diff.

---

### Category 4: Module Import & Variable Scoping (Moderate - Codegen & Globals)
*Reason:* Global variable scoping and module symbol relocation in AOT generated executables.

27. [ ] `tests/modules/basic_import_test.lm` - Output Mismatch: Imported function call print output diff.
28. [ ] `tests/modules/alias_import_test.lm` - Output Mismatch: Alias import symbol resolution output diff.
29. [ ] `tests/modules/comprehensive_module_test.lm` - Output Mismatch: Comprehensive module symbol resolution diff.
30. [x] `tests/modules/function_params_test.lm` - PASS
31. [ ] `tests/modules/hide_filter_test.lm` - Output Mismatch: Module filter export output diff.
32. [ ] `tests/modules/module_caching_test.lm` - Output Mismatch: Module caching symbol resolution output diff.
33. [ ] `tests/modules/multiple_imports_test.lm` - Output Mismatch: Multiple module import symbol resolution output diff.
34. [ ] `tests/modules/show_filter_test.lm` - Output Mismatch: Show filter export output diff.

---

### Category 5: Pattern Matching & Enums (Hard - Control Flow & Data Layout)
*Reason:* Enum tag and payload layout in Fyra IR branch lowering.

35. [ ] `tests/loops/match.lm` - Output Mismatch: Pattern match branch output diff.
36. [ ] `tests/loops/match_advanced.lm` - Output Mismatch: Advanced pattern match branch output diff.
37. [ ] `tests/types/basic.lm` - Output Mismatch: Basic type check output diff.
38. [ ] `tests/types/enums.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in enum tag dispatch).
39. [ ] `tests/types/options.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in Option unwrap).
40. [ ] `tests/types/advanced.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in structural type dispatch).
41. [ ] `tests/types/refined_types.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in refined type assertion).
42. [ ] `tests/types/structural_type_tests.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in structural type matching).
43. [ ] `tests/types/unions.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in union type dispatch).

---

### Category 6: OOP & Frame Field Lowering (Hard - Memory & Vtables)
*Reason:* Frame field offset calculations and dynamic trait/method dispatch.

44. [ ] `tests/oop/frame_declaration.lm` - Output Mismatch: Frame instance field access output diff.
45. [ ] `tests/oop/composition_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in composed frame access).
46. [ ] `tests/oop/traits_dynamic.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in dynamic trait dispatch).
47. [ ] `tests/oop/traits_inheritance.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in trait inheritance dispatch).
48. [ ] `tests/oop/visibility_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in frame visibility check).
49. [ ] `tests/regression/trait_dispatch_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in trait vtable dispatch).

---

### Category 7: Standard Library Collections & Algorithms (Hard - Memory Allocation & Collections)
*Reason:* Dynamic array reallocation and list/dict/tuple memory layout in Fyra IR runtime functions.

50. [ ] `tests/stdlib/collections/list_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in list append/get).
51. [ ] `tests/stdlib/collections/vector_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in vector resize).
52. [ ] `tests/stdlib/collections/arraylist_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in arraylist).
53. [ ] `tests/stdlib/collections/queue_stack_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in queue/stack push/pop).
54. [ ] `tests/stdlib/collections/queue_stack_bitset_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in bitset operations).
55. [ ] `tests/stdlib/collections/priority_queue_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in priority queue heapify).
56. [ ] `tests/stdlib/collections_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in collections module).
57. [ ] `tests/stdlib/algorithm_module_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in algorithm sort/search).
58. [ ] `tests/stdlib/sort/sort_test.lm` - Runtime Failure: `Exit code: -11` (SIGSEGV in sorting algorithm).

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
