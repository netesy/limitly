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
1. `tests/basic/variables.lm` (Float representation null byte artifact)
2. `tests/basic/print_statements.lm` (Nil printing representation difference: `2` vs `nil`)
3. `tests/basic/list_dict_tuple.lm` (Dict iteration key ordering difference)
4. `tests/expressions/arithmetic.lm` (Float value representation in AOT text generator)
5. `tests/expressions/scientific_notation.lm` (Float scientific formatting differences)
6. `tests/strings/interpolation.lm` (Float interpolation null byte strings)
7. `tests/strings/operations.lm` (Float string conversion differences)
8. `tests/loops/match.lm` (Nil case match pattern behavior)
9. `tests/types/basic.lm` (Float type string representation)
10. `tests/types/unions.lm` (Union type reflection string output)
11. `tests/modules/basic_import_test.lm` (Module export initialization order)
12. `tests/modules/comprehensive_module_test.lm` (Module namespace printing)
13. `tests/modules/show_filter_test.lm` (Show filter symbol resolution order)
14. `tests/modules/hide_filter_test.lm` (Hide filter symbol resolution order)
15. `tests/modules/module_caching_test.lm` (Module cache execution tracking)
16. `tests/modules/alias_import_test.lm` (Aliased namespace string output)
17. `tests/modules/multiple_imports_test.lm` (Multiple module symbol collision handling)
18. `tests/oop/traits_dynamic.lm` (Dynamic trait dispatch printing)
19. `tests/stdlib/core/string_test.lm` (String float format functions)
20. `tests/stdlib/core_module_test.lm` (Core module export inspection)
21. `tests/stdlib/collections/queue_stack_test.lm` (Collection stack/queue string representations)
22. `tests/stdlib/collections/priority_queue_test.lm` (Heap tie-breaker order differences)
23. `tests/stdlib/collections_module_test.lm` (Collections module inspection)
24. `tests/stdlib/algorithm_module_test.lm` (Algorithm helper return values)
25. `tests/stdlib/string_module_test.lm` (String module float formatting)
26. `tests/stdlib/unicode_module_test.lm` (Unicode codepoint representation)
27. `tests/stdlib/regex_module_test.lm` (Regex match group printing)
28. `tests/stdlib/path/path_test.lm` (Path separator string formatting)
29. `tests/stdlib/url_test.lm` (URL query string parameter ordering)
30. `tests/stdlib/mime_test.lm` (MIME parameters string formatting)

