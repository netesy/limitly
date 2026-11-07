# API Documentation: `list.lm`

## Overview

Standard Library List Collection

## Symbols

- **Frame**: [`List`](#List)

---

### `List` <a id="List"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame List: Collection, Indexable, Mutable
```

#### Members

- `var pub data: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn append(item: any): nil` *(method)*
- `pub fn push(item: any)` *(method)*
- `pub fn pop(): any` *(method)*
- `pub fn remove(index: int): any` *(method)*
- `pub fn get(index: int): any` *(method)*
- `pub fn set(index: int, item: any): bool` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn clear(): nil` *(method)*

---

