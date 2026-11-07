# API Documentation: `viewport.lm`

## Overview

── Viewport & MediaQuery ─────────────────────────────────────────────────────

## Symbols

- **Frame**: [`Viewport`](#Viewport)
- **Frame**: [`MediaQuery`](#MediaQuery)

---

### `Viewport` <a id="Viewport"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Viewport
```

── Viewport & MediaQuery ─────────────────────────────────────────────────────

#### Members

- `var pub width: float` *(field)*
- `var pub height: float` *(field)*
- `var pub content_w: float` *(field)*
- `var pub content_h: float` *(field)*
- `var pub scroll_x: float` *(field)*
- `var pub scroll_y: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn max_scroll_x(): float` *(method)*
- `pub fn max_scroll_y(): float` *(method)*
- `pub fn clamp_scroll()` *(method)*
- `pub fn ensure_visible(item_x: float, item_y: float, item_w: float, item_h: float)` *(method)*

---

### `MediaQuery` <a id="MediaQuery"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame MediaQuery
```

#### Members

- `pub fn is_mobile(): bool` *(method)*
- `pub fn is_tablet(): bool` *(method)*
- `pub fn is_desktop(): bool` *(method)*

---

