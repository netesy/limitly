# Nested While Loop Infinite Loop Bug Report

## Issue
Nested while loops cause an infinite loop or incorrect execution in the VM.

## Symptoms
- Single while loops work correctly ✅
- Sequential while loops work correctly ✅
- Nested while loops hang or produce incorrect output ❌

## Test Cases

### Working: Single While Loop
```limit
var i = 0;
while (i < 3) {
    print("i = {i}");
    i = i + 1;
}
```
**Result**: ✅ Works correctly

### Working: Sequential While Loops
```limit
var i = 0;
while (i < 2) {
    print("i = {i}");
    i = i + 1;
}

var j = 0;
while (j < 2) {
    print("j = {j}");
    j = j + 1;
}
```
**Result**: ✅ Works correctly

### Broken: Nested While Loops
```limit
var outer = 0;
while (outer < 2) {
    print("outer = {outer}");
    var inner = 0;
    while (inner < 2) {
        print("  inner = {inner}");
        inner = inner + 1;
    }
    outer = outer + 1;
}
```
**Result**: ❌ Produces incorrect output (prints "Done" multiple times after completion)

## Root Cause Analysis

### LIR Generation
The bytecode generation appears correct:
- Outer loop condition check at L4
- Inner loop condition check at L15
- Inner loop jumps back to L15 (correct)
- After inner loop, jumps back to L4 (correct)
- After outer loop, exits to L12 (correct)

### VM Execution Issue
The problem appears to be in the VM's jump instruction handling:
1. Nested loops generate correct bytecode
2. The jumps are correct in the LIR
3. But the VM doesn't execute them correctly

Possible causes:
- Jump instruction not properly updating instruction pointer
- Loop variable scope issues in nested contexts
- Stack frame management problem with nested loops
- Instruction pointer corruption in nested jump scenarios

## Workaround
Until this is fixed, avoid nested while loops. Use:
- Sequential while loops instead
- For loops with ranges instead
- Refactor nested logic into separate functions

## Files Affected
- `src/backend/vm.cpp` - VM execution engine
- `src/lir/generator.cpp` - LIR generation (appears correct)

## Priority
**High** - Nested loops are a fundamental language feature

## Test Files
- `test_while_nested.lm` - Demonstrates the bug
- `test_while_sequential.lm` - Shows sequential loops work
- `test_while_simple.lm` - Shows single loops work
- `test_while_nested_debug.lm` - Diagnostic test

## Next Steps
1. Debug VM jump instruction handling
2. Check instruction pointer management in nested contexts
3. Verify loop variable scoping
4. Test with debugger to trace execution path
