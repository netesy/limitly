# Limitly AOT Compiler Documentation & Test Baseline

## Overview

The Limitly AOT compiler converts Limitly Low-Level Intermediate Representation (LIR) into target machine code via the vendored **Fyra** IR and code generator.

---

## Fresh Test Results (Linux Native Execution)

Run Date: Current Fresh Run

- **PASS**: 48
- **MISMATCH**: 20
- **RUNTIME_FAIL**: 11
- **HANG (Timeout)**: 1
- **TOTAL**: 80

*Note: Windows/Wine execution could not be verified directly as `wine` is not installed in the Linux sandbox environment. Linux builds and PE executable generation were verified.*

---

## Key Root Causes & Architectural Fixes Applied

1. **Closure Lambda Environment Passing (`builder.cpp`)**:
   - Fixed parameter allocation and argument ordering for indirect calls (`CallIndirect`) to lambda functions expecting environment tuples (`r0`).
2. **Boxed Callee Unboxing (`builder.cpp`)**:
   - Added unboxing logic for `CallIndirect` when `raw_callee` is a boxed value (`TYPE_BOX = 13`), resolving function dispatch crashes.
3. **String Value Equality (`lm_key_eq` in `fyra_builtin_functions.cpp`)**:
   - Fixed string equality comparison to handle both `LmStringHeader` structs (`type_id == 11`) and raw null-terminated C-strings, resolving string comparison false negatives in `path_test.lm` and `string_module_test.lm`.
4. **Portability Header Guards (`fyra_builtin_functions.cpp`)**:
   - Guarded Windows-specific headers (`<windows.h>`, `IsBadReadPtr`) with `#ifdef _WIN32` for Linux builds.
5. **Float Representation Invariants**:
   - Enforced native IEEE-754 double precision (`ir::Type::getDoubleType()`) across `LoadConst`, arithmetic, comparisons, and formatting.

---

## Submodule & Repository Verification

- **Limitly Working Tree**: Clean
- **Fyra Working Tree (`vendor/fyra`)**: Clean (Commit: `21aa057`)
- **Clean Build**: Verified (`make clean && make -j4`)
- **git diff --check**: Passed
