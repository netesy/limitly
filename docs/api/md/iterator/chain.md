# API Documentation: `chain.lm`

## Overview

Standard Library Chain Iterator

## Symbols

- **Frame**: [`ChainIterator`](#ChainIterator)
- **Function**: [`chain`](#chain)

---

### `ChainIterator` <a id="ChainIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ChainIterator: it.Iterator
```

#### Members

- `var pub left: it.Iterator` *(field)*
- `var pub on_left: bool` *(field)*
- `var pub right: it.Iterator` *(field)*
- `pub init(left: it.Iterator, right: it.Iterator)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `chain` <a id="chain"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn chain(left: it.Iterator, right: it.Iterator): it.Iterator
```

---