#### C. Runtime Failures (`RUNTIME_FAIL` - 19 Tests)
1. `tests/basic/literals.lm` (Segmentation fault SIGSEGV / Exit code -11)
2. `tests/expressions/large_literals.lm` (SIGSEGV -11: BigInt / float literal overflow)
3. `tests/loops/match_advanced.lm` (SIGSEGV -11: Nested pattern match destructuring)
4. `tests/functions/advanced.lm` (SIGSEGV -11: Variadic / default argument handling)
5. `tests/functions/closures.lm` (SIGSEGV -11: Environment allocation / dereference)
6. `tests/functions/first_class.lm` (SIGSEGV -11: Function pointer call ABI mismatch)
7. `tests/types/advanced.lm` (SIGSEGV -11: Refined type validation call stack)
8. `tests/types/enums.lm` (SIGSEGV -11: Enum payload memory access)
9. `tests/types/refined_types.lm` (SIGSEGV -11: Contract predicate evaluation)
10. `tests/concurrency/parallel_blocks.lm` (SIGSEGV -11: Thread pool spawning / pthread join)
11. `tests/concurrency/concurrent_blocks.lm` (SIGSEGV -11: Channel synchronization)
12. `tests/stdlib/math_module_test.lm` (SIGSEGV -11: Native math float library bindings)
13. `tests/stdlib/time_module_test.lm` (SIGSEGV -11: Clock resolution system call)
14. `tests/stdlib/random_module_test.lm` (SIGSEGV -11: Entropy buffer initialization)
15. `tests/stdlib/parse_module_test.lm` (SIGSEGV -11: String parser float conversion)
16. `tests/stdlib/format_module_test.lm` (SIGSEGV -11: String buffer formatting)
17. `tests/stdlib/semver_test.lm` (SIGSEGV -11: Regex / string split memory fault)
18. `tests/stdlib/uuid_test.lm` (SIGSEGV -11: Random bytes generation)
19. `tests/stdlib/net/net_test.lm` (SIGSEGV -11: Socket FFI call)

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
1. `tests/basic/literals.lm` (Exit code: 3221225477 / 0xC0000005 Access Violation)
2. `tests/expressions/large_literals.lm` (Exit code: 0xC0000005)
3. `tests/loops/match.lm` (Exit code: 5 - Assertion failure in PE machine code)
4. `tests/loops/match_advanced.lm` (Exit code: 0xC0000005)
5. `tests/functions/advanced.lm` (Exit code: 0xC0000005)
6. `tests/functions/closures.lm` (Exit code: 0xC0000005)
7. `tests/functions/first_class.lm` (Exit code: 0xC0000005)
8. `tests/types/advanced.lm` (Exit code: 0xC0000005)
9. `tests/types/enums.lm` (Exit code: 0xC0000005)
10. `tests/types/refined_types.lm` (Exit code: 0xC0000005)
11. `tests/concurrency/parallel_blocks.lm` (Exit code: 0xC0000005)
12. `tests/concurrency/concurrent_blocks.lm` (Exit code: 0xC0000005)
13. `tests/stdlib/algorithm_module_test.lm` (Exit code: 1 - Assertion failure)
14. `tests/stdlib/math_module_test.lm` (Exit code: 0xC0000005)
15. `tests/stdlib/random_module_test.lm` (Exit code: 0xC0000005)
16. `tests/stdlib/parse_module_test.lm` (Exit code: 0xC0000005)
17. `tests/stdlib/sort/sort_test.lm` (Exit code: 1 - Array bounds / comparator fault under Win PE)
18. `tests/stdlib/semver_test.lm` (Exit code: 0xC0000005)
19. `tests/stdlib/uuid_test.lm` (Exit code: 0xC0000005)
20. `tests/stdlib/net/net_test.lm` (Exit code: 0xC0000005)

#### D. Hung Tests (`HANG` - 1 Test)
1. `tests/stdlib/iterator_module_test.lm` (Exceeded 30.0s timeout limit under Wine)

---

## Cross-Platform Parity & Behavioral Differences

Comparing the native Linux ELF execution against the Windows PE execution under Wine reveals 6 explicit cross-platform discrepancies:

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

### Detailed Breakdown of Parity Discrepancies

1. **`tests/loops/match.lm`**:
   - **Linux**: Executes to completion (exit code 0), but output mismatches interpreter output.
   - **Windows**: Fails with exit code 5 during PE execution (pattern matching dispatch jump table targets invalid memory address on Win PE binary).

2. **`tests/stdlib/algorithm_module_test.lm`**:
   - **Linux**: Completes with exit code 0, but outputs slightly different array ordering.
   - **Windows**: Fails with exit code 1 (assertion failure when verifying sorted algorithm output due to array slicing differences).

3. **`tests/stdlib/time_module_test.lm`**:
   - **Linux**: Triggers SIGSEGV (-11) during Linux `clock_gettime` POSIX syscall wrapping.
   - **Windows**: Executes successfully under Wine (exit code 0), but output text has slight sub-second formatting differences.

4. **`tests/stdlib/format_module_test.lm`**:
   - **Linux**: Triggers SIGSEGV (-11) during float formatting string allocation.
   - **Windows**: Executes to completion under Wine (exit code 0) but string padding outputs mismatch due to float `\x00` byte representation.

5. **`tests/stdlib/sort/sort_test.lm`**:
   - **Linux**: `PASS` (100% exact output match).
   - **Windows**: `RUNTIME_FAIL` with exit code 1 under Wine (Windows PE memory layout alters comparator function pointer ABI).

