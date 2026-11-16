# API Documentation: `mesh.lm`

## Overview

std/d3/mesh.lm
Triangular mesh representation combining geometry, material, and spatial transform.

## Symbols

- **Frame**: [`Mesh`](#Mesh)

---

### `Mesh` <a id="Mesh"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Mesh
```

#### Members

- `var pub geometry: geom.Geometry` *(field)*
- `var pub material: mtrl.Material` *(field)*
- `var pub name: str` *(field)*
- `var pub visible: bool` *(field)*
- `var pub parent: Mesh?` *(field)*
- `pub init(geo: geom.Geometry, m: mtrl.Material)` *(constructor)*
- `pub fn attach_to(p: Mesh)` *(method)*
- `pub fn detach()` *(method)*
- `pub fn update_world()` *(method)*

---

