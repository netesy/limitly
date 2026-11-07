# API Documentation: `comparable.lm`

## Overview

Standard Library Core Comparable Trait

Behavioral contract for ordering and comparison.

## Symbols

- **Trait**: [`Comparable`](#Comparable)

---

### `Comparable` <a id="Comparable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Comparable
```

Interface for objects that can be compared for ordering.
Implementations must return:
- `< 0` if `self < other`
- `0` if `self == other`
- `> 0` if `self > other`

#### Example: Idiomatic Usage

```lymar
frame Priority : Comparable {
    pub level: int;
    pub fn compare(other: any): int {
        var o = other as Priority;
        if (self.level < o.level) return -1;
        if (self.level > o.level) return 1;
        return 0;
    }
}
```

#### Members

- `fn compare(other: any): int` *(method requirement)*

---

