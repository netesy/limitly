# API Documentation: `index.lm`

## Overview

Standard Library Text Formatting Module

String alignment, case conversion, interpolation templates, and primitive value representations.

## Symbols

- **Frame**: [`Format`](#Format)
- **Function**: [`pad_string`](#pad_string)
- **Function**: [`truncate_string`](#truncate_string)

---

### `Format` <a id="Format"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Format
```

Facade helper frame aggregating formatting utilities.

#### Example: Idiomatic Usage

```lymar
var fmt = Format();
var res = fmt.pad_left("42", 5, "0");
```

#### Members

- `pub init()` *(constructor)*
- `pub fn format_int(value: int): str` *(method)*
- `pub fn format_float(value: float): str` *(method)*
- `pub fn format_bool(value: bool): str` *(method)*
- `pub fn pad_left(value: str, length_val: int, fill_char: str): str` *(method)*
- `pub fn pad_right(value: str, length_val: int, fill_char: str): str` *(method)*
- `pub fn center(value: str, length_val: int, fill_char: str): str` *(method)*
- `pub fn truncate(value: str, length_val: int, ellipsis: bool): str` *(method)*
- `pub fn title_case(value: str): str` *(method)*
- `pub fn snake_case(value: str): str` *(method)*
- `pub fn camel_case(value: str): str` *(method)*
- `pub fn kebab_case(value: str): str` *(method)*
- `pub fn pascal_case(value: str): str` *(method)*

---

### `pad_string` <a id="pad_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pad_string(value: str, length_val: int): str
```

Left-pads a string with whitespace until reaching target length.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |
| `length_val` | Minimum output length. |

#### Returns

Padded string.

---

### `truncate_string` <a id="truncate_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn truncate_string(value: str, length_val: int): str
```

Truncates a string to maximum length, appending an ellipsis (`"..."`).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text. |
| `length_val` | Maximum character length allowed. |

#### Returns

Truncated string with ellipsis.

---

