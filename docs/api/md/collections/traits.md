# API Documentation: `traits.lm`

## Overview

Standard Library Collections Traits

## Symbols

- **Trait**: [`Collection`](#Collection)
- **Trait**: [`Indexable`](#Indexable)
- **Trait**: [`Mutable`](#Mutable)

---

### `Collection` <a id="Collection"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Collection
```

Common interface for sized collection data structures.
Defines universal queries and operations supported across all container types.

#### Example: Idiomatic Usage

```lymar
var list = List();
if (list.is_empty()) {
    print("Empty collection");
}
```

#### Members

- `fn len(): int` *(method requirement)*
- `fn is_empty(): bool` *(method requirement)*
- `fn clear(): nil` *(method requirement)*

---

### `Indexable` <a id="Indexable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Indexable
```

Interface for collections supporting zero-based indexed element access.

> [!NOTE]
> **Note**: Implementations should safely validate index bounds.

#### Example: Idiomatic Usage

```lymar
var list = List();
list.append(10);
var item = list.get(0);
```

#### Members

- `fn get(index: int): any` *(method requirement)*
- `fn set(index: int, item: any): bool` *(method requirement)*

---

### `Mutable` <a id="Mutable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Mutable
```

Interface for collections supporting in-place element insertion and removal.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Combine with `Indexable` for full dynamic list semantics.

#### Example: Idiomatic Usage

```lymar
var list = List();
list.append("hello");
list.remove(0);
```

#### Members

- `fn append(item: any): nil` *(method requirement)*
- `fn remove(index: int): any` *(method requirement)*

---

