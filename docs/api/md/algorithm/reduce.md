# API Documentation: `reduce.lm`

## Overview

Standard Library Sequence Reduction Submodule

Left-associative accumulation and fold operations.

## Symbols

- **Function**: [`reduce`](#reduce)
- **Function**: [`fold`](#fold)

---

### `reduce` <a id="reduce"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn reduce(items: list, f: function, initial)
```

Reduces a sequence to a single accumulated value using a binary reducer function.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence of elements to accumulate. |
| `f` | Binary reducer function `f(accumulator, current_item)`. |
| `initial` | Initial accumulator starting value. |

#### Returns

Final accumulated value.

#### Example: Idiomatic Usage

```lymar
fn add(a: any, b: any): any { return (a as int) + (b as int); }
var sum = reduce([1, 2, 3, 4], add, 0); // 10
```

---

### `fold` <a id="fold"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fold(items: list, initial, f: function)
```

Folds a sequence starting from an initial value using a binary accumulation function.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | Sequence of elements. |
| `initial` | Initial starting value. |
| `f` | Binary folding function `f(accumulator, item)`. |

#### Returns

Final accumulated value.

---

