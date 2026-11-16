# API Documentation: `math.lm`

## Overview

std/widget/math.lm
Headless mathematical normalization, snapping, and layout computations for widgets.

## Symbols

- **Function**: [`clamp_value`](#clamp_value)
- **Function**: [`value_to_ratio`](#value_to_ratio)
- **Function**: [`ratio_to_value`](#ratio_to_value)
- **Function**: [`step_value`](#step_value)
- **Function**: [`calculate_thumb_rect`](#calculate_thumb_rect)
- **Function**: [`calculate_progress_rect`](#calculate_progress_rect)
- **Function**: [`hit_test`](#hit_test)

---

### `clamp_value` <a id="clamp_value"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clamp_value(v: float, min_val: float, max_val: float): float
```

---

### `value_to_ratio` <a id="value_to_ratio"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn value_to_ratio(v: float, min_val: float, max_val: float): float
```

---

### `ratio_to_value` <a id="ratio_to_value"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ratio_to_value(ratio: float, min_val: float, max_val: float): float
```

---

### `step_value` <a id="step_value"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn step_value(v: float, step: float, min_val: float): float
```

---

### `calculate_thumb_rect` <a id="calculate_thumb_rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn calculate_thumb_rect(track: Rect, ratio: float, thumb_w: float, thumb_h: float, is_vertical: bool): Rect
```

---

### `calculate_progress_rect` <a id="calculate_progress_rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn calculate_progress_rect(track: Rect, ratio: float, is_vertical: bool): Rect
```

---

### `hit_test` <a id="hit_test"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hit_test(bounds: Rect, px: float, py: float): bool
```

---

