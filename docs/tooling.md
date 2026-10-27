# Lymar Tooling Guide

The Lymar ecosystem ships with a complete, modern suite of developer tools designed to deliver instant developer velocity, static safety guarantees, and deep observability without relying on fragmented third-party utilities.

This guide provides a comprehensive manual for the tools available via `lymar` (the core compiler driver) and `lyra` (the package and workflow manager).

---

## Tooling Matrix

| Tool | CLI Command | Purpose |
| :--- | :--- | :--- |
| **First-Class Test Runner** | `lymar test` / `lyra test` | Discover and run test suites in parallel with high-resolution timings and fail-fast options. |
| **Documentation Generator** | `lymar doc` / `lyra doc` | Generate Markdown and standalone responsive HTML docs with real-time symbol search, callouts, and examples. |
| **Static Linter & Analysis** | `lymar lint` / `lyra lint` | Clippy-style rich terminal diagnostics for anti-patterns, unsupported constructs, and bugs. |
| **Benchmarking Harness** | `lymar bench` / `lyra bench` | Built-in micro-benchmarking with statistical warmup, iterations, and throughput metrics (`ns/op`). |
| **Runtime Observability & Profiler** | `lymar profile` | Statistical CPU and allocation profiling for function execution hot paths. |
| **Formal Verification Engine** | `lymar run --verify=...` | Compile-time and runtime solver for contracts (`contract`) and refinement types (`where`). |

---

## 1. First-Class Test Runner (`lymar test` / `lyra test`)

The test runner provides out-of-the-box parallel execution, granular test filtering, and clear assertion reports.

### Usage & Flags

```bash
# Run all tests discovered in tests/ or specified directories
lymar test

# Run tests in parallel with N worker threads (default: CPU core count)
lymar test -j 4
lymar test --parallel 8

# Filter tests by substring or wildcard
lymar test --filter "crypto"
lymar test -f "zlib"

# Abort test run immediately upon the first failure
lymar test --fail-fast

# Verbose output showing each test's duration
lymar test -v
```

### Writing Tests

Tests are standard `.lm` files that execute verification assertions or fallible tests:

```lymar
// tests/math_test.lm

fn test_addition() {
    var a = 10;
    var b = 20;
    contract(a + b == 30, "Addition failed");
}

fn main() {
    test_addition();
    print("All math tests passed");
}
```

---

## 2. Documentation Generator (`lymar doc` / `lyra doc`)

The documentation generator parses doc comments (`///` and `//`), module overviews, type annotations, contracts, and examples directly from your source code.

### Usage & Flags

```bash
# Emit GitHub-Flavored Markdown to stdout
lymar doc src/zlib.lm

# Output Markdown directly to a file
lymar doc src/zlib.lm -o docs/zlib.md

# Generate standalone, interactive HTML documentation
lymar doc --html src/zlib.lm -o docs/api/zlib.html

# Batch generate HTML documentation for an entire package directory
lymar doc --html src/ -o site/
```

### Writing Rich Docstrings

Lymar documentation comments support specialized tags and GitHub alert blocks to showcase **idiomatic usage ("the right way to use code")**, hazards, warnings, and runnable examples:

```lymar
/// Compresses an input string into raw deflate/zlib bytes encoded as hex.
///
/// @tip The idiomatic and recommended way to compress data is level 6: it achieves
/// 95% of maximal compression while running 4x faster than level 9.
///
/// @warning Always enforce a maximum buffer limit when decompressing untrusted inputs
/// to prevent memory exhaustion and zip-bomb denial of service attacks.
///
/// @note Thread-safe and allocation-safe; frees temporary native buffers on exit.
///
/// @pre len(data) > 0
/// @param data The raw ASCII or UTF-8 string to compress.
/// @param level Compression level between 0 (store) and 9 (max compression). Default is 6.
/// @return Returns ok(hex_str) on success, or err() on compression failure.
///
/// @example
/// var payload = "Hello, high-performance Lymar compression!";
/// var compressed = compress_hex(payload, 6)? else {
///     print("Compression failed");
///     return;
/// };
/// print("Compressed size: {len(compressed)}");
pub fn compress_hex(data: str, level: int = 6): str? {
    if (len(data) == 0) return ok("");
    return ok("789c...");
}
```

