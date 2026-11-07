# API Documentation: `string.lm`

## Overview

std/string/string.lm
The String wrapper frame.

## Symbols

- **Frame**: [`String`](#String)

---

### `String` <a id="String"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame String
```

Object-oriented wrapper around raw primitive strings providing fluent methods.

#### Members

- `var pub value: str` *(field)*
- `pub init(value: str)` *(constructor)*
- `pub fn length(): int` *(method)*
- `pub fn concat(other: str): str` *(method)*
- `pub fn trim(): str` *(method)*
- `pub fn to_upper(): str` *(method)*
- `pub fn to_lower(): str` *(method)*
- `pub fn contains(needle: str): bool` *(method)*
- `pub fn split(delimiter: str): list` *(method)*
- `pub fn replace(old: str, replacement: str): str` *(method)*
- `pub fn starts_with(prefix: str): bool` *(method)*
- `pub fn ends_with(suffix: str): bool` *(method)*
- `pub fn substring(start: int, end: int): str` *(method)*
- `pub fn char_at(index: int): str` *(method)*
- `pub fn byte_at(index: int): int` *(method)*
- `pub fn repeat(count: int): str` *(method)*
- `pub fn pad_left(width: int): str` *(method)*
- `pub fn pad_right(width: int): str` *(method)*
- `pub fn index_of(sub: str): int` *(method)*
- `pub fn last_index_of(sub: str): int` *(method)*

---

