# API Documentation: `grid.lm`

## Overview

std/ui/containers/grid.lm
Container — fixed-column grid. Children flow left-to-right,
top-to-bottom; each row's height is the tallest cell in that row.
Port of the legacy index.lm `grid()` helper, as a real Component so
cells participate in measure/arrange/paint/event dispatch.

## Symbols

- **Frame**: [`Grid`](#Grid)
- **Function**: [`grid`](#grid)

---

### `Grid` <a id="Grid"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Grid
```

#### Members

- `var pub children: list` *(field)*
- `var pub cols: int` *(field)*
- `var pub spacing: float` *(field)*
- `var pub _cw: float` *(field)*
- `var pub _ch: float` *(field)*
- `var pub _cx: float` *(field)*
- `var pub _cy: float` *(field)*
- `var pub _rw: float` *(field)*
- `var pub _rh: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(c: comp.Component): nil` *(method)*
- `pub fn add_all(list: list): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `fn row_count(): int` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `grid` <a id="grid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid(columns: int = ..., sp: float = ...): Grid
```

---

