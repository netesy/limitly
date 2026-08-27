# Limitly AOT Compiler Documentation & Test Baseline

## Overview

The Limitly AOT compiler converts Limitly Low-Level Intermediate Representation (LIR) into target machine code via the vendored **Fyra** IR and code generator.

---

## Fresh Test Results (Linux Native Execution)

Run Date: Current Verified Run

- **PASS**: 41
- **MISMATCH**: 31
- **RUNTIME_FAIL**: 7
- **HANG (Timeout)**: 1
- **TOTAL**: 80 (79 executed, 1 skipped timeout in harness)

*Note: Windows/Wine execution could not be verified directly as `wine` is not installed in the Linux sandbox environment. Linux builds and executable generation were verified.*

---

## Key Root Causes & Architectural Fixes Applied

1. **Primitive Value Representation & Integer Equality**:
   - Reverted invalid pointer heuristics (`>= 65536`, pointer alignment/bit tests) that were previously applied to primitive integers in `CmpEQ`/`CmpNEQ`.
   - Primitive integer comparisons now correctly use primitive integer IR instructions (`createCeq`/`createCne`), preserving fundamental language semantics.
   - `lm_key_eq_ffi` delegates safely to `lm_value_eq` for value equality comparison without dereferencing primitive integer values.

2. **Closure Environment Passing & CallIndirect Dispatch**:
   - Fixed LIR function signature generation for closures (`core.cpp`) to explicitly include the hidden environment parameter (`__env`).
   - Corrected `CallIndirect` dispatch in `builder.cpp` to inspect `callee` type representation (`TYPE_TUPLE` vs `TYPE_STRING`) and pass `callee` as the environment argument matching target parameter counts without relying on hardcoded `__lambda` name checks.

3. **Float Parameter & Global Variable Propagation**:
   - Fixed LIR function parameter ABI type mapping (`core.cpp`) so `F64` float parameters are declared as `F64` rather than defaulting to `I64`.
   - Pre-scanned global variable types in `builder.cpp` across reachable functions to preserve float representation across `StoreGlobal` and `LoadGlobal`.
   - Fixed type selection in `STR_FORMAT` to inspect register language types before applying fallback string conversions.

4. **Linux Build Portability**:
   - Retained `#ifdef _WIN32` guards around Windows-specific header inclusions (`<windows.h>`, `IsBadReadPtr`) in `fyra_builtin_functions.cpp`.

---

## Submodule & Repository Verification

- **Limitly Working Tree**: Modified (`aot.md`, `src/backend/fyra/builder.cpp`, `src/backend/fyra/fyra_builtin_functions.cpp`, `src/lir/generator/core.cpp`)
- **Fyra Working Tree (`vendor/fyra`)**: Clean
- **Clean Build**: Verified (`make clean && make -j$(nproc)`)
- **git diff --check**: Passed
