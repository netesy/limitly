# Limitly AOT Compiler Documentation & Test Baseline

## Overview

The Limitly AOT compiler converts Limitly Low-Level Intermediate Representation (LIR) into target machine code via the vendored **Fyra** IR and code generator.

---

## Fresh Test Results (Linux Native Execution)

Run Date: Current Verified Baseline

- **PASS**: 49
- **MISMATCH**: 21
- **RUNTIME_FAIL**: 9
- **TIMEOUT**: 0
- **TOTAL**: 79 executed (1 skipped due to interpreter timeout)

*Note: Windows/Wine execution could not be verified directly as `wine` is not installed in the Linux sandbox environment. Linux builds and executable generation were verified.*

---

## Key Root Causes & Audit Findings

1. **`CallIndirect` Closure Dispatch & ABI**:
   - Signature generation in `src/lir/generator/core.cpp` appends `__env` for closures.
   - Fyra builder in `src/backend/fyra/builder.cpp` checks `target_param_cnt == args.size() + 1` and passes `callee` as the environment parameter.

2. **Primitive Integer vs Heap String Equality (`CmpEQ` / `CmpNEQ`)**:
   - Fixed string header equality comparison in `src/backend/fyra/builder.cpp`: previously, dynamic strings (from `split`, `substring`, `ListIndex`, etc.) failed `reg_string_literals.count()`, falling through to primitive pointer address comparison.
   - Updated `CmpEQ`/`CmpNEQ` to route operand registers with `LIR::Type::Ptr` through `lm_key_eq`, which safely compares string contents or unboxed value representations while retaining primitive integer speed.

3. **Dynamic String-to-Integer Cast**:
   - Fixed `LIR_Op::Cast` in `src/backend/fyra/builder.cpp`: added dynamic header type check (`TYPE_STRING = 11`) to invoke `emit_str_to_int_inline` when casting dynamic string headers to integers (e.g. `part as int` in `std.net.dns`).

4. **Decimal Scale Resolution**:
   - Enhanced `LIR_Op::DecRescale` in `src/backend/fyra/builder.cpp` to look up decimal scale from `lir_func.register_language_types` when `reg_decimal_scales` lacks local scale info.

---

## Failure Classification Summary (Remaining 30 Failures)

### Group A — Backend Codegen / Type Pre-scanning Gaps
- `tests/stdlib/math_module_test.lm` & `tests/stdlib/random_module_test.lm`: Global double constant type propagation in `__init__` routines.
- `tests/stdlib/collections_module_test.lm`, `tests/stdlib/time_module_test.lm`, `tests/stdlib/parse_module_test.lm`, `tests/stdlib/regex_module_test.lm`: Complex frame field indexing / unboxed value alignment in stdlib modules.

### Group B — Existing Language / Runtime Issues
- `tests/stdlib/format_module_test.lm`: `printf_template` formatting discrepancy.
- `tests/concurrency/*`: Async fiber / channel scheduling differences in AOT native binaries.

### Group C — Environment / Test Infra Issues
- `tests/stdlib/collections/queue_stack_bitset_test.lm`: Skipped due to interpreter timing out before AOT execution.

---

## Verification

- **Clean Build**: Verified (`make clean && make -j$(nproc)`)
- **git diff --check**: Passed
