# API Documentation: `device.lm`

## Overview

std/gpu/device.lm
GPU device abstraction: capability limits, device info, and pipeline
construction. On the register VM this is a lightweight descriptor layer;
real backends bind it to a native GPU device.

## Symbols

- **Frame**: [`Limits`](#Limits)
- **Frame**: [`Info`](#Info)
- **Frame**: [`Device`](#Device)
- **Function**: [`device`](#device)

---

### `Limits` <a id="Limits"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Limits
```

#### Members

- `var pub max_texture_dimension_2d: int` *(field)*
- `var pub max_texture_dimension_3d: int` *(field)*
- `var pub max_buffer_size: int` *(field)*
- `var pub max_compute_workgroup_size: types.UVec3` *(field)*
- `var pub max_compute_workgroups_per_dimension: int` *(field)*
- `pub init()` *(constructor)*

---

### `Info` <a id="Info"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Info
```

#### Members

- `var pub name: str` *(field)*
- `var pub backend: str` *(field)*
- `pub init()` *(constructor)*

---

### `Device` <a id="Device"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Device
```

#### Members

- `var pub info_: Info` *(field)*
- `pub init()` *(constructor)*
- `pub fn info(): Info` *(method)*
- `pub fn is_valid(): bool` *(method)*
- `pub fn default_queue(): Queue` *(method)*
- `pub fn create_compute_pipeline(kernel: any): ComputePipeline` *(method)*
- `pub fn create_mesh_pipeline(mesh: any, pixel: any, max_vertices: int, max_primitives: int): MeshPipeline` *(method)*

---

### `device` <a id="device"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn device(): Device
```

---

