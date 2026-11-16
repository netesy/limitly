# API Documentation: `gpu_vulkan.lm`

## Overview

std.native.gpu_vulkan - Pure-Lymar Vulkan compute driver.

Implements a real GPU device layer entirely through std.ffi: the Vulkan
loader (vulkan-1.dll / libvulkan.so / libMoltenVK.dylib) is resolved with
vkGetInstanceProcAddr and every command is invoked through foreign_call.
All Vulkan structs are hand-marshaled into ffi.alloc'd memory - no C glue.

This is the submission backend for Fyra's SPIR-V output:
gpu_shader_create_spv() accepts SPIR-V words produced by the vendor/fyra
spirv target and vkCreateShaderModule compiles them through the platform
driver.

Scope: compute only - first compute-capable queue family, host-visible +
host-coherent memory (no staging copies), STORAGE_BUFFER descriptors
(binding index == buffer list index), synchronous dispatch with fence
wait. Vertex/pixel/mesh stages and device-local memory are later work.

Struct layouts are x86-64 Vulkan 1.1 ABI (handles/pointers 8 bytes,
enums/u32 4 bytes) taken from vulkan_core.h.

Record layouts (ffi.alloc'd, returned as int handles):
  buffer record (64B): @0 VkBuffer, @8 VkDeviceMemory, @16 mapped ptr,
                       @24 size, @32 VkDeviceSize allocSize
  pipe record (96B):   @0 VkPipeline, @8 VkPipelineLayout,
                       @16 VkDescriptorSetLayout, @24 VkDescriptorPool,
                       @32 VkDescriptorSet, @40 max_bindings

Designed for `lymar build -shared` -> native library (gpu_vulkan.dll +
.meta); the VM and AOT hosts call its exports through the Lymar ABI.

## Symbols

- **Function**: [`vk`](#vk)
- **Function**: [`vk_device`](#vk_device)
- **Function**: [`vk_resolve_all`](#vk_resolve_all)
- **Function**: [`st_u32`](#st_u32)
- **Function**: [`st_u64`](#st_u64)
- **Function**: [`st_ptr`](#st_ptr)
- **Function**: [`gpu_init`](#gpu_init)
- **Function**: [`ensure_device`](#ensure_device)
- **Function**: [`gpu_buffer_create`](#gpu_buffer_create)
- **Function**: [`gpu_buffer_write`](#gpu_buffer_write)
- **Function**: [`gpu_buffer_read`](#gpu_buffer_read)
- **Function**: [`buf_vk`](#buf_vk)
- **Function**: [`gpu_shader_create_spv`](#gpu_shader_create_spv)
- **Function**: [`gpu_pipeline_create`](#gpu_pipeline_create)
- **Function**: [`gpu_debug_phys_index`](#gpu_debug_phys_index)
- **Function**: [`gpu_dispatch`](#gpu_dispatch)
- **Function**: [`gpu_release`](#gpu_release)
- **Function**: [`gpu_shutdown`](#gpu_shutdown)

---

### `vk` <a id="vk"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn vk(name: str): int
```

vk resolves a command pointer through vkGetInstanceProcAddr. With
_instance == 0 only global commands resolve; after instance creation every
device-level command resolves through the same entry point.

---

### `vk_device` <a id="vk_device"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn vk_device(name: str): int
```

---

### `vk_resolve_all` <a id="vk_resolve_all"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn vk_resolve_all(): nil
```

---

### `st_u32` <a id="st_u32"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn st_u32(p: int, off: int, v: int): nil
```

---

### `st_u64` <a id="st_u64"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn st_u64(p: int, off: int, v: int): nil
```

---

### `st_ptr` <a id="st_ptr"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn st_ptr(p: int, off: int, v: int): nil
```

---

### `gpu_init` <a id="gpu_init"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_init(): int
```

gpu_init creates the Vulkan instance, picks the first physical device with
a compute-capable queue family, creates the device (64/16 shader features
enabled so Fyra SPIR-V modules using Int64/Float64 validate), queue,
command pool, one primary command buffer, and a fence.
Returns 1 on success. Idempotent.

---

### `ensure_device` <a id="ensure_device"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_device(): int
```

---

### `gpu_buffer_create` <a id="gpu_buffer_create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_buffer_create(bytes: int): int
```

gpu_buffer_create allocates a VkBuffer plus host-visible+coherent memory
and maps it. Returns the buffer record pointer (see header layout) or 0.

---

### `gpu_buffer_write` <a id="gpu_buffer_write"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_buffer_write(buf: int, src: int, bytes: int): int
```

gpu_buffer_write uploads `bytes` from raw address `src` into the mapped
host-visible buffer memory.

---

### `gpu_buffer_read` <a id="gpu_buffer_read"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_buffer_read(buf: int, dst: int, bytes: int): int
```

gpu_buffer_read downloads `bytes` from mapped memory to raw address `dst`.
gpu_dispatch is synchronous (fence wait), so reads after it are safe.

---

### `buf_vk` <a id="buf_vk"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn buf_vk(bufrec: int): int
```

---

### `gpu_shader_create_spv` <a id="gpu_shader_create_spv"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_shader_create_spv(code_ptr: int, code_size: int): int
```

gpu_shader_create_spv creates a VkShaderModule from SPIR-V words.
`code_ptr` is a raw address holding `code_size` bytes of little-endian
SPIR-V (4-byte aligned, multiple of 4). This is the entry point for
Fyra's spirv backend output.

---

### `gpu_pipeline_create` <a id="gpu_pipeline_create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_pipeline_create(shader_module: int, max_bindings: int): int
```

gpu_pipeline_create builds the full compute pipeline for a shader module:
descriptor set layout with `max_bindings` STORAGE_BUFFER bindings
(binding i <-> buffers[i] at dispatch), pipeline layout, descriptor pool,
one descriptor set, and the VkComputePipeline. Returns the pipe record
pointer (see header layout) or 0.

---

### `gpu_debug_phys_index` <a id="gpu_debug_phys_index"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_debug_phys_index(v: int): nil
```

---

### `gpu_dispatch` <a id="gpu_dispatch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_dispatch(pipe: int, buffers: list, x: int, y: int, z: int): int
```

gpu_dispatch updates the descriptor set with `buffers` (buffer record
pointers; index i binds descriptor binding i), records
bind-pipeline + bind-set + dispatch into the shared command buffer,
submits with the fence, and waits. Returns 1 on success.

---

### `gpu_release` <a id="gpu_release"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_release(obj: int): int
```

gpu_release frees only the ffi record memory. Object teardown is
gpu_shutdown's job.

---

### `gpu_shutdown` <a id="gpu_shutdown"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_shutdown(): int
```

gpu_shutdown destroys device-level objects, the instance, and unloads
the loader. Buffer/pipe records should be gpu_release'd first.

---

