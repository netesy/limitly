# API Documentation: `vector3.lm`

## Overview

std/graphics/vector3.lm
Vector3 submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`Vector3`](#Vector3)

---

### `Vector3` <a id="Vector3"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vector3
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub z: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(other: Vector3): Vector3` *(method)*
- `pub fn sub(other: Vector3): Vector3` *(method)*
- `pub fn scale(s: float): Vector3` *(method)*
- `pub fn dot(other: Vector3): float` *(method)*
- `pub fn cross(other: Vector3): Vector3` *(method)*
- `pub fn mag(): float` *(method)*
- `pub fn normalize(): Vector3` *(method)*

---

