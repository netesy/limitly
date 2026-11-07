# API Documentation: `vector3.lm`

## Overview

std/math/vector3.lm
Three-dimensional floating-point geometric vector.

## Symbols

- **Frame**: [`Vector3`](#Vector3)

---

### `Vector3` <a id="Vector3"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vector3
```

Represents a 3D Euclidean vector with x, y, and z Cartesian coordinates.
Supports component-wise addition and subtraction, scalar scaling,
dot product, 3D cross product, magnitude calculation, and normalization.

#### Example: Idiomatic Usage

```lymar
import std.math.vector3 as v3;
var right = v3.Vector3(1.0, 0.0, 0.0);
var up = v3.Vector3(0.0, 1.0, 0.0);
var forward = right.cross(up); // Vector3(0.0, 0.0, 1.0)
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

