# API Documentation: `overlay.lm`

## Overview

std/ui/containers/overlay.lm
Container — positions a single child at an absolute offset inside
(or outside) the component's own rect. Port of the legacy Fluent
`overlay` container. ow/oh <= 0 means "child's measured size".

## Symbols

- **Frame**: [`Overlay`](#Overlay)
- **Function**: [`overlay`](#overlay)

---

### `Overlay` <a id="Overlay"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Overlay
```

#### Members

- `var pub child: comp.Component?` *(field)*
- `var pub ox: float` *(field)*
- `var pub oy: float` *(field)*
- `var pub ow: float` *(field)*
- `var pub oh: float` *(field)*
- `var pub _cw: float` *(field)*
- `var pub _ch: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_child(c: comp.Component): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `fn child_w(): float` *(method)*
- `fn child_h(): float` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `overlay` <a id="overlay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn overlay(c: any = ..., x: float = ..., y: float = ..., w: float = ..., h: float = ...): Overlay
```

---

