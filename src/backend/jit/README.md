# JIT Backend

This folder contains Just-In-Time compilation backends for the Limitly language.

## Files

- `jit_backend.cpp/hh` - Original AST-based JIT backend (legacy)
- `jit.cpp/hh` - Register-based LIR JIT backend
- `libgccjit.h` - libgccjit C API bindings
- `libgccjit++.h` - libgccjit C++ wrapper

## Description

The JIT backend compiles intermediate representations to native machine code using libgccjit. There are two approaches:

1. **Legacy AST-based**: Directly compiles AST nodes to machine code
2. **New LIR-based**: Compiles register-based LIR instructions to machine code

The new LIR-based approach provides better optimization opportunities and cleaner separation between frontend and backend.
