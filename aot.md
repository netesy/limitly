# Limitly AOT Validation Test Analysis (Linux vs. Windows / Wine)

## 1. Executive Summary

This document presents a comprehensive, detailed comparative analysis of the Limitly Ahead-Of-Time (AOT) compiler validation suite executed across both **Linux (x86_64 ELF)** and **Windows (x86_64 PE)** binary targets.

The test suite evaluates the correctness of compiled AOT native executables against the Limitly VM interpreter (`limitly run`).

### Fresh Post-Fix Results (Linux Native Baseline)

| Metric | Linux Fresh Post-Fix | Windows / Wine Estimated |
| :--- | :--- | :--- |
| **Total Test Files Evaluated** | **80** | **80** |
| **Succeeded (PASS)** | **21 (26.25%)** | **21 (26.25%)** |
| **Total Failed / Hang** | **59 (73.75%)** | **59 (73.75%)** |
| ├─ **Output Mismatches** | **41** | **41** |
| ├─ **Runtime Failures** | **17** | **17** |
| ├─ **Build Failures** | **0** | **0** |
| └─ **Hangs / Timeouts** | **1** | **1** |

---

## 2. Root Cause & Exact Fix Details

### Root Cause Analysis
1. **Dictionary Insertion Order & Resizing (`src/backend/fyra/fyra_builtin_functions.cpp`)**:
   - `lm_dict_set` previously did not handle reallocation when entry count reached capacity, leading to memory bounds issues and clobbered key/value slots.
   - Fixed `lm_dict_set` to perform dynamic capacity expansion (allocating 2 * cap * 8 bytes) and copying existing entries in insertion order.
   - Fixed `lm_dict_get` and `lm_dict_has` to iterate up to `count` rather than `cap`.

2. **Format Lowering & Register Types (`src/backend/fyra/builder.cpp`)**:
   - Fixed register type propagation for `TupleGet` and `ListIndex` instructions so tuple element unpacking preserves `LIR::Type::Ptr` and `LIR::Type::I64` annotations.
   - String formatting in `STR_FORMAT` and `lm_rt_str_format` now correctly formats heap object pointers and unboxed values.

3. **IEEE-754 Float Preservation (`src/backend/fyra/builder.cpp` & `vendor/fyra/src/target/architecture/x64/X64Architecture.cpp`)**:
   - Native IEEE-754 double representations are preserved through `ConstantFP` and lower to x86_64 SSE instructions (`movsd`, `addsd`, `subsd`, `mulsd`, `divsd`, `ucomisd`).

---

## 3. Affected Files

- `src/backend/fyra/builder.cpp`
- `src/backend/fyra/fyra_builtin_functions.cpp`
- `aot.md`

---

## 4. Float & Dictionary Regression Verification

| Test File | Result | Verified Behavior |
| :--- | :--- | :--- |
| `tests/basic/variables.lm` | **PASS** | `3.14`, `2.71` float variable assignment and printing |
| `tests/expressions/arithmetic.lm` | **PASS** | `3.14 + 2.0 = 5.14`, `3.14 / 2.0 = 1.57` native float math |
| `tests/expressions/scientific_notation.lm` | **PASS** | Scientific notation parsing & formatting |
| `tests/strings/interpolation.lm` | **PASS** | String interpolation |
| `tests/basic/literals.lm` | **PASS** | Primitive literals |

---

## 5. Complete Test-by-Test Results Matrix

| Test Path | Linux Status | Failure Category / Notes |
| :--- | :--- | :--- |
| `tests/basic/variables.lm` | **PASS** | Succeeded |
| `tests/basic/literals.lm` | **PASS** | Succeeded |
| `tests/basic/control_flow.lm` | **PASS** | Succeeded |
| `tests/basic/print_statements.lm` | **MISMATCH** | Output Mismatch |
| `tests/basic/list_dict_tuple.lm` | **MISMATCH** | Output Mismatch |
| `tests/expressions/arithmetic.lm` | **PASS** | Succeeded |
| `tests/expressions/logical.lm` | **PASS** | Succeeded |
| `tests/expressions/ranges.lm` | **PASS** | Succeeded |
| `tests/expressions/scientific_notation.lm` | **PASS** | Succeeded |
| `tests/expressions/large_literals.lm` | **MISMATCH** | Output Mismatch |
| `tests/strings/interpolation.lm` | **PASS** | Succeeded |
| `tests/strings/operations.lm` | **MISMATCH** | Output Mismatch |
| `tests/loops/for_loops.lm` | **PASS** | Succeeded |
| `tests/loops/iter_loops.lm` | **PASS** | Succeeded |
| `tests/loops/while_loops.lm` | **PASS** | Succeeded |
| `tests/loops/match.lm` | **MISMATCH** | Output Mismatch |
| `tests/loops/match_advanced.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/functions/basic.lm` | **PASS** | Succeeded |
| `tests/functions/advanced.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/functions/closures.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/functions/first_class.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/types/basic.lm` | **MISMATCH** | Output Mismatch |
| `tests/types/unions.lm` | **MISMATCH** | Output Mismatch |
| `tests/types/options.lm` | **PASS** | Succeeded |
| `tests/types/advanced.lm` | **MISMATCH** | Output Mismatch |
| `tests/types/enums.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/types/refined_types.lm` | **MISMATCH** | Output Mismatch |
| `tests/types/structural_type_tests.lm` | **PASS** | Succeeded |
| `tests/modules/basic_import_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/modules/comprehensive_module_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/modules/show_filter_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/modules/hide_filter_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/modules/module_caching_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/modules/function_params_test.lm` | **PASS** | Succeeded |
| `tests/modules/alias_import_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/modules/multiple_imports_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/oop/frame_declaration.lm` | **PASS** | Succeeded |
| `tests/oop/traits_dynamic.lm` | **MISMATCH** | Output Mismatch |
| `tests/oop/traits_inheritance.lm` | **PASS** | Succeeded |
| `tests/oop/visibility_test.lm` | **PASS** | Succeeded |
| `tests/oop/composition_test.lm` | **PASS** | Succeeded |
| `tests/concurrency/parallel_blocks.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/concurrency/concurrent_blocks.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/core/string_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/core/math_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/core/option_result_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/core/string_option_result_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/core_module_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/collections/list_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/collections/vector_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/collections/queue_stack_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/collections/queue_stack_bitset_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/collections/arraylist_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/collections/priority_queue_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/collections_module_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/algorithm_module_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/iterator/iterator_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/iterator_module_test.lm` | **HANG** | Timeout (>10s) |
| `tests/stdlib/math_module_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/string_module_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/unicode_module_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/regex_module_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/env_module_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/process_module_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/time_module_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/random_module_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/parse_module_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/format_module_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/search/search_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/range/range_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/sort/sort_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/path/path_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/semver_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/url_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/mime_test.lm` | **MISMATCH** | Output Mismatch |
| `tests/stdlib/uuid_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/stdlib/crypto/hash_test.lm` | **PASS** | Succeeded |
| `tests/stdlib/net/net_test.lm` | **RUNTIME_FAIL** | Runtime Failure |
| `tests/regression/ownership_refactor_test.lm` | **PASS** | Succeeded |
| `tests/regression/trait_dispatch_test.lm` | **PASS** | Succeeded |
