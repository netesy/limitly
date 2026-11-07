# API Documentation: `take.lm`

## Overview

Standard Library Take Iterator

## Symbols

- **Frame**: [`TakeIterator`](#TakeIterator)
- **Function**: [`take`](#take)

---

### `TakeIterator` <a id="TakeIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TakeIterator: it.Iterator
```

#### Members

- `var pub remaining: int` *(field)*
- `var pub source: it.Iterator` *(field)*
- `pub init(source: it.Iterator, count: int)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `take` <a id="take"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn take(source: it.Iterator, count: int): it.Iterator
```

---

