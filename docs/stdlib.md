# Limit Standard Library Reference

This document describes the built-in functions and core modules available in the Limit standard library.

## 1. Global Built-in Functions

### 1.1 I/O and System
- `print(args...)`: Prints arguments to standard output followed by a newline.
- `input(prompt: str): str`: Displays a prompt and reads a line from standard input.
- `clock(): float`: Returns the current CPU time in seconds.
- `time(): int`: Returns the current system time in seconds since the epoch.
- `sleep(seconds: float)`: Suspends execution for the specified duration. (`sleep` is a regular identifier, not a keyword.)

### 1.2 File Operations
- `file_open(path: str, mode: str): int64`: Opens a file and returns a handle. Modes: `r`, `w`, `a`, `r+`, `w+`, `a+`.
- `file_read(handle: int64): str`: Reads the entire content of a file.
- `file_write(handle: int64, content: str)`: Writes content to a file.
- `file_close(handle: int64)`: Closes the file handle.
- `file_exists(path: str): bool`: Checks if a file exists.
- `file_delete(path: str): bool`: Deletes a file.

### 1.3 Resource System
- `resource_create(type_id: int): int64`: Creates a resource handle of the given type. Types: `0`=FILE, `1`=SOCKET, `9`=STDOUT, `10`=STDERR, `12`=ENTROPY, plus channel/memory types.
- `resource_call(handle: int64, op: int [, data: any]): any`: Invokes an operation on a resource. The 3-arg form passes `data` as the operation argument.
- `resource_destroy(handle: int64): nil`: Releases a resource handle.

### 1.4 Utilities
- `assert(condition: bool, message: str)`: Throws a runtime error if the condition is false.
- `typeof(value: any): str`: Returns a string representation of the value's type.

## 2. Core Module (`std/core.lm`)

The core module defines the fundamental frames used for safe error handling and optionality. All frames use `pub` visibility for their members; `self` is the instance reference.

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
- `unwrap_or(default: T): T`
- `map(f: fn(T): T): Result`: Applies `f` to the ok value (if any), returning a new Result.
- `map_err(f: fn(str): str): Result`: Applies `f` to the error message (if err), returning a new Result.

### 2.4 Constructor helpers
- `ok_int(v: int): ResultInt`
- `err_int(e: str): ResultInt`
- `ok_str(v: str): ResultStr`
- `err_str(e: str): ResultStr`
- `some_int(v: int): int?` / `none_int(): int?`
- `some_str(v: str): str?` / `none_str(): str?`

## 3. Communication

### `channel(): Channel`
Creates a new communication channel for structured concurrency. (`channel` is a regular identifier — it's a builtin function, not a keyword.)
- `.send(value)`: Blocking send.
- `.receive(): T?`: Blocking receive.
- `.poll(): T?`: Non-blocking receive.
- `.offer(value): bool`: Non-blocking send.

## 4. Parsing (`std/parse.lm`)

### `Parse` frame
Pure-Limitly string parsers.
- `Parse.int(s: str): ResultInt`: Parses a base-10 integer with optional leading `+`/`-`. Returns `err_int` on invalid input.
- `Parse.float(s: str): ResultStr`: Returns the input string wrapped in `ok_str` (placeholder).
- `Parse.bool(s: str): bool`: Recognises `"true"`/`"1"` as true; everything else is false.

## 5. Encoding (`std/encoding.lm`)

### `Encoding` frame
Static-method namespace for encoding conversions.
- `Encoding.base64_encode(data: str): str`
- `Encoding.base64_decode(data: str): str`
- `Encoding.hex_encode(data: str): str`
- `Encoding.hex_decode(data: str): str`
- `Encoding.byte_to_hex(b: int): str`
- `Encoding.hex_to_byte(h: str): int`

## 6. I/O (`std/io.lm`)

### `File` frame
- `pub fn read(): str?IOError`
- `pub fn write(content: str): nil?IOError`
- `pub fn close(): nil?IOError`

### `Console` frame
- `pub fn write_line(msg: str): nil`
- `pub fn read_line(): str`

### Free functions
- `open(path: str, mode: str): File?IOError`
- `exists(path: str): bool`: Wraps the native `file_exists` builtin.
- `delete(path: str): bool`: Wraps the native `file_delete` builtin.
- `create_directory(path: str): nil?IOError`: Not yet natively backed; returns a real error rather than silently succeeding.
- `list_directory(path: str): [str]?IOError`: Not yet natively backed; returns a real error.

## 7. FFI (`std/ffi.lm`)

The FFI module provides typed wrappers around the libffi-based native call infrastructure. See the module source for the full API surface (memory allocation, pointer load/store, library loading, typed ccall helpers).

## 8. Other Modules

The standard library also includes: `math`, `random`, `time`, `strings`, `iter`, `collections` (with submodules `vector`, `list`, `stack`, `queue`, `hashmap`, `set`, `tree`), `data_structures`, `parsers` (`json`, `toml`, `yaml`), `net` (`tcp`, `udp`, `dns`), `http` (`client`, `server`), `crypto` (`hash`, `hmac`, `random`), `fs`, `log`, `path`, `format`, `regex`, `bytes`, `color`, `cli`, `env`, `process`, `async`, `validation`, `statistics`, `linear_algebra`, `geometry`, `sort`, `search`, `algorithm`, `functional`, `iter`, `debug`, `url`, `serialization`, `app`, `archive`, `image`, `config`.

The umbrella `std/std.lm` re-exports the most commonly used modules. Note that some modules are stubs (process, env, archive, net/dns, http/*) — they return real errors rather than silently succeeding.
