# API Documentation: `geometry.lm`

## Overview

std/d3/geometry.lm
Triangular mesh geometry data structure backed by staged BufferAttribute(T) storage.

## Symbols

- **Frame**: [`ValidationReport`](#ValidationReport)
- **Frame**: [`Geometry`](#Geometry)

---

### `ValidationReport` <a id="ValidationReport"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ValidationReport
```

Result of Geometry.validate(): counts of structural problems plus human-readable
issue strings. A clean mesh has all counts at zero and is_watertight == true.

#### Members

- `var pub vertex_count: int` *(field)*
- `var pub face_count: int` *(field)*
- `var pub invalid_indices: int` *(field)*
- `var pub degenerate_faces: int` *(field)*
- `var pub boundary_edges: int` *(field)*
- `var pub non_manifold_edges: int` *(field)*
- `var pub inconsistent_winding: bool` *(field)*
- `var pub issues: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn is_clean(): bool` *(method)*
- `pub fn summary(): str` *(method)*

---

### `Geometry` <a id="Geometry"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Geometry
```

#### Members

- `var pub pos_attr: buf.FloatAttribute` *(field)*
- `var pub normal_attr: buf.FloatAttribute` *(field)*
- `var pub uv_attr: buf.FloatAttribute` *(field)*
- `var pub color_attr: buf.FloatAttribute` *(field)*
- `var pub index_attr: buf.IntAttribute` *(field)*
- `var pub vertices: list` *(field)*
- `var pub normals: list` *(field)*
- `var pub uvs: list` *(field)*
- `var pub colors: list` *(field)*
- `var pub indices: list` *(field)*
- `var pub gpu_vbuf: int` *(field)*
- `var pub gpu_ibuf: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn add_vertex(x: float, y: float, z: float): int` *(method)*
- `pub fn add_normal(nx: float, ny: float, nz: float)` *(method)*
- `pub fn add_uv(u: float, v: float)` *(method)*
- `pub fn add_color(r: float, g: float, b: float)` *(method)*
- `pub fn add_face(i0: int, i1: int, i2: int)` *(method)*
- `pub fn get_vertex_count(): int` *(method)*
- `pub fn get_face_count(): int` *(method)*
- `pub fn get_vertex_x(idx: int): float` *(method)*
- `pub fn get_vertex_y(idx: int): float` *(method)*
- `pub fn get_vertex_z(idx: int): float` *(method)*
- `pub fn compute_vertex_normals()` *(method)*
- `pub fn scale(sx: float, sy: float, sz: float)` *(method)*
- `pub fn translate(dx: float, dy: float, dz: float)` *(method)*
- `pub fn add_quad(i0: int, i1: int, i2: int, i3: int)` *(method)*
- `pub fn clone(): Geometry` *(method)*
- `pub fn merge(other: Geometry)` *(method)*
- `pub fn mirror(): Geometry` *(method)*
- `pub fn rotate_x(angle: float)` *(method)*
- `pub fn rotate_y(angle: float)` *(method)*
- `pub fn rotate_z(angle: float)` *(method)*
- `pub fn validate(): ValidationReport` *(method)*
- `pub fn make_double_sided(): Geometry` *(method)*

---

