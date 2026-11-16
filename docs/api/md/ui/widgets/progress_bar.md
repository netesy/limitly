# API Documentation: `progress_bar.lm`

## Overview

std/ui/widgets/progress_bar.lm
Widget — split from std/ui/widgets.lm.

## Symbols

- **Frame**: [`ProgressBar`](#ProgressBar)
- **Function**: [`progress_bar`](#progress_bar)

---

### `ProgressBar` <a id="ProgressBar"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ProgressBar
```

#### Members

- `var pub frac: float` *(field)*
- `var pub frac_sig: state.FloatSignal?` *(field)*
- `var pub track_color: color.Color` *(field)*
- `var pub fill_color: color.Color` *(field)*
- `var pub show_pct: int` *(field)*
- `var pub fg: color.Color` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn bind_frac(sig: state.FloatSignal): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `fn resolved_frac(): float` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `progress_bar` <a id="progress_bar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn progress_bar(f: float = ...): ProgressBar
```

---

