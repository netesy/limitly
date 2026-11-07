# API Documentation: `rect.lm`

## Overview

std/graphics/rect.lm
Rect submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`Rect`](#Rect)

---

### `Rect` <a id="Rect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rect
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub w: float` *(field)*
- `var pub h: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn contains(px: float, py: float): bool` *(method)*
- `pub fn intersects(other: Rect): bool` *(method)*
- `pub fn area(): float` *(method)*

---

