# API Documentation: `types.lm`

## Overview

std/ui/types.lm
Shared enums, style model, and geometry for the retained component UI.
Concrete widgets live under std.ui.widgets / std.ui.containers and
conform to the std.ui.component.Component contract.

## Symbols

- **Type Alias**: [`Align`](#Align)
- **Function**: [`point`](#point)
- **Function**: [`rect`](#rect)
- **Function**: [`axis_flag`](#axis_flag)
- **Function**: [`align_flag`](#align_flag)
- **Function**: [`weight_value`](#weight_value)
- **Function**: [`semantic_name`](#semantic_name)
- **Function**: [`mask_shape_name`](#mask_shape_name)
- **Function**: [`alert_kind_of`](#alert_kind_of)
- **Function**: [`dot_state_of`](#dot_state_of)
- **Function**: [`alert_kind_name`](#alert_kind_name)
- **Function**: [`dot_state_name`](#dot_state_name)
- **Frame**: [`Style`](#Style)
- **Function**: [`style`](#style)

---

### `Align` <a id="Align"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type Align = Alignment
```

---

### `point` <a id="point"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn point(x: float, y: float): Vector2
```

---

### `rect` <a id="rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rect(x: float, y: float, w: float, h: float): Rect
```

---

### `axis_flag` <a id="axis_flag"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn axis_flag(a: Axis): int
```

---

### `align_flag` <a id="align_flag"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn align_flag(a: Align): int
```

---

### `weight_value` <a id="weight_value"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn weight_value(w: Weight): int
```

---

### `semantic_name` <a id="semantic_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn semantic_name(s: Semantic): str
```

---

### `mask_shape_name` <a id="mask_shape_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mask_shape_name(m: MaskShape): str
```

---

### `alert_kind_of` <a id="alert_kind_of"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert_kind_of(type_val: str): AlertKind
```

---

### `dot_state_of` <a id="dot_state_of"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dot_state_of(status: str): DotState
```

---

### `alert_kind_name` <a id="alert_kind_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alert_kind_name(k: AlertKind): str
```

---

### `dot_state_name` <a id="dot_state_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dot_state_name(s: DotState): str
```

---

### `Style` <a id="Style"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Style
```

Reusable Style Model (LVGL / CSS Inspired)

#### Members

- `var pub has_bg: bool` *(field)*
- `var pub bg: color.Color` *(field)*
- `var pub has_fg: bool` *(field)*
- `var pub fg: color.Color` *(field)*
- `var pub has_padding: bool` *(field)*
- `var pub pad_l: float` *(field)*
- `var pub pad_t: float` *(field)*
- `var pub pad_r: float` *(field)*
- `var pub pad_b: float` *(field)*
- `var pub has_radius: bool` *(field)*
- `var pub radius: float` *(field)*
- `var pub has_font_size: bool` *(field)*
- `var pub font_size_val: float` *(field)*
- `var pub has_weight: bool` *(field)*
- `var pub weight_val: int` *(field)*
- `var pub has_spacing: bool` *(field)*
- `var pub spacing_val: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn background(c: color.Color): Style` *(method)*
- `pub fn foreground(c: color.Color): Style` *(method)*
- `pub fn color(c: color.Color): Style` *(method)*
- `pub fn padding(p: float): Style` *(method)*
- `pub fn padding_xy(x: float, y: float): Style` *(method)*
- `pub fn corner_radius(r: float): Style` *(method)*
- `pub fn font_size(s: float): Style` *(method)*
- `pub fn weight(w: int): Style` *(method)*
- `pub fn bold(): Style` *(method)*
- `pub fn spacing(s: float): Style` *(method)*
- `pub fn merge(other: Style): Style` *(method)*

---

### `style` <a id="style"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn style(): Style
```

---

