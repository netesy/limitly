# API Documentation: `index.lm`

## Overview

Standard Library Color Module

Canonical Color frame, RGBA / Hex / HSL constructors, linear interpolation, and Tailwind-inspired shade palettes.

## Symbols

- **Frame**: [`Color`](#Color)
- **Function**: [`hex_digit`](#hex_digit)
- **Function**: [`hex_byte`](#hex_byte)
- **Function**: [`rgb`](#rgb)
- **Function**: [`rgba`](#rgba)
- **Function**: [`hex`](#hex)
- **Function**: [`color_rgb`](#color_rgb)
- **Function**: [`color_rgba`](#color_rgba)
- **Function**: [`hue_to_rgb`](#hue_to_rgb)
- **Function**: [`hsl`](#hsl)
- **Function**: [`lerp`](#lerp)

---

### `Color` <a id="Color"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Color
```

Canonical 4-channel RGBA floating-point color representation (0.0 to 1.0).

#### Example: Idiomatic Usage

```lymar
var c = Color(1.0, 0.5, 0.0, 1.0);
var hex_code = c.to_hex();
```

#### Members

- `var pub r: float` *(field)*
- `var pub g: float` *(field)*
- `var pub b: float` *(field)*
- `var pub a: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn to_hex(): str` *(method)*
- `pub fn with_alpha(new_a: float): Color` *(method)*

---

### `hex_digit` <a id="hex_digit"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hex_digit(v: int): str
```

---

### `hex_byte` <a id="hex_byte"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hex_byte(v: int): str
```

---

### `rgb` <a id="rgb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rgb(r: int, g: int, b: int): Color
```

Constructs a color from integer byte components [0, 255].

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `r` | Red value in range 0-255. |
| `g` | Green value in range 0-255. |
| `b` | Blue value in range 0-255. |

#### Returns

Full opacity Color instance.

---

### `rgba` <a id="rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rgba(r: int, g: int, b: int, a: float): Color
```

Constructs a color from integer byte components [0, 255] and float alpha [0.0, 1.0].

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `r` | Red value in range 0-255. |
| `g` | Green value in range 0-255. |
| `b` | Blue value in range 0-255. |
| `a` | Opacity in range 0.0-1.0. |

#### Returns

Color instance.

---

### `hex` <a id="hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hex(c: int, a: float = ...): Color
```

Constructs a color from a 24-bit integer hex code (e.g. `0xff55aa`).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `c` | 24-bit RGB integer literal (0x000000 - 0xffffff). |
| `a` | Optional alpha opacity between 0.0 and 1.0. |

#### Returns

Color instance.

---

### `color_rgb` <a id="color_rgb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgb(r: float, g: float, b: float): Color
```

Constructs a color from normalized float components [0.0, 1.0] with full opacity.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `r` | Red value in range 0.0-1.0. |
| `g` | Green value in range 0.0-1.0. |
| `b` | Blue value in range 0.0-1.0. |

#### Returns

Full opacity Color instance.

---

### `color_rgba` <a id="color_rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_rgba(r: float, g: float, b: float, a: float): Color
```

Constructs a color from normalized float components [0.0, 1.0] and alpha opacity.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `r` | Red value in range 0.0-1.0. |
| `g` | Green value in range 0.0-1.0. |
| `b` | Blue value in range 0.0-1.0. |
| `a` | Alpha opacity in range 0.0-1.0. |

#### Returns

Color instance.

---

### `hue_to_rgb` <a id="hue_to_rgb"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hue_to_rgb(p: float, q: float, t: float): float
```

---

### `hsl` <a id="hsl"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hsl(h: float, s: float, l: float): Color
```

Constructs a color from Hue, Saturation, and Lightness values.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `h` | Hue angle in degrees (0.0 to 360.0). |
| `s` | Saturation percentage (0.0 to 1.0). |
| `l` | Lightness percentage (0.0 to 1.0). |

#### Returns

Color representation in RGBA.

---

### `lerp` <a id="lerp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lerp(c1: Color, c2: Color, t: float): Color
```

Linearly interpolates between two colors.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `c1` | Starting color at t = 0.0. |
| `c2` | Ending color at t = 1.0. |
| `t` | Interpolation progress (0.0 to 1.0). |

#### Returns

Blended intermediate Color.

---

