# API Documentation: `index.lm`

## Overview

std/font/index.lm
TrueType & OpenType Font Loading, Typography Metrics, and Antialiased Text Rasterization.

## Symbols

- **Frame**: [`Metrics`](#Metrics)
- **Frame**: [`TypoMetrics`](#TypoMetrics)
- **Frame**: [`GlyphMetrics`](#GlyphMetrics)
- **Frame**: [`Font`](#Font)
- **Function**: [`load_font_from_bytes`](#load_font_from_bytes)
- **Function**: [`get_num_fonts_from_bytes`](#get_num_fonts_from_bytes)
- **Function**: [`load_font`](#load_font)
- **Function**: [`get_num_fonts`](#get_num_fonts)

---

### `Metrics` <a id="Metrics"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Metrics
```

#### Members

- `var pub ascent: float` *(field)*
- `var pub descent: float` *(field)*
- `var pub line_gap: float` *(field)*
- `var pub line_height: float` *(field)*
- `var pub units_per_em: int` *(field)*
- `pub init()` *(constructor)*

---

### `TypoMetrics` <a id="TypoMetrics"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TypoMetrics
```

#### Members

- `var pub ascent: float` *(field)*
- `var pub descent: float` *(field)*
- `var pub line_gap: float` *(field)*
- `var pub line_height: float` *(field)*
- `pub init()` *(constructor)*

---

### `GlyphMetrics` <a id="GlyphMetrics"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GlyphMetrics
```

#### Members

- `var pub glyph_index: int` *(field)*
- `var pub advance_width: float` *(field)*
- `var pub left_side_bearing: float` *(field)*
- `var pub width: float` *(field)*
- `var pub height: float` *(field)*
- `pub init()` *(constructor)*

---

### `Font` <a id="Font"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Font
```

#### Members

- `var pub path: str` *(field)*
- `var pub is_valid: bool` *(field)*
- `var pub info: t.Info` *(field)*
- `var pub reader: r.ByteReader` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_metrics(): Metrics` *(method)*
- `pub fn get_glyph_index(codepoint: int): int` *(method)*
- `pub fn get_glyph_metrics(glyph_idx: int): GlyphMetrics` *(method)*
- `pub fn get_kern_advance(glyph1: int, glyph2: int): float` *(method)*
- `pub fn get_kern_advance_codepoint(ch1: int, ch2: int): float` *(method)*
- `pub fn get_typo_metrics(): TypoMetrics` *(method)*
- `pub fn text_width(text: str): float` *(method)*
- `pub fn text_height(text: str): float` *(method)*
- `pub fn render_glyph(glyph_idx: int): rast.GlyphBitmap` *(method)*
- `pub fn render_glyph_subpixel(glyph_idx: int): rast.GlyphBitmap` *(method)*
- `pub fn render_glyph_sdf(glyph_idx: int): rast.GlyphBitmap` *(method)*

---

### `load_font_from_bytes` <a id="load_font_from_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_font_from_bytes(bytes: list, filepath: str = ..., font_index: int = ...): Font?
```

---

### `get_num_fonts_from_bytes` <a id="get_num_fonts_from_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_num_fonts_from_bytes(bytes: list): int
```

---

### `load_font` <a id="load_font"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_font(filepath: str, font_index: int = ...): Font?
```

---

### `get_num_fonts` <a id="get_num_fonts"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_num_fonts(filepath: str): int
```

---

