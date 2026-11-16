# API Documentation: `camera3d.lm`

## Overview

std/camera/camera3d.lm
Universal 3D camera defining viewport projections and eye view transforms.

## Symbols

- **Frame**: [`Camera3D`](#Camera3D)
- **Function**: [`perspective_camera`](#perspective_camera)
- **Function**: [`orthographic_camera`](#orthographic_camera)

---

### `Camera3D` <a id="Camera3D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Camera3D
```

#### Members

- `var pub camera_type: types.CameraType` *(field)*
- `var pub fov_degrees: float` *(field)*
- `var pub aspect: float` *(field)*
- `var pub near: float` *(field)*
- `var pub far: float` *(field)*
- `var pub ortho_left: float` *(field)*
- `var pub ortho_right: float` *(field)*
- `var pub ortho_top: float` *(field)*
- `var pub ortho_bottom: float` *(field)*
- `var pub projection_matrix: mat.Matrix` *(field)*
- `var pub view_matrix: mat.Matrix` *(field)*
- `var pub view_projection_matrix: mat.Matrix` *(field)*
- `pub init()` *(constructor)*
- `pub fn update_projection_matrix()` *(method)*
- `pub fn update_view_matrix()` *(method)*
- `pub fn look_at(target_x: float, target_y: float, target_z: float)` *(method)*
- `pub fn update_view_projection()` *(method)*

---

### `perspective_camera` <a id="perspective_camera"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn perspective_camera(fov_deg: float = ..., aspect: float = ..., near: float = ..., far: float = ...): Camera3D
```

---

### `orthographic_camera` <a id="orthographic_camera"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn orthographic_camera(left: float = ..., right: float = ..., top: float = ..., bottom: float = ..., near: float = ..., far: float = ...): Camera3D
```

---

