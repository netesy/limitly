# API Documentation: `index.lm`

## Overview

std/range/index.lm
Public entrypoint and facade for std.range. Range generators, stepping, and range iterators.

## Symbols

- **Frame**: [`Range`](#Range)
- **Frame**: [`RangeIterator`](#RangeIterator)
- **Function**: [`exclusive`](#exclusive)
- **Function**: [`inclusive`](#inclusive)
- **Function**: [`stepped`](#stepped)
- **Function**: [`reverse`](#reverse)
- **Function**: [`infinite`](#infinite)

---

### `Range` <a id="Range"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Range
```

#### Members

- `var pub start: int` *(field)*
- `var pub stop: int` *(field)*
- `var pub step: int` *(field)*
- `var pub inclusive: bool` *(field)*
- `var pub infinite: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn iterator(): RangeIterator` *(method)*

---

### `RangeIterator` <a id="RangeIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RangeIterator: Iterator
```

#### Members

- `var current: int` *(field)*
- `var stop: int` *(field)*
- `var step: int` *(field)*
- `var inclusive: bool` *(field)*
- `var infinite: bool` *(field)*
- `pub init(start: int, stop: int)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `exclusive` <a id="exclusive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exclusive(start: int, stop: int, step: int = ...): Range
```

---

### `inclusive` <a id="inclusive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn inclusive(start: int, stop: int, step: int = ...): Range
```

---

### `stepped` <a id="stepped"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stepped(start: int, stop: int, step: int): Range
```

---

### `reverse` <a id="reverse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn reverse(start: int, stop: int, step: int = ...): Range
```

---

### `infinite` <a id="infinite"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn infinite(start: int = ..., step: int = ...): Range
```

---

