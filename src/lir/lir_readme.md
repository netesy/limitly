# LIR (Low-Level Intermediate Representation)

This folder contains the register-based Low-Level Intermediate Representation system for Limitly.

## Files

- `lir.cpp/hh` - Register-based LIR instruction definitions and utilities
- `lir_generator.cpp/hh` - AST to register-based LIR generator

## Description

LIR is a register-based intermediate representation that sits between the frontend AST and backend execution. It provides:

- **Register Allocation**: Virtual registers (r0, r1, r2, ...) with automatic allocation
- **Instruction Set**: Arithmetic, logical, comparison, control flow, and memory operations
- **Lowering**: Converts AST nodes to register-based LIR instructions
- **Backend Integration**: Works with both register VM and JIT backends

## Instruction Format

```
LIR_Inst {
    LIR_Op op;     // Operation type
    Reg dst;       // Destination register
    Reg a;         // Source register 1
    Reg b;         // Source register 2 (optional)
    Imm imm;       // Immediate value (optional)
    LIR_Value const_val; // Constant value (for LoadConst)
}
```

## Key Operations

- **Mov**: Register-to-register moves
- **LoadConst**: Load constants into registers
- **Arithmetic**: Add, Sub, Mul, Div, Mod
- **Comparison**: CmpEQ, CmpNEQ, CmpLT, CmpLE, CmpGT, CmpGE
- **Control Flow**: Jump, JumpIfFalse, Call, Return
- **Memory**: Load, Store
- **String**: Concat

## Usage Flow

1. Frontend generates AST
2. LIR generator converts AST to register-based LIR
3. LIR can be executed by:
   - Register VM (backend/register/register)
   - JIT backend (backend/jit/jit)
