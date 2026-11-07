# API Documentation: `matrix.lm`

## Overview

std/math/matrix.lm
4x4 row-major transformation matrix.

## Symbols

- **Frame**: [`Matrix`](#Matrix)

---

### `Matrix` <a id="Matrix"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Matrix
```

Represents a 4x4 floating-point transformation matrix stored in row-major order.
Defaults to an identity matrix upon initialization.

#### Example: Idiomatic Usage

```lymar
import std.math.matrix as mat;
var m = mat.Matrix();
print(m.get(0, 0)); // 1.0
m.set(0, 3, 10.0);  // set X translation
```

#### Members

- `var pub data: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn get(row: int, col: int): float` *(method)*
- `pub fn set(row: int, col: int, value_val: float)` *(method)*

---

