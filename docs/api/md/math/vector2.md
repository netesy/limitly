# API Documentation: `vector2.lm`

## Overview

std/math/vector2.lm
Two-dimensional floating-point geometric vector.

## Symbols

- **Frame**: [`Vector2`](#Vector2)

---

### `Vector2` <a id="Vector2"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vector2
```

Represents a 2D Euclidean vector with x and y Cartesian coordinates.
Supports basic vector arithmetic (addition, subtraction, scalar scaling),
dot product, magnitude calculation, and normalization.

#### Example: Idiomatic Usage

```lymar
import std.math.vector2 as v2;
var a = v2.Vector2(3.0, 4.0);
print(a.mag()); // 5.0
var b = a.normalize();
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

