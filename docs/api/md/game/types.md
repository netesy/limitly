# API Documentation: `types.lm`

## Overview

std/game/types.lm
Fundamental math primitives, color definitions, and themes for std.game IMGUI

## Symbols

- **Frame**: [`Vec2`](#Vec2)
- **Function**: [`vec2`](#vec2)
- **Frame**: [`Rect`](#Rect)
- **Function**: [`rect`](#rect)
- **Function**: [`color_role_from_index`](#color_role_from_index)
- **Function**: [`style_var_from_index`](#style_var_from_index)
- **Frame**: [`GUITheme`](#GUITheme)
- **Function**: [`default_theme`](#default_theme)
- **Function**: [`dark_theme`](#dark_theme)
- **Function**: [`light_theme`](#light_theme)
- **Function**: [`cyberpunk_theme`](#cyberpunk_theme)
- **Function**: [`retro_theme`](#retro_theme)

---

### `Vec2` <a id="Vec2"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vec2
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(other: Vec2): Vec2` *(method)*
- `pub fn sub(other: Vec2): Vec2` *(method)*
- `pub fn scale(s: float): Vec2` *(method)*
- `pub fn mul(other: Vec2): Vec2` *(method)*
- `pub fn div(s: float): Vec2` *(method)*
- `pub fn dot(other: Vec2): float` *(method)*
- `pub fn cross(other: Vec2): float` *(method)*
- `pub fn mag_sq(): float` *(method)*
- `pub fn mag(): float` *(method)*
- `pub fn length(): float` *(method)*
- `pub fn length_sq(): float` *(method)*
- `pub fn normalize(): Vec2` *(method)*
- `pub fn dist_sq(other: Vec2): float` *(method)*
- `pub fn dist(other: Vec2): float` *(method)*
- `pub fn lerp(target: Vec2, t: float): Vec2` *(method)*
- `pub fn angle(): float` *(method)*
- `pub fn rotate(radians: float): Vec2` *(method)*
- `pub fn perpendicular(): Vec2` *(method)*
- `pub fn reflect(normal: Vec2): Vec2` *(method)*
- `pub fn clamp_length(max_len: float): Vec2` *(method)*

---

### `vec2` <a id="vec2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn vec2(x: float, y: float): Vec2
```

---

### `Rect` <a id="Rect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rect
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub w: float` *(field)*
- `var pub h: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn contains(px: float, py: float): bool` *(method)*
- `pub fn contains_vec(p: Vec2): bool` *(method)*
- `pub fn intersects(other: Rect): bool` *(method)*
- `pub fn intersection(other: Rect): Rect` *(method)*
- `pub fn union_rect(other: Rect): Rect` *(method)*
- `pub fn center(): Vec2` *(method)*
- `pub fn expand(amount: float): Rect` *(method)*
- `pub fn clamp_point(p: Vec2): Vec2` *(method)*

---

### `rect` <a id="rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rect(x: float, y: float, w: float, h: float): Rect
```

---

### `color_role_from_index` <a id="color_role_from_index"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn color_role_from_index(idx: int): ColorRole
```

---

### `style_var_from_index` <a id="style_var_from_index"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn style_var_from_index(idx: int): StyleVar
```

---

### `GUITheme` <a id="GUITheme"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GUITheme
```

#### Members

- `var pub bg_window: color.Color` *(field)*
- `var pub bg_window_title: color.Color` *(field)*
- `var pub bg_panel: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub text_muted: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub btn_normal: color.Color` *(field)*
- `var pub btn_hover: color.Color` *(field)*
- `var pub btn_active: color.Color` *(field)*
- `var pub slider_track: color.Color` *(field)*
- `var pub slider_thumb: color.Color` *(field)*
- `var pub slider_thumb_hover: color.Color` *(field)*
- `var pub checkbox_border: color.Color` *(field)*
- `var pub checkbox_check: color.Color` *(field)*
- `var pub separator: color.Color` *(field)*
- `var pub frame_bg: color.Color` *(field)*
- `var pub frame_bg_hover: color.Color` *(field)*
- `var pub frame_bg_active: color.Color` *(field)*
- `var pub tab_normal: color.Color` *(field)*
- `var pub tab_active: color.Color` *(field)*
- `var pub plot_lines: color.Color` *(field)*
- `var pub plot_histogram: color.Color` *(field)*
- `var pub padding: float` *(field)*
- `var pub spacing: float` *(field)*
- `var pub item_height: float` *(field)*
- `var pub rounding: float` *(field)*
- `var pub font_scale: int` *(field)*
- `var pub hover_duration: float` *(field)*
- `var pub press_duration: float` *(field)*
- `var pub enter_duration: float` *(field)*
- `var pub exit_duration: float` *(field)*
- `var pub button_shadow: Shadow?` *(field)*
- `var pub window_shadow: Shadow?` *(field)*
- `var pub popup_shadow: Shadow?` *(field)*
- `pub init()` *(constructor)*

---

### `default_theme` <a id="default_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn default_theme(): GUITheme
```

---

### `dark_theme` <a id="dark_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dark_theme(): GUITheme
```

---

### `light_theme` <a id="light_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn light_theme(): GUITheme
```

---

### `cyberpunk_theme` <a id="cyberpunk_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cyberpunk_theme(): GUITheme
```

---

### `retro_theme` <a id="retro_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn retro_theme(): GUITheme
```

---

