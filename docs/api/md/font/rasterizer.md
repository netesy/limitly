# API Documentation: `rasterizer.lm`

## Overview

std/font/rasterizer.lm
Subpixel supersampled scanline rasterizer for font glyphs.
Produces 8-bit alpha coverage bitmaps (0..255) using standard non-zero winding rule.

## Symbols

- **Frame**: [`GlyphBitmap`](#GlyphBitmap)
- **Frame**: [`Intersection`](#Intersection)
- **Function**: [`rasterize_glyph`](#rasterize_glyph)
- **Function**: [`rasterize_glyph_subpixel`](#rasterize_glyph_subpixel)
- **Function**: [`sqrt_approx`](#sqrt_approx)
- **Function**: [`dist_to_segment_squared`](#dist_to_segment_squared)
- **Function**: [`point_inside_outline`](#point_inside_outline)
- **Function**: [`rasterize_glyph_sdf`](#rasterize_glyph_sdf)

---

### `GlyphBitmap` <a id="GlyphBitmap"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GlyphBitmap
```

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub x_offset: int` *(field)*
- `var pub y_offset: int` *(field)*
- `var pub pixels: list` *(field)*
- `pub init()` *(constructor)*

---

### `Intersection` <a id="Intersection"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Intersection
```

#### Members

- `var pub x: float` *(field)*
- `var pub direction: int` *(field)*
- `pub init()` *(constructor)*

---

### `rasterize_glyph` <a id="rasterize_glyph"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rasterize_glyph(outline: g.GlyphOutline, scale: float): GlyphBitmap
```

---

### `rasterize_glyph_subpixel` <a id="rasterize_glyph_subpixel"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rasterize_glyph_subpixel(outline: g.GlyphOutline, scale: float, oversample_x: int = ..., oversample_y: int = ..., shift_x: float = ..., shift_y: float = ...): GlyphBitmap
```

---

### `sqrt_approx` <a id="sqrt_approx"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn sqrt_approx(x: float): float
```

Helper: Square root using Newton-Raphson approximation

---

### `dist_to_segment_squared` <a id="dist_to_segment_squared"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn dist_to_segment_squared(px: float, py: float, x1: float, y1: float, x2: float, y2: float): float
```

Helper: Calculate squared distance from point to line segment

---

### `point_inside_outline` <a id="point_inside_outline"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn point_inside_outline(px: float, py: float, segments: list): bool
```

Helper: Check if point is inside glyph using winding rule

---

### `rasterize_glyph_sdf` <a id="rasterize_glyph_sdf"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rasterize_glyph_sdf(outline: g.GlyphOutline, scale: float, padding: int = ..., onedge_value: float = ..., pixel_dist_scale: float = ...): GlyphBitmap
```

---

