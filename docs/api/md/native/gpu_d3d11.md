# API Documentation: `gpu_d3d11.lm`

## Overview

std.native.gpu_d3d11 - Pure-Lymar D3D11 compute driver.

Implements a real GPU device layer entirely through std.ffi: COM vtable
calls into d3d11.dll / dxgi.dll / d3dcompiler_*.dll, hand-marshaled
D3D11_BUFFER_DESC / D3D11_SUBRESOURCE_DATA / MAPPED_SUBRESOURCE structs,
and HLSL->DXBC shader compilation via D3DCompile. No C glue.

This module is designed to be precompiled with `lymar build -shared` into
a native library (gpu_d3d11.dll + .meta). The VM and AOT hosts then call
its exports through the Lymar ABI (CompiledResolver) - native speed, one
implementation shared by both backends.

Scope: compute only (buffers, SRV/UAV, compile shaders, dispatch,
readback). Vertex/pixel/mesh stages are a later milestone.

VTable indices (stable D3D11 ABI, IUnknown occupies slots 0-2):
  ID3D11Device:          Release=2 CreateBuffer=3 CreateSRV=7 CreateUAV=8
                         CreateComputeShader=18
  ID3D11DeviceContext (incl. ID3D11DeviceChild slots 3-6):
    Map=14 Unmap=15 Dispatch=41 CopyResource=47
    CSSetShaderResources=67 CSSetUnorderedAccessViews=68 CSSetShader=69
  ID3DBlob:              GetBufferPointer=3 GetBufferSize=4

## Symbols

- **Function**: [`com`](#com)
- **Function**: [`com_i32`](#com_i32)
- **Function**: [`com_void`](#com_void)
- **Function**: [`release`](#release)
- **Function**: [`gpu_init`](#gpu_init)
- **Function**: [`ensure_device`](#ensure_device)
- **Function**: [`gpu_buffer_create`](#gpu_buffer_create)
- **Function**: [`gpu_uav_create_typed`](#gpu_uav_create_typed)
- **Function**: [`gpu_uav_create`](#gpu_uav_create)
- **Function**: [`gpu_srv_create`](#gpu_srv_create)
- **Function**: [`gpu_shader_create`](#gpu_shader_create)
- **Function**: [`gpu_dispatch`](#gpu_dispatch)
- **Function**: [`gpu_buffer_write`](#gpu_buffer_write)
- **Function**: [`gpu_buffer_read`](#gpu_buffer_read)
- **Function**: [`gpu_release`](#gpu_release)

---

### `com` <a id="com"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn com(obj: int, index: int, args: list, ret: int): any
```

---

### `com_i32` <a id="com_i32"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn com_i32(obj: int, index: int, args: list): int
```

---

### `com_void` <a id="com_void"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn com_void(obj: int, index: int, args: list): nil
```

---

### `release` <a id="release"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn release(obj: int): nil
```

---

### `gpu_init` <a id="gpu_init"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_init(): int
```

gpu_init creates the D3D11 device + immediate context (HARDWARE first,
WARP fallback). Returns 1 on success. Idempotent.

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
pub fn gpu_buffer_create(bytes: int, usage: int, bind: int, cpu_access: int, misc: int, stride: int, initial_ptr: int): int
```

gpu_buffer_create: D3D11_BUFFER_DESC is 24 bytes of u32 fields.
bytes, usage, bind_flags, cpu_access, misc_flags, structure_stride
initial_ptr may be 0 or a raw address with `bytes` of upload data.

---

### `gpu_uav_create_typed` <a id="gpu_uav_create_typed"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_uav_create_typed(buf: int, format: int, num: int): int
```

gpu_uav_create_typed builds a D3D11_UNORDERED_ACCESS_VIEW_DESC for a typed
buffer view (e.g. RWBuffer<uint> with DXGI_FORMAT_R32_UINT=42) and creates
the UAV. The 32-byte desc is zeroed, then Format/ViewDimension/Buffer
fields are stored at their documented offsets.

---

### `gpu_uav_create` <a id="gpu_uav_create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_uav_create(buf: int): int
```

gpu_uav_create: default (NULL) view desc — only valid for buffers whose
usage allows an implicit view.

---

### `gpu_srv_create` <a id="gpu_srv_create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_srv_create(buf: int): int
```

---

### `gpu_shader_create` <a id="gpu_shader_create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_shader_create(hlsl: str): int
```

gpu_shader_create compiles HLSL source through D3DCompile and creates a
compute shader. Returns the ID3D11ComputeShader* or 0 on failure.

---

### `gpu_dispatch` <a id="gpu_dispatch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_dispatch(shader: int, uavs: list, srvs: list, x: int, y: int, z: int): int
```

gpu_dispatch binds the shader plus UAV/SRV arrays and issues Dispatch.
uavs/srvs are Lymar [int] lists of COM view pointers; pass empty lists to
leave a slot class unbound.

---

### `gpu_buffer_write` <a id="gpu_buffer_write"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_buffer_write(buf: int, src: int, bytes: int): int
```

gpu_buffer_write uploads `bytes` from raw address `src` into a DEFAULT or
DYNAMIC buffer via Map(WRITE_DISCARD).

---

### `gpu_buffer_read` <a id="gpu_buffer_read"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_buffer_read(buf: int, dst: int, bytes: int): int
```

gpu_buffer_read downloads `bytes` through an internal staging buffer.

---

### `gpu_release` <a id="gpu_release"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gpu_release(obj: int): int
```

gpu_release drops a COM reference (buffers, views, shaders, device).

---

