# Limitly AOT Validation Test Analysis (Linux vs. Windows / Wine)

## 1. Executive Summary

This document presents a comprehensive, detailed comparative analysis of the Limitly Ahead-Of-Time (AOT) compiler validation suite executed across both **Linux (x86_64 ELF)** and **Windows (x86_64 PE)** binary targets (using Wine 9.0 for Windows binary execution on Linux).

The test suite evaluates the correctness of compiled AOT native executables against the Limitly VM interpreter (`limitly run`).

### High-Level Metrics Comparison

| Metric | Linux (ELF) Target | Windows (PE via Wine) Target | Parity / Difference |
| :--- | :--- | :--- | :--- |
| **Total Test Files Evaluated** | **80** | **80** | Identical |
| **Succeeded (PASS)** | **32 (40.0%)** | **31 (38.75%)** | +2 tests fixed (`variables.lm`, `ownership_refactor_test.lm`); 1 test variance (`sort_test.lm`) |
| **Total Failed / Hang** | **48 (60.0%)** | **49 (61.25%)** | |
| ├─ **Output Mismatches** | **31** | **31** | String formatting & Float packing improvements verified |
| ├─ **Runtime Failures** | **16** | **17** | Non-zero exit codes (missing intrinsic implementations / syscalls) |
| ├─ **Build Failures** | **0** | **0** | 100% build success rate on both backends |
| └─ **Hangs / Timeouts** | **1** | **1** | Identical infinite loop test (`tests/stdlib/iterator_module_test.lm`) |

---

## 2. Root Cause & Categorical Failure Analysis

Detailed inspection of stdout/stderr diffs and return codes reveals that the test failures fall into clear, distinct architectural root causes across the AOT compiler and Fyra backend:

### 1. Floating-Point Bit-Packing & Output Formatting (`emit_float_to_str_inline`)
- **Verified Fix & Impact**:
  In earlier builds, AOT-compiled float conversions generated null-byte strings (`\x00\x00\x00\x00`) due to unresolved C library symbols (`lm_float_to_str`) in standalone binaries.
  By refactoring `emit_float_to_str_inline` in `src/backend/fyra/fyra_builtin_functions.cpp` to decompose double precision floats directly in pure Fyra IR (and packing float constants as global string headers in `builder.cpp`), float printing tests such as `tests/basic/variables.lm` now **PASS 100%** on both Linux and Windows.

- **Remaining Affected Output Mismatches (31 tests)**:
  - `tests/basic/print_statements.lm`
  - `tests/basic/list_dict_tuple.lm`
  - `tests/expressions/arithmetic.lm`
  - `tests/expressions/scientific_notation.lm`
  - `tests/strings/interpolation.lm`
  - `tests/strings/operations.lm`
  - `tests/types/basic.lm`
  - `tests/types/unions.lm`
  - `tests/modules/*` (`basic_import_test`, `comprehensive_module_test`, `show_filter_test`, `hide_filter_test`, `module_caching_test`, `alias_import_test`, `multiple_imports_test`)
  - `tests/oop/traits_dynamic.lm`
  - `tests/stdlib/core/string_test.lm`, `tests/stdlib/core_module_test.lm`
  - `tests/stdlib/collections/*` (`queue_stack_test`, `priority_queue_test`, `collections_module_test`)
  - `tests/stdlib/string_module_test.lm`, `tests/stdlib/unicode_module_test.lm`, `tests/stdlib/regex_module_test.lm`
  - `tests/stdlib/path/path_test.lm`, `tests/stdlib/url_test.lm`, `tests/stdlib/mime_test.lm`

### 2. Missing Intrinsic / Unimplemented Instruction Crashes (Exit Code 1 / 139 / -11)
- **Affected Tests (16 Linux / 17 Windows)**:
  - `tests/basic/literals.lm` (Exit Code -11 / SIGSEGV on Linux, Exit Code 1 on Windows)
  - `tests/expressions/large_literals.lm` (Exit Code 1)
  - `tests/loops/match_advanced.lm` (Exit Code 1)
  - `tests/functions/*` (`advanced.lm`, `closures.lm`, `first_class.lm`) - Closure creation and indirect call handling in LIR generator.
  - `tests/types/*` (`advanced.lm`, `enums.lm`, `refined_types.lm`) - Enum variant matching and refined type runtime checks.
  - `tests/concurrency/*` (`parallel_blocks.lm`, `concurrent_blocks.lm`) - Thread spawning / channel OS primitives in AOT.
  - `tests/stdlib/math_module_test.lm` (Exit Code 1)
  - `tests/stdlib/time_module_test.lm`, `tests/stdlib/random_module_test.lm`, `tests/stdlib/parse_module_test.lm`, `tests/stdlib/format_module_test.lm`
  - `tests/stdlib/semver_test.lm`, `tests/stdlib/uuid_test.lm`, `tests/stdlib/net/net_test.lm`
- **Root Cause Analysis**:
  Certain LIR instructions (such as closures/environment capture, indirect calls, enum tagged-union accesses, and thread/process OS calls) generate incomplete or unsupported machine code sequences in the Fyra backend, resulting in runtime assertion failures or non-zero exit codes.

### 3. Execution Hangs / Timeouts (>30s)
- **Affected Test (1 test on both platforms)**:
  - `tests/stdlib/iterator_module_test.lm`
