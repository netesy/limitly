# API Documentation: `accordion.lm`

## Overview

std/ui/widgets/accordion.lm
Widget — ported from legacy Fluent Accordion.
Header bar that toggles its child open/closed on click. Open state is a
plain int field (0/1) plus an optional BoolSignal for external binding.

## Symbols

- **Frame**: [`Accordion`](#Accordion)
- **Function**: [`accordion`](#accordion)

---

### `Accordion` <a id="Accordion"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Accordion
```

#### Members

- `var pub title: str` *(field)*
- `var pub child: comp.Component?` *(field)*
- `var pub is_open: int` *(field)*
- `var pub open_sig: state.BoolSignal?` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub header_h: float` *(field)*
- `var pub pad: float` *(field)*
- `var pub _ch: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_child(c: comp.Component): nil` *(method)*
- `pub fn bind_open(sig: state.BoolSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `fn open_now(): int` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `accordion` <a id="accordion"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn accordion(t: str, content: any = ..., default_open: bool = ...): Accordion
```

---

