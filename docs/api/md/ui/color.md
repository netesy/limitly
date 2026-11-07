# API Documentation: `color.lm`

## Overview

std/ui/color.lm
UI Color bridge delegating to canonical std.color.
NOTE: This module is deprecated. Import std.color directly instead.

## Symbols

- **Function**: [`rgb`](#rgb)
- **Function**: [`rgba`](#rgba)
- **Function**: [`color_rgb`](#color_rgb)
- **Function**: [`color_rgba`](#color_rgba)
- **Function**: [`color_rgb8`](#color_rgb8)
- **Function**: [`hex`](#hex)
- **Function**: [`hsl`](#hsl)

---

### `rgb` <a id="rgb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rgb(r: int, g: int, b: int): Color
```

Convenience functions delegating to std.color

---

### `rgba` <a id="rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rgba(r: int, g: int, b: int, a: float): Color
```

---

### `color_rgb` <a id="color_rgb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgb(r: float, g: float, b: float): Color
```

---

### `color_rgba` <a id="color_rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgba(r: float, g: float, b: float, a: float): Color
```

---

### `color_rgb8` <a id="color_rgb8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgb8(r: int, g: int, b: int): Color
```

---

### `hex` <a id="hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hex(h: int): Color
```

---

### `hsl` <a id="hsl"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hsl(h: float, s: float, l: float): Color
```

---

