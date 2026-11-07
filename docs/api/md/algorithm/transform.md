# API Documentation: `transform.lm`

## Overview

std/algorithm/transform.lm
Transform submodule for std.algorithm. Algorithmic utilities, searching, filtering, and sequence manipulation.

## Symbols

- **Function**: [`map`](#map)
- **Function**: [`zip`](#zip)
- **Function**: [`unzip`](#unzip)
- **Function**: [`transform`](#transform)
- **Function**: [`_reverse_range`](#_reverse_range)
- **Function**: [`reverse`](#reverse)
- **Function**: [`rotate`](#rotate)

---

### `map` <a id="map"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn map(items: list, f: function): list
```

---

### `zip` <a id="zip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn zip(left: list, right: list): list
```

---

### `unzip` <a id="unzip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn unzip(pairs: list): tuple
```

---

### `transform` <a id="transform"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn transform(items: list, f: function): list
```

---

### `_reverse_range` <a id="_reverse_range"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _reverse_range(items: list, start: int, end: int)
```

---

### `reverse` <a id="reverse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn reverse(items: list)
```

---

### `rotate` <a id="rotate"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rotate(items: list, k: int)
```

---

