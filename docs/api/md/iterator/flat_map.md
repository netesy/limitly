# API Documentation: `flat_map.lm`

## Overview

Standard Library FlatMap Iterator

## Symbols

- **Frame**: [`FlatMapIterator`](#FlatMapIterator)
- **Function**: [`flat_map`](#flat_map)
- **Function**: [`flatten`](#flatten)

---

### `FlatMapIterator` <a id="FlatMapIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FlatMapIterator: it.Iterator
```

#### Members

- `var pub source: it.Iterator` *(field)*
- `var pub f: function` *(field)*
- `var pub inner_iter: any` *(field)*
- `var pub has_inner: bool` *(field)*
- `var pub ready: bool` *(field)*
- `var pub pending: any` *(field)*
- `pub init(source: it.Iterator, f: function)` *(constructor)*
- `fn _advance(): bool` *(method)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `flat_map` <a id="flat_map"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flat_map(source: it.Iterator, f: function): it.Iterator
```

---

### `flatten` <a id="flatten"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flatten(source: it.Iterator): it.Iterator
```

---

