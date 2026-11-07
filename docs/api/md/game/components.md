# API Documentation: `components.lm`

## Overview

std/game/components.lm
Zero-Cost Frame Embedding Architecture for std.game IMGUI

Eliminates loose dynamic dictionaries and parallel arrays by embedding
geometry primitives directly into widget state representations.

## Symbols

- **Frame**: [`WidgetState`](#WidgetState)
- **Frame**: [`Transform2D`](#Transform2D)

---

### `WidgetState` <a id="WidgetState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame WidgetState
```

#### Members

- `var pub id: str` *(field)*
- `var pub is_hot: bool` *(field)*
- `var pub is_active: bool` *(field)*
- `var pub is_focused: bool` *(field)*
- `pub init(id: str)` *(constructor)*
- `pub fn update_hover(mx: float, my: float): bool` *(method)*
- `pub fn set_active(active: bool): nil` *(method)*

---

### `Transform2D` <a id="Transform2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Transform2D
```

#### Members

- `var pub scale_x: float` *(field)*
- `var pub scale_y: float` *(field)*
- `var pub rotation_val: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn translate(dx: float, dy: float): nil` *(method)*

---

