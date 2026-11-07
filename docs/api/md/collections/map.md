# API Documentation: `map.lm`

## Overview

Standard Library Map Collection

## Symbols

- **Frame**: [`HashMapWrapper`](#HashMapWrapper)
- **Function**: [`Map`](#Map)

---

### `HashMapWrapper` <a id="HashMapWrapper"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HashMapWrapper
```

Hash map wrapper supporting dynamic key-value pairs.

#### Members

- `var pub impl: hashmap.HashMap` *(field)*
- `pub init()` *(constructor)*
- `pub fn put(key: str, value: any)` *(method)*
- `pub fn get(key: str): any?` *(method)*
- `pub fn remove(key: str)` *(method)*
- `pub fn contains_key(key: str): bool` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear()` *(method)*

---

### `Map` <a id="Map"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn Map(initial_cap: int = ...): HashMapWrapper
```

Constructs a new Map instance backed by HashMapWrapper.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `initial_cap` | Initial capacity for the underlying hash map table. |

#### Returns

New Map wrapper instance.

---

