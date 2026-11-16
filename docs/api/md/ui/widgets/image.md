# API Documentation: `image.lm`

## Overview

std/ui/widgets/image.lm
Widget — ported from legacy Fluent Image.
Placeholder-level parity with legacy: rounded surface + source label
centered. Real texture blit lands when the GPU/image path integrates.

## Symbols

- **Frame**: [`Image`](#Image)
- **Function**: [`image`](#image)

---

### `Image` <a id="Image"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Image
```

#### Members

- `var pub source: str` *(field)*
- `var pub texture_id: int` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub text2: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `image` <a id="image"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn image(src: str = ...): Image
```

---

