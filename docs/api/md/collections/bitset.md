# API Documentation: `bitset.lm`

## Overview

Standard Library BitSet Collection

## Symbols

- **Frame**: [`BitSetIterator`](#BitSetIterator)
- **Frame**: [`BitSet`](#BitSet)
- **Function**: [`BitSetWrapper`](#BitSetWrapper)

---

### `BitSetIterator` <a id="BitSetIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BitSetIterator: Iterator
```

#### Members

- `var bitset: BitSet` *(field)*
- `var current: int` *(field)*
- `var yielded: int` *(field)*
- `pub init(bs: BitSet)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `BitSet` <a id="BitSet"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BitSet
```

#### Members

- `var w0: int` *(field)*
- `var w1: int` *(field)*
- `var w2: int` *(field)*
- `var w3: int` *(field)*
- `var size: int` *(field)*
- `var used: int` *(field)*
- `pub init()` *(constructor)*
- `fn _mask(bit: int): int` *(method)*
- `fn _valid(bit: int): bool` *(method)*
- `fn _word_value(word: int): int` *(method)*
- `fn _set_word(word: int, value: int)` *(method)*
- `pub fn set(bit: int)` *(method)*
- `pub fn unset(bit: int)` *(method)*
- `pub fn toggle(bit: int)` *(method)*
- `pub fn contains(bit: int): bool` *(method)*
- `pub fn get(bit: int): bool` *(method)*
- `pub fn count(): int` *(method)*
- `pub fn get_size(): int` *(method)*
- `pub fn iterator(): BitSetIterator` *(method)*

---

### `BitSetWrapper` <a id="BitSetWrapper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn BitSetWrapper(size: int = ...): BitSet
```

---

