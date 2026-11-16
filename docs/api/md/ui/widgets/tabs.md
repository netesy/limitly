# API Documentation: `tabs.lm`

## Overview

std/ui/widgets/tabs.lm
Widget — ported from legacy Fluent Tabs.
Tab header strip + one visible page ([comp.Component] per tab). Click a
tab header to switch; active index lives in an IntSignal (bind_active)
or the plain active_tab field.

## Symbols

- **Frame**: [`Tabs`](#Tabs)
- **Function**: [`tabs`](#tabs)

---

### `Tabs` <a id="Tabs"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Tabs
```

#### Members

- `var pub tab_titles: list` *(field)*
- `var pub pages: list` *(field)*
- `var pub active_tab: int` *(field)*
- `var pub active_sig: state.IntSignal?` *(field)*
- `var pub spacing: float` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub text2: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub header_h: float` *(field)*
- `var pub _tx: float` *(field)*
- `var pub _tw: float` *(field)*
- `pub init(titles: list, page_list: list)` *(constructor)*
- `pub fn bind_active(sig: state.IntSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `fn active_now(): int` *(method)*
- `pub fn add_page(title: str, page: any): nil` *(method)*
- `fn tab_rect(i: int): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `tabs` <a id="tabs"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tabs(titles: list, page_list: list, active: int = ...): Tabs
```

---

