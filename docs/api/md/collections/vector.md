# API Documentation: `vector.lm`

## Overview

Standard Library Vector, ArrayList, and RingBuffer Collections

## Symbols

- **Frame**: [`Vector`](#Vector)
- **Frame**: [`VectorIterator`](#VectorIterator)
- **Frame**: [`ArrayList`](#ArrayList)
- **Frame**: [`RingBuffer`](#RingBuffer)

---

### `Vector` <a id="Vector"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Vector
```

#### Members

- `var pub data: list` *(field)*
- `var size: int` *(field)*
- `var capacity: int` *(field)*
- `pub init()` *(constructor)*
- `fn _copy_without(index_to_skip: int): list` *(method)*
- `fn _grow_for(count: int)` *(method)*
- `pub fn append(item: T)` *(method)*
- `pub fn push(item: T)` *(method)*
- `pub fn insert(index: int, item: T)` *(method)*
- `pub fn remove(index: int): union` *(method)*
- `pub fn pop(): union` *(method)*
- `pub fn get(index: int): union` *(method)*
- `pub fn set(index: int, item: T): bool` *(method)*
- `pub fn peek(): union` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn reserve(new_capacity: int)` *(method)*
- `pub fn resize(new_size: int, fill: T)` *(method)*
- `pub fn clear()` *(method)*
- `pub fn iterator(): Iterator` *(method)*

---

### `VectorIterator` <a id="VectorIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame VectorIterator: Iterator
```

#### Members

- `var data: list` *(field)*
- `var index: int` *(field)*
- `pub init(data: list)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `ArrayList` <a id="ArrayList"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ArrayList
```

#### Members

- `var data: Vector` *(field)*
- `pub init()` *(constructor)*
- `pub fn push(item: T)` *(method)*
- `pub fn pop(): union` *(method)*
- `pub fn remove(index: int): union` *(method)*
- `pub fn resize(new_size: int, fill: T)` *(method)*
- `pub fn get(index: int): union` *(method)*
- `pub fn set(index: int, item: T): bool` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn iterator(): Iterator` *(method)*

---

### `RingBuffer` <a id="RingBuffer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RingBuffer
```

#### Members

- `var data: list` *(field)*
- `var capacity: int` *(field)*
- `var start: int` *(field)*
- `var count: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn push(item: T)` *(method)*
- `pub fn pop(): union` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn size(): int` *(method)*

---

