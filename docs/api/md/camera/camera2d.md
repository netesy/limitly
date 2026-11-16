# API Documentation: `camera2d.lm`

## Overview

std/camera/camera2d.lm
Universal 2D Camera with projection, tracking, zoom, rotation, and trauma-based screen shake.

## Symbols

- **Frame**: [`Camera2D`](#Camera2D)

---

### `Camera2D` <a id="Camera2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Camera2D
```

#### Members

- `var pub target: Vector2` *(field)*
- `var pub offset: Vector2` *(field)*
- `var pub rotation: float` *(field)*
- `var pub zoom: float` *(field)*
- `var pub trauma: float` *(field)*
- `var pub trauma_decay: float` *(field)*
- `var pub max_shake_offset: float` *(field)*
- `var pub max_shake_angle: float` *(field)*
- `var pub shake_time: float` *(field)*
- `var pub shake_offset: Vector2` *(field)*
- `var pub shake_rotation: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_viewport(width: float, height: float): nil` *(method)*
- `pub fn screen_to_world(screen_pos: Vector2): Vector2` *(method)*
- `pub fn world_to_screen(world_pos: Vector2): Vector2` *(method)*
- `pub fn follow(target_pos: Vector2): nil` *(method)*
- `pub fn add_trauma(amount: float): nil` *(method)*
- `pub fn update(dt: float): nil` *(method)*

---

