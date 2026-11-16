# API Documentation: `stack.lm`

## Overview

std/ui/containers/stack.lm
Container — all children share the same rect (CSS grid-stack /
legacy Fluent `stack`). measure reports the largest child's size;
arrange gives every child the full inner rect; paint/on_event forward
to all children in order (events reverse, topmost-last wins).

## Symbols

- **Frame**: [`Stack`](#Stack)
- **Function**: [`stack`](#stack)

---

### `Stack` <a id="Stack"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Stack
```

#### Members

- `var pub children: list` *(field)*
- `var pub spacing: float` *(field)*
- `var pub _cw: float` *(field)*
- `var pub _ch: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(c: comp.Component): nil` *(method)*
- `pub fn add_all(list: list): nil` *(method)*
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

### `stack` <a id="stack"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stack(sp: float = ...): Stack
```

---

