# API Documentation: `index.lm`

## Overview

std/image/index.lm

Core image types, fluent manipulation, shared lifecycle, and pixel access.
Sub-modules (png, jpg, bmp, tga, hdr) import this module.

## Symbols

- **Frame**: [`Pixel`](#Pixel)
- **Function**: [`rgb`](#rgb)
- **Function**: [`rgba`](#rgba)
- **Function**: [`color_rgb`](#color_rgb)
- **Function**: [`color_rgba`](#color_rgba)
- **Function**: [`color_rgb8`](#color_rgb8)
- **Frame**: [`Info`](#Info)
- **Function**: [`_open_lib`](#_open_lib)
- **Frame**: [`Image`](#Image)
- **Function**: [`load`](#load)
- **Function**: [`load_forced`](#load_forced)
- **Function**: [`query`](#query)
- **Function**: [`create`](#create)
- **Function**: [`get_pixel`](#get_pixel)
- **Function**: [`set_pixel`](#set_pixel)
- **Function**: [`free_image`](#free_image)
- **Function**: [`free`](#free)
- **Function**: [`destroy`](#destroy)
- **Function**: [`clone`](#clone)
- **Function**: [`resize`](#resize)
- **Function**: [`crop`](#crop)
- **Function**: [`flip_vertical`](#flip_vertical)
- **Function**: [`flip_horizontal`](#flip_horizontal)
- **Function**: [`rotate_90`](#rotate_90)
- **Function**: [`fill`](#fill)
- **Function**: [`fill_rect`](#fill_rect)
- **Function**: [`draw_line`](#draw_line)
- **Function**: [`flip_v`](#flip_v)
- **Function**: [`flip_h`](#flip_h)
- **Function**: [`blit`](#blit)
- **Function**: [`blend_blit`](#blend_blit)
- **Function**: [`save_png`](#save_png)
- **Function**: [`save_jpg`](#save_jpg)
- **Function**: [`save_bmp`](#save_bmp)
- **Function**: [`save_tga`](#save_tga)
- **Function**: [`save`](#save)
- **Frame**: [`PngFacade`](#PngFacade)
- **Frame**: [`JpgFacade`](#JpgFacade)
- **Frame**: [`BmpFacade`](#BmpFacade)
- **Frame**: [`TgaFacade`](#TgaFacade)
- **Function**: [`detect_system_font`](#detect_system_font)

---

### `Pixel` <a id="Pixel"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Pixel
```

── Pixel value frame ─────────────────────────────────────────────────────

#### Members

- `var pub r: int` *(field)*
- `var pub g: int` *(field)*
- `var pub b: int` *(field)*
- `var pub a: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn with_alpha(new_a: int): Pixel` *(method)*

---

### `rgb` <a id="rgb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rgb(r: int, g: int, b: int): Pixel
```

── Semantic Color Constructors & Palettes (Fluent style matching std.ui) ──

---

### `rgba` <a id="rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rgba(r: int, g: int, b: int, a: int): Pixel
```

---

### `color_rgb` <a id="color_rgb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgb(r: float, g: float, b: float): Pixel
```

---

### `color_rgba` <a id="color_rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgba(r: float, g: float, b: float, a: float): Pixel
```

---

### `color_rgb8` <a id="color_rgb8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgb8(r: int, g: int, b: int): Pixel
```

---

### `Info` <a id="Info"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Info
```

── Image metadata frame ──────────────────────────────────────────────────

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub channels: int` *(field)*
- `pub init()` *(constructor)*

---

### `_open_lib` <a id="_open_lib"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _open_lib(): int
```

---

### `Image` <a id="Image"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Image
```

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub channels: int` *(field)*
- `var pub pixels: int` *(field)*
- `var pub is_hdr: bool` *(field)*
- `var pub _lib: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn pixel_offset(x: int, y: int): int` *(method)*
- `pub fn byte_size(): int` *(method)*
- `pub fn is_valid(): bool` *(method)*
- `pub fn get(x: int, y: int): Pixel` *(method)*
- `pub fn set(x: int, y: int, px: Pixel): Image` *(method)*
- `pub fn set_rgba(x: int, y: int, r: int, g: int, b: int): Image` *(method)*
- `pub fn fill(color: Pixel): Image` *(method)*
- `pub fn fill_rgb(r: int, g: int, b: int): Image` *(method)*
- `pub fn fill_rgba(r: int, g: int, b: int, a: int): Image` *(method)*
- `pub fn clear(color: Pixel): Image` *(method)*
- `pub fn fill_rect(x: int, y: int, w: int, h: int, color: Pixel): Image` *(method)*
- `pub fn rect(x: int, y: int, w: int, h: int, color: Pixel): Image` *(method)*
- `pub fn line(x0: int, y0: int, x1: int, y1: int, color: Pixel): Image` *(method)*
- `pub fn blit(src: Image, dst_x: int, dst_y: int): Image` *(method)*
- `pub fn blend_blit(src: Image, dst_x: int, dst_y: int): Image` *(method)*
- `pub fn flip_v(): Image` *(method)*
- `pub fn flip_h(): Image` *(method)*
- `pub fn flip_vertical(): Image` *(method)*
- `pub fn flip_horizontal(): Image` *(method)*
- `pub fn clone(): Image?` *(method)*
- `pub fn resize(new_w: int, new_h: int): Image?` *(method)*
- `pub fn crop(x: int, y: int, w: int, h: int): Image?` *(method)*
- `pub fn rotate_90(): Image?` *(method)*
- `pub fn save(path: str): bool?` *(method)*
- `pub fn save_png(path: str): bool?` *(method)*
- `pub fn save_jpg(path: str): bool?` *(method)*
- `pub fn save_bmp(path: str): bool?` *(method)*
- `pub fn save_tga(path: str): bool?` *(method)*
- `pub fn release(): nil` *(method)*
- `pub fn free(): nil` *(method)*

---

### `load` <a id="load"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load(path: str): Image?
```

---

### `load_forced` <a id="load_forced"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_forced(path: str, channels: int): Image?
```

---

### `query` <a id="query"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn query(path: str): Info?
```

---

### `create` <a id="create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create(w: int, h: int, channels: int = ...): Image?
```

---

### `get_pixel` <a id="get_pixel"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_pixel(img: Image, x: int, y: int): Pixel
```

---

### `set_pixel` <a id="set_pixel"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_pixel(img: Image, x: int, y: int, r: int, g: int, b: int, a: int = ...): nil
```

---

### `free_image` <a id="free_image"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn free_image(img: Image): nil
```

---

### `free` <a id="free"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn free(img: Image): nil
```

---

### `destroy` <a id="destroy"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn destroy(img: Image): nil
```

---

### `clone` <a id="clone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clone(img: Image): Image?
```

---

### `resize` <a id="resize"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn resize(img: Image, new_width: int, new_height: int): Image?
```

---

### `crop` <a id="crop"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn crop(img: Image, x: int, y: int, width: int, height: int): Image?
```

---

### `flip_vertical` <a id="flip_vertical"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flip_vertical(img: Image): nil
```

---

### `flip_horizontal` <a id="flip_horizontal"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flip_horizontal(img: Image): nil
```

---

### `rotate_90` <a id="rotate_90"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rotate_90(img: Image): Image?
```

---

### `fill` <a id="fill"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fill(img: Image, r: int, g: int, b: int, a: int = ...): nil
```

---

### `fill_rect` <a id="fill_rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fill_rect(img: Image, x: int, y: int, w: int, h: int, color: Pixel): nil
```

---

### `draw_line` <a id="draw_line"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_line(img: Image, x0: int, y0: int, x1: int, y1: int, color: Pixel): nil
```

---

### `flip_v` <a id="flip_v"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flip_v(img: Image): nil
```

---

### `flip_h` <a id="flip_h"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flip_h(img: Image): nil
```

---

### `blit` <a id="blit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blit(dst: Image, src: Image, dst_x: int, dst_y: int): nil
```

---

### `blend_blit` <a id="blend_blit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blend_blit(dst: Image, src: Image, dst_x: int, dst_y: int): nil
```

---

### `save_png` <a id="save_png"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_png(img: Image, path: str): bool?
```

---

### `save_jpg` <a id="save_jpg"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_jpg(img: Image, path: str, quality: int = ...): bool?
```

---

### `save_bmp` <a id="save_bmp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_bmp(img: Image, path: str): bool?
```

---

### `save_tga` <a id="save_tga"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_tga(img: Image, path: str, rle: bool = ...): bool?
```

---

### `save` <a id="save"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save(img: Image, path: str, quality: int = ...): bool?
```

Unified save with format auto-detection by file extension

---

### `PngFacade` <a id="PngFacade"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PngFacade
```

#### Members

- `pub init()` *(constructor)*
- `pub fn save(img: Image, path: str): bool?` *(method)*
- `pub fn load(path: str): Image?` *(method)*
- `pub fn load_as(path: str, channels: int): Image?` *(method)*

---

### `JpgFacade` <a id="JpgFacade"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame JpgFacade
```

#### Members

- `pub init()` *(constructor)*
- `pub fn save(img: Image, path: str): bool?` *(method)*
- `pub fn load(path: str): Image?` *(method)*
- `pub fn load_as(path: str, channels: int): Image?` *(method)*

---

### `BmpFacade` <a id="BmpFacade"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BmpFacade
```

#### Members

- `pub init()` *(constructor)*
- `pub fn save(img: Image, path: str): bool?` *(method)*
- `pub fn load(path: str): Image?` *(method)*
- `pub fn load_as(path: str, channels: int): Image?` *(method)*

---

### `TgaFacade` <a id="TgaFacade"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TgaFacade
```

#### Members

- `pub init()` *(constructor)*
- `pub fn save(img: Image, path: str): bool?` *(method)*
- `pub fn save_rle(img: Image, path: str): bool?` *(method)*
- `pub fn load(path: str): Image?` *(method)*
- `pub fn load_as(path: str, channels: int): Image?` *(method)*

---

### `detect_system_font` <a id="detect_system_font"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn detect_system_font(preferred_name: str = ...): str
```

---

