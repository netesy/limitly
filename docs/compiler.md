# Limitly Compiler & Standard Library Architecture

## 1. Compiler Driver & CLI Interface

The compiler entry point is implemented in `src/main.cpp` and `src/limitly.cpp`.

### Execution Subcommands

- **`limitly run [options] <source_file>`**:
  Parses, type-checks, lowers to LIR, and executes the program using the internal bytecode Register VM.
  - `-debug`: Enables diagnostic tracing during execution.
  - `--verify=strict`: Enforces strict static verification for all contracts and refinement types.
  - `--verify=hybrid`: Retains dynamic runtime assertions for unproven contracts (default).

- **`limitly build [options] <source_file>`**:
  Compiles the program into native object code or standalone executables via the Fyra AOT backend.
  - `-target <windows|linux|macos|wasm>`: Target platform.
  - `-o <output_path>`: Specifies output binary name.
  - `-O <0|1|2|3>`: Optimization level.
  - `-s` or `--strip`: Strips debug symbols and metadata.

### Tooling & Debugging Commands

- `limitly -tokens <file>`: Prints the lexical token stream produced by `Scanner`.
- `limitly -cst <file>`: Prints the Concrete Syntax Tree produced by `Parser`.
- `limitly -ast <file>`: Prints the Abstract Syntax Tree using `ASTPrinter`.
- `limitly -lir <file>`: Prints disassembled LIR instructions.
- `limitly -fyra-ir <file>`: Prints the Fyra intermediate representation.
- `limitly -format <file>`: Runs the built-in source code formatter.
- `limitly -lsp`: Spawns the Language Server Protocol background daemon.

---

## 2. Standard-Library Boundary & Type Ownership

### Compiler-Owned Types
Type definitions are strictly owned by the compiler and cannot be redefined in userland or standard library code:
- Primitives (`int`, `uint`, `float`, `bool`, `str`, `nil`, fixed-width scalars).
- Decimals (`d2`, `d4`, `d6`).
- Collection primitives: `[Type]` (lists), `{Key: Val}` (dictionaries), `(T1, T2)` (tuples).
- Fallible types: `Type?` and `Type?Error1,Error2`.

### Stdlib-Owned Behavior
The standard library in `std/` provides algorithms and userland data structures using compiler-owned types:
- `std/collections/`: Implements vectors, queues, stacks, and sets wrapping `[T]`.
- `std/math/`: Trigonometry, logarithms, and arithmetic algorithms.
- `std/string/`: Text manipulations, builders, and encodings.
- `std/crypto/`, `std/archive/`, `std/net/`: Wrappers delegating to low-level native libraries via the C ABI FFI adapter boundary.
