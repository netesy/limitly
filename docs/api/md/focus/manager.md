# API Documentation: `manager.lm`

## Overview

std/focus/manager.lm
Manager submodule for std.focus. Focus management, keyboard focus rings, and widget focus navigation.

## Symbols

- **Frame**: [`Manager`](#Manager)

---

### `Manager` <a id="Manager"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Manager
```

#### Members

- `var pub current_id: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn request_focus(id: str): nil` *(method)*
- `pub fn clear_focus(): nil` *(method)*
- `pub fn has_focus(id: str): bool` *(method)*

---

