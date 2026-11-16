# API Documentation: `intrinsics.lm`

## Overview

std/gpu/intrinsics.lm
Thread-space intrinsics and workgroup operations. These wrap the gpu_*
builtins that the register VM executes as emulation and GPU backends lower
to hardware instructions. Only meaningful inside `gpu task` bodies (and
`gpu mesh`/`gpu vertex`/`gpu pixel` stages once those dispatch paths exist).

## Symbols

- **Function**: [`thread_id`](#thread_id)
- **Function**: [`local_id`](#local_id)
- **Function**: [`group_id`](#group_id)
- **Function**: [`num_groups`](#num_groups)
- **Function**: [`sync`](#sync)
- **Function**: [`set_mesh_counts`](#set_mesh_counts)

---

### `thread_id` <a id="thread_id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn thread_id(): UVec3
```

Global invocation id across the whole dispatched grid (group * local_size + local).

---

### `local_id` <a id="local_id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn local_id(): UVec3
```

Index of this thread within its workgroup.

---

### `group_id` <a id="group_id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn group_id(): UVec3
```

Workgroup (thread-block) index of this thread.

---

### `num_groups` <a id="num_groups"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn num_groups(): UVec3
```

Number of workgroups along each grid axis.

---

### `sync` <a id="sync"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sync(scope: Scope): nil
```

Workgroup / subgroup / invocation memory and execution barrier.

---

### `set_mesh_counts` <a id="set_mesh_counts"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_mesh_counts(vertices: int, primitives: int): nil
```

Allocate mesh output topology for the current mesh shader invocation.

---

