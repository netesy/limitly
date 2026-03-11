# Limit Programming Language

Limit is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## 🚀 Get Started

To learn how to use the Limit language, check out our comprehensive, step-by-step guide:

**[➡️ Read the Full Guide](./docs/guide.md)**

## ✨ Features

*   **Static Typing:** A strong, static type system with type inference.
*   **Structured Concurrency:** High-level `parallel` and `concurrent` blocks for safe and efficient multi-tasking.
*   **Modern Error Handling:** `Option` and `Result` types for robust error handling without exceptions.
*   **Object-Oriented (Frames & Traits):** Efficient, modern OOP with static dispatch, traits, and automatic lifecycle management (init/deinit).
*   **First-Class Functions:** Higher-order functions and closures.
*   **Pattern Matching:** Powerful `match` statements for expressive control flow.
*   **Modules:** A flexible module system for organizing code.
*   **AOT Compilation:** An AOT compiler for high-performance applications.

## 🛠️ Building and Running

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler

### Build Instructions
```bash
# Initialize Fyra backend submodule (required for embedded AOT backend)
git submodule update --init --recursive

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

# Print frontend/IR forms
./limitly -ast sample.lm
./limitly -lir sample.lm
./limitly -fyra-ir sample.lm

# Production path (preferred): AST -> Fyra IR -> executable
./limitly -aot sample.lm

# Compatibility path: LIR -> Register VM interpreter
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

# Run embedded Fyra AOT on all non-OOP tests (skips classes/oop suites)
./tests/run_fyra_non_oop_tests.sh

```
