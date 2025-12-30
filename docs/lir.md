# Limit Intermediate Representation (LIR)

The **Limit Intermediate Representation (LIR)** is a register-based intermediate representation for the Limit programming language compiler. It is designed to be **simple, efficient, and directly executable** by the Limit virtual machine and JIT compiler.

LIR uses a **register-based design** with explicit typing and includes Limit-specific features like string operations, concurrency primitives, and builtin function calls.

---

## 1. Architecture

LIR is a register-based IR where:
* All values are stored in numbered registers (`r0`, `r1`, `r2`, etc.)
* Instructions operate on registers and produce results in registers
* Functions have parameter registers and local registers
* Control flow uses basic blocks with explicit jumps

**Basic Syntax:**
```lir
# Register assignment
r1 = add r0, r2

# Function calls
r3 = call print(r1)

# Control flow
jump_if_false r1, @label1
```

---

## 2. Types

LIR uses a simplified ABI-level type system:

| Type | Meaning                      | Size | Notes                     |
| ---- | ---------------------------- | ---- | ------------------------- |
| `I32`| 32-bit integer               | 4 B  | signed/unsigned           |
| `I64`| 64-bit integer               | 8 B  | signed/unsigned, pointers |
| `F64`| 64-bit float                 | 8 B  | IEEE-754 double           |
| `Bool`| Boolean value               | 1 B  | true/false                |
| `Ptr`| Pointer/reference            | 8 B  | Memory address            |
| `Void`| No value                    | 0 B  | Used for void functions   |

These types correspond directly to the underlying machine types and are used by the JIT compiler for efficient code generation.

---

## 3. Constants and Literals

* Integers: `42`, `-17`, `0`
* Floating-point: `3.14`, `-2.5`, `1e-5`
* Booleans: `true`, `false`
* Strings: `"hello world"`
* Null/void: represented as void type

---

## 4. Instructions

### 4.1 Data Movement

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `Mov`               | Move register to register  | `r1 = mov r0`         |
| `LoadConst`         | Load constant into register| `r1 = loadconst 42`   |

### 4.2 Arithmetic Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `Add`               | Addition                   | `r2 = add r0, r1`     |
| `Sub`               | Subtraction                | `r2 = sub r0, r1`     |
| `Mul`               | Multiplication             | `r2 = mul r0, r1`     |
| `Div`               | Division                   | `r2 = div r0, r1`     |
| `Mod`               | Modulo                     | `r2 = mod r0, r1`     |
| `Neg`               | Negation                   | `r1 = neg r0`         |

### 4.3 Bitwise Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `And`               | Bitwise AND                | `r2 = and r0, r1`     |
| `Or`                | Bitwise OR                 | `r2 = or r0, r1`      |
| `Xor`               | Bitwise XOR                | `r2 = xor r0, r1`     |

### 4.4 Comparison Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `CmpEQ`             | Compare Equal              | `r2 = cmpeq r0, r1`   |
| `CmpNEQ`            | Compare Not Equal          | `r2 = cmpneq r0, r1`  |
| `CmpLT`             | Compare Less Than          | `r2 = cmplt r0, r1`   |
| `CmpLE`             | Compare Less or Equal      | `r2 = cmple r0, r1`   |
| `CmpGT`             | Compare Greater Than       | `r2 = cmpgt r0, r1`   |
| `CmpGE`             | Compare Greater or Equal   | `r2 = cmpge r0, r1`   |

### 4.5 Control Flow

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `Jump`              | Unconditional jump         | `jump @label1`        |
| `JumpIfFalse`       | Jump if condition is false | `jump_if_false r0, @label1` |
| `JumpIf`            | Jump if condition is true  | `jump_if r0, @label1` |
| `Return`            | Return from function       | `return r0`           |
| `Ret`               | Return (alternative form)  | `ret r0`              |

### 4.6 Function Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `Call`              | Function call              | `r2 = call print(r0, r1)` |
| `CallVoid`          | Void function call         | `call_void print(r0)` |
| `CallBuiltin`       | Builtin function call      | `r1 = call_builtin abs(r0)` |