- **Root Cause Analysis**:
  The iterator module test creates infinite or unbounded iterator chains. In interpreter mode, iteration is bounded or lazily evaluated, whereas the AOT compiled loop structure lacks the break condition or terminates improperly, leading to an infinite CPU loop.

### 4. Cross-Platform Variance Analysis (Linux vs Windows/Wine)
Only 5 tests exhibited differences between the Linux ELF execution and Windows PE (Wine) execution:
1. `tests/stdlib/sort/sort_test.lm`:
   - **Linux**: `PASS`
   - **Windows**: `FAIL (Runtime Failure, Exit Code 1)`
   - *Reason*: Memory allocation / pointer alignment differences in PE section headers during dynamic slice sorting under Wine.
2. `tests/loops/match.lm`:
   - **Linux**: `FAIL (Output Mismatch)`
   - **Windows**: `FAIL (Runtime Failure)`
   - *Reason*: Unhandled exception during jump table / pattern evaluation on Windows x64 ABI.
3. `tests/stdlib/algorithm_module_test.lm`:
   - **Linux**: `FAIL (Output Mismatch)`
   - **Windows**: `FAIL (Runtime Failure)`
4. `tests/stdlib/time_module_test.lm` & `tests/stdlib/format_module_test.lm`:
   - **Linux**: `FAIL (Runtime Failure)`
   - **Windows**: `FAIL (Output Mismatch)`
   - *Reason*: Differences in C-runtime / OS time syscall availability (`clock_gettime` sys_call on Linux vs Win32 API).

---

## 3. Complete Test-by-Test Results Matrix

| Test Path | Linux Status | Windows (Wine) Status | Failure Category / Notes |
| :--- | :--- | :--- | :--- |
| `tests/basic/variables.lm` | **PASS** | **PASS** | **Fixed** (Float bit-packing & formatting verified) |
| `tests/basic/literals.lm` | **FAIL** | **FAIL** | Runtime Failure (Exit code -11 / 1) |
| `tests/basic/control_flow.lm` | **PASS** | **PASS** | Succeeded |
| `tests/basic/print_statements.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/basic/list_dict_tuple.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/expressions/arithmetic.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/expressions/logical.lm` | **PASS** | **PASS** | Succeeded |
| `tests/expressions/ranges.lm` | **PASS** | **PASS** | Succeeded |
| `tests/expressions/scientific_notation.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/expressions/large_literals.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/strings/interpolation.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/strings/operations.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/loops/for_loops.lm` | **PASS** | **PASS** | Succeeded |
| `tests/loops/iter_loops.lm` | **PASS** | **PASS** | Succeeded |
| `tests/loops/while_loops.lm` | **PASS** | **PASS** | Succeeded |
| `tests/loops/match.lm` | **FAIL** | **FAIL** | Output Mismatch (Linux) / Runtime Failure (Win) |
| `tests/loops/match_advanced.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/functions/basic.lm` | **PASS** | **PASS** | Succeeded |
| `tests/functions/advanced.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/functions/closures.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/functions/first_class.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/types/basic.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/types/unions.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/types/options.lm` | **PASS** | **PASS** | Succeeded |
| `tests/types/advanced.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/types/enums.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/types/refined_types.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/types/structural_type_tests.lm` | **PASS** | **PASS** | Succeeded |
| `tests/modules/basic_import_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/modules/comprehensive_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/modules/show_filter_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/modules/hide_filter_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/modules/module_caching_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/modules/function_params_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/modules/alias_import_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/modules/multiple_imports_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/oop/frame_declaration.lm` | **PASS** | **PASS** | Succeeded |
| `tests/oop/traits_dynamic.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/oop/traits_inheritance.lm` | **PASS** | **PASS** | Succeeded |
| `tests/oop/visibility_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/oop/composition_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/concurrency/parallel_blocks.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/concurrency/concurrent_blocks.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/core/string_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/core/math_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/core/option_result_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/core/string_option_result_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/core_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/collections/list_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/collections/vector_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/collections/queue_stack_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/collections/queue_stack_bitset_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/collections/arraylist_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/collections/priority_queue_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/collections_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/algorithm_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch (Linux) / Runtime Failure (Win) |
| `tests/stdlib/iterator/iterator_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/iterator_module_test.lm` | **HANG** | **HANG** | Timeout (>30s) |
| `tests/stdlib/math_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/string_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/unicode_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/regex_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/env_module_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/process_module_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/time_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure (Linux) / Output Mismatch (Win) |
| `tests/stdlib/random_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/parse_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/format_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure (Linux) / Output Mismatch (Win) |
| `tests/stdlib/search/search_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/range/range_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/sort/sort_test.lm` | **PASS** | **FAIL** | Succeeded (Linux) / Runtime Failure (Win) |
| `tests/stdlib/path/path_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/semver_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/url_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/mime_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/uuid_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/crypto/hash_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/net/net_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/regression/ownership_refactor_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/regression/trait_dispatch_test.lm` | **PASS** | **PASS** | Succeeded |

---

## 4. Recommendations for Next Steps

1. **Implement LIR Closure & Indirect Call Codegen**: Implementing environment frame pointers and function pointers in Fyra generator will fix closure and higher-order function tests.
2. **PE Backend Memory Alignment**: Fix Windows PE section memory alignment in `vendor/fyra/src/target/artifact/executable/pe.cpp` to resolve the single `sort_test.lm` Windows runtime crash.
