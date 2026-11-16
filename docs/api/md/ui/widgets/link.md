# API Documentation: `link.lm`

## Overview

std/ui/widgets/link.lm
Widget — ported from legacy Fluent Link (std/ui/components.lm).
Clickable accent-colored text. `url` is metadata only (no browser
integration); clicks fire the optional callback.

## Symbols

- **Frame**: [`Link`](#Link)
- **Function**: [`link`](#link)

---

### `Link` <a id="Link"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Link
```

#### Members

- `var pub url: str` *(field)*
- `var pub click: function?` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub hovered: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `link` <a id="link"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn link(txt: str, target_url: str = ..., on_click: function? = ...): Link
```

---

