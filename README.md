# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./docs/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference.
*   **Advanced Function System:** Optional parameters (`name: str?`), default parameters (`name: str = "World"`), and nested calls.
*   **Unified Error/Optional Types:** A unified `Type?` system for robust error and optional value handling.
*   **Memory Safety:** Region-based, deterministic memory management without a garbage collector.
*   **Modern Control Flow:** Includes `if/else`, `while`, `for`, and range-based `iter` loops.
*   **String Interpolation:** Easily embed expressions in strings, like `"Hello, {name}!"`.
*   **Partial Class Support:** Basic class syntax, fields, and methods are implemented (inheritance is not yet supported).
*   **AOT Compilation:** An AOT compiler for high-performance applications (experimental).

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
./limitly sample.lm

# Start the REPL (interactive mode)
./limitly -repl
```

## Testing

The project includes a comprehensive test suite in the `tests/` directory.

```bash
# Run all tests (silent mode)
./tests/run_tests.bat
./tests/run_tests.sh

```
