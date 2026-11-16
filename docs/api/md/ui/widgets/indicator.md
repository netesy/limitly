# API Documentation: `indicator.lm`

## Overview

std/ui/widgets/indicator.lm
Widget — ported from legacy Fluent Indicator.
Status dot + optional label. status: "online" | "busy" | anything else
(offline/unknown → gray).

## Symbols

- **Frame**: [`Indicator`](#Indicator)
- **Function**: [`indicator`](#indicator)

---

### `Indicator` <a id="Indicator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Indicator
```

#### Members

- `var pub dot: color.Color` *(field)*
- `var pub text_color: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub status_kind: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `indicator` <a id="indicator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn indicator(status: str = ..., lbl: str = ...): Indicator
```

---

