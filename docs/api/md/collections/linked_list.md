# API Documentation: `linked_list.lm`

## Overview

Standard Library LinkedList Collection

## Symbols

- **Frame**: [`Node`](#Node)
- **Frame**: [`LinkedListIterator`](#LinkedListIterator)
- **Frame**: [`LinkedList`](#LinkedList)

---

### `Node` <a id="Node"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Node
```

#### Members

- `var pub value: T` *(field)*
- `var pub next: any` *(field)*
- `pub init(value: T)` *(constructor)*

---

### `LinkedListIterator` <a id="LinkedListIterator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LinkedListIterator: Iterator
```

#### Members

- `var current: any` *(field)*
- `pub init(head: any)` *(constructor)*
- `pub fn has_next(): bool` *(method)*
- `pub fn next(): any` *(method)*

---

### `LinkedList` <a id="LinkedList"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LinkedList
```

#### Members

- `var pub head: any` *(field)*
- `var pub tail: any` *(field)*
- `var pub size: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn push_back(value: T)` *(method)*
- `pub fn push_front(value: T)` *(method)*
- `pub fn pop_back(): union` *(method)*
- `pub fn pop_front(): union` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn is_empty(): bool` *(method)*
- `pub fn iterator(): LinkedListIterator` *(method)*

---

