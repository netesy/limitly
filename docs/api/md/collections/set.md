# API Documentation: `set.lm`

## Overview

Set Frame - Unique element collection implementation

## Symbols

- **Frame**: [`Set`](#Set)
- **Function**: [`set_from_array`](#set_from_array)
- **Frame**: [`GenericSet`](#GenericSet)

---

### `Set` <a id="Set"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Set
```

#### Members

- `var pub elements: list` *(field)*
- `pub fn add(value: int): Set` *(method)*
- `pub fn remove(value: int): Set` *(method)*
- `pub fn contains(value: int): bool` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear(): Set` *(method)*
- `pub fn union(other: Set): Set` *(method)*
- `pub fn intersection(other: Set): Set` *(method)*
- `pub fn difference(other: Set): Set` *(method)*
- `pub fn symmetric_difference(other: Set): Set` *(method)*
- `pub fn is_subset(other: Set): bool` *(method)*
- `pub fn is_superset(other: Set): bool` *(method)*
- `pub fn is_disjoint(other: Set): bool` *(method)*
- `pub fn map(f: function): Set` *(method)*
- `pub fn filter(predicate: function): Set` *(method)*
- `pub fn fold(f: function, initial: int): int` *(method)*
- `pub fn for_each(f: function): nil` *(method)*
- `pub fn sum(): int` *(method)*
- `pub fn product(): int` *(method)*
- `pub fn min(): int?` *(method)*
- `pub fn max(): int?` *(method)*
- `fn find_index(value: int): int?` *(method)*
- `pub fn to_array(): list` *(method)*
- `pub fn to_string(): str` *(method)*

---

### `set_from_array` <a id="set_from_array"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_from_array(arr: list): Set
```

---

### `GenericSet` <a id="GenericSet"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GenericSet
```

#### Members

- `var pub elements: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(value: T): bool` *(method)*
- `pub fn remove(value: T): bool` *(method)*
- `pub fn contains(value: T): bool` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear(): nil` *(method)*
- `pub fn to_array(): list` *(method)*

---

