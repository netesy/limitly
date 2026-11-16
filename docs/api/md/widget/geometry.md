# API Documentation: `geometry.lm`

## Overview

std/widget/geometry.lm
Geometric primitives for UI, widgets, and layouts.

Canonical types live in their domain modules and are re-exported here:
  Rect    -> std.geometry.Rect
  Vector2 -> std.math.vector2.Vector2
Only Insets is widget-local.

## Symbols

- **Frame**: [`Insets`](#Insets)

---

### `Insets` <a id="Insets"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Insets
```

#### Members

- `var pub left: float` *(field)*
- `var pub top: float` *(field)*
- `var pub right: float` *(field)*
- `var pub bottom: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn horizontal(): float` *(method)*
- `pub fn vertical(): float` *(method)*

---

