# API Documentation: `camera.lm`

## Overview

std/game/camera.lm
2D Camera system with coordinate projection, tracking, zoom, rotation, and trauma-based screen shake

## Symbols

- **Frame**: [`Camera2D`](#Camera2D)
- **Function**: [`Camera`](#Camera)

---

### `Camera2D` <a id="Camera2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Camera2D: gtraits.Updatable
```

#### Members

- `var pub target: types.Vec2` *(field)*
- `var pub offset: types.Vec2` *(field)*
- `var pub rotation: float` *(field)*
- `var pub zoom: float` *(field)*
- `var pub trauma: float` *(field)*
- `var pub trauma_decay: float` *(field)*
- `var pub max_shake_offset: float` *(field)*
- `var pub max_shake_angle: float` *(field)*
- `var pub shake_time: float` *(field)*
- `var pub shake_offset: types.Vec2` *(field)*
- `var pub shake_rotation: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_viewport(width: float, height: float): nil` *(method)*
- `pub fn screen_to_world(screen_pos: types.Vec2): types.Vec2` *(method)*
- `pub fn world_to_screen(world_pos: types.Vec2): types.Vec2` *(method)*
- `pub fn follow(target_pos: types.Vec2): nil` *(method)*
- `pub fn add_trauma(amount: float): nil` *(method)*
- `pub fn update(dt: float): nil` *(method)*
- `pub fn draw_rect(world_rect: types.Rect, r: float, g: float, b: float, a: float): nil` *(method)*
- `pub fn draw_circle(world_center: types.Vec2, radius: float, r: float, g: float, b: float, a: float): nil` *(method)*
- `pub fn draw_line(p1: types.Vec2, p2: types.Vec2, thickness: float, r: float, g: float, b: float, a: float): nil` *(method)*

---

### `Camera` <a id="Camera"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn Camera(target: types.Vec2 = ..., offset: types.Vec2 = ..., zoom: float = ...): Camera2D
```

---

