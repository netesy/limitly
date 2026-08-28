# Limitly AOT Compiler Documentation & Test Baseline

## Overview

The Limitly AOT compiler converts Limitly Low-Level Intermediate Representation (LIR) into target machine code via the vendored **Fyra** IR and code generator.

---

## Fresh Test Results (Linux Native Execution)

Run Date: Final Post-Fix Verification

- **PASS**: 39
- **MISMATCH**: 20
- **RUNTIME_FAIL**: 19
- **TIMEOUT**: 1 (`tests/stdlib/iterator_module_test.lm`)
- **TOTAL EXECUTED**: 79
- **SKIPPED**: 0 (all test files in suite present and executed)

*Note: Windows/Wine execution could not be verified directly as `wine` is not installed in the Linux sandbox environment. Linux builds and executable generation were verified.*

---

## Key Root Causes & Audit Findings (Resolved Defect Summary)

1. **Stack Slot Allocation Placement in Inline Formatting Functions**:
   - **Root Cause**: `createAlloc` calls in `FyraBuiltinFunctions::emit_int_to_str_inline` and `emit_decimal_to_str_inline` were inserting alloc instructions inside loop/conditional basic blocks rather than the function's entry basic block.
   - **Fix**: Moved `createAlloc` for temporary pointers (`v_cur_ptr`, `v_val`, `v_is_neg`, `copy_idx_d`, etc.) into `entry_bb`. Corrected stack frame offset calculations and eliminated SIGSEGV crash during decimal formatting in `tests/basic/literals.lm`.

2. **Parameter Store Address vs Value Generation in x64 Codegen**:
   - **Root Cause**: In `vendor/fyra/src/target/architecture/x64/X64Architecture.cpp`, `emitStore` checked `dynamic_cast<ir::GlobalValue*>`, which matched `ir::Parameter*`. This caused parameter store operations to emit `leaq -0x30(%rbp), %rax` (taking the address of the parameter stack slot) instead of `movq -0x30(%rbp), %rax` (reading the parameter value).
   - **Fix**: Added `dynamic_cast<ir::Parameter*>(i.getOperands()[0]->get()) == nullptr` to exclude function parameters from global address generation in `X64Architecture.cpp`.

3. **Floating-Point Parameter Passing & Global Variable Type Inference**:
   - **Root Cause**: Function signatures created in Fyra IR defaulted parameter types to `i64`, causing x64 System V `emitCall` to pass float arguments in integer registers (`%rdi`, `%rsi`) instead of float registers (`%xmm0`, `%xmm1`). Pre-scanning also failed to inspect instructions to infer global float types during `StoreGlobal`.
   - **Fix**: Added parameter type inspection to assign `DoubleType` for float parameters in `builder.cpp` and updated `emitCall` / `emitFunctionPrologue` in `X64Architecture.cpp` to correctly route float arguments to `%xmm` registers.

4. **x64 Call Return Store Syntax & Stack Alignment**:
   - **Root Cause**: `emitCall` in `X64Architecture.cpp` printed Intel syntax `mov -0x50(%rbp), rax` for System V AT&T mode, which reversed operands and overwrote `%rax` with stack garbage upon returning from calls. Additionally, stack allocation alignment math was subtracting an extra 8 bytes.
   - **Fix**: Corrected return value store in `X64Architecture.cpp` to `movq %rax, -0x50(%rbp)` for System V AT&T mode and adjusted stack alignment math to ensure strict 16-byte alignment of `%rsp`.

5. **`CallIndirect` Closure ABI Dispatch**:
   - **Root Cause**: In `src/backend/fyra/builder.cpp`, indirect closure calls matched target functions using parameter count heuristics (`target_param_cnt == args.size() + 1`).
   - **Fix**: Replaced parameter count heuristics with exact inspection of `LIR_Function::variable_to_reg` for `__env`. Updated argument packing to pass `callee` environment tuple pointer for closure functions and null for direct string function calls. Verified all 7 closure test suites in `tests/functions/closures.lm` pass 100%.

6. **Pointer Equality (`CmpEQ` / `CmpNEQ`)**:
   - **Audit Result**: Operand registers marked with `LIR::Type::Ptr` route through `lm_key_eq`. `lm_key_eq_ffi` checks fast pointer equality (`k1 == k2`), and falls back to `lm_value_eq` for string header content comparison (`strcmp`) and unboxed values while preserving primitive pointer speed.

---

## Failure Classification Summary (Remaining 40 Failures)

### Group A — Complex Frame Field & Unboxed Alignment (19 Runtime Failures)
- `tests/basic/literals.lm` (decimal format assertion), `tests/concurrency/parallel_blocks.lm`, `tests/concurrency/concurrent_blocks.lm`, `tests/stdlib/core/option_result_test.lm`, `tests/stdlib/core_module_test.lm`, `tests/stdlib/collections/priority_queue_test.lm`, `tests/stdlib/collections_module_test.lm`, `tests/stdlib/algorithm_module_test.lm`, `tests/stdlib/math_module_test.lm`, `tests/stdlib/string_module_test.lm`, `tests/stdlib/unicode_module_test.lm`, `tests/stdlib/regex_module_test.lm`, `tests/stdlib/process_module_test.lm`, `tests/stdlib/time_module_test.lm`, `tests/stdlib/random_module_test.lm`, `tests/stdlib/parse_module_test.lm`, `tests/stdlib/url_test.lm`, `tests/stdlib/mime_test.lm`, `tests/stdlib/uuid_test.lm`:
- **Classification**: Complex struct frame field indexing / unboxed value alignment in stdlib modules requiring deeper frame layout metadata lowerings.

### Group B — Formatting / Nondeterministic Output Mismatches (20 Mismatches)
- `tests/basic/print_statements.lm`, `tests/basic/list_dict_tuple.lm`, `tests/expressions/arithmetic.lm`, `tests/expressions/scientific_notation.lm`, `tests/expressions/large_literals.lm`, `tests/strings/interpolation.lm`, `tests/strings/operations.lm`, `tests/loops/match.lm`, `tests/loops/match_advanced.lm`, `tests/functions/advanced.lm`, `tests/types/basic.lm`, `tests/types/advanced.lm`, `tests/types/enums.lm`, `tests/types/refined_types.lm`, `tests/modules/comprehensive_module_test.lm`, `tests/modules/show_filter_test.lm`, `tests/modules/hide_filter_test.lm`, `tests/modules/module_caching_test.lm`, `tests/oop/traits_dynamic.lm`, `tests/stdlib/format_module_test.lm`:
- **Classification**: String formatting, float printing representation differences, or match construct string formatting discrepancies vs interpreter.

### Group C — Infra / Execution Timeout (1 Timeout)
- `tests/stdlib/iterator_module_test.lm`: Exceeds 30 second limit due to extensive iteration loops.

---

## Clean Verification Commands

```bash
make clean
make -j$(nproc)
git diff --check
./tests/run_aot_tests.sh
```
