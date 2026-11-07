# API Documentation: `document.lm`

## Overview

Standard Library NOL Document and Builder
Netesy Object Language (NOL)

## Symbols

- **Frame**: [`Document`](#Document)
- **Frame**: [`Builder`](#Builder)

---

### `Document` <a id="Document"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Document
```

Represents a parsed NOL configuration document with path querying.

#### Members

- `var pub root: value.Value` *(field)*
- `pub init(root: value.Value)` *(constructor)*
- `fn resolve_node(curr: any, parts: list, idx: int): any` *(method)*
- `pub fn get(path: str): any` *(method)*
- `pub fn exists(path: str): bool` *(method)*
- `pub fn data(): value.Value` *(method)*

---

### `Builder` <a id="Builder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Builder
```

Fluent builder for constructing NOL documents programmatically.

#### Members

- `var pub root: value.Value` *(field)*
- `pub init()` *(constructor)*
- `fn builder_set(curr: any, parts: list, idx: int, value_node: any)` *(method)*
- `pub fn set(path: str, value_node: any): Builder` *(method)*
- `pub fn build(): Document` *(method)*

---

