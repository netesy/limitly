# API Documentation: `path.lm`

## Overview

std/graphics/path.lm
Path submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`Path`](#Path)

---

### `Path` <a id="Path"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Path
```

#### Members

- `var pub commands: list` *(field)*
- `var pub points: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn move_to(x: float, y: float): nil` *(method)*
- `pub fn line_to(x: float, y: float): nil` *(method)*
- `pub fn quadratic_curve_to(cx: float, cy: float, x: float, y: float): nil` *(method)*
- `pub fn cubic_bezier_to(c1x: float, c1y: float, c2x: float, c2y: float, x: float, y: float): nil` *(method)*
- `pub fn arc(cx: float, cy: float, radius: float, start_angle: float, end_angle: float): nil` *(method)*
- `pub fn rect(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn close(): nil` *(method)*
- `pub fn command_count(): int` *(method)*
- `pub fn point_count(): int` *(method)*
- `pub fn clear(): nil` *(method)*

---

