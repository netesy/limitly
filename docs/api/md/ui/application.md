# API Documentation: `application.lm`

## Overview

std/ui/application.lm
Application submodule for std.ui. User interface widgets, layout engines, styling, and application framework.

## Symbols

- **Frame**: [`Application`](#Application)

---

### `Application` <a id="Application"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Application
```

#### Members

- `var pub name: str` *(field)*
- `var pub root_widget: ui_types.Widget` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_root(widget: ui_types.Widget): nil` *(method)*
- `pub fn run(): nil` *(method)*

---

