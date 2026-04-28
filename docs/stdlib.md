# Limit Standard Library Reference

This document describes the built-in functions and core modules available in the Limit standard library.

## 1. Built-in Functions

### `print(args...)`
Prints the provided arguments to standard output, followed by a newline. Supports string interpolation.

### `assert(condition: bool, message: str)`
Asserts that the condition is true. If false, the program terminates with the provided message.

### `to_int(s: str): int?`
Attempts to parse a string into an integer. Returns `ok(int)` on success or `err()` on failure.

## 2. Core Module (`std/core.lm`)

The core module provides fundamental types for error handling and optional values.

### `Error` Frame
Represents a generic error.
- `code: str`
- `message: str`

### `OptionInt` / `OptionStr` Frames
Provide explicit methods for handling optional values.
- `is_some(): bool`
- `is_none(): bool`
- `unwrap(): T`
- `unwrap_or(default: T): T`

### `ResultInt` / `ResultStr` Frames
Provide explicit methods for handling fallible operations.
- `is_ok(): bool`
- `is_err(): bool`
- `map(f: fn(T): T): Result<T>`

## 3. Communication

### `channel(): Channel`
Creates a new communication channel for use in `concurrent` or `parallel` blocks.
- `.send(value)`
- `.receive(): T?`
