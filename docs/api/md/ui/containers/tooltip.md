# API Documentation: `tooltip.lm`

## Overview

std/ui/containers/tooltip.lm
Container — wraps a child and shows a label bubble while the
pointer hovers the child's bounds. Hover is tracked via MouseMove in
on_event; entering/leaving requests a repaint.

## Symbols

- **Frame**: [`Tooltip`](#Tooltip)
- **Function**: [`tooltip`](#tooltip)

---

### `Tooltip` <a id="Tooltip"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Tooltip
```

#### Members

- `var pub child: comp.Component?` *(field)*
- `var pub label_text: str` *(field)*
- `var pub hovered: int` *(field)*
- `var pub bg: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub pad_x: float` *(field)*
- `var pub pad_y: float` *(field)*
- `var pub _pal: uitheme.Palette?` *(field)*
- `var pub _shadow: shadow.Shadow?` *(field)*
- `var pub _bw: float` *(field)*
- `var pub _bh: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn set_child(c: comp.Component): nil` *(method)*
- `pub fn set_label(s: str): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `tooltip` <a id="tooltip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tooltip(c: any = ..., lbl: str = ...): Tooltip
```

---

