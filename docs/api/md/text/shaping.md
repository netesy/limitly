# API Documentation: `shaping.lm`

## Overview

std/text/shaping.lm
Explicit text shaping — a documented subset, applied to the LOGICAL
string before bidi.visual_text() reorders it for display.

Implemented:
  - Arabic lam-alef MANDATORY ligatures (U+FEF5..U+FEFC). These are
    required by Arabic typography — lam followed by any alef variant
    must ligate or the text is wrong.
  - Hebrew final forms (sofit): kaf/mem/nun/pe/tsadi take their final
    glyph at word end.

Deliberately NOT implemented (documented limits):
  - Arabic contextual letter forms (isolated/initial/medial/final per
    joining type). The joining-type engine is here
    (joining_type/neighbors) but the per-letter presentation-form
    table is intentionally partial — see arabic_form() — because a
    wrong table entry renders wrong glyphs silently. Extend the table
    from UnicodeData.txt names ("ARABIC LETTER X INITIAL FORM").
  - No mark positioning, no ligatures beyond lam-alef, no GSUB/GPOS.
  - Whether the loaded font HAS the presentation-form glyphs is a font
    property; fons renders whatever the cmap provides.

## Symbols

- **Function**: [`lam_alef_ligature`](#lam_alef_ligature)
- **Function**: [`hebrew_final`](#hebrew_final)
- **Function**: [`is_hebrew_letter`](#is_hebrew_letter)
- **Function**: [`shape`](#shape)
- **Function**: [`prepare_display`](#prepare_display)

---

### `lam_alef_ligature` <a id="lam_alef_ligature"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn lam_alef_ligature(lam_next: int): int
```

Arabic presentation-form ligatures for LAM + alef variants.
Returns the ligature codepoint, or -1 when the pair doesn't ligate.

---

### `hebrew_final` <a id="hebrew_final"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hebrew_final(cp: int): int
```

Hebrew sofit (final) forms: base -> final. Applied at word end.

---

### `is_hebrew_letter` <a id="is_hebrew_letter"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_hebrew_letter(cp: int): bool
```

Is this codepoint a Hebrew letter (so sofit context applies)?

---

### `shape` <a id="shape"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn shape(text: str): str
```

Shape a logical string: mandatory ligatures + final forms.
Returns a NEW string; the input is untouched (strings immutable).

---

### `prepare_display` <a id="prepare_display"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn prepare_display(text: str): str
```

Full display pipeline: shape (logical) THEN bidi visual reorder.
This is what widgets should emit for painting.
Fast path: pure-ASCII text cannot contain RTL codepoints, presentation
forms, or marks, so it returns unchanged with a single byte scan —
no decode/encode allocations on the hot path.

---

