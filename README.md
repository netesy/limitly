# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## Get Started

To learn how to use the Limit language, check out our comprehensive guides:

- **[Quickstart & Beginner Tutorial](./docs/learn.md)**
- **[Full Language Guide](./docs/guide.md)**
- **[Formal Language Specification](./docs/language.md)**
- **[Compiler & Architecture](./docs/architecture.md)**

## Features

- **Static Typing & Inference:** A strong, static type system with local type inference, fixed-width scalars (`i8`..`i128`, `u8`..`u128`, `f32`/`f64`), fixed-scale decimals (`d2`, `d4`, `d6`), and type casts (`as`).
- **Structured Concurrency:** Lexically-scoped `parallel` (data parallelism) and `concurrent` (cooperative task/worker) blocks communicating through typed `channel` primitives.
- **Native Error Handling (`Type?`):** Zero-overhead compiler-level error unions using `ok(val)` and `err()` / `err(Type)` constructors, the `?` propagator, and inline `? else { ... }` fallbacks without generic overhead.
- **Object-Oriented Programming (Frames & Traits):** Class-like `frame` structures with traits, composition, explicit visibility (`pub`, `prot`, private by default), and lifecycle hooks (`pub init` / `pub deinit`) using canonical `self`.
- **First-Class Functions & Closures:** Higher-order functions, function types (`fn(T): R`), and lexical closures.
- **Pattern Matching:** Expressive `match` construct supporting value literals, enum variants, structural bindings, fallible patterns (`val success => ...`, `err error => ...`), and wildcards (`_`).
- **Modules & Import Filtering:** Hierarchical module resolution with aliasing (`as`), symbol inclusion (`show`), and exclusion (`hide`).
- **Dual Execution Backends:** High-performance bytecode Register VM for instant execution and debugging (`run`), plus native AOT / WASM compilation via Fyra (`build`).

## Source of Truth & Runtime Status

The **authoritative source of truth** for currently supported syntax and semantics is the compiler codebase (`src/`) and the passing test suites in `tests/`:

- `tests/basic/`, `tests/expressions/`, `tests/loops/`, `tests/functions/`
- `tests/types/` (including enums, decimal arithmetic, and pattern matching)
- `tests/modules/` (imports, aliases, and symbol filters)
- `tests/oop/` (frames, traits, field visibility, and initialization)
- `tests/concurrency/` (`parallel`, `concurrent`, tasks, workers, and channels)

## Building and Running

### Prerequisites
- C++20 compatible compiler (e.g., GCC 11+, Clang 13+, or MSVC)
- GNU Make (or CMake 3.20+)
- Windows: MSYS2 MinGW64 environment (`g++`, `make`)

### Build Instructions

```bash
# Build release compiler (bin/limitly or bin/limitly.exe)
make

# Build debug compiler with symbols
make MODE=debug

# Clean build artifacts
make clean
```

### Running Limit Programs

The `limitly` binary provides clear subcommands:

```bash
# Execute a Limit source file using the Register VM
./bin/limitly run path/to/script.lm

# Run with verbose debug output
./bin/limitly run -debug path/to/script.lm

# Run with strict contract/refinement verification
./bin/limitly run --verify=strict path/to/script.lm

# Compile to native binary via Fyra AOT backend
./bin/limitly build -o output_app path/to/script.lm

# Tooling and Inspection
./bin/limitly -tokens path/to/script.lm   # Print scanned tokens
./bin/limitly -cst path/to/script.lm      # Print Concrete Syntax Tree
./bin/limitly -ast path/to/script.lm      # Print Abstract Syntax Tree
./bin/limitly -lir path/to/script.lm      # Print Low-level Intermediate Representation
./bin/limitly -format path/to/script.lm   # Format a source file
./bin/limitly -lsp                       # Start Language Server Protocol daemon
```

## Testing

The test suite runs each test individually against the Register VM with timeouts to prevent hangs:

```bash
# Run all automated tests via Python test runner
python tests/run_tests.py
```
