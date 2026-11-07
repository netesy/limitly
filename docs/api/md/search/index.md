# API Documentation: `index.lm`

## Overview

Standard Library Search Module

Linear search, binary search, bounds, and interpolation search algorithms.

## Symbols

- **Function**: [`linear_search`](#linear_search)
- **Function**: [`binary_search`](#binary_search)
- **Function**: [`lower_bound`](#lower_bound)
- **Function**: [`upper_bound`](#upper_bound)
- **Function**: [`equal_range`](#equal_range)
- **Function**: [`interpolation_search`](#interpolation_search)

---

### `linear_search` <a id="linear_search"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn linear_search(items: list, target): int
```

Performs linear search on an arbitrary sequence.

---

### `binary_search` <a id="binary_search"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn binary_search(items: list, target): int
```

Performs binary search on a sorted sequence.

---

### `lower_bound` <a id="lower_bound"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lower_bound(items: list, target): int
```

Finds lower bound index in a sorted sequence.

---

### `upper_bound` <a id="upper_bound"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn upper_bound(items: list, target): int
```

Finds upper bound index in a sorted sequence.

---

### `equal_range` <a id="equal_range"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn equal_range(items: list, target): tuple
```

Computes (lower_bound, upper_bound) range tuple.

---

### `interpolation_search` <a id="interpolation_search"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn interpolation_search(items: list, target: int): int
```

Fast interpolation search on uniformly distributed integers.

---

