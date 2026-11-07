# API Documentation: `controller.lm`

## Overview

std/text/controller.lm
Controller submodule for std.text. Rich text editing, text layout, cursors, and text selection.

## Symbols

- **Frame**: [`EditorController`](#EditorController)

---

### `EditorController` <a id="EditorController"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame EditorController
```

#### Members

- `var pub document: doc.Document` *(field)*
- `var pub cursor: cursor.Cursor` *(field)*
- `var pub selection: cursor.Selection` *(field)*
- `var pub get_clipboard: function?` *(field)*
- `var pub set_clipboard: function?` *(field)*
- `var pub history: list` *(field)*
- `var pub history_idx: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn save_history(): nil` *(method)*
- `pub fn undo(): nil` *(method)*
- `pub fn redo(): nil` *(method)*
- `pub fn insert_text(s: str): nil` *(method)*
- `pub fn insert_newline(): nil` *(method)*
- `pub fn backspace(): nil` *(method)*
- `pub fn move_left(): nil` *(method)*
- `pub fn move_right(): nil` *(method)*
- `pub fn move_up(): nil` *(method)*
- `pub fn move_down(): nil` *(method)*
- `pub fn copy(): nil` *(method)*
- `pub fn cut(): nil` *(method)*
- `pub fn paste(): nil` *(method)*
- `pub fn get_text(): str` *(method)*
- `pub fn get_line_count(): int` *(method)*
- `pub fn get_line(idx: int): str` *(method)*
- `pub fn get_cursor_line(): int` *(method)*
- `pub fn get_cursor_col(): int` *(method)*
- `pub fn get_lines(): list` *(method)*
- `pub fn set_cursor(line: int, col: int): nil` *(method)*
- `pub fn set_selection(line: int, col: int): nil` *(method)*
- `pub fn has_selection(): int` *(method)*
- `pub fn is_selected(): bool` *(method)*
- `pub fn get_selection_range(): list` *(method)*
- `pub fn set_text(new_text: str): nil` *(method)*

---

