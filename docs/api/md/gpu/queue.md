# API Documentation: `queue.lm`

## Overview

std/gpu/queue.lm
GPU command submission model: CommandBuffer records work, Encoder builds
command buffers, Queue submits them, Fence tracks completion.

On the register VM, Encoder.dispatch records (task, grid, args) tuples and
CommandBuffer.execute replays them through the gpu_dispatch emulation
builtin. GPU backends replace the replay with real command encoding.

## Symbols

- **Frame**: [`CommandBuffer`](#CommandBuffer)
- **Frame**: [`Encoder`](#Encoder)
- **Frame**: [`Fence`](#Fence)
- **Frame**: [`Queue`](#Queue)

---

### `CommandBuffer` <a id="CommandBuffer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame CommandBuffer
```

A finished, submittable command buffer. `dispatches` holds recorded work
items of the shape [task_ref, gx, gy, gz, args_list].

#### Members

- `var pub dispatches: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn execute(): nil` *(method)*

---

### `Encoder` <a id="Encoder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Encoder
```

Records commands for later submission via finish() + Queue.submit().

#### Members

- `var pub commands: CommandBuffer` *(field)*
- `pub init()` *(constructor)*
- `pub fn dispatch(kernel: any, grid: types.Extent3D, args: list): nil` *(method)*
- `pub fn dispatch_dims(kernel: any, gx: int, gy: int, gz: int, args: list): nil` *(method)*
- `pub fn barrier(): nil` *(method)*
- `pub fn finish(): CommandBuffer` *(method)*

---

### `Fence` <a id="Fence"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Fence
```

Completion signal for submitted command buffers.

#### Members

- `var pub signaled: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn wait(): nil` *(method)*
- `pub fn is_signaled(): bool` *(method)*

---

### `Queue` <a id="Queue"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Queue
```

Submission queue owning command-buffer execution.

#### Members

- `pub fn encoder(): Encoder` *(method)*
- `pub fn submit(cmd: CommandBuffer): Fence` *(method)*
- `pub fn submit_and_wait(cmd: CommandBuffer): nil` *(method)*

---

