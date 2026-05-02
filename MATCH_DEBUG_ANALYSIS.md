# Match Statement Debug Analysis

## Problem Summary

Match statements are not working correctly. Literal patterns are not matching, and enum patterns are failing silently.

## Test Case: Simple Literal Match

```limit
var x: int = 10;
match (x) {
    5 => { print("x is five"); },
    10 => { print("x is ten"); },
    _ => { print("x is something else"); }
}
```

**Expected Output:** `x is ten`
**Actual Output:** `x is something else`

## LIR Generation Analysis

### Current LIR Generation (from statements.cpp:1590)

The LIR generator creates:
1. A value register for the match value
2. For each case:
   - A pattern block to check the pattern
   - A body block to execute if pattern matches
   - A next case pattern block to try next pattern

### For Literal Patterns:

```cpp
if (auto literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(match_case.pattern.get())) {
    if (std::holds_alternative<std::nullptr_t>(literal->value)) {
        // Wildcard _ or nil pattern
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, body_block->id));
    } else {
        Reg literal_reg = emit_expr(*literal);
        Reg cmp = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::CmpEQ, cmp, value_reg, literal_reg));
        
        emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp, 0, next_case_pattern->id));
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, body_block->id));
    }
}
```

### Issue 1: Unreachable Code

**Problem:** After `JumpIfFalse`, there's an unconditional `Jump` to body_block.

```
JumpIfFalse -> next_case_pattern (if false)
Jump -> body_block (always executed if we reach here)
```

This means if the comparison is FALSE, we jump to next_case_pattern. But if it's TRUE, we fall through to the unconditional Jump to body_block. This should work, but the control flow is confusing.

**Better approach:**
```
JumpIfFalse -> next_case_pattern (if false)
// If true, fall through to body_block
```

### Issue 2: Block Edge Management

The code adds edges:
```cpp
emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp, 0, next_case_pattern->id));
add_block_edge(pattern_block, next_case_pattern);

emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, body_block->id));
add_block_edge(pattern_block, body_block);
```

This creates two edges from pattern_block:
1. To next_case_pattern (if comparison is false)
2. To body_block (unconditional)

But the second edge is unreachable because the first instruction is a conditional jump that either jumps or falls through, and the second is an unconditional jump.

### Issue 3: Control Flow Logic

The current logic:
1. Evaluate pattern (CmpEQ)
2. If false, jump to next case
3. If true, fall through to unconditional jump to body

This should work, but there's a subtle issue: **the unconditional jump is always executed**, even if the comparison was false and we jumped to next_case_pattern.

Wait, that's not right. Let me re-read the code...

Actually, looking at the LIR_Op::JumpIfFalse implementation:
```cpp
case LIR::LIR_Op::JumpIfFalse: {
    if (!to_bool(registers[pc->a])) {
        pc = function.instructions.data() + (pc->imm);
        continue; // Skip pc++ at end of loop
    }
    // If true, fall through to next instruction
}
```

So if the condition is false, it jumps and continues (skipping the pc++ at the end).
If the condition is true, it falls through to the next instruction.

This means:
- If comparison is FALSE: Jump to next_case_pattern
- If comparison is TRUE: Fall through to the unconditional Jump to body_block

This should work correctly!

## Hypothesis: The Problem is Elsewhere

### Possible Issues:

1. **Pattern Block Not Being Executed**
   - The initial jump to the first pattern block might not be happening
   - Or the pattern block might not be connected properly

2. **Value Register Not Containing the Match Value**
   - The value_reg might not have the correct value
   - Or it might be getting overwritten

3. **Literal Register Not Containing the Literal Value**
   - The literal_reg might not have the correct value
   - Or the literal might not be parsed correctly

4. **CmpEQ Not Working Correctly**
   - The comparison might be failing even when values are equal
   - Type mismatch between value_reg and literal_reg

5. **Block Connectivity Issue**
   - The blocks might not be connected in the right order
   - The first pattern block might not be reachable

## Debug Strategy

### Step 1: Print LIR Instructions

Add debug output to see what LIR instructions are generated for the match statement.

```bash
./bin/limitly.exe -lir tests/loops/match_simple.lm
```

### Step 2: Add Debug Output to VM

Add debug output in the VM to trace:
- Which blocks are being executed
- What values are in registers
- What comparisons are being made

### Step 3: Create Minimal Test Case

Create a minimal test case with just one literal pattern:

```limit
var x: int = 10;
match (x) {
    10 => { print("matched"); },
    _ => { print("not matched"); }
}
```

### Step 4: Test Each Pattern Type

Test each pattern type independently:
- Literal patterns
- Variable binding patterns
- Enum patterns
- Wildcard patterns

## Suspected Root Cause

Based on the code analysis, I suspect the issue is in **block connectivity** or **initial block setup**. The pattern matching logic itself looks correct, but the blocks might not be connected properly to the rest of the function.

Specifically:
1. The first pattern block might not be reachable from the entry block
2. The match_exit block might not be connected properly
3. The control flow might be jumping to the wrong block

## Recommended Fix

1. **Verify Block Connectivity**
   - Ensure the first pattern block is reachable from the current block
   - Ensure all blocks are properly connected

2. **Simplify Control Flow**
   - Remove the unconditional Jump after JumpIfFalse
   - Let the JumpIfFalse handle both true and false cases

3. **Add Debug Output**
   - Print which pattern is being tried
   - Print the comparison result
   - Print which block is being executed

## Code Changes Needed

### In emit_match_stmt:

```cpp
// Current (problematic):
emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp, 0, next_case_pattern->id));
add_block_edge(pattern_block, next_case_pattern);

emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, body_block->id));
add_block_edge(pattern_block, body_block);

// Proposed (cleaner):
emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp, 0, next_case_pattern->id));
add_block_edge(pattern_block, next_case_pattern);
add_block_edge(pattern_block, body_block);  // Fall-through edge

// Then set body_block as current for the body
set_current_block(body_block);
```

This makes it clear that:
- If comparison is false, jump to next_case_pattern
- If comparison is true, fall through to body_block

## Testing Plan

1. Create `tests/loops/match_simple.lm` with minimal test cases
2. Run with `-lir` flag to see generated instructions
3. Add debug output to VM to trace execution
4. Fix the issue based on findings
5. Run full match test suite to verify fix
