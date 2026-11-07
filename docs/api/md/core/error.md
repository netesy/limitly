# API Documentation: `error.lm`

## Overview

Standard Library Core Error Frame

## Symbols

- **Frame**: [`Error`](#Error)

---

### `Error` <a id="Error"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Error
```

Canonical structured error representation in Lymar.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Construct errors using `err(Error(code="...", message="..."))` and handle them with `? else { ... }` or `match`.

#### Example: Idiomatic Usage

```lymar
fn fail_example(): int? {
    return err(Error("E001", "Operation failed"));
}
```

#### Members

- `var pub code: str` *(field)*
- `var pub message: str` *(field)*
- `pub init(code: str, message: str)` *(constructor)*
- `pub fn to_string(): str` *(method)*

---

