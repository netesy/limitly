# API Documentation: `index.lm`

## Overview

Standard Library Sort Module

Sorting algorithms and ordering utilities: quicksort, mergesort, heapsort, timsort, and counting sort.

## Symbols

- **Function**: [`insertion_sort`](#insertion_sort)
- **Function**: [`quicksort`](#quicksort)
- **Function**: [`mergesort`](#mergesort)
- **Function**: [`heapsort`](#heapsort)
- **Function**: [`counting_sort`](#counting_sort)
- **Function**: [`radix_sort`](#radix_sort)
- **Function**: [`timsort`](#timsort)
- **Function**: [`stable_sort`](#stable_sort)
- **Function**: [`partial_sort`](#partial_sort)
- **Function**: [`sort`](#sort)
- **Function**: [`compare`](#compare)

---

### `insertion_sort` <a id="insertion_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn insertion_sort(items: list, descending: bool = ..., cmp: function = ...)
```

Sorts a sequence using insertion sort algorithm.

---

### `quicksort` <a id="quicksort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn quicksort(items: list, descending: bool = ..., cmp: function = ...)
```

Sorts a sequence in-place using quicksort.

---

### `mergesort` <a id="mergesort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mergesort(items: list, descending: bool = ..., cmp: function = ...)
```

Sorts a sequence using mergesort algorithm.

---

### `heapsort` <a id="heapsort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn heapsort(items: list, descending: bool = ..., cmp: function = ...)
```

Sorts a sequence using heapsort.

---

### `counting_sort` <a id="counting_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn counting_sort(items: list, descending: bool = ...)
```

Sorts an integer list using counting sort.

---

### `radix_sort` <a id="radix_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn radix_sort(items: list, descending: bool = ...)
```

Sorts an integer list using radix sort.

---

### `timsort` <a id="timsort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timsort(items: list, descending: bool = ..., cmp: function = ...)
```

Sorts a sequence using adaptive timsort.

---

### `stable_sort` <a id="stable_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stable_sort(items: list, descending: bool = ..., cmp: function = ...)
```

Stable-sorts a sequence preserving relative order of equivalent items.

---

### `partial_sort` <a id="partial_sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn partial_sort(items: list, count: int, descending: bool = ..., cmp: function = ...)
```

Sorts the first `count` elements of a sequence.

---

### `sort` <a id="sort"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sort(items: list, descending: bool = ..., cmp: function = ...)
```

Default high-performance sequence sorting function.

---

### `compare` <a id="compare"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compare(a, b): Ordering
```

Compares two elements and returns their Ordering relation.

---

