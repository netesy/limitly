# API Documentation: `controller.lm`

## Overview

std/camera/controller.lm
Interactive camera controllers: orbit (turntable around a target) and fly
(first-person look + move). Both wrap Camera3D and recompute its view
matrix from yaw/pitch state, so they compose with any projection type.

## Symbols

- **Frame**: [`OrbitController`](#OrbitController)
- **Function**: [`orbit_camera`](#orbit_camera)
- **Frame**: [`FlyController`](#FlyController)
- **Function**: [`fly_controller`](#fly_controller)

---

### `OrbitController` <a id="OrbitController"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame OrbitController
```

Turntable controller: orbits `camera` around `target` at `distance`.
Angles are radians; pitch is clamped to avoid gimbal flip at the poles.

#### Members

- `var pub camera: Camera3D` *(field)*
- `var pub target_x: float` *(field)*
- `var pub target_y: float` *(field)*
- `var pub target_z: float` *(field)*
- `var pub yaw: float` *(field)*
- `var pub pitch: float` *(field)*
- `var pub distance: float` *(field)*
- `var pub min_distance: float` *(field)*
- `var pub max_distance: float` *(field)*
- `var pub min_pitch: float` *(field)*
- `var pub max_pitch: float` *(field)*
- `var pub rotate_speed: float` *(field)*
- `var pub zoom_speed: float` *(field)*
- `pub init(target_camera: Camera3D)` *(constructor)*
- `pub fn orbit(dx: float, dy: float)` *(method)*
- `pub fn zoom(delta: float)` *(method)*
- `pub fn pan(dx: float, dy: float)` *(method)*
- `pub fn set_target(tx: float, ty: float, tz: float)` *(method)*
- `pub fn snap_behind(tx: float, ty: float, tz: float)` *(method)*
- `pub fn update()` *(method)*

---

### `orbit_camera` <a id="orbit_camera"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn orbit_camera(target_camera: Camera3D, tx: float = ..., ty: float = ..., tz: float = ..., distance_val: float = ...): OrbitController
```

---

### `FlyController` <a id="FlyController"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FlyController
```

First-person fly controller: yaw/pitch look with WASD-style translation.
Forward is -Z at yaw=pitch=0, matching Camera3D's default view direction.

#### Members

- `var pub camera: Camera3D` *(field)*
- `var pub yaw: float` *(field)*
- `var pub pitch: float` *(field)*
- `var pub speed: float` *(field)*
- `var pub sprint_multiplier: float` *(field)*
- `pub init(target_camera: Camera3D)` *(constructor)*
- `pub fn look(dx: float, dy: float)` *(method)*
- `pub fn move(forward_amt: float, right_amt: float, up_amt: float)` *(method)*
- `pub fn move_forward(dist: float)` *(method)*
- `pub fn move_right(dist: float)` *(method)*
- `pub fn move_up(dist: float)` *(method)*
- `pub fn update()` *(method)*

---

### `fly_controller` <a id="fly_controller"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fly_controller(target_camera: Camera3D, yaw_val: float = ..., pitch_val: float = ..., speed_val: float = ...): FlyController
```

---

