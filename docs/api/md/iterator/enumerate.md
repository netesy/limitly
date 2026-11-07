# API Documentation: `enumerate.lm`

## Overview

Standard Library Enumerate Iterator

## Symbols

- **Frame**: [`EnumerateIterator`](#EnumerateIterator)
- **Function**: [`enumerate`](#enumerate)

---

### `EnumerateIterator` <a id="EnumerateIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame EnumerateIterator: it.Iterator
```

#### Members

- `var pub index: int` *(field)*
- `var pub source: it.Iterator` *(field)*
- `pub init(source: it.Iterator)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `enumerate` <a id="enumerate"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn enumerate(source: it.Iterator): it.Iterator
```

---

