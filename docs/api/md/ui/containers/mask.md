# API Documentation: `mask.lm`

## Overview

std/ui/containers/mask.lm
Container — clips its child via draw-list ClipPush/ClipPop
(gg.push_clip → scissor + shader coverage). shape names:
  "rect"      — plain rectangle (scissor only)
  "rounded"   — rounded rect, radius = min(w,h)*0.25 (default)
  "squircle"  — approximated as rounded rect, radius = min(w,h)*0.35
  "pill"      — stadium shape, radius = min(w,h)*0.5
  "circle"    — ellipse inscribed in the rect
Shaped clips apply to rect/triangle draws (surfaces, borders, lines,
charts); text keeps rectangular clipping — glyph quads near a shaped
edge can overdraw slightly outside the silhouette.

## Symbols

- **Frame**: [`Mask`](#Mask)
- **Function**: [`mask`](#mask)

---

### `Mask` <a id="Mask"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Mask
```

#### Members

- `var pub child: comp.Component?` *(field)*
- `var pub shape: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_child(c: comp.Component): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `fn clip_args(): any` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `mask` <a id="mask"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mask(c: any = ..., shape_name: str = ...): Mask
```

---

