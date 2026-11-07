# API Documentation: `iterator.lm`

## Overview

Standard Library Iterator Trait and Common Implementations

Termination is out-of-band: `has_next()` reports whether a value remains and
`next()` yields it. The earlier in-band `next() == nil` protocol silently
truncated iteration at the first nil element, because nil is a legal value in
an [any] sequence. Consumers must ask `has_next()` before calling `next()`.

## Symbols

- **Trait**: [`Iterator`](#Iterator)
- **Frame**: [`ListIterator`](#ListIterator)
- **Frame**: [`PeekableIterator`](#PeekableIterator)
- **Function**: [`iterator`](#iterator)
- **Function**: [`collect`](#collect)
- **Function**: [`collect_dict`](#collect_dict)
- **Function**: [`to_dict`](#to_dict)
- **Frame**: [`ChunkIterator`](#ChunkIterator)
- **Frame**: [`CycleIterator`](#CycleIterator)
- **Frame**: [`StepByIterator`](#StepByIterator)
- **Function**: [`chunk`](#chunk)
- **Function**: [`cycle`](#cycle)
- **Function**: [`step_by`](#step_by)
- **Function**: [`peekable`](#peekable)

---

### `Iterator` <a id="Iterator"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Iterator
```

#### Members

- `fn has_next(): bool` *(method requirement)*
- `fn next(): any` *(method requirement)*

---

### `ListIterator` <a id="ListIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ListIterator: Iterator
```

#### Members

- `var pub index: int` *(field)*
- `var pub items: list` *(field)*
- `pub init(items: list)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `PeekableIterator` <a id="PeekableIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PeekableIterator: Iterator
```

#### Members

- `var pub cached: any` *(field)*
- `var pub has_cached: bool` *(field)*
- `var pub source: Iterator` *(field)*
- `pub init(source: Iterator)` *(constructor)*
- `pub fn peek(): any` *(method)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `iterator` <a id="iterator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn iterator(items: list): Iterator
```

---

### `collect` <a id="collect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn collect(it: Iterator): list
```

---

### `collect_dict` <a id="collect_dict"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn collect_dict(it: Iterator): dict
```

---

### `to_dict` <a id="to_dict"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_dict(it: Iterator, key_fn: function = ..., val_fn: function = ...): dict
```

---

### `ChunkIterator` <a id="ChunkIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ChunkIterator: Iterator
```

#### Members

- `var pub size: int` *(field)*
- `var pub source: Iterator` *(field)*
- `var pub ready: bool` *(field)*
- `var pub pending: list` *(field)*
- `pub init(source: Iterator, size: int)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `CycleIterator` <a id="CycleIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame CycleIterator: Iterator
```

#### Members

- `var pub index: int` *(field)*
- `var pub items: list` *(field)*
- `pub init(items: list)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `StepByIterator` <a id="StepByIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame StepByIterator: Iterator
```

#### Members

- `var pub source: Iterator` *(field)*
- `var pub step: int` *(field)*
- `pub init(source: Iterator, step: int)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `chunk` <a id="chunk"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn chunk(it: Iterator, size: int): Iterator
```

---

### `cycle` <a id="cycle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cycle(items: list): Iterator
```

---

### `step_by` <a id="step_by"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn step_by(it: Iterator, step: int): Iterator
```

---

### `peekable` <a id="peekable"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn peekable(it: Iterator): PeekableIterator
```

---

