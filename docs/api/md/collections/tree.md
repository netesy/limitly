# API Documentation: `tree.lm`

## Overview

Standard Library TreeMap & TreeSet Collection

## Symbols

- **Frame**: [`AVLNode`](#AVLNode)
- **Frame**: [`TreeMap`](#TreeMap)
- **Frame**: [`TreeSet`](#TreeSet)
- **Frame**: [`BTree`](#BTree)

---

### `AVLNode` <a id="AVLNode"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame AVLNode
```

#### Members

- `var pub key: any` *(field)*
- `var pub value: any` *(field)*
- `var pub left: any` *(field)*
- `var pub right: any` *(field)*
- `pub init(key: any, value: any)` *(constructor)*

---

### `TreeMap` <a id="TreeMap"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TreeMap
```

#### Members

- `var pub root: any` *(field)*
- `var pub size: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn put(key: any, value: any)` *(method)*
- `pub fn get(key: any): any` *(method)*
- `pub fn contains(key: any): bool` *(method)*
- `pub fn remove(key: any): bool` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*

---

### `TreeSet` <a id="TreeSet"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TreeSet
```

#### Members

- `var pub map: TreeMap` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(item: any)` *(method)*
- `pub fn contains(item: any): bool` *(method)*
- `pub fn remove(item: any): bool` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*

---

### `BTree` <a id="BTree"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BTree
```

#### Members

- `var pub map: TreeMap` *(field)*
- `var pub order: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn put(key: any, value: any)` *(method)*
- `pub fn get(key: any): any` *(method)*
- `pub fn remove(key: any): bool` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*

---

