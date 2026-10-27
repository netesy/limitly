# Documentation Generation, Static Linting & Code Contracts Guide

This comprehensive guide covers:
1. Writing professional API documentation that demonstrates **idiomatic usage ("the right way to use code")**, **executable examples**, **admonitions (warnings, tips, notes)**, and **parameter specifications** using `lymar doc`.
2. Utilizing the robust **Linter & Static Analysis Engine** (`lymar lint` / `lyra lint`) to catch anti-patterns, unsupported features, and potential bugs.
3. Enforcing invariants with **Code Contracts** and **Refinement Types** verified statically and at runtime.

---

## 1. Writing Professional Documentation

Lymar's documentation generator (`lymar doc` and `lyra doc`) extracts doc comments, module overviews, type signatures, contracts, and examples directly from your `.lm` source code. It emits publication-ready Markdown (for GitHub wikis/READMEs) and standalone, responsive HTML with real-time symbol search.

### 1.1 Doc Comments & Tag Syntax

Doc comments use triple-slashes (`///`) or double-slashes (`//`) placed directly above declarations.

#### Supported Tags & Admonitions

| Tag / Syntax | Purpose | Rendered Appearance |
| :--- | :--- | :--- |
| `@tip <text>` or `> [!TIP]` | **The right way to use the code** (idiomatic patterns, performance best practices) | Glowing emerald callout box with 💡 icon |
| `@warning <text>` or `> [!WARNING]` | Hazards, security boundaries, limits, or crash risks | Vibrant amber alert box with ⚠️ icon |
| `@note <text>` or `> [!NOTE]` / `@info` | Invariants, thread-safety, allocation behavior | Cyan/sky info box with ℹ️ icon |
| `@caution <text>` or `> [!CAUTION]` | High-risk actions or destructive side-effects | Red/orange caution box with 🛑 icon |
| `@deprecated <text>` | Deprecation notice and migration advice | Crimson alert box with 🚫 icon |
| `@example` or ```` ```lymar ```` | Code example showing idiomatic usage | Distinct syntax-highlighted editor card |
| `@param <name> <description>` | Parameter details and valid value ranges | Formatted parameter table |
| `@return <description>` | Return value semantics, errors returned | Return value summary card |
| `@pre <condition>` or `@requires` | Formal precondition contracts | Monospace contract requirement |

### 1.2 Comprehensive Example: Idiomatic Function & Frame

```lymar
// std/compress/zlib.lm
// Dynamic buffer zlib compression and decompression engine.

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
    if (len(data) == 0) {
        return ok("");
    }
    // Compression implementation...
    return ok("789c...");
}

/// Thread-safe streaming decompressor with memory ceiling enforcement.
///
/// > [!TIP]
/// > Prefer reusing a single Decompressor instance across batch tasks
/// > to minimize repeated allocator initialization.
///
/// > [!WARNING]
/// > Attempting to decompress malformed inputs will return err(InvalidStream).
frame Decompressor {
    /// Maximum allowed decompressed byte size (default: 10MB).
    pub max_bytes: int;

    /// Initializes a decompressor with a safe buffer memory ceiling.
    pub init(limit: int = 10485760) {
        self.max_bytes = limit;
    }

    /// Decompresses a hex-encoded deflate payload into plain text.
    ///
    /// @param hex_data The hex-encoded deflate string.
    /// @return Returns the uncompressed string payload, or err().
    pub fn decompress(hex_data: str): str? {
        return ok("uncompressed");
    }
}
```

---

## 2. Generating Documentation with CLI

### 2.1 Generating GitHub-Flavored Markdown

```bash
# Print Markdown documentation to stdout
lymar doc src/zlib.lm

# Output directly to a file
lymar doc src/zlib.lm -o docs/zlib.md

# Batch generate Markdown documentation for an entire package directory
lymar doc src/ -o docs/api/
```

### 2.2 Generating Standalone Interactive HTML (`--html`)

The HTML documentation generator creates a dark-mode website featuring:
* **Interactive Symbol Filter**: Client-side search box that filters symbols in real time.
* **Admonition Cards**: Color-coded callouts for `@tip`, `@warning`, `@note`, `@deprecated`.
* **Example Editor Cards**: Highlighting idiomatic usage snippets.
* **Responsive Layout**: Sticky sidebar navigation for large codebases.

```bash
# Generate single standalone HTML document
lymar doc --html src/zlib.lm -o docs/api/zlib.html

