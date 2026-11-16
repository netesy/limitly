# API Documentation: `table.lm`

## Overview

std/ui/widgets/table.lm
Widget — ported from legacy Fluent Table.
Header row + grid of child Components. rows is a list of rows, each a
list of [comp.Component] cells (nil cells render empty). Column widths are
equal shares of the arranged width, matching the legacy emit.

## Symbols

- **Frame**: [`Table`](#Table)
- **Function**: [`table`](#table)
- **Function**: [`table_text`](#table_text)

---

### `Table` <a id="Table"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Table
```

#### Members

- `var pub headers: list` *(field)*
- `var pub rows: list` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub header_bg: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub row_h: float` *(field)*
- `var pub header_h: float` *(field)*
- `var pub _cur: float` *(field)*
- `var pub _cw: float` *(field)*
- `var pub _ch: float` *(field)*
- `pub init(hdrs: list, row_data: list)` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn add_row(cells: list): nil` *(method)*
- `fn col_count(): int` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `table` <a id="table"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn table(hdrs: list, row_data: list): Table
```

---

### `table_text` <a id="table_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn table_text(hdrs: list, row_data: list): Table
```

String-grid convenience: wraps each cell in a Label. Use table() when
cells need to be interactive Components.

---

