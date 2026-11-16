# API Documentation: `diff.lm`

## Overview

std/ui/widgets/diff.lm
Widget — line-based diff view. Computes an LCS alignment between
old_text and new_text, then renders context/removed/added rows with a
gutter marker. Rows are clipped to the widget rect; wrap in a
scroll_view for long diffs.

## Symbols

- **Frame**: [`DiffLine`](#DiffLine)
- **Frame**: [`Diff`](#Diff)
- **Function**: [`diff`](#diff)

---

### `DiffLine` <a id="DiffLine"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DiffLine
```

#### Members

- `var pub kind: DiffKind` *(field)*
- `var pub text: str` *(field)*
- `pub init(k: DiffKind, t: str)` *(constructor)*

---

### `Diff` <a id="Diff"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Diff
```

#### Members

- `var pub old_text: str` *(field)*
- `var pub new_text: str` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub removed_color: color.Color` *(field)*
- `var pub added_color: color.Color` *(field)*
- `var pub context_color: color.Color` *(field)*
- `var pub removed_bg: color.Color` *(field)*
- `var pub added_bg: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub _lines: list` *(field)*
- `var pub _built_old: str` *(field)*
- `var pub _built_new: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_texts(old_t: str, new_t: str): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `fn row_h(): float` *(method)*
- `fn rebuild(): nil` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `diff` <a id="diff"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn diff(old_t: str, new_t: str): Diff
```

---

