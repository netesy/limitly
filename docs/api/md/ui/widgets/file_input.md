# API Documentation: `file_input.lm`

## Overview

std/ui/widgets/file_input.lm
Widget — file picker control. Shows the selected path (or the
placeholder label) plus a "Browse" chip. Clicking fires the optional
callback — the app opens the native dialog and calls set_path() with
the result. `path_sig` mirrors selected_path for reactive UIs.

## Symbols

- **Frame**: [`FileInput`](#FileInput)
- **Function**: [`file_input`](#file_input)

---

### `FileInput` <a id="FileInput"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FileInput
```

#### Members

- `var pub label: str` *(field)*
- `var pub selected_path: str` *(field)*
- `var pub path_sig: state.StrSignal?` *(field)*
- `var pub click: function?` *(field)*
- `var pub surface: color.Color` *(field)*
- `var pub surface_hover: color.Color` *(field)*
- `var pub border: color.Color` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub text_muted: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub on_accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub hovered: int` *(field)*
- `var pub pressed: int` *(field)*
- `var pub auto_dialog: int` *(field)*
- `var pub _bx: float` *(field)*
- `var pub _bw: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn enable_native_dialog(): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn bind_path(sig: state.StrSignal): nil` *(method)*
- `pub fn set_path(p: str): nil` *(method)*
- `pub fn clear(): nil` *(method)*
- `fn display_name(): str` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `fn chip_w(): float` *(method)*
- `pub fn paint(): nil` *(method)*
- `fn in_chip(x: int, y: int): bool` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `file_input` <a id="file_input"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn file_input(lbl: str = ..., on_select: function? = ...): FileInput
```

---

