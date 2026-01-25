# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./docs/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference.
*   **Structured Concurrency:** High-level `parallel` and `concurrent` blocks (syntax and AST only, VM support pending).
*   **Modern Error Handling:** A unified `Type?` system for robust error handling without exceptions.
*   **Object-Oriented:** Basic support for classes (inheritance and polymorphism are partial).
*   **Modules:** A flexible module system for organizing code (VM support pending).
*   **AOT Compilation:** An AOT compiler for high-performance applications.

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
