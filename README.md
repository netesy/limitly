# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./docs/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference, union types, and type aliases.
*   **Unified Error/Optional Types:** A robust `Type?` system for handling errors and optional values without exceptions.
*   **Memory Safety:** Region-based, deterministic memory management with compile-time lifetime analysis.
*   **Advanced Functions:** Supports optional parameters, default parameters, and nested calls.
*   **Object-Oriented (Partial):** Basic support for classes and methods. Inheritance and polymorphism are under development.
*   **Module System (Partial):** Syntax for importing and exporting modules is supported by the parser, but runtime implementation is pending.
*   **Concurrency (Partial):** `parallel` and `concurrent` block syntax is parsed, but the VM implementation is pending.

### Planned Features
*   **Full Object-Oriented Support:** Inheritance, polymorphism, and abstract classes.
*   **First-Class Functions:** Higher-order functions and closures.
*   **Pattern Matching:** Powerful `match` statements for expressive control flow.
*   **Full Concurrency Support:** Complete VM implementation for `parallel` and `concurrent` blocks.

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
