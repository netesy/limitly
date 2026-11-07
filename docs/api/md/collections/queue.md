# API Documentation: `queue.lm`

## Overview

Standard Library Queue Collection

## Symbols

- **Frame**: [`Queue`](#Queue)

---

### `Queue` <a id="Queue"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Queue
```

#### Members

- `var pub items: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn enqueue(item: T)` *(method)*
- `pub fn dequeue(): union` *(method)*
- `pub fn peek(): union` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear()` *(method)*

---

