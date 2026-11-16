# API Documentation: `spacer.lm`

## Overview

std/ui/widgets/spacer.lm
Widget — ported from legacy Fluent Spacer.
Empty flexible space: measure reports ~0 intrinsic size so Flow expands
it to consume leftover space; fixed width/height override when set.

## Symbols

- **Frame**: [`Spacer`](#Spacer)
- **Function**: [`spacer`](#spacer)

---

### `Spacer` <a id="Spacer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Spacer
```

#### Members

- `var pub flex: float` *(field)*
- `var pub fixed_w: float` *(field)*
- `var pub fixed_h: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `spacer` <a id="spacer"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn spacer(flex_val: float = ...): Spacer
```

---