### HTML Documentation Features

* **Interactive Search**: Client-side instant filter for symbols in large codebases.
* **Colored Callout Cards**:
  * 💡 **Idiomatic Usage & Best Practice** (`@tip` / `> [!TIP]`)
  * ⚠️ **Warning** (`@warning` / `> [!WARNING]`)
  * ℹ️ **Note / Invariant** (`@note` / `> [!NOTE]`)
  * 🛑 **Caution** (`@caution` / `> [!CAUTION]`)
  * 🚫 **Deprecated** (`@deprecated`)
* **Example Editor Cards**: Highlighting copy-ready snippets.
* **Parameter & Return Tables**: Clean breakdowns of types and descriptions.

---

## 3. Static Linter & Analysis Engine (`lymar lint` / `lyra lint`)

The linter detects code smells, anti-patterns, and language violations before execution. It features friendly, Rust/Clippy-style diagnostics displaying line numbers, source snippets, carets, and actionable `= help:` hints.

### Diagnostic Presentation Example

```text
warning[list-concat]: List concatenation with '+' is unsupported in Lymar
  --> src/collections.lm:18:9
   |
18 |     var bad_concat = list1 + list2;
   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
   = help: in Lymar, '+' is not supported for lists; use 'append(list, item)' or 'append(list, other_list)' instead (AGENTS.md)
```

### Active Linter Rules

| Rule | Severity | Description & Fix Hint |
| :--- | :--- | :--- |
| `list-concat` | **Warning** | Flagged when using `list1 + list2`. In Lymar, list concatenation with `+` is unsupported; use `append(list, item)` or `append(list, other_list)`. |
| `self-comparison` | **Warning** | Flagged when comparing a variable to itself (e.g., `x == x`), which always yields a constant. |
| `variable-shadowing` | **Warning** | Warns when a variable in an inner block shadows a variable in an outer scope. |
| `this-forbidden` | **Warning** | In Lymar, `self` is the canonical reference; `this` is unsupported. |
| `reserved-identifier` | **Warning** | Flags variables, functions, or fields named after language keywords (`iter`, `any`, `var`, `val`, `fn`, `contract`, etc.). |
| `constant-condition` | **Warning** | Detects conditions that are compile-time constants (e.g. `if (true)`, `while (false)`). |
| `unhandled-fallible` | **Warning** | Flags discarded results from fallible functions (`Type?`) invoked without `?`, `? else`, or assignment. |
| `unused-import` | **Warning** | Identifies imported modules or symbols that are never referenced in the file. |
| `unused-var` | **Warning** | Warns on declared variables that are never read. Prefix with `_` if intentionally unused. |
| `dead-code` | **Warning** | Detects unreachable statements after a `return`, `break`, or `continue`. |
| `empty-block` | **Warning** | Flags empty control flow blocks in `if`, `while`, `for`, or `iter`. |
| `redundant-bool` | **Warning** | Flags redundant comparisons with boolean literals (e.g., `cond == true`). |
| `any-overuse` | **Warning** | Discourages unconstrained dynamic `any` type annotations where concrete types or traits should be used. |
| `naming-convention` | **Warning** | Enforces `snake_case` for functions/variables/methods and `PascalCase` for frames/traits/enums. |

### CLI Options

```bash
# Lint current workspace or target files
lymar lint src/ tests/

# Treat all warnings as fatal errors (ideal for CI/CD gates)
lymar lint --deny-warnings src/ tests/
lymar lint -Werror src/

# Emit structured JSON diagnostics
lymar lint --json src/

# Disable ANSI color escape codes
lymar lint --no-color src/
```

---

## 4. Benchmarking Harness (`lymar bench` / `lyra bench`)

The benchmarking harness measures function performance with statistical warmup, multiple iterations, outlier rejection, and timing reported in `ns/op` and throughput (`ops/sec`).

### Usage

