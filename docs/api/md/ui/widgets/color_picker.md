# API Documentation: `color_picker.lm`

## Overview

std/ui/widgets/color_picker.lm
Widget — HSV color picker. Closed: swatch + label. Open: popup panel
(overlay) with an SV square, hue bar, and hex readout; click/drag inside
updates `picked` live and fires the optional callback on release.

## Symbols

- **Function**: [`hsv_to_rgb`](#hsv_to_rgb)
- **Function**: [`rgb_to_hsv`](#rgb_to_hsv)
- **Function**: [`hex2`](#hex2)
- **Frame**: [`ColorPicker`](#ColorPicker)
- **Function**: [`color_picker`](#color_picker)

---

### `hsv_to_rgb` <a id="hsv_to_rgb"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hsv_to_rgb(h: float, s: float, v: float): color.Color
```

---

### `rgb_to_hsv` <a id="rgb_to_hsv"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn rgb_to_hsv(col: color.Color): tuple
```

---

### `hex2` <a id="hex2"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hex2(v: int): str
```

---

### `ColorPicker` <a id="ColorPicker"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ColorPicker
```

#### Members

- `var pub label: str` *(field)*
- `var pub picked: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub click: function?` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub hovered: int` *(field)*
- `var pub is_open: int` *(field)*
- `var pub h: float` *(field)*
- `var pub s: float` *(field)*
- `var pub v: float` *(field)*
- `var pub _drag: int` *(field)*
- `var pub _suppress_up: int` *(field)*
- `var pub _px: float` *(field)*
- `var pub _py: float` *(field)*
- `var pub _pw: float` *(field)*
- `var pub _sv_h: float` *(field)*
- `var pub _bar_y: float` *(field)*
- `var pub _bar_h: float` *(field)*
- `var pub _panel_h: float` *(field)*
- `var pub _custom_picked: int` *(field)*
- `var pub panel_surface: color.Color` *(field)*
- `var pub _shadow: shadow.Shadow?` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `fn set_open(v: int): nil` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `fn layout_panel(): nil` *(method)*
- `fn sv_rect(): tuple` *(method)*
- `fn apply_sv(fx: float, fy: float): nil` *(method)*
- `fn apply_hue(fx: float): nil` *(method)*
- `fn commit_color(): nil` *(method)*
- `fn fire_change(): nil` *(method)*
- `fn hex_text(): str` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `color_picker` <a id="color_picker"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_picker(lbl: str = ..., c: color.Color? = ..., on_change: function? = ...): ColorPicker
```

---

