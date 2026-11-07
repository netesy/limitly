# API Documentation: `normalize.lm`

## Overview

Standard Library Unicode Case Normalization Module

Fast case translation and Unicode string normalization.

## Symbols

- **Function**: [`_char_to_lower`](#_char_to_lower)
- **Function**: [`_char_to_upper`](#_char_to_upper)
- **Function**: [`to_lower`](#to_lower)
- **Function**: [`to_upper`](#to_upper)

---

### `_char_to_lower` <a id="_char_to_lower"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _char_to_lower(ch: str): str
```

---

### `_char_to_upper` <a id="_char_to_upper"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _char_to_upper(ch: str): str
```

---

### `to_lower` <a id="to_lower"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_lower(value: str): str
```

Converts all characters in a string to lowercase.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |

#### Returns

Lowercased string.

#### Example: Idiomatic Usage

```lymar
var text = to_lower("LIMITLESS"); // "limitless"
```

---

### `to_upper` <a id="to_upper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_upper(value: str): str
```

Converts all characters in a string to uppercase.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |

#### Returns

Uppercased string.

#### Example: Idiomatic Usage

```lymar
var text = to_upper("limitless"); // "LIMITLESS"
```

---

