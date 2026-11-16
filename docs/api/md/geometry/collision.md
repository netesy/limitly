# API Documentation: `collision.lm`

## Overview

std/geometry/collision.lm
2D collision detection, contact resolution, and raycast queries over
canonical Vector2 / Rect / Circle primitives.

## Symbols

- **Frame**: [`Ray2D`](#Ray2D)
- **Function**: [`ray2d`](#ray2d)
- **Frame**: [`Contact2D`](#Contact2D)
- **Frame**: [`RayHit2D`](#RayHit2D)
- **Function**: [`test_aabb_aabb`](#test_aabb_aabb)
- **Function**: [`test_circle_circle`](#test_circle_circle)
- **Function**: [`test_circle_aabb`](#test_circle_aabb)
- **Function**: [`raycast_aabb`](#raycast_aabb)
- **Function**: [`raycast_circle`](#raycast_circle)

---

### `Ray2D` <a id="Ray2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Ray2D
```

#### Members

- `var pub origin: Vector2` *(field)*
- `var pub direction: Vector2` *(field)*
- `pub init()` *(constructor)*
- `pub fn point_at(t: float): Vector2` *(method)*

---

### `ray2d` <a id="ray2d"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ray2d(origin: Vector2 = ..., direction: Vector2 = ...): Ray2D
```

---

### `Contact2D` <a id="Contact2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Contact2D
```

#### Members

- `var pub collided: bool` *(field)*
- `var pub normal: Vector2` *(field)*
- `var pub penetration: float` *(field)*
- `var pub point: Vector2` *(field)*
- `pub init()` *(constructor)*

---

### `RayHit2D` <a id="RayHit2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RayHit2D
```

#### Members

- `var pub hit: bool` *(field)*
- `var pub point: Vector2` *(field)*
- `var pub normal: Vector2` *(field)*
- `var pub distance: float` *(field)*
- `pub init()` *(constructor)*

---

### `test_aabb_aabb` <a id="test_aabb_aabb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn test_aabb_aabb(a: Rect, b: Rect): Contact2D
```

---

### `test_circle_circle` <a id="test_circle_circle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn test_circle_circle(a: Circle, b: Circle): Contact2D
```

---

### `test_circle_aabb` <a id="test_circle_aabb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn test_circle_aabb(c: Circle, b: Rect): Contact2D
```

---

### `raycast_aabb` <a id="raycast_aabb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn raycast_aabb(ray: Ray2D, b: Rect, max_dist: float = ...): RayHit2D
```

---

### `raycast_circle` <a id="raycast_circle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn raycast_circle(ray: Ray2D, c: Circle, max_dist: float = ...): RayHit2D
```

---

