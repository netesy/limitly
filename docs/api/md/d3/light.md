# API Documentation: `light.lm`

## Overview

std/d3/light.lm
Scene illumination sources including ambient, directional, and point lights.

## Symbols

- **Frame**: [`Light`](#Light)
- **Function**: [`ambient_light`](#ambient_light)
- **Function**: [`directional_light`](#directional_light)
- **Function**: [`point_light`](#point_light)

---

### `Light` <a id="Light"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Light
```

#### Members

- `var pub light_type: types.LightType` *(field)*
- `var pub color_r: float` *(field)*
- `var pub color_g: float` *(field)*
- `var pub color_b: float` *(field)*
- `var pub intensity: float` *(field)*
- `var pub direction_x: float` *(field)*
- `var pub direction_y: float` *(field)*
- `var pub direction_z: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_direction(dx: float, dy: float, dz: float)` *(method)*

---

### `ambient_light` <a id="ambient_light"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ambient_light(r: float = ..., g: float = ..., b: float = ..., intensity: float = ...): Light
```

---

### `directional_light` <a id="directional_light"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn directional_light(dx: float = ..., dy: float = ..., dz: float = ..., r: float = ..., g: float = ..., b: float = ..., intensity: float = ...): Light
```

---

### `point_light` <a id="point_light"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn point_light(px: float = ..., py: float = ..., pz: float = ..., r: float = ..., g: float = ..., b: float = ..., intensity: float = ...): Light
```

---

