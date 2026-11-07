# API Documentation: `map.lm`

## Overview

Standard Library Map Iterator
Architectural Note: Per AGENTS.md, Lymar currently lacks generic frame/template parameters (e.g. MapIterator<T>).
Until generic monomorphization is added to the Lymar frontend type checker, MapIterator relies on duck-typed field access
or dynamic trait bounds for its source iterator.

## Symbols

- **Frame**: [`MapIterator`](#MapIterator)
- **Function**: [`map`](#map)

---

### `MapIterator` <a id="MapIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame MapIterator: it.Iterator
```

#### Members

- `var pub source: it.Iterator` *(field)*
- `var pub f: function` *(field)*
- `pub init(source: it.Iterator, f: function)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `map` <a id="map"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn map(source: it.Iterator, f: function): it.Iterator
```

---

