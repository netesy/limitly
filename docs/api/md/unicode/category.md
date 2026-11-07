# API Documentation: `category.lm`

## Overview

Standard Library Unicode Character Category Module

Unicode character classification, letter casing checks, digit and whitespace detection.

## Symbols

- **Function**: [`is_upper`](#is_upper)
- **Function**: [`is_lower`](#is_lower)
- **Function**: [`is_digit`](#is_digit)
- **Function**: [`is_alpha`](#is_alpha)
- **Function**: [`is_alphanumeric`](#is_alphanumeric)
- **Function**: [`is_whitespace`](#is_whitespace)

---

### `is_upper` <a id="is_upper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_upper(ch: str): bool
```

Checks whether the first character of the string is an uppercase ASCII/Unicode letter.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ch` | Input string whose initial character is checked. |

#### Returns

`true` if uppercase, `false` otherwise.

#### Example: Idiomatic Usage

```lymar
var ok = is_upper("Hello"); // true
```

---

### `is_lower` <a id="is_lower"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_lower(ch: str): bool
```

Checks whether the first character of the string is a lowercase ASCII/Unicode letter.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ch` | Input string whose initial character is checked. |

#### Returns

`true` if lowercase, `false` otherwise.

#### Example: Idiomatic Usage

```lymar
var ok = is_lower("world"); // true
```

---

### `is_digit` <a id="is_digit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_digit(ch: str): bool
```

Checks whether the first character of the string is a decimal digit ('0' through '9').

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ch` | Input string whose initial character is checked. |

#### Returns

`true` if digit, `false` otherwise.

#### Example: Idiomatic Usage

```lymar
var ok = is_digit("7"); // true
```

---

### `is_alpha` <a id="is_alpha"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_alpha(ch: str): bool
```

Checks whether the first character is an alphabetic letter.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ch` | Input string. |

#### Returns

`true` if upper or lowercase letter, `false` otherwise.

---

### `is_alphanumeric` <a id="is_alphanumeric"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_alphanumeric(ch: str): bool
```

Checks whether the first character is an alphanumeric character (letter or digit).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ch` | Input string. |

#### Returns

`true` if letter or digit, `false` otherwise.

---

### `is_whitespace` <a id="is_whitespace"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_whitespace(ch: str): bool
```

Checks whether the first character is a whitespace delimiter (space, tab, newline, carriage return).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ch` | Input string. |

#### Returns

`true` if whitespace, `false` otherwise.

---

