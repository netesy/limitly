# API Documentation: `hash.lm`

## Overview

Standard Library HashMap Collection
This implementation uses the native dict type for efficiency.

## Symbols

- **Frame**: [`NativeHashMap`](#NativeHashMap)
- **Frame**: [`NativeHashSet`](#NativeHashSet)

---

### `NativeHashMap` <a id="NativeHashMap"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame NativeHashMap
```

#### Members

- `var pub data: dict` *(field)*
- `pub init()` *(constructor)*
- `pub fn put(key: any, value: any)` *(method)*
- `pub fn get(key: any): any` *(method)*
- `pub fn has(key: any): bool` *(method)*
- `pub fn remove(key: any)` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn keys(): list` *(method)*

---

### `NativeHashSet` <a id="NativeHashSet"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame NativeHashSet
```

#### Members

- `var pub data: dict` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(item: any)` *(method)*
- `pub fn contains(item: any): bool` *(method)*
- `pub fn remove(item: any)` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn length(): int` *(method)*

---

