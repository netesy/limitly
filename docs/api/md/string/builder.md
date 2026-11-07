# API Documentation: `builder.lm`

## Overview

std/string/builder.lm
Builder submodule for std.string. String manipulation, UTF-8 text processing, and string builders.

## Symbols

- **Frame**: [`Builder`](#Builder)
- **Function**: [`builder`](#builder)

---

### `Builder` <a id="Builder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Builder
```

Efficient string concatenation accumulator.

#### Members

- `var pub parts: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn append(s: str): nil` *(method)*
- `pub fn append_str(s: str): nil` *(method)*
- `pub fn append_line(s: str): nil` *(method)*
- `pub fn append_char(cp: int): nil` *(method)*
- `pub fn clear(): nil` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn to_string(): str` *(method)*

---

### `builder` <a id="builder"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn builder(): Builder
```

Creates a new empty `Builder` instance.

#### Returns

Initialized `Builder`.

---

