# API Documentation: `renderer.lm`

## Overview

std/d3/renderer.lm
3D scene rasterizer and projection pipeline with pooled SoA triangle buffers,
exhaustive shading/light dispatch, depth sorting, and face culling.

## Symbols

- **Function**: [`_quicksort_tri_order`](#_quicksort_tri_order)
- **Function**: [`_project_vertices_parallel`](#_project_vertices_parallel)
- **Function**: [`_render_mesh_item`](#_render_mesh_item)
- **Function**: [`_ensure_gpu_buffers`](#_ensure_gpu_buffers)
- **Function**: [`_ensure_material_texture`](#_ensure_material_texture)
- **Function**: [`_uniform_shading_int`](#_uniform_shading_int)
- **Function**: [`_uniform_cull_int`](#_uniform_cull_int)
- **Function**: [`_uniform_light_type_int`](#_uniform_light_type_int)
- **Function**: [`_pack_mesh_uniforms`](#_pack_mesh_uniforms)
- **Function**: [`_draw_mesh_gpu`](#_draw_mesh_gpu)
- **Function**: [`_render_scene_gpu`](#_render_scene_gpu)
- **Function**: [`render_scene`](#render_scene)
- **Function**: [`_render_scene_cpu`](#_render_scene_cpu)
- **Function**: [`_accumulate_lights`](#_accumulate_lights)
- **Frame**: [`Renderer3D`](#Renderer3D)

---

### `_quicksort_tri_order` <a id="_quicksort_tri_order"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _quicksort_tri_order(order: list, coords: list, low: int, high: int)
```

---

### `_project_vertices_parallel` <a id="_project_vertices_parallel"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _project_vertices_parallel(g_verts: list, m: list, v_count: int, viewport_x: float, viewport_y: float, half_vw: float, half_vh: float, proj_buf: list)
```

---

### `_render_mesh_item` <a id="_render_mesh_item"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _render_mesh_item(renderer: Renderer3D, geo: geom.Geometry, material: mtrl.Material, world: Matrix, mvp: Matrix, lights: list, n_lights: int, amb_r: float, amb_g: float, amb_b: float, viewport_x: float, viewport_y: float, half_vw: float, half_vh: float, bound_w: float, bound_h: float, bound_min_x: float, bound_max_x: float, bound_min_y: float, bound_max_y: float): nil
```

---

### `_ensure_gpu_buffers` <a id="_ensure_gpu_buffers"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ensure_gpu_buffers(geo: geom.Geometry): nil
```

Builds (once) the interleaved pos+normal+uv vertex stream and index stream
for a Geometry and uploads them as gg buffers. Local-space data is
transformed by the MVP uniform at draw time, so one buffer serves every
mesh/instance that shares the geometry. Vertex record: 8 floats
(pos3, normal3, uv2); missing UVs default to (0,0).

---

### `_ensure_material_texture` <a id="_ensure_material_texture"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ensure_material_texture(material: mtrl.Material): nil
```

Loads material.base_color_texture once and uploads it as a gg image.
material.texture_state: 0 = not tried, 1 = ready (texture_id valid),
-1 = failed (renderer falls back to flat material color).

---

### `_uniform_shading_int` <a id="_uniform_shading_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _uniform_shading_int(shading: types.ShadingModel, wireframe: bool): int
```

Uniform blob layout consumed by the runtime vertex-stream pipeline.
See src/runtime/software_graphics.hh draw_vertex_stream.

---

### `_uniform_cull_int` <a id="_uniform_cull_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _uniform_cull_int(material: mtrl.Material): int
```

---

### `_uniform_light_type_int` <a id="_uniform_light_type_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _uniform_light_type_int(light: lgt.Light): int
```

---

### `_pack_mesh_uniforms` <a id="_pack_mesh_uniforms"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _pack_mesh_uniforms(renderer: Renderer3D, geo: geom.Geometry, material: mtrl.Material, world: Matrix, mvp: Matrix, lights: list, n_lights: int, amb_r: float, amb_g: float, amb_b: float, viewport_x: float, viewport_y: float, viewport_w: float, viewport_h: float): nil
```

Fills renderer.uniform_scratch with the per-draw uniform blob. The scratch
list is grown once and overwritten in place — no per-frame allocation.

---

### `_draw_mesh_gpu` <a id="_draw_mesh_gpu"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _draw_mesh_gpu(renderer: Renderer3D, geo: geom.Geometry, material: mtrl.Material, world: Matrix, mvp: Matrix, lights: list, n_lights: int, amb_r: float, amb_g: float, amb_b: float, viewport_x: float, viewport_y: float, viewport_w: float, viewport_h: float, frustum: list): nil
```

GPU path: one vertex-stream draw call per visible mesh/instance through the
gg buffer/pipeline/bindings handles. The runtime performs vertex transform,
lighting, and z-buffered rasterization.

---

### `_render_scene_gpu` <a id="_render_scene_gpu"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _render_scene_gpu(renderer: Renderer3D, target_scene: sc.Scene3D, target_camera: cam.Camera3D, viewport_x: float, viewport_y: float, viewport_w: float, viewport_h: float)
```

---

### `render_scene` <a id="render_scene"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn render_scene(renderer: Renderer3D, target_scene: sc.Scene3D, target_camera: cam.Camera3D, viewport_x: float, viewport_y: float, viewport_w: float, viewport_h: float)
```

---

### `_render_scene_cpu` <a id="_render_scene_cpu"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _render_scene_cpu(renderer: Renderer3D, target_scene: sc.Scene3D, target_camera: cam.Camera3D, viewport_x: float, viewport_y: float, viewport_w: float, viewport_h: float)
```

---

### `_accumulate_lights` <a id="_accumulate_lights"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _accumulate_lights(s_lights: list, n_lights: int, base_r: float, base_g: float, base_b: float, fnx: float, fny: float, fnz: float, wcx: float, wcy: float, wcz: float, mat_diff: float, mat_spec: float, mat_shin: float): tuple
```

---

### `Renderer3D` <a id="Renderer3D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Renderer3D
```

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub clear_color: bool` *(field)*
- `var pub proj_buf: list` *(field)*
- `var pub tri_coords: list` *(field)*
- `var pub tri_colors: list` *(field)*
- `var pub tri_wire: list` *(field)*
- `var pub tri_wire_w: list` *(field)*
- `var pub tri_order: list` *(field)*
- `var pub tri_count: int` *(field)*
- `var pub pipeline_id: int` *(field)*
- `var pub uniform_scratch: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn push_triangle(x0: float, y0: float, x1: float, y1: float, x2: float, y2: float, avg_z: float, r: float, g: float, b: float, a: float, is_wire: bool, wire_w: float)` *(method)*
- `pub fn set_size(w: int, h: int)` *(method)*
- `pub fn render(target_scene: sc.Scene3D, target_camera: cam.Camera3D)` *(method)*

---

