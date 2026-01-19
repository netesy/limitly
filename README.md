# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./docs/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference, union types, and type aliases.
*   **Modern Error Handling:** A unified `Type?` system with an error propagation (`?`) operator for robust, exception-free error handling.
*   **Functions:** Support for optional parameters and default values.
*   **Object-Oriented Programming (Partial):** Basic support for classes, fields, and methods.
*   **Modules (Partial):** Parser and AST support for modules, with VM/runtime implementation in progress.
*   **Concurrency (Partial):** Parser and AST support for `parallel` and `concurrent` blocks, with VM/runtime implementation in progress.

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
