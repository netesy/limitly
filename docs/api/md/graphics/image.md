# API Documentation: `image.lm`

## Overview

Portable Image representation for std.graphics

## Symbols

- **Frame**: [`Image`](#Image)
- **Function**: [`load`](#load)
- **Function**: [`save_png`](#save_png)
- **Function**: [`free`](#free)

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
- `var pub lib_handle: int` *(field)*
- `pub init()` *(constructor)*

---

### `load` <a id="load"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load(filename: str): Image
```

---

### `save_png` <a id="save_png"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn save_png(img: Image, filename: str): bool
```

---

### `free` <a id="free"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn free(img: Image): nil
```

---

