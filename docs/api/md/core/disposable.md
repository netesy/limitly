# API Documentation: `disposable.lm`

## Overview

Standard Library Core Disposable Trait

Behavioral contract for deterministic resource reclamation.

## Symbols

- **Trait**: [`Disposable`](#Disposable)

---

### `Disposable` <a id="Disposable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Disposable
```

Interface for objects holding unmanaged system handles or resources.

#### Example: Idiomatic Usage

```lymar
frame FileStream : Disposable {
    pub handle: int;
    pub fn dispose(): nil {
        if (self.handle != 0) {
            // close handle
            self.handle = 0;
        }
    }
}
```

#### Members

- `fn dispose(): nil` *(method requirement)*

---

