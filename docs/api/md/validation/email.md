# API Documentation: `email.lm`

## Overview

std/validation/email.lm
RFC 5322 compliant email address validation.

## Symbols

- **Function**: [`is_digit_char`](#is_digit_char)
- **Function**: [`is_alpha_char`](#is_alpha_char)
- **Function**: [`is_email`](#is_email)

---

### `is_digit_char` <a id="is_digit_char"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_digit_char(ch: str): bool
```

---

### `is_alpha_char` <a id="is_alpha_char"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_alpha_char(ch: str): bool
```

---

### `is_email` <a id="is_email"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_email(value: str): bool
```

Validates whether a candidate string is a well-formed email address.
Verifies local part character set, domain label format, and top-level domain length.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Candidate email string. |

#### Returns

True if string is a valid email format, false otherwise.

---

