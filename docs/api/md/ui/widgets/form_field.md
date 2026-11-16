# API Documentation: `form_field.lm`

## Overview

std/ui/widgets/form_field.lm
Widget — ported from legacy Fluent FormField.
Label above a child control, with optional help/error caption below.
error takes precedence over help when both are set.

## Symbols

- **Frame**: [`FormField`](#FormField)
- **Function**: [`form_field`](#form_field)

---

### `FormField` <a id="FormField"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FormField
```

#### Members

- `var pub label_text: str` *(field)*
- `var pub help_text: str` *(field)*
- `var pub error_text: str` *(field)*
- `var pub child: comp.Component?` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub text2: color.Color` *(field)*
- `var pub error_color: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub _ch: float` *(field)*
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
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `form_field` <a id="form_field"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn form_field(lbl: str, control: any = ..., help: str = ..., err_txt: str = ...): FormField
```

---

