# Limitly Compiler: Negative Test Failures & Architectural Analysis

This document provides a comprehensive technical analysis of why certain negative tests (expected to fail compilation or execution with errors) currently succeed (exit with code 0) or produce unexpected results. It categorizes the architectural and implementation reasons for these behaviors in the Limitly compiler.

---

## 1. Bounds Checking
*   **Failing Tests:** `array_index_out_of_bounds.lm`, `large_negative_index.lm`, `negative_array_index.lm`, `string_bounds.lm`, `string_index_out_of_bounds.lm`
*   **Reason for Failure:** The runtime is designed to fail-safe by returning `nil` instead of crashing or throwing a hard exception.
*   **Implementation Detail:**
    In `src/runtime/runtime_list.c`:
    ```c
    RUNTIME_API LmValue lm_list_get(LmList* list, uint64_t index) {
        if (!list || index >= list->size) return VAL_NIL;
        return list->data[index];
    }
    ```
    Similarly, in `src/backend/vm/ops/collections.cpp`'s `ListIndex` implementation, any out-of-bounds or non-existent index safely resolves to `VAL_NIL` (`nil`) and continues execution with exit code `0`. Because the program does not raise a runtime error, the negative test framework (which expects a non-zero exit code or `bounds_error`) flags this as a failure.

---

## 2. Soundness / Move Semantics
*   **Failing Tests:** `double_move.lm`, `double_move_dict.lm`, `move_then_assign.lm`, `use_after_move.lm`, `use_after_move_dict.lm`
*   **Reason for Failure:** The static `MemoryChecker` adopts conservative borrowing assumptions and does not automatically track function parameter passing as complete ownership transfer (move).
*   **Implementation Detail:**
    In `src/frontend/memory_checker.cpp`:
    ```cpp
    // For now, we conservatively assume parameters are borrowed (not moved)
    // NOTE: We do NOT mark the variable as moved here
    ```
    Because standard function calls (such as `consume(data)`) assume borrowing rather than moving, variables are never marked as statically moved (`is_variable_moved` remains `false`). Consequently, subsequent accesses to the same variable are not flagged as use-after-move or double-move errors.

---

## 3. Arithmetic Overflows & Underflows
*   **Failing Tests:** `exponent_overflow.lm`, `integer_overflow.lm`, `multiplication_overflow.lm`, `negative_shift.lm`, `shift_overflow.lm`, `subtraction_underflow.lm`
*   **Reason for Failure:** Arithmetic operations directly utilize the underlying host platform's register-level operations (64-bit signed/unsigned math), which overflow or underflow silently by default without raising exceptions or compile-time checks.
*   **Implementation Detail:**
    The parser and code generator do not perform compile-time range/value validation for constant folding, and the VM instructions (such as `LIR_Op::Add`, `LIR_Op::Sub`) run native arithmetic operations directly. Thus, calculations like `-100 - 50` silently wrap or overflow to `-150` under larger integer types and complete execution cleanly.

---

## 4. Closure lifetimes and Capturing
*   **Failing Tests:** `capture_moved_var.lm`, `capture_mutable_conflict.lm`, `closure_lifetime_violation.lm`, `move_in_closure.lm`, `multiple_move_in_closure.lm`, `nested_closure_capture.lm`
*   **Reason for Failure:** Static closure lifetime and escape analysis are not fully implemented in the current memory or borrow checker.
*   **Implementation Detail:**
    While Limitly supports closures at runtime, the compile-time memory checker does not track capture-by-reference escape paths or enforce lifetime boundaries relative to enclosing stacks. As a result, code violating closure-capture rules compile and run normally without flagging compile-time memory/soundness errors.

---

## 5. Pattern Matching Exhaustiveness
*   **Failing Tests:** `missing_enum_variant.lm`, `missing_wildcard.lm`, `non_exhaustive_int_match.lm`, `non_exhaustive_match.lm`
*   **Reason for Failure:** The type checker does not enforce exhaustiveness checks on integer or custom enum pattern match statement branches.
*   **Implementation Detail:**
    Match statements are compiled directly to sequential conditional jumps. At compile time, if some variant branches or wildcards are missing, the compiler accepts the code. At runtime, if a non-matching value is provided and there is no default branch, the match simply does nothing and completes cleanly with exit code `0`.
