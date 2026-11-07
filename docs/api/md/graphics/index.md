# API Documentation: `index.lm`

## Overview

Re-exports all graphics primitives and types

## Symbols

- **Function**: [`rgb`](#rgb)
- **Function**: [`rgba`](#rgba)
- **Function**: [`lerp`](#lerp)
- **Function**: [`load_image`](#load_image)
- **Function**: [`save_image_png`](#save_image_png)
- **Function**: [`free_image`](#free_image)

---

### `rgb` <a id="rgb"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn rgb(r: int, g: int, b: int): Color
```

---

### `rgba` <a id="rgba"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn rgba(r: int, g: int, b: int, a: float): Color
```

---

### `lerp` <a id="lerp"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn lerp(c1: Color, c2: Color, t: float): Color
```

---

### `load_image` <a id="load_image"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn load_image(filename: str): Image
```

---

### `save_image_png` <a id="save_image_png"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn save_image_png(img: Image, filename: str): bool
```

---

### `free_image` <a id="free_image"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn free_image(img: Image): nil
```

---

