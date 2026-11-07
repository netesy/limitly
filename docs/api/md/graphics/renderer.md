# API Documentation: `renderer.lm`

## Overview

std/graphics/renderer.lm
Renderer submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`Renderer`](#Renderer)

---

### `Renderer` <a id="Renderer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Renderer
```

#### Members

- `var pub is_active: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn begin_frame(surf: surface.Surface): canvas.Canvas` *(method)*
- `pub fn end_frame(): nil` *(method)*

---

