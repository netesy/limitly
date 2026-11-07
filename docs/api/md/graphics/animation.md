# API Documentation: `animation.lm`

## Overview

std/graphics/animation.lm
Animation submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`Animation`](#Animation)

---

### `Animation` <a id="Animation"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Animation
```

#### Members

- `var pub duration: float` *(field)*
- `var pub current_time: float` *(field)*
- `var pub loop_val: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn update(dt: float): nil` *(method)*

---

