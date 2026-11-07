# API Documentation: `btreemap.lm`

## Overview

Standard Library BTreeMap & SortedMap Collections

## Symbols

- **Frame**: [`BTreeMapWrapper`](#BTreeMapWrapper)
- **Function**: [`BTreeMap`](#BTreeMap)
- **Function**: [`SortedMap`](#SortedMap)

---

### `BTreeMapWrapper` <a id="BTreeMapWrapper"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BTreeMapWrapper
```

Ordered map data structure backed by an underlying binary search tree.

#### Members

- `var pub impl: tree.TreeMap` *(field)*
- `pub init()` *(constructor)*
- `pub fn put(key: any, value: any)` *(method)*
- `pub fn get(key: any): any` *(method)*
- `pub fn contains(key: any): bool` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear(): nil` *(method)*

---

### `BTreeMap` <a id="BTreeMap"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn BTreeMap(): BTreeMapWrapper
```

Constructs a new BTreeMap instance backed by BTreeMapWrapper.

#### Returns

New ordered map instance.

---

### `SortedMap` <a id="SortedMap"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn SortedMap(): BTreeMapWrapper
```

Constructs a new SortedMap instance backed by BTreeMapWrapper.

#### Returns

New sorted map instance.

---

