# API Documentation: `badge.lm`

## Overview

std/ui/widgets/badge.lm
Widget — ported from legacy Fluent Badge.
Small rounded label chip. bg/fg are color fields; bg.a <= 0 falls back
to the accent color like the legacy emit path.

## Symbols

- **Frame**: [`Badge`](#Badge)
- **Function**: [`badge`](#badge)

---

### `Badge` <a id="Badge"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Badge
```

#### Members

- `var pub bg: color.Color` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `badge` <a id="badge"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn badge(txt: str): Badge
```

---

