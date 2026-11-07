# API Documentation: `math.lm`

## Overview

std/game/math.lm
2D Game Math, Geometry, Collision Detection, and Raycasting Primitives

## Symbols

- **Function**: [`Vec2`](#Vec2)
- **Function**: [`vec2`](#vec2)
- **Function**: [`Rect`](#Rect)
- **Function**: [`rect`](#rect)
- **Frame**: [`Circle`](#Circle)
- **Function**: [`circle`](#circle)
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

### `Vec2` <a id="Vec2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn Vec2(x: float = ..., y: float = ...): types.Vec2
```

Re-export core types

---

### `vec2` <a id="vec2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn vec2(x: float, y: float): types.Vec2
```

---

### `Rect` <a id="Rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn Rect(x: float = ..., y: float = ..., w: float = ..., h: float = ...): types.Rect
```

---

### `rect` <a id="rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rect(x: float, y: float, w: float, h: float): types.Rect
```

---

### `Circle` <a id="Circle"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Circle
```

#### Members

- `var pub center: types.Vec2` *(field)*
- `var pub radius: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn contains(p: types.Vec2): bool` *(method)*
- `pub fn intersects_circle(other: Circle): bool` *(method)*
- `pub fn intersects_rect(r: types.Rect): bool` *(method)*

---

### `circle` <a id="circle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn circle(center: types.Vec2 = ..., radius: float = ...): Circle
```

---

### `Ray2D` <a id="Ray2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Ray2D
```

#### Members

- `var pub origin: types.Vec2` *(field)*
- `var pub direction: types.Vec2` *(field)*
- `pub init()` *(constructor)*
- `pub fn point_at(t: float): types.Vec2` *(method)*

---

### `ray2d` <a id="ray2d"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ray2d(origin: types.Vec2 = ..., direction: types.Vec2 = ...): Ray2D
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
- `var pub normal: types.Vec2` *(field)*
- `var pub penetration: float` *(field)*
- `var pub point: types.Vec2` *(field)*
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
- `var pub point: types.Vec2` *(field)*
- `var pub normal: types.Vec2` *(field)*
- `var pub distance: float` *(field)*
- `pub init()` *(constructor)*

---

### `test_aabb_aabb` <a id="test_aabb_aabb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn test_aabb_aabb(a: types.Rect, b: types.Rect): Contact2D
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
pub fn test_circle_aabb(c: Circle, b: types.Rect): Contact2D
```

---

### `raycast_aabb` <a id="raycast_aabb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn raycast_aabb(ray: Ray2D, b: types.Rect, max_dist: float = ...): RayHit2D
```

---

### `raycast_circle` <a id="raycast_circle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn raycast_circle(ray: Ray2D, c: Circle, max_dist: float = ...): RayHit2D
```

---

