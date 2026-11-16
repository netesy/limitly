# API Documentation: `theme.lm`

## Overview

std/ui/theme.lm
Theming layer for the Component UI, backed by the canonical
std.theme.types.Theme (the same type the presets produce).

  import std.ui.theme as uitheme;
  val pal = uitheme.palette();          // init-time snapshot
  self.surface = pal.surface;

Live re-theming:
  uitheme.set_dark();                    // swap preset + bump version
  tree.apply_theme(root);                // walk tree, refresh widgets

Widgets snapshot palette() in init and may implement
on_theme_changed() to re-snapshot; tree.apply_theme drives that.
Per-instance fields remain overridable — the palette only supplies
defaults.

## Symbols

- **Frame**: [`Palette`](#Palette)
- **Function**: [`palette`](#palette)
- **Function**: [`set_theme`](#set_theme)
- **Function**: [`set_default`](#set_default)
- **Function**: [`set_dark`](#set_dark)
- **Function**: [`set_light`](#set_light)
- **Function**: [`set_cyberpunk`](#set_cyberpunk)
- **Function**: [`set_retro`](#set_retro)
- **Function**: [`set_nord`](#set_nord)
- **Function**: [`elevation_shadow`](#elevation_shadow)

---

### `Palette` <a id="Palette"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Palette
```

#### Members

- `var pub background: color.Color` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub surface_variant: color.Color` *(field)*
- `var pub surface_hover: color.Color` *(field)*
- `var pub surface_pressed: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text_primary: color.Color` *(field)*
- `var pub text_muted: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub primary: color.Color` *(field)*
- `var pub secondary: color.Color` *(field)*
- `var pub focus_ring: color.Color` *(field)*
- `var pub btn_normal: color.Color` *(field)*
- `var pub btn_hover: color.Color` *(field)*
- `var pub btn_active: color.Color` *(field)*
- `var pub tab_active: color.Color` *(field)*
- `var pub thumb: color.Color` *(field)*
- `var pub thumb_hover: color.Color` *(field)*
- `var pub check: color.Color` *(field)*
- `var pub track: color.Color` *(field)*
- `var pub on_accent: color.Color` *(field)*
- `var pub accent_hover: color.Color` *(field)*
- `var pub selection: color.Color` *(field)*
- `var pub text_disabled: color.Color` *(field)*
- `var pub success: color.Color` *(field)*
- `var pub warning: color.Color` *(field)*
- `var pub error: color.Color` *(field)*
- `var pub info: color.Color` *(field)*
- `var pub plot_lines: color.Color` *(field)*
- `var pub plot_histogram: color.Color` *(field)*
- `var pub spacing: float` *(field)*
- `var pub item_height: float` *(field)*
- `var pub rounding: float` *(field)*
- `var pub corner_sm: float` *(field)*
- `var pub corner_md: float` *(field)*
- `var pub corner_lg: float` *(field)*
- `var pub body_size: float` *(field)*
- `var pub label_size: float` *(field)*
- `var pub button_shadow: shadow.Shadow?` *(field)*
- `var pub window_shadow: shadow.Shadow?` *(field)*
- `var pub popup_shadow: shadow.Shadow?` *(field)*

---

### `palette` <a id="palette"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn palette(): Palette
```

Snapshot the active theme into a UI palette. Called per-widget init
and per on_theme_changed — allocation happens only at those times,
never per-frame.

---

### `set_theme` <a id="set_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_theme(t: tt.Theme): nil
```

---

### `set_default` <a id="set_default"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_default(): nil
```

---

### `set_dark` <a id="set_dark"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_dark(): nil
```

---

### `set_light` <a id="set_light"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_light(): nil
```

---

### `set_cyberpunk` <a id="set_cyberpunk"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_cyberpunk(): nil
```

---

### `set_retro` <a id="set_retro"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_retro(): nil
```

---

### `set_nord` <a id="set_nord"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_nord(): nil
```

---

### `elevation_shadow` <a id="elevation_shadow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn elevation_shadow(pal: Palette, elev: int): shadow.Shadow?
```

Re-snapshot palette defaults on a widget after a theme swap. Widgets
call this from on_theme_changed(); fields the user overrode keep their
values only if the widget chose to preserve them — the convention is
that on_theme_changed re-applies theme-derived fields.

---

