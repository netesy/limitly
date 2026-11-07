# API Documentation: `bmp.lm`

## Overview

std/image/bmp.lm
BMP-specific load/save API.

## Symbols

- **Function**: [`load`](#load)
- **Function**: [`load_as`](#load_as)
- **Function**: [`save`](#save)

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

