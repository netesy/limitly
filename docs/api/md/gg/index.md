# API Documentation: `index.lm`

## Overview

std.gg - Portable Sokol-GFX Style Low-Level Graphics Abstraction Module

## Symbols

- **Trait**: [`ResourceTrait`](#ResourceTrait)
- **Frame**: [`Buffer`](#Buffer)
- **Frame**: [`Image`](#Image)
- **Frame**: [`Sampler`](#Sampler)
- **Frame**: [`Shader`](#Shader)
- **Frame**: [`Pipeline`](#Pipeline)
- **Frame**: [`Bindings`](#Bindings)
- **Frame**: [`PassAction`](#PassAction)
- **Frame**: [`Pass`](#Pass)
- **Frame**: [`GraphicsContext`](#GraphicsContext)
- **Function**: [`setup`](#setup)
- **Function**: [`shutdown`](#shutdown)
- **Function**: [`is_valid`](#is_valid)
- **Function**: [`spawn_window`](#spawn_window)
- **Function**: [`push_clip`](#push_clip)
- **Function**: [`pop_clip`](#pop_clip)
- **Function**: [`poll_events`](#poll_events)
- **Function**: [`rgba`](#rgba)
- **Function**: [`make_pass_action`](#make_pass_action)
- **Function**: [`make_buffer`](#make_buffer)
- **Function**: [`make_buffer_data`](#make_buffer_data)
- **Function**: [`make_image`](#make_image)
- **Function**: [`make_sampler`](#make_sampler)
- **Function**: [`make_shader`](#make_shader)
- **Function**: [`make_pipeline`](#make_pipeline)
- **Function**: [`make_bindings`](#make_bindings)
- **Function**: [`begin_pass`](#begin_pass)
- **Function**: [`set_window_size`](#set_window_size)
- **Function**: [`draw_rect_primitive`](#draw_rect_primitive)
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

### `Image` <a id="Image"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Image: ResourceTrait
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
frame Bindings
```

#### Members

- `var pub vertex_buffer_id: int` *(field)*
- `var pub index_buffer_id: int` *(field)*
- `var pub image_id: int` *(field)*
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

### `GraphicsContext` <a id="GraphicsContext"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GraphicsContext
```

#### Members

- `var pub handle: int` *(field)*
- `var pub next_resource_id: int` *(field)*
- `pub init()` *(constructor)*

---

### `setup` <a id="setup"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn setup(): bool
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
pub fn poll_events(): any
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
pub fn make_buffer_data(size: int, is_index: bool, data: any): Buffer
```

---

### `make_image` <a id="make_image"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_image(width: int, height: int): Image
```

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

### `make_bindings` <a id="make_bindings"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_bindings(vbuf_id: int, ibuf_id: int, img_id: int, sampler_id: int): Bindings
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
pub fn apply_bindings(v_id: int, i_id: int): nil
```

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
pub fn readback_pixel(x: int, y: int): any
```

---

