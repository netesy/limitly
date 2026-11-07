# API Documentation: `document.lm`

## Overview

std/text/document.lm
Document submodule for std.text. Rich text editing, text layout, cursors, and text selection.

## Symbols

- **Frame**: [`Document`](#Document)

---

### `Document` <a id="Document"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Document
```

#### Members

- `var pub lines: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_text(): str` *(method)*
- `pub fn insert_string(line: int, col: int, s: str): tuple` *(method)*
- `pub fn delete_range(start_line: int, start_col: int, end_line: int, end_col: int): nil` *(method)*
- `pub fn insert_newline(line: int, col: int): tuple` *(method)*

---

