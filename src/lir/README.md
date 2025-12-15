# Register Backend

This folder contains the register-based Low-Level Intermediate Representation (LIR) system.

## Files

- `lir.cpp/hh` - Register-based LIR instruction definitions and utilities
- `generator.cpp/hh` - AST to register-based LIR generator
- `lir_utils.cpp/hh` - Optimzations for the register-based LIR

## Description

The register backend implements a modern register-based intermediate representation that provides:

- **Register Allocation**: Virtual registers (r0, r1, r2, ...) with automatic allocation
- **Instruction Set**: Arithmetic, logical, comparison, control flow, and memory operations
- **Lowering**: Converts AST nodes to register-based LIR instructions
- **Interpretation**: Simple VM for executing LIR instructions
- **JIT Integration**: Works with the JIT backend for native compilation

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
