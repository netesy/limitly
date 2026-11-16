# API Documentation: `range_slider.lm`

## Overview

std/ui/widgets/range_slider.lm
Widget — ported from legacy Fluent RangeSlider.
Two-thumb range slider backed by two FloatSignals (low_sig/high_sig).
Drag whichever thumb is nearest the pointer; values clamp to
[min_val, max_val] and low <= high is enforced.

## Symbols

- **Frame**: [`RangeSlider`](#RangeSlider)
- **Function**: [`range_slider`](#range_slider)

---

### `RangeSlider` <a id="RangeSlider"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RangeSlider
```

#### Members

- `var pub low_sig: state.FloatSignal` *(field)*
- `var pub high_sig: state.FloatSignal` *(field)*
- `var pub min_val: float` *(field)*
- `var pub max_val: float` *(field)*
- `var pub track_h: float` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub track_color: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub dragging: int` *(field)*
- `var pub hovered: int` *(field)*
- `var pub _tx: float` *(field)*
- `var pub _ty: float` *(field)*
- `var pub _tw: float` *(field)*
- `var pub _th: float` *(field)*
- `var pub _lx: float` *(field)*
- `var pub _hx: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn bind_low(sig: state.FloatSignal): nil` *(method)*
- `pub fn bind_high(sig: state.FloatSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `fn clamp_val(v: float): float` *(method)*
- `fn frac_of(v: float): float` *(method)*
- `fn value_at_px(px: float): float` *(method)*
- `fn layout_track(): nil` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*
- `fn apply_drag(fx: float): nil` *(method)*

---

### `range_slider` <a id="range_slider"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn range_slider(low: float = ..., high: float = ..., min_v: float = ..., max_v: float = ...): RangeSlider
```

---

