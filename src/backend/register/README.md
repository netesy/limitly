# Register Backend

This folder contains register-based backend components for executing LIR instructions.

## Files

- `register_vm.cpp/hh` - Register-based virtual machine (renamed from lir_interpreter)

## Description

The register backend provides execution support for register-based LIR instructions:

- **Register VM**: Simple virtual machine for executing register-based LIR instructions
- **Integration**: Works with LIR generator and JIT backend

## VM Architecture

The register VM implements a interpreter for register-based LIR:

- Virtual registers (r0, r1, r2, ...)
- Instruction pointer-based execution
- Support for arithmetic, logical, and control flow operations
- Type system with int, float, bool, string, and nil values

This VM is useful for:
- Debugging LIR generation
- Testing without JIT compilation
- Platforms where native compilation isn't available