# Generate HTML documentation tree for all files in a package
lymar doc --html src/ -o site/
```

### 2.3 CLI Flags Reference

| Flag | Description | Example |
| :--- | :--- | :--- |
| `--markdown` (default) | Emits GitHub-Flavored Markdown with alert blockquotes | `lymar doc --markdown src/` |
| `--html` | Emits responsive dark-theme HTML with live search | `lymar doc --html src/ -o site/` |
| `-o <path>` | Specifies output file or output directory | `lymar doc src/main.lm -o api.md` |
| `--stdout` | Force prints output directly to stdout | `lymar doc --stdout src/main.lm` |

---

## 3. Robust Static Analysis & Linter (`lymar lint`)

The Lymar linter performs deep semantic inspection to enforce language design rules (`AGENTS.md`), detect anti-patterns, and catch bugs before code runs.

### 3.1 Active Linter Rules

| Rule | Severity | Description |
| :--- | :--- | :--- |
| `list-concat` | **Warning** | Flagged when using `list1 + list2`. Per `AGENTS.md`, list concatenation with `+` is unsupported; use `append(list, item)` or `append(list, other_list)`. |
| `self-comparison` | **Warning** | Flagged when comparing a variable to itself (e.g. `x == x`, `a != a`), which is redundant or constant. |
| `variable-shadowing` | **Warning** | Flagged when an inner variable shadows an outer variable in an enclosing scope. |
| `this-forbidden` | **Warning** | Flagged when using `this` instead of `self`. In Lymar, `self` is the canonical instance reference. |
| `reserved-identifier` | **Warning** | Flagged when using reserved language keywords (`iter`, `any`, `var`, `val`, `fn`, `frame`, `contract`, etc.) as variable or function names. |
| `constant-condition` | **Warning** | Flagged when conditions are compile-time constants (e.g. `if (true)`, `while (false)`). |
| `unhandled-fallible` | **Warning** | Flagged when calling a fallible function (`Type?`) as a statement without propagating (`?`), handling (`? else`), or binding. |
| `unused-import` | **Warning** | Flagged when an imported module or symbol is never referenced anywhere in the file. |
| `unused-var` | **Warning** | Flagged when a local variable is declared but never read. Prefix with `_` (e.g. `_temp`) if intentional. |
| `dead-code` | **Warning** | Flagged when statements appear after a `return`, `break`, or `continue` statement. |
| `empty-block` | **Warning** | Flagged when `if`, `while`, `for`, or `iter` branches contain zero statements. |
| `redundant-bool` | **Warning** | Flagged when comparing expressions to boolean literals (e.g. `cond == true` or `flag != false`). |
| `any-overuse` | **Warning** | Flagged when explicitly annotating variables or parameters with dynamic `any` instead of concrete types or traits. |
| `naming-convention` | **Warning** | Enforces `snake_case` for functions/variables/methods and `PascalCase` for frames/traits/enums. |

### 3.2 Running the Linter

```bash
# Lint current workspace / target files
lymar lint src/ tests/

# Treat all warnings as fatal errors (ideal for CI/CD gates)
lymar lint --deny-warnings src/ tests/
lymar lint -Werror src/

# Emit machine-readable JSON diagnostics for IDE and CI integrations
lymar lint --json src/
```

Example JSON output:
```json
{"file":"src/main.lm","line":12,"rule":"list-concat","severity":"warning","message":"List concatenation with '+' is unsupported in Lymar; use 'append(list, item)' instead (AGENTS.md)"}
```

---

## 4. Code Contracts & Formal Verification

Lymar includes built-in support for **Design-by-Contract** and **Refinement Types**, allowing developers to state assumptions, invariants, and pre/post-conditions.

### 4.1 Contract Statements (`contract`)

```lymar
fn allocate_buffer(capacity: int): [int] {
    // Precondition contract:
    contract(capacity > 0, "Capacity must be strictly positive");
    contract(capacity <= 1048576, "Exceeded maximum allocation limit of 1MB");

    var buf: [int] = [];
    // Allocation logic...

    // Postcondition / invariant:
    contract(len(buf) <= capacity, "Buffer overflow during allocation");
    return buf;
}
```

### 4.2 Refinement Types (`where`)

Refinement types attach predicate constraints directly to types:

```lymar
// Refined integers
type PositiveInt = int where value > 0;
type PortNumber = int where value >= 1 and value <= 65535;

// Refined strings
type NonEmptyStr = str where len(value) > 0;

fn bind_server(host: NonEmptyStr, port: PortNumber) {
    print("Listening on {host}:{port}");
}
```

### 4.3 Verification Modes

* **Hybrid Mode (`--verify=hybrid`, Default)**: Proves what it can at compile-time and inserts lightweight runtime assertions for dynamic inputs.
* **Strict Mode (`--verify=strict`)**: Demands full compile-time static proof of all contracts and refinement predicates; fails compilation if any constraint cannot be proved.

```bash
lymar run --verify=hybrid src/main.lm
lyra build --verify=strict
```

---

## 5. Automated CI/CD Workflow

Ensure high software quality in your CI pipeline with the following standard workflow:

```bash
# 1. Run tests in parallel with fast-fail
lymar test -j 4 --fail-fast

# 2. Enforce zero lint warnings
lymar lint --deny-warnings src/ tests/

# 3. Generate publication-ready HTML API documentation
lymar doc --html src/ -o docs/api/
```
