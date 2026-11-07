# API Documentation: `glyph.lm`

## Overview

std/font/glyph.lm
TrueType glyf contour extraction and quadratic Bézier curve flattening into line segments.

## Symbols

- **Frame**: [`Point`](#Point)
- **Frame**: [`LineSegment`](#LineSegment)
- **Frame**: [`GlyphOutline`](#GlyphOutline)
- **Function**: [`parse_glyph`](#parse_glyph)

---

### `Point` <a id="Point"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Point
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub on_curve: bool` *(field)*
- `pub init()` *(constructor)*

---

### `LineSegment` <a id="LineSegment"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LineSegment
```

#### Members

- `var pub x0: float` *(field)*
- `var pub y0: float` *(field)*
- `var pub x1: float` *(field)*
- `var pub y1: float` *(field)*
- `pub init()` *(constructor)*

---

### `GlyphOutline` <a id="GlyphOutline"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GlyphOutline
```

#### Members

- `var pub x_min: int` *(field)*
- `var pub y_min: int` *(field)*
- `var pub x_max: int` *(field)*
- `var pub y_max: int` *(field)*
- `var pub contours: list` *(field)*
- `var pub is_empty: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_scaled_segments(scale_x: float, scale_y: float): list` *(method)*

---

### `parse_glyph` <a id="parse_glyph"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_glyph(reader: r.ByteReader, info: t.Info, glyph_idx: int): GlyphOutline
```

---

