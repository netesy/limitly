# CFG Linearization Bug Analysis

## Problem

The match statement is generating incorrect jumps. For example:

```
11: jmp_if_false r6, 12      // If not equal, jump to 12
12: jump 13                  // Unconditional jump to 13 (wildcard body)
```

This should jump to the correct body (instruction 16), not the wildcard body (instruction 13).

## Root Cause

The issue is in how blocks are linearized in `flatten_cfg_to_instructions()`:

1. **Block Creation Order**:
   - Pattern block 0 (ID: 0)
   - Body block 0 (ID: 1)
   - Pattern block 1 (ID: 2)
   - Body block 1 (ID: 3)
   - Wildcard pattern block (ID: 4)
   - Wildcard body block (ID: 5)

2. **CFG Edges**:
   - Pattern block 0 → Pattern block 1 (if comparison false)
   - Pattern block 0 → Body block 0 (if comparison true)
   - Pattern block 1 → Pattern block 2 (if comparison false)
   - Pattern block 1 → Body block 1 (if comparison true)
   - Pattern block 2 → Wildcard body (always)

3. **DFS Linearization**:
   The DFS visits successors in reverse order:
   ```
   visit(Pattern block 0):
     visit(Body block 0):  // Visited first (reverse order)
       sorted_blocks = [Body block 0]
     visit(Pattern block 1):
       visit(Body block 1):
         sorted_blocks = [Body block 0, Body block 1]
       visit(Pattern block 2):
         visit(Wildcard body):
           sorted_blocks = [Body block 0, Body block 1, Wildcard body]
         sorted_blocks = [Body block 0, Body block 1, Wildcard body, Pattern block 2]
       sorted_blocks = [Body block 0, Body block 1, Wildcard body, Pattern block 2, Pattern block 1]
     sorted_blocks = [Body block 0, Body block 1, Wildcard body, Pattern block 2, Pattern block 1, Pattern block 0]
   ```

4. **Linearized Instruction Order**:
   After reversing:
   ```
   Pattern block 0 (instructions 0-1)
   Pattern block 1 (instructions 2-3)
   Pattern block 2 (instructions 4-5)
   Wildcard body (instructions 6-7)
   Body block 1 (instructions 8-9)
   Body block 0 (instructions 10-11)
   ```

5. **Jump Target Mapping**:
   - Block ID 0 (Pattern block 0) → instruction 0
   - Block ID 2 (Pattern block 1) → instruction 2
   - Block ID 4 (Pattern block 2) → instruction 4
   - Block ID 5 (Wildcard body) → instruction 6
   - Block ID 3 (Body block 1) → instruction 8
   - Block ID 1 (Body block 0) → instruction 10

6. **The Bug**:
   When Pattern block 0 emits `jmp_if_false r6, 12`:
   - The immediate value `12` is the block ID of Pattern block 1
   - But the block_positions map says block ID 2 → instruction 2
   - Wait, that's not right...

Actually, let me re-read the code. The issue is that the block IDs are being used directly as jump targets in the LIR instructions, but they should be mapped to instruction positions.

Looking at the code:
```cpp
emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp, 0, next_pattern->id));
```

This stores `next_pattern->id` (the block ID) as the immediate value. Then in `flatten_cfg_to_instructions()`:

```cpp
if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
    auto it = block_positions.find(inst.imm);
    if (it != block_positions.end()) {
        modified_inst.imm = it->second; // Use instruction position as label
    }
}
```

This should map the block ID to the instruction position. But something is going wrong.

## Hypothesis

The problem might be that:

1. The block IDs are not sequential (they might have gaps)
2. The block_positions map is not being populated correctly
3. The DFS is not visiting all blocks
4. The block linearization order is wrong

## Solution

The issue is that the match statement is creating blocks in the wrong order. Instead of:
- Pattern block 0
- Body block 0
- Pattern block 1
- Body block 1
- ...

We should create:
- Pattern block 0
- Pattern block 1
- ...
- Body block 0
- Body block 1
- ...

Or better yet, we should create blocks in the order they will be executed:
- Pattern block 0
- Body block 0 (if pattern matches)
- Pattern block 1 (if pattern doesn't match)
- Body block 1 (if pattern matches)
- ...

## Fix

The fix is to change the match statement generation to create blocks in the correct order, or to ensure that the CFG edges are set up correctly so that the DFS linearization produces the right order.

The current code creates all pattern blocks first, then all body blocks. This causes the DFS to visit body blocks before pattern blocks, resulting in the wrong linearization order.

## Recommended Fix

Change the match statement generation to:
1. Create pattern block 0
2. Create body block 0
3. Create pattern block 1
4. Create body block 1
5. ...

This way, the DFS will naturally linearize them in the right order.

Alternatively, we could fix the DFS to prefer visiting blocks in a specific order (e.g., by block creation order rather than reverse order).
