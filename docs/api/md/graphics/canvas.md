# API Documentation: `canvas.lm`

## Overview

std/graphics/canvas.lm
Canvas submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`Canvas`](#Canvas)

---

### `Canvas` <a id="Canvas"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Canvas
```

#### Members

- `var pub width: float` *(field)*
- `var pub height: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn draw_shadow(r: rect.Rect, s: shadow.Shadow): nil` *(method)*
- `pub fn draw_rect(r: rect.Rect, p: paint.Paint): nil` *(method)*
- `pub fn draw_triangle(x1: float, y1: float, x2: float, y2: float, x3: float, y3: float, p: paint.Paint): nil` *(method)*
- `pub fn draw_color(c: color.Color): nil` *(method)*
- `pub fn draw_image(img: image.Image, x: float, y: float): nil` *(method)*
- `pub fn draw_path(p: path.Path, paint_obj: paint.Paint): nil` *(method)*
- `pub fn draw_text(text_str: str, x: float, y: float, p: paint.Paint): nil` *(method)*
- `pub fn push_clip(r: rect.Rect): nil` *(method)*
- `pub fn pop_clip(): nil` *(method)*

---

