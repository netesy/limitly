# API Documentation: `checkbox.lm`

## Overview

std/ui/widgets/checkbox.lm
Widget — split from std/ui/widgets.lm.

## Symbols

- **Frame**: [`Checkbox`](#Checkbox)
- **Function**: [`checkbox`](#checkbox)

---

### `Checkbox` <a id="Checkbox"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Checkbox
```

#### Members

- `var pub checked_sig: state.BoolSignal` *(field)*
- `var pub box: float` *(field)*
- `var pub gap: float` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub box_border: color.Color` *(field)*
- `var pub box_fill: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub hovered: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn bind_check(sig: state.BoolSignal): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `checkbox` <a id="checkbox"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn checkbox(label_txt: str = ..., initial: bool = ...): Checkbox
```

---

