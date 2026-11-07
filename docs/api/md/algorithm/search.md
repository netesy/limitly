# API Documentation: `search.lm`

## Overview

Standard Library Sequence Search Submodule

Linear search, predicate search, quantifiers (all, any, none), and interpolation search.

## Symbols

- **Function**: [`linear_search`](#linear_search)
- **Function**: [`find`](#find)
- **Function**: [`find_if`](#find_if)
- **Function**: [`any_match`](#any_match)
- **Function**: [`none`](#none)
- **Function**: [`all`](#all)
- **Function**: [`count`](#count)
- **Function**: [`interpolation_search`](#interpolation_search)

---

### `linear_search` <a id="linear_search"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn linear_search(items: list, value): int
```

Finds the first index of a matching value using linear traversal.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence to search. |
| `value` | Target element to find. |

#### Returns

Index if found, or -1 if not present.

#### Example: Idiomatic Usage

```lymar
var idx = linear_search(["a", "b", "c"], "b"); // 1
```

---

### `find` <a id="find"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn find(items: list, value): int
```

Alias for linear_search to find a matching value.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence to search. |
| `value` | Target element. |

#### Returns

Index if found, or -1.

---

### `find_if` <a id="find_if"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn find_if(items: list, p: function): int
```

Finds the index of the first element satisfying a predicate function.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence to search. |
| `p` | Predicate callback returning boolean. |

#### Returns

Index of matching item, or -1 if none match.

---

### `any_match` <a id="any_match"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn any_match(items: list, p: function): bool
```

Checks whether at least one element satisfies the predicate.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence to inspect. |
| `p` | Predicate callback. |

#### Returns

`true` if any element satisfies `p`, `false` otherwise.

---

### `none` <a id="none"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn none(items: list, p: function): bool
```

Checks whether no elements satisfy the predicate.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence to inspect. |
| `p` | Predicate callback. |

#### Returns

`true` if no element satisfies `p`, `false` otherwise.

---

### `all` <a id="all"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn all(items: list, p: function): bool
```

Checks whether all elements satisfy the predicate.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence to inspect. |
| `p` | Predicate callback. |

#### Returns

`true` if every element satisfies `p`, `false` otherwise.

---

### `count` <a id="count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn count(items: list, value): int
```

Counts the number of occurrences of value within items.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence to scan. |
| `value` | Value to count. |

#### Returns

Occurrence count.

---

### `interpolation_search` <a id="interpolation_search"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn interpolation_search(items: list, target: int): int
```

Fast interpolation search on uniformly distributed sorted integer arrays.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sorted list of integer values. |
| `target` | Integer value to locate. |

#### Returns

Index if found, or -1 if absent.

---

