# API Documentation: `png.lm`

## Overview

std/image/png.lm
PNG-specific load/save API.

## Symbols

- **Function**: [`load`](#load)
- **Function**: [`load_as`](#load_as)
- **Function**: [`save`](#save)
- **Function**: [`save_with_stride`](#save_with_stride)

---

### `load` <a id="load"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load(path: str): image.Image?
```

---

### `load_as` <a id="load_as"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_as(path: str, channels: int): image.Image?
```

---

### `save` <a id="save"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save(img: image.Image, path: str): bool?
```

---

### `save_with_stride` <a id="save_with_stride"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_with_stride(img: image.Image, path: str, stride: int): bool?
```

---

