# API Documentation: `scene.lm`

## Overview

std/d3/scene.lm
Scene container holding 3D meshes, instanced draws, illumination sources,
and environment settings.

## Symbols

- **Frame**: [`InstanceGroup`](#InstanceGroup)
- **Frame**: [`Scene3D`](#Scene3D)

---

### `InstanceGroup` <a id="InstanceGroup"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame InstanceGroup
```

One geometry drawn many times with different local transforms.
Each entry in `transforms` is multiplied after the mesh's own world matrix.

#### Members

- `var pub mesh: mesh_mod.Mesh` *(field)*
- `var pub transforms: list` *(field)*
- `pub init(m: mesh_mod.Mesh, instance_transforms: list)` *(constructor)*

---

### `Scene3D` <a id="Scene3D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Scene3D
```

#### Members

- `var pub meshes: list` *(field)*
- `var pub instance_groups: list` *(field)*
- `var pub lights: list` *(field)*
- `var pub background_r: float` *(field)*
- `var pub background_g: float` *(field)*
- `var pub background_b: float` *(field)*
- `var pub background_a: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(m: mesh_mod.Mesh)` *(method)*
- `pub fn add_instanced(m: mesh_mod.Mesh, transforms: list)` *(method)*
- `pub fn add_light(l: light_mod.Light)` *(method)*
- `pub fn clear()` *(method)*

---

