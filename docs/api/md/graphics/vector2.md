# API Documentation: `vector2.lm`

## Overview

std/graphics/vector2.lm
Vector2 submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`Vector2`](#Vector2)

---

### `Vector2` <a id="Vector2"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vector2
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(other: Vector2): Vector2` *(method)*
- `pub fn sub(other: Vector2): Vector2` *(method)*
- `pub fn scale(s: float): Vector2` *(method)*
- `pub fn dot(other: Vector2): float` *(method)*
- `pub fn mag(): float` *(method)*
- `pub fn normalize(): Vector2` *(method)*

---

