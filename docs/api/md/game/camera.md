# API Documentation: `camera.lm`

## Overview

std/game/camera.lm
Canonical 2D Camera facade routing directly to std.camera.Camera2D plus world-space drawing helpers.

## Symbols

- **Function**: [`draw_world_rect`](#draw_world_rect)
- **Function**: [`draw_world_circle`](#draw_world_circle)
- **Function**: [`draw_world_line`](#draw_world_line)

---

### `draw_world_rect` <a id="draw_world_rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_world_rect(cam: Camera2D, world_rect: Rect, r: float, g: float, b: float, a: float): nil
```

---

### `draw_world_circle` <a id="draw_world_circle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_world_circle(cam: Camera2D, world_center: Vector2, radius: float, r: float, g: float, b: float, a: float, segments: int = ...): nil
```

---

### `draw_world_line` <a id="draw_world_line"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_world_line(cam: Camera2D, p1: Vector2, p2: Vector2, thickness: float, r: float, g: float, b: float, a: float): nil
```

---

