# API Documentation: `steps.lm`

## Overview

std/ui/widgets/steps.lm
Widget — ported from legacy Fluent Steps.
Horizontal sequence of numbered circles + titles; steps up to
active_step render in accent. `is_vertical` is accepted for API parity
(horizontal layout only in v1, matching the legacy emit).

## Symbols

- **Frame**: [`Steps`](#Steps)
- **Function**: [`steps`](#steps)

---

### `Steps` <a id="Steps"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Steps
```

#### Members

- `var pub step_titles: list` *(field)*
- `var pub active_step: int` *(field)*
- `var pub active_sig: state.IntSignal?` *(field)*
- `var pub is_vertical: bool` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub step_w: float` *(field)*
- `pub init(titles: list)` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn bind_active(sig: state.IntSignal): nil` *(method)*
- `fn current_step(): int` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `steps` <a id="steps"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn steps(titles: list, active: int = ..., vertical: bool = ...): Steps
```

---

