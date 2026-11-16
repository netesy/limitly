# API Documentation: `stat.lm`

## Overview

std/ui/widgets/stat.lm
Widget — ported from legacy Fluent Stat.
Metric card: small title, large value, optional accent description.

## Symbols

- **Frame**: [`Stat`](#Stat)
- **Function**: [`stat`](#stat)

---

### `Stat` <a id="Stat"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Stat
```

#### Members

- `var pub title: str` *(field)*
- `var pub value_text: str` *(field)*
- `var pub desc: str` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub text2: color.Color` *(field)*
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

### `stat` <a id="stat"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stat(t: str, v: str, d: str = ...): Stat
```

---