```bash
# Discover and run benchmarks in benchmarks/ or matching *_bench.lm
lymar bench

# Run specific benchmark file or filter by name
lymar bench tests/crypto_bench.lm
lymar bench --filter "sha256"

# Customize warmup and measurement iterations
lymar bench --warmup 5 --iters 50 tests/compress_bench.lm
```

### Writing Benchmarks

```lymar
// benchmarks/hash_bench.lm
import std.crypto.hash as hash;

pub fn bench_sha256() {
    var data = "benchmark payload data";
    var digest = hash.hash_sha256(data);
}
```

---

## 5. Profilers & Runtime Observability (`lymar profile` / `lyra profile`)

The built-in deterministic execution profiler instruments Register VM invocations, recursion stacks, and standard library builtins. It measures function call counts, total (inclusive) time, exclusive (self) time, and highlights top CPU bottlenecks.

### Usage

```bash
# Profile script execution with formatted hotspot table
lymar profile src/main.lm
lyra profile src/main.lm

# Run via 'run' subcommand with profiling enabled
lymar run --profile src/main.lm

# Sort hotspots by self time (default), total time, or call count
lymar profile src/main.lm --sort=self
lymar profile src/main.lm --sort=total
lymar profile src/main.lm --sort=calls

# Display top N functions (default: 25)
lymar profile src/main.lm --top=10

# Export folded stack traces for Flamegraph generation
lymar profile src/main.lm --flamegraph=profile.folded
# Render SVG flamegraph using Brendan Gregg's flamegraph.pl:
# flamegraph.pl profile.folded > flamegraph.svg
# Or drag-and-drop profile.folded directly into https://speedscope.app

# Output structured JSON results for programmatic CI performance gates
lymar profile src/main.lm --json
```

### Sample Output

```text
========================================================================================
Lymar Execution Profile: benchmarks/hash_bench.lm
Total Runtime: 79.94 ms | Total Invocations: 2205 | Unique Functions: 13
========================================================================================
Function Name                              Calls      Total Time       Self Time    % Self
----------------------------------------------------------------------------------------
std.crypto.hash._open_lib                    200        28.11 ms        28.11 ms     35.2%
std.crypto.hash.hash                         200        79.49 ms        24.12 ms     30.2%
std.ffi.cstring_to_string                    200        19.53 ms        16.63 ms     20.8%
std.ffi.string_to_cstring                    400         7.34 ms         7.34 ms      9.2%
_builtin_string_from_bytes                   200         2.91 ms         2.91 ms      3.6%
std.ffi.cstring_free                         400       314.90 us       314.90 us      0.4%
main                                           1        79.86 ms       137.10 us      0.2%
----------------------------------------------------------------------------------------
Top Bottleneck: 'std.crypto.hash._open_lib' consumed 35.2% (28.11 ms) of execution time.
```

---

## 6. Code Contracts & Formal Verification

Lymar features native **Design-by-Contract** and **Refinement Types**:

```lymar
// Preconditions and postconditions
fn allocate(capacity: int): [int] {
    contract(capacity > 0, "Capacity must be strictly positive");
    contract(capacity <= 1048576, "Maximum allocation ceiling exceeded");
    var buf: [int] = [];
    contract(len(buf) <= capacity, "Buffer overflow");
    return buf;
}

// Refinement Types
type Port = int where value >= 1 and value <= 65535;
type NonEmptyStr = str where len(value) > 0;
```

### Verification Flags

* `--verify=hybrid` (Default): Proves what it can statically; enforces remaining constraints via fast assertions.
* `--verify=strict`: Demands static proof for all contracts and refinement types at compile time; fails compilation if unproven.

---

## 7. Recommended CI/CD Pipeline

A complete workflow ensuring zero regressions, strict style compliance, and up-to-date documentation:

```bash
# Step 1: Run unit and integration tests in parallel
lymar test -j 4 --fail-fast

# Step 2: Enforce zero lint warnings
lymar lint --deny-warnings src/ tests/

# Step 3: Run performance benchmarks to catch regressions
lymar bench tests/

# Step 4: Publish documentation site
lymar doc --html src/ -o docs/api/
```
