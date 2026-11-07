# API Documentation: `quaternion.lm`

## Overview

std/math/quaternion.lm
Quaternion representation for 3D orientation and rotation.

## Symbols

- **Frame**: [`Quaternion`](#Quaternion)

---

### `Quaternion` <a id="Quaternion"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Quaternion
```

Represents a Hamiltonian quaternion q = w + xi + yj + zk.
Widely used in 3D graphics, robotics, and physics engines for representing
spatial orientations and smooth spherical linear interpolations without gimbal lock.

#### Example: Idiomatic Usage

```lymar
import std.math.quaternion as quat;
var q = quat.Quaternion(0.0, 0.0, 0.0, 1.0); // Identity quaternion
print(q.mag()); // 1.0
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub z: float` *(field)*
- `var pub w: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(other: Quaternion): Quaternion` *(method)*
- `pub fn sub(other: Quaternion): Quaternion` *(method)*
- `pub fn scale(s: float): Quaternion` *(method)*
- `pub fn mag(): float` *(method)*
- `pub fn normalize(): Quaternion` *(method)*

---

