# API Documentation: `state.lm`

## Overview

std/game/gui/state.lm
Modular layout state, window tracking, and style state for IMGUI

## Symbols

- **Trait**: [`Component`](#Component)
- **Frame**: [`WindowState`](#WindowState)
- **Function**: [`WindowState`](#WindowState)
- **Frame**: [`LayoutCursor`](#LayoutCursor)
- **Function**: [`LayoutCursor`](#LayoutCursor)

---

### `Component` <a id="Component"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Component
```

#### Members

- `fn is_occluded(x: float, y: float, w: float, h: float): bool` *(method requirement)*

---

### `WindowState` <a id="WindowState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame WindowState
```

#### Members

- `var pub collapsed: bool` *(field)*
- `var pub is_dragging: bool` *(field)*
- `var pub drag_off_x: float` *(field)*
- `var pub drag_off_y: float` *(field)*
- `pub init()` *(constructor)*

---

### `WindowState` <a id="WindowState"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn WindowState(x: float = ..., y: float = ..., w: float = ..., h: float = ...): WindowState
```

---

### `LayoutCursor` <a id="LayoutCursor"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LayoutCursor
```

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub start_x: float` *(field)*
- `var pub start_y: float` *(field)*
- `var pub line_h: float` *(field)*
- `var pub same_line_flag: bool` *(field)*
- `var pub prev_item_w: float` *(field)*
- `var pub indent_x: float` *(field)*
- `pub init()` *(constructor)*

---

### `LayoutCursor` <a id="LayoutCursor"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn LayoutCursor(start_x: float = ..., start_y: float = ...): LayoutCursor
```

---

