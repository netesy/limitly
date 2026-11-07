# API Documentation: `sort.lm`

## Overview

std/algorithm/sort.lm
Sort submodule for std.algorithm. Algorithmic utilities, searching, filtering, and sequence manipulation.

## Symbols

- **Function**: [`compare_ordering`](#compare_ordering)
- **Function**: [`_compare`](#_compare)
- **Function**: [`_swap`](#_swap)
- **Function**: [`insertion_sort`](#insertion_sort)
- **Function**: [`_partition`](#_partition)
- **Function**: [`_quicksort_range`](#_quicksort_range)
- **Function**: [`quicksort`](#quicksort)
- **Function**: [`quicksort_descending`](#quicksort_descending)
- **Function**: [`_merge`](#_merge)
- **Function**: [`_mergesort_range`](#_mergesort_range)
- **Function**: [`mergesort`](#mergesort)
- **Function**: [`_heapify`](#_heapify)
- **Function**: [`heapsort`](#heapsort)
- **Function**: [`counting_sort`](#counting_sort)
- **Function**: [`radix_sort`](#radix_sort)
- **Function**: [`timsort`](#timsort)
- **Function**: [`stable_sort`](#stable_sort)
- **Function**: [`partial_sort`](#partial_sort)
- **Function**: [`sort`](#sort)

---

### `compare_ordering` <a id="compare_ordering"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compare_ordering(a, b): Ordering
```

Compares two elements and yields an Ordering enum value.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `a` | First element. |
| `b` | Second element. |

#### Returns

Ordering value (Less, Greater, or Equal).

---

### `_compare` <a id="_compare"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _compare(a, b, descending: bool = ..., cmp: function = ...): int
```

---

### `_swap` <a id="_swap"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _swap(items: list, i: int, j: int)
```

---

### `insertion_sort` <a id="insertion_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn insertion_sort(items: list, descending: bool = ..., cmp: function = ...)
```

---

### `_partition` <a id="_partition"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _partition(items: list, low: int, high: int, descending: bool, cmp: function): int
```

---

### `_quicksort_range` <a id="_quicksort_range"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _quicksort_range(items: list, low: int, high: int, descending: bool, cmp: function)
```

---

### `quicksort` <a id="quicksort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn quicksort(items: list, descending: bool = ..., cmp: function = ...)
```

---

### `quicksort_descending` <a id="quicksort_descending"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn quicksort_descending(items: list)
```

---

### `_merge` <a id="_merge"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _merge(items: list, left: int, mid: int, right: int, descending: bool, cmp: function)
```

---

### `_mergesort_range` <a id="_mergesort_range"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _mergesort_range(items: list, left: int, right: int, descending: bool, cmp: function)
```

---

### `mergesort` <a id="mergesort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mergesort(items: list, descending: bool = ..., cmp: function = ...)
```

---

### `_heapify` <a id="_heapify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _heapify(items: list, n: int, i: int, descending: bool, cmp: function)
```

---

### `heapsort` <a id="heapsort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn heapsort(items: list, descending: bool = ..., cmp: function = ...)
```

---

### `counting_sort` <a id="counting_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn counting_sort(items: list, descending: bool = ...)
```

---

### `radix_sort` <a id="radix_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn radix_sort(items: list, descending: bool = ...)
```

---

### `timsort` <a id="timsort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timsort(items: list, descending: bool = ..., cmp: function = ...)
```

---

### `stable_sort` <a id="stable_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stable_sort(items: list, descending: bool = ..., cmp: function = ...)
```

---

### `partial_sort` <a id="partial_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn partial_sort(items: list, count: int, descending: bool = ..., cmp: function = ...)
```

---

### `sort` <a id="sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sort(items: list, descending: bool = ..., cmp: function = ...)
```

---

