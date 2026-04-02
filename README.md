# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

> **Current execution model:** the primary working system in this repository is the **register VM pipeline** (`frontend -> type checker -> LIR -> Register VM`).
> For language syntax/examples, treat the `tests/` directory as the source of truth.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./docs/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference.
*   **Structured Concurrency:** `parallel`, `concurrent`, `task`, and channel primitives.
*   **Enums + Pattern Matching:** Enum construction (including payload variants) and `match` destructuring.
*   **Modern Error Handling:** `Option`/union-style handling and error-oriented patterns.
*   **Object-Oriented (Frames & Traits):** Frame + trait model with init/deinit lifecycle support.
*   **First-Class Functions:** Higher-order functions and closures.
*   **Modules:** A flexible module system for organizing code.
*   **VM-backed execution:** LIR lowered into the register VM backend.

## ✅ Syntax/Capability Snapshot (from `tests/`)

These are all actively exercised in the test suite:

* Variables, literals, interpolation, arithmetic/logical expressions
* Control flow: `if/else`, `for`, `while`, `iter`, `match`
* Collections: list, dict, tuple
* Functions, optional/default args, closures, first-class functions
* Enums:
  * unit variants (`Color.Red`)
  * payload variants (`Result.Success("ok")`)
  * match on variants (including payload binds)
* Modules/import aliases (`import ... as ...`)
* Frames/traits and visibility tests
* Concurrency primitives (`parallel` / `concurrent`)

## 🛠️ Building and Running

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler

### Build Instructions
```bash
# Using Make (recommended for cross-platform)
make

# Using Windows Batch (MSYS2/MinGW64)
build.bat

# Using Unix Shell
./build.sh
```

### Running
```bash
# Execute a source file
./bin/limitly sample.lm

# Start the REPL (interactive mode)
./bin/limitly -repl
```

## Testing

The project includes a comprehensive test suite in the `tests/` directory.

```bash
# Run all tests (silent mode)
./tests/run_tests.sh
./tests/run_tests.bat

```
