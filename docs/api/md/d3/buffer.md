# API Documentation: `buffer.lm`

## Overview

std/d3/buffer.lm
Staged frame templates for generic 3D geometry attributes and shader uniforms.

## Symbols

- **Frame**: [`BufferAttribute`](#BufferAttribute)
- **Frame**: [`Uniform`](#Uniform)
- **Type Alias**: [`FloatAttribute`](#FloatAttribute)
- **Type Alias**: [`IntAttribute`](#IntAttribute)
- **Function**: [`float_attribute`](#float_attribute)
- **Function**: [`int_attribute`](#int_attribute)

---

### `BufferAttribute` <a id="BufferAttribute"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BufferAttribute
```

#### Members

- `var pub data: list` *(field)*
- `var pub item_size: int` *(field)*
- `pub init(data: list)` *(constructor)*
- `pub fn count(): int` *(method)*
- `pub fn get(index: int): T` *(method)*
- `pub fn set(index: int, component: int, value: T)` *(method)*

---

### `Uniform` <a id="Uniform"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Uniform
```

#### Members

- `var pub name: str` *(field)*
- `var pub value: T` *(field)*
- `pub init(name: str, value: T)` *(constructor)*

---

### `FloatAttribute` <a id="FloatAttribute"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type FloatAttribute = BufferAttribute
```

---

### `IntAttribute` <a id="IntAttribute"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type IntAttribute = BufferAttribute
```

---

### `float_attribute` <a id="float_attribute"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn float_attribute(data: list, item_size: int = ...): FloatAttribute
```

---

### `int_attribute` <a id="int_attribute"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn int_attribute(data: list, item_size: int = ...): IntAttribute
```

---

