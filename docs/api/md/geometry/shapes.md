# API Documentation: `shapes.lm`

## Overview

std/geometry/shapes.lm
Canonical 2D geometric primitives: axis-aligned rectangles and circles.

## Symbols

- **Frame**: [`Rect`](#Rect)
- **Frame**: [`Circle`](#Circle)
- **Function**: [`rect`](#rect)

---

### `Rect` <a id="Rect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rect
```

Axis-aligned 2D rectangle defined by position (x, y) and dimensions (width, height).

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub w: float` *(field)*
- `var pub h: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn contains(px: float, py: float): bool` *(method)*
- `pub fn contains_vec(p: Vector2): bool` *(method)*
- `pub fn intersects(other: Rect): bool` *(method)*
- `pub fn intersection(other: Rect): Rect` *(method)*
- `pub fn union_rect(other: Rect): Rect` *(method)*
- `pub fn center(): Vector2` *(method)*
- `pub fn expand(amount: float): Rect` *(method)*
- `pub fn clamp_point(p: Vector2): Vector2` *(method)*
- `pub fn area(): float` *(method)*

---

### `Circle` <a id="Circle"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Circle
```

2D circle defined by a center point and radius.

#### Members

- `var pub center: Vector2` *(field)*
- `var pub radius: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn contains(p: Vector2): bool` *(method)*
- `pub fn contains_point(px: float, py: float): bool` *(method)*
- `pub fn intersects_circle(other: Circle): bool` *(method)*
- `pub fn intersects_rect(r: Rect): bool` *(method)*
- `pub fn area(): float` *(method)*

---

### `rect` <a id="rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rect(x: float = ..., y: float = ..., w: float = ..., h: float = ...): Rect
```

Convenience constructor for an axis-aligned rectangle.

---

