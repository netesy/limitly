# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./docs/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference.
*   **Structured Concurrency (Syntax Only):** High-level `parallel` and `concurrent` blocks are parsed but not yet implemented in the VM.
*   **Modern Error Handling:** A unified `Type?` system for robust error handling without exceptions.
*   **Object-Oriented (Partial):** Basic support for classes. Inheritance and polymorphism are not yet implemented.
*   **First-Class Functions (Not Started):** Higher-order functions and closures are planned for a future release.
*   **Pattern Matching (Not Started):** Powerful `match` statements are planned but not yet implemented.
*   **Modules (Syntax Only):** A flexible module system is parsed but not yet implemented in the VM.
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
