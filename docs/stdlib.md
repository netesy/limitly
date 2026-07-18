# Limit Standard Library Reference

This document describes the built-in functions and core modules available in the Limit standard library.

## 1. Global Built-in Functions

### 1.1 I/O and System
- `print(args...)`: Prints arguments to standard output followed by a newline. Supports variable arguments of types: int (all variants), float, decimal (d2, d4, d6), bool, string, nil, any.
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
- `resource_create(type_id: int): int64`: Creates a resource handle of the given type. Types: `0`=FILE, `1`=SOCKET (TCP), `5`=CHANNEL, `9`=STDOUT, `10`=STDERR, `11`=MEMORY, `12`=ENTROPY, `13`=DNS_RESOLVER, `14`=UDP_SOCKET, `15`=WEBSOCKET, `16`=HASH_ENGINE.
- `resource_call(handle: int64, op: int [, data: any]): any`: Invokes an operation on a resource. The 3-arg form passes `data` as the operation argument.
- `resource_destroy(handle: int64): nil`: Releases a resource handle.

### 1.4 Utilities
- `assert(condition: bool, message: str)`: Throws a runtime error if the condition is false.
- `typeof(value: any): str`: Returns a string representation of the value's type.
- `len(value: any): int`: Returns the length of strings, lists, dicts, and other collections.

## 2. Core Module (`std/core.lm`)

The core module defines the fundamental frames used for safe error handling and optionality. All frames use `pub` visibility for their members; `self` is the instance reference.

### 2.1 `Error`
A basic frame for error representation.
- `pub var code: str`
- `pub var message: str`

### 2.2 `OptionInt` / `OptionStr`
Used to represent optional values for primitive types.
- `pub var has_value: bool`
- `pub var value: T` (int or str)
- `pub fn is_some(): bool`: Returns true if value is present.
- `pub fn is_none(): bool`: Returns true if no value is present.
- `pub fn unwrap(): T`: Returns the value or a default (0 / "").
- `pub fn unwrap_or(default_value: T): T`: Returns the value or the provided default.

### 2.3 `ResultInt` / `ResultStr`
Used for fallible operations.
- `pub var success: bool`
- `pub var value: T` (int or str)
- `pub var error_info: Error`
- `pub fn is_ok(): bool`: Returns true if operation succeeded.
- `pub fn is_err(): bool`: Returns true if operation failed.
- `pub fn unwrap(): T`: Returns the value or a default (0 / "").
- `pub fn unwrap_or(default_value: T): T`: Returns the value or the provided default.
- `pub fn map(f: fn(T): T): Result`: Applies `f` to the ok value (if any), returning a new Result.
- `pub fn map_err(f: fn(str): str): Result`: Applies `f` to the error message (if err), returning a new Result.

### 2.4 Constructor helpers
- `pub fn some_int(value: int): int`: Returns the value (simplified version).
- `pub fn some_str(value: str): str`: Returns the value (simplified version).
- `pub fn ok_int(v: int): ResultInt`: Creates a successful ResultInt.
- `pub fn err_int(e: str): ResultInt`: Creates a failed ResultInt with error message.
- `pub fn make_err_int(e: str): ResultInt`: Alias for err_int.
- `pub fn ok_str(v: str): ResultStr`: Creates a successful ResultStr.
- `pub fn err_str(e: str): ResultStr`: Creates a failed ResultStr with error message.
- `pub fn make_err_str(e: str): ResultStr`: Alias for err_str.
- `pub fn ok_bool(v: bool): ResultInt`: Creates a ResultInt with 1 for true, 0 for false.

## 3. Communication

