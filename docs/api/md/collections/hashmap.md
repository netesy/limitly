# API Documentation: `hashmap.lm`

## Overview

HashMap Frame - $O(1)$ amortized bucket hash table

## Symbols

- **Frame**: [`HashEntry`](#HashEntry)
- **Frame**: [`HashMap`](#HashMap)
- **Function**: [`hashmap`](#hashmap)

---

### `HashEntry` <a id="HashEntry"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HashEntry
```

#### Members

- `var pub key: str` *(field)*
- `var pub value: any` *(field)*
- `pub init(k: str, v: any)` *(constructor)*

---

### `HashMap` <a id="HashMap"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HashMap
```

#### Members

- `var pub buckets: list` *(field)*
- `var pub capacity: int` *(field)*
- `var pub count: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn _hash(key: str): int` *(method)*
- `pub fn _grow()` *(method)*
- `pub fn put(key: str, value: any): HashMap` *(method)*
- `pub fn get(key: str): any?` *(method)*
- `pub fn contains_key(key: str): bool` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn remove(key: str): HashMap` *(method)*
- `pub fn clear(): HashMap` *(method)*

---

### `hashmap` <a id="hashmap"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hashmap(initial_cap: int = ...): HashMap
```

---

