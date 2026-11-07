# API Documentation: `filter.lm`

## Overview

Standard Library Filter Iterator

## Symbols

- **Frame**: [`FilterIterator`](#FilterIterator)
- **Function**: [`filter`](#filter)

---

### `FilterIterator` <a id="FilterIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FilterIterator: it.Iterator
```

#### Members

- `var pub p: function` *(field)*
- `var pub source: it.Iterator` *(field)*
- `var pub ready: bool` *(field)*
- `var pub pending: any` *(field)*
- `pub init(source: it.Iterator, p: function)` *(constructor)*
- `fn _fill()` *(method)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `filter` <a id="filter"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn filter(source: it.Iterator, p: function): it.Iterator
```

---

