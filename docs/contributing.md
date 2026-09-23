# Contributing to Limit

## 1. Development Workflow

1. **Prerequisites**: A C++20 compatible compiler (GCC 11+, Clang 13+, or MSVC) and GNU `make`. Windows requires MSYS2 MinGW64.
2. **Build**: Run `make` to compile the `bin/limitly` executable (or `bin/limitly.exe` on Windows).
3. **Debug Build**: Run `make MODE=debug` to compile with full debug symbols and sanitizers.
4. **Test**: Run `python tests/run_tests.py` to execute the automated test runner across the test suite.
5. **Format**: The codebase follows standard C++ conventions. Source files can be formatted with `./bin/limitly -format <file>`.

## 2. Code Organization

- `src/frontend/`: Scanner, Parser, CST, AST, Type Checker, and Memory Checker.
- `src/lir/`: Low-level Intermediate Representation (LIR) definition, basic block analysis, and lowering.
- `src/backend/vm/`: Bytecode Register VM implementation for direct execution (`limitly run`).
- `src/backend/fyra/`: Fyra AOT backend integration for native code generation (`limitly build`).
- `std/`: The standard library (written in Limitly).
- `tests/`: Automated test suite categorized by language feature.

## 3. Submission Guidelines

- All bug fixes and language additions must include regression tests in `tests/`.
- Ensure commit messages are concise, conventional, and single-line (under 80 characters, no emojis).
- Keep documentation in `docs/` synchronized with actual compiler behavior.
