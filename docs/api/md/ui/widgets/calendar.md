# API Documentation: `calendar.lm`

## Overview

std/ui/widgets/calendar.lm
Widget — month-grid calendar with day picking. Parses "YYYY-MM-DD",
renders a weekday header + 6x7 day grid, highlights the selected day,
and fires on_select with the newly picked date. "<" / ">" in the header
navigate months.

## Symbols

- **Function**: [`pad2`](#pad2)
- **Function**: [`days_in_month`](#days_in_month)
- **Function**: [`day_of_week`](#day_of_week)
- **Frame**: [`Calendar`](#Calendar)
- **Function**: [`calendar`](#calendar)

---

### `pad2` <a id="pad2"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn pad2(n: int): str
```

---

### `days_in_month` <a id="days_in_month"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn days_in_month(y: int, m: int): int
```

---

### `day_of_week` <a id="day_of_week"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn day_of_week(y: int, m: int, d: int): int
```

Sakamoto day-of-week: 0 = Sunday.

---

### `Calendar` <a id="Calendar"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Calendar
```

#### Members

- `var pub selected_date: str` *(field)*
- `var pub selected_day: int` *(field)*
- `var pub year: int` *(field)*
- `var pub month: int` *(field)*
- `var pub on_select: function?` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub muted: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub on_accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub _cell: float` *(field)*
- `var pub _grid_x: float` *(field)*
- `var pub _grid_y: float` *(field)*
- `var pub _head_h: float` *(field)*
- `var pub _popup: int` *(field)*
- `var pub _pop_x: float` *(field)*
- `var pub _pop_y: float` *(field)*
- `var pub _pop_w: float` *(field)*
- `var pub _pop_h: float` *(field)*
- `var pub _item_h: float` *(field)*
- `var pub _year_base: int` *(field)*
- `var pub _title_x: float` *(field)*
- `var pub _month_w: float` *(field)*
- `var pub _year_w: float` *(field)*
- `var pub _shadow: shadow.Shadow?` *(field)*
- `pub init()` *(constructor)*
- `pub fn parse_date(ds: str): nil` *(method)*
- `pub fn set_date(ds: str): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `fn cell_size(): float` *(method)*
- `fn grid_rows(): int` *(method)*
- `fn layout_grid(): nil` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `fn shift_month(delta: int): nil` *(method)*
- `fn shift_year(delta: int): nil` *(method)*
- `fn title_metrics(): nil` *(method)*
- `fn set_popup(v: int): nil` *(method)*
- `fn popup_layout(): nil` *(method)*
- `fn in_popup(fx: float, fy: float): bool` *(method)*
- `fn pick_day(d: int): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `calendar` <a id="calendar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn calendar(date_str: str = ..., on_pick: function? = ...): Calendar
```

---

