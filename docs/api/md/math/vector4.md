# API Documentation: `vector4.lm`

## Overview

std/math/vector4.lm
Four-dimensional floating-point geometric or homogeneous vector.

## Symbols

- **Frame**: [`Vector4`](#Vector4)

---

### `Vector4` <a id="Vector4"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vector4
```

Represents a 4D vector or homogeneous coordinate tuple (x, y, z, w).
Supports basic vector arithmetic, dot product, magnitude calculation, and normalization.

#### Example: Idiomatic Usage

```lymar
import std.math.vector4 as v4;
var v = v4.Vector4(1.0, 2.0, 3.0, 1.0);
print(v.mag());
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub z: float` *(field)*
- `var pub w: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(other: Vector4): Vector4` *(method)*
- `pub fn sub(other: Vector4): Vector4` *(method)*
- `pub fn scale(s: float): Vector4` *(method)*
- `pub fn dot(other: Vector4): float` *(method)*
- `pub fn mag(): float` *(method)*
- `pub fn normalize(): Vector4` *(method)*

---

