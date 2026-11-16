# API Documentation: `button.lm`

## Overview

std/ui/widgets/button.lm
Widget — split from std/ui/widgets.lm.

## Symbols

- **Frame**: [`Button`](#Button)
- **Function**: [`button`](#button)

---

### `Button` <a id="Button"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Button
```

#### Members

- `var pub bg: color.Color` *(field)*
- `var pub bg_hover: color.Color` *(field)*
- `var pub bg_pressed: color.Color` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub pad_x: float` *(field)*
- `var pub pad_y: float` *(field)*
- `var pub on_click: function?` *(field)*
- `var pub pressed: int` *(field)*
- `var pub hovered: int` *(field)*
- `var pub _custom_bg: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `button` <a id="button"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn button(txt: str, c: color.Color? = ..., click: function? = ...): Button
```

---

