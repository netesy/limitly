# API Documentation: `index.lm`

## Overview

std/linear_algebra/index.lm
Public entrypoint and facade for std.linear_algebra. Vector and matrix linear algebra routines and transformations.

## Symbols

- **Frame**: [`Vec2`](#Vec2)
- **Frame**: [`Vec3`](#Vec3)
- **Frame**: [`Mat4`](#Mat4)

---

### `Vec2` <a id="Vec2"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vec2
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(other: Vec2): Vec2` *(method)*
- `pub fn sub(other: Vec2): Vec2` *(method)*
- `pub fn scale(s: float): Vec2` *(method)*
- `pub fn dot(other: Vec2): float` *(method)*
- `pub fn mag(): float` *(method)*
- `pub fn normalize(): Vec2` *(method)*

---

### `Vec3` <a id="Vec3"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vec3
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub z: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(other: Vec3): Vec3` *(method)*
- `pub fn sub(other: Vec3): Vec3` *(method)*
- `pub fn scale(s: float): Vec3` *(method)*
- `pub fn dot(other: Vec3): float` *(method)*
- `pub fn cross(other: Vec3): Vec3` *(method)*
- `pub fn mag(): float` *(method)*
- `pub fn normalize(): Vec3` *(method)*

---

### `Mat4` <a id="Mat4"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Mat4
```

#### Members

- `var pub data: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn get(row: int, col: int): float` *(method)*
- `pub fn set(row: int, col: int, value: float)` *(method)*

---

