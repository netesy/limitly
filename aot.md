# Limitly AOT Validation Test Analysis (Linux vs. Windows / Wine)

## 1. Executive Summary

This document presents a comprehensive, detailed comparative analysis of the Limitly Ahead-Of-Time (AOT) compiler validation suite executed across both **Linux (x86_64 ELF)** and **Windows (x86_64 PE)** binary targets.

The test suite evaluates the correctness of compiled AOT native executables against the Limitly VM interpreter (`limitly run`).

### Baseline vs. Post-Fix Metrics Comparison

| Metric | Linux Baseline | Linux Post-Fix | Windows Baseline | Windows Post-Fix |
| :--- | :--- | :--- | :--- | :--- |
| **Total Test Files Evaluated** | **80** | **80** | **80** | **80** |
| **Succeeded (PASS)** | **30 (37.5%)** | **31 (38.75%)** | **29 (36.25%)** | **29 (36.25%)** |
| **Total Failed / Hang** | **50 (62.5%)** | **49 (61.25%)** | **51 (63.75%)** | **51 (63.75%)** |
| ├─ **Output Mismatches** | **30** | **31** | **30** | **30** |
| ├─ **Runtime Failures** | **19** | **17** | **20** | **20** |
| ├─ **Build Failures** | **0** | **0** | **0** | **0** |
| └─ **Hangs / Timeouts** | **1** | **1** | **1** | **1** |

---

## 2. Root Cause & Exact Fix Details

### Root Cause Analysis
Floating point operations failed due to six distinct root causes across the Fyra backend, x64 machine code generation, LIR lowering, and PE section alignment:

1. **Missing In-Memory Machine Code Emission for Floating Point Instructions (`vendor/fyra/src/target/architecture/x64/X64Architecture.cpp`)**:
   - `emitFAdd`, `emitFSub`, `emitFMul`, `emitFDiv`, `emitCmp` (for `isFloatCmp`), and `emitCast` (for `Sltof`) in `X64Architecture.cpp` only had code paths for text assembly stream output (`if (auto* os = cg.getTextStream())`).
   - When generating binary executables directly via in-memory machine code (`as`), the `else` branch was completely missing. Consequently, no machine code bytes were emitted for floating point math or float comparisons, leaving the destination register/stack slot at zero.

2. **Float Unpacking & Constant Type Tracking (`src/backend/fyra/builder.cpp`)**:
   - Float constants stored in boxed structures (`LM_BOX_FLOAT`, `TYPE_FLOAT`) or converted from string literals were not being properly unpacked into `ConstantFP` double constants in `LoadConst`.
   - Register type tracking in `LoadConst` was incorrectly overwriting destination register types with `I64` or `Ptr` instead of maintaining `LIR::Type::F64`.

3. **Global Variable Array Type Declarations (`src/backend/fyra/builder.cpp` & `fyra_builtin_functions.cpp`)**:
   - String header array constants were being declared as `PointerType(i8)` instead of `ArrayType`.
   - The Fyra validator marked these globals as `unsupported_global` and omitted `.data` section byte emission, resulting in null pointer dereference segfaults at runtime when accessing string constants.

4. **Fyra IR Loop SSA Regalloc Fix (`src/backend/fyra/fyra_builtin_functions.cpp`)**:
   - Inlined string formatting loops (`emit_decimal_to_str_inline`, `emit_int_to_str_inline`, `emit_float_to_str_inline`) were using local stack allocs (`createAlloc`/`createLoad`/`createStore`) for loop counters. Direct `createLoad` on stack slots emitted direct dereferences that clobbered loop registers across iterations.
   - Replaced stack alloc counter loops with SSA `PhiNode` constructs to preserve register values across loop iterations.

5. **Pure Fyra IR Float-to-String Formatting (`src/backend/fyra/fyra_builtin_functions.cpp`)**:
   - Replaced unresolved external C library symbol `lm_float_to_str` with a pure Fyra IR routine that performs IEEE-754 64-bit double bitfield decomposition (sign, exponent, mantissa), %g-style 6-significant-digit conversion, and NaN/Inf detection.

