# API Documentation: `card.lm`

## Overview

std/ui/widgets/card.lm
Widget — ported from legacy Fluent Card.
Titled surface card wrapping a single child Component. The child is
arranged inside the card body (below the header) and painted after the
chrome, so it receives events through the normal bounds walk.

## Symbols

- **Frame**: [`Card`](#Card)
- **Function**: [`card`](#card)

---

### `Card` <a id="Card"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Card
```

#### Members

- `var pub title: str` *(field)*
- `var pub child: comp.Component?` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub pad: float` *(field)*
- `var pub elevation: int` *(field)*
- `var pub _pal: uitheme.Palette?` *(field)*
- `var pub _shadow: shadow.Shadow?` *(field)*
- `var pub header_h: float` *(field)*
- `var pub _cw: float` *(field)*
- `var pub _ch: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_elevation(e: int): nil` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn set_child(c: comp.Component): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `card` <a id="card"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn card(t: str, content: any = ...): Card
```

---

