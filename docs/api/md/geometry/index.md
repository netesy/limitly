# API Documentation: `index.lm`

## Overview

std/geometry/index.lm
Public entrypoint and facade for std.geometry. Geometric shapes, intersections, bounding boxes, and containment.

## Symbols

- **Frame**: [`Rect`](#Rect)
- **Frame**: [`Circle`](#Circle)

---

### `Rect` <a id="Rect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rect
```

Axis-aligned 2D rectangle defined by position (x, y) and dimensions (width, height).

#### Example: Idiomatic Usage

```lymar
var r = Rect(0.0, 0.0, 100.0, 50.0);
assert(r.contains(10.0, 10.0));
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

### `Circle` <a id="Circle"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Circle
```

2D circle defined by center (x, y) and radius r.

#### Example: Idiomatic Usage

```lymar
var c = Circle(0.0, 0.0, 10.0);
assert(c.contains(5.0, 5.0));
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub r: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn contains(px: float, py: float): bool` *(method)*
- `pub fn area(): float` *(method)*

---

