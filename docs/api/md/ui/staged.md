# API Documentation: `staged.lm`

## Overview

std/ui/staged.lm
Compile-Time Staged Evaluation for Lymar UI

Folds static layouts, bounding boxes, and theme tokens into read-only
constants at compile time; only dynamic signal bindings evaluate at runtime.
Provides type-safe compile-time generic state bindings via staged frame templates.

Stage-0 note: `staged fn` calls fold when their arguments are literals.
Keep folded call sites written with literal geometry (grid counts, paddings,
palette roles) so the compile-time path engages.

## Symbols

- **Function**: [`compute_item_width`](#compute_item_width)
- **Function**: [`compute_grid_column_width`](#compute_grid_column_width)
- **Function**: [`compute_constrained_size`](#compute_constrained_size)
- **Function**: [`fold_box_width`](#fold_box_width)
- **Function**: [`fold_box_height`](#fold_box_height)
- **Function**: [`fold_stack_extent`](#fold_stack_extent)
- **Function**: [`fold_child_offset`](#fold_child_offset)
- **Function**: [`theme_argb`](#theme_argb)
- **Frame**: [`Binding`](#Binding)

---

### `compute_item_width` <a id="compute_item_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_item_width(char_count: int, font_scale: int, pad_x: int): int
```

---

### `compute_grid_column_width` <a id="compute_grid_column_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_grid_column_width(container_w: int, num_cols: int, gap: int): int
```

---

### `compute_constrained_size` <a id="compute_constrained_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_constrained_size(desired: int, min_bound: int, max_bound: int): int
```

---

### `fold_box_width` <a id="fold_box_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fold_box_width(content_w: int, pad_x: int, border: int): int
```

---

### `fold_box_height` <a id="fold_box_height"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fold_box_height(content_h: int, pad_y: int, border: int): int
```

---

### `fold_stack_extent` <a id="fold_stack_extent"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fold_stack_extent(count: int, child_size: int, gap: int): int
```

Cumulative cross-axis extent of `count` stacked children.

---

### `fold_child_offset` <a id="fold_child_offset"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fold_child_offset(index: int, origin: int, child_size: int, gap: int): int
```

Origin of child `index` inside an evenly packed track.

---

### `theme_argb` <a id="theme_argb"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn theme_argb(role: ThemeRole): int
```

---

### `Binding` <a id="Binding"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Binding
```

#### Members

- `var pub value: T` *(field)*
- `pub init(initial: T)` *(constructor)*
- `pub fn get(): T` *(method)*
- `pub fn set(new_val: T): nil` *(method)*

---

