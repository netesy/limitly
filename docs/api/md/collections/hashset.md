# API Documentation: `hashset.lm`

## Overview

Standard Library HashSet Collection

## Symbols

- **Frame**: [`HashSet`](#HashSet)
- **Function**: [`HashSetWrapper`](#HashSetWrapper)

---

### `HashSet` <a id="HashSet"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HashSet
```

#### Members

- `var pub elements: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(item: any)` *(method)*
- `pub fn contains(item: any): bool` *(method)*
- `pub fn remove(item: any)` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*

---

### `HashSetWrapper` <a id="HashSetWrapper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn HashSetWrapper(): HashSet
```

---

