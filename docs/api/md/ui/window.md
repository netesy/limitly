# API Documentation: `window.lm`

## Overview

std/ui/window.lm
Window submodule for std.ui. User interface widgets, layout engines, styling, and application framework.

## Symbols

- **Frame**: [`Window`](#Window)

---

### `Window` <a id="Window"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Window
```

#### Members

- `var pub title: str` *(field)*
- `var pub width: float` *(field)*
- `var pub height: float` *(field)*
- `var pub root: ui_types.Widget` *(field)*
- `var pub root_blueprint: ui_types.Blueprint` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_root(w: ui_types.Widget): Window` *(method)*

---

