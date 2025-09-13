# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./doc/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference.
*   **Structured Concurrency:** High-level `parallel` and `concurrent` blocks for safe and efficient multi-tasking.
*   **Modern Error Handling:** `Option` and `Result` types for robust error handling without exceptions.
*   **Object-Oriented:** Support for classes, inheritance, and polymorphism.
*   **First-Class Functions:** Higher-order functions and closures.
*   **Pattern Matching:** Powerful `match` statements for expressive control flow.

## 🛠️ Building and Running

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler

### Build Instructions
```bash
# Using CMake (recommended for cross-platform)
mkdir build && cd build
cmake ..
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
./run_tests.bat

# Run all tests (verbose mode)  
./run_tests_verbose.bat
```