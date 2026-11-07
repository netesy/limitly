# API Documentation: `url.lm`

## Overview

std/validation/url.lm
URL and domain name format validation.

## Symbols

- **Function**: [`starts_with`](#starts_with)
- **Function**: [`index_of`](#index_of)
- **Function**: [`last_index_of`](#last_index_of)
- **Function**: [`is_digit_char`](#is_digit_char)
- **Function**: [`is_alpha_char`](#is_alpha_char)
- **Function**: [`is_url`](#is_url)
- **Function**: [`is_domain`](#is_domain)

---

### `starts_with` <a id="starts_with"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn starts_with(s: str, prefix: str): bool
```

---

### `index_of` <a id="index_of"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn index_of(s: str, pattern: str): int
```

---

### `last_index_of` <a id="last_index_of"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn last_index_of(s: str, pattern: str): int
```

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

### `is_url` <a id="is_url"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_url(value: str): bool
```

Validates whether a candidate string is a well-formed HTTP or HTTPS URL.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Candidate URL string. |

#### Returns

True if string begins with http:// or https:// and contains a valid domain.

---

### `is_domain` <a id="is_domain"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_domain(value: str): bool
```

Validates whether a string is a well-formed Internet domain name.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Candidate domain name string. |

#### Returns

True if domain and TLD follow standard naming conventions.

---

