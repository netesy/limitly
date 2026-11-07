# API Documentation: `tga.lm`

## Overview

std/image/tga.lm
TGA-specific load/save API (supports RLE compression).

## Symbols

- **Function**: [`load`](#load)
- **Function**: [`load_as`](#load_as)
- **Function**: [`save`](#save)
- **Function**: [`save_rle`](#save_rle)

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

### `save_rle` <a id="save_rle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_rle(img: image.Image, path: str): bool?
```

---

