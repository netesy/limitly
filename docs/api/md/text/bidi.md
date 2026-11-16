# API Documentation: `bidi.lm`

## Overview

std/text/bidi.lm
Explicit Unicode Bidirectional Algorithm (UBA) support — a documented
subset, not silent LTR-everything.

What this implements (enough for real mixed-direction UI text):
  - Codepoint classification into UBA bidi classes (L, R, AL, EN, AN,
    ES, ET, CS, B, S, WS, ON, BN, NSM).
  - Paragraph direction from the first strong character (UBA P2/P3).
  - Implicit level resolution for strong types and the common weak
    rules (W5/W6/W7 subset): European/Arabic numbers keep their
    direction relative to AL text.
  - Reorder to visual order (UBA L2): reverse contiguous sequences
    level-by-level so an LTR renderer (sokol fontstash) draws the
    correct glyph sequence.

What this deliberately does NOT do (documented limits):
  - No explicit embedding/override controls parsed (LRE/RLE/PDF/LRO/
    RLO are stripped as BN); add them later if needed.
  - No bracket mirroring — paired punctuation keeps its logical glyph;
    correct mirroring needs font glyph substitution.
  - Neutrals between different-direction strongs resolve to paragraph
    direction (N1/N2), which is correct for the common cases.
  - No multi-paragraph handling — callers split on '\n' themselves.

## Symbols

- **Function**: [`bidi_class`](#bidi_class)
- **Function**: [`first_strong`](#first_strong)
- **Function**: [`levels`](#levels)
- **Function**: [`visual_text`](#visual_text)
- **Function**: [`is_rtl`](#is_rtl)

---

### `bidi_class` <a id="bidi_class"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn bidi_class(cp: int): int
```

Classify one codepoint into a bidi class. Ranges follow DerivedBidiClass.

---

### `first_strong` <a id="first_strong"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn first_strong(cps: list): int
```

First strong type wins the paragraph direction (UBA P2).

---

### `levels` <a id="levels"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn levels(text: str): list
```

Resolve implicit levels (UBA X10 + W5/W6/W7 subset).
Returns [int] of embedding levels, one per codepoint.

---

### `visual_text` <a id="visual_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn visual_text(text: str): str
```

Reorder codepoints into VISUAL order (UBA L2) for an LTR renderer.
Strips BN-class chars. Returns the display string.

---

### `is_rtl` <a id="is_rtl"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_rtl(text: str): bool
```

Paragraph direction for callers that need it: 0 = LTR, 1 = RTL.

---

