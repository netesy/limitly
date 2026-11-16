# API Documentation: `timeline.lm`

## Overview

std/ui/widgets/timeline.lm
Widget — ported from legacy Fluent Timeline.
Vertical list of child components, each prefixed with an accent dot.
Children are [comp.Component]; measure/arrange stack them top-down.

## Symbols

- **Frame**: [`Timeline`](#Timeline)
- **Function**: [`timeline`](#timeline)

---

### `Timeline` <a id="Timeline"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Timeline
```

#### Members

- `var pub children: list` *(field)*
- `var pub spacing: float` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub _cur: float` *(field)*
- `var pub _cw: float` *(field)*
- `var pub _ch: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(c: comp.Component): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `timeline` <a id="timeline"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timeline(): Timeline
```

---

