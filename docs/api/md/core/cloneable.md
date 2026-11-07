# API Documentation: `cloneable.lm`

## Overview

Standard Library Core Cloneable Trait

Behavioral contract for types supporting deep or shallow replication.

## Symbols

- **Trait**: [`Cloneable`](#Cloneable)

---

### `Cloneable` <a id="Cloneable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Cloneable
```

Interface for objects that can produce an independent copy of themselves.

#### Example: Idiomatic Usage

```lymar
frame Config : Cloneable {
    pub name: str;
    pub fn clone(): any {
        var c = Config();
        c.name = self.name;
        return c;
    }
}
```

#### Members

- `fn clone(): any` *(method requirement)*

---