### 4.7 Print Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `PrintInt`          | Print integer              | `print_int r0`        |
| `PrintUint`         | Print unsigned integer     | `print_uint r0`       |
| `PrintFloat`        | Print floating point       | `print_float r0`      |
| `PrintBool`         | Print boolean              | `print_bool r0`       |
| `PrintString`       | Print string               | `print_string r0`     |

### 4.8 String Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `STR_CONCAT`        | String concatenation       | `r2 = str_concat r0, r1` |
| `STR_FORMAT`        | String formatting          | `r2 = str_format r0, r1` |
| `ToString`          | Convert to string          | `r1 = tostring r0`    |

### 4.9 Type Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `Cast`              | Type casting               | `r1 = cast r0 : F64`  |

### 4.10 Concurrency Operations

| Instruction         | Description                | Example               |
| ------------------- | -------------------------- | --------------------- |
| `TaskContextAlloc`  | Allocate task context      | `r1 = task_context_alloc r0` |
| `TaskContextInit`   | Initialize task context    | `task_context_init r0` |
| `TaskSetField`      | Set task field             | `task_set_field r0, r1, 2` |
| `TaskGetField`      | Get task field             | `r2 = task_get_field r0, 1` |
| `ChannelAlloc`      | Allocate channel           | `r1 = channel_alloc 32` |
| `ChannelPush`       | Push to channel            | `channel_push r0, r1` |
| `ChannelPop`        | Pop from channel           | `r2 = channel_pop r0` |
| `ChannelHasData`    | Check channel has data     | `r1 = channel_has_data r0` |
| `SchedulerRun`      | Run scheduler              | `scheduler_run r0, r1` |

---

## 5. Function Structure

Functions in LIR have the following structure:

```lir
function function_name(param_count) {
    # Parameter registers: r0, r1, r2, ... (up to param_count-1)
    # Local registers: r{param_count}, r{param_count+1}, ...
    
    # Instructions
    r2 = add r0, r1
    return r2
}
```

### 5.1 Parameter Passing
- Parameters are passed in registers `r0`, `r1`, `r2`, etc.
- Return values are placed in a designated register
- Local variables use registers after the parameter registers

### 5.2 Register Allocation
- Registers are allocated sequentially
- Each function tracks its `register_count` for proper allocation
- Type information is maintained for each register

---

## 6. Examples

### 6.1 Simple Arithmetic Function
Limit:
```limit
fn add(a: int, b: int) -> int {
    return a + b;
}
```

LIR:
```lir
function add(2) {
    r2 = add r0, r1
    return r2
}
```

### 6.2 Conditional Logic
Limit:
```limit
fn max(a: int, b: int) -> int {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
```

LIR:
```lir
function max(2) {
    r2 = cmpgt r0, r1
    jump_if_false r2, @else_label
    return r0
@else_label:
    return r1
}
```

### 6.3 String Operations
Limit:
```limit
fn greet(name: str) -> str {
    return "Hello, " + name + "!";
}
```

LIR:
```lir
function greet(1) {
    r1 = loadconst "Hello, "
    r2 = str_concat r1, r0
    r3 = loadconst "!"
    r4 = str_concat r2, r3
    return r4
}
```

### 6.4 Print Statement
Limit:
```limit
print("Hello, World!");
```

LIR:
```lir
r0 = loadconst "Hello, World!"
print_string r0
```

### 6.5 Function Call
Limit:
```limit
let result = add(5, 3);
print(result);
```

LIR:
```lir
r0 = loadconst 5
r1 = loadconst 3
r2 = call add(r0, r1)
print_int r2
```

---

## 7. Builtin Functions

The LIR system includes several categories of builtin functions:

### 7.1 String Functions
- `concat(str, str) -> str` - String concatenation
- `length(str) -> int` - String length
- `substring(str, int, int) -> str` - Extract substring
- `str_format(str, any) -> str` - Format string with value

### 7.2 I/O Functions
- `print(any) -> void` - Print value to stdout
- `input(str) -> str` - Read line from stdin with prompt

### 7.3 Math Functions
- `abs(int) -> int` - Absolute value for integers
- `fabs(float) -> float` - Absolute value for floats
- `sqrt(float) -> float` - Square root
- `pow(float, float) -> float` - Power function
- `sin(float) -> float` - Sine function
- `cos(float) -> float` - Cosine function
- `tan(float) -> float` - Tangent function

