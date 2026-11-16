# API Documentation: `stepper.lm`

## Overview

std/ui/widgets/stepper.lm
Widget — ported from legacy Fluent Stepper.
− / value / + integer stepper. Value lives in an IntSignal (bind_value);
clicks on the left/right thirds decrement/increment within [min,max].

## Symbols

- **Frame**: [`Stepper`](#Stepper)
- **Function**: [`stepper`](#stepper)

---

### `Stepper` <a id="Stepper"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Stepper
```

#### Members

- `var pub value_sig: state.IntSignal` *(field)*
- `var pub step_size: int` *(field)*
- `var pub min_int: int` *(field)*
- `var pub max_int: int` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub btn_w: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn bind_value(sig: state.IntSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `fn clamp(v: int): int` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `stepper` <a id="stepper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stepper(v: int = ..., step: int = ..., min_v: int = ..., max_v: int = ...): Stepper
```

---

