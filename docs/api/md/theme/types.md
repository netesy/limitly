# API Documentation: `types.lm`

## Overview

std/theme/types.lm
Universal Design Tokens and Theme specifications for Limitless / Lymar.

## Symbols

- **Function**: [`color_role_from_index`](#color_role_from_index)
- **Function**: [`style_var_from_index`](#style_var_from_index)
- **Frame**: [`SpacingTokens`](#SpacingTokens)
- **Frame**: [`TypographyTokens`](#TypographyTokens)
- **Frame**: [`ShapeTokens`](#ShapeTokens)
- **Frame**: [`Theme`](#Theme)

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

### `SpacingTokens` <a id="SpacingTokens"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SpacingTokens
```

#### Members

- `var pub xs: float` *(field)*
- `var pub sm: float` *(field)*
- `var pub md: float` *(field)*
- `var pub lg: float` *(field)*
- `var pub xl: float` *(field)*
- `pub init()` *(constructor)*

---

### `TypographyTokens` <a id="TypographyTokens"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TypographyTokens
```

#### Members

- `var pub font_family: str` *(field)*
- `var pub display_size: float` *(field)*
- `var pub headline_size: float` *(field)*
- `var pub title_size: float` *(field)*
- `var pub body_size: float` *(field)*
- `var pub label_size: float` *(field)*
- `pub init()` *(constructor)*

---

### `ShapeTokens` <a id="ShapeTokens"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ShapeTokens
```

#### Members

- `var pub corner_xs: float` *(field)*
- `var pub corner_sm: float` *(field)*
- `var pub corner_md: float` *(field)*
- `var pub corner_lg: float` *(field)*
- `pub init()` *(constructor)*

---

### `Theme` <a id="Theme"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Theme
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
- `var pub success: color.Color` *(field)*
- `var pub warning: color.Color` *(field)*
- `var pub danger: color.Color` *(field)*
- `var pub info: color.Color` *(field)*
- `var pub padding: float` *(field)*
- `var pub spacing: float` *(field)*
- `var pub item_height: float` *(field)*
- `var pub rounding: float` *(field)*
- `var pub font_scale: int` *(field)*
- `var pub hover_duration: float` *(field)*
- `var pub press_duration: float` *(field)*
- `var pub enter_duration: float` *(field)*
- `var pub exit_duration: float` *(field)*
- `var pub button_shadow: shadow.Shadow?` *(field)*
- `var pub window_shadow: shadow.Shadow?` *(field)*
- `var pub popup_shadow: shadow.Shadow?` *(field)*
- `var pub spacing_tokens: SpacingTokens` *(field)*
- `var pub typography_tokens: TypographyTokens` *(field)*
- `var pub shape_tokens: ShapeTokens` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_color(role: ColorRole): color.Color` *(method)*
- `pub fn set_color(role: ColorRole, c: color.Color): nil` *(method)*

---

