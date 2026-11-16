# API Documentation: `primitives.lm`

## Overview

std/d3/primitives.lm
Parametric and procedural 3D geometric shapes inspired by Three.js.

## Symbols

- **Function**: [`_staged_box_face_count`](#_staged_box_face_count)
- **Function**: [`box_face_count`](#box_face_count)
- **Function**: [`sphere_face_count`](#sphere_face_count)
- **Function**: [`sphere_vertex_count`](#sphere_vertex_count)
- **Function**: [`cylinder_face_count`](#cylinder_face_count)
- **Function**: [`plane_face_count`](#plane_face_count)
- **Function**: [`box`](#box)
- **Function**: [`sphere`](#sphere)
- **Function**: [`cylinder`](#cylinder)
- **Function**: [`plane`](#plane)
- **Function**: [`cone`](#cone)
- **Function**: [`torus`](#torus)

---

### `_staged_box_face_count` <a id="_staged_box_face_count"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _staged_box_face_count(): int
```

---

### `box_face_count` <a id="box_face_count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn box_face_count(): int
```

Returns the number of triangular faces in a box geometry.

---

### `sphere_face_count` <a id="sphere_face_count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sphere_face_count(segments_w: int, segments_h: int): int
```

Computes the face count of a UV sphere based on segments.

---

### `sphere_vertex_count` <a id="sphere_vertex_count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sphere_vertex_count(segments_w: int, segments_h: int): int
```

Computes the vertex count of a UV sphere.

---

### `cylinder_face_count` <a id="cylinder_face_count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cylinder_face_count(radial_segments: int): int
```

Computes the face count of a cylinder with end caps.

---

### `plane_face_count` <a id="plane_face_count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plane_face_count(segments_w: int, segments_h: int): int
```

Computes the face count of a segmented plane mesh.

---

### `box` <a id="box"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn box(width: float = ..., height: float = ..., depth: float = ...): geom.Geometry
```

Creates a 3D rectangular cuboid geometry centered at the origin.

---

### `sphere` <a id="sphere"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sphere(radius: float = ..., width_segments: int = ..., height_segments: int = ...): geom.Geometry
```

Creates a UV sphere geometry.

---

### `cylinder` <a id="cylinder"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cylinder(radius_top: float = ..., radius_bottom: float = ..., height: float = ..., radial_segments: int = ...): geom.Geometry
```

Creates a cylinder or frustum geometry.

---

### `plane` <a id="plane"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn plane(width: float = ..., height: float = ..., width_segments: int = ..., height_segments: int = ...): geom.Geometry
```

Creates a 2D plane geometry lying in the X-Z plane.

---

### `cone` <a id="cone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cone(radius: float = ..., height: float = ..., radial_segments: int = ...): geom.Geometry
```

Creates a 3D cone geometry with a circular base and apex at the top.

---

### `torus` <a id="torus"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn torus(radius: float = ..., tube: float = ..., radial_segments: int = ..., tubular_segments: int = ...): geom.Geometry
```

Creates a 3D torus (donut-shaped) geometry.

---

