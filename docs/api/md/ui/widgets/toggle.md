# API Documentation: `toggle.lm`

## Overview

std/ui/widgets/toggle.lm
Widget — split from std/ui/widgets.lm.

## Symbols

- **Frame**: [`Toggle`](#Toggle)
- **Function**: [`toggle`](#toggle)

---

### `Toggle` <a id="Toggle"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Toggle
```

#### Members

- `var pub on_sig: state.BoolSignal` *(field)*
- `var pub track_w: float` *(field)*
- `var pub track_h: float` *(field)*
- `var pub gap: float` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub on_color: color.Color` *(field)*
- `var pub off_color: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub hovered: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn bind_toggle(sig: state.BoolSignal): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `toggle` <a id="toggle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn toggle(label_txt: str = ..., initial: bool = ...): Toggle
```

---

