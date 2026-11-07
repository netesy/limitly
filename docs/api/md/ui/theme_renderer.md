# API Documentation: `theme_renderer.lm`

## Overview

std/ui/theme_renderer - Theme-aware rendering helpers

## Symbols

- **Function**: [`apply_theme_color`](#apply_theme_color)
- **Function**: [`draw_focus_ring`](#draw_focus_ring)
- **Function**: [`draw_rounded_rect`](#draw_rounded_rect)
- **Function**: [`get_button_bg_color`](#get_button_bg_color)
- **Function**: [`get_input_border_color`](#get_input_border_color)

---

### `apply_theme_color` <a id="apply_theme_color"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn apply_theme_color(p: paint.Paint, color_token: ui_types.Color): paint.Paint
```

Apply theme color to paint based on context

---

### `draw_focus_ring` <a id="draw_focus_ring"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_focus_ring(cvs: canvas.Canvas, x: float, y: float, w: float, h: float, thickness: float = ...): nil
```

Draw focus ring around a widget

---

### `draw_rounded_rect` <a id="draw_rounded_rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_rounded_rect(cvs: canvas.Canvas, r: rect.Rect, radius: float, bg_color: ui_types.Color): nil
```

Draw corner radius on a rect using theme

---

### `get_button_bg_color` <a id="get_button_bg_color"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_button_bg_color(w: ui_types.Widget, theme: Theme): ui_types.Color
```

Get button background color based on state

---

### `get_input_border_color` <a id="get_input_border_color"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_input_border_color(w: ui_types.Widget, has_focus: bool, theme: Theme): ui_types.Color
```

Get input border color based on state and focus

---

