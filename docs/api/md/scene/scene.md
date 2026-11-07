# API Documentation: `scene.lm`

## Overview

std/scene/scene.lm
Scene submodule for std.scene. Scene graph nodes, 2D/3D scene trees, and transformation hierarchies.

## Symbols

- **Frame**: [`Scene`](#Scene)

---

### `Scene` <a id="Scene"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Scene
```

#### Members

- `var pub root: node.Node` *(field)*
- `var pub active_camera: camera.Camera` *(field)*
- `var pub vp: viewport.Viewport` *(field)*
- `pub init()` *(constructor)*

---

