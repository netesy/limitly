# API Documentation: `index.lm`

## Overview

std.gg - Portable Sokol-GFX Style Low-Level Graphics Abstraction Module

## Symbols

- **Function**: [`primitive_type_code`](#primitive_type_code)
- **Trait**: [`ResourceTrait`](#ResourceTrait)
- **Frame**: [`Buffer`](#Buffer)
- **Frame**: [`Texture`](#Texture)
- **Frame**: [`Sampler`](#Sampler)
- **Frame**: [`Shader`](#Shader)
- **Frame**: [`Pipeline`](#Pipeline)
- **Frame**: [`Bindings`](#Bindings)
- **Frame**: [`PassAction`](#PassAction)
- **Frame**: [`Pass`](#Pass)
- **Frame**: [`DrawBatch`](#DrawBatch)
- **Frame**: [`GraphicsContext`](#GraphicsContext)
- **Function**: [`setup`](#setup)
- **Function**: [`setup_checked`](#setup_checked)
- **Function**: [`shutdown`](#shutdown)
- **Function**: [`is_valid`](#is_valid)
- **Function**: [`begin_batch`](#begin_batch)
- **Function**: [`flush_batch`](#flush_batch)
- **Function**: [`end_batch`](#end_batch)
- **Function**: [`submit_batch`](#submit_batch)
- **Function**: [`spawn_window`](#spawn_window)
- **Function**: [`push_clip`](#push_clip)
- **Function**: [`pop_clip`](#pop_clip)
- **Function**: [`poll_events`](#poll_events)
- **Function**: [`rgba`](#rgba)
- **Function**: [`make_pass_action`](#make_pass_action)
- **Function**: [`make_buffer`](#make_buffer)
- **Function**: [`make_buffer_data`](#make_buffer_data)
- **Function**: [`make_texture`](#make_texture)
- **Function**: [`make_texture_data`](#make_texture_data)
- **Function**: [`make_sampler`](#make_sampler)
- **Function**: [`make_shader`](#make_shader)
- **Function**: [`make_pipeline`](#make_pipeline)
- **Function**: [`make_pipeline_typed`](#make_pipeline_typed)
- **Function**: [`make_bindings`](#make_bindings)
- **Function**: [`begin_pass`](#begin_pass)
- **Function**: [`set_window_size`](#set_window_size)
- **Function**: [`draw_rect_primitive`](#draw_rect_primitive)
- **Function**: [`draw_rect_rounded_primitive`](#draw_rect_rounded_primitive)
- **Function**: [`draw_rect_border_primitive`](#draw_rect_border_primitive)
- **Function**: [`draw_line_primitive`](#draw_line_primitive)
- **Function**: [`draw_shadow_primitive`](#draw_shadow_primitive)
- **Function**: [`draw_triangle_primitive`](#draw_triangle_primitive)
- **Function**: [`draw_text`](#draw_text)
- **Function**: [`measure_text`](#measure_text)
- **Function**: [`get_line_height`](#get_line_height)
- **Function**: [`end_pass`](#end_pass)
- **Function**: [`apply_pipeline`](#apply_pipeline)
- **Function**: [`apply_bindings`](#apply_bindings)
- **Function**: [`draw`](#draw)
- **Function**: [`commit`](#commit)
- **Function**: [`readback_pixel`](#readback_pixel)

---

### `primitive_type_code` <a id="primitive_type_code"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn primitive_type_code(p: PrimitiveType): int
```

---

### `ResourceTrait` <a id="ResourceTrait"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait ResourceTrait
```

#### Members

- `fn is_valid(): bool` *(method requirement)*

---

### `Buffer` <a id="Buffer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Buffer: ResourceTrait
```

#### Members

- `var pub size: int` *(field)*
- `var pub is_index: bool` *(field)*

---

### `Texture` <a id="Texture"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Texture: ResourceTrait
```

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*

---

### `Sampler` <a id="Sampler"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Sampler: ResourceTrait
```

---

### `Shader` <a id="Shader"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Shader: ResourceTrait
```

#### Members

- `var pub vs_src: str` *(field)*
- `var pub fs_src: str` *(field)*

---

### `Pipeline` <a id="Pipeline"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Pipeline: ResourceTrait
```

#### Members

- `var pub shader_id: int` *(field)*
- `var pub primitive_type: int` *(field)*

---

### `Bindings` <a id="Bindings"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Bindings: ResourceTrait
```

#### Members

- `var pub vertex_buffer_id: int` *(field)*
- `var pub index_buffer_id: int` *(field)*
- `var pub texture_id: int` *(field)*
- `var pub sampler_id: int` *(field)*

---

### `PassAction` <a id="PassAction"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PassAction
```

#### Members

- `var pub r: float` *(field)*
- `var pub g: float` *(field)*
- `var pub b: float` *(field)*
- `var pub a: float` *(field)*
- `var pub clear: bool` *(field)*

---

### `Pass` <a id="Pass"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Pass
```

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub action: PassAction` *(field)*

---

### `DrawBatch` <a id="DrawBatch"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DrawBatch
```

Reusable flat command & float buffer to batch draw calls with zero per-call list allocations.

#### Members

- `var pub ops: list` *(field)*
- `var pub op_count: int` *(field)*
- `var pub data: list` *(field)*
- `var pub data_len: int` *(field)*
- `var pub texts: list` *(field)*
- `var pub text_count: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn clear(): nil` *(method)*
- `fn push_op(op: BatchOp): nil` *(method)*
- `fn push_f(v: float): nil` *(method)*
- `fn push_text(s: str): nil` *(method)*
- `pub fn add_rect(x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float): nil` *(method)*
- `pub fn add_triangle(x1: float, y1: float, x2: float, y2: float, x3: float, y3: float, r: float, g: float, b: float, a: float): nil` *(method)*
- `pub fn add_text(text_str: str, x: float, y: float, r: float, g: float, b: float, a: float): nil` *(method)*
- `pub fn add_clip_push(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn add_clip_pop(): nil` *(method)*

---

### `GraphicsContext` <a id="GraphicsContext"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GraphicsContext
```

#### Members

- `var pub handle: int` *(field)*
- `var pub next_resource_id: int` *(field)*
- `var pub batching: bool` *(field)*
- `var pub batch: DrawBatch` *(field)*
- `var pub _args0: list` *(field)*
- `var pub _args1i: list` *(field)*
- `var pub _args2i: list` *(field)*
- `var pub _args3i: list` *(field)*
- `var pub _args4f: list` *(field)*
- `var pub _args10f: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn flush_draw_batch(b: DrawBatch): nil` *(method)*

---

### `setup` <a id="setup"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn setup(): bool
```

---

### `setup_checked` <a id="setup_checked"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn setup_checked(): nil?
```

---

### `shutdown` <a id="shutdown"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn shutdown(): nil
```

---

### `is_valid` <a id="is_valid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_valid(): bool
```

---

### `begin_batch` <a id="begin_batch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn begin_batch(): nil
```

---

### `flush_batch` <a id="flush_batch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flush_batch(): nil
```

---

### `end_batch` <a id="end_batch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn end_batch(): nil
```

---

### `submit_batch` <a id="submit_batch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn submit_batch(b: DrawBatch): nil
```

---

### `spawn_window` <a id="spawn_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn spawn_window(width: int, height: int, title: str, resizable: int = ...): nil
```

---

### `push_clip` <a id="push_clip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_clip(x: float, y: float, w: float, h: float): nil
```

---

### `pop_clip` <a id="pop_clip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pop_clip(): nil
```

---

### `poll_events` <a id="poll_events"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn poll_events(): union
```

---

### `rgba` <a id="rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rgba(r: int, g: int, b: int): int
```

---

### `make_pass_action` <a id="make_pass_action"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_pass_action(r: float, g: float, b: float, a: float, clear: bool): PassAction
```

---

### `make_buffer` <a id="make_buffer"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_buffer(size: int, is_index: bool): Buffer
```

---

### `make_buffer_data` <a id="make_buffer_data"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_buffer_data(size: int, is_index: bool, data: list): Buffer
```

---

### `make_texture` <a id="make_texture"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_texture(width: int, height: int): Texture
```

---

### `make_texture_data` <a id="make_texture_data"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_texture_data(width: int, height: int, pixels: list): int
```

Creates a texture with initial RGBA8 pixel data and returns its id.
`pixels` is a flat byte list in row-major order, length == width*height*4.

---

### `make_sampler` <a id="make_sampler"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_sampler(): Sampler
```

---

### `make_shader` <a id="make_shader"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_shader(vs: str, fs: str): Shader
```

---

### `make_pipeline` <a id="make_pipeline"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_pipeline(shader_id: int, primitive_type: int): Pipeline
```

---

### `make_pipeline_typed` <a id="make_pipeline_typed"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_pipeline_typed(shader: Shader, primitive: PrimitiveType): Pipeline
```

---

### `make_bindings` <a id="make_bindings"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_bindings(vbuf_id: int, ibuf_id: int, tex_id: int, sampler_id: int): Bindings
```

---

### `begin_pass` <a id="begin_pass"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn begin_pass(w: int, h: int, r: float, g: float, b: float, a: float): nil
```

---

### `set_window_size` <a id="set_window_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_window_size(width: int, height: int): nil
```

---

### `draw_rect_primitive` <a id="draw_rect_primitive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_rect_primitive(x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float): nil
```

---

### `draw_rect_rounded_primitive` <a id="draw_rect_rounded_primitive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_rect_rounded_primitive(x: float, y: float, w: float, h: float, rad: float, r: float, g: float, b: float, a: float): nil
```

---

### `draw_rect_border_primitive` <a id="draw_rect_border_primitive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_rect_border_primitive(x: float, y: float, w: float, h: float, rad: float, border_w: float, r: float, g: float, b: float, a: float): nil
```

---

### `draw_line_primitive` <a id="draw_line_primitive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_line_primitive(x1: float, y1: float, x2: float, y2: float, r: float, g: float, b: float, a: float, thickness: float = ...): nil
```

---

### `draw_shadow_primitive` <a id="draw_shadow_primitive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_shadow_primitive(x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float, off_x: float, off_y: float, blur: float, spread: float): nil
```

---

### `draw_triangle_primitive` <a id="draw_triangle_primitive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_triangle_primitive(x1: float, y1: float, x2: float, y2: float, x3: float, y3: float, r: float, g: float, b: float, a: float): nil
```

---

### `draw_text` <a id="draw_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_text(text_str: str, x: float, y: float, r: float, g: float, b: float, a: float, scale: int = ...): nil
```

---

### `measure_text` <a id="measure_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn measure_text(text_str: str, scale: int = ...): float
```

---

### `get_line_height` <a id="get_line_height"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_line_height(scale: int = ...): float
```

---

### `end_pass` <a id="end_pass"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn end_pass(): nil
```

---

### `apply_pipeline` <a id="apply_pipeline"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn apply_pipeline(pip_id: int): nil
```

---

### `apply_bindings` <a id="apply_bindings"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn apply_bindings(v_id: int, i_id: int, uniforms: list? = ..., img_id: int = ..., sampler_id: int = ...): nil
```

img_id/sampler_id bind a texture for shaders that sample one (e.g. the
d3 vertex-stream pipeline). Pass 0 to leave the texture slot unbound.

---

### `draw` <a id="draw"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw(base: int, count: int, instances: int): nil
```

---

### `commit` <a id="commit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn commit(): nil
```

---

### `readback_pixel` <a id="readback_pixel"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn readback_pixel(x: int, y: int): union
```

---

