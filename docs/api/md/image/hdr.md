# API Documentation: `hdr.lm`

## Overview

std/image/hdr.lm
HDR (Radiance RGBE) image API — float pixel buffers.

## Symbols

- **Frame**: [`HdrImage`](#HdrImage)
- **Function**: [`load`](#load)
- **Function**: [`save`](#save)
- **Function**: [`free`](#free)
- **Function**: [`to_ldr`](#to_ldr)
- **Function**: [`get_pixel_hdr`](#get_pixel_hdr)

---

### `HdrImage` <a id="HdrImage"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HdrImage
```

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub channels: int` *(field)*
- `var pub pixels: int` *(field)*
- `var pub _lib: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn float_count(): int` *(method)*
- `pub fn pixel_byte_offset(x: int, y: int): int` *(method)*
- `pub fn is_valid(): bool` *(method)*

---

### `load` <a id="load"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load(path: str): HdrImage?
```

---

### `save` <a id="save"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save(img: HdrImage, path: str): bool?
```

---

### `free` <a id="free"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn free(img: HdrImage): nil
```

---

### `to_ldr` <a id="to_ldr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_ldr(img: HdrImage, exposure: float = ...): image.Image?
```

Reinhard tone-map + sRGB gamma encode -> standard u8 Image.

---

### `get_pixel_hdr` <a id="get_pixel_hdr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_pixel_hdr(img: HdrImage, x: int, y: int): tuple
```

---

