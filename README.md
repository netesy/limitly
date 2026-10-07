# Lymar Programming Language

Lymar is a modern programming language designed with static typing, structured concurrency, and memory safety features. It combines the performance of systems programming with the safety and expressiveness of modern language design.

## Get Started

To learn how to use the Lymar language, check out our comprehensive guides:

- **[Quickstart & Beginner Tutorial](./docs/learn.md)**
- **[Full Language Guide](./docs/guide.md)**
- **[Formal Language Specification](./docs/language.md)**
- **[Compiler & Architecture](./docs/architecture.md)**

## Features

- **Static Typing & Inference:** A strong, static type system with local type inference, fixed-width scalars (`i8`..`i128`, `u8`..`u128`, `f32`/`f64`), fixed-scale decimals (`d2`, `d4`, `d6`), and type casts (`as`).
- **Structured Concurrency:** Lexically-scoped `parallel` (data parallelism) and `concurrent` (cooperative task/worker) blocks communicating through typed `channel` primitives.
- **Native Error Handling (`Type?`):** Zero-overhead compiler-level error unions using `ok(val)` and `err()` / `err(Type)` constructors, the `?` propagator, and inline `? else { ... }` fallbacks without generic overhead.
- **Object-Oriented Programming (Frames & Traits):** Class-like `frame` structures with traits, composition, explicit visibility (`pub`, `prot`, private by default), and lifecycle hooks (`pub init` / `pub deinit`) using canonical `self`.
- **First-Class Functions & Closures:** Higher-order functions, function types (`fn(T): R`), and lexical closures.
- **Pattern Matching:** Expressive `match` construct supporting value literals, enum variants, structural bindings, fallible patterns (`val success => ...`, `err error => ...`), and wildcards (`_`).
- **Modules & Import Filtering:** Hierarchical module resolution with aliasing (`as`), symbol inclusion (`show`), and exclusion (`hide`).
- **Dual Execution Backends:** High-performance bytecode Register VM for instant execution and debugging (`run`), plus native AOT / WASM compilation via Fyra (`build`).

## Building and Running

### Prerequisites
- C++20 compatible compiler (e.g., GCC 11+, Clang 13+, or MSVC)
- GNU Make (or CMake 3.20+)
- Windows: MSYS2 MinGW64 environment (`g++`, `make`)

### Build Instructions

For installation from any checkout location, use Bash (MSYS2 MinGW64 on Windows):

```bash
bash scripts/install.sh --prefix "$HOME/.local" --jobs 4
# Linux x86-64: also compile and install native fonts and collections:
bash scripts/install.sh --prefix "$HOME/.local" --precompile-stdlib
# Add the selected prefix's bin directory to PATH, then:
lymar run path/to/script.lm
```

Install GCC/G++, GNU Make, Git, Python 3, and the libffi, OpenSSL, and zlib
development packages first. Debian/Ubuntu package names are `build-essential`,
`git`, `python3`, `libffi-dev`, `libssl-dev`, and `zlib1g-dev`. On Windows, use
the matching MSYS2 MinGW64 packages. On macOS, install GNU GCC/Make and the
libraries with your package manager; set `CPATH` and `LIBRARY_PATH` if their
headers and libraries are outside the compiler's default search paths.
Set `CXX`, `CC`, and `AR` to select a toolchain (for example, `CXX=g++-15`
with Homebrew GCC on macOS).

The installer accepts `--prefix` and `--jobs` (or `LYMAR_PREFIX` and
`LYMAR_JOBS`), preserves the current working directory in its launcher, and
sets `LYMAR_HOME` so installed standard modules and native libraries can be
found outside the checkout. It initializes pinned submodules without changing
the selected branch. Rerun it after source changes to update the installation.

Validate the font benchmark on Windows/Linux with:

```bash
python3 tests/precompiled/run_benchmark.py --font /path/to/font.ttf --runs 5
# Check only the interpreted implementation against the C oracle:
python3 tests/precompiled/run_benchmark.py --oracle-only --runs 1
```

All modes use the same font, 50 iterations, and em-size floating-point widths.
The runner checks results before comparing measured end-to-end times, restores
existing precompiled artifacts even on failure, and requires actual native
dispatch in mode B. It fails instead of timing an invalid or skipped workload.

On Linux x86-64, shared modules compile their LIR through the host C++ compiler
(`c++`, or `LYMAR_NATIVE_CXX`). This compiles module control flow to native code
while using a versioned ABI with the VM's tagged values, object layouts, runtime
helpers, globals, resources, and ownership regions. Frames and collections keep
their identity across calls, including mutations and returned object graphs.
Other targets continue to use Fyra's target-specific lowering.

Full `std.font` precompilation is covered by strict native tests for loading,
metrics, kerning, normal/subpixel/SDF rendering, and in-memory loading. The
benchmark requires native loading and all 50 native `text_width` calls, then
checks their result against STB. Run `python3 tests/precompiled/test_benchmark.py`
for the object bridge and font regressions. Shared module validation does not
establish standalone AOT executable readiness.

`--precompile-stdlib` installs `libcollections.so` and `libfont.so` with their
metadata. Normal facade imports, explicit `.index` imports, and direct child
module imports discover the libraries automatically. The collection facade's
canonical exports and constructors are included, and dependency hashes reject
stale binaries after implementation changes. Installed metadata binds to the
adjacent binary, allowing relocation of the installation.

Run `python3 tests/precompiled/test_collections_native.py` for collection/font
interop tests, including aliases, iterators, and priority-queue callbacks into
the VM. Font code already uses native runtime helpers for built-in lists;
precompiling the `std.collections` wrappers speeds calls to those wrappers.

```bash
# Build release compiler (bin/lymar or bin/lymar.exe)
make

# Build debug compiler with symbols
make MODE=debug

# Clean build artifacts
make clean
```

### Running Lymar Programs

The `lymar` binary provides clear subcommands:

```bash
# Execute a Lymar source file using the Register VM
./bin/lymar run path/to/script.lm

# Run with verbose debug output
./bin/lymar run -debug path/to/script.lm

# Run with strict contract/refinement verification
./bin/lymar run --verify=strict path/to/script.lm

# Compile to native binary via Fyra AOT backend
./bin/lymar build -o output_app path/to/script.lm

# Tooling and Inspection
./bin/lymar -tokens path/to/script.lm   # Print scanned tokens
./bin/lymar -cst path/to/script.lm      # Print Concrete Syntax Tree
./bin/lymar -ast path/to/script.lm      # Print Abstract Syntax Tree
./bin/lymar -lir path/to/script.lm      # Print Low-level Intermediate Representation
./bin/lymar -format path/to/script.lm   # Format a source file
./bin/lymar -lsp                       # Start Language Server Protocol daemon
```

## Testing

The test suite runs each test individually against the Register VM with timeouts to prevent hangs:

```bash
# Run all automated tests for vm via Python test runner
python tests/run_tests.py

# Run all automated tests for aot via Python test runner
python tests/build_tests.py
```
