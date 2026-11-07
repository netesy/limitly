# API Documentation: `distributions.lm`

## Overview

std/random/distributions.lm
Statistical and uniform distributions.

## Symbols

- **Frame**: [`Uniform`](#Uniform)

---

### `Uniform` <a id="Uniform"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Uniform
```

Continuous uniform distribution over the real interval `[min_val, max_val)`.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Useful for sampling values where all outcomes within the range have equal likelihood.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `min_val` | Inclusive minimum value of the interval. |
| `max_val` | Exclusive maximum value of the interval. |

#### Members

- `var pub min_val: float` *(field)*
- `var pub max_val: float` *(field)*
- `pub init(min_val: float, max_val: float)` *(constructor)*
- `pub fn sample(rng: r.Random): float` *(method)*

---

