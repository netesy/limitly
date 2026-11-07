# API Documentation: `phone.lm`

## Overview

std/validation/phone.lm
International and domestic telephone number validation.

## Symbols

- **Function**: [`is_digit_char`](#is_digit_char)
- **Function**: [`is_phone`](#is_phone)

---

### `is_digit_char` <a id="is_digit_char"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_digit_char(ch: str): bool
```

---

### `is_phone` <a id="is_phone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_phone(value: str): bool
```

Validates whether a candidate string is a telephone number.
Allows an optional leading '+' country code prefix, digits, and standard separators (spaces, hyphens, parentheses).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Candidate phone number string. |

#### Returns

True if string matches telephone formatting rules.

---

