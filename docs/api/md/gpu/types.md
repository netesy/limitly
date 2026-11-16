# API Documentation: `types.lm`

## Overview

std/gpu/types.lm
Core GPU types: execution scopes, shader stages, resource enums, and
small nominal frames shared by device, queue, and shader-facing code.

## Symbols

- **Frame**: [`UVec3`](#UVec3)
- **Function**: [`uvec3`](#uvec3)
- **Frame**: [`Extent2D`](#Extent2D)
- **Frame**: [`Extent3D`](#Extent3D)
- **Function**: [`extent2d`](#extent2d)
- **Function**: [`extent3d`](#extent3d)
- **Frame**: [`Error`](#Error)
- **Frame**: [`ComputePipeline`](#ComputePipeline)
- **Frame**: [`MeshPipeline`](#MeshPipeline)
- **Frame**: [`Triangle`](#Triangle)

---

### `UVec3` <a id="UVec3"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame UVec3
```

Unsigned 3-component integer vector used for thread-space coordinates
(gpu.thread_id / local_id / group_id / num_groups).

#### Members

- `var pub x: int` *(field)*
- `var pub y: int` *(field)*
- `var pub z: int` *(field)*
- `pub init()` *(constructor)*

---

### `uvec3` <a id="uvec3"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn uvec3(x: int = ..., y: int = ..., z: int = ...): UVec3
```

---

### `Extent2D` <a id="Extent2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Extent2D
```

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `pub init()` *(constructor)*

---

### `Extent3D` <a id="Extent3D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Extent3D
```

#### Members

- `var pub x: int` *(field)*
- `var pub y: int` *(field)*
- `var pub z: int` *(field)*
- `pub init()` *(constructor)*

---

### `extent2d` <a id="extent2d"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn extent2d(width: int, height: int): Extent2D
```

---

### `extent3d` <a id="extent3d"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn extent3d(x: int = ..., y: int = ..., z: int = ...): Extent3D
```

---

### `Error` <a id="Error"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Error
```

#### Members

- `var pub code: str` *(field)*
- `var pub message: str` *(field)*
- `pub init()` *(constructor)*

---

### `ComputePipeline` <a id="ComputePipeline"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ComputePipeline
```

Pipeline descriptors. On the register VM these are plain data records;
GPU backends lower them to immutable shader bytecode at pipeline creation.

#### Members

- `var pub kernel: any` *(field)*
- `var pub threads: Extent3D` *(field)*
- `pub init()` *(constructor)*

---

### `MeshPipeline` <a id="MeshPipeline"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame MeshPipeline
```

#### Members

- `var pub mesh_fn: any` *(field)*
- `var pub pixel_fn: any` *(field)*
- `var pub max_vertices: int` *(field)*
- `var pub max_primitives: int` *(field)*
- `pub init()` *(constructor)*

---

### `Triangle` <a id="Triangle"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Triangle
```

A single vertex emitted by a mesh shader (or produced by the vertex stage).

#### Members

- `var pub v0: any` *(field)*
- `var pub v1: any` *(field)*
- `var pub v2: any` *(field)*
- `pub init()` *(constructor)*

---

