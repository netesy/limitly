# API Documentation: `index.lm`

## Overview

Standard Library Iterator Module

Iterator protocol traits, adapters (map, filter, take, skip, zip, chain), and pipeline generators.

## Symbols

- **Function**: [`iterator`](#iterator)
- **Function**: [`collect`](#collect)
- **Function**: [`collect_dict`](#collect_dict)
- **Function**: [`to_dict`](#to_dict)
- **Function**: [`map`](#map)
- **Function**: [`flat_map`](#flat_map)
- **Function**: [`flatten`](#flatten)
- **Function**: [`filter`](#filter)
- **Function**: [`take`](#take)
- **Function**: [`skip`](#skip)
- **Function**: [`zip`](#zip)
- **Function**: [`chain`](#chain)
- **Function**: [`enumerate`](#enumerate)
- **Function**: [`chunk`](#chunk)
- **Function**: [`cycle`](#cycle)
- **Function**: [`step_by`](#step_by)
- **Function**: [`peekable`](#peekable)

---

### `iterator` <a id="iterator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn iterator(items: list): Iterator
```

Common iterator helpers

---

### `collect` <a id="collect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn collect(source: Iterator): list
```

---

### `collect_dict` <a id="collect_dict"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn collect_dict(source: Iterator): dict
```

---

### `to_dict` <a id="to_dict"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_dict(source: Iterator, key_fn: function = ..., val_fn: function = ...): dict
```

---

### `map` <a id="map"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn map(source: Iterator, f: function): Iterator
```

Submodule functions

---

### `flat_map` <a id="flat_map"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flat_map(source: Iterator, f: function): Iterator
```

---

### `flatten` <a id="flatten"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn flatten(source: Iterator): Iterator
```

---

### `filter` <a id="filter"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn filter(source: Iterator, p: function): Iterator
```

---

### `take` <a id="take"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn take(source: Iterator, count: int): Iterator
```

---

### `skip` <a id="skip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn skip(source: Iterator, count: int): Iterator
```

---

### `zip` <a id="zip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn zip(left: Iterator, right: Iterator): Iterator
```

---

### `chain` <a id="chain"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn chain(left: Iterator, right: Iterator): Iterator
```

---

### `enumerate` <a id="enumerate"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn enumerate(source: Iterator): Iterator
```

---

### `chunk` <a id="chunk"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn chunk(source: Iterator, size: int): Iterator
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
pub fn step_by(source: Iterator, step: int): Iterator
```

---

### `peekable` <a id="peekable"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn peekable(source: Iterator): PeekableIterator
```

---

