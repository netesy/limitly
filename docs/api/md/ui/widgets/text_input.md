# API Documentation: `text_input.lm`

## Overview

std/ui/widgets/text_input.lm
Widget — split from std/ui/widgets.lm.

## Symbols

- **Frame**: [`TextInput`](#TextInput)
- **Function**: [`text_input`](#text_input)

---

### `TextInput` <a id="TextInput"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TextInput
```

#### Members

- `var pub ctrl: text_ctrl.EditorController` *(field)*
- `var pub text_sig: state.StrSignal` *(field)*
- `var pub placeholder: str` *(field)*
- `var pub bg: color.Color` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub pad_x: float` *(field)*
- `var pub pad_y: float` *(field)*
- `var pub focused: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn text(): str` *(method)*
- `pub fn bind_text(sig: state.StrSignal): nil` *(method)*
- `fn sync_sig(): nil` *(method)*
- `fn reconcile(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*
- `pub fn paint(): nil` *(method)*

---

### `text_input` <a id="text_input"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn text_input(initial: str = ..., hint: str = ...): TextInput
```

---

