# API Documentation: `container.lm`

## Overview

std/ui/container.lm
M2 layout containers: Flow (row/column), Container (padded box), ScrollView.

All children are [Component] trait objects. measure asks each child for
its intrinsic size under loose constraints; arrange distributes the
parent's Rect; paint recurses in order; on_event hit-tests children in
reverse paint order (topmost first).

Events arrive as scalars (trait dispatch cannot take managed args);
ScrollView reconstitutes a scroll offset by adjusting the y coordinate
before forwarding — children see content-space coordinates.

## Symbols

- **Frame**: [`Flow`](#Flow)
- **Function**: [`row`](#row)
- **Function**: [`column`](#column)
- **Frame**: [`Container`](#Container)
- **Frame**: [`ScrollView`](#ScrollView)
- **Function**: [`scroll_view`](#scroll_view)

---

### `Flow` <a id="Flow"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Flow
```

#### Members

- `var pub children: list` *(field)*
- `var pub spacing: float` *(field)*
- `var pub pad_x: float` *(field)*
- `var pub pad_y: float` *(field)*
- `var pub vertical: int` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub _cur: float` *(field)*
- `var pub _cross: float` *(field)*
- `var pub _ox: float` *(field)*
- `var pub _oy: float` *(field)*
- `var pub _aw: float` *(field)*
- `var pub _ah: float` *(field)*
- `var pub _rw: float` *(field)*
- `var pub _rh: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(c: comp.Component): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `row` <a id="row"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn row(spacing: float = ...): Flow
```

---

### `column` <a id="column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn column(spacing: float = ...): Flow
```

---

### `Container` <a id="Container"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Container
```

#### Members

- `var pub child: comp.Component` *(field)*
- `var pub pad_x: float` *(field)*
- `var pub pad_y: float` *(field)*
- `var pub bg: color.Color` *(field)*
- `pub init(c: comp.Component)` *(constructor)*
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

### `ScrollView` <a id="ScrollView"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ScrollView
```

#### Members

- `var pub child: comp.Component` *(field)*
- `var pub scroll_y: float` *(field)*
- `var pub scroll_target: float` *(field)*
- `var pub max_scroll: float` *(field)*
- `var pub scroll_sig: state.FloatSignal?` *(field)*
- `pub init(c: comp.Component)` *(constructor)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `pub fn bind_scroll(sig: state.FloatSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `scroll_view` <a id="scroll_view"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn scroll_view(c: comp.Component): ScrollView
```

---

