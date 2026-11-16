# API Documentation: `culling.lm`

## Overview

std/d3/culling.lm
Bounding volumes and frustum culling. Pure math over Geometry + Matrix so it
can be unit-tested without a renderer or window.

Convention: matrices are row-major `data[row*4+col]`, column-vector
multiplication (clip = M * v), translation in m[3], m[7], m[11].

## Symbols

- **Function**: [`geometry_bounds`](#geometry_bounds)
- **Function**: [`world_sphere`](#world_sphere)
- **Function**: [`frustum_planes`](#frustum_planes)
- **Function**: [`sphere_in_frustum`](#sphere_in_frustum)
- **Function**: [`sphere_visible`](#sphere_visible)

---

### `geometry_bounds` <a id="geometry_bounds"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn geometry_bounds(geo: geom.Geometry): tuple
```

Local-space bounding sphere of a geometry's vertices:
returns (center_x, center_y, center_z, radius).

---

### `world_sphere` <a id="world_sphere"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn world_sphere(geo: geom.Geometry, world: Matrix): tuple
```

Transform a local-space bounding sphere into world space.
Returns (center_x, center_y, center_z, radius).

---

### `frustum_planes` <a id="frustum_planes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn frustum_planes(vp: Matrix): list
```

Extract the six view-frustum planes from a view-projection matrix.
Returns 24 floats: 6 planes x (a, b, c, d) with the plane equation
a*x + b*y + c*z + d >= 0 meaning "inside" for world-space points.
Order: left, right, bottom, top, near, far.

---

### `sphere_in_frustum` <a id="sphere_in_frustum"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sphere_in_frustum(planes: list, cx: float, cy: float, cz: float, radius: float): bool
```

True if the world-space sphere may intersect the frustum (conservative).

---

### `sphere_visible` <a id="sphere_visible"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sphere_visible(planes: list, geo: geom.Geometry, world: Matrix): bool
```

Convenience: bounds + frustum test in one call.

---