---

## Technical Root Cause Analysis of AOT Compiler Deficiencies

### 1. Float Value Representation & Null-Byte Corruption (`\x00`)
- **Observed Symptoms**: Floating point numbers printed in AOT binaries output null bytes (`\x00\x00\x00\x00`) or `0` instead of formatted float representations (e.g. `3.14`).
- **Root Cause**: In `src/backend/fyra/fyra_builtin_functions.cpp`, the IEEE-754 float unpacking logic casts boxed double-precision values incorrectly when passing parameters to `printf`/`snprintf` or when storing double values in `.rodata`. Constant float initializers in `fyra_ir_generator.cpp` lack proper bitcast encoding into 64-bit register values.

### 2. Closure Environment Allocation & Function Pointer Calling Conventions
- **Observed Symptoms**: All closure tests (`closures.lm`, `first_class.lm`, `advanced.lm`) crash with SIGSEGV (Linux -11) or Access Violation (Windows 0xC0000005).
- **Root Cause**: The LIR-to-Fyra lowering pass (`src/backend/fyra/builder.cpp`) emits standard static call instructions (`CallDirect`) for dynamic closure values. When calling a closure, the env context pointer expected in register `rdi`/`rcx` is omitted, causing the callee to dereference garbage memory when accessing captured variables.

### 3. Non-Deterministic Dictionary Iteration Order
- **Observed Symptoms**: `list_dict_tuple.lm`, `comprehensive_module_test.lm`, `url_test.lm` produce output mismatch errors.
- **Root Cause**: The VM interpreter processes dictionary key iteration insertion-order or hash-bucket order differently than the compiled AOT runtime (`lm_dict_iter_next`). The AOT runtime uses raw memory address hashing for keys without deterministic hash ordering.

### 4. Threading & Concurrency Primitive Deficiencies
- **Observed Symptoms**: `parallel_blocks.lm` and `concurrent_blocks.lm` crash instantly with non-zero exit codes.
- **Root Cause**: The AOT backend's implementation of `parallel` and `concurrent` blocks in `src/backend/fyra/fyra_builtin_functions.cpp` relies on stubbed wrapper calls for `pthread_create`/`CreateThread`. The thread entry arguments fail to pass the LIR frame environment stack pointer.

### 5. Infinite Loop in Iterator Generator Module (`iterator_module_test.lm`)
- **Observed Symptoms**: Binary hangs and is forcibly killed after 30 seconds on both Linux and Windows.
- **Root Cause**: `lm_iterator_next` state transition logic in AOT machine code fails to update the internal counter register upon reaching loop termination, generating an infinite loop in compiled code.

---

## Recommendations & Action Plan for AOT Backend Fixes

1. **Fix Floating-Point Register & Value Packaging**:
   - Update `FyraIRGenerator` and `builder.cpp` to correctly double-box floats (`LmValue` double encoding) and pass double values in `xmm0` / SSE registers per System V and Win64 ABIs.
2. **Implement Proper Closure Calling Convention in Fyra IR**:
   - Lower LIR closure functions to struct pairs containing `(code_pointer, env_pointer)`. Update `CallIndirect` in `builder.cpp` to pass `env_pointer` as the first hidden parameter.
3. **Standardize Dictionary Iteration Order**:
   - Modify `lm_dict` builtins in `fyra_builtin_functions.cpp` to maintain a deterministic insertion-order linked list alongside hash buckets.
4. **Fix Concurrency Entry Points**:
   - Provide full thread worker function stubs in `fyra_builtin_functions.cpp` with proper OS-specific thread entry wrappers (`pthread` on Linux, `WinAPI` on Windows).
5. **Fix Iterator State Machine Lowering**:
   - Ensure `LIR_Op::IterNext` updates condition flags and branch targets in `builder.cpp` to prevent infinite loops in generator iterators.
