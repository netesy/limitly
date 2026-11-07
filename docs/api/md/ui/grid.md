# API Documentation: `grid.lm`

## Overview

std/ui/grid - Grid layout container (CSS-grid like layout)

## Symbols

- **Function**: [`grid`](#grid)
- **Frame**: [`GridLayout`](#GridLayout)
- **Function**: [`grid_two_column`](#grid_two_column)
- **Function**: [`grid_three_column`](#grid_three_column)
- **Function**: [`grid_with_aspect`](#grid_with_aspect)
- **Function**: [`grid_enhanced`](#grid_enhanced)

---

### `grid` <a id="grid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid(columns_count: int, children: list, spacing_val: float = ...): ui_types.Widget
```

Create a grid layout with columns × rows

---

### `GridLayout` <a id="GridLayout"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GridLayout
```

Grid widget with auto layout

#### Members

- `var pub columns: int` *(field)*
- `var pub gap: float` *(field)*
- `var pub children: list` *(field)*
- `pub init()` *(constructor)*

---

### `grid_two_column` <a id="grid_two_column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_two_column(left: ui_types.Widget, right: ui_types.Widget, gap: float = ...): ui_types.Widget
```

Two-column grid (common pattern)

---

### `grid_three_column` <a id="grid_three_column"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_three_column(a: ui_types.Widget, b: ui_types.Widget, c: ui_types.Widget, gap: float = ...): ui_types.Widget
```

Three-column grid (common pattern)

---

### `grid_with_aspect` <a id="grid_with_aspect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_with_aspect(columns_count: int, children: list, aspect_ratio: float, spacing_val: float = ...): ui_types.Widget
```

Grid with aspect ratio constraint on cells

---

### `grid_enhanced` <a id="grid_enhanced"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn grid_enhanced(spec: layout.GridSpec, children: list): ui_types.Widget
```

Grid using enhanced layout system

---

