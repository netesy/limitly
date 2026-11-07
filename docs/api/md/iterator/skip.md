# API Documentation: `skip.lm`

## Overview

Standard Library Skip Iterator

## Symbols

- **Frame**: [`SkipIterator`](#SkipIterator)
- **Function**: [`skip`](#skip)

---

### `SkipIterator` <a id="SkipIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SkipIterator: it.Iterator
```

#### Members

- `var pub remaining: int` *(field)*
- `var pub source: it.Iterator` *(field)*
- `pub init(source: it.Iterator, count: int)` *(constructor)*
- `fn _drain()` *(method)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `skip` <a id="skip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn skip(source: it.Iterator, count: int): it.Iterator
```

---

