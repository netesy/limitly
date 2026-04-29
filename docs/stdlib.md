# Limit Standard Library Reference

This document describes the built-in functions and core modules available in the Limit standard library.

## 1. Global Built-in Functions

### 1.1 I/O and System
- `print(args...)`: Prints arguments to standard output followed by a newline.
- `input(prompt: str): str`: Displays a prompt and reads a line from standard input.
- `clock(): float`: Returns the current CPU time in seconds.
- `time(): int`: Returns the current system time in seconds since the epoch.
- `sleep(seconds: float)`: Suspends execution for the specified duration.

### 1.2 File Operations
- `file_open(path: str, mode: str): int64`: Opens a file and returns a handle. Modes: `r`, `w`, `a`, `r+`, `w+`, `a+`.
- `file_read(handle: int64): str`: Reads the entire content of a file.
- `file_write(handle: int64, content: str)`: Writes content to a file.
- `file_close(handle: int64)`: Closes the file handle.
- `file_exists(path: str): bool`: Checks if a file exists.
- `file_delete(path: str): bool`: Deletes a file.

### 1.3 Utilities
- `assert(condition: bool, message: str)`: Throws a runtime error if the condition is false.
- `typeof(value: any): str`: Returns a string representation of the value's type.
- `to_int(s: str): int?`: (Planned) Parses a string to an integer. Currently handled via `std/parse.lm`.

## 2. Core Module (`std/core.lm`)

The core module defines the fundamental frames used for safe error handling and optionality.

### 2.1 `Error`
A basic frame for error representation.
- `code: str`
- `message: str`

### 2.2 `OptionInt` / `OptionStr`
Used to represent optional values for primitive types.
- `is_some(): bool`
- `is_none(): bool`
- `unwrap(): T`: Returns the value or a default (0 / "").
- `unwrap_or(default: T): T`: Returns the value or the provided default.

### 2.3 `ResultInt` / `ResultStr`
Used for fallible operations.
- `is_ok(): bool`
- `is_err(): bool`
- `unwrap(): T`
- `map(f: fn(T): T): Result`
- `map_err(f: fn(str): str): Result`

## 3. Communication

### `channel(): Channel`
Creates a new communication channel for structured concurrency.
- `.send(value)`: Blocking send.
- `.receive(): T?`: Blocking receive.
- `.poll(): T?`: Non-blocking receive.
- `.offer(value): bool`: Non-blocking send.
