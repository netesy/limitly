# API Documentation: `text_metrics.lm`

## Overview

std/ui/text_metrics.lm
Font metric provider for the retained UI — pixel-parity with the
renderer when a graphics context exists, real advances otherwise.

Parity chain (first hit wins):
  1. gg.measure_text / gg.get_line_height — the RENDERER's own
     metrics context: same embedded font, same gfx_font_size_for_scale
     size mapping the draw path uses. Pixel-exact.
  2. std.image.font system font at the renderer-mapped pixel size —
     real advances, possibly a different typeface than the embedded
     font (advances can differ slightly).
  3. Heuristic: FALLBACK_CHAR_W per codepoint — headless/no-font.

font_scale maps to renderer scale EXACTLY like replay():
  font_scale < 1.5 -> scale 1 (13px), >= 1.5 -> scale 2 (20px).

Callers must pass the DISPLAY string (textshape.prepare_display).
Results are cached per "text#scale_milli" — each uncached query is an
FFI call, which would break the per-frame zero-alloc budget (M5).

## Symbols

- **Function**: [`render_scale`](#render_scale)
- **Function**: [`render_px`](#render_px)
- **Function**: [`ensure_font`](#ensure_font)
- **Function**: [`using_renderer_metrics`](#using_renderer_metrics)
- **Function**: [`using_real_font`](#using_real_font)
- **Function**: [`text_width`](#text_width)
- **Function**: [`line_height`](#line_height)

---

### `render_scale` <a id="render_scale"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn render_scale(font_scale: float): int
```

Map widget font_scale to the renderer's integer scale, mirroring
std/ui/replay.lm: scale_i = font_scale >= 1.5 ? 2 : 1.

---

### `render_px` <a id="render_px"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn render_px(font_scale: float): float
```

Pixel size the renderer will use for a widget font_scale.
Mirrors gfx_font_size_for_scale for the two scales replay emits.

---

### `ensure_font` <a id="ensure_font"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_font(): int
```

---

### `using_renderer_metrics` <a id="using_renderer_metrics"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn using_renderer_metrics(): bool
```

Whether the live-graphics-context (pixel-exact) path is active.

---

### `using_real_font` <a id="using_real_font"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn using_real_font(): bool
```

Whether a fallback real font is loaded (diagnostics).

---

### `text_width` <a id="text_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn text_width(text: str, font_scale: float = ...): float
```

Advance width of a display string at the given font_scale.

---

### `line_height` <a id="line_height"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn line_height(font_scale: float = ...): float
```

Line height for single-line widgets at the given font_scale.

---

