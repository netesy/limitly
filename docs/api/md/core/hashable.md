# API Documentation: `hashable.lm`

## Overview

Standard Library Core Hashable Trait

Behavioral contract for hash code computation.

## Symbols

- **Trait**: [`Hashable`](#Hashable)

---

### `Hashable` <a id="Hashable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Hashable
```

Interface for objects that can compute a stable 64-bit hash code.
Objects that compare equal must return identical hash codes.

#### Example: Idiomatic Usage

```lymar
frame UserKey : Hashable {
    pub id: int;
    pub fn hash(): int {
        return self.id;
    }
}
```

#### Members

- `fn hash(): int` *(method requirement)*

---

