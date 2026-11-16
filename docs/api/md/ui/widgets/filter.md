# API Documentation: `filter.lm`

## Overview

std/ui/widgets/filter.lm
Widget — ported from legacy Fluent Filter.
Single-line query box backed by EditorController + StrSignal, same
editing model as TextInput (cursor keys, backspace, char insert,
single focus owner via tree.set_focus).

## Symbols

- **Frame**: [`Filter`](#Filter)
- **Function**: [`filter`](#filter)

---

### `Filter` <a id="Filter"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Filter
```

#### Members

- `var pub ctrl: text_ctrl.EditorController` *(field)*
- `var pub query_sig: state.StrSignal` *(field)*
- `var pub placeholder: str` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub pad_x: float` *(field)*
- `var pub pad_y: float` *(field)*
- `var pub focused: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn bind_query(sig: state.StrSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `fn sync_sig(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `filter` <a id="filter"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn filter(q: str = ..., hint: str = ...): Filter
```

---