### 7.4 Utility Functions
- `type_of(any) -> str` - Get type name as string
- `to_string(any) -> str` - Convert value to string representation

---

## 8. Integration with Limit Compiler

### 8.1 Compilation Pipeline
1. **Frontend**: Limit source → AST
2. **Type Checker**: AST → Typed AST
3. **LIR Generator**: Typed AST → LIR
4. **JIT Compiler**: LIR → Native Code

### 8.2 Register Allocation
- The LIR generator performs register allocation during code generation
- Each function maintains its own register space
- Type information is preserved for JIT compilation

### 8.3 Function Management
- Functions are registered in a global function registry
- Builtin functions are pre-registered during initialization
- User-defined functions are registered during compilation

---

## 9. Control Flow Graph (CFG)

LIR supports both linear instruction sequences and Control Flow Graphs:

### 9.1 Basic Blocks
- Instructions are grouped into basic blocks
- Each block has a unique ID and optional label
- Blocks are connected by edges representing control flow

### 9.2 CFG Operations
- `create_block(label)` - Create new basic block
- `add_edge(from, to)` - Connect blocks
- `flatten_cfg()` - Convert CFG to linear instruction sequence

---

## 10. Memory Management

### 10.1 Register Types
- Each register has an associated ABI type (`I32`, `I64`, `F64`, etc.)
- Language-level type information is preserved for debugging
- Type conversions are explicit through `Cast` instructions

### 10.2 Value Representation
- Constants are stored as `ValuePtr` objects
- Runtime values are managed by the VM/JIT
- Memory allocation is handled by the runtime system

---

## 11. Instruction Format

### 11.1 LIR_Inst Structure
```cpp
struct LIR_Inst {
    LIR_Op op;             // Operation
    Type result_type;      // Type of the result register (ABI-level)
    Reg dst;               // Destination register
    Reg a;                 // Operand 1 (source register)
    Reg b;                 // Operand 2 (source register, optional)
    Imm imm;               // Immediate value (optional)
    ValuePtr const_val;    // Constant value (for LoadConst operations)
    
    // Enhanced function call support
    std::string func_name;          // Function name (for calls)
    std::vector<Reg> call_args;     // Arguments for calls
};
```

### 11.2 Instruction Constructors
```cpp
// Basic instruction
LIR_Inst(LIR_Op::Add, Type::I64, dst_reg, src1_reg, src2_reg)

// Load constant
LIR_Inst(LIR_Op::LoadConst, Type::I64, dst_reg, constant_value)

// Function call
LIR_Inst(LIR_Op::Call, dst_reg, "function_name", {arg1_reg, arg2_reg})
```

---

## 12. Optimization

### 12.1 Optimization Flags
```cpp
struct OptimizationFlags {
    bool enable_peephole : 1;
    bool enable_const_fold : 1;
    bool enable_dead_code_elim : 1;
};
```

### 12.2 Available Optimizations
- **Peephole optimization**: Local instruction pattern matching
- **Constant folding**: Compile-time evaluation of constants
- **Dead code elimination**: Removal of unused instructions

---

## 13. Debug Information

### 13.1 Source Location Tracking
```cpp
struct LIR_SourceLoc {
    std::string filename;
    uint32_t line;
    uint32_t column;
};
```

### 13.2 Debug Info Structure
```cpp
struct LIR_DebugInfo {
    std::string function_name;
    LIR_SourceLoc loc;
    std::unordered_map<uint32_t, std::string> var_names; // reg -> name
    std::unordered_map<uint32_t, LIR_SourceLoc> reg_defs; // reg -> definition location
};
```

---

## 14. Disassembly

### 14.1 Disassembler Usage
```cpp
LIR::Disassembler disasm(function, true); // true for debug info
std::string assembly = disasm.disassemble();
```

### 14.2 Example Disassembly Output
```
function add(2):
  r2 = add r0, r1 : I64    # line 3: return a + b;
  ret r2                   # line 3: return a + b;
```

---

*For more information, see the complete [Limit Programming Language Documentation](../README.md).*