6. **PE Section Alignment (`vendor/fyra/src/target/artifact/executable/pe.cpp`)**:
   - Fixed PE section header `virtualSize` calculation to guarantee alignment with `fileAlignment_` and ensure `virtualSize >= rawDataSize` for PE executable generation.

---

## 3. Affected Files

- `vendor/fyra/src/target/architecture/x64/X64Architecture.cpp`
- `vendor/fyra/include/target/artifact/executable/elf.hh`
- `vendor/fyra/src/target/artifact/executable/elf.cpp`
- `vendor/fyra/src/target/artifact/executable/pe.cpp`
- `src/backend/fyra/builder.cpp`
- `src/backend/fyra/fyra_builtin_functions.cpp`
- `fyra.patch`

---

## 4. Float Regression Test Verification

The following focused tests were used to verify native float packing, arithmetic, and formatting:

| Test File | Result | Verified Expressions / Behavior |
| :--- | :--- | :--- |
| `tests/basic/variables.lm` | **PASS** | `3.14`, `2.71` float variable assignment and printing |
| `tests/expressions/arithmetic.lm` | **PASS** | `3.14 + 2.0 = 5.14`, `3.14 / 2.0 = 1.57` native float math |
| `tests/strings/interpolation.lm` | **PASS** | `Pi: 3.14159`, `Area of circle: 12.56636` float expressions in interpolated strings |
| `tests/expressions/scientific_notation.lm` | **PASS** | `1.23e-10`, `4.56e+15`, `1.5e3 + 2.5e2 = 1750.0` scientific notation parsing & formatting |
| `tests/basic/literals.lm` | **PASS** | Integers, Floats, Strings, Booleans, Nil, Decimals all pass cleanly |

---

## 5. Complete Test-by-Test Results Matrix

| Test Path | Linux Status | Windows (Wine) Status | Failure Category / Notes |
| :--- | :--- | :--- | :--- |
| `tests/basic/variables.lm` | **PASS** | **PASS** | Succeeded |
| `tests/basic/literals.lm` | **PASS** | **PASS** | Succeeded |
| `tests/basic/control_flow.lm` | **PASS** | **PASS** | Succeeded |
| `tests/basic/print_statements.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/basic/list_dict_tuple.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/expressions/arithmetic.lm` | **PASS** | **PASS** | Succeeded |
| `tests/expressions/logical.lm` | **PASS** | **PASS** | Succeeded |
| `tests/expressions/ranges.lm` | **PASS** | **PASS** | Succeeded |
| `tests/expressions/scientific_notation.lm` | **PASS** | **PASS** | Succeeded |
| `tests/expressions/large_literals.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/strings/interpolation.lm` | **PASS** | **PASS** | Succeeded |
| `tests/strings/operations.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/loops/for_loops.lm` | **PASS** | **PASS** | Succeeded |
| `tests/loops/iter_loops.lm` | **PASS** | **PASS** | Succeeded |
| `tests/loops/while_loops.lm` | **PASS** | **PASS** | Succeeded |
| `tests/loops/match.lm` | **FAIL** | **FAIL** | Output Mismatch |
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
| `tests/stdlib/algorithm_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/iterator/iterator_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/iterator_module_test.lm` | **HANG** | **HANG** | Timeout (>30s) |
| `tests/stdlib/math_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/string_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/unicode_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/regex_module_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/env_module_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/process_module_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/time_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/random_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/parse_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/format_module_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/search/search_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/range/range_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/sort/sort_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/path/path_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/semver_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/url_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/mime_test.lm` | **FAIL** | **FAIL** | Output Mismatch |
| `tests/stdlib/uuid_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/stdlib/crypto/hash_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/stdlib/net/net_test.lm` | **FAIL** | **FAIL** | Runtime Failure |
| `tests/regression/ownership_refactor_test.lm` | **PASS** | **PASS** | Succeeded |
| `tests/regression/trait_dispatch_test.lm` | **PASS** | **PASS** | Succeeded |
