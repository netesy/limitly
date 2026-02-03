# JIT Debug Guide

## Enabling Debug Output

To see detailed LIR instructions being compiled, use the `-jit-debug` flag:

```bash
./bin/limitly.exe -jit-debug test_simple.lm
```

## Debug Output Format

Each LIR instruction will be printed with the following information:

```
[JIT DEBUG] Compiling LIR instruction: <OPERATION> (result_type=<TYPE>)
```

### Example Output

```
[JIT DEBUG] Compiling LIR instruction: LoadConst r0 = Apple (result_type=0)
[JIT DEBUG] Compiling LIR instruction: PrintString r0 (result_type=0)
[JIT DEBUG] Compiling LIR instruction: LoadConst r1 = Banana (result_type=0)
[JIT DEBUG] Compiling LIR instruction: PrintString r1 (result_type=0)
```

## Understanding the Output

### Register Notation
- `r0`, `r1`, `r2`, etc. = Virtual registers
- `r0` is typically the return register

### Operation Types

**Data Movement:**
- `Mov r<dst> = r<src>` - Copy register value
- `LoadConst r<dst> = <value>` - Load constant

**Arithmetic:**
- `Add r<dst> = r<a> + r<b>` - Addition
- `Sub r<dst> = r<a> - r<b>` - Subtraction
- `Mul r<dst> = r<a> * r<b>` - Multiplication
- `Div r<dst> = r<a> / r<b>` - Division
- `Mod r<dst> = r<a> % r<b>` - Modulo

**Comparisons:**
- `CmpEQ r<dst> = r<a> == r<b>` - Equal
- `CmpNEQ r<dst> = r<a> != r<b>` - Not equal
- `CmpLT r<dst> = r<a> < r<b>` - Less than
- `CmpLE r<dst> = r<a> <= r<b>` - Less than or equal
- `CmpGT r<dst> = r<a> > r<b>` - Greater than
- `CmpGE r<dst> = r<a> >= r<b>` - Greater than or equal

**Control Flow:**
- `Jump to <label>` - Unconditional jump
- `JumpIfFalse r<a> to <label>` - Conditional jump
- `Call r<dst> = <func>(<args>)` - Function call
- `Return r<dst>` - Return from function

**I/O:**
- `PrintInt r<a>` - Print integer
- `PrintUint r<a>` - Print unsigned integer
- `PrintFloat r<a>` - Print float
- `PrintBool r<a>` - Print boolean
- `PrintString r<a>` - Print string

**Collections:**
- `ListCreate r<dst>` - Create list
- `ListAppend r<a>, r<b>` - Append to list
- `ListIndex r<dst> = r<a>[r<b>]` - Index into list
- `ListLen r<dst> = len(r<a>)` - Get list length
- `DictCreate r<dst>` - Create dictionary
- `DictSet r<dst>[r<a>] = r<b>` - Set dict value
- `DictGet r<dst> = r<a>[r<b>]` - Get dict value
- `DictItems r<dst> = items(r<a>)` - Get dict items
- `TupleCreate r<dst> size=<n>` - Create tuple
- `TupleGet r<dst> = r<a>[r<b>]` - Get tuple element
- `TupleSet r<dst>[r<a>] = r<b>` - Set tuple element

**Channels:**
- `ChannelSend r<a>, r<b>` - Send on channel
- `ChannelRecv r<dst> = recv(r<a>)` - Receive from channel
- `ChannelOffer r<dst> = offer(r<a>, r<b>)` - Non-blocking send
- `ChannelPoll r<dst> = poll(r<a>)` - Non-blocking receive
- `ChannelClose r<a>` - Close channel

**Type Operations:**
- `Cast r<dst> = (cast) r<a>` - Type cast
- `ToString r<dst> = str(r<a>)` - Convert to string
- `STR_CONCAT r<dst> = r<a> + r<b>` - String concatenation
- `STR_FORMAT r<dst> = format(r<a>, r<b>)` - String formatting

### Result Type Values

The `result_type` field indicates the expected result type:
- `0` = I32 (32-bit integer)
- `1` = I64 (64-bit integer)
- `2` = F64 (64-bit float)
- `3` = Bool (boolean)
- `4` = Ptr (pointer)
- `5` = Void (void)

## Troubleshooting

### Finding the Error Location

1. Run with `-jit-debug` flag
2. Look for the instruction that causes the error
3. Check the operation type and registers involved
4. Look at the `result_type` - if it's 5 (Void), that might be the issue

### Example: Void Type Error

If you see:
```
[JIT DEBUG] Compiling LIR instruction: Mov r12 = r11 (result_type=5)
libgccjit.so: error: gcc_jit_context_new_cast: cannot cast r12 from type: void * to type: void
```

This means:
- A `Mov` instruction is trying to move a value to register 12
- The result type is 5 (Void)
- The JIT is trying to create a void register, which is invalid

**Fix**: Check the `to_jit_type()` function to ensure it never returns `m_void_type` for register operations.

## Running Tests with Debug

```bash
# Test with debug output
./bin/limitly.exe -jit-debug tests/basic/lists.lm

# Compare with register VM (no debug needed)
./bin/limitly.exe --vm tests/basic/lists.lm

# Redirect debug output to file for analysis
./bin/limitly.exe -jit-debug test_simple.lm > debug_output.txt 2>&1
```

## Tips

1. **Grep for errors**: `./bin/limitly.exe -jit-debug test.lm 2>&1 | grep -A5 "error"`
2. **Count instructions**: `./bin/limitly.exe -jit-debug test.lm 2>&1 | grep "Compiling LIR" | wc -l`
3. **Find specific operations**: `./bin/limitly.exe -jit-debug test.lm 2>&1 | grep "TupleGet"`
4. **Save for comparison**: `./bin/limitly.exe -jit-debug test.lm > jit_debug.log 2>&1`
