# API Documentation: `cursor.lm`

## Overview

std/text/cursor.lm
Cursor submodule for std.text. Rich text editing, text layout, cursors, and text selection.

## Symbols

- **Frame**: [`Cursor`](#Cursor)
- **Frame**: [`Selection`](#Selection)

---

### `Cursor` <a id="Cursor"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Cursor
```

#### Members

- `var pub line: int` *(field)*
- `var pub col: int` *(field)*
- `var pub pref_col: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn set(l: int, c: int): nil` *(method)*

---

### `Selection` <a id="Selection"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Selection
```

#### Members

- `var pub anchor_line: int` *(field)*
- `var pub anchor_col: int` *(field)*
- `var pub active_line: int` *(field)*
- `var pub active_col: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn set(line: int, col: int): nil` *(method)*
- `pub fn extend_to(line: int, col: int): nil` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn get_range(): tuple` *(method)*

---

