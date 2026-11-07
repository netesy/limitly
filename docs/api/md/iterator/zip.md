# API Documentation: `zip.lm`

## Overview

Standard Library Zip Iterator

## Symbols

- **Frame**: [`ZipIterator`](#ZipIterator)
- **Function**: [`zip`](#zip)

---

### `ZipIterator` <a id="ZipIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ZipIterator: it.Iterator
```

#### Members

- `var pub left: it.Iterator` *(field)*
- `var pub right: it.Iterator` *(field)*
- `pub init(left: it.Iterator, right: it.Iterator)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `zip` <a id="zip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn zip(left: it.Iterator, right: it.Iterator): it.Iterator
```

---

