# Lymar Error Handling & Diagnostic Architecture

Lymar approaches error handling at two distinct, tightly coordinated levels:
1. **Language-Level Error Unions (`Type?`)**: A zero-overhead, type-safe system for handling fallible operations and optional values without exceptions or null pointers.
2. **Compiler-Level Diagnostics (`ErrorCatalog`)**: A rich diagnostic catalog providing structured error codes (E100–E400), contextual suggestions, and formatting across compiler phases.

---

## Part 1: Language-Level Error Handling (`Type?`)

### 1.1 The Unified Fallible System

Lymar does not use exceptions, runtime panics, or generic `Result<T, E>` / `Option<T>` wrappers. Instead, the type system features native **ErrorUnions** denoted by the `Type?` syntax:

```lymar
// Optional / fallible return where absence is an error condition
fn find_user(id: int): str? {
    if (id == 1) {
        return ok("Alice");
    }
    return err(); // Absent / not found condition
}

// Function with specific error tag
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);
    }
    return ok(a / b);
}
```

### 1.2 Error Constructors

The parser accepts exactly three shapes:

- `ok(value)`: Wraps a successful result.
- `err()`: Generic error or absent value. Carries no payload.
- `err(ErrorType)`: Typed error for a specific domain. `ErrorType` must be a **bare identifier**; it is checked statically against a `T?ErrorType` return annotation and carries no runtime payload.
- `err(ErrorType(arg))`: Same, plus a runtime payload. The arguments are **positional** — the first one is carried as the error value.

```lymar
fn load_config(path: str): str? {
    if (len(path) == 0) {
        return err(InvalidPath("path must not be empty")); // positional payload
    }
    return ok(read_all(path)?);
}
```

> [!WARNING]
> These three spellings are **rejected** and must not be used:
> - `err("ErrorType", "Message")` — a string literal cannot name an error type. The parser reports `Expected error type name.`
> - `err(ErrorType { field = value })` — error constructors take parentheses, not braces.
> - `err(ErrorType(field = value))` — `name = expr` is a named argument only in an ordinary *call*. Inside `err(...)` it parses as an assignment expression, which is not an error payload.

The `ErrorType` name is a static-only annotation: it lets a `T?ErrorType` return type be validated against the `err(...)` sites a function actually returns. Nothing about the name reaches runtime, so `err(DivisionByZero)` and `err()` produce equivalent values.

### 1.3 Propagation with the `?` Operator
Suffixing any fallible expression with `?` automatically propagates errors up the call stack:

```lymar
fn process_user(id: int): str? {
    var user: str = find_user(id)?; // Returns err() immediately if find_user fails
    return ok("Processed: " + user);
}
```

### 1.4 Inline Handling with `? else`
Provide immediate fallback defaults or recovery blocks without deep nesting:

```lymar
var count: int = divide(10, 0)? else {
    print("Division failed; defaulting to 0");
    return 0;
};
```

### 1.5 Pattern Matching on Fallible Results
Match statements branch cleanly on success and error variants:

```lymar
match (divide(10, 2)) {
    val result => {
        print("Success: {result}");
    },
    err => {
        print("Encountered division failure");
    }
}
```

---

## Part 2: Compiler Diagnostics & Error Catalog

The compiler diagnostic engine (`src/error/error_catalog.hh`) manages error reporting, pattern matching, and contextual suggestions across interpretation phases.

### 2.1 Diagnostic Stages & Code Ranges

| Stage | Code Range | Description | Example |
|---|---|---|---|
| **Lexical** | `E100` – `E199` | Tokenization and scanner errors | Unterminated string, invalid escape sequence |
| **Parsing** | `E200` – `E299` | Grammar, CST, and AST construction | Unexpected token, missing semicolon on field |
| **Semantic** | `E300` – `E399` | Type checking, verification, linear rules | Type mismatch, use-after-move, missing trait method |
| **Runtime** | `E400` – `E499` | Register VM and execution traps | Division by zero, unhandled capability violation |

### 2.2 Diagnostic Architecture in C++ Core

```cpp
#include "error/error_catalog.hh"

// Look up diagnostic definition by standard code
const auto* def = ErrorCatalog::getInstance().lookupByCode("E201");
if (def) {
    // Generate context-aware hint and suggestion
    std::string hint = catalog.generateHint(*def, context);
    std::string suggestion = catalog.generateSuggestion(*def, context);
}
```

### 2.3 Diagnostic Formatting
Diagnostics follow modern compiler standards (file path, line, column, snippet highlight, explanation, and fix suggestions):

```text
error[E302]: Type mismatch in variable assignment
  --> src/main.lm:12:5
   |
12 |     var x: int = "hello";
   |     ^^^^^^^^^^^^^^^^^^^^^ expected `int`, found `str`
   |
   = help: cast explicitly using `as int` or adjust variable type annotation
```
