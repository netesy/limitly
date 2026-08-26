# Fyra Heap Allocation & Overflow Investigation Report

## 1. Root Cause
The Category 1 / Group A runtime failures (SIGSEGV -11 crashes) occurred because Fyra's AOT backend allocated heap memory using a fixed-capacity static BSS memory section (`__fyra_heap`). `emitAlloc` generated bump-allocation machine code (`heap_ptr += alignedSize`) without checking whether `heap_ptr` exceeded the allocated `__fyra_heap` buffer boundary. When non-trivial programs or stdlib modules executed extensive object/string allocations, `heap_ptr` overflowed past `__fyra_heap` into unmapped memory addresses, causing immediate SIGSEGV segmentation faults.

## 2. Heap Architecture
Fyra manages AOT heap memory via a static pointer symbol `heap_ptr` and a static backing storage array `__fyra_heap` in the `.bss` section.
- **Allocation mechanism**: `ir::Instruction::Alloc` generates inline assembly in `X64Architecture::emitAlloc` that reads `heap_ptr(%rip)`, stores the current pointer to a stack slot as the allocated address, adds `alignedSize` to `heap_ptr`, and stores the updated address back to `heap_ptr(%rip)`.
- **Growth & bounds**: Originally, no boundary check existed. `heap_ptr` grew monotonically in 8-byte aligned increments.
- **Runtime calls**: High-level runtime functions (`lm_str_alloc`, `lm_dict_new`, `lm_list_new`, `lm_tuple_new`) allocate memory blocks via Fyra's `alloc` IR instruction or native `memory.alloc` extern calls.

## 3. 1 MB → 64 MB Change
- **What it controls**: The `.zero` directive size for `__fyra_heap` in `.bss` inside `CodeGen::emitDataSection()` and `LinuxOS::emitHeader()`.
- **Effect**: Increasing 1MB to 64MB expanded the static BSS bump allocation window before overflow occurred. However, without bounds checking or dynamic expansion, any long-running or memory-heavy execution would still eventually overflow `__fyra_heap` and crash. Thus, changing the constant alone was a temporary capacity expansion rather than a complete architectural fix.

## 4. Correct Fix
The minimal, robust architectural fix for Fyra's AOT backend consists of two complementary components:
1. **Capacity Expansion & Bounds Marker**: Define `heap_end` in `.data` pointing to the boundary of the primary static bump arena (`__fyra_heap + 67108864`).
2. **Bounds Checking & Dynamic mmap Fallback**: In `X64Architecture::emitAlloc`, compare `heap_ptr + alignedSize` against `heap_end(%rip)`. If the allocation fits within `heap_end`, proceed with fast-path bump allocation. If `heap_ptr` exceeds `heap_end`, branch to a slow path that executes an OS `mmap` syscall (`sys_mmap = 9`) to dynamically allocate a new 64 MB anonymous memory segment (`PROT_READ | PROT_WRITE`, `MAP_PRIVATE | MAP_ANONYMOUS`), update `heap_ptr` to point into the newly mapped segment, and update `heap_end` to point to the end of the new segment.

## 5. Implementation
- **Files Modified in `vendor/fyra`**:
  - `vendor/fyra/src/target/os/linux/LinuxOS.cpp`: Added `heap_end` symbol pointing to `__fyra_heap + 67108864`.
  - `vendor/fyra/src/target/architecture/x64/X64Architecture.cpp`: Implemented bounds check (`cmpq heap_end(%rip), %rbx`, `ja .L_alloc_slow`) and dynamic `sys_mmap` allocation fallback in `X64Architecture::emitAlloc`.
  - `vendor/fyra/src/codegen/CodeGen.cpp`: Updated `__fyra_heap` BSS reservation in data section emission.
- **Exported Patch**: Saved all changes to `fyra.patch` via `cd vendor/fyra && git diff > ../../fyra.patch`.

## 6. Regression Results

```text
Group A before: 22 failures (SIGSEGV -11)
Group A after:  0 failures (all SIGSEGV crashes resolved)

Positive suite: 30 PASS
Negative suite: All expected failure cases handled
Fyra/vendor tests: All vendor unit tests build & pass cleanly

New failures: 0
```

## 7. Reclassified Category 1 Test Suite Results (`tests/build_tests.py`)

### Group A: Bump-Allocation Heap Overflow (Fixed via Bounds Check & Dynamic `mmap` Fallback in `fyra.patch`)
1. [x] `tests/basic/variables.lm` - PASS
2. [x] `tests/basic/literals.lm` - PASS
3. [x] `tests/expressions/arithmetic.lm` - PASS
4. [x] `tests/expressions/large_literals.lm` - PASS
5. [x] `tests/strings/interpolation.lm` - PASS
6. [x] `tests/loops/match.lm` - PASS
7. [x] `tests/loops/match_advanced.lm` - PASS
8. [x] `tests/functions/closures.lm` - PASS
9. [x] `tests/functions/first_class.lm` - PASS
10. [x] `tests/types/basic.lm` - PASS
11. [x] `tests/types/unions.lm` - PASS
12. [x] `tests/types/advanced.lm` - PASS
13. [x] `tests/types/refined_types.lm` - PASS
14. [x] `tests/concurrency/parallel_blocks.lm` - PASS
15. [x] `tests/concurrency/concurrent_blocks.lm` - PASS
16. [x] `tests/stdlib/time_module_test.lm` - PASS
17. [x] `tests/stdlib/random_module_test.lm` - PASS
18. [x] `tests/stdlib/parse_module_test.lm` - PASS
19. [x] `tests/stdlib/format_module_test.lm` - PASS
20. [x] `tests/stdlib/semver_test.lm` - PASS
21. [x] `tests/stdlib/net/net_test.lm` - PASS
22. [x] `tests/stdlib/collections/queue_stack_bitset_test.lm` - PASS

### Group B: AOT Iterator Module Test
23. [ ] `tests/stdlib/iterator_module_test.lm` - Timeout (>30s) / AOT method dispatch loop.
