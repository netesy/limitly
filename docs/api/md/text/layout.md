# API Documentation: `layout.lm`

## Overview

std/text/layout.lm
Text measurement and line wrapping for std.text.

Honesty note: widths are CODEPOINT counts times a per-glyph advance —
the same 8px/char heuristic std.ui uses until real font metrics
(std.font text_width) are wired through. Wide glyphs (CJK) and
proportional fonts will under/over-estimate; that is a documented v1
limit, not silent wrongness. Breaks prefer spaces, then hard-break.

## Symbols

- **Function**: [`char_count`](#char_count)
- **Function**: [`measure_width`](#measure_width)
- **Function**: [`wrap_text`](#wrap_text)
- **Function**: [`split_lines`](#split_lines)
- **Function**: [`wrap_paragraph`](#wrap_paragraph)
- **Function**: [`slice_cps`](#slice_cps)
- **Function**: [`wrap_width`](#wrap_width)

---

### `char_count` <a id="char_count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn char_count(text: str): int
```

Number of codepoints in a string (NOT bytes).

---

### `measure_width` <a id="measure_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn measure_width(text: str, char_w: float = ...): float
```

Estimated pixel width: codepoints * advance.

---

### `wrap_text` <a id="wrap_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn wrap_text(text: str, max_chars: int): list
```

Greedy word wrap. max_chars is in CODEPOINTS (consistent with
measure_width's units). Prefers breaking at the last space that fits;
hard-breaks overlong words. Empty input yields one empty line.

---

### `split_lines` <a id="split_lines"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn split_lines(text: str): list
```

---

### `wrap_paragraph` <a id="wrap_paragraph"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn wrap_paragraph(para: str, max_chars: int, out: list): nil
```

---

### `slice_cps` <a id="slice_cps"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn slice_cps(cps: list, lo: int, hi: int): list
```

---

### `wrap_width` <a id="wrap_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn wrap_width(text: str, max_px: float, char_w: float = ...): list
```

Wrap by pixel width: converts max_px to a codepoint budget using
char_w, then delegates to wrap_text.

---

