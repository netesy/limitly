# API Documentation: `stack.lm`

## Overview

Stack Frame - LIFO (Last In, First Out) implementation

## Symbols

- **Frame**: [`Stack`](#Stack)

---

### `Stack` <a id="Stack"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Stack
```

#### Members

- `var pub data: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn push(value: T)` *(method)*
- `pub fn pop(): union` *(method)*
- `pub fn peek(): union` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear()` *(method)*

---

