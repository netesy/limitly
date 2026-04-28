# Contributing to Limit

## 1. Development Workflow

1. **Build**: Use `make linux` to build the `bin/limitly` executable.
2. **Test**: Run `bash tests/run_tests.sh` to execute the full test suite.
3. **Format**: The codebase follows standard C++ conventions. A formatter is integrated into `libLimitly`.

## 2. Code Organization

- `src/frontend/`: Scanner, Parser, AST, and Type Checker.
- `src/lir/`: LIR definition and generation logic.
- `src/backend/`: Register VM and Fyra AOT integration.
- `std/`: The standard library (written in Limit).
- `tests/`: Comprehensive test suite grouped by feature.

## 3. Submission Guidelines

- All new features must include corresponding tests in `tests/`.
- Documentation in `docs/` must be updated to reflect syntax or API changes.
- Ensure the audit traceability in `docs/verification.md` is maintained.
