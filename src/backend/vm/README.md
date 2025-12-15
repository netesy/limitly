# VM Backend

This folder contains virtual machine implementations for executing Limitly programs.

## Files

- `vm.cpp/hh` - Stack-based virtual machine implementation

## Description

The VM backend provides an interpreted execution environment for Limitly programs. This is useful for:

- Debugging and testing
- Platforms where JIT compilation is not available
- Runtime code generation and evaluation

The current implementation uses a stack-based architecture. A register-based VM could be added in the future for better performance.
