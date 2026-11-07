# API Documentation: `scene_builder.lm`

## Overview

std/scene/scene_builder.lm
Scene Builder submodule for std.scene. Scene graph nodes, 2D/3D scene trees, and transformation hierarchies.

## Symbols

- **Frame**: [`Builder`](#Builder)

---

### `Builder` <a id="Builder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Builder
```

Fluent builder for constructing and composing hierarchical scenes.

#### Example: Idiomatic Usage

```lymar
var b = Builder();
var s = b.build();
```

#### Members

- `var pub active_scene: scene.Scene` *(field)*
- `pub init()` *(constructor)*
- `pub fn build(): scene.Scene` *(method)*

---

