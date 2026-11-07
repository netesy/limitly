# API Documentation: `deque.lm`

## Overview

Standard Library Deque Collection

## Symbols

- **Frame**: [`Deque`](#Deque)

---

### `Deque` <a id="Deque"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Deque
```

#### Members

- `var pub data: list` *(field)*
- `var size: int` *(field)*
- `pub init()` *(constructor)*
- `fn _copy_range(lo: int, hi: int): list` *(method)*
- `pub fn push_back(item: T)` *(method)*
- `pub fn push_front(item: T)` *(method)*
- `pub fn peek_back(): union` *(method)*
- `pub fn peek_front(): union` *(method)*
- `pub fn pop_back(): union` *(method)*
- `pub fn pop_front(): union` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear()` *(method)*

---

