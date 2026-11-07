# API Documentation: `jpg.lm`

## Overview

std/image/jpg.lm
JPEG-specific load/save API.

## Symbols

- **Function**: [`load`](#load)
- **Function**: [`load_as`](#load_as)
- **Function**: [`save`](#save)
- **Function**: [`save_default`](#save_default)

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
pub fn save(img: image.Image, path: str, quality: int = ...): bool?
```

---

### `save_default` <a id="save_default"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_default(img: image.Image, path: str): bool?
```

---

