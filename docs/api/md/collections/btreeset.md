# API Documentation: `btreeset.lm`

## Overview

Standard Library BTreeSet Collection

## Symbols

- **Frame**: [`BTreeSetWrapper`](#BTreeSetWrapper)
- **Function**: [`BTreeSet`](#BTreeSet)

---

### `BTreeSetWrapper` <a id="BTreeSetWrapper"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BTreeSetWrapper
```

Ordered set data structure backed by an underlying binary search tree.

#### Members

- `var pub impl: tree.TreeSet` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(item: any)` *(method)*
- `pub fn contains(item: any): bool` *(method)*
- `pub fn length(): int` *(method)*

---

### `BTreeSet` <a id="BTreeSet"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn BTreeSet(): BTreeSetWrapper
```

Constructs a new BTreeSet instance backed by BTreeSetWrapper.

#### Returns

New ordered set instance.

---

