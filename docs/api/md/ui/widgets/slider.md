# API Documentation: `slider.lm`

## Overview

std/ui/widgets/slider.lm
Widget — split from std/ui/widgets.lm.

## Symbols

- **Frame**: [`Slider`](#Slider)
- **Function**: [`slider`](#slider)

---

### `Slider` <a id="Slider"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Slider
```

#### Members

- `var pub value_sig: state.FloatSignal` *(field)*
- `var pub min_val: float` *(field)*
- `var pub max_val: float` *(field)*
- `var pub track_h: float` *(field)*
- `var pub gap: float` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub track_color: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub dragging: int` *(field)*
- `var pub hovered: int` *(field)*
- `var pub _tx: float` *(field)*
- `var pub _ty: float` *(field)*
- `var pub _tw: float` *(field)*
- `var pub _th: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn bind_value(sig: state.FloatSignal): nil` *(method)*
- `fn label_w(): float` *(method)*
- `fn clamp_val(v: float): float` *(method)*
- `fn layout_track(): nil` *(method)*
- `fn value_at_px(px: float): float` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `slider` <a id="slider"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn slider(min_v: float = ..., max_v: float = ..., initial: float = ..., label_txt: str = ...): Slider
```

---

