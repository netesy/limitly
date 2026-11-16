# API Documentation: `transform.lm`

## Overview

std/d3/transform.lm
Zero-cost spatial transformation component embedding TRS and dirty-flagged matrix caching.

## Symbols

- **Frame**: [`Transform3D`](#Transform3D)

---

### `Transform3D` <a id="Transform3D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Transform3D
```

#### Members

- `var pub position_x: float` *(field)*
- `var pub position_y: float` *(field)*
- `var pub position_z: float` *(field)*
- `var pub rotation_x: float` *(field)*
- `var pub rotation_y: float` *(field)*
- `var pub rotation_z: float` *(field)*
- `var pub scale_x: float` *(field)*
- `var pub scale_y: float` *(field)*
- `var pub scale_z: float` *(field)*
- `var pub local_matrix: Matrix` *(field)*
- `var pub world_matrix: Matrix` *(field)*
- `var pub matrix_auto_update: bool` *(field)*
- `var pub dirty: bool` *(field)*
- `var _c_px: float` *(field)*
- `var _c_py: float` *(field)*
- `var _c_pz: float` *(field)*
- `var _c_rx: float` *(field)*
- `var _c_ry: float` *(field)*
- `var _c_rz: float` *(field)*
- `var _c_sx: float` *(field)*
- `var _c_sy: float` *(field)*
- `var _c_sz: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn init_transform()` *(method)*
- `pub fn mark_dirty()` *(method)*
- `pub fn set_position(x: float, y: float, z: float)` *(method)*
- `pub fn set_rotation(rx: float, ry: float, rz: float)` *(method)*
- `pub fn set_scale(sx: float, sy: float, sz: float)` *(method)*
- `pub fn translate(dx: float, dy: float, dz: float)` *(method)*
- `pub fn rotate_x(angle: float)` *(method)*
- `pub fn rotate_y(angle: float)` *(method)*
- `pub fn rotate_z(angle: float)` *(method)*
- `pub fn update_matrix()` *(method)*

---

