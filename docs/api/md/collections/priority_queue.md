# API Documentation: `priority_queue.lm`

## Overview

Standard Library PriorityQueue Collection

Min-heap ordered by a caller-supplied comparator. `PriorityQueue(T)` is a
staged frame: instantiate it with a type argument (e.g. `PriorityQueue(int)`)
and pass a `fn(T, T): int` comparator to `init`. The comparator returns a
negative value when `left` should sort ahead of `right`, zero when equal, and
a positive value when `left` should sort behind `right`.

## Symbols

- **Frame**: [`PriorityQueue`](#PriorityQueue)

---

### `PriorityQueue` <a id="PriorityQueue"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PriorityQueue
```

#### Members

- `var pub heap: list` *(field)*
- `var size: int` *(field)*
- `var comparator: function` *(field)*
- `pub init(comparator: function)` *(constructor)*
- `fn _compare(left: T, right: T): int` *(method)*
- `pub fn insert(item: T)` *(method)*
- `pub fn push(item: T)` *(method)*
- `pub fn peek(): union` *(method)*
- `pub fn remove(): union` *(method)*
- `pub fn pop(): union` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn clear()` *(method)*
- `fn _sift_up(idx: int)` *(method)*
- `fn _sift_down(idx: int)` *(method)*

---

