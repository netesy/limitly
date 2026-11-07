# API Documentation: `index.lm`

## Overview

Standard Library Core Traits
These traits define shared capabilities for stdlib abstractions.

The Iterator contract lives next to its adapters in std.iterator and is
re-exported here: the two hand-written copies that used to exist accepted the
same call shape but were distinct nominal traits, so iterators produced by one
module could not be handed to consumers in the other.

## Symbols

- **Trait**: [`Iterable`](#Iterable)

---

### `Iterable` <a id="Iterable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Iterable
```

Iterable trait for types that can create an iterator

#### Members

- `fn iterator(): Iterator` *(method requirement)*

---

