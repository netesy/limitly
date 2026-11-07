# API Documentation: `layout.lm`

## Overview

std/ui/layout - Layout measurement and box model

## Symbols

- **Frame**: [`LayoutBox`](#LayoutBox)
- **Frame**: [`GridSpec`](#GridSpec)
- **Frame**: [`Breakpoint`](#Breakpoint)
- **Function**: [`measure_height`](#measure_height)
- **Function**: [`measure_width`](#measure_width)
- **Function**: [`compute_layout`](#compute_layout)
- **Function**: [`flatten_layout`](#flatten_layout)
- **Function**: [`hit_test_boxes`](#hit_test_boxes)
- **Function**: [`apply_aspect_ratio`](#apply_aspect_ratio)
- **Function**: [`compute_grid_layout`](#compute_grid_layout)
- **Function**: [`responsive_layout`](#responsive_layout)
- **Function**: [`responsive`](#responsive)
- **Function**: [`breakpoint`](#breakpoint)
- **Function**: [`apply_size_constraints`](#apply_size_constraints)
- **Function**: [`compute_layout_enhanced`](#compute_layout_enhanced)

---

### `LayoutBox` <a id="LayoutBox"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LayoutBox
```

Layout box representing a measured widget with position and size

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub width: float` *(field)*
- `var pub height: float` *(field)*
- `var pub widget: ui_types.Widget` *(field)*
- `var pub children: list` *(field)*
- `pub init()` *(constructor)*

---

### `GridSpec` <a id="GridSpec"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GridSpec
```

Grid layout specification

#### Members

- `var pub columns: int` *(field)*
- `var pub rows: int` *(field)*
- `var pub column_gap: float` *(field)*
- `var pub row_gap: float` *(field)*
- `pub init()` *(constructor)*

---

### `Breakpoint` <a id="Breakpoint"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Breakpoint
```

Responsive breakpoint specification

#### Members

- `var pub min_width: float` *(field)*
- `var pub widget: ui_types.Widget` *(field)*
- `pub init(min_w: float, w: ui_types.Widget)` *(constructor)*

---

### `measure_height` <a id="measure_height"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn measure_height(w: ui_types.Widget): float
```

Measure widget height (from context.lm)

---

### `measure_width` <a id="measure_width"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn measure_width(w: ui_types.Widget, available_w: float): float
```

Measure widget width (from context.lm)

---

### `compute_layout` <a id="compute_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_layout(widget: ui_types.Widget, x: float, y: float, available_w: float, available_h: float): LayoutBox
```

Compute full layout tree with positions and sizes

---

### `flatten_layout` <a id="flatten_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flatten_layout(box: LayoutBox): list
```

Flatten layout tree to list for efficient rendering and hit-testing

---

### `hit_test_boxes` <a id="hit_test_boxes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hit_test_boxes(boxes: list, px: float, py: float): LayoutBox
```

Hit-test a flat layout box list

---

### `apply_aspect_ratio` <a id="apply_aspect_ratio"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn apply_aspect_ratio(box: LayoutBox, ratio: float): LayoutBox
```

── Aspect Ratio Layout ─────────────────────────────────────────────────────
Compute layout with aspect ratio constraint

---

### `compute_grid_layout` <a id="compute_grid_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_grid_layout(spec: GridSpec, children: list, x: float, y: float, available_w: float, available_h: float): list
```

── Enhanced Grid Layout ───────────────────────────────────────────────────
Compute grid layout with explicit column/row specification

---

### `responsive_layout` <a id="responsive_layout"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn responsive_layout(breakpoints: list, viewport_w: float, default_widget: ui_types.Widget): ui_types.Widget
```

── Responsive Layout Helpers ───────────────────────────────────────────────
Select widget based on viewport width (responsive design)

---

### `responsive` <a id="responsive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn responsive(mobile: ui_types.Widget, tablet: ui_types.Widget, desktop: ui_types.Widget, viewport_w: float): ui_types.Widget
```

Mobile-first responsive helper

---

### `breakpoint` <a id="breakpoint"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn breakpoint(small: ui_types.Widget, large: ui_types.Widget, viewport_w: float, threshold: float = ...): ui_types.Widget
```

Simple breakpoint helper (two breakpoints)

---

### `apply_size_constraints` <a id="apply_size_constraints"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn apply_size_constraints(box: LayoutBox, widget: ui_types.Widget): LayoutBox
```

── Constraint-Based Layout Helpers ─────────────────────────────────────────
Apply min/max width constraints to a layout box

---

### `compute_layout_enhanced` <a id="compute_layout_enhanced"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compute_layout_enhanced(widget: ui_types.Widget, x: float, y: float, available_w: float, available_h: float): LayoutBox
```

Enhanced compute_layout with constraints and aspect ratio

---

