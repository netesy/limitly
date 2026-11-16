# API Documentation: `select.lm`

## Overview

std/ui/widgets/select.lm
Widget — ported from legacy Fluent Select (+ multi_select).
Closed: rounded box with selected label + chevron. Open: dropdown menu
painted below the box; menu item rects are cached in fields for
hit-testing (the menu may extend past the widget's arranged bounds —
on_event receives all pointer events, so manual hit-tests work).

## Symbols

- **Frame**: [`Select`](#Select)
- **Function**: [`select`](#select)
- **Function**: [`multi_select`](#multi_select)

---

### `Select` <a id="Select"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Select
```

#### Members

- `var pub options: list` *(field)*
- `var pub selected_idx: int` *(field)*
- `var pub selected_sig: state.IntSignal?` *(field)*
- `var pub is_open: int` *(field)*
- `var pub hovered: int` *(field)*
- `var pub hover_idx: int` *(field)*
- `var pub is_multi: int` *(field)*
- `var pub multi_sel: list` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub text2: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub box_h: float` *(field)*
- `var pub item_h: float` *(field)*
- `var pub _sx: float` *(field)*
- `var pub _sy: float` *(field)*
- `var pub _sw: float` *(field)*
- `var pub _sh: float` *(field)*
- `var pub _menu_y: float` *(field)*
- `var pub _mh: float` *(field)*
- `var pub _pal: uitheme.Palette?` *(field)*
- `var pub _shadow: shadow.Shadow?` *(field)*
- `pub init(opts: list)` *(constructor)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn bind_selected(sig: state.IntSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `fn selected_now(): int` *(method)*
- `fn set_selected(i: int): nil` *(method)*
- `fn set_open(v: int): nil` *(method)*
- `fn label_text(): str` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `fn layout_menu(): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `select` <a id="select"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn select(opts: list, idx: int = ...): Select
```

---

### `multi_select` <a id="multi_select"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn multi_select(opts: list, selected: list = ...): Select
```

---

