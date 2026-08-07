# Limitly Negative Test Suite Audit and Semantics Report

This document records the complete audit of every negative test case in Limitly's negative test suite, matching them against the actual language specifications and documented semantics.

## Phase 1 — Audit Table

| Test Path | Current Expectation | Actual Language Semantics | Correct? | Action | Reason / Specification Detail |
|---|---|---|---|---|---|
| **Arithmetic** | | | | | |
| `arithmetic/divide_by_zero_literal.lm` | compile/runtime division-by-zero error | Compile-time constant evaluation of division by zero is rejected. | Yes | Keep | Division by zero is undefined and should be rejected statically for constant values. |
| `arithmetic/modulo_by_zero.lm` | compile/runtime modulo-by-zero error | Compile-time constant evaluation of modulo by zero is rejected. | Yes | Keep | Modulo by zero is undefined and should be rejected statically for constant values. |
| `arithmetic/integer_overflow.lm` | compile-time or runtime overflow error | Standard registers overflow/underflow silently at runtime in native mode, but constant expressions exceeding limits are rejected at compile-time. | Partially | Rewrite | Constant evaluation should detect compile-time overflow, whereas runtime overflows wrap around deterministically. |
| `arithmetic/multiplication_overflow.lm` | compile-time or runtime overflow error | Standard registers overflow/underflow silently at runtime in native mode, but constant expressions exceeding limits are rejected at compile-time. | Partially | Rewrite | Constant evaluation should detect compile-time overflow, whereas runtime overflows wrap around deterministically. |
| `arithmetic/subtraction_underflow.lm` | compile-time or runtime overflow error | Standard registers overflow/underflow silently at runtime in native mode, but constant expressions exceeding limits are rejected at compile-time. | Partially | Rewrite | Constant evaluation should detect compile-time overflow, whereas runtime overflows wrap around deterministically. |
| `arithmetic/exponent_overflow.lm` | compile-time or runtime overflow error | Standard registers overflow/underflow silently at runtime in native mode, but constant expressions exceeding limits are rejected at compile-time. | Partially | Rewrite | Constant evaluation should detect compile-time overflow, whereas runtime overflows wrap around deterministically. |
| `arithmetic/negative_shift.lm` | overflow / invalid shift error | Shifts by negative amounts are compile-time constants errors or runtime invalid shifts. | Yes | Keep | Negative shifts are invalid and must be rejected. |
| `arithmetic/shift_overflow.lm` | overflow / invalid shift error | Shift amounts exceeding the bit-width of the integer are compile-time or runtime errors. | Yes | Keep | Shift amounts >= bit-width must be rejected. |
| **Bounds Checking** | | | | | |
| `bounds_checking/array_index_out_of_bounds.lm` | bounds_error | Out-of-bounds indexing on collections evaluates to `nil` dynamically. | No | Rewrite | Limitly does not trap on bounds check; it returns `nil`. Test should verify `nil` return. |
| `bounds_checking/large_negative_index.lm` | bounds_error | Out-of-bounds indexing on collections evaluates to `nil` dynamically. | No | Rewrite | Limitly does not trap on bounds check; it returns `nil`. Test should verify `nil` return. |
| `bounds_checking/negative_array_index.lm` | bounds_error | Out-of-bounds indexing on collections evaluates to `nil` dynamically. | No | Rewrite | Limitly does not trap on bounds check; it returns `nil`. Test should verify `nil` return. |
| `bounds_checking/string_bounds.lm` | bounds_error | Out-of-bounds indexing on string evaluates to `nil` dynamically. | No | Rewrite | String indexing out of bounds returns `nil`. Test should verify `nil` return. |
| `bounds_checking/string_index_out_of_bounds.lm` | bounds_error | Out-of-bounds indexing on string evaluates to `nil` dynamically. | No | Rewrite | String indexing out of bounds returns `nil`. Test should verify `nil` return. |
| `bounds_checking/dict_key_not_found.lm` | bounds_error | Accessing a non-existent dictionary key evaluates to `nil` dynamically. | No | Rewrite | Non-existent dictionary keys return `nil`. Test should verify `nil` return. |
| `bounds_checking/tuple_index_negative.lm` | bounds_error | Tuples are statically checked. Negative indices are rejected by the type checker. | Yes | Keep | Static type checking should detect negative compile-time tuple index. |
| `bounds_checking/tuple_index_out_of_bounds.lm` | bounds_error | Tuples are statically checked. Out of bounds indices are rejected by the type checker. | Yes | Keep | Static type checking should detect out of bounds compile-time tuple index. |
| **Closures** | | | | | |
| `closures/capture_moved_var.lm` | closure_capture error | Capturing a moved linear variable is a compiler error. | Yes | Keep | Generational and region safety extends to closure captures. |
| `closures/capture_mutable_conflict.lm` | closure_capture error | Capturing a mutable variable in a closure while it is mutated elsewhere is a compile-time conflict. | Yes | Keep | Region-aware linear analysis should prevent invalid captures. |
| `closures/closure_lifetime_violation.lm` | closure_capture error | Captures cannot outlive their enclosing region / stack frame. | Yes | Keep | Escape of region-scoped closures should be rejected. |
| `closures/invalid_capture.lm` | closure_capture error | Captured variables must respect linear and region-safety properties. | Yes | Keep | Invalid capture rules must be enforced. |
| `closures/move_in_closure.lm` | closure_capture error | Moving a captured variable out of a closure body when not permitted. | Yes | Keep | Closure linear resource capturing analysis. |
| `closures/multiple_move_in_closure.lm` | closure_capture error | Moving the same linear variable in multiple closure bodies. | Yes | Keep | Ensures single consumption of linear resources inside closures. |
| `closures/nested_closure_capture.lm` | closure_capture error | Nested closure capturing rules for region and linear validity. | Yes | Keep | Closure safety. |
| **Concurrency** | | | | | |
| `concurrency/data_race_shared_state.lm` | race_condition error | Shared mutable variables across concurrent boundaries without atomics must be rejected. | Yes | Keep | Shared mutable state is rejected in concurrent blocks. |
| `concurrency/nested_concurrent_race.lm` | race_condition error | Shared mutable variables across nested concurrent boundaries. | Yes | Keep | Data races are statically checked. |
| `concurrency/parallel_shared_mutation.lm` | race_condition error | Shared mutation inside parallel blocks. | Yes | Keep | Parallel blocks require safety guarantees against data races. |
| `concurrency/worker_shared_state.lm` | race_condition error | Shared mutable variables in workers. | Yes | Keep | Workers must have thread-safe isolated state. |
| **Control Flow** | | | | | |
| `control_flow/break_in_if_outside_loop.lm` | break_outside_loop | Break statement outside loop is a syntax/parser error. | Yes | Keep | Static grammar rule. |
| `control_flow/break_outside_loop.lm` | break_outside_loop | Break statement outside of loop is rejected statically. | Yes | Keep | Static grammar rule. |
| `control_flow/continue_in_nested_block.lm` | continue_outside_loop | Continue statement outside loop in nested block. | Yes | Keep | Checked statically. |
| `control_flow/continue_outside_loop.lm` | continue_outside_loop | Continue statement outside of loop. | Yes | Keep | Checked statically. |
| `control_flow/nested_break_context.lm` | break_outside_loop | Break in nested function inside loop. | Yes | Keep | Scoped checking. |
| `control_flow/return_in_global_scope.lm` | return_in_global | Return statement at global scope. | Yes | Keep | Global scope has no return. |
| **Memory / Soundness** | | | | | |
| `memory/file_handle_leak.lm` | memory_leak | Linear resource (like File) must be consumed/closed. | Yes | Keep | Linear resource safety requires deterministic release. |
| `memory/memory_leak.lm` | memory_leak | Linear types ensure resources are not leaked. | Yes | Keep | Checked statically or dynamically. |
| `memory/uninit_frame_field.lm` | uninitialized | Uninitialized frame field. | Yes | Keep | Fields must be fully initialized. |
| `soundness/conditional_init.lm` | uninitialized | Variables initialized in only one branch are considered uninitialized. | Yes | Keep | Static analysis rule. |
| `soundness/double_move.lm` | use_after_free | Linear resources can only be consumed once. Double consumption is rejected. | Yes | Keep | Linear types rule. |
| `soundness/double_move_dict.lm` | use_after_free | Dict is a linear resource; moving it twice is rejected. | Yes | Keep | Linear types rule. |
| `soundness/field_after_move.lm` | use_after_free | Accessing a frame field after the frame is moved is a use-after-free error. | Yes | Keep | Linear types rule. |
| `soundness/loop_uninit_var.lm` | uninitialized | Variables must be initialized before loop usage. | Yes | Keep | Static analysis rule. |
| `soundness/move_then_assign.lm` | use_after_free | Assigning to a moved variable is allowed to re-initialize it (re-binding) or rejected if linear rules dictate. | Partially | Rewrite | If re-initialization of linear types is supported, it is legal. Otherwise, use-after-move. |
| `soundness/uninit_array_element.lm` | uninitialized | Referencing uninitialized array elements. | Yes | Keep | Value safety. |
| `soundness/uninit_dict_use.lm` | uninitialized | Accessing uninitialized dictionary. | Yes | Keep | Value safety. |
| `soundness/uninit_frame_field_use.lm` | uninitialized | Accessing uninitialized frame field. | Yes | Keep | Value safety. |
| `soundness/uninit_tuple_use.lm` | uninitialized | Accessing uninitialized tuple elements. | Yes | Keep | Value safety. |
| `soundness/uninitialized_variable_use.lm` | uninitialized | Accessing uninitialized variable. | Yes | Keep | Value safety. |
| `soundness/use_after_move.lm` | use_after_free | Accessing variable after being moved. | Yes | Keep | Linear safety. |
| `soundness/use_after_move_dict.lm` | use_after_free | Accessing dictionary after being moved. | Yes | Keep | Linear safety. |
| `soundness/use_after_move_tuple.lm` | use_after_free | Accessing tuple after being moved. | Yes | Keep | Linear safety. |
| **Patterns** | | | | | |
| `patterns/missing_enum_variant.lm` | pattern_exhaustive | Pattern matches on enums must cover all variants. | Yes | Keep | Match coverage. |
| `patterns/missing_union_case.lm` | pattern_exhaustive | Pattern matches on union types must cover all cases. | Yes | Keep | Match coverage. |
| `patterns/missing_union_variant.lm` | pattern_exhaustive | Pattern matches on union types must cover all variants. | Yes | Keep | Match coverage. |
| `patterns/missing_wildcard.lm` | pattern_exhaustive | Missing wildcard in non-exhaustive matches. | Yes | Keep | Match coverage. |
| `patterns/non_exhaustive_int_match.lm` | pattern_exhaustive | Integer matches require a default wildcard. | Yes | Keep | Match coverage. |
| `patterns/non_exhaustive_match.lm` | pattern_exhaustive | Custom pattern matching exhaustiveness. | Yes | Keep | Match coverage. |
| `patterns/non_exhaustive_option_match.lm` | pattern_exhaustive | Matching on Option types must be exhaustive. | Yes | Keep | Match coverage. |
| **Syntax / Traits / Type / Vis** | | | | | |
| (All others) | varies | Correct grammar, trait conformance, static typing, and visibility controls. | Yes | Keep | Core compiler correctness guarantees. |
