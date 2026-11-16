# API Documentation: `alert.lm`

## Overview

std/ui/widgets/alert.lm
Widget — ported from legacy Fluent Alert (+ toast helper).
Rounded message bar; kind selects the background color
(info/success/warning/danger).

## Symbols

- **Frame**: [`Alert`](#Alert)
- **Function**: [`alert`](#alert)
- **Function**: [`toast`](#toast)

---

### `Alert` <a id="Alert"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Alert
```

#### Members

- `var pub bg: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub alert_kind: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `alert` <a id="alert"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert(msg: str, type_str: str = ...): Alert
```

---

### `toast` <a id="toast"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn toast(msg: str, type_str: str = ...): Alert
```

---

