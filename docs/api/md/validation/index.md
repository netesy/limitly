# API Documentation: `index.lm`

## Overview

std/validation/index.lm
Comprehensive input, format, type, and pattern validation library.

## Symbols

- **Function**: [`starts_with`](#starts_with)
- **Function**: [`ends_with`](#ends_with)
- **Function**: [`contains`](#contains)
- **Function**: [`count`](#count)
- **Function**: [`is_digit_char`](#is_digit_char)
- **Function**: [`is_alpha_char`](#is_alpha_char)
- **Frame**: [`Validate`](#Validate)
- **Function**: [`is_empty`](#is_empty)
- **Function**: [`is_number`](#is_number)

---

### `starts_with` <a id="starts_with"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn starts_with(s: str, prefix: str): bool
```

---

### `ends_with` <a id="ends_with"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ends_with(s: str, suffix: str): bool
```

---

### `contains` <a id="contains"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn contains(s: str, sub: str): bool
```

---

### `count` <a id="count"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn count(s: str, pattern: str): int
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

### `Validate` <a id="Validate"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Validate
```

Comprehensive validator providing string, numeric, pattern, and compound checks.

#### Members

- `pub init()` *(constructor)*
- `pub fn is_empty(value: str): bool` *(method)*
- `pub fn is_not_empty(value: str): bool` *(method)*
- `pub fn is_blank(value: str): bool` *(method)*
- `pub fn is_number(value: str): bool` *(method)*
- `pub fn is_integer(value: str): bool` *(method)*
- `pub fn is_alpha(value: str): bool` *(method)*
- `pub fn is_alphanumeric(value: str): bool` *(method)*
- `pub fn is_email(value: str): bool` *(method)*
- `pub fn is_phone(value: str): bool` *(method)*
- `pub fn is_url(value: str): bool` *(method)*
- `pub fn is_domain(value: str): bool` *(method)*
- `pub fn is_uuid(value: str): bool` *(method)*
- `pub fn is_ip_address(value: str): bool` *(method)*
- `pub fn is_ipv4(value: str): bool` *(method)*
- `pub fn is_ipv6(value: str): bool` *(method)*
- `pub fn length_range(value: str, min_val: int, max_val: int): bool` *(method)*
- `pub fn min_length(value: str, min_val: int): bool` *(method)*
- `pub fn max_length(value: str, max_val: int): bool` *(method)*
- `pub fn exact_length(value: str, length: int): bool` *(method)*
- `pub fn contains(value: str, substring_val: str): bool` *(method)*
- `pub fn starts_with(value: str, prefix: str): bool` *(method)*
- `pub fn ends_with(value: str, suffix: str): bool` *(method)*
- `pub fn matches_pattern(value: str, pattern: str): bool` *(method)*
- `pub fn custom_validator(value: str, validator: function): bool` *(method)*
- `pub fn all_valid(value: str, validators: list): bool` *(method)*
- `pub fn any_valid(value: str, validators: list): bool` *(method)*

---

### `is_empty` <a id="is_empty"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_empty(value: str): bool
```

Checks if string is empty.

---

### `is_number` <a id="is_number"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_number(value: str): bool
```

Checks if string is numeric.

---

