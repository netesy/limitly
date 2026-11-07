# API Documentation: `binary_search.lm`

## Overview

Standard Library Binary Search Submodule

Fast logarithmic searching on sorted sequences.

## Symbols

- **Function**: [`binary_search`](#binary_search)
- **Function**: [`lower_bound`](#lower_bound)
- **Function**: [`upper_bound`](#upper_bound)
- **Function**: [`equal_range`](#equal_range)

---

### `binary_search` <a id="binary_search"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn binary_search(items: list, value): int
```

Performs binary search on a sorted list to locate the index of a target value.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sorted list of elements. |
| `value` | Target element to search for. |

#### Returns

Zero-based index if found, or -1 if not present.

#### Example: Idiomatic Usage

```lymar
var idx = binary_search([1, 3, 5, 7, 9], 5); // 2
```

---

### `lower_bound` <a id="lower_bound"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lower_bound(items: list, value): int
```

Finds the index of the first element not less than value in a sorted list.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sorted list of elements. |
| `value` | Target comparison value. |

#### Returns

Index in range [0, len(items)].

---

### `upper_bound` <a id="upper_bound"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn upper_bound(items: list, value): int
```

Finds the index of the first element strictly greater than value in a sorted list.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sorted list of elements. |
| `value` | Target comparison value. |

#### Returns

Index in range [0, len(items)].

---

### `equal_range` <a id="equal_range"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn equal_range(items: list, value): tuple
```

Computes the [lower_bound, upper_bound) range for a value in a sorted list.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sorted list of elements. |
| `value` | Target value. |

#### Returns

Tuple containing (lower_bound, upper_bound).

---