### `channel(): Channel`
Creates a new communication channel for structured concurrency. (`channel` is a regular identifier — it's a builtin function, not a keyword.)
- `.send(value)`: Blocking send.
- `.receive(): T?`: Blocking receive.
- `.poll(): T?`: Non-blocking receive.
- `.offer(value): bool`: Non-blocking send.

## 4. String Module (`std/string.lm`)

The string module provides comprehensive string manipulation functions using only built-in operations.

### String Functions
- `fn length(value: str): int`: Returns the length of the string (wraps `len()`).
- `fn contains(value: str, needle: str): bool`: Checks if needle is in value.
- `fn starts_with(value: str, prefix: str): bool`: Checks if value starts with prefix.
- `fn ends_with(value: str, suffix: str): bool`: Checks if value ends with suffix.
- `fn split(value: str, delimiter: str): [str]`: Splits string by delimiter into list.
- `fn join(values: [str], delimiter: str): str`: Joins list of strings with delimiter.
- `fn trim(value: str): str`: Removes whitespace from both ends.
- `fn replace(value: str, old: str, replacement: str): str`: Replaces all occurrences of old with replacement.
- `fn substring(value: str, start: int, end: int): str`: Built-in function to extract substring.
- `fn lowercase(value: str): str`: Converts to lowercase.
- `fn uppercase(value: str): str`: Converts to uppercase.
- `fn to_lower(value: str): str`: Alias for lowercase.
- `fn to_upper(value: str): str`: Alias for uppercase.
- `fn compare(left: str, right: str): int`: Compares two strings (-1, 0, 1).
- `fn format_pair(key: str, value: str): str`: Formats as "key=value".
- `fn is_empty(value: str): bool`: Checks if string is empty.
- `fn reverse(value: str): str`: Reverses the string.
- `fn index_of(value: str, needle: str): int`: Returns first index of needle, or -1.
- `fn last_index_of(value: str, needle: str): int`: Returns last index of needle, or -1.
- `fn repeat(value: str, count: int): str`: Repeats string count times.
- `fn pad_left(value: str, total_length: int, pad_char: str): str`: Pads string on left.
- `fn pad_right(value: str, total_length: int, pad_char: str): str`: Pads string on right.
- `fn count_occurrences(value: str, needle: str): int`: Counts non-overlapping occurrences.
- `fn is_palindrome(value: str): bool`: Checks if string is a palindrome.

## 5. Parsing (`std/parse.lm`)

### `Parse` frame
Pure-Limitly string parsers.
- `Parse.int(s: str): ResultInt`: Parses a base-10 integer with optional leading `+`/`-`. Returns `err_int` on invalid input.
- `Parse.float(s: str): ResultStr`: Returns the input string wrapped in `ok_str` (placeholder).
- `Parse.bool(s: str): bool`: Recognises `"true"`/`"1"` as true; everything else is false.

## 6. Encoding (`std/encoding.lm`)

### `Encoding` frame
Static-method namespace for encoding conversions.
- `Encoding.base64_encode(data: str): str`
- `Encoding.base64_decode(data: str): str`
- `Encoding.hex_encode(data: str): str`
- `Encoding.hex_decode(data: str): str`
- `Encoding.byte_to_hex(b: int): str`
- `Encoding.hex_to_byte(h: str): int`

## 7. I/O (`std/io.lm`)

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

## 8. FFI (`std/ffi.lm`)

The FFI module provides typed wrappers around the libffi-based native call infrastructure. See the module source for the full API surface (memory allocation, pointer load/store, library loading, typed ccall helpers).

## 9. Other Modules

The standard library also includes: `math`, `random`, `time`, `collections` (with submodules `vector`, `list`, `stack`, `queue`, `hashmap`, `set`, `tree`), `data_structures`, `parsers` (`json`, `toml`, `yaml`), `net` (`tcp`, `udp`, `dns`), `http` (`client`, `server`), `crypto` (`hash`, `hmac`, `random`), `fs`, `log`, `path`, `format`, `regex`, `bytes`, `color`, `cli`, `env`, `process`, `async`, `validation`, `statistics`, `linear_algebra`, `geometry`, `sort`, `search`, `algorithm`, `functional`, `iter`, `debug`, `url`, `serialization`, `app`, `archive`, `image`, `config`.

The umbrella `std/std.lm` re-exports the most commonly used modules. Note that some modules are stubs (process, env, archive, net/dns, http/*) — they return real errors rather than silently succeeding.

## 10. Group 2 Standard Library Modules

The standard library Group 2 modules use parser-supported statement syntax only: control flow is expressed with `if (...) { ... } else { ... }`, `while (...) { ... }`, and `for (...) { ... }`; method receivers use `self`; and collection type annotations use concrete shorthand such as `[int]`, `[any]`, `{str: int}`, and tuple types.

### `std.sort`

`std.sort` provides in-place sorting over `[any]` plus integer counting/radix helpers:

- `insertion_sort(items, descending = false, cmp = nil)`
- `quicksort(items, descending = false, cmp = nil)`
- `mergesort(items, descending = false, cmp = nil)`
- `heapsort(items, descending = false, cmp = nil)`
- `counting_sort(items: [int], descending = false)`
- `radix_sort(items: [int], descending = false)`
- `timsort(items, descending = false, cmp = nil)`
- `stable_sort(items, descending = false, cmp = nil)`
- `partial_sort(items, count, descending = false, cmp = nil)`

Comparators have type `fn(any, any): int` and return a negative value, zero, or a positive value.

### `std.search`

`std.search` provides `linear_search`, `binary_search`, `interpolation_search`, `lower_bound`, `upper_bound`, and `equal_range`.

### `std.algorithm`

`std.algorithm` provides `map`, `filter`, `reduce`, `fold`, `transform`, `zip`, `unzip`, `partition`, `reverse`, `rotate`, `unique`, `count`, `find`, `find_if`, `any`, `all`, `none`, and `remove_if`.

### `std.iterator`

`std.iterator` provides iterator frames and adapters for `iter`, `map`, `filter`, `enumerate`, `zip`, `chain`, `flatten`, `skip`, `take`, `step_by`, `chunk`, `cycle`, `peekable`, and `collect`.

### `std.range`

`std.range` provides `exclusive`, `inclusive`, `stepped`, `reverse`, and `infinite` range constructors. Each range creates a `RangeIterator` through `iter()`.

### `std.collections`

The collections index re-exports `Vector`, `ArrayList`, `LinkedList`, `Deque`, `RingBuffer`, `Queue`, `Stack`, `PriorityQueue`, `BitSet`, `TreeMap`, `TreeSet`, and `BTree` from pure standard-library modules.

## 11. Additional Core Modules

### `std.option`

`std.option` provides `Option`, `Some(value)`, and `None()`. `Option` supports `is_some`, `is_none`, `unwrap`, `unwrap_or`, `map`, and `filter`.

### `std.result`

`std.result` provides `Result`, `Ok(value)`, and `Err(error)`. `Result` supports `is_ok`, `is_err`, `unwrap`, `unwrap_or`, `unwrap_err`, and `map`.

## 12. Standard Library Test Layout

New standard-library regression tests live under `tests/stdlib/` with `.lm` source files grouped by module area: `collections`, `sort`, `search`, `algorithm`, `iterator`, `range`, and `core`.
