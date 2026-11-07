# API Documentation: `shadow.lm`

## Overview

std/graphics/shadow.lm
Shared First-Class Shadow Abstraction for Lymar Graphics, UI, and Game GUI

## Symbols

- **Frame**: [`Shadow`](#Shadow)
- **Function**: [`shadow`](#shadow)
- **Function**: [`lerp_float`](#lerp_float)
- **Function**: [`lerp_shadow`](#lerp_shadow)

---

### `Shadow` <a id="Shadow"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Shadow
```

#### Members

- `var pub r: float` *(field)*
- `var pub g: float` *(field)*
- `var pub b: float` *(field)*
- `var pub a: float` *(field)*
- `var pub offset_x: float` *(field)*
- `var pub offset_y: float` *(field)*
- `var pub blur_radius: float` *(field)*
- `var pub spread_radius: float` *(field)*
- `pub init()` *(constructor)*

---

### `shadow` <a id="shadow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn shadow(r: float = ..., g: float = ..., b: float = ..., a: float = ..., off_x: float = ..., off_y: float = ..., blur: float = ..., spread: float = ...): Shadow
```

---

### `lerp_float` <a id="lerp_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lerp_float(a: float, b: float, t: float): float
```

---

### `lerp_shadow` <a id="lerp_shadow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lerp_shadow(s1: Shadow, s2: Shadow, t: float): Shadow
```

---